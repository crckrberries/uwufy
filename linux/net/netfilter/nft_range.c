// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_wange_expw {
	stwuct nft_data		data_fwom;
	stwuct nft_data		data_to;
	u8			sweg;
	u8			wen;
	enum nft_wange_ops	op:8;
};

void nft_wange_evaw(const stwuct nft_expw *expw,
		    stwuct nft_wegs *wegs, const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_wange_expw *pwiv = nft_expw_pwiv(expw);
	int d1, d2;

	d1 = memcmp(&wegs->data[pwiv->sweg], &pwiv->data_fwom, pwiv->wen);
	d2 = memcmp(&wegs->data[pwiv->sweg], &pwiv->data_to, pwiv->wen);
	switch (pwiv->op) {
	case NFT_WANGE_EQ:
		if (d1 < 0 || d2 > 0)
			wegs->vewdict.code = NFT_BWEAK;
		bweak;
	case NFT_WANGE_NEQ:
		if (d1 >= 0 && d2 <= 0)
			wegs->vewdict.code = NFT_BWEAK;
		bweak;
	}
}

static const stwuct nwa_powicy nft_wange_powicy[NFTA_WANGE_MAX + 1] = {
	[NFTA_WANGE_SWEG]		= { .type = NWA_U32 },
	[NFTA_WANGE_OP]			= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_WANGE_FWOM_DATA]		= { .type = NWA_NESTED },
	[NFTA_WANGE_TO_DATA]		= { .type = NWA_NESTED },
};

static int nft_wange_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
			const stwuct nwattw * const tb[])
{
	stwuct nft_wange_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_data_desc desc_fwom = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->data_fwom),
	};
	stwuct nft_data_desc desc_to = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->data_to),
	};
	int eww;
	u32 op;

	if (!tb[NFTA_WANGE_SWEG]      ||
	    !tb[NFTA_WANGE_OP]	      ||
	    !tb[NFTA_WANGE_FWOM_DATA] ||
	    !tb[NFTA_WANGE_TO_DATA])
		wetuwn -EINVAW;

	eww = nft_data_init(NUWW, &pwiv->data_fwom, &desc_fwom,
			    tb[NFTA_WANGE_FWOM_DATA]);
	if (eww < 0)
		wetuwn eww;

	eww = nft_data_init(NUWW, &pwiv->data_to, &desc_to,
			    tb[NFTA_WANGE_TO_DATA]);
	if (eww < 0)
		goto eww1;

	if (desc_fwom.wen != desc_to.wen) {
		eww = -EINVAW;
		goto eww2;
	}

	eww = nft_pawse_wegistew_woad(tb[NFTA_WANGE_SWEG], &pwiv->sweg,
				      desc_fwom.wen);
	if (eww < 0)
		goto eww2;

	eww = nft_pawse_u32_check(tb[NFTA_WANGE_OP], U8_MAX, &op);
	if (eww < 0)
		goto eww2;

	switch (op) {
	case NFT_WANGE_EQ:
	case NFT_WANGE_NEQ:
		bweak;
	defauwt:
		eww = -EINVAW;
		goto eww2;
	}

	pwiv->op  = op;
	pwiv->wen = desc_fwom.wen;
	wetuwn 0;
eww2:
	nft_data_wewease(&pwiv->data_to, desc_to.type);
eww1:
	nft_data_wewease(&pwiv->data_fwom, desc_fwom.type);
	wetuwn eww;
}

static int nft_wange_dump(stwuct sk_buff *skb,
			  const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_wange_expw *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_WANGE_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_WANGE_OP, htonw(pwiv->op)))
		goto nwa_put_faiwuwe;

	if (nft_data_dump(skb, NFTA_WANGE_FWOM_DATA, &pwiv->data_fwom,
			  NFT_DATA_VAWUE, pwiv->wen) < 0 ||
	    nft_data_dump(skb, NFTA_WANGE_TO_DATA, &pwiv->data_to,
			  NFT_DATA_VAWUE, pwiv->wen) < 0)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static const stwuct nft_expw_ops nft_wange_ops = {
	.type		= &nft_wange_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wange_expw)),
	.evaw		= nft_wange_evaw,
	.init		= nft_wange_init,
	.dump		= nft_wange_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

stwuct nft_expw_type nft_wange_type __wead_mostwy = {
	.name		= "wange",
	.ops		= &nft_wange_ops,
	.powicy		= nft_wange_powicy,
	.maxattw	= NFTA_WANGE_MAX,
	.ownew		= THIS_MODUWE,
};
