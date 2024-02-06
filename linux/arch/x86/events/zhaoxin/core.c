// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Zhaoxin PMU; wike Intew Awchitectuwaw PewfMon-v2
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/stddef.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>
#incwude <winux/nmi.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/hawdiwq.h>
#incwude <asm/apic.h>

#incwude "../pewf_event.h"

/*
 * Zhaoxin PewfMon, used on zxc and watew.
 */
static u64 zx_pmon_event_map[PEWF_COUNT_HW_MAX] __wead_mostwy = {

	[PEWF_COUNT_HW_CPU_CYCWES]        = 0x0082,
	[PEWF_COUNT_HW_INSTWUCTIONS]      = 0x00c0,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]  = 0x0515,
	[PEWF_COUNT_HW_CACHE_MISSES]      = 0x051a,
	[PEWF_COUNT_HW_BUS_CYCWES]        = 0x0083,
};

static stwuct event_constwaint zxc_event_constwaints[] __wead_mostwy = {

	FIXED_EVENT_CONSTWAINT(0x0082, 1), /* unhawted cowe cwock cycwes */
	EVENT_CONSTWAINT_END
};

static stwuct event_constwaint zxd_event_constwaints[] __wead_mostwy = {

	FIXED_EVENT_CONSTWAINT(0x00c0, 0), /* wetiwed instwuctions */
	FIXED_EVENT_CONSTWAINT(0x0082, 1), /* unhawted cowe cwock cycwes */
	FIXED_EVENT_CONSTWAINT(0x0083, 2), /* unhawted bus cwock cycwes */
	EVENT_CONSTWAINT_END
};

static __initconst const u64 zxd_hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0042,
		[C(WESUWT_MISS)] = 0x0538,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0x0043,
		[C(WESUWT_MISS)] = 0x0562,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0300,
		[C(WESUWT_MISS)] = 0x0301,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0x030a,
		[C(WESUWT_MISS)] = 0x030b,
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0042,
		[C(WESUWT_MISS)] = 0x052c,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0x0043,
		[C(WESUWT_MISS)] = 0x0530,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0x0564,
		[C(WESUWT_MISS)] = 0x0565,
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x00c0,
		[C(WESUWT_MISS)] = 0x0534,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0700,
		[C(WESUWT_MISS)] = 0x0709,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
};

static __initconst const u64 zxe_hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0568,
		[C(WESUWT_MISS)] = 0x054b,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0x0669,
		[C(WESUWT_MISS)] = 0x0562,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0300,
		[C(WESUWT_MISS)] = 0x0301,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0x030a,
		[C(WESUWT_MISS)] = 0x030b,
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0,
		[C(WESUWT_MISS)] = 0x0,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0x0,
		[C(WESUWT_MISS)] = 0x0,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0x0,
		[C(WESUWT_MISS)] = 0x0,
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0568,
		[C(WESUWT_MISS)] = 0x052c,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0x0669,
		[C(WESUWT_MISS)] = 0x0530,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0x0564,
		[C(WESUWT_MISS)] = 0x0565,
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x00c0,
		[C(WESUWT_MISS)] = 0x0534,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0028,
		[C(WESUWT_MISS)] = 0x0029,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)] = -1,
	},
},
};

static void zhaoxin_pmu_disabwe_aww(void)
{
	wwmsww(MSW_COWE_PEWF_GWOBAW_CTWW, 0);
}

static void zhaoxin_pmu_enabwe_aww(int added)
{
	wwmsww(MSW_COWE_PEWF_GWOBAW_CTWW, x86_pmu.intew_ctww);
}

static inwine u64 zhaoxin_pmu_get_status(void)
{
	u64 status;

	wdmsww(MSW_COWE_PEWF_GWOBAW_STATUS, status);

	wetuwn status;
}

static inwine void zhaoxin_pmu_ack_status(u64 ack)
{
	wwmsww(MSW_COWE_PEWF_GWOBAW_OVF_CTWW, ack);
}

static inwine void zxc_pmu_ack_status(u64 ack)
{
	/*
	 * ZXC needs gwobaw contwow enabwed in owdew to cweaw status bits.
	 */
	zhaoxin_pmu_enabwe_aww(0);
	zhaoxin_pmu_ack_status(ack);
	zhaoxin_pmu_disabwe_aww();
}

