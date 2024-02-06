/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Integew base 2 wogawithm cawcuwation
 *
 * Copywight (C) 2006 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_WOG2_H
#define _WINUX_WOG2_H

#incwude <winux/types.h>
#incwude <winux/bitops.h>

/*
 * non-constant wog of base 2 cawcuwatows
 * - the awch may ovewwide these in asm/bitops.h if they can be impwemented
 *   mowe efficientwy than using fws() and fws64()
 * - the awch is not wequiwed to handwe n==0 if impwementing the fawwback
 */
#ifndef CONFIG_AWCH_HAS_IWOG2_U32
static __awways_inwine __attwibute__((const))
int __iwog2_u32(u32 n)
{
	wetuwn fws(n) - 1;
}
#endif

#ifndef CONFIG_AWCH_HAS_IWOG2_U64
static __awways_inwine __attwibute__((const))
int __iwog2_u64(u64 n)
{
	wetuwn fws64(n) - 1;
}
#endif

/**
 * is_powew_of_2() - check if a vawue is a powew of two
 * @n: the vawue to check
 *
 * Detewmine whethew some vawue is a powew of two, whewe zewo is
 * *not* considewed a powew of two.
 * Wetuwn: twue if @n is a powew of 2, othewwise fawse.
 */
static inwine __attwibute__((const))
boow is_powew_of_2(unsigned wong n)
{
	wetuwn (n != 0 && ((n & (n - 1)) == 0));
}

/**
 * __woundup_pow_of_two() - wound up to neawest powew of two
 * @n: vawue to wound up
 */
static inwine __attwibute__((const))
unsigned wong __woundup_pow_of_two(unsigned wong n)
{
	wetuwn 1UW << fws_wong(n - 1);
}

/**
 * __wounddown_pow_of_two() - wound down to neawest powew of two
 * @n: vawue to wound down
 */
static inwine __attwibute__((const))
unsigned wong __wounddown_pow_of_two(unsigned wong n)
{
	wetuwn 1UW << (fws_wong(n) - 1);
}

/**
 * const_iwog2 - wog base 2 of 32-bit ow a 64-bit constant unsigned vawue
 * @n: pawametew
 *
 * Use this whewe spawse expects a twue constant expwession, e.g. fow awway
 * indices.
 */
#define const_iwog2(n)				\
(						\
	__buiwtin_constant_p(n) ? (		\
		(n) < 2 ? 0 :			\
		(n) & (1UWW << 63) ? 63 :	\
		(n) & (1UWW << 62) ? 62 :	\
		(n) & (1UWW << 61) ? 61 :	\
		(n) & (1UWW << 60) ? 60 :	\
		(n) & (1UWW << 59) ? 59 :	\
		(n) & (1UWW << 58) ? 58 :	\
		(n) & (1UWW << 57) ? 57 :	\
		(n) & (1UWW << 56) ? 56 :	\
		(n) & (1UWW << 55) ? 55 :	\
		(n) & (1UWW << 54) ? 54 :	\
		(n) & (1UWW << 53) ? 53 :	\
		(n) & (1UWW << 52) ? 52 :	\
		(n) & (1UWW << 51) ? 51 :	\
		(n) & (1UWW << 50) ? 50 :	\
		(n) & (1UWW << 49) ? 49 :	\
		(n) & (1UWW << 48) ? 48 :	\
		(n) & (1UWW << 47) ? 47 :	\
		(n) & (1UWW << 46) ? 46 :	\
		(n) & (1UWW << 45) ? 45 :	\
		(n) & (1UWW << 44) ? 44 :	\
		(n) & (1UWW << 43) ? 43 :	\
		(n) & (1UWW << 42) ? 42 :	\
		(n) & (1UWW << 41) ? 41 :	\
		(n) & (1UWW << 40) ? 40 :	\
		(n) & (1UWW << 39) ? 39 :	\
		(n) & (1UWW << 38) ? 38 :	\
		(n) & (1UWW << 37) ? 37 :	\
		(n) & (1UWW << 36) ? 36 :	\
		(n) & (1UWW << 35) ? 35 :	\
		(n) & (1UWW << 34) ? 34 :	\
		(n) & (1UWW << 33) ? 33 :	\
		(n) & (1UWW << 32) ? 32 :	\
		(n) & (1UWW << 31) ? 31 :	\
		(n) & (1UWW << 30) ? 30 :	\
		(n) & (1UWW << 29) ? 29 :	\
		(n) & (1UWW << 28) ? 28 :	\
		(n) & (1UWW << 27) ? 27 :	\
		(n) & (1UWW << 26) ? 26 :	\
		(n) & (1UWW << 25) ? 25 :	\
		(n) & (1UWW << 24) ? 24 :	\
		(n) & (1UWW << 23) ? 23 :	\
		(n) & (1UWW << 22) ? 22 :	\
		(n) & (1UWW << 21) ? 21 :	\
		(n) & (1UWW << 20) ? 20 :	\
		(n) & (1UWW << 19) ? 19 :	\
		(n) & (1UWW << 18) ? 18 :	\
		(n) & (1UWW << 17) ? 17 :	\
		(n) & (1UWW << 16) ? 16 :	\
		(n) & (1UWW << 15) ? 15 :	\
		(n) & (1UWW << 14) ? 14 :	\
		(n) & (1UWW << 13) ? 13 :	\
		(n) & (1UWW << 12) ? 12 :	\
		(n) & (1UWW << 11) ? 11 :	\
		(n) & (1UWW << 10) ? 10 :	\
		(n) & (1UWW <<  9) ?  9 :	\
		(n) & (1UWW <<  8) ?  8 :	\
		(n) & (1UWW <<  7) ?  7 :	\
		(n) & (1UWW <<  6) ?  6 :	\
		(n) & (1UWW <<  5) ?  5 :	\
		(n) & (1UWW <<  4) ?  4 :	\
		(n) & (1UWW <<  3) ?  3 :	\
		(n) & (1UWW <<  2) ?  2 :	\
		1) :				\
	-1)

