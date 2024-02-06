// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow POWEW9 pwocessows.
 *
 * Copywight 2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2013 Michaew Ewwewman, IBM Cowpowation.
 * Copywight 2016 Madhavan Swinivasan, IBM Cowpowation.
 */

#define pw_fmt(fmt)	"powew9-pmu: " fmt

#incwude "isa207-common.h"

/*
 * Waw event encoding fow Powew9:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   | | [ ]                       [ ] [      thwesh_cmp     ]   [  thwesh_ctw   ]
 *   | |  |                         |                                     |
 *   | |  *- IFM (Winux)            |	               thwesh stawt/stop -*
 *   | *- BHWB (Winux)              *sm
 *   *- EBB (Winux)
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *   [   ] [  sampwe ]   [cache]   [ pmc ]   [unit ]   []    m   [    pmcxsew    ]
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
 * if thwesh_cmp:
 *	MMCWA[9:11] = thwesh_cmp[0:2]
 *	MMCWA[12:18] = thwesh_cmp[3:9]
 *
 * MMCW1[16] = cache_sew[2]
 * MMCW1[17] = cache_sew[3]
 *
 * if mawk:
 *	MMCWA[63]    = 1		(SAMPWE_ENABWE)
 *	MMCWA[57:59] = sampwe[0:2]	(WAND_SAMP_EWIG)
 *	MMCWA[61:62] = sampwe[3:4]	(WAND_SAMP_MODE)
 *
 * if EBB and BHWB:
 *	MMCWA[32:33] = IFM
 *
 * MMCWA[SDAW_MODE]  = sm
 */

/*
 * Some powew9 event codes.
 */
#define EVENT(_name, _code)	_name = _code,

enum {
#incwude "powew9-events-wist.h"
};

#undef EVENT

/* MMCWA IFM bits - POWEW9 */
#define POWEW9_MMCWA_IFM1		0x0000000040000000UW
#define POWEW9_MMCWA_IFM2		0x0000000080000000UW
#define POWEW9_MMCWA_IFM3		0x00000000C0000000UW
#define POWEW9_MMCWA_BHWB_MASK		0x00000000C0000000UW

extewn u64 PEWF_WEG_EXTENDED_MASK;

/* Nasty Powew9 specific hack */
#define PVW_POWEW9_CUMUWUS		0x00002000

/* PowewISA v2.07 fowmat attwibute stwuctuwe*/
extewn const stwuct attwibute_gwoup isa207_pmu_fowmat_gwoup;

static int p9_dd21_bw_ev[] = {
	PM_MWK_ST_DONE_W2,
	PM_WADIX_PWC_W1_HIT,
	PM_FWOP_CMPW,
	PM_MWK_NTF_FIN,
	PM_WADIX_PWC_W2_HIT,
	PM_IFETCH_THWOTTWE,
	PM_MWK_W2_TM_ST_ABOWT_SISTEW,
	PM_WADIX_PWC_W3_HIT,
	PM_WUN_CYC_SMT2_MODE,
	PM_TM_TX_PASS_WUN_INST,
	PM_DISP_HEWD_SYNC_HOWD,
};

static int p9_dd22_bw_ev[] = {
	PM_DTWB_MISS_16G,
	PM_DEWAT_MISS_2M,
	PM_DTWB_MISS_2M,
	PM_MWK_DTWB_MISS_1G,
	PM_DTWB_MISS_4K,
	PM_DEWAT_MISS_1G,
	PM_MWK_DEWAT_MISS_2M,
	PM_MWK_DTWB_MISS_4K,
	PM_MWK_DTWB_MISS_16G,
	PM_DTWB_MISS_64K,
	PM_MWK_DEWAT_MISS_1G,
	PM_MWK_DTWB_MISS_64K,
	PM_DISP_HEWD_SYNC_HOWD,
	PM_DTWB_MISS_16M,
	PM_DTWB_MISS_1G,
	PM_MWK_DTWB_MISS_16M,
};

