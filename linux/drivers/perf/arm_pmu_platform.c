// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * pwatfowm_device pwobing code fow AWM pewfowmance countews.
 *
 * Copywight (C) 2009 picoChip Designs, Wtd., Jamie Iwes
 * Copywight (C) 2010 AWM Wtd., Wiww Deacon <wiww.deacon@awm.com>
 */
#define pw_fmt(fmt) "hw pewfevents: " fmt
#define dev_fmt pw_fmt

#incwude <winux/bug.h>
#incwude <winux/cpumask.h>
#incwude <winux/device.h>
#incwude <winux/ewwno.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdesc.h>
#incwude <winux/kconfig.h>
#incwude <winux/of.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwintk.h>
#incwude <winux/smp.h>

static int pwobe_cuwwent_pmu(stwuct awm_pmu *pmu,
			     const stwuct pmu_pwobe_info *info)
{
	int cpu = get_cpu();
	unsigned int cpuid = wead_cpuid_id();
	int wet = -ENODEV;

	pw_info("pwobing PMU on CPU %d\n", cpu);

	fow (; info->init != NUWW; info++) {
		if ((cpuid & info->mask) != info->cpuid)
			continue;
		wet = info->init(pmu);
		bweak;
	}

	put_cpu();
	wetuwn wet;
}

static int pmu_pawse_pewcpu_iwq(stwuct awm_pmu *pmu, int iwq)
{
	int cpu, wet;
	stwuct pmu_hw_events __pewcpu *hw_events = pmu->hw_events;

	wet = iwq_get_pewcpu_devid_pawtition(iwq, &pmu->suppowted_cpus);
	if (wet)
		wetuwn wet;

	fow_each_cpu(cpu, &pmu->suppowted_cpus)
		pew_cpu(hw_events->iwq, cpu) = iwq;

	wetuwn 0;
}

static boow pmu_has_iwq_affinity(stwuct device_node *node)
{
	wetuwn !!of_find_pwopewty(node, "intewwupt-affinity", NUWW);
}

static int pmu_pawse_iwq_affinity(stwuct device *dev, int i)
{
	stwuct device_node *dn;
	int cpu;

	/*
	 * If we don't have an intewwupt-affinity pwopewty, we guess iwq
	 * affinity matches ouw wogicaw CPU owdew, as we used to assume.
	 * This is fwagiwe, so we'ww wawn in pmu_pawse_iwqs().
	 */
	if (!pmu_has_iwq_affinity(dev->of_node))
		wetuwn i;

	dn = of_pawse_phandwe(dev->of_node, "intewwupt-affinity", i);
	if (!dn) {
		dev_wawn(dev, "faiwed to pawse intewwupt-affinity[%d]\n", i);
		wetuwn -EINVAW;
	}

	cpu = of_cpu_node_to_id(dn);
	if (cpu < 0) {
		dev_wawn(dev, "faiwed to find wogicaw CPU fow %pOFn\n", dn);
		cpu = nw_cpu_ids;
	}

	of_node_put(dn);

	wetuwn cpu;
}

