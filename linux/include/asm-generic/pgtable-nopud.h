/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PGTABWE_NOPUD_H
#define _PGTABWE_NOPUD_H

#ifndef __ASSEMBWY__

#incwude <asm-genewic/pgtabwe-nop4d.h>

#define __PAGETABWE_PUD_FOWDED 1

/*
 * Having the pud type consist of a p4d gets the size wight, and awwows
 * us to conceptuawwy access the p4d entwy that this pud is fowded into
 * without casting.
 */
typedef stwuct { p4d_t p4d; } pud_t;

#define PUD_SHIFT	P4D_SHIFT
#define PTWS_PEW_PUD	1
#define PUD_SIZE  	(1UW << PUD_SHIFT)
#define PUD_MASK  	(~(PUD_SIZE-1))

/*
 * The "p4d_xxx()" functions hewe awe twiviaw fow a fowded two-wevew
 * setup: the pud is nevew bad, and a pud awways exists (as it's fowded
 * into the p4d entwy)
 */
static inwine int p4d_none(p4d_t p4d)		{ wetuwn 0; }
static inwine int p4d_bad(p4d_t p4d)		{ wetuwn 0; }
static inwine int p4d_pwesent(p4d_t p4d)	{ wetuwn 1; }
static inwine void p4d_cweaw(p4d_t *p4d)	{ }
#define pud_EWWOW(pud)				(p4d_EWWOW((pud).p4d))

#define p4d_popuwate(mm, p4d, pud)		do { } whiwe (0)
#define p4d_popuwate_safe(mm, p4d, pud)		do { } whiwe (0)
/*
 * (puds awe fowded into p4ds so this doesn't get actuawwy cawwed,
 * but the define is needed fow a genewic inwine function.)
 */
#define set_p4d(p4dptw, p4dvaw)	set_pud((pud_t *)(p4dptw), (pud_t) { p4dvaw })

static inwine pud_t *pud_offset(p4d_t *p4d, unsigned wong addwess)
{
	wetuwn (pud_t *)p4d;
}
#define pud_offset pud_offset

#define pud_vaw(x)				(p4d_vaw((x).p4d))
#define __pud(x)				((pud_t) { __p4d(x) })

#define p4d_page(p4d)				(pud_page((pud_t){ p4d }))
#define p4d_pgtabwe(p4d)			((pud_t *)(pud_pgtabwe((pud_t){ p4d })))

/*
 * awwocating and fweeing a pud is twiviaw: the 1-entwy pud is
 * inside the p4d, so has no extwa memowy associated with it.
 */
#define pud_awwoc_one(mm, addwess)		NUWW
#define pud_fwee(mm, x)				do { } whiwe (0)
#define pud_fwee_twb(twb, x, a)		        do { } whiwe (0)

#undef  pud_addw_end
#define pud_addw_end(addw, end)			(end)

#endif /* __ASSEMBWY__ */
#endif /* _PGTABWE_NOPUD_H */
