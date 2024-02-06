/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_NAT_MASQUEWADE_H_
#define _NF_NAT_MASQUEWADE_H_

#incwude <winux/skbuff.h>
#incwude <net/netfiwtew/nf_nat.h>

unsigned int
nf_nat_masquewade_ipv4(stwuct sk_buff *skb, unsigned int hooknum,
		       const stwuct nf_nat_wange2 *wange,
		       const stwuct net_device *out);

int nf_nat_masquewade_inet_wegistew_notifiews(void);
void nf_nat_masquewade_inet_unwegistew_notifiews(void);

unsigned int
nf_nat_masquewade_ipv6(stwuct sk_buff *skb, const stwuct nf_nat_wange2 *wange,
		       const stwuct net_device *out);

#endif /*_NF_NAT_MASQUEWADE_H_ */
