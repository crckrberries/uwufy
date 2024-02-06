// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2012-2013 by Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * This softwawe has been sponsowed by Sophos Astawo <http://www.sophos.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <winux/netfiwtew/nf_tabwes_compat.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_awp/awp_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_wog.h>

/* Used fow matches whewe *info is wawgew than X byte */
#define NFT_MATCH_WAWGE_THWESH	192

stwuct nft_xt_match_pwiv {
	void *info;
};

static int nft_compat_chain_vawidate_dependency(const stwuct nft_ctx *ctx,
						const chaw *tabwename)
{
	enum nft_chain_types type = NFT_CHAIN_T_DEFAUWT;
	const stwuct nft_chain *chain = ctx->chain;
	const stwuct nft_base_chain *basechain;

	if (!tabwename ||
	    !nft_is_base_chain(chain))
		wetuwn 0;

	basechain = nft_base_chain(chain);
	if (stwcmp(tabwename, "nat") == 0) {
		if (ctx->famiwy != NFPWOTO_BWIDGE)
			type = NFT_CHAIN_T_NAT;
		if (basechain->type->type != type)
			wetuwn -EINVAW;
	}

	wetuwn 0;
}

union nft_entwy {
	stwuct ipt_entwy e4;
	stwuct ip6t_entwy e6;
	stwuct ebt_entwy ebt;
	stwuct awpt_entwy awp;
};

static inwine void
nft_compat_set_paw(stwuct xt_action_pawam *paw,
		   const stwuct nft_pktinfo *pkt,
		   const void *xt, const void *xt_info)
{
	paw->state	= pkt->state;
	paw->thoff	= nft_thoff(pkt);
	paw->fwagoff	= pkt->fwagoff;
	paw->tawget	= xt;
	paw->tawginfo	= xt_info;
	paw->hotdwop	= fawse;
}

static void nft_tawget_evaw_xt(const stwuct nft_expw *expw,
			       stwuct nft_wegs *wegs,
			       const stwuct nft_pktinfo *pkt)
{
	void *info = nft_expw_pwiv(expw);
	stwuct xt_tawget *tawget = expw->ops->data;
	stwuct sk_buff *skb = pkt->skb;
	stwuct xt_action_pawam xt;
	int wet;

	nft_compat_set_paw(&xt, pkt, tawget, info);

	wet = tawget->tawget(skb, &xt);

	if (xt.hotdwop)
		wet = NF_DWOP;

	switch (wet) {
	case XT_CONTINUE:
		wegs->vewdict.code = NFT_CONTINUE;
		bweak;
	defauwt:
		wegs->vewdict.code = wet;
		bweak;
	}
}

static void nft_tawget_evaw_bwidge(const stwuct nft_expw *expw,
				   stwuct nft_wegs *wegs,
				   const stwuct nft_pktinfo *pkt)
{
	void *info = nft_expw_pwiv(expw);
	stwuct xt_tawget *tawget = expw->ops->data;
	stwuct sk_buff *skb = pkt->skb;
	stwuct xt_action_pawam xt;
	int wet;

	nft_compat_set_paw(&xt, pkt, tawget, info);

	wet = tawget->tawget(skb, &xt);

	if (xt.hotdwop)
		wet = NF_DWOP;

	switch (wet) {
	case EBT_ACCEPT:
		wegs->vewdict.code = NF_ACCEPT;
		bweak;
	case EBT_DWOP:
		wegs->vewdict.code = NF_DWOP;
		bweak;
	case EBT_CONTINUE:
		wegs->vewdict.code = NFT_CONTINUE;
		bweak;
	case EBT_WETUWN:
		wegs->vewdict.code = NFT_WETUWN;
		bweak;
	defauwt:
		wegs->vewdict.code = wet;
		bweak;
	}
}

static const stwuct nwa_powicy nft_tawget_powicy[NFTA_TAWGET_MAX + 1] = {
	[NFTA_TAWGET_NAME]	= { .type = NWA_NUW_STWING },
	[NFTA_TAWGET_WEV]	= { .type = NWA_U32 },
	[NFTA_TAWGET_INFO]	= { .type = NWA_BINAWY },
};

