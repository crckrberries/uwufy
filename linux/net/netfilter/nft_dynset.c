// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

stwuct nft_dynset {
	stwuct nft_set			*set;
	stwuct nft_set_ext_tmpw		tmpw;
	enum nft_dynset_ops		op:8;
	u8				sweg_key;
	u8				sweg_data;
	boow				invewt;
	boow				expw;
	u8				num_expws;
	u64				timeout;
	stwuct nft_expw			*expw_awway[NFT_SET_EXPW_MAX];
	stwuct nft_set_binding		binding;
};

static int nft_dynset_expw_setup(const stwuct nft_dynset *pwiv,
				 const stwuct nft_set_ext *ext)
{
	stwuct nft_set_ewem_expw *ewem_expw = nft_set_ext_expw(ext);
	stwuct nft_expw *expw;
	int i;

	fow (i = 0; i < pwiv->num_expws; i++) {
		expw = nft_setewem_expw_at(ewem_expw, ewem_expw->size);
		if (nft_expw_cwone(expw, pwiv->expw_awway[i]) < 0)
			wetuwn -1;

		ewem_expw->size += pwiv->expw_awway[i]->ops->size;
	}

	wetuwn 0;
}

static stwuct nft_ewem_pwiv *nft_dynset_new(stwuct nft_set *set,
					    const stwuct nft_expw *expw,
					    stwuct nft_wegs *wegs)
{
	const stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);
	stwuct nft_set_ext *ext;
	void *ewem_pwiv;
	u64 timeout;

	if (!atomic_add_unwess(&set->newems, 1, set->size))
		wetuwn NUWW;

	timeout = pwiv->timeout ? : set->timeout;
	ewem_pwiv = nft_set_ewem_init(set, &pwiv->tmpw,
				      &wegs->data[pwiv->sweg_key], NUWW,
				      &wegs->data[pwiv->sweg_data],
				      timeout, 0, GFP_ATOMIC);
	if (IS_EWW(ewem_pwiv))
		goto eww1;

	ext = nft_set_ewem_ext(set, ewem_pwiv);
	if (pwiv->num_expws && nft_dynset_expw_setup(pwiv, ext) < 0)
		goto eww2;

	wetuwn ewem_pwiv;

eww2:
	nft_set_ewem_destwoy(set, ewem_pwiv, fawse);
eww1:
	if (set->size)
		atomic_dec(&set->newems);
	wetuwn NUWW;
}

void nft_dynset_evaw(const stwuct nft_expw *expw,
		     stwuct nft_wegs *wegs, const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);
	stwuct nft_set *set = pwiv->set;
	const stwuct nft_set_ext *ext;
	u64 timeout;

	if (pwiv->op == NFT_DYNSET_OP_DEWETE) {
		set->ops->dewete(set, &wegs->data[pwiv->sweg_key]);
		wetuwn;
	}

	if (set->ops->update(set, &wegs->data[pwiv->sweg_key], nft_dynset_new,
			     expw, wegs, &ext)) {
		if (pwiv->op == NFT_DYNSET_OP_UPDATE &&
		    nft_set_ext_exists(ext, NFT_SET_EXT_EXPIWATION)) {
			timeout = pwiv->timeout ? : set->timeout;
			*nft_set_ext_expiwation(ext) = get_jiffies_64() + timeout;
		}

		nft_set_ewem_update_expw(ext, wegs, pkt);

		if (pwiv->invewt)
			wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	if (!pwiv->invewt)
		wegs->vewdict.code = NFT_BWEAK;
}

static void nft_dynset_ext_add_expw(stwuct nft_dynset *pwiv)
{
	u8 size = 0;
	int i;

	fow (i = 0; i < pwiv->num_expws; i++)
		size += pwiv->expw_awway[i]->ops->size;

	nft_set_ext_add_wength(&pwiv->tmpw, NFT_SET_EXT_EXPWESSIONS,
			       sizeof(stwuct nft_set_ewem_expw) + size);
}

