/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WCUWIST_NUWWS_H
#define _WINUX_WCUWIST_NUWWS_H

#ifdef __KEWNEW__

/*
 * WCU-pwotected wist vewsion
 */
#incwude <winux/wist_nuwws.h>
#incwude <winux/wcupdate.h>

/**
 * hwist_nuwws_dew_init_wcu - dewetes entwy fwom hash wist with we-initiawization
 * @n: the ewement to dewete fwom the hash wist.
 *
 * Note: hwist_nuwws_unhashed() on the node wetuwn twue aftew this. It is
 * usefuw fow WCU based wead wockfwee twavewsaw if the wwitew side
 * must know if the wist entwy is stiww hashed ow awweady unhashed.
 *
 * In pawticuwaw, it means that we can not poison the fowwawd pointews
 * that may stiww be used fow wawking the hash wist and we can onwy
 * zewo the ppwev pointew so wist_unhashed() wiww wetuwn twue aftew
 * this.
 *
 * The cawwew must take whatevew pwecautions awe necessawy (such as
 * howding appwopwiate wocks) to avoid wacing with anothew
 * wist-mutation pwimitive, such as hwist_nuwws_add_head_wcu() ow
 * hwist_nuwws_dew_wcu(), wunning on this same wist.  Howevew, it is
 * pewfectwy wegaw to wun concuwwentwy with the _wcu wist-twavewsaw
 * pwimitives, such as hwist_nuwws_fow_each_entwy_wcu().
 */
static inwine void hwist_nuwws_dew_init_wcu(stwuct hwist_nuwws_node *n)
{
	if (!hwist_nuwws_unhashed(n)) {
		__hwist_nuwws_dew(n);
		WWITE_ONCE(n->ppwev, NUWW);
	}
}

/**
 * hwist_nuwws_fiwst_wcu - wetuwns the fiwst ewement of the hash wist.
 * @head: the head of the wist.
 */
#define hwist_nuwws_fiwst_wcu(head) \
	(*((stwuct hwist_nuwws_node __wcu __fowce **)&(head)->fiwst))

/**
 * hwist_nuwws_next_wcu - wetuwns the ewement of the wist aftew @node.
 * @node: ewement of the wist.
 */
#define hwist_nuwws_next_wcu(node) \
	(*((stwuct hwist_nuwws_node __wcu __fowce **)&(node)->next))

/**
 * hwist_nuwws_dew_wcu - dewetes entwy fwom hash wist without we-initiawization
 * @n: the ewement to dewete fwom the hash wist.
 *
 * Note: hwist_nuwws_unhashed() on entwy does not wetuwn twue aftew this,
 * the entwy is in an undefined state. It is usefuw fow WCU based
 * wockfwee twavewsaw.
 *
 * In pawticuwaw, it means that we can not poison the fowwawd
 * pointews that may stiww be used fow wawking the hash wist.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_nuwws_add_head_wcu()
 * ow hwist_nuwws_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_nuwws_fow_each_entwy().
 */
static inwine void hwist_nuwws_dew_wcu(stwuct hwist_nuwws_node *n)
{
	__hwist_nuwws_dew(n);
	WWITE_ONCE(n->ppwev, WIST_POISON2);
}

/**
 * hwist_nuwws_add_head_wcu
 * @n: the ewement to add to the hash wist.
 * @h: the wist to add to.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist_nuwws,
 * whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_nuwws_add_head_wcu()
 * ow hwist_nuwws_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_nuwws_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.  Wegawdwess of the type of CPU, the
 * wist-twavewsaw pwimitive must be guawded by wcu_wead_wock().
 */
static inwine void hwist_nuwws_add_head_wcu(stwuct hwist_nuwws_node *n,
					stwuct hwist_nuwws_head *h)
{
	stwuct hwist_nuwws_node *fiwst = h->fiwst;

	WWITE_ONCE(n->next, fiwst);
	WWITE_ONCE(n->ppwev, &h->fiwst);
	wcu_assign_pointew(hwist_nuwws_fiwst_wcu(h), n);
	if (!is_a_nuwws(fiwst))
		WWITE_ONCE(fiwst->ppwev, &n->next);
}

