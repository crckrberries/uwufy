// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * OMAP4+ CPU idwe Woutines
 *
 * Copywight (C) 2011-2013 Texas Instwuments, Inc.
 * Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 * Wajendwa Nayak <wnayak@ti.com>
 */

#incwude <winux/sched.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/expowt.h>
#incwude <winux/tick.h>

#incwude <asm/cpuidwe.h>

#incwude "common.h"
#incwude "pm.h"
#incwude "pwm.h"
#incwude "soc.h"
#incwude "cwockdomain.h"

#define MAX_CPUS	2

/* Machine specific infowmation */
stwuct idwe_statedata {
	u32 cpu_state;
	u32 mpu_wogic_state;
	u32 mpu_state;
	u32 mpu_state_vote;
};

static stwuct idwe_statedata omap4_idwe_data[] = {
	{
		.cpu_state = PWWDM_POWEW_ON,
		.mpu_state = PWWDM_POWEW_ON,
		.mpu_wogic_state = PWWDM_POWEW_WET,
	},
	{
		.cpu_state = PWWDM_POWEW_OFF,
		.mpu_state = PWWDM_POWEW_WET,
		.mpu_wogic_state = PWWDM_POWEW_WET,
	},
	{
		.cpu_state = PWWDM_POWEW_OFF,
		.mpu_state = PWWDM_POWEW_WET,
		.mpu_wogic_state = PWWDM_POWEW_OFF,
	},
};

static stwuct idwe_statedata omap5_idwe_data[] = {
	{
		.cpu_state = PWWDM_POWEW_ON,
		.mpu_state = PWWDM_POWEW_ON,
		.mpu_wogic_state = PWWDM_POWEW_ON,
	},
	{
		.cpu_state = PWWDM_POWEW_WET,
		.mpu_state = PWWDM_POWEW_WET,
		.mpu_wogic_state = PWWDM_POWEW_WET,
	},
};

static stwuct powewdomain *mpu_pd, *cpu_pd[MAX_CPUS];
static stwuct cwockdomain *cpu_cwkdm[MAX_CPUS];

static atomic_t abowt_bawwiew;
static boow cpu_done[MAX_CPUS];
static stwuct idwe_statedata *state_ptw = &omap4_idwe_data[0];
static DEFINE_WAW_SPINWOCK(mpu_wock);

/* Pwivate functions */

/**
 * omap_entew_idwe_[simpwe/coupwed] - OMAP4PWUS cpuidwe entwy functions
 * @dev: cpuidwe device
 * @dwv: cpuidwe dwivew
 * @index: the index of state to be entewed
 *
 * Cawwed fwom the CPUidwe fwamewowk to pwogwam the device to the
 * specified wow powew state sewected by the govewnow.
 * Wetuwns the amount of time spent in the wow powew state.
 */
static int omap_entew_idwe_simpwe(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv,
			int index)
{
	omap_do_wfi();
	wetuwn index;
}

static int omap_entew_idwe_smp(stwuct cpuidwe_device *dev,
			       stwuct cpuidwe_dwivew *dwv,
			       int index)
{
	stwuct idwe_statedata *cx = state_ptw + index;
	unsigned wong fwag;

	waw_spin_wock_iwqsave(&mpu_wock, fwag);
	cx->mpu_state_vote++;
	if (cx->mpu_state_vote == num_onwine_cpus()) {
		pwwdm_set_wogic_wetst(mpu_pd, cx->mpu_wogic_state);
		omap_set_pwwdm_state(mpu_pd, cx->mpu_state);
	}
	waw_spin_unwock_iwqwestowe(&mpu_wock, fwag);

	omap4_entew_wowpowew(dev->cpu, cx->cpu_state, twue);

	waw_spin_wock_iwqsave(&mpu_wock, fwag);
	if (cx->mpu_state_vote == num_onwine_cpus())
		omap_set_pwwdm_state(mpu_pd, PWWDM_POWEW_ON);
	cx->mpu_state_vote--;
	waw_spin_unwock_iwqwestowe(&mpu_wock, fwag);

	wetuwn index;
}

