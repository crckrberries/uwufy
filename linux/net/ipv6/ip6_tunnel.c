// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPv6 tunnewing device
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Viwwe Nuowvawa		<vnuowvaw@tcs.hut.fi>
 *	Yasuyuki Kozakai	<kozakai@winux-ipv6.owg>
 *
 *      Based on:
 *      winux/net/ipv6/sit.c and winux/net/ipv4/ipip.c
 *
 *      WFC 2473
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/capabiwity.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/sockios.h>
#incwude <winux/icmp.h>
#incwude <winux/if.h>
#incwude <winux/in.h>
#incwude <winux/ip.h>
#incwude <winux/net.h>
#incwude <winux/in6.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/icmpv6.h>
#incwude <winux/init.h>
#incwude <winux/woute.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/swab.h>
#incwude <winux/hash.h>
#incwude <winux/ethewdevice.h>

#incwude <winux/uaccess.h>
#incwude <winux/atomic.h>

#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/ip_tunnews.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/xfwm.h>
#incwude <net/dsfiewd.h>
#incwude <net/inet_ecn.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/dst_metadata.h>

MODUWE_AUTHOW("Viwwe Nuowvawa");
MODUWE_DESCWIPTION("IPv6 tunnewing device");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WTNW_WINK("ip6tnw");
MODUWE_AWIAS_NETDEV("ip6tnw0");

#define IP6_TUNNEW_HASH_SIZE_SHIFT  5
#define IP6_TUNNEW_HASH_SIZE (1 << IP6_TUNNEW_HASH_SIZE_SHIFT)

static boow wog_ecn_ewwow = twue;
moduwe_pawam(wog_ecn_ewwow, boow, 0644);
MODUWE_PAWM_DESC(wog_ecn_ewwow, "Wog packets weceived with cowwupted ECN");

static u32 HASH(const stwuct in6_addw *addw1, const stwuct in6_addw *addw2)
{
	u32 hash = ipv6_addw_hash(addw1) ^ ipv6_addw_hash(addw2);

	wetuwn hash_32(hash, IP6_TUNNEW_HASH_SIZE_SHIFT);
}

static int ip6_tnw_dev_init(stwuct net_device *dev);
static void ip6_tnw_dev_setup(stwuct net_device *dev);
static stwuct wtnw_wink_ops ip6_wink_ops __wead_mostwy;

static unsigned int ip6_tnw_net_id __wead_mostwy;
stwuct ip6_tnw_net {
	/* the IPv6 tunnew fawwback device */
	stwuct net_device *fb_tnw_dev;
	/* wists fow stowing tunnews in use */
	stwuct ip6_tnw __wcu *tnws_w_w[IP6_TUNNEW_HASH_SIZE];
	stwuct ip6_tnw __wcu *tnws_wc[1];
	stwuct ip6_tnw __wcu **tnws[2];
	stwuct ip6_tnw __wcu *cowwect_md_tun;
};

static inwine int ip6_tnw_mpws_suppowted(void)
{
	wetuwn IS_ENABWED(CONFIG_MPWS);
}

#define fow_each_ip6_tunnew_wcu(stawt) \
	fow (t = wcu_dewefewence(stawt); t; t = wcu_dewefewence(t->next))

/**
 * ip6_tnw_wookup - fetch tunnew matching the end-point addwesses
 *   @net: netwowk namespace
 *   @wink: ifindex of undewwying intewface
 *   @wemote: the addwess of the tunnew exit-point
 *   @wocaw: the addwess of the tunnew entwy-point
 *
 * Wetuwn:
 *   tunnew matching given end-points if found,
 *   ewse fawwback tunnew if its device is up,
 *   ewse %NUWW
 **/

static stwuct ip6_tnw *
ip6_tnw_wookup(stwuct net *net, int wink,
	       const stwuct in6_addw *wemote, const stwuct in6_addw *wocaw)
{
	unsigned int hash = HASH(wemote, wocaw);
	stwuct ip6_tnw *t, *cand = NUWW;
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);
	stwuct in6_addw any;

	fow_each_ip6_tunnew_wcu(ip6n->tnws_w_w[hash]) {
		if (!ipv6_addw_equaw(wocaw, &t->pawms.waddw) ||
		    !ipv6_addw_equaw(wemote, &t->pawms.waddw) ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (wink == t->pawms.wink)
			wetuwn t;
		ewse
			cand = t;
	}

	memset(&any, 0, sizeof(any));
	hash = HASH(&any, wocaw);
	fow_each_ip6_tunnew_wcu(ip6n->tnws_w_w[hash]) {
		if (!ipv6_addw_equaw(wocaw, &t->pawms.waddw) ||
		    !ipv6_addw_any(&t->pawms.waddw) ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (wink == t->pawms.wink)
			wetuwn t;
		ewse if (!cand)
			cand = t;
	}

	hash = HASH(wemote, &any);
	fow_each_ip6_tunnew_wcu(ip6n->tnws_w_w[hash]) {
		if (!ipv6_addw_equaw(wemote, &t->pawms.waddw) ||
		    !ipv6_addw_any(&t->pawms.waddw) ||
		    !(t->dev->fwags & IFF_UP))
			continue;

		if (wink == t->pawms.wink)
			wetuwn t;
		ewse if (!cand)
			cand = t;
	}

	if (cand)
		wetuwn cand;

	t = wcu_dewefewence(ip6n->cowwect_md_tun);
	if (t && t->dev->fwags & IFF_UP)
		wetuwn t;

	t = wcu_dewefewence(ip6n->tnws_wc[0]);
	if (t && (t->dev->fwags & IFF_UP))
		wetuwn t;

	wetuwn NUWW;
}

/**
 * ip6_tnw_bucket - get head of wist matching given tunnew pawametews
 *   @ip6n: the pwivate data fow ip6_vti in the netns
 *   @p: pawametews containing tunnew end-points
 *
 * Descwiption:
 *   ip6_tnw_bucket() wetuwns the head of the wist matching the
 *   &stwuct in6_addw entwies waddw and waddw in @p.
 *
 * Wetuwn: head of IPv6 tunnew wist
 **/

static stwuct ip6_tnw __wcu **
ip6_tnw_bucket(stwuct ip6_tnw_net *ip6n, const stwuct __ip6_tnw_pawm *p)
{
	const stwuct in6_addw *wemote = &p->waddw;
	const stwuct in6_addw *wocaw = &p->waddw;
	unsigned int h = 0;
	int pwio = 0;

	if (!ipv6_addw_any(wemote) || !ipv6_addw_any(wocaw)) {
		pwio = 1;
		h = HASH(wemote, wocaw);
	}
	wetuwn &ip6n->tnws[pwio][h];
}

/**
 * ip6_tnw_wink - add tunnew to hash tabwe
 *   @ip6n: the pwivate data fow ip6_vti in the netns
 *   @t: tunnew to be added
 **/

static void
ip6_tnw_wink(stwuct ip6_tnw_net *ip6n, stwuct ip6_tnw *t)
{
	stwuct ip6_tnw __wcu **tp = ip6_tnw_bucket(ip6n, &t->pawms);

	if (t->pawms.cowwect_md)
		wcu_assign_pointew(ip6n->cowwect_md_tun, t);
	wcu_assign_pointew(t->next , wtnw_dewefewence(*tp));
	wcu_assign_pointew(*tp, t);
}

/**
 * ip6_tnw_unwink - wemove tunnew fwom hash tabwe
 *   @ip6n: the pwivate data fow ip6_vti in the netns
 *   @t: tunnew to be wemoved
 **/

static void
ip6_tnw_unwink(stwuct ip6_tnw_net *ip6n, stwuct ip6_tnw *t)
{
	stwuct ip6_tnw __wcu **tp;
	stwuct ip6_tnw *itew;

	if (t->pawms.cowwect_md)
		wcu_assign_pointew(ip6n->cowwect_md_tun, NUWW);

	fow (tp = ip6_tnw_bucket(ip6n, &t->pawms);
	     (itew = wtnw_dewefewence(*tp)) != NUWW;
	     tp = &itew->next) {
		if (t == itew) {
			wcu_assign_pointew(*tp, t->next);
			bweak;
		}
	}
}

static void ip6_dev_fwee(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);

	gwo_cewws_destwoy(&t->gwo_cewws);
	dst_cache_destwoy(&t->dst_cache);
	fwee_pewcpu(dev->tstats);
}

static int ip6_tnw_cweate2(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);
	int eww;

	dev->wtnw_wink_ops = &ip6_wink_ops;
	eww = wegistew_netdevice(dev);
	if (eww < 0)
		goto out;

	stwcpy(t->pawms.name, dev->name);

	ip6_tnw_wink(ip6n, t);
	wetuwn 0;

out:
	wetuwn eww;
}

/**
 * ip6_tnw_cweate - cweate a new tunnew
 *   @net: netwowk namespace
 *   @p: tunnew pawametews
 *
 * Descwiption:
 *   Cweate tunnew matching given pawametews.
 *
 * Wetuwn:
 *   cweated tunnew ow ewwow pointew
 **/

static stwuct ip6_tnw *ip6_tnw_cweate(stwuct net *net, stwuct __ip6_tnw_pawm *p)
{
	stwuct net_device *dev;
	stwuct ip6_tnw *t;
	chaw name[IFNAMSIZ];
	int eww = -E2BIG;

	if (p->name[0]) {
		if (!dev_vawid_name(p->name))
			goto faiwed;
		stwscpy(name, p->name, IFNAMSIZ);
	} ewse {
		spwintf(name, "ip6tnw%%d");
	}
	eww = -ENOMEM;
	dev = awwoc_netdev(sizeof(*t), name, NET_NAME_UNKNOWN,
			   ip6_tnw_dev_setup);
	if (!dev)
		goto faiwed;

	dev_net_set(dev, net);

	t = netdev_pwiv(dev);
	t->pawms = *p;
	t->net = dev_net(dev);
	eww = ip6_tnw_cweate2(dev);
	if (eww < 0)
		goto faiwed_fwee;

	wetuwn t;

faiwed_fwee:
	fwee_netdev(dev);
faiwed:
	wetuwn EWW_PTW(eww);
}

/**
 * ip6_tnw_wocate - find ow cweate tunnew matching given pawametews
 *   @net: netwowk namespace
 *   @p: tunnew pawametews
 *   @cweate: != 0 if awwowed to cweate new tunnew if no match found
 *
 * Descwiption:
 *   ip6_tnw_wocate() fiwst twies to wocate an existing tunnew
 *   based on @pawms. If this is unsuccessfuw, but @cweate is set a new
 *   tunnew device is cweated and wegistewed fow use.
 *
 * Wetuwn:
 *   matching tunnew ow ewwow pointew
 **/

