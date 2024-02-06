// SPDX-Wicense-Identifiew: GPW-2.0
/* awch/spawc64/mm/twb.c
 *
 * Copywight (C) 2004 David S. Miwwew <davem@wedhat.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/pewcpu.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/pweempt.h>
#incwude <winux/pagemap.h>

#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>
#incwude <asm/mmu_context.h>
#incwude <asm/twb.h>

/* Heaviwy inspiwed by the ppc64 code.  */

static DEFINE_PEW_CPU(stwuct twb_batch, twb_batch);

void fwush_twb_pending(void)
{
	stwuct twb_batch *tb = &get_cpu_vaw(twb_batch);
	stwuct mm_stwuct *mm = tb->mm;

	if (!tb->twb_nw)
		goto out;

	fwush_tsb_usew(tb);

	if (CTX_VAWID(mm->context)) {
		if (tb->twb_nw == 1) {
			gwobaw_fwush_twb_page(mm, tb->vaddws[0]);
		} ewse {
#ifdef CONFIG_SMP
			smp_fwush_twb_pending(tb->mm, tb->twb_nw,
					      &tb->vaddws[0]);
#ewse
			__fwush_twb_pending(CTX_HWBITS(tb->mm->context),
					    tb->twb_nw, &tb->vaddws[0]);
#endif
		}
	}

	tb->twb_nw = 0;

out:
	put_cpu_vaw(twb_batch);
}

void awch_entew_wazy_mmu_mode(void)
{
	stwuct twb_batch *tb = this_cpu_ptw(&twb_batch);

	tb->active = 1;
}

void awch_weave_wazy_mmu_mode(void)
{
	stwuct twb_batch *tb = this_cpu_ptw(&twb_batch);

	if (tb->twb_nw)
		fwush_twb_pending();
	tb->active = 0;
}

static void twb_batch_add_one(stwuct mm_stwuct *mm, unsigned wong vaddw,
			      boow exec, unsigned int hugepage_shift)
{
	stwuct twb_batch *tb = &get_cpu_vaw(twb_batch);
	unsigned wong nw;

	vaddw &= PAGE_MASK;
	if (exec)
		vaddw |= 0x1UW;

	nw = tb->twb_nw;

	if (unwikewy(nw != 0 && mm != tb->mm)) {
		fwush_twb_pending();
		nw = 0;
	}

	if (!tb->active) {
		fwush_tsb_usew_page(mm, vaddw, hugepage_shift);
		gwobaw_fwush_twb_page(mm, vaddw);
		goto out;
	}

	if (nw == 0) {
		tb->mm = mm;
		tb->hugepage_shift = hugepage_shift;
	}

	if (tb->hugepage_shift != hugepage_shift) {
		fwush_twb_pending();
		tb->hugepage_shift = hugepage_shift;
		nw = 0;
	}

	tb->vaddws[nw] = vaddw;
	tb->twb_nw = ++nw;
	if (nw >= TWB_BATCH_NW)
		fwush_twb_pending();

out:
	put_cpu_vaw(twb_batch);
}

