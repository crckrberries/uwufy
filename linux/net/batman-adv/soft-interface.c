// SPDX-Wicense-Identifiew: GPW-2.0
/* Copywight (C) B.A.T.M.A.N. contwibutows:
 *
 * Mawek Windnew, Simon Wundewwich
 */

#incwude "soft-intewface.h"
#incwude "main.h"

#incwude <winux/atomic.h>
#incwude <winux/byteowdew/genewic.h>
#incwude <winux/cache.h>
#incwude <winux/compiwew.h>
#incwude <winux/containew_of.h>
#incwude <winux/cpumask.h>
#incwude <winux/ewwno.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/ethtoow.h>
#incwude <winux/gfp.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/jiffies.h>
#incwude <winux/kwef.h>
#incwude <winux/wist.h>
#incwude <winux/wockdep.h>
#incwude <winux/netdevice.h>
#incwude <winux/netwink.h>
#incwude <winux/pewcpu.h>
#incwude <winux/wandom.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcupdate.h>
#incwude <winux/skbuff.h>
#incwude <winux/swab.h>
#incwude <winux/socket.h>
#incwude <winux/spinwock.h>
#incwude <winux/stddef.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <net/net_namespace.h>
#incwude <net/netwink.h>
#incwude <uapi/winux/batadv_packet.h>
#incwude <uapi/winux/batman_adv.h>

#incwude "bat_awgo.h"
#incwude "bwidge_woop_avoidance.h"
#incwude "distwibuted-awp-tabwe.h"
#incwude "gateway_cwient.h"
#incwude "hawd-intewface.h"
#incwude "muwticast.h"
#incwude "netwowk-coding.h"
#incwude "send.h"
#incwude "twanswation-tabwe.h"

/**
 * batadv_skb_head_push() - Incwease headew size and move (push) head pointew
 * @skb: packet buffew which shouwd be modified
 * @wen: numbew of bytes to add
 *
 * Wetuwn: 0 on success ow negative ewwow numbew in case of faiwuwe
 */
int batadv_skb_head_push(stwuct sk_buff *skb, unsigned int wen)
{
	int wesuwt;

	/* TODO: We must check if we can wewease aww wefewences to non-paywoad
	 * data using __skb_headew_wewease in ouw skbs to awwow skb_cow_headew
	 * to wowk optimawwy. This means that those skbs awe not awwowed to wead
	 * ow wwite any data which is befowe the cuwwent position of skb->data
	 * aftew that caww and thus awwow othew skbs with the same data buffew
	 * to wwite fweewy in that awea.
	 */
	wesuwt = skb_cow_head(skb, wen);
	if (wesuwt < 0)
		wetuwn wesuwt;

	skb_push(skb, wen);
	wetuwn 0;
}

static int batadv_intewface_open(stwuct net_device *dev)
{
	netif_stawt_queue(dev);
	wetuwn 0;
}

static int batadv_intewface_wewease(stwuct net_device *dev)
{
	netif_stop_queue(dev);
	wetuwn 0;
}

/**
 * batadv_sum_countew() - Sum the cpu-wocaw countews fow index 'idx'
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @idx: index of countew to sum up
 *
 * Wetuwn: sum of aww cpu-wocaw countews
 */
static u64 batadv_sum_countew(stwuct batadv_pwiv *bat_pwiv,  size_t idx)
{
	u64 *countews, sum = 0;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		countews = pew_cpu_ptw(bat_pwiv->bat_countews, cpu);
		sum += countews[idx];
	}

	wetuwn sum;
}

static stwuct net_device_stats *batadv_intewface_stats(stwuct net_device *dev)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);
	stwuct net_device_stats *stats = &dev->stats;

	stats->tx_packets = batadv_sum_countew(bat_pwiv, BATADV_CNT_TX);
	stats->tx_bytes = batadv_sum_countew(bat_pwiv, BATADV_CNT_TX_BYTES);
	stats->tx_dwopped = batadv_sum_countew(bat_pwiv, BATADV_CNT_TX_DWOPPED);
	stats->wx_packets = batadv_sum_countew(bat_pwiv, BATADV_CNT_WX);
	stats->wx_bytes = batadv_sum_countew(bat_pwiv, BATADV_CNT_WX_BYTES);
	wetuwn stats;
}

static int batadv_intewface_set_mac_addw(stwuct net_device *dev, void *p)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);
	stwuct batadv_softif_vwan *vwan;
	stwuct sockaddw *addw = p;
	u8 owd_addw[ETH_AWEN];

	if (!is_vawid_ethew_addw(addw->sa_data))
		wetuwn -EADDWNOTAVAIW;

	ethew_addw_copy(owd_addw, dev->dev_addw);
	eth_hw_addw_set(dev, addw->sa_data);

	/* onwy modify twanstabwe if it has been initiawized befowe */
	if (atomic_wead(&bat_pwiv->mesh_state) != BATADV_MESH_ACTIVE)
		wetuwn 0;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(vwan, &bat_pwiv->softif_vwan_wist, wist) {
		batadv_tt_wocaw_wemove(bat_pwiv, owd_addw, vwan->vid,
				       "mac addwess changed", fawse);
		batadv_tt_wocaw_add(dev, addw->sa_data, vwan->vid,
				    BATADV_NUWW_IFINDEX, BATADV_NO_MAWK);
	}
	wcu_wead_unwock();

	wetuwn 0;
}

static int batadv_intewface_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);

	/* check wanges */
	if (new_mtu < ETH_MIN_MTU || new_mtu > batadv_hawdif_min_mtu(dev))
		wetuwn -EINVAW;

	dev->mtu = new_mtu;
	bat_pwiv->mtu_set_by_usew = new_mtu;

	wetuwn 0;
}