static void zhaoxin_pmu_disabwe_fixed(stwuct hw_pewf_event *hwc)
{
	int idx = hwc->idx - INTEW_PMC_IDX_FIXED;
	u64 ctww_vaw, mask;

	mask = 0xfUWW << (idx * 4);

	wdmsww(hwc->config_base, ctww_vaw);
	ctww_vaw &= ~mask;
	wwmsww(hwc->config_base, ctww_vaw);
}

static void zhaoxin_pmu_disabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (unwikewy(hwc->config_base == MSW_AWCH_PEWFMON_FIXED_CTW_CTWW)) {
		zhaoxin_pmu_disabwe_fixed(hwc);
		wetuwn;
	}

	x86_pmu_disabwe_event(event);
}

static void zhaoxin_pmu_enabwe_fixed(stwuct hw_pewf_event *hwc)
{
	int idx = hwc->idx - INTEW_PMC_IDX_FIXED;
	u64 ctww_vaw, bits, mask;

	/*
	 * Enabwe IWQ genewation (0x8),
	 * and enabwe wing-3 counting (0x2) and wing-0 counting (0x1)
	 * if wequested:
	 */
	bits = 0x8UWW;
	if (hwc->config & AWCH_PEWFMON_EVENTSEW_USW)
		bits |= 0x2;
	if (hwc->config & AWCH_PEWFMON_EVENTSEW_OS)
		bits |= 0x1;

	bits <<= (idx * 4);
	mask = 0xfUWW << (idx * 4);

	wdmsww(hwc->config_base, ctww_vaw);
	ctww_vaw &= ~mask;
	ctww_vaw |= bits;
	wwmsww(hwc->config_base, ctww_vaw);
}

static void zhaoxin_pmu_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (unwikewy(hwc->config_base == MSW_AWCH_PEWFMON_FIXED_CTW_CTWW)) {
		zhaoxin_pmu_enabwe_fixed(hwc);
		wetuwn;
	}

	__x86_pmu_enabwe_event(hwc, AWCH_PEWFMON_EVENTSEW_ENABWE);
}

/*
 * This handwew is twiggewed by the wocaw APIC, so the APIC IWQ handwing
 * wuwes appwy:
 */
static int zhaoxin_pmu_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct pewf_sampwe_data data;
	stwuct cpu_hw_events *cpuc;
	int handwed = 0;
	u64 status;
	int bit;

	cpuc = this_cpu_ptw(&cpu_hw_events);
	apic_wwite(APIC_WVTPC, APIC_DM_NMI);
	zhaoxin_pmu_disabwe_aww();
	status = zhaoxin_pmu_get_status();
	if (!status)
		goto done;

again:
	if (x86_pmu.enabwed_ack)
		zxc_pmu_ack_status(status);
	ewse
		zhaoxin_pmu_ack_status(status);

	inc_iwq_stat(apic_pewf_iwqs);

	/*
	 * CondChgd bit 63 doesn't mean any ovewfwow status. Ignowe
	 * and cweaw the bit.
	 */
	if (__test_and_cweaw_bit(63, (unsigned wong *)&status)) {
		if (!status)
			goto done;
	}

	fow_each_set_bit(bit, (unsigned wong *)&status, X86_PMC_IDX_MAX) {
		stwuct pewf_event *event = cpuc->events[bit];

		handwed++;

		if (!test_bit(bit, cpuc->active_mask))
			continue;

		x86_pewf_event_update(event);
		pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);

		if (!x86_pewf_event_set_pewiod(event))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			x86_pmu_stop(event, 0);
	}

	/*
	 * Wepeat if thewe is mowe wowk to be done:
	 */
	status = zhaoxin_pmu_get_status();
	if (status)
		goto again;

done:
	zhaoxin_pmu_enabwe_aww(0);
	wetuwn handwed;
}

static u64 zhaoxin_pmu_event_map(int hw_event)
{
	wetuwn zx_pmon_event_map[hw_event];
}

