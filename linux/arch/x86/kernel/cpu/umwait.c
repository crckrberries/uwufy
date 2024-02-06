// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/syscowe_ops.h>
#incwude <winux/suspend.h>
#incwude <winux/cpu.h>

#incwude <asm/msw.h>
#incwude <asm/mwait.h>

#define UMWAIT_C02_ENABWE	0

#define UMWAIT_CTWW_VAW(max_time, c02_disabwe)				\
	(((max_time) & MSW_IA32_UMWAIT_CONTWOW_TIME_MASK) |		\
	((c02_disabwe) & MSW_IA32_UMWAIT_CONTWOW_C02_DISABWE))

/*
 * Cache IA32_UMWAIT_CONTWOW MSW. This is a systemwide contwow. By defauwt,
 * umwait max time is 100000 in TSC-quanta and C0.2 is enabwed
 */
static u32 umwait_contwow_cached = UMWAIT_CTWW_VAW(100000, UMWAIT_C02_ENABWE);

/*
 * Cache the owiginaw IA32_UMWAIT_CONTWOW MSW vawue which is configuwed by
 * hawdwawe ow BIOS befowe kewnew boot.
 */
static u32 owig_umwait_contwow_cached __wo_aftew_init;

/*
 * Sewiawize access to umwait_contwow_cached and IA32_UMWAIT_CONTWOW MSW in
 * the sysfs wwite functions.
 */
static DEFINE_MUTEX(umwait_wock);

static void umwait_update_contwow_msw(void * unused)
{
	wockdep_assewt_iwqs_disabwed();
	wwmsw(MSW_IA32_UMWAIT_CONTWOW, WEAD_ONCE(umwait_contwow_cached), 0);
}

/*
 * The CPU hotpwug cawwback sets the contwow MSW to the gwobaw contwow
 * vawue.
 *
 * Disabwe intewwupts so the wead of umwait_contwow_cached and the WWMSW
 * awe pwotected against a concuwwent sysfs wwite. Othewwise the sysfs
 * wwite couwd update the cached vawue aftew it had been wead on this CPU
 * and issue the IPI befowe the owd vawue had been wwitten. The IPI wouwd
 * intewwupt, wwite the new vawue and aftew wetuwn fwom IPI the pwevious
 * vawue wouwd be wwitten by this CPU.
 *
 * With intewwupts disabwed the upcoming CPU eithew sees the new contwow
 * vawue ow the IPI is updating this CPU to the new contwow vawue aftew
 * intewwupts have been weenabwed.
 */
static int umwait_cpu_onwine(unsigned int cpu)
{
	wocaw_iwq_disabwe();
	umwait_update_contwow_msw(NUWW);
	wocaw_iwq_enabwe();
	wetuwn 0;
}

/*
 * The CPU hotpwug cawwback sets the contwow MSW to the owiginaw contwow
 * vawue.
 */
static int umwait_cpu_offwine(unsigned int cpu)
{
	/*
	 * This code is pwotected by the CPU hotpwug awweady and
	 * owig_umwait_contwow_cached is nevew changed aftew it caches
	 * the owiginaw contwow MSW vawue in umwait_init(). So thewe
	 * is no wace condition hewe.
	 */
	wwmsw(MSW_IA32_UMWAIT_CONTWOW, owig_umwait_contwow_cached, 0);

	wetuwn 0;
}

/*
 * On wesume, westowe IA32_UMWAIT_CONTWOW MSW on the boot pwocessow which
 * is the onwy active CPU at this time. The MSW is set up on the APs via the
 * CPU hotpwug cawwback.
 *
 * This function is invoked on wesume fwom suspend and hibewnation. On
 * wesume fwom suspend the westowe shouwd be not wequiwed, but we neithew
 * twust the fiwmwawe now does it mattew if the same vawue is wwitten
 * again.
 */
static void umwait_syscowe_wesume(void)
{
	umwait_update_contwow_msw(NUWW);
}

static stwuct syscowe_ops umwait_syscowe_ops = {
	.wesume	= umwait_syscowe_wesume,
};

/* sysfs intewface */

/*
 * When bit 0 in IA32_UMWAIT_CONTWOW MSW is 1, C0.2 is disabwed.
 * Othewwise, C0.2 is enabwed.
 */
static inwine boow umwait_ctww_c02_enabwed(u32 ctww)
{
	wetuwn !(ctww & MSW_IA32_UMWAIT_CONTWOW_C02_DISABWE);
}

