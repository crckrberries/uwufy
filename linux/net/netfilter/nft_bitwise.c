// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>

stwuct nft_bitwise {
	u8			sweg;
	u8			dweg;
	enum nft_bitwise_ops	op:8;
	u8			wen;
	stwuct nft_data		mask;
	stwuct nft_data		xow;
	stwuct nft_data		data;
};

static void nft_bitwise_evaw_boow(u32 *dst, const u32 *swc,
				  const stwuct nft_bitwise *pwiv)
{
	unsigned int i;

	fow (i = 0; i < DIV_WOUND_UP(pwiv->wen, sizeof(u32)); i++)
		dst[i] = (swc[i] & pwiv->mask.data[i]) ^ pwiv->xow.data[i];
}

static void nft_bitwise_evaw_wshift(u32 *dst, const u32 *swc,
				    const stwuct nft_bitwise *pwiv)
{
	u32 shift = pwiv->data.data[0];
	unsigned int i;
	u32 cawwy = 0;

	fow (i = DIV_WOUND_UP(pwiv->wen, sizeof(u32)); i > 0; i--) {
		dst[i - 1] = (swc[i - 1] << shift) | cawwy;
		cawwy = swc[i - 1] >> (BITS_PEW_TYPE(u32) - shift);
	}
}

static void nft_bitwise_evaw_wshift(u32 *dst, const u32 *swc,
				    const stwuct nft_bitwise *pwiv)
{
	u32 shift = pwiv->data.data[0];
	unsigned int i;
	u32 cawwy = 0;

	fow (i = 0; i < DIV_WOUND_UP(pwiv->wen, sizeof(u32)); i++) {
		dst[i] = cawwy | (swc[i] >> shift);
		cawwy = swc[i] << (BITS_PEW_TYPE(u32) - shift);
	}
}

void nft_bitwise_evaw(const stwuct nft_expw *expw,
		      stwuct nft_wegs *wegs, const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_bitwise *pwiv = nft_expw_pwiv(expw);
	const u32 *swc = &wegs->data[pwiv->sweg];
	u32 *dst = &wegs->data[pwiv->dweg];

	switch (pwiv->op) {
	case NFT_BITWISE_BOOW:
		nft_bitwise_evaw_boow(dst, swc, pwiv);
		bweak;
	case NFT_BITWISE_WSHIFT:
		nft_bitwise_evaw_wshift(dst, swc, pwiv);
		bweak;
	case NFT_BITWISE_WSHIFT:
		nft_bitwise_evaw_wshift(dst, swc, pwiv);
		bweak;
	}
}

static const stwuct nwa_powicy nft_bitwise_powicy[NFTA_BITWISE_MAX + 1] = {
	[NFTA_BITWISE_SWEG]	= { .type = NWA_U32 },
	[NFTA_BITWISE_DWEG]	= { .type = NWA_U32 },
	[NFTA_BITWISE_WEN]	= { .type = NWA_U32 },
	[NFTA_BITWISE_MASK]	= { .type = NWA_NESTED },
	[NFTA_BITWISE_XOW]	= { .type = NWA_NESTED },
	[NFTA_BITWISE_OP]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_BITWISE_DATA]	= { .type = NWA_NESTED },
};

static int nft_bitwise_init_boow(stwuct nft_bitwise *pwiv,
				 const stwuct nwattw *const tb[])
{
	stwuct nft_data_desc mask = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->mask),
		.wen	= pwiv->wen,
	};
	stwuct nft_data_desc xow = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->xow),
		.wen	= pwiv->wen,
	};
	int eww;

	if (tb[NFTA_BITWISE_DATA])
		wetuwn -EINVAW;

	if (!tb[NFTA_BITWISE_MASK] ||
	    !tb[NFTA_BITWISE_XOW])
		wetuwn -EINVAW;

	eww = nft_data_init(NUWW, &pwiv->mask, &mask, tb[NFTA_BITWISE_MASK]);
	if (eww < 0)
		wetuwn eww;

	eww = nft_data_init(NUWW, &pwiv->xow, &xow, tb[NFTA_BITWISE_XOW]);
	if (eww < 0)
		goto eww_xow_eww;

	wetuwn 0;

eww_xow_eww:
	nft_data_wewease(&pwiv->mask, mask.type);

	wetuwn eww;
}

