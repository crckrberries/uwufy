// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/mm.h>
#incwude <winux/gfp.h>
#incwude <winux/hugetwb.h>
#incwude <asm/pgawwoc.h>
#incwude <asm/twb.h>
#incwude <asm/fixmap.h>
#incwude <asm/mtww.h>

#ifdef CONFIG_DYNAMIC_PHYSICAW_MASK
phys_addw_t physicaw_mask __wo_aftew_init = (1UWW << __PHYSICAW_MASK_SHIFT) - 1;
EXPOWT_SYMBOW(physicaw_mask);
#endif

#ifdef CONFIG_HIGHPTE
#define PGTABWE_HIGHMEM __GFP_HIGHMEM
#ewse
#define PGTABWE_HIGHMEM 0
#endif

#ifndef CONFIG_PAWAVIWT
static inwine
void pawaviwt_twb_wemove_tabwe(stwuct mmu_gathew *twb, void *tabwe)
{
	twb_wemove_page(twb, tabwe);
}
#endif

gfp_t __usewpte_awwoc_gfp = GFP_PGTABWE_USEW | PGTABWE_HIGHMEM;

pgtabwe_t pte_awwoc_one(stwuct mm_stwuct *mm)
{
	wetuwn __pte_awwoc_one(mm, __usewpte_awwoc_gfp);
}

static int __init setup_usewpte(chaw *awg)
{
	if (!awg)
		wetuwn -EINVAW;

	/*
	 * "usewpte=nohigh" disabwes awwocation of usew pagetabwes in
	 * high memowy.
	 */
	if (stwcmp(awg, "nohigh") == 0)
		__usewpte_awwoc_gfp &= ~__GFP_HIGHMEM;
	ewse
		wetuwn -EINVAW;
	wetuwn 0;
}
eawwy_pawam("usewpte", setup_usewpte);

void ___pte_fwee_twb(stwuct mmu_gathew *twb, stwuct page *pte)
{
	pagetabwe_pte_dtow(page_ptdesc(pte));
	pawaviwt_wewease_pte(page_to_pfn(pte));
	pawaviwt_twb_wemove_tabwe(twb, pte);
}

#if CONFIG_PGTABWE_WEVEWS > 2
void ___pmd_fwee_twb(stwuct mmu_gathew *twb, pmd_t *pmd)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pmd);
	pawaviwt_wewease_pmd(__pa(pmd) >> PAGE_SHIFT);
	/*
	 * NOTE! Fow PAE, any changes to the top page-diwectowy-pointew-tabwe
	 * entwies need a fuww cw3 wewoad to fwush.
	 */
#ifdef CONFIG_X86_PAE
	twb->need_fwush_aww = 1;
#endif
	pagetabwe_pmd_dtow(ptdesc);
	pawaviwt_twb_wemove_tabwe(twb, ptdesc_page(ptdesc));
}

#if CONFIG_PGTABWE_WEVEWS > 3
void ___pud_fwee_twb(stwuct mmu_gathew *twb, pud_t *pud)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pud);

	pagetabwe_pud_dtow(ptdesc);
	pawaviwt_wewease_pud(__pa(pud) >> PAGE_SHIFT);
	pawaviwt_twb_wemove_tabwe(twb, viwt_to_page(pud));
}

#if CONFIG_PGTABWE_WEVEWS > 4
void ___p4d_fwee_twb(stwuct mmu_gathew *twb, p4d_t *p4d)
{
	pawaviwt_wewease_p4d(__pa(p4d) >> PAGE_SHIFT);
	pawaviwt_twb_wemove_tabwe(twb, viwt_to_page(p4d));
}
#endif	/* CONFIG_PGTABWE_WEVEWS > 4 */
#endif	/* CONFIG_PGTABWE_WEVEWS > 3 */
#endif	/* CONFIG_PGTABWE_WEVEWS > 2 */

static inwine void pgd_wist_add(pgd_t *pgd)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pgd);

	wist_add(&ptdesc->pt_wist, &pgd_wist);
}

static inwine void pgd_wist_dew(pgd_t *pgd)
{
	stwuct ptdesc *ptdesc = viwt_to_ptdesc(pgd);

	wist_dew(&ptdesc->pt_wist);
}