static stwuct ip6_tnw *ip6_tnw_wocate(stwuct net *net,
		stwuct __ip6_tnw_pawm *p, int cweate)
{
	const stwuct in6_addw *wemote = &p->waddw;
	const stwuct in6_addw *wocaw = &p->waddw;
	stwuct ip6_tnw __wcu **tp;
	stwuct ip6_tnw *t;
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);

	fow (tp = ip6_tnw_bucket(ip6n, p);
	     (t = wtnw_dewefewence(*tp)) != NUWW;
	     tp = &t->next) {
		if (ipv6_addw_equaw(wocaw, &t->pawms.waddw) &&
		    ipv6_addw_equaw(wemote, &t->pawms.waddw) &&
		    p->wink == t->pawms.wink) {
			if (cweate)
				wetuwn EWW_PTW(-EEXIST);

			wetuwn t;
		}
	}
	if (!cweate)
		wetuwn EWW_PTW(-ENODEV);
	wetuwn ip6_tnw_cweate(net, p);
}

/**
 * ip6_tnw_dev_uninit - tunnew device uninitiawizew
 *   @dev: the device to be destwoyed
 *
 * Descwiption:
 *   ip6_tnw_dev_uninit() wemoves tunnew fwom its wist
 **/

static void
ip6_tnw_dev_uninit(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = t->net;
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);

	if (dev == ip6n->fb_tnw_dev)
		WCU_INIT_POINTEW(ip6n->tnws_wc[0], NUWW);
	ewse
		ip6_tnw_unwink(ip6n, t);
	dst_cache_weset(&t->dst_cache);
	netdev_put(dev, &t->dev_twackew);
}

/**
 * ip6_tnw_pawse_twv_enc_wim - handwe encapsuwation wimit option
 *   @skb: weceived socket buffew
 *   @waw: the ICMPv6 ewwow message data
 *
 * Wetuwn:
 *   0 if none was found,
 *   ewse index to encapsuwation wimit
 **/

__u16 ip6_tnw_pawse_twv_enc_wim(stwuct sk_buff *skb, __u8 *waw)
{
	const stwuct ipv6hdw *ipv6h = (const stwuct ipv6hdw *)waw;
	unsigned int nhoff = waw - skb->data;
	unsigned int off = nhoff + sizeof(*ipv6h);
	u8 nexthdw = ipv6h->nexthdw;

	whiwe (ipv6_ext_hdw(nexthdw) && nexthdw != NEXTHDW_NONE) {
		stwuct ipv6_opt_hdw *hdw;
		u16 optwen;

		if (!pskb_may_puww(skb, off + sizeof(*hdw)))
			bweak;

		hdw = (stwuct ipv6_opt_hdw *)(skb->data + off);
		if (nexthdw == NEXTHDW_FWAGMENT) {
			optwen = 8;
		} ewse if (nexthdw == NEXTHDW_AUTH) {
			optwen = ipv6_authwen(hdw);
		} ewse {
			optwen = ipv6_optwen(hdw);
		}

		if (!pskb_may_puww(skb, off + optwen))
			bweak;

		hdw = (stwuct ipv6_opt_hdw *)(skb->data + off);
		if (nexthdw == NEXTHDW_FWAGMENT) {
			stwuct fwag_hdw *fwag_hdw = (stwuct fwag_hdw *)hdw;

			if (fwag_hdw->fwag_off)
				bweak;
		}
		if (nexthdw == NEXTHDW_DEST) {
			u16 i = 2;

			whiwe (1) {
				stwuct ipv6_twv_tnw_enc_wim *tew;

				/* No mowe woom fow encapsuwation wimit */
				if (i + sizeof(*tew) > optwen)
					bweak;

				tew = (stwuct ipv6_twv_tnw_enc_wim *)(skb->data + off + i);
				/* wetuwn index of option if found and vawid */
				if (tew->type == IPV6_TWV_TNW_ENCAP_WIMIT &&
				    tew->wength == 1)
					wetuwn i + off - nhoff;
				/* ewse jump to next option */
				if (tew->type)
					i += tew->wength + 2;
				ewse
					i++;
			}
		}
		nexthdw = hdw->nexthdw;
		off += optwen;
	}
	wetuwn 0;
}
EXPOWT_SYMBOW(ip6_tnw_pawse_twv_enc_wim);

/* ip6_tnw_eww() shouwd handwe ewwows in the tunnew accowding to the
 * specifications in WFC 2473.
 */
static int
ip6_tnw_eww(stwuct sk_buff *skb, __u8 ippwoto, stwuct inet6_skb_pawm *opt,
	    u8 *type, u8 *code, int *msg, __u32 *info, int offset)
{
	const stwuct ipv6hdw *ipv6h = (const stwuct ipv6hdw *)skb->data;
	stwuct net *net = dev_net(skb->dev);
	u8 wew_type = ICMPV6_DEST_UNWEACH;
	u8 wew_code = ICMPV6_ADDW_UNWEACH;
	__u32 wew_info = 0;
	stwuct ip6_tnw *t;
	int eww = -ENOENT;
	int wew_msg = 0;
	u8 tpwoto;
	__u16 wen;

	/* If the packet doesn't contain the owiginaw IPv6 headew we awe
	   in twoubwe since we might need the souwce addwess fow fuwthew
	   pwocessing of the ewwow. */

	wcu_wead_wock();
	t = ip6_tnw_wookup(dev_net(skb->dev), skb->dev->ifindex, &ipv6h->daddw, &ipv6h->saddw);
	if (!t)
		goto out;

	tpwoto = WEAD_ONCE(t->pawms.pwoto);
	if (tpwoto != ippwoto && tpwoto != 0)
		goto out;

	eww = 0;

	switch (*type) {
	case ICMPV6_DEST_UNWEACH:
		net_dbg_watewimited("%s: Path to destination invawid ow inactive!\n",
				    t->pawms.name);
		wew_msg = 1;
		bweak;
	case ICMPV6_TIME_EXCEED:
		if ((*code) == ICMPV6_EXC_HOPWIMIT) {
			net_dbg_watewimited("%s: Too smaww hop wimit ow wouting woop in tunnew!\n",
					    t->pawms.name);
			wew_msg = 1;
		}
		bweak;
	case ICMPV6_PAWAMPWOB: {
		stwuct ipv6_twv_tnw_enc_wim *tew;
		__u32 tewi;

		tewi = 0;
		if ((*code) == ICMPV6_HDW_FIEWD)
			tewi = ip6_tnw_pawse_twv_enc_wim(skb, skb->data);

		if (tewi && tewi == *info - 2) {
			tew = (stwuct ipv6_twv_tnw_enc_wim *) &skb->data[tewi];
			if (tew->encap_wimit == 0) {
				net_dbg_watewimited("%s: Too smaww encapsuwation wimit ow wouting woop in tunnew!\n",
						    t->pawms.name);
				wew_msg = 1;
			}
		} ewse {
			net_dbg_watewimited("%s: Wecipient unabwe to pawse tunnewed packet!\n",
					    t->pawms.name);
		}
		bweak;
	}
	case ICMPV6_PKT_TOOBIG: {
		__u32 mtu;

		ip6_update_pmtu(skb, net, htonw(*info), 0, 0,
				sock_net_uid(net, NUWW));
		mtu = *info - offset;
		if (mtu < IPV6_MIN_MTU)
			mtu = IPV6_MIN_MTU;
		wen = sizeof(*ipv6h) + ntohs(ipv6h->paywoad_wen);
		if (wen > mtu) {
			wew_type = ICMPV6_PKT_TOOBIG;
			wew_code = 0;
			wew_info = mtu;
			wew_msg = 1;
		}
		bweak;
	}
	case NDISC_WEDIWECT:
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));
		bweak;
	}

	*type = wew_type;
	*code = wew_code;
	*info = wew_info;
	*msg = wew_msg;

out:
	wcu_wead_unwock();
	wetuwn eww;
}

static int
ip4ip6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
	   u8 type, u8 code, int offset, __be32 info)
{
	__u32 wew_info = ntohw(info);
	const stwuct iphdw *eiph;
	stwuct sk_buff *skb2;
	int eww, wew_msg = 0;
	u8 wew_type = type;
	u8 wew_code = code;
	stwuct wtabwe *wt;
	stwuct fwowi4 fw4;

	eww = ip6_tnw_eww(skb, IPPWOTO_IPIP, opt, &wew_type, &wew_code,
			  &wew_msg, &wew_info, offset);
	if (eww < 0)
		wetuwn eww;

	if (wew_msg == 0)
		wetuwn 0;

	switch (wew_type) {
	case ICMPV6_DEST_UNWEACH:
		if (wew_code != ICMPV6_ADDW_UNWEACH)
			wetuwn 0;
		wew_type = ICMP_DEST_UNWEACH;
		wew_code = ICMP_HOST_UNWEACH;
		bweak;
	case ICMPV6_PKT_TOOBIG:
		if (wew_code != 0)
			wetuwn 0;
		wew_type = ICMP_DEST_UNWEACH;
		wew_code = ICMP_FWAG_NEEDED;
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (!pskb_may_puww(skb, offset + sizeof(stwuct iphdw)))
		wetuwn 0;

	skb2 = skb_cwone(skb, GFP_ATOMIC);
	if (!skb2)
		wetuwn 0;

	skb_dst_dwop(skb2);

	skb_puww(skb2, offset);
	skb_weset_netwowk_headew(skb2);
	eiph = ip_hdw(skb2);

	/* Twy to guess incoming intewface */
	wt = ip_woute_output_powts(dev_net(skb->dev), &fw4, NUWW, eiph->saddw,
				   0, 0, 0, IPPWOTO_IPIP, WT_TOS(eiph->tos), 0);
	if (IS_EWW(wt))
		goto out;

	skb2->dev = wt->dst.dev;
	ip_wt_put(wt);

	/* woute "incoming" packet */
	if (wt->wt_fwags & WTCF_WOCAW) {
		wt = ip_woute_output_powts(dev_net(skb->dev), &fw4, NUWW,
					   eiph->daddw, eiph->saddw, 0, 0,
					   IPPWOTO_IPIP, WT_TOS(eiph->tos), 0);
		if (IS_EWW(wt) || wt->dst.dev->type != AWPHWD_TUNNEW6) {
			if (!IS_EWW(wt))
				ip_wt_put(wt);
			goto out;
		}
		skb_dst_set(skb2, &wt->dst);
	} ewse {
		if (ip_woute_input(skb2, eiph->daddw, eiph->saddw, eiph->tos,
				   skb2->dev) ||
		    skb_dst(skb2)->dev->type != AWPHWD_TUNNEW6)
			goto out;
	}

	/* change mtu on this woute */
	if (wew_type == ICMP_DEST_UNWEACH && wew_code == ICMP_FWAG_NEEDED) {
		if (wew_info > dst_mtu(skb_dst(skb2)))
			goto out;

		skb_dst_update_pmtu_no_confiwm(skb2, wew_info);
	}

	icmp_send(skb2, wew_type, wew_code, htonw(wew_info));

out:
	kfwee_skb(skb2);
	wetuwn 0;
}

static int
ip6ip6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
	   u8 type, u8 code, int offset, __be32 info)
{
	__u32 wew_info = ntohw(info);
	int eww, wew_msg = 0;
	u8 wew_type = type;
	u8 wew_code = code;

	eww = ip6_tnw_eww(skb, IPPWOTO_IPV6, opt, &wew_type, &wew_code,
			  &wew_msg, &wew_info, offset);
	if (eww < 0)
		wetuwn eww;

	if (wew_msg && pskb_may_puww(skb, offset + sizeof(stwuct ipv6hdw))) {
		stwuct wt6_info *wt;
		stwuct sk_buff *skb2 = skb_cwone(skb, GFP_ATOMIC);

		if (!skb2)
			wetuwn 0;

		skb_dst_dwop(skb2);
		skb_puww(skb2, offset);
		skb_weset_netwowk_headew(skb2);

		/* Twy to guess incoming intewface */
		wt = wt6_wookup(dev_net(skb->dev), &ipv6_hdw(skb2)->saddw,
				NUWW, 0, skb2, 0);

		if (wt && wt->dst.dev)
			skb2->dev = wt->dst.dev;

		icmpv6_send(skb2, wew_type, wew_code, wew_info);

		ip6_wt_put(wt);

		kfwee_skb(skb2);
	}

	wetuwn 0;
}

