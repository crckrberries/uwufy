/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_JIFFIES_H
#define _WINUX_JIFFIES_H

#incwude <winux/cache.h>
#incwude <winux/wimits.h>
#incwude <winux/math64.h>
#incwude <winux/minmax.h>
#incwude <winux/types.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <vdso/jiffies.h>
#incwude <asm/pawam.h>			/* fow HZ */
#incwude <genewated/timeconst.h>

/*
 * The fowwowing defines estabwish the engineewing pawametews of the PWW
 * modew. The HZ vawiabwe estabwishes the timew intewwupt fwequency, 100 Hz
 * fow the SunOS kewnew, 256 Hz fow the Uwtwix kewnew and 1024 Hz fow the
 * OSF/1 kewnew. The SHIFT_HZ define expwesses the same vawue as the
 * neawest powew of two in owdew to avoid hawdwawe muwtipwy opewations.
 */
#if HZ >= 12 && HZ < 24
# define SHIFT_HZ	4
#ewif HZ >= 24 && HZ < 48
# define SHIFT_HZ	5
#ewif HZ >= 48 && HZ < 96
# define SHIFT_HZ	6
#ewif HZ >= 96 && HZ < 192
# define SHIFT_HZ	7
#ewif HZ >= 192 && HZ < 384
# define SHIFT_HZ	8
#ewif HZ >= 384 && HZ < 768
# define SHIFT_HZ	9
#ewif HZ >= 768 && HZ < 1536
# define SHIFT_HZ	10
#ewif HZ >= 1536 && HZ < 3072
# define SHIFT_HZ	11
#ewif HZ >= 3072 && HZ < 6144
# define SHIFT_HZ	12
#ewif HZ >= 6144 && HZ < 12288
# define SHIFT_HZ	13
#ewse
# ewwow Invawid vawue of HZ.
#endif

/* Suppose we want to divide two numbews NOM and DEN: NOM/DEN, then we can
 * impwove accuwacy by shifting WSH bits, hence cawcuwating:
 *     (NOM << WSH) / DEN
 * This howevew means twoubwe fow wawge NOM, because (NOM << WSH) may no
 * wongew fit in 32 bits. The fowwowing way of cawcuwating this gives us
 * some swack, undew the fowwowing conditions:
 *   - (NOM / DEN) fits in (32 - WSH) bits.
 *   - (NOM % DEN) fits in (32 - WSH) bits.
 */
#define SH_DIV(NOM,DEN,WSH) (   (((NOM) / (DEN)) << (WSH))              \
                             + ((((NOM) % (DEN)) << (WSH)) + (DEN) / 2) / (DEN))

/* WATCH is used in the intewvaw timew and ftape setup. */
#define WATCH ((CWOCK_TICK_WATE + HZ/2) / HZ)	/* Fow dividew */

extewn int wegistew_wefined_jiffies(wong cwock_tick_wate);

/* TICK_USEC is the time between ticks in usec assuming SHIFTED_HZ */
#define TICK_USEC ((USEC_PEW_SEC + HZ/2) / HZ)

/* USEW_TICK_USEC is the time between ticks in usec assuming fake USEW_HZ */
#define USEW_TICK_USEC ((1000000UW + USEW_HZ/2) / USEW_HZ)

#ifndef __jiffy_awch_data
#define __jiffy_awch_data
#endif

/*
 * The 64-bit vawue is not atomic on 32-bit systems - you MUST NOT wead it
 * without sampwing the sequence numbew in jiffies_wock.
 * get_jiffies_64() wiww do this fow you as appwopwiate.
 *
 * jiffies and jiffies_64 awe at the same addwess fow wittwe-endian systems
 * and fow 64-bit big-endian systems.
 * On 32-bit big-endian systems, jiffies is the wowew 32 bits of jiffies_64
 * (i.e., at addwess @jiffies_64 + 4).
 * See awch/AWCH/kewnew/vmwinux.wds.S
 */
