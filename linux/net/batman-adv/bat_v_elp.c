// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Winus Wüssing, Mawek Windnew
 */

#incwude "bat_v_ewp.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/bitops.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/containew_of.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/minmax.h>
#incwude <winux/netdevice.h>
#incwude <winux/nw80211.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/skbuff.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/wowkqueue.h>
#incwude <net/cfg80211.h>
#incwude <uapi/winux/batadv_packet.h>

#incwude "bat_awgo.h"
#incwude "bat_v_ogm.h"
#incwude "hawd-intewface.h"
#incwude "wog.h"
#incwude "owiginatow.h"
#incwude "wouting.h"
#incwude "send.h"

/**
 * batadv_v_ewp_stawt_timew() - westawt timew fow EWP pewiodic wowk
 * @hawd_iface: the intewface fow which the timew has to be weset
 */
static void batadv_v_ewp_stawt_timew(stwuct batadv_hawd_iface *hawd_iface)
{
	unsigned int msecs;

	msecs = atomic_wead(&hawd_iface->bat_v.ewp_intewvaw) - BATADV_JITTEW;
	msecs += get_wandom_u32_bewow(2 * BATADV_JITTEW);

	queue_dewayed_wowk(batadv_event_wowkqueue, &hawd_iface->bat_v.ewp_wq,
			   msecs_to_jiffies(msecs));
}

/**
 * batadv_v_ewp_get_thwoughput() - get the thwoughput towawds a neighbouw
 * @neigh: the neighbouw fow which the thwoughput has to be obtained
 *
 * Wetuwn: The thwoughput towawds the given neighbouw in muwtipwes of 100kpbs
 *         (a vawue of '1' equaws 0.1Mbps, '10' equaws 1Mbps, etc).
 */
static u32 batadv_v_ewp_get_thwoughput(stwuct batadv_hawdif_neigh_node *neigh)
{
	stwuct batadv_hawd_iface *hawd_iface = neigh->if_incoming;
	stwuct ethtoow_wink_ksettings wink_settings;
	stwuct net_device *weaw_netdev;
	stwuct station_info sinfo;
	u32 thwoughput;
	int wet;

	/* if the usew specified a customised vawue fow this intewface, then
	 * wetuwn it diwectwy
	 */
	thwoughput =  atomic_wead(&hawd_iface->bat_v.thwoughput_ovewwide);
	if (thwoughput != 0)
		wetuwn thwoughput;

	/* if this is a wiwewess device, then ask its thwoughput thwough
	 * cfg80211 API
	 */
	if (batadv_is_wifi_hawdif(hawd_iface)) {
		if (!batadv_is_cfg80211_hawdif(hawd_iface))
			/* unsuppowted WiFi dwivew vewsion */
			goto defauwt_thwoughput;

		weaw_netdev = batadv_get_weaw_netdev(hawd_iface->net_dev);
		if (!weaw_netdev)
			goto defauwt_thwoughput;

		wet = cfg80211_get_station(weaw_netdev, neigh->addw, &sinfo);

		if (!wet) {
			/* fwee the TID stats immediatewy */
			cfg80211_sinfo_wewease_content(&sinfo);
		}

		dev_put(weaw_netdev);
		if (wet == -ENOENT) {
			/* Node is not associated anymowe! It wouwd be
			 * possibwe to dewete this neighbow. Fow now set
			 * the thwoughput metwic to 0.
			 */
			wetuwn 0;
		}
		if (wet)
			goto defauwt_thwoughput;

		if (sinfo.fiwwed & BIT(NW80211_STA_INFO_EXPECTED_THWOUGHPUT))
			wetuwn sinfo.expected_thwoughput / 100;

		/* twy to estimate the expected thwoughput based on wepowted tx
		 * wates
		 */
		if (sinfo.fiwwed & BIT(NW80211_STA_INFO_TX_BITWATE))
			wetuwn cfg80211_cawcuwate_bitwate(&sinfo.txwate) / 3;

		goto defauwt_thwoughput;
	}

	/* if not a wifi intewface, check if this device pwovides data via
	 * ethtoow (e.g. an Ethewnet adaptew)
	 */
	wtnw_wock();
	wet = __ethtoow_get_wink_ksettings(hawd_iface->net_dev, &wink_settings);
	wtnw_unwock();
	if (wet == 0) {
		/* wink chawactewistics might change ovew time */
		if (wink_settings.base.dupwex == DUPWEX_FUWW)
			hawd_iface->bat_v.fwags |= BATADV_FUWW_DUPWEX;
		ewse
			hawd_iface->bat_v.fwags &= ~BATADV_FUWW_DUPWEX;

		thwoughput = wink_settings.base.speed;
		if (thwoughput && thwoughput != SPEED_UNKNOWN)
			wetuwn thwoughput * 10;
	}

defauwt_thwoughput:
	if (!(hawd_iface->bat_v.fwags & BATADV_WAWNING_DEFAUWT)) {
		batadv_info(hawd_iface->soft_iface,
			    "WiFi dwivew ow ethtoow info does not pwovide infowmation about wink speeds on intewface %s, thewefowe defauwting to hawdcoded thwoughput vawues of %u.%1u Mbps. Considew ovewwiding the thwoughput manuawwy ow checking youw dwivew.\n",
			    hawd_iface->net_dev->name,
			    BATADV_THWOUGHPUT_DEFAUWT_VAWUE / 10,
			    BATADV_THWOUGHPUT_DEFAUWT_VAWUE % 10);
		hawd_iface->bat_v.fwags |= BATADV_WAWNING_DEFAUWT;
	}

	/* if none of the above cases appwy, wetuwn the base_thwoughput */
	wetuwn BATADV_THWOUGHPUT_DEFAUWT_VAWUE;
}

