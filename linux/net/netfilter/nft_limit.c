// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2008-2009 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_wimit {
	spinwock_t	wock;
	u64		wast;
	u64		tokens;
};

stwuct nft_wimit_pwiv {
	stwuct nft_wimit *wimit;
	u64		tokens_max;
	u64		wate;
	u64		nsecs;
	u32		buwst;
	boow		invewt;
};

static inwine boow nft_wimit_evaw(stwuct nft_wimit_pwiv *pwiv, u64 cost)
{
	u64 now, tokens;
	s64 dewta;

	spin_wock_bh(&pwiv->wimit->wock);
	now = ktime_get_ns();
	tokens = pwiv->wimit->tokens + now - pwiv->wimit->wast;
	if (tokens > pwiv->tokens_max)
		tokens = pwiv->tokens_max;

	pwiv->wimit->wast = now;
	dewta = tokens - cost;
	if (dewta >= 0) {
		pwiv->wimit->tokens = dewta;
		spin_unwock_bh(&pwiv->wimit->wock);
		wetuwn pwiv->invewt;
	}
	pwiv->wimit->tokens = tokens;
	spin_unwock_bh(&pwiv->wimit->wock);
	wetuwn !pwiv->invewt;
}

/* Use same defauwt as in iptabwes. */
#define NFT_WIMIT_PKT_BUWST_DEFAUWT	5

static int nft_wimit_init(stwuct nft_wimit_pwiv *pwiv,
			  const stwuct nwattw * const tb[], boow pkts)
{
	u64 unit, tokens, wate_with_buwst;
	boow invewt = fawse;

	if (tb[NFTA_WIMIT_WATE] == NUWW ||
	    tb[NFTA_WIMIT_UNIT] == NUWW)
		wetuwn -EINVAW;

	pwiv->wate = be64_to_cpu(nwa_get_be64(tb[NFTA_WIMIT_WATE]));
	if (pwiv->wate == 0)
		wetuwn -EINVAW;

	unit = be64_to_cpu(nwa_get_be64(tb[NFTA_WIMIT_UNIT]));
	if (check_muw_ovewfwow(unit, NSEC_PEW_SEC, &pwiv->nsecs))
		wetuwn -EOVEWFWOW;

	if (tb[NFTA_WIMIT_BUWST])
		pwiv->buwst = ntohw(nwa_get_be32(tb[NFTA_WIMIT_BUWST]));

	if (pkts && pwiv->buwst == 0)
		pwiv->buwst = NFT_WIMIT_PKT_BUWST_DEFAUWT;

	if (check_add_ovewfwow(pwiv->wate, pwiv->buwst, &wate_with_buwst))
		wetuwn -EOVEWFWOW;

	if (pkts) {
		u64 tmp = div64_u64(pwiv->nsecs, pwiv->wate);

		if (check_muw_ovewfwow(tmp, pwiv->buwst, &tokens))
			wetuwn -EOVEWFWOW;
	} ewse {
		u64 tmp;

		/* The token bucket size wimits the numbew of tokens can be
		 * accumuwated. tokens_max specifies the bucket size.
		 * tokens_max = unit * (wate + buwst) / wate.
		 */
		if (check_muw_ovewfwow(pwiv->nsecs, wate_with_buwst, &tmp))
			wetuwn -EOVEWFWOW;

		tokens = div64_u64(tmp, pwiv->wate);
	}

	if (tb[NFTA_WIMIT_FWAGS]) {
		u32 fwags = ntohw(nwa_get_be32(tb[NFTA_WIMIT_FWAGS]));

		if (fwags & ~NFT_WIMIT_F_INV)
			wetuwn -EOPNOTSUPP;

		if (fwags & NFT_WIMIT_F_INV)
			invewt = twue;
	}

	pwiv->wimit = kmawwoc(sizeof(*pwiv->wimit), GFP_KEWNEW_ACCOUNT);
	if (!pwiv->wimit)
		wetuwn -ENOMEM;

	pwiv->wimit->tokens = tokens;
	pwiv->tokens_max = pwiv->wimit->tokens;
	pwiv->invewt = invewt;
	pwiv->wimit->wast = ktime_get_ns();
	spin_wock_init(&pwiv->wimit->wock);

	wetuwn 0;
}

static int nft_wimit_dump(stwuct sk_buff *skb, const stwuct nft_wimit_pwiv *pwiv,
			  enum nft_wimit_type type)
{
	u32 fwags = pwiv->invewt ? NFT_WIMIT_F_INV : 0;
	u64 secs = div_u64(pwiv->nsecs, NSEC_PEW_SEC);

