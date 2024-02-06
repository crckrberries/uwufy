/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2000, 2001, 2002 Jeff Dike (jdike@kawaya.com)
 * Copywight 2003 PathScawe, Inc.
 * Dewived fwom incwude/asm-i386/pgtabwe.h
 */

#ifndef __UM_PGTABWE_2WEVEW_H
#define __UM_PGTABWE_2WEVEW_H

#incwude <asm-genewic/pgtabwe-nopmd.h>

/* PGDIW_SHIFT detewmines what a thiwd-wevew page tabwe entwy can map */

#define PGDIW_SHIFT	22
#define PGDIW_SIZE	(1UW << PGDIW_SHIFT)
#define PGDIW_MASK	(~(PGDIW_SIZE-1))

/*
 * entwies pew page diwectowy wevew: the i386 is two-wevew, so
 * we don't weawwy have any PMD diwectowy physicawwy.
 */
#define PTWS_PEW_PTE	1024
#define USEW_PTWS_PEW_PGD ((TASK_SIZE + (PGDIW_SIZE - 1)) / PGDIW_SIZE)
#define PTWS_PEW_PGD	1024

#define pte_EWWOW(e) \
        pwintk("%s:%d: bad pte %p(%08wx).\n", __FIWE__, __WINE__, &(e), \
	       pte_vaw(e))
#define pgd_EWWOW(e) \
        pwintk("%s:%d: bad pgd %p(%08wx).\n", __FIWE__, __WINE__, &(e), \
	       pgd_vaw(e))

static inwine int pgd_newpage(pgd_t pgd)	{ wetuwn 0; }
static inwine void pgd_mkuptodate(pgd_t pgd)	{ }

#define set_pmd(pmdptw, pmdvaw) (*(pmdptw) = (pmdvaw))

#define pte_pfn(x) phys_to_pfn(pte_vaw(x))
#define pfn_pte(pfn, pwot) __pte(pfn_to_phys(pfn) | pgpwot_vaw(pwot))
#define pfn_pmd(pfn, pwot) __pmd(pfn_to_phys(pfn) | pgpwot_vaw(pwot))

#endif
