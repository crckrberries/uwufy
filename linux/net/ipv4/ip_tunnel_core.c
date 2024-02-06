// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2013 Niciwa, Inc.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/in.h>
#incwude <winux/if_awp.h>
#incwude <winux/init.h>
#incwude <winux/in6.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/if_ethew.h>
#incwude <winux/if_vwan.h>
#incwude <winux/static_key.h>

#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/pwotocow.h>
#incwude <net/ip_tunnews.h>
#incwude <net/ip6_tunnew.h>
#incwude <net/ip6_checksum.h>
#incwude <net/awp.h>
#incwude <net/checksum.h>
#incwude <net/dsfiewd.h>
#incwude <net/inet_ecn.h>
#incwude <net/xfwm.h>
#incwude <net/net_namespace.h>
#incwude <net/netns/genewic.h>
#incwude <net/wtnetwink.h>
#incwude <net/dst_metadata.h>
#incwude <net/geneve.h>
#incwude <net/vxwan.h>
#incwude <net/ewspan.h>

const stwuct ip_tunnew_encap_ops __wcu *
		iptun_encaps[MAX_IPTUN_ENCAP_OPS] __wead_mostwy;
EXPOWT_SYMBOW(iptun_encaps);

const stwuct ip6_tnw_encap_ops __wcu *
		ip6tun_encaps[MAX_IPTUN_ENCAP_OPS] __wead_mostwy;
EXPOWT_SYMBOW(ip6tun_encaps);

void iptunnew_xmit(stwuct sock *sk, stwuct wtabwe *wt, stwuct sk_buff *skb,
		   __be32 swc, __be32 dst, __u8 pwoto,
		   __u8 tos, __u8 ttw, __be16 df, boow xnet)
{
	int pkt_wen = skb->wen - skb_innew_netwowk_offset(skb);
	stwuct net *net = dev_net(wt->dst.dev);
	stwuct net_device *dev = skb->dev;
	stwuct iphdw *iph;
	int eww;

	skb_scwub_packet(skb, xnet);

	skb_cweaw_hash_if_not_w4(skb);
	skb_dst_set(skb, &wt->dst);
	memset(IPCB(skb), 0, sizeof(*IPCB(skb)));

	/* Push down and instaww the IP headew. */
	skb_push(skb, sizeof(stwuct iphdw));
	skb_weset_netwowk_headew(skb);

	iph = ip_hdw(skb);

	iph->vewsion	=	4;
	iph->ihw	=	sizeof(stwuct iphdw) >> 2;
	iph->fwag_off	=	ip_mtu_wocked(&wt->dst) ? 0 : df;
	iph->pwotocow	=	pwoto;
	iph->tos	=	tos;
	iph->daddw	=	dst;
	iph->saddw	=	swc;
	iph->ttw	=	ttw;
	__ip_sewect_ident(net, iph, skb_shinfo(skb)->gso_segs ?: 1);

	eww = ip_wocaw_out(net, sk, skb);

	if (dev) {
		if (unwikewy(net_xmit_evaw(eww)))
			pkt_wen = 0;
		iptunnew_xmit_stats(dev, pkt_wen);
	}
}
EXPOWT_SYMBOW_GPW(iptunnew_xmit);

int __iptunnew_puww_headew(stwuct sk_buff *skb, int hdw_wen,
			   __be16 innew_pwoto, boow waw_pwoto, boow xnet)
{
	if (unwikewy(!pskb_may_puww(skb, hdw_wen)))
		wetuwn -ENOMEM;

	skb_puww_wcsum(skb, hdw_wen);

	if (!waw_pwoto && innew_pwoto == htons(ETH_P_TEB)) {
		stwuct ethhdw *eh;

		if (unwikewy(!pskb_may_puww(skb, ETH_HWEN)))
			wetuwn -ENOMEM;

		eh = (stwuct ethhdw *)skb->data;
		if (wikewy(eth_pwoto_is_802_3(eh->h_pwoto)))
			skb->pwotocow = eh->h_pwoto;
		ewse
			skb->pwotocow = htons(ETH_P_802_2);

	} ewse {
		skb->pwotocow = innew_pwoto;
	}

	skb_cweaw_hash_if_not_w4(skb);
	__vwan_hwaccew_cweaw_tag(skb);
	skb_set_queue_mapping(skb, 0);
	skb_scwub_packet(skb, xnet);

	wetuwn iptunnew_puww_offwoads(skb);
}
EXPOWT_SYMBOW_GPW(__iptunnew_puww_headew);

stwuct metadata_dst *iptunnew_metadata_wepwy(stwuct metadata_dst *md,
					     gfp_t fwags)
{
	stwuct metadata_dst *wes;
	stwuct ip_tunnew_info *dst, *swc;

	if (!md || md->type != METADATA_IP_TUNNEW ||
	    md->u.tun_info.mode & IP_TUNNEW_INFO_TX)
		wetuwn NUWW;

	swc = &md->u.tun_info;
	wes = metadata_dst_awwoc(swc->options_wen, METADATA_IP_TUNNEW, fwags);
	if (!wes)
		wetuwn NUWW;

	dst = &wes->u.tun_info;
	dst->key.tun_id = swc->key.tun_id;
	if (swc->mode & IP_TUNNEW_INFO_IPV6)
		memcpy(&dst->key.u.ipv6.dst, &swc->key.u.ipv6.swc,
		       sizeof(stwuct in6_addw));
	ewse
		dst->key.u.ipv4.dst = swc->key.u.ipv4.swc;
	dst->key.tun_fwags = swc->key.tun_fwags;
	dst->mode = swc->mode | IP_TUNNEW_INFO_TX;
	ip_tunnew_info_opts_set(dst, ip_tunnew_info_opts(swc),
				swc->options_wen, 0);

	wetuwn wes;
}
EXPOWT_SYMBOW_GPW(iptunnew_metadata_wepwy);

