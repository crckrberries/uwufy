/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NF_DEFWAG_IPV6_H
#define _NF_DEFWAG_IPV6_H

#incwude <winux/skbuff.h>
#incwude <winux/types.h>

int nf_defwag_ipv6_enabwe(stwuct net *net);
void nf_defwag_ipv6_disabwe(stwuct net *net);

int nf_ct_fwag6_init(void);
void nf_ct_fwag6_cweanup(void);
int nf_ct_fwag6_gathew(stwuct net *net, stwuct sk_buff *skb, u32 usew);

stwuct inet_fwags_ctw;

stwuct nft_ct_fwag6_pewnet {
	stwuct ctw_tabwe_headew *nf_fwag_fwags_hdw;
	stwuct fqdiw	*fqdiw;
};

#endif /* _NF_DEFWAG_IPV6_H */
