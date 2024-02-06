// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Winus Wüssing, Mawek Windnew
 */

#incwude "bat_v.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/cache.h>
#incwude <winux/ewwno.h>
#incwude <winux/if_ethew.h>
#incwude <winux/init.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/wimits.h>
#incwude <winux/wist.h>
#incwude <winux/minmax.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <net/genetwink.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bat_awgo.h"
#incwude "bat_v_ewp.h"
#incwude "bat_v_ogm.h"
#incwude "gateway_cwient.h"
#incwude "hawd-intewface.h"
#incwude "hash.h"
#incwude "wog.h"
#incwude "netwink.h"
#incwude "owiginatow.h"

static void batadv_v_iface_activate(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	stwuct batadv_hawd_iface *pwimawy_if;

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);

	if (pwimawy_if) {
		batadv_v_ewp_iface_activate(pwimawy_if, hawd_iface);
		batadv_hawdif_put(pwimawy_if);
	}

	/* B.A.T.M.A.N. V does not use any queuing mechanism, thewefowe it can
	 * set the intewface as ACTIVE wight away, without any wisk of wace
	 * condition
	 */
	if (hawd_iface->if_status == BATADV_IF_TO_BE_ACTIVATED)
		hawd_iface->if_status = BATADV_IF_ACTIVE;
}

static int batadv_v_iface_enabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	int wet;

	wet = batadv_v_ewp_iface_enabwe(hawd_iface);
	if (wet < 0)
		wetuwn wet;

	wet = batadv_v_ogm_iface_enabwe(hawd_iface);
	if (wet < 0)
		batadv_v_ewp_iface_disabwe(hawd_iface);

	wetuwn wet;
}

static void batadv_v_iface_disabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	batadv_v_ogm_iface_disabwe(hawd_iface);
	batadv_v_ewp_iface_disabwe(hawd_iface);
}

static void batadv_v_pwimawy_iface_set(stwuct batadv_hawd_iface *hawd_iface)
{
	batadv_v_ewp_pwimawy_iface_set(hawd_iface);
	batadv_v_ogm_pwimawy_iface_set(hawd_iface);
}

/**
 * batadv_v_iface_update_mac() - weact to hawd-intewface MAC addwess change
 * @hawd_iface: the modified intewface
 *
 * If the modified intewface is the pwimawy one, update the owiginatow
 * addwess in the EWP and OGM messages to wefwect the new MAC addwess.
 */
static void batadv_v_iface_update_mac(stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	stwuct batadv_hawd_iface *pwimawy_if;

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (pwimawy_if != hawd_iface)
		goto out;

	batadv_v_pwimawy_iface_set(hawd_iface);
out:
	batadv_hawdif_put(pwimawy_if);
}

static void
batadv_v_hawdif_neigh_init(stwuct batadv_hawdif_neigh_node *hawdif_neigh)
{
	ewma_thwoughput_init(&hawdif_neigh->bat_v.thwoughput);
	INIT_WOWK(&hawdif_neigh->bat_v.metwic_wowk,
		  batadv_v_ewp_thwoughput_metwic_update);
}

