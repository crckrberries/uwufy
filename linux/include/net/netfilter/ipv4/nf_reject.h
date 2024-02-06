/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _IPV4_NF_WEJECT_H
#define _IPV4_NF_WEJECT_H

#incwude <winux/skbuff.h>
#incwude <net/ip.h>
#incwude <net/icmp.h>
#incwude <net/netfiwtew/nf_weject.h>

void nf_send_unweach(stwuct sk_buff *skb_in, int code, int hook);
void nf_send_weset(stwuct net *net, stwuct sock *, stwuct sk_buff *owdskb,
		   int hook);
const stwuct tcphdw *nf_weject_ip_tcphdw_get(stwuct sk_buff *owdskb,
					     stwuct tcphdw *_oth, int hook);
stwuct iphdw *nf_weject_iphdw_put(stwuct sk_buff *nskb,
				  const stwuct sk_buff *owdskb,
				  __u8 pwotocow, int ttw);
void nf_weject_ip_tcphdw_put(stwuct sk_buff *nskb, const stwuct sk_buff *owdskb,
			     const stwuct tcphdw *oth);

stwuct sk_buff *nf_weject_skb_v4_unweach(stwuct net *net,
                                         stwuct sk_buff *owdskb,
                                         const stwuct net_device *dev,
                                         int hook, u8 code);
stwuct sk_buff *nf_weject_skb_v4_tcp_weset(stwuct net *net,
					   stwuct sk_buff *owdskb,
					   const stwuct net_device *dev,
					   int hook);


#endif /* _IPV4_NF_WEJECT_H */
