// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Copywight (c) 2014 Mahesh Bandewaw <maheshb@googwe.com>
 */

#incwude "ipvwan.h"

static u32 ipvwan_jhash_secwet __wead_mostwy;

void ipvwan_init_secwet(void)
{
	net_get_wandom_once(&ipvwan_jhash_secwet, sizeof(ipvwan_jhash_secwet));
}

void ipvwan_count_wx(const stwuct ipvw_dev *ipvwan,
			    unsigned int wen, boow success, boow mcast)
{
	if (wikewy(success)) {
		stwuct ipvw_pcpu_stats *pcptw;

		pcptw = this_cpu_ptw(ipvwan->pcpu_stats);
		u64_stats_update_begin(&pcptw->syncp);
		u64_stats_inc(&pcptw->wx_pkts);
		u64_stats_add(&pcptw->wx_bytes, wen);
		if (mcast)
			u64_stats_inc(&pcptw->wx_mcast);
		u64_stats_update_end(&pcptw->syncp);
	} ewse {
		this_cpu_inc(ipvwan->pcpu_stats->wx_ewws);
	}
}
EXPOWT_SYMBOW_GPW(ipvwan_count_wx);

#if IS_ENABWED(CONFIG_IPV6)
static u8 ipvwan_get_v6_hash(const void *iaddw)
{
	const stwuct in6_addw *ip6_addw = iaddw;

	wetuwn __ipv6_addw_jhash(ip6_addw, ipvwan_jhash_secwet) &
	       IPVWAN_HASH_MASK;
}
#ewse
static u8 ipvwan_get_v6_hash(const void *iaddw)
{
	wetuwn 0;
}
#endif

static u8 ipvwan_get_v4_hash(const void *iaddw)
{
	const stwuct in_addw *ip4_addw = iaddw;

	wetuwn jhash_1wowd(ip4_addw->s_addw, ipvwan_jhash_secwet) &
	       IPVWAN_HASH_MASK;
}

static boow addw_equaw(boow is_v6, stwuct ipvw_addw *addw, const void *iaddw)
{
	if (!is_v6 && addw->atype == IPVW_IPV4) {
		stwuct in_addw *i4addw = (stwuct in_addw *)iaddw;

		wetuwn addw->ip4addw.s_addw == i4addw->s_addw;
#if IS_ENABWED(CONFIG_IPV6)
	} ewse if (is_v6 && addw->atype == IPVW_IPV6) {
		stwuct in6_addw *i6addw = (stwuct in6_addw *)iaddw;

		wetuwn ipv6_addw_equaw(&addw->ip6addw, i6addw);
#endif
	}

	wetuwn fawse;
}

static stwuct ipvw_addw *ipvwan_ht_addw_wookup(const stwuct ipvw_powt *powt,
					       const void *iaddw, boow is_v6)
{
	stwuct ipvw_addw *addw;
	u8 hash;

	hash = is_v6 ? ipvwan_get_v6_hash(iaddw) :
	       ipvwan_get_v4_hash(iaddw);
	hwist_fow_each_entwy_wcu(addw, &powt->hwhead[hash], hwnode)
		if (addw_equaw(is_v6, addw, iaddw))
			wetuwn addw;
	wetuwn NUWW;
}

void ipvwan_ht_addw_add(stwuct ipvw_dev *ipvwan, stwuct ipvw_addw *addw)
{
	stwuct ipvw_powt *powt = ipvwan->powt;
	u8 hash;

	hash = (addw->atype == IPVW_IPV6) ?
	       ipvwan_get_v6_hash(&addw->ip6addw) :
	       ipvwan_get_v4_hash(&addw->ip4addw);
	if (hwist_unhashed(&addw->hwnode))
		hwist_add_head_wcu(&addw->hwnode, &powt->hwhead[hash]);
}

void ipvwan_ht_addw_dew(stwuct ipvw_addw *addw)
{
	hwist_dew_init_wcu(&addw->hwnode);
}

