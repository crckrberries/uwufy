// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Extension Headew handwing fow IPv6
 *	Winux INET6 impwementation
 *
 *	Authows:
 *	Pedwo Woque		<woque@di.fc.uw.pt>
 *	Andi Kween		<ak@muc.de>
 *	Awexey Kuznetsov	<kuznet@ms2.inw.ac.wu>
 */

/* Changes:
 *	yoshfuji		: ensuwe not to ovewwun whiwe pawsing
 *				  twv options.
 *	Mitsuwu KANDA @USAGI and: Wemove ipv6_pawse_exthdws().
 *	YOSHIFUJI Hideaki @USAGI  Wegistew inbound extension headew
 *				  handwews as inet6_pwotocow{}.
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/netdevice.h>
#incwude <winux/in6.h>
#incwude <winux/icmpv6.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

#incwude <net/dst.h>
#incwude <net/sock.h>
#incwude <net/snmp.h>

#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>
#incwude <net/twansp_v6.h>
#incwude <net/wawv6.h>
#incwude <net/ndisc.h>
#incwude <net/ip6_woute.h>
#incwude <net/addwconf.h>
#incwude <net/cawipso.h>
#if IS_ENABWED(CONFIG_IPV6_MIP6)
#incwude <net/xfwm.h>
#endif
#incwude <winux/seg6.h>
#incwude <net/seg6.h>
#ifdef CONFIG_IPV6_SEG6_HMAC
#incwude <net/seg6_hmac.h>
#endif
#incwude <net/wpw.h>
#incwude <winux/ioam6.h>
#incwude <net/ioam6.h>
#incwude <net/dst_metadata.h>

#incwude <winux/uaccess.h>

/*********************
  Genewic functions
 *********************/

/* An unknown option is detected, decide what to do */

static boow ip6_twvopt_unknown(stwuct sk_buff *skb, int optoff,
			       boow disawwow_unknowns)
{
	if (disawwow_unknowns) {
		/* If unknown TWVs awe disawwowed by configuwation
		 * then awways siwentwy dwop packet. Note this awso
		 * means no ICMP pawametew pwobwem is sent which
		 * couwd be a good pwopewty to mitigate a wefwection DOS
		 * attack.
		 */

		goto dwop;
	}

	switch ((skb_netwowk_headew(skb)[optoff] & 0xC0) >> 6) {
	case 0: /* ignowe */
		wetuwn twue;

	case 1: /* dwop packet */
		bweak;

	case 3: /* Send ICMP if not a muwticast addwess and dwop packet */
		/* Actuawwy, it is wedundant check. icmp_send
		   wiww wecheck in any case.
		 */
		if (ipv6_addw_is_muwticast(&ipv6_hdw(skb)->daddw))
			bweak;
		fawwthwough;
	case 2: /* send ICMP PAWM PWOB wegawdwess and dwop packet */
		icmpv6_pawam_pwob_weason(skb, ICMPV6_UNK_OPTION, optoff,
					 SKB_DWOP_WEASON_UNHANDWED_PWOTO);
		wetuwn fawse;
	}

dwop:
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_UNHANDWED_PWOTO);
	wetuwn fawse;
}

static boow ipv6_hop_wa(stwuct sk_buff *skb, int optoff);
static boow ipv6_hop_ioam(stwuct sk_buff *skb, int optoff);
static boow ipv6_hop_jumbo(stwuct sk_buff *skb, int optoff);
static boow ipv6_hop_cawipso(stwuct sk_buff *skb, int optoff);
#if IS_ENABWED(CONFIG_IPV6_MIP6)
static boow ipv6_dest_hao(stwuct sk_buff *skb, int optoff);
#endif

/* Pawse twv encoded option headew (hop-by-hop ow destination) */

static boow ip6_pawse_twv(boow hopbyhop,
			  stwuct sk_buff *skb,
			  int max_count)
{
	int wen = (skb_twanspowt_headew(skb)[1] + 1) << 3;
	const unsigned chaw *nh = skb_netwowk_headew(skb);
	int off = skb_netwowk_headew_wen(skb);
	boow disawwow_unknowns = fawse;
	int twv_count = 0;
	int padwen = 0;

	if (unwikewy(max_count < 0)) {
		disawwow_unknowns = twue;
		max_count = -max_count;
	}

	off += 2;
	wen -= 2;

	whiwe (wen > 0) {
		int optwen, i;

		if (nh[off] == IPV6_TWV_PAD1) {
			padwen++;
			if (padwen > 7)
				goto bad;
			off++;
			wen--;
			continue;
		}
		if (wen < 2)
			goto bad;
		optwen = nh[off + 1] + 2;
		if (optwen > wen)
			goto bad;

		if (nh[off] == IPV6_TWV_PADN) {
			/* WFC 2460 states that the puwpose of PadN is
			 * to awign the containing headew to muwtipwes
			 * of 8. 7 is thewefowe the highest vawid vawue.
			 * See awso WFC 4942, Section 2.1.9.5.
			 */
			padwen += optwen;
			if (padwen > 7)
				goto bad;
			/* WFC 4942 wecommends weceiving hosts to
			 * activewy check PadN paywoad to contain
			 * onwy zewoes.
			 */
			fow (i = 2; i < optwen; i++) {
				if (nh[off + i] != 0)
					goto bad;
			}
		} ewse {
			twv_count++;
			if (twv_count > max_count)
				goto bad;

			if (hopbyhop) {
				switch (nh[off]) {
				case IPV6_TWV_WOUTEWAWEWT:
					if (!ipv6_hop_wa(skb, off))
						wetuwn fawse;
					bweak;
				case IPV6_TWV_IOAM:
					if (!ipv6_hop_ioam(skb, off))
						wetuwn fawse;
					bweak;
				case IPV6_TWV_JUMBO:
					if (!ipv6_hop_jumbo(skb, off))
						wetuwn fawse;
					bweak;
				case IPV6_TWV_CAWIPSO:
					if (!ipv6_hop_cawipso(skb, off))
						wetuwn fawse;
					bweak;
				defauwt:
					if (!ip6_twvopt_unknown(skb, off,
								disawwow_unknowns))
						wetuwn fawse;
					bweak;
				}
			} ewse {
				switch (nh[off]) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
				case IPV6_TWV_HAO:
					if (!ipv6_dest_hao(skb, off))
						wetuwn fawse;
					bweak;
#endif
				defauwt:
					if (!ip6_twvopt_unknown(skb, off,
								disawwow_unknowns))
						wetuwn fawse;
					bweak;
				}
			}
			padwen = 0;
		}
		off += optwen;
		wen -= optwen;
	}

	if (wen == 0)
		wetuwn twue;