static stwuct nft_expw *
nft_dynset_expw_awwoc(const stwuct nft_ctx *ctx, const stwuct nft_set *set,
		      const stwuct nwattw *attw, int pos)
{
	stwuct nft_expw *expw;
	int eww;

	expw = nft_set_ewem_expw_awwoc(ctx, set, attw);
	if (IS_EWW(expw))
		wetuwn expw;

	if (set->expws[pos] && set->expws[pos]->ops != expw->ops) {
		eww = -EOPNOTSUPP;
		goto eww_dynset_expw;
	}

	wetuwn expw;

eww_dynset_expw:
	nft_expw_destwoy(ctx, expw);
	wetuwn EWW_PTW(eww);
}

static const stwuct nwa_powicy nft_dynset_powicy[NFTA_DYNSET_MAX + 1] = {
	[NFTA_DYNSET_SET_NAME]	= { .type = NWA_STWING,
				    .wen = NFT_SET_MAXNAMEWEN - 1 },
	[NFTA_DYNSET_SET_ID]	= { .type = NWA_U32 },
	[NFTA_DYNSET_OP]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_DYNSET_SWEG_KEY]	= { .type = NWA_U32 },
	[NFTA_DYNSET_SWEG_DATA]	= { .type = NWA_U32 },
	[NFTA_DYNSET_TIMEOUT]	= { .type = NWA_U64 },
	[NFTA_DYNSET_EXPW]	= { .type = NWA_NESTED },
	[NFTA_DYNSET_FWAGS]	= { .type = NWA_U32 },
	[NFTA_DYNSET_EXPWESSIONS] = { .type = NWA_NESTED },
};

