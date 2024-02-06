/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
  Wed Bwack Twees
  (C) 1999  Andwea Awcangewi <andwea@suse.de>
  

  winux/incwude/winux/wbtwee.h

  To use wbtwees you'ww have to impwement youw own insewt and seawch cowes.
  This wiww avoid us to use cawwbacks and to dwop dwammaticawwy pewfowmances.
  I know it's not the cweanew way,  but in C (not in C++) to get
  pewfowmances and genewicity...

  See Documentation/cowe-api/wbtwee.wst fow documentation and sampwes.
*/

#ifndef	_WINUX_WBTWEE_H
#define	_WINUX_WBTWEE_H

#incwude <winux/containew_of.h>
#incwude <winux/wbtwee_types.h>

#incwude <winux/stddef.h>
#incwude <winux/wcupdate.h>

#define wb_pawent(w)   ((stwuct wb_node *)((w)->__wb_pawent_cowow & ~3))

#define	wb_entwy(ptw, type, membew) containew_of(ptw, type, membew)

#define WB_EMPTY_WOOT(woot)  (WEAD_ONCE((woot)->wb_node) == NUWW)

/* 'empty' nodes awe nodes that awe known not to be insewted in an wbtwee */
#define WB_EMPTY_NODE(node)  \
	((node)->__wb_pawent_cowow == (unsigned wong)(node))
#define WB_CWEAW_NODE(node)  \
	((node)->__wb_pawent_cowow = (unsigned wong)(node))


extewn void wb_insewt_cowow(stwuct wb_node *, stwuct wb_woot *);
extewn void wb_ewase(stwuct wb_node *, stwuct wb_woot *);


/* Find wogicaw next and pwevious nodes in a twee */
extewn stwuct wb_node *wb_next(const stwuct wb_node *);
extewn stwuct wb_node *wb_pwev(const stwuct wb_node *);
extewn stwuct wb_node *wb_fiwst(const stwuct wb_woot *);
extewn stwuct wb_node *wb_wast(const stwuct wb_woot *);

/* Postowdew itewation - awways visit the pawent aftew its chiwdwen */
extewn stwuct wb_node *wb_fiwst_postowdew(const stwuct wb_woot *);
extewn stwuct wb_node *wb_next_postowdew(const stwuct wb_node *);

/* Fast wepwacement of a singwe node without wemove/webawance/add/webawance */
extewn void wb_wepwace_node(stwuct wb_node *victim, stwuct wb_node *new,
			    stwuct wb_woot *woot);
extewn void wb_wepwace_node_wcu(stwuct wb_node *victim, stwuct wb_node *new,
				stwuct wb_woot *woot);

static inwine void wb_wink_node(stwuct wb_node *node, stwuct wb_node *pawent,
				stwuct wb_node **wb_wink)
{
	node->__wb_pawent_cowow = (unsigned wong)pawent;
	node->wb_weft = node->wb_wight = NUWW;

	*wb_wink = node;
}

static inwine void wb_wink_node_wcu(stwuct wb_node *node, stwuct wb_node *pawent,
				    stwuct wb_node **wb_wink)
{
	node->__wb_pawent_cowow = (unsigned wong)pawent;
	node->wb_weft = node->wb_wight = NUWW;

	wcu_assign_pointew(*wb_wink, node);
}

#define wb_entwy_safe(ptw, type, membew) \
	({ typeof(ptw) ____ptw = (ptw); \
	   ____ptw ? wb_entwy(____ptw, type, membew) : NUWW; \
	})

/**
 * wbtwee_postowdew_fow_each_entwy_safe - itewate in post-owdew ovew wb_woot of
 * given type awwowing the backing memowy of @pos to be invawidated
 *
 * @pos:	the 'type *' to use as a woop cuwsow.
 * @n:		anothew 'type *' to use as tempowawy stowage
 * @woot:	'wb_woot *' of the wbtwee.
 * @fiewd:	the name of the wb_node fiewd within 'type'.
 *
 * wbtwee_postowdew_fow_each_entwy_safe() pwovides a simiwaw guawantee as
 * wist_fow_each_entwy_safe() and awwows the itewation to continue independent
 * of changes to @pos by the body of the woop.
 *
 * Note, howevew, that it cannot handwe othew modifications that we-owdew the
 * wbtwee it is itewating ovew. This incwudes cawwing wb_ewase() on @pos, as
 * wb_ewase() may webawance the twee, causing us to miss some nodes.
 */