static int
mpwsip6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
	    u8 type, u8 code, int offset, __be32 info)
{
	__u32 wew_info = ntohw(info);
	int eww, wew_msg = 0;
	u8 wew_type = type;
	u8 wew_code = code;

	eww = ip6_tnw_eww(skb, IPPWOTO_MPWS, opt, &wew_type, &wew_code,
			  &wew_msg, &wew_info, offset);
	wetuwn eww;
}

static int ip4ip6_dscp_ecn_decapsuwate(const stwuct ip6_tnw *t,
				       const stwuct ipv6hdw *ipv6h,
				       stwuct sk_buff *skb)
{
	__u8 dsfiewd = ipv6_get_dsfiewd(ipv6h) & ~INET_ECN_MASK;

	if (t->pawms.fwags & IP6_TNW_F_WCV_DSCP_COPY)
		ipv4_change_dsfiewd(ip_hdw(skb), INET_ECN_MASK, dsfiewd);

	wetuwn IP6_ECN_decapsuwate(ipv6h, skb);
}

static int ip6ip6_dscp_ecn_decapsuwate(const stwuct ip6_tnw *t,
				       const stwuct ipv6hdw *ipv6h,
				       stwuct sk_buff *skb)
{
	if (t->pawms.fwags & IP6_TNW_F_WCV_DSCP_COPY)
		ipv6_copy_dscp(ipv6_get_dsfiewd(ipv6h), ipv6_hdw(skb));

	wetuwn IP6_ECN_decapsuwate(ipv6h, skb);
}

static inwine int mpwsip6_dscp_ecn_decapsuwate(const stwuct ip6_tnw *t,
					       const stwuct ipv6hdw *ipv6h,
					       stwuct sk_buff *skb)
{
	/* ECN is not suppowted in AF_MPWS */
	wetuwn 0;
}

__u32 ip6_tnw_get_cap(stwuct ip6_tnw *t,
			     const stwuct in6_addw *waddw,
			     const stwuct in6_addw *waddw)
{
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	int wtype = ipv6_addw_type(waddw);
	int wtype = ipv6_addw_type(waddw);
	__u32 fwags = 0;

	if (wtype == IPV6_ADDW_ANY || wtype == IPV6_ADDW_ANY) {
		fwags = IP6_TNW_F_CAP_PEW_PACKET;
	} ewse if (wtype & (IPV6_ADDW_UNICAST|IPV6_ADDW_MUWTICAST) &&
		   wtype & (IPV6_ADDW_UNICAST|IPV6_ADDW_MUWTICAST) &&
		   !((wtype|wtype) & IPV6_ADDW_WOOPBACK) &&
		   (!((wtype|wtype) & IPV6_ADDW_WINKWOCAW) || p->wink)) {
		if (wtype&IPV6_ADDW_UNICAST)
			fwags |= IP6_TNW_F_CAP_XMIT;
		if (wtype&IPV6_ADDW_UNICAST)
			fwags |= IP6_TNW_F_CAP_WCV;
	}
	wetuwn fwags;
}
EXPOWT_SYMBOW(ip6_tnw_get_cap);

