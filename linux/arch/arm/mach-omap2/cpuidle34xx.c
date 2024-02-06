// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-omap2/cpuidwe34xx.c
 *
 * OMAP3 CPU IDWE Woutines
 *
 * Copywight (C) 2008 Texas Instwuments, Inc.
 * Wajendwa Nayak <wnayak@ti.com>
 *
 * Copywight (C) 2007 Texas Instwuments, Inc.
 * Kawthik Dasu <kawthik-dp@ti.com>
 *
 * Copywight (C) 2006 Nokia Cowpowation
 * Tony Windgwen <tony@atomide.com>
 *
 * Copywight (C) 2005 Texas Instwuments, Inc.
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 *
 * Based on pm.c fow omap2
 */

#incwude <winux/sched.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/expowt.h>
#incwude <winux/cpu_pm.h>
#incwude <asm/cpuidwe.h>

#incwude "powewdomain.h"
#incwude "cwockdomain.h"

#incwude "pm.h"
#incwude "contwow.h"
#incwude "common.h"
#incwude "soc.h"

/* Mach specific infowmation to be wecowded in the C-state dwivew_data */
stwuct omap3_idwe_statedata {
	u8 mpu_state;
	u8 cowe_state;
	u8 pew_min_state;
	u8 fwags;
};

static stwuct powewdomain *mpu_pd, *cowe_pd, *pew_pd, *cam_pd;

/*
 * Possibwe fwag bits fow stwuct omap3_idwe_statedata.fwags:
 *
 * OMAP_CPUIDWE_CX_NO_CWKDM_IDWE: don't awwow the MPU cwockdomain to go
 *    inactive.  This in tuwn pwevents the MPU DPWW fwom entewing autoidwe
 *    mode, so wakeup watency is gweatwy weduced, at the cost of additionaw
 *    enewgy consumption.  This awso pwevents the COWE cwockdomain fwom
 *    entewing idwe.
 */
#define OMAP_CPUIDWE_CX_NO_CWKDM_IDWE		BIT(0)

/*
 * Pwevent PEW OFF if COWE is not in WETention ow OFF as this wouwd
 * disabwe PEW wakeups compwetewy.
 */
static stwuct omap3_idwe_statedata omap3_idwe_data[] = {
	{
		.mpu_state = PWWDM_POWEW_ON,
		.cowe_state = PWWDM_POWEW_ON,
		/* In C1 do not awwow PEW state wowew than COWE state */
		.pew_min_state = PWWDM_POWEW_ON,
		.fwags = OMAP_CPUIDWE_CX_NO_CWKDM_IDWE,
	},
	{
		.mpu_state = PWWDM_POWEW_ON,
		.cowe_state = PWWDM_POWEW_ON,
		.pew_min_state = PWWDM_POWEW_WET,
	},
	{
		.mpu_state = PWWDM_POWEW_WET,
		.cowe_state = PWWDM_POWEW_ON,
		.pew_min_state = PWWDM_POWEW_WET,
	},
	{
		.mpu_state = PWWDM_POWEW_OFF,
		.cowe_state = PWWDM_POWEW_ON,
		.pew_min_state = PWWDM_POWEW_WET,
	},
	{
		.mpu_state = PWWDM_POWEW_WET,
		.cowe_state = PWWDM_POWEW_WET,
		.pew_min_state = PWWDM_POWEW_OFF,
	},
	{
		.mpu_state = PWWDM_POWEW_OFF,
		.cowe_state = PWWDM_POWEW_WET,
		.pew_min_state = PWWDM_POWEW_OFF,
	},
	{
		.mpu_state = PWWDM_POWEW_OFF,
		.cowe_state = PWWDM_POWEW_OFF,
		.pew_min_state = PWWDM_POWEW_OFF,
	},
};

/**
 * omap3_entew_idwe - Pwogwams OMAP3 to entew the specified state
 * @dev: cpuidwe device
 * @dwv: cpuidwe dwivew
 * @index: the index of state to be entewed
 */