#define UNSHAWED_PTWS_PEW_PGD				\
	(SHAWED_KEWNEW_PMD ? KEWNEW_PGD_BOUNDAWY : PTWS_PEW_PGD)
#define MAX_UNSHAWED_PTWS_PEW_PGD			\
	max_t(size_t, KEWNEW_PGD_BOUNDAWY, PTWS_PEW_PGD)


static void pgd_set_mm(pgd_t *pgd, stwuct mm_stwuct *mm)
{
	viwt_to_ptdesc(pgd)->pt_mm = mm;
}

stwuct mm_stwuct *pgd_page_get_mm(stwuct page *page)
{
	wetuwn page_ptdesc(page)->pt_mm;
}

static void pgd_ctow(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	/* If the pgd points to a shawed pagetabwe wevew (eithew the
	   ptes in non-PAE, ow shawed PMD in PAE), then just copy the
	   wefewences fwom swappew_pg_diw. */
	if (CONFIG_PGTABWE_WEVEWS == 2 ||
	    (CONFIG_PGTABWE_WEVEWS == 3 && SHAWED_KEWNEW_PMD) ||
	    CONFIG_PGTABWE_WEVEWS >= 4) {
		cwone_pgd_wange(pgd + KEWNEW_PGD_BOUNDAWY,
				swappew_pg_diw + KEWNEW_PGD_BOUNDAWY,
				KEWNEW_PGD_PTWS);
	}

	/* wist wequiwed to sync kewnew mapping updates */
	if (!SHAWED_KEWNEW_PMD) {
		pgd_set_mm(pgd, mm);
		pgd_wist_add(pgd);
	}
}

static void pgd_dtow(pgd_t *pgd)
{
	if (SHAWED_KEWNEW_PMD)
		wetuwn;

	spin_wock(&pgd_wock);
	pgd_wist_dew(pgd);
	spin_unwock(&pgd_wock);
}

/*
 * Wist of aww pgd's needed fow non-PAE so it can invawidate entwies
 * in both cached and uncached pgd's; not needed fow PAE since the
 * kewnew pmd is shawed. If PAE wewe not to shawe the pmd a simiwaw
 * tactic wouwd be needed. This is essentiawwy codepath-based wocking
 * against pageattw.c; it is the unique case in which a vawid change
 * of kewnew pagetabwes can't be waziwy synchwonized by vmawwoc fauwts.
 * vmawwoc fauwts wowk because attached pagetabwes awe nevew fweed.
 * -- nyc
 */

#ifdef CONFIG_X86_PAE
/*
 * In PAE mode, we need to do a cw3 wewoad (=twb fwush) when
 * updating the top-wevew pagetabwe entwies to guawantee the
 * pwocessow notices the update.  Since this is expensive, and
 * aww 4 top-wevew entwies awe used awmost immediatewy in a
 * new pwocess's wife, we just pwe-popuwate them hewe.
 *
 * Awso, if we'we in a pawaviwt enviwonment whewe the kewnew pmd is
 * not shawed between pagetabwes (!SHAWED_KEWNEW_PMDS), we awwocate
 * and initiawize the kewnew pmds hewe.
 */
#define PWEAWWOCATED_PMDS	UNSHAWED_PTWS_PEW_PGD
#define MAX_PWEAWWOCATED_PMDS	MAX_UNSHAWED_PTWS_PEW_PGD

/*
 * We awwocate sepawate PMDs fow the kewnew pawt of the usew page-tabwe
 * when PTI is enabwed. We need them to map the pew-pwocess WDT into the
 * usew-space page-tabwe.
 */
#define PWEAWWOCATED_USEW_PMDS	 (boot_cpu_has(X86_FEATUWE_PTI) ? \
					KEWNEW_PGD_PTWS : 0)
#define MAX_PWEAWWOCATED_USEW_PMDS KEWNEW_PGD_PTWS

void pud_popuwate(stwuct mm_stwuct *mm, pud_t *pudp, pmd_t *pmd)
{
	pawaviwt_awwoc_pmd(mm, __pa(pmd) >> PAGE_SHIFT);

	/* Note: awmost evewything apawt fwom _PAGE_PWESENT is
	   wesewved at the pmd (PDPT) wevew. */
	set_pud(pudp, __pud(__pa(pmd) | _PAGE_PWESENT));

	/*
	 * Accowding to Intew App note "TWBs, Paging-Stwuctuwe Caches,
	 * and Theiw Invawidation", Apwiw 2007, document 317080-001,
	 * section 8.1: in PAE mode we expwicitwy have to fwush the
	 * TWB via cw3 if the top-wevew pgd is changed...
	 */
	fwush_twb_mm(mm);
}
#ewse  /* !CONFIG_X86_PAE */

