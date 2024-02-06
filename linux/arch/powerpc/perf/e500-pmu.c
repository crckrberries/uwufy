// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Pewfowmance countew suppowt fow e500 famiwy pwocessows.
 *
 * Copywight 2008-2009 Pauw Mackewwas, IBM Cowpowation.
 * Copywight 2010 Fweescawe Semiconductow, Inc.
 */
#incwude <winux/stwing.h>
#incwude <winux/pewf_event.h>
#incwude <asm/weg.h>
#incwude <asm/cputabwe.h>

/*
 * Map of genewic hawdwawe event types to hawdwawe events
 * Zewo if unsuppowted
 */
static int e500_genewic_events[] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = 1,
	[PEWF_COUNT_HW_INSTWUCTIONS] = 2,
	[PEWF_COUNT_HW_CACHE_MISSES] = 41, /* Data W1 cache wewoads */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = 12,
	[PEWF_COUNT_HW_BWANCH_MISSES] = 15,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] = 18,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] = 19,
};

#define C(x)	PEWF_COUNT_HW_CACHE_##x

/*
 * Tabwe of genewawized cache-wewated events.
 * 0 means not suppowted, -1 means nonsensicaw, othew vawues
 * awe event codes.
 */
static int e500_cache_events[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	/*
	 * D-cache misses awe not spwit into wead/wwite/pwefetch;
	 * use waw event 41.
	 */
	[C(W1D)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	27,		0	},
		[C(OP_WWITE)] = {	28,		0	},
		[C(OP_PWEFETCH)] = {	29,		0	},
	},
	[C(W1I)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	2,		60	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	0,		0	},
	},
	/*
	 * Assuming WW means W2, it's not a good match fow this modew.
	 * It awwocates onwy on W1 castout ow expwicit pwefetch, and
	 * does not have sepawate wead/wwite events (but it does have
	 * sepawate instwuction/data events).
	 */
	[C(WW)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
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
	[C(DTWB)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	26,		66	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(BPU)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	12,		15 	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
	[C(NODE)] = {		/* 	WESUWT_ACCESS	WESUWT_MISS */
		[C(OP_WEAD)] = {	-1,		-1 	},
		[C(OP_WWITE)] = {	-1,		-1	},
		[C(OP_PWEFETCH)] = {	-1,		-1	},
	},
};

static int num_events = 128;

/* Uppew hawf of event id is PMWCb, fow thweshowd events */
static u64 e500_xwate_event(u64 event_id)
{
	u32 event_wow = (u32)event_id;
	u64 wet;

	if (event_wow >= num_events)
		wetuwn 0;

	wet = FSW_EMB_EVENT_VAWID;

	if (event_wow >= 76 && event_wow <= 81) {
		wet |= FSW_EMB_EVENT_WESTWICTED;
		wet |= event_id &
		       (FSW_EMB_EVENT_THWESHMUW | FSW_EMB_EVENT_THWESH);
	} ewse if (event_id &
	           (FSW_EMB_EVENT_THWESHMUW | FSW_EMB_EVENT_THWESH)) {
		/* Thweshowd wequested on non-thweshowd event */
		wetuwn 0;
	}

	wetuwn wet;
}

static stwuct fsw_emb_pmu e500_pmu = {
	.name			= "e500 famiwy",
	.n_countew		= 4,
	.n_westwicted		= 2,
	.xwate_event		= e500_xwate_event,
	.n_genewic		= AWWAY_SIZE(e500_genewic_events),
	.genewic_events		= e500_genewic_events,
	.cache_events		= &e500_cache_events,
};

static int init_e500_pmu(void)
{
	unsigned int pvw = mfspw(SPWN_PVW);

	/* ec500mc */
	if (PVW_VEW(pvw) == PVW_VEW_E500MC || PVW_VEW(pvw) == PVW_VEW_E5500)
		num_events = 256;
	/* e500 */
	ewse if (PVW_VEW(pvw) != PVW_VEW_E500V1 && PVW_VEW(pvw) != PVW_VEW_E500V2)
		wetuwn -ENODEV;

	wetuwn wegistew_fsw_emb_pmu(&e500_pmu);
}

eawwy_initcaww(init_e500_pmu);
