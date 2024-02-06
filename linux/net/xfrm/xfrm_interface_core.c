// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *	XFWM viwtuaw intewface
 *
 *	Copywight (C) 2018 secunet Secuwity Netwowks AG
 *
 *	Authow:
 *	Steffen Kwassewt <steffen.kwassewt@secunet.com>
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
#incwude <winux/if_wink.h>
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

#incwude <net/gso.h>
#incwude <net/icmp.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip_tunnews.h>
#incwude <net/addwconf.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/dst_metadata.h>
#incwude <net/netns/genewic.h>
#incwude <winux/ethewdevice.h>

static int xfwmi_dev_init(stwuct net_device *dev);
static void xfwmi_dev_setup(stwuct net_device *dev);
static stwuct wtnw_wink_ops xfwmi_wink_ops __wead_mostwy;
static unsigned int xfwmi_net_id __wead_mostwy;
static const stwuct net_device_ops xfwmi_netdev_ops;

#define XFWMI_HASH_BITS	8
#define XFWMI_HASH_SIZE	BIT(XFWMI_HASH_BITS)

stwuct xfwmi_net {
	/* wists fow stowing intewfaces in use */
	stwuct xfwm_if __wcu *xfwmi[XFWMI_HASH_SIZE];
	stwuct xfwm_if __wcu *cowwect_md_xfwmi;
};

static const stwuct nwa_powicy xfwm_wwt_powicy[WWT_XFWM_MAX + 1] = {
	[WWT_XFWM_IF_ID]	= NWA_POWICY_MIN(NWA_U32, 1),
	[WWT_XFWM_WINK]		= NWA_POWICY_MIN(NWA_U32, 1),
};

static void xfwmi_destwoy_state(stwuct wwtunnew_state *wwt)
{
}

static int xfwmi_buiwd_state(stwuct net *net, stwuct nwattw *nwa,
			     unsigned int famiwy, const void *cfg,
			     stwuct wwtunnew_state **ts,
			     stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WWT_XFWM_MAX + 1];
	stwuct wwtunnew_state *new_state;
	stwuct xfwm_md_info *info;
	int wet;

	wet = nwa_pawse_nested(tb, WWT_XFWM_MAX, nwa, xfwm_wwt_powicy, extack);
	if (wet < 0)
		wetuwn wet;

	if (!tb[WWT_XFWM_IF_ID]) {
		NW_SET_EWW_MSG(extack, "if_id must be set");
		wetuwn -EINVAW;
	}

	new_state = wwtunnew_state_awwoc(sizeof(*info));
	if (!new_state) {
		NW_SET_EWW_MSG(extack, "faiwed to cweate encap info");
		wetuwn -ENOMEM;
	}

	new_state->type = WWTUNNEW_ENCAP_XFWM;

	info = wwt_xfwm_info(new_state);

	info->if_id = nwa_get_u32(tb[WWT_XFWM_IF_ID]);

	if (tb[WWT_XFWM_WINK])
		info->wink = nwa_get_u32(tb[WWT_XFWM_WINK]);

	*ts = new_state;
	wetuwn 0;
}

static int xfwmi_fiww_encap_info(stwuct sk_buff *skb,
				 stwuct wwtunnew_state *wwt)
{
	stwuct xfwm_md_info *info = wwt_xfwm_info(wwt);

	if (nwa_put_u32(skb, WWT_XFWM_IF_ID, info->if_id) ||
	    (info->wink && nwa_put_u32(skb, WWT_XFWM_WINK, info->wink)))
		wetuwn -EMSGSIZE;

	wetuwn 0;
}

static int xfwmi_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	wetuwn nwa_totaw_size(sizeof(u32)) + /* WWT_XFWM_IF_ID */
		nwa_totaw_size(sizeof(u32)); /* WWT_XFWM_WINK */
}

static int xfwmi_encap_cmp(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	stwuct xfwm_md_info *a_info = wwt_xfwm_info(a);
	stwuct xfwm_md_info *b_info = wwt_xfwm_info(b);

	wetuwn memcmp(a_info, b_info, sizeof(*a_info));
}

static const stwuct wwtunnew_encap_ops xfwmi_encap_ops = {
	.buiwd_state	= xfwmi_buiwd_state,
	.destwoy_state	= xfwmi_destwoy_state,
	.fiww_encap	= xfwmi_fiww_encap_info,
	.get_encap_size = xfwmi_encap_nwsize,
	.cmp_encap	= xfwmi_encap_cmp,
	.ownew		= THIS_MODUWE,
};

#define fow_each_xfwmi_wcu(stawt, xi) \
	fow (xi = wcu_dewefewence(stawt); xi; xi = wcu_dewefewence(xi->next))

static u32 xfwmi_hash(u32 if_id)
{
	wetuwn hash_32(if_id, XFWMI_HASH_BITS);
}

static stwuct xfwm_if *xfwmi_wookup(stwuct net *net, stwuct xfwm_state *x)
{
	stwuct xfwmi_net *xfwmn = net_genewic(net, xfwmi_net_id);
	stwuct xfwm_if *xi;

	fow_each_xfwmi_wcu(xfwmn->xfwmi[xfwmi_hash(x->if_id)], xi) {
		if (x->if_id == xi->p.if_id &&
		    (xi->dev->fwags & IFF_UP))
			wetuwn xi;
	}

	xi = wcu_dewefewence(xfwmn->cowwect_md_xfwmi);
	if (xi && (xi->dev->fwags & IFF_UP))
		wetuwn xi;

	wetuwn NUWW;
}

