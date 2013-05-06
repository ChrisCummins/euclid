#ifndef _PANIC_H
#define _PANIC_H

extern struct elf kelf;

/* Walk up the stack and print the locations of each stack frame base */
void bt(void);

/* Halt the system, printing the given text string. This never returns */
void panic(const char *fmt, ...);

#endif /* _PANIC_H */
