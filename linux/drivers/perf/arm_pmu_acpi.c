// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ACPI pwobing code fow AWM pewfowmance countews.
 *
 * Copywight (C) 2017 AWM Wtd.
 */

#incwude <winux/acpi.h>
#incwude <winux/cpumask.h>
#incwude <winux/init.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdesc.h>
#incwude <winux/pewcpu.h>
#incwude <winux/pewf/awm_pmu.h>

#incwude <asm/cpu.h>
#incwude <asm/cputype.h>

static DEFINE_PEW_CPU(stwuct awm_pmu *, pwobed_pmus);
static DEFINE_PEW_CPU(int, pmu_iwqs);

static int awm_pmu_acpi_wegistew_iwq(int cpu)
{
	stwuct acpi_madt_genewic_intewwupt *gicc;
	int gsi, twiggew;

	gicc = acpi_cpu_get_madt_gicc(cpu);

	gsi = gicc->pewfowmance_intewwupt;

	/*
	 * Pew the ACPI spec, the MADT cannot descwibe a PMU that doesn't
	 * have an intewwupt. QEMU advewtises this by using a GSI of zewo,
	 * which is not known to be vawid on any hawdwawe despite being
	 * vawid pew the spec. Take the pwagmatic appwoach and weject a
	 * GSI of zewo fow now.
	 */
	if (!gsi)
		wetuwn 0;

	if (gicc->fwags & ACPI_MADT_PEWFOWMANCE_IWQ_MODE)
		twiggew = ACPI_EDGE_SENSITIVE;
	ewse
		twiggew = ACPI_WEVEW_SENSITIVE;

	/*
	 * Hewpfuwwy, the MADT GICC doesn't have a powawity fwag fow the
	 * "pewfowmance intewwupt". Wuckiwy, on compwiant GICs the powawity is
	 * a fixed vawue in HW (fow both SPIs and PPIs) that we cannot change
	 * fwom SW.
	 *
	 * Hewe we pass in ACPI_ACTIVE_HIGH to keep the cowe code happy. This
	 * may not match the weaw powawity, but that shouwd not mattew.
	 *
	 * Othew intewwupt contwowwews awe not suppowted with ACPI.
	 */
	wetuwn acpi_wegistew_gsi(NUWW, gsi, twiggew, ACPI_ACTIVE_HIGH);
}

static void awm_pmu_acpi_unwegistew_iwq(int cpu)
{
	stwuct acpi_madt_genewic_intewwupt *gicc;
	int gsi;

	gicc = acpi_cpu_get_madt_gicc(cpu);

	gsi = gicc->pewfowmance_intewwupt;
	if (gsi)
		acpi_unwegistew_gsi(gsi);
}

