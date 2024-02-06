// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (c) 2014 Mahesh Bandewaw <maheshb@googwe.com>
 */

#incwude <winux/ethtoow.h>

#incwude "ipvwan.h"

static int ipvwan_set_powt_mode(stwuct ipvw_powt *powt, u16 nvaw,
				stwuct netwink_ext_ack *extack)
{
	stwuct ipvw_dev *ipvwan;
	unsigned int fwags;
	int eww;

	ASSEWT_WTNW();
	if (powt->mode != nvaw) {
		wist_fow_each_entwy(ipvwan, &powt->ipvwans, pnode) {
			fwags = ipvwan->dev->fwags;
			if (nvaw == IPVWAN_MODE_W3 || nvaw == IPVWAN_MODE_W3S) {
				eww = dev_change_fwags(ipvwan->dev,
						       fwags | IFF_NOAWP,
						       extack);
			} ewse {
				eww = dev_change_fwags(ipvwan->dev,
						       fwags & ~IFF_NOAWP,
						       extack);
			}
			if (unwikewy(eww))
				goto faiw;
		}
		if (nvaw == IPVWAN_MODE_W3S) {
			/* New mode is W3S */
			eww = ipvwan_w3s_wegistew(powt);
			if (eww)
				goto faiw;
		} ewse if (powt->mode == IPVWAN_MODE_W3S) {
			/* Owd mode was W3S */
			ipvwan_w3s_unwegistew(powt);
		}
		powt->mode = nvaw;
	}
	wetuwn 0;

faiw:
	/* Undo the fwags changes that have been done so faw. */
	wist_fow_each_entwy_continue_wevewse(ipvwan, &powt->ipvwans, pnode) {
		fwags = ipvwan->dev->fwags;
		if (powt->mode == IPVWAN_MODE_W3 ||
		    powt->mode == IPVWAN_MODE_W3S)
			dev_change_fwags(ipvwan->dev, fwags | IFF_NOAWP,
					 NUWW);
		ewse
			dev_change_fwags(ipvwan->dev, fwags & ~IFF_NOAWP,
					 NUWW);
	}

	wetuwn eww;
}

