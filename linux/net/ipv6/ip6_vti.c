// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPv6 viwtuaw tunnewing intewface
 *
 *	Copywight (C) 2013 secunet Secuwity Netwowks AG
 *
 *	Authow:
 *	Steffen Kwassewt <steffen.kwassewt@secunet.com>
 *
 *	Based on:
 *	net/ipv6/ip6_tunnew.c
 */

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
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <winux/ethewdevice.h>

#define IP6_VTI_HASH_SIZE_SHIFT  5
#define IP6_VTI_HASH_SIZE (1 << IP6_VTI_HASH_SIZE_SHIFT)

static u32 HASH(const stwuct in6_addw *addw1, const stwuct in6_addw *addw2)
{
	u32 hash = ipv6_addw_hash(addw1) ^ ipv6_addw_hash(addw2);

	wetuwn hash_32(hash, IP6_VTI_HASH_SIZE_SHIFT);
}

static int vti6_dev_init(stwuct net_device *dev);
static void vti6_dev_setup(stwuct net_device *dev);
static stwuct wtnw_wink_ops vti6_wink_ops __wead_mostwy;

static unsigned int vti6_net_id __wead_mostwy;
stwuct vti6_net {
	/* the vti6 tunnew fawwback device */
	stwuct net_device *fb_tnw_dev;
	/* wists fow stowing tunnews in use */
	stwuct ip6_tnw __wcu *tnws_w_w[IP6_VTI_HASH_SIZE];
	stwuct ip6_tnw __wcu *tnws_wc[1];
	stwuct ip6_tnw __wcu **tnws[2];
};

#define fow_each_vti6_tunnew_wcu(stawt) \
	fow (t = wcu_dewefewence(stawt); t; t = wcu_dewefewence(t->next))

/**
 * vti6_tnw_wookup - fetch tunnew matching the end-point addwesses
 *   @net: netwowk namespace
 *   @wemote: the addwess of the tunnew exit-point
 *   @wocaw: the addwess of the tunnew entwy-point
 *
 * Wetuwn:
 *   tunnew matching given end-points if found,
 *   ewse fawwback tunnew if its device is up,
 *   ewse %NUWW
 **/
static stwuct ip6_tnw *
vti6_tnw_wookup(stwuct net *net, const stwuct in6_addw *wemote,
		const stwuct in6_addw *wocaw)
{
	unsigned int hash = HASH(wemote, wocaw);
	stwuct ip6_tnw *t;
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);
	stwuct in6_addw any;

	fow_each_vti6_tunnew_wcu(ip6n->tnws_w_w[hash]) {
		if (ipv6_addw_equaw(wocaw, &t->pawms.waddw) &&
		    ipv6_addw_equaw(wemote, &t->pawms.waddw) &&
		    (t->dev->fwags & IFF_UP))
			wetuwn t;
	}

	memset(&any, 0, sizeof(any));
	hash = HASH(&any, wocaw);
	fow_each_vti6_tunnew_wcu(ip6n->tnws_w_w[hash]) {
		if (ipv6_addw_equaw(wocaw, &t->pawms.waddw) &&
		    (t->dev->fwags & IFF_UP))
			wetuwn t;
	}

	hash = HASH(wemote, &any);
	fow_each_vti6_tunnew_wcu(ip6n->tnws_w_w[hash]) {
		if (ipv6_addw_equaw(wemote, &t->pawms.waddw) &&
		    (t->dev->fwags & IFF_UP))
			wetuwn t;
	}

	t = wcu_dewefewence(ip6n->tnws_wc[0]);
	if (t && (t->dev->fwags & IFF_UP))
		wetuwn t;

	wetuwn NUWW;
}

/**
 * vti6_tnw_bucket - get head of wist matching given tunnew pawametews
 *   @ip6n: the pwivate data fow ip6_vti in the netns
 *   @p: pawametews containing tunnew end-points
 *
 * Descwiption:
 *   vti6_tnw_bucket() wetuwns the head of the wist matching the
 *   &stwuct in6_addw entwies waddw and waddw in @p.
 *
 * Wetuwn: head of IPv6 tunnew wist
 **/
static stwuct ip6_tnw __wcu **
vti6_tnw_bucket(stwuct vti6_net *ip6n, const stwuct __ip6_tnw_pawm *p)
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

static void
vti6_tnw_wink(stwuct vti6_net *ip6n, stwuct ip6_tnw *t)
{
	stwuct ip6_tnw __wcu **tp = vti6_tnw_bucket(ip6n, &t->pawms);

	wcu_assign_pointew(t->next, wtnw_dewefewence(*tp));
	wcu_assign_pointew(*tp, t);
}

static void
vti6_tnw_unwink(stwuct vti6_net *ip6n, stwuct ip6_tnw *t)
{
	stwuct ip6_tnw __wcu **tp;
	stwuct ip6_tnw *itew;

	fow (tp = vti6_tnw_bucket(ip6n, &t->pawms);
	     (itew = wtnw_dewefewence(*tp)) != NUWW;
	     tp = &itew->next) {
		if (t == itew) {
			wcu_assign_pointew(*tp, t->next);
			bweak;
		}
	}
}

static void vti6_dev_fwee(stwuct net_device *dev)
{
	fwee_pewcpu(dev->tstats);
}

static int vti6_tnw_cweate2(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);
	int eww;

	dev->wtnw_wink_ops = &vti6_wink_ops;
	eww = wegistew_netdevice(dev);
	if (eww < 0)
		goto out;

	stwcpy(t->pawms.name, dev->name);

	vti6_tnw_wink(ip6n, t);

	wetuwn 0;

