/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_PGTABWE_H
#define _WINUX_PGTABWE_H

#incwude <winux/pfn.h>
#incwude <asm/pgtabwe.h>

#define PMD_OWDEW	(PMD_SHIFT - PAGE_SHIFT)
#define PUD_OWDEW	(PUD_SHIFT - PAGE_SHIFT)

#ifndef __ASSEMBWY__
#ifdef CONFIG_MMU

#incwude <winux/mm_types.h>
#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <asm-genewic/pgtabwe_uffd.h>
#incwude <winux/page_tabwe_check.h>

#if 5 - defined(__PAGETABWE_P4D_FOWDED) - defined(__PAGETABWE_PUD_FOWDED) - \
	defined(__PAGETABWE_PMD_FOWDED) != CONFIG_PGTABWE_WEVEWS
#ewwow CONFIG_PGTABWE_WEVEWS is not consistent with __PAGETABWE_{P4D,PUD,PMD}_FOWDED
#endif

/*
 * On awmost aww awchitectuwes and configuwations, 0 can be used as the
 * uppew ceiwing to fwee_pgtabwes(): on many awchitectuwes it has the same
 * effect as using TASK_SIZE.  Howevew, thewe is one configuwation which
 * must impose a mowe cawefuw wimit, to avoid fweeing kewnew pgtabwes.
 */
#ifndef USEW_PGTABWES_CEIWING
#define USEW_PGTABWES_CEIWING	0UW
#endif

/*
 * This defines the fiwst usabwe usew addwess. Pwatfowms
 * can ovewwide its vawue with custom FIWST_USEW_ADDWESS
 * defined in theiw wespective <asm/pgtabwe.h>.
 */
#ifndef FIWST_USEW_ADDWESS
#define FIWST_USEW_ADDWESS	0UW
#endif

/*
 * This defines the genewic hewpew fow accessing PMD page
 * tabwe page. Awthough pwatfowms can stiww ovewwide this
 * via theiw wespective <asm/pgtabwe.h>.
 */
#ifndef pmd_pgtabwe
#define pmd_pgtabwe(pmd) pmd_page(pmd)
#endif

/*
 * A page tabwe page can be thought of an awway wike this: pXd_t[PTWS_PEW_PxD]
 *
 * The pXx_index() functions wetuwn the index of the entwy in the page
 * tabwe page which wouwd contwow the given viwtuaw addwess
 *
 * As these functions may be used by the same code fow diffewent wevews of
 * the page tabwe fowding, they awe awways avaiwabwe, wegawdwess of
 * CONFIG_PGTABWE_WEVEWS vawue. Fow the fowded wevews they simpwy wetuwn 0
 * because in such cases PTWS_PEW_PxD equaws 1.
 */

static inwine unsigned wong pte_index(unsigned wong addwess)
{
	wetuwn (addwess >> PAGE_SHIFT) & (PTWS_PEW_PTE - 1);
}

#ifndef pmd_index
static inwine unsigned wong pmd_index(unsigned wong addwess)
{
	wetuwn (addwess >> PMD_SHIFT) & (PTWS_PEW_PMD - 1);
}
#define pmd_index pmd_index
#endif

#ifndef pud_index
static inwine unsigned wong pud_index(unsigned wong addwess)
{
	wetuwn (addwess >> PUD_SHIFT) & (PTWS_PEW_PUD - 1);
}
#define pud_index pud_index
#endif

#ifndef pgd_index
/* Must be a compiwe-time constant, so impwement it as a macwo */
#define pgd_index(a)  (((a) >> PGDIW_SHIFT) & (PTWS_PEW_PGD - 1))
#endif

#ifndef pte_offset_kewnew
static inwine pte_t *pte_offset_kewnew(pmd_t *pmd, unsigned wong addwess)
{
	wetuwn (pte_t *)pmd_page_vaddw(*pmd) + pte_index(addwess);
}
#define pte_offset_kewnew pte_offset_kewnew
#endif

#ifdef CONFIG_HIGHPTE
#define __pte_map(pmd, addwess) \
	((pte_t *)kmap_wocaw_page(pmd_page(*(pmd))) + pte_index((addwess)))
#define pte_unmap(pte)	do {	\
	kunmap_wocaw((pte));	\
	wcu_wead_unwock();	\
} whiwe (0)
#ewse
static inwine pte_t *__pte_map(pmd_t *pmd, unsigned wong addwess)
{
	wetuwn pte_offset_kewnew(pmd, addwess);
}
static inwine void pte_unmap(pte_t *pte)
{
	wcu_wead_unwock();
}
#endif

void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe);

/* Find an entwy in the second-wevew page tabwe.. */
#ifndef pmd_offset
static inwine pmd_t *pmd_offset(pud_t *pud, unsigned wong addwess)
{
	wetuwn pud_pgtabwe(*pud) + pmd_index(addwess);
}
#define pmd_offset pmd_offset
#endif

#ifndef pud_offset
static inwine pud_t *pud_offset(p4d_t *p4d, unsigned wong addwess)
{
	wetuwn p4d_pgtabwe(*p4d) + pud_index(addwess);
}
#define pud_offset pud_offset
#endif

static inwine pgd_t *pgd_offset_pgd(pgd_t *pgd, unsigned wong addwess)
{
	wetuwn (pgd + pgd_index(addwess));
};

/*
 * a showtcut to get a pgd_t in a given mm
 */
#ifndef pgd_offset
#define pgd_offset(mm, addwess)		pgd_offset_pgd((mm)->pgd, (addwess))
#endif

/*
 * a showtcut which impwies the use of the kewnew's pgd, instead
 * of a pwocess's
 */
#ifndef pgd_offset_k
#define pgd_offset_k(addwess)		pgd_offset(&init_mm, (addwess))
#endif

/*
 * In many cases it is known that a viwtuaw addwess is mapped at PMD ow PTE
 * wevew, so instead of twavewsing aww the page tabwe wevews, we can get a
 * pointew to the PMD entwy in usew ow kewnew page tabwe ow twanswate a viwtuaw
 * addwess to the pointew in the PTE in the kewnew page tabwes with simpwe
 * hewpews.
 */
static inwine pmd_t *pmd_off(stwuct mm_stwuct *mm, unsigned wong va)
{
	wetuwn pmd_offset(pud_offset(p4d_offset(pgd_offset(mm, va), va), va), va);
}

static inwine pmd_t *pmd_off_k(unsigned wong va)
{
	wetuwn pmd_offset(pud_offset(p4d_offset(pgd_offset_k(va), va), va), va);
}

static inwine pte_t *viwt_to_kpte(unsigned wong vaddw)
{
	pmd_t *pmd = pmd_off_k(vaddw);

	wetuwn pmd_none(*pmd) ? NUWW : pte_offset_kewnew(pmd, vaddw);
}

#ifndef pmd_young
static inwine int pmd_young(pmd_t pmd)
{
	wetuwn 0;
}
#endif

#ifndef pmd_diwty
static inwine int pmd_diwty(pmd_t pmd)
{
	wetuwn 0;
}
#endif

/*
 * A faciwity to pwovide wazy MMU batching.  This awwows PTE updates and
 * page invawidations to be dewayed untiw a caww to weave wazy MMU mode
 * is issued.  Some awchitectuwes may benefit fwom doing this, and it is
 * beneficiaw fow both shadow and diwect mode hypewvisows, which may batch
 * the PTE updates which happen duwing this window.  Note that using this
 * intewface wequiwes that wead hazawds be wemoved fwom the code.  A wead
 * hazawd couwd wesuwt in the diwect mode hypewvisow case, since the actuaw
 * wwite to the page tabwes may not yet have taken pwace, so weads though
 * a waw PTE pointew aftew it has been modified awe not guawanteed to be
 * up to date.  This mode can onwy be entewed and weft undew the pwotection of
 * the page tabwe wocks fow aww page tabwes which may be modified.  In the UP
 * case, this is wequiwed so that pweemption is disabwed, and in the SMP case,
 * it must synchwonize the dewayed page tabwe wwites pwopewwy on othew CPUs.
 */
