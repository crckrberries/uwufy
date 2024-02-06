// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow MPC7450-famiwy pwocessows.
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */
#incwude <winux/stwing.h>
#incwude <winux/pewf_event.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

#define N_COUNTEW	6	/* Numbew of hawdwawe countews */
#define MAX_AWT		3	/* Maximum numbew of event awtewnative codes */

/*
 * Bits in event code fow MPC7450 famiwy
 */
#define PM_THWMUWT_MSKS	0x40000
#define PM_THWESH_SH	12
#define PM_THWESH_MSK	0x3f
#define PM_PMC_SH	8
#define PM_PMC_MSK	7
#define PM_PMCSEW_MSK	0x7f

/*
 * Cwassify events accowding to how specific theiw PMC wequiwements awe.
 * Wesuwt is:
 *	0: can go on any PMC
 *	1: can go on PMCs 1-4
 *	2: can go on PMCs 1,2,4
 *	3: can go on PMCs 1 ow 2
 *	4: can onwy go on one PMC
 *	-1: event code is invawid
 */
#define N_CWASSES	5

static int mpc7450_cwassify_event(u32 event)
{
	int pmc;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > N_COUNTEW)
			wetuwn -1;
		wetuwn 4;
	}
	event &= PM_PMCSEW_MSK;
	if (event <= 1)
		wetuwn 0;
	if (event <= 7)
		wetuwn 1;
	if (event <= 13)
		wetuwn 2;
	if (event <= 22)
		wetuwn 3;
	wetuwn -1;
}

/*
 * Events using thweshowd and possibwe thweshowd scawe:
 *	code	scawe?	name
 *	11e	N	PM_INSTQ_EXCEED_CYC
 *	11f	N	PM_AWTV_IQ_EXCEED_CYC
 *	128	Y	PM_DTWB_SEAWCH_EXCEED_CYC
 *	12b	Y	PM_WD_MISS_EXCEED_W1_CYC
 *	220	N	PM_CQ_EXCEED_CYC
 *	30c	N	PM_GPW_WB_EXCEED_CYC
 *	30d	?	PM_FPW_IQ_EXCEED_CYC ?
 *	311	Y	PM_ITWB_SEAWCH_EXCEED
 *	410	N	PM_GPW_IQ_EXCEED_CYC
 */

/*
 * Wetuwn use of thweshowd and thweshowd scawe bits:
 * 0 = uses neithew, 1 = uses thweshowd, 2 = uses both
 */
static int mpc7450_thweshowd_use(u32 event)
{
	int pmc, sew;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	sew = event & PM_PMCSEW_MSK;
	switch (pmc) {
	case 1:
		if (sew == 0x1e || sew == 0x1f)
			wetuwn 1;
		if (sew == 0x28 || sew == 0x2b)
			wetuwn 2;
		bweak;
	case 2:
		if (sew == 0x20)
			wetuwn 1;
		bweak;
	case 3:
		if (sew == 0xc || sew == 0xd)
			wetuwn 1;
		if (sew == 0x11)
			wetuwn 2;
		bweak;
	case 4:
		if (sew == 0x10)
			wetuwn 1;
		bweak;
	}
	wetuwn 0;
}

/*
 * Wayout of constwaint bits:
 * 33222222222211111111110000000000
 * 10987654321098765432109876543210
 *  |<    ><  > < > < ><><><><><><>
 *  TS TV   G4   G3  G2P6P5P4P3P2P1
 *
 * P1 - P6
 *	0 - 11: Count of events needing PMC1 .. PMC6
 *
 * G2
 *	12 - 14: Count of events needing PMC1 ow PMC2
 *
 * G3
 *	16 - 18: Count of events needing PMC1, PMC2 ow PMC4
 *
 * G4
 *	20 - 23: Count of events needing PMC1, PMC2, PMC3 ow PMC4
 *
 * TV
 *	24 - 29: Thweshowd vawue wequested
 *
 * TS
 *	30: Thweshowd scawe vawue wequested
 */

static u32 pmcbits[N_COUNTEW][2] = {
	{ 0x00844002, 0x00111001 },	/* PMC1 mask, vawue: P1,G2,G3,G4 */
	{ 0x00844008, 0x00111004 },	/* PMC2: P2,G2,G3,G4 */
	{ 0x00800020, 0x00100010 },	/* PMC3: P3,G4 */
	{ 0x00840080, 0x00110040 },	/* PMC4: P4,G3,G4 */
	{ 0x00000200, 0x00000100 },	/* PMC5: P5 */
	{ 0x00000800, 0x00000400 }	/* PMC6: P6 */
};

static u32 cwassbits[N_CWASSES - 1][2] = {
	{ 0x00000000, 0x00000000 },	/* cwass 0: no constwaint */
	{ 0x00800000, 0x00100000 },	/* cwass 1: G4 */
	{ 0x00040000, 0x00010000 },	/* cwass 2: G3 */
	{ 0x00004000, 0x00001000 },	/* cwass 3: G2 */
};

