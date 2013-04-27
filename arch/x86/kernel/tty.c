#include <kernel/tty.h>

#include <kernel/memory-map.h>
#include <kernel/port.h>

#include <assert.h>
#include <stdio.h>
#include <string.h>

/* The physical dimensions of the TTY, in units of characters */
#define TTY_WIDTH		80
#define TTY_HEIGHT		25
#define TTY_SIZE		(TTY_WIDTH * TTY_HEIGHT)
#define TTY_WIDTH_BYTES 	(TTY_WIDTH * sizeof(tty_char_t))

/* Each TTY character consists of two bytes, with bits 7:0 being an ASCII code,
 * and the higher and lower nibbles of bits 15:8 representing the background and
 * foreground colours, respectively
 */
typedef u16			tty_char_t;

/* Memory regions for TTY */
#define TTY_MEMORY		(tty_char_t *)COLOR_TEXT_MODE_MEMORY
#define TTY_MEMORY_SIZE		(TTY_SIZE * sizeof (tty_char_t))
#define TTY_MEMORY_END		TTY_MEMORY + TTY_MEMORY_SIZE

/* Checks if a given address is with the TTY memory region */
#define is_in_tty_memory_region(addr)		\
	__is_in_region(addr, TTY_MEMORY, TTY_MEMORY_END)

/* Zero if the TTY is uninitialised, else set to the return value
 * of init_tty()
 */
static int tty_initialised = 0;

/* Track the cursor position, color and memory index */
static struct {
	enum tty_color_e bg;
	enum tty_color_e fg;
	u8 x;
	u8 y;
	u16 __pad__; /* alignment boundary */
} cursor;

/* Returns an index into the TTY memory for a given cursor position */
static inline u16 get_index_for_pos(const u8 y, const u8 x)
{
	assert(y <= TTY_HEIGHT);
	assert(x <= TTY_WIDTH);

	return (y * TTY_WIDTH) + x;
}

/* Returns a pointer to the TTY memory of a given cursor position */
static inline tty_char_t *get_mem_for_pos(const u8 y, const u8 x)
{
	assert(y <= TTY_HEIGHT);
	assert(x <= TTY_WIDTH);

	return TTY_MEMORY + get_index_for_pos(y, x);
}

/* Returns the TTY attribute byte for the given colors */
static inline u8 get_attribute_byte(const enum tty_color_e bg,
				    const enum tty_color_e fg)
{
	return (bg << 4) | (fg & 0xF);
}

/* Convert an ASCII char into a TTY char with color information obtained from
 * the cursor */
static inline tty_char_t char_to_tty_char(const char c,
					  const enum tty_color_e bg,
					  const enum tty_color_e fg)
{
	return c | (get_attribute_byte(bg, fg) << 8);
}

/* Write a blank character to the character pointed to by tty_char_p */
static inline void blank_char(tty_char_t *tty_char_p)
{
	assert(is_in_tty_memory_region(tty_char_p));

	if (unlikely(!tty_initialised))
		return;

	*tty_char_p = char_to_tty_char(' ',
				       TTY_COLOR_DEFAULT_BG,
				       TTY_COLOR_DEFAULT_FG);
}

/* Updates the hardware cursor position based on the cursor.[xy] values */
static void update_cursor_pos(void)
{
	u16 index = get_index_for_pos(cursor.y, cursor.x);

	assert(cursor.x <= TTY_WIDTH);
	assert(cursor.y <= TTY_HEIGHT);

	/* transmit high then low byte */
	tty_command_out(14);
	tty_data_out(index >> 8);
	tty_command_out(15);
	tty_data_out(index & 0x00FF);
}

/* scroll the display one line */
static void scroll_line(void)
{
	int i;

	if (unlikely(!tty_initialised))
		return;

	/* duplicate each line onto the preceding one */
	for (i = 0; i < TTY_HEIGHT - 1; i++) {
		memcpy(get_mem_for_pos(i, 0),
		       get_mem_for_pos(i + 1, 0),
		       TTY_WIDTH_BYTES);
	}

	/* insert a blank final line */
	memset(get_mem_for_pos(TTY_HEIGHT - 1, 0), 0x00, TTY_WIDTH_BYTES);

	/* scroll the hardware cursor */
	if (cursor.y) {
		cursor.y--;
		update_cursor_pos();
	}
}

inline void tty_reset_color(void)
{
	tty_set_color(TTY_COLOR_DEFAULT_BG, TTY_COLOR_DEFAULT_FG);
}

inline void tty_reset(void)
{
	tty_clear_screen();
	tty_reset_color();
}

int init_tty(void *data)
{
	/* protect against re-initialising */
	if (likely(!tty_initialised)) {
		tty_initialised = 1;

		/* prepare the screen */
		tty_reset();
	}

	return tty_initialised;
}

inline int test_tty(void *data)
{
	int i = 1234, j = 0;

	printf("printf() conversion characters:\n");
	printf("\td: %d\n", -1234);
	printf("\ti: %u\n", 1234);
	printf("\tx: 0x%x, 0x%X\n", 1234);
	printf("\tc: `%c'\n", 'c');
	printf("\ts: `%s'\n", "Hello, World!");
	printf("\tp: 0x%p, 0x%p\n", &i, &j);
	printf("\n");

	printf("debugging messages:\n");
	debug("\tNDEBUG not defined");
	debug("\tformat test: %d", 1234);
	printf("\n");

	return 0;
}

void tty_clear_screen(void)
{
	if (unlikely(!tty_initialised))
		return;

	memset(TTY_MEMORY, 0x00, TTY_SIZE * sizeof(tty_char_t));

	cursor.x = 0;
	cursor.y = 0;
	update_cursor_pos();
}

void tty_putc(const char c)
{
	tty_char_t *c_p;

	if (unlikely(!tty_initialised))
		return;

	c_p = TTY_MEMORY + get_index_for_pos(cursor.y, cursor.x);

	assert(is_in_tty_memory_region(c_p));

	switch (c) {
	case ASCII_BACKSPACE:
		if (cursor.x) {
			blank_char(--c_p);
			cursor.x--;
		} else {
			/* start of line, don't backspace */
			blank_char(c_p);
		}
		break;

	case '\t':
	{
		u8 i, new_x, x_diff;

		/* get the number of spaces traversed (in the range [1, 8]).
		 * Enforce a maximum new x of TTY_WIDTH, as we don't want a tab
		 * character to wrap around a line. */
		new_x = min((cursor.x + 8) & ~(8 - 1), TTY_WIDTH);
		x_diff = new_x - cursor.x;

		/* step through each empty space, preserving the correct bg
		 * color */
		for (i = 0; i < x_diff; i++)
			tty_putc(' ');
	}
		break;

	case '\n':
		cursor.y++;
		/* fall through */
	case '\r':
		cursor.x = 0;
		break;

	default:
		if (c >= ' ') {
			*c_p = char_to_tty_char(c, cursor.bg, cursor.fg);
			cursor.x++;
		}
		break;
	}

	/* wrap to the next line if necessary */
	if (cursor.x >= TTY_WIDTH) {
		cursor.x = 0;
		cursor.y++;
	}

	/* scroll the screen if necessary */
	while (cursor.y >= TTY_HEIGHT) {
		scroll_line();
	}

	update_cursor_pos();
}

void tty_set_bg_color(const enum tty_color_e color)
{
	cursor.bg = color;
}

void tty_set_fg_color(const enum tty_color_e color)
{
	cursor.fg = color;
}
