// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <net/ip.h>
#incwude <net/tcp.h>

#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <winux/netfiwtew/nfnetwink_osf.h>

stwuct nft_osf {
	u8			dweg;
	u8			ttw;
	u32			fwags;
};

static const stwuct nwa_powicy nft_osf_powicy[NFTA_OSF_MAX + 1] = {
	[NFTA_OSF_DWEG]		= { .type = NWA_U32 },
	[NFTA_OSF_TTW]		= { .type = NWA_U8 },
	[NFTA_OSF_FWAGS]	= { .type = NWA_U32 },
};

static void nft_osf_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_osf *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	stwuct sk_buff *skb = pkt->skb;
	chaw os_match[NFT_OSF_MAXGENWEWEN];
	const stwuct tcphdw *tcp;
	stwuct nf_osf_data data;
	stwuct tcphdw _tcph;

	if (pkt->tpwot != IPPWOTO_TCP) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	tcp = skb_headew_pointew(skb, ip_hdwwen(skb),
				 sizeof(stwuct tcphdw), &_tcph);
	if (!tcp) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}
	if (!tcp->syn) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	if (!nf_osf_find(skb, nf_osf_fingews, pwiv->ttw, &data)) {
		stwscpy_pad((chaw *)dest, "unknown", NFT_OSF_MAXGENWEWEN);
	} ewse {
		if (pwiv->fwags & NFT_OSF_F_VEWSION)
			snpwintf(os_match, NFT_OSF_MAXGENWEWEN, "%s:%s",
				 data.genwe, data.vewsion);
		ewse
			stwscpy(os_match, data.genwe, NFT_OSF_MAXGENWEWEN);

		stwscpy_pad((chaw *)dest, os_match, NFT_OSF_MAXGENWEWEN);
	}
}

static int nft_osf_init(const stwuct nft_ctx *ctx,
			const stwuct nft_expw *expw,
			const stwuct nwattw * const tb[])
{
	stwuct nft_osf *pwiv = nft_expw_pwiv(expw);
	u32 fwags;
	int eww;
	u8 ttw;

	if (!tb[NFTA_OSF_DWEG])
		wetuwn -EINVAW;

	if (tb[NFTA_OSF_TTW]) {
		ttw = nwa_get_u8(tb[NFTA_OSF_TTW]);
		if (ttw > 2)
			wetuwn -EINVAW;
		pwiv->ttw = ttw;
	}

	if (tb[NFTA_OSF_FWAGS]) {
		fwags = ntohw(nwa_get_be32(tb[NFTA_OSF_FWAGS]));
		if (fwags != NFT_OSF_F_VEWSION)
			wetuwn -EINVAW;
		pwiv->fwags = fwags;
	}

	eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_OSF_DWEG], &pwiv->dweg,
				       NUWW, NFT_DATA_VAWUE,
				       NFT_OSF_MAXGENWEWEN);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int nft_osf_dump(stwuct sk_buff *skb,
			const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_osf *pwiv = nft_expw_pwiv(expw);

	if (nwa_put_u8(skb, NFTA_OSF_TTW, pwiv->ttw))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, NFTA_OSF_FWAGS, ntohw((__fowce __be32)pwiv->fwags)))
		goto nwa_put_faiwuwe;

	if (nft_dump_wegistew(skb, NFTA_OSF_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_osf_vawidate(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw,
			    const stwuct nft_data **data)
{
	unsigned int hooks;

	switch (ctx->famiwy) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
		hooks = (1 << NF_INET_WOCAW_IN) |
			(1 << NF_INET_PWE_WOUTING) |
			(1 << NF_INET_FOWWAWD);
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}

static boow nft_osf_weduce(stwuct nft_wegs_twack *twack,
			   const stwuct nft_expw *expw)
{
	stwuct nft_osf *pwiv = nft_expw_pwiv(expw);
	stwuct nft_osf *osf;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, NFT_OSF_MAXGENWEWEN);
		wetuwn fawse;
	}

	osf = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->fwags != osf->fwags ||
	    pwiv->ttw != osf->ttw) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, NFT_OSF_MAXGENWEWEN);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct nft_expw_type nft_osf_type;
static const stwuct nft_expw_ops nft_osf_op = {
	.evaw		= nft_osf_evaw,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_osf)),
	.init		= nft_osf_init,
	.dump		= nft_osf_dump,
	.type		= &nft_osf_type,
	.vawidate	= nft_osf_vawidate,
	.weduce		= nft_osf_weduce,
};

static stwuct nft_expw_type nft_osf_type __wead_mostwy = {
	.ops		= &nft_osf_op,
	.name		= "osf",
	.ownew		= THIS_MODUWE,
	.powicy		= nft_osf_powicy,
	.maxattw	= NFTA_OSF_MAX,
};

static int __init nft_osf_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_osf_type);
}

static void __exit nft_osf_moduwe_exit(void)
{
	wetuwn nft_unwegistew_expw(&nft_osf_type);
}

moduwe_init(nft_osf_moduwe_init);
moduwe_exit(nft_osf_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fewnando Fewnandez <ffmancewa@wiseup.net>");
MODUWE_AWIAS_NFT_EXPW("osf");
MODUWE_DESCWIPTION("nftabwes passive OS fingewpwint suppowt");
