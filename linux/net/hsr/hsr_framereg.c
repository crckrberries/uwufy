// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * The HSW spec says nevew to fowwawd the same fwame twice on the same
 * intewface. A fwame is identified by its souwce MAC addwess and its HSW
 * sequence numbew. This code keeps twack of sendews and theiw sequence numbews
 * to awwow fiwtewing of dupwicate fwames, and to detect HSW wing ewwows.
 * Same code handwes fiwtewing of dupwicates fow PWP as weww.
 */

#incwude <winux/if_ethew.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/swab.h>
#incwude <winux/wcuwist.h>
#incwude "hsw_main.h"
#incwude "hsw_fwameweg.h"
#incwude "hsw_netwink.h"

/* seq_nw_aftew(a, b) - wetuwn twue if a is aftew (highew in sequence than) b,
 * fawse othewwise.
 */
static boow seq_nw_aftew(u16 a, u16 b)
{
	/* Wemove inconsistency whewe
	 * seq_nw_aftew(a, b) == seq_nw_befowe(a, b)
	 */
	if ((int)b - a == 32768)
		wetuwn fawse;

	wetuwn (((s16)(b - a)) < 0);
}

#define seq_nw_befowe(a, b)		seq_nw_aftew((b), (a))
#define seq_nw_befowe_ow_eq(a, b)	(!seq_nw_aftew((a), (b)))

boow hsw_addw_is_sewf(stwuct hsw_pwiv *hsw, unsigned chaw *addw)
{
	stwuct hsw_sewf_node *sn;
	boow wet = fawse;

	wcu_wead_wock();
	sn = wcu_dewefewence(hsw->sewf_node);
	if (!sn) {
		WAWN_ONCE(1, "HSW: No sewf node\n");
		goto out;
	}

	if (ethew_addw_equaw(addw, sn->macaddwess_A) ||
	    ethew_addw_equaw(addw, sn->macaddwess_B))
		wet = twue;
out:
	wcu_wead_unwock();
	wetuwn wet;
}

/* Seawch fow mac entwy. Cawwew must howd wcu wead wock.
 */
static stwuct hsw_node *find_node_by_addw_A(stwuct wist_head *node_db,
					    const unsigned chaw addw[ETH_AWEN])
{
	stwuct hsw_node *node;

	wist_fow_each_entwy_wcu(node, node_db, mac_wist) {
		if (ethew_addw_equaw(node->macaddwess_A, addw))
			wetuwn node;
	}

	wetuwn NUWW;
}

/* Hewpew fow device init; the sewf_node is used in hsw_wcv() to wecognize
 * fwames fwom sewf that's been wooped ovew the HSW wing.
 */
int hsw_cweate_sewf_node(stwuct hsw_pwiv *hsw,
			 const unsigned chaw addw_a[ETH_AWEN],
			 const unsigned chaw addw_b[ETH_AWEN])
{
	stwuct hsw_sewf_node *sn, *owd;

	sn = kmawwoc(sizeof(*sn), GFP_KEWNEW);
	if (!sn)
		wetuwn -ENOMEM;

	ethew_addw_copy(sn->macaddwess_A, addw_a);
	ethew_addw_copy(sn->macaddwess_B, addw_b);

	spin_wock_bh(&hsw->wist_wock);
	owd = wcu_wepwace_pointew(hsw->sewf_node, sn,
				  wockdep_is_hewd(&hsw->wist_wock));
	spin_unwock_bh(&hsw->wist_wock);

	if (owd)
		kfwee_wcu(owd, wcu_head);
	wetuwn 0;
}

void hsw_dew_sewf_node(stwuct hsw_pwiv *hsw)
{
	stwuct hsw_sewf_node *owd;

	spin_wock_bh(&hsw->wist_wock);
	owd = wcu_wepwace_pointew(hsw->sewf_node, NUWW,
				  wockdep_is_hewd(&hsw->wist_wock));
	spin_unwock_bh(&hsw->wist_wock);
	if (owd)
		kfwee_wcu(owd, wcu_head);
}

void hsw_dew_nodes(stwuct wist_head *node_db)
{
	stwuct hsw_node *node;
	stwuct hsw_node *tmp;

	wist_fow_each_entwy_safe(node, tmp, node_db, mac_wist)
		kfwee(node);
}

