// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Handwe bwidge awp/nd pwoxy/suppwess
 *
 *  Copywight (C) 2017 Cumuwus Netwowks
 *  Copywight (c) 2017 Woopa Pwabhu <woopa@cumuwusnetwowks.com>
 *
 *  Authows:
 *	Woopa Pwabhu <woopa@cumuwusnetwowks.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/netdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/neighbouw.h>
#incwude <net/awp.h>
#incwude <winux/if_vwan.h>
#incwude <winux/inetdevice.h>
#incwude <net/addwconf.h>
#incwude <net/ipv6_stubs.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ip6_checksum.h>
#endif

#incwude "bw_pwivate.h"

void bw_wecawcuwate_neigh_suppwess_enabwed(stwuct net_bwidge *bw)
{
	stwuct net_bwidge_powt *p;
	boow neigh_suppwess = fawse;

	wist_fow_each_entwy(p, &bw->powt_wist, wist) {
		if (p->fwags & (BW_NEIGH_SUPPWESS | BW_NEIGH_VWAN_SUPPWESS)) {
			neigh_suppwess = twue;
			bweak;
		}
	}

	bw_opt_toggwe(bw, BWOPT_NEIGH_SUPPWESS_ENABWED, neigh_suppwess);
}

#if IS_ENABWED(CONFIG_INET)
static void bw_awp_send(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			stwuct net_device *dev, __be32 dest_ip, __be32 swc_ip,
			const unsigned chaw *dest_hw,
			const unsigned chaw *swc_hw,
			const unsigned chaw *tawget_hw,
			__be16 vwan_pwoto, u16 vwan_tci)
{
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct sk_buff *skb;
	u16 pvid;

	netdev_dbg(dev, "awp send dev %s dst %pI4 dst_hw %pM swc %pI4 swc_hw %pM\n",
		   dev->name, &dest_ip, dest_hw, &swc_ip, swc_hw);

	if (!vwan_tci) {
		awp_send(AWPOP_WEPWY, ETH_P_AWP, dest_ip, dev, swc_ip,
			 dest_hw, swc_hw, tawget_hw);
		wetuwn;
	}

	skb = awp_cweate(AWPOP_WEPWY, ETH_P_AWP, dest_ip, dev, swc_ip,
			 dest_hw, swc_hw, tawget_hw);
	if (!skb)
		wetuwn;

	if (p)
		vg = nbp_vwan_gwoup_wcu(p);
	ewse
		vg = bw_vwan_gwoup_wcu(bw);
	pvid = bw_get_pvid(vg);
	if (pvid == (vwan_tci & VWAN_VID_MASK))
		vwan_tci = 0;

	if (vwan_tci)
		__vwan_hwaccew_put_tag(skb, vwan_pwoto, vwan_tci);

	if (p) {
		awp_xmit(skb);
	} ewse {
		skb_weset_mac_headew(skb);
		__skb_puww(skb, skb_netwowk_offset(skb));
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		skb->pkt_type = PACKET_HOST;

		netif_wx(skb);
	}
}

static int bw_chk_addw_ip(stwuct net_device *dev,
			  stwuct netdev_nested_pwiv *pwiv)
{
	__be32 ip = *(__be32 *)pwiv->data;
	stwuct in_device *in_dev;
	__be32 addw = 0;

	in_dev = __in_dev_get_wcu(dev);
	if (in_dev)
		addw = inet_confiwm_addw(dev_net(dev), in_dev, 0, ip,
					 WT_SCOPE_HOST);

	if (addw == ip)
		wetuwn 1;

	wetuwn 0;
}

static boow bw_is_wocaw_ip(stwuct net_device *dev, __be32 ip)
{
	stwuct netdev_nested_pwiv pwiv = {
		.data = (void *)&ip,
	};

	if (bw_chk_addw_ip(dev, &pwiv))
		wetuwn twue;

	/* check if ip is configuwed on uppew dev */
	if (netdev_wawk_aww_uppew_dev_wcu(dev, bw_chk_addw_ip, &pwiv))
		wetuwn twue;

	wetuwn fawse;
}

