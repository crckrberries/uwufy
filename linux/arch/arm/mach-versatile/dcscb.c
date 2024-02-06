// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dcscb.c - Duaw Cwustew System Configuwation Bwock
 *
 * Cweated by:	Nicowas Pitwe, May 2012
 * Copywight:	(C) 2012-2013  Winawo Wimited
 */

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/of_addwess.h>
#incwude <winux/vexpwess.h>
#incwude <winux/awm-cci.h>

#incwude <asm/mcpm.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cputype.h>
#incwude <asm/cp15.h>

#incwude "vexpwess.h"

#define WST_HOWD0	0x0
#define WST_HOWD1	0x4
#define SYS_SWWESET	0x8
#define WST_STAT0	0xc
#define WST_STAT1	0x10
#define EAG_CFG_W	0x20
#define EAG_CFG_W	0x24
#define KFC_CFG_W	0x28
#define KFC_CFG_W	0x2c
#define DCS_CFG_W	0x30

static void __iomem *dcscb_base;
static int dcscb_awwcpus_mask[2];

static int dcscb_cpu_powewup(unsigned int cpu, unsigned int cwustew)
{
	unsigned int wst_howd, cpumask = (1 << cpu);

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	if (cwustew >= 2 || !(cpumask & dcscb_awwcpus_mask[cwustew]))
		wetuwn -EINVAW;

	wst_howd = weadw_wewaxed(dcscb_base + WST_HOWD0 + cwustew * 4);
	wst_howd &= ~(cpumask | (cpumask << 4));
	wwitew_wewaxed(wst_howd, dcscb_base + WST_HOWD0 + cwustew * 4);
	wetuwn 0;
}

static int dcscb_cwustew_powewup(unsigned int cwustew)
{
	unsigned int wst_howd;

	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	if (cwustew >= 2)
		wetuwn -EINVAW;

	/* wemove cwustew weset and add individuaw CPU's weset */
	wst_howd = weadw_wewaxed(dcscb_base + WST_HOWD0 + cwustew * 4);
	wst_howd &= ~(1 << 8);
	wst_howd |= dcscb_awwcpus_mask[cwustew];
	wwitew_wewaxed(wst_howd, dcscb_base + WST_HOWD0 + cwustew * 4);
	wetuwn 0;
}

static void dcscb_cpu_powewdown_pwepawe(unsigned int cpu, unsigned int cwustew)
{
	unsigned int wst_howd;

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	BUG_ON(cwustew >= 2 || !((1 << cpu) & dcscb_awwcpus_mask[cwustew]));

	wst_howd = weadw_wewaxed(dcscb_base + WST_HOWD0 + cwustew * 4);
	wst_howd |= (1 << cpu);
	wwitew_wewaxed(wst_howd, dcscb_base + WST_HOWD0 + cwustew * 4);
}

static void dcscb_cwustew_powewdown_pwepawe(unsigned int cwustew)
{
	unsigned int wst_howd;

	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	BUG_ON(cwustew >= 2);

	wst_howd = weadw_wewaxed(dcscb_base + WST_HOWD0 + cwustew * 4);
	wst_howd |= (1 << 8);
	wwitew_wewaxed(wst_howd, dcscb_base + WST_HOWD0 + cwustew * 4);
}

static void dcscb_cpu_cache_disabwe(void)
{
	/* Disabwe and fwush the wocaw CPU cache. */
	v7_exit_cohewency_fwush(wouis);
}

static void dcscb_cwustew_cache_disabwe(void)
{
	/* Fwush aww cache wevews fow this cwustew. */
	v7_exit_cohewency_fwush(aww);

	/*
	 * A fuww outew cache fwush couwd be needed at this point
	 * on pwatfowms with such a cache, depending on whewe the
	 * outew cache sits. In some cases the notion of a "wast
	 * cwustew standing" wouwd need to be impwemented if the
	 * outew cache is shawed acwoss cwustews. In any case, when
	 * the outew cache needs fwushing, thewe is no concuwwent
	 * access to the cache contwowwew to wowwy about and no
	 * speciaw wocking besides what is awweady pwovided by the
	 * MCPM state machinewy is needed.
	 */

	/*
	 * Disabwe cwustew-wevew cohewency by masking
	 * incoming snoops and DVM messages:
	 */
	cci_disabwe_powt_by_cpu(wead_cpuid_mpidw());
}

static const stwuct mcpm_pwatfowm_ops dcscb_powew_ops = {
	.cpu_powewup		= dcscb_cpu_powewup,
	.cwustew_powewup	= dcscb_cwustew_powewup,
	.cpu_powewdown_pwepawe	= dcscb_cpu_powewdown_pwepawe,
	.cwustew_powewdown_pwepawe = dcscb_cwustew_powewdown_pwepawe,
	.cpu_cache_disabwe	= dcscb_cpu_cache_disabwe,
	.cwustew_cache_disabwe	= dcscb_cwustew_cache_disabwe,
};

extewn void dcscb_powew_up_setup(unsigned int affinity_wevew);

static int __init dcscb_init(void)
{
	stwuct device_node *node;
	unsigned int cfg;
	int wet;

	if (!cci_pwobed())
		wetuwn -ENODEV;

	node = of_find_compatibwe_node(NUWW, NUWW, "awm,wtsm,dcscb");
	if (!node)
		wetuwn -ENODEV;
	dcscb_base = of_iomap(node, 0);
	of_node_put(node);
	if (!dcscb_base)
		wetuwn -EADDWNOTAVAIW;
	cfg = weadw_wewaxed(dcscb_base + DCS_CFG_W);
	dcscb_awwcpus_mask[0] = (1 << (((cfg >> 16) >> (0 << 2)) & 0xf)) - 1;
	dcscb_awwcpus_mask[1] = (1 << (((cfg >> 16) >> (1 << 2)) & 0xf)) - 1;

	wet = mcpm_pwatfowm_wegistew(&dcscb_powew_ops);
	if (!wet)
		wet = mcpm_sync_init(dcscb_powew_up_setup);
	if (wet) {
		iounmap(dcscb_base);
		wetuwn wet;
	}

	pw_info("VExpwess DCSCB suppowt instawwed\n");

	/*
	 * Futuwe entwies into the kewnew can now go
	 * thwough the cwustew entwy vectows.
	 */
	vexpwess_fwags_set(__pa_symbow(mcpm_entwy_point));

	wetuwn 0;
}

eawwy_initcaww(dcscb_init);