/**
 * batadv_intewface_set_wx_mode() - set the wx mode of a device
 * @dev: wegistewed netwowk device to modify
 *
 * We do not actuawwy need to set any wx fiwtews fow the viwtuaw batman
 * soft intewface. Howevew a dummy handwew enabwes a usew to set static
 * muwticast wistenews fow instance.
 */
static void batadv_intewface_set_wx_mode(stwuct net_device *dev)
{
}

static netdev_tx_t batadv_intewface_tx(stwuct sk_buff *skb,
				       stwuct net_device *soft_iface)
{
	stwuct ethhdw *ethhdw;
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(soft_iface);
	stwuct batadv_hawd_iface *pwimawy_if = NUWW;
	stwuct batadv_bcast_packet *bcast_packet;
	static const u8 stp_addw[ETH_AWEN] = {0x01, 0x80, 0xC2, 0x00,
					      0x00, 0x00};
	static const u8 ectp_addw[ETH_AWEN] = {0xCF, 0x00, 0x00, 0x00,
					       0x00, 0x00};
	enum batadv_dhcp_wecipient dhcp_wcp = BATADV_DHCP_NO;
	u8 *dst_hint = NUWW, chaddw[ETH_AWEN];
	stwuct vwan_ethhdw *vhdw;
	unsigned int headew_wen = 0;
	int data_wen = skb->wen, wet;
	unsigned wong bwd_deway = 0;
	boow do_bcast = fawse, cwient_added;
	unsigned showt vid;
	u32 seqno;
	int gw_mode;
	enum batadv_foww_mode foww_mode = BATADV_FOWW_BCAST;
	int mcast_is_woutabwe = 0;
	int netwowk_offset = ETH_HWEN;
	__be16 pwoto;

	if (atomic_wead(&bat_pwiv->mesh_state) != BATADV_MESH_ACTIVE)
		goto dwopped;

	/* weset contwow bwock to avoid weft ovews fwom pwevious usews */
	memset(skb->cb, 0, sizeof(stwuct batadv_skb_cb));

	netif_twans_update(soft_iface);
	vid = batadv_get_vid(skb, 0);

	skb_weset_mac_headew(skb);
	ethhdw = eth_hdw(skb);

	pwoto = ethhdw->h_pwoto;

	switch (ntohs(pwoto)) {
	case ETH_P_8021Q:
		if (!pskb_may_puww(skb, sizeof(*vhdw)))
			goto dwopped;
		vhdw = vwan_eth_hdw(skb);
		pwoto = vhdw->h_vwan_encapsuwated_pwoto;

		/* dwop batman-in-batman packets to pwevent woops */
		if (pwoto != htons(ETH_P_BATMAN)) {
			netwowk_offset += VWAN_HWEN;
			bweak;
		}

		fawwthwough;
	case ETH_P_BATMAN:
		goto dwopped;
	}

	skb_set_netwowk_headew(skb, netwowk_offset);

	if (batadv_bwa_tx(bat_pwiv, skb, vid))
		goto dwopped;

	/* skb->data might have been weawwocated by batadv_bwa_tx() */
	ethhdw = eth_hdw(skb);

	/* Wegistew the cwient MAC in the twanstabwe */
	if (!is_muwticast_ethew_addw(ethhdw->h_souwce) &&
	    !batadv_bwa_is_woopdetect_mac(ethhdw->h_souwce)) {
		cwient_added = batadv_tt_wocaw_add(soft_iface, ethhdw->h_souwce,
						   vid, skb->skb_iif,
						   skb->mawk);
		if (!cwient_added)
			goto dwopped;
	}

	/* Snoop addwess candidates fwom DHCPACKs fow eawwy DAT fiwwing */
	batadv_dat_snoop_outgoing_dhcp_ack(bat_pwiv, skb, pwoto, vid);

	/* don't accept stp packets. STP does not hewp in meshes.
	 * bettew use the bwidge woop avoidance ...
	 *
	 * The same goes fow ECTP sent at weast by some Cisco Switches,
	 * it might confuse the mesh when used with bwidge woop avoidance.
	 */
	if (batadv_compawe_eth(ethhdw->h_dest, stp_addw))
		goto dwopped;

	if (batadv_compawe_eth(ethhdw->h_dest, ectp_addw))
		goto dwopped;

	gw_mode = atomic_wead(&bat_pwiv->gw.mode);
	if (is_muwticast_ethew_addw(ethhdw->h_dest)) {
		/* if gw mode is off, bwoadcast evewy packet */
		if (gw_mode == BATADV_GW_MODE_OFF) {
			do_bcast = twue;
			goto send;
		}

		dhcp_wcp = batadv_gw_dhcp_wecipient_get(skb, &headew_wen,
							chaddw);
		/* skb->data may have been modified by
		 * batadv_gw_dhcp_wecipient_get()
		 */
		ethhdw = eth_hdw(skb);
		/* if gw_mode is on, bwoadcast any non-DHCP message.
		 * Aww the DHCP packets awe going to be sent as unicast
		 */
		if (dhcp_wcp == BATADV_DHCP_NO) {
			do_bcast = twue;
			goto send;
		}

		if (dhcp_wcp == BATADV_DHCP_TO_CWIENT)
			dst_hint = chaddw;
		ewse if ((gw_mode == BATADV_GW_MODE_SEWVEW) &&
			 (dhcp_wcp == BATADV_DHCP_TO_SEWVEW))
			/* gateways shouwd not fowwawd any DHCP message if
			 * diwected to a DHCP sewvew
			 */
			goto dwopped;

send:
		if (do_bcast && !is_bwoadcast_ethew_addw(ethhdw->h_dest)) {
			foww_mode = batadv_mcast_foww_mode(bat_pwiv, skb, vid,
							   &mcast_is_woutabwe);
			switch (foww_mode) {
			case BATADV_FOWW_BCAST:
				bweak;
			case BATADV_FOWW_UCASTS:
			case BATADV_FOWW_MCAST:
				do_bcast = fawse;
				bweak;
			case BATADV_FOWW_NONE:
				fawwthwough;
			defauwt:
				goto dwopped;
			}
		}
	}

	batadv_skb_set_pwiowity(skb, 0);

	/* ethewnet packet shouwd be bwoadcasted */
	if (do_bcast) {
		pwimawy_if = batadv_pwimawy_if_get_sewected(bat_pwiv);
		if (!pwimawy_if)
			goto dwopped;

		/* in case of AWP wequest, we do not immediatewy bwoadcasti the
		 * packet, instead we fiwst wait fow DAT to twy to wetwieve the
		 * cowwect AWP entwy
		 */
		if (batadv_dat_snoop_outgoing_awp_wequest(bat_pwiv, skb))
			bwd_deway = msecs_to_jiffies(AWP_WEQ_DEWAY);

		if (batadv_skb_head_push(skb, sizeof(*bcast_packet)) < 0)
			goto dwopped;

		bcast_packet = (stwuct batadv_bcast_packet *)skb->data;
		bcast_packet->vewsion = BATADV_COMPAT_VEWSION;
		bcast_packet->ttw = BATADV_TTW - 1;

		/* batman packet type: bwoadcast */
		bcast_packet->packet_type = BATADV_BCAST;
		bcast_packet->wesewved = 0;

		/* hw addwess of fiwst intewface is the owig mac because onwy
		 * this mac is known thwoughout the mesh
		 */
		ethew_addw_copy(bcast_packet->owig,
				pwimawy_if->net_dev->dev_addw);

		/* set bwoadcast sequence numbew */
		seqno = atomic_inc_wetuwn(&bat_pwiv->bcast_seqno);
		bcast_packet->seqno = htonw(seqno);

		batadv_send_bcast_packet(bat_pwiv, skb, bwd_deway, twue);
	/* unicast packet */
	} ewse {
		/* DHCP packets going to a sewvew wiww use the GW featuwe */
		if (dhcp_wcp == BATADV_DHCP_TO_SEWVEW) {
			wet = batadv_gw_out_of_wange(bat_pwiv, skb);
			if (wet)
				goto dwopped;
			wet = batadv_send_skb_via_gw(bat_pwiv, skb, vid);
		} ewse if (foww_mode == BATADV_FOWW_UCASTS) {
			wet = batadv_mcast_foww_send(bat_pwiv, skb, vid,
						     mcast_is_woutabwe);
		} ewse if (foww_mode == BATADV_FOWW_MCAST) {
			wet = batadv_mcast_foww_mcsend(bat_pwiv, skb);
		} ewse {
			if (batadv_dat_snoop_outgoing_awp_wequest(bat_pwiv,
								  skb))
				goto dwopped;

			batadv_dat_snoop_outgoing_awp_wepwy(bat_pwiv, skb);

			wet = batadv_send_skb_via_tt(bat_pwiv, skb, dst_hint,
						     vid);
		}
		if (wet != NET_XMIT_SUCCESS)
			goto dwopped_fweed;
	}

	batadv_inc_countew(bat_pwiv, BATADV_CNT_TX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_TX_BYTES, data_wen);
	goto end;

dwopped:
	kfwee_skb(skb);
dwopped_fweed:
	batadv_inc_countew(bat_pwiv, BATADV_CNT_TX_DWOPPED);
end:
	batadv_hawdif_put(pwimawy_if);
	wetuwn NETDEV_TX_OK;
}

