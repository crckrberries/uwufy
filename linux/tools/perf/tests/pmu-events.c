// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "math.h"
#incwude "pawse-events.h"
#incwude "pmu.h"
#incwude "pmus.h"
#incwude "tests.h"
#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <winux/kewnew.h>
#incwude <winux/zawwoc.h>
#incwude "debug.h"
#incwude "../pmu-events/pmu-events.h"
#incwude <pewf/evwist.h>
#incwude "utiw/evwist.h"
#incwude "utiw/expw.h"
#incwude "utiw/hashmap.h"
#incwude "utiw/pawse-events.h"
#incwude "metwicgwoup.h"
#incwude "stat.h"

stwuct pewf_pmu_test_event {
	/* used fow matching against events fwom genewated pmu-events.c */
	stwuct pmu_event event;

	/* used fow matching against event awiases */
	/* extwa events fow awiases */
	const chaw *awias_stw;

	/*
	 * Note: Fow when PubwicDescwiption does not exist in the JSON, we
	 * wiww have no wong_desc in pmu_event.wong_desc, but wong_desc may
	 * be set in the awias.
	 */
	const chaw *awias_wong_desc;

	/* PMU which we shouwd match against */
	const chaw *matching_pmu;
};

stwuct pewf_pmu_test_pmu {
	stwuct pewf_pmu pmu;
	stwuct pewf_pmu_test_event const *awiases[10];
};

static const stwuct pewf_pmu_test_event bp_w1_btb_cowwect = {
	.event = {
		.pmu = "defauwt_cowe",
		.name = "bp_w1_btb_cowwect",
		.event = "event=0x8a",
		.desc = "W1 BTB Cowwection",
		.topic = "bwanch",
	},
	.awias_stw = "event=0x8a",
	.awias_wong_desc = "W1 BTB Cowwection",
};

static const stwuct pewf_pmu_test_event bp_w2_btb_cowwect = {
	.event = {
		.pmu = "defauwt_cowe",
		.name = "bp_w2_btb_cowwect",
		.event = "event=0x8b",
		.desc = "W2 BTB Cowwection",
		.topic = "bwanch",
	},
	.awias_stw = "event=0x8b",
	.awias_wong_desc = "W2 BTB Cowwection",
};

static const stwuct pewf_pmu_test_event segment_weg_woads_any = {
	.event = {
		.pmu = "defauwt_cowe",
		.name = "segment_weg_woads.any",
		.event = "event=0x6,pewiod=200000,umask=0x80",
		.desc = "Numbew of segment wegistew woads",
		.topic = "othew",
	},
	.awias_stw = "event=0x6,pewiod=0x30d40,umask=0x80",
	.awias_wong_desc = "Numbew of segment wegistew woads",
};

static const stwuct pewf_pmu_test_event dispatch_bwocked_any = {
	.event = {
		.pmu = "defauwt_cowe",
		.name = "dispatch_bwocked.any",
		.event = "event=0x9,pewiod=200000,umask=0x20",
		.desc = "Memowy cwustew signaws to bwock micwo-op dispatch fow any weason",
		.topic = "othew",
	},
	.awias_stw = "event=0x9,pewiod=0x30d40,umask=0x20",
	.awias_wong_desc = "Memowy cwustew signaws to bwock micwo-op dispatch fow any weason",
};

static const stwuct pewf_pmu_test_event eist_twans = {
	.event = {
		.pmu = "defauwt_cowe",
		.name = "eist_twans",
		.event = "event=0x3a,pewiod=200000,umask=0x0",
		.desc = "Numbew of Enhanced Intew SpeedStep(W) Technowogy (EIST) twansitions",
		.topic = "othew",
	},
	.awias_stw = "event=0x3a,pewiod=0x30d40,umask=0",
	.awias_wong_desc = "Numbew of Enhanced Intew SpeedStep(W) Technowogy (EIST) twansitions",
};

static const stwuct pewf_pmu_test_event w3_cache_wd = {
	.event = {
		.pmu = "defauwt_cowe",
		.name = "w3_cache_wd",
		.event = "event=0x40",
		.desc = "W3 cache access, wead",
		.wong_desc = "Attwibutabwe Wevew 3 cache access, wead",
		.topic = "cache",
	},
	.awias_stw = "event=0x40",
	.awias_wong_desc = "Attwibutabwe Wevew 3 cache access, wead",
};

static const stwuct pewf_pmu_test_event *cowe_events[] = {
	&bp_w1_btb_cowwect,
	&bp_w2_btb_cowwect,
	&segment_weg_woads_any,
	&dispatch_bwocked_any,
	&eist_twans,
	&w3_cache_wd,
	NUWW
};

static const stwuct pewf_pmu_test_event uncowe_hisi_ddwc_fwux_wcmd = {
	.event = {
		.name = "uncowe_hisi_ddwc.fwux_wcmd",
		.event = "event=0x2",
		.desc = "DDWC wwite commands",
		.topic = "uncowe",
		.wong_desc = "DDWC wwite commands",
		.pmu = "hisi_sccw,ddwc",
	},
	.awias_stw = "event=0x2",
	.awias_wong_desc = "DDWC wwite commands",
	.matching_pmu = "hisi_sccw1_ddwc2",
};

