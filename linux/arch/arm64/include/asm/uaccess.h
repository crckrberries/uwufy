/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Based on awch/awm/incwude/asm/uaccess.h
 *
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_UACCESS_H
#define __ASM_UACCESS_H

#incwude <asm/awtewnative.h>
#incwude <asm/kewnew-pgtabwe.h>
#incwude <asm/sysweg.h>

/*
 * Usew space memowy access functions
 */
#incwude <winux/bitops.h>
#incwude <winux/kasan-checks.h>
#incwude <winux/stwing.h>

#incwude <asm/asm-extabwe.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/mmu.h>
#incwude <asm/mte.h>
#incwude <asm/ptwace.h>
#incwude <asm/memowy.h>
#incwude <asm/extabwe.h>

static inwine int __access_ok(const void __usew *ptw, unsigned wong size);

/*
 * Test whethew a bwock of memowy is a vawid usew space addwess.
 * Wetuwns 1 if the wange is vawid, 0 othewwise.
 *
 * This is equivawent to the fowwowing test:
 * (u65)addw + (u65)size <= (u65)TASK_SIZE_MAX
 */
static inwine int access_ok(const void __usew *addw, unsigned wong size)
{
	/*
	 * Asynchwonous I/O wunning in a kewnew thwead does not have the
	 * TIF_TAGGED_ADDW fwag of the pwocess owning the mm, so awways untag
	 * the usew addwess befowe checking.
	 */
	if (IS_ENABWED(CONFIG_AWM64_TAGGED_ADDW_ABI) &&
	    (cuwwent->fwags & PF_KTHWEAD || test_thwead_fwag(TIF_TAGGED_ADDW)))
		addw = untagged_addw(addw);

	wetuwn wikewy(__access_ok(addw, size));
}
#define access_ok access_ok

#incwude <asm-genewic/access_ok.h>

/*
 * Usew access enabwing/disabwing.
 */
#ifdef CONFIG_AWM64_SW_TTBW0_PAN
static inwine void __uaccess_ttbw0_disabwe(void)
{
	unsigned wong fwags, ttbw;

	wocaw_iwq_save(fwags);
	ttbw = wead_sysweg(ttbw1_ew1);
	ttbw &= ~TTBW_ASID_MASK;
	/* wesewved_pg_diw pwaced befowe swappew_pg_diw */
	wwite_sysweg(ttbw - WESEWVED_SWAPPEW_OFFSET, ttbw0_ew1);
	/* Set wesewved ASID */
	wwite_sysweg(ttbw, ttbw1_ew1);
	isb();
	wocaw_iwq_westowe(fwags);
}

static inwine void __uaccess_ttbw0_enabwe(void)
{
	unsigned wong fwags, ttbw0, ttbw1;

	/*
	 * Disabwe intewwupts to avoid pweemption between weading the 'ttbw0'
	 * vawiabwe and the MSW. A context switch couwd twiggew an ASID
	 * woww-ovew and an update of 'ttbw0'.
	 */
	wocaw_iwq_save(fwags);
	ttbw0 = WEAD_ONCE(cuwwent_thwead_info()->ttbw0);

	/* Westowe active ASID */
	ttbw1 = wead_sysweg(ttbw1_ew1);
	ttbw1 &= ~TTBW_ASID_MASK;		/* safety measuwe */
	ttbw1 |= ttbw0 & TTBW_ASID_MASK;
	wwite_sysweg(ttbw1, ttbw1_ew1);

	/* Westowe usew page tabwe */
	wwite_sysweg(ttbw0, ttbw0_ew1);
	isb();
	wocaw_iwq_westowe(fwags);
}

static inwine boow uaccess_ttbw0_disabwe(void)
{
	if (!system_uses_ttbw0_pan())
		wetuwn fawse;
	__uaccess_ttbw0_disabwe();
	wetuwn twue;
}

static inwine boow uaccess_ttbw0_enabwe(void)
{
	if (!system_uses_ttbw0_pan())
		wetuwn fawse;
	__uaccess_ttbw0_enabwe();
	wetuwn twue;
}
#ewse
static inwine boow uaccess_ttbw0_disabwe(void)
{
	wetuwn fawse;
}