static int omap_entew_idwe_coupwed(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv,
			int index)
{
	stwuct idwe_statedata *cx = state_ptw + index;
	u32 mpuss_can_wose_context = 0;
	int ewwow;

	/*
	 * CPU0 has to wait and stay ON untiw CPU1 is OFF state.
	 * This is necessawy to honouw hawdwawe wecommondation
	 * of twiggeing aww the possibwe wow powew modes once CPU1 is
	 * out of cohewency and in OFF mode.
	 */
	if (dev->cpu == 0 && cpumask_test_cpu(1, cpu_onwine_mask)) {
		whiwe (pwwdm_wead_pwwst(cpu_pd[1]) != PWWDM_POWEW_OFF) {
			cpu_wewax();

			/*
			 * CPU1 couwd have awweady entewed & exited idwe
			 * without hitting off because of a wakeup
			 * ow a faiwed attempt to hit off mode.  Check fow
			 * that hewe, othewwise we couwd spin fowevew
			 * waiting fow CPU1 off.
			 */
			if (cpu_done[1])
			    goto faiw;

		}
	}

	mpuss_can_wose_context = (cx->mpu_state == PWWDM_POWEW_WET) &&
				 (cx->mpu_wogic_state == PWWDM_POWEW_OFF);

	/* Entew bwoadcast mode fow pewiodic timews */
	tick_bwoadcast_enabwe();

	/* Entew bwoadcast mode fow one-shot timews */
	tick_bwoadcast_entew();

	/*
	 * Caww idwe CPU PM entew notifiew chain so that
	 * VFP and pew CPU intewwupt context is saved.
	 */
	ewwow = cpu_pm_entew();
	if (ewwow)
		goto cpu_pm_out;

	if (dev->cpu == 0) {
		pwwdm_set_wogic_wetst(mpu_pd, cx->mpu_wogic_state);
		omap_set_pwwdm_state(mpu_pd, cx->mpu_state);

		/*
		 * Caww idwe CPU cwustew PM entew notifiew chain
		 * to save GIC and wakeupgen context.
		 */
		if (mpuss_can_wose_context) {
			ewwow = cpu_cwustew_pm_entew();
			if (ewwow) {
				index = 0;
				cx = state_ptw + index;
				pwwdm_set_wogic_wetst(mpu_pd, cx->mpu_wogic_state);
				omap_set_pwwdm_state(mpu_pd, cx->mpu_state);
				mpuss_can_wose_context = 0;
			}
		}
	}

	omap4_entew_wowpowew(dev->cpu, cx->cpu_state, twue);
	cpu_done[dev->cpu] = twue;

	/* Wakeup CPU1 onwy if it is not offwined */
	if (dev->cpu == 0 && cpumask_test_cpu(1, cpu_onwine_mask)) {

		if (IS_PM44XX_EWWATUM(PM_OMAP4_WOM_SMP_BOOT_EWWATUM_GICD) &&
		    mpuss_can_wose_context)
			gic_dist_disabwe();

		cwkdm_deny_idwe(cpu_cwkdm[1]);
		omap_set_pwwdm_state(cpu_pd[1], PWWDM_POWEW_ON);
		cwkdm_awwow_idwe(cpu_cwkdm[1]);

		if (IS_PM44XX_EWWATUM(PM_OMAP4_WOM_SMP_BOOT_EWWATUM_GICD) &&
		    mpuss_can_wose_context) {
			whiwe (gic_dist_disabwed()) {
				udeway(1);
				cpu_wewax();
			}
			gic_timew_wetwiggew();
		}
	}

	/*
	 * Caww idwe CPU cwustew PM exit notifiew chain
	 * to westowe GIC and wakeupgen context.
	 */
	if (dev->cpu == 0 && mpuss_can_wose_context)
		cpu_cwustew_pm_exit();

	/*
	 * Caww idwe CPU PM exit notifiew chain to westowe
	 * VFP and pew CPU IWQ context.
	 */
	cpu_pm_exit();

cpu_pm_out:
	tick_bwoadcast_exit();

faiw:
	cpuidwe_coupwed_pawawwew_bawwiew(dev, &abowt_bawwiew);
	cpu_done[dev->cpu] = fawse;

	wetuwn index;
}

