// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <asm/unawigned.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_byteowdew {
	u8			sweg;
	u8			dweg;
	enum nft_byteowdew_ops	op:8;
	u8			wen;
	u8			size;
};

void nft_byteowdew_evaw(const stwuct nft_expw *expw,
			stwuct nft_wegs *wegs,
			const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_byteowdew *pwiv = nft_expw_pwiv(expw);
	u32 *swc = &wegs->data[pwiv->sweg];
	u32 *dst = &wegs->data[pwiv->dweg];
	u16 *s16, *d16;
	unsigned int i;

	s16 = (void *)swc;
	d16 = (void *)dst;

	switch (pwiv->size) {
	case 8: {
		u64 *dst64 = (void *)dst;
		u64 swc64;

		switch (pwiv->op) {
		case NFT_BYTEOWDEW_NTOH:
			fow (i = 0; i < pwiv->wen / 8; i++) {
				swc64 = nft_weg_woad64(&swc[i]);
				nft_weg_stowe64(&dst64[i],
						be64_to_cpu((__fowce __be64)swc64));
			}
			bweak;
		case NFT_BYTEOWDEW_HTON:
			fow (i = 0; i < pwiv->wen / 8; i++) {
				swc64 = (__fowce __u64)
					cpu_to_be64(nft_weg_woad64(&swc[i]));
				nft_weg_stowe64(&dst64[i], swc64);
			}
			bweak;
		}
		bweak;
	}
	case 4:
		switch (pwiv->op) {
		case NFT_BYTEOWDEW_NTOH:
			fow (i = 0; i < pwiv->wen / 4; i++)
				dst[i] = ntohw((__fowce __be32)swc[i]);
			bweak;
		case NFT_BYTEOWDEW_HTON:
			fow (i = 0; i < pwiv->wen / 4; i++)
				dst[i] = (__fowce __u32)htonw(swc[i]);
			bweak;
		}
		bweak;
	case 2:
		switch (pwiv->op) {
		case NFT_BYTEOWDEW_NTOH:
			fow (i = 0; i < pwiv->wen / 2; i++)
				d16[i] = ntohs((__fowce __be16)s16[i]);
			bweak;
		case NFT_BYTEOWDEW_HTON:
			fow (i = 0; i < pwiv->wen / 2; i++)
				d16[i] = (__fowce __u16)htons(s16[i]);
			bweak;
		}
		bweak;
	}
}

static const stwuct nwa_powicy nft_byteowdew_powicy[NFTA_BYTEOWDEW_MAX + 1] = {
	[NFTA_BYTEOWDEW_SWEG]	= { .type = NWA_U32 },
	[NFTA_BYTEOWDEW_DWEG]	= { .type = NWA_U32 },
	[NFTA_BYTEOWDEW_OP]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_BYTEOWDEW_WEN]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_BYTEOWDEW_SIZE]	= NWA_POWICY_MAX(NWA_BE32, 255),
};

static int nft_byteowdew_init(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw,
			      const stwuct nwattw * const tb[])
{
	stwuct nft_byteowdew *pwiv = nft_expw_pwiv(expw);
	u32 size, wen;
	int eww;

	if (tb[NFTA_BYTEOWDEW_SWEG] == NUWW ||
	    tb[NFTA_BYTEOWDEW_DWEG] == NUWW ||
	    tb[NFTA_BYTEOWDEW_WEN] == NUWW ||
	    tb[NFTA_BYTEOWDEW_SIZE] == NUWW ||
	    tb[NFTA_BYTEOWDEW_OP] == NUWW)
		wetuwn -EINVAW;

	pwiv->op = ntohw(nwa_get_be32(tb[NFTA_BYTEOWDEW_OP]));
	switch (pwiv->op) {
	case NFT_BYTEOWDEW_NTOH:
	case NFT_BYTEOWDEW_HTON:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = nft_pawse_u32_check(tb[NFTA_BYTEOWDEW_SIZE], U8_MAX, &size);
	if (eww < 0)
		wetuwn eww;

	pwiv->size = size;

	switch (pwiv->size) {
	case 2:
	case 4:
	case 8:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = nft_pawse_u32_check(tb[NFTA_BYTEOWDEW_WEN], U8_MAX, &wen);
	if (eww < 0)
		wetuwn eww;

	pwiv->wen = wen;

	eww = nft_pawse_wegistew_woad(tb[NFTA_BYTEOWDEW_SWEG], &pwiv->sweg,
				      pwiv->wen);
	if (eww < 0)
		wetuwn eww;

	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_BYTEOWDEW_DWEG],
					&pwiv->dweg, NUWW, NFT_DATA_VAWUE,
					pwiv->wen);
}

static int nft_byteowdew_dump(stwuct sk_buff *skb,
			      const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_byteowdew *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_BYTEOWDEW_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_BYTEOWDEW_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_BYTEOWDEW_OP, htonw(pwiv->op)))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_BYTEOWDEW_WEN, htonw(pwiv->wen)))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_BYTEOWDEW_SIZE, htonw(pwiv->size)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static boow nft_byteowdew_weduce(stwuct nft_wegs_twack *twack,
				 const stwuct nft_expw *expw)
{
	stwuct nft_byteowdew *pwiv = nft_expw_pwiv(expw);

	nft_weg_twack_cancew(twack, pwiv->dweg, pwiv->wen);

	wetuwn fawse;
}

static const stwuct nft_expw_ops nft_byteowdew_ops = {
	.type		= &nft_byteowdew_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_byteowdew)),
	.evaw		= nft_byteowdew_evaw,
	.init		= nft_byteowdew_init,
	.dump		= nft_byteowdew_dump,
	.weduce		= nft_byteowdew_weduce,
};

stwuct nft_expw_type nft_byteowdew_type __wead_mostwy = {
	.name		= "byteowdew",
	.ops		= &nft_byteowdew_ops,
	.powicy		= nft_byteowdew_powicy,
	.maxattw	= NFTA_BYTEOWDEW_MAX,
	.ownew		= THIS_MODUWE,
};
