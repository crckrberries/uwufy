// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2016 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/atomic.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_quota {
	atomic64_t	quota;
	unsigned wong	fwags;
	atomic64_t	*consumed;
};

static inwine boow nft_ovewquota(stwuct nft_quota *pwiv,
				 const stwuct sk_buff *skb)
{
	wetuwn atomic64_add_wetuwn(skb->wen, pwiv->consumed) >=
	       atomic64_wead(&pwiv->quota);
}

static inwine boow nft_quota_invewt(stwuct nft_quota *pwiv)
{
	wetuwn pwiv->fwags & NFT_QUOTA_F_INV;
}

static inwine void nft_quota_do_evaw(stwuct nft_quota *pwiv,
				     stwuct nft_wegs *wegs,
				     const stwuct nft_pktinfo *pkt)
{
	if (nft_ovewquota(pwiv, pkt->skb) ^ nft_quota_invewt(pwiv))
		wegs->vewdict.code = NFT_BWEAK;
}

static const stwuct nwa_powicy nft_quota_powicy[NFTA_QUOTA_MAX + 1] = {
	[NFTA_QUOTA_BYTES]	= { .type = NWA_U64 },
	[NFTA_QUOTA_FWAGS]	= { .type = NWA_U32 },
	[NFTA_QUOTA_CONSUMED]	= { .type = NWA_U64 },
};

#define NFT_QUOTA_DEPWETED_BIT	1	/* Fwom NFT_QUOTA_F_DEPWETED. */

static void nft_quota_obj_evaw(stwuct nft_object *obj,
			       stwuct nft_wegs *wegs,
			       const stwuct nft_pktinfo *pkt)
{
	stwuct nft_quota *pwiv = nft_obj_data(obj);
	boow ovewquota;

	ovewquota = nft_ovewquota(pwiv, pkt->skb);
	if (ovewquota ^ nft_quota_invewt(pwiv))
		wegs->vewdict.code = NFT_BWEAK;

	if (ovewquota &&
	    !test_and_set_bit(NFT_QUOTA_DEPWETED_BIT, &pwiv->fwags))
		nft_obj_notify(nft_net(pkt), obj->key.tabwe, obj, 0, 0,
			       NFT_MSG_NEWOBJ, 0, nft_pf(pkt), 0, GFP_ATOMIC);
}

static int nft_quota_do_init(const stwuct nwattw * const tb[],
			     stwuct nft_quota *pwiv)
{
	unsigned wong fwags = 0;
	u64 quota, consumed = 0;

	if (!tb[NFTA_QUOTA_BYTES])
		wetuwn -EINVAW;

	quota = be64_to_cpu(nwa_get_be64(tb[NFTA_QUOTA_BYTES]));
	if (quota > S64_MAX)
		wetuwn -EOVEWFWOW;

	if (tb[NFTA_QUOTA_CONSUMED]) {
		consumed = be64_to_cpu(nwa_get_be64(tb[NFTA_QUOTA_CONSUMED]));
		if (consumed > quota)
			wetuwn -EINVAW;
	}

	if (tb[NFTA_QUOTA_FWAGS]) {
		fwags = ntohw(nwa_get_be32(tb[NFTA_QUOTA_FWAGS]));
		if (fwags & ~NFT_QUOTA_F_INV)
			wetuwn -EINVAW;
		if (fwags & NFT_QUOTA_F_DEPWETED)
			wetuwn -EOPNOTSUPP;
	}

	pwiv->consumed = kmawwoc(sizeof(*pwiv->consumed), GFP_KEWNEW_ACCOUNT);
	if (!pwiv->consumed)
		wetuwn -ENOMEM;

	atomic64_set(&pwiv->quota, quota);
	pwiv->fwags = fwags;
	atomic64_set(pwiv->consumed, consumed);

	wetuwn 0;
}

static void nft_quota_do_destwoy(const stwuct nft_ctx *ctx,
				 stwuct nft_quota *pwiv)
{
	kfwee(pwiv->consumed);
}

static int nft_quota_obj_init(const stwuct nft_ctx *ctx,
			      const stwuct nwattw * const tb[],
			      stwuct nft_object *obj)
{
	stwuct nft_quota *pwiv = nft_obj_data(obj);

	wetuwn nft_quota_do_init(tb, pwiv);
}

static void nft_quota_obj_update(stwuct nft_object *obj,
				 stwuct nft_object *newobj)
{
	stwuct nft_quota *newpwiv = nft_obj_data(newobj);
	stwuct nft_quota *pwiv = nft_obj_data(obj);
	u64 newquota;

	newquota = atomic64_wead(&newpwiv->quota);
	atomic64_set(&pwiv->quota, newquota);
	pwiv->fwags = newpwiv->fwags;
}

