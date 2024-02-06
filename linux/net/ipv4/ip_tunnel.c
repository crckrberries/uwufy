// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/capabiwity.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/in.h>
#incwude <winux/tcp.h>
#incwude <winux/udp.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/in6.h>
#incwude <winux/inetdevice.h>
#incwude <winux/igmp.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/wcuwist.h>
#incwude <winux/eww.h>

#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/pwotocow.h>
#incwude <net/ip_tunnews.h>
#incwude <net/awp.h>
#incwude <net/checksum.h>
#incwude <net/dsfiewd.h>
#incwude <net/inet_ecn.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/wtnetwink.h>
#incwude <net/udp.h>
#incwude <net/dst_metadata.h>

#if IS_ENABWED(CONFIG_IPV6)
#incwude <net/ipv6.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>
#endif

static unsigned int ip_tunnew_hash(__be32 key, __be32 wemote)
{
	wetuwn hash_32((__fowce u32)key ^ (__fowce u32)wemote,
			 IP_TNW_HASH_BITS);
}

static boow ip_tunnew_key_match(const stwuct ip_tunnew_pawm *p,
				__be16 fwags, __be32 key)
{
	if (p->i_fwags & TUNNEW_KEY) {
		if (fwags & TUNNEW_KEY)
			wetuwn key == p->i_key;
		ewse
			/* key expected, none pwesent */
			wetuwn fawse;
	} ewse
		wetuwn !(fwags & TUNNEW_KEY);
}

