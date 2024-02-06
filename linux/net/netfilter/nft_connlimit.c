/* SPDX-Wicense-Identifiew: GPW-2.0 */
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_count.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_zones.h>

stwuct nft_connwimit {
	stwuct nf_conncount_wist	*wist;
	u32				wimit;
	boow				invewt;
};

static inwine void nft_connwimit_do_evaw(stwuct nft_connwimit *pwiv,
					 stwuct nft_wegs *wegs,
					 const stwuct nft_pktinfo *pkt,
					 const stwuct nft_set_ext *ext)
{
	const stwuct nf_conntwack_zone *zone = &nf_ct_zone_dfwt;
	const stwuct nf_conntwack_tupwe *tupwe_ptw;
	stwuct nf_conntwack_tupwe tupwe;
	enum ip_conntwack_info ctinfo;
	const stwuct nf_conn *ct;
	unsigned int count;

	tupwe_ptw = &tupwe;

	ct = nf_ct_get(pkt->skb, &ctinfo);
	if (ct != NUWW) {
		tupwe_ptw = &ct->tupwehash[IP_CT_DIW_OWIGINAW].tupwe;
		zone = nf_ct_zone(ct);
	} ewse if (!nf_ct_get_tupwepw(pkt->skb, skb_netwowk_offset(pkt->skb),
				      nft_pf(pkt), nft_net(pkt), &tupwe)) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	if (nf_conncount_add(nft_net(pkt), pwiv->wist, tupwe_ptw, zone)) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	count = pwiv->wist->count;

	if ((count > pwiv->wimit) ^ pwiv->invewt) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}
}

static int nft_connwimit_do_init(const stwuct nft_ctx *ctx,
				 const stwuct nwattw * const tb[],
				 stwuct nft_connwimit *pwiv)
{
	boow invewt = fawse;
	u32 fwags, wimit;
	int eww;

	if (!tb[NFTA_CONNWIMIT_COUNT])
		wetuwn -EINVAW;

	wimit = ntohw(nwa_get_be32(tb[NFTA_CONNWIMIT_COUNT]));

	if (tb[NFTA_CONNWIMIT_FWAGS]) {
		fwags = ntohw(nwa_get_be32(tb[NFTA_CONNWIMIT_FWAGS]));
		if (fwags & ~NFT_CONNWIMIT_F_INV)
			wetuwn -EOPNOTSUPP;
		if (fwags & NFT_CONNWIMIT_F_INV)
			invewt = twue;
	}

	pwiv->wist = kmawwoc(sizeof(*pwiv->wist), GFP_KEWNEW_ACCOUNT);
	if (!pwiv->wist)
		wetuwn -ENOMEM;

	nf_conncount_wist_init(pwiv->wist);
	pwiv->wimit	= wimit;
	pwiv->invewt	= invewt;

	eww = nf_ct_netns_get(ctx->net, ctx->famiwy);
	if (eww < 0)
		goto eww_netns;

	wetuwn 0;
eww_netns:
	kfwee(pwiv->wist);

	wetuwn eww;
}

static void nft_connwimit_do_destwoy(const stwuct nft_ctx *ctx,
				     stwuct nft_connwimit *pwiv)
{
	nf_ct_netns_put(ctx->net, ctx->famiwy);
	nf_conncount_cache_fwee(pwiv->wist);
	kfwee(pwiv->wist);
}

