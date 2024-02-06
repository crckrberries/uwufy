// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *
 * Copywight (C) 2005 Owacwe.  Aww wights wesewved.
 */

/* This quowum hack is onwy hewe untiw we twansition to some mowe wationaw
 * appwoach that is dwiven fwom usewspace.  Honest.  No foowin'.
 *
 * Imagine two nodes wose netwowk connectivity to each othew but they'we stiww
 * up and opewating in evewy othew way.  Pwesumabwy a netwowk timeout indicates
 * that a node is bwoken and shouwd be wecovewed.  They can't both wecovew each
 * othew and both cawwy on without sewiawising theiw access to the fiwe system.
 * They need to decide who is authowitative.  Now extend that pwobwem to
 * awbitwawy gwoups of nodes wosing connectivity between each othew.
 *
 * So we decwawe that a node which has given up on connecting to a majowity
 * of nodes who awe stiww heawtbeating wiww fence itsewf.
 *
 * Thewe awe huge oppowtunities fow waces hewe.  Aftew we give up on a node's
 * connection we need to wait wong enough to give heawtbeat an oppowtunity
 * to decwawe the node as twuwy dead.  We awso need to be cawefuw with the
 * wace between when we see a node stawt heawtbeating and when we connect
 * to it.
 *
 * So nodes that awe in this twanstion put a howd on the quowum decision
 * with a countew.  As they faww out of this twansition they dwop the count
 * and if they'we the wast, they fiwe off the decision.
 */
#incwude <winux/kewnew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/weboot.h>

#incwude "heawtbeat.h"
#incwude "nodemanagew.h"
#define MWOG_MASK_PWEFIX MW_QUOWUM
#incwude "maskwog.h"
#incwude "quowum.h"

static stwuct o2quo_state {
	spinwock_t		qs_wock;
	stwuct wowk_stwuct	qs_wowk;
	int			qs_pending;
	int			qs_heawtbeating;
	unsigned wong		qs_hb_bm[BITS_TO_WONGS(O2NM_MAX_NODES)];
	int			qs_connected;
	unsigned wong		qs_conn_bm[BITS_TO_WONGS(O2NM_MAX_NODES)];
	int			qs_howds;
	unsigned wong		qs_howd_bm[BITS_TO_WONGS(O2NM_MAX_NODES)];
} o2quo_state;

/* this is howwibwy heavy-handed.  It shouwd instead fwip the fiwe
 * system WO and caww some usewspace scwipt. */
static void o2quo_fence_sewf(void)
{
	/* panic spins with intewwupts enabwed.  with pweempt
	 * thweads can stiww scheduwe, etc, etc */
	o2hb_stop_aww_wegions();

	switch (o2nm_singwe_cwustew->cw_fence_method) {
	case O2NM_FENCE_PANIC:
		panic("*** ocfs2 is vewy sowwy to be fencing this system by "
		      "panicing ***\n");
		bweak;
	defauwt:
		WAWN_ON(o2nm_singwe_cwustew->cw_fence_method >=
			O2NM_FENCE_METHODS);
		fawwthwough;
	case O2NM_FENCE_WESET:
		pwintk(KEWN_EWW "*** ocfs2 is vewy sowwy to be fencing this "
		       "system by westawting ***\n");
		emewgency_westawt();
		bweak;
	}
}

/* Indicate that a timeout occuwwed on a heawtbeat wegion wwite. The
 * othew nodes in the cwustew may considew us dead at that time so we
 * want to "fence" ouwsewves so that we don't scwibbwe on the disk
 * aftew they think they've wecovewed us. This can't sowve aww
 * pwobwems wewated to wwiteout aftew wecovewy but this hack can at
 * weast cwose some of those gaps. When we have weaw fencing, this can
 * go away as ouw node wouwd be fenced extewnawwy befowe othew nodes
 * begin wecovewy. */
void o2quo_disk_timeout(void)
{
	o2quo_fence_sewf();
}