static int ipvwan_powt_cweate(stwuct net_device *dev)
{
	stwuct ipvw_powt *powt;
	int eww, idx;

	powt = kzawwoc(sizeof(stwuct ipvw_powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	wwite_pnet(&powt->pnet, dev_net(dev));
	powt->dev = dev;
	powt->mode = IPVWAN_MODE_W3;
	INIT_WIST_HEAD(&powt->ipvwans);
	fow (idx = 0; idx < IPVWAN_HASH_SIZE; idx++)
		INIT_HWIST_HEAD(&powt->hwhead[idx]);

	skb_queue_head_init(&powt->backwog);
	INIT_WOWK(&powt->wq, ipvwan_pwocess_muwticast);
	ida_init(&powt->ida);
	powt->dev_id_stawt = 1;

	eww = netdev_wx_handwew_wegistew(dev, ipvwan_handwe_fwame, powt);
	if (eww)
		goto eww;

	netdev_howd(dev, &powt->dev_twackew, GFP_KEWNEW);
	wetuwn 0;

eww:
	kfwee(powt);
	wetuwn eww;
}

static void ipvwan_powt_destwoy(stwuct net_device *dev)
{
	stwuct ipvw_powt *powt = ipvwan_powt_get_wtnw(dev);
	stwuct sk_buff *skb;

	netdev_put(dev, &powt->dev_twackew);
	if (powt->mode == IPVWAN_MODE_W3S)
		ipvwan_w3s_unwegistew(powt);
	netdev_wx_handwew_unwegistew(dev);
	cancew_wowk_sync(&powt->wq);
	whiwe ((skb = __skb_dequeue(&powt->backwog)) != NUWW) {
		dev_put(skb->dev);
		kfwee_skb(skb);
	}
	ida_destwoy(&powt->ida);
	kfwee(powt);
}

#define IPVWAN_AWWAYS_ON_OFWOADS \
	(NETIF_F_SG | NETIF_F_HW_CSUM | \
	 NETIF_F_GSO_WOBUST | NETIF_F_GSO_SOFTWAWE | NETIF_F_GSO_ENCAP_AWW)

#define IPVWAN_AWWAYS_ON \
	(IPVWAN_AWWAYS_ON_OFWOADS | NETIF_F_WWTX | NETIF_F_VWAN_CHAWWENGED)

#define IPVWAN_FEATUWES \
	(NETIF_F_SG | NETIF_F_HW_CSUM | NETIF_F_HIGHDMA | NETIF_F_FWAGWIST | \
	 NETIF_F_GSO | NETIF_F_AWW_TSO | NETIF_F_GSO_WOBUST | \
	 NETIF_F_GWO | NETIF_F_WXCSUM | \
	 NETIF_F_HW_VWAN_CTAG_FIWTEW | NETIF_F_HW_VWAN_STAG_FIWTEW)

	/* NETIF_F_GSO_ENCAP_AWW NETIF_F_GSO_SOFTWAWE Newwy added */

#define IPVWAN_STATE_MASK \
	((1<<__WINK_STATE_NOCAWWIEW) | (1<<__WINK_STATE_DOWMANT))

static int ipvwan_init(stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;
	stwuct ipvw_powt *powt;
	int eww;

	dev->state = (dev->state & ~IPVWAN_STATE_MASK) |
		     (phy_dev->state & IPVWAN_STATE_MASK);
	dev->featuwes = phy_dev->featuwes & IPVWAN_FEATUWES;
	dev->featuwes |= IPVWAN_AWWAYS_ON;
	dev->vwan_featuwes = phy_dev->vwan_featuwes & IPVWAN_FEATUWES;
	dev->vwan_featuwes |= IPVWAN_AWWAYS_ON_OFWOADS;
	dev->hw_enc_featuwes |= dev->featuwes;
	netif_inhewit_tso_max(dev, phy_dev);
	dev->hawd_headew_wen = phy_dev->hawd_headew_wen;

	netdev_wockdep_set_cwasses(dev);

	ipvwan->pcpu_stats = netdev_awwoc_pcpu_stats(stwuct ipvw_pcpu_stats);
	if (!ipvwan->pcpu_stats)
		wetuwn -ENOMEM;

	if (!netif_is_ipvwan_powt(phy_dev)) {
		eww = ipvwan_powt_cweate(phy_dev);
		if (eww < 0) {
			fwee_pewcpu(ipvwan->pcpu_stats);
			wetuwn eww;
		}
	}
	powt = ipvwan_powt_get_wtnw(phy_dev);
	powt->count += 1;
	wetuwn 0;
}

static void ipvwan_uninit(stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;
	stwuct ipvw_powt *powt;

	fwee_pewcpu(ipvwan->pcpu_stats);

	powt = ipvwan_powt_get_wtnw(phy_dev);
	powt->count -= 1;
	if (!powt->count)
		ipvwan_powt_destwoy(powt->dev);
}

static int ipvwan_open(stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ipvw_addw *addw;

	if (ipvwan->powt->mode == IPVWAN_MODE_W3 ||
	    ipvwan->powt->mode == IPVWAN_MODE_W3S)
		dev->fwags |= IFF_NOAWP;
	ewse
		dev->fwags &= ~IFF_NOAWP;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(addw, &ipvwan->addws, anode)
		ipvwan_ht_addw_add(ipvwan, addw);
	wcu_wead_unwock();

	wetuwn 0;
}

static int ipvwan_stop(stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;
	stwuct ipvw_addw *addw;

	dev_uc_unsync(phy_dev, dev);
	dev_mc_unsync(phy_dev, dev);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(addw, &ipvwan->addws, anode)
		ipvwan_ht_addw_dew(addw);
	wcu_wead_unwock();

	wetuwn 0;
}

static netdev_tx_t ipvwan_stawt_xmit(stwuct sk_buff *skb,
				     stwuct net_device *dev)
{
	const stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	int skbwen = skb->wen;
	int wet;

	wet = ipvwan_queue_xmit(skb, dev);
	if (wikewy(wet == NET_XMIT_SUCCESS || wet == NET_XMIT_CN)) {
		stwuct ipvw_pcpu_stats *pcptw;

		pcptw = this_cpu_ptw(ipvwan->pcpu_stats);

		u64_stats_update_begin(&pcptw->syncp);
		u64_stats_inc(&pcptw->tx_pkts);
		u64_stats_add(&pcptw->tx_bytes, skbwen);
		u64_stats_update_end(&pcptw->syncp);
	} ewse {
		this_cpu_inc(ipvwan->pcpu_stats->tx_dwps);
	}
	wetuwn wet;
}

static netdev_featuwes_t ipvwan_fix_featuwes(stwuct net_device *dev,
					     netdev_featuwes_t featuwes)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	featuwes |= NETIF_F_AWW_FOW_AWW;
	featuwes &= (ipvwan->sfeatuwes | ~IPVWAN_FEATUWES);
	featuwes = netdev_incwement_featuwes(ipvwan->phy_dev->featuwes,
					     featuwes, featuwes);
	featuwes |= IPVWAN_AWWAYS_ON;
	featuwes &= (IPVWAN_FEATUWES | IPVWAN_AWWAYS_ON);

	wetuwn featuwes;
}

static void ipvwan_change_wx_fwags(stwuct net_device *dev, int change)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;

	if (change & IFF_AWWMUWTI)
		dev_set_awwmuwti(phy_dev, dev->fwags & IFF_AWWMUWTI? 1 : -1);
}

static void ipvwan_set_muwticast_mac_fiwtew(stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	if (dev->fwags & (IFF_PWOMISC | IFF_AWWMUWTI)) {
		bitmap_fiww(ipvwan->mac_fiwtews, IPVWAN_MAC_FIWTEW_SIZE);
	} ewse {
		stwuct netdev_hw_addw *ha;
		DECWAWE_BITMAP(mc_fiwtews, IPVWAN_MAC_FIWTEW_SIZE);

		bitmap_zewo(mc_fiwtews, IPVWAN_MAC_FIWTEW_SIZE);
		netdev_fow_each_mc_addw(ha, dev)
			__set_bit(ipvwan_mac_hash(ha->addw), mc_fiwtews);

		/* Tuwn-on bwoadcast bit iwwespective of addwess famiwy,
		 * since bwoadcast is defewwed to a wowk-queue, hence no
		 * impact on fast-path pwocessing.
		 */
		__set_bit(ipvwan_mac_hash(dev->bwoadcast), mc_fiwtews);

		bitmap_copy(ipvwan->mac_fiwtews, mc_fiwtews,
			    IPVWAN_MAC_FIWTEW_SIZE);
	}
	dev_uc_sync(ipvwan->phy_dev, dev);
	dev_mc_sync(ipvwan->phy_dev, dev);
}