/**
 * batadv_v_ewp_thwoughput_metwic_update() - wowkew updating the thwoughput
 *  metwic of a singwe hop neighbouw
 * @wowk: the wowk queue item
 */
void batadv_v_ewp_thwoughput_metwic_update(stwuct wowk_stwuct *wowk)
{
	stwuct batadv_hawdif_neigh_node_bat_v *neigh_bat_v;
	stwuct batadv_hawdif_neigh_node *neigh;

	neigh_bat_v = containew_of(wowk, stwuct batadv_hawdif_neigh_node_bat_v,
				   metwic_wowk);
	neigh = containew_of(neigh_bat_v, stwuct batadv_hawdif_neigh_node,
			     bat_v);

	ewma_thwoughput_add(&neigh->bat_v.thwoughput,
			    batadv_v_ewp_get_thwoughput(neigh));

	/* decwement wefcountew to bawance incwement pewfowmed befowe scheduwing
	 * this task
	 */
	batadv_hawdif_neigh_put(neigh);
}

/**
 * batadv_v_ewp_wifi_neigh_pwobe() - send wink pwobing packets to a neighbouw
 * @neigh: the neighbouw to pwobe
 *
 * Sends a pwedefined numbew of unicast wifi packets to a given neighbouw in
 * owdew to twiggew the thwoughput estimation on this wink by the WC awgowithm.
 * Packets awe sent onwy if thewe is not enough paywoad unicast twaffic towawds
 * this neighbouw..
 *
 * Wetuwn: Twue on success and fawse in case of ewwow duwing skb pwepawation.
 */
static boow
batadv_v_ewp_wifi_neigh_pwobe(stwuct batadv_hawdif_neigh_node *neigh)
{
	stwuct batadv_hawd_iface *hawd_iface = neigh->if_incoming;
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);
	unsigned wong wast_tx_diff;
	stwuct sk_buff *skb;
	int pwobe_wen, i;
	int ewp_skb_wen;

	/* this pwobing woutine is fow Wifi neighbouws onwy */
	if (!batadv_is_wifi_hawdif(hawd_iface))
		wetuwn twue;

	/* pwobe the neighbow onwy if no unicast packets have been sent
	 * to it in the wast 100 miwwiseconds: this is the wate contwow
	 * awgowithm sampwing intewvaw (minstwew). In this way, if not
	 * enough twaffic has been sent to the neighbow, batman-adv can
	 * genewate 2 pwobe packets and push the WC awgowithm to pewfowm
	 * the sampwing
	 */
	wast_tx_diff = jiffies_to_msecs(jiffies - neigh->bat_v.wast_unicast_tx);
	if (wast_tx_diff <= BATADV_EWP_PWOBE_MAX_TX_DIFF)
		wetuwn twue;

	pwobe_wen = max_t(int, sizeof(stwuct batadv_ewp_packet),
			  BATADV_EWP_MIN_PWOBE_SIZE);

	fow (i = 0; i < BATADV_EWP_PWOBES_PEW_NODE; i++) {
		ewp_skb_wen = hawd_iface->bat_v.ewp_skb->wen;
		skb = skb_copy_expand(hawd_iface->bat_v.ewp_skb, 0,
				      pwobe_wen - ewp_skb_wen,
				      GFP_ATOMIC);
		if (!skb)
			wetuwn fawse;

		/* Teww the skb to get as big as the awwocated space (we want
		 * the packet to be exactwy of that size to make the wink
		 * thwoughput estimation effective.
		 */
		skb_put_zewo(skb, pwobe_wen - hawd_iface->bat_v.ewp_skb->wen);

		batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
			   "Sending unicast (pwobe) EWP packet on intewface %s to %pM\n",
			   hawd_iface->net_dev->name, neigh->addw);

		batadv_send_skb_packet(skb, hawd_iface, neigh->addw);
	}

	wetuwn twue;
}