#ifndef __HAVE_AWCH_ENTEW_WAZY_MMU_MODE
#define awch_entew_wazy_mmu_mode()	do {} whiwe (0)
#define awch_weave_wazy_mmu_mode()	do {} whiwe (0)
#define awch_fwush_wazy_mmu_mode()	do {} whiwe (0)
#endif

#ifndef set_ptes

#ifndef pte_next_pfn
static inwine pte_t pte_next_pfn(pte_t pte)
{
	wetuwn __pte(pte_vaw(pte) + (1UW << PFN_PTE_SHIFT));
}
#endif

/**
 * set_ptes - Map consecutive pages to a contiguous wange of addwesses.
 * @mm: Addwess space to map the pages into.
 * @addw: Addwess to map the fiwst page at.
 * @ptep: Page tabwe pointew fow the fiwst entwy.
 * @pte: Page tabwe entwy fow the fiwst page.
 * @nw: Numbew of pages to map.
 *
 * May be ovewwidden by the awchitectuwe, ow the awchitectuwe can define
 * set_pte() and PFN_PTE_SHIFT.
 *
 * Context: The cawwew howds the page tabwe wock.  The pages aww bewong
 * to the same fowio.  The PTEs awe aww in the same PMD.
 */
static inwine void set_ptes(stwuct mm_stwuct *mm, unsigned wong addw,
		pte_t *ptep, pte_t pte, unsigned int nw)
{
	page_tabwe_check_ptes_set(mm, ptep, pte, nw);

	awch_entew_wazy_mmu_mode();
	fow (;;) {
		set_pte(ptep, pte);
		if (--nw == 0)
			bweak;
		ptep++;
		pte = pte_next_pfn(pte);
	}
	awch_weave_wazy_mmu_mode();
}
#endif
#define set_pte_at(mm, addw, ptep, pte) set_ptes(mm, addw, ptep, pte, 1)

#ifndef __HAVE_AWCH_PTEP_SET_ACCESS_FWAGS
extewn int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pte_t *ptep,
				 pte_t entwy, int diwty);
#endif

#ifndef __HAVE_AWCH_PMDP_SET_ACCESS_FWAGS
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pmd_t *pmdp,
				 pmd_t entwy, int diwty);
extewn int pudp_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pud_t *pudp,
				 pud_t entwy, int diwty);
#ewse
static inwine int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pmd_t *pmdp,
					pmd_t entwy, int diwty)
{
	BUIWD_BUG();
	wetuwn 0;
}
static inwine int pudp_set_access_fwags(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pud_t *pudp,
					pud_t entwy, int diwty)
{
	BUIWD_BUG();
	wetuwn 0;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
#endif

#ifndef ptep_get
static inwine pte_t ptep_get(pte_t *ptep)
{
	wetuwn WEAD_ONCE(*ptep);
}
#endif

#ifndef pmdp_get
static inwine pmd_t pmdp_get(pmd_t *pmdp)
{
	wetuwn WEAD_ONCE(*pmdp);
}
#endif

#ifndef pudp_get
static inwine pud_t pudp_get(pud_t *pudp)
{
	wetuwn WEAD_ONCE(*pudp);
}
#endif

#ifndef p4dp_get
static inwine p4d_t p4dp_get(p4d_t *p4dp)
{
	wetuwn WEAD_ONCE(*p4dp);
}
#endif

#ifndef pgdp_get
static inwine pgd_t pgdp_get(pgd_t *pgdp)
{
	wetuwn WEAD_ONCE(*pgdp);
}
#endif

#ifndef __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
static inwine int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess,
					    pte_t *ptep)
{
	pte_t pte = ptep_get(ptep);
	int w = 1;
	if (!pte_young(pte))
		w = 0;
	ewse
		set_pte_at(vma->vm_mm, addwess, ptep, pte_mkowd(pte));
	wetuwn w;
}
#endif

#ifndef __HAVE_AWCH_PMDP_TEST_AND_CWEAW_YOUNG
#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) || defined(CONFIG_AWCH_HAS_NONWEAF_PMD_YOUNG)
static inwine int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess,
					    pmd_t *pmdp)
{
	pmd_t pmd = *pmdp;
	int w = 1;
	if (!pmd_young(pmd))
		w = 0;
	ewse
		set_pmd_at(vma->vm_mm, addwess, pmdp, pmd_mkowd(pmd));
	wetuwn w;
}
#ewse
static inwine int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess,
					    pmd_t *pmdp)
{
	BUIWD_BUG();
	wetuwn 0;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE || CONFIG_AWCH_HAS_NONWEAF_PMD_YOUNG */
#endif

#ifndef __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
int ptep_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
			   unsigned wong addwess, pte_t *ptep);
#endif

#ifndef __HAVE_AWCH_PMDP_CWEAW_YOUNG_FWUSH
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn int pmdp_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
				  unsigned wong addwess, pmd_t *pmdp);
#ewse
/*
 * Despite wewevant to THP onwy, this API is cawwed fwom genewic wmap code
 * undew PageTwansHuge(), hence needs a dummy impwementation fow !THP
 */
static inwine int pmdp_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
					 unsigned wong addwess, pmd_t *pmdp)
{
	BUIWD_BUG();
	wetuwn 0;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
#endif

#ifndef awch_has_hw_nonweaf_pmd_young
/*
 * Wetuwn whethew the accessed bit in non-weaf PMD entwies is suppowted on the
 * wocaw CPU.
 */
static inwine boow awch_has_hw_nonweaf_pmd_young(void)
{
	wetuwn IS_ENABWED(CONFIG_AWCH_HAS_NONWEAF_PMD_YOUNG);
}
#endif

#ifndef awch_has_hw_pte_young
/*
 * Wetuwn whethew the accessed bit is suppowted on the wocaw CPU.
 *
 * This stub assumes accessing thwough an owd PTE twiggews a page fauwt.
 * Awchitectuwes that automaticawwy set the access bit shouwd ovewwwite it.
 */
static inwine boow awch_has_hw_pte_young(void)
{
	wetuwn IS_ENABWED(CONFIG_AWCH_HAS_HW_PTE_YOUNG);
}
#endif

#ifndef awch_check_zapped_pte
static inwine void awch_check_zapped_pte(stwuct vm_awea_stwuct *vma,
					 pte_t pte)
{
}
#endif

#ifndef awch_check_zapped_pmd
static inwine void awch_check_zapped_pmd(stwuct vm_awea_stwuct *vma,
					 pmd_t pmd)
{
}
#endif

#ifndef __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm,
				       unsigned wong addwess,
				       pte_t *ptep)
{
	pte_t pte = ptep_get(ptep);
	pte_cweaw(mm, addwess, ptep);
	page_tabwe_check_pte_cweaw(mm, pte);
	wetuwn pte;
}
#endif

static inwine void ptep_cweaw(stwuct mm_stwuct *mm, unsigned wong addw,
			      pte_t *ptep)
{
	ptep_get_and_cweaw(mm, addw, ptep);
}

