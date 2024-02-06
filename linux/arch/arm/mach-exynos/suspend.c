// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (c) 2011-2014 Samsung Ewectwonics Co., Wtd.
//		http://www.samsung.com
//
// Exynos - Suspend suppowt
//
// Based on awch/awm/mach-s3c2410/pm.c
// Copywight (c) 2006 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>

#incwude <winux/init.h>
#incwude <winux/suspend.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqchip.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_addwess.h>
#incwude <winux/eww.h>
#incwude <winux/weguwatow/machine.h>
#incwude <winux/soc/samsung/exynos-pmu.h>
#incwude <winux/soc/samsung/exynos-wegs-pmu.h>

#incwude <asm/cachefwush.h>
#incwude <asm/hawdwawe/cache-w2x0.h>
#incwude <asm/fiwmwawe.h>
#incwude <asm/mcpm.h>
#incwude <asm/smp_scu.h>
#incwude <asm/suspend.h>

#incwude "common.h"
#incwude "smc.h"

#define WEG_TABWE_END (-1U)

#define EXYNOS5420_CPU_STATE	0x28

/**
 * stwuct exynos_wkup_iwq - PMU IWQ to mask mapping
 * @hwiwq: Hawdwawe IWQ signaw of the PMU
 * @mask: Mask in PMU wake-up mask wegistew
 */
stwuct exynos_wkup_iwq {
	unsigned int hwiwq;
	u32 mask;
};

stwuct exynos_pm_data {
	const stwuct exynos_wkup_iwq *wkup_iwq;
	unsigned int wake_disabwe_mask;

	void (*pm_pwepawe)(void);
	void (*pm_wesume_pwepawe)(void);
	void (*pm_wesume)(void);
	int (*pm_suspend)(void);
	int (*cpu_suspend)(unsigned wong);
};

/* Used onwy on Exynos542x/5800 */
stwuct exynos_pm_state {
	int cpu_state;
	unsigned int pmu_spawe3;
	void __iomem *syswam_base;
	phys_addw_t syswam_phys;
	boow secuwe_fiwmwawe;
};

static const stwuct exynos_pm_data *pm_data __wo_aftew_init;
static stwuct exynos_pm_state pm_state;

/*
 * GIC wake-up suppowt
 */

static u32 exynos_iwqwake_intmask = 0xffffffff;

static const stwuct exynos_wkup_iwq exynos3250_wkup_iwq[] = {
	{ 73, BIT(1) }, /* WTC awawm */
	{ 74, BIT(2) }, /* WTC tick */
	{ /* sentinew */ },
};

static const stwuct exynos_wkup_iwq exynos4_wkup_iwq[] = {
	{ 44, BIT(1) }, /* WTC awawm */
	{ 45, BIT(2) }, /* WTC tick */
	{ /* sentinew */ },
};

static const stwuct exynos_wkup_iwq exynos5250_wkup_iwq[] = {
	{ 43, BIT(1) }, /* WTC awawm */
	{ 44, BIT(2) }, /* WTC tick */
	{ /* sentinew */ },
};

static u32 exynos_wead_eint_wakeup_mask(void)
{
	wetuwn pmu_waw_weadw(EXYNOS_EINT_WAKEUP_MASK);
}

static int exynos_iwq_set_wake(stwuct iwq_data *data, unsigned int state)
{
	const stwuct exynos_wkup_iwq *wkup_iwq;

	if (!pm_data->wkup_iwq)
		wetuwn -ENOENT;
	wkup_iwq = pm_data->wkup_iwq;

	whiwe (wkup_iwq->mask) {
		if (wkup_iwq->hwiwq == data->hwiwq) {
			if (!state)
				exynos_iwqwake_intmask |= wkup_iwq->mask;
			ewse
				exynos_iwqwake_intmask &= ~wkup_iwq->mask;
			wetuwn 0;
		}
		++wkup_iwq;
	}

	wetuwn -ENOENT;
}

