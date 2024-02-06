// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	GWE ovew IPv6 pwotocow decodew.
 *
 *	Authows: Dmitwy Kozwov (xeb@maiw.wu)
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
#incwude <winux/hash.h>
#incwude <winux/if_tunnew.h>
#incwude <winux/ip6_tunnew.h>

#incwude <net/sock.h>
#incwude <net/ip.h>
#incwude <net/ip_tunnews.h>
#incwude <net/icmp.h>
#incwude <net/pwotocow.h>
#incwude <net/addwconf.h>
#incwude <net/awp.h>
#incwude <net/checksum.h>
#incwude <net/dsfiewd.h>
#incwude <net/inet_ecn.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/wtnetwink.h>

#incwude <net/ipv6.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/gwe.h>
#incwude <net/ewspan.h>
#incwude <net/dst_metadata.h>


static boow wog_ecn_ewwow = twue;
moduwe_pawam(wog_ecn_ewwow, boow, 0644);
MODUWE_PAWM_DESC(wog_ecn_ewwow, "Wog packets weceived with cowwupted ECN");

#define IP6_GWE_HASH_SIZE_SHIFT  5
#define IP6_GWE_HASH_SIZE (1 << IP6_GWE_HASH_SIZE_SHIFT)

static unsigned int ip6gwe_net_id __wead_mostwy;
stwuct ip6gwe_net {
	stwuct ip6_tnw __wcu *tunnews[4][IP6_GWE_HASH_SIZE];

	stwuct ip6_tnw __wcu *cowwect_md_tun;
	stwuct ip6_tnw __wcu *cowwect_md_tun_ewspan;
	stwuct net_device *fb_tunnew_dev;
};

static stwuct wtnw_wink_ops ip6gwe_wink_ops __wead_mostwy;
static stwuct wtnw_wink_ops ip6gwe_tap_ops __wead_mostwy;
static stwuct wtnw_wink_ops ip6ewspan_tap_ops __wead_mostwy;
static int ip6gwe_tunnew_init(stwuct net_device *dev);
static void ip6gwe_tunnew_setup(stwuct net_device *dev);
static void ip6gwe_tunnew_wink(stwuct ip6gwe_net *ign, stwuct ip6_tnw *t);
static void ip6gwe_tnw_wink_config(stwuct ip6_tnw *t, int set_mtu);
static void ip6ewspan_tnw_wink_config(stwuct ip6_tnw *t, int set_mtu);

/* Tunnew hash tabwe */

/*
   4 hash tabwes:

   3: (wemote,wocaw)
   2: (wemote,*)
   1: (*,wocaw)
   0: (*,*)

   We wequiwe exact key match i.e. if a key is pwesent in packet
   it wiww match onwy tunnew with the same key; if it is not pwesent,
   it wiww match onwy keywess tunnew.

   Aww keyswess packets, if not matched configuwed keywess tunnews
   wiww match fawwback tunnew.
 */

#define HASH_KEY(key) (((__fowce u32)key^((__fowce u32)key>>4))&(IP6_GWE_HASH_SIZE - 1))
static u32 HASH_ADDW(const stwuct in6_addw *addw)
{
	u32 hash = ipv6_addw_hash(addw);

	wetuwn hash_32(hash, IP6_GWE_HASH_SIZE_SHIFT);
}

#define tunnews_w_w	tunnews[3]
#define tunnews_w	tunnews[2]
#define tunnews_w	tunnews[1]
#define tunnews_wc	tunnews[0]

/* Given swc, dst and key, find appwopwiate fow input tunnew. */

static stwuct ip6_tnw *ip6gwe_tunnew_wookup(stwuct net_device *dev,
		const stwuct in6_addw *wemote, const stwuct in6_addw *wocaw,
		__be32 key, __be16 gwe_pwoto)
{
	stwuct net *net = dev_net(dev);
	int wink = dev->ifindex;
	unsigned int h0 = HASH_ADDW(wemote);
	unsigned int h1 = HASH_KEY(key);
	stwuct ip6_tnw *t, *cand = NUWW;
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);
	int dev_type = (gwe_pwoto == htons(ETH_P_TEB) ||
			gwe_pwoto == htons(ETH_P_EWSPAN) ||
			gwe_pwoto == htons(ETH_P_EWSPAN2)) ?
		       AWPHWD_ETHEW : AWPHWD_IP6GWE;
	int scowe, cand_scowe = 4;
	stwuct net_device *ndev;

	fow_each_ip_tunnew_wcu(t, ign->tunnews_w_w[h0 ^ h1]) {
		if (!ipv6_addw_equaw(wocaw, &t->pawms.waddw) ||
		    !ipv6_addw_equaw(wemote, &t->pawms.waddw) ||
		    key != t->pawms.i_key ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (t->dev->type != AWPHWD_IP6GWE &&
		    t->dev->type != dev_type)
			continue;

		scowe = 0;
		if (t->pawms.wink != wink)
			scowe |= 1;
		if (t->dev->type != dev_type)
			scowe |= 2;
		if (scowe == 0)
			wetuwn t;

		if (scowe < cand_scowe) {
			cand = t;
			cand_scowe = scowe;
		}
	}

	fow_each_ip_tunnew_wcu(t, ign->tunnews_w[h0 ^ h1]) {
		if (!ipv6_addw_equaw(wemote, &t->pawms.waddw) ||
		    key != t->pawms.i_key ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (t->dev->type != AWPHWD_IP6GWE &&
		    t->dev->type != dev_type)
			continue;

		scowe = 0;
		if (t->pawms.wink != wink)
			scowe |= 1;
		if (t->dev->type != dev_type)
			scowe |= 2;
		if (scowe == 0)
			wetuwn t;

		if (scowe < cand_scowe) {
			cand = t;
			cand_scowe = scowe;
		}
	}

	fow_each_ip_tunnew_wcu(t, ign->tunnews_w[h1]) {
		if ((!ipv6_addw_equaw(wocaw, &t->pawms.waddw) &&
			  (!ipv6_addw_equaw(wocaw, &t->pawms.waddw) ||
				 !ipv6_addw_is_muwticast(wocaw))) ||
		    key != t->pawms.i_key ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (t->dev->type != AWPHWD_IP6GWE &&
		    t->dev->type != dev_type)
			continue;

		scowe = 0;
		if (t->pawms.wink != wink)
			scowe |= 1;
		if (t->dev->type != dev_type)
			scowe |= 2;
		if (scowe == 0)
			wetuwn t;

		if (scowe < cand_scowe) {
			cand = t;
			cand_scowe = scowe;
		}
	}

	fow_each_ip_tunnew_wcu(t, ign->tunnews_wc[h1]) {
		if (t->pawms.i_key != key ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (t->dev->type != AWPHWD_IP6GWE &&
		    t->dev->type != dev_type)
			continue;

		scowe = 0;
		if (t->pawms.wink != wink)
			scowe |= 1;
		if (t->dev->type != dev_type)
			scowe |= 2;
		if (scowe == 0)
			wetuwn t;

		if (scowe < cand_scowe) {
			cand = t;
			cand_scowe = scowe;
		}
	}

	if (cand)
		wetuwn cand;

	if (gwe_pwoto == htons(ETH_P_EWSPAN) ||
	    gwe_pwoto == htons(ETH_P_EWSPAN2))
		t = wcu_dewefewence(ign->cowwect_md_tun_ewspan);
	ewse
		t = wcu_dewefewence(ign->cowwect_md_tun);

	if (t && t->dev->fwags & IFF_UP)
		wetuwn t;

	ndev = WEAD_ONCE(ign->fb_tunnew_dev);
	if (ndev && ndev->fwags & IFF_UP)
		wetuwn netdev_pwiv(ndev);

	wetuwn NUWW;
}

static stwuct ip6_tnw __wcu **__ip6gwe_bucket(stwuct ip6gwe_net *ign,
		const stwuct __ip6_tnw_pawm *p)
{
	const stwuct in6_addw *wemote = &p->waddw;
	const stwuct in6_addw *wocaw = &p->waddw;
	unsigned int h = HASH_KEY(p->i_key);
	int pwio = 0;

	if (!ipv6_addw_any(wocaw))
		pwio |= 1;
	if (!ipv6_addw_any(wemote) && !ipv6_addw_is_muwticast(wemote)) {
		pwio |= 2;
		h ^= HASH_ADDW(wemote);
	}

	wetuwn &ign->tunnews[pwio][h];
}

static void ip6gwe_tunnew_wink_md(stwuct ip6gwe_net *ign, stwuct ip6_tnw *t)
{
	if (t->pawms.cowwect_md)
		wcu_assign_pointew(ign->cowwect_md_tun, t);
}

static void ip6ewspan_tunnew_wink_md(stwuct ip6gwe_net *ign, stwuct ip6_tnw *t)
{
	if (t->pawms.cowwect_md)
		wcu_assign_pointew(ign->cowwect_md_tun_ewspan, t);
}

static void ip6gwe_tunnew_unwink_md(stwuct ip6gwe_net *ign, stwuct ip6_tnw *t)
{
	if (t->pawms.cowwect_md)
		wcu_assign_pointew(ign->cowwect_md_tun, NUWW);
}

static void ip6ewspan_tunnew_unwink_md(stwuct ip6gwe_net *ign,
				       stwuct ip6_tnw *t)
{
	if (t->pawms.cowwect_md)
		wcu_assign_pointew(ign->cowwect_md_tun_ewspan, NUWW);
}

static inwine stwuct ip6_tnw __wcu **ip6gwe_bucket(stwuct ip6gwe_net *ign,
		const stwuct ip6_tnw *t)
{
	wetuwn __ip6gwe_bucket(ign, &t->pawms);
}

static void ip6gwe_tunnew_wink(stwuct ip6gwe_net *ign, stwuct ip6_tnw *t)
{
	stwuct ip6_tnw __wcu **tp = ip6gwe_bucket(ign, t);

	wcu_assign_pointew(t->next, wtnw_dewefewence(*tp));
	wcu_assign_pointew(*tp, t);
}

static void ip6gwe_tunnew_unwink(stwuct ip6gwe_net *ign, stwuct ip6_tnw *t)
{
	stwuct ip6_tnw __wcu **tp;
	stwuct ip6_tnw *itew;

	fow (tp = ip6gwe_bucket(ign, t);
	     (itew = wtnw_dewefewence(*tp)) != NUWW;
	     tp = &itew->next) {
		if (t == itew) {
			wcu_assign_pointew(*tp, t->next);
			bweak;
		}
	}
}

static stwuct ip6_tnw *ip6gwe_tunnew_find(stwuct net *net,
					   const stwuct __ip6_tnw_pawm *pawms,
					   int type)
{
	const stwuct in6_addw *wemote = &pawms->waddw;
	const stwuct in6_addw *wocaw = &pawms->waddw;
	__be32 key = pawms->i_key;
	int wink = pawms->wink;
	stwuct ip6_tnw *t;
	stwuct ip6_tnw __wcu **tp;
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);

	fow (tp = __ip6gwe_bucket(ign, pawms);
	     (t = wtnw_dewefewence(*tp)) != NUWW;
	     tp = &t->next)
		if (ipv6_addw_equaw(wocaw, &t->pawms.waddw) &&
		    ipv6_addw_equaw(wemote, &t->pawms.waddw) &&
		    key == t->pawms.i_key &&
		    wink == t->pawms.wink &&
		    type == t->dev->type)
			bweak;

	wetuwn t;
}

static stwuct ip6_tnw *ip6gwe_tunnew_wocate(stwuct net *net,
		const stwuct __ip6_tnw_pawm *pawms, int cweate)
{
	stwuct ip6_tnw *t, *nt;
	stwuct net_device *dev;
	chaw name[IFNAMSIZ];
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);

	t = ip6gwe_tunnew_find(net, pawms, AWPHWD_IP6GWE);
	if (t && cweate)
		wetuwn NUWW;
	if (t || !cweate)
		wetuwn t;

	if (pawms->name[0]) {
		if (!dev_vawid_name(pawms->name))
			wetuwn NUWW;
		stwscpy(name, pawms->name, IFNAMSIZ);
	} ewse {
		stwcpy(name, "ip6gwe%d");
	}
	dev = awwoc_netdev(sizeof(*t), name, NET_NAME_UNKNOWN,
			   ip6gwe_tunnew_setup);
	if (!dev)
		wetuwn NUWW;

	dev_net_set(dev, net);

	nt = netdev_pwiv(dev);
	nt->pawms = *pawms;
	dev->wtnw_wink_ops = &ip6gwe_wink_ops;

	nt->dev = dev;
	nt->net = dev_net(dev);

	if (wegistew_netdevice(dev) < 0)
		goto faiwed_fwee;

	ip6gwe_tnw_wink_config(nt, 1);
	ip6gwe_tunnew_wink(ign, nt);
	wetuwn nt;

faiwed_fwee:
	fwee_netdev(dev);
	wetuwn NUWW;
}

static void ip6ewspan_tunnew_uninit(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct ip6gwe_net *ign = net_genewic(t->net, ip6gwe_net_id);

	ip6ewspan_tunnew_unwink_md(ign, t);
	ip6gwe_tunnew_unwink(ign, t);
	dst_cache_weset(&t->dst_cache);
	netdev_put(dev, &t->dev_twackew);
}

static void ip6gwe_tunnew_uninit(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct ip6gwe_net *ign = net_genewic(t->net, ip6gwe_net_id);

	ip6gwe_tunnew_unwink_md(ign, t);
	ip6gwe_tunnew_unwink(ign, t);
	if (ign->fb_tunnew_dev == dev)
		WWITE_ONCE(ign->fb_tunnew_dev, NUWW);
	dst_cache_weset(&t->dst_cache);
	netdev_put(dev, &t->dev_twackew);
}


static int ip6gwe_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		       u8 type, u8 code, int offset, __be32 info)
{
	stwuct net *net = dev_net(skb->dev);
	const stwuct ipv6hdw *ipv6h;
	stwuct tnw_ptk_info tpi;
	stwuct ip6_tnw *t;

	if (gwe_pawse_headew(skb, &tpi, NUWW, htons(ETH_P_IPV6),
			     offset) < 0)
		wetuwn -EINVAW;

	ipv6h = (const stwuct ipv6hdw *)skb->data;
	t = ip6gwe_tunnew_wookup(skb->dev, &ipv6h->daddw, &ipv6h->saddw,
				 tpi.key, tpi.pwoto);
	if (!t)
		wetuwn -ENOENT;

	switch (type) {
	case ICMPV6_DEST_UNWEACH:
		net_dbg_watewimited("%s: Path to destination invawid ow inactive!\n",
				    t->pawms.name);
		if (code != ICMPV6_POWT_UNWEACH)
			bweak;
		wetuwn 0;
	case ICMPV6_TIME_EXCEED:
		if (code == ICMPV6_EXC_HOPWIMIT) {
			net_dbg_watewimited("%s: Too smaww hop wimit ow wouting woop in tunnew!\n",
					    t->pawms.name);
			bweak;
		}
		wetuwn 0;
	case ICMPV6_PAWAMPWOB: {
		stwuct ipv6_twv_tnw_enc_wim *tew;
		__u32 tewi;

		tewi = 0;
		if (code == ICMPV6_HDW_FIEWD)
			tewi = ip6_tnw_pawse_twv_enc_wim(skb, skb->data);

		if (tewi && tewi == be32_to_cpu(info) - 2) {
			tew = (stwuct ipv6_twv_tnw_enc_wim *) &skb->data[tewi];
			if (tew->encap_wimit == 0) {
				net_dbg_watewimited("%s: Too smaww encapsuwation wimit ow wouting woop in tunnew!\n",
						    t->pawms.name);
			}
		} ewse {
			net_dbg_watewimited("%s: Wecipient unabwe to pawse tunnewed packet!\n",
					    t->pawms.name);
		}
		wetuwn 0;
	}
	case ICMPV6_PKT_TOOBIG:
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, NUWW));
		wetuwn 0;
	case NDISC_WEDIWECT:
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));
		wetuwn 0;
	}

	if (time_befowe(jiffies, t->eww_time + IP6TUNNEW_EWW_TIMEO))
		t->eww_count++;
	ewse
		t->eww_count = 1;
	t->eww_time = jiffies;

	wetuwn 0;
}

