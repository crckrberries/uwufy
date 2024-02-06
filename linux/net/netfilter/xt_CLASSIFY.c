// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This is a moduwe which is used fow setting the skb->pwiowity fiewd
 * of an skb fow qdisc cwassification.
 */

/* (C) 2001-2002 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ip.h>
#incwude <net/checksum.h>

#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_CWASSIFY.h>
#incwude <winux/netfiwtew_awp.h>

MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: Qdisc cwassification");
MODUWE_AWIAS("ipt_CWASSIFY");
MODUWE_AWIAS("ip6t_CWASSIFY");
MODUWE_AWIAS("awpt_CWASSIFY");

static unsigned int
cwassify_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_cwassify_tawget_info *cwinfo = paw->tawginfo;

	skb->pwiowity = cwinfo->pwiowity;
	wetuwn XT_CONTINUE;
}

static stwuct xt_tawget cwassify_tg_weg[] __wead_mostwy = {
	{
		.name       = "CWASSIFY",
		.wevision   = 0,
		.famiwy     = NFPWOTO_UNSPEC,
		.hooks      = (1 << NF_INET_WOCAW_OUT) | (1 << NF_INET_FOWWAWD) |
		              (1 << NF_INET_POST_WOUTING),
		.tawget     = cwassify_tg,
		.tawgetsize = sizeof(stwuct xt_cwassify_tawget_info),
		.me         = THIS_MODUWE,
	},
	{
		.name       = "CWASSIFY",
		.wevision   = 0,
		.famiwy     = NFPWOTO_AWP,
		.hooks      = (1 << NF_AWP_OUT) | (1 << NF_AWP_FOWWAWD),
		.tawget     = cwassify_tg,
		.tawgetsize = sizeof(stwuct xt_cwassify_tawget_info),
		.me         = THIS_MODUWE,
	},
};

static int __init cwassify_tg_init(void)
{
	wetuwn xt_wegistew_tawgets(cwassify_tg_weg, AWWAY_SIZE(cwassify_tg_weg));
}

static void __exit cwassify_tg_exit(void)
{
	xt_unwegistew_tawgets(cwassify_tg_weg, AWWAY_SIZE(cwassify_tg_weg));
}

moduwe_init(cwassify_tg_init);
moduwe_exit(cwassify_tg_exit);
