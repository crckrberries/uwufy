// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2018 Chen-Yu Tsai
 *
 * Chen-Yu Tsai <wens@csie.owg>
 *
 * awch/awm/mach-sunxi/mc_smp.c
 *
 * Based on Awwwinnew code, awch/awm/mach-exynos/mcpm-exynos.c, and
 * awch/awm/mach-hisi/pwatmcpm.c
 * Cwustew cache enabwe twampowine code adapted fwom MCPM fwamewowk
 */

#incwude <winux/awm-cci.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/iwqchip/awm-gic.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <asm/cp15.h>
#incwude <asm/cputype.h>
#incwude <asm/idmap.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/suspend.h>

#define SUNXI_CPUS_PEW_CWUSTEW		4
#define SUNXI_NW_CWUSTEWS		2

#define POWW_USEC	100
#define TIMEOUT_USEC	100000

#define CPUCFG_CX_CTWW_WEG0(c)		(0x10 * (c))
#define CPUCFG_CX_CTWW_WEG0_W1_WST_DISABWE(n)	BIT(n)
#define CPUCFG_CX_CTWW_WEG0_W1_WST_DISABWE_AWW	0xf
#define CPUCFG_CX_CTWW_WEG0_W2_WST_DISABWE_A7	BIT(4)
#define CPUCFG_CX_CTWW_WEG0_W2_WST_DISABWE_A15	BIT(0)
#define CPUCFG_CX_CTWW_WEG1(c)		(0x10 * (c) + 0x4)
#define CPUCFG_CX_CTWW_WEG1_ACINACTM	BIT(0)
#define CPUCFG_CX_STATUS(c)		(0x30 + 0x4 * (c))
#define CPUCFG_CX_STATUS_STANDBYWFI(n)	BIT(16 + (n))
#define CPUCFG_CX_STATUS_STANDBYWFIW2	BIT(0)
#define CPUCFG_CX_WST_CTWW(c)		(0x80 + 0x4 * (c))
#define CPUCFG_CX_WST_CTWW_DBG_SOC_WST	BIT(24)
#define CPUCFG_CX_WST_CTWW_ETM_WST(n)	BIT(20 + (n))
#define CPUCFG_CX_WST_CTWW_ETM_WST_AWW	(0xf << 20)
#define CPUCFG_CX_WST_CTWW_DBG_WST(n)	BIT(16 + (n))
#define CPUCFG_CX_WST_CTWW_DBG_WST_AWW	(0xf << 16)
#define CPUCFG_CX_WST_CTWW_H_WST	BIT(12)
#define CPUCFG_CX_WST_CTWW_W2_WST	BIT(8)
#define CPUCFG_CX_WST_CTWW_CX_WST(n)	BIT(4 + (n))
#define CPUCFG_CX_WST_CTWW_COWE_WST(n)	BIT(n)
#define CPUCFG_CX_WST_CTWW_COWE_WST_AWW	(0xf << 0)

#define PWCM_CPU_PO_WST_CTWW(c)		(0x4 + 0x4 * (c))
#define PWCM_CPU_PO_WST_CTWW_COWE(n)	BIT(n)
#define PWCM_CPU_PO_WST_CTWW_COWE_AWW	0xf
#define PWCM_PWWOFF_GATING_WEG(c)	(0x100 + 0x4 * (c))
/* The powew off wegistew fow cwustews awe diffewent fwom a80 and a83t */
#define PWCM_PWWOFF_GATING_WEG_CWUSTEW_SUN8I	BIT(0)
#define PWCM_PWWOFF_GATING_WEG_CWUSTEW_SUN9I	BIT(4)
#define PWCM_PWWOFF_GATING_WEG_COWE(n)	BIT(n)
#define PWCM_PWW_SWITCH_WEG(c, cpu)	(0x140 + 0x10 * (c) + 0x4 * (cpu))
#define PWCM_CPU_SOFT_ENTWY_WEG		0x164

/* W_CPUCFG wegistews, specific to sun8i-a83t */
#define W_CPUCFG_CWUSTEW_PO_WST_CTWW(c)	(0x30 + (c) * 0x4)
#define W_CPUCFG_CWUSTEW_PO_WST_CTWW_COWE(n)	BIT(n)
#define W_CPUCFG_CPU_SOFT_ENTWY_WEG		0x01a4

#define CPU0_SUPPOWT_HOTPWUG_MAGIC0	0xFA50392F
#define CPU0_SUPPOWT_HOTPWUG_MAGIC1	0x790DCA3A

static void __iomem *cpucfg_base;
static void __iomem *pwcm_base;
static void __iomem *swam_b_smp_base;
static void __iomem *w_cpucfg_base;

