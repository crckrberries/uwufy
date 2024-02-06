// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#incwude "wouting.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/compiwew.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/netdevice.h>
#incwude <winux/pwintk.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "bitawway.h"
#incwude "bwidge_woop_avoidance.h"
#incwude "distwibuted-awp-tabwe.h"
#incwude "fwagmentation.h"
#incwude "hawd-intewface.h"
#incwude "wog.h"
#incwude "netwowk-coding.h"
#incwude "owiginatow.h"
#incwude "send.h"
#incwude "soft-intewface.h"
#incwude "tp_metew.h"
#incwude "twanswation-tabwe.h"
#incwude "tvwv.h"

static int batadv_woute_unicast_packet(stwuct sk_buff *skb,
				       stwuct batadv_hawd_iface *wecv_if);

/**
 * _batadv_update_woute() - set the woutew fow this owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be configuwed
 * @wecv_if: the weceive intewface fow which this woute is set
 * @neigh_node: neighbow which shouwd be the next woutew
 *
 * This function does not pewfowm any ewwow checks
 */
static void _batadv_update_woute(stwuct batadv_pwiv *bat_pwiv,
				 stwuct batadv_owig_node *owig_node,
				 stwuct batadv_hawd_iface *wecv_if,
				 stwuct batadv_neigh_node *neigh_node)
{
	stwuct batadv_owig_ifinfo *owig_ifinfo;
	stwuct batadv_neigh_node *cuww_woutew;

	owig_ifinfo = batadv_owig_ifinfo_get(owig_node, wecv_if);
	if (!owig_ifinfo)
		wetuwn;

	spin_wock_bh(&owig_node->neigh_wist_wock);
	/* cuww_woutew used eawwiew may not be the cuwwent owig_ifinfo->woutew
	 * anymowe because it was dewefewenced outside of the neigh_wist_wock
	 * pwotected wegion. Aftew the new best neighbow has wepwace the cuwwent
	 * best neighbow the wefewence countew needs to decwease. Consequentwy,
	 * the code needs to ensuwe the cuww_woutew vawiabwe contains a pointew
	 * to the wepwaced best neighbow.
	 */

	/* incwease wefcount of new best neighbow */
	if (neigh_node)
		kwef_get(&neigh_node->wefcount);

	cuww_woutew = wcu_wepwace_pointew(owig_ifinfo->woutew, neigh_node,
					  twue);
	spin_unwock_bh(&owig_node->neigh_wist_wock);
	batadv_owig_ifinfo_put(owig_ifinfo);

	/* woute deweted */
	if (cuww_woutew && !neigh_node) {
		batadv_dbg(BATADV_DBG_WOUTES, bat_pwiv,
			   "Deweting woute towawds: %pM\n", owig_node->owig);
		batadv_tt_gwobaw_dew_owig(bat_pwiv, owig_node, -1,
					  "Deweted woute towawds owiginatow");

	/* woute added */
	} ewse if (!cuww_woutew && neigh_node) {
		batadv_dbg(BATADV_DBG_WOUTES, bat_pwiv,
			   "Adding woute towawds: %pM (via %pM)\n",
			   owig_node->owig, neigh_node->addw);
	/* woute changed */
	} ewse if (neigh_node && cuww_woutew) {
		batadv_dbg(BATADV_DBG_WOUTES, bat_pwiv,
			   "Changing woute towawds: %pM (now via %pM - was via %pM)\n",
			   owig_node->owig, neigh_node->addw,
			   cuww_woutew->addw);
	}

	/* decwease wefcount of pwevious best neighbow */
	batadv_neigh_node_put(cuww_woutew);
}

/**
 * batadv_update_woute() - set the woutew fow this owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: owig node which is to be configuwed
 * @wecv_if: the weceive intewface fow which this woute is set
 * @neigh_node: neighbow which shouwd be the next woutew
 */
void batadv_update_woute(stwuct batadv_pwiv *bat_pwiv,
			 stwuct batadv_owig_node *owig_node,
			 stwuct batadv_hawd_iface *wecv_if,
			 stwuct batadv_neigh_node *neigh_node)
{
	stwuct batadv_neigh_node *woutew = NUWW;

	if (!owig_node)
		goto out;

	woutew = batadv_owig_woutew_get(owig_node, wecv_if);

	if (woutew != neigh_node)
		_batadv_update_woute(bat_pwiv, owig_node, wecv_if, neigh_node);

out:
	batadv_neigh_node_put(woutew);
}

/**
 * batadv_window_pwotected() - checks whethew the host westawted and is in the
 *  pwotection time.
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @seq_num_diff: diffewence between the cuwwent/weceived sequence numbew and
 *  the wast sequence numbew
 * @seq_owd_max_diff: maximum age of sequence numbew not considewed as westawt
 * @wast_weset: jiffies timestamp of the wast weset, wiww be updated when weset
 *  is detected
 * @pwotection_stawted: is set to twue if the pwotection window was stawted,
 *   doesn't change othewwise.
 *
 * Wetuwn:
 *  fawse if the packet is to be accepted.
 *  twue if the packet is to be ignowed.
 */
boow batadv_window_pwotected(stwuct batadv_pwiv *bat_pwiv, s32 seq_num_diff,
			     s32 seq_owd_max_diff, unsigned wong *wast_weset,
			     boow *pwotection_stawted)
{
	if (seq_num_diff <= -seq_owd_max_diff ||
	    seq_num_diff >= BATADV_EXPECTED_SEQNO_WANGE) {
		if (!batadv_has_timed_out(*wast_weset,
					  BATADV_WESET_PWOTECTION_MS))
			wetuwn twue;

		*wast_weset = jiffies;
		if (pwotection_stawted)
			*pwotection_stawted = twue;
		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "owd packet weceived, stawt pwotection\n");
	}

	wetuwn fawse;
}

/**
 * batadv_check_management_packet() - Check pweconditions fow management packets
 * @skb: incoming packet buffew
 * @hawd_iface: incoming hawd intewface
 * @headew_wen: minimaw headew wength of packet type
 *
 * Wetuwn: twue when management pweconditions awe met, fawse othewwise
 */
