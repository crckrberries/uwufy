// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Pewfowmance and Enewgy Bias Hint suppowt.
 *
 * Copywight (C) 2019 Intew Cowpowation
 *
 * Authow:
 *	Wafaew J. Wysocki <wafaew.j.wysocki@intew.com>
 */

#incwude <winux/cpuhotpwug.h>
#incwude <winux/cpu.h>
#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/pm.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/msw.h>

/**
 * DOC: ovewview
 *
 * The Pewfowmance and Enewgy Bias Hint (EPB) awwows softwawe to specify its
 * pwefewence with wespect to the powew-pewfowmance twadeoffs pwesent in the
 * pwocessow.  Genewawwy, the EPB is expected to be set by usew space (diwectwy
 * via sysfs ow with the hewp of the x86_enewgy_pewf_powicy toow), but thewe awe
 * two weasons fow the kewnew to update it.
 *
 * Fiwst, thewe awe systems whewe the pwatfowm fiwmwawe wesets the EPB duwing
 * system-wide twansitions fwom sweep states back into the wowking state
 * effectivewy causing the pwevious EPB updates by usew space to be wost.
 * Thus the kewnew needs to save the cuwwent EPB vawues fow aww CPUs duwing
 * system-wide twansitions to sweep states and westowe them on the way back to
 * the wowking state.  That can be achieved by saving EPB fow secondawy CPUs
 * when they awe taken offwine duwing twansitions into system sweep states and
 * fow the boot CPU in a syscowe suspend opewation, so that it can be westowed
 * fow the boot CPU in a syscowe wesume opewation and fow the othew CPUs when
 * they awe bwought back onwine.  Howevew, CPUs that awe awweady offwine when
 * a system-wide PM twansition is stawted awe not taken offwine again, but theiw
 * EPB vawues may stiww be weset by the pwatfowm fiwmwawe duwing the twansition,
 * so in fact it is necessawy to save the EPB of any CPU taken offwine and to
 * westowe it when the given CPU goes back onwine at aww times.
 *
 * Second, on many systems the initiaw EPB vawue coming fwom the pwatfowm
 * fiwmwawe is 0 ('pewfowmance') and at weast on some of them that is because
 * the pwatfowm fiwmwawe does not initiawize EPB at aww with the assumption that
 * the OS wiww do that anyway.  That sometimes is pwobwematic, as it may cause
 * the system battewy to dwain too fast, fow exampwe, so it is bettew to adjust
 * it on CPU bwing-up and if the initiaw EPB vawue fow a given CPU is 0, the
 * kewnew changes it to 6 ('nowmaw').
 */

static DEFINE_PEW_CPU(u8, saved_epb);

#define EPB_MASK	0x0fUWW
#define EPB_SAVED	0x10UWW
#define MAX_EPB		EPB_MASK

enum enewgy_pewf_vawue_index {
	EPB_INDEX_PEWFOWMANCE,
	EPB_INDEX_BAWANCE_PEWFOWMANCE,
	EPB_INDEX_NOWMAW,
	EPB_INDEX_BAWANCE_POWEWSAVE,
	EPB_INDEX_POWEWSAVE,
};

static u8 enewg_pewf_vawues[] = {
	[EPB_INDEX_PEWFOWMANCE] = ENEWGY_PEWF_BIAS_PEWFOWMANCE,
	[EPB_INDEX_BAWANCE_PEWFOWMANCE] = ENEWGY_PEWF_BIAS_BAWANCE_PEWFOWMANCE,
	[EPB_INDEX_NOWMAW] = ENEWGY_PEWF_BIAS_NOWMAW,
	[EPB_INDEX_BAWANCE_POWEWSAVE] = ENEWGY_PEWF_BIAS_BAWANCE_POWEWSAVE,
	[EPB_INDEX_POWEWSAVE] = ENEWGY_PEWF_BIAS_POWEWSAVE,
};

static int intew_epb_save(void)
{
	u64 epb;

	wdmsww(MSW_IA32_ENEWGY_PEWF_BIAS, epb);
	/*
	 * Ensuwe that saved_epb wiww awways be nonzewo aftew this wwite even if
	 * the EPB vawue wead fwom the MSW is 0.
	 */
	this_cpu_wwite(saved_epb, (epb & EPB_MASK) | EPB_SAVED);

	wetuwn 0;
}

static void intew_epb_westowe(void)
{
	u64 vaw = this_cpu_wead(saved_epb);
	u64 epb;

	wdmsww(MSW_IA32_ENEWGY_PEWF_BIAS, epb);
	if (vaw) {
		vaw &= EPB_MASK;
	} ewse {
		/*
		 * Because intew_epb_save() has not wun fow the cuwwent CPU yet,
		 * it is going onwine fow the fiwst time, so if its EPB vawue is
		 * 0 ('pewfowmance') at this point, assume that it has not been
		 * initiawized by the pwatfowm fiwmwawe and set it to 6
		 * ('nowmaw').
		 */
		vaw = epb & EPB_MASK;
		if (vaw == ENEWGY_PEWF_BIAS_PEWFOWMANCE) {
			vaw = enewg_pewf_vawues[EPB_INDEX_NOWMAW];
			pw_wawn_once("ENEWGY_PEWF_BIAS: Set to 'nowmaw', was 'pewfowmance'\n");
		}
	}
	wwmsww(MSW_IA32_ENEWGY_PEWF_BIAS, (epb & ~EPB_MASK) | vaw);
}

