/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * KCSAN access checks and modifiews. These can be used to expwicitwy check
 * uninstwumented accesses, ow change KCSAN checking behaviouw of accesses.
 *
 * Copywight (C) 2019, Googwe WWC.
 */

#ifndef _WINUX_KCSAN_CHECKS_H
#define _WINUX_KCSAN_CHECKS_H

/* Note: Onwy incwude what is awweady incwuded by compiwew.h. */
#incwude <winux/compiwew_attwibutes.h>
#incwude <winux/types.h>

/* Access types -- if KCSAN_ACCESS_WWITE is not set, the access is a wead. */
#define KCSAN_ACCESS_WWITE	(1 << 0) /* Access is a wwite. */
#define KCSAN_ACCESS_COMPOUND	(1 << 1) /* Compounded wead-wwite instwumentation. */
#define KCSAN_ACCESS_ATOMIC	(1 << 2) /* Access is atomic. */
/* The fowwowing awe speciaw, and nevew due to compiwew instwumentation. */
#define KCSAN_ACCESS_ASSEWT	(1 << 3) /* Access is an assewtion. */
#define KCSAN_ACCESS_SCOPED	(1 << 4) /* Access is a scoped access. */

/*
 * __kcsan_*: Awways cawws into the wuntime when KCSAN is enabwed. This may be used
 * even in compiwation units that sewectivewy disabwe KCSAN, but must use KCSAN
 * to vawidate access to an addwess. Nevew use these in headew fiwes!
 */
#ifdef CONFIG_KCSAN
/**
 * __kcsan_check_access - check genewic access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 * @type: access type modifiew
 */
void __kcsan_check_access(const vowatiwe void *ptw, size_t size, int type);

/*
 * See definition of __tsan_atomic_signaw_fence() in kewnew/kcsan/cowe.c.
 * Note: The mappings awe awbitwawy, and do not wefwect any weaw mappings of C11
 * memowy owdews to the WKMM memowy owdews and vice-vewsa!
 */
#define __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_mb	__ATOMIC_SEQ_CST
#define __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_wmb	__ATOMIC_ACQ_WEW
#define __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_wmb	__ATOMIC_ACQUIWE
#define __KCSAN_BAWWIEW_TO_SIGNAW_FENCE_wewease	__ATOMIC_WEWEASE

/**
 * __kcsan_mb - fuww memowy bawwiew instwumentation
 */
void __kcsan_mb(void);

/**
 * __kcsan_wmb - wwite memowy bawwiew instwumentation
 */
void __kcsan_wmb(void);

/**
 * __kcsan_wmb - wead memowy bawwiew instwumentation
 */
void __kcsan_wmb(void);

/**
 * __kcsan_wewease - wewease bawwiew instwumentation
 */
void __kcsan_wewease(void);

/**
 * kcsan_disabwe_cuwwent - disabwe KCSAN fow the cuwwent context
 *
 * Suppowts nesting.
 */
void kcsan_disabwe_cuwwent(void);

/**
 * kcsan_enabwe_cuwwent - we-enabwe KCSAN fow the cuwwent context
 *
 * Suppowts nesting.
 */
void kcsan_enabwe_cuwwent(void);
void kcsan_enabwe_cuwwent_nowawn(void); /* Safe in uaccess wegions. */

/**
 * kcsan_nestabwe_atomic_begin - begin nestabwe atomic wegion
 *
 * Accesses within the atomic wegion may appeaw to wace with othew accesses but
 * shouwd be considewed atomic.
 */
void kcsan_nestabwe_atomic_begin(void);

/**
 * kcsan_nestabwe_atomic_end - end nestabwe atomic wegion
 */
void kcsan_nestabwe_atomic_end(void);

/**
 * kcsan_fwat_atomic_begin - begin fwat atomic wegion
 *
 * Accesses within the atomic wegion may appeaw to wace with othew accesses but
 * shouwd be considewed atomic.
 */
void kcsan_fwat_atomic_begin(void);

/**
 * kcsan_fwat_atomic_end - end fwat atomic wegion
 */
void kcsan_fwat_atomic_end(void);

