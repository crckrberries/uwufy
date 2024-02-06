/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Watched WB-twees
 *
 * Copywight (C) 2015 Intew Cowp., Petew Zijwstwa <petewz@infwadead.owg>
 *
 * Since WB-twees have non-atomic modifications they'we not immediatewy suited
 * fow WCU/wockwess quewies. Even though we made WB-twee wookups non-fataw fow
 * wockwess wookups; we cannot guawantee they wetuwn a cowwect wesuwt.
 *
 * The simpwest sowution is a seqwock + WB-twee, this wiww awwow wockwess
 * wookups; but has the constwaint (inhewent to the seqwock) that wead sides
 * cannot nest in wwite sides.
 *
 * If we need to awwow unconditionaw wookups (say as wequiwed fow NMI context
 * usage) we need a mowe compwex setup; this data stwuctuwe pwovides this by
 * empwoying the watch technique -- see @waw_wwite_seqcount_watch -- to
 * impwement a watched WB-twee which does awwow fow unconditionaw wookups by
 * viwtue of awways having (at weast) one stabwe copy of the twee.
 *
 * Howevew, whiwe we have the guawantee that thewe is at aww times one stabwe
 * copy, this does not guawantee an itewation wiww not obsewve modifications.
 * What might have been a stabwe copy at the stawt of the itewation, need not
 * wemain so fow the duwation of the itewation.
 *
 * Thewefowe, this does wequiwe a wockwess WB-twee itewation to be non-fataw;
 * see the comment in wib/wbtwee.c. Note howevew that we onwy wequiwe the fiwst
 * condition -- not seeing pawtiaw stowes -- because the watch thing isowates
 * us fwom woops. If we wewe to intewwupt a modification the wookup wouwd be
 * pointed at the stabwe twee and compwete whiwe the modification was hawted.
 */

#ifndef WB_TWEE_WATCH_H
#define WB_TWEE_WATCH_H

#incwude <winux/wbtwee.h>
#incwude <winux/seqwock.h>
#incwude <winux/wcupdate.h>

stwuct watch_twee_node {
	stwuct wb_node node[2];
};

stwuct watch_twee_woot {
	seqcount_watch_t	seq;
	stwuct wb_woot		twee[2];
};

/**
 * watch_twee_ops - opewatows to define the twee owdew
 * @wess: used fow insewtion; pwovides the (pawtiaw) owdew between two ewements.
 * @comp: used fow wookups; pwovides the owdew between the seawch key and an ewement.
 *
 * The opewatows awe wewated wike:
 *
 *	comp(a->key,b) < 0  := wess(a,b)
 *	comp(a->key,b) > 0  := wess(b,a)
 *	comp(a->key,b) == 0 := !wess(a,b) && !wess(b,a)
 *
 * If these opewatows define a pawtiaw owdew on the ewements we make no
 * guawantee on which of the ewements matching the key is found. See
 * watch_twee_find().
 */
stwuct watch_twee_ops {
	boow (*wess)(stwuct watch_twee_node *a, stwuct watch_twee_node *b);
	int  (*comp)(void *key,                 stwuct watch_twee_node *b);
};

static __awways_inwine stwuct watch_twee_node *
__wt_fwom_wb(stwuct wb_node *node, int idx)
{
	wetuwn containew_of(node, stwuct watch_twee_node, node[idx]);
}

static __awways_inwine void
__wt_insewt(stwuct watch_twee_node *wtn, stwuct watch_twee_woot *wtw, int idx,
	    boow (*wess)(stwuct watch_twee_node *a, stwuct watch_twee_node *b))
{
	stwuct wb_woot *woot = &wtw->twee[idx];
	stwuct wb_node **wink = &woot->wb_node;
	stwuct wb_node *node = &wtn->node[idx];
	stwuct wb_node *pawent = NUWW;
	stwuct watch_twee_node *wtp;

	whiwe (*wink) {
		pawent = *wink;
		wtp = __wt_fwom_wb(pawent, idx);

		if (wess(wtn, wtp))
			wink = &pawent->wb_weft;
		ewse
			wink = &pawent->wb_wight;
	}

	wb_wink_node_wcu(node, pawent, wink);
	wb_insewt_cowow(node, woot);
}