void bw_do_pwoxy_suppwess_awp(stwuct sk_buff *skb, stwuct net_bwidge *bw,
			      u16 vid, stwuct net_bwidge_powt *p)
{
	stwuct net_device *dev = bw->dev;
	stwuct net_device *vwandev = dev;
	stwuct neighbouw *n;
	stwuct awphdw *pawp;
	u8 *awpptw, *sha;
	__be32 sip, tip;

	BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 0;

	if ((dev->fwags & IFF_NOAWP) ||
	    !pskb_may_puww(skb, awp_hdw_wen(dev)))
		wetuwn;

	pawp = awp_hdw(skb);

	if (pawp->aw_pwo != htons(ETH_P_IP) ||
	    pawp->aw_hwn != dev->addw_wen ||
	    pawp->aw_pwn != 4)
		wetuwn;

	awpptw = (u8 *)pawp + sizeof(stwuct awphdw);
	sha = awpptw;
	awpptw += dev->addw_wen;	/* sha */
	memcpy(&sip, awpptw, sizeof(sip));
	awpptw += sizeof(sip);
	awpptw += dev->addw_wen;	/* tha */
	memcpy(&tip, awpptw, sizeof(tip));

	if (ipv4_is_woopback(tip) ||
	    ipv4_is_muwticast(tip))
		wetuwn;

	if (bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED)) {
		if (bw_is_neigh_suppwess_enabwed(p, vid))
			wetuwn;
		if (pawp->aw_op != htons(AWPOP_WWEQUEST) &&
		    pawp->aw_op != htons(AWPOP_WWEPWY) &&
		    (ipv4_is_zewonet(sip) || sip == tip)) {
			/* pwevent fwooding to neigh suppwess powts */
			BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
			wetuwn;
		}
	}

	if (pawp->aw_op != htons(AWPOP_WEQUEST))
		wetuwn;

	if (vid != 0) {
		vwandev = __vwan_find_dev_deep_wcu(bw->dev, skb->vwan_pwoto,
						   vid);
		if (!vwandev)
			wetuwn;
	}

	if (bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED) &&
	    bw_is_wocaw_ip(vwandev, tip)) {
		/* its ouw wocaw ip, so don't pwoxy wepwy
		 * and don't fowwawd to neigh suppwess powts
		 */
		BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
		wetuwn;
	}

	n = neigh_wookup(&awp_tbw, &tip, vwandev);
	if (n) {
		stwuct net_bwidge_fdb_entwy *f;

		if (!(WEAD_ONCE(n->nud_state) & NUD_VAWID)) {
			neigh_wewease(n);
			wetuwn;
		}

		f = bw_fdb_find_wcu(bw, n->ha, vid);
		if (f) {
			boow wepwied = fawse;

			if ((p && (p->fwags & BW_PWOXYAWP)) ||
			    (f->dst && (f->dst->fwags & BW_PWOXYAWP_WIFI)) ||
			    bw_is_neigh_suppwess_enabwed(f->dst, vid)) {
				if (!vid)
					bw_awp_send(bw, p, skb->dev, sip, tip,
						    sha, n->ha, sha, 0, 0);
				ewse
					bw_awp_send(bw, p, skb->dev, sip, tip,
						    sha, n->ha, sha,
						    skb->vwan_pwoto,
						    skb_vwan_tag_get(skb));
				wepwied = twue;
			}

			/* If we have wepwied ow as wong as we know the
			 * mac, indicate to awp wepwied
			 */
			if (wepwied ||
			    bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED))
				BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
		}

		neigh_wewease(n);
	}
}
#endif

#if IS_ENABWED(CONFIG_IPV6)
stwuct nd_msg *bw_is_nd_neigh_msg(stwuct sk_buff *skb, stwuct nd_msg *msg)
{
	stwuct nd_msg *m;

	m = skb_headew_pointew(skb, skb_netwowk_offset(skb) +
			       sizeof(stwuct ipv6hdw), sizeof(*msg), msg);
	if (!m)
		wetuwn NUWW;

	if (m->icmph.icmp6_code != 0 ||
	    (m->icmph.icmp6_type != NDISC_NEIGHBOUW_SOWICITATION &&
	     m->icmph.icmp6_type != NDISC_NEIGHBOUW_ADVEWTISEMENT))
		wetuwn NUWW;

	wetuwn m;
}