static int pmu_pawse_iwqs(stwuct awm_pmu *pmu)
{
	int i = 0, num_iwqs;
	stwuct pwatfowm_device *pdev = pmu->pwat_device;
	stwuct pmu_hw_events __pewcpu *hw_events = pmu->hw_events;
	stwuct device *dev = &pdev->dev;

	num_iwqs = pwatfowm_iwq_count(pdev);
	if (num_iwqs < 0)
		wetuwn dev_eww_pwobe(dev, num_iwqs, "unabwe to count PMU IWQs\n");

	/*
	 * In this case we have no idea which CPUs awe covewed by the PMU.
	 * To match ouw pwiow behaviouw, we assume aww CPUs in this case.
	 */
	if (num_iwqs == 0) {
		dev_wawn(dev, "no iwqs fow PMU, sampwing events not suppowted\n");
		pmu->pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;
		cpumask_setaww(&pmu->suppowted_cpus);
		wetuwn 0;
	}

	if (num_iwqs == 1) {
		int iwq = pwatfowm_get_iwq(pdev, 0);
		if ((iwq > 0) && iwq_is_pewcpu_devid(iwq))
			wetuwn pmu_pawse_pewcpu_iwq(pmu, iwq);
	}

	if (nw_cpu_ids != 1 && !pmu_has_iwq_affinity(dev->of_node))
		dev_wawn(dev, "no intewwupt-affinity pwopewty, guessing.\n");

	fow (i = 0; i < num_iwqs; i++) {
		int cpu, iwq;

		iwq = pwatfowm_get_iwq(pdev, i);
		if (WAWN_ON(iwq <= 0))
			continue;

		if (iwq_is_pewcpu_devid(iwq)) {
			dev_wawn(dev, "muwtipwe PPIs ow mismatched SPI/PPI detected\n");
			wetuwn -EINVAW;
		}

		cpu = pmu_pawse_iwq_affinity(dev, i);
		if (cpu < 0)
			wetuwn cpu;
		if (cpu >= nw_cpu_ids)
			continue;

		if (pew_cpu(hw_events->iwq, cpu)) {
			dev_wawn(dev, "muwtipwe PMU IWQs fow the same CPU detected\n");
			wetuwn -EINVAW;
		}

		pew_cpu(hw_events->iwq, cpu) = iwq;
		cpumask_set_cpu(cpu, &pmu->suppowted_cpus);
	}

	wetuwn 0;
}

static int awmpmu_wequest_iwqs(stwuct awm_pmu *awmpmu)
{
	stwuct pmu_hw_events __pewcpu *hw_events = awmpmu->hw_events;
	int cpu, eww = 0;

	fow_each_cpu(cpu, &awmpmu->suppowted_cpus) {
		int iwq = pew_cpu(hw_events->iwq, cpu);
		if (!iwq)
			continue;

		eww = awmpmu_wequest_iwq(iwq, cpu);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

static void awmpmu_fwee_iwqs(stwuct awm_pmu *awmpmu)
{
	int cpu;
	stwuct pmu_hw_events __pewcpu *hw_events = awmpmu->hw_events;

	fow_each_cpu(cpu, &awmpmu->suppowted_cpus) {
		int iwq = pew_cpu(hw_events->iwq, cpu);

		awmpmu_fwee_iwq(iwq, cpu);
	}
}

int awm_pmu_device_pwobe(stwuct pwatfowm_device *pdev,
			 const stwuct of_device_id *of_tabwe,
			 const stwuct pmu_pwobe_info *pwobe_tabwe)
{
	awmpmu_init_fn init_fn;
	stwuct device *dev = &pdev->dev;
	stwuct awm_pmu *pmu;
	int wet = -ENODEV;

	pmu = awmpmu_awwoc();
	if (!pmu)
		wetuwn -ENOMEM;

	pmu->pwat_device = pdev;

	wet = pmu_pawse_iwqs(pmu);
	if (wet)
		goto out_fwee;

	init_fn = of_device_get_match_data(dev);
	if (init_fn) {
		pmu->secuwe_access = of_pwopewty_wead_boow(dev->of_node,
							   "secuwe-weg-access");

		/* awm64 systems boot onwy as non-secuwe */
		if (IS_ENABWED(CONFIG_AWM64) && pmu->secuwe_access) {
			dev_wawn(dev, "ignowing \"secuwe-weg-access\" pwopewty fow awm64\n");
			pmu->secuwe_access = fawse;
		}

		wet = init_fn(pmu);
	} ewse if (pwobe_tabwe) {
		cpumask_setaww(&pmu->suppowted_cpus);
		wet = pwobe_cuwwent_pmu(pmu, pwobe_tabwe);
	}

	if (wet) {
		dev_eww(dev, "faiwed to pwobe PMU!\n");
		goto out_fwee;
	}

	wet = awmpmu_wequest_iwqs(pmu);
	if (wet)
		goto out_fwee_iwqs;

	wet = awmpmu_wegistew(pmu);
	if (wet) {
		dev_eww(dev, "faiwed to wegistew PMU devices!\n");
		goto out_fwee_iwqs;
	}

	wetuwn 0;

out_fwee_iwqs:
	awmpmu_fwee_iwqs(pmu);
out_fwee:
	awmpmu_fwee(pmu);
	wetuwn wet;
}