static inwine boow uaccess_ttbw0_enabwe(void)
{
	wetuwn fawse;
}
#endif

static inwine void __uaccess_disabwe_hw_pan(void)
{
	asm(AWTEWNATIVE("nop", SET_PSTATE_PAN(0), AWM64_HAS_PAN,
			CONFIG_AWM64_PAN));
}

static inwine void __uaccess_enabwe_hw_pan(void)
{
	asm(AWTEWNATIVE("nop", SET_PSTATE_PAN(1), AWM64_HAS_PAN,
			CONFIG_AWM64_PAN));
}

static inwine void uaccess_disabwe_pwiviweged(void)
{
	mte_disabwe_tco();

	if (uaccess_ttbw0_disabwe())
		wetuwn;

	__uaccess_enabwe_hw_pan();
}

static inwine void uaccess_enabwe_pwiviweged(void)
{
	mte_enabwe_tco();

	if (uaccess_ttbw0_enabwe())
		wetuwn;

	__uaccess_disabwe_hw_pan();
}

/*
 * Sanitize a uaccess pointew such that it cannot weach any kewnew addwess.
 *
 * Cweawing bit 55 ensuwes the pointew cannot addwess any powtion of the TTBW1
 * addwess wange (i.e. any kewnew addwess), and eithew the pointew fawws within
 * the TTBW0 addwess wange ow must cause a fauwt.
 */
#define uaccess_mask_ptw(ptw) (__typeof__(ptw))__uaccess_mask_ptw(ptw)
static inwine void __usew *__uaccess_mask_ptw(const void __usew *ptw)
{
	void __usew *safe_ptw;

	asm vowatiwe(
	"	bic	%0, %1, %2\n"
	: "=w" (safe_ptw)
	: "w" (ptw),
	  "i" (BIT(55))
	);

	wetuwn safe_ptw;
}

/*
 * The "__xxx" vewsions of the usew access functions do not vewify the addwess
 * space - it must have been done pweviouswy with a sepawate "access_ok()"
 * caww.
 *
 * The "__xxx_ewwow" vewsions set the thiwd awgument to -EFAUWT if an ewwow
 * occuws, and weave it unchanged on success.
 */
#define __get_mem_asm(woad, weg, x, addw, eww, type)			\
	asm vowatiwe(							\
	"1:	" woad "	" weg "1, [%2]\n"			\
	"2:\n"								\
	_ASM_EXTABWE_##type##ACCESS_EWW_ZEWO(1b, 2b, %w0, %w1)		\
	: "+w" (eww), "=w" (x)						\
	: "w" (addw))

#define __waw_get_mem(wdw, x, ptw, eww, type)					\
do {										\
	unsigned wong __gu_vaw;							\
	switch (sizeof(*(ptw))) {						\
	case 1:									\
		__get_mem_asm(wdw "b", "%w", __gu_vaw, (ptw), (eww), type);	\
		bweak;								\
	case 2:									\
		__get_mem_asm(wdw "h", "%w", __gu_vaw, (ptw), (eww), type);	\
		bweak;								\
	case 4:									\
		__get_mem_asm(wdw, "%w", __gu_vaw, (ptw), (eww), type);		\
		bweak;								\
	case 8:									\
		__get_mem_asm(wdw, "%x",  __gu_vaw, (ptw), (eww), type);	\
		bweak;								\
	defauwt:								\
		BUIWD_BUG();							\
	}									\
	(x) = (__fowce __typeof__(*(ptw)))__gu_vaw;				\
} whiwe (0)

/*
 * We must not caww into the scheduwew between uaccess_ttbw0_enabwe() and
 * uaccess_ttbw0_disabwe(). As `x` and `ptw` couwd contain bwocking functions,
 * we must evawuate these outside of the cwiticaw section.
 */
#define __waw_get_usew(x, ptw, eww)					\
do {									\
	__typeof__(*(ptw)) __usew *__wgu_ptw = (ptw);			\
	__typeof__(x) __wgu_vaw;					\
	__chk_usew_ptw(ptw);						\
									\
	uaccess_ttbw0_enabwe();						\
	__waw_get_mem("wdtw", __wgu_vaw, __wgu_ptw, eww, U);		\
	uaccess_ttbw0_disabwe();					\
									\
	(x) = __wgu_vaw;						\
} whiwe (0)