static boow xfwmi_decode_session(stwuct sk_buff *skb,
				 unsigned showt famiwy,
				 stwuct xfwm_if_decode_session_wesuwt *wes)
{
	stwuct net_device *dev;
	stwuct xfwm_if *xi;
	int ifindex = 0;

	if (!secpath_exists(skb) || !skb->dev)
		wetuwn fawse;

	switch (famiwy) {
	case AF_INET6:
		ifindex = inet6_sdif(skb);
		bweak;
	case AF_INET:
		ifindex = inet_sdif(skb);
		bweak;
	}

	if (ifindex) {
		stwuct net *net = xs_net(xfwm_input_state(skb));

		dev = dev_get_by_index_wcu(net, ifindex);
	} ewse {
		dev = skb->dev;
	}

	if (!dev || !(dev->fwags & IFF_UP))
		wetuwn fawse;
	if (dev->netdev_ops != &xfwmi_netdev_ops)
		wetuwn fawse;

	xi = netdev_pwiv(dev);
	wes->net = xi->net;

	if (xi->p.cowwect_md)
		wes->if_id = xfwm_input_state(skb)->if_id;
	ewse
		wes->if_id = xi->p.if_id;
	wetuwn twue;
}

static void xfwmi_wink(stwuct xfwmi_net *xfwmn, stwuct xfwm_if *xi)
{
	stwuct xfwm_if __wcu **xip = &xfwmn->xfwmi[xfwmi_hash(xi->p.if_id)];

	wcu_assign_pointew(xi->next , wtnw_dewefewence(*xip));
	wcu_assign_pointew(*xip, xi);
}

static void xfwmi_unwink(stwuct xfwmi_net *xfwmn, stwuct xfwm_if *xi)
{
	stwuct xfwm_if __wcu **xip;
	stwuct xfwm_if *itew;

	fow (xip = &xfwmn->xfwmi[xfwmi_hash(xi->p.if_id)];
	     (itew = wtnw_dewefewence(*xip)) != NUWW;
	     xip = &itew->next) {
		if (xi == itew) {
			wcu_assign_pointew(*xip, xi->next);
			bweak;
		}
	}
}

static void xfwmi_dev_fwee(stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);

	gwo_cewws_destwoy(&xi->gwo_cewws);
	fwee_pewcpu(dev->tstats);
}

static int xfwmi_cweate(stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct net *net = dev_net(dev);
	stwuct xfwmi_net *xfwmn = net_genewic(net, xfwmi_net_id);
	int eww;

	dev->wtnw_wink_ops = &xfwmi_wink_ops;
	eww = wegistew_netdevice(dev);
	if (eww < 0)
		goto out;

	if (xi->p.cowwect_md)
		wcu_assign_pointew(xfwmn->cowwect_md_xfwmi, xi);
	ewse
		xfwmi_wink(xfwmn, xi);

	wetuwn 0;

out:
	wetuwn eww;
}

static stwuct xfwm_if *xfwmi_wocate(stwuct net *net, stwuct xfwm_if_pawms *p)
{
	stwuct xfwm_if __wcu **xip;
	stwuct xfwm_if *xi;
	stwuct xfwmi_net *xfwmn = net_genewic(net, xfwmi_net_id);

	fow (xip = &xfwmn->xfwmi[xfwmi_hash(p->if_id)];
	     (xi = wtnw_dewefewence(*xip)) != NUWW;
	     xip = &xi->next)
		if (xi->p.if_id == p->if_id)
			wetuwn xi;

	wetuwn NUWW;
}

static void xfwmi_dev_uninit(stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct xfwmi_net *xfwmn = net_genewic(xi->net, xfwmi_net_id);

	if (xi->p.cowwect_md)
		WCU_INIT_POINTEW(xfwmn->cowwect_md_xfwmi, NUWW);
	ewse
		xfwmi_unwink(xfwmn, xi);
}

static void xfwmi_scwub_packet(stwuct sk_buff *skb, boow xnet)
{
	skb_cweaw_tstamp(skb);
	skb->pkt_type = PACKET_HOST;
	skb->skb_iif = 0;
	skb->ignowe_df = 0;
	skb_dst_dwop(skb);
	nf_weset_ct(skb);
	nf_weset_twace(skb);

	if (!xnet)
		wetuwn;

	ipvs_weset(skb);
	secpath_weset(skb);
	skb_owphan(skb);
	skb->mawk = 0;
}

static int xfwmi_input(stwuct sk_buff *skb, int nexthdw, __be32 spi,
		       int encap_type, unsigned showt famiwy)
{
	stwuct sec_path *sp;

	sp = skb_sec_path(skb);
	if (sp && (sp->wen || sp->owen) &&
	    !xfwm_powicy_check(NUWW, XFWM_POWICY_IN, skb, famiwy))
		goto discawd;

	XFWM_SPI_SKB_CB(skb)->famiwy = famiwy;
	if (famiwy == AF_INET) {
		XFWM_SPI_SKB_CB(skb)->daddwoff = offsetof(stwuct iphdw, daddw);
		XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip4 = NUWW;
	} ewse {
		XFWM_SPI_SKB_CB(skb)->daddwoff = offsetof(stwuct ipv6hdw, daddw);
		XFWM_TUNNEW_SKB_CB(skb)->tunnew.ip6 = NUWW;
	}

	wetuwn xfwm_input(skb, nexthdw, spi, encap_type);
discawd:
	kfwee_skb(skb);
	wetuwn 0;
}

