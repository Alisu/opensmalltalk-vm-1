/*
 * Informative assert definitions that print expression and line number.
 *
 * assert's expression is evaluated only if NDEBUG is not defined and printed
 * along with its the line number if it is false.
 *
 * asserta's expression is always evaluated but only printed if it is false and
 * NDEBUG is not defined. (asserta => assert always)
 *
 * assertf's message is printed along with its line number if NDEBUG is not
 * defined. (assertf => assert fail)
 *
 * assertl, assertal & assertfl take a line number as an argument.
 */

#include "debug.h"

#ifdef NDEBUG /* compatible with Mac OS X (FreeBSD) /usr/include/assert.h */
# define assert(expr, self) 0 /* hack disabling of asserts.  Better in makefile? */
# define asserta(expr, self) (expr)
# define assertf(msg, self) 0
# define assertl(expr,line, self) 0
# define assertal(expr,line, self) (expr)
# define assertfl(msg,line, self) 0
# define eassert(expr, self) 0 /* hack disabling of asserts.  Better in makefile? */
# define PRODUCTION 1

#else

# define assert(expr)  ((expr)||(logAssert(__FILENAME__, __FUNCTION__, __LINE__, #expr),0))
# define asserta(expr) assert(expr)
# define assertf(msg)  (logAssert(__FILENAME__, __FUNCTION__, __LINE__, #msg),0)
# define assertl(expr,line)  ((expr)||(logAssert(__FILENAME__, __FUNCTION__, line, #expr),0))
# define assertal(expr,line) assertl(expr,line)
# define assertfl(msg,line)  (logAssert(__FILENAME__, __FUNCTION__, line, #msg),0)

extern char expensiveAsserts;

# define eassert(expr)  (!expensiveAsserts||assert(expr))
# define PRODUCTION 0
#endif