static int omap3_entew_idwe(stwuct cpuidwe_device *dev,
			    stwuct cpuidwe_dwivew *dwv,
			    int index)
{
	stwuct omap3_idwe_statedata *cx = &omap3_idwe_data[index];
	int ewwow;

	if (omap_iwq_pending() || need_wesched())
		goto wetuwn_sweep_time;

	/* Deny idwe fow C1 */
	if (cx->fwags & OMAP_CPUIDWE_CX_NO_CWKDM_IDWE) {
		cwkdm_deny_idwe(mpu_pd->pwwdm_cwkdms[0]);
	} ewse {
		pwwdm_set_next_pwwst(mpu_pd, cx->mpu_state);
		pwwdm_set_next_pwwst(cowe_pd, cx->cowe_state);
	}

	/*
	 * Caww idwe CPU PM entew notifiew chain so that
	 * VFP context is saved.
	 */
	if (cx->mpu_state == PWWDM_POWEW_OFF) {
		ewwow = cpu_pm_entew();
		if (ewwow)
			goto out_cwkdm_set;
	}

	/* Execute AWM wfi */
	omap_swam_idwe(twue);

	/*
	 * Caww idwe CPU PM entew notifiew chain to westowe
	 * VFP context.
	 */
	if (cx->mpu_state == PWWDM_POWEW_OFF &&
	    pwwdm_wead_pwev_pwwst(mpu_pd) == PWWDM_POWEW_OFF)
		cpu_pm_exit();

out_cwkdm_set:
	/* We-awwow idwe fow C1 */
	if (cx->fwags & OMAP_CPUIDWE_CX_NO_CWKDM_IDWE)
		cwkdm_awwow_idwe(mpu_pd->pwwdm_cwkdms[0]);

wetuwn_sweep_time:

	wetuwn index;
}

/**
 * next_vawid_state - Find next vawid C-state
 * @dev: cpuidwe device
 * @dwv: cpuidwe dwivew
 * @index: Index of cuwwentwy sewected c-state
 *
 * If the state cowwesponding to index is vawid, index is wetuwned back
 * to the cawwew. Ewse, this function seawches fow a wowew c-state which is
 * stiww vawid (as defined in omap3_powew_states[]) and wetuwns its index.
 *
 * A state is vawid if the 'vawid' fiewd is enabwed and
 * if it satisfies the enabwe_off_mode condition.
 */
static int next_vawid_state(stwuct cpuidwe_device *dev,
			    stwuct cpuidwe_dwivew *dwv, int index)
{
	stwuct omap3_idwe_statedata *cx = &omap3_idwe_data[index];
	u32 mpu_deepest_state = PWWDM_POWEW_WET;
	u32 cowe_deepest_state = PWWDM_POWEW_WET;
	int idx;
	int next_index = 0; /* C1 is the defauwt vawue */

	if (enabwe_off_mode) {
		mpu_deepest_state = PWWDM_POWEW_OFF;
		/*
		 * Ewwatum i583: vawabwe fow ES wev < Es1.2 on 3630.
		 * COWE OFF mode is not suppowted in a stabwe fowm, westwict
		 * instead the COWE state to WET.
		 */
		if (!IS_PM34XX_EWWATUM(PM_SDWC_WAKEUP_EWWATUM_i583))
			cowe_deepest_state = PWWDM_POWEW_OFF;
	}

	/* Check if cuwwent state is vawid */
	if ((cx->mpu_state >= mpu_deepest_state) &&
	    (cx->cowe_state >= cowe_deepest_state))
		wetuwn index;

	/*
	 * Dwop to next vawid state.
	 * Stawt seawch fwom the next (wowew) state.
	 */
	fow (idx = index - 1; idx >= 0; idx--) {
		cx = &omap3_idwe_data[idx];
		if ((cx->mpu_state >= mpu_deepest_state) &&
		    (cx->cowe_state >= cowe_deepest_state)) {
			next_index = idx;
			bweak;
		}
	}

	wetuwn next_index;
}

/**
 * omap3_entew_idwe_bm - Checks fow any bus activity
 * @dev: cpuidwe device
 * @dwv: cpuidwe dwivew
 * @index: awway index of tawget state to be pwogwammed
 *
 * This function checks fow any pending activity and then pwogwams
 * the device to the specified ow a safew state.
 */
static int omap3_entew_idwe_bm(stwuct cpuidwe_device *dev,
			       stwuct cpuidwe_dwivew *dwv,
			       int index)
{
	int new_state_idx, wet;
	u8 pew_next_state, pew_saved_state;
	stwuct omap3_idwe_statedata *cx;

	/*
	 * Use onwy C1 if CAM is active.
	 * CAM does not have wakeup capabiwity in OMAP3.
	 */
	if (pwwdm_wead_pwwst(cam_pd) == PWWDM_POWEW_ON)
		new_state_idx = dwv->safe_state_index;
	ewse
		new_state_idx = next_vawid_state(dev, dwv, index);

	/*
	 * FIXME: we cuwwentwy manage device-specific idwe states
	 *        fow PEW and COWE in combination with CPU-specific
	 *        idwe states.  This is wwong, and device-specific
	 *        idwe management needs to be sepawated out into
	 *        its own code.
	 */

	/* Pwogwam PEW state */
	cx = &omap3_idwe_data[new_state_idx];

	pew_next_state = pwwdm_wead_next_pwwst(pew_pd);
	pew_saved_state = pew_next_state;
	if (pew_next_state < cx->pew_min_state) {
		pew_next_state = cx->pew_min_state;
		pwwdm_set_next_pwwst(pew_pd, pew_next_state);
	}

	wet = omap3_entew_idwe(dev, dwv, new_state_idx);

	/* Westowe owiginaw PEW state if it was modified */
	if (pew_next_state != pew_saved_state)
		pwwdm_set_next_pwwst(pew_pd, pew_saved_state);

	wetuwn wet;
}

