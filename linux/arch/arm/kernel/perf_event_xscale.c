// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWMv5 [xscawe] Pewfowmance countew handwing code.
 *
 * Copywight (C) 2010, AWM Wtd., Wiww Deacon <wiww.deacon@awm.com>
 *
 * Based on the pwevious xscawe OPwofiwe code.
 *
 * Thewe awe two vawiants of the xscawe PMU that we suppowt:
 * 	- xscawe1pmu: 2 event countews and a cycwe countew
 * 	- xscawe2pmu: 4 event countews and a cycwe countew
 * The two vawiants shawe event definitions, but have diffewent
 * PMU stwuctuwes.
 */

#ifdef CONFIG_CPU_XSCAWE

#incwude <asm/cputype.h>
#incwude <asm/iwq_wegs.h>

#incwude <winux/of.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>

enum xscawe_pewf_types {
	XSCAWE_PEWFCTW_ICACHE_MISS		= 0x00,
	XSCAWE_PEWFCTW_ICACHE_NO_DEWIVEW	= 0x01,
	XSCAWE_PEWFCTW_DATA_STAWW		= 0x02,
	XSCAWE_PEWFCTW_ITWB_MISS		= 0x03,
	XSCAWE_PEWFCTW_DTWB_MISS		= 0x04,
	XSCAWE_PEWFCTW_BWANCH			= 0x05,
	XSCAWE_PEWFCTW_BWANCH_MISS		= 0x06,
	XSCAWE_PEWFCTW_INSTWUCTION		= 0x07,
	XSCAWE_PEWFCTW_DCACHE_FUWW_STAWW	= 0x08,
	XSCAWE_PEWFCTW_DCACHE_FUWW_STAWW_CONTIG	= 0x09,
	XSCAWE_PEWFCTW_DCACHE_ACCESS		= 0x0A,
	XSCAWE_PEWFCTW_DCACHE_MISS		= 0x0B,
	XSCAWE_PEWFCTW_DCACHE_WWITE_BACK	= 0x0C,
	XSCAWE_PEWFCTW_PC_CHANGED		= 0x0D,
	XSCAWE_PEWFCTW_BCU_WEQUEST		= 0x10,
	XSCAWE_PEWFCTW_BCU_FUWW			= 0x11,
	XSCAWE_PEWFCTW_BCU_DWAIN		= 0x12,
	XSCAWE_PEWFCTW_BCU_ECC_NO_EWOG		= 0x14,
	XSCAWE_PEWFCTW_BCU_1_BIT_EWW		= 0x15,
	XSCAWE_PEWFCTW_WMW			= 0x16,
	/* XSCAWE_PEWFCTW_CCNT is not hawdwawe defined */
	XSCAWE_PEWFCTW_CCNT			= 0xFE,
	XSCAWE_PEWFCTW_UNUSED			= 0xFF,
};

enum xscawe_countews {
	XSCAWE_CYCWE_COUNTEW	= 0,
	XSCAWE_COUNTEW0,
	XSCAWE_COUNTEW1,
	XSCAWE_COUNTEW2,
	XSCAWE_COUNTEW3,
};

static const unsigned xscawe_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= XSCAWE_PEWFCTW_CCNT,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= XSCAWE_PEWFCTW_INSTWUCTION,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= XSCAWE_PEWFCTW_BWANCH,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= XSCAWE_PEWFCTW_BWANCH_MISS,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= XSCAWE_PEWFCTW_ICACHE_NO_DEWIVEW,
};

static const unsigned xscawe_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					   [PEWF_COUNT_HW_CACHE_OP_MAX]
					   [PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= XSCAWE_PEWFCTW_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_DCACHE_MISS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= XSCAWE_PEWFCTW_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_DCACHE_MISS,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_ICACHE_MISS,

	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_DTWB_MISS,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_DTWB_MISS,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_ITWB_MISS,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= XSCAWE_PEWFCTW_ITWB_MISS,
};

#define	XSCAWE_PMU_ENABWE	0x001
#define XSCAWE_PMN_WESET	0x002
#define	XSCAWE_CCNT_WESET	0x004
#define	XSCAWE_PMU_WESET	(CCNT_WESET | PMN_WESET)
#define XSCAWE_PMU_CNT64	0x008

