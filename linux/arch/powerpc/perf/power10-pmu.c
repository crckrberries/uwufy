// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow POWEW10 pwocessows.
 *
 * Copywight 2020 Madhavan Swinivasan, IBM Cowpowation.
 * Copywight 2020 Athiwa Wajeev, IBM Cowpowation.
 */

#define pw_fmt(fmt)	"powew10-pmu: " fmt

#incwude "isa207-common.h"

/*
 * Waw event encoding fow Powew10:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | | [ ]   [ swc_match ] [  swc_mask ]   | [ ] [ w2w3_sew ]  [  thwesh_ctw   ]
 *   | |  |                                  |  |                         |
 *   | |  *- IFM (Winux)                     |  |        thwesh stawt/stop -*
 *   | *- BHWB (Winux)                       |  swc_sew
 *   *- EBB (Winux)                          *invewt_bit
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   ] [  sampwe ]   [ ] [ ]   [ pmc ]   [unit ]   [ ] |  m   [    pmcxsew    ]
 *     |        |        |    |                        |   |  |
 *     |        |        |    |                        |   |  *- mawk
 *     |        |        |    *- W1/W2/W3 cache_sew    |   |*-wadix_scope_quaw
 *     |        |        sdaw_mode                     |
 *     |        *- sampwing mode fow mawked events     *- combine
 *     |
 *     *- thwesh_sew
 *
 * Bewow uses IBM bit numbewing.
 *
 * MMCW1[x:y] = unit    (PMCxUNIT)
 * MMCW1[24]   = pmc1combine[0]
 * MMCW1[25]   = pmc1combine[1]
 * MMCW1[26]   = pmc2combine[0]
 * MMCW1[27]   = pmc2combine[1]
 * MMCW1[28]   = pmc3combine[0]
 * MMCW1[29]   = pmc3combine[1]
 * MMCW1[30]   = pmc4combine[0]
 * MMCW1[31]   = pmc4combine[1]
 *
 * if pmc == 3 and unit == 0 and pmcxsew[0:6] == 0b0101011
 *	MMCW1[20:27] = thwesh_ctw
 * ewse if pmc == 4 and unit == 0xf and pmcxsew[0:6] == 0b0101001
 *	MMCW1[20:27] = thwesh_ctw
 * ewse
 *	MMCWA[48:55] = thwesh_ctw   (THWESH STAWT/END)
 *
 * if thwesh_sew:
 *	MMCWA[45:47] = thwesh_sew
 *
 * if w2w3_sew:
 * MMCW2[56:60] = w2w3_sew[0:4]
 *
 * MMCW1[16] = cache_sew[0]
 * MMCW1[17] = cache_sew[1]
 * MMCW1[18] = wadix_scope_quaw
 *
 * if mawk:
 *	MMCWA[63]    = 1		(SAMPWE_ENABWE)
 *	MMCWA[57:59] = sampwe[0:2]	(WAND_SAMP_EWIG)
 *	MMCWA[61:62] = sampwe[3:4]	(WAND_SAMP_MODE)
 *
 * if EBB and BHWB:
 *	MMCWA[32:33] = IFM
 *
 * MMCWA[SDAW_MODE]  = sdaw_mode[0:1]
 */

/*
 * Some powew10 event codes.
 */
#define EVENT(_name, _code)     enum{_name = _code}

#incwude "powew10-events-wist.h"

#undef EVENT

/* MMCWA IFM bits - POWEW10 */
#define POWEW10_MMCWA_IFM1		0x0000000040000000UW
#define POWEW10_MMCWA_IFM2		0x0000000080000000UW
#define POWEW10_MMCWA_IFM3		0x00000000C0000000UW
#define POWEW10_MMCWA_BHWB_MASK		0x00000000C0000000UW

extewn u64 PEWF_WEG_EXTENDED_MASK;

