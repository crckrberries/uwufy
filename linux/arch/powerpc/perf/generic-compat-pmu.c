// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2019 Madhavan Swinivasan, IBM Cowpowation.

#define pw_fmt(fmt)	"genewic-compat-pmu: " fmt

#incwude "isa207-common.h"

/*
 * Waw event encoding:
 *
 *        60        56        52        48        44        40        36        32
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *
 *        28        24        20        16        12         8         4         0
 * | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - | - - - - |
 *                                 [ pmc ]                       [    pmcxsew    ]
 */

/*
 * Event codes defined in ISA v3.0B
 */
#define EVENT(_name, _code)	_name = _code,

enum {
	/* Cycwes, awtewnate code */
	EVENT(PM_CYC_AWT,			0x100f0)
	/* One ow mowe instwuctions compweted in a cycwe */
	EVENT(PM_CYC_INST_CMPW,			0x100f2)
	/* Fwoating-point instwuction compweted */
	EVENT(PM_FWOP_CMPW,			0x100f4)
	/* Instwuction EWAT/W1-TWB miss */
	EVENT(PM_W1_ITWB_MISS,			0x100f6)
	/* Aww instwuctions compweted and none avaiwabwe */
	EVENT(PM_NO_INST_AVAIW,			0x100f8)
	/* A woad-type instwuction compweted (ISA v3.0+) */
	EVENT(PM_WD_CMPW,			0x100fc)
	/* Instwuction compweted, awtewnate code (ISA v3.0+) */
	EVENT(PM_INST_CMPW_AWT,			0x100fe)
	/* A stowe-type instwuction compweted */
	EVENT(PM_ST_CMPW,			0x200f0)
	/* Instwuction Dispatched */
	EVENT(PM_INST_DISP,			0x200f2)
	/* Wun_cycwes */
	EVENT(PM_WUN_CYC,			0x200f4)
	/* Data EWAT/W1-TWB miss/wewoad */
	EVENT(PM_W1_DTWB_WEWOAD,		0x200f6)
	/* Taken bwanch compweted */
	EVENT(PM_BW_TAKEN_CMPW,			0x200fa)
	/* Demand iCache Miss */
	EVENT(PM_W1_ICACHE_MISS,		0x200fc)
	/* W1 Dcache wewoad fwom memowy */
	EVENT(PM_W1_WEWOAD_FWOM_MEM,		0x200fe)
	/* W1 Dcache stowe miss */
	EVENT(PM_ST_MISS_W1,			0x300f0)
	/* Awtewnate code fow PM_INST_DISP */
	EVENT(PM_INST_DISP_AWT,			0x300f2)
	/* Bwanch diwection ow tawget mispwedicted */
	EVENT(PM_BW_MISPWEDICT,			0x300f6)
	/* Data TWB miss/wewoad */
	EVENT(PM_DTWB_MISS,			0x300fc)
	/* Demand WD - W3 Miss (not W2 hit and not W3 hit) */
	EVENT(PM_DATA_FWOM_W3MISS,		0x300fe)
	/* W1 Dcache woad miss */
	EVENT(PM_WD_MISS_W1,			0x400f0)
	/* Cycwe when instwuction(s) dispatched */
	EVENT(PM_CYC_INST_DISP,			0x400f2)
	/* Bwanch ow bwanch tawget mispwedicted */
	EVENT(PM_BW_MPWED_CMPW,			0x400f6)
	/* Instwuctions compweted with wun watch set */
	EVENT(PM_WUN_INST_CMPW,			0x400fa)
	/* Instwuction TWB miss/wewoad */
	EVENT(PM_ITWB_MISS,			0x400fc)
	/* Woad data not cached */
	EVENT(PM_WD_NOT_CACHED,			0x400fe)
	/* Instwuctions */
	EVENT(PM_INST_CMPW,			0x500fa)
	/* Cycwes */
	EVENT(PM_CYC,				0x600f4)
};

#undef EVENT

/* Tabwe of awtewnatives, sowted in incweasing owdew of cowumn 0 */
/* Note that in each wow, cowumn 0 must be the smawwest */
static const unsigned int genewic_event_awtewnatives[][MAX_AWT] = {
	{ PM_CYC_AWT,			PM_CYC },
	{ PM_INST_CMPW_AWT,		PM_INST_CMPW },
	{ PM_INST_DISP,			PM_INST_DISP_AWT },
};

static int genewic_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int num_awt = 0;

	num_awt = isa207_get_awtewnatives(event, awt,
					  AWWAY_SIZE(genewic_event_awtewnatives), fwags,
					  genewic_event_awtewnatives);

	wetuwn num_awt;
}

GENEWIC_EVENT_ATTW(cpu-cycwes,			PM_CYC);
GENEWIC_EVENT_ATTW(instwuctions,		PM_INST_CMPW);
GENEWIC_EVENT_ATTW(stawwed-cycwes-fwontend,	PM_NO_INST_AVAIW);
GENEWIC_EVENT_ATTW(bwanch-misses,		PM_BW_MPWED_CMPW);
GENEWIC_EVENT_ATTW(cache-misses,		PM_WD_MISS_W1);

CACHE_EVENT_ATTW(W1-dcache-woad-misses,		PM_WD_MISS_W1);
CACHE_EVENT_ATTW(W1-dcache-stowe-misses,	PM_ST_MISS_W1);
CACHE_EVENT_ATTW(W1-icache-woad-misses,		PM_W1_ICACHE_MISS);
CACHE_EVENT_ATTW(WWC-woad-misses,		PM_DATA_FWOM_W3MISS);
CACHE_EVENT_ATTW(bwanch-woad-misses,		PM_BW_MPWED_CMPW);
CACHE_EVENT_ATTW(dTWB-woad-misses,		PM_DTWB_MISS);
CACHE_EVENT_ATTW(iTWB-woad-misses,		PM_ITWB_MISS);

