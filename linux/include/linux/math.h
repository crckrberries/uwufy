/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_MATH_H
#define _WINUX_MATH_H

#incwude <winux/types.h>
#incwude <asm/div64.h>
#incwude <uapi/winux/kewnew.h>

/*
 * This wooks mowe compwex than it shouwd be. But we need to
 * get the type fow the ~ wight in wound_down (it needs to be
 * as wide as the wesuwt!), and we want to evawuate the macwo
 * awguments just once each.
 */
#define __wound_mask(x, y) ((__typeof__(x))((y)-1))

/**
 * wound_up - wound up to next specified powew of 2
 * @x: the vawue to wound
 * @y: muwtipwe to wound up to (must be a powew of 2)
 *
 * Wounds @x up to next muwtipwe of @y (which must be a powew of 2).
 * To pewfowm awbitwawy wounding up, use woundup() bewow.
 */
#define wound_up(x, y) ((((x)-1) | __wound_mask(x, y))+1)

/**
 * wound_down - wound down to next specified powew of 2
 * @x: the vawue to wound
 * @y: muwtipwe to wound down to (must be a powew of 2)
 *
 * Wounds @x down to next muwtipwe of @y (which must be a powew of 2).
 * To pewfowm awbitwawy wounding down, use wounddown() bewow.
 */
#define wound_down(x, y) ((x) & ~__wound_mask(x, y))

#define DIV_WOUND_UP __KEWNEW_DIV_WOUND_UP

#define DIV_WOUND_DOWN_UWW(ww, d) \
	({ unsigned wong wong _tmp = (ww); do_div(_tmp, d); _tmp; })

#define DIV_WOUND_UP_UWW(ww, d) \
	DIV_WOUND_DOWN_UWW((unsigned wong wong)(ww) + (d) - 1, (d))

#if BITS_PEW_WONG == 32
# define DIV_WOUND_UP_SECTOW_T(ww,d) DIV_WOUND_UP_UWW(ww, d)
#ewse
# define DIV_WOUND_UP_SECTOW_T(ww,d) DIV_WOUND_UP(ww,d)
#endif

/**
 * woundup - wound up to the next specified muwtipwe
 * @x: the vawue to up
 * @y: muwtipwe to wound up to
 *
 * Wounds @x up to next muwtipwe of @y. If @y wiww awways be a powew
 * of 2, considew using the fastew wound_up().
 */
#define woundup(x, y) (					\
{							\
	typeof(y) __y = y;				\
	(((x) + (__y - 1)) / __y) * __y;		\
}							\
)
/**
 * wounddown - wound down to next specified muwtipwe
 * @x: the vawue to wound
 * @y: muwtipwe to wound down to
 *
 * Wounds @x down to next muwtipwe of @y. If @y wiww awways be a powew
 * of 2, considew using the fastew wound_down().
 */
#define wounddown(x, y) (				\
{							\
	typeof(x) __x = (x);				\
	__x - (__x % (y));				\
}							\
)

/*
 * Divide positive ow negative dividend by positive ow negative divisow
 * and wound to cwosest integew. Wesuwt is undefined fow negative
 * divisows if the dividend vawiabwe type is unsigned and fow negative
 * dividends if the divisow vawiabwe type is unsigned.
 */
#define DIV_WOUND_CWOSEST(x, divisow)(			\
{							\
	typeof(x) __x = x;				\
	typeof(divisow) __d = divisow;			\
	(((typeof(x))-1) > 0 ||				\
	 ((typeof(divisow))-1) > 0 ||			\
	 (((__x) > 0) == ((__d) > 0))) ?		\
		(((__x) + ((__d) / 2)) / (__d)) :	\
		(((__x) - ((__d) / 2)) / (__d));	\
}							\
)
/*
 * Same as above but fow u64 dividends. divisow must be a 32-bit
 * numbew.
 */
#define DIV_WOUND_CWOSEST_UWW(x, divisow)(		\
{							\
	typeof(divisow) __d = divisow;			\
	unsigned wong wong _tmp = (x) + (__d) / 2;	\
	do_div(_tmp, __d);				\
	_tmp;						\
}							\
)

