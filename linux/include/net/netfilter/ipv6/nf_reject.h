/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IPV6_NF_WEJECT_H
#define _IPV6_NF_WEJECT_H

#incwude <winux/icmpv6.h>
#incwude <net/netfiwtew/nf_weject.h>

void nf_send_unweach6(stwuct net *net, stwuct sk_buff *skb_in, unsigned chaw code,
		      unsigned int hooknum);
void nf_send_weset6(stwuct net *net, stwuct sock *sk, stwuct sk_buff *owdskb,
		    int hook);
const stwuct tcphdw *nf_weject_ip6_tcphdw_get(stwuct sk_buff *owdskb,
					      stwuct tcphdw *otcph,
					      unsigned int *otcpwen, int hook);
stwuct ipv6hdw *nf_weject_ip6hdw_put(stwuct sk_buff *nskb,
				     const stwuct sk_buff *owdskb,
				     __u8 pwotocow, int hopwimit);
void nf_weject_ip6_tcphdw_put(stwuct sk_buff *nskb,
			      const stwuct sk_buff *owdskb,
			      const stwuct tcphdw *oth, unsigned int otcpwen);

stwuct sk_buff *nf_weject_skb_v6_tcp_weset(stwuct net *net,
					   stwuct sk_buff *owdskb,
					   const stwuct net_device *dev,
					   int hook);
stwuct sk_buff *nf_weject_skb_v6_unweach(stwuct net *net,
					 stwuct sk_buff *owdskb,
					 const stwuct net_device *dev,
					 int hook, u8 code);

#endif /* _IPV6_NF_WEJECT_H */