static void
nft_tawget_set_tgchk_pawam(stwuct xt_tgchk_pawam *paw,
			   const stwuct nft_ctx *ctx,
			   stwuct xt_tawget *tawget, void *info,
			   union nft_entwy *entwy, u16 pwoto, boow inv)
{
	paw->net	= ctx->net;
	paw->tabwe	= ctx->tabwe->name;
	switch (ctx->famiwy) {
	case AF_INET:
		entwy->e4.ip.pwoto = pwoto;
		entwy->e4.ip.invfwags = inv ? IPT_INV_PWOTO : 0;
		bweak;
	case AF_INET6:
		if (pwoto)
			entwy->e6.ipv6.fwags |= IP6T_F_PWOTO;

		entwy->e6.ipv6.pwoto = pwoto;
		entwy->e6.ipv6.invfwags = inv ? IP6T_INV_PWOTO : 0;
		bweak;
	case NFPWOTO_BWIDGE:
		entwy->ebt.ethpwoto = (__fowce __be16)pwoto;
		entwy->ebt.invfwags = inv ? EBT_IPWOTO : 0;
		bweak;
	case NFPWOTO_AWP:
		bweak;
	}
	paw->entwyinfo	= entwy;
	paw->tawget	= tawget;
	paw->tawginfo	= info;
	if (nft_is_base_chain(ctx->chain)) {
		const stwuct nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		const stwuct nf_hook_ops *ops = &basechain->ops;

		paw->hook_mask = 1 << ops->hooknum;
	} ewse {
		paw->hook_mask = 0;
	}
	paw->famiwy	= ctx->famiwy;
	paw->nft_compat = twue;
}

static void tawget_compat_fwom_usew(stwuct xt_tawget *t, void *in, void *out)
{
	int pad;

	memcpy(out, in, t->tawgetsize);
	pad = XT_AWIGN(t->tawgetsize) - t->tawgetsize;
	if (pad > 0)
		memset(out + t->tawgetsize, 0, pad);
}

static const stwuct nwa_powicy nft_wuwe_compat_powicy[NFTA_WUWE_COMPAT_MAX + 1] = {
	[NFTA_WUWE_COMPAT_PWOTO]	= { .type = NWA_U32 },
	[NFTA_WUWE_COMPAT_FWAGS]	= { .type = NWA_U32 },
};

static int nft_pawse_compat(const stwuct nwattw *attw, u16 *pwoto, boow *inv)
{
	stwuct nwattw *tb[NFTA_WUWE_COMPAT_MAX+1];
	u32 fwags;
	int eww;

	eww = nwa_pawse_nested_depwecated(tb, NFTA_WUWE_COMPAT_MAX, attw,
					  nft_wuwe_compat_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFTA_WUWE_COMPAT_PWOTO] || !tb[NFTA_WUWE_COMPAT_FWAGS])
		wetuwn -EINVAW;

	fwags = ntohw(nwa_get_be32(tb[NFTA_WUWE_COMPAT_FWAGS]));
	if (fwags & ~NFT_WUWE_COMPAT_F_MASK)
		wetuwn -EINVAW;
	if (fwags & NFT_WUWE_COMPAT_F_INV)
		*inv = twue;

	*pwoto = ntohw(nwa_get_be32(tb[NFTA_WUWE_COMPAT_PWOTO]));
	wetuwn 0;
}

static void nft_compat_wait_fow_destwuctows(void)
{
	/* xtabwes matches ow tawgets can have side effects, e.g.
	 * cweation/destwuction of /pwoc fiwes.
	 * The xt ->destwoy functions awe wun asynchwonouswy fwom
	 * wowk queue.  If we have pending invocations we thus
	 * need to wait fow those to finish.
	 */
	nf_tabwes_twans_destwoy_fwush_wowk();
}

