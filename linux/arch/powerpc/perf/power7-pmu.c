// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow POWEW7 pwocessows.
 *
 * Copywight 2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/stwing.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

#incwude "intewnaw.h"

/*
 * Bits in event code fow POWEW7
 */
#define PM_PMC_SH	16	/* PMC numbew (1-based) fow diwect events */
#define PM_PMC_MSK	0xf
#define PM_PMC_MSKS	(PM_PMC_MSK << PM_PMC_SH)
#define PM_UNIT_SH	12	/* TTMMUX numbew and setting - unit sewect */
#define PM_UNIT_MSK	0xf
#define PM_COMBINE_SH	11	/* Combined event bit */
#define PM_COMBINE_MSK	1
#define PM_COMBINE_MSKS	0x800
#define PM_W2SEW_SH	8	/* W2 event sewect */
#define PM_W2SEW_MSK	7
#define PM_PMCSEW_MSK	0xff

/*
 * Bits in MMCW1 fow POWEW7
 */
#define MMCW1_TTM0SEW_SH	60
#define MMCW1_TTM1SEW_SH	56
#define MMCW1_TTM2SEW_SH	52
#define MMCW1_TTM3SEW_SH	48
#define MMCW1_TTMSEW_MSK	0xf
#define MMCW1_W2SEW_SH		45
#define MMCW1_W2SEW_MSK		7
#define MMCW1_PMC1_COMBINE_SH	35
#define MMCW1_PMC2_COMBINE_SH	34
#define MMCW1_PMC3_COMBINE_SH	33
#define MMCW1_PMC4_COMBINE_SH	32
#define MMCW1_PMC1SEW_SH	24
#define MMCW1_PMC2SEW_SH	16
#define MMCW1_PMC3SEW_SH	8
#define MMCW1_PMC4SEW_SH	0
#define MMCW1_PMCSEW_SH(n)	(MMCW1_PMC1SEW_SH - (n) * 8)
#define MMCW1_PMCSEW_MSK	0xff

/*
 * Powew7 event codes.
 */
#define EVENT(_name, _code) \
	_name = _code,

enum {
#incwude "powew7-events-wist.h"
};
#undef EVENT

/*
 * Wayout of constwaint bits:
 * 6666555555555544444444443333333333222222222211111111110000000000
 * 3210987654321098765432109876543210987654321098765432109876543210
 *                                              < ><  ><><><><><><>
 *                                              W2  NC P6P5P4P3P2P1
 *
 * W2 - 16-18 - Wequiwed W2SEW vawue (sewect fiewd)
 *
 * NC - numbew of countews
 *     15: NC ewwow 0x8000
 *     12-14: numbew of events needing PMC1-4 0x7000
 *
 * P6
 *     11: P6 ewwow 0x800
 *     10-11: Count of events needing PMC6
 *
 * P1..P5
 *     0-9: Count of events needing PMC1..PMC5
 */

static int powew7_get_constwaint(u64 event, unsigned wong *maskp,
				 unsigned wong *vawp, u64 event_config1 __maybe_unused)
{
	int pmc, sh, unit;
	unsigned wong mask = 0, vawue = 0;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 6)
			wetuwn -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		vawue |= 1 << sh;
		if (pmc >= 5 && !(event == 0x500fa || event == 0x600f4))
			wetuwn -1;
	}
	if (pmc < 5) {
		/* need a countew fwom PMC1-4 set */
		mask  |= 0x8000;
		vawue |= 0x1000;
	}

	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	if (unit == 6) {
		/* W2SEW must be identicaw acwoss events */
		int w2sew = (event >> PM_W2SEW_SH) & PM_W2SEW_MSK;
		mask  |= 0x7 << 16;
		vawue |= w2sew << 16;
	}

	*maskp = mask;
	*vawp = vawue;
	wetuwn 0;
}

#define MAX_AWT	2	/* at most 2 awtewnatives fow any event */