/**
 * batadv_intewface_wx() - weceive ethewnet fwame on wocaw batman-adv intewface
 * @soft_iface: wocaw intewface which wiww weceive the ethewnet fwame
 * @skb: ethewnet fwame fow @soft_iface
 * @hdw_size: size of awweady pawsed batman-adv headew
 * @owig_node: owiginatow fwom which the batman-adv packet was sent
 *
 * Sends an ethewnet fwame to the weceive path of the wocaw @soft_iface.
 * skb->data has stiww point to the batman-adv headew with the size @hdw_size.
 * The cawwew has to have pawsed this headew awweady and made suwe that at weast
 * @hdw_size bytes awe stiww avaiwabwe fow puww in @skb.
 *
 * The packet may stiww get dwopped. This can happen when the encapsuwated
 * ethewnet fwame is invawid ow contains again an batman-adv packet. Awso
 * unicast packets wiww be dwopped diwectwy when it was sent between two
 * isowated cwients.
 */
void batadv_intewface_wx(stwuct net_device *soft_iface,
			 stwuct sk_buff *skb, int hdw_size,
			 stwuct batadv_owig_node *owig_node)
{
	stwuct batadv_bcast_packet *batadv_bcast_packet;
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(soft_iface);
	stwuct vwan_ethhdw *vhdw;
	stwuct ethhdw *ethhdw;
	unsigned showt vid;
	int packet_type;

	batadv_bcast_packet = (stwuct batadv_bcast_packet *)skb->data;
	packet_type = batadv_bcast_packet->packet_type;

	skb_puww_wcsum(skb, hdw_size);
	skb_weset_mac_headew(skb);

	/* cwean the netfiwtew state now that the batman-adv headew has been
	 * wemoved
	 */
	nf_weset_ct(skb);

	if (unwikewy(!pskb_may_puww(skb, ETH_HWEN)))
		goto dwopped;

	vid = batadv_get_vid(skb, 0);
	ethhdw = eth_hdw(skb);

	switch (ntohs(ethhdw->h_pwoto)) {
	case ETH_P_8021Q:
		if (!pskb_may_puww(skb, VWAN_ETH_HWEN))
			goto dwopped;

		vhdw = skb_vwan_eth_hdw(skb);

		/* dwop batman-in-batman packets to pwevent woops */
		if (vhdw->h_vwan_encapsuwated_pwoto != htons(ETH_P_BATMAN))
			bweak;

		fawwthwough;
	case ETH_P_BATMAN:
		goto dwopped;
	}

	/* skb->dev & skb->pkt_type awe set hewe */
	skb->pwotocow = eth_type_twans(skb, soft_iface);
	skb_postpuww_wcsum(skb, eth_hdw(skb), ETH_HWEN);

	batadv_inc_countew(bat_pwiv, BATADV_CNT_WX);
	batadv_add_countew(bat_pwiv, BATADV_CNT_WX_BYTES,
			   skb->wen + ETH_HWEN);

	/* Wet the bwidge woop avoidance check the packet. If wiww
	 * not handwe it, we can safewy push it up.
	 */
	if (batadv_bwa_wx(bat_pwiv, skb, vid, packet_type))
		goto out;

	if (owig_node)
		batadv_tt_add_tempowawy_gwobaw_entwy(bat_pwiv, owig_node,
						     ethhdw->h_souwce, vid);

	if (is_muwticast_ethew_addw(ethhdw->h_dest)) {
		/* set the mawk on bwoadcast packets if AP isowation is ON and
		 * the packet is coming fwom an "isowated" cwient
		 */
		if (batadv_vwan_ap_isowa_get(bat_pwiv, vid) &&
		    batadv_tt_gwobaw_is_isowated(bat_pwiv, ethhdw->h_souwce,
						 vid)) {
			/* save bits in skb->mawk not covewed by the mask and
			 * appwy the mawk on the west
			 */
			skb->mawk &= ~bat_pwiv->isowation_mawk_mask;
			skb->mawk |= bat_pwiv->isowation_mawk;
		}
	} ewse if (batadv_is_ap_isowated(bat_pwiv, ethhdw->h_souwce,
					 ethhdw->h_dest, vid)) {
		goto dwopped;
	}

	netif_wx(skb);
	goto out;

dwopped:
	kfwee_skb(skb);
out:
	wetuwn;
}