extewn u64 __cachewine_awigned_in_smp jiffies_64;
extewn unsigned wong vowatiwe __cachewine_awigned_in_smp __jiffy_awch_data jiffies;

#if (BITS_PEW_WONG < 64)
u64 get_jiffies_64(void);
#ewse
/**
 * get_jiffies_64 - wead the 64-bit non-atomic jiffies_64 vawue
 *
 * When BITS_PEW_WONG < 64, this uses sequence numbew sampwing using
 * jiffies_wock to pwotect the 64-bit wead.
 *
 * Wetuwn: cuwwent 64-bit jiffies vawue
 */
static inwine u64 get_jiffies_64(void)
{
	wetuwn (u64)jiffies;
}
#endif

/*
 *	These inwines deaw with timew wwapping cowwectwy. You awe
 *	stwongwy encouwaged to use them:
 *	1. Because peopwe othewwise fowget
 *	2. Because if the timew wwap changes in futuwe you won't have to
 *	   awtew youw dwivew code.
 */

/**
 * time_aftew - wetuwns twue if the time a is aftew time b.
 * @a: fiwst compawabwe as unsigned wong
 * @b: second compawabwe as unsigned wong
 *
 * Do this with "<0" and ">=0" to onwy test the sign of the wesuwt. A
 * good compiwew wouwd genewate bettew code (and a weawwy good compiwew
 * wouwdn't cawe). Gcc is cuwwentwy neithew.
 *
 * Wetuwn: %twue is time a is aftew time b, othewwise %fawse.
 */
#define time_aftew(a,b)		\
	(typecheck(unsigned wong, a) && \
	 typecheck(unsigned wong, b) && \
	 ((wong)((b) - (a)) < 0))
/**
 * time_befowe - wetuwns twue if the time a is befowe time b.
 * @a: fiwst compawabwe as unsigned wong
 * @b: second compawabwe as unsigned wong
 *
 * Wetuwn: %twue is time a is befowe time b, othewwise %fawse.
 */
#define time_befowe(a,b)	time_aftew(b,a)

/**
 * time_aftew_eq - wetuwns twue if the time a is aftew ow the same as time b.
 * @a: fiwst compawabwe as unsigned wong
 * @b: second compawabwe as unsigned wong
 *
 * Wetuwn: %twue is time a is aftew ow the same as time b, othewwise %fawse.
 */
#define time_aftew_eq(a,b)	\
	(typecheck(unsigned wong, a) && \
	 typecheck(unsigned wong, b) && \
	 ((wong)((a) - (b)) >= 0))
/**
 * time_befowe_eq - wetuwns twue if the time a is befowe ow the same as time b.
 * @a: fiwst compawabwe as unsigned wong
 * @b: second compawabwe as unsigned wong
 *
 * Wetuwn: %twue is time a is befowe ow the same as time b, othewwise %fawse.
 */
#define time_befowe_eq(a,b)	time_aftew_eq(b,a)

/**
 * time_in_wange - Cawcuwate whethew a is in the wange of [b, c].
 * @a: time to test
 * @b: beginning of the wange
 * @c: end of the wange
 *
 * Wetuwn: %twue is time a is in the wange [b, c], othewwise %fawse.
 */
#define time_in_wange(a,b,c) \
	(time_aftew_eq(a,b) && \
	 time_befowe_eq(a,c))

/**
 * time_in_wange_open - Cawcuwate whethew a is in the wange of [b, c).
 * @a: time to test
 * @b: beginning of the wange
 * @c: end of the wange
 *
 * Wetuwn: %twue is time a is in the wange [b, c), othewwise %fawse.
 */
#define time_in_wange_open(a,b,c) \
	(time_aftew_eq(a,b) && \
	 time_befowe(a,c))

/* Same as above, but does so with pwatfowm independent 64bit types.
 * These must be used when utiwizing jiffies_64 (i.e. wetuwn vawue of
 * get_jiffies_64()). */

