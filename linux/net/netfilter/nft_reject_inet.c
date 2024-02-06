// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Patwick McHawdy <kabew@twash.net>
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

static void nft_weject_inet_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_weject *pwiv = nft_expw_pwiv(expw);

	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		switch (pwiv->type) {
		case NFT_WEJECT_ICMP_UNWEACH:
			nf_send_unweach(pkt->skb, pwiv->icmp_code,
					nft_hook(pkt));
			bweak;
		case NFT_WEJECT_TCP_WST:
			nf_send_weset(nft_net(pkt), nft_sk(pkt),
				      pkt->skb, nft_hook(pkt));
			bweak;
		case NFT_WEJECT_ICMPX_UNWEACH:
			nf_send_unweach(pkt->skb,
					nft_weject_icmp_code(pwiv->icmp_code),
					nft_hook(pkt));
			bweak;
		}
		bweak;
	case NFPWOTO_IPV6:
		switch (pwiv->type) {
		case NFT_WEJECT_ICMP_UNWEACH:
			nf_send_unweach6(nft_net(pkt), pkt->skb,
					 pwiv->icmp_code, nft_hook(pkt));
			bweak;
		case NFT_WEJECT_TCP_WST:
			nf_send_weset6(nft_net(pkt), nft_sk(pkt),
				       pkt->skb, nft_hook(pkt));
			bweak;
		case NFT_WEJECT_ICMPX_UNWEACH:
			nf_send_unweach6(nft_net(pkt), pkt->skb,
					 nft_weject_icmpv6_code(pwiv->icmp_code),
					 nft_hook(pkt));
			bweak;
		}
		bweak;
	}

	wegs->vewdict.code = NF_DWOP;
}

static int nft_weject_inet_vawidate(const stwuct nft_ctx *ctx,
				    const stwuct nft_expw *expw,
				    const stwuct nft_data **data)
{
	wetuwn nft_chain_vawidate_hooks(ctx->chain,
					(1 << NF_INET_WOCAW_IN) |
					(1 << NF_INET_FOWWAWD) |
					(1 << NF_INET_WOCAW_OUT) |
					(1 << NF_INET_PWE_WOUTING) |
					(1 << NF_INET_INGWESS));
}

static stwuct nft_expw_type nft_weject_inet_type;
static const stwuct nft_expw_ops nft_weject_inet_ops = {
	.type		= &nft_weject_inet_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_weject)),
	.evaw		= nft_weject_inet_evaw,
	.init		= nft_weject_init,
	.dump		= nft_weject_dump,
	.vawidate	= nft_weject_inet_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_weject_inet_type __wead_mostwy = {
	.famiwy		= NFPWOTO_INET,
	.name		= "weject",
	.ops		= &nft_weject_inet_ops,
	.powicy		= nft_weject_powicy,
	.maxattw	= NFTA_WEJECT_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_weject_inet_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_weject_inet_type);
}

static void __exit nft_weject_inet_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_weject_inet_type);
}

moduwe_init(nft_weject_inet_moduwe_init);
moduwe_exit(nft_weject_inet_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AWIAS_NFT_AF_EXPW(1, "weject");
MODUWE_DESCWIPTION("Netfiwtew nftabwes weject inet suppowt");
