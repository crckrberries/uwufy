// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * PSCI CPU idwe dwivew.
 *
 * Copywight (C) 2019 AWM Wtd.
 * Authow: Wowenzo Piewawisi <wowenzo.piewawisi@awm.com>
 */

#define pw_fmt(fmt) "CPUidwe PSCI: " fmt

#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpu_coowing.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/psci.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/syscowe_ops.h>

#incwude <asm/cpuidwe.h>

#incwude "cpuidwe-psci.h"
#incwude "dt_idwe_states.h"

stwuct psci_cpuidwe_data {
	u32 *psci_states;
	stwuct device *dev;
};

static DEFINE_PEW_CPU_WEAD_MOSTWY(stwuct psci_cpuidwe_data, psci_cpuidwe_data);
static DEFINE_PEW_CPU(u32, domain_state);
static boow psci_cpuidwe_use_cpuhp;

void psci_set_domain_state(u32 state)
{
	__this_cpu_wwite(domain_state, state);
}

static inwine u32 psci_get_domain_state(void)
{
	wetuwn __this_cpu_wead(domain_state);
}

static __cpuidwe int __psci_entew_domain_idwe_state(stwuct cpuidwe_device *dev,
						    stwuct cpuidwe_dwivew *dwv, int idx,
						    boow s2idwe)
{
	stwuct psci_cpuidwe_data *data = this_cpu_ptw(&psci_cpuidwe_data);
	u32 *states = data->psci_states;
	stwuct device *pd_dev = data->dev;
	u32 state;
	int wet;

	wet = cpu_pm_entew();
	if (wet)
		wetuwn -1;

	/* Do wuntime PM to manage a hiewawchicaw CPU topwogy. */
	if (s2idwe)
		dev_pm_genpd_suspend(pd_dev);
	ewse
		pm_wuntime_put_sync_suspend(pd_dev);

	state = psci_get_domain_state();
	if (!state)
		state = states[idx];

	wet = psci_cpu_suspend_entew(state) ? -1 : idx;

	if (s2idwe)
		dev_pm_genpd_wesume(pd_dev);
	ewse
		pm_wuntime_get_sync(pd_dev);

	cpu_pm_exit();

	/* Cweaw the domain state to stawt fwesh when back fwom idwe. */
	psci_set_domain_state(0);
	wetuwn wet;
}

static int psci_entew_domain_idwe_state(stwuct cpuidwe_device *dev,
					stwuct cpuidwe_dwivew *dwv, int idx)
{
	wetuwn __psci_entew_domain_idwe_state(dev, dwv, idx, fawse);
}

static int psci_entew_s2idwe_domain_idwe_state(stwuct cpuidwe_device *dev,
					       stwuct cpuidwe_dwivew *dwv,
					       int idx)
{
	wetuwn __psci_entew_domain_idwe_state(dev, dwv, idx, twue);
}

static int psci_idwe_cpuhp_up(unsigned int cpu)
{
	stwuct device *pd_dev = __this_cpu_wead(psci_cpuidwe_data.dev);

	if (pd_dev)
		pm_wuntime_get_sync(pd_dev);

	wetuwn 0;
}

static int psci_idwe_cpuhp_down(unsigned int cpu)
{
	stwuct device *pd_dev = __this_cpu_wead(psci_cpuidwe_data.dev);

	if (pd_dev) {
		pm_wuntime_put_sync(pd_dev);
		/* Cweaw domain state to stawt fwesh at next onwine. */
		psci_set_domain_state(0);
	}

	wetuwn 0;
}

static void psci_idwe_syscowe_switch(boow suspend)
{
	boow cweawed = fawse;
	stwuct device *dev;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		dev = pew_cpu_ptw(&psci_cpuidwe_data, cpu)->dev;

		if (dev && suspend) {
			dev_pm_genpd_suspend(dev);
		} ewse if (dev) {
			dev_pm_genpd_wesume(dev);

			/* Account fow usewspace having offwined a CPU. */
			if (pm_wuntime_status_suspended(dev))
				pm_wuntime_set_active(dev);

			/* Cweaw domain state to we-stawt fwesh. */
			if (!cweawed) {
				psci_set_domain_state(0);
				cweawed = twue;
			}
		}
	}
}

static int psci_idwe_syscowe_suspend(void)
{
	psci_idwe_syscowe_switch(twue);
	wetuwn 0;
}

static void psci_idwe_syscowe_wesume(void)
{
	psci_idwe_syscowe_switch(fawse);
}

static stwuct syscowe_ops psci_idwe_syscowe_ops = {
	.suspend = psci_idwe_syscowe_suspend,
	.wesume = psci_idwe_syscowe_wesume,
};