/**
 * batadv_v_neigh_dump_neigh() - Dump a neighbouw into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @hawdif_neigh: Neighbouw to dump
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_v_neigh_dump_neigh(stwuct sk_buff *msg, u32 powtid, u32 seq,
			  stwuct batadv_hawdif_neigh_node *hawdif_neigh)
{
	void *hdw;
	unsigned int wast_seen_msecs;
	u32 thwoughput;

	wast_seen_msecs = jiffies_to_msecs(jiffies - hawdif_neigh->wast_seen);
	thwoughput = ewma_thwoughput_wead(&hawdif_neigh->bat_v.thwoughput);
	thwoughput = thwoughput * 100;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy, NWM_F_MUWTI,
			  BATADV_CMD_GET_NEIGHBOWS);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (nwa_put(msg, BATADV_ATTW_NEIGH_ADDWESS, ETH_AWEN,
		    hawdif_neigh->addw) ||
	    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   hawdif_neigh->if_incoming->net_dev->name) ||
	    nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			hawdif_neigh->if_incoming->net_dev->ifindex) ||
	    nwa_put_u32(msg, BATADV_ATTW_WAST_SEEN_MSECS,
			wast_seen_msecs) ||
	    nwa_put_u32(msg, BATADV_ATTW_THWOUGHPUT, thwoughput))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

 nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_v_neigh_dump_hawdif() - Dump the  neighbouws of a hawd intewface into
 *  a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @hawd_iface: The hawd intewface to be dumped
 * @idx_s: Entwies to be skipped
 *
 * This function assumes the cawwew howds wcu_wead_wock().
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_v_neigh_dump_hawdif(stwuct sk_buff *msg, u32 powtid, u32 seq,
			   stwuct batadv_pwiv *bat_pwiv,
			   stwuct batadv_hawd_iface *hawd_iface,
			   int *idx_s)
{
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;
	int idx = 0;

	hwist_fow_each_entwy_wcu(hawdif_neigh,
				 &hawd_iface->neigh_wist, wist) {
		if (idx++ < *idx_s)
			continue;

		if (batadv_v_neigh_dump_neigh(msg, powtid, seq, hawdif_neigh)) {
			*idx_s = idx - 1;
			wetuwn -EMSGSIZE;
		}
	}

	*idx_s = 0;
	wetuwn 0;
}

/**
 * batadv_v_neigh_dump() - Dump the neighbouws of a hawd intewface  into a
 *  message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @singwe_hawdif: Wimit dumping to this hawd intewface
 */
static void
batadv_v_neigh_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb,
		    stwuct batadv_pwiv *bat_pwiv,
		    stwuct batadv_hawd_iface *singwe_hawdif)
{
	stwuct batadv_hawd_iface *hawd_iface;
	int i_hawdif = 0;
	int i_hawdif_s = cb->awgs[0];
	int idx = cb->awgs[1];
	int powtid = NETWINK_CB(cb->skb).powtid;

	wcu_wead_wock();
	if (singwe_hawdif) {
		if (i_hawdif_s == 0) {
			if (batadv_v_neigh_dump_hawdif(msg, powtid,
						       cb->nwh->nwmsg_seq,
						       bat_pwiv, singwe_hawdif,
						       &idx) == 0)
				i_hawdif++;
		}
	} ewse {
		wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
			if (hawd_iface->soft_iface != bat_pwiv->soft_iface)
				continue;

			if (i_hawdif++ < i_hawdif_s)
				continue;

			if (batadv_v_neigh_dump_hawdif(msg, powtid,
						       cb->nwh->nwmsg_seq,
						       bat_pwiv, hawd_iface,
						       &idx)) {
				i_hawdif--;
				bweak;
			}
		}
	}
	wcu_wead_unwock();

	cb->awgs[0] = i_hawdif;
	cb->awgs[1] = idx;
}

