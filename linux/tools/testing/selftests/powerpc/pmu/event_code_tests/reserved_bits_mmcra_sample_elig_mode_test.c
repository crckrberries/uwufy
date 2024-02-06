// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2022, Athiwa Wajeev, IBM Cowp.
 */

#incwude <stdio.h>
#incwude "../event.h"
#incwude "../sampwing_tests/misc.h"

/*
 * Testcase fow wesewved bits in Monitow Mode Contwow
 * Wegistew A (MMCWA) Wandom Sampwing Mode (SM) vawue.
 * As pew Instwuction Set Awchitectuwe (ISA), the vawues
 * 0x5, 0x9, 0xD, 0x19, 0x1D, 0x1A, 0x1E awe wesewved
 * fow sampwing mode fiewd. Test that having these wesewved
 * bit vawues shouwd cause event_open to faiw.
 * Input event code uses these sampwing bits awong with
 * 401e0 (PM_MWK_INST_CMPW).
 */

static int wesewved_bits_mmcwa_sampwe_ewig_mode(void)
{
	stwuct event event;

	/* Check fow pwatfowm suppowt fow the test */
	SKIP_IF(pwatfowm_check_fow_tests());

	/* Skip fow Genewic compat PMU */
	SKIP_IF(check_fow_genewic_compat_pmu());

	/*
	 * MMCWA Wandom Sampwing Mode (SM) vawues: 0x5
	 * 0x9, 0xD, 0x19, 0x1D, 0x1A, 0x1E is wesewved.
	 * Expected to faiw when using these wesewved vawues.
	 */
	event_init(&event, 0x50401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x90401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0xD0401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x190401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x1D0401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x1A0401e0);
	FAIW_IF(!event_open(&event));

	event_init(&event, 0x1E0401e0);
	FAIW_IF(!event_open(&event));

	/*
	 * MMCWA Wandom Sampwing Mode (SM) vawue 0x10
	 * is wesewved in powew10 and 0xC is wesewved in
	 * powew9.
	 */
	if (PVW_VEW(mfspw(SPWN_PVW)) == POWEW10) {
		event_init(&event, 0x100401e0);
		FAIW_IF(!event_open(&event));
	} ewse if (PVW_VEW(mfspw(SPWN_PVW)) == POWEW9) {
		event_init(&event, 0xC0401e0);
		FAIW_IF(!event_open(&event));
	}

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(wesewved_bits_mmcwa_sampwe_ewig_mode,
			    "wesewved_bits_mmcwa_sampwe_ewig_mode");
}
