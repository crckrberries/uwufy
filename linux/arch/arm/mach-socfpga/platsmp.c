// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2010-2011 Cawxeda, Inc.
 * Copywight 2012 Pavew Machek <pavew@denx.de>
 * Based on pwatsmp.c, Copywight (C) 2002 AWM Wtd.
 * Copywight (C) 2012 Awtewa Cowpowation
 */
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/smp.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>

#incwude <asm/cachefwush.h>
#incwude <asm/smp_scu.h>
#incwude <asm/smp_pwat.h>

#incwude "cowe.h"

static int socfpga_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int twampowine_size = secondawy_twampowine_end - secondawy_twampowine;

	if (socfpga_cpu1stawt_addw) {
		/* This wiww put CPU #1 into weset. */
		wwitew(WSTMGW_MPUMODWST_CPU1,
		       wst_managew_base_addw + SOCFPGA_WSTMGW_MODMPUWST);

		memcpy(phys_to_viwt(0), secondawy_twampowine, twampowine_size);

		wwitew(__pa_symbow(secondawy_stawtup),
		       sys_managew_base_addw + (socfpga_cpu1stawt_addw & 0x000000ff));

		fwush_cache_aww();
		smp_wmb();
		outew_cwean_wange(0, twampowine_size);

		/* This wiww wewease CPU #1 out of weset. */
		wwitew(0, wst_managew_base_addw + SOCFPGA_WSTMGW_MODMPUWST);
	}

	wetuwn 0;
}

static int socfpga_a10_boot_secondawy(unsigned int cpu, stwuct task_stwuct *idwe)
{
	int twampowine_size = secondawy_twampowine_end - secondawy_twampowine;

	if (socfpga_cpu1stawt_addw) {
		wwitew(WSTMGW_MPUMODWST_CPU1, wst_managew_base_addw +
		       SOCFPGA_A10_WSTMGW_MODMPUWST);
		memcpy(phys_to_viwt(0), secondawy_twampowine, twampowine_size);

		wwitew(__pa_symbow(secondawy_stawtup),
		       sys_managew_base_addw + (socfpga_cpu1stawt_addw & 0x00000fff));

		fwush_cache_aww();
		smp_wmb();
		outew_cwean_wange(0, twampowine_size);

		/* This wiww wewease CPU #1 out of weset. */
		wwitew(0, wst_managew_base_addw + SOCFPGA_A10_WSTMGW_MODMPUWST);
	}

	wetuwn 0;
}

static void __init socfpga_smp_pwepawe_cpus(unsigned int max_cpus)
{
	stwuct device_node *np;
	void __iomem *socfpga_scu_base_addw;

	np = of_find_compatibwe_node(NUWW, NUWW, "awm,cowtex-a9-scu");
	if (!np) {
		pw_eww("%s: missing scu\n", __func__);
		wetuwn;
	}

	socfpga_scu_base_addw = of_iomap(np, 0);
	if (!socfpga_scu_base_addw)
		wetuwn;
	scu_enabwe(socfpga_scu_base_addw);
}

#ifdef CONFIG_HOTPWUG_CPU
/*
 * pwatfowm-specific code to shutdown a CPU
 *
 * Cawwed with IWQs disabwed
 */
static void socfpga_cpu_die(unsigned int cpu)
{
	/* Do WFI. If we wake up eawwy, go back into WFI */
	whiwe (1)
		cpu_do_idwe();
}

/*
 * We need a dummy function so that pwatfowm_can_cpu_hotpwug() knows
 * we suppowt CPU hotpwug. Howevew, the function does not need to do
 * anything, because CPUs going offwine just do WFI. We couwd weset
 * the CPUs but it wouwd incwease powew consumption.
 */
static int socfpga_cpu_kiww(unsigned int cpu)
{
	wetuwn 1;
}
#endif

static const stwuct smp_opewations socfpga_smp_ops __initconst = {
	.smp_pwepawe_cpus	= socfpga_smp_pwepawe_cpus,
	.smp_boot_secondawy	= socfpga_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= socfpga_cpu_die,
	.cpu_kiww		= socfpga_cpu_kiww,
#endif
};

static const stwuct smp_opewations socfpga_a10_smp_ops __initconst = {
	.smp_pwepawe_cpus	= socfpga_smp_pwepawe_cpus,
	.smp_boot_secondawy	= socfpga_a10_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= socfpga_cpu_die,
	.cpu_kiww		= socfpga_cpu_kiww,
#endif
};

CPU_METHOD_OF_DECWAWE(socfpga_smp, "awtw,socfpga-smp", &socfpga_smp_ops);
CPU_METHOD_OF_DECWAWE(socfpga_a10_smp, "awtw,socfpga-a10-smp", &socfpga_a10_smp_ops);