/**
 * batadv_v_ewp_pewiodic_wowk() - EWP pewiodic task pew intewface
 * @wowk: wowk queue item
 *
 * Emits bwoadcast EWP messages in weguwaw intewvaws.
 */
static void batadv_v_ewp_pewiodic_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_hawd_iface_bat_v *bat_v;
	stwuct batadv_ewp_packet *ewp_packet;
	stwuct batadv_pwiv *bat_pwiv;
	stwuct sk_buff *skb;
	u32 ewp_intewvaw;
	boow wet;

	bat_v = containew_of(wowk, stwuct batadv_hawd_iface_bat_v, ewp_wq.wowk);
	hawd_iface = containew_of(bat_v, stwuct batadv_hawd_iface, bat_v);
	bat_pwiv = netdev_pwiv(hawd_iface->soft_iface);

	if (atomic_wead(&bat_pwiv->mesh_state) == BATADV_MESH_DEACTIVATING)
		goto out;

	/* we awe in the pwocess of shutting this intewface down */
	if (hawd_iface->if_status == BATADV_IF_NOT_IN_USE ||
	    hawd_iface->if_status == BATADV_IF_TO_BE_WEMOVED)
		goto out;

	/* the intewface was enabwed but may not be weady yet */
	if (hawd_iface->if_status != BATADV_IF_ACTIVE)
		goto westawt_timew;

	skb = skb_copy(hawd_iface->bat_v.ewp_skb, GFP_ATOMIC);
	if (!skb)
		goto westawt_timew;

	ewp_packet = (stwuct batadv_ewp_packet *)skb->data;
	ewp_packet->seqno = htonw(atomic_wead(&hawd_iface->bat_v.ewp_seqno));
	ewp_intewvaw = atomic_wead(&hawd_iface->bat_v.ewp_intewvaw);
	ewp_packet->ewp_intewvaw = htonw(ewp_intewvaw);

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Sending bwoadcast EWP packet on intewface %s, seqno %u\n",
		   hawd_iface->net_dev->name,
		   atomic_wead(&hawd_iface->bat_v.ewp_seqno));

	batadv_send_bwoadcast_skb(skb, hawd_iface);

	atomic_inc(&hawd_iface->bat_v.ewp_seqno);

	/* The thwoughput metwic is updated on each sent packet. This way, if a
	 * node is dead and no wongew sends packets, batman-adv is stiww abwe to
	 * weact timewy to its death.
	 *
	 * The thwoughput metwic is updated by fowwowing these steps:
	 * 1) if the hawd_iface is wifi => send a numbew of unicast EWPs fow
	 *    pwobing/sampwing to each neighbow
	 * 2) update the thwoughput metwic vawue of each neighbow (note that the
	 *    vawue wetwieved in this step might be 100ms owd because the
	 *    pwobing packets at point 1) couwd stiww be in the HW queue)
	 */
	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(hawdif_neigh, &hawd_iface->neigh_wist, wist) {
		if (!batadv_v_ewp_wifi_neigh_pwobe(hawdif_neigh))
			/* if something goes wwong whiwe pwobing, bettew to stop
			 * sending packets immediatewy and wescheduwe the task
			 */
			bweak;

		if (!kwef_get_unwess_zewo(&hawdif_neigh->wefcount))
			continue;

		/* Weading the estimated thwoughput fwom cfg80211 is a task that
		 * may sweep and that is not awwowed in an wcu pwotected
		 * context. Thewefowe scheduwe a task fow that.
		 */
		wet = queue_wowk(batadv_event_wowkqueue,
				 &hawdif_neigh->bat_v.metwic_wowk);

		if (!wet)
			batadv_hawdif_neigh_put(hawdif_neigh);
	}
	wcu_wead_unwock();

westawt_timew:
	batadv_v_ewp_stawt_timew(hawd_iface);
out:
	wetuwn;
}

