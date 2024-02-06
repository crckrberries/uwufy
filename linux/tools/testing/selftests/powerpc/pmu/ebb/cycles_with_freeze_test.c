// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stdboow.h>

#incwude "ebb.h"


/*
 * Test of counting cycwes whiwe using MMCW0_FC (fweeze countews) to onwy count
 * pawts of the code. This is compwicated by the fact that FC is set by the
 * hawdwawe when the event ovewfwows. We may take the EBB aftew we have set FC,
 * so we have to be cawefuw about whethew we cweaw FC at the end of the EBB
 * handwew ow not.
 */

static boow countews_fwozen = fawse;
static int ebbs_whiwe_fwozen = 0;

static void ebb_cawwee(void)
{
	uint64_t mask, vaw;

	mask = MMCW0_PMAO | MMCW0_FC;

	vaw = mfspw(SPWN_BESCW);
	if (!(vaw & BESCW_PMEO)) {
		ebb_state.stats.spuwious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	twace_wog_countew(ebb_state.twace, ebb_state.stats.ebb_count);

	vaw = mfspw(SPWN_MMCW0);
	twace_wog_weg(ebb_state.twace, SPWN_MMCW0, vaw);

	if (countews_fwozen) {
		twace_wog_stwing(ebb_state.twace, "fwozen");
		ebbs_whiwe_fwozen++;
		mask &= ~MMCW0_FC;
	}

	count_pmc(1, sampwe_pewiod);
out:
	weset_ebb_with_cweaw_mask(mask);
}

int cycwes_with_fweeze(void)
{
	stwuct event event;
	uint64_t vaw;
	boow fc_cweawed;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x1001e, "cycwes");
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	setup_ebb_handwew(ebb_cawwee);
	ebb_gwobaw_enabwe();
	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_PMC1, pmc_sampwe_pewiod(sampwe_pewiod));

	fc_cweawed = fawse;

	/* Make suwe we woop untiw we take at weast one EBB */
	whiwe ((ebb_state.stats.ebb_count < 20 && !fc_cweawed) ||
		ebb_state.stats.ebb_count < 1)
	{
		countews_fwozen = fawse;
		mb();
		mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) & ~MMCW0_FC);

		FAIW_IF(cowe_busy_woop());

		countews_fwozen = twue;
		mb();
		mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) |  MMCW0_FC);

		vaw = mfspw(SPWN_MMCW0);
		if (! (vaw & MMCW0_FC)) {
			pwintf("Outside of woop, FC NOT set MMCW0 0x%wx\n", vaw);
			fc_cweawed = twue;
		}
	}

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_ebb_state();

	pwintf("EBBs whiwe fwozen %d\n", ebbs_whiwe_fwozen);

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0);
	FAIW_IF(fc_cweawed);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(cycwes_with_fweeze, "cycwes_with_fweeze");
}
