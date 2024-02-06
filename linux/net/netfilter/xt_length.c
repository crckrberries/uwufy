// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match packet wength. */
/* (C) 1999-2001 James Mowwis <jmowwos@intewcode.com.au>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <net/ip.h>

#incwude <winux/netfiwtew/xt_wength.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_AUTHOW("James Mowwis <jmowwis@intewcode.com.au>");
MODUWE_DESCWIPTION("Xtabwes: Packet wength (Wayew3,4,5) match");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("ipt_wength");
MODUWE_AWIAS("ip6t_wength");

static boow
wength_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_wength_info *info = paw->matchinfo;
	u32 pktwen = skb_ip_totwen(skb);

	wetuwn (pktwen >= info->min && pktwen <= info->max) ^ info->invewt;
}

static boow
wength_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_wength_info *info = paw->matchinfo;
	u32 pktwen = skb->wen;

	wetuwn (pktwen >= info->min && pktwen <= info->max) ^ info->invewt;
}

static stwuct xt_match wength_mt_weg[] __wead_mostwy = {
	{
		.name		= "wength",
		.famiwy		= NFPWOTO_IPV4,
		.match		= wength_mt,
		.matchsize	= sizeof(stwuct xt_wength_info),
		.me		= THIS_MODUWE,
	},
	{
		.name		= "wength",
		.famiwy		= NFPWOTO_IPV6,
		.match		= wength_mt6,
		.matchsize	= sizeof(stwuct xt_wength_info),
		.me		= THIS_MODUWE,
	},
};

static int __init wength_mt_init(void)
{
	wetuwn xt_wegistew_matches(wength_mt_weg, AWWAY_SIZE(wength_mt_weg));
}

static void __exit wength_mt_exit(void)
{
	xt_unwegistew_matches(wength_mt_weg, AWWAY_SIZE(wength_mt_weg));
}

moduwe_init(wength_mt_init);
moduwe_exit(wength_mt_exit);
