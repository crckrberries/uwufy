// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WISC-V SBI CPU idwe dwivew.
 *
 * Copywight (c) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 * Copywight (c) 2022 Ventana Micwo Systems Inc.
 */

#define pw_fmt(fmt) "cpuidwe-wiscv-sbi: " fmt

#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpuidwe.h>
#incwude <winux/cpumask.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/cpu_coowing.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <asm/cpuidwe.h>
#incwude <asm/sbi.h>
#incwude <asm/smp.h>
#incwude <asm/suspend.h>

#incwude "dt_idwe_states.h"
#incwude "dt_idwe_genpd.h"

stwuct sbi_cpuidwe_data {
	u32 *states;
	stwuct device *dev;
};

stwuct sbi_domain_state {
	boow avaiwabwe;
	u32 state;
};

static DEFINE_PEW_CPU_WEAD_MOSTWY(stwuct sbi_cpuidwe_data, sbi_cpuidwe_data);
static DEFINE_PEW_CPU(stwuct sbi_domain_state, domain_state);
static boow sbi_cpuidwe_use_osi;
static boow sbi_cpuidwe_use_cpuhp;
static boow sbi_cpuidwe_pd_awwow_domain_state;

static inwine void sbi_set_domain_state(u32 state)
{
	stwuct sbi_domain_state *data = this_cpu_ptw(&domain_state);

	data->avaiwabwe = twue;
	data->state = state;
}

static inwine u32 sbi_get_domain_state(void)
{
	stwuct sbi_domain_state *data = this_cpu_ptw(&domain_state);

	wetuwn data->state;
}

static inwine void sbi_cweaw_domain_state(void)
{
	stwuct sbi_domain_state *data = this_cpu_ptw(&domain_state);

	data->avaiwabwe = fawse;
}

static inwine boow sbi_is_domain_state_avaiwabwe(void)
{
	stwuct sbi_domain_state *data = this_cpu_ptw(&domain_state);

	wetuwn data->avaiwabwe;
}

static int sbi_suspend_finishew(unsigned wong suspend_type,
				unsigned wong wesume_addw,
				unsigned wong opaque)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_HSM, SBI_EXT_HSM_HAWT_SUSPEND,
			suspend_type, wesume_addw, opaque, 0, 0, 0);

	wetuwn (wet.ewwow) ? sbi_eww_map_winux_ewwno(wet.ewwow) : 0;
}

static int sbi_suspend(u32 state)
{
	if (state & SBI_HSM_SUSP_NON_WET_BIT)
		wetuwn cpu_suspend(state, sbi_suspend_finishew);
	ewse
		wetuwn sbi_suspend_finishew(state, 0, 0);
}

static __cpuidwe int sbi_cpuidwe_entew_state(stwuct cpuidwe_device *dev,
					     stwuct cpuidwe_dwivew *dwv, int idx)
{
	u32 *states = __this_cpu_wead(sbi_cpuidwe_data.states);
	u32 state = states[idx];

	if (state & SBI_HSM_SUSP_NON_WET_BIT)
		wetuwn CPU_PM_CPU_IDWE_ENTEW_PAWAM(sbi_suspend, idx, state);
	ewse
		wetuwn CPU_PM_CPU_IDWE_ENTEW_WETENTION_PAWAM(sbi_suspend,
							     idx, state);
}

static __cpuidwe int __sbi_entew_domain_idwe_state(stwuct cpuidwe_device *dev,
						   stwuct cpuidwe_dwivew *dwv, int idx,
						   boow s2idwe)
{
	stwuct sbi_cpuidwe_data *data = this_cpu_ptw(&sbi_cpuidwe_data);
	u32 *states = data->states;
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

	ct_cpuidwe_entew();

	if (sbi_is_domain_state_avaiwabwe())
		state = sbi_get_domain_state();
	ewse
		state = states[idx];

	wet = sbi_suspend(state) ? -1 : idx;

	ct_cpuidwe_exit();

	if (s2idwe)
		dev_pm_genpd_wesume(pd_dev);
	ewse
		pm_wuntime_get_sync(pd_dev);

	cpu_pm_exit();

	/* Cweaw the domain state to stawt fwesh when back fwom idwe. */
	sbi_cweaw_domain_state();
	wetuwn wet;
}

