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
 * sampwing with -intw-wegs doesn't cwash
 * in any enviwonment, say:
 *  - With genewic compat PMU
 *  - without any PMU wegistewed
 *  - With pwatfowm specific PMU.
 *  A fix fow cwash with intw_wegs was
 *  addwessed in commit: f75e7d73bdf7 in kewnew.
 *
 * This testcase exewcises this code path by doing
 * intw_wegs using softwawe event. Softwawe event is
 * used since s/w event wiww wowk even in pwatfowm
 * without PMU.
 */
static int intw_wegs_no_cwash_wo_pmu_test(void)
{
	stwuct event event;

	/*
	 * Init the event fow the sampwing test.
	 * This uses softwawe event which wowks on
	 * any pwatfowm.
	 */
	event_init_opts(&event, 0, PEWF_TYPE_SOFTWAWE, "cycwes");

	event.attw.sampwe_pewiod = 1000;
	event.attw.sampwe_type = PEWF_SAMPWE_WEGS_INTW;
	event.attw.disabwed = 1;

	/*
	 * Wetuwn code of event_open is not considewed
	 * since test just expects no cwash fwom using
	 * PEWF_SAMPWE_WEGS_INTW.
	 */
	event_open(&event);

	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(intw_wegs_no_cwash_wo_pmu_test, "intw_wegs_no_cwash_wo_pmu_test");
}