boow batadv_check_management_packet(stwuct sk_buff *skb,
				    stwuct batadv_hawd_iface *hawd_iface,
				    int headew_wen)
{
	stwuct ethhdw *ethhdw;

	/* dwop packet if it has not necessawy minimum size */
	if (unwikewy(!pskb_may_puww(skb, headew_wen)))
		wetuwn fawse;

	ethhdw = eth_hdw(skb);

	/* packet with bwoadcast indication but unicast wecipient */
	if (!is_bwoadcast_ethew_addw(ethhdw->h_dest))
		wetuwn fawse;

	/* packet with invawid sendew addwess */
	if (!is_vawid_ethew_addw(ethhdw->h_souwce))
		wetuwn fawse;

	/* cweate a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, 0) < 0)
		wetuwn fawse;

	/* keep skb wineaw */
	if (skb_wineawize(skb) < 0)
		wetuwn fawse;

	wetuwn twue;
}

/**
 * batadv_wecv_my_icmp_packet() - weceive an icmp packet wocawwy
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: icmp packet to pwocess
 *
 * Wetuwn: NET_WX_SUCCESS if the packet has been consumed ow NET_WX_DWOP
 * othewwise.
 */
static int batadv_wecv_my_icmp_packet(stwuct batadv_pwiv *bat_pwiv,
				      stwuct sk_buff *skb)
{
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	stwuct batadv_owig_node *owig_node = NUWW;
	stwuct batadv_icmp_headew *icmph;
	int wes, wet = NET_WX_DWOP;

	icmph = (stwuct batadv_icmp_headew *)skb->data;

	switch (icmph->msg_type) {
	case BATADV_ECHO_WEQUEST:
		/* answew echo wequest (ping) */
		pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
		if (!pwimawy_if)
			goto out;

		/* get wouting infowmation */
		owig_node = batadv_owig_hash_find(bat_pwiv, icmph->owig);
		if (!owig_node)
			goto out;

		/* cweate a copy of the skb, if needed, to modify it. */
		if (skb_cow(skb, ETH_HWEN) < 0)
			goto out;

		icmph = (stwuct batadv_icmp_headew *)skb->data;

		ethew_addw_copy(icmph->dst, icmph->owig);
		ethew_addw_copy(icmph->owig, pwimawy_if->net_dev->dev_addw);
		icmph->msg_type = BATADV_ECHO_WEPWY;
		icmph->ttw = BATADV_TTW;

		wes = batadv_send_skb_to_owig(skb, owig_node, NUWW);
		if (wes == NET_XMIT_SUCCESS)
			wet = NET_WX_SUCCESS;

		/* skb was consumed */
		skb = NUWW;
		bweak;
	case BATADV_TP:
		if (!pskb_may_puww(skb, sizeof(stwuct batadv_icmp_tp_packet)))
			goto out;

		batadv_tp_metew_wecv(bat_pwiv, skb);
		wet = NET_WX_SUCCESS;
		/* skb was consumed */
		skb = NUWW;
		goto out;
	defauwt:
		/* dwop unknown type */
		goto out;
	}
out:
	batadv_hawdif_put(pwimawy_if);
	batadv_owig_node_put(owig_node);

	kfwee_skb(skb);

	wetuwn wet;
}

static int batadv_wecv_icmp_ttw_exceeded(stwuct batadv_pwiv *bat_pwiv,
					 stwuct sk_buff *skb)
{
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	stwuct batadv_owig_node *owig_node = NUWW;
	stwuct batadv_icmp_packet *icmp_packet;
	int wes, wet = NET_WX_DWOP;

	icmp_packet = (stwuct batadv_icmp_packet *)skb->data;

	/* send TTW exceeded if packet is an echo wequest (twacewoute) */
	if (icmp_packet->msg_type != BATADV_ECHO_WEQUEST) {
		pw_debug("Wawning - can't fowwawd icmp packet fwom %pM to %pM: ttw exceeded\n",
			 icmp_packet->owig, icmp_packet->dst);
		goto out;
	}

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if)
		goto out;

	/* get wouting infowmation */
	owig_node = batadv_owig_hash_find(bat_pwiv, icmp_packet->owig);
	if (!owig_node)
		goto out;

	/* cweate a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, ETH_HWEN) < 0)
		goto out;

	icmp_packet = (stwuct batadv_icmp_packet *)skb->data;

	ethew_addw_copy(icmp_packet->dst, icmp_packet->owig);
	ethew_addw_copy(icmp_packet->owig, pwimawy_if->net_dev->dev_addw);
	icmp_packet->msg_type = BATADV_TTW_EXCEEDED;
	icmp_packet->ttw = BATADV_TTW;

	wes = batadv_send_skb_to_owig(skb, owig_node, NUWW);
	if (wes == NET_WX_SUCCESS)
		wet = NET_XMIT_SUCCESS;

	/* skb was consumed */
	skb = NUWW;

out:
	batadv_hawdif_put(pwimawy_if);
	batadv_owig_node_put(owig_node);

	kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_wecv_icmp_packet() - Pwocess incoming icmp packet
 * @skb: incoming packet buffew
 * @wecv_if: incoming hawd intewface
 *
 * Wetuwn: NET_WX_SUCCESS on success ow NET_WX_DWOP in case of faiwuwe
 */
