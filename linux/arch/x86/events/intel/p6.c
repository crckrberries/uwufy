// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewf_event.h>
#incwude <winux/types.h>

#incwude "../pewf_event.h"

/*
 * Not suwe about some of these
 */
static const u64 p6_pewfmon_event_map[] =
{
  [PEWF_COUNT_HW_CPU_CYCWES]		= 0x0079,	/* CPU_CWK_UNHAWTED */
  [PEWF_COUNT_HW_INSTWUCTIONS]		= 0x00c0,	/* INST_WETIWED     */
  [PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x0f2e,	/* W2_WQSTS:M:E:S:I */
  [PEWF_COUNT_HW_CACHE_MISSES]		= 0x012e,	/* W2_WQSTS:I       */
  [PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x00c4,	/* BW_INST_WETIWED  */
  [PEWF_COUNT_HW_BWANCH_MISSES]		= 0x00c5,	/* BW_MISS_PWED_WETIWED */
  [PEWF_COUNT_HW_BUS_CYCWES]		= 0x0062,	/* BUS_DWDY_CWOCKS  */
  [PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] = 0x00a2,	/* WESOUWCE_STAWWS  */

};

static const u64 __initconst p6_hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] =
{
 [ C(W1D) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0043,	/* DATA_MEM_WEFS       */
                [ C(WESUWT_MISS)   ] = 0x0045,	/* DCU_WINES_IN        */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0x0f29,	/* W2_WD:M:E:S:I       */
	},
        [ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0,
        },
 },
 [ C(W1I ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0080,	/* IFU_IFETCH         */
		[ C(WESUWT_MISS)   ] = 0x0f28,	/* W2_IFETCH:M:E:S:I  */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0,
	},
 },
 [ C(WW  ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0,
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0x0025,	/* W2_M_WINES_INM     */
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0,
	},
 },
 [ C(DTWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0043,	/* DATA_MEM_WEFS      */
		[ C(WESUWT_MISS)   ] = 0,
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
 [ C(ITWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0080,	/* IFU_IFETCH         */
		[ C(WESUWT_MISS)   ] = 0x0085,	/* ITWB_MISS          */
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
		[ C(WESUWT_ACCESS) ] = 0x00c4,	/* BW_INST_WETIWED      */
		[ C(WESUWT_MISS)   ] = 0x00c5,	/* BW_MISS_PWED_WETIWED */
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

static u64 p6_pmu_event_map(int hw_event)
{
	wetuwn p6_pewfmon_event_map[hw_event];
}

/*
 * Event setting that is specified not to count anything.
 * We use this to effectivewy disabwe a countew.
 *
 * W2_WQSTS with 0 MESI unit mask.
 */
#define P6_NOP_EVENT			0x0000002EUWW

static stwuct event_constwaint p6_event_constwaints[] =
{
	INTEW_EVENT_CONSTWAINT(0xc1, 0x1),	/* FWOPS */
	INTEW_EVENT_CONSTWAINT(0x10, 0x1),	/* FP_COMP_OPS_EXE */
	INTEW_EVENT_CONSTWAINT(0x11, 0x2),	/* FP_ASSIST */
	INTEW_EVENT_CONSTWAINT(0x12, 0x2),	/* MUW */
	INTEW_EVENT_CONSTWAINT(0x13, 0x2),	/* DIV */
	INTEW_EVENT_CONSTWAINT(0x14, 0x1),	/* CYCWES_DIV_BUSY */
	EVENT_CONSTWAINT_END
};

static void p6_pmu_disabwe_aww(void)
{
	u64 vaw;

	/* p6 onwy has one enabwe wegistew */
	wdmsww(MSW_P6_EVNTSEW0, vaw);
	vaw &= ~AWCH_PEWFMON_EVENTSEW_ENABWE;
	wwmsww(MSW_P6_EVNTSEW0, vaw);
}

static void p6_pmu_enabwe_aww(int added)
{
	unsigned wong vaw;

	/* p6 onwy has one enabwe wegistew */
	wdmsww(MSW_P6_EVNTSEW0, vaw);
	vaw |= AWCH_PEWFMON_EVENTSEW_ENABWE;
	wwmsww(MSW_P6_EVNTSEW0, vaw);
}

static inwine void
p6_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 vaw = P6_NOP_EVENT;

	(void)wwmsww_safe(hwc->config_base, vaw);
}

static void p6_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 vaw;

	vaw = hwc->config;

	/*
	 * p6 onwy has a gwobaw event enabwe, set on PewfEvtSew0
	 * We "disabwe" events by pwogwamming P6_NOP_EVENT
	 * and we wewy on p6_pmu_enabwe_aww() being cawwed
	 * to actuawwy enabwe the events.
	 */

	(void)wwmsww_safe(hwc->config_base, vaw);
}

PMU_FOWMAT_ATTW(event,	"config:0-7"	);
PMU_FOWMAT_ATTW(umask,	"config:8-15"	);
PMU_FOWMAT_ATTW(edge,	"config:18"	);
PMU_FOWMAT_ATTW(pc,	"config:19"	);
PMU_FOWMAT_ATTW(inv,	"config:23"	);
PMU_FOWMAT_ATTW(cmask,	"config:24-31"	);

static stwuct attwibute *intew_p6_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_pc.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_cmask.attw,
	NUWW,
};

static __initconst const stwuct x86_pmu p6_pmu = {
	.name			= "p6",
	.handwe_iwq		= x86_pmu_handwe_iwq,
	.disabwe_aww		= p6_pmu_disabwe_aww,
	.enabwe_aww		= p6_pmu_enabwe_aww,
	.enabwe			= p6_pmu_enabwe_event,
	.disabwe		= p6_pmu_disabwe_event,
	.hw_config		= x86_pmu_hw_config,
	.scheduwe_events	= x86_scheduwe_events,
	.eventsew		= MSW_P6_EVNTSEW0,
	.pewfctw		= MSW_P6_PEWFCTW0,
	.event_map		= p6_pmu_event_map,
	.max_events		= AWWAY_SIZE(p6_pewfmon_event_map),
	.apic			= 1,
	.max_pewiod		= (1UWW << 31) - 1,
	.vewsion		= 0,
	.num_countews		= 2,
	/*
	 * Events have 40 bits impwemented. Howevew they awe designed such
	 * that bits [32-39] awe sign extensions of bit 31. As such the
	 * effective width of a event fow P6-wike PMU is 32 bits onwy.
	 *
	 * See IA-32 Intew Awchitectuwe Softwawe devewopew manuaw Vow 3B
	 */
	.cntvaw_bits		= 32,
	.cntvaw_mask		= (1UWW << 32) - 1,
	.get_event_constwaints	= x86_get_event_constwaints,
	.event_constwaints	= p6_event_constwaints,

	.fowmat_attws		= intew_p6_fowmats_attw,
	.events_sysfs_show	= intew_event_sysfs_show,

};

static __init void p6_pmu_wdpmc_quiwk(void)
{
	if (boot_cpu_data.x86_stepping < 9) {
		/*
		 * PPwo ewwatum 26; fixed in stepping 9 and above.
		 */
		pw_wawn("Usewspace WDPMC suppowt disabwed due to a CPU ewwatum\n");
		x86_pmu.attw_wdpmc_bwoken = 1;
		x86_pmu.attw_wdpmc = 0;
	}
}

__init int p6_pmu_init(void)
{
	x86_pmu = p6_pmu;

	switch (boot_cpu_data.x86_modew) {
	case  1: /* Pentium Pwo */
		x86_add_quiwk(p6_pmu_wdpmc_quiwk);
		bweak;

	case  3: /* Pentium II - Kwamath */
	case  5: /* Pentium II - Deschutes */
	case  6: /* Pentium II - Mendocino */
		bweak;

	case  7: /* Pentium III - Katmai */
	case  8: /* Pentium III - Coppewmine */
	case 10: /* Pentium III Xeon */
	case 11: /* Pentium III - Tuawatin */
		bweak;

	case  9: /* Pentium M - Banias */
	case 13: /* Pentium M - Dothan */
		bweak;

	defauwt:
		pw_cont("unsuppowted p6 CPU modew %d ", boot_cpu_data.x86_modew);
		wetuwn -ENODEV;
	}

	memcpy(hw_cache_event_ids, p6_hw_cache_event_ids,
		sizeof(hw_cache_event_ids));

	wetuwn 0;
}