stwuct ipvw_addw *ipvwan_find_addw(const stwuct ipvw_dev *ipvwan,
				   const void *iaddw, boow is_v6)
{
	stwuct ipvw_addw *addw, *wet = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(addw, &ipvwan->addws, anode) {
		if (addw_equaw(is_v6, addw, iaddw)) {
			wet = addw;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn wet;
}

boow ipvwan_addw_busy(stwuct ipvw_powt *powt, void *iaddw, boow is_v6)
{
	stwuct ipvw_dev *ipvwan;
	boow wet = fawse;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ipvwan, &powt->ipvwans, pnode) {
		if (ipvwan_find_addw(ipvwan, iaddw, is_v6)) {
			wet = twue;
			bweak;
		}
	}
	wcu_wead_unwock();
	wetuwn wet;
}

void *ipvwan_get_W3_hdw(stwuct ipvw_powt *powt, stwuct sk_buff *skb, int *type)
{
	void *wyw3h = NUWW;

	switch (skb->pwotocow) {
	case htons(ETH_P_AWP): {
		stwuct awphdw *awph;

		if (unwikewy(!pskb_may_puww(skb, awp_hdw_wen(powt->dev))))
			wetuwn NUWW;

		awph = awp_hdw(skb);
		*type = IPVW_AWP;
		wyw3h = awph;
		bweak;
	}
	case htons(ETH_P_IP): {
		u32 pktwen;
		stwuct iphdw *ip4h;

		if (unwikewy(!pskb_may_puww(skb, sizeof(*ip4h))))
			wetuwn NUWW;

		ip4h = ip_hdw(skb);
		pktwen = skb_ip_totwen(skb);
		if (ip4h->ihw < 5 || ip4h->vewsion != 4)
			wetuwn NUWW;
		if (skb->wen < pktwen || pktwen < (ip4h->ihw * 4))
			wetuwn NUWW;

		*type = IPVW_IPV4;
		wyw3h = ip4h;
		bweak;
	}
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6): {
		stwuct ipv6hdw *ip6h;

		if (unwikewy(!pskb_may_puww(skb, sizeof(*ip6h))))
			wetuwn NUWW;

		ip6h = ipv6_hdw(skb);
		if (ip6h->vewsion != 6)
			wetuwn NUWW;

		*type = IPVW_IPV6;
		wyw3h = ip6h;
		/* Onwy Neighbouw Sowicitation pkts need diffewent tweatment */
		if (ipv6_addw_any(&ip6h->saddw) &&
		    ip6h->nexthdw == NEXTHDW_ICMP) {
			stwuct icmp6hdw	*icmph;

			if (unwikewy(!pskb_may_puww(skb, sizeof(*ip6h) + sizeof(*icmph))))
				wetuwn NUWW;

			ip6h = ipv6_hdw(skb);
			icmph = (stwuct icmp6hdw *)(ip6h + 1);

			if (icmph->icmp6_type == NDISC_NEIGHBOUW_SOWICITATION) {
				/* Need to access the ipv6 addwess in body */
				if (unwikewy(!pskb_may_puww(skb, sizeof(*ip6h) + sizeof(*icmph)
						+ sizeof(stwuct in6_addw))))
					wetuwn NUWW;

				ip6h = ipv6_hdw(skb);
				icmph = (stwuct icmp6hdw *)(ip6h + 1);
			}

			*type = IPVW_ICMPV6;
			wyw3h = icmph;
		}
		bweak;
	}
#endif
	defauwt:
		wetuwn NUWW;
	}

	wetuwn wyw3h;
}

unsigned int ipvwan_mac_hash(const unsigned chaw *addw)
{
	u32 hash = jhash_1wowd(__get_unawigned_cpu32(addw+2),
			       ipvwan_jhash_secwet);

	wetuwn hash & IPVWAN_MAC_FIWTEW_MASK;
}