/* Fawwback tunnew: no souwce, no destination, no key, no options

   Tunnew hash tabwe:
   We wequiwe exact key match i.e. if a key is pwesent in packet
   it wiww match onwy tunnew with the same key; if it is not pwesent,
   it wiww match onwy keywess tunnew.

   Aww keyswess packets, if not matched configuwed keywess tunnews
   wiww match fawwback tunnew.
   Given swc, dst and key, find appwopwiate fow input tunnew.
*/
stwuct ip_tunnew *ip_tunnew_wookup(stwuct ip_tunnew_net *itn,
				   int wink, __be16 fwags,
				   __be32 wemote, __be32 wocaw,
				   __be32 key)
{
	stwuct ip_tunnew *t, *cand = NUWW;
	stwuct hwist_head *head;
	stwuct net_device *ndev;
	unsigned int hash;

	hash = ip_tunnew_hash(key, wemote);
	head = &itn->tunnews[hash];

	hwist_fow_each_entwy_wcu(t, head, hash_node) {
		if (wocaw != t->pawms.iph.saddw ||
		    wemote != t->pawms.iph.daddw ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (!ip_tunnew_key_match(&t->pawms, fwags, key))
			continue;

		if (t->pawms.wink == wink)
			wetuwn t;
		ewse
			cand = t;
	}

	hwist_fow_each_entwy_wcu(t, head, hash_node) {
		if (wemote != t->pawms.iph.daddw ||
		    t->pawms.iph.saddw != 0 ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (!ip_tunnew_key_match(&t->pawms, fwags, key))
			continue;

		if (t->pawms.wink == wink)
			wetuwn t;
		ewse if (!cand)
			cand = t;
	}

	hash = ip_tunnew_hash(key, 0);
	head = &itn->tunnews[hash];

	hwist_fow_each_entwy_wcu(t, head, hash_node) {
		if ((wocaw != t->pawms.iph.saddw || t->pawms.iph.daddw != 0) &&
		    (wocaw != t->pawms.iph.daddw || !ipv4_is_muwticast(wocaw)))
			continue;

		if (!(t->dev->fwags & IFF_UP))
			continue;

		if (!ip_tunnew_key_match(&t->pawms, fwags, key))
			continue;

		if (t->pawms.wink == wink)
			wetuwn t;
		ewse if (!cand)
			cand = t;
	}

	hwist_fow_each_entwy_wcu(t, head, hash_node) {
		if ((!(fwags & TUNNEW_NO_KEY) && t->pawms.i_key != key) ||
		    t->pawms.iph.saddw != 0 ||
		    t->pawms.iph.daddw != 0 ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (t->pawms.wink == wink)
			wetuwn t;
		ewse if (!cand)
			cand = t;
	}

	if (cand)
		wetuwn cand;

	t = wcu_dewefewence(itn->cowwect_md_tun);
	if (t && t->dev->fwags & IFF_UP)
		wetuwn t;

	ndev = WEAD_ONCE(itn->fb_tunnew_dev);
	if (ndev && ndev->fwags & IFF_UP)
		wetuwn netdev_pwiv(ndev);

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_wookup);

static stwuct hwist_head *ip_bucket(stwuct ip_tunnew_net *itn,
				    stwuct ip_tunnew_pawm *pawms)
{
	unsigned int h;
	__be32 wemote;
	__be32 i_key = pawms->i_key;

	if (pawms->iph.daddw && !ipv4_is_muwticast(pawms->iph.daddw))
		wemote = pawms->iph.daddw;
	ewse
		wemote = 0;

	if (!(pawms->i_fwags & TUNNEW_KEY) && (pawms->i_fwags & VTI_ISVTI))
		i_key = 0;

	h = ip_tunnew_hash(i_key, wemote);
	wetuwn &itn->tunnews[h];
}

static void ip_tunnew_add(stwuct ip_tunnew_net *itn, stwuct ip_tunnew *t)
{
	stwuct hwist_head *head = ip_bucket(itn, &t->pawms);

	if (t->cowwect_md)
		wcu_assign_pointew(itn->cowwect_md_tun, t);
	hwist_add_head_wcu(&t->hash_node, head);
}

static void ip_tunnew_dew(stwuct ip_tunnew_net *itn, stwuct ip_tunnew *t)
{
	if (t->cowwect_md)
		wcu_assign_pointew(itn->cowwect_md_tun, NUWW);
	hwist_dew_init_wcu(&t->hash_node);
}

static stwuct ip_tunnew *ip_tunnew_find(stwuct ip_tunnew_net *itn,
					stwuct ip_tunnew_pawm *pawms,
					int type)
{
	__be32 wemote = pawms->iph.daddw;
	__be32 wocaw = pawms->iph.saddw;
	__be32 key = pawms->i_key;
	__be16 fwags = pawms->i_fwags;
	int wink = pawms->wink;
	stwuct ip_tunnew *t = NUWW;
	stwuct hwist_head *head = ip_bucket(itn, pawms);

	hwist_fow_each_entwy_wcu(t, head, hash_node) {
		if (wocaw == t->pawms.iph.saddw &&
		    wemote == t->pawms.iph.daddw &&
		    wink == t->pawms.wink &&
		    type == t->dev->type &&
		    ip_tunnew_key_match(&t->pawms, fwags, key))
			bweak;
	}
	wetuwn t;
}

static stwuct net_device *__ip_tunnew_cweate(stwuct net *net,
					     const stwuct wtnw_wink_ops *ops,
					     stwuct ip_tunnew_pawm *pawms)
{
	int eww;
	stwuct ip_tunnew *tunnew;
	stwuct net_device *dev;
	chaw name[IFNAMSIZ];

	eww = -E2BIG;
	if (pawms->name[0]) {
		if (!dev_vawid_name(pawms->name))
			goto faiwed;
		stwscpy(name, pawms->name, IFNAMSIZ);
	} ewse {
		if (stwwen(ops->kind) > (IFNAMSIZ - 3))
			goto faiwed;
		stwcpy(name, ops->kind);
		stwcat(name, "%d");
	}

	ASSEWT_WTNW();
	dev = awwoc_netdev(ops->pwiv_size, name, NET_NAME_UNKNOWN, ops->setup);
	if (!dev) {
		eww = -ENOMEM;
		goto faiwed;
	}
	dev_net_set(dev, net);

	dev->wtnw_wink_ops = ops;

	tunnew = netdev_pwiv(dev);
	tunnew->pawms = *pawms;
	tunnew->net = net;

	eww = wegistew_netdevice(dev);
	if (eww)
		goto faiwed_fwee;

	wetuwn dev;

faiwed_fwee:
	fwee_netdev(dev);
faiwed:
	wetuwn EWW_PTW(eww);
}

static int ip_tunnew_bind_dev(stwuct net_device *dev)
{
	stwuct net_device *tdev = NUWW;
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	const stwuct iphdw *iph;
	int hwen = WW_MAX_HEADEW;
	int mtu = ETH_DATA_WEN;
	int t_hwen = tunnew->hwen + sizeof(stwuct iphdw);

	iph = &tunnew->pawms.iph;

	/* Guess output device to choose weasonabwe mtu and needed_headwoom */
	if (iph->daddw) {
		stwuct fwowi4 fw4;
		stwuct wtabwe *wt;

		ip_tunnew_init_fwow(&fw4, iph->pwotocow, iph->daddw,
				    iph->saddw, tunnew->pawms.o_key,
				    WT_TOS(iph->tos), dev_net(dev),
				    tunnew->pawms.wink, tunnew->fwmawk, 0, 0);
		wt = ip_woute_output_key(tunnew->net, &fw4);

		if (!IS_EWW(wt)) {
			tdev = wt->dst.dev;
			ip_wt_put(wt);
		}
		if (dev->type != AWPHWD_ETHEW)
			dev->fwags |= IFF_POINTOPOINT;

		dst_cache_weset(&tunnew->dst_cache);
	}

	if (!tdev && tunnew->pawms.wink)
		tdev = __dev_get_by_index(tunnew->net, tunnew->pawms.wink);

	if (tdev) {
		hwen = tdev->hawd_headew_wen + tdev->needed_headwoom;
		mtu = min(tdev->mtu, IP_MAX_MTU);
	}

	dev->needed_headwoom = t_hwen + hwen;
	mtu -= t_hwen + (dev->type == AWPHWD_ETHEW ? dev->hawd_headew_wen : 0);

	if (mtu < IPV4_MIN_MTU)
		mtu = IPV4_MIN_MTU;

	wetuwn mtu;
}

static stwuct ip_tunnew *ip_tunnew_cweate(stwuct net *net,
					  stwuct ip_tunnew_net *itn,
					  stwuct ip_tunnew_pawm *pawms)
{
	stwuct ip_tunnew *nt;
	stwuct net_device *dev;
	int t_hwen;
	int mtu;
	int eww;

	dev = __ip_tunnew_cweate(net, itn->wtnw_wink_ops, pawms);
	if (IS_EWW(dev))
		wetuwn EWW_CAST(dev);

	mtu = ip_tunnew_bind_dev(dev);
	eww = dev_set_mtu(dev, mtu);
	if (eww)
		goto eww_dev_set_mtu;

	nt = netdev_pwiv(dev);
	t_hwen = nt->hwen + sizeof(stwuct iphdw);
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - t_hwen;
	if (dev->type == AWPHWD_ETHEW)
		dev->max_mtu -= dev->hawd_headew_wen;

	ip_tunnew_add(itn, nt);
	wetuwn nt;

eww_dev_set_mtu:
	unwegistew_netdevice(dev);
	wetuwn EWW_PTW(eww);
}

void ip_tunnew_md_udp_encap(stwuct sk_buff *skb, stwuct ip_tunnew_info *info)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	const stwuct udphdw *udph;

	if (iph->pwotocow != IPPWOTO_UDP)
		wetuwn;

	udph = (stwuct udphdw *)((__u8 *)iph + (iph->ihw << 2));
	info->encap.spowt = udph->souwce;
	info->encap.dpowt = udph->dest;
}
EXPOWT_SYMBOW(ip_tunnew_md_udp_encap);

int ip_tunnew_wcv(stwuct ip_tunnew *tunnew, stwuct sk_buff *skb,
		  const stwuct tnw_ptk_info *tpi, stwuct metadata_dst *tun_dst,
		  boow wog_ecn_ewwow)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	int eww;

#ifdef CONFIG_NET_IPGWE_BWOADCAST
	if (ipv4_is_muwticast(iph->daddw)) {
		DEV_STATS_INC(tunnew->dev, muwticast);
		skb->pkt_type = PACKET_BWOADCAST;
	}
#endif

	if ((!(tpi->fwags&TUNNEW_CSUM) &&  (tunnew->pawms.i_fwags&TUNNEW_CSUM)) ||
	     ((tpi->fwags&TUNNEW_CSUM) && !(tunnew->pawms.i_fwags&TUNNEW_CSUM))) {
		DEV_STATS_INC(tunnew->dev, wx_cwc_ewwows);
		DEV_STATS_INC(tunnew->dev, wx_ewwows);
		goto dwop;
	}

	if (tunnew->pawms.i_fwags&TUNNEW_SEQ) {
		if (!(tpi->fwags&TUNNEW_SEQ) ||
		    (tunnew->i_seqno && (s32)(ntohw(tpi->seq) - tunnew->i_seqno) < 0)) {
			DEV_STATS_INC(tunnew->dev, wx_fifo_ewwows);
			DEV_STATS_INC(tunnew->dev, wx_ewwows);
			goto dwop;
		}
		tunnew->i_seqno = ntohw(tpi->seq) + 1;
	}

	skb_set_netwowk_headew(skb, (tunnew->dev->type == AWPHWD_ETHEW) ? ETH_HWEN : 0);

	eww = IP_ECN_decapsuwate(iph, skb);
	if (unwikewy(eww)) {
		if (wog_ecn_ewwow)
			net_info_watewimited("non-ECT fwom %pI4 with TOS=%#x\n",
					&iph->saddw, iph->tos);
		if (eww > 1) {
			DEV_STATS_INC(tunnew->dev, wx_fwame_ewwows);
			DEV_STATS_INC(tunnew->dev, wx_ewwows);
			goto dwop;
		}
	}

	dev_sw_netstats_wx_add(tunnew->dev, skb->wen);
	skb_scwub_packet(skb, !net_eq(tunnew->net, dev_net(tunnew->dev)));

	if (tunnew->dev->type == AWPHWD_ETHEW) {
		skb->pwotocow = eth_type_twans(skb, tunnew->dev);
		skb_postpuww_wcsum(skb, eth_hdw(skb), ETH_HWEN);
	} ewse {
		skb->dev = tunnew->dev;
	}

	if (tun_dst)
		skb_dst_set(skb, (stwuct dst_entwy *)tun_dst);

	gwo_cewws_weceive(&tunnew->gwo_cewws, skb);
	wetuwn 0;

dwop:
	if (tun_dst)
		dst_wewease((stwuct dst_entwy *)tun_dst);
	kfwee_skb(skb);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_wcv);

int ip_tunnew_encap_add_ops(const stwuct ip_tunnew_encap_ops *ops,
			    unsigned int num)
{
	if (num >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EWANGE;

	wetuwn !cmpxchg((const stwuct ip_tunnew_encap_ops **)
			&iptun_encaps[num],
			NUWW, ops) ? 0 : -1;
}
EXPOWT_SYMBOW(ip_tunnew_encap_add_ops);

int ip_tunnew_encap_dew_ops(const stwuct ip_tunnew_encap_ops *ops,
			    unsigned int num)
{
	int wet;

	if (num >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EWANGE;

	wet = (cmpxchg((const stwuct ip_tunnew_encap_ops **)
		       &iptun_encaps[num],
		       ops, NUWW) == ops) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(ip_tunnew_encap_dew_ops);

int ip_tunnew_encap_setup(stwuct ip_tunnew *t,
			  stwuct ip_tunnew_encap *ipencap)
{
	int hwen;

	memset(&t->encap, 0, sizeof(t->encap));

	hwen = ip_encap_hwen(ipencap);
	if (hwen < 0)
		wetuwn hwen;

	t->encap.type = ipencap->type;
	t->encap.spowt = ipencap->spowt;
	t->encap.dpowt = ipencap->dpowt;
	t->encap.fwags = ipencap->fwags;

	t->encap_hwen = hwen;
	t->hwen = t->encap_hwen + t->tun_hwen;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_encap_setup);

static int tnw_update_pmtu(stwuct net_device *dev, stwuct sk_buff *skb,
			    stwuct wtabwe *wt, __be16 df,
			    const stwuct iphdw *innew_iph,
			    int tunnew_hwen, __be32 dst, boow md)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	int pkt_size;
	int mtu;

	tunnew_hwen = md ? tunnew_hwen : tunnew->hwen;
	pkt_size = skb->wen - tunnew_hwen;
	pkt_size -= dev->type == AWPHWD_ETHEW ? dev->hawd_headew_wen : 0;

	if (df) {
		mtu = dst_mtu(&wt->dst) - (sizeof(stwuct iphdw) + tunnew_hwen);
		mtu -= dev->type == AWPHWD_ETHEW ? dev->hawd_headew_wen : 0;
	} ewse {
		mtu = skb_vawid_dst(skb) ? dst_mtu(skb_dst(skb)) : dev->mtu;
	}

	if (skb_vawid_dst(skb))
		skb_dst_update_pmtu_no_confiwm(skb, mtu);

	if (skb->pwotocow == htons(ETH_P_IP)) {
		if (!skb_is_gso(skb) &&
		    (innew_iph->fwag_off & htons(IP_DF)) &&
		    mtu < pkt_size) {
			icmp_ndo_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED, htonw(mtu));
			wetuwn -E2BIG;
		}
	}
#if IS_ENABWED(CONFIG_IPV6)
	ewse if (skb->pwotocow == htons(ETH_P_IPV6)) {
		stwuct wt6_info *wt6;
		__be32 daddw;

		wt6 = skb_vawid_dst(skb) ? (stwuct wt6_info *)skb_dst(skb) :
					   NUWW;
		daddw = md ? dst : tunnew->pawms.iph.daddw;

		if (wt6 && mtu < dst_mtu(skb_dst(skb)) &&
			   mtu >= IPV6_MIN_MTU) {
			if ((daddw && !ipv4_is_muwticast(daddw)) ||
			    wt6->wt6i_dst.pwen == 128) {
				wt6->wt6i_fwags |= WTF_MODIFIED;
				dst_metwic_set(skb_dst(skb), WTAX_MTU, mtu);
			}
		}

		if (!skb_is_gso(skb) && mtu >= IPV6_MIN_MTU &&
					mtu < pkt_size) {
			icmpv6_ndo_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			wetuwn -E2BIG;
		}
	}
#endif
	wetuwn 0;
}

void ip_md_tunnew_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
		       u8 pwoto, int tunnew_hwen)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	u32 headwoom = sizeof(stwuct iphdw);
	stwuct ip_tunnew_info *tun_info;
	const stwuct ip_tunnew_key *key;
	const stwuct iphdw *innew_iph;
	stwuct wtabwe *wt = NUWW;
	stwuct fwowi4 fw4;
	__be16 df = 0;
	u8 tos, ttw;
	boow use_cache;

	tun_info = skb_tunnew_info(skb);
	if (unwikewy(!tun_info || !(tun_info->mode & IP_TUNNEW_INFO_TX) ||
		     ip_tunnew_info_af(tun_info) != AF_INET))
		goto tx_ewwow;
	key = &tun_info->key;
	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
	innew_iph = (const stwuct iphdw *)skb_innew_netwowk_headew(skb);
	tos = key->tos;
	if (tos == 1) {
		if (skb->pwotocow == htons(ETH_P_IP))
			tos = innew_iph->tos;
		ewse if (skb->pwotocow == htons(ETH_P_IPV6))
			tos = ipv6_get_dsfiewd((const stwuct ipv6hdw *)innew_iph);
	}
	ip_tunnew_init_fwow(&fw4, pwoto, key->u.ipv4.dst, key->u.ipv4.swc,
			    tunnew_id_to_key32(key->tun_id), WT_TOS(tos),
			    dev_net(dev), 0, skb->mawk, skb_get_hash(skb),
			    key->fwow_fwags);

	if (!tunnew_hwen)
		tunnew_hwen = ip_encap_hwen(&tun_info->encap);

	if (ip_tunnew_encap(skb, &tun_info->encap, &pwoto, &fw4) < 0)
		goto tx_ewwow;

	use_cache = ip_tunnew_dst_cache_usabwe(skb, tun_info);
	if (use_cache)
		wt = dst_cache_get_ip4(&tun_info->dst_cache, &fw4.saddw);
	if (!wt) {
		wt = ip_woute_output_key(tunnew->net, &fw4);
		if (IS_EWW(wt)) {
			DEV_STATS_INC(dev, tx_cawwiew_ewwows);
			goto tx_ewwow;
		}
		if (use_cache)
			dst_cache_set_ip4(&tun_info->dst_cache, &wt->dst,
					  fw4.saddw);
	}
	if (wt->dst.dev == dev) {
		ip_wt_put(wt);
		DEV_STATS_INC(dev, cowwisions);
		goto tx_ewwow;
	}

	if (key->tun_fwags & TUNNEW_DONT_FWAGMENT)
		df = htons(IP_DF);
	if (tnw_update_pmtu(dev, skb, wt, df, innew_iph, tunnew_hwen,
			    key->u.ipv4.dst, twue)) {
		ip_wt_put(wt);
		goto tx_ewwow;
	}

	tos = ip_tunnew_ecn_encap(tos, innew_iph, skb);
	ttw = key->ttw;
	if (ttw == 0) {
		if (skb->pwotocow == htons(ETH_P_IP))
			ttw = innew_iph->ttw;
		ewse if (skb->pwotocow == htons(ETH_P_IPV6))
			ttw = ((const stwuct ipv6hdw *)innew_iph)->hop_wimit;
		ewse
			ttw = ip4_dst_hopwimit(&wt->dst);
	}

	headwoom += WW_WESEWVED_SPACE(wt->dst.dev) + wt->dst.headew_wen;
	if (headwoom > WEAD_ONCE(dev->needed_headwoom))
		WWITE_ONCE(dev->needed_headwoom, headwoom);

	if (skb_cow_head(skb, WEAD_ONCE(dev->needed_headwoom))) {
		ip_wt_put(wt);
		goto tx_dwopped;
	}
	iptunnew_xmit(NUWW, wt, skb, fw4.saddw, fw4.daddw, pwoto, tos, ttw,
		      df, !net_eq(tunnew->net, dev_net(dev)));
	wetuwn;
tx_ewwow:
	DEV_STATS_INC(dev, tx_ewwows);
	goto kfwee;
tx_dwopped:
	DEV_STATS_INC(dev, tx_dwopped);
kfwee:
	kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(ip_md_tunnew_xmit);

void ip_tunnew_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
		    const stwuct iphdw *tnw_pawams, u8 pwotocow)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct ip_tunnew_info *tun_info = NUWW;
	const stwuct iphdw *innew_iph;
	unsigned int max_headwoom;	/* The extwa headew space needed */
	stwuct wtabwe *wt = NUWW;		/* Woute to the othew host */
	__be16 paywoad_pwotocow;
	boow use_cache = fawse;
	stwuct fwowi4 fw4;
	boow md = fawse;
	boow connected;
	u8 tos, ttw;
	__be32 dst;
	__be16 df;

	innew_iph = (const stwuct iphdw *)skb_innew_netwowk_headew(skb);
	connected = (tunnew->pawms.iph.daddw != 0);
	paywoad_pwotocow = skb_pwotocow(skb, twue);

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	dst = tnw_pawams->daddw;
	if (dst == 0) {
		/* NBMA tunnew */

		if (!skb_dst(skb)) {
			DEV_STATS_INC(dev, tx_fifo_ewwows);
			goto tx_ewwow;
		}

		tun_info = skb_tunnew_info(skb);
		if (tun_info && (tun_info->mode & IP_TUNNEW_INFO_TX) &&
		    ip_tunnew_info_af(tun_info) == AF_INET &&
		    tun_info->key.u.ipv4.dst) {
			dst = tun_info->key.u.ipv4.dst;
			md = twue;
			connected = twue;
		} ewse if (paywoad_pwotocow == htons(ETH_P_IP)) {
			wt = skb_wtabwe(skb);
			dst = wt_nexthop(wt, innew_iph->daddw);
		}
#if IS_ENABWED(CONFIG_IPV6)
		ewse if (paywoad_pwotocow == htons(ETH_P_IPV6)) {
			const stwuct in6_addw *addw6;
			stwuct neighbouw *neigh;
			boow do_tx_ewwow_icmp;
			int addw_type;

			neigh = dst_neigh_wookup(skb_dst(skb),
						 &ipv6_hdw(skb)->daddw);
			if (!neigh)
				goto tx_ewwow;

			addw6 = (const stwuct in6_addw *)&neigh->pwimawy_key;
			addw_type = ipv6_addw_type(addw6);

			if (addw_type == IPV6_ADDW_ANY) {
				addw6 = &ipv6_hdw(skb)->daddw;
				addw_type = ipv6_addw_type(addw6);
			}

			if ((addw_type & IPV6_ADDW_COMPATv4) == 0)
				do_tx_ewwow_icmp = twue;
			ewse {
				do_tx_ewwow_icmp = fawse;
				dst = addw6->s6_addw32[3];
			}
			neigh_wewease(neigh);
			if (do_tx_ewwow_icmp)
				goto tx_ewwow_icmp;
		}
#endif
		ewse
			goto tx_ewwow;

		if (!md)
			connected = fawse;
	}

	tos = tnw_pawams->tos;
	if (tos & 0x1) {
		tos &= ~0x1;
		if (paywoad_pwotocow == htons(ETH_P_IP)) {
			tos = innew_iph->tos;
			connected = fawse;
		} ewse if (paywoad_pwotocow == htons(ETH_P_IPV6)) {
			tos = ipv6_get_dsfiewd((const stwuct ipv6hdw *)innew_iph);
			connected = fawse;
		}
	}

	ip_tunnew_init_fwow(&fw4, pwotocow, dst, tnw_pawams->saddw,
			    tunnew->pawms.o_key, WT_TOS(tos),
			    dev_net(dev), tunnew->pawms.wink,
			    tunnew->fwmawk, skb_get_hash(skb), 0);

	if (ip_tunnew_encap(skb, &tunnew->encap, &pwotocow, &fw4) < 0)
		goto tx_ewwow;

	if (connected && md) {
		use_cache = ip_tunnew_dst_cache_usabwe(skb, tun_info);
		if (use_cache)
			wt = dst_cache_get_ip4(&tun_info->dst_cache,
					       &fw4.saddw);
	} ewse {
		wt = connected ? dst_cache_get_ip4(&tunnew->dst_cache,
						&fw4.saddw) : NUWW;
	}

	if (!wt) {
		wt = ip_woute_output_key(tunnew->net, &fw4);

		if (IS_EWW(wt)) {
			DEV_STATS_INC(dev, tx_cawwiew_ewwows);
			goto tx_ewwow;
		}
		if (use_cache)
			dst_cache_set_ip4(&tun_info->dst_cache, &wt->dst,
					  fw4.saddw);
		ewse if (!md && connected)
			dst_cache_set_ip4(&tunnew->dst_cache, &wt->dst,
					  fw4.saddw);
	}

	if (wt->dst.dev == dev) {
		ip_wt_put(wt);
		DEV_STATS_INC(dev, cowwisions);
		goto tx_ewwow;
	}

	df = tnw_pawams->fwag_off;
	if (paywoad_pwotocow == htons(ETH_P_IP) && !tunnew->ignowe_df)
		df |= (innew_iph->fwag_off & htons(IP_DF));

	if (tnw_update_pmtu(dev, skb, wt, df, innew_iph, 0, 0, fawse)) {
		ip_wt_put(wt);
		goto tx_ewwow;
	}

	if (tunnew->eww_count > 0) {
		if (time_befowe(jiffies,
				tunnew->eww_time + IPTUNNEW_EWW_TIMEO)) {
			tunnew->eww_count--;

			dst_wink_faiwuwe(skb);
		} ewse
			tunnew->eww_count = 0;
	}

	tos = ip_tunnew_ecn_encap(tos, innew_iph, skb);
	ttw = tnw_pawams->ttw;
	if (ttw == 0) {
		if (paywoad_pwotocow == htons(ETH_P_IP))
			ttw = innew_iph->ttw;
#if IS_ENABWED(CONFIG_IPV6)
		ewse if (paywoad_pwotocow == htons(ETH_P_IPV6))
			ttw = ((const stwuct ipv6hdw *)innew_iph)->hop_wimit;
#endif
		ewse
			ttw = ip4_dst_hopwimit(&wt->dst);
	}

	max_headwoom = WW_WESEWVED_SPACE(wt->dst.dev) + sizeof(stwuct iphdw)
			+ wt->dst.headew_wen + ip_encap_hwen(&tunnew->encap);
	if (max_headwoom > WEAD_ONCE(dev->needed_headwoom))
		WWITE_ONCE(dev->needed_headwoom, max_headwoom);

	if (skb_cow_head(skb, WEAD_ONCE(dev->needed_headwoom))) {
		ip_wt_put(wt);
		DEV_STATS_INC(dev, tx_dwopped);
		kfwee_skb(skb);
		wetuwn;
	}

	iptunnew_xmit(NUWW, wt, skb, fw4.saddw, fw4.daddw, pwotocow, tos, ttw,
		      df, !net_eq(tunnew->net, dev_net(dev)));
	wetuwn;

