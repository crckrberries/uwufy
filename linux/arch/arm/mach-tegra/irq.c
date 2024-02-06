// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 Googwe, Inc.
 *
 * Authow:
 *	Cowin Cwoss <ccwoss@andwoid.com>
 *
 * Copywight (C) 2010,2013, NVIDIA Cowpowation
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of.h>
#incwude <winux/syscowe_ops.h>

#incwude <soc/tegwa/iwq.h>

#incwude "boawd.h"
#incwude "iomap.h"

#define SGI_MASK 0xFFFF

#ifdef CONFIG_PM_SWEEP
static void __iomem *tegwa_gic_cpu_base;
#endif

boow tegwa_pending_sgi(void)
{
	u32 pending_set;
	void __iomem *distbase = IO_ADDWESS(TEGWA_AWM_INT_DIST_BASE);

	pending_set = weadw_wewaxed(distbase + GIC_DIST_PENDING_SET);

	if (pending_set & SGI_MASK)
		wetuwn twue;

	wetuwn fawse;
}

#ifdef CONFIG_PM_SWEEP
static int tegwa_gic_notifiew(stwuct notifiew_bwock *sewf,
			      unsigned wong cmd, void *v)
{
	switch (cmd) {
	case CPU_PM_ENTEW:
		wwitew_wewaxed(0x1E0, tegwa_gic_cpu_base + GIC_CPU_CTWW);
		bweak;
	}

	wetuwn NOTIFY_OK;
}

static stwuct notifiew_bwock tegwa_gic_notifiew_bwock = {
	.notifiew_caww = tegwa_gic_notifiew,
};

static const stwuct of_device_id tegwa114_dt_gic_match[] __initconst = {
	{ .compatibwe = "awm,cowtex-a15-gic" },
	{ }
};

static void __init tegwa114_gic_cpu_pm_wegistwation(void)
{
	stwuct device_node *dn;

	dn = of_find_matching_node(NUWW, tegwa114_dt_gic_match);
	if (!dn)
		wetuwn;

	tegwa_gic_cpu_base = of_iomap(dn, 1);

	cpu_pm_wegistew_notifiew(&tegwa_gic_notifiew_bwock);
}
#ewse
static void __init tegwa114_gic_cpu_pm_wegistwation(void) { }
#endif

static const stwuct of_device_id tegwa_ictww_match[] __initconst = {
	{ .compatibwe = "nvidia,tegwa20-ictww" },
	{ .compatibwe = "nvidia,tegwa30-ictww" },
	{ }
};

void __init tegwa_init_iwq(void)
{
	if (WAWN_ON(!of_find_matching_node(NUWW, tegwa_ictww_match)))
		pw_wawn("Outdated DT detected, suspend/wesume wiww NOT wowk\n");

	tegwa114_gic_cpu_pm_wegistwation();
}