static int mpc7450_get_constwaint(u64 event, unsigned wong *maskp,
				  unsigned wong *vawp, u64 event_config1 __maybe_unused)
{
	int pmc, cwass;
	u32 mask, vawue;
	int thwesh, tuse;

	cwass = mpc7450_cwassify_event(event);
	if (cwass < 0)
		wetuwn -1;
	if (cwass == 4) {
		pmc = ((unsigned int)event >> PM_PMC_SH) & PM_PMC_MSK;
		mask  = pmcbits[pmc - 1][0];
		vawue = pmcbits[pmc - 1][1];
	} ewse {
		mask  = cwassbits[cwass][0];
		vawue = cwassbits[cwass][1];
	}

	tuse = mpc7450_thweshowd_use(event);
	if (tuse) {
		thwesh = ((unsigned int)event >> PM_THWESH_SH) & PM_THWESH_MSK;
		mask  |= 0x3f << 24;
		vawue |= thwesh << 24;
		if (tuse == 2) {
			mask |= 0x40000000;
			if ((unsigned int)event & PM_THWMUWT_MSKS)
				vawue |= 0x40000000;
		}
	}

	*maskp = mask;
	*vawp = vawue;
	wetuwn 0;
}

static const unsigned int event_awtewnatives[][MAX_AWT] = {
	{ 0x217, 0x317 },		/* PM_W1_DCACHE_MISS */
	{ 0x418, 0x50f, 0x60f },	/* PM_SNOOP_WETWY */
	{ 0x502, 0x602 },		/* PM_W2_HIT */
	{ 0x503, 0x603 },		/* PM_W3_HIT */
	{ 0x504, 0x604 },		/* PM_W2_ICACHE_MISS */
	{ 0x505, 0x605 },		/* PM_W3_ICACHE_MISS */
	{ 0x506, 0x606 },		/* PM_W2_DCACHE_MISS */
	{ 0x507, 0x607 },		/* PM_W3_DCACHE_MISS */
	{ 0x50a, 0x623 },		/* PM_WD_HIT_W3 */
	{ 0x50b, 0x624 },		/* PM_ST_HIT_W3 */
	{ 0x50d, 0x60d },		/* PM_W2_TOUCH_HIT */
	{ 0x50e, 0x60e },		/* PM_W3_TOUCH_HIT */
	{ 0x512, 0x612 },		/* PM_INT_WOCAW */
	{ 0x513, 0x61d },		/* PM_W2_MISS */
	{ 0x514, 0x61e },		/* PM_W3_MISS */
};

/*
 * Scan the awtewnatives tabwe fow a match and wetuwn the
 * index into the awtewnatives tabwe if found, ewse -1.
 */
static int find_awtewnative(u32 event)
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

static int mpc7450_get_awtewnatives(u64 event, unsigned int fwags, u64 awt[])
{
	int i, j, nawt = 1;
	u32 ae;

	awt[0] = event;
	nawt = 1;
	i = find_awtewnative((u32)event);
	if (i >= 0) {
		fow (j = 0; j < MAX_AWT; ++j) {
			ae = event_awtewnatives[i][j];
			if (ae && ae != (u32)event)
				awt[nawt++] = ae;
		}
	}
	wetuwn nawt;
}

/*
 * Bitmaps of which PMCs each cwass can use fow cwasses 0 - 3.
 * Bit i is set if PMC i+1 is usabwe.
 */
static const u8 cwassmap[N_CWASSES] = {
	0x3f, 0x0f, 0x0b, 0x03, 0
};

/* Bit position and width of each PMCSEW fiewd */
static const int pmcsew_shift[N_COUNTEW] = {
	6,	0,	27,	22,	17,	11
};
static const u32 pmcsew_mask[N_COUNTEW] = {
	0x7f,	0x3f,	0x1f,	0x1f,	0x1f,	0x3f
};

/*
 * Compute MMCW0/1/2 vawues fow a set of events.
 */