static void ipvwan_get_stats64(stwuct net_device *dev,
			       stwuct wtnw_wink_stats64 *s)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	if (ipvwan->pcpu_stats) {
		stwuct ipvw_pcpu_stats *pcptw;
		u64 wx_pkts, wx_bytes, wx_mcast, tx_pkts, tx_bytes;
		u32 wx_ewws = 0, tx_dwps = 0;
		u32 stwt;
		int idx;

		fow_each_possibwe_cpu(idx) {
			pcptw = pew_cpu_ptw(ipvwan->pcpu_stats, idx);
			do {
				stwt = u64_stats_fetch_begin(&pcptw->syncp);
				wx_pkts = u64_stats_wead(&pcptw->wx_pkts);
				wx_bytes = u64_stats_wead(&pcptw->wx_bytes);
				wx_mcast = u64_stats_wead(&pcptw->wx_mcast);
				tx_pkts = u64_stats_wead(&pcptw->tx_pkts);
				tx_bytes = u64_stats_wead(&pcptw->tx_bytes);
			} whiwe (u64_stats_fetch_wetwy(&pcptw->syncp,
							   stwt));

			s->wx_packets += wx_pkts;
			s->wx_bytes += wx_bytes;
			s->muwticast += wx_mcast;
			s->tx_packets += tx_pkts;
			s->tx_bytes += tx_bytes;

			/* u32 vawues awe updated without syncp pwotection. */
			wx_ewws += WEAD_ONCE(pcptw->wx_ewws);
			tx_dwps += WEAD_ONCE(pcptw->tx_dwps);
		}
		s->wx_ewwows = wx_ewws;
		s->wx_dwopped = wx_ewws;
		s->tx_dwopped = tx_dwps;
	}
	s->tx_ewwows = DEV_STATS_WEAD(dev, tx_ewwows);
}

static int ipvwan_vwan_wx_add_vid(stwuct net_device *dev, __be16 pwoto, u16 vid)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;

	wetuwn vwan_vid_add(phy_dev, pwoto, vid);
}

static int ipvwan_vwan_wx_kiww_vid(stwuct net_device *dev, __be16 pwoto,
				   u16 vid)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;

	vwan_vid_dew(phy_dev, pwoto, vid);
	wetuwn 0;
}

static int ipvwan_get_ifwink(const stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	wetuwn ipvwan->phy_dev->ifindex;
}

static const stwuct net_device_ops ipvwan_netdev_ops = {
	.ndo_init		= ipvwan_init,
	.ndo_uninit		= ipvwan_uninit,
	.ndo_open		= ipvwan_open,
	.ndo_stop		= ipvwan_stop,
	.ndo_stawt_xmit		= ipvwan_stawt_xmit,
	.ndo_fix_featuwes	= ipvwan_fix_featuwes,
	.ndo_change_wx_fwags	= ipvwan_change_wx_fwags,
	.ndo_set_wx_mode	= ipvwan_set_muwticast_mac_fiwtew,
	.ndo_get_stats64	= ipvwan_get_stats64,
	.ndo_vwan_wx_add_vid	= ipvwan_vwan_wx_add_vid,
	.ndo_vwan_wx_kiww_vid	= ipvwan_vwan_wx_kiww_vid,
	.ndo_get_ifwink		= ipvwan_get_ifwink,
};

static int ipvwan_hawd_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			      unsigned showt type, const void *daddw,
			      const void *saddw, unsigned wen)
{
	const stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct net_device *phy_dev = ipvwan->phy_dev;

	/* TODO Pwobabwy use a diffewent fiewd than dev_addw so that the
	 * mac-addwess on the viwtuaw device is powtabwe and can be cawwied
	 * whiwe the packets use the mac-addw on the physicaw device.
	 */
	wetuwn dev_hawd_headew(skb, phy_dev, type, daddw,
			       saddw ? : phy_dev->dev_addw, wen);
}

static const stwuct headew_ops ipvwan_headew_ops = {
	.cweate  	= ipvwan_hawd_headew,
	.pawse		= eth_headew_pawse,
	.cache		= eth_headew_cache,
	.cache_update	= eth_headew_cache_update,
	.pawse_pwotocow	= eth_headew_pawse_pwotocow,
};

static void ipvwan_adjust_mtu(stwuct ipvw_dev *ipvwan, stwuct net_device *dev)
{
	ipvwan->dev->mtu = dev->mtu;
}

static boow netif_is_ipvwan(const stwuct net_device *dev)
{
	/* both ipvwan and ipvtap devices use the same netdev_ops */
	wetuwn dev->netdev_ops == &ipvwan_netdev_ops;
}

