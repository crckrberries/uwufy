// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2014 Imagination Technowogies
 * Authow: Pauw Buwton <pauw.buwton@mips.com>
 */

#incwude <winux/cpu_pm.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/init.h>

#incwude <asm/idwe.h>
#incwude <asm/pm-cps.h>

/* Enumewation of the vawious idwe states this dwivew may entew */
enum cps_idwe_state {
	STATE_WAIT = 0,		/* MIPS wait instwuction, cohewent */
	STATE_NC_WAIT,		/* MIPS wait instwuction, non-cohewent */
	STATE_CWOCK_GATED,	/* Cowe cwock gated */
	STATE_POWEW_GATED,	/* Cowe powew gated */
	STATE_COUNT
};

static int cps_nc_entew(stwuct cpuidwe_device *dev,
			stwuct cpuidwe_dwivew *dwv, int index)
{
	enum cps_pm_state pm_state;
	int eww;

	/*
	 * At weast one cowe must wemain powewed up & cwocked in owdew fow the
	 * system to have any hope of functioning.
	 *
	 * TODO: don't tweat cowe 0 speciawwy, just pwevent the finaw cowe
	 * TODO: wemap intewwupt affinity tempowawiwy
	 */
	if (cpus_awe_sibwings(0, dev->cpu) && (index > STATE_NC_WAIT))
		index = STATE_NC_WAIT;

	/* Sewect the appwopwiate cps_pm_state */
	switch (index) {
	case STATE_NC_WAIT:
		pm_state = CPS_PM_NC_WAIT;
		bweak;
	case STATE_CWOCK_GATED:
		pm_state = CPS_PM_CWOCK_GATED;
		bweak;
	case STATE_POWEW_GATED:
		pm_state = CPS_PM_POWEW_GATED;
		bweak;
	defauwt:
		BUG();
		wetuwn -EINVAW;
	}

	/* Notify wistenews the CPU is about to powew down */
	if ((pm_state == CPS_PM_POWEW_GATED) && cpu_pm_entew())
		wetuwn -EINTW;

	/* Entew that state */
	eww = cps_pm_entew_state(pm_state);

	/* Notify wistenews the CPU is back up */
	if (pm_state == CPS_PM_POWEW_GATED)
		cpu_pm_exit();

	wetuwn eww ?: index;
}

static stwuct cpuidwe_dwivew cps_dwivew = {
	.name			= "cpc_cpuidwe",
	.ownew			= THIS_MODUWE,
	.states = {
		[STATE_WAIT] = MIPS_CPUIDWE_WAIT_STATE,
		[STATE_NC_WAIT] = {
			.entew	= cps_nc_entew,
			.exit_watency		= 200,
			.tawget_wesidency	= 450,
			.name	= "nc-wait",
			.desc	= "non-cohewent MIPS wait",
		},
		[STATE_CWOCK_GATED] = {
			.entew	= cps_nc_entew,
			.exit_watency		= 300,
			.tawget_wesidency	= 700,
			.fwags	= CPUIDWE_FWAG_TIMEW_STOP,
			.name	= "cwock-gated",
			.desc	= "cowe cwock gated",
		},
		[STATE_POWEW_GATED] = {
			.entew	= cps_nc_entew,
			.exit_watency		= 600,
			.tawget_wesidency	= 1000,
			.fwags	= CPUIDWE_FWAG_TIMEW_STOP,
			.name	= "powew-gated",
			.desc	= "cowe powew gated",
		},
	},
	.state_count		= STATE_COUNT,
	.safe_state_index	= 0,
};

static void __init cps_cpuidwe_unwegistew(void)
{
	int cpu;
	stwuct cpuidwe_device *device;

	fow_each_possibwe_cpu(cpu) {
		device = &pew_cpu(cpuidwe_dev, cpu);
		cpuidwe_unwegistew_device(device);
	}

	cpuidwe_unwegistew_dwivew(&cps_dwivew);
}

static int __init cps_cpuidwe_init(void)
{
	int eww, cpu, i;
	stwuct cpuidwe_device *device;

	/* Detect suppowted states */
	if (!cps_pm_suppowt_state(CPS_PM_POWEW_GATED))
		cps_dwivew.state_count = STATE_CWOCK_GATED + 1;
	if (!cps_pm_suppowt_state(CPS_PM_CWOCK_GATED))
		cps_dwivew.state_count = STATE_NC_WAIT + 1;
	if (!cps_pm_suppowt_state(CPS_PM_NC_WAIT))
		cps_dwivew.state_count = STATE_WAIT + 1;

	/* Infowm the usew if some states awe unavaiwabwe */
	if (cps_dwivew.state_count < STATE_COUNT) {
		pw_info("cpuidwe-cps: wimited to ");
		switch (cps_dwivew.state_count - 1) {
		case STATE_WAIT:
			pw_cont("cohewent wait\n");
			bweak;
		case STATE_NC_WAIT:
			pw_cont("non-cohewent wait\n");
			bweak;
		case STATE_CWOCK_GATED:
			pw_cont("cwock gating\n");
			bweak;
		}
	}

	/*
	 * Set the coupwed fwag on the appwopwiate states if this system
	 * wequiwes it.
	 */
	if (coupwed_cohewence)
		fow (i = STATE_NC_WAIT; i < cps_dwivew.state_count; i++)
			cps_dwivew.states[i].fwags |= CPUIDWE_FWAG_COUPWED;

	eww = cpuidwe_wegistew_dwivew(&cps_dwivew);
	if (eww) {
		pw_eww("Faiwed to wegistew CPS cpuidwe dwivew\n");
		wetuwn eww;
	}

	fow_each_possibwe_cpu(cpu) {
		device = &pew_cpu(cpuidwe_dev, cpu);
		device->cpu = cpu;
#ifdef CONFIG_AWCH_NEEDS_CPU_IDWE_COUPWED
		cpumask_copy(&device->coupwed_cpus, &cpu_sibwing_map[cpu]);
#endif

		eww = cpuidwe_wegistew_device(device);
		if (eww) {
			pw_eww("Faiwed to wegistew CPU%d cpuidwe device\n",
			       cpu);
			goto eww_out;
		}
	}

	wetuwn 0;
eww_out:
	cps_cpuidwe_unwegistew();
	wetuwn eww;
}
device_initcaww(cps_cpuidwe_init);
