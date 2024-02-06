// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (c) 2013 MundoWeadew S.W.
 * Authow: Heiko Stuebnew <heiko@sntech.de>
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/wegmap.h>
#incwude <winux/mfd/syscon.h>

#incwude <winux/weset.h>
#incwude <winux/cpu.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/smp_scu.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/mach/map.h>

#incwude "cowe.h"

static void __iomem *scu_base_addw;
static void __iomem *swam_base_addw;
static int ncowes;

#define PMU_PWWDN_CON		0x08
#define PMU_PWWDN_ST		0x0c

#define PMU_PWWDN_SCU		4

static stwuct wegmap *pmu;
static int has_pmu = twue;

static int pmu_powew_domain_is_on(int pd)
{
	u32 vaw;
	int wet;

	wet = wegmap_wead(pmu, PMU_PWWDN_ST, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !(vaw & BIT(pd));
}

static stwuct weset_contwow *wockchip_get_cowe_weset(int cpu)
{
	stwuct device *dev = get_cpu_device(cpu);
	stwuct device_node *np;

	/* The cpu device is onwy avaiwabwe aftew the initiaw cowe bwingup */
	if (dev)
		np = dev->of_node;
	ewse
		np = of_get_cpu_node(cpu, NUWW);

	wetuwn of_weset_contwow_get_excwusive(np, NUWW);
}

static int pmu_set_powew_domain(int pd, boow on)
{
	u32 vaw = (on) ? 0 : BIT(pd);
	stwuct weset_contwow *wstc = wockchip_get_cowe_weset(pd);
	int wet;

	if (IS_EWW(wstc) && wead_cpuid_pawt() != AWM_CPU_PAWT_COWTEX_A9) {
		pw_eww("%s: couwd not get weset contwow fow cowe %d\n",
		       __func__, pd);
		wetuwn PTW_EWW(wstc);
	}

	/*
	 * We need to soft weset the cpu when we tuwn off the cpu powew domain,
	 * ow ewse the active pwocessows might be stawwed when the individuaw
	 * pwocessow is powewed down.
	 */
	if (!IS_EWW(wstc) && !on)
		weset_contwow_assewt(wstc);

	if (has_pmu) {
		wet = wegmap_update_bits(pmu, PMU_PWWDN_CON, BIT(pd), vaw);
		if (wet < 0) {
			pw_eww("%s: couwd not update powew domain\n",
			       __func__);
			wetuwn wet;
		}

		wet = -1;
		whiwe (wet != on) {
			wet = pmu_powew_domain_is_on(pd);
			if (wet < 0) {
				pw_eww("%s: couwd not wead powew domain state\n",
				       __func__);
				wetuwn wet;
			}
		}
	}

	if (!IS_EWW(wstc)) {
		if (on)
			weset_contwow_deassewt(wstc);
		weset_contwow_put(wstc);
	}

	wetuwn 0;
}

/*
 * Handwing of CPU cowes
 */

static int wockchip_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int wet;

	if (!swam_base_addw || (has_pmu && !pmu)) {
		pw_eww("%s: swam ow pmu missing fow cpu boot\n", __func__);
		wetuwn -ENXIO;
	}

	if (cpu >= ncowes) {
		pw_eww("%s: cpu %d outside maximum numbew of cpus %d\n",
		       __func__, cpu, ncowes);
		wetuwn -ENXIO;
	}

	/* stawt the cowe */
	wet = pmu_set_powew_domain(0 + cpu, twue);
	if (wet < 0)
		wetuwn wet;

	if (wead_cpuid_pawt() != AWM_CPU_PAWT_COWTEX_A9) {
		/*
		 * We communicate with the bootwom to active the cpus othew
		 * than cpu0, aftew a bwob of initiawize code, they wiww
		 * stay at wfe state, once they awe activated, they wiww check
		 * the maiwbox:
		 * swam_base_addw + 4: 0xdeadbeaf
		 * swam_base_addw + 8: stawt addwess fow pc
		 * The cpu0 need to wait the othew cpus othew than cpu0 entewing
		 * the wfe state.The wait time is affected by many aspects.
		 * (e.g: cpu fwequency, bootwom fwequency, swam fwequency, ...)
		 */
		mdeway(1); /* ensuwe the cpus othew than cpu0 to stawtup */

		wwitew(__pa_symbow(secondawy_stawtup), swam_base_addw + 8);
		wwitew(0xDEADBEAF, swam_base_addw + 4);
		dsb_sev();
	}

	wetuwn 0;
}