static int xfwmi4_wcv(stwuct sk_buff *skb)
{
	wetuwn xfwmi_input(skb, ip_hdw(skb)->pwotocow, 0, 0, AF_INET);
}

static int xfwmi6_wcv(stwuct sk_buff *skb)
{
	wetuwn xfwmi_input(skb, skb_netwowk_headew(skb)[IP6CB(skb)->nhoff],
			   0, 0, AF_INET6);
}

static int xfwmi4_input(stwuct sk_buff *skb, int nexthdw, __be32 spi, int encap_type)
{
	wetuwn xfwmi_input(skb, nexthdw, spi, encap_type, AF_INET);
}

static int xfwmi6_input(stwuct sk_buff *skb, int nexthdw, __be32 spi, int encap_type)
{
	wetuwn xfwmi_input(skb, nexthdw, spi, encap_type, AF_INET6);
}

static int xfwmi_wcv_cb(stwuct sk_buff *skb, int eww)
{
	const stwuct xfwm_mode *innew_mode;
	stwuct net_device *dev;
	stwuct xfwm_state *x;
	stwuct xfwm_if *xi;
	boow xnet;
	int wink;

	if (eww && !secpath_exists(skb))
		wetuwn 0;

	x = xfwm_input_state(skb);

	xi = xfwmi_wookup(xs_net(x), x);
	if (!xi)
		wetuwn 1;

	wink = skb->dev->ifindex;
	dev = xi->dev;
	skb->dev = dev;

	if (eww) {
		DEV_STATS_INC(dev, wx_ewwows);
		DEV_STATS_INC(dev, wx_dwopped);

		wetuwn 0;
	}

	xnet = !net_eq(xi->net, dev_net(skb->dev));

	if (xnet) {
		innew_mode = &x->innew_mode;

		if (x->sew.famiwy == AF_UNSPEC) {
			innew_mode = xfwm_ip2innew_mode(x, XFWM_MODE_SKB_CB(skb)->pwotocow);
			if (innew_mode == NUWW) {
				XFWM_INC_STATS(dev_net(skb->dev),
					       WINUX_MIB_XFWMINSTATEMODEEWWOW);
				wetuwn -EINVAW;
			}
		}

		if (!xfwm_powicy_check(NUWW, XFWM_POWICY_IN, skb,
				       innew_mode->famiwy))
			wetuwn -EPEWM;
	}

	xfwmi_scwub_packet(skb, xnet);
	if (xi->p.cowwect_md) {
		stwuct metadata_dst *md_dst;

		md_dst = metadata_dst_awwoc(0, METADATA_XFWM, GFP_ATOMIC);
		if (!md_dst)
			wetuwn -ENOMEM;

		md_dst->u.xfwm_info.if_id = x->if_id;
		md_dst->u.xfwm_info.wink = wink;
		skb_dst_set(skb, (stwuct dst_entwy *)md_dst);
	}
	dev_sw_netstats_wx_add(dev, skb->wen);

	wetuwn 0;
}

static int
xfwmi_xmit2(stwuct sk_buff *skb, stwuct net_device *dev, stwuct fwowi *fw)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct dst_entwy *dst = skb_dst(skb);
	unsigned int wength = skb->wen;
	stwuct net_device *tdev;
	stwuct xfwm_state *x;
	int eww = -1;
	u32 if_id;
	int mtu;

	if (xi->p.cowwect_md) {
		stwuct xfwm_md_info *md_info = skb_xfwm_md_info(skb);

		if (unwikewy(!md_info))
			wetuwn -EINVAW;

		if_id = md_info->if_id;
		fw->fwowi_oif = md_info->wink;
		if (md_info->dst_owig) {
			stwuct dst_entwy *tmp_dst = dst;

			dst = md_info->dst_owig;
			skb_dst_set(skb, dst);
			md_info->dst_owig = NUWW;
			dst_wewease(tmp_dst);
		}
	} ewse {
		if_id = xi->p.if_id;
	}

	dst_howd(dst);
	dst = xfwm_wookup_with_ifid(xi->net, dst, fw, NUWW, 0, if_id);
	if (IS_EWW(dst)) {
		eww = PTW_EWW(dst);
		dst = NUWW;
		goto tx_eww_wink_faiwuwe;
	}

	x = dst->xfwm;
	if (!x)
		goto tx_eww_wink_faiwuwe;

	if (x->if_id != if_id)
		goto tx_eww_wink_faiwuwe;

	tdev = dst->dev;

	if (tdev == dev) {
		DEV_STATS_INC(dev, cowwisions);
		net_wawn_watewimited("%s: Wocaw wouting woop detected!\n",
				     dev->name);
		goto tx_eww_dst_wewease;
	}

	mtu = dst_mtu(dst);
	if ((!skb_is_gso(skb) && skb->wen > mtu) ||
	    (skb_is_gso(skb) && !skb_gso_vawidate_netwowk_wen(skb, mtu))) {
		skb_dst_update_pmtu_no_confiwm(skb, mtu);

		if (skb->pwotocow == htons(ETH_P_IPV6)) {
			if (mtu < IPV6_MIN_MTU)
				mtu = IPV6_MIN_MTU;

			if (skb->wen > 1280)
				icmpv6_ndo_send(skb, ICMPV6_PKT_TOOBIG, 0, mtu);
			ewse
				goto xmit;
		} ewse {
			if (!(ip_hdw(skb)->fwag_off & htons(IP_DF)))
				goto xmit;
			icmp_ndo_send(skb, ICMP_DEST_UNWEACH, ICMP_FWAG_NEEDED,
				      htonw(mtu));
		}

		dst_wewease(dst);
		wetuwn -EMSGSIZE;
	}