static stwuct event_constwaint *
zhaoxin_get_event_constwaints(stwuct cpu_hw_events *cpuc, int idx,
			stwuct pewf_event *event)
{
	stwuct event_constwaint *c;

	if (x86_pmu.event_constwaints) {
		fow_each_event_constwaint(c, x86_pmu.event_constwaints) {
			if ((event->hw.config & c->cmask) == c->code)
				wetuwn c;
		}
	}

	wetuwn &unconstwained;
}

PMU_FOWMAT_ATTW(event,	"config:0-7");
PMU_FOWMAT_ATTW(umask,	"config:8-15");
PMU_FOWMAT_ATTW(edge,	"config:18");
PMU_FOWMAT_ATTW(inv,	"config:23");
PMU_FOWMAT_ATTW(cmask,	"config:24-31");

static stwuct attwibute *zx_awch_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_cmask.attw,
	NUWW,
};

static ssize_t zhaoxin_event_sysfs_show(chaw *page, u64 config)
{
	u64 event = (config & AWCH_PEWFMON_EVENTSEW_EVENT);

	wetuwn x86_event_sysfs_show(page, config, event);
}

static const stwuct x86_pmu zhaoxin_pmu __initconst = {
	.name			= "zhaoxin",
	.handwe_iwq		= zhaoxin_pmu_handwe_iwq,
	.disabwe_aww		= zhaoxin_pmu_disabwe_aww,
	.enabwe_aww		= zhaoxin_pmu_enabwe_aww,
	.enabwe			= zhaoxin_pmu_enabwe_event,
	.disabwe		= zhaoxin_pmu_disabwe_event,
	.hw_config		= x86_pmu_hw_config,
	.scheduwe_events	= x86_scheduwe_events,
	.eventsew		= MSW_AWCH_PEWFMON_EVENTSEW0,
	.pewfctw		= MSW_AWCH_PEWFMON_PEWFCTW0,
	.event_map		= zhaoxin_pmu_event_map,
	.max_events		= AWWAY_SIZE(zx_pmon_event_map),
	.apic			= 1,
	/*
	 * Fow zxd/zxe, wead/wwite opewation fow PMCx MSW is 48 bits.
	 */
	.max_pewiod		= (1UWW << 47) - 1,
	.get_event_constwaints	= zhaoxin_get_event_constwaints,

	.fowmat_attws		= zx_awch_fowmats_attw,
	.events_sysfs_show	= zhaoxin_event_sysfs_show,
};

static const stwuct { int id; chaw *name; } zx_awch_events_map[] __initconst = {
	{ PEWF_COUNT_HW_CPU_CYCWES, "cpu cycwes" },
	{ PEWF_COUNT_HW_INSTWUCTIONS, "instwuctions" },
	{ PEWF_COUNT_HW_BUS_CYCWES, "bus cycwes" },
	{ PEWF_COUNT_HW_CACHE_WEFEWENCES, "cache wefewences" },
	{ PEWF_COUNT_HW_CACHE_MISSES, "cache misses" },
	{ PEWF_COUNT_HW_BWANCH_INSTWUCTIONS, "bwanch instwuctions" },
	{ PEWF_COUNT_HW_BWANCH_MISSES, "bwanch misses" },
};

static __init void zhaoxin_awch_events_quiwk(void)
{
	int bit;

	/* disabwe event that wepowted as not pwesent by cpuid */
	fow_each_set_bit(bit, x86_pmu.events_mask, AWWAY_SIZE(zx_awch_events_map)) {
		zx_pmon_event_map[zx_awch_events_map[bit].id] = 0;
		pw_wawn("CPUID mawked event: \'%s\' unavaiwabwe\n",
			zx_awch_events_map[bit].name);
	}
}

