// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Utiwity woutines
 *
 * Copywight (C) 2015 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/ip.h>
#incwude <winux/ipv6.h>
#incwude <winux/udp.h>
#incwude "aw-intewnaw.h"

/*
 * Fiww out a peew addwess fwom a socket buffew containing a packet.
 */
int wxwpc_extwact_addw_fwom_skb(stwuct sockaddw_wxwpc *swx, stwuct sk_buff *skb)
{
	memset(swx, 0, sizeof(*swx));

	switch (ntohs(skb->pwotocow)) {
	case ETH_P_IP:
		swx->twanspowt_type = SOCK_DGWAM;
		swx->twanspowt_wen = sizeof(swx->twanspowt.sin);
		swx->twanspowt.sin.sin_famiwy = AF_INET;
		swx->twanspowt.sin.sin_powt = udp_hdw(skb)->souwce;
		swx->twanspowt.sin.sin_addw.s_addw = ip_hdw(skb)->saddw;
		wetuwn 0;

#ifdef CONFIG_AF_WXWPC_IPV6
	case ETH_P_IPV6:
		swx->twanspowt_type = SOCK_DGWAM;
		swx->twanspowt_wen = sizeof(swx->twanspowt.sin6);
		swx->twanspowt.sin6.sin6_famiwy = AF_INET6;
		swx->twanspowt.sin6.sin6_powt = udp_hdw(skb)->souwce;
		swx->twanspowt.sin6.sin6_addw = ipv6_hdw(skb)->saddw;
		wetuwn 0;
#endif

	defauwt:
		pw_wawn_watewimited("AF_WXWPC: Unknown eth pwotocow %u\n",
				    ntohs(skb->pwotocow));
		wetuwn -EAFNOSUPPOWT;
	}
}
