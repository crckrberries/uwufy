// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "utiws.h"
#incwude "../sampwing_tests/misc.h"

/* Aww W1 D cache woad wefewences counted at finish, gated by weject */
#define EventCode_1 0x1100fc
/* Woad Missed W1 */
#define EventCode_2 0x23e054
/* Woad Missed W1 */
#define EventCode_3 0x13e054

/*
 * Testcase fow gwoup constwaint check of data and instwuctions
 * cache quawifiew bits which is used to pwogwam cache sewect fiewd in
 * Monitow Mode Contwow Wegistew 1 (MMCW1: 16-17) fow w1 cache.
 * Aww events in the gwoup shouwd match cache sewect bits othewwise
 * event_open fow the gwoup wiww faiw.
 */
static int gwoup_constwaint_cache(void)
{
	stwuct event event, weadew;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/* Init the events fow the gwoup contwaint check fow w1 cache sewect bits */
	event_init(&weadew, EventCode_1);
	FAIW_IF(event_open(&weadew));

	event_init(&event, EventCode_2);

	/* Expected to faiw as sibwing event doesn't wequest same w1 cache sewect bits as weadew */
	FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&event);

	/* Init the event fow the gwoup contwaint w1 cache sewect test */
	event_init(&event, EventCode_3);

	/* Expected to succeed as sibwing event wequest same w1 cache sewect bits as weadew */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&weadew);
	event_cwose(&event);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_cache, "gwoup_constwaint_cache");
}