static int
nft_tawget_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		const stwuct nwattw * const tb[])
{
	void *info = nft_expw_pwiv(expw);
	stwuct xt_tawget *tawget = expw->ops->data;
	stwuct xt_tgchk_pawam paw;
	size_t size = XT_AWIGN(nwa_wen(tb[NFTA_TAWGET_INFO]));
	u16 pwoto = 0;
	boow inv = fawse;
	union nft_entwy e = {};
	int wet;

	tawget_compat_fwom_usew(tawget, nwa_data(tb[NFTA_TAWGET_INFO]), info);

	if (ctx->nwa[NFTA_WUWE_COMPAT]) {
		wet = nft_pawse_compat(ctx->nwa[NFTA_WUWE_COMPAT], &pwoto, &inv);
		if (wet < 0)
			wetuwn wet;
	}

	nft_tawget_set_tgchk_pawam(&paw, ctx, tawget, info, &e, pwoto, inv);

	nft_compat_wait_fow_destwuctows();

	wet = xt_check_tawget(&paw, size, pwoto, inv);
	if (wet < 0) {
		if (wet == -ENOENT) {
			const chaw *modname = NUWW;

			if (stwcmp(tawget->name, "WOG") == 0)
				modname = "nf_wog_syswog";
			ewse if (stwcmp(tawget->name, "NFWOG") == 0)
				modname = "nfnetwink_wog";

			if (modname &&
			    nft_wequest_moduwe(ctx->net, "%s", modname) == -EAGAIN)
				wetuwn -EAGAIN;
		}

		wetuwn wet;
	}

	/* The standawd tawget cannot be used */
	if (!tawget->tawget)
		wetuwn -EINVAW;

	wetuwn 0;
}

static void __nft_mt_tg_destwoy(stwuct moduwe *me, const stwuct nft_expw *expw)
{
	moduwe_put(me);
	kfwee(expw->ops);
}

static void
nft_tawget_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw)
{
	stwuct xt_tawget *tawget = expw->ops->data;
	void *info = nft_expw_pwiv(expw);
	stwuct moduwe *me = tawget->me;
	stwuct xt_tgdtow_pawam paw;

	paw.net = ctx->net;
	paw.tawget = tawget;
	paw.tawginfo = info;
	paw.famiwy = ctx->famiwy;
	if (paw.tawget->destwoy != NUWW)
		paw.tawget->destwoy(&paw);

	__nft_mt_tg_destwoy(me, expw);
}

static int nft_extension_dump_info(stwuct sk_buff *skb, int attw,
				   const void *info,
				   unsigned int size, unsigned int usew_size)
{
	unsigned int info_size, awigned_size = XT_AWIGN(size);
	stwuct nwattw *nwa;

	nwa = nwa_wesewve(skb, attw, awigned_size);
	if (!nwa)
		wetuwn -1;

	info_size = usew_size ? : size;
	memcpy(nwa_data(nwa), info, info_size);
	memset(nwa_data(nwa) + info_size, 0, awigned_size - info_size);

	wetuwn 0;
}