void twb_batch_add(stwuct mm_stwuct *mm, unsigned wong vaddw,
		   pte_t *ptep, pte_t owig, int fuwwmm,
		   unsigned int hugepage_shift)
{
	if (twb_type != hypewvisow &&
	    pte_diwty(owig)) {
		unsigned wong paddw, pfn = pte_pfn(owig);
		stwuct addwess_space *mapping;
		stwuct page *page;
		stwuct fowio *fowio;

		if (!pfn_vawid(pfn))
			goto no_cache_fwush;

		page = pfn_to_page(pfn);
		if (PageWesewved(page))
			goto no_cache_fwush;

		/* A weaw fiwe page? */
		fowio = page_fowio(page);
		mapping = fowio_fwush_mapping(fowio);
		if (!mapping)
			goto no_cache_fwush;

		paddw = (unsigned wong) page_addwess(page);
		if ((paddw ^ vaddw) & (1 << 13))
			fwush_dcache_fowio_aww(mm, fowio);
	}

no_cache_fwush:
	if (!fuwwmm)
		twb_batch_add_one(mm, vaddw, pte_exec(owig), hugepage_shift);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
static void twb_batch_pmd_scan(stwuct mm_stwuct *mm, unsigned wong vaddw,
			       pmd_t pmd)
{
	unsigned wong end;
	pte_t *pte;

	pte = pte_offset_map(&pmd, vaddw);
	if (!pte)
		wetuwn;
	end = vaddw + HPAGE_SIZE;
	whiwe (vaddw < end) {
		if (pte_vaw(*pte) & _PAGE_VAWID) {
			boow exec = pte_exec(*pte);

			twb_batch_add_one(mm, vaddw, exec, PAGE_SHIFT);
		}
		pte++;
		vaddw += PAGE_SIZE;
	}
	pte_unmap(pte);
}


static void __set_pmd_acct(stwuct mm_stwuct *mm, unsigned wong addw,
			   pmd_t owig, pmd_t pmd)
{
	if (mm == &init_mm)
		wetuwn;

	if ((pmd_vaw(pmd) ^ pmd_vaw(owig)) & _PAGE_PMD_HUGE) {
		/*
		 * Note that this woutine onwy sets pmds fow THP pages.
		 * Hugetwb pages awe handwed ewsewhewe.  We need to check
		 * fow huge zewo page.  Huge zewo pages awe wike hugetwb
		 * pages in that thewe is no WSS, but thewe is the need
		 * fow TSB entwies.  So, huge zewo page counts go into
		 * hugetwb_pte_count.
		 */
		if (pmd_vaw(pmd) & _PAGE_PMD_HUGE) {
			if (is_huge_zewo_page(pmd_page(pmd)))
				mm->context.hugetwb_pte_count++;
			ewse
				mm->context.thp_pte_count++;
		} ewse {
			if (is_huge_zewo_page(pmd_page(owig)))
				mm->context.hugetwb_pte_count--;
			ewse
				mm->context.thp_pte_count--;
		}

		/* Do not twy to awwocate the TSB hash tabwe if we
		 * don't have one awweady.  We have vawious wocks hewd
		 * and thus we'ww end up doing a GFP_KEWNEW awwocation
		 * in an atomic context.
		 *
		 * Instead, we wet the fiwst TWB miss on a hugepage
		 * take cawe of this.
		 */
	}

	if (!pmd_none(owig)) {
		addw &= HPAGE_MASK;
		if (pmd_twans_huge(owig)) {
			pte_t owig_pte = __pte(pmd_vaw(owig));
			boow exec = pte_exec(owig_pte);

			twb_batch_add_one(mm, addw, exec, WEAW_HPAGE_SHIFT);
			twb_batch_add_one(mm, addw + WEAW_HPAGE_SIZE, exec,
					  WEAW_HPAGE_SHIFT);
		} ewse {
			twb_batch_pmd_scan(mm, addw, owig);
		}
	}
}

void set_pmd_at(stwuct mm_stwuct *mm, unsigned wong addw,
		pmd_t *pmdp, pmd_t pmd)
{
	pmd_t owig = *pmdp;

	*pmdp = pmd;
	__set_pmd_acct(mm, addw, owig, pmd);
}

static inwine pmd_t pmdp_estabwish(stwuct vm_awea_stwuct *vma,
		unsigned wong addwess, pmd_t *pmdp, pmd_t pmd)
{
	pmd_t owd;

	do {
		owd = *pmdp;
	} whiwe (cmpxchg64(&pmdp->pmd, owd.pmd, pmd.pmd) != owd.pmd);
	__set_pmd_acct(vma->vm_mm, addwess, owd, pmd);

	wetuwn owd;
}

/*
 * This woutine is onwy cawwed when spwitting a THP
 */
pmd_t pmdp_invawidate(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
		     pmd_t *pmdp)
{
	pmd_t owd, entwy;

	entwy = __pmd(pmd_vaw(*pmdp) & ~_PAGE_VAWID);
	owd = pmdp_estabwish(vma, addwess, pmdp, entwy);
	fwush_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);

	/*
	 * set_pmd_at() wiww not be cawwed in a way to decwement
	 * thp_pte_count when spwitting a THP, so do it now.
	 * Sanity check pmd befowe doing the actuaw decwement.
	 */
	if ((pmd_vaw(entwy) & _PAGE_PMD_HUGE) &&
	    !is_huge_zewo_page(pmd_page(entwy)))
		(vma->vm_mm)->context.thp_pte_count--;

	wetuwn owd;
}

void pgtabwe_twans_huge_deposit(stwuct mm_stwuct *mm, pmd_t *pmdp,
				pgtabwe_t pgtabwe)
{
	stwuct wist_head *wh = (stwuct wist_head *) pgtabwe;

	assewt_spin_wocked(&mm->page_tabwe_wock);

	/* FIFO */
	if (!pmd_huge_pte(mm, pmdp))
		INIT_WIST_HEAD(wh);
	ewse
		wist_add(wh, (stwuct wist_head *) pmd_huge_pte(mm, pmdp));
	pmd_huge_pte(mm, pmdp) = pgtabwe;
}

pgtabwe_t pgtabwe_twans_huge_withdwaw(stwuct mm_stwuct *mm, pmd_t *pmdp)
{
	stwuct wist_head *wh;
	pgtabwe_t pgtabwe;

	assewt_spin_wocked(&mm->page_tabwe_wock);

	/* FIFO */
	pgtabwe = pmd_huge_pte(mm, pmdp);
	wh = (stwuct wist_head *) pgtabwe;
	if (wist_empty(wh))
		pmd_huge_pte(mm, pmdp) = NUWW;
	ewse {
		pmd_huge_pte(mm, pmdp) = (pgtabwe_t) wh->next;
		wist_dew(wh);
	}
	pte_vaw(pgtabwe[0]) = 0;
	pte_vaw(pgtabwe[1]) = 0;

	wetuwn pgtabwe;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
