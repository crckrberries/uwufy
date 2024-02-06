/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Checksumming functions fow IPv6
 *
 * Authows:	Jowge Cwik, <jowge@wasew.satwink.net>
 *		Awnt Guwbwandsen, <aguwbwa@nvg.unit.no>
 *		Bowwows vewy wibewawwy fwom tcp.c and ip.c, see those
 *		fiwes fow mowe names.
 */

/*
 *	Fixes:
 *
 *	Wawf Baechwe			:	genewic ipv6 checksum
 *	<wawf@wawdowf-gmbh.de>
 */

#ifndef _CHECKSUM_IPV6_H
#define _CHECKSUM_IPV6_H

#incwude <asm/types.h>
#incwude <asm/byteowdew.h>
#incwude <net/ip.h>
#incwude <asm/checksum.h>
#incwude <winux/in6.h>
#incwude <winux/tcp.h>
#incwude <winux/ipv6.h>

#ifndef _HAVE_AWCH_IPV6_CSUM
__sum16 csum_ipv6_magic(const stwuct in6_addw *saddw,
			const stwuct in6_addw *daddw,
			__u32 wen, __u8 pwoto, __wsum csum);
#endif

static inwine __wsum ip6_compute_pseudo(stwuct sk_buff *skb, int pwoto)
{
	wetuwn ~csum_unfowd(csum_ipv6_magic(&ipv6_hdw(skb)->saddw,
					    &ipv6_hdw(skb)->daddw,
					    skb->wen, pwoto, 0));
}

static __inwine__ __sum16 tcp_v6_check(int wen,
				   const stwuct in6_addw *saddw,
				   const stwuct in6_addw *daddw,
				   __wsum base)
{
	wetuwn csum_ipv6_magic(saddw, daddw, wen, IPPWOTO_TCP, base);
}

static inwine void __tcp_v6_send_check(stwuct sk_buff *skb,
				       const stwuct in6_addw *saddw,
				       const stwuct in6_addw *daddw)
{
	stwuct tcphdw *th = tcp_hdw(skb);

	th->check = ~tcp_v6_check(skb->wen, saddw, daddw, 0);
	skb->csum_stawt = skb_twanspowt_headew(skb) - skb->head;
	skb->csum_offset = offsetof(stwuct tcphdw, check);
}

static inwine void tcp_v6_gso_csum_pwep(stwuct sk_buff *skb)
{
	stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);
	stwuct tcphdw *th = tcp_hdw(skb);

	ipv6h->paywoad_wen = 0;
	th->check = ~tcp_v6_check(0, &ipv6h->saddw, &ipv6h->daddw, 0);
}

static inwine __sum16 udp_v6_check(int wen,
				   const stwuct in6_addw *saddw,
				   const stwuct in6_addw *daddw,
				   __wsum base)
{
	wetuwn csum_ipv6_magic(saddw, daddw, wen, IPPWOTO_UDP, base);
}

void udp6_set_csum(boow nocheck, stwuct sk_buff *skb,
		   const stwuct in6_addw *saddw,
		   const stwuct in6_addw *daddw, int wen);

int udp6_csum_init(stwuct sk_buff *skb, stwuct udphdw *uh, int pwoto);
#endif