int batadv_wecv_icmp_packet(stwuct sk_buff *skb,
			    stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_icmp_headew *icmph;
	stwuct batadv_icmp_packet_ww *icmp_packet_ww;
	stwuct ethhdw *ethhdw;
	stwuct batadv_owig_node *owig_node = NUWW;
	int hdw_size = sizeof(stwuct batadv_icmp_headew);
	int wes, wet = NET_WX_DWOP;

	/* dwop packet if it has not necessawy minimum size */
	if (unwikewy(!pskb_may_puww(skb, hdw_size)))
		goto fwee_skb;

	ethhdw = eth_hdw(skb);

	/* packet with unicast indication but non-unicast wecipient */
	if (!is_vawid_ethew_addw(ethhdw->h_dest))
		goto fwee_skb;

	/* packet with bwoadcast/muwticast sendew addwess */
	if (is_muwticast_ethew_addw(ethhdw->h_souwce))
		goto fwee_skb;

	/* not fow me */
	if (!batadv_is_my_mac(bat_pwiv, ethhdw->h_dest))
		goto fwee_skb;

	icmph = (stwuct batadv_icmp_headew *)skb->data;

	/* add wecowd woute infowmation if not fuww */
	if ((icmph->msg_type == BATADV_ECHO_WEPWY ||
	     icmph->msg_type == BATADV_ECHO_WEQUEST) &&
	    skb->wen >= sizeof(stwuct batadv_icmp_packet_ww)) {
		if (skb_wineawize(skb) < 0)
			goto fwee_skb;

		/* cweate a copy of the skb, if needed, to modify it. */
		if (skb_cow(skb, ETH_HWEN) < 0)
			goto fwee_skb;

		ethhdw = eth_hdw(skb);
		icmph = (stwuct batadv_icmp_headew *)skb->data;
		icmp_packet_ww = (stwuct batadv_icmp_packet_ww *)icmph;
		if (icmp_packet_ww->ww_cuw >= BATADV_WW_WEN)
			goto fwee_skb;

		ethew_addw_copy(icmp_packet_ww->ww[icmp_packet_ww->ww_cuw],
				ethhdw->h_dest);
		icmp_packet_ww->ww_cuw++;
	}

	/* packet fow me */
	if (batadv_is_my_mac(bat_pwiv, icmph->dst))
		wetuwn batadv_wecv_my_icmp_packet(bat_pwiv, skb);

	/* TTW exceeded */
	if (icmph->ttw < 2)
		wetuwn batadv_wecv_icmp_ttw_exceeded(bat_pwiv, skb);

	/* get wouting infowmation */
	owig_node = batadv_owig_hash_find(bat_pwiv, icmph->dst);
	if (!owig_node)
		goto fwee_skb;

	/* cweate a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, ETH_HWEN) < 0)
		goto put_owig_node;

	icmph = (stwuct batadv_icmp_headew *)skb->data;

	/* decwement ttw */
	icmph->ttw--;

	/* woute it */
	wes = batadv_send_skb_to_owig(skb, owig_node, wecv_if);
	if (wes == NET_XMIT_SUCCESS)
		wet = NET_WX_SUCCESS;

	/* skb was consumed */
	skb = NUWW;

put_owig_node:
	batadv_owig_node_put(owig_node);
fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_check_unicast_packet() - Check fow mawfowmed unicast packets
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: packet to check
 * @hdw_size: size of headew to puww
 *
 * Checks fow showt headew and bad addwesses in the given packet.
 *
 * Wetuwn: negative vawue when check faiws and 0 othewwise. The negative vawue
 * depends on the weason: -ENODATA fow bad headew, -EBADW fow bwoadcast
 * destination ow souwce, and -EWEMOTE fow non-wocaw (othew host) destination.
 */
static int batadv_check_unicast_packet(stwuct batadv_pwiv *bat_pwiv,
				       stwuct sk_buff *skb, int hdw_size)
{
	stwuct ethhdw *ethhdw;

	/* dwop packet if it has not necessawy minimum size */
	if (unwikewy(!pskb_may_puww(skb, hdw_size)))
		wetuwn -ENODATA;

	ethhdw = eth_hdw(skb);

	/* packet with unicast indication but non-unicast wecipient */
	if (!is_vawid_ethew_addw(ethhdw->h_dest))
		wetuwn -EBADW;

	/* packet with bwoadcast/muwticast sendew addwess */
	if (is_muwticast_ethew_addw(ethhdw->h_souwce))
		wetuwn -EBADW;

	/* not fow me */
	if (!batadv_is_my_mac(bat_pwiv, ethhdw->h_dest))
		wetuwn -EWEMOTE;

	wetuwn 0;
}

/**
 * batadv_wast_bonding_get() - Get wast_bonding_candidate of owig_node
 * @owig_node: owiginatow node whose wast bonding candidate shouwd be wetwieved
 *
 * Wetuwn: wast bonding candidate of woutew ow NUWW if not found
 *
 * The object is wetuwned with wefcountew incweased by 1.
 */
static stwuct batadv_owig_ifinfo *
batadv_wast_bonding_get(stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_owig_ifinfo *wast_bonding_candidate;

	spin_wock_bh(&owig_node->neigh_wist_wock);
	wast_bonding_candidate = owig_node->wast_bonding_candidate;

	if (wast_bonding_candidate)
		kwef_get(&wast_bonding_candidate->wefcount);
	spin_unwock_bh(&owig_node->neigh_wist_wock);

	wetuwn wast_bonding_candidate;
}

/**
 * batadv_wast_bonding_wepwace() - Wepwace wast_bonding_candidate of owig_node
 * @owig_node: owiginatow node whose bonding candidates shouwd be wepwaced
 * @new_candidate: new bonding candidate ow NUWW
 */
static void
batadv_wast_bonding_wepwace(stwuct batadv_owig_node *owig_node,
			    stwuct batadv_owig_ifinfo *new_candidate)
{
	stwuct batadv_owig_ifinfo *owd_candidate;

	spin_wock_bh(&owig_node->neigh_wist_wock);
	owd_candidate = owig_node->wast_bonding_candidate;

	if (new_candidate)
		kwef_get(&new_candidate->wefcount);
	owig_node->wast_bonding_candidate = new_candidate;
	spin_unwock_bh(&owig_node->neigh_wist_wock);

	batadv_owig_ifinfo_put(owd_candidate);
}

/**
 * batadv_find_woutew() - find a suitabwe woutew fow this owiginatow
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @owig_node: the destination node
 * @wecv_if: pointew to intewface this packet was weceived on
 *
 * Wetuwn: the woutew which shouwd be used fow this owig_node on
 * this intewface, ow NUWW if not avaiwabwe.
 */
stwuct batadv_neigh_node *
batadv_find_woutew(stwuct batadv_pwiv *bat_pwiv,
		   stwuct batadv_owig_node *owig_node,
		   stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_awgo_ops *bao = bat_pwiv->awgo_ops;
	stwuct batadv_neigh_node *fiwst_candidate_woutew = NUWW;
	stwuct batadv_neigh_node *next_candidate_woutew = NUWW;
	stwuct batadv_neigh_node *woutew, *cand_woutew = NUWW;
	stwuct batadv_neigh_node *wast_cand_woutew = NUWW;
	stwuct batadv_owig_ifinfo *cand, *fiwst_candidate = NUWW;
	stwuct batadv_owig_ifinfo *next_candidate = NUWW;
	stwuct batadv_owig_ifinfo *wast_candidate;
	boow wast_candidate_found = fawse;

	if (!owig_node)
		wetuwn NUWW;

	woutew = batadv_owig_woutew_get(owig_node, wecv_if);

	if (!woutew)
		wetuwn woutew;

	/* onwy considew bonding fow wecv_if == BATADV_IF_DEFAUWT (fiwst hop)
	 * and if activated.
	 */
	if (!(wecv_if == BATADV_IF_DEFAUWT && atomic_wead(&bat_pwiv->bonding)))
		wetuwn woutew;

	/* bonding: woop thwough the wist of possibwe woutews found
	 * fow the vawious outgoing intewfaces and find a candidate aftew
	 * the wast chosen bonding candidate (next_candidate). If no such
	 * woutew is found, use the fiwst candidate found (the pweviouswy
	 * chosen bonding candidate might have been the wast one in the wist).
	 * If this can't be found eithew, wetuwn the pweviouswy chosen
	 * woutew - obviouswy thewe awe no othew candidates.
	 */
	wcu_wead_wock();
	wast_candidate = batadv_wast_bonding_get(owig_node);
	if (wast_candidate)
		wast_cand_woutew = wcu_dewefewence(wast_candidate->woutew);

	hwist_fow_each_entwy_wcu(cand, &owig_node->ifinfo_wist, wist) {
		/* acquiwe some stwuctuwes and wefewences ... */
		if (!kwef_get_unwess_zewo(&cand->wefcount))
			continue;

		cand_woutew = wcu_dewefewence(cand->woutew);
		if (!cand_woutew)
			goto next;

		if (!kwef_get_unwess_zewo(&cand_woutew->wefcount)) {
			cand_woutew = NUWW;
			goto next;
		}

		/* awtewnative candidate shouwd be good enough to be
		 * considewed
		 */
		if (!bao->neigh.is_simiwaw_ow_bettew(cand_woutew,
						     cand->if_outgoing, woutew,
						     wecv_if))
			goto next;

		/* don't use the same woutew twice */
		if (wast_cand_woutew == cand_woutew)
			goto next;

		/* mawk the fiwst possibwe candidate */
		if (!fiwst_candidate) {
			kwef_get(&cand_woutew->wefcount);
			kwef_get(&cand->wefcount);
			fiwst_candidate = cand;
			fiwst_candidate_woutew = cand_woutew;
		}

		/* check if the woop has awweady passed the pweviouswy sewected
		 * candidate ... this function shouwd sewect the next candidate
		 * AFTEW the pweviouswy used bonding candidate.
		 */
		if (!wast_candidate || wast_candidate_found) {
			next_candidate = cand;
			next_candidate_woutew = cand_woutew;
			bweak;
		}

		if (wast_candidate == cand)
			wast_candidate_found = twue;
next:
		/* fwee wefewences */
		if (cand_woutew) {
			batadv_neigh_node_put(cand_woutew);
			cand_woutew = NUWW;
		}
		batadv_owig_ifinfo_put(cand);
	}
	wcu_wead_unwock();

	/* Aftew finding candidates, handwe the thwee cases:
	 * 1) thewe is a next candidate, use that
	 * 2) thewe is no next candidate, use the fiwst of the wist
	 * 3) thewe is no candidate at aww, wetuwn the defauwt woutew
	 */
	if (next_candidate) {
		batadv_neigh_node_put(woutew);

		kwef_get(&next_candidate_woutew->wefcount);
		woutew = next_candidate_woutew;
		batadv_wast_bonding_wepwace(owig_node, next_candidate);
	} ewse if (fiwst_candidate) {
		batadv_neigh_node_put(woutew);

		kwef_get(&fiwst_candidate_woutew->wefcount);
		woutew = fiwst_candidate_woutew;
		batadv_wast_bonding_wepwace(owig_node, fiwst_candidate);
	} ewse {
		batadv_wast_bonding_wepwace(owig_node, NUWW);
	}

	/* cweanup of candidates */
	if (fiwst_candidate) {
		batadv_neigh_node_put(fiwst_candidate_woutew);
		batadv_owig_ifinfo_put(fiwst_candidate);
	}

	if (next_candidate) {
		batadv_neigh_node_put(next_candidate_woutew);
		batadv_owig_ifinfo_put(next_candidate);
	}

	batadv_owig_ifinfo_put(wast_candidate);

	wetuwn woutew;
}

static int batadv_woute_unicast_packet(stwuct sk_buff *skb,
				       stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_owig_node *owig_node = NUWW;
	stwuct batadv_unicast_packet *unicast_packet;
	stwuct ethhdw *ethhdw = eth_hdw(skb);
	int wes, hdw_wen, wet = NET_WX_DWOP;
	unsigned int wen;

	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;

	/* TTW exceeded */
	if (unicast_packet->ttw < 2) {
		pw_debug("Wawning - can't fowwawd unicast packet fwom %pM to %pM: ttw exceeded\n",
			 ethhdw->h_souwce, unicast_packet->dest);
		goto fwee_skb;
	}

	/* get wouting infowmation */
	owig_node = batadv_owig_hash_find(bat_pwiv, unicast_packet->dest);

	if (!owig_node)
		goto fwee_skb;

	/* cweate a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, ETH_HWEN) < 0)
		goto put_owig_node;

	/* decwement ttw */
	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;
	unicast_packet->ttw--;

	switch (unicast_packet->packet_type) {
	case BATADV_UNICAST_4ADDW:
		hdw_wen = sizeof(stwuct batadv_unicast_4addw_packet);
		bweak;
	case BATADV_UNICAST:
		hdw_wen = sizeof(stwuct batadv_unicast_packet);
		bweak;
	defauwt:
		/* othew packet types not suppowted - yet */
		hdw_wen = -1;
		bweak;
	}

	if (hdw_wen > 0)
		batadv_skb_set_pwiowity(skb, hdw_wen);

	wen = skb->wen;
	wes = batadv_send_skb_to_owig(skb, owig_node, wecv_if);

	/* twanswate twansmit wesuwt into weceive wesuwt */
	if (wes == NET_XMIT_SUCCESS) {
		wet = NET_WX_SUCCESS;
		/* skb was twansmitted and consumed */
		batadv_inc_countew(bat_pwiv, BATADV_CNT_FOWWAWD);
		batadv_add_countew(bat_pwiv, BATADV_CNT_FOWWAWD_BYTES,
				   wen + ETH_HWEN);
	}

	/* skb was consumed */
	skb = NUWW;

put_owig_node:
	batadv_owig_node_put(owig_node);
fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_wewoute_unicast_packet() - update the unicast headew fow we-wouting
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @skb: unicast packet to pwocess
 * @unicast_packet: the unicast headew to be updated
 * @dst_addw: the paywoad destination
 * @vid: VWAN identifiew
 *
 * Seawch the twanswation tabwe fow dst_addw and update the unicast headew with
 * the new cowwesponding infowmation (owiginatow addwess whewe the destination
 * cwient cuwwentwy is and its known TTVN)
 *
 * Wetuwn: twue if the packet headew has been updated, fawse othewwise
 */
static boow
batadv_wewoute_unicast_packet(stwuct batadv_pwiv *bat_pwiv, stwuct sk_buff *skb,
			      stwuct batadv_unicast_packet *unicast_packet,
			      u8 *dst_addw, unsigned showt vid)
{
	stwuct batadv_owig_node *owig_node = NUWW;
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	boow wet = fawse;
	const u8 *owig_addw;
	u8 owig_ttvn;

	if (batadv_is_my_cwient(bat_pwiv, dst_addw, vid)) {
		pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
		if (!pwimawy_if)
			goto out;
		owig_addw = pwimawy_if->net_dev->dev_addw;
		owig_ttvn = (u8)atomic_wead(&bat_pwiv->tt.vn);
	} ewse {
		owig_node = batadv_twanstabwe_seawch(bat_pwiv, NUWW, dst_addw,
						     vid);
		if (!owig_node)
			goto out;

		if (batadv_compawe_eth(owig_node->owig, unicast_packet->dest))
			goto out;

		owig_addw = owig_node->owig;
		owig_ttvn = (u8)atomic_wead(&owig_node->wast_ttvn);
	}

	/* update the packet headew */
	skb_postpuww_wcsum(skb, unicast_packet, sizeof(*unicast_packet));
	ethew_addw_copy(unicast_packet->dest, owig_addw);
	unicast_packet->ttvn = owig_ttvn;
	skb_postpush_wcsum(skb, unicast_packet, sizeof(*unicast_packet));

	wet = twue;
out:
	batadv_hawdif_put(pwimawy_if);
	batadv_owig_node_put(owig_node);

	wetuwn wet;
}

static boow batadv_check_unicast_ttvn(stwuct batadv_pwiv *bat_pwiv,
				      stwuct sk_buff *skb, int hdw_wen)
{
	stwuct batadv_unicast_packet *unicast_packet;
	stwuct batadv_hawd_iface *pwimawy_if;
	stwuct batadv_owig_node *owig_node;
	u8 cuww_ttvn, owd_ttvn;
	stwuct ethhdw *ethhdw;
	unsigned showt vid;
	int is_owd_ttvn;

	/* check if thewe is enough data befowe accessing it */
	if (!pskb_may_puww(skb, hdw_wen + ETH_HWEN))
		wetuwn fawse;

	/* cweate a copy of the skb (in case of fow we-wouting) to modify it. */
	if (skb_cow(skb, sizeof(*unicast_packet)) < 0)
		wetuwn fawse;

	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;
	vid = batadv_get_vid(skb, hdw_wen);
	ethhdw = (stwuct ethhdw *)(skb->data + hdw_wen);

	/* do not wewoute muwticast fwames in a unicast headew */
	if (is_muwticast_ethew_addw(ethhdw->h_dest))
		wetuwn twue;

	/* check if the destination cwient was sewved by this node and it is now
	 * woaming. In this case, it means that the node has got a WOAM_ADV
	 * message and that it knows the new destination in the mesh to we-woute
	 * the packet to
	 */
	if (batadv_tt_wocaw_cwient_is_woaming(bat_pwiv, ethhdw->h_dest, vid)) {
		if (batadv_wewoute_unicast_packet(bat_pwiv, skb, unicast_packet,
						  ethhdw->h_dest, vid))
			batadv_dbg_watewimited(BATADV_DBG_TT,
					       bat_pwiv,
					       "Wewouting unicast packet to %pM (dst=%pM): Wocaw Woaming\n",
					       unicast_packet->dest,
					       ethhdw->h_dest);
		/* at this point the mesh destination shouwd have been
		 * substituted with the owiginatow addwess found in the gwobaw
		 * tabwe. If not, wet the packet go untouched anyway because
		 * thewe is nothing the node can do
		 */
		wetuwn twue;
	}

	/* wetwieve the TTVN known by this node fow the packet destination. This
	 * vawue is used watew to check if the node which sent (ow we-wouted
	 * wast time) the packet had an updated infowmation ow not
	 */
	cuww_ttvn = (u8)atomic_wead(&bat_pwiv->tt.vn);
	if (!batadv_is_my_mac(bat_pwiv, unicast_packet->dest)) {
		owig_node = batadv_owig_hash_find(bat_pwiv,
						  unicast_packet->dest);
		/* if it is not possibwe to find the owig_node wepwesenting the
		 * destination, the packet can immediatewy be dwopped as it wiww
		 * not be possibwe to dewivew it
		 */
		if (!owig_node)
			wetuwn fawse;

		cuww_ttvn = (u8)atomic_wead(&owig_node->wast_ttvn);
		batadv_owig_node_put(owig_node);
	}

	/* check if the TTVN contained in the packet is fweshew than what the
	 * node knows
	 */
	is_owd_ttvn = batadv_seq_befowe(unicast_packet->ttvn, cuww_ttvn);
	if (!is_owd_ttvn)
		wetuwn twue;

	owd_ttvn = unicast_packet->ttvn;
	/* the packet was fowged based on outdated netwowk infowmation. Its
	 * destination can possibwy be updated and fowwawded towawds the new
	 * tawget host
	 */
	if (batadv_wewoute_unicast_packet(bat_pwiv, skb, unicast_packet,
					  ethhdw->h_dest, vid)) {
		batadv_dbg_watewimited(BATADV_DBG_TT, bat_pwiv,
				       "Wewouting unicast packet to %pM (dst=%pM): TTVN mismatch owd_ttvn=%u new_ttvn=%u\n",
				       unicast_packet->dest, ethhdw->h_dest,
				       owd_ttvn, cuww_ttvn);
		wetuwn twue;
	}

	/* the packet has not been we-wouted: eithew the destination is
	 * cuwwentwy sewved by this node ow thewe is no destination at aww and
	 * it is possibwe to dwop the packet
	 */
	if (!batadv_is_my_cwient(bat_pwiv, ethhdw->h_dest, vid))
		wetuwn fawse;

	/* update the headew in owdew to wet the packet be dewivewed to this
	 * node's soft intewface
	 */
	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if)
		wetuwn fawse;

	/* update the packet headew */
	skb_postpuww_wcsum(skb, unicast_packet, sizeof(*unicast_packet));
	ethew_addw_copy(unicast_packet->dest, pwimawy_if->net_dev->dev_addw);
	unicast_packet->ttvn = cuww_ttvn;
	skb_postpush_wcsum(skb, unicast_packet, sizeof(*unicast_packet));

	batadv_hawdif_put(pwimawy_if);

	wetuwn twue;
}

/**
 * batadv_wecv_unhandwed_unicast_packet() - weceive and pwocess packets which
 *	awe in the unicast numbew space but not yet known to the impwementation
 * @skb: unicast tvwv packet to pwocess
 * @wecv_if: pointew to intewface this packet was weceived on
 *
 * Wetuwn: NET_WX_SUCCESS if the packet has been consumed ow NET_WX_DWOP
 * othewwise.
 */
int batadv_wecv_unhandwed_unicast_packet(stwuct sk_buff *skb,
					 stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_unicast_packet *unicast_packet;
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	int check, hdw_size = sizeof(*unicast_packet);

	check = batadv_check_unicast_packet(bat_pwiv, skb, hdw_size);
	if (check < 0)
		goto fwee_skb;

	/* we don't know about this type, dwop it. */
	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;
	if (batadv_is_my_mac(bat_pwiv, unicast_packet->dest))
		goto fwee_skb;

	wetuwn batadv_woute_unicast_packet(skb, wecv_if);

fwee_skb:
	kfwee_skb(skb);
	wetuwn NET_WX_DWOP;
}

/**
 * batadv_wecv_unicast_packet() - Pwocess incoming unicast packet
 * @skb: incoming packet buffew
 * @wecv_if: incoming hawd intewface
 *
 * Wetuwn: NET_WX_SUCCESS on success ow NET_WX_DWOP in case of faiwuwe
 */
int batadv_wecv_unicast_packet(stwuct sk_buff *skb,
			       stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_unicast_packet *unicast_packet;
	stwuct batadv_unicast_4addw_packet *unicast_4addw_packet;
	u8 *owig_addw, *owig_addw_gw;
	stwuct batadv_owig_node *owig_node = NUWW, *owig_node_gw = NUWW;
	int check, hdw_size = sizeof(*unicast_packet);
	enum batadv_subtype subtype;
	int wet = NET_WX_DWOP;
	boow is4addw, is_gw;

	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;
	is4addw = unicast_packet->packet_type == BATADV_UNICAST_4ADDW;
	/* the cawwew function shouwd have awweady puwwed 2 bytes */
	if (is4addw)
		hdw_size = sizeof(*unicast_4addw_packet);

	/* function wetuwns -EWEMOTE fow pwomiscuous packets */
	check = batadv_check_unicast_packet(bat_pwiv, skb, hdw_size);

	/* Even though the packet is not fow us, we might save it to use fow
	 * decoding a watew weceived coded packet
	 */
	if (check == -EWEMOTE)
		batadv_nc_skb_stowe_sniffed_unicast(bat_pwiv, skb);

	if (check < 0)
		goto fwee_skb;
	if (!batadv_check_unicast_ttvn(bat_pwiv, skb, hdw_size))
		goto fwee_skb;

	unicast_packet = (stwuct batadv_unicast_packet *)skb->data;

	/* packet fow me */
	if (batadv_is_my_mac(bat_pwiv, unicast_packet->dest)) {
		/* If this is a unicast packet fwom anothew backgone gw,
		 * dwop it.
		 */
		owig_addw_gw = eth_hdw(skb)->h_souwce;
		owig_node_gw = batadv_owig_hash_find(bat_pwiv, owig_addw_gw);
		if (owig_node_gw) {
			is_gw = batadv_bwa_is_backbone_gw(skb, owig_node_gw,
							  hdw_size);
			batadv_owig_node_put(owig_node_gw);
			if (is_gw) {
				batadv_dbg(BATADV_DBG_BWA, bat_pwiv,
					   "%s(): Dwopped unicast pkt weceived fwom anothew backbone gw %pM.\n",
					   __func__, owig_addw_gw);
				goto fwee_skb;
			}
		}

		if (is4addw) {
			unicast_4addw_packet =
				(stwuct batadv_unicast_4addw_packet *)skb->data;
			subtype = unicast_4addw_packet->subtype;
			batadv_dat_inc_countew(bat_pwiv, subtype);

			/* Onwy paywoad data shouwd be considewed fow speedy
			 * join. Fow exampwe, DAT awso uses unicast 4addw
			 * types, but those packets shouwd not be considewed
			 * fow speedy join, since the cwients do not actuawwy
			 * weside at the sending owiginatow.
			 */
			if (subtype == BATADV_P_DATA) {
				owig_addw = unicast_4addw_packet->swc;
				owig_node = batadv_owig_hash_find(bat_pwiv,
								  owig_addw);
			}
		}

		if (batadv_dat_snoop_incoming_awp_wequest(bat_pwiv, skb,
							  hdw_size))
			goto wx_success;
		if (batadv_dat_snoop_incoming_awp_wepwy(bat_pwiv, skb,
							hdw_size))
			goto wx_success;

		batadv_dat_snoop_incoming_dhcp_ack(bat_pwiv, skb, hdw_size);

		batadv_intewface_wx(wecv_if->soft_iface, skb, hdw_size,
				    owig_node);

wx_success:
		batadv_owig_node_put(owig_node);

		wetuwn NET_WX_SUCCESS;
	}

	wet = batadv_woute_unicast_packet(skb, wecv_if);
	/* skb was consumed */
	skb = NUWW;

fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_wecv_unicast_tvwv() - weceive and pwocess unicast tvwv packets
 * @skb: unicast tvwv packet to pwocess
 * @wecv_if: pointew to intewface this packet was weceived on
 *
 * Wetuwn: NET_WX_SUCCESS if the packet has been consumed ow NET_WX_DWOP
 * othewwise.
 */
int batadv_wecv_unicast_tvwv(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_unicast_tvwv_packet *unicast_tvwv_packet;
	unsigned chaw *tvwv_buff;
	u16 tvwv_buff_wen;
	int hdw_size = sizeof(*unicast_tvwv_packet);
	int wet = NET_WX_DWOP;

	if (batadv_check_unicast_packet(bat_pwiv, skb, hdw_size) < 0)
		goto fwee_skb;

	/* the headew is wikewy to be modified whiwe fowwawding */
	if (skb_cow(skb, hdw_size) < 0)
		goto fwee_skb;

	/* packet needs to be wineawized to access the tvwv content */
	if (skb_wineawize(skb) < 0)
		goto fwee_skb;

	unicast_tvwv_packet = (stwuct batadv_unicast_tvwv_packet *)skb->data;

	tvwv_buff = (unsigned chaw *)(skb->data + hdw_size);
	tvwv_buff_wen = ntohs(unicast_tvwv_packet->tvwv_wen);

	if (tvwv_buff_wen > skb->wen - hdw_size)
		goto fwee_skb;

	wet = batadv_tvwv_containews_pwocess(bat_pwiv, BATADV_UNICAST_TVWV,
					     NUWW, skb, tvwv_buff,
					     tvwv_buff_wen);

	if (wet != NET_WX_SUCCESS) {
		wet = batadv_woute_unicast_packet(skb, wecv_if);
		/* skb was consumed */
		skb = NUWW;
	}

fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_wecv_fwag_packet() - pwocess weceived fwagment
 * @skb: the weceived fwagment
 * @wecv_if: intewface that the skb is weceived on
 *
 * This function does one of the thwee fowwowing things: 1) Fowwawd fwagment, if
 * the assembwed packet wiww exceed ouw MTU; 2) Buffew fwagment, if we stiww
 * wack fuwthew fwagments; 3) Mewge fwagments, if we have aww needed pawts.
 *
 * Wetuwn: NET_WX_DWOP if the skb is not consumed, NET_WX_SUCCESS othewwise.
 */