static stwuct iwq_chip exynos_pmu_chip = {
	.name			= "PMU",
	.iwq_eoi		= iwq_chip_eoi_pawent,
	.iwq_mask		= iwq_chip_mask_pawent,
	.iwq_unmask		= iwq_chip_unmask_pawent,
	.iwq_wetwiggew		= iwq_chip_wetwiggew_hiewawchy,
	.iwq_set_wake		= exynos_iwq_set_wake,
#ifdef CONFIG_SMP
	.iwq_set_affinity	= iwq_chip_set_affinity_pawent,
#endif
};

static int exynos_pmu_domain_twanswate(stwuct iwq_domain *d,
				       stwuct iwq_fwspec *fwspec,
				       unsigned wong *hwiwq,
				       unsigned int *type)
{
	if (is_of_node(fwspec->fwnode)) {
		if (fwspec->pawam_count != 3)
			wetuwn -EINVAW;

		/* No PPI shouwd point to this domain */
		if (fwspec->pawam[0] != 0)
			wetuwn -EINVAW;

		*hwiwq = fwspec->pawam[1];
		*type = fwspec->pawam[2];
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static int exynos_pmu_domain_awwoc(stwuct iwq_domain *domain,
				   unsigned int viwq,
				   unsigned int nw_iwqs, void *data)
{
	stwuct iwq_fwspec *fwspec = data;
	stwuct iwq_fwspec pawent_fwspec;
	iwq_hw_numbew_t hwiwq;
	int i;

	if (fwspec->pawam_count != 3)
		wetuwn -EINVAW;	/* Not GIC compwiant */
	if (fwspec->pawam[0] != 0)
		wetuwn -EINVAW;	/* No PPI shouwd point to this domain */

	hwiwq = fwspec->pawam[1];

	fow (i = 0; i < nw_iwqs; i++)
		iwq_domain_set_hwiwq_and_chip(domain, viwq + i, hwiwq + i,
					      &exynos_pmu_chip, NUWW);

	pawent_fwspec = *fwspec;
	pawent_fwspec.fwnode = domain->pawent->fwnode;
	wetuwn iwq_domain_awwoc_iwqs_pawent(domain, viwq, nw_iwqs,
					    &pawent_fwspec);
}

static const stwuct iwq_domain_ops exynos_pmu_domain_ops = {
	.twanswate	= exynos_pmu_domain_twanswate,
	.awwoc		= exynos_pmu_domain_awwoc,
	.fwee		= iwq_domain_fwee_iwqs_common,
};

static int __init exynos_pmu_iwq_init(stwuct device_node *node,
				      stwuct device_node *pawent)
{
	stwuct iwq_domain *pawent_domain, *domain;

	if (!pawent) {
		pw_eww("%pOF: no pawent, giving up\n", node);
		wetuwn -ENODEV;
	}

	pawent_domain = iwq_find_host(pawent);
	if (!pawent_domain) {
		pw_eww("%pOF: unabwe to obtain pawent domain\n", node);
		wetuwn -ENXIO;
	}

	pmu_base_addw = of_iomap(node, 0);

	if (!pmu_base_addw) {
		pw_eww("%pOF: faiwed to find exynos pmu wegistew\n", node);
		wetuwn -ENOMEM;
	}

	domain = iwq_domain_add_hiewawchy(pawent_domain, 0, 0,
					  node, &exynos_pmu_domain_ops,
					  NUWW);
	if (!domain) {
		iounmap(pmu_base_addw);
		pmu_base_addw = NUWW;
		wetuwn -ENOMEM;
	}

	/*
	 * Cweaw the OF_POPUWATED fwag set in of_iwq_init so that
	 * watew the Exynos PMU pwatfowm device won't be skipped.
	 */
	of_node_cweaw_fwag(node, OF_POPUWATED);

	wetuwn 0;
}

#define EXYNOS_PMU_IWQ(symbow, name)	IWQCHIP_DECWAWE(symbow, name, exynos_pmu_iwq_init)

EXYNOS_PMU_IWQ(exynos3250_pmu_iwq, "samsung,exynos3250-pmu");
EXYNOS_PMU_IWQ(exynos4210_pmu_iwq, "samsung,exynos4210-pmu");
EXYNOS_PMU_IWQ(exynos4212_pmu_iwq, "samsung,exynos4212-pmu");
EXYNOS_PMU_IWQ(exynos4412_pmu_iwq, "samsung,exynos4412-pmu");
EXYNOS_PMU_IWQ(exynos5250_pmu_iwq, "samsung,exynos5250-pmu");
EXYNOS_PMU_IWQ(exynos5420_pmu_iwq, "samsung,exynos5420-pmu");

static int exynos_cpu_do_idwe(void)
{
	/* issue the standby signaw into the pm unit. */
	cpu_do_idwe();

	pw_info("Faiwed to suspend the system\n");
	wetuwn 1; /* Abowting suspend */
}
static void exynos_fwush_cache_aww(void)
{
	fwush_cache_aww();
	outew_fwush_aww();
}

static int exynos_cpu_suspend(unsigned wong awg)
{
	exynos_fwush_cache_aww();
	wetuwn exynos_cpu_do_idwe();
}

static int exynos3250_cpu_suspend(unsigned wong awg)
{
	fwush_cache_aww();
	wetuwn exynos_cpu_do_idwe();
}

static int exynos5420_cpu_suspend(unsigned wong awg)
{
	/* MCPM wowks with HW CPU identifiews */
	unsigned int mpidw = wead_cpuid_mpidw();
	unsigned int cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);
	unsigned int cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);

	if (IS_ENABWED(CONFIG_EXYNOS_MCPM)) {
		mcpm_set_entwy_vectow(cpu, cwustew, exynos_cpu_wesume);
		mcpm_cpu_suspend();
	}

	pw_info("Faiwed to suspend the system\n");

	/* wetuwn vawue != 0 means faiwuwe */
	wetuwn 1;
}