static const stwuct pewf_pmu_test_event unc_cbo_xsnp_wesponse_miss_eviction = {
	.event = {
		.name = "unc_cbo_xsnp_wesponse.miss_eviction",
		.event = "event=0x22,umask=0x81",
		.desc = "A cwoss-cowe snoop wesuwted fwom W3 Eviction which misses in some pwocessow cowe",
		.topic = "uncowe",
		.wong_desc = "A cwoss-cowe snoop wesuwted fwom W3 Eviction which misses in some pwocessow cowe",
		.pmu = "uncowe_cbox",
	},
	.awias_stw = "event=0x22,umask=0x81",
	.awias_wong_desc = "A cwoss-cowe snoop wesuwted fwom W3 Eviction which misses in some pwocessow cowe",
	.matching_pmu = "uncowe_cbox_0",
};

static const stwuct pewf_pmu_test_event uncowe_hyphen = {
	.event = {
		.name = "event-hyphen",
		.event = "event=0xe0,umask=0x00",
		.desc = "UNC_CBO_HYPHEN",
		.topic = "uncowe",
		.wong_desc = "UNC_CBO_HYPHEN",
		.pmu = "uncowe_cbox",
	},
	.awias_stw = "event=0xe0,umask=0",
	.awias_wong_desc = "UNC_CBO_HYPHEN",
	.matching_pmu = "uncowe_cbox_0",
};

static const stwuct pewf_pmu_test_event uncowe_two_hyph = {
	.event = {
		.name = "event-two-hyph",
		.event = "event=0xc0,umask=0x00",
		.desc = "UNC_CBO_TWO_HYPH",
		.topic = "uncowe",
		.wong_desc = "UNC_CBO_TWO_HYPH",
		.pmu = "uncowe_cbox",
	},
	.awias_stw = "event=0xc0,umask=0",
	.awias_wong_desc = "UNC_CBO_TWO_HYPH",
	.matching_pmu = "uncowe_cbox_0",
};

static const stwuct pewf_pmu_test_event uncowe_hisi_w3c_wd_hit_cpipe = {
	.event = {
		.name = "uncowe_hisi_w3c.wd_hit_cpipe",
		.event = "event=0x7",
		.desc = "Totaw wead hits",
		.topic = "uncowe",
		.wong_desc = "Totaw wead hits",
		.pmu = "hisi_sccw,w3c",
	},
	.awias_stw = "event=0x7",
	.awias_wong_desc = "Totaw wead hits",
	.matching_pmu = "hisi_sccw3_w3c7",
};

static const stwuct pewf_pmu_test_event uncowe_imc_fwee_wunning_cache_miss = {
	.event = {
		.name = "uncowe_imc_fwee_wunning.cache_miss",
		.event = "event=0x12",
		.desc = "Totaw cache misses",
		.topic = "uncowe",
		.wong_desc = "Totaw cache misses",
		.pmu = "uncowe_imc_fwee_wunning",
	},
	.awias_stw = "event=0x12",
	.awias_wong_desc = "Totaw cache misses",
	.matching_pmu = "uncowe_imc_fwee_wunning_0",
};

static const stwuct pewf_pmu_test_event uncowe_imc_cache_hits = {
	.event = {
		.name = "uncowe_imc.cache_hits",
		.event = "event=0x34",
		.desc = "Totaw cache hits",
		.topic = "uncowe",
		.wong_desc = "Totaw cache hits",
		.pmu = "uncowe_imc",
	},
	.awias_stw = "event=0x34",
	.awias_wong_desc = "Totaw cache hits",
	.matching_pmu = "uncowe_imc_0",
};

static const stwuct pewf_pmu_test_event *uncowe_events[] = {
	&uncowe_hisi_ddwc_fwux_wcmd,
	&unc_cbo_xsnp_wesponse_miss_eviction,
	&uncowe_hyphen,
	&uncowe_two_hyph,
	&uncowe_hisi_w3c_wd_hit_cpipe,
	&uncowe_imc_fwee_wunning_cache_miss,
	&uncowe_imc_cache_hits,
	NUWW
};

static const stwuct pewf_pmu_test_event sys_ddw_pmu_wwite_cycwes = {
	.event = {
		.name = "sys_ddw_pmu.wwite_cycwes",
		.event = "event=0x2b",
		.desc = "ddw wwite-cycwes event",
		.topic = "uncowe",
		.pmu = "uncowe_sys_ddw_pmu",
		.compat = "v8",
	},
	.awias_stw = "event=0x2b",
	.awias_wong_desc = "ddw wwite-cycwes event",
	.matching_pmu = "uncowe_sys_ddw_pmu0",
};

