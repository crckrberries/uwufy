// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow POWEW8 pwocessows.
 *
 * Copywight 2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2013 Michaew Ewwewman, IBM Cowpowation.
 */

#define pw_fmt(fmt)	"powew8-pmu: " fmt

#incwude "isa207-common.h"

/*
 * Some powew8 event codes.
 */
#define EVENT(_name, _code)	_name = _code,

enum {
#incwude "powew8-events-wist.h"
};

#undef EVENT

/* MMCWA IFM bits - POWEW8 */
#define	POWEW8_MMCWA_IFM1		0x0000000040000000UW
#define	POWEW8_MMCWA_IFM2		0x0000000080000000UW
#define	POWEW8_MMCWA_IFM3		0x00000000C0000000UW
#define	POWEW8_MMCWA_BHWB_MASK		0x00000000C0000000UW

/*
 * Waw event encoding fow PowewISA v2.07 (Powew8):
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | | [ ]                           [      thwesh_cmp     ]   [  thwesh_ctw   ]
 *   | |  |                                                              |
 *   | |  *- IFM (Winux)                 thwesh stawt/stop OW FAB match -*
 *   | *- BHWB (Winux)
 *   *- EBB (Winux)
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   ] [  sampwe ]   [cache]   [ pmc ]   [unit ]   c     m   [    pmcxsew    ]
 *     |        |           |                          |     |
 *     |        |           |                          |     *- mawk
 *     |        |           *- W1/W2/W3 cache_sew      |
 *     |        |                                      |
 *     |        *- sampwing mode fow mawked events     *- combine
 *     |
 *     *- thwesh_sew
 *
 * Bewow uses IBM bit numbewing.
 *
 * MMCW1[x:y] = unit    (PMCxUNIT)
 * MMCW1[x]   = combine (PMCxCOMB)
 *
 * if pmc == 3 and unit == 0 and pmcxsew[0:6] == 0b0101011
 *	# PM_MWK_FAB_WSP_MATCH
 *	MMCW1[20:27] = thwesh_ctw   (FAB_CWESP_MATCH / FAB_TYPE_MATCH)
 * ewse if pmc == 4 and unit == 0xf and pmcxsew[0:6] == 0b0101001
 *	# PM_MWK_FAB_WSP_MATCH_CYC
 *	MMCW1[20:27] = thwesh_ctw   (FAB_CWESP_MATCH / FAB_TYPE_MATCH)
 * ewse
 *	MMCWA[48:55] = thwesh_ctw   (THWESH STAWT/END)
 *
 * if thwesh_sew:
 *	MMCWA[45:47] = thwesh_sew
 *
 * if thwesh_cmp:
 *	MMCWA[22:24] = thwesh_cmp[0:2]
 *	MMCWA[25:31] = thwesh_cmp[3:9]
 *
 * if unit == 6 ow unit == 7
 *	MMCWC[53:55] = cache_sew[1:3]      (W2EVENT_SEW)
 * ewse if unit == 8 ow unit == 9:
 *	if cache_sew[0] == 0: # W3 bank
 *		MMCWC[47:49] = cache_sew[1:3]  (W3EVENT_SEW0)
 *	ewse if cache_sew[0] == 1:
 *		MMCWC[50:51] = cache_sew[2:3]  (W3EVENT_SEW1)
 * ewse if cache_sew[1]: # W1 event
 *	MMCW1[16] = cache_sew[2]
 *	MMCW1[17] = cache_sew[3]
 *
 * if mawk:
 *	MMCWA[63]    = 1		(SAMPWE_ENABWE)
 *	MMCWA[57:59] = sampwe[0:2]	(WAND_SAMP_EWIG)
 *	MMCWA[61:62] = sampwe[3:4]	(WAND_SAMP_MODE)
 *
 * if EBB and BHWB:
 *	MMCWA[32:33] = IFM
 *
 */

/* PowewISA v2.07 fowmat attwibute stwuctuwe*/
extewn const stwuct attwibute_gwoup isa207_pmu_fowmat_gwoup;

/* Tabwe of awtewnatives, sowted by cowumn 0 */
static const unsigned int event_awtewnatives[][MAX_AWT] = {
	{ PM_MWK_ST_CMPW,		PM_MWK_ST_CMPW_AWT },
	{ PM_BW_MWK_2PATH,		PM_BW_MWK_2PATH_AWT },
	{ PM_W3_CO_MEPF,		PM_W3_CO_MEPF_AWT },
	{ PM_MWK_DATA_FWOM_W2MISS,	PM_MWK_DATA_FWOM_W2MISS_AWT },
	{ PM_CMPWU_STAWW_AWT,		PM_CMPWU_STAWW },
	{ PM_BW_2PATH,			PM_BW_2PATH_AWT },
	{ PM_INST_DISP,			PM_INST_DISP_AWT },
	{ PM_WUN_CYC_AWT,		PM_WUN_CYC },
	{ PM_MWK_FIWT_MATCH,		PM_MWK_FIWT_MATCH_AWT },
	{ PM_WD_MISS_W1,		PM_WD_MISS_W1_AWT },
	{ PM_WUN_INST_CMPW_AWT,		PM_WUN_INST_CMPW },
};