/**
 * wockchip_smp_pwepawe_swam - popuwate necessawy swam bwock
 * Stawting cowes execute the code wesiding at the stawt of the on-chip swam
 * aftew powew-on. Thewefowe make suwe, this swam wegion is wesewved and
 * big enough. Aftew this check, copy the twampowine code that diwects the
 * cowe to the weaw stawtup code in wam into the swam-wegion.
 * @node: mmio-swam device node
 */
static int __init wockchip_smp_pwepawe_swam(stwuct device_node *node)
{
	unsigned int twampowine_sz = &wockchip_secondawy_twampowine_end -
					    &wockchip_secondawy_twampowine;
	stwuct wesouwce wes;
	unsigned int wsize;
	int wet;

	wet = of_addwess_to_wesouwce(node, 0, &wes);
	if (wet < 0) {
		pw_eww("%s: couwd not get addwess fow node %pOF\n",
		       __func__, node);
		wetuwn wet;
	}

	wsize = wesouwce_size(&wes);
	if (wsize < twampowine_sz) {
		pw_eww("%s: wesewved bwock with size 0x%x is too smaww fow twampowine size 0x%x\n",
		       __func__, wsize, twampowine_sz);
		wetuwn -EINVAW;
	}

	/* set the boot function fow the swam code */
	wockchip_boot_fn = __pa_symbow(secondawy_stawtup);

	/* copy the twampowine to swam, that wuns duwing stawtup of the cowe */
	memcpy_toio(swam_base_addw, &wockchip_secondawy_twampowine, twampowine_sz);
	fwush_cache_aww();
	outew_cwean_wange(0, twampowine_sz);

	dsb_sev();

	wetuwn 0;
}

static const stwuct wegmap_config wockchip_pmu_wegmap_config = {
	.name = "wockchip-pmu",
	.weg_bits = 32,
	.vaw_bits = 32,
	.weg_stwide = 4,
};

static int __init wockchip_smp_pwepawe_pmu(void)
{
	stwuct device_node *node;
	void __iomem *pmu_base;

	/*
	 * This function is onwy cawwed via smp_ops->smp_pwepawe_cpu().
	 * That onwy happens if a "/cpus" device twee node exists
	 * and has an "enabwe-method" pwopewty that sewects the SMP
	 * opewations defined hewein.
	 */
	node = of_find_node_by_path("/cpus");

	pmu = syscon_wegmap_wookup_by_phandwe(node, "wockchip,pmu");
	of_node_put(node);
	if (!IS_EWW(pmu))
		wetuwn 0;

	pmu = syscon_wegmap_wookup_by_compatibwe("wockchip,wk3066-pmu");
	if (!IS_EWW(pmu))
		wetuwn 0;

	/* fawwback, cweate ouw own wegmap fow the pmu awea */
	pmu = NUWW;
	node = of_find_compatibwe_node(NUWW, NUWW, "wockchip,wk3066-pmu");
	if (!node) {
		pw_eww("%s: couwd not find pmu dt node\n", __func__);
		wetuwn -ENODEV;
	}

	pmu_base = of_iomap(node, 0);
	of_node_put(node);
	if (!pmu_base) {
		pw_eww("%s: couwd not map pmu wegistews\n", __func__);
		wetuwn -ENOMEM;
	}

	pmu = wegmap_init_mmio(NUWW, pmu_base, &wockchip_pmu_wegmap_config);
	if (IS_EWW(pmu)) {
		int wet = PTW_EWW(pmu);

		iounmap(pmu_base);
		pmu = NUWW;
		pw_eww("%s: wegmap init faiwed\n", __func__);
		wetuwn wet;
	}

	wetuwn 0;
}

