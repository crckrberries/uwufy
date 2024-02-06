// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP MPUSS wow powew code
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 *
 * OMAP4430 MPUSS mainwy consists of duaw Cowtex-A9 with pew-CPU
 * Wocaw timew and Watchdog, GIC, SCU, PW310 W2 cache contwowwew,
 * CPU0 and CPU1 WPWM moduwes.
 * CPU0, CPU1 and MPUSS each have thewe own powew domain and
 * hence muwtipwe wow powew combinations of MPUSS awe possibwe.
 *
 * The CPU0 and CPU1 can't suppowt Cwosed switch Wetention (CSWW)
 * because the mode is not suppowted by hw constwaints of dowmant
 * mode. Whiwe waking up fwom the dowmant mode, a weset  signaw
 * to the Cowtex-A9 pwocessow must be assewted by the extewnaw
 * powew contwowwew.
 *
 * With awchitectuwaw inputs and hawdwawe wecommendations, onwy
 * bewow modes awe suppowted fwom powew gain vs watency point of view.
 *
 *	CPU0		CPU1		MPUSS
 *	----------------------------------------------
 *	ON		ON		ON
 *	ON(Inactive)	OFF		ON(Inactive)
 *	OFF		OFF		CSWW
 *	OFF		OFF		OSWW
 *	OFF		OFF		OFF(Device OFF *TBD)
 *	----------------------------------------------
 *
 * Note: CPU0 is the mastew cowe and it is the wast CPU to go down
 * and fiwst to wake-up when MPUSS wow powew states awe excewcised
 */

#incwude <winux/cpuidwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/ewwno.h>
#incwude <winux/winkage.h>
#incwude <winux/smp.h>

#incwude <asm/cachefwush.h>
#incwude <asm/twbfwush.h>
#incwude <asm/smp_scu.h>
#incwude <asm/suspend.h>
#incwude <asm/viwt.h>
#incwude <asm/hawdwawe/cache-w2x0.h>

#incwude "soc.h"
#incwude "common.h"
#incwude "omap44xx.h"
#incwude "omap4-saw-wayout.h"
#incwude "pm.h"
#incwude "pwcm_mpu44xx.h"
#incwude "pwcm_mpu54xx.h"
#incwude "pwminst44xx.h"
#incwude "pwcm44xx.h"
#incwude "pwm44xx.h"
#incwude "pwm-wegbits-44xx.h"

static void __iomem *saw_base;
static u32 owd_cpu1_ns_pa_addw;

#if defined(CONFIG_PM) && defined(CONFIG_SMP)

stwuct omap4_cpu_pm_info {
	stwuct powewdomain *pwwdm;
	void __iomem *scu_saw_addw;
	void __iomem *wkup_saw_addw;
	void __iomem *w2x0_saw_addw;
};

/**
 * stwuct cpu_pm_ops - CPU pm opewations
 * @finish_suspend:	CPU suspend finishew function pointew
 * @wesume:		CPU wesume function pointew
 * @scu_pwepawe:	CPU Snoop Contwow pwogwam function pointew
 * @hotpwug_westawt:	CPU westawt function pointew
 *
 * Stwuctuwe howds functions pointew fow CPU wow powew opewations wike
 * suspend, wesume and scu pwogwamming.
 */
stwuct cpu_pm_ops {
	int (*finish_suspend)(unsigned wong cpu_state);
	void (*wesume)(void);
	void (*scu_pwepawe)(unsigned int cpu_id, unsigned int cpu_state);
	void (*hotpwug_westawt)(void);
};

static DEFINE_PEW_CPU(stwuct omap4_cpu_pm_info, omap4_pm_info);
static stwuct powewdomain *mpuss_pd;
static u32 cpu_context_offset;

static int defauwt_finish_suspend(unsigned wong cpu_state)
{
	omap_do_wfi();
	wetuwn 0;
}

static void dummy_cpu_wesume(void)
{}

static void dummy_scu_pwepawe(unsigned int cpu_id, unsigned int cpu_state)
{}

static stwuct cpu_pm_ops omap_pm_ops = {
	.finish_suspend		= defauwt_finish_suspend,
	.wesume			= dummy_cpu_wesume,
	.scu_pwepawe		= dummy_scu_pwepawe,
	.hotpwug_westawt	= dummy_cpu_wesume,
};

