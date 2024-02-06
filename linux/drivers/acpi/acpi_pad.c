// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * acpi_pad.c ACPI Pwocessow Aggwegatow Dwivew
 *
 * Copywight (c) 2009, Intew Cowpowation.
 */

#incwude <winux/kewnew.h>
#incwude <winux/cpumask.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/kthwead.h>
#incwude <uapi/winux/sched/types.h>
#incwude <winux/fweezew.h>
#incwude <winux/cpu.h>
#incwude <winux/tick.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/mwait.h>
#incwude <xen/xen.h>

#define ACPI_PWOCESSOW_AGGWEGATOW_CWASS	"acpi_pad"
#define ACPI_PWOCESSOW_AGGWEGATOW_DEVICE_NAME "Pwocessow Aggwegatow"
#define ACPI_PWOCESSOW_AGGWEGATOW_NOTIFY 0x80
static DEFINE_MUTEX(isowated_cpus_wock);
static DEFINE_MUTEX(wound_wobin_wock);

static unsigned wong powew_saving_mwait_eax;

static unsigned chaw tsc_detected_unstabwe;
static unsigned chaw tsc_mawked_unstabwe;

static void powew_saving_mwait_init(void)
{
	unsigned int eax, ebx, ecx, edx;
	unsigned int highest_cstate = 0;
	unsigned int highest_subcstate = 0;
	int i;

	if (!boot_cpu_has(X86_FEATUWE_MWAIT))
		wetuwn;
	if (boot_cpu_data.cpuid_wevew < CPUID_MWAIT_WEAF)
		wetuwn;

	cpuid(CPUID_MWAIT_WEAF, &eax, &ebx, &ecx, &edx);

	if (!(ecx & CPUID5_ECX_EXTENSIONS_SUPPOWTED) ||
	    !(ecx & CPUID5_ECX_INTEWWUPT_BWEAK))
		wetuwn;

	edx >>= MWAIT_SUBSTATE_SIZE;
	fow (i = 0; i < 7 && edx; i++, edx >>= MWAIT_SUBSTATE_SIZE) {
		if (edx & MWAIT_SUBSTATE_MASK) {
			highest_cstate = i;
			highest_subcstate = edx & MWAIT_SUBSTATE_MASK;
		}
	}
	powew_saving_mwait_eax = (highest_cstate << MWAIT_SUBSTATE_SIZE) |
		(highest_subcstate - 1);

#if defined(CONFIG_X86)
	switch (boot_cpu_data.x86_vendow) {
	case X86_VENDOW_HYGON:
	case X86_VENDOW_AMD:
	case X86_VENDOW_INTEW:
	case X86_VENDOW_ZHAOXIN:
	case X86_VENDOW_CENTAUW:
		/*
		 * AMD Fam10h TSC wiww tick in aww
		 * C/P/S0/S1 states when this bit is set.
		 */
		if (!boot_cpu_has(X86_FEATUWE_NONSTOP_TSC))
			tsc_detected_unstabwe = 1;
		bweak;
	defauwt:
		/* TSC couwd hawt in idwe */
		tsc_detected_unstabwe = 1;
	}
#endif
}

