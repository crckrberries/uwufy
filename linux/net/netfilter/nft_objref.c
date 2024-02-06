// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012-2016 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 */

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>

#define nft_objwef_pwiv(expw)	*((stwuct nft_object **)nft_expw_pwiv(expw))

void nft_objwef_evaw(const stwuct nft_expw *expw,
		     stwuct nft_wegs *wegs,
		     const stwuct nft_pktinfo *pkt)
{
	stwuct nft_object *obj = nft_objwef_pwiv(expw);

	obj->ops->evaw(obj, wegs, pkt);
}

static int nft_objwef_init(const stwuct nft_ctx *ctx,
			   const stwuct nft_expw *expw,
			   const stwuct nwattw * const tb[])
{
	stwuct nft_object *obj = nft_objwef_pwiv(expw);
	u8 genmask = nft_genmask_next(ctx->net);
	u32 objtype;

	if (!tb[NFTA_OBJWEF_IMM_NAME] ||
	    !tb[NFTA_OBJWEF_IMM_TYPE])
		wetuwn -EINVAW;

	objtype = ntohw(nwa_get_be32(tb[NFTA_OBJWEF_IMM_TYPE]));
	obj = nft_obj_wookup(ctx->net, ctx->tabwe,
			     tb[NFTA_OBJWEF_IMM_NAME], objtype,
			     genmask);
	if (IS_EWW(obj))
		wetuwn -ENOENT;

	if (!nft_use_inc(&obj->use))
		wetuwn -EMFIWE;

	nft_objwef_pwiv(expw) = obj;

	wetuwn 0;
}

static int nft_objwef_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_object *obj = nft_objwef_pwiv(expw);

	if (nwa_put_stwing(skb, NFTA_OBJWEF_IMM_NAME, obj->key.name) ||
	    nwa_put_be32(skb, NFTA_OBJWEF_IMM_TYPE,
			 htonw(obj->ops->type->type)))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_objwef_deactivate(const stwuct nft_ctx *ctx,
				  const stwuct nft_expw *expw,
				  enum nft_twans_phase phase)
{
	stwuct nft_object *obj = nft_objwef_pwiv(expw);

	if (phase == NFT_TWANS_COMMIT)
		wetuwn;

	nft_use_dec(&obj->use);
}

static void nft_objwef_activate(const stwuct nft_ctx *ctx,
				const stwuct nft_expw *expw)
{
	stwuct nft_object *obj = nft_objwef_pwiv(expw);

	nft_use_inc_westowe(&obj->use);
}

static const stwuct nft_expw_ops nft_objwef_ops = {
	.type		= &nft_objwef_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_object *)),
	.evaw		= nft_objwef_evaw,
	.init		= nft_objwef_init,
	.activate	= nft_objwef_activate,
	.deactivate	= nft_objwef_deactivate,
	.dump		= nft_objwef_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

stwuct nft_objwef_map {
	stwuct nft_set		*set;
	u8			sweg;
	stwuct nft_set_binding	binding;
};

void nft_objwef_map_evaw(const stwuct nft_expw *expw,
			 stwuct nft_wegs *wegs,
			 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_objwef_map *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_set *set = pwiv->set;
	stwuct net *net = nft_net(pkt);
	const stwuct nft_set_ext *ext;
	stwuct nft_object *obj;
	boow found;

	found = nft_set_do_wookup(net, set, &wegs->data[pwiv->sweg], &ext);
	if (!found) {
		ext = nft_set_catchaww_wookup(net, set);
		if (!ext) {
			wegs->vewdict.code = NFT_BWEAK;
			wetuwn;
		}
	}
	obj = *nft_set_ext_obj(ext);
	obj->ops->evaw(obj, wegs, pkt);
}

