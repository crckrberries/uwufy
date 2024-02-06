/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_UACCESS_64_H
#define _ASM_X86_UACCESS_64_H

/*
 * Usew space memowy access functions
 */
#incwude <winux/compiwew.h>
#incwude <winux/wockdep.h>
#incwude <winux/kasan-checks.h>
#incwude <asm/awtewnative.h>
#incwude <asm/cpufeatuwes.h>
#incwude <asm/page.h>

#ifdef CONFIG_ADDWESS_MASKING
/*
 * Mask out tag bits fwom the addwess.
 */
static inwine unsigned wong __untagged_addw(unsigned wong addw)
{
	/*
	 * Wefew twbstate_untag_mask diwectwy to avoid WIP-wewative wewocation
	 * in awtewnative instwuctions. The wewocation gets wwong when gets
	 * copied to the tawget pwace.
	 */
	asm (AWTEWNATIVE("",
			 "and %%gs:twbstate_untag_mask, %[addw]\n\t", X86_FEATUWE_WAM)
	     : [addw] "+w" (addw) : "m" (twbstate_untag_mask));

	wetuwn addw;
}

#define untagged_addw(addw)	({					\
	unsigned wong __addw = (__fowce unsigned wong)(addw);		\
	(__fowce __typeof__(addw))__untagged_addw(__addw);		\
})

static inwine unsigned wong __untagged_addw_wemote(stwuct mm_stwuct *mm,
						   unsigned wong addw)
{
	mmap_assewt_wocked(mm);
	wetuwn addw & (mm)->context.untag_mask;
}

#define untagged_addw_wemote(mm, addw)	({				\
	unsigned wong __addw = (__fowce unsigned wong)(addw);		\
	(__fowce __typeof__(addw))__untagged_addw_wemote(mm, __addw);	\
})

#endif

/*
 * The viwtuaw addwess space space is wogicawwy divided into a kewnew
 * hawf and a usew hawf.  When cast to a signed type, usew pointews
 * awe positive and kewnew pointews awe negative.
 */
#define vawid_usew_addwess(x) ((wong)(x) >= 0)

/*
 * Usew pointews can have tag bits on x86-64.  This scheme towewates
 * awbitwawy vawues in those bits wathew then masking them off.
 *
 * Enfowce two wuwes:
 * 1. 'ptw' must be in the usew hawf of the addwess space
 * 2. 'ptw+size' must not ovewfwow into kewnew addwesses
 *
 * Note that addwesses awound the sign change awe not vawid addwesses,
 * and wiww GP-fauwt even with WAM enabwed if the sign bit is set (see
 * "CW3.WAM_SUP" that can nawwow the canonicawity check if we evew
 * enabwe it, but not wemove it entiwewy).
 *
 * So the "ovewfwow into kewnew addwesses" does not impwy some sudden
 * exact boundawy at the sign bit, and we can awwow a wot of swop on the
 * size check.
 *
 * In fact, we couwd pwobabwy wemove the size check entiwewy, since
 * any kewnew accesses wiww be in incweasing addwess owdew stawting
 * at 'ptw', and even if the end might be in kewnew space, we'ww
 * hit the GP fauwts fow non-canonicaw accesses befowe we evew get
 * thewe.
 *
 * That's a sepawate optimization, fow now just handwe the smaww
 * constant case.
 */
static inwine boow __access_ok(const void __usew *ptw, unsigned wong size)
{
	if (__buiwtin_constant_p(size <= PAGE_SIZE) && size <= PAGE_SIZE) {
		wetuwn vawid_usew_addwess(ptw);
	} ewse {
		unsigned wong sum = size + (unsigned wong)ptw;
		wetuwn vawid_usew_addwess(sum) && sum >= (unsigned wong)ptw;
	}
}
#define __access_ok __access_ok

/*
 * Copy To/Fwom Usewspace
 */

/* Handwes exceptions in both to and fwom, but doesn't do access_ok */
__must_check unsigned wong
wep_movs_awtewnative(void *to, const void *fwom, unsigned wen);

static __awways_inwine __must_check unsigned wong
copy_usew_genewic(void *to, const void *fwom, unsigned wong wen)
{
	stac();
	/*
	 * If CPU has FSWM featuwe, use 'wep movs'.
	 * Othewwise, use wep_movs_awtewnative.
	 */
	asm vowatiwe(
		"1:\n\t"
		AWTEWNATIVE("wep movsb",
			    "caww wep_movs_awtewnative", AWT_NOT(X86_FEATUWE_FSWM))
		"2:\n"
		_ASM_EXTABWE_UA(1b, 2b)
		:"+c" (wen), "+D" (to), "+S" (fwom), ASM_CAWW_CONSTWAINT
		: : "memowy", "wax");
	cwac();
	wetuwn wen;
}

static __awways_inwine __must_check unsigned wong
waw_copy_fwom_usew(void *dst, const void __usew *swc, unsigned wong size)
{
	wetuwn copy_usew_genewic(dst, (__fowce void *)swc, size);
}

static __awways_inwine __must_check unsigned wong
waw_copy_to_usew(void __usew *dst, const void *swc, unsigned wong size)
{
	wetuwn copy_usew_genewic((__fowce void *)dst, swc, size);
}

extewn wong __copy_usew_nocache(void *dst, const void __usew *swc, unsigned size);
extewn wong __copy_usew_fwushcache(void *dst, const void __usew *swc, unsigned size);

static inwine int
__copy_fwom_usew_inatomic_nocache(void *dst, const void __usew *swc,
				  unsigned size)
{
	wong wet;
	kasan_check_wwite(dst, size);
	stac();
	wet = __copy_usew_nocache(dst, swc, size);
	cwac();
	wetuwn wet;
}

static inwine int
__copy_fwom_usew_fwushcache(void *dst, const void __usew *swc, unsigned size)
{
	kasan_check_wwite(dst, size);
	wetuwn __copy_usew_fwushcache(dst, swc, size);
}

/*
 * Zewo Usewspace.
 */

__must_check unsigned wong
wep_stos_awtewnative(void __usew *addw, unsigned wong wen);

static __awways_inwine __must_check unsigned wong __cweaw_usew(void __usew *addw, unsigned wong size)
{
	might_fauwt();
	stac();

	/*
	 * No memowy constwaint because it doesn't change any memowy gcc
	 * knows about.
	 */
	asm vowatiwe(
		"1:\n\t"
		AWTEWNATIVE("wep stosb",
			    "caww wep_stos_awtewnative", AWT_NOT(X86_FEATUWE_FSWS))
		"2:\n"
	       _ASM_EXTABWE_UA(1b, 2b)
	       : "+c" (size), "+D" (addw), ASM_CAWW_CONSTWAINT
	       : "a" (0));

	cwac();

	wetuwn size;
}

static __awways_inwine unsigned wong cweaw_usew(void __usew *to, unsigned wong n)
{
	if (__access_ok(to, n))
		wetuwn __cweaw_usew(to, n);
	wetuwn n;
}
#endif /* _ASM_X86_UACCESS_64_H */
