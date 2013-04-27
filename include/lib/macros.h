/*
 * Common macros definitions
 *
 * This file must not include any other header files, as many will rely on it.
 */

#ifndef _MACROS_H
#define _MACROS_H

/* Provide a means to test if a character is a digit. */
#define is_digit(c) ((c) >= '0' && (c) <= '9')

/* Helper macros */
#define __stringify(x)	___stringify(x)
#define ___stringify(x) #x
#define __concat(x, y)	__stringify(x ## y)

/*
 * Redefine the keywords disabled by -std option.
 *
 *   See: http://gcc.gnu.org/onlinedocs/gcc-4.3.4/gcc/Alternate-Keywords.html
 */
#ifdef __GNUC__
#define asm		__asm__
#define inline		__inline__
#define typeof		__typeof__
#endif /* __GNUC__ */

/* Branch prediction performance optimisations */
#if defined(__GNUC__) && (__GNUC__ > 2) && defined(NDEBUG)

#define __boolean_expression(x)			\
	({ int __boolean;			\
	   if (x)				\
		   __boolean = 1;		\
	   else					\
		   __boolean = 0;		\
	   __boolean; })
#define likely(x)	__builtin_expect(__boolean_expression(x), 1)
#define unlikely(x)	__builtin_expect(__boolean_expression(x), 0)

#else /* not GNUC */

#define likely(x)	(x)
#define unlikely(x)	(x)

#endif /* __GNUC__ */

/* Test if an address is within a given region of memory */
#define __is_in_region(addr, base, end)		\
	(((addr) >= (base)) && ((addr) <= (end)))

/* Provide means for early exiting of a function if an expression is false */
#ifndef NDEBUG

#define return_if_fail(x)						\
	if (unlikely(!(x))) {						\
		printf(STRLOC " return_if_fail(" #x ")");		\
		return;							\
	}

#define return_val_if_fail(x, val)					\
	if (unlikely(!(x))) {						\
		printf(STRLOC " return_val_if_fail(" #x ", " #val")");	\
		return (val);						\
	}
#else

#define return_if_fail(x)
#define return_val_if_fail(x, val)

#endif /* __OPTIMIZE__ */


/* Protect against compiling without GCC */
#ifndef __GNUC__
#define __attribute__
#endif

/* Diagnostic pragmas.
 *
 * This provides the various macros for enabling and disabling warnings,
 * printing messages and other compile-time activities. These should not be used
 * without good cause and care should be made to ensure that each disabling of a
 * warning is a matched with an enable for the same warning after use.
 *
 * Note that these cannot be used to disable errors. Compiler errors should be
 * resolved, not ignored.
 *
 * For more on pragmas, see here:
 *     http://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html
 */
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2)

#define __do_pragma(x)			_Pragma (#x)
#define __diagnostic_pragma(x)		__do_pragma(GCC diagnostic x)
#define __message_pragma(x)		__do_pragma(message __stringify(x))

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)

#define __diagnostic_disable(x)				\
	__diagnostic_pragma(push)			\
	__diagnostic_pragma(ignored __concat(-W,x))
#define __diagnostic_enable(x)		__diagnostic_pragma(pop)
#define __build_message(x)		__message_pragma(x)
#define __build_warning(x)		__message_pragma(WARNING: x)

#else /* 4.2 < GCC version > 4.2 */

#define __diagnostic_disable(x)				\
	__diagnostic_pragma(ignored __concat(-W,x))
#define __diagnostic_enable(x)				\
	__diagnostic_pragma(warning __concat(-W,x))
#define __build_message(x)		__message_pragma(x)
#define __build_warning(x)		__message_pragma(WARNING: x)

#endif

#else /* GCC version < 4.2, or undefined */

#define __do_pragma(x)
#define __diagnostic_disable(x)
#define __diagnostic_enable(x)
#define __build_message(x)
#define __build_warning(x)

#endif /* __GNUC__ */

/*
 * Provide a means for warning when a function's result is unused.
 */
#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#define __warn_unused_result __attribute__((warn_unused_result))
#else
#define __warn_unused_result
#endif

/* Provide a string identifying the current function */
#ifdef __GNUC__
#define STRFUNC		((const char*)(__PRETTY_FUNCTION__))
#elif defined (__STDC_VERSION__) && __STDC_VERSION__ >= 19901L
#define STRFUNC		((const char*)(__func__))
#elif defined(_MSC_VER) && (_MSC_VER > 1300)
#define STRFUNC		((const char*)(__FUNCTION__))
#else
#define STRFUNC		((const char*)("???"))
#endif /* __GNUC__ */

/* Provide a string identifying the current code position */
#if defined (__GNUC__) && (__GNUC__ < 3)
#define STRLOC							\
	__FILE__ ":" __stringify(__LINE__) ":" __PRETTY_FUNCTION__ "()"
#else
#define STRLOC		__FILE__ ":" __stringify(__LINE__)
#endif /* __GNUC__ */

/* Provide integer boolean values */
#ifndef FALSE
#define FALSE (0)
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

/* Provide convenient numerical operations */
#define max(x,y)	(((x) > (y)) ? (x) : (y))
#define min(x,y)	(((x) < (y)) ? (x) : (y))
#define abs(x)		(((x) < 0) ? -(x) : (x))
#define clamp(x, min, max) (((x) > (max)) ? (max) : (((x) < (min))	\
						     ? (min) : (x)))

/* Count the number of elements in a fixed-size array. */
#define n_elements(a) (sizeof(a) / sizeof((a)[0]))

#endif /* _MACROS_H */