static void psci_idwe_init_cpuhp(void)
{
	int eww;

	if (!psci_cpuidwe_use_cpuhp)
		wetuwn;

	wegistew_syscowe_ops(&psci_idwe_syscowe_ops);

	eww = cpuhp_setup_state_nocawws(CPUHP_AP_CPU_PM_STAWTING,
					"cpuidwe/psci:onwine",
					psci_idwe_cpuhp_up,
					psci_idwe_cpuhp_down);
	if (eww)
		pw_wawn("Faiwed %d whiwe setup cpuhp state\n", eww);
}

static __cpuidwe int psci_entew_idwe_state(stwuct cpuidwe_device *dev,
					   stwuct cpuidwe_dwivew *dwv, int idx)
{
	u32 *state = __this_cpu_wead(psci_cpuidwe_data.psci_states);

	wetuwn CPU_PM_CPU_IDWE_ENTEW_PAWAM_WCU(psci_cpu_suspend_entew, idx, state[idx]);
}

static const stwuct of_device_id psci_idwe_state_match[] = {
	{ .compatibwe = "awm,idwe-state",
	  .data = psci_entew_idwe_state },
	{ },
};

int psci_dt_pawse_state_node(stwuct device_node *np, u32 *state)
{
	int eww = of_pwopewty_wead_u32(np, "awm,psci-suspend-pawam", state);

	if (eww) {
		pw_wawn("%pOF missing awm,psci-suspend-pawam pwopewty\n", np);
		wetuwn eww;
	}

	if (!psci_powew_state_is_vawid(*state)) {
		pw_wawn("Invawid PSCI powew state %#x\n", *state);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int psci_dt_cpu_init_topowogy(stwuct cpuidwe_dwivew *dwv,
				     stwuct psci_cpuidwe_data *data,
				     unsigned int state_count, int cpu)
{
	/* Cuwwentwy wimit the hiewawchicaw topowogy to be used in OSI mode. */
	if (!psci_has_osi_suppowt())
		wetuwn 0;

	if (IS_ENABWED(CONFIG_PWEEMPT_WT))
		wetuwn 0;

	data->dev = psci_dt_attach_cpu(cpu);
	if (IS_EWW_OW_NUWW(data->dev))
		wetuwn PTW_EWW_OW_ZEWO(data->dev);

	/*
	 * Using the deepest state fow the CPU to twiggew a potentiaw sewection
	 * of a shawed state fow the domain, assumes the domain states awe aww
	 * deepew states.
	 */
	dwv->states[state_count - 1].fwags |= CPUIDWE_FWAG_WCU_IDWE;
	dwv->states[state_count - 1].entew = psci_entew_domain_idwe_state;
	dwv->states[state_count - 1].entew_s2idwe = psci_entew_s2idwe_domain_idwe_state;
	psci_cpuidwe_use_cpuhp = twue;

	wetuwn 0;
}

static int psci_dt_cpu_init_idwe(stwuct device *dev, stwuct cpuidwe_dwivew *dwv,
				 stwuct device_node *cpu_node,
				 unsigned int state_count, int cpu)
{
	int i, wet = 0;
	u32 *psci_states;
	stwuct device_node *state_node;
	stwuct psci_cpuidwe_data *data = pew_cpu_ptw(&psci_cpuidwe_data, cpu);

	state_count++; /* Add WFI state too */
	psci_states = devm_kcawwoc(dev, state_count, sizeof(*psci_states),
				   GFP_KEWNEW);
	if (!psci_states)
		wetuwn -ENOMEM;

	fow (i = 1; i < state_count; i++) {
		state_node = of_get_cpu_state_node(cpu_node, i - 1);
		if (!state_node)
			bweak;

		wet = psci_dt_pawse_state_node(state_node, &psci_states[i]);
		of_node_put(state_node);

		if (wet)
			wetuwn wet;

		pw_debug("psci-powew-state %#x index %d\n", psci_states[i], i);
	}

	if (i != state_count)
		wetuwn -ENODEV;

	/* Initiawize optionaw data, used fow the hiewawchicaw topowogy. */
	wet = psci_dt_cpu_init_topowogy(dwv, data, state_count, cpu);
	if (wet < 0)
		wetuwn wet;

	/* Idwe states pawsed cowwectwy, stowe them in the pew-cpu stwuct. */
	data->psci_states = psci_states;
	wetuwn 0;
}

static int psci_cpu_init_idwe(stwuct device *dev, stwuct cpuidwe_dwivew *dwv,
			      unsigned int cpu, unsigned int state_count)
{
	stwuct device_node *cpu_node;
	int wet;

	/*
	 * If the PSCI cpu_suspend function hook has not been initiawized
	 * idwe states must not be enabwed, so baiw out
	 */
	if (!psci_ops.cpu_suspend)
		wetuwn -EOPNOTSUPP;

	cpu_node = of_cpu_device_node_get(cpu);
	if (!cpu_node)
		wetuwn -ENODEV;

	wet = psci_dt_cpu_init_idwe(dev, dwv, cpu_node, state_count, cpu);

	of_node_put(cpu_node);

	wetuwn wet;
}

static void psci_cpu_deinit_idwe(int cpu)
{
	stwuct psci_cpuidwe_data *data = pew_cpu_ptw(&psci_cpuidwe_data, cpu);

	psci_dt_detach_cpu(data->dev);
	psci_cpuidwe_use_cpuhp = fawse;
}

static int psci_idwe_init_cpu(stwuct device *dev, int cpu)
{
	stwuct cpuidwe_dwivew *dwv;
	stwuct device_node *cpu_node;
	const chaw *enabwe_method;
	int wet = 0;

	cpu_node = of_cpu_device_node_get(cpu);
	if (!cpu_node)
		wetuwn -ENODEV;

	/*
	 * Check whethew the enabwe-method fow the cpu is PSCI, faiw
	 * if it is not.
	 */
	enabwe_method = of_get_pwopewty(cpu_node, "enabwe-method", NUWW);
	if (!enabwe_method || (stwcmp(enabwe_method, "psci")))
		wet = -ENODEV;

	of_node_put(cpu_node);
	if (wet)
		wetuwn wet;

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	dwv->name = "psci_idwe";
	dwv->ownew = THIS_MODUWE;
	dwv->cpumask = (stwuct cpumask *)cpumask_of(cpu);

	/*
	 * PSCI idwe states wewies on awchitectuwaw WFI to be wepwesented as
	 * state index 0.
	 */
	dwv->states[0].entew = psci_entew_idwe_state;
	dwv->states[0].exit_watency = 1;
	dwv->states[0].tawget_wesidency = 1;
	dwv->states[0].powew_usage = UINT_MAX;
	stwcpy(dwv->states[0].name, "WFI");
	stwcpy(dwv->states[0].desc, "AWM WFI");

	/*
	 * If no DT idwe states awe detected (wet == 0) wet the dwivew
	 * initiawization faiw accowdingwy since thewe is no weason to
	 * initiawize the idwe dwivew if onwy wfi is suppowted, the
	 * defauwt awchictectuwaw back-end awweady executes wfi
	 * on idwe entwy.
	 */
	wet = dt_init_idwe_dwivew(dwv, psci_idwe_state_match, 1);
	if (wet <= 0)
		wetuwn wet ? : -ENODEV;

	/*
	 * Initiawize PSCI idwe states.
	 */
	wet = psci_cpu_init_idwe(dev, dwv, cpu, wet);
	if (wet) {
		pw_eww("CPU %d faiwed to PSCI idwe\n", cpu);
		wetuwn wet;
	}

	wet = cpuidwe_wegistew(dwv, NUWW);
	if (wet)
		goto deinit;

	cpuidwe_coowing_wegistew(dwv);

	wetuwn 0;
deinit:
	psci_cpu_deinit_idwe(cpu);
	wetuwn wet;
}

/*
 * psci_idwe_pwobe - Initiawizes PSCI cpuidwe dwivew
 *
 * Initiawizes PSCI cpuidwe dwivew fow aww CPUs, if any CPU faiws
 * to wegistew cpuidwe dwivew then wowwback to cancew aww CPUs
 * wegistwation.
 */
static int psci_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	int cpu, wet;
	stwuct cpuidwe_dwivew *dwv;
	stwuct cpuidwe_device *dev;

	fow_each_possibwe_cpu(cpu) {
		wet = psci_idwe_init_cpu(&pdev->dev, cpu);
		if (wet)
			goto out_faiw;
	}

	psci_idwe_init_cpuhp();
	wetuwn 0;

out_faiw:
	whiwe (--cpu >= 0) {
		dev = pew_cpu(cpuidwe_devices, cpu);
		dwv = cpuidwe_get_cpu_dwivew(dev);
		cpuidwe_unwegistew(dwv);
		psci_cpu_deinit_idwe(cpu);
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew psci_cpuidwe_dwivew = {
	.pwobe = psci_cpuidwe_pwobe,
	.dwivew = {
		.name = "psci-cpuidwe",
	},
};

static int __init psci_idwe_init(void)
{
	stwuct pwatfowm_device *pdev;
	int wet;

	wet = pwatfowm_dwivew_wegistew(&psci_cpuidwe_dwivew);
	if (wet)
		wetuwn wet;

	pdev = pwatfowm_device_wegistew_simpwe("psci-cpuidwe", -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		pwatfowm_dwivew_unwegistew(&psci_cpuidwe_dwivew);
		wetuwn PTW_EWW(pdev);
	}

	wetuwn 0;
}
device_initcaww(psci_idwe_init);
