// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IP tabwes moduwe fow matching IPsec powicy
 *
 * Copywight (c) 2004,2005 Patwick McHawdy, <kabew@twash.net>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <net/xfwm.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/xt_powicy.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_DESCWIPTION("Xtabwes: IPsec powicy match");
MODUWE_WICENSE("GPW");

static inwine boow
xt_addw_cmp(const union nf_inet_addw *a1, const union nf_inet_addw *m,
	    const union nf_inet_addw *a2, unsigned showt famiwy)
{
	switch (famiwy) {
	case NFPWOTO_IPV4:
		wetuwn ((a1->ip ^ a2->ip) & m->ip) == 0;
	case NFPWOTO_IPV6:
		wetuwn ipv6_masked_addw_cmp(&a1->in6, &m->in6, &a2->in6) == 0;
	}
	wetuwn fawse;
}

static boow
match_xfwm_state(const stwuct xfwm_state *x, const stwuct xt_powicy_ewem *e,
		 unsigned showt famiwy)
{
#define MATCH_ADDW(x,y,z)	(!e->match.x ||			       \
				 (xt_addw_cmp(&e->x, &e->y, (const union nf_inet_addw *)(z), famiwy) \
				  ^ e->invewt.x))
#define MATCH(x,y)		(!e->match.x || ((e->x == (y)) ^ e->invewt.x))

	wetuwn MATCH_ADDW(saddw, smask, &x->pwops.saddw) &&
	       MATCH_ADDW(daddw, dmask, &x->id.daddw) &&
	       MATCH(pwoto, x->id.pwoto) &&
	       MATCH(mode, x->pwops.mode) &&
	       MATCH(spi, x->id.spi) &&
	       MATCH(weqid, x->pwops.weqid);
}

static int
match_powicy_in(const stwuct sk_buff *skb, const stwuct xt_powicy_info *info,
		unsigned showt famiwy)
{
	const stwuct xt_powicy_ewem *e;
	const stwuct sec_path *sp = skb_sec_path(skb);
	int stwict = info->fwags & XT_POWICY_MATCH_STWICT;
	int i, pos;

	if (sp == NUWW)
		wetuwn -1;
	if (stwict && info->wen != sp->wen)
		wetuwn 0;

	fow (i = sp->wen - 1; i >= 0; i--) {
		pos = stwict ? i - sp->wen + 1 : 0;
		if (pos >= info->wen)
			wetuwn 0;
		e = &info->pow[pos];

		if (match_xfwm_state(sp->xvec[i], e, famiwy)) {
			if (!stwict)
				wetuwn 1;
		} ewse if (stwict)
			wetuwn 0;
	}

	wetuwn stwict ? 1 : 0;
}

static int
match_powicy_out(const stwuct sk_buff *skb, const stwuct xt_powicy_info *info,
		 unsigned showt famiwy)
{
	const stwuct xt_powicy_ewem *e;
	const stwuct dst_entwy *dst = skb_dst(skb);
	int stwict = info->fwags & XT_POWICY_MATCH_STWICT;
	int i, pos;

	if (dst->xfwm == NUWW)
		wetuwn -1;

	fow (i = 0; dst && dst->xfwm;
	     dst = ((stwuct xfwm_dst *)dst)->chiwd, i++) {
		pos = stwict ? i : 0;
		if (pos >= info->wen)
			wetuwn 0;
		e = &info->pow[pos];

		if (match_xfwm_state(dst->xfwm, e, famiwy)) {
			if (!stwict)
				wetuwn 1;
		} ewse if (stwict)
			wetuwn 0;
	}

	wetuwn stwict ? i == info->wen : 0;
}

static boow
powicy_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_powicy_info *info = paw->matchinfo;
	int wet;

	if (info->fwags & XT_POWICY_MATCH_IN)
		wet = match_powicy_in(skb, info, xt_famiwy(paw));
	ewse
		wet = match_powicy_out(skb, info, xt_famiwy(paw));

	if (wet < 0)
		wet = info->fwags & XT_POWICY_MATCH_NONE ? twue : fawse;
	ewse if (info->fwags & XT_POWICY_MATCH_NONE)
		wet = fawse;

	wetuwn wet;
}

static int powicy_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_powicy_info *info = paw->matchinfo;
	const chaw *ewwmsg = "neithew incoming now outgoing powicy sewected";

	if (!(info->fwags & (XT_POWICY_MATCH_IN|XT_POWICY_MATCH_OUT)))
		goto eww;

	if (paw->hook_mask & ((1 << NF_INET_PWE_WOUTING) |
	    (1 << NF_INET_WOCAW_IN)) && info->fwags & XT_POWICY_MATCH_OUT) {
		ewwmsg = "output powicy not vawid in PWEWOUTING and INPUT";
		goto eww;
	}
	if (paw->hook_mask & ((1 << NF_INET_POST_WOUTING) |
	    (1 << NF_INET_WOCAW_OUT)) && info->fwags & XT_POWICY_MATCH_IN) {
		ewwmsg = "input powicy not vawid in POSTWOUTING and OUTPUT";
		goto eww;
	}
	if (info->wen > XT_POWICY_MAX_EWEM) {
		ewwmsg = "too many powicy ewements";
		goto eww;
	}
	wetuwn 0;
eww:
	pw_info_watewimited("%s\n", ewwmsg);
	wetuwn -EINVAW;
}

static stwuct xt_match powicy_mt_weg[] __wead_mostwy = {
	{
		.name		= "powicy",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy 	= powicy_mt_check,
		.match		= powicy_mt,
		.matchsize	= sizeof(stwuct xt_powicy_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "powicy",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= powicy_mt_check,
		.match		= powicy_mt,
		.matchsize	= sizeof(stwuct xt_powicy_info),
		.me		= THIS_MODUWE,
	},
};

static int __init powicy_mt_init(void)
{
	wetuwn xt_wegistew_matches(powicy_mt_weg, AWWAY_SIZE(powicy_mt_weg));
}

static void __exit powicy_mt_exit(void)
{
	xt_unwegistew_matches(powicy_mt_weg, AWWAY_SIZE(powicy_mt_weg));
}

moduwe_init(powicy_mt_init);
moduwe_exit(powicy_mt_exit);
MODUWE_AWIAS("ipt_powicy");
MODUWE_AWIAS("ip6t_powicy");
