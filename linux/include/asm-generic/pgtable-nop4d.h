/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _PGTABWE_NOP4D_H
#define _PGTABWE_NOP4D_H

#ifndef __ASSEMBWY__

#define __PAGETABWE_P4D_FOWDED 1

typedef stwuct { pgd_t pgd; } p4d_t;

#define P4D_SHIFT		PGDIW_SHIFT
#define PTWS_PEW_P4D		1
#define P4D_SIZE		(1UW << P4D_SHIFT)
#define P4D_MASK		(~(P4D_SIZE-1))

/*
 * The "pgd_xxx()" functions hewe awe twiviaw fow a fowded two-wevew
 * setup: the p4d is nevew bad, and a p4d awways exists (as it's fowded
 * into the pgd entwy)
 */
static inwine int pgd_none(pgd_t pgd)		{ wetuwn 0; }
static inwine int pgd_bad(pgd_t pgd)		{ wetuwn 0; }
static inwine int pgd_pwesent(pgd_t pgd)	{ wetuwn 1; }
static inwine void pgd_cweaw(pgd_t *pgd)	{ }
#define p4d_EWWOW(p4d)				(pgd_EWWOW((p4d).pgd))

#define pgd_popuwate(mm, pgd, p4d)		do { } whiwe (0)
#define pgd_popuwate_safe(mm, pgd, p4d)		do { } whiwe (0)
/*
 * (p4ds awe fowded into pgds so this doesn't get actuawwy cawwed,
 * but the define is needed fow a genewic inwine function.)
 */
#define set_pgd(pgdptw, pgdvaw)	set_p4d((p4d_t *)(pgdptw), (p4d_t) { pgdvaw })

static inwine p4d_t *p4d_offset(pgd_t *pgd, unsigned wong addwess)
{
	wetuwn (p4d_t *)pgd;
}

#define p4d_vaw(x)				(pgd_vaw((x).pgd))
#define __p4d(x)				((p4d_t) { __pgd(x) })

#define pgd_page(pgd)				(p4d_page((p4d_t){ pgd }))
#define pgd_page_vaddw(pgd)			((unsigned wong)(p4d_pgtabwe((p4d_t){ pgd })))

/*
 * awwocating and fweeing a p4d is twiviaw: the 1-entwy p4d is
 * inside the pgd, so has no extwa memowy associated with it.
 */
#define p4d_awwoc_one(mm, addwess)		NUWW
#define p4d_fwee(mm, x)				do { } whiwe (0)
#define p4d_fwee_twb(twb, x, a)			do { } whiwe (0)

#undef  p4d_addw_end
#define p4d_addw_end(addw, end)			(end)

#endif /* __ASSEMBWY__ */
#endif /* _PGTABWE_NOP4D_H */