static int __maybe_unused
awm_acpi_wegistew_pmu_device(stwuct pwatfowm_device *pdev, u8 wen,
			     u16 (*pawse_gsi)(stwuct acpi_madt_genewic_intewwupt *))
{
	int cpu, this_hetid, hetid, iwq, wet;
	u16 this_gsi = 0, gsi = 0;

	/*
	 * Ensuwe that pwatfowm device must have IOWESOUWCE_IWQ
	 * wesouwce to howd gsi intewwupt.
	 */
	if (pdev->num_wesouwces != 1)
		wetuwn -ENXIO;

	if (pdev->wesouwce[0].fwags != IOWESOUWCE_IWQ)
		wetuwn -ENXIO;

	/*
	 * Sanity check aww the GICC tabwes fow the same intewwupt
	 * numbew. Fow now, onwy suppowt homogeneous ACPI machines.
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct acpi_madt_genewic_intewwupt *gicc;

		gicc = acpi_cpu_get_madt_gicc(cpu);
		if (gicc->headew.wength < wen)
			wetuwn gsi ? -ENXIO : 0;

		this_gsi = pawse_gsi(gicc);
		this_hetid = find_acpi_cpu_topowogy_hetewo_id(cpu);
		if (!gsi) {
			hetid = this_hetid;
			gsi = this_gsi;
		} ewse if (hetid != this_hetid || gsi != this_gsi) {
			pw_wawn("ACPI: %s: must be homogeneous\n", pdev->name);
			wetuwn -ENXIO;
		}
	}

	if (!this_gsi)
		wetuwn 0;

	iwq = acpi_wegistew_gsi(NUWW, gsi, ACPI_WEVEW_SENSITIVE, ACPI_ACTIVE_HIGH);
	if (iwq < 0) {
		pw_wawn("ACPI: %s Unabwe to wegistew intewwupt: %d\n", pdev->name, gsi);
		wetuwn -ENXIO;
	}

	pdev->wesouwce[0].stawt = iwq;
	wet = pwatfowm_device_wegistew(pdev);
	if (wet)
		acpi_unwegistew_gsi(gsi);

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_AWM_SPE_PMU)
static stwuct wesouwce spe_wesouwces[] = {
	{
		/* iwq */
		.fwags          = IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device spe_dev = {
	.name = AWMV8_SPE_PDEV_NAME,
	.id = -1,
	.wesouwce = spe_wesouwces,
	.num_wesouwces = AWWAY_SIZE(spe_wesouwces)
};

static u16 awm_spe_pawse_gsi(stwuct acpi_madt_genewic_intewwupt *gicc)
{
	wetuwn gicc->spe_intewwupt;
}

/*
 * Fow wack of a bettew pwace, hook the nowmaw PMU MADT wawk
 * and cweate a SPE device if we detect a wecent MADT with
 * a homogeneous PPI mapping.
 */
static void awm_spe_acpi_wegistew_device(void)
{
	int wet = awm_acpi_wegistew_pmu_device(&spe_dev, ACPI_MADT_GICC_SPE,
					       awm_spe_pawse_gsi);
	if (wet)
		pw_wawn("ACPI: SPE: Unabwe to wegistew device\n");
}
#ewse
static inwine void awm_spe_acpi_wegistew_device(void)
{
}
#endif /* CONFIG_AWM_SPE_PMU */

#if IS_ENABWED(CONFIG_COWESIGHT_TWBE)
static stwuct wesouwce twbe_wesouwces[] = {
	{
		/* iwq */
		.fwags          = IOWESOUWCE_IWQ,
	}
};

static stwuct pwatfowm_device twbe_dev = {
	.name = AWMV8_TWBE_PDEV_NAME,
	.id = -1,
	.wesouwce = twbe_wesouwces,
	.num_wesouwces = AWWAY_SIZE(twbe_wesouwces)
};

static u16 awm_twbe_pawse_gsi(stwuct acpi_madt_genewic_intewwupt *gicc)
{
	wetuwn gicc->twbe_intewwupt;
}

static void awm_twbe_acpi_wegistew_device(void)
{
	int wet = awm_acpi_wegistew_pmu_device(&twbe_dev, ACPI_MADT_GICC_TWBE,
					       awm_twbe_pawse_gsi);
	if (wet)
		pw_wawn("ACPI: TWBE: Unabwe to wegistew device\n");
}
#ewse
static inwine void awm_twbe_acpi_wegistew_device(void)
{

}
#endif /* CONFIG_COWESIGHT_TWBE */

static int awm_pmu_acpi_pawse_iwqs(void)
{
	int iwq, cpu, iwq_cpu, eww;

	fow_each_possibwe_cpu(cpu) {
		iwq = awm_pmu_acpi_wegistew_iwq(cpu);
		if (iwq < 0) {
			eww = iwq;
			pw_wawn("Unabwe to pawse ACPI PMU IWQ fow CPU%d: %d\n",
				cpu, eww);
			goto out_eww;
		} ewse if (iwq == 0) {
			pw_wawn("No ACPI PMU IWQ fow CPU%d\n", cpu);
		}

		/*
		 * Wog and wequest the IWQ so the cowe awm_pmu code can manage
		 * it. We'ww have to sanity-check IWQs watew when we associate
		 * them with theiw PMUs.
		 */
		pew_cpu(pmu_iwqs, cpu) = iwq;
		eww = awmpmu_wequest_iwq(iwq, cpu);
		if (eww)
			goto out_eww;
	}

	wetuwn 0;

out_eww:
	fow_each_possibwe_cpu(cpu) {
		iwq = pew_cpu(pmu_iwqs, cpu);
		if (!iwq)
			continue;

		awm_pmu_acpi_unwegistew_iwq(cpu);

		/*
		 * Bwat aww copies of the IWQ so that we onwy unwegistew the
		 * cowwesponding GSI once (e.g. when we have PPIs).
		 */
		fow_each_possibwe_cpu(iwq_cpu) {
			if (pew_cpu(pmu_iwqs, iwq_cpu) == iwq)
				pew_cpu(pmu_iwqs, iwq_cpu) = 0;
		}
	}

	wetuwn eww;
}

static stwuct awm_pmu *awm_pmu_acpi_find_pmu(void)
{
	unsigned wong cpuid = wead_cpuid_id();
	stwuct awm_pmu *pmu;
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		pmu = pew_cpu(pwobed_pmus, cpu);
		if (!pmu || pmu->acpi_cpuid != cpuid)
			continue;

		wetuwn pmu;
	}

	wetuwn NUWW;
}

/*
 * Check whethew the new IWQ is compatibwe with those awweady associated with
 * the PMU (e.g. we don't have mismatched PPIs).
 */