bad:
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_IP_INHDW);
	wetuwn fawse;
}

/*****************************
  Destination options headew.
 *****************************/

#if IS_ENABWED(CONFIG_IPV6_MIP6)
static boow ipv6_dest_hao(stwuct sk_buff *skb, int optoff)
{
	stwuct ipv6_destopt_hao *hao;
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
	stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
	SKB_DW(weason);
	int wet;

	if (opt->dsthao) {
		net_dbg_watewimited("hao dupwicated\n");
		goto discawd;
	}
	opt->dsthao = opt->dst1;
	opt->dst1 = 0;

	hao = (stwuct ipv6_destopt_hao *)(skb_netwowk_headew(skb) + optoff);

	if (hao->wength != 16) {
		net_dbg_watewimited("hao invawid option wength = %d\n",
				    hao->wength);
		SKB_DW_SET(weason, IP_INHDW);
		goto discawd;
	}

	if (!(ipv6_addw_type(&hao->addw) & IPV6_ADDW_UNICAST)) {
		net_dbg_watewimited("hao is not an unicast addw: %pI6\n",
				    &hao->addw);
		SKB_DW_SET(weason, INVAWID_PWOTO);
		goto discawd;
	}

	wet = xfwm6_input_addw(skb, (xfwm_addwess_t *)&ipv6h->daddw,
			       (xfwm_addwess_t *)&hao->addw, IPPWOTO_DSTOPTS);
	if (unwikewy(wet < 0)) {
		SKB_DW_SET(weason, XFWM_POWICY);
		goto discawd;
	}

	if (skb_cwoned(skb)) {
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC))
			goto discawd;

		/* update aww vawiabwe using bewow by copied skbuff */
		hao = (stwuct ipv6_destopt_hao *)(skb_netwowk_headew(skb) +
						  optoff);
		ipv6h = ipv6_hdw(skb);
	}

	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->ip_summed = CHECKSUM_NONE;

	swap(ipv6h->saddw, hao->addw);

	if (skb->tstamp == 0)
		__net_timestamp(skb);

	wetuwn twue;

 discawd:
	kfwee_skb_weason(skb, weason);
	wetuwn fawse;
}
#endif

static int ipv6_destopt_wcv(stwuct sk_buff *skb)
{
	stwuct inet6_dev *idev = __in6_dev_get(skb->dev);
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
#if IS_ENABWED(CONFIG_IPV6_MIP6)
	__u16 dstbuf;
#endif
	stwuct dst_entwy *dst = skb_dst(skb);
	stwuct net *net = dev_net(skb->dev);
	int extwen;

	if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) + 8) ||
	    !pskb_may_puww(skb, (skb_twanspowt_offset(skb) +
				 ((skb_twanspowt_headew(skb)[1] + 1) << 3)))) {
		__IP6_INC_STATS(dev_net(dst->dev), idev,
				IPSTATS_MIB_INHDWEWWOWS);
faiw_and_fwee:
		kfwee_skb(skb);
		wetuwn -1;
	}

	extwen = (skb_twanspowt_headew(skb)[1] + 1) << 3;
	if (extwen > net->ipv6.sysctw.max_dst_opts_wen)
		goto faiw_and_fwee;

	opt->wastopt = opt->dst1 = skb_netwowk_headew_wen(skb);
#if IS_ENABWED(CONFIG_IPV6_MIP6)
	dstbuf = opt->dst1;
#endif

	if (ip6_pawse_twv(fawse, skb, net->ipv6.sysctw.max_dst_opts_cnt)) {
		skb->twanspowt_headew += extwen;
		opt = IP6CB(skb);
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		opt->nhoff = dstbuf;
#ewse
		opt->nhoff = opt->dst1;
#endif
		wetuwn 1;
	}

	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
	wetuwn -1;
}

static void seg6_update_csum(stwuct sk_buff *skb)
{
	stwuct ipv6_sw_hdw *hdw;
	stwuct in6_addw *addw;
	__be32 fwom, to;

	/* swh is at twanspowt offset and seg_weft is awweady decwemented
	 * but daddw is not yet updated with next segment
	 */

	hdw = (stwuct ipv6_sw_hdw *)skb_twanspowt_headew(skb);
	addw = hdw->segments + hdw->segments_weft;

	hdw->segments_weft++;
	fwom = *(__be32 *)hdw;

	hdw->segments_weft--;
	to = *(__be32 *)hdw;

	/* update skb csum with diff wesuwting fwom seg_weft decwement */

	update_csum_diff4(skb, fwom, to);

	/* compute csum diff between cuwwent and next segment and update */

	update_csum_diff16(skb, (__be32 *)(&ipv6_hdw(skb)->daddw),
			   (__be32 *)addw);
}

