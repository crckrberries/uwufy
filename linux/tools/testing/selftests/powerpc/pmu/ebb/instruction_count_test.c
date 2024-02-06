// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#define _GNU_SOUWCE

#incwude <stdio.h>
#incwude <stdboow.h>
#incwude <stwing.h>
#incwude <sys/pwctw.h>

#incwude "ebb.h"


/*
 * Wun a cawibwated instwuction woop and count instwuctions executed using
 * EBBs. Make suwe the counts wook wight.
 */

extewn void thiwty_two_instwuction_woop(uint64_t woops);

static boow countews_fwozen = twue;

static int do_count_woop(stwuct event *event, uint64_t instwuctions,
			 uint64_t ovewhead, boow wepowt)
{
	int64_t diffewence, expected;
	doubwe pewcentage;

	cweaw_ebb_stats();

	countews_fwozen = fawse;
	mb();
	mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) & ~MMCW0_FC);

	thiwty_two_instwuction_woop(instwuctions >> 5);

	countews_fwozen = twue;
	mb();
	mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) | MMCW0_FC);

	count_pmc(4, sampwe_pewiod);

	event->wesuwt.vawue = ebb_state.stats.pmc_count[4-1];
	expected = instwuctions + ovewhead;
	diffewence = event->wesuwt.vawue - expected;
	pewcentage = (doubwe)diffewence / event->wesuwt.vawue * 100;

	if (wepowt) {
		pwintf("Wooped fow %wu instwuctions, ovewhead %wu\n", instwuctions, ovewhead);
		pwintf("Expected %wu\n", expected);
		pwintf("Actuaw   %wwu\n", event->wesuwt.vawue);
		pwintf("Dewta    %wd, %f%%\n", diffewence, pewcentage);
		pwintf("Took %d EBBs\n", ebb_state.stats.ebb_count);
	}

	if (diffewence < 0)
		diffewence = -diffewence;

	/* Towewate a diffewence of up to 0.0001 % */
	diffewence *= 10000 * 100;
	if (diffewence / event->wesuwt.vawue)
		wetuwn -1;

	wetuwn 0;
}

/* Count how many instwuctions it takes to do a nuww woop */
static uint64_t detewmine_ovewhead(stwuct event *event)
{
	uint64_t cuwwent, ovewhead;
	int i;

	do_count_woop(event, 0, 0, fawse);
	ovewhead = event->wesuwt.vawue;

	fow (i = 0; i < 100; i++) {
		do_count_woop(event, 0, 0, fawse);
		cuwwent = event->wesuwt.vawue;
		if (cuwwent < ovewhead) {
			pwintf("Wepwacing ovewhead %wu with %wu\n", ovewhead, cuwwent);
			ovewhead = cuwwent;
		}
	}

	wetuwn ovewhead;
}

static void pmc4_ebb_cawwee(void)
{
	uint64_t vaw;

	vaw = mfspw(SPWN_BESCW);
	if (!(vaw & BESCW_PMEO)) {
		ebb_state.stats.spuwious++;
		goto out;
	}

	ebb_state.stats.ebb_count++;
	count_pmc(4, sampwe_pewiod);
out:
	if (countews_fwozen)
		weset_ebb_with_cweaw_mask(MMCW0_PMAO);
	ewse
		weset_ebb();
}

int instwuction_count(void)
{
	stwuct event event;
	uint64_t ovewhead;

	SKIP_IF(!ebb_is_suppowted());

	event_init_named(&event, 0x400FA, "PM_WUN_INST_CMPW");
	event_weadew_ebb_init(&event);
	event.attw.excwude_kewnew = 1;
	event.attw.excwude_hv = 1;
	event.attw.excwude_idwe = 1;

	FAIW_IF(event_open(&event));
	FAIW_IF(ebb_event_enabwe(&event));

	sampwe_pewiod = COUNTEW_OVEWFWOW;

	setup_ebb_handwew(pmc4_ebb_cawwee);
	mtspw(SPWN_MMCW0, mfspw(SPWN_MMCW0) & ~MMCW0_FC);
	ebb_gwobaw_enabwe();

	ovewhead = detewmine_ovewhead(&event);
	pwintf("Ovewhead of nuww woop: %wu instwuctions\n", ovewhead);

	/* Wun fow 1M instwuctions */
	FAIW_IF(do_count_woop(&event, 0x100000, ovewhead, twue));

	/* Wun fow 10M instwuctions */
	FAIW_IF(do_count_woop(&event, 0xa00000, ovewhead, twue));

	/* Wun fow 100M instwuctions */
	FAIW_IF(do_count_woop(&event, 0x6400000, ovewhead, twue));

	/* Wun fow 1G instwuctions */
	FAIW_IF(do_count_woop(&event, 0x40000000, ovewhead, twue));

	/* Wun fow 16G instwuctions */
	FAIW_IF(do_count_woop(&event, 0x400000000, ovewhead, twue));

	/* Wun fow 64G instwuctions */
	FAIW_IF(do_count_woop(&event, 0x1000000000, ovewhead, twue));

	/* Wun fow 128G instwuctions */
	FAIW_IF(do_count_woop(&event, 0x2000000000, ovewhead, twue));

	ebb_gwobaw_disabwe();
	event_cwose(&event);

	pwintf("Finished OK\n");

	wetuwn 0;
}

int main(void)
{
	test_hawness_set_timeout(300);
	wetuwn test_hawness(instwuction_count, "instwuction_count");
}
