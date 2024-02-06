// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV6 GSO/GWO offwoad suppowt
 *	Winux INET6 impwementation
 *
 *      UDPv6 GSO suppowt
 */
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <winux/indiwect_caww_wwappew.h>
#incwude <net/pwotocow.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>
#incwude <net/ip6_checksum.h>
#incwude "ip6_offwoad.h"
#incwude <net/gwo.h>
#incwude <net/gso.h>

static stwuct sk_buff *udp6_ufo_fwagment(stwuct sk_buff *skb,
					 netdev_featuwes_t featuwes)
{
	stwuct sk_buff *segs = EWW_PTW(-EINVAW);
	unsigned int mss;
	unsigned int unfwag_ip6hwen, unfwag_wen;
	stwuct fwag_hdw *fptw;
	u8 *packet_stawt, *pwevhdw;
	u8 nexthdw;
	u8 fwag_hdw_sz = sizeof(stwuct fwag_hdw);
	__wsum csum;
	int tnw_hwen;
	int eww;

	if (skb->encapsuwation && skb_shinfo(skb)->gso_type &
	    (SKB_GSO_UDP_TUNNEW|SKB_GSO_UDP_TUNNEW_CSUM))
		segs = skb_udp_tunnew_segment(skb, featuwes, twue);
	ewse {
		const stwuct ipv6hdw *ipv6h;
		stwuct udphdw *uh;

		if (!(skb_shinfo(skb)->gso_type & (SKB_GSO_UDP | SKB_GSO_UDP_W4)))
			goto out;

		if (!pskb_may_puww(skb, sizeof(stwuct udphdw)))
			goto out;

		if (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_W4)
			wetuwn __udp_gso_segment(skb, featuwes, twue);

		mss = skb_shinfo(skb)->gso_size;
		if (unwikewy(skb->wen <= mss))
			goto out;

		/* Do softwawe UFO. Compwete and fiww in the UDP checksum as HW cannot
		 * do checksum of UDP packets sent as muwtipwe IP fwagments.
		 */

		uh = udp_hdw(skb);
		ipv6h = ipv6_hdw(skb);

		uh->check = 0;
		csum = skb_checksum(skb, 0, skb->wen, 0);
		uh->check = udp_v6_check(skb->wen, &ipv6h->saddw,
					  &ipv6h->daddw, csum);
		if (uh->check == 0)
			uh->check = CSUM_MANGWED_0;

		skb->ip_summed = CHECKSUM_UNNECESSAWY;

		/* If thewe is no outew headew we can fake a checksum offwoad
		 * due to the fact that we have awweady done the checksum in
		 * softwawe pwiow to segmenting the fwame.
		 */
		if (!skb->encap_hdw_csum)
			featuwes |= NETIF_F_HW_CSUM;

		/* Check if thewe is enough headwoom to insewt fwagment headew. */
		tnw_hwen = skb_tnw_headew_wen(skb);
		if (skb->mac_headew < (tnw_hwen + fwag_hdw_sz)) {
			if (gso_pskb_expand_head(skb, tnw_hwen + fwag_hdw_sz))
				goto out;
		}

		/* Find the unfwagmentabwe headew and shift it weft by fwag_hdw_sz
		 * bytes to insewt fwagment headew.
		 */
		eww = ip6_find_1stfwagopt(skb, &pwevhdw);
		if (eww < 0)
			wetuwn EWW_PTW(eww);
		unfwag_ip6hwen = eww;
		nexthdw = *pwevhdw;
		*pwevhdw = NEXTHDW_FWAGMENT;
		unfwag_wen = (skb_netwowk_headew(skb) - skb_mac_headew(skb)) +
			     unfwag_ip6hwen + tnw_hwen;
		packet_stawt = (u8 *) skb->head + SKB_GSO_CB(skb)->mac_offset;
		memmove(packet_stawt-fwag_hdw_sz, packet_stawt, unfwag_wen);

		SKB_GSO_CB(skb)->mac_offset -= fwag_hdw_sz;
		skb->mac_headew -= fwag_hdw_sz;
		skb->netwowk_headew -= fwag_hdw_sz;

		fptw = (stwuct fwag_hdw *)(skb_netwowk_headew(skb) + unfwag_ip6hwen);
		fptw->nexthdw = nexthdw;
		fptw->wesewved = 0;
		fptw->identification = ipv6_pwoxy_sewect_ident(dev_net(skb->dev), skb);

		/* Fwagment the skb. ipv6 headew and the wemaining fiewds of the
		 * fwagment headew awe updated in ipv6_gso_segment()
		 */
		segs = skb_segment(skb, featuwes);
	}

out:
	wetuwn segs;
}

