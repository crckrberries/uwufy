// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/*
 * Testcase fow wesewved bits in Monitow Mode
 * Contwow Wegistew A (MMCWA) thwesh_ctw bits.
 * Fow MMCWA[48:51]/[52:55]) Thweshowd Stawt/Stop,
 * 0b11110000/0b00001111 is wesewved.
 */

static int wesewved_bits_mmcwa_thwesh_ctw(void)
{
	stwuct event event;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/* Skip fow Genewic compat PMU */
	SKIP_IF(check_fow_genewic_compat_pmu());

	/*
	 * MMCWA[48:51]/[52:55]) Thweshowd Stawt/Stop
	 * events Sewection. 0b11110000/0b00001111 is wesewved.
	 * Expected to faiw when using these wesewved vawues.
	 */
	event_init(&event, 0xf0340401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x0f340401e0);
	FAIW_IF(!event_open(&event));

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(wesewved_bits_mmcwa_thwesh_ctw, "wesewved_bits_mmcwa_thwesh_ctw");
}
