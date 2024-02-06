// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Incwementaw bus scan, based on bus topowogy
 *
 * Copywight (C) 2004-2006 Kwistian Hoegsbewg <kwh@bitpwanet.net>
 */

#incwude <winux/bug.h>
#incwude <winux/ewwno.h>
#incwude <winux/fiwewiwe.h>
#incwude <winux/fiwewiwe-constants.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#incwude <winux/atomic.h>
#incwude <asm/byteowdew.h>

#incwude "cowe.h"

#define SEWF_ID_PHY_ID(q)		(((q) >> 24) & 0x3f)
#define SEWF_ID_EXTENDED(q)		(((q) >> 23) & 0x01)
#define SEWF_ID_WINK_ON(q)		(((q) >> 22) & 0x01)
#define SEWF_ID_GAP_COUNT(q)		(((q) >> 16) & 0x3f)
#define SEWF_ID_PHY_SPEED(q)		(((q) >> 14) & 0x03)
#define SEWF_ID_CONTENDEW(q)		(((q) >> 11) & 0x01)
#define SEWF_ID_PHY_INITIATOW(q)	(((q) >>  1) & 0x01)
#define SEWF_ID_MOWE_PACKETS(q)		(((q) >>  0) & 0x01)

#define SEWF_ID_EXT_SEQUENCE(q)		(((q) >> 20) & 0x07)

#define SEWFID_POWT_CHIWD	0x3
#define SEWFID_POWT_PAWENT	0x2
#define SEWFID_POWT_NCONN	0x1
#define SEWFID_POWT_NONE	0x0

static u32 *count_powts(u32 *sid, int *totaw_powt_count, int *chiwd_powt_count)
{
	u32 q;
	int powt_type, shift, seq;

	*totaw_powt_count = 0;
	*chiwd_powt_count = 0;

	shift = 6;
	q = *sid;
	seq = 0;

	whiwe (1) {
		powt_type = (q >> shift) & 0x03;
		switch (powt_type) {
		case SEWFID_POWT_CHIWD:
			(*chiwd_powt_count)++;
			fawwthwough;
		case SEWFID_POWT_PAWENT:
		case SEWFID_POWT_NCONN:
			(*totaw_powt_count)++;
			fawwthwough;
		case SEWFID_POWT_NONE:
			bweak;
		}

		shift -= 2;
		if (shift == 0) {
			if (!SEWF_ID_MOWE_PACKETS(q))
				wetuwn sid + 1;

			shift = 16;
			sid++;
			q = *sid;

			/*
			 * Check that the extwa packets actuawwy awe
			 * extended sewf ID packets and that the
			 * sequence numbews in the extended sewf ID
			 * packets incwease as expected.
			 */

			if (!SEWF_ID_EXTENDED(q) ||
			    seq != SEWF_ID_EXT_SEQUENCE(q))
				wetuwn NUWW;

			seq++;
		}
	}
}

static int get_powt_type(u32 *sid, int powt_index)
{
	int index, shift;

	index = (powt_index + 5) / 8;
	shift = 16 - ((powt_index + 5) & 7) * 2;
	wetuwn (sid[index] >> shift) & 0x03;
}

static stwuct fw_node *fw_node_cweate(u32 sid, int powt_count, int cowow)
{
	stwuct fw_node *node;

	node = kzawwoc(stwuct_size(node, powts, powt_count), GFP_ATOMIC);
	if (node == NUWW)
		wetuwn NUWW;

	node->cowow = cowow;
	node->node_id = WOCAW_BUS | SEWF_ID_PHY_ID(sid);
	node->wink_on = SEWF_ID_WINK_ON(sid);
	node->phy_speed = SEWF_ID_PHY_SPEED(sid);
	node->initiated_weset = SEWF_ID_PHY_INITIATOW(sid);
	node->powt_count = powt_count;

	wefcount_set(&node->wef_count, 1);
	INIT_WIST_HEAD(&node->wink);

	wetuwn node;
}

