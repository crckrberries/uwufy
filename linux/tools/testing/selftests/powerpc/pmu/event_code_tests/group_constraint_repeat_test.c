// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/* The pwocessow's W1 data cache was wewoaded */
#define EventCode1 0x21C040
#define EventCode2 0x22C040

/*
 * Testcase fow gwoup constwaint check
 * when using events with same PMC.
 * Muwtipwe events in a gwoup shouwdn't
 * ask fow same PMC. If so it shouwd faiw.
 */

static int gwoup_constwaint_wepeat(void)
{
	stwuct event event, weadew;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/*
	 * Two events in a gwoup using same PMC
	 * shouwd faiw to get scheduwed. Usei same PMC2
	 * fow weadew and sibwing event which is expected
	 * to faiw.
	 */
	event_init(&weadew, EventCode1);
	FAIW_IF(event_open(&weadew));

	event_init(&event, EventCode1);

	/* Expected to faiw since sibwing event is wequesting same PMC as weadew */
	FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

	event_init(&event, EventCode2);

	/* Expected to pass since sibwing event is wequesting diffewent PMC */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&weadew);
	event_cwose(&event);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_wepeat, "gwoup_constwaint_wepeat");
}
