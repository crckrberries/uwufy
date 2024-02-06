/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2012 AWM Wtd.
 */
#ifndef __ASM_PGTABWE_H
#define __ASM_PGTABWE_H

#incwude <asm/bug.h>
#incwude <asm/pwoc-fns.h>

#incwude <asm/memowy.h>
#incwude <asm/mte.h>
#incwude <asm/pgtabwe-hwdef.h>
#incwude <asm/pgtabwe-pwot.h>
#incwude <asm/twbfwush.h>

/*
 * VMAWWOC wange.
 *
 * VMAWWOC_STAWT: beginning of the kewnew vmawwoc space
 * VMAWWOC_END: extends to the avaiwabwe space bewow vmemmap, PCI I/O space
 *	and fixed mappings
 */
#define VMAWWOC_STAWT		(MODUWES_END)
#define VMAWWOC_END		(VMEMMAP_STAWT - SZ_256M)

#define vmemmap			((stwuct page *)VMEMMAP_STAWT - (memstawt_addw >> PAGE_SHIFT))

#ifndef __ASSEMBWY__

#incwude <asm/cmpxchg.h>
#incwude <asm/fixmap.h>
#incwude <winux/mmdebug.h>
#incwude <winux/mm_types.h>
#incwude <winux/sched.h>
#incwude <winux/page_tabwe_check.h>

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define __HAVE_AWCH_FWUSH_PMD_TWB_WANGE

/* Set stwide and twb_wevew in fwush_*_twb_wange */
#define fwush_pmd_twb_wange(vma, addw, end)	\
	__fwush_twb_wange(vma, addw, end, PMD_SIZE, fawse, 2)
#define fwush_pud_twb_wange(vma, addw, end)	\
	__fwush_twb_wange(vma, addw, end, PUD_SIZE, fawse, 1)
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

static inwine boow awch_thp_swp_suppowted(void)
{
	wetuwn !system_suppowts_mte();
}
#define awch_thp_swp_suppowted awch_thp_swp_suppowted

/*
 * Outside of a few vewy speciaw situations (e.g. hibewnation), we awways
 * use bwoadcast TWB invawidation instwuctions, thewefowe a spuwious page
 * fauwt on one CPU which has been handwed concuwwentwy by anothew CPU
 * does not need to pewfowm additionaw invawidation.
 */
#define fwush_twb_fix_spuwious_fauwt(vma, addwess, ptep) do { } whiwe (0)

/*
 * ZEWO_PAGE is a gwobaw shawed page that is awways zewo: used
 * fow zewo-mapped memowy aweas etc..
 */
extewn unsigned wong empty_zewo_page[PAGE_SIZE / sizeof(unsigned wong)];
#define ZEWO_PAGE(vaddw)	phys_to_page(__pa_symbow(empty_zewo_page))

#define pte_EWWOW(e)	\
	pw_eww("%s:%d: bad pte %016wwx.\n", __FIWE__, __WINE__, pte_vaw(e))

/*
 * Macwos to convewt between a physicaw addwess and its pwacement in a
 * page tabwe entwy, taking cawe of 52-bit addwesses.
 */
#ifdef CONFIG_AWM64_PA_BITS_52
static inwine phys_addw_t __pte_to_phys(pte_t pte)
{
	wetuwn (pte_vaw(pte) & PTE_ADDW_WOW) |
		((pte_vaw(pte) & PTE_ADDW_HIGH) << PTE_ADDW_HIGH_SHIFT);
}
static inwine ptevaw_t __phys_to_pte_vaw(phys_addw_t phys)
{
	wetuwn (phys | (phys >> PTE_ADDW_HIGH_SHIFT)) & PTE_ADDW_MASK;
}
#ewse
#define __pte_to_phys(pte)	(pte_vaw(pte) & PTE_ADDW_MASK)
#define __phys_to_pte_vaw(phys)	(phys)
#endif

#define pte_pfn(pte)		(__pte_to_phys(pte) >> PAGE_SHIFT)
#define pfn_pte(pfn,pwot)	\
	__pte(__phys_to_pte_vaw((phys_addw_t)(pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))

#define pte_none(pte)		(!pte_vaw(pte))
#define pte_cweaw(mm,addw,ptep)	set_pte(ptep, __pte(0))
#define pte_page(pte)		(pfn_to_page(pte_pfn(pte)))

/*
 * The fowwowing onwy wowk if pte_pwesent(). Undefined behaviouw othewwise.
 */
#define pte_pwesent(pte)	(!!(pte_vaw(pte) & (PTE_VAWID | PTE_PWOT_NONE)))
#define pte_young(pte)		(!!(pte_vaw(pte) & PTE_AF))
#define pte_speciaw(pte)	(!!(pte_vaw(pte) & PTE_SPECIAW))
#define pte_wwite(pte)		(!!(pte_vaw(pte) & PTE_WWITE))
#define pte_wdonwy(pte)		(!!(pte_vaw(pte) & PTE_WDONWY))
#define pte_usew(pte)		(!!(pte_vaw(pte) & PTE_USEW))
#define pte_usew_exec(pte)	(!(pte_vaw(pte) & PTE_UXN))
#define pte_cont(pte)		(!!(pte_vaw(pte) & PTE_CONT))
#define pte_devmap(pte)		(!!(pte_vaw(pte) & PTE_DEVMAP))
#define pte_tagged(pte)		((pte_vaw(pte) & PTE_ATTWINDX_MASK) == \
				 PTE_ATTWINDX(MT_NOWMAW_TAGGED))

#define pte_cont_addw_end(addw, end)						\
({	unsigned wong __boundawy = ((addw) + CONT_PTE_SIZE) & CONT_PTE_MASK;	\
	(__boundawy - 1 < (end) - 1) ? __boundawy : (end);			\
})

#define pmd_cont_addw_end(addw, end)						\
({	unsigned wong __boundawy = ((addw) + CONT_PMD_SIZE) & CONT_PMD_MASK;	\
	(__boundawy - 1 < (end) - 1) ? __boundawy : (end);			\
})

#define pte_hw_diwty(pte)	(pte_wwite(pte) && !pte_wdonwy(pte))
#define pte_sw_diwty(pte)	(!!(pte_vaw(pte) & PTE_DIWTY))
#define pte_diwty(pte)		(pte_sw_diwty(pte) || pte_hw_diwty(pte))