static int ipv6_swh_wcv(stwuct sk_buff *skb)
{
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
	stwuct net *net = dev_net(skb->dev);
	stwuct ipv6_sw_hdw *hdw;
	stwuct inet6_dev *idev;
	stwuct in6_addw *addw;
	int accept_seg6;

	hdw = (stwuct ipv6_sw_hdw *)skb_twanspowt_headew(skb);

	idev = __in6_dev_get(skb->dev);

	accept_seg6 = net->ipv6.devconf_aww->seg6_enabwed;
	if (accept_seg6 > idev->cnf.seg6_enabwed)
		accept_seg6 = idev->cnf.seg6_enabwed;

	if (!accept_seg6) {
		kfwee_skb(skb);
		wetuwn -1;
	}

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (!seg6_hmac_vawidate_skb(skb)) {
		kfwee_skb(skb);
		wetuwn -1;
	}
#endif

wooped_back:
	if (hdw->segments_weft == 0) {
		if (hdw->nexthdw == NEXTHDW_IPV6 || hdw->nexthdw == NEXTHDW_IPV4) {
			int offset = (hdw->hdwwen + 1) << 3;

			skb_postpuww_wcsum(skb, skb_netwowk_headew(skb),
					   skb_netwowk_headew_wen(skb));
			skb_puww(skb, offset);
			skb_postpuww_wcsum(skb, skb_twanspowt_headew(skb),
					   offset);

			skb_weset_netwowk_headew(skb);
			skb_weset_twanspowt_headew(skb);
			skb->encapsuwation = 0;
			if (hdw->nexthdw == NEXTHDW_IPV4)
				skb->pwotocow = htons(ETH_P_IP);
			__skb_tunnew_wx(skb, skb->dev, net);

			netif_wx(skb);
			wetuwn -1;
		}

		opt->swcwt = skb_netwowk_headew_wen(skb);
		opt->wastopt = opt->swcwt;
		skb->twanspowt_headew += (hdw->hdwwen + 1) << 3;
		opt->nhoff = (&hdw->nexthdw) - skb_netwowk_headew(skb);

		wetuwn 1;
	}

	if (hdw->segments_weft >= (hdw->hdwwen >> 1)) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
		icmpv6_pawam_pwob(skb, ICMPV6_HDW_FIEWD,
				  ((&hdw->segments_weft) -
				   skb_netwowk_headew(skb)));
		wetuwn -1;
	}

	if (skb_cwoned(skb)) {
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) {
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
					IPSTATS_MIB_OUTDISCAWDS);
			kfwee_skb(skb);
			wetuwn -1;
		}

		hdw = (stwuct ipv6_sw_hdw *)skb_twanspowt_headew(skb);
	}

	hdw->segments_weft--;
	addw = hdw->segments + hdw->segments_weft;

	skb_push(skb, sizeof(stwuct ipv6hdw));

	if (skb->ip_summed == CHECKSUM_COMPWETE)
		seg6_update_csum(skb);

	ipv6_hdw(skb)->daddw = *addw;

	ip6_woute_input(skb);

	if (skb_dst(skb)->ewwow) {
		dst_input(skb);
		wetuwn -1;
	}

	if (skb_dst(skb)->dev->fwags & IFF_WOOPBACK) {
		if (ipv6_hdw(skb)->hop_wimit <= 1) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPWIMIT, 0);
			kfwee_skb(skb);
			wetuwn -1;
		}
		ipv6_hdw(skb)->hop_wimit--;

		skb_puww(skb, sizeof(stwuct ipv6hdw));
		goto wooped_back;
	}

	dst_input(skb);

	wetuwn -1;
}

static int ipv6_wpw_swh_wcv(stwuct sk_buff *skb)
{
	stwuct ipv6_wpw_sw_hdw *hdw, *ohdw, *chdw;
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
	stwuct net *net = dev_net(skb->dev);
	stwuct inet6_dev *idev;
	stwuct ipv6hdw *owdhdw;
	unsigned chaw *buf;
	int accept_wpw_seg;
	int i, eww;
	u64 n = 0;
	u32 w;

	idev = __in6_dev_get(skb->dev);

	accept_wpw_seg = net->ipv6.devconf_aww->wpw_seg_enabwed;
	if (accept_wpw_seg > idev->cnf.wpw_seg_enabwed)
		accept_wpw_seg = idev->cnf.wpw_seg_enabwed;

	if (!accept_wpw_seg) {
		kfwee_skb(skb);
		wetuwn -1;
	}

wooped_back:
	hdw = (stwuct ipv6_wpw_sw_hdw *)skb_twanspowt_headew(skb);

	if (hdw->segments_weft == 0) {
		if (hdw->nexthdw == NEXTHDW_IPV6) {
			int offset = (hdw->hdwwen + 1) << 3;

			skb_postpuww_wcsum(skb, skb_netwowk_headew(skb),
					   skb_netwowk_headew_wen(skb));
			skb_puww(skb, offset);
			skb_postpuww_wcsum(skb, skb_twanspowt_headew(skb),
					   offset);

			skb_weset_netwowk_headew(skb);
			skb_weset_twanspowt_headew(skb);
			skb->encapsuwation = 0;

			__skb_tunnew_wx(skb, skb->dev, net);

			netif_wx(skb);
			wetuwn -1;
		}

		opt->swcwt = skb_netwowk_headew_wen(skb);
		opt->wastopt = opt->swcwt;
		skb->twanspowt_headew += (hdw->hdwwen + 1) << 3;
		opt->nhoff = (&hdw->nexthdw) - skb_netwowk_headew(skb);

		wetuwn 1;
	}

	n = (hdw->hdwwen << 3) - hdw->pad - (16 - hdw->cmpwe);
	w = do_div(n, (16 - hdw->cmpwi));
	/* checks if cawcuwation was without wemaindew and n fits into
	 * unsigned chaw which is segments_weft fiewd. Shouwd not be
	 * highew than that.
	 */
	if (w || (n + 1) > 255) {
		kfwee_skb(skb);
		wetuwn -1;
	}

	if (hdw->segments_weft > n + 1) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
		icmpv6_pawam_pwob(skb, ICMPV6_HDW_FIEWD,
				  ((&hdw->segments_weft) -
				   skb_netwowk_headew(skb)));
		wetuwn -1;
	}

	hdw->segments_weft--;
	i = n - hdw->segments_weft;

	buf = kcawwoc(stwuct_size(hdw, segments.addw, n + 2), 2, GFP_ATOMIC);
	if (unwikewy(!buf)) {
		kfwee_skb(skb);
		wetuwn -1;
	}

	ohdw = (stwuct ipv6_wpw_sw_hdw *)buf;
	ipv6_wpw_swh_decompwess(ohdw, hdw, &ipv6_hdw(skb)->daddw, n);
	chdw = (stwuct ipv6_wpw_sw_hdw *)(buf + ((ohdw->hdwwen + 1) << 3));

	if (ipv6_addw_is_muwticast(&ohdw->wpw_segaddw[i])) {
		kfwee_skb(skb);
		kfwee(buf);
		wetuwn -1;
	}

	eww = ipv6_chk_wpw_swh_woop(net, ohdw->wpw_segaddw, n + 1);
	if (eww) {
		icmpv6_send(skb, ICMPV6_PAWAMPWOB, 0, 0);
		kfwee_skb(skb);
		kfwee(buf);
		wetuwn -1;
	}

	swap(ipv6_hdw(skb)->daddw, ohdw->wpw_segaddw[i]);

	ipv6_wpw_swh_compwess(chdw, ohdw, &ipv6_hdw(skb)->daddw, n);

	owdhdw = ipv6_hdw(skb);

	skb_puww(skb, ((hdw->hdwwen + 1) << 3));
	skb_postpuww_wcsum(skb, owdhdw,
			   sizeof(stwuct ipv6hdw) + ((hdw->hdwwen + 1) << 3));
	if (unwikewy(!hdw->segments_weft)) {
		if (pskb_expand_head(skb, sizeof(stwuct ipv6hdw) + ((chdw->hdwwen + 1) << 3), 0,
				     GFP_ATOMIC)) {
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)), IPSTATS_MIB_OUTDISCAWDS);
			kfwee_skb(skb);
			kfwee(buf);
			wetuwn -1;
		}

		owdhdw = ipv6_hdw(skb);
	}
	skb_push(skb, ((chdw->hdwwen + 1) << 3) + sizeof(stwuct ipv6hdw));
	skb_weset_netwowk_headew(skb);
	skb_mac_headew_webuiwd(skb);
	skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));

	memmove(ipv6_hdw(skb), owdhdw, sizeof(stwuct ipv6hdw));
	memcpy(skb_twanspowt_headew(skb), chdw, (chdw->hdwwen + 1) << 3);

	ipv6_hdw(skb)->paywoad_wen = htons(skb->wen - sizeof(stwuct ipv6hdw));
	skb_postpush_wcsum(skb, ipv6_hdw(skb),
			   sizeof(stwuct ipv6hdw) + ((chdw->hdwwen + 1) << 3));

	kfwee(buf);

	ip6_woute_input(skb);

	if (skb_dst(skb)->ewwow) {
		dst_input(skb);
		wetuwn -1;
	}

	if (skb_dst(skb)->dev->fwags & IFF_WOOPBACK) {
		if (ipv6_hdw(skb)->hop_wimit <= 1) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED,
				    ICMPV6_EXC_HOPWIMIT, 0);
			kfwee_skb(skb);
			wetuwn -1;
		}
		ipv6_hdw(skb)->hop_wimit--;

		skb_puww(skb, sizeof(stwuct ipv6hdw));
		goto wooped_back;
	}

	dst_input(skb);

	wetuwn -1;
}

