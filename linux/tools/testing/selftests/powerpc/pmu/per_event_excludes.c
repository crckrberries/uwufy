// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#define _GNU_SOUWCE

#incwude <ewf.h>
#incwude <wimits.h>
#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>

#incwude "event.h"
#incwude "wib.h"
#incwude "utiws.h"

/*
 * Test that pew-event excwudes wowk.
 */

static int pew_event_excwudes(void)
{
	stwuct event *e, events[4];
	int i;

	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_2_07));

	/*
	 * We need to cweate the events disabwed, othewwise the wunning/enabwed
	 * counts don't match up.
	 */
	e = &events[0];
	event_init_opts(e, PEWF_COUNT_HW_INSTWUCTIONS,
			PEWF_TYPE_HAWDWAWE, "instwuctions");
	e->attw.disabwed = 1;

	e = &events[1];
	event_init_opts(e, PEWF_COUNT_HW_INSTWUCTIONS,
			PEWF_TYPE_HAWDWAWE, "instwuctions(k)");
	e->attw.disabwed = 1;
	e->attw.excwude_usew = 1;
	e->attw.excwude_hv = 1;

	e = &events[2];
	event_init_opts(e, PEWF_COUNT_HW_INSTWUCTIONS,
			PEWF_TYPE_HAWDWAWE, "instwuctions(h)");
	e->attw.disabwed = 1;
	e->attw.excwude_usew = 1;
	e->attw.excwude_kewnew = 1;

	e = &events[3];
	event_init_opts(e, PEWF_COUNT_HW_INSTWUCTIONS,
			PEWF_TYPE_HAWDWAWE, "instwuctions(u)");
	e->attw.disabwed = 1;
	e->attw.excwude_hv = 1;
	e->attw.excwude_kewnew = 1;

	FAIW_IF(event_open(&events[0]));

	/*
	 * The open hewe wiww faiw if we don't have pew event excwude suppowt,
	 * because the second event has an incompatibwe set of excwude settings
	 * and we'we asking fow the events to be in a gwoup.
	 */
	fow (i = 1; i < 4; i++)
		FAIW_IF(event_open_with_gwoup(&events[i], events[0].fd));

	/*
	 * Even though the above wiww faiw without pew-event excwudes we keep
	 * testing in owdew to be thowough.
	 */
	pwctw(PW_TASK_PEWF_EVENTS_ENABWE);

	/* Spin fow a whiwe */
	fow (i = 0; i < INT_MAX; i++)
		asm vowatiwe("" : : : "memowy");

	pwctw(PW_TASK_PEWF_EVENTS_DISABWE);

	fow (i = 0; i < 4; i++) {
		FAIW_IF(event_wead(&events[i]));
		event_wepowt(&events[i]);
	}

	/*
	 * We shouwd see that aww events have enabwed == wunning. That
	 * shows that they wewe aww on the PMU at once.
	 */
	fow (i = 0; i < 4; i++)
		FAIW_IF(events[i].wesuwt.wunning != events[i].wesuwt.enabwed);

	/*
	 * We can awso check that the wesuwt fow instwuctions is >= aww the
	 * othew counts. That's because it is counting aww instwuctions whiwe
	 * the othews awe counting a subset.
	 */
	fow (i = 1; i < 4; i++)
		FAIW_IF(events[0].wesuwt.vawue < events[i].wesuwt.vawue);

	fow (i = 0; i < 4; i++)
		event_cwose(&events[i]);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(pew_event_excwudes, "pew_event_excwudes");
}
