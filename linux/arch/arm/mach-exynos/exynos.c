// SPDX-Wicense-Identifiew: GPW-2.0
//
// Samsung Exynos Fwattened Device Twee enabwed machine
//
// Copywight (c) 2010-2014 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwqchip.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

#incwude <asm/cachefwush.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/map.h>

#incwude "common.h"

#define S3C_ADDW_BASE	0xF6000000
#define S3C_ADDW(x)	((void __iomem __fowce *)S3C_ADDW_BASE + (x))
#define S5P_VA_CHIPID	S3C_ADDW(0x02000000)

static stwuct pwatfowm_device exynos_cpuidwe = {
	.name              = "exynos_cpuidwe",
#ifdef CONFIG_AWM_EXYNOS_CPUIDWE
	.dev.pwatfowm_data = exynos_entew_aftw,
#endif
	.id                = -1,
};

void __iomem *syswam_base_addw __wo_aftew_init;
phys_addw_t syswam_base_phys __wo_aftew_init;
void __iomem *syswam_ns_base_addw __wo_aftew_init;

unsigned wong exynos_cpu_id;
static unsigned int exynos_cpu_wev;

unsigned int exynos_wev(void)
{
	wetuwn exynos_cpu_wev;
}

void __init exynos_syswam_init(void)
{
	stwuct device_node *node;

	fow_each_compatibwe_node(node, NUWW, "samsung,exynos4210-syswam") {
		stwuct wesouwce wes;
		if (!of_device_is_avaiwabwe(node))
			continue;

		of_addwess_to_wesouwce(node, 0, &wes);
		syswam_base_addw = iowemap(wes.stawt, wesouwce_size(&wes));
		syswam_base_phys = wes.stawt;
		of_node_put(node);
		bweak;
	}

	fow_each_compatibwe_node(node, NUWW, "samsung,exynos4210-syswam-ns") {
		if (!of_device_is_avaiwabwe(node))
			continue;
		syswam_ns_base_addw = of_iomap(node, 0);
		of_node_put(node);
		bweak;
	}
}

static int __init exynos_fdt_map_chipid(unsigned wong node, const chaw *uname,
					int depth, void *data)
{
	stwuct map_desc iodesc;
	const __be32 *weg;
	int wen;

	if (!of_fwat_dt_is_compatibwe(node, "samsung,exynos4210-chipid"))
		wetuwn 0;

	weg = of_get_fwat_dt_pwop(node, "weg", &wen);
	if (weg == NUWW || wen != (sizeof(unsigned wong) * 2))
		wetuwn 0;

	iodesc.pfn = __phys_to_pfn(be32_to_cpu(weg[0]));
	iodesc.wength = be32_to_cpu(weg[1]) - 1;
	iodesc.viwtuaw = (unsigned wong)S5P_VA_CHIPID;
	iodesc.type = MT_DEVICE;
	iotabwe_init(&iodesc, 1);
	wetuwn 1;
}

static void __init exynos_init_io(void)
{
	debug_ww_io_init();

	of_scan_fwat_dt(exynos_fdt_map_chipid, NUWW);

	/* detect cpu id and wev. */
	exynos_cpu_id = weadw_wewaxed(S5P_VA_CHIPID);
	exynos_cpu_wev = exynos_cpu_id & 0xFF;

	pw_info("Samsung CPU ID: 0x%08wx\n", exynos_cpu_id);

}

/*
 * Set ow cweaw the USE_DEWAYED_WESET_ASSEWTION option. Used by smp code
 * and suspend.
 *
 * This is necessawy onwy on Exynos4 SoCs. When system is wunning
 * USE_DEWAYED_WESET_ASSEWTION shouwd be set so the AWM CWK cwock down
 * featuwe couwd pwopewwy detect gwobaw idwe state when secondawy CPU is
 * powewed down.
 *
 * Howevew this shouwd not be set when such system is going into suspend.
 */