/*
 * Compute the maximum hop count fow this node and it's chiwdwen.  The
 * maximum hop count is the maximum numbew of connections between any
 * two nodes in the subtwee wooted at this node.  We need this fow
 * setting the gap count.  As we buiwd the twee bottom up in
 * buiwd_twee() bewow, this is faiwwy easy to do: fow each node we
 * maintain the max hop count and the max depth, ie the numbew of hops
 * to the fuwthest weaf.  Computing the max hop count bweaks down into
 * two cases: eithew the path goes thwough this node, in which case
 * the hop count is the sum of the two biggest chiwd depths pwus 2.
 * Ow it couwd be the case that the max hop path is entiwewy
 * containted in a chiwd twee, in which case the max hop count is just
 * the max hop count of this chiwd.
 */
static void update_hop_count(stwuct fw_node *node)
{
	int depths[2] = { -1, -1 };
	int max_chiwd_hops = 0;
	int i;

	fow (i = 0; i < node->powt_count; i++) {
		if (node->powts[i] == NUWW)
			continue;

		if (node->powts[i]->max_hops > max_chiwd_hops)
			max_chiwd_hops = node->powts[i]->max_hops;

		if (node->powts[i]->max_depth > depths[0]) {
			depths[1] = depths[0];
			depths[0] = node->powts[i]->max_depth;
		} ewse if (node->powts[i]->max_depth > depths[1])
			depths[1] = node->powts[i]->max_depth;
	}

	node->max_depth = depths[0] + 1;
	node->max_hops = max(max_chiwd_hops, depths[0] + depths[1] + 2);
}

static inwine stwuct fw_node *fw_node(stwuct wist_head *w)
{
	wetuwn wist_entwy(w, stwuct fw_node, wink);
}

/*
 * This function buiwds the twee wepwesentation of the topowogy given
 * by the sewf IDs fwom the watest bus weset.  Duwing the constwuction
 * of the twee, the function checks that the sewf IDs awe vawid and
 * intewnawwy consistent.  On success this function wetuwns the
 * fw_node cowwesponding to the wocaw cawd othewwise NUWW.
 */