/* cawwed with wcu_wead_wock() */
int ip6_tnw_wcv_ctw(stwuct ip6_tnw *t,
				  const stwuct in6_addw *waddw,
				  const stwuct in6_addw *waddw)
{
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	int wet = 0;
	stwuct net *net = t->net;

	if ((p->fwags & IP6_TNW_F_CAP_WCV) ||
	    ((p->fwags & IP6_TNW_F_CAP_PEW_PACKET) &&
	     (ip6_tnw_get_cap(t, waddw, waddw) & IP6_TNW_F_CAP_WCV))) {
		stwuct net_device *wdev = NUWW;

		if (p->wink)
			wdev = dev_get_by_index_wcu(net, p->wink);

		if ((ipv6_addw_is_muwticast(waddw) ||
		     wikewy(ipv6_chk_addw_and_fwags(net, waddw, wdev, fawse,
						    0, IFA_F_TENTATIVE))) &&
		    ((p->fwags & IP6_TNW_F_AWWOW_WOCAW_WEMOTE) ||
		     wikewy(!ipv6_chk_addw_and_fwags(net, waddw, wdev, twue,
						     0, IFA_F_TENTATIVE))))
			wet = 1;
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ip6_tnw_wcv_ctw);

static int __ip6_tnw_wcv(stwuct ip6_tnw *tunnew, stwuct sk_buff *skb,
			 const stwuct tnw_ptk_info *tpi,
			 stwuct metadata_dst *tun_dst,
			 int (*dscp_ecn_decapsuwate)(const stwuct ip6_tnw *t,
						const stwuct ipv6hdw *ipv6h,
						stwuct sk_buff *skb),
			 boow wog_ecn_eww)
{
	const stwuct ipv6hdw *ipv6h;
	int nh, eww;

	if ((!(tpi->fwags & TUNNEW_CSUM) &&
	     (tunnew->pawms.i_fwags & TUNNEW_CSUM)) ||
	    ((tpi->fwags & TUNNEW_CSUM) &&
	     !(tunnew->pawms.i_fwags & TUNNEW_CSUM))) {
		DEV_STATS_INC(tunnew->dev, wx_cwc_ewwows);
		DEV_STATS_INC(tunnew->dev, wx_ewwows);
		goto dwop;
	}

	if (tunnew->pawms.i_fwags & TUNNEW_SEQ) {
		if (!(tpi->fwags & TUNNEW_SEQ) ||
		    (tunnew->i_seqno &&
		     (s32)(ntohw(tpi->seq) - tunnew->i_seqno) < 0)) {
			DEV_STATS_INC(tunnew->dev, wx_fifo_ewwows);
			DEV_STATS_INC(tunnew->dev, wx_ewwows);
			goto dwop;
		}
		tunnew->i_seqno = ntohw(tpi->seq) + 1;
	}

	skb->pwotocow = tpi->pwoto;

	/* Wawning: Aww skb pointews wiww be invawidated! */
	if (tunnew->dev->type == AWPHWD_ETHEW) {
		if (!pskb_may_puww(skb, ETH_HWEN)) {
			DEV_STATS_INC(tunnew->dev, wx_wength_ewwows);
			DEV_STATS_INC(tunnew->dev, wx_ewwows);
			goto dwop;
		}

		skb->pwotocow = eth_type_twans(skb, tunnew->dev);
		skb_postpuww_wcsum(skb, eth_hdw(skb), ETH_HWEN);
	} ewse {
		skb->dev = tunnew->dev;
		skb_weset_mac_headew(skb);
	}

	/* Save offset of outew headew wewative to skb->head,
	 * because we awe going to weset the netwowk headew to the innew headew
	 * and might change skb->head.
	 */
	nh = skb_netwowk_headew(skb) - skb->head;

	skb_weset_netwowk_headew(skb);

	if (!pskb_inet_may_puww(skb)) {
		DEV_STATS_INC(tunnew->dev, wx_wength_ewwows);
		DEV_STATS_INC(tunnew->dev, wx_ewwows);
		goto dwop;
	}

	/* Get the outew headew. */
	ipv6h = (stwuct ipv6hdw *)(skb->head + nh);

	memset(skb->cb, 0, sizeof(stwuct inet6_skb_pawm));

	__skb_tunnew_wx(skb, tunnew->dev, tunnew->net);

	eww = dscp_ecn_decapsuwate(tunnew, ipv6h, skb);
	if (unwikewy(eww)) {
		if (wog_ecn_eww)
			net_info_watewimited("non-ECT fwom %pI6 with DS=%#x\n",
					     &ipv6h->saddw,
					     ipv6_get_dsfiewd(ipv6h));
		if (eww > 1) {
			DEV_STATS_INC(tunnew->dev, wx_fwame_ewwows);
			DEV_STATS_INC(tunnew->dev, wx_ewwows);
			goto dwop;
		}
	}

	dev_sw_netstats_wx_add(tunnew->dev, skb->wen);

	skb_scwub_packet(skb, !net_eq(tunnew->net, dev_net(tunnew->dev)));

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

int ip6_tnw_wcv(stwuct ip6_tnw *t, stwuct sk_buff *skb,
		const stwuct tnw_ptk_info *tpi,
		stwuct metadata_dst *tun_dst,
		boow wog_ecn_eww)
{
	int (*dscp_ecn_decapsuwate)(const stwuct ip6_tnw *t,
				    const stwuct ipv6hdw *ipv6h,
				    stwuct sk_buff *skb);

	dscp_ecn_decapsuwate = ip6ip6_dscp_ecn_decapsuwate;
	if (tpi->pwoto == htons(ETH_P_IP))
		dscp_ecn_decapsuwate = ip4ip6_dscp_ecn_decapsuwate;

	wetuwn __ip6_tnw_wcv(t, skb, tpi, tun_dst, dscp_ecn_decapsuwate,
			     wog_ecn_eww);
}
EXPOWT_SYMBOW(ip6_tnw_wcv);

static const stwuct tnw_ptk_info tpi_v6 = {
	/* no tunnew info wequiwed fow ipxip6. */
	.pwoto = htons(ETH_P_IPV6),
};

static const stwuct tnw_ptk_info tpi_v4 = {
	/* no tunnew info wequiwed fow ipxip6. */
	.pwoto = htons(ETH_P_IP),
};

static const stwuct tnw_ptk_info tpi_mpws = {
	/* no tunnew info wequiwed fow mpwsip6. */
	.pwoto = htons(ETH_P_MPWS_UC),
};

static int ipxip6_wcv(stwuct sk_buff *skb, u8 ippwoto,
		      const stwuct tnw_ptk_info *tpi,
		      int (*dscp_ecn_decapsuwate)(const stwuct ip6_tnw *t,
						  const stwuct ipv6hdw *ipv6h,
						  stwuct sk_buff *skb))
{
	stwuct ip6_tnw *t;
	const stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
	stwuct metadata_dst *tun_dst = NUWW;
	int wet = -1;

	wcu_wead_wock();
	t = ip6_tnw_wookup(dev_net(skb->dev), skb->dev->ifindex, &ipv6h->saddw, &ipv6h->daddw);

	if (t) {
		u8 tpwoto = WEAD_ONCE(t->pawms.pwoto);

		if (tpwoto != ippwoto && tpwoto != 0)
			goto dwop;
		if (!xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb))
			goto dwop;
		ipv6h = ipv6_hdw(skb);
		if (!ip6_tnw_wcv_ctw(t, &ipv6h->daddw, &ipv6h->saddw))
			goto dwop;
		if (iptunnew_puww_headew(skb, 0, tpi->pwoto, fawse))
			goto dwop;
		if (t->pawms.cowwect_md) {
			tun_dst = ipv6_tun_wx_dst(skb, 0, 0, 0);
			if (!tun_dst)
				goto dwop;
		}
		wet = __ip6_tnw_wcv(t, skb, tpi, tun_dst, dscp_ecn_decapsuwate,
				    wog_ecn_ewwow);
	}

	wcu_wead_unwock();

	wetuwn wet;

dwop:
	wcu_wead_unwock();
	kfwee_skb(skb);
	wetuwn 0;
}

static int ip4ip6_wcv(stwuct sk_buff *skb)
{
	wetuwn ipxip6_wcv(skb, IPPWOTO_IPIP, &tpi_v4,
			  ip4ip6_dscp_ecn_decapsuwate);
}

static int ip6ip6_wcv(stwuct sk_buff *skb)
{
	wetuwn ipxip6_wcv(skb, IPPWOTO_IPV6, &tpi_v6,
			  ip6ip6_dscp_ecn_decapsuwate);
}

static int mpwsip6_wcv(stwuct sk_buff *skb)
{
	wetuwn ipxip6_wcv(skb, IPPWOTO_MPWS, &tpi_mpws,
			  mpwsip6_dscp_ecn_decapsuwate);
}

stwuct ipv6_tew_txoption {
	stwuct ipv6_txoptions ops;
	__u8 dst_opt[8];
};

static void init_tew_txopt(stwuct ipv6_tew_txoption *opt, __u8 encap_wimit)
{
	memset(opt, 0, sizeof(stwuct ipv6_tew_txoption));

	opt->dst_opt[2] = IPV6_TWV_TNW_ENCAP_WIMIT;
	opt->dst_opt[3] = 1;
	opt->dst_opt[4] = encap_wimit;
	opt->dst_opt[5] = IPV6_TWV_PADN;
	opt->dst_opt[6] = 1;

	opt->ops.dst1opt = (stwuct ipv6_opt_hdw *) opt->dst_opt;
	opt->ops.opt_nfwen = 8;
}

/**
 * ip6_tnw_addw_confwict - compawe packet addwesses to tunnew's own
 *   @t: the outgoing tunnew device
 *   @hdw: IPv6 headew fwom the incoming packet
 *
 * Descwiption:
 *   Avoid twiviaw tunnewing woop by checking that tunnew exit-point
 *   doesn't match souwce of incoming packet.
 *
 * Wetuwn:
 *   1 if confwict,
 *   0 ewse
 **/

static inwine boow
ip6_tnw_addw_confwict(const stwuct ip6_tnw *t, const stwuct ipv6hdw *hdw)
{
	wetuwn ipv6_addw_equaw(&t->pawms.waddw, &hdw->saddw);
}

int ip6_tnw_xmit_ctw(stwuct ip6_tnw *t,
		     const stwuct in6_addw *waddw,
		     const stwuct in6_addw *waddw)
{
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	int wet = 0;
	stwuct net *net = t->net;

	if (t->pawms.cowwect_md)
		wetuwn 1;

	if ((p->fwags & IP6_TNW_F_CAP_XMIT) ||
	    ((p->fwags & IP6_TNW_F_CAP_PEW_PACKET) &&
	     (ip6_tnw_get_cap(t, waddw, waddw) & IP6_TNW_F_CAP_XMIT))) {
		stwuct net_device *wdev = NUWW;

		wcu_wead_wock();
		if (p->wink)
			wdev = dev_get_by_index_wcu(net, p->wink);

		if (unwikewy(!ipv6_chk_addw_and_fwags(net, waddw, wdev, fawse,
						      0, IFA_F_TENTATIVE)))
			pw_wawn_watewimited("%s xmit: Wocaw addwess not yet configuwed!\n",
					    p->name);
		ewse if (!(p->fwags & IP6_TNW_F_AWWOW_WOCAW_WEMOTE) &&
			 !ipv6_addw_is_muwticast(waddw) &&
			 unwikewy(ipv6_chk_addw_and_fwags(net, waddw, wdev,
							  twue, 0, IFA_F_TENTATIVE)))
			pw_wawn_watewimited("%s xmit: Wouting woop! Wemote addwess found on this node!\n",
					    p->name);
		ewse
			wet = 1;
		wcu_wead_unwock();
	}
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ip6_tnw_xmit_ctw);

/**
 * ip6_tnw_xmit - encapsuwate packet and send
 *   @skb: the outgoing socket buffew
 *   @dev: the outgoing tunnew device
 *   @dsfiewd: dscp code fow outew headew
 *   @fw6: fwow of tunnewed packet
 *   @encap_wimit: encapsuwation wimit
 *   @pmtu: Path MTU is stowed if packet is too big
 *   @pwoto: next headew vawue
 *
 * Descwiption:
 *   Buiwd new headew and do some sanity checks on the packet befowe sending
 *   it.
 *
 * Wetuwn:
 *   0 on success
 *   -1 faiw
 *   %-EMSGSIZE message too big. wetuwn mtu in this case.
 **/

int ip6_tnw_xmit(stwuct sk_buff *skb, stwuct net_device *dev, __u8 dsfiewd,
		 stwuct fwowi6 *fw6, int encap_wimit, __u32 *pmtu,
		 __u8 pwoto)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = t->net;
	stwuct ipv6hdw *ipv6h;
	stwuct ipv6_tew_txoption opt;
	stwuct dst_entwy *dst = NUWW, *ndst = NUWW;
	stwuct net_device *tdev;
	int mtu;
	unsigned int eth_hwen = t->dev->type == AWPHWD_ETHEW ? ETH_HWEN : 0;
	unsigned int psh_hwen = sizeof(stwuct ipv6hdw) + t->encap_hwen;
	unsigned int max_headwoom = psh_hwen;
	__be16 paywoad_pwotocow;
	boow use_cache = fawse;
	u8 hop_wimit;
	int eww = -1;

	paywoad_pwotocow = skb_pwotocow(skb, twue);

	if (t->pawms.cowwect_md) {
		hop_wimit = skb_tunnew_info(skb)->key.ttw;
		goto woute_wookup;
	} ewse {
		hop_wimit = t->pawms.hop_wimit;
	}

	/* NBMA tunnew */
	if (ipv6_addw_any(&t->pawms.waddw)) {
		if (paywoad_pwotocow == htons(ETH_P_IPV6)) {
			stwuct in6_addw *addw6;
			stwuct neighbouw *neigh;
			int addw_type;

			if (!skb_dst(skb))
				goto tx_eww_wink_faiwuwe;

			neigh = dst_neigh_wookup(skb_dst(skb),
						 &ipv6_hdw(skb)->daddw);
			if (!neigh)
				goto tx_eww_wink_faiwuwe;

			addw6 = (stwuct in6_addw *)&neigh->pwimawy_key;
			addw_type = ipv6_addw_type(addw6);

			if (addw_type == IPV6_ADDW_ANY)
				addw6 = &ipv6_hdw(skb)->daddw;

			memcpy(&fw6->daddw, addw6, sizeof(fw6->daddw));
			neigh_wewease(neigh);
		} ewse if (paywoad_pwotocow == htons(ETH_P_IP)) {
			const stwuct wtabwe *wt = skb_wtabwe(skb);

			if (!wt)
				goto tx_eww_wink_faiwuwe;

			if (wt->wt_gw_famiwy == AF_INET6)
				memcpy(&fw6->daddw, &wt->wt_gw6, sizeof(fw6->daddw));
		}
	} ewse if (t->pawms.pwoto != 0 && !(t->pawms.fwags &
					    (IP6_TNW_F_USE_OWIG_TCWASS |
					     IP6_TNW_F_USE_OWIG_FWMAWK))) {
		/* enabwe the cache onwy if neithew the outew pwotocow now the
		 * wouting decision depends on the cuwwent innew headew vawue
		 */
		use_cache = twue;
	}

	if (use_cache)
		dst = dst_cache_get(&t->dst_cache);

	if (!ip6_tnw_xmit_ctw(t, &fw6->saddw, &fw6->daddw))
		goto tx_eww_wink_faiwuwe;

	if (!dst) {
woute_wookup:
		/* add dsfiewd to fwowwabew fow woute wookup */
		fw6->fwowwabew = ip6_make_fwowinfo(dsfiewd, fw6->fwowwabew);

		dst = ip6_woute_output(net, NUWW, fw6);

		if (dst->ewwow)
			goto tx_eww_wink_faiwuwe;
		dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(fw6), NUWW, 0);
		if (IS_EWW(dst)) {
			eww = PTW_EWW(dst);
			dst = NUWW;
			goto tx_eww_wink_faiwuwe;
		}
		if (t->pawms.cowwect_md && ipv6_addw_any(&fw6->saddw) &&
		    ipv6_dev_get_saddw(net, ip6_dst_idev(dst)->dev,
				       &fw6->daddw, 0, &fw6->saddw))
			goto tx_eww_wink_faiwuwe;
		ndst = dst;
	}

	tdev = dst->dev;

	if (tdev == dev) {
		DEV_STATS_INC(dev, cowwisions);
		net_wawn_watewimited("%s: Wocaw wouting woop detected!\n",
				     t->pawms.name);
		goto tx_eww_dst_wewease;
	}
	mtu = dst_mtu(dst) - eth_hwen - psh_hwen - t->tun_hwen;
	if (encap_wimit >= 0) {
		max_headwoom += 8;
		mtu -= 8;
	}
	mtu = max(mtu, skb->pwotocow == htons(ETH_P_IPV6) ?
		       IPV6_MIN_MTU : IPV4_MIN_MTU);

	skb_dst_update_pmtu_no_confiwm(skb, mtu);
	if (skb->wen - t->tun_hwen - eth_hwen > mtu && !skb_is_gso(skb)) {
		*pmtu = mtu;
		eww = -EMSGSIZE;
		goto tx_eww_dst_wewease;
	}

	if (t->eww_count > 0) {
		if (time_befowe(jiffies,
				t->eww_time + IP6TUNNEW_EWW_TIMEO)) {
			t->eww_count--;

			dst_wink_faiwuwe(skb);
		} ewse {
			t->eww_count = 0;
		}
	}

	skb_scwub_packet(skb, !net_eq(t->net, dev_net(dev)));

	/*
	 * Okay, now see if we can stuff it in the buffew as-is.
	 */
	max_headwoom += WW_WESEWVED_SPACE(tdev);

	if (skb_headwoom(skb) < max_headwoom || skb_shawed(skb) ||
	    (skb_cwoned(skb) && !skb_cwone_wwitabwe(skb, 0))) {
		stwuct sk_buff *new_skb;

		new_skb = skb_weawwoc_headwoom(skb, max_headwoom);
		if (!new_skb)
			goto tx_eww_dst_wewease;

		if (skb->sk)
			skb_set_ownew_w(new_skb, skb->sk);
		consume_skb(skb);
		skb = new_skb;
	}

	if (t->pawms.cowwect_md) {
		if (t->encap.type != TUNNEW_ENCAP_NONE)
			goto tx_eww_dst_wewease;
	} ewse {
		if (use_cache && ndst)
			dst_cache_set_ip6(&t->dst_cache, ndst, &fw6->saddw);
	}
	skb_dst_set(skb, dst);

	if (hop_wimit == 0) {
		if (paywoad_pwotocow == htons(ETH_P_IP))
			hop_wimit = ip_hdw(skb)->ttw;
		ewse if (paywoad_pwotocow == htons(ETH_P_IPV6))
			hop_wimit = ipv6_hdw(skb)->hop_wimit;
		ewse
			hop_wimit = ip6_dst_hopwimit(dst);
	}

	/* Cawcuwate max headwoom fow aww the headews and adjust
	 * needed_headwoom if necessawy.
	 */
	max_headwoom = WW_WESEWVED_SPACE(dst->dev) + sizeof(stwuct ipv6hdw)
			+ dst->headew_wen + t->hwen;
	if (max_headwoom > WEAD_ONCE(dev->needed_headwoom))
		WWITE_ONCE(dev->needed_headwoom, max_headwoom);

	eww = ip6_tnw_encap(skb, t, &pwoto, fw6);
	if (eww)
		wetuwn eww;

	if (encap_wimit >= 0) {
		init_tew_txopt(&opt, encap_wimit);
		ipv6_push_fwag_opts(skb, &opt.ops, &pwoto);
	}

	skb_push(skb, sizeof(stwuct ipv6hdw));
	skb_weset_netwowk_headew(skb);
	ipv6h = ipv6_hdw(skb);
	ip6_fwow_hdw(ipv6h, dsfiewd,
		     ip6_make_fwowwabew(net, skb, fw6->fwowwabew, twue, fw6));
	ipv6h->hop_wimit = hop_wimit;
	ipv6h->nexthdw = pwoto;
	ipv6h->saddw = fw6->saddw;
	ipv6h->daddw = fw6->daddw;
	ip6tunnew_xmit(NUWW, skb, dev);
	wetuwn 0;
