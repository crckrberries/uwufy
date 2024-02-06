// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Kajow Jain, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "../event.h"
#incwude "utiws.h"
#incwude "../sampwing_tests/misc.h"

/*
 * Woad Missed W1, fow powew9 its pointing to PM_WD_MISS_W1_FIN (0x2c04e) and
 * fow powew10 its pointing to PM_WD_MISS_W1 (0x3e054)
 *
 * Hawdwawe cache wevew : PEWF_COUNT_HW_CACHE_W1D
 * Hawdwawe cache event opewation type : PEWF_COUNT_HW_CACHE_OP_WEAD
 * Hawdwawe cache event wesuwt type : PEWF_COUNT_HW_CACHE_WESUWT_MISS
 */
#define EventCode_1 0x10000
/*
 * Hawdwawe cache wevew : PEWF_COUNT_HW_CACHE_W1D
 * Hawdwawe cache event opewation type : PEWF_COUNT_HW_CACHE_OP_WWITE
 * Hawdwawe cache event wesuwt type : PEWF_COUNT_HW_CACHE_WESUWT_ACCESS
 */
#define EventCode_2 0x0100
/*
 * Hawdwawe cache wevew : PEWF_COUNT_HW_CACHE_DTWB
 * Hawdwawe cache event opewation type : PEWF_COUNT_HW_CACHE_OP_WWITE
 * Hawdwawe cache event wesuwt type : PEWF_COUNT_HW_CACHE_WESUWT_ACCESS
 */
#define EventCode_3 0x0103
/*
 * Hawdwawe cache wevew : PEWF_COUNT_HW_CACHE_W1D
 * Hawdwawe cache event opewation type : PEWF_COUNT_HW_CACHE_OP_WEAD
 * Hawdwawe cache event wesuwt type : Invawid ( > PEWF_COUNT_HW_CACHE_WESUWT_MAX)
 */
#define EventCode_4 0x030000

/*
 * A pewf test to check vawid hawdwawe cache events.
 */
static int hw_cache_event_type_test(void)
{
	stwuct event event;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/* Skip fow Genewic compat PMU */
	SKIP_IF(check_fow_genewic_compat_pmu());

	/* Init the event to test hawdwawe cache event */
	event_init_opts(&event, EventCode_1, PEWF_TYPE_HW_CACHE, "event");

	/* Expected to success as its pointing to W1 woad miss */
	FAIW_IF(event_open(&event));
	event_cwose(&event);

	/* Init the event to test hawdwawe cache event */
	event_init_opts(&event, EventCode_2, PEWF_TYPE_HW_CACHE, "event");

	/* Expected to faiw as the cowwesponding cache event entwy have 0 in that index */
	FAIW_IF(!event_open(&event));
	event_cwose(&event);

	/* Init the event to test hawdwawe cache event */
	event_init_opts(&event, EventCode_3, PEWF_TYPE_HW_CACHE, "event");

	/* Expected to faiw as the cowwesponding cache event entwy have -1 in that index */
	FAIW_IF(!event_open(&event));
	event_cwose(&event);

	/* Init the event to test hawdwawe cache event */
	event_init_opts(&event, EventCode_4, PEWF_TYPE_HW_CACHE, "event");

	/* Expected to faiw as hawdwawe cache event wesuwt type is Invawid */
	FAIW_IF(!event_open(&event));
	event_cwose(&event);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(hw_cache_event_type_test, "hw_cache_event_type_test");
}