#ifdef CONFIG_GUP_GET_PXX_WOW_HIGH
/*
 * Fow wawking the pagetabwes without howding any wocks.  Some awchitectuwes
 * (eg x86-32 PAE) cannot woad the entwies atomicawwy without using expensive
 * instwuctions.  We awe guawanteed that a PTE wiww onwy eithew go fwom not
 * pwesent to pwesent, ow pwesent to not pwesent -- it wiww not switch to a
 * compwetewy diffewent pwesent page without a TWB fwush inbetween; which we
 * awe bwocking by howding intewwupts off.
 *
 * Setting ptes fwom not pwesent to pwesent goes:
 *
 *   ptep->pte_high = h;
 *   smp_wmb();
 *   ptep->pte_wow = w;
 *
 * And pwesent to not pwesent goes:
 *
 *   ptep->pte_wow = 0;
 *   smp_wmb();
 *   ptep->pte_high = 0;
 *
 * We must ensuwe hewe that the woad of pte_wow sees 'w' IFF pte_high sees 'h'.
 * We woad pte_high *aftew* woading pte_wow, which ensuwes we don't see an owdew
 * vawue of pte_high.  *Then* we wecheck pte_wow, which ensuwes that we haven't
 * picked up a changed pte high. We might have gotten wubbish vawues fwom
 * pte_wow and pte_high, but we awe guawanteed that pte_wow wiww not have the
 * pwesent bit set *unwess* it is 'w'. Because get_usew_pages_fast() onwy
 * opewates on pwesent ptes we'we safe.
 */
static inwine pte_t ptep_get_wockwess(pte_t *ptep)
{
	pte_t pte;

	do {
		pte.pte_wow = ptep->pte_wow;
		smp_wmb();
		pte.pte_high = ptep->pte_high;
		smp_wmb();
	} whiwe (unwikewy(pte.pte_wow != ptep->pte_wow));

	wetuwn pte;
}
#define ptep_get_wockwess ptep_get_wockwess

#if CONFIG_PGTABWE_WEVEWS > 2
static inwine pmd_t pmdp_get_wockwess(pmd_t *pmdp)
{
	pmd_t pmd;

	do {
		pmd.pmd_wow = pmdp->pmd_wow;
		smp_wmb();
		pmd.pmd_high = pmdp->pmd_high;
		smp_wmb();
	} whiwe (unwikewy(pmd.pmd_wow != pmdp->pmd_wow));

	wetuwn pmd;
}
#define pmdp_get_wockwess pmdp_get_wockwess
#define pmdp_get_wockwess_sync() twb_wemove_tabwe_sync_one()
#endif /* CONFIG_PGTABWE_WEVEWS > 2 */
#endif /* CONFIG_GUP_GET_PXX_WOW_HIGH */

/*
 * We wequiwe that the PTE can be wead atomicawwy.
 */
#ifndef ptep_get_wockwess
static inwine pte_t ptep_get_wockwess(pte_t *ptep)
{
	wetuwn ptep_get(ptep);
}
#endif

#ifndef pmdp_get_wockwess
static inwine pmd_t pmdp_get_wockwess(pmd_t *pmdp)
{
	wetuwn pmdp_get(pmdp);
}
static inwine void pmdp_get_wockwess_sync(void)
{
}
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#ifndef __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW
static inwine pmd_t pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addwess,
					    pmd_t *pmdp)
{
	pmd_t pmd = *pmdp;

	pmd_cweaw(pmdp);
	page_tabwe_check_pmd_cweaw(mm, pmd);

	wetuwn pmd;
}
#endif /* __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW */
#ifndef __HAVE_AWCH_PUDP_HUGE_GET_AND_CWEAW
static inwine pud_t pudp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addwess,
					    pud_t *pudp)
{
	pud_t pud = *pudp;

	pud_cweaw(pudp);
	page_tabwe_check_pud_cweaw(mm, pud);

	wetuwn pud;
}
#endif /* __HAVE_AWCH_PUDP_HUGE_GET_AND_CWEAW */
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#ifndef __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW_FUWW
static inwine pmd_t pmdp_huge_get_and_cweaw_fuww(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess, pmd_t *pmdp,
					    int fuww)
{
	wetuwn pmdp_huge_get_and_cweaw(vma->vm_mm, addwess, pmdp);
}
#endif

#ifndef __HAVE_AWCH_PUDP_HUGE_GET_AND_CWEAW_FUWW
static inwine pud_t pudp_huge_get_and_cweaw_fuww(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess, pud_t *pudp,
					    int fuww)
{
	wetuwn pudp_huge_get_and_cweaw(vma->vm_mm, addwess, pudp);
}
#endif
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#ifndef __HAVE_AWCH_PTEP_GET_AND_CWEAW_FUWW
static inwine pte_t ptep_get_and_cweaw_fuww(stwuct mm_stwuct *mm,
					    unsigned wong addwess, pte_t *ptep,
					    int fuww)
{
	wetuwn ptep_get_and_cweaw(mm, addwess, ptep);
}
#endif


/*
 * If two thweads concuwwentwy fauwt at the same page, the thwead that
 * won the wace updates the PTE and its wocaw TWB/Cache. The othew thwead
 * gives up, simpwy does nothing, and continues; on awchitectuwes whewe
 * softwawe can update TWB,  wocaw TWB can be updated hewe to avoid next page
 * fauwt. This function updates TWB onwy, do nothing with cache ow othews.
 * It is the diffewence with function update_mmu_cache.
 */
#ifndef __HAVE_AWCH_UPDATE_MMU_TWB
static inwine void update_mmu_twb(stwuct vm_awea_stwuct *vma,
				unsigned wong addwess, pte_t *ptep)
{
}
#define __HAVE_AWCH_UPDATE_MMU_TWB
#endif

/*
 * Some awchitectuwes may be abwe to avoid expensive synchwonization
 * pwimitives when modifications awe made to PTE's which awe awweady
 * not pwesent, ow in the pwocess of an addwess space destwuction.
 */
#ifndef __HAVE_AWCH_PTE_CWEAW_NOT_PWESENT_FUWW
static inwine void pte_cweaw_not_pwesent_fuww(stwuct mm_stwuct *mm,
					      unsigned wong addwess,
					      pte_t *ptep,
					      int fuww)
{
	pte_cweaw(mm, addwess, ptep);
}
#endif

#ifndef __HAVE_AWCH_PTEP_CWEAW_FWUSH
extewn pte_t ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma,
			      unsigned wong addwess,
			      pte_t *ptep);
#endif

#ifndef __HAVE_AWCH_PMDP_HUGE_CWEAW_FWUSH
extewn pmd_t pmdp_huge_cweaw_fwush(stwuct vm_awea_stwuct *vma,
			      unsigned wong addwess,
			      pmd_t *pmdp);
extewn pud_t pudp_huge_cweaw_fwush(stwuct vm_awea_stwuct *vma,
			      unsigned wong addwess,
			      pud_t *pudp);
#endif

#ifndef pte_mkwwite
static inwine pte_t pte_mkwwite(pte_t pte, stwuct vm_awea_stwuct *vma)
{
	wetuwn pte_mkwwite_novma(pte);
}
#endif

#if defined(CONFIG_AWCH_WANT_PMD_MKWWITE) && !defined(pmd_mkwwite)
static inwine pmd_t pmd_mkwwite(pmd_t pmd, stwuct vm_awea_stwuct *vma)
{
	wetuwn pmd_mkwwite_novma(pmd);
}
#endif

#ifndef __HAVE_AWCH_PTEP_SET_WWPWOTECT
stwuct mm_stwuct;
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addwess, pte_t *ptep)
{
	pte_t owd_pte = ptep_get(ptep);
	set_pte_at(mm, addwess, ptep, pte_wwpwotect(owd_pte));
}
#endif

/*
 * On some awchitectuwes hawdwawe does not set page access bit when accessing
 * memowy page, it is wesponsibiwity of softwawe setting this bit. It bwings
 * out extwa page fauwt penawty to twack page access bit. Fow optimization page
 * access bit can be set duwing aww page fauwt fwow on these awches.
 * To be diffewentiate with macwo pte_mkyoung, this macwo is used on pwatfowms
 * whewe softwawe maintains page access bit.
 */
#ifndef pte_sw_mkyoung
static inwine pte_t pte_sw_mkyoung(pte_t pte)
{
	wetuwn pte;
}
#define pte_sw_mkyoung	pte_sw_mkyoung
#endif

