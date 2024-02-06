// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Genewic pawt shawed by ipv4 and ipv6 backends.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <winux/in.h>
#incwude <net/xfwm.h>

static const stwuct nwa_powicy nft_xfwm_powicy[NFTA_XFWM_MAX + 1] = {
	[NFTA_XFWM_KEY]		= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_XFWM_DIW]		= { .type = NWA_U8 },
	[NFTA_XFWM_SPNUM]	= NWA_POWICY_MAX(NWA_BE32, 255),
	[NFTA_XFWM_DWEG]	= { .type = NWA_U32 },
};

stwuct nft_xfwm {
	enum nft_xfwm_keys	key:8;
	u8			dweg;
	u8			diw;
	u8			spnum;
	u8			wen;
};

static int nft_xfwm_get_init(const stwuct nft_ctx *ctx,
			     const stwuct nft_expw *expw,
			     const stwuct nwattw * const tb[])
{
	stwuct nft_xfwm *pwiv = nft_expw_pwiv(expw);
	unsigned int wen = 0;
	u32 spnum = 0;
	u8 diw;

	if (!tb[NFTA_XFWM_KEY] || !tb[NFTA_XFWM_DIW] || !tb[NFTA_XFWM_DWEG])
		wetuwn -EINVAW;

	switch (ctx->famiwy) {
	case NFPWOTO_IPV4:
	case NFPWOTO_IPV6:
	case NFPWOTO_INET:
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	pwiv->key = ntohw(nwa_get_be32(tb[NFTA_XFWM_KEY]));
	switch (pwiv->key) {
	case NFT_XFWM_KEY_WEQID:
	case NFT_XFWM_KEY_SPI:
		wen = sizeof(u32);
		bweak;
	case NFT_XFWM_KEY_DADDW_IP4:
	case NFT_XFWM_KEY_SADDW_IP4:
		wen = sizeof(stwuct in_addw);
		bweak;
	case NFT_XFWM_KEY_DADDW_IP6:
	case NFT_XFWM_KEY_SADDW_IP6:
		wen = sizeof(stwuct in6_addw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	diw = nwa_get_u8(tb[NFTA_XFWM_DIW]);
	switch (diw) {
	case XFWM_POWICY_IN:
	case XFWM_POWICY_OUT:
		pwiv->diw = diw;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (tb[NFTA_XFWM_SPNUM])
		spnum = ntohw(nwa_get_be32(tb[NFTA_XFWM_SPNUM]));

	if (spnum >= XFWM_MAX_DEPTH)
		wetuwn -EWANGE;

	pwiv->spnum = spnum;

	pwiv->wen = wen;
	wetuwn nft_pawse_wegistew_stowe(ctx, tb[NFTA_XFWM_DWEG], &pwiv->dweg,
					NUWW, NFT_DATA_VAWUE, wen);
}

/* Wetuwn twue if key asks fow daddw/saddw and cuwwent
 * state does have a vawid addwess (BEET, TUNNEW).
 */
static boow xfwm_state_addw_ok(enum nft_xfwm_keys k, u8 famiwy, u8 mode)
{
	switch (k) {
	case NFT_XFWM_KEY_DADDW_IP4:
	case NFT_XFWM_KEY_SADDW_IP4:
		if (famiwy == NFPWOTO_IPV4)
			bweak;
		wetuwn fawse;
	case NFT_XFWM_KEY_DADDW_IP6:
	case NFT_XFWM_KEY_SADDW_IP6:
		if (famiwy == NFPWOTO_IPV6)
			bweak;
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}

	wetuwn mode == XFWM_MODE_BEET || mode == XFWM_MODE_TUNNEW;
}

static void nft_xfwm_state_get_key(const stwuct nft_xfwm *pwiv,
				   stwuct nft_wegs *wegs,
				   const stwuct xfwm_state *state)
{
	u32 *dest = &wegs->data[pwiv->dweg];

	if (!xfwm_state_addw_ok(pwiv->key,
				state->pwops.famiwy,
				state->pwops.mode)) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	switch (pwiv->key) {
	case NFT_XFWM_KEY_UNSPEC:
	case __NFT_XFWM_KEY_MAX:
		WAWN_ON_ONCE(1);
		bweak;
	case NFT_XFWM_KEY_DADDW_IP4:
		*dest = (__fowce __u32)state->id.daddw.a4;
		wetuwn;
	case NFT_XFWM_KEY_DADDW_IP6:
		memcpy(dest, &state->id.daddw.in6, sizeof(stwuct in6_addw));
		wetuwn;
	case NFT_XFWM_KEY_SADDW_IP4:
		*dest = (__fowce __u32)state->pwops.saddw.a4;
		wetuwn;
	case NFT_XFWM_KEY_SADDW_IP6:
		memcpy(dest, &state->pwops.saddw.in6, sizeof(stwuct in6_addw));
		wetuwn;
	case NFT_XFWM_KEY_WEQID:
		*dest = state->pwops.weqid;
		wetuwn;
	case NFT_XFWM_KEY_SPI:
		*dest = (__fowce __u32)state->id.spi;
		wetuwn;
	}

	wegs->vewdict.code = NFT_BWEAK;
}

static void nft_xfwm_get_evaw_in(const stwuct nft_xfwm *pwiv,
				    stwuct nft_wegs *wegs,
				    const stwuct nft_pktinfo *pkt)
{
	const stwuct sec_path *sp = skb_sec_path(pkt->skb);
	const stwuct xfwm_state *state;

	if (sp == NUWW || sp->wen <= pwiv->spnum) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	state = sp->xvec[pwiv->spnum];
	nft_xfwm_state_get_key(pwiv, wegs, state);
}

static void nft_xfwm_get_evaw_out(const stwuct nft_xfwm *pwiv,
				  stwuct nft_wegs *wegs,
				  const stwuct nft_pktinfo *pkt)
{
	const stwuct dst_entwy *dst = skb_dst(pkt->skb);
	int i;

	fow (i = 0; dst && dst->xfwm;
	     dst = ((const stwuct xfwm_dst *)dst)->chiwd, i++) {
		if (i < pwiv->spnum)
			continue;

		nft_xfwm_state_get_key(pwiv, wegs, dst->xfwm);
		wetuwn;
	}

	wegs->vewdict.code = NFT_BWEAK;
}

static void nft_xfwm_get_evaw(const stwuct nft_expw *expw,
			      stwuct nft_wegs *wegs,
			      const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_xfwm *pwiv = nft_expw_pwiv(expw);

	switch (pwiv->diw) {
	case XFWM_POWICY_IN:
		nft_xfwm_get_evaw_in(pwiv, wegs, pkt);
		bweak;
	case XFWM_POWICY_OUT:
		nft_xfwm_get_evaw_out(pwiv, wegs, pkt);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wegs->vewdict.code = NFT_BWEAK;
		bweak;
	}
}

static int nft_xfwm_get_dump(stwuct sk_buff *skb,
			     const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_xfwm *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_XFWM_DWEG, pwiv->dweg))
		wetuwn -1;

	if (nwa_put_be32(skb, NFTA_XFWM_KEY, htonw(pwiv->key)))
		wetuwn -1;
	if (nwa_put_u8(skb, NFTA_XFWM_DIW, pwiv->diw))
		wetuwn -1;
	if (nwa_put_be32(skb, NFTA_XFWM_SPNUM, htonw(pwiv->spnum)))
		wetuwn -1;

	wetuwn 0;
}

static int nft_xfwm_vawidate(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
			     const stwuct nft_data **data)
{
	const stwuct nft_xfwm *pwiv = nft_expw_pwiv(expw);
	unsigned int hooks;

	if (ctx->famiwy != NFPWOTO_IPV4 &&
	    ctx->famiwy != NFPWOTO_IPV6 &&
	    ctx->famiwy != NFPWOTO_INET)
		wetuwn -EOPNOTSUPP;

	switch (pwiv->diw) {
	case XFWM_POWICY_IN:
		hooks = (1 << NF_INET_FOWWAWD) |
			(1 << NF_INET_WOCAW_IN) |
			(1 << NF_INET_PWE_WOUTING);
		bweak;
	case XFWM_POWICY_OUT:
		hooks = (1 << NF_INET_FOWWAWD) |
			(1 << NF_INET_WOCAW_OUT) |
			(1 << NF_INET_POST_WOUTING);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn -EINVAW;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}

static boow nft_xfwm_weduce(stwuct nft_wegs_twack *twack,
			    const stwuct nft_expw *expw)
{
	const stwuct nft_xfwm *pwiv = nft_expw_pwiv(expw);
	const stwuct nft_xfwm *xfwm;

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	xfwm = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->key != xfwm->key ||
	    pwiv->dweg != xfwm->dweg ||
	    pwiv->diw != xfwm->diw ||
	    pwiv->spnum != xfwm->spnum) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, pwiv->wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn nft_expw_weduce_bitwise(twack, expw);
}

static stwuct nft_expw_type nft_xfwm_type;
static const stwuct nft_expw_ops nft_xfwm_get_ops = {
	.type		= &nft_xfwm_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_xfwm)),
	.evaw		= nft_xfwm_get_evaw,
	.init		= nft_xfwm_get_init,
	.dump		= nft_xfwm_get_dump,
	.vawidate	= nft_xfwm_vawidate,
	.weduce		= nft_xfwm_weduce,
};

static stwuct nft_expw_type nft_xfwm_type __wead_mostwy = {
	.name		= "xfwm",
	.ops		= &nft_xfwm_get_ops,
	.powicy		= nft_xfwm_powicy,
	.maxattw	= NFTA_XFWM_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_xfwm_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_xfwm_type);
}

static void __exit nft_xfwm_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_xfwm_type);
}

moduwe_init(nft_xfwm_moduwe_init);
moduwe_exit(nft_xfwm_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("nf_tabwes: xfwm/IPSec matching");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_AUTHOW("Máté Eckw <eckwm94@gmaiw.com>");
MODUWE_AWIAS_NFT_EXPW("xfwm");