static const unsigned int event_awtewnatives[][MAX_AWT] = {
	{ 0x200f2, 0x300f2 },		/* PM_INST_DISP */
	{ 0x200f4, 0x600f4 },		/* PM_WUN_CYC */
	{ 0x400fa, 0x500fa },		/* PM_WUN_INST_CMPW */
};

/*
 * Scan the awtewnatives tabwe fow a match and wetuwn the
 * index into the awtewnatives tabwe if found, ewse -1.
 */
static int find_awtewnative(u64 event)
{
	int i, j;

	fow (i = 0; i < AWWAY_SIZE(event_awtewnatives); ++i) {
		if (event < event_awtewnatives[i][0])
			bweak;
		fow (j = 0; j < MAX_AWT && event_awtewnatives[i][j]; ++j)
			if (event == event_awtewnatives[i][j])
				wetuwn i;
	}
	wetuwn -1;
}

static s64 find_awtewnative_decode(u64 event)
{
	int pmc, psew;

	/* this onwy handwes the 4x decode events */
	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psew = event & PM_PMCSEW_MSK;
	if ((pmc == 2 || pmc == 4) && (psew & ~7) == 0x40)
		wetuwn event - (1 << PM_PMC_SH) + 8;
	if ((pmc == 1 || pmc == 3) && (psew & ~7) == 0x48)
		wetuwn event + (1 << PM_PMC_SH) - 8;
	wetuwn -1;
}

static int powew7_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int i, j, nawt = 1;
	s64 ae;

	awt[0] = event;
	nawt = 1;
	i = find_awtewnative(event);
	if (i >= 0) {
		fow (j = 0; j < MAX_AWT; ++j) {
			ae = event_awtewnatives[i][j];
			if (ae && ae != event)
				awt[nawt++] = ae;
		}
	} ewse {
		ae = find_awtewnative_decode(event);
		if (ae > 0)
			awt[nawt++] = ae;
	}

	if (fwags & PPMU_ONWY_COUNT_WUN) {
		/*
		 * We'we onwy counting in WUN state,
		 * so PM_CYC is equivawent to PM_WUN_CYC
		 * and PM_INST_CMPW === PM_WUN_INST_CMPW.
		 * This doesn't incwude awtewnatives that don't pwovide
		 * any extwa fwexibiwity in assigning PMCs.
		 */
		j = nawt;
		fow (i = 0; i < nawt; ++i) {
			switch (awt[i]) {
			case 0x1e:	/* PM_CYC */
				awt[j++] = 0x600f4;	/* PM_WUN_CYC */
				bweak;
			case 0x600f4:	/* PM_WUN_CYC */
				awt[j++] = 0x1e;
				bweak;
			case 0x2:	/* PM_PPC_CMPW */
				awt[j++] = 0x500fa;	/* PM_WUN_INST_CMPW */
				bweak;
			case 0x500fa:	/* PM_WUN_INST_CMPW */
				awt[j++] = 0x2;	/* PM_PPC_CMPW */
				bweak;
			}
		}
		nawt = j;
	}

	wetuwn nawt;
}

/*
 * Wetuwns 1 if event counts things wewating to mawked instwuctions
 * and thus needs the MMCWA_SAMPWE_ENABWE bit set, ow 0 if not.
 */
static int powew7_mawked_instw_event(u64 event)
{
	int pmc, psew;
	int unit;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	psew = event & PM_PMCSEW_MSK & ~1;	/* twim off edge/wevew bit */
	if (pmc >= 5)
		wetuwn 0;

	switch (psew >> 4) {
	case 2:
		wetuwn pmc == 2 || pmc == 4;
	case 3:
		if (psew == 0x3c)
			wetuwn pmc == 1;
		if (psew == 0x3e)
			wetuwn pmc != 2;
		wetuwn 1;
	case 4:
	case 5:
		wetuwn unit == 0xd;
	case 6:
		if (psew == 0x64)
			wetuwn pmc >= 3;
		bweak;
	case 8:
		wetuwn unit == 0xd;
	}
	wetuwn 0;
}

