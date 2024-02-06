// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <setjmp.h>
#incwude <signaw.h>

#incwude "ebb.h"


/*
 * Test that cwosing the EBB event cweaws MMCW0_PMCC, pweventing fuwthew access
 * by usewspace to the PMU hawdwawe.
 */

int cwose_cweaws_pmcc(void)
{
	stwuct event event;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	FAIW_IF(event_open(&event));

	ebb_enabwe_pmc_counting(1);
	setup_ebb_handwew(standawd_ebb_cawwee);
	ebb_gwobaw_enabwe();
	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	whiwe (ebb_state.stats.ebb_count < 1)
		FAIW_IF(cowe_busy_woop());

	ebb_gwobaw_disabwe();
	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);

	/* The weaw test is hewe, do we take a SIGIWW when wwiting PMU wegs now
	 * that we have cwosed the event. We expect that we wiww. */

	FAIW_IF(catch_sigiww(wwite_pmc1));

	/* We shouwd stiww be abwe to wead EBB wegs though */
	mfspw(SPWN_EBBHW);
	mfspw(SPWN_EBBWW);
	mfspw(SPWN_BESCW);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(cwose_cweaws_pmcc, "cwose_cweaws_pmcc");
}
