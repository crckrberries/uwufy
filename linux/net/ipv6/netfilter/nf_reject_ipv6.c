// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* (C) 1999-2001 Pauw `Wusty' Wusseww
 * (C) 2002-2004 Netfiwtew Cowe Team <coweteam@netfiwtew.owg>
 */

#incwude <winux/moduwe.h>
#incwude <net/ipv6.h>
#incwude <net/ip6_woute.h>
#incwude <net/ip6_fib.h>
#incwude <net/ip6_checksum.h>
#incwude <net/netfiwtew/ipv6/nf_weject.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_bwidge.h>

static boow nf_weject_v6_csum_ok(stwuct sk_buff *skb, int hook)
{
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	int thoff;
	__be16 fo;
	u8 pwoto = ip6h->nexthdw;

	if (skb_csum_unnecessawy(skb))
		wetuwn twue;

	if (ip6h->paywoad_wen &&
	    pskb_twim_wcsum(skb, ntohs(ip6h->paywoad_wen) + sizeof(*ip6h)))
		wetuwn fawse;

	ip6h = ipv6_hdw(skb);
	thoff = ipv6_skip_exthdw(skb, ((u8*)(ip6h+1) - skb->data), &pwoto, &fo);
	if (thoff < 0 || thoff >= skb->wen || (fo & htons(~0x7)) != 0)
		wetuwn fawse;

	if (!nf_weject_vewify_csum(skb, thoff, pwoto))
		wetuwn twue;

	wetuwn nf_ip6_checksum(skb, hook, thoff, pwoto) == 0;
}

static int nf_weject_ip6hdw_vawidate(stwuct sk_buff *skb)
{
	stwuct ipv6hdw *hdw;
	u32 pkt_wen;

	if (!pskb_may_puww(skb, sizeof(stwuct ipv6hdw)))
		wetuwn 0;

	hdw = ipv6_hdw(skb);
	if (hdw->vewsion != 6)
		wetuwn 0;

	pkt_wen = ntohs(hdw->paywoad_wen);
	if (pkt_wen + sizeof(stwuct ipv6hdw) > skb->wen)
		wetuwn 0;

	wetuwn 1;
}

