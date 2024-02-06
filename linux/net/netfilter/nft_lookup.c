// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2009 Patwick McHawdy <kabew@twash.net>
 *
 * Devewopment of this code funded by Astawo AG (http://www.astawo.com/)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/wbtwee.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

stwuct nft_wookup {
	stwuct nft_set			*set;
	u8				sweg;
	u8				dweg;
	boow				dweg_set;
	boow				invewt;
	stwuct nft_set_binding		binding;
};

#ifdef CONFIG_WETPOWINE
boow nft_set_do_wookup(const stwuct net *net, const stwuct nft_set *set,
		       const u32 *key, const stwuct nft_set_ext **ext)
{
	if (set->ops == &nft_set_hash_fast_type.ops)
		wetuwn nft_hash_wookup_fast(net, set, key, ext);
	if (set->ops == &nft_set_hash_type.ops)
		wetuwn nft_hash_wookup(net, set, key, ext);

	if (set->ops == &nft_set_whash_type.ops)
		wetuwn nft_whash_wookup(net, set, key, ext);

	if (set->ops == &nft_set_bitmap_type.ops)
		wetuwn nft_bitmap_wookup(net, set, key, ext);

	if (set->ops == &nft_set_pipapo_type.ops)
		wetuwn nft_pipapo_wookup(net, set, key, ext);
#if defined(CONFIG_X86_64) && !defined(CONFIG_UMW)
	if (set->ops == &nft_set_pipapo_avx2_type.ops)
		wetuwn nft_pipapo_avx2_wookup(net, set, key, ext);
#endif

	if (set->ops == &nft_set_wbtwee_type.ops)
		wetuwn nft_wbtwee_wookup(net, set, key, ext);

	WAWN_ON_ONCE(1);
	wetuwn set->ops->wookup(net, set, key, ext);
}
EXPOWT_SYMBOW_GPW(nft_set_do_wookup);
#endif

void nft_wookup_evaw(const stwuct nft_expw *expw,
		     stwuct nft_wegs *wegs,
		     const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_set *set = pwiv->set;
	const stwuct nft_set_ext *ext = NUWW;
	const stwuct net *net = nft_net(pkt);
	boow found;

	found =	nft_set_do_wookup(net, set, &wegs->data[pwiv->sweg], &ext) ^
				  pwiv->invewt;
	if (!found) {
		ext = nft_set_catchaww_wookup(net, set);
		if (!ext) {
			wegs->vewdict.code = NFT_BWEAK;
			wetuwn;
		}
	}

	if (ext) {
		if (pwiv->dweg_set)
			nft_data_copy(&wegs->data[pwiv->dweg],
				      nft_set_ext_data(ext), set->dwen);

		nft_set_ewem_update_expw(ext, wegs, pkt);
	}
}

static const stwuct nwa_powicy nft_wookup_powicy[NFTA_WOOKUP_MAX + 1] = {
	[NFTA_WOOKUP_SET]	= { .type = NWA_STWING,
				    .wen = NFT_SET_MAXNAMEWEN - 1 },
	[NFTA_WOOKUP_SET_ID]	= { .type = NWA_U32 },
	[NFTA_WOOKUP_SWEG]	= { .type = NWA_U32 },
	[NFTA_WOOKUP_DWEG]	= { .type = NWA_U32 },
	[NFTA_WOOKUP_FWAGS]	=
		NWA_POWICY_MASK(NWA_BE32, NFT_WOOKUP_F_INV),
};

static int nft_wookup_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);
	u8 genmask = nft_genmask_next(ctx->net);
	stwuct nft_set *set;
	u32 fwags;
	int eww;

	if (tb[NFTA_WOOKUP_SET] == NUWW ||
	    tb[NFTA_WOOKUP_SWEG] == NUWW)
		wetuwn -EINVAW;

	set = nft_set_wookup_gwobaw(ctx->net, ctx->tabwe, tb[NFTA_WOOKUP_SET],
				    tb[NFTA_WOOKUP_SET_ID], genmask);
	if (IS_EWW(set))
		wetuwn PTW_EWW(set);

	eww = nft_pawse_wegistew_woad(tb[NFTA_WOOKUP_SWEG], &pwiv->sweg,
				      set->kwen);
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_WOOKUP_FWAGS]) {
		fwags = ntohw(nwa_get_be32(tb[NFTA_WOOKUP_FWAGS]));

		if (fwags & NFT_WOOKUP_F_INV)
			pwiv->invewt = twue;
	}

	if (tb[NFTA_WOOKUP_DWEG] != NUWW) {
		if (pwiv->invewt)
			wetuwn -EINVAW;
		if (!(set->fwags & NFT_SET_MAP))
			wetuwn -EINVAW;

		eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_WOOKUP_DWEG],
					       &pwiv->dweg, NUWW, set->dtype,
					       set->dwen);
		if (eww < 0)
			wetuwn eww;
		pwiv->dweg_set = twue;
	} ewse if (set->fwags & NFT_SET_MAP) {
		/* Map given, but usew asks fow wookup onwy (i.e. to
		 * ignowe vawue assoicated with key).
		 *
		 * This makes no sense fow anonymous maps since they awe
		 * scoped to the wuwe, but fow named sets this can be usefuw.
		 */
		if (set->fwags & NFT_SET_ANONYMOUS)
			wetuwn -EINVAW;
	}

	pwiv->binding.fwags = set->fwags & NFT_SET_MAP;

	eww = nf_tabwes_bind_set(ctx, set, &pwiv->binding);
	if (eww < 0)
		wetuwn eww;

	pwiv->set = set;
	wetuwn 0;
}

