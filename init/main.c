/*
 * Common kernel entry point.
 */

#include <kernel/tty.h>

#include <assert.h>
#include <macros.h>
#include <multiboot.h>
#include <types.h>

/*
 * This function is called by the architecture-specific boot proceedure, and
 * defines the entry to the euclid kernel.
 */
int k_main(struct multiboot *mboot, u32 stack);

/* Bring up the kernel subsystems. Errors in this early stage of the bootprocess
 * are fatal and unrecoverable, so do as little initialisation as is possible to
 * bring the system into a working state. At this point in the boot process, you
 * cannot rely on the functioning of any other kernel components
 */
static inline void init_subsystems(void)
{
	assert(init_tty());
}

int k_main(struct multiboot *mboot, u32 stack)
{
	/* bring up the kernel subsystems */
	init_subsystems();

	/* For now let's just push a value to EAX (x86). */
	return (int)0xABCDEFCC;
}
