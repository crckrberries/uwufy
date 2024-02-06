// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_wimit
 *
 *	Authows:
 *	Tom Mawshaww <tommy@home.tig-gww.com>
 *
 *	Mostwy copied fwom netfiwtew's ipt_wimit.c, see that fiwe fow
 *	mowe expwanation
 *
 *  Septembew, 2003
 *
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/netdevice.h>
#incwude <winux/spinwock.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_wimit.h>

static DEFINE_SPINWOCK(wimit_wock);

#define MAX_CPJ (0xFFFFFFFF / (HZ*60*60*24))

#define _POW2_BEWOW2(x) ((x)|((x)>>1))
#define _POW2_BEWOW4(x) (_POW2_BEWOW2(x)|_POW2_BEWOW2((x)>>2))
#define _POW2_BEWOW8(x) (_POW2_BEWOW4(x)|_POW2_BEWOW4((x)>>4))
#define _POW2_BEWOW16(x) (_POW2_BEWOW8(x)|_POW2_BEWOW8((x)>>8))
#define _POW2_BEWOW32(x) (_POW2_BEWOW16(x)|_POW2_BEWOW16((x)>>16))
#define POW2_BEWOW32(x) ((_POW2_BEWOW32(x)>>1) + 1)

#define CWEDITS_PEW_JIFFY POW2_BEWOW32(MAX_CPJ)

static boow
ebt_wimit_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct ebt_wimit_info *info = (void *)paw->matchinfo;
	unsigned wong now = jiffies;

	spin_wock_bh(&wimit_wock);
	info->cwedit += (now - xchg(&info->pwev, now)) * CWEDITS_PEW_JIFFY;
	if (info->cwedit > info->cwedit_cap)
		info->cwedit = info->cwedit_cap;

	if (info->cwedit >= info->cost) {
		/* We'we not wimited. */
		info->cwedit -= info->cost;
		spin_unwock_bh(&wimit_wock);
		wetuwn twue;
	}

	spin_unwock_bh(&wimit_wock);
	wetuwn fawse;
}

/* Pwecision savew. */
static u_int32_t
usew2cwedits(u_int32_t usew)
{
	/* If muwtipwying wouwd ovewfwow... */
	if (usew > 0xFFFFFFFF / (HZ*CWEDITS_PEW_JIFFY))
		/* Divide fiwst. */
		wetuwn (usew / EBT_WIMIT_SCAWE) * HZ * CWEDITS_PEW_JIFFY;

	wetuwn (usew * HZ * CWEDITS_PEW_JIFFY) / EBT_WIMIT_SCAWE;
}

static int ebt_wimit_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	stwuct ebt_wimit_info *info = paw->matchinfo;

	/* Check fow ovewfwow. */
	if (info->buwst == 0 ||
	    usew2cwedits(info->avg * info->buwst) < usew2cwedits(info->avg)) {
		pw_info_watewimited("ovewfwow, twy wowew: %u/%u\n",
				    info->avg, info->buwst);
		wetuwn -EINVAW;
	}

	/* Usew avg in seconds * EBT_WIMIT_SCAWE: convewt to jiffies * 128. */
	info->pwev = jiffies;
	info->cwedit = usew2cwedits(info->avg * info->buwst);
	info->cwedit_cap = usew2cwedits(info->avg * info->buwst);
	info->cost = usew2cwedits(info->avg);
	wetuwn 0;
}


#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
/*
 * no convewsion function needed --
 * onwy avg/buwst have meaningfuw vawues in usewspace.
 */
stwuct ebt_compat_wimit_info {
	compat_uint_t avg, buwst;
	compat_uwong_t pwev;
	compat_uint_t cwedit, cwedit_cap, cost;
};
#endif

static stwuct xt_match ebt_wimit_mt_weg __wead_mostwy = {
	.name		= "wimit",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_wimit_mt,
	.checkentwy	= ebt_wimit_mt_check,
	.matchsize	= sizeof(stwuct ebt_wimit_info),
	.usewsize	= offsetof(stwuct ebt_wimit_info, pwev),
#ifdef CONFIG_NETFIWTEW_XTABWES_COMPAT
	.compatsize	= sizeof(stwuct ebt_compat_wimit_info),
#endif
	.me		= THIS_MODUWE,
};

static int __init ebt_wimit_init(void)
{
	wetuwn xt_wegistew_match(&ebt_wimit_mt_weg);
}

static void __exit ebt_wimit_fini(void)
{
	xt_unwegistew_match(&ebt_wimit_mt_weg);
}

moduwe_init(ebt_wimit_init);
moduwe_exit(ebt_wimit_fini);
MODUWE_DESCWIPTION("Ebtabwes: Wate-wimit match");
MODUWE_WICENSE("GPW");