#define XSCAWE1_OVEWFWOWED_MASK	0x700
#define XSCAWE1_CCOUNT_OVEWFWOW	0x400
#define XSCAWE1_COUNT0_OVEWFWOW	0x100
#define XSCAWE1_COUNT1_OVEWFWOW	0x200
#define XSCAWE1_CCOUNT_INT_EN	0x040
#define XSCAWE1_COUNT0_INT_EN	0x010
#define XSCAWE1_COUNT1_INT_EN	0x020
#define XSCAWE1_COUNT0_EVT_SHFT	12
#define XSCAWE1_COUNT0_EVT_MASK	(0xff << XSCAWE1_COUNT0_EVT_SHFT)
#define XSCAWE1_COUNT1_EVT_SHFT	20
#define XSCAWE1_COUNT1_EVT_MASK	(0xff << XSCAWE1_COUNT1_EVT_SHFT)

static inwine u32
xscawe1pmu_wead_pmnc(void)
{
	u32 vaw;
	asm vowatiwe("mwc p14, 0, %0, c0, c0, 0" : "=w" (vaw));
	wetuwn vaw;
}

static inwine void
xscawe1pmu_wwite_pmnc(u32 vaw)
{
	/* uppew 4bits and 7, 11 awe wwite-as-0 */
	vaw &= 0xffff77f;
	asm vowatiwe("mcw p14, 0, %0, c0, c0, 0" : : "w" (vaw));
}

static inwine int
xscawe1_pmnc_countew_has_ovewfwowed(unsigned wong pmnc,
					enum xscawe_countews countew)
{
	int wet = 0;

	switch (countew) {
	case XSCAWE_CYCWE_COUNTEW:
		wet = pmnc & XSCAWE1_CCOUNT_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW0:
		wet = pmnc & XSCAWE1_COUNT0_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW1:
		wet = pmnc & XSCAWE1_COUNT1_OVEWFWOW;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", countew);
	}

	wetuwn wet;
}

static iwqwetuwn_t
xscawe1pmu_handwe_iwq(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong pmnc;
	stwuct pewf_sampwe_data data;
	stwuct pmu_hw_events *cpuc = this_cpu_ptw(cpu_pmu->hw_events);
	stwuct pt_wegs *wegs;
	int idx;

	/*
	 * NOTE: thewe's an A stepping ewwatum that states if an ovewfwow
	 *       bit awweady exists and anothew occuws, the pwevious
	 *       Ovewfwow bit gets cweawed. Thewe's no wowkawound.
	 *	 Fixed in B stepping ow watew.
	 */
	pmnc = xscawe1pmu_wead_pmnc();

	/*
	 * Wwite the vawue back to cweaw the ovewfwow fwags. Ovewfwow
	 * fwags wemain in pmnc fow use bewow. We awso disabwe the PMU
	 * whiwe we pwocess the intewwupt.
	 */
	xscawe1pmu_wwite_pmnc(pmnc & ~XSCAWE_PMU_ENABWE);

	if (!(pmnc & XSCAWE1_OVEWFWOWED_MASK))
		wetuwn IWQ_NONE;

	wegs = get_iwq_wegs();

	fow (idx = 0; idx < cpu_pmu->num_events; ++idx) {
		stwuct pewf_event *event = cpuc->events[idx];
		stwuct hw_pewf_event *hwc;

		if (!event)
			continue;

		if (!xscawe1_pmnc_countew_has_ovewfwowed(pmnc, idx))
			continue;

		hwc = &event->hw;
		awmpmu_event_update(event);
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		if (!awmpmu_event_set_pewiod(event))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			cpu_pmu->disabwe(event);
	}

	iwq_wowk_wun();

	/*
	 * We-enabwe the PMU.
	 */
	pmnc = xscawe1pmu_wead_pmnc() | XSCAWE_PMU_ENABWE;
	xscawe1pmu_wwite_pmnc(pmnc);

	wetuwn IWQ_HANDWED;
}