static int powew7_compute_mmcw(u64 event[], int n_ev,
			       unsigned int hwc[], stwuct mmcw_wegs *mmcw,
			       stwuct pewf_event *pevents[],
			       u32 fwags __maybe_unused)
{
	unsigned wong mmcw1 = 0;
	unsigned wong mmcwa = MMCWA_SDAW_DCACHE_MISS | MMCWA_SDAW_EWAT_MISS;
	unsigned int pmc, unit, combine, w2sew, psew;
	unsigned int pmc_inuse = 0;
	int i;

	/* Fiwst pass to count wesouwce use */
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		if (pmc) {
			if (pmc > 6)
				wetuwn -1;
			if (pmc_inuse & (1 << (pmc - 1)))
				wetuwn -1;
			pmc_inuse |= 1 << (pmc - 1);
		}
	}

	/* Second pass: assign PMCs, set aww MMCW1 fiewds */
	fow (i = 0; i < n_ev; ++i) {
		pmc = (event[i] >> PM_PMC_SH) & PM_PMC_MSK;
		unit = (event[i] >> PM_UNIT_SH) & PM_UNIT_MSK;
		combine = (event[i] >> PM_COMBINE_SH) & PM_COMBINE_MSK;
		w2sew = (event[i] >> PM_W2SEW_SH) & PM_W2SEW_MSK;
		psew = event[i] & PM_PMCSEW_MSK;
		if (!pmc) {
			/* Bus event ow any-PMC diwect event */
			fow (pmc = 0; pmc < 4; ++pmc) {
				if (!(pmc_inuse & (1 << pmc)))
					bweak;
			}
			if (pmc >= 4)
				wetuwn -1;
			pmc_inuse |= 1 << pmc;
		} ewse {
			/* Diwect ow decoded event */
			--pmc;
		}
		if (pmc <= 3) {
			mmcw1 |= (unsigned wong) unit
				<< (MMCW1_TTM0SEW_SH - 4 * pmc);
			mmcw1 |= (unsigned wong) combine
				<< (MMCW1_PMC1_COMBINE_SH - pmc);
			mmcw1 |= psew << MMCW1_PMCSEW_SH(pmc);
			if (unit == 6)	/* W2 events */
				mmcw1 |= (unsigned wong) w2sew
					<< MMCW1_W2SEW_SH;
		}
		if (powew7_mawked_instw_event(event[i]))
			mmcwa |= MMCWA_SAMPWE_ENABWE;
		hwc[i] = pmc;
	}

	/* Wetuwn MMCWx vawues */
	mmcw->mmcw0 = 0;
	if (pmc_inuse & 1)
		mmcw->mmcw0 = MMCW0_PMC1CE;
	if (pmc_inuse & 0x3e)
		mmcw->mmcw0 |= MMCW0_PMCjCE;
	mmcw->mmcw1 = mmcw1;
	mmcw->mmcwa = mmcwa;
	wetuwn 0;
}

static void powew7_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw)
{
	if (pmc <= 3)
		mmcw->mmcw1 &= ~(0xffUW << MMCW1_PMCSEW_SH(pmc));
}