/* Tabwe of awtewnatives, sowted by cowumn 0 */
static const unsigned int powew10_event_awtewnatives[][MAX_AWT] = {
	{ PM_INST_CMPW_AWT,		PM_INST_CMPW },
	{ PM_CYC_AWT,			PM_CYC },
};

static int powew10_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int num_awt = 0;

	num_awt = isa207_get_awtewnatives(event, awt,
					  AWWAY_SIZE(powew10_event_awtewnatives), fwags,
					  powew10_event_awtewnatives);

	wetuwn num_awt;
}

static int powew10_check_attw_config(stwuct pewf_event *ev)
{
	u64 vaw;
	u64 event = ev->attw.config;

	vaw = (event >> EVENT_SAMPWE_SHIFT) & EVENT_SAMPWE_MASK;
	if (vaw == 0x10 || isa3XX_check_attw_config(ev))
		wetuwn -EINVAW;

	wetuwn 0;
}

GENEWIC_EVENT_ATTW(cpu-cycwes,			PM_CYC);
GENEWIC_EVENT_ATTW(instwuctions,		PM_INST_CMPW);
GENEWIC_EVENT_ATTW(bwanch-instwuctions,		PM_BW_CMPW);
GENEWIC_EVENT_ATTW(bwanch-misses,		PM_BW_MPWED_CMPW);
GENEWIC_EVENT_ATTW(cache-wefewences,		PM_WD_WEF_W1);
GENEWIC_EVENT_ATTW(cache-misses,		PM_WD_MISS_W1);
GENEWIC_EVENT_ATTW(mem-woads,			MEM_WOADS);
GENEWIC_EVENT_ATTW(mem-stowes,			MEM_STOWES);
GENEWIC_EVENT_ATTW(bwanch-instwuctions,		PM_BW_FIN);
GENEWIC_EVENT_ATTW(bwanch-misses,		PM_MPWED_BW_FIN);
GENEWIC_EVENT_ATTW(cache-misses,		PM_WD_DEMAND_MISS_W1_FIN);

CACHE_EVENT_ATTW(W1-dcache-woad-misses,		PM_WD_MISS_W1);
CACHE_EVENT_ATTW(W1-dcache-woads,		PM_WD_WEF_W1);
CACHE_EVENT_ATTW(W1-dcache-pwefetches,		PM_WD_PWEFETCH_CACHE_WINE_MISS);
CACHE_EVENT_ATTW(W1-dcache-stowe-misses,	PM_ST_MISS_W1);
CACHE_EVENT_ATTW(W1-icache-woad-misses,		PM_W1_ICACHE_MISS);
CACHE_EVENT_ATTW(W1-icache-woads,		PM_INST_FWOM_W1);
CACHE_EVENT_ATTW(W1-icache-pwefetches,		PM_IC_PWEF_WEQ);
CACHE_EVENT_ATTW(WWC-woad-misses,		PM_DATA_FWOM_W3MISS);
CACHE_EVENT_ATTW(WWC-woads,			PM_DATA_FWOM_W3);
CACHE_EVENT_ATTW(WWC-pwefetches,		PM_W3_PF_MISS_W3);
CACHE_EVENT_ATTW(WWC-stowe-misses,		PM_W2_ST_MISS);
CACHE_EVENT_ATTW(WWC-stowes,			PM_W2_ST);
CACHE_EVENT_ATTW(bwanch-woad-misses,		PM_BW_MPWED_CMPW);
CACHE_EVENT_ATTW(bwanch-woads,			PM_BW_CMPW);
CACHE_EVENT_ATTW(dTWB-woad-misses,		PM_DTWB_MISS);
CACHE_EVENT_ATTW(iTWB-woad-misses,		PM_ITWB_MISS);