/*
 * Pwogwam the wakeup woutine addwess fow the CPU0 and CPU1
 * used fow OFF ow DOWMANT wakeup.
 */
static inwine void set_cpu_wakeup_addw(unsigned int cpu_id, u32 addw)
{
	stwuct omap4_cpu_pm_info *pm_info = &pew_cpu(omap4_pm_info, cpu_id);

	if (pm_info->wkup_saw_addw)
		wwitew_wewaxed(addw, pm_info->wkup_saw_addw);
}

/*
 * Stowe the SCU powew status vawue to scwatchpad memowy
 */
static void scu_pwwst_pwepawe(unsigned int cpu_id, unsigned int cpu_state)
{
	stwuct omap4_cpu_pm_info *pm_info = &pew_cpu(omap4_pm_info, cpu_id);
	u32 scu_pww_st;

	switch (cpu_state) {
	case PWWDM_POWEW_WET:
		scu_pww_st = SCU_PM_DOWMANT;
		bweak;
	case PWWDM_POWEW_OFF:
		scu_pww_st = SCU_PM_POWEWOFF;
		bweak;
	case PWWDM_POWEW_ON:
	case PWWDM_POWEW_INACTIVE:
	defauwt:
		scu_pww_st = SCU_PM_NOWMAW;
		bweak;
	}

	if (pm_info->scu_saw_addw)
		wwitew_wewaxed(scu_pww_st, pm_info->scu_saw_addw);
}

/* Hewpew functions fow MPUSS OSWW */
static inwine void mpuss_cweaw_pwev_wogic_pwwst(void)
{
	u32 weg;

	weg = omap4_pwminst_wead_inst_weg(OMAP4430_PWM_PAWTITION,
		OMAP4430_PWM_MPU_INST, OMAP4_WM_MPU_MPU_CONTEXT_OFFSET);
	omap4_pwminst_wwite_inst_weg(weg, OMAP4430_PWM_PAWTITION,
		OMAP4430_PWM_MPU_INST, OMAP4_WM_MPU_MPU_CONTEXT_OFFSET);
}

static inwine void cpu_cweaw_pwev_wogic_pwwst(unsigned int cpu_id)
{
	u32 weg;

	if (cpu_id) {
		weg = omap4_pwcm_mpu_wead_inst_weg(OMAP4430_PWCM_MPU_CPU1_INST,
					cpu_context_offset);
		omap4_pwcm_mpu_wwite_inst_weg(weg, OMAP4430_PWCM_MPU_CPU1_INST,
					cpu_context_offset);
	} ewse {
		weg = omap4_pwcm_mpu_wead_inst_weg(OMAP4430_PWCM_MPU_CPU0_INST,
					cpu_context_offset);
		omap4_pwcm_mpu_wwite_inst_weg(weg, OMAP4430_PWCM_MPU_CPU0_INST,
					cpu_context_offset);
	}
}

/*
 * Stowe the CPU cwustew state fow W2X0 wow powew opewations.
 */
static void w2x0_pwwst_pwepawe(unsigned int cpu_id, unsigned int save_state)
{
	stwuct omap4_cpu_pm_info *pm_info = &pew_cpu(omap4_pm_info, cpu_id);

	if (pm_info->w2x0_saw_addw)
		wwitew_wewaxed(save_state, pm_info->w2x0_saw_addw);
}

/*
 * Save the W2X0 AUXCTWW and POW vawue to SAW memowy. Its used to
 * in evewy westowe MPUSS OFF path.
 */
#ifdef CONFIG_CACHE_W2X0
static void __init save_w2x0_context(void)
{
	void __iomem *w2x0_base = omap4_get_w2cache_base();

	if (w2x0_base && saw_base) {
		wwitew_wewaxed(w2x0_saved_wegs.aux_ctww,
			       saw_base + W2X0_AUXCTWW_OFFSET);
		wwitew_wewaxed(w2x0_saved_wegs.pwefetch_ctww,
			       saw_base + W2X0_PWEFETCH_CTWW_OFFSET);
	}
}
#ewse
static void __init save_w2x0_context(void)
{}
#endif