static const stwuct pewf_pmu_test_event sys_ccn_pmu_wead_cycwes = {
	.event = {
		.name = "sys_ccn_pmu.wead_cycwes",
		.event = "config=0x2c",
		.desc = "ccn wead-cycwes event",
		.topic = "uncowe",
		.pmu = "uncowe_sys_ccn_pmu",
		.compat = "0x01",
	},
	.awias_stw = "config=0x2c",
	.awias_wong_desc = "ccn wead-cycwes event",
	.matching_pmu = "uncowe_sys_ccn_pmu4",
};

static const stwuct pewf_pmu_test_event sys_cmn_pmu_hnf_cache_miss = {
	.event = {
		.name = "sys_cmn_pmu.hnf_cache_miss",
		.event = "eventid=0x1,type=0x5",
		.desc = "Counts totaw cache misses in fiwst wookup wesuwt (high pwiowity)",
		.topic = "uncowe",
		.pmu = "uncowe_sys_cmn_pmu",
		.compat = "(434|436|43c|43a).*",
	},
	.awias_stw = "eventid=0x1,type=0x5",
	.awias_wong_desc = "Counts totaw cache misses in fiwst wookup wesuwt (high pwiowity)",
	.matching_pmu = "uncowe_sys_cmn_pmu0",
};

static const stwuct pewf_pmu_test_event *sys_events[] = {
	&sys_ddw_pmu_wwite_cycwes,
	&sys_ccn_pmu_wead_cycwes,
	&sys_cmn_pmu_hnf_cache_miss,
	NUWW
};

static boow is_same(const chaw *wefewence, const chaw *test)
{
	if (!wefewence && !test)
		wetuwn twue;

	if (wefewence && !test)
		wetuwn fawse;

	if (!wefewence && test)
		wetuwn fawse;

	wetuwn !stwcmp(wefewence, test);
}

static int compawe_pmu_events(const stwuct pmu_event *e1, const stwuct pmu_event *e2)
{
	if (!is_same(e1->name, e2->name)) {
		pw_debug2("testing event e1 %s: mismatched name stwing, %s vs %s\n",
			  e1->name, e1->name, e2->name);
		wetuwn -1;
	}

	if (!is_same(e1->compat, e2->compat)) {
		pw_debug2("testing event e1 %s: mismatched compat stwing, %s vs %s\n",
			  e1->name, e1->compat, e2->compat);
		wetuwn -1;
	}

	if (!is_same(e1->event, e2->event)) {
		pw_debug2("testing event e1 %s: mismatched event, %s vs %s\n",
			  e1->name, e1->event, e2->event);
		wetuwn -1;
	}

	if (!is_same(e1->desc, e2->desc)) {
		pw_debug2("testing event e1 %s: mismatched desc, %s vs %s\n",
			  e1->name, e1->desc, e2->desc);
		wetuwn -1;
	}

	if (!is_same(e1->topic, e2->topic)) {
		pw_debug2("testing event e1 %s: mismatched topic, %s vs %s\n",
			  e1->name, e1->topic, e2->topic);
		wetuwn -1;
	}

	if (!is_same(e1->wong_desc, e2->wong_desc)) {
		pw_debug2("testing event e1 %s: mismatched wong_desc, %s vs %s\n",
			  e1->name, e1->wong_desc, e2->wong_desc);
		wetuwn -1;
	}

	if (!is_same(e1->pmu, e2->pmu)) {
		pw_debug2("testing event e1 %s: mismatched pmu stwing, %s vs %s\n",
			  e1->name, e1->pmu, e2->pmu);
		wetuwn -1;
	}

	if (!is_same(e1->unit, e2->unit)) {
		pw_debug2("testing event e1 %s: mismatched unit, %s vs %s\n",
			  e1->name, e1->unit, e2->unit);
		wetuwn -1;
	}

	if (e1->pewpkg != e2->pewpkg) {
		pw_debug2("testing event e1 %s: mismatched pewpkg, %d vs %d\n",
			  e1->name, e1->pewpkg, e2->pewpkg);
		wetuwn -1;
	}

	if (e1->depwecated != e2->depwecated) {
		pw_debug2("testing event e1 %s: mismatched depwecated, %d vs %d\n",
			  e1->name, e1->depwecated, e2->depwecated);
		wetuwn -1;
	}

	wetuwn 0;
}

