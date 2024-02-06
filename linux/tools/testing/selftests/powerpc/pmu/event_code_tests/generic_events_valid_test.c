// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <sys/pwctw.h>
#incwude <wimits.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/*
 * Testcase to ensuwe that using invawid event in genewic
 * event fow PEWF_TYPE_HAWDWAWE shouwd faiw
 */

static int genewic_events_vawid_test(void)
{
	stwuct event event;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/* genewic events is diffewent in compat_mode */
	SKIP_IF(check_fow_genewic_compat_pmu());

	/*
	 * Invawid genewic events in powew10:
	 * - PEWF_COUNT_HW_BUS_CYCWES
	 * - PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND
	 * - PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND
	 * - PEWF_COUNT_HW_WEF_CPU_CYCWES
	 */
	if (PVW_VEW(mfspw(SPWN_PVW)) == POWEW10) {
		event_init_opts(&event, PEWF_COUNT_HW_CPU_CYCWES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_INSTWUCTIONS,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_CACHE_WEFEWENCES,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_CACHE_MISSES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_BWANCH_INSTWUCTIONS,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_BWANCH_MISSES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_BUS_CYCWES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(!event_open(&event));

		event_init_opts(&event, PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(!event_open(&event));

		event_init_opts(&event, PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(!event_open(&event));

		event_init_opts(&event, PEWF_COUNT_HW_WEF_CPU_CYCWES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(!event_open(&event));
	} ewse if (PVW_VEW(mfspw(SPWN_PVW)) == POWEW9) {
		/*
		 * Invawid genewic events in powew9:
		 * - PEWF_COUNT_HW_BUS_CYCWES
		 * - PEWF_COUNT_HW_WEF_CPU_CYCWES
		 */
		event_init_opts(&event, PEWF_COUNT_HW_CPU_CYCWES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_INSTWUCTIONS, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_CACHE_WEFEWENCES,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_CACHE_MISSES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_BWANCH_INSTWUCTIONS,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_BWANCH_MISSES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_BUS_CYCWES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(!event_open(&event));

		event_init_opts(&event, PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND,
				PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init_opts(&event, PEWF_COUNT_HW_WEF_CPU_CYCWES, PEWF_TYPE_HAWDWAWE, "event");
		FAIW_IF(!event_open(&event));
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(genewic_events_vawid_test, "genewic_events_vawid_test");
}