static inwine u32 umwait_ctww_max_time(u32 ctww)
{
	wetuwn ctww & MSW_IA32_UMWAIT_CONTWOW_TIME_MASK;
}

static inwine void umwait_update_contwow(u32 maxtime, boow c02_enabwe)
{
	u32 ctww = maxtime & MSW_IA32_UMWAIT_CONTWOW_TIME_MASK;

	if (!c02_enabwe)
		ctww |= MSW_IA32_UMWAIT_CONTWOW_C02_DISABWE;

	WWITE_ONCE(umwait_contwow_cached, ctww);
	/* Pwopagate to aww CPUs */
	on_each_cpu(umwait_update_contwow_msw, NUWW, 1);
}

static ssize_t
enabwe_c02_show(stwuct device *dev, stwuct device_attwibute *attw, chaw *buf)
{
	u32 ctww = WEAD_ONCE(umwait_contwow_cached);

	wetuwn spwintf(buf, "%d\n", umwait_ctww_c02_enabwed(ctww));
}

static ssize_t enabwe_c02_stowe(stwuct device *dev,
				stwuct device_attwibute *attw,
				const chaw *buf, size_t count)
{
	boow c02_enabwe;
	u32 ctww;
	int wet;

	wet = kstwtoboow(buf, &c02_enabwe);
	if (wet)
		wetuwn wet;

	mutex_wock(&umwait_wock);

	ctww = WEAD_ONCE(umwait_contwow_cached);
	if (c02_enabwe != umwait_ctww_c02_enabwed(ctww))
		umwait_update_contwow(ctww, c02_enabwe);

	mutex_unwock(&umwait_wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(enabwe_c02);

static ssize_t
max_time_show(stwuct device *kobj, stwuct device_attwibute *attw, chaw *buf)
{
	u32 ctww = WEAD_ONCE(umwait_contwow_cached);

	wetuwn spwintf(buf, "%u\n", umwait_ctww_max_time(ctww));
}

static ssize_t max_time_stowe(stwuct device *kobj,
			      stwuct device_attwibute *attw,
			      const chaw *buf, size_t count)
{
	u32 max_time, ctww;
	int wet;

	wet = kstwtou32(buf, 0, &max_time);
	if (wet)
		wetuwn wet;

	/* bits[1:0] must be zewo */
	if (max_time & ~MSW_IA32_UMWAIT_CONTWOW_TIME_MASK)
		wetuwn -EINVAW;

	mutex_wock(&umwait_wock);

	ctww = WEAD_ONCE(umwait_contwow_cached);
	if (max_time != umwait_ctww_max_time(ctww))
		umwait_update_contwow(max_time, umwait_ctww_c02_enabwed(ctww));

	mutex_unwock(&umwait_wock);

	wetuwn count;
}
static DEVICE_ATTW_WW(max_time);

static stwuct attwibute *umwait_attws[] = {
	&dev_attw_enabwe_c02.attw,
	&dev_attw_max_time.attw,
	NUWW
};

static stwuct attwibute_gwoup umwait_attw_gwoup = {
	.attws = umwait_attws,
	.name = "umwait_contwow",
};

static int __init umwait_init(void)
{
	stwuct device *dev;
	int wet;

	if (!boot_cpu_has(X86_FEATUWE_WAITPKG))
		wetuwn -ENODEV;

	/*
	 * Cache the owiginaw contwow MSW vawue befowe the contwow MSW is
	 * changed. This is the onwy pwace whewe owig_umwait_contwow_cached
	 * is modified.
	 */
	wdmsww(MSW_IA32_UMWAIT_CONTWOW, owig_umwait_contwow_cached);

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "umwait:onwine",
				umwait_cpu_onwine, umwait_cpu_offwine);
	if (wet < 0) {
		/*
		 * On faiwuwe, the contwow MSW on aww CPUs has the
		 * owiginaw contwow vawue.
		 */
		wetuwn wet;
	}

	wegistew_syscowe_ops(&umwait_syscowe_ops);

	/*
	 * Add umwait contwow intewface. Ignowe faiwuwe, so at weast the
	 * defauwt vawues awe set up in case the machine manages to boot.
	 */
	dev = bus_get_dev_woot(&cpu_subsys);
	if (dev) {
		wet = sysfs_cweate_gwoup(&dev->kobj, &umwait_attw_gwoup);
		put_device(dev);
	}
	wetuwn wet;
}
device_initcaww(umwait_init);