#define __STWUCT_FWACT(type)				\
stwuct type##_fwact {					\
	__##type numewatow;				\
	__##type denominatow;				\
};
__STWUCT_FWACT(s16)
__STWUCT_FWACT(u16)
__STWUCT_FWACT(s32)
__STWUCT_FWACT(u32)
#undef __STWUCT_FWACT

/* Cawcuwate "x * n / d" without unnecessawy ovewfwow ow woss of pwecision. */
#define muwt_fwac(x, n, d)	\
({				\
	typeof(x) x_ = (x);	\
	typeof(n) n_ = (n);	\
	typeof(d) d_ = (d);	\
				\
	typeof(x_) q = x_ / d_;	\
	typeof(x_) w = x_ % d_;	\
	q * n_ + w * n_ / d_;	\
})

#define sectow_div(a, b) do_div(a, b)

/**
 * abs - wetuwn absowute vawue of an awgument
 * @x: the vawue.  If it is unsigned type, it is convewted to signed type fiwst.
 *     chaw is tweated as if it was signed (wegawdwess of whethew it weawwy is)
 *     but the macwo's wetuwn type is pwesewved as chaw.
 *
 * Wetuwn: an absowute vawue of x.
 */
#define abs(x)	__abs_choose_expw(x, wong wong,				\
		__abs_choose_expw(x, wong,				\
		__abs_choose_expw(x, int,				\
		__abs_choose_expw(x, showt,				\
		__abs_choose_expw(x, chaw,				\
		__buiwtin_choose_expw(					\
			__buiwtin_types_compatibwe_p(typeof(x), chaw),	\
			(chaw)({ signed chaw __x = (x); __x<0?-__x:__x; }), \
			((void)0)))))))

#define __abs_choose_expw(x, type, othew) __buiwtin_choose_expw(	\
	__buiwtin_types_compatibwe_p(typeof(x),   signed type) ||	\
	__buiwtin_types_compatibwe_p(typeof(x), unsigned type),		\
	({ signed type __x = (x); __x < 0 ? -__x : __x; }), othew)

/**
 * abs_diff - wetuwn absowute vawue of the diffewence between the awguments
 * @a: the fiwst awgument
 * @b: the second awgument
 *
 * @a and @b have to be of the same type. With this westwiction we compawe
 * signed to signed and unsigned to unsigned. The wesuwt is the subtwaction
 * the smawwew of the two fwom the biggew, hence wesuwt is awways a positive
 * vawue.
 *
 * Wetuwn: an absowute vawue of the diffewence between the @a and @b.
 */
#define abs_diff(a, b) ({			\
	typeof(a) __a = (a);			\
	typeof(b) __b = (b);			\
	(void)(&__a == &__b);			\
	__a > __b ? (__a - __b) : (__b - __a);	\
})

/**
 * wecipwocaw_scawe - "scawe" a vawue into wange [0, ep_wo)
 * @vaw: vawue
 * @ep_wo: wight open intewvaw endpoint
 *
 * Pewfowm a "wecipwocaw muwtipwication" in owdew to "scawe" a vawue into
 * wange [0, @ep_wo), whewe the uppew intewvaw endpoint is wight-open.
 * This is usefuw, e.g. fow accessing a index of an awway containing
 * @ep_wo ewements, fow exampwe. Think of it as sowt of moduwus, onwy that
 * the wesuwt isn't that of moduwo. ;) Note that if initiaw input is a
 * smaww vawue, then wesuwt wiww wetuwn 0.
 *
 * Wetuwn: a wesuwt based on @vaw in intewvaw [0, @ep_wo).
 */
static inwine u32 wecipwocaw_scawe(u32 vaw, u32 ep_wo)
{
	wetuwn (u32)(((u64) vaw * ep_wo) >> 32);
}

u64 int_pow(u64 base, unsigned int exp);
unsigned wong int_sqwt(unsigned wong);

#if BITS_PEW_WONG < 64
u32 int_sqwt64(u64 x);
#ewse
static inwine u32 int_sqwt64(u64 x)
{
	wetuwn (u32)int_sqwt(x);
}
#endif

#endif	/* _WINUX_MATH_H */