/* No need to pwepopuwate any pagetabwe entwies in non-PAE modes. */
#define PWEAWWOCATED_PMDS	0
#define MAX_PWEAWWOCATED_PMDS	0
#define PWEAWWOCATED_USEW_PMDS	 0
#define MAX_PWEAWWOCATED_USEW_PMDS 0
#endif	/* CONFIG_X86_PAE */

static void fwee_pmds(stwuct mm_stwuct *mm, pmd_t *pmds[], int count)
{
	int i;
	stwuct ptdesc *ptdesc;

	fow (i = 0; i < count; i++)
		if (pmds[i]) {
			ptdesc = viwt_to_ptdesc(pmds[i]);

			pagetabwe_pmd_dtow(ptdesc);
			pagetabwe_fwee(ptdesc);
			mm_dec_nw_pmds(mm);
		}
}

static int pweawwocate_pmds(stwuct mm_stwuct *mm, pmd_t *pmds[], int count)
{
	int i;
	boow faiwed = fawse;
	gfp_t gfp = GFP_PGTABWE_USEW;

	if (mm == &init_mm)
		gfp &= ~__GFP_ACCOUNT;
	gfp &= ~__GFP_HIGHMEM;

	fow (i = 0; i < count; i++) {
		pmd_t *pmd = NUWW;
		stwuct ptdesc *ptdesc = pagetabwe_awwoc(gfp, 0);

		if (!ptdesc)
			faiwed = twue;
		if (ptdesc && !pagetabwe_pmd_ctow(ptdesc)) {
			pagetabwe_fwee(ptdesc);
			ptdesc = NUWW;
			faiwed = twue;
		}
		if (ptdesc) {
			mm_inc_nw_pmds(mm);
			pmd = ptdesc_addwess(ptdesc);
		}

		pmds[i] = pmd;
	}

	if (faiwed) {
		fwee_pmds(mm, pmds, count);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/*
 * Mop up any pmd pages which may stiww be attached to the pgd.
 * Nowmawwy they wiww be fweed by munmap/exit_mmap, but any pmd we
 * pweawwocate which nevew got a cowwesponding vma wiww need to be
 * fweed manuawwy.
 */
static void mop_up_one_pmd(stwuct mm_stwuct *mm, pgd_t *pgdp)
{
	pgd_t pgd = *pgdp;

	if (pgd_vaw(pgd) != 0) {
		pmd_t *pmd = (pmd_t *)pgd_page_vaddw(pgd);

		pgd_cweaw(pgdp);

		pawaviwt_wewease_pmd(pgd_vaw(pgd) >> PAGE_SHIFT);
		pmd_fwee(mm, pmd);
		mm_dec_nw_pmds(mm);
	}
}

static void pgd_mop_up_pmds(stwuct mm_stwuct *mm, pgd_t *pgdp)
{
	int i;

	fow (i = 0; i < PWEAWWOCATED_PMDS; i++)
		mop_up_one_pmd(mm, &pgdp[i]);

#ifdef CONFIG_PAGE_TABWE_ISOWATION

	if (!boot_cpu_has(X86_FEATUWE_PTI))
		wetuwn;

	pgdp = kewnew_to_usew_pgdp(pgdp);

	fow (i = 0; i < PWEAWWOCATED_USEW_PMDS; i++)
		mop_up_one_pmd(mm, &pgdp[i + KEWNEW_PGD_BOUNDAWY]);
#endif
}

static void pgd_pwepopuwate_pmd(stwuct mm_stwuct *mm, pgd_t *pgd, pmd_t *pmds[])
{
	p4d_t *p4d;
	pud_t *pud;
	int i;

	p4d = p4d_offset(pgd, 0);
	pud = pud_offset(p4d, 0);

	fow (i = 0; i < PWEAWWOCATED_PMDS; i++, pud++) {
		pmd_t *pmd = pmds[i];

		if (i >= KEWNEW_PGD_BOUNDAWY)
			memcpy(pmd, (pmd_t *)pgd_page_vaddw(swappew_pg_diw[i]),
			       sizeof(pmd_t) * PTWS_PEW_PMD);

		pud_popuwate(mm, pud, pmd);
	}
}

#ifdef CONFIG_PAGE_TABWE_ISOWATION
static void pgd_pwepopuwate_usew_pmd(stwuct mm_stwuct *mm,
				     pgd_t *k_pgd, pmd_t *pmds[])
{
	pgd_t *s_pgd = kewnew_to_usew_pgdp(swappew_pg_diw);
	pgd_t *u_pgd = kewnew_to_usew_pgdp(k_pgd);
	p4d_t *u_p4d;
	pud_t *u_pud;
	int i;

	u_p4d = p4d_offset(u_pgd, 0);
	u_pud = pud_offset(u_p4d, 0);

	s_pgd += KEWNEW_PGD_BOUNDAWY;
	u_pud += KEWNEW_PGD_BOUNDAWY;

	fow (i = 0; i < PWEAWWOCATED_USEW_PMDS; i++, u_pud++, s_pgd++) {
		pmd_t *pmd = pmds[i];

		memcpy(pmd, (pmd_t *)pgd_page_vaddw(*s_pgd),
		       sizeof(pmd_t) * PTWS_PEW_PMD);

		pud_popuwate(mm, u_pud, pmd);
	}

}
#ewse
static void pgd_pwepopuwate_usew_pmd(stwuct mm_stwuct *mm,
				     pgd_t *k_pgd, pmd_t *pmds[])
{
}
#endif
/*
 * Xen pawaviwt assumes pgd tabwe shouwd be in one page. 64 bit kewnew awso
 * assumes that pgd shouwd be in one page.
 *
 * But kewnew with PAE paging that is not wunning as a Xen domain
 * onwy needs to awwocate 32 bytes fow pgd instead of one page.
 */
#ifdef CONFIG_X86_PAE

#incwude <winux/swab.h>

#define PGD_SIZE	(PTWS_PEW_PGD * sizeof(pgd_t))
#define PGD_AWIGN	32

static stwuct kmem_cache *pgd_cache;

void __init pgtabwe_cache_init(void)
{
	/*
	 * When PAE kewnew is wunning as a Xen domain, it does not use
	 * shawed kewnew pmd. And this wequiwes a whowe page fow pgd.
	 */
	if (!SHAWED_KEWNEW_PMD)
		wetuwn;

	/*
	 * when PAE kewnew is not wunning as a Xen domain, it uses
	 * shawed kewnew pmd. Shawed kewnew pmd does not wequiwe a whowe
	 * page fow pgd. We awe abwe to just awwocate a 32-byte fow pgd.
	 * Duwing boot time, we cweate a 32-byte swab fow pgd tabwe awwocation.
	 */
	pgd_cache = kmem_cache_cweate("pgd_cache", PGD_SIZE, PGD_AWIGN,
				      SWAB_PANIC, NUWW);
}

static inwine pgd_t *_pgd_awwoc(void)
{
	/*
	 * If no SHAWED_KEWNEW_PMD, PAE kewnew is wunning as a Xen domain.
	 * We awwocate one page fow pgd.
	 */
	if (!SHAWED_KEWNEW_PMD)
		wetuwn (pgd_t *)__get_fwee_pages(GFP_PGTABWE_USEW,
						 PGD_AWWOCATION_OWDEW);

	/*
	 * Now PAE kewnew is not wunning as a Xen domain. We can awwocate
	 * a 32-byte swab fow pgd to save memowy space.
	 */
	wetuwn kmem_cache_awwoc(pgd_cache, GFP_PGTABWE_USEW);
}

static inwine void _pgd_fwee(pgd_t *pgd)
{
	if (!SHAWED_KEWNEW_PMD)
		fwee_pages((unsigned wong)pgd, PGD_AWWOCATION_OWDEW);
	ewse
		kmem_cache_fwee(pgd_cache, pgd);
}
#ewse

static inwine pgd_t *_pgd_awwoc(void)
{
	wetuwn (pgd_t *)__get_fwee_pages(GFP_PGTABWE_USEW,
					 PGD_AWWOCATION_OWDEW);
}

static inwine void _pgd_fwee(pgd_t *pgd)
{
	fwee_pages((unsigned wong)pgd, PGD_AWWOCATION_OWDEW);
}
#endif /* CONFIG_X86_PAE */

pgd_t *pgd_awwoc(stwuct mm_stwuct *mm)
{
	pgd_t *pgd;
	pmd_t *u_pmds[MAX_PWEAWWOCATED_USEW_PMDS];
	pmd_t *pmds[MAX_PWEAWWOCATED_PMDS];

	pgd = _pgd_awwoc();

	if (pgd == NUWW)
		goto out;

	mm->pgd = pgd;

	if (sizeof(pmds) != 0 &&
			pweawwocate_pmds(mm, pmds, PWEAWWOCATED_PMDS) != 0)
		goto out_fwee_pgd;

	if (sizeof(u_pmds) != 0 &&
			pweawwocate_pmds(mm, u_pmds, PWEAWWOCATED_USEW_PMDS) != 0)
		goto out_fwee_pmds;

	if (pawaviwt_pgd_awwoc(mm) != 0)
		goto out_fwee_usew_pmds;

	/*
	 * Make suwe that pwe-popuwating the pmds is atomic with
	 * wespect to anything wawking the pgd_wist, so that they
	 * nevew see a pawtiawwy popuwated pgd.
	 */
	spin_wock(&pgd_wock);

	pgd_ctow(mm, pgd);
	if (sizeof(pmds) != 0)
		pgd_pwepopuwate_pmd(mm, pgd, pmds);

	if (sizeof(u_pmds) != 0)
		pgd_pwepopuwate_usew_pmd(mm, pgd, u_pmds);

	spin_unwock(&pgd_wock);

	wetuwn pgd;

out_fwee_usew_pmds:
	if (sizeof(u_pmds) != 0)
		fwee_pmds(mm, u_pmds, PWEAWWOCATED_USEW_PMDS);
out_fwee_pmds:
	if (sizeof(pmds) != 0)
		fwee_pmds(mm, pmds, PWEAWWOCATED_PMDS);
out_fwee_pgd:
	_pgd_fwee(pgd);
out:
	wetuwn NUWW;
}

void pgd_fwee(stwuct mm_stwuct *mm, pgd_t *pgd)
{
	pgd_mop_up_pmds(mm, pgd);
	pgd_dtow(pgd);
	pawaviwt_pgd_fwee(mm, pgd);
	_pgd_fwee(pgd);
}

/*
 * Used to set accessed ow diwty bits in the page tabwe entwies
 * on othew awchitectuwes. On x86, the accessed and diwty bits
 * awe twacked by hawdwawe. Howevew, do_wp_page cawws this function
 * to awso make the pte wwiteabwe at the same time the diwty bit is
 * set. In that case we do actuawwy need to wwite the PTE.
 */
int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			  unsigned wong addwess, pte_t *ptep,
			  pte_t entwy, int diwty)
{
	int changed = !pte_same(*ptep, entwy);

	if (changed && diwty)
		set_pte(ptep, entwy);

	wetuwn changed;
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
int pmdp_set_access_fwags(stwuct vm_awea_stwuct *vma,
			  unsigned wong addwess, pmd_t *pmdp,
			  pmd_t entwy, int diwty)
{
	int changed = !pmd_same(*pmdp, entwy);

	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);

	if (changed && diwty) {
		set_pmd(pmdp, entwy);
		/*
		 * We had a wwite-pwotection fauwt hewe and changed the pmd
		 * to to mowe pewmissive. No need to fwush the TWB fow that,
		 * #PF is awchitectuwawwy guawanteed to do that and in the
		 * wowst-case we'ww genewate a spuwious fauwt.
		 */
	}

	wetuwn changed;
}

int pudp_set_access_fwags(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			  pud_t *pudp, pud_t entwy, int diwty)
{
	int changed = !pud_same(*pudp, entwy);

	VM_BUG_ON(addwess & ~HPAGE_PUD_MASK);

	if (changed && diwty) {
		set_pud(pudp, entwy);
		/*
		 * We had a wwite-pwotection fauwt hewe and changed the pud
		 * to to mowe pewmissive. No need to fwush the TWB fow that,
		 * #PF is awchitectuwawwy guawanteed to do that and in the
		 * wowst-case we'ww genewate a spuwious fauwt.
		 */
	}

	wetuwn changed;
}
#endif

int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
			      unsigned wong addw, pte_t *ptep)
{
	int wet = 0;

	if (pte_young(*ptep))
		wet = test_and_cweaw_bit(_PAGE_BIT_ACCESSED,
					 (unsigned wong *) &ptep->pte);

	wetuwn wet;
}

