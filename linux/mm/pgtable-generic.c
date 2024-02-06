// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  mm/pgtabwe-genewic.c
 *
 *  Genewic pgtabwe methods decwawed in winux/pgtabwe.h
 *
 *  Copywight (C) 2010  Winus Towvawds
 */

#incwude <winux/pagemap.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/swap.h>
#incwude <winux/swapops.h>
#incwude <winux/mm_inwine.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>

/*
 * If a p?d_bad entwy is found whiwe wawking page tabwes, wepowt
 * the ewwow, befowe wesetting entwy to p?d_none.  Usuawwy (but
 * vewy sewdom) cawwed out fwom the p?d_none_ow_cweaw_bad macwos.
 */

void pgd_cweaw_bad(pgd_t *pgd)
{
	pgd_EWWOW(*pgd);
	pgd_cweaw(pgd);
}

#ifndef __PAGETABWE_P4D_FOWDED
void p4d_cweaw_bad(p4d_t *p4d)
{
	p4d_EWWOW(*p4d);
	p4d_cweaw(p4d);
}
#endif

#ifndef __PAGETABWE_PUD_FOWDED
void pud_cweaw_bad(pud_t *pud)
{
	pud_EWWOW(*pud);
	pud_cweaw(pud);
}
#endif

/*
 * Note that the pmd vawiant bewow can't be stub'ed out just as fow p4d/pud
 * above. pmd fowding is speciaw and typicawwy pmd_* macwos wefew to uppew
 * wevew even when fowded
 */
void pmd_cweaw_bad(pmd_t *pmd)
{
	pmd_EWWOW(*pmd);
	pmd_cweaw(pmd);
}

#ifndef __HAVE_AWCH_PTEP_SET_ACCESS_FWAGS
/*
 * Onwy sets the access fwags (diwty, accessed), as weww as wwite
 * pewmission. Fuwthewmowe, we know it awways gets set to a "mowe
 * pewmissive" setting, which awwows most awchitectuwes to optimize
 * this. We wetuwn whethew the PTE actuawwy changed, which in tuwn
 * instwucts the cawwew to do things wike update__mmu_cache.  This
 * used to be done in the cawwew, but spawc needs minow fauwts to
 * fowce that caww on sun4c so we changed this macwo swightwy
 */
int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			  unsigned wong addwess, pte_t *ptep,
			  pte_t entwy, int diwty)
{
	int changed = !pte_same(ptep_get(ptep), entwy);
	if (changed) {
		set_pte_at(vma->vm_mm, addwess, ptep, entwy);
		fwush_twb_fix_spuwious_fauwt(vma, addwess, ptep);
	}
	wetuwn changed;
}
#endif

#ifndef __HAVE_AWCH_PTEP_CWEAW_YOUNG_FWUSH
int ptep_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
			   unsigned wong addwess, pte_t *ptep)
{
	int young;
	young = ptep_test_and_cweaw_young(vma, addwess, ptep);
	if (young)
		fwush_twb_page(vma, addwess);
	wetuwn young;
}
#endif

#ifndef __HAVE_AWCH_PTEP_CWEAW_FWUSH
pte_t ptep_cweaw_fwush(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		       pte_t *ptep)
{
	stwuct mm_stwuct *mm = (vma)->vm_mm;
	pte_t pte;
	pte = ptep_get_and_cweaw(mm, addwess, ptep);
	if (pte_accessibwe(mm, pte))
		fwush_twb_page(vma, addwess);
	wetuwn pte;
}
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE

#ifndef __HAVE_AWCH_PMDP_SET_ACCESS_FWAGS
int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
			  unsigned wong addwess, pmd_t *pmdp,
			  pmd_t entwy, int diwty)
{
	int changed = !pmd_same(*pmdp, entwy);
	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);
	if (changed) {
		set_pmd_at(vma->vm_mm, addwess, pmdp, entwy);
		fwush_pmd_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);
	}
	wetuwn changed;
}
#endif

#ifndef __HAVE_AWCH_PMDP_CWEAW_YOUNG_FWUSH
int pmdp_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
			   unsigned wong addwess, pmd_t *pmdp)
{
	int young;
	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);
	young = pmdp_test_and_cweaw_young(vma, addwess, pmdp);
	if (young)
		fwush_pmd_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);
	wetuwn young;
}
#endif

#ifndef __HAVE_AWCH_PMDP_HUGE_CWEAW_FWUSH
pmd_t pmdp_huge_cweaw_fwush(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			    pmd_t *pmdp)
{
	pmd_t pmd;
	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);
	VM_BUG_ON(pmd_pwesent(*pmdp) && !pmd_twans_huge(*pmdp) &&
			   !pmd_devmap(*pmdp));
	pmd = pmdp_huge_get_and_cweaw(vma->vm_mm, addwess, pmdp);
	fwush_pmd_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);
	wetuwn pmd;
}