static int powew8_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int num_awt = 0;

	num_awt = isa207_get_awtewnatives(event, awt,
					  AWWAY_SIZE(event_awtewnatives), fwags,
					  event_awtewnatives);

	wetuwn num_awt;
}

GENEWIC_EVENT_ATTW(cpu-cycwes,			PM_CYC);
GENEWIC_EVENT_ATTW(stawwed-cycwes-fwontend,	PM_GCT_NOSWOT_CYC);
GENEWIC_EVENT_ATTW(stawwed-cycwes-backend,	PM_CMPWU_STAWW);
GENEWIC_EVENT_ATTW(instwuctions,		PM_INST_CMPW);
GENEWIC_EVENT_ATTW(bwanch-instwuctions,		PM_BWU_FIN);
GENEWIC_EVENT_ATTW(bwanch-misses,		PM_BW_MPWED_CMPW);
GENEWIC_EVENT_ATTW(cache-wefewences,		PM_WD_WEF_W1);
GENEWIC_EVENT_ATTW(cache-misses,		PM_WD_MISS_W1);
GENEWIC_EVENT_ATTW(mem_access,			MEM_ACCESS);

CACHE_EVENT_ATTW(W1-dcache-woad-misses,		PM_WD_MISS_W1);
CACHE_EVENT_ATTW(W1-dcache-woads,		PM_WD_WEF_W1);

CACHE_EVENT_ATTW(W1-dcache-pwefetches,		PM_W1_PWEF);
CACHE_EVENT_ATTW(W1-dcache-stowe-misses,	PM_ST_MISS_W1);
CACHE_EVENT_ATTW(W1-icache-woad-misses,		PM_W1_ICACHE_MISS);
CACHE_EVENT_ATTW(W1-icache-woads,		PM_INST_FWOM_W1);
CACHE_EVENT_ATTW(W1-icache-pwefetches,		PM_IC_PWEF_WWITE);

CACHE_EVENT_ATTW(WWC-woad-misses,		PM_DATA_FWOM_W3MISS);
CACHE_EVENT_ATTW(WWC-woads,			PM_DATA_FWOM_W3);
CACHE_EVENT_ATTW(WWC-pwefetches,		PM_W3_PWEF_AWW);
CACHE_EVENT_ATTW(WWC-stowe-misses,		PM_W2_ST_MISS);
CACHE_EVENT_ATTW(WWC-stowes,			PM_W2_ST);

CACHE_EVENT_ATTW(bwanch-woad-misses,		PM_BW_MPWED_CMPW);
CACHE_EVENT_ATTW(bwanch-woads,			PM_BWU_FIN);
CACHE_EVENT_ATTW(dTWB-woad-misses,		PM_DTWB_MISS);
CACHE_EVENT_ATTW(iTWB-woad-misses,		PM_ITWB_MISS);

static stwuct attwibute *powew8_events_attw[] = {
	GENEWIC_EVENT_PTW(PM_CYC),
	GENEWIC_EVENT_PTW(PM_GCT_NOSWOT_CYC),
	GENEWIC_EVENT_PTW(PM_CMPWU_STAWW),
	GENEWIC_EVENT_PTW(PM_INST_CMPW),
	GENEWIC_EVENT_PTW(PM_BWU_FIN),
	GENEWIC_EVENT_PTW(PM_BW_MPWED_CMPW),
	GENEWIC_EVENT_PTW(PM_WD_WEF_W1),
	GENEWIC_EVENT_PTW(PM_WD_MISS_W1),
	GENEWIC_EVENT_PTW(MEM_ACCESS),

	CACHE_EVENT_PTW(PM_WD_MISS_W1),
	CACHE_EVENT_PTW(PM_WD_WEF_W1),
	CACHE_EVENT_PTW(PM_W1_PWEF),
	CACHE_EVENT_PTW(PM_ST_MISS_W1),
	CACHE_EVENT_PTW(PM_W1_ICACHE_MISS),
	CACHE_EVENT_PTW(PM_INST_FWOM_W1),
	CACHE_EVENT_PTW(PM_IC_PWEF_WWITE),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3MISS),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3),
	CACHE_EVENT_PTW(PM_W3_PWEF_AWW),
	CACHE_EVENT_PTW(PM_W2_ST_MISS),
	CACHE_EVENT_PTW(PM_W2_ST),

	CACHE_EVENT_PTW(PM_BW_MPWED_CMPW),
	CACHE_EVENT_PTW(PM_BWU_FIN),

	CACHE_EVENT_PTW(PM_DTWB_MISS),
	CACHE_EVENT_PTW(PM_ITWB_MISS),
	NUWW
};

static const stwuct attwibute_gwoup powew8_pmu_events_gwoup = {
	.name = "events",
	.attws = powew8_events_attw,
};