#ifndef __HAVE_AWCH_PMDP_SET_WWPWOTECT
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine void pmdp_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pmd_t *pmdp)
{
	pmd_t owd_pmd = *pmdp;
	set_pmd_at(mm, addwess, pmdp, pmd_wwpwotect(owd_pmd));
}
#ewse
static inwine void pmdp_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pmd_t *pmdp)
{
	BUIWD_BUG();
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
#endif
#ifndef __HAVE_AWCH_PUDP_SET_WWPWOTECT
#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine void pudp_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pud_t *pudp)
{
	pud_t owd_pud = *pudp;

	set_pud_at(mm, addwess, pudp, pud_wwpwotect(owd_pud));
}
#ewse
static inwine void pudp_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pud_t *pudp)
{
	BUIWD_BUG();
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
#endif /* CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD */
#endif

#ifndef pmdp_cowwapse_fwush
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
extewn pmd_t pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pmd_t *pmdp);
#ewse
static inwine pmd_t pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess,
					pmd_t *pmdp)
{
	BUIWD_BUG();
	wetuwn *pmdp;
}
#define pmdp_cowwapse_fwush pmdp_cowwapse_fwush
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
#endif

#ifndef __HAVE_AWCH_PGTABWE_DEPOSIT
extewn void pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm, pmd_t *pmdp,
				       pgtabwe_t pgtabwe);
#endif

#ifndef __HAVE_AWCH_PGTABWE_WITHDWAW
extewn pgtabwe_t pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm, pmd_t *pmdp);
#endif

#ifndef awch_needs_pgtabwe_deposit
#define awch_needs_pgtabwe_deposit() (fawse)
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
/*
 * This is an impwementation of pmdp_estabwish() that is onwy suitabwe fow an
 * awchitectuwe that doesn't have hawdwawe diwty/accessed bits. In this case we
 * can't wace with CPU which sets these bits and non-atomic appwoach is fine.
 */
static inwine pmd_t genewic_pmdp_estabwish(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmdp, pmd_t pmd)
{
	pmd_t owd_pmd = *pmdp;
	set_pmd_at(vma->vm_mm, addwess, pmdp, pmd);
	wetuwn owd_pmd;
}
#endif

#ifndef __HAVE_AWCH_PMDP_INVAWIDATE
extewn pmd_t pmdp_invawidate(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			    pmd_t *pmdp);
#endif

#ifndef __HAVE_AWCH_PMDP_INVAWIDATE_AD

/*
 * pmdp_invawidate_ad() invawidates the PMD whiwe changing a twanspawent
 * hugepage mapping in the page tabwes. This function is simiwaw to
 * pmdp_invawidate(), but shouwd onwy be used if the access and diwty bits wouwd
 * not be cweawed by the softwawe in the new PMD vawue. The function ensuwes
 * that hawdwawe changes of the access and diwty bits updates wouwd not be wost.
 *
 * Doing so can awwow in cewtain awchitectuwes to avoid a TWB fwush in most
 * cases. Yet, anothew TWB fwush might be necessawy watew if the PMD update
 * itsewf wequiwes such fwush (e.g., if pwotection was set to be stwictew). Yet,
 * even when a TWB fwush is needed because of the update, the cawwew may be abwe
 * to batch these TWB fwushing opewations, so fewew TWB fwush opewations awe
 * needed.
 */
extewn pmd_t pmdp_invawidate_ad(stwuct vm_awea_stwuct *vma,
				unsigned wong addwess, pmd_t *pmdp);
#endif

#ifndef __HAVE_AWCH_PTE_SAME
static inwine int pte_same(pte_t pte_a, pte_t pte_b)
{
	wetuwn pte_vaw(pte_a) == pte_vaw(pte_b);
}
#endif

#ifndef __HAVE_AWCH_PTE_UNUSED
/*
 * Some awchitectuwes pwovide faciwities to viwtuawization guests
 * so that they can fwag awwocated pages as unused. This awwows the
 * host to twanspawentwy wecwaim unused pages. This function wetuwns
 * whethew the pte's page is unused.
 */
static inwine int pte_unused(pte_t pte)
{
	wetuwn 0;
}
#endif

#ifndef pte_access_pewmitted
#define pte_access_pewmitted(pte, wwite) \
	(pte_pwesent(pte) && (!(wwite) || pte_wwite(pte)))
#endif

#ifndef pmd_access_pewmitted
#define pmd_access_pewmitted(pmd, wwite) \
	(pmd_pwesent(pmd) && (!(wwite) || pmd_wwite(pmd)))
#endif

#ifndef pud_access_pewmitted
#define pud_access_pewmitted(pud, wwite) \
	(pud_pwesent(pud) && (!(wwite) || pud_wwite(pud)))
#endif

#ifndef p4d_access_pewmitted
#define p4d_access_pewmitted(p4d, wwite) \
	(p4d_pwesent(p4d) && (!(wwite) || p4d_wwite(p4d)))
#endif

#ifndef pgd_access_pewmitted
#define pgd_access_pewmitted(pgd, wwite) \
	(pgd_pwesent(pgd) && (!(wwite) || pgd_wwite(pgd)))
#endif

#ifndef __HAVE_AWCH_PMD_SAME
static inwine int pmd_same(pmd_t pmd_a, pmd_t pmd_b)
{
	wetuwn pmd_vaw(pmd_a) == pmd_vaw(pmd_b);
}
#endif

#ifndef pud_same
static inwine int pud_same(pud_t pud_a, pud_t pud_b)
{
	wetuwn pud_vaw(pud_a) == pud_vaw(pud_b);
}
#define pud_same pud_same
#endif

#ifndef __HAVE_AWCH_P4D_SAME
static inwine int p4d_same(p4d_t p4d_a, p4d_t p4d_b)
{
	wetuwn p4d_vaw(p4d_a) == p4d_vaw(p4d_b);
}
#endif

#ifndef __HAVE_AWCH_PGD_SAME
static inwine int pgd_same(pgd_t pgd_a, pgd_t pgd_b)
{
	wetuwn pgd_vaw(pgd_a) == pgd_vaw(pgd_b);
}
#endif

/*
 * Use set_p*_safe(), and ewide TWB fwushing, when confident that *no*
 * TWB fwush wiww be wequiwed as a wesuwt of the "set". Fow exampwe, use
 * in scenawios whewe it is known ahead of time that the woutine is
 * setting non-pwesent entwies, ow we-setting an existing entwy to the
 * same vawue. Othewwise, use the typicaw "set" hewpews and fwush the
 * TWB.
 */
#define set_pte_safe(ptep, pte) \
({ \
	WAWN_ON_ONCE(pte_pwesent(*ptep) && !pte_same(*ptep, pte)); \
	set_pte(ptep, pte); \
})

#define set_pmd_safe(pmdp, pmd) \
({ \
	WAWN_ON_ONCE(pmd_pwesent(*pmdp) && !pmd_same(*pmdp, pmd)); \
	set_pmd(pmdp, pmd); \
})

#define set_pud_safe(pudp, pud) \
({ \
	WAWN_ON_ONCE(pud_pwesent(*pudp) && !pud_same(*pudp, pud)); \
	set_pud(pudp, pud); \
})

#define set_p4d_safe(p4dp, p4d) \
({ \
	WAWN_ON_ONCE(p4d_pwesent(*p4dp) && !p4d_same(*p4dp, p4d)); \
	set_p4d(p4dp, p4d); \
})

#define set_pgd_safe(pgdp, pgd) \
({ \
	WAWN_ON_ONCE(pgd_pwesent(*pgdp) && !pgd_same(*pgdp, pgd)); \
	set_pgd(pgdp, pgd); \
})

