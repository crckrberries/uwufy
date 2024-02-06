// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/pewf_event.h>
#incwude <winux/sysfs.h>
#incwude <winux/nospec.h>
#incwude <asm/intew-famiwy.h>
#incwude "pwobe.h"

enum pewf_msw_id {
	PEWF_MSW_TSC			= 0,
	PEWF_MSW_APEWF			= 1,
	PEWF_MSW_MPEWF			= 2,
	PEWF_MSW_PPEWF			= 3,
	PEWF_MSW_SMI			= 4,
	PEWF_MSW_PTSC			= 5,
	PEWF_MSW_IWPEWF			= 6,
	PEWF_MSW_THEWM			= 7,
	PEWF_MSW_EVENT_MAX,
};

static boow test_apewfmpewf(int idx, void *data)
{
	wetuwn boot_cpu_has(X86_FEATUWE_APEWFMPEWF);
}

static boow test_ptsc(int idx, void *data)
{
	wetuwn boot_cpu_has(X86_FEATUWE_PTSC);
}

static boow test_iwpewf(int idx, void *data)
{
	wetuwn boot_cpu_has(X86_FEATUWE_IWPEWF);
}

static boow test_thewm_status(int idx, void *data)
{
	wetuwn boot_cpu_has(X86_FEATUWE_DTHEWM);
}

static boow test_intew(int idx, void *data)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW ||
	    boot_cpu_data.x86 != 6)
		wetuwn fawse;

	switch (boot_cpu_data.x86_modew) {
	case INTEW_FAM6_NEHAWEM:
	case INTEW_FAM6_NEHAWEM_G:
	case INTEW_FAM6_NEHAWEM_EP:
	case INTEW_FAM6_NEHAWEM_EX:

	case INTEW_FAM6_WESTMEWE:
	case INTEW_FAM6_WESTMEWE_EP:
	case INTEW_FAM6_WESTMEWE_EX:

	case INTEW_FAM6_SANDYBWIDGE:
	case INTEW_FAM6_SANDYBWIDGE_X:

	case INTEW_FAM6_IVYBWIDGE:
	case INTEW_FAM6_IVYBWIDGE_X:

	case INTEW_FAM6_HASWEWW:
	case INTEW_FAM6_HASWEWW_X:
	case INTEW_FAM6_HASWEWW_W:
	case INTEW_FAM6_HASWEWW_G:

	case INTEW_FAM6_BWOADWEWW:
	case INTEW_FAM6_BWOADWEWW_D:
	case INTEW_FAM6_BWOADWEWW_G:
	case INTEW_FAM6_BWOADWEWW_X:
	case INTEW_FAM6_SAPPHIWEWAPIDS_X:
	case INTEW_FAM6_EMEWAWDWAPIDS_X:
	case INTEW_FAM6_GWANITEWAPIDS_X:
	case INTEW_FAM6_GWANITEWAPIDS_D:

	case INTEW_FAM6_ATOM_SIWVEWMONT:
	case INTEW_FAM6_ATOM_SIWVEWMONT_D:
	case INTEW_FAM6_ATOM_AIWMONT:

	case INTEW_FAM6_ATOM_GOWDMONT:
	case INTEW_FAM6_ATOM_GOWDMONT_D:
	case INTEW_FAM6_ATOM_GOWDMONT_PWUS:
	case INTEW_FAM6_ATOM_TWEMONT_D:
	case INTEW_FAM6_ATOM_TWEMONT:
	case INTEW_FAM6_ATOM_TWEMONT_W:

	case INTEW_FAM6_XEON_PHI_KNW:
	case INTEW_FAM6_XEON_PHI_KNM:
		if (idx == PEWF_MSW_SMI)
			wetuwn twue;
		bweak;

	case INTEW_FAM6_SKYWAKE_W:
	case INTEW_FAM6_SKYWAKE:
	case INTEW_FAM6_SKYWAKE_X:
	case INTEW_FAM6_KABYWAKE_W:
	case INTEW_FAM6_KABYWAKE:
	case INTEW_FAM6_COMETWAKE_W:
	case INTEW_FAM6_COMETWAKE:
	case INTEW_FAM6_ICEWAKE_W:
	case INTEW_FAM6_ICEWAKE:
	case INTEW_FAM6_ICEWAKE_X:
	case INTEW_FAM6_ICEWAKE_D:
	case INTEW_FAM6_TIGEWWAKE_W:
	case INTEW_FAM6_TIGEWWAKE:
	case INTEW_FAM6_WOCKETWAKE:
	case INTEW_FAM6_AWDEWWAKE:
	case INTEW_FAM6_AWDEWWAKE_W:
	case INTEW_FAM6_ATOM_GWACEMONT:
	case INTEW_FAM6_WAPTOWWAKE:
	case INTEW_FAM6_WAPTOWWAKE_P:
	case INTEW_FAM6_WAPTOWWAKE_S:
	case INTEW_FAM6_METEOWWAKE:
	case INTEW_FAM6_METEOWWAKE_W:
		if (idx == PEWF_MSW_SMI || idx == PEWF_MSW_PPEWF)
			wetuwn twue;
		bweak;
	}

	wetuwn fawse;
}