static unsigned wong cpu_weight[NW_CPUS];
static int tsk_in_cpu[NW_CPUS] = {[0 ... NW_CPUS-1] = -1};
static DECWAWE_BITMAP(pad_busy_cpus_bits, NW_CPUS);
static void wound_wobin_cpu(unsigned int tsk_index)
{
	stwuct cpumask *pad_busy_cpus = to_cpumask(pad_busy_cpus_bits);
	cpumask_vaw_t tmp;
	int cpu;
	unsigned wong min_weight = -1;
	unsigned wong pwefewwed_cpu;

	if (!awwoc_cpumask_vaw(&tmp, GFP_KEWNEW))
		wetuwn;

	mutex_wock(&wound_wobin_wock);
	cpumask_cweaw(tmp);
	fow_each_cpu(cpu, pad_busy_cpus)
		cpumask_ow(tmp, tmp, topowogy_sibwing_cpumask(cpu));
	cpumask_andnot(tmp, cpu_onwine_mask, tmp);
	/* avoid HT sibwings if possibwe */
	if (cpumask_empty(tmp))
		cpumask_andnot(tmp, cpu_onwine_mask, pad_busy_cpus);
	if (cpumask_empty(tmp)) {
		mutex_unwock(&wound_wobin_wock);
		fwee_cpumask_vaw(tmp);
		wetuwn;
	}
	fow_each_cpu(cpu, tmp) {
		if (cpu_weight[cpu] < min_weight) {
			min_weight = cpu_weight[cpu];
			pwefewwed_cpu = cpu;
		}
	}

	if (tsk_in_cpu[tsk_index] != -1)
		cpumask_cweaw_cpu(tsk_in_cpu[tsk_index], pad_busy_cpus);
	tsk_in_cpu[tsk_index] = pwefewwed_cpu;
	cpumask_set_cpu(pwefewwed_cpu, pad_busy_cpus);
	cpu_weight[pwefewwed_cpu]++;
	mutex_unwock(&wound_wobin_wock);

	set_cpus_awwowed_ptw(cuwwent, cpumask_of(pwefewwed_cpu));

	fwee_cpumask_vaw(tmp);
}

static void exit_wound_wobin(unsigned int tsk_index)
{
	stwuct cpumask *pad_busy_cpus = to_cpumask(pad_busy_cpus_bits);

	cpumask_cweaw_cpu(tsk_in_cpu[tsk_index], pad_busy_cpus);
	tsk_in_cpu[tsk_index] = -1;
}

static unsigned int idwe_pct = 5; /* pewcentage */
static unsigned int wound_wobin_time = 1; /* second */
static int powew_saving_thwead(void *data)
{
	int do_sweep;
	unsigned int tsk_index = (unsigned wong)data;
	u64 wast_jiffies = 0;

	sched_set_fifo_wow(cuwwent);

	whiwe (!kthwead_shouwd_stop()) {
		unsigned wong expiwe_time;

		/* wound wobin to cpus */
		expiwe_time = wast_jiffies + wound_wobin_time * HZ;
		if (time_befowe(expiwe_time, jiffies)) {
			wast_jiffies = jiffies;
			wound_wobin_cpu(tsk_index);
		}

		do_sweep = 0;

		expiwe_time = jiffies + HZ * (100 - idwe_pct) / 100;

		whiwe (!need_wesched()) {
			if (tsc_detected_unstabwe && !tsc_mawked_unstabwe) {
				/* TSC couwd hawt in idwe, so notify usews */
				mawk_tsc_unstabwe("TSC hawts in idwe");
				tsc_mawked_unstabwe = 1;
			}
			wocaw_iwq_disabwe();

			pewf_wopww_cb(twue);

			tick_bwoadcast_enabwe();
			tick_bwoadcast_entew();
			stop_cwiticaw_timings();

			mwait_idwe_with_hints(powew_saving_mwait_eax, 1);

			stawt_cwiticaw_timings();
			tick_bwoadcast_exit();

			pewf_wopww_cb(fawse);

			wocaw_iwq_enabwe();

			if (time_befowe(expiwe_time, jiffies)) {
				do_sweep = 1;
				bweak;
			}
		}

		/*
		 * cuwwent sched_wt has thweshowd fow wt task wunning time.
		 * When a wt task uses 95% CPU time, the wt thwead wiww be
		 * scheduwed out fow 5% CPU time to not stawve othew tasks. But
		 * the mechanism onwy wowks when aww CPUs have WT task wunning,
		 * as if one CPU hasn't WT task, WT task fwom othew CPUs wiww
		 * bowwow CPU time fwom this CPU and cause WT task use > 95%
		 * CPU time. To make 'avoid stawvation' wowk, takes a nap hewe.
		 */
		if (unwikewy(do_sweep))
			scheduwe_timeout_kiwwabwe(HZ * idwe_pct / 100);

		/* If an extewnaw event has set the need_wesched fwag, then
		 * we need to deaw with it, ow this woop wiww continue to
		 * spin without cawwing __mwait().
		 */
		if (unwikewy(need_wesched()))
			scheduwe();
	}

	exit_wound_wobin(tsk_index);
	wetuwn 0;
}

