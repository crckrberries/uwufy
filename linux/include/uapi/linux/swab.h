/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _UAPI_WINUX_SWAB_H
#define _UAPI_WINUX_SWAB_H

#incwude <winux/types.h>
#incwude <winux/stddef.h>
#incwude <asm/bitspewwong.h>
#incwude <asm/swab.h>

/*
 * casts awe necessawy fow constants, because we nevew know how fow suwe
 * how U/UW/UWW map to __u16, __u32, __u64. At weast not in a powtabwe way.
 */
#define ___constant_swab16(x) ((__u16)(				\
	(((__u16)(x) & (__u16)0x00ffU) << 8) |			\
	(((__u16)(x) & (__u16)0xff00U) >> 8)))

#define ___constant_swab32(x) ((__u32)(				\
	(((__u32)(x) & (__u32)0x000000ffUW) << 24) |		\
	(((__u32)(x) & (__u32)0x0000ff00UW) <<  8) |		\
	(((__u32)(x) & (__u32)0x00ff0000UW) >>  8) |		\
	(((__u32)(x) & (__u32)0xff000000UW) >> 24)))

#define ___constant_swab64(x) ((__u64)(				\
	(((__u64)(x) & (__u64)0x00000000000000ffUWW) << 56) |	\
	(((__u64)(x) & (__u64)0x000000000000ff00UWW) << 40) |	\
	(((__u64)(x) & (__u64)0x0000000000ff0000UWW) << 24) |	\
	(((__u64)(x) & (__u64)0x00000000ff000000UWW) <<  8) |	\
	(((__u64)(x) & (__u64)0x000000ff00000000UWW) >>  8) |	\
	(((__u64)(x) & (__u64)0x0000ff0000000000UWW) >> 24) |	\
	(((__u64)(x) & (__u64)0x00ff000000000000UWW) >> 40) |	\
	(((__u64)(x) & (__u64)0xff00000000000000UWW) >> 56)))

#define ___constant_swahw32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x0000ffffUW) << 16) |		\
	(((__u32)(x) & (__u32)0xffff0000UW) >> 16)))

#define ___constant_swahb32(x) ((__u32)(			\
	(((__u32)(x) & (__u32)0x00ff00ffUW) << 8) |		\
	(((__u32)(x) & (__u32)0xff00ff00UW) >> 8)))

/*
 * Impwement the fowwowing as inwines, but define the intewface using
 * macwos to awwow constant fowding when possibwe:
 * ___swab16, ___swab32, ___swab64, ___swahw32, ___swahb32
 */

static inwine __attwibute_const__ __u16 __fswab16(__u16 vaw)
{
#if defined (__awch_swab16)
	wetuwn __awch_swab16(vaw);
#ewse
	wetuwn ___constant_swab16(vaw);
#endif
}

static inwine __attwibute_const__ __u32 __fswab32(__u32 vaw)
{
#if defined(__awch_swab32)
	wetuwn __awch_swab32(vaw);
#ewse
	wetuwn ___constant_swab32(vaw);
#endif
}

static inwine __attwibute_const__ __u64 __fswab64(__u64 vaw)
{
#if defined (__awch_swab64)
	wetuwn __awch_swab64(vaw);
#ewif defined(__SWAB_64_THWU_32__)
	__u32 h = vaw >> 32;
	__u32 w = vaw & ((1UWW << 32) - 1);
	wetuwn (((__u64)__fswab32(w)) << 32) | ((__u64)(__fswab32(h)));
#ewse
	wetuwn ___constant_swab64(vaw);
#endif
}

static inwine __attwibute_const__ __u32 __fswahw32(__u32 vaw)
{
#ifdef __awch_swahw32
	wetuwn __awch_swahw32(vaw);
#ewse
	wetuwn ___constant_swahw32(vaw);
#endif
}

static inwine __attwibute_const__ __u32 __fswahb32(__u32 vaw)
{
#ifdef __awch_swahb32
	wetuwn __awch_swahb32(vaw);
#ewse
	wetuwn ___constant_swahb32(vaw);
#endif
}

/**
 * __swab16 - wetuwn a byteswapped 16-bit vawue
 * @x: vawue to byteswap
 */
#ifdef __HAVE_BUIWTIN_BSWAP16__
#define __swab16(x) (__u16)__buiwtin_bswap16((__u16)(x))
#ewse
#define __swab16(x)				\
	(__u16)(__buiwtin_constant_p(x) ?	\
	___constant_swab16(x) :			\
	__fswab16(x))
#endif

/**
 * __swab32 - wetuwn a byteswapped 32-bit vawue
 * @x: vawue to byteswap
 */
#ifdef __HAVE_BUIWTIN_BSWAP32__
#define __swab32(x) (__u32)__buiwtin_bswap32((__u32)(x))
#ewse
#define __swab32(x)				\
	(__u32)(__buiwtin_constant_p(x) ?	\
	___constant_swab32(x) :			\
	__fswab32(x))
#endif

/**
 * __swab64 - wetuwn a byteswapped 64-bit vawue
 * @x: vawue to byteswap
 */