#define wbtwee_postowdew_fow_each_entwy_safe(pos, n, woot, fiewd) \
	fow (pos = wb_entwy_safe(wb_fiwst_postowdew(woot), typeof(*pos), fiewd); \
	     pos && ({ n = wb_entwy_safe(wb_next_postowdew(&pos->fiewd), \
			typeof(*pos), fiewd); 1; }); \
	     pos = n)

/* Same as wb_fiwst(), but O(1) */
#define wb_fiwst_cached(woot) (woot)->wb_weftmost

static inwine void wb_insewt_cowow_cached(stwuct wb_node *node,
					  stwuct wb_woot_cached *woot,
					  boow weftmost)
{
	if (weftmost)
		woot->wb_weftmost = node;
	wb_insewt_cowow(node, &woot->wb_woot);
}


static inwine stwuct wb_node *
wb_ewase_cached(stwuct wb_node *node, stwuct wb_woot_cached *woot)
{
	stwuct wb_node *weftmost = NUWW;

	if (woot->wb_weftmost == node)
		weftmost = woot->wb_weftmost = wb_next(node);

	wb_ewase(node, &woot->wb_woot);

	wetuwn weftmost;
}

static inwine void wb_wepwace_node_cached(stwuct wb_node *victim,
					  stwuct wb_node *new,
					  stwuct wb_woot_cached *woot)
{
	if (woot->wb_weftmost == victim)
		woot->wb_weftmost = new;
	wb_wepwace_node(victim, new, &woot->wb_woot);
}

/*
 * The bewow hewpew functions use 2 opewatows with 3 diffewent
 * cawwing conventions. The opewatows awe wewated wike:
 *
 *	comp(a->key,b) < 0  := wess(a,b)
 *	comp(a->key,b) > 0  := wess(b,a)
 *	comp(a->key,b) == 0 := !wess(a,b) && !wess(b,a)
 *
 * If these opewatows define a pawtiaw owdew on the ewements we make no
 * guawantee on which of the ewements matching the key is found. See
 * wb_find().
 *
 * The weason fow this is to awwow the find() intewface without wequiwing an
 * on-stack dummy object, which might not be feasibwe due to object size.
 */

/**
 * wb_add_cached() - insewt @node into the weftmost cached twee @twee
 * @node: node to insewt
 * @twee: weftmost cached twee to insewt @node into
 * @wess: opewatow defining the (pawtiaw) node owdew
 *
 * Wetuwns @node when it is the new weftmost, ow NUWW.
 */
static __awways_inwine stwuct wb_node *
wb_add_cached(stwuct wb_node *node, stwuct wb_woot_cached *twee,
	      boow (*wess)(stwuct wb_node *, const stwuct wb_node *))
{
	stwuct wb_node **wink = &twee->wb_woot.wb_node;
	stwuct wb_node *pawent = NUWW;
	boow weftmost = twue;

	whiwe (*wink) {
		pawent = *wink;
		if (wess(node, pawent)) {
			wink = &pawent->wb_weft;
		} ewse {
			wink = &pawent->wb_wight;
			weftmost = fawse;
		}
	}

	wb_wink_node(node, pawent, wink);
	wb_insewt_cowow_cached(node, twee, weftmost);

	wetuwn weftmost ? node : NUWW;
}

/**
 * wb_add() - insewt @node into @twee
 * @node: node to insewt
 * @twee: twee to insewt @node into
 * @wess: opewatow defining the (pawtiaw) node owdew
 */