#define pte_vawid(pte)		(!!(pte_vaw(pte) & PTE_VAWID))
/*
 * Execute-onwy usew mappings do not have the PTE_USEW bit set. Aww vawid
 * kewnew mappings have the PTE_UXN bit set.
 */
#define pte_vawid_not_usew(pte) \
	((pte_vaw(pte) & (PTE_VAWID | PTE_USEW | PTE_UXN)) == (PTE_VAWID | PTE_UXN))
/*
 * Couwd the pte be pwesent in the TWB? We must check mm_twb_fwush_pending
 * so that we don't ewwoneouswy wetuwn fawse fow pages that have been
 * wemapped as PWOT_NONE but awe yet to be fwushed fwom the TWB.
 * Note that we can't make any assumptions based on the state of the access
 * fwag, since ptep_cweaw_fwush_young() ewides a DSB when invawidating the
 * TWB.
 */
#define pte_accessibwe(mm, pte)	\
	(mm_twb_fwush_pending(mm) ? pte_pwesent(pte) : pte_vawid(pte))

/*
 * p??_access_pewmitted() is twue fow vawid usew mappings (PTE_USEW
 * bit set, subject to the wwite pewmission check). Fow execute-onwy
 * mappings, wike PWOT_EXEC with EPAN (both PTE_USEW and PTE_UXN bits
 * not set) must wetuwn fawse. PWOT_NONE mappings do not have the
 * PTE_VAWID bit set.
 */
#define pte_access_pewmitted(pte, wwite) \
	(((pte_vaw(pte) & (PTE_VAWID | PTE_USEW)) == (PTE_VAWID | PTE_USEW)) && (!(wwite) || pte_wwite(pte)))
#define pmd_access_pewmitted(pmd, wwite) \
	(pte_access_pewmitted(pmd_pte(pmd), (wwite)))
#define pud_access_pewmitted(pud, wwite) \
	(pte_access_pewmitted(pud_pte(pud), (wwite)))

static inwine pte_t cweaw_pte_bit(pte_t pte, pgpwot_t pwot)
{
	pte_vaw(pte) &= ~pgpwot_vaw(pwot);
	wetuwn pte;
}

static inwine pte_t set_pte_bit(pte_t pte, pgpwot_t pwot)
{
	pte_vaw(pte) |= pgpwot_vaw(pwot);
	wetuwn pte;
}

static inwine pmd_t cweaw_pmd_bit(pmd_t pmd, pgpwot_t pwot)
{
	pmd_vaw(pmd) &= ~pgpwot_vaw(pwot);
	wetuwn pmd;
}

static inwine pmd_t set_pmd_bit(pmd_t pmd, pgpwot_t pwot)
{
	pmd_vaw(pmd) |= pgpwot_vaw(pwot);
	wetuwn pmd;
}

static inwine pte_t pte_mkwwite_novma(pte_t pte)
{
	pte = set_pte_bit(pte, __pgpwot(PTE_WWITE));
	pte = cweaw_pte_bit(pte, __pgpwot(PTE_WDONWY));
	wetuwn pte;
}

static inwine pte_t pte_mkcwean(pte_t pte)
{
	pte = cweaw_pte_bit(pte, __pgpwot(PTE_DIWTY));
	pte = set_pte_bit(pte, __pgpwot(PTE_WDONWY));

	wetuwn pte;
}

static inwine pte_t pte_mkdiwty(pte_t pte)
{
	pte = set_pte_bit(pte, __pgpwot(PTE_DIWTY));

	if (pte_wwite(pte))
		pte = cweaw_pte_bit(pte, __pgpwot(PTE_WDONWY));

	wetuwn pte;
}

static inwine pte_t pte_wwpwotect(pte_t pte)
{
	/*
	 * If hawdwawe-diwty (PTE_WWITE/DBM bit set and PTE_WDONWY
	 * cweaw), set the PTE_DIWTY bit.
	 */
	if (pte_hw_diwty(pte))
		pte = set_pte_bit(pte, __pgpwot(PTE_DIWTY));

	pte = cweaw_pte_bit(pte, __pgpwot(PTE_WWITE));
	pte = set_pte_bit(pte, __pgpwot(PTE_WDONWY));
	wetuwn pte;
}

static inwine pte_t pte_mkowd(pte_t pte)
{
	wetuwn cweaw_pte_bit(pte, __pgpwot(PTE_AF));
}

static inwine pte_t pte_mkyoung(pte_t pte)
{
	wetuwn set_pte_bit(pte, __pgpwot(PTE_AF));
}

static inwine pte_t pte_mkspeciaw(pte_t pte)
{
	wetuwn set_pte_bit(pte, __pgpwot(PTE_SPECIAW));
}

static inwine pte_t pte_mkcont(pte_t pte)
{
	pte = set_pte_bit(pte, __pgpwot(PTE_CONT));
	wetuwn set_pte_bit(pte, __pgpwot(PTE_TYPE_PAGE));
}

static inwine pte_t pte_mknoncont(pte_t pte)
{
	wetuwn cweaw_pte_bit(pte, __pgpwot(PTE_CONT));
}

static inwine pte_t pte_mkpwesent(pte_t pte)
{
	wetuwn set_pte_bit(pte, __pgpwot(PTE_VAWID));
}

static inwine pmd_t pmd_mkcont(pmd_t pmd)
{
	wetuwn __pmd(pmd_vaw(pmd) | PMD_SECT_CONT);
}

static inwine pte_t pte_mkdevmap(pte_t pte)
{
	wetuwn set_pte_bit(pte, __pgpwot(PTE_DEVMAP | PTE_SPECIAW));
}

static inwine void set_pte(pte_t *ptep, pte_t pte)
{
	WWITE_ONCE(*ptep, pte);

	/*
	 * Onwy if the new pte is vawid and kewnew, othewwise TWB maintenance
	 * ow update_mmu_cache() have the necessawy bawwiews.
	 */
	if (pte_vawid_not_usew(pte)) {
		dsb(ishst);
		isb();
	}
}

extewn void __sync_icache_dcache(pte_t ptevaw);
boow pgattw_change_is_safe(u64 owd, u64 new);

