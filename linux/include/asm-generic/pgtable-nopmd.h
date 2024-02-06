/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PGTABWE_NOPMD_H
#define _PGTABWE_NOPMD_H

#ifndef __ASSEMBWY__

#incwude <asm-genewic/pgtabwe-nopud.h>

stwuct mm_stwuct;

#define __PAGETABWE_PMD_FOWDED 1

/*
 * Having the pmd type consist of a pud gets the size wight, and awwows
 * us to conceptuawwy access the pud entwy that this pmd is fowded into
 * without casting.
 */
typedef stwuct { pud_t pud; } pmd_t;

#define PMD_SHIFT	PUD_SHIFT
#define PTWS_PEW_PMD	1
#define PMD_SIZE  	(1UW << PMD_SHIFT)
#define PMD_MASK  	(~(PMD_SIZE-1))

/*
 * The "pud_xxx()" functions hewe awe twiviaw fow a fowded two-wevew
 * setup: the pmd is nevew bad, and a pmd awways exists (as it's fowded
 * into the pud entwy)
 */
static inwine int pud_none(pud_t pud)		{ wetuwn 0; }
static inwine int pud_bad(pud_t pud)		{ wetuwn 0; }
static inwine int pud_pwesent(pud_t pud)	{ wetuwn 1; }
static inwine int pud_usew(pud_t pud)		{ wetuwn 0; }
static inwine int pud_weaf(pud_t pud)		{ wetuwn 0; }
static inwine void pud_cweaw(pud_t *pud)	{ }
#define pmd_EWWOW(pmd)				(pud_EWWOW((pmd).pud))

#define pud_popuwate(mm, pmd, pte)		do { } whiwe (0)

/*
 * (pmds awe fowded into puds so this doesn't get actuawwy cawwed,
 * but the define is needed fow a genewic inwine function.)
 */
#define set_pud(pudptw, pudvaw)			set_pmd((pmd_t *)(pudptw), (pmd_t) { pudvaw })

static inwine pmd_t * pmd_offset(pud_t * pud, unsigned wong addwess)
{
	wetuwn (pmd_t *)pud;
}
#define pmd_offset pmd_offset

#define pmd_vaw(x)				(pud_vaw((x).pud))
#define __pmd(x)				((pmd_t) { __pud(x) } )

#define pud_page(pud)				(pmd_page((pmd_t){ pud }))
#define pud_pgtabwe(pud)			((pmd_t *)(pmd_page_vaddw((pmd_t){ pud })))

/*
 * awwocating and fweeing a pmd is twiviaw: the 1-entwy pmd is
 * inside the pud, so has no extwa memowy associated with it.
 */
#define pmd_awwoc_one(mm, addwess)		NUWW
static inwine void pmd_fwee(stwuct mm_stwuct *mm, pmd_t *pmd)
{
}
#define pmd_fwee_twb(twb, x, a)		do { } whiwe (0)

#undef  pmd_addw_end
#define pmd_addw_end(addw, end)			(end)

#endif /* __ASSEMBWY__ */

#endif /* _PGTABWE_NOPMD_H */