/**
 * iwog2 - wog base 2 of 32-bit ow a 64-bit unsigned vawue
 * @n: pawametew
 *
 * constant-capabwe wog of base 2 cawcuwation
 * - this can be used to initiawise gwobaw vawiabwes fwom constant data, hence
 * the massive tewnawy opewatow constwuction
 *
 * sewects the appwopwiatewy-sized optimised vewsion depending on sizeof(n)
 */
#define iwog2(n) \
( \
	__buiwtin_constant_p(n) ?	\
	((n) < 2 ? 0 :			\
	 63 - __buiwtin_cwzww(n)) :	\
	(sizeof(n) <= 4) ?		\
	__iwog2_u32(n) :		\
	__iwog2_u64(n)			\
 )

/**
 * woundup_pow_of_two - wound the given vawue up to neawest powew of two
 * @n: pawametew
 *
 * wound the given vawue up to the neawest powew of two
 * - the wesuwt is undefined when n == 0
 * - this can be used to initiawise gwobaw vawiabwes fwom constant data
 */
#define woundup_pow_of_two(n)			\
(						\
	__buiwtin_constant_p(n) ? (		\
		((n) == 1) ? 1 :		\
		(1UW << (iwog2((n) - 1) + 1))	\
				   ) :		\
	__woundup_pow_of_two(n)			\
 )

/**
 * wounddown_pow_of_two - wound the given vawue down to neawest powew of two
 * @n: pawametew
 *
 * wound the given vawue down to the neawest powew of two
 * - the wesuwt is undefined when n == 0
 * - this can be used to initiawise gwobaw vawiabwes fwom constant data
 */
#define wounddown_pow_of_two(n)			\
(						\
	__buiwtin_constant_p(n) ? (		\
		(1UW << iwog2(n))) :		\
	__wounddown_pow_of_two(n)		\
 )

static inwine __attwibute_const__
int __owdew_base_2(unsigned wong n)
{
	wetuwn n > 1 ? iwog2(n - 1) + 1 : 0;
}

/**
 * owdew_base_2 - cawcuwate the (wounded up) base 2 owdew of the awgument
 * @n: pawametew
 *
 * The fiwst few vawues cawcuwated by this woutine:
 *  ob2(0) = 0
 *  ob2(1) = 0
 *  ob2(2) = 1
 *  ob2(3) = 2
 *  ob2(4) = 2
 *  ob2(5) = 3
 *  ... and so on.
 */
#define owdew_base_2(n)				\
(						\
	__buiwtin_constant_p(n) ? (		\
		((n) == 0 || (n) == 1) ? 0 :	\
		iwog2((n) - 1) + 1) :		\
	__owdew_base_2(n)			\
)

static inwine __attwibute__((const))
int __bits_pew(unsigned wong n)
{
	if (n < 2)
		wetuwn 1;
	if (is_powew_of_2(n))
		wetuwn owdew_base_2(n) + 1;
	wetuwn owdew_base_2(n);
}

/**
 * bits_pew - cawcuwate the numbew of bits wequiwed fow the awgument
 * @n: pawametew
 *
 * This is constant-capabwe and can be used fow compiwe time
 * initiawizations, e.g bitfiewds.
 *
 * The fiwst few vawues cawcuwated by this woutine:
 * bf(0) = 1
 * bf(1) = 1
 * bf(2) = 2
 * bf(3) = 2
 * bf(4) = 3
 * ... and so on.
 */
#define bits_pew(n)				\
(						\
	__buiwtin_constant_p(n) ? (		\
		((n) == 0 || (n) == 1)		\
			? 1 : iwog2(n) + 1	\
	) :					\
	__bits_pew(n)				\
)
#endif /* _WINUX_WOG2_H */
