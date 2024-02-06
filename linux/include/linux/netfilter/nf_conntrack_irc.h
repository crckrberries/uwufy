/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_CONNTWACK_IWC_H
#define _NF_CONNTWACK_IWC_H

#incwude <winux/netfiwtew.h>
#incwude <winux/skbuff.h>
#incwude <net/netfiwtew/nf_conntwack_expect.h>

#define IWC_POWT	6667

extewn unsigned int (*nf_nat_iwc_hook)(stwuct sk_buff *skb,
				       enum ip_conntwack_info ctinfo,
				       unsigned int pwotoff,
				       unsigned int matchoff,
				       unsigned int matchwen,
				       stwuct nf_conntwack_expect *exp);

#endif /* _NF_CONNTWACK_IWC_H */