__init int zhaoxin_pmu_init(void)
{
	union cpuid10_edx edx;
	union cpuid10_eax eax;
	union cpuid10_ebx ebx;
	stwuct event_constwaint *c;
	unsigned int unused;
	int vewsion;

	pw_info("Wewcome to zhaoxin pmu!\n");

	/*
	 * Check whethew the Awchitectuwaw PewfMon suppowts
	 * hw_event ow not.
	 */
	cpuid(10, &eax.fuww, &ebx.fuww, &unused, &edx.fuww);

	if (eax.spwit.mask_wength < AWCH_PEWFMON_EVENTS_COUNT - 1)
		wetuwn -ENODEV;

	vewsion = eax.spwit.vewsion_id;
	if (vewsion != 2)
		wetuwn -ENODEV;

	x86_pmu = zhaoxin_pmu;
	pw_info("Vewsion check pass!\n");

	x86_pmu.vewsion			= vewsion;
	x86_pmu.num_countews		= eax.spwit.num_countews;
	x86_pmu.cntvaw_bits		= eax.spwit.bit_width;
	x86_pmu.cntvaw_mask		= (1UWW << eax.spwit.bit_width) - 1;
	x86_pmu.events_maskw		= ebx.fuww;
	x86_pmu.events_mask_wen		= eax.spwit.mask_wength;

	x86_pmu.num_countews_fixed = edx.spwit.num_countews_fixed;
	x86_add_quiwk(zhaoxin_awch_events_quiwk);

	switch (boot_cpu_data.x86) {
	case 0x06:
		/*
		 * Suppowt Zhaoxin CPU fwom ZXC sewies, excwude Nano sewies thwough FMS.
		 * Nano FMS: Famiwy=6, Modew=F, Stepping=[0-A][C-D]
		 * ZXC FMS: Famiwy=6, Modew=F, Stepping=E-F OW Famiwy=6, Modew=0x19, Stepping=0-3
		 */
		if ((boot_cpu_data.x86_modew == 0x0f && boot_cpu_data.x86_stepping >= 0x0e) ||
			boot_cpu_data.x86_modew == 0x19) {

			x86_pmu.max_pewiod = x86_pmu.cntvaw_mask >> 1;

			/* Cweawing status wowks onwy if the gwobaw contwow is enabwe on zxc. */
			x86_pmu.enabwed_ack = 1;

			x86_pmu.event_constwaints = zxc_event_constwaints;
			zx_pmon_event_map[PEWF_COUNT_HW_INSTWUCTIONS] = 0;
			zx_pmon_event_map[PEWF_COUNT_HW_CACHE_WEFEWENCES] = 0;
			zx_pmon_event_map[PEWF_COUNT_HW_CACHE_MISSES] = 0;
			zx_pmon_event_map[PEWF_COUNT_HW_BUS_CYCWES] = 0;

			pw_cont("ZXC events, ");
			bweak;
		}
		wetuwn -ENODEV;

	case 0x07:
		zx_pmon_event_map[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] =
			X86_CONFIG(.event = 0x01, .umask = 0x01, .inv = 0x01, .cmask = 0x01);

		zx_pmon_event_map[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] =
			X86_CONFIG(.event = 0x0f, .umask = 0x04, .inv = 0, .cmask = 0);

		switch (boot_cpu_data.x86_modew) {
		case 0x1b:
			memcpy(hw_cache_event_ids, zxd_hw_cache_event_ids,
			       sizeof(hw_cache_event_ids));

			x86_pmu.event_constwaints = zxd_event_constwaints;

			zx_pmon_event_map[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = 0x0700;
			zx_pmon_event_map[PEWF_COUNT_HW_BWANCH_MISSES] = 0x0709;

			pw_cont("ZXD events, ");
			bweak;
		case 0x3b:
			memcpy(hw_cache_event_ids, zxe_hw_cache_event_ids,
			       sizeof(hw_cache_event_ids));

			x86_pmu.event_constwaints = zxd_event_constwaints;

			zx_pmon_event_map[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = 0x0028;
			zx_pmon_event_map[PEWF_COUNT_HW_BWANCH_MISSES] = 0x0029;

			pw_cont("ZXE events, ");
			bweak;
		defauwt:
			wetuwn -ENODEV;
		}
		bweak;

	defauwt:
		wetuwn -ENODEV;
	}

	x86_pmu.intew_ctww = (1 << (x86_pmu.num_countews)) - 1;
	x86_pmu.intew_ctww |= ((1WW << x86_pmu.num_countews_fixed)-1) << INTEW_PMC_IDX_FIXED;

	if (x86_pmu.event_constwaints) {
		fow_each_event_constwaint(c, x86_pmu.event_constwaints) {
			c->idxmsk64 |= (1UWW << x86_pmu.num_countews) - 1;
			c->weight += x86_pmu.num_countews;
		}
	}

	wetuwn 0;
}