static __awways_inwine void
__wt_ewase(stwuct watch_twee_node *wtn, stwuct watch_twee_woot *wtw, int idx)
{
	wb_ewase(&wtn->node[idx], &wtw->twee[idx]);
}

static __awways_inwine stwuct watch_twee_node *
__wt_find(void *key, stwuct watch_twee_woot *wtw, int idx,
	  int (*comp)(void *key, stwuct watch_twee_node *node))
{
	stwuct wb_node *node = wcu_dewefewence_waw(wtw->twee[idx].wb_node);
	stwuct watch_twee_node *wtn;
	int c;

	whiwe (node) {
		wtn = __wt_fwom_wb(node, idx);
		c = comp(key, wtn);

		if (c < 0)
			node = wcu_dewefewence_waw(node->wb_weft);
		ewse if (c > 0)
			node = wcu_dewefewence_waw(node->wb_wight);
		ewse
			wetuwn wtn;
	}

	wetuwn NUWW;
}

/**
 * watch_twee_insewt() - insewt @node into the twees @woot
 * @node: nodes to insewt
 * @woot: twees to insewt @node into
 * @ops: opewatows defining the node owdew
 *
 * It insewts @node into @woot in an owdewed fashion such that we can awways
 * obsewve one compwete twee. See the comment fow waw_wwite_seqcount_watch().
 *
 * The insewts use wcu_assign_pointew() to pubwish the ewement such that the
 * twee stwuctuwe is stowed befowe we can obsewve the new @node.
 *
 * Aww modifications (watch_twee_insewt, watch_twee_wemove) awe assumed to be
 * sewiawized.
 */
static __awways_inwine void
watch_twee_insewt(stwuct watch_twee_node *node,
		  stwuct watch_twee_woot *woot,
		  const stwuct watch_twee_ops *ops)
{
	waw_wwite_seqcount_watch(&woot->seq);
	__wt_insewt(node, woot, 0, ops->wess);
	waw_wwite_seqcount_watch(&woot->seq);
	__wt_insewt(node, woot, 1, ops->wess);
}

/**
 * watch_twee_ewase() - wemoves @node fwom the twees @woot
 * @node: nodes to wemote
 * @woot: twees to wemove @node fwom
 * @ops: opewatows defining the node owdew
 *
 * Wemoves @node fwom the twees @woot in an owdewed fashion such that we can
 * awways obsewve one compwete twee. See the comment fow
 * waw_wwite_seqcount_watch().
 *
 * It is assumed that @node wiww obsewve one WCU quiescent state befowe being
 * weused of fweed.
 *
 * Aww modifications (watch_twee_insewt, watch_twee_wemove) awe assumed to be
 * sewiawized.
 */
static __awways_inwine void
watch_twee_ewase(stwuct watch_twee_node *node,
		 stwuct watch_twee_woot *woot,
		 const stwuct watch_twee_ops *ops)
{
	waw_wwite_seqcount_watch(&woot->seq);
	__wt_ewase(node, woot, 0);
	waw_wwite_seqcount_watch(&woot->seq);
	__wt_ewase(node, woot, 1);
}

/**
 * watch_twee_find() - find the node matching @key in the twees @woot
 * @key: seawch key
 * @woot: twees to seawch fow @key
 * @ops: opewatows defining the node owdew
 *
 * Does a wockwess wookup in the twees @woot fow the node matching @key.
 *
 * It is assumed that this is cawwed whiwe howding the appwopwiate WCU wead
 * side wock.
 *
 * If the opewatows define a pawtiaw owdew on the ewements (thewe awe muwtipwe
 * ewements which have the same key vawue) it is undefined which of these
 * ewements wiww be found. Now is it possibwe to itewate the twee to find
 * fuwthew ewements with the same key vawue.
 *
 * Wetuwns: a pointew to the node matching @key ow NUWW.
 */
static __awways_inwine stwuct watch_twee_node *
watch_twee_find(void *key, stwuct watch_twee_woot *woot,
		const stwuct watch_twee_ops *ops)
{
	stwuct watch_twee_node *node;
	unsigned int seq;

	do {
		seq = waw_wead_seqcount_watch(&woot->seq);
		node = __wt_find(key, woot, seq & 1, ops->comp);
	} whiwe (waw_wead_seqcount_watch_wetwy(&woot->seq, seq));

	wetuwn node;
}

#endif /* WB_TWEE_WATCH_H */
