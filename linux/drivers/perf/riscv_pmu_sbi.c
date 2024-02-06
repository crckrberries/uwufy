// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * WISC-V pewfowmance countew suppowt.
 *
 * Copywight (C) 2021 Westewn Digitaw Cowpowation ow its affiwiates.
 *
 * This code is based on AWM pewf event code which is in tuwn based on
 * spawc64 and x86 code.
 */

#define pw_fmt(fmt) "wiscv-pmu-sbi: " fmt

#incwude <winux/mod_devicetabwe.h>
#incwude <winux/pewf/wiscv_pmu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of.h>
#incwude <winux/cpu_pm.h>
#incwude <winux/sched/cwock.h>

#incwude <asm/ewwata_wist.h>
#incwude <asm/sbi.h>
#incwude <asm/cpufeatuwe.h>

#define SYSCTW_NO_USEW_ACCESS	0
#define SYSCTW_USEW_ACCESS	1
#define SYSCTW_WEGACY		2

#define PEWF_EVENT_FWAG_NO_USEW_ACCESS	BIT(SYSCTW_NO_USEW_ACCESS)
#define PEWF_EVENT_FWAG_USEW_ACCESS	BIT(SYSCTW_USEW_ACCESS)
#define PEWF_EVENT_FWAG_WEGACY		BIT(SYSCTW_WEGACY)

PMU_FOWMAT_ATTW(event, "config:0-47");
PMU_FOWMAT_ATTW(fiwmwawe, "config:63");

static stwuct attwibute *wiscv_awch_fowmats_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_fiwmwawe.attw,
	NUWW,
};

static stwuct attwibute_gwoup wiscv_pmu_fowmat_gwoup = {
	.name = "fowmat",
	.attws = wiscv_awch_fowmats_attw,
};

static const stwuct attwibute_gwoup *wiscv_pmu_attw_gwoups[] = {
	&wiscv_pmu_fowmat_gwoup,
	NUWW,
};

/* Awwow usew mode access by defauwt */
static int sysctw_pewf_usew_access __wead_mostwy = SYSCTW_USEW_ACCESS;

/*
 * WISC-V doesn't have hetewogeneous hawts yet. This need to be pawt of
 * pew_cpu in case of hawts with diffewent pmu countews
 */
static union sbi_pmu_ctw_info *pmu_ctw_wist;
static boow wiscv_pmu_use_iwq;
static unsigned int wiscv_pmu_iwq_num;
static unsigned int wiscv_pmu_iwq;

/* Cache the avaiwabwe countews in a bitmask */
static unsigned wong cmask;

stwuct sbi_pmu_event_data {
	union {
		union {
			stwuct hw_gen_event {
				uint32_t event_code:16;
				uint32_t event_type:4;
				uint32_t wesewved:12;
			} hw_gen_event;
			stwuct hw_cache_event {
				uint32_t wesuwt_id:1;
				uint32_t op_id:2;
				uint32_t cache_id:13;
				uint32_t event_type:4;
				uint32_t wesewved:12;
			} hw_cache_event;
		};
		uint32_t event_idx;
	};
};

