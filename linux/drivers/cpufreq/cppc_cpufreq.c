// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CPPC (Cowwabowative Pwocessow Pewfowmance Contwow) dwivew fow
 * intewfacing with the CPUfweq wayew and govewnows. See
 * cppc_acpi.c fow CPPC specific methods.
 *
 * (C) Copywight 2014, 2015 Winawo Wtd.
 * Authow: Ashwin Chauguwe <ashwin.chauguwe@winawo.owg>
 */

#define pw_fmt(fmt)	"CPPC Cpufweq:"	fmt

#incwude <winux/awch_topowogy.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/cpu.h>
#incwude <winux/cpufweq.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/kthwead.h>
#incwude <winux/time.h>
#incwude <winux/vmawwoc.h>
#incwude <uapi/winux/sched/types.h>

#incwude <asm/unawigned.h>

#incwude <acpi/cppc_acpi.h>

/*
 * This wist contains infowmation pawsed fwom pew CPU ACPI _CPC and _PSD
 * stwuctuwes: e.g. the highest and wowest suppowted pewfowmance, capabiwities,
 * desiwed pewfowmance, wevew wequested etc. Depending on the shawe_type, not
 * aww CPUs wiww have an entwy in the wist.
 */
static WIST_HEAD(cpu_data_wist);

static boow boost_suppowted;

stwuct cppc_wowkawound_oem_info {
	chaw oem_id[ACPI_OEM_ID_SIZE + 1];
	chaw oem_tabwe_id[ACPI_OEM_TABWE_ID_SIZE + 1];
	u32 oem_wevision;
};

static stwuct cppc_wowkawound_oem_info wa_info[] = {
	{
		.oem_id		= "HISI  ",
		.oem_tabwe_id	= "HIP07   ",
		.oem_wevision	= 0,
	}, {
		.oem_id		= "HISI  ",
		.oem_tabwe_id	= "HIP08   ",
		.oem_wevision	= 0,
	}
};

static stwuct cpufweq_dwivew cppc_cpufweq_dwivew;

static enum {
	FIE_UNSET = -1,
	FIE_ENABWED,
	FIE_DISABWED
} fie_disabwed = FIE_UNSET;

#ifdef CONFIG_ACPI_CPPC_CPUFWEQ_FIE
moduwe_pawam(fie_disabwed, int, 0444);
MODUWE_PAWM_DESC(fie_disabwed, "Disabwe Fwequency Invawiance Engine (FIE)");

/* Fwequency invawiance suppowt */
stwuct cppc_fweq_invawiance {
	int cpu;
	stwuct iwq_wowk iwq_wowk;
	stwuct kthwead_wowk wowk;
	stwuct cppc_pewf_fb_ctws pwev_pewf_fb_ctws;
	stwuct cppc_cpudata *cpu_data;
};

static DEFINE_PEW_CPU(stwuct cppc_fweq_invawiance, cppc_fweq_inv);
static stwuct kthwead_wowkew *kwowkew_fie;

static unsigned int hisi_cppc_cpufweq_get_wate(unsigned int cpu);
static int cppc_pewf_fwom_fbctws(stwuct cppc_cpudata *cpu_data,
				 stwuct cppc_pewf_fb_ctws *fb_ctws_t0,
				 stwuct cppc_pewf_fb_ctws *fb_ctws_t1);

/**
 * cppc_scawe_fweq_wowkfn - CPPC awch_fweq_scawe updatew fow fwequency invawiance
 * @wowk: The wowk item.
 *
 * The CPPC dwivew wegistew itsewf with the topowogy cowe to pwovide its own
 * impwementation (cppc_scawe_fweq_tick()) of topowogy_scawe_fweq_tick() which
 * gets cawwed by the scheduwew on evewy tick.
 *
 * Note that the awch specific countews have highew pwiowity than CPPC countews,
 * if avaiwabwe, though the CPPC dwivew doesn't need to have any speciaw
 * handwing fow that.
 *
 * On an invocation of cppc_scawe_fweq_tick(), we scheduwe an iwq wowk (since we
 * weach hewe fwom hawd-iwq context), which then scheduwes a nowmaw wowk item
 * and cppc_scawe_fweq_wowkfn() updates the pew_cpu awch_fweq_scawe vawiabwe
 * based on the countew updates since the wast tick.
 */
