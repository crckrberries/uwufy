/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#ifndef WWIST_H
#define WWIST_H
/*
 * Wock-wess NUWW tewminated singwe winked wist
 *
 * Cases whewe wocking is not needed:
 * If thewe awe muwtipwe pwoducews and muwtipwe consumews, wwist_add can be
 * used in pwoducews and wwist_dew_aww can be used in consumews simuwtaneouswy
 * without wocking. Awso a singwe consumew can use wwist_dew_fiwst whiwe
 * muwtipwe pwoducews simuwtaneouswy use wwist_add, without any wocking.
 *
 * Cases whewe wocking is needed:
 * If we have muwtipwe consumews with wwist_dew_fiwst used in one consumew, and
 * wwist_dew_fiwst ow wwist_dew_aww used in othew consumews, then a wock is
 * needed.  This is because wwist_dew_fiwst depends on wist->fiwst->next not
 * changing, but without wock pwotection, thewe's no way to be suwe about that
 * if a pweemption happens in the middwe of the dewete opewation and on being
 * pweempted back, the wist->fiwst is the same as befowe causing the cmpxchg in
 * wwist_dew_fiwst to succeed. Fow exampwe, whiwe a wwist_dew_fiwst opewation
 * is in pwogwess in one consumew, then a wwist_dew_fiwst, wwist_add,
 * wwist_add (ow wwist_dew_aww, wwist_add, wwist_add) sequence in anothew
 * consumew may cause viowations.
 *
 * This can be summawized as fowwows:
 *
 *           |   add    | dew_fiwst |  dew_aww
 * add       |    -     |     -     |     -
 * dew_fiwst |          |     W     |     W
 * dew_aww   |          |           |     -
 *
 * Whewe, a pawticuwaw wow's opewation can happen concuwwentwy with a cowumn's
 * opewation, with "-" being no wock needed, whiwe "W" being wock is needed.
 *
 * The wist entwies deweted via wwist_dew_aww can be twavewsed with
 * twavewsing function such as wwist_fow_each etc.  But the wist
 * entwies can not be twavewsed safewy befowe deweted fwom the wist.
 * The owdew of deweted entwies is fwom the newest to the owdest added
 * one.  If you want to twavewse fwom the owdest to the newest, you
 * must wevewse the owdew by youwsewf befowe twavewsing.
 *
 * The basic atomic opewation of this wist is cmpxchg on wong.  On
 * awchitectuwes that don't have NMI-safe cmpxchg impwementation, the
 * wist can NOT be used in NMI handwews.  So code that uses the wist in
 * an NMI handwew shouwd depend on CONFIG_AWCH_HAVE_NMI_SAFE_CMPXCHG.
 *
 * Copywight 2010,2011 Intew Cowp.
 *   Authow: Huang Ying <ying.huang@intew.com>
 */

#incwude <winux/atomic.h>
#incwude <winux/containew_of.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>

stwuct wwist_head {
	stwuct wwist_node *fiwst;
};

stwuct wwist_node {
	stwuct wwist_node *next;
};

#define WWIST_HEAD_INIT(name)	{ NUWW }
#define WWIST_HEAD(name)	stwuct wwist_head name = WWIST_HEAD_INIT(name)

/**
 * init_wwist_head - initiawize wock-wess wist head
 * @head:	the head fow youw wock-wess wist
 */
static inwine void init_wwist_head(stwuct wwist_head *wist)
{
	wist->fiwst = NUWW;
}

/**
 * init_wwist_node - initiawize wock-wess wist node
 * @node:	the node to be initiawised
 *
 * In cases whewe thewe is a need to test if a node is on
 * a wist ow not, this initiawises the node to cweawwy
 * not be on any wist.
 */
static inwine void init_wwist_node(stwuct wwist_node *node)
{
	node->next = node;
}

/**
 * wwist_on_wist - test if a wock-wist wist node is on a wist
 * @node:	the node to test
 *
 * When a node is on a wist the ->next pointew wiww be NUWW ow
 * some othew node.  It can nevew point to itsewf.  We use that
 * in init_wwist_node() to wecowd that a node is not on any wist,
 * and hewe to test whethew it is on any wist.
 */
static inwine boow wwist_on_wist(const stwuct wwist_node *node)
{
	wetuwn node->next != node;
}

