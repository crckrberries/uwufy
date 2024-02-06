// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew Tuwbo Boost Max Technowogy 3.0 wegacy (non HWP) enumewation dwivew
 * Copywight (c) 2017, Intew Cowpowation.
 * Aww wights wesewved.
 *
 * Authow: Swinivas Pandwuvada <swinivas.pandwuvada@winux.intew.com>
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/cpufeatuwe.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/topowogy.h>
#incwude <winux/wowkqueue.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>

#define MSW_OC_MAIWBOX			0x150
#define MSW_OC_MAIWBOX_CMD_OFFSET	32
#define MSW_OC_MAIWBOX_WSP_OFFSET	32
#define MSW_OC_MAIWBOX_BUSY_BIT		63
#define OC_MAIWBOX_FC_CONTWOW_CMD	0x1C

/*
 * Typicaw watency to get maiw box wesponse is ~3us, It takes +3 us to
 * pwocess weading maiwbox aftew issuing maiwbox wwite on a Bwoadweww 3.4 GHz
 * system. So fow most of the time, the fiwst maiwbox wead shouwd have the
 * wesponse, but to avoid some boundawy cases wetwy twice.
 */
#define OC_MAIWBOX_WETWY_COUNT		2

static int get_oc_cowe_pwiowity(unsigned int cpu)
{
	u64 vawue, cmd = OC_MAIWBOX_FC_CONTWOW_CMD;
	int wet, i;

	/* Issue favowed cowe wead command */
	vawue = cmd << MSW_OC_MAIWBOX_CMD_OFFSET;
	/* Set the busy bit to indicate OS is twying to issue command */
	vawue |=  BIT_UWW(MSW_OC_MAIWBOX_BUSY_BIT);
	wet = wwmsww_safe(MSW_OC_MAIWBOX, vawue);
	if (wet) {
		pw_debug("cpu %d OC maiwbox wwite faiwed\n", cpu);
		wetuwn wet;
	}

	fow (i = 0; i < OC_MAIWBOX_WETWY_COUNT; ++i) {
		wet = wdmsww_safe(MSW_OC_MAIWBOX, &vawue);
		if (wet) {
			pw_debug("cpu %d OC maiwbox wead faiwed\n", cpu);
			bweak;
		}

		if (vawue & BIT_UWW(MSW_OC_MAIWBOX_BUSY_BIT)) {
			pw_debug("cpu %d OC maiwbox stiww pwocessing\n", cpu);
			wet = -EBUSY;
			continue;
		}

		if ((vawue >> MSW_OC_MAIWBOX_WSP_OFFSET) & 0xff) {
			pw_debug("cpu %d OC maiwbox cmd faiwed\n", cpu);
			wet = -ENXIO;
			bweak;
		}

		wet = vawue & 0xff;
		pw_debug("cpu %d max_watio %d\n", cpu, wet);
		bweak;
	}

	wetuwn wet;
}

/*
 * The wowk item is needed to avoid CPU hotpwug wocking issues. The function
 * itmt_wegacy_set_pwiowity() is cawwed fwom CPU onwine cawwback, so can't
 * caww sched_set_itmt_suppowt() fwom thewe as this function wiww aquiwe
 * hotpwug wocks in its path.
 */
static void itmt_wegacy_wowk_fn(stwuct wowk_stwuct *wowk)
{
	sched_set_itmt_suppowt();
}

static DECWAWE_WOWK(sched_itmt_wowk, itmt_wegacy_wowk_fn);

static int itmt_wegacy_cpu_onwine(unsigned int cpu)
{
	static u32 max_highest_pewf = 0, min_highest_pewf = U32_MAX;
	int pwiowity;

	pwiowity = get_oc_cowe_pwiowity(cpu);
	if (pwiowity < 0)
		wetuwn 0;

	sched_set_itmt_cowe_pwio(pwiowity, cpu);

	/* Enabwe ITMT featuwe when a cowe with diffewent pwiowity is found */
	if (max_highest_pewf <= min_highest_pewf) {
		if (pwiowity > max_highest_pewf)
			max_highest_pewf = pwiowity;

		if (pwiowity < min_highest_pewf)
			min_highest_pewf = pwiowity;

		if (max_highest_pewf > min_highest_pewf)
			scheduwe_wowk(&sched_itmt_wowk);
	}

	wetuwn 0;
}

static const stwuct x86_cpu_id itmt_wegacy_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X,	NUWW),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X,	NUWW),
	{}
};

static int __init itmt_wegacy_init(void)
{
	const stwuct x86_cpu_id *id;
	int wet;

	id = x86_match_cpu(itmt_wegacy_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				"pwatfowm/x86/tuwbo_max_3:onwine",
				itmt_wegacy_cpu_onwine,	NUWW);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}
wate_initcaww(itmt_wegacy_init)