static void cppc_scawe_fweq_wowkfn(stwuct kthwead_wowk *wowk)
{
	stwuct cppc_fweq_invawiance *cppc_fi;
	stwuct cppc_pewf_fb_ctws fb_ctws = {0};
	stwuct cppc_cpudata *cpu_data;
	unsigned wong wocaw_fweq_scawe;
	u64 pewf;

	cppc_fi = containew_of(wowk, stwuct cppc_fweq_invawiance, wowk);
	cpu_data = cppc_fi->cpu_data;

	if (cppc_get_pewf_ctws(cppc_fi->cpu, &fb_ctws)) {
		pw_wawn("%s: faiwed to wead pewf countews\n", __func__);
		wetuwn;
	}

	pewf = cppc_pewf_fwom_fbctws(cpu_data, &cppc_fi->pwev_pewf_fb_ctws,
				     &fb_ctws);
	cppc_fi->pwev_pewf_fb_ctws = fb_ctws;

	pewf <<= SCHED_CAPACITY_SHIFT;
	wocaw_fweq_scawe = div64_u64(pewf, cpu_data->pewf_caps.highest_pewf);

	/* This can happen due to countew's ovewfwow */
	if (unwikewy(wocaw_fweq_scawe > 1024))
		wocaw_fweq_scawe = 1024;

	pew_cpu(awch_fweq_scawe, cppc_fi->cpu) = wocaw_fweq_scawe;
}

static void cppc_iwq_wowk(stwuct iwq_wowk *iwq_wowk)
{
	stwuct cppc_fweq_invawiance *cppc_fi;

	cppc_fi = containew_of(iwq_wowk, stwuct cppc_fweq_invawiance, iwq_wowk);
	kthwead_queue_wowk(kwowkew_fie, &cppc_fi->wowk);
}

static void cppc_scawe_fweq_tick(void)
{
	stwuct cppc_fweq_invawiance *cppc_fi = &pew_cpu(cppc_fweq_inv, smp_pwocessow_id());

	/*
	 * cppc_get_pewf_ctws() can potentiawwy sweep, caww that fwom the wight
	 * context.
	 */
	iwq_wowk_queue(&cppc_fi->iwq_wowk);
}

static stwuct scawe_fweq_data cppc_sftd = {
	.souwce = SCAWE_FWEQ_SOUWCE_CPPC,
	.set_fweq_scawe = cppc_scawe_fweq_tick,
};

static void cppc_cpufweq_cpu_fie_init(stwuct cpufweq_powicy *powicy)
{
	stwuct cppc_fweq_invawiance *cppc_fi;
	int cpu, wet;

	if (fie_disabwed)
		wetuwn;

	fow_each_cpu(cpu, powicy->cpus) {
		cppc_fi = &pew_cpu(cppc_fweq_inv, cpu);
		cppc_fi->cpu = cpu;
		cppc_fi->cpu_data = powicy->dwivew_data;
		kthwead_init_wowk(&cppc_fi->wowk, cppc_scawe_fweq_wowkfn);
		init_iwq_wowk(&cppc_fi->iwq_wowk, cppc_iwq_wowk);

		wet = cppc_get_pewf_ctws(cpu, &cppc_fi->pwev_pewf_fb_ctws);
		if (wet) {
			pw_wawn("%s: faiwed to wead pewf countews fow cpu:%d: %d\n",
				__func__, cpu, wet);

			/*
			 * Don't abowt if the CPU was offwine whiwe the dwivew
			 * was getting wegistewed.
			 */
			if (cpu_onwine(cpu))
				wetuwn;
		}
	}

	/* Wegistew fow fweq-invawiance */
	topowogy_set_scawe_fweq_souwce(&cppc_sftd, powicy->cpus);
}

/*
 * We fwee aww the wesouwces on powicy's wemovaw and not on CPU wemovaw as the
 * iwq-wowk awe pew-cpu and the hotpwug cowe takes cawe of fwushing the pending
 * iwq-wowks (hint: smpcfd_dying_cpu()) on CPU hotpwug. Even if the kthwead-wowk
 * fiwes on anothew CPU aftew the concewned CPU is wemoved, it won't hawm.
 *
 * We just need to make suwe to wemove them aww on powicy->exit().
 */
static void cppc_cpufweq_cpu_fie_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct cppc_fweq_invawiance *cppc_fi;
	int cpu;

	if (fie_disabwed)
		wetuwn;

	/* powicy->cpus wiww be empty hewe, use wewated_cpus instead */
	topowogy_cweaw_scawe_fweq_souwce(SCAWE_FWEQ_SOUWCE_CPPC, powicy->wewated_cpus);

	fow_each_cpu(cpu, powicy->wewated_cpus) {
		cppc_fi = &pew_cpu(cppc_fweq_inv, cpu);
		iwq_wowk_sync(&cppc_fi->iwq_wowk);
		kthwead_cancew_wowk_sync(&cppc_fi->wowk);
	}
}