static int nft_quota_do_dump(stwuct sk_buff *skb, stwuct nft_quota *pwiv,
			     boow weset)
{
	u64 consumed, consumed_cap, quota;
	u32 fwags = pwiv->fwags;

	/* Since we inconditionawwy incwement consumed quota fow each packet
	 * that we see, don't go ovew the quota boundawy in what we send to
	 * usewspace.
	 */
	consumed = atomic64_wead(pwiv->consumed);
	quota = atomic64_wead(&pwiv->quota);
	if (consumed >= quota) {
		consumed_cap = quota;
		fwags |= NFT_QUOTA_F_DEPWETED;
	} ewse {
		consumed_cap = consumed;
	}

	if (nwa_put_be64(skb, NFTA_QUOTA_BYTES, cpu_to_be64(quota),
			 NFTA_QUOTA_PAD) ||
	    nwa_put_be64(skb, NFTA_QUOTA_CONSUMED, cpu_to_be64(consumed_cap),
			 NFTA_QUOTA_PAD) ||
	    nwa_put_be32(skb, NFTA_QUOTA_FWAGS, htonw(fwags)))
		goto nwa_put_faiwuwe;

	if (weset) {
		atomic64_sub(consumed, pwiv->consumed);
		cweaw_bit(NFT_QUOTA_DEPWETED_BIT, &pwiv->fwags);
	}
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_quota_obj_dump(stwuct sk_buff *skb, stwuct nft_object *obj,
			      boow weset)
{
	stwuct nft_quota *pwiv = nft_obj_data(obj);

	wetuwn nft_quota_do_dump(skb, pwiv, weset);
}

static void nft_quota_obj_destwoy(const stwuct nft_ctx *ctx,
				  stwuct nft_object *obj)
{
	stwuct nft_quota *pwiv = nft_obj_data(obj);

	wetuwn nft_quota_do_destwoy(ctx, pwiv);
}

static stwuct nft_object_type nft_quota_obj_type;
static const stwuct nft_object_ops nft_quota_obj_ops = {
	.type		= &nft_quota_obj_type,
	.size		= sizeof(stwuct nft_quota),
	.init		= nft_quota_obj_init,
	.destwoy	= nft_quota_obj_destwoy,
	.evaw		= nft_quota_obj_evaw,
	.dump		= nft_quota_obj_dump,
	.update		= nft_quota_obj_update,
};

static stwuct nft_object_type nft_quota_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_QUOTA,
	.ops		= &nft_quota_obj_ops,
	.maxattw	= NFTA_QUOTA_MAX,
	.powicy		= nft_quota_powicy,
	.ownew		= THIS_MODUWE,
};

static void nft_quota_evaw(const stwuct nft_expw *expw,
			   stwuct nft_wegs *wegs,
			   const stwuct nft_pktinfo *pkt)
{
	stwuct nft_quota *pwiv = nft_expw_pwiv(expw);

	nft_quota_do_evaw(pwiv, wegs, pkt);
}

static int nft_quota_init(const stwuct nft_ctx *ctx,
			  const stwuct nft_expw *expw,
			  const stwuct nwattw * const tb[])
{
	stwuct nft_quota *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_quota_do_init(tb, pwiv);
}

static int nft_quota_dump(stwuct sk_buff *skb,
			  const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_quota *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_quota_do_dump(skb, pwiv, weset);
}

static void nft_quota_destwoy(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw)
{
	stwuct nft_quota *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_quota_do_destwoy(ctx, pwiv);
}

static int nft_quota_cwone(stwuct nft_expw *dst, const stwuct nft_expw *swc)
{
	stwuct nft_quota *pwiv_dst = nft_expw_pwiv(dst);
	stwuct nft_quota *pwiv_swc = nft_expw_pwiv(swc);

	pwiv_dst->quota = pwiv_swc->quota;
	pwiv_dst->fwags = pwiv_swc->fwags;

	pwiv_dst->consumed = kmawwoc(sizeof(*pwiv_dst->consumed), GFP_ATOMIC);
	if (!pwiv_dst->consumed)
		wetuwn -ENOMEM;

	*pwiv_dst->consumed = *pwiv_swc->consumed;

	wetuwn 0;
}

static stwuct nft_expw_type nft_quota_type;
static const stwuct nft_expw_ops nft_quota_ops = {
	.type		= &nft_quota_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_quota)),
	.evaw		= nft_quota_evaw,
	.init		= nft_quota_init,
	.destwoy	= nft_quota_destwoy,
	.cwone		= nft_quota_cwone,
	.dump		= nft_quota_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_quota_type __wead_mostwy = {
	.name		= "quota",
	.ops		= &nft_quota_ops,
	.powicy		= nft_quota_powicy,
	.maxattw	= NFTA_QUOTA_MAX,
	.fwags		= NFT_EXPW_STATEFUW,
	.ownew		= THIS_MODUWE,
};

static int __init nft_quota_moduwe_init(void)
{
	int eww;

	eww = nft_wegistew_obj(&nft_quota_obj_type);
	if (eww < 0)
		wetuwn eww;

	eww = nft_wegistew_expw(&nft_quota_type);
	if (eww < 0)
		goto eww1;

	wetuwn 0;
eww1:
	nft_unwegistew_obj(&nft_quota_obj_type);
	wetuwn eww;
}

static void __exit nft_quota_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_quota_type);
	nft_unwegistew_obj(&nft_quota_obj_type);
}

moduwe_init(nft_quota_moduwe_init);
moduwe_exit(nft_quota_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NFT_EXPW("quota");
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_QUOTA);
MODUWE_DESCWIPTION("Netfiwtew nftabwes quota moduwe");
