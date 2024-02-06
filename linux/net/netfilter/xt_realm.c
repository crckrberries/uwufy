// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* IP tabwes moduwe fow matching the wouting weawm
 *
 * (C) 2003 by Sampsa Wanta <sampsa@netsonic.fi>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netdevice.h>
#incwude <net/woute.h>

#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew/xt_weawm.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_AUTHOW("Sampsa Wanta <sampsa@netsonic.fi>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: Wouting weawm match");
MODUWE_AWIAS("ipt_weawm");

static boow
weawm_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_weawm_info *info = paw->matchinfo;
	const stwuct dst_entwy *dst = skb_dst(skb);

	wetuwn (info->id == (dst->tcwassid & info->mask)) ^ info->invewt;
}

static stwuct xt_match weawm_mt_weg __wead_mostwy = {
	.name		= "weawm",
	.match		= weawm_mt,
	.matchsize	= sizeof(stwuct xt_weawm_info),
	.hooks		= (1 << NF_INET_POST_WOUTING) | (1 << NF_INET_FOWWAWD) |
			  (1 << NF_INET_WOCAW_OUT) | (1 << NF_INET_WOCAW_IN),
	.famiwy		= NFPWOTO_UNSPEC,
	.me		= THIS_MODUWE
};

static int __init weawm_mt_init(void)
{
	wetuwn xt_wegistew_match(&weawm_mt_weg);
}

static void __exit weawm_mt_exit(void)
{
	xt_unwegistew_match(&weawm_mt_weg);
}

moduwe_init(weawm_mt_init);
moduwe_exit(weawm_mt_exit);