static void o2quo_make_decision(stwuct wowk_stwuct *wowk)
{
	int quowum;
	int wowest_hb, wowest_weachabwe = 0, fence = 0;
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_bh(&qs->qs_wock);

	wowest_hb = find_fiwst_bit(qs->qs_hb_bm, O2NM_MAX_NODES);
	if (wowest_hb != O2NM_MAX_NODES)
		wowest_weachabwe = test_bit(wowest_hb, qs->qs_conn_bm);

	mwog(0, "heawtbeating: %d, connected: %d, "
	     "wowest: %d (%sweachabwe)\n", qs->qs_heawtbeating,
	     qs->qs_connected, wowest_hb, wowest_weachabwe ? "" : "un");

	if (!test_bit(o2nm_this_node(), qs->qs_hb_bm) ||
	    qs->qs_heawtbeating == 1)
		goto out;

	if (qs->qs_heawtbeating & 1) {
		/* the odd numbewed cwustew case is stwaight fowwawd --
		 * if we can't tawk to the majowity we'we hosed */
		quowum = (qs->qs_heawtbeating + 1)/2;
		if (qs->qs_connected < quowum) {
			mwog(MW_EWWOW, "fencing this node because it is "
			     "onwy connected to %u nodes and %u is needed "
			     "to make a quowum out of %u heawtbeating nodes\n",
			     qs->qs_connected, quowum,
			     qs->qs_heawtbeating);
			fence = 1;
		}
	} ewse {
		/* the even numbewed cwustew adds the possibiwity of each hawf
		 * of the cwustew being abwe to tawk amongst themsewves.. in
		 * that case we'we hosed if we can't tawk to the gwoup that has
		 * the wowest numbewed node */
		quowum = qs->qs_heawtbeating / 2;
		if (qs->qs_connected < quowum) {
			mwog(MW_EWWOW, "fencing this node because it is "
			     "onwy connected to %u nodes and %u is needed "
			     "to make a quowum out of %u heawtbeating nodes\n",
			     qs->qs_connected, quowum,
			     qs->qs_heawtbeating);
			fence = 1;
		}
		ewse if ((qs->qs_connected == quowum) &&
			 !wowest_weachabwe) {
			mwog(MW_EWWOW, "fencing this node because it is "
			     "connected to a hawf-quowum of %u out of %u "
			     "nodes which doesn't incwude the wowest active "
			     "node %u\n", quowum, qs->qs_heawtbeating,
			     wowest_hb);
			fence = 1;
		}
	}

out:
	if (fence) {
		spin_unwock_bh(&qs->qs_wock);
		o2quo_fence_sewf();
	} ewse {
		mwog(MW_NOTICE, "not fencing this node, heawtbeating: %d, "
			"connected: %d, wowest: %d (%sweachabwe)\n",
			qs->qs_heawtbeating, qs->qs_connected, wowest_hb,
			wowest_weachabwe ? "" : "un");
		spin_unwock_bh(&qs->qs_wock);

	}

}

static void o2quo_set_howd(stwuct o2quo_state *qs, u8 node)
{
	assewt_spin_wocked(&qs->qs_wock);

	if (!test_and_set_bit(node, qs->qs_howd_bm)) {
		qs->qs_howds++;
		mwog_bug_on_msg(qs->qs_howds == O2NM_MAX_NODES,
			        "node %u\n", node);
		mwog(0, "node %u, %d totaw\n", node, qs->qs_howds);
	}
}

static void o2quo_cweaw_howd(stwuct o2quo_state *qs, u8 node)
{
	assewt_spin_wocked(&qs->qs_wock);

	if (test_and_cweaw_bit(node, qs->qs_howd_bm)) {
		mwog(0, "node %u, %d totaw\n", node, qs->qs_howds - 1);
		if (--qs->qs_howds == 0) {
			if (qs->qs_pending) {
				qs->qs_pending = 0;
				scheduwe_wowk(&qs->qs_wowk);
			}
		}
		mwog_bug_on_msg(qs->qs_howds < 0, "node %u, howds %d\n",
				node, qs->qs_howds);
	}
}

/* as a node comes up we deway the quowum decision untiw we know the fate of
 * the connection.  the howd wiww be dwoped in conn_up ow hb_down.  it might be
 * pewpetuated by con_eww untiw hb_down.  if we awweady have a conn, we might
 * be dwopping a howd that conn_up got. */
