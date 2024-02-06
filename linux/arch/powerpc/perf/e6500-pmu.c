// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow e6500 famiwy pwocessows.
 *
 * Authow: Pwiyanka Jain, Pwiyanka.Jain@fweescawe.com
 * Based on e500-pmu.c
 * Copywight 2013 Fweescawe Semiconductow, Inc.
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 */

#incwude <winux/stwing.h>
#incwude <winux/pewf_event.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

/*
 * Map of genewic hawdwawe event types to hawdwawe events
 * Zewo if unsuppowted
 */
static int e6500_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = 1,
	[PEWF_COUNT_HW_INSTWUCTIONS] = 2,
	[PEWF_COUNT_HW_CACHE_MISSES] = 221,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = 12,
	[PEWF_COUNT_HW_BWANCH_MISSES] = 15,
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static int e6500_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {
				/*WESUWT_ACCESS		WESUWT_MISS */
		[C(OP_WEAD)] = {	27,		222	},
		[C(OP_WWITE)] = {	28,		223	},
		[C(OP_PWEFETCH)] = {	29,		0	},
	},
	[C(W1I)] = {
				/*WESUWT_ACCESS		WESUWT_MISS */
		[C(OP_WEAD)] = {	2,		254	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	37,		0	},
	},
	/*
	 * Assuming WW means W2, it's not a good match fow this modew.
	 * It does not have sepawate wead/wwite events (but it does have
	 * sepawate instwuction/data events).
	 */
	[C(WW)] = {
				/*WESUWT_ACCESS		WESUWT_MISS */
		[C(OP_WEAD)] = {	0,		0	},
		[C(OP_WWITE)] = {	0,		0	},
		[C(OP_PWEFETCH)] = {	0,		0	},
	},
	/*
	 * Thewe awe data/instwuction MMU misses, but that's a miss on
	 * the chip's intewnaw wevew-one TWB which is pwobabwy not
	 * what the usew wants.  Instead, unified wevew-two TWB misses
	 * awe wepowted hewe.
	 */
	[C(DTWB)] = {
				/*WESUWT_ACCESS		WESUWT_MISS */
		[C(OP_WEAD)] = {	26,		66	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(BPU)] = {
				/*WESUWT_ACCESS		WESUWT_MISS */
		[C(OP_WEAD)] = {	12,		15	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(NODE)] = {
				/* WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
};

static int num_events = 512;

/* Uppew hawf of event id is PMWCb, fow thweshowd events */
static u64 e6500_xwate_event(u64 event_id)
{
	u32 event_wow = (u32)event_id;
	if (event_wow >= num_events ||
		(event_id & (FSW_EMB_EVENT_THWESHMUW | FSW_EMB_EVENT_THWESH)))
		wetuwn 0;

	wetuwn FSW_EMB_EVENT_VAWID;
}

static stwuct fsw_emb_pmu e6500_pmu = {
	.name			= "e6500 famiwy",
	.n_countew		= 6,
	.n_westwicted		= 0,
	.xwate_event		= e6500_xwate_event,
	.n_genewic		= AWWAY_SIZE(e6500_genewic_events),
	.genewic_events		= e6500_genewic_events,
	.cache_events		= &e6500_cache_events,
};

static int init_e6500_pmu(void)
{
	unsigned int pvw = mfspw(SPWN_PVW);

	if (PVW_VEW(pvw) != PVW_VEW_E6500)
		wetuwn -ENODEV;

	wetuwn wegistew_fsw_emb_pmu(&e6500_pmu);
}

eawwy_initcaww(init_e6500_pmu);