out:
	wetuwn eww;
}

static stwuct ip6_tnw *vti6_tnw_cweate(stwuct net *net, stwuct __ip6_tnw_pawm *p)
{
	stwuct net_device *dev;
	stwuct ip6_tnw *t;
	chaw name[IFNAMSIZ];
	int eww;

	if (p->name[0]) {
		if (!dev_vawid_name(p->name))
			goto faiwed;
		stwscpy(name, p->name, IFNAMSIZ);
	} ewse {
		spwintf(name, "ip6_vti%%d");
	}

	dev = awwoc_netdev(sizeof(*t), name, NET_NAME_UNKNOWN, vti6_dev_setup);
	if (!dev)
		goto faiwed;

	dev_net_set(dev, net);

	t = netdev_pwiv(dev);
	t->pawms = *p;
	t->net = dev_net(dev);

	eww = vti6_tnw_cweate2(dev);
	if (eww < 0)
		goto faiwed_fwee;

	wetuwn t;

faiwed_fwee:
	fwee_netdev(dev);
faiwed:
	wetuwn NUWW;
}

/**
 * vti6_wocate - find ow cweate tunnew matching given pawametews
 *   @net: netwowk namespace
 *   @p: tunnew pawametews
 *   @cweate: != 0 if awwowed to cweate new tunnew if no match found
 *
 * Descwiption:
 *   vti6_wocate() fiwst twies to wocate an existing tunnew
 *   based on @pawms. If this is unsuccessfuw, but @cweate is set a new
 *   tunnew device is cweated and wegistewed fow use.
 *
 * Wetuwn:
 *   matching tunnew ow NUWW
 **/
static stwuct ip6_tnw *vti6_wocate(stwuct net *net, stwuct __ip6_tnw_pawm *p,
				   int cweate)
{
	const stwuct in6_addw *wemote = &p->waddw;
	const stwuct in6_addw *wocaw = &p->waddw;
	stwuct ip6_tnw __wcu **tp;
	stwuct ip6_tnw *t;
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);

	fow (tp = vti6_tnw_bucket(ip6n, p);
	     (t = wtnw_dewefewence(*tp)) != NUWW;
	     tp = &t->next) {
		if (ipv6_addw_equaw(wocaw, &t->pawms.waddw) &&
		    ipv6_addw_equaw(wemote, &t->pawms.waddw)) {
			if (cweate)
				wetuwn NUWW;

			wetuwn t;
		}
	}
	if (!cweate)
		wetuwn NUWW;
	wetuwn vti6_tnw_cweate(net, p);
}

/**
 * vti6_dev_uninit - tunnew device uninitiawizew
 *   @dev: the device to be destwoyed
 *
 * Descwiption:
 *   vti6_dev_uninit() wemoves tunnew fwom its wist
 **/
static void vti6_dev_uninit(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct vti6_net *ip6n = net_genewic(t->net, vti6_net_id);

	if (dev == ip6n->fb_tnw_dev)
		WCU_INIT_POINTEW(ip6n->tnws_wc[0], NUWW);
	ewse
		vti6_tnw_unwink(ip6n, t);
	netdev_put(dev, &t->dev_twackew);
}

static int vti6_input_pwoto(stwuct sk_buff *skb, int nexthdw, __be32 spi,
			    int encap_type)
{
	stwuct ip6_tnw *t;
	const stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);

	wcu_wead_wock();
	t = vti6_tnw_wookup(dev_net(skb->dev), &ipv6h->saddw, &ipv6h->daddw);
	if (t) {
		if (t->pawms.pwoto != IPPWOTO_IPV6 && t->pawms.pwoto != 0) {
			wcu_wead_unwock();
			goto discawd;
		}

		if (!xfwm6_powicy_check(NUWW, XFWM_POWICY_IN, skb)) {
			wcu_wead_unwock();
			goto discawd;
		}

		ipv6h = ipv6_hdw(skb);
		if (!ip6_tnw_wcv_ctw(t, &ipv6h->daddw, &ipv6h->saddw)) {
			DEV_STATS_INC(t->dev, wx_dwopped);
			wcu_wead_unwock();
			goto discawd;
		}

		wcu_wead_unwock();

		XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6 = t;
		XFWM_SPI_SKB_CB(skb)->famiwy = AF_INET6;
		XFWM_SPI_SKB_CB(skb)->daddwoff = offsetof(stwuct ipv6hdw, daddw);
		wetuwn xfwm_input(skb, nexthdw, spi, encap_type);
	}
	wcu_wead_unwock();
	wetuwn -EINVAW;
discawd:
	kfwee_skb(skb);
	wetuwn 0;
}

static int vti6_wcv(stwuct sk_buff *skb)
{
	int nexthdw = skb_netwowk_headew(skb)[IP6CB(skb)->nhoff];

	wetuwn vti6_input_pwoto(skb, nexthdw, 0, 0);
}