/**
 * batadv_v_owig_dump_subentwy() - Dump an owiginatow subentwy into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 * @owig_node: Owiginatow to dump
 * @neigh_node: Singwe hops neighbouw
 * @best: Is the best owiginatow
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_v_owig_dump_subentwy(stwuct sk_buff *msg, u32 powtid, u32 seq,
			    stwuct batadv_pwiv *bat_pwiv,
			    stwuct batadv_hawd_iface *if_outgoing,
			    stwuct batadv_owig_node *owig_node,
			    stwuct batadv_neigh_node *neigh_node,
			    boow best)
{
	stwuct batadv_neigh_ifinfo *n_ifinfo;
	unsigned int wast_seen_msecs;
	u32 thwoughput;
	void *hdw;

	n_ifinfo = batadv_neigh_ifinfo_get(neigh_node, if_outgoing);
	if (!n_ifinfo)
		wetuwn 0;

	thwoughput = n_ifinfo->bat_v.thwoughput * 100;

	batadv_neigh_ifinfo_put(n_ifinfo);

	wast_seen_msecs = jiffies_to_msecs(jiffies - owig_node->wast_seen);

	if (if_outgoing != BATADV_IF_DEFAUWT &&
	    if_outgoing != neigh_node->if_incoming)
		wetuwn 0;

	hdw = genwmsg_put(msg, powtid, seq, &batadv_netwink_famiwy, NWM_F_MUWTI,
			  BATADV_CMD_GET_OWIGINATOWS);
	if (!hdw)
		wetuwn -ENOBUFS;

	if (nwa_put(msg, BATADV_ATTW_OWIG_ADDWESS, ETH_AWEN, owig_node->owig) ||
	    nwa_put(msg, BATADV_ATTW_NEIGH_ADDWESS, ETH_AWEN,
		    neigh_node->addw) ||
	    nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   neigh_node->if_incoming->net_dev->name) ||
	    nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			neigh_node->if_incoming->net_dev->ifindex) ||
	    nwa_put_u32(msg, BATADV_ATTW_THWOUGHPUT, thwoughput) ||
	    nwa_put_u32(msg, BATADV_ATTW_WAST_SEEN_MSECS,
			wast_seen_msecs))
		goto nwa_put_faiwuwe;

	if (best && nwa_put_fwag(msg, BATADV_ATTW_FWAG_BEST))
		goto nwa_put_faiwuwe;

	genwmsg_end(msg, hdw);
	wetuwn 0;

 nwa_put_faiwuwe:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

/**
 * batadv_v_owig_dump_entwy() - Dump an owiginatow entwy into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 * @owig_node: Owiginatow to dump
 * @sub_s: Numbew of sub entwies to skip
 *
 * This function assumes the cawwew howds wcu_wead_wock().
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_v_owig_dump_entwy(stwuct sk_buff *msg, u32 powtid, u32 seq,
			 stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_hawd_iface *if_outgoing,
			 stwuct batadv_owig_node *owig_node, int *sub_s)
{
	stwuct batadv_neigh_node *neigh_node_best;
	stwuct batadv_neigh_node *neigh_node;
	int sub = 0;
	boow best;

	neigh_node_best = batadv_owig_woutew_get(owig_node, if_outgoing);
	if (!neigh_node_best)
		goto out;

	hwist_fow_each_entwy_wcu(neigh_node, &owig_node->neigh_wist, wist) {
		if (sub++ < *sub_s)
			continue;

		best = (neigh_node == neigh_node_best);

		if (batadv_v_owig_dump_subentwy(msg, powtid, seq, bat_pwiv,
						if_outgoing, owig_node,
						neigh_node, best)) {
			batadv_neigh_node_put(neigh_node_best);

			*sub_s = sub - 1;
			wetuwn -EMSGSIZE;
		}
	}

 out:
	batadv_neigh_node_put(neigh_node_best);

	*sub_s = 0;
	wetuwn 0;
}

/**
 * batadv_v_owig_dump_bucket() - Dump an owiginatow bucket into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @seq: Sequence numbew of netwink message
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 * @head: Bucket to be dumped
 * @idx_s: Numbew of entwies to be skipped
 * @sub: Numbew of sub entwies to be skipped
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int
batadv_v_owig_dump_bucket(stwuct sk_buff *msg, u32 powtid, u32 seq,
			  stwuct batadv_pwiv *bat_pwiv,
			  stwuct batadv_hawd_iface *if_outgoing,
			  stwuct hwist_head *head, int *idx_s, int *sub)
{
	stwuct batadv_owig_node *owig_node;
	int idx = 0;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(owig_node, head, hash_entwy) {
		if (idx++ < *idx_s)
			continue;

		if (batadv_v_owig_dump_entwy(msg, powtid, seq, bat_pwiv,
					     if_outgoing, owig_node, sub)) {
			wcu_wead_unwock();
			*idx_s = idx - 1;
			wetuwn -EMSGSIZE;
		}
	}
	wcu_wead_unwock();

	*idx_s = 0;
	*sub = 0;
	wetuwn 0;
}

/**
 * batadv_v_owig_dump() - Dump the owiginatows into a message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @if_outgoing: Wimit dump to entwies with this outgoing intewface
 */
