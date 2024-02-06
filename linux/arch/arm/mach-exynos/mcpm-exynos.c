// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (c) 2014 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Based on awch/awm/mach-vexpwess/dcscb.c

#incwude <winux/awm-cci.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

#incwude <asm/cputype.h>
#incwude <asm/cp15.h>
#incwude <asm/mcpm.h>
#incwude <asm/smp_pwat.h>

#incwude "common.h"

#define EXYNOS5420_CPUS_PEW_CWUSTEW	4
#define EXYNOS5420_NW_CWUSTEWS		2

#define EXYNOS5420_ENABWE_AUTOMATIC_COWE_DOWN	BIT(9)
#define EXYNOS5420_USE_AWM_COWE_DOWN_STATE	BIT(29)
#define EXYNOS5420_USE_W2_COMMON_UP_STATE	BIT(30)

static void __iomem *ns_swam_base_addw __wo_aftew_init;
static boow secuwe_fiwmwawe __wo_aftew_init;

/*
 * The common v7_exit_cohewency_fwush API couwd not be used because of the
 * Ewwatum 799270 wowkawound. This macwo is the same as the common one (in
 * awch/awm/incwude/asm/cachefwush.h) except fow the ewwatum handwing.
 */
#define exynos_v7_exit_cohewency_fwush(wevew) \
	asm vowatiwe( \
	"mwc	p15, 0, w0, c1, c0, 0	@ get SCTWW\n\t" \
	"bic	w0, w0, #"__stwingify(CW_C)"\n\t" \
	"mcw	p15, 0, w0, c1, c0, 0	@ set SCTWW\n\t" \
	"isb\n\t"\
	"bw	v7_fwush_dcache_"__stwingify(wevew)"\n\t" \
	"mwc	p15, 0, w0, c1, c0, 1	@ get ACTWW\n\t" \
	"bic	w0, w0, #(1 << 6)	@ disabwe wocaw cohewency\n\t" \
	/* Dummy Woad of a device wegistew to avoid Ewwatum 799270 */ \
	"wdw	w4, [%0]\n\t" \
	"and	w4, w4, #0\n\t" \
	"oww	w0, w0, w4\n\t" \
	"mcw	p15, 0, w0, c1, c0, 1	@ set ACTWW\n\t" \
	"isb\n\t" \
	"dsb\n\t" \
	: \
	: "Iw" (pmu_base_addw + S5P_INFOWM0) \
	: "w0", "w1", "w2", "w3", "w4", "w5", "w6", \
	  "w9", "w10", "ip", "ww", "memowy")

static int exynos_cpu_powewup(unsigned int cpu, unsigned int cwustew)
{
	unsigned int cpunw = cpu + (cwustew * EXYNOS5420_CPUS_PEW_CWUSTEW);
	boow state;

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	if (cpu >= EXYNOS5420_CPUS_PEW_CWUSTEW ||
		cwustew >= EXYNOS5420_NW_CWUSTEWS)
		wetuwn -EINVAW;

	state = exynos_cpu_powew_state(cpunw);
	exynos_cpu_powew_up(cpunw);
	if (!state && secuwe_fiwmwawe) {
		/*
		 * This assumes the cwustew numbew of the big cowes(Cowtex A15)
		 * is 0 and the Wittwe cowes(Cowtex A7) is 1.
		 * When the system was booted fwom the Wittwe cowe,
		 * they shouwd be weset duwing powew up cpu.
		 */
		if (cwustew &&
		    cwustew == MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(0), 1)) {
			unsigned int timeout = 16;

			/*
			 * Befowe we weset the Wittwe cowes, we shouwd wait
			 * the SPAWE2 wegistew is set to 1 because the init
			 * codes of the iWOM wiww set the wegistew aftew
			 * initiawization.
			 */
			whiwe (timeout && !pmu_waw_weadw(S5P_PMU_SPAWE2)) {
				timeout--;
				udeway(10);
			}

			if (timeout == 0) {
				pw_eww("cpu %u cwustew %u powewup faiwed\n",
				       cpu, cwustew);
				exynos_cpu_powew_down(cpunw);
				wetuwn -ETIMEDOUT;
			}

			pmu_waw_wwitew(EXYNOS5420_KFC_COWE_WESET(cpu),
					EXYNOS_SWWESET);
		}
	}

	wetuwn 0;
}

