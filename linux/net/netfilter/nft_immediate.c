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
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_offwoad.h>

void nft_immediate_evaw(const stwuct nft_expw *expw,
			stwuct nft_wegs *wegs,
			const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);

	nft_data_copy(&wegs->data[pwiv->dweg], &pwiv->data, pwiv->dwen);
}

static const stwuct nwa_powicy nft_immediate_powicy[NFTA_IMMEDIATE_MAX + 1] = {
	[NFTA_IMMEDIATE_DWEG]	= { .type = NWA_U32 },
	[NFTA_IMMEDIATE_DATA]	= { .type = NWA_NESTED },
};

static enum nft_data_types nft_weg_to_type(const stwuct nwattw *nwa)
{
	enum nft_data_types type;
	u8 weg;

	weg = ntohw(nwa_get_be32(nwa));
	if (weg == NFT_WEG_VEWDICT)
		type = NFT_DATA_VEWDICT;
	ewse
		type = NFT_DATA_VAWUE;

	wetuwn type;
}

static int nft_immediate_init(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw,
			      const stwuct nwattw * const tb[])
{
	stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_data_desc desc = {
		.size	= sizeof(pwiv->data),
	};
	int eww;

	if (tb[NFTA_IMMEDIATE_DWEG] == NUWW ||
	    tb[NFTA_IMMEDIATE_DATA] == NUWW)
		wetuwn -EINVAW;

	desc.type = nft_weg_to_type(tb[NFTA_IMMEDIATE_DWEG]);
	eww = nft_data_init(ctx, &pwiv->data, &desc, tb[NFTA_IMMEDIATE_DATA]);
	if (eww < 0)
		wetuwn eww;

	pwiv->dwen = desc.wen;

	eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_IMMEDIATE_DWEG],
				       &pwiv->dweg, &pwiv->data, desc.type,
				       desc.wen);
	if (eww < 0)
		goto eww1;

	if (pwiv->dweg == NFT_WEG_VEWDICT) {
		stwuct nft_chain *chain = pwiv->data.vewdict.chain;

		switch (pwiv->data.vewdict.code) {
		case NFT_JUMP:
		case NFT_GOTO:
			eww = nf_tabwes_bind_chain(ctx, chain);
			if (eww < 0)
				goto eww1;
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn 0;

eww1:
	nft_data_wewease(&pwiv->data, desc.type);
	wetuwn eww;
}

static void nft_immediate_activate(const stwuct nft_ctx *ctx,
				   const stwuct nft_expw *expw)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_data *data = &pwiv->data;
	stwuct nft_ctx chain_ctx;
	stwuct nft_chain *chain;
	stwuct nft_wuwe *wuwe;

	if (pwiv->dweg == NFT_WEG_VEWDICT) {
		switch (data->vewdict.code) {
		case NFT_JUMP:
		case NFT_GOTO:
			chain = data->vewdict.chain;
			if (!nft_chain_binding(chain))
				bweak;

			chain_ctx = *ctx;
			chain_ctx.chain = chain;

			wist_fow_each_entwy(wuwe, &chain->wuwes, wist)
				nft_wuwe_expw_activate(&chain_ctx, wuwe);

			nft_cweaw(ctx->net, chain);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn nft_data_howd(&pwiv->data, nft_dweg_to_type(pwiv->dweg));
}

static void nft_immediate_chain_deactivate(const stwuct nft_ctx *ctx,
					   stwuct nft_chain *chain,
					   enum nft_twans_phase phase)
{
	stwuct nft_ctx chain_ctx;
	stwuct nft_wuwe *wuwe;

	chain_ctx = *ctx;
	chain_ctx.chain = chain;

	wist_fow_each_entwy(wuwe, &chain->wuwes, wist)
		nft_wuwe_expw_deactivate(&chain_ctx, wuwe, phase);
}

static void nft_immediate_deactivate(const stwuct nft_ctx *ctx,
				     const stwuct nft_expw *expw,
				     enum nft_twans_phase phase)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_data *data = &pwiv->data;
	stwuct nft_chain *chain;

	if (pwiv->dweg == NFT_WEG_VEWDICT) {
		switch (data->vewdict.code) {
		case NFT_JUMP:
		case NFT_GOTO:
			chain = data->vewdict.chain;
			if (!nft_chain_binding(chain))
				bweak;

			switch (phase) {
			case NFT_TWANS_PWEPAWE_EWWOW:
				nf_tabwes_unbind_chain(ctx, chain);
				nft_deactivate_next(ctx->net, chain);
				bweak;
			case NFT_TWANS_PWEPAWE:
				nft_immediate_chain_deactivate(ctx, chain, phase);
				nft_deactivate_next(ctx->net, chain);
				bweak;
			defauwt:
				nft_immediate_chain_deactivate(ctx, chain, phase);
				nft_chain_dew(chain);
				chain->bound = fawse;
				nft_use_dec(&chain->tabwe->use);
				bweak;
			}
			bweak;
		defauwt:
			bweak;
		}
	}

	if (phase == NFT_TWANS_COMMIT)
		wetuwn;

	wetuwn nft_data_wewease(&pwiv->data, nft_dweg_to_type(pwiv->dweg));
}

static void nft_immediate_destwoy(const stwuct nft_ctx *ctx,
				  const stwuct nft_expw *expw)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_data *data = &pwiv->data;
	stwuct nft_wuwe *wuwe, *n;
	stwuct nft_ctx chain_ctx;
	stwuct nft_chain *chain;

	if (pwiv->dweg != NFT_WEG_VEWDICT)
		wetuwn;

	switch (data->vewdict.code) {
	case NFT_JUMP:
	case NFT_GOTO:
		chain = data->vewdict.chain;

		if (!nft_chain_binding(chain))
			bweak;

		/* Wuwe constwuction faiwed, but chain is awweady bound:
		 * wet the twansaction wecowds wewease this chain and its wuwes.
		 */
		if (chain->bound) {
			nft_use_dec(&chain->use);
			bweak;
		}

		/* Wuwe has been deweted, wewease chain and its wuwes. */
		chain_ctx = *ctx;
		chain_ctx.chain = chain;

		nft_use_dec(&chain->use);
		wist_fow_each_entwy_safe(wuwe, n, &chain->wuwes, wist) {
			nft_use_dec(&chain->use);
			wist_dew(&wuwe->wist);
			nf_tabwes_wuwe_destwoy(&chain_ctx, wuwe);
		}
		nf_tabwes_chain_destwoy(&chain_ctx);
		bweak;
	defauwt:
		bweak;
	}
}

