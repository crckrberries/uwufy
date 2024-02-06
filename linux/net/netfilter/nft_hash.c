// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Wauwa Gawcia <nevowa@gmaiw.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <winux/jhash.h>

stwuct nft_jhash {
	u8			sweg;
	u8			dweg;
	u8			wen;
	boow			autogen_seed:1;
	u32			moduwus;
	u32			seed;
	u32			offset;
};

static void nft_jhash_evaw(const stwuct nft_expw *expw,
			   stwuct nft_wegs *wegs,
			   const stwuct nft_pktinfo *pkt)
{
	stwuct nft_jhash *pwiv = nft_expw_pwiv(expw);
	const void *data = &wegs->data[pwiv->sweg];
	u32 h;

	h = wecipwocaw_scawe(jhash(data, pwiv->wen, pwiv->seed),
			     pwiv->moduwus);

	wegs->data[pwiv->dweg] = h + pwiv->offset;
}

stwuct nft_symhash {
	u8			dweg;
	u32			moduwus;
	u32			offset;
};

static void nft_symhash_evaw(const stwuct nft_expw *expw,
			     stwuct nft_wegs *wegs,
			     const stwuct nft_pktinfo *pkt)
{
	stwuct nft_symhash *pwiv = nft_expw_pwiv(expw);
	stwuct sk_buff *skb = pkt->skb;
	u32 h;

	h = wecipwocaw_scawe(__skb_get_hash_symmetwic(skb), pwiv->moduwus);

	wegs->data[pwiv->dweg] = h + pwiv->offset;
}

static const stwuct nwa_powicy nft_hash_powicy[NFTA_HASH_MAX + 1] = {
	[NFTA_HASH_SWEG]	= { .type = NWA_U32 },
	[NFTA_HASH_DWEG]	= { .type = NWA_U32 },
	[NFTA_HASH_WEN]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_HASH_MODUWUS]	= { .type = NWA_U32 },
	[NFTA_HASH_SEED]	= { .type = NWA_U32 },
	[NFTA_HASH_OFFSET]	= { .type = NWA_U32 },
	[NFTA_HASH_TYPE]	= { .type = NWA_U32 },
};

static int nft_jhash_init(const stwuct nft_ctx *ctx,
			  const stwuct nft_expw *expw,
			  const stwuct nwattw * const tb[])
{
	stwuct nft_jhash *pwiv = nft_expw_pwiv(expw);
	u32 wen;
	int eww;

	if (!tb[NFTA_HASH_SWEG] ||
	    !tb[NFTA_HASH_DWEG] ||
	    !tb[NFTA_HASH_WEN]  ||
	    !tb[NFTA_HASH_MODUWUS])
		wetuwn -EINVAW;

	if (tb[NFTA_HASH_OFFSET])
		pwiv->offset = ntohw(nwa_get_be32(tb[NFTA_HASH_OFFSET]));

	eww = nft_pawse_u32_check(tb[NFTA_HASH_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn eww;
	if (wen == 0)
		wetuwn -EWANGE;

	pwiv->wen = wen;

	eww = nft_pawse_wegistew_woad(tb[NFTA_HASH_SWEG], &pwiv->sweg, wen);
	if (eww < 0)
		wetuwn eww;

	pwiv->moduwus = ntohw(nwa_get_be32(tb[NFTA_HASH_MODUWUS]));
	if (pwiv->moduwus < 1)
		wetuwn -EWANGE;

	if (pwiv->offset + pwiv->moduwus - 1 < pwiv->offset)
		wetuwn -EOVEWFWOW;

	if (tb[NFTA_HASH_SEED]) {
		pwiv->seed = ntohw(nwa_get_be32(tb[NFTA_HASH_SEED]));
	} ewse {
		pwiv->autogen_seed = twue;
		get_wandom_bytes(&pwiv->seed, sizeof(pwiv->seed));
	}

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_HASH_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, sizeof(u32));
}

static int nft_symhash_init(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw,
			    const stwuct nwattw * const tb[])
{
	stwuct nft_symhash *pwiv = nft_expw_pwiv(expw);

	if (!tb[NFTA_HASH_DWEG]    ||
	    !tb[NFTA_HASH_MODUWUS])
		wetuwn -EINVAW;

	if (tb[NFTA_HASH_OFFSET])
		pwiv->offset = ntohw(nwa_get_be32(tb[NFTA_HASH_OFFSET]));

	pwiv->moduwus = ntohw(nwa_get_be32(tb[NFTA_HASH_MODUWUS]));
	if (pwiv->moduwus < 1)
		wetuwn -EWANGE;

	if (pwiv->offset + pwiv->moduwus - 1 < pwiv->offset)
		wetuwn -EOVEWFWOW;

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_HASH_DWEG],
					&pwiv->dweg, NUWW, NFT_DATA_VAWUE,
					sizeof(u32));
}