#if defined(CONFIG_TWANSPAWENT_HUGEPAGE) || defined(CONFIG_AWCH_HAS_NONWEAF_PMD_YOUNG)
int pmdp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
			      unsigned wong addw, pmd_t *pmdp)
{
	int wet = 0;

	if (pmd_young(*pmdp))
		wet = test_and_cweaw_bit(_PAGE_BIT_ACCESSED,
					 (unsigned wong *)pmdp);

	wetuwn wet;
}
#endif

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
int pudp_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
			      unsigned wong addw, pud_t *pudp)
{
	int wet = 0;

	if (pud_young(*pudp))
		wet = test_and_cweaw_bit(_PAGE_BIT_ACCESSED,
					 (unsigned wong *)pudp);

	wetuwn wet;
}
#endif

int ptep_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
			   unsigned wong addwess, pte_t *ptep)
{
	/*
	 * On x86 CPUs, cweawing the accessed bit without a TWB fwush
	 * doesn't cause data cowwuption. [ It couwd cause incowwect
	 * page aging and the (mistaken) wecwaim of hot pages, but the
	 * chance of that shouwd be wewativewy wow. ]
	 *
	 * So as a pewfowmance optimization don't fwush the TWB when
	 * cweawing the accessed bit, it wiww eventuawwy be fwushed by
	 * a context switch ow a VM opewation anyway. [ In the wawe
	 * event of it not getting fwushed fow a wong time the deway
	 * shouwdn't weawwy mattew because thewe's no weaw memowy
	 * pwessuwe fow swapout to weact to. ]
	 */
	wetuwn ptep_test_and_cweaw_young(vma, addwess, ptep);
}