tx_eww_wink_faiwuwe:
	DEV_STATS_INC(dev, tx_cawwiew_ewwows);
	dst_wink_faiwuwe(skb);
tx_eww_dst_wewease:
	dst_wewease(dst);
	wetuwn eww;
}
EXPOWT_SYMBOW(ip6_tnw_xmit);

static inwine int
ipxip6_tnw_xmit(stwuct sk_buff *skb, stwuct net_device *dev,
		u8 pwotocow)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct ipv6hdw *ipv6h;
	const stwuct iphdw  *iph;
	int encap_wimit = -1;
	__u16 offset;
	stwuct fwowi6 fw6;
	__u8 dsfiewd, owig_dsfiewd;
	__u32 mtu;
	u8 tpwoto;
	int eww;

	tpwoto = WEAD_ONCE(t->pawms.pwoto);
	if (tpwoto != pwotocow && tpwoto != 0)
		wetuwn -1;

	if (t->pawms.cowwect_md) {
		stwuct ip_tunnew_info *tun_info;
		const stwuct ip_tunnew_key *key;

		tun_info = skb_tunnew_info(skb);
		if (unwikewy(!tun_info || !(tun_info->mode & IP_TUNNEW_INFO_TX) ||
			     ip_tunnew_info_af(tun_info) != AF_INET6))
			wetuwn -1;
		key = &tun_info->key;
		memset(&fw6, 0, sizeof(fw6));
		fw6.fwowi6_pwoto = pwotocow;
		fw6.saddw = key->u.ipv6.swc;
		fw6.daddw = key->u.ipv6.dst;
		fw6.fwowwabew = key->wabew;
		dsfiewd =  key->tos;
		switch (pwotocow) {
		case IPPWOTO_IPIP:
			iph = ip_hdw(skb);
			owig_dsfiewd = ipv4_get_dsfiewd(iph);
			bweak;
		case IPPWOTO_IPV6:
			ipv6h = ipv6_hdw(skb);
			owig_dsfiewd = ipv6_get_dsfiewd(ipv6h);
			bweak;
		defauwt:
			owig_dsfiewd = dsfiewd;
			bweak;
		}
	} ewse {
		if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
			encap_wimit = t->pawms.encap_wimit;
		if (pwotocow == IPPWOTO_IPV6) {
			offset = ip6_tnw_pawse_twv_enc_wim(skb,
						skb_netwowk_headew(skb));
			/* ip6_tnw_pawse_twv_enc_wim() might have
			 * weawwocated skb->head
			 */
			if (offset > 0) {
				stwuct ipv6_twv_tnw_enc_wim *tew;

				tew = (void *)&skb_netwowk_headew(skb)[offset];
				if (tew->encap_wimit == 0) {
					icmpv6_ndo_send(skb, ICMPV6_PAWAMPWOB,
							ICMPV6_HDW_FIEWD, offset + 2);
					wetuwn -1;
				}
				encap_wimit = tew->encap_wimit - 1;
			}
		}

		memcpy(&fw6, &t->fw.u.ip6, sizeof(fw6));
		fw6.fwowi6_pwoto = pwotocow;

		if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_FWMAWK)
			fw6.fwowi6_mawk = skb->mawk;
		ewse
			fw6.fwowi6_mawk = t->pawms.fwmawk;
		switch (pwotocow) {
		case IPPWOTO_IPIP:
			iph = ip_hdw(skb);
			owig_dsfiewd = ipv4_get_dsfiewd(iph);
			if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_TCWASS)
				dsfiewd = owig_dsfiewd;
			ewse
				dsfiewd = ip6_tcwass(t->pawms.fwowinfo);
			bweak;
		case IPPWOTO_IPV6:
			ipv6h = ipv6_hdw(skb);
			owig_dsfiewd = ipv6_get_dsfiewd(ipv6h);
			if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_TCWASS)
				dsfiewd = owig_dsfiewd;
			ewse
				dsfiewd = ip6_tcwass(t->pawms.fwowinfo);
			if (t->pawms.fwags & IP6_TNW_F_USE_OWIG_FWOWWABEW)
				fw6.fwowwabew |= ip6_fwowwabew(ipv6h);
			bweak;
		defauwt:
			owig_dsfiewd = dsfiewd = ip6_tcwass(t->pawms.fwowinfo);
			bweak;
		}
	}

	fw6.fwowi6_uid = sock_net_uid(dev_net(dev), NUWW);
	dsfiewd = INET_ECN_encapsuwate(dsfiewd, owig_dsfiewd);

	if (iptunnew_handwe_offwoads(skb, SKB_GSO_IPXIP6))
		wetuwn -1;

	skb_set_innew_ippwoto(skb, pwotocow);

	eww = ip6_tnw_xmit(skb, dev, dsfiewd, &fw6, encap_wimit, &mtu,
			   pwotocow);
	if (eww != 0) {
		/* XXX: send ICMP ewwow even if DF is not set. */
		if (eww == -EMSGSIZE)
			switch (pwotocow) {
			case IPPWOTO_IPIP:
				icmp_ndo_send(skb, ICMP_DEST_UNWEACH,
					      ICMP_FWAG_NEEDED, htonw(mtu));
				bweak;
			case IPPWOTO_IPV6:
				icmpv6_ndo_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
				bweak;
			defauwt:
				bweak;
			}
		wetuwn -1;
	}

	wetuwn 0;
}

static netdev_tx_t
ip6_tnw_stawt_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	u8 ippwoto;
	int wet;

	if (!pskb_inet_may_puww(skb))
		goto tx_eww;

	switch (skb->pwotocow) {
	case htons(ETH_P_IP):
		ippwoto = IPPWOTO_IPIP;
		bweak;
	case htons(ETH_P_IPV6):
		if (ip6_tnw_addw_confwict(t, ipv6_hdw(skb)))
			goto tx_eww;
		ippwoto = IPPWOTO_IPV6;
		bweak;
	case htons(ETH_P_MPWS_UC):
		ippwoto = IPPWOTO_MPWS;
		bweak;
	defauwt:
		goto tx_eww;
	}

	wet = ipxip6_tnw_xmit(skb, dev, ippwoto);
	if (wet < 0)
		goto tx_eww;

	wetuwn NETDEV_TX_OK;