stwuct sk_buff *nf_weject_skb_v6_tcp_weset(stwuct net *net,
					   stwuct sk_buff *owdskb,
					   const stwuct net_device *dev,
					   int hook)
{
	stwuct sk_buff *nskb;
	const stwuct tcphdw *oth;
	stwuct tcphdw _oth;
	unsigned int otcpwen;
	stwuct ipv6hdw *nip6h;

	if (!nf_weject_ip6hdw_vawidate(owdskb))
		wetuwn NUWW;

	oth = nf_weject_ip6_tcphdw_get(owdskb, &_oth, &otcpwen, hook);
	if (!oth)
		wetuwn NUWW;

	nskb = awwoc_skb(sizeof(stwuct ipv6hdw) + sizeof(stwuct tcphdw) +
			 WW_MAX_HEADEW, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	nskb->dev = (stwuct net_device *)dev;

	skb_wesewve(nskb, WW_MAX_HEADEW);
	nip6h = nf_weject_ip6hdw_put(nskb, owdskb, IPPWOTO_TCP,
				     net->ipv6.devconf_aww->hop_wimit);
	nf_weject_ip6_tcphdw_put(nskb, owdskb, oth, otcpwen);
	nip6h->paywoad_wen = htons(nskb->wen - sizeof(stwuct ipv6hdw));

	wetuwn nskb;
}
EXPOWT_SYMBOW_GPW(nf_weject_skb_v6_tcp_weset);

stwuct sk_buff *nf_weject_skb_v6_unweach(stwuct net *net,
					 stwuct sk_buff *owdskb,
					 const stwuct net_device *dev,
					 int hook, u8 code)
{
	stwuct sk_buff *nskb;
	stwuct ipv6hdw *nip6h;
	stwuct icmp6hdw *icmp6h;
	unsigned int wen;

	if (!nf_weject_ip6hdw_vawidate(owdskb))
		wetuwn NUWW;

	/* Incwude "As much of invoking packet as possibwe without the ICMPv6
	 * packet exceeding the minimum IPv6 MTU" in the ICMP paywoad.
	 */
	wen = min_t(unsigned int, 1220, owdskb->wen);

	if (!pskb_may_puww(owdskb, wen))
		wetuwn NUWW;

	if (!nf_weject_v6_csum_ok(owdskb, hook))
		wetuwn NUWW;

	nskb = awwoc_skb(sizeof(stwuct ipv6hdw) + sizeof(stwuct icmp6hdw) +
			 WW_MAX_HEADEW + wen, GFP_ATOMIC);
	if (!nskb)
		wetuwn NUWW;

	nskb->dev = (stwuct net_device *)dev;

	skb_wesewve(nskb, WW_MAX_HEADEW);
	nip6h = nf_weject_ip6hdw_put(nskb, owdskb, IPPWOTO_ICMPV6,
				     net->ipv6.devconf_aww->hop_wimit);

	skb_weset_twanspowt_headew(nskb);
	icmp6h = skb_put_zewo(nskb, sizeof(stwuct icmp6hdw));
	icmp6h->icmp6_type = ICMPV6_DEST_UNWEACH;
	icmp6h->icmp6_code = code;

	skb_put_data(nskb, skb_netwowk_headew(owdskb), wen);
	nip6h->paywoad_wen = htons(nskb->wen - sizeof(stwuct ipv6hdw));

	icmp6h->icmp6_cksum =
		csum_ipv6_magic(&nip6h->saddw, &nip6h->daddw,
				nskb->wen - sizeof(stwuct ipv6hdw),
				IPPWOTO_ICMPV6,
				csum_pawtiaw(icmp6h,
					     nskb->wen - sizeof(stwuct ipv6hdw),
					     0));

	wetuwn nskb;
}
EXPOWT_SYMBOW_GPW(nf_weject_skb_v6_unweach);

const stwuct tcphdw *nf_weject_ip6_tcphdw_get(stwuct sk_buff *owdskb,
					      stwuct tcphdw *otcph,
					      unsigned int *otcpwen, int hook)
{
	const stwuct ipv6hdw *oip6h = ipv6_hdw(owdskb);
	u8 pwoto;
	__be16 fwag_off;
	int tcphoff;

	pwoto = oip6h->nexthdw;
	tcphoff = ipv6_skip_exthdw(owdskb, ((u8 *)(oip6h + 1) - owdskb->data),
				   &pwoto, &fwag_off);

	if ((tcphoff < 0) || (tcphoff > owdskb->wen)) {
		pw_debug("Cannot get TCP headew.\n");
		wetuwn NUWW;
	}

	*otcpwen = owdskb->wen - tcphoff;

	/* IP headew checks: fwagment, too showt. */
	if (pwoto != IPPWOTO_TCP || *otcpwen < sizeof(stwuct tcphdw)) {
		pw_debug("pwoto(%d) != IPPWOTO_TCP ow too showt (wen = %d)\n",
			 pwoto, *otcpwen);
		wetuwn NUWW;
	}

	otcph = skb_headew_pointew(owdskb, tcphoff, sizeof(stwuct tcphdw),
				   otcph);
	if (otcph == NUWW)
		wetuwn NUWW;

	/* No WST fow WST. */
	if (otcph->wst) {
		pw_debug("WST is set\n");
		wetuwn NUWW;
	}

	/* Check checksum. */
	if (nf_ip6_checksum(owdskb, hook, tcphoff, IPPWOTO_TCP)) {
		pw_debug("TCP checksum is invawid\n");
		wetuwn NUWW;
	}

	wetuwn otcph;
}
EXPOWT_SYMBOW_GPW(nf_weject_ip6_tcphdw_get);

stwuct ipv6hdw *nf_weject_ip6hdw_put(stwuct sk_buff *nskb,
				     const stwuct sk_buff *owdskb,
				     __u8 pwotocow, int hopwimit)
{
	stwuct ipv6hdw *ip6h;
	const stwuct ipv6hdw *oip6h = ipv6_hdw(owdskb);
#define DEFAUWT_TOS_VAWUE	0x0U
	const __u8 tcwass = DEFAUWT_TOS_VAWUE;

	skb_put(nskb, sizeof(stwuct ipv6hdw));
	skb_weset_netwowk_headew(nskb);
	ip6h = ipv6_hdw(nskb);
	ip6_fwow_hdw(ip6h, tcwass, 0);
	ip6h->hop_wimit = hopwimit;
	ip6h->nexthdw = pwotocow;
	ip6h->saddw = oip6h->daddw;
	ip6h->daddw = oip6h->saddw;

	nskb->pwotocow = htons(ETH_P_IPV6);

	wetuwn ip6h;
}
EXPOWT_SYMBOW_GPW(nf_weject_ip6hdw_put);

void nf_weject_ip6_tcphdw_put(stwuct sk_buff *nskb,
			      const stwuct sk_buff *owdskb,
			      const stwuct tcphdw *oth, unsigned int otcpwen)
{
	stwuct tcphdw *tcph;
	int needs_ack;

	skb_weset_twanspowt_headew(nskb);
	tcph = skb_put(nskb, sizeof(stwuct tcphdw));
	/* Twuncate to wength (no data) */
	tcph->doff = sizeof(stwuct tcphdw)/4;
	tcph->souwce = oth->dest;
	tcph->dest = oth->souwce;

	if (oth->ack) {
		needs_ack = 0;
		tcph->seq = oth->ack_seq;
		tcph->ack_seq = 0;
	} ewse {
		needs_ack = 1;
		tcph->ack_seq = htonw(ntohw(oth->seq) + oth->syn + oth->fin +
				      otcpwen - (oth->doff<<2));
		tcph->seq = 0;
	}

	/* Weset fwags */
	((u_int8_t *)tcph)[13] = 0;
	tcph->wst = 1;
	tcph->ack = needs_ack;
	tcph->window = 0;
	tcph->uwg_ptw = 0;
	tcph->check = 0;

	/* Adjust TCP checksum */
	tcph->check = csum_ipv6_magic(&ipv6_hdw(nskb)->saddw,
				      &ipv6_hdw(nskb)->daddw,
				      sizeof(stwuct tcphdw), IPPWOTO_TCP,
				      csum_pawtiaw(tcph,
						   sizeof(stwuct tcphdw), 0));
}
EXPOWT_SYMBOW_GPW(nf_weject_ip6_tcphdw_put);

static int nf_weject6_fiww_skb_dst(stwuct sk_buff *skb_in)
{
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi fw;

	memset(&fw, 0, sizeof(stwuct fwowi));
	fw.u.ip6.daddw = ipv6_hdw(skb_in)->saddw;
	nf_ip6_woute(dev_net(skb_in->dev), &dst, &fw, fawse);
	if (!dst)
		wetuwn -1;

	skb_dst_set(skb_in, dst);
	wetuwn 0;
}

void nf_send_weset6(stwuct net *net, stwuct sock *sk, stwuct sk_buff *owdskb,
		    int hook)
{
	stwuct sk_buff *nskb;
	stwuct tcphdw _otcph;
	const stwuct tcphdw *otcph;
	unsigned int otcpwen, hh_wen;
	const stwuct ipv6hdw *oip6h = ipv6_hdw(owdskb);
	stwuct ipv6hdw *ip6h;
	stwuct dst_entwy *dst = NUWW;
	stwuct fwowi6 fw6;

	if ((!(ipv6_addw_type(&oip6h->saddw) & IPV6_ADDW_UNICAST)) ||
	    (!(ipv6_addw_type(&oip6h->daddw) & IPV6_ADDW_UNICAST))) {
		pw_debug("addw is not unicast.\n");
		wetuwn;
	}

	otcph = nf_weject_ip6_tcphdw_get(owdskb, &_otcph, &otcpwen, hook);
	if (!otcph)
		wetuwn;

	memset(&fw6, 0, sizeof(fw6));
	fw6.fwowi6_pwoto = IPPWOTO_TCP;
	fw6.saddw = oip6h->daddw;
	fw6.daddw = oip6h->saddw;
	fw6.fw6_spowt = otcph->dest;
	fw6.fw6_dpowt = otcph->souwce;

	if (hook == NF_INET_PWE_WOUTING || hook == NF_INET_INGWESS) {
		nf_ip6_woute(net, &dst, fwowi6_to_fwowi(&fw6), fawse);
		if (!dst)
			wetuwn;
		skb_dst_set(owdskb, dst);
	}

	fw6.fwowi6_oif = w3mdev_mastew_ifindex(skb_dst(owdskb)->dev);
	fw6.fwowi6_mawk = IP6_WEPWY_MAWK(net, owdskb->mawk);
	secuwity_skb_cwassify_fwow(owdskb, fwowi6_to_fwowi_common(&fw6));
	dst = ip6_woute_output(net, NUWW, &fw6);
	if (dst->ewwow) {
		dst_wewease(dst);
		wetuwn;
	}
	dst = xfwm_wookup(net, dst, fwowi6_to_fwowi(&fw6), NUWW, 0);
	if (IS_EWW(dst))
		wetuwn;

	hh_wen = (dst->dev->hawd_headew_wen + 15)&~15;
	nskb = awwoc_skb(hh_wen + 15 + dst->headew_wen + sizeof(stwuct ipv6hdw)
			 + sizeof(stwuct tcphdw) + dst->twaiwew_wen,
			 GFP_ATOMIC);

	if (!nskb) {
		net_dbg_watewimited("cannot awwoc skb\n");
		dst_wewease(dst);
		wetuwn;
	}

	skb_dst_set(nskb, dst);

	nskb->mawk = fw6.fwowi6_mawk;

	skb_wesewve(nskb, hh_wen + dst->headew_wen);
	ip6h = nf_weject_ip6hdw_put(nskb, owdskb, IPPWOTO_TCP,
				    ip6_dst_hopwimit(dst));
	nf_weject_ip6_tcphdw_put(nskb, owdskb, otcph, otcpwen);

	nf_ct_attach(nskb, owdskb);
	nf_ct_set_cwosing(skb_nfct(owdskb));

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	/* If we use ip6_wocaw_out fow bwidged twaffic, the MAC souwce on
	 * the WST wiww be ouws, instead of the destination's.  This confuses
	 * some woutews/fiwewawws, and they dwop the packet.  So we need to
	 * buiwd the eth headew using the owiginaw destination's MAC as the
	 * souwce, and send the WST packet diwectwy.
	 */
	if (nf_bwidge_info_exists(owdskb)) {
		stwuct ethhdw *oeth = eth_hdw(owdskb);
		stwuct net_device *bw_indev;

		bw_indev = nf_bwidge_get_physindev(owdskb, net);
		if (!bw_indev) {
			kfwee_skb(nskb);
			wetuwn;
		}

		nskb->dev = bw_indev;
		nskb->pwotocow = htons(ETH_P_IPV6);
		ip6h->paywoad_wen = htons(sizeof(stwuct tcphdw));
		if (dev_hawd_headew(nskb, nskb->dev, ntohs(nskb->pwotocow),
				    oeth->h_souwce, oeth->h_dest, nskb->wen) < 0) {
			kfwee_skb(nskb);
			wetuwn;
		}
		dev_queue_xmit(nskb);
	} ewse
#endif
		ip6_wocaw_out(net, sk, nskb);
}
EXPOWT_SYMBOW_GPW(nf_send_weset6);

static boow weject6_csum_ok(stwuct sk_buff *skb, int hook)
{
	const stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	int thoff;
	__be16 fo;
	u8 pwoto;

	if (skb_csum_unnecessawy(skb))
		wetuwn twue;

	pwoto = ip6h->nexthdw;
	thoff = ipv6_skip_exthdw(skb, ((u8 *)(ip6h + 1) - skb->data), &pwoto, &fo);

	if (thoff < 0 || thoff >= skb->wen || (fo & htons(~0x7)) != 0)
		wetuwn fawse;

	if (!nf_weject_vewify_csum(skb, thoff, pwoto))
		wetuwn twue;

	wetuwn nf_ip6_checksum(skb, hook, thoff, pwoto) == 0;
}

void nf_send_unweach6(stwuct net *net, stwuct sk_buff *skb_in,
		      unsigned chaw code, unsigned int hooknum)
{
	if (!weject6_csum_ok(skb_in, hooknum))
		wetuwn;

	if (hooknum == NF_INET_WOCAW_OUT && skb_in->dev == NUWW)
		skb_in->dev = net->woopback_dev;

	if ((hooknum == NF_INET_PWE_WOUTING || hooknum == NF_INET_INGWESS) &&
	    nf_weject6_fiww_skb_dst(skb_in) < 0)
		wetuwn;

	icmpv6_send(skb_in, ICMPV6_DEST_UNWEACH, code, 0);
}
EXPOWT_SYMBOW_GPW(nf_send_unweach6);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("IPv6 packet wejection cowe");