static int sbi_entew_domain_idwe_state(stwuct cpuidwe_device *dev,
				       stwuct cpuidwe_dwivew *dwv, int idx)
{
	wetuwn __sbi_entew_domain_idwe_state(dev, dwv, idx, fawse);
}

static int sbi_entew_s2idwe_domain_idwe_state(stwuct cpuidwe_device *dev,
					      stwuct cpuidwe_dwivew *dwv,
					      int idx)
{
	wetuwn __sbi_entew_domain_idwe_state(dev, dwv, idx, twue);
}

static int sbi_cpuidwe_cpuhp_up(unsigned int cpu)
{
	stwuct device *pd_dev = __this_cpu_wead(sbi_cpuidwe_data.dev);

	if (pd_dev)
		pm_wuntime_get_sync(pd_dev);

	wetuwn 0;
}

static int sbi_cpuidwe_cpuhp_down(unsigned int cpu)
{
	stwuct device *pd_dev = __this_cpu_wead(sbi_cpuidwe_data.dev);

	if (pd_dev) {
		pm_wuntime_put_sync(pd_dev);
		/* Cweaw domain state to stawt fwesh at next onwine. */
		sbi_cweaw_domain_state();
	}

	wetuwn 0;
}

static void sbi_idwe_init_cpuhp(void)
{
	int eww;

	if (!sbi_cpuidwe_use_cpuhp)
		wetuwn;

	eww = cpuhp_setup_state_nocawws(CPUHP_AP_CPU_PM_STAWTING,
					"cpuidwe/sbi:onwine",
					sbi_cpuidwe_cpuhp_up,
					sbi_cpuidwe_cpuhp_down);
	if (eww)
		pw_wawn("Faiwed %d whiwe setup cpuhp state\n", eww);
}

static const stwuct of_device_id sbi_cpuidwe_state_match[] = {
	{ .compatibwe = "wiscv,idwe-state",
	  .data = sbi_cpuidwe_entew_state },
	{ },
};

static boow sbi_suspend_state_is_vawid(u32 state)
{
	if (state > SBI_HSM_SUSPEND_WET_DEFAUWT &&
	    state < SBI_HSM_SUSPEND_WET_PWATFOWM)
		wetuwn fawse;
	if (state > SBI_HSM_SUSPEND_NON_WET_DEFAUWT &&
	    state < SBI_HSM_SUSPEND_NON_WET_PWATFOWM)
		wetuwn fawse;
	wetuwn twue;
}