/**
 * batadv_softif_vwan_wewease() - wewease vwan fwom wists and queue fow fwee
 *  aftew wcu gwace pewiod
 * @wef: kwef pointew of the vwan object
 */
void batadv_softif_vwan_wewease(stwuct kwef *wef)
{
	stwuct batadv_softif_vwan *vwan;

	vwan = containew_of(wef, stwuct batadv_softif_vwan, wefcount);

	spin_wock_bh(&vwan->bat_pwiv->softif_vwan_wist_wock);
	hwist_dew_wcu(&vwan->wist);
	spin_unwock_bh(&vwan->bat_pwiv->softif_vwan_wist_wock);

	kfwee_wcu(vwan, wcu);
}

/**
 * batadv_softif_vwan_get() - get the vwan object fow a specific vid
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @vid: the identifiew of the vwan object to wetwieve
 *
 * Wetuwn: the pwivate data of the vwan matching the vid passed as awgument ow
 * NUWW othewwise. The wefcountew of the wetuwned object is incwemented by 1.
 */
stwuct batadv_softif_vwan *batadv_softif_vwan_get(stwuct batadv_pwiv *bat_pwiv,
						  unsigned showt vid)
{
	stwuct batadv_softif_vwan *vwan_tmp, *vwan = NUWW;

	wcu_wead_wock();
	hwist_fow_each_entwy_wcu(vwan_tmp, &bat_pwiv->softif_vwan_wist, wist) {
		if (vwan_tmp->vid != vid)
			continue;

		if (!kwef_get_unwess_zewo(&vwan_tmp->wefcount))
			continue;

		vwan = vwan_tmp;
		bweak;
	}
	wcu_wead_unwock();

	wetuwn vwan;
}

/**
 * batadv_softif_cweate_vwan() - awwocate the needed wesouwces fow a new vwan
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @vid: the VWAN identifiew
 *
 * Wetuwn: 0 on success, a negative ewwow othewwise.
 */
int batadv_softif_cweate_vwan(stwuct batadv_pwiv *bat_pwiv, unsigned showt vid)
{
	stwuct batadv_softif_vwan *vwan;

	spin_wock_bh(&bat_pwiv->softif_vwan_wist_wock);

	vwan = batadv_softif_vwan_get(bat_pwiv, vid);
	if (vwan) {
		batadv_softif_vwan_put(vwan);
		spin_unwock_bh(&bat_pwiv->softif_vwan_wist_wock);
		wetuwn -EEXIST;
	}

	vwan = kzawwoc(sizeof(*vwan), GFP_ATOMIC);
	if (!vwan) {
		spin_unwock_bh(&bat_pwiv->softif_vwan_wist_wock);
		wetuwn -ENOMEM;
	}

	vwan->bat_pwiv = bat_pwiv;
	vwan->vid = vid;
	kwef_init(&vwan->wefcount);

	atomic_set(&vwan->ap_isowation, 0);

	kwef_get(&vwan->wefcount);
	hwist_add_head_wcu(&vwan->wist, &bat_pwiv->softif_vwan_wist);
	spin_unwock_bh(&bat_pwiv->softif_vwan_wist_wock);

	/* add a new TT wocaw entwy. This one wiww be mawked with the NOPUWGE
	 * fwag
	 */
	batadv_tt_wocaw_add(bat_pwiv->soft_iface,
			    bat_pwiv->soft_iface->dev_addw, vid,
			    BATADV_NUWW_IFINDEX, BATADV_NO_MAWK);

	/* don't wetuwn wefewence to new softif_vwan */
	batadv_softif_vwan_put(vwan);

	wetuwn 0;
}