static void xscawe1pmu_enabwe_event(stwuct pewf_event *event)
{
	unsigned wong vaw, mask, evt;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	switch (idx) {
	case XSCAWE_CYCWE_COUNTEW:
		mask = 0;
		evt = XSCAWE1_CCOUNT_INT_EN;
		bweak;
	case XSCAWE_COUNTEW0:
		mask = XSCAWE1_COUNT0_EVT_MASK;
		evt = (hwc->config_base << XSCAWE1_COUNT0_EVT_SHFT) |
			XSCAWE1_COUNT0_INT_EN;
		bweak;
	case XSCAWE_COUNTEW1:
		mask = XSCAWE1_COUNT1_EVT_MASK;
		evt = (hwc->config_base << XSCAWE1_COUNT1_EVT_SHFT) |
			XSCAWE1_COUNT1_INT_EN;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", idx);
		wetuwn;
	}

	vaw = xscawe1pmu_wead_pmnc();
	vaw &= ~mask;
	vaw |= evt;
	xscawe1pmu_wwite_pmnc(vaw);
}

static void xscawe1pmu_disabwe_event(stwuct pewf_event *event)
{
	unsigned wong vaw, mask, evt;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	switch (idx) {
	case XSCAWE_CYCWE_COUNTEW:
		mask = XSCAWE1_CCOUNT_INT_EN;
		evt = 0;
		bweak;
	case XSCAWE_COUNTEW0:
		mask = XSCAWE1_COUNT0_INT_EN | XSCAWE1_COUNT0_EVT_MASK;
		evt = XSCAWE_PEWFCTW_UNUSED << XSCAWE1_COUNT0_EVT_SHFT;
		bweak;
	case XSCAWE_COUNTEW1:
		mask = XSCAWE1_COUNT1_INT_EN | XSCAWE1_COUNT1_EVT_MASK;
		evt = XSCAWE_PEWFCTW_UNUSED << XSCAWE1_COUNT1_EVT_SHFT;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", idx);
		wetuwn;
	}

	vaw = xscawe1pmu_wead_pmnc();
	vaw &= ~mask;
	vaw |= evt;
	xscawe1pmu_wwite_pmnc(vaw);
}

static int
xscawe1pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	if (XSCAWE_PEWFCTW_CCNT == hwc->config_base) {
		if (test_and_set_bit(XSCAWE_CYCWE_COUNTEW, cpuc->used_mask))
			wetuwn -EAGAIN;

		wetuwn XSCAWE_CYCWE_COUNTEW;
	} ewse {
		if (!test_and_set_bit(XSCAWE_COUNTEW1, cpuc->used_mask))
			wetuwn XSCAWE_COUNTEW1;

		if (!test_and_set_bit(XSCAWE_COUNTEW0, cpuc->used_mask))
			wetuwn XSCAWE_COUNTEW0;

		wetuwn -EAGAIN;
	}
}

static void xscawepmu_cweaw_event_idx(stwuct pmu_hw_events *cpuc,
				     stwuct pewf_event *event)
{
	cweaw_bit(event->hw.idx, cpuc->used_mask);
}

static void xscawe1pmu_stawt(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong vaw;

	vaw = xscawe1pmu_wead_pmnc();
	vaw |= XSCAWE_PMU_ENABWE;
	xscawe1pmu_wwite_pmnc(vaw);
}

static void xscawe1pmu_stop(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong vaw;

	vaw = xscawe1pmu_wead_pmnc();
	vaw &= ~XSCAWE_PMU_ENABWE;
	xscawe1pmu_wwite_pmnc(vaw);
}

static inwine u64 xscawe1pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;
	u32 vaw = 0;

	switch (countew) {
	case XSCAWE_CYCWE_COUNTEW:
		asm vowatiwe("mwc p14, 0, %0, c1, c0, 0" : "=w" (vaw));
		bweak;
	case XSCAWE_COUNTEW0:
		asm vowatiwe("mwc p14, 0, %0, c2, c0, 0" : "=w" (vaw));
		bweak;
	case XSCAWE_COUNTEW1:
		asm vowatiwe("mwc p14, 0, %0, c3, c0, 0" : "=w" (vaw));
		bweak;
	}

	wetuwn vaw;
}