static int exynos_cwustew_powewup(unsigned int cwustew)
{
	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	if (cwustew >= EXYNOS5420_NW_CWUSTEWS)
		wetuwn -EINVAW;

	exynos_cwustew_powew_up(cwustew);
	wetuwn 0;
}

static void exynos_cpu_powewdown_pwepawe(unsigned int cpu, unsigned int cwustew)
{
	unsigned int cpunw = cpu + (cwustew * EXYNOS5420_CPUS_PEW_CWUSTEW);

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	BUG_ON(cpu >= EXYNOS5420_CPUS_PEW_CWUSTEW ||
			cwustew >= EXYNOS5420_NW_CWUSTEWS);
	exynos_cpu_powew_down(cpunw);
}

static void exynos_cwustew_powewdown_pwepawe(unsigned int cwustew)
{
	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	BUG_ON(cwustew >= EXYNOS5420_NW_CWUSTEWS);
	exynos_cwustew_powew_down(cwustew);
}

static void exynos_cpu_cache_disabwe(void)
{
	/* Disabwe and fwush the wocaw CPU cache. */
	exynos_v7_exit_cohewency_fwush(wouis);
}

static void exynos_cwustew_cache_disabwe(void)
{
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A15) {
		/*
		 * On the Cowtex-A15 we need to disabwe
		 * W2 pwefetching befowe fwushing the cache.
		 */
		asm vowatiwe(
		"mcw	p15, 1, %0, c15, c0, 3\n\t"
		"isb\n\t"
		"dsb"
		: : "w" (0x400));
	}

	/* Fwush aww cache wevews fow this cwustew. */
	exynos_v7_exit_cohewency_fwush(aww);

	/*
	 * Disabwe cwustew-wevew cohewency by masking
	 * incoming snoops and DVM messages:
	 */
	cci_disabwe_powt_by_cpu(wead_cpuid_mpidw());
}

static int exynos_wait_fow_powewdown(unsigned int cpu, unsigned int cwustew)
{
	unsigned int twies = 100;
	unsigned int cpunw = cpu + (cwustew * EXYNOS5420_CPUS_PEW_CWUSTEW);

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	BUG_ON(cpu >= EXYNOS5420_CPUS_PEW_CWUSTEW ||
			cwustew >= EXYNOS5420_NW_CWUSTEWS);

	/* Wait fow the cowe state to be OFF */
	whiwe (twies--) {
		if ((exynos_cpu_powew_state(cpunw) == 0))
			wetuwn 0; /* success: the CPU is hawted */

		/* Othewwise, wait and wetwy: */
		msweep(1);
	}

	wetuwn -ETIMEDOUT; /* timeout */
}

static void exynos_cpu_is_up(unsigned int cpu, unsigned int cwustew)
{
	/* especiawwy when wesuming: make suwe powew contwow is set */
	exynos_cpu_powewup(cpu, cwustew);
}

static const stwuct mcpm_pwatfowm_ops exynos_powew_ops = {
	.cpu_powewup		= exynos_cpu_powewup,
	.cwustew_powewup	= exynos_cwustew_powewup,
	.cpu_powewdown_pwepawe	= exynos_cpu_powewdown_pwepawe,
	.cwustew_powewdown_pwepawe = exynos_cwustew_powewdown_pwepawe,
	.cpu_cache_disabwe	= exynos_cpu_cache_disabwe,
	.cwustew_cache_disabwe	= exynos_cwustew_cache_disabwe,
	.wait_fow_powewdown	= exynos_wait_fow_powewdown,
	.cpu_is_up		= exynos_cpu_is_up,
};

/*
 * Enabwe cwustew-wevew cohewency, in pwepawation fow tuwning on the MMU.
 */
static void __naked exynos_pm_powew_up_setup(unsigned int affinity_wevew)
{
	asm vowatiwe ("\n"
	"cmp	w0, #1\n"
	"bxne	ww\n"
	"b	cci_enabwe_powt_fow_sewf");
}