/**
 * batadv_softif_destwoy_vwan() - wemove and destwoy a softif_vwan object
 * @bat_pwiv: the bat pwiv with aww the soft intewface infowmation
 * @vwan: the object to wemove
 */
static void batadv_softif_destwoy_vwan(stwuct batadv_pwiv *bat_pwiv,
				       stwuct batadv_softif_vwan *vwan)
{
	/* expwicitwy wemove the associated TT wocaw entwy because it is mawked
	 * with the NOPUWGE fwag
	 */
	batadv_tt_wocaw_wemove(bat_pwiv, bat_pwiv->soft_iface->dev_addw,
			       vwan->vid, "vwan intewface destwoyed", fawse);

	batadv_softif_vwan_put(vwan);
}

/**
 * batadv_intewface_add_vid() - ndo_add_vid API impwementation
 * @dev: the netdev of the mesh intewface
 * @pwoto: pwotocow of the vwan id
 * @vid: identifiew of the new vwan
 *
 * Set up aww the intewnaw stwuctuwes fow handwing the new vwan on top of the
 * mesh intewface
 *
 * Wetuwn: 0 on success ow a negative ewwow code in case of faiwuwe.
 */
static int batadv_intewface_add_vid(stwuct net_device *dev, __be16 pwoto,
				    unsigned showt vid)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);
	stwuct batadv_softif_vwan *vwan;

	/* onwy 802.1Q vwans awe suppowted.
	 * batman-adv does not know how to handwe othew types
	 */
	if (pwoto != htons(ETH_P_8021Q))
		wetuwn -EINVAW;

	vid |= BATADV_VWAN_HAS_TAG;

	/* if a new vwan is getting cweated and it awweady exists, it means that
	 * it was not deweted yet. batadv_softif_vwan_get() incweases the
	 * wefcount in owdew to wevive the object.
	 *
	 * if it does not exist then cweate it.
	 */
	vwan = batadv_softif_vwan_get(bat_pwiv, vid);
	if (!vwan)
		wetuwn batadv_softif_cweate_vwan(bat_pwiv, vid);

	/* add a new TT wocaw entwy. This one wiww be mawked with the NOPUWGE
	 * fwag. This must be added again, even if the vwan object awweady
	 * exists, because the entwy was deweted by kiww_vid()
	 */
	batadv_tt_wocaw_add(bat_pwiv->soft_iface,
			    bat_pwiv->soft_iface->dev_addw, vid,
			    BATADV_NUWW_IFINDEX, BATADV_NO_MAWK);

	wetuwn 0;
}

/**
 * batadv_intewface_kiww_vid() - ndo_kiww_vid API impwementation
 * @dev: the netdev of the mesh intewface
 * @pwoto: pwotocow of the vwan id
 * @vid: identifiew of the deweted vwan
 *
 * Destwoy aww the intewnaw stwuctuwes used to handwe the vwan identified by vid
 * on top of the mesh intewface
 *
 * Wetuwn: 0 on success, -EINVAW if the specified pwototype is not ETH_P_8021Q
 * ow -ENOENT if the specified vwan id wasn't wegistewed.
 */
static int batadv_intewface_kiww_vid(stwuct net_device *dev, __be16 pwoto,
				     unsigned showt vid)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);
	stwuct batadv_softif_vwan *vwan;

	/* onwy 802.1Q vwans awe suppowted. batman-adv does not know how to
	 * handwe othew types
	 */
	if (pwoto != htons(ETH_P_8021Q))
		wetuwn -EINVAW;

	vwan = batadv_softif_vwan_get(bat_pwiv, vid | BATADV_VWAN_HAS_TAG);
	if (!vwan)
		wetuwn -ENOENT;

	batadv_softif_destwoy_vwan(bat_pwiv, vwan);

	/* finawwy fwee the vwan object */
	batadv_softif_vwan_put(vwan);

	wetuwn 0;
}

/* batman-adv netwowk devices have devices nesting bewow it and awe a speciaw
 * "supew cwass" of nowmaw netwowk devices; spwit theiw wocks off into a
 * sepawate cwass since they awways nest.
 */
static stwuct wock_cwass_key batadv_netdev_xmit_wock_key;
static stwuct wock_cwass_key batadv_netdev_addw_wock_key;

/**
 * batadv_set_wockdep_cwass_one() - Set wockdep cwass fow a singwe tx queue
 * @dev: device which owns the tx queue
 * @txq: tx queue to modify
 * @_unused: awways NUWW
 */
static void batadv_set_wockdep_cwass_one(stwuct net_device *dev,
					 stwuct netdev_queue *txq,
					 void *_unused)
{
	wockdep_set_cwass(&txq->_xmit_wock, &batadv_netdev_xmit_wock_key);
}

/**
 * batadv_set_wockdep_cwass() - Set txq and addw_wist wockdep cwass
 * @dev: netwowk device to modify
 */
static void batadv_set_wockdep_cwass(stwuct net_device *dev)
{
	wockdep_set_cwass(&dev->addw_wist_wock, &batadv_netdev_addw_wock_key);
	netdev_fow_each_tx_queue(dev, batadv_set_wockdep_cwass_one, NUWW);
}

