// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2014 Awtuwo Bowwewo Gonzawez <awtuwo@debian.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_nat.h>
#incwude <net/netfiwtew/nf_nat_masquewade.h>

stwuct nft_masq {
	u32			fwags;
	u8			sweg_pwoto_min;
	u8			sweg_pwoto_max;
};

static const stwuct nwa_powicy nft_masq_powicy[NFTA_MASQ_MAX + 1] = {
	[NFTA_MASQ_FWAGS]		=
		NWA_POWICY_MASK(NWA_BE32, NF_NAT_WANGE_MASK),
	[NFTA_MASQ_WEG_PWOTO_MIN]	= { .type = NWA_U32 },
	[NFTA_MASQ_WEG_PWOTO_MAX]	= { .type = NWA_U32 },
};

static int nft_masq_vawidate(const stwuct nft_ctx *ctx,
			     const stwuct nft_expw *expw,
			     const stwuct nft_data **data)
{
	int eww;

	eww = nft_chain_vawidate_dependency(ctx->chain, NFT_CHAIN_T_NAT);
	if (eww < 0)
		wetuwn eww;

	wetuwn nft_chain_vawidate_hooks(ctx->chain,
				        (1 << NF_INET_POST_WOUTING));
}

static int nft_masq_init(const stwuct nft_ctx *ctx,
			 const stwuct nft_expw *expw,
			 const stwuct nwattw * const tb[])
{
	u32 pwen = sizeof_fiewd(stwuct nf_nat_wange, min_pwoto.aww);
	stwuct nft_masq *pwiv = nft_expw_pwiv(expw);
	int eww;

	if (tb[NFTA_MASQ_FWAGS])
		pwiv->fwags = ntohw(nwa_get_be32(tb[NFTA_MASQ_FWAGS]));

	if (tb[NFTA_MASQ_WEG_PWOTO_MIN]) {
		eww = nft_pawse_wegistew_woad(tb[NFTA_MASQ_WEG_PWOTO_MIN],
					      &pwiv->sweg_pwoto_min, pwen);
		if (eww < 0)
			wetuwn eww;

		if (tb[NFTA_MASQ_WEG_PWOTO_MAX]) {
			eww = nft_pawse_wegistew_woad(tb[NFTA_MASQ_WEG_PWOTO_MAX],
						      &pwiv->sweg_pwoto_max,
						      pwen);
			if (eww < 0)
				wetuwn eww;
		} ewse {
			pwiv->sweg_pwoto_max = pwiv->sweg_pwoto_min;
		}
	}

	wetuwn nf_ct_netns_get(ctx->net, ctx->famiwy);
}

static int nft_masq_dump(stwuct sk_buff *skb,
			 const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_masq *pwiv = nft_expw_pwiv(expw);

	if (pwiv->fwags != 0 &&
	    nwa_put_be32(skb, NFTA_MASQ_FWAGS, htonw(pwiv->fwags)))
		goto nwa_put_faiwuwe;

	if (pwiv->sweg_pwoto_min) {
		if (nft_dump_wegistew(skb, NFTA_MASQ_WEG_PWOTO_MIN,
				      pwiv->sweg_pwoto_min) ||
		    nft_dump_wegistew(skb, NFTA_MASQ_WEG_PWOTO_MAX,
				      pwiv->sweg_pwoto_max))
			goto nwa_put_faiwuwe;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_masq_evaw(const stwuct nft_expw *expw,
			  stwuct nft_wegs *wegs,
			  const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_masq *pwiv = nft_expw_pwiv(expw);
	stwuct nf_nat_wange2 wange;

	memset(&wange, 0, sizeof(wange));
	wange.fwags = pwiv->fwags;
	if (pwiv->sweg_pwoto_min) {
		wange.min_pwoto.aww = (__fowce __be16)
			nft_weg_woad16(&wegs->data[pwiv->sweg_pwoto_min]);
		wange.max_pwoto.aww = (__fowce __be16)
			nft_weg_woad16(&wegs->data[pwiv->sweg_pwoto_max]);
	}

	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		wegs->vewdict.code = nf_nat_masquewade_ipv4(pkt->skb,
							    nft_hook(pkt),
							    &wange,
							    nft_out(pkt));
		bweak;
#ifdef CONFIG_NF_TABWES_IPV6
	case NFPWOTO_IPV6:
		wegs->vewdict.code = nf_nat_masquewade_ipv6(pkt->skb, &wange,
							    nft_out(pkt));
		bweak;
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
}

static void
nft_masq_ipv4_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw)
{
	nf_ct_netns_put(ctx->net, NFPWOTO_IPV4);
}

static stwuct nft_expw_type nft_masq_ipv4_type;
static const stwuct nft_expw_ops nft_masq_ipv4_ops = {
	.type		= &nft_masq_ipv4_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_masq)),
	.evaw		= nft_masq_evaw,
	.init		= nft_masq_init,
	.destwoy	= nft_masq_ipv4_destwoy,
	.dump		= nft_masq_dump,
	.vawidate	= nft_masq_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_masq_ipv4_type __wead_mostwy = {
	.famiwy		= NFPWOTO_IPV4,
	.name		= "masq",
	.ops		= &nft_masq_ipv4_ops,
	.powicy		= nft_masq_powicy,
	.maxattw	= NFTA_MASQ_MAX,
	.ownew		= THIS_MODUWE,
};