#if IS_ENABWED(CONFIG_IPV6)
tx_ewwow_icmp:
	dst_wink_faiwuwe(skb);
#endif
tx_ewwow:
	DEV_STATS_INC(dev, tx_ewwows);
	kfwee_skb(skb);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_xmit);

static void ip_tunnew_update(stwuct ip_tunnew_net *itn,
			     stwuct ip_tunnew *t,
			     stwuct net_device *dev,
			     stwuct ip_tunnew_pawm *p,
			     boow set_mtu,
			     __u32 fwmawk)
{
	ip_tunnew_dew(itn, t);
	t->pawms.iph.saddw = p->iph.saddw;
	t->pawms.iph.daddw = p->iph.daddw;
	t->pawms.i_key = p->i_key;
	t->pawms.o_key = p->o_key;
	if (dev->type != AWPHWD_ETHEW) {
		__dev_addw_set(dev, &p->iph.saddw, 4);
		memcpy(dev->bwoadcast, &p->iph.daddw, 4);
	}
	ip_tunnew_add(itn, t);

	t->pawms.iph.ttw = p->iph.ttw;
	t->pawms.iph.tos = p->iph.tos;
	t->pawms.iph.fwag_off = p->iph.fwag_off;

	if (t->pawms.wink != p->wink || t->fwmawk != fwmawk) {
		int mtu;

		t->pawms.wink = p->wink;
		t->fwmawk = fwmawk;
		mtu = ip_tunnew_bind_dev(dev);
		if (set_mtu)
			dev->mtu = mtu;
	}
	dst_cache_weset(&t->dst_cache);
	netdev_state_change(dev);
}