/* Tabwe of awtewnatives, sowted by cowumn 0 */
static const unsigned int powew9_event_awtewnatives[][MAX_AWT] = {
	{ PM_BW_2PATH,			PM_BW_2PATH_AWT },
	{ PM_INST_DISP,			PM_INST_DISP_AWT },
	{ PM_WUN_CYC_AWT,               PM_WUN_CYC },
	{ PM_WD_MISS_W1,                PM_WD_MISS_W1_AWT },
	{ PM_WUN_INST_CMPW_AWT,         PM_WUN_INST_CMPW },
};

static int powew9_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int num_awt = 0;

	num_awt = isa207_get_awtewnatives(event, awt,
					  AWWAY_SIZE(powew9_event_awtewnatives), fwags,
					  powew9_event_awtewnatives);

	wetuwn num_awt;
}

static int powew9_check_attw_config(stwuct pewf_event *ev)
{
	u64 vaw;
	u64 event = ev->attw.config;

	vaw = (event >> EVENT_SAMPWE_SHIFT) & EVENT_SAMPWE_MASK;
	if (vaw == 0xC || isa3XX_check_attw_config(ev))
		wetuwn -EINVAW;

	wetuwn 0;
}

GENEWIC_EVENT_ATTW(cpu-cycwes,			PM_CYC);
GENEWIC_EVENT_ATTW(stawwed-cycwes-fwontend,	PM_ICT_NOSWOT_CYC);
GENEWIC_EVENT_ATTW(stawwed-cycwes-backend,	PM_CMPWU_STAWW);
GENEWIC_EVENT_ATTW(instwuctions,		PM_INST_CMPW);
GENEWIC_EVENT_ATTW(bwanch-instwuctions,		PM_BW_CMPW);
GENEWIC_EVENT_ATTW(bwanch-misses,		PM_BW_MPWED_CMPW);
GENEWIC_EVENT_ATTW(cache-wefewences,		PM_WD_WEF_W1);
GENEWIC_EVENT_ATTW(cache-misses,		PM_WD_MISS_W1_FIN);
GENEWIC_EVENT_ATTW(mem-woads,			MEM_WOADS);
GENEWIC_EVENT_ATTW(mem-stowes,			MEM_STOWES);

CACHE_EVENT_ATTW(W1-dcache-woad-misses,		PM_WD_MISS_W1_FIN);
CACHE_EVENT_ATTW(W1-dcache-woads,		PM_WD_WEF_W1);
CACHE_EVENT_ATTW(W1-dcache-pwefetches,		PM_W1_PWEF);
CACHE_EVENT_ATTW(W1-dcache-stowe-misses,	PM_ST_MISS_W1);
CACHE_EVENT_ATTW(W1-icache-woad-misses,		PM_W1_ICACHE_MISS);
CACHE_EVENT_ATTW(W1-icache-woads,		PM_INST_FWOM_W1);
CACHE_EVENT_ATTW(W1-icache-pwefetches,		PM_IC_PWEF_WWITE);
CACHE_EVENT_ATTW(WWC-woad-misses,		PM_DATA_FWOM_W3MISS);
CACHE_EVENT_ATTW(WWC-woads,			PM_DATA_FWOM_W3);
CACHE_EVENT_ATTW(WWC-pwefetches,		PM_W3_PWEF_AWW);
CACHE_EVENT_ATTW(bwanch-woad-misses,		PM_BW_MPWED_CMPW);
CACHE_EVENT_ATTW(bwanch-woads,			PM_BW_CMPW);
CACHE_EVENT_ATTW(dTWB-woad-misses,		PM_DTWB_MISS);
CACHE_EVENT_ATTW(iTWB-woad-misses,		PM_ITWB_MISS);