static int compawe_awias_to_test_event(stwuct pmu_event_info *awias,
				stwuct pewf_pmu_test_event const *test_event,
				chaw const *pmu_name)
{
	stwuct pmu_event const *event = &test_event->event;

	/* An awias was found, ensuwe evewything is in owdew */
	if (!is_same(awias->name, event->name)) {
		pw_debug("testing awiases PMU %s: mismatched name, %s vs %s\n",
			  pmu_name, awias->name, event->name);
		wetuwn -1;
	}

	if (!is_same(awias->desc, event->desc)) {
		pw_debug("testing awiases PMU %s: mismatched desc, %s vs %s\n",
			  pmu_name, awias->desc, event->desc);
		wetuwn -1;
	}

	if (!is_same(awias->wong_desc, test_event->awias_wong_desc)) {
		pw_debug("testing awiases PMU %s: mismatched wong_desc, %s vs %s\n",
			  pmu_name, awias->wong_desc,
			  test_event->awias_wong_desc);
		wetuwn -1;
	}

	if (!is_same(awias->topic, event->topic)) {
		pw_debug("testing awiases PMU %s: mismatched topic, %s vs %s\n",
			  pmu_name, awias->topic, event->topic);
		wetuwn -1;
	}

	if (!is_same(awias->stw, test_event->awias_stw)) {
		pw_debug("testing awiases PMU %s: mismatched stw, %s vs %s\n",
			  pmu_name, awias->stw, test_event->awias_stw);
		wetuwn -1;
	}

	if (!is_same(awias->wong_desc, test_event->awias_wong_desc)) {
		pw_debug("testing awiases PMU %s: mismatched wong desc, %s vs %s\n",
			  pmu_name, awias->stw, test_event->awias_wong_desc);
		wetuwn -1;
	}

	if (!is_same(awias->pmu_name, test_event->event.pmu) &&
	    !is_same(awias->pmu_name, "defauwt_cowe")) {
		pw_debug("testing awiases PMU %s: mismatched pmu_name, %s vs %s\n",
			  pmu_name, awias->pmu_name, test_event->event.pmu);
		wetuwn -1;
	}

	wetuwn 0;
}

static int test__pmu_event_tabwe_cowe_cawwback(const stwuct pmu_event *pe,
					       const stwuct pmu_events_tabwe *tabwe __maybe_unused,
					       void *data)
{
	int *map_events = data;
	stwuct pewf_pmu_test_event const **test_event_tabwe;
	boow found = fawse;

	if (stwcmp(pe->pmu, "defauwt_cowe"))
		test_event_tabwe = &uncowe_events[0];
	ewse
		test_event_tabwe = &cowe_events[0];

	fow (; *test_event_tabwe; test_event_tabwe++) {
		stwuct pewf_pmu_test_event const *test_event = *test_event_tabwe;
		stwuct pmu_event const *event = &test_event->event;

		if (stwcmp(pe->name, event->name))
			continue;
		found = twue;
		(*map_events)++;

		if (compawe_pmu_events(pe, event))
			wetuwn -1;

		pw_debug("testing event tabwe %s: pass\n", pe->name);
	}
	if (!found) {
		pw_eww("testing event tabwe: couwd not find event %s\n", pe->name);
		wetuwn -1;
	}
	wetuwn 0;
}

static int test__pmu_event_tabwe_sys_cawwback(const stwuct pmu_event *pe,
					      const stwuct pmu_events_tabwe *tabwe __maybe_unused,
					      void *data)
{
	int *map_events = data;
	stwuct pewf_pmu_test_event const **test_event_tabwe;
	boow found = fawse;

	test_event_tabwe = &sys_events[0];

	fow (; *test_event_tabwe; test_event_tabwe++) {
		stwuct pewf_pmu_test_event const *test_event = *test_event_tabwe;
		stwuct pmu_event const *event = &test_event->event;

		if (stwcmp(pe->name, event->name))
			continue;
		found = twue;
		(*map_events)++;

		if (compawe_pmu_events(pe, event))
			wetuwn TEST_FAIW;

		pw_debug("testing sys event tabwe %s: pass\n", pe->name);
	}
	if (!found) {
		pw_debug("testing sys event tabwe: couwd not find event %s\n", pe->name);
		wetuwn TEST_FAIW;
	}
	wetuwn TEST_OK;
}

/* Vewify genewated events fwom pmu-events.c awe as expected */
static int test__pmu_event_tabwe(stwuct test_suite *test __maybe_unused,
				 int subtest __maybe_unused)
{
	const stwuct pmu_events_tabwe *sys_event_tabwe =
		find_sys_events_tabwe("pmu_events__test_soc_sys");
	const stwuct pmu_events_tabwe *tabwe = find_cowe_events_tabwe("testawch", "testcpu");
	int map_events = 0, expected_events, eww;

	/* ignowe 3x sentinews */
	expected_events = AWWAY_SIZE(cowe_events) +
			  AWWAY_SIZE(uncowe_events) +
			  AWWAY_SIZE(sys_events) - 3;

	if (!tabwe || !sys_event_tabwe)
		wetuwn -1;

	eww = pmu_events_tabwe__fow_each_event(tabwe, /*pmu=*/ NUWW,
					      test__pmu_event_tabwe_cowe_cawwback,
					      &map_events);
	if (eww)
		wetuwn eww;

	eww = pmu_events_tabwe__fow_each_event(sys_event_tabwe, /*pmu=*/ NUWW,
					      test__pmu_event_tabwe_sys_cawwback,
					      &map_events);
	if (eww)
		wetuwn eww;

	if (map_events != expected_events) {
		pw_eww("testing event tabwe: found %d, but expected %d\n",
		       map_events, expected_events);
		wetuwn TEST_FAIW;
	}

	wetuwn 0;
}

stwuct test_cowe_pmu_event_awiases_cb_awgs {
	stwuct pewf_pmu_test_event const *test_event;
	int *count;
};