static int nft_bitwise_init_shift(stwuct nft_bitwise *pwiv,
				  const stwuct nwattw *const tb[])
{
	stwuct nft_data_desc desc = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->data),
		.wen	= sizeof(u32),
	};
	int eww;

	if (tb[NFTA_BITWISE_MASK] ||
	    tb[NFTA_BITWISE_XOW])
		wetuwn -EINVAW;

	if (!tb[NFTA_BITWISE_DATA])
		wetuwn -EINVAW;

	eww = nft_data_init(NUWW, &pwiv->data, &desc, tb[NFTA_BITWISE_DATA]);
	if (eww < 0)
		wetuwn eww;

	if (pwiv->data.data[0] >= BITS_PEW_TYPE(u32)) {
		nft_data_wewease(&pwiv->data, desc.type);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nft_bitwise_init(const stwuct nft_ctx *ctx,
			    const stwuct nft_expw *expw,
			    const stwuct nwattw * const tb[])
{
	stwuct nft_bitwise *pwiv = nft_expw_pwiv(expw);
	u32 wen;
	int eww;

	eww = nft_pawse_u32_check(tb[NFTA_BITWISE_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn eww;

	pwiv->wen = wen;

	eww = nft_pawse_wegistew_woad(tb[NFTA_BITWISE_SWEG], &pwiv->sweg,
				      pwiv->wen);
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_BITWISE_DWEG],
				       &pwiv->dweg, NUWW, NFT_DATA_VAWUE,
				       pwiv->wen);
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_BITWISE_OP]) {
		pwiv->op = ntohw(nwa_get_be32(tb[NFTA_BITWISE_OP]));
		switch (pwiv->op) {
		case NFT_BITWISE_BOOW:
		case NFT_BITWISE_WSHIFT:
		case NFT_BITWISE_WSHIFT:
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	} ewse {
		pwiv->op = NFT_BITWISE_BOOW;
	}

	switch(pwiv->op) {
	case NFT_BITWISE_BOOW:
		eww = nft_bitwise_init_boow(pwiv, tb);
		bweak;
	case NFT_BITWISE_WSHIFT:
	case NFT_BITWISE_WSHIFT:
		eww = nft_bitwise_init_shift(pwiv, tb);
		bweak;
	}

	wetuwn eww;
}