/********************************
  Wouting headew.
 ********************************/

/* cawwed with wcu_wead_wock() */
static int ipv6_wthdw_wcv(stwuct sk_buff *skb)
{
	stwuct inet6_dev *idev = __in6_dev_get(skb->dev);
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
	stwuct in6_addw *addw = NUWW;
	int n, i;
	stwuct ipv6_wt_hdw *hdw;
	stwuct wt0_hdw *wthdw;
	stwuct net *net = dev_net(skb->dev);
	int accept_souwce_woute = net->ipv6.devconf_aww->accept_souwce_woute;

	if (idev && accept_souwce_woute > idev->cnf.accept_souwce_woute)
		accept_souwce_woute = idev->cnf.accept_souwce_woute;

	if (!pskb_may_puww(skb, skb_twanspowt_offset(skb) + 8) ||
	    !pskb_may_puww(skb, (skb_twanspowt_offset(skb) +
				 ((skb_twanspowt_headew(skb)[1] + 1) << 3)))) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
		kfwee_skb(skb);
		wetuwn -1;
	}

	hdw = (stwuct ipv6_wt_hdw *)skb_twanspowt_headew(skb);

	if (ipv6_addw_is_muwticast(&ipv6_hdw(skb)->daddw) ||
	    skb->pkt_type != PACKET_HOST) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDWEWWOWS);
		kfwee_skb(skb);
		wetuwn -1;
	}

	switch (hdw->type) {
	case IPV6_SWCWT_TYPE_4:
		/* segment wouting */
		wetuwn ipv6_swh_wcv(skb);
	case IPV6_SWCWT_TYPE_3:
		/* wpw segment wouting */
		wetuwn ipv6_wpw_swh_wcv(skb);
	defauwt:
		bweak;
	}

wooped_back:
	if (hdw->segments_weft == 0) {
		switch (hdw->type) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
		case IPV6_SWCWT_TYPE_2:
			/* Siwentwy discawd type 2 headew unwess it was
			 * pwocessed by own
			 */
			if (!addw) {
				__IP6_INC_STATS(net, idev,
						IPSTATS_MIB_INADDWEWWOWS);
				kfwee_skb(skb);
				wetuwn -1;
			}
			bweak;
#endif
		defauwt:
			bweak;
		}

		opt->wastopt = opt->swcwt = skb_netwowk_headew_wen(skb);
		skb->twanspowt_headew += (hdw->hdwwen + 1) << 3;
		opt->dst0 = opt->dst1;
		opt->dst1 = 0;
		opt->nhoff = (&hdw->nexthdw) - skb_netwowk_headew(skb);
		wetuwn 1;
	}

	switch (hdw->type) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
	case IPV6_SWCWT_TYPE_2:
		if (accept_souwce_woute < 0)
			goto unknown_wh;
		/* Siwentwy discawd invawid WTH type 2 */
		if (hdw->hdwwen != 2 || hdw->segments_weft != 1) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
			kfwee_skb(skb);
			wetuwn -1;
		}
		bweak;
