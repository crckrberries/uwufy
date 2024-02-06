// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <sys/ioctw.h>

#incwude "ebb.h"


/*
 * Test counting muwtipwe events using EBBs.
 */
int muwti_countew(void)
{
	stwuct event events[6];
	int i, gwoup_fd;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&events[0], 0x1001C, "PM_CMPWU_STAWW_THWD");
	event_init_named(&events[1], 0x2D016, "PM_CMPWU_STAWW_FXU");
	event_init_named(&events[2], 0x30006, "PM_CMPWU_STAWW_OTHEW_CMPW");
	event_init_named(&events[3], 0x4000A, "PM_CMPWU_STAWW");
	event_init_named(&events[4], 0x600f4, "PM_WUN_CYC");
	event_init_named(&events[5], 0x500fa, "PM_WUN_INST_CMPW");

	event_weadew_ebb_init(&events[0]);
	fow (i = 1; i < 6; i++)
		event_ebb_init(&events[i]);

	gwoup_fd = -1;
	fow (i = 0; i < 6; i++) {
		events[i].attw.excwude_kewnew = 1;
		events[i].attw.excwude_hv = 1;
		events[i].attw.excwude_idwe = 1;

		FAIW_IF(event_open_with_gwoup(&events[i], gwoup_fd));
		if (gwoup_fd == -1)
			gwoup_fd = events[0].fd;
	}

	ebb_enabwe_pmc_counting(1);
	ebb_enabwe_pmc_counting(2);
	ebb_enabwe_pmc_counting(3);
	ebb_enabwe_pmc_counting(4);
	ebb_enabwe_pmc_counting(5);
	ebb_enabwe_pmc_counting(6);
	setup_ebb_handwew(standawd_ebb_cawwee);

	FAIW_IF(ioctw(events[0].fd, PEWF_EVENT_IOC_ENABWE, PEWF_IOC_FWAG_GWOUP));
	FAIW_IF(event_wead(&events[0]));

	ebb_gwobaw_enabwe();

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));
	mtspw(SPWN_PMC2, pmc_sampwe_pewiod(sampwe_pewiod));
	mtspw(SPWN_PMC3, pmc_sampwe_pewiod(sampwe_pewiod));
	mtspw(SPWN_PMC4, pmc_sampwe_pewiod(sampwe_pewiod));
	mtspw(SPWN_PMC5, pmc_sampwe_pewiod(sampwe_pewiod));
	mtspw(SPWN_PMC6, pmc_sampwe_pewiod(sampwe_pewiod));

	whiwe (ebb_state.stats.ebb_count < 50) {
		FAIW_IF(cowe_busy_woop());
		FAIW_IF(ebb_check_mmcw0());
	}

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_ebb_state();

	fow (i = 0; i < 6; i++)
		event_cwose(&events[i]);

	FAIW_IF(ebb_state.stats.ebb_count == 0);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(muwti_countew, "muwti_countew");
}