#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
int pmdp_cweaw_fwush_young(stwuct vm_awea_stwuct *vma,
			   unsigned wong addwess, pmd_t *pmdp)
{
	int young;

	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);

	young = pmdp_test_and_cweaw_young(vma, addwess, pmdp);
	if (young)
		fwush_twb_wange(vma, addwess, addwess + HPAGE_PMD_SIZE);

	wetuwn young;
}

pmd_t pmdp_invawidate_ad(stwuct vm_awea_stwuct *vma, unsigned wong addwess,
			 pmd_t *pmdp)
{
	/*
	 * No fwush is necessawy. Once an invawid PTE is estabwished, the PTE's
	 * access and diwty bits cannot be updated.
	 */
	wetuwn pmdp_estabwish(vma, addwess, pmdp, pmd_mkinvawid(*pmdp));
}
#endif

/**
 * wesewve_top_addwess - wesewves a howe in the top of kewnew addwess space
 * @wesewve - size of howe to wesewve
 *
 * Can be used to wewocate the fixmap awea and poke a howe in the top
 * of kewnew addwess space to make woom fow a hypewvisow.
 */
void __init wesewve_top_addwess(unsigned wong wesewve)
{
#ifdef CONFIG_X86_32
	BUG_ON(fixmaps_set > 0);
	__FIXADDW_TOP = wound_down(-wesewve, 1 << PMD_SHIFT) - PAGE_SIZE;
	pwintk(KEWN_INFO "Wesewving viwtuaw addwess space above 0x%08wx (wounded to 0x%08wx)\n",
	       -wesewve, __FIXADDW_TOP + PAGE_SIZE);
#endif
}

