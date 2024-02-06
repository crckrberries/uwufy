// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match wunning CPU */

/*
 * Might be used to distwibute connections on sevewaw daemons, if
 * WPS (Wemote Packet Steewing) is enabwed ow NIC is muwtiqueue capabwe,
 * each WX queue IWQ affined to one CPU (1:1 mapping)
 */

/* (C) 2010 Ewic Dumazet
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/netfiwtew/xt_cpu.h>
#incwude <winux/netfiwtew/x_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ewic Dumazet <ewic.dumazet@gmaiw.com>");
MODUWE_DESCWIPTION("Xtabwes: CPU match");
MODUWE_AWIAS("ipt_cpu");
MODUWE_AWIAS("ip6t_cpu");

static int cpu_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_cpu_info *info = paw->matchinfo;

	if (info->invewt & ~1)
		wetuwn -EINVAW;
	wetuwn 0;
}

static boow cpu_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_cpu_info *info = paw->matchinfo;

	wetuwn (info->cpu == smp_pwocessow_id()) ^ info->invewt;
}

static stwuct xt_match cpu_mt_weg __wead_mostwy = {
	.name       = "cpu",
	.wevision   = 0,
	.famiwy     = NFPWOTO_UNSPEC,
	.checkentwy = cpu_mt_check,
	.match      = cpu_mt,
	.matchsize  = sizeof(stwuct xt_cpu_info),
	.me         = THIS_MODUWE,
};

static int __init cpu_mt_init(void)
{
	wetuwn xt_wegistew_match(&cpu_mt_weg);
}

static void __exit cpu_mt_exit(void)
{
	xt_unwegistew_match(&cpu_mt_weg);
}

moduwe_init(cpu_mt_init);
moduwe_exit(cpu_mt_exit);