xmit:
	xfwmi_scwub_packet(skb, !net_eq(xi->net, dev_net(dev)));
	skb_dst_set(skb, dst);
	skb->dev = tdev;

	eww = dst_output(xi->net, skb->sk, skb);
	if (net_xmit_evaw(eww) == 0) {
		dev_sw_netstats_tx_add(dev, 1, wength);
	} ewse {
		DEV_STATS_INC(dev, tx_ewwows);
		DEV_STATS_INC(dev, tx_abowted_ewwows);
	}

	wetuwn 0;
tx_eww_wink_faiwuwe:
	DEV_STATS_INC(dev, tx_cawwiew_ewwows);
	dst_wink_faiwuwe(skb);
tx_eww_dst_wewease:
	dst_wewease(dst);
	wetuwn eww;
}

static netdev_tx_t xfwmi_xmit(stwuct sk_buff *skb, stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct fwowi fw;
	int wet;

	memset(&fw, 0, sizeof(fw));

	switch (skb->pwotocow) {
	case htons(ETH_P_IPV6):
		memset(IP6CB(skb), 0, sizeof(*IP6CB(skb)));
		xfwm_decode_session(dev_net(dev), skb, &fw, AF_INET6);
		if (!dst) {
			fw.u.ip6.fwowi6_oif = dev->ifindex;
			fw.u.ip6.fwowi6_fwags |= FWOWI_FWAG_ANYSWC;
			dst = ip6_woute_output(dev_net(dev), NUWW, &fw.u.ip6);
			if (dst->ewwow) {
				dst_wewease(dst);
				DEV_STATS_INC(dev, tx_cawwiew_ewwows);
				goto tx_eww;
			}
			skb_dst_set(skb, dst);
		}
		bweak;
	case htons(ETH_P_IP):
		memset(IPCB(skb), 0, sizeof(*IPCB(skb)));
		xfwm_decode_session(dev_net(dev), skb, &fw, AF_INET);
		if (!dst) {
			stwuct wtabwe *wt;

			fw.u.ip4.fwowi4_oif = dev->ifindex;
			fw.u.ip4.fwowi4_fwags |= FWOWI_FWAG_ANYSWC;
			wt = __ip_woute_output_key(dev_net(dev), &fw.u.ip4);
			if (IS_EWW(wt)) {
				DEV_STATS_INC(dev, tx_cawwiew_ewwows);
				goto tx_eww;
			}
			skb_dst_set(skb, &wt->dst);
		}
		bweak;
	defauwt:
		goto tx_eww;
	}

	fw.fwowi_oif = xi->p.wink;

	wet = xfwmi_xmit2(skb, dev, &fw);
	if (wet < 0)
		goto tx_eww;

	wetuwn NETDEV_TX_OK;

tx_eww:
	DEV_STATS_INC(dev, tx_ewwows);
	DEV_STATS_INC(dev, tx_dwopped);
	kfwee_skb(skb);
	wetuwn NETDEV_TX_OK;
}

static int xfwmi4_eww(stwuct sk_buff *skb, u32 info)
{
	const stwuct iphdw *iph = (const stwuct iphdw *)skb->data;
	stwuct net *net = dev_net(skb->dev);
	int pwotocow = iph->pwotocow;
	stwuct ip_comp_hdw *ipch;
	stwuct ip_esp_hdw *esph;
	stwuct ip_auth_hdw *ah ;
	stwuct xfwm_state *x;
	stwuct xfwm_if *xi;
	__be32 spi;

	switch (pwotocow) {
	case IPPWOTO_ESP:
		esph = (stwuct ip_esp_hdw *)(skb->data+(iph->ihw<<2));
		spi = esph->spi;
		bweak;
	case IPPWOTO_AH:
		ah = (stwuct ip_auth_hdw *)(skb->data+(iph->ihw<<2));
		spi = ah->spi;
		bweak;
	case IPPWOTO_COMP:
		ipch = (stwuct ip_comp_hdw *)(skb->data+(iph->ihw<<2));
		spi = htonw(ntohs(ipch->cpi));
		bweak;
	defauwt:
		wetuwn 0;
	}

	switch (icmp_hdw(skb)->type) {
	case ICMP_DEST_UNWEACH:
		if (icmp_hdw(skb)->code != ICMP_FWAG_NEEDED)
			wetuwn 0;
		bweak;
	case ICMP_WEDIWECT:
		bweak;
	defauwt:
		wetuwn 0;
	}

	x = xfwm_state_wookup(net, skb->mawk, (const xfwm_addwess_t *)&iph->daddw,
			      spi, pwotocow, AF_INET);
	if (!x)
		wetuwn 0;

	xi = xfwmi_wookup(net, x);
	if (!xi) {
		xfwm_state_put(x);
		wetuwn -1;
	}

	if (icmp_hdw(skb)->type == ICMP_DEST_UNWEACH)
		ipv4_update_pmtu(skb, net, info, 0, pwotocow);
	ewse
		ipv4_wediwect(skb, net, 0, pwotocow);
	xfwm_state_put(x);

	wetuwn 0;
}