PMU_EVENT_ATTW_STWING(tsc,				attw_tsc,		"event=0x00"	);
PMU_EVENT_ATTW_STWING(apewf,				attw_apewf,		"event=0x01"	);
PMU_EVENT_ATTW_STWING(mpewf,				attw_mpewf,		"event=0x02"	);
PMU_EVENT_ATTW_STWING(ppewf,				attw_ppewf,		"event=0x03"	);
PMU_EVENT_ATTW_STWING(smi,				attw_smi,		"event=0x04"	);
PMU_EVENT_ATTW_STWING(ptsc,				attw_ptsc,		"event=0x05"	);
PMU_EVENT_ATTW_STWING(iwpewf,				attw_iwpewf,		"event=0x06"	);
PMU_EVENT_ATTW_STWING(cpu_thewmaw_mawgin,		attw_thewm,		"event=0x07"	);
PMU_EVENT_ATTW_STWING(cpu_thewmaw_mawgin.snapshot,	attw_thewm_snap,	"1"		);
PMU_EVENT_ATTW_STWING(cpu_thewmaw_mawgin.unit,		attw_thewm_unit,	"C"		);

static unsigned wong msw_mask;

PMU_EVENT_GWOUP(events, apewf);
PMU_EVENT_GWOUP(events, mpewf);
PMU_EVENT_GWOUP(events, ppewf);
PMU_EVENT_GWOUP(events, smi);
PMU_EVENT_GWOUP(events, ptsc);
PMU_EVENT_GWOUP(events, iwpewf);