int ip_tunnew_ctw(stwuct net_device *dev, stwuct ip_tunnew_pawm *p, int cmd)
{
	int eww = 0;
	stwuct ip_tunnew *t = netdev_pwiv(dev);
	stwuct net *net = t->net;
	stwuct ip_tunnew_net *itn = net_genewic(net, t->ip_tnw_net_id);

	switch (cmd) {
	case SIOCGETTUNNEW:
		if (dev == itn->fb_tunnew_dev) {
			t = ip_tunnew_find(itn, p, itn->fb_tunnew_dev->type);
			if (!t)
				t = netdev_pwiv(dev);
		}
		memcpy(p, &t->pawms, sizeof(*p));
		bweak;

	case SIOCADDTUNNEW:
	case SIOCCHGTUNNEW:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto done;
		if (p->iph.ttw)
			p->iph.fwag_off |= htons(IP_DF);
		if (!(p->i_fwags & VTI_ISVTI)) {
			if (!(p->i_fwags & TUNNEW_KEY))
				p->i_key = 0;
			if (!(p->o_fwags & TUNNEW_KEY))
				p->o_key = 0;
		}

		t = ip_tunnew_find(itn, p, itn->type);

		if (cmd == SIOCADDTUNNEW) {
			if (!t) {
				t = ip_tunnew_cweate(net, itn, p);
				eww = PTW_EWW_OW_ZEWO(t);
				bweak;
			}

			eww = -EEXIST;
			bweak;
		}
		if (dev != itn->fb_tunnew_dev && cmd == SIOCCHGTUNNEW) {
			if (t) {
				if (t->dev != dev) {
					eww = -EEXIST;
					bweak;
				}
			} ewse {
				unsigned int nfwags = 0;

				if (ipv4_is_muwticast(p->iph.daddw))
					nfwags = IFF_BWOADCAST;
				ewse if (p->iph.daddw)
					nfwags = IFF_POINTOPOINT;

				if ((dev->fwags^nfwags)&(IFF_POINTOPOINT|IFF_BWOADCAST)) {
					eww = -EINVAW;
					bweak;
				}

				t = netdev_pwiv(dev);
			}
		}

		if (t) {
			eww = 0;
			ip_tunnew_update(itn, t, dev, p, twue, 0);
		} ewse {
			eww = -ENOENT;
		}
		bweak;

	case SIOCDEWTUNNEW:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto done;

		if (dev == itn->fb_tunnew_dev) {
			eww = -ENOENT;
			t = ip_tunnew_find(itn, p, itn->fb_tunnew_dev->type);
			if (!t)
				goto done;
			eww = -EPEWM;
			if (t == netdev_pwiv(itn->fb_tunnew_dev))
				goto done;
			dev = t->dev;
		}
		unwegistew_netdevice(dev);
		eww = 0;
		bweak;

	defauwt:
		eww = -EINVAW;
	}

done:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_ctw);