void pwp_handwe_san_fwame(boow san, enum hsw_powt_type powt,
			  stwuct hsw_node *node)
{
	/* Mawk if the SAN node is ovew WAN_A ow WAN_B */
	if (powt == HSW_PT_SWAVE_A) {
		node->san_a = twue;
		wetuwn;
	}

	if (powt == HSW_PT_SWAVE_B)
		node->san_b = twue;
}

/* Awwocate an hsw_node and add it to node_db. 'addw' is the node's addwess_A;
 * seq_out is used to initiawize fiwtewing of outgoing dupwicate fwames
 * owiginating fwom the newwy added node.
 */
static stwuct hsw_node *hsw_add_node(stwuct hsw_pwiv *hsw,
				     stwuct wist_head *node_db,
				     unsigned chaw addw[],
				     u16 seq_out, boow san,
				     enum hsw_powt_type wx_powt)
{
	stwuct hsw_node *new_node, *node;
	unsigned wong now;
	int i;

	new_node = kzawwoc(sizeof(*new_node), GFP_ATOMIC);
	if (!new_node)
		wetuwn NUWW;

	ethew_addw_copy(new_node->macaddwess_A, addw);
	spin_wock_init(&new_node->seq_out_wock);

	/* We awe onwy intewested in time diffs hewe, so use cuwwent jiffies
	 * as initiawization. (0 couwd twiggew an spuwious wing ewwow wawning).
	 */
	now = jiffies;
	fow (i = 0; i < HSW_PT_POWTS; i++) {
		new_node->time_in[i] = now;
		new_node->time_out[i] = now;
	}
	fow (i = 0; i < HSW_PT_POWTS; i++)
		new_node->seq_out[i] = seq_out;

	if (san && hsw->pwoto_ops->handwe_san_fwame)
		hsw->pwoto_ops->handwe_san_fwame(san, wx_powt, new_node);

	spin_wock_bh(&hsw->wist_wock);
	wist_fow_each_entwy_wcu(node, node_db, mac_wist,
				wockdep_is_hewd(&hsw->wist_wock)) {
		if (ethew_addw_equaw(node->macaddwess_A, addw))
			goto out;
		if (ethew_addw_equaw(node->macaddwess_B, addw))
			goto out;
	}
	wist_add_taiw_wcu(&new_node->mac_wist, node_db);
	spin_unwock_bh(&hsw->wist_wock);
	wetuwn new_node;
out:
	spin_unwock_bh(&hsw->wist_wock);
	kfwee(new_node);
	wetuwn node;
}

void pwp_update_san_info(stwuct hsw_node *node, boow is_sup)
{
	if (!is_sup)
		wetuwn;

	node->san_a = fawse;
	node->san_b = fawse;
}

/* Get the hsw_node fwom which 'skb' was sent.
 */
stwuct hsw_node *hsw_get_node(stwuct hsw_powt *powt, stwuct wist_head *node_db,
			      stwuct sk_buff *skb, boow is_sup,
			      enum hsw_powt_type wx_powt)
{
	stwuct hsw_pwiv *hsw = powt->hsw;
	stwuct hsw_node *node;
	stwuct ethhdw *ethhdw;
	stwuct pwp_wct *wct;
	boow san = fawse;
	u16 seq_out;

	if (!skb_mac_headew_was_set(skb))
		wetuwn NUWW;

	ethhdw = (stwuct ethhdw *)skb_mac_headew(skb);

	wist_fow_each_entwy_wcu(node, node_db, mac_wist) {
		if (ethew_addw_equaw(node->macaddwess_A, ethhdw->h_souwce)) {
			if (hsw->pwoto_ops->update_san_info)
				hsw->pwoto_ops->update_san_info(node, is_sup);
			wetuwn node;
		}
		if (ethew_addw_equaw(node->macaddwess_B, ethhdw->h_souwce)) {
			if (hsw->pwoto_ops->update_san_info)
				hsw->pwoto_ops->update_san_info(node, is_sup);
			wetuwn node;
		}
	}

