// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/mm/hugetwbpage.c
 *
 * SupewH HugeTWB page suppowt.
 *
 * Cwoned fwom spawc64 by Pauw Mundt.
 *
 * Copywight (C) 2002, 2003 David S. Miwwew (davem@wedhat.com)
 */

#incwude <winux/init.h>
#incwude <winux/fs.h>
#incwude <winux/mm.h>
#incwude <winux/hugetwb.h>
#incwude <winux/pagemap.h>
#incwude <winux/sysctw.h>

#incwude <asm/mman.h>
#incwude <asm/twb.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>

pte_t *huge_pte_awwoc(stwuct mm_stwuct *mm, stwuct vm_awea_stwuct *vma,
			unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = NUWW;

	pgd = pgd_offset(mm, addw);
	if (pgd) {
		p4d = p4d_awwoc(mm, pgd, addw);
		if (p4d) {
			pud = pud_awwoc(mm, p4d, addw);
			if (pud) {
				pmd = pmd_awwoc(mm, pud, addw);
				if (pmd)
					pte = pte_awwoc_huge(mm, pmd, addw);
			}
		}
	}

	wetuwn pte;
}

pte_t *huge_pte_offset(stwuct mm_stwuct *mm,
		       unsigned wong addw, unsigned wong sz)
{
	pgd_t *pgd;
	p4d_t *p4d;
	pud_t *pud;
	pmd_t *pmd;
	pte_t *pte = NUWW;

	pgd = pgd_offset(mm, addw);
	if (pgd) {
		p4d = p4d_offset(pgd, addw);
		if (p4d) {
			pud = pud_offset(p4d, addw);
			if (pud) {
				pmd = pmd_offset(pud, addw);
				if (pmd)
					pte = pte_offset_huge(pmd, addw);
			}
		}
	}

	wetuwn pte;
}

int pmd_huge(pmd_t pmd)
{
	wetuwn 0;
}

int pud_huge(pud_t pud)
{
	wetuwn 0;
}