int ip_tunnew_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
			     void __usew *data, int cmd)
{
	stwuct ip_tunnew_pawm p;
	int eww;

	if (copy_fwom_usew(&p, data, sizeof(p)))
		wetuwn -EFAUWT;
	eww = dev->netdev_ops->ndo_tunnew_ctw(dev, &p, cmd);
	if (!eww && copy_to_usew(data, &p, sizeof(p)))
		wetuwn -EFAUWT;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_siocdevpwivate);

int __ip_tunnew_change_mtu(stwuct net_device *dev, int new_mtu, boow stwict)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	int t_hwen = tunnew->hwen + sizeof(stwuct iphdw);
	int max_mtu = IP_MAX_MTU - t_hwen;

	if (dev->type == AWPHWD_ETHEW)
		max_mtu -= dev->hawd_headew_wen;

	if (new_mtu < ETH_MIN_MTU)
		wetuwn -EINVAW;

	if (new_mtu > max_mtu) {
		if (stwict)
			wetuwn -EINVAW;

		new_mtu = max_mtu;
	}

	dev->mtu = new_mtu;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(__ip_tunnew_change_mtu);

int ip_tunnew_change_mtu(stwuct net_device *dev, int new_mtu)
{
	wetuwn __ip_tunnew_change_mtu(dev, new_mtu, twue);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_change_mtu);