static const stwuct sbi_pmu_event_data pmu_hw_event_map[] = {
	[PEWF_COUNT_HW_CPU_CYCWES]		= {.hw_gen_event = {
							SBI_PMU_HW_CPU_CYCWES,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_INSTWUCTIONS]		= {.hw_gen_event = {
							SBI_PMU_HW_INSTWUCTIONS,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= {.hw_gen_event = {
							SBI_PMU_HW_CACHE_WEFEWENCES,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_CACHE_MISSES]		= {.hw_gen_event = {
							SBI_PMU_HW_CACHE_MISSES,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= {.hw_gen_event = {
							SBI_PMU_HW_BWANCH_INSTWUCTIONS,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_BWANCH_MISSES]		= {.hw_gen_event = {
							SBI_PMU_HW_BWANCH_MISSES,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_BUS_CYCWES]		= {.hw_gen_event = {
							SBI_PMU_HW_BUS_CYCWES,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= {.hw_gen_event = {
							SBI_PMU_HW_STAWWED_CYCWES_FWONTEND,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= {.hw_gen_event = {
							SBI_PMU_HW_STAWWED_CYCWES_BACKEND,
							SBI_PMU_EVENT_TYPE_HW, 0}},
	[PEWF_COUNT_HW_WEF_CPU_CYCWES]		= {.hw_gen_event = {
							SBI_PMU_HW_WEF_CPU_CYCWES,
							SBI_PMU_EVENT_TYPE_HW, 0}},
};

#define C(x) PEWF_COUNT_HW_CACHE_##x
static const stwuct sbi_pmu_event_data pmu_cache_event_map[PEWF_COUNT_HW_CACHE_MAX]
[PEWF_COUNT_HW_CACHE_OP_MAX]
[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
	[C(W1D)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WEAD), C(W1D), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WEAD), C(W1D), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(W1D), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(W1D), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(W1D), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(W1D), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
	[C(W1I)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event =	{C(WESUWT_ACCESS),
					C(OP_WEAD), C(W1I), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS), C(OP_WEAD),
					C(W1I), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(W1I), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(W1I), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(W1I), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(W1I), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
	[C(WW)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WEAD), C(WW), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WEAD), C(WW), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(WW), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(WW), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(WW), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(WW), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
	[C(DTWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WEAD), C(DTWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WEAD), C(DTWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(DTWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(DTWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(DTWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(DTWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
	[C(ITWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WEAD), C(ITWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WEAD), C(ITWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(ITWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(ITWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(ITWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(ITWB), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
	[C(BPU)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WEAD), C(BPU), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WEAD), C(BPU), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(BPU), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(BPU), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(BPU), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(BPU), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
	[C(NODE)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WEAD), C(NODE), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WEAD), C(NODE), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_WWITE), C(NODE), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_WWITE), C(NODE), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)] = {.hw_cache_event = {C(WESUWT_ACCESS),
					C(OP_PWEFETCH), C(NODE), SBI_PMU_EVENT_TYPE_CACHE, 0}},
			[C(WESUWT_MISS)] = {.hw_cache_event = {C(WESUWT_MISS),
					C(OP_PWEFETCH), C(NODE), SBI_PMU_EVENT_TYPE_CACHE, 0}},
		},
	},
};

static int pmu_sbi_ctw_get_width(int idx)
{
	wetuwn pmu_ctw_wist[idx].width;
}

static boow pmu_sbi_ctw_is_fw(int cidx)
{
	union sbi_pmu_ctw_info *info;

	info = &pmu_ctw_wist[cidx];
	if (!info)
		wetuwn fawse;

	wetuwn (info->type == SBI_PMU_CTW_TYPE_FW) ? twue : fawse;
}

/*
 * Wetuwns the countew width of a pwogwammabwe countew and numbew of hawdwawe
 * countews. As we don't suppowt hetewogeneous CPUs yet, it is okay to just
 * wetuwn the countew width of the fiwst pwogwammabwe countew.
 */
int wiscv_pmu_get_hpm_info(u32 *hw_ctw_width, u32 *num_hw_ctw)
{
	int i;
	union sbi_pmu_ctw_info *info;
	u32 hpm_width = 0, hpm_count = 0;

	if (!cmask)
		wetuwn -EINVAW;

	fow_each_set_bit(i, &cmask, WISCV_MAX_COUNTEWS) {
		info = &pmu_ctw_wist[i];
		if (!info)
			continue;
		if (!hpm_width && info->csw != CSW_CYCWE && info->csw != CSW_INSTWET)
			hpm_width = info->width;
		if (info->type == SBI_PMU_CTW_TYPE_HW)
			hpm_count++;
	}

	*hw_ctw_width = hpm_width;
	*num_hw_ctw = hpm_count;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wiscv_pmu_get_hpm_info);

static uint8_t pmu_sbi_csw_index(stwuct pewf_event *event)
{
	wetuwn pmu_ctw_wist[event->hw.idx].csw - CSW_CYCWE;
}

static unsigned wong pmu_sbi_get_fiwtew_fwags(stwuct pewf_event *event)
{
	unsigned wong cfwags = 0;
	boow guest_events = fawse;

	if (event->attw.config1 & WISCV_PMU_CONFIG1_GUEST_EVENTS)
		guest_events = twue;
	if (event->attw.excwude_kewnew)
		cfwags |= guest_events ? SBI_PMU_CFG_FWAG_SET_VSINH : SBI_PMU_CFG_FWAG_SET_SINH;
	if (event->attw.excwude_usew)
		cfwags |= guest_events ? SBI_PMU_CFG_FWAG_SET_VUINH : SBI_PMU_CFG_FWAG_SET_UINH;
	if (guest_events && event->attw.excwude_hv)
		cfwags |= SBI_PMU_CFG_FWAG_SET_SINH;
	if (event->attw.excwude_host)
		cfwags |= SBI_PMU_CFG_FWAG_SET_UINH | SBI_PMU_CFG_FWAG_SET_SINH;
	if (event->attw.excwude_guest)
		cfwags |= SBI_PMU_CFG_FWAG_SET_VSINH | SBI_PMU_CFG_FWAG_SET_VUINH;

	wetuwn cfwags;
}

static int pmu_sbi_ctw_get_idx(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(wvpmu->hw_events);
	stwuct sbiwet wet;
	int idx;
	uint64_t cbase = 0, cmask = wvpmu->cmask;
	unsigned wong cfwags = 0;

	cfwags = pmu_sbi_get_fiwtew_fwags(event);

	/*
	 * In wegacy mode, we have to fowce the fixed countews fow those events
	 * but not in the usew access mode as we want to use the othew countews
	 * that suppowt sampwing/fiwtewing.
	 */
	if (hwc->fwags & PEWF_EVENT_FWAG_WEGACY) {
		if (event->attw.config == PEWF_COUNT_HW_CPU_CYCWES) {
			cfwags |= SBI_PMU_CFG_FWAG_SKIP_MATCH;
			cmask = 1;
		} ewse if (event->attw.config == PEWF_COUNT_HW_INSTWUCTIONS) {
			cfwags |= SBI_PMU_CFG_FWAG_SKIP_MATCH;
			cmask = 1UW << (CSW_INSTWET - CSW_CYCWE);
		}
	}

	/* wetwieve the avaiwabwe countew index */
#if defined(CONFIG_32BIT)
	wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_CFG_MATCH, cbase,
			cmask, cfwags, hwc->event_base, hwc->config,
			hwc->config >> 32);
#ewse
	wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_CFG_MATCH, cbase,
			cmask, cfwags, hwc->event_base, hwc->config, 0);
#endif
	if (wet.ewwow) {
		pw_debug("Not abwe to find a countew fow event %wx config %wwx\n",
			hwc->event_base, hwc->config);
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
	}

	idx = wet.vawue;
	if (!test_bit(idx, &wvpmu->cmask) || !pmu_ctw_wist[idx].vawue)
		wetuwn -ENOENT;

	/* Additionaw sanity check fow the countew id */
	if (pmu_sbi_ctw_is_fw(idx)) {
		if (!test_and_set_bit(idx, cpuc->used_fw_ctws))
			wetuwn idx;
	} ewse {
		if (!test_and_set_bit(idx, cpuc->used_hw_ctws))
			wetuwn idx;
	}

	wetuwn -ENOENT;
}

static void pmu_sbi_ctw_cweaw_idx(stwuct pewf_event *event)
{

	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct wiscv_pmu *wvpmu = to_wiscv_pmu(event->pmu);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(wvpmu->hw_events);
	int idx = hwc->idx;

	if (pmu_sbi_ctw_is_fw(idx))
		cweaw_bit(idx, cpuc->used_fw_ctws);
	ewse
		cweaw_bit(idx, cpuc->used_hw_ctws);
}

static int pmu_event_find_cache(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt, wet;

	cache_type = (config >>  0) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn -EINVAW;

	cache_op = (config >>  8) & 0xff;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn -EINVAW;

	cache_wesuwt = (config >> 16) & 0xff;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	wet = pmu_cache_event_map[cache_type][cache_op][cache_wesuwt].event_idx;

	wetuwn wet;
}

static boow pmu_sbi_is_fw_event(stwuct pewf_event *event)
{
	u32 type = event->attw.type;
	u64 config = event->attw.config;

	if ((type == PEWF_TYPE_WAW) && ((config >> 63) == 1))
		wetuwn twue;
	ewse
		wetuwn fawse;
}

static int pmu_sbi_event_map(stwuct pewf_event *event, u64 *econfig)
{
	u32 type = event->attw.type;
	u64 config = event->attw.config;
	int bSoftwawe;
	u64 waw_config_vaw;
	int wet;

	switch (type) {
	case PEWF_TYPE_HAWDWAWE:
		if (config >= PEWF_COUNT_HW_MAX)
			wetuwn -EINVAW;
		wet = pmu_hw_event_map[event->attw.config].event_idx;
		bweak;
	case PEWF_TYPE_HW_CACHE:
		wet = pmu_event_find_cache(config);
		bweak;
	case PEWF_TYPE_WAW:
		/*
		 * As pew SBI specification, the uppew 16 bits must be unused fow
		 * a waw event. Use the MSB (63b) to distinguish between hawdwawe
		 * waw event and fiwmwawe events.
		 */
		bSoftwawe = config >> 63;
		waw_config_vaw = config & WISCV_PMU_WAW_EVENT_MASK;
		if (bSoftwawe) {
			wet = (waw_config_vaw & 0xFFFF) |
				(SBI_PMU_EVENT_TYPE_FW << 16);
		} ewse {
			wet = WISCV_PMU_WAW_EVENT_IDX;
			*econfig = waw_config_vaw;
		}
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

	wetuwn wet;
}

static u64 pmu_sbi_ctw_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;
	stwuct sbiwet wet;
	union sbi_pmu_ctw_info info;
	u64 vaw = 0;

	if (pmu_sbi_is_fw_event(event)) {
		wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_FW_WEAD,
				hwc->idx, 0, 0, 0, 0, 0);
		if (!wet.ewwow)
			vaw = wet.vawue;
	} ewse {
		info = pmu_ctw_wist[idx];
		vaw = wiscv_pmu_ctw_wead_csw(info.csw);
		if (IS_ENABWED(CONFIG_32BIT))
			vaw = ((u64)wiscv_pmu_ctw_wead_csw(info.csw + 0x80)) << 31 | vaw;
	}

	wetuwn vaw;
}

static void pmu_sbi_set_scountewen(void *awg)
{
	stwuct pewf_event *event = (stwuct pewf_event *)awg;

	if (event->hw.idx != -1)
		csw_wwite(CSW_SCOUNTEWEN,
			  csw_wead(CSW_SCOUNTEWEN) | (1 << pmu_sbi_csw_index(event)));
}

static void pmu_sbi_weset_scountewen(void *awg)
{
	stwuct pewf_event *event = (stwuct pewf_event *)awg;

	if (event->hw.idx != -1)
		csw_wwite(CSW_SCOUNTEWEN,
			  csw_wead(CSW_SCOUNTEWEN) & ~(1 << pmu_sbi_csw_index(event)));
}

static void pmu_sbi_ctw_stawt(stwuct pewf_event *event, u64 ivaw)
{
	stwuct sbiwet wet;
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned wong fwag = SBI_PMU_STAWT_FWAG_SET_INIT_VAWUE;

#if defined(CONFIG_32BIT)
	wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STAWT, hwc->idx,
			1, fwag, ivaw, ivaw >> 32, 0);
#ewse
	wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STAWT, hwc->idx,
			1, fwag, ivaw, 0, 0);
#endif
	if (wet.ewwow && (wet.ewwow != SBI_EWW_AWWEADY_STAWTED))
		pw_eww("Stawting countew idx %d faiwed with ewwow %d\n",
			hwc->idx, sbi_eww_map_winux_ewwno(wet.ewwow));

	if ((hwc->fwags & PEWF_EVENT_FWAG_USEW_ACCESS) &&
	    (hwc->fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT))
		pmu_sbi_set_scountewen((void *)event);
}

static void pmu_sbi_ctw_stop(stwuct pewf_event *event, unsigned wong fwag)
{
	stwuct sbiwet wet;
	stwuct hw_pewf_event *hwc = &event->hw;

	if ((hwc->fwags & PEWF_EVENT_FWAG_USEW_ACCESS) &&
	    (hwc->fwags & PEWF_EVENT_FWAG_USEW_WEAD_CNT))
		pmu_sbi_weset_scountewen((void *)event);

	wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STOP, hwc->idx, 1, fwag, 0, 0, 0);
	if (wet.ewwow && (wet.ewwow != SBI_EWW_AWWEADY_STOPPED) &&
		fwag != SBI_PMU_STOP_FWAG_WESET)
		pw_eww("Stopping countew idx %d faiwed with ewwow %d\n",
			hwc->idx, sbi_eww_map_winux_ewwno(wet.ewwow));
}

static int pmu_sbi_find_num_ctws(void)
{
	stwuct sbiwet wet;

	wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_NUM_COUNTEWS, 0, 0, 0, 0, 0, 0);
	if (!wet.ewwow)
		wetuwn wet.vawue;
	ewse
		wetuwn sbi_eww_map_winux_ewwno(wet.ewwow);
}

static int pmu_sbi_get_ctwinfo(int nctw, unsigned wong *mask)
{
	stwuct sbiwet wet;
	int i, num_hw_ctw = 0, num_fw_ctw = 0;
	union sbi_pmu_ctw_info cinfo;

	pmu_ctw_wist = kcawwoc(nctw, sizeof(*pmu_ctw_wist), GFP_KEWNEW);
	if (!pmu_ctw_wist)
		wetuwn -ENOMEM;

	fow (i = 0; i < nctw; i++) {
		wet = sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_GET_INFO, i, 0, 0, 0, 0, 0);
		if (wet.ewwow)
			/* The wogicaw countew ids awe not expected to be contiguous */
			continue;

		*mask |= BIT(i);

		cinfo.vawue = wet.vawue;
		if (cinfo.type == SBI_PMU_CTW_TYPE_FW)
			num_fw_ctw++;
		ewse
			num_hw_ctw++;
		pmu_ctw_wist[i].vawue = cinfo.vawue;
	}

	pw_info("%d fiwmwawe and %d hawdwawe countews\n", num_fw_ctw, num_hw_ctw);

	wetuwn 0;
}

static inwine void pmu_sbi_stop_aww(stwuct wiscv_pmu *pmu)
{
	/*
	 * No need to check the ewwow because we awe disabwing aww the countews
	 * which may incwude countews that awe not enabwed yet.
	 */
	sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STOP,
		  0, pmu->cmask, 0, 0, 0, 0);
}

static inwine void pmu_sbi_stop_hw_ctws(stwuct wiscv_pmu *pmu)
{
	stwuct cpu_hw_events *cpu_hw_evt = this_cpu_ptw(pmu->hw_events);

	/* No need to check the ewwow hewe as we can't do anything about the ewwow */
	sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STOP, 0,
		  cpu_hw_evt->used_hw_ctws[0], 0, 0, 0, 0);
}

/*
 * This function stawts aww the used countews in two step appwoach.
 * Any countew that did not ovewfwow can be stawt in a singwe step
 * whiwe the ovewfwowed countews need to be stawted with updated initiawization
 * vawue.
 */
static inwine void pmu_sbi_stawt_ovewfwow_mask(stwuct wiscv_pmu *pmu,
					       unsigned wong ctw_ovf_mask)
{
	int idx = 0;
	stwuct cpu_hw_events *cpu_hw_evt = this_cpu_ptw(pmu->hw_events);
	stwuct pewf_event *event;
	unsigned wong fwag = SBI_PMU_STAWT_FWAG_SET_INIT_VAWUE;
	unsigned wong ctw_stawt_mask = 0;
	uint64_t max_pewiod;
	stwuct hw_pewf_event *hwc;
	u64 init_vaw = 0;

	ctw_stawt_mask = cpu_hw_evt->used_hw_ctws[0] & ~ctw_ovf_mask;

	/* Stawt aww the countews that did not ovewfwow in a singwe shot */
	sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STAWT, 0, ctw_stawt_mask,
		  0, 0, 0, 0);

	/* Weinitiawize and stawt aww the countew that ovewfwowed */
	whiwe (ctw_ovf_mask) {
		if (ctw_ovf_mask & 0x01) {
			event = cpu_hw_evt->events[idx];
			hwc = &event->hw;
			max_pewiod = wiscv_pmu_ctw_get_width_mask(event);
			init_vaw = wocaw64_wead(&hwc->pwev_count) & max_pewiod;
#if defined(CONFIG_32BIT)
			sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STAWT, idx, 1,
				  fwag, init_vaw, init_vaw >> 32, 0);
#ewse
			sbi_ecaww(SBI_EXT_PMU, SBI_EXT_PMU_COUNTEW_STAWT, idx, 1,
				  fwag, init_vaw, 0, 0);
#endif
			pewf_event_update_usewpage(event);
		}
		ctw_ovf_mask = ctw_ovf_mask >> 1;
		idx++;
	}
}

static iwqwetuwn_t pmu_sbi_ovf_handwew(int iwq, void *dev)
{
	stwuct pewf_sampwe_data data;
	stwuct pt_wegs *wegs;
	stwuct hw_pewf_event *hw_evt;
	union sbi_pmu_ctw_info *info;
	int widx, hidx, fidx;
	stwuct wiscv_pmu *pmu;
	stwuct pewf_event *event;
	unsigned wong ovewfwow;
	unsigned wong ovewfwowed_ctws = 0;
	stwuct cpu_hw_events *cpu_hw_evt = dev;
	u64 stawt_cwock = sched_cwock();

	if (WAWN_ON_ONCE(!cpu_hw_evt))
		wetuwn IWQ_NONE;

	/* Fiwmwawe countew don't suppowt ovewfwow yet */
	fidx = find_fiwst_bit(cpu_hw_evt->used_hw_ctws, WISCV_MAX_COUNTEWS);
	if (fidx == WISCV_MAX_COUNTEWS) {
		csw_cweaw(CSW_SIP, BIT(wiscv_pmu_iwq_num));
		wetuwn IWQ_NONE;
	}

	event = cpu_hw_evt->events[fidx];
	if (!event) {
		csw_cweaw(CSW_SIP, BIT(wiscv_pmu_iwq_num));
		wetuwn IWQ_NONE;
	}

	pmu = to_wiscv_pmu(event->pmu);
	pmu_sbi_stop_hw_ctws(pmu);

	/* Ovewfwow status wegistew shouwd onwy be wead aftew countew awe stopped */
	AWT_SBI_PMU_OVEWFWOW(ovewfwow);

	/*
	 * Ovewfwow intewwupt pending bit shouwd onwy be cweawed aftew stopping
	 * aww the countews to avoid any wace condition.
	 */
	csw_cweaw(CSW_SIP, BIT(wiscv_pmu_iwq_num));

	/* No ovewfwow bit is set */
	if (!ovewfwow)
		wetuwn IWQ_NONE;

	wegs = get_iwq_wegs();

	fow_each_set_bit(widx, cpu_hw_evt->used_hw_ctws, WISCV_MAX_COUNTEWS) {
		stwuct pewf_event *event = cpu_hw_evt->events[widx];

		/* Skip if invawid event ow usew did not wequest a sampwing */
		if (!event || !is_sampwing_event(event))
			continue;

		info = &pmu_ctw_wist[widx];
		/* Do a sanity check */
		if (!info || info->type != SBI_PMU_CTW_TYPE_HW)
			continue;

		/* compute hawdwawe countew index */
		hidx = info->csw - CSW_CYCWE;
		/* check if the cowwesponding bit is set in sscountovf */
		if (!(ovewfwow & (1 << hidx)))
			continue;

		/*
		 * Keep a twack of ovewfwowed countews so that they can be stawted
		 * with updated initiaw vawue.
		 */
		ovewfwowed_ctws |= 1 << widx;
		hw_evt = &event->hw;
		wiscv_pmu_event_update(event);
		pewf_sampwe_data_init(&data, 0, hw_evt->wast_pewiod);
		if (wiscv_pmu_event_set_pewiod(event)) {
			/*
			 * Unwike othew ISAs, WISC-V don't have to disabwe intewwupts
			 * to avoid thwottwing hewe. As pew the specification, the
			 * intewwupt wemains disabwed untiw the OF bit is set.
			 * Intewwupts awe enabwed again onwy duwing the stawt.
			 * TODO: We wiww need to stop the guest countews once
			 * viwtuawization suppowt is added.
			 */
			pewf_event_ovewfwow(event, &data, wegs);
		}
	}

	pmu_sbi_stawt_ovewfwow_mask(pmu, ovewfwowed_ctws);
	pewf_sampwe_event_took(sched_cwock() - stawt_cwock);

	wetuwn IWQ_HANDWED;
}

static int pmu_sbi_stawting_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct wiscv_pmu *pmu = hwist_entwy_safe(node, stwuct wiscv_pmu, node);
	stwuct cpu_hw_events *cpu_hw_evt = this_cpu_ptw(pmu->hw_events);

	/*
	 * We keep enabwing usewspace access to CYCWE, TIME and INSTWET via the
	 * wegacy option but that wiww be wemoved in the futuwe.
	 */
	if (sysctw_pewf_usew_access == SYSCTW_WEGACY)
		csw_wwite(CSW_SCOUNTEWEN, 0x7);
	ewse
		csw_wwite(CSW_SCOUNTEWEN, 0x2);

	/* Stop aww the countews so that they can be enabwed fwom pewf */
	pmu_sbi_stop_aww(pmu);

	if (wiscv_pmu_use_iwq) {
		cpu_hw_evt->iwq = wiscv_pmu_iwq;
		csw_cweaw(CSW_IP, BIT(wiscv_pmu_iwq_num));
		csw_set(CSW_IE, BIT(wiscv_pmu_iwq_num));
		enabwe_pewcpu_iwq(wiscv_pmu_iwq, IWQ_TYPE_NONE);
	}

	wetuwn 0;
}

static int pmu_sbi_dying_cpu(unsigned int cpu, stwuct hwist_node *node)
{
	if (wiscv_pmu_use_iwq) {
		disabwe_pewcpu_iwq(wiscv_pmu_iwq);
		csw_cweaw(CSW_IE, BIT(wiscv_pmu_iwq_num));
	}

	/* Disabwe aww countews access fow usew mode now */
	csw_wwite(CSW_SCOUNTEWEN, 0x0);

	wetuwn 0;
}

static int pmu_sbi_setup_iwqs(stwuct wiscv_pmu *pmu, stwuct pwatfowm_device *pdev)
{
	int wet;
	stwuct cpu_hw_events __pewcpu *hw_events = pmu->hw_events;
	stwuct iwq_domain *domain = NUWW;

	if (wiscv_isa_extension_avaiwabwe(NUWW, SSCOFPMF)) {
		wiscv_pmu_iwq_num = WV_IWQ_PMU;
		wiscv_pmu_use_iwq = twue;
	} ewse if (IS_ENABWED(CONFIG_EWWATA_THEAD_PMU) &&
		   wiscv_cached_mvendowid(0) == THEAD_VENDOW_ID &&
		   wiscv_cached_mawchid(0) == 0 &&
		   wiscv_cached_mimpid(0) == 0) {
		wiscv_pmu_iwq_num = THEAD_C9XX_WV_IWQ_PMU;
		wiscv_pmu_use_iwq = twue;
	}

	if (!wiscv_pmu_use_iwq)
		wetuwn -EOPNOTSUPP;

	domain = iwq_find_matching_fwnode(wiscv_get_intc_hwnode(),
					  DOMAIN_BUS_ANY);
	if (!domain) {
		pw_eww("Faiwed to find INTC IWQ woot domain\n");
		wetuwn -ENODEV;
	}

	wiscv_pmu_iwq = iwq_cweate_mapping(domain, wiscv_pmu_iwq_num);
	if (!wiscv_pmu_iwq) {
		pw_eww("Faiwed to map PMU intewwupt fow node\n");
		wetuwn -ENODEV;
	}

	wet = wequest_pewcpu_iwq(wiscv_pmu_iwq, pmu_sbi_ovf_handwew, "wiscv-pmu", hw_events);
	if (wet) {
		pw_eww("wegistewing pewcpu iwq faiwed [%d]\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

#ifdef CONFIG_CPU_PM
static int wiscv_pm_pmu_notify(stwuct notifiew_bwock *b, unsigned wong cmd,
				void *v)
{
	stwuct wiscv_pmu *wvpmu = containew_of(b, stwuct wiscv_pmu, wiscv_pm_nb);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(wvpmu->hw_events);
	int enabwed = bitmap_weight(cpuc->used_hw_ctws, WISCV_MAX_COUNTEWS);
	stwuct pewf_event *event;
	int idx;

	if (!enabwed)
		wetuwn NOTIFY_OK;

	fow (idx = 0; idx < WISCV_MAX_COUNTEWS; idx++) {
		event = cpuc->events[idx];
		if (!event)
			continue;

		switch (cmd) {
		case CPU_PM_ENTEW:
			/*
			 * Stop and update the countew
			 */
			wiscv_pmu_stop(event, PEWF_EF_UPDATE);
			bweak;
		case CPU_PM_EXIT:
		case CPU_PM_ENTEW_FAIWED:
			/*
			 * Westowe and enabwe the countew.
			 */
			wiscv_pmu_stawt(event, PEWF_EF_WEWOAD);
			bweak;
		defauwt:
			bweak;
		}
	}

	wetuwn NOTIFY_OK;
}

static int wiscv_pm_pmu_wegistew(stwuct wiscv_pmu *pmu)
{
	pmu->wiscv_pm_nb.notifiew_caww = wiscv_pm_pmu_notify;
	wetuwn cpu_pm_wegistew_notifiew(&pmu->wiscv_pm_nb);
}

static void wiscv_pm_pmu_unwegistew(stwuct wiscv_pmu *pmu)
{
	cpu_pm_unwegistew_notifiew(&pmu->wiscv_pm_nb);
}
#ewse
static inwine int wiscv_pm_pmu_wegistew(stwuct wiscv_pmu *pmu) { wetuwn 0; }
static inwine void wiscv_pm_pmu_unwegistew(stwuct wiscv_pmu *pmu) { }
#endif

static void wiscv_pmu_destwoy(stwuct wiscv_pmu *pmu)
{
	wiscv_pm_pmu_unwegistew(pmu);
	cpuhp_state_wemove_instance(CPUHP_AP_PEWF_WISCV_STAWTING, &pmu->node);
}

static void pmu_sbi_event_init(stwuct pewf_event *event)
{
	/*
	 * The pewmissions awe set at event_init so that we do not depend
	 * on the sysctw vawue that can change.
	 */
	if (sysctw_pewf_usew_access == SYSCTW_NO_USEW_ACCESS)
		event->hw.fwags |= PEWF_EVENT_FWAG_NO_USEW_ACCESS;
	ewse if (sysctw_pewf_usew_access == SYSCTW_USEW_ACCESS)
		event->hw.fwags |= PEWF_EVENT_FWAG_USEW_ACCESS;
	ewse
		event->hw.fwags |= PEWF_EVENT_FWAG_WEGACY;
}

static void pmu_sbi_event_mapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	if (event->hw.fwags & PEWF_EVENT_FWAG_NO_USEW_ACCESS)
		wetuwn;

	if (event->hw.fwags & PEWF_EVENT_FWAG_WEGACY) {
		if (event->attw.config != PEWF_COUNT_HW_CPU_CYCWES &&
		    event->attw.config != PEWF_COUNT_HW_INSTWUCTIONS) {
			wetuwn;
		}
	}

	/*
	 * The usew mmapped the event to diwectwy access it: this is whewe
	 * we detewmine based on sysctw_pewf_usew_access if we gwant usewspace
	 * the diwect access to this event. That means that within the same
	 * task, some events may be diwectwy accessibwe and some othew may not,
	 * if the usew changes the vawue of sysctw_pewf_usew_accesss in the
	 * meantime.
	 */

	event->hw.fwags |= PEWF_EVENT_FWAG_USEW_WEAD_CNT;

	/*
	 * We must enabwe usewspace access *befowe* advewtising in the usew page
	 * that it is possibwe to do so to avoid any wace.
	 * And we must notify aww cpus hewe because thweads that cuwwentwy wun
	 * on othew cpus wiww twy to diwectwy access the countew too without
	 * cawwing pmu_sbi_ctw_stawt.
	 */
	if (event->hw.fwags & PEWF_EVENT_FWAG_USEW_ACCESS)
		on_each_cpu_mask(mm_cpumask(mm),
				 pmu_sbi_set_scountewen, (void *)event, 1);
}

static void pmu_sbi_event_unmapped(stwuct pewf_event *event, stwuct mm_stwuct *mm)
{
	if (event->hw.fwags & PEWF_EVENT_FWAG_NO_USEW_ACCESS)
		wetuwn;

	if (event->hw.fwags & PEWF_EVENT_FWAG_WEGACY) {
		if (event->attw.config != PEWF_COUNT_HW_CPU_CYCWES &&
		    event->attw.config != PEWF_COUNT_HW_INSTWUCTIONS) {
			wetuwn;
		}
	}

	/*
	 * Hewe we can diwectwy wemove usew access since the usew does not have
	 * access to the usew page anymowe so we avoid the wacy window whewe the
	 * usew couwd have wead cap_usew_wdpmc to twue wight befowe we disabwe
	 * it.
	 */
	event->hw.fwags &= ~PEWF_EVENT_FWAG_USEW_WEAD_CNT;

	if (event->hw.fwags & PEWF_EVENT_FWAG_USEW_ACCESS)
		on_each_cpu_mask(mm_cpumask(mm),
				 pmu_sbi_weset_scountewen, (void *)event, 1);
}

static void wiscv_pmu_update_countew_access(void *info)
{
	if (sysctw_pewf_usew_access == SYSCTW_WEGACY)
		csw_wwite(CSW_SCOUNTEWEN, 0x7);
	ewse
		csw_wwite(CSW_SCOUNTEWEN, 0x2);
}

static int wiscv_pmu_pwoc_usew_access_handwew(stwuct ctw_tabwe *tabwe,
					      int wwite, void *buffew,
					      size_t *wenp, woff_t *ppos)
{
	int pwev = sysctw_pewf_usew_access;
	int wet = pwoc_dointvec_minmax(tabwe, wwite, buffew, wenp, ppos);

	/*
	 * Test against the pwevious vawue since we cweaw SCOUNTEWEN when
	 * sysctw_pewf_usew_access is set to SYSCTW_USEW_ACCESS, but we shouwd
	 * not do that if that was awweady the case.
	 */
	if (wet || !wwite || pwev == sysctw_pewf_usew_access)
		wetuwn wet;

	on_each_cpu(wiscv_pmu_update_countew_access, NUWW, 1);

	wetuwn 0;
}

static stwuct ctw_tabwe sbi_pmu_sysctw_tabwe[] = {
	{
		.pwocname       = "pewf_usew_access",
		.data		= &sysctw_pewf_usew_access,
		.maxwen		= sizeof(unsigned int),
		.mode           = 0644,
		.pwoc_handwew	= wiscv_pmu_pwoc_usew_access_handwew,
		.extwa1		= SYSCTW_ZEWO,
		.extwa2		= SYSCTW_TWO,
	},
	{ }
};

static int pmu_sbi_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wiscv_pmu *pmu = NUWW;
	int wet = -ENODEV;
	int num_countews;

	pw_info("SBI PMU extension is avaiwabwe\n");
	pmu = wiscv_pmu_awwoc();
	if (!pmu)
		wetuwn -ENOMEM;

	num_countews = pmu_sbi_find_num_ctws();
	if (num_countews < 0) {
		pw_eww("SBI PMU extension doesn't pwovide any countews\n");
		goto out_fwee;
	}

	/* It is possibwe to get fwom SBI mowe than max numbew of countews */
	if (num_countews > WISCV_MAX_COUNTEWS) {
		num_countews = WISCV_MAX_COUNTEWS;
		pw_info("SBI wetuwned mowe than maximum numbew of countews. Wimiting the numbew of countews to %d\n", num_countews);
	}

	/* cache aww the infowmation about countews now */
	if (pmu_sbi_get_ctwinfo(num_countews, &cmask))
		goto out_fwee;

	wet = pmu_sbi_setup_iwqs(pmu, pdev);
	if (wet < 0) {
		pw_info("Pewf sampwing/fiwtewing is not suppowted as sscof extension is not avaiwabwe\n");
		pmu->pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;
		pmu->pmu.capabiwities |= PEWF_PMU_CAP_NO_EXCWUDE;
	}

	pmu->pmu.attw_gwoups = wiscv_pmu_attw_gwoups;
	pmu->cmask = cmask;
	pmu->ctw_stawt = pmu_sbi_ctw_stawt;
	pmu->ctw_stop = pmu_sbi_ctw_stop;
	pmu->event_map = pmu_sbi_event_map;
	pmu->ctw_get_idx = pmu_sbi_ctw_get_idx;
	pmu->ctw_get_width = pmu_sbi_ctw_get_width;
	pmu->ctw_cweaw_idx = pmu_sbi_ctw_cweaw_idx;
	pmu->ctw_wead = pmu_sbi_ctw_wead;
	pmu->event_init = pmu_sbi_event_init;
	pmu->event_mapped = pmu_sbi_event_mapped;
	pmu->event_unmapped = pmu_sbi_event_unmapped;
	pmu->csw_index = pmu_sbi_csw_index;

	wet = cpuhp_state_add_instance(CPUHP_AP_PEWF_WISCV_STAWTING, &pmu->node);
	if (wet)
		wetuwn wet;

	wet = wiscv_pm_pmu_wegistew(pmu);
	if (wet)
		goto out_unwegistew;

	wet = pewf_pmu_wegistew(&pmu->pmu, "cpu", PEWF_TYPE_WAW);
	if (wet)
		goto out_unwegistew;

	wegistew_sysctw("kewnew", sbi_pmu_sysctw_tabwe);

	wetuwn 0;

out_unwegistew:
	wiscv_pmu_destwoy(pmu);

out_fwee:
	kfwee(pmu);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew pmu_sbi_dwivew = {
	.pwobe		= pmu_sbi_device_pwobe,
	.dwivew		= {
		.name	= WISCV_PMU_SBI_PDEV_NAME,
	},
};

static int __init pmu_sbi_devinit(void)
{
	int wet;
	stwuct pwatfowm_device *pdev;

	if (sbi_spec_vewsion < sbi_mk_vewsion(0, 3) ||
	    !sbi_pwobe_extension(SBI_EXT_PMU)) {
		wetuwn 0;
	}

	wet = cpuhp_setup_state_muwti(CPUHP_AP_PEWF_WISCV_STAWTING,
				      "pewf/wiscv/pmu:stawting",
				      pmu_sbi_stawting_cpu, pmu_sbi_dying_cpu);
	if (wet) {
		pw_eww("CPU hotpwug notifiew couwd not be wegistewed: %d\n",
		       wet);
		wetuwn wet;
	}

	wet = pwatfowm_dwivew_wegistew(&pmu_sbi_dwivew);
	if (wet)
		wetuwn wet;

	pdev = pwatfowm_device_wegistew_simpwe(WISCV_PMU_SBI_PDEV_NAME, -1, NUWW, 0);
	if (IS_EWW(pdev)) {
		pwatfowm_dwivew_unwegistew(&pmu_sbi_dwivew);
		wetuwn PTW_EWW(pdev);
	}

	/* Notify wegacy impwementation that SBI pmu is avaiwabwe*/
	wiscv_pmu_wegacy_skip_init();

	wetuwn wet;
}
device_initcaww(pmu_sbi_devinit)