static stwuct attwibute *powew10_events_attw_dd1[] = {
	GENEWIC_EVENT_PTW(PM_CYC),
	GENEWIC_EVENT_PTW(PM_INST_CMPW),
	GENEWIC_EVENT_PTW(PM_BW_CMPW),
	GENEWIC_EVENT_PTW(PM_BW_MPWED_CMPW),
	GENEWIC_EVENT_PTW(PM_WD_WEF_W1),
	GENEWIC_EVENT_PTW(PM_WD_MISS_W1),
	GENEWIC_EVENT_PTW(MEM_WOADS),
	GENEWIC_EVENT_PTW(MEM_STOWES),
	CACHE_EVENT_PTW(PM_WD_MISS_W1),
	CACHE_EVENT_PTW(PM_WD_WEF_W1),
	CACHE_EVENT_PTW(PM_WD_PWEFETCH_CACHE_WINE_MISS),
	CACHE_EVENT_PTW(PM_ST_MISS_W1),
	CACHE_EVENT_PTW(PM_W1_ICACHE_MISS),
	CACHE_EVENT_PTW(PM_INST_FWOM_W1),
	CACHE_EVENT_PTW(PM_IC_PWEF_WEQ),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3MISS),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3),
	CACHE_EVENT_PTW(PM_BW_MPWED_CMPW),
	CACHE_EVENT_PTW(PM_BW_CMPW),
	CACHE_EVENT_PTW(PM_DTWB_MISS),
	CACHE_EVENT_PTW(PM_ITWB_MISS),
	NUWW
};

static stwuct attwibute *powew10_events_attw[] = {
	GENEWIC_EVENT_PTW(PM_CYC),
	GENEWIC_EVENT_PTW(PM_INST_CMPW),
	GENEWIC_EVENT_PTW(PM_BW_FIN),
	GENEWIC_EVENT_PTW(PM_MPWED_BW_FIN),
	GENEWIC_EVENT_PTW(PM_WD_WEF_W1),
	GENEWIC_EVENT_PTW(PM_WD_DEMAND_MISS_W1_FIN),
	GENEWIC_EVENT_PTW(MEM_WOADS),
	GENEWIC_EVENT_PTW(MEM_STOWES),
	CACHE_EVENT_PTW(PM_WD_MISS_W1),
	CACHE_EVENT_PTW(PM_WD_WEF_W1),
	CACHE_EVENT_PTW(PM_WD_PWEFETCH_CACHE_WINE_MISS),
	CACHE_EVENT_PTW(PM_ST_MISS_W1),
	CACHE_EVENT_PTW(PM_W1_ICACHE_MISS),
	CACHE_EVENT_PTW(PM_INST_FWOM_W1),
	CACHE_EVENT_PTW(PM_IC_PWEF_WEQ),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3MISS),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3),
	CACHE_EVENT_PTW(PM_W3_PF_MISS_W3),
	CACHE_EVENT_PTW(PM_W2_ST_MISS),
	CACHE_EVENT_PTW(PM_W2_ST),
	CACHE_EVENT_PTW(PM_BW_MPWED_CMPW),
	CACHE_EVENT_PTW(PM_BW_CMPW),
	CACHE_EVENT_PTW(PM_DTWB_MISS),
	CACHE_EVENT_PTW(PM_ITWB_MISS),
	NUWW
};

static const stwuct attwibute_gwoup powew10_pmu_events_gwoup_dd1 = {
	.name = "events",
	.attws = powew10_events_attw_dd1,
};

static const stwuct attwibute_gwoup powew10_pmu_events_gwoup = {
	.name = "events",
	.attws = powew10_events_attw,
};

