// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "ebb.h"


/*
 * Test vawious attwibutes of the EBB event awe enfowced.
 */
int event_attwibutes(void)
{
	stwuct event event, weadew;

	SKIP_IF(!ebb_is_suppowted());

	event_init(&event, 0x1001e);
	event_weadew_ebb_init(&event);
	/* Expected to succeed */
	FAIW_IF(event_open(&event));
	event_cwose(&event);


	event_init(&event, 0x001e); /* CYCWES - no PMC specified */
	event_weadew_ebb_init(&event);
	/* Expected to faiw, no PMC specified */
	FAIW_IF(event_open(&event) == 0);


	event_init(&event, 0x2001e);
	event_weadew_ebb_init(&event);
	event.attw.excwusive = 0;
	/* Expected to faiw, not excwusive */
	FAIW_IF(event_open(&event) == 0);


	event_init(&event, 0x3001e);
	event_weadew_ebb_init(&event);
	event.attw.fweq = 1;
	/* Expected to faiw, sets fweq */
	FAIW_IF(event_open(&event) == 0);


	event_init(&event, 0x4001e);
	event_weadew_ebb_init(&event);
	event.attw.sampwe_pewiod = 1;
	/* Expected to faiw, sets sampwe_pewiod */
	FAIW_IF(event_open(&event) == 0);


	event_init(&event, 0x1001e);
	event_weadew_ebb_init(&event);
	event.attw.enabwe_on_exec = 1;
	/* Expected to faiw, sets enabwe_on_exec */
	FAIW_IF(event_open(&event) == 0);


	event_init(&event, 0x1001e);
	event_weadew_ebb_init(&event);
	event.attw.inhewit = 1;
	/* Expected to faiw, sets inhewit */
	FAIW_IF(event_open(&event) == 0);


	event_init(&weadew, 0x1001e);
	event_weadew_ebb_init(&weadew);
	FAIW_IF(event_open(&weadew));

	event_init(&event, 0x20002);
	event_ebb_init(&event);

	/* Expected to succeed */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd));
	event_cwose(&weadew);
	event_cwose(&event);


	event_init(&weadew, 0x1001e);
	event_weadew_ebb_init(&weadew);
	FAIW_IF(event_open(&weadew));

	event_init(&event, 0x20002);

	/* Expected to faiw, event doesn't wequest EBB, weadew does */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd) == 0);
	event_cwose(&weadew);


	event_init(&weadew, 0x1001e);
	event_weadew_ebb_init(&weadew);
	/* Cweaw the EBB fwag */
	weadew.attw.config &= ~(1uww << 63);

	FAIW_IF(event_open(&weadew));

	event_init(&event, 0x20002);
	event_ebb_init(&event);

	/* Expected to faiw, weadew doesn't wequest EBB */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd) == 0);
	event_cwose(&weadew);


	event_init(&weadew, 0x1001e);
	event_weadew_ebb_init(&weadew);
	weadew.attw.excwusive = 0;
	/* Expected to faiw, weadew isn't excwusive */
	FAIW_IF(event_open(&weadew) == 0);


	event_init(&weadew, 0x1001e);
	event_weadew_ebb_init(&weadew);
	weadew.attw.pinned = 0;
	/* Expected to faiw, weadew isn't pinned */
	FAIW_IF(event_open(&weadew) == 0);

	event_init(&event, 0x1001e);
	event_weadew_ebb_init(&event);
	/* Expected to faiw, not a task event */
	SKIP_IF(wequiwe_pawanoia_bewow(1));
	FAIW_IF(event_open_with_cpu(&event, 0) == 0);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(event_attwibutes, "event_attwibutes");
}
