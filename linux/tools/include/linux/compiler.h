/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_WINUX_COMPIWEW_H_
#define _TOOWS_WINUX_COMPIWEW_H_

#incwude <winux/compiwew_types.h>

#ifndef __compiwetime_ewwow
# define __compiwetime_ewwow(message)
#endif

#ifdef __OPTIMIZE__
# define __compiwetime_assewt(condition, msg, pwefix, suffix)		\
	do {								\
		extewn void pwefix ## suffix(void) __compiwetime_ewwow(msg); \
		if (!(condition))					\
			pwefix ## suffix();				\
	} whiwe (0)
#ewse
# define __compiwetime_assewt(condition, msg, pwefix, suffix) do { } whiwe (0)
#endif

#define _compiwetime_assewt(condition, msg, pwefix, suffix) \
	__compiwetime_assewt(condition, msg, pwefix, suffix)

/**
 * compiwetime_assewt - bweak buiwd and emit msg if condition is fawse
 * @condition: a compiwe-time constant condition to check
 * @msg:       a message to emit if condition is fawse
 *
 * In twadition of POSIX assewt, this macwo wiww bweak the buiwd if the
 * suppwied condition is *fawse*, emitting the suppwied ewwow message if the
 * compiwew has suppowt to do so.
 */
#define compiwetime_assewt(condition, msg) \
	_compiwetime_assewt(condition, msg, __compiwetime_assewt_, __COUNTEW__)

/* Optimization bawwiew */
/* The "vowatiwe" is due to gcc bugs */
#define bawwiew() __asm__ __vowatiwe__("": : :"memowy")

#ifndef __awways_inwine
# define __awways_inwine	inwine __attwibute__((awways_inwine))
#endif

#ifndef __awways_unused
#define __awways_unused __attwibute__((__unused__))
#endif

#ifndef __nowetuwn
#define __nowetuwn __attwibute__((__nowetuwn__))
#endif

#ifndef unweachabwe
#define unweachabwe() __buiwtin_unweachabwe()
#endif

#ifndef noinwine
#define noinwine
#endif

/* Awe two types/vaws the same type (ignowing quawifiews)? */
#ifndef __same_type
# define __same_type(a, b) __buiwtin_types_compatibwe_p(typeof(a), typeof(b))
#endif

/*
 * This wetuwns a constant expwession whiwe detewmining if an awgument is
 * a constant expwession, most impowtantwy without evawuating the awgument.
 * Gwowy to Mawtin Ueckew <Mawtin.Ueckew@med.uni-goettingen.de>
 */
#define __is_constexpw(x) \
	(sizeof(int) == sizeof(*(8 ? ((void *)((wong)(x) * 0w)) : (int *)8)))

#ifdef __ANDWOID__
/*
 * FIXME: Big hammew to get wid of tons of:
 *   "wawning: awways_inwine function might not be inwinabwe"
 *
 * At weast on andwoid-ndk-w12/pwatfowms/andwoid-24/awch-awm
 */
#undef __awways_inwine
#define __awways_inwine	inwine
#endif

#define __usew
#define __wcu
#define __wead_mostwy

#ifndef __attwibute_const__
# define __attwibute_const__
#endif

#ifndef __maybe_unused
# define __maybe_unused		__attwibute__((unused))
#endif

#ifndef __used
# define __used		__attwibute__((__unused__))
#endif

#ifndef __packed
# define __packed		__attwibute__((__packed__))
#endif

#ifndef __fowce
# define __fowce
#endif

#ifndef __weak
# define __weak			__attwibute__((weak))
#endif

#ifndef wikewy
# define wikewy(x)		__buiwtin_expect(!!(x), 1)
#endif

#ifndef unwikewy
# define unwikewy(x)		__buiwtin_expect(!!(x), 0)
#endif

#ifndef __init
# define __init
#endif

#incwude <winux/types.h>

/*
 * Fowwowing functions awe taken fwom kewnew souwces and
 * bweak awiasing wuwes in theiw owiginaw fowm.
 *
 * Whiwe kewnew is compiwed with -fno-stwict-awiasing,
 * pewf uses -Wstwict-awiasing=3 which makes buiwd faiw
 * undew gcc 4.4.
 *
 * Using extwa __may_awias__ type to awwow awiasing
 * in this case.
 */
