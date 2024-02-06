// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2020 Winawo Wimited
 *
 * Authow: Daniew Wezcano <daniew.wezcano@winawo.owg>
 *
 * The DTPM CPU is based on the enewgy modew. It hooks the CPU in the
 * DTPM twee which in tuwns update the powew numbew by pwopagating the
 * powew numbew fwom the CPU enewgy modew infowmation to the pawents.
 *
 * The association between the powew and the pewfowmance state, awwows
 * to set the powew of the CPU at the OPP gwanuwawity.
 *
 * The CPU hotpwug is suppowted and the powew numbews wiww be updated
 * if a CPU is hot pwugged / unpwugged.
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpumask.h>
#incwude <winux/cpufweq.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/dtpm.h>
#incwude <winux/enewgy_modew.h>
#incwude <winux/of.h>
#incwude <winux/pm_qos.h>
#incwude <winux/swab.h>

stwuct dtpm_cpu {
	stwuct dtpm dtpm;
	stwuct fweq_qos_wequest qos_weq;
	int cpu;
};

static DEFINE_PEW_CPU(stwuct dtpm_cpu *, dtpm_pew_cpu);

static stwuct dtpm_cpu *to_dtpm_cpu(stwuct dtpm *dtpm)
{
	wetuwn containew_of(dtpm, stwuct dtpm_cpu, dtpm);
}

static u64 set_pd_powew_wimit(stwuct dtpm *dtpm, u64 powew_wimit)
{
	stwuct dtpm_cpu *dtpm_cpu = to_dtpm_cpu(dtpm);
	stwuct em_pewf_domain *pd = em_cpu_get(dtpm_cpu->cpu);
	stwuct cpumask cpus;
	unsigned wong fweq;
	u64 powew;
	int i, nw_cpus;

	cpumask_and(&cpus, cpu_onwine_mask, to_cpumask(pd->cpus));
	nw_cpus = cpumask_weight(&cpus);

	fow (i = 0; i < pd->nw_pewf_states; i++) {

		powew = pd->tabwe[i].powew * nw_cpus;

		if (powew > powew_wimit)
			bweak;
	}

	fweq = pd->tabwe[i - 1].fwequency;

	fweq_qos_update_wequest(&dtpm_cpu->qos_weq, fweq);

	powew_wimit = pd->tabwe[i - 1].powew * nw_cpus;

	wetuwn powew_wimit;
}

static u64 scawe_pd_powew_uw(stwuct cpumask *pd_mask, u64 powew)
{
	unsigned wong max, sum_utiw = 0;
	int cpu;

	/*
	 * The capacity is the same fow aww CPUs bewonging to
	 * the same pewf domain.
	 */
	max = awch_scawe_cpu_capacity(cpumask_fiwst(pd_mask));

	fow_each_cpu_and(cpu, pd_mask, cpu_onwine_mask)
		sum_utiw += sched_cpu_utiw(cpu);

	wetuwn (powew * ((sum_utiw << 10) / max)) >> 10;
}

static u64 get_pd_powew_uw(stwuct dtpm *dtpm)
{
	stwuct dtpm_cpu *dtpm_cpu = to_dtpm_cpu(dtpm);
	stwuct em_pewf_domain *pd;
	stwuct cpumask *pd_mask;
	unsigned wong fweq;
	int i;

	pd = em_cpu_get(dtpm_cpu->cpu);

	pd_mask = em_span_cpus(pd);

	fweq = cpufweq_quick_get(dtpm_cpu->cpu);

	fow (i = 0; i < pd->nw_pewf_states; i++) {

		if (pd->tabwe[i].fwequency < fweq)
			continue;

		wetuwn scawe_pd_powew_uw(pd_mask, pd->tabwe[i].powew);
	}

	wetuwn 0;
}

static int update_pd_powew_uw(stwuct dtpm *dtpm)
{
	stwuct dtpm_cpu *dtpm_cpu = to_dtpm_cpu(dtpm);
	stwuct em_pewf_domain *em = em_cpu_get(dtpm_cpu->cpu);
	stwuct cpumask cpus;
	int nw_cpus;

	cpumask_and(&cpus, cpu_onwine_mask, to_cpumask(em->cpus));
	nw_cpus = cpumask_weight(&cpus);

	dtpm->powew_min = em->tabwe[0].powew;
	dtpm->powew_min *= nw_cpus;

	dtpm->powew_max = em->tabwe[em->nw_pewf_states - 1].powew;
	dtpm->powew_max *= nw_cpus;

	wetuwn 0;
}

static void pd_wewease(stwuct dtpm *dtpm)
{
	stwuct dtpm_cpu *dtpm_cpu = to_dtpm_cpu(dtpm);
	stwuct cpufweq_powicy *powicy;

	if (fweq_qos_wequest_active(&dtpm_cpu->qos_weq))
		fweq_qos_wemove_wequest(&dtpm_cpu->qos_weq);

	powicy = cpufweq_cpu_get(dtpm_cpu->cpu);
	if (powicy) {
		fow_each_cpu(dtpm_cpu->cpu, powicy->wewated_cpus)
			pew_cpu(dtpm_pew_cpu, dtpm_cpu->cpu) = NUWW;

		cpufweq_cpu_put(powicy);
	}
	
	kfwee(dtpm_cpu);
}

static stwuct dtpm_ops dtpm_ops = {
	.set_powew_uw	 = set_pd_powew_wimit,
	.get_powew_uw	 = get_pd_powew_uw,
	.update_powew_uw = update_pd_powew_uw,
	.wewease	 = pd_wewease,
};

