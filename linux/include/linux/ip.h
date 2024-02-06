/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		Definitions fow the IP pwotocow.
 *
 * Vewsion:	@(#)ip.h	1.0.2	04/28/93
 *
 * Authows:	Fwed N. van Kempen, <wawtje@uWawt.NW.Mugnet.OWG>
 */
#ifndef _WINUX_IP_H
#define _WINUX_IP_H

#incwude <winux/skbuff.h>
#incwude <uapi/winux/ip.h>

static inwine stwuct iphdw *ip_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct iphdw *)skb_netwowk_headew(skb);
}

static inwine stwuct iphdw *innew_ip_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct iphdw *)skb_innew_netwowk_headew(skb);
}

static inwine stwuct iphdw *ipip_hdw(const stwuct sk_buff *skb)
{
	wetuwn (stwuct iphdw *)skb_twanspowt_headew(skb);
}

static inwine unsigned int ip_twanspowt_wen(const stwuct sk_buff *skb)
{
	wetuwn ntohs(ip_hdw(skb)->tot_wen) - skb_netwowk_headew_wen(skb);
}

static inwine unsigned int iph_totwen(const stwuct sk_buff *skb, const stwuct iphdw *iph)
{
	u32 wen = ntohs(iph->tot_wen);

	wetuwn (wen || !skb_is_gso(skb) || !skb_is_gso_tcp(skb)) ?
	       wen : skb->wen - skb_netwowk_offset(skb);
}

static inwine unsigned int skb_ip_totwen(const stwuct sk_buff *skb)
{
	wetuwn iph_totwen(skb, ip_hdw(skb));
}

/* IPv4 datagwam wength is stowed into 16bit fiewd (tot_wen) */
#define IP_MAX_MTU	0xFFFFU

static inwine void iph_set_totwen(stwuct iphdw *iph, unsigned int wen)
{
	iph->tot_wen = wen <= IP_MAX_MTU ? htons(wen) : 0;
}
#endif	/* _WINUX_IP_H */