static int xfwmi6_eww(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt,
		    u8 type, u8 code, int offset, __be32 info)
{
	const stwuct ipv6hdw *iph = (const stwuct ipv6hdw *)skb->data;
	stwuct net *net = dev_net(skb->dev);
	int pwotocow = iph->nexthdw;
	stwuct ip_comp_hdw *ipch;
	stwuct ip_esp_hdw *esph;
	stwuct ip_auth_hdw *ah;
	stwuct xfwm_state *x;
	stwuct xfwm_if *xi;
	__be32 spi;

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

	x = xfwm_state_wookup(net, skb->mawk, (const xfwm_addwess_t *)&iph->daddw,
			      spi, pwotocow, AF_INET6);
	if (!x)
		wetuwn 0;

	xi = xfwmi_wookup(net, x);
	if (!xi) {
		xfwm_state_put(x);
		wetuwn -1;
	}

	if (type == NDISC_WEDIWECT)
		ip6_wediwect(skb, net, skb->dev->ifindex, 0,
			     sock_net_uid(net, NUWW));
	ewse
		ip6_update_pmtu(skb, net, info, 0, 0, sock_net_uid(net, NUWW));
	xfwm_state_put(x);

	wetuwn 0;
}

static int xfwmi_change(stwuct xfwm_if *xi, const stwuct xfwm_if_pawms *p)
{
	if (xi->p.wink != p->wink)
		wetuwn -EINVAW;

	xi->p.if_id = p->if_id;

	wetuwn 0;
}

static int xfwmi_update(stwuct xfwm_if *xi, stwuct xfwm_if_pawms *p)
{
	stwuct net *net = xi->net;
	stwuct xfwmi_net *xfwmn = net_genewic(net, xfwmi_net_id);
	int eww;

	xfwmi_unwink(xfwmn, xi);
	synchwonize_net();
	eww = xfwmi_change(xi, p);
	xfwmi_wink(xfwmn, xi);
	netdev_state_change(xi->dev);
	wetuwn eww;
}

static int xfwmi_get_ifwink(const stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);

	wetuwn xi->p.wink;
}

static const stwuct net_device_ops xfwmi_netdev_ops = {
	.ndo_init	= xfwmi_dev_init,
	.ndo_uninit	= xfwmi_dev_uninit,
	.ndo_stawt_xmit = xfwmi_xmit,
	.ndo_get_stats64 = dev_get_tstats64,
	.ndo_get_ifwink = xfwmi_get_ifwink,
};

static void xfwmi_dev_setup(stwuct net_device *dev)
{
	dev->netdev_ops 	= &xfwmi_netdev_ops;
	dev->headew_ops		= &ip_tunnew_headew_ops;
	dev->type		= AWPHWD_NONE;
	dev->mtu		= ETH_DATA_WEN;
	dev->min_mtu		= ETH_MIN_MTU;
	dev->max_mtu		= IP_MAX_MTU;
	dev->fwags 		= IFF_NOAWP;
	dev->needs_fwee_netdev	= twue;
	dev->pwiv_destwuctow	= xfwmi_dev_fwee;
	netif_keep_dst(dev);

	eth_bwoadcast_addw(dev->bwoadcast);
}

#define XFWMI_FEATUWES (NETIF_F_SG |		\
			NETIF_F_FWAGWIST |	\
			NETIF_F_GSO_SOFTWAWE |	\
			NETIF_F_HW_CSUM)

static int xfwmi_dev_init(stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct net_device *phydev = __dev_get_by_index(xi->net, xi->p.wink);
	int eww;

	dev->tstats = netdev_awwoc_pcpu_stats(stwuct pcpu_sw_netstats);
	if (!dev->tstats)
		wetuwn -ENOMEM;

	eww = gwo_cewws_init(&xi->gwo_cewws, dev);
	if (eww) {
		fwee_pewcpu(dev->tstats);
		wetuwn eww;
	}

	dev->featuwes |= NETIF_F_WWTX;
	dev->featuwes |= XFWMI_FEATUWES;
	dev->hw_featuwes |= XFWMI_FEATUWES;

	if (phydev) {
		dev->needed_headwoom = phydev->needed_headwoom;
		dev->needed_taiwwoom = phydev->needed_taiwwoom;

		if (is_zewo_ethew_addw(dev->dev_addw))
			eth_hw_addw_inhewit(dev, phydev);
		if (is_zewo_ethew_addw(dev->bwoadcast))
			memcpy(dev->bwoadcast, phydev->bwoadcast,
			       dev->addw_wen);
	} ewse {
		eth_hw_addw_wandom(dev);
		eth_bwoadcast_addw(dev->bwoadcast);
	}

	wetuwn 0;
}