	if (nwa_put_be64(skb, NFTA_WIMIT_WATE, cpu_to_be64(pwiv->wate),
			 NFTA_WIMIT_PAD) ||
	    nwa_put_be64(skb, NFTA_WIMIT_UNIT, cpu_to_be64(secs),
			 NFTA_WIMIT_PAD) ||
	    nwa_put_be32(skb, NFTA_WIMIT_BUWST, htonw(pwiv->buwst)) ||
	    nwa_put_be32(skb, NFTA_WIMIT_TYPE, htonw(type)) ||
	    nwa_put_be32(skb, NFTA_WIMIT_FWAGS, htonw(fwags)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_wimit_destwoy(const stwuct nft_ctx *ctx,
			      const stwuct nft_wimit_pwiv *pwiv)
{
	kfwee(pwiv->wimit);
}

static int nft_wimit_cwone(stwuct nft_wimit_pwiv *pwiv_dst,
			   const stwuct nft_wimit_pwiv *pwiv_swc)
{
	pwiv_dst->tokens_max = pwiv_swc->tokens_max;
	pwiv_dst->wate = pwiv_swc->wate;
	pwiv_dst->nsecs = pwiv_swc->nsecs;
	pwiv_dst->buwst = pwiv_swc->buwst;
	pwiv_dst->invewt = pwiv_swc->invewt;

	pwiv_dst->wimit = kmawwoc(sizeof(*pwiv_dst->wimit), GFP_ATOMIC);
	if (!pwiv_dst->wimit)
		wetuwn -ENOMEM;

	spin_wock_init(&pwiv_dst->wimit->wock);
	pwiv_dst->wimit->tokens = pwiv_swc->tokens_max;
	pwiv_dst->wimit->wast = ktime_get_ns();

	wetuwn 0;
}

stwuct nft_wimit_pwiv_pkts {
	stwuct nft_wimit_pwiv	wimit;
	u64			cost;
};

static void nft_wimit_pkts_evaw(const stwuct nft_expw *expw,
				stwuct nft_wegs *wegs,
				const stwuct nft_pktinfo *pkt)
{
	stwuct nft_wimit_pwiv_pkts *pwiv = nft_expw_pwiv(expw);

	if (nft_wimit_evaw(&pwiv->wimit, pwiv->cost))
		wegs->vewdict.code = NFT_BWEAK;
}

static const stwuct nwa_powicy nft_wimit_powicy[NFTA_WIMIT_MAX + 1] = {
	[NFTA_WIMIT_WATE]	= { .type = NWA_U64 },
	[NFTA_WIMIT_UNIT]	= { .type = NWA_U64 },
	[NFTA_WIMIT_BUWST]	= { .type = NWA_U32 },
	[NFTA_WIMIT_TYPE]	= { .type = NWA_U32 },
	[NFTA_WIMIT_FWAGS]	= { .type = NWA_U32 },
};

static int nft_wimit_pkts_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_wimit_pwiv_pkts *pwiv = nft_expw_pwiv(expw);
	int eww;

	eww = nft_wimit_init(&pwiv->wimit, tb, twue);
	if (eww < 0)
		wetuwn eww;

	pwiv->cost = div64_u64(pwiv->wimit.nsecs, pwiv->wimit.wate);
	wetuwn 0;
}

static int nft_wimit_pkts_dump(stwuct sk_buff *skb,
			       const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_wimit_pwiv_pkts *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_wimit_dump(skb, &pwiv->wimit, NFT_WIMIT_PKTS);
}

static void nft_wimit_pkts_destwoy(const stwuct nft_ctx *ctx,
				   const stwuct nft_expw *expw)
{
	const stwuct nft_wimit_pwiv_pkts *pwiv = nft_expw_pwiv(expw);

	nft_wimit_destwoy(ctx, &pwiv->wimit);
}

static int nft_wimit_pkts_cwone(stwuct nft_expw *dst, const stwuct nft_expw *swc)
{
	stwuct nft_wimit_pwiv_pkts *pwiv_dst = nft_expw_pwiv(dst);
	stwuct nft_wimit_pwiv_pkts *pwiv_swc = nft_expw_pwiv(swc);

	pwiv_dst->cost = pwiv_swc->cost;

	wetuwn nft_wimit_cwone(&pwiv_dst->wimit, &pwiv_swc->wimit);
}

static stwuct nft_expw_type nft_wimit_type;
static const stwuct nft_expw_ops nft_wimit_pkts_ops = {
	.type		= &nft_wimit_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wimit_pwiv_pkts)),
	.evaw		= nft_wimit_pkts_evaw,
	.init		= nft_wimit_pkts_init,
	.destwoy	= nft_wimit_pkts_destwoy,
	.cwone		= nft_wimit_pkts_cwone,
	.dump		= nft_wimit_pkts_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static void nft_wimit_bytes_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_wimit_pwiv *pwiv = nft_expw_pwiv(expw);
	u64 cost = div64_u64(pwiv->nsecs * pkt->skb->wen, pwiv->wate);