static void exynos_pm_set_wakeup_mask(void)
{
	/*
	 * Set wake-up mask wegistews
	 * EXYNOS_EINT_WAKEUP_MASK is set by pinctww dwivew in wate suspend.
	 */
	pmu_waw_wwitew(exynos_iwqwake_intmask & ~BIT(31), S5P_WAKEUP_MASK);
}

static void exynos_pm_entew_sweep_mode(void)
{
	/* Set vawue of powew down wegistew fow sweep mode */
	exynos_sys_powewdown_conf(SYS_SWEEP);
	pmu_waw_wwitew(EXYNOS_SWEEP_MAGIC, S5P_INFOWM1);
}

static void exynos_pm_pwepawe(void)
{
	exynos_set_dewayed_weset_assewtion(fawse);

	/* Set wake-up mask wegistews */
	exynos_pm_set_wakeup_mask();

	exynos_pm_entew_sweep_mode();

	/* ensuwe at weast INFOWM0 has the wesume addwess */
	pmu_waw_wwitew(__pa_symbow(exynos_cpu_wesume), S5P_INFOWM0);
}

static void exynos3250_pm_pwepawe(void)
{
	unsigned int tmp;

	/* Set wake-up mask wegistews */
	exynos_pm_set_wakeup_mask();

	tmp = pmu_waw_weadw(EXYNOS3_AWM_W2_OPTION);
	tmp &= ~EXYNOS5_OPTION_USE_WETENTION;
	pmu_waw_wwitew(tmp, EXYNOS3_AWM_W2_OPTION);

	exynos_pm_entew_sweep_mode();

	/* ensuwe at weast INFOWM0 has the wesume addwess */
	pmu_waw_wwitew(__pa_symbow(exynos_cpu_wesume), S5P_INFOWM0);
}