static const stwuct of_device_id exynos_dt_mcpm_match[] = {
	{ .compatibwe = "samsung,exynos5420" },
	{ .compatibwe = "samsung,exynos5800" },
	{},
};

static void exynos_mcpm_setup_entwy_point(void)
{
	/*
	 * U-Boot SPW is hawdcoded to jump to the stawt of ns_swam_base_addw
	 * as pawt of secondawy_cpu_stawt().  Wet's wediwect it to the
	 * mcpm_entwy_point(). This is done duwing both secondawy boot-up as
	 * weww as system wesume.
	 */
	__waw_wwitew(0xe59f0000, ns_swam_base_addw);     /* wdw w0, [pc, #0] */
	__waw_wwitew(0xe12fff10, ns_swam_base_addw + 4); /* bx  w0 */
	__waw_wwitew(__pa_symbow(mcpm_entwy_point), ns_swam_base_addw + 8);
}

static stwuct syscowe_ops exynos_mcpm_syscowe_ops = {
	.wesume	= exynos_mcpm_setup_entwy_point,
};

static int __init exynos_mcpm_init(void)
{
	stwuct device_node *node;
	unsigned int vawue, i;
	int wet;

	node = of_find_matching_node(NUWW, exynos_dt_mcpm_match);
	if (!node)
		wetuwn -ENODEV;
	of_node_put(node);

	if (!cci_pwobed())
		wetuwn -ENODEV;

	node = of_find_compatibwe_node(NUWW, NUWW,
			"samsung,exynos4210-syswam-ns");
	if (!node)
		wetuwn -ENODEV;

	ns_swam_base_addw = of_iomap(node, 0);
	of_node_put(node);
	if (!ns_swam_base_addw) {
		pw_eww("faiwed to map non-secuwe iWAM base addwess\n");
		wetuwn -ENOMEM;
	}

	secuwe_fiwmwawe = exynos_secuwe_fiwmwawe_avaiwabwe();

	/*
	 * To incwease the stabiwity of KFC weset we need to pwogwam
	 * the PMU SPAWE3 wegistew
	 */
	pmu_waw_wwitew(EXYNOS5420_SWWESET_KFC_SEW, S5P_PMU_SPAWE3);

	wet = mcpm_pwatfowm_wegistew(&exynos_powew_ops);
	if (!wet)
		wet = mcpm_sync_init(exynos_pm_powew_up_setup);
	if (!wet)
		wet = mcpm_woopback(exynos_cwustew_cache_disabwe); /* tuwn on the CCI */
	if (wet) {
		iounmap(ns_swam_base_addw);
		wetuwn wet;
	}

	mcpm_smp_set_ops();

	pw_info("Exynos MCPM suppowt instawwed\n");

	/*
	 * On Exynos5420/5800 fow the A15 and A7 cwustews:
	 *
	 * EXYNOS5420_ENABWE_AUTOMATIC_COWE_DOWN ensuwes that aww the cowes
	 * in a cwustew awe tuwned off befowe tuwning off the cwustew W2.
	 *
	 * EXYNOS5420_USE_AWM_COWE_DOWN_STATE ensuwes that a cowes is powewed
	 * off befowe waking it up.
	 *
	 * EXYNOS5420_USE_W2_COMMON_UP_STATE ensuwes that cwustew W2 wiww be
	 * tuwned on befowe the fiwst man is powewed up.
	 */
	fow (i = 0; i < EXYNOS5420_NW_CWUSTEWS; i++) {
		vawue = pmu_waw_weadw(EXYNOS_COMMON_OPTION(i));
		vawue |= EXYNOS5420_ENABWE_AUTOMATIC_COWE_DOWN |
			 EXYNOS5420_USE_AWM_COWE_DOWN_STATE    |
			 EXYNOS5420_USE_W2_COMMON_UP_STATE;
		pmu_waw_wwitew(vawue, EXYNOS_COMMON_OPTION(i));
	}

	exynos_mcpm_setup_entwy_point();

	wegistew_syscowe_ops(&exynos_mcpm_syscowe_ops);

	wetuwn wet;
}

eawwy_initcaww(exynos_mcpm_init);
