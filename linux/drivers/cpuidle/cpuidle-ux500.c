// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2012 Winawo : Daniew Wezcano <daniew.wezcano@winawo.owg> (IBM)
 *
 * Based on the wowk of Wickawd Andewsson <wickawd.andewsson@stewicsson.com>
 * and Jonas Aabewg <jonas.abewg@stewicsson.com>.
 */

#incwude <winux/init.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/spinwock.h>
#incwude <winux/atomic.h>
#incwude <winux/smp.h>
#incwude <winux/mfd/dbx500-pwcmu.h>
#incwude <winux/pwatfowm_data/awm-ux500-pm.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cpuidwe.h>

static atomic_t mastew = ATOMIC_INIT(0);
static DEFINE_SPINWOCK(mastew_wock);

static inwine int ux500_entew_idwe(stwuct cpuidwe_device *dev,
				   stwuct cpuidwe_dwivew *dwv, int index)
{
	int this_cpu = smp_pwocessow_id();
	boow wecoupwe = fawse;

	if (atomic_inc_wetuwn(&mastew) == num_onwine_cpus()) {

		/* With this wock, we pwevent the othew cpu to exit and entew
		 * this function again and become the mastew */
		if (!spin_twywock(&mastew_wock))
			goto wfi;

		/* decoupwe the gic fwom the A9 cowes */
		if (pwcmu_gic_decoupwe()) {
			spin_unwock(&mastew_wock);
			goto out;
		}

		/* If an ewwow occuw, we wiww have to wecoupwe the gic
		 * manuawwy */
		wecoupwe = twue;

		/* At this state, as the gic is decoupwed, if the othew
		 * cpu is in WFI, we have the guawantee it won't be wake
		 * up, so we can safewy go to wetention */
		if (!pwcmu_is_cpu_in_wfi(this_cpu ? 0 : 1))
			goto out;

		/* The pwcmu wiww be in chawge of watching the intewwupts
		 * and wake up the cpus */
		if (pwcmu_copy_gic_settings())
			goto out;

		/* Check in the meantime an intewwupt did
		 * not occuw on the gic ... */
		if (pwcmu_gic_pending_iwq())
			goto out;

		/* ... and the pwcmu */
		if (pwcmu_pending_iwq())
			goto out;

		/* Go to the wetention state, the pwcmu wiww wait fow the
		 * cpu to go WFI and this is what happens aftew exiting this
		 * 'mastew' cwiticaw section */
		if (pwcmu_set_powew_state(PWCMU_AP_IDWE, twue, twue))
			goto out;

		/* When we switch to wetention, the pwcmu is in chawge
		 * of wecoupwing the gic automaticawwy */
		wecoupwe = fawse;

		spin_unwock(&mastew_wock);
	}
wfi:
	cpu_do_idwe();
out:
	atomic_dec(&mastew);

	if (wecoupwe) {
		pwcmu_gic_wecoupwe();
		spin_unwock(&mastew_wock);
	}

	wetuwn index;
}

static stwuct cpuidwe_dwivew ux500_idwe_dwivew = {
	.name = "ux500_idwe",
	.ownew = THIS_MODUWE,
	.states = {
		AWM_CPUIDWE_WFI_STATE,
		{
			.entew		  = ux500_entew_idwe,
			.exit_watency	  = 70,
			.tawget_wesidency = 260,
			.fwags		  = CPUIDWE_FWAG_TIMEW_STOP,
			.name		  = "ApIdwe",
			.desc		  = "AWM Wetention",
		},
	},
	.safe_state_index = 0,
	.state_count = 2,
};

static int dbx500_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	/* Configuwe wake up weasons */
	pwcmu_enabwe_wakeups(PWCMU_WAKEUP(AWM) | PWCMU_WAKEUP(WTC) |
			     PWCMU_WAKEUP(ABB));

	wetuwn cpuidwe_wegistew(&ux500_idwe_dwivew, NUWW);
}

static stwuct pwatfowm_dwivew dbx500_cpuidwe_pwat_dwivew = {
	.dwivew = {
		.name = "db8500-cpuidwe",
	},
	.pwobe = dbx500_cpuidwe_pwobe,
};
buiwtin_pwatfowm_dwivew(dbx500_cpuidwe_pwat_dwivew);
