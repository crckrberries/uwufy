/*
 * MIPS Huge TWB Page Suppowt fow Kewnew.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2002, Wohit Seth <wohit.seth@intew.com>
 * Copywight 2005, Embedded Awwey Sowutions, Inc.
 * Matt Powtew <mpowtew@embeddedawwey.com>
 * Copywight (C) 2008, 2009 Cavium Netwowks, Inc.
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