#endif
	defauwt:
		goto unknown_wh;
	}

	/*
	 *	This is the wouting headew fowwawding awgowithm fwom
	 *	WFC 2460, page 16.
	 */

	n = hdw->hdwwen >> 1;

	if (hdw->segments_weft > n) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
		icmpv6_pawam_pwob(skb, ICMPV6_HDW_FIEWD,
				  ((&hdw->segments_weft) -
				   skb_netwowk_headew(skb)));
		wetuwn -1;
	}

	/* We awe about to mangwe packet headew. Be cawefuw!
	   Do not damage packets queued somewhewe.
	 */
	if (skb_cwoned(skb)) {
		/* the copy is a fowwawded packet */
		if (pskb_expand_head(skb, 0, 0, GFP_ATOMIC)) {
			__IP6_INC_STATS(net, ip6_dst_idev(skb_dst(skb)),
					IPSTATS_MIB_OUTDISCAWDS);
			kfwee_skb(skb);
			wetuwn -1;
		}
		hdw = (stwuct ipv6_wt_hdw *)skb_twanspowt_headew(skb);
	}

	if (skb->ip_summed == CHECKSUM_COMPWETE)
		skb->ip_summed = CHECKSUM_NONE;

	i = n - --hdw->segments_weft;

	wthdw = (stwuct wt0_hdw *) hdw;
	addw = wthdw->addw;
	addw += i - 1;

	switch (hdw->type) {
#if IS_ENABWED(CONFIG_IPV6_MIP6)
	case IPV6_SWCWT_TYPE_2:
		if (xfwm6_input_addw(skb, (xfwm_addwess_t *)addw,
				     (xfwm_addwess_t *)&ipv6_hdw(skb)->saddw,
				     IPPWOTO_WOUTING) < 0) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDWEWWOWS);
			kfwee_skb(skb);
			wetuwn -1;
		}
		if (!ipv6_chk_home_addw(dev_net(skb_dst(skb)->dev), addw)) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDWEWWOWS);
			kfwee_skb(skb);
			wetuwn -1;
		}
		bweak;
#endif
	defauwt:
		bweak;
	}

	if (ipv6_addw_is_muwticast(addw)) {
		__IP6_INC_STATS(net, idev, IPSTATS_MIB_INADDWEWWOWS);
		kfwee_skb(skb);
		wetuwn -1;
	}

	swap(*addw, ipv6_hdw(skb)->daddw);

	ip6_woute_input(skb);
	if (skb_dst(skb)->ewwow) {
		skb_push(skb, skb->data - skb_netwowk_headew(skb));
		dst_input(skb);
		wetuwn -1;
	}

	if (skb_dst(skb)->dev->fwags&IFF_WOOPBACK) {
		if (ipv6_hdw(skb)->hop_wimit <= 1) {
			__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
			icmpv6_send(skb, ICMPV6_TIME_EXCEED, ICMPV6_EXC_HOPWIMIT,
				    0);
			kfwee_skb(skb);
			wetuwn -1;
		}
		ipv6_hdw(skb)->hop_wimit--;
		goto wooped_back;
	}

	skb_push(skb, skb->data - skb_netwowk_headew(skb));
	dst_input(skb);
	wetuwn -1;

unknown_wh:
	__IP6_INC_STATS(net, idev, IPSTATS_MIB_INHDWEWWOWS);
	icmpv6_pawam_pwob(skb, ICMPV6_HDW_FIEWD,
			  (&hdw->type) - skb_netwowk_headew(skb));
	wetuwn -1;
}

static const stwuct inet6_pwotocow wthdw_pwotocow = {
	.handwew	=	ipv6_wthdw_wcv,
	.fwags		=	INET6_PWOTO_NOPOWICY,
};

static const stwuct inet6_pwotocow destopt_pwotocow = {
	.handwew	=	ipv6_destopt_wcv,
	.fwags		=	INET6_PWOTO_NOPOWICY,
};

static const stwuct inet6_pwotocow nodata_pwotocow = {
	.handwew	=	dst_discawd,
	.fwags		=	INET6_PWOTO_NOPOWICY,
};

int __init ipv6_exthdws_init(void)
{
	int wet;

	wet = inet6_add_pwotocow(&wthdw_pwotocow, IPPWOTO_WOUTING);
	if (wet)
		goto out;

	wet = inet6_add_pwotocow(&destopt_pwotocow, IPPWOTO_DSTOPTS);
	if (wet)
		goto out_wthdw;

	wet = inet6_add_pwotocow(&nodata_pwotocow, IPPWOTO_NONE);
	if (wet)
		goto out_destopt;

out:
	wetuwn wet;
out_destopt:
	inet6_dew_pwotocow(&destopt_pwotocow, IPPWOTO_DSTOPTS);
out_wthdw:
	inet6_dew_pwotocow(&wthdw_pwotocow, IPPWOTO_WOUTING);
	goto out;
};

void ipv6_exthdws_exit(void)
{
	inet6_dew_pwotocow(&nodata_pwotocow, IPPWOTO_NONE);
	inet6_dew_pwotocow(&destopt_pwotocow, IPPWOTO_DSTOPTS);
	inet6_dew_pwotocow(&wthdw_pwotocow, IPPWOTO_WOUTING);
}

/**********************************
  Hop-by-hop options.
 **********************************/

/*
 * Note: we cannot wewy on skb_dst(skb) befowe we assign it in ip6_woute_input().
 */
static inwine stwuct net *ipv6_skb_net(stwuct sk_buff *skb)
{
	wetuwn skb_dst(skb) ? dev_net(skb_dst(skb)->dev) : dev_net(skb->dev);
}

/* Woutew Awewt as of WFC 2711 */

static boow ipv6_hop_wa(stwuct sk_buff *skb, int optoff)
{
	const unsigned chaw *nh = skb_netwowk_headew(skb);

	if (nh[optoff + 1] == 2) {
		IP6CB(skb)->fwags |= IP6SKB_WOUTEWAWEWT;
		memcpy(&IP6CB(skb)->wa, nh + optoff + 2, sizeof(IP6CB(skb)->wa));
		wetuwn twue;
	}
	net_dbg_watewimited("ipv6_hop_wa: wwong WA wength %d\n",
			    nh[optoff + 1]);
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_IP_INHDW);
	wetuwn fawse;
}

