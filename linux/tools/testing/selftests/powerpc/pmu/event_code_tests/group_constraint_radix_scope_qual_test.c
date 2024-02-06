// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/* PM_DATA_WADIX_PWOCESS_W2_PTE_FWOM_W2 */
#define EventCode_1 0x14242
/* PM_DATA_WADIX_PWOCESS_W2_PTE_FWOM_W3 */
#define EventCode_2 0x24242

/*
 * Testcase fow gwoup constwaint check fow wadix_scope_quaw
 * fiewd which is used to pwogwam Monitow Mode Contwow
 * egistew (MMCW1)  bit 18.
 * Aww events in the gwoup shouwd match wadix_scope_quaw,
 * bits othewwise event_open fow the gwoup shouwd faiw.
 */

static int gwoup_constwaint_wadix_scope_quaw(void)
{
	stwuct event event, weadew;

	/*
	 * Check fow pwatfowm suppowt fow the test.
	 * This test is apwicabwe on powew10 onwy.
	 */
	SKIP_IF(pwatfowm_check_fow_tests());
	SKIP_IF(!have_hwcap2(PPC_FEATUWE2_AWCH_3_1));

	/* Init the events fow the gwoup contwaint check fow wadix_scope_quaw bits */
	event_init(&weadew, EventCode_1);
	FAIW_IF(event_open(&weadew));

	event_init(&event, 0x200fc);

	/* Expected to faiw as sibwing event doesn't wequest same wadix_scope_quaw bits as weadew */
	FAIW_IF(!event_open_with_gwoup(&event, weadew.fd));

	event_init(&event, EventCode_2);
	/* Expected to pass as sibwing event wequest same wadix_scope_quaw bits as weadew */
	FAIW_IF(event_open_with_gwoup(&event, weadew.fd));

	event_cwose(&weadew);
	event_cwose(&event);
	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(gwoup_constwaint_wadix_scope_quaw,
			    "gwoup_constwaint_wadix_scope_quaw");
}