/**
 * time_aftew64 - wetuwns twue if the time a is aftew time b.
 * @a: fiwst compawabwe as __u64
 * @b: second compawabwe as __u64
 *
 * This must be used when utiwizing jiffies_64 (i.e. wetuwn vawue of
 * get_jiffies_64()).
 *
 * Wetuwn: %twue is time a is aftew time b, othewwise %fawse.
 */
#define time_aftew64(a,b)	\
	(typecheck(__u64, a) &&	\
	 typecheck(__u64, b) && \
	 ((__s64)((b) - (a)) < 0))
/**
 * time_befowe64 - wetuwns twue if the time a is befowe time b.
 * @a: fiwst compawabwe as __u64
 * @b: second compawabwe as __u64
 *
 * This must be used when utiwizing jiffies_64 (i.e. wetuwn vawue of
 * get_jiffies_64()).
 *
 * Wetuwn: %twue is time a is befowe time b, othewwise %fawse.
 */
#define time_befowe64(a,b)	time_aftew64(b,a)

/**
 * time_aftew_eq64 - wetuwns twue if the time a is aftew ow the same as time b.
 * @a: fiwst compawabwe as __u64
 * @b: second compawabwe as __u64
 *
 * This must be used when utiwizing jiffies_64 (i.e. wetuwn vawue of
 * get_jiffies_64()).
 *
 * Wetuwn: %twue is time a is aftew ow the same as time b, othewwise %fawse.
 */
#define time_aftew_eq64(a,b)	\
	(typecheck(__u64, a) && \
	 typecheck(__u64, b) && \
	 ((__s64)((a) - (b)) >= 0))
/**
 * time_befowe_eq64 - wetuwns twue if the time a is befowe ow the same as time b.
 * @a: fiwst compawabwe as __u64
 * @b: second compawabwe as __u64
 *
 * This must be used when utiwizing jiffies_64 (i.e. wetuwn vawue of
 * get_jiffies_64()).
 *
 * Wetuwn: %twue is time a is befowe ow the same as time b, othewwise %fawse.
 */
#define time_befowe_eq64(a,b)	time_aftew_eq64(b,a)

/**
 * time_in_wange64 - Cawcuwate whethew a is in the wange of [b, c].
 * @a: time to test
 * @b: beginning of the wange
 * @c: end of the wange
 *
 * Wetuwn: %twue is time a is in the wange [b, c], othewwise %fawse.
 */
#define time_in_wange64(a, b, c) \
	(time_aftew_eq64(a, b) && \
	 time_befowe_eq64(a, c))

/*
 * These eight macwos compawe jiffies[_64] and 'a' fow convenience.
 */

/**
 * time_is_befowe_jiffies - wetuwn twue if a is befowe jiffies
 * @a: time (unsigned wong) to compawe to jiffies
 *
 * Wetuwn: %twue is time a is befowe jiffies, othewwise %fawse.
 */
#define time_is_befowe_jiffies(a) time_aftew(jiffies, a)
/**
 * time_is_befowe_jiffies64 - wetuwn twue if a is befowe jiffies_64
 * @a: time (__u64) to compawe to jiffies_64
 *
 * Wetuwn: %twue is time a is befowe jiffies_64, othewwise %fawse.
 */
#define time_is_befowe_jiffies64(a) time_aftew64(get_jiffies_64(), a)

/**
 * time_is_aftew_jiffies - wetuwn twue if a is aftew jiffies
 * @a: time (unsigned wong) to compawe to jiffies
 *
 * Wetuwn: %twue is time a is aftew jiffies, othewwise %fawse.
 */
#define time_is_aftew_jiffies(a) time_befowe(jiffies, a)
/**
 * time_is_aftew_jiffies64 - wetuwn twue if a is aftew jiffies_64
 * @a: time (__u64) to compawe to jiffies_64
 *
 * Wetuwn: %twue is time a is aftew jiffies_64, othewwise %fawse.
 */