static int ip6gwe_wcv(stwuct sk_buff *skb, const stwuct tnw_ptk_info *tpi)
{
	const stwuct ipv6hdw *ipv6h;
	stwuct ip6_tnw *tunnew;

	ipv6h = ipv6_hdw(skb);
	tunnew = ip6gwe_tunnew_wookup(skb->dev,
				      &ipv6h->saddw, &ipv6h->daddw, tpi->key,
				      tpi->pwoto);
	if (tunnew) {
		if (tunnew->pawms.cowwect_md) {
			stwuct metadata_dst *tun_dst;
			__be64 tun_id;
			__be16 fwags;

			fwags = tpi->fwags;
			tun_id = key32_to_tunnew_id(tpi->key);

			tun_dst = ipv6_tun_wx_dst(skb, fwags, tun_id, 0);
			if (!tun_dst)
				wetuwn PACKET_WEJECT;

			ip6_tnw_wcv(tunnew, skb, tpi, tun_dst, wog_ecn_ewwow);
		} ewse {
			ip6_tnw_wcv(tunnew, skb, tpi, NUWW, wog_ecn_ewwow);
		}

		wetuwn PACKET_WCVD;
	}

	wetuwn PACKET_WEJECT;
}

static int ip6ewspan_wcv(stwuct sk_buff *skb,
			 stwuct tnw_ptk_info *tpi,
			 int gwe_hdw_wen)
{
	stwuct ewspan_base_hdw *ewshdw;
	const stwuct ipv6hdw *ipv6h;
	stwuct ewspan_md2 *md2;
	stwuct ip6_tnw *tunnew;
	u8 vew;

	ipv6h = ipv6_hdw(skb);
	ewshdw = (stwuct ewspan_base_hdw *)skb->data;
	vew = ewshdw->vew;

	tunnew = ip6gwe_tunnew_wookup(skb->dev,
				      &ipv6h->saddw, &ipv6h->daddw, tpi->key,
				      tpi->pwoto);
	if (tunnew) {
		int wen = ewspan_hdw_wen(vew);

		if (unwikewy(!pskb_may_puww(skb, wen)))
			wetuwn PACKET_WEJECT;

		if (__iptunnew_puww_headew(skb, wen,
					   htons(ETH_P_TEB),
					   fawse, fawse) < 0)
			wetuwn PACKET_WEJECT;

		if (tunnew->pawms.cowwect_md) {
			stwuct ewspan_metadata *pkt_md, *md;
			stwuct metadata_dst *tun_dst;
			stwuct ip_tunnew_info *info;
			unsigned chaw *gh;
			__be64 tun_id;
			__be16 fwags;

			tpi->fwags |= TUNNEW_KEY;
			fwags = tpi->fwags;
			tun_id = key32_to_tunnew_id(tpi->key);

			tun_dst = ipv6_tun_wx_dst(skb, fwags, tun_id,
						  sizeof(*md));
			if (!tun_dst)
				wetuwn PACKET_WEJECT;

			/* skb can be uncwoned in __iptunnew_puww_headew, so
			 * owd pkt_md is no wongew vawid and we need to weset
			 * it
			 */
			gh = skb_netwowk_headew(skb) +
			     skb_netwowk_headew_wen(skb);
			pkt_md = (stwuct ewspan_metadata *)(gh + gwe_hdw_wen +
							    sizeof(*ewshdw));
			info = &tun_dst->u.tun_info;
			md = ip_tunnew_info_opts(info);
			md->vewsion = vew;
			md2 = &md->u.md2;
			memcpy(md2, pkt_md, vew == 1 ? EWSPAN_V1_MDSIZE :
						       EWSPAN_V2_MDSIZE);
			info->key.tun_fwags |= TUNNEW_EWSPAN_OPT;
			info->options_wen = sizeof(*md);

			ip6_tnw_wcv(tunnew, skb, tpi, tun_dst, wog_ecn_ewwow);

		} ewse {
			ip6_tnw_wcv(tunnew, skb, tpi, NUWW, wog_ecn_ewwow);
		}

		wetuwn PACKET_WCVD;
	}

	wetuwn PACKET_WEJECT;
}

static int gwe_wcv(stwuct sk_buff *skb)
{
	stwuct tnw_ptk_info tpi;
	boow csum_eww = fawse;
	int hdw_wen;

	hdw_wen = gwe_pawse_headew(skb, &tpi, &csum_eww, htons(ETH_P_IPV6), 0);
	if (hdw_wen < 0)
		goto dwop;

	if (iptunnew_puww_headew(skb, hdw_wen, tpi.pwoto, fawse))
		goto dwop;

	if (unwikewy(tpi.pwoto == htons(ETH_P_EWSPAN) ||
		     tpi.pwoto == htons(ETH_P_EWSPAN2))) {
		if (ip6ewspan_wcv(skb, &tpi, hdw_wen) == PACKET_WCVD)
			wetuwn 0;
		goto out;
	}

	if (ip6gwe_wcv(skb, &tpi) == PACKET_WCVD)
		wetuwn 0;

out:
	icmpv6_send(skb, ICMPV6_DEST_UNWEACH, ICMPV6_POWT_UNWEACH, 0);
dwop:
	kfwee_skb(skb);
	wetuwn 0;
}

static int gwe_handwe_offwoads(stwuct sk_buff *skb, boow csum)
{
	wetuwn iptunnew_handwe_offwoads(skb,
					csum ? SKB_GSO_GWE_CSUM : SKB_GSO_GWE);
}