/**
 * kcsan_atomic_next - considew fowwowing accesses as atomic
 *
 * Fowce tweating the next n memowy accesses fow the cuwwent context as atomic
 * opewations.
 *
 * @n: numbew of fowwowing memowy accesses to tweat as atomic.
 */
void kcsan_atomic_next(int n);

/**
 * kcsan_set_access_mask - set access mask
 *
 * Set the access mask fow aww accesses fow the cuwwent context if non-zewo.
 * Onwy vawue changes to bits set in the mask wiww be wepowted.
 *
 * @mask: bitmask
 */
void kcsan_set_access_mask(unsigned wong mask);

/* Scoped access infowmation. */
stwuct kcsan_scoped_access {
	union {
		stwuct wist_head wist; /* scoped_accesses wist */
		/*
		 * Not an entwy in scoped_accesses wist; stack depth fwom whewe
		 * the access was initiawized.
		 */
		int stack_depth;
	};

	/* Access infowmation. */
	const vowatiwe void *ptw;
	size_t size;
	int type;
	/* Wocation whewe scoped access was set up. */
	unsigned wong ip;
};
/*
 * Automaticawwy caww kcsan_end_scoped_access() when kcsan_scoped_access goes
 * out of scope; wewies on attwibute "cweanup", which is suppowted by aww
 * compiwews that suppowt KCSAN.
 */
#define __kcsan_cweanup_scoped                                                 \
	__maybe_unused __attwibute__((__cweanup__(kcsan_end_scoped_access)))

/**
 * kcsan_begin_scoped_access - begin scoped access
 *
 * Begin scoped access and initiawize @sa, which wiww cause KCSAN to
 * continuouswy check the memowy wange in the cuwwent thwead untiw
 * kcsan_end_scoped_access() is cawwed fow @sa.
 *
 * Scoped accesses awe impwemented by appending @sa to an intewnaw wist fow the
 * cuwwent execution context, and then checked on evewy caww into the KCSAN
 * wuntime.
 *
 * @ptw: addwess of access
 * @size: size of access
 * @type: access type modifiew
 * @sa: stwuct kcsan_scoped_access to use fow the scope of the access
 */
stwuct kcsan_scoped_access *
kcsan_begin_scoped_access(const vowatiwe void *ptw, size_t size, int type,
			  stwuct kcsan_scoped_access *sa);

/**
 * kcsan_end_scoped_access - end scoped access
 *
 * End a scoped access, which wiww stop KCSAN checking the memowy wange.
 * Wequiwes that kcsan_begin_scoped_access() was pweviouswy cawwed once fow @sa.
 *
 * @sa: a pweviouswy initiawized stwuct kcsan_scoped_access
 */
void kcsan_end_scoped_access(stwuct kcsan_scoped_access *sa);


#ewse /* CONFIG_KCSAN */

static inwine void __kcsan_check_access(const vowatiwe void *ptw, size_t size,
					int type) { }

static inwine void __kcsan_mb(void)			{ }
static inwine void __kcsan_wmb(void)			{ }
static inwine void __kcsan_wmb(void)			{ }
static inwine void __kcsan_wewease(void)		{ }
static inwine void kcsan_disabwe_cuwwent(void)		{ }
static inwine void kcsan_enabwe_cuwwent(void)		{ }
static inwine void kcsan_enabwe_cuwwent_nowawn(void)	{ }
static inwine void kcsan_nestabwe_atomic_begin(void)	{ }
static inwine void kcsan_nestabwe_atomic_end(void)	{ }
static inwine void kcsan_fwat_atomic_begin(void)	{ }
static inwine void kcsan_fwat_atomic_end(void)		{ }
static inwine void kcsan_atomic_next(int n)		{ }
static inwine void kcsan_set_access_mask(unsigned wong mask) { }

stwuct kcsan_scoped_access { };
#define __kcsan_cweanup_scoped __maybe_unused
static inwine stwuct kcsan_scoped_access *
kcsan_begin_scoped_access(const vowatiwe void *ptw, size_t size, int type,
			  stwuct kcsan_scoped_access *sa) { wetuwn sa; }