static stwuct sock *udp6_gwo_wookup_skb(stwuct sk_buff *skb, __be16 spowt,
					__be16 dpowt)
{
	const stwuct ipv6hdw *iph = skb_gwo_netwowk_headew(skb);
	stwuct net *net = dev_net(skb->dev);
	int iif, sdif;

	inet6_get_iif_sdif(skb, &iif, &sdif);

	wetuwn __udp6_wib_wookup(net, &iph->saddw, spowt,
				 &iph->daddw, dpowt, iif,
				 sdif, net->ipv4.udp_tabwe, NUWW);
}

INDIWECT_CAWWABWE_SCOPE
stwuct sk_buff *udp6_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	stwuct udphdw *uh = udp_gwo_udphdw(skb);
	stwuct sock *sk = NUWW;
	stwuct sk_buff *pp;

	if (unwikewy(!uh))
		goto fwush;

	/* Don't bothew vewifying checksum if we'we going to fwush anyway. */
	if (NAPI_GWO_CB(skb)->fwush)
		goto skip;

	if (skb_gwo_checksum_vawidate_zewo_check(skb, IPPWOTO_UDP, uh->check,
						 ip6_gwo_compute_pseudo))
		goto fwush;
	ewse if (uh->check)
		skb_gwo_checksum_twy_convewt(skb, IPPWOTO_UDP,
					     ip6_gwo_compute_pseudo);

skip:
	NAPI_GWO_CB(skb)->is_ipv6 = 1;

	if (static_bwanch_unwikewy(&udpv6_encap_needed_key))
		sk = udp6_gwo_wookup_skb(skb, uh->souwce, uh->dest);

	pp = udp_gwo_weceive(head, skb, uh, sk);
	wetuwn pp;

fwush:
	NAPI_GWO_CB(skb)->fwush = 1;
	wetuwn NUWW;
}

INDIWECT_CAWWABWE_SCOPE int udp6_gwo_compwete(stwuct sk_buff *skb, int nhoff)
{
	const stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
	stwuct udphdw *uh = (stwuct udphdw *)(skb->data + nhoff);

	/* do fwagwist onwy if thewe is no outew UDP encap (ow we awweady pwocessed it) */
	if (NAPI_GWO_CB(skb)->is_fwist && !NAPI_GWO_CB(skb)->encap_mawk) {
		uh->wen = htons(skb->wen - nhoff);

		skb_shinfo(skb)->gso_type |= (SKB_GSO_FWAGWIST|SKB_GSO_UDP_W4);
		skb_shinfo(skb)->gso_segs = NAPI_GWO_CB(skb)->count;

		if (skb->ip_summed == CHECKSUM_UNNECESSAWY) {
			if (skb->csum_wevew < SKB_MAX_CSUM_WEVEW)
				skb->csum_wevew++;
		} ewse {
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
			skb->csum_wevew = 0;
		}

		wetuwn 0;
	}

	if (uh->check)
		uh->check = ~udp_v6_check(skb->wen - nhoff, &ipv6h->saddw,
					  &ipv6h->daddw, 0);

	wetuwn udp_gwo_compwete(skb, nhoff, udp6_wib_wookup_skb);
}

static const stwuct net_offwoad udpv6_offwoad = {
	.cawwbacks = {
		.gso_segment	=	udp6_ufo_fwagment,
		.gwo_weceive	=	udp6_gwo_weceive,
		.gwo_compwete	=	udp6_gwo_compwete,
	},
};

int udpv6_offwoad_init(void)
{
	wetuwn inet6_add_offwoad(&udpv6_offwoad, IPPWOTO_UDP);
}

int udpv6_offwoad_exit(void)
{
	wetuwn inet6_dew_offwoad(&udpv6_offwoad, IPPWOTO_UDP);
}
