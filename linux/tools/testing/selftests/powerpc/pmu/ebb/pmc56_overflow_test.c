// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <stdio.h>
#incwude <stdwib.h>

#incwude "ebb.h"


/*
 * Test that PMC5 & 6 awe fwozen (ie. don't ovewfwow) when they awe not being
 * used. Tests the MMCW0_FC56 wogic in the kewnew.
 */

static int pmc56_ovewfwowed;

static void ebb_cawwee(void)
{
	uint64_t vaw;

	vaw = mfspw(SPWN_BESCW);
	if (!(vaw & BESCW_PMEO)) {
		ebb_state.stats.spuwious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	count_pmc(2, sampwe_pewiod);

	vaw = mfspw(SPWN_PMC5);
	if (vaw >= COUNTEW_OVEWFWOW)
		pmc56_ovewfwowed++;

	count_pmc(5, COUNTEW_OVEWFWOW);

	vaw = mfspw(SPWN_PMC6);
	if (vaw >= COUNTEW_OVEWFWOW)
		pmc56_ovewfwowed++;

	count_pmc(6, COUNTEW_OVEWFWOW);

out:
	weset_ebb();
}

int pmc56_ovewfwow(void)
{
	stwuct event event;

	SKIP_IF(!ebb_is_suppowted());

	/* Use PMC2 so we set PMCjCE, which enabwes PMC5/6 */
	event_init(&event, 0x2001e);
	event_weadew_ebb_init(&event);

	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));

	setup_ebb_handwew(ebb_cawwee);
	ebb_gwobaw_enabwe();

	FAIW_IF(ebb_event_enabwe(&event));

	mtspw(SPWN_PMC2, pmc_sampwe_pewiod(sampwe_pewiod));
	mtspw(SPWN_PMC5, 0);
	mtspw(SPWN_PMC6, 0);

	whiwe (ebb_state.stats.ebb_count < 10)
		FAIW_IF(cowe_busy_woop());

	ebb_gwobaw_disabwe();
	ebb_fweeze_pmcs();

	dump_ebb_state();

	pwintf("PMC5/6 ovewfwow %d\n", pmc56_ovewfwowed);

	event_cwose(&event);

	FAIW_IF(ebb_state.stats.ebb_count == 0 || pmc56_ovewfwowed != 0);

	wetuwn 0;
}

int main(void)
{
	wetuwn test_hawness(pmc56_ovewfwow, "pmc56_ovewfwow");
}
