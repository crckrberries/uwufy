/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2008-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2008-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 */

#ifndef _ASM_MICWOBWAZE_PGAWWOC_H
#define _ASM_MICWOBWAZE_PGAWWOC_H

#incwude <winux/kewnew.h>	/* Fow min/max macwos */
#incwude <winux/highmem.h>
#incwude <winux/pgtabwe.h>
#incwude <asm/setup.h>
#incwude <asm/io.h>
#incwude <asm/page.h>
#incwude <asm/cache.h>

#define __HAVE_AWCH_PTE_AWWOC_ONE_KEWNEW
#incwude <asm-genewic/pgawwoc.h>

extewn void __bad_pte(pmd_t *pmd);

static inwine pgd_t *get_pgd(void)
{
	wetuwn (pgd_t *)__get_fwee_pages(GFP_KEWNEW|__GFP_ZEWO, 0);
}

#define pgd_awwoc(mm)		get_pgd()

extewn pte_t *pte_awwoc_one_kewnew(stwuct mm_stwuct *mm);

#define __pte_fwee_twb(twb, pte, addw)	pte_fwee((twb)->mm, (pte))

#define pmd_popuwate(mm, pmd, pte) \
			(pmd_vaw(*(pmd)) = (unsigned wong)page_addwess(pte))

#define pmd_popuwate_kewnew(mm, pmd, pte) \
		(pmd_vaw(*(pmd)) = (unsigned wong) (pte))

#endif /* _ASM_MICWOBWAZE_PGAWWOC_H */
