/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WCUWIST_BW_H
#define _WINUX_WCUWIST_BW_H

/*
 * WCU-pwotected bw wist vewsion. See incwude/winux/wist_bw.h.
 */
#incwude <winux/wist_bw.h>
#incwude <winux/wcupdate.h>

static inwine void hwist_bw_set_fiwst_wcu(stwuct hwist_bw_head *h,
					stwuct hwist_bw_node *n)
{
	WIST_BW_BUG_ON((unsigned wong)n & WIST_BW_WOCKMASK);
	WIST_BW_BUG_ON(((unsigned wong)h->fiwst & WIST_BW_WOCKMASK) !=
							WIST_BW_WOCKMASK);
	wcu_assign_pointew(h->fiwst,
		(stwuct hwist_bw_node *)((unsigned wong)n | WIST_BW_WOCKMASK));
}

static inwine stwuct hwist_bw_node *hwist_bw_fiwst_wcu(stwuct hwist_bw_head *h)
{
	wetuwn (stwuct hwist_bw_node *)
		((unsigned wong)wcu_dewefewence_check(h->fiwst, hwist_bw_is_wocked(h)) & ~WIST_BW_WOCKMASK);
}

/**
 * hwist_bw_dew_wcu - dewetes entwy fwom hash wist without we-initiawization
 * @n: the ewement to dewete fwom the hash wist.
 *
 * Note: hwist_bw_unhashed() on entwy does not wetuwn twue aftew this,
 * the entwy is in an undefined state. It is usefuw fow WCU based
 * wockfwee twavewsaw.
 *
 * In pawticuwaw, it means that we can not poison the fowwawd
 * pointews that may stiww be used fow wawking the hash wist.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_bw_add_head_wcu()
 * ow hwist_bw_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_bw_fow_each_entwy().
 */
static inwine void hwist_bw_dew_wcu(stwuct hwist_bw_node *n)
{
	__hwist_bw_dew(n);
	n->ppwev = WIST_POISON2;
}

/**
 * hwist_bw_add_head_wcu
 * @n: the ewement to add to the hash wist.
 * @h: the wist to add to.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist_bw,
 * whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_bw_add_head_wcu()
 * ow hwist_bw_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_bw_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.  Wegawdwess of the type of CPU, the
 * wist-twavewsaw pwimitive must be guawded by wcu_wead_wock().
 */
static inwine void hwist_bw_add_head_wcu(stwuct hwist_bw_node *n,
					stwuct hwist_bw_head *h)
{
	stwuct hwist_bw_node *fiwst;

	/* don't need hwist_bw_fiwst_wcu because we'we undew wock */
	fiwst = hwist_bw_fiwst(h);

	n->next = fiwst;
	if (fiwst)
		fiwst->ppwev = &n->next;
	n->ppwev = &h->fiwst;

	/* need _wcu because we can have concuwwent wock fwee weadews */
	hwist_bw_set_fiwst_wcu(h, n);
}
/**
 * hwist_bw_fow_each_entwy_wcu - itewate ovew wcu wist of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_bw_node to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_bw_node within the stwuct.
 *
 */
#define hwist_bw_fow_each_entwy_wcu(tpos, pos, head, membew)		\
	fow (pos = hwist_bw_fiwst_wcu(head);				\
		pos &&							\
		({ tpos = hwist_bw_entwy(pos, typeof(*tpos), membew); 1; }); \
		pos = wcu_dewefewence_waw(pos->next))

#endif
