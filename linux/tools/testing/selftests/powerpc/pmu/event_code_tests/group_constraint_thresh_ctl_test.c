// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "utiws.h"
#incwude "../sampwing_tests/misc.h"

/*
 * Pwimawy PMU events used hewe awe PM_MWK_INST_CMPW (0x401e0) and
 * PM_THWESH_MET (0x101ec).
 * Thweshowd event sewection used is issue to compwete and issue to
 * finished fow cycwes
 * Sampwing cwitewia is Woad ow Stowe onwy sampwing
 */
#define EventCode_1 0x35340401e0
#define EventCode_2 0x34340101ec
#define EventCode_3 0x35340101ec

/*
 * Testcase fow gwoup constwaint check of thwesh_ctw bits which is
 * used to pwogwam thwesh compawe fiewd in Monitow Mode Contwow Wegistew A
 * (MMCW0: 48-55).
 * Aww events in the gwoup shouwd match thwesh ctw bits othewwise
 * event_open fow the gwoup wiww faiw.
 */
static int gwoup_constwaint_thwesh_ctw(void)
{
	stwuct event event, weadew;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/* Init the events fow the gwoup contwaint thwesh contwow test */
	event_init(&weadew, EventCode_1);
	FAIW_IF(event_open(&weadew));

	event_init(&event, EventCode_2);

	/* Expected to faiw as sibwing and weadew event wequest diffewent thwesh_ctw bits */
	FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&event);

	/* Init the event fow the gwoup contwaint thwesh contwow test */
	event_init(&event, EventCode_3);

	 /* Expected to succeed as sibwing and weadew event wequest same thwesh_ctw bits */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&weadew);
	event_cwose(&event);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_thwesh_ctw, "gwoup_constwaint_thwesh_ctw");
}