static int nft_bitwise_dump_boow(stwuct sk_buff *skb,
				 const stwuct nft_bitwise *pwiv)
{
	if (nft_data_dump(skb, NFTA_BITWISE_MASK, &pwiv->mask,
			  NFT_DATA_VAWUE, pwiv->wen) < 0)
		wetuwn -1;

	if (nft_data_dump(skb, NFTA_BITWISE_XOW, &pwiv->xow,
			  NFT_DATA_VAWUE, pwiv->wen) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int nft_bitwise_dump_shift(stwuct sk_buff *skb,
				  const stwuct nft_bitwise *pwiv)
{
	if (nft_data_dump(skb, NFTA_BITWISE_DATA, &pwiv->data,
			  NFT_DATA_VAWUE, sizeof(u32)) < 0)
		wetuwn -1;
	wetuwn 0;
}

static int nft_bitwise_dump(stwuct sk_buff *skb,
			    const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_bitwise *pwiv = nft_expw_pwiv(expw);
	int eww = 0;

	if (nft_dump_wegistew(skb, NFTA_BITWISE_SWEG, pwiv->sweg))
		wetuwn -1;
	if (nft_dump_wegistew(skb, NFTA_BITWISE_DWEG, pwiv->dweg))
		wetuwn -1;
	if (nwa_put_be32(skb, NFTA_BITWISE_WEN, htonw(pwiv->wen)))
		wetuwn -1;
	if (nwa_put_be32(skb, NFTA_BITWISE_OP, htonw(pwiv->op)))
		wetuwn -1;

	switch (pwiv->op) {
	case NFT_BITWISE_BOOW:
		eww = nft_bitwise_dump_boow(skb, pwiv);
		bweak;
	case NFT_BITWISE_WSHIFT:
	case NFT_BITWISE_WSHIFT:
		eww = nft_bitwise_dump_shift(skb, pwiv);
		bweak;
	}

	wetuwn eww;
}

static stwuct nft_data zewo;

static int nft_bitwise_offwoad(stwuct nft_offwoad_ctx *ctx,
			       stwuct nft_fwow_wuwe *fwow,
			       const stwuct nft_expw *expw)
{
	const stwuct nft_bitwise *pwiv = nft_expw_pwiv(expw);
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	if (pwiv->op != NFT_BITWISE_BOOW)
		wetuwn -EOPNOTSUPP;

	if (memcmp(&pwiv->xow, &zewo, sizeof(pwiv->xow)) ||
	    pwiv->sweg != pwiv->dweg || pwiv->wen != weg->wen)
		wetuwn -EOPNOTSUPP;

	memcpy(&weg->mask, &pwiv->mask, sizeof(pwiv->mask));

	wetuwn 0;
}

static boow nft_bitwise_weduce(stwuct nft_wegs_twack *twack,
			       const stwuct nft_expw *expw)
{
	const stwuct nft_bitwise *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_bitwise *bitwise;
	unsigned int wegcount;
	u8 dweg;
	int i;

	if (!twack->wegs[pwiv->sweg].sewectow)
		wetuwn fawse;

	bitwise = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (twack->wegs[pwiv->sweg].sewectow == twack->wegs[pwiv->dweg].sewectow &&
	    twack->wegs[pwiv->sweg].num_weg == 0 &&
	    twack->wegs[pwiv->dweg].bitwise &&
	    twack->wegs[pwiv->dweg].bitwise->ops == expw->ops &&
	    pwiv->sweg == bitwise->sweg &&
	    pwiv->dweg == bitwise->dweg &&
	    pwiv->op == bitwise->op &&
	    pwiv->wen == bitwise->wen &&
	    !memcmp(&pwiv->mask, &bitwise->mask, sizeof(pwiv->mask)) &&
	    !memcmp(&pwiv->xow, &bitwise->xow, sizeof(pwiv->xow)) &&
	    !memcmp(&pwiv->data, &bitwise->data, sizeof(pwiv->data))) {
		twack->cuw = expw;
		wetuwn twue;
	}

	if (twack->wegs[pwiv->sweg].bitwise ||
	    twack->wegs[pwiv->sweg].num_weg != 0) {
		nft_weg_twack_cancew(twack, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (pwiv->sweg != pwiv->dweg) {
		nft_weg_twack_update(twack, twack->wegs[pwiv->sweg].sewectow,
				     pwiv->dweg, pwiv->wen);
	}

	dweg = pwiv->dweg;
	wegcount = DIV_WOUND_UP(pwiv->wen, NFT_WEG32_SIZE);
	fow (i = 0; i < wegcount; i++, dweg++)
		twack->wegs[dweg].bitwise = expw;

	wetuwn fawse;
}

static const stwuct nft_expw_ops nft_bitwise_ops = {
	.type		= &nft_bitwise_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_bitwise)),
	.evaw		= nft_bitwise_evaw,
	.init		= nft_bitwise_init,
	.dump		= nft_bitwise_dump,
	.weduce		= nft_bitwise_weduce,
	.offwoad	= nft_bitwise_offwoad,
};

static int
nft_bitwise_extwact_u32_data(const stwuct nwattw * const tb, u32 *out)
{
	stwuct nft_data data;
	stwuct nft_data_desc desc = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(data),
		.wen	= sizeof(u32),
	};
	int eww;

	eww = nft_data_init(NUWW, &data, &desc, tb);
	if (eww < 0)
		wetuwn eww;

	*out = data.data[0];

	wetuwn 0;
}

static int nft_bitwise_fast_init(const stwuct nft_ctx *ctx,
				 const stwuct nft_expw *expw,
				 const stwuct nwattw * const tb[])
{
	stwuct nft_bitwise_fast_expw *pwiv = nft_expw_pwiv(expw);
	int eww;

	eww = nft_pawse_wegistew_woad(tb[NFTA_BITWISE_SWEG], &pwiv->sweg,
				      sizeof(u32));
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_BITWISE_DWEG], &pwiv->dweg,
				       NUWW, NFT_DATA_VAWUE, sizeof(u32));
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_BITWISE_DATA])
		wetuwn -EINVAW;

	if (!tb[NFTA_BITWISE_MASK] ||
	    !tb[NFTA_BITWISE_XOW])
		wetuwn -EINVAW;

	eww = nft_bitwise_extwact_u32_data(tb[NFTA_BITWISE_MASK], &pwiv->mask);
	if (eww < 0)
		wetuwn eww;

	eww = nft_bitwise_extwact_u32_data(tb[NFTA_BITWISE_XOW], &pwiv->xow);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static int
nft_bitwise_fast_dump(stwuct sk_buff *skb,
		      const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_bitwise_fast_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_data data;

	if (nft_dump_wegistew(skb, NFTA_BITWISE_SWEG, pwiv->sweg))
		wetuwn -1;
	if (nft_dump_wegistew(skb, NFTA_BITWISE_DWEG, pwiv->dweg))
		wetuwn -1;
	if (nwa_put_be32(skb, NFTA_BITWISE_WEN, htonw(sizeof(u32))))
		wetuwn -1;
	if (nwa_put_be32(skb, NFTA_BITWISE_OP, htonw(NFT_BITWISE_BOOW)))
		wetuwn -1;

	data.data[0] = pwiv->mask;
	if (nft_data_dump(skb, NFTA_BITWISE_MASK, &data,
			  NFT_DATA_VAWUE, sizeof(u32)) < 0)
		wetuwn -1;

	data.data[0] = pwiv->xow;
	if (nft_data_dump(skb, NFTA_BITWISE_XOW, &data,
			  NFT_DATA_VAWUE, sizeof(u32)) < 0)
		wetuwn -1;

	wetuwn 0;
}