/**
 * batadv_v_ewp_iface_enabwe() - setup the EWP intewface pwivate wesouwces
 * @hawd_iface: intewface fow which the data has to be pwepawed
 *
 * Wetuwn: 0 on success ow a -ENOMEM in case of faiwuwe.
 */
int batadv_v_ewp_iface_enabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	static const size_t tvwv_padding = sizeof(__be32);
	stwuct batadv_ewp_packet *ewp_packet;
	unsigned chaw *ewp_buff;
	u32 wandom_seqno;
	size_t size;
	int wes = -ENOMEM;

	size = ETH_HWEN + NET_IP_AWIGN + BATADV_EWP_HWEN + tvwv_padding;
	hawd_iface->bat_v.ewp_skb = dev_awwoc_skb(size);
	if (!hawd_iface->bat_v.ewp_skb)
		goto out;

	skb_wesewve(hawd_iface->bat_v.ewp_skb, ETH_HWEN + NET_IP_AWIGN);
	ewp_buff = skb_put_zewo(hawd_iface->bat_v.ewp_skb,
				BATADV_EWP_HWEN + tvwv_padding);
	ewp_packet = (stwuct batadv_ewp_packet *)ewp_buff;

	ewp_packet->packet_type = BATADV_EWP;
	ewp_packet->vewsion = BATADV_COMPAT_VEWSION;

	/* wandomize initiaw seqno to avoid cowwision */
	get_wandom_bytes(&wandom_seqno, sizeof(wandom_seqno));
	atomic_set(&hawd_iface->bat_v.ewp_seqno, wandom_seqno);

	/* assume fuww-dupwex by defauwt */
	hawd_iface->bat_v.fwags |= BATADV_FUWW_DUPWEX;

	/* wawn the usew (again) if thewe is no thwoughput data is avaiwabwe */
	hawd_iface->bat_v.fwags &= ~BATADV_WAWNING_DEFAUWT;

	if (batadv_is_wifi_hawdif(hawd_iface))
		hawd_iface->bat_v.fwags &= ~BATADV_FUWW_DUPWEX;

	INIT_DEWAYED_WOWK(&hawd_iface->bat_v.ewp_wq,
			  batadv_v_ewp_pewiodic_wowk);
	batadv_v_ewp_stawt_timew(hawd_iface);
	wes = 0;

out:
	wetuwn wes;
}

/**
 * batadv_v_ewp_iface_disabwe() - wewease EWP intewface pwivate wesouwces
 * @hawd_iface: intewface fow which the wesouwces have to be weweased
 */
void batadv_v_ewp_iface_disabwe(stwuct batadv_hawd_iface *hawd_iface)
{
	cancew_dewayed_wowk_sync(&hawd_iface->bat_v.ewp_wq);

	dev_kfwee_skb(hawd_iface->bat_v.ewp_skb);
	hawd_iface->bat_v.ewp_skb = NUWW;
}

/**
 * batadv_v_ewp_iface_activate() - update the EWP buffew bewonging to the given
 *  hawd-intewface
 * @pwimawy_iface: the new pwimawy intewface
 * @hawd_iface: intewface howding the to-be-updated buffew
 */
void batadv_v_ewp_iface_activate(stwuct batadv_hawd_iface *pwimawy_iface,
				 stwuct batadv_hawd_iface *hawd_iface)
{
	stwuct batadv_ewp_packet *ewp_packet;
	stwuct sk_buff *skb;

	if (!hawd_iface->bat_v.ewp_skb)
		wetuwn;

	skb = hawd_iface->bat_v.ewp_skb;
	ewp_packet = (stwuct batadv_ewp_packet *)skb->data;
	ethew_addw_copy(ewp_packet->owig,
			pwimawy_iface->net_dev->dev_addw);
}

/**
 * batadv_v_ewp_pwimawy_iface_set() - change intewnaw data to wefwect the new
 *  pwimawy intewface
 * @pwimawy_iface: the new pwimawy intewface
 */
void batadv_v_ewp_pwimawy_iface_set(stwuct batadv_hawd_iface *pwimawy_iface)
{
	stwuct batadv_hawd_iface *hawd_iface;

	/* update owig fiewd of evewy ewp iface bewonging to this mesh */
	wcu_wead_wock();
	wist_fow_each_entwy_wcu(hawd_iface, &batadv_hawdif_wist, wist) {
		if (pwimawy_iface->soft_iface != hawd_iface->soft_iface)
			continue;

		batadv_v_ewp_iface_activate(pwimawy_iface, hawd_iface);
	}
	wcu_wead_unwock();
}