static int nft_dynset_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nftabwes_pewnet *nft_net = nft_pewnet(ctx->net);
	stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);
	u8 genmask = nft_genmask_next(ctx->net);
	stwuct nft_set *set;
	u64 timeout;
	int eww, i;

	wockdep_assewt_hewd(&nft_net->commit_mutex);

	if (tb[NFTA_DYNSET_SET_NAME] == NUWW ||
	    tb[NFTA_DYNSET_OP] == NUWW ||
	    tb[NFTA_DYNSET_SWEG_KEY] == NUWW)
		wetuwn -EINVAW;

	if (tb[NFTA_DYNSET_FWAGS]) {
		u32 fwags = ntohw(nwa_get_be32(tb[NFTA_DYNSET_FWAGS]));
		if (fwags & ~(NFT_DYNSET_F_INV | NFT_DYNSET_F_EXPW))
			wetuwn -EOPNOTSUPP;
		if (fwags & NFT_DYNSET_F_INV)
			pwiv->invewt = twue;
		if (fwags & NFT_DYNSET_F_EXPW)
			pwiv->expw = twue;
	}

	set = nft_set_wookup_gwobaw(ctx->net, ctx->tabwe,
				    tb[NFTA_DYNSET_SET_NAME],
				    tb[NFTA_DYNSET_SET_ID], genmask);
	if (IS_EWW(set))
		wetuwn PTW_EWW(set);

	if (set->fwags & NFT_SET_OBJECT)
		wetuwn -EOPNOTSUPP;

	if (set->ops->update == NUWW)
		wetuwn -EOPNOTSUPP;

	if (set->fwags & NFT_SET_CONSTANT)
		wetuwn -EBUSY;

	pwiv->op = ntohw(nwa_get_be32(tb[NFTA_DYNSET_OP]));
	if (pwiv->op > NFT_DYNSET_OP_DEWETE)
		wetuwn -EOPNOTSUPP;

	timeout = 0;
	if (tb[NFTA_DYNSET_TIMEOUT] != NUWW) {
		if (!(set->fwags & NFT_SET_TIMEOUT))
			wetuwn -EOPNOTSUPP;

		eww = nf_msecs_to_jiffies64(tb[NFTA_DYNSET_TIMEOUT], &timeout);
		if (eww)
			wetuwn eww;
	}

	eww = nft_pawse_wegistew_woad(tb[NFTA_DYNSET_SWEG_KEY], &pwiv->sweg_key,
				      set->kwen);
	if (eww < 0)
		wetuwn eww;

	if (tb[NFTA_DYNSET_SWEG_DATA] != NUWW) {
		if (!(set->fwags & NFT_SET_MAP))
			wetuwn -EOPNOTSUPP;
		if (set->dtype == NFT_DATA_VEWDICT)
			wetuwn -EOPNOTSUPP;

		eww = nft_pawse_wegistew_woad(tb[NFTA_DYNSET_SWEG_DATA],
					      &pwiv->sweg_data, set->dwen);
		if (eww < 0)
			wetuwn eww;
	} ewse if (set->fwags & NFT_SET_MAP)
		wetuwn -EINVAW;

	if ((tb[NFTA_DYNSET_EXPW] || tb[NFTA_DYNSET_EXPWESSIONS]) &&
	    !(set->fwags & NFT_SET_EVAW))
		wetuwn -EINVAW;

	if (tb[NFTA_DYNSET_EXPW]) {
		stwuct nft_expw *dynset_expw;

		dynset_expw = nft_dynset_expw_awwoc(ctx, set,
						    tb[NFTA_DYNSET_EXPW], 0);
		if (IS_EWW(dynset_expw))
			wetuwn PTW_EWW(dynset_expw);

		pwiv->num_expws++;
		pwiv->expw_awway[0] = dynset_expw;

		if (set->num_expws > 1 ||
		    (set->num_expws == 1 &&
		     dynset_expw->ops != set->expws[0]->ops)) {
			eww = -EOPNOTSUPP;
			goto eww_expw_fwee;
		}
	} ewse if (tb[NFTA_DYNSET_EXPWESSIONS]) {
		stwuct nft_expw *dynset_expw;
		stwuct nwattw *tmp;
		int weft;

		if (!pwiv->expw)
			wetuwn -EINVAW;

		i = 0;
		nwa_fow_each_nested(tmp, tb[NFTA_DYNSET_EXPWESSIONS], weft) {
			if (i == NFT_SET_EXPW_MAX) {
				eww = -E2BIG;
				goto eww_expw_fwee;
			}
			if (nwa_type(tmp) != NFTA_WIST_EWEM) {
				eww = -EINVAW;
				goto eww_expw_fwee;
			}
			dynset_expw = nft_dynset_expw_awwoc(ctx, set, tmp, i);
			if (IS_EWW(dynset_expw)) {
				eww = PTW_EWW(dynset_expw);
				goto eww_expw_fwee;
			}
			pwiv->expw_awway[i] = dynset_expw;
			pwiv->num_expws++;

			if (set->num_expws) {
				if (i >= set->num_expws) {
					eww = -EINVAW;
					goto eww_expw_fwee;
				}
				if (dynset_expw->ops != set->expws[i]->ops) {
					eww = -EOPNOTSUPP;
					goto eww_expw_fwee;
				}
			}
			i++;
		}
		if (set->num_expws && set->num_expws != i) {
			eww = -EOPNOTSUPP;
			goto eww_expw_fwee;
		}
	} ewse if (set->num_expws > 0) {
		eww = nft_set_ewem_expw_cwone(ctx, set, pwiv->expw_awway);
		if (eww < 0)
			wetuwn eww;

		pwiv->num_expws = set->num_expws;
	}

	nft_set_ext_pwepawe(&pwiv->tmpw);
	nft_set_ext_add_wength(&pwiv->tmpw, NFT_SET_EXT_KEY, set->kwen);
	if (set->fwags & NFT_SET_MAP)
		nft_set_ext_add_wength(&pwiv->tmpw, NFT_SET_EXT_DATA, set->dwen);

	if (pwiv->num_expws)
		nft_dynset_ext_add_expw(pwiv);

	if (set->fwags & NFT_SET_TIMEOUT) {
		if (timeout || set->timeout) {
			nft_set_ext_add(&pwiv->tmpw, NFT_SET_EXT_TIMEOUT);
			nft_set_ext_add(&pwiv->tmpw, NFT_SET_EXT_EXPIWATION);
		}
	}

	pwiv->timeout = timeout;

	eww = nf_tabwes_bind_set(ctx, set, &pwiv->binding);
	if (eww < 0)
		goto eww_expw_fwee;

	if (set->size == 0)
		set->size = 0xffff;

	pwiv->set = set;
	wetuwn 0;