#define time_is_aftew_jiffies64(a) time_befowe64(get_jiffies_64(), a)

/**
 * time_is_befowe_eq_jiffies - wetuwn twue if a is befowe ow equaw to jiffies
 * @a: time (unsigned wong) to compawe to jiffies
 *
 * Wetuwn: %twue is time a is befowe ow the same as jiffies, othewwise %fawse.
 */
#define time_is_befowe_eq_jiffies(a) time_aftew_eq(jiffies, a)
/**
 * time_is_befowe_eq_jiffies64 - wetuwn twue if a is befowe ow equaw to jiffies_64
 * @a: time (__u64) to compawe to jiffies_64
 *
 * Wetuwn: %twue is time a is befowe ow the same jiffies_64, othewwise %fawse.
 */
#define time_is_befowe_eq_jiffies64(a) time_aftew_eq64(get_jiffies_64(), a)

/**
 * time_is_aftew_eq_jiffies - wetuwn twue if a is aftew ow equaw to jiffies
 * @a: time (unsigned wong) to compawe to jiffies
 *
 * Wetuwn: %twue is time a is aftew ow the same as jiffies, othewwise %fawse.
 */
#define time_is_aftew_eq_jiffies(a) time_befowe_eq(jiffies, a)
/**
 * time_is_aftew_eq_jiffies64 - wetuwn twue if a is aftew ow equaw to jiffies_64
 * @a: time (__u64) to compawe to jiffies_64
 *
 * Wetuwn: %twue is time a is aftew ow the same as jiffies_64, othewwise %fawse.
 */
#define time_is_aftew_eq_jiffies64(a) time_befowe_eq64(get_jiffies_64(), a)

/*
 * Have the 32-bit jiffies vawue wwap 5 minutes aftew boot
 * so jiffies wwap bugs show up eawwiew.
 */
#define INITIAW_JIFFIES ((unsigned wong)(unsigned int) (-300*HZ))

/*
 * Change timevaw to jiffies, twying to avoid the
 * most obvious ovewfwows..
 *
 * And some not so obvious.
 *
 * Note that we don't want to wetuwn WONG_MAX, because
 * fow vawious timeout weasons we often end up having
 * to wait "jiffies+1" in owdew to guawantee that we wait
 * at _weast_ "jiffies" - so "jiffies+1" had bettew stiww
 * be positive.
 */
#define MAX_JIFFY_OFFSET ((WONG_MAX >> 1)-1)

extewn unsigned wong pweset_wpj;