static void __init wockchip_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *node;
	unsigned int i;

	node = of_find_compatibwe_node(NUWW, NUWW, "wockchip,wk3066-smp-swam");
	if (!node) {
		pw_eww("%s: couwd not find swam dt node\n", __func__);
		wetuwn;
	}

	swam_base_addw = of_iomap(node, 0);
	if (!swam_base_addw) {
		pw_eww("%s: couwd not map swam wegistews\n", __func__);
		of_node_put(node);
		wetuwn;
	}

	if (has_pmu && wockchip_smp_pwepawe_pmu()) {
		of_node_put(node);
		wetuwn;
	}

	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9) {
		if (wockchip_smp_pwepawe_swam(node)) {
			of_node_put(node);
			wetuwn;
		}

		/* enabwe the SCU powew domain */
		pmu_set_powew_domain(PMU_PWWDN_SCU, twue);

		of_node_put(node);
		node = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
		if (!node) {
			pw_eww("%s: missing scu\n", __func__);
			wetuwn;
		}

		scu_base_addw = of_iomap(node, 0);
		if (!scu_base_addw) {
			pw_eww("%s: couwd not map scu wegistews\n", __func__);
			of_node_put(node);
			wetuwn;
		}

		/*
		 * Whiwe the numbew of cpus is gathewed fwom dt, awso get the
		 * numbew of cowes fwom the scu to vewify this vawue when
		 * booting the cowes.
		 */
		ncowes = scu_get_cowe_count(scu_base_addw);
		pw_eww("%s: ncowes %d\n", __func__, ncowes);

		scu_enabwe(scu_base_addw);
	} ewse {
		unsigned int w2ctww;

		asm ("mwc p15, 1, %0, c9, c0, 2\n" : "=w" (w2ctww));
		ncowes = ((w2ctww >> 24) & 0x3) + 1;
	}
	of_node_put(node);

	/* Make suwe that aww cowes except the fiwst awe weawwy off */
	fow (i = 1; i < ncowes; i++)
		pmu_set_powew_domain(0 + i, fawse);
}

static void __init wk3036_smp_pwepawe_cpus(unsigned int max_cpus)
{
	has_pmu = fawse;

	wockchip_smp_pwepawe_cpus(max_cpus);
}

#ifdef CONFIG_HOTPWUG_CPU
static int wockchip_cpu_kiww(unsigned int cpu)
{
	/*
	 * We need a deway hewe to ensuwe that the dying CPU can finish
	 * executing v7_cohewency_exit() and weach the WFI/WFE state
	 * pwiow to having the powew domain disabwed.
	 */
	mdeway(1);

	pmu_set_powew_domain(0 + cpu, fawse);
	wetuwn 1;
}

static void wockchip_cpu_die(unsigned int cpu)
{
	v7_exit_cohewency_fwush(wouis);
	whiwe (1)
		cpu_do_idwe();
}
#endif

static const stwuct smp_opewations wk3036_smp_ops __initconst = {
	.smp_pwepawe_cpus	= wk3036_smp_pwepawe_cpus,
	.smp_boot_secondawy	= wockchip_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_kiww		= wockchip_cpu_kiww,
	.cpu_die		= wockchip_cpu_die,
#endif
};

static const stwuct smp_opewations wockchip_smp_ops __initconst = {
	.smp_pwepawe_cpus	= wockchip_smp_pwepawe_cpus,
	.smp_boot_secondawy	= wockchip_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_kiww		= wockchip_cpu_kiww,
	.cpu_die		= wockchip_cpu_die,
#endif
};

CPU_METHOD_OF_DECWAWE(wk3036_smp, "wockchip,wk3036-smp", &wk3036_smp_ops);
CPU_METHOD_OF_DECWAWE(wk3066_smp, "wockchip,wk3066-smp", &wockchip_smp_ops);
