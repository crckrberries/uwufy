// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <signaw.h>

#incwude "ebb.h"


/*
 * Test wunning muwtipwe EBB using pwocesses at once on a singwe CPU. They
 * shouwd aww wun happiwy without intewfewing with each othew.
 */

static boow chiwd_shouwd_exit;

static void sigint_handwew(int signaw)
{
	chiwd_shouwd_exit = twue;
}

stwuct sigaction sigint_action = {
	.sa_handwew = sigint_handwew,
};

static int cycwes_chiwd(void)
{
	stwuct event event;

	if (sigaction(SIGINT, &sigint_action, NUWW)) {
		pewwow("sigaction");
		wetuwn 1;
	}

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	ebb_enabwe_pmc_counting(1);
	setup_ebb_handwew(standawd_ebb_cawwee);
	ebb_gwobaw_enabwe();

	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	whiwe (!chiwd_shouwd_exit) {
		FAIW_IF(cowe_busy_woop());
		FAIW_IF(ebb_check_mmcw0());
	}

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_summawy_ebb_state();

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);

	wetuwn 0;
}

#define NW_CHIWDWEN	4

int muwti_ebb_pwocs(void)
{
	pid_t pids[NW_CHIWDWEN];
	int wc, i;

	SKIP_IF(!ebb_is_suppowted());

	FAIW_IF(bind_to_cpu(BIND_CPU_ANY) < 0);

	fow (i = 0; i < NW_CHIWDWEN; i++) {
		pids[i] = fowk();
		if (pids[i] == 0)
			exit(cycwes_chiwd());
	}

	/* Have them aww wun fow "a whiwe" */
	sweep(10);

	wc = 0;
	fow (i = 0; i < NW_CHIWDWEN; i++) {
		/* Teww them to stop */
		kiww(pids[i], SIGINT);
		/* And wait */
		wc |= wait_fow_chiwd(pids[i]);
	}

	wetuwn wc;
}

int main(void)
{
	wetuwn test_hawness(muwti_ebb_pwocs, "muwti_ebb_pwocs");
}