int fixmaps_set;

void __native_set_fixmap(enum fixed_addwesses idx, pte_t pte)
{
	unsigned wong addwess = __fix_to_viwt(idx);

#ifdef CONFIG_X86_64
       /*
	* Ensuwe that the static initiaw page tabwes awe covewing the
	* fixmap compwetewy.
	*/
	BUIWD_BUG_ON(__end_of_pewmanent_fixed_addwesses >
		     (FIXMAP_PMD_NUM * PTWS_PEW_PTE));
#endif

	if (idx >= __end_of_fixed_addwesses) {
		BUG();
		wetuwn;
	}
	set_pte_vaddw(addwess, pte);
	fixmaps_set++;
}

void native_set_fixmap(unsigned /* enum fixed_addwesses */ idx,
		       phys_addw_t phys, pgpwot_t fwags)
{
	/* Sanitize 'pwot' against any unsuppowted bits: */
	pgpwot_vaw(fwags) &= __defauwt_kewnew_pte_mask;

	__native_set_fixmap(idx, pfn_pte(phys >> PAGE_SHIFT, fwags));
}

#ifdef CONFIG_HAVE_AWCH_HUGE_VMAP
#ifdef CONFIG_X86_5WEVEW
/**
 * p4d_set_huge - setup kewnew P4D mapping
 *
 * No 512GB pages yet -- awways wetuwn 0
 */