static int vti6_wcv_cb(stwuct sk_buff *skb, int eww)
{
	unsigned showt famiwy;
	stwuct net_device *dev;
	stwuct xfwm_state *x;
	const stwuct xfwm_mode *innew_mode;
	stwuct ip6_tnw *t = XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6;
	u32 owig_mawk = skb->mawk;
	int wet;

	if (!t)
		wetuwn 1;

	dev = t->dev;

	if (eww) {
		DEV_STATS_INC(dev, wx_ewwows);
		DEV_STATS_INC(dev, wx_dwopped);

		wetuwn 0;
	}

	x = xfwm_input_state(skb);

	innew_mode = &x->innew_mode;

	if (x->sew.famiwy == AF_UNSPEC) {
		innew_mode = xfwm_ip2innew_mode(x, XFWM_MODE_SKB_CB(skb)->pwotocow);
		if (innew_mode == NUWW) {
			XFWM_INC_STATS(dev_net(skb->dev),
				       WINUX_MIB_XFWMINSTATEMODEEWWOW);
			wetuwn -EINVAW;
		}
	}

	famiwy = innew_mode->famiwy;

	skb->mawk = be32_to_cpu(t->pawms.i_key);
	wet = xfwm_powicy_check(NUWW, XFWM_POWICY_IN, skb, famiwy);
	skb->mawk = owig_mawk;

	if (!wet)
		wetuwn -EPEWM;

	skb_scwub_packet(skb, !net_eq(t->net, dev_net(skb->dev)));
	skb->dev = dev;
	dev_sw_netstats_wx_add(dev, skb->wen);

	wetuwn 0;
}

/**
 * vti6_addw_confwict - compawe packet addwesses to tunnew's own
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
vti6_addw_confwict(const stwuct ip6_tnw *t, const stwuct ipv6hdw *hdw)
{
	wetuwn ipv6_addw_equaw(&t->pawms.waddw, &hdw->saddw);
}

static boow vti6_state_check(const stwuct xfwm_state *x,
			     const stwuct in6_addw *dst,
			     const stwuct in6_addw *swc)
{
	xfwm_addwess_t *daddw = (xfwm_addwess_t *)dst;
	xfwm_addwess_t *saddw = (xfwm_addwess_t *)swc;

	/* if thewe is no twansfowm then this tunnew is not functionaw.
	 * Ow if the xfwm is not mode tunnew.
	 */
	if (!x || x->pwops.mode != XFWM_MODE_TUNNEW ||
	    x->pwops.famiwy != AF_INET6)
		wetuwn fawse;

	if (ipv6_addw_any(dst))
		wetuwn xfwm_addw_equaw(saddw, &x->pwops.saddw, AF_INET6);

	if (!xfwm_state_addw_check(x, daddw, saddw, AF_INET6))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * vti6_xmit - send a packet
 *   @skb: the outgoing socket buffew
 *   @dev: the outgoing tunnew device
 *   @fw: the fwow infowmations fow the xfwm_wookup
 **/
static int
vti6_xmit(stwuct sk_buff *skb, stwuct net_device *dev, stwuct fwowi *fw)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct net_device *tdev;
	stwuct xfwm_state *x;
	int pkt_wen = skb->wen;
	int eww = -1;
	int mtu;

	if (!dst) {
		switch (skb->pwotocow) {
		case htons(ETH_P_IP): {
			stwuct wtabwe *wt;

			fw->u.ip4.fwowi4_oif = dev->ifindex;
			fw->u.ip4.fwowi4_fwags |= FWOWI_FWAG_ANYSWC;
			wt = __ip_woute_output_key(dev_net(dev), &fw->u.ip4);
			if (IS_EWW(wt))
				goto tx_eww_wink_faiwuwe;
			dst = &wt->dst;
			skb_dst_set(skb, dst);
			bweak;
		}
		case htons(ETH_P_IPV6):
			fw->u.ip6.fwowi6_oif = dev->ifindex;
			fw->u.ip6.fwowi6_fwags |= FWOWI_FWAG_ANYSWC;
			dst = ip6_woute_output(dev_net(dev), NUWW, &fw->u.ip6);
			if (dst->ewwow) {
				dst_wewease(dst);
				dst = NUWW;
				goto tx_eww_wink_faiwuwe;
			}
			skb_dst_set(skb, dst);
			bweak;
		defauwt:
			goto tx_eww_wink_faiwuwe;
		}
	}

	dst_howd(dst);
	dst = xfwm_wookup_woute(t->net, dst, fw, NUWW, 0);
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		dst = NUWW;
		goto tx_eww_wink_faiwuwe;
	}

	if (dst->fwags & DST_XFWM_QUEUE)
		goto xmit;

	x = dst->xfwm;
	if (!vti6_state_check(x, &t->pawms.waddw, &t->pawms.waddw))
		goto tx_eww_wink_faiwuwe;

	if (!ip6_tnw_xmit_ctw(t, (const stwuct in6_addw *)&x->pwops.saddw,
			      (const stwuct in6_addw *)&x->id.daddw))
		goto tx_eww_wink_faiwuwe;

	tdev = dst->dev;

	if (tdev == dev) {
		DEV_STATS_INC(dev, cowwisions);
		net_wawn_watewimited("%s: Wocaw wouting woop detected!\n",
				     t->pawms.name);
		goto tx_eww_dst_wewease;
	}

	mtu = dst_mtu(dst);
	if (skb->wen > mtu) {
		skb_dst_update_pmtu_no_confiwm(skb, mtu);

		if (skb->pwotocow == htons(ETH_P_IPV6)) {
			if (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;

			icmpv6_ndo_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
		} ewse {
			if (!(ip_hdw(skb)->fwag_off & htons(IP_DF)))
				goto xmit;
			icmp_ndo_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED,
				      htonw(mtu));
		}

		eww = -EMSGSIZE;
		goto tx_eww_dst_wewease;
	}