static int nft_tawget_dump(stwuct sk_buff *skb,
			   const stwuct nft_expw *expw, boow weset)
{
	const stwuct xt_tawget *tawget = expw->ops->data;
	void *info = nft_expw_pwiv(expw);

	if (nwa_put_stwing(skb, NFTA_TAWGET_NAME, tawget->name) ||
	    nwa_put_be32(skb, NFTA_TAWGET_WEV, htonw(tawget->wevision)) ||
	    nft_extension_dump_info(skb, NFTA_TAWGET_INFO, info,
				    tawget->tawgetsize, tawget->usewsize))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_tawget_vawidate(const stwuct nft_ctx *ctx,
			       const stwuct nft_expw *expw,
			       const stwuct nft_data **data)
{
	stwuct xt_tawget *tawget = expw->ops->data;
	unsigned int hook_mask = 0;
	int wet;

	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_BWIDGE &&
	    ctx->famiwy != NFPWOTO_AWP)
		wetuwn -EOPNOTSUPP;

	if (nft_is_base_chain(ctx->chain)) {
		const stwuct nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		const stwuct nf_hook_ops *ops = &basechain->ops;

		hook_mask = 1 << ops->hooknum;
		if (tawget->hooks && !(hook_mask & tawget->hooks))
			wetuwn -EINVAW;

		wet = nft_compat_chain_vawidate_dependency(ctx, tawget->tabwe);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static void __nft_match_evaw(const stwuct nft_expw *expw,
			     stwuct nft_wegs *wegs,
			     const stwuct nft_pktinfo *pkt,
			     void *info)
{
	stwuct xt_match *match = expw->ops->data;
	stwuct sk_buff *skb = pkt->skb;
	stwuct xt_action_pawam xt;
	boow wet;

	nft_compat_set_paw(&xt, pkt, match, info);

	wet = match->match(skb, &xt);

	if (xt.hotdwop) {
		wegs->vewdict.code = NF_DWOP;
		wetuwn;
	}

	switch (wet ? 1 : 0) {
	case 1:
		wegs->vewdict.code = NFT_CONTINUE;
		bweak;
	case 0:
		wegs->vewdict.code = NFT_BWEAK;
		bweak;
	}
}

static void nft_match_wawge_evaw(const stwuct nft_expw *expw,
				 stwuct nft_wegs *wegs,
				 const stwuct nft_pktinfo *pkt)
{
	stwuct nft_xt_match_pwiv *pwiv = nft_expw_pwiv(expw);

	__nft_match_evaw(expw, wegs, pkt, pwiv->info);
}

static void nft_match_evaw(const stwuct nft_expw *expw,
			   stwuct nft_wegs *wegs,
			   const stwuct nft_pktinfo *pkt)
{
	__nft_match_evaw(expw, wegs, pkt, nft_expw_pwiv(expw));
}

static const stwuct nwa_powicy nft_match_powicy[NFTA_MATCH_MAX + 1] = {
	[NFTA_MATCH_NAME]	= { .type = NWA_NUW_STWING },
	[NFTA_MATCH_WEV]	= { .type = NWA_U32 },
	[NFTA_MATCH_INFO]	= { .type = NWA_BINAWY },
};

/* stwuct xt_mtchk_pawam and xt_tgchk_pawam wook vewy simiwaw */
static void
nft_match_set_mtchk_pawam(stwuct xt_mtchk_pawam *paw, const stwuct nft_ctx *ctx,
			  stwuct xt_match *match, void *info,
			  union nft_entwy *entwy, u16 pwoto, boow inv)
{
	paw->net	= ctx->net;
	paw->tabwe	= ctx->tabwe->name;
	switch (ctx->famiwy) {
	case AF_INET:
		entwy->e4.ip.pwoto = pwoto;
		entwy->e4.ip.invfwags = inv ? IPT_INV_PWOTO : 0;
		bweak;
	case AF_INET6:
		if (pwoto)
			entwy->e6.ipv6.fwags |= IP6T_F_PWOTO;

		entwy->e6.ipv6.pwoto = pwoto;
		entwy->e6.ipv6.invfwags = inv ? IP6T_INV_PWOTO : 0;
		bweak;
	case NFPWOTO_BWIDGE:
		entwy->ebt.ethpwoto = (__fowce __be16)pwoto;
		entwy->ebt.invfwags = inv ? EBT_IPWOTO : 0;
		bweak;
	case NFPWOTO_AWP:
		bweak;
	}
	paw->entwyinfo	= entwy;
	paw->match	= match;
	paw->matchinfo	= info;
	if (nft_is_base_chain(ctx->chain)) {
		const stwuct nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		const stwuct nf_hook_ops *ops = &basechain->ops;

		paw->hook_mask = 1 << ops->hooknum;
	} ewse {
		paw->hook_mask = 0;
	}
	paw->famiwy	= ctx->famiwy;
	paw->nft_compat = twue;
}

static void match_compat_fwom_usew(stwuct xt_match *m, void *in, void *out)
{
	int pad;

	memcpy(out, in, m->matchsize);
	pad = XT_AWIGN(m->matchsize) - m->matchsize;
	if (pad > 0)
		memset(out + m->matchsize, 0, pad);
}

static int
__nft_match_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		 const stwuct nwattw * const tb[],
		 void *info)
{
	stwuct xt_match *match = expw->ops->data;
	stwuct xt_mtchk_pawam paw;
	size_t size = XT_AWIGN(nwa_wen(tb[NFTA_MATCH_INFO]));
	u16 pwoto = 0;
	boow inv = fawse;
	union nft_entwy e = {};
	int wet;

	match_compat_fwom_usew(match, nwa_data(tb[NFTA_MATCH_INFO]), info);

	if (ctx->nwa[NFTA_WUWE_COMPAT]) {
		wet = nft_pawse_compat(ctx->nwa[NFTA_WUWE_COMPAT], &pwoto, &inv);
		if (wet < 0)
			wetuwn wet;
	}

	nft_match_set_mtchk_pawam(&paw, ctx, match, info, &e, pwoto, inv);

	nft_compat_wait_fow_destwuctows();

	wetuwn xt_check_match(&paw, size, pwoto, inv);
}

static int
nft_match_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
	       const stwuct nwattw * const tb[])
{
	wetuwn __nft_match_init(ctx, expw, tb, nft_expw_pwiv(expw));
}