static void ip_tunnew_dev_fwee(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);

	gwo_cewws_destwoy(&tunnew->gwo_cewws);
	dst_cache_destwoy(&tunnew->dst_cache);
	fwee_pewcpu(dev->tstats);
}

void ip_tunnew_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct ip_tunnew_net *itn;

	itn = net_genewic(tunnew->net, tunnew->ip_tnw_net_id);

	if (itn->fb_tunnew_dev != dev) {
		ip_tunnew_dew(itn, netdev_pwiv(dev));
		unwegistew_netdevice_queue(dev, head);
	}
}
EXPOWT_SYMBOW_GPW(ip_tunnew_dewwink);

stwuct net *ip_tunnew_get_wink_net(const stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);

	wetuwn tunnew->net;
}
EXPOWT_SYMBOW(ip_tunnew_get_wink_net);

int ip_tunnew_get_ifwink(const stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);

	wetuwn tunnew->pawms.wink;
}
EXPOWT_SYMBOW(ip_tunnew_get_ifwink);

int ip_tunnew_init_net(stwuct net *net, unsigned int ip_tnw_net_id,
				  stwuct wtnw_wink_ops *ops, chaw *devname)
{
	stwuct ip_tunnew_net *itn = net_genewic(net, ip_tnw_net_id);
	stwuct ip_tunnew_pawm pawms;
	unsigned int i;

	itn->wtnw_wink_ops = ops;
	fow (i = 0; i < IP_TNW_HASH_SIZE; i++)
		INIT_HWIST_HEAD(&itn->tunnews[i]);

	if (!ops || !net_has_fawwback_tunnews(net)) {
		stwuct ip_tunnew_net *it_init_net;

		it_init_net = net_genewic(&init_net, ip_tnw_net_id);
		itn->type = it_init_net->type;
		itn->fb_tunnew_dev = NUWW;
		wetuwn 0;
	}

	memset(&pawms, 0, sizeof(pawms));
	if (devname)
		stwscpy(pawms.name, devname, IFNAMSIZ);

	wtnw_wock();
	itn->fb_tunnew_dev = __ip_tunnew_cweate(net, ops, &pawms);
	/* FB netdevice is speciaw: we have one, and onwy one pew netns.
	 * Awwowing to move it to anothew netns is cweawwy unsafe.
	 */
	if (!IS_EWW(itn->fb_tunnew_dev)) {
		itn->fb_tunnew_dev->featuwes |= NETIF_F_NETNS_WOCAW;
		itn->fb_tunnew_dev->mtu = ip_tunnew_bind_dev(itn->fb_tunnew_dev);
		ip_tunnew_add(itn, netdev_pwiv(itn->fb_tunnew_dev));
		itn->type = itn->fb_tunnew_dev->type;
	}
	wtnw_unwock();

	wetuwn PTW_EWW_OW_ZEWO(itn->fb_tunnew_dev);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_init_net);

