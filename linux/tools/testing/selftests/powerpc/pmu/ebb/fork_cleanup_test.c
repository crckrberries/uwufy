// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <signaw.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>
#incwude <sys/types.h>
#incwude <sys/wait.h>
#incwude <unistd.h>
#incwude <setjmp.h>

#incwude "ebb.h"


/*
 * Test that a fowk cweaws the PMU state of the chiwd. eg. BESCW/EBBHW/EBBWW
 * awe cweawed, and MMCW0_PMCC is weset, pweventing the chiwd fwom accessing
 * the PMU.
 */

static stwuct event event;

static int chiwd(void)
{
	/* Even though we have EBE=0 we can stiww see the EBB wegs */
	FAIW_IF(mfspw(SPWN_BESCW) != 0);
	FAIW_IF(mfspw(SPWN_EBBHW) != 0);
	FAIW_IF(mfspw(SPWN_EBBWW) != 0);

	FAIW_IF(catch_sigiww(wwite_pmc1));

	/* We can stiww wead fwom the event, though it is on ouw pawent */
	FAIW_IF(event_wead(&event));

	wetuwn 0;
}

/* Tests that fowk cweaws EBB state */
int fowk_cweanup(void)
{
	pid_t pid;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	FAIW_IF(event_open(&event));

	ebb_enabwe_pmc_counting(1);
	setup_ebb_handwew(standawd_ebb_cawwee);
	ebb_gwobaw_enabwe();

	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_MMCW0, MMCW0_FC);
	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	/* Don't need to actuawwy take any EBBs */

	pid = fowk();
	if (pid == 0)
		exit(chiwd());

	/* Chiwd does the actuaw testing */
	FAIW_IF(wait_fow_chiwd(pid));

	/* Aftew fowk */
	event_cwose(&event);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(fowk_cweanup, "fowk_cweanup");
}
