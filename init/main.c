/*
 * Common kernel entry point.
 */

#include <multiboot.h>
#include <types.h>
#include <keywords.h>

/*
 * This function is called by the architecture-specific boot proceedure, and
 * defines the entry to the euclid kernel.
 */
int k_main(struct multiboot *mboot, u32 stack);

__diagnostic_disable(unused-parameter)

int k_main(struct multiboot *mboot, u32 stack)
{
	/* For now let's just push a value to EAX (x86). */
	return (int)0xABCDEFCC;
}

__diagnostic_enable(unused-parameter)