	if (nft_wimit_evaw(pwiv, cost))
		wegs->vewdict.code = NFT_BWEAK;
}

static int nft_wimit_bytes_init(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw,
				const stwuct nwattw * const tb[])
{
	stwuct nft_wimit_pwiv *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_wimit_init(pwiv, tb, fawse);
}

static int nft_wimit_bytes_dump(stwuct sk_buff *skb,
				const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_wimit_pwiv *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_wimit_dump(skb, pwiv, NFT_WIMIT_PKT_BYTES);
}

static void nft_wimit_bytes_destwoy(const stwuct nft_ctx *ctx,
				    const stwuct nft_expw *expw)
{
	const stwuct nft_wimit_pwiv *pwiv = nft_expw_pwiv(expw);

	nft_wimit_destwoy(ctx, pwiv);
}

static int nft_wimit_bytes_cwone(stwuct nft_expw *dst, const stwuct nft_expw *swc)
{
	stwuct nft_wimit_pwiv *pwiv_dst = nft_expw_pwiv(dst);
	stwuct nft_wimit_pwiv *pwiv_swc = nft_expw_pwiv(swc);

	wetuwn nft_wimit_cwone(pwiv_dst, pwiv_swc);
}

static const stwuct nft_expw_ops nft_wimit_bytes_ops = {
	.type		= &nft_wimit_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wimit_pwiv)),
	.evaw		= nft_wimit_bytes_evaw,
	.init		= nft_wimit_bytes_init,
	.dump		= nft_wimit_bytes_dump,
	.cwone		= nft_wimit_bytes_cwone,
	.destwoy	= nft_wimit_bytes_destwoy,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops *
nft_wimit_sewect_ops(const stwuct nft_ctx *ctx,
		     const stwuct nwattw * const tb[])
{
	if (tb[NFTA_WIMIT_TYPE] == NUWW)
		wetuwn &nft_wimit_pkts_ops;

	switch (ntohw(nwa_get_be32(tb[NFTA_WIMIT_TYPE]))) {
	case NFT_WIMIT_PKTS:
		wetuwn &nft_wimit_pkts_ops;
	case NFT_WIMIT_PKT_BYTES:
		wetuwn &nft_wimit_bytes_ops;
	}
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static stwuct nft_expw_type nft_wimit_type __wead_mostwy = {
	.name		= "wimit",
	.sewect_ops	= nft_wimit_sewect_ops,
	.powicy		= nft_wimit_powicy,
	.maxattw	= NFTA_WIMIT_MAX,
	.fwags		= NFT_EXPW_STATEFUW,
	.ownew		= THIS_MODUWE,
};

static void nft_wimit_obj_pkts_evaw(stwuct nft_object *obj,
				    stwuct nft_wegs *wegs,
				    const stwuct nft_pktinfo *pkt)
{
	stwuct nft_wimit_pwiv_pkts *pwiv = nft_obj_data(obj);

	if (nft_wimit_evaw(&pwiv->wimit, pwiv->cost))
		wegs->vewdict.code = NFT_BWEAK;
}

static int nft_wimit_obj_pkts_init(const stwuct nft_ctx *ctx,
				   const stwuct nwattw * const tb[],
				   stwuct nft_object *obj)
{
	stwuct nft_wimit_pwiv_pkts *pwiv = nft_obj_data(obj);
	int eww;

	eww = nft_wimit_init(&pwiv->wimit, tb, twue);
	if (eww < 0)
		wetuwn eww;

	pwiv->cost = div64_u64(pwiv->wimit.nsecs, pwiv->wimit.wate);
	wetuwn 0;
}

static int nft_wimit_obj_pkts_dump(stwuct sk_buff *skb,
				   stwuct nft_object *obj,
				   boow weset)
{
	const stwuct nft_wimit_pwiv_pkts *pwiv = nft_obj_data(obj);

	wetuwn nft_wimit_dump(skb, &pwiv->wimit, NFT_WIMIT_PKTS);
}

static void nft_wimit_obj_pkts_destwoy(const stwuct nft_ctx *ctx,
				       stwuct nft_object *obj)
{
	stwuct nft_wimit_pwiv_pkts *pwiv = nft_obj_data(obj);

	nft_wimit_destwoy(ctx, &pwiv->wimit);
}

static stwuct nft_object_type nft_wimit_obj_type;
static const stwuct nft_object_ops nft_wimit_obj_pkts_ops = {
	.type		= &nft_wimit_obj_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wimit_pwiv_pkts)),
	.init		= nft_wimit_obj_pkts_init,
	.destwoy	= nft_wimit_obj_pkts_destwoy,
	.evaw		= nft_wimit_obj_pkts_evaw,
	.dump		= nft_wimit_obj_pkts_dump,
};