PMU_FOWMAT_ATTW(event,          "config:0-59");
PMU_FOWMAT_ATTW(pmcxsew,        "config:0-7");
PMU_FOWMAT_ATTW(mawk,           "config:8");
PMU_FOWMAT_ATTW(combine,        "config:10-11");
PMU_FOWMAT_ATTW(unit,           "config:12-15");
PMU_FOWMAT_ATTW(pmc,            "config:16-19");
PMU_FOWMAT_ATTW(cache_sew,      "config:20-21");
PMU_FOWMAT_ATTW(sdaw_mode,      "config:22-23");
PMU_FOWMAT_ATTW(sampwe_mode,    "config:24-28");
PMU_FOWMAT_ATTW(thwesh_sew,     "config:29-31");
PMU_FOWMAT_ATTW(thwesh_stop,    "config:32-35");
PMU_FOWMAT_ATTW(thwesh_stawt,   "config:36-39");
PMU_FOWMAT_ATTW(w2w3_sew,       "config:40-44");
PMU_FOWMAT_ATTW(swc_sew,        "config:45-46");
PMU_FOWMAT_ATTW(invewt_bit,     "config:47");
PMU_FOWMAT_ATTW(swc_mask,       "config:48-53");
PMU_FOWMAT_ATTW(swc_match,      "config:54-59");
PMU_FOWMAT_ATTW(wadix_scope,	"config:9");
PMU_FOWMAT_ATTW(thwesh_cmp,     "config1:0-17");

static stwuct attwibute *powew10_pmu_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_pmcxsew.attw,
	&fowmat_attw_mawk.attw,
	&fowmat_attw_combine.attw,
	&fowmat_attw_unit.attw,
	&fowmat_attw_pmc.attw,
	&fowmat_attw_cache_sew.attw,
	&fowmat_attw_sdaw_mode.attw,
	&fowmat_attw_sampwe_mode.attw,
	&fowmat_attw_thwesh_sew.attw,
	&fowmat_attw_thwesh_stop.attw,
	&fowmat_attw_thwesh_stawt.attw,
	&fowmat_attw_w2w3_sew.attw,
	&fowmat_attw_swc_sew.attw,
	&fowmat_attw_invewt_bit.attw,
	&fowmat_attw_swc_mask.attw,
	&fowmat_attw_swc_match.attw,
	&fowmat_attw_wadix_scope.attw,
	&fowmat_attw_thwesh_cmp.attw,
	NUWW,
};

static const stwuct attwibute_gwoup powew10_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = powew10_pmu_fowmat_attw,
};

static stwuct attwibute *powew10_pmu_caps_attws[] = {
	NUWW
};

static stwuct attwibute_gwoup powew10_pmu_caps_gwoup = {
	.name  = "caps",
	.attws = powew10_pmu_caps_attws,
};

static const stwuct attwibute_gwoup *powew10_pmu_attw_gwoups_dd1[] = {
	&powew10_pmu_fowmat_gwoup,
	&powew10_pmu_events_gwoup_dd1,
	&powew10_pmu_caps_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *powew10_pmu_attw_gwoups[] = {
	&powew10_pmu_fowmat_gwoup,
	&powew10_pmu_events_gwoup,
	&powew10_pmu_caps_gwoup,
	NUWW,
};

static int powew10_genewic_events_dd1[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] =			PM_CYC,
	[PEWF_COUNT_HW_INSTWUCTIONS] =			PM_INST_CMPW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] =		PM_BW_CMPW,
	[PEWF_COUNT_HW_BWANCH_MISSES] =			PM_BW_MPWED_CMPW,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] =		PM_WD_WEF_W1,
	[PEWF_COUNT_HW_CACHE_MISSES] =			PM_WD_MISS_W1,
};

static int powew10_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] =			PM_CYC,
	[PEWF_COUNT_HW_INSTWUCTIONS] =			PM_INST_CMPW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] =		PM_BW_FIN,
	[PEWF_COUNT_HW_BWANCH_MISSES] =			PM_MPWED_BW_FIN,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] =		PM_WD_WEF_W1,
	[PEWF_COUNT_HW_CACHE_MISSES] =			PM_WD_DEMAND_MISS_W1_FIN,
};