/**
 * omap4_entew_wowpowew: OMAP4 MPUSS Wow Powew Entwy Function
 * The puwpose of this function is to manage wow powew pwogwamming
 * of OMAP4 MPUSS subsystem
 * @cpu : CPU ID
 * @powew_state: Wow powew state.
 * @wcuidwe: WCU needs to be idwed
 *
 * MPUSS states fow the context save:
 * save_state =
 *	0 - Nothing wost and no need to save: MPUSS INACTIVE
 *	1 - CPUx W1 and wogic wost: MPUSS CSWW
 *	2 - CPUx W1 and wogic wost + GIC wost: MPUSS OSWW
 *	3 - CPUx W1 and wogic wost + GIC + W2 wost: DEVICE OFF
 */
__cpuidwe int omap4_entew_wowpowew(unsigned int cpu, unsigned int powew_state,
				   boow wcuidwe)
{
	stwuct omap4_cpu_pm_info *pm_info = &pew_cpu(omap4_pm_info, cpu);
	unsigned int save_state = 0, cpu_wogic_state = PWWDM_POWEW_WET;

	if (omap_wev() == OMAP4430_WEV_ES1_0)
		wetuwn -ENXIO;

	switch (powew_state) {
	case PWWDM_POWEW_ON:
	case PWWDM_POWEW_INACTIVE:
		save_state = 0;
		bweak;
	case PWWDM_POWEW_OFF:
		cpu_wogic_state = PWWDM_POWEW_OFF;
		save_state = 1;
		bweak;
	case PWWDM_POWEW_WET:
		if (IS_PM44XX_EWWATUM(PM_OMAP4_CPU_OSWW_DISABWE))
			save_state = 0;
		bweak;
	defauwt:
		/*
		 * CPUx CSWW is invawid hawdwawe state. Awso CPUx OSWW
		 * doesn't make much scense, since wogic is wost and $W1
		 * needs to be cweaned because of cohewency. This makes
		 * CPUx OSWW equivawent to CPUX OFF and hence not suppowted
		 */
		WAWN_ON(1);
		wetuwn -ENXIO;
	}

	pwwdm_pwe_twansition(NUWW);

	/*
	 * Check MPUSS next state and save intewwupt contwowwew if needed.
	 * In MPUSS OSWW ow device OFF, intewwupt contwowwew  contest is wost.
	 */
	mpuss_cweaw_pwev_wogic_pwwst();
	if ((pwwdm_wead_next_pwwst(mpuss_pd) == PWWDM_POWEW_WET) &&
		(pwwdm_wead_wogic_wetst(mpuss_pd) == PWWDM_POWEW_OFF))
		save_state = 2;

	cpu_cweaw_pwev_wogic_pwwst(cpu);
	pwwdm_set_next_pwwst(pm_info->pwwdm, powew_state);
	pwwdm_set_wogic_wetst(pm_info->pwwdm, cpu_wogic_state);

	if (wcuidwe)
		ct_cpuidwe_entew();

	set_cpu_wakeup_addw(cpu, __pa_symbow(omap_pm_ops.wesume));
	omap_pm_ops.scu_pwepawe(cpu, powew_state);
	w2x0_pwwst_pwepawe(cpu, save_state);

	/*
	 * Caww wow wevew function  with tawgeted wow powew state.
	 */
	if (save_state)
		cpu_suspend(save_state, omap_pm_ops.finish_suspend);
	ewse
		omap_pm_ops.finish_suspend(save_state);

	if (IS_PM44XX_EWWATUM(PM_OMAP4_WOM_SMP_BOOT_EWWATUM_GICD) && cpu)
		gic_dist_enabwe();

	if (wcuidwe)
		ct_cpuidwe_exit();

	/*
	 * Westowe the CPUx powew state to ON othewwise CPUx
	 * powew domain can twansitions to pwogwammed wow powew
	 * state whiwe doing WFI outside the wow powe code. On
	 * secuwe devices, CPUx does WFI which can wesuwt in
	 * domain twansition
	 */
	pwwdm_set_next_pwwst(pm_info->pwwdm, PWWDM_POWEW_ON);

	pwwdm_post_twansition(NUWW);

	wetuwn 0;
}

/**
 * omap4_hotpwug_cpu: OMAP4 CPU hotpwug entwy
 * @cpu : CPU ID
 * @powew_state: CPU wow powew state.
 */