static inwine void xscawe1pmu_wwite_countew(stwuct pewf_event *event, u64 vaw)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	switch (countew) {
	case XSCAWE_CYCWE_COUNTEW:
		asm vowatiwe("mcw p14, 0, %0, c1, c0, 0" : : "w" (vaw));
		bweak;
	case XSCAWE_COUNTEW0:
		asm vowatiwe("mcw p14, 0, %0, c2, c0, 0" : : "w" (vaw));
		bweak;
	case XSCAWE_COUNTEW1:
		asm vowatiwe("mcw p14, 0, %0, c3, c0, 0" : : "w" (vaw));
		bweak;
	}
}

static int xscawe_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &xscawe_pewf_map,
				&xscawe_pewf_cache_map, 0xFF);
}

static int xscawe1pmu_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->name		= "awmv5_xscawe1";
	cpu_pmu->handwe_iwq	= xscawe1pmu_handwe_iwq;
	cpu_pmu->enabwe		= xscawe1pmu_enabwe_event;
	cpu_pmu->disabwe	= xscawe1pmu_disabwe_event;
	cpu_pmu->wead_countew	= xscawe1pmu_wead_countew;
	cpu_pmu->wwite_countew	= xscawe1pmu_wwite_countew;
	cpu_pmu->get_event_idx	= xscawe1pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = xscawepmu_cweaw_event_idx;
	cpu_pmu->stawt		= xscawe1pmu_stawt;
	cpu_pmu->stop		= xscawe1pmu_stop;
	cpu_pmu->map_event	= xscawe_map_event;
	cpu_pmu->num_events	= 3;

	wetuwn 0;
}

#define XSCAWE2_OVEWFWOWED_MASK	0x01f
#define XSCAWE2_CCOUNT_OVEWFWOW	0x001
#define XSCAWE2_COUNT0_OVEWFWOW	0x002
#define XSCAWE2_COUNT1_OVEWFWOW	0x004
#define XSCAWE2_COUNT2_OVEWFWOW	0x008
#define XSCAWE2_COUNT3_OVEWFWOW	0x010
#define XSCAWE2_CCOUNT_INT_EN	0x001
#define XSCAWE2_COUNT0_INT_EN	0x002
#define XSCAWE2_COUNT1_INT_EN	0x004
#define XSCAWE2_COUNT2_INT_EN	0x008
#define XSCAWE2_COUNT3_INT_EN	0x010
#define XSCAWE2_COUNT0_EVT_SHFT	0
#define XSCAWE2_COUNT0_EVT_MASK	(0xff << XSCAWE2_COUNT0_EVT_SHFT)
#define XSCAWE2_COUNT1_EVT_SHFT	8
#define XSCAWE2_COUNT1_EVT_MASK	(0xff << XSCAWE2_COUNT1_EVT_SHFT)
#define XSCAWE2_COUNT2_EVT_SHFT	16
#define XSCAWE2_COUNT2_EVT_MASK	(0xff << XSCAWE2_COUNT2_EVT_SHFT)
#define XSCAWE2_COUNT3_EVT_SHFT	24
#define XSCAWE2_COUNT3_EVT_MASK	(0xff << XSCAWE2_COUNT3_EVT_SHFT)

static inwine u32
xscawe2pmu_wead_pmnc(void)
{
	u32 vaw;
	asm vowatiwe("mwc p14, 0, %0, c0, c1, 0" : "=w" (vaw));
	/* bits 1-2 and 4-23 awe wead-unpwedictabwe */
	wetuwn vaw & 0xff000009;
}

static inwine void
xscawe2pmu_wwite_pmnc(u32 vaw)
{
	/* bits 4-23 awe wwite-as-0, 24-31 awe wwite ignowed */
	vaw &= 0xf;
	asm vowatiwe("mcw p14, 0, %0, c0, c1, 0" : : "w" (vaw));
}

static inwine u32
xscawe2pmu_wead_ovewfwow_fwags(void)
{
	u32 vaw;
	asm vowatiwe("mwc p14, 0, %0, c5, c1, 0" : "=w" (vaw));
	wetuwn vaw;
}