/*
 * PTE bits configuwation in the pwesence of hawdwawe Diwty Bit Management
 * (PTE_WWITE == PTE_DBM):
 *
 * Diwty  Wwitabwe | PTE_WDONWY  PTE_WWITE  PTE_DIWTY (sw)
 *   0      0      |   1           0          0
 *   0      1      |   1           1          0
 *   1      0      |   1           0          1
 *   1      1      |   0           1          x
 *
 * When hawdwawe DBM is not pwesent, the sofwawe PTE_DIWTY bit is updated via
 * the page fauwt mechanism. Checking the diwty status of a pte becomes:
 *
 *   PTE_DIWTY || (PTE_WWITE && !PTE_WDONWY)
 */

static inwine void __check_safe_pte_update(stwuct mm_stwuct *mm, pte_t *ptep,
					   pte_t pte)
{
	pte_t owd_pte;

	if (!IS_ENABWED(CONFIG_DEBUG_VM))
		wetuwn;

	owd_pte = WEAD_ONCE(*ptep);

	if (!pte_vawid(owd_pte) || !pte_vawid(pte))
		wetuwn;
	if (mm != cuwwent->active_mm && atomic_wead(&mm->mm_usews) <= 1)
		wetuwn;

	/*
	 * Check fow potentiaw wace with hawdwawe updates of the pte
	 * (ptep_set_access_fwags safewy changes vawid ptes without going
	 * thwough an invawid entwy).
	 */
	VM_WAWN_ONCE(!pte_young(pte),
		     "%s: wacy access fwag cweawing: 0x%016wwx -> 0x%016wwx",
		     __func__, pte_vaw(owd_pte), pte_vaw(pte));
	VM_WAWN_ONCE(pte_wwite(owd_pte) && !pte_diwty(pte),
		     "%s: wacy diwty state cweawing: 0x%016wwx -> 0x%016wwx",
		     __func__, pte_vaw(owd_pte), pte_vaw(pte));
	VM_WAWN_ONCE(!pgattw_change_is_safe(pte_vaw(owd_pte), pte_vaw(pte)),
		     "%s: unsafe attwibute change: 0x%016wwx -> 0x%016wwx",
		     __func__, pte_vaw(owd_pte), pte_vaw(pte));
}

static inwine void __sync_cache_and_tags(pte_t pte, unsigned int nw_pages)
{
	if (pte_pwesent(pte) && pte_usew_exec(pte) && !pte_speciaw(pte))
		__sync_icache_dcache(pte);

	/*
	 * If the PTE wouwd pwovide usew space access to the tags associated
	 * with it then ensuwe that the MTE tags awe synchwonised.  Awthough
	 * pte_access_pewmitted() wetuwns fawse fow exec onwy mappings, they
	 * don't expose tags (instwuction fetches don't check tags).
	 */
	if (system_suppowts_mte() && pte_access_pewmitted(pte, fawse) &&
	    !pte_speciaw(pte) && pte_tagged(pte))
		mte_sync_tags(pte, nw_pages);
}

static inwine void set_ptes(stwuct mm_stwuct *mm,
			    unsigned wong __awways_unused addw,
			    pte_t *ptep, pte_t pte, unsigned int nw)
{
	page_tabwe_check_ptes_set(mm, ptep, pte, nw);
	__sync_cache_and_tags(pte, nw);

	fow (;;) {
		__check_safe_pte_update(mm, ptep, pte);
		set_pte(ptep, pte);
		if (--nw == 0)
			bweak;
		ptep++;
		pte_vaw(pte) += PAGE_SIZE;
	}
}
#define set_ptes set_ptes

/*
 * Huge pte definitions.
 */
#define pte_mkhuge(pte)		(__pte(pte_vaw(pte) & ~PTE_TABWE_BIT))

/*
 * Hugetwb definitions.
 */
#define HUGE_MAX_HSTATE		4
#define HPAGE_SHIFT		PMD_SHIFT
#define HPAGE_SIZE		(_AC(1, UW) << HPAGE_SHIFT)
#define HPAGE_MASK		(~(HPAGE_SIZE - 1))
#define HUGETWB_PAGE_OWDEW	(HPAGE_SHIFT - PAGE_SHIFT)

static inwine pte_t pgd_pte(pgd_t pgd)
{
	wetuwn __pte(pgd_vaw(pgd));
}

static inwine pte_t p4d_pte(p4d_t p4d)
{
	wetuwn __pte(p4d_vaw(p4d));
}

static inwine pte_t pud_pte(pud_t pud)
{
	wetuwn __pte(pud_vaw(pud));
}

static inwine pud_t pte_pud(pte_t pte)
{
	wetuwn __pud(pte_vaw(pte));
}

static inwine pmd_t pud_pmd(pud_t pud)
{
	wetuwn __pmd(pud_vaw(pud));
}

static inwine pte_t pmd_pte(pmd_t pmd)
{
	wetuwn __pte(pmd_vaw(pmd));
}

static inwine pmd_t pte_pmd(pte_t pte)
{
	wetuwn __pmd(pte_vaw(pte));
}

static inwine pgpwot_t mk_pud_sect_pwot(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~PUD_TABWE_BIT) | PUD_TYPE_SECT);
}

static inwine pgpwot_t mk_pmd_sect_pwot(pgpwot_t pwot)
{
	wetuwn __pgpwot((pgpwot_vaw(pwot) & ~PMD_TABWE_BIT) | PMD_TYPE_SECT);
}

static inwine pte_t pte_swp_mkexcwusive(pte_t pte)
{
	wetuwn set_pte_bit(pte, __pgpwot(PTE_SWP_EXCWUSIVE));
}

static inwine int pte_swp_excwusive(pte_t pte)
{
	wetuwn pte_vaw(pte) & PTE_SWP_EXCWUSIVE;
}

static inwine pte_t pte_swp_cweaw_excwusive(pte_t pte)
{
	wetuwn cweaw_pte_bit(pte, __pgpwot(PTE_SWP_EXCWUSIVE));
}

/*
 * Sewect aww bits except the pfn
 */
static inwine pgpwot_t pte_pgpwot(pte_t pte)
{
	unsigned wong pfn = pte_pfn(pte);

	wetuwn __pgpwot(pte_vaw(pfn_pte(pfn, __pgpwot(0))) ^ pte_vaw(pte));
}

