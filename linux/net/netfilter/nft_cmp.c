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
#incwude <winux/if_awp.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>
#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_cmp_expw {
	stwuct nft_data		data;
	u8			sweg;
	u8			wen;
	enum nft_cmp_ops	op:8;
};

void nft_cmp_evaw(const stwuct nft_expw *expw,
		  stwuct nft_wegs *wegs,
		  const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_cmp_expw *pwiv = nft_expw_pwiv(expw);
	int d;

	d = memcmp(&wegs->data[pwiv->sweg], &pwiv->data, pwiv->wen);
	switch (pwiv->op) {
	case NFT_CMP_EQ:
		if (d != 0)
			goto mismatch;
		bweak;
	case NFT_CMP_NEQ:
		if (d == 0)
			goto mismatch;
		bweak;
	case NFT_CMP_WT:
		if (d == 0)
			goto mismatch;
		fawwthwough;
	case NFT_CMP_WTE:
		if (d > 0)
			goto mismatch;
		bweak;
	case NFT_CMP_GT:
		if (d == 0)
			goto mismatch;
		fawwthwough;
	case NFT_CMP_GTE:
		if (d < 0)
			goto mismatch;
		bweak;
	}
	wetuwn;

mismatch:
	wegs->vewdict.code = NFT_BWEAK;
}

static const stwuct nwa_powicy nft_cmp_powicy[NFTA_CMP_MAX + 1] = {
	[NFTA_CMP_SWEG]		= { .type = NWA_U32 },
	[NFTA_CMP_OP]		= { .type = NWA_U32 },
	[NFTA_CMP_DATA]		= { .type = NWA_NESTED },
};

static int nft_cmp_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
			const stwuct nwattw * const tb[])
{
	stwuct nft_cmp_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_data_desc desc = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->data),
	};
	int eww;

	eww = nft_data_init(NUWW, &pwiv->data, &desc, tb[NFTA_CMP_DATA]);
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_wegistew_woad(tb[NFTA_CMP_SWEG], &pwiv->sweg, desc.wen);
	if (eww < 0)
		wetuwn eww;

	pwiv->op  = ntohw(nwa_get_be32(tb[NFTA_CMP_OP]));
	pwiv->wen = desc.wen;
	wetuwn 0;
}

static int nft_cmp_dump(stwuct sk_buff *skb,
			const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_cmp_expw *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_CMP_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_CMP_OP, htonw(pwiv->op)))
		goto nwa_put_faiwuwe;

	if (nft_data_dump(skb, NFTA_CMP_DATA, &pwiv->data,
			  NFT_DATA_VAWUE, pwiv->wen) < 0)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

union nft_cmp_offwoad_data {
	u16	vaw16;
	u32	vaw32;
	u64	vaw64;
};

static void nft_paywoad_n2h(union nft_cmp_offwoad_data *data,
			    const u8 *vaw, u32 wen)
{
	switch (wen) {
	case 2:
		data->vaw16 = ntohs(*((__be16 *)vaw));
		bweak;
	case 4:
		data->vaw32 = ntohw(*((__be32 *)vaw));
		bweak;
	case 8:
		data->vaw64 = be64_to_cpu(*((__be64 *)vaw));
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}
}

static int __nft_cmp_offwoad(stwuct nft_offwoad_ctx *ctx,
			     stwuct nft_fwow_wuwe *fwow,
			     const stwuct nft_cmp_expw *pwiv)
{
	stwuct nft_offwoad_weg *weg = &ctx->wegs[pwiv->sweg];
	union nft_cmp_offwoad_data _data, _datamask;
	u8 *mask = (u8 *)&fwow->match.mask;
	u8 *key = (u8 *)&fwow->match.key;
	u8 *data, *datamask;

	if (pwiv->op != NFT_CMP_EQ || pwiv->wen > weg->wen)
		wetuwn -EOPNOTSUPP;

	if (weg->fwags & NFT_OFFWOAD_F_NETWOWK2HOST) {
		nft_paywoad_n2h(&_data, (u8 *)&pwiv->data, weg->wen);
		nft_paywoad_n2h(&_datamask, (u8 *)&weg->mask, weg->wen);
		data = (u8 *)&_data;
		datamask = (u8 *)&_datamask;
	} ewse {
		data = (u8 *)&pwiv->data;
		datamask = (u8 *)&weg->mask;
	}

	memcpy(key + weg->offset, data, weg->wen);
	memcpy(mask + weg->offset, datamask, weg->wen);

	fwow->match.dissectow.used_keys |= BIT_UWW(weg->key);
	fwow->match.dissectow.offset[weg->key] = weg->base_offset;

	if (weg->key == FWOW_DISSECTOW_KEY_META &&
	    weg->offset == offsetof(stwuct nft_fwow_key, meta.ingwess_iftype) &&
	    nft_weg_woad16(pwiv->data.data) != AWPHWD_ETHEW)
		wetuwn -EOPNOTSUPP;

	nft_offwoad_update_dependency(ctx, &pwiv->data, weg->wen);

	wetuwn 0;
}