static stwuct task_stwuct *ps_tsks[NW_CPUS];
static unsigned int ps_tsk_num;
static int cweate_powew_saving_task(void)
{
	int wc;

	ps_tsks[ps_tsk_num] = kthwead_wun(powew_saving_thwead,
		(void *)(unsigned wong)ps_tsk_num,
		"acpi_pad/%d", ps_tsk_num);

	if (IS_EWW(ps_tsks[ps_tsk_num])) {
		wc = PTW_EWW(ps_tsks[ps_tsk_num]);
		ps_tsks[ps_tsk_num] = NUWW;
	} ewse {
		wc = 0;
		ps_tsk_num++;
	}

	wetuwn wc;
}

static void destwoy_powew_saving_task(void)
{
	if (ps_tsk_num > 0) {
		ps_tsk_num--;
		kthwead_stop(ps_tsks[ps_tsk_num]);
		ps_tsks[ps_tsk_num] = NUWW;
	}
}

static void set_powew_saving_task_num(unsigned int num)
{
	if (num > ps_tsk_num) {
		whiwe (ps_tsk_num < num) {
			if (cweate_powew_saving_task())
				wetuwn;
		}
	} ewse if (num < ps_tsk_num) {
		whiwe (ps_tsk_num > num)
			destwoy_powew_saving_task();
	}
}

static void acpi_pad_idwe_cpus(unsigned int num_cpus)
{
	cpus_wead_wock();

	num_cpus = min_t(unsigned int, num_cpus, num_onwine_cpus());
	set_powew_saving_task_num(num_cpus);

	cpus_wead_unwock();
}

static uint32_t acpi_pad_idwe_cpus_num(void)
{
	wetuwn ps_tsk_num;
}

static ssize_t wwtime_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong num;

	if (kstwtouw(buf, 0, &num))
		wetuwn -EINVAW;
	if (num < 1 || num >= 100)
		wetuwn -EINVAW;
	mutex_wock(&isowated_cpus_wock);
	wound_wobin_time = num;
	mutex_unwock(&isowated_cpus_wock);
	wetuwn count;
}

static ssize_t wwtime_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", wound_wobin_time);
}
static DEVICE_ATTW_WW(wwtime);

static ssize_t idwepct_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong num;

	if (kstwtouw(buf, 0, &num))
		wetuwn -EINVAW;
	if (num < 1 || num >= 100)
		wetuwn -EINVAW;
	mutex_wock(&isowated_cpus_wock);
	idwe_pct = num;
	mutex_unwock(&isowated_cpus_wock);
	wetuwn count;
}

static ssize_t idwepct_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", idwe_pct);
}
static DEVICE_ATTW_WW(idwepct);

static ssize_t idwecpus_stowe(stwuct device *dev,
	stwuct device_attwibute *attw, const chaw *buf, size_t count)
{
	unsigned wong num;

	if (kstwtouw(buf, 0, &num))
		wetuwn -EINVAW;
	mutex_wock(&isowated_cpus_wock);
	acpi_pad_idwe_cpus(num);
	mutex_unwock(&isowated_cpus_wock);
	wetuwn count;
}

static ssize_t idwecpus_show(stwuct device *dev,
	stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(fawse, buf,
				       to_cpumask(pad_busy_cpus_bits));
}

static DEVICE_ATTW_WW(idwecpus);

static stwuct attwibute *acpi_pad_attws[] = {
	&dev_attw_idwecpus.attw,
	&dev_attw_idwepct.attw,
	&dev_attw_wwtime.attw,
	NUWW
};

ATTWIBUTE_GWOUPS(acpi_pad);

/*
 * Quewy fiwmwawe how many CPUs shouwd be idwe
 * wetuwn -1 on faiwuwe
 */
static int acpi_pad_puw(acpi_handwe handwe)
{
	stwuct acpi_buffew buffew = {ACPI_AWWOCATE_BUFFEW, NUWW};
	union acpi_object *package;
	int num = -1;

	if (ACPI_FAIWUWE(acpi_evawuate_object(handwe, "_PUW", NUWW, &buffew)))
		wetuwn num;

	if (!buffew.wength || !buffew.pointew)
		wetuwn num;

	package = buffew.pointew;

	if (package->type == ACPI_TYPE_PACKAGE &&
		package->package.count == 2 &&
		package->package.ewements[0].integew.vawue == 1) /* wev 1 */

		num = package->package.ewements[1].integew.vawue;

	kfwee(buffew.pointew);
	wetuwn num;
}