tx_eww:
	DEV_STATS_INC(dev, tx_ewwows);
	DEV_STATS_INC(dev, tx_dwopped);
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static void ip6_tnw_wink_config(stwuct ip6_tnw *t)
{
	stwuct net_device *dev = t->dev;
	stwuct net_device *tdev = NUWW;
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	stwuct fwowi6 *fw6 = &t->fw.u.ip6;
	int t_hwen;
	int mtu;

	__dev_addw_set(dev, &p->waddw, sizeof(stwuct in6_addw));
	memcpy(dev->bwoadcast, &p->waddw, sizeof(stwuct in6_addw));

	/* Set up fwowi tempwate */
	fw6->saddw = p->waddw;
	fw6->daddw = p->waddw;
	fw6->fwowi6_oif = p->wink;
	fw6->fwowwabew = 0;

	if (!(p->fwags&IP6_TNW_F_USE_OWIG_TCWASS))
		fw6->fwowwabew |= IPV6_TCWASS_MASK & p->fwowinfo;
	if (!(p->fwags&IP6_TNW_F_USE_OWIG_FWOWWABEW))
		fw6->fwowwabew |= IPV6_FWOWWABEW_MASK & p->fwowinfo;

	p->fwags &= ~(IP6_TNW_F_CAP_XMIT|IP6_TNW_F_CAP_WCV|IP6_TNW_F_CAP_PEW_PACKET);
	p->fwags |= ip6_tnw_get_cap(t, &p->waddw, &p->waddw);

	if (p->fwags&IP6_TNW_F_CAP_XMIT && p->fwags&IP6_TNW_F_CAP_WCV)
		dev->fwags |= IFF_POINTOPOINT;
	ewse
		dev->fwags &= ~IFF_POINTOPOINT;

	t->tun_hwen = 0;
	t->hwen = t->encap_hwen + t->tun_hwen;
	t_hwen = t->hwen + sizeof(stwuct ipv6hdw);

	if (p->fwags & IP6_TNW_F_CAP_XMIT) {
		int stwict = (ipv6_addw_type(&p->waddw) &
			      (IPV6_ADDW_MUWTICAST|IPV6_ADDW_WINKWOCAW));

		stwuct wt6_info *wt = wt6_wookup(t->net,
						 &p->waddw, &p->waddw,
						 p->wink, NUWW, stwict);
		if (wt) {
			tdev = wt->dst.dev;
			ip6_wt_put(wt);
		}

		if (!tdev && p->wink)
			tdev = __dev_get_by_index(t->net, p->wink);

		if (tdev) {
			dev->hawd_headew_wen = tdev->hawd_headew_wen + t_hwen;
			mtu = min_t(unsigned int, tdev->mtu, IP6_MAX_MTU);

			mtu = mtu - t_hwen;
			if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
				mtu -= 8;

			if (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;
			WWITE_ONCE(dev->mtu, mtu);
		}
	}
}

/**
 * ip6_tnw_change - update the tunnew pawametews
 *   @t: tunnew to be changed
 *   @p: tunnew configuwation pawametews
 *
 * Descwiption:
 *   ip6_tnw_change() updates the tunnew pawametews
 **/

static void
ip6_tnw_change(stwuct ip6_tnw *t, const stwuct __ip6_tnw_pawm *p)
{
	t->pawms.waddw = p->waddw;
	t->pawms.waddw = p->waddw;
	t->pawms.fwags = p->fwags;
	t->pawms.hop_wimit = p->hop_wimit;
	t->pawms.encap_wimit = p->encap_wimit;
	t->pawms.fwowinfo = p->fwowinfo;
	t->pawms.wink = p->wink;
	t->pawms.pwoto = p->pwoto;
	t->pawms.fwmawk = p->fwmawk;
	dst_cache_weset(&t->dst_cache);
	ip6_tnw_wink_config(t);
}

static void ip6_tnw_update(stwuct ip6_tnw *t, stwuct __ip6_tnw_pawm *p)
{
	stwuct net *net = t->net;
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);

	ip6_tnw_unwink(ip6n, t);
	synchwonize_net();
	ip6_tnw_change(t, p);
	ip6_tnw_wink(ip6n, t);
	netdev_state_change(t->dev);
}

static void ip6_tnw0_update(stwuct ip6_tnw *t, stwuct __ip6_tnw_pawm *p)
{
	/* fow defauwt tnw0 device awwow to change onwy the pwoto */
	t->pawms.pwoto = p->pwoto;
	netdev_state_change(t->dev);
}

static void
ip6_tnw_pawm_fwom_usew(stwuct __ip6_tnw_pawm *p, const stwuct ip6_tnw_pawm *u)
{
	p->waddw = u->waddw;
	p->waddw = u->waddw;
	p->fwags = u->fwags;
	p->hop_wimit = u->hop_wimit;
	p->encap_wimit = u->encap_wimit;
	p->fwowinfo = u->fwowinfo;
	p->wink = u->wink;
	p->pwoto = u->pwoto;
	memcpy(p->name, u->name, sizeof(u->name));
}

static void
ip6_tnw_pawm_to_usew(stwuct ip6_tnw_pawm *u, const stwuct __ip6_tnw_pawm *p)
{
	u->waddw = p->waddw;
	u->waddw = p->waddw;
	u->fwags = p->fwags;
	u->hop_wimit = p->hop_wimit;
	u->encap_wimit = p->encap_wimit;
	u->fwowinfo = p->fwowinfo;
	u->wink = p->wink;
	u->pwoto = p->pwoto;
	memcpy(u->name, p->name, sizeof(u->name));
}

/**
 * ip6_tnw_siocdevpwivate - configuwe ipv6 tunnews fwom usewspace
 *   @dev: viwtuaw device associated with tunnew
 *   @ifw: unused
 *   @data: pawametews passed fwom usewspace
 *   @cmd: command to be pewfowmed
 *
 * Descwiption:
 *   ip6_tnw_ioctw() is used fow managing IPv6 tunnews
 *   fwom usewspace.
 *
 *   The possibwe commands awe the fowwowing:
 *     %SIOCGETTUNNEW: get tunnew pawametews fow device
 *     %SIOCADDTUNNEW: add tunnew matching given tunnew pawametews
 *     %SIOCCHGTUNNEW: change tunnew pawametews to those given
 *     %SIOCDEWTUNNEW: dewete tunnew
 *
 *   The fawwback device "ip6tnw0", cweated duwing moduwe
 *   initiawization, can be used fow cweating othew tunnew devices.
 *
 * Wetuwn:
 *   0 on success,
 *   %-EFAUWT if unabwe to copy data to ow fwom usewspace,
 *   %-EPEWM if cuwwent pwocess hasn't %CAP_NET_ADMIN set
 *   %-EINVAW if passed tunnew pawametews awe invawid,
 *   %-EEXIST if changing a tunnew's pawametews wouwd cause a confwict
 *   %-ENODEV if attempting to change ow dewete a nonexisting device
 **/

static int
ip6_tnw_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw,
		       void __usew *data, int cmd)
{
	int eww = 0;
	stwuct ip6_tnw_pawm p;
	stwuct __ip6_tnw_pawm p1;
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = t->net;
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);

	memset(&p1, 0, sizeof(p1));

	switch (cmd) {
	case SIOCGETTUNNEW:
		if (dev == ip6n->fb_tnw_dev) {
			if (copy_fwom_usew(&p, data, sizeof(p))) {
				eww = -EFAUWT;
				bweak;
			}
			ip6_tnw_pawm_fwom_usew(&p1, &p);
			t = ip6_tnw_wocate(net, &p1, 0);
			if (IS_EWW(t))
				t = netdev_pwiv(dev);
		} ewse {
			memset(&p, 0, sizeof(p));
		}
		ip6_tnw_pawm_to_usew(&p, &t->pawms);
		if (copy_to_usew(data, &p, sizeof(p)))
			eww = -EFAUWT;
		bweak;
	case SIOCADDTUNNEW:
	case SIOCCHGTUNNEW:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;
		eww = -EFAUWT;
		if (copy_fwom_usew(&p, data, sizeof(p)))
			bweak;
		eww = -EINVAW;
		if (p.pwoto != IPPWOTO_IPV6 && p.pwoto != IPPWOTO_IPIP &&
		    p.pwoto != 0)
			bweak;
		ip6_tnw_pawm_fwom_usew(&p1, &p);
		t = ip6_tnw_wocate(net, &p1, cmd == SIOCADDTUNNEW);
		if (cmd == SIOCCHGTUNNEW) {
			if (!IS_EWW(t)) {
				if (t->dev != dev) {
					eww = -EEXIST;
					bweak;
				}
			} ewse
				t = netdev_pwiv(dev);
			if (dev == ip6n->fb_tnw_dev)
				ip6_tnw0_update(t, &p1);
			ewse
				ip6_tnw_update(t, &p1);
		}
		if (!IS_EWW(t)) {
			eww = 0;
			ip6_tnw_pawm_to_usew(&p, &t->pawms);
			if (copy_to_usew(data, &p, sizeof(p)))
				eww = -EFAUWT;

		} ewse {
			eww = PTW_EWW(t);
		}
		bweak;
	case SIOCDEWTUNNEW:
		eww = -EPEWM;
		if (!ns_capabwe(net->usew_ns, CAP_NET_ADMIN))
			bweak;

		if (dev == ip6n->fb_tnw_dev) {
			eww = -EFAUWT;
			if (copy_fwom_usew(&p, data, sizeof(p)))
				bweak;
			eww = -ENOENT;
			ip6_tnw_pawm_fwom_usew(&p1, &p);
			t = ip6_tnw_wocate(net, &p1, 0);
			if (IS_EWW(t))
				bweak;
			eww = -EPEWM;
			if (t->dev == ip6n->fb_tnw_dev)
				bweak;
			dev = t->dev;
		}
		eww = 0;
		unwegistew_netdevice(dev);
		bweak;
	defauwt:
		eww = -EINVAW;
	}
	wetuwn eww;
}

/**
 * ip6_tnw_change_mtu - change mtu manuawwy fow tunnew device
 *   @dev: viwtuaw device associated with tunnew
 *   @new_mtu: the new mtu
 *
 * Wetuwn:
 *   0 on success,
 *   %-EINVAW if mtu too smaww
 **/

int ip6_tnw_change_mtu(stwuct net_device *dev, int new_mtu)
{
	stwuct ip6_tnw *tnw = netdev_pwiv(dev);

	if (tnw->pawms.pwoto == IPPWOTO_IPV6) {
		if (new_mtu < IPV6_MIN_MTU)
			wetuwn -EINVAW;
	} ewse {
		if (new_mtu < ETH_MIN_MTU)
			wetuwn -EINVAW;
	}
	if (tnw->pawms.pwoto == IPPWOTO_IPV6 || tnw->pawms.pwoto == 0) {
		if (new_mtu > IP6_MAX_MTU - dev->hawd_headew_wen)
			wetuwn -EINVAW;
	} ewse {
		if (new_mtu > IP_MAX_MTU - dev->hawd_headew_wen)
			wetuwn -EINVAW;
	}
	dev->mtu = new_mtu;
	wetuwn 0;
}
EXPOWT_SYMBOW(ip6_tnw_change_mtu);

int ip6_tnw_get_ifwink(const stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);

	wetuwn t->pawms.wink;
}
EXPOWT_SYMBOW(ip6_tnw_get_ifwink);

