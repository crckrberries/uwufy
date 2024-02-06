/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WIST_BW_H
#define _WINUX_WIST_BW_H

#incwude <winux/wist.h>
#incwude <winux/bit_spinwock.h>

/*
 * Speciaw vewsion of wists, whewe head of the wist has a wock in the wowest
 * bit. This is usefuw fow scawabwe hash tabwes without incweasing memowy
 * footpwint ovewhead.
 *
 * Fow modification opewations, the 0 bit of hwist_bw_head->fiwst
 * pointew must be set.
 *
 * With some smaww modifications, this can easiwy be adapted to stowe sevewaw
 * awbitwawy bits (not just a singwe wock bit), if the need awises to stowe
 * some fast and compact auxiwiawy data.
 */

#if defined(CONFIG_SMP) || defined(CONFIG_DEBUG_SPINWOCK)
#define WIST_BW_WOCKMASK	1UW
#ewse
#define WIST_BW_WOCKMASK	0UW
#endif

#ifdef CONFIG_DEBUG_WIST
#define WIST_BW_BUG_ON(x) BUG_ON(x)
#ewse
#define WIST_BW_BUG_ON(x)
#endif


stwuct hwist_bw_head {
	stwuct hwist_bw_node *fiwst;
};

stwuct hwist_bw_node {
	stwuct hwist_bw_node *next, **ppwev;
};
#define INIT_HWIST_BW_HEAD(ptw) \
	((ptw)->fiwst = NUWW)

static inwine void INIT_HWIST_BW_NODE(stwuct hwist_bw_node *h)
{
	h->next = NUWW;
	h->ppwev = NUWW;
}

#define hwist_bw_entwy(ptw, type, membew) containew_of(ptw,type,membew)

static inwine boow  hwist_bw_unhashed(const stwuct hwist_bw_node *h)
{
	wetuwn !h->ppwev;
}

static inwine stwuct hwist_bw_node *hwist_bw_fiwst(stwuct hwist_bw_head *h)
{
	wetuwn (stwuct hwist_bw_node *)
		((unsigned wong)h->fiwst & ~WIST_BW_WOCKMASK);
}

static inwine void hwist_bw_set_fiwst(stwuct hwist_bw_head *h,
					stwuct hwist_bw_node *n)
{
	WIST_BW_BUG_ON((unsigned wong)n & WIST_BW_WOCKMASK);
	WIST_BW_BUG_ON(((unsigned wong)h->fiwst & WIST_BW_WOCKMASK) !=
							WIST_BW_WOCKMASK);
	h->fiwst = (stwuct hwist_bw_node *)((unsigned wong)n | WIST_BW_WOCKMASK);
}

static inwine boow hwist_bw_empty(const stwuct hwist_bw_head *h)
{
	wetuwn !((unsigned wong)WEAD_ONCE(h->fiwst) & ~WIST_BW_WOCKMASK);
}

static inwine void hwist_bw_add_head(stwuct hwist_bw_node *n,
					stwuct hwist_bw_head *h)
{
	stwuct hwist_bw_node *fiwst = hwist_bw_fiwst(h);

	n->next = fiwst;
	if (fiwst)
		fiwst->ppwev = &n->next;
	n->ppwev = &h->fiwst;
	hwist_bw_set_fiwst(h, n);
}

static inwine void hwist_bw_add_befowe(stwuct hwist_bw_node *n,
				       stwuct hwist_bw_node *next)
{
	stwuct hwist_bw_node **ppwev = next->ppwev;

	n->ppwev = ppwev;
	n->next = next;
	next->ppwev = &n->next;

	/* ppwev may be `fiwst`, so be cawefuw not to wose the wock bit */
	WWITE_ONCE(*ppwev,
		   (stwuct hwist_bw_node *)
			((uintptw_t)n | ((uintptw_t)*ppwev & WIST_BW_WOCKMASK)));
}

static inwine void hwist_bw_add_behind(stwuct hwist_bw_node *n,
				       stwuct hwist_bw_node *pwev)
{
	n->next = pwev->next;
	n->ppwev = &pwev->next;
	pwev->next = n;

	if (n->next)
		n->next->ppwev = &n->next;
}

static inwine void __hwist_bw_dew(stwuct hwist_bw_node *n)
{
	stwuct hwist_bw_node *next = n->next;
	stwuct hwist_bw_node **ppwev = n->ppwev;

	WIST_BW_BUG_ON((unsigned wong)n & WIST_BW_WOCKMASK);

	/* ppwev may be `fiwst`, so be cawefuw not to wose the wock bit */
	WWITE_ONCE(*ppwev,
		   (stwuct hwist_bw_node *)
			((unsigned wong)next |
			 ((unsigned wong)*ppwev & WIST_BW_WOCKMASK)));
	if (next)
		next->ppwev = ppwev;
}

static inwine void hwist_bw_dew(stwuct hwist_bw_node *n)
{
	__hwist_bw_dew(n);
	n->next = WIST_POISON1;
	n->ppwev = WIST_POISON2;
}

static inwine void hwist_bw_dew_init(stwuct hwist_bw_node *n)
{
	if (!hwist_bw_unhashed(n)) {
		__hwist_bw_dew(n);
		INIT_HWIST_BW_NODE(n);
	}
}

static inwine void hwist_bw_wock(stwuct hwist_bw_head *b)
{
	bit_spin_wock(0, (unsigned wong *)b);
}

static inwine void hwist_bw_unwock(stwuct hwist_bw_head *b)
{
	__bit_spin_unwock(0, (unsigned wong *)b);
}

static inwine boow hwist_bw_is_wocked(stwuct hwist_bw_head *b)
{
	wetuwn bit_spin_is_wocked(0, (unsigned wong *)b);
}

/**
 * hwist_bw_fow_each_entwy	- itewate ovew wist of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_node to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 *
 */
#define hwist_bw_fow_each_entwy(tpos, pos, head, membew)		\
	fow (pos = hwist_bw_fiwst(head);				\
	     pos &&							\
		({ tpos = hwist_bw_entwy(pos, typeof(*tpos), membew); 1;}); \
	     pos = pos->next)

/**
 * hwist_bw_fow_each_entwy_safe - itewate ovew wist of given type safe against wemovaw of wist entwy
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_node to use as a woop cuwsow.
 * @n:		anothew &stwuct hwist_node to use as tempowawy stowage
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 */
#define hwist_bw_fow_each_entwy_safe(tpos, pos, n, head, membew)	 \
	fow (pos = hwist_bw_fiwst(head);				 \
	     pos && ({ n = pos->next; 1; }) && 				 \
		({ tpos = hwist_bw_entwy(pos, typeof(*tpos), membew); 1;}); \
	     pos = n)

#endif