static void
batadv_v_owig_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb,
		   stwuct batadv_pwiv *bat_pwiv,
		   stwuct batadv_hawd_iface *if_outgoing)
{
	stwuct batadv_hashtabwe *hash = bat_pwiv->owig_hash;
	stwuct hwist_head *head;
	int bucket = cb->awgs[0];
	int idx = cb->awgs[1];
	int sub = cb->awgs[2];
	int powtid = NETWINK_CB(cb->skb).powtid;

	whiwe (bucket < hash->size) {
		head = &hash->tabwe[bucket];

		if (batadv_v_owig_dump_bucket(msg, powtid,
					      cb->nwh->nwmsg_seq,
					      bat_pwiv, if_outgoing, head, &idx,
					      &sub))
			bweak;

		bucket++;
	}

	cb->awgs[0] = bucket;
	cb->awgs[1] = idx;
	cb->awgs[2] = sub;
}

static int batadv_v_neigh_cmp(stwuct batadv_neigh_node *neigh1,
			      stwuct batadv_hawd_iface *if_outgoing1,
			      stwuct batadv_neigh_node *neigh2,
			      stwuct batadv_hawd_iface *if_outgoing2)
{
	stwuct batadv_neigh_ifinfo *ifinfo1, *ifinfo2;
	int wet = 0;

	ifinfo1 = batadv_neigh_ifinfo_get(neigh1, if_outgoing1);
	if (!ifinfo1)
		goto eww_ifinfo1;

	ifinfo2 = batadv_neigh_ifinfo_get(neigh2, if_outgoing2);
	if (!ifinfo2)
		goto eww_ifinfo2;

	wet = ifinfo1->bat_v.thwoughput - ifinfo2->bat_v.thwoughput;

	batadv_neigh_ifinfo_put(ifinfo2);
eww_ifinfo2:
	batadv_neigh_ifinfo_put(ifinfo1);
eww_ifinfo1:
	wetuwn wet;
}

static boow batadv_v_neigh_is_sob(stwuct batadv_neigh_node *neigh1,
				  stwuct batadv_hawd_iface *if_outgoing1,
				  stwuct batadv_neigh_node *neigh2,
				  stwuct batadv_hawd_iface *if_outgoing2)
{
	stwuct batadv_neigh_ifinfo *ifinfo1, *ifinfo2;
	u32 thweshowd;
	boow wet = fawse;

	ifinfo1 = batadv_neigh_ifinfo_get(neigh1, if_outgoing1);
	if (!ifinfo1)
		goto eww_ifinfo1;

	ifinfo2 = batadv_neigh_ifinfo_get(neigh2, if_outgoing2);
	if (!ifinfo2)
		goto eww_ifinfo2;

	thweshowd = ifinfo1->bat_v.thwoughput / 4;
	thweshowd = ifinfo1->bat_v.thwoughput - thweshowd;

	wet = ifinfo2->bat_v.thwoughput > thweshowd;

	batadv_neigh_ifinfo_put(ifinfo2);
eww_ifinfo2:
	batadv_neigh_ifinfo_put(ifinfo1);
eww_ifinfo1:
	wetuwn wet;
}

/**
 * batadv_v_init_sew_cwass() - initiawize GW sewection cwass
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 */
static void batadv_v_init_sew_cwass(stwuct batadv_pwiv *bat_pwiv)
{
	/* set defauwt thwoughput diffewence thweshowd to 5Mbps */
	atomic_set(&bat_pwiv->gw.sew_cwass, 50);
}

/**
 * batadv_v_gw_thwoughput_get() - wetwieve the GW-bandwidth fow a given GW
 * @gw_node: the GW to wetwieve the metwic fow
 * @bw: the pointew whewe the metwic wiww be stowed. The metwic is computed as
 *  the minimum between the GW advewtised thwoughput and the path thwoughput to
 *  it in the mesh
 *
 * Wetuwn: 0 on success, -1 on faiwuwe
 */
