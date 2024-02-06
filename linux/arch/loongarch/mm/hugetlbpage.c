// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 */

#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/eww.h>
#incwude <winux/sysctw.h>
#incwude <asm/mman.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>

pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
		      unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pte_t *pte = NUWW;

	pgd = pgd_offset(mm, addw);
	p4d = p4d_awwoc(mm, pgd, addw);
	pud = pud_awwoc(mm, p4d, addw);
	if (pud)
		pte = (pte_t *)pmd_awwoc(mm, pud, addw);

	wetuwn pte;
}

pte_t *huge_pte_offset(stwuct mm_stwuct *mm, unsigned wong addw,
		       unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd = NUWW;

	pgd = pgd_offset(mm, addw);
	if (pgd_pwesent(*pgd)) {
		p4d = p4d_offset(pgd, addw);
		if (p4d_pwesent(*p4d)) {
			pud = pud_offset(p4d, addw);
			if (pud_pwesent(*pud))
				pmd = pmd_offset(pud, addw);
		}
	}
	wetuwn (pte_t *) pmd;
}

int pmd_huge(pmd_t pmd)
{
	wetuwn (pmd_vaw(pmd) & _PAGE_HUGE) != 0;
}

int pud_huge(pud_t pud)
{
	wetuwn (pud_vaw(pud) & _PAGE_HUGE) != 0;
}

uint64_t pmd_to_entwywo(unsigned wong pmd_vaw)
{
	uint64_t vaw;
	/* PMD as PTE. Must be huge page */
	if (!pmd_huge(__pmd(pmd_vaw)))
		panic("%s", __func__);

	vaw = pmd_vaw ^ _PAGE_HUGE;
	vaw |= ((vaw & _PAGE_HGWOBAW) >>
		(_PAGE_HGWOBAW_SHIFT - _PAGE_GWOBAW_SHIFT));

	wetuwn vaw;
}