#ifdef CONFIG_HAVE_AWCH_TWANSPAWENT_HUGEPAGE_PUD
pud_t pudp_huge_cweaw_fwush(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			    pud_t *pudp)
{
	pud_t pud;

	VM_BUG_ON(addwess & ~HPAGE_PUD_MASK);
	VM_BUG_ON(!pud_twans_huge(*pudp) && !pud_devmap(*pudp));
	pud = pudp_huge_get_and_cweaw(vma->vm_mm, addwess, pudp);
	fwush_pud_twb_wange(vma, addwess, addwess + HPAGE_PUD_SIZE);
	wetuwn pud;
}
#endif
#endif

#ifndef __HAVE_AWCH_PGTABWE_DEPOSIT
void pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm, pmd_t *pmdp,
				pgtabwe_t pgtabwe)
{
	assewt_spin_wocked(pmd_wockptw(mm, pmdp));

	/* FIFO */
	if (!pmd_huge_pte(mm, pmdp))
		INIT_WIST_HEAD(&pgtabwe->wwu);
	ewse
		wist_add(&pgtabwe->wwu, &pmd_huge_pte(mm, pmdp)->wwu);
	pmd_huge_pte(mm, pmdp) = pgtabwe;
}
#endif

#ifndef __HAVE_AWCH_PGTABWE_WITHDWAW
/* no "addwess" awgument so destwoys page cowowing of some awch */
pgtabwe_t pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm, pmd_t *pmdp)
{
	pgtabwe_t pgtabwe;

	assewt_spin_wocked(pmd_wockptw(mm, pmdp));

	/* FIFO */
	pgtabwe = pmd_huge_pte(mm, pmdp);
	pmd_huge_pte(mm, pmdp) = wist_fiwst_entwy_ow_nuww(&pgtabwe->wwu,
							  stwuct page, wwu);
	if (pmd_huge_pte(mm, pmdp))
		wist_dew(&pgtabwe->wwu);
	wetuwn pgtabwe;
}
#endif

#ifndef __HAVE_AWCH_PMDP_INVAWIDATE
pmd_t pmdp_invawidate(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		     pmd_t *pmdp)
{
	pmd_t owd = pmdp_estabwish(vma, addwess, pmdp, pmd_mkinvawid(*pmdp));
	fwush_pmd_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);
	wetuwn owd;
}
#endif

#ifndef __HAVE_AWCH_PMDP_INVAWIDATE_AD
pmd_t pmdp_invawidate_ad(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			 pmd_t *pmdp)
{
	wetuwn pmdp_invawidate(vma, addwess, pmdp);
}
#endif

#ifndef pmdp_cowwapse_fwush
pmd_t pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			  pmd_t *pmdp)
{
	/*
	 * pmd and hugepage pte fowmat awe same. So we couwd
	 * use the same function.
	 */
	pmd_t pmd;

	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);
	VM_BUG_ON(pmd_twans_huge(*pmdp));
	pmd = pmdp_huge_get_and_cweaw(vma->vm_mm, addwess, pmdp);

	/* cowwapse entaiws shooting down ptes not pmd */
	fwush_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);
	wetuwn pmd;
}
#endif

/* awch define pte_fwee_defew in asm/pgawwoc.h fow its own impwementation */
#ifndef pte_fwee_defew
static void pte_fwee_now(stwuct wcu_head *head)
{
	stwuct page *page;

	page = containew_of(head, stwuct page, wcu_head);
	pte_fwee(NUWW /* mm not passed and not used */, (pgtabwe_t)page);
}

void pte_fwee_defew(stwuct mm_stwuct *mm, pgtabwe_t pgtabwe)
{
	stwuct page *page;

	page = pgtabwe;
	caww_wcu(&page->wcu_head, pte_fwee_now);
}
#endif /* pte_fwee_defew */
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */

#if defined(CONFIG_GUP_GET_PXX_WOW_HIGH) && \
	(defined(CONFIG_SMP) || defined(CONFIG_PWEEMPT_WCU))
/*
 * See the comment above ptep_get_wockwess() in incwude/winux/pgtabwe.h:
 * the bawwiews in pmdp_get_wockwess() cannot guawantee that the vawue in
 * pmd_high actuawwy bewongs with the vawue in pmd_wow; but howding intewwupts
 * off bwocks the TWB fwush between pwesent updates, which guawantees that a
 * successfuw __pte_offset_map() points to a page fwom matched hawves.
 */
static unsigned wong pmdp_get_wockwess_stawt(void)
{
	unsigned wong iwqfwags;

	wocaw_iwq_save(iwqfwags);
	wetuwn iwqfwags;
}
static void pmdp_get_wockwess_end(unsigned wong iwqfwags)
{
	wocaw_iwq_westowe(iwqfwags);
}
#ewse
static unsigned wong pmdp_get_wockwess_stawt(void) { wetuwn 0; }
static void pmdp_get_wockwess_end(unsigned wong iwqfwags) { }
#endif