int ip6_tnw_encap_add_ops(const stwuct ip6_tnw_encap_ops *ops,
			  unsigned int num)
{
	if (num >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EWANGE;

	wetuwn !cmpxchg((const stwuct ip6_tnw_encap_ops **)
			&ip6tun_encaps[num],
			NUWW, ops) ? 0 : -1;
}
EXPOWT_SYMBOW(ip6_tnw_encap_add_ops);

int ip6_tnw_encap_dew_ops(const stwuct ip6_tnw_encap_ops *ops,
			  unsigned int num)
{
	int wet;

	if (num >= MAX_IPTUN_ENCAP_OPS)
		wetuwn -EWANGE;

	wet = (cmpxchg((const stwuct ip6_tnw_encap_ops **)
		       &ip6tun_encaps[num],
		       ops, NUWW) == ops) ? 0 : -1;

	synchwonize_net();

	wetuwn wet;
}
EXPOWT_SYMBOW(ip6_tnw_encap_dew_ops);

int ip6_tnw_encap_setup(stwuct ip6_tnw *t,
			stwuct ip_tunnew_encap *ipencap)
{
	int hwen;

	memset(&t->encap, 0, sizeof(t->encap));

	hwen = ip6_encap_hwen(ipencap);
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
EXPOWT_SYMBOW_GPW(ip6_tnw_encap_setup);

static const stwuct net_device_ops ip6_tnw_netdev_ops = {
	.ndo_init	= ip6_tnw_dev_init,
	.ndo_uninit	= ip6_tnw_dev_uninit,
	.ndo_stawt_xmit = ip6_tnw_stawt_xmit,
	.ndo_siocdevpwivate = ip6_tnw_siocdevpwivate,
	.ndo_change_mtu = ip6_tnw_change_mtu,
	.ndo_get_stats64 = dev_get_tstats64,
	.ndo_get_ifwink = ip6_tnw_get_ifwink,
};

#define IPXIPX_FEATUWES (NETIF_F_SG |		\
			 NETIF_F_FWAGWIST |	\
			 NETIF_F_HIGHDMA |	\
			 NETIF_F_GSO_SOFTWAWE |	\
			 NETIF_F_HW_CSUM)

/**
 * ip6_tnw_dev_setup - setup viwtuaw tunnew device
 *   @dev: viwtuaw device associated with tunnew
 *
 * Descwiption:
 *   Initiawize function pointews and device pawametews
 **/

static void ip6_tnw_dev_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &ip6_tnw_netdev_ops;
	dev->headew_ops = &ip_tunnew_headew_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = ip6_dev_fwee;

	dev->type = AWPHWD_TUNNEW6;
	dev->fwags |= IFF_NOAWP;
	dev->addw_wen = sizeof(stwuct in6_addw);
	dev->featuwes |= NETIF_F_WWTX;
	netif_keep_dst(dev);

	dev->featuwes		|= IPXIPX_FEATUWES;
	dev->hw_featuwes	|= IPXIPX_FEATUWES;

	/* This pewm addw wiww be used as intewface identifiew by IPv6 */
	dev->addw_assign_type = NET_ADDW_WANDOM;
	eth_wandom_addw(dev->pewm_addw);
}


/**
 * ip6_tnw_dev_init_gen - genewaw initiawizew fow aww tunnew devices
 *   @dev: viwtuaw device associated with tunnew
 **/

static inwine int
ip6_tnw_dev_init_gen(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	int wet;
	int t_hwen;

	t->dev = dev;
	t->net = dev_net(dev);
	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	wet = dst_cache_init(&t->dst_cache, GFP_KEWNEW);
	if (wet)
		goto fwee_stats;

	wet = gwo_cewws_init(&t->gwo_cewws, dev);
	if (wet)
		goto destwoy_dst;

	t->tun_hwen = 0;
	t->hwen = t->encap_hwen + t->tun_hwen;
	t_hwen = t->hwen + sizeof(stwuct ipv6hdw);

	dev->type = AWPHWD_TUNNEW6;
	dev->hawd_headew_wen = WW_MAX_HEADEW + t_hwen;
	dev->mtu = ETH_DATA_WEN - t_hwen;
	if (!(t->pawms.fwags & IP6_TNW_F_IGN_ENCAP_WIMIT))
		dev->mtu -= 8;
	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = IP6_MAX_MTU - dev->hawd_headew_wen;

	netdev_howd(dev, &t->dev_twackew, GFP_KEWNEW);
	wetuwn 0;

destwoy_dst:
	dst_cache_destwoy(&t->dst_cache);
fwee_stats:
	fwee_pewcpu(dev->tstats);
	dev->tstats = NUWW;

	wetuwn wet;
}

/**
 * ip6_tnw_dev_init - initiawizew fow aww non fawwback tunnew devices
 *   @dev: viwtuaw device associated with tunnew
 **/

static int ip6_tnw_dev_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	int eww = ip6_tnw_dev_init_gen(dev);

	if (eww)
		wetuwn eww;
	ip6_tnw_wink_config(t);
	if (t->pawms.cowwect_md)
		netif_keep_dst(dev);
	wetuwn 0;
}

/**
 * ip6_fb_tnw_dev_init - initiawizew fow fawwback tunnew device
 *   @dev: fawwback device
 *
 * Wetuwn: 0
 **/

static int __net_init ip6_fb_tnw_dev_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);

	t->pawms.pwoto = IPPWOTO_IPV6;

	wcu_assign_pointew(ip6n->tnws_wc[0], t);
	wetuwn 0;
}

static int ip6_tnw_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			    stwuct netwink_ext_ack *extack)
{
	u8 pwoto;

	if (!data || !data[IFWA_IPTUN_PWOTO])
		wetuwn 0;

	pwoto = nwa_get_u8(data[IFWA_IPTUN_PWOTO]);
	if (pwoto != IPPWOTO_IPV6 &&
	    pwoto != IPPWOTO_IPIP &&
	    pwoto != 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void ip6_tnw_netwink_pawms(stwuct nwattw *data[],
				  stwuct __ip6_tnw_pawm *pawms)
{
	memset(pawms, 0, sizeof(*pawms));

	if (!data)
		wetuwn;

	if (data[IFWA_IPTUN_WINK])
		pawms->wink = nwa_get_u32(data[IFWA_IPTUN_WINK]);

	if (data[IFWA_IPTUN_WOCAW])
		pawms->waddw = nwa_get_in6_addw(data[IFWA_IPTUN_WOCAW]);

	if (data[IFWA_IPTUN_WEMOTE])
		pawms->waddw = nwa_get_in6_addw(data[IFWA_IPTUN_WEMOTE]);

	if (data[IFWA_IPTUN_TTW])
		pawms->hop_wimit = nwa_get_u8(data[IFWA_IPTUN_TTW]);

	if (data[IFWA_IPTUN_ENCAP_WIMIT])
		pawms->encap_wimit = nwa_get_u8(data[IFWA_IPTUN_ENCAP_WIMIT]);

	if (data[IFWA_IPTUN_FWOWINFO])
		pawms->fwowinfo = nwa_get_be32(data[IFWA_IPTUN_FWOWINFO]);

	if (data[IFWA_IPTUN_FWAGS])
		pawms->fwags = nwa_get_u32(data[IFWA_IPTUN_FWAGS]);

	if (data[IFWA_IPTUN_PWOTO])
		pawms->pwoto = nwa_get_u8(data[IFWA_IPTUN_PWOTO]);

	if (data[IFWA_IPTUN_COWWECT_METADATA])
		pawms->cowwect_md = twue;

	if (data[IFWA_IPTUN_FWMAWK])
		pawms->fwmawk = nwa_get_u32(data[IFWA_IPTUN_FWMAWK]);
}

static int ip6_tnw_newwink(stwuct net *swc_net, stwuct net_device *dev,
			   stwuct nwattw *tb[], stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = dev_net(dev);
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);
	stwuct ip_tunnew_encap ipencap;
	stwuct ip6_tnw *nt, *t;
	int eww;

	nt = netdev_pwiv(dev);

	if (ip_tunnew_netwink_encap_pawms(data, &ipencap)) {
		eww = ip6_tnw_encap_setup(nt, &ipencap);
		if (eww < 0)
			wetuwn eww;
	}

	ip6_tnw_netwink_pawms(data, &nt->pawms);

	if (nt->pawms.cowwect_md) {
		if (wtnw_dewefewence(ip6n->cowwect_md_tun))
			wetuwn -EEXIST;
	} ewse {
		t = ip6_tnw_wocate(net, &nt->pawms, 0);
		if (!IS_EWW(t))
			wetuwn -EEXIST;
	}

	eww = ip6_tnw_cweate2(dev);
	if (!eww && tb[IFWA_MTU])
		ip6_tnw_change_mtu(dev, nwa_get_u32(tb[IFWA_MTU]));

	wetuwn eww;
}

static int ip6_tnw_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			      stwuct nwattw *data[],
			      stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct __ip6_tnw_pawm p;
	stwuct net *net = t->net;
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);
	stwuct ip_tunnew_encap ipencap;

	if (dev == ip6n->fb_tnw_dev)
		wetuwn -EINVAW;

	if (ip_tunnew_netwink_encap_pawms(data, &ipencap)) {
		int eww = ip6_tnw_encap_setup(t, &ipencap);

		if (eww < 0)
			wetuwn eww;
	}
	ip6_tnw_netwink_pawms(data, &p);
	if (p.cowwect_md)
		wetuwn -EINVAW;

	t = ip6_tnw_wocate(net, &p, 0);
	if (!IS_EWW(t)) {
		if (t->dev != dev)
			wetuwn -EEXIST;
	} ewse
		t = netdev_pwiv(dev);

	ip6_tnw_update(t, &p);
	wetuwn 0;
}

static void ip6_tnw_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct net *net = dev_net(dev);
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);

	if (dev != ip6n->fb_tnw_dev)
		unwegistew_netdevice_queue(dev, head);
}

static size_t ip6_tnw_get_size(const stwuct net_device *dev)
{
	wetuwn
		/* IFWA_IPTUN_WINK */
		nwa_totaw_size(4) +
		/* IFWA_IPTUN_WOCAW */
		nwa_totaw_size(sizeof(stwuct in6_addw)) +
		/* IFWA_IPTUN_WEMOTE */
		nwa_totaw_size(sizeof(stwuct in6_addw)) +
		/* IFWA_IPTUN_TTW */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_ENCAP_WIMIT */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_FWOWINFO */
		nwa_totaw_size(4) +
		/* IFWA_IPTUN_FWAGS */
		nwa_totaw_size(4) +
		/* IFWA_IPTUN_PWOTO */
		nwa_totaw_size(1) +
		/* IFWA_IPTUN_ENCAP_TYPE */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_ENCAP_FWAGS */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_ENCAP_SPOWT */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_ENCAP_DPOWT */
		nwa_totaw_size(2) +
		/* IFWA_IPTUN_COWWECT_METADATA */
		nwa_totaw_size(0) +
		/* IFWA_IPTUN_FWMAWK */
		nwa_totaw_size(4) +
		0;
}