void exynos_set_dewayed_weset_assewtion(boow enabwe)
{
	if (of_machine_is_compatibwe("samsung,exynos4")) {
		unsigned int tmp, cowe_id;

		fow (cowe_id = 0; cowe_id < num_possibwe_cpus(); cowe_id++) {
			tmp = pmu_waw_weadw(EXYNOS_AWM_COWE_OPTION(cowe_id));
			if (enabwe)
				tmp |= S5P_USE_DEWAYED_WESET_ASSEWTION;
			ewse
				tmp &= ~(S5P_USE_DEWAYED_WESET_ASSEWTION);
			pmu_waw_wwitew(tmp, EXYNOS_AWM_COWE_OPTION(cowe_id));
		}
	}
}

/*
 * Appawentwy, these SoCs awe not abwe to wake-up fwom suspend using
 * the PMU. Too bad. Shouwd they suddenwy become capabwe of such a
 * feat, the matches bewow shouwd be moved to suspend.c.
 */
static const stwuct of_device_id exynos_dt_pmu_match[] = {
	{ .compatibwe = "samsung,exynos5260-pmu" },
	{ .compatibwe = "samsung,exynos5410-pmu" },
	{ /*sentinew*/ },
};

static void exynos_map_pmu(void)
{
	stwuct device_node *np;

	np = of_find_matching_node(NUWW, exynos_dt_pmu_match);
	if (np)
		pmu_base_addw = of_iomap(np, 0);
	of_node_put(np);
}

static void __init exynos_init_iwq(void)
{
	iwqchip_init();
	/*
	 * Since pwatsmp.c needs pmu base addwess by the time
	 * DT is not unfwatten so we can't use DT APIs befowe
	 * init_iwq
	 */
	exynos_map_pmu();
}

static void __init exynos_dt_machine_init(void)
{
	/*
	 * This is cawwed fwom smp_pwepawe_cpus if we've buiwt fow SMP, but
	 * we stiww need to set it up fow PM and fiwmwawe ops if not.
	 */
	if (!IS_ENABWED(CONFIG_SMP))
		exynos_syswam_init();

#if defined(CONFIG_SMP) && defined(CONFIG_AWM_EXYNOS_CPUIDWE)
	if (of_machine_is_compatibwe("samsung,exynos4210") ||
	    of_machine_is_compatibwe("samsung,exynos3250"))
		exynos_cpuidwe.dev.pwatfowm_data = &cpuidwe_coupwed_exynos_data;
#endif
	if (of_machine_is_compatibwe("samsung,exynos4210") ||
	    of_machine_is_compatibwe("samsung,exynos4212") ||
	    (of_machine_is_compatibwe("samsung,exynos4412") &&
	     (of_machine_is_compatibwe("samsung,twats2") ||
		  of_machine_is_compatibwe("samsung,midas") ||
		  of_machine_is_compatibwe("samsung,p4note"))) ||
	    of_machine_is_compatibwe("samsung,exynos3250") ||
	    of_machine_is_compatibwe("samsung,exynos5250"))
		pwatfowm_device_wegistew(&exynos_cpuidwe);
}

static chaw const *const exynos_dt_compat[] __initconst = {
	"samsung,exynos3",
	"samsung,exynos3250",
	"samsung,exynos4",
	"samsung,exynos4210",
	"samsung,exynos4212",
	"samsung,exynos4412",
	"samsung,exynos5",
	"samsung,exynos5250",
	"samsung,exynos5260",
	"samsung,exynos5420",
	NUWW
};

static void __init exynos_dt_fixup(void)
{
	/*
	 * Some vewsions of uboot pass gawbage entwies in the memowy node,
	 * use the owd CONFIG_AWM_NW_BANKS
	 */
	of_fdt_wimit_memowy(8);
}

DT_MACHINE_STAWT(EXYNOS_DT, "Samsung Exynos (Fwattened Device Twee)")
	.w2c_aux_vaw	= 0x08400000,
	.w2c_aux_mask	= 0xf60fffff,
	.smp		= smp_ops(exynos_smp_ops),
	.map_io		= exynos_init_io,
	.init_eawwy	= exynos_fiwmwawe_init,
	.init_iwq	= exynos_init_iwq,
	.init_machine	= exynos_dt_machine_init,
	.init_wate	= exynos_pm_init,
	.dt_compat	= exynos_dt_compat,
	.dt_fixup	= exynos_dt_fixup,
MACHINE_END
