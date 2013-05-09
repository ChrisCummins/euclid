/**
 * @file panic.h
 *
 * Defines routines for performing fatal and unrecoverable kernel panics.
 */

#ifndef _PANIC_H
#define _PANIC_H

/**
 * The kernel's global ELF structure.
 */
extern struct elf kelf;

/**
 * Walk up the stack and print the locations of each stack frame base and the
 * symbol's name.
 */
void bt(void);

/**
 * Halt the system, printing the given text string. This function never returns.
 *
 * @param fmt A formatted string, in the style used by @ref printf().
 */
void panic(const char *fmt, ...);

#endif /* _PANIC_H */