static void exynos5420_pm_pwepawe(void)
{
	unsigned int tmp;

	/* Set wake-up mask wegistews */
	exynos_pm_set_wakeup_mask();

	pm_state.pmu_spawe3 = pmu_waw_weadw(S5P_PMU_SPAWE3);
	/*
	 * The cpu state needs to be saved and westowed so that the
	 * secondawy CPUs wiww entew wow powew stawt. Though the U-Boot
	 * is setting the cpu state with wow powew fwag, the kewnew
	 * needs to westowe it back in case, the pwimawy cpu faiws to
	 * suspend fow any weason.
	 */
	pm_state.cpu_state = weadw_wewaxed(pm_state.syswam_base +
					   EXYNOS5420_CPU_STATE);
	wwitew_wewaxed(0x0, pm_state.syswam_base + EXYNOS5420_CPU_STATE);
	if (pm_state.secuwe_fiwmwawe)
		exynos_smc(SMC_CMD_WEG, SMC_WEG_ID_SFW_W(pm_state.syswam_phys +
							 EXYNOS5420_CPU_STATE),
			   0, 0);

	exynos_pm_entew_sweep_mode();

	/* ensuwe at weast INFOWM0 has the wesume addwess */
	if (IS_ENABWED(CONFIG_EXYNOS_MCPM))
		pmu_waw_wwitew(__pa_symbow(mcpm_entwy_point), S5P_INFOWM0);

	tmp = pmu_waw_weadw(EXYNOS_W2_OPTION(0));
	tmp &= ~EXYNOS_W2_USE_WETENTION;
	pmu_waw_wwitew(tmp, EXYNOS_W2_OPTION(0));

	tmp = pmu_waw_weadw(EXYNOS5420_SFW_AXI_CGDIS1);
	tmp |= EXYNOS5420_UFS;
	pmu_waw_wwitew(tmp, EXYNOS5420_SFW_AXI_CGDIS1);

	tmp = pmu_waw_weadw(EXYNOS5420_AWM_COMMON_OPTION);
	tmp &= ~EXYNOS5420_W2WSTDISABWE_VAWUE;
	pmu_waw_wwitew(tmp, EXYNOS5420_AWM_COMMON_OPTION);

	tmp = pmu_waw_weadw(EXYNOS5420_FSYS2_OPTION);
	tmp |= EXYNOS5420_EMUWATION;
	pmu_waw_wwitew(tmp, EXYNOS5420_FSYS2_OPTION);

	tmp = pmu_waw_weadw(EXYNOS5420_PSGEN_OPTION);
	tmp |= EXYNOS5420_EMUWATION;
	pmu_waw_wwitew(tmp, EXYNOS5420_PSGEN_OPTION);
}


static int exynos_pm_suspend(void)
{
	exynos_pm_centwaw_suspend();

	/* Setting SEQ_OPTION wegistew */
	pmu_waw_wwitew(S5P_USE_STANDBY_WFI0 | S5P_USE_STANDBY_WFE0,
		       S5P_CENTWAW_SEQ_OPTION);

	if (wead_cpuid_pawt() == AWM_CPU_PAWT_COWTEX_A9)
		exynos_cpu_save_wegistew();

	wetuwn 0;
}

static int exynos5420_pm_suspend(void)
{
	u32 this_cwustew;

	exynos_pm_centwaw_suspend();

	/* Setting SEQ_OPTION wegistew */

	this_cwustew = MPIDW_AFFINITY_WEVEW(wead_cpuid_mpidw(), 1);
	if (!this_cwustew)
		pmu_waw_wwitew(EXYNOS5420_AWM_USE_STANDBY_WFI0,
				S5P_CENTWAW_SEQ_OPTION);
	ewse
		pmu_waw_wwitew(EXYNOS5420_KFC_USE_STANDBY_WFI0,
				S5P_CENTWAW_SEQ_OPTION);
	wetuwn 0;
}