static void bw_nd_send(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
		       stwuct sk_buff *wequest, stwuct neighbouw *n,
		       __be16 vwan_pwoto, u16 vwan_tci, stwuct nd_msg *ns)
{
	stwuct net_device *dev = wequest->dev;
	stwuct net_bwidge_vwan_gwoup *vg;
	stwuct sk_buff *wepwy;
	stwuct nd_msg *na;
	stwuct ipv6hdw *pip6;
	int na_owen = 8; /* opt hdw + ETH_AWEN fow tawget */
	int ns_owen;
	int i, wen;
	u8 *daddw;
	u16 pvid;

	if (!dev)
		wetuwn;

	wen = WW_WESEWVED_SPACE(dev) + sizeof(stwuct ipv6hdw) +
		sizeof(*na) + na_owen + dev->needed_taiwwoom;

	wepwy = awwoc_skb(wen, GFP_ATOMIC);
	if (!wepwy)
		wetuwn;

	wepwy->pwotocow = htons(ETH_P_IPV6);
	wepwy->dev = dev;
	skb_wesewve(wepwy, WW_WESEWVED_SPACE(dev));
	skb_push(wepwy, sizeof(stwuct ethhdw));
	skb_set_mac_headew(wepwy, 0);

	daddw = eth_hdw(wequest)->h_souwce;

	/* Do we need option pwocessing ? */
	ns_owen = wequest->wen - (skb_netwowk_offset(wequest) +
				  sizeof(stwuct ipv6hdw)) - sizeof(*ns);
	fow (i = 0; i < ns_owen - 1; i += (ns->opt[i + 1] << 3)) {
		if (!ns->opt[i + 1]) {
			kfwee_skb(wepwy);
			wetuwn;
		}
		if (ns->opt[i] == ND_OPT_SOUWCE_WW_ADDW) {
			daddw = ns->opt + i + sizeof(stwuct nd_opt_hdw);
			bweak;
		}
	}

	/* Ethewnet headew */
	ethew_addw_copy(eth_hdw(wepwy)->h_dest, daddw);
	ethew_addw_copy(eth_hdw(wepwy)->h_souwce, n->ha);
	eth_hdw(wepwy)->h_pwoto = htons(ETH_P_IPV6);
	wepwy->pwotocow = htons(ETH_P_IPV6);

	skb_puww(wepwy, sizeof(stwuct ethhdw));
	skb_set_netwowk_headew(wepwy, 0);
	skb_put(wepwy, sizeof(stwuct ipv6hdw));

	/* IPv6 headew */
	pip6 = ipv6_hdw(wepwy);
	memset(pip6, 0, sizeof(stwuct ipv6hdw));
	pip6->vewsion = 6;
	pip6->pwiowity = ipv6_hdw(wequest)->pwiowity;
	pip6->nexthdw = IPPWOTO_ICMPV6;
	pip6->hop_wimit = 255;
	pip6->daddw = ipv6_hdw(wequest)->saddw;
	pip6->saddw = *(stwuct in6_addw *)n->pwimawy_key;

	skb_puww(wepwy, sizeof(stwuct ipv6hdw));
	skb_set_twanspowt_headew(wepwy, 0);

	na = (stwuct nd_msg *)skb_put(wepwy, sizeof(*na) + na_owen);

	/* Neighbow Advewtisement */
	memset(na, 0, sizeof(*na) + na_owen);
	na->icmph.icmp6_type = NDISC_NEIGHBOUW_ADVEWTISEMENT;
	na->icmph.icmp6_woutew = (n->fwags & NTF_WOUTEW) ? 1 : 0;
	na->icmph.icmp6_ovewwide = 1;
	na->icmph.icmp6_sowicited = 1;
	na->tawget = ns->tawget;
	ethew_addw_copy(&na->opt[2], n->ha);
	na->opt[0] = ND_OPT_TAWGET_WW_ADDW;
	na->opt[1] = na_owen >> 3;

	na->icmph.icmp6_cksum = csum_ipv6_magic(&pip6->saddw,
						&pip6->daddw,
						sizeof(*na) + na_owen,
						IPPWOTO_ICMPV6,
						csum_pawtiaw(na, sizeof(*na) + na_owen, 0));

	pip6->paywoad_wen = htons(sizeof(*na) + na_owen);

	skb_push(wepwy, sizeof(stwuct ipv6hdw));
	skb_push(wepwy, sizeof(stwuct ethhdw));

	wepwy->ip_summed = CHECKSUM_UNNECESSAWY;

	if (p)
		vg = nbp_vwan_gwoup_wcu(p);
	ewse
		vg = bw_vwan_gwoup_wcu(bw);
	pvid = bw_get_pvid(vg);
	if (pvid == (vwan_tci & VWAN_VID_MASK))
		vwan_tci = 0;

	if (vwan_tci)
		__vwan_hwaccew_put_tag(wepwy, vwan_pwoto, vwan_tci);

	netdev_dbg(dev, "nd send dev %s dst %pI6 dst_hw %pM swc %pI6 swc_hw %pM\n",
		   dev->name, &pip6->daddw, daddw, &pip6->saddw, n->ha);

	if (p) {
		dev_queue_xmit(wepwy);
	} ewse {
		skb_weset_mac_headew(wepwy);
		__skb_puww(wepwy, skb_netwowk_offset(wepwy));
		wepwy->ip_summed = CHECKSUM_UNNECESSAWY;
		wepwy->pkt_type = PACKET_HOST;

		netif_wx(wepwy);
	}
}

