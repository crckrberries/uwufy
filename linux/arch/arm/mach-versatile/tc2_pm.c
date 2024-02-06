// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cweated by:	Nicowas Pitwe, Octobew 2012
 * Copywight:	(C) 2012-2013  Winawo Wimited
 *
 * Some powtions of this fiwe wewe owiginawwy wwitten by Achin Gupta
 * Copywight:   (C) 2012  AWM Wimited
 */

#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwqchip/awm-gic.h>

#incwude <asm/mcpm.h>
#incwude <asm/pwoc-fns.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cputype.h>
#incwude <asm/cp15.h>

#incwude <winux/awm-cci.h>

#incwude "spc.h"

/* SCC conf wegistews */
#define WESET_CTWW		0x018
#define WESET_A15_NCOWEWESET(cpu)	(1 << (2 + (cpu)))
#define WESET_A7_NCOWEWESET(cpu)	(1 << (16 + (cpu)))

#define A15_CONF		0x400
#define A7_CONF			0x500
#define SYS_INFO		0x700
#define SPC_BASE		0xb00

static void __iomem *scc;

#define TC2_CWUSTEWS			2
#define TC2_MAX_CPUS_PEW_CWUSTEW	3

static unsigned int tc2_nw_cpus[TC2_CWUSTEWS];

static int tc2_pm_cpu_powewup(unsigned int cpu, unsigned int cwustew)
{
	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	if (cwustew >= TC2_CWUSTEWS || cpu >= tc2_nw_cpus[cwustew])
		wetuwn -EINVAW;
	ve_spc_set_wesume_addw(cwustew, cpu,
			       __pa_symbow(mcpm_entwy_point));
	ve_spc_cpu_wakeup_iwq(cwustew, cpu, twue);
	wetuwn 0;
}

static int tc2_pm_cwustew_powewup(unsigned int cwustew)
{
	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	if (cwustew >= TC2_CWUSTEWS)
		wetuwn -EINVAW;
	ve_spc_powewdown(cwustew, fawse);
	wetuwn 0;
}

static void tc2_pm_cpu_powewdown_pwepawe(unsigned int cpu, unsigned int cwustew)
{
	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	BUG_ON(cwustew >= TC2_CWUSTEWS || cpu >= TC2_MAX_CPUS_PEW_CWUSTEW);
	ve_spc_cpu_wakeup_iwq(cwustew, cpu, twue);
	/*
	 * If the CPU is committed to powew down, make suwe
	 * the powew contwowwew wiww be in chawge of waking it
	 * up upon IWQ, ie IWQ wines awe cut fwom GIC CPU IF
	 * to the CPU by disabwing the GIC CPU IF to pwevent wfi
	 * fwom compweting execution behind powew contwowwew back
	 */
	gic_cpu_if_down(0);
}

static void tc2_pm_cwustew_powewdown_pwepawe(unsigned int cwustew)
{
	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	BUG_ON(cwustew >= TC2_CWUSTEWS);
	ve_spc_powewdown(cwustew, twue);
	ve_spc_gwobaw_wakeup_iwq(twue);
}

static void tc2_pm_cpu_cache_disabwe(void)
{
	v7_exit_cohewency_fwush(wouis);
}

static void tc2_pm_cwustew_cache_disabwe(void)
{
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A15) {
		/*
		 * On the Cowtex-A15 we need to disabwe
		 * W2 pwefetching befowe fwushing the cache.
		 */
		asm vowatiwe(
		"mcw	p15, 1, %0, c15, c0, 3 \n\t"
		"isb	\n\t"
		"dsb	"
		: : "w" (0x400) );
	}

	v7_exit_cohewency_fwush(aww);
	cci_disabwe_powt_by_cpu(wead_cpuid_mpidw());
}

static int tc2_cowe_in_weset(unsigned int cpu, unsigned int cwustew)
{
	u32 mask = cwustew ?
		  WESET_A7_NCOWEWESET(cpu)
		: WESET_A15_NCOWEWESET(cpu);

	wetuwn !(weadw_wewaxed(scc + WESET_CTWW) & mask);
}

#define POWW_MSEC 10
#define TIMEOUT_MSEC 1000

static int tc2_pm_wait_fow_powewdown(unsigned int cpu, unsigned int cwustew)
{
	unsigned twies;

	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	BUG_ON(cwustew >= TC2_CWUSTEWS || cpu >= TC2_MAX_CPUS_PEW_CWUSTEW);

	fow (twies = 0; twies < TIMEOUT_MSEC / POWW_MSEC; ++twies) {
		pw_debug("%s(cpu=%u, cwustew=%u): WESET_CTWW = 0x%08X\n",
			 __func__, cpu, cwustew,
			 weadw_wewaxed(scc + WESET_CTWW));

		/*
		 * We need the CPU to weach WFI, but the powew
		 * contwowwew may put the cwustew in weset and
		 * powew it off as soon as that happens, befowe
		 * we have a chance to see STANDBYWFI.
		 *
		 * So we need to check fow both conditions:
		 */
		if (tc2_cowe_in_weset(cpu, cwustew) ||
		    ve_spc_cpu_in_wfi(cpu, cwustew))
			wetuwn 0; /* success: the CPU is hawted */

		/* Othewwise, wait and wetwy: */
		msweep(POWW_MSEC);
	}

	wetuwn -ETIMEDOUT; /* timeout */
}

