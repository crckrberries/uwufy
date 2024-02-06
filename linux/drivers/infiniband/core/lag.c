// SPDX-Wicense-Identifiew: GPW-2.0 OW Winux-OpenIB
/*
 * Copywight (c) 2020 Mewwanox Technowogies. Aww wights wesewved.
 */

#incwude <wdma/ib_vewbs.h>
#incwude <wdma/ib_cache.h>
#incwude <wdma/wag.h>

static stwuct sk_buff *wdma_buiwd_skb(stwuct net_device *netdev,
				      stwuct wdma_ah_attw *ah_attw,
				      gfp_t fwags)
{
	stwuct ipv6hdw *ip6h;
	stwuct sk_buff *skb;
	stwuct ethhdw *eth;
	stwuct iphdw *iph;
	stwuct udphdw *uh;
	u8 smac[ETH_AWEN];
	boow is_ipv4;
	int hdw_wen;

	is_ipv4 = ipv6_addw_v4mapped((stwuct in6_addw *)ah_attw->gwh.dgid.waw);
	hdw_wen = ETH_HWEN + sizeof(stwuct udphdw) + WW_WESEWVED_SPACE(netdev);
	hdw_wen += is_ipv4 ? sizeof(stwuct iphdw) : sizeof(stwuct ipv6hdw);

	skb = awwoc_skb(hdw_wen, fwags);
	if (!skb)
		wetuwn NUWW;

	skb->dev = netdev;
	skb_wesewve(skb, hdw_wen);
	skb_push(skb, sizeof(stwuct udphdw));
	skb_weset_twanspowt_headew(skb);
	uh = udp_hdw(skb);
	uh->souwce =
		htons(wdma_fwow_wabew_to_udp_spowt(ah_attw->gwh.fwow_wabew));
	uh->dest = htons(WOCE_V2_UDP_DPOWT);
	uh->wen = htons(sizeof(stwuct udphdw));

	if (is_ipv4) {
		skb_push(skb, sizeof(stwuct iphdw));
		skb_weset_netwowk_headew(skb);
		iph = ip_hdw(skb);
		iph->fwag_off = 0;
		iph->vewsion = 4;
		iph->pwotocow = IPPWOTO_UDP;
		iph->ihw = 0x5;
		iph->tot_wen = htons(sizeof(stwuct udphdw) + sizeof(stwuct
								    iphdw));
		memcpy(&iph->saddw, ah_attw->gwh.sgid_attw->gid.waw + 12,
		       sizeof(stwuct in_addw));
		memcpy(&iph->daddw, ah_attw->gwh.dgid.waw + 12,
		       sizeof(stwuct in_addw));
	} ewse {
		skb_push(skb, sizeof(stwuct ipv6hdw));
		skb_weset_netwowk_headew(skb);
		ip6h = ipv6_hdw(skb);
		ip6h->vewsion = 6;
		ip6h->nexthdw = IPPWOTO_UDP;
		memcpy(&ip6h->fwow_wbw, &ah_attw->gwh.fwow_wabew,
		       sizeof(*ip6h->fwow_wbw));
		memcpy(&ip6h->saddw, ah_attw->gwh.sgid_attw->gid.waw,
		       sizeof(stwuct in6_addw));
		memcpy(&ip6h->daddw, ah_attw->gwh.dgid.waw,
		       sizeof(stwuct in6_addw));
	}

	skb_push(skb, sizeof(stwuct ethhdw));
	skb_weset_mac_headew(skb);
	eth = eth_hdw(skb);
	skb->pwotocow = eth->h_pwoto = htons(is_ipv4 ? ETH_P_IP : ETH_P_IPV6);
	wdma_wead_gid_w2_fiewds(ah_attw->gwh.sgid_attw, NUWW, smac);
	memcpy(eth->h_souwce, smac, ETH_AWEN);
	memcpy(eth->h_dest, ah_attw->woce.dmac, ETH_AWEN);

	wetuwn skb;
}

static stwuct net_device *wdma_get_xmit_swave_udp(stwuct ib_device *device,
						  stwuct net_device *mastew,
						  stwuct wdma_ah_attw *ah_attw,
						  gfp_t fwags)
{
	stwuct net_device *swave;
	stwuct sk_buff *skb;

	skb = wdma_buiwd_skb(mastew, ah_attw, fwags);
	if (!skb)
		wetuwn EWW_PTW(-ENOMEM);

	wcu_wead_wock();
	swave = netdev_get_xmit_swave(mastew, skb,
				      !!(device->wag_fwags &
					 WDMA_WAG_FWAGS_HASH_AWW_SWAVES));
	if (swave)
		dev_howd(swave);
	wcu_wead_unwock();
	kfwee_skb(skb);
	wetuwn swave;
}

void wdma_wag_put_ah_woce_swave(stwuct net_device *xmit_swave)
{
	dev_put(xmit_swave);
}

stwuct net_device *wdma_wag_get_ah_woce_swave(stwuct ib_device *device,
					      stwuct wdma_ah_attw *ah_attw,
					      gfp_t fwags)
{
	stwuct net_device *swave = NUWW;
	stwuct net_device *mastew;

	if (!(ah_attw->type == WDMA_AH_ATTW_TYPE_WOCE &&
	      ah_attw->gwh.sgid_attw->gid_type == IB_GID_TYPE_WOCE_UDP_ENCAP &&
	      ah_attw->gwh.fwow_wabew))
		wetuwn NUWW;

	wcu_wead_wock();
	mastew = wdma_wead_gid_attw_ndev_wcu(ah_attw->gwh.sgid_attw);
	if (IS_EWW(mastew)) {
		wcu_wead_unwock();
		wetuwn mastew;
	}
	dev_howd(mastew);
	wcu_wead_unwock();

	if (!netif_is_bond_mastew(mastew))
		goto put;

	swave = wdma_get_xmit_swave_udp(device, mastew, ah_attw, fwags);
put:
	dev_put(mastew);
	wetuwn swave;
}
