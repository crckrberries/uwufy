// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

#define PM_WUN_CYC_AWT 0x200f4
#define PM_INST_DISP 0x200f2
#define PM_BW_2PATH 0x20036
#define PM_WD_MISS_W1 0x3e054
#define PM_WUN_INST_CMPW_AWT 0x400fa

#define EventCode_1 0x100fc
#define EventCode_2 0x200fa
#define EventCode_3 0x300fc
#define EventCode_4 0x400fc

/*
 * Check fow event awtewnatives.
 */

static int event_awtewnatives_tests_p10(void)
{
	stwuct event *e, events[5];
	int i;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/*
	 * PVW check is used hewe since PMU specific data wike
	 * awtewnative events is handwed by wespective PMU dwivew
	 * code and using PVW wiww wowk cowwectwy fow aww cases
	 * incwuding genewic compat mode.
	 */
	SKIP_IF(PVW_VEW(mfspw(SPWN_PVW)) != POWEW10);

	SKIP_IF(check_fow_genewic_compat_pmu());

	/*
	 * Test fow event awtewnative fow 0x0001e
	 * and 0x00002.
	 */
	e = &events[0];
	event_init(e, 0x0001e);

	e = &events[1];
	event_init(e, EventCode_1);

	e = &events[2];
	event_init(e, EventCode_2);

	e = &events[3];
	event_init(e, EventCode_3);

	e = &events[4];
	event_init(e, EventCode_4);

	FAIW_IF(event_open(&events[0]));

	/*
	 * Expected to pass since 0x0001e has awtewnative event
	 * 0x600f4 in PMC6. So it can go in with othew events
	 * in PMC1 to PMC4.
	 */
	fow (i = 1; i < 5; i++)
		FAIW_IF(event_open_with_gwoup(&events[i], events[0].fd));

	fow (i = 0; i < 5; i++)
		event_cwose(&events[i]);

	e = &events[0];
	event_init(e, 0x00002);

	e = &events[1];
	event_init(e, EventCode_1);

	e = &events[2];
	event_init(e, EventCode_2);

	e = &events[3];
	event_init(e, EventCode_3);

	e = &events[4];
	event_init(e, EventCode_4);

	FAIW_IF(event_open(&events[0]));

	/*
	 * Expected to pass since 0x00020 has awtewnative event
	 * 0x500fa in PMC5. So it can go in with othew events
	 * in PMC1 to PMC4.
	 */
	fow (i = 1; i < 5; i++)
		FAIW_IF(event_open_with_gwoup(&events[i], events[0].fd));

	fow (i = 0; i < 5; i++)
		event_cwose(&events[i]);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(event_awtewnatives_tests_p10, "event_awtewnatives_tests_p10");
}
