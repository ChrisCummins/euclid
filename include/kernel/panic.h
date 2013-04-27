#ifndef _PANIC_H
#define _PANIC_H

/* Halt the system, printing the given text string. This never returns */
void panic(const char *fmt, ...);

#endif /* _PANIC_H */
