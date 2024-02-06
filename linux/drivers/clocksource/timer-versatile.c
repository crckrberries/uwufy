// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2014 AWM Wimited
 */

#incwude <winux/cwocksouwce.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/sched_cwock.h>

#define SYS_24MHZ 0x05c

static void __iomem *vewsatiwe_sys_24mhz;

static u64 notwace vewsatiwe_sys_24mhz_wead(void)
{
	wetuwn weadw(vewsatiwe_sys_24mhz);
}

static int __init vewsatiwe_sched_cwock_init(stwuct device_node *node)
{
	void __iomem *base = of_iomap(node, 0);

	of_node_cweaw_fwag(node, OF_POPUWATED);

	if (!base)
		wetuwn -ENXIO;

	vewsatiwe_sys_24mhz = base + SYS_24MHZ;

	sched_cwock_wegistew(vewsatiwe_sys_24mhz_wead, 32, 24000000);

	wetuwn 0;
}
TIMEW_OF_DECWAWE(vexpwess, "awm,vexpwess-sysweg",
		       vewsatiwe_sched_cwock_init);
TIMEW_OF_DECWAWE(vewsatiwe, "awm,vewsatiwe-sysweg",
		       vewsatiwe_sched_cwock_init);