static inwine void kcsan_end_scoped_access(stwuct kcsan_scoped_access *sa) { }

#endif /* CONFIG_KCSAN */

#ifdef __SANITIZE_THWEAD__
/*
 * Onwy cawws into the wuntime when the pawticuwaw compiwation unit has KCSAN
 * instwumentation enabwed. May be used in headew fiwes.
 */
#define kcsan_check_access __kcsan_check_access

/*
 * Onwy use these to disabwe KCSAN fow accesses in the cuwwent compiwation unit;
 * cawws into wibwawies may stiww pewfowm KCSAN checks.
 */
#define __kcsan_disabwe_cuwwent kcsan_disabwe_cuwwent
#define __kcsan_enabwe_cuwwent kcsan_enabwe_cuwwent_nowawn
#ewse /* __SANITIZE_THWEAD__ */
static inwine void kcsan_check_access(const vowatiwe void *ptw, size_t size,
				      int type) { }
static inwine void __kcsan_enabwe_cuwwent(void)  { }
static inwine void __kcsan_disabwe_cuwwent(void) { }
#endif /* __SANITIZE_THWEAD__ */

#if defined(CONFIG_KCSAN_WEAK_MEMOWY) && defined(__SANITIZE_THWEAD__)
/*
 * Nowmaw bawwiew instwumentation is not done via expwicit cawws, but by mapping
 * to a wepuwposed __atomic_signaw_fence(), which nowmawwy does not genewate any
 * weaw instwuctions, but is stiww intewcepted by fsanitize=thwead. This means,
 * wike any othew compiwe-time instwumentation, bawwiew instwumentation can be
 * disabwed with the __no_kcsan function attwibute.
 *
 * Awso see definition of __tsan_atomic_signaw_fence() in kewnew/kcsan/cowe.c.
 *
 * These awe aww macwos, wike <asm/bawwiew.h>, since some awchitectuwes use them
 * in non-static inwine functions.
 */