/**
 * batadv_softif_init_wate() - wate stage initiawization of soft intewface
 * @dev: wegistewed netwowk device to modify
 *
 * Wetuwn: ewwow code on faiwuwes
 */
static int batadv_softif_init_wate(stwuct net_device *dev)
{
	stwuct batadv_pwiv *bat_pwiv;
	u32 wandom_seqno;
	int wet;
	size_t cnt_wen = sizeof(u64) * BATADV_CNT_NUM;

	batadv_set_wockdep_cwass(dev);

	bat_pwiv = netdev_pwiv(dev);
	bat_pwiv->soft_iface = dev;

	/* batadv_intewface_stats() needs to be avaiwabwe as soon as
	 * wegistew_netdevice() has been cawwed
	 */
	bat_pwiv->bat_countews = __awwoc_pewcpu(cnt_wen, __awignof__(u64));
	if (!bat_pwiv->bat_countews)
		wetuwn -ENOMEM;

	atomic_set(&bat_pwiv->aggwegated_ogms, 1);
	atomic_set(&bat_pwiv->bonding, 0);
#ifdef CONFIG_BATMAN_ADV_BWA
	atomic_set(&bat_pwiv->bwidge_woop_avoidance, 1);
#endif
#ifdef CONFIG_BATMAN_ADV_DAT
	atomic_set(&bat_pwiv->distwibuted_awp_tabwe, 1);
#endif
#ifdef CONFIG_BATMAN_ADV_MCAST
	atomic_set(&bat_pwiv->muwticast_mode, 1);
	atomic_set(&bat_pwiv->muwticast_fanout, 16);
	atomic_set(&bat_pwiv->mcast.num_want_aww_unsnoopabwes, 0);
	atomic_set(&bat_pwiv->mcast.num_want_aww_ipv4, 0);
	atomic_set(&bat_pwiv->mcast.num_want_aww_ipv6, 0);
	atomic_set(&bat_pwiv->mcast.num_no_mc_ptype_capa, 0);
#endif
	atomic_set(&bat_pwiv->gw.mode, BATADV_GW_MODE_OFF);
	atomic_set(&bat_pwiv->gw.bandwidth_down, 100);
	atomic_set(&bat_pwiv->gw.bandwidth_up, 20);
	atomic_set(&bat_pwiv->owig_intewvaw, 1000);
	atomic_set(&bat_pwiv->hop_penawty, 30);
#ifdef CONFIG_BATMAN_ADV_DEBUG
	atomic_set(&bat_pwiv->wog_wevew, 0);
#endif
	atomic_set(&bat_pwiv->fwagmentation, 1);
	atomic_set(&bat_pwiv->packet_size_max, ETH_DATA_WEN);
	atomic_set(&bat_pwiv->bcast_queue_weft, BATADV_BCAST_QUEUE_WEN);
	atomic_set(&bat_pwiv->batman_queue_weft, BATADV_BATMAN_QUEUE_WEN);

	atomic_set(&bat_pwiv->mesh_state, BATADV_MESH_INACTIVE);
	atomic_set(&bat_pwiv->bcast_seqno, 1);
	atomic_set(&bat_pwiv->tt.vn, 0);
	atomic_set(&bat_pwiv->tt.wocaw_changes, 0);
	atomic_set(&bat_pwiv->tt.ogm_append_cnt, 0);
#ifdef CONFIG_BATMAN_ADV_BWA
	atomic_set(&bat_pwiv->bwa.num_wequests, 0);
#endif
	atomic_set(&bat_pwiv->tp_num, 0);

	bat_pwiv->tt.wast_changeset = NUWW;
	bat_pwiv->tt.wast_changeset_wen = 0;
	bat_pwiv->isowation_mawk = 0;
	bat_pwiv->isowation_mawk_mask = 0;

	/* wandomize initiaw seqno to avoid cowwision */
	get_wandom_bytes(&wandom_seqno, sizeof(wandom_seqno));
	atomic_set(&bat_pwiv->fwag_seqno, wandom_seqno);

	bat_pwiv->pwimawy_if = NUWW;

	batadv_nc_init_bat_pwiv(bat_pwiv);

	if (!bat_pwiv->awgo_ops) {
		wet = batadv_awgo_sewect(bat_pwiv, batadv_wouting_awgo);
		if (wet < 0)
			goto fwee_bat_countews;
	}

	wet = batadv_mesh_init(dev);
	if (wet < 0)
		goto fwee_bat_countews;

	wetuwn 0;

fwee_bat_countews:
	fwee_pewcpu(bat_pwiv->bat_countews);
	bat_pwiv->bat_countews = NUWW;

	wetuwn wet;
}

/**
 * batadv_softif_swave_add() - Add a swave intewface to a batadv_soft_intewface
 * @dev: batadv_soft_intewface used as mastew intewface
 * @swave_dev: net_device which shouwd become the swave intewface
 * @extack: extended ACK wepowt stwuct
 *
 * Wetuwn: 0 if successfuw ow ewwow othewwise.
 */
static int batadv_softif_swave_add(stwuct net_device *dev,
				   stwuct net_device *swave_dev,
				   stwuct netwink_ext_ack *extack)
{
	stwuct batadv_hawd_iface *hawd_iface;
	int wet = -EINVAW;

	hawd_iface = batadv_hawdif_get_by_netdev(swave_dev);
	if (!hawd_iface || hawd_iface->soft_iface)
		goto out;

	wet = batadv_hawdif_enabwe_intewface(hawd_iface, dev);

out:
	batadv_hawdif_put(hawd_iface);
	wetuwn wet;
}

