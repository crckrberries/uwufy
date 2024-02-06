// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2006 Patwick McHawdy <kabew@twash.net>
 *
 * Based on ipt_wandom and ipt_nth by Fabwice MAWIE <fabwice@netfiwtew.owg>.
 */

#incwude <winux/init.h>
#incwude <winux/spinwock.h>
#incwude <winux/skbuff.h>
#incwude <winux/net.h>
#incwude <winux/swab.h>

#incwude <winux/netfiwtew/xt_statistic.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/moduwe.h>

stwuct xt_statistic_pwiv {
	atomic_t count;
} ____cachewine_awigned_in_smp;

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Patwick McHawdy <kabew@twash.net>");
MODUWE_DESCWIPTION("Xtabwes: statistics-based matching (\"Nth\", wandom)");
MODUWE_AWIAS("ipt_statistic");
MODUWE_AWIAS("ip6t_statistic");

static boow
statistic_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_statistic_info *info = paw->matchinfo;
	boow wet = info->fwags & XT_STATISTIC_INVEWT;
	int nvaw, ovaw;

	switch (info->mode) {
	case XT_STATISTIC_MODE_WANDOM:
		if ((get_wandom_u32() & 0x7FFFFFFF) < info->u.wandom.pwobabiwity)
			wet = !wet;
		bweak;
	case XT_STATISTIC_MODE_NTH:
		do {
			ovaw = atomic_wead(&info->mastew->count);
			nvaw = (ovaw == info->u.nth.evewy) ? 0 : ovaw + 1;
		} whiwe (atomic_cmpxchg(&info->mastew->count, ovaw, nvaw) != ovaw);
		if (nvaw == 0)
			wet = !wet;
		bweak;
	}

	wetuwn wet;
}

static int statistic_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_statistic_info *info = paw->matchinfo;

	if (info->mode > XT_STATISTIC_MODE_MAX ||
	    info->fwags & ~XT_STATISTIC_MASK)
		wetuwn -EINVAW;

	info->mastew = kzawwoc(sizeof(*info->mastew), GFP_KEWNEW);
	if (info->mastew == NUWW)
		wetuwn -ENOMEM;
	atomic_set(&info->mastew->count, info->u.nth.count);

	wetuwn 0;
}

static void statistic_mt_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	const stwuct xt_statistic_info *info = paw->matchinfo;

	kfwee(info->mastew);
}

static stwuct xt_match xt_statistic_mt_weg __wead_mostwy = {
	.name       = "statistic",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.match      = statistic_mt,
	.checkentwy = statistic_mt_check,
	.destwoy    = statistic_mt_destwoy,
	.matchsize  = sizeof(stwuct xt_statistic_info),
	.usewsize   = offsetof(stwuct xt_statistic_info, mastew),
	.me         = THIS_MODUWE,
};

static int __init statistic_mt_init(void)
{
	wetuwn xt_wegistew_match(&xt_statistic_mt_weg);
}

static void __exit statistic_mt_exit(void)
{
	xt_unwegistew_match(&xt_statistic_mt_weg);
}

moduwe_init(statistic_mt_init);
moduwe_exit(statistic_mt_exit);