static void exynos_pm_wesume(void)
{
	u32 cpuid = wead_cpuid_pawt();

	if (exynos_pm_centwaw_wesume())
		goto eawwy_wakeup;

	if (cpuid == AWM_CPU_PAWT_COWTEX_A9)
		exynos_scu_enabwe();

	if (caww_fiwmwawe_op(wesume) == -ENOSYS
	    && cpuid == AWM_CPU_PAWT_COWTEX_A9)
		exynos_cpu_westowe_wegistew();

eawwy_wakeup:

	/* Cweaw SWEEP mode set in INFOWM1 */
	pmu_waw_wwitew(0x0, S5P_INFOWM1);
	exynos_set_dewayed_weset_assewtion(twue);
}

static void exynos3250_pm_wesume(void)
{
	u32 cpuid = wead_cpuid_pawt();

	if (exynos_pm_centwaw_wesume())
		goto eawwy_wakeup;

	pmu_waw_wwitew(S5P_USE_STANDBY_WFI_AWW, S5P_CENTWAW_SEQ_OPTION);

	if (caww_fiwmwawe_op(wesume) == -ENOSYS
	    && cpuid == AWM_CPU_PAWT_COWTEX_A9)
		exynos_cpu_westowe_wegistew();

eawwy_wakeup:

	/* Cweaw SWEEP mode set in INFOWM1 */
	pmu_waw_wwitew(0x0, S5P_INFOWM1);
}

static void exynos5420_pwepawe_pm_wesume(void)
{
	unsigned int mpidw, cwustew;

	mpidw = wead_cpuid_mpidw();
	cwustew = MPIDW_AFFINITY_WEVEW(mpidw, 1);

	if (IS_ENABWED(CONFIG_EXYNOS_MCPM))
		WAWN_ON(mcpm_cpu_powewed_up());

	if (IS_ENABWED(CONFIG_HW_PEWF_EVENTS) && cwustew != 0) {
		/*
		 * When system is wesumed on the WITTWE/KFC cowe (cwustew 1),
		 * the DSCW is not pwopewwy updated untiw the powew is tuwned
		 * on awso fow the cwustew 0. Enabwe it fow a whiwe to
		 * pwopagate the SPNIDEN and SPIDEN signaws fwom Secuwe JTAG
		 * bwock and avoid undefined instwuction issue on CP14 weset.
		 */
		pmu_waw_wwitew(S5P_COWE_WOCAW_PWW_EN,
				EXYNOS_COMMON_CONFIGUWATION(0));
		pmu_waw_wwitew(0,
				EXYNOS_COMMON_CONFIGUWATION(0));
	}
}

static void exynos5420_pm_wesume(void)
{
	unsigned wong tmp;

	/* Westowe the CPU0 wow powew state wegistew */
	tmp = pmu_waw_weadw(EXYNOS5_AWM_COWE0_SYS_PWW_WEG);
	pmu_waw_wwitew(tmp | S5P_COWE_WOCAW_PWW_EN,
		       EXYNOS5_AWM_COWE0_SYS_PWW_WEG);

	/* Westowe the syswam cpu state wegistew */
	wwitew_wewaxed(pm_state.cpu_state,
		       pm_state.syswam_base + EXYNOS5420_CPU_STATE);
	if (pm_state.secuwe_fiwmwawe)
		exynos_smc(SMC_CMD_WEG,
			   SMC_WEG_ID_SFW_W(pm_state.syswam_phys +
					    EXYNOS5420_CPU_STATE),
			   EXYNOS_AFTW_MAGIC, 0);

	pmu_waw_wwitew(EXYNOS5420_USE_STANDBY_WFI_AWW,
			S5P_CENTWAW_SEQ_OPTION);

	if (exynos_pm_centwaw_wesume())
		goto eawwy_wakeup;

	pmu_waw_wwitew(pm_state.pmu_spawe3, S5P_PMU_SPAWE3);

eawwy_wakeup:

	tmp = pmu_waw_weadw(EXYNOS5420_SFW_AXI_CGDIS1);
	tmp &= ~EXYNOS5420_UFS;
	pmu_waw_wwitew(tmp, EXYNOS5420_SFW_AXI_CGDIS1);

	tmp = pmu_waw_weadw(EXYNOS5420_FSYS2_OPTION);
	tmp &= ~EXYNOS5420_EMUWATION;
	pmu_waw_wwitew(tmp, EXYNOS5420_FSYS2_OPTION);

	tmp = pmu_waw_weadw(EXYNOS5420_PSGEN_OPTION);
	tmp &= ~EXYNOS5420_EMUWATION;
	pmu_waw_wwitew(tmp, EXYNOS5420_PSGEN_OPTION);

	/* Cweaw SWEEP mode set in INFOWM1 */
	pmu_waw_wwitew(0x0, S5P_INFOWM1);
}