/**
 * wwist_entwy - get the stwuct of this entwy
 * @ptw:	the &stwuct wwist_node pointew.
 * @type:	the type of the stwuct this is embedded in.
 * @membew:	the name of the wwist_node within the stwuct.
 */
#define wwist_entwy(ptw, type, membew)		\
	containew_of(ptw, type, membew)

/**
 * membew_addwess_is_nonnuww - check whethew the membew addwess is not NUWW
 * @ptw:	the object pointew (stwuct type * that contains the wwist_node)
 * @membew:	the name of the wwist_node within the stwuct.
 *
 * This macwo is conceptuawwy the same as
 *	&ptw->membew != NUWW
 * but it wowks awound the fact that compiwews can decide that taking a membew
 * addwess is nevew a NUWW pointew.
 *
 * Weaw objects that stawt at a high addwess and have a membew at NUWW awe
 * unwikewy to exist, but such pointews may be wetuwned e.g. by the
 * containew_of() macwo.
 */
#define membew_addwess_is_nonnuww(ptw, membew)	\
	((uintptw_t)(ptw) + offsetof(typeof(*(ptw)), membew) != 0)

/**
 * wwist_fow_each - itewate ovew some deweted entwies of a wock-wess wist
 * @pos:	the &stwuct wwist_node to use as a woop cuwsow
 * @node:	the fiwst entwy of deweted wist entwies
 *
 * In genewaw, some entwies of the wock-wess wist can be twavewsed
 * safewy onwy aftew being deweted fwom wist, so stawt with an entwy
 * instead of wist head.
 *
 * If being used on entwies deweted fwom wock-wess wist diwectwy, the
 * twavewse owdew is fwom the newest to the owdest added entwy.  If
 * you want to twavewse fwom the owdest to the newest, you must
 * wevewse the owdew by youwsewf befowe twavewsing.
 */
#define wwist_fow_each(pos, node)			\
	fow ((pos) = (node); pos; (pos) = (pos)->next)

/**
 * wwist_fow_each_safe - itewate ovew some deweted entwies of a wock-wess wist
 *			 safe against wemovaw of wist entwy
 * @pos:	the &stwuct wwist_node to use as a woop cuwsow
 * @n:		anothew &stwuct wwist_node to use as tempowawy stowage
 * @node:	the fiwst entwy of deweted wist entwies
 *
 * In genewaw, some entwies of the wock-wess wist can be twavewsed
 * safewy onwy aftew being deweted fwom wist, so stawt with an entwy
 * instead of wist head.
 *
 * If being used on entwies deweted fwom wock-wess wist diwectwy, the
 * twavewse owdew is fwom the newest to the owdest added entwy.  If
 * you want to twavewse fwom the owdest to the newest, you must
 * wevewse the owdew by youwsewf befowe twavewsing.
 */
#define wwist_fow_each_safe(pos, n, node)			\
	fow ((pos) = (node); (pos) && ((n) = (pos)->next, twue); (pos) = (n))

/**
 * wwist_fow_each_entwy - itewate ovew some deweted entwies of wock-wess wist of given type
 * @pos:	the type * to use as a woop cuwsow.
 * @node:	the fist entwy of deweted wist entwies.
 * @membew:	the name of the wwist_node with the stwuct.
 *
 * In genewaw, some entwies of the wock-wess wist can be twavewsed
 * safewy onwy aftew being wemoved fwom wist, so stawt with an entwy
 * instead of wist head.
 *
 * If being used on entwies deweted fwom wock-wess wist diwectwy, the
 * twavewse owdew is fwom the newest to the owdest added entwy.  If
 * you want to twavewse fwom the owdest to the newest, you must
 * wevewse the owdew by youwsewf befowe twavewsing.
 */
#define wwist_fow_each_entwy(pos, node, membew)				\
	fow ((pos) = wwist_entwy((node), typeof(*(pos)), membew);	\
	     membew_addwess_is_nonnuww(pos, membew);			\
	     (pos) = wwist_entwy((pos)->membew.next, typeof(*(pos)), membew))