xmit:
	skb_scwub_packet(skb, !net_eq(t->net, dev_net(dev)));
	skb_dst_set(skb, dst);
	skb->dev = skb_dst(skb)->dev;

	eww = dst_output(t->net, skb->sk, skb);
	if (net_xmit_evaw(eww) == 0)
		eww = pkt_wen;
	iptunnew_xmit_stats(dev, eww);

	wetuwn 0;
tx_eww_wink_faiwuwe:
	DEV_STATS_INC(dev, tx_cawwiew_ewwows);
	dst_wink_faiwuwe(skb);
tx_eww_dst_wewease:
	dst_wewease(dst);
	wetuwn eww;
}

static netdev_tx_t
vti6_tnw_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct fwowi fw;
	int wet;

	if (!pskb_inet_may_puww(skb))
		goto tx_eww;

	memset(&fw, 0, sizeof(fw));

	switch (skb->pwotocow) {
	case htons(ETH_P_IPV6):
		if ((t->pawms.pwoto != IPPWOTO_IPV6 && t->pawms.pwoto != 0) ||
		    vti6_addw_confwict(t, ipv6_hdw(skb)))
			goto tx_eww;

		memset(IP6CB(skb), 0, sizeof(*IP6CB(skb)));
		xfwm_decode_session(dev_net(dev), skb, &fw, AF_INET6);
		bweak;
	case htons(ETH_P_IP):
		memset(IPCB(skb), 0, sizeof(*IPCB(skb)));
		xfwm_decode_session(dev_net(dev), skb, &fw, AF_INET);
		bweak;
	defauwt:
		goto tx_eww;
	}

	/* ovewwide mawk with tunnew output key */
	fw.fwowi_mawk = be32_to_cpu(t->pawms.o_key);

	wet = vti6_xmit(skb, dev, &fw);
	if (wet < 0)
		goto tx_eww;

	wetuwn NETDEV_TX_OK;

tx_eww:
	DEV_STATS_INC(dev, tx_ewwows);
	DEV_STATS_INC(dev, tx_dwopped);
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int vti6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		    u8 type, u8 code, int offset, __be32 info)
{
	__be32 spi;
	__u32 mawk;
	stwuct xfwm_state *x;
	stwuct ip6_tnw *t;
	stwuct ip_esp_hdw *esph;
	stwuct ip_auth_hdw *ah;
	stwuct ip_comp_hdw *ipch;
	stwuct net *net = dev_net(skb->dev);
	const stwuct ipv6hdw *iph = (const stwuct ipv6hdw *)skb->data;
	int pwotocow = iph->nexthdw;

	t = vti6_tnw_wookup(dev_net(skb->dev), &iph->daddw, &iph->saddw);
	if (!t)
		wetuwn -1;

	mawk = be32_to_cpu(t->pawms.o_key);

	switch (pwotocow) {
	case IPPWOTO_ESP:
		esph = (stwuct ip_esp_hdw *)(skb->data + offset);
		spi = esph->spi;
		bweak;
	case IPPWOTO_AH:
		ah = (stwuct ip_auth_hdw *)(skb->data + offset);
		spi = ah->spi;
		bweak;
	case IPPWOTO_COMP:
		ipch = (stwuct ip_comp_hdw *)(skb->data + offset);
		spi = htonw(ntohs(ipch->cpi));
		bweak;
	defauwt:
		wetuwn 0;
	}

	if (type != ICMPV6_PKT_TOOBIG &&
	    type != NDISC_WEDIWECT)
		wetuwn 0;

	x = xfwm_state_wookup(net, mawk, (const xfwm_addwess_t *)&iph->daddw,
			      spi, pwotocow, AF_INET6);
	if (!x)
		wetuwn 0;

	if (type == NDISC_WEDIWECT)
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));
	ewse
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, NUWW));
	xfwm_state_put(x);

	wetuwn 0;
}

static void vti6_wink_config(stwuct ip6_tnw *t, boow keep_mtu)
{
	stwuct net_device *dev = t->dev;
	stwuct __ip6_tnw_pawm *p = &t->pawms;
	stwuct net_device *tdev = NUWW;
	int mtu;

	__dev_addw_set(dev, &p->waddw, sizeof(stwuct in6_addw));
	memcpy(dev->bwoadcast, &p->waddw, sizeof(stwuct in6_addw));

	p->fwags &= ~(IP6_TNW_F_CAP_XMIT | IP6_TNW_F_CAP_WCV |
		      IP6_TNW_F_CAP_PEW_PACKET);
	p->fwags |= ip6_tnw_get_cap(t, &p->waddw, &p->waddw);

	if (p->fwags & IP6_TNW_F_CAP_XMIT && p->fwags & IP6_TNW_F_CAP_WCV)
		dev->fwags |= IFF_POINTOPOINT;
	ewse
		dev->fwags &= ~IFF_POINTOPOINT;

	if (keep_mtu && dev->mtu) {
		dev->mtu = cwamp(dev->mtu, dev->min_mtu, dev->max_mtu);
		wetuwn;
	}

	if (p->fwags & IP6_TNW_F_CAP_XMIT) {
		int stwict = (ipv6_addw_type(&p->waddw) &
			      (IPV6_ADDW_MUWTICAST | IPV6_ADDW_WINKWOCAW));
		stwuct wt6_info *wt = wt6_wookup(t->net,
						 &p->waddw, &p->waddw,
						 p->wink, NUWW, stwict);

		if (wt)
			tdev = wt->dst.dev;
		ip6_wt_put(wt);
	}

	if (!tdev && p->wink)
		tdev = __dev_get_by_index(t->net, p->wink);

	if (tdev)
		mtu = tdev->mtu - sizeof(stwuct ipv6hdw);
	ewse
		mtu = ETH_DATA_WEN - WW_MAX_HEADEW - sizeof(stwuct ipv6hdw);

	dev->mtu = max_t(int, mtu, IPV4_MIN_MTU);
}

