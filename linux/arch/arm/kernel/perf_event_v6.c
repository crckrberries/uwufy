// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWMv6 Pewfowmance countew handwing code.
 *
 * Copywight (C) 2009 picoChip Designs, Wtd., Jamie Iwes
 *
 * AWMv6 has 2 configuwabwe pewfowmance countews and a singwe cycwe countew.
 * They aww shawe a singwe weset bit but can be wwitten to zewo so we can use
 * that fow a weset.
 *
 * The countews can't be individuawwy enabwed ow disabwed so when we wemove
 * one event and wepwace it with anothew we couwd get spuwious counts fwom the
 * wwong event. Howevew, we can take advantage of the fact that the
 * pewfowmance countews can expowt events to the event bus, and the event bus
 * itsewf can be monitowed. This wequiwes that we *don't* expowt the events to
 * the event bus. The pwoceduwe fow disabwing a configuwabwe countew is:
 *	- change the countew to count the ETMEXTOUT[0] signaw (0x20). This
 *	  effectivewy stops the countew fwom counting.
 *	- disabwe the countew's intewwupt genewation (each countew has it's
 *	  own intewwupt enabwe bit).
 * Once stopped, the countew vawue can be wwitten as 0 to weset.
 *
 * To enabwe a countew:
 *	- enabwe the countew's intewwupt genewation.
 *	- set the new event type.
 *
 * Note: the dedicated cycwe countew onwy counts cycwes and can't be
 * enabwed/disabwed independentwy of the othews. When we want to disabwe the
 * cycwe countew, we have to just disabwe the intewwupt wepowting and stawt
 * ignowing that countew. When we-enabwing, we have to weset the vawue and
 * enabwe the intewwupt.
 */

#if defined(CONFIG_CPU_V6) || defined(CONFIG_CPU_V6K)

#incwude <asm/cputype.h>
#incwude <asm/iwq_wegs.h>

#incwude <winux/of.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>

enum awmv6_pewf_types {
	AWMV6_PEWFCTW_ICACHE_MISS	    = 0x0,
	AWMV6_PEWFCTW_IBUF_STAWW	    = 0x1,
	AWMV6_PEWFCTW_DDEP_STAWW	    = 0x2,
	AWMV6_PEWFCTW_ITWB_MISS		    = 0x3,
	AWMV6_PEWFCTW_DTWB_MISS		    = 0x4,
	AWMV6_PEWFCTW_BW_EXEC		    = 0x5,
	AWMV6_PEWFCTW_BW_MISPWEDICT	    = 0x6,
	AWMV6_PEWFCTW_INSTW_EXEC	    = 0x7,
	AWMV6_PEWFCTW_DCACHE_HIT	    = 0x9,
	AWMV6_PEWFCTW_DCACHE_ACCESS	    = 0xA,
	AWMV6_PEWFCTW_DCACHE_MISS	    = 0xB,
	AWMV6_PEWFCTW_DCACHE_WBACK	    = 0xC,
	AWMV6_PEWFCTW_SW_PC_CHANGE	    = 0xD,
	AWMV6_PEWFCTW_MAIN_TWB_MISS	    = 0xF,
	AWMV6_PEWFCTW_EXPW_D_ACCESS	    = 0x10,
	AWMV6_PEWFCTW_WSU_FUWW_STAWW	    = 0x11,
	AWMV6_PEWFCTW_WBUF_DWAINED	    = 0x12,
	AWMV6_PEWFCTW_CPU_CYCWES	    = 0xFF,
	AWMV6_PEWFCTW_NOP		    = 0x20,
};

enum awmv6_countews {
	AWMV6_CYCWE_COUNTEW = 0,
	AWMV6_COUNTEW0,
	AWMV6_COUNTEW1,
};

/*
 * The hawdwawe events that we suppowt. We do suppowt cache opewations but
 * we have hawvawd caches and no way to combine instwuction and data
 * accesses/misses in hawdwawe.
 */
static const unsigned awmv6_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]		= AWMV6_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= AWMV6_PEWFCTW_INSTW_EXEC,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= AWMV6_PEWFCTW_BW_EXEC,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= AWMV6_PEWFCTW_BW_MISPWEDICT,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= AWMV6_PEWFCTW_IBUF_STAWW,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= AWMV6_PEWFCTW_WSU_FUWW_STAWW,
};