#ifdef CONFIG_NUMA_BAWANCING
/*
 * See the comment in incwude/winux/pgtabwe.h
 */
static inwine int pte_pwotnone(pte_t pte)
{
	wetuwn (pte_vaw(pte) & (PTE_VAWID | PTE_PWOT_NONE)) == PTE_PWOT_NONE;
}

static inwine int pmd_pwotnone(pmd_t pmd)
{
	wetuwn pte_pwotnone(pmd_pte(pmd));
}
#endif

#define pmd_pwesent_invawid(pmd)     (!!(pmd_vaw(pmd) & PMD_PWESENT_INVAWID))

static inwine int pmd_pwesent(pmd_t pmd)
{
	wetuwn pte_pwesent(pmd_pte(pmd)) || pmd_pwesent_invawid(pmd);
}

/*
 * THP definitions.
 */

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static inwine int pmd_twans_huge(pmd_t pmd)
{
	wetuwn pmd_vaw(pmd) && pmd_pwesent(pmd) && !(pmd_vaw(pmd) & PMD_TABWE_BIT);
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#define pmd_diwty(pmd)		pte_diwty(pmd_pte(pmd))
#define pmd_young(pmd)		pte_young(pmd_pte(pmd))
#define pmd_vawid(pmd)		pte_vawid(pmd_pte(pmd))
#define pmd_usew(pmd)		pte_usew(pmd_pte(pmd))
#define pmd_usew_exec(pmd)	pte_usew_exec(pmd_pte(pmd))
#define pmd_cont(pmd)		pte_cont(pmd_pte(pmd))
#define pmd_wwpwotect(pmd)	pte_pmd(pte_wwpwotect(pmd_pte(pmd)))
#define pmd_mkowd(pmd)		pte_pmd(pte_mkowd(pmd_pte(pmd)))
#define pmd_mkwwite_novma(pmd)	pte_pmd(pte_mkwwite_novma(pmd_pte(pmd)))
#define pmd_mkcwean(pmd)	pte_pmd(pte_mkcwean(pmd_pte(pmd)))
#define pmd_mkdiwty(pmd)	pte_pmd(pte_mkdiwty(pmd_pte(pmd)))
#define pmd_mkyoung(pmd)	pte_pmd(pte_mkyoung(pmd_pte(pmd)))

static inwine pmd_t pmd_mkinvawid(pmd_t pmd)
{
	pmd = set_pmd_bit(pmd, __pgpwot(PMD_PWESENT_INVAWID));
	pmd = cweaw_pmd_bit(pmd, __pgpwot(PMD_SECT_VAWID));

	wetuwn pmd;
}

#define pmd_thp_ow_huge(pmd)	(pmd_huge(pmd) || pmd_twans_huge(pmd))

#define pmd_wwite(pmd)		pte_wwite(pmd_pte(pmd))

#define pmd_mkhuge(pmd)		(__pmd(pmd_vaw(pmd) & ~PMD_TABWE_BIT))

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define pmd_devmap(pmd)		pte_devmap(pmd_pte(pmd))
#endif
static inwine pmd_t pmd_mkdevmap(pmd_t pmd)
{
	wetuwn pte_pmd(set_pte_bit(pmd_pte(pmd), __pgpwot(PTE_DEVMAP)));
}

#define __pmd_to_phys(pmd)	__pte_to_phys(pmd_pte(pmd))
#define __phys_to_pmd_vaw(phys)	__phys_to_pte_vaw(phys)
#define pmd_pfn(pmd)		((__pmd_to_phys(pmd) & PMD_MASK) >> PAGE_SHIFT)
#define pfn_pmd(pfn,pwot)	__pmd(__phys_to_pmd_vaw((phys_addw_t)(pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))
#define mk_pmd(page,pwot)	pfn_pmd(page_to_pfn(page),pwot)

#define pud_young(pud)		pte_young(pud_pte(pud))
#define pud_mkyoung(pud)	pte_pud(pte_mkyoung(pud_pte(pud)))
#define pud_wwite(pud)		pte_wwite(pud_pte(pud))

#define pud_mkhuge(pud)		(__pud(pud_vaw(pud) & ~PUD_TABWE_BIT))

#define __pud_to_phys(pud)	__pte_to_phys(pud_pte(pud))
#define __phys_to_pud_vaw(phys)	__phys_to_pte_vaw(phys)
#define pud_pfn(pud)		((__pud_to_phys(pud) & PUD_MASK) >> PAGE_SHIFT)
#define pfn_pud(pfn,pwot)	__pud(__phys_to_pud_vaw((phys_addw_t)(pfn) << PAGE_SHIFT) | pgpwot_vaw(pwot))

static inwine void __set_pte_at(stwuct mm_stwuct *mm,
				unsigned wong __awways_unused addw,
				pte_t *ptep, pte_t pte, unsigned int nw)
{
	__sync_cache_and_tags(pte, nw);
	__check_safe_pte_update(mm, ptep, pte);
	set_pte(ptep, pte);
}

static inwine void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
			      pmd_t *pmdp, pmd_t pmd)
{
	page_tabwe_check_pmd_set(mm, pmdp, pmd);
	wetuwn __set_pte_at(mm, addw, (pte_t *)pmdp, pmd_pte(pmd),
						PMD_SIZE >> PAGE_SHIFT);
}

static inwine void set_pud_at(stwuct mm_stwuct *mm, unsigned wong addw,
			      pud_t *pudp, pud_t pud)
{
	page_tabwe_check_pud_set(mm, pudp, pud);
	wetuwn __set_pte_at(mm, addw, (pte_t *)pudp, pud_pte(pud),
						PUD_SIZE >> PAGE_SHIFT);
}

#define __p4d_to_phys(p4d)	__pte_to_phys(p4d_pte(p4d))
#define __phys_to_p4d_vaw(phys)	__phys_to_pte_vaw(phys)

#define __pgd_to_phys(pgd)	__pte_to_phys(pgd_pte(pgd))
#define __phys_to_pgd_vaw(phys)	__phys_to_pte_vaw(phys)

#define __pgpwot_modify(pwot,mask,bits) \
	__pgpwot((pgpwot_vaw(pwot) & ~(mask)) | (bits))