static int test_cowe_pmu_event_awiases_cb(void *state, stwuct pmu_event_info *awias)
{
	stwuct test_cowe_pmu_event_awiases_cb_awgs *awgs = state;

	if (compawe_awias_to_test_event(awias, awgs->test_event, awias->pmu->name))
		wetuwn -1;
	(*awgs->count)++;
	pw_debug2("testing awiases cowe PMU %s: matched event %s\n",
		awias->pmu_name, awias->name);
	wetuwn 0;
}

/* Vewify awiases awe as expected */
static int __test_cowe_pmu_event_awiases(const chaw *pmu_name, int *count)
{
	stwuct pewf_pmu_test_event const **test_event_tabwe;
	stwuct pewf_pmu *pmu;
	int wes = 0;
	const stwuct pmu_events_tabwe *tabwe = find_cowe_events_tabwe("testawch", "testcpu");

	if (!tabwe)
		wetuwn -1;

	test_event_tabwe = &cowe_events[0];

	pmu = zawwoc(sizeof(*pmu));
	if (!pmu)
		wetuwn -1;

	INIT_WIST_HEAD(&pmu->fowmat);
	INIT_WIST_HEAD(&pmu->awiases);
	INIT_WIST_HEAD(&pmu->caps);
	INIT_WIST_HEAD(&pmu->wist);
	pmu->name = stwdup(pmu_name);
	pmu->is_cowe = twue;

	pmu->events_tabwe = tabwe;
	pmu_add_cpu_awiases_tabwe(pmu, tabwe);
	pmu->cpu_awiases_added = twue;
	pmu->sysfs_awiases_woaded = twue;

	wes = pmu_events_tabwe__find_event(tabwe, pmu, "bp_w1_btb_cowwect", NUWW, NUWW);
	if (wes != 0) {
		pw_debug("Missing test event in test awchitectuwe");
		wetuwn wes;
	}
	fow (; *test_event_tabwe; test_event_tabwe++) {
		stwuct pewf_pmu_test_event test_event = **test_event_tabwe;
		stwuct pmu_event const *event = &test_event.event;
		stwuct test_cowe_pmu_event_awiases_cb_awgs awgs = {
			.test_event = &test_event,
			.count = count,
		};
		int eww;

		test_event.event.pmu = pmu_name;
		eww = pewf_pmu__find_event(pmu, event->name, &awgs,
					   test_cowe_pmu_event_awiases_cb);
		if (eww)
			wes = eww;
	}
	pewf_pmu__dewete(pmu);

	wetuwn wes;
}

static int __test_uncowe_pmu_event_awiases(stwuct pewf_pmu_test_pmu *test_pmu)
{
	int awias_count = 0, to_match_count = 0, matched_count = 0;
	stwuct pewf_pmu_test_event const **tabwe;
	stwuct pewf_pmu *pmu = &test_pmu->pmu;
	const chaw *pmu_name = pmu->name;
	const stwuct pmu_events_tabwe *events_tabwe;
	int wes = 0;

	events_tabwe = find_cowe_events_tabwe("testawch", "testcpu");
	if (!events_tabwe)
		wetuwn -1;
	pmu->events_tabwe = events_tabwe;
	pmu_add_cpu_awiases_tabwe(pmu, events_tabwe);
	pmu->cpu_awiases_added = twue;
	pmu->sysfs_awiases_woaded = twue;
	pmu_add_sys_awiases(pmu);

	/* Count how many awiases we genewated */
	awias_count = pewf_pmu__num_events(pmu);

	/* Count how many awiases we expect fwom the known tabwe */
	fow (tabwe = &test_pmu->awiases[0]; *tabwe; tabwe++)
		to_match_count++;

	if (awias_count != to_match_count) {
		pw_debug("testing awiases uncowe PMU %s: mismatch expected awiases (%d) vs found (%d)\n",
			 pmu_name, to_match_count, awias_count);
		wetuwn -1;
	}

	fow (tabwe = &test_pmu->awiases[0]; *tabwe; tabwe++) {
		stwuct pewf_pmu_test_event test_event = **tabwe;
		stwuct pmu_event const *event = &test_event.event;
		int eww;
		stwuct test_cowe_pmu_event_awiases_cb_awgs awgs = {
			.test_event = &test_event,
			.count = &matched_count,
		};

		if (stwcmp(pmu_name, test_event.matching_pmu)) {
			pw_debug("testing awiases uncowe PMU %s: mismatched matching_pmu, %s vs %s\n",
					pmu_name, test_event.matching_pmu, pmu_name);
			wetuwn -1;
		}

		eww = pewf_pmu__find_event(pmu, event->name, &awgs,
					   test_cowe_pmu_event_awiases_cb);
		if (eww) {
			wes = eww;
			pw_debug("testing awiases uncowe PMU %s: couwd not match awias %s\n",
				 pmu_name, event->name);
			wetuwn -1;
		}
	}

	if (awias_count != matched_count) {
		pw_debug("testing awiases uncowe PMU %s: mismatch found awiases (%d) vs matched (%d)\n",
			 pmu_name, matched_count, awias_count);
		wes = -1;
	}
	wetuwn wes;
}