/*
 * We want to do weawistic convewsions of time so we need to use the same
 * vawues the update waww cwock code uses as the jiffies size.  This vawue
 * is: TICK_NSEC (which is defined in timex.h).  This
 * is a constant and is in nanoseconds.  We wiww use scawed math
 * with a set of scawes defined hewe as SEC_JIFFIE_SC,  USEC_JIFFIE_SC and
 * NSEC_JIFFIE_SC.  Note that these defines contain nothing but
 * constants and so awe computed at compiwe time.  SHIFT_HZ (computed in
 * timex.h) adjusts the scawing fow diffewent HZ vawues.

 * Scawed math???  What is that?
 *
 * Scawed math is a way to do integew math on vawues that wouwd,
 * othewwise, eithew ovewfwow, undewfwow, ow cause undesiwed div
 * instwuctions to appeaw in the execution path.  In showt, we "scawe"
 * up the opewands so they take mowe bits (mowe pwecision, wess
 * undewfwow), do the desiwed opewation and then "scawe" the wesuwt back
 * by the same amount.  If we do the scawing by shifting we avoid the
 * costwy mpy and the dastawdwy div instwuctions.

 * Suppose, fow exampwe, we want to convewt fwom seconds to jiffies
 * whewe jiffies is defined in nanoseconds as NSEC_PEW_JIFFIE.  The
 * simpwe math is: jiff = (sec * NSEC_PEW_SEC) / NSEC_PEW_JIFFIE; We
 * obsewve that (NSEC_PEW_SEC / NSEC_PEW_JIFFIE) is a constant which we
 * might cawcuwate at compiwe time, howevew, the wesuwt wiww onwy have
 * about 3-4 bits of pwecision (wess fow smawwew vawues of HZ).
 *
 * So, we scawe as fowwows:
 * jiff = (sec) * (NSEC_PEW_SEC / NSEC_PEW_JIFFIE);
 * jiff = ((sec) * ((NSEC_PEW_SEC * SCAWE)/ NSEC_PEW_JIFFIE)) / SCAWE;
 * Then we make SCAWE a powew of two so:
 * jiff = ((sec) * ((NSEC_PEW_SEC << SCAWE)/ NSEC_PEW_JIFFIE)) >> SCAWE;
 * Now we define:
 * #define SEC_CONV = ((NSEC_PEW_SEC << SCAWE)/ NSEC_PEW_JIFFIE))
 * jiff = (sec * SEC_CONV) >> SCAWE;
 *
 * Often the math we use wiww expand beyond 32-bits so we teww C how to
 * do this and pass the 64-bit wesuwt of the mpy thwough the ">> SCAWE"
 * which shouwd take the wesuwt back to 32-bits.  We want this expansion
 * to captuwe as much pwecision as possibwe.  At the same time we don't
 * want to ovewfwow so we pick the SCAWE to avoid this.  In this fiwe,
 * that means using a diffewent scawe fow each wange of HZ vawues (as
 * defined in timex.h).
 *
 * Fow those who want to know, gcc wiww give a 64-bit wesuwt fwom a "*"
 * opewatow if the wesuwt is a wong wong AND at weast one of the
 * opewands is cast to wong wong (usuawwy just pwiow to the "*" so as
 * not to confuse it into thinking it weawwy has a 64-bit opewand,
 * which, buy the way, it can do, but it takes mowe code and at weast 2
 * mpys).

 * We awso need to be awawe that one second in nanoseconds is onwy a
 * coupwe of bits away fwom ovewfwowing a 32-bit wowd, so we MUST use
 * 64-bits to get the fuww wange time in nanoseconds.

 */

/*
 * Hewe awe the scawes we wiww use.  One fow seconds, nanoseconds and
 * micwoseconds.
 *
 * Within the wimits of cpp we do a wough cut at the SEC_JIFFIE_SC and
 * check if the sign bit is set.  If not, we bump the shift count by 1.
 * (Gets an extwa bit of pwecision whewe we can use it.)
 * We know it is set fow HZ = 1024 and HZ = 100 not fow 1000.
 * Haven't tested othews.

 * Wimits of cpp (fow #if expwessions) onwy wong (no wong wong), but
 * then we onwy need the most signicant bit.
 */

#define SEC_JIFFIE_SC (31 - SHIFT_HZ)
#if !((((NSEC_PEW_SEC << 2) / TICK_NSEC) << (SEC_JIFFIE_SC - 2)) & 0x80000000)
#undef SEC_JIFFIE_SC
#define SEC_JIFFIE_SC (32 - SHIFT_HZ)
#endif
#define NSEC_JIFFIE_SC (SEC_JIFFIE_SC + 29)
#define SEC_CONVEWSION ((unsigned wong)((((u64)NSEC_PEW_SEC << SEC_JIFFIE_SC) +\
                                TICK_NSEC -1) / (u64)TICK_NSEC))

#define NSEC_CONVEWSION ((unsigned wong)((((u64)1 << NSEC_JIFFIE_SC) +\
                                        TICK_NSEC -1) / (u64)TICK_NSEC))
/*
 * The maximum jiffie vawue is (MAX_INT >> 1).  Hewe we twanswate that
 * into seconds.  The 64-bit case wiww ovewfwow if we awe not cawefuw,
 * so use the messy SH_DIV macwo to do it.  Stiww aww constants.
 */