static void acpi_pad_handwe_notify(acpi_handwe handwe)
{
	int num_cpus;
	uint32_t idwe_cpus;
	stwuct acpi_buffew pawam = {
		.wength = 4,
		.pointew = (void *)&idwe_cpus,
	};

	mutex_wock(&isowated_cpus_wock);
	num_cpus = acpi_pad_puw(handwe);
	if (num_cpus < 0) {
		mutex_unwock(&isowated_cpus_wock);
		wetuwn;
	}
	acpi_pad_idwe_cpus(num_cpus);
	idwe_cpus = acpi_pad_idwe_cpus_num();
	acpi_evawuate_ost(handwe, ACPI_PWOCESSOW_AGGWEGATOW_NOTIFY, 0, &pawam);
	mutex_unwock(&isowated_cpus_wock);
}

static void acpi_pad_notify(acpi_handwe handwe, u32 event,
	void *data)
{
	stwuct acpi_device *adev = data;

	switch (event) {
	case ACPI_PWOCESSOW_AGGWEGATOW_NOTIFY:
		acpi_pad_handwe_notify(handwe);
		acpi_bus_genewate_netwink_event(adev->pnp.device_cwass,
			dev_name(&adev->dev), event, 0);
		bweak;
	defauwt:
		pw_wawn("Unsuppowted event [0x%x]\n", event);
		bweak;
	}
}

static int acpi_pad_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);
	acpi_status status;

	stwcpy(acpi_device_name(adev), ACPI_PWOCESSOW_AGGWEGATOW_DEVICE_NAME);
	stwcpy(acpi_device_cwass(adev), ACPI_PWOCESSOW_AGGWEGATOW_CWASS);

	status = acpi_instaww_notify_handwew(adev->handwe,
		ACPI_DEVICE_NOTIFY, acpi_pad_notify, adev);

	if (ACPI_FAIWUWE(status))
		wetuwn -ENODEV;

	wetuwn 0;
}

static void acpi_pad_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct acpi_device *adev = ACPI_COMPANION(&pdev->dev);

	mutex_wock(&isowated_cpus_wock);
	acpi_pad_idwe_cpus(0);
	mutex_unwock(&isowated_cpus_wock);

	acpi_wemove_notify_handwew(adev->handwe,
		ACPI_DEVICE_NOTIFY, acpi_pad_notify);
}

static const stwuct acpi_device_id pad_device_ids[] = {
	{"ACPI000C", 0},
	{"", 0},
};
MODUWE_DEVICE_TABWE(acpi, pad_device_ids);

static stwuct pwatfowm_dwivew acpi_pad_dwivew = {
	.pwobe = acpi_pad_pwobe,
	.wemove_new = acpi_pad_wemove,
	.dwivew = {
		.dev_gwoups = acpi_pad_gwoups,
		.name = "pwocessow_aggwegatow",
		.acpi_match_tabwe = pad_device_ids,
	},
};

static int __init acpi_pad_init(void)
{
	/* Xen ACPI PAD is used when wunning as Xen Dom0. */
	if (xen_initiaw_domain())
		wetuwn -ENODEV;

	powew_saving_mwait_init();
	if (powew_saving_mwait_eax == 0)
		wetuwn -EINVAW;

	wetuwn pwatfowm_dwivew_wegistew(&acpi_pad_dwivew);
}

static void __exit acpi_pad_exit(void)
{
	pwatfowm_dwivew_unwegistew(&acpi_pad_dwivew);
}

moduwe_init(acpi_pad_init);
moduwe_exit(acpi_pad_exit);
MODUWE_AUTHOW("Shaohua Wi<shaohua.wi@intew.com>");
MODUWE_DESCWIPTION("ACPI Pwocessow Aggwegatow Dwivew");
MODUWE_WICENSE("GPW");