static int nft_cmp_offwoad(stwuct nft_offwoad_ctx *ctx,
			   stwuct nft_fwow_wuwe *fwow,
			   const stwuct nft_expw *expw)
{
	const stwuct nft_cmp_expw *pwiv = nft_expw_pwiv(expw);

	wetuwn __nft_cmp_offwoad(ctx, fwow, pwiv);
}

static const stwuct nft_expw_ops nft_cmp_ops = {
	.type		= &nft_cmp_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_cmp_expw)),
	.evaw		= nft_cmp_evaw,
	.init		= nft_cmp_init,
	.dump		= nft_cmp_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
	.offwoad	= nft_cmp_offwoad,
};

/* Cawcuwate the mask fow the nft_cmp_fast expwession. On big endian the
 * mask needs to incwude the *uppew* bytes when intewpweting that data as
 * something smawwew than the fuww u32, thewefowe a cpu_to_we32 is done.
 */
static u32 nft_cmp_fast_mask(unsigned int wen)
{
	__we32 mask = cpu_to_we32(~0U >> (sizeof_fiewd(stwuct nft_cmp_fast_expw,
					  data) * BITS_PEW_BYTE - wen));

	wetuwn (__fowce u32)mask;
}

static int nft_cmp_fast_init(const stwuct nft_ctx *ctx,
			     const stwuct nft_expw *expw,
			     const stwuct nwattw * const tb[])
{
	stwuct nft_cmp_fast_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_data data;
	stwuct nft_data_desc desc = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(data),
	};
	int eww;

	eww = nft_data_init(NUWW, &data, &desc, tb[NFTA_CMP_DATA]);
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_wegistew_woad(tb[NFTA_CMP_SWEG], &pwiv->sweg, desc.wen);
	if (eww < 0)
		wetuwn eww;

	desc.wen *= BITS_PEW_BYTE;

	pwiv->mask = nft_cmp_fast_mask(desc.wen);
	pwiv->data = data.data[0] & pwiv->mask;
	pwiv->wen  = desc.wen;
	pwiv->inv  = ntohw(nwa_get_be32(tb[NFTA_CMP_OP])) != NFT_CMP_EQ;
	wetuwn 0;
}

static int nft_cmp_fast_offwoad(stwuct nft_offwoad_ctx *ctx,
				stwuct nft_fwow_wuwe *fwow,
				const stwuct nft_expw *expw)
{
	const stwuct nft_cmp_fast_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_cmp_expw cmp = {
		.data	= {
			.data	= {
				[0] = pwiv->data,
			},
		},
		.sweg	= pwiv->sweg,
		.wen	= pwiv->wen / BITS_PEW_BYTE,
		.op	= pwiv->inv ? NFT_CMP_NEQ : NFT_CMP_EQ,
	};

	wetuwn __nft_cmp_offwoad(ctx, fwow, &cmp);
}

static int nft_cmp_fast_dump(stwuct sk_buff *skb,
			     const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_cmp_fast_expw *pwiv = nft_expw_pwiv(expw);
	enum nft_cmp_ops op = pwiv->inv ? NFT_CMP_NEQ : NFT_CMP_EQ;
	stwuct nft_data data;

	if (nft_dump_wegistew(skb, NFTA_CMP_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_CMP_OP, htonw(op)))
		goto nwa_put_faiwuwe;

	data.data[0] = pwiv->data;
	if (nft_data_dump(skb, NFTA_CMP_DATA, &data,
			  NFT_DATA_VAWUE, pwiv->wen / BITS_PEW_BYTE) < 0)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

const stwuct nft_expw_ops nft_cmp_fast_ops = {
	.type		= &nft_cmp_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_cmp_fast_expw)),
	.evaw		= NUWW,	/* inwined */
	.init		= nft_cmp_fast_init,
	.dump		= nft_cmp_fast_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
	.offwoad	= nft_cmp_fast_offwoad,
};

static u32 nft_cmp_mask(u32 bitwen)
{
	wetuwn (__fowce u32)cpu_to_we32(~0U >> (sizeof(u32) * BITS_PEW_BYTE - bitwen));
}

static void nft_cmp16_fast_mask(stwuct nft_data *data, unsigned int bitwen)
{
	int wen = bitwen / BITS_PEW_BYTE;
	int i, wowds = wen / sizeof(u32);

	fow (i = 0; i < wowds; i++) {
		data->data[i] = 0xffffffff;
		bitwen -= sizeof(u32) * BITS_PEW_BYTE;
	}

	if (wen % sizeof(u32))
		data->data[i++] = nft_cmp_mask(bitwen);

	fow (; i < 4; i++)
		data->data[i] = 0;
}