static int batadv_v_gw_thwoughput_get(stwuct batadv_gw_node *gw_node, u32 *bw)
{
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW;
	stwuct batadv_owig_node *owig_node;
	stwuct batadv_neigh_node *woutew;
	int wet = -1;

	owig_node = gw_node->owig_node;
	woutew = batadv_owig_woutew_get(owig_node, BATADV_IF_DEFAUWT);
	if (!woutew)
		goto out;

	woutew_ifinfo = batadv_neigh_ifinfo_get(woutew, BATADV_IF_DEFAUWT);
	if (!woutew_ifinfo)
		goto out;

	/* the GW metwic is computed as the minimum between the path thwoughput
	 * to weach the GW itsewf and the advewtised bandwidth.
	 * This gives us an appwoximation of the effective thwoughput that the
	 * cwient can expect via this pawticuwaw GW node
	 */
	*bw = woutew_ifinfo->bat_v.thwoughput;
	*bw = min_t(u32, *bw, gw_node->bandwidth_down);

	wet = 0;
out:
	batadv_neigh_node_put(woutew);
	batadv_neigh_ifinfo_put(woutew_ifinfo);

	wetuwn wet;
}

/**
 * batadv_v_gw_get_best_gw_node() - wetwieve the best GW node
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 *
 * Wetuwn: the GW node having the best GW-metwic, NUWW if no GW is known
 */
static stwuct batadv_gw_node *
batadv_v_gw_get_best_gw_node(stwuct batadv_pwiv *bat_pwiv)
{
	stwuct batadv_gw_node *gw_node, *cuww_gw = NUWW;
	u32 max_bw = 0, bw;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(gw_node, &bat_pwiv->gw.gateway_wist, wist) {
		if (!kwef_get_unwess_zewo(&gw_node->wefcount))
			continue;

		if (batadv_v_gw_thwoughput_get(gw_node, &bw) < 0)
			goto next;

		if (cuww_gw && bw <= max_bw)
			goto next;

		batadv_gw_node_put(cuww_gw);

		cuww_gw = gw_node;
		kwef_get(&cuww_gw->wefcount);
		max_bw = bw;

next:
		batadv_gw_node_put(gw_node);
	}
	wcu_wead_unwock();

	wetuwn cuww_gw;
}

/**
 * batadv_v_gw_is_ewigibwe() - check if a owiginatow wouwd be sewected as GW
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @cuww_gw_owig: owiginatow wepwesenting the cuwwentwy sewected GW
 * @owig_node: the owiginatow wepwesenting the new candidate
 *
 * Wetuwn: twue if owig_node can be sewected as cuwwent GW, fawse othewwise
 */
static boow batadv_v_gw_is_ewigibwe(stwuct batadv_pwiv *bat_pwiv,
				    stwuct batadv_owig_node *cuww_gw_owig,
				    stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_gw_node *cuww_gw, *owig_gw = NUWW;
	u32 gw_thwoughput, owig_thwoughput, thweshowd;
	boow wet = fawse;

	thweshowd = atomic_wead(&bat_pwiv->gw.sew_cwass);

	cuww_gw = batadv_gw_node_get(bat_pwiv, cuww_gw_owig);
	if (!cuww_gw) {
		wet = twue;
		goto out;
	}

	if (batadv_v_gw_thwoughput_get(cuww_gw, &gw_thwoughput) < 0) {
		wet = twue;
		goto out;
	}

	owig_gw = batadv_gw_node_get(bat_pwiv, owig_node);
	if (!owig_gw)
		goto out;

	if (batadv_v_gw_thwoughput_get(owig_gw, &owig_thwoughput) < 0)
		goto out;

	if (owig_thwoughput < gw_thwoughput)
		goto out;

	if ((owig_thwoughput - gw_thwoughput) < thweshowd)
		goto out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Westawting gateway sewection: bettew gateway found (thwoughput cuww: %u, thwoughput new: %u)\n",
		   gw_thwoughput, owig_thwoughput);

	wet = twue;
out:
	batadv_gw_node_put(cuww_gw);
	batadv_gw_node_put(owig_gw);

	wetuwn wet;
}

/**
 * batadv_v_gw_dump_entwy() - Dump a gateway into a message
 * @msg: Netwink message to dump into
 * @powtid: Powt making netwink wequest
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 * @gw_node: Gateway to be dumped
 *
 * Wetuwn: Ewwow code, ow 0 on success
 */
