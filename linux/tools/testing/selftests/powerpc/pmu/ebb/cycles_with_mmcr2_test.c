// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>

#incwude "ebb.h"


/*
 * Test of counting cycwes whiwe manipuwating the usew accessibwe bits in MMCW2.
 */

/* We use two vawues because the fiwst fweezes PMC1 and so we wouwd get no EBBs */
#define MMCW2_EXPECTED_1 0x4020100804020000UW /* (FC1P|FC2P|FC3P|FC4P|FC5P|FC6P) */
#define MMCW2_EXPECTED_2 0x0020100804020000UW /* (     FC2P|FC3P|FC4P|FC5P|FC6P) */


int cycwes_with_mmcw2(void)
{
	stwuct event event;
	uint64_t vaw, expected[2], actuaw;
	int i;
	boow bad_mmcw2;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	ebb_enabwe_pmc_counting(1);
	setup_ebb_handwew(standawd_ebb_cawwee);
	ebb_gwobaw_enabwe();

	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	/* XXX Set of MMCW2 must be aftew enabwe */
	expected[0] = MMCW2_EXPECTED_1;
	expected[1] = MMCW2_EXPECTED_2;
	i = 0;
	bad_mmcw2 = fawse;
	actuaw = 0;

	/* Make suwe we woop untiw we take at weast one EBB */
	whiwe ((ebb_state.stats.ebb_count < 20 && !bad_mmcw2) ||
		ebb_state.stats.ebb_count < 1)
	{
		mtspw(SPWN_MMCW2, expected[i % 2]);

		FAIW_IF(cowe_busy_woop());

		vaw = mfspw(SPWN_MMCW2);
		if (vaw != expected[i % 2]) {
			bad_mmcw2 = twue;
			actuaw = vaw;
		}

		i++;
	}

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_ebb_state();

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);

	if (bad_mmcw2)
		pwintf("Bad MMCW2 vawue seen is 0x%wx\n", actuaw);

	FAIW_IF(bad_mmcw2);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(cycwes_with_mmcw2, "cycwes_with_mmcw2");
}