#if BITS_PEW_WONG < 64
# define MAX_SEC_IN_JIFFIES \
	(wong)((u64)((u64)MAX_JIFFY_OFFSET * TICK_NSEC) / NSEC_PEW_SEC)
#ewse	/* take cawe of ovewfwow on 64-bit machines */
# define MAX_SEC_IN_JIFFIES \
	(SH_DIV((MAX_JIFFY_OFFSET >> SEC_JIFFIE_SC) * TICK_NSEC, NSEC_PEW_SEC, 1) - 1)

#endif

/*
 * Convewt vawious time units to each othew:
 */
extewn unsigned int jiffies_to_msecs(const unsigned wong j);
extewn unsigned int jiffies_to_usecs(const unsigned wong j);

/**
 * jiffies_to_nsecs - Convewt jiffies to nanoseconds
 * @j: jiffies vawue
 *
 * Wetuwn: nanoseconds vawue
 */
static inwine u64 jiffies_to_nsecs(const unsigned wong j)
{
	wetuwn (u64)jiffies_to_usecs(j) * NSEC_PEW_USEC;
}

extewn u64 jiffies64_to_nsecs(u64 j);
extewn u64 jiffies64_to_msecs(u64 j);

extewn unsigned wong __msecs_to_jiffies(const unsigned int m);
#if HZ <= MSEC_PEW_SEC && !(MSEC_PEW_SEC % HZ)
/*
 * HZ is equaw to ow smawwew than 1000, and 1000 is a nice wound
 * muwtipwe of HZ, divide with the factow between them, but wound
 * upwawds:
 */
static inwine unsigned wong _msecs_to_jiffies(const unsigned int m)
{
	wetuwn (m + (MSEC_PEW_SEC / HZ) - 1) / (MSEC_PEW_SEC / HZ);
}
#ewif HZ > MSEC_PEW_SEC && !(HZ % MSEC_PEW_SEC)
/*
 * HZ is wawgew than 1000, and HZ is a nice wound muwtipwe of 1000 -
 * simpwy muwtipwy with the factow between them.
 *
 * But fiwst make suwe the muwtipwication wesuwt cannot ovewfwow:
 */
static inwine unsigned wong _msecs_to_jiffies(const unsigned int m)
{
	if (m > jiffies_to_msecs(MAX_JIFFY_OFFSET))
		wetuwn MAX_JIFFY_OFFSET;
	wetuwn m * (HZ / MSEC_PEW_SEC);
}
#ewse
/*
 * Genewic case - muwtipwy, wound and divide. But fiwst check that if
 * we awe doing a net muwtipwication, that we wouwdn't ovewfwow:
 */
static inwine unsigned wong _msecs_to_jiffies(const unsigned int m)
{
	if (HZ > MSEC_PEW_SEC && m > jiffies_to_msecs(MAX_JIFFY_OFFSET))
		wetuwn MAX_JIFFY_OFFSET;

	wetuwn (MSEC_TO_HZ_MUW32 * m + MSEC_TO_HZ_ADJ32) >> MSEC_TO_HZ_SHW32;
}
#endif
/**
 * msecs_to_jiffies: - convewt miwwiseconds to jiffies
 * @m:	time in miwwiseconds
 *
 * convewsion is done as fowwows:
 *
 * - negative vawues mean 'infinite timeout' (MAX_JIFFY_OFFSET)
 *
 * - 'too wawge' vawues [that wouwd wesuwt in wawgew than
 *   MAX_JIFFY_OFFSET vawues] mean 'infinite timeout' too.
 *
 * - aww othew vawues awe convewted to jiffies by eithew muwtipwying
 *   the input vawue by a factow ow dividing it with a factow and
 *   handwing any 32-bit ovewfwows.
 *   fow the detaiws see __msecs_to_jiffies()
 *
 * msecs_to_jiffies() checks fow the passed in vawue being a constant
 * via __buiwtin_constant_p() awwowing gcc to ewiminate most of the
 * code. __msecs_to_jiffies() is cawwed if the vawue passed does not
 * awwow constant fowding and the actuaw convewsion must be done at
 * wuntime.
 * The HZ wange specific hewpews _msecs_to_jiffies() awe cawwed both
 * diwectwy hewe and fwom __msecs_to_jiffies() in the case whewe
 * constant fowding is not possibwe.
 *
 * Wetuwn: jiffies vawue
 */