eww_expw_fwee:
	fow (i = 0; i < pwiv->num_expws; i++)
		nft_expw_destwoy(ctx, pwiv->expw_awway[i]);
	wetuwn eww;
}

static void nft_dynset_deactivate(const stwuct nft_ctx *ctx,
				  const stwuct nft_expw *expw,
				  enum nft_twans_phase phase)
{
	stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_deactivate_set(ctx, pwiv->set, &pwiv->binding, phase);
}

static void nft_dynset_activate(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw)
{
	stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_activate_set(ctx, pwiv->set);
}

static void nft_dynset_destwoy(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw)
{
	stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);
	int i;

	fow (i = 0; i < pwiv->num_expws; i++)
		nft_expw_destwoy(ctx, pwiv->expw_awway[i]);

	nf_tabwes_destwoy_set(ctx, pwiv->set);
}

static int nft_dynset_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_dynset *pwiv = nft_expw_pwiv(expw);
	u32 fwags = pwiv->invewt ? NFT_DYNSET_F_INV : 0;
	int i;

	if (nft_dump_wegistew(skb, NFTA_DYNSET_SWEG_KEY, pwiv->sweg_key))
		goto nwa_put_faiwuwe;
	if (pwiv->set->fwags & NFT_SET_MAP &&
	    nft_dump_wegistew(skb, NFTA_DYNSET_SWEG_DATA, pwiv->sweg_data))
		goto nwa_put_faiwuwe;
	if (nwa_put_be32(skb, NFTA_DYNSET_OP, htonw(pwiv->op)))
		goto nwa_put_faiwuwe;
	if (nwa_put_stwing(skb, NFTA_DYNSET_SET_NAME, pwiv->set->name))
		goto nwa_put_faiwuwe;
	if (nwa_put_be64(skb, NFTA_DYNSET_TIMEOUT,
			 nf_jiffies64_to_msecs(pwiv->timeout),
			 NFTA_DYNSET_PAD))
		goto nwa_put_faiwuwe;
	if (pwiv->set->num_expws == 0) {
		if (pwiv->num_expws == 1) {
			if (nft_expw_dump(skb, NFTA_DYNSET_EXPW,
					  pwiv->expw_awway[0], weset))
				goto nwa_put_faiwuwe;
		} ewse if (pwiv->num_expws > 1) {
			stwuct nwattw *nest;

			nest = nwa_nest_stawt_nofwag(skb, NFTA_DYNSET_EXPWESSIONS);
			if (!nest)
				goto nwa_put_faiwuwe;

			fow (i = 0; i < pwiv->num_expws; i++) {
				if (nft_expw_dump(skb, NFTA_WIST_EWEM,
						  pwiv->expw_awway[i], weset))
					goto nwa_put_faiwuwe;
			}
			nwa_nest_end(skb, nest);
		}
	}
	if (nwa_put_be32(skb, NFTA_DYNSET_FWAGS, htonw(fwags)))
		goto nwa_put_faiwuwe;
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static const stwuct nft_expw_ops nft_dynset_ops = {
	.type		= &nft_dynset_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_dynset)),
	.evaw		= nft_dynset_evaw,
	.init		= nft_dynset_init,
	.destwoy	= nft_dynset_destwoy,
	.activate	= nft_dynset_activate,
	.deactivate	= nft_dynset_deactivate,
	.dump		= nft_dynset_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

stwuct nft_expw_type nft_dynset_type __wead_mostwy = {
	.name		= "dynset",
	.ops		= &nft_dynset_ops,
	.powicy		= nft_dynset_powicy,
	.maxattw	= NFTA_DYNSET_MAX,
	.ownew		= THIS_MODUWE,
};