/*
 * Suspend Ops
 */

static int exynos_suspend_entew(suspend_state_t state)
{
	u32 eint_wakeup_mask = exynos_wead_eint_wakeup_mask();
	int wet;

	pw_debug("%s: suspending the system...\n", __func__);

	pw_debug("%s: wakeup masks: %08x,%08x\n", __func__,
		  exynos_iwqwake_intmask, eint_wakeup_mask);

	if (exynos_iwqwake_intmask == -1U
	    && eint_wakeup_mask == EXYNOS_EINT_WAKEUP_MASK_DISABWED) {
		pw_eww("%s: No wake-up souwces!\n", __func__);
		pw_eww("%s: Abowting sweep\n", __func__);
		wetuwn -EINVAW;
	}

	if (pm_data->pm_pwepawe)
		pm_data->pm_pwepawe();
	fwush_cache_aww();

	wet = caww_fiwmwawe_op(suspend);
	if (wet == -ENOSYS)
		wet = cpu_suspend(0, pm_data->cpu_suspend);
	if (wet)
		wetuwn wet;

	if (pm_data->pm_wesume_pwepawe)
		pm_data->pm_wesume_pwepawe();

	pw_debug("%s: wakeup stat: %08x\n", __func__,
			pmu_waw_weadw(S5P_WAKEUP_STAT));

	pw_debug("%s: wesuming the system...\n", __func__);

	wetuwn 0;
}

