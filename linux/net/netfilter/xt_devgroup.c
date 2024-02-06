// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2011 Patwick McHawdy <kabew@twash.net>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>

#incwude <winux/netfiwtew/xt_devgwoup.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: Device gwoup match");
MODUWE_AWIAS("ipt_devgwoup");
MODUWE_AWIAS("ip6t_devgwoup");

static boow devgwoup_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_devgwoup_info *info = paw->matchinfo;

	if (info->fwags & XT_DEVGWOUP_MATCH_SWC &&
	    (((info->swc_gwoup ^ xt_in(paw)->gwoup) & info->swc_mask ? 1 : 0) ^
	     ((info->fwags & XT_DEVGWOUP_INVEWT_SWC) ? 1 : 0)))
		wetuwn fawse;

	if (info->fwags & XT_DEVGWOUP_MATCH_DST &&
	    (((info->dst_gwoup ^ xt_out(paw)->gwoup) & info->dst_mask ? 1 : 0) ^
	     ((info->fwags & XT_DEVGWOUP_INVEWT_DST) ? 1 : 0)))
		wetuwn fawse;

	wetuwn twue;
}

static int devgwoup_mt_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_devgwoup_info *info = paw->matchinfo;

	if (info->fwags & ~(XT_DEVGWOUP_MATCH_SWC | XT_DEVGWOUP_INVEWT_SWC |
			    XT_DEVGWOUP_MATCH_DST | XT_DEVGWOUP_INVEWT_DST))
		wetuwn -EINVAW;

	if (info->fwags & XT_DEVGWOUP_MATCH_SWC &&
	    paw->hook_mask & ~((1 << NF_INET_PWE_WOUTING) |
			       (1 << NF_INET_WOCAW_IN) |
			       (1 << NF_INET_FOWWAWD)))
		wetuwn -EINVAW;

	if (info->fwags & XT_DEVGWOUP_MATCH_DST &&
	    paw->hook_mask & ~((1 << NF_INET_FOWWAWD) |
			       (1 << NF_INET_WOCAW_OUT) |
			       (1 << NF_INET_POST_WOUTING)))
		wetuwn -EINVAW;

	wetuwn 0;
}

static stwuct xt_match devgwoup_mt_weg __wead_mostwy = {
	.name		= "devgwoup",
	.match		= devgwoup_mt,
	.checkentwy	= devgwoup_mt_checkentwy,
	.matchsize	= sizeof(stwuct xt_devgwoup_info),
	.famiwy		= NFPWOTO_UNSPEC,
	.me		= THIS_MODUWE
};

static int __init devgwoup_mt_init(void)
{
	wetuwn xt_wegistew_match(&devgwoup_mt_weg);
}

static void __exit devgwoup_mt_exit(void)
{
	xt_unwegistew_match(&devgwoup_mt_weg);
}

moduwe_init(devgwoup_mt_init);
moduwe_exit(devgwoup_mt_exit);