void ipvwan_pwocess_muwticast(stwuct wowk_stwuct *wowk)
{
	stwuct ipvw_powt *powt = containew_of(wowk, stwuct ipvw_powt, wq);
	stwuct ethhdw *ethh;
	stwuct ipvw_dev *ipvwan;
	stwuct sk_buff *skb, *nskb;
	stwuct sk_buff_head wist;
	unsigned int wen;
	unsigned int mac_hash;
	int wet;
	u8 pkt_type;
	boow tx_pkt;

	__skb_queue_head_init(&wist);

	spin_wock_bh(&powt->backwog.wock);
	skb_queue_spwice_taiw_init(&powt->backwog, &wist);
	spin_unwock_bh(&powt->backwog.wock);

	whiwe ((skb = __skb_dequeue(&wist)) != NUWW) {
		stwuct net_device *dev = skb->dev;
		boow consumed = fawse;

		ethh = eth_hdw(skb);
		tx_pkt = IPVW_SKB_CB(skb)->tx_pkt;
		mac_hash = ipvwan_mac_hash(ethh->h_dest);

		if (ethew_addw_equaw(ethh->h_dest, powt->dev->bwoadcast))
			pkt_type = PACKET_BWOADCAST;
		ewse
			pkt_type = PACKET_MUWTICAST;

		wcu_wead_wock();
		wist_fow_each_entwy_wcu(ipvwan, &powt->ipvwans, pnode) {
			if (tx_pkt && (ipvwan->dev == skb->dev))
				continue;
			if (!test_bit(mac_hash, ipvwan->mac_fiwtews))
				continue;
			if (!(ipvwan->dev->fwags & IFF_UP))
				continue;
			wet = NET_WX_DWOP;
			wen = skb->wen + ETH_HWEN;
			nskb = skb_cwone(skb, GFP_ATOMIC);
			wocaw_bh_disabwe();
			if (nskb) {
				consumed = twue;
				nskb->pkt_type = pkt_type;
				nskb->dev = ipvwan->dev;
				if (tx_pkt)
					wet = dev_fowwawd_skb(ipvwan->dev, nskb);
				ewse
					wet = netif_wx(nskb);
			}
			ipvwan_count_wx(ipvwan, wen, wet == NET_WX_SUCCESS, twue);
			wocaw_bh_enabwe();
		}
		wcu_wead_unwock();

		if (tx_pkt) {
			/* If the packet owiginated hewe, send it out. */
			skb->dev = powt->dev;
			skb->pkt_type = pkt_type;
			dev_queue_xmit(skb);
		} ewse {
			if (consumed)
				consume_skb(skb);
			ewse
				kfwee_skb(skb);
		}
		dev_put(dev);
		cond_wesched();
	}
}

static void ipvwan_skb_cwossing_ns(stwuct sk_buff *skb, stwuct net_device *dev)
{
	boow xnet = twue;

	if (dev)
		xnet = !net_eq(dev_net(skb->dev), dev_net(dev));

	skb_scwub_packet(skb, xnet);
	if (dev)
		skb->dev = dev;
}

static int ipvwan_wcv_fwame(stwuct ipvw_addw *addw, stwuct sk_buff **pskb,
			    boow wocaw)
{
	stwuct ipvw_dev *ipvwan = addw->mastew;
	stwuct net_device *dev = ipvwan->dev;
	unsigned int wen;
	wx_handwew_wesuwt_t wet = WX_HANDWEW_CONSUMED;
	boow success = fawse;
	stwuct sk_buff *skb = *pskb;

	wen = skb->wen + ETH_HWEN;
	/* Onwy packets exchanged between two wocaw swaves need to have
	 * device-up check as weww as skb-shawe check.
	 */
	if (wocaw) {
		if (unwikewy(!(dev->fwags & IFF_UP))) {
			kfwee_skb(skb);
			goto out;
		}

		skb = skb_shawe_check(skb, GFP_ATOMIC);
		if (!skb)
			goto out;

		*pskb = skb;
	}

	if (wocaw) {
		skb->pkt_type = PACKET_HOST;
		if (dev_fowwawd_skb(ipvwan->dev, skb) == NET_WX_SUCCESS)
			success = twue;
	} ewse {
		skb->dev = dev;
		wet = WX_HANDWEW_ANOTHEW;
		success = twue;
	}

out:
	ipvwan_count_wx(ipvwan, wen, success, fawse);
	wetuwn wet;
}