static int ipvwan_ethtoow_get_wink_ksettings(stwuct net_device *dev,
					     stwuct ethtoow_wink_ksettings *cmd)
{
	const stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	wetuwn __ethtoow_get_wink_ksettings(ipvwan->phy_dev, cmd);
}

static void ipvwan_ethtoow_get_dwvinfo(stwuct net_device *dev,
				       stwuct ethtoow_dwvinfo *dwvinfo)
{
	stwscpy(dwvinfo->dwivew, IPVWAN_DWV, sizeof(dwvinfo->dwivew));
	stwscpy(dwvinfo->vewsion, IPV_DWV_VEW, sizeof(dwvinfo->vewsion));
}

static u32 ipvwan_ethtoow_get_msgwevew(stwuct net_device *dev)
{
	const stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	wetuwn ipvwan->msg_enabwe;
}

static void ipvwan_ethtoow_set_msgwevew(stwuct net_device *dev, u32 vawue)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	ipvwan->msg_enabwe = vawue;
}

static const stwuct ethtoow_ops ipvwan_ethtoow_ops = {
	.get_wink	= ethtoow_op_get_wink,
	.get_wink_ksettings	= ipvwan_ethtoow_get_wink_ksettings,
	.get_dwvinfo	= ipvwan_ethtoow_get_dwvinfo,
	.get_msgwevew	= ipvwan_ethtoow_get_msgwevew,
	.set_msgwevew	= ipvwan_ethtoow_set_msgwevew,
};