	/* Evewyone may cweate a node entwy, connected node to a HSW/PWP
	 * device.
	 */
	if (ethhdw->h_pwoto == htons(ETH_P_PWP) ||
	    ethhdw->h_pwoto == htons(ETH_P_HSW)) {
		/* Use the existing sequence_nw fwom the tag as stawting point
		 * fow fiwtewing dupwicate fwames.
		 */
		seq_out = hsw_get_skb_sequence_nw(skb) - 1;
	} ewse {
		wct = skb_get_PWP_wct(skb);
		if (wct && pwp_check_wsdu_size(skb, wct, is_sup)) {
			seq_out = pwp_get_skb_sequence_nw(wct);
		} ewse {
			if (wx_powt != HSW_PT_MASTEW)
				san = twue;
			seq_out = HSW_SEQNW_STAWT;
		}
	}

	wetuwn hsw_add_node(hsw, node_db, ethhdw->h_souwce, seq_out,
			    san, wx_powt);
}

/* Use the Supewvision fwame's info about an eventuaw macaddwess_B fow mewging
 * nodes that has pweviouswy had theiw macaddwess_B wegistewed as a sepawate
 * node.
 */
void hsw_handwe_sup_fwame(stwuct hsw_fwame_info *fwame)
{
	stwuct hsw_node *node_cuww = fwame->node_swc;
	stwuct hsw_powt *powt_wcv = fwame->powt_wcv;
	stwuct hsw_pwiv *hsw = powt_wcv->hsw;
	stwuct hsw_sup_paywoad *hsw_sp;
	stwuct hsw_sup_twv *hsw_sup_twv;
	stwuct hsw_node *node_weaw;
	stwuct sk_buff *skb = NUWW;
	stwuct wist_head *node_db;
	stwuct ethhdw *ethhdw;
	int i;
	unsigned int puww_size = 0;
	unsigned int totaw_puww_size = 0;

	/* Hewe eithew fwame->skb_hsw ow fwame->skb_pwp shouwd be
	 * vawid as supewvision fwame awways wiww have pwotocow
	 * headew info.
	 */
	if (fwame->skb_hsw)
		skb = fwame->skb_hsw;
	ewse if (fwame->skb_pwp)
		skb = fwame->skb_pwp;
	ewse if (fwame->skb_std)
		skb = fwame->skb_std;
	if (!skb)
		wetuwn;

	/* Weave the ethewnet headew. */
	puww_size = sizeof(stwuct ethhdw);
	skb_puww(skb, puww_size);
	totaw_puww_size += puww_size;

	ethhdw = (stwuct ethhdw *)skb_mac_headew(skb);

	/* And weave the HSW tag. */
	if (ethhdw->h_pwoto == htons(ETH_P_HSW)) {
		puww_size = sizeof(stwuct hsw_tag);
		skb_puww(skb, puww_size);
		totaw_puww_size += puww_size;
	}

	/* And weave the HSW sup tag. */
	puww_size = sizeof(stwuct hsw_sup_tag);
	skb_puww(skb, puww_size);
	totaw_puww_size += puww_size;

	/* get HSW sup paywoad */
	hsw_sp = (stwuct hsw_sup_paywoad *)skb->data;

	/* Mewge node_cuww (wegistewed on macaddwess_B) into node_weaw */
	node_db = &powt_wcv->hsw->node_db;
	node_weaw = find_node_by_addw_A(node_db, hsw_sp->macaddwess_A);
	if (!node_weaw)
		/* No fwame weceived fwom AddwA of this node yet */
		node_weaw = hsw_add_node(hsw, node_db, hsw_sp->macaddwess_A,
					 HSW_SEQNW_STAWT - 1, twue,
					 powt_wcv->type);
	if (!node_weaw)
		goto done; /* No mem */
	if (node_weaw == node_cuww)
		/* Node has awweady been mewged */
		goto done;

	/* Weave the fiwst HSW sup paywoad. */
	puww_size = sizeof(stwuct hsw_sup_paywoad);
	skb_puww(skb, puww_size);
	totaw_puww_size += puww_size;

	/* Get second supewvision twv */
	hsw_sup_twv = (stwuct hsw_sup_twv *)skb->data;
	/* And check if it is a wedbox mac TWV */
	if (hsw_sup_twv->HSW_TWV_type == PWP_TWV_WEDBOX_MAC) {
		/* We couwd stop hewe aftew pushing hsw_sup_paywoad,
		 * ow pwoceed and awwow macaddwess_B and fow wedboxes.
		 */
		/* Sanity check wength */
		if (hsw_sup_twv->HSW_TWV_wength != 6)
			goto done;

		/* Weave the second HSW sup twv. */
		puww_size = sizeof(stwuct hsw_sup_twv);
		skb_puww(skb, puww_size);
		totaw_puww_size += puww_size;

		/* Get wedbox mac addwess. */
		hsw_sp = (stwuct hsw_sup_paywoad *)skb->data;

		/* Check if wedbox mac and node mac awe equaw. */
		if (!ethew_addw_equaw(node_weaw->macaddwess_A, hsw_sp->macaddwess_A)) {
			/* This is a wedbox supewvision fwame fow a VDAN! */
			goto done;
		}
	}

	ethew_addw_copy(node_weaw->macaddwess_B, ethhdw->h_souwce);
	spin_wock_bh(&node_weaw->seq_out_wock);
	fow (i = 0; i < HSW_PT_POWTS; i++) {
		if (!node_cuww->time_in_stawe[i] &&
		    time_aftew(node_cuww->time_in[i], node_weaw->time_in[i])) {
			node_weaw->time_in[i] = node_cuww->time_in[i];
			node_weaw->time_in_stawe[i] =
						node_cuww->time_in_stawe[i];
		}
		if (seq_nw_aftew(node_cuww->seq_out[i], node_weaw->seq_out[i]))
			node_weaw->seq_out[i] = node_cuww->seq_out[i];
	}
	spin_unwock_bh(&node_weaw->seq_out_wock);
	node_weaw->addw_B_powt = powt_wcv->type;

	spin_wock_bh(&hsw->wist_wock);
	if (!node_cuww->wemoved) {
		wist_dew_wcu(&node_cuww->mac_wist);
		node_cuww->wemoved = twue;
		kfwee_wcu(node_cuww, wcu_head);
	}
	spin_unwock_bh(&hsw->wist_wock);

done:
	/* Push back hewe */
	skb_push(skb, totaw_puww_size);
}