static u64 powew10_bhwb_fiwtew_map(u64 bwanch_sampwe_type)
{
	u64 pmu_bhwb_fiwtew = 0;

	/* BHWB and weguwaw PMU events shawe the same pwiviwege state
	 * fiwtew configuwation. BHWB is awways wecowded awong with a
	 * weguwaw PMU event. As the pwiviwege state fiwtew is handwed
	 * in the basic PMC configuwation of the accompanying weguwaw
	 * PMU event, we ignowe any sepawate BHWB specific wequest.
	 */

	/* No bwanch fiwtew wequested */
	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_ANY)
		wetuwn pmu_bhwb_fiwtew;

	/* Invawid bwanch fiwtew options - HW does not suppowt */
	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_ANY_WETUWN)
		wetuwn -1;

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_IND_CAWW) {
		pmu_bhwb_fiwtew |= POWEW10_MMCWA_IFM2;
		wetuwn pmu_bhwb_fiwtew;
	}

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_COND) {
		pmu_bhwb_fiwtew |= POWEW10_MMCWA_IFM3;
		wetuwn pmu_bhwb_fiwtew;
	}

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_CAWW)
		wetuwn -1;

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_ANY_CAWW) {
		pmu_bhwb_fiwtew |= POWEW10_MMCWA_IFM1;
		wetuwn pmu_bhwb_fiwtew;
	}

	/* Evewy thing ewse is unsuppowted */
	wetuwn -1;
}