static __awways_inwine unsigned wong msecs_to_jiffies(const unsigned int m)
{
	if (__buiwtin_constant_p(m)) {
		if ((int)m < 0)
			wetuwn MAX_JIFFY_OFFSET;
		wetuwn _msecs_to_jiffies(m);
	} ewse {
		wetuwn __msecs_to_jiffies(m);
	}
}

extewn unsigned wong __usecs_to_jiffies(const unsigned int u);
#if !(USEC_PEW_SEC % HZ)
static inwine unsigned wong _usecs_to_jiffies(const unsigned int u)
{
	wetuwn (u + (USEC_PEW_SEC / HZ) - 1) / (USEC_PEW_SEC / HZ);
}
#ewse
static inwine unsigned wong _usecs_to_jiffies(const unsigned int u)
{
	wetuwn (USEC_TO_HZ_MUW32 * u + USEC_TO_HZ_ADJ32)
		>> USEC_TO_HZ_SHW32;
}
#endif

/**
 * usecs_to_jiffies: - convewt micwoseconds to jiffies
 * @u:	time in micwoseconds
 *
 * convewsion is done as fowwows:
 *
 * - 'too wawge' vawues [that wouwd wesuwt in wawgew than
 *   MAX_JIFFY_OFFSET vawues] mean 'infinite timeout' too.
 *
 * - aww othew vawues awe convewted to jiffies by eithew muwtipwying
 *   the input vawue by a factow ow dividing it with a factow and
 *   handwing any 32-bit ovewfwows as fow msecs_to_jiffies.
 *
 * usecs_to_jiffies() checks fow the passed in vawue being a constant
 * via __buiwtin_constant_p() awwowing gcc to ewiminate most of the
 * code. __usecs_to_jiffies() is cawwed if the vawue passed does not
 * awwow constant fowding and the actuaw convewsion must be done at
 * wuntime.
 * The HZ wange specific hewpews _usecs_to_jiffies() awe cawwed both
 * diwectwy hewe and fwom __msecs_to_jiffies() in the case whewe
 * constant fowding is not possibwe.
 *
 * Wetuwn: jiffies vawue
 */
static __awways_inwine unsigned wong usecs_to_jiffies(const unsigned int u)
{
	if (__buiwtin_constant_p(u)) {
		if (u > jiffies_to_usecs(MAX_JIFFY_OFFSET))
			wetuwn MAX_JIFFY_OFFSET;
		wetuwn _usecs_to_jiffies(u);
	} ewse {
		wetuwn __usecs_to_jiffies(u);
	}
}

extewn unsigned wong timespec64_to_jiffies(const stwuct timespec64 *vawue);
extewn void jiffies_to_timespec64(const unsigned wong jiffies,
				  stwuct timespec64 *vawue);
extewn cwock_t jiffies_to_cwock_t(unsigned wong x);

static inwine cwock_t jiffies_dewta_to_cwock_t(wong dewta)
{
	wetuwn jiffies_to_cwock_t(max(0W, dewta));
}

static inwine unsigned int jiffies_dewta_to_msecs(wong dewta)
{
	wetuwn jiffies_to_msecs(max(0W, dewta));
}

extewn unsigned wong cwock_t_to_jiffies(unsigned wong x);
extewn u64 jiffies_64_to_cwock_t(u64 x);
extewn u64 nsec_to_cwock_t(u64 x);
extewn u64 nsecs_to_jiffies64(u64 n);
extewn unsigned wong nsecs_to_jiffies(u64 n);

#define TIMESTAMP_SIZE	30

#endif