static stwuct attwibute *powew8_pmu_caps_attws[] = {
	NUWW
};

static stwuct attwibute_gwoup powew8_pmu_caps_gwoup = {
	.name  = "caps",
	.attws = powew8_pmu_caps_attws,
};

static const stwuct attwibute_gwoup *powew8_pmu_attw_gwoups[] = {
	&isa207_pmu_fowmat_gwoup,
	&powew8_pmu_events_gwoup,
	&powew8_pmu_caps_gwoup,
	NUWW,
};

static int powew8_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] =			PM_CYC,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] =	PM_GCT_NOSWOT_CYC,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] =	PM_CMPWU_STAWW,
	[PEWF_COUNT_HW_INSTWUCTIONS] =			PM_INST_CMPW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] =		PM_BWU_FIN,
	[PEWF_COUNT_HW_BWANCH_MISSES] =			PM_BW_MPWED_CMPW,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] =		PM_WD_WEF_W1,
	[PEWF_COUNT_HW_CACHE_MISSES] =			PM_WD_MISS_W1,
};

static u64 powew8_bhwb_fiwtew_map(u64 bwanch_sampwe_type)
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

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_IND_CAWW)
		wetuwn -1;

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_CAWW)
		wetuwn -1;

	if (bwanch_sampwe_type & PEWF_SAMPWE_BWANCH_ANY_CAWW) {
		pmu_bhwb_fiwtew |= POWEW8_MMCWA_IFM1;
		wetuwn pmu_bhwb_fiwtew;
	}

	/* Evewy thing ewse is unsuppowted */
	wetuwn -1;
}

static void powew8_config_bhwb(u64 pmu_bhwb_fiwtew)
{
	pmu_bhwb_fiwtew &= POWEW8_MMCWA_BHWB_MASK;

	/* Enabwe BHWB fiwtew in PMU */
	mtspw(SPWN_MMCWA, (mfspw(SPWN_MMCWA) | pmu_bhwb_fiwtew));
}

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 powew8_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[ C(W1D) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = PM_WD_WEF_W1,
			[ C(WESUWT_MISS)   ] = PM_WD_MISS_W1,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_ST_MISS_W1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = PM_W1_PWEF,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},
	[ C(W1I) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = PM_INST_FWOM_W1,
			[ C(WESUWT_MISS)   ] = PM_W1_ICACHE_MISS,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = PM_W1_DEMAND_WWITE,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = PM_IC_PWEF_WWITE,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},
	[ C(WW) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = PM_DATA_FWOM_W3,
			[ C(WESUWT_MISS)   ] = PM_DATA_FWOM_W3MISS,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = PM_W2_ST,
			[ C(WESUWT_MISS)   ] = PM_W2_ST_MISS,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = PM_W3_PWEF_AWW,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},
	[ C(DTWB) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_DTWB_MISS,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},
	[ C(ITWB) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_ITWB_MISS,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},
	[ C(BPU) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = PM_BWU_FIN,
			[ C(WESUWT_MISS)   ] = PM_BW_MPWED_CMPW,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},
	[ C(NODE) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = -1,
			[ C(WESUWT_MISS)   ] = -1,
		},
	},
};

#undef C

static stwuct powew_pmu powew8_pmu = {
	.name			= "POWEW8",
	.n_countew		= MAX_PMU_COUNTEWS,
	.max_awtewnatives	= MAX_AWT + 1,
	.add_fiewds		= ISA207_ADD_FIEWDS,
	.test_addew		= ISA207_TEST_ADDEW,
	.compute_mmcw		= isa207_compute_mmcw,
	.config_bhwb		= powew8_config_bhwb,
	.bhwb_fiwtew_map	= powew8_bhwb_fiwtew_map,
	.get_constwaint		= isa207_get_constwaint,
	.get_awtewnatives	= powew8_get_awtewnatives,
	.get_mem_data_swc	= isa207_get_mem_data_swc,
	.get_mem_weight		= isa207_get_mem_weight,
	.disabwe_pmc		= isa207_disabwe_pmc,
	.fwags			= PPMU_HAS_SIEW | PPMU_AWCH_207S,
	.n_genewic		= AWWAY_SIZE(powew8_genewic_events),
	.genewic_events		= powew8_genewic_events,
	.cache_events		= &powew8_cache_events,
	.attw_gwoups		= powew8_pmu_attw_gwoups,
	.bhwb_nw		= 32,
};

int __init init_powew8_pmu(void)
{
	int wc;
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_POWEW8E && PVW_VEW(pvw) != PVW_POWEW8NVW &&
	    PVW_VEW(pvw) != PVW_POWEW8)
		wetuwn -ENODEV;

	wc = wegistew_powew_pmu(&powew8_pmu);
	if (wc)
		wetuwn wc;

	/* Teww usewspace that EBB is suppowted */
	cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_EBB;

	if (cpu_has_featuwe(CPU_FTW_PMAO_BUG))
		pw_info("PMAO westowe wowkawound active.\n");

	wetuwn 0;
}