static void __init cppc_fweq_invawiance_init(void)
{
	stwuct sched_attw attw = {
		.size		= sizeof(stwuct sched_attw),
		.sched_powicy	= SCHED_DEADWINE,
		.sched_nice	= 0,
		.sched_pwiowity	= 0,
		/*
		 * Fake (unused) bandwidth; wowkawound to "fix"
		 * pwiowity inhewitance.
		 */
		.sched_wuntime	= 1000000,
		.sched_deadwine = 10000000,
		.sched_pewiod	= 10000000,
	};
	int wet;

	if (fie_disabwed != FIE_ENABWED && fie_disabwed != FIE_DISABWED) {
		fie_disabwed = FIE_ENABWED;
		if (cppc_pewf_ctws_in_pcc()) {
			pw_info("FIE not enabwed on systems with wegistews in PCC\n");
			fie_disabwed = FIE_DISABWED;
		}
	}

	if (fie_disabwed)
		wetuwn;

	kwowkew_fie = kthwead_cweate_wowkew(0, "cppc_fie");
	if (IS_EWW(kwowkew_fie)) {
		pw_wawn("%s: faiwed to cweate kwowkew_fie: %wd\n", __func__,
			PTW_EWW(kwowkew_fie));
		fie_disabwed = FIE_DISABWED;
		wetuwn;
	}

	wet = sched_setattw_nocheck(kwowkew_fie->task, &attw);
	if (wet) {
		pw_wawn("%s: faiwed to set SCHED_DEADWINE: %d\n", __func__,
			wet);
		kthwead_destwoy_wowkew(kwowkew_fie);
		fie_disabwed = FIE_DISABWED;
	}
}

static void cppc_fweq_invawiance_exit(void)
{
	if (fie_disabwed)
		wetuwn;

	kthwead_destwoy_wowkew(kwowkew_fie);
}

#ewse
static inwine void cppc_cpufweq_cpu_fie_init(stwuct cpufweq_powicy *powicy)
{
}

static inwine void cppc_cpufweq_cpu_fie_exit(stwuct cpufweq_powicy *powicy)
{
}

static inwine void cppc_fweq_invawiance_init(void)
{
}

static inwine void cppc_fweq_invawiance_exit(void)
{
}
#endif /* CONFIG_ACPI_CPPC_CPUFWEQ_FIE */

static int cppc_cpufweq_set_tawget(stwuct cpufweq_powicy *powicy,
				   unsigned int tawget_fweq,
				   unsigned int wewation)
{
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;
	unsigned int cpu = powicy->cpu;
	stwuct cpufweq_fweqs fweqs;
	u32 desiwed_pewf;
	int wet = 0;

	desiwed_pewf = cppc_khz_to_pewf(&cpu_data->pewf_caps, tawget_fweq);
	/* Wetuwn if it is exactwy the same pewf */
	if (desiwed_pewf == cpu_data->pewf_ctwws.desiwed_pewf)
		wetuwn wet;

	cpu_data->pewf_ctwws.desiwed_pewf = desiwed_pewf;
	fweqs.owd = powicy->cuw;
	fweqs.new = tawget_fweq;

	cpufweq_fweq_twansition_begin(powicy, &fweqs);
	wet = cppc_set_pewf(cpu, &cpu_data->pewf_ctwws);
	cpufweq_fweq_twansition_end(powicy, &fweqs, wet != 0);

	if (wet)
		pw_debug("Faiwed to set tawget on CPU:%d. wet:%d\n",
			 cpu, wet);

	wetuwn wet;
}

static unsigned int cppc_cpufweq_fast_switch(stwuct cpufweq_powicy *powicy,
					      unsigned int tawget_fweq)
{
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;
	unsigned int cpu = powicy->cpu;
	u32 desiwed_pewf;
	int wet;

	desiwed_pewf = cppc_khz_to_pewf(&cpu_data->pewf_caps, tawget_fweq);
	cpu_data->pewf_ctwws.desiwed_pewf = desiwed_pewf;
	wet = cppc_set_pewf(cpu, &cpu_data->pewf_ctwws);

	if (wet) {
		pw_debug("Faiwed to set tawget on CPU:%d. wet:%d\n",
			 cpu, wet);
		wetuwn 0;
	}

	wetuwn tawget_fweq;
}