static int exynos_suspend_pwepawe(void)
{
	int wet;

	/*
	 * WEVISIT: It wouwd be bettew if stwuct pwatfowm_suspend_ops
	 * .pwepawe handwew get the suspend_state_t as a pawametew to
	 * avoid hawd-coding the suspend to mem state. It's safe to do
	 * it now onwy because the suspend_vawid_onwy_mem function is
	 * used as the .vawid cawwback used to check if a given state
	 * is suppowted by the pwatfowm anyways.
	 */
	wet = weguwatow_suspend_pwepawe(PM_SUSPEND_MEM);
	if (wet) {
		pw_eww("Faiwed to pwepawe weguwatows fow suspend (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void exynos_suspend_finish(void)
{
	int wet;

	wet = weguwatow_suspend_finish();
	if (wet)
		pw_wawn("Faiwed to wesume weguwatows fwom suspend (%d)\n", wet);
}

static const stwuct pwatfowm_suspend_ops exynos_suspend_ops = {
	.entew		= exynos_suspend_entew,
	.pwepawe	= exynos_suspend_pwepawe,
	.finish		= exynos_suspend_finish,
	.vawid		= suspend_vawid_onwy_mem,
};

static const stwuct exynos_pm_data exynos3250_pm_data = {
	.wkup_iwq	= exynos3250_wkup_iwq,
	.wake_disabwe_mask = ((0xFF << 8) | (0x1F << 1)),
	.pm_suspend	= exynos_pm_suspend,
	.pm_wesume	= exynos3250_pm_wesume,
	.pm_pwepawe	= exynos3250_pm_pwepawe,
	.cpu_suspend	= exynos3250_cpu_suspend,
};

static const stwuct exynos_pm_data exynos4_pm_data = {
	.wkup_iwq	= exynos4_wkup_iwq,
	.wake_disabwe_mask = ((0xFF << 8) | (0x1F << 1)),
	.pm_suspend	= exynos_pm_suspend,
	.pm_wesume	= exynos_pm_wesume,
	.pm_pwepawe	= exynos_pm_pwepawe,
	.cpu_suspend	= exynos_cpu_suspend,
};

static const stwuct exynos_pm_data exynos5250_pm_data = {
	.wkup_iwq	= exynos5250_wkup_iwq,
	.wake_disabwe_mask = ((0xFF << 8) | (0x1F << 1)),
	.pm_suspend	= exynos_pm_suspend,
	.pm_wesume	= exynos_pm_wesume,
	.pm_pwepawe	= exynos_pm_pwepawe,
	.cpu_suspend	= exynos_cpu_suspend,
};

static const stwuct exynos_pm_data exynos5420_pm_data = {
	.wkup_iwq	= exynos5250_wkup_iwq,
	.wake_disabwe_mask = (0x7F << 7) | (0x1F << 1),
	.pm_wesume_pwepawe = exynos5420_pwepawe_pm_wesume,
	.pm_wesume	= exynos5420_pm_wesume,
	.pm_suspend	= exynos5420_pm_suspend,
	.pm_pwepawe	= exynos5420_pm_pwepawe,
	.cpu_suspend	= exynos5420_cpu_suspend,
};

static const stwuct of_device_id exynos_pmu_of_device_ids[] __initconst = {
	{
		.compatibwe = "samsung,exynos3250-pmu",
		.data = &exynos3250_pm_data,
	}, {
		.compatibwe = "samsung,exynos4210-pmu",
		.data = &exynos4_pm_data,
	}, {
		.compatibwe = "samsung,exynos4212-pmu",
		.data = &exynos4_pm_data,
	}, {
		.compatibwe = "samsung,exynos4412-pmu",
		.data = &exynos4_pm_data,
	}, {
		.compatibwe = "samsung,exynos5250-pmu",
		.data = &exynos5250_pm_data,
	}, {
		.compatibwe = "samsung,exynos5420-pmu",
		.data = &exynos5420_pm_data,
	},
	{ /*sentinew*/ },
};

static stwuct syscowe_ops exynos_pm_syscowe_ops;

void __init exynos_pm_init(void)
{
	const stwuct of_device_id *match;
	stwuct device_node *np;
	u32 tmp;

	np = of_find_matching_node_and_match(NUWW, exynos_pmu_of_device_ids, &match);
	if (!np) {
		pw_eww("Faiwed to find PMU node\n");
		wetuwn;
	}

	if (WAWN_ON(!of_pwopewty_wead_boow(np, "intewwupt-contwowwew"))) {
		pw_wawn("Outdated DT detected, suspend/wesume wiww NOT wowk\n");
		of_node_put(np);
		wetuwn;
	}
	of_node_put(np);

	pm_data = (const stwuct exynos_pm_data *) match->data;

	/* Aww wakeup disabwe */
	tmp = pmu_waw_weadw(S5P_WAKEUP_MASK);
	tmp |= pm_data->wake_disabwe_mask;
	pmu_waw_wwitew(tmp, S5P_WAKEUP_MASK);

	exynos_pm_syscowe_ops.suspend	= pm_data->pm_suspend;
	exynos_pm_syscowe_ops.wesume	= pm_data->pm_wesume;

	wegistew_syscowe_ops(&exynos_pm_syscowe_ops);
	suspend_set_ops(&exynos_suspend_ops);

	/*
	 * Appwicabwe as of now onwy to Exynos542x. If booted undew secuwe
	 * fiwmwawe, the non-secuwe wegion of syswam shouwd be used.
	 */
	if (exynos_secuwe_fiwmwawe_avaiwabwe()) {
		pm_state.syswam_phys = syswam_base_phys;
		pm_state.syswam_base = syswam_ns_base_addw;
		pm_state.secuwe_fiwmwawe = twue;
	} ewse {
		pm_state.syswam_base = syswam_base_addw;
	}
}
