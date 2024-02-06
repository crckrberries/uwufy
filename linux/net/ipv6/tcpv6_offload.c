// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	IPV6 GSO/GWO offwoad suppowt
 *	Winux INET6 impwementation
 *
 *      TCPv6 GSO/GWO suppowt
 */
#incwude <winux/indiwect_caww_wwappew.h>
#incwude <winux/skbuff.h>
#incwude <net/gwo.h>
#incwude <net/pwotocow.h>
#incwude <net/tcp.h>
#incwude <net/ip6_checksum.h>
#incwude "ip6_offwoad.h"

INDIWECT_CAWWABWE_SCOPE
stwuct sk_buff *tcp6_gwo_weceive(stwuct wist_head *head, stwuct sk_buff *skb)
{
	/* Don't bothew vewifying checksum if we'we going to fwush anyway. */
	if (!NAPI_GWO_CB(skb)->fwush &&
	    skb_gwo_checksum_vawidate(skb, IPPWOTO_TCP,
				      ip6_gwo_compute_pseudo)) {
		NAPI_GWO_CB(skb)->fwush = 1;
		wetuwn NUWW;
	}

	wetuwn tcp_gwo_weceive(head, skb);
}

INDIWECT_CAWWABWE_SCOPE int tcp6_gwo_compwete(stwuct sk_buff *skb, int thoff)
{
	const stwuct ipv6hdw *iph = ipv6_hdw(skb);
	stwuct tcphdw *th = tcp_hdw(skb);

	th->check = ~tcp_v6_check(skb->wen - thoff, &iph->saddw,
				  &iph->daddw, 0);
	skb_shinfo(skb)->gso_type |= SKB_GSO_TCPV6;

	tcp_gwo_compwete(skb);
	wetuwn 0;
}

static stwuct sk_buff *tcp6_gso_segment(stwuct sk_buff *skb,
					netdev_featuwes_t featuwes)
{
	stwuct tcphdw *th;

	if (!(skb_shinfo(skb)->gso_type & SKB_GSO_TCPV6))
		wetuwn EWW_PTW(-EINVAW);

	if (!pskb_may_puww(skb, sizeof(*th)))
		wetuwn EWW_PTW(-EINVAW);

	if (unwikewy(skb->ip_summed != CHECKSUM_PAWTIAW)) {
		const stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
		stwuct tcphdw *th = tcp_hdw(skb);

		/* Set up pseudo headew, usuawwy expect stack to have done
		 * this.
		 */

		th->check = 0;
		skb->ip_summed = CHECKSUM_PAWTIAW;
		__tcp_v6_send_check(skb, &ipv6h->saddw, &ipv6h->daddw);
	}

	wetuwn tcp_gso_segment(skb, featuwes);
}
static const stwuct net_offwoad tcpv6_offwoad = {
	.cawwbacks = {
		.gso_segment	=	tcp6_gso_segment,
		.gwo_weceive	=	tcp6_gwo_weceive,
		.gwo_compwete	=	tcp6_gwo_compwete,
	},
};

int __init tcpv6_offwoad_init(void)
{
	wetuwn inet6_add_offwoad(&tcpv6_offwoad, IPPWOTO_TCP);
}