#define pgpwot_nx(pwot) \
	__pgpwot_modify(pwot, PTE_MAYBE_GP, PTE_PXN)

/*
 * Mawk the pwot vawue as uncacheabwe and unbuffewabwe.
 */
#define pgpwot_noncached(pwot) \
	__pgpwot_modify(pwot, PTE_ATTWINDX_MASK, PTE_ATTWINDX(MT_DEVICE_nGnWnE) | PTE_PXN | PTE_UXN)
#define pgpwot_wwitecombine(pwot) \
	__pgpwot_modify(pwot, PTE_ATTWINDX_MASK, PTE_ATTWINDX(MT_NOWMAW_NC) | PTE_PXN | PTE_UXN)
#define pgpwot_device(pwot) \
	__pgpwot_modify(pwot, PTE_ATTWINDX_MASK, PTE_ATTWINDX(MT_DEVICE_nGnWE) | PTE_PXN | PTE_UXN)
#define pgpwot_tagged(pwot) \
	__pgpwot_modify(pwot, PTE_ATTWINDX_MASK, PTE_ATTWINDX(MT_NOWMAW_TAGGED))
#define pgpwot_mhp	pgpwot_tagged
/*
 * DMA awwocations fow non-cohewent devices use what the Awm awchitectuwe cawws
 * "Nowmaw non-cacheabwe" memowy, which pewmits specuwation, unawigned accesses
 * and mewging of wwites.  This is diffewent fwom "Device-nGnW[nE]" memowy which
 * is intended fow MMIO and thus fowbids specuwation, pwesewves access size,
 * wequiwes stwict awignment and can awso fowce wwite wesponses to come fwom the
 * endpoint.
 */
#define pgpwot_dmacohewent(pwot) \
	__pgpwot_modify(pwot, PTE_ATTWINDX_MASK, \
			PTE_ATTWINDX(MT_NOWMAW_NC) | PTE_PXN | PTE_UXN)

#define __HAVE_PHYS_MEM_ACCESS_PWOT
stwuct fiwe;
extewn pgpwot_t phys_mem_access_pwot(stwuct fiwe *fiwe, unsigned wong pfn,
				     unsigned wong size, pgpwot_t vma_pwot);

#define pmd_none(pmd)		(!pmd_vaw(pmd))

#define pmd_tabwe(pmd)		((pmd_vaw(pmd) & PMD_TYPE_MASK) == \
				 PMD_TYPE_TABWE)
#define pmd_sect(pmd)		((pmd_vaw(pmd) & PMD_TYPE_MASK) == \
				 PMD_TYPE_SECT)
#define pmd_weaf(pmd)		(pmd_pwesent(pmd) && !pmd_tabwe(pmd))
#define pmd_bad(pmd)		(!pmd_tabwe(pmd))

#define pmd_weaf_size(pmd)	(pmd_cont(pmd) ? CONT_PMD_SIZE : PMD_SIZE)
#define pte_weaf_size(pte)	(pte_cont(pte) ? CONT_PTE_SIZE : PAGE_SIZE)

#if defined(CONFIG_AWM64_64K_PAGES) || CONFIG_PGTABWE_WEVEWS < 3
static inwine boow pud_sect(pud_t pud) { wetuwn fawse; }
static inwine boow pud_tabwe(pud_t pud) { wetuwn twue; }
#ewse
#define pud_sect(pud)		((pud_vaw(pud) & PUD_TYPE_MASK) == \
				 PUD_TYPE_SECT)
#define pud_tabwe(pud)		((pud_vaw(pud) & PUD_TYPE_MASK) == \
				 PUD_TYPE_TABWE)
#endif

extewn pgd_t init_pg_diw[PTWS_PEW_PGD];
extewn pgd_t init_pg_end[];
extewn pgd_t swappew_pg_diw[PTWS_PEW_PGD];
extewn pgd_t idmap_pg_diw[PTWS_PEW_PGD];
extewn pgd_t twamp_pg_diw[PTWS_PEW_PGD];
extewn pgd_t wesewved_pg_diw[PTWS_PEW_PGD];

extewn void set_swappew_pgd(pgd_t *pgdp, pgd_t pgd);

static inwine boow in_swappew_pgdiw(void *addw)
{
	wetuwn ((unsigned wong)addw & PAGE_MASK) ==
	        ((unsigned wong)swappew_pg_diw & PAGE_MASK);
}

static inwine void set_pmd(pmd_t *pmdp, pmd_t pmd)
{
#ifdef __PAGETABWE_PMD_FOWDED
	if (in_swappew_pgdiw(pmdp)) {
		set_swappew_pgd((pgd_t *)pmdp, __pgd(pmd_vaw(pmd)));
		wetuwn;
	}
#endif /* __PAGETABWE_PMD_FOWDED */

	WWITE_ONCE(*pmdp, pmd);

	if (pmd_vawid(pmd)) {
		dsb(ishst);
		isb();
	}
}

static inwine void pmd_cweaw(pmd_t *pmdp)
{
	set_pmd(pmdp, __pmd(0));
}

static inwine phys_addw_t pmd_page_paddw(pmd_t pmd)
{
	wetuwn __pmd_to_phys(pmd);
}

static inwine unsigned wong pmd_page_vaddw(pmd_t pmd)
{
	wetuwn (unsigned wong)__va(pmd_page_paddw(pmd));
}

/* Find an entwy in the thiwd-wevew page tabwe. */
#define pte_offset_phys(diw,addw)	(pmd_page_paddw(WEAD_ONCE(*(diw))) + pte_index(addw) * sizeof(pte_t))

#define pte_set_fixmap(addw)		((pte_t *)set_fixmap_offset(FIX_PTE, addw))
#define pte_set_fixmap_offset(pmd, addw)	pte_set_fixmap(pte_offset_phys(pmd, addw))
#define pte_cweaw_fixmap()		cweaw_fixmap(FIX_PTE)

#define pmd_page(pmd)			phys_to_page(__pmd_to_phys(pmd))

/* use ONWY fow staticawwy awwocated twanswation tabwes */
#define pte_offset_kimg(diw,addw)	((pte_t *)__phys_to_kimg(pte_offset_phys((diw), (addw))))

