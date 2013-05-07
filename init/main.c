/**
 * \mainpage
 *
 * # Overview
 * The Euclid kernel is a hobby `toy OS' project written by myself (Chris
 * Cummins) in my free time as a means for better understanding the internals of
 * a computer operating system, by writing one. The name is a nod to Euclid's
 * Elements, a mathematical teatrise in which the author begins with a small
 * handful of axioms with which he methodically constructs a vast landscape of
 * proofs in geometry, far beyond the scope of his humble opening
 * statements. When writing an operating system kernel, the author must begin
 * with a small handful of tools ("wtf, not even standard libraries!?") and
 * construct a full system to bridge the gap between hardware and userspace
 * programs.
 *
 * The intention of this project is not to produce a complete operating system,
 * but I am instead using it as an opportunity to explore some of the
 * fascinating challenges involved in kernel development, drawing inspiration
 * heavily from existing mature projects and UNIX-like systems, with
 * particularly heavy credit owed to the Linux kernel.
 */

/**
 * @file main.c
 *
 * Common entry point for the kernel. The early boot process is dictated by the
 * architecture-specific implementations. Each architecture implements a
 * procedure for preparing the stack and stack frame pointer, disable interrupts
 * and finally call the @ref k_main() function.
 *
 * On x86, the assembly routine that is responsible for calling @ref k_main() on
 * initial boot is defined in `arch/x86/boot/boot.s`.
 */

#include <kernel/panic.h>
#include <kernel/subsystems.h>
#include <kernel/tty.h>

#include <multiboot.h>
#include <stdio.h>
#include <types.h>

/**
 * The main kernel entry point.
 *
 * This function is called by the architecture-specific boot proceedure, and
 * defines the entry to the euclid kernel.
 */
int k_main(struct multiboot *mboot, u32 stack);

struct elf kelf;

int k_main(struct multiboot *mboot, u32 stack)
{
	elf_from_mb(mboot, &kelf);

	/* bring up the kernel subsystems */
	init_subsystems();

	printf("@@@@@@@@@@@@@@@@@@@@@@@@@"
	       "@@@@@@@@@@ EUCLID @@@@@@@"
	       "@@@@@@@@@@@@@@@@@@@@@@@@@"
	       "@@@@@\n");
	printf("Hello, World!\n");

	/* For now let's just push a value to EAX (x86). */
	return (int)0xABCDEFCC;
}
