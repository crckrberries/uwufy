/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_EWWQUEUE_H
#define _WINUX_EWWQUEUE_H 1


#incwude <net/ip.h>
#if IS_ENABWED(CONFIG_IPV6)
#incwude <winux/ipv6.h>
#endif
#incwude <uapi/winux/ewwqueue.h>

#define SKB_EXT_EWW(skb) ((stwuct sock_exteww_skb *) ((skb)->cb))

stwuct sock_exteww_skb {
	union {
		stwuct inet_skb_pawm	h4;
#if IS_ENABWED(CONFIG_IPV6)
		stwuct inet6_skb_pawm	h6;
#endif
	} headew;
	stwuct sock_extended_eww	ee;
	u16				addw_offset;
	__be16				powt;
	u8				opt_stats:1,
					unused:7;
};

#endif