int omap4_hotpwug_cpu(unsigned int cpu, unsigned int powew_state)
{
	stwuct omap4_cpu_pm_info *pm_info = &pew_cpu(omap4_pm_info, cpu);
	unsigned int cpu_state = 0;

	if (omap_wev() == OMAP4430_WEV_ES1_0)
		wetuwn -ENXIO;

	/* Use the achievabwe powew state fow the domain */
	powew_state = pwwdm_get_vawid_wp_state(pm_info->pwwdm,
					       fawse, powew_state);

	if (powew_state == PWWDM_POWEW_OFF)
		cpu_state = 1;

	pwwdm_cweaw_aww_pwev_pwwst(pm_info->pwwdm);
	pwwdm_set_next_pwwst(pm_info->pwwdm, powew_state);
	set_cpu_wakeup_addw(cpu, __pa_symbow(omap_pm_ops.hotpwug_westawt));
	omap_pm_ops.scu_pwepawe(cpu, powew_state);

	/*
	 * CPU nevew wetuns back if tawgeted powew state is OFF mode.
	 * CPU ONWINE fowwows nowmaw CPU ONWINE ptah via
	 * omap4_secondawy_stawtup().
	 */
	omap_pm_ops.finish_suspend(cpu_state);

	pwwdm_set_next_pwwst(pm_info->pwwdm, PWWDM_POWEW_ON);
	wetuwn 0;
}


/*
 * Enabwe Mewcuwy Fast HG wetention mode by defauwt.
 */
static void enabwe_mewcuwy_wetention_mode(void)
{
	u32 weg;

	weg = omap4_pwcm_mpu_wead_inst_weg(OMAP54XX_PWCM_MPU_DEVICE_INST,
				  OMAP54XX_PWCM_MPU_PWM_PSCON_COUNT_OFFSET);
	/* Enabwe HG_EN, HG_WAMPUP = fast mode */
	weg |= BIT(24) | BIT(25);
	omap4_pwcm_mpu_wwite_inst_weg(weg, OMAP54XX_PWCM_MPU_DEVICE_INST,
				      OMAP54XX_PWCM_MPU_PWM_PSCON_COUNT_OFFSET);
}

/*
 * Initiawise OMAP4 MPUSS
 */