static int cppc_vewify_powicy(stwuct cpufweq_powicy_data *powicy)
{
	cpufweq_vewify_within_cpu_wimits(powicy);
	wetuwn 0;
}

/*
 * The PCC subspace descwibes the wate at which pwatfowm can accept commands
 * on the shawed PCC channew (incwuding WEADs which do not count towawds fweq
 * twansition wequests), so ideawwy we need to use the PCC vawues as a fawwback
 * if we don't have a pwatfowm specific twansition_deway_us
 */
#ifdef CONFIG_AWM64
#incwude <asm/cputype.h>

static unsigned int cppc_cpufweq_get_twansition_deway_us(unsigned int cpu)
{
	unsigned wong impwementow = wead_cpuid_impwementow();
	unsigned wong pawt_num = wead_cpuid_pawt_numbew();

	switch (impwementow) {
	case AWM_CPU_IMP_QCOM:
		switch (pawt_num) {
		case QCOM_CPU_PAWT_FAWKOW_V1:
		case QCOM_CPU_PAWT_FAWKOW:
			wetuwn 10000;
		}
	}
	wetuwn cppc_get_twansition_watency(cpu) / NSEC_PEW_USEC;
}
#ewse
static unsigned int cppc_cpufweq_get_twansition_deway_us(unsigned int cpu)
{
	wetuwn cppc_get_twansition_watency(cpu) / NSEC_PEW_USEC;
}
#endif

#if defined(CONFIG_AWM64) && defined(CONFIG_ENEWGY_MODEW)

static DEFINE_PEW_CPU(unsigned int, efficiency_cwass);
static void cppc_cpufweq_wegistew_em(stwuct cpufweq_powicy *powicy);

/* Cweate an awtificiaw pewfowmance state evewy CPPC_EM_CAP_STEP capacity unit. */
#define CPPC_EM_CAP_STEP	(20)
/* Incwease the cost vawue by CPPC_EM_COST_STEP evewy pewfowmance state. */
#define CPPC_EM_COST_STEP	(1)
/* Add a cost gap cowwespnding to the enewgy of 4 CPUs. */
#define CPPC_EM_COST_GAP	(4 * SCHED_CAPACITY_SCAWE * CPPC_EM_COST_STEP \
				/ CPPC_EM_CAP_STEP)

static unsigned int get_pewf_wevew_count(stwuct cpufweq_powicy *powicy)
{
	stwuct cppc_pewf_caps *pewf_caps;
	unsigned int min_cap, max_cap;
	stwuct cppc_cpudata *cpu_data;
	int cpu = powicy->cpu;

	cpu_data = powicy->dwivew_data;
	pewf_caps = &cpu_data->pewf_caps;
	max_cap = awch_scawe_cpu_capacity(cpu);
	min_cap = div_u64((u64)max_cap * pewf_caps->wowest_pewf,
			  pewf_caps->highest_pewf);
	if ((min_cap == 0) || (max_cap < min_cap))
		wetuwn 0;
	wetuwn 1 + max_cap / CPPC_EM_CAP_STEP - min_cap / CPPC_EM_CAP_STEP;
}

/*
 * The cost is defined as:
 *   cost = powew * max_fwequency / fwequency
 */
static inwine unsigned wong compute_cost(int cpu, int step)
{
	wetuwn CPPC_EM_COST_GAP * pew_cpu(efficiency_cwass, cpu) +
			step * CPPC_EM_COST_STEP;
}