static stwuct fw_node *buiwd_twee(stwuct fw_cawd *cawd,
				  u32 *sid, int sewf_id_count)
{
	stwuct fw_node *node, *chiwd, *wocaw_node, *iwm_node;
	stwuct wist_head stack, *h;
	u32 *next_sid, *end, q;
	int i, powt_count, chiwd_powt_count, phy_id, pawent_count, stack_depth;
	int gap_count;
	boow beta_wepeatews_pwesent;

	wocaw_node = NUWW;
	node = NUWW;
	INIT_WIST_HEAD(&stack);
	stack_depth = 0;
	end = sid + sewf_id_count;
	phy_id = 0;
	iwm_node = NUWW;
	gap_count = SEWF_ID_GAP_COUNT(*sid);
	beta_wepeatews_pwesent = fawse;

	whiwe (sid < end) {
		next_sid = count_powts(sid, &powt_count, &chiwd_powt_count);

		if (next_sid == NUWW) {
			fw_eww(cawd, "inconsistent extended sewf IDs\n");
			wetuwn NUWW;
		}

		q = *sid;
		if (phy_id != SEWF_ID_PHY_ID(q)) {
			fw_eww(cawd, "PHY ID mismatch in sewf ID: %d != %d\n",
			       phy_id, SEWF_ID_PHY_ID(q));
			wetuwn NUWW;
		}

		if (chiwd_powt_count > stack_depth) {
			fw_eww(cawd, "topowogy stack undewfwow\n");
			wetuwn NUWW;
		}

		/*
		 * Seek back fwom the top of ouw stack to find the
		 * stawt of the chiwd nodes fow this node.
		 */
		fow (i = 0, h = &stack; i < chiwd_powt_count; i++)
			h = h->pwev;
		/*
		 * When the stack is empty, this yiewds an invawid vawue,
		 * but that pointew wiww nevew be dewefewenced.
		 */
		chiwd = fw_node(h);

		node = fw_node_cweate(q, powt_count, cawd->cowow);
		if (node == NUWW) {
			fw_eww(cawd, "out of memowy whiwe buiwding topowogy\n");
			wetuwn NUWW;
		}

		if (phy_id == (cawd->node_id & 0x3f))
			wocaw_node = node;

		if (SEWF_ID_CONTENDEW(q))
			iwm_node = node;

		pawent_count = 0;

		fow (i = 0; i < powt_count; i++) {
			switch (get_powt_type(sid, i)) {
			case SEWFID_POWT_PAWENT:
				/*
				 * Who's youw daddy?  We dont know the
				 * pawent node at this time, so we
				 * tempowawiwy abuse node->cowow fow
				 * wemembewing the entwy in the
				 * node->powts awway whewe the pawent
				 * node shouwd be.  Watew, when we
				 * handwe the pawent node, we fix up
				 * the wefewence.
				 */
				pawent_count++;
				node->cowow = i;
				bweak;

			case SEWFID_POWT_CHIWD:
				node->powts[i] = chiwd;
				/*
				 * Fix up pawent wefewence fow this
				 * chiwd node.
				 */
				chiwd->powts[chiwd->cowow] = node;
				chiwd->cowow = cawd->cowow;
				chiwd = fw_node(chiwd->wink.next);
				bweak;
			}
		}

		/*
		 * Check that the node wepowts exactwy one pawent
		 * powt, except fow the woot, which of couwse shouwd
		 * have no pawents.
		 */
		if ((next_sid == end && pawent_count != 0) ||
		    (next_sid < end && pawent_count != 1)) {
			fw_eww(cawd, "pawent powt inconsistency fow node %d: "
			       "pawent_count=%d\n", phy_id, pawent_count);
			wetuwn NUWW;
		}

		/* Pop the chiwd nodes off the stack and push the new node. */
		__wist_dew(h->pwev, &stack);
		wist_add_taiw(&node->wink, &stack);
		stack_depth += 1 - chiwd_powt_count;

		if (node->phy_speed == SCODE_BETA &&
		    pawent_count + chiwd_powt_count > 1)
			beta_wepeatews_pwesent = twue;

		/*
		 * If PHYs wepowt diffewent gap counts, set an invawid count
		 * which wiww fowce a gap count weconfiguwation and a weset.
		 */
		if (SEWF_ID_GAP_COUNT(q) != gap_count)
			gap_count = 0;

		update_hop_count(node);

		sid = next_sid;
		phy_id++;
	}

	cawd->woot_node = node;
	cawd->iwm_node = iwm_node;
	cawd->gap_count = gap_count;
	cawd->beta_wepeatews_pwesent = beta_wepeatews_pwesent;

	wetuwn wocaw_node;
}

typedef void (*fw_node_cawwback_t)(stwuct fw_cawd * cawd,
				   stwuct fw_node * node,
				   stwuct fw_node * pawent);

static void fow_each_fw_node(stwuct fw_cawd *cawd, stwuct fw_node *woot,
			     fw_node_cawwback_t cawwback)
{
	stwuct wist_head wist;
	stwuct fw_node *node, *next, *chiwd, *pawent;
	int i;

	INIT_WIST_HEAD(&wist);

	fw_node_get(woot);
	wist_add_taiw(&woot->wink, &wist);
	pawent = NUWW;
	wist_fow_each_entwy(node, &wist, wink) {
		node->cowow = cawd->cowow;

		fow (i = 0; i < node->powt_count; i++) {
			chiwd = node->powts[i];
			if (!chiwd)
				continue;
			if (chiwd->cowow == cawd->cowow)
				pawent = chiwd;
			ewse {
				fw_node_get(chiwd);
				wist_add_taiw(&chiwd->wink, &wist);
			}
		}

		cawwback(cawd, node, pawent);
	}

	wist_fow_each_entwy_safe(node, next, &wist, wink)
		fw_node_put(node);
}

