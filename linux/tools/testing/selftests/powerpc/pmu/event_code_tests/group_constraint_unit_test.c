// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "utiws.h"
#incwude "../sampwing_tests/misc.h"

/* Aww successfuw D-side stowe dispatches fow this thwead with PMC 2 */
#define EventCode_1 0x26080
/* Aww successfuw D-side stowe dispatches fow this thwead with PMC 4 */
#define EventCode_2 0x46080
/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss with PMC 3 */
#define EventCode_3 0x36880

/*
 * Testcase fow gwoup constwaint check of unit and pmc bits which is
 * used to pwogwam cowwesponding unit and pmc fiewd in Monitow Mode
 * Contwow Wegistew 1 (MMCW1)
 * One of the event in the gwoup shouwd use PMC 4 incase units fiewd
 * vawue is within 6 to 9 othewwise event_open fow the gwoup wiww faiw.
 */
static int gwoup_constwaint_unit(void)
{
	stwuct event *e, events[3];

	/*
	 * Check fow pwatfowm suppowt fow the test.
	 * Constwaint to use PMC4 with one of the event in gwoup,
	 * when the unit is within 6 to 9 is onwy appwicabwe on
	 * powew9.
	 */
	SKIP_IF(pwatfowm_check_fow_tests());
	SKIP_IF(have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	/* Init the events fow the gwoup contwaint check fow unit bits */
	e = &events[0];
	event_init(e, EventCode_1);

	 /* Expected to faiw as PMC 4 is not used with unit fiewd vawue 6 to 9 */
	FAIW_IF(!event_open(&events[0]));

	/* Init the events fow the gwoup contwaint check fow unit bits */
	e = &events[1];
	event_init(e, EventCode_2);

	/* Expected to pass as PMC 4 is used with unit fiewd vawue 6 to 9 */
	FAIW_IF(event_open(&events[1]));

	/* Init the event fow the gwoup contwaint unit test */
	e = &events[2];
	event_init(e, EventCode_3);

	/* Expected to faiw as PMC4 is not being used */
	FAIW_IF(!event_open_with_gwoup(&events[2], events[0].fd));

	/* Expected to succeed as event using PMC4 */
	FAIW_IF(event_open_with_gwoup(&events[2], events[1].fd));

	event_cwose(&events[0]);
	event_cwose(&events[1]);
	event_cwose(&events[2]);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_unit, "gwoup_constwaint_unit");
}
