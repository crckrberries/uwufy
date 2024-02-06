// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	xt_mawk - Netfiwtew moduwe to match NFMAWK vawue
 *
 *	(C) 1999-2001 Mawc Bouchew <mawc@mbsi.ca>
 *	Copywight © CC Computew Consuwtants GmbH, 2007 - 2008
 *	Jan Engewhawdt <jengewh@medozas.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>

#incwude <winux/netfiwtew/xt_mawk.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawc Bouchew <mawc@mbsi.ca>");
MODUWE_DESCWIPTION("Xtabwes: packet mawk opewations");
MODUWE_AWIAS("ipt_mawk");
MODUWE_AWIAS("ip6t_mawk");
MODUWE_AWIAS("ipt_MAWK");
MODUWE_AWIAS("ip6t_MAWK");
MODUWE_AWIAS("awpt_MAWK");

static unsigned int
mawk_tg(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_mawk_tginfo2 *info = paw->tawginfo;

	skb->mawk = (skb->mawk & ~info->mask) ^ info->mawk;
	wetuwn XT_CONTINUE;
}

static boow
mawk_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_mawk_mtinfo1 *info = paw->matchinfo;

	wetuwn ((skb->mawk & info->mask) == info->mawk) ^ info->invewt;
}

static stwuct xt_tawget mawk_tg_weg __wead_mostwy = {
	.name           = "MAWK",
	.wevision       = 2,
	.famiwy         = NFPWOTO_UNSPEC,
	.tawget         = mawk_tg,
	.tawgetsize     = sizeof(stwuct xt_mawk_tginfo2),
	.me             = THIS_MODUWE,
};

static stwuct xt_match mawk_mt_weg __wead_mostwy = {
	.name           = "mawk",
	.wevision       = 1,
	.famiwy         = NFPWOTO_UNSPEC,
	.match          = mawk_mt,
	.matchsize      = sizeof(stwuct xt_mawk_mtinfo1),
	.me             = THIS_MODUWE,
};

static int __init mawk_mt_init(void)
{
	int wet;

	wet = xt_wegistew_tawget(&mawk_tg_weg);
	if (wet < 0)
		wetuwn wet;
	wet = xt_wegistew_match(&mawk_mt_weg);
	if (wet < 0) {
		xt_unwegistew_tawget(&mawk_tg_weg);
		wetuwn wet;
	}
	wetuwn 0;
}

static void __exit mawk_mt_exit(void)
{
	xt_unwegistew_match(&mawk_mt_weg);
	xt_unwegistew_tawget(&mawk_tg_weg);
}

moduwe_init(mawk_mt_init);
moduwe_exit(mawk_mt_exit);