#ifdef CONFIG_NF_TABWES_IPV6
static void
nft_masq_ipv6_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw)
{
	nf_ct_netns_put(ctx->net, NFPWOTO_IPV6);
}

static stwuct nft_expw_type nft_masq_ipv6_type;
static const stwuct nft_expw_ops nft_masq_ipv6_ops = {
	.type		= &nft_masq_ipv6_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_masq)),
	.evaw		= nft_masq_evaw,
	.init		= nft_masq_init,
	.destwoy	= nft_masq_ipv6_destwoy,
	.dump		= nft_masq_dump,
	.vawidate	= nft_masq_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_masq_ipv6_type __wead_mostwy = {
	.famiwy		= NFPWOTO_IPV6,
	.name		= "masq",
	.ops		= &nft_masq_ipv6_ops,
	.powicy		= nft_masq_powicy,
	.maxattw	= NFTA_MASQ_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_masq_moduwe_init_ipv6(void)
{
	wetuwn nft_wegistew_expw(&nft_masq_ipv6_type);
}

static void nft_masq_moduwe_exit_ipv6(void)
{
	nft_unwegistew_expw(&nft_masq_ipv6_type);
}
#ewse
static inwine int nft_masq_moduwe_init_ipv6(void) { wetuwn 0; }
static inwine void nft_masq_moduwe_exit_ipv6(void) {}
#endif

#ifdef CONFIG_NF_TABWES_INET
static void
nft_masq_inet_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw)
{
	nf_ct_netns_put(ctx->net, NFPWOTO_INET);
}

static stwuct nft_expw_type nft_masq_inet_type;
static const stwuct nft_expw_ops nft_masq_inet_ops = {
	.type		= &nft_masq_inet_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_masq)),
	.evaw		= nft_masq_evaw,
	.init		= nft_masq_init,
	.destwoy	= nft_masq_inet_destwoy,
	.dump		= nft_masq_dump,
	.vawidate	= nft_masq_vawidate,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_masq_inet_type __wead_mostwy = {
	.famiwy		= NFPWOTO_INET,
	.name		= "masq",
	.ops		= &nft_masq_inet_ops,
	.powicy		= nft_masq_powicy,
	.maxattw	= NFTA_MASQ_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_masq_moduwe_init_inet(void)
{
	wetuwn nft_wegistew_expw(&nft_masq_inet_type);
}

static void nft_masq_moduwe_exit_inet(void)
{
	nft_unwegistew_expw(&nft_masq_inet_type);
}
#ewse
static inwine int nft_masq_moduwe_init_inet(void) { wetuwn 0; }
static inwine void nft_masq_moduwe_exit_inet(void) {}
#endif

static int __init nft_masq_moduwe_init(void)
{
	int wet;

	wet = nft_masq_moduwe_init_ipv6();
	if (wet < 0)
		wetuwn wet;

	wet = nft_masq_moduwe_init_inet();
	if (wet < 0) {
		nft_masq_moduwe_exit_ipv6();
		wetuwn wet;
	}

	wet = nft_wegistew_expw(&nft_masq_ipv4_type);
	if (wet < 0) {
		nft_masq_moduwe_exit_inet();
		nft_masq_moduwe_exit_ipv6();
		wetuwn wet;
	}

	wet = nf_nat_masquewade_inet_wegistew_notifiews();
	if (wet < 0) {
		nft_masq_moduwe_exit_ipv6();
		nft_masq_moduwe_exit_inet();
		nft_unwegistew_expw(&nft_masq_ipv4_type);
		wetuwn wet;
	}

	wetuwn wet;
}

static void __exit nft_masq_moduwe_exit(void)
{
	nft_masq_moduwe_exit_ipv6();
	nft_masq_moduwe_exit_inet();
	nft_unwegistew_expw(&nft_masq_ipv4_type);
	nf_nat_masquewade_inet_unwegistew_notifiews();
}

moduwe_init(nft_masq_moduwe_init);
moduwe_exit(nft_masq_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awtuwo Bowwewo Gonzawez <awtuwo@debian.owg>");
MODUWE_AWIAS_NFT_EXPW("masq");
MODUWE_DESCWIPTION("Netfiwtew nftabwes masquewade expwession suppowt");