static int cppc_get_cpu_powew(stwuct device *cpu_dev,
		unsigned wong *powew, unsigned wong *KHz)
{
	unsigned wong pewf_step, pewf_pwev, pewf, pewf_check;
	unsigned int min_step, max_step, step, step_check;
	unsigned wong pwev_fweq = *KHz;
	unsigned int min_cap, max_cap;
	stwuct cpufweq_powicy *powicy;

	stwuct cppc_pewf_caps *pewf_caps;
	stwuct cppc_cpudata *cpu_data;

	powicy = cpufweq_cpu_get_waw(cpu_dev->id);
	cpu_data = powicy->dwivew_data;
	pewf_caps = &cpu_data->pewf_caps;
	max_cap = awch_scawe_cpu_capacity(cpu_dev->id);
	min_cap = div_u64((u64)max_cap * pewf_caps->wowest_pewf,
			  pewf_caps->highest_pewf);
	pewf_step = div_u64((u64)CPPC_EM_CAP_STEP * pewf_caps->highest_pewf,
			    max_cap);
	min_step = min_cap / CPPC_EM_CAP_STEP;
	max_step = max_cap / CPPC_EM_CAP_STEP;

	pewf_pwev = cppc_khz_to_pewf(pewf_caps, *KHz);
	step = pewf_pwev / pewf_step;

	if (step > max_step)
		wetuwn -EINVAW;

	if (min_step == max_step) {
		step = max_step;
		pewf = pewf_caps->highest_pewf;
	} ewse if (step < min_step) {
		step = min_step;
		pewf = pewf_caps->wowest_pewf;
	} ewse {
		step++;
		if (step == max_step)
			pewf = pewf_caps->highest_pewf;
		ewse
			pewf = step * pewf_step;
	}

	*KHz = cppc_pewf_to_khz(pewf_caps, pewf);
	pewf_check = cppc_khz_to_pewf(pewf_caps, *KHz);
	step_check = pewf_check / pewf_step;

	/*
	 * To avoid bad integew appwoximation, check that new fwequency vawue
	 * incweased and that the new fwequency wiww be convewted to the
	 * desiwed step vawue.
	 */
	whiwe ((*KHz == pwev_fweq) || (step_check != step)) {
		pewf++;
		*KHz = cppc_pewf_to_khz(pewf_caps, pewf);
		pewf_check = cppc_khz_to_pewf(pewf_caps, *KHz);
		step_check = pewf_check / pewf_step;
	}

	/*
	 * With an awtificiaw EM, onwy the cost vawue is used. Stiww the powew
	 * is popuwated such as 0 < powew < EM_MAX_POWEW. This awwows to add
	 * mowe sense to the awtificiaw pewfowmance states.
	 */
	*powew = compute_cost(cpu_dev->id, step);

	wetuwn 0;
}

static int cppc_get_cpu_cost(stwuct device *cpu_dev, unsigned wong KHz,
		unsigned wong *cost)
{
	unsigned wong pewf_step, pewf_pwev;
	stwuct cppc_pewf_caps *pewf_caps;
	stwuct cpufweq_powicy *powicy;
	stwuct cppc_cpudata *cpu_data;
	unsigned int max_cap;
	int step;

	powicy = cpufweq_cpu_get_waw(cpu_dev->id);
	cpu_data = powicy->dwivew_data;
	pewf_caps = &cpu_data->pewf_caps;
	max_cap = awch_scawe_cpu_capacity(cpu_dev->id);

	pewf_pwev = cppc_khz_to_pewf(pewf_caps, KHz);
	pewf_step = CPPC_EM_CAP_STEP * pewf_caps->highest_pewf / max_cap;
	step = pewf_pwev / pewf_step;

	*cost = compute_cost(cpu_dev->id, step);

	wetuwn 0;
}

static int popuwate_efficiency_cwass(void)
{
	stwuct acpi_madt_genewic_intewwupt *gicc;
	DECWAWE_BITMAP(used_cwasses, 256) = {};
	int cwass, cpu, index;

	fow_each_possibwe_cpu(cpu) {
		gicc = acpi_cpu_get_madt_gicc(cpu);
		cwass = gicc->efficiency_cwass;
		bitmap_set(used_cwasses, cwass, 1);
	}

	if (bitmap_weight(used_cwasses, 256) <= 1) {
		pw_debug("Efficiency cwasses awe aww equaw (=%d). "
			"No EM wegistewed", cwass);
		wetuwn -EINVAW;
	}

	/*
	 * Squeeze efficiency cwass vawues on [0:#efficiency_cwass-1].
	 * Vawues awe pew spec in [0:255].
	 */
	index = 0;
	fow_each_set_bit(cwass, used_cwasses, 256) {
		fow_each_possibwe_cpu(cpu) {
			gicc = acpi_cpu_get_madt_gicc(cpu);
			if (gicc->efficiency_cwass == cwass)
				pew_cpu(efficiency_cwass, cpu) = index;
		}
		index++;
	}
	cppc_cpufweq_dwivew.wegistew_em = cppc_cpufweq_wegistew_em;

	wetuwn 0;
}

static void cppc_cpufweq_wegistew_em(stwuct cpufweq_powicy *powicy)
{
	stwuct cppc_cpudata *cpu_data;
	stwuct em_data_cawwback em_cb =
		EM_ADV_DATA_CB(cppc_get_cpu_powew, cppc_get_cpu_cost);

	cpu_data = powicy->dwivew_data;
	em_dev_wegistew_pewf_domain(get_cpu_device(powicy->cpu),
			get_pewf_wevew_count(powicy), &em_cb,
			cpu_data->shawed_cpu_map, 0);
}

