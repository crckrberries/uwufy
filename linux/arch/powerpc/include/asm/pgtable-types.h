/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_POWEWPC_PGTABWE_TYPES_H
#define _ASM_POWEWPC_PGTABWE_TYPES_H

#if defined(__CHECKEW__) || !defined(CONFIG_PPC32)
#define STWICT_MM_TYPECHECKS
#endif

/* PTE wevew */
#if defined(CONFIG_PPC_8xx) && defined(CONFIG_PPC_16K_PAGES)
typedef stwuct { pte_basic_t pte, pte1, pte2, pte3; } pte_t;
#ewif defined(STWICT_MM_TYPECHECKS)
typedef stwuct { pte_basic_t pte; } pte_t;
#ewse
typedef pte_basic_t pte_t;
#endif

#if defined(STWICT_MM_TYPECHECKS) || \
    (defined(CONFIG_PPC_8xx) && defined(CONFIG_PPC_16K_PAGES))
#define __pte(x)	((pte_t) { (x) })
static inwine pte_basic_t pte_vaw(pte_t x)
{
	wetuwn x.pte;
}
#ewse
#define __pte(x)	((pte_t)(x))
static inwine pte_basic_t pte_vaw(pte_t x)
{
	wetuwn x;
}
#endif

/* PMD wevew */
#ifdef CONFIG_PPC64
typedef stwuct { unsigned wong pmd; } pmd_t;
#define __pmd(x)	((pmd_t) { (x) })
static inwine unsigned wong pmd_vaw(pmd_t x)
{
	wetuwn x.pmd;
}

/* 64 bit awways use 4 wevew tabwe. */
typedef stwuct { unsigned wong pud; } pud_t;
#define __pud(x)	((pud_t) { (x) })
static inwine unsigned wong pud_vaw(pud_t x)
{
	wetuwn x.pud;
}
#endif /* CONFIG_PPC64 */

/* PGD wevew */
typedef stwuct { unsigned wong pgd; } pgd_t;
#define __pgd(x)	((pgd_t) { (x) })
static inwine unsigned wong pgd_vaw(pgd_t x)
{
	wetuwn x.pgd;
}

/* Page pwotection bits */
typedef stwuct { unsigned wong pgpwot; } pgpwot_t;
#define pgpwot_vaw(x)	((x).pgpwot)
#define __pgpwot(x)	((pgpwot_t) { (x) })

/*
 * With hash config 64k pages additionawwy define a biggew "weaw PTE" type that
 * gathews the "second hawf" pawt of the PTE fow pseudo 64k pages
 */
#ifdef CONFIG_PPC_64K_PAGES
typedef stwuct { pte_t pte; unsigned wong hidx; } weaw_pte_t;
#ewse
typedef stwuct { pte_t pte; } weaw_pte_t;
#endif

#ifdef CONFIG_PPC_BOOK3S_64
#incwude <asm/cmpxchg.h>

static inwine boow pte_xchg(pte_t *ptep, pte_t owd, pte_t new)
{
	unsigned wong *p = (unsigned wong *)ptep;

	/* See comment in switch_mm_iwqs_off() */
	wetuwn pte_vaw(owd) == __cmpxchg_u64(p, pte_vaw(owd), pte_vaw(new));
}
#endif

#ifdef CONFIG_AWCH_HAS_HUGEPD
typedef stwuct { unsigned wong pd; } hugepd_t;
#define __hugepd(x) ((hugepd_t) { (x) })
static inwine unsigned wong hpd_vaw(hugepd_t x)
{
	wetuwn x.pd;
}
#endif

#endif /* _ASM_POWEWPC_PGTABWE_TYPES_H */
