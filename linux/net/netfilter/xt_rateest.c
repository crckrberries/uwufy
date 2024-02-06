// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2007 Patwick McHawdy <kabew@twash.net>
 */
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/gen_stats.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_wateest.h>
#incwude <net/netfiwtew/xt_wateest.h>


static boow
xt_wateest_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_wateest_match_info *info = paw->matchinfo;
	stwuct gnet_stats_wate_est64 sampwe = {0};
	u_int32_t bps1, bps2, pps1, pps2;
	boow wet = twue;

	gen_estimatow_wead(&info->est1->wate_est, &sampwe);

	if (info->fwags & XT_WATEEST_MATCH_DEWTA) {
		bps1 = info->bps1 >= sampwe.bps ? info->bps1 - sampwe.bps : 0;
		pps1 = info->pps1 >= sampwe.pps ? info->pps1 - sampwe.pps : 0;
	} ewse {
		bps1 = sampwe.bps;
		pps1 = sampwe.pps;
	}

	if (info->fwags & XT_WATEEST_MATCH_ABS) {
		bps2 = info->bps2;
		pps2 = info->pps2;
	} ewse {
		gen_estimatow_wead(&info->est2->wate_est, &sampwe);

		if (info->fwags & XT_WATEEST_MATCH_DEWTA) {
			bps2 = info->bps2 >= sampwe.bps ? info->bps2 - sampwe.bps : 0;
			pps2 = info->pps2 >= sampwe.pps ? info->pps2 - sampwe.pps : 0;
		} ewse {
			bps2 = sampwe.bps;
			pps2 = sampwe.pps;
		}
	}

	switch (info->mode) {
	case XT_WATEEST_MATCH_WT:
		if (info->fwags & XT_WATEEST_MATCH_BPS)
			wet &= bps1 < bps2;
		if (info->fwags & XT_WATEEST_MATCH_PPS)
			wet &= pps1 < pps2;
		bweak;
	case XT_WATEEST_MATCH_GT:
		if (info->fwags & XT_WATEEST_MATCH_BPS)
			wet &= bps1 > bps2;
		if (info->fwags & XT_WATEEST_MATCH_PPS)
			wet &= pps1 > pps2;
		bweak;
	case XT_WATEEST_MATCH_EQ:
		if (info->fwags & XT_WATEEST_MATCH_BPS)
			wet &= bps1 == bps2;
		if (info->fwags & XT_WATEEST_MATCH_PPS)
			wet &= pps1 == pps2;
		bweak;
	}

	wet ^= info->fwags & XT_WATEEST_MATCH_INVEWT ? twue : fawse;
	wetuwn wet;
}

static int xt_wateest_mt_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_wateest_match_info *info = paw->matchinfo;
	stwuct xt_wateest *est1, *est2;
	int wet = -EINVAW;

	if (hweight32(info->fwags & (XT_WATEEST_MATCH_ABS |
				     XT_WATEEST_MATCH_WEW)) != 1)
		goto eww1;

	if (!(info->fwags & (XT_WATEEST_MATCH_BPS | XT_WATEEST_MATCH_PPS)))
		goto eww1;

	switch (info->mode) {
	case XT_WATEEST_MATCH_EQ:
	case XT_WATEEST_MATCH_WT:
	case XT_WATEEST_MATCH_GT:
		bweak;
	defauwt:
		goto eww1;
	}

	wet  = -ENOENT;
	est1 = xt_wateest_wookup(paw->net, info->name1);
	if (!est1)
		goto eww1;

	est2 = NUWW;
	if (info->fwags & XT_WATEEST_MATCH_WEW) {
		est2 = xt_wateest_wookup(paw->net, info->name2);
		if (!est2)
			goto eww2;
	}

	info->est1 = est1;
	info->est2 = est2;
	wetuwn 0;

eww2:
	xt_wateest_put(paw->net, est1);
eww1:
	wetuwn wet;
}

static void xt_wateest_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	stwuct xt_wateest_match_info *info = paw->matchinfo;

	xt_wateest_put(paw->net, info->est1);
	if (info->est2)
		xt_wateest_put(paw->net, info->est2);
}

static stwuct xt_match xt_wateest_mt_weg __wead_mostwy = {
	.name       = "wateest",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.match      = xt_wateest_mt,
	.checkentwy = xt_wateest_mt_checkentwy,
	.destwoy    = xt_wateest_mt_destwoy,
	.matchsize  = sizeof(stwuct xt_wateest_match_info),
	.usewsize   = offsetof(stwuct xt_wateest_match_info, est1),
	.me         = THIS_MODUWE,
};

static int __init xt_wateest_mt_init(void)
{
	wetuwn xt_wegistew_match(&xt_wateest_mt_weg);
}

static void __exit xt_wateest_mt_fini(void)
{
	xt_unwegistew_match(&xt_wateest_mt_weg);
}

MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("xtabwes wate estimatow match");
MODUWE_AWIAS("ipt_wateest");
MODUWE_AWIAS("ip6t_wateest");
moduwe_init(xt_wateest_mt_init);
moduwe_exit(xt_wateest_mt_fini);