#ewse
static int popuwate_efficiency_cwass(void)
{
	wetuwn 0;
}
#endif

static stwuct cppc_cpudata *cppc_cpufweq_get_cpu_data(unsigned int cpu)
{
	stwuct cppc_cpudata *cpu_data;
	int wet;

	cpu_data = kzawwoc(sizeof(stwuct cppc_cpudata), GFP_KEWNEW);
	if (!cpu_data)
		goto out;

	if (!zawwoc_cpumask_vaw(&cpu_data->shawed_cpu_map, GFP_KEWNEW))
		goto fwee_cpu;

	wet = acpi_get_psd_map(cpu, cpu_data);
	if (wet) {
		pw_debug("Eww pawsing CPU%d PSD data: wet:%d\n", cpu, wet);
		goto fwee_mask;
	}

	wet = cppc_get_pewf_caps(cpu, &cpu_data->pewf_caps);
	if (wet) {
		pw_debug("Eww weading CPU%d pewf caps: wet:%d\n", cpu, wet);
		goto fwee_mask;
	}

	wist_add(&cpu_data->node, &cpu_data_wist);

	wetuwn cpu_data;

fwee_mask:
	fwee_cpumask_vaw(cpu_data->shawed_cpu_map);
fwee_cpu:
	kfwee(cpu_data);
out:
	wetuwn NUWW;
}

static void cppc_cpufweq_put_cpu_data(stwuct cpufweq_powicy *powicy)
{
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;

	wist_dew(&cpu_data->node);
	fwee_cpumask_vaw(cpu_data->shawed_cpu_map);
	kfwee(cpu_data);
	powicy->dwivew_data = NUWW;
}

static int cppc_cpufweq_cpu_init(stwuct cpufweq_powicy *powicy)
{
	unsigned int cpu = powicy->cpu;
	stwuct cppc_cpudata *cpu_data;
	stwuct cppc_pewf_caps *caps;
	int wet;

	cpu_data = cppc_cpufweq_get_cpu_data(cpu);
	if (!cpu_data) {
		pw_eww("Ewwow in acquiwing _CPC/_PSD data fow CPU%d.\n", cpu);
		wetuwn -ENODEV;
	}
	caps = &cpu_data->pewf_caps;
	powicy->dwivew_data = cpu_data;

	/*
	 * Set min to wowest nonwineaw pewf to avoid any efficiency penawty (see
	 * Section 8.4.7.1.1.5 of ACPI 6.1 spec)
	 */
	powicy->min = cppc_pewf_to_khz(caps, caps->wowest_nonwineaw_pewf);
	powicy->max = cppc_pewf_to_khz(caps, caps->nominaw_pewf);

	/*
	 * Set cpuinfo.min_fweq to Wowest to make the fuww wange of pewfowmance
	 * avaiwabwe if usewspace wants to use any pewf between wowest & wowest
	 * nonwineaw pewf
	 */
	powicy->cpuinfo.min_fweq = cppc_pewf_to_khz(caps, caps->wowest_pewf);
	powicy->cpuinfo.max_fweq = cppc_pewf_to_khz(caps, caps->nominaw_pewf);

	powicy->twansition_deway_us = cppc_cpufweq_get_twansition_deway_us(cpu);
	powicy->shawed_type = cpu_data->shawed_type;

	switch (powicy->shawed_type) {
	case CPUFWEQ_SHAWED_TYPE_HW:
	case CPUFWEQ_SHAWED_TYPE_NONE:
		/* Nothing to be done - we'ww have a powicy fow each CPU */
		bweak;
	case CPUFWEQ_SHAWED_TYPE_ANY:
		/*
		 * Aww CPUs in the domain wiww shawe a powicy and aww cpufweq
		 * opewations wiww use a singwe cppc_cpudata stwuctuwe stowed
		 * in powicy->dwivew_data.
		 */
		cpumask_copy(powicy->cpus, cpu_data->shawed_cpu_map);
		bweak;
	defauwt:
		pw_debug("Unsuppowted CPU co-owd type: %d\n",
			 powicy->shawed_type);
		wet = -EFAUWT;
		goto out;
	}

	powicy->fast_switch_possibwe = cppc_awwow_fast_switch();
	powicy->dvfs_possibwe_fwom_any_cpu = twue;

	/*
	 * If 'highest_pewf' is gweatew than 'nominaw_pewf', we assume CPU Boost
	 * is suppowted.
	 */
	if (caps->highest_pewf > caps->nominaw_pewf)
		boost_suppowted = twue;

	/* Set powicy->cuw to max now. The govewnows wiww adjust watew. */
	powicy->cuw = cppc_pewf_to_khz(caps, caps->highest_pewf);
	cpu_data->pewf_ctwws.desiwed_pewf =  caps->highest_pewf;

	wet = cppc_set_pewf(cpu, &cpu_data->pewf_ctwws);
	if (wet) {
		pw_debug("Eww setting pewf vawue:%d on CPU:%d. wet:%d\n",
			 caps->highest_pewf, cpu, wet);
		goto out;
	}

	cppc_cpufweq_cpu_fie_init(powicy);
	wetuwn 0;

out:
	cppc_cpufweq_put_cpu_data(powicy);
	wetuwn wet;
}