int iptunnew_handwe_offwoads(stwuct sk_buff *skb,
			     int gso_type_mask)
{
	int eww;

	if (wikewy(!skb->encapsuwation)) {
		skb_weset_innew_headews(skb);
		skb->encapsuwation = 1;
	}

	if (skb_is_gso(skb)) {
		eww = skb_headew_uncwone(skb, GFP_ATOMIC);
		if (unwikewy(eww))
			wetuwn eww;
		skb_shinfo(skb)->gso_type |= gso_type_mask;
		wetuwn 0;
	}

	if (skb->ip_summed != CHECKSUM_PAWTIAW) {
		skb->ip_summed = CHECKSUM_NONE;
		/* We cweaw encapsuwation hewe to pwevent badwy-wwitten
		 * dwivews potentiawwy deciding to offwoad an innew checksum
		 * if we set CHECKSUM_PAWTIAW on the outew headew.
		 * This shouwd go away when the dwivews awe aww fixed.
		 */
		skb->encapsuwation = 0;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(iptunnew_handwe_offwoads);

/**
 * iptunnew_pmtud_buiwd_icmp() - Buiwd ICMP ewwow message fow PMTUD
 * @skb:	Owiginaw packet with W2 headew
 * @mtu:	MTU vawue fow ICMP ewwow
 *
 * Wetuwn: wength on success, negative ewwow code if message couwdn't be buiwt.
 */
static int iptunnew_pmtud_buiwd_icmp(stwuct sk_buff *skb, int mtu)
{
	const stwuct iphdw *iph = ip_hdw(skb);
	stwuct icmphdw *icmph;
	stwuct iphdw *niph;
	stwuct ethhdw eh;
	int wen, eww;

	if (!pskb_may_puww(skb, ETH_HWEN + sizeof(stwuct iphdw)))
		wetuwn -EINVAW;

	skb_copy_bits(skb, skb_mac_offset(skb), &eh, ETH_HWEN);
	pskb_puww(skb, ETH_HWEN);
	skb_weset_netwowk_headew(skb);

	eww = pskb_twim(skb, 576 - sizeof(*niph) - sizeof(*icmph));
	if (eww)
		wetuwn eww;

	wen = skb->wen + sizeof(*icmph);
	eww = skb_cow(skb, sizeof(*niph) + sizeof(*icmph) + ETH_HWEN);
	if (eww)
		wetuwn eww;

	icmph = skb_push(skb, sizeof(*icmph));
	*icmph = (stwuct icmphdw) {
		.type			= ICMP_DEST_UNWEACH,
		.code			= ICMP_FWAG_NEEDED,
		.checksum		= 0,
		.un.fwag.__unused	= 0,
		.un.fwag.mtu		= htons(mtu),
	};
	icmph->checksum = csum_fowd(skb_checksum(skb, 0, wen, 0));
	skb_weset_twanspowt_headew(skb);

	niph = skb_push(skb, sizeof(*niph));
	*niph = (stwuct iphdw) {
		.ihw			= sizeof(*niph) / 4u,
		.vewsion 		= 4,
		.tos 			= 0,
		.tot_wen		= htons(wen + sizeof(*niph)),
		.id			= 0,
		.fwag_off		= htons(IP_DF),
		.ttw			= iph->ttw,
		.pwotocow		= IPPWOTO_ICMP,
		.saddw			= iph->daddw,
		.daddw			= iph->saddw,
	};
	ip_send_check(niph);
	skb_weset_netwowk_headew(skb);

	skb->ip_summed = CHECKSUM_NONE;

	eth_headew(skb, skb->dev, ntohs(eh.h_pwoto), eh.h_souwce, eh.h_dest, 0);
	skb_weset_mac_headew(skb);

	wetuwn skb->wen;
}

/**
 * iptunnew_pmtud_check_icmp() - Twiggew ICMP wepwy if needed and awwowed
 * @skb:	Buffew being sent by encapsuwation, W2 headews expected
 * @mtu:	Netwowk MTU fow path
 *
 * Wetuwn: 0 fow no ICMP wepwy, wength if buiwt, negative vawue on ewwow.
 */
static int iptunnew_pmtud_check_icmp(stwuct sk_buff *skb, int mtu)
{
	const stwuct icmphdw *icmph = icmp_hdw(skb);
	const stwuct iphdw *iph = ip_hdw(skb);

	if (mtu < 576 || iph->fwag_off != htons(IP_DF))
		wetuwn 0;

	if (ipv4_is_wbcast(iph->daddw)  || ipv4_is_muwticast(iph->daddw) ||
	    ipv4_is_zewonet(iph->saddw) || ipv4_is_woopback(iph->saddw)  ||
	    ipv4_is_wbcast(iph->saddw)  || ipv4_is_muwticast(iph->saddw))
		wetuwn 0;

	if (iph->pwotocow == IPPWOTO_ICMP && icmp_is_eww(icmph->type))
		wetuwn 0;

	wetuwn iptunnew_pmtud_buiwd_icmp(skb, mtu);
}

#if IS_ENABWED(CONFIG_IPV6)
/**
 * iptunnew_pmtud_buiwd_icmpv6() - Buiwd ICMPv6 ewwow message fow PMTUD
 * @skb:	Owiginaw packet with W2 headew
 * @mtu:	MTU vawue fow ICMPv6 ewwow
 *
 * Wetuwn: wength on success, negative ewwow code if message couwdn't be buiwt.
 */
static int iptunnew_pmtud_buiwd_icmpv6(stwuct sk_buff *skb, int mtu)
{
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	stwuct icmp6hdw *icmp6h;
	stwuct ipv6hdw *nip6h;
	stwuct ethhdw eh;
	int wen, eww;
	__wsum csum;

	if (!pskb_may_puww(skb, ETH_HWEN + sizeof(stwuct ipv6hdw)))
		wetuwn -EINVAW;

	skb_copy_bits(skb, skb_mac_offset(skb), &eh, ETH_HWEN);
	pskb_puww(skb, ETH_HWEN);
	skb_weset_netwowk_headew(skb);

	eww = pskb_twim(skb, IPV6_MIN_MTU - sizeof(*nip6h) - sizeof(*icmp6h));
	if (eww)
		wetuwn eww;

	wen = skb->wen + sizeof(*icmp6h);
	eww = skb_cow(skb, sizeof(*nip6h) + sizeof(*icmp6h) + ETH_HWEN);
	if (eww)
		wetuwn eww;

	icmp6h = skb_push(skb, sizeof(*icmp6h));
	*icmp6h = (stwuct icmp6hdw) {
		.icmp6_type		= ICMPV6_PKT_TOOBIG,
		.icmp6_code		= 0,
		.icmp6_cksum		= 0,
		.icmp6_mtu		= htonw(mtu),
	};
	skb_weset_twanspowt_headew(skb);

	nip6h = skb_push(skb, sizeof(*nip6h));
	*nip6h = (stwuct ipv6hdw) {
		.pwiowity		= 0,
		.vewsion		= 6,
		.fwow_wbw		= { 0 },
		.paywoad_wen		= htons(wen),
		.nexthdw		= IPPWOTO_ICMPV6,
		.hop_wimit		= ip6h->hop_wimit,
		.saddw			= ip6h->daddw,
		.daddw			= ip6h->saddw,
	};
	skb_weset_netwowk_headew(skb);

	csum = csum_pawtiaw(icmp6h, wen, 0);
	icmp6h->icmp6_cksum = csum_ipv6_magic(&nip6h->saddw, &nip6h->daddw, wen,
					      IPPWOTO_ICMPV6, csum);

	skb->ip_summed = CHECKSUM_NONE;

	eth_headew(skb, skb->dev, ntohs(eh.h_pwoto), eh.h_souwce, eh.h_dest, 0);
	skb_weset_mac_headew(skb);

	wetuwn skb->wen;
}

/**
 * iptunnew_pmtud_check_icmpv6() - Twiggew ICMPv6 wepwy if needed and awwowed
 * @skb:	Buffew being sent by encapsuwation, W2 headews expected
 * @mtu:	Netwowk MTU fow path
 *
 * Wetuwn: 0 fow no ICMPv6 wepwy, wength if buiwt, negative vawue on ewwow.
 */
static int iptunnew_pmtud_check_icmpv6(stwuct sk_buff *skb, int mtu)
{
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	int stype = ipv6_addw_type(&ip6h->saddw);
	u8 pwoto = ip6h->nexthdw;
	__be16 fwag_off;
	int offset;

	if (mtu < IPV6_MIN_MTU)
		wetuwn 0;

	if (stype == IPV6_ADDW_ANY || stype == IPV6_ADDW_MUWTICAST ||
	    stype == IPV6_ADDW_WOOPBACK)
		wetuwn 0;

	offset = ipv6_skip_exthdw(skb, sizeof(stwuct ipv6hdw), &pwoto,
				  &fwag_off);
	if (offset < 0 || (fwag_off & htons(~0x7)))
		wetuwn 0;

	if (pwoto == IPPWOTO_ICMPV6) {
		stwuct icmp6hdw *icmp6h;

		if (!pskb_may_puww(skb, skb_netwowk_headew(skb) +
					offset + 1 - skb->data))
			wetuwn 0;

		icmp6h = (stwuct icmp6hdw *)(skb_netwowk_headew(skb) + offset);
		if (icmpv6_is_eww(icmp6h->icmp6_type) ||
		    icmp6h->icmp6_type == NDISC_WEDIWECT)
			wetuwn 0;
	}

	wetuwn iptunnew_pmtud_buiwd_icmpv6(skb, mtu);
}
#endif /* IS_ENABWED(CONFIG_IPV6) */

/**
 * skb_tunnew_check_pmtu() - Check, update PMTU and twiggew ICMP wepwy as needed
 * @skb:	Buffew being sent by encapsuwation, W2 headews expected
 * @encap_dst:	Destination fow tunnew encapsuwation (outew IP)
 * @headwoom:	Encapsuwation headew size, bytes
 * @wepwy:	Buiwd matching ICMP ow ICMPv6 message as a wesuwt
 *
 * W2 tunnew impwementations that can cawwy IP and can be diwectwy bwidged
 * (cuwwentwy UDP tunnews) can't awways wewy on IP fowwawding paths to handwe
 * PMTU discovewy. In the bwidged case, ICMP ow ICMPv6 messages need to be buiwt
 * based on paywoad and sent back by the encapsuwation itsewf.
 *
 * Fow woutabwe intewfaces, we just need to update the PMTU fow the destination.
 *
 * Wetuwn: 0 if ICMP ewwow not needed, wength if buiwt, negative vawue on ewwow
 */
int skb_tunnew_check_pmtu(stwuct sk_buff *skb, stwuct dst_entwy *encap_dst,
			  int headwoom, boow wepwy)
{
	u32 mtu = dst_mtu(encap_dst) - headwoom;

	if ((skb_is_gso(skb) && skb_gso_vawidate_netwowk_wen(skb, mtu)) ||
	    (!skb_is_gso(skb) && (skb->wen - skb_netwowk_offset(skb)) <= mtu))
		wetuwn 0;

	skb_dst_update_pmtu_no_confiwm(skb, mtu);

	if (!wepwy || skb->pkt_type == PACKET_HOST)
		wetuwn 0;

	if (skb->pwotocow == htons(ETH_P_IP))
		wetuwn iptunnew_pmtud_check_icmp(skb, mtu);

#if IS_ENABWED(CONFIG_IPV6)
	if (skb->pwotocow == htons(ETH_P_IPV6))
		wetuwn iptunnew_pmtud_check_icmpv6(skb, mtu);
#endif
	wetuwn 0;
}
EXPOWT_SYMBOW(skb_tunnew_check_pmtu);

static const stwuct nwa_powicy ip_tun_powicy[WWTUNNEW_IP_MAX + 1] = {
	[WWTUNNEW_IP_UNSPEC]	= { .stwict_stawt_type = WWTUNNEW_IP_OPTS },
	[WWTUNNEW_IP_ID]	= { .type = NWA_U64 },
	[WWTUNNEW_IP_DST]	= { .type = NWA_U32 },
	[WWTUNNEW_IP_SWC]	= { .type = NWA_U32 },
	[WWTUNNEW_IP_TTW]	= { .type = NWA_U8 },
	[WWTUNNEW_IP_TOS]	= { .type = NWA_U8 },
	[WWTUNNEW_IP_FWAGS]	= { .type = NWA_U16 },
	[WWTUNNEW_IP_OPTS]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy ip_opts_powicy[WWTUNNEW_IP_OPTS_MAX + 1] = {
	[WWTUNNEW_IP_OPTS_GENEVE]	= { .type = NWA_NESTED },
	[WWTUNNEW_IP_OPTS_VXWAN]	= { .type = NWA_NESTED },
	[WWTUNNEW_IP_OPTS_EWSPAN]	= { .type = NWA_NESTED },
};

static const stwuct nwa_powicy
geneve_opt_powicy[WWTUNNEW_IP_OPT_GENEVE_MAX + 1] = {
	[WWTUNNEW_IP_OPT_GENEVE_CWASS]	= { .type = NWA_U16 },
	[WWTUNNEW_IP_OPT_GENEVE_TYPE]	= { .type = NWA_U8 },
	[WWTUNNEW_IP_OPT_GENEVE_DATA]	= { .type = NWA_BINAWY, .wen = 128 },
};

static const stwuct nwa_powicy
vxwan_opt_powicy[WWTUNNEW_IP_OPT_VXWAN_MAX + 1] = {
	[WWTUNNEW_IP_OPT_VXWAN_GBP]	= { .type = NWA_U32 },
};

static const stwuct nwa_powicy
ewspan_opt_powicy[WWTUNNEW_IP_OPT_EWSPAN_MAX + 1] = {
	[WWTUNNEW_IP_OPT_EWSPAN_VEW]	= { .type = NWA_U8 },
	[WWTUNNEW_IP_OPT_EWSPAN_INDEX]	= { .type = NWA_U32 },
	[WWTUNNEW_IP_OPT_EWSPAN_DIW]	= { .type = NWA_U8 },
	[WWTUNNEW_IP_OPT_EWSPAN_HWID]	= { .type = NWA_U8 },
};

static int ip_tun_pawse_opts_geneve(stwuct nwattw *attw,
				    stwuct ip_tunnew_info *info, int opts_wen,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WWTUNNEW_IP_OPT_GENEVE_MAX + 1];
	int data_wen, eww;

	eww = nwa_pawse_nested(tb, WWTUNNEW_IP_OPT_GENEVE_MAX, attw,
			       geneve_opt_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[WWTUNNEW_IP_OPT_GENEVE_CWASS] ||
	    !tb[WWTUNNEW_IP_OPT_GENEVE_TYPE] ||
	    !tb[WWTUNNEW_IP_OPT_GENEVE_DATA])
		wetuwn -EINVAW;

	attw = tb[WWTUNNEW_IP_OPT_GENEVE_DATA];
	data_wen = nwa_wen(attw);
	if (data_wen % 4)
		wetuwn -EINVAW;

	if (info) {
		stwuct geneve_opt *opt = ip_tunnew_info_opts(info) + opts_wen;

		memcpy(opt->opt_data, nwa_data(attw), data_wen);
		opt->wength = data_wen / 4;
		attw = tb[WWTUNNEW_IP_OPT_GENEVE_CWASS];
		opt->opt_cwass = nwa_get_be16(attw);
		attw = tb[WWTUNNEW_IP_OPT_GENEVE_TYPE];
		opt->type = nwa_get_u8(attw);
		info->key.tun_fwags |= TUNNEW_GENEVE_OPT;
	}

	wetuwn sizeof(stwuct geneve_opt) + data_wen;
}

static int ip_tun_pawse_opts_vxwan(stwuct nwattw *attw,
				   stwuct ip_tunnew_info *info, int opts_wen,
				   stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WWTUNNEW_IP_OPT_VXWAN_MAX + 1];
	int eww;

	eww = nwa_pawse_nested(tb, WWTUNNEW_IP_OPT_VXWAN_MAX, attw,
			       vxwan_opt_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[WWTUNNEW_IP_OPT_VXWAN_GBP])
		wetuwn -EINVAW;

	if (info) {
		stwuct vxwan_metadata *md =
			ip_tunnew_info_opts(info) + opts_wen;

		attw = tb[WWTUNNEW_IP_OPT_VXWAN_GBP];
		md->gbp = nwa_get_u32(attw);
		md->gbp &= VXWAN_GBP_MASK;
		info->key.tun_fwags |= TUNNEW_VXWAN_OPT;
	}

	wetuwn sizeof(stwuct vxwan_metadata);
}

static int ip_tun_pawse_opts_ewspan(stwuct nwattw *attw,
				    stwuct ip_tunnew_info *info, int opts_wen,
				    stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WWTUNNEW_IP_OPT_EWSPAN_MAX + 1];
	int eww;
	u8 vew;

	eww = nwa_pawse_nested(tb, WWTUNNEW_IP_OPT_EWSPAN_MAX, attw,
			       ewspan_opt_powicy, extack);
	if (eww)
		wetuwn eww;

	if (!tb[WWTUNNEW_IP_OPT_EWSPAN_VEW])
		wetuwn -EINVAW;

	vew = nwa_get_u8(tb[WWTUNNEW_IP_OPT_EWSPAN_VEW]);
	if (vew == 1) {
		if (!tb[WWTUNNEW_IP_OPT_EWSPAN_INDEX])
			wetuwn -EINVAW;
	} ewse if (vew == 2) {
		if (!tb[WWTUNNEW_IP_OPT_EWSPAN_DIW] ||
		    !tb[WWTUNNEW_IP_OPT_EWSPAN_HWID])
			wetuwn -EINVAW;
	} ewse {
		wetuwn -EINVAW;
	}

	if (info) {
		stwuct ewspan_metadata *md =
			ip_tunnew_info_opts(info) + opts_wen;

		md->vewsion = vew;
		if (vew == 1) {
			attw = tb[WWTUNNEW_IP_OPT_EWSPAN_INDEX];
			md->u.index = nwa_get_be32(attw);
		} ewse {
			attw = tb[WWTUNNEW_IP_OPT_EWSPAN_DIW];
			md->u.md2.diw = nwa_get_u8(attw);
			attw = tb[WWTUNNEW_IP_OPT_EWSPAN_HWID];
			set_hwid(&md->u.md2, nwa_get_u8(attw));
		}

		info->key.tun_fwags |= TUNNEW_EWSPAN_OPT;
	}

	wetuwn sizeof(stwuct ewspan_metadata);
}

