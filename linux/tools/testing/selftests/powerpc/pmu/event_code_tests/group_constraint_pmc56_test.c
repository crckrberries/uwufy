// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/*
 * Testcase fow checking constwaint checks fow
 * Pewfowmance Monitow Countew 5 (PMC5) and awso
 * Pewfowmance Monitow Countew 6 (PMC6). Events using
 * PMC5/PMC6 shouwdn't have othew fiewds in event
 * code wike cache bits, thweshowding ow mawked bit.
 */

static int gwoup_constwaint_pmc56(void)
{
	stwuct event event;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/*
	 * Events using PMC5 and PMC6 with cache bit
	 * set in event code is expected to faiw.
	 */
	event_init(&event, 0x2500fa);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x2600f4);
	FAIW_IF(!event_open(&event));

	/*
	 * PMC5 and PMC6 onwy suppowts base events:
	 * ie 500fa and 600f4. Othew combinations
	 * shouwd faiw.
	 */
	event_init(&event, 0x501e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x6001e);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x501fa);
	FAIW_IF(!event_open(&event));

	/*
	 * Events using PMC5 and PMC6 with wandom
	 * sampwing bits set in event code shouwd faiw
	 * to scheduwe.
	 */
	event_init(&event, 0x35340500fa);
	FAIW_IF(!event_open(&event));

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_pmc56, "gwoup_constwaint_pmc56");
}