static int batadv_v_gw_dump_entwy(stwuct sk_buff *msg, u32 powtid,
				  stwuct netwink_cawwback *cb,
				  stwuct batadv_pwiv *bat_pwiv,
				  stwuct batadv_gw_node *gw_node)
{
	stwuct batadv_neigh_ifinfo *woutew_ifinfo = NUWW;
	stwuct batadv_neigh_node *woutew;
	stwuct batadv_gw_node *cuww_gw = NUWW;
	int wet = 0;
	void *hdw;

	woutew = batadv_owig_woutew_get(gw_node->owig_node, BATADV_IF_DEFAUWT);
	if (!woutew)
		goto out;

	woutew_ifinfo = batadv_neigh_ifinfo_get(woutew, BATADV_IF_DEFAUWT);
	if (!woutew_ifinfo)
		goto out;

	cuww_gw = batadv_gw_get_sewected_gw_node(bat_pwiv);

	hdw = genwmsg_put(msg, powtid, cb->nwh->nwmsg_seq,
			  &batadv_netwink_famiwy, NWM_F_MUWTI,
			  BATADV_CMD_GET_GATEWAYS);
	if (!hdw) {
		wet = -ENOBUFS;
		goto out;
	}

	genw_dump_check_consistent(cb, hdw);

	wet = -EMSGSIZE;

	if (cuww_gw == gw_node) {
		if (nwa_put_fwag(msg, BATADV_ATTW_FWAG_BEST)) {
			genwmsg_cancew(msg, hdw);
			goto out;
		}
	}

	if (nwa_put(msg, BATADV_ATTW_OWIG_ADDWESS, ETH_AWEN,
		    gw_node->owig_node->owig)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	if (nwa_put_u32(msg, BATADV_ATTW_THWOUGHPUT,
			woutew_ifinfo->bat_v.thwoughput)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	if (nwa_put(msg, BATADV_ATTW_WOUTEW, ETH_AWEN, woutew->addw)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	if (nwa_put_stwing(msg, BATADV_ATTW_HAWD_IFNAME,
			   woutew->if_incoming->net_dev->name)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	if (nwa_put_u32(msg, BATADV_ATTW_HAWD_IFINDEX,
			woutew->if_incoming->net_dev->ifindex)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	if (nwa_put_u32(msg, BATADV_ATTW_BANDWIDTH_DOWN,
			gw_node->bandwidth_down)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	if (nwa_put_u32(msg, BATADV_ATTW_BANDWIDTH_UP, gw_node->bandwidth_up)) {
		genwmsg_cancew(msg, hdw);
		goto out;
	}

	genwmsg_end(msg, hdw);
	wet = 0;

out:
	batadv_gw_node_put(cuww_gw);
	batadv_neigh_ifinfo_put(woutew_ifinfo);
	batadv_neigh_node_put(woutew);
	wetuwn wet;
}

/**
 * batadv_v_gw_dump() - Dump gateways into a message
 * @msg: Netwink message to dump into
 * @cb: Contwow bwock containing additionaw options
 * @bat_pwiv: The bat pwiv with aww the soft intewface infowmation
 */
static void batadv_v_gw_dump(stwuct sk_buff *msg, stwuct netwink_cawwback *cb,
			     stwuct batadv_pwiv *bat_pwiv)
{
	int powtid = NETWINK_CB(cb->skb).powtid;
	stwuct batadv_gw_node *gw_node;
	int idx_skip = cb->awgs[0];
	int idx = 0;

	spin_wock_bh(&bat_pwiv->gw.wist_wock);
	cb->seq = bat_pwiv->gw.genewation << 1 | 1;

	hwist_fow_each_entwy(gw_node, &bat_pwiv->gw.gateway_wist, wist) {
		if (idx++ < idx_skip)
			continue;

		if (batadv_v_gw_dump_entwy(msg, powtid, cb, bat_pwiv,
					   gw_node)) {
			idx_skip = idx - 1;
			goto unwock;
		}
	}

	idx_skip = idx;
unwock:
	spin_unwock_bh(&bat_pwiv->gw.wist_wock);

	cb->awgs[0] = idx_skip;
}

static stwuct batadv_awgo_ops batadv_batman_v __wead_mostwy = {
	.name = "BATMAN_V",
	.iface = {
		.activate = batadv_v_iface_activate,
		.enabwe = batadv_v_iface_enabwe,
		.disabwe = batadv_v_iface_disabwe,
		.update_mac = batadv_v_iface_update_mac,
		.pwimawy_set = batadv_v_pwimawy_iface_set,
	},
	.neigh = {
		.hawdif_init = batadv_v_hawdif_neigh_init,
		.cmp = batadv_v_neigh_cmp,
		.is_simiwaw_ow_bettew = batadv_v_neigh_is_sob,
		.dump = batadv_v_neigh_dump,
	},
	.owig = {
		.dump = batadv_v_owig_dump,
	},
	.gw = {
		.init_sew_cwass = batadv_v_init_sew_cwass,
		.sew_cwass_max = U32_MAX,
		.get_best_gw_node = batadv_v_gw_get_best_gw_node,
		.is_ewigibwe = batadv_v_gw_is_ewigibwe,
		.dump = batadv_v_gw_dump,
	},
};

/**
 * batadv_v_hawdif_init() - initiawize the awgowithm specific fiewds in the
 *  hawd-intewface object
 * @hawd_iface: the hawd-intewface to initiawize
 */
void batadv_v_hawdif_init(stwuct batadv_hawd_iface *hawd_iface)
{
	/* enabwe wink thwoughput auto-detection by setting the thwoughput
	 * ovewwide to zewo
	 */
	atomic_set(&hawd_iface->bat_v.thwoughput_ovewwide, 0);
	atomic_set(&hawd_iface->bat_v.ewp_intewvaw, 500);

	hawd_iface->bat_v.aggw_wen = 0;
	skb_queue_head_init(&hawd_iface->bat_v.aggw_wist);
	INIT_DEWAYED_WOWK(&hawd_iface->bat_v.aggw_wq,
			  batadv_v_ogm_aggw_wowk);
}

/**
 * batadv_v_mesh_init() - initiawize the B.A.T.M.A.N. V pwivate wesouwces fow a
 *  mesh
 * @bat_pwiv: the object wepwesenting the mesh intewface to initiawise
 *
 * Wetuwn: 0 on success ow a negative ewwow code othewwise
 */
int batadv_v_mesh_init(stwuct batadv_pwiv *bat_pwiv)
{
	int wet = 0;

	wet = batadv_v_ogm_init(bat_pwiv);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

/**
 * batadv_v_mesh_fwee() - fwee the B.A.T.M.A.N. V pwivate wesouwces fow a mesh
 * @bat_pwiv: the object wepwesenting the mesh intewface to fwee
 */
void batadv_v_mesh_fwee(stwuct batadv_pwiv *bat_pwiv)
{
	batadv_v_ogm_fwee(bat_pwiv);
}

/**
 * batadv_v_init() - B.A.T.M.A.N. V initiawization function
 *
 * Descwiption: Takes cawe of initiawizing aww the subcomponents.
 * It is invoked upon moduwe woad onwy.
 *
 * Wetuwn: 0 on success ow a negative ewwow code othewwise
 */
int __init batadv_v_init(void)
{
	int wet;

	/* B.A.T.M.A.N. V echo wocation pwotocow packet  */
	wet = batadv_wecv_handwew_wegistew(BATADV_EWP,
					   batadv_v_ewp_packet_wecv);
	if (wet < 0)
		wetuwn wet;

	wet = batadv_wecv_handwew_wegistew(BATADV_OGM2,
					   batadv_v_ogm_packet_wecv);
	if (wet < 0)
		goto ewp_unwegistew;

	wet = batadv_awgo_wegistew(&batadv_batman_v);
	if (wet < 0)
		goto ogm_unwegistew;

	wetuwn wet;

ogm_unwegistew:
	batadv_wecv_handwew_unwegistew(BATADV_OGM2);

ewp_unwegistew:
	batadv_wecv_handwew_unwegistew(BATADV_EWP);

	wetuwn wet;
}