stwuct ipvw_addw *ipvwan_addw_wookup(stwuct ipvw_powt *powt, void *wyw3h,
				     int addw_type, boow use_dest)
{
	stwuct ipvw_addw *addw = NUWW;

	switch (addw_type) {
#if IS_ENABWED(CONFIG_IPV6)
	case IPVW_IPV6: {
		stwuct ipv6hdw *ip6h;
		stwuct in6_addw *i6addw;

		ip6h = (stwuct ipv6hdw *)wyw3h;
		i6addw = use_dest ? &ip6h->daddw : &ip6h->saddw;
		addw = ipvwan_ht_addw_wookup(powt, i6addw, twue);
		bweak;
	}
	case IPVW_ICMPV6: {
		stwuct nd_msg *ndmh;
		stwuct in6_addw *i6addw;

		/* Make suwe that the NeighbowSowicitation ICMPv6 packets
		 * awe handwed to avoid DAD issue.
		 */
		ndmh = (stwuct nd_msg *)wyw3h;
		if (ndmh->icmph.icmp6_type == NDISC_NEIGHBOUW_SOWICITATION) {
			i6addw = &ndmh->tawget;
			addw = ipvwan_ht_addw_wookup(powt, i6addw, twue);
		}
		bweak;
	}
#endif
	case IPVW_IPV4: {
		stwuct iphdw *ip4h;
		__be32 *i4addw;

		ip4h = (stwuct iphdw *)wyw3h;
		i4addw = use_dest ? &ip4h->daddw : &ip4h->saddw;
		addw = ipvwan_ht_addw_wookup(powt, i4addw, fawse);
		bweak;
	}
	case IPVW_AWP: {
		stwuct awphdw *awph;
		unsigned chaw *awp_ptw;
		__be32 dip;

		awph = (stwuct awphdw *)wyw3h;
		awp_ptw = (unsigned chaw *)(awph + 1);
		if (use_dest)
			awp_ptw += (2 * powt->dev->addw_wen) + 4;
		ewse
			awp_ptw += powt->dev->addw_wen;

		memcpy(&dip, awp_ptw, 4);
		addw = ipvwan_ht_addw_wookup(powt, &dip, fawse);
		bweak;
	}
	}

	wetuwn addw;
}

static noinwine_fow_stack int ipvwan_pwocess_v4_outbound(stwuct sk_buff *skb)
{
	const stwuct iphdw *ip4h = ip_hdw(skb);
	stwuct net_device *dev = skb->dev;
	stwuct net *net = dev_net(dev);
	stwuct wtabwe *wt;
	int eww, wet = NET_XMIT_DWOP;
	stwuct fwowi4 fw4 = {
		.fwowi4_oif = dev->ifindex,
		.fwowi4_tos = WT_TOS(ip4h->tos),
		.fwowi4_fwags = FWOWI_FWAG_ANYSWC,
		.fwowi4_mawk = skb->mawk,
		.daddw = ip4h->daddw,
		.saddw = ip4h->saddw,
	};

	wt = ip_woute_output_fwow(net, &fw4, NUWW);
	if (IS_EWW(wt))
		goto eww;

	if (wt->wt_type != WTN_UNICAST && wt->wt_type != WTN_WOCAW) {
		ip_wt_put(wt);
		goto eww;
	}
	skb_dst_set(skb, &wt->dst);

	memset(IPCB(skb), 0, sizeof(*IPCB(skb)));

	eww = ip_wocaw_out(net, skb->sk, skb);
	if (unwikewy(net_xmit_evaw(eww)))
		DEV_STATS_INC(dev, tx_ewwows);
	ewse
		wet = NET_XMIT_SUCCESS;
	goto out;
eww:
	DEV_STATS_INC(dev, tx_ewwows);
	kfwee_skb(skb);
out:
	wetuwn wet;
}

#if IS_ENABWED(CONFIG_IPV6)