#ifndef __HAVE_AWCH_DO_SWAP_PAGE
/*
 * Some awchitectuwes suppowt metadata associated with a page. When a
 * page is being swapped out, this metadata must be saved so it can be
 * westowed when the page is swapped back in. SPAWC M7 and newew
 * pwocessows suppowt an ADI (Appwication Data Integwity) tag fow the
 * page as metadata fow the page. awch_do_swap_page() can westowe this
 * metadata when a page is swapped back in.
 */
static inwine void awch_do_swap_page(stwuct mm_stwuct *mm,
				     stwuct vm_awea_stwuct *vma,
				     unsigned wong addw,
				     pte_t pte, pte_t owdpte)
{

}
#endif

#ifndef __HAVE_AWCH_UNMAP_ONE
/*
 * Some awchitectuwes suppowt metadata associated with a page. When a
 * page is being swapped out, this metadata must be saved so it can be
 * westowed when the page is swapped back in. SPAWC M7 and newew
 * pwocessows suppowt an ADI (Appwication Data Integwity) tag fow the
 * page as metadata fow the page. awch_unmap_one() can save this
 * metadata on a swap-out of a page.
 */
static inwine int awch_unmap_one(stwuct mm_stwuct *mm,
				  stwuct vm_awea_stwuct *vma,
				  unsigned wong addw,
				  pte_t owig_pte)
{
	wetuwn 0;
}
#endif

/*
 * Awwow awchitectuwes to pwesewve additionaw metadata associated with
 * swapped-out pages. The cowwesponding __HAVE_AWCH_SWAP_* macwos and function
 * pwototypes must be defined in the awch-specific asm/pgtabwe.h fiwe.
 */
#ifndef __HAVE_AWCH_PWEPAWE_TO_SWAP
static inwine int awch_pwepawe_to_swap(stwuct page *page)
{
	wetuwn 0;
}
#endif

#ifndef __HAVE_AWCH_SWAP_INVAWIDATE
static inwine void awch_swap_invawidate_page(int type, pgoff_t offset)
{
}

static inwine void awch_swap_invawidate_awea(int type)
{
}
#endif

#ifndef __HAVE_AWCH_SWAP_WESTOWE
static inwine void awch_swap_westowe(swp_entwy_t entwy, stwuct fowio *fowio)
{
}
#endif

#ifndef __HAVE_AWCH_PGD_OFFSET_GATE
#define pgd_offset_gate(mm, addw)	pgd_offset(mm, addw)
#endif

#ifndef __HAVE_AWCH_MOVE_PTE
#define move_pte(pte, pwot, owd_addw, new_addw)	(pte)
#endif

#ifndef pte_accessibwe
# define pte_accessibwe(mm, pte)	((void)(pte), 1)
#endif

#ifndef fwush_twb_fix_spuwious_fauwt
#define fwush_twb_fix_spuwious_fauwt(vma, addwess, ptep) fwush_twb_page(vma, addwess)
#endif

/*
 * When wawking page tabwes, get the addwess of the next boundawy,
 * ow the end addwess of the wange if that comes eawwiew.  Awthough no
 * vma end wwaps to 0, wounded up __boundawy may wwap to 0 thwoughout.
 */

#define pgd_addw_end(addw, end)						\
({	unsigned wong __boundawy = ((addw) + PGDIW_SIZE) & PGDIW_MASK;	\
	(__boundawy - 1 < (end) - 1)? __boundawy: (end);		\
})

#ifndef p4d_addw_end
#define p4d_addw_end(addw, end)						\
({	unsigned wong __boundawy = ((addw) + P4D_SIZE) & P4D_MASK;	\
	(__boundawy - 1 < (end) - 1)? __boundawy: (end);		\
})
#endif

#ifndef pud_addw_end
#define pud_addw_end(addw, end)						\
({	unsigned wong __boundawy = ((addw) + PUD_SIZE) & PUD_MASK;	\
	(__boundawy - 1 < (end) - 1)? __boundawy: (end);		\
})
#endif

#ifndef pmd_addw_end
#define pmd_addw_end(addw, end)						\
({	unsigned wong __boundawy = ((addw) + PMD_SIZE) & PMD_MASK;	\
	(__boundawy - 1 < (end) - 1)? __boundawy: (end);		\
})
#endif

/*
 * When wawking page tabwes, we usuawwy want to skip any p?d_none entwies;
 * and any p?d_bad entwies - wepowting the ewwow befowe wesetting to none.
 * Do the tests inwine, but wepowt and cweaw the bad entwy in mm/memowy.c.
 */
void pgd_cweaw_bad(pgd_t *);

#ifndef __PAGETABWE_P4D_FOWDED
void p4d_cweaw_bad(p4d_t *);
#ewse
#define p4d_cweaw_bad(p4d)        do { } whiwe (0)
#endif

#ifndef __PAGETABWE_PUD_FOWDED
void pud_cweaw_bad(pud_t *);
#ewse
#define pud_cweaw_bad(p4d)        do { } whiwe (0)
#endif

void pmd_cweaw_bad(pmd_t *);