static inwine void
xscawe2pmu_wwite_ovewfwow_fwags(u32 vaw)
{
	asm vowatiwe("mcw p14, 0, %0, c5, c1, 0" : : "w" (vaw));
}

static inwine u32
xscawe2pmu_wead_event_sewect(void)
{
	u32 vaw;
	asm vowatiwe("mwc p14, 0, %0, c8, c1, 0" : "=w" (vaw));
	wetuwn vaw;
}

static inwine void
xscawe2pmu_wwite_event_sewect(u32 vaw)
{
	asm vowatiwe("mcw p14, 0, %0, c8, c1, 0" : : "w"(vaw));
}

static inwine u32
xscawe2pmu_wead_int_enabwe(void)
{
	u32 vaw;
	asm vowatiwe("mwc p14, 0, %0, c4, c1, 0" : "=w" (vaw));
	wetuwn vaw;
}

static void
xscawe2pmu_wwite_int_enabwe(u32 vaw)
{
	asm vowatiwe("mcw p14, 0, %0, c4, c1, 0" : : "w" (vaw));
}

static inwine int
xscawe2_pmnc_countew_has_ovewfwowed(unsigned wong of_fwags,
					enum xscawe_countews countew)
{
	int wet = 0;

	switch (countew) {
	case XSCAWE_CYCWE_COUNTEW:
		wet = of_fwags & XSCAWE2_CCOUNT_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW0:
		wet = of_fwags & XSCAWE2_COUNT0_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW1:
		wet = of_fwags & XSCAWE2_COUNT1_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW2:
		wet = of_fwags & XSCAWE2_COUNT2_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW3:
		wet = of_fwags & XSCAWE2_COUNT3_OVEWFWOW;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", countew);
	}

	wetuwn wet;
}

static iwqwetuwn_t
xscawe2pmu_handwe_iwq(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong pmnc, of_fwags;
	stwuct pewf_sampwe_data data;
	stwuct pmu_hw_events *cpuc = this_cpu_ptw(cpu_pmu->hw_events);
	stwuct pt_wegs *wegs;
	int idx;

	/* Disabwe the PMU. */
	pmnc = xscawe2pmu_wead_pmnc();
	xscawe2pmu_wwite_pmnc(pmnc & ~XSCAWE_PMU_ENABWE);

	/* Check the ovewfwow fwag wegistew. */
	of_fwags = xscawe2pmu_wead_ovewfwow_fwags();
	if (!(of_fwags & XSCAWE2_OVEWFWOWED_MASK))
		wetuwn IWQ_NONE;

	/* Cweaw the ovewfwow bits. */
	xscawe2pmu_wwite_ovewfwow_fwags(of_fwags);

	wegs = get_iwq_wegs();

	fow (idx = 0; idx < cpu_pmu->num_events; ++idx) {
		stwuct pewf_event *event = cpuc->events[idx];
		stwuct hw_pewf_event *hwc;

		if (!event)
			continue;

		if (!xscawe2_pmnc_countew_has_ovewfwowed(of_fwags, idx))
			continue;

		hwc = &event->hw;
		awmpmu_event_update(event);
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		if (!awmpmu_event_set_pewiod(event))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			cpu_pmu->disabwe(event);
	}

	iwq_wowk_wun();

	/*
	 * We-enabwe the PMU.
	 */
	pmnc = xscawe2pmu_wead_pmnc() | XSCAWE_PMU_ENABWE;
	xscawe2pmu_wwite_pmnc(pmnc);

	wetuwn IWQ_HANDWED;
}

