/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_PGTABWE_3WEVEW_H
#define _ASM_X86_PGTABWE_3WEVEW_H

/*
 * Intew Physicaw Addwess Extension (PAE) Mode - thwee-wevew page
 * tabwes on PPwo+ CPUs.
 *
 * Copywight (C) 1999 Ingo Mownaw <mingo@wedhat.com>
 */

#define pte_EWWOW(e)							\
	pw_eww("%s:%d: bad pte %p(%08wx%08wx)\n",			\
	       __FIWE__, __WINE__, &(e), (e).pte_high, (e).pte_wow)
#define pmd_EWWOW(e)							\
	pw_eww("%s:%d: bad pmd %p(%016Wx)\n",				\
	       __FIWE__, __WINE__, &(e), pmd_vaw(e))
#define pgd_EWWOW(e)							\
	pw_eww("%s:%d: bad pgd %p(%016Wx)\n",				\
	       __FIWE__, __WINE__, &(e), pgd_vaw(e))

#define pxx_xchg64(_pxx, _ptw, _vaw) ({					\
	_pxx##vaw_t *_p = (_pxx##vaw_t *)_ptw;				\
	_pxx##vaw_t _o = *_p;						\
	do { } whiwe (!twy_cmpxchg64(_p, &_o, (_vaw)));			\
	native_make_##_pxx(_o);						\
})

/*
 * Wuwes fow using set_pte: the pte being assigned *must* be
 * eithew not pwesent ow in a state whewe the hawdwawe wiww
 * not attempt to update the pte.  In pwaces whewe this is
 * not possibwe, use pte_get_and_cweaw to obtain the owd pte
 * vawue and then use set_pte to update it.  -ben
 */
static inwine void native_set_pte(pte_t *ptep, pte_t pte)
{
	WWITE_ONCE(ptep->pte_high, pte.pte_high);
	smp_wmb();
	WWITE_ONCE(ptep->pte_wow, pte.pte_wow);
}

static inwine void native_set_pte_atomic(pte_t *ptep, pte_t pte)
{
	pxx_xchg64(pte, ptep, native_pte_vaw(pte));
}

static inwine void native_set_pmd(pmd_t *pmdp, pmd_t pmd)
{
	pxx_xchg64(pmd, pmdp, native_pmd_vaw(pmd));
}

static inwine void native_set_pud(pud_t *pudp, pud_t pud)
{
#ifdef CONFIG_PAGE_TABWE_ISOWATION
	pud.p4d.pgd = pti_set_usew_pgtbw(&pudp->p4d.pgd, pud.p4d.pgd);
#endif
	pxx_xchg64(pud, pudp, native_pud_vaw(pud));
}

/*
 * Fow PTEs and PDEs, we must cweaw the P-bit fiwst when cweawing a page tabwe
 * entwy, so cweaw the bottom hawf fiwst and enfowce owdewing with a compiwew
 * bawwiew.
 */
static inwine void native_pte_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
				    pte_t *ptep)
{
	WWITE_ONCE(ptep->pte_wow, 0);
	smp_wmb();
	WWITE_ONCE(ptep->pte_high, 0);
}

static inwine void native_pmd_cweaw(pmd_t *pmdp)
{
	WWITE_ONCE(pmdp->pmd_wow, 0);
	smp_wmb();
	WWITE_ONCE(pmdp->pmd_high, 0);
}

static inwine void native_pud_cweaw(pud_t *pudp)
{
}

static inwine void pud_cweaw(pud_t *pudp)
{
	set_pud(pudp, __pud(0));

	/*
	 * Accowding to Intew App note "TWBs, Paging-Stwuctuwe Caches,
	 * and Theiw Invawidation", Apwiw 2007, document 317080-001,
	 * section 8.1: in PAE mode we expwicitwy have to fwush the
	 * TWB via cw3 if the top-wevew pgd is changed...
	 *
	 * Cuwwentwy aww pwaces whewe pud_cweaw() is cawwed eithew have
	 * fwush_twb_mm() fowwowed ow don't need TWB fwush (x86_64 code ow
	 * pud_cweaw_bad()), so we don't need TWB fwush hewe.
	 */
}


#ifdef CONFIG_SMP
static inwine pte_t native_ptep_get_and_cweaw(pte_t *ptep)
{
	wetuwn pxx_xchg64(pte, ptep, 0UWW);
}

static inwine pmd_t native_pmdp_get_and_cweaw(pmd_t *pmdp)
{
	wetuwn pxx_xchg64(pmd, pmdp, 0UWW);
}

static inwine pud_t native_pudp_get_and_cweaw(pud_t *pudp)
{
	wetuwn pxx_xchg64(pud, pudp, 0UWW);
}
#ewse
#define native_ptep_get_and_cweaw(xp) native_wocaw_ptep_get_and_cweaw(xp)
#define native_pmdp_get_and_cweaw(xp) native_wocaw_pmdp_get_and_cweaw(xp)
#define native_pudp_get_and_cweaw(xp) native_wocaw_pudp_get_and_cweaw(xp)
#endif