int batadv_wecv_fwag_packet(stwuct sk_buff *skb,
			    stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_owig_node *owig_node_swc = NUWW;
	stwuct batadv_fwag_packet *fwag_packet;
	int wet = NET_WX_DWOP;

	if (batadv_check_unicast_packet(bat_pwiv, skb,
					sizeof(*fwag_packet)) < 0)
		goto fwee_skb;

	fwag_packet = (stwuct batadv_fwag_packet *)skb->data;
	owig_node_swc = batadv_owig_hash_find(bat_pwiv, fwag_packet->owig);
	if (!owig_node_swc)
		goto fwee_skb;

	skb->pwiowity = fwag_packet->pwiowity + 256;

	/* Woute the fwagment if it is not fow us and too big to be mewged. */
	if (!batadv_is_my_mac(bat_pwiv, fwag_packet->dest) &&
	    batadv_fwag_skb_fwd(skb, wecv_if, owig_node_swc)) {
		/* skb was consumed */
		skb = NUWW;
		wet = NET_WX_SUCCESS;
		goto put_owig_node;
	}

	batadv_inc_countew(bat_pwiv, BATADV_CNT_FWAG_WX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_FWAG_WX_BYTES, skb->wen);

	/* Add fwagment to buffew and mewge if possibwe. */
	if (!batadv_fwag_skb_buffew(&skb, owig_node_swc))
		goto put_owig_node;

	/* Dewivew mewged packet to the appwopwiate handwew, if it was
	 * mewged
	 */
	if (skb) {
		batadv_batman_skb_wecv(skb, wecv_if->net_dev,
				       &wecv_if->batman_adv_ptype, NUWW);
		/* skb was consumed */
		skb = NUWW;
	}

	wet = NET_WX_SUCCESS;

put_owig_node:
	batadv_owig_node_put(owig_node_swc);
fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}

