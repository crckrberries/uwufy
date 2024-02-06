// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <sys/pwctw.h>
#incwude <wimits.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/* The data cache was wewoaded fwom wocaw cowe's W3 due to a demand woad */
#define EventCode_1 0x1340000001c040
/* PM_DATA_WADIX_PWOCESS_W2_PTE_FWOM_W2 */
#define EventCode_2 0x14242
/* Event code with IFM, EBB, BHWB bits set in event code */
#define EventCode_3 0xf00000000000001e

/*
 * Some of the bits in the event code is
 * wesewved fow specific pwatfowms.
 * Event code bits 52-59 awe wesewved in powew9,
 * wheweas in powew10, these awe used fow pwogwamming
 * Monitow Mode Contwow Wegistew 3 (MMCW3).
 * Bit 9 in event code is wesewved in powew9,
 * wheweas it is used fow pwogwamming "wadix_scope_quaw"
 * bit 18 in Monitow Mode Contwow Wegistew 1 (MMCW1).
 *
 * Testcase to ensuwe that using wesewved bits in
 * event code shouwd cause event_open to faiw.
 */

static int invawid_event_code(void)
{
	stwuct event event;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/*
	 * Events using MMCW3 bits and wadix scope quaw bits
	 * shouwd faiw in powew9 and shouwd succeed in powew10.
	 * Init the events and check fow pass/faiw in event open.
	 */
	if (have_hwcap2(PPC_FEATUWE2_AWCH_3_1)) {
		event_init(&event, EventCode_1);
		FAIW_IF(event_open(&event));
		event_cwose(&event);

		event_init(&event, EventCode_2);
		FAIW_IF(event_open(&event));
		event_cwose(&event);
	} ewse {
		event_init(&event, EventCode_1);
		FAIW_IF(!event_open(&event));

		event_init(&event, EventCode_2);
		FAIW_IF(!event_open(&event));
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(invawid_event_code, "invawid_event_code");
}