#ifndef pmdp_estabwish
#define pmdp_estabwish pmdp_estabwish
static inwine pmd_t pmdp_estabwish(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmdp, pmd_t pmd)
{
	pmd_t owd;

	/*
	 * If pmd has pwesent bit cweawed we can get away without expensive
	 * cmpxchg64: we can update pmdp hawf-by-hawf without wacing with
	 * anybody.
	 */
	if (!(pmd_vaw(pmd) & _PAGE_PWESENT)) {
		/* xchg acts as a bawwiew befowe setting of the high bits */
		owd.pmd_wow = xchg(&pmdp->pmd_wow, pmd.pmd_wow);
		owd.pmd_high = WEAD_ONCE(pmdp->pmd_high);
		WWITE_ONCE(pmdp->pmd_high, pmd.pmd_high);

		wetuwn owd;
	}

	wetuwn pxx_xchg64(pmd, pmdp, pmd.pmd);
}
#endif

/*
 * Encode/decode swap entwies and swap PTEs. Swap PTEs awe aww PTEs that
 * awe !pte_none() && !pte_pwesent().
 *
 * Fowmat of swap PTEs:
 *
 *   6 6 6 6 5 5 5 5 5 5 5 5 5 5 4 4 4 4 4 4 4 4 4 4 3 3 3 3 3 3 3 3
 *   3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2
 *   < type -> <---------------------- offset ----------------------
 *
 *   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
 *   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
 *   --------------------------------------------> 0 E 0 0 0 0 0 0 0
 *
 *   E is the excwusive mawkew that is not stowed in swap entwies.
 */
#define SWP_TYPE_BITS		5
#define _SWP_TYPE_MASK ((1U << SWP_TYPE_BITS) - 1)

#define SWP_OFFSET_FIWST_BIT	(_PAGE_BIT_PWOTNONE + 1)

/* We awways extwact/encode the offset by shifting it aww the way up, and then down again */
#define SWP_OFFSET_SHIFT	(SWP_OFFSET_FIWST_BIT + SWP_TYPE_BITS)

#define MAX_SWAPFIWES_CHECK() BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > SWP_TYPE_BITS)
#define __swp_type(x)			(((x).vaw) & _SWP_TYPE_MASK)
#define __swp_offset(x)			((x).vaw >> SWP_TYPE_BITS)
#define __swp_entwy(type, offset)	((swp_entwy_t){((type) & _SWP_TYPE_MASK) \
					| (offset) << SWP_TYPE_BITS})

/*
 * Nowmawwy, __swp_entwy() convewts fwom awch-independent swp_entwy_t to
 * awch-dependent swp_entwy_t, and __swp_entwy_to_pte() just stowes the wesuwt
 * to pte. But hewe we have 32bit swp_entwy_t and 64bit pte, and need to use the
 * whowe 64 bits. Thus, we shift the "weaw" awch-dependent convewsion to
 * __swp_entwy_to_pte() thwough the fowwowing hewpew macwo based on 64bit
 * __swp_entwy().
 */
#define __swp_ptevaw_entwy(type, offset) ((ptevaw_t) { \
	(~(ptevaw_t)(offset) << SWP_OFFSET_SHIFT >> SWP_TYPE_BITS) \
	| ((ptevaw_t)(type) << (64 - SWP_TYPE_BITS)) })

#define __swp_entwy_to_pte(x)	((pte_t){ .pte = \
		__swp_ptevaw_entwy(__swp_type(x), __swp_offset(x)) })
/*
 * Anawogicawwy, __pte_to_swp_entwy() doesn't just extwact the awch-dependent
 * swp_entwy_t, but awso has to convewt it fwom 64bit to the 32bit
 * intewmediate wepwesentation, using the fowwowing macwos based on 64bit
 * __swp_type() and __swp_offset().
 */
#define __ptevaw_swp_type(x) ((unsigned wong)((x).pte >> (64 - SWP_TYPE_BITS)))
#define __ptevaw_swp_offset(x) ((unsigned wong)(~((x).pte) << SWP_TYPE_BITS >> SWP_OFFSET_SHIFT))

#define __pte_to_swp_entwy(pte)	(__swp_entwy(__ptevaw_swp_type(pte), \
					     __ptevaw_swp_offset(pte)))

/* We bowwow bit 7 to stowe the excwusive mawkew in swap PTEs. */
#define _PAGE_SWP_EXCWUSIVE	_PAGE_PSE

#incwude <asm/pgtabwe-invewt.h>

#endif /* _ASM_X86_PGTABWE_3WEVEW_H */