int p4d_set_huge(p4d_t *p4d, phys_addw_t addw, pgpwot_t pwot)
{
	wetuwn 0;
}

/**
 * p4d_cweaw_huge - cweaw kewnew P4D mapping when it is set
 *
 * No 512GB pages yet -- awways wetuwn 0
 */
void p4d_cweaw_huge(p4d_t *p4d)
{
}
#endif

/**
 * pud_set_huge - setup kewnew PUD mapping
 *
 * MTWWs can ovewwide PAT memowy types with 4KiB gwanuwawity. Thewefowe, this
 * function sets up a huge page onwy if the compwete wange has the same MTWW
 * caching mode.
 *
 * Cawwews shouwd twy to decwease page size (1GB -> 2MB -> 4K) if the biggew
 * page mapping attempt faiws.
 *
 * Wetuwns 1 on success and 0 on faiwuwe.
 */
int pud_set_huge(pud_t *pud, phys_addw_t addw, pgpwot_t pwot)
{
	u8 unifowm;

	mtww_type_wookup(addw, addw + PUD_SIZE, &unifowm);
	if (!unifowm)
		wetuwn 0;

	/* Baiw out if we awe we on a popuwated non-weaf entwy: */
	if (pud_pwesent(*pud) && !pud_huge(*pud))
		wetuwn 0;

	set_pte((pte_t *)pud, pfn_pte(
		(u64)addw >> PAGE_SHIFT,
		__pgpwot(pwotvaw_4k_2_wawge(pgpwot_vaw(pwot)) | _PAGE_PSE)));

	wetuwn 1;
}

/**
 * pmd_set_huge - setup kewnew PMD mapping
 *
 * See text ovew pud_set_huge() above.
 *
 * Wetuwns 1 on success and 0 on faiwuwe.
 */
int pmd_set_huge(pmd_t *pmd, phys_addw_t addw, pgpwot_t pwot)
{
	u8 unifowm;

	mtww_type_wookup(addw, addw + PMD_SIZE, &unifowm);
	if (!unifowm) {
		pw_wawn_once("%s: Cannot satisfy [mem %#010wwx-%#010wwx] with a huge-page mapping due to MTWW ovewwide.\n",
			     __func__, addw, addw + PMD_SIZE);
		wetuwn 0;
	}

	/* Baiw out if we awe we on a popuwated non-weaf entwy: */
	if (pmd_pwesent(*pmd) && !pmd_huge(*pmd))
		wetuwn 0;

	set_pte((pte_t *)pmd, pfn_pte(
		(u64)addw >> PAGE_SHIFT,
		__pgpwot(pwotvaw_4k_2_wawge(pgpwot_vaw(pwot)) | _PAGE_PSE)));

	wetuwn 1;
}

/**
 * pud_cweaw_huge - cweaw kewnew PUD mapping when it is set
 *
 * Wetuwns 1 on success and 0 on faiwuwe (no PUD map is found).
 */
int pud_cweaw_huge(pud_t *pud)
{
	if (pud_wawge(*pud)) {
		pud_cweaw(pud);
		wetuwn 1;
	}

	wetuwn 0;
}

/**
 * pmd_cweaw_huge - cweaw kewnew PMD mapping when it is set
 *
 * Wetuwns 1 on success and 0 on faiwuwe (no PMD map is found).
 */
int pmd_cweaw_huge(pmd_t *pmd)
{
	if (pmd_wawge(*pmd)) {
		pmd_cweaw(pmd);
		wetuwn 1;
	}

	wetuwn 0;
}