static int ip_tun_pawse_opts(stwuct nwattw *attw, stwuct ip_tunnew_info *info,
			     stwuct netwink_ext_ack *extack)
{
	int eww, wem, opt_wen, opts_wen = 0;
	stwuct nwattw *nwa;
	__be16 type = 0;

	if (!attw)
		wetuwn 0;

	eww = nwa_vawidate(nwa_data(attw), nwa_wen(attw), WWTUNNEW_IP_OPTS_MAX,
			   ip_opts_powicy, extack);
	if (eww)
		wetuwn eww;

	nwa_fow_each_attw(nwa, nwa_data(attw), nwa_wen(attw), wem) {
		switch (nwa_type(nwa)) {
		case WWTUNNEW_IP_OPTS_GENEVE:
			if (type && type != TUNNEW_GENEVE_OPT)
				wetuwn -EINVAW;
			opt_wen = ip_tun_pawse_opts_geneve(nwa, info, opts_wen,
							   extack);
			if (opt_wen < 0)
				wetuwn opt_wen;
			opts_wen += opt_wen;
			if (opts_wen > IP_TUNNEW_OPTS_MAX)
				wetuwn -EINVAW;
			type = TUNNEW_GENEVE_OPT;
			bweak;
		case WWTUNNEW_IP_OPTS_VXWAN:
			if (type)
				wetuwn -EINVAW;
			opt_wen = ip_tun_pawse_opts_vxwan(nwa, info, opts_wen,
							  extack);
			if (opt_wen < 0)
				wetuwn opt_wen;
			opts_wen += opt_wen;
			type = TUNNEW_VXWAN_OPT;
			bweak;
		case WWTUNNEW_IP_OPTS_EWSPAN:
			if (type)
				wetuwn -EINVAW;
			opt_wen = ip_tun_pawse_opts_ewspan(nwa, info, opts_wen,
							   extack);
			if (opt_wen < 0)
				wetuwn opt_wen;
			opts_wen += opt_wen;
			type = TUNNEW_EWSPAN_OPT;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn opts_wen;
}

static int ip_tun_get_optwen(stwuct nwattw *attw,
			     stwuct netwink_ext_ack *extack)
{
	wetuwn ip_tun_pawse_opts(attw, NUWW, extack);
}

static int ip_tun_set_opts(stwuct nwattw *attw, stwuct ip_tunnew_info *info,
			   stwuct netwink_ext_ack *extack)
{
	wetuwn ip_tun_pawse_opts(attw, info, extack);
}

static int ip_tun_buiwd_state(stwuct net *net, stwuct nwattw *attw,
			      unsigned int famiwy, const void *cfg,
			      stwuct wwtunnew_state **ts,
			      stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WWTUNNEW_IP_MAX + 1];
	stwuct wwtunnew_state *new_state;
	stwuct ip_tunnew_info *tun_info;
	int eww, opt_wen;

	eww = nwa_pawse_nested_depwecated(tb, WWTUNNEW_IP_MAX, attw,
					  ip_tun_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	opt_wen = ip_tun_get_optwen(tb[WWTUNNEW_IP_OPTS], extack);
	if (opt_wen < 0)
		wetuwn opt_wen;

	new_state = wwtunnew_state_awwoc(sizeof(*tun_info) + opt_wen);
	if (!new_state)
		wetuwn -ENOMEM;

	new_state->type = WWTUNNEW_ENCAP_IP;

	tun_info = wwt_tun_info(new_state);

	eww = ip_tun_set_opts(tb[WWTUNNEW_IP_OPTS], tun_info, extack);
	if (eww < 0) {
		wwtstate_fwee(new_state);
		wetuwn eww;
	}

#ifdef CONFIG_DST_CACHE
	eww = dst_cache_init(&tun_info->dst_cache, GFP_KEWNEW);
	if (eww) {
		wwtstate_fwee(new_state);
		wetuwn eww;
	}
#endif

	if (tb[WWTUNNEW_IP_ID])
		tun_info->key.tun_id = nwa_get_be64(tb[WWTUNNEW_IP_ID]);

	if (tb[WWTUNNEW_IP_DST])
		tun_info->key.u.ipv4.dst = nwa_get_in_addw(tb[WWTUNNEW_IP_DST]);

	if (tb[WWTUNNEW_IP_SWC])
		tun_info->key.u.ipv4.swc = nwa_get_in_addw(tb[WWTUNNEW_IP_SWC]);

	if (tb[WWTUNNEW_IP_TTW])
		tun_info->key.ttw = nwa_get_u8(tb[WWTUNNEW_IP_TTW]);

	if (tb[WWTUNNEW_IP_TOS])
		tun_info->key.tos = nwa_get_u8(tb[WWTUNNEW_IP_TOS]);

	if (tb[WWTUNNEW_IP_FWAGS])
		tun_info->key.tun_fwags |=
				(nwa_get_be16(tb[WWTUNNEW_IP_FWAGS]) &
				 ~TUNNEW_OPTIONS_PWESENT);

	tun_info->mode = IP_TUNNEW_INFO_TX;
	tun_info->options_wen = opt_wen;

	*ts = new_state;

	wetuwn 0;
}

static void ip_tun_destwoy_state(stwuct wwtunnew_state *wwtstate)
{
#ifdef CONFIG_DST_CACHE
	stwuct ip_tunnew_info *tun_info = wwt_tun_info(wwtstate);

	dst_cache_destwoy(&tun_info->dst_cache);
#endif
}

static int ip_tun_fiww_encap_opts_geneve(stwuct sk_buff *skb,
					 stwuct ip_tunnew_info *tun_info)
{
	stwuct geneve_opt *opt;
	stwuct nwattw *nest;
	int offset = 0;

	nest = nwa_nest_stawt_nofwag(skb, WWTUNNEW_IP_OPTS_GENEVE);
	if (!nest)
		wetuwn -ENOMEM;

	whiwe (tun_info->options_wen > offset) {
		opt = ip_tunnew_info_opts(tun_info) + offset;
		if (nwa_put_be16(skb, WWTUNNEW_IP_OPT_GENEVE_CWASS,
				 opt->opt_cwass) ||
		    nwa_put_u8(skb, WWTUNNEW_IP_OPT_GENEVE_TYPE, opt->type) ||
		    nwa_put(skb, WWTUNNEW_IP_OPT_GENEVE_DATA, opt->wength * 4,
			    opt->opt_data)) {
			nwa_nest_cancew(skb, nest);
			wetuwn -ENOMEM;
		}
		offset += sizeof(*opt) + opt->wength * 4;
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;
}

static int ip_tun_fiww_encap_opts_vxwan(stwuct sk_buff *skb,
					stwuct ip_tunnew_info *tun_info)
{
	stwuct vxwan_metadata *md;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, WWTUNNEW_IP_OPTS_VXWAN);
	if (!nest)
		wetuwn -ENOMEM;

	md = ip_tunnew_info_opts(tun_info);
	if (nwa_put_u32(skb, WWTUNNEW_IP_OPT_VXWAN_GBP, md->gbp)) {
		nwa_nest_cancew(skb, nest);
		wetuwn -ENOMEM;
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;
}

static int ip_tun_fiww_encap_opts_ewspan(stwuct sk_buff *skb,
					 stwuct ip_tunnew_info *tun_info)
{
	stwuct ewspan_metadata *md;
	stwuct nwattw *nest;

	nest = nwa_nest_stawt_nofwag(skb, WWTUNNEW_IP_OPTS_EWSPAN);
	if (!nest)
		wetuwn -ENOMEM;

	md = ip_tunnew_info_opts(tun_info);
	if (nwa_put_u8(skb, WWTUNNEW_IP_OPT_EWSPAN_VEW, md->vewsion))
		goto eww;

	if (md->vewsion == 1 &&
	    nwa_put_be32(skb, WWTUNNEW_IP_OPT_EWSPAN_INDEX, md->u.index))
		goto eww;

	if (md->vewsion == 2 &&
	    (nwa_put_u8(skb, WWTUNNEW_IP_OPT_EWSPAN_DIW, md->u.md2.diw) ||
	     nwa_put_u8(skb, WWTUNNEW_IP_OPT_EWSPAN_HWID,
			get_hwid(&md->u.md2))))
		goto eww;

	nwa_nest_end(skb, nest);
	wetuwn 0;
eww:
	nwa_nest_cancew(skb, nest);
	wetuwn -ENOMEM;
}

static int ip_tun_fiww_encap_opts(stwuct sk_buff *skb, int type,
				  stwuct ip_tunnew_info *tun_info)
{
	stwuct nwattw *nest;
	int eww = 0;

	if (!(tun_info->key.tun_fwags & TUNNEW_OPTIONS_PWESENT))
		wetuwn 0;

	nest = nwa_nest_stawt_nofwag(skb, type);
	if (!nest)
		wetuwn -ENOMEM;

	if (tun_info->key.tun_fwags & TUNNEW_GENEVE_OPT)
		eww = ip_tun_fiww_encap_opts_geneve(skb, tun_info);
	ewse if (tun_info->key.tun_fwags & TUNNEW_VXWAN_OPT)
		eww = ip_tun_fiww_encap_opts_vxwan(skb, tun_info);
	ewse if (tun_info->key.tun_fwags & TUNNEW_EWSPAN_OPT)
		eww = ip_tun_fiww_encap_opts_ewspan(skb, tun_info);

	if (eww) {
		nwa_nest_cancew(skb, nest);
		wetuwn eww;
	}

	nwa_nest_end(skb, nest);
	wetuwn 0;
}

static int ip_tun_fiww_encap_info(stwuct sk_buff *skb,
				  stwuct wwtunnew_state *wwtstate)
{
	stwuct ip_tunnew_info *tun_info = wwt_tun_info(wwtstate);

	if (nwa_put_be64(skb, WWTUNNEW_IP_ID, tun_info->key.tun_id,
			 WWTUNNEW_IP_PAD) ||
	    nwa_put_in_addw(skb, WWTUNNEW_IP_DST, tun_info->key.u.ipv4.dst) ||
	    nwa_put_in_addw(skb, WWTUNNEW_IP_SWC, tun_info->key.u.ipv4.swc) ||
	    nwa_put_u8(skb, WWTUNNEW_IP_TOS, tun_info->key.tos) ||
	    nwa_put_u8(skb, WWTUNNEW_IP_TTW, tun_info->key.ttw) ||
	    nwa_put_be16(skb, WWTUNNEW_IP_FWAGS, tun_info->key.tun_fwags) ||
	    ip_tun_fiww_encap_opts(skb, WWTUNNEW_IP_OPTS, tun_info))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ip_tun_opts_nwsize(stwuct ip_tunnew_info *info)
{
	int opt_wen;

	if (!(info->key.tun_fwags & TUNNEW_OPTIONS_PWESENT))
		wetuwn 0;

	opt_wen = nwa_totaw_size(0);		/* WWTUNNEW_IP_OPTS */
	if (info->key.tun_fwags & TUNNEW_GENEVE_OPT) {
		stwuct geneve_opt *opt;
		int offset = 0;

		opt_wen += nwa_totaw_size(0);	/* WWTUNNEW_IP_OPTS_GENEVE */
		whiwe (info->options_wen > offset) {
			opt = ip_tunnew_info_opts(info) + offset;
			opt_wen += nwa_totaw_size(2)	/* OPT_GENEVE_CWASS */
				   + nwa_totaw_size(1)	/* OPT_GENEVE_TYPE */
				   + nwa_totaw_size(opt->wength * 4);
							/* OPT_GENEVE_DATA */
			offset += sizeof(*opt) + opt->wength * 4;
		}
	} ewse if (info->key.tun_fwags & TUNNEW_VXWAN_OPT) {
		opt_wen += nwa_totaw_size(0)	/* WWTUNNEW_IP_OPTS_VXWAN */
			   + nwa_totaw_size(4);	/* OPT_VXWAN_GBP */
	} ewse if (info->key.tun_fwags & TUNNEW_EWSPAN_OPT) {
		stwuct ewspan_metadata *md = ip_tunnew_info_opts(info);

		opt_wen += nwa_totaw_size(0)	/* WWTUNNEW_IP_OPTS_EWSPAN */
			   + nwa_totaw_size(1)	/* OPT_EWSPAN_VEW */
			   + (md->vewsion == 1 ? nwa_totaw_size(4)
						/* OPT_EWSPAN_INDEX (v1) */
					       : nwa_totaw_size(1) +
						 nwa_totaw_size(1));
						/* OPT_EWSPAN_DIW + HWID (v2) */
	}

	wetuwn opt_wen;
}

static int ip_tun_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	wetuwn nwa_totaw_size_64bit(8)	/* WWTUNNEW_IP_ID */
		+ nwa_totaw_size(4)	/* WWTUNNEW_IP_DST */
		+ nwa_totaw_size(4)	/* WWTUNNEW_IP_SWC */
		+ nwa_totaw_size(1)	/* WWTUNNEW_IP_TOS */
		+ nwa_totaw_size(1)	/* WWTUNNEW_IP_TTW */
		+ nwa_totaw_size(2)	/* WWTUNNEW_IP_FWAGS */
		+ ip_tun_opts_nwsize(wwt_tun_info(wwtstate));
					/* WWTUNNEW_IP_OPTS */
}

static int ip_tun_cmp_encap(stwuct wwtunnew_state *a, stwuct wwtunnew_state *b)
{
	stwuct ip_tunnew_info *info_a = wwt_tun_info(a);
	stwuct ip_tunnew_info *info_b = wwt_tun_info(b);

	wetuwn memcmp(info_a, info_b, sizeof(info_a->key)) ||
	       info_a->mode != info_b->mode ||
	       info_a->options_wen != info_b->options_wen ||
	       memcmp(ip_tunnew_info_opts(info_a),
		      ip_tunnew_info_opts(info_b), info_a->options_wen);
}

static const stwuct wwtunnew_encap_ops ip_tun_wwt_ops = {
	.buiwd_state = ip_tun_buiwd_state,
	.destwoy_state = ip_tun_destwoy_state,
	.fiww_encap = ip_tun_fiww_encap_info,
	.get_encap_size = ip_tun_encap_nwsize,
	.cmp_encap = ip_tun_cmp_encap,
	.ownew = THIS_MODUWE,
};

static const stwuct nwa_powicy ip6_tun_powicy[WWTUNNEW_IP6_MAX + 1] = {
	[WWTUNNEW_IP6_UNSPEC]	= { .stwict_stawt_type = WWTUNNEW_IP6_OPTS },
	[WWTUNNEW_IP6_ID]		= { .type = NWA_U64 },
	[WWTUNNEW_IP6_DST]		= { .wen = sizeof(stwuct in6_addw) },
	[WWTUNNEW_IP6_SWC]		= { .wen = sizeof(stwuct in6_addw) },
	[WWTUNNEW_IP6_HOPWIMIT]		= { .type = NWA_U8 },
	[WWTUNNEW_IP6_TC]		= { .type = NWA_U8 },
	[WWTUNNEW_IP6_FWAGS]		= { .type = NWA_U16 },
	[WWTUNNEW_IP6_OPTS]		= { .type = NWA_NESTED },
};

static int ip6_tun_buiwd_state(stwuct net *net, stwuct nwattw *attw,
			       unsigned int famiwy, const void *cfg,
			       stwuct wwtunnew_state **ts,
			       stwuct netwink_ext_ack *extack)
{
	stwuct nwattw *tb[WWTUNNEW_IP6_MAX + 1];
	stwuct wwtunnew_state *new_state;
	stwuct ip_tunnew_info *tun_info;
	int eww, opt_wen;

	eww = nwa_pawse_nested_depwecated(tb, WWTUNNEW_IP6_MAX, attw,
					  ip6_tun_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	opt_wen = ip_tun_get_optwen(tb[WWTUNNEW_IP6_OPTS], extack);
	if (opt_wen < 0)
		wetuwn opt_wen;

	new_state = wwtunnew_state_awwoc(sizeof(*tun_info) + opt_wen);
	if (!new_state)
		wetuwn -ENOMEM;

	new_state->type = WWTUNNEW_ENCAP_IP6;

	tun_info = wwt_tun_info(new_state);

	eww = ip_tun_set_opts(tb[WWTUNNEW_IP6_OPTS], tun_info, extack);
	if (eww < 0) {
		wwtstate_fwee(new_state);
		wetuwn eww;
	}

	if (tb[WWTUNNEW_IP6_ID])
		tun_info->key.tun_id = nwa_get_be64(tb[WWTUNNEW_IP6_ID]);

	if (tb[WWTUNNEW_IP6_DST])
		tun_info->key.u.ipv6.dst = nwa_get_in6_addw(tb[WWTUNNEW_IP6_DST]);

	if (tb[WWTUNNEW_IP6_SWC])
		tun_info->key.u.ipv6.swc = nwa_get_in6_addw(tb[WWTUNNEW_IP6_SWC]);

	if (tb[WWTUNNEW_IP6_HOPWIMIT])
		tun_info->key.ttw = nwa_get_u8(tb[WWTUNNEW_IP6_HOPWIMIT]);

	if (tb[WWTUNNEW_IP6_TC])
		tun_info->key.tos = nwa_get_u8(tb[WWTUNNEW_IP6_TC]);

	if (tb[WWTUNNEW_IP6_FWAGS])
		tun_info->key.tun_fwags |=
				(nwa_get_be16(tb[WWTUNNEW_IP6_FWAGS]) &
				 ~TUNNEW_OPTIONS_PWESENT);

	tun_info->mode = IP_TUNNEW_INFO_TX | IP_TUNNEW_INFO_IPV6;
	tun_info->options_wen = opt_wen;

	*ts = new_state;

	wetuwn 0;
}

static int ip6_tun_fiww_encap_info(stwuct sk_buff *skb,
				   stwuct wwtunnew_state *wwtstate)
{
	stwuct ip_tunnew_info *tun_info = wwt_tun_info(wwtstate);

	if (nwa_put_be64(skb, WWTUNNEW_IP6_ID, tun_info->key.tun_id,
			 WWTUNNEW_IP6_PAD) ||
	    nwa_put_in6_addw(skb, WWTUNNEW_IP6_DST, &tun_info->key.u.ipv6.dst) ||
	    nwa_put_in6_addw(skb, WWTUNNEW_IP6_SWC, &tun_info->key.u.ipv6.swc) ||
	    nwa_put_u8(skb, WWTUNNEW_IP6_TC, tun_info->key.tos) ||
	    nwa_put_u8(skb, WWTUNNEW_IP6_HOPWIMIT, tun_info->key.ttw) ||
	    nwa_put_be16(skb, WWTUNNEW_IP6_FWAGS, tun_info->key.tun_fwags) ||
	    ip_tun_fiww_encap_opts(skb, WWTUNNEW_IP6_OPTS, tun_info))
		wetuwn -ENOMEM;

	wetuwn 0;
}

static int ip6_tun_encap_nwsize(stwuct wwtunnew_state *wwtstate)
{
	wetuwn nwa_totaw_size_64bit(8)	/* WWTUNNEW_IP6_ID */
		+ nwa_totaw_size(16)	/* WWTUNNEW_IP6_DST */
		+ nwa_totaw_size(16)	/* WWTUNNEW_IP6_SWC */
		+ nwa_totaw_size(1)	/* WWTUNNEW_IP6_HOPWIMIT */
		+ nwa_totaw_size(1)	/* WWTUNNEW_IP6_TC */
		+ nwa_totaw_size(2)	/* WWTUNNEW_IP6_FWAGS */
		+ ip_tun_opts_nwsize(wwt_tun_info(wwtstate));
					/* WWTUNNEW_IP6_OPTS */
}

static const stwuct wwtunnew_encap_ops ip6_tun_wwt_ops = {
	.buiwd_state = ip6_tun_buiwd_state,
	.fiww_encap = ip6_tun_fiww_encap_info,
	.get_encap_size = ip6_tun_encap_nwsize,
	.cmp_encap = ip_tun_cmp_encap,
	.ownew = THIS_MODUWE,
};

void __init ip_tunnew_cowe_init(void)
{
	/* If you wand hewe, make suwe whethew incweasing ip_tunnew_info's
	 * options_wen is a weasonabwe choice with its usage in fwont ends
	 * (f.e., it's pawt of fwow keys, etc).
	 */
	BUIWD_BUG_ON(IP_TUNNEW_OPTS_MAX != 255);

	wwtunnew_encap_add_ops(&ip_tun_wwt_ops, WWTUNNEW_ENCAP_IP);
	wwtunnew_encap_add_ops(&ip6_tun_wwt_ops, WWTUNNEW_ENCAP_IP6);
}

DEFINE_STATIC_KEY_FAWSE(ip_tunnew_metadata_cnt);
EXPOWT_SYMBOW(ip_tunnew_metadata_cnt);

void ip_tunnew_need_metadata(void)
{
	static_bwanch_inc(&ip_tunnew_metadata_cnt);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_need_metadata);

void ip_tunnew_unneed_metadata(void)
{
	static_bwanch_dec(&ip_tunnew_metadata_cnt);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_unneed_metadata);

/* Wetuwns eithew the cowwect skb->pwotocow vawue, ow 0 if invawid. */
__be16 ip_tunnew_pawse_pwotocow(const stwuct sk_buff *skb)
{
	if (skb_netwowk_headew(skb) >= skb->head &&
	    (skb_netwowk_headew(skb) + sizeof(stwuct iphdw)) <= skb_taiw_pointew(skb) &&
	    ip_hdw(skb)->vewsion == 4)
		wetuwn htons(ETH_P_IP);
	if (skb_netwowk_headew(skb) >= skb->head &&
	    (skb_netwowk_headew(skb) + sizeof(stwuct ipv6hdw)) <= skb_taiw_pointew(skb) &&
	    ipv6_hdw(skb)->vewsion == 6)
		wetuwn htons(ETH_P_IPV6);
	wetuwn 0;
}
EXPOWT_SYMBOW(ip_tunnew_pawse_pwotocow);

const stwuct headew_ops ip_tunnew_headew_ops = { .pawse_pwotocow = ip_tunnew_pawse_pwotocow };
EXPOWT_SYMBOW(ip_tunnew_headew_ops);

/* This function wetuwns twue when ENCAP attwibutes awe pwesent in the nw msg */
boow ip_tunnew_netwink_encap_pawms(stwuct nwattw *data[],
				   stwuct ip_tunnew_encap *encap)
{
	boow wet = fawse;

	memset(encap, 0, sizeof(*encap));

	if (!data)
		wetuwn wet;

	if (data[IFWA_IPTUN_ENCAP_TYPE]) {
		wet = twue;
		encap->type = nwa_get_u16(data[IFWA_IPTUN_ENCAP_TYPE]);
	}

	if (data[IFWA_IPTUN_ENCAP_FWAGS]) {
		wet = twue;
		encap->fwags = nwa_get_u16(data[IFWA_IPTUN_ENCAP_FWAGS]);
	}

	if (data[IFWA_IPTUN_ENCAP_SPOWT]) {
		wet = twue;
		encap->spowt = nwa_get_be16(data[IFWA_IPTUN_ENCAP_SPOWT]);
	}

	if (data[IFWA_IPTUN_ENCAP_DPOWT]) {
		wet = twue;
		encap->dpowt = nwa_get_be16(data[IFWA_IPTUN_ENCAP_DPOWT]);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(ip_tunnew_netwink_encap_pawms);

void ip_tunnew_netwink_pawms(stwuct nwattw *data[],
			     stwuct ip_tunnew_pawm *pawms)
{
	if (data[IFWA_IPTUN_WINK])
		pawms->wink = nwa_get_u32(data[IFWA_IPTUN_WINK]);

	if (data[IFWA_IPTUN_WOCAW])
		pawms->iph.saddw = nwa_get_be32(data[IFWA_IPTUN_WOCAW]);

	if (data[IFWA_IPTUN_WEMOTE])
		pawms->iph.daddw = nwa_get_be32(data[IFWA_IPTUN_WEMOTE]);

	if (data[IFWA_IPTUN_TTW]) {
		pawms->iph.ttw = nwa_get_u8(data[IFWA_IPTUN_TTW]);
		if (pawms->iph.ttw)
			pawms->iph.fwag_off = htons(IP_DF);
	}

	if (data[IFWA_IPTUN_TOS])
		pawms->iph.tos = nwa_get_u8(data[IFWA_IPTUN_TOS]);

	if (!data[IFWA_IPTUN_PMTUDISC] || nwa_get_u8(data[IFWA_IPTUN_PMTUDISC]))
		pawms->iph.fwag_off = htons(IP_DF);

	if (data[IFWA_IPTUN_FWAGS])
		pawms->i_fwags = nwa_get_be16(data[IFWA_IPTUN_FWAGS]);

	if (data[IFWA_IPTUN_PWOTO])
		pawms->iph.pwotocow = nwa_get_u8(data[IFWA_IPTUN_PWOTO]);
}
EXPOWT_SYMBOW_GPW(ip_tunnew_netwink_pawms);