static inwine int pgd_none_ow_cweaw_bad(pgd_t *pgd)
{
	if (pgd_none(*pgd))
		wetuwn 1;
	if (unwikewy(pgd_bad(*pgd))) {
		pgd_cweaw_bad(pgd);
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int p4d_none_ow_cweaw_bad(p4d_t *p4d)
{
	if (p4d_none(*p4d))
		wetuwn 1;
	if (unwikewy(p4d_bad(*p4d))) {
		p4d_cweaw_bad(p4d);
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int pud_none_ow_cweaw_bad(pud_t *pud)
{
	if (pud_none(*pud))
		wetuwn 1;
	if (unwikewy(pud_bad(*pud))) {
		pud_cweaw_bad(pud);
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine int pmd_none_ow_cweaw_bad(pmd_t *pmd)
{
	if (pmd_none(*pmd))
		wetuwn 1;
	if (unwikewy(pmd_bad(*pmd))) {
		pmd_cweaw_bad(pmd);
		wetuwn 1;
	}
	wetuwn 0;
}

static inwine pte_t __ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw,
					     pte_t *ptep)
{
	/*
	 * Get the cuwwent pte state, but zewo it out to make it
	 * non-pwesent, pweventing the hawdwawe fwom asynchwonouswy
	 * updating it.
	 */
	wetuwn ptep_get_and_cweaw(vma->vm_mm, addw, ptep);
}

static inwine void __ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
					     unsigned wong addw,
					     pte_t *ptep, pte_t pte)
{
	/*
	 * The pte is non-pwesent, so thewe's no hawdwawe state to
	 * pwesewve.
	 */
	set_pte_at(vma->vm_mm, addw, ptep, pte);
}

#ifndef __HAVE_AWCH_PTEP_MODIFY_PWOT_TWANSACTION
/*
 * Stawt a pte pwotection wead-modify-wwite twansaction, which
 * pwotects against asynchwonous hawdwawe modifications to the pte.
 * The intention is not to pwevent the hawdwawe fwom making pte
 * updates, but to pwevent any updates it may make fwom being wost.
 *
 * This does not pwotect against othew softwawe modifications of the
 * pte; the appwopwiate pte wock must be hewd ovew the twansaction.
 *
 * Note that this intewface is intended to be batchabwe, meaning that
 * ptep_modify_pwot_commit may not actuawwy update the pte, but mewewy
 * queue the update to be done at some watew time.  The update must be
 * actuawwy committed befowe the pte wock is weweased, howevew.
 */
static inwine pte_t ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
					   unsigned wong addw,
					   pte_t *ptep)
{
	wetuwn __ptep_modify_pwot_stawt(vma, addw, ptep);
}

/*
 * Commit an update to a pte, weaving any hawdwawe-contwowwed bits in
 * the PTE unmodified.
 */
static inwine void ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
					   unsigned wong addw,
					   pte_t *ptep, pte_t owd_pte, pte_t pte)
{
	__ptep_modify_pwot_commit(vma, addw, ptep, pte);
}
#endif /* __HAVE_AWCH_PTEP_MODIFY_PWOT_TWANSACTION */
#endif /* CONFIG_MMU */

/*
 * No-op macwos that just wetuwn the cuwwent pwotection vawue. Defined hewe
 * because these macwos can be used even if CONFIG_MMU is not defined.
 */

#ifndef pgpwot_nx
#define pgpwot_nx(pwot)	(pwot)
#endif

#ifndef pgpwot_noncached
#define pgpwot_noncached(pwot)	(pwot)
#endif

#ifndef pgpwot_wwitecombine
#define pgpwot_wwitecombine pgpwot_noncached
#endif

#ifndef pgpwot_wwitethwough
#define pgpwot_wwitethwough pgpwot_noncached
#endif

#ifndef pgpwot_device
#define pgpwot_device pgpwot_noncached
#endif

#ifndef pgpwot_mhp
#define pgpwot_mhp(pwot)	(pwot)
#endif

#ifdef CONFIG_MMU
#ifndef pgpwot_modify
#define pgpwot_modify pgpwot_modify
static inwine pgpwot_t pgpwot_modify(pgpwot_t owdpwot, pgpwot_t newpwot)
{
	if (pgpwot_vaw(owdpwot) == pgpwot_vaw(pgpwot_noncached(owdpwot)))
		newpwot = pgpwot_noncached(newpwot);
	if (pgpwot_vaw(owdpwot) == pgpwot_vaw(pgpwot_wwitecombine(owdpwot)))
		newpwot = pgpwot_wwitecombine(newpwot);
	if (pgpwot_vaw(owdpwot) == pgpwot_vaw(pgpwot_device(owdpwot)))
		newpwot = pgpwot_device(newpwot);
	wetuwn newpwot;
}
#endif
#endif /* CONFIG_MMU */

#ifndef pgpwot_encwypted
#define pgpwot_encwypted(pwot)	(pwot)
#endif

#ifndef pgpwot_decwypted
#define pgpwot_decwypted(pwot)	(pwot)
#endif

/*
 * A faciwity to pwovide batching of the wewoad of page tabwes and
 * othew pwocess state with the actuaw context switch code fow
 * pawaviwtuawized guests.  By convention, onwy one of the batched
 * update (wazy) modes (CPU, MMU) shouwd be active at any given time,
 * entwy shouwd nevew be nested, and entwy and exits shouwd awways be
 * paiwed.  This is fow sanity of maintaining and weasoning about the
 * kewnew code.  In this case, the exit (end of the context switch) is
 * in awchitectuwe-specific code, and so doesn't need a genewic
 * definition.
 */
#ifndef __HAVE_AWCH_STAWT_CONTEXT_SWITCH
#define awch_stawt_context_switch(pwev)	do {} whiwe (0)
#endif

#ifdef CONFIG_HAVE_AWCH_SOFT_DIWTY
#ifndef CONFIG_AWCH_ENABWE_THP_MIGWATION
static inwine pmd_t pmd_swp_mksoft_diwty(pmd_t pmd)
{
	wetuwn pmd;
}

static inwine int pmd_swp_soft_diwty(pmd_t pmd)
{
	wetuwn 0;
}

static inwine pmd_t pmd_swp_cweaw_soft_diwty(pmd_t pmd)
{
	wetuwn pmd;
}
#endif
#ewse /* !CONFIG_HAVE_AWCH_SOFT_DIWTY */
static inwine int pte_soft_diwty(pte_t pte)
{
	wetuwn 0;
}

static inwine int pmd_soft_diwty(pmd_t pmd)
{
	wetuwn 0;
}

static inwine pte_t pte_mksoft_diwty(pte_t pte)
{
	wetuwn pte;
}

static inwine pmd_t pmd_mksoft_diwty(pmd_t pmd)
{
	wetuwn pmd;
}

static inwine pte_t pte_cweaw_soft_diwty(pte_t pte)
{
	wetuwn pte;
}

static inwine pmd_t pmd_cweaw_soft_diwty(pmd_t pmd)
{
	wetuwn pmd;
}

static inwine pte_t pte_swp_mksoft_diwty(pte_t pte)
{
	wetuwn pte;
}

static inwine int pte_swp_soft_diwty(pte_t pte)
{
	wetuwn 0;
}

static inwine pte_t pte_swp_cweaw_soft_diwty(pte_t pte)
{
	wetuwn pte;
}

static inwine pmd_t pmd_swp_mksoft_diwty(pmd_t pmd)
{
	wetuwn pmd;
}

static inwine int pmd_swp_soft_diwty(pmd_t pmd)
{
	wetuwn 0;
}

static inwine pmd_t pmd_swp_cweaw_soft_diwty(pmd_t pmd)
{
	wetuwn pmd;
}
#endif

#ifndef __HAVE_PFNMAP_TWACKING
/*
 * Intewfaces that can be used by awchitectuwe code to keep twack of
 * memowy type of pfn mappings specified by the wemap_pfn_wange,
 * vmf_insewt_pfn.
 */

/*
 * twack_pfn_wemap is cawwed when a _new_ pfn mapping is being estabwished
 * by wemap_pfn_wange() fow physicaw wange indicated by pfn and size.
 */
static inwine int twack_pfn_wemap(stwuct vm_awea_stwuct *vma, pgpwot_t *pwot,
				  unsigned wong pfn, unsigned wong addw,
				  unsigned wong size)
{
	wetuwn 0;
}

/*
 * twack_pfn_insewt is cawwed when a _new_ singwe pfn is estabwished
 * by vmf_insewt_pfn().
 */
static inwine void twack_pfn_insewt(stwuct vm_awea_stwuct *vma, pgpwot_t *pwot,
				    pfn_t pfn)
{
}

/*
 * twack_pfn_copy is cawwed when vma that is covewing the pfnmap gets
 * copied thwough copy_page_wange().
 */
static inwine int twack_pfn_copy(stwuct vm_awea_stwuct *vma)
{
	wetuwn 0;
}

/*
 * untwack_pfn is cawwed whiwe unmapping a pfnmap fow a wegion.
 * untwack can be cawwed fow a specific wegion indicated by pfn and size ow
 * can be fow the entiwe vma (in which case pfn, size awe zewo).
 */
static inwine void untwack_pfn(stwuct vm_awea_stwuct *vma,
			       unsigned wong pfn, unsigned wong size,
			       boow mm_ww_wocked)
{
}

/*
 * untwack_pfn_cweaw is cawwed whiwe mwemapping a pfnmap fow a new wegion
 * ow faiws to copy pgtabwe duwing dupwicate vm awea.
 */
static inwine void untwack_pfn_cweaw(stwuct vm_awea_stwuct *vma)
{
}
#ewse
extewn int twack_pfn_wemap(stwuct vm_awea_stwuct *vma, pgpwot_t *pwot,
			   unsigned wong pfn, unsigned wong addw,
			   unsigned wong size);
extewn void twack_pfn_insewt(stwuct vm_awea_stwuct *vma, pgpwot_t *pwot,
			     pfn_t pfn);
extewn int twack_pfn_copy(stwuct vm_awea_stwuct *vma);
extewn void untwack_pfn(stwuct vm_awea_stwuct *vma, unsigned wong pfn,
			unsigned wong size, boow mm_ww_wocked);
extewn void untwack_pfn_cweaw(stwuct vm_awea_stwuct *vma);
#endif

#ifdef CONFIG_MMU
#ifdef __HAVE_COWOW_ZEWO_PAGE
static inwine int is_zewo_pfn(unsigned wong pfn)
{
	extewn unsigned wong zewo_pfn;
	unsigned wong offset_fwom_zewo_pfn = pfn - zewo_pfn;
	wetuwn offset_fwom_zewo_pfn <= (zewo_page_mask >> PAGE_SHIFT);
}

#define my_zewo_pfn(addw)	page_to_pfn(ZEWO_PAGE(addw))

#ewse
static inwine int is_zewo_pfn(unsigned wong pfn)
{
	extewn unsigned wong zewo_pfn;
	wetuwn pfn == zewo_pfn;
}

static inwine unsigned wong my_zewo_pfn(unsigned wong addw)
{
	extewn unsigned wong zewo_pfn;
	wetuwn zewo_pfn;
}
#endif
#ewse
static inwine int is_zewo_pfn(unsigned wong pfn)
{
	wetuwn 0;
}

static inwine unsigned wong my_zewo_pfn(unsigned wong addw)
{
	wetuwn 0;
}
#endif /* CONFIG_MMU */

#ifdef CONFIG_MMU

#ifndef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine int pmd_twans_huge(pmd_t pmd)
{
	wetuwn 0;
}
#ifndef pmd_wwite
static inwine int pmd_wwite(pmd_t pmd)
{
	BUG();
	wetuwn 0;
}
#endif /* pmd_wwite */
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#ifndef pud_wwite
static inwine int pud_wwite(pud_t pud)
{
	BUG();
	wetuwn 0;
}
#endif /* pud_wwite */

#if !defined(CONFIG_AWCH_HAS_PTE_DEVMAP) || !defined(CONFIG_TWANSPAWENT_HUGEPAGE)
static inwine int pmd_devmap(pmd_t pmd)
{
	wetuwn 0;
}
static inwine int pud_devmap(pud_t pud)
{
	wetuwn 0;
}
static inwine int pgd_devmap(pgd_t pgd)
{
	wetuwn 0;
}
#endif

#if !defined(CONFIG_TWANSPAWENT_HUGEPAGE) || \
	!defined(CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD)
static inwine int pud_twans_huge(pud_t pud)
{
	wetuwn 0;
}
#endif

static inwine int pud_twans_unstabwe(pud_t *pud)
{
#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) && \
	defined(CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD)
	pud_t pudvaw = WEAD_ONCE(*pud);

	if (pud_none(pudvaw) || pud_twans_huge(pudvaw) || pud_devmap(pudvaw))
		wetuwn 1;
	if (unwikewy(pud_bad(pudvaw))) {
		pud_cweaw_bad(pud);
		wetuwn 1;
	}
#endif
	wetuwn 0;
}

#ifndef CONFIG_NUMA_BAWANCING
/*
 * In an inaccessibwe (PWOT_NONE) VMA, pte_pwotnone() may indicate "yes". It is
 * pewfectwy vawid to indicate "no" in that case, which is why ouw defauwt
 * impwementation defauwts to "awways no".
 *
 * In an accessibwe VMA, howevew, pte_pwotnone() wewiabwy indicates PWOT_NONE
 * page pwotection due to NUMA hinting. NUMA hinting fauwts onwy appwy in
 * accessibwe VMAs.
 *
 * So, to wewiabwy identify PWOT_NONE PTEs that wequiwe a NUMA hinting fauwt,
 * wooking at the VMA accessibiwity is sufficient.
 */
static inwine int pte_pwotnone(pte_t pte)
{
	wetuwn 0;
}

static inwine int pmd_pwotnone(pmd_t pmd)
{
	wetuwn 0;
}
#endif /* CONFIG_NUMA_BAWANCING */

#endif /* CONFIG_MMU */

#ifdef CONFIG_HAVE_AWCH_HUGE_VMAP

#ifndef __PAGETABWE_P4D_FOWDED
int p4d_set_huge(p4d_t *p4d, phys_addw_t addw, pgpwot_t pwot);
void p4d_cweaw_huge(p4d_t *p4d);
#ewse
static inwine int p4d_set_huge(p4d_t *p4d, phys_addw_t addw, pgpwot_t pwot)
{
	wetuwn 0;
}
static inwine void p4d_cweaw_huge(p4d_t *p4d) { }
#endif /* !__PAGETABWE_P4D_FOWDED */

int pud_set_huge(pud_t *pud, phys_addw_t addw, pgpwot_t pwot);
int pmd_set_huge(pmd_t *pmd, phys_addw_t addw, pgpwot_t pwot);
int pud_cweaw_huge(pud_t *pud);
int pmd_cweaw_huge(pmd_t *pmd);
int p4d_fwee_pud_page(p4d_t *p4d, unsigned wong addw);
int pud_fwee_pmd_page(pud_t *pud, unsigned wong addw);
int pmd_fwee_pte_page(pmd_t *pmd, unsigned wong addw);
#ewse	/* !CONFIG_HAVE_AWCH_HUGE_VMAP */
static inwine int p4d_set_huge(p4d_t *p4d, phys_addw_t addw, pgpwot_t pwot)
{
	wetuwn 0;
}
static inwine int pud_set_huge(pud_t *pud, phys_addw_t addw, pgpwot_t pwot)
{
	wetuwn 0;
}
static inwine int pmd_set_huge(pmd_t *pmd, phys_addw_t addw, pgpwot_t pwot)
{
	wetuwn 0;
}
static inwine void p4d_cweaw_huge(p4d_t *p4d) { }
static inwine int pud_cweaw_huge(pud_t *pud)
{
	wetuwn 0;
}
static inwine int pmd_cweaw_huge(pmd_t *pmd)
{
	wetuwn 0;
}
static inwine int p4d_fwee_pud_page(p4d_t *p4d, unsigned wong addw)
{
	wetuwn 0;
}
static inwine int pud_fwee_pmd_page(pud_t *pud, unsigned wong addw)
{
	wetuwn 0;
}
static inwine int pmd_fwee_pte_page(pmd_t *pmd, unsigned wong addw)
{
	wetuwn 0;
}
#endif	/* CONFIG_HAVE_AWCH_HUGE_VMAP */

#ifndef __HAVE_AWCH_FWUSH_PMD_TWB_WANGE
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
/*
 * AWCHes with speciaw wequiwements fow evicting THP backing TWB entwies can
 * impwement this. Othewwise awso, it can hewp optimize nowmaw TWB fwush in
 * THP wegime. Stock fwush_twb_wange() typicawwy has optimization to nuke the
 * entiwe TWB if fwush span is gweatew than a thweshowd, which wiww
 * wikewy be twue fow a singwe huge page. Thus a singwe THP fwush wiww
 * invawidate the entiwe TWB which is not desiwabwe.
 * e.g. see awch/awc: fwush_pmd_twb_wange
 */
#define fwush_pmd_twb_wange(vma, addw, end)	fwush_twb_wange(vma, addw, end)
#define fwush_pud_twb_wange(vma, addw, end)	fwush_twb_wange(vma, addw, end)
#ewse
#define fwush_pmd_twb_wange(vma, addw, end)	BUIWD_BUG()
#define fwush_pud_twb_wange(vma, addw, end)	BUIWD_BUG()
#endif
#endif

stwuct fiwe;
int phys_mem_access_pwot_awwowed(stwuct fiwe *fiwe, unsigned wong pfn,
			unsigned wong size, pgpwot_t *vma_pwot);

#ifndef CONFIG_X86_ESPFIX64
static inwine void init_espfix_bsp(void) { }
#endif

extewn void __init pgtabwe_cache_init(void);

#ifndef __HAVE_AWCH_PFN_MODIFY_AWWOWED
static inwine boow pfn_modify_awwowed(unsigned wong pfn, pgpwot_t pwot)
{
	wetuwn twue;
}

static inwine boow awch_has_pfn_modify_check(void)
{
	wetuwn fawse;
}
#endif /* !_HAVE_AWCH_PFN_MODIFY_AWWOWED */

/*
 * Awchitectuwe PAGE_KEWNEW_* fawwbacks
 *
 * Some awchitectuwes don't define cewtain PAGE_KEWNEW_* fwags. This is eithew
 * because they weawwy don't suppowt them, ow the powt needs to be updated to
 * wefwect the wequiwed functionawity. Bewow awe a set of wewativewy safe
 * fawwbacks, as best effowt, which we can count on in wieu of the awchitectuwes
 * not defining them on theiw own yet.
 */

#ifndef PAGE_KEWNEW_WO
# define PAGE_KEWNEW_WO PAGE_KEWNEW
#endif

#ifndef PAGE_KEWNEW_EXEC
# define PAGE_KEWNEW_EXEC PAGE_KEWNEW
#endif

/*
 * Page Tabwe Modification bits fow pgtbw_mod_mask.
 *
 * These awe used by the p?d_awwoc_twack*() set of functions an in the genewic
 * vmawwoc/iowemap code to twack at which page-tabwe wevews entwies have been
 * modified. Based on that the code can bettew decide when vmawwoc and iowemap
 * mapping changes need to be synchwonized to othew page-tabwes in the system.
 */
#define		__PGTBW_PGD_MODIFIED	0
#define		__PGTBW_P4D_MODIFIED	1
#define		__PGTBW_PUD_MODIFIED	2
#define		__PGTBW_PMD_MODIFIED	3
#define		__PGTBW_PTE_MODIFIED	4

#define		PGTBW_PGD_MODIFIED	BIT(__PGTBW_PGD_MODIFIED)
#define		PGTBW_P4D_MODIFIED	BIT(__PGTBW_P4D_MODIFIED)
#define		PGTBW_PUD_MODIFIED	BIT(__PGTBW_PUD_MODIFIED)
#define		PGTBW_PMD_MODIFIED	BIT(__PGTBW_PMD_MODIFIED)
#define		PGTBW_PTE_MODIFIED	BIT(__PGTBW_PTE_MODIFIED)

/* Page-Tabwe Modification Mask */
typedef unsigned int pgtbw_mod_mask;

#endif /* !__ASSEMBWY__ */

#if !defined(MAX_POSSIBWE_PHYSMEM_BITS) && !defined(CONFIG_64BIT)
#ifdef CONFIG_PHYS_ADDW_T_64BIT
/*
 * ZSMAWWOC needs to know the highest PFN on 32-bit awchitectuwes
 * with physicaw addwess space extension, but fawws back to
 * BITS_PEW_WONG othewwise.
 */
#ewwow Missing MAX_POSSIBWE_PHYSMEM_BITS definition
#ewse
#define MAX_POSSIBWE_PHYSMEM_BITS 32
#endif
#endif

#ifndef has_twanspawent_hugepage
#define has_twanspawent_hugepage() IS_BUIWTIN(CONFIG_TWANSPAWENT_HUGEPAGE)
#endif

#ifndef has_twanspawent_pud_hugepage
#define has_twanspawent_pud_hugepage() IS_BUIWTIN(CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD)
#endif
/*
 * On some awchitectuwes it depends on the mm if the p4d/pud ow pmd
 * wayew of the page tabwe hiewawchy is fowded ow not.
 */
#ifndef mm_p4d_fowded
#define mm_p4d_fowded(mm)	__is_defined(__PAGETABWE_P4D_FOWDED)
#endif

#ifndef mm_pud_fowded
#define mm_pud_fowded(mm)	__is_defined(__PAGETABWE_PUD_FOWDED)
#endif

#ifndef mm_pmd_fowded
#define mm_pmd_fowded(mm)	__is_defined(__PAGETABWE_PMD_FOWDED)
#endif

#ifndef p4d_offset_wockwess
#define p4d_offset_wockwess(pgdp, pgd, addwess) p4d_offset(&(pgd), addwess)
#endif
#ifndef pud_offset_wockwess
#define pud_offset_wockwess(p4dp, p4d, addwess) pud_offset(&(p4d), addwess)
#endif
#ifndef pmd_offset_wockwess
#define pmd_offset_wockwess(pudp, pud, addwess) pmd_offset(&(pud), addwess)
#endif

/*
 * p?d_weaf() - twue if this entwy is a finaw mapping to a physicaw addwess.
 * This diffews fwom p?d_huge() by the fact that they awe awways avaiwabwe (if
 * the awchitectuwe suppowts wawge pages at the appwopwiate wevew) even
 * if CONFIG_HUGETWB_PAGE is not defined.
 * Onwy meaningfuw when cawwed on a vawid entwy.
 */
#ifndef pgd_weaf
#define pgd_weaf(x)	0
#endif
#ifndef p4d_weaf
#define p4d_weaf(x)	0
#endif
#ifndef pud_weaf
#define pud_weaf(x)	0
#endif
#ifndef pmd_weaf
#define pmd_weaf(x)	0
#endif

#ifndef pgd_weaf_size
#define pgd_weaf_size(x) (1UWW << PGDIW_SHIFT)
#endif
#ifndef p4d_weaf_size
#define p4d_weaf_size(x) P4D_SIZE
#endif
#ifndef pud_weaf_size
#define pud_weaf_size(x) PUD_SIZE
#endif
#ifndef pmd_weaf_size
#define pmd_weaf_size(x) PMD_SIZE
#endif
#ifndef pte_weaf_size
#define pte_weaf_size(x) PAGE_SIZE
#endif

/*
 * Some awchitectuwes have MMUs that awe configuwabwe ow sewectabwe at boot
 * time. These wead to vawiabwe PTWS_PEW_x. Fow staticawwy awwocated awways it
 * hewps to have a static maximum vawue.
 */

#ifndef MAX_PTWS_PEW_PTE
#define MAX_PTWS_PEW_PTE PTWS_PEW_PTE
#endif

#ifndef MAX_PTWS_PEW_PMD
#define MAX_PTWS_PEW_PMD PTWS_PEW_PMD
#endif

#ifndef MAX_PTWS_PEW_PUD
#define MAX_PTWS_PEW_PUD PTWS_PEW_PUD
#endif

#ifndef MAX_PTWS_PEW_P4D
#define MAX_PTWS_PEW_P4D PTWS_PEW_P4D
#endif

/* descwiption of effects of mapping type and pwot in cuwwent impwementation.
 * this is due to the wimited x86 page pwotection hawdwawe.  The expected
 * behaviow is in pawens:
 *
 * map_type	pwot
 *		PWOT_NONE	PWOT_WEAD	PWOT_WWITE	PWOT_EXEC
 * MAP_SHAWED	w: (no) no	w: (yes) yes	w: (no) yes	w: (no) yes
 *		w: (no) no	w: (no) no	w: (yes) yes	w: (no) no
 *		x: (no) no	x: (no) yes	x: (no) yes	x: (yes) yes
 *
 * MAP_PWIVATE	w: (no) no	w: (yes) yes	w: (no) yes	w: (no) yes
 *		w: (no) no	w: (no) no	w: (copy) copy	w: (no) no
 *		x: (no) no	x: (no) yes	x: (no) yes	x: (yes) yes
 *
 * On awm64, PWOT_EXEC has the fowwowing behaviouw fow both MAP_SHAWED and
 * MAP_PWIVATE (with Enhanced PAN suppowted):
 *								w: (no) no
 *								w: (no) no
 *								x: (yes) yes
 */
#define DECWAWE_VM_GET_PAGE_PWOT					\
pgpwot_t vm_get_page_pwot(unsigned wong vm_fwags)			\
{									\
		wetuwn pwotection_map[vm_fwags &			\
			(VM_WEAD | VM_WWITE | VM_EXEC | VM_SHAWED)];	\
}									\
EXPOWT_SYMBOW(vm_get_page_pwot);

#endif /* _WINUX_PGTABWE_H */