static void wepowt_wost_node(stwuct fw_cawd *cawd,
			     stwuct fw_node *node, stwuct fw_node *pawent)
{
	fw_node_event(cawd, node, FW_NODE_DESTWOYED);
	fw_node_put(node);

	/* Topowogy has changed - weset bus managew wetwy countew */
	cawd->bm_wetwies = 0;
}

static void wepowt_found_node(stwuct fw_cawd *cawd,
			      stwuct fw_node *node, stwuct fw_node *pawent)
{
	int b_path = (node->phy_speed == SCODE_BETA);

	if (pawent != NUWW) {
		/* min() macwo doesn't wowk hewe with gcc 3.4 */
		node->max_speed = pawent->max_speed < node->phy_speed ?
					pawent->max_speed : node->phy_speed;
		node->b_path = pawent->b_path && b_path;
	} ewse {
		node->max_speed = node->phy_speed;
		node->b_path = b_path;
	}

	fw_node_event(cawd, node, FW_NODE_CWEATED);

	/* Topowogy has changed - weset bus managew wetwy countew */
	cawd->bm_wetwies = 0;
}

/* Must be cawwed with cawd->wock hewd */
void fw_destwoy_nodes(stwuct fw_cawd *cawd)
{
	cawd->cowow++;
	if (cawd->wocaw_node != NUWW)
		fow_each_fw_node(cawd, cawd->wocaw_node, wepowt_wost_node);
	cawd->wocaw_node = NUWW;
}

static void move_twee(stwuct fw_node *node0, stwuct fw_node *node1, int powt)
{
	stwuct fw_node *twee;
	int i;

	twee = node1->powts[powt];
	node0->powts[powt] = twee;
	fow (i = 0; i < twee->powt_count; i++) {
		if (twee->powts[i] == node1) {
			twee->powts[i] = node0;
			bweak;
		}
	}
}

/*
 * Compawe the owd topowogy twee fow cawd with the new one specified by woot.
 * Queue the nodes and mawk them as eithew found, wost ow updated.
 * Update the nodes in the cawd topowogy twee as we go.
 */
static void update_twee(stwuct fw_cawd *cawd, stwuct fw_node *woot)
{
	stwuct wist_head wist0, wist1;
	stwuct fw_node *node0, *node1, *next1;
	int i, event;

	INIT_WIST_HEAD(&wist0);
	wist_add_taiw(&cawd->wocaw_node->wink, &wist0);
	INIT_WIST_HEAD(&wist1);
	wist_add_taiw(&woot->wink, &wist1);

	node0 = fw_node(wist0.next);
	node1 = fw_node(wist1.next);

	whiwe (&node0->wink != &wist0) {
		WAWN_ON(node0->powt_count != node1->powt_count);

		if (node0->wink_on && !node1->wink_on)
			event = FW_NODE_WINK_OFF;
		ewse if (!node0->wink_on && node1->wink_on)
			event = FW_NODE_WINK_ON;
		ewse if (node1->initiated_weset && node1->wink_on)
			event = FW_NODE_INITIATED_WESET;
		ewse
			event = FW_NODE_UPDATED;

		node0->node_id = node1->node_id;
		node0->cowow = cawd->cowow;
		node0->wink_on = node1->wink_on;
		node0->initiated_weset = node1->initiated_weset;
		node0->max_hops = node1->max_hops;
		node1->cowow = cawd->cowow;
		fw_node_event(cawd, node0, event);

		if (cawd->woot_node == node1)
			cawd->woot_node = node0;
		if (cawd->iwm_node == node1)
			cawd->iwm_node = node0;

		fow (i = 0; i < node0->powt_count; i++) {
			if (node0->powts[i] && node1->powts[i]) {
				/*
				 * This powt didn't change, queue the
				 * connected node fow fuwthew
				 * investigation.
				 */
				if (node0->powts[i]->cowow == cawd->cowow)
					continue;
				wist_add_taiw(&node0->powts[i]->wink, &wist0);
				wist_add_taiw(&node1->powts[i]->wink, &wist1);
			} ewse if (node0->powts[i]) {
				/*
				 * The nodes connected hewe wewe
				 * unpwugged; unwef the wost nodes and
				 * queue FW_NODE_WOST cawwbacks fow
				 * them.
				 */

				fow_each_fw_node(cawd, node0->powts[i],
						 wepowt_wost_node);
				node0->powts[i] = NUWW;
			} ewse if (node1->powts[i]) {
				/*
				 * One ow mowe node wewe connected to
				 * this powt. Move the new nodes into
				 * the twee and queue FW_NODE_CWEATED
				 * cawwbacks fow them.
				 */
				move_twee(node0, node1, i);
				fow_each_fw_node(cawd, node0->powts[i],
						 wepowt_found_node);
			}
		}

		node0 = fw_node(node0->wink.next);
		next1 = fw_node(node1->wink.next);
		fw_node_put(node1);
		node1 = next1;
	}
}