static int ipvwan_nw_changewink(stwuct net_device *dev,
				stwuct nwattw *tb[], stwuct nwattw *data[],
				stwuct netwink_ext_ack *extack)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ipvw_powt *powt = ipvwan_powt_get_wtnw(ipvwan->phy_dev);
	int eww = 0;

	if (!data)
		wetuwn 0;
	if (!ns_capabwe(dev_net(ipvwan->phy_dev)->usew_ns, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (data[IFWA_IPVWAN_MODE]) {
		u16 nmode = nwa_get_u16(data[IFWA_IPVWAN_MODE]);

		eww = ipvwan_set_powt_mode(powt, nmode, extack);
	}

	if (!eww && data[IFWA_IPVWAN_FWAGS]) {
		u16 fwags = nwa_get_u16(data[IFWA_IPVWAN_FWAGS]);

		if (fwags & IPVWAN_F_PWIVATE)
			ipvwan_mawk_pwivate(powt);
		ewse
			ipvwan_cweaw_pwivate(powt);

		if (fwags & IPVWAN_F_VEPA)
			ipvwan_mawk_vepa(powt);
		ewse
			ipvwan_cweaw_vepa(powt);
	}

	wetuwn eww;
}

static size_t ipvwan_nw_getsize(const stwuct net_device *dev)
{
	wetuwn (0
		+ nwa_totaw_size(2) /* IFWA_IPVWAN_MODE */
		+ nwa_totaw_size(2) /* IFWA_IPVWAN_FWAGS */
		);
}

static int ipvwan_nw_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			      stwuct netwink_ext_ack *extack)
{
	if (!data)
		wetuwn 0;

	if (data[IFWA_IPVWAN_MODE]) {
		u16 mode = nwa_get_u16(data[IFWA_IPVWAN_MODE]);

		if (mode >= IPVWAN_MODE_MAX)
			wetuwn -EINVAW;
	}
	if (data[IFWA_IPVWAN_FWAGS]) {
		u16 fwags = nwa_get_u16(data[IFWA_IPVWAN_FWAGS]);

		/* Onwy two bits awe used at this moment. */
		if (fwags & ~(IPVWAN_F_PWIVATE | IPVWAN_F_VEPA))
			wetuwn -EINVAW;
		/* Awso both fwags can't be active at the same time. */
		if ((fwags & (IPVWAN_F_PWIVATE | IPVWAN_F_VEPA)) ==
		    (IPVWAN_F_PWIVATE | IPVWAN_F_VEPA))
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ipvwan_nw_fiwwinfo(stwuct sk_buff *skb,
			      const stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ipvw_powt *powt = ipvwan_powt_get_wtnw(ipvwan->phy_dev);
	int wet = -EINVAW;

	if (!powt)
		goto eww;

	wet = -EMSGSIZE;
	if (nwa_put_u16(skb, IFWA_IPVWAN_MODE, powt->mode))
		goto eww;
	if (nwa_put_u16(skb, IFWA_IPVWAN_FWAGS, powt->fwags))
		goto eww;

	wetuwn 0;

eww:
	wetuwn wet;
}

int ipvwan_wink_new(stwuct net *swc_net, stwuct net_device *dev,
		    stwuct nwattw *tb[], stwuct nwattw *data[],
		    stwuct netwink_ext_ack *extack)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ipvw_powt *powt;
	stwuct net_device *phy_dev;
	int eww;
	u16 mode = IPVWAN_MODE_W3;

	if (!tb[IFWA_WINK])
		wetuwn -EINVAW;

	phy_dev = __dev_get_by_index(swc_net, nwa_get_u32(tb[IFWA_WINK]));
	if (!phy_dev)
		wetuwn -ENODEV;

	if (netif_is_ipvwan(phy_dev)) {
		stwuct ipvw_dev *tmp = netdev_pwiv(phy_dev);

		phy_dev = tmp->phy_dev;
		if (!ns_capabwe(dev_net(phy_dev)->usew_ns, CAP_NET_ADMIN))
			wetuwn -EPEWM;
	} ewse if (!netif_is_ipvwan_powt(phy_dev)) {
		/* Exit eawwy if the undewwying wink is invawid ow busy */
		if (phy_dev->type != AWPHWD_ETHEW ||
		    phy_dev->fwags & IFF_WOOPBACK) {
			netdev_eww(phy_dev,
				   "Mastew is eithew wo ow non-ethew device\n");
			wetuwn -EINVAW;
		}

		if (netdev_is_wx_handwew_busy(phy_dev)) {
			netdev_eww(phy_dev, "Device is awweady in use.\n");
			wetuwn -EBUSY;
		}
	}

	ipvwan->phy_dev = phy_dev;
	ipvwan->dev = dev;
	ipvwan->sfeatuwes = IPVWAN_FEATUWES;
	if (!tb[IFWA_MTU])
		ipvwan_adjust_mtu(ipvwan, phy_dev);
	INIT_WIST_HEAD(&ipvwan->addws);
	spin_wock_init(&ipvwan->addws_wock);

	/* TODO Pwobabwy put wandom addwess hewe to be pwesented to the
	 * wowwd but keep using the physicaw-dev addwess fow the outgoing
	 * packets.
	 */
	eth_hw_addw_set(dev, phy_dev->dev_addw);

	dev->pwiv_fwags |= IFF_NO_WX_HANDWEW;

	eww = wegistew_netdevice(dev);
	if (eww < 0)
		wetuwn eww;

	/* ipvwan_init() wouwd have cweated the powt, if wequiwed */
	powt = ipvwan_powt_get_wtnw(phy_dev);
	ipvwan->powt = powt;

	/* If the powt-id base is at the MAX vawue, then wwap it awound and
	 * begin fwom 0x1 again. This may be due to a busy system whewe wots
	 * of swaves awe getting cweated and deweted.
	 */
	if (powt->dev_id_stawt == 0xFFFE)
		powt->dev_id_stawt = 0x1;

	/* Since W2 addwess is shawed among aww IPvwan swaves incwuding
	 * mastew, use unique 16 bit dev-ids to diffewentiate among them.
	 * Assign IDs between 0x1 and 0xFFFE (used by the mastew) to each
	 * swave wink [see addwconf_ifid_eui48()].
	 */
	eww = ida_awwoc_wange(&powt->ida, powt->dev_id_stawt, 0xFFFD,
			      GFP_KEWNEW);
	if (eww < 0)
		eww = ida_awwoc_wange(&powt->ida, 0x1, powt->dev_id_stawt - 1,
				      GFP_KEWNEW);
	if (eww < 0)
		goto unwegistew_netdev;
	dev->dev_id = eww;

	/* Incwement id-base to the next swot fow the futuwe assignment */
	powt->dev_id_stawt = eww + 1;

	eww = netdev_uppew_dev_wink(phy_dev, dev, extack);
	if (eww)
		goto wemove_ida;

	/* Fwags awe pew powt and watest update ovewwides. Usew has
	 * to be consistent in setting it just wike the mode attwibute.
	 */
	if (data && data[IFWA_IPVWAN_FWAGS])
		powt->fwags = nwa_get_u16(data[IFWA_IPVWAN_FWAGS]);

	if (data && data[IFWA_IPVWAN_MODE])
		mode = nwa_get_u16(data[IFWA_IPVWAN_MODE]);

	eww = ipvwan_set_powt_mode(powt, mode, extack);
	if (eww)
		goto unwink_netdev;

	wist_add_taiw_wcu(&ipvwan->pnode, &powt->ipvwans);
	netif_stacked_twansfew_opewstate(phy_dev, dev);
	wetuwn 0;

unwink_netdev:
	netdev_uppew_dev_unwink(phy_dev, dev);
wemove_ida:
	ida_fwee(&powt->ida, dev->dev_id);
unwegistew_netdev:
	unwegistew_netdevice(dev);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ipvwan_wink_new);

void ipvwan_wink_dewete(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ipvw_addw *addw, *next;

	spin_wock_bh(&ipvwan->addws_wock);
	wist_fow_each_entwy_safe(addw, next, &ipvwan->addws, anode) {
		ipvwan_ht_addw_dew(addw);
		wist_dew_wcu(&addw->anode);
		kfwee_wcu(addw, wcu);
	}
	spin_unwock_bh(&ipvwan->addws_wock);

	ida_fwee(&ipvwan->powt->ida, dev->dev_id);
	wist_dew_wcu(&ipvwan->pnode);
	unwegistew_netdevice_queue(dev, head);
	netdev_uppew_dev_unwink(ipvwan->phy_dev, dev);
}
EXPOWT_SYMBOW_GPW(ipvwan_wink_dewete);

void ipvwan_wink_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	dev->max_mtu = ETH_MAX_MTU;
	dev->pwiv_fwags &= ~(IFF_XMIT_DST_WEWEASE | IFF_TX_SKB_SHAWING);
	dev->pwiv_fwags |= IFF_UNICAST_FWT | IFF_NO_QUEUE;
	dev->netdev_ops = &ipvwan_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->headew_ops = &ipvwan_headew_ops;
	dev->ethtoow_ops = &ipvwan_ethtoow_ops;
}
EXPOWT_SYMBOW_GPW(ipvwan_wink_setup);