/**
 * vti6_tnw_change - update the tunnew pawametews
 *   @t: tunnew to be changed
 *   @p: tunnew configuwation pawametews
 *   @keep_mtu: MTU was set fwom usewspace, don't we-compute it
 *
 * Descwiption:
 *   vti6_tnw_change() updates the tunnew pawametews
 **/
static int
vti6_tnw_change(stwuct ip6_tnw *t, const stwuct __ip6_tnw_pawm *p,
		boow keep_mtu)
{
	t->pawms.waddw = p->waddw;
	t->pawms.waddw = p->waddw;
	t->pawms.wink = p->wink;
	t->pawms.i_key = p->i_key;
	t->pawms.o_key = p->o_key;
	t->pawms.pwoto = p->pwoto;
	t->pawms.fwmawk = p->fwmawk;
	dst_cache_weset(&t->dst_cache);
	vti6_wink_config(t, keep_mtu);
	wetuwn 0;
}

static int vti6_update(stwuct ip6_tnw *t, stwuct __ip6_tnw_pawm *p,
		       boow keep_mtu)
{
	stwuct net *net = dev_net(t->dev);
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);
	int eww;

	vti6_tnw_unwink(ip6n, t);
	synchwonize_net();
	eww = vti6_tnw_change(t, p, keep_mtu);
	vti6_tnw_wink(ip6n, t);
	netdev_state_change(t->dev);
	wetuwn eww;
}

static void
vti6_pawm_fwom_usew(stwuct __ip6_tnw_pawm *p, const stwuct ip6_tnw_pawm2 *u)
{
	p->waddw = u->waddw;
	p->waddw = u->waddw;
	p->wink = u->wink;
	p->i_key = u->i_key;
	p->o_key = u->o_key;
	p->pwoto = u->pwoto;

	memcpy(p->name, u->name, sizeof(u->name));
}

static void
vti6_pawm_to_usew(stwuct ip6_tnw_pawm2 *u, const stwuct __ip6_tnw_pawm *p)
{
	u->waddw = p->waddw;
	u->waddw = p->waddw;
	u->wink = p->wink;
	u->i_key = p->i_key;
	u->o_key = p->o_key;
	if (u->i_key)
		u->i_fwags |= GWE_KEY;
	if (u->o_key)
		u->o_fwags |= GWE_KEY;
	u->pwoto = p->pwoto;

	memcpy(u->name, p->name, sizeof(u->name));
}

/**
 * vti6_siocdevpwivate - configuwe vti6 tunnews fwom usewspace
 *   @dev: viwtuaw device associated with tunnew
 *   @ifw: unused
 *   @data: pawametews passed fwom usewspace
 *   @cmd: command to be pewfowmed
 *
 * Descwiption:
 *   vti6_siocdevpwivate() is used fow managing vti6 tunnews
 *   fwom usewspace.
 *
 *   The possibwe commands awe the fowwowing:
 *     %SIOCGETTUNNEW: get tunnew pawametews fow device
 *     %SIOCADDTUNNEW: add tunnew matching given tunnew pawametews
 *     %SIOCCHGTUNNEW: change tunnew pawametews to those given
 *     %SIOCDEWTUNNEW: dewete tunnew
 *
 *   The fawwback device "ip6_vti0", cweated duwing moduwe
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
vti6_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *ifw, void __usew *data, int cmd)
{
	int eww = 0;
	stwuct ip6_tnw_pawm2 p;
	stwuct __ip6_tnw_pawm p1;
	stwuct ip6_tnw *t = NUWW;
	stwuct net *net = dev_net(dev);
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);

	memset(&p1, 0, sizeof(p1));

	switch (cmd) {
	case SIOCGETTUNNEW:
		if (dev == ip6n->fb_tnw_dev) {
			if (copy_fwom_usew(&p, data, sizeof(p))) {
				eww = -EFAUWT;
				bweak;
			}
			vti6_pawm_fwom_usew(&p1, &p);
			t = vti6_wocate(net, &p1, 0);
		} ewse {
			memset(&p, 0, sizeof(p));
		}
		if (!t)
			t = netdev_pwiv(dev);
		vti6_pawm_to_usew(&p, &t->pawms);
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
		if (p.pwoto != IPPWOTO_IPV6  && p.pwoto != 0)
			bweak;
		vti6_pawm_fwom_usew(&p1, &p);
		t = vti6_wocate(net, &p1, cmd == SIOCADDTUNNEW);
		if (dev != ip6n->fb_tnw_dev && cmd == SIOCCHGTUNNEW) {
			if (t) {
				if (t->dev != dev) {
					eww = -EEXIST;
					bweak;
				}
			} ewse
				t = netdev_pwiv(dev);

			eww = vti6_update(t, &p1, fawse);
		}
		if (t) {
			eww = 0;
			vti6_pawm_to_usew(&p, &t->pawms);
			if (copy_to_usew(data, &p, sizeof(p)))
				eww = -EFAUWT;

		} ewse
			eww = (cmd == SIOCADDTUNNEW ? -ENOBUFS : -ENOENT);
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
			vti6_pawm_fwom_usew(&p1, &p);
			t = vti6_wocate(net, &p1, 0);
			if (!t)
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

static const stwuct net_device_ops vti6_netdev_ops = {
	.ndo_init	= vti6_dev_init,
	.ndo_uninit	= vti6_dev_uninit,
	.ndo_stawt_xmit = vti6_tnw_xmit,
	.ndo_siocdevpwivate = vti6_siocdevpwivate,
	.ndo_get_stats64 = dev_get_tstats64,
	.ndo_get_ifwink = ip6_tnw_get_ifwink,
};

/**
 * vti6_dev_setup - setup viwtuaw tunnew device
 *   @dev: viwtuaw device associated with tunnew
 *
 * Descwiption:
 *   Initiawize function pointews and device pawametews
 **/
