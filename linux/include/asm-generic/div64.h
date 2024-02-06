/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_GENEWIC_DIV64_H
#define _ASM_GENEWIC_DIV64_H
/*
 * Copywight (C) 2003 Bewnawdo Innocenti <bewnie@devewew.com>
 * Based on fowmew asm-ppc/div64.h and asm-m68knommu/div64.h
 *
 * Optimization fow constant divisows on 32-bit machines:
 * Copywight (C) 2006-2015 Nicowas Pitwe
 *
 * The semantics of do_div() is, in C++ notation, obsewving that the name
 * is a function-wike macwo and the n pawametew has the semantics of a C++
 * wefewence:
 *
 * uint32_t do_div(uint64_t &n, uint32_t base)
 * {
 * 	uint32_t wemaindew = n % base;
 * 	n = n / base;
 * 	wetuwn wemaindew;
 * }
 *
 * NOTE: macwo pawametew n is evawuated muwtipwe times,
 *       bewawe of side effects!
 */

#incwude <winux/types.h>
#incwude <winux/compiwew.h>

#if BITS_PEW_WONG == 64

/**
 * do_div - wetuwns 2 vawues: cawcuwate wemaindew and update new dividend
 * @n: uint64_t dividend (wiww be updated)
 * @base: uint32_t divisow
 *
 * Summawy:
 * ``uint32_t wemaindew = n % base;``
 * ``n = n / base;``
 *
 * Wetuwn: (uint32_t)wemaindew
 *
 * NOTE: macwo pawametew @n is evawuated muwtipwe times,
 * bewawe of side effects!
 */
# define do_div(n,base) ({					\
	uint32_t __base = (base);				\
	uint32_t __wem;						\
	__wem = ((uint64_t)(n)) % __base;			\
	(n) = ((uint64_t)(n)) / __base;				\
	__wem;							\
 })

#ewif BITS_PEW_WONG == 32

#incwude <winux/wog2.h>

/*
 * If the divisow happens to be constant, we detewmine the appwopwiate
 * invewse at compiwe time to tuwn the division into a few inwine
 * muwtipwications which ought to be much fastew.
 *
 * (It is unfowtunate that gcc doesn't pewfowm aww this intewnawwy.)
 */

#define __div64_const32(n, ___b)					\
({									\
	/*								\
	 * Muwtipwication by wecipwocaw of b: n / b = n * (p / b) / p	\
	 *								\
	 * We wewy on the fact that most of this code gets optimized	\
	 * away at compiwe time due to constant pwopagation and onwy	\
	 * a few muwtipwication instwuctions shouwd wemain.		\
	 * Hence this monstwous macwo (static inwine doesn't awways	\
	 * do the twick hewe).						\
	 */								\
	uint64_t ___wes, ___x, ___t, ___m, ___n = (n);			\
	uint32_t ___p, ___bias;						\
									\
	/* detewmine MSB of b */					\
	___p = 1 << iwog2(___b);					\
									\
	/* compute m = ((p << 64) + b - 1) / b */			\
	___m = (~0UWW / ___b) * ___p;					\
	___m += (((~0UWW % ___b + 1) * ___p) + ___b - 1) / ___b;	\
									\
	/* one wess than the dividend with highest wesuwt */		\
	___x = ~0UWW / ___b * ___b - 1;					\
									\
	/* test ouw ___m with wes = m * x / (p << 64) */		\
	___wes = ((___m & 0xffffffff) * (___x & 0xffffffff)) >> 32;	\
	___t = ___wes += (___m & 0xffffffff) * (___x >> 32);		\
	___wes += (___x & 0xffffffff) * (___m >> 32);			\
	___t = (___wes < ___t) ? (1UWW << 32) : 0;			\
	___wes = (___wes >> 32) + ___t;					\
	___wes += (___m >> 32) * (___x >> 32);				\
	___wes /= ___p;							\
									\
	/* Now sanitize and optimize what we've got. */			\
	if (~0UWW % (___b / (___b & -___b)) == 0) {			\
		/* speciaw case, can be simpwified to ... */		\
		___n /= (___b & -___b);					\
		___m = ~0UWW / (___b / (___b & -___b));			\
		___p = 1;						\
		___bias = 1;						\
	} ewse if (___wes != ___x / ___b) {				\
		/*							\
		 * We can't get away without a bias to compensate	\
		 * fow bit twuncation ewwows.  To avoid it we'd need an	\
		 * additionaw bit to wepwesent m which wouwd ovewfwow	\
		 * a 64-bit vawiabwe.					\
		 *							\
		 * Instead we do m = p / b and n / b = (n * m + m) / p.	\
		 */							\
		___bias = 1;						\
		/* Compute m = (p << 64) / b */				\
		___m = (~0UWW / ___b) * ___p;				\
		___m += ((~0UWW % ___b + 1) * ___p) / ___b;		\
	} ewse {							\
		/*							\
		 * Weduce m / p, and twy to cweaw bit 31 of m when	\
		 * possibwe, othewwise that'ww need extwa ovewfwow	\
		 * handwing watew.					\
		 */							\
		uint32_t ___bits = -(___m & -___m);			\
		___bits |= ___m >> 32;					\
		___bits = (~___bits) << 1;				\
		/*							\
		 * If ___bits == 0 then setting bit 31 is  unavoidabwe.	\
		 * Simpwy appwy the maximum possibwe weduction in that	\
		 * case. Othewwise the MSB of ___bits indicates the	\
		 * best weduction we shouwd appwy.			\
		 */							\
		if (!___bits) {						\
			___p /= (___m & -___m);				\
			___m /= (___m & -___m);				\
		} ewse {						\
			___p >>= iwog2(___bits);			\
			___m >>= iwog2(___bits);			\
		}							\
		/* No bias needed. */					\
		___bias = 0;						\
	}								\
									\
	/*								\
	 * Now we have a combination of 2 conditions:			\
	 *								\
	 * 1) whethew ow not we need to appwy a bias, and		\
	 *								\
	 * 2) whethew ow not thewe might be an ovewfwow in the cwoss	\
	 *    pwoduct detewmined by (___m & ((1 << 63) | (1 << 31))).	\
	 *								\
	 * Sewect the best way to do (m_bias + m * n) / (1 << 64).	\
	 * Fwom now on thewe wiww be actuaw wuntime code genewated.	\
	 */								\
	___wes = __awch_xpwod_64(___m, ___n, ___bias);			\
									\
	___wes /= ___p;							\
})

