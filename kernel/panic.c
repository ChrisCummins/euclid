#include <kernel/panic.h>

#include <kernel/subsystems.h>

#include <stdarg.h>
#include <stdio.h>

/* halt the CPU */
static void self_stop(void)
{
	while (1)
		;
}

void panic(const char *fmt, ...)
{
	va_list ap;

	printf("\n\t\t***** KERNEL PANIC *****\n\n");

	printf("An unrecoverable error has been encountered:\n\n");

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);

	printf("\n\nBeginning subsystem teardown:\n\n");
	teardown_subsystems();

	self_stop();
}
