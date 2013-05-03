#include <kernel/pit.h>

#include <kernel/idt.h>
#include <kernel/port.h>

#include <macros.h>
#include <stdio.h>

/* Frequency of the internal PIT clock, in Hz */
#define CLOCK_FREQUENCY 1193180

static int pit_initialised = 0;

static unsigned long _tick = 0;
static unsigned long frequency = 0;

static void tick(struct r r) {
	_tick++;
}

unsigned long pit_freq(void) {
	return_val_if_fail(pit_initialised, 0);

	return frequency;
}

int init_pit(void *data)
{
	u16 divisor;

	return_val_if_fail(!pit_initialised, -1);

	/* Don't set the PIT if no passed NULL */
	if (!data) {
		debug("PIT inactive");
		return 0;
	}

	frequency = (unsigned long)data;

	debug("Activated PIT (f: %u)", frequency);

	/* ensure that frequency is in bounds */
	return_val_if_fail(frequency <= CLOCK_FREQUENCY, 1);

	register_interrupt_handler(IRQ0, (ihandler)&tick);

	divisor = CLOCK_FREQUENCY / frequency;

	/* send the divisor byte-wise */
	pit_command_out(0x36);
	pit_0_data_out((char)(divisor & 0xFF));
	pit_0_data_out((char)((divisor>>8) & 0xFF));

	pit_initialised = 1;

	return 0;
}