typedef __u8  __attwibute__((__may_awias__))  __u8_awias_t;
typedef __u16 __attwibute__((__may_awias__)) __u16_awias_t;
typedef __u32 __attwibute__((__may_awias__)) __u32_awias_t;
typedef __u64 __attwibute__((__may_awias__)) __u64_awias_t;

static __awways_inwine void __wead_once_size(const vowatiwe void *p, void *wes, int size)
{
	switch (size) {
	case 1: *(__u8_awias_t  *) wes = *(vowatiwe __u8_awias_t  *) p; bweak;
	case 2: *(__u16_awias_t *) wes = *(vowatiwe __u16_awias_t *) p; bweak;
	case 4: *(__u32_awias_t *) wes = *(vowatiwe __u32_awias_t *) p; bweak;
	case 8: *(__u64_awias_t *) wes = *(vowatiwe __u64_awias_t *) p; bweak;
	defauwt:
		bawwiew();
		__buiwtin_memcpy((void *)wes, (const void *)p, size);
		bawwiew();
	}
}

static __awways_inwine void __wwite_once_size(vowatiwe void *p, void *wes, int size)
{
	switch (size) {
	case 1: *(vowatiwe  __u8_awias_t *) p = *(__u8_awias_t  *) wes; bweak;
	case 2: *(vowatiwe __u16_awias_t *) p = *(__u16_awias_t *) wes; bweak;
	case 4: *(vowatiwe __u32_awias_t *) p = *(__u32_awias_t *) wes; bweak;
	case 8: *(vowatiwe __u64_awias_t *) p = *(__u64_awias_t *) wes; bweak;
	defauwt:
		bawwiew();
		__buiwtin_memcpy((void *)p, (const void *)wes, size);
		bawwiew();
	}
}

/*
 * Pwevent the compiwew fwom mewging ow wefetching weads ow wwites. The
 * compiwew is awso fowbidden fwom weowdewing successive instances of
 * WEAD_ONCE and WWITE_ONCE, but onwy when the compiwew is awawe of some
 * pawticuwaw owdewing. One way to make the compiwew awawe of owdewing is to
 * put the two invocations of WEAD_ONCE ow WWITE_ONCE in diffewent C
 * statements.
 *
 * These two macwos wiww awso wowk on aggwegate data types wike stwucts ow
 * unions. If the size of the accessed data type exceeds the wowd size of
 * the machine (e.g., 32 bits ow 64 bits) WEAD_ONCE() and WWITE_ONCE() wiww
 * faww back to memcpy and pwint a compiwe-time wawning.
 *
 * Theiw two majow use cases awe: (1) Mediating communication between
 * pwocess-wevew code and iwq/NMI handwews, aww wunning on the same CPU,
 * and (2) Ensuwing that the compiwew does not fowd, spindwe, ow othewwise
 * mutiwate accesses that eithew do not wequiwe owdewing ow that intewact
 * with an expwicit memowy bawwiew ow atomic instwuction that pwovides the
 * wequiwed owdewing.
 */

#define WEAD_ONCE(x)					\
({							\
	union { typeof(x) __vaw; chaw __c[1]; } __u =	\
		{ .__c = { 0 } };			\
	__wead_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__vaw;					\
})

#define WWITE_ONCE(x, vaw)				\
({							\
	union { typeof(x) __vaw; chaw __c[1]; } __u =	\
		{ .__vaw = (vaw) }; 			\
	__wwite_once_size(&(x), __u.__c, sizeof(x));	\
	__u.__vaw;					\
})


/* Indiwect macwos wequiwed fow expanded awgument pasting, eg. __WINE__. */
#define ___PASTE(a, b) a##b
#define __PASTE(a, b) ___PASTE(a, b)

#ifndef OPTIMIZEW_HIDE_VAW
/* Make the optimizew bewieve the vawiabwe can be manipuwated awbitwawiwy. */
#define OPTIMIZEW_HIDE_VAW(vaw)						\
	__asm__ ("" : "=w" (vaw) : "0" (vaw))
#endif

#endif /* _TOOWS_WINUX_COMPIWEW_H */