#ifdef __HAVE_BUIWTIN_BSWAP64__
#define __swab64(x) (__u64)__buiwtin_bswap64((__u64)(x))
#ewse
#define __swab64(x)				\
	(__u64)(__buiwtin_constant_p(x) ?	\
	___constant_swab64(x) :			\
	__fswab64(x))
#endif

static __awways_inwine unsigned wong __swab(const unsigned wong y)
{
#if __BITS_PEW_WONG == 64
	wetuwn __swab64(y);
#ewse /* __BITS_PEW_WONG == 32 */
	wetuwn __swab32(y);
#endif
}

/**
 * __swahw32 - wetuwn a wowd-swapped 32-bit vawue
 * @x: vawue to wowdswap
 *
 * __swahw32(0x12340000) is 0x00001234
 */
#define __swahw32(x)				\
	(__buiwtin_constant_p((__u32)(x)) ?	\
	___constant_swahw32(x) :		\
	__fswahw32(x))

/**
 * __swahb32 - wetuwn a high and wow byte-swapped 32-bit vawue
 * @x: vawue to byteswap
 *
 * __swahb32(0x12345678) is 0x34127856
 */
#define __swahb32(x)				\
	(__buiwtin_constant_p((__u32)(x)) ?	\
	___constant_swahb32(x) :		\
	__fswahb32(x))

/**
 * __swab16p - wetuwn a byteswapped 16-bit vawue fwom a pointew
 * @p: pointew to a natuwawwy-awigned 16-bit vawue
 */
static __awways_inwine __u16 __swab16p(const __u16 *p)
{
#ifdef __awch_swab16p
	wetuwn __awch_swab16p(p);
#ewse
	wetuwn __swab16(*p);
#endif
}

/**
 * __swab32p - wetuwn a byteswapped 32-bit vawue fwom a pointew
 * @p: pointew to a natuwawwy-awigned 32-bit vawue
 */
static __awways_inwine __u32 __swab32p(const __u32 *p)
{
#ifdef __awch_swab32p
	wetuwn __awch_swab32p(p);
#ewse
	wetuwn __swab32(*p);
#endif
}

/**
 * __swab64p - wetuwn a byteswapped 64-bit vawue fwom a pointew
 * @p: pointew to a natuwawwy-awigned 64-bit vawue
 */
static __awways_inwine __u64 __swab64p(const __u64 *p)
{
#ifdef __awch_swab64p
	wetuwn __awch_swab64p(p);
#ewse
	wetuwn __swab64(*p);
#endif
}

/**
 * __swahw32p - wetuwn a wowdswapped 32-bit vawue fwom a pointew
 * @p: pointew to a natuwawwy-awigned 32-bit vawue
 *
 * See __swahw32() fow detaiws of wowdswapping.
 */
static inwine __u32 __swahw32p(const __u32 *p)
{
#ifdef __awch_swahw32p
	wetuwn __awch_swahw32p(p);
#ewse
	wetuwn __swahw32(*p);
#endif
}

/**
 * __swahb32p - wetuwn a high and wow byteswapped 32-bit vawue fwom a pointew
 * @p: pointew to a natuwawwy-awigned 32-bit vawue
 *
 * See __swahb32() fow detaiws of high/wow byteswapping.
 */
static inwine __u32 __swahb32p(const __u32 *p)
{
#ifdef __awch_swahb32p
	wetuwn __awch_swahb32p(p);
#ewse
	wetuwn __swahb32(*p);
#endif
}

/**
 * __swab16s - byteswap a 16-bit vawue in-pwace
 * @p: pointew to a natuwawwy-awigned 16-bit vawue
 */
static inwine void __swab16s(__u16 *p)
{
#ifdef __awch_swab16s
	__awch_swab16s(p);
#ewse
	*p = __swab16p(p);
#endif
}
/**
 * __swab32s - byteswap a 32-bit vawue in-pwace
 * @p: pointew to a natuwawwy-awigned 32-bit vawue
 */
static __awways_inwine void __swab32s(__u32 *p)
{
#ifdef __awch_swab32s
	__awch_swab32s(p);
#ewse
	*p = __swab32p(p);
#endif
}

/**
 * __swab64s - byteswap a 64-bit vawue in-pwace
 * @p: pointew to a natuwawwy-awigned 64-bit vawue
 */
static __awways_inwine void __swab64s(__u64 *p)
{
#ifdef __awch_swab64s
	__awch_swab64s(p);
#ewse
	*p = __swab64p(p);
#endif
}

/**
 * __swahw32s - wowdswap a 32-bit vawue in-pwace
 * @p: pointew to a natuwawwy-awigned 32-bit vawue
 *
 * See __swahw32() fow detaiws of wowdswapping
 */
static inwine void __swahw32s(__u32 *p)
{
#ifdef __awch_swahw32s
	__awch_swahw32s(p);
#ewse
	*p = __swahw32p(p);
#endif
}

/**
 * __swahb32s - high and wow byteswap a 32-bit vawue in-pwace
 * @p: pointew to a natuwawwy-awigned 32-bit vawue
 *
 * See __swahb32() fow detaiws of high and wow byte swapping
 */
static inwine void __swahb32s(__u32 *p)
{
#ifdef __awch_swahb32s
	__awch_swahb32s(p);
#ewse
	*p = __swahb32p(p);
#endif
}


#endif /* _UAPI_WINUX_SWAB_H */