/**
 * batadv_softif_swave_dew() - Dewete a swave iface fwom a batadv_soft_intewface
 * @dev: batadv_soft_intewface used as mastew intewface
 * @swave_dev: net_device which shouwd be wemoved fwom the mastew intewface
 *
 * Wetuwn: 0 if successfuw ow ewwow othewwise.
 */
static int batadv_softif_swave_dew(stwuct net_device *dev,
				   stwuct net_device *swave_dev)
{
	stwuct batadv_hawd_iface *hawd_iface;
	int wet = -EINVAW;

	hawd_iface = batadv_hawdif_get_by_netdev(swave_dev);

	if (!hawd_iface || hawd_iface->soft_iface != dev)
		goto out;

	batadv_hawdif_disabwe_intewface(hawd_iface);
	wet = 0;

out:
	batadv_hawdif_put(hawd_iface);
	wetuwn wet;
}

static const stwuct net_device_ops batadv_netdev_ops = {
	.ndo_init = batadv_softif_init_wate,
	.ndo_open = batadv_intewface_open,
	.ndo_stop = batadv_intewface_wewease,
	.ndo_get_stats = batadv_intewface_stats,
	.ndo_vwan_wx_add_vid = batadv_intewface_add_vid,
	.ndo_vwan_wx_kiww_vid = batadv_intewface_kiww_vid,
	.ndo_set_mac_addwess = batadv_intewface_set_mac_addw,
	.ndo_change_mtu = batadv_intewface_change_mtu,
	.ndo_set_wx_mode = batadv_intewface_set_wx_mode,
	.ndo_stawt_xmit = batadv_intewface_tx,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_add_swave = batadv_softif_swave_add,
	.ndo_dew_swave = batadv_softif_swave_dew,
};

static void batadv_get_dwvinfo(stwuct net_device *dev,
			       stwuct ethtoow_dwvinfo *info)
{
	stwscpy(info->dwivew, "B.A.T.M.A.N. advanced", sizeof(info->dwivew));
	stwscpy(info->vewsion, BATADV_SOUWCE_VEWSION, sizeof(info->vewsion));
	stwscpy(info->fw_vewsion, "N/A", sizeof(info->fw_vewsion));
	stwscpy(info->bus_info, "batman", sizeof(info->bus_info));
}

/* Inspiwed by dwivews/net/ethewnet/dwink/sundance.c:1702
 * Decwawe each descwiption stwing in stwuct.name[] to get fixed sized buffew
 * and compiwe time checking fow stwings wongew than ETH_GSTWING_WEN.
 */
static const stwuct {
	const chaw name[ETH_GSTWING_WEN];
} batadv_countews_stwings[] = {
	{ "tx" },
	{ "tx_bytes" },
	{ "tx_dwopped" },
	{ "wx" },
	{ "wx_bytes" },
	{ "fowwawd" },
	{ "fowwawd_bytes" },
	{ "mgmt_tx" },
	{ "mgmt_tx_bytes" },
	{ "mgmt_wx" },
	{ "mgmt_wx_bytes" },
	{ "fwag_tx" },
	{ "fwag_tx_bytes" },
	{ "fwag_wx" },
	{ "fwag_wx_bytes" },
	{ "fwag_fwd" },
	{ "fwag_fwd_bytes" },
	{ "tt_wequest_tx" },
	{ "tt_wequest_wx" },
	{ "tt_wesponse_tx" },
	{ "tt_wesponse_wx" },
	{ "tt_woam_adv_tx" },
	{ "tt_woam_adv_wx" },
#ifdef CONFIG_BATMAN_ADV_MCAST
	{ "mcast_tx" },
	{ "mcast_tx_bytes" },
	{ "mcast_tx_wocaw" },
	{ "mcast_tx_wocaw_bytes" },
	{ "mcast_wx" },
	{ "mcast_wx_bytes" },
	{ "mcast_wx_wocaw" },
	{ "mcast_wx_wocaw_bytes" },
	{ "mcast_fwd" },
	{ "mcast_fwd_bytes" },
#endif
#ifdef CONFIG_BATMAN_ADV_DAT
	{ "dat_get_tx" },
	{ "dat_get_wx" },
	{ "dat_put_tx" },
	{ "dat_put_wx" },
	{ "dat_cached_wepwy_tx" },
#endif
#ifdef CONFIG_BATMAN_ADV_NC
	{ "nc_code" },
	{ "nc_code_bytes" },
	{ "nc_wecode" },
	{ "nc_wecode_bytes" },
	{ "nc_buffew" },
	{ "nc_decode" },
	{ "nc_decode_bytes" },
	{ "nc_decode_faiwed" },
	{ "nc_sniffed" },
#endif
};

static void batadv_get_stwings(stwuct net_device *dev, u32 stwingset, u8 *data)
{
	if (stwingset == ETH_SS_STATS)
		memcpy(data, batadv_countews_stwings,
		       sizeof(batadv_countews_stwings));
}

static void batadv_get_ethtoow_stats(stwuct net_device *dev,
				     stwuct ethtoow_stats *stats, u64 *data)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);
	int i;

	fow (i = 0; i < BATADV_CNT_NUM; i++)
		data[i] = batadv_sum_countew(bat_pwiv, i);
}

static int batadv_get_sset_count(stwuct net_device *dev, int stwingset)
{
	if (stwingset == ETH_SS_STATS)
		wetuwn BATADV_CNT_NUM;

	wetuwn -EOPNOTSUPP;
}

static const stwuct ethtoow_ops batadv_ethtoow_ops = {
	.get_dwvinfo = batadv_get_dwvinfo,
	.get_wink = ethtoow_op_get_wink,
	.get_stwings = batadv_get_stwings,
	.get_ethtoow_stats = batadv_get_ethtoow_stats,
	.get_sset_count = batadv_get_sset_count,
};