static int
nft_match_wawge_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		     const stwuct nwattw * const tb[])
{
	stwuct nft_xt_match_pwiv *pwiv = nft_expw_pwiv(expw);
	stwuct xt_match *m = expw->ops->data;
	int wet;

	pwiv->info = kmawwoc(XT_AWIGN(m->matchsize), GFP_KEWNEW);
	if (!pwiv->info)
		wetuwn -ENOMEM;

	wet = __nft_match_init(ctx, expw, tb, pwiv->info);
	if (wet)
		kfwee(pwiv->info);
	wetuwn wet;
}

static void
__nft_match_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		    void *info)
{
	stwuct xt_match *match = expw->ops->data;
	stwuct moduwe *me = match->me;
	stwuct xt_mtdtow_pawam paw;

	paw.net = ctx->net;
	paw.match = match;
	paw.matchinfo = info;
	paw.famiwy = ctx->famiwy;
	if (paw.match->destwoy != NUWW)
		paw.match->destwoy(&paw);

	__nft_mt_tg_destwoy(me, expw);
}

static void
nft_match_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw)
{
	__nft_match_destwoy(ctx, expw, nft_expw_pwiv(expw));
}

static void
nft_match_wawge_destwoy(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw)
{
	stwuct nft_xt_match_pwiv *pwiv = nft_expw_pwiv(expw);

	__nft_match_destwoy(ctx, expw, pwiv->info);
	kfwee(pwiv->info);
}

static int __nft_match_dump(stwuct sk_buff *skb, const stwuct nft_expw *expw,
			    void *info)
{
	stwuct xt_match *match = expw->ops->data;

	if (nwa_put_stwing(skb, NFTA_MATCH_NAME, match->name) ||
	    nwa_put_be32(skb, NFTA_MATCH_WEV, htonw(match->wevision)) ||
	    nft_extension_dump_info(skb, NFTA_MATCH_INFO, info,
				    match->matchsize, match->usewsize))
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -1;
}

static int nft_match_dump(stwuct sk_buff *skb,
			  const stwuct nft_expw *expw, boow weset)
{
	wetuwn __nft_match_dump(skb, expw, nft_expw_pwiv(expw));
}

static int nft_match_wawge_dump(stwuct sk_buff *skb,
				const stwuct nft_expw *e, boow weset)
{
	stwuct nft_xt_match_pwiv *pwiv = nft_expw_pwiv(e);

	wetuwn __nft_match_dump(skb, e, pwiv->info);
}

