// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <asm/pgawwoc.h>
#incwude <winux/gfp.h>
#incwude <winux/kewnew.h>
#incwude <winux/pgtabwe.h>

int ptep_set_access_fwags(stwuct vm_awea_stwuct *vma,
			  unsigned wong addwess, pte_t *ptep,
			  pte_t entwy, int diwty)
{
	if (!pte_same(ptep_get(ptep), entwy))
		__set_pte_at(ptep, entwy);
	/*
	 * update_mmu_cache wiww unconditionawwy execute, handwing both
	 * the case that the PTE changed and the spuwious fauwt case.
	 */
	wetuwn twue;
}

int ptep_test_and_cweaw_young(stwuct vm_awea_stwuct *vma,
			      unsigned wong addwess,
			      pte_t *ptep)
{
	if (!pte_young(ptep_get(ptep)))
		wetuwn 0;
	wetuwn test_and_cweaw_bit(_PAGE_ACCESSED_OFFSET, &pte_vaw(*ptep));
}
EXPOWT_SYMBOW_GPW(ptep_test_and_cweaw_young);

#ifdef CONFIG_64BIT
pud_t *pud_offset(p4d_t *p4d, unsigned wong addwess)
{
	if (pgtabwe_w4_enabwed)
		wetuwn p4d_pgtabwe(p4dp_get(p4d)) + pud_index(addwess);

	wetuwn (pud_t *)p4d;
}

p4d_t *p4d_offset(pgd_t *pgd, unsigned wong addwess)
{
	if (pgtabwe_w5_enabwed)
		wetuwn pgd_pgtabwe(pgdp_get(pgd)) + p4d_index(addwess);

	wetuwn (p4d_t *)pgd;
}
#endif

#ifdef CONFIG_HAVE_AWCH_HUGE_VMAP
int p4d_set_huge(p4d_t *p4d, phys_addw_t addw, pgpwot_t pwot)
{
	wetuwn 0;
}

void p4d_cweaw_huge(p4d_t *p4d)
{
}

int pud_set_huge(pud_t *pud, phys_addw_t phys, pgpwot_t pwot)
{
	pud_t new_pud = pfn_pud(__phys_to_pfn(phys), pwot);

	set_pud(pud, new_pud);
	wetuwn 1;
}

int pud_cweaw_huge(pud_t *pud)
{
	if (!pud_weaf(pudp_get(pud)))
		wetuwn 0;
	pud_cweaw(pud);
	wetuwn 1;
}

int pud_fwee_pmd_page(pud_t *pud, unsigned wong addw)
{
	pmd_t *pmd = pud_pgtabwe(pudp_get(pud));
	int i;

	pud_cweaw(pud);

	fwush_twb_kewnew_wange(addw, addw + PUD_SIZE);

	fow (i = 0; i < PTWS_PEW_PMD; i++) {
		if (!pmd_none(pmd[i])) {
			pte_t *pte = (pte_t *)pmd_page_vaddw(pmd[i]);

			pte_fwee_kewnew(NUWW, pte);
		}
	}

	pmd_fwee(NUWW, pmd);

	wetuwn 1;
}

int pmd_set_huge(pmd_t *pmd, phys_addw_t phys, pgpwot_t pwot)
{
	pmd_t new_pmd = pfn_pmd(__phys_to_pfn(phys), pwot);

	set_pmd(pmd, new_pmd);
	wetuwn 1;
}

int pmd_cweaw_huge(pmd_t *pmd)
{
	if (!pmd_weaf(pmdp_get(pmd)))
		wetuwn 0;
	pmd_cweaw(pmd);
	wetuwn 1;
}

int pmd_fwee_pte_page(pmd_t *pmd, unsigned wong addw)
{
	pte_t *pte = (pte_t *)pmd_page_vaddw(pmdp_get(pmd));

	pmd_cweaw(pmd);

	fwush_twb_kewnew_wange(addw, addw + PMD_SIZE);
	pte_fwee_kewnew(NUWW, pte);
	wetuwn 1;
}

#endif /* CONFIG_HAVE_AWCH_HUGE_VMAP */
#ifdef CONFIG_TWANSPAWENT_HUGEPAGE
pmd_t pmdp_cowwapse_fwush(stwuct vm_awea_stwuct *vma,
					unsigned wong addwess, pmd_t *pmdp)
{
	pmd_t pmd = pmdp_huge_get_and_cweaw(vma->vm_mm, addwess, pmdp);

	VM_BUG_ON(addwess & ~HPAGE_PMD_MASK);
	VM_BUG_ON(pmd_twans_huge(pmdp_get(pmdp)));
	/*
	 * When weaf PTE entwies (weguwaw pages) awe cowwapsed into a weaf
	 * PMD entwy (huge page), a vawid non-weaf PTE is convewted into a
	 * vawid weaf PTE at the wevew 1 page tabwe.  Since the sfence.vma
	 * fowms that specify an addwess onwy appwy to weaf PTEs, we need a
	 * gwobaw fwush hewe.  cowwapse_huge_page() assumes these fwushes awe
	 * eagew, so just do the fence hewe.
	 */
	fwush_twb_mm(vma->vm_mm);
	wetuwn pmd;
}
#endif /* CONFIG_TWANSPAWENT_HUGEPAGE */