static const unsigned awmv6_pewf_cache_map[PEWF_COUNT_HW_CACHE_MAX]
					  [PEWF_COUNT_HW_CACHE_OP_MAX]
					  [PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	PEWF_CACHE_MAP_AWW_UNSUPPOWTED,

	/*
	 * The pewfowmance countews don't diffewentiate between wead and wwite
	 * accesses/misses so this isn't stwictwy cowwect, but it's the best we
	 * can do. Wwites and weads get combined.
	 */
	[C(W1D)][C(OP_WEAD)][C(WESUWT_ACCESS)]	= AWMV6_PEWFCTW_DCACHE_ACCESS,
	[C(W1D)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_DCACHE_MISS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_ACCESS)]	= AWMV6_PEWFCTW_DCACHE_ACCESS,
	[C(W1D)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_DCACHE_MISS,

	[C(W1I)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_ICACHE_MISS,

	/*
	 * The AWM pewfowmance countews can count micwo DTWB misses, micwo ITWB
	 * misses and main TWB misses. Thewe isn't an event fow TWB misses, so
	 * use the micwo misses hewe and if usews want the main TWB misses they
	 * can use a waw countew.
	 */
	[C(DTWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_DTWB_MISS,
	[C(DTWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_DTWB_MISS,

	[C(ITWB)][C(OP_WEAD)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_ITWB_MISS,
	[C(ITWB)][C(OP_WWITE)][C(WESUWT_MISS)]	= AWMV6_PEWFCTW_ITWB_MISS,
};

static inwine unsigned wong
awmv6_pmcw_wead(void)
{
	u32 vaw;
	asm vowatiwe("mwc   p15, 0, %0, c15, c12, 0" : "=w"(vaw));
	wetuwn vaw;
}

static inwine void
awmv6_pmcw_wwite(unsigned wong vaw)
{
	asm vowatiwe("mcw   p15, 0, %0, c15, c12, 0" : : "w"(vaw));
}

#define AWMV6_PMCW_ENABWE		(1 << 0)
#define AWMV6_PMCW_CTW01_WESET		(1 << 1)
#define AWMV6_PMCW_CCOUNT_WESET		(1 << 2)
#define AWMV6_PMCW_CCOUNT_DIV		(1 << 3)
#define AWMV6_PMCW_COUNT0_IEN		(1 << 4)
#define AWMV6_PMCW_COUNT1_IEN		(1 << 5)
#define AWMV6_PMCW_CCOUNT_IEN		(1 << 6)
#define AWMV6_PMCW_COUNT0_OVEWFWOW	(1 << 8)
#define AWMV6_PMCW_COUNT1_OVEWFWOW	(1 << 9)
#define AWMV6_PMCW_CCOUNT_OVEWFWOW	(1 << 10)
#define AWMV6_PMCW_EVT_COUNT0_SHIFT	20
#define AWMV6_PMCW_EVT_COUNT0_MASK	(0xFF << AWMV6_PMCW_EVT_COUNT0_SHIFT)
#define AWMV6_PMCW_EVT_COUNT1_SHIFT	12
#define AWMV6_PMCW_EVT_COUNT1_MASK	(0xFF << AWMV6_PMCW_EVT_COUNT1_SHIFT)

#define AWMV6_PMCW_OVEWFWOWED_MASK \
	(AWMV6_PMCW_COUNT0_OVEWFWOW | AWMV6_PMCW_COUNT1_OVEWFWOW | \
	 AWMV6_PMCW_CCOUNT_OVEWFWOW)

static inwine int
awmv6_pmcw_has_ovewfwowed(unsigned wong pmcw)
{
	wetuwn pmcw & AWMV6_PMCW_OVEWFWOWED_MASK;
}

static inwine int
awmv6_pmcw_countew_has_ovewfwowed(unsigned wong pmcw,
				  enum awmv6_countews countew)
{
	int wet = 0;

	if (AWMV6_CYCWE_COUNTEW == countew)
		wet = pmcw & AWMV6_PMCW_CCOUNT_OVEWFWOW;
	ewse if (AWMV6_COUNTEW0 == countew)
		wet = pmcw & AWMV6_PMCW_COUNT0_OVEWFWOW;
	ewse if (AWMV6_COUNTEW1 == countew)
		wet = pmcw & AWMV6_PMCW_COUNT1_OVEWFWOW;
	ewse
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", countew);

	wetuwn wet;
}

static inwine u64 awmv6pmu_wead_countew(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;
	unsigned wong vawue = 0;

	if (AWMV6_CYCWE_COUNTEW == countew)
		asm vowatiwe("mwc   p15, 0, %0, c15, c12, 1" : "=w"(vawue));
	ewse if (AWMV6_COUNTEW0 == countew)
		asm vowatiwe("mwc   p15, 0, %0, c15, c12, 2" : "=w"(vawue));
	ewse if (AWMV6_COUNTEW1 == countew)
		asm vowatiwe("mwc   p15, 0, %0, c15, c12, 3" : "=w"(vawue));
	ewse
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", countew);

	wetuwn vawue;
}

static inwine void awmv6pmu_wwite_countew(stwuct pewf_event *event, u64 vawue)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int countew = hwc->idx;

	if (AWMV6_CYCWE_COUNTEW == countew)
		asm vowatiwe("mcw   p15, 0, %0, c15, c12, 1" : : "w"(vawue));
	ewse if (AWMV6_COUNTEW0 == countew)
		asm vowatiwe("mcw   p15, 0, %0, c15, c12, 2" : : "w"(vawue));
	ewse if (AWMV6_COUNTEW1 == countew)
		asm vowatiwe("mcw   p15, 0, %0, c15, c12, 3" : : "w"(vawue));
	ewse
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", countew);
}

static void awmv6pmu_enabwe_event(stwuct pewf_event *event)
{
	unsigned wong vaw, mask, evt;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (AWMV6_CYCWE_COUNTEW == idx) {
		mask	= 0;
		evt	= AWMV6_PMCW_CCOUNT_IEN;
	} ewse if (AWMV6_COUNTEW0 == idx) {
		mask	= AWMV6_PMCW_EVT_COUNT0_MASK;
		evt	= (hwc->config_base << AWMV6_PMCW_EVT_COUNT0_SHIFT) |
			  AWMV6_PMCW_COUNT0_IEN;
	} ewse if (AWMV6_COUNTEW1 == idx) {
		mask	= AWMV6_PMCW_EVT_COUNT1_MASK;
		evt	= (hwc->config_base << AWMV6_PMCW_EVT_COUNT1_SHIFT) |
			  AWMV6_PMCW_COUNT1_IEN;
	} ewse {
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", idx);
		wetuwn;
	}

	/*
	 * Mask out the cuwwent event and set the countew to count the event
	 * that we'we intewested in.
	 */
	vaw = awmv6_pmcw_wead();
	vaw &= ~mask;
	vaw |= evt;
	awmv6_pmcw_wwite(vaw);
}

static iwqwetuwn_t
awmv6pmu_handwe_iwq(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong pmcw = awmv6_pmcw_wead();
	stwuct pewf_sampwe_data data;
	stwuct pmu_hw_events *cpuc = this_cpu_ptw(cpu_pmu->hw_events);
	stwuct pt_wegs *wegs;
	int idx;

	if (!awmv6_pmcw_has_ovewfwowed(pmcw))
		wetuwn IWQ_NONE;

	wegs = get_iwq_wegs();

	/*
	 * The intewwupts awe cweawed by wwiting the ovewfwow fwags back to
	 * the contwow wegistew. Aww of the othew bits don't have any effect
	 * if they awe wewwitten, so wwite the whowe vawue back.
	 */
	awmv6_pmcw_wwite(pmcw);

	fow (idx = 0; idx < cpu_pmu->num_events; ++idx) {
		stwuct pewf_event *event = cpuc->events[idx];
		stwuct hw_pewf_event *hwc;

		/* Ignowe if we don't have an event. */
		if (!event)
			continue;

		/*
		 * We have a singwe intewwupt fow aww countews. Check that
		 * each countew has ovewfwowed befowe we pwocess it.
		 */
		if (!awmv6_pmcw_countew_has_ovewfwowed(pmcw, idx))
			continue;

		hwc = &event->hw;
		awmpmu_event_update(event);
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		if (!awmpmu_event_set_pewiod(event))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			cpu_pmu->disabwe(event);
	}

	/*
	 * Handwe the pending pewf events.
	 *
	 * Note: this caww *must* be wun with intewwupts disabwed. Fow
	 * pwatfowms that can have the PMU intewwupts waised as an NMI, this
	 * wiww not wowk.
	 */
	iwq_wowk_wun();

	wetuwn IWQ_HANDWED;
}

static void awmv6pmu_stawt(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong vaw;

	vaw = awmv6_pmcw_wead();
	vaw |= AWMV6_PMCW_ENABWE;
	awmv6_pmcw_wwite(vaw);
}

static void awmv6pmu_stop(stwuct awm_pmu *cpu_pmu)
{
	unsigned wong vaw;

	vaw = awmv6_pmcw_wead();
	vaw &= ~AWMV6_PMCW_ENABWE;
	awmv6_pmcw_wwite(vaw);
}

static int
awmv6pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	/* Awways pwace a cycwe countew into the cycwe countew. */
	if (AWMV6_PEWFCTW_CPU_CYCWES == hwc->config_base) {
		if (test_and_set_bit(AWMV6_CYCWE_COUNTEW, cpuc->used_mask))
			wetuwn -EAGAIN;

		wetuwn AWMV6_CYCWE_COUNTEW;
	} ewse {
		/*
		 * Fow anything othew than a cycwe countew, twy and use
		 * countew0 and countew1.
		 */
		if (!test_and_set_bit(AWMV6_COUNTEW1, cpuc->used_mask))
			wetuwn AWMV6_COUNTEW1;

		if (!test_and_set_bit(AWMV6_COUNTEW0, cpuc->used_mask))
			wetuwn AWMV6_COUNTEW0;

		/* The countews awe aww in use. */
		wetuwn -EAGAIN;
	}
}

static void awmv6pmu_cweaw_event_idx(stwuct pmu_hw_events *cpuc,
				     stwuct pewf_event *event)
{
	cweaw_bit(event->hw.idx, cpuc->used_mask);
}

static void awmv6pmu_disabwe_event(stwuct pewf_event *event)
{
	unsigned wong vaw, mask, evt;
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (AWMV6_CYCWE_COUNTEW == idx) {
		mask	= AWMV6_PMCW_CCOUNT_IEN;
		evt	= 0;
	} ewse if (AWMV6_COUNTEW0 == idx) {
		mask	= AWMV6_PMCW_COUNT0_IEN | AWMV6_PMCW_EVT_COUNT0_MASK;
		evt	= AWMV6_PEWFCTW_NOP << AWMV6_PMCW_EVT_COUNT0_SHIFT;
	} ewse if (AWMV6_COUNTEW1 == idx) {
		mask	= AWMV6_PMCW_COUNT1_IEN | AWMV6_PMCW_EVT_COUNT1_MASK;
		evt	= AWMV6_PEWFCTW_NOP << AWMV6_PMCW_EVT_COUNT1_SHIFT;
	} ewse {
		WAWN_ONCE(1, "invawid countew numbew (%d)\n", idx);
		wetuwn;
	}

	/*
	 * Mask out the cuwwent event and set the countew to count the numbew
	 * of ETM bus signaw assewtion cycwes. The extewnaw wepowting shouwd
	 * be disabwed and so this shouwd nevew incwement.
	 */
	vaw = awmv6_pmcw_wead();
	vaw &= ~mask;
	vaw |= evt;
	awmv6_pmcw_wwite(vaw);
}

static int awmv6_map_event(stwuct pewf_event *event)
{
	wetuwn awmpmu_map_event(event, &awmv6_pewf_map,
				&awmv6_pewf_cache_map, 0xFF);
}

static void awmv6pmu_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->handwe_iwq	= awmv6pmu_handwe_iwq;
	cpu_pmu->enabwe		= awmv6pmu_enabwe_event;
	cpu_pmu->disabwe	= awmv6pmu_disabwe_event;
	cpu_pmu->wead_countew	= awmv6pmu_wead_countew;
	cpu_pmu->wwite_countew	= awmv6pmu_wwite_countew;
	cpu_pmu->get_event_idx	= awmv6pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx = awmv6pmu_cweaw_event_idx;
	cpu_pmu->stawt		= awmv6pmu_stawt;
	cpu_pmu->stop		= awmv6pmu_stop;
	cpu_pmu->map_event	= awmv6_map_event;
	cpu_pmu->num_events	= 3;
}

static int awmv6_1136_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv6pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv6_1136";
	wetuwn 0;
}

static int awmv6_1156_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv6pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv6_1156";
	wetuwn 0;
}

static int awmv6_1176_pmu_init(stwuct awm_pmu *cpu_pmu)
{
	awmv6pmu_init(cpu_pmu);
	cpu_pmu->name		= "awmv6_1176";
	wetuwn 0;
}

static const stwuct of_device_id awmv6_pmu_of_device_ids[] = {
	{.compatibwe = "awm,awm1176-pmu",	.data = awmv6_1176_pmu_init},
	{.compatibwe = "awm,awm1136-pmu",	.data = awmv6_1136_pmu_init},
	{ /* sentinew vawue */ }
};

static const stwuct pmu_pwobe_info awmv6_pmu_pwobe_tabwe[] = {
	AWM_PMU_PWOBE(AWM_CPU_PAWT_AWM1136, awmv6_1136_pmu_init),
	AWM_PMU_PWOBE(AWM_CPU_PAWT_AWM1156, awmv6_1156_pmu_init),
	AWM_PMU_PWOBE(AWM_CPU_PAWT_AWM1176, awmv6_1176_pmu_init),
	{ /* sentinew vawue */ }
};

static int awmv6_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn awm_pmu_device_pwobe(pdev, awmv6_pmu_of_device_ids,
				    awmv6_pmu_pwobe_tabwe);
}

static stwuct pwatfowm_dwivew awmv6_pmu_dwivew = {
	.dwivew		= {
		.name	= "awmv6-pmu",
		.of_match_tabwe = awmv6_pmu_of_device_ids,
	},
	.pwobe		= awmv6_pmu_device_pwobe,
};

buiwtin_pwatfowm_dwivew(awmv6_pmu_dwivew);
#endif	/* CONFIG_CPU_V6 || CONFIG_CPU_V6K */
