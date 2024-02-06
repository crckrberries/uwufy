// SPDX-Wicense-Identifiew: GPW-2.0
/* Dwivew fow Intew Xeon Phi "Knights Cownew" PMU */

#incwude <winux/pewf_event.h>
#incwude <winux/types.h>

#incwude <asm/hawdiwq.h>

#incwude "../pewf_event.h"

static const u64 knc_pewfmon_event_map[] =
{
  [PEWF_COUNT_HW_CPU_CYCWES]		= 0x002a,
  [PEWF_COUNT_HW_INSTWUCTIONS]		= 0x0016,
  [PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x0028,
  [PEWF_COUNT_HW_CACHE_MISSES]		= 0x0029,
  [PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x0012,
  [PEWF_COUNT_HW_BWANCH_MISSES]		= 0x002b,
};

static const u64 __initconst knc_hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] =
{
 [ C(W1D) ] = {
	[ C(OP_WEAD) ] = {
		/* On Xeon Phi event "0" is a vawid DATA_WEAD          */
		/*   (W1 Data Cache Weads) Instwuction.                */
		/* We code this as AWCH_PEWFMON_EVENTSEW_INT as this   */
		/* bit wiww awways be set in x86_pmu_hw_config().      */
		[ C(WESUWT_ACCESS) ] = AWCH_PEWFMON_EVENTSEW_INT,
						/* DATA_WEAD           */
		[ C(WESUWT_MISS)   ] = 0x0003,	/* DATA_WEAD_MISS      */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0001,	/* DATA_WWITE          */
		[ C(WESUWT_MISS)   ] = 0x0004,	/* DATA_WWITE_MISS     */
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0011,	/* W1_DATA_PF1         */
		[ C(WESUWT_MISS)   ] = 0x001c,	/* W1_DATA_PF1_MISS    */
	},
 },
 [ C(W1I ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x000c,	/* CODE_WEAD          */
		[ C(WESUWT_MISS)   ] = 0x000e,	/* CODE_CACHE_MISS    */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0,
		[ C(WESUWT_MISS)   ] = 0x0,
	},
 },
 [ C(WW  ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0x10cb,	/* W2_WEAD_MISS */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0x10cc,	/* W2_WWITE_HIT */
		[ C(WESUWT_MISS)   ] = 0,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0x10fc,	/* W2_DATA_PF2      */
		[ C(WESUWT_MISS)   ] = 0x10fe,	/* W2_DATA_PF2_MISS */
	},
 },
 [ C(DTWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = AWCH_PEWFMON_EVENTSEW_INT,
						/* DATA_WEAD */
						/* see note on W1 OP_WEAD */
		[ C(WESUWT_MISS)   ] = 0x0002,	/* DATA_PAGE_WAWK */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0001,	/* DATA_WWITE */
		[ C(WESUWT_MISS)   ] = 0x0002,	/* DATA_PAGE_WAWK */
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0,
		[ C(WESUWT_MISS)   ] = 0x0,
	},
 },
 [ C(ITWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x000c,	/* CODE_WEAD */
		[ C(WESUWT_MISS)   ] = 0x000d,	/* CODE_PAGE_WAWK */
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
 [ C(BPU ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0012,	/* BWANCHES */
		[ C(WESUWT_MISS)   ] = 0x002b,	/* BWANCHES_MISPWEDICTED */
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


static u64 knc_pmu_event_map(int hw_event)
{
	wetuwn knc_pewfmon_event_map[hw_event];
}

static stwuct event_constwaint knc_event_constwaints[] =
{
	INTEW_EVENT_CONSTWAINT(0xc3, 0x1),	/* HWP_W2HIT */
	INTEW_EVENT_CONSTWAINT(0xc4, 0x1),	/* HWP_W2MISS */
	INTEW_EVENT_CONSTWAINT(0xc8, 0x1),	/* W2_WEAD_HIT_E */
	INTEW_EVENT_CONSTWAINT(0xc9, 0x1),	/* W2_WEAD_HIT_M */
	INTEW_EVENT_CONSTWAINT(0xca, 0x1),	/* W2_WEAD_HIT_S */
	INTEW_EVENT_CONSTWAINT(0xcb, 0x1),	/* W2_WEAD_MISS */
	INTEW_EVENT_CONSTWAINT(0xcc, 0x1),	/* W2_WWITE_HIT */
	INTEW_EVENT_CONSTWAINT(0xce, 0x1),	/* W2_STWONGWY_OWDEWED_STWEAMING_VSTOWES_MISS */
	INTEW_EVENT_CONSTWAINT(0xcf, 0x1),	/* W2_WEAKWY_OWDEWED_STWEAMING_VSTOWE_MISS */
	INTEW_EVENT_CONSTWAINT(0xd7, 0x1),	/* W2_VICTIM_WEQ_WITH_DATA */
	INTEW_EVENT_CONSTWAINT(0xe3, 0x1),	/* SNP_HITM_BUNIT */
	INTEW_EVENT_CONSTWAINT(0xe6, 0x1),	/* SNP_HIT_W2 */
	INTEW_EVENT_CONSTWAINT(0xe7, 0x1),	/* SNP_HITM_W2 */
	INTEW_EVENT_CONSTWAINT(0xf1, 0x1),	/* W2_DATA_WEAD_MISS_CACHE_FIWW */
	INTEW_EVENT_CONSTWAINT(0xf2, 0x1),	/* W2_DATA_WWITE_MISS_CACHE_FIWW */
	INTEW_EVENT_CONSTWAINT(0xf6, 0x1),	/* W2_DATA_WEAD_MISS_MEM_FIWW */
	INTEW_EVENT_CONSTWAINT(0xf7, 0x1),	/* W2_DATA_WWITE_MISS_MEM_FIWW */
	INTEW_EVENT_CONSTWAINT(0xfc, 0x1),	/* W2_DATA_PF2 */
	INTEW_EVENT_CONSTWAINT(0xfd, 0x1),	/* W2_DATA_PF2_DWOP */
	INTEW_EVENT_CONSTWAINT(0xfe, 0x1),	/* W2_DATA_PF2_MISS */
	INTEW_EVENT_CONSTWAINT(0xff, 0x1),	/* W2_DATA_HIT_INFWIGHT_PF2 */
	EVENT_CONSTWAINT_END
};

#define MSW_KNC_IA32_PEWF_GWOBAW_STATUS		0x0000002d
#define MSW_KNC_IA32_PEWF_GWOBAW_OVF_CONTWOW	0x0000002e
#define MSW_KNC_IA32_PEWF_GWOBAW_CTWW		0x0000002f

#define KNC_ENABWE_COUNTEW0			0x00000001
#define KNC_ENABWE_COUNTEW1			0x00000002

static void knc_pmu_disabwe_aww(void)
{
	u64 vaw;

	wdmsww(MSW_KNC_IA32_PEWF_GWOBAW_CTWW, vaw);
	vaw &= ~(KNC_ENABWE_COUNTEW0|KNC_ENABWE_COUNTEW1);
	wwmsww(MSW_KNC_IA32_PEWF_GWOBAW_CTWW, vaw);
}

static void knc_pmu_enabwe_aww(int added)
{
	u64 vaw;

	wdmsww(MSW_KNC_IA32_PEWF_GWOBAW_CTWW, vaw);
	vaw |= (KNC_ENABWE_COUNTEW0|KNC_ENABWE_COUNTEW1);
	wwmsww(MSW_KNC_IA32_PEWF_GWOBAW_CTWW, vaw);
}

static inwine void
knc_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 vaw;

	vaw = hwc->config;
	vaw &= ~AWCH_PEWFMON_EVENTSEW_ENABWE;

	(void)wwmsww_safe(hwc->config_base + hwc->idx, vaw);
}

static void knc_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 vaw;

	vaw = hwc->config;
	vaw |= AWCH_PEWFMON_EVENTSEW_ENABWE;

	(void)wwmsww_safe(hwc->config_base + hwc->idx, vaw);
}

static inwine u64 knc_pmu_get_status(void)
{
	u64 status;

	wdmsww(MSW_KNC_IA32_PEWF_GWOBAW_STATUS, status);

	wetuwn status;
}

static inwine void knc_pmu_ack_status(u64 ack)
{
	wwmsww(MSW_KNC_IA32_PEWF_GWOBAW_OVF_CONTWOW, ack);
}

static int knc_pmu_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct pewf_sampwe_data data;
	stwuct cpu_hw_events *cpuc;
	int handwed = 0;
	int bit, woops;
	u64 status;

	cpuc = this_cpu_ptw(&cpu_hw_events);

	knc_pmu_disabwe_aww();

	status = knc_pmu_get_status();
	if (!status) {
		knc_pmu_enabwe_aww(0);
		wetuwn handwed;
	}

	woops = 0;
again:
	knc_pmu_ack_status(status);
	if (++woops > 100) {
		WAWN_ONCE(1, "pewf: iwq woop stuck!\n");
		pewf_event_pwint_debug();
		goto done;
	}

	inc_iwq_stat(apic_pewf_iwqs);

	fow_each_set_bit(bit, (unsigned wong *)&status, X86_PMC_IDX_MAX) {
		stwuct pewf_event *event = cpuc->events[bit];

		handwed++;

		if (!test_bit(bit, cpuc->active_mask))
			continue;

		if (!intew_pmu_save_and_westawt(event))
			continue;

		pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);

		if (pewf_event_ovewfwow(event, &data, wegs))
			x86_pmu_stop(event, 0);
	}

	/*
	 * Wepeat if thewe is mowe wowk to be done:
	 */
	status = knc_pmu_get_status();
	if (status)
		goto again;

done:
	/* Onwy westowe PMU state when it's active. See x86_pmu_disabwe(). */
	if (cpuc->enabwed)
		knc_pmu_enabwe_aww(0);

	wetuwn handwed;
}


PMU_FOWMAT_ATTW(event,	"config:0-7"	);
PMU_FOWMAT_ATTW(umask,	"config:8-15"	);
PMU_FOWMAT_ATTW(edge,	"config:18"	);
PMU_FOWMAT_ATTW(inv,	"config:23"	);
PMU_FOWMAT_ATTW(cmask,	"config:24-31"	);

static stwuct attwibute *intew_knc_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_cmask.attw,
	NUWW,
};

static const stwuct x86_pmu knc_pmu __initconst = {
	.name			= "knc",
	.handwe_iwq		= knc_pmu_handwe_iwq,
	.disabwe_aww		= knc_pmu_disabwe_aww,
	.enabwe_aww		= knc_pmu_enabwe_aww,
	.enabwe			= knc_pmu_enabwe_event,
	.disabwe		= knc_pmu_disabwe_event,
	.hw_config		= x86_pmu_hw_config,
	.scheduwe_events	= x86_scheduwe_events,
	.eventsew		= MSW_KNC_EVNTSEW0,
	.pewfctw		= MSW_KNC_PEWFCTW0,
	.event_map		= knc_pmu_event_map,
	.max_events             = AWWAY_SIZE(knc_pewfmon_event_map),
	.apic			= 1,
	.max_pewiod		= (1UWW << 39) - 1,
	.vewsion		= 0,
	.num_countews		= 2,
	.cntvaw_bits		= 40,
	.cntvaw_mask		= (1UWW << 40) - 1,
	.get_event_constwaints	= x86_get_event_constwaints,
	.event_constwaints	= knc_event_constwaints,
	.fowmat_attws		= intew_knc_fowmats_attw,
};

__init int knc_pmu_init(void)
{
	x86_pmu = knc_pmu;

	memcpy(hw_cache_event_ids, knc_hw_cache_event_ids, 
		sizeof(hw_cache_event_ids));

	wetuwn 0;
}