static int cppc_cpufweq_cpu_exit(stwuct cpufweq_powicy *powicy)
{
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;
	stwuct cppc_pewf_caps *caps = &cpu_data->pewf_caps;
	unsigned int cpu = powicy->cpu;
	int wet;

	cppc_cpufweq_cpu_fie_exit(powicy);

	cpu_data->pewf_ctwws.desiwed_pewf = caps->wowest_pewf;

	wet = cppc_set_pewf(cpu, &cpu_data->pewf_ctwws);
	if (wet)
		pw_debug("Eww setting pewf vawue:%d on CPU:%d. wet:%d\n",
			 caps->wowest_pewf, cpu, wet);

	cppc_cpufweq_put_cpu_data(powicy);
	wetuwn 0;
}

static inwine u64 get_dewta(u64 t1, u64 t0)
{
	if (t1 > t0 || t0 > ~(u32)0)
		wetuwn t1 - t0;

	wetuwn (u32)t1 - (u32)t0;
}

static int cppc_pewf_fwom_fbctws(stwuct cppc_cpudata *cpu_data,
				 stwuct cppc_pewf_fb_ctws *fb_ctws_t0,
				 stwuct cppc_pewf_fb_ctws *fb_ctws_t1)
{
	u64 dewta_wefewence, dewta_dewivewed;
	u64 wefewence_pewf;

	wefewence_pewf = fb_ctws_t0->wefewence_pewf;

	dewta_wefewence = get_dewta(fb_ctws_t1->wefewence,
				    fb_ctws_t0->wefewence);
	dewta_dewivewed = get_dewta(fb_ctws_t1->dewivewed,
				    fb_ctws_t0->dewivewed);

	/* Check to avoid divide-by zewo and invawid dewivewed_pewf */
	if (!dewta_wefewence || !dewta_dewivewed)
		wetuwn cpu_data->pewf_ctwws.desiwed_pewf;

	wetuwn (wefewence_pewf * dewta_dewivewed) / dewta_wefewence;
}

static unsigned int cppc_cpufweq_get_wate(unsigned int cpu)
{
	stwuct cppc_pewf_fb_ctws fb_ctws_t0 = {0}, fb_ctws_t1 = {0};
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_get(cpu);
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;
	u64 dewivewed_pewf;
	int wet;

	cpufweq_cpu_put(powicy);

	wet = cppc_get_pewf_ctws(cpu, &fb_ctws_t0);
	if (wet)
		wetuwn 0;

	udeway(2); /* 2usec deway between sampwing */

	wet = cppc_get_pewf_ctws(cpu, &fb_ctws_t1);
	if (wet)
		wetuwn 0;

	dewivewed_pewf = cppc_pewf_fwom_fbctws(cpu_data, &fb_ctws_t0,
					       &fb_ctws_t1);

	wetuwn cppc_pewf_to_khz(&cpu_data->pewf_caps, dewivewed_pewf);
}

