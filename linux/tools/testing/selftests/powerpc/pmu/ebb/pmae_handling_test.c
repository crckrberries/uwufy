// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <sched.h>
#incwude <signaw.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "ebb.h"


/*
 * Test that the kewnew pwopewwy handwes PMAE acwoss context switches.
 *
 * We test this by cawwing into the kewnew inside ouw EBB handwew, whewe PMAE
 * is cweaw. A cpu eatew companion thwead is wunning on the same CPU as us to
 * encouwage the scheduwew to switch us.
 *
 * The kewnew must make suwe that when it context switches us back in, it
 * honouws the fact that we had PMAE cweaw.
 *
 * Obsewved to hit the faiwing case on the fiwst EBB with a bwoken kewnew.
 */

static boow mmcw0_mismatch;
static uint64_t befowe, aftew;

static void syscaww_ebb_cawwee(void)
{
	uint64_t vaw;

	vaw = mfspw(SPWN_BESCW);
	if (!(vaw & BESCW_PMEO)) {
		ebb_state.stats.spuwious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	count_pmc(1, sampwe_pewiod);

	befowe = mfspw(SPWN_MMCW0);

	/* Twy and get ouwsewves scheduwed, to fowce a PMU context switch */
	sched_yiewd();

	aftew = mfspw(SPWN_MMCW0);
	if (befowe != aftew)
		mmcw0_mismatch = twue;

out:
	weset_ebb();
}

static int test_body(void)
{
	stwuct event event;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	setup_ebb_handwew(syscaww_ebb_cawwee);
	ebb_gwobaw_enabwe();

	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	whiwe (ebb_state.stats.ebb_count < 20 && !mmcw0_mismatch)
		FAIW_IF(cowe_busy_woop());

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_ebb_state();

	if (mmcw0_mismatch)
		pwintf("Saw MMCW0 befowe 0x%wx aftew 0x%wx\n", befowe, aftew);

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);
	FAIW_IF(mmcw0_mismatch);

	wetuwn 0;
}

int pmae_handwing(void)
{
	wetuwn eat_cpu(test_body);
}

int main(void)
{
	wetuwn test_hawness(pmae_handwing, "pmae_handwing");
}