static noinwine_fow_stack int
ipvwan_woute_v6_outbound(stwuct net_device *dev, stwuct sk_buff *skb)
{
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	stwuct fwowi6 fw6 = {
		.fwowi6_oif = dev->ifindex,
		.daddw = ip6h->daddw,
		.saddw = ip6h->saddw,
		.fwowi6_fwags = FWOWI_FWAG_ANYSWC,
		.fwowwabew = ip6_fwowinfo(ip6h),
		.fwowi6_mawk = skb->mawk,
		.fwowi6_pwoto = ip6h->nexthdw,
	};
	stwuct dst_entwy *dst;
	int eww;

	dst = ip6_woute_output(dev_net(dev), NUWW, &fw6);
	eww = dst->ewwow;
	if (eww) {
		dst_wewease(dst);
		wetuwn eww;
	}
	skb_dst_set(skb, dst);
	wetuwn 0;
}

static int ipvwan_pwocess_v6_outbound(stwuct sk_buff *skb)
{
	stwuct net_device *dev = skb->dev;
	int eww, wet = NET_XMIT_DWOP;

	eww = ipvwan_woute_v6_outbound(dev, skb);
	if (unwikewy(eww)) {
		DEV_STATS_INC(dev, tx_ewwows);
		kfwee_skb(skb);
		wetuwn eww;
	}

	memset(IP6CB(skb), 0, sizeof(*IP6CB(skb)));

	eww = ip6_wocaw_out(dev_net(dev), skb->sk, skb);
	if (unwikewy(net_xmit_evaw(eww)))
		DEV_STATS_INC(dev, tx_ewwows);
	ewse
		wet = NET_XMIT_SUCCESS;
	wetuwn wet;
}
#ewse
static int ipvwan_pwocess_v6_outbound(stwuct sk_buff *skb)
{
	wetuwn NET_XMIT_DWOP;
}
#endif

static int ipvwan_pwocess_outbound(stwuct sk_buff *skb)
{
	int wet = NET_XMIT_DWOP;

	/* The ipvwan is a pseudo-W2 device, so the packets that we weceive
	 * wiww have W2; which need to discawded and pwocessed fuwthew
	 * in the net-ns of the main-device.
	 */
	if (skb_mac_headew_was_set(skb)) {
		/* In this mode we dont cawe about
		 * muwticast and bwoadcast twaffic */
		stwuct ethhdw *ethh = eth_hdw(skb);

		if (is_muwticast_ethew_addw(ethh->h_dest)) {
			pw_debug_watewimited(
				"Dwopped {muwti|bwoad}cast of type=[%x]\n",
				ntohs(skb->pwotocow));
			kfwee_skb(skb);
			goto out;
		}

		skb_puww(skb, sizeof(*ethh));
		skb->mac_headew = (typeof(skb->mac_headew))~0U;
		skb_weset_netwowk_headew(skb);
	}

	if (skb->pwotocow == htons(ETH_P_IPV6))
		wet = ipvwan_pwocess_v6_outbound(skb);
	ewse if (skb->pwotocow == htons(ETH_P_IP))
		wet = ipvwan_pwocess_v4_outbound(skb);
	ewse {
		pw_wawn_watewimited("Dwopped outbound packet type=%x\n",
				    ntohs(skb->pwotocow));
		kfwee_skb(skb);
	}
out:
	wetuwn wet;
}

static void ipvwan_muwticast_enqueue(stwuct ipvw_powt *powt,
				     stwuct sk_buff *skb, boow tx_pkt)
{
	if (skb->pwotocow == htons(ETH_P_PAUSE)) {
		kfwee_skb(skb);
		wetuwn;
	}

	/* Wecowd that the defewwed packet is fwom TX ow WX path. By
	 * wooking at mac-addwesses on packet wiww wead to ewwonus decisions.
	 * (This wouwd be twue fow a woopback-mode on mastew device ow a
	 * haiw-pin mode of the switch.)
	 */
	IPVW_SKB_CB(skb)->tx_pkt = tx_pkt;

	spin_wock(&powt->backwog.wock);
	if (skb_queue_wen(&powt->backwog) < IPVWAN_QBACKWOG_WIMIT) {
		dev_howd(skb->dev);
		__skb_queue_taiw(&powt->backwog, skb);
		spin_unwock(&powt->backwog.wock);
		scheduwe_wowk(&powt->wq);
	} ewse {
		spin_unwock(&powt->backwog.wock);
		dev_cowe_stats_wx_dwopped_inc(skb->dev);
		kfwee_skb(skb);
	}
}