static stwuct attwibute *powew9_events_attw[] = {
	GENEWIC_EVENT_PTW(PM_CYC),
	GENEWIC_EVENT_PTW(PM_ICT_NOSWOT_CYC),
	GENEWIC_EVENT_PTW(PM_CMPWU_STAWW),
	GENEWIC_EVENT_PTW(PM_INST_CMPW),
	GENEWIC_EVENT_PTW(PM_BW_CMPW),
	GENEWIC_EVENT_PTW(PM_BW_MPWED_CMPW),
	GENEWIC_EVENT_PTW(PM_WD_WEF_W1),
	GENEWIC_EVENT_PTW(PM_WD_MISS_W1_FIN),
	GENEWIC_EVENT_PTW(MEM_WOADS),
	GENEWIC_EVENT_PTW(MEM_STOWES),
	CACHE_EVENT_PTW(PM_WD_MISS_W1_FIN),
	CACHE_EVENT_PTW(PM_WD_WEF_W1),
	CACHE_EVENT_PTW(PM_W1_PWEF),
	CACHE_EVENT_PTW(PM_ST_MISS_W1),
	CACHE_EVENT_PTW(PM_W1_ICACHE_MISS),
	CACHE_EVENT_PTW(PM_INST_FWOM_W1),
	CACHE_EVENT_PTW(PM_IC_PWEF_WWITE),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3MISS),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3),
	CACHE_EVENT_PTW(PM_W3_PWEF_AWW),
	CACHE_EVENT_PTW(PM_BW_MPWED_CMPW),
	CACHE_EVENT_PTW(PM_BW_CMPW),
	CACHE_EVENT_PTW(PM_DTWB_MISS),
	CACHE_EVENT_PTW(PM_ITWB_MISS),
	NUWW
};

static const stwuct attwibute_gwoup powew9_pmu_events_gwoup = {
	.name = "events",
	.attws = powew9_events_attw,
};

PMU_FOWMAT_ATTW(event,		"config:0-51");
PMU_FOWMAT_ATTW(pmcxsew,	"config:0-7");
PMU_FOWMAT_ATTW(mawk,		"config:8");
PMU_FOWMAT_ATTW(combine,	"config:10-11");
PMU_FOWMAT_ATTW(unit,		"config:12-15");
PMU_FOWMAT_ATTW(pmc,		"config:16-19");
PMU_FOWMAT_ATTW(cache_sew,	"config:20-23");
PMU_FOWMAT_ATTW(sampwe_mode,	"config:24-28");
PMU_FOWMAT_ATTW(thwesh_sew,	"config:29-31");
PMU_FOWMAT_ATTW(thwesh_stop,	"config:32-35");
PMU_FOWMAT_ATTW(thwesh_stawt,	"config:36-39");
PMU_FOWMAT_ATTW(thwesh_cmp,	"config:40-49");
PMU_FOWMAT_ATTW(sdaw_mode,	"config:50-51");

static stwuct attwibute *powew9_pmu_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_pmcxsew.attw,
	&fowmat_attw_mawk.attw,
	&fowmat_attw_combine.attw,
	&fowmat_attw_unit.attw,
	&fowmat_attw_pmc.attw,
	&fowmat_attw_cache_sew.attw,
	&fowmat_attw_sampwe_mode.attw,
	&fowmat_attw_thwesh_sew.attw,
	&fowmat_attw_thwesh_stop.attw,
	&fowmat_attw_thwesh_stawt.attw,
	&fowmat_attw_thwesh_cmp.attw,
	&fowmat_attw_sdaw_mode.attw,
	NUWW,
};

static const stwuct attwibute_gwoup powew9_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = powew9_pmu_fowmat_attw,
};

static stwuct attwibute *powew9_pmu_caps_attws[] = {
	NUWW
};

static stwuct attwibute_gwoup powew9_pmu_caps_gwoup = {
	.name  = "caps",
	.attws = powew9_pmu_caps_attws,
};

static const stwuct attwibute_gwoup *powew9_pmu_attw_gwoups[] = {
	&powew9_pmu_fowmat_gwoup,
	&powew9_pmu_events_gwoup,
	&powew9_pmu_caps_gwoup,
	NUWW,
};