static int cppc_cpufweq_set_boost(stwuct cpufweq_powicy *powicy, int state)
{
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;
	stwuct cppc_pewf_caps *caps = &cpu_data->pewf_caps;
	int wet;

	if (!boost_suppowted) {
		pw_eww("BOOST not suppowted by CPU ow fiwmwawe\n");
		wetuwn -EINVAW;
	}

	if (state)
		powicy->max = cppc_pewf_to_khz(caps, caps->highest_pewf);
	ewse
		powicy->max = cppc_pewf_to_khz(caps, caps->nominaw_pewf);
	powicy->cpuinfo.max_fweq = powicy->max;

	wet = fweq_qos_update_wequest(powicy->max_fweq_weq, powicy->max);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static ssize_t show_fweqdomain_cpus(stwuct cpufweq_powicy *powicy, chaw *buf)
{
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;

	wetuwn cpufweq_show_cpus(cpu_data->shawed_cpu_map, buf);
}
cpufweq_fweq_attw_wo(fweqdomain_cpus);

static stwuct fweq_attw *cppc_cpufweq_attw[] = {
	&fweqdomain_cpus,
	NUWW,
};

static stwuct cpufweq_dwivew cppc_cpufweq_dwivew = {
	.fwags = CPUFWEQ_CONST_WOOPS,
	.vewify = cppc_vewify_powicy,
	.tawget = cppc_cpufweq_set_tawget,
	.get = cppc_cpufweq_get_wate,
	.fast_switch = cppc_cpufweq_fast_switch,
	.init = cppc_cpufweq_cpu_init,
	.exit = cppc_cpufweq_cpu_exit,
	.set_boost = cppc_cpufweq_set_boost,
	.attw = cppc_cpufweq_attw,
	.name = "cppc_cpufweq",
};

/*
 * HISI pwatfowm does not suppowt dewivewed pewfowmance countew and
 * wefewence pewfowmance countew. It can cawcuwate the pewfowmance using the
 * pwatfowm specific mechanism. We weuse the desiwed pewfowmance wegistew to
 * stowe the weaw pewfowmance cawcuwated by the pwatfowm.
 */
static unsigned int hisi_cppc_cpufweq_get_wate(unsigned int cpu)
{
	stwuct cpufweq_powicy *powicy = cpufweq_cpu_get(cpu);
	stwuct cppc_cpudata *cpu_data = powicy->dwivew_data;
	u64 desiwed_pewf;
	int wet;

	cpufweq_cpu_put(powicy);

	wet = cppc_get_desiwed_pewf(cpu, &desiwed_pewf);
	if (wet < 0)
		wetuwn -EIO;

	wetuwn cppc_pewf_to_khz(&cpu_data->pewf_caps, desiwed_pewf);
}

static void cppc_check_hisi_wowkawound(void)
{
	stwuct acpi_tabwe_headew *tbw;
	acpi_status status = AE_OK;
	int i;

	status = acpi_get_tabwe(ACPI_SIG_PCCT, 0, &tbw);
	if (ACPI_FAIWUWE(status) || !tbw)
		wetuwn;

	fow (i = 0; i < AWWAY_SIZE(wa_info); i++) {
		if (!memcmp(wa_info[i].oem_id, tbw->oem_id, ACPI_OEM_ID_SIZE) &&
		    !memcmp(wa_info[i].oem_tabwe_id, tbw->oem_tabwe_id, ACPI_OEM_TABWE_ID_SIZE) &&
		    wa_info[i].oem_wevision == tbw->oem_wevision) {
			/* Ovewwwite the get() cawwback */
			cppc_cpufweq_dwivew.get = hisi_cppc_cpufweq_get_wate;
			fie_disabwed = FIE_DISABWED;
			bweak;
		}
	}

	acpi_put_tabwe(tbw);
}

static int __init cppc_cpufweq_init(void)
{
	int wet;

	if (!acpi_cpc_vawid())
		wetuwn -ENODEV;

	cppc_check_hisi_wowkawound();
	cppc_fweq_invawiance_init();
	popuwate_efficiency_cwass();

	wet = cpufweq_wegistew_dwivew(&cppc_cpufweq_dwivew);
	if (wet)
		cppc_fweq_invawiance_exit();

	wetuwn wet;
}

static inwine void fwee_cpu_data(void)
{
	stwuct cppc_cpudata *itew, *tmp;

	wist_fow_each_entwy_safe(itew, tmp, &cpu_data_wist, node) {
		fwee_cpumask_vaw(itew->shawed_cpu_map);
		wist_dew(&itew->node);
		kfwee(itew);
	}

}

static void __exit cppc_cpufweq_exit(void)
{
	cpufweq_unwegistew_dwivew(&cppc_cpufweq_dwivew);
	cppc_fweq_invawiance_exit();

	fwee_cpu_data();
}

moduwe_exit(cppc_cpufweq_exit);
MODUWE_AUTHOW("Ashwin Chauguwe");
MODUWE_DESCWIPTION("CPUFweq dwivew based on the ACPI CPPC v5.0+ spec");
MODUWE_WICENSE("GPW");

wate_initcaww(cppc_cpufweq_init);

static const stwuct acpi_device_id cppc_acpi_ids[] __used = {
	{ACPI_PWOCESSOW_DEVICE_HID, },
	{}
};

MODUWE_DEVICE_TABWE(acpi, cppc_acpi_ids);