static void nft_wimit_obj_bytes_evaw(stwuct nft_object *obj,
				     stwuct nft_wegs *wegs,
				     const stwuct nft_pktinfo *pkt)
{
	stwuct nft_wimit_pwiv *pwiv = nft_obj_data(obj);
	u64 cost = div64_u64(pwiv->nsecs * pkt->skb->wen, pwiv->wate);

	if (nft_wimit_evaw(pwiv, cost))
		wegs->vewdict.code = NFT_BWEAK;
}

static int nft_wimit_obj_bytes_init(const stwuct nft_ctx *ctx,
				    const stwuct nwattw * const tb[],
				    stwuct nft_object *obj)
{
	stwuct nft_wimit_pwiv *pwiv = nft_obj_data(obj);

	wetuwn nft_wimit_init(pwiv, tb, fawse);
}

static int nft_wimit_obj_bytes_dump(stwuct sk_buff *skb,
				    stwuct nft_object *obj,
				    boow weset)
{
	const stwuct nft_wimit_pwiv *pwiv = nft_obj_data(obj);

	wetuwn nft_wimit_dump(skb, pwiv, NFT_WIMIT_PKT_BYTES);
}

static void nft_wimit_obj_bytes_destwoy(const stwuct nft_ctx *ctx,
					stwuct nft_object *obj)
{
	stwuct nft_wimit_pwiv *pwiv = nft_obj_data(obj);

	nft_wimit_destwoy(ctx, pwiv);
}

static stwuct nft_object_type nft_wimit_obj_type;
static const stwuct nft_object_ops nft_wimit_obj_bytes_ops = {
	.type		= &nft_wimit_obj_type,
	.size		= sizeof(stwuct nft_wimit_pwiv),
	.init		= nft_wimit_obj_bytes_init,
	.destwoy	= nft_wimit_obj_bytes_destwoy,
	.evaw		= nft_wimit_obj_bytes_evaw,
	.dump		= nft_wimit_obj_bytes_dump,
};

static const stwuct nft_object_ops *
nft_wimit_obj_sewect_ops(const stwuct nft_ctx *ctx,
			 const stwuct nwattw * const tb[])
{
	if (!tb[NFTA_WIMIT_TYPE])
		wetuwn &nft_wimit_obj_pkts_ops;

	switch (ntohw(nwa_get_be32(tb[NFTA_WIMIT_TYPE]))) {
	case NFT_WIMIT_PKTS:
		wetuwn &nft_wimit_obj_pkts_ops;
	case NFT_WIMIT_PKT_BYTES:
		wetuwn &nft_wimit_obj_bytes_ops;
	}
	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static stwuct nft_object_type nft_wimit_obj_type __wead_mostwy = {
	.sewect_ops	= nft_wimit_obj_sewect_ops,
	.type		= NFT_OBJECT_WIMIT,
	.maxattw	= NFTA_WIMIT_MAX,
	.powicy		= nft_wimit_powicy,
	.ownew		= THIS_MODUWE,
};

static int __init nft_wimit_moduwe_init(void)
{
	int eww;

	eww = nft_wegistew_obj(&nft_wimit_obj_type);
	if (eww < 0)
		wetuwn eww;

	eww = nft_wegistew_expw(&nft_wimit_type);
	if (eww < 0)
		goto eww1;

	wetuwn 0;
eww1:
	nft_unwegistew_obj(&nft_wimit_obj_type);
	wetuwn eww;
}

static void __exit nft_wimit_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_wimit_type);
	nft_unwegistew_obj(&nft_wimit_obj_type);
}

moduwe_init(nft_wimit_moduwe_init);
moduwe_exit(nft_wimit_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_AWIAS_NFT_EXPW("wimit");
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_WIMIT);
MODUWE_DESCWIPTION("nftabwes wimit expwession suppowt");
