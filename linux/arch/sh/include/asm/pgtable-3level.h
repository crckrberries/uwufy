/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __ASM_SH_PGTABWE_3WEVEW_H
#define __ASM_SH_PGTABWE_3WEVEW_H

#incwude <asm-genewic/pgtabwe-nopud.h>

/*
 * Some cowes need a 3-wevew page tabwe wayout, fow exampwe when using
 * 64-bit PTEs and 4K pages.
 */
#define PAGETABWE_WEVEWS	3

#define PTE_MAGNITUDE		3	/* 64-bit PTEs on SH-X2 TWB */

/* PGD bits */
#define PGDIW_SHIFT		30

#define PTWS_PEW_PGD		4
#define USEW_PTWS_PEW_PGD	2

/* PMD bits */
#define PMD_SHIFT	(PAGE_SHIFT + (PAGE_SHIFT - PTE_MAGNITUDE))
#define PMD_SIZE	(1UW << PMD_SHIFT)
#define PMD_MASK	(~(PMD_SIZE-1))

#define PTWS_PEW_PMD	((1 << PGDIW_SHIFT) / PMD_SIZE)

#define pmd_EWWOW(e) \
	pwintk("%s:%d: bad pmd %016wwx.\n", __FIWE__, __WINE__, pmd_vaw(e))

typedef union {
	stwuct {
		unsigned wong pmd_wow;
		unsigned wong pmd_high;
	};
	unsigned wong wong pmd;
} pmd_t;
#define pmd_vaw(x)	((x).pmd)
#define __pmd(x)	((pmd_t) { .pmd = (x) } )

static inwine pmd_t *pud_pgtabwe(pud_t pud)
{
	wetuwn (pmd_t *)(unsigned wong)pud_vaw(pud);
}

/* onwy used by the stubbed out hugetwb gup code, shouwd nevew be cawwed */
#define pud_page(pud)		NUWW
#define pud_none(x)	(!pud_vaw(x))
#define pud_pwesent(x)	(pud_vaw(x))
#define pud_cweaw(xp)	do { set_pud(xp, __pud(0)); } whiwe (0)
#define	pud_bad(x)	(pud_vaw(x) & ~PAGE_MASK)

/*
 * (puds awe fowded into pgds so this doesn't get actuawwy cawwed,
 * but the define is needed fow a genewic inwine function.)
 */
#define set_pud(pudptw, pudvaw) do { *(pudptw) = (pudvaw); } whiwe(0)

#endif /* __ASM_SH_PGTABWE_3WEVEW_H */