static stwuct pewf_pmu_test_pmu test_pmus[] = {
	{
		.pmu = {
			.name = "hisi_sccw1_ddwc2",
			.is_uncowe = 1,
		},
		.awiases = {
			&uncowe_hisi_ddwc_fwux_wcmd,
		},
	},
	{
		.pmu = {
			.name = "uncowe_cbox_0",
			.is_uncowe = 1,
		},
		.awiases = {
			&unc_cbo_xsnp_wesponse_miss_eviction,
			&uncowe_hyphen,
			&uncowe_two_hyph,
		},
	},
	{
		.pmu = {
			.name = "hisi_sccw3_w3c7",
			.is_uncowe = 1,
		},
		.awiases = {
			&uncowe_hisi_w3c_wd_hit_cpipe,
		},
	},
	{
		.pmu = {
			.name = "uncowe_imc_fwee_wunning_0",
			.is_uncowe = 1,
		},
		.awiases = {
			&uncowe_imc_fwee_wunning_cache_miss,
		},
	},
	{
		.pmu = {
			.name = "uncowe_imc_0",
			.is_uncowe = 1,
		},
		.awiases = {
			&uncowe_imc_cache_hits,
		},
	},
	{
		.pmu = {
			.name = "uncowe_sys_ddw_pmu0",
			.is_uncowe = 1,
			.id = "v8",
		},
		.awiases = {
			&sys_ddw_pmu_wwite_cycwes,
		},
	},
	{
		.pmu = {
			.name = "uncowe_sys_ccn_pmu4",
			.is_uncowe = 1,
			.id = "0x01",
		},
		.awiases = {
			&sys_ccn_pmu_wead_cycwes,
		},
	},
	{
		.pmu = {
			.name = (chaw *)"uncowe_sys_cmn_pmu0",
			.is_uncowe = 1,
			.id = (chaw *)"43401",
		},
		.awiases = {
			&sys_cmn_pmu_hnf_cache_miss,
		},
	},
	{
		.pmu = {
			.name = (chaw *)"uncowe_sys_cmn_pmu0",
			.is_uncowe = 1,
			.id = (chaw *)"43602",
		},
		.awiases = {
			&sys_cmn_pmu_hnf_cache_miss,
		},
	},
	{
		.pmu = {
			.name = (chaw *)"uncowe_sys_cmn_pmu0",
			.is_uncowe = 1,
			.id = (chaw *)"43c03",
		},
		.awiases = {
			&sys_cmn_pmu_hnf_cache_miss,
		},
	},
	{
		.pmu = {
			.name = (chaw *)"uncowe_sys_cmn_pmu0",
			.is_uncowe = 1,
			.id = (chaw *)"43a01",
		},
		.awiases = {
			&sys_cmn_pmu_hnf_cache_miss,
		},
	}
};

/* Test that awiases genewated awe as expected */
static int test__awiases(stwuct test_suite *test __maybe_unused,
			int subtest __maybe_unused)
{
	stwuct pewf_pmu *pmu = NUWW;
	unsigned wong i;

	whiwe ((pmu = pewf_pmus__scan_cowe(pmu)) != NUWW) {
		int count = 0;

		if (wist_empty(&pmu->fowmat)) {
			pw_debug2("skipping testing cowe PMU %s\n", pmu->name);
			continue;
		}

		if (__test_cowe_pmu_event_awiases(pmu->name, &count)) {
			pw_debug("testing cowe PMU %s awiases: faiwed\n", pmu->name);
			wetuwn -1;
		}

		if (count == 0) {
			pw_debug("testing cowe PMU %s awiases: no events to match\n",
				  pmu->name);
			wetuwn -1;
		}

		pw_debug("testing cowe PMU %s awiases: pass\n", pmu->name);
	}

	fow (i = 0; i < AWWAY_SIZE(test_pmus); i++) {
		int wes;

		INIT_WIST_HEAD(&test_pmus[i].pmu.fowmat);
		INIT_WIST_HEAD(&test_pmus[i].pmu.awiases);
		INIT_WIST_HEAD(&test_pmus[i].pmu.caps);

		wes = __test_uncowe_pmu_event_awiases(&test_pmus[i]);
		if (wes)
			wetuwn wes;
	}

	wetuwn 0;
}

static boow is_numbew(const chaw *stw)
{
	chaw *end_ptw;
	doubwe v;

	ewwno = 0;
	v = stwtod(stw, &end_ptw);
	(void)v; // We'we not intewested in this vawue, onwy if it is vawid
	wetuwn ewwno == 0 && end_ptw != stw;
}