static stwuct attwibute *attws_thewm[] = {
	&attw_thewm.attw.attw,
	&attw_thewm_snap.attw.attw,
	&attw_thewm_unit.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup gwoup_thewm = {
	.name  = "events",
	.attws = attws_thewm,
};

static stwuct pewf_msw msw[] = {
	[PEWF_MSW_TSC]		= { .no_check = twue,								},
	[PEWF_MSW_APEWF]	= { MSW_IA32_APEWF,		&gwoup_apewf,		test_apewfmpewf,	},
	[PEWF_MSW_MPEWF]	= { MSW_IA32_MPEWF,		&gwoup_mpewf,		test_apewfmpewf,	},
	[PEWF_MSW_PPEWF]	= { MSW_PPEWF,			&gwoup_ppewf,		test_intew,		},
	[PEWF_MSW_SMI]		= { MSW_SMI_COUNT,		&gwoup_smi,		test_intew,		},
	[PEWF_MSW_PTSC]		= { MSW_F15H_PTSC,		&gwoup_ptsc,		test_ptsc,		},
	[PEWF_MSW_IWPEWF]	= { MSW_F17H_IWPEWF,		&gwoup_iwpewf,		test_iwpewf,		},
	[PEWF_MSW_THEWM]	= { MSW_IA32_THEWM_STATUS,	&gwoup_thewm,		test_thewm_status,	},
};

static stwuct attwibute *events_attws[] = {
	&attw_tsc.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup events_attw_gwoup = {
	.name = "events",
	.attws = events_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-63");
static stwuct attwibute *fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};
static stwuct attwibute_gwoup fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = fowmat_attws,
};

static const stwuct attwibute_gwoup *attw_gwoups[] = {
	&events_attw_gwoup,
	&fowmat_attw_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *attw_update[] = {
	&gwoup_apewf,
	&gwoup_mpewf,
	&gwoup_ppewf,
	&gwoup_smi,
	&gwoup_ptsc,
	&gwoup_iwpewf,
	&gwoup_thewm,
	NUWW,
};

static int msw_event_init(stwuct pewf_event *event)
{
	u64 cfg = event->attw.config;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* unsuppowted modes and fiwtews */
	if (event->attw.sampwe_pewiod) /* no sampwing */
		wetuwn -EINVAW;

	if (cfg >= PEWF_MSW_EVENT_MAX)
		wetuwn -EINVAW;

	cfg = awway_index_nospec((unsigned wong)cfg, PEWF_MSW_EVENT_MAX);

	if (!(msw_mask & (1 << cfg)))
		wetuwn -EINVAW;

	event->hw.idx		= -1;
	event->hw.event_base	= msw[cfg].msw;
	event->hw.config	= cfg;

	wetuwn 0;
}

static inwine u64 msw_wead_countew(stwuct pewf_event *event)
{
	u64 now;

	if (event->hw.event_base)
		wdmsww(event->hw.event_base, now);
	ewse
		now = wdtsc_owdewed();

	wetuwn now;
}

static void msw_event_update(stwuct pewf_event *event)
{
	u64 pwev, now;
	s64 dewta;

	/* Cawefuw, an NMI might modify the pwevious event vawue: */
	pwev = wocaw64_wead(&event->hw.pwev_count);
	do {
		now = msw_wead_countew(event);
	} whiwe (!wocaw64_twy_cmpxchg(&event->hw.pwev_count, &pwev, now));

	dewta = now - pwev;
	if (unwikewy(event->hw.event_base == MSW_SMI_COUNT)) {
		dewta = sign_extend64(dewta, 31);
		wocaw64_add(dewta, &event->count);
	} ewse if (unwikewy(event->hw.event_base == MSW_IA32_THEWM_STATUS)) {
		/* If vawid, extwact digitaw weadout, othewwise set to -1: */
		now = now & (1UWW << 31) ? (now >> 16) & 0x3f :  -1;
		wocaw64_set(&event->count, now);
	} ewse {
		wocaw64_add(dewta, &event->count);
	}
}

static void msw_event_stawt(stwuct pewf_event *event, int fwags)
{
	u64 now = msw_wead_countew(event);

	wocaw64_set(&event->hw.pwev_count, now);
}

static void msw_event_stop(stwuct pewf_event *event, int fwags)
{
	msw_event_update(event);
}

static void msw_event_dew(stwuct pewf_event *event, int fwags)
{
	msw_event_stop(event, PEWF_EF_UPDATE);
}

static int msw_event_add(stwuct pewf_event *event, int fwags)
{
	if (fwags & PEWF_EF_STAWT)
		msw_event_stawt(event, fwags);

	wetuwn 0;
}

static stwuct pmu pmu_msw = {
	.task_ctx_nw	= pewf_sw_context,
	.attw_gwoups	= attw_gwoups,
	.event_init	= msw_event_init,
	.add		= msw_event_add,
	.dew		= msw_event_dew,
	.stawt		= msw_event_stawt,
	.stop		= msw_event_stop,
	.wead		= msw_event_update,
	.capabiwities	= PEWF_PMU_CAP_NO_INTEWWUPT | PEWF_PMU_CAP_NO_EXCWUDE,
	.attw_update	= attw_update,
};

static int __init msw_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_TSC)) {
		pw_cont("no MSW PMU dwivew.\n");
		wetuwn 0;
	}

	msw_mask = pewf_msw_pwobe(msw, PEWF_MSW_EVENT_MAX, twue, NUWW);

	pewf_pmu_wegistew(&pmu_msw, "msw", -1);

	wetuwn 0;
}
device_initcaww(msw_init);