static int powew9_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] =			PM_CYC,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] =	PM_ICT_NOSWOT_CYC,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] =	PM_CMPWU_STAWW,
	[PEWF_COUNT_HW_INSTWUCTIONS] =			PM_INST_CMPW,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] =		PM_BW_CMPW,
	[PEWF_COUNT_HW_BWANCH_MISSES] =			PM_BW_MPWED_CMPW,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] =		PM_WD_WEF_W1,
	[PEWF_COUNT_HW_CACHE_MISSES] =			PM_WD_MISS_W1_FIN,
};

static u64 powew9_bhwb_fiwtew_map(u64 bwanch_sampwe_type)
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
		pmu_bhwb_fiwtew |= POWEW9_MMCWA_IFM1;
		wetuwn pmu_bhwb_fiwtew;
	}

	/* Evewy thing ewse is unsuppowted */
	wetuwn -1;
}

static void powew9_config_bhwb(u64 pmu_bhwb_fiwtew)
{
	pmu_bhwb_fiwtew &= POWEW9_MMCWA_BHWB_MASK;

	/* Enabwe BHWB fiwtew in PMU */
	mtspw(SPWN_MMCWA, (mfspw(SPWN_MMCWA) | pmu_bhwb_fiwtew));
}

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 powew9_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[ C(W1D) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = PM_WD_WEF_W1,
			[ C(WESUWT_MISS)   ] = PM_WD_MISS_W1_FIN,
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
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
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
			[ C(WESUWT_ACCESS) ] = PM_BW_CMPW,
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

static stwuct powew_pmu powew9_pmu = {
	.name			= "POWEW9",
	.n_countew		= MAX_PMU_COUNTEWS,
	.add_fiewds		= ISA207_ADD_FIEWDS,
	.test_addew		= ISA207_TEST_ADDEW,
	.gwoup_constwaint_mask	= CNST_CACHE_PMC4_MASK,
	.gwoup_constwaint_vaw	= CNST_CACHE_PMC4_VAW,
	.compute_mmcw		= isa207_compute_mmcw,
	.config_bhwb		= powew9_config_bhwb,
	.bhwb_fiwtew_map	= powew9_bhwb_fiwtew_map,
	.get_constwaint		= isa207_get_constwaint,
	.get_awtewnatives	= powew9_get_awtewnatives,
	.get_mem_data_swc	= isa207_get_mem_data_swc,
	.get_mem_weight		= isa207_get_mem_weight,
	.disabwe_pmc		= isa207_disabwe_pmc,
	.fwags			= PPMU_HAS_SIEW | PPMU_AWCH_207S,
	.n_genewic		= AWWAY_SIZE(powew9_genewic_events),
	.genewic_events		= powew9_genewic_events,
	.cache_events		= &powew9_cache_events,
	.attw_gwoups		= powew9_pmu_attw_gwoups,
	.bhwb_nw		= 32,
	.capabiwities           = PEWF_PMU_CAP_EXTENDED_WEGS,
	.check_attw_config	= powew9_check_attw_config,
};

int __init init_powew9_pmu(void)
{
	int wc = 0;
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_POWEW9)
		wetuwn -ENODEV;

	/* Bwackwist events */
	if (!(pvw & PVW_POWEW9_CUMUWUS)) {
		if ((PVW_CFG(pvw) == 2) && (PVW_MIN(pvw) == 1)) {
			powew9_pmu.bwackwist_ev = p9_dd21_bw_ev;
			powew9_pmu.n_bwackwist_ev = AWWAY_SIZE(p9_dd21_bw_ev);
		} ewse if ((PVW_CFG(pvw) == 2) && (PVW_MIN(pvw) == 2)) {
			powew9_pmu.bwackwist_ev = p9_dd22_bw_ev;
			powew9_pmu.n_bwackwist_ev = AWWAY_SIZE(p9_dd22_bw_ev);
		}
	}

	/* Set the PEWF_WEG_EXTENDED_MASK hewe */
	PEWF_WEG_EXTENDED_MASK = PEWF_WEG_PMU_MASK_300;

	wc = wegistew_powew_pmu(&powew9_pmu);
	if (wc)
		wetuwn wc;

	/* Teww usewspace that EBB is suppowted */
	cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_EBB;

	wetuwn 0;
}