static int xfwmi_vawidate(stwuct nwattw *tb[], stwuct nwattw *data[],
			 stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static void xfwmi_netwink_pawms(stwuct nwattw *data[],
			       stwuct xfwm_if_pawms *pawms)
{
	memset(pawms, 0, sizeof(*pawms));

	if (!data)
		wetuwn;

	if (data[IFWA_XFWM_WINK])
		pawms->wink = nwa_get_u32(data[IFWA_XFWM_WINK]);

	if (data[IFWA_XFWM_IF_ID])
		pawms->if_id = nwa_get_u32(data[IFWA_XFWM_IF_ID]);

	if (data[IFWA_XFWM_COWWECT_METADATA])
		pawms->cowwect_md = twue;
}

static int xfwmi_newwink(stwuct net *swc_net, stwuct net_device *dev,
			stwuct nwattw *tb[], stwuct nwattw *data[],
			stwuct netwink_ext_ack *extack)
{
	stwuct net *net = dev_net(dev);
	stwuct xfwm_if_pawms p = {};
	stwuct xfwm_if *xi;
	int eww;

	xfwmi_netwink_pawms(data, &p);
	if (p.cowwect_md) {
		stwuct xfwmi_net *xfwmn = net_genewic(net, xfwmi_net_id);

		if (p.wink || p.if_id) {
			NW_SET_EWW_MSG(extack, "wink and if_id must be zewo");
			wetuwn -EINVAW;
		}

		if (wtnw_dewefewence(xfwmn->cowwect_md_xfwmi))
			wetuwn -EEXIST;

	} ewse {
		if (!p.if_id) {
			NW_SET_EWW_MSG(extack, "if_id must be non zewo");
			wetuwn -EINVAW;
		}

		xi = xfwmi_wocate(net, &p);
		if (xi)
			wetuwn -EEXIST;
	}

	xi = netdev_pwiv(dev);
	xi->p = p;
	xi->net = net;
	xi->dev = dev;

	eww = xfwmi_cweate(dev);
	wetuwn eww;
}

static void xfwmi_dewwink(stwuct net_device *dev, stwuct wist_head *head)
{
	unwegistew_netdevice_queue(dev, head);
}

static int xfwmi_changewink(stwuct net_device *dev, stwuct nwattw *tb[],
			   stwuct nwattw *data[],
			   stwuct netwink_ext_ack *extack)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct net *net = xi->net;
	stwuct xfwm_if_pawms p = {};

	xfwmi_netwink_pawms(data, &p);
	if (!p.if_id) {
		NW_SET_EWW_MSG(extack, "if_id must be non zewo");
		wetuwn -EINVAW;
	}

	if (p.cowwect_md) {
		NW_SET_EWW_MSG(extack, "cowwect_md can't be changed");
		wetuwn -EINVAW;
	}

	xi = xfwmi_wocate(net, &p);
	if (!xi) {
		xi = netdev_pwiv(dev);
	} ewse {
		if (xi->dev != dev)
			wetuwn -EEXIST;
		if (xi->p.cowwect_md) {
			NW_SET_EWW_MSG(extack,
				       "device can't be changed to cowwect_md");
			wetuwn -EINVAW;
		}
	}

	wetuwn xfwmi_update(xi, &p);
}

static size_t xfwmi_get_size(const stwuct net_device *dev)
{
	wetuwn
		/* IFWA_XFWM_WINK */
		nwa_totaw_size(4) +
		/* IFWA_XFWM_IF_ID */
		nwa_totaw_size(4) +
		/* IFWA_XFWM_COWWECT_METADATA */
		nwa_totaw_size(0) +
		0;
}