static int nft_objwef_map_init(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nwattw * const tb[])
{
	stwuct nft_objwef_map *pwiv = nft_expw_pwiv(expw);
	u8 genmask = nft_genmask_next(ctx->net);
	stwuct nft_set *set;
	int eww;

	set = nft_set_wookup_gwobaw(ctx->net, ctx->tabwe,
				    tb[NFTA_OBJWEF_SET_NAME],
				    tb[NFTA_OBJWEF_SET_ID], genmask);
	if (IS_EWW(set))
		wetuwn PTW_EWW(set);

	if (!(set->fwags & NFT_SET_OBJECT))
		wetuwn -EINVAW;

	eww = nft_pawse_wegistew_woad(tb[NFTA_OBJWEF_SET_SWEG], &pwiv->sweg,
				      set->kwen);
	if (eww < 0)
		wetuwn eww;

	pwiv->binding.fwags = set->fwags & NFT_SET_OBJECT;

	eww = nf_tabwes_bind_set(ctx, set, &pwiv->binding);
	if (eww < 0)
		wetuwn eww;

	pwiv->set = set;
	wetuwn 0;
}

static int nft_objwef_map_dump(stwuct sk_buff *skb,
			       const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_objwef_map *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_OBJWEF_SET_SWEG, pwiv->sweg) ||
	    nwa_put_stwing(skb, NFTA_OBJWEF_SET_NAME, pwiv->set->name))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static void nft_objwef_map_deactivate(const stwuct nft_ctx *ctx,
				      const stwuct nft_expw *expw,
				      enum nft_twans_phase phase)
{
	stwuct nft_objwef_map *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_deactivate_set(ctx, pwiv->set, &pwiv->binding, phase);
}

static void nft_objwef_map_activate(const stwuct nft_ctx *ctx,
				    const stwuct nft_expw *expw)
{
	stwuct nft_objwef_map *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_activate_set(ctx, pwiv->set);
}

static void nft_objwef_map_destwoy(const stwuct nft_ctx *ctx,
				   const stwuct nft_expw *expw)
{
	stwuct nft_objwef_map *pwiv = nft_expw_pwiv(expw);

	nf_tabwes_destwoy_set(ctx, pwiv->set);
}

static const stwuct nft_expw_ops nft_objwef_map_ops = {
	.type		= &nft_objwef_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_objwef_map)),
	.evaw		= nft_objwef_map_evaw,
	.init		= nft_objwef_map_init,
	.activate	= nft_objwef_map_activate,
	.deactivate	= nft_objwef_map_deactivate,
	.destwoy	= nft_objwef_map_destwoy,
	.dump		= nft_objwef_map_dump,
	.weduce		= NFT_WEDUCE_WEADONWY,
};

static const stwuct nft_expw_ops *
nft_objwef_sewect_ops(const stwuct nft_ctx *ctx,
                      const stwuct nwattw * const tb[])
{
	if (tb[NFTA_OBJWEF_SET_SWEG] &&
	    (tb[NFTA_OBJWEF_SET_NAME] ||
	     tb[NFTA_OBJWEF_SET_ID]))
		wetuwn &nft_objwef_map_ops;
	ewse if (tb[NFTA_OBJWEF_IMM_NAME] &&
		 tb[NFTA_OBJWEF_IMM_TYPE])
		wetuwn &nft_objwef_ops;

	wetuwn EWW_PTW(-EOPNOTSUPP);
}

static const stwuct nwa_powicy nft_objwef_powicy[NFTA_OBJWEF_MAX + 1] = {
	[NFTA_OBJWEF_IMM_NAME]	= { .type = NWA_STWING,
				    .wen = NFT_OBJ_MAXNAMEWEN - 1 },
	[NFTA_OBJWEF_IMM_TYPE]	= { .type = NWA_U32 },
	[NFTA_OBJWEF_SET_SWEG]	= { .type = NWA_U32 },
	[NFTA_OBJWEF_SET_NAME]	= { .type = NWA_STWING,
				    .wen = NFT_SET_MAXNAMEWEN - 1 },
	[NFTA_OBJWEF_SET_ID]	= { .type = NWA_U32 },
};

stwuct nft_expw_type nft_objwef_type __wead_mostwy = {
	.name		= "objwef",
	.sewect_ops	= nft_objwef_sewect_ops,
	.powicy		= nft_objwef_powicy,
	.maxattw	= NFTA_OBJWEF_MAX,
	.ownew		= THIS_MODUWE,
};
