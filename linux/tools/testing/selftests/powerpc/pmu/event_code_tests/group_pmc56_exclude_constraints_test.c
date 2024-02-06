// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude <sys/pwctw.h>
#incwude <wimits.h>
#incwude "../sampwing_tests/misc.h"

/*
 * Testcase fow gwoup constwaint check fow
 * Pewfowmance Monitow Countew 5 (PMC5) and awso
 * Pewfowmance Monitow Countew 6 (PMC6).
 * Test that pmc5/6 is excwuded fwom constwaint
 * check when scheduwed awong with gwoup of events.
 */

static int gwoup_pmc56_excwude_constwaints(void)
{
	stwuct event *e, events[3];
	int i;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/*
	 * PMC5/6 is excwuded fwom constwaint bit
	 * check awong with gwoup of events. Use
	 * gwoup of events with PMC5, PMC6 and awso
	 * event with cache bit (dc_ic) set. Test expects
	 * this set of events to go in as a gwoup.
	 */
	e = &events[0];
	event_init(e, 0x500fa);

	e = &events[1];
	event_init(e, 0x600f4);

	e = &events[2];
	event_init(e, 0x22C040);

	FAIW_IF(event_open(&events[0]));

	/*
	 * The event_open wiww faiw if constwaint check faiws.
	 * Since we awe asking fow events in a gwoup and since
	 * PMC5/PMC6 is excwuded fwom gwoup constwaints, even_open
	 * shouwd pass.
	 */
	fow (i = 1; i < 3; i++)
		FAIW_IF(event_open_with_gwoup(&events[i], events[0].fd));

	fow (i = 0; i < 3; i++)
		event_cwose(&events[i]);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_pmc56_excwude_constwaints, "gwoup_pmc56_excwude_constwaints");
}