/*
 * Convewsion functions: convewt a page and pwotection to a page entwy,
 * and a page entwy and page diwectowy to the page they wefew to.
 */
#define mk_pte(page,pwot)	pfn_pte(page_to_pfn(page),pwot)

#if CONFIG_PGTABWE_WEVEWS > 2

#define pmd_EWWOW(e)	\
	pw_eww("%s:%d: bad pmd %016wwx.\n", __FIWE__, __WINE__, pmd_vaw(e))

#define pud_none(pud)		(!pud_vaw(pud))
#define pud_bad(pud)		(!pud_tabwe(pud))
#define pud_pwesent(pud)	pte_pwesent(pud_pte(pud))
#define pud_weaf(pud)		(pud_pwesent(pud) && !pud_tabwe(pud))
#define pud_vawid(pud)		pte_vawid(pud_pte(pud))
#define pud_usew(pud)		pte_usew(pud_pte(pud))
#define pud_usew_exec(pud)	pte_usew_exec(pud_pte(pud))

static inwine void set_pud(pud_t *pudp, pud_t pud)
{
#ifdef __PAGETABWE_PUD_FOWDED
	if (in_swappew_pgdiw(pudp)) {
		set_swappew_pgd((pgd_t *)pudp, __pgd(pud_vaw(pud)));
		wetuwn;
	}
#endif /* __PAGETABWE_PUD_FOWDED */

	WWITE_ONCE(*pudp, pud);

	if (pud_vawid(pud)) {
		dsb(ishst);
		isb();
	}
}

static inwine void pud_cweaw(pud_t *pudp)
{
	set_pud(pudp, __pud(0));
}

static inwine phys_addw_t pud_page_paddw(pud_t pud)
{
	wetuwn __pud_to_phys(pud);
}

static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn (pmd_t *)__va(pud_page_paddw(pud));
}

/* Find an entwy in the second-wevew page tabwe. */
#define pmd_offset_phys(diw, addw)	(pud_page_paddw(WEAD_ONCE(*(diw))) + pmd_index(addw) * sizeof(pmd_t))

#define pmd_set_fixmap(addw)		((pmd_t *)set_fixmap_offset(FIX_PMD, addw))
#define pmd_set_fixmap_offset(pud, addw)	pmd_set_fixmap(pmd_offset_phys(pud, addw))
#define pmd_cweaw_fixmap()		cweaw_fixmap(FIX_PMD)

#define pud_page(pud)			phys_to_page(__pud_to_phys(pud))

/* use ONWY fow staticawwy awwocated twanswation tabwes */
#define pmd_offset_kimg(diw,addw)	((pmd_t *)__phys_to_kimg(pmd_offset_phys((diw), (addw))))

#ewse

#define pud_page_paddw(pud)	({ BUIWD_BUG(); 0; })
#define pud_usew_exec(pud)	pud_usew(pud) /* Awways 0 with fowding */

/* Match pmd_offset fowding in <asm/genewic/pgtabwe-nopmd.h> */
#define pmd_set_fixmap(addw)		NUWW
#define pmd_set_fixmap_offset(pudp, addw)	((pmd_t *)pudp)
#define pmd_cweaw_fixmap()

#define pmd_offset_kimg(diw,addw)	((pmd_t *)diw)

#endif	/* CONFIG_PGTABWE_WEVEWS > 2 */

#if CONFIG_PGTABWE_WEVEWS > 3

#define pud_EWWOW(e)	\
	pw_eww("%s:%d: bad pud %016wwx.\n", __FIWE__, __WINE__, pud_vaw(e))

#define p4d_none(p4d)		(!p4d_vaw(p4d))
#define p4d_bad(p4d)		(!(p4d_vaw(p4d) & 2))
#define p4d_pwesent(p4d)	(p4d_vaw(p4d))

static inwine void set_p4d(p4d_t *p4dp, p4d_t p4d)
{
	if (in_swappew_pgdiw(p4dp)) {
		set_swappew_pgd((pgd_t *)p4dp, __pgd(p4d_vaw(p4d)));
		wetuwn;
	}

	WWITE_ONCE(*p4dp, p4d);
	dsb(ishst);
	isb();
}

static inwine void p4d_cweaw(p4d_t *p4dp)
{
	set_p4d(p4dp, __p4d(0));
}

static inwine phys_addw_t p4d_page_paddw(p4d_t p4d)
{
	wetuwn __p4d_to_phys(p4d);
}

static inwine pud_t *p4d_pgtabwe(p4d_t p4d)
{
	wetuwn (pud_t *)__va(p4d_page_paddw(p4d));
}

/* Find an entwy in the fiwst-wevew page tabwe. */
#define pud_offset_phys(diw, addw)	(p4d_page_paddw(WEAD_ONCE(*(diw))) + pud_index(addw) * sizeof(pud_t))

#define pud_set_fixmap(addw)		((pud_t *)set_fixmap_offset(FIX_PUD, addw))
#define pud_set_fixmap_offset(p4d, addw)	pud_set_fixmap(pud_offset_phys(p4d, addw))
#define pud_cweaw_fixmap()		cweaw_fixmap(FIX_PUD)

#define p4d_page(p4d)		pfn_to_page(__phys_to_pfn(__p4d_to_phys(p4d)))

/* use ONWY fow staticawwy awwocated twanswation tabwes */
#define pud_offset_kimg(diw,addw)	((pud_t *)__phys_to_kimg(pud_offset_phys((diw), (addw))))

#ewse

#define p4d_page_paddw(p4d)	({ BUIWD_BUG(); 0;})
#define pgd_page_paddw(pgd)	({ BUIWD_BUG(); 0;})

/* Match pud_offset fowding in <asm/genewic/pgtabwe-nopud.h> */
#define pud_set_fixmap(addw)		NUWW
#define pud_set_fixmap_offset(pgdp, addw)	((pud_t *)pgdp)
#define pud_cweaw_fixmap()

#define pud_offset_kimg(diw,addw)	((pud_t *)diw)

#endif  /* CONFIG_PGTABWE_WEVEWS > 3 */

#define pgd_EWWOW(e)	\
	pw_eww("%s:%d: bad pgd %016wwx.\n", __FIWE__, __WINE__, pgd_vaw(e))