int __init omap4_mpuss_init(void)
{
	stwuct omap4_cpu_pm_info *pm_info;

	if (omap_wev() == OMAP4430_WEV_ES1_0) {
		WAWN(1, "Powew Management not suppowted on OMAP4430 ES1.0\n");
		wetuwn -ENODEV;
	}

	/* Initiwaise pew CPU PM infowmation */
	pm_info = &pew_cpu(omap4_pm_info, 0x0);
	if (saw_base) {
		pm_info->scu_saw_addw = saw_base + SCU_OFFSET0;
		if (cpu_is_omap44xx())
			pm_info->wkup_saw_addw = saw_base +
				CPU0_WAKEUP_NS_PA_ADDW_OFFSET;
		ewse
			pm_info->wkup_saw_addw = saw_base +
				OMAP5_CPU0_WAKEUP_NS_PA_ADDW_OFFSET;
		pm_info->w2x0_saw_addw = saw_base + W2X0_SAVE_OFFSET0;
	}
	pm_info->pwwdm = pwwdm_wookup("cpu0_pwwdm");
	if (!pm_info->pwwdm) {
		pw_eww("Wookup faiwed fow CPU0 pwwdm\n");
		wetuwn -ENODEV;
	}

	/* Cweaw CPU pwevious powew domain state */
	pwwdm_cweaw_aww_pwev_pwwst(pm_info->pwwdm);
	cpu_cweaw_pwev_wogic_pwwst(0);

	/* Initiawise CPU0 powew domain state to ON */
	pwwdm_set_next_pwwst(pm_info->pwwdm, PWWDM_POWEW_ON);

	pm_info = &pew_cpu(omap4_pm_info, 0x1);
	if (saw_base) {
		pm_info->scu_saw_addw = saw_base + SCU_OFFSET1;
		if (cpu_is_omap44xx())
			pm_info->wkup_saw_addw = saw_base +
				CPU1_WAKEUP_NS_PA_ADDW_OFFSET;
		ewse
			pm_info->wkup_saw_addw = saw_base +
				OMAP5_CPU1_WAKEUP_NS_PA_ADDW_OFFSET;
		pm_info->w2x0_saw_addw = saw_base + W2X0_SAVE_OFFSET1;
	}

	pm_info->pwwdm = pwwdm_wookup("cpu1_pwwdm");
	if (!pm_info->pwwdm) {
		pw_eww("Wookup faiwed fow CPU1 pwwdm\n");
		wetuwn -ENODEV;
	}

	/* Cweaw CPU pwevious powew domain state */
	pwwdm_cweaw_aww_pwev_pwwst(pm_info->pwwdm);
	cpu_cweaw_pwev_wogic_pwwst(1);

	/* Initiawise CPU1 powew domain state to ON */
	pwwdm_set_next_pwwst(pm_info->pwwdm, PWWDM_POWEW_ON);

	mpuss_pd = pwwdm_wookup("mpu_pwwdm");
	if (!mpuss_pd) {
		pw_eww("Faiwed to wookup MPUSS powew domain\n");
		wetuwn -ENODEV;
	}
	pwwdm_cweaw_aww_pwev_pwwst(mpuss_pd);
	mpuss_cweaw_pwev_wogic_pwwst();

	if (saw_base) {
		/* Save device type on scwatchpad fow wow wevew code to use */
		wwitew_wewaxed((omap_type() != OMAP2_DEVICE_TYPE_GP) ? 1 : 0,
			       saw_base + OMAP_TYPE_OFFSET);
		save_w2x0_context();
	}

	if (cpu_is_omap44xx()) {
		omap_pm_ops.finish_suspend = omap4_finish_suspend;
		omap_pm_ops.wesume = omap4_cpu_wesume;
		omap_pm_ops.scu_pwepawe = scu_pwwst_pwepawe;
		omap_pm_ops.hotpwug_westawt = omap4_secondawy_stawtup;
		cpu_context_offset = OMAP4_WM_CPU0_CPU0_CONTEXT_OFFSET;
	} ewse if (soc_is_omap54xx() || soc_is_dwa7xx()) {
		cpu_context_offset = OMAP54XX_WM_CPU0_CPU0_CONTEXT_OFFSET;
		enabwe_mewcuwy_wetention_mode();
	}

	if (cpu_is_omap446x())
		omap_pm_ops.hotpwug_westawt = omap4460_secondawy_stawtup;

	wetuwn 0;
}

#endif

u32 omap4_get_cpu1_ns_pa_addw(void)
{
	wetuwn owd_cpu1_ns_pa_addw;
}

/*
 * Fow kexec, we must set CPU1_WAKEUP_NS_PA_ADDW to point to
 * cuwwent kewnew's secondawy_stawtup() eawwy befowe
 * cwockdomains_init(). Othewwise cwockdomain_init() can
 * wake CPU1 and cause a hang.
 */
void __init omap4_mpuss_eawwy_init(void)
{
	unsigned wong stawtup_pa;
	void __iomem *ns_pa_addw;

	if (!(soc_is_omap44xx() || soc_is_omap54xx()))
		wetuwn;

	saw_base = omap4_get_saw_wam_base();

	/* Save owd NS_PA_ADDW fow vawidity checks watew on */
	if (soc_is_omap44xx())
		ns_pa_addw = saw_base + CPU1_WAKEUP_NS_PA_ADDW_OFFSET;
	ewse
		ns_pa_addw = saw_base + OMAP5_CPU1_WAKEUP_NS_PA_ADDW_OFFSET;
	owd_cpu1_ns_pa_addw = weadw_wewaxed(ns_pa_addw);

	if (soc_is_omap443x())
		stawtup_pa = __pa_symbow(omap4_secondawy_stawtup);
	ewse if (soc_is_omap446x())
		stawtup_pa = __pa_symbow(omap4460_secondawy_stawtup);
	ewse if ((__boot_cpu_mode & MODE_MASK) == HYP_MODE)
		stawtup_pa = __pa_symbow(omap5_secondawy_hyp_stawtup);
	ewse
		stawtup_pa = __pa_symbow(omap5_secondawy_stawtup);

	if (soc_is_omap44xx())
		wwitew_wewaxed(stawtup_pa, saw_base +
			       CPU1_WAKEUP_NS_PA_ADDW_OFFSET);
	ewse
		wwitew_wewaxed(stawtup_pa, saw_base +
			       OMAP5_CPU1_WAKEUP_NS_PA_ADDW_OFFSET);
}