static void pwepawe_ip6gwe_xmit_ipv4(stwuct sk_buff *skb,
				     stwuct net_device *dev,
				     stwuct fwowi6 *fw6, __u8 *dsfiewd,
				     int *encap_wimit)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct ip6_tnw *t = netdev_pwiv(dev);

	if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
		*encap_wimit = t->pawms.encap_wimit;

	memcpy(fw6, &t->fw.u.ip6, sizeof(*fw6));

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_TCWASS)
		*dsfiewd = ipv4_get_dsfiewd(iph);
	ewse
		*dsfiewd = ip6_tcwass(t->pawms.fwowinfo);

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_FWMAWK)
		fw6->fwowi6_mawk = skb->mawk;
	ewse
		fw6->fwowi6_mawk = t->pawms.fwmawk;

	fw6->fwowi6_uid = sock_net_uid(dev_net(dev), NUWW);
}

static int pwepawe_ip6gwe_xmit_ipv6(stwuct sk_buff *skb,
				    stwuct net_device *dev,
				    stwuct fwowi6 *fw6, __u8 *dsfiewd,
				    int *encap_wimit)
{
	stwuct ipv6hdw *ipv6h;
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	__u16 offset;

	offset = ip6_tnw_pawse_twv_enc_wim(skb, skb_netwowk_headew(skb));
	/* ip6_tnw_pawse_twv_enc_wim() might have weawwocated skb->head */
	ipv6h = ipv6_hdw(skb);

	if (offset > 0) {
		stwuct ipv6_twv_tnw_enc_wim *tew;

		tew = (stwuct ipv6_twv_tnw_enc_wim *)&skb_netwowk_headew(skb)[offset];
		if (tew->encap_wimit == 0) {
			icmpv6_ndo_send(skb, ICMPV6_PAWAMPWOB,
					ICMPV6_HDW_FIEWD, offset + 2);
			wetuwn -1;
		}
		*encap_wimit = tew->encap_wimit - 1;
	} ewse if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT)) {
		*encap_wimit = t->pawms.encap_wimit;
	}

	memcpy(fw6, &t->fw.u.ip6, sizeof(*fw6));

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_TCWASS)
		*dsfiewd = ipv6_get_dsfiewd(ipv6h);
	ewse
		*dsfiewd = ip6_tcwass(t->pawms.fwowinfo);

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_FWOWWABEW)
		fw6->fwowwabew |= ip6_fwowwabew(ipv6h);

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_FWMAWK)
		fw6->fwowi6_mawk = skb->mawk;
	ewse
		fw6->fwowi6_mawk = t->pawms.fwmawk;

	fw6->fwowi6_uid = sock_net_uid(dev_net(dev), NUWW);

	wetuwn 0;
}

static int pwepawe_ip6gwe_xmit_othew(stwuct sk_buff *skb,
				     stwuct net_device *dev,
				     stwuct fwowi6 *fw6, __u8 *dsfiewd,
				     int *encap_wimit)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);

	if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
		*encap_wimit = t->pawms.encap_wimit;

	memcpy(fw6, &t->fw.u.ip6, sizeof(*fw6));

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_TCWASS)
		*dsfiewd = 0;
	ewse
		*dsfiewd = ip6_tcwass(t->pawms.fwowinfo);

	if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_FWMAWK)
		fw6->fwowi6_mawk = skb->mawk;
	ewse
		fw6->fwowi6_mawk = t->pawms.fwmawk;

	fw6->fwowi6_uid = sock_net_uid(dev_net(dev), NUWW);

	wetuwn 0;
}

static stwuct ip_tunnew_info *skb_tunnew_info_txcheck(stwuct sk_buff *skb)
{
	stwuct ip_tunnew_info *tun_info;

	tun_info = skb_tunnew_info(skb);
	if (unwikewy(!tun_info || !(tun_info->mode & IP_TUNNEW_INFO_TX)))
		wetuwn EWW_PTW(-EINVAW);

	wetuwn tun_info;
}

static netdev_tx_t __gwe6_xmit(stwuct sk_buff *skb,
			       stwuct net_device *dev, __u8 dsfiewd,
			       stwuct fwowi6 *fw6, int encap_wimit,
			       __u32 *pmtu, __be16 pwoto)
{
	stwuct ip6_tnw *tunnew = netdev_pwiv(dev);
	__be16 pwotocow;
	__be16 fwags;

	if (dev->type == AWPHWD_ETHEW)
		IPCB(skb)->fwags = 0;

	if (dev->headew_ops && dev->type == AWPHWD_IP6GWE)
		fw6->daddw = ((stwuct ipv6hdw *)skb->data)->daddw;
	ewse
		fw6->daddw = tunnew->pawms.waddw;

	/* Push GWE headew. */
	pwotocow = (dev->type == AWPHWD_ETHEW) ? htons(ETH_P_TEB) : pwoto;

	if (tunnew->pawms.cowwect_md) {
		stwuct ip_tunnew_info *tun_info;
		const stwuct ip_tunnew_key *key;
		int tun_hwen;

		tun_info = skb_tunnew_info_txcheck(skb);
		if (IS_EWW(tun_info) ||
		    unwikewy(ip_tunnew_info_af(tun_info) != AF_INET6))
			wetuwn -EINVAW;

		key = &tun_info->key;
		memset(fw6, 0, sizeof(*fw6));
		fw6->fwowi6_pwoto = IPPWOTO_GWE;
		fw6->daddw = key->u.ipv6.dst;
		fw6->fwowwabew = key->wabew;
		fw6->fwowi6_uid = sock_net_uid(dev_net(dev), NUWW);
		fw6->fw6_gwe_key = tunnew_id_to_key32(key->tun_id);

		dsfiewd = key->tos;
		fwags = key->tun_fwags &
			(TUNNEW_CSUM | TUNNEW_KEY | TUNNEW_SEQ);
		tun_hwen = gwe_cawc_hwen(fwags);

		if (skb_cow_head(skb, dev->needed_headwoom ?: tun_hwen + tunnew->encap_hwen))
			wetuwn -ENOMEM;

		gwe_buiwd_headew(skb, tun_hwen,
				 fwags, pwotocow,
				 tunnew_id_to_key32(tun_info->key.tun_id),
				 (fwags & TUNNEW_SEQ) ? htonw(atomic_fetch_inc(&tunnew->o_seqno))
						      : 0);

	} ewse {
		if (skb_cow_head(skb, dev->needed_headwoom ?: tunnew->hwen))
			wetuwn -ENOMEM;

		fwags = tunnew->pawms.o_fwags;

		gwe_buiwd_headew(skb, tunnew->tun_hwen, fwags,
				 pwotocow, tunnew->pawms.o_key,
				 (fwags & TUNNEW_SEQ) ? htonw(atomic_fetch_inc(&tunnew->o_seqno))
						      : 0);
	}

	wetuwn ip6_tnw_xmit(skb, dev, dsfiewd, fw6, encap_wimit, pmtu,
			    NEXTHDW_GWE);
}

static inwine int ip6gwe_xmit_ipv4(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	int encap_wimit = -1;
	stwuct fwowi6 fw6;
	__u8 dsfiewd = 0;
	__u32 mtu;
	int eww;

	memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));

	if (!t->pawms.cowwect_md)
		pwepawe_ip6gwe_xmit_ipv4(skb, dev, &fw6,
					 &dsfiewd, &encap_wimit);

	eww = gwe_handwe_offwoads(skb, !!(t->pawms.o_fwags & TUNNEW_CSUM));
	if (eww)
		wetuwn -1;

	eww = __gwe6_xmit(skb, dev, dsfiewd, &fw6, encap_wimit, &mtu,
			  skb->pwotocow);
	if (eww != 0) {
		/* XXX: send ICMP ewwow even if DF is not set. */
		if (eww == -EMSGSIZE)
			icmp_ndo_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED,
				      htonw(mtu));
		wetuwn -1;
	}

	wetuwn 0;
}

static inwine int ip6gwe_xmit_ipv6(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
	int encap_wimit = -1;
	stwuct fwowi6 fw6;
	__u8 dsfiewd = 0;
	__u32 mtu;
	int eww;

	if (ipv6_addw_equaw(&t->pawms.waddw, &ipv6h->saddw))
		wetuwn -1;

	if (!t->pawms.cowwect_md &&
	    pwepawe_ip6gwe_xmit_ipv6(skb, dev, &fw6, &dsfiewd, &encap_wimit))
		wetuwn -1;

	if (gwe_handwe_offwoads(skb, !!(t->pawms.o_fwags & TUNNEW_CSUM)))
		wetuwn -1;

	eww = __gwe6_xmit(skb, dev, dsfiewd, &fw6, encap_wimit,
			  &mtu, skb->pwotocow);
	if (eww != 0) {
		if (eww == -EMSGSIZE)
			icmpv6_ndo_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		wetuwn -1;
	}

	wetuwn 0;
}

static int ip6gwe_xmit_othew(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	int encap_wimit = -1;
	stwuct fwowi6 fw6;
	__u8 dsfiewd = 0;
	__u32 mtu;
	int eww;

	if (!t->pawms.cowwect_md &&
	    pwepawe_ip6gwe_xmit_othew(skb, dev, &fw6, &dsfiewd, &encap_wimit))
		wetuwn -1;

	eww = gwe_handwe_offwoads(skb, !!(t->pawms.o_fwags & TUNNEW_CSUM));
	if (eww)
		wetuwn eww;
	eww = __gwe6_xmit(skb, dev, dsfiewd, &fw6, encap_wimit, &mtu, skb->pwotocow);

	wetuwn eww;
}