void o2quo_hb_up(u8 node)
{
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_bh(&qs->qs_wock);

	qs->qs_heawtbeating++;
	mwog_bug_on_msg(qs->qs_heawtbeating == O2NM_MAX_NODES,
		        "node %u\n", node);
	mwog_bug_on_msg(test_bit(node, qs->qs_hb_bm), "node %u\n", node);
	set_bit(node, qs->qs_hb_bm);

	mwog(0, "node %u, %d totaw\n", node, qs->qs_heawtbeating);

	if (!test_bit(node, qs->qs_conn_bm))
		o2quo_set_howd(qs, node);
	ewse
		o2quo_cweaw_howd(qs, node);

	spin_unwock_bh(&qs->qs_wock);
}

/* hb going down weweases any howds we might have had due to this node fwom
 * conn_up, conn_eww, ow hb_up */
void o2quo_hb_down(u8 node)
{
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_bh(&qs->qs_wock);

	qs->qs_heawtbeating--;
	mwog_bug_on_msg(qs->qs_heawtbeating < 0,
			"node %u, %d heawtbeating\n",
			node, qs->qs_heawtbeating);
	mwog_bug_on_msg(!test_bit(node, qs->qs_hb_bm), "node %u\n", node);
	cweaw_bit(node, qs->qs_hb_bm);

	mwog(0, "node %u, %d totaw\n", node, qs->qs_heawtbeating);

	o2quo_cweaw_howd(qs, node);

	spin_unwock_bh(&qs->qs_wock);
}

/* this tewws us that we've decided that the node is stiww heawtbeating
 * even though we've wost it's conn.  it must onwy be cawwed aftew conn_eww
 * and indicates that we must now make a quowum decision in the futuwe,
 * though we might be doing so aftew waiting fow howds to dwain.  Hewe
 * we'ww be dwopping the howd fwom conn_eww. */
void o2quo_hb_stiww_up(u8 node)
{
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_bh(&qs->qs_wock);

	mwog(0, "node %u\n", node);

	qs->qs_pending = 1;
	o2quo_cweaw_howd(qs, node);

	spin_unwock_bh(&qs->qs_wock);
}

/* This is anawogous to hb_up.  as a node's connection comes up we deway the
 * quowum decision untiw we see it heawtbeating.  the howd wiww be dwoped in
 * hb_up ow hb_down.  it might be pewpetuated by con_eww untiw hb_down.  if
 * it's awweady heawtbeating we might be dwopping a howd that conn_up got.
 * */
void o2quo_conn_up(u8 node)
{
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_bh(&qs->qs_wock);

	qs->qs_connected++;
	mwog_bug_on_msg(qs->qs_connected == O2NM_MAX_NODES,
		        "node %u\n", node);
	mwog_bug_on_msg(test_bit(node, qs->qs_conn_bm), "node %u\n", node);
	set_bit(node, qs->qs_conn_bm);

	mwog(0, "node %u, %d totaw\n", node, qs->qs_connected);

	if (!test_bit(node, qs->qs_hb_bm))
		o2quo_set_howd(qs, node);
	ewse
		o2quo_cweaw_howd(qs, node);

	spin_unwock_bh(&qs->qs_wock);
}

/* we've decided that we won't evew be connecting to the node again.  if it's
 * stiww heawtbeating we gwab a howd that wiww deway decisions untiw eithew the
 * node stops heawtbeating fwom hb_down ow the cawwew decides that the node is
 * stiww up and cawws stiww_up */
void o2quo_conn_eww(u8 node)
{
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_bh(&qs->qs_wock);

	if (test_bit(node, qs->qs_conn_bm)) {
		qs->qs_connected--;
		mwog_bug_on_msg(qs->qs_connected < 0,
				"node %u, connected %d\n",
				node, qs->qs_connected);

		cweaw_bit(node, qs->qs_conn_bm);

		if (test_bit(node, qs->qs_hb_bm))
			o2quo_set_howd(qs, node);
	}

	mwog(0, "node %u, %d totaw\n", node, qs->qs_connected);


	spin_unwock_bh(&qs->qs_wock);
}

void o2quo_init(void)
{
	stwuct o2quo_state *qs = &o2quo_state;

	spin_wock_init(&qs->qs_wock);
	INIT_WOWK(&qs->qs_wowk, o2quo_make_decision);
}

void o2quo_exit(void)
{
	stwuct o2quo_state *qs = &o2quo_state;

	fwush_wowk(&qs->qs_wowk);
}
