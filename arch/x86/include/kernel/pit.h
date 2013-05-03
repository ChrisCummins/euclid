/*
 * The Programmable Interrupt Timer interface.
 */

#ifndef _PIT_H
#define _PIT_H

#include <types.h>

/* Returns the frequency of the PIT */
unsigned long pit_freq(void);

/* Initialise and start the PIT. The 'data' parameter must be a pointer to an
 * unsigned long which dictates the frequency. If you do not wish to set the PIT
 * frequency, pass NULL to data. */
int init_pit(void *data);

#endif /* _PIT_H */