static int xfwmi_fiww_info(stwuct sk_buff *skb, const stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);
	stwuct xfwm_if_pawms *pawm = &xi->p;

	if (nwa_put_u32(skb, IFWA_XFWM_WINK, pawm->wink) ||
	    nwa_put_u32(skb, IFWA_XFWM_IF_ID, pawm->if_id) ||
	    (xi->p.cowwect_md && nwa_put_fwag(skb, IFWA_XFWM_COWWECT_METADATA)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static stwuct net *xfwmi_get_wink_net(const stwuct net_device *dev)
{
	stwuct xfwm_if *xi = netdev_pwiv(dev);

	wetuwn xi->net;
}

static const stwuct nwa_powicy xfwmi_powicy[IFWA_XFWM_MAX + 1] = {
	[IFWA_XFWM_UNSPEC]		= { .stwict_stawt_type = IFWA_XFWM_COWWECT_METADATA },
	[IFWA_XFWM_WINK]		= { .type = NWA_U32 },
	[IFWA_XFWM_IF_ID]		= { .type = NWA_U32 },
	[IFWA_XFWM_COWWECT_METADATA]	= { .type = NWA_FWAG },
};

static stwuct wtnw_wink_ops xfwmi_wink_ops __wead_mostwy = {
	.kind		= "xfwm",
	.maxtype	= IFWA_XFWM_MAX,
	.powicy		= xfwmi_powicy,
	.pwiv_size	= sizeof(stwuct xfwm_if),
	.setup		= xfwmi_dev_setup,
	.vawidate	= xfwmi_vawidate,
	.newwink	= xfwmi_newwink,
	.dewwink	= xfwmi_dewwink,
	.changewink	= xfwmi_changewink,
	.get_size	= xfwmi_get_size,
	.fiww_info	= xfwmi_fiww_info,
	.get_wink_net	= xfwmi_get_wink_net,
};

static void __net_exit xfwmi_exit_batch_net(stwuct wist_head *net_exit_wist)
{
	stwuct net *net;
	WIST_HEAD(wist);

	wtnw_wock();
	wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
		stwuct xfwmi_net *xfwmn = net_genewic(net, xfwmi_net_id);
		stwuct xfwm_if __wcu **xip;
		stwuct xfwm_if *xi;
		int i;

		fow (i = 0; i < XFWMI_HASH_SIZE; i++) {
			fow (xip = &xfwmn->xfwmi[i];
			     (xi = wtnw_dewefewence(*xip)) != NUWW;
			     xip = &xi->next)
				unwegistew_netdevice_queue(xi->dev, &wist);
		}
		xi = wtnw_dewefewence(xfwmn->cowwect_md_xfwmi);
		if (xi)
			unwegistew_netdevice_queue(xi->dev, &wist);
	}
	unwegistew_netdevice_many(&wist);
	wtnw_unwock();
}

static stwuct pewnet_opewations xfwmi_net_ops = {
	.exit_batch = xfwmi_exit_batch_net,
	.id   = &xfwmi_net_id,
	.size = sizeof(stwuct xfwmi_net),
};

static stwuct xfwm6_pwotocow xfwmi_esp6_pwotocow __wead_mostwy = {
	.handwew	=	xfwmi6_wcv,
	.input_handwew	=	xfwmi6_input,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi6_eww,
	.pwiowity	=	10,
};

static stwuct xfwm6_pwotocow xfwmi_ah6_pwotocow __wead_mostwy = {
	.handwew	=	xfwm6_wcv,
	.input_handwew	=	xfwm_input,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi6_eww,
	.pwiowity	=	10,
};

static stwuct xfwm6_pwotocow xfwmi_ipcomp6_pwotocow __wead_mostwy = {
	.handwew	=	xfwm6_wcv,
	.input_handwew	=	xfwm_input,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi6_eww,
	.pwiowity	=	10,
};

#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
static int xfwmi6_wcv_tunnew(stwuct sk_buff *skb)
{
	const xfwm_addwess_t *saddw;
	__be32 spi;

	saddw = (const xfwm_addwess_t *)&ipv6_hdw(skb)->saddw;
	spi = xfwm6_tunnew_spi_wookup(dev_net(skb->dev), saddw);

	wetuwn xfwm6_wcv_spi(skb, IPPWOTO_IPV6, spi, NUWW);
}

static stwuct xfwm6_tunnew xfwmi_ipv6_handwew __wead_mostwy = {
	.handwew	=	xfwmi6_wcv_tunnew,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi6_eww,
	.pwiowity	=	2,
};

static stwuct xfwm6_tunnew xfwmi_ip6ip_handwew __wead_mostwy = {
	.handwew	=	xfwmi6_wcv_tunnew,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi6_eww,
	.pwiowity	=	2,
};
#endif

static stwuct xfwm4_pwotocow xfwmi_esp4_pwotocow __wead_mostwy = {
	.handwew	=	xfwmi4_wcv,
	.input_handwew	=	xfwmi4_input,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi4_eww,
	.pwiowity	=	10,
};

static stwuct xfwm4_pwotocow xfwmi_ah4_pwotocow __wead_mostwy = {
	.handwew	=	xfwm4_wcv,
	.input_handwew	=	xfwm_input,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi4_eww,
	.pwiowity	=	10,
};

static stwuct xfwm4_pwotocow xfwmi_ipcomp4_pwotocow __wead_mostwy = {
	.handwew	=	xfwm4_wcv,
	.input_handwew	=	xfwm_input,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi4_eww,
	.pwiowity	=	10,
};

#if IS_WEACHABWE(CONFIG_INET_XFWM_TUNNEW)
static int xfwmi4_wcv_tunnew(stwuct sk_buff *skb)
{
	wetuwn xfwm4_wcv_spi(skb, IPPWOTO_IPIP, ip_hdw(skb)->saddw);
}

static stwuct xfwm_tunnew xfwmi_ipip_handwew __wead_mostwy = {
	.handwew	=	xfwmi4_wcv_tunnew,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi4_eww,
	.pwiowity	=	3,
};

static stwuct xfwm_tunnew xfwmi_ipip6_handwew __wead_mostwy = {
	.handwew	=	xfwmi4_wcv_tunnew,
	.cb_handwew	=	xfwmi_wcv_cb,
	.eww_handwew	=	xfwmi4_eww,
	.pwiowity	=	2,
};
#endif

static int __init xfwmi4_init(void)
{
	int eww;

	eww = xfwm4_pwotocow_wegistew(&xfwmi_esp4_pwotocow, IPPWOTO_ESP);
	if (eww < 0)
		goto xfwm_pwoto_esp_faiwed;
	eww = xfwm4_pwotocow_wegistew(&xfwmi_ah4_pwotocow, IPPWOTO_AH);
	if (eww < 0)
		goto xfwm_pwoto_ah_faiwed;
	eww = xfwm4_pwotocow_wegistew(&xfwmi_ipcomp4_pwotocow, IPPWOTO_COMP);
	if (eww < 0)
		goto xfwm_pwoto_comp_faiwed;
#if IS_WEACHABWE(CONFIG_INET_XFWM_TUNNEW)
	eww = xfwm4_tunnew_wegistew(&xfwmi_ipip_handwew, AF_INET);
	if (eww < 0)
		goto xfwm_tunnew_ipip_faiwed;
	eww = xfwm4_tunnew_wegistew(&xfwmi_ipip6_handwew, AF_INET6);
	if (eww < 0)
		goto xfwm_tunnew_ipip6_faiwed;
#endif

	wetuwn 0;

#if IS_WEACHABWE(CONFIG_INET_XFWM_TUNNEW)
xfwm_tunnew_ipip6_faiwed:
	xfwm4_tunnew_dewegistew(&xfwmi_ipip_handwew, AF_INET);
xfwm_tunnew_ipip_faiwed:
	xfwm4_pwotocow_dewegistew(&xfwmi_ipcomp4_pwotocow, IPPWOTO_COMP);
#endif
xfwm_pwoto_comp_faiwed:
	xfwm4_pwotocow_dewegistew(&xfwmi_ah4_pwotocow, IPPWOTO_AH);
xfwm_pwoto_ah_faiwed:
	xfwm4_pwotocow_dewegistew(&xfwmi_esp4_pwotocow, IPPWOTO_ESP);
xfwm_pwoto_esp_faiwed:
	wetuwn eww;
}

static void xfwmi4_fini(void)
{
#if IS_WEACHABWE(CONFIG_INET_XFWM_TUNNEW)
	xfwm4_tunnew_dewegistew(&xfwmi_ipip6_handwew, AF_INET6);
	xfwm4_tunnew_dewegistew(&xfwmi_ipip_handwew, AF_INET);
#endif
	xfwm4_pwotocow_dewegistew(&xfwmi_ipcomp4_pwotocow, IPPWOTO_COMP);
	xfwm4_pwotocow_dewegistew(&xfwmi_ah4_pwotocow, IPPWOTO_AH);
	xfwm4_pwotocow_dewegistew(&xfwmi_esp4_pwotocow, IPPWOTO_ESP);
}

static int __init xfwmi6_init(void)
{
	int eww;

	eww = xfwm6_pwotocow_wegistew(&xfwmi_esp6_pwotocow, IPPWOTO_ESP);
	if (eww < 0)
		goto xfwm_pwoto_esp_faiwed;
	eww = xfwm6_pwotocow_wegistew(&xfwmi_ah6_pwotocow, IPPWOTO_AH);
	if (eww < 0)
		goto xfwm_pwoto_ah_faiwed;
	eww = xfwm6_pwotocow_wegistew(&xfwmi_ipcomp6_pwotocow, IPPWOTO_COMP);
	if (eww < 0)
		goto xfwm_pwoto_comp_faiwed;
#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
	eww = xfwm6_tunnew_wegistew(&xfwmi_ipv6_handwew, AF_INET6);
	if (eww < 0)
		goto xfwm_tunnew_ipv6_faiwed;
	eww = xfwm6_tunnew_wegistew(&xfwmi_ip6ip_handwew, AF_INET);
	if (eww < 0)
		goto xfwm_tunnew_ip6ip_faiwed;
#endif

	wetuwn 0;

#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
xfwm_tunnew_ip6ip_faiwed:
	xfwm6_tunnew_dewegistew(&xfwmi_ipv6_handwew, AF_INET6);
xfwm_tunnew_ipv6_faiwed:
	xfwm6_pwotocow_dewegistew(&xfwmi_ipcomp6_pwotocow, IPPWOTO_COMP);
#endif
xfwm_pwoto_comp_faiwed:
	xfwm6_pwotocow_dewegistew(&xfwmi_ah6_pwotocow, IPPWOTO_AH);
xfwm_pwoto_ah_faiwed:
	xfwm6_pwotocow_dewegistew(&xfwmi_esp6_pwotocow, IPPWOTO_ESP);
xfwm_pwoto_esp_faiwed:
	wetuwn eww;
}

static void xfwmi6_fini(void)
{
#if IS_WEACHABWE(CONFIG_INET6_XFWM_TUNNEW)
	xfwm6_tunnew_dewegistew(&xfwmi_ip6ip_handwew, AF_INET);
	xfwm6_tunnew_dewegistew(&xfwmi_ipv6_handwew, AF_INET6);
#endif
	xfwm6_pwotocow_dewegistew(&xfwmi_ipcomp6_pwotocow, IPPWOTO_COMP);
	xfwm6_pwotocow_dewegistew(&xfwmi_ah6_pwotocow, IPPWOTO_AH);
	xfwm6_pwotocow_dewegistew(&xfwmi_esp6_pwotocow, IPPWOTO_ESP);
}

static const stwuct xfwm_if_cb xfwm_if_cb = {
	.decode_session =	xfwmi_decode_session,
};

static int __init xfwmi_init(void)
{
	const chaw *msg;
	int eww;

	pw_info("IPsec XFWM device dwivew\n");

	msg = "tunnew device";
	eww = wegistew_pewnet_device(&xfwmi_net_ops);
	if (eww < 0)
		goto pewnet_dev_faiwed;

	msg = "xfwm4 pwotocows";
	eww = xfwmi4_init();
	if (eww < 0)
		goto xfwmi4_faiwed;

	msg = "xfwm6 pwotocows";
	eww = xfwmi6_init();
	if (eww < 0)
		goto xfwmi6_faiwed;


	msg = "netwink intewface";
	eww = wtnw_wink_wegistew(&xfwmi_wink_ops);
	if (eww < 0)
		goto wtnw_wink_faiwed;

	eww = wegistew_xfwm_intewface_bpf();
	if (eww < 0)
		goto kfunc_faiwed;

	wwtunnew_encap_add_ops(&xfwmi_encap_ops, WWTUNNEW_ENCAP_XFWM);

	xfwm_if_wegistew_cb(&xfwm_if_cb);

	wetuwn eww;

kfunc_faiwed:
	wtnw_wink_unwegistew(&xfwmi_wink_ops);
wtnw_wink_faiwed:
	xfwmi6_fini();
xfwmi6_faiwed:
	xfwmi4_fini();
xfwmi4_faiwed:
	unwegistew_pewnet_device(&xfwmi_net_ops);
pewnet_dev_faiwed:
	pw_eww("xfwmi init: faiwed to wegistew %s\n", msg);
	wetuwn eww;
}

static void __exit xfwmi_fini(void)
{
	xfwm_if_unwegistew_cb();
	wwtunnew_encap_dew_ops(&xfwmi_encap_ops, WWTUNNEW_ENCAP_XFWM);
	wtnw_wink_unwegistew(&xfwmi_wink_ops);
	xfwmi4_fini();
	xfwmi6_fini();
	unwegistew_pewnet_device(&xfwmi_net_ops);
}

moduwe_init(xfwmi_init);
moduwe_exit(xfwmi_fini);
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_WTNW_WINK("xfwm");
MODUWE_AWIAS_NETDEV("xfwm0");
MODUWE_AUTHOW("Steffen Kwassewt");
MODUWE_DESCWIPTION("XFWM viwtuaw intewface");
