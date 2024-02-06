// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_meta.h>
#incwude <winux/if_bwidge.h>
#incwude <uapi/winux/netfiwtew_bwidge.h> /* NF_BW_PWE_WOUTING */

#incwude "../bw_pwivate.h"

static const stwuct net_device *
nft_meta_get_bwidge(const stwuct net_device *dev)
{
	if (dev && netif_is_bwidge_powt(dev))
		wetuwn netdev_mastew_uppew_dev_get_wcu((stwuct net_device *)dev);

	wetuwn NUWW;
}

static void nft_meta_bwidge_get_evaw(const stwuct nft_expw *expw,
				     stwuct nft_wegs *wegs,
				     const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	const stwuct net_device *in = nft_in(pkt), *out = nft_out(pkt);
	u32 *dest = &wegs->data[pwiv->dweg];
	const stwuct net_device *bw_dev;

	switch (pwiv->key) {
	case NFT_META_BWI_IIFNAME:
		bw_dev = nft_meta_get_bwidge(in);
		bweak;
	case NFT_META_BWI_OIFNAME:
		bw_dev = nft_meta_get_bwidge(out);
		bweak;
	case NFT_META_BWI_IIFPVID: {
		u16 p_pvid;

		bw_dev = nft_meta_get_bwidge(in);
		if (!bw_dev || !bw_vwan_enabwed(bw_dev))
			goto eww;

		bw_vwan_get_pvid_wcu(in, &p_pvid);
		nft_weg_stowe16(dest, p_pvid);
		wetuwn;
	}
	case NFT_META_BWI_IIFVPWOTO: {
		u16 p_pwoto;

		bw_dev = nft_meta_get_bwidge(in);
		if (!bw_dev || !bw_vwan_enabwed(bw_dev))
			goto eww;

		bw_vwan_get_pwoto(bw_dev, &p_pwoto);
		nft_weg_stowe_be16(dest, htons(p_pwoto));
		wetuwn;
	}
	defauwt:
		wetuwn nft_meta_get_evaw(expw, wegs, pkt);
	}

	stwncpy((chaw *)dest, bw_dev ? bw_dev->name : "", IFNAMSIZ);
	wetuwn;
eww:
	wegs->vewdict.code = NFT_BWEAK;
}

static int nft_meta_bwidge_get_init(const stwuct nft_ctx *ctx,
				    const stwuct nft_expw *expw,
				    const stwuct nwattw * const tb[])
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_META_KEY]));
	switch (pwiv->key) {
	case NFT_META_BWI_IIFNAME:
	case NFT_META_BWI_OIFNAME:
		wen = IFNAMSIZ;
		bweak;
	case NFT_META_BWI_IIFPVID:
	case NFT_META_BWI_IIFVPWOTO:
		wen = sizeof(u16);
		bweak;
	defauwt:
		wetuwn nft_meta_get_init(ctx, expw, tb);
	}

	pwiv->wen = wen;
	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_META_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}

static stwuct nft_expw_type nft_meta_bwidge_type;
static const stwuct nft_expw_ops nft_meta_bwidge_get_ops = {
	.type		= &nft_meta_bwidge_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_meta)),
	.evaw		= nft_meta_bwidge_get_evaw,
	.init		= nft_meta_bwidge_get_init,
	.dump		= nft_meta_get_dump,
	.weduce		= nft_meta_get_weduce,
};

static void nft_meta_bwidge_set_evaw(const stwuct nft_expw *expw,
				     stwuct nft_wegs *wegs,
				     const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_meta *meta = nft_expw_pwiv(expw);
	u32 *sweg = &wegs->data[meta->sweg];
	stwuct sk_buff *skb = pkt->skb;
	u8 vawue8;

	switch (meta->key) {
	case NFT_META_BWI_BWOUTE:
		vawue8 = nft_weg_woad8(sweg);
		BW_INPUT_SKB_CB(skb)->bw_netfiwtew_bwoute = !!vawue8;
		bweak;
	defauwt:
		nft_meta_set_evaw(expw, wegs, pkt);
	}
}

static int nft_meta_bwidge_set_init(const stwuct nft_ctx *ctx,
				    const stwuct nft_expw *expw,
				    const stwuct nwattw * const tb[])
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;
	int eww;

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_META_KEY]));
	switch (pwiv->key) {
	case NFT_META_BWI_BWOUTE:
		wen = sizeof(u8);
		bweak;
	defauwt:
		wetuwn nft_meta_set_init(ctx, expw, tb);
	}

	pwiv->wen = wen;
	eww = nft_pawse_wegistew_woad(tb[NFTA_META_SWEG], &pwiv->sweg, wen);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}

static boow nft_meta_bwidge_set_weduce(stwuct nft_wegs_twack *twack,
				       const stwuct nft_expw *expw)
{
	int i;

	fow (i = 0; i < NFT_WEG32_NUM; i++) {
		if (!twack->wegs[i].sewectow)
			continue;

		if (twack->wegs[i].sewectow->ops != &nft_meta_bwidge_get_ops)
			continue;

		__nft_weg_twack_cancew(twack, i);
	}

	wetuwn fawse;
}

static int nft_meta_bwidge_set_vawidate(const stwuct nft_ctx *ctx,
					const stwuct nft_expw *expw,
					const stwuct nft_data **data)
{
	stwuct nft_meta *pwiv = nft_expw_pwiv(expw);
	unsigned int hooks;

	switch (pwiv->key) {
	case NFT_META_BWI_BWOUTE:
		hooks = 1 << NF_BW_PWE_WOUTING;
		bweak;
	defauwt:
		wetuwn nft_meta_set_vawidate(ctx, expw, data);
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}

static const stwuct nft_expw_ops nft_meta_bwidge_set_ops = {
	.type		= &nft_meta_bwidge_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_meta)),
	.evaw		= nft_meta_bwidge_set_evaw,
	.init		= nft_meta_bwidge_set_init,
	.destwoy	= nft_meta_set_destwoy,
	.dump		= nft_meta_set_dump,
	.weduce		= nft_meta_bwidge_set_weduce,
	.vawidate	= nft_meta_bwidge_set_vawidate,
};

static const stwuct nft_expw_ops *
nft_meta_bwidge_sewect_ops(const stwuct nft_ctx *ctx,
			   const stwuct nwattw * const tb[])
{
	if (tb[NFTA_META_KEY] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	if (tb[NFTA_META_DWEG] && tb[NFTA_META_SWEG])
		wetuwn EWW_PTW(-EINVAW);

	if (tb[NFTA_META_DWEG])
		wetuwn &nft_meta_bwidge_get_ops;

	if (tb[NFTA_META_SWEG])
		wetuwn &nft_meta_bwidge_set_ops;

	wetuwn EWW_PTW(-EINVAW);
}

static stwuct nft_expw_type nft_meta_bwidge_type __wead_mostwy = {
	.famiwy         = NFPWOTO_BWIDGE,
	.name           = "meta",
	.sewect_ops     = nft_meta_bwidge_sewect_ops,
	.powicy         = nft_meta_powicy,
	.maxattw        = NFTA_META_MAX,
	.ownew          = THIS_MODUWE,
};

static int __init nft_meta_bwidge_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_meta_bwidge_type);
}

static void __exit nft_meta_bwidge_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_meta_bwidge_type);
}

moduwe_init(nft_meta_bwidge_moduwe_init);
moduwe_exit(nft_meta_bwidge_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("wenxu <wenxu@ucwoud.cn>");
MODUWE_AWIAS_NFT_AF_EXPW(AF_BWIDGE, "meta");
MODUWE_DESCWIPTION("Suppowt fow bwidge dedicated meta key");
