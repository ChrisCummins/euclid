/*
 * Common macros definitions
 *
 * This file must not include any other header files, as many will rely on it.
 */

#ifndef _MACROS_H
#define _MACROS_H

/* Helper macros */
#define __stringify(x)	#x
#define __concat(x, y)	__stringify(x ## y)

/*
 * Redefine the keywords disabled by -std option.
 *
 *   See: http://gcc.gnu.org/onlinedocs/gcc-4.3.4/gcc/Alternate-Keywords.html
 */
#ifdef __GNUC__
# define asm		__asm__
# define inline		__inline__
# define typeof		__typeof__
#endif

/* Branch prediction performance optimisations */
#if defined(__GNUC__) && (__GNUC__ > 2) && defined(__OPTIMIZE__)
# define likely(x)	__builtin_expect((x),1)
# define unlikely(x)	__builtin_expect((x),0)
#else
# define likely(x)	(x)
# define unlikely(x)	(x)
#endif

/* Protect against compiling without GCC */
#ifndef __GNUC__
# define __attribute__
#endif

/* Diagnostic pragmas.
 *
 * This provides the two macros __diagnostic_disable(x) and __diagnostic_enable
 * for disabling and enabling warnings, respectively. These should not be used
 * without good cause and care should be made to ensure that each disabling of a
 * warning is a matched with an enable for the same warning after use.
 *
 * Note that these cannot be used to disable errors. Compiler errors should be
 * resolved, not ignored.
 *
 * For more on diagnostic pragmas, see here:
 *     http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
 */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)
# define __do_pragma(x)			_Pragma (#x)
# define __diagnostic_pragma(x)		__do_pragma(GCC diagnostic x)
# if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#  define __diagnostic_disable(x)			\
	__diagnostic_pragma(push)			\
	__diagnostic_pragma(ignored __concat(-W,x))
#  define __diagnostic_enable(x)		\
	__diagnostic_pragma(pop)
# else /* 4.2 < GCC version > 4.2 */
#  define __diagnostic_disable(x)		\
	__diagnostic_pragma(ignored __concat(-W,x))
#  define __diagnostic_enable(x)		\
	__diagnostic_pragma(warning __concat(-W,x))
# endif
#else /* GCC version < 4.2, or undefined */
# define __do_pragma(x)
# define __diagnostic_disable(x)
# define __diagnostic_enable(x)
#endif

#endif /* _MACROS_H */