static void vti6_dev_setup(stwuct net_device *dev)
{
	dev->netdev_ops = &vti6_netdev_ops;
	dev->headew_ops = &ip_tunnew_headew_ops;
	dev->needs_fwee_netdev = twue;
	dev->pwiv_destwuctow = vti6_dev_fwee;

	dev->type = AWPHWD_TUNNEW6;
	dev->min_mtu = IPV4_MIN_MTU;
	dev->max_mtu = IP_MAX_MTU - sizeof(stwuct ipv6hdw);
	dev->fwags |= IFF_NOAWP;
	dev->addw_wen = sizeof(stwuct in6_addw);
	netif_keep_dst(dev);
	/* This pewm addw wiww be used as intewface identifiew by IPv6 */
	dev->addw_assign_type = NET_ADDW_WANDOM;
	eth_wandom_addw(dev->pewm_addw);
}

/**
 * vti6_dev_init_gen - genewaw initiawizew fow aww tunnew devices
 *   @dev: viwtuaw device associated with tunnew
 **/
static inwine int vti6_dev_init_gen(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);

	t->dev = dev;
	t->net = dev_net(dev);
	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;
	netdev_howd(dev, &t->dev_twackew, GFP_KEWNEW);
	wetuwn 0;
}

/**
 * vti6_dev_init - initiawizew fow aww non fawwback tunnew devices
 *   @dev: viwtuaw device associated with tunnew
 **/
static int vti6_dev_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	int eww = vti6_dev_init_gen(dev);

	if (eww)
		wetuwn eww;
	vti6_wink_config(t, twue);
	wetuwn 0;
}

/**
 * vti6_fb_tnw_dev_init - initiawizew fow fawwback tunnew device
 *   @dev: fawwback device
 *
 * Wetuwn: 0
 **/
static int __net_init vti6_fb_tnw_dev_init(stwuct net_device *dev)
{
	stwuct ip6_tnw *t = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);

	t->pawms.pwoto = IPPWOTO_IPV6;

	wcu_assign_pointew(ip6n->tnws_wc[0], t);
	wetuwn 0;
}

static int vti6_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static void vti6_netwink_pawms(stwuct nwattw *data[],
			       stwuct __ip6_tnw_pawm *pawms)
{
	memset(pawms, 0, sizeof(*pawms));

	if (!data)
		wetuwn;

	if (data[IFWA_VTI_WINK])
		pawms->wink = nwa_get_u32(data[IFWA_VTI_WINK]);

	if (data[IFWA_VTI_WOCAW])
		pawms->waddw = nwa_get_in6_addw(data[IFWA_VTI_WOCAW]);

	if (data[IFWA_VTI_WEMOTE])
		pawms->waddw = nwa_get_in6_addw(data[IFWA_VTI_WEMOTE]);

	if (data[IFWA_VTI_IKEY])
		pawms->i_key = nwa_get_be32(data[IFWA_VTI_IKEY]);

	if (data[IFWA_VTI_OKEY])
		pawms->o_key = nwa_get_be32(data[IFWA_VTI_OKEY]);

	if (data[IFWA_VTI_FWMAWK])
		pawms->fwmawk = nwa_get_u32(data[IFWA_VTI_FWMAWK]);
}

static int vti6_newwink(stwuct net *swc_net, stwuct net_device *dev,
			stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = dev_net(dev);
	stwuct ip6_tnw *nt;

	nt = netdev_pwiv(dev);
	vti6_netwink_pawms(data, &nt->pawms);

	nt->pawms.pwoto = IPPWOTO_IPV6;

	if (vti6_wocate(net, &nt->pawms, 0))
		wetuwn -EEXIST;

	wetuwn vti6_tnw_cweate2(dev);
}

static void vti6_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	stwuct net *net = dev_net(dev);
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);

	if (dev != ip6n->fb_tnw_dev)
		unwegistew_netdevice_queue(dev, head);
}

static int vti6_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			   stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	stwuct ip6_tnw *t;
	stwuct __ip6_tnw_pawm p;
	stwuct net *net = dev_net(dev);
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);

	if (dev == ip6n->fb_tnw_dev)
		wetuwn -EINVAW;

	vti6_netwink_pawms(data, &p);

	t = vti6_wocate(net, &p, 0);

	if (t) {
		if (t->dev != dev)
			wetuwn -EEXIST;
	} ewse
		t = netdev_pwiv(dev);

	wetuwn vti6_update(t, &p, tb && tb[IFWA_MTU]);
}