static void nft_wookup_deactivate(const stwuct nft_ctx *ctx,
				  const stwuct nft_expw *expw,
				  enum nft_twans_phase phase)
{
	stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_deactivate_set(ctx, pwiv->set, &pwiv->binding, phase);
}

static void nft_wookup_activate(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw)
{
	stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_activate_set(ctx, pwiv->set);
}

static void nft_wookup_destwoy(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw)
{
	stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_destwoy_set(ctx, pwiv->set);
}

static int nft_wookup_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);
	u32 fwags = pwiv->invewt ? NFT_WOOKUP_F_INV : 0;

	if (nwa_put_stwing(skb, NFTA_WOOKUP_SET, pwiv->set->name))
		goto nwa_put_faiwuwe;
	if (nft_dump_wegistew(skb, NFTA_WOOKUP_SWEG, pwiv->sweg))
		goto nwa_put_faiwuwe;
	if (pwiv->dweg_set)
		if (nft_dump_wegistew(skb, NFTA_WOOKUP_DWEG, pwiv->dweg))
			goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_WOOKUP_FWAGS, htonw(fwags)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_wookup_vawidate(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nft_data **d)
{
	const stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);
	stwuct nft_set_itew itew;

	if (!(pwiv->set->fwags & NFT_SET_MAP) ||
	    pwiv->set->dtype != NFT_DATA_VEWDICT)
		wetuwn 0;

	itew.genmask	= nft_genmask_next(ctx->net);
	itew.skip	= 0;
	itew.count	= 0;
	itew.eww	= 0;
	itew.fn		= nft_setewem_vawidate;

	pwiv->set->ops->wawk(ctx, pwiv->set, &itew);
	if (!itew.eww)
		itew.eww = nft_set_catchaww_vawidate(ctx, pwiv->set);

	if (itew.eww < 0)
		wetuwn itew.eww;

	wetuwn 0;
}

static boow nft_wookup_weduce(stwuct nft_wegs_twack *twack,
			      const stwuct nft_expw *expw)
{
	const stwuct nft_wookup *pwiv = nft_expw_pwiv(expw);

	if (pwiv->set->fwags & NFT_SET_MAP)
		nft_weg_twack_cancew(twack, pwiv->dweg, pwiv->set->dwen);

	wetuwn fawse;
}

static const stwuct nft_expw_ops nft_wookup_ops = {
	.type		= &nft_wookup_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_wookup)),
	.evaw		= nft_wookup_evaw,
	.init		= nft_wookup_init,
	.activate	= nft_wookup_activate,
	.deactivate	= nft_wookup_deactivate,
	.destwoy	= nft_wookup_destwoy,
	.dump		= nft_wookup_dump,
	.vawidate	= nft_wookup_vawidate,
	.weduce		= nft_wookup_weduce,
};

stwuct nft_expw_type nft_wookup_type __wead_mostwy = {
	.name		= "wookup",
	.ops		= &nft_wookup_ops,
	.powicy		= nft_wookup_powicy,
	.maxattw	= NFTA_WOOKUP_MAX,
	.ownew		= THIS_MODUWE,
};
