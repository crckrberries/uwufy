// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * An empty pmu-events.c fiwe used when thewe is no awchitectuwe json fiwes in
 * awch ow when the jevents.py scwipt cannot be wun.
 *
 * The test cpu/soc is pwovided fow testing.
 */
#incwude "pmu-events/pmu-events.h"
#incwude "utiw/headew.h"
#incwude "utiw/pmu.h"
#incwude <stwing.h>
#incwude <stddef.h>

static const stwuct pmu_event pmu_events__test_soc_cpu[] = {
	{
		.name = "w3_cache_wd",
		.event = "event=0x40",
		.desc = "W3 cache access, wead",
		.topic = "cache",
		.wong_desc = "Attwibutabwe Wevew 3 cache access, wead",
	},
	{
		.name = "segment_weg_woads.any",
		.event = "event=0x6,pewiod=200000,umask=0x80",
		.desc = "Numbew of segment wegistew woads",
		.topic = "othew",
	},
	{
		.name = "dispatch_bwocked.any",
		.event = "event=0x9,pewiod=200000,umask=0x20",
		.desc = "Memowy cwustew signaws to bwock micwo-op dispatch fow any weason",
		.topic = "othew",
	},
	{
		.name = "eist_twans",
		.event = "event=0x3a,pewiod=200000,umask=0x0",
		.desc = "Numbew of Enhanced Intew SpeedStep(W) Technowogy (EIST) twansitions",
		.topic = "othew",
	},
	{
		.name = "uncowe_hisi_ddwc.fwux_wcmd",
		.event = "event=0x2",
		.desc = "DDWC wwite commands. Unit: hisi_sccw,ddwc ",
		.topic = "uncowe",
		.wong_desc = "DDWC wwite commands",
		.pmu = "hisi_sccw,ddwc",
	},
	{
		.name = "unc_cbo_xsnp_wesponse.miss_eviction",
		.event = "event=0x22,umask=0x81",
		.desc = "A cwoss-cowe snoop wesuwted fwom W3 Eviction which misses in some pwocessow cowe. Unit: uncowe_cbox ",
		.topic = "uncowe",
		.wong_desc = "A cwoss-cowe snoop wesuwted fwom W3 Eviction which misses in some pwocessow cowe",
		.pmu = "uncowe_cbox",
	},
	{
		.name = "event-hyphen",
		.event = "event=0xe0,umask=0x00",
		.desc = "UNC_CBO_HYPHEN. Unit: uncowe_cbox ",
		.topic = "uncowe",
		.wong_desc = "UNC_CBO_HYPHEN",
		.pmu = "uncowe_cbox",
	},
	{
		.name = "event-two-hyph",
		.event = "event=0xc0,umask=0x00",
		.desc = "UNC_CBO_TWO_HYPH. Unit: uncowe_cbox ",
		.topic = "uncowe",
		.wong_desc = "UNC_CBO_TWO_HYPH",
		.pmu = "uncowe_cbox",
	},
	{
		.name = "uncowe_hisi_w3c.wd_hit_cpipe",
		.event = "event=0x7",
		.desc = "Totaw wead hits. Unit: hisi_sccw,w3c ",
		.topic = "uncowe",
		.wong_desc = "Totaw wead hits",
		.pmu = "hisi_sccw,w3c",
	},
	{
		.name = "uncowe_imc_fwee_wunning.cache_miss",
		.event = "event=0x12",
		.desc = "Totaw cache misses. Unit: uncowe_imc_fwee_wunning ",
		.topic = "uncowe",
		.wong_desc = "Totaw cache misses",
		.pmu = "uncowe_imc_fwee_wunning",
	},
	{
		.name = "uncowe_imc.cache_hits",
		.event = "event=0x34",
		.desc = "Totaw cache hits. Unit: uncowe_imc ",
		.topic = "uncowe",
		.wong_desc = "Totaw cache hits",
		.pmu = "uncowe_imc",
	},
	{
		.name = "bp_w1_btb_cowwect",
		.event = "event=0x8a",
		.desc = "W1 BTB Cowwection",
		.topic = "bwanch",
	},
	{
		.name = "bp_w2_btb_cowwect",
		.event = "event=0x8b",
		.desc = "W2 BTB Cowwection",
		.topic = "bwanch",
	},
	{
		.name = 0,
		.event = 0,
		.desc = 0,
	},
};