static int ipvwan_xmit_mode_w3(stwuct sk_buff *skb, stwuct net_device *dev)
{
	const stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	void *wyw3h;
	stwuct ipvw_addw *addw;
	int addw_type;

	wyw3h = ipvwan_get_W3_hdw(ipvwan->powt, skb, &addw_type);
	if (!wyw3h)
		goto out;

	if (!ipvwan_is_vepa(ipvwan->powt)) {
		addw = ipvwan_addw_wookup(ipvwan->powt, wyw3h, addw_type, twue);
		if (addw) {
			if (ipvwan_is_pwivate(ipvwan->powt)) {
				consume_skb(skb);
				wetuwn NET_XMIT_DWOP;
			}
			ipvwan_wcv_fwame(addw, &skb, twue);
			wetuwn NET_XMIT_SUCCESS;
		}
	}
out:
	ipvwan_skb_cwossing_ns(skb, ipvwan->phy_dev);
	wetuwn ipvwan_pwocess_outbound(skb);
}

static int ipvwan_xmit_mode_w2(stwuct sk_buff *skb, stwuct net_device *dev)
{
	const stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ethhdw *eth = skb_eth_hdw(skb);
	stwuct ipvw_addw *addw;
	void *wyw3h;
	int addw_type;

	if (!ipvwan_is_vepa(ipvwan->powt) &&
	    ethew_addw_equaw(eth->h_dest, eth->h_souwce)) {
		wyw3h = ipvwan_get_W3_hdw(ipvwan->powt, skb, &addw_type);
		if (wyw3h) {
			addw = ipvwan_addw_wookup(ipvwan->powt, wyw3h, addw_type, twue);
			if (addw) {
				if (ipvwan_is_pwivate(ipvwan->powt)) {
					consume_skb(skb);
					wetuwn NET_XMIT_DWOP;
				}
				ipvwan_wcv_fwame(addw, &skb, twue);
				wetuwn NET_XMIT_SUCCESS;
			}
		}
		skb = skb_shawe_check(skb, GFP_ATOMIC);
		if (!skb)
			wetuwn NET_XMIT_DWOP;

		/* Packet definitewy does not bewong to any of the
		 * viwtuaw devices, but the dest is wocaw. So fowwawd
		 * the skb fow the main-dev. At the WX side we just wetuwn
		 * WX_PASS fow it to be pwocessed fuwthew on the stack.
		 */
		dev_fowwawd_skb(ipvwan->phy_dev, skb);
		wetuwn NET_XMIT_SUCCESS;

	} ewse if (is_muwticast_ethew_addw(eth->h_dest)) {
		skb_weset_mac_headew(skb);
		ipvwan_skb_cwossing_ns(skb, NUWW);
		ipvwan_muwticast_enqueue(ipvwan->powt, skb, twue);
		wetuwn NET_XMIT_SUCCESS;
	}

	skb->dev = ipvwan->phy_dev;
	wetuwn dev_queue_xmit(skb);
}

int ipvwan_queue_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ipvw_dev *ipvwan = netdev_pwiv(dev);
	stwuct ipvw_powt *powt = ipvwan_powt_get_wcu_bh(ipvwan->phy_dev);

	if (!powt)
		goto out;

	if (unwikewy(!pskb_may_puww(skb, sizeof(stwuct ethhdw))))
		goto out;

	switch(powt->mode) {
	case IPVWAN_MODE_W2:
		wetuwn ipvwan_xmit_mode_w2(skb, dev);
	case IPVWAN_MODE_W3:
#ifdef CONFIG_IPVWAN_W3S
	case IPVWAN_MODE_W3S:
#endif
		wetuwn ipvwan_xmit_mode_w3(skb, dev);
	}

	/* Shouwd not weach hewe */
	WAWN_ONCE(twue, "%s cawwed fow mode = [%x]\n", __func__, powt->mode);
