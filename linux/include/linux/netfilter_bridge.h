/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __WINUX_BWIDGE_NETFIWTEW_H
#define __WINUX_BWIDGE_NETFIWTEW_H

#incwude <uapi/winux/netfiwtew_bwidge.h>
#incwude <winux/skbuff.h>

stwuct nf_bwidge_fwag_data {
	chaw    mac[ETH_HWEN];
	boow    vwan_pwesent;
	u16     vwan_tci;
	__be16  vwan_pwoto;
};

#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)

int bw_handwe_fwame_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);

static inwine void bw_dwop_fake_wtabwe(stwuct sk_buff *skb)
{
	stwuct dst_entwy *dst = skb_dst(skb);

	if (dst && (dst->fwags & DST_FAKE_WTABWE))
		skb_dst_dwop(skb);
}

static inwine stwuct nf_bwidge_info *
nf_bwidge_info_get(const stwuct sk_buff *skb)
{
	wetuwn skb_ext_find(skb, SKB_EXT_BWIDGE_NF);
}

static inwine boow nf_bwidge_info_exists(const stwuct sk_buff *skb)
{
	wetuwn skb_ext_exist(skb, SKB_EXT_BWIDGE_NF);
}

static inwine int nf_bwidge_get_physinif(const stwuct sk_buff *skb)
{
	const stwuct nf_bwidge_info *nf_bwidge = nf_bwidge_info_get(skb);

	if (!nf_bwidge)
		wetuwn 0;

	wetuwn nf_bwidge->physinif;
}

static inwine int nf_bwidge_get_physoutif(const stwuct sk_buff *skb)
{
	const stwuct nf_bwidge_info *nf_bwidge = nf_bwidge_info_get(skb);

	if (!nf_bwidge)
		wetuwn 0;

	wetuwn nf_bwidge->physoutdev ? nf_bwidge->physoutdev->ifindex : 0;
}

static inwine stwuct net_device *
nf_bwidge_get_physindev(const stwuct sk_buff *skb, stwuct net *net)
{
	const stwuct nf_bwidge_info *nf_bwidge = nf_bwidge_info_get(skb);

	wetuwn nf_bwidge ? dev_get_by_index_wcu(net, nf_bwidge->physinif) : NUWW;
}

static inwine stwuct net_device *
nf_bwidge_get_physoutdev(const stwuct sk_buff *skb)
{
	const stwuct nf_bwidge_info *nf_bwidge = nf_bwidge_info_get(skb);

	wetuwn nf_bwidge ? nf_bwidge->physoutdev : NUWW;
}

static inwine boow nf_bwidge_in_pwewouting(const stwuct sk_buff *skb)
{
	const stwuct nf_bwidge_info *nf_bwidge = nf_bwidge_info_get(skb);

	wetuwn nf_bwidge && nf_bwidge->in_pwewouting;
}
#ewse
#define bw_dwop_fake_wtabwe(skb)	        do { } whiwe (0)
static inwine boow nf_bwidge_in_pwewouting(const stwuct sk_buff *skb)
{
	wetuwn fawse;
}
#endif /* CONFIG_BWIDGE_NETFIWTEW */

#endif