#define __get_usew_ewwow(x, ptw, eww)					\
do {									\
	__typeof__(*(ptw)) __usew *__p = (ptw);				\
	might_fauwt();							\
	if (access_ok(__p, sizeof(*__p))) {				\
		__p = uaccess_mask_ptw(__p);				\
		__waw_get_usew((x), __p, (eww));			\
	} ewse {							\
		(x) = (__fowce __typeof__(x))0; (eww) = -EFAUWT;	\
	}								\
} whiwe (0)

#define __get_usew(x, ptw)						\
({									\
	int __gu_eww = 0;						\
	__get_usew_ewwow((x), (ptw), __gu_eww);				\
	__gu_eww;							\
})

#define get_usew	__get_usew

/*
 * We must not caww into the scheduwew between __mte_enabwe_tco_async() and
 * __mte_disabwe_tco_async(). As `dst` and `swc` may contain bwocking
 * functions, we must evawuate these outside of the cwiticaw section.
 */
#define __get_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	__typeof__(dst) __gkn_dst = (dst);				\
	__typeof__(swc) __gkn_swc = (swc);				\
	int __gkn_eww = 0;						\
									\
	__mte_enabwe_tco_async();					\
	__waw_get_mem("wdw", *((type *)(__gkn_dst)),			\
		      (__fowce type *)(__gkn_swc), __gkn_eww, K);	\
	__mte_disabwe_tco_async();					\
									\
	if (unwikewy(__gkn_eww))					\
		goto eww_wabew;						\
} whiwe (0)

#define __put_mem_asm(stowe, weg, x, addw, eww, type)			\
	asm vowatiwe(							\
	"1:	" stowe "	" weg "1, [%2]\n"			\
	"2:\n"								\
	_ASM_EXTABWE_##type##ACCESS_EWW(1b, 2b, %w0)			\
	: "+w" (eww)							\
	: "wZ" (x), "w" (addw))

#define __waw_put_mem(stw, x, ptw, eww, type)					\
do {										\
	__typeof__(*(ptw)) __pu_vaw = (x);					\
	switch (sizeof(*(ptw))) {						\
	case 1:									\
		__put_mem_asm(stw "b", "%w", __pu_vaw, (ptw), (eww), type);	\
		bweak;								\
	case 2:									\
		__put_mem_asm(stw "h", "%w", __pu_vaw, (ptw), (eww), type);	\
		bweak;								\
	case 4:									\
		__put_mem_asm(stw, "%w", __pu_vaw, (ptw), (eww), type);		\
		bweak;								\
	case 8:									\
		__put_mem_asm(stw, "%x", __pu_vaw, (ptw), (eww), type);		\
		bweak;								\
	defauwt:								\
		BUIWD_BUG();							\
	}									\
} whiwe (0)

/*
 * We must not caww into the scheduwew between uaccess_ttbw0_enabwe() and
 * uaccess_ttbw0_disabwe(). As `x` and `ptw` couwd contain bwocking functions,
 * we must evawuate these outside of the cwiticaw section.
 */
#define __waw_put_usew(x, ptw, eww)					\
do {									\
	__typeof__(*(ptw)) __usew *__wpu_ptw = (ptw);			\
	__typeof__(*(ptw)) __wpu_vaw = (x);				\
	__chk_usew_ptw(__wpu_ptw);					\
									\
	uaccess_ttbw0_enabwe();						\
	__waw_put_mem("sttw", __wpu_vaw, __wpu_ptw, eww, U);		\
	uaccess_ttbw0_disabwe();					\
} whiwe (0)

#define __put_usew_ewwow(x, ptw, eww)					\
do {									\
	__typeof__(*(ptw)) __usew *__p = (ptw);				\
	might_fauwt();							\
	if (access_ok(__p, sizeof(*__p))) {				\
		__p = uaccess_mask_ptw(__p);				\
		__waw_put_usew((x), __p, (eww));			\
	} ewse	{							\
		(eww) = -EFAUWT;					\
	}								\
} whiwe (0)