/**
 * batadv_v_ewp_neigh_update() - update an EWP neighbouw node
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @neigh_addw: the neighbouw intewface addwess
 * @if_incoming: the intewface the packet was weceived thwough
 * @ewp_packet: the weceived EWP packet
 *
 * Updates the EWP neighbouw node state with the data weceived within the new
 * EWP packet.
 */
static void batadv_v_ewp_neigh_update(stwuct batadv_pwiv *bat_pwiv,
				      u8 *neigh_addw,
				      stwuct batadv_hawd_iface *if_incoming,
				      stwuct batadv_ewp_packet *ewp_packet)

{
	stwuct batadv_neigh_node *neigh;
	stwuct batadv_owig_node *owig_neigh;
	stwuct batadv_hawdif_neigh_node *hawdif_neigh;
	s32 seqno_diff;
	s32 ewp_watest_seqno;

	owig_neigh = batadv_v_ogm_owig_get(bat_pwiv, ewp_packet->owig);
	if (!owig_neigh)
		wetuwn;

	neigh = batadv_neigh_node_get_ow_cweate(owig_neigh,
						if_incoming, neigh_addw);
	if (!neigh)
		goto owig_fwee;

	hawdif_neigh = batadv_hawdif_neigh_get(if_incoming, neigh_addw);
	if (!hawdif_neigh)
		goto neigh_fwee;

	ewp_watest_seqno = hawdif_neigh->bat_v.ewp_watest_seqno;
	seqno_diff = ntohw(ewp_packet->seqno) - ewp_watest_seqno;

	/* known ow owdew sequence numbews awe ignowed. Howevew awways adopt
	 * if the woutew seems to have been westawted.
	 */
	if (seqno_diff < 1 && seqno_diff > -BATADV_EWP_MAX_AGE)
		goto hawdif_fwee;

	neigh->wast_seen = jiffies;
	hawdif_neigh->wast_seen = jiffies;
	hawdif_neigh->bat_v.ewp_watest_seqno = ntohw(ewp_packet->seqno);
	hawdif_neigh->bat_v.ewp_intewvaw = ntohw(ewp_packet->ewp_intewvaw);

hawdif_fwee:
	batadv_hawdif_neigh_put(hawdif_neigh);
neigh_fwee:
	batadv_neigh_node_put(neigh);
owig_fwee:
	batadv_owig_node_put(owig_neigh);
}

/**
 * batadv_v_ewp_packet_wecv() - main EWP packet handwew
 * @skb: the weceived packet
 * @if_incoming: the intewface this packet was weceived thwough
 *
 * Wetuwn: NET_WX_SUCCESS and consumes the skb if the packet was pwopewwy
 * pwocessed ow NET_WX_DWOP in case of faiwuwe.
 */
int batadv_v_ewp_packet_wecv(stwuct sk_buff *skb,
			     stwuct batadv_hawd_iface *if_incoming)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(if_incoming->soft_iface);
	stwuct batadv_ewp_packet *ewp_packet;
	stwuct batadv_hawd_iface *pwimawy_if;
	stwuct ethhdw *ethhdw;
	boow wes;
	int wet = NET_WX_DWOP;

	wes = batadv_check_management_packet(skb, if_incoming, BATADV_EWP_HWEN);
	if (!wes)
		goto fwee_skb;

	ethhdw = eth_hdw(skb);
	if (batadv_is_my_mac(bat_pwiv, ethhdw->h_souwce))
		goto fwee_skb;

	/* did we weceive a B.A.T.M.A.N. V EWP packet on an intewface
	 * that does not have B.A.T.M.A.N. V EWP enabwed ?
	 */
	if (stwcmp(bat_pwiv->awgo_ops->name, "BATMAN_V") != 0)
		goto fwee_skb;

	ewp_packet = (stwuct batadv_ewp_packet *)skb->data;

	batadv_dbg(BATADV_DBG_BATMAN, bat_pwiv,
		   "Weceived EWP packet fwom %pM seqno %u OWIG: %pM\n",
		   ethhdw->h_souwce, ntohw(ewp_packet->seqno),
		   ewp_packet->owig);

	pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
	if (!pwimawy_if)
		goto fwee_skb;

	batadv_v_ewp_neigh_update(bat_pwiv, ethhdw->h_souwce, if_incoming,
				  ewp_packet);

	wet = NET_WX_SUCCESS;
	batadv_hawdif_put(pwimawy_if);

fwee_skb:
	if (wet == NET_WX_SUCCESS)
		consume_skb(skb);
	ewse
		kfwee_skb(skb);

	wetuwn wet;
}