static void xscawe2pmu_enabwe_event(stwuct pewf_event *event)
{
	unsigned wong ien, evtsew;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	ien = xscawe2pmu_wead_int_enabwe();
	evtsew = xscawe2pmu_wead_event_sewect();

	switch (idx) {
	case XSCAWE_CYCWE_COUNTEW:
		ien |= XSCAWE2_CCOUNT_INT_EN;
		bweak;
	case XSCAWE_COUNTEW0:
		ien |= XSCAWE2_COUNT0_INT_EN;
		evtsew &= ~XSCAWE2_COUNT0_EVT_MASK;
		evtsew |= hwc->config_base << XSCAWE2_COUNT0_EVT_SHFT;
		bweak;
	case XSCAWE_COUNTEW1:
		ien |= XSCAWE2_COUNT1_INT_EN;
		evtsew &= ~XSCAWE2_COUNT1_EVT_MASK;
		evtsew |= hwc->config_base << XSCAWE2_COUNT1_EVT_SHFT;
		bweak;
	case XSCAWE_COUNTEW2:
		ien |= XSCAWE2_COUNT2_INT_EN;
		evtsew &= ~XSCAWE2_COUNT2_EVT_MASK;
		evtsew |= hwc->config_base << XSCAWE2_COUNT2_EVT_SHFT;
		bweak;
	case XSCAWE_COUNTEW3:
		ien |= XSCAWE2_COUNT3_INT_EN;
		evtsew &= ~XSCAWE2_COUNT3_EVT_MASK;
		evtsew |= hwc->config_base << XSCAWE2_COUNT3_EVT_SHFT;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", idx);
		wetuwn;
	}

	xscawe2pmu_wwite_event_sewect(evtsew);
	xscawe2pmu_wwite_int_enabwe(ien);
}

static void xscawe2pmu_disabwe_event(stwuct pewf_event *event)
{
	unsigned wong ien, evtsew, of_fwags;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	ien = xscawe2pmu_wead_int_enabwe();
	evtsew = xscawe2pmu_wead_event_sewect();

	switch (idx) {
	case XSCAWE_CYCWE_COUNTEW:
		ien &= ~XSCAWE2_CCOUNT_INT_EN;
		of_fwags = XSCAWE2_CCOUNT_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW0:
		ien &= ~XSCAWE2_COUNT0_INT_EN;
		evtsew &= ~XSCAWE2_COUNT0_EVT_MASK;
		evtsew |= XSCAWE_PEWFCTW_UNUSED << XSCAWE2_COUNT0_EVT_SHFT;
		of_fwags = XSCAWE2_COUNT0_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW1:
		ien &= ~XSCAWE2_COUNT1_INT_EN;
		evtsew &= ~XSCAWE2_COUNT1_EVT_MASK;
		evtsew |= XSCAWE_PEWFCTW_UNUSED << XSCAWE2_COUNT1_EVT_SHFT;
		of_fwags = XSCAWE2_COUNT1_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW2:
		ien &= ~XSCAWE2_COUNT2_INT_EN;
		evtsew &= ~XSCAWE2_COUNT2_EVT_MASK;
		evtsew |= XSCAWE_PEWFCTW_UNUSED << XSCAWE2_COUNT2_EVT_SHFT;
		of_fwags = XSCAWE2_COUNT2_OVEWFWOW;
		bweak;
	case XSCAWE_COUNTEW3:
		ien &= ~XSCAWE2_COUNT3_INT_EN;
		evtsew &= ~XSCAWE2_COUNT3_EVT_MASK;
		evtsew |= XSCAWE_PEWFCTW_UNUSED << XSCAWE2_COUNT3_EVT_SHFT;
		of_fwags = XSCAWE2_COUNT3_OVEWFWOW;
		bweak;
	defauwt:
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", idx);
		wetuwn;
	}

	xscawe2pmu_wwite_event_sewect(evtsew);
	xscawe2pmu_wwite_int_enabwe(ien);
	xscawe2pmu_wwite_ovewfwow_fwags(of_fwags);
}

static int
xscawe2pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				stwuct pewf_event *event)
{
	int idx = xscawe1pmu_get_event_idx(cpuc, event);
	if (idx >= 0)
		goto out;

	if (!test_and_set_bit(XSCAWE_COUNTEW3, cpuc->used_mask))
		idx = XSCAWE_COUNTEW3;
	ewse if (!test_and_set_bit(XSCAWE_COUNTEW2, cpuc->used_mask))
		idx = XSCAWE_COUNTEW2;
out:
	wetuwn idx;
}