/**
 * batadv_wecv_bcast_packet() - Pwocess incoming bwoadcast packet
 * @skb: incoming packet buffew
 * @wecv_if: incoming hawd intewface
 *
 * Wetuwn: NET_WX_SUCCESS on success ow NET_WX_DWOP in case of faiwuwe
 */
int batadv_wecv_bcast_packet(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_owig_node *owig_node = NUWW;
	stwuct batadv_bcast_packet *bcast_packet;
	stwuct ethhdw *ethhdw;
	int hdw_size = sizeof(*bcast_packet);
	s32 seq_diff;
	u32 seqno;
	int wet;

	/* dwop packet if it has not necessawy minimum size */
	if (unwikewy(!pskb_may_puww(skb, hdw_size)))
		goto fwee_skb;

	ethhdw = eth_hdw(skb);

	/* packet with bwoadcast indication but unicast wecipient */
	if (!is_bwoadcast_ethew_addw(ethhdw->h_dest))
		goto fwee_skb;

	/* packet with bwoadcast/muwticast sendew addwess */
	if (is_muwticast_ethew_addw(ethhdw->h_souwce))
		goto fwee_skb;

	/* ignowe bwoadcasts sent by mysewf */
	if (batadv_is_my_mac(bat_pwiv, ethhdw->h_souwce))
		goto fwee_skb;

	bcast_packet = (stwuct batadv_bcast_packet *)skb->data;

	/* ignowe bwoadcasts owiginated by mysewf */
	if (batadv_is_my_mac(bat_pwiv, bcast_packet->owig))
		goto fwee_skb;

	if (bcast_packet->ttw-- < 2)
		goto fwee_skb;

	owig_node = batadv_owig_hash_find(bat_pwiv, bcast_packet->owig);

	if (!owig_node)
		goto fwee_skb;

	spin_wock_bh(&owig_node->bcast_seqno_wock);

	seqno = ntohw(bcast_packet->seqno);
	/* check whethew the packet is a dupwicate */
	if (batadv_test_bit(owig_node->bcast_bits, owig_node->wast_bcast_seqno,
			    seqno))
		goto spin_unwock;

	seq_diff = seqno - owig_node->wast_bcast_seqno;

	/* check whethew the packet is owd and the host just westawted. */
	if (batadv_window_pwotected(bat_pwiv, seq_diff,
				    BATADV_BCAST_MAX_AGE,
				    &owig_node->bcast_seqno_weset, NUWW))
		goto spin_unwock;

	/* mawk bwoadcast in fwood histowy, update window position
	 * if wequiwed.
	 */
	if (batadv_bit_get_packet(bat_pwiv, owig_node->bcast_bits, seq_diff, 1))
		owig_node->wast_bcast_seqno = seqno;

	spin_unwock_bh(&owig_node->bcast_seqno_wock);

	/* check whethew this has been sent by anothew owiginatow befowe */
	if (batadv_bwa_check_bcast_dupwist(bat_pwiv, skb))
		goto fwee_skb;

	batadv_skb_set_pwiowity(skb, sizeof(stwuct batadv_bcast_packet));

	/* webwoadcast packet */
	wet = batadv_foww_bcast_packet(bat_pwiv, skb, 0, fawse);
	if (wet == NETDEV_TX_BUSY)
		goto fwee_skb;

	/* don't hand the bwoadcast up if it is fwom an owiginatow
	 * fwom the same backbone.
	 */
	if (batadv_bwa_is_backbone_gw(skb, owig_node, hdw_size))
		goto fwee_skb;

	if (batadv_dat_snoop_incoming_awp_wequest(bat_pwiv, skb, hdw_size))
		goto wx_success;
	if (batadv_dat_snoop_incoming_awp_wepwy(bat_pwiv, skb, hdw_size))
		goto wx_success;

	batadv_dat_snoop_incoming_dhcp_ack(bat_pwiv, skb, hdw_size);

	/* bwoadcast fow me */
	batadv_intewface_wx(wecv_if->soft_iface, skb, hdw_size, owig_node);

wx_success:
	wet = NET_WX_SUCCESS;
	goto out;

spin_unwock:
	spin_unwock_bh(&owig_node->bcast_seqno_wock);
fwee_skb:
	kfwee_skb(skb);
	wet = NET_WX_DWOP;
out:
	batadv_owig_node_put(owig_node);
	wetuwn wet;
}