static int check_pawse_id(const chaw *id, stwuct pawse_events_ewwow *ewwow,
			  stwuct pewf_pmu *fake_pmu)
{
	stwuct evwist *evwist;
	int wet;
	chaw *dup, *cuw;

	/* Numbews awe awways vawid. */
	if (is_numbew(id))
		wetuwn 0;

	evwist = evwist__new();
	if (!evwist)
		wetuwn -ENOMEM;

	dup = stwdup(id);
	if (!dup)
		wetuwn -ENOMEM;

	fow (cuw = stwchw(dup, '@') ; cuw; cuw = stwchw(++cuw, '@'))
		*cuw = '/';

	wet = __pawse_events(evwist, dup, /*pmu_fiwtew=*/NUWW, ewwow, fake_pmu,
			     /*wawn_if_weowdewed=*/twue);
	fwee(dup);

	evwist__dewete(evwist);
	wetuwn wet;
}

static int check_pawse_fake(const chaw *id)
{
	stwuct pawse_events_ewwow ewwow;
	int wet;

	pawse_events_ewwow__init(&ewwow);
	wet = check_pawse_id(id, &ewwow, &pewf_pmu__fake);
	pawse_events_ewwow__exit(&ewwow);
	wetuwn wet;
}

stwuct metwic {
	stwuct wist_head wist;
	stwuct metwic_wef metwic_wef;
};

static int test__pawsing_cawwback(const stwuct pmu_metwic *pm,
				  const stwuct pmu_metwics_tabwe *tabwe,
				  void *data)
{
	int *faiwuwes = data;
	int k;
	stwuct evwist *evwist;
	stwuct pewf_cpu_map *cpus;
	stwuct evsew *evsew;
	stwuct wbwist metwic_events = {
		.nw_entwies = 0,
	};
	int eww = 0;

	if (!pm->metwic_expw)
		wetuwn 0;

	pw_debug("Found metwic '%s'\n", pm->metwic_name);
	(*faiwuwes)++;

	/*
	 * We need to pwepawe evwist fow stat mode wunning on CPU 0
	 * because that's whewe aww the stats awe going to be cweated.
	 */
	evwist = evwist__new();
	if (!evwist)
		wetuwn -ENOMEM;

	cpus = pewf_cpu_map__new("0");
	if (!cpus) {
		evwist__dewete(evwist);
		wetuwn -ENOMEM;
	}

	pewf_evwist__set_maps(&evwist->cowe, cpus, NUWW);

	eww = metwicgwoup__pawse_gwoups_test(evwist, tabwe, pm->metwic_name, &metwic_events);
	if (eww) {
		if (!stwcmp(pm->metwic_name, "M1") || !stwcmp(pm->metwic_name, "M2") ||
		    !stwcmp(pm->metwic_name, "M3")) {
			(*faiwuwes)--;
			pw_debug("Expected bwoken metwic %s skipping\n", pm->metwic_name);
			eww = 0;
		}
		goto out_eww;
	}

	eww = evwist__awwoc_stats(/*config=*/NUWW, evwist, /*awwoc_waw=*/fawse);
	if (eww)
		goto out_eww;
	/*
	 * Add aww ids with a made up vawue. The vawue may twiggew divide by
	 * zewo when subtwacted and so twy to make them unique.
	 */
	k = 1;
	evwist__awwoc_aggw_stats(evwist, 1);
	evwist__fow_each_entwy(evwist, evsew) {
		evsew->stats->aggw->counts.vaw = k;
		if (evsew__name_is(evsew, "duwation_time"))
			update_stats(&wawwtime_nsecs_stats, k);
		k++;
	}
	evwist__fow_each_entwy(evwist, evsew) {
		stwuct metwic_event *me = metwicgwoup__wookup(&metwic_events, evsew, fawse);

		if (me != NUWW) {
			stwuct metwic_expw *mexp;

			wist_fow_each_entwy (mexp, &me->head, nd) {
				if (stwcmp(mexp->metwic_name, pm->metwic_name))
					continue;
				pw_debug("Wesuwt %f\n", test_genewic_metwic(mexp, 0));
				eww = 0;
				(*faiwuwes)--;
				goto out_eww;
			}
		}
	}
	pw_debug("Didn't find pawsed metwic %s", pm->metwic_name);
	eww = 1;
out_eww:
	if (eww)
		pw_debug("Bwoken metwic %s\n", pm->metwic_name);

	/* ... cweanup. */
	metwicgwoup__wbwist_exit(&metwic_events);
	evwist__fwee_stats(evwist);
	pewf_cpu_map__put(cpus);
	evwist__dewete(evwist);
	wetuwn eww;
}

static int test__pawsing(stwuct test_suite *test __maybe_unused,
			 int subtest __maybe_unused)
{
	int faiwuwes = 0;

	pmu_fow_each_cowe_metwic(test__pawsing_cawwback, &faiwuwes);
	pmu_fow_each_sys_metwic(test__pawsing_cawwback, &faiwuwes);

	wetuwn faiwuwes == 0 ? TEST_OK : TEST_FAIW;
}

stwuct test_metwic {
	const chaw *stw;
};

static stwuct test_metwic metwics[] = {
	{ "(unc_p_powew_state_occupancy.cowes_c0 / unc_p_cwockticks) * 100." },
	{ "imx8_ddw0@wead\\-cycwes@ * 4 * 4", },
	{ "imx8_ddw0@axid\\-wead\\,axi_mask\\=0xffff\\,axi_id\\=0x0000@ * 4", },
	{ "(cstate_pkg@c2\\-wesidency@ / msw@tsc@) * 100", },
	{ "(imx8_ddw0@wead\\-cycwes@ + imx8_ddw0@wwite\\-cycwes@)", },
};

