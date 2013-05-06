#include <kernel/panic.h>

#include <elf.h>
#include <macros.h>
#include <stdio.h>
#include <types.h>

#define MAX_STACK_FRAME 10000

/*
 * Walk up the stack and print the locations of each stack frame base.
 */
void bt(void) {
	u32 *ebp, *eip;
	unsigned int sf = 0;

	/* Start form the current stack base */
	asm volatile("mov %%ebp, %0" : "=r" (ebp));

	/* Continue until you reach a zeroed stack base pointer. The initial ebp
	 * value is zeroed at boot, but note that this could be corrupted in the
	 * case of serious memory corruption. To protect against this, we keep
	 * track of the frame number and break if it exceeds a reasonable
	 * maximum value. */
	while (ebp) {
		eip = ebp + 1;
		printf("#%d  [0x%x] %s\n",
		       sf, *eip, symbol_from_elf(&kelf, *eip));
		ebp = (u32*)*ebp;
		sf++;

		/* break if exceeded maximum */
		if (sf > MAX_STACK_FRAME)
			break;
	}
}