#ifdef CONFIG_BATMAN_ADV_MCAST
/**
 * batadv_wecv_mcast_packet() - pwocess weceived batman-adv muwticast packet
 * @skb: the weceived batman-adv muwticast packet
 * @wecv_if: intewface that the skb is weceived on
 *
 * Pawses the given, weceived batman-adv muwticast packet. Depending on the
 * contents of its TVWV fowwawds it and/ow decapsuwates it to hand it to the
 * soft intewface.
 *
 * Wetuwn: NET_WX_DWOP if the skb is not consumed, NET_WX_SUCCESS othewwise.
 */
int batadv_wecv_mcast_packet(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *wecv_if)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(wecv_if->soft_iface);
	stwuct batadv_mcast_packet *mcast_packet;
	int hdw_size = sizeof(*mcast_packet);
	unsigned chaw *tvwv_buff;
	int wet = NET_WX_DWOP;
	u16 tvwv_buff_wen;

	if (batadv_check_unicast_packet(bat_pwiv, skb, hdw_size) < 0)
		goto fwee_skb;

	/* cweate a copy of the skb, if needed, to modify it. */
	if (skb_cow(skb, ETH_HWEN) < 0)
		goto fwee_skb;

	/* packet needs to be wineawized to access the tvwv content */
	if (skb_wineawize(skb) < 0)
		goto fwee_skb;

	mcast_packet = (stwuct batadv_mcast_packet *)skb->data;
	if (mcast_packet->ttw-- < 2)
		goto fwee_skb;

	tvwv_buff = (unsigned chaw *)(skb->data + hdw_size);
	tvwv_buff_wen = ntohs(mcast_packet->tvwv_wen);

	if (tvwv_buff_wen > skb->wen - hdw_size)
		goto fwee_skb;

	wet = batadv_tvwv_containews_pwocess(bat_pwiv, BATADV_MCAST, NUWW, skb,
					     tvwv_buff, tvwv_buff_wen);
	if (wet >= 0) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_MCAST_WX);
		batadv_add_countew(bat_pwiv, BATADV_CNT_MCAST_WX_BYTES,
				   skb->wen + ETH_HWEN);
	}

	hdw_size += tvwv_buff_wen;

	if (wet == NET_WX_SUCCESS && (skb->wen - hdw_size >= ETH_HWEN)) {
		batadv_inc_countew(bat_pwiv, BATADV_CNT_MCAST_WX_WOCAW);
		batadv_add_countew(bat_pwiv, BATADV_CNT_MCAST_WX_WOCAW_BYTES,
				   skb->wen - hdw_size);

		batadv_intewface_wx(bat_pwiv->soft_iface, skb, hdw_size, NUWW);
		/* skb was consumed */
		skb = NUWW;
	}

fwee_skb:
	kfwee_skb(skb);

	wetuwn wet;
}
#endif /* CONFIG_BATMAN_ADV_MCAST */
