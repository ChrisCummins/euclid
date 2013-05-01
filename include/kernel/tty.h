/*
 * The euclid tty terminal interface.
 *
 * Implementations for the tty functions are architecture specific, see:
 * 	arch/<arch>/kernel/tty.c
 */

#ifndef _TTY_H
#define _TTY_H

#include <macros.h>

/* Characters which cannot be printed */
#define ASCII_BACKSPACE 0x08

/* The tty has 16 possible colours which can be assigned as foreground and
 * background colours. See tty_set_color() */
enum tty_color_e {
	TTY_COLOR_BLACK         = 0x0,
	TTY_COLOR_DARK_GREY     = 0x8,
	TTY_COLOR_BLUE          = 0x1,
	TTY_COLOR_LIGHT_BLUE    = 0x9,
	TTY_COLOR_GREEN         = 0x2,
	TTY_COLOR_LIGHT_GREEN   = 0xA,
	TTY_COLOR_CYAN          = 0x3,
	TTY_COLOR_LIGHT_CYAN    = 0xB,
	TTY_COLOR_RED           = 0x4,
	TTY_COLOR_LIGHT_RED     = 0xC,
	TTY_COLOR_MAGENTA       = 0x5,
	TTY_COLOR_LIGHT_MAGNETA = 0xD,
	TTY_COLOR_BROWN         = 0x6,
	TTY_COLOR_LIGHT_BROWN   = 0xE,
	TTY_COLOR_LIGHT_GREY    = 0x7,
	TTY_COLOR_WHITE         = 0xF
};

/* Default color values */
#define TTY_COLOR_DEFAULT_BG TTY_COLOR_BLACK
#define TTY_COLOR_DEFAULT_FG TTY_COLOR_LIGHT_GREY

/* Print a character to the screen */
void tty_putc(const char c);

/* Clear the contents of the screen, resetting cursor to line 1, column 1 */
void tty_clear_screen(void);

/* Reset the terminal color to the system default */
void tty_reset_color(void);

/* Reset the terminal (clear screen and reset color) */
void tty_reset(void);

/* Set the background color at the cursor */
void tty_set_bg_color(const enum tty_color_e color);

/* Set the foreground color (text color) at the cursor */
void tty_set_fg_color(const enum tty_color_e color);

/* Convenience macro to set both foreground and background colors
 * simultaneously */
#define tty_set_color(bg, fg)			\
	tty_set_bg_color(bg);			\
	tty_set_fg_color(fg)

/* Initialise the tty. Returns a zero on success. Non-successful initialisation
 * is considered an unrecoverable fault */
int init_tty(void *data) __warn_unused_result;

/* Perform post-init tests */
int test_tty(void *data);

#endif /* _TTY_H */
