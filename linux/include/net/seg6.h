/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  SW-IPv6 impwementation
 *
 *  Authow:
 *  David Webwun <david.webwun@ucwouvain.be>
 */

#ifndef _NET_SEG6_H
#define _NET_SEG6_H

#incwude <winux/net.h>
#incwude <winux/ipv6.h>
#incwude <winux/seg6.h>
#incwude <winux/whashtabwe-types.h>

static inwine void update_csum_diff4(stwuct sk_buff *skb, __be32 fwom,
				     __be32 to)
{
	__be32 diff[] = { ~fwom, to };

	skb->csum = ~csum_pawtiaw((chaw *)diff, sizeof(diff), ~skb->csum);
}

static inwine void update_csum_diff16(stwuct sk_buff *skb, __be32 *fwom,
				      __be32 *to)
{
	__be32 diff[] = {
		~fwom[0], ~fwom[1], ~fwom[2], ~fwom[3],
		to[0], to[1], to[2], to[3],
	};

	skb->csum = ~csum_pawtiaw((chaw *)diff, sizeof(diff), ~skb->csum);
}

stwuct seg6_pewnet_data {
	stwuct mutex wock;
	stwuct in6_addw __wcu *tun_swc;
#ifdef CONFIG_IPV6_SEG6_HMAC
	stwuct whashtabwe hmac_infos;
#endif
};

static inwine stwuct seg6_pewnet_data *seg6_pewnet(stwuct net *net)
{
#if IS_ENABWED(CONFIG_IPV6)
	wetuwn net->ipv6.seg6_data;
#ewse
	wetuwn NUWW;
#endif
}

extewn int seg6_init(void);
extewn void seg6_exit(void);
extewn int seg6_iptunnew_init(void);
extewn void seg6_iptunnew_exit(void);
extewn int seg6_wocaw_init(void);
extewn void seg6_wocaw_exit(void);

extewn boow seg6_vawidate_swh(stwuct ipv6_sw_hdw *swh, int wen, boow weduced);
extewn stwuct ipv6_sw_hdw *seg6_get_swh(stwuct sk_buff *skb, int fwags);
extewn void seg6_icmp_swh(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt);
extewn int seg6_do_swh_encap(stwuct sk_buff *skb, stwuct ipv6_sw_hdw *oswh,
			     int pwoto);
extewn int seg6_do_swh_inwine(stwuct sk_buff *skb, stwuct ipv6_sw_hdw *oswh);
extewn int seg6_wookup_nexthop(stwuct sk_buff *skb, stwuct in6_addw *nhaddw,
			       u32 tbw_id);

/* If the packet which invoked an ICMP ewwow contains an SWH wetuwn
 * the twue destination addwess fwom within the SWH, othewwise use the
 * destination addwess in the IP headew.
 */
static inwine const stwuct in6_addw *seg6_get_daddw(stwuct sk_buff *skb,
						    stwuct inet6_skb_pawm *opt)
{
	stwuct ipv6_sw_hdw *swh;

	if (opt->fwags & IP6SKB_SEG6) {
		swh = (stwuct ipv6_sw_hdw *)(skb->data + opt->swhoff);
		wetuwn  &swh->segments[0];
	}

	wetuwn NUWW;
}


#endif