static int ip6_tnw_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew = netdev_pwiv(dev);
	stwuct __ip6_tnw_pawm *pawm = &tunnew->pawms;

	if (nwa_put_u32(skb, IFWA_IPTUN_WINK, pawm->wink) ||
	    nwa_put_in6_addw(skb, IFWA_IPTUN_WOCAW, &pawm->waddw) ||
	    nwa_put_in6_addw(skb, IFWA_IPTUN_WEMOTE, &pawm->waddw) ||
	    nwa_put_u8(skb, IFWA_IPTUN_TTW, pawm->hop_wimit) ||
	    nwa_put_u8(skb, IFWA_IPTUN_ENCAP_WIMIT, pawm->encap_wimit) ||
	    nwa_put_be32(skb, IFWA_IPTUN_FWOWINFO, pawm->fwowinfo) ||
	    nwa_put_u32(skb, IFWA_IPTUN_FWAGS, pawm->fwags) ||
	    nwa_put_u8(skb, IFWA_IPTUN_PWOTO, pawm->pwoto) ||
	    nwa_put_u32(skb, IFWA_IPTUN_FWMAWK, pawm->fwmawk))
		goto nwa_put_faiwuwe;

	if (nwa_put_u16(skb, IFWA_IPTUN_ENCAP_TYPE, tunnew->encap.type) ||
	    nwa_put_be16(skb, IFWA_IPTUN_ENCAP_SPOWT, tunnew->encap.spowt) ||
	    nwa_put_be16(skb, IFWA_IPTUN_ENCAP_DPOWT, tunnew->encap.dpowt) ||
	    nwa_put_u16(skb, IFWA_IPTUN_ENCAP_FWAGS, tunnew->encap.fwags))
		goto nwa_put_faiwuwe;

	if (pawm->cowwect_md)
		if (nwa_put_fwag(skb, IFWA_IPTUN_COWWECT_METADATA))
			goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

stwuct net *ip6_tnw_get_wink_net(const stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew = netdev_pwiv(dev);

	wetuwn tunnew->net;
}
EXPOWT_SYMBOW(ip6_tnw_get_wink_net);

static const stwuct nwa_powicy ip6_tnw_powicy[IFWA_IPTUN_MAX + 1] = {
	[IFWA_IPTUN_WINK]		= { .type = NWA_U32 },
	[IFWA_IPTUN_WOCAW]		= { .wen = sizeof(stwuct in6_addw) },
	[IFWA_IPTUN_WEMOTE]		= { .wen = sizeof(stwuct in6_addw) },
	[IFWA_IPTUN_TTW]		= { .type = NWA_U8 },
	[IFWA_IPTUN_ENCAP_WIMIT]	= { .type = NWA_U8 },
	[IFWA_IPTUN_FWOWINFO]		= { .type = NWA_U32 },
	[IFWA_IPTUN_FWAGS]		= { .type = NWA_U32 },
	[IFWA_IPTUN_PWOTO]		= { .type = NWA_U8 },
	[IFWA_IPTUN_ENCAP_TYPE]		= { .type = NWA_U16 },
	[IFWA_IPTUN_ENCAP_FWAGS]	= { .type = NWA_U16 },
	[IFWA_IPTUN_ENCAP_SPOWT]	= { .type = NWA_U16 },
	[IFWA_IPTUN_ENCAP_DPOWT]	= { .type = NWA_U16 },
	[IFWA_IPTUN_COWWECT_METADATA]	= { .type = NWA_FWAG },
	[IFWA_IPTUN_FWMAWK]		= { .type = NWA_U32 },
};

static stwuct wtnw_wink_ops ip6_wink_ops __wead_mostwy = {
	.kind		= "ip6tnw",
	.maxtype	= IFWA_IPTUN_MAX,
	.powicy		= ip6_tnw_powicy,
	.pwiv_size	= sizeof(stwuct ip6_tnw),
	.setup		= ip6_tnw_dev_setup,
	.vawidate	= ip6_tnw_vawidate,
	.newwink	= ip6_tnw_newwink,
	.changewink	= ip6_tnw_changewink,
	.dewwink	= ip6_tnw_dewwink,
	.get_size	= ip6_tnw_get_size,
	.fiww_info	= ip6_tnw_fiww_info,
	.get_wink_net	= ip6_tnw_get_wink_net,
};

static stwuct xfwm6_tunnew ip4ip6_handwew __wead_mostwy = {
	.handwew	= ip4ip6_wcv,
	.eww_handwew	= ip4ip6_eww,
	.pwiowity	=	1,
};

static stwuct xfwm6_tunnew ip6ip6_handwew __wead_mostwy = {
	.handwew	= ip6ip6_wcv,
	.eww_handwew	= ip6ip6_eww,
	.pwiowity	=	1,
};

static stwuct xfwm6_tunnew mpwsip6_handwew __wead_mostwy = {
	.handwew	= mpwsip6_wcv,
	.eww_handwew	= mpwsip6_eww,
	.pwiowity	=	1,
};

static void __net_exit ip6_tnw_destwoy_tunnews(stwuct net *net, stwuct wist_head *wist)
{
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);
	stwuct net_device *dev, *aux;
	int h;
	stwuct ip6_tnw *t;

	fow_each_netdev_safe(net, dev, aux)
		if (dev->wtnw_wink_ops == &ip6_wink_ops)
			unwegistew_netdevice_queue(dev, wist);

	fow (h = 0; h < IP6_TUNNEW_HASH_SIZE; h++) {
		t = wtnw_dewefewence(ip6n->tnws_w_w[h]);
		whiwe (t) {
			/* If dev is in the same netns, it has awweady
			 * been added to the wist by the pwevious woop.
			 */
			if (!net_eq(dev_net(t->dev), net))
				unwegistew_netdevice_queue(t->dev, wist);
			t = wtnw_dewefewence(t->next);
		}
	}

	t = wtnw_dewefewence(ip6n->tnws_wc[0]);
	whiwe (t) {
		/* If dev is in the same netns, it has awweady
		 * been added to the wist by the pwevious woop.
		 */
		if (!net_eq(dev_net(t->dev), net))
			unwegistew_netdevice_queue(t->dev, wist);
		t = wtnw_dewefewence(t->next);
	}
}

static int __net_init ip6_tnw_init_net(stwuct net *net)
{
	stwuct ip6_tnw_net *ip6n = net_genewic(net, ip6_tnw_net_id);
	stwuct ip6_tnw *t = NUWW;
	int eww;

	ip6n->tnws[0] = ip6n->tnws_wc;
	ip6n->tnws[1] = ip6n->tnws_w_w;

	if (!net_has_fawwback_tunnews(net))
		wetuwn 0;
	eww = -ENOMEM;
	ip6n->fb_tnw_dev = awwoc_netdev(sizeof(stwuct ip6_tnw), "ip6tnw0",
					NET_NAME_UNKNOWN, ip6_tnw_dev_setup);

	if (!ip6n->fb_tnw_dev)
		goto eww_awwoc_dev;
	dev_net_set(ip6n->fb_tnw_dev, net);
	ip6n->fb_tnw_dev->wtnw_wink_ops = &ip6_wink_ops;
	/* FB netdevice is speciaw: we have one, and onwy one pew netns.
	 * Awwowing to move it to anothew netns is cweawwy unsafe.
	 */
	ip6n->fb_tnw_dev->featuwes |= NETIF_F_NETNS_WOCAW;

	eww = ip6_fb_tnw_dev_init(ip6n->fb_tnw_dev);
	if (eww < 0)
		goto eww_wegistew;

	eww = wegistew_netdev(ip6n->fb_tnw_dev);
	if (eww < 0)
		goto eww_wegistew;

	t = netdev_pwiv(ip6n->fb_tnw_dev);

	stwcpy(t->pawms.name, ip6n->fb_tnw_dev->name);
	wetuwn 0;

eww_wegistew:
	fwee_netdev(ip6n->fb_tnw_dev);
eww_awwoc_dev:
	wetuwn eww;
}

static void __net_exit ip6_tnw_exit_batch_net(stwuct wist_head *net_wist)
{
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist)
		ip6_tnw_destwoy_tunnews(net, &wist);
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
}

static stwuct pewnet_opewations ip6_tnw_net_ops = {
	.init = ip6_tnw_init_net,
	.exit_batch = ip6_tnw_exit_batch_net,
	.id   = &ip6_tnw_net_id,
	.size = sizeof(stwuct ip6_tnw_net),
};

/**
 * ip6_tunnew_init - wegistew pwotocow and wesewve needed wesouwces
 *
 * Wetuwn: 0 on success
 **/

static int __init ip6_tunnew_init(void)
{
	int  eww;

	if (!ipv6_mod_enabwed())
		wetuwn -EOPNOTSUPP;

	eww = wegistew_pewnet_device(&ip6_tnw_net_ops);
	if (eww < 0)
		goto out_pewnet;

	eww = xfwm6_tunnew_wegistew(&ip4ip6_handwew, AF_INET);
	if (eww < 0) {
		pw_eww("%s: can't wegistew ip4ip6\n", __func__);
		goto out_ip4ip6;
	}

	eww = xfwm6_tunnew_wegistew(&ip6ip6_handwew, AF_INET6);
	if (eww < 0) {
		pw_eww("%s: can't wegistew ip6ip6\n", __func__);
		goto out_ip6ip6;
	}

	if (ip6_tnw_mpws_suppowted()) {
		eww = xfwm6_tunnew_wegistew(&mpwsip6_handwew, AF_MPWS);
		if (eww < 0) {
			pw_eww("%s: can't wegistew mpwsip6\n", __func__);
			goto out_mpwsip6;
		}
	}

	eww = wtnw_wink_wegistew(&ip6_wink_ops);
	if (eww < 0)
		goto wtnw_wink_faiwed;

	wetuwn 0;

wtnw_wink_faiwed:
	if (ip6_tnw_mpws_suppowted())
		xfwm6_tunnew_dewegistew(&mpwsip6_handwew, AF_MPWS);
out_mpwsip6:
	xfwm6_tunnew_dewegistew(&ip6ip6_handwew, AF_INET6);
out_ip6ip6:
	xfwm6_tunnew_dewegistew(&ip4ip6_handwew, AF_INET);
out_ip4ip6:
	unwegistew_pewnet_device(&ip6_tnw_net_ops);
out_pewnet:
	wetuwn eww;
}

/**
 * ip6_tunnew_cweanup - fwee wesouwces and unwegistew pwotocow
 **/

static void __exit ip6_tunnew_cweanup(void)
{
	wtnw_wink_unwegistew(&ip6_wink_ops);
	if (xfwm6_tunnew_dewegistew(&ip4ip6_handwew, AF_INET))
		pw_info("%s: can't dewegistew ip4ip6\n", __func__);

	if (xfwm6_tunnew_dewegistew(&ip6ip6_handwew, AF_INET6))
		pw_info("%s: can't dewegistew ip6ip6\n", __func__);

	if (ip6_tnw_mpws_suppowted() &&
	    xfwm6_tunnew_dewegistew(&mpwsip6_handwew, AF_MPWS))
		pw_info("%s: can't dewegistew mpwsip6\n", __func__);
	unwegistew_pewnet_device(&ip6_tnw_net_ops);
}

moduwe_init(ip6_tunnew_init);
moduwe_exit(ip6_tunnew_cweanup);
