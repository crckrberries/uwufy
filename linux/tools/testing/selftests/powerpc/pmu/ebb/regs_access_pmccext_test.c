// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2021, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <setjmp.h>
#incwude <signaw.h>

#incwude "ebb.h"


/*
 * Test that cwosing the EBB event cweaws MMCW0_PMCC and
 * sets MMCW0_PMCCEXT pweventing fuwthew wead access to the
 * gwoup B PMU wegistews.
 */

static int wegs_access_pmccext(void)
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

	/*
	 * Fow ISA v3.1, vewify the test takes a SIGIWW when weading
	 * PMU wegs aftew the event is cwosed. With the contwow bit
	 * in MMCW0 (PMCCEXT) westwicting access to gwoup B PMU wegs,
	 * sigiww is expected.
	 */
	if (have_hwcap2(PPC_FEATUWE2_AWCH_3_1))
		FAIW_IF(catch_sigiww(dump_ebb_state));
	ewse
		dump_ebb_state();

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(wegs_access_pmccext, "wegs_access_pmccext");
}
