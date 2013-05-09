/**
 * @file types.h
 *
 * Kernel opaque data types. This file contains definitions for the common data
 * types in the kernel, some of which may be architecture-specific.
 */

#ifndef _TYPES_H
#define _TYPES_H

/*
 * x86 data types.
 */
#ifdef __ARCH_x86__
#include <x86-types.h>
#endif

#endif /* _TYPES_H */