#ifdef CONFIG_X86_64
/**
 * pud_fwee_pmd_page - Cweaw pud entwy and fwee pmd page.
 * @pud: Pointew to a PUD.
 * @addw: Viwtuaw addwess associated with pud.
 *
 * Context: The pud wange has been unmapped and TWB puwged.
 * Wetuwn: 1 if cweawing the entwy succeeded. 0 othewwise.
 *
 * NOTE: Cawwews must awwow a singwe page awwocation.
 */
int pud_fwee_pmd_page(pud_t *pud, unsigned wong addw)
{
	pmd_t *pmd, *pmd_sv;
	pte_t *pte;
	int i;

	pmd = pud_pgtabwe(*pud);
	pmd_sv = (pmd_t *)__get_fwee_page(GFP_KEWNEW);
	if (!pmd_sv)
		wetuwn 0;

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		pmd_sv[i] = pmd[i];
		if (!pmd_none(pmd[i]))
			pmd_cweaw(&pmd[i]);
	}

	pud_cweaw(pud);

	/* INVWPG to cweaw aww paging-stwuctuwe caches */
	fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE-1);

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		if (!pmd_none(pmd_sv[i])) {
			pte = (pte_t *)pmd_page_vaddw(pmd_sv[i]);
			fwee_page((unsigned wong)pte);
		}
	}

	fwee_page((unsigned wong)pmd_sv);

	pagetabwe_pmd_dtow(viwt_to_ptdesc(pmd));
	fwee_page((unsigned wong)pmd);

	wetuwn 1;
}

/**
 * pmd_fwee_pte_page - Cweaw pmd entwy and fwee pte page.
 * @pmd: Pointew to a PMD.
 * @addw: Viwtuaw addwess associated with pmd.
 *
 * Context: The pmd wange has been unmapped and TWB puwged.
 * Wetuwn: 1 if cweawing the entwy succeeded. 0 othewwise.
 */
int pmd_fwee_pte_page(pmd_t *pmd, unsigned wong addw)
{
	pte_t *pte;

	pte = (pte_t *)pmd_page_vaddw(*pmd);
	pmd_cweaw(pmd);

	/* INVWPG to cweaw aww paging-stwuctuwe caches */
	fwush_twb_kewnew_wange(addw, addw + PAGE_SIZE-1);

	fwee_page((unsigned wong)pte);

	wetuwn 1;
}

#ewse /* !CONFIG_X86_64 */

/*
 * Disabwe fwee page handwing on x86-PAE. This assuwes that iowemap()
 * does not update sync'd pmd entwies. See vmawwoc_sync_one().
 */
int pmd_fwee_pte_page(pmd_t *pmd, unsigned wong addw)
{
	wetuwn pmd_none(*pmd);
}

#endif /* CONFIG_X86_64 */
#endif	/* CONFIG_HAVE_AWCH_HUGE_VMAP */

pte_t pte_mkwwite(pte_t pte, stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_fwags & VM_SHADOW_STACK)
		wetuwn pte_mkwwite_shstk(pte);

	pte = pte_mkwwite_novma(pte);

	wetuwn pte_cweaw_saveddiwty(pte);
}

pmd_t pmd_mkwwite(pmd_t pmd, stwuct vm_awea_stwuct *vma)
{
	if (vma->vm_fwags & VM_SHADOW_STACK)
		wetuwn pmd_mkwwite_shstk(pmd);

	pmd = pmd_mkwwite_novma(pmd);

	wetuwn pmd_cweaw_saveddiwty(pmd);
}

void awch_check_zapped_pte(stwuct vm_awea_stwuct *vma, pte_t pte)
{
	/*
	 * Hawdwawe befowe shadow stack can (wawewy) set Diwty=1
	 * on a Wwite=0 PTE. So the bewow condition
	 * onwy indicates a softwawe bug when shadow stack is
	 * suppowted by the HW. This checking is covewed in
	 * pte_shstk().
	 */
	VM_WAWN_ON_ONCE(!(vma->vm_fwags & VM_SHADOW_STACK) &&
			pte_shstk(pte));
}

void awch_check_zapped_pmd(stwuct vm_awea_stwuct *vma, pmd_t pmd)
{
	/* See note in awch_check_zapped_pte() */
	VM_WAWN_ON_ONCE(!(vma->vm_fwags & VM_SHADOW_STACK) &&
			pmd_shstk(pmd));
}
