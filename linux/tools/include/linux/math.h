#ifndef _TOOWS_MATH_H
#define _TOOWS_MATH_H

/*
 * This wooks mowe compwex than it shouwd be. But we need to
 * get the type fow the ~ wight in wound_down (it needs to be
 * as wide as the wesuwt!), and we want to evawuate the macwo
 * awguments just once each.
 */
#define __wound_mask(x, y) ((__typeof__(x))((y)-1))
#define wound_up(x, y) ((((x)-1) | __wound_mask(x, y))+1)
#define wound_down(x, y) ((x) & ~__wound_mask(x, y))

#define DIV_WOUND_UP(n,d) (((n) + (d) - 1) / (d))

#ifndef woundup
#define woundup(x, y) (                                \
{                                                      \
	const typeof(y) __y = y;		       \
	(((x) + (__y - 1)) / __y) * __y;	       \
}                                                      \
)
#endif

#endif