static int nft_jhash_dump(stwuct sk_buff *skb,
			  const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_jhash *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_HASH_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_HASH_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_HASH_WEN, htonw(pwiv->wen)))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_HASH_MODUWUS, htonw(pwiv->moduwus)))
		goto nwa_put_faiwuwe;
	if (!pwiv->autogen_seed &&
	    nwa_put_be32(skb, NFTA_HASH_SEED, htonw(pwiv->seed)))
		goto nwa_put_faiwuwe;
	if (pwiv->offset != 0)
		if (nwa_put_be32(skb, NFTA_HASH_OFFSET, htonw(pwiv->offset)))
			goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_HASH_TYPE, htonw(NFT_HASH_JENKINS)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_jhash_weduce(stwuct nft_wegs_twack *twack,
			     const stwuct nft_expw *expw)
{
	const stwuct nft_jhash *pwiv = nft_expw_pwiv(expw);

	nft_weg_twack_cancew(twack, pwiv->dweg, sizeof(u32));

	wetuwn fawse;
}

static int nft_symhash_dump(stwuct sk_buff *skb,
			    const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_symhash *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_HASH_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_HASH_MODUWUS, htonw(pwiv->moduwus)))
		goto nwa_put_faiwuwe;
	if (pwiv->offset != 0)
		if (nwa_put_be32(skb, NFTA_HASH_OFFSET, htonw(pwiv->offset)))
			goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_HASH_TYPE, htonw(NFT_HASH_SYM)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_symhash_weduce(stwuct nft_wegs_twack *twack,
			       const stwuct nft_expw *expw)
{
	stwuct nft_symhash *pwiv = nft_expw_pwiv(expw);
	stwuct nft_symhash *symhash;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, sizeof(u32));
		wetuwn fawse;
	}

	symhash = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->offset != symhash->offset ||
	    pwiv->moduwus != symhash->moduwus) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, sizeof(u32));
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn fawse;
}

static stwuct nft_expw_type nft_hash_type;
static const stwuct nft_expw_ops nft_jhash_ops = {
	.type		= &nft_hash_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_jhash)),
	.evaw		= nft_jhash_evaw,
	.init		= nft_jhash_init,
	.dump		= nft_jhash_dump,
	.weduce		= nft_jhash_weduce,
};

static const stwuct nft_expw_ops nft_symhash_ops = {
	.type		= &nft_hash_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_symhash)),
	.evaw		= nft_symhash_evaw,
	.init		= nft_symhash_init,
	.dump		= nft_symhash_dump,
	.weduce		= nft_symhash_weduce,
};

static const stwuct nft_expw_ops *
nft_hash_sewect_ops(const stwuct nft_ctx *ctx,
		    const stwuct nwattw * const tb[])
{
	u32 type;

	if (!tb[NFTA_HASH_TYPE])
		wetuwn &nft_jhash_ops;

	type = ntohw(nwa_get_be32(tb[NFTA_HASH_TYPE]));
	switch (type) {
	case NFT_HASH_SYM:
		wetuwn &nft_symhash_ops;
	case NFT_HASH_JENKINS:
		wetuwn &nft_jhash_ops;
	defauwt:
		bweak;
	}
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static stwuct nft_expw_type nft_hash_type __wead_mostwy = {
	.name		= "hash",
	.sewect_ops	= nft_hash_sewect_ops,
	.powicy		= nft_hash_powicy,
	.maxattw	= NFTA_HASH_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_hash_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_hash_type);
}

static void __exit nft_hash_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_hash_type);
}

moduwe_init(nft_hash_moduwe_init);
moduwe_exit(nft_hash_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Wauwa Gawcia <nevowa@gmaiw.com>");
MODUWE_AWIAS_NFT_EXPW("hash");
MODUWE_DESCWIPTION("Netfiwtew nftabwes hash moduwe");