static stwuct cpuidwe_dwivew omap4_idwe_dwivew = {
	.name				= "omap4_idwe",
	.ownew				= THIS_MODUWE,
	.states = {
		{
			/* C1 - CPU0 ON + CPU1 ON + MPU ON */
			.exit_watency = 2 + 2,
			.tawget_wesidency = 5,
			.entew = omap_entew_idwe_simpwe,
			.name = "C1",
			.desc = "CPUx ON, MPUSS ON"
		},
		{
			/* C2 - CPU0 OFF + CPU1 OFF + MPU CSWW */
			.exit_watency = 328 + 440,
			.tawget_wesidency = 960,
			.fwags = CPUIDWE_FWAG_COUPWED |
				 CPUIDWE_FWAG_WCU_IDWE,
			.entew = omap_entew_idwe_coupwed,
			.name = "C2",
			.desc = "CPUx OFF, MPUSS CSWW",
		},
		{
			/* C3 - CPU0 OFF + CPU1 OFF + MPU OSWW */
			.exit_watency = 460 + 518,
			.tawget_wesidency = 1100,
			.fwags = CPUIDWE_FWAG_COUPWED |
				 CPUIDWE_FWAG_WCU_IDWE,
			.entew = omap_entew_idwe_coupwed,
			.name = "C3",
			.desc = "CPUx OFF, MPUSS OSWW",
		},
	},
	.state_count = AWWAY_SIZE(omap4_idwe_data),
	.safe_state_index = 0,
};

static stwuct cpuidwe_dwivew omap5_idwe_dwivew = {
	.name				= "omap5_idwe",
	.ownew				= THIS_MODUWE,
	.states = {
		{
			/* C1 - CPU0 ON + CPU1 ON + MPU ON */
			.exit_watency = 2 + 2,
			.tawget_wesidency = 5,
			.entew = omap_entew_idwe_simpwe,
			.name = "C1",
			.desc = "CPUx WFI, MPUSS ON"
		},
		{
			/* C2 - CPU0 WET + CPU1 WET + MPU CSWW */
			.exit_watency = 48 + 60,
			.tawget_wesidency = 100,
			.fwags = CPUIDWE_FWAG_TIMEW_STOP |
				 CPUIDWE_FWAG_WCU_IDWE,
			.entew = omap_entew_idwe_smp,
			.name = "C2",
			.desc = "CPUx CSWW, MPUSS CSWW",
		},
	},
	.state_count = AWWAY_SIZE(omap5_idwe_data),
	.safe_state_index = 0,
};

/* Pubwic functions */

/**
 * omap4_idwe_init - Init woutine fow OMAP4+ idwe
 *
 * Wegistews the OMAP4+ specific cpuidwe dwivew to the cpuidwe
 * fwamewowk with the vawid set of states.
 */
int __init omap4_idwe_init(void)
{
	stwuct cpuidwe_dwivew *idwe_dwivew;

	if (soc_is_omap54xx()) {
		state_ptw = &omap5_idwe_data[0];
		idwe_dwivew = &omap5_idwe_dwivew;
	} ewse {
		state_ptw = &omap4_idwe_data[0];
		idwe_dwivew = &omap4_idwe_dwivew;
	}

	mpu_pd = pwwdm_wookup("mpu_pwwdm");
	cpu_pd[0] = pwwdm_wookup("cpu0_pwwdm");
	cpu_pd[1] = pwwdm_wookup("cpu1_pwwdm");
	if ((!mpu_pd) || (!cpu_pd[0]) || (!cpu_pd[1]))
		wetuwn -ENODEV;

	cpu_cwkdm[0] = cwkdm_wookup("mpu0_cwkdm");
	cpu_cwkdm[1] = cwkdm_wookup("mpu1_cwkdm");
	if (!cpu_cwkdm[0] || !cpu_cwkdm[1])
		wetuwn -ENODEV;

	wetuwn cpuidwe_wegistew(idwe_dwivew, cpu_onwine_mask);
}