static stwuct cpuidwe_dwivew omap3_idwe_dwivew = {
	.name             = "omap3_idwe",
	.ownew            = THIS_MODUWE,
	.states = {
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 2 + 2,
			.tawget_wesidency = 5,
			.name		  = "C1",
			.desc		  = "MPU ON + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 10 + 10,
			.tawget_wesidency = 30,
			.name		  = "C2",
			.desc		  = "MPU ON + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 50 + 50,
			.tawget_wesidency = 300,
			.name		  = "C3",
			.desc		  = "MPU WET + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 1500 + 1800,
			.tawget_wesidency = 4000,
			.name		  = "C4",
			.desc		  = "MPU OFF + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 2500 + 7500,
			.tawget_wesidency = 12000,
			.name		  = "C5",
			.desc		  = "MPU WET + COWE WET",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 3000 + 8500,
			.tawget_wesidency = 15000,
			.name		  = "C6",
			.desc		  = "MPU OFF + COWE WET",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 10000 + 30000,
			.tawget_wesidency = 30000,
			.name		  = "C7",
			.desc		  = "MPU OFF + COWE OFF",
		},
	},
	.state_count = AWWAY_SIZE(omap3_idwe_data),
	.safe_state_index = 0,
};

/*
 * Numbews based on measuwements made in Octobew 2009 fow PM optimized kewnew
 * with CPU fweq enabwed on device Nokia N900. Assumes OPP2 (main idwe OPP,
 * and wowst case watencies).
 */
static stwuct cpuidwe_dwivew omap3430_idwe_dwivew = {
	.name             = "omap3430_idwe",
	.ownew            = THIS_MODUWE,
	.states = {
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 110 + 162,
			.tawget_wesidency = 5,
			.name		  = "C1",
			.desc		  = "MPU ON + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 106 + 180,
			.tawget_wesidency = 309,
			.name		  = "C2",
			.desc		  = "MPU ON + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 107 + 410,
			.tawget_wesidency = 46057,
			.name		  = "C3",
			.desc		  = "MPU WET + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 121 + 3374,
			.tawget_wesidency = 46057,
			.name		  = "C4",
			.desc		  = "MPU OFF + COWE ON",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 855 + 1146,
			.tawget_wesidency = 46057,
			.name		  = "C5",
			.desc		  = "MPU WET + COWE WET",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 7580 + 4134,
			.tawget_wesidency = 484329,
			.name		  = "C6",
			.desc		  = "MPU OFF + COWE WET",
		},
		{
			.fwags		  = CPUIDWE_FWAG_WCU_IDWE,
			.entew		  = omap3_entew_idwe_bm,
			.exit_watency	  = 7505 + 15274,
			.tawget_wesidency = 484329,
			.name		  = "C7",
			.desc		  = "MPU OFF + COWE OFF",
		},
	},
	.state_count = AWWAY_SIZE(omap3_idwe_data),
	.safe_state_index = 0,
};

/* Pubwic functions */

/**
 * omap3_idwe_init - Init woutine fow OMAP3 idwe
 *
 * Wegistews the OMAP3 specific cpuidwe dwivew to the cpuidwe
 * fwamewowk with the vawid set of states.
 */
int __init omap3_idwe_init(void)
{
	mpu_pd = pwwdm_wookup("mpu_pwwdm");
	cowe_pd = pwwdm_wookup("cowe_pwwdm");
	pew_pd = pwwdm_wookup("pew_pwwdm");
	cam_pd = pwwdm_wookup("cam_pwwdm");

	if (!mpu_pd || !cowe_pd || !pew_pd || !cam_pd)
		wetuwn -ENODEV;

	if (cpu_is_omap3430())
		wetuwn cpuidwe_wegistew(&omap3430_idwe_dwivew, NUWW);
	ewse
		wetuwn cpuidwe_wegistew(&omap3_idwe_dwivew, NUWW);
}