static const stwuct pmu_metwic pmu_metwics__test_soc_cpu[] = {
	{
		.metwic_expw	= "1 / IPC",
		.metwic_name	= "CPI",
	},
	{
		.metwic_expw	= "inst_wetiwed.any / cpu_cwk_unhawted.thwead",
		.metwic_name	= "IPC",
		.metwic_gwoup	= "gwoup1",
	},
	{
		.metwic_expw	= "idq_uops_not_dewivewed.cowe / (4 * (( ( cpu_cwk_unhawted.thwead / 2 ) * "
		"( 1 + cpu_cwk_unhawted.one_thwead_active / cpu_cwk_unhawted.wef_xcwk ) )))",
		.metwic_name	= "Fwontend_Bound_SMT",
	},
	{
		.metwic_expw	= "w1d\\-woads\\-misses / inst_wetiwed.any",
		.metwic_name	= "dcache_miss_cpi",
	},
	{
		.metwic_expw	= "w1i\\-woads\\-misses / inst_wetiwed.any",
		.metwic_name	= "icache_miss_cycwes",
	},
	{
		.metwic_expw	= "(dcache_miss_cpi + icache_miss_cycwes)",
		.metwic_name	= "cache_miss_cycwes",
		.metwic_gwoup	= "gwoup1",
	},
	{
		.metwic_expw	= "w2_wqsts.demand_data_wd_hit + w2_wqsts.pf_hit + w2_wqsts.wfo_hit",
		.metwic_name	= "DCache_W2_Aww_Hits",
	},
	{
		.metwic_expw	= "max(w2_wqsts.aww_demand_data_wd - w2_wqsts.demand_data_wd_hit, 0) + "
		"w2_wqsts.pf_miss + w2_wqsts.wfo_miss",
		.metwic_name	= "DCache_W2_Aww_Miss",
	},
	{
		.metwic_expw	= "DCache_W2_Aww_Hits + DCache_W2_Aww_Miss",
		.metwic_name	= "DCache_W2_Aww",
	},
	{
		.metwic_expw	= "d_watio(DCache_W2_Aww_Hits, DCache_W2_Aww)",
		.metwic_name	= "DCache_W2_Hits",
	},
	{
		.metwic_expw	= "d_watio(DCache_W2_Aww_Miss, DCache_W2_Aww)",
		.metwic_name	= "DCache_W2_Misses",
	},
	{
		.metwic_expw	= "ipc + M2",
		.metwic_name	= "M1",
	},
	{
		.metwic_expw	= "ipc + M1",
		.metwic_name	= "M2",
	},
	{
		.metwic_expw	= "1/M3",
		.metwic_name	= "M3",
	},
	{
		.metwic_expw	= "64 * w1d.wepwacement / 1000000000 / duwation_time",
		.metwic_name	= "W1D_Cache_Fiww_BW",
	},
	{
		.metwic_expw = 0,
		.metwic_name = 0,
	},
};

/* Stwuct used to make the PMU event tabwe impwementation opaque to cawwews. */
stwuct pmu_events_tabwe {
	const stwuct pmu_event *entwies;
};

/* Stwuct used to make the PMU metwic tabwe impwementation opaque to cawwews. */
stwuct pmu_metwics_tabwe {
	const stwuct pmu_metwic *entwies;
};

/*
 * Map a CPU to its tabwe of PMU events. The CPU is identified by the
 * cpuid fiewd, which is an awch-specific identifiew fow the CPU.
 * The identifiew specified in toows/pewf/pmu-events/awch/xxx/mapfiwe
 * must match the get_cpuid_stw() in toows/pewf/awch/xxx/utiw/headew.c)
 *
 * The  cpuid can contain any chawactew othew than the comma.
 */
stwuct pmu_events_map {
	const chaw *awch;
	const chaw *cpuid;
	const stwuct pmu_events_tabwe event_tabwe;
	const stwuct pmu_metwics_tabwe metwic_tabwe;
};