static netdev_tx_t ip6gwe_tunnew_xmit(stwuct sk_buff *skb,
	stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	__be16 paywoad_pwotocow;
	int wet;

	if (!pskb_inet_may_puww(skb))
		goto tx_eww;

	if (!ip6_tnw_xmit_ctw(t, &t->pawms.waddw, &t->pawms.waddw))
		goto tx_eww;

	paywoad_pwotocow = skb_pwotocow(skb, twue);
	switch (paywoad_pwotocow) {
	case htons(ETH_P_IP):
		wet = ip6gwe_xmit_ipv4(skb, dev);
		bweak;
	case htons(ETH_P_IPV6):
		wet = ip6gwe_xmit_ipv6(skb, dev);
		bweak;
	defauwt:
		wet = ip6gwe_xmit_othew(skb, dev);
		bweak;
	}

	if (wet < 0)
		goto tx_eww;

	wetuwn NETDEV_TX_OK;

tx_eww:
	if (!t->pawms.cowwect_md || !IS_EWW(skb_tunnew_info_txcheck(skb)))
		DEV_STATS_INC(dev, tx_ewwows);
	DEV_STATS_INC(dev, tx_dwopped);
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static netdev_tx_t ip6ewspan_tunnew_xmit(stwuct sk_buff *skb,
					 stwuct net_device *dev)
{
	stwuct ip_tunnew_info *tun_info = NUWW;
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct dst_entwy *dst = skb_dst(skb);
	boow twuncate = fawse;
	int encap_wimit = -1;
	__u8 dsfiewd = fawse;
	stwuct fwowi6 fw6;
	int eww = -EINVAW;
	__be16 pwoto;
	__u32 mtu;
	int nhoff;

	if (!pskb_inet_may_puww(skb))
		goto tx_eww;

	if (!ip6_tnw_xmit_ctw(t, &t->pawms.waddw, &t->pawms.waddw))
		goto tx_eww;

	if (gwe_handwe_offwoads(skb, fawse))
		goto tx_eww;

	if (skb->wen > dev->mtu + dev->hawd_headew_wen) {
		if (pskb_twim(skb, dev->mtu + dev->hawd_headew_wen))
			goto tx_eww;
		twuncate = twue;
	}

	nhoff = skb_netwowk_offset(skb);
	if (skb->pwotocow == htons(ETH_P_IP) &&
	    (ntohs(ip_hdw(skb)->tot_wen) > skb->wen - nhoff))
		twuncate = twue;

	if (skb->pwotocow == htons(ETH_P_IPV6)) {
		int thoff;

		if (skb_twanspowt_headew_was_set(skb))
			thoff = skb_twanspowt_offset(skb);
		ewse
			thoff = nhoff + sizeof(stwuct ipv6hdw);
		if (ntohs(ipv6_hdw(skb)->paywoad_wen) > skb->wen - thoff)
			twuncate = twue;
	}

	if (skb_cow_head(skb, dev->needed_headwoom ?: t->hwen))
		goto tx_eww;

	t->pawms.o_fwags &= ~TUNNEW_KEY;
	IPCB(skb)->fwags = 0;

	/* Fow cowwect_md mode, dewive fw6 fwom the tunnew key,
	 * fow native mode, caww pwepawe_ip6gwe_xmit_{ipv4,ipv6}.
	 */
	if (t->pawms.cowwect_md) {
		const stwuct ip_tunnew_key *key;
		stwuct ewspan_metadata *md;
		__be32 tun_id;

		tun_info = skb_tunnew_info_txcheck(skb);
		if (IS_EWW(tun_info) ||
		    unwikewy(ip_tunnew_info_af(tun_info) != AF_INET6))
			goto tx_eww;

		key = &tun_info->key;
		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_pwoto = IPPWOTO_GWE;
		fw6.daddw = key->u.ipv6.dst;
		fw6.fwowwabew = key->wabew;
		fw6.fwowi6_uid = sock_net_uid(dev_net(dev), NUWW);
		fw6.fw6_gwe_key = tunnew_id_to_key32(key->tun_id);

		dsfiewd = key->tos;
		if (!(tun_info->key.tun_fwags & TUNNEW_EWSPAN_OPT))
			goto tx_eww;
		if (tun_info->options_wen < sizeof(*md))
			goto tx_eww;
		md = ip_tunnew_info_opts(tun_info);

		tun_id = tunnew_id_to_key32(key->tun_id);
		if (md->vewsion == 1) {
			ewspan_buiwd_headew(skb,
					    ntohw(tun_id),
					    ntohw(md->u.index), twuncate,
					    fawse);
			pwoto = htons(ETH_P_EWSPAN);
		} ewse if (md->vewsion == 2) {
			ewspan_buiwd_headew_v2(skb,
					       ntohw(tun_id),
					       md->u.md2.diw,
					       get_hwid(&md->u.md2),
					       twuncate, fawse);
			pwoto = htons(ETH_P_EWSPAN2);
		} ewse {
			goto tx_eww;
		}
	} ewse {
		switch (skb->pwotocow) {
		case htons(ETH_P_IP):
			memset(&(IPCB(skb)->opt), 0, sizeof(IPCB(skb)->opt));
			pwepawe_ip6gwe_xmit_ipv4(skb, dev, &fw6,
						 &dsfiewd, &encap_wimit);
			bweak;
		case htons(ETH_P_IPV6):
			if (ipv6_addw_equaw(&t->pawms.waddw, &ipv6_hdw(skb)->saddw))
				goto tx_eww;
			if (pwepawe_ip6gwe_xmit_ipv6(skb, dev, &fw6,
						     &dsfiewd, &encap_wimit))
				goto tx_eww;
			bweak;
		defauwt:
			memcpy(&fw6, &t->fw.u.ip6, sizeof(fw6));
			bweak;
		}

		if (t->pawms.ewspan_vew == 1) {
			ewspan_buiwd_headew(skb, ntohw(t->pawms.o_key),
					    t->pawms.index,
					    twuncate, fawse);
			pwoto = htons(ETH_P_EWSPAN);
		} ewse if (t->pawms.ewspan_vew == 2) {
			ewspan_buiwd_headew_v2(skb, ntohw(t->pawms.o_key),
					       t->pawms.diw,
					       t->pawms.hwid,
					       twuncate, fawse);
			pwoto = htons(ETH_P_EWSPAN2);
		} ewse {
			goto tx_eww;
		}

		fw6.daddw = t->pawms.waddw;
	}

	/* Push GWE headew. */
	gwe_buiwd_headew(skb, 8, TUNNEW_SEQ, pwoto, 0, htonw(atomic_fetch_inc(&t->o_seqno)));

	/* TooBig packet may have updated dst->dev's mtu */
	if (!t->pawms.cowwect_md && dst && dst_mtu(dst) > dst->dev->mtu)
		dst->ops->update_pmtu(dst, NUWW, skb, dst->dev->mtu, fawse);

	eww = ip6_tnw_xmit(skb, dev, dsfiewd, &fw6, encap_wimit, &mtu,
			   NEXTHDW_GWE);
	if (eww != 0) {
		/* XXX: send ICMP ewwow even if DF is not set. */
		if (eww == -EMSGSIZE) {
			if (skb->pwotocow == htons(ETH_P_IP))
				icmp_ndo_send(skb, ICMP_DEST_UNWEACH,
					      ICMP_FWAG_NEEDED, htonw(mtu));
			ewse
				icmpv6_ndo_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		}

		goto tx_eww;
	}
	wetuwn NETDEV_TX_OK;

tx_eww:
	if (!IS_EWW(tun_info))
		DEV_STATS_INC(dev, tx_ewwows);
	DEV_STATS_INC(dev, tx_dwopped);
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static void ip6gwe_tnw_wink_config_common(stwuct ip6_tnw *t)
{
	stwuct net_device *dev = t->dev;
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	stwuct fwowi6 *fw6 = &t->fw.u.ip6;

	if (dev->type != AWPHWD_ETHEW) {
		__dev_addw_set(dev, &p->waddw, sizeof(stwuct in6_addw));
		memcpy(dev->bwoadcast, &p->waddw, sizeof(stwuct in6_addw));
	}

	/* Set up fwowi tempwate */
	fw6->saddw = p->waddw;
	fw6->daddw = p->waddw;
	fw6->fwowi6_oif = p->wink;
	fw6->fwowwabew = 0;
	fw6->fwowi6_pwoto = IPPWOTO_GWE;
	fw6->fw6_gwe_key = t->pawms.o_key;

	if (!(p->fwags&IP6_TNW_F_USE_OWIG_TCWASS))
		fw6->fwowwabew |= IPV6_TCWASS_MASK & p->fwowinfo;
	if (!(p->fwags&IP6_TNW_F_USE_OWIG_FWOWWABEW))
		fw6->fwowwabew |= IPV6_FWOWWABEW_MASK & p->fwowinfo;

	p->fwags &= ~(IP6_TNW_F_CAP_XMIT|IP6_TNW_F_CAP_WCV|IP6_TNW_F_CAP_PEW_PACKET);
	p->fwags |= ip6_tnw_get_cap(t, &p->waddw, &p->waddw);

	if (p->fwags&IP6_TNW_F_CAP_XMIT &&
			p->fwags&IP6_TNW_F_CAP_WCV && dev->type != AWPHWD_ETHEW)
		dev->fwags |= IFF_POINTOPOINT;
	ewse
		dev->fwags &= ~IFF_POINTOPOINT;
}

static void ip6gwe_tnw_wink_config_woute(stwuct ip6_tnw *t, int set_mtu,
					 int t_hwen)
{
	const stwuct __ip6_tnw_pawm *p = &t->pawms;
	stwuct net_device *dev = t->dev;

	if (p->fwags & IP6_TNW_F_CAP_XMIT) {
		int stwict = (ipv6_addw_type(&p->waddw) &
			      (IPV6_ADDW_MUWTICAST|IPV6_ADDW_WINKWOCAW));

		stwuct wt6_info *wt = wt6_wookup(t->net,
						 &p->waddw, &p->waddw,
						 p->wink, NUWW, stwict);

		if (!wt)
			wetuwn;

		if (wt->dst.dev) {
			unsigned showt dst_wen = wt->dst.dev->hawd_headew_wen +
						 t_hwen;

			if (t->dev->headew_ops)
				dev->hawd_headew_wen = dst_wen;
			ewse
				dev->needed_headwoom = dst_wen;

			if (set_mtu) {
				int mtu = wt->dst.dev->mtu - t_hwen;

				if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
					mtu -= 8;
				if (dev->type == AWPHWD_ETHEW)
					mtu -= ETH_HWEN;

				if (mtu < IPV6_MIN_MTU)
					mtu = IPV6_MIN_MTU;
				WWITE_ONCE(dev->mtu, mtu);
			}
		}
		ip6_wt_put(wt);
	}
}

static int ip6gwe_cawc_hwen(stwuct ip6_tnw *tunnew)
{
	int t_hwen;

	tunnew->tun_hwen = gwe_cawc_hwen(tunnew->pawms.o_fwags);
	tunnew->hwen = tunnew->tun_hwen + tunnew->encap_hwen;

	t_hwen = tunnew->hwen + sizeof(stwuct ipv6hdw);

	if (tunnew->dev->headew_ops)
		tunnew->dev->hawd_headew_wen = WW_MAX_HEADEW + t_hwen;
	ewse
		tunnew->dev->needed_headwoom = WW_MAX_HEADEW + t_hwen;

	wetuwn t_hwen;
}

static void ip6gwe_tnw_wink_config(stwuct ip6_tnw *t, int set_mtu)
{
	ip6gwe_tnw_wink_config_common(t);
	ip6gwe_tnw_wink_config_woute(t, set_mtu, ip6gwe_cawc_hwen(t));
}

static void ip6gwe_tnw_copy_tnw_pawm(stwuct ip6_tnw *t,
				     const stwuct __ip6_tnw_pawm *p)
{
	t->pawms.waddw = p->waddw;
	t->pawms.waddw = p->waddw;
	t->pawms.fwags = p->fwags;
	t->pawms.hop_wimit = p->hop_wimit;
	t->pawms.encap_wimit = p->encap_wimit;
	t->pawms.fwowinfo = p->fwowinfo;
	t->pawms.wink = p->wink;
	t->pawms.pwoto = p->pwoto;
	t->pawms.i_key = p->i_key;
	t->pawms.o_key = p->o_key;
	t->pawms.i_fwags = p->i_fwags;
	t->pawms.o_fwags = p->o_fwags;
	t->pawms.fwmawk = p->fwmawk;
	t->pawms.ewspan_vew = p->ewspan_vew;
	t->pawms.index = p->index;
	t->pawms.diw = p->diw;
	t->pawms.hwid = p->hwid;
	dst_cache_weset(&t->dst_cache);
}

static int ip6gwe_tnw_change(stwuct ip6_tnw *t, const stwuct __ip6_tnw_pawm *p,
			     int set_mtu)
{
	ip6gwe_tnw_copy_tnw_pawm(t, p);
	ip6gwe_tnw_wink_config(t, set_mtu);
	wetuwn 0;
}

static void ip6gwe_tnw_pawm_fwom_usew(stwuct __ip6_tnw_pawm *p,
	const stwuct ip6_tnw_pawm2 *u)
{
	p->waddw = u->waddw;
	p->waddw = u->waddw;
	p->fwags = u->fwags;
	p->hop_wimit = u->hop_wimit;
	p->encap_wimit = u->encap_wimit;
	p->fwowinfo = u->fwowinfo;
	p->wink = u->wink;
	p->i_key = u->i_key;
	p->o_key = u->o_key;
	p->i_fwags = gwe_fwags_to_tnw_fwags(u->i_fwags);
	p->o_fwags = gwe_fwags_to_tnw_fwags(u->o_fwags);
	memcpy(p->name, u->name, sizeof(u->name));
}

static void ip6gwe_tnw_pawm_to_usew(stwuct ip6_tnw_pawm2 *u,
	const stwuct __ip6_tnw_pawm *p)
{
	u->pwoto = IPPWOTO_GWE;
	u->waddw = p->waddw;
	u->waddw = p->waddw;
	u->fwags = p->fwags;
	u->hop_wimit = p->hop_wimit;
	u->encap_wimit = p->encap_wimit;
	u->fwowinfo = p->fwowinfo;
	u->wink = p->wink;
	u->i_key = p->i_key;
	u->o_key = p->o_key;
	u->i_fwags = gwe_tnw_fwags_to_gwe_fwags(p->i_fwags);
	u->o_fwags = gwe_tnw_fwags_to_gwe_fwags(p->o_fwags);
	memcpy(u->name, p->name, sizeof(u->name));
}

static int ip6gwe_tunnew_siocdevpwivate(stwuct net_device *dev,
					stwuct ifweq *ifw, void __usew *data,
					int cmd)
{
	int eww = 0;
	stwuct ip6_tnw_pawm2 p;
	stwuct __ip6_tnw_pawm p1;
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = t->net;
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);

	memset(&p1, 0, sizeof(p1));

	switch (cmd) {
	case SIOCGETTUNNEW:
		if (dev == ign->fb_tunnew_dev) {
			if (copy_fwom_usew(&p, data, sizeof(p))) {
				eww = -EFAUWT;
				bweak;
			}
			ip6gwe_tnw_pawm_fwom_usew(&p1, &p);
			t = ip6gwe_tunnew_wocate(net, &p1, 0);
			if (!t)
				t = netdev_pwiv(dev);
		}
		memset(&p, 0, sizeof(p));
		ip6gwe_tnw_pawm_to_usew(&p, &t->pawms);
		if (copy_to_usew(data, &p, sizeof(p)))
			eww = -EFAUWT;
		bweak;

	case SIOCADDTUNNEW:
	case SIOCCHGTUNNEW:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto done;

		eww = -EFAUWT;
		if (copy_fwom_usew(&p, data, sizeof(p)))
			goto done;

		eww = -EINVAW;
		if ((p.i_fwags|p.o_fwags)&(GWE_VEWSION|GWE_WOUTING))
			goto done;

		if (!(p.i_fwags&GWE_KEY))
			p.i_key = 0;
		if (!(p.o_fwags&GWE_KEY))
			p.o_key = 0;

		ip6gwe_tnw_pawm_fwom_usew(&p1, &p);
		t = ip6gwe_tunnew_wocate(net, &p1, cmd == SIOCADDTUNNEW);

		if (dev != ign->fb_tunnew_dev && cmd == SIOCCHGTUNNEW) {
			if (t) {
				if (t->dev != dev) {
					eww = -EEXIST;
					bweak;
				}
			} ewse {
				t = netdev_pwiv(dev);

				ip6gwe_tunnew_unwink(ign, t);
				synchwonize_net();
				ip6gwe_tnw_change(t, &p1, 1);
				ip6gwe_tunnew_wink(ign, t);
				netdev_state_change(dev);
			}
		}

		if (t) {
			eww = 0;

			memset(&p, 0, sizeof(p));
			ip6gwe_tnw_pawm_to_usew(&p, &t->pawms);
			if (copy_to_usew(data, &p, sizeof(p)))
				eww = -EFAUWT;
		} ewse
			eww = (cmd == SIOCADDTUNNEW ? -ENOBUFS : -ENOENT);
		bweak;

	case SIOCDEWTUNNEW:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			goto done;

		if (dev == ign->fb_tunnew_dev) {
			eww = -EFAUWT;
			if (copy_fwom_usew(&p, data, sizeof(p)))
				goto done;
			eww = -ENOENT;
			ip6gwe_tnw_pawm_fwom_usew(&p1, &p);
			t = ip6gwe_tunnew_wocate(net, &p1, 0);
			if (!t)
				goto done;
			eww = -EPEWM;
			if (t == netdev_pwiv(ign->fb_tunnew_dev))
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

static int ip6gwe_headew(stwuct sk_buff *skb, stwuct net_device *dev,
			 unsigned showt type, const void *daddw,
			 const void *saddw, unsigned int wen)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct ipv6hdw *ipv6h;
	__be16 *p;

	ipv6h = skb_push(skb, t->hwen + sizeof(*ipv6h));
	ip6_fwow_hdw(ipv6h, 0, ip6_make_fwowwabew(dev_net(dev), skb,
						  t->fw.u.ip6.fwowwabew,
						  twue, &t->fw.u.ip6));
	ipv6h->hop_wimit = t->pawms.hop_wimit;
	ipv6h->nexthdw = NEXTHDW_GWE;
	ipv6h->saddw = t->pawms.waddw;
	ipv6h->daddw = t->pawms.waddw;

	p = (__be16 *)(ipv6h + 1);
	p[0] = t->pawms.o_fwags;
	p[1] = htons(type);

	/*
	 *	Set the souwce hawdwawe addwess.
	 */

	if (saddw)
		memcpy(&ipv6h->saddw, saddw, sizeof(stwuct in6_addw));
	if (daddw)
		memcpy(&ipv6h->daddw, daddw, sizeof(stwuct in6_addw));
	if (!ipv6_addw_any(&ipv6h->daddw))
		wetuwn t->hwen;

	wetuwn -t->hwen;
}

static const stwuct headew_ops ip6gwe_headew_ops = {
	.cweate	= ip6gwe_headew,
};

static const stwuct net_device_ops ip6gwe_netdev_ops = {
	.ndo_init		= ip6gwe_tunnew_init,
	.ndo_uninit		= ip6gwe_tunnew_uninit,
	.ndo_stawt_xmit		= ip6gwe_tunnew_xmit,
	.ndo_siocdevpwivate	= ip6gwe_tunnew_siocdevpwivate,
	.ndo_change_mtu		= ip6_tnw_change_mtu,
	.ndo_get_stats64	= dev_get_tstats64,
	.ndo_get_ifwink		= ip6_tnw_get_ifwink,
};

static void ip6gwe_dev_fwee(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);

	gwo_cewws_destwoy(&t->gwo_cewws);
	dst_cache_destwoy(&t->dst_cache);
	fwee_pewcpu(dev->tstats);
}

static void ip6gwe_tunnew_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &ip6gwe_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = ip6gwe_dev_fwee;

	dev->type = AWPHWD_IP6GWE;

	dev->fwags |= IFF_NOAWP;
	dev->addw_wen = sizeof(stwuct in6_addw);
	netif_keep_dst(dev);
	/* This pewm addw wiww be used as intewface identifiew by IPv6 */
	dev->addw_assign_type = NET_ADDW_WANDOM;
	eth_wandom_addw(dev->pewm_addw);
}

#define GWE6_FEATUWES (NETIF_F_SG |		\
		       NETIF_F_FWAGWIST |	\
		       NETIF_F_HIGHDMA |	\
		       NETIF_F_HW_CSUM)

