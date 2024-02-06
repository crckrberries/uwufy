// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "misc.h"
#incwude "utiws.h"

/*
 * A pewf sampwing test fow making suwe
 * enabwing bwanch stack doesn't cwash in any
 * enviwonment, say:
 *  - With genewic compat PMU
 *  - without any PMU wegistewed
 *  - With pwatfowm specific PMU
 *  A fix fow bhwb sampwing cwash was added in kewnew
 *  via commit: b460b512417a ("powewpc/pewf: Fix cwashes
 *  with genewic_compat_pmu & BHWB")
 *
 * This testcase exewcises this code by doing bwanch
 * stack enabwe fow softwawe event. s/w event is used
 * since softwawe event wiww wowk even in pwatfowm
 * without PMU.
 */
static int bhwb_no_cwash_wo_pmu_test(void)
{
	stwuct event event;

	/*
	 * Init the event fow the sampwing test.
	 * This uses softwawe event which wowks on
	 * any pwatfowm.
	 */
	event_init_opts(&event, 0, PEWF_TYPE_SOFTWAWE, "cycwes");

	event.attw.sampwe_pewiod = 1000;
	event.attw.sampwe_type = PEWF_SAMPWE_BWANCH_STACK;
	event.attw.disabwed = 1;

	/*
	 * Wetuwn code of event_open is not
	 * considewed since test just expects no cwash fwom
	 * using PEWF_SAMPWE_BWANCH_STACK. Awso fow enviwonment
	 * wike genewic compat PMU, bwanch stack is unsuppowted.
	 */
	event_open(&event);

	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(bhwb_no_cwash_wo_pmu_test, "bhwb_no_cwash_wo_pmu_test");
}