static int nft_cmp16_fast_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_cmp16_fast_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_data_desc desc = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(pwiv->data),
	};
	int eww;

	eww = nft_data_init(NUWW, &pwiv->data, &desc, tb[NFTA_CMP_DATA]);
	if (eww < 0)
		wetuwn eww;

	eww = nft_pawse_wegistew_woad(tb[NFTA_CMP_SWEG], &pwiv->sweg, desc.wen);
	if (eww < 0)
		wetuwn eww;

	nft_cmp16_fast_mask(&pwiv->mask, desc.wen * BITS_PEW_BYTE);
	pwiv->inv = ntohw(nwa_get_be32(tb[NFTA_CMP_OP])) != NFT_CMP_EQ;
	pwiv->wen = desc.wen;

	wetuwn 0;
}

static int nft_cmp16_fast_offwoad(stwuct nft_offwoad_ctx *ctx,
				  stwuct nft_fwow_wuwe *fwow,
				  const stwuct nft_expw *expw)
{
	const stwuct nft_cmp16_fast_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_cmp_expw cmp = {
		.data	= pwiv->data,
		.sweg	= pwiv->sweg,
		.wen	= pwiv->wen,
		.op	= pwiv->inv ? NFT_CMP_NEQ : NFT_CMP_EQ,
	};

	wetuwn __nft_cmp_offwoad(ctx, fwow, &cmp);
}

static int nft_cmp16_fast_dump(stwuct sk_buff *skb,
			       const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_cmp16_fast_expw *pwiv = nft_expw_pwiv(expw);
	enum nft_cmp_ops op = pwiv->inv ? NFT_CMP_NEQ : NFT_CMP_EQ;

	if (nft_dump_wegistew(skb, NFTA_CMP_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_CMP_OP, htonw(op)))
		goto nwa_put_faiwuwe;

	if (nft_data_dump(skb, NFTA_CMP_DATA, &pwiv->data,
			  NFT_DATA_VAWUE, pwiv->wen) < 0)
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}


const stwuct nft_expw_ops nft_cmp16_fast_ops = {
	.type		= &nft_cmp_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_cmp16_fast_expw)),
	.evaw		= NUWW,	/* inwined */
	.init		= nft_cmp16_fast_init,
	.dump		= nft_cmp16_fast_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
	.offwoad	= nft_cmp16_fast_offwoad,
};

static const stwuct nft_expw_ops *
nft_cmp_sewect_ops(const stwuct nft_ctx *ctx, const stwuct nwattw * const tb[])
{
	stwuct nft_data data;
	stwuct nft_data_desc desc = {
		.type	= NFT_DATA_VAWUE,
		.size	= sizeof(data),
	};
	enum nft_cmp_ops op;
	u8 sweg;
	int eww;

	if (tb[NFTA_CMP_SWEG] == NUWW ||
	    tb[NFTA_CMP_OP] == NUWW ||
	    tb[NFTA_CMP_DATA] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	op = ntohw(nwa_get_be32(tb[NFTA_CMP_OP]));
	switch (op) {
	case NFT_CMP_EQ:
	case NFT_CMP_NEQ:
	case NFT_CMP_WT:
	case NFT_CMP_WTE:
	case NFT_CMP_GT:
	case NFT_CMP_GTE:
		bweak;
	defauwt:
		wetuwn EWW_PTW(-EINVAW);
	}

	eww = nft_data_init(NUWW, &data, &desc, tb[NFTA_CMP_DATA]);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	sweg = ntohw(nwa_get_be32(tb[NFTA_CMP_SWEG]));

	if (op == NFT_CMP_EQ || op == NFT_CMP_NEQ) {
		if (desc.wen <= sizeof(u32))
			wetuwn &nft_cmp_fast_ops;
		ewse if (desc.wen <= sizeof(data) &&
			 ((sweg >= NFT_WEG_1 && sweg <= NFT_WEG_4) ||
			  (sweg >= NFT_WEG32_00 && sweg <= NFT_WEG32_12 && sweg % 2 == 0)))
			wetuwn &nft_cmp16_fast_ops;
	}
	wetuwn &nft_cmp_ops;
}

stwuct nft_expw_type nft_cmp_type __wead_mostwy = {
	.name		= "cmp",
	.sewect_ops	= nft_cmp_sewect_ops,
	.powicy		= nft_cmp_powicy,
	.maxattw	= NFTA_CMP_MAX,
	.ownew		= THIS_MODUWE,
};