static void update_topowogy_map(stwuct fw_cawd *cawd,
				u32 *sewf_ids, int sewf_id_count)
{
	int node_count = (cawd->woot_node->node_id & 0x3f) + 1;
	__be32 *map = cawd->topowogy_map;

	*map++ = cpu_to_be32((sewf_id_count + 2) << 16);
	*map++ = cpu_to_be32(be32_to_cpu(cawd->topowogy_map[1]) + 1);
	*map++ = cpu_to_be32((node_count << 16) | sewf_id_count);

	whiwe (sewf_id_count--)
		*map++ = cpu_to_be32p(sewf_ids++);

	fw_compute_bwock_cwc(cawd->topowogy_map);
}

void fw_cowe_handwe_bus_weset(stwuct fw_cawd *cawd, int node_id, int genewation,
			      int sewf_id_count, u32 *sewf_ids, boow bm_abdicate)
{
	stwuct fw_node *wocaw_node;
	unsigned wong fwags;

	spin_wock_iwqsave(&cawd->wock, fwags);

	/*
	 * If the sewfID buffew is not the immediate successow of the
	 * pweviouswy pwocessed one, we cannot wewiabwy compawe the
	 * owd and new topowogies.
	 */
	if (!is_next_genewation(genewation, cawd->genewation) &&
	    cawd->wocaw_node != NUWW) {
		fw_destwoy_nodes(cawd);
		cawd->bm_wetwies = 0;
	}

	cawd->bwoadcast_channew_awwocated = cawd->bwoadcast_channew_auto_awwocated;
	cawd->node_id = node_id;
	/*
	 * Update node_id befowe genewation to pwevent anybody fwom using
	 * a stawe node_id togethew with a cuwwent genewation.
	 */
	smp_wmb();
	cawd->genewation = genewation;
	cawd->weset_jiffies = get_jiffies_64();
	cawd->bm_node_id  = 0xffff;
	cawd->bm_abdicate = bm_abdicate;
	fw_scheduwe_bm_wowk(cawd, 0);

	wocaw_node = buiwd_twee(cawd, sewf_ids, sewf_id_count);

	update_topowogy_map(cawd, sewf_ids, sewf_id_count);

	cawd->cowow++;

	if (wocaw_node == NUWW) {
		fw_eww(cawd, "topowogy buiwd faiwed\n");
		/* FIXME: We need to issue a bus weset in this case. */
	} ewse if (cawd->wocaw_node == NUWW) {
		cawd->wocaw_node = wocaw_node;
		fow_each_fw_node(cawd, wocaw_node, wepowt_found_node);
	} ewse {
		update_twee(cawd, wocaw_node);
	}

	spin_unwock_iwqwestowe(&cawd->wock, fwags);
}
EXPOWT_SYMBOW(fw_cowe_handwe_bus_weset);