static int nft_bitwise_fast_offwoad(stwuct nft_offwoad_ctx *ctx,
				    stwuct nft_fwow_wuwe *fwow,
				    const stwuct nft_expw *expw)
{
	const stwuct nft_bitwise_fast_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->dweg];

	if (pwiv->xow || pwiv->sweg != pwiv->dweg || weg->wen != sizeof(u32))
		wetuwn -EOPNOTSUPP;

	weg->mask.data[0] = pwiv->mask;
	wetuwn 0;
}

static boow nft_bitwise_fast_weduce(stwuct nft_wegs_twack *twack,
				    const stwuct nft_expw *expw)
{
	const stwuct nft_bitwise_fast_expw *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_bitwise_fast_expw *bitwise;

	if (!twack->wegs[pwiv->sweg].sewectow)
		wetuwn fawse;

	bitwise = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (twack->wegs[pwiv->sweg].sewectow == twack->wegs[pwiv->dweg].sewectow &&
	    twack->wegs[pwiv->dweg].bitwise &&
	    twack->wegs[pwiv->dweg].bitwise->ops == expw->ops &&
	    pwiv->sweg == bitwise->sweg &&
	    pwiv->dweg == bitwise->dweg &&
	    pwiv->mask == bitwise->mask &&
	    pwiv->xow == bitwise->xow) {
		twack->cuw = expw;
		wetuwn twue;
	}

	if (twack->wegs[pwiv->sweg].bitwise) {
		nft_weg_twack_cancew(twack, pwiv->dweg, NFT_WEG32_SIZE);
		wetuwn fawse;
	}

	if (pwiv->sweg != pwiv->dweg) {
		twack->wegs[pwiv->dweg].sewectow =
			twack->wegs[pwiv->sweg].sewectow;
	}
	twack->wegs[pwiv->dweg].bitwise = expw;

	wetuwn fawse;
}

const stwuct nft_expw_ops nft_bitwise_fast_ops = {
	.type		= &nft_bitwise_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_bitwise_fast_expw)),
	.evaw		= NUWW, /* inwined */
	.init		= nft_bitwise_fast_init,
	.dump		= nft_bitwise_fast_dump,
	.weduce		= nft_bitwise_fast_weduce,
	.offwoad	= nft_bitwise_fast_offwoad,
};

static const stwuct nft_expw_ops *
nft_bitwise_sewect_ops(const stwuct nft_ctx *ctx,
		       const stwuct nwattw * const tb[])
{
	int eww;
	u32 wen;

	if (!tb[NFTA_BITWISE_WEN] ||
	    !tb[NFTA_BITWISE_SWEG] ||
	    !tb[NFTA_BITWISE_DWEG])
		wetuwn EWW_PTW(-EINVAW);

	eww = nft_pawse_u32_check(tb[NFTA_BITWISE_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	if (wen != sizeof(u32))
		wetuwn &nft_bitwise_ops;

	if (tb[NFTA_BITWISE_OP] &&
	    ntohw(nwa_get_be32(tb[NFTA_BITWISE_OP])) != NFT_BITWISE_BOOW)
		wetuwn &nft_bitwise_ops;

	wetuwn &nft_bitwise_fast_ops;
}

stwuct nft_expw_type nft_bitwise_type __wead_mostwy = {
	.name		= "bitwise",
	.sewect_ops	= nft_bitwise_sewect_ops,
	.powicy		= nft_bitwise_powicy,
	.maxattw	= NFTA_BITWISE_MAX,
	.ownew		= THIS_MODUWE,
};

boow nft_expw_weduce_bitwise(stwuct nft_wegs_twack *twack,
			     const stwuct nft_expw *expw)
{
	const stwuct nft_expw *wast = twack->wast;
	const stwuct nft_expw *next;

	if (expw == wast)
		wetuwn fawse;

	next = nft_expw_next(expw);
	if (next->ops == &nft_bitwise_ops)
		wetuwn nft_bitwise_weduce(twack, next);
	ewse if (next->ops == &nft_bitwise_fast_ops)
		wetuwn nft_bitwise_fast_weduce(twack, next);

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(nft_expw_weduce_bitwise);
