/*
 * Common kernel entry point.
 */

#include <kernel/tty.h>
#include <kernel/subsystems.h>

#include <multiboot.h>
#include <stdio.h>
#include <types.h>

/*
 * This function is called by the architecture-specific boot proceedure, and
 * defines the entry to the euclid kernel.
 */
int k_main(struct multiboot *mboot, u32 stack);

int k_main(struct multiboot *mboot, u32 stack)
{
	/* bring up the kernel subsystems */
	init_subsystems();

	printf("Hello, World!\n");

	/* For now let's just push a value to EAX (x86). */
	return (int)0xABCDEFCC;
}