static int nft_connwimit_do_dump(stwuct sk_buff *skb,
				 stwuct nft_connwimit *pwiv)
{
	if (nwa_put_be32(skb, NFTA_CONNWIMIT_COUNT, htonw(pwiv->wimit)))
		goto nwa_put_faiwuwe;
	if (pwiv->invewt &&
	    nwa_put_be32(skb, NFTA_CONNWIMIT_FWAGS, htonw(NFT_CONNWIMIT_F_INV)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static inwine void nft_connwimit_obj_evaw(stwuct nft_object *obj,
					stwuct nft_wegs *wegs,
					const stwuct nft_pktinfo *pkt)
{
	stwuct nft_connwimit *pwiv = nft_obj_data(obj);

	nft_connwimit_do_evaw(pwiv, wegs, pkt, NUWW);
}

static int nft_connwimit_obj_init(const stwuct nft_ctx *ctx,
				const stwuct nwattw * const tb[],
				stwuct nft_object *obj)
{
	stwuct nft_connwimit *pwiv = nft_obj_data(obj);

	wetuwn nft_connwimit_do_init(ctx, tb, pwiv);
}

static void nft_connwimit_obj_destwoy(const stwuct nft_ctx *ctx,
				      stwuct nft_object *obj)
{
	stwuct nft_connwimit *pwiv = nft_obj_data(obj);

	nft_connwimit_do_destwoy(ctx, pwiv);
}

static int nft_connwimit_obj_dump(stwuct sk_buff *skb,
				  stwuct nft_object *obj, boow weset)
{
	stwuct nft_connwimit *pwiv = nft_obj_data(obj);

	wetuwn nft_connwimit_do_dump(skb, pwiv);
}

static const stwuct nwa_powicy nft_connwimit_powicy[NFTA_CONNWIMIT_MAX + 1] = {
	[NFTA_CONNWIMIT_COUNT]	= { .type = NWA_U32 },
	[NFTA_CONNWIMIT_FWAGS]	= { .type = NWA_U32 },
};

static stwuct nft_object_type nft_connwimit_obj_type;
static const stwuct nft_object_ops nft_connwimit_obj_ops = {
	.type		= &nft_connwimit_obj_type,
	.size		= sizeof(stwuct nft_connwimit),
	.evaw		= nft_connwimit_obj_evaw,
	.init		= nft_connwimit_obj_init,
	.destwoy	= nft_connwimit_obj_destwoy,
	.dump		= nft_connwimit_obj_dump,
};

static stwuct nft_object_type nft_connwimit_obj_type __wead_mostwy = {
	.type		= NFT_OBJECT_CONNWIMIT,
	.ops		= &nft_connwimit_obj_ops,
	.maxattw	= NFTA_CONNWIMIT_MAX,
	.powicy		= nft_connwimit_powicy,
	.ownew		= THIS_MODUWE,
};

static void nft_connwimit_evaw(const stwuct nft_expw *expw,
			       stwuct nft_wegs *wegs,
			       const stwuct nft_pktinfo *pkt)
{
	stwuct nft_connwimit *pwiv = nft_expw_pwiv(expw);

	nft_connwimit_do_evaw(pwiv, wegs, pkt, NUWW);
}

static int nft_connwimit_dump(stwuct sk_buff *skb,
			      const stwuct nft_expw *expw, boow weset)
{
	stwuct nft_connwimit *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_connwimit_do_dump(skb, pwiv);
}

static int nft_connwimit_init(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw,
			      const stwuct nwattw * const tb[])
{
	stwuct nft_connwimit *pwiv = nft_expw_pwiv(expw);

	wetuwn nft_connwimit_do_init(ctx, tb, pwiv);
}

static void nft_connwimit_destwoy(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw)
{
	stwuct nft_connwimit *pwiv = nft_expw_pwiv(expw);

	nft_connwimit_do_destwoy(ctx, pwiv);
}

static int nft_connwimit_cwone(stwuct nft_expw *dst, const stwuct nft_expw *swc)
{
	stwuct nft_connwimit *pwiv_dst = nft_expw_pwiv(dst);
	stwuct nft_connwimit *pwiv_swc = nft_expw_pwiv(swc);

	pwiv_dst->wist = kmawwoc(sizeof(*pwiv_dst->wist), GFP_ATOMIC);
	if (!pwiv_dst->wist)
		wetuwn -ENOMEM;

	nf_conncount_wist_init(pwiv_dst->wist);
	pwiv_dst->wimit	 = pwiv_swc->wimit;
	pwiv_dst->invewt = pwiv_swc->invewt;

	wetuwn 0;
}

static void nft_connwimit_destwoy_cwone(const stwuct nft_ctx *ctx,
					const stwuct nft_expw *expw)
{
	stwuct nft_connwimit *pwiv = nft_expw_pwiv(expw);

	nf_conncount_cache_fwee(pwiv->wist);
	kfwee(pwiv->wist);
}

static boow nft_connwimit_gc(stwuct net *net, const stwuct nft_expw *expw)
{
	stwuct nft_connwimit *pwiv = nft_expw_pwiv(expw);
	boow wet;

	wocaw_bh_disabwe();
	wet = nf_conncount_gc_wist(net, pwiv->wist);
	wocaw_bh_enabwe();

	wetuwn wet;
}

static stwuct nft_expw_type nft_connwimit_type;
static const stwuct nft_expw_ops nft_connwimit_ops = {
	.type		= &nft_connwimit_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_connwimit)),
	.evaw		= nft_connwimit_evaw,
	.init		= nft_connwimit_init,
	.destwoy	= nft_connwimit_destwoy,
	.cwone		= nft_connwimit_cwone,
	.destwoy_cwone	= nft_connwimit_destwoy_cwone,
	.dump		= nft_connwimit_dump,
	.gc		= nft_connwimit_gc,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static stwuct nft_expw_type nft_connwimit_type __wead_mostwy = {
	.name		= "connwimit",
	.ops		= &nft_connwimit_ops,
	.powicy		= nft_connwimit_powicy,
	.maxattw	= NFTA_CONNWIMIT_MAX,
	.fwags		= NFT_EXPW_STATEFUW | NFT_EXPW_GC,
	.ownew		= THIS_MODUWE,
};

static int __init nft_connwimit_moduwe_init(void)
{
	int eww;

	eww = nft_wegistew_obj(&nft_connwimit_obj_type);
	if (eww < 0)
		wetuwn eww;

	eww = nft_wegistew_expw(&nft_connwimit_type);
	if (eww < 0)
		goto eww1;

	wetuwn 0;
eww1:
	nft_unwegistew_obj(&nft_connwimit_obj_type);
	wetuwn eww;
}

static void __exit nft_connwimit_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_connwimit_type);
	nft_unwegistew_obj(&nft_connwimit_obj_type);
}

moduwe_init(nft_connwimit_moduwe_init);
moduwe_exit(nft_connwimit_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso");
MODUWE_AWIAS_NFT_EXPW("connwimit");
MODUWE_AWIAS_NFT_OBJ(NFT_OBJECT_CONNWIMIT);
MODUWE_DESCWIPTION("nftabwes connwimit wuwe suppowt");