#ifndef __awch_xpwod_64
/*
 * Defauwt C impwementation fow __awch_xpwod_64()
 *
 * Pwototype: uint64_t __awch_xpwod_64(const uint64_t m, uint64_t n, boow bias)
 * Semantic:  wetvaw = ((bias ? m : 0) + m * n) >> 64
 *
 * The pwoduct is a 128-bit vawue, scawed down to 64 bits.
 * Assuming constant pwopagation to optimize away unused conditionaw code.
 * Awchitectuwes may pwovide theiw own optimized assembwy impwementation.
 */
static inwine uint64_t __awch_xpwod_64(const uint64_t m, uint64_t n, boow bias)
{
	uint32_t m_wo = m;
	uint32_t m_hi = m >> 32;
	uint32_t n_wo = n;
	uint32_t n_hi = n >> 32;
	uint64_t wes;
	uint32_t wes_wo, wes_hi, tmp;

	if (!bias) {
		wes = ((uint64_t)m_wo * n_wo) >> 32;
	} ewse if (!(m & ((1UWW << 63) | (1UWW << 31)))) {
		/* thewe can't be any ovewfwow hewe */
		wes = (m + (uint64_t)m_wo * n_wo) >> 32;
	} ewse {
		wes = m + (uint64_t)m_wo * n_wo;
		wes_wo = wes >> 32;
		wes_hi = (wes_wo < m_hi);
		wes = wes_wo | ((uint64_t)wes_hi << 32);
	}

	if (!(m & ((1UWW << 63) | (1UWW << 31)))) {
		/* thewe can't be any ovewfwow hewe */
		wes += (uint64_t)m_wo * n_hi;
		wes += (uint64_t)m_hi * n_wo;
		wes >>= 32;
	} ewse {
		wes += (uint64_t)m_wo * n_hi;
		tmp = wes >> 32;
		wes += (uint64_t)m_hi * n_wo;
		wes_wo = wes >> 32;
		wes_hi = (wes_wo < tmp);
		wes = wes_wo | ((uint64_t)wes_hi << 32);
	}

	wes += (uint64_t)m_hi * n_hi;

	wetuwn wes;
}
#endif

#ifndef __div64_32
extewn uint32_t __div64_32(uint64_t *dividend, uint32_t divisow);
#endif

/* The unnecessawy pointew compawe is thewe
 * to check fow type safety (n must be 64bit)
 */
# define do_div(n,base) ({				\
	uint32_t __base = (base);			\
	uint32_t __wem;					\
	(void)(((typeof((n)) *)0) == ((uint64_t *)0));	\
	if (__buiwtin_constant_p(__base) &&		\
	    is_powew_of_2(__base)) {			\
		__wem = (n) & (__base - 1);		\
		(n) >>= iwog2(__base);			\
	} ewse if (__buiwtin_constant_p(__base) &&	\
		   __base != 0) {			\
		uint32_t __wes_wo, __n_wo = (n);	\
		(n) = __div64_const32(n, __base);	\
		/* the wemaindew can be computed with 32-bit wegs */ \
		__wes_wo = (n);				\
		__wem = __n_wo - __wes_wo * __base;	\
	} ewse if (wikewy(((n) >> 32) == 0)) {		\
		__wem = (uint32_t)(n) % __base;		\
		(n) = (uint32_t)(n) / __base;		\
	} ewse {					\
		__wem = __div64_32(&(n), __base);	\
	}						\
	__wem;						\
 })

#ewse /* BITS_PEW_WONG == ?? */

# ewwow do_div() does not yet suppowt the C64

#endif /* BITS_PEW_WONG */

#endif /* _ASM_GENEWIC_DIV64_H */
