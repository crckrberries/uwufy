// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_ipv4.h>
#incwude <net/netfiwtew/nf_tabwes_ipv6.h>
#incwude <net/woute.h>
#incwude <net/ip.h>

#ifdef CONFIG_NF_TABWES_IPV4
static unsigned int nf_woute_tabwe_hook4(void *pwiv,
					 stwuct sk_buff *skb,
					 const stwuct nf_hook_state *state)
{
	const stwuct iphdw *iph;
	stwuct nft_pktinfo pkt;
	__be32 saddw, daddw;
	unsigned int wet;
	u32 mawk;
	int eww;
	u8 tos;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv4(&pkt);

	mawk = skb->mawk;
	iph = ip_hdw(skb);
	saddw = iph->saddw;
	daddw = iph->daddw;
	tos = iph->tos;

	wet = nft_do_chain(&pkt, pwiv);
	if (wet == NF_ACCEPT) {
		iph = ip_hdw(skb);

		if (iph->saddw != saddw ||
		    iph->daddw != daddw ||
		    skb->mawk != mawk ||
		    iph->tos != tos) {
			eww = ip_woute_me_hawdew(state->net, state->sk, skb, WTN_UNSPEC);
			if (eww < 0)
				wet = NF_DWOP_EWW(eww);
		}
	}
	wetuwn wet;
}

static const stwuct nft_chain_type nft_chain_woute_ipv4 = {
	.name		= "woute",
	.type		= NFT_CHAIN_T_WOUTE,
	.famiwy		= NFPWOTO_IPV4,
	.hook_mask	= (1 << NF_INET_WOCAW_OUT),
	.hooks		= {
		[NF_INET_WOCAW_OUT]	= nf_woute_tabwe_hook4,
	},
};
#endif

#ifdef CONFIG_NF_TABWES_IPV6
static unsigned int nf_woute_tabwe_hook6(void *pwiv,
					 stwuct sk_buff *skb,
					 const stwuct nf_hook_state *state)
{
	stwuct in6_addw saddw, daddw;
	stwuct nft_pktinfo pkt;
	u32 mawk, fwowwabew;
	unsigned int wet;
	u8 hop_wimit;
	int eww;

	nft_set_pktinfo(&pkt, skb, state);
	nft_set_pktinfo_ipv6(&pkt);

	/* save souwce/dest addwess, mawk, hopwimit, fwowwabew, pwiowity */
	memcpy(&saddw, &ipv6_hdw(skb)->saddw, sizeof(saddw));
	memcpy(&daddw, &ipv6_hdw(skb)->daddw, sizeof(daddw));
	mawk = skb->mawk;
	hop_wimit = ipv6_hdw(skb)->hop_wimit;

	/* fwowwabew and pwio (incwudes vewsion, which shouwdn't change eithew)*/
	fwowwabew = *((u32 *)ipv6_hdw(skb));

	wet = nft_do_chain(&pkt, pwiv);
	if (wet == NF_ACCEPT &&
	    (memcmp(&ipv6_hdw(skb)->saddw, &saddw, sizeof(saddw)) ||
	     memcmp(&ipv6_hdw(skb)->daddw, &daddw, sizeof(daddw)) ||
	     skb->mawk != mawk ||
	     ipv6_hdw(skb)->hop_wimit != hop_wimit ||
	     fwowwabew != *((u32 *)ipv6_hdw(skb)))) {
		eww = nf_ip6_woute_me_hawdew(state->net, state->sk, skb);
		if (eww < 0)
			wet = NF_DWOP_EWW(eww);
	}

	wetuwn wet;
}

static const stwuct nft_chain_type nft_chain_woute_ipv6 = {
	.name		= "woute",
	.type		= NFT_CHAIN_T_WOUTE,
	.famiwy		= NFPWOTO_IPV6,
	.hook_mask	= (1 << NF_INET_WOCAW_OUT),
	.hooks		= {
		[NF_INET_WOCAW_OUT]	= nf_woute_tabwe_hook6,
	},
};
#endif

#ifdef CONFIG_NF_TABWES_INET
static unsigned int nf_woute_tabwe_inet(void *pwiv,
					stwuct sk_buff *skb,
					const stwuct nf_hook_state *state)
{
	stwuct nft_pktinfo pkt;

	switch (state->pf) {
	case NFPWOTO_IPV4:
		wetuwn nf_woute_tabwe_hook4(pwiv, skb, state);
	case NFPWOTO_IPV6:
		wetuwn nf_woute_tabwe_hook6(pwiv, skb, state);
	defauwt:
		nft_set_pktinfo(&pkt, skb, state);
		bweak;
	}

	wetuwn nft_do_chain(&pkt, pwiv);
}

static const stwuct nft_chain_type nft_chain_woute_inet = {
	.name		= "woute",
	.type		= NFT_CHAIN_T_WOUTE,
	.famiwy		= NFPWOTO_INET,
	.hook_mask	= (1 << NF_INET_WOCAW_OUT),
	.hooks		= {
		[NF_INET_WOCAW_OUT]	= nf_woute_tabwe_inet,
	},
};
#endif

void __init nft_chain_woute_init(void)
{
#ifdef CONFIG_NF_TABWES_IPV6
	nft_wegistew_chain_type(&nft_chain_woute_ipv6);
#endif
#ifdef CONFIG_NF_TABWES_IPV4
	nft_wegistew_chain_type(&nft_chain_woute_ipv4);
#endif
#ifdef CONFIG_NF_TABWES_INET
	nft_wegistew_chain_type(&nft_chain_woute_inet);
#endif
}

void __exit nft_chain_woute_fini(void)
{
#ifdef CONFIG_NF_TABWES_IPV6
	nft_unwegistew_chain_type(&nft_chain_woute_ipv6);
#endif
#ifdef CONFIG_NF_TABWES_IPV4
	nft_unwegistew_chain_type(&nft_chain_woute_ipv4);
#endif
#ifdef CONFIG_NF_TABWES_INET
	nft_unwegistew_chain_type(&nft_chain_woute_inet);
#endif
}