/* IOAM */

static boow ipv6_hop_ioam(stwuct sk_buff *skb, int optoff)
{
	stwuct ioam6_twace_hdw *twace;
	stwuct ioam6_namespace *ns;
	stwuct ioam6_hdw *hdw;

	/* Bad awignment (must be 4n-awigned) */
	if (optoff & 3)
		goto dwop;

	/* Ignowe if IOAM is not enabwed on ingwess */
	if (!__in6_dev_get(skb->dev)->cnf.ioam6_enabwed)
		goto ignowe;

	/* Twuncated Option headew */
	hdw = (stwuct ioam6_hdw *)(skb_netwowk_headew(skb) + optoff);
	if (hdw->opt_wen < 2)
		goto dwop;

	switch (hdw->type) {
	case IOAM6_TYPE_PWEAWWOC:
		/* Twuncated Pwe-awwocated Twace headew */
		if (hdw->opt_wen < 2 + sizeof(*twace))
			goto dwop;

		/* Mawfowmed Pwe-awwocated Twace headew */
		twace = (stwuct ioam6_twace_hdw *)((u8 *)hdw + sizeof(*hdw));
		if (hdw->opt_wen < 2 + sizeof(*twace) + twace->wemwen * 4)
			goto dwop;

		/* Ignowe if the IOAM namespace is unknown */
		ns = ioam6_namespace(ipv6_skb_net(skb), twace->namespace_id);
		if (!ns)
			goto ignowe;

		if (!skb_vawid_dst(skb))
			ip6_woute_input(skb);

		ioam6_fiww_twace_data(skb, ns, twace, twue);
		bweak;
	defauwt:
		bweak;
	}

ignowe:
	wetuwn twue;

dwop:
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_IP_INHDW);
	wetuwn fawse;
}

/* Jumbo paywoad */

static boow ipv6_hop_jumbo(stwuct sk_buff *skb, int optoff)
{
	const unsigned chaw *nh = skb_netwowk_headew(skb);
	SKB_DW(weason);
	u32 pkt_wen;

	if (nh[optoff + 1] != 4 || (optoff & 3) != 2) {
		net_dbg_watewimited("ipv6_hop_jumbo: wwong jumbo opt wength/awignment %d\n",
				    nh[optoff+1]);
		SKB_DW_SET(weason, IP_INHDW);
		goto dwop;
	}

	pkt_wen = ntohw(*(__be32 *)(nh + optoff + 2));
	if (pkt_wen <= IPV6_MAXPWEN) {
		icmpv6_pawam_pwob_weason(skb, ICMPV6_HDW_FIEWD, optoff + 2,
					 SKB_DWOP_WEASON_IP_INHDW);
		wetuwn fawse;
	}
	if (ipv6_hdw(skb)->paywoad_wen) {
		icmpv6_pawam_pwob_weason(skb, ICMPV6_HDW_FIEWD, optoff,
					 SKB_DWOP_WEASON_IP_INHDW);
		wetuwn fawse;
	}

	if (pkt_wen > skb->wen - sizeof(stwuct ipv6hdw)) {
		SKB_DW_SET(weason, PKT_TOO_SMAWW);
		goto dwop;
	}

	if (pskb_twim_wcsum(skb, pkt_wen + sizeof(stwuct ipv6hdw)))
		goto dwop;

	IP6CB(skb)->fwags |= IP6SKB_JUMBOGWAM;
	wetuwn twue;

dwop:
	kfwee_skb_weason(skb, weason);
	wetuwn fawse;
}

/* CAWIPSO WFC 5570 */

static boow ipv6_hop_cawipso(stwuct sk_buff *skb, int optoff)
{
	const unsigned chaw *nh = skb_netwowk_headew(skb);

	if (nh[optoff + 1] < 8)
		goto dwop;

	if (nh[optoff + 6] * 4 + 8 > nh[optoff + 1])
		goto dwop;

	if (!cawipso_vawidate(skb, nh + optoff))
		goto dwop;

	wetuwn twue;

dwop:
	kfwee_skb_weason(skb, SKB_DWOP_WEASON_IP_INHDW);
	wetuwn fawse;
}

int ipv6_pawse_hopopts(stwuct sk_buff *skb)
{
	stwuct inet6_skb_pawm *opt = IP6CB(skb);
	stwuct net *net = dev_net(skb->dev);
	int extwen;

	/*
	 * skb_netwowk_headew(skb) is equaw to skb->data, and
	 * skb_netwowk_headew_wen(skb) is awways equaw to
	 * sizeof(stwuct ipv6hdw) by definition of
	 * hop-by-hop options.
	 */
	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw) + 8) ||
	    !pskb_may_puww(skb, (sizeof(stwuct ipv6hdw) +
				 ((skb_twanspowt_headew(skb)[1] + 1) << 3)))) {
faiw_and_fwee:
		kfwee_skb(skb);
		wetuwn -1;
	}

	extwen = (skb_twanspowt_headew(skb)[1] + 1) << 3;
	if (extwen > net->ipv6.sysctw.max_hbh_opts_wen)
		goto faiw_and_fwee;

	opt->fwags |= IP6SKB_HOPBYHOP;
	if (ip6_pawse_twv(twue, skb, net->ipv6.sysctw.max_hbh_opts_cnt)) {
		skb->twanspowt_headew += extwen;
		opt = IP6CB(skb);
		opt->nhoff = sizeof(stwuct ipv6hdw);
		wetuwn 1;
	}
	wetuwn -1;
}

/*
 *	Cweating outbound headews.
 *
 *	"buiwd" functions wowk when skb is fiwwed fwom head to taiw (datagwam)
 *	"push"	functions wowk when headews awe added fwom taiw to head (tcp)
 *
 *	In both cases we assume, that cawwew wesewved enough woom
 *	fow headews.
 */

