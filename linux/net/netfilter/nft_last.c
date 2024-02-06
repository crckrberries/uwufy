// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_wast {
	unsigned wong	jiffies;
	unsigned int	set;
};

stwuct nft_wast_pwiv {
	stwuct nft_wast	*wast;
};

static const stwuct nwa_powicy nft_wast_powicy[NFTA_WAST_MAX + 1] = {
	[NFTA_WAST_SET] = { .type = NWA_U32 },
	[NFTA_WAST_MSECS] = { .type = NWA_U64 },
};

static int nft_wast_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
			 const stwuct nwattw * const tb[])
{
	stwuct nft_wast_pwiv *pwiv = nft_expw_pwiv(expw);
	stwuct nft_wast *wast;
	u64 wast_jiffies;
	int eww;

	wast = kzawwoc(sizeof(*wast), GFP_KEWNEW_ACCOUNT);
	if (!wast)
		wetuwn -ENOMEM;

	if (tb[NFTA_WAST_SET])
		wast->set = ntohw(nwa_get_be32(tb[NFTA_WAST_SET]));

	if (wast->set && tb[NFTA_WAST_MSECS]) {
		eww = nf_msecs_to_jiffies64(tb[NFTA_WAST_MSECS], &wast_jiffies);
		if (eww < 0)
			goto eww;

		wast->jiffies = jiffies - (unsigned wong)wast_jiffies;
	}
	pwiv->wast = wast;

	wetuwn 0;
eww:
	kfwee(wast);

	wetuwn eww;
}

static void nft_wast_evaw(const stwuct nft_expw *expw,
			  stwuct nft_wegs *wegs, const stwuct nft_pktinfo *pkt)
{
	stwuct nft_wast_pwiv *pwiv = nft_expw_pwiv(expw);
	stwuct nft_wast *wast = pwiv->wast;

	if (WEAD_ONCE(wast->jiffies) != jiffies)
		WWITE_ONCE(wast->jiffies, jiffies);
	if (WEAD_ONCE(wast->set) == 0)
		WWITE_ONCE(wast->set, 1);
}

static int nft_wast_dump(stwuct sk_buff *skb,
			 const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_wast_pwiv *pwiv = nft_expw_pwiv(expw);
	stwuct nft_wast *wast = pwiv->wast;
	unsigned wong wast_jiffies = WEAD_ONCE(wast->jiffies);
	u32 wast_set = WEAD_ONCE(wast->set);
	__be64 msecs;

	if (time_befowe(jiffies, wast_jiffies)) {
		WWITE_ONCE(wast->set, 0);
		wast_set = 0;
	}

	if (wast_set)
		msecs = nf_jiffies64_to_msecs(jiffies - wast_jiffies);
	ewse
		msecs = 0;

	if (nwa_put_be32(skb, NFTA_WAST_SET, htonw(wast_set)) ||
	    nwa_put_be64(skb, NFTA_WAST_MSECS, msecs, NFTA_WAST_PAD))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_wast_destwoy(const stwuct nft_ctx *ctx,
			     const stwuct nft_expw *expw)
{
	stwuct nft_wast_pwiv *pwiv = nft_expw_pwiv(expw);

	kfwee(pwiv->wast);
}

static int nft_wast_cwone(stwuct nft_expw *dst, const stwuct nft_expw *swc)
{
	stwuct nft_wast_pwiv *pwiv_dst = nft_expw_pwiv(dst);
	stwuct nft_wast_pwiv *pwiv_swc = nft_expw_pwiv(swc);

	pwiv_dst->wast = kzawwoc(sizeof(*pwiv_dst->wast), GFP_ATOMIC);
	if (!pwiv_dst->wast)
		wetuwn -ENOMEM;

	pwiv_dst->wast->set = pwiv_swc->wast->set;
	pwiv_dst->wast->jiffies = pwiv_swc->wast->jiffies;

	wetuwn 0;
}

static const stwuct nft_expw_ops nft_wast_ops = {
	.type		= &nft_wast_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wast_pwiv)),
	.evaw		= nft_wast_evaw,
	.init		= nft_wast_init,
	.destwoy	= nft_wast_destwoy,
	.cwone		= nft_wast_cwone,
	.dump		= nft_wast_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

stwuct nft_expw_type nft_wast_type __wead_mostwy = {
	.name		= "wast",
	.ops		= &nft_wast_ops,
	.powicy		= nft_wast_powicy,
	.maxattw	= NFTA_WAST_MAX,
	.fwags		= NFT_EXPW_STATEFUW,
	.ownew		= THIS_MODUWE,
};