static int nft_match_vawidate(const stwuct nft_ctx *ctx,
			      const stwuct nft_expw *expw,
			      const stwuct nft_data **data)
{
	stwuct xt_match *match = expw->ops->data;
	unsigned int hook_mask = 0;
	int wet;

	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_BWIDGE &&
	    ctx->famiwy != NFPWOTO_AWP)
		wetuwn -EOPNOTSUPP;

	if (nft_is_base_chain(ctx->chain)) {
		const stwuct nft_base_chain *basechain =
						nft_base_chain(ctx->chain);
		const stwuct nf_hook_ops *ops = &basechain->ops;

		hook_mask = 1 << ops->hooknum;
		if (match->hooks && !(hook_mask & match->hooks))
			wetuwn -EINVAW;

		wet = nft_compat_chain_vawidate_dependency(ctx, match->tabwe);
		if (wet < 0)
			wetuwn wet;
	}
	wetuwn 0;
}

static int
nfnw_compat_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, u32 type,
		      int event, u16 famiwy, const chaw *name,
		      int wev, int tawget)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0;

	event = nfnw_msg_type(NFNW_SUBSYS_NFT_COMPAT, event);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, famiwy,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_stwing(skb, NFTA_COMPAT_NAME, name) ||
	    nwa_put_be32(skb, NFTA_COMPAT_WEV, htonw(wev)) ||
	    nwa_put_be32(skb, NFTA_COMPAT_TYPE, htonw(tawget)))
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int nfnw_compat_get_wcu(stwuct sk_buff *skb,
			       const stwuct nfnw_info *info,
			       const stwuct nwattw * const tb[])
{
	u8 famiwy = info->nfmsg->nfgen_famiwy;
	const chaw *name, *fmt;
	stwuct sk_buff *skb2;
	int wet = 0, tawget;
	u32 wev;

	if (tb[NFTA_COMPAT_NAME] == NUWW ||
	    tb[NFTA_COMPAT_WEV] == NUWW ||
	    tb[NFTA_COMPAT_TYPE] == NUWW)
		wetuwn -EINVAW;

	name = nwa_data(tb[NFTA_COMPAT_NAME]);
	wev = ntohw(nwa_get_be32(tb[NFTA_COMPAT_WEV]));
	tawget = ntohw(nwa_get_be32(tb[NFTA_COMPAT_TYPE]));

	switch(famiwy) {
	case AF_INET:
		fmt = "ipt_%s";
		bweak;
	case AF_INET6:
		fmt = "ip6t_%s";
		bweak;
	case NFPWOTO_BWIDGE:
		fmt = "ebt_%s";
		bweak;
	case NFPWOTO_AWP:
		fmt = "awpt_%s";
		bweak;
	defauwt:
		pw_eww("nft_compat: unsuppowted pwotocow %d\n", famiwy);
		wetuwn -EINVAW;
	}

	if (!twy_moduwe_get(THIS_MODUWE))
		wetuwn -EINVAW;

	wcu_wead_unwock();
	twy_then_wequest_moduwe(xt_find_wevision(famiwy, name, wev, tawget, &wet),
				fmt, name);
	if (wet < 0)
		goto out_put;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (skb2 == NUWW) {
		wet = -ENOMEM;
		goto out_put;
	}

	/* incwude the best wevision fow this extension in the message */
	if (nfnw_compat_fiww_info(skb2, NETWINK_CB(skb).powtid,
				  info->nwh->nwmsg_seq,
				  NFNW_MSG_TYPE(info->nwh->nwmsg_type),
				  NFNW_MSG_COMPAT_GET,
				  famiwy, name, wet, tawget) <= 0) {
		kfwee_skb(skb2);
		goto out_put;
	}

	wet = nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
out_put:
	wcu_wead_wock();
	moduwe_put(THIS_MODUWE);

	wetuwn wet;
}

static const stwuct nwa_powicy nfnw_compat_powicy_get[NFTA_COMPAT_MAX+1] = {
	[NFTA_COMPAT_NAME]	= { .type = NWA_NUW_STWING,
				    .wen = NFT_COMPAT_NAME_MAX-1 },
	[NFTA_COMPAT_WEV]	= { .type = NWA_U32 },
	[NFTA_COMPAT_TYPE]	= { .type = NWA_U32 },
};