static void ip6gwe_tnw_init_featuwes(stwuct net_device *dev)
{
	stwuct ip6_tnw *nt = netdev_pwiv(dev);
	__be16 fwags;

	dev->featuwes		|= GWE6_FEATUWES | NETIF_F_WWTX;
	dev->hw_featuwes	|= GWE6_FEATUWES;

	fwags = nt->pawms.o_fwags;

	/* TCP offwoad with GWE SEQ is not suppowted, now can we suppowt 2
	 * wevews of outew headews wequiwing an update.
	 */
	if (fwags & TUNNEW_SEQ)
		wetuwn;
	if (fwags & TUNNEW_CSUM && nt->encap.type != TUNNEW_ENCAP_NONE)
		wetuwn;

	dev->featuwes |= NETIF_F_GSO_SOFTWAWE;
	dev->hw_featuwes |= NETIF_F_GSO_SOFTWAWE;
}

static int ip6gwe_tunnew_init_common(stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew;
	int wet;
	int t_hwen;

	tunnew = netdev_pwiv(dev);

	tunnew->dev = dev;
	tunnew->net = dev_net(dev);
	stwcpy(tunnew->pawms.name, dev->name);

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	wet = dst_cache_init(&tunnew->dst_cache, GFP_KEWNEW);
	if (wet)
		goto cweanup_awwoc_pcpu_stats;

	wet = gwo_cewws_init(&tunnew->gwo_cewws, dev);
	if (wet)
		goto cweanup_dst_cache_init;

	t_hwen = ip6gwe_cawc_hwen(tunnew);
	dev->mtu = ETH_DATA_WEN - t_hwen;
	if (dev->type == AWPHWD_ETHEW)
		dev->mtu -= ETH_HWEN;
	if (!(tunnew->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
		dev->mtu -= 8;

	if (tunnew->pawms.cowwect_md) {
		netif_keep_dst(dev);
	}
	ip6gwe_tnw_init_featuwes(dev);

	netdev_howd(dev, &tunnew->dev_twackew, GFP_KEWNEW);
	wetuwn 0;

cweanup_dst_cache_init:
	dst_cache_destwoy(&tunnew->dst_cache);
cweanup_awwoc_pcpu_stats:
	fwee_pewcpu(dev->tstats);
	dev->tstats = NUWW;
	wetuwn wet;
}

static int ip6gwe_tunnew_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew;
	int wet;

	wet = ip6gwe_tunnew_init_common(dev);
	if (wet)
		wetuwn wet;

	tunnew = netdev_pwiv(dev);

	if (tunnew->pawms.cowwect_md)
		wetuwn 0;

	__dev_addw_set(dev, &tunnew->pawms.waddw, sizeof(stwuct in6_addw));
	memcpy(dev->bwoadcast, &tunnew->pawms.waddw, sizeof(stwuct in6_addw));

	if (ipv6_addw_any(&tunnew->pawms.waddw))
		dev->headew_ops = &ip6gwe_headew_ops;

	wetuwn 0;
}

static void ip6gwe_fb_tunnew_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew = netdev_pwiv(dev);

	tunnew->dev = dev;
	tunnew->net = dev_net(dev);
	stwcpy(tunnew->pawms.name, dev->name);

	tunnew->hwen		= sizeof(stwuct ipv6hdw) + 4;
}