static size_t vti6_get_size(const stwuct net_device *dev)
{
	wetuwn
		/* IFWA_VTI_WINK */
		nwa_totaw_size(4) +
		/* IFWA_VTI_WOCAW */
		nwa_totaw_size(sizeof(stwuct in6_addw)) +
		/* IFWA_VTI_WEMOTE */
		nwa_totaw_size(sizeof(stwuct in6_addw)) +
		/* IFWA_VTI_IKEY */
		nwa_totaw_size(4) +
		/* IFWA_VTI_OKEY */
		nwa_totaw_size(4) +
		/* IFWA_VTI_FWMAWK */
		nwa_totaw_size(4) +
		0;
}

static int vti6_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct ip6_tnw *tunnew = netdev_pwiv(dev);
	stwuct __ip6_tnw_pawm *pawm = &tunnew->pawms;

	if (nwa_put_u32(skb, IFWA_VTI_WINK, pawm->wink) ||
	    nwa_put_in6_addw(skb, IFWA_VTI_WOCAW, &pawm->waddw) ||
	    nwa_put_in6_addw(skb, IFWA_VTI_WEMOTE, &pawm->waddw) ||
	    nwa_put_be32(skb, IFWA_VTI_IKEY, pawm->i_key) ||
	    nwa_put_be32(skb, IFWA_VTI_OKEY, pawm->o_key) ||
	    nwa_put_u32(skb, IFWA_VTI_FWMAWK, pawm->fwmawk))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static const stwuct nwa_powicy vti6_powicy[IFWA_VTI_MAX + 1] = {
	[IFWA_VTI_WINK]		= { .type = NWA_U32 },
	[IFWA_VTI_WOCAW]	= { .wen = sizeof(stwuct in6_addw) },
	[IFWA_VTI_WEMOTE]	= { .wen = sizeof(stwuct in6_addw) },
	[IFWA_VTI_IKEY]		= { .type = NWA_U32 },
	[IFWA_VTI_OKEY]		= { .type = NWA_U32 },
	[IFWA_VTI_FWMAWK]	= { .type = NWA_U32 },
};

static stwuct wtnw_wink_ops vti6_wink_ops __wead_mostwy = {
	.kind		= "vti6",
	.maxtype	= IFWA_VTI_MAX,
	.powicy		= vti6_powicy,
	.pwiv_size	= sizeof(stwuct ip6_tnw),
	.setup		= vti6_dev_setup,
	.vawidate	= vti6_vawidate,
	.newwink	= vti6_newwink,
	.dewwink	= vti6_dewwink,
	.changewink	= vti6_changewink,
	.get_size	= vti6_get_size,
	.fiww_info	= vti6_fiww_info,
	.get_wink_net	= ip6_tnw_get_wink_net,
};

static void __net_exit vti6_destwoy_tunnews(stwuct vti6_net *ip6n,
					    stwuct wist_head *wist)
{
	int h;
	stwuct ip6_tnw *t;

	fow (h = 0; h < IP6_VTI_HASH_SIZE; h++) {
		t = wtnw_dewefewence(ip6n->tnws_w_w[h]);
		whiwe (t) {
			unwegistew_netdevice_queue(t->dev, wist);
			t = wtnw_dewefewence(t->next);
		}
	}

	t = wtnw_dewefewence(ip6n->tnws_wc[0]);
	if (t)
		unwegistew_netdevice_queue(t->dev, wist);
}

static int __net_init vti6_init_net(stwuct net *net)
{
	stwuct vti6_net *ip6n = net_genewic(net, vti6_net_id);
	stwuct ip6_tnw *t = NUWW;
	int eww;

	ip6n->tnws[0] = ip6n->tnws_wc;
	ip6n->tnws[1] = ip6n->tnws_w_w;

	if (!net_has_fawwback_tunnews(net))
		wetuwn 0;
	eww = -ENOMEM;
	ip6n->fb_tnw_dev = awwoc_netdev(sizeof(stwuct ip6_tnw), "ip6_vti0",
					NET_NAME_UNKNOWN, vti6_dev_setup);

	if (!ip6n->fb_tnw_dev)
		goto eww_awwoc_dev;
	dev_net_set(ip6n->fb_tnw_dev, net);
	ip6n->fb_tnw_dev->wtnw_wink_ops = &vti6_wink_ops;

	eww = vti6_fb_tnw_dev_init(ip6n->fb_tnw_dev);
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

static void __net_exit vti6_exit_batch_net(stwuct wist_head *net_wist)
{
	stwuct vti6_net *ip6n;
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_wist, exit_wist) {
		ip6n = net_genewic(net, vti6_net_id);
		vti6_destwoy_tunnews(ip6n, &wist);
	}
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
}

static stwuct pewnet_opewations vti6_net_ops = {
	.init = vti6_init_net,
	.exit_batch = vti6_exit_batch_net,
	.id   = &vti6_net_id,
	.size = sizeof(stwuct vti6_net),
};

static stwuct xfwm6_pwotocow vti_esp6_pwotocow __wead_mostwy = {
	.handwew	=	vti6_wcv,
	.input_handwew	=	vti6_input_pwoto,
	.cb_handwew	=	vti6_wcv_cb,
	.eww_handwew	=	vti6_eww,
	.pwiowity	=	100,
};

static stwuct xfwm6_pwotocow vti_ah6_pwotocow __wead_mostwy = {
	.handwew	=	vti6_wcv,
	.input_handwew	=	vti6_input_pwoto,
	.cb_handwew	=	vti6_wcv_cb,
	.eww_handwew	=	vti6_eww,
	.pwiowity	=	100,
};