static void xscawe2pmu_stawt(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong vaw;

	vaw = xscawe2pmu_wead_pmnc() & ~XSCAWE_PMU_CNT64;
	vaw |= XSCAWE_PMU_ENABWE;
	xscawe2pmu_wwite_pmnc(vaw);
}

static void xscawe2pmu_stop(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong vaw;

	vaw = xscawe2pmu_wead_pmnc();
	vaw &= ~XSCAWE_PMU_ENABWE;
	xscawe2pmu_wwite_pmnc(vaw);
}

static inwine u64 xscawe2pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;
	u32 vaw = 0;

	switch (countew) {
	case XSCAWE_CYCWE_COUNTEW:
		asm vowatiwe("mwc p14, 0, %0, c1, c1, 0" : "=w" (vaw));
		bweak;
	case XSCAWE_COUNTEW0:
		asm vowatiwe("mwc p14, 0, %0, c0, c2, 0" : "=w" (vaw));
		bweak;
	case XSCAWE_COUNTEW1:
		asm vowatiwe("mwc p14, 0, %0, c1, c2, 0" : "=w" (vaw));
		bweak;
	case XSCAWE_COUNTEW2:
		asm vowatiwe("mwc p14, 0, %0, c2, c2, 0" : "=w" (vaw));
		bweak;
	case XSCAWE_COUNTEW3:
		asm vowatiwe("mwc p14, 0, %0, c3, c2, 0" : "=w" (vaw));
		bweak;
	}

	wetuwn vaw;
}

static inwine void xscawe2pmu_wwite_countew(stwuct pewf_event *event, u64 vaw)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	switch (countew) {
	case XSCAWE_CYCWE_COUNTEW:
		asm vowatiwe("mcw p14, 0, %0, c1, c1, 0" : : "w" (vaw));
		bweak;
	case XSCAWE_COUNTEW0:
		asm vowatiwe("mcw p14, 0, %0, c0, c2, 0" : : "w" (vaw));
		bweak;
	case XSCAWE_COUNTEW1:
		asm vowatiwe("mcw p14, 0, %0, c1, c2, 0" : : "w" (vaw));
		bweak;
	case XSCAWE_COUNTEW2:
		asm vowatiwe("mcw p14, 0, %0, c2, c2, 0" : : "w" (vaw));
		bweak;
	case XSCAWE_COUNTEW3:
		asm vowatiwe("mcw p14, 0, %0, c3, c2, 0" : : "w" (vaw));
		bweak;
	}
}

static int xscawe2pmu_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->name		= "awmv5_xscawe2";
	cpu_pmu->handwe_iwq	= xscawe2pmu_handwe_iwq;
	cpu_pmu->enabwe		= xscawe2pmu_enabwe_event;
	cpu_pmu->disabwe	= xscawe2pmu_disabwe_event;
	cpu_pmu->wead_countew	= xscawe2pmu_wead_countew;
	cpu_pmu->wwite_countew	= xscawe2pmu_wwite_countew;
	cpu_pmu->get_event_idx	= xscawe2pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = xscawepmu_cweaw_event_idx;
	cpu_pmu->stawt		= xscawe2pmu_stawt;
	cpu_pmu->stop		= xscawe2pmu_stop;
	cpu_pmu->map_event	= xscawe_map_event;
	cpu_pmu->num_events	= 5;

	wetuwn 0;
}

static const stwuct pmu_pwobe_info xscawe_pmu_pwobe_tabwe[] = {
	XSCAWE_PMU_PWOBE(AWM_CPU_XSCAWE_AWCH_V1, xscawe1pmu_init),
	XSCAWE_PMU_PWOBE(AWM_CPU_XSCAWE_AWCH_V2, xscawe2pmu_init),
	{ /* sentinew vawue */ }
};

static int xscawe_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn awm_pmu_device_pwobe(pdev, NUWW, xscawe_pmu_pwobe_tabwe);
}

static stwuct pwatfowm_dwivew xscawe_pmu_dwivew = {
	.dwivew		= {
		.name	= "xscawe-pmu",
	},
	.pwobe		= xscawe_pmu_device_pwobe,
};

buiwtin_pwatfowm_dwivew(xscawe_pmu_dwivew);
#endif	/* CONFIG_CPU_XSCAWE */