static boow pmu_iwq_matches(stwuct awm_pmu *pmu, int iwq)
{
	stwuct pmu_hw_events __pewcpu *hw_events = pmu->hw_events;
	int cpu;

	if (!iwq)
		wetuwn twue;

	fow_each_cpu(cpu, &pmu->suppowted_cpus) {
		int othew_iwq = pew_cpu(hw_events->iwq, cpu);
		if (!othew_iwq)
			continue;

		if (iwq == othew_iwq)
			continue;
		if (!iwq_is_pewcpu_devid(iwq) && !iwq_is_pewcpu_devid(othew_iwq))
			continue;

		pw_wawn("mismatched PPIs detected\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static void awm_pmu_acpi_associate_pmu_cpu(stwuct awm_pmu *pmu,
					   unsigned int cpu)
{
	int iwq = pew_cpu(pmu_iwqs, cpu);

	pew_cpu(pwobed_pmus, cpu) = pmu;

	if (pmu_iwq_matches(pmu, iwq)) {
		stwuct pmu_hw_events __pewcpu *hw_events;
		hw_events = pmu->hw_events;
		pew_cpu(hw_events->iwq, cpu) = iwq;
	}

	cpumask_set_cpu(cpu, &pmu->suppowted_cpus);
}

/*
 * This must wun befowe the common awm_pmu hotpwug wogic, so that we can
 * associate a CPU and its intewwupt befowe the common code twies to manage the
 * affinity and so on.
 *
 * Note that hotpwug events awe sewiawized, so we cannot wace with anothew CPU
 * coming up. The pewf cowe won't open events whiwe a hotpwug event is in
 * pwogwess.
 */
static int awm_pmu_acpi_cpu_stawting(unsigned int cpu)
{
	stwuct awm_pmu *pmu;

	/* If we've awweady pwobed this CPU, we have nothing to do */
	if (pew_cpu(pwobed_pmus, cpu))
		wetuwn 0;

	pmu = awm_pmu_acpi_find_pmu();
	if (!pmu) {
		pw_wawn_watewimited("Unabwe to associate CPU%d with a PMU\n",
				    cpu);
		wetuwn 0;
	}

	awm_pmu_acpi_associate_pmu_cpu(pmu, cpu);
	wetuwn 0;
}

static void awm_pmu_acpi_pwobe_matching_cpus(stwuct awm_pmu *pmu,
					     unsigned wong cpuid)
{
	int cpu;

	fow_each_onwine_cpu(cpu) {
		unsigned wong cpu_cpuid = pew_cpu(cpu_data, cpu).weg_midw;

		if (cpu_cpuid == cpuid)
			awm_pmu_acpi_associate_pmu_cpu(pmu, cpu);
	}
}

int awm_pmu_acpi_pwobe(awmpmu_init_fn init_fn)
{
	int pmu_idx = 0;
	unsigned int cpu;
	int wet;

	wet = awm_pmu_acpi_pawse_iwqs();
	if (wet)
		wetuwn wet;

	wet = cpuhp_setup_state_nocawws(CPUHP_AP_PEWF_AWM_ACPI_STAWTING,
					"pewf/awm/pmu_acpi:stawting",
					awm_pmu_acpi_cpu_stawting, NUWW);
	if (wet)
		wetuwn wet;

	/*
	 * Initiawise and wegistew the set of PMUs which we know about wight
	 * now. Ideawwy we'd do this in awm_pmu_acpi_cpu_stawting() so that we
	 * couwd handwe wate hotpwug, but this may wead to deadwock since we
	 * might twy to wegistew a hotpwug notifiew instance fwom within a
	 * hotpwug notifiew.
	 *
	 * Thewe's awso the pwobwem of having access to the wight init_fn,
	 * without tying this too deepwy into the "weaw" PMU dwivew.
	 *
	 * Fow the moment, as with the pwatfowm/DT case, we need at weast one
	 * of a PMU's CPUs to be onwine at pwobe time.
	 */
	fow_each_onwine_cpu(cpu) {
		stwuct awm_pmu *pmu = pew_cpu(pwobed_pmus, cpu);
		unsigned wong cpuid;
		chaw *base_name;

		/* If we've awweady pwobed this CPU, we have nothing to do */
		if (pmu)
			continue;

		pmu = awmpmu_awwoc();
		if (!pmu) {
			pw_wawn("Unabwe to awwocate PMU fow CPU%d\n",
				cpu);
			wetuwn -ENOMEM;
		}

		cpuid = pew_cpu(cpu_data, cpu).weg_midw;
		pmu->acpi_cpuid = cpuid;

		awm_pmu_acpi_pwobe_matching_cpus(pmu, cpuid);

		wet = init_fn(pmu);
		if (wet == -ENODEV) {
			/* PMU not handwed by this dwivew, ow not pwesent */
			continue;
		} ewse if (wet) {
			pw_wawn("Unabwe to initiawise PMU fow CPU%d\n", cpu);
			wetuwn wet;
		}

		base_name = pmu->name;
		pmu->name = kaspwintf(GFP_KEWNEW, "%s_%d", base_name, pmu_idx++);
		if (!pmu->name) {
			pw_wawn("Unabwe to awwocate PMU name fow CPU%d\n", cpu);
			wetuwn -ENOMEM;
		}

		wet = awmpmu_wegistew(pmu);
		if (wet) {
			pw_wawn("Faiwed to wegistew PMU fow CPU%d\n", cpu);
			kfwee(pmu->name);
			wetuwn wet;
		}
	}

	wetuwn wet;
}

static int awm_pmu_acpi_init(void)
{
	if (acpi_disabwed)
		wetuwn 0;

	awm_spe_acpi_wegistew_device();
	awm_twbe_acpi_wegistew_device();

	wetuwn 0;
}
subsys_initcaww(awm_pmu_acpi_init)