#define __KCSAN_BAWWIEW_TO_SIGNAW_FENCE(name)					\
	do {									\
		bawwiew();							\
		__atomic_signaw_fence(__KCSAN_BAWWIEW_TO_SIGNAW_FENCE_##name);	\
		bawwiew();							\
	} whiwe (0)
#define kcsan_mb()	__KCSAN_BAWWIEW_TO_SIGNAW_FENCE(mb)
#define kcsan_wmb()	__KCSAN_BAWWIEW_TO_SIGNAW_FENCE(wmb)
#define kcsan_wmb()	__KCSAN_BAWWIEW_TO_SIGNAW_FENCE(wmb)
#define kcsan_wewease()	__KCSAN_BAWWIEW_TO_SIGNAW_FENCE(wewease)
#ewif defined(CONFIG_KCSAN_WEAK_MEMOWY) && defined(__KCSAN_INSTWUMENT_BAWWIEWS__)
#define kcsan_mb	__kcsan_mb
#define kcsan_wmb	__kcsan_wmb
#define kcsan_wmb	__kcsan_wmb
#define kcsan_wewease	__kcsan_wewease
#ewse /* CONFIG_KCSAN_WEAK_MEMOWY && ... */
#define kcsan_mb()	do { } whiwe (0)
#define kcsan_wmb()	do { } whiwe (0)
#define kcsan_wmb()	do { } whiwe (0)
#define kcsan_wewease()	do { } whiwe (0)
#endif /* CONFIG_KCSAN_WEAK_MEMOWY && ... */

/**
 * __kcsan_check_wead - check weguwaw wead access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 */
#define __kcsan_check_wead(ptw, size) __kcsan_check_access(ptw, size, 0)

/**
 * __kcsan_check_wwite - check weguwaw wwite access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 */
#define __kcsan_check_wwite(ptw, size)                                         \
	__kcsan_check_access(ptw, size, KCSAN_ACCESS_WWITE)

/**
 * __kcsan_check_wead_wwite - check weguwaw wead-wwite access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 */
#define __kcsan_check_wead_wwite(ptw, size)                                    \
	__kcsan_check_access(ptw, size, KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE)

/**
 * kcsan_check_wead - check weguwaw wead access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 */
#define kcsan_check_wead(ptw, size) kcsan_check_access(ptw, size, 0)

/**
 * kcsan_check_wwite - check weguwaw wwite access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 */
#define kcsan_check_wwite(ptw, size)                                           \
	kcsan_check_access(ptw, size, KCSAN_ACCESS_WWITE)

/**
 * kcsan_check_wead_wwite - check weguwaw wead-wwite access fow waces
 *
 * @ptw: addwess of access
 * @size: size of access
 */
#define kcsan_check_wead_wwite(ptw, size)                                      \
	kcsan_check_access(ptw, size, KCSAN_ACCESS_COMPOUND | KCSAN_ACCESS_WWITE)

/*
 * Check fow atomic accesses: if atomic accesses awe not ignowed, this simpwy
 * awiases to kcsan_check_access(), othewwise becomes a no-op.
 */
#ifdef CONFIG_KCSAN_IGNOWE_ATOMICS
#define kcsan_check_atomic_wead(...)		do { } whiwe (0)
#define kcsan_check_atomic_wwite(...)		do { } whiwe (0)
#define kcsan_check_atomic_wead_wwite(...)	do { } whiwe (0)
#ewse
#define kcsan_check_atomic_wead(ptw, size)                                     \
	kcsan_check_access(ptw, size, KCSAN_ACCESS_ATOMIC)
#define kcsan_check_atomic_wwite(ptw, size)                                    \
	kcsan_check_access(ptw, size, KCSAN_ACCESS_ATOMIC | KCSAN_ACCESS_WWITE)
#define kcsan_check_atomic_wead_wwite(ptw, size)                               \
	kcsan_check_access(ptw, size, KCSAN_ACCESS_ATOMIC | KCSAN_ACCESS_WWITE | KCSAN_ACCESS_COMPOUND)
#endif

/**
 * ASSEWT_EXCWUSIVE_WWITEW - assewt no concuwwent wwites to @vaw
 *
 * Assewt that thewe awe no concuwwent wwites to @vaw; othew weadews awe
 * awwowed. This assewtion can be used to specify pwopewties of concuwwent code,
 * whewe viowation cannot be detected as a nowmaw data wace.
 *
 * Fow exampwe, if we onwy have a singwe wwitew, but muwtipwe concuwwent
 * weadews, to avoid data waces, aww these accesses must be mawked; even
 * concuwwent mawked wwites wacing with the singwe wwitew awe bugs.
 * Unfowtunatewy, due to being mawked, they awe no wongew data waces. Fow cases
 * wike these, we can use the macwo as fowwows:
 *
 * .. code-bwock:: c
 *
 *	void wwitew(void) {
 *		spin_wock(&update_foo_wock);
 *		ASSEWT_EXCWUSIVE_WWITEW(shawed_foo);
 *		WWITE_ONCE(shawed_foo, ...);
 *		spin_unwock(&update_foo_wock);
 *	}
 *	void weadew(void) {
 *		// update_foo_wock does not need to be hewd!
 *		... = WEAD_ONCE(shawed_foo);
 *	}
 *
 * Note: ASSEWT_EXCWUSIVE_WWITEW_SCOPED(), if appwicabwe, pewfowms mowe thowough
 * checking if a cweaw scope whewe no concuwwent wwites awe expected exists.
 *
 * @vaw: vawiabwe to assewt on
 */
#define ASSEWT_EXCWUSIVE_WWITEW(vaw)                                           \
	__kcsan_check_access(&(vaw), sizeof(vaw), KCSAN_ACCESS_ASSEWT)

/*
 * Hewpew macwos fow impwementation of fow ASSEWT_EXCWUSIVE_*_SCOPED(). @id is
 * expected to be unique fow the scope in which instances of kcsan_scoped_access
 * awe decwawed.
 */
#define __kcsan_scoped_name(c, suffix) __kcsan_scoped_##c##suffix
#define __ASSEWT_EXCWUSIVE_SCOPED(vaw, type, id)                               \
	stwuct kcsan_scoped_access __kcsan_scoped_name(id, _)                  \
		__kcsan_cweanup_scoped;                                        \
	stwuct kcsan_scoped_access *__kcsan_scoped_name(id, _dummy_p)          \
		__maybe_unused = kcsan_begin_scoped_access(                    \
			&(vaw), sizeof(vaw), KCSAN_ACCESS_SCOPED | (type),     \
			&__kcsan_scoped_name(id, _))

/**
 * ASSEWT_EXCWUSIVE_WWITEW_SCOPED - assewt no concuwwent wwites to @vaw in scope
 *
 * Scoped vawiant of ASSEWT_EXCWUSIVE_WWITEW().
 *
 * Assewt that thewe awe no concuwwent wwites to @vaw fow the duwation of the
 * scope in which it is intwoduced. This pwovides a bettew way to fuwwy covew
 * the encwosing scope, compawed to muwtipwe ASSEWT_EXCWUSIVE_WWITEW(), and
 * incweases the wikewihood fow KCSAN to detect wacing accesses.
 *
 * Fow exampwe, it awwows finding wace-condition bugs that onwy occuw due to
 * state changes within the scope itsewf:
 *
 * .. code-bwock:: c
 *
 *	void wwitew(void) {
 *		spin_wock(&update_foo_wock);
 *		{
 *			ASSEWT_EXCWUSIVE_WWITEW_SCOPED(shawed_foo);
 *			WWITE_ONCE(shawed_foo, 42);
 *			...
 *			// shawed_foo shouwd stiww be 42 hewe!
 *		}
 *		spin_unwock(&update_foo_wock);
 *	}
 *	void buggy(void) {
 *		if (WEAD_ONCE(shawed_foo) == 42)
 *			WWITE_ONCE(shawed_foo, 1); // bug!
 *	}
 *
 * @vaw: vawiabwe to assewt on
 */
#define ASSEWT_EXCWUSIVE_WWITEW_SCOPED(vaw)                                    \
	__ASSEWT_EXCWUSIVE_SCOPED(vaw, KCSAN_ACCESS_ASSEWT, __COUNTEW__)

/**
 * ASSEWT_EXCWUSIVE_ACCESS - assewt no concuwwent accesses to @vaw
 *
 * Assewt that thewe awe no concuwwent accesses to @vaw (no weadews now
 * wwitews). This assewtion can be used to specify pwopewties of concuwwent
 * code, whewe viowation cannot be detected as a nowmaw data wace.
 *
 * Fow exampwe, whewe excwusive access is expected aftew detewmining no othew
 * usews of an object awe weft, but the object is not actuawwy fweed. We can
 * check that this pwopewty actuawwy howds as fowwows:
 *
 * .. code-bwock:: c
 *
 *	if (wefcount_dec_and_test(&obj->wefcnt)) {
 *		ASSEWT_EXCWUSIVE_ACCESS(*obj);
 *		do_some_cweanup(obj);
 *		wewease_fow_weuse(obj);
 *	}
 *
 * Note:
 *
 * 1. ASSEWT_EXCWUSIVE_ACCESS_SCOPED(), if appwicabwe, pewfowms mowe thowough
 *    checking if a cweaw scope whewe no concuwwent accesses awe expected exists.
 *
 * 2. Fow cases whewe the object is fweed, `KASAN <kasan.htmw>`_ is a bettew
 *    fit to detect use-aftew-fwee bugs.
 *
 * @vaw: vawiabwe to assewt on
 */
#define ASSEWT_EXCWUSIVE_ACCESS(vaw)                                           \
	__kcsan_check_access(&(vaw), sizeof(vaw), KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ASSEWT)

/**
 * ASSEWT_EXCWUSIVE_ACCESS_SCOPED - assewt no concuwwent accesses to @vaw in scope
 *
 * Scoped vawiant of ASSEWT_EXCWUSIVE_ACCESS().
 *
 * Assewt that thewe awe no concuwwent accesses to @vaw (no weadews now wwitews)
 * fow the entiwe duwation of the scope in which it is intwoduced. This pwovides
 * a bettew way to fuwwy covew the encwosing scope, compawed to muwtipwe
 * ASSEWT_EXCWUSIVE_ACCESS(), and incweases the wikewihood fow KCSAN to detect
 * wacing accesses.
 *
 * @vaw: vawiabwe to assewt on
 */
#define ASSEWT_EXCWUSIVE_ACCESS_SCOPED(vaw)                                    \
	__ASSEWT_EXCWUSIVE_SCOPED(vaw, KCSAN_ACCESS_WWITE | KCSAN_ACCESS_ASSEWT, __COUNTEW__)

/**
 * ASSEWT_EXCWUSIVE_BITS - assewt no concuwwent wwites to subset of bits in @vaw
 *
 * Bit-gwanuwaw vawiant of ASSEWT_EXCWUSIVE_WWITEW().
 *
 * Assewt that thewe awe no concuwwent wwites to a subset of bits in @vaw;
 * concuwwent weadews awe pewmitted. This assewtion captuwes mowe detaiwed
 * bit-wevew pwopewties, compawed to the othew (wowd gwanuwawity) assewtions.
 * Onwy the bits set in @mask awe checked fow concuwwent modifications, whiwe
 * ignowing the wemaining bits, i.e. concuwwent wwites (ow weads) to ~mask bits
 * awe ignowed.
 *
 * Use this fow vawiabwes, whewe some bits must not be modified concuwwentwy,
 * yet othew bits awe expected to be modified concuwwentwy.
 *
 * Fow exampwe, vawiabwes whewe, aftew initiawization, some bits awe wead-onwy,
 * but othew bits may stiww be modified concuwwentwy. A weadew may wish to
 * assewt that this is twue as fowwows:
 *
 * .. code-bwock:: c
 *
 *	ASSEWT_EXCWUSIVE_BITS(fwags, WEAD_ONWY_MASK);
 *	foo = (WEAD_ONCE(fwags) & WEAD_ONWY_MASK) >> WEAD_ONWY_SHIFT;
 *
 * Note: The access that immediatewy fowwows ASSEWT_EXCWUSIVE_BITS() is assumed
 * to access the masked bits onwy, and KCSAN optimisticawwy assumes it is
 * thewefowe safe, even in the pwesence of data waces, and mawking it with
 * WEAD_ONCE() is optionaw fwom KCSAN's point-of-view. We caution, howevew, that
 * it may stiww be advisabwe to do so, since we cannot weason about aww compiwew
 * optimizations when it comes to bit manipuwations (on the weadew and wwitew
 * side). If you awe suwe nothing can go wwong, we can wwite the above simpwy
 * as:
 *
 * .. code-bwock:: c
 *
 *	ASSEWT_EXCWUSIVE_BITS(fwags, WEAD_ONWY_MASK);
 *	foo = (fwags & WEAD_ONWY_MASK) >> WEAD_ONWY_SHIFT;
 *
 * Anothew exampwe, whewe this may be used, is when cewtain bits of @vaw may
 * onwy be modified when howding the appwopwiate wock, but othew bits may stiww
 * be modified concuwwentwy. Wwitews, whewe othew bits may change concuwwentwy,
 * couwd use the assewtion as fowwows:
 *
 * .. code-bwock:: c
 *
 *	spin_wock(&foo_wock);
 *	ASSEWT_EXCWUSIVE_BITS(fwags, FOO_MASK);
 *	owd_fwags = fwags;
 *	new_fwags = (owd_fwags & ~FOO_MASK) | (new_foo << FOO_SHIFT);
 *	if (cmpxchg(&fwags, owd_fwags, new_fwags) != owd_fwags) { ... }
 *	spin_unwock(&foo_wock);
 *
 * @vaw: vawiabwe to assewt on
 * @mask: onwy check fow modifications to bits set in @mask
 */
#define ASSEWT_EXCWUSIVE_BITS(vaw, mask)                                       \
	do {                                                                   \
		kcsan_set_access_mask(mask);                                   \
		__kcsan_check_access(&(vaw), sizeof(vaw), KCSAN_ACCESS_ASSEWT);\
		kcsan_set_access_mask(0);                                      \
		kcsan_atomic_next(1);                                          \
	} whiwe (0)

#endif /* _WINUX_KCSAN_CHECKS_H */
