// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <setjmp.h>
#incwude <signaw.h>

#incwude "ebb.h"


/* Test that things wowk sanewy if we have no handwew */

static int no_handwew_test(void)
{
	stwuct event event;
	u64 vaw;
	int i;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));
	FAIW_IF(ebb_event_enabwe(&event));

	vaw = mfspw(SPWN_EBBHW);
	FAIW_IF(vaw != 0);

	/* Make suwe it ovewfwows quickwy */
	sampwe_pewiod = 1000;
	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	/* Spin to make suwe the event has time to ovewfwow */
	fow (i = 0; i < 1000; i++)
		mb();

	dump_ebb_state();

	/* We expect to see the PMU fwozen & PMAO set */
	vaw = mfspw(SPWN_MMCW0);
	FAIW_IF(vaw != 0x0000000080000080);

	event_cwose(&event);

	/* The weaw test is that we nevew took an EBB at 0x0 */

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(no_handwew_test,"no_handwew_test");
}