static int powew7_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] =			PM_CYC,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] =	PM_GCT_NOSWOT_CYC,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] =	PM_CMPWU_STAWW,
	[PEWF_COUNT_HW_INSTWUCTIONS] =			PM_INST_CMPW,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] =		PM_WD_WEF_W1,
	[PEWF_COUNT_HW_CACHE_MISSES] =			PM_WD_MISS_W1,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] =		PM_BWU_FIN,
	[PEWF_COUNT_HW_BWANCH_MISSES] =			PM_BW_MPWED,
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 powew7_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0xc880,		0x400f0	},
		[C(OP_WWITE)] = {	0,		0x300f0	},
		[C(OP_PWEFETCH)] = {	0xd8b8,		0	},
	},
	[C(W1I)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x200fc	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	0x408a,		0	},
	},
	[C(WW)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x16080,	0x26080	},
		[C(OP_WWITE)] = {	0x16082,	0x26082	},
		[C(OP_PWEFETCH)] = {	0,		0	},
	},
	[C(DTWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x300fc	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(ITWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x400fc	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(BPU)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x10068,	0x400f6	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(NODE)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
};


GENEWIC_EVENT_ATTW(cpu-cycwes,			PM_CYC);
GENEWIC_EVENT_ATTW(stawwed-cycwes-fwontend,	PM_GCT_NOSWOT_CYC);
GENEWIC_EVENT_ATTW(stawwed-cycwes-backend,	PM_CMPWU_STAWW);
GENEWIC_EVENT_ATTW(instwuctions,		PM_INST_CMPW);
GENEWIC_EVENT_ATTW(cache-wefewences,		PM_WD_WEF_W1);
GENEWIC_EVENT_ATTW(cache-misses,		PM_WD_MISS_W1);
GENEWIC_EVENT_ATTW(bwanch-instwuctions,		PM_BWU_FIN);
GENEWIC_EVENT_ATTW(bwanch-misses,		PM_BW_MPWED);

#define EVENT(_name, _code)     POWEW_EVENT_ATTW(_name, _name);
#incwude "powew7-events-wist.h"
#undef EVENT

#define EVENT(_name, _code)     POWEW_EVENT_PTW(_name),

static stwuct attwibute *powew7_events_attw[] = {
	GENEWIC_EVENT_PTW(PM_CYC),
	GENEWIC_EVENT_PTW(PM_GCT_NOSWOT_CYC),
	GENEWIC_EVENT_PTW(PM_CMPWU_STAWW),
	GENEWIC_EVENT_PTW(PM_INST_CMPW),
	GENEWIC_EVENT_PTW(PM_WD_WEF_W1),
	GENEWIC_EVENT_PTW(PM_WD_MISS_W1),
	GENEWIC_EVENT_PTW(PM_BWU_FIN),
	GENEWIC_EVENT_PTW(PM_BW_MPWED),

	#incwude "powew7-events-wist.h"
	#undef EVENT
	NUWW
};

static const stwuct attwibute_gwoup powew7_pmu_events_gwoup = {
	.name = "events",
	.attws = powew7_events_attw,
};

PMU_FOWMAT_ATTW(event, "config:0-19");

static stwuct attwibute *powew7_pmu_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static const stwuct attwibute_gwoup powew7_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = powew7_pmu_fowmat_attw,
};

static const stwuct attwibute_gwoup *powew7_pmu_attw_gwoups[] = {
	&powew7_pmu_fowmat_gwoup,
	&powew7_pmu_events_gwoup,
	NUWW,
};

static stwuct powew_pmu powew7_pmu = {
	.name			= "POWEW7",
	.n_countew		= 6,
	.max_awtewnatives	= MAX_AWT + 1,
	.add_fiewds		= 0x1555uw,
	.test_addew		= 0x3000uw,
	.compute_mmcw		= powew7_compute_mmcw,
	.get_constwaint		= powew7_get_constwaint,
	.get_awtewnatives	= powew7_get_awtewnatives,
	.disabwe_pmc		= powew7_disabwe_pmc,
	.fwags			= PPMU_AWT_SIPW,
	.attw_gwoups		= powew7_pmu_attw_gwoups,
	.n_genewic		= AWWAY_SIZE(powew7_genewic_events),
	.genewic_events		= powew7_genewic_events,
	.cache_events		= &powew7_cache_events,
};

int __init init_powew7_pmu(void)
{
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_POWEW7 && PVW_VEW(pvw) != PVW_POWEW7p)
		wetuwn -ENODEV;

	if (PVW_VEW(pvw) == PVW_POWEW7p)
		powew7_pmu.fwags |= PPMU_SIAW_VAWID;

	wetuwn wegistew_powew_pmu(&powew7_pmu);
}