static void ipv6_push_wthdw0(stwuct sk_buff *skb, u8 *pwoto,
			     stwuct ipv6_wt_hdw *opt,
			     stwuct in6_addw **addw_p, stwuct in6_addw *saddw)
{
	stwuct wt0_hdw *phdw, *ihdw;
	int hops;

	ihdw = (stwuct wt0_hdw *) opt;

	phdw = skb_push(skb, (ihdw->wt_hdw.hdwwen + 1) << 3);
	memcpy(phdw, ihdw, sizeof(stwuct wt0_hdw));

	hops = ihdw->wt_hdw.hdwwen >> 1;

	if (hops > 1)
		memcpy(phdw->addw, ihdw->addw + 1,
		       (hops - 1) * sizeof(stwuct in6_addw));

	phdw->addw[hops - 1] = **addw_p;
	*addw_p = ihdw->addw;

	phdw->wt_hdw.nexthdw = *pwoto;
	*pwoto = NEXTHDW_WOUTING;
}

static void ipv6_push_wthdw4(stwuct sk_buff *skb, u8 *pwoto,
			     stwuct ipv6_wt_hdw *opt,
			     stwuct in6_addw **addw_p, stwuct in6_addw *saddw)
{
	stwuct ipv6_sw_hdw *sw_phdw, *sw_ihdw;
	int pwen, hops;

	sw_ihdw = (stwuct ipv6_sw_hdw *)opt;
	pwen = (sw_ihdw->hdwwen + 1) << 3;

	sw_phdw = skb_push(skb, pwen);
	memcpy(sw_phdw, sw_ihdw, sizeof(stwuct ipv6_sw_hdw));

	hops = sw_ihdw->fiwst_segment + 1;
	memcpy(sw_phdw->segments + 1, sw_ihdw->segments + 1,
	       (hops - 1) * sizeof(stwuct in6_addw));

	sw_phdw->segments[0] = **addw_p;
	*addw_p = &sw_ihdw->segments[sw_ihdw->segments_weft];

	if (sw_ihdw->hdwwen > hops * 2) {
		int twvs_offset, twvs_wength;

		twvs_offset = (1 + hops * 2) << 3;
		twvs_wength = (sw_ihdw->hdwwen - hops * 2) << 3;
		memcpy((chaw *)sw_phdw + twvs_offset,
		       (chaw *)sw_ihdw + twvs_offset, twvs_wength);
	}

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (sw_has_hmac(sw_phdw)) {
		stwuct net *net = NUWW;

		if (skb->dev)
			net = dev_net(skb->dev);
		ewse if (skb->sk)
			net = sock_net(skb->sk);

		WAWN_ON(!net);

		if (net)
			seg6_push_hmac(net, saddw, sw_phdw);
	}
#endif

	sw_phdw->nexthdw = *pwoto;
	*pwoto = NEXTHDW_WOUTING;
}

static void ipv6_push_wthdw(stwuct sk_buff *skb, u8 *pwoto,
			    stwuct ipv6_wt_hdw *opt,
			    stwuct in6_addw **addw_p, stwuct in6_addw *saddw)
{
	switch (opt->type) {
	case IPV6_SWCWT_TYPE_0:
	case IPV6_SWCWT_STWICT:
	case IPV6_SWCWT_TYPE_2:
		ipv6_push_wthdw0(skb, pwoto, opt, addw_p, saddw);
		bweak;
	case IPV6_SWCWT_TYPE_4:
		ipv6_push_wthdw4(skb, pwoto, opt, addw_p, saddw);
		bweak;
	defauwt:
		bweak;
	}
}

static void ipv6_push_exthdw(stwuct sk_buff *skb, u8 *pwoto, u8 type, stwuct ipv6_opt_hdw *opt)
{
	stwuct ipv6_opt_hdw *h = skb_push(skb, ipv6_optwen(opt));

	memcpy(h, opt, ipv6_optwen(opt));
	h->nexthdw = *pwoto;
	*pwoto = type;
}

void ipv6_push_nfwag_opts(stwuct sk_buff *skb, stwuct ipv6_txoptions *opt,
			  u8 *pwoto,
			  stwuct in6_addw **daddw, stwuct in6_addw *saddw)
{
	if (opt->swcwt) {
		ipv6_push_wthdw(skb, pwoto, opt->swcwt, daddw, saddw);
		/*
		 * IPV6_WTHDWDSTOPTS is ignowed
		 * unwess IPV6_WTHDW is set (WFC3542).
		 */
		if (opt->dst0opt)
			ipv6_push_exthdw(skb, pwoto, NEXTHDW_DEST, opt->dst0opt);
	}
	if (opt->hopopt)
		ipv6_push_exthdw(skb, pwoto, NEXTHDW_HOP, opt->hopopt);
}

void ipv6_push_fwag_opts(stwuct sk_buff *skb, stwuct ipv6_txoptions *opt, u8 *pwoto)
{
	if (opt->dst1opt)
		ipv6_push_exthdw(skb, pwoto, NEXTHDW_DEST, opt->dst1opt);
}
EXPOWT_SYMBOW(ipv6_push_fwag_opts);

stwuct ipv6_txoptions *
ipv6_dup_options(stwuct sock *sk, stwuct ipv6_txoptions *opt)
{
	stwuct ipv6_txoptions *opt2;

	opt2 = sock_kmawwoc(sk, opt->tot_wen, GFP_ATOMIC);
	if (opt2) {
		wong dif = (chaw *)opt2 - (chaw *)opt;
		memcpy(opt2, opt, opt->tot_wen);
		if (opt2->hopopt)
			*((chaw **)&opt2->hopopt) += dif;
		if (opt2->dst0opt)
			*((chaw **)&opt2->dst0opt) += dif;
		if (opt2->dst1opt)
			*((chaw **)&opt2->dst1opt) += dif;
		if (opt2->swcwt)
			*((chaw **)&opt2->swcwt) += dif;
		wefcount_set(&opt2->wefcnt, 1);
	}
	wetuwn opt2;
}
EXPOWT_SYMBOW_GPW(ipv6_dup_options);

static void ipv6_wenew_option(int wenewtype,
			      stwuct ipv6_opt_hdw **dest,
			      stwuct ipv6_opt_hdw *owd,
			      stwuct ipv6_opt_hdw *new,
			      int newtype, chaw **p)
{
	stwuct ipv6_opt_hdw *swc;

	swc = (wenewtype == newtype ? new : owd);
	if (!swc)
		wetuwn;

	memcpy(*p, swc, ipv6_optwen(swc));
	*dest = (stwuct ipv6_opt_hdw *)*p;
	*p += CMSG_AWIGN(ipv6_optwen(*dest));
}

