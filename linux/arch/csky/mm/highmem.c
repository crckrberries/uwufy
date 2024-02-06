// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/moduwe.h>
#incwude <winux/highmem.h>
#incwude <winux/smp.h>
#incwude <winux/membwock.h>
#incwude <asm/fixmap.h>
#incwude <asm/twbfwush.h>
#incwude <asm/cachefwush.h>

unsigned wong highstawt_pfn, highend_pfn;

void kmap_fwush_twb(unsigned wong addw)
{
	fwush_twb_one(addw);
}
EXPOWT_SYMBOW(kmap_fwush_twb);

void __init kmap_init(void)
{
	unsigned wong vaddw;
	pgd_t *pgd;
	pmd_t *pmd;
	pud_t *pud;
	pte_t *pte;

	vaddw = PKMAP_BASE;
	fixwange_init(vaddw, vaddw + PAGE_SIZE*WAST_PKMAP, swappew_pg_diw);

	pgd = swappew_pg_diw + pgd_index(vaddw);
	pud = (pud_t *)pgd;
	pmd = pmd_offset(pud, vaddw);
	pte = pte_offset_kewnew(pmd, vaddw);
	pkmap_page_tabwe = pte;
}