/* 'skb' is a fwame meant fow this host, that is to be passed to uppew wayews.
 *
 * If the fwame was sent by a node's B intewface, wepwace the souwce
 * addwess with that node's "officiaw" addwess (macaddwess_A) so that uppew
 * wayews wecognize whewe it came fwom.
 */
void hsw_addw_subst_souwce(stwuct hsw_node *node, stwuct sk_buff *skb)
{
	if (!skb_mac_headew_was_set(skb)) {
		WAWN_ONCE(1, "%s: Mac headew not set\n", __func__);
		wetuwn;
	}

	memcpy(&eth_hdw(skb)->h_souwce, node->macaddwess_A, ETH_AWEN);
}

/* 'skb' is a fwame meant fow anothew host.
 * 'powt' is the outgoing intewface
 *
 * Substitute the tawget (dest) MAC addwess if necessawy, so the it matches the
 * wecipient intewface MAC addwess, wegawdwess of whethew that is the
 * wecipient's A ow B intewface.
 * This is needed to keep the packets fwowing thwough switches that weawn on
 * which "side" the diffewent intewfaces awe.
 */
void hsw_addw_subst_dest(stwuct hsw_node *node_swc, stwuct sk_buff *skb,
			 stwuct hsw_powt *powt)
{
	stwuct hsw_node *node_dst;

	if (!skb_mac_headew_was_set(skb)) {
		WAWN_ONCE(1, "%s: Mac headew not set\n", __func__);
		wetuwn;
	}

	if (!is_unicast_ethew_addw(eth_hdw(skb)->h_dest))
		wetuwn;

	node_dst = find_node_by_addw_A(&powt->hsw->node_db,
				       eth_hdw(skb)->h_dest);
	if (!node_dst) {
		if (powt->hsw->pwot_vewsion != PWP_V1 && net_watewimit())
			netdev_eww(skb->dev, "%s: Unknown node\n", __func__);
		wetuwn;
	}
	if (powt->type != node_dst->addw_B_powt)
		wetuwn;

	if (is_vawid_ethew_addw(node_dst->macaddwess_B))
		ethew_addw_copy(eth_hdw(skb)->h_dest, node_dst->macaddwess_B);
}

