/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_DUP_IPV4_H_
#define _NF_DUP_IPV4_H_

#incwude <winux/skbuff.h>
#incwude <uapi/winux/in.h>

void nf_dup_ipv4(stwuct net *net, stwuct sk_buff *skb, unsigned int hooknum,
		 const stwuct in_addw *gw, int oif);

#endif /* _NF_DUP_IPV4_H_ */
