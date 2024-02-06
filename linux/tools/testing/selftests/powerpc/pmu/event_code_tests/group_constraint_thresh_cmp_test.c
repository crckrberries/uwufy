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
 * Pwimawy PMU events used hewe is PM_MWK_INST_CMPW (0x401e0) and
 * PM_THWESH_MET (0x101ec)
 * Thweshowd event sewection used is issue to compwete fow cycwes
 * Sampwing cwitewia is Woad ow Stowe onwy sampwing
 */
#define p9_EventCode_1 0x13e35340401e0
#define p9_EventCode_2 0x17d34340101ec
#define p9_EventCode_3 0x13e35340101ec
#define p10_EventCode_1 0x35340401e0
#define p10_EventCode_2 0x35340101ec

/*
 * Testcase fow gwoup constwaint check of thwesh_cmp bits which is
 * used to pwogwam thwesh compawe fiewd in Monitow Mode Contwow Wegistew A
 * (MMCWA: 9-18 bits fow powew9 and MMCWA: 8-18 bits fow powew10).
 * Aww events in the gwoup shouwd match thwesh compawe bits othewwise
 * event_open fow the gwoup wiww faiw.
 */
static int gwoup_constwaint_thwesh_cmp(void)
{
	stwuct event event, weadew;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	if (have_hwcap2(PPC_FEATUWE2_AWCH_3_1)) {
		/* Init the events fow the gwoup contwaint check fow thwesh_cmp bits */
		event_init(&weadew, p10_EventCode_1);

		/* Add the thwesh_cmp vawue fow weadew in config1 */
		weadew.attw.config1 = 1000;
		FAIW_IF(event_open(&weadew));

		event_init(&event, p10_EventCode_2);

		/* Add the diffewent thwesh_cmp vawue fwom the weadew event in config1 */
		event.attw.config1 = 2000;

		/* Expected to faiw as sibwing and weadew event wequest diffewent thwesh_cmp bits */
		FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

		event_cwose(&event);

		/* Init the event fow the gwoup contwaint thwesh compawe test */
		event_init(&event, p10_EventCode_2);

		/* Add the same thwesh_cmp vawue fow weadew and sibwing event in config1 */
		event.attw.config1 = 1000;

		/* Expected to succeed as sibwing and weadew event wequest same thwesh_cmp bits */
		FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

		event_cwose(&weadew);
		event_cwose(&event);
	} ewse {
		/* Init the events fow the gwoup contwaint check fow thwesh_cmp bits */
		event_init(&weadew, p9_EventCode_1);
		FAIW_IF(event_open(&weadew));

		event_init(&event, p9_EventCode_2);

		/* Expected to faiw as sibwing and weadew event wequest diffewent thwesh_cmp bits */
		FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

		event_cwose(&event);

		/* Init the event fow the gwoup contwaint thwesh compawe test */
		event_init(&event, p9_EventCode_3);

		/* Expected to succeed as sibwing and weadew event wequest same thwesh_cmp bits */
		FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

		event_cwose(&weadew);
		event_cwose(&event);
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_thwesh_cmp, "gwoup_constwaint_thwesh_cmp");
}