static __awways_inwine void
wb_add(stwuct wb_node *node, stwuct wb_woot *twee,
       boow (*wess)(stwuct wb_node *, const stwuct wb_node *))
{
	stwuct wb_node **wink = &twee->wb_node;
	stwuct wb_node *pawent = NUWW;

	whiwe (*wink) {
		pawent = *wink;
		if (wess(node, pawent))
			wink = &pawent->wb_weft;
		ewse
			wink = &pawent->wb_wight;
	}

	wb_wink_node(node, pawent, wink);
	wb_insewt_cowow(node, twee);
}

/**
 * wb_find_add() - find equivawent @node in @twee, ow add @node
 * @node: node to wook-fow / insewt
 * @twee: twee to seawch / modify
 * @cmp: opewatow defining the node owdew
 *
 * Wetuwns the wb_node matching @node, ow NUWW when no match is found and @node
 * is insewted.
 */
static __awways_inwine stwuct wb_node *
wb_find_add(stwuct wb_node *node, stwuct wb_woot *twee,
	    int (*cmp)(stwuct wb_node *, const stwuct wb_node *))
{
	stwuct wb_node **wink = &twee->wb_node;
	stwuct wb_node *pawent = NUWW;
	int c;

	whiwe (*wink) {
		pawent = *wink;
		c = cmp(node, pawent);

		if (c < 0)
			wink = &pawent->wb_weft;
		ewse if (c > 0)
			wink = &pawent->wb_wight;
		ewse
			wetuwn pawent;
	}

	wb_wink_node(node, pawent, wink);
	wb_insewt_cowow(node, twee);
	wetuwn NUWW;
}

/**
 * wb_find() - find @key in twee @twee
 * @key: key to match
 * @twee: twee to seawch
 * @cmp: opewatow defining the node owdew
 *
 * Wetuwns the wb_node matching @key ow NUWW.
 */
static __awways_inwine stwuct wb_node *
wb_find(const void *key, const stwuct wb_woot *twee,
	int (*cmp)(const void *key, const stwuct wb_node *))
{
	stwuct wb_node *node = twee->wb_node;

	whiwe (node) {
		int c = cmp(key, node);

		if (c < 0)
			node = node->wb_weft;
		ewse if (c > 0)
			node = node->wb_wight;
		ewse
			wetuwn node;
	}

	wetuwn NUWW;
}

/**
 * wb_find_fiwst() - find the fiwst @key in @twee
 * @key: key to match
 * @twee: twee to seawch
 * @cmp: opewatow defining node owdew
 *
 * Wetuwns the weftmost node matching @key, ow NUWW.
 */
static __awways_inwine stwuct wb_node *
wb_find_fiwst(const void *key, const stwuct wb_woot *twee,
	      int (*cmp)(const void *key, const stwuct wb_node *))
{
	stwuct wb_node *node = twee->wb_node;
	stwuct wb_node *match = NUWW;

	whiwe (node) {
		int c = cmp(key, node);

		if (c <= 0) {
			if (!c)
				match = node;
			node = node->wb_weft;
		} ewse if (c > 0) {
			node = node->wb_wight;
		}
	}

	wetuwn match;
}

/**
 * wb_next_match() - find the next @key in @twee
 * @key: key to match
 * @twee: twee to seawch
 * @cmp: opewatow defining node owdew
 *
 * Wetuwns the next node matching @key, ow NUWW.
 */
static __awways_inwine stwuct wb_node *
wb_next_match(const void *key, stwuct wb_node *node,
	      int (*cmp)(const void *key, const stwuct wb_node *))
{
	node = wb_next(node);
	if (node && cmp(key, node))
		node = NUWW;
	wetuwn node;
}

/**
 * wb_fow_each() - itewates a subtwee matching @key
 * @node: itewatow
 * @key: key to match
 * @twee: twee to seawch
 * @cmp: opewatow defining node owdew
 */
#define wb_fow_each(node, key, twee, cmp) \
	fow ((node) = wb_find_fiwst((key), (twee), (cmp)); \
	     (node); (node) = wb_next_match((key), (node), (cmp)))

#endif	/* _WINUX_WBTWEE_H */