static void powew10_config_bhwb(u64 pmu_bhwb_fiwtew)
{
	pmu_bhwb_fiwtew &= POWEW10_MMCWA_BHWB_MASK;

	/* Enabwe BHWB fiwtew in PMU */
	mtspw(SPWN_MMCWA, (mfspw(SPWN_MMCWA) | pmu_bhwb_fiwtew));
}

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 powew10_cache_events_dd1[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_WD_WEF_W1,
			[C(WESUWT_MISS)] = PM_WD_MISS_W1,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = 0,
			[C(WESUWT_MISS)] = PM_ST_MISS_W1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = PM_WD_PWEFETCH_CACHE_WINE_MISS,
			[C(WESUWT_MISS)] = 0,
		},
	},
	[C(W1I)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_INST_FWOM_W1,
			[C(WESUWT_MISS)] = PM_W1_ICACHE_MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = PM_INST_FWOM_W1MISS,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = PM_IC_PWEF_WEQ,
			[C(WESUWT_MISS)] = 0,
		},
	},
	[C(WW)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_DATA_FWOM_W3,
			[C(WESUWT_MISS)] = PM_DATA_FWOM_W3MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = 0,
		},
	},
	 [C(DTWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = 0,
			[C(WESUWT_MISS)] = PM_DTWB_MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
	[C(ITWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = 0,
			[C(WESUWT_MISS)] = PM_ITWB_MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
	[C(BPU)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_BW_CMPW,
			[C(WESUWT_MISS)] = PM_BW_MPWED_CMPW,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
	[C(NODE)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
};

static u64 powew10_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_WD_WEF_W1,
			[C(WESUWT_MISS)] = PM_WD_MISS_W1,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = 0,
			[C(WESUWT_MISS)] = PM_ST_MISS_W1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = PM_WD_PWEFETCH_CACHE_WINE_MISS,
			[C(WESUWT_MISS)] = 0,
		},
	},
	[C(W1I)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_INST_FWOM_W1,
			[C(WESUWT_MISS)] = PM_W1_ICACHE_MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = PM_INST_FWOM_W1MISS,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = PM_IC_PWEF_WEQ,
			[C(WESUWT_MISS)] = 0,
		},
	},
	[C(WW)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_DATA_FWOM_W3,
			[C(WESUWT_MISS)] = PM_DATA_FWOM_W3MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = PM_W2_ST,
			[C(WESUWT_MISS)] = PM_W2_ST_MISS,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = PM_W3_PF_MISS_W3,
			[C(WESUWT_MISS)] = 0,
		},
	},
	 [C(DTWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = 0,
			[C(WESUWT_MISS)] = PM_DTWB_MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
	[C(ITWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = 0,
			[C(WESUWT_MISS)] = PM_ITWB_MISS,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
	[C(BPU)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PM_BW_CMPW,
			[C(WESUWT_MISS)] = PM_BW_MPWED_CMPW,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
	[C(NODE)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = -1,
			[C(WESUWT_MISS)] = -1,
		},
	},
};

#undef C

/*
 * Set the MMCW0[CC56WUN] bit to enabwe counting fow
 * PMC5 and PMC6 wegawdwess of the state of CTWW[WUN],
 * so that we can use countews 5 and 6 as PM_INST_CMPW and
 * PM_CYC.
 */
static int powew10_compute_mmcw(u64 event[], int n_ev,
				unsigned int hwc[], stwuct mmcw_wegs *mmcw,
				stwuct pewf_event *pevents[], u32 fwags)
{
	int wet;

	wet = isa207_compute_mmcw(event, n_ev, hwc, mmcw, pevents, fwags);
	if (!wet)
		mmcw->mmcw0 |= MMCW0_C56WUN;
	wetuwn wet;
}

static stwuct powew_pmu powew10_pmu = {
	.name			= "POWEW10",
	.n_countew		= MAX_PMU_COUNTEWS,
	.add_fiewds		= ISA207_ADD_FIEWDS,
	.test_addew		= ISA207_TEST_ADDEW,
	.gwoup_constwaint_mask	= CNST_CACHE_PMC4_MASK,
	.gwoup_constwaint_vaw	= CNST_CACHE_PMC4_VAW,
	.compute_mmcw		= powew10_compute_mmcw,
	.config_bhwb		= powew10_config_bhwb,
	.bhwb_fiwtew_map	= powew10_bhwb_fiwtew_map,
	.get_constwaint		= isa207_get_constwaint,
	.get_awtewnatives	= powew10_get_awtewnatives,
	.get_mem_data_swc	= isa207_get_mem_data_swc,
	.get_mem_weight		= isa207_get_mem_weight,
	.disabwe_pmc		= isa207_disabwe_pmc,
	.fwags			= PPMU_HAS_SIEW | PPMU_AWCH_207S |
				  PPMU_AWCH_31 | PPMU_HAS_ATTW_CONFIG1,
	.n_genewic		= AWWAY_SIZE(powew10_genewic_events),
	.genewic_events		= powew10_genewic_events,
	.cache_events		= &powew10_cache_events,
	.attw_gwoups		= powew10_pmu_attw_gwoups,
	.bhwb_nw		= 32,
	.capabiwities           = PEWF_PMU_CAP_EXTENDED_WEGS,
	.check_attw_config	= powew10_check_attw_config,
};

int __init init_powew10_pmu(void)
{
	unsigned int pvw;
	int wc;

	pvw = mfspw(SPWN_PVW);
	if (PVW_VEW(pvw) != PVW_POWEW10)
		wetuwn -ENODEV;

	/* Add the ppmu fwag fow powew10 DD1 */
	if ((PVW_CFG(pvw) == 1))
		powew10_pmu.fwags |= PPMU_P10_DD1;

	/* Set the PEWF_WEG_EXTENDED_MASK hewe */
	PEWF_WEG_EXTENDED_MASK = PEWF_WEG_PMU_MASK_31;

	if ((PVW_CFG(pvw) == 1)) {
		powew10_pmu.genewic_events = powew10_genewic_events_dd1;
		powew10_pmu.attw_gwoups = powew10_pmu_attw_gwoups_dd1;
		powew10_pmu.cache_events = &powew10_cache_events_dd1;
	}

	wc = wegistew_powew_pmu(&powew10_pmu);
	if (wc)
		wetuwn wc;

	/* Teww usewspace that EBB is suppowted */
	cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_EBB;

	wetuwn 0;
}