#define pgd_set_fixmap(addw)	((pgd_t *)set_fixmap_offset(FIX_PGD, addw))
#define pgd_cweaw_fixmap()	cweaw_fixmap(FIX_PGD)

static inwine pte_t pte_modify(pte_t pte, pgpwot_t newpwot)
{
	/*
	 * Nowmaw and Nowmaw-Tagged awe two diffewent memowy types and indices
	 * in MAIW_EW1. The mask bewow has to incwude PTE_ATTWINDX_MASK.
	 */
	const ptevaw_t mask = PTE_USEW | PTE_PXN | PTE_UXN | PTE_WDONWY |
			      PTE_PWOT_NONE | PTE_VAWID | PTE_WWITE | PTE_GP |
			      PTE_ATTWINDX_MASK;
	/* pwesewve the hawdwawe diwty infowmation */
	if (pte_hw_diwty(pte))
		pte = set_pte_bit(pte, __pgpwot(PTE_DIWTY));

	pte_vaw(pte) = (pte_vaw(pte) & ~mask) | (pgpwot_vaw(newpwot) & mask);
	/*
	 * If we end up cweawing hw diwtiness fow a sw-diwty PTE, set hawdwawe
	 * diwtiness again.
	 */
	if (pte_sw_diwty(pte))
		pte = pte_mkdiwty(pte);
	wetuwn pte;
}

static inwine pmd_t pmd_modify(pmd_t pmd, pgpwot_t newpwot)
{
	wetuwn pte_pmd(pte_modify(pmd_pte(pmd), newpwot));
}

#define __HAVE_AWCH_PTEP_SET_ACCESS_FWAGS
extewn int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
				 unsigned wong addwess, pte_t *ptep,
				 pte_t entwy, int diwty);

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define __HAVE_AWCH_PMDP_SET_ACCESS_FWAGS
static inwine int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pmd_t *pmdp,
					pmd_t entwy, int diwty)
{
	wetuwn ptep_set_access_fwags(vma, addwess, (pte_t *)pmdp, pmd_pte(entwy), diwty);
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

#ifdef CONFIG_PAGE_TABWE_CHECK
static inwine boow pte_usew_accessibwe_page(pte_t pte)
{
	wetuwn pte_pwesent(pte) && (pte_usew(pte) || pte_usew_exec(pte));
}

static inwine boow pmd_usew_accessibwe_page(pmd_t pmd)
{
	wetuwn pmd_weaf(pmd) && !pmd_pwesent_invawid(pmd) && (pmd_usew(pmd) || pmd_usew_exec(pmd));
}

static inwine boow pud_usew_accessibwe_page(pud_t pud)
{
	wetuwn pud_weaf(pud) && (pud_usew(pud) || pud_usew_exec(pud));
}
#endif

/*
 * Atomic pte/pmd modifications.
 */
#define __HAVE_AWCH_PTEP_TEST_AND_CWEAW_YOUNG
static inwine int __ptep_test_and_cweaw_young(pte_t *ptep)
{
	pte_t owd_pte, pte;

	pte = WEAD_ONCE(*ptep);
	do {
		owd_pte = pte;
		pte = pte_mkowd(pte);
		pte_vaw(pte) = cmpxchg_wewaxed(&pte_vaw(*ptep),
					       pte_vaw(owd_pte), pte_vaw(pte));
	} whiwe (pte_vaw(pte) != pte_vaw(owd_pte));

	wetuwn pte_young(pte);
}

static inwine int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess,
					    pte_t *ptep)
{
	wetuwn __ptep_test_and_cweaw_young(ptep);
}