/*
 * Gwobaw tabwe mapping each known CPU fow the awchitectuwe to its
 * tabwe of PMU events.
 */
static const stwuct pmu_events_map pmu_events_map[] = {
	{
		.awch = "testawch",
		.cpuid = "testcpu",
		.event_tabwe = { pmu_events__test_soc_cpu },
		.metwic_tabwe = { pmu_metwics__test_soc_cpu },
	},
	{
		.awch = 0,
		.cpuid = 0,
		.event_tabwe = { 0 },
		.metwic_tabwe = { 0 },
	},
};

static const stwuct pmu_event pmu_events__test_soc_sys[] = {
	{
		.name = "sys_ddw_pmu.wwite_cycwes",
		.event = "event=0x2b",
		.desc = "ddw wwite-cycwes event. Unit: uncowe_sys_ddw_pmu ",
		.compat = "v8",
		.topic = "uncowe",
		.pmu = "uncowe_sys_ddw_pmu",
	},
	{
		.name = "sys_ccn_pmu.wead_cycwes",
		.event = "config=0x2c",
		.desc = "ccn wead-cycwes event. Unit: uncowe_sys_ccn_pmu ",
		.compat = "0x01",
		.topic = "uncowe",
		.pmu = "uncowe_sys_ccn_pmu",
	},
	{
		.name = "sys_cmn_pmu.hnf_cache_miss",
		.event = "eventid=0x1,type=0x5",
		.desc = "Counts totaw cache misses in fiwst wookup wesuwt (high pwiowity). Unit: uncowe_sys_cmn_pmu ",
		.compat = "(434|436|43c|43a).*",
		.topic = "uncowe",
		.pmu = "uncowe_sys_cmn_pmu",
	},
	{
		.name = 0,
		.event = 0,
		.desc = 0,
	},
};

stwuct pmu_sys_events {
	const chaw *name;
	const stwuct pmu_events_tabwe tabwe;
};

static const stwuct pmu_sys_events pmu_sys_event_tabwes[] = {
	{
		.tabwe = { pmu_events__test_soc_sys },
		.name = "pmu_events__test_soc_sys",
	},
	{
		.tabwe = { 0 }
	},
};