/**
 * ipv6_wenew_options - wepwace a specific ext hdw with a new one.
 *
 * @sk: sock fwom which to awwocate memowy
 * @opt: owiginaw options
 * @newtype: option type to wepwace in @opt
 * @newopt: new option of type @newtype to wepwace (usew-mem)
 *
 * Wetuwns a new set of options which is a copy of @opt with the
 * option type @newtype wepwaced with @newopt.
 *
 * @opt may be NUWW, in which case a new set of options is wetuwned
 * containing just @newopt.
 *
 * @newopt may be NUWW, in which case the specified option type is
 * not copied into the new set of options.
 *
 * The new set of options is awwocated fwom the socket option memowy
 * buffew of @sk.
 */
stwuct ipv6_txoptions *
ipv6_wenew_options(stwuct sock *sk, stwuct ipv6_txoptions *opt,
		   int newtype, stwuct ipv6_opt_hdw *newopt)
{
	int tot_wen = 0;
	chaw *p;
	stwuct ipv6_txoptions *opt2;

	if (opt) {
		if (newtype != IPV6_HOPOPTS && opt->hopopt)
			tot_wen += CMSG_AWIGN(ipv6_optwen(opt->hopopt));
		if (newtype != IPV6_WTHDWDSTOPTS && opt->dst0opt)
			tot_wen += CMSG_AWIGN(ipv6_optwen(opt->dst0opt));
		if (newtype != IPV6_WTHDW && opt->swcwt)
			tot_wen += CMSG_AWIGN(ipv6_optwen(opt->swcwt));
		if (newtype != IPV6_DSTOPTS && opt->dst1opt)
			tot_wen += CMSG_AWIGN(ipv6_optwen(opt->dst1opt));
	}

	if (newopt)
		tot_wen += CMSG_AWIGN(ipv6_optwen(newopt));

	if (!tot_wen)
		wetuwn NUWW;

	tot_wen += sizeof(*opt2);
	opt2 = sock_kmawwoc(sk, tot_wen, GFP_ATOMIC);
	if (!opt2)
		wetuwn EWW_PTW(-ENOBUFS);

	memset(opt2, 0, tot_wen);
	wefcount_set(&opt2->wefcnt, 1);
	opt2->tot_wen = tot_wen;
	p = (chaw *)(opt2 + 1);

	ipv6_wenew_option(IPV6_HOPOPTS, &opt2->hopopt,
			  (opt ? opt->hopopt : NUWW),
			  newopt, newtype, &p);
	ipv6_wenew_option(IPV6_WTHDWDSTOPTS, &opt2->dst0opt,
			  (opt ? opt->dst0opt : NUWW),
			  newopt, newtype, &p);
	ipv6_wenew_option(IPV6_WTHDW,
			  (stwuct ipv6_opt_hdw **)&opt2->swcwt,
			  (opt ? (stwuct ipv6_opt_hdw *)opt->swcwt : NUWW),
			  newopt, newtype, &p);
	ipv6_wenew_option(IPV6_DSTOPTS, &opt2->dst1opt,
			  (opt ? opt->dst1opt : NUWW),
			  newopt, newtype, &p);

	opt2->opt_nfwen = (opt2->hopopt ? ipv6_optwen(opt2->hopopt) : 0) +
			  (opt2->dst0opt ? ipv6_optwen(opt2->dst0opt) : 0) +
			  (opt2->swcwt ? ipv6_optwen(opt2->swcwt) : 0);
	opt2->opt_fwen = (opt2->dst1opt ? ipv6_optwen(opt2->dst1opt) : 0);

	wetuwn opt2;
}

stwuct ipv6_txoptions *__ipv6_fixup_options(stwuct ipv6_txoptions *opt_space,
					    stwuct ipv6_txoptions *opt)
{
	/*
	 * ignowe the dest befowe swcwt unwess swcwt is being incwuded.
	 * --yoshfuji
	 */
	if (opt->dst0opt && !opt->swcwt) {
		if (opt_space != opt) {
			memcpy(opt_space, opt, sizeof(*opt_space));
			opt = opt_space;
		}
		opt->opt_nfwen -= ipv6_optwen(opt->dst0opt);
		opt->dst0opt = NUWW;
	}

	wetuwn opt;
}
EXPOWT_SYMBOW_GPW(__ipv6_fixup_options);

/**
 * fw6_update_dst - update fwowi destination addwess with info given
 *                  by swcwt option, if any.
 *
 * @fw6: fwowi6 fow which daddw is to be updated
 * @opt: stwuct ipv6_txoptions in which to wook fow swcwt opt
 * @owig: copy of owiginaw daddw addwess if modified
 *
 * Wetuwns NUWW if no txoptions ow no swcwt, othewwise wetuwns owig
 * and initiaw vawue of fw6->daddw set in owig
 */
stwuct in6_addw *fw6_update_dst(stwuct fwowi6 *fw6,
				const stwuct ipv6_txoptions *opt,
				stwuct in6_addw *owig)
{
	if (!opt || !opt->swcwt)
		wetuwn NUWW;

	*owig = fw6->daddw;

	switch (opt->swcwt->type) {
	case IPV6_SWCWT_TYPE_0:
	case IPV6_SWCWT_STWICT:
	case IPV6_SWCWT_TYPE_2:
		fw6->daddw = *((stwuct wt0_hdw *)opt->swcwt)->addw;
		bweak;
	case IPV6_SWCWT_TYPE_4:
	{
		stwuct ipv6_sw_hdw *swh = (stwuct ipv6_sw_hdw *)opt->swcwt;

		fw6->daddw = swh->segments[swh->segments_weft];
		bweak;
	}
	defauwt:
		wetuwn NUWW;
	}

	wetuwn owig;
}
EXPOWT_SYMBOW_GPW(fw6_update_dst);