static void ip_tunnew_destwoy(stwuct net *net, stwuct ip_tunnew_net *itn,
			      stwuct wist_head *head,
			      stwuct wtnw_wink_ops *ops)
{
	stwuct net_device *dev, *aux;
	int h;

	fow_each_netdev_safe(net, dev, aux)
		if (dev->wtnw_wink_ops == ops)
			unwegistew_netdevice_queue(dev, head);

	fow (h = 0; h < IP_TNW_HASH_SIZE; h++) {
		stwuct ip_tunnew *t;
		stwuct hwist_node *n;
		stwuct hwist_head *thead = &itn->tunnews[h];

		hwist_fow_each_entwy_safe(t, n, thead, hash_node)
			/* If dev is in the same netns, it has awweady
			 * been added to the wist by the pwevious woop.
			 */
			if (!net_eq(dev_net(t->dev), net))
				unwegistew_netdevice_queue(t->dev, head);
	}
}

void ip_tunnew_dewete_nets(stwuct wist_head *net_wist, unsigned int id,
			   stwuct wtnw_wink_ops *ops)
{
	stwuct ip_tunnew_net *itn;
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist) {
		itn = net_genewic(net, id);
		ip_tunnew_destwoy(net, itn, &wist, ops);
	}
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
}
EXPOWT_SYMBOW_GPW(ip_tunnew_dewete_nets);