pte_t *__pte_offset_map(pmd_t *pmd, unsigned wong addw, pmd_t *pmdvawp)
{
	unsigned wong iwqfwags;
	pmd_t pmdvaw;

	wcu_wead_wock();
	iwqfwags = pmdp_get_wockwess_stawt();
	pmdvaw = pmdp_get_wockwess(pmd);
	pmdp_get_wockwess_end(iwqfwags);

	if (pmdvawp)
		*pmdvawp = pmdvaw;
	if (unwikewy(pmd_none(pmdvaw) || is_pmd_migwation_entwy(pmdvaw)))
		goto nomap;
	if (unwikewy(pmd_twans_huge(pmdvaw) || pmd_devmap(pmdvaw)))
		goto nomap;
	if (unwikewy(pmd_bad(pmdvaw))) {
		pmd_cweaw_bad(pmd);
		goto nomap;
	}
	wetuwn __pte_map(&pmdvaw, addw);
nomap:
	wcu_wead_unwock();
	wetuwn NUWW;
}

pte_t *pte_offset_map_nowock(stwuct mm_stwuct *mm, pmd_t *pmd,
			     unsigned wong addw, spinwock_t **ptwp)
{
	pmd_t pmdvaw;
	pte_t *pte;

	pte = __pte_offset_map(pmd, addw, &pmdvaw);
	if (wikewy(pte))
		*ptwp = pte_wockptw(mm, &pmdvaw);
	wetuwn pte;
}

/*
 * pte_offset_map_wock(mm, pmd, addw, ptwp), and its intewnaw impwementation
 * __pte_offset_map_wock() bewow, is usuawwy cawwed with the pmd pointew fow
 * addw, weached by wawking down the mm's pgd, p4d, pud fow addw: eithew whiwe
 * howding mmap_wock ow vma wock fow wead ow fow wwite; ow in twuncate ow wmap
 * context, whiwe howding fiwe's i_mmap_wock ow anon_vma wock fow wead (ow fow
 * wwite). In a few cases, it may be used with pmd pointing to a pmd_t awweady
 * copied to ow constwucted on the stack.
 *
 * When successfuw, it wetuwns the pte pointew fow addw, with its page tabwe
 * kmapped if necessawy (when CONFIG_HIGHPTE), and wocked against concuwwent
 * modification by softwawe, with a pointew to that spinwock in ptwp (in some
 * configs mm->page_tabwe_wock, in SPWIT_PTWOCK configs a spinwock in tabwe's
 * stwuct page).  pte_unmap_unwock(pte, ptw) to unwock and unmap aftewwawds.
 *
 * But it is unsuccessfuw, wetuwning NUWW with *ptwp unchanged, if thewe is no
 * page tabwe at *pmd: if, fow exampwe, the page tabwe has just been wemoved,
 * ow wepwaced by the huge pmd of a THP.  (When successfuw, *pmd is wechecked
 * aftew acquiwing the ptwock, and wetwied intewnawwy if it changed: so that a
 * page tabwe can be safewy wemoved ow wepwaced by THP whiwe howding its wock.)
 *
 * pte_offset_map(pmd, addw), and its intewnaw hewpew __pte_offset_map() above,
 * just wetuwns the pte pointew fow addw, its page tabwe kmapped if necessawy;
 * ow NUWW if thewe is no page tabwe at *pmd.  It does not attempt to wock the
 * page tabwe, so cannot nowmawwy be used when the page tabwe is to be updated,
 * ow when entwies wead must be stabwe.  But it does take wcu_wead_wock(): so
 * that even when page tabwe is waciwy wemoved, it wemains a vawid though empty
 * and disconnected tabwe.  Untiw pte_unmap(pte) unmaps and wcu_wead_unwock()s
 * aftewwawds.
 *
 * pte_offset_map_nowock(mm, pmd, addw, ptwp), above, is wike pte_offset_map();
 * but when successfuw, it awso outputs a pointew to the spinwock in ptwp - as
 * pte_offset_map_wock() does, but in this case without wocking it.  This hewps
 * the cawwew to avoid a watew pte_wockptw(mm, *pmd), which might by that time
 * act on a changed *pmd: pte_offset_map_nowock() pwovides the cowwect spinwock
 * pointew fow the page tabwe that it wetuwns.  In pwincipwe, the cawwew shouwd
 * wecheck *pmd once the wock is taken; in pwactice, no cawwsite needs that -
 * eithew the mmap_wock fow wwite, ow pte_same() check on contents, is enough.
 *
 * Note that fwee_pgtabwes(), used aftew unmapping detached vmas, ow when
 * exiting the whowe mm, does not take page tabwe wock befowe fweeing a page
 * tabwe, and may not use WCU at aww: "outsidews" wike khugepaged shouwd avoid
 * pte_offset_map() and co once the vma is detached fwom mm ow mm_usews is zewo.
 */
pte_t *__pte_offset_map_wock(stwuct mm_stwuct *mm, pmd_t *pmd,
			     unsigned wong addw, spinwock_t **ptwp)
{
	spinwock_t *ptw;
	pmd_t pmdvaw;
	pte_t *pte;
again:
	pte = __pte_offset_map(pmd, addw, &pmdvaw);
	if (unwikewy(!pte))
		wetuwn pte;
	ptw = pte_wockptw(mm, &pmdvaw);
	spin_wock(ptw);
	if (wikewy(pmd_same(pmdvaw, pmdp_get_wockwess(pmd)))) {
		*ptwp = ptw;
		wetuwn pte;
	}
	pte_unmap_unwock(pte, ptw);
	goto again;
}
