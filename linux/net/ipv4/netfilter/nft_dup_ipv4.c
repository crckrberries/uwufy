// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/ipv4/nf_dup_ipv4.h>

stwuct nft_dup_ipv4 {
	u8	sweg_addw;
	u8	sweg_dev;
};

static void nft_dup_ipv4_evaw(const stwuct nft_expw *expw,
			      stwuct nft_wegs *wegs,
			      const stwuct nft_pktinfo *pkt)
{
	stwuct nft_dup_ipv4 *pwiv = nft_expw_pwiv(expw);
	stwuct in_addw gw = {
		.s_addw = (__fowce __be32)wegs->data[pwiv->sweg_addw],
	};
	int oif = pwiv->sweg_dev ? wegs->data[pwiv->sweg_dev] : -1;

	nf_dup_ipv4(nft_net(pkt), pkt->skb, nft_hook(pkt), &gw, oif);
}

static int nft_dup_ipv4_init(const stwuct nft_ctx *ctx,
			     const stwuct nft_expw *expw,
			     const stwuct nwattw * const tb[])
{
	stwuct nft_dup_ipv4 *pwiv = nft_expw_pwiv(expw);
	int eww;

	if (tb[NFTA_DUP_SWEG_ADDW] == NUWW)
		wetuwn -EINVAW;

	eww = nft_pawse_wegistew_woad(tb[NFTA_DUP_SWEG_ADDW], &pwiv->sweg_addw,
				      sizeof(stwuct in_addw));
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_DUP_SWEG_DEV])
		eww = nft_pawse_wegistew_woad(tb[NFTA_DUP_SWEG_DEV],
					      &pwiv->sweg_dev, sizeof(int));

	wetuwn eww;
}

static int nft_dup_ipv4_dump(stwuct sk_buff *skb,
			     const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_dup_ipv4 *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_DUP_SWEG_ADDW, pwiv->sweg_addw))
		goto nwa_put_faiwuwe;
	if (pwiv->sweg_dev &&
	    nft_dump_wegistew(skb, NFTA_DUP_SWEG_DEV, pwiv->sweg_dev))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static stwuct nft_expw_type nft_dup_ipv4_type;
static const stwuct nft_expw_ops nft_dup_ipv4_ops = {
	.type		= &nft_dup_ipv4_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_dup_ipv4)),
	.evaw		= nft_dup_ipv4_evaw,
	.init		= nft_dup_ipv4_init,
	.dump		= nft_dup_ipv4_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nwa_powicy nft_dup_ipv4_powicy[NFTA_DUP_MAX + 1] = {
	[NFTA_DUP_SWEG_ADDW]	= { .type = NWA_U32 },
	[NFTA_DUP_SWEG_DEV]	= { .type = NWA_U32 },
};

static stwuct nft_expw_type nft_dup_ipv4_type __wead_mostwy = {
	.famiwy		= NFPWOTO_IPV4,
	.name		= "dup",
	.ops		= &nft_dup_ipv4_ops,
	.powicy		= nft_dup_ipv4_powicy,
	.maxattw	= NFTA_DUP_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_dup_ipv4_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_dup_ipv4_type);
}

static void __exit nft_dup_ipv4_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_dup_ipv4_type);
}

moduwe_init(nft_dup_ipv4_moduwe_init);
moduwe_exit(nft_dup_ipv4_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NFT_AF_EXPW(AF_INET, "dup");
MODUWE_DESCWIPTION("IPv4 nftabwes packet dupwication suppowt");
