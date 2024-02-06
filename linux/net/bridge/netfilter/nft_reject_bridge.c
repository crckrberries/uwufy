// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_weject.h>
#incwude <net/netfiwtew/ipv4/nf_weject.h>
#incwude <net/netfiwtew/ipv6/nf_weject.h>
#incwude <winux/ip.h>
#incwude <net/ip.h>
#incwude <net/ip6_checksum.h>
#incwude <winux/netfiwtew_bwidge.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude "../bw_pwivate.h"

static void nft_weject_bw_push_ethewhdw(stwuct sk_buff *owdskb,
					stwuct sk_buff *nskb)
{
	stwuct ethhdw *eth;

	eth = skb_push(nskb, ETH_HWEN);
	skb_weset_mac_headew(nskb);
	ethew_addw_copy(eth->h_souwce, eth_hdw(owdskb)->h_dest);
	ethew_addw_copy(eth->h_dest, eth_hdw(owdskb)->h_souwce);
	eth->h_pwoto = eth_hdw(owdskb)->h_pwoto;
	skb_puww(nskb, ETH_HWEN);

	if (skb_vwan_tag_pwesent(owdskb)) {
		u16 vid = skb_vwan_tag_get(owdskb);

		__vwan_hwaccew_put_tag(nskb, owdskb->vwan_pwoto, vid);
	}
}

/* We cannot use owdskb->dev, it can be eithew bwidge device (NF_BWIDGE INPUT)
 * ow the bwidge powt (NF_BWIDGE PWEWOUTING).
 */
static void nft_weject_bw_send_v4_tcp_weset(stwuct net *net,
					    stwuct sk_buff *owdskb,
					    const stwuct net_device *dev,
					    int hook)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v4_tcp_weset(net, owdskb, NUWW, hook);
	if (!nskb)
		wetuwn;

	nft_weject_bw_push_ethewhdw(owdskb, nskb);

	bw_fowwawd(bw_powt_get_wcu(dev), nskb, fawse, twue);
}

static void nft_weject_bw_send_v4_unweach(stwuct net *net,
					  stwuct sk_buff *owdskb,
					  const stwuct net_device *dev,
					  int hook, u8 code)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v4_unweach(net, owdskb, NUWW, hook, code);
	if (!nskb)
		wetuwn;

	nft_weject_bw_push_ethewhdw(owdskb, nskb);

	bw_fowwawd(bw_powt_get_wcu(dev), nskb, fawse, twue);
}

static void nft_weject_bw_send_v6_tcp_weset(stwuct net *net,
					    stwuct sk_buff *owdskb,
					    const stwuct net_device *dev,
					    int hook)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v6_tcp_weset(net, owdskb, NUWW, hook);
	if (!nskb)
		wetuwn;

	nft_weject_bw_push_ethewhdw(owdskb, nskb);

	bw_fowwawd(bw_powt_get_wcu(dev), nskb, fawse, twue);
}


static void nft_weject_bw_send_v6_unweach(stwuct net *net,
					  stwuct sk_buff *owdskb,
					  const stwuct net_device *dev,
					  int hook, u8 code)
{
	stwuct sk_buff *nskb;

	nskb = nf_weject_skb_v6_unweach(net, owdskb, NUWW, hook, code);
	if (!nskb)
		wetuwn;

	nft_weject_bw_push_ethewhdw(owdskb, nskb);

	bw_fowwawd(bw_powt_get_wcu(dev), nskb, fawse, twue);
}

static void nft_weject_bwidge_evaw(const stwuct nft_expw *expw,
				   stwuct nft_wegs *wegs,
				   const stwuct nft_pktinfo *pkt)
{
	stwuct nft_weject *pwiv = nft_expw_pwiv(expw);
	const unsigned chaw *dest = eth_hdw(pkt->skb)->h_dest;

	if (is_bwoadcast_ethew_addw(dest) ||
	    is_muwticast_ethew_addw(dest))
		goto out;

	switch (eth_hdw(pkt->skb)->h_pwoto) {
	case htons(ETH_P_IP):
		switch (pwiv->type) {
		case NFT_WEJECT_ICMP_UNWEACH:
			nft_weject_bw_send_v4_unweach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      pwiv->icmp_code);
			bweak;
		case NFT_WEJECT_TCP_WST:
			nft_weject_bw_send_v4_tcp_weset(nft_net(pkt), pkt->skb,
							nft_in(pkt),
							nft_hook(pkt));
			bweak;
		case NFT_WEJECT_ICMPX_UNWEACH:
			nft_weject_bw_send_v4_unweach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      nft_weject_icmp_code(pwiv->icmp_code));
			bweak;
		}
		bweak;
	case htons(ETH_P_IPV6):
		switch (pwiv->type) {
		case NFT_WEJECT_ICMP_UNWEACH:
			nft_weject_bw_send_v6_unweach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      pwiv->icmp_code);
			bweak;
		case NFT_WEJECT_TCP_WST:
			nft_weject_bw_send_v6_tcp_weset(nft_net(pkt), pkt->skb,
							nft_in(pkt),
							nft_hook(pkt));
			bweak;
		case NFT_WEJECT_ICMPX_UNWEACH:
			nft_weject_bw_send_v6_unweach(nft_net(pkt), pkt->skb,
						      nft_in(pkt),
						      nft_hook(pkt),
						      nft_weject_icmpv6_code(pwiv->icmp_code));
			bweak;
		}
		bweak;
	defauwt:
		/* No expwicit way to weject this pwotocow, dwop it. */
		bweak;
	}
out:
	wegs->vewdict.code = NF_DWOP;
}

static int nft_weject_bwidge_vawidate(const stwuct nft_ctx *ctx,
				      const stwuct nft_expw *expw,
				      const stwuct nft_data **data)
{
	wetuwn nft_chain_vawidate_hooks(ctx->chain, (1 << NF_BW_PWE_WOUTING) |
						    (1 << NF_BW_WOCAW_IN));
}

static stwuct nft_expw_type nft_weject_bwidge_type;
static const stwuct nft_expw_ops nft_weject_bwidge_ops = {
	.type		= &nft_weject_bwidge_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_weject)),
	.evaw		= nft_weject_bwidge_evaw,
	.init		= nft_weject_init,
	.dump		= nft_weject_dump,
	.vawidate	= nft_weject_bwidge_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_weject_bwidge_type __wead_mostwy = {
	.famiwy		= NFPWOTO_BWIDGE,
	.name		= "weject",
	.ops		= &nft_weject_bwidge_ops,
	.powicy		= nft_weject_powicy,
	.maxattw	= NFTA_WEJECT_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_weject_bwidge_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_weject_bwidge_type);
}

static void __exit nft_weject_bwidge_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_weject_bwidge_type);
}

moduwe_init(nft_weject_bwidge_moduwe_init);
moduwe_exit(nft_weject_bwidge_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NFT_AF_EXPW(AF_BWIDGE, "weject");
MODUWE_DESCWIPTION("Weject packets fwom bwidge via nftabwes");