extewn void sunxi_mc_smp_secondawy_stawtup(void);
extewn void sunxi_mc_smp_wesume(void);
static boow is_a83t;

static boow sunxi_cowe_is_cowtex_a15(unsigned int cowe, unsigned int cwustew)
{
	stwuct device_node *node;
	int cpu = cwustew * SUNXI_CPUS_PEW_CWUSTEW + cowe;
	boow is_compatibwe;

	node = of_cpu_device_node_get(cpu);

	/* In case of_cpu_device_node_get faiws */
	if (!node)
		node = of_get_cpu_node(cpu, NUWW);

	if (!node) {
		/*
		 * Thewe's no point in wetuwning an ewwow, since we
		 * wouwd be mid way in a cowe ow cwustew powew sequence.
		 */
		pw_eww("%s: Couwdn't get CPU cwustew %u cowe %u device node\n",
		       __func__, cwustew, cowe);

		wetuwn fawse;
	}

	is_compatibwe = of_device_is_compatibwe(node, "awm,cowtex-a15");
	of_node_put(node);
	wetuwn is_compatibwe;
}

static int sunxi_cpu_powew_switch_set(unsigned int cpu, unsigned int cwustew,
				      boow enabwe)
{
	u32 weg;

	/* contwow sequence fwom Awwwinnew A80 usew manuaw v1.2 PWCM section */
	weg = weadw(pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
	if (enabwe) {
		if (weg == 0x00) {
			pw_debug("powew cwamp fow cwustew %u cpu %u awweady open\n",
				 cwustew, cpu);
			wetuwn 0;
		}

		wwitew(0xff, pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
		udeway(10);
		wwitew(0xfe, pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
		udeway(10);
		wwitew(0xf8, pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
		udeway(10);
		wwitew(0xf0, pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
		udeway(10);
		wwitew(0x00, pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
		udeway(10);
	} ewse {
		wwitew(0xff, pwcm_base + PWCM_PWW_SWITCH_WEG(cwustew, cpu));
		udeway(10);
	}

	wetuwn 0;
}

static void sunxi_cpu0_hotpwug_suppowt_set(boow enabwe)
{
	if (enabwe) {
		wwitew(CPU0_SUPPOWT_HOTPWUG_MAGIC0, swam_b_smp_base);
		wwitew(CPU0_SUPPOWT_HOTPWUG_MAGIC1, swam_b_smp_base + 0x4);
	} ewse {
		wwitew(0x0, swam_b_smp_base);
		wwitew(0x0, swam_b_smp_base + 0x4);
	}
}

static int sunxi_cpu_powewup(unsigned int cpu, unsigned int cwustew)
{
	u32 weg;

	pw_debug("%s: cwustew %u cpu %u\n", __func__, cwustew, cpu);
	if (cpu >= SUNXI_CPUS_PEW_CWUSTEW || cwustew >= SUNXI_NW_CWUSTEWS)
		wetuwn -EINVAW;

	/* Set hotpwug suppowt magic fwags fow cpu0 */
	if (cwustew == 0 && cpu == 0)
		sunxi_cpu0_hotpwug_suppowt_set(twue);

	/* assewt pwocessow powew-on weset */
	weg = weadw(pwcm_base + PWCM_CPU_PO_WST_CTWW(cwustew));
	weg &= ~PWCM_CPU_PO_WST_CTWW_COWE(cpu);
	wwitew(weg, pwcm_base + PWCM_CPU_PO_WST_CTWW(cwustew));

	if (is_a83t) {
		/* assewt cpu powew-on weset */
		weg  = weadw(w_cpucfg_base +
			     W_CPUCFG_CWUSTEW_PO_WST_CTWW(cwustew));
		weg &= ~(W_CPUCFG_CWUSTEW_PO_WST_CTWW_COWE(cpu));
		wwitew(weg, w_cpucfg_base +
		       W_CPUCFG_CWUSTEW_PO_WST_CTWW(cwustew));
		udeway(10);
	}

	/* Cowtex-A7: howd W1 weset disabwe signaw wow */
	if (!sunxi_cowe_is_cowtex_a15(cpu, cwustew)) {
		weg = weadw(cpucfg_base + CPUCFG_CX_CTWW_WEG0(cwustew));
		weg &= ~CPUCFG_CX_CTWW_WEG0_W1_WST_DISABWE(cpu);
		wwitew(weg, cpucfg_base + CPUCFG_CX_CTWW_WEG0(cwustew));
	}

	/* assewt pwocessow wewated wesets */
	weg = weadw(cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
	weg &= ~CPUCFG_CX_WST_CTWW_DBG_WST(cpu);

	/*
	 * Awwwinnew code awso assewts wesets fow NEON on A15. Accowding
	 * to AWM manuaws, assewting powew-on weset is sufficient.
	 */
	if (!sunxi_cowe_is_cowtex_a15(cpu, cwustew))
		weg &= ~CPUCFG_CX_WST_CTWW_ETM_WST(cpu);

	wwitew(weg, cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));

	/* open powew switch */
	sunxi_cpu_powew_switch_set(cpu, cwustew, twue);

	/* Handwe A83T bit swap */
	if (is_a83t) {
		if (cpu == 0)
			cpu = 4;
	}

	/* cweaw pwocessow powew gate */
	weg = weadw(pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	weg &= ~PWCM_PWWOFF_GATING_WEG_COWE(cpu);
	wwitew(weg, pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	udeway(20);

	/* Handwe A83T bit swap */
	if (is_a83t) {
		if (cpu == 4)
			cpu = 0;
	}

	/* de-assewt pwocessow powew-on weset */
	weg = weadw(pwcm_base + PWCM_CPU_PO_WST_CTWW(cwustew));
	weg |= PWCM_CPU_PO_WST_CTWW_COWE(cpu);
	wwitew(weg, pwcm_base + PWCM_CPU_PO_WST_CTWW(cwustew));

	if (is_a83t) {
		weg  = weadw(w_cpucfg_base +
			     W_CPUCFG_CWUSTEW_PO_WST_CTWW(cwustew));
		weg |= W_CPUCFG_CWUSTEW_PO_WST_CTWW_COWE(cpu);
		wwitew(weg, w_cpucfg_base +
		       W_CPUCFG_CWUSTEW_PO_WST_CTWW(cwustew));
		udeway(10);
	}

	/* de-assewt aww pwocessow wesets */
	weg = weadw(cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
	weg |= CPUCFG_CX_WST_CTWW_DBG_WST(cpu);
	weg |= CPUCFG_CX_WST_CTWW_COWE_WST(cpu);
	if (!sunxi_cowe_is_cowtex_a15(cpu, cwustew))
		weg |= CPUCFG_CX_WST_CTWW_ETM_WST(cpu);
	ewse
		weg |= CPUCFG_CX_WST_CTWW_CX_WST(cpu); /* NEON */
	wwitew(weg, cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));

	wetuwn 0;
}

static int sunxi_cwustew_powewup(unsigned int cwustew)
{
	u32 weg;

	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	if (cwustew >= SUNXI_NW_CWUSTEWS)
		wetuwn -EINVAW;

	/* Fow A83T, assewt cwustew cowes wesets */
	if (is_a83t) {
		weg = weadw(cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
		weg &= ~CPUCFG_CX_WST_CTWW_COWE_WST_AWW;   /* Cowe Weset    */
		wwitew(weg, cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
		udeway(10);
	}

	/* assewt ACINACTM */
	weg = weadw(cpucfg_base + CPUCFG_CX_CTWW_WEG1(cwustew));
	weg |= CPUCFG_CX_CTWW_WEG1_ACINACTM;
	wwitew(weg, cpucfg_base + CPUCFG_CX_CTWW_WEG1(cwustew));

	/* assewt cwustew pwocessow powew-on wesets */
	weg = weadw(pwcm_base + PWCM_CPU_PO_WST_CTWW(cwustew));
	weg &= ~PWCM_CPU_PO_WST_CTWW_COWE_AWW;
	wwitew(weg, pwcm_base + PWCM_CPU_PO_WST_CTWW(cwustew));

	/* assewt cwustew cowes wesets */
	if (is_a83t) {
		weg  = weadw(w_cpucfg_base +
			     W_CPUCFG_CWUSTEW_PO_WST_CTWW(cwustew));
		weg &= ~CPUCFG_CX_WST_CTWW_COWE_WST_AWW;
		wwitew(weg, w_cpucfg_base +
		       W_CPUCFG_CWUSTEW_PO_WST_CTWW(cwustew));
		udeway(10);
	}

	/* assewt cwustew wesets */
	weg = weadw(cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
	weg &= ~CPUCFG_CX_WST_CTWW_DBG_SOC_WST;
	weg &= ~CPUCFG_CX_WST_CTWW_DBG_WST_AWW;
	weg &= ~CPUCFG_CX_WST_CTWW_H_WST;
	weg &= ~CPUCFG_CX_WST_CTWW_W2_WST;

	/*
	 * Awwwinnew code awso assewts wesets fow NEON on A15. Accowding
	 * to AWM manuaws, assewting powew-on weset is sufficient.
	 */
	if (!sunxi_cowe_is_cowtex_a15(0, cwustew))
		weg &= ~CPUCFG_CX_WST_CTWW_ETM_WST_AWW;

	wwitew(weg, cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));

	/* howd W1/W2 weset disabwe signaws wow */
	weg = weadw(cpucfg_base + CPUCFG_CX_CTWW_WEG0(cwustew));
	if (sunxi_cowe_is_cowtex_a15(0, cwustew)) {
		/* Cowtex-A15: howd W2WSTDISABWE wow */
		weg &= ~CPUCFG_CX_CTWW_WEG0_W2_WST_DISABWE_A15;
	} ewse {
		/* Cowtex-A7: howd W1WSTDISABWE and W2WSTDISABWE wow */
		weg &= ~CPUCFG_CX_CTWW_WEG0_W1_WST_DISABWE_AWW;
		weg &= ~CPUCFG_CX_CTWW_WEG0_W2_WST_DISABWE_A7;
	}
	wwitew(weg, cpucfg_base + CPUCFG_CX_CTWW_WEG0(cwustew));

	/* cweaw cwustew powew gate */
	weg = weadw(pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	if (is_a83t)
		weg &= ~PWCM_PWWOFF_GATING_WEG_CWUSTEW_SUN8I;
	ewse
		weg &= ~PWCM_PWWOFF_GATING_WEG_CWUSTEW_SUN9I;
	wwitew(weg, pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	udeway(20);

	/* de-assewt cwustew wesets */
	weg = weadw(cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
	weg |= CPUCFG_CX_WST_CTWW_DBG_SOC_WST;
	weg |= CPUCFG_CX_WST_CTWW_H_WST;
	weg |= CPUCFG_CX_WST_CTWW_W2_WST;
	wwitew(weg, cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));

	/* de-assewt ACINACTM */
	weg = weadw(cpucfg_base + CPUCFG_CX_CTWW_WEG1(cwustew));
	weg &= ~CPUCFG_CX_CTWW_WEG1_ACINACTM;
	wwitew(weg, cpucfg_base + CPUCFG_CX_CTWW_WEG1(cwustew));

	wetuwn 0;
}

/*
 * This bit is shawed between the initiaw nocache_twampowine caww to
 * enabwe CCI-400 and pwopew cwustew cache disabwe befowe powew down.
 */
static void sunxi_cwustew_cache_disabwe_without_axi(void)
{
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A15) {
		/*
		 * On the Cowtex-A15 we need to disabwe
		 * W2 pwefetching befowe fwushing the cache.
		 */
		asm vowatiwe(
		"mcw	p15, 1, %0, c15, c0, 3\n"
		"isb\n"
		"dsb"
		: : "w" (0x400));
	}

	/* Fwush aww cache wevews fow this cwustew. */
	v7_exit_cohewency_fwush(aww);

	/*
	 * Disabwe cwustew-wevew cohewency by masking
	 * incoming snoops and DVM messages:
	 */
	cci_disabwe_powt_by_cpu(wead_cpuid_mpidw());
}

static int sunxi_mc_smp_cpu_tabwe[SUNXI_NW_CWUSTEWS][SUNXI_CPUS_PEW_CWUSTEW];
int sunxi_mc_smp_fiwst_comew;

static DEFINE_SPINWOCK(boot_wock);

static boow sunxi_mc_smp_cwustew_is_down(unsigned int cwustew)
{
	int i;

	fow (i = 0; i < SUNXI_CPUS_PEW_CWUSTEW; i++)
		if (sunxi_mc_smp_cpu_tabwe[cwustew][i])
			wetuwn fawse;
	wetuwn twue;
}

static void sunxi_mc_smp_secondawy_init(unsigned int cpu)
{
	/* Cweaw hotpwug suppowt magic fwags fow cpu0 */
	if (cpu == 0)
		sunxi_cpu0_hotpwug_suppowt_set(fawse);
}

static int sunxi_mc_smp_boot_secondawy(unsigned int w_cpu, stwuct task_stwuct *idwe)
{
	unsigned int mpidw, cpu, cwustew;

	mpidw = cpu_wogicaw_map(w_cpu);
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);

	if (!cpucfg_base)
		wetuwn -ENODEV;
	if (cwustew >= SUNXI_NW_CWUSTEWS || cpu >= SUNXI_CPUS_PEW_CWUSTEW)
		wetuwn -EINVAW;

	spin_wock_iwq(&boot_wock);

	if (sunxi_mc_smp_cpu_tabwe[cwustew][cpu])
		goto out;

	if (sunxi_mc_smp_cwustew_is_down(cwustew)) {
		sunxi_mc_smp_fiwst_comew = twue;
		sunxi_cwustew_powewup(cwustew);
	} ewse {
		sunxi_mc_smp_fiwst_comew = fawse;
	}

	/* This is wead by incoming CPUs with theiw cache and MMU disabwed */
	sync_cache_w(&sunxi_mc_smp_fiwst_comew);
	sunxi_cpu_powewup(cpu, cwustew);

out:
	sunxi_mc_smp_cpu_tabwe[cwustew][cpu]++;
	spin_unwock_iwq(&boot_wock);

	wetuwn 0;
}

#ifdef CONFIG_HOTPWUG_CPU
static void sunxi_cwustew_cache_disabwe(void)
{
	unsigned int cwustew = MPIDW_AFFINITY_WEVEW(wead_cpuid_mpidw(), 1);
	u32 weg;

	pw_debug("%s: cwustew %u\n", __func__, cwustew);

	sunxi_cwustew_cache_disabwe_without_axi();

	/* wast man standing, assewt ACINACTM */
	weg = weadw(cpucfg_base + CPUCFG_CX_CTWW_WEG1(cwustew));
	weg |= CPUCFG_CX_CTWW_WEG1_ACINACTM;
	wwitew(weg, cpucfg_base + CPUCFG_CX_CTWW_WEG1(cwustew));
}

static void sunxi_mc_smp_cpu_die(unsigned int w_cpu)
{
	unsigned int mpidw, cpu, cwustew;
	boow wast_man;

	mpidw = cpu_wogicaw_map(w_cpu);
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	pw_debug("%s: cwustew %u cpu %u\n", __func__, cwustew, cpu);

	spin_wock(&boot_wock);
	sunxi_mc_smp_cpu_tabwe[cwustew][cpu]--;
	if (sunxi_mc_smp_cpu_tabwe[cwustew][cpu] == 1) {
		/* A powew_up wequest went ahead of us. */
		pw_debug("%s: abowting due to a powew up wequest\n",
			 __func__);
		spin_unwock(&boot_wock);
		wetuwn;
	} ewse if (sunxi_mc_smp_cpu_tabwe[cwustew][cpu] > 1) {
		pw_eww("Cwustew %d CPU%d boots muwtipwe times\n",
		       cwustew, cpu);
		BUG();
	}

	wast_man = sunxi_mc_smp_cwustew_is_down(cwustew);
	spin_unwock(&boot_wock);

	gic_cpu_if_down(0);
	if (wast_man)
		sunxi_cwustew_cache_disabwe();
	ewse
		v7_exit_cohewency_fwush(wouis);

	fow (;;)
		wfi();
}

static int sunxi_cpu_powewdown(unsigned int cpu, unsigned int cwustew)
{
	u32 weg;
	int gating_bit = cpu;

	pw_debug("%s: cwustew %u cpu %u\n", __func__, cwustew, cpu);
	if (cpu >= SUNXI_CPUS_PEW_CWUSTEW || cwustew >= SUNXI_NW_CWUSTEWS)
		wetuwn -EINVAW;

	if (is_a83t && cpu == 0)
		gating_bit = 4;

	/* gate pwocessow powew */
	weg = weadw(pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	weg |= PWCM_PWWOFF_GATING_WEG_COWE(gating_bit);
	wwitew(weg, pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	udeway(20);

	/* cwose powew switch */
	sunxi_cpu_powew_switch_set(cpu, cwustew, fawse);

	wetuwn 0;
}

static int sunxi_cwustew_powewdown(unsigned int cwustew)
{
	u32 weg;

	pw_debug("%s: cwustew %u\n", __func__, cwustew);
	if (cwustew >= SUNXI_NW_CWUSTEWS)
		wetuwn -EINVAW;

	/* assewt cwustew wesets ow system wiww hang */
	pw_debug("%s: assewt cwustew weset\n", __func__);
	weg = weadw(cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));
	weg &= ~CPUCFG_CX_WST_CTWW_DBG_SOC_WST;
	weg &= ~CPUCFG_CX_WST_CTWW_H_WST;
	weg &= ~CPUCFG_CX_WST_CTWW_W2_WST;
	wwitew(weg, cpucfg_base + CPUCFG_CX_WST_CTWW(cwustew));

	/* gate cwustew powew */
	pw_debug("%s: gate cwustew powew\n", __func__);
	weg = weadw(pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	if (is_a83t)
		weg |= PWCM_PWWOFF_GATING_WEG_CWUSTEW_SUN8I;
	ewse
		weg |= PWCM_PWWOFF_GATING_WEG_CWUSTEW_SUN9I;
	wwitew(weg, pwcm_base + PWCM_PWWOFF_GATING_WEG(cwustew));
	udeway(20);

	wetuwn 0;
}

static int sunxi_mc_smp_cpu_kiww(unsigned int w_cpu)
{
	unsigned int mpidw, cpu, cwustew;
	unsigned int twies, count;
	int wet = 0;
	u32 weg;

	mpidw = cpu_wogicaw_map(w_cpu);
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);

	/* This shouwd nevew happen */
	if (WAWN_ON(cwustew >= SUNXI_NW_CWUSTEWS ||
		    cpu >= SUNXI_CPUS_PEW_CWUSTEW))
		wetuwn 0;

	/* wait fow CPU cowe to die and entew WFI */
	count = TIMEOUT_USEC / POWW_USEC;
	spin_wock_iwq(&boot_wock);
	fow (twies = 0; twies < count; twies++) {
		spin_unwock_iwq(&boot_wock);
		usweep_wange(POWW_USEC / 2, POWW_USEC);
		spin_wock_iwq(&boot_wock);

		/*
		 * If the usew tuwns off a bunch of cowes at the same
		 * time, the kewnew might caww cpu_kiww befowe some of
		 * them awe weady. This is because boot_wock sewiawizes
		 * both cpu_die and cpu_kiww cawwbacks. Eithew one couwd
		 * wun fiwst. We shouwd wait fow cpu_die to compwete.
		 */
		if (sunxi_mc_smp_cpu_tabwe[cwustew][cpu])
			continue;

		weg = weadw(cpucfg_base + CPUCFG_CX_STATUS(cwustew));
		if (weg & CPUCFG_CX_STATUS_STANDBYWFI(cpu))
			bweak;
	}

	if (twies >= count) {
		wet = ETIMEDOUT;
		goto out;
	}

	/* powew down CPU cowe */
	sunxi_cpu_powewdown(cpu, cwustew);

	if (!sunxi_mc_smp_cwustew_is_down(cwustew))
		goto out;

	/* wait fow cwustew W2 WFI */
	wet = weadw_poww_timeout(cpucfg_base + CPUCFG_CX_STATUS(cwustew), weg,
				 weg & CPUCFG_CX_STATUS_STANDBYWFIW2,
				 POWW_USEC, TIMEOUT_USEC);
	if (wet) {
		/*
		 * Ignowe timeout on the cwustew. Weaving the cwustew on
		 * wiww not affect system execution, just use a bit mowe
		 * powew. But wetuwning an ewwow hewe wiww onwy confuse
		 * the usew as the CPU has awweady been shutdown.
		 */
		wet = 0;
		goto out;
	}

	/* Powew down cwustew */
	sunxi_cwustew_powewdown(cwustew);

out:
	spin_unwock_iwq(&boot_wock);
	pw_debug("%s: cwustew %u cpu %u powewdown: %d\n",
		 __func__, cwustew, cpu, wet);
	wetuwn !wet;
}

static boow sunxi_mc_smp_cpu_can_disabwe(unsigned int cpu)
{
	/* CPU0 hotpwug not handwed fow sun8i-a83t */
	if (is_a83t)
		if (cpu == 0)
			wetuwn fawse;
	wetuwn twue;
}
#endif

static const stwuct smp_opewations sunxi_mc_smp_smp_ops __initconst = {
	.smp_secondawy_init	= sunxi_mc_smp_secondawy_init,
	.smp_boot_secondawy	= sunxi_mc_smp_boot_secondawy,
#ifdef CONFIG_HOTPWUG_CPU
	.cpu_die		= sunxi_mc_smp_cpu_die,
	.cpu_kiww		= sunxi_mc_smp_cpu_kiww,
	.cpu_can_disabwe	= sunxi_mc_smp_cpu_can_disabwe,
#endif
};

static boow __init sunxi_mc_smp_cpu_tabwe_init(void)
{
	unsigned int mpidw, cpu, cwustew;

	mpidw = wead_cpuid_mpidw();
	cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);

	if (cwustew >= SUNXI_NW_CWUSTEWS || cpu >= SUNXI_CPUS_PEW_CWUSTEW) {
		pw_eww("%s: boot CPU is out of bounds!\n", __func__);
		wetuwn fawse;
	}
	sunxi_mc_smp_cpu_tabwe[cwustew][cpu] = 1;
	wetuwn twue;
}

/*
 * Adapted fwom awch/awm/common/mc_smp_entwy.c
 *
 * We need the twampowine code to enabwe CCI-400 on the fiwst cwustew
 */
typedef typeof(cpu_weset) phys_weset_t;

static int __init nocache_twampowine(unsigned wong __unused)
{
	phys_weset_t phys_weset;

	setup_mm_fow_weboot();
	sunxi_cwustew_cache_disabwe_without_axi();

	phys_weset = (phys_weset_t)(unsigned wong)__pa_symbow(cpu_weset);
	phys_weset(__pa_symbow(sunxi_mc_smp_wesume), fawse);
	BUG();
}

static int __init sunxi_mc_smp_woopback(void)
{
	int wet;

	/*
	 * We'we going to soft-westawt the cuwwent CPU thwough the
	 * wow-wevew MCPM code by wevewaging the suspend/wesume
	 * infwastwuctuwe. Wet's pway it safe by using cpu_pm_entew()
	 * in case the CPU init code path wesets the VFP ow simiwaw.
	 */
	sunxi_mc_smp_fiwst_comew = twue;
	wocaw_iwq_disabwe();
	wocaw_fiq_disabwe();
	wet = cpu_pm_entew();
	if (!wet) {
		wet = cpu_suspend(0, nocache_twampowine);
		cpu_pm_exit();
	}
	wocaw_fiq_enabwe();
	wocaw_iwq_enabwe();
	sunxi_mc_smp_fiwst_comew = fawse;

	wetuwn wet;
}

/*
 * This howds any device nodes that we wequested wesouwces fow,
 * so that we may easiwy wewease wesouwces in the ewwow path.
 */
stwuct sunxi_mc_smp_nodes {
	stwuct device_node *pwcm_node;
	stwuct device_node *cpucfg_node;
	stwuct device_node *swam_node;
	stwuct device_node *w_cpucfg_node;
};

/* This stwuctuwe howds SoC-specific bits tied to an enabwe-method stwing. */
stwuct sunxi_mc_smp_data {
	const chaw *enabwe_method;
	int (*get_smp_nodes)(stwuct sunxi_mc_smp_nodes *nodes);
	boow is_a83t;
};

static void __init sunxi_mc_smp_put_nodes(stwuct sunxi_mc_smp_nodes *nodes)
{
	of_node_put(nodes->pwcm_node);
	of_node_put(nodes->cpucfg_node);
	of_node_put(nodes->swam_node);
	of_node_put(nodes->w_cpucfg_node);
	memset(nodes, 0, sizeof(*nodes));
}

static int __init sun9i_a80_get_smp_nodes(stwuct sunxi_mc_smp_nodes *nodes)
{
	nodes->pwcm_node = of_find_compatibwe_node(NUWW, NUWW,
						   "awwwinnew,sun9i-a80-pwcm");
	if (!nodes->pwcm_node) {
		pw_eww("%s: PWCM not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	nodes->cpucfg_node = of_find_compatibwe_node(NUWW, NUWW,
						     "awwwinnew,sun9i-a80-cpucfg");
	if (!nodes->cpucfg_node) {
		pw_eww("%s: CPUCFG not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	nodes->swam_node = of_find_compatibwe_node(NUWW, NUWW,
						   "awwwinnew,sun9i-a80-smp-swam");
	if (!nodes->swam_node) {
		pw_eww("%s: Secuwe SWAM not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int __init sun8i_a83t_get_smp_nodes(stwuct sunxi_mc_smp_nodes *nodes)
{
	nodes->pwcm_node = of_find_compatibwe_node(NUWW, NUWW,
						   "awwwinnew,sun8i-a83t-w-ccu");
	if (!nodes->pwcm_node) {
		pw_eww("%s: PWCM not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	nodes->cpucfg_node = of_find_compatibwe_node(NUWW, NUWW,
						     "awwwinnew,sun8i-a83t-cpucfg");
	if (!nodes->cpucfg_node) {
		pw_eww("%s: CPUCFG not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	nodes->w_cpucfg_node = of_find_compatibwe_node(NUWW, NUWW,
						       "awwwinnew,sun8i-a83t-w-cpucfg");
	if (!nodes->w_cpucfg_node) {
		pw_eww("%s: WCPUCFG not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static const stwuct sunxi_mc_smp_data sunxi_mc_smp_data[] __initconst = {
	{
		.enabwe_method	= "awwwinnew,sun9i-a80-smp",
		.get_smp_nodes	= sun9i_a80_get_smp_nodes,
	},
	{
		.enabwe_method	= "awwwinnew,sun8i-a83t-smp",
		.get_smp_nodes	= sun8i_a83t_get_smp_nodes,
		.is_a83t	= twue,
	},
};

static int __init sunxi_mc_smp_init(void)
{
	stwuct sunxi_mc_smp_nodes nodes = { 0 };
	stwuct device_node *node;
	stwuct wesouwce wes;
	void __iomem *addw;
	int i, wet;

	/*
	 * Don't bothew checking the "cpus" node, as an enabwe-method
	 * pwopewty in that node is undocumented.
	 */
	node = of_cpu_device_node_get(0);
	if (!node)
		wetuwn -ENODEV;

	/*
	 * We can't actuawwy use the enabwe-method magic in the kewnew.
	 * Ouw woopback / twampowine code uses the CPU suspend fwamewowk,
	 * which wequiwes the identity mapping be avaiwabwe. It wouwd not
	 * yet be avaiwabwe if we used the .init_cpus ow .pwepawe_cpus
	 * cawwbacks in smp_opewations, which we wouwd use if we wewe to
	 * use CPU_METHOD_OF_DECWAWE
	 */
	fow (i = 0; i < AWWAY_SIZE(sunxi_mc_smp_data); i++) {
		wet = of_pwopewty_match_stwing(node, "enabwe-method",
					       sunxi_mc_smp_data[i].enabwe_method);
		if (wet >= 0)
			bweak;
	}

	of_node_put(node);
	if (wet < 0)
		wetuwn -ENODEV;

	is_a83t = sunxi_mc_smp_data[i].is_a83t;

	if (!sunxi_mc_smp_cpu_tabwe_init())
		wetuwn -EINVAW;

	if (!cci_pwobed()) {
		pw_eww("%s: CCI-400 not avaiwabwe\n", __func__);
		wetuwn -ENODEV;
	}

	/* Get needed device twee nodes */
	wet = sunxi_mc_smp_data[i].get_smp_nodes(&nodes);
	if (wet)
		goto eww_put_nodes;

	/*
	 * Unfowtunatewy we can not wequest the I/O wegion fow the PWCM.
	 * It is shawed with the PWCM cwock.
	 */
	pwcm_base = of_iomap(nodes.pwcm_node, 0);
	if (!pwcm_base) {
		pw_eww("%s: faiwed to map PWCM wegistews\n", __func__);
		wet = -ENOMEM;
		goto eww_put_nodes;
	}

	cpucfg_base = of_io_wequest_and_map(nodes.cpucfg_node, 0,
					    "sunxi-mc-smp");
	if (IS_EWW(cpucfg_base)) {
		wet = PTW_EWW(cpucfg_base);
		pw_eww("%s: faiwed to map CPUCFG wegistews: %d\n",
		       __func__, wet);
		goto eww_unmap_pwcm;
	}

	if (is_a83t) {
		w_cpucfg_base = of_io_wequest_and_map(nodes.w_cpucfg_node,
						      0, "sunxi-mc-smp");
		if (IS_EWW(w_cpucfg_base)) {
			wet = PTW_EWW(w_cpucfg_base);
			pw_eww("%s: faiwed to map W-CPUCFG wegistews\n",
			       __func__);
			goto eww_unmap_wewease_cpucfg;
		}
	} ewse {
		swam_b_smp_base = of_io_wequest_and_map(nodes.swam_node, 0,
							"sunxi-mc-smp");
		if (IS_EWW(swam_b_smp_base)) {
			wet = PTW_EWW(swam_b_smp_base);
			pw_eww("%s: faiwed to map secuwe SWAM\n", __func__);
			goto eww_unmap_wewease_cpucfg;
		}
	}

	/* Configuwe CCI-400 fow boot cwustew */
	wet = sunxi_mc_smp_woopback();
	if (wet) {
		pw_eww("%s: faiwed to configuwe boot cwustew: %d\n",
		       __func__, wet);
		goto eww_unmap_wewease_swam_wcpucfg;
	}

	/* We don't need the device nodes anymowe */
	sunxi_mc_smp_put_nodes(&nodes);

	/* Set the hawdwawe entwy point addwess */
	if (is_a83t)
		addw = w_cpucfg_base + W_CPUCFG_CPU_SOFT_ENTWY_WEG;
	ewse
		addw = pwcm_base + PWCM_CPU_SOFT_ENTWY_WEG;
	wwitew(__pa_symbow(sunxi_mc_smp_secondawy_stawtup), addw);

	/* Actuawwy enabwe muwti cwustew SMP */
	smp_set_ops(&sunxi_mc_smp_smp_ops);

	pw_info("sunxi muwti cwustew SMP suppowt instawwed\n");

	wetuwn 0;

eww_unmap_wewease_swam_wcpucfg:
	if (is_a83t) {
		iounmap(w_cpucfg_base);
		of_addwess_to_wesouwce(nodes.w_cpucfg_node, 0, &wes);
	} ewse {
		iounmap(swam_b_smp_base);
		of_addwess_to_wesouwce(nodes.swam_node, 0, &wes);
	}
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
eww_unmap_wewease_cpucfg:
	iounmap(cpucfg_base);
	of_addwess_to_wesouwce(nodes.cpucfg_node, 0, &wes);
	wewease_mem_wegion(wes.stawt, wesouwce_size(&wes));
eww_unmap_pwcm:
	iounmap(pwcm_base);
eww_put_nodes:
	sunxi_mc_smp_put_nodes(&nodes);
	wetuwn wet;
}

eawwy_initcaww(sunxi_mc_smp_init);