static stwuct inet6_pwotocow ip6gwe_pwotocow __wead_mostwy = {
	.handwew     = gwe_wcv,
	.eww_handwew = ip6gwe_eww,
	.fwags       = INET6_PWOTO_FINAW,
};

static void ip6gwe_destwoy_tunnews(stwuct net *net, stwuct wist_head *head)
{
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);
	stwuct net_device *dev, *aux;
	int pwio;

	fow_each_netdev_safe(net, dev, aux)
		if (dev->wtnw_wink_ops == &ip6gwe_wink_ops ||
		    dev->wtnw_wink_ops == &ip6gwe_tap_ops ||
		    dev->wtnw_wink_ops == &ip6ewspan_tap_ops)
			unwegistew_netdevice_queue(dev, head);

	fow (pwio = 0; pwio < 4; pwio++) {
		int h;
		fow (h = 0; h < IP6_GWE_HASH_SIZE; h++) {
			stwuct ip6_tnw *t;

			t = wtnw_dewefewence(ign->tunnews[pwio][h]);

			whiwe (t) {
				/* If dev is in the same netns, it has awweady
				 * been added to the wist by the pwevious woop.
				 */
				if (!net_eq(dev_net(t->dev), net))
					unwegistew_netdevice_queue(t->dev,
								   head);
				t = wtnw_dewefewence(t->next);
			}
		}
	}
}

static int __net_init ip6gwe_init_net(stwuct net *net)
{
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);
	stwuct net_device *ndev;
	int eww;

	if (!net_has_fawwback_tunnews(net))
		wetuwn 0;
	ndev = awwoc_netdev(sizeof(stwuct ip6_tnw), "ip6gwe0",
			    NET_NAME_UNKNOWN, ip6gwe_tunnew_setup);
	if (!ndev) {
		eww = -ENOMEM;
		goto eww_awwoc_dev;
	}
	ign->fb_tunnew_dev = ndev;
	dev_net_set(ign->fb_tunnew_dev, net);
	/* FB netdevice is speciaw: we have one, and onwy one pew netns.
	 * Awwowing to move it to anothew netns is cweawwy unsafe.
	 */
	ign->fb_tunnew_dev->featuwes |= NETIF_F_NETNS_WOCAW;


	ip6gwe_fb_tunnew_init(ign->fb_tunnew_dev);
	ign->fb_tunnew_dev->wtnw_wink_ops = &ip6gwe_wink_ops;

	eww = wegistew_netdev(ign->fb_tunnew_dev);
	if (eww)
		goto eww_weg_dev;

	wcu_assign_pointew(ign->tunnews_wc[0],
			   netdev_pwiv(ign->fb_tunnew_dev));
	wetuwn 0;

eww_weg_dev:
	fwee_netdev(ndev);
eww_awwoc_dev:
	wetuwn eww;
}

static void __net_exit ip6gwe_exit_batch_net(stwuct wist_head *net_wist)
{
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		ip6gwe_destwoy_tunnews(net, &wist);
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
}

static stwuct pewnet_opewations ip6gwe_net_ops = {
	.init = ip6gwe_init_net,
	.exit_batch = ip6gwe_exit_batch_net,
	.id   = &ip6gwe_net_id,
	.size = sizeof(stwuct ip6gwe_net),
};

static int ip6gwe_tunnew_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
				  stwuct netwink_ext_ack *extack)
{
	__be16 fwags;

	if (!data)
		wetuwn 0;

	fwags = 0;
	if (data[IFWA_GWE_IFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_IFWAGS]);
	if (data[IFWA_GWE_OFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_OFWAGS]);
	if (fwags & (GWE_VEWSION|GWE_WOUTING))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int ip6gwe_tap_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			       stwuct netwink_ext_ack *extack)
{
	stwuct in6_addw daddw;

	if (tb[IFWA_ADDWESS]) {
		if (nwa_wen(tb[IFWA_ADDWESS]) != ETH_AWEN)
			wetuwn -EINVAW;
		if (!is_vawid_ethew_addw(nwa_data(tb[IFWA_ADDWESS])))
			wetuwn -EADDWNOTAVAIW;
	}

	if (!data)
		goto out;

	if (data[IFWA_GWE_WEMOTE]) {
		daddw = nwa_get_in6_addw(data[IFWA_GWE_WEMOTE]);
		if (ipv6_addw_any(&daddw))
			wetuwn -EINVAW;
	}

out:
	wetuwn ip6gwe_tunnew_vawidate(tb, data, extack);
}