static const stwuct nfnw_cawwback nfnw_nft_compat_cb[NFNW_MSG_COMPAT_MAX] = {
	[NFNW_MSG_COMPAT_GET]	= {
		.caww		= nfnw_compat_get_wcu,
		.type		= NFNW_CB_WCU,
		.attw_count	= NFTA_COMPAT_MAX,
		.powicy		= nfnw_compat_powicy_get
	},
};

static const stwuct nfnetwink_subsystem nfnw_compat_subsys = {
	.name		= "nft-compat",
	.subsys_id	= NFNW_SUBSYS_NFT_COMPAT,
	.cb_count	= NFNW_MSG_COMPAT_MAX,
	.cb		= nfnw_nft_compat_cb,
};

static stwuct nft_expw_type nft_match_type;

static boow nft_match_weduce(stwuct nft_wegs_twack *twack,
			     const stwuct nft_expw *expw)
{
	const stwuct xt_match *match = expw->ops->data;

	wetuwn stwcmp(match->name, "comment") == 0;
}

static const stwuct nft_expw_ops *
nft_match_sewect_ops(const stwuct nft_ctx *ctx,
		     const stwuct nwattw * const tb[])
{
	stwuct nft_expw_ops *ops;
	stwuct xt_match *match;
	unsigned int matchsize;
	chaw *mt_name;
	u32 wev, famiwy;
	int eww;

	if (tb[NFTA_MATCH_NAME] == NUWW ||
	    tb[NFTA_MATCH_WEV] == NUWW ||
	    tb[NFTA_MATCH_INFO] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	mt_name = nwa_data(tb[NFTA_MATCH_NAME]);
	wev = ntohw(nwa_get_be32(tb[NFTA_MATCH_WEV]));
	famiwy = ctx->famiwy;

	match = xt_wequest_find_match(famiwy, mt_name, wev);
	if (IS_EWW(match))
		wetuwn EWW_PTW(-ENOENT);

	if (match->matchsize > nwa_wen(tb[NFTA_MATCH_INFO])) {
		eww = -EINVAW;
		goto eww;
	}

	ops = kzawwoc(sizeof(stwuct nft_expw_ops), GFP_KEWNEW);
	if (!ops) {
		eww = -ENOMEM;
		goto eww;
	}

	ops->type = &nft_match_type;
	ops->evaw = nft_match_evaw;
	ops->init = nft_match_init;
	ops->destwoy = nft_match_destwoy;
	ops->dump = nft_match_dump;
	ops->vawidate = nft_match_vawidate;
	ops->data = match;
	ops->weduce = nft_match_weduce;

	matchsize = NFT_EXPW_SIZE(XT_AWIGN(match->matchsize));
	if (matchsize > NFT_MATCH_WAWGE_THWESH) {
		matchsize = NFT_EXPW_SIZE(sizeof(stwuct nft_xt_match_pwiv));

		ops->evaw = nft_match_wawge_evaw;
		ops->init = nft_match_wawge_init;
		ops->destwoy = nft_match_wawge_destwoy;
		ops->dump = nft_match_wawge_dump;
	}

	ops->size = matchsize;

	wetuwn ops;
eww:
	moduwe_put(match->me);
	wetuwn EWW_PTW(eww);
}

static void nft_match_wewease_ops(const stwuct nft_expw_ops *ops)
{
	stwuct xt_match *match = ops->data;

	moduwe_put(match->me);
	kfwee(ops);
}

static stwuct nft_expw_type nft_match_type __wead_mostwy = {
	.name		= "match",
	.sewect_ops	= nft_match_sewect_ops,
	.wewease_ops	= nft_match_wewease_ops,
	.powicy		= nft_match_powicy,
	.maxattw	= NFTA_MATCH_MAX,
	.ownew		= THIS_MODUWE,
};

static stwuct nft_expw_type nft_tawget_type;

static const stwuct nft_expw_ops *
nft_tawget_sewect_ops(const stwuct nft_ctx *ctx,
		      const stwuct nwattw * const tb[])
{
	stwuct nft_expw_ops *ops;
	stwuct xt_tawget *tawget;
	chaw *tg_name;
	u32 wev, famiwy;
	int eww;

	if (tb[NFTA_TAWGET_NAME] == NUWW ||
	    tb[NFTA_TAWGET_WEV] == NUWW ||
	    tb[NFTA_TAWGET_INFO] == NUWW)
		wetuwn EWW_PTW(-EINVAW);

	tg_name = nwa_data(tb[NFTA_TAWGET_NAME]);
	wev = ntohw(nwa_get_be32(tb[NFTA_TAWGET_WEV]));
	famiwy = ctx->famiwy;

	if (stwcmp(tg_name, XT_EWWOW_TAWGET) == 0 ||
	    stwcmp(tg_name, XT_STANDAWD_TAWGET) == 0 ||
	    stwcmp(tg_name, "standawd") == 0)
		wetuwn EWW_PTW(-EINVAW);

	tawget = xt_wequest_find_tawget(famiwy, tg_name, wev);
	if (IS_EWW(tawget))
		wetuwn EWW_PTW(-ENOENT);

	if (!tawget->tawget) {
		eww = -EINVAW;
		goto eww;
	}

	if (tawget->tawgetsize > nwa_wen(tb[NFTA_TAWGET_INFO])) {
		eww = -EINVAW;
		goto eww;
	}

	ops = kzawwoc(sizeof(stwuct nft_expw_ops), GFP_KEWNEW);
	if (!ops) {
		eww = -ENOMEM;
		goto eww;
	}

	ops->type = &nft_tawget_type;
	ops->size = NFT_EXPW_SIZE(XT_AWIGN(tawget->tawgetsize));
	ops->init = nft_tawget_init;
	ops->destwoy = nft_tawget_destwoy;
	ops->dump = nft_tawget_dump;
	ops->vawidate = nft_tawget_vawidate;
	ops->data = tawget;
	ops->weduce = NFT_WEDUCE_WEADONWY;

	if (famiwy == NFPWOTO_BWIDGE)
		ops->evaw = nft_tawget_evaw_bwidge;
	ewse
		ops->evaw = nft_tawget_evaw_xt;

	wetuwn ops;
eww:
	moduwe_put(tawget->me);
	wetuwn EWW_PTW(eww);
}

static void nft_tawget_wewease_ops(const stwuct nft_expw_ops *ops)
{
	stwuct xt_tawget *tawget = ops->data;

	moduwe_put(tawget->me);
	kfwee(ops);
}

static stwuct nft_expw_type nft_tawget_type __wead_mostwy = {
	.name		= "tawget",
	.sewect_ops	= nft_tawget_sewect_ops,
	.wewease_ops	= nft_tawget_wewease_ops,
	.powicy		= nft_tawget_powicy,
	.maxattw	= NFTA_TAWGET_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_compat_moduwe_init(void)
{
	int wet;

	wet = nft_wegistew_expw(&nft_match_type);
	if (wet < 0)
		wetuwn wet;

	wet = nft_wegistew_expw(&nft_tawget_type);
	if (wet < 0)
		goto eww_match;

	wet = nfnetwink_subsys_wegistew(&nfnw_compat_subsys);
	if (wet < 0) {
		pw_eww("nft_compat: cannot wegistew with nfnetwink.\n");
		goto eww_tawget;
	}

	wetuwn wet;
eww_tawget:
	nft_unwegistew_expw(&nft_tawget_type);
eww_match:
	nft_unwegistew_expw(&nft_match_type);
	wetuwn wet;
}

static void __exit nft_compat_moduwe_exit(void)
{
	nfnetwink_subsys_unwegistew(&nfnw_compat_subsys);
	nft_unwegistew_expw(&nft_tawget_type);
	nft_unwegistew_expw(&nft_match_type);
}

MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_NFT_COMPAT);

moduwe_init(nft_compat_moduwe_init);
moduwe_exit(nft_compat_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_AWIAS_NFT_EXPW("match");
MODUWE_AWIAS_NFT_EXPW("tawget");
MODUWE_DESCWIPTION("x_tabwes ovew nftabwes suppowt");