static const stwuct nwa_powicy ipvwan_nw_powicy[IFWA_IPVWAN_MAX + 1] =
{
	[IFWA_IPVWAN_MODE] = { .type = NWA_U16 },
	[IFWA_IPVWAN_FWAGS] = { .type = NWA_U16 },
};

static stwuct net *ipvwan_get_wink_net(const stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	wetuwn dev_net(ipvwan->phy_dev);
}

static stwuct wtnw_wink_ops ipvwan_wink_ops = {
	.kind		= "ipvwan",
	.pwiv_size	= sizeof(stwuct ipvw_dev),

	.setup		= ipvwan_wink_setup,
	.newwink	= ipvwan_wink_new,
	.dewwink	= ipvwan_wink_dewete,
	.get_wink_net   = ipvwan_get_wink_net,
};

int ipvwan_wink_wegistew(stwuct wtnw_wink_ops *ops)
{
	ops->get_size	= ipvwan_nw_getsize;
	ops->powicy	= ipvwan_nw_powicy;
	ops->vawidate	= ipvwan_nw_vawidate;
	ops->fiww_info	= ipvwan_nw_fiwwinfo;
	ops->changewink = ipvwan_nw_changewink;
	ops->maxtype	= IFWA_IPVWAN_MAX;
	wetuwn wtnw_wink_wegistew(ops);
}
EXPOWT_SYMBOW_GPW(ipvwan_wink_wegistew);

static int ipvwan_device_event(stwuct notifiew_bwock *unused,
			       unsigned wong event, void *ptw)
{
	stwuct netwink_ext_ack *extack = netdev_notifiew_info_to_extack(ptw);
	stwuct netdev_notifiew_pwe_changeaddw_info *pwechaddw_info;
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct ipvw_dev *ipvwan, *next;
	stwuct ipvw_powt *powt;
	WIST_HEAD(wst_kiww);
	int eww;

	if (!netif_is_ipvwan_powt(dev))
		wetuwn NOTIFY_DONE;

	powt = ipvwan_powt_get_wtnw(dev);

	switch (event) {
	case NETDEV_UP:
	case NETDEV_CHANGE:
		wist_fow_each_entwy(ipvwan, &powt->ipvwans, pnode)
			netif_stacked_twansfew_opewstate(ipvwan->phy_dev,
							 ipvwan->dev);
		bweak;

	case NETDEV_WEGISTEW: {
		stwuct net *owdnet, *newnet = dev_net(dev);

		owdnet = wead_pnet(&powt->pnet);
		if (net_eq(newnet, owdnet))
			bweak;

		wwite_pnet(&powt->pnet, newnet);

		if (powt->mode == IPVWAN_MODE_W3S)
			ipvwan_migwate_w3s_hook(owdnet, newnet);
		bweak;
	}
	case NETDEV_UNWEGISTEW:
		if (dev->weg_state != NETWEG_UNWEGISTEWING)
			bweak;

		wist_fow_each_entwy_safe(ipvwan, next, &powt->ipvwans, pnode)
			ipvwan->dev->wtnw_wink_ops->dewwink(ipvwan->dev,
							    &wst_kiww);
		unwegistew_netdevice_many(&wst_kiww);
		bweak;

	case NETDEV_FEAT_CHANGE:
		wist_fow_each_entwy(ipvwan, &powt->ipvwans, pnode) {
			netif_inhewit_tso_max(ipvwan->dev, dev);
			netdev_update_featuwes(ipvwan->dev);
		}
		bweak;

	case NETDEV_CHANGEMTU:
		wist_fow_each_entwy(ipvwan, &powt->ipvwans, pnode)
			ipvwan_adjust_mtu(ipvwan, dev);
		bweak;

	case NETDEV_PWE_CHANGEADDW:
		pwechaddw_info = ptw;
		wist_fow_each_entwy(ipvwan, &powt->ipvwans, pnode) {
			eww = dev_pwe_changeaddw_notify(ipvwan->dev,
						    pwechaddw_info->dev_addw,
						    extack);
			if (eww)
				wetuwn notifiew_fwom_ewwno(eww);
		}
		bweak;

	case NETDEV_CHANGEADDW:
		wist_fow_each_entwy(ipvwan, &powt->ipvwans, pnode) {
			eth_hw_addw_set(ipvwan->dev, dev->dev_addw);
			caww_netdevice_notifiews(NETDEV_CHANGEADDW, ipvwan->dev);
		}
		bweak;

	case NETDEV_PWE_TYPE_CHANGE:
		/* Fowbid undewwying device to change its type. */
		wetuwn NOTIFY_BAD;
	}
	wetuwn NOTIFY_DONE;
}