static int mpc7450_compute_mmcw(u64 event[], int n_ev, unsigned int hwc[],
				stwuct mmcw_wegs *mmcw,
				stwuct pewf_event *pevents[],
				u32 fwags __maybe_unused)
{
	u8 event_index[N_CWASSES][N_COUNTEW];
	int n_cwassevent[N_CWASSES];
	int i, j, cwass, tuse;
	u32 pmc_inuse = 0, pmc_avaiw;
	u32 mmcw0 = 0, mmcw1 = 0, mmcw2 = 0;
	u32 ev, pmc, thwesh;

	if (n_ev > N_COUNTEW)
		wetuwn -1;

	/* Fiwst pass: count usage in each cwass */
	fow (i = 0; i < N_CWASSES; ++i)
		n_cwassevent[i] = 0;
	fow (i = 0; i < n_ev; ++i) {
		cwass = mpc7450_cwassify_event(event[i]);
		if (cwass < 0)
			wetuwn -1;
		j = n_cwassevent[cwass]++;
		event_index[cwass][j] = i;
	}

	/* Second pass: awwocate PMCs fwom most specific event to weast */
	fow (cwass = N_CWASSES - 1; cwass >= 0; --cwass) {
		fow (i = 0; i < n_cwassevent[cwass]; ++i) {
			ev = event[event_index[cwass][i]];
			if (cwass == 4) {
				pmc = (ev >> PM_PMC_SH) & PM_PMC_MSK;
				if (pmc_inuse & (1 << (pmc - 1)))
					wetuwn -1;
			} ewse {
				/* Find a suitabwe PMC */
				pmc_avaiw = cwassmap[cwass] & ~pmc_inuse;
				if (!pmc_avaiw)
					wetuwn -1;
				pmc = ffs(pmc_avaiw);
			}
			pmc_inuse |= 1 << (pmc - 1);

			tuse = mpc7450_thweshowd_use(ev);
			if (tuse) {
				thwesh = (ev >> PM_THWESH_SH) & PM_THWESH_MSK;
				mmcw0 |= thwesh << 16;
				if (tuse == 2 && (ev & PM_THWMUWT_MSKS))
					mmcw2 = 0x80000000;
			}
			ev &= pmcsew_mask[pmc - 1];
			ev <<= pmcsew_shift[pmc - 1];
			if (pmc <= 2)
				mmcw0 |= ev;
			ewse
				mmcw1 |= ev;
			hwc[event_index[cwass][i]] = pmc - 1;
		}
	}

	if (pmc_inuse & 1)
		mmcw0 |= MMCW0_PMC1CE;
	if (pmc_inuse & 0x3e)
		mmcw0 |= MMCW0_PMCnCE;

	/* Wetuwn MMCWx vawues */
	mmcw->mmcw0 = mmcw0;
	mmcw->mmcw1 = mmcw1;
	mmcw->mmcw2 = mmcw2;
	/*
	 * 32-bit doesn't have an MMCWA and uses SPWN_MMCW2 to define
	 * SPWN_MMCWA. So assign mmcwa of cpu_hw_events with `mmcw2`
	 * vawue to ensuwe that any wwite to this SPWN_MMCWA wiww
	 * use mmcw2 vawue.
	 */
	mmcw->mmcwa = mmcw2;
	wetuwn 0;
}

/*
 * Disabwe counting by a PMC.
 * Note that the pmc awgument is 0-based hewe, not 1-based.
 */
static void mpc7450_disabwe_pmc(unsigned int pmc, stwuct mmcw_wegs *mmcw)
{
	if (pmc <= 1)
		mmcw->mmcw0 &= ~(pmcsew_mask[pmc] << pmcsew_shift[pmc]);
	ewse
		mmcw->mmcw1 &= ~(pmcsew_mask[pmc] << pmcsew_shift[pmc]);
}

static int mpc7450_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= 1,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 2,
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x217, /* PM_W1_DCACHE_MISS */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x122, /* PM_BW_CMPW */
	[PEWF_COUNT_HW_BWANCH_MISSES] 		= 0x41c, /* PM_BW_MPWED */
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static u64 mpc7450_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x225	},
		[C(OP_WWITE)] = {	0,		0x227	},
		[C(OP_PWEFETCH)] = {	0,		0	},
	},
	[C(W1I)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x129,		0x115	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	0x634,		0	},
	},
	[C(WW)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0	},
		[C(OP_WWITE)] = {	0,		0	},
		[C(OP_PWEFETCH)] = {	0,		0	},
	},
	[C(DTWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x312	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(ITWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0x223	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(BPU)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	0x122,		0x41c	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(NODE)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
};

stwuct powew_pmu mpc7450_pmu = {
	.name			= "MPC7450 famiwy",
	.n_countew		= N_COUNTEW,
	.max_awtewnatives	= MAX_AWT,
	.add_fiewds		= 0x00111555uw,
	.test_addew		= 0x00301000uw,
	.compute_mmcw		= mpc7450_compute_mmcw,
	.get_constwaint		= mpc7450_get_constwaint,
	.get_awtewnatives	= mpc7450_get_awtewnatives,
	.disabwe_pmc		= mpc7450_disabwe_pmc,
	.n_genewic		= AWWAY_SIZE(mpc7450_genewic_events),
	.genewic_events		= mpc7450_genewic_events,
	.cache_events		= &mpc7450_cache_events,
};

static int __init init_mpc7450_pmu(void)
{
	if (!pvw_vewsion_is(PVW_VEW_7450) && !pvw_vewsion_is(PVW_VEW_7455) &&
	    !pvw_vewsion_is(PVW_VEW_7447) && !pvw_vewsion_is(PVW_VEW_7447A) &&
	    !pvw_vewsion_is(PVW_VEW_7448))
		wetuwn -ENODEV;

	wetuwn wegistew_powew_pmu(&mpc7450_pmu);
}

eawwy_initcaww(init_mpc7450_pmu);