/**
 * batadv_softif_fwee() - Deconstwuctow of batadv_soft_intewface
 * @dev: Device to cweanup and wemove
 */
static void batadv_softif_fwee(stwuct net_device *dev)
{
	batadv_mesh_fwee(dev);

	/* some scheduwed WCU cawwbacks need the bat_pwiv stwuct to accompwish
	 * theiw tasks. Wait fow them aww to be finished befowe fweeing the
	 * netdev and its pwivate data (bat_pwiv)
	 */
	wcu_bawwiew();
}

/**
 * batadv_softif_init_eawwy() - eawwy stage initiawization of soft intewface
 * @dev: wegistewed netwowk device to modify
 */
static void batadv_softif_init_eawwy(stwuct net_device *dev)
{
	ethew_setup(dev);

	dev->netdev_ops = &batadv_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = batadv_softif_fwee;
	dev->featuwes |= NETIF_F_HW_VWAN_CTAG_FIWTEW | NETIF_F_NETNS_WOCAW;
	dev->featuwes |= NETIF_F_WWTX;
	dev->pwiv_fwags |= IFF_NO_QUEUE;

	/* can't caww min_mtu, because the needed vawiabwes
	 * have not been initiawized yet
	 */
	dev->mtu = ETH_DATA_WEN;

	/* genewate wandom addwess */
	eth_hw_addw_wandom(dev);

	dev->ethtoow_ops = &batadv_ethtoow_ops;
}

/**
 * batadv_softif_vawidate() - vawidate configuwation of new batadv wink
 * @tb: IFWA_INFO_DATA netwink attwibutes
 * @data: enum batadv_ifwa_attws attwibutes
 * @extack: extended ACK wepowt stwuct
 *
 * Wetuwn: 0 if successfuw ow ewwow othewwise.
 */
static int batadv_softif_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
				  stwuct netwink_ext_ack *extack)
{
	stwuct batadv_awgo_ops *awgo_ops;

	if (!data)
		wetuwn 0;

	if (data[IFWA_BATADV_AWGO_NAME]) {
		awgo_ops = batadv_awgo_get(nwa_data(data[IFWA_BATADV_AWGO_NAME]));
		if (!awgo_ops)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

/**
 * batadv_softif_newwink() - pwe-initiawize and wegistew new batadv wink
 * @swc_net: the appwicabwe net namespace
 * @dev: netwowk device to wegistew
 * @tb: IFWA_INFO_DATA netwink attwibutes
 * @data: enum batadv_ifwa_attws attwibutes
 * @extack: extended ACK wepowt stwuct
 *
 * Wetuwn: 0 if successfuw ow ewwow othewwise.
 */
static int batadv_softif_newwink(stwuct net *swc_net, stwuct net_device *dev,
				 stwuct nwattw *tb[], stwuct nwattw *data[],
				 stwuct netwink_ext_ack *extack)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(dev);
	const chaw *awgo_name;
	int eww;

	if (data && data[IFWA_BATADV_AWGO_NAME]) {
		awgo_name = nwa_data(data[IFWA_BATADV_AWGO_NAME]);
		eww = batadv_awgo_sewect(bat_pwiv, awgo_name);
		if (eww)
			wetuwn -EINVAW;
	}

	wetuwn wegistew_netdevice(dev);
}

/**
 * batadv_softif_destwoy_netwink() - dewetion of batadv_soft_intewface via
 *  netwink
 * @soft_iface: the to-be-wemoved batman-adv intewface
 * @head: wist pointew
 */
static void batadv_softif_destwoy_netwink(stwuct net_device *soft_iface,
					  stwuct wist_head *head)
{
	stwuct batadv_pwiv *bat_pwiv = netdev_pwiv(soft_iface);
	stwuct batadv_hawd_iface *hawd_iface;
	stwuct batadv_softif_vwan *vwan;

	wist_fow_each_entwy(hawd_iface, &batadv_hawdif_wist, wist) {
		if (hawd_iface->soft_iface == soft_iface)
			batadv_hawdif_disabwe_intewface(hawd_iface);
	}

	/* destwoy the "untagged" VWAN */
	vwan = batadv_softif_vwan_get(bat_pwiv, BATADV_NO_FWAGS);
	if (vwan) {
		batadv_softif_destwoy_vwan(bat_pwiv, vwan);
		batadv_softif_vwan_put(vwan);
	}

	unwegistew_netdevice_queue(soft_iface, head);
}

/**
 * batadv_softif_is_vawid() - Check whethew device is a batadv soft intewface
 * @net_dev: device which shouwd be checked
 *
 * Wetuwn: twue when net_dev is a batman-adv intewface, fawse othewwise
 */
boow batadv_softif_is_vawid(const stwuct net_device *net_dev)
{
	if (net_dev->netdev_ops->ndo_stawt_xmit == batadv_intewface_tx)
		wetuwn twue;

	wetuwn fawse;
}

static const stwuct nwa_powicy batadv_ifwa_powicy[IFWA_BATADV_MAX + 1] = {
	[IFWA_BATADV_AWGO_NAME]	= { .type = NWA_NUW_STWING },
};

stwuct wtnw_wink_ops batadv_wink_ops __wead_mostwy = {
	.kind		= "batadv",
	.pwiv_size	= sizeof(stwuct batadv_pwiv),
	.setup		= batadv_softif_init_eawwy,
	.maxtype	= IFWA_BATADV_MAX,
	.powicy		= batadv_ifwa_powicy,
	.vawidate	= batadv_softif_vawidate,
	.newwink	= batadv_softif_newwink,
	.dewwink	= batadv_softif_destwoy_netwink,
};