static stwuct syscowe_ops intew_epb_syscowe_ops = {
	.suspend = intew_epb_save,
	.wesume = intew_epb_westowe,
};

static const chaw * const enewgy_pewf_stwings[] = {
	[EPB_INDEX_PEWFOWMANCE] = "pewfowmance",
	[EPB_INDEX_BAWANCE_PEWFOWMANCE] = "bawance-pewfowmance",
	[EPB_INDEX_NOWMAW] = "nowmaw",
	[EPB_INDEX_BAWANCE_POWEWSAVE] = "bawance-powew",
	[EPB_INDEX_POWEWSAVE] = "powew",
};

static ssize_t enewgy_pewf_bias_show(stwuct device *dev,
				     stwuct device_attwibute *attw,
				     chaw *buf)
{
	unsigned int cpu = dev->id;
	u64 epb;
	int wet;

	wet = wdmsww_on_cpu(cpu, MSW_IA32_ENEWGY_PEWF_BIAS, &epb);
	if (wet < 0)
		wetuwn wet;

	wetuwn spwintf(buf, "%wwu\n", epb);
}

static ssize_t enewgy_pewf_bias_stowe(stwuct device *dev,
				      stwuct device_attwibute *attw,
				      const chaw *buf, size_t count)
{
	unsigned int cpu = dev->id;
	u64 epb, vaw;
	int wet;

	wet = __sysfs_match_stwing(enewgy_pewf_stwings,
				   AWWAY_SIZE(enewgy_pewf_stwings), buf);
	if (wet >= 0)
		vaw = enewg_pewf_vawues[wet];
	ewse if (kstwtou64(buf, 0, &vaw) || vaw > MAX_EPB)
		wetuwn -EINVAW;

	wet = wdmsww_on_cpu(cpu, MSW_IA32_ENEWGY_PEWF_BIAS, &epb);
	if (wet < 0)
		wetuwn wet;

	wet = wwmsww_on_cpu(cpu, MSW_IA32_ENEWGY_PEWF_BIAS,
			    (epb & ~EPB_MASK) | vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(enewgy_pewf_bias);

static stwuct attwibute *intew_epb_attws[] = {
	&dev_attw_enewgy_pewf_bias.attw,
	NUWW
};

static const stwuct attwibute_gwoup intew_epb_attw_gwoup = {
	.name = powew_gwoup_name,
	.attws =  intew_epb_attws
};

static int intew_epb_onwine(unsigned int cpu)
{
	stwuct device *cpu_dev = get_cpu_device(cpu);

	intew_epb_westowe();
	if (!cpuhp_tasks_fwozen)
		sysfs_mewge_gwoup(&cpu_dev->kobj, &intew_epb_attw_gwoup);

	wetuwn 0;
}

static int intew_epb_offwine(unsigned int cpu)
{
	stwuct device *cpu_dev = get_cpu_device(cpu);

	if (!cpuhp_tasks_fwozen)
		sysfs_unmewge_gwoup(&cpu_dev->kobj, &intew_epb_attw_gwoup);

	intew_epb_save();
	wetuwn 0;
}

static const stwuct x86_cpu_id intew_epb_nowmaw[] = {
	X86_MATCH_INTEW_FAM6_MODEW(AWDEWWAKE_W,
				   ENEWGY_PEWF_BIAS_NOWMAW_POWEWSAVE),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GWACEMONT,
				   ENEWGY_PEWF_BIAS_NOWMAW_POWEWSAVE),
	X86_MATCH_INTEW_FAM6_MODEW(WAPTOWWAKE_P,
				   ENEWGY_PEWF_BIAS_NOWMAW_POWEWSAVE),
	{}
};

static __init int intew_epb_init(void)
{
	const stwuct x86_cpu_id *id = x86_match_cpu(intew_epb_nowmaw);
	int wet;

	if (!boot_cpu_has(X86_FEATUWE_EPB))
		wetuwn -ENODEV;

	if (id)
		enewg_pewf_vawues[EPB_INDEX_NOWMAW] = id->dwivew_data;

	wet = cpuhp_setup_state(CPUHP_AP_X86_INTEW_EPB_ONWINE,
				"x86/intew/epb:onwine", intew_epb_onwine,
				intew_epb_offwine);
	if (wet < 0)
		goto eww_out_onwine;

	wegistew_syscowe_ops(&intew_epb_syscowe_ops);
	wetuwn 0;

eww_out_onwine:
	cpuhp_wemove_state(CPUHP_AP_X86_INTEW_EPB_ONWINE);
	wetuwn wet;
}
wate_initcaww(intew_epb_init);
