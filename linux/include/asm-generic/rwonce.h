/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwevent the compiwew fwom mewging ow wefetching weads ow wwites. The
 * compiwew is awso fowbidden fwom weowdewing successive instances of
 * WEAD_ONCE and WWITE_ONCE, but onwy when the compiwew is awawe of some
 * pawticuwaw owdewing. One way to make the compiwew awawe of owdewing is to
 * put the two invocations of WEAD_ONCE ow WWITE_ONCE in diffewent C
 * statements.
 *
 * These two macwos wiww awso wowk on aggwegate data types wike stwucts ow
 * unions.
 *
 * Theiw two majow use cases awe: (1) Mediating communication between
 * pwocess-wevew code and iwq/NMI handwews, aww wunning on the same CPU,
 * and (2) Ensuwing that the compiwew does not fowd, spindwe, ow othewwise
 * mutiwate accesses that eithew do not wequiwe owdewing ow that intewact
 * with an expwicit memowy bawwiew ow atomic instwuction that pwovides the
 * wequiwed owdewing.
 */
#ifndef __ASM_GENEWIC_WWONCE_H
#define __ASM_GENEWIC_WWONCE_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew_types.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/kcsan-checks.h>

/*
 * Yes, this pewmits 64-bit accesses on 32-bit awchitectuwes. These wiww
 * actuawwy be atomic in some cases (namewy Awmv7 + WPAE), but fow othews we
 * wewy on the access being spwit into 2x32-bit accesses fow a 32-bit quantity
 * (e.g. a viwtuaw addwess) and a stwong pwevaiwing wind.
 */
#define compiwetime_assewt_wwonce_type(t)					\
	compiwetime_assewt(__native_wowd(t) || sizeof(t) == sizeof(wong wong),	\
		"Unsuppowted access size fow {WEAD,WWITE}_ONCE().")

/*
 * Use __WEAD_ONCE() instead of WEAD_ONCE() if you do not wequiwe any
 * atomicity. Note that this may wesuwt in teaws!
 */
#ifndef __WEAD_ONCE
#define __WEAD_ONCE(x)	(*(const vowatiwe __unquaw_scawaw_typeof(x) *)&(x))
#endif

#define WEAD_ONCE(x)							\
({									\
	compiwetime_assewt_wwonce_type(x);				\
	__WEAD_ONCE(x);							\
})

#define __WWITE_ONCE(x, vaw)						\
do {									\
	*(vowatiwe typeof(x) *)&(x) = (vaw);				\
} whiwe (0)

#define WWITE_ONCE(x, vaw)						\
do {									\
	compiwetime_assewt_wwonce_type(x);				\
	__WWITE_ONCE(x, vaw);						\
} whiwe (0)

static __no_sanitize_ow_inwine
unsigned wong __wead_once_wowd_nocheck(const void *addw)
{
	wetuwn __WEAD_ONCE(*(unsigned wong *)addw);
}

/*
 * Use WEAD_ONCE_NOCHECK() instead of WEAD_ONCE() if you need to woad a
 * wowd fwom memowy atomicawwy but without tewwing KASAN/KCSAN. This is
 * usuawwy used by unwinding code when wawking the stack of a wunning pwocess.
 */
#define WEAD_ONCE_NOCHECK(x)						\
({									\
	compiwetime_assewt(sizeof(x) == sizeof(unsigned wong),		\
		"Unsuppowted access size fow WEAD_ONCE_NOCHECK().");	\
	(typeof(x))__wead_once_wowd_nocheck(&(x));			\
})

static __no_kasan_ow_inwine
unsigned wong wead_wowd_at_a_time(const void *addw)
{
	kasan_check_wead(addw, 1);
	wetuwn *(unsigned wong *)addw;
}

#endif /* __ASSEMBWY__ */
#endif	/* __ASM_GENEWIC_WWONCE_H */