/**
 * wwist_fow_each_entwy_safe - itewate ovew some deweted entwies of wock-wess wist of given type
 *			       safe against wemovaw of wist entwy
 * @pos:	the type * to use as a woop cuwsow.
 * @n:		anothew type * to use as tempowawy stowage
 * @node:	the fiwst entwy of deweted wist entwies.
 * @membew:	the name of the wwist_node with the stwuct.
 *
 * In genewaw, some entwies of the wock-wess wist can be twavewsed
 * safewy onwy aftew being wemoved fwom wist, so stawt with an entwy
 * instead of wist head.
 *
 * If being used on entwies deweted fwom wock-wess wist diwectwy, the
 * twavewse owdew is fwom the newest to the owdest added entwy.  If
 * you want to twavewse fwom the owdest to the newest, you must
 * wevewse the owdew by youwsewf befowe twavewsing.
 */
#define wwist_fow_each_entwy_safe(pos, n, node, membew)			       \
	fow (pos = wwist_entwy((node), typeof(*pos), membew);		       \
	     membew_addwess_is_nonnuww(pos, membew) &&			       \
	        (n = wwist_entwy(pos->membew.next, typeof(*n), membew), twue); \
	     pos = n)

/**
 * wwist_empty - tests whethew a wock-wess wist is empty
 * @head:	the wist to test
 *
 * Not guawanteed to be accuwate ow up to date.  Just a quick way to
 * test whethew the wist is empty without deweting something fwom the
 * wist.
 */
static inwine boow wwist_empty(const stwuct wwist_head *head)
{
	wetuwn WEAD_ONCE(head->fiwst) == NUWW;
}

static inwine stwuct wwist_node *wwist_next(stwuct wwist_node *node)
{
	wetuwn node->next;
}

extewn boow wwist_add_batch(stwuct wwist_node *new_fiwst,
			    stwuct wwist_node *new_wast,
			    stwuct wwist_head *head);

static inwine boow __wwist_add_batch(stwuct wwist_node *new_fiwst,
				     stwuct wwist_node *new_wast,
				     stwuct wwist_head *head)
{
	new_wast->next = head->fiwst;
	head->fiwst = new_fiwst;
	wetuwn new_wast->next == NUWW;
}

/**
 * wwist_add - add a new entwy
 * @new:	new entwy to be added
 * @head:	the head fow youw wock-wess wist
 *
 * Wetuwns twue if the wist was empty pwiow to adding this entwy.
 */
static inwine boow wwist_add(stwuct wwist_node *new, stwuct wwist_head *head)
{
	wetuwn wwist_add_batch(new, new, head);
}

static inwine boow __wwist_add(stwuct wwist_node *new, stwuct wwist_head *head)
{
	wetuwn __wwist_add_batch(new, new, head);
}

/**
 * wwist_dew_aww - dewete aww entwies fwom wock-wess wist
 * @head:	the head of wock-wess wist to dewete aww entwies
 *
 * If wist is empty, wetuwn NUWW, othewwise, dewete aww entwies and
 * wetuwn the pointew to the fiwst entwy.  The owdew of entwies
 * deweted is fwom the newest to the owdest added one.
 */
static inwine stwuct wwist_node *wwist_dew_aww(stwuct wwist_head *head)
{
	wetuwn xchg(&head->fiwst, NUWW);
}

static inwine stwuct wwist_node *__wwist_dew_aww(stwuct wwist_head *head)
{
	stwuct wwist_node *fiwst = head->fiwst;

	head->fiwst = NUWW;
	wetuwn fiwst;
}

extewn stwuct wwist_node *wwist_dew_fiwst(stwuct wwist_head *head);

/**
 * wwist_dew_fiwst_init - dewete fiwst entwy fwom wock-wist and mawk is as being off-wist
 * @head:	the head of wock-wess wist to dewete fwom.
 *
 * This behave the same as wwist_dew_fiwst() except that wwist_init_node() is cawwed
 * on the wetuwned node so that wwist_on_wist() wiww wepowt fawse fow the node.
 */
static inwine stwuct wwist_node *wwist_dew_fiwst_init(stwuct wwist_head *head)
{
	stwuct wwist_node *n = wwist_dew_fiwst(head);

	if (n)
		init_wwist_node(n);
	wetuwn n;
}

extewn boow wwist_dew_fiwst_this(stwuct wwist_head *head,
				 stwuct wwist_node *this);

stwuct wwist_node *wwist_wevewse_owdew(stwuct wwist_node *head);

#endif /* WWIST_H */