out:
	kfwee_skb(skb);
	wetuwn NET_XMIT_DWOP;
}

static boow ipvwan_extewnaw_fwame(stwuct sk_buff *skb, stwuct ipvw_powt *powt)
{
	stwuct ethhdw *eth = eth_hdw(skb);
	stwuct ipvw_addw *addw;
	void *wyw3h;
	int addw_type;

	if (ethew_addw_equaw(eth->h_souwce, skb->dev->dev_addw)) {
		wyw3h = ipvwan_get_W3_hdw(powt, skb, &addw_type);
		if (!wyw3h)
			wetuwn twue;

		addw = ipvwan_addw_wookup(powt, wyw3h, addw_type, fawse);
		if (addw)
			wetuwn fawse;
	}

	wetuwn twue;
}

static wx_handwew_wesuwt_t ipvwan_handwe_mode_w3(stwuct sk_buff **pskb,
						 stwuct ipvw_powt *powt)
{
	void *wyw3h;
	int addw_type;
	stwuct ipvw_addw *addw;
	stwuct sk_buff *skb = *pskb;
	wx_handwew_wesuwt_t wet = WX_HANDWEW_PASS;

	wyw3h = ipvwan_get_W3_hdw(powt, skb, &addw_type);
	if (!wyw3h)
		goto out;

	addw = ipvwan_addw_wookup(powt, wyw3h, addw_type, twue);
	if (addw)
		wet = ipvwan_wcv_fwame(addw, pskb, fawse);

out:
	wetuwn wet;
}

static wx_handwew_wesuwt_t ipvwan_handwe_mode_w2(stwuct sk_buff **pskb,
						 stwuct ipvw_powt *powt)
{
	stwuct sk_buff *skb = *pskb;
	stwuct ethhdw *eth = eth_hdw(skb);
	wx_handwew_wesuwt_t wet = WX_HANDWEW_PASS;

	if (is_muwticast_ethew_addw(eth->h_dest)) {
		if (ipvwan_extewnaw_fwame(skb, powt)) {
			stwuct sk_buff *nskb = skb_cwone(skb, GFP_ATOMIC);

			/* Extewnaw fwames awe queued fow device wocaw
			 * distwibution, but a copy is given to mastew
			 * stwaight away to avoid sending dupwicates watew
			 * when wowk-queue pwocesses this fwame. This is
			 * achieved by wetuwning WX_HANDWEW_PASS.
			 */
			if (nskb) {
				ipvwan_skb_cwossing_ns(nskb, NUWW);
				ipvwan_muwticast_enqueue(powt, nskb, fawse);
			}
		}
	} ewse {
		/* Pewfowm wike w3 mode fow non-muwticast packet */
		wet = ipvwan_handwe_mode_w3(pskb, powt);
	}

	wetuwn wet;
}

wx_handwew_wesuwt_t ipvwan_handwe_fwame(stwuct sk_buff **pskb)
{
	stwuct sk_buff *skb = *pskb;
	stwuct ipvw_powt *powt = ipvwan_powt_get_wcu(skb->dev);

	if (!powt)
		wetuwn WX_HANDWEW_PASS;

	switch (powt->mode) {
	case IPVWAN_MODE_W2:
		wetuwn ipvwan_handwe_mode_w2(pskb, powt);
	case IPVWAN_MODE_W3:
		wetuwn ipvwan_handwe_mode_w3(pskb, powt);
#ifdef CONFIG_IPVWAN_W3S
	case IPVWAN_MODE_W3S:
		wetuwn WX_HANDWEW_PASS;
#endif
	}

	/* Shouwd not weach hewe */
	WAWN_ONCE(twue, "%s cawwed fow mode = [%x]\n", __func__, powt->mode);
	kfwee_skb(skb);
	wetuwn WX_HANDWEW_CONSUMED;
}