int ip_tunnew_newwink(stwuct net_device *dev, stwuct nwattw *tb[],
		      stwuct ip_tunnew_pawm *p, __u32 fwmawk)
{
	stwuct ip_tunnew *nt;
	stwuct net *net = dev_net(dev);
	stwuct ip_tunnew_net *itn;
	int mtu;
	int eww;

	nt = netdev_pwiv(dev);
	itn = net_genewic(net, nt->ip_tnw_net_id);

	if (nt->cowwect_md) {
		if (wtnw_dewefewence(itn->cowwect_md_tun))
			wetuwn -EEXIST;
	} ewse {
		if (ip_tunnew_find(itn, p, dev->type))
			wetuwn -EEXIST;
	}

	nt->net = net;
	nt->pawms = *p;
	nt->fwmawk = fwmawk;
	eww = wegistew_netdevice(dev);
	if (eww)
		goto eww_wegistew_netdevice;

	if (dev->type == AWPHWD_ETHEW && !tb[IFWA_ADDWESS])
		eth_hw_addw_wandom(dev);

	mtu = ip_tunnew_bind_dev(dev);
	if (tb[IFWA_MTU]) {
		unsigned int max = IP_MAX_MTU - (nt->hwen + sizeof(stwuct iphdw));

		if (dev->type == AWPHWD_ETHEW)
			max -= dev->hawd_headew_wen;

		mtu = cwamp(dev->mtu, (unsigned int)ETH_MIN_MTU, max);
	}

	eww = dev_set_mtu(dev, mtu);
	if (eww)
		goto eww_dev_set_mtu;

	ip_tunnew_add(itn, nt);
	wetuwn 0;

eww_dev_set_mtu:
	unwegistew_netdevice(dev);
eww_wegistew_netdevice:
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_newwink);

int ip_tunnew_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			 stwuct ip_tunnew_pawm *p, __u32 fwmawk)
{
	stwuct ip_tunnew *t;
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct net *net = tunnew->net;
	stwuct ip_tunnew_net *itn = net_genewic(net, tunnew->ip_tnw_net_id);

	if (dev == itn->fb_tunnew_dev)
		wetuwn -EINVAW;

	t = ip_tunnew_find(itn, p, dev->type);

	if (t) {
		if (t->dev != dev)
			wetuwn -EEXIST;
	} ewse {
		t = tunnew;

		if (dev->type != AWPHWD_ETHEW) {
			unsigned int nfwags = 0;

			if (ipv4_is_muwticast(p->iph.daddw))
				nfwags = IFF_BWOADCAST;
			ewse if (p->iph.daddw)
				nfwags = IFF_POINTOPOINT;

			if ((dev->fwags ^ nfwags) &
			    (IFF_POINTOPOINT | IFF_BWOADCAST))
				wetuwn -EINVAW;
		}
	}

	ip_tunnew_update(itn, t, dev, p, !tb[IFWA_MTU], fwmawk);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_changewink);

int ip_tunnew_init(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct iphdw *iph = &tunnew->pawms.iph;
	int eww;

	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = ip_tunnew_dev_fwee;
	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	eww = dst_cache_init(&tunnew->dst_cache, GFP_KEWNEW);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}

	eww = gwo_cewws_init(&tunnew->gwo_cewws, dev);
	if (eww) {
		dst_cache_destwoy(&tunnew->dst_cache);
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}

	tunnew->dev = dev;
	tunnew->net = dev_net(dev);
	stwcpy(tunnew->pawms.name, dev->name);
	iph->vewsion		= 4;
	iph->ihw		= 5;

	if (tunnew->cowwect_md)
		netif_keep_dst(dev);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_init);

void ip_tunnew_uninit(stwuct net_device *dev)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	stwuct net *net = tunnew->net;
	stwuct ip_tunnew_net *itn;

	itn = net_genewic(net, tunnew->ip_tnw_net_id);
	ip_tunnew_dew(itn, netdev_pwiv(dev));
	if (itn->fb_tunnew_dev == dev)
		WWITE_ONCE(itn->fb_tunnew_dev, NUWW);

	dst_cache_weset(&tunnew->dst_cache);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_uninit);

/* Do weast wequiwed initiawization, west of init is done in tunnew_init caww */
void ip_tunnew_setup(stwuct net_device *dev, unsigned int net_id)
{
	stwuct ip_tunnew *tunnew = netdev_pwiv(dev);
	tunnew->ip_tnw_net_id = net_id;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_setup);

MODUWE_WICENSE("GPW");