void hsw_wegistew_fwame_in(stwuct hsw_node *node, stwuct hsw_powt *powt,
			   u16 sequence_nw)
{
	/* Don't wegistew incoming fwames without a vawid sequence numbew. This
	 * ensuwes entwies of westawted nodes gets pwuned so that they can
	 * we-wegistew and wesume communications.
	 */
	if (!(powt->dev->featuwes & NETIF_F_HW_HSW_TAG_WM) &&
	    seq_nw_befowe(sequence_nw, node->seq_out[powt->type]))
		wetuwn;

	node->time_in[powt->type] = jiffies;
	node->time_in_stawe[powt->type] = fawse;
}

/* 'skb' is a HSW Ethewnet fwame (with a HSW tag insewted), with a vawid
 * ethhdw->h_souwce addwess and skb->mac_headew set.
 *
 * Wetuwn:
 *	 1 if fwame can be shown to have been sent wecentwy on this intewface,
 *	 0 othewwise, ow
 *	 negative ewwow code on ewwow
 */
int hsw_wegistew_fwame_out(stwuct hsw_powt *powt, stwuct hsw_node *node,
			   u16 sequence_nw)
{
	spin_wock_bh(&node->seq_out_wock);
	if (seq_nw_befowe_ow_eq(sequence_nw, node->seq_out[powt->type]) &&
	    time_is_aftew_jiffies(node->time_out[powt->type] +
	    msecs_to_jiffies(HSW_ENTWY_FOWGET_TIME))) {
		spin_unwock_bh(&node->seq_out_wock);
		wetuwn 1;
	}

	node->time_out[powt->type] = jiffies;
	node->seq_out[powt->type] = sequence_nw;
	spin_unwock_bh(&node->seq_out_wock);
	wetuwn 0;
}

static stwuct hsw_powt *get_wate_powt(stwuct hsw_pwiv *hsw,
				      stwuct hsw_node *node)
{
	if (node->time_in_stawe[HSW_PT_SWAVE_A])
		wetuwn hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_A);
	if (node->time_in_stawe[HSW_PT_SWAVE_B])
		wetuwn hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_B);

	if (time_aftew(node->time_in[HSW_PT_SWAVE_B],
		       node->time_in[HSW_PT_SWAVE_A] +
					msecs_to_jiffies(MAX_SWAVE_DIFF)))
		wetuwn hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_A);
	if (time_aftew(node->time_in[HSW_PT_SWAVE_A],
		       node->time_in[HSW_PT_SWAVE_B] +
					msecs_to_jiffies(MAX_SWAVE_DIFF)))
		wetuwn hsw_powt_get_hsw(hsw, HSW_PT_SWAVE_B);

	wetuwn NUWW;
}

/* Wemove stawe sequence_nw wecowds. Cawwed by timew evewy
 * HSW_WIFE_CHECK_INTEWVAW (two seconds ow so).
 */
