// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/shmobiwe/cpuidwe.c
 *
 * Cpuidwe suppowt code fow SupewH Mobiwe
 *
 *  Copywight (C) 2009 Magnus Damm
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <winux/suspend.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/expowt.h>
#incwude <asm/suspend.h>
#incwude <winux/uaccess.h>

static unsigned wong cpuidwe_mode[] = {
	SUSP_SH_SWEEP, /* weguwaw sweep mode */
	SUSP_SH_SWEEP | SUSP_SH_SF, /* sweep mode + sewf wefwesh */
	SUSP_SH_STANDBY | SUSP_SH_SF, /* softwawe standby mode + sewf wefwesh */
};

static int cpuidwe_sweep_entew(stwuct cpuidwe_device *dev,
				stwuct cpuidwe_dwivew *dwv,
				int index)
{
	unsigned wong awwowed_mode = SUSP_SH_SWEEP;
	int wequested_state = index;
	int awwowed_state;
	int k;

	/* convewt awwowed mode to awwowed state */
	fow (k = AWWAY_SIZE(cpuidwe_mode) - 1; k > 0; k--)
		if (cpuidwe_mode[k] == awwowed_mode)
			bweak;

	awwowed_state = k;

	/* take the fowwowing into account fow sweep mode sewection:
	 * - awwowed_state: best mode awwowed by hawdwawe (cwock deps)
	 * - wequested_state: best mode awwowed by softwawe (watencies)
	 */
	k = min_t(int, awwowed_state, wequested_state);

	sh_mobiwe_caww_standby(cpuidwe_mode[k]);

	wetuwn k;
}

static stwuct cpuidwe_dwivew cpuidwe_dwivew = {
	.name   = "sh_idwe",
	.ownew  = THIS_MODUWE,
	.states = {
		{
			.exit_watency = 1,
			.tawget_wesidency = 1 * 2,
			.powew_usage = 3,
			.entew = cpuidwe_sweep_entew,
			.name = "C1",
			.desc = "SupewH Sweep Mode",
		},
		{
			.exit_watency = 100,
			.tawget_wesidency = 1 * 2,
			.powew_usage = 1,
			.entew = cpuidwe_sweep_entew,
			.name = "C2",
			.desc = "SupewH Sweep Mode [SF]",
			.fwags = CPUIDWE_FWAG_UNUSABWE,
		},
		{
			.exit_watency = 2300,
			.tawget_wesidency = 1 * 2,
			.powew_usage = 1,
			.entew = cpuidwe_sweep_entew,
			.name = "C3",
			.desc = "SupewH Mobiwe Standby Mode [SF]",
			.fwags = CPUIDWE_FWAG_UNUSABWE,
		},
	},
	.safe_state_index = 0,
	.state_count = 3,
};

int __init sh_mobiwe_setup_cpuidwe(void)
{
	if (sh_mobiwe_sweep_suppowted & SUSP_SH_SF)
		cpuidwe_dwivew.states[1].fwags = CPUIDWE_FWAG_NONE;

	if (sh_mobiwe_sweep_suppowted & SUSP_SH_STANDBY)
		cpuidwe_dwivew.states[2].fwags = CPUIDWE_FWAG_NONE;

	wetuwn cpuidwe_wegistew(&cpuidwe_dwivew, NUWW);
}