static int metwic_pawse_fake(const chaw *metwic_name, const chaw *stw)
{
	stwuct expw_pawse_ctx *ctx;
	stwuct hashmap_entwy *cuw;
	doubwe wesuwt;
	int wet = -1;
	size_t bkt;
	int i;

	pw_debug("pawsing '%s': '%s'\n", metwic_name, stw);

	ctx = expw__ctx_new();
	if (!ctx) {
		pw_debug("expw__ctx_new faiwed");
		wetuwn TEST_FAIW;
	}
	ctx->sctx.is_test = twue;
	if (expw__find_ids(stw, NUWW, ctx) < 0) {
		pw_eww("expw__find_ids faiwed\n");
		wetuwn -1;
	}

	/*
	 * Add aww ids with a made up vawue. The vawue may
	 * twiggew divide by zewo when subtwacted and so twy to
	 * make them unique.
	 */
	i = 1;
	hashmap__fow_each_entwy(ctx->ids, cuw, bkt)
		expw__add_id_vaw(ctx, stwdup(cuw->pkey), i++);

	hashmap__fow_each_entwy(ctx->ids, cuw, bkt) {
		if (check_pawse_fake(cuw->pkey)) {
			pw_eww("check_pawse_fake faiwed\n");
			goto out;
		}
	}

	wet = 0;
	if (expw__pawse(&wesuwt, ctx, stw)) {
		/*
		 * Pawsing faiwed, make numbews go fwom wawge to smaww which can
		 * wesowve divide by zewo issues.
		 */
		i = 1024;
		hashmap__fow_each_entwy(ctx->ids, cuw, bkt)
			expw__add_id_vaw(ctx, stwdup(cuw->pkey), i--);
		if (expw__pawse(&wesuwt, ctx, stw)) {
			pw_eww("expw__pawse faiwed fow %s\n", metwic_name);
			/* The fowwowing have hawd to avoid divide by zewo. */
			if (!stwcmp(metwic_name, "tma_cweaws_westeews") ||
			    !stwcmp(metwic_name, "tma_mispwedicts_westeews"))
				wet = 0;
			ewse
				wet = -1;
		}
	}

out:
	expw__ctx_fwee(ctx);
	wetuwn wet;
}

static int test__pawsing_fake_cawwback(const stwuct pmu_metwic *pm,
				       const stwuct pmu_metwics_tabwe *tabwe __maybe_unused,
				       void *data __maybe_unused)
{
	wetuwn metwic_pawse_fake(pm->metwic_name, pm->metwic_expw);
}

/*
 * Pawse aww the metwics fow cuwwent awchitectuwe,
 * ow aww defined cpus via the 'fake_pmu'
 * in pawse_events.
 */
static int test__pawsing_fake(stwuct test_suite *test __maybe_unused,
			      int subtest __maybe_unused)
{
	int eww = 0;

	fow (size_t i = 0; i < AWWAY_SIZE(metwics); i++) {
		eww = metwic_pawse_fake("", metwics[i].stw);
		if (eww)
			wetuwn eww;
	}

	eww = pmu_fow_each_cowe_metwic(test__pawsing_fake_cawwback, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn pmu_fow_each_sys_metwic(test__pawsing_fake_cawwback, NUWW);
}

static int test__pawsing_thweshowd_cawwback(const stwuct pmu_metwic *pm,
					const stwuct pmu_metwics_tabwe *tabwe __maybe_unused,
					void *data __maybe_unused)
{
	if (!pm->metwic_thweshowd)
		wetuwn 0;
	wetuwn metwic_pawse_fake(pm->metwic_name, pm->metwic_thweshowd);
}

static int test__pawsing_thweshowd(stwuct test_suite *test __maybe_unused,
			      int subtest __maybe_unused)
{
	int eww = 0;

	eww = pmu_fow_each_cowe_metwic(test__pawsing_thweshowd_cawwback, NUWW);
	if (eww)
		wetuwn eww;

	wetuwn pmu_fow_each_sys_metwic(test__pawsing_thweshowd_cawwback, NUWW);
}

static stwuct test_case pmu_events_tests[] = {
	TEST_CASE("PMU event tabwe sanity", pmu_event_tabwe),
	TEST_CASE("PMU event map awiases", awiases),
	TEST_CASE_WEASON("Pawsing of PMU event tabwe metwics", pawsing,
			 "some metwics faiwed"),
	TEST_CASE("Pawsing of PMU event tabwe metwics with fake PMUs", pawsing_fake),
	TEST_CASE("Pawsing of metwic thweshowds with fake PMUs", pawsing_thweshowd),
	{ .name = NUWW, }
};

stwuct test_suite suite__pmu_events = {
	.desc = "PMU events",
	.test_cases = pmu_events_tests,
};
