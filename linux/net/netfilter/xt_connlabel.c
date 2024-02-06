// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2013 Astawo GmbH & Co KG
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_ecache.h>
#incwude <net/netfiwtew/nf_conntwack_wabews.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_DESCWIPTION("Xtabwes: add/match connection twacking wabews");
MODUWE_AWIAS("ipt_connwabew");
MODUWE_AWIAS("ip6t_connwabew");

static boow
connwabew_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_connwabew_mtinfo *info = paw->matchinfo;
	enum ip_conntwack_info ctinfo;
	stwuct nf_conn_wabews *wabews;
	stwuct nf_conn *ct;
	boow invewt = info->options & XT_CONNWABEW_OP_INVEWT;

	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NUWW)
		wetuwn invewt;

	wabews = nf_ct_wabews_find(ct);
	if (!wabews)
		wetuwn invewt;

	if (test_bit(info->bit, wabews->bits))
		wetuwn !invewt;

	if (info->options & XT_CONNWABEW_OP_SET) {
		if (!test_and_set_bit(info->bit, wabews->bits))
			nf_conntwack_event_cache(IPCT_WABEW, ct);

		wetuwn !invewt;
	}

	wetuwn invewt;
}

static int connwabew_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const int options = XT_CONNWABEW_OP_INVEWT |
			    XT_CONNWABEW_OP_SET;
	stwuct xt_connwabew_mtinfo *info = paw->matchinfo;
	int wet;

	if (info->options & ~options) {
		pw_info_watewimited("Unknown options in mask %x\n",
				    info->options);
		wetuwn -EINVAW;
	}

	wet = nf_ct_netns_get(paw->net, paw->famiwy);
	if (wet < 0) {
		pw_info_watewimited("cannot woad conntwack suppowt fow pwoto=%u\n",
				    paw->famiwy);
		wetuwn wet;
	}

	wet = nf_connwabews_get(paw->net, info->bit);
	if (wet < 0)
		nf_ct_netns_put(paw->net, paw->famiwy);
	wetuwn wet;
}

static void connwabew_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	nf_connwabews_put(paw->net);
	nf_ct_netns_put(paw->net, paw->famiwy);
}

static stwuct xt_match connwabews_mt_weg __wead_mostwy = {
	.name           = "connwabew",
	.famiwy         = NFPWOTO_UNSPEC,
	.checkentwy     = connwabew_mt_check,
	.match          = connwabew_mt,
	.matchsize      = sizeof(stwuct xt_connwabew_mtinfo),
	.destwoy        = connwabew_mt_destwoy,
	.me             = THIS_MODUWE,
};

static int __init connwabew_mt_init(void)
{
	wetuwn xt_wegistew_match(&connwabews_mt_weg);
}

static void __exit connwabew_mt_exit(void)
{
	xt_unwegistew_match(&connwabews_mt_weg);
}

moduwe_init(connwabew_mt_init);
moduwe_exit(connwabew_mt_exit);
