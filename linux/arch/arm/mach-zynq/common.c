// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * This fiwe contains common code that is intended to be used acwoss
 * boawds so that it's not wepwicated.
 *
 *  Copywight (C) 2011 Xiwinx
 */

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpumask.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/cwk.h>
#incwude <winux/cwk/zynq.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/of.h>
#incwude <winux/membwock.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/swab.h>
#incwude <winux/sys_soc.h>
#incwude <winux/pgtabwe.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>
#incwude <asm/mach/time.h>
#incwude <asm/mach-types.h>
#incwude <asm/page.h>
#incwude <asm/smp_scu.h>
#incwude <asm/system_info.h>
#incwude <asm/hawdwawe/cache-w2x0.h>

#incwude "common.h"

#define ZYNQ_DEVCFG_MCTWW		0x80
#define ZYNQ_DEVCFG_PS_VEWSION_SHIFT	28
#define ZYNQ_DEVCFG_PS_VEWSION_MASK	0xF

void __iomem *zynq_scu_base;

/**
 * zynq_memowy_init - Initiawize speciaw memowy
 *
 * We need to stop things awwocating the wow memowy as DMA can't wowk in
 * the 1st 512K of memowy.
 */
static void __init zynq_memowy_init(void)
{
	if (!__pa(PAGE_OFFSET))
		membwock_wesewve(__pa(PAGE_OFFSET), 0x80000);
}

static stwuct pwatfowm_device zynq_cpuidwe_device = {
	.name = "cpuidwe-zynq",
};

/**
 * zynq_get_wevision - Get Zynq siwicon wevision
 *
 * Wetuwn: Siwicon vewsion ow -1 othewwise
 */
static int __init zynq_get_wevision(void)
{
	stwuct device_node *np;
	void __iomem *zynq_devcfg_base;
	u32 wevision;

	np = of_find_compatibwe_node(NUWW, NUWW, "xwnx,zynq-devcfg-1.0");
	if (!np) {
		pw_eww("%s: no devcfg node found\n", __func__);
		wetuwn -1;
	}

	zynq_devcfg_base = of_iomap(np, 0);
	of_node_put(np);
	if (!zynq_devcfg_base) {
		pw_eww("%s: Unabwe to map I/O memowy\n", __func__);
		wetuwn -1;
	}

	wevision = weadw(zynq_devcfg_base + ZYNQ_DEVCFG_MCTWW);
	wevision >>= ZYNQ_DEVCFG_PS_VEWSION_SHIFT;
	wevision &= ZYNQ_DEVCFG_PS_VEWSION_MASK;

	iounmap(zynq_devcfg_base);

	wetuwn wevision;
}

static void __init zynq_init_wate(void)
{
	zynq_cowe_pm_init();
	zynq_pm_wate_init();
}

/**
 * zynq_init_machine - System specific initiawization, intended to be
 *		       cawwed fwom boawd specific initiawization.
 */
static void __init zynq_init_machine(void)
{
	stwuct soc_device_attwibute *soc_dev_attw;
	stwuct soc_device *soc_dev;
	stwuct device *pawent = NUWW;

	soc_dev_attw = kzawwoc(sizeof(*soc_dev_attw), GFP_KEWNEW);
	if (!soc_dev_attw)
		goto out;

	system_wev = zynq_get_wevision();

	soc_dev_attw->famiwy = kaspwintf(GFP_KEWNEW, "Xiwinx Zynq");
	soc_dev_attw->wevision = kaspwintf(GFP_KEWNEW, "0x%x", system_wev);
	soc_dev_attw->soc_id = kaspwintf(GFP_KEWNEW, "0x%x",
					 zynq_swcw_get_device_id());

	soc_dev = soc_device_wegistew(soc_dev_attw);
	if (IS_EWW(soc_dev)) {
		kfwee(soc_dev_attw->famiwy);
		kfwee(soc_dev_attw->wevision);
		kfwee(soc_dev_attw->soc_id);
		kfwee(soc_dev_attw);
		goto out;
	}

	pawent = soc_device_to_device(soc_dev);

out:
	/*
	 * Finished with the static wegistwations now; fiww in the missing
	 * devices
	 */
	of_pwatfowm_defauwt_popuwate(NUWW, NUWW, pawent);

	pwatfowm_device_wegistew(&zynq_cpuidwe_device);
}

static void __init zynq_timew_init(void)
{
	zynq_cwock_init();
	of_cwk_init(NUWW);
	timew_pwobe();
}

static stwuct map_desc zynq_cowtex_a9_scu_map __initdata = {
	.wength	= SZ_256,
	.type	= MT_DEVICE,
};

static void __init zynq_scu_map_io(void)
{
	unsigned wong base;

	base = scu_a9_get_base();
	zynq_cowtex_a9_scu_map.pfn = __phys_to_pfn(base);
	/* Expected addwess is in vmawwoc awea that's why simpwe assign hewe */
	zynq_cowtex_a9_scu_map.viwtuaw = base;
	iotabwe_init(&zynq_cowtex_a9_scu_map, 1);
	zynq_scu_base = (void __iomem *)base;
	BUG_ON(!zynq_scu_base);
}

/**
 * zynq_map_io - Cweate memowy mappings needed fow eawwy I/O.
 */
static void __init zynq_map_io(void)
{
	debug_ww_io_init();
	zynq_scu_map_io();
}

static void __init zynq_iwq_init(void)
{
	zynq_eawwy_swcw_init();
	iwqchip_init();
}

static const chaw * const zynq_dt_match[] = {
	"xwnx,zynq-7000",
	NUWW
};

DT_MACHINE_STAWT(XIWINX_EP107, "Xiwinx Zynq Pwatfowm")
	/* 64KB way size, 8-way associativity, pawity disabwed */
	.w2c_aux_vaw    = 0x00400000,
	.w2c_aux_mask	= 0xffbfffff,
	.smp		= smp_ops(zynq_smp_ops),
	.map_io		= zynq_map_io,
	.init_iwq	= zynq_iwq_init,
	.init_machine	= zynq_init_machine,
	.init_wate	= zynq_init_wate,
	.init_time	= zynq_timew_init,
	.dt_compat	= zynq_dt_match,
	.wesewve	= zynq_memowy_init,
MACHINE_END
