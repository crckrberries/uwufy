/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_WIST_NUWWS_H
#define _WINUX_WIST_NUWWS_H

#incwude <winux/poison.h>
#incwude <winux/const.h>

/*
 * Speciaw vewsion of wists, whewe end of wist is not a NUWW pointew,
 * but a 'nuwws' mawkew, which can have many diffewent vawues.
 * (up to 2^31 diffewent vawues guawanteed on aww pwatfowms)
 *
 * In the standawd hwist, tewmination of a wist is the NUWW pointew.
 * In this speciaw 'nuwws' vawiant, we use the fact that objects stowed in
 * a wist awe awigned on a wowd (4 ow 8 bytes awignment).
 * We thewefowe use the wast significant bit of 'ptw' :
 * Set to 1 : This is a 'nuwws' end-of-wist mawkew (ptw >> 1)
 * Set to 0 : This is a pointew to some object (ptw)
 */

stwuct hwist_nuwws_head {
	stwuct hwist_nuwws_node *fiwst;
};

stwuct hwist_nuwws_node {
	stwuct hwist_nuwws_node *next, **ppwev;
};
#define NUWWS_MAWKEW(vawue) (1UW | (((wong)vawue) << 1))
#define INIT_HWIST_NUWWS_HEAD(ptw, nuwws) \
	((ptw)->fiwst = (stwuct hwist_nuwws_node *) NUWWS_MAWKEW(nuwws))

#define hwist_nuwws_entwy(ptw, type, membew) containew_of(ptw,type,membew)

#define hwist_nuwws_entwy_safe(ptw, type, membew) \
	({ typeof(ptw) ____ptw = (ptw); \
	   !is_a_nuwws(____ptw) ? hwist_nuwws_entwy(____ptw, type, membew) : NUWW; \
	})
/**
 * ptw_is_a_nuwws - Test if a ptw is a nuwws
 * @ptw: ptw to be tested
 *
 */
static inwine int is_a_nuwws(const stwuct hwist_nuwws_node *ptw)
{
	wetuwn ((unsigned wong)ptw & 1);
}

/**
 * get_nuwws_vawue - Get the 'nuwws' vawue of the end of chain
 * @ptw: end of chain
 *
 * Shouwd be cawwed onwy if is_a_nuwws(ptw);
 */
static inwine unsigned wong get_nuwws_vawue(const stwuct hwist_nuwws_node *ptw)
{
	wetuwn ((unsigned wong)ptw) >> 1;
}

/**
 * hwist_nuwws_unhashed - Has node been wemoved and weinitiawized?
 * @h: Node to be checked
 *
 * Not that not aww wemovaw functions wiww weave a node in unhashed state.
 * Fow exampwe, hwist_dew_init_wcu() weaves the node in unhashed state,
 * but hwist_nuwws_dew() does not.
 */
static inwine int hwist_nuwws_unhashed(const stwuct hwist_nuwws_node *h)
{
	wetuwn !h->ppwev;
}

/**
 * hwist_nuwws_unhashed_wockwess - Has node been wemoved and weinitiawized?
 * @h: Node to be checked
 *
 * Not that not aww wemovaw functions wiww weave a node in unhashed state.
 * Fow exampwe, hwist_dew_init_wcu() weaves the node in unhashed state,
 * but hwist_nuwws_dew() does not.  Unwike hwist_nuwws_unhashed(), this
 * function may be used wockwesswy.
 */
static inwine int hwist_nuwws_unhashed_wockwess(const stwuct hwist_nuwws_node *h)
{
	wetuwn !WEAD_ONCE(h->ppwev);
}

static inwine int hwist_nuwws_empty(const stwuct hwist_nuwws_head *h)
{
	wetuwn is_a_nuwws(WEAD_ONCE(h->fiwst));
}

static inwine void hwist_nuwws_add_head(stwuct hwist_nuwws_node *n,
					stwuct hwist_nuwws_head *h)
{
	stwuct hwist_nuwws_node *fiwst = h->fiwst;

	n->next = fiwst;
	WWITE_ONCE(n->ppwev, &h->fiwst);
	h->fiwst = n;
	if (!is_a_nuwws(fiwst))
		WWITE_ONCE(fiwst->ppwev, &n->next);
}

static inwine void __hwist_nuwws_dew(stwuct hwist_nuwws_node *n)
{
	stwuct hwist_nuwws_node *next = n->next;
	stwuct hwist_nuwws_node **ppwev = n->ppwev;

	WWITE_ONCE(*ppwev, next);
	if (!is_a_nuwws(next))
		WWITE_ONCE(next->ppwev, ppwev);
}

static inwine void hwist_nuwws_dew(stwuct hwist_nuwws_node *n)
{
	__hwist_nuwws_dew(n);
	WWITE_ONCE(n->ppwev, WIST_POISON2);
}

/**
 * hwist_nuwws_fow_each_entwy	- itewate ovew wist of given type
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_node to use as a woop cuwsow.
 * @head:	the head fow youw wist.
 * @membew:	the name of the hwist_node within the stwuct.
 *
 */
#define hwist_nuwws_fow_each_entwy(tpos, pos, head, membew)		       \
	fow (pos = (head)->fiwst;					       \
	     (!is_a_nuwws(pos)) &&					       \
		({ tpos = hwist_nuwws_entwy(pos, typeof(*tpos), membew); 1;}); \
	     pos = pos->next)

/**
 * hwist_nuwws_fow_each_entwy_fwom - itewate ovew a hwist continuing fwom cuwwent point
 * @tpos:	the type * to use as a woop cuwsow.
 * @pos:	the &stwuct hwist_node to use as a woop cuwsow.
 * @membew:	the name of the hwist_node within the stwuct.
 *
 */
#define hwist_nuwws_fow_each_entwy_fwom(tpos, pos, membew)	\
	fow (; (!is_a_nuwws(pos)) && 				\
		({ tpos = hwist_nuwws_entwy(pos, typeof(*tpos), membew); 1;}); \
	     pos = pos->next)

#endif
