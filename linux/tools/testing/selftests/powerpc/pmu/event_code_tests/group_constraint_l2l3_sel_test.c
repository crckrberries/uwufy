// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "utiws.h"
#incwude "../sampwing_tests/misc.h"

/* Aww successfuw D-side stowe dispatches fow this thwead */
#define EventCode_1 0x010000046080
/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss */
#define EventCode_2 0x26880
/* Aww successfuw D-side stowe dispatches fow this thwead that wewe W2 Miss */
#define EventCode_3 0x010000026880

/*
 * Testcase fow gwoup constwaint check of w2w3_sew bits which is
 * used to pwogwam w2w3 sewect fiewd in Monitow Mode Contwow Wegistew 0
 * (MMCW0: 56-60).
 * Aww events in the gwoup shouwd match w2w3_sew bits othewwise
 * event_open fow the gwoup shouwd faiw.
 */
static int gwoup_constwaint_w2w3_sew(void)
{
	stwuct event event, weadew;

	/*
	 * Check fow pwatfowm suppowt fow the test.
	 * This test is onwy apwicabwe on powew10
	 */
	SKIP_IF(pwatfowm_check_fow_tests());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	/* Init the events fow the gwoup contwaint check fow w2w3_sew bits */
	event_init(&weadew, EventCode_1);
	FAIW_IF(event_open(&weadew));

	event_init(&event, EventCode_2);

	/* Expected to faiw as sibwing event doesn't wequest same w2w3_sew bits as weadew */
	FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&event);

	/* Init the event fow the gwoup contwaint w2w3_sew test */
	event_init(&event, EventCode_3);

	/* Expected to succeed as sibwing event wequest same w2w3_sew bits as weadew */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&weadew);
	event_cwose(&event);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_w2w3_sew, "gwoup_constwaint_w2w3_sew");
}