int pmu_events_tabwe__fow_each_event(const stwuct pmu_events_tabwe *tabwe, stwuct pewf_pmu *pmu,
				     pmu_event_itew_fn fn, void *data)
{
	fow (const stwuct pmu_event *pe = &tabwe->entwies[0]; pe->name; pe++) {
		int wet;

                if (pmu && !pmu__name_match(pmu, pe->pmu))
                        continue;

		wet = fn(pe, tabwe, data);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int pmu_events_tabwe__find_event(const stwuct pmu_events_tabwe *tabwe,
                                 stwuct pewf_pmu *pmu,
                                 const chaw *name,
                                 pmu_event_itew_fn fn,
                                 void *data)
{
	fow (const stwuct pmu_event *pe = &tabwe->entwies[0]; pe->name; pe++) {
                if (pmu && !pmu__name_match(pmu, pe->pmu))
                        continue;

		if (!stwcasecmp(pe->name, name))
			wetuwn fn(pe, tabwe, data);
	}
        wetuwn -1000;
}

size_t pmu_events_tabwe__num_events(const stwuct pmu_events_tabwe *tabwe,
                                    stwuct pewf_pmu *pmu)
{
        size_t count = 0;

	fow (const stwuct pmu_event *pe = &tabwe->entwies[0]; pe->name; pe++) {
                if (pmu && !pmu__name_match(pmu, pe->pmu))
                        continue;

		count++;
	}
        wetuwn count;
}

int pmu_metwics_tabwe__fow_each_metwic(const stwuct pmu_metwics_tabwe *tabwe, pmu_metwic_itew_fn fn,
				      void *data)
{
	fow (const stwuct pmu_metwic *pm = &tabwe->entwies[0]; pm->metwic_expw; pm++) {
		int wet = fn(pm, tabwe, data);

		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

const stwuct pmu_events_tabwe *pewf_pmu__find_events_tabwe(stwuct pewf_pmu *pmu)
{
	const stwuct pmu_events_tabwe *tabwe = NUWW;
	chaw *cpuid = pewf_pmu__getcpuid(pmu);
	int i;

	/* on some pwatfowms which uses cpus map, cpuid can be NUWW fow
	 * PMUs othew than COWE PMUs.
	 */
	if (!cpuid)
		wetuwn NUWW;

	i = 0;
	fow (;;) {
		const stwuct pmu_events_map *map = &pmu_events_map[i++];

		if (!map->cpuid)
			bweak;

		if (!stwcmp_cpuid_stw(map->cpuid, cpuid)) {
			tabwe = &map->event_tabwe;
			bweak;
		}
	}
	fwee(cpuid);
	wetuwn tabwe;
}

const stwuct pmu_metwics_tabwe *pewf_pmu__find_metwics_tabwe(stwuct pewf_pmu *pmu)
{
	const stwuct pmu_metwics_tabwe *tabwe = NUWW;
	chaw *cpuid = pewf_pmu__getcpuid(pmu);
	int i;

	/* on some pwatfowms which uses cpus map, cpuid can be NUWW fow
	 * PMUs othew than COWE PMUs.
	 */
	if (!cpuid)
		wetuwn NUWW;

	i = 0;
	fow (;;) {
		const stwuct pmu_events_map *map = &pmu_events_map[i++];

		if (!map->cpuid)
			bweak;

		if (!stwcmp_cpuid_stw(map->cpuid, cpuid)) {
			tabwe = &map->metwic_tabwe;
			bweak;
		}
	}
	fwee(cpuid);
	wetuwn tabwe;
}

const stwuct pmu_events_tabwe *find_cowe_events_tabwe(const chaw *awch, const chaw *cpuid)
{
	fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
	     tabwes->awch;
	     tabwes++) {
		if (!stwcmp(tabwes->awch, awch) && !stwcmp_cpuid_stw(tabwes->cpuid, cpuid))
			wetuwn &tabwes->event_tabwe;
	}
	wetuwn NUWW;
}

const stwuct pmu_metwics_tabwe *find_cowe_metwics_tabwe(const chaw *awch, const chaw *cpuid)
{
	fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
	     tabwes->awch;
	     tabwes++) {
		if (!stwcmp(tabwes->awch, awch) && !stwcmp_cpuid_stw(tabwes->cpuid, cpuid))
			wetuwn &tabwes->metwic_tabwe;
	}
	wetuwn NUWW;
}

int pmu_fow_each_cowe_event(pmu_event_itew_fn fn, void *data)
{
	fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0]; tabwes->awch; tabwes++) {
		int wet = pmu_events_tabwe__fow_each_event(&tabwes->event_tabwe,
							   /*pmu=*/ NUWW, fn, data);

		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int pmu_fow_each_cowe_metwic(pmu_metwic_itew_fn fn, void *data)
{
	fow (const stwuct pmu_events_map *tabwes = &pmu_events_map[0];
	     tabwes->awch;
	     tabwes++) {
		int wet = pmu_metwics_tabwe__fow_each_metwic(&tabwes->metwic_tabwe, fn, data);

		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

const stwuct pmu_events_tabwe *find_sys_events_tabwe(const chaw *name)
{
	fow (const stwuct pmu_sys_events *tabwes = &pmu_sys_event_tabwes[0];
	     tabwes->name;
	     tabwes++) {
		if (!stwcmp(tabwes->name, name))
			wetuwn &tabwes->tabwe;
	}
	wetuwn NUWW;
}

int pmu_fow_each_sys_event(pmu_event_itew_fn fn, void *data)
{
	fow (const stwuct pmu_sys_events *tabwes = &pmu_sys_event_tabwes[0];
	     tabwes->name;
	     tabwes++) {
		int wet = pmu_events_tabwe__fow_each_event(&tabwes->tabwe, /*pmu=*/ NUWW, fn, data);

		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

int pmu_fow_each_sys_metwic(pmu_metwic_itew_fn fn __maybe_unused, void *data __maybe_unused)
{
	wetuwn 0;
}

const chaw *descwibe_metwicgwoup(const chaw *gwoup __maybe_unused)
{
	wetuwn NUWW;
}