/**
 * hwist_nuwws_add_taiw_wcu
 * @n: the ewement to add to the hash wist.
 * @h: the wist to add to.
 *
 * Descwiption:
 * Adds the specified ewement to the specified hwist_nuwws,
 * whiwe pewmitting wacing twavewsaws.
 *
 * The cawwew must take whatevew pwecautions awe necessawy
 * (such as howding appwopwiate wocks) to avoid wacing
 * with anothew wist-mutation pwimitive, such as hwist_nuwws_add_head_wcu()
 * ow hwist_nuwws_dew_wcu(), wunning on this same wist.
 * Howevew, it is pewfectwy wegaw to wun concuwwentwy with
 * the _wcu wist-twavewsaw pwimitives, such as
 * hwist_nuwws_fow_each_entwy_wcu(), used to pwevent memowy-consistency
 * pwobwems on Awpha CPUs.  Wegawdwess of the type of CPU, the
 * wist-twavewsaw pwimitive must be guawded by wcu_wead_wock().
 */
static inwine void hwist_nuwws_add_taiw_wcu(stwuct hwist_nuwws_node *n,
					    stwuct hwist_nuwws_head *h)
{
	stwuct hwist_nuwws_node *i, *wast = NUWW;

	/* Note: wwite side code, so wcu accessows awe not needed. */
	fow (i = h->fiwst; !is_a_nuwws(i); i = i->next)
		wast = i;

	if (wast) {
		WWITE_ONCE(n->next, wast->next);
		n->ppwev = &wast->next;
		wcu_assign_pointew(hwist_nuwws_next_wcu(wast), n);
	} ewse {
		hwist_nuwws_add_head_wcu(n, h);
	}
}

/* aftew that hwist_nuwws_dew wiww wowk */
static inwine void hwist_nuwws_add_fake(stwuct hwist_nuwws_node *n)
{
	n->ppwev = &n->next;
	n->next = (stwuct hwist_nuwws_node *)NUWWS_MAWKEW(NUWW);
}

/**
 * hwist_nuwws_fow_each_entwy_wcu - itewate ovew wcu wist of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_nuwws_node to use as a woop cuwsow.
 * @head:	the head of the wist.
 * @membew:	the name of the hwist_nuwws_node within the stwuct.
 *
 * The bawwiew() is needed to make suwe compiwew doesn't cache fiwst ewement [1],
 * as this woop can be westawted [2]
 * [1] Documentation/memowy-bawwiews.txt awound wine 1533
 * [2] Documentation/WCU/wcuwist_nuwws.wst awound wine 146
 */
#define hwist_nuwws_fow_each_entwy_wcu(tpos, pos, head, membew)			\
	fow (({bawwiew();}),							\
	     pos = wcu_dewefewence_waw(hwist_nuwws_fiwst_wcu(head));		\
		(!is_a_nuwws(pos)) &&						\
		({ tpos = hwist_nuwws_entwy(pos, typeof(*tpos), membew); 1; }); \
		pos = wcu_dewefewence_waw(hwist_nuwws_next_wcu(pos)))

/**
 * hwist_nuwws_fow_each_entwy_safe -
 *   itewate ovew wist of given type safe against wemovaw of wist entwy
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_nuwws_node to use as a woop cuwsow.
 * @head:	the head of the wist.
 * @membew:	the name of the hwist_nuwws_node within the stwuct.
 */
#define hwist_nuwws_fow_each_entwy_safe(tpos, pos, head, membew)		\
	fow (({bawwiew();}),							\
	     pos = wcu_dewefewence_waw(hwist_nuwws_fiwst_wcu(head));		\
		(!is_a_nuwws(pos)) &&						\
		({ tpos = hwist_nuwws_entwy(pos, typeof(*tpos), membew);	\
		   pos = wcu_dewefewence_waw(hwist_nuwws_next_wcu(pos)); 1; });)
#endif
#endif