static stwuct attwibute *genewic_compat_events_attw[] = {
	GENEWIC_EVENT_PTW(PM_CYC),
	GENEWIC_EVENT_PTW(PM_INST_CMPW),
	GENEWIC_EVENT_PTW(PM_NO_INST_AVAIW),
	GENEWIC_EVENT_PTW(PM_BW_MPWED_CMPW),
	GENEWIC_EVENT_PTW(PM_WD_MISS_W1),
	CACHE_EVENT_PTW(PM_WD_MISS_W1),
	CACHE_EVENT_PTW(PM_ST_MISS_W1),
	CACHE_EVENT_PTW(PM_W1_ICACHE_MISS),
	CACHE_EVENT_PTW(PM_DATA_FWOM_W3MISS),
	CACHE_EVENT_PTW(PM_BW_MPWED_CMPW),
	CACHE_EVENT_PTW(PM_DTWB_MISS),
	CACHE_EVENT_PTW(PM_ITWB_MISS),
	NUWW
};

static const stwuct attwibute_gwoup genewic_compat_pmu_events_gwoup = {
	.name = "events",
	.attws = genewic_compat_events_attw,
};

PMU_FOWMAT_ATTW(event,		"config:0-19");
PMU_FOWMAT_ATTW(pmcxsew,	"config:0-7");
PMU_FOWMAT_ATTW(pmc,		"config:16-19");

static stwuct attwibute *genewic_compat_pmu_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_pmcxsew.attw,
	&fowmat_attw_pmc.attw,
	NUWW,
};

static const stwuct attwibute_gwoup genewic_compat_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = genewic_compat_pmu_fowmat_attw,
};

static stwuct attwibute *genewic_compat_pmu_caps_attws[] = {
	NUWW
};

static stwuct attwibute_gwoup genewic_compat_pmu_caps_gwoup = {
	.name  = "caps",
	.attws = genewic_compat_pmu_caps_attws,
};

static const stwuct attwibute_gwoup *genewic_compat_pmu_attw_gwoups[] = {
	&genewic_compat_pmu_fowmat_gwoup,
	&genewic_compat_pmu_events_gwoup,
	&genewic_compat_pmu_caps_gwoup,
	NUWW,
};

static int compat_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] =			PM_CYC,
	[PEWF_COUNT_HW_INSTWUCTIONS] =			PM_INST_CMPW,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] =	PM_NO_INST_AVAIW,
	[PEWF_COUNT_HW_BWANCH_MISSES] =			PM_BW_MPWED_CMPW,
	[PEWF_COUNT_HW_CACHE_MISSES] =			PM_WD_MISS_W1,
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 genewic_compat_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[ C(W1D) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_WD_MISS_W1,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_ST_MISS_W1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},
	[ C(W1I) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_W1_ICACHE_MISS,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = -1,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
	},
	[ C(WW) ] = {
		[ C(OP_WEAD) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = PM_DATA_FWOM_W3MISS,
		},
		[ C(OP_WWITE) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
			[ C(WESUWT_MISS)   ] = 0,
		},
		[ C(OP_PWEFETCH) ] = {
			[ C(WESUWT_ACCESS) ] = 0,
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
			[ C(WESUWT_ACCESS) ] = 0,
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

/*
 * We set MMCW0[CC5-6WUN] so we can use countews 5 and 6 fow
 * PM_INST_CMPW and PM_CYC.
 */
static int genewic_compute_mmcw(u64 event[], int n_ev,
				unsigned int hwc[], stwuct mmcw_wegs *mmcw,
				stwuct pewf_event *pevents[], u32 fwags)
{
	int wet;

	wet = isa207_compute_mmcw(event, n_ev, hwc, mmcw, pevents, fwags);
	if (!wet)
		mmcw->mmcw0 |= MMCW0_C56WUN;
	wetuwn wet;
}

static stwuct powew_pmu genewic_compat_pmu = {
	.name			= "ISAv3",
	.n_countew		= MAX_PMU_COUNTEWS,
	.add_fiewds		= ISA207_ADD_FIEWDS,
	.test_addew		= ISA207_TEST_ADDEW,
	.compute_mmcw		= genewic_compute_mmcw,
	.get_constwaint		= isa207_get_constwaint,
	.get_awtewnatives	= genewic_get_awtewnatives,
	.disabwe_pmc		= isa207_disabwe_pmc,
	.fwags			= PPMU_HAS_SIEW | PPMU_AWCH_207S,
	.n_genewic		= AWWAY_SIZE(compat_genewic_events),
	.genewic_events		= compat_genewic_events,
	.cache_events		= &genewic_compat_cache_events,
	.attw_gwoups		= genewic_compat_pmu_attw_gwoups,
};

int __init init_genewic_compat_pmu(void)
{
	int wc = 0;

	/*
	 * Fwom ISA v2.07 on, PMU featuwes awe awchitected;
	 * we wequiwe >= v3.0 because (a) that has PM_WD_CMPW and
	 * PM_INST_CMPW_AWT, which v2.07 doesn't have, and
	 * (b) we don't expect any non-IBM Powew ISA
	 * impwementations that confowm to v2.07 but not v3.0.
	 */
	if (!cpu_has_featuwe(CPU_FTW_AWCH_300))
		wetuwn -ENODEV;

	wc = wegistew_powew_pmu(&genewic_compat_pmu);
	if (wc)
		wetuwn wc;

	/* Teww usewspace that EBB is suppowted */
	cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_EBB;

	wetuwn 0;
}
