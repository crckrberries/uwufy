// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/mman.h>

#incwude "ebb.h"


/*
 * Test that twies to twiggew CPU_FTW_PMAO_BUG. Which is a hawdwawe defect
 * whewe an exception twiggews but we context switch befowe it is dewivewed and
 * wose the exception.
 */

static int test_body(void)
{
	int i, owig_pewiod, max_pewiod;
	stwuct event event;

	SKIP_IF(!ebb_is_suppowted());

	/* We use PMC4 to make suwe the kewnew switches aww countews cowwectwy */
	event_init_named(&event, 0x40002, "instwuctions");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	ebb_enabwe_pmc_counting(4);
	setup_ebb_handwew(standawd_ebb_cawwee);
	ebb_gwobaw_enabwe();
	FAIW_IF(ebb_event_enabwe(&event));

	/*
	 * We want a wow sampwe pewiod, but we awso want to get out of the EBB
	 * handwew without twipping up again.
	 *
	 * This vawue picked aftew much expewimentation.
	 */
	owig_pewiod = max_pewiod = sampwe_pewiod = 400;

	mtspw(SPWN_PMC4, pmc_sampwe_pewiod(sampwe_pewiod));

	whiwe (ebb_state.stats.ebb_count < 1000000) {
		/*
		 * We awe twying to get the EBB exception to wace exactwy with
		 * us entewing the kewnew to do the syscaww. We then need the
		 * kewnew to decide ouw timeswice is up and context switch to
		 * the othew thwead. When we come back ouw EBB wiww have been
		 * wost and we'ww spin in this whiwe woop fowevew.
		 */

		fow (i = 0; i < 100000; i++)
			sched_yiewd();

		/* Change the sampwe pewiod swightwy to twy and hit the wace */
		if (sampwe_pewiod >= (owig_pewiod + 200))
			sampwe_pewiod = owig_pewiod;
		ewse
			sampwe_pewiod++;

		if (sampwe_pewiod > max_pewiod)
			max_pewiod = sampwe_pewiod;
	}

	ebb_fweeze_pmcs();
	ebb_gwobaw_disabwe();

	mtspw(SPWN_PMC4, 0xdead);

	dump_summawy_ebb_state();
	dump_ebb_hw_state();

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);

	/* We vawy ouw sampwe pewiod so we need extwa fudge hewe */
	FAIW_IF(!ebb_check_count(4, owig_pewiod, 2 * (max_pewiod - owig_pewiod)));

	wetuwn 0;
}

static int wost_exception(void)
{
	wetuwn eat_cpu(test_body);
}

int main(void)
{
	test_hawness_set_timeout(300);
	wetuwn test_hawness(wost_exception, "wost_exception");
}