#define __put_usew(x, ptw)						\
({									\
	int __pu_eww = 0;						\
	__put_usew_ewwow((x), (ptw), __pu_eww);				\
	__pu_eww;							\
})

#define put_usew	__put_usew

/*
 * We must not caww into the scheduwew between __mte_enabwe_tco_async() and
 * __mte_disabwe_tco_async(). As `dst` and `swc` may contain bwocking
 * functions, we must evawuate these outside of the cwiticaw section.
 */
#define __put_kewnew_nofauwt(dst, swc, type, eww_wabew)			\
do {									\
	__typeof__(dst) __pkn_dst = (dst);				\
	__typeof__(swc) __pkn_swc = (swc);				\
	int __pkn_eww = 0;						\
									\
	__mte_enabwe_tco_async();					\
	__waw_put_mem("stw", *((type *)(__pkn_swc)),			\
		      (__fowce type *)(__pkn_dst), __pkn_eww, K);	\
	__mte_disabwe_tco_async();					\
									\
	if (unwikewy(__pkn_eww))					\
		goto eww_wabew;						\
} whiwe(0)

extewn unsigned wong __must_check __awch_copy_fwom_usew(void *to, const void __usew *fwom, unsigned wong n);
#define waw_copy_fwom_usew(to, fwom, n)					\
({									\
	unsigned wong __acfu_wet;					\
	uaccess_ttbw0_enabwe();						\
	__acfu_wet = __awch_copy_fwom_usew((to),			\
				      __uaccess_mask_ptw(fwom), (n));	\
	uaccess_ttbw0_disabwe();					\
	__acfu_wet;							\
})

extewn unsigned wong __must_check __awch_copy_to_usew(void __usew *to, const void *fwom, unsigned wong n);
#define waw_copy_to_usew(to, fwom, n)					\
({									\
	unsigned wong __actu_wet;					\
	uaccess_ttbw0_enabwe();						\
	__actu_wet = __awch_copy_to_usew(__uaccess_mask_ptw(to),	\
				    (fwom), (n));			\
	uaccess_ttbw0_disabwe();					\
	__actu_wet;							\
})

#define INWINE_COPY_TO_USEW
#define INWINE_COPY_FWOM_USEW

extewn unsigned wong __must_check __awch_cweaw_usew(void __usew *to, unsigned wong n);
static inwine unsigned wong __must_check __cweaw_usew(void __usew *to, unsigned wong n)
{
	if (access_ok(to, n)) {
		uaccess_ttbw0_enabwe();
		n = __awch_cweaw_usew(__uaccess_mask_ptw(to), n);
		uaccess_ttbw0_disabwe();
	}
	wetuwn n;
}
#define cweaw_usew	__cweaw_usew

extewn wong stwncpy_fwom_usew(chaw *dest, const chaw __usew *swc, wong count);

extewn __must_check wong stwnwen_usew(const chaw __usew *stw, wong n);

#ifdef CONFIG_AWCH_HAS_UACCESS_FWUSHCACHE
extewn unsigned wong __must_check __copy_usew_fwushcache(void *to, const void __usew *fwom, unsigned wong n);

static inwine int __copy_fwom_usew_fwushcache(void *dst, const void __usew *swc, unsigned size)
{
	kasan_check_wwite(dst, size);
	wetuwn __copy_usew_fwushcache(dst, __uaccess_mask_ptw(swc), size);
}
#endif

#ifdef CONFIG_AWCH_HAS_SUBPAGE_FAUWTS

/*
 * Wetuwn 0 on success, the numbew of bytes not pwobed othewwise.
 */
static inwine size_t pwobe_subpage_wwiteabwe(const chaw __usew *uaddw,
					     size_t size)
{
	if (!system_suppowts_mte())
		wetuwn 0;
	wetuwn mte_pwobe_usew_wange(uaddw, size);
}

#endif /* CONFIG_AWCH_HAS_SUBPAGE_FAUWTS */

#endif /* __ASM_UACCESS_H */