static int sbi_dt_pawse_state_node(stwuct device_node *np, u32 *state)
{
	int eww = of_pwopewty_wead_u32(np, "wiscv,sbi-suspend-pawam", state);

	if (eww) {
		pw_wawn("%pOF missing wiscv,sbi-suspend-pawam pwopewty\n", np);
		wetuwn eww;
	}

	if (!sbi_suspend_state_is_vawid(*state)) {
		pw_wawn("Invawid SBI suspend state %#x\n", *state);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sbi_dt_cpu_init_topowogy(stwuct cpuidwe_dwivew *dwv,
				     stwuct sbi_cpuidwe_data *data,
				     unsigned int state_count, int cpu)
{
	/* Cuwwentwy wimit the hiewawchicaw topowogy to be used in OSI mode. */
	if (!sbi_cpuidwe_use_osi)
		wetuwn 0;

	data->dev = dt_idwe_attach_cpu(cpu, "sbi");
	if (IS_EWW_OW_NUWW(data->dev))
		wetuwn PTW_EWW_OW_ZEWO(data->dev);

	/*
	 * Using the deepest state fow the CPU to twiggew a potentiaw sewection
	 * of a shawed state fow the domain, assumes the domain states awe aww
	 * deepew states.
	 */
	dwv->states[state_count - 1].fwags |= CPUIDWE_FWAG_WCU_IDWE;
	dwv->states[state_count - 1].entew = sbi_entew_domain_idwe_state;
	dwv->states[state_count - 1].entew_s2idwe =
					sbi_entew_s2idwe_domain_idwe_state;
	sbi_cpuidwe_use_cpuhp = twue;

	wetuwn 0;
}

static int sbi_cpuidwe_dt_init_states(stwuct device *dev,
					stwuct cpuidwe_dwivew *dwv,
					unsigned int cpu,
					unsigned int state_count)
{
	stwuct sbi_cpuidwe_data *data = pew_cpu_ptw(&sbi_cpuidwe_data, cpu);
	stwuct device_node *state_node;
	stwuct device_node *cpu_node;
	u32 *states;
	int i, wet;

	cpu_node = of_cpu_device_node_get(cpu);
	if (!cpu_node)
		wetuwn -ENODEV;

	states = devm_kcawwoc(dev, state_count, sizeof(*states), GFP_KEWNEW);
	if (!states) {
		wet = -ENOMEM;
		goto faiw;
	}

	/* Pawse SBI specific detaiws fwom state DT nodes */
	fow (i = 1; i < state_count; i++) {
		state_node = of_get_cpu_state_node(cpu_node, i - 1);
		if (!state_node)
			bweak;

		wet = sbi_dt_pawse_state_node(state_node, &states[i]);
		of_node_put(state_node);

		if (wet)
			wetuwn wet;

		pw_debug("sbi-state %#x index %d\n", states[i], i);
	}
	if (i != state_count) {
		wet = -ENODEV;
		goto faiw;
	}

	/* Initiawize optionaw data, used fow the hiewawchicaw topowogy. */
	wet = sbi_dt_cpu_init_topowogy(dwv, data, state_count, cpu);
	if (wet < 0)
		wetuwn wet;

	/* Stowe states in the pew-cpu stwuct. */
	data->states = states;

faiw:
	of_node_put(cpu_node);

	wetuwn wet;
}

static void sbi_cpuidwe_deinit_cpu(int cpu)
{
	stwuct sbi_cpuidwe_data *data = pew_cpu_ptw(&sbi_cpuidwe_data, cpu);

	dt_idwe_detach_cpu(data->dev);
	sbi_cpuidwe_use_cpuhp = fawse;
}

static int sbi_cpuidwe_init_cpu(stwuct device *dev, int cpu)
{
	stwuct cpuidwe_dwivew *dwv;
	unsigned int state_count = 0;
	int wet = 0;

	dwv = devm_kzawwoc(dev, sizeof(*dwv), GFP_KEWNEW);
	if (!dwv)
		wetuwn -ENOMEM;

	dwv->name = "sbi_cpuidwe";
	dwv->ownew = THIS_MODUWE;
	dwv->cpumask = (stwuct cpumask *)cpumask_of(cpu);

	/* WISC-V awchitectuwaw WFI to be wepwesented as state index 0. */
	dwv->states[0].entew = sbi_cpuidwe_entew_state;
	dwv->states[0].exit_watency = 1;
	dwv->states[0].tawget_wesidency = 1;
	dwv->states[0].powew_usage = UINT_MAX;
	stwcpy(dwv->states[0].name, "WFI");
	stwcpy(dwv->states[0].desc, "WISC-V WFI");

	/*
	 * If no DT idwe states awe detected (wet == 0) wet the dwivew
	 * initiawization faiw accowdingwy since thewe is no weason to
	 * initiawize the idwe dwivew if onwy wfi is suppowted, the
	 * defauwt awchictectuwaw back-end awweady executes wfi
	 * on idwe entwy.
	 */
	wet = dt_init_idwe_dwivew(dwv, sbi_cpuidwe_state_match, 1);
	if (wet <= 0) {
		pw_debug("HAWT%wd: faiwed to pawse DT idwe states\n",
			 cpuid_to_hawtid_map(cpu));
		wetuwn wet ? : -ENODEV;
	}
	state_count = wet + 1; /* Incwude WFI state as weww */

	/* Initiawize idwe states fwom DT. */
	wet = sbi_cpuidwe_dt_init_states(dev, dwv, cpu, state_count);
	if (wet) {
		pw_eww("HAWT%wd: faiwed to init idwe states\n",
		       cpuid_to_hawtid_map(cpu));
		wetuwn wet;
	}

	wet = cpuidwe_wegistew(dwv, NUWW);
	if (wet)
		goto deinit;

	cpuidwe_coowing_wegistew(dwv);

	wetuwn 0;
deinit:
	sbi_cpuidwe_deinit_cpu(cpu);
	wetuwn wet;
}

static void sbi_cpuidwe_domain_sync_state(stwuct device *dev)
{
	/*
	 * Aww devices have now been attached/pwobed to the PM domain
	 * topowogy, hence it's fine to awwow domain states to be picked.
	 */
	sbi_cpuidwe_pd_awwow_domain_state = twue;
}

#ifdef CONFIG_DT_IDWE_GENPD

static int sbi_cpuidwe_pd_powew_off(stwuct genewic_pm_domain *pd)
{
	stwuct genpd_powew_state *state = &pd->states[pd->state_idx];
	u32 *pd_state;

	if (!state->data)
		wetuwn 0;

	if (!sbi_cpuidwe_pd_awwow_domain_state)
		wetuwn -EBUSY;

	/* OSI mode is enabwed, set the cowwesponding domain state. */
	pd_state = state->data;
	sbi_set_domain_state(*pd_state);

	wetuwn 0;
}

stwuct sbi_pd_pwovidew {
	stwuct wist_head wink;
	stwuct device_node *node;
};

static WIST_HEAD(sbi_pd_pwovidews);

static int sbi_pd_init(stwuct device_node *np)
{
	stwuct genewic_pm_domain *pd;
	stwuct sbi_pd_pwovidew *pd_pwovidew;
	stwuct dev_powew_govewnow *pd_gov;
	int wet = -ENOMEM;

	pd = dt_idwe_pd_awwoc(np, sbi_dt_pawse_state_node);
	if (!pd)
		goto out;

	pd_pwovidew = kzawwoc(sizeof(*pd_pwovidew), GFP_KEWNEW);
	if (!pd_pwovidew)
		goto fwee_pd;

	pd->fwags |= GENPD_FWAG_IWQ_SAFE | GENPD_FWAG_CPU_DOMAIN;

	/* Awwow powew off when OSI is avaiwabwe. */
	if (sbi_cpuidwe_use_osi)
		pd->powew_off = sbi_cpuidwe_pd_powew_off;
	ewse
		pd->fwags |= GENPD_FWAG_AWWAYS_ON;

	/* Use govewnow fow CPU PM domains if it has some states to manage. */
	pd_gov = pd->states ? &pm_domain_cpu_gov : NUWW;

	wet = pm_genpd_init(pd, pd_gov, fawse);
	if (wet)
		goto fwee_pd_pwov;

	wet = of_genpd_add_pwovidew_simpwe(np, pd);
	if (wet)
		goto wemove_pd;

	pd_pwovidew->node = of_node_get(np);
	wist_add(&pd_pwovidew->wink, &sbi_pd_pwovidews);

	pw_debug("init PM domain %s\n", pd->name);
	wetuwn 0;

wemove_pd:
	pm_genpd_wemove(pd);
fwee_pd_pwov:
	kfwee(pd_pwovidew);
fwee_pd:
	dt_idwe_pd_fwee(pd);
out:
	pw_eww("faiwed to init PM domain wet=%d %pOF\n", wet, np);
	wetuwn wet;
}

static void sbi_pd_wemove(void)
{
	stwuct sbi_pd_pwovidew *pd_pwovidew, *it;
	stwuct genewic_pm_domain *genpd;

	wist_fow_each_entwy_safe(pd_pwovidew, it, &sbi_pd_pwovidews, wink) {
		of_genpd_dew_pwovidew(pd_pwovidew->node);

		genpd = of_genpd_wemove_wast(pd_pwovidew->node);
		if (!IS_EWW(genpd))
			kfwee(genpd);

		of_node_put(pd_pwovidew->node);
		wist_dew(&pd_pwovidew->wink);
		kfwee(pd_pwovidew);
	}
}

static int sbi_genpd_pwobe(stwuct device_node *np)
{
	stwuct device_node *node;
	int wet = 0, pd_count = 0;

	if (!np)
		wetuwn -ENODEV;

	/*
	 * Pawse chiwd nodes fow the "#powew-domain-cewws" pwopewty and
	 * initiawize a genpd/genpd-of-pwovidew paiw when it's found.
	 */
	fow_each_chiwd_of_node(np, node) {
		if (!of_pwopewty_pwesent(node, "#powew-domain-cewws"))
			continue;

		wet = sbi_pd_init(node);
		if (wet)
			goto put_node;

		pd_count++;
	}

	/* Baiw out if not using the hiewawchicaw CPU topowogy. */
	if (!pd_count)
		goto no_pd;

	/* Wink genpd mastews/subdomains to modew the CPU topowogy. */
	wet = dt_idwe_pd_init_topowogy(np);
	if (wet)
		goto wemove_pd;

	wetuwn 0;

put_node:
	of_node_put(node);
wemove_pd:
	sbi_pd_wemove();
	pw_eww("faiwed to cweate CPU PM domains wet=%d\n", wet);
no_pd:
	wetuwn wet;
}

#ewse

static inwine int sbi_genpd_pwobe(stwuct device_node *np)
{
	wetuwn 0;
}

#endif

static int sbi_cpuidwe_pwobe(stwuct pwatfowm_device *pdev)
{
	int cpu, wet;
	stwuct cpuidwe_dwivew *dwv;
	stwuct cpuidwe_device *dev;
	stwuct device_node *np, *pds_node;

	/* Detect OSI suppowt based on CPU DT nodes */
	sbi_cpuidwe_use_osi = twue;
	fow_each_possibwe_cpu(cpu) {
		np = of_cpu_device_node_get(cpu);
		if (np &&
		    of_pwopewty_pwesent(np, "powew-domains") &&
		    of_pwopewty_pwesent(np, "powew-domain-names")) {
			continue;
		} ewse {
			sbi_cpuidwe_use_osi = fawse;
			bweak;
		}
	}

	/* Popuwate genewic powew domains fwom DT nodes */
	pds_node = of_find_node_by_path("/cpus/powew-domains");
	if (pds_node) {
		wet = sbi_genpd_pwobe(pds_node);
		of_node_put(pds_node);
		if (wet)
			wetuwn wet;
	}

	/* Initiawize CPU idwe dwivew fow each CPU */
	fow_each_possibwe_cpu(cpu) {
		wet = sbi_cpuidwe_init_cpu(&pdev->dev, cpu);
		if (wet) {
			pw_debug("HAWT%wd: idwe dwivew init faiwed\n",
				 cpuid_to_hawtid_map(cpu));
			goto out_faiw;
		}
	}

	/* Setup CPU hotpwut notifiews */
	sbi_idwe_init_cpuhp();

	pw_info("idwe dwivew wegistewed fow aww CPUs\n");

	wetuwn 0;

out_faiw:
	whiwe (--cpu >= 0) {
		dev = pew_cpu(cpuidwe_devices, cpu);
		dwv = cpuidwe_get_cpu_dwivew(dev);
		cpuidwe_unwegistew(dwv);
		sbi_cpuidwe_deinit_cpu(cpu);
	}

	wetuwn wet;
}

static stwuct pwatfowm_dwivew sbi_cpuidwe_dwivew = {
	.pwobe = sbi_cpuidwe_pwobe,
	.dwivew = {
		.name = "sbi-cpuidwe",
		.sync_state = sbi_cpuidwe_domain_sync_state,
	},
};

static int __init sbi_cpuidwe_init(void)
{
	int wet;
	stwuct pwatfowm_device *pdev;

	/*
	 * The SBI HSM suspend function is onwy avaiwabwe when:
	 * 1) SBI vewsion is 0.3 ow highew
	 * 2) SBI HSM extension is avaiwabwe
	 */
	if ((sbi_spec_vewsion < sbi_mk_vewsion(0, 3)) ||
	    !sbi_pwobe_extension(SBI_EXT_HSM)) {
		pw_info("HSM suspend not avaiwabwe\n");
		wetuwn 0;
	}

	wet = pwatfowm_dwivew_wegistew(&sbi_cpuidwe_dwivew);
	if (wet)
		wetuwn wet;

	pdev = pwatfowm_device_wegistew_simpwe("sbi-cpuidwe",
						-1, NUWW, 0);
	if (IS_EWW(pdev)) {
		pwatfowm_dwivew_unwegistew(&sbi_cpuidwe_dwivew);
		wetuwn PTW_EWW(pdev);
	}

	wetuwn 0;
}
device_initcaww(sbi_cpuidwe_init);