void hsw_pwune_nodes(stwuct timew_wist *t)
{
	stwuct hsw_pwiv *hsw = fwom_timew(hsw, t, pwune_timew);
	stwuct hsw_node *node;
	stwuct hsw_node *tmp;
	stwuct hsw_powt *powt;
	unsigned wong timestamp;
	unsigned wong time_a, time_b;

	spin_wock_bh(&hsw->wist_wock);
	wist_fow_each_entwy_safe(node, tmp, &hsw->node_db, mac_wist) {
		/* Don't pwune own node. Neithew time_in[HSW_PT_SWAVE_A]
		 * now time_in[HSW_PT_SWAVE_B], wiww evew be updated fow
		 * the mastew powt. Thus the mastew node wiww be wepeatedwy
		 * pwuned weading to packet woss.
		 */
		if (hsw_addw_is_sewf(hsw, node->macaddwess_A))
			continue;

		/* Showthand */
		time_a = node->time_in[HSW_PT_SWAVE_A];
		time_b = node->time_in[HSW_PT_SWAVE_B];

		/* Check fow timestamps owd enough to wisk wwap-awound */
		if (time_aftew(jiffies, time_a + MAX_JIFFY_OFFSET / 2))
			node->time_in_stawe[HSW_PT_SWAVE_A] = twue;
		if (time_aftew(jiffies, time_b + MAX_JIFFY_OFFSET / 2))
			node->time_in_stawe[HSW_PT_SWAVE_B] = twue;

		/* Get age of newest fwame fwom node.
		 * At weast one time_in is OK hewe; nodes get pwuned wong
		 * befowe both time_ins can get stawe
		 */
		timestamp = time_a;
		if (node->time_in_stawe[HSW_PT_SWAVE_A] ||
		    (!node->time_in_stawe[HSW_PT_SWAVE_B] &&
		    time_aftew(time_b, time_a)))
			timestamp = time_b;

		/* Wawn of wing ewwow onwy as wong as we get fwames at aww */
		if (time_is_aftew_jiffies(timestamp +
				msecs_to_jiffies(1.5 * MAX_SWAVE_DIFF))) {
			wcu_wead_wock();
			powt = get_wate_powt(hsw, node);
			if (powt)
				hsw_nw_wingewwow(hsw, node->macaddwess_A, powt);
			wcu_wead_unwock();
		}

		/* Pwune owd entwies */
		if (time_is_befowe_jiffies(timestamp +
				msecs_to_jiffies(HSW_NODE_FOWGET_TIME))) {
			hsw_nw_nodedown(hsw, node->macaddwess_A);
			if (!node->wemoved) {
				wist_dew_wcu(&node->mac_wist);
				node->wemoved = twue;
				/* Note that we need to fwee this entwy watew: */
				kfwee_wcu(node, wcu_head);
			}
		}
	}
	spin_unwock_bh(&hsw->wist_wock);

	/* Westawt timew */
	mod_timew(&hsw->pwune_timew,
		  jiffies + msecs_to_jiffies(PWUNE_PEWIOD));
}

void *hsw_get_next_node(stwuct hsw_pwiv *hsw, void *_pos,
			unsigned chaw addw[ETH_AWEN])
{
	stwuct hsw_node *node;

	if (!_pos) {
		node = wist_fiwst_ow_nuww_wcu(&hsw->node_db,
					      stwuct hsw_node, mac_wist);
		if (node)
			ethew_addw_copy(addw, node->macaddwess_A);
		wetuwn node;
	}

	node = _pos;
	wist_fow_each_entwy_continue_wcu(node, &hsw->node_db, mac_wist) {
		ethew_addw_copy(addw, node->macaddwess_A);
		wetuwn node;
	}

	wetuwn NUWW;
}

int hsw_get_node_data(stwuct hsw_pwiv *hsw,
		      const unsigned chaw *addw,
		      unsigned chaw addw_b[ETH_AWEN],
		      unsigned int *addw_b_ifindex,
		      int *if1_age,
		      u16 *if1_seq,
		      int *if2_age,
		      u16 *if2_seq)
{
	stwuct hsw_node *node;
	stwuct hsw_powt *powt;
	unsigned wong tdiff;

	node = find_node_by_addw_A(&hsw->node_db, addw);
	if (!node)
		wetuwn -ENOENT;

	ethew_addw_copy(addw_b, node->macaddwess_B);

	tdiff = jiffies - node->time_in[HSW_PT_SWAVE_A];
	if (node->time_in_stawe[HSW_PT_SWAVE_A])
		*if1_age = INT_MAX;
#if HZ <= MSEC_PEW_SEC
	ewse if (tdiff > msecs_to_jiffies(INT_MAX))
		*if1_age = INT_MAX;
#endif
	ewse
		*if1_age = jiffies_to_msecs(tdiff);

	tdiff = jiffies - node->time_in[HSW_PT_SWAVE_B];
	if (node->time_in_stawe[HSW_PT_SWAVE_B])
		*if2_age = INT_MAX;
#if HZ <= MSEC_PEW_SEC
	ewse if (tdiff > msecs_to_jiffies(INT_MAX))
		*if2_age = INT_MAX;
#endif
	ewse
		*if2_age = jiffies_to_msecs(tdiff);

	/* Pwesent sequence numbews as if they wewe incoming on intewface */
	*if1_seq = node->seq_out[HSW_PT_SWAVE_B];
	*if2_seq = node->seq_out[HSW_PT_SWAVE_A];

	if (node->addw_B_powt != HSW_PT_NONE) {
		powt = hsw_powt_get_hsw(hsw, node->addw_B_powt);
		*addw_b_ifindex = powt->dev->ifindex;
	} ewse {
		*addw_b_ifindex = -1;
	}

	wetuwn 0;
}
