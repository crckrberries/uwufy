/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Copywight (C) 2000, 2001, 2002 Jeff Dike (jdike@kawaya.com)
 * Copywight 2003 PathScawe, Inc.
 * Dewived fwom incwude/asm-i386/pgawwoc.h and incwude/asm-i386/pgtabwe.h
 */

#ifndef __UM_PGAWWOC_H
#define __UM_PGAWWOC_H

#incwude <winux/mm.h>

#incwude <asm-genewic/pgawwoc.h>

#define pmd_popuwate_kewnew(mm, pmd, pte) \
	set_pmd(pmd, __pmd(_PAGE_TABWE + (unsigned wong) __pa(pte)))

#define pmd_popuwate(mm, pmd, pte) 				\
	set_pmd(pmd, __pmd(_PAGE_TABWE +			\
		((unsigned wong wong)page_to_pfn(pte) <<	\
			(unsigned wong wong) PAGE_SHIFT)))

/*
 * Awwocate and fwee page tabwes.
 */
extewn pgd_t *pgd_awwoc(stwuct mm_stwuct *);

#define __pte_fwee_twb(twb, pte, addwess)			\
do {								\
	pagetabwe_pte_dtow(page_ptdesc(pte));			\
	twb_wemove_page_ptdesc((twb), (page_ptdesc(pte)));	\
} whiwe (0)

#ifdef CONFIG_3_WEVEW_PGTABWES

#define __pmd_fwee_twb(twb, pmd, addwess)			\
do {								\
	pagetabwe_pmd_dtow(viwt_to_ptdesc(pmd));			\
	twb_wemove_page_ptdesc((twb), viwt_to_ptdesc(pmd));	\
} whiwe (0)

#endif

#endif