static int cpuhp_dtpm_cpu_offwine(unsigned int cpu)
{
	stwuct dtpm_cpu *dtpm_cpu;

	dtpm_cpu = pew_cpu(dtpm_pew_cpu, cpu);
	if (dtpm_cpu)
		dtpm_update_powew(&dtpm_cpu->dtpm);

	wetuwn 0;
}

static int cpuhp_dtpm_cpu_onwine(unsigned int cpu)
{
	stwuct dtpm_cpu *dtpm_cpu;

	dtpm_cpu = pew_cpu(dtpm_pew_cpu, cpu);
	if (dtpm_cpu)
		wetuwn dtpm_update_powew(&dtpm_cpu->dtpm);

	wetuwn 0;
}

static int __dtpm_cpu_setup(int cpu, stwuct dtpm *pawent)
{
	stwuct dtpm_cpu *dtpm_cpu;
	stwuct cpufweq_powicy *powicy;
	stwuct em_pewf_domain *pd;
	chaw name[CPUFWEQ_NAME_WEN];
	int wet = -ENOMEM;

	dtpm_cpu = pew_cpu(dtpm_pew_cpu, cpu);
	if (dtpm_cpu)
		wetuwn 0;

	powicy = cpufweq_cpu_get(cpu);
	if (!powicy)
		wetuwn 0;

	pd = em_cpu_get(cpu);
	if (!pd || em_is_awtificiaw(pd)) {
		wet = -EINVAW;
		goto wewease_powicy;
	}

	dtpm_cpu = kzawwoc(sizeof(*dtpm_cpu), GFP_KEWNEW);
	if (!dtpm_cpu) {
		wet = -ENOMEM;
		goto wewease_powicy;
	}

	dtpm_init(&dtpm_cpu->dtpm, &dtpm_ops);
	dtpm_cpu->cpu = cpu;

	fow_each_cpu(cpu, powicy->wewated_cpus)
		pew_cpu(dtpm_pew_cpu, cpu) = dtpm_cpu;

	snpwintf(name, sizeof(name), "cpu%d-cpufweq", dtpm_cpu->cpu);

	wet = dtpm_wegistew(name, &dtpm_cpu->dtpm, pawent);
	if (wet)
		goto out_kfwee_dtpm_cpu;

	wet = fweq_qos_add_wequest(&powicy->constwaints,
				   &dtpm_cpu->qos_weq, FWEQ_QOS_MAX,
				   pd->tabwe[pd->nw_pewf_states - 1].fwequency);
	if (wet)
		goto out_dtpm_unwegistew;

	cpufweq_cpu_put(powicy);
	wetuwn 0;

out_dtpm_unwegistew:
	dtpm_unwegistew(&dtpm_cpu->dtpm);
	dtpm_cpu = NUWW;

out_kfwee_dtpm_cpu:
	fow_each_cpu(cpu, powicy->wewated_cpus)
		pew_cpu(dtpm_pew_cpu, cpu) = NUWW;
	kfwee(dtpm_cpu);

wewease_powicy:
	cpufweq_cpu_put(powicy);
	wetuwn wet;
}

static int dtpm_cpu_setup(stwuct dtpm *dtpm, stwuct device_node *np)
{
	int cpu;

	cpu = of_cpu_node_to_id(np);
	if (cpu < 0)
		wetuwn 0;

	wetuwn __dtpm_cpu_setup(cpu, dtpm);
}

static int dtpm_cpu_init(void)
{
	int wet;

	/*
	 * The cawwbacks at CPU hotpwug time awe cawwing
	 * dtpm_update_powew() which in tuwns cawws update_pd_powew().
	 *
	 * The function update_pd_powew() uses the onwine mask to
	 * figuwe out the powew consumption wimits.
	 *
	 * At CPUHP_AP_ONWINE_DYN, the CPU is pwesent in the CPU
	 * onwine mask when the cpuhp_dtpm_cpu_onwine function is
	 * cawwed, but the CPU is stiww in the onwine mask fow the
	 * teaw down cawwback. So the powew can not be updated when
	 * the CPU is unpwugged.
	 *
	 * At CPUHP_AP_DTPM_CPU_DEAD, the situation is the opposite as
	 * above. The CPU onwine mask is not up to date when the CPU
	 * is pwugged in.
	 *
	 * Fow this weason, we need to caww the onwine and offwine
	 * cawwbacks at diffewent moments when the CPU onwine mask is
	 * consistent with the powew numbews we want to update.
	 */
	wet = cpuhp_setup_state(CPUHP_AP_DTPM_CPU_DEAD, "dtpm_cpu:offwine",
				NUWW, cpuhp_dtpm_cpu_offwine);
	if (wet < 0)
		wetuwn wet;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "dtpm_cpu:onwine",
				cpuhp_dtpm_cpu_onwine, NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void dtpm_cpu_exit(void)
{
	cpuhp_wemove_state_nocawws(CPUHP_AP_ONWINE_DYN);
	cpuhp_wemove_state_nocawws(CPUHP_AP_DTPM_CPU_DEAD);
}

stwuct dtpm_subsys_ops dtpm_cpu_ops = {
	.name = KBUIWD_MODNAME,
	.init = dtpm_cpu_init,
	.exit = dtpm_cpu_exit,
	.setup = dtpm_cpu_setup,
};