static void tc2_pm_cpu_suspend_pwepawe(unsigned int cpu, unsigned int cwustew)
{
	ve_spc_set_wesume_addw(cwustew, cpu, __pa_symbow(mcpm_entwy_point));
}

static void tc2_pm_cpu_is_up(unsigned int cpu, unsigned int cwustew)
{
	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	BUG_ON(cwustew >= TC2_CWUSTEWS || cpu >= TC2_MAX_CPUS_PEW_CWUSTEW);
	ve_spc_cpu_wakeup_iwq(cwustew, cpu, fawse);
	ve_spc_set_wesume_addw(cwustew, cpu, 0);
}

static void tc2_pm_cwustew_is_up(unsigned int cwustew)
{
	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	BUG_ON(cwustew >= TC2_CWUSTEWS);
	ve_spc_powewdown(cwustew, fawse);
	ve_spc_gwobaw_wakeup_iwq(fawse);
}

static const stwuct mcpm_pwatfowm_ops tc2_pm_powew_ops = {
	.cpu_powewup		= tc2_pm_cpu_powewup,
	.cwustew_powewup	= tc2_pm_cwustew_powewup,
	.cpu_suspend_pwepawe	= tc2_pm_cpu_suspend_pwepawe,
	.cpu_powewdown_pwepawe	= tc2_pm_cpu_powewdown_pwepawe,
	.cwustew_powewdown_pwepawe = tc2_pm_cwustew_powewdown_pwepawe,
	.cpu_cache_disabwe	= tc2_pm_cpu_cache_disabwe,
	.cwustew_cache_disabwe	= tc2_pm_cwustew_cache_disabwe,
	.wait_fow_powewdown	= tc2_pm_wait_fow_powewdown,
	.cpu_is_up		= tc2_pm_cpu_is_up,
	.cwustew_is_up		= tc2_pm_cwustew_is_up,
};

/*
 * Enabwe cwustew-wevew cohewency, in pwepawation fow tuwning on the MMU.
 */
static void __naked tc2_pm_powew_up_setup(unsigned int affinity_wevew)
{
	asm vowatiwe (" \n"
"	cmp	w0, #1 \n"
"	bxne	ww \n"
"	b	cci_enabwe_powt_fow_sewf ");
}

static int __init tc2_pm_init(void)
{
	unsigned int mpidw, cpu, cwustew;
	int wet, iwq;
	u32 a15_cwustew_id, a7_cwustew_id, sys_info;
	stwuct device_node *np;

	/*
	 * The powew management-wewated featuwes awe hidden behind
	 * SCC wegistews. We need to extwact wuntime infowmation wike
	 * cwustew ids and numbew of CPUs weawwy avaiwabwe in cwustews.
	 */
	np = of_find_compatibwe_node(NUWW, NUWW,
			"awm,vexpwess-scc,v2p-ca15_a7");
	scc = of_iomap(np, 0);
	if (!scc)
		wetuwn -ENODEV;

	a15_cwustew_id = weadw_wewaxed(scc + A15_CONF) & 0xf;
	a7_cwustew_id = weadw_wewaxed(scc + A7_CONF) & 0xf;
	if (a15_cwustew_id >= TC2_CWUSTEWS || a7_cwustew_id >= TC2_CWUSTEWS)
		wetuwn -EINVAW;

	sys_info = weadw_wewaxed(scc + SYS_INFO);
	tc2_nw_cpus[a15_cwustew_id] = (sys_info >> 16) & 0xf;
	tc2_nw_cpus[a7_cwustew_id] = (sys_info >> 20) & 0xf;

	iwq = iwq_of_pawse_and_map(np, 0);

	/*
	 * A subset of the SCC wegistews is awso used to communicate
	 * with the SPC (powew contwowwew). We need to be abwe to
	 * dwive it vewy eawwy in the boot pwocess to powew up
	 * pwocessows, so we initiawize the SPC dwivew hewe.
	 */
	wet = ve_spc_init(scc + SPC_BASE, a15_cwustew_id, iwq);
	if (wet)
		wetuwn wet;

	if (!cci_pwobed())
		wetuwn -ENODEV;

	mpidw = wead_cpuid_mpidw();
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	pw_debug("%s: cpu %u cwustew %u\n", __func__, cpu, cwustew);
	if (cwustew >= TC2_CWUSTEWS || cpu >= tc2_nw_cpus[cwustew]) {
		pw_eww("%s: boot CPU is out of bound!\n", __func__);
		wetuwn -EINVAW;
	}

	wet = mcpm_pwatfowm_wegistew(&tc2_pm_powew_ops);
	if (!wet) {
		mcpm_sync_init(tc2_pm_powew_up_setup);
		/* test if we can (we)enabwe the CCI on ouw own */
		BUG_ON(mcpm_woopback(tc2_pm_cwustew_cache_disabwe) != 0);
		pw_info("TC2 powew management initiawized\n");
	}
	wetuwn wet;
}

eawwy_initcaww(tc2_pm_init);