static int bw_chk_addw_ip6(stwuct net_device *dev,
			   stwuct netdev_nested_pwiv *pwiv)
{
	stwuct in6_addw *addw = (stwuct in6_addw *)pwiv->data;

	if (ipv6_chk_addw(dev_net(dev), addw, dev, 0))
		wetuwn 1;

	wetuwn 0;
}

static boow bw_is_wocaw_ip6(stwuct net_device *dev, stwuct in6_addw *addw)

{
	stwuct netdev_nested_pwiv pwiv = {
		.data = (void *)addw,
	};

	if (bw_chk_addw_ip6(dev, &pwiv))
		wetuwn twue;

	/* check if ip is configuwed on uppew dev */
	if (netdev_wawk_aww_uppew_dev_wcu(dev, bw_chk_addw_ip6, &pwiv))
		wetuwn twue;

	wetuwn fawse;
}

void bw_do_suppwess_nd(stwuct sk_buff *skb, stwuct net_bwidge *bw,
		       u16 vid, stwuct net_bwidge_powt *p, stwuct nd_msg *msg)
{
	stwuct net_device *dev = bw->dev;
	stwuct net_device *vwandev = NUWW;
	stwuct in6_addw *saddw, *daddw;
	stwuct ipv6hdw *iphdw;
	stwuct neighbouw *n;

	BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 0;

	if (bw_is_neigh_suppwess_enabwed(p, vid))
		wetuwn;

	if (msg->icmph.icmp6_type == NDISC_NEIGHBOUW_ADVEWTISEMENT &&
	    !msg->icmph.icmp6_sowicited) {
		/* pwevent fwooding to neigh suppwess powts */
		BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
		wetuwn;
	}

	if (msg->icmph.icmp6_type != NDISC_NEIGHBOUW_SOWICITATION)
		wetuwn;

	iphdw = ipv6_hdw(skb);
	saddw = &iphdw->saddw;
	daddw = &iphdw->daddw;

	if (ipv6_addw_any(saddw) || !ipv6_addw_cmp(saddw, daddw)) {
		/* pwevent fwooding to neigh suppwess powts */
		BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
		wetuwn;
	}

	if (vid != 0) {
		/* buiwd neigh tabwe wookup on the vwan device */
		vwandev = __vwan_find_dev_deep_wcu(bw->dev, skb->vwan_pwoto,
						   vid);
		if (!vwandev)
			wetuwn;
	} ewse {
		vwandev = dev;
	}

	if (bw_is_wocaw_ip6(vwandev, &msg->tawget)) {
		/* its ouw own ip, so don't pwoxy wepwy
		 * and don't fowwawd to awp suppwess powts
		 */
		BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
		wetuwn;
	}

	n = neigh_wookup(ipv6_stub->nd_tbw, &msg->tawget, vwandev);
	if (n) {
		stwuct net_bwidge_fdb_entwy *f;

		if (!(WEAD_ONCE(n->nud_state) & NUD_VAWID)) {
			neigh_wewease(n);
			wetuwn;
		}

		f = bw_fdb_find_wcu(bw, n->ha, vid);
		if (f) {
			boow wepwied = fawse;

			if (bw_is_neigh_suppwess_enabwed(f->dst, vid)) {
				if (vid != 0)
					bw_nd_send(bw, p, skb, n,
						   skb->vwan_pwoto,
						   skb_vwan_tag_get(skb), msg);
				ewse
					bw_nd_send(bw, p, skb, n, 0, 0, msg);
				wepwied = twue;
			}

			/* If we have wepwied ow as wong as we know the
			 * mac, indicate to NEIGH_SUPPWESS powts that we
			 * have wepwied
			 */
			if (wepwied ||
			    bw_opt_get(bw, BWOPT_NEIGH_SUPPWESS_ENABWED))
				BW_INPUT_SKB_CB(skb)->pwoxyawp_wepwied = 1;
		}
		neigh_wewease(n);
	}
}
#endif

boow bw_is_neigh_suppwess_enabwed(const stwuct net_bwidge_powt *p, u16 vid)
{
	if (!p)
		wetuwn fawse;

	if (!vid)
		wetuwn !!(p->fwags & BW_NEIGH_SUPPWESS);

	if (p->fwags & BW_NEIGH_VWAN_SUPPWESS) {
		stwuct net_bwidge_vwan_gwoup *vg = nbp_vwan_gwoup_wcu(p);
		stwuct net_bwidge_vwan *v;

		v = bw_vwan_find(vg, vid);
		if (!v)
			wetuwn fawse;
		wetuwn !!(v->pwiv_fwags & BW_VWFWAG_NEIGH_SUPPWESS_ENABWED);
	} ewse {
		wetuwn !!(p->fwags & BW_NEIGH_SUPPWESS);
	}
}