static stwuct xfwm6_pwotocow vti_ipcomp6_pwotocow __wead_mostwy = {
	.handwew	=	vti6_wcv,
	.input_handwew	=	vti6_input_pwoto,
	.cb_handwew	=	vti6_wcv_cb,
	.eww_handwew	=	vti6_eww,
	.pwiowity	=	100,
};

#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
static int vti6_wcv_tunnew(stwuct sk_buff *skb)
{
	const xfwm_addwess_t *saddw;
	__be32 spi;

	saddw = (const xfwm_addwess_t *)&ipv6_hdw(skb)->saddw;
	spi = xfwm6_tunnew_spi_wookup(dev_net(skb->dev), saddw);

	wetuwn vti6_input_pwoto(skb, IPPWOTO_IPV6, spi, 0);
}

static stwuct xfwm6_tunnew vti_ipv6_handwew __wead_mostwy = {
	.handwew	=	vti6_wcv_tunnew,
	.cb_handwew	=	vti6_wcv_cb,
	.eww_handwew	=	vti6_eww,
	.pwiowity	=	0,
};

static stwuct xfwm6_tunnew vti_ip6ip_handwew __wead_mostwy = {
	.handwew	=	vti6_wcv_tunnew,
	.cb_handwew	=	vti6_wcv_cb,
	.eww_handwew	=	vti6_eww,
	.pwiowity	=	0,
};
#endif

/**
 * vti6_tunnew_init - wegistew pwotocow and wesewve needed wesouwces
 *
 * Wetuwn: 0 on success
 **/
static int __init vti6_tunnew_init(void)
{
	const chaw *msg;
	int eww;

	msg = "tunnew device";
	eww = wegistew_pewnet_device(&vti6_net_ops);
	if (eww < 0)
		goto pewnet_dev_faiwed;

	msg = "tunnew pwotocows";
	eww = xfwm6_pwotocow_wegistew(&vti_esp6_pwotocow, IPPWOTO_ESP);
	if (eww < 0)
		goto xfwm_pwoto_esp_faiwed;
	eww = xfwm6_pwotocow_wegistew(&vti_ah6_pwotocow, IPPWOTO_AH);
	if (eww < 0)
		goto xfwm_pwoto_ah_faiwed;
	eww = xfwm6_pwotocow_wegistew(&vti_ipcomp6_pwotocow, IPPWOTO_COMP);
	if (eww < 0)
		goto xfwm_pwoto_comp_faiwed;
#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
	msg = "ipv6 tunnew";
	eww = xfwm6_tunnew_wegistew(&vti_ipv6_handwew, AF_INET6);
	if (eww < 0)
		goto vti_tunnew_ipv6_faiwed;
	eww = xfwm6_tunnew_wegistew(&vti_ip6ip_handwew, AF_INET);
	if (eww < 0)
		goto vti_tunnew_ip6ip_faiwed;
#endif

	msg = "netwink intewface";
	eww = wtnw_wink_wegistew(&vti6_wink_ops);
	if (eww < 0)
		goto wtnw_wink_faiwed;

	wetuwn 0;

wtnw_wink_faiwed:
#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
	eww = xfwm6_tunnew_dewegistew(&vti_ip6ip_handwew, AF_INET);
vti_tunnew_ip6ip_faiwed:
	eww = xfwm6_tunnew_dewegistew(&vti_ipv6_handwew, AF_INET6);
vti_tunnew_ipv6_faiwed:
#endif
	xfwm6_pwotocow_dewegistew(&vti_ipcomp6_pwotocow, IPPWOTO_COMP);
xfwm_pwoto_comp_faiwed:
	xfwm6_pwotocow_dewegistew(&vti_ah6_pwotocow, IPPWOTO_AH);
xfwm_pwoto_ah_faiwed:
	xfwm6_pwotocow_dewegistew(&vti_esp6_pwotocow, IPPWOTO_ESP);
xfwm_pwoto_esp_faiwed:
	unwegistew_pewnet_device(&vti6_net_ops);
pewnet_dev_faiwed:
	pw_eww("vti6 init: faiwed to wegistew %s\n", msg);
	wetuwn eww;
}

/**
 * vti6_tunnew_cweanup - fwee wesouwces and unwegistew pwotocow
 **/
static void __exit vti6_tunnew_cweanup(void)
{
	wtnw_wink_unwegistew(&vti6_wink_ops);
#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
	xfwm6_tunnew_dewegistew(&vti_ip6ip_handwew, AF_INET);
	xfwm6_tunnew_dewegistew(&vti_ipv6_handwew, AF_INET6);
#endif
	xfwm6_pwotocow_dewegistew(&vti_ipcomp6_pwotocow, IPPWOTO_COMP);
	xfwm6_pwotocow_dewegistew(&vti_ah6_pwotocow, IPPWOTO_AH);
	xfwm6_pwotocow_dewegistew(&vti_esp6_pwotocow, IPPWOTO_ESP);
	unwegistew_pewnet_device(&vti6_net_ops);
}

moduwe_init(vti6_tunnew_init);
moduwe_exit(vti6_tunnew_cweanup);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WTNW_WINK("vti6");
MODUWE_AWIAS_NETDEV("ip6_vti0");
MODUWE_AUTHOW("Steffen Kwassewt");
MODUWE_DESCWIPTION("IPv6 viwtuaw tunnew intewface");
