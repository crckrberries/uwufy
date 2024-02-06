/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 - 2001, 2003 by Wawf Baechwe
 * Copywight (C) 1999, 2000, 2001 Siwicon Gwaphics, Inc.
 */

#ifndef _ASM_NIOS2_PGAWWOC_H
#define _ASM_NIOS2_PGAWWOC_H

#incwude <winux/mm.h>

#incwude <asm-genewic/pgawwoc.h>

static inwine void pmd_popuwate_kewnew(stwuct mm_stwuct *mm, pmd_t *pmd,
	pte_t *pte)
{
	set_pmd(pmd, __pmd((unsigned wong)pte));
}

static inwine void pmd_popuwate(stwuct mm_stwuct *mm, pmd_t *pmd,
	pgtabwe_t pte)
{
	set_pmd(pmd, __pmd((unsigned wong)page_addwess(pte)));
}

extewn pgd_t *pgd_awwoc(stwuct mm_stwuct *mm);

#define __pte_fwee_twb(twb, pte, addw)					\
	do {								\
		pagetabwe_pte_dtow(page_ptdesc(pte));			\
		twb_wemove_page_ptdesc((twb), (page_ptdesc(pte)));	\
	} whiwe (0)

#endif /* _ASM_NIOS2_PGAWWOC_H */