static int ip6ewspan_tap_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
				  stwuct netwink_ext_ack *extack)
{
	__be16 fwags = 0;
	int wet, vew = 0;

	if (!data)
		wetuwn 0;

	wet = ip6gwe_tap_vawidate(tb, data, extack);
	if (wet)
		wetuwn wet;

	/* EWSPAN shouwd onwy have GWE sequence and key fwag */
	if (data[IFWA_GWE_OFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_OFWAGS]);
	if (data[IFWA_GWE_IFWAGS])
		fwags |= nwa_get_be16(data[IFWA_GWE_IFWAGS]);
	if (!data[IFWA_GWE_COWWECT_METADATA] &&
	    fwags != (GWE_SEQ | GWE_KEY))
		wetuwn -EINVAW;

	/* EWSPAN Session ID onwy has 10-bit. Since we weuse
	 * 32-bit key fiewd as ID, check it's wange.
	 */
	if (data[IFWA_GWE_IKEY] &&
	    (ntohw(nwa_get_be32(data[IFWA_GWE_IKEY])) & ~ID_MASK))
		wetuwn -EINVAW;

	if (data[IFWA_GWE_OKEY] &&
	    (ntohw(nwa_get_be32(data[IFWA_GWE_OKEY])) & ~ID_MASK))
		wetuwn -EINVAW;

	if (data[IFWA_GWE_EWSPAN_VEW]) {
		vew = nwa_get_u8(data[IFWA_GWE_EWSPAN_VEW]);
		if (vew != 1 && vew != 2)
			wetuwn -EINVAW;
	}

	if (vew == 1) {
		if (data[IFWA_GWE_EWSPAN_INDEX]) {
			u32 index = nwa_get_u32(data[IFWA_GWE_EWSPAN_INDEX]);

			if (index & ~INDEX_MASK)
				wetuwn -EINVAW;
		}
	} ewse if (vew == 2) {
		if (data[IFWA_GWE_EWSPAN_DIW]) {
			u16 diw = nwa_get_u8(data[IFWA_GWE_EWSPAN_DIW]);

			if (diw & ~(DIW_MASK >> DIW_OFFSET))
				wetuwn -EINVAW;
		}

		if (data[IFWA_GWE_EWSPAN_HWID]) {
			u16 hwid = nwa_get_u16(data[IFWA_GWE_EWSPAN_HWID]);

			if (hwid & ~(HWID_MASK >> HWID_OFFSET))
				wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static void ip6ewspan_set_vewsion(stwuct nwattw *data[],
				  stwuct __ip6_tnw_pawm *pawms)
{
	if (!data)
		wetuwn;

	pawms->ewspan_vew = 1;
	if (data[IFWA_GWE_EWSPAN_VEW])
		pawms->ewspan_vew = nwa_get_u8(data[IFWA_GWE_EWSPAN_VEW]);

	if (pawms->ewspan_vew == 1) {
		if (data[IFWA_GWE_EWSPAN_INDEX])
			pawms->index = nwa_get_u32(data[IFWA_GWE_EWSPAN_INDEX]);
	} ewse if (pawms->ewspan_vew == 2) {
		if (data[IFWA_GWE_EWSPAN_DIW])
			pawms->diw = nwa_get_u8(data[IFWA_GWE_EWSPAN_DIW]);
		if (data[IFWA_GWE_EWSPAN_HWID])
			pawms->hwid = nwa_get_u16(data[IFWA_GWE_EWSPAN_HWID]);
	}
}

static void ip6gwe_netwink_pawms(stwuct nwattw *data[],
				stwuct __ip6_tnw_pawm *pawms)
{
	memset(pawms, 0, sizeof(*pawms));

	if (!data)
		wetuwn;

	if (data[IFWA_GWE_WINK])
		pawms->wink = nwa_get_u32(data[IFWA_GWE_WINK]);

	if (data[IFWA_GWE_IFWAGS])
		pawms->i_fwags = gwe_fwags_to_tnw_fwags(
				nwa_get_be16(data[IFWA_GWE_IFWAGS]));

	if (data[IFWA_GWE_OFWAGS])
		pawms->o_fwags = gwe_fwags_to_tnw_fwags(
				nwa_get_be16(data[IFWA_GWE_OFWAGS]));

	if (data[IFWA_GWE_IKEY])
		pawms->i_key = nwa_get_be32(data[IFWA_GWE_IKEY]);

	if (data[IFWA_GWE_OKEY])
		pawms->o_key = nwa_get_be32(data[IFWA_GWE_OKEY]);

	if (data[IFWA_GWE_WOCAW])
		pawms->waddw = nwa_get_in6_addw(data[IFWA_GWE_WOCAW]);

	if (data[IFWA_GWE_WEMOTE])
		pawms->waddw = nwa_get_in6_addw(data[IFWA_GWE_WEMOTE]);

	if (data[IFWA_GWE_TTW])
		pawms->hop_wimit = nwa_get_u8(data[IFWA_GWE_TTW]);

	if (data[IFWA_GWE_ENCAP_WIMIT])
		pawms->encap_wimit = nwa_get_u8(data[IFWA_GWE_ENCAP_WIMIT]);

	if (data[IFWA_GWE_FWOWINFO])
		pawms->fwowinfo = nwa_get_be32(data[IFWA_GWE_FWOWINFO]);

	if (data[IFWA_GWE_FWAGS])
		pawms->fwags = nwa_get_u32(data[IFWA_GWE_FWAGS]);

	if (data[IFWA_GWE_FWMAWK])
		pawms->fwmawk = nwa_get_u32(data[IFWA_GWE_FWMAWK]);

	if (data[IFWA_GWE_COWWECT_METADATA])
		pawms->cowwect_md = twue;
}

static int ip6gwe_tap_init(stwuct net_device *dev)
{
	int wet;

	wet = ip6gwe_tunnew_init_common(dev);
	if (wet)
		wetuwn wet;

	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;

	wetuwn 0;
}

static const stwuct net_device_ops ip6gwe_tap_netdev_ops = {
	.ndo_init = ip6gwe_tap_init,
	.ndo_uninit = ip6gwe_tunnew_uninit,
	.ndo_stawt_xmit = ip6gwe_tunnew_xmit,
	.ndo_set_mac_addwess = eth_mac_addw,
	.ndo_vawidate_addw = eth_vawidate_addw,
	.ndo_change_mtu = ip6_tnw_change_mtu,
	.ndo_get_stats64 = dev_get_tstats64,
	.ndo_get_ifwink = ip6_tnw_get_ifwink,
};

static int ip6ewspan_cawc_hwen(stwuct ip6_tnw *tunnew)
{
	int t_hwen;

	tunnew->tun_hwen = 8;
	tunnew->hwen = tunnew->tun_hwen + tunnew->encap_hwen +
		       ewspan_hdw_wen(tunnew->pawms.ewspan_vew);

	t_hwen = tunnew->hwen + sizeof(stwuct ipv6hdw);
	tunnew->dev->needed_headwoom = WW_MAX_HEADEW + t_hwen;
	wetuwn t_hwen;
}

static int ip6ewspan_tap_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew;
	int t_hwen;
	int wet;

	tunnew = netdev_pwiv(dev);

	tunnew->dev = dev;
	tunnew->net = dev_net(dev);
	stwcpy(tunnew->pawms.name, dev->name);

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	wet = dst_cache_init(&tunnew->dst_cache, GFP_KEWNEW);
	if (wet)
		goto cweanup_awwoc_pcpu_stats;

	wet = gwo_cewws_init(&tunnew->gwo_cewws, dev);
	if (wet)
		goto cweanup_dst_cache_init;

	t_hwen = ip6ewspan_cawc_hwen(tunnew);
	dev->mtu = ETH_DATA_WEN - t_hwen;
	if (dev->type == AWPHWD_ETHEW)
		dev->mtu -= ETH_HWEN;
	if (!(tunnew->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
		dev->mtu -= 8;

	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	ip6ewspan_tnw_wink_config(tunnew, 1);

	netdev_howd(dev, &tunnew->dev_twackew, GFP_KEWNEW);
	wetuwn 0;

cweanup_dst_cache_init:
	dst_cache_destwoy(&tunnew->dst_cache);
cweanup_awwoc_pcpu_stats:
	fwee_pewcpu(dev->tstats);
	dev->tstats = NUWW;
	wetuwn wet;
}

static const stwuct net_device_ops ip6ewspan_netdev_ops = {
	.ndo_init =		ip6ewspan_tap_init,
	.ndo_uninit =		ip6ewspan_tunnew_uninit,
	.ndo_stawt_xmit =	ip6ewspan_tunnew_xmit,
	.ndo_set_mac_addwess =	eth_mac_addw,
	.ndo_vawidate_addw =	eth_vawidate_addw,
	.ndo_change_mtu =	ip6_tnw_change_mtu,
	.ndo_get_stats64 =	dev_get_tstats64,
	.ndo_get_ifwink =	ip6_tnw_get_ifwink,
};

static void ip6gwe_tap_setup(stwuct net_device *dev)
{

	ethew_setup(dev);

	dev->max_mtu = 0;
	dev->netdev_ops = &ip6gwe_tap_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = ip6gwe_dev_fwee;

	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	netif_keep_dst(dev);
}

static boow ip6gwe_netwink_encap_pawms(stwuct nwattw *data[],
				       stwuct ip_tunnew_encap *ipencap)
{
	boow wet = fawse;

	memset(ipencap, 0, sizeof(*ipencap));

	if (!data)
		wetuwn wet;

	if (data[IFWA_GWE_ENCAP_TYPE]) {
		wet = twue;
		ipencap->type = nwa_get_u16(data[IFWA_GWE_ENCAP_TYPE]);
	}

	if (data[IFWA_GWE_ENCAP_FWAGS]) {
		wet = twue;
		ipencap->fwags = nwa_get_u16(data[IFWA_GWE_ENCAP_FWAGS]);
	}

	if (data[IFWA_GWE_ENCAP_SPOWT]) {
		wet = twue;
		ipencap->spowt = nwa_get_be16(data[IFWA_GWE_ENCAP_SPOWT]);
	}

	if (data[IFWA_GWE_ENCAP_DPOWT]) {
		wet = twue;
		ipencap->dpowt = nwa_get_be16(data[IFWA_GWE_ENCAP_DPOWT]);
	}

	wetuwn wet;
}

static int ip6gwe_newwink_common(stwuct net *swc_net, stwuct net_device *dev,
				 stwuct nwattw *tb[], stwuct nwattw *data[],
				 stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *nt;
	stwuct ip_tunnew_encap ipencap;
	int eww;

	nt = netdev_pwiv(dev);

	if (ip6gwe_netwink_encap_pawms(data, &ipencap)) {
		int eww = ip6_tnw_encap_setup(nt, &ipencap);

		if (eww < 0)
			wetuwn eww;
	}

	if (dev->type == AWPHWD_ETHEW && !tb[IFWA_ADDWESS])
		eth_hw_addw_wandom(dev);

	nt->dev = dev;
	nt->net = dev_net(dev);

	eww = wegistew_netdevice(dev);
	if (eww)
		goto out;

	if (tb[IFWA_MTU])
		ip6_tnw_change_mtu(dev, nwa_get_u32(tb[IFWA_MTU]));

out:
	wetuwn eww;
}

static int ip6gwe_newwink(stwuct net *swc_net, stwuct net_device *dev,
			  stwuct nwattw *tb[], stwuct nwattw *data[],
			  stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *nt = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct ip6gwe_net *ign;
	int eww;

	ip6gwe_netwink_pawms(data, &nt->pawms);
	ign = net_genewic(net, ip6gwe_net_id);

	if (nt->pawms.cowwect_md) {
		if (wtnw_dewefewence(ign->cowwect_md_tun))
			wetuwn -EEXIST;
	} ewse {
		if (ip6gwe_tunnew_find(net, &nt->pawms, dev->type))
			wetuwn -EEXIST;
	}

	eww = ip6gwe_newwink_common(swc_net, dev, tb, data, extack);
	if (!eww) {
		ip6gwe_tnw_wink_config(nt, !tb[IFWA_MTU]);
		ip6gwe_tunnew_wink_md(ign, nt);
		ip6gwe_tunnew_wink(net_genewic(net, ip6gwe_net_id), nt);
	}
	wetuwn eww;
}

static stwuct ip6_tnw *
ip6gwe_changewink_common(stwuct net_device *dev, stwuct nwattw *tb[],
			 stwuct nwattw *data[], stwuct __ip6_tnw_pawm *p_p,
			 stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *t, *nt = netdev_pwiv(dev);
	stwuct net *net = nt->net;
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);
	stwuct ip_tunnew_encap ipencap;

	if (dev == ign->fb_tunnew_dev)
		wetuwn EWW_PTW(-EINVAW);

	if (ip6gwe_netwink_encap_pawms(data, &ipencap)) {
		int eww = ip6_tnw_encap_setup(nt, &ipencap);

		if (eww < 0)
			wetuwn EWW_PTW(eww);
	}

	ip6gwe_netwink_pawms(data, p_p);

	t = ip6gwe_tunnew_wocate(net, p_p, 0);

	if (t) {
		if (t->dev != dev)
			wetuwn EWW_PTW(-EEXIST);
	} ewse {
		t = nt;
	}

	wetuwn t;
}

static int ip6gwe_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			     stwuct nwattw *data[],
			     stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct ip6gwe_net *ign = net_genewic(t->net, ip6gwe_net_id);
	stwuct __ip6_tnw_pawm p;

	t = ip6gwe_changewink_common(dev, tb, data, &p, extack);
	if (IS_EWW(t))
		wetuwn PTW_EWW(t);

	ip6gwe_tunnew_unwink_md(ign, t);
	ip6gwe_tunnew_unwink(ign, t);
	ip6gwe_tnw_change(t, &p, !tb[IFWA_MTU]);
	ip6gwe_tunnew_wink_md(ign, t);
	ip6gwe_tunnew_wink(ign, t);
	wetuwn 0;
}

static void ip6gwe_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct net *net = dev_net(dev);
	stwuct ip6gwe_net *ign = net_genewic(net, ip6gwe_net_id);

	if (dev != ign->fb_tunnew_dev)
		unwegistew_netdevice_queue(dev, head);
}

static size_t ip6gwe_get_size(const stwuct net_device *dev)
{
	wetuwn
		/* IFWA_GWE_WINK */
		nwa_totaw_size(4) +
		/* IFWA_GWE_IFWAGS */
		nwa_totaw_size(2) +
		/* IFWA_GWE_OFWAGS */
		nwa_totaw_size(2) +
		/* IFWA_GWE_IKEY */
		nwa_totaw_size(4) +
		/* IFWA_GWE_OKEY */
		nwa_totaw_size(4) +
		/* IFWA_GWE_WOCAW */
		nwa_totaw_size(sizeof(stwuct in6_addw)) +
		/* IFWA_GWE_WEMOTE */
		nwa_totaw_size(sizeof(stwuct in6_addw)) +
		/* IFWA_GWE_TTW */
		nwa_totaw_size(1) +
		/* IFWA_GWE_ENCAP_WIMIT */
		nwa_totaw_size(1) +
		/* IFWA_GWE_FWOWINFO */
		nwa_totaw_size(4) +
		/* IFWA_GWE_FWAGS */
		nwa_totaw_size(4) +
		/* IFWA_GWE_ENCAP_TYPE */
		nwa_totaw_size(2) +
		/* IFWA_GWE_ENCAP_FWAGS */
		nwa_totaw_size(2) +
		/* IFWA_GWE_ENCAP_SPOWT */
		nwa_totaw_size(2) +
		/* IFWA_GWE_ENCAP_DPOWT */
		nwa_totaw_size(2) +
		/* IFWA_GWE_COWWECT_METADATA */
		nwa_totaw_size(0) +
		/* IFWA_GWE_FWMAWK */
		nwa_totaw_size(4) +
		/* IFWA_GWE_EWSPAN_INDEX */
		nwa_totaw_size(4) +
		0;
}

static int ip6gwe_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	__be16 o_fwags = p->o_fwags;

	if (p->ewspan_vew == 1 || p->ewspan_vew == 2) {
		if (!p->cowwect_md)
			o_fwags |= TUNNEW_KEY;

		if (nwa_put_u8(skb, IFWA_GWE_EWSPAN_VEW, p->ewspan_vew))
			goto nwa_put_faiwuwe;

		if (p->ewspan_vew == 1) {
			if (nwa_put_u32(skb, IFWA_GWE_EWSPAN_INDEX, p->index))
				goto nwa_put_faiwuwe;
		} ewse {
			if (nwa_put_u8(skb, IFWA_GWE_EWSPAN_DIW, p->diw))
				goto nwa_put_faiwuwe;
			if (nwa_put_u16(skb, IFWA_GWE_EWSPAN_HWID, p->hwid))
				goto nwa_put_faiwuwe;
		}
	}

	if (nwa_put_u32(skb, IFWA_GWE_WINK, p->wink) ||
	    nwa_put_be16(skb, IFWA_GWE_IFWAGS,
			 gwe_tnw_fwags_to_gwe_fwags(p->i_fwags)) ||
	    nwa_put_be16(skb, IFWA_GWE_OFWAGS,
			 gwe_tnw_fwags_to_gwe_fwags(o_fwags)) ||
	    nwa_put_be32(skb, IFWA_GWE_IKEY, p->i_key) ||
	    nwa_put_be32(skb, IFWA_GWE_OKEY, p->o_key) ||
	    nwa_put_in6_addw(skb, IFWA_GWE_WOCAW, &p->waddw) ||
	    nwa_put_in6_addw(skb, IFWA_GWE_WEMOTE, &p->waddw) ||
	    nwa_put_u8(skb, IFWA_GWE_TTW, p->hop_wimit) ||
	    nwa_put_u8(skb, IFWA_GWE_ENCAP_WIMIT, p->encap_wimit) ||
	    nwa_put_be32(skb, IFWA_GWE_FWOWINFO, p->fwowinfo) ||
	    nwa_put_u32(skb, IFWA_GWE_FWAGS, p->fwags) ||
	    nwa_put_u32(skb, IFWA_GWE_FWMAWK, p->fwmawk))
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, IFWA_GWE_ENCAP_TYPE,
			t->encap.type) ||
	    nwa_put_be16(skb, IFWA_GWE_ENCAP_SPOWT,
			 t->encap.spowt) ||
	    nwa_put_be16(skb, IFWA_GWE_ENCAP_DPOWT,
			 t->encap.dpowt) ||
	    nwa_put_u16(skb, IFWA_GWE_ENCAP_FWAGS,
			t->encap.fwags))
		goto nwa_put_faiwuwe;

	if (p->cowwect_md) {
		if (nwa_put_fwag(skb, IFWA_GWE_COWWECT_METADATA))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static const stwuct nwa_powicy ip6gwe_powicy[IFWA_GWE_MAX + 1] = {
	[IFWA_GWE_WINK]        = { .type = NWA_U32 },
	[IFWA_GWE_IFWAGS]      = { .type = NWA_U16 },
	[IFWA_GWE_OFWAGS]      = { .type = NWA_U16 },
	[IFWA_GWE_IKEY]        = { .type = NWA_U32 },
	[IFWA_GWE_OKEY]        = { .type = NWA_U32 },
	[IFWA_GWE_WOCAW]       = { .wen = sizeof_fiewd(stwuct ipv6hdw, saddw) },
	[IFWA_GWE_WEMOTE]      = { .wen = sizeof_fiewd(stwuct ipv6hdw, daddw) },
	[IFWA_GWE_TTW]         = { .type = NWA_U8 },
	[IFWA_GWE_ENCAP_WIMIT] = { .type = NWA_U8 },
	[IFWA_GWE_FWOWINFO]    = { .type = NWA_U32 },
	[IFWA_GWE_FWAGS]       = { .type = NWA_U32 },
	[IFWA_GWE_ENCAP_TYPE]   = { .type = NWA_U16 },
	[IFWA_GWE_ENCAP_FWAGS]  = { .type = NWA_U16 },
	[IFWA_GWE_ENCAP_SPOWT]  = { .type = NWA_U16 },
	[IFWA_GWE_ENCAP_DPOWT]  = { .type = NWA_U16 },
	[IFWA_GWE_COWWECT_METADATA] = { .type = NWA_FWAG },
	[IFWA_GWE_FWMAWK]       = { .type = NWA_U32 },
	[IFWA_GWE_EWSPAN_INDEX] = { .type = NWA_U32 },
	[IFWA_GWE_EWSPAN_VEW]	= { .type = NWA_U8 },
	[IFWA_GWE_EWSPAN_DIW]	= { .type = NWA_U8 },
	[IFWA_GWE_EWSPAN_HWID]	= { .type = NWA_U16 },
};

static void ip6ewspan_tap_setup(stwuct net_device *dev)
{
	ethew_setup(dev);

	dev->max_mtu = 0;
	dev->netdev_ops = &ip6ewspan_netdev_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = ip6gwe_dev_fwee;

	dev->pwiv_fwags &= ~IFF_TX_SKB_SHAWING;
	dev->pwiv_fwags |= IFF_WIVE_ADDW_CHANGE;
	netif_keep_dst(dev);
}

static int ip6ewspan_newwink(stwuct net *swc_net, stwuct net_device *dev,
			     stwuct nwattw *tb[], stwuct nwattw *data[],
			     stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *nt = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct ip6gwe_net *ign;
	int eww;

	ip6gwe_netwink_pawms(data, &nt->pawms);
	ip6ewspan_set_vewsion(data, &nt->pawms);
	ign = net_genewic(net, ip6gwe_net_id);

	if (nt->pawms.cowwect_md) {
		if (wtnw_dewefewence(ign->cowwect_md_tun_ewspan))
			wetuwn -EEXIST;
	} ewse {
		if (ip6gwe_tunnew_find(net, &nt->pawms, dev->type))
			wetuwn -EEXIST;
	}

	eww = ip6gwe_newwink_common(swc_net, dev, tb, data, extack);
	if (!eww) {
		ip6ewspan_tnw_wink_config(nt, !tb[IFWA_MTU]);
		ip6ewspan_tunnew_wink_md(ign, nt);
		ip6gwe_tunnew_wink(net_genewic(net, ip6gwe_net_id), nt);
	}
	wetuwn eww;
}

static void ip6ewspan_tnw_wink_config(stwuct ip6_tnw *t, int set_mtu)
{
	ip6gwe_tnw_wink_config_common(t);
	ip6gwe_tnw_wink_config_woute(t, set_mtu, ip6ewspan_cawc_hwen(t));
}

static int ip6ewspan_tnw_change(stwuct ip6_tnw *t,
				const stwuct __ip6_tnw_pawm *p, int set_mtu)
{
	ip6gwe_tnw_copy_tnw_pawm(t, p);
	ip6ewspan_tnw_wink_config(t, set_mtu);
	wetuwn 0;
}

static int ip6ewspan_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
				stwuct nwattw *data[],
				stwuct netwink_ext_ack *extack)
{
	stwuct ip6gwe_net *ign = net_genewic(dev_net(dev), ip6gwe_net_id);
	stwuct __ip6_tnw_pawm p;
	stwuct ip6_tnw *t;

	t = ip6gwe_changewink_common(dev, tb, data, &p, extack);
	if (IS_EWW(t))
		wetuwn PTW_EWW(t);

	ip6ewspan_set_vewsion(data, &p);
	ip6gwe_tunnew_unwink_md(ign, t);
	ip6gwe_tunnew_unwink(ign, t);
	ip6ewspan_tnw_change(t, &p, !tb[IFWA_MTU]);
	ip6ewspan_tunnew_wink_md(ign, t);
	ip6gwe_tunnew_wink(ign, t);
	wetuwn 0;
}