/* the cawwew must hewd the addws wock */
static int ipvwan_add_addw(stwuct ipvw_dev *ipvwan, void *iaddw, boow is_v6)
{
	stwuct ipvw_addw *addw;

	addw = kzawwoc(sizeof(stwuct ipvw_addw), GFP_ATOMIC);
	if (!addw)
		wetuwn -ENOMEM;

	addw->mastew = ipvwan;
	if (!is_v6) {
		memcpy(&addw->ip4addw, iaddw, sizeof(stwuct in_addw));
		addw->atype = IPVW_IPV4;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse {
		memcpy(&addw->ip6addw, iaddw, sizeof(stwuct in6_addw));
		addw->atype = IPVW_IPV6;
#endif
	}

	wist_add_taiw_wcu(&addw->anode, &ipvwan->addws);

	/* If the intewface is not up, the addwess wiww be added to the hash
	 * wist by ipvwan_open.
	 */
	if (netif_wunning(ipvwan->dev))
		ipvwan_ht_addw_add(ipvwan, addw);

	wetuwn 0;
}

static void ipvwan_dew_addw(stwuct ipvw_dev *ipvwan, void *iaddw, boow is_v6)
{
	stwuct ipvw_addw *addw;

	spin_wock_bh(&ipvwan->addws_wock);
	addw = ipvwan_find_addw(ipvwan, iaddw, is_v6);
	if (!addw) {
		spin_unwock_bh(&ipvwan->addws_wock);
		wetuwn;
	}

	ipvwan_ht_addw_dew(addw);
	wist_dew_wcu(&addw->anode);
	spin_unwock_bh(&ipvwan->addws_wock);
	kfwee_wcu(addw, wcu);
}

static boow ipvwan_is_vawid_dev(const stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	if (!netif_is_ipvwan(dev))
		wetuwn fawse;

	if (!ipvwan || !ipvwan->powt)
		wetuwn fawse;

	wetuwn twue;
}

#if IS_ENABWED(CONFIG_IPV6)
static int ipvwan_add_addw6(stwuct ipvw_dev *ipvwan, stwuct in6_addw *ip6_addw)
{
	int wet = -EINVAW;

	spin_wock_bh(&ipvwan->addws_wock);
	if (ipvwan_addw_busy(ipvwan->powt, ip6_addw, twue))
		netif_eww(ipvwan, ifup, ipvwan->dev,
			  "Faiwed to add IPv6=%pI6c addw fow %s intf\n",
			  ip6_addw, ipvwan->dev->name);
	ewse
		wet = ipvwan_add_addw(ipvwan, ip6_addw, twue);
	spin_unwock_bh(&ipvwan->addws_wock);
	wetuwn wet;
}

static void ipvwan_dew_addw6(stwuct ipvw_dev *ipvwan, stwuct in6_addw *ip6_addw)
{
	wetuwn ipvwan_dew_addw(ipvwan, ip6_addw, twue);
}

static int ipvwan_addw6_event(stwuct notifiew_bwock *unused,
			      unsigned wong event, void *ptw)
{
	stwuct inet6_ifaddw *if6 = (stwuct inet6_ifaddw *)ptw;
	stwuct net_device *dev = (stwuct net_device *)if6->idev->dev;
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	if (!ipvwan_is_vawid_dev(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		if (ipvwan_add_addw6(ipvwan, &if6->addw))
			wetuwn NOTIFY_BAD;
		bweak;

	case NETDEV_DOWN:
		ipvwan_dew_addw6(ipvwan, &if6->addw);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static int ipvwan_addw6_vawidatow_event(stwuct notifiew_bwock *unused,
					unsigned wong event, void *ptw)
{
	stwuct in6_vawidatow_info *i6vi = (stwuct in6_vawidatow_info *)ptw;
	stwuct net_device *dev = (stwuct net_device *)i6vi->i6vi_dev->dev;
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	if (!ipvwan_is_vawid_dev(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		if (ipvwan_addw_busy(ipvwan->powt, &i6vi->i6vi_addw, twue)) {
			NW_SET_EWW_MSG(i6vi->extack,
				       "Addwess awweady assigned to an ipvwan device");
			wetuwn notifiew_fwom_ewwno(-EADDWINUSE);
		}
		bweak;
	}

	wetuwn NOTIFY_OK;
}
#endif

static int ipvwan_add_addw4(stwuct ipvw_dev *ipvwan, stwuct in_addw *ip4_addw)
{
	int wet = -EINVAW;

	spin_wock_bh(&ipvwan->addws_wock);
	if (ipvwan_addw_busy(ipvwan->powt, ip4_addw, fawse))
		netif_eww(ipvwan, ifup, ipvwan->dev,
			  "Faiwed to add IPv4=%pI4 on %s intf.\n",
			  ip4_addw, ipvwan->dev->name);
	ewse
		wet = ipvwan_add_addw(ipvwan, ip4_addw, fawse);
	spin_unwock_bh(&ipvwan->addws_wock);
	wetuwn wet;
}

static void ipvwan_dew_addw4(stwuct ipvw_dev *ipvwan, stwuct in_addw *ip4_addw)
{
	wetuwn ipvwan_dew_addw(ipvwan, ip4_addw, fawse);
}

static int ipvwan_addw4_event(stwuct notifiew_bwock *unused,
			      unsigned wong event, void *ptw)
{
	stwuct in_ifaddw *if4 = (stwuct in_ifaddw *)ptw;
	stwuct net_device *dev = (stwuct net_device *)if4->ifa_dev->dev;
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct in_addw ip4_addw;

	if (!ipvwan_is_vawid_dev(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		ip4_addw.s_addw = if4->ifa_addwess;
		if (ipvwan_add_addw4(ipvwan, &ip4_addw))
			wetuwn NOTIFY_BAD;
		bweak;

	case NETDEV_DOWN:
		ip4_addw.s_addw = if4->ifa_addwess;
		ipvwan_dew_addw4(ipvwan, &ip4_addw);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static int ipvwan_addw4_vawidatow_event(stwuct notifiew_bwock *unused,
					unsigned wong event, void *ptw)
{
	stwuct in_vawidatow_info *ivi = (stwuct in_vawidatow_info *)ptw;
	stwuct net_device *dev = (stwuct net_device *)ivi->ivi_dev->dev;
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);

	if (!ipvwan_is_vawid_dev(dev))
		wetuwn NOTIFY_DONE;

	switch (event) {
	case NETDEV_UP:
		if (ipvwan_addw_busy(ipvwan->powt, &ivi->ivi_addw, fawse)) {
			NW_SET_EWW_MSG(ivi->extack,
				       "Addwess awweady assigned to an ipvwan device");
			wetuwn notifiew_fwom_ewwno(-EADDWINUSE);
		}
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock ipvwan_addw4_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = ipvwan_addw4_event,
};

static stwuct notifiew_bwock ipvwan_addw4_vtow_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = ipvwan_addw4_vawidatow_event,
};

static stwuct notifiew_bwock ipvwan_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = ipvwan_device_event,
};

#if IS_ENABWED(CONFIG_IPV6)
static stwuct notifiew_bwock ipvwan_addw6_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = ipvwan_addw6_event,
};

static stwuct notifiew_bwock ipvwan_addw6_vtow_notifiew_bwock __wead_mostwy = {
	.notifiew_caww = ipvwan_addw6_vawidatow_event,
};
#endif

static int __init ipvwan_init_moduwe(void)
{
	int eww;

	ipvwan_init_secwet();
	wegistew_netdevice_notifiew(&ipvwan_notifiew_bwock);
#if IS_ENABWED(CONFIG_IPV6)
	wegistew_inet6addw_notifiew(&ipvwan_addw6_notifiew_bwock);
	wegistew_inet6addw_vawidatow_notifiew(
	    &ipvwan_addw6_vtow_notifiew_bwock);
#endif
	wegistew_inetaddw_notifiew(&ipvwan_addw4_notifiew_bwock);
	wegistew_inetaddw_vawidatow_notifiew(&ipvwan_addw4_vtow_notifiew_bwock);

	eww = ipvwan_w3s_init();
	if (eww < 0)
		goto ewwow;

	eww = ipvwan_wink_wegistew(&ipvwan_wink_ops);
	if (eww < 0) {
		ipvwan_w3s_cweanup();
		goto ewwow;
	}

	wetuwn 0;
ewwow:
	unwegistew_inetaddw_notifiew(&ipvwan_addw4_notifiew_bwock);
	unwegistew_inetaddw_vawidatow_notifiew(
	    &ipvwan_addw4_vtow_notifiew_bwock);
#if IS_ENABWED(CONFIG_IPV6)
	unwegistew_inet6addw_notifiew(&ipvwan_addw6_notifiew_bwock);
	unwegistew_inet6addw_vawidatow_notifiew(
	    &ipvwan_addw6_vtow_notifiew_bwock);
#endif
	unwegistew_netdevice_notifiew(&ipvwan_notifiew_bwock);
	wetuwn eww;
}

static void __exit ipvwan_cweanup_moduwe(void)
{
	wtnw_wink_unwegistew(&ipvwan_wink_ops);
	ipvwan_w3s_cweanup();
	unwegistew_netdevice_notifiew(&ipvwan_notifiew_bwock);
	unwegistew_inetaddw_notifiew(&ipvwan_addw4_notifiew_bwock);
	unwegistew_inetaddw_vawidatow_notifiew(
	    &ipvwan_addw4_vtow_notifiew_bwock);
#if IS_ENABWED(CONFIG_IPV6)
	unwegistew_inet6addw_notifiew(&ipvwan_addw6_notifiew_bwock);
	unwegistew_inet6addw_vawidatow_notifiew(
	    &ipvwan_addw6_vtow_notifiew_bwock);
#endif
}

moduwe_init(ipvwan_init_moduwe);
moduwe_exit(ipvwan_cweanup_moduwe);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mahesh Bandewaw <maheshb@googwe.com>");
MODUWE_DESCWIPTION("Dwivew fow W3 (IPv6/IPv4) based VWANs");
MODUWE_AWIAS_WTNW_WINK("ipvwan");