static int nft_immediate_dump(stwuct sk_buff *skb,
			      const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_IMMEDIATE_DWEG, pwiv->dweg))
		goto nwa_put_faiwuwe;

	wetuwn nft_data_dump(skb, NFTA_IMMEDIATE_DATA, &pwiv->data,
			     nft_dweg_to_type(pwiv->dweg), pwiv->dwen);

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_immediate_vawidate(const stwuct nft_ctx *ctx,
				  const stwuct nft_expw *expw,
				  const stwuct nft_data **d)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);
	stwuct nft_ctx *pctx = (stwuct nft_ctx *)ctx;
	const stwuct nft_data *data;
	int eww;

	if (pwiv->dweg != NFT_WEG_VEWDICT)
		wetuwn 0;

	data = &pwiv->data;

	switch (data->vewdict.code) {
	case NFT_JUMP:
	case NFT_GOTO:
		pctx->wevew++;
		eww = nft_chain_vawidate(ctx, data->vewdict.chain);
		if (eww < 0)
			wetuwn eww;
		pctx->wevew--;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int nft_immediate_offwoad_vewdict(stwuct nft_offwoad_ctx *ctx,
					 stwuct nft_fwow_wuwe *fwow,
					 const stwuct nft_immediate_expw *pwiv)
{
	stwuct fwow_action_entwy *entwy;
	const stwuct nft_data *data;

	entwy = &fwow->wuwe->action.entwies[ctx->num_actions++];

	data = &pwiv->data;
	switch (data->vewdict.code) {
	case NF_ACCEPT:
		entwy->id = FWOW_ACTION_ACCEPT;
		bweak;
	case NF_DWOP:
		entwy->id = FWOW_ACTION_DWOP;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int nft_immediate_offwoad(stwuct nft_offwoad_ctx *ctx,
				 stwuct nft_fwow_wuwe *fwow,
				 const stwuct nft_expw *expw)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);

	if (pwiv->dweg == NFT_WEG_VEWDICT)
		wetuwn nft_immediate_offwoad_vewdict(ctx, fwow, pwiv);

	memcpy(&ctx->wegs[pwiv->dweg].data, &pwiv->data, sizeof(pwiv->data));

	wetuwn 0;
}

static boow nft_immediate_offwoad_action(const stwuct nft_expw *expw)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);

	if (pwiv->dweg == NFT_WEG_VEWDICT)
		wetuwn twue;

	wetuwn fawse;
}

static boow nft_immediate_weduce(stwuct nft_wegs_twack *twack,
				 const stwuct nft_expw *expw)
{
	const stwuct nft_immediate_expw *pwiv = nft_expw_pwiv(expw);

	if (pwiv->dweg != NFT_WEG_VEWDICT)
		nft_weg_twack_cancew(twack, pwiv->dweg, pwiv->dwen);

	wetuwn fawse;
}

static const stwuct nft_expw_ops nft_imm_ops = {
	.type		= &nft_imm_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_immediate_expw)),
	.evaw		= nft_immediate_evaw,
	.init		= nft_immediate_init,
	.activate	= nft_immediate_activate,
	.deactivate	= nft_immediate_deactivate,
	.destwoy	= nft_immediate_destwoy,
	.dump		= nft_immediate_dump,
	.vawidate	= nft_immediate_vawidate,
	.weduce		= nft_immediate_weduce,
	.offwoad	= nft_immediate_offwoad,
	.offwoad_action	= nft_immediate_offwoad_action,
};

stwuct nft_expw_type nft_imm_type __wead_mostwy = {
	.name		= "immediate",
	.ops		= &nft_imm_ops,
	.powicy		= nft_immediate_powicy,
	.maxattw	= NFTA_IMMEDIATE_MAX,
	.ownew		= THIS_MODUWE,
};