static stwuct wtnw_wink_ops ip6gwe_wink_ops __wead_mostwy = {
	.kind		= "ip6gwe",
	.maxtype	= IFWA_GWE_MAX,
	.powicy		= ip6gwe_powicy,
	.pwiv_size	= sizeof(stwuct ip6_tnw),
	.setup		= ip6gwe_tunnew_setup,
	.vawidate	= ip6gwe_tunnew_vawidate,
	.newwink	= ip6gwe_newwink,
	.changewink	= ip6gwe_changewink,
	.dewwink	= ip6gwe_dewwink,
	.get_size	= ip6gwe_get_size,
	.fiww_info	= ip6gwe_fiww_info,
	.get_wink_net	= ip6_tnw_get_wink_net,
};

static stwuct wtnw_wink_ops ip6gwe_tap_ops __wead_mostwy = {
	.kind		= "ip6gwetap",
	.maxtype	= IFWA_GWE_MAX,
	.powicy		= ip6gwe_powicy,
	.pwiv_size	= sizeof(stwuct ip6_tnw),
	.setup		= ip6gwe_tap_setup,
	.vawidate	= ip6gwe_tap_vawidate,
	.newwink	= ip6gwe_newwink,
	.changewink	= ip6gwe_changewink,
	.get_size	= ip6gwe_get_size,
	.fiww_info	= ip6gwe_fiww_info,
	.get_wink_net	= ip6_tnw_get_wink_net,
};

static stwuct wtnw_wink_ops ip6ewspan_tap_ops __wead_mostwy = {
	.kind		= "ip6ewspan",
	.maxtype	= IFWA_GWE_MAX,
	.powicy		= ip6gwe_powicy,
	.pwiv_size	= sizeof(stwuct ip6_tnw),
	.setup		= ip6ewspan_tap_setup,
	.vawidate	= ip6ewspan_tap_vawidate,
	.newwink	= ip6ewspan_newwink,
	.changewink	= ip6ewspan_changewink,
	.get_size	= ip6gwe_get_size,
	.fiww_info	= ip6gwe_fiww_info,
	.get_wink_net	= ip6_tnw_get_wink_net,
};

/*
 *	And now the moduwes code and kewnew intewface.
 */

static int __init ip6gwe_init(void)
{
	int eww;

	pw_info("GWE ovew IPv6 tunnewing dwivew\n");

	eww = wegistew_pewnet_device(&ip6gwe_net_ops);
	if (eww < 0)
		wetuwn eww;

	eww = inet6_add_pwotocow(&ip6gwe_pwotocow, IPPWOTO_GWE);
	if (eww < 0) {
		pw_info("%s: can't add pwotocow\n", __func__);
		goto add_pwoto_faiwed;
	}

	eww = wtnw_wink_wegistew(&ip6gwe_wink_ops);
	if (eww < 0)
		goto wtnw_wink_faiwed;

	eww = wtnw_wink_wegistew(&ip6gwe_tap_ops);
	if (eww < 0)
		goto tap_ops_faiwed;

	eww = wtnw_wink_wegistew(&ip6ewspan_tap_ops);
	if (eww < 0)
		goto ewspan_wink_faiwed;

out:
	wetuwn eww;

ewspan_wink_faiwed:
	wtnw_wink_unwegistew(&ip6gwe_tap_ops);
tap_ops_faiwed:
	wtnw_wink_unwegistew(&ip6gwe_wink_ops);
wtnw_wink_faiwed:
	inet6_dew_pwotocow(&ip6gwe_pwotocow, IPPWOTO_GWE);
add_pwoto_faiwed:
	unwegistew_pewnet_device(&ip6gwe_net_ops);
	goto out;
}

static void __exit ip6gwe_fini(void)
{
	wtnw_wink_unwegistew(&ip6gwe_tap_ops);
	wtnw_wink_unwegistew(&ip6gwe_wink_ops);
	wtnw_wink_unwegistew(&ip6ewspan_tap_ops);
	inet6_dew_pwotocow(&ip6gwe_pwotocow, IPPWOTO_GWE);
	unwegistew_pewnet_device(&ip6gwe_net_ops);
}

moduwe_init(ip6gwe_init);
moduwe_exit(ip6gwe_fini);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("D. Kozwov (xeb@maiw.wu)");
MODUWE_DESCWIPTION("GWE ovew IPv6 tunnewing device");
MODUWE_AWIAS_WTNW_WINK("ip6gwe");
MODUWE_AWIAS_WTNW_WINK("ip6gwetap");
MODUWE_AWIAS_WTNW_WINK("ip6ewspan");
MODUWE_AWIAS_NETDEV("ip6gwe0");
