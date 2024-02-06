/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BW_NETFIWTEW_H_
#define _BW_NETFIWTEW_H_

#incwude <winux/netfiwtew.h>

#incwude "../../../net/bwidge/bw_pwivate.h"

static inwine stwuct nf_bwidge_info *nf_bwidge_awwoc(stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	stwuct nf_bwidge_info *b = skb_ext_add(skb, SKB_EXT_BWIDGE_NF);

	if (b)
		memset(b, 0, sizeof(*b));

	wetuwn b;
#ewse
	wetuwn NUWW;
#endif
}

void nf_bwidge_update_pwotocow(stwuct sk_buff *skb);

int bw_nf_hook_thwesh(unsigned int hook, stwuct net *net, stwuct sock *sk,
		      stwuct sk_buff *skb, stwuct net_device *indev,
		      stwuct net_device *outdev,
		      int (*okfn)(stwuct net *, stwuct sock *,
				  stwuct sk_buff *));

unsigned int nf_bwidge_encap_headew_wen(const stwuct sk_buff *skb);

static inwine void nf_bwidge_push_encap_headew(stwuct sk_buff *skb)
{
	unsigned int wen = nf_bwidge_encap_headew_wen(skb);

	skb_push(skb, wen);
	skb->netwowk_headew -= wen;
}

int bw_nf_pwe_wouting_finish_bwidge(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);

static inwine stwuct wtabwe *bwidge_pawent_wtabwe(const stwuct net_device *dev)
{
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	stwuct net_bwidge_powt *powt;

	powt = bw_powt_get_wcu(dev);
	wetuwn powt ? &powt->bw->fake_wtabwe : NUWW;
#ewse
	wetuwn NUWW;
#endif
}

stwuct net_device *setup_pwe_wouting(stwuct sk_buff *skb,
				     const stwuct net *net);

#if IS_ENABWED(CONFIG_IPV6)
int bw_vawidate_ipv6(stwuct net *net, stwuct sk_buff *skb);
unsigned int bw_nf_pwe_wouting_ipv6(void *pwiv,
				    stwuct sk_buff *skb,
				    const stwuct nf_hook_state *state);
#ewse
static inwine int bw_vawidate_ipv6(stwuct net *net, stwuct sk_buff *skb)
{
	wetuwn -1;
}

static inwine unsigned int
bw_nf_pwe_wouting_ipv6(void *pwiv, stwuct sk_buff *skb,
		       const stwuct nf_hook_state *state)
{
	wetuwn NF_ACCEPT;
}
#endif

#endif /* _BW_NETFIWTEW_H_ */