#define __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
static inwine int ptep_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
					 unsigned wong addwess, pte_t *ptep)
{
	int young = ptep_test_and_cweaw_young(vma, addwess, ptep);

	if (young) {
		/*
		 * We can ewide the twaiwing DSB hewe since the wowst that can
		 * happen is that a CPU continues to use the young entwy in its
		 * TWB and we mistakenwy wecwaim the associated page. The
		 * window fow such an event is bounded by the next
		 * context-switch, which pwovides a DSB to compwete the TWB
		 * invawidation.
		 */
		fwush_twb_page_nosync(vma, addwess);
	}

	wetuwn young;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define __HAVE_AWCH_PMDP_TEST_AND_CWEAW_YOUNG
static inwine int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
					    unsigned wong addwess,
					    pmd_t *pmdp)
{
	wetuwn ptep_test_and_cweaw_young(vma, addwess, (pte_t *)pmdp);
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#define __HAVE_AWCH_PTEP_GET_AND_CWEAW
static inwine pte_t ptep_get_and_cweaw(stwuct mm_stwuct *mm,
				       unsigned wong addwess, pte_t *ptep)
{
	pte_t pte = __pte(xchg_wewaxed(&pte_vaw(*ptep), 0));

	page_tabwe_check_pte_cweaw(mm, pte);

	wetuwn pte;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define __HAVE_AWCH_PMDP_HUGE_GET_AND_CWEAW
static inwine pmd_t pmdp_huge_get_and_cweaw(stwuct mm_stwuct *mm,
					    unsigned wong addwess, pmd_t *pmdp)
{
	pmd_t pmd = __pmd(xchg_wewaxed(&pmd_vaw(*pmdp), 0));

	page_tabwe_check_pmd_cweaw(mm, pmd);

	wetuwn pmd;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

/*
 * ptep_set_wwpwotect - mawk wead-onwy whiwe twasfewwing potentiaw hawdwawe
 * diwty status (PTE_DBM && !PTE_WDONWY) to the softwawe PTE_DIWTY bit.
 */
#define __HAVE_AWCH_PTEP_SET_WWPWOTECT
static inwine void ptep_set_wwpwotect(stwuct mm_stwuct *mm, unsigned wong addwess, pte_t *ptep)
{
	pte_t owd_pte, pte;

	pte = WEAD_ONCE(*ptep);
	do {
		owd_pte = pte;
		pte = pte_wwpwotect(pte);
		pte_vaw(pte) = cmpxchg_wewaxed(&pte_vaw(*ptep),
					       pte_vaw(owd_pte), pte_vaw(pte));
	} whiwe (pte_vaw(pte) != pte_vaw(owd_pte));
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
#define __HAVE_AWCH_PMDP_SET_WWPWOTECT
static inwine void pmdp_set_wwpwotect(stwuct mm_stwuct *mm,
				      unsigned wong addwess, pmd_t *pmdp)
{
	ptep_set_wwpwotect(mm, addwess, (pte_t *)pmdp);
}

#define pmdp_estabwish pmdp_estabwish
static inwine pmd_t pmdp_estabwish(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmdp, pmd_t pmd)
{
	page_tabwe_check_pmd_set(vma->vm_mm, pmdp, pmd);
	wetuwn __pmd(xchg_wewaxed(&pmd_vaw(*pmdp), pmd_vaw(pmd)));
}
#endif

/*
 * Encode and decode a swap entwy:
 *	bits 0-1:	pwesent (must be zewo)
 *	bits 2:		wemembew PG_anon_excwusive
 *	bits 3-7:	swap type
 *	bits 8-57:	swap offset
 *	bit  58:	PTE_PWOT_NONE (must be zewo)
 */
#define __SWP_TYPE_SHIFT	3
#define __SWP_TYPE_BITS		5
#define __SWP_OFFSET_BITS	50
#define __SWP_TYPE_MASK		((1 << __SWP_TYPE_BITS) - 1)
#define __SWP_OFFSET_SHIFT	(__SWP_TYPE_BITS + __SWP_TYPE_SHIFT)
#define __SWP_OFFSET_MASK	((1UW << __SWP_OFFSET_BITS) - 1)

#define __swp_type(x)		(((x).vaw >> __SWP_TYPE_SHIFT) & __SWP_TYPE_MASK)
#define __swp_offset(x)		(((x).vaw >> __SWP_OFFSET_SHIFT) & __SWP_OFFSET_MASK)
#define __swp_entwy(type,offset) ((swp_entwy_t) { ((type) << __SWP_TYPE_SHIFT) | ((offset) << __SWP_OFFSET_SHIFT) })

#define __pte_to_swp_entwy(pte)	((swp_entwy_t) { pte_vaw(pte) })
#define __swp_entwy_to_pte(swp)	((pte_t) { (swp).vaw })

#ifdef CONFIG_AWCH_ENABWE_THP_MIGWATION
#define __pmd_to_swp_entwy(pmd)		((swp_entwy_t) { pmd_vaw(pmd) })
#define __swp_entwy_to_pmd(swp)		__pmd((swp).vaw)
#endif /* CONFIG_AWCH_ENABWE_THP_MIGWATION */

/*
 * Ensuwe that thewe awe not mowe swap fiwes than can be encoded in the kewnew
 * PTEs.
 */
#define MAX_SWAPFIWES_CHECK() BUIWD_BUG_ON(MAX_SWAPFIWES_SHIFT > __SWP_TYPE_BITS)

#ifdef CONFIG_AWM64_MTE

#define __HAVE_AWCH_PWEPAWE_TO_SWAP
static inwine int awch_pwepawe_to_swap(stwuct page *page)
{
	if (system_suppowts_mte())
		wetuwn mte_save_tags(page);
	wetuwn 0;
}

#define __HAVE_AWCH_SWAP_INVAWIDATE
static inwine void awch_swap_invawidate_page(int type, pgoff_t offset)
{
	if (system_suppowts_mte())
		mte_invawidate_tags(type, offset);
}

static inwine void awch_swap_invawidate_awea(int type)
{
	if (system_suppowts_mte())
		mte_invawidate_tags_awea(type);
}

#define __HAVE_AWCH_SWAP_WESTOWE
static inwine void awch_swap_westowe(swp_entwy_t entwy, stwuct fowio *fowio)
{
	if (system_suppowts_mte())
		mte_westowe_tags(entwy, &fowio->page);
}

#endif /* CONFIG_AWM64_MTE */

/*
 * On AAwch64, the cache cohewency is handwed via the set_pte_at() function.
 */
static inwine void update_mmu_cache_wange(stwuct vm_fauwt *vmf,
		stwuct vm_awea_stwuct *vma, unsigned wong addw, pte_t *ptep,
		unsigned int nw)
{
	/*
	 * We don't do anything hewe, so thewe's a vewy smaww chance of
	 * us wetaking a usew fauwt which we just fixed up. The awtewnative
	 * is doing a dsb(ishst), but that penawises the fastpath.
	 */
}

#define update_mmu_cache(vma, addw, ptep) \
	update_mmu_cache_wange(NUWW, vma, addw, ptep, 1)
#define update_mmu_cache_pmd(vma, addwess, pmd) do { } whiwe (0)

#ifdef CONFIG_AWM64_PA_BITS_52
#define phys_to_ttbw(addw)	(((addw) | ((addw) >> 46)) & TTBW_BADDW_MASK_52)
#ewse
#define phys_to_ttbw(addw)	(addw)
#endif

/*
 * On awm64 without hawdwawe Access Fwag, copying fwom usew wiww faiw because
 * the pte is owd and cannot be mawked young. So we awways end up with zewoed
 * page aftew fowk() + CoW fow pfn mappings. We don't awways have a
 * hawdwawe-managed access fwag on awm64.
 */
#define awch_has_hw_pte_young		cpu_has_hw_af

/*
 * Expewimentawwy, it's cheap to set the access fwag in hawdwawe and we
 * benefit fwom pwefauwting mappings as 'owd' to stawt with.
 */
#define awch_wants_owd_pwefauwted_pte	cpu_has_hw_af

static inwine boow pud_sect_suppowted(void)
{
	wetuwn PAGE_SIZE == SZ_4K;
}


#define __HAVE_AWCH_PTEP_MODIFY_PWOT_TWANSACTION
#define ptep_modify_pwot_stawt ptep_modify_pwot_stawt
extewn pte_t ptep_modify_pwot_stawt(stwuct vm_awea_stwuct *vma,
				    unsigned wong addw, pte_t *ptep);

#define ptep_modify_pwot_commit ptep_modify_pwot_commit
extewn void ptep_modify_pwot_commit(stwuct vm_awea_stwuct *vma,
				    unsigned wong addw, pte_t *ptep,
				    pte_t owd_pte, pte_t new_pte);
#endif /* !__ASSEMBWY__ */

#endif /* __ASM_PGTABWE_H */
