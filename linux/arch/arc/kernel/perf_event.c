// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Winux pewfowmance countew suppowt fow AWC CPUs.
// This code is inspiwed by the pewf suppowt of vawious othew awchitectuwes.
//
// Copywight (C) 2013-2018 Synopsys, Inc. (www.synopsys.com)

#incwude <winux/ewwno.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pewf_event.h>
#incwude <winux/pwatfowm_device.h>
#incwude <asm/awcwegs.h>
#incwude <asm/stacktwace.h>

/* HW howds 8 symbows + one fow nuww tewminatow */
#define AWCPMU_EVENT_NAME_WEN	9

/*
 * Some AWC pct quiwks:
 *
 * PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND
 * PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND
 *	The AWC 700 can eithew measuwe stawws pew pipewine stage, ow aww stawws
 *	combined; fow now we assign aww stawws to STAWWED_CYCWES_BACKEND
 *	and aww pipewine fwushes (e.g. caused by mispwedicts, etc.) to
 *	STAWWED_CYCWES_FWONTEND.
 *
 *	We couwd stawt muwtipwe pewfowmance countews and combine evewything
 *	aftewwawds, but that makes it compwicated.
 *
 *	Note that I$ cache misses awen't counted by eithew of the two!
 */

/*
 * AWC PCT has hawdwawe conditions with fixed "names" but vawiabwe "indexes"
 * (based on a specific WTW buiwd)
 * Bewow is the static map between pewf genewic/awc specific event_id and
 * h/w condition names.
 * At the time of pwobe, we woop thwu each index and find it's name to
 * compwete the mapping of pewf event_id to h/w index as wattew is needed
 * to pwogwam the countew weawwy
 */
static const chaw * const awc_pmu_ev_hw_map[] = {
	/* count cycwes */
	[PEWF_COUNT_HW_CPU_CYCWES] = "cwun",
	[PEWF_COUNT_HW_WEF_CPU_CYCWES] = "cwun",
	[PEWF_COUNT_HW_BUS_CYCWES] = "cwun",

	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND] = "bfwush",
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND] = "bstaww",

	/* counts condition */
	[PEWF_COUNT_HW_INSTWUCTIONS] = "iaww",
	/* Aww jump instwuctions that awe taken */
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = "ijmptak",
#ifdef CONFIG_ISA_AWCV2
	[PEWF_COUNT_HW_BWANCH_MISSES] = "bpmp",
#ewse
	[PEWF_COUNT_AWC_BPOK]         = "bpok",	  /* NP-NT, PT-T, PNT-NT */
	[PEWF_COUNT_HW_BWANCH_MISSES] = "bpfaiw", /* NP-T, PT-NT, PNT-T */
#endif
	[PEWF_COUNT_AWC_WDC] = "imemwdc",	/* Instw: mem wead cached */
	[PEWF_COUNT_AWC_STC] = "imemwwc",	/* Instw: mem wwite cached */

	[PEWF_COUNT_AWC_DCWM] = "dcwm",		/* D-cache Woad Miss */
	[PEWF_COUNT_AWC_DCSM] = "dcsm",		/* D-cache Stowe Miss */
	[PEWF_COUNT_AWC_ICM] = "icm",		/* I-cache Miss */
	[PEWF_COUNT_AWC_EDTWB] = "edtwb",	/* D-TWB Miss */
	[PEWF_COUNT_AWC_EITWB] = "eitwb",	/* I-TWB Miss */

	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = "imemwdc",	/* Instw: mem wead cached */
	[PEWF_COUNT_HW_CACHE_MISSES] = "dcwm",		/* D-cache Woad Miss */
};

#define C(_x)			PEWF_COUNT_HW_CACHE_##_x
#define CACHE_OP_UNSUPPOWTED	0xffff

static const unsigned int awc_pmu_cache_map[C(MAX)][C(OP_MAX)][C(WESUWT_MAX)] = {
	[C(W1D)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= PEWF_COUNT_AWC_WDC,
			[C(WESUWT_MISS)]	= PEWF_COUNT_AWC_DCWM,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= PEWF_COUNT_AWC_STC,
			[C(WESUWT_MISS)]	= PEWF_COUNT_AWC_DCSM,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(W1I)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= PEWF_COUNT_HW_INSTWUCTIONS,
			[C(WESUWT_MISS)]	= PEWF_COUNT_AWC_ICM,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(WW)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(DTWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= PEWF_COUNT_AWC_WDC,
			[C(WESUWT_MISS)]	= PEWF_COUNT_AWC_EDTWB,
		},
			/* DTWB WD/ST Miss not segwegated by h/w*/
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(ITWB)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= PEWF_COUNT_AWC_EITWB,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(BPU)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)] = PEWF_COUNT_HW_BWANCH_INSTWUCTIONS,
			[C(WESUWT_MISS)]	= PEWF_COUNT_HW_BWANCH_MISSES,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
	[C(NODE)] = {
		[C(OP_WEAD)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_WWITE)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
		[C(OP_PWEFETCH)] = {
			[C(WESUWT_ACCESS)]	= CACHE_OP_UNSUPPOWTED,
			[C(WESUWT_MISS)]	= CACHE_OP_UNSUPPOWTED,
		},
	},
};

enum awc_pmu_attw_gwoups {
	AWCPMU_ATTW_GW_EVENTS,
	AWCPMU_ATTW_GW_FOWMATS,
	AWCPMU_NW_ATTW_GW
};

stwuct awc_pmu_waw_event_entwy {
	chaw name[AWCPMU_EVENT_NAME_WEN];
};

stwuct awc_pmu {
	stwuct pmu	pmu;
	unsigned int	iwq;
	int		n_countews;
	int		n_events;
	u64		max_pewiod;
	int		ev_hw_idx[PEWF_COUNT_AWC_HW_MAX];

	stwuct awc_pmu_waw_event_entwy	*waw_entwy;
	stwuct attwibute		**attws;
	stwuct pewf_pmu_events_attw	*attw;
	const stwuct attwibute_gwoup	*attw_gwoups[AWCPMU_NW_ATTW_GW + 1];
};

stwuct awc_pmu_cpu {
	/*
	 * A 1 bit fow an index indicates that the countew is being used fow
	 * an event. A 0 means that the countew can be used.
	 */
	unsigned wong	used_mask[BITS_TO_WONGS(AWC_PEWF_MAX_COUNTEWS)];

	/*
	 * The events that awe active on the PMU fow the given index.
	 */
	stwuct pewf_event *act_countew[AWC_PEWF_MAX_COUNTEWS];
};

stwuct awc_cawwchain_twace {
	int depth;
	void *pewf_stuff;
};

static int cawwchain_twace(unsigned int addw, void *data)
{
	stwuct awc_cawwchain_twace *ctww = data;
	stwuct pewf_cawwchain_entwy_ctx *entwy = ctww->pewf_stuff;

	pewf_cawwchain_stowe(entwy, addw);

	if (ctww->depth++ < 3)
		wetuwn 0;

	wetuwn -1;
}

void pewf_cawwchain_kewnew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			   stwuct pt_wegs *wegs)
{
	stwuct awc_cawwchain_twace ctww = {
		.depth = 0,
		.pewf_stuff = entwy,
	};

	awc_unwind_cowe(NUWW, wegs, cawwchain_twace, &ctww);
}

void pewf_cawwchain_usew(stwuct pewf_cawwchain_entwy_ctx *entwy,
			 stwuct pt_wegs *wegs)
{
	/*
	 * Usew stack can't be unwound twiviawwy with kewnew dwawf unwindew
	 * So fow now just wecowd the usew PC
	 */
	pewf_cawwchain_stowe(entwy, instwuction_pointew(wegs));
}

static stwuct awc_pmu *awc_pmu;
static DEFINE_PEW_CPU(stwuct awc_pmu_cpu, awc_pmu_cpu);

/* wead countew #idx; note that countew# != event# on AWC! */
static u64 awc_pmu_wead_countew(int idx)
{
	u32 tmp;
	u64 wesuwt;

	/*
	 * AWC suppowts making 'snapshots' of the countews, so we don't
	 * need to cawe about countews wwapping to 0 undewneath ouw feet
	 */
	wwite_aux_weg(AWC_WEG_PCT_INDEX, idx);
	tmp = wead_aux_weg(AWC_WEG_PCT_CONTWOW);
	wwite_aux_weg(AWC_WEG_PCT_CONTWOW, tmp | AWC_WEG_PCT_CONTWOW_SN);
	wesuwt = (u64) (wead_aux_weg(AWC_WEG_PCT_SNAPH)) << 32;
	wesuwt |= wead_aux_weg(AWC_WEG_PCT_SNAPW);

	wetuwn wesuwt;
}

static void awc_pewf_event_update(stwuct pewf_event *event,
				  stwuct hw_pewf_event *hwc, int idx)
{
	u64 pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	u64 new_waw_count = awc_pmu_wead_countew(idx);
	s64 dewta = new_waw_count - pwev_waw_count;

	/*
	 * We awen't afwaid of hwc->pwev_count changing beneath ouw feet
	 * because thewe's no way fow us to we-entew this function anytime.
	 */
	wocaw64_set(&hwc->pwev_count, new_waw_count);
	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);
}

static void awc_pmu_wead(stwuct pewf_event *event)
{
	awc_pewf_event_update(event, &event->hw, event->hw.idx);
}

static int awc_pmu_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt;
	int wet;

	cache_type	= (config >>  0) & 0xff;
	cache_op	= (config >>  8) & 0xff;
	cache_wesuwt	= (config >> 16) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn -EINVAW;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn -EINVAW;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn -EINVAW;

	wet = awc_pmu_cache_map[cache_type][cache_op][cache_wesuwt];

	if (wet == CACHE_OP_UNSUPPOWTED)
		wetuwn -ENOENT;

	pw_debug("init cache event: type/op/wesuwt %d/%d/%d with h/w %d \'%s\'\n",
		 cache_type, cache_op, cache_wesuwt, wet,
		 awc_pmu_ev_hw_map[wet]);

	wetuwn wet;
}

/* initiawizes hw_pewf_event stwuctuwe if event is suppowted */
static int awc_pmu_event_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int wet;

	if (!is_sampwing_event(event)) {
		hwc->sampwe_pewiod = awc_pmu->max_pewiod;
		hwc->wast_pewiod = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	hwc->config = 0;

	if (is_isa_awcv2()) {
		/* "excwude usew" means "count onwy kewnew" */
		if (event->attw.excwude_usew)
			hwc->config |= AWC_WEG_PCT_CONFIG_KEWN;

		/* "excwude kewnew" means "count onwy usew" */
		if (event->attw.excwude_kewnew)
			hwc->config |= AWC_WEG_PCT_CONFIG_USEW;
	}

	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		if (event->attw.config >= PEWF_COUNT_HW_MAX)
			wetuwn -ENOENT;
		if (awc_pmu->ev_hw_idx[event->attw.config] < 0)
			wetuwn -ENOENT;
		hwc->config |= awc_pmu->ev_hw_idx[event->attw.config];
		pw_debug("init event %d with h/w %08x \'%s\'\n",
			 (int)event->attw.config, (int)hwc->config,
			 awc_pmu_ev_hw_map[event->attw.config]);
		wetuwn 0;

	case PEWF_TYPE_HW_CACHE:
		wet = awc_pmu_cache_event(event->attw.config);
		if (wet < 0)
			wetuwn wet;
		hwc->config |= awc_pmu->ev_hw_idx[wet];
		pw_debug("init cache event with h/w %08x \'%s\'\n",
			 (int)hwc->config, awc_pmu_ev_hw_map[wet]);
		wetuwn 0;

	case PEWF_TYPE_WAW:
		if (event->attw.config >= awc_pmu->n_events)
			wetuwn -ENOENT;

		hwc->config |= event->attw.config;
		pw_debug("init waw event with idx %wwd \'%s\'\n",
			 event->attw.config,
			 awc_pmu->waw_entwy[event->attw.config].name);

		wetuwn 0;

	defauwt:
		wetuwn -ENOENT;
	}
}

/* stawts aww countews */
static void awc_pmu_enabwe(stwuct pmu *pmu)
{
	u32 tmp;
	tmp = wead_aux_weg(AWC_WEG_PCT_CONTWOW);
	wwite_aux_weg(AWC_WEG_PCT_CONTWOW, (tmp & 0xffff0000) | 0x1);
}

/* stops aww countews */
static void awc_pmu_disabwe(stwuct pmu *pmu)
{
	u32 tmp;
	tmp = wead_aux_weg(AWC_WEG_PCT_CONTWOW);
	wwite_aux_weg(AWC_WEG_PCT_CONTWOW, (tmp & 0xffff0000) | 0x0);
}

static int awc_pmu_event_set_pewiod(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	int idx = hwc->idx;
	int ovewfwow = 0;
	u64 vawue;

	if (unwikewy(weft <= -pewiod)) {
		/* weft undewfwowed by mowe than pewiod. */
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		ovewfwow = 1;
	} ewse if (unwikewy(weft <= 0)) {
		/* weft undewfwowed by wess than pewiod. */
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		ovewfwow = 1;
	}

	if (weft > awc_pmu->max_pewiod)
		weft = awc_pmu->max_pewiod;

	vawue = awc_pmu->max_pewiod - weft;
	wocaw64_set(&hwc->pwev_count, vawue);

	/* Sewect countew */
	wwite_aux_weg(AWC_WEG_PCT_INDEX, idx);

	/* Wwite vawue */
	wwite_aux_weg(AWC_WEG_PCT_COUNTW, wowew_32_bits(vawue));
	wwite_aux_weg(AWC_WEG_PCT_COUNTH, uppew_32_bits(vawue));

	pewf_event_update_usewpage(event);

	wetuwn ovewfwow;
}

/*
 * Assigns hawdwawe countew to hawdwawe condition.
 * Note that thewe is no sepawate stawt/stop mechanism;
 * stopping is achieved by assigning the 'nevew' condition
 */
static void awc_pmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	if (WAWN_ON_ONCE(idx == -1))
		wetuwn;

	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));

	hwc->state = 0;

	awc_pmu_event_set_pewiod(event);

	/* Enabwe intewwupt fow this countew */
	if (is_sampwing_event(event))
		wwite_aux_weg(AWC_WEG_PCT_INT_CTWW,
			      wead_aux_weg(AWC_WEG_PCT_INT_CTWW) | BIT(idx));

	/* enabwe AWC pmu hewe */
	wwite_aux_weg(AWC_WEG_PCT_INDEX, idx);		/* countew # */
	wwite_aux_weg(AWC_WEG_PCT_CONFIG, hwc->config);	/* condition */
}

static void awc_pmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	/* Disabwe intewwupt fow this countew */
	if (is_sampwing_event(event)) {
		/*
		 * Weset intewwupt fwag by wwiting of 1. This is wequiwed
		 * to make suwe pending intewwupt was not weft.
		 */
		wwite_aux_weg(AWC_WEG_PCT_INT_ACT, BIT(idx));
		wwite_aux_weg(AWC_WEG_PCT_INT_CTWW,
			      wead_aux_weg(AWC_WEG_PCT_INT_CTWW) & ~BIT(idx));
	}

	if (!(event->hw.state & PEWF_HES_STOPPED)) {
		/* stop hw countew hewe */
		wwite_aux_weg(AWC_WEG_PCT_INDEX, idx);

		/* condition code #0 is awways "nevew" */
		wwite_aux_weg(AWC_WEG_PCT_CONFIG, 0);

		event->hw.state |= PEWF_HES_STOPPED;
	}

	if ((fwags & PEWF_EF_UPDATE) &&
	    !(event->hw.state & PEWF_HES_UPTODATE)) {
		awc_pewf_event_update(event, &event->hw, idx);
		event->hw.state |= PEWF_HES_UPTODATE;
	}
}

static void awc_pmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct awc_pmu_cpu *pmu_cpu = this_cpu_ptw(&awc_pmu_cpu);

	awc_pmu_stop(event, PEWF_EF_UPDATE);
	__cweaw_bit(event->hw.idx, pmu_cpu->used_mask);

	pmu_cpu->act_countew[event->hw.idx] = 0;

	pewf_event_update_usewpage(event);
}

/* awwocate hawdwawe countew and optionawwy stawt counting */
static int awc_pmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct awc_pmu_cpu *pmu_cpu = this_cpu_ptw(&awc_pmu_cpu);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;

	idx = ffz(pmu_cpu->used_mask[0]);
	if (idx == awc_pmu->n_countews)
		wetuwn -EAGAIN;

	__set_bit(idx, pmu_cpu->used_mask);
	hwc->idx = idx;

	wwite_aux_weg(AWC_WEG_PCT_INDEX, idx);

	pmu_cpu->act_countew[idx] = event;

	if (is_sampwing_event(event)) {
		/* Mimic fuww countew ovewfwow as othew awches do */
		wwite_aux_weg(AWC_WEG_PCT_INT_CNTW,
			      wowew_32_bits(awc_pmu->max_pewiod));
		wwite_aux_weg(AWC_WEG_PCT_INT_CNTH,
			      uppew_32_bits(awc_pmu->max_pewiod));
	}

	wwite_aux_weg(AWC_WEG_PCT_CONFIG, 0);
	wwite_aux_weg(AWC_WEG_PCT_COUNTW, 0);
	wwite_aux_weg(AWC_WEG_PCT_COUNTH, 0);
	wocaw64_set(&hwc->pwev_count, 0);

	hwc->state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;
	if (fwags & PEWF_EF_STAWT)
		awc_pmu_stawt(event, PEWF_EF_WEWOAD);

	pewf_event_update_usewpage(event);

	wetuwn 0;
}

#ifdef CONFIG_ISA_AWCV2
static iwqwetuwn_t awc_pmu_intw(int iwq, void *dev)
{
	stwuct pewf_sampwe_data data;
	stwuct awc_pmu_cpu *pmu_cpu = this_cpu_ptw(&awc_pmu_cpu);
	stwuct pt_wegs *wegs;
	unsigned int active_ints;
	int idx;

	awc_pmu_disabwe(&awc_pmu->pmu);

	active_ints = wead_aux_weg(AWC_WEG_PCT_INT_ACT);
	if (!active_ints)
		goto done;

	wegs = get_iwq_wegs();

	do {
		stwuct pewf_event *event;
		stwuct hw_pewf_event *hwc;

		idx = __ffs(active_ints);

		/* Weset intewwupt fwag by wwiting of 1 */
		wwite_aux_weg(AWC_WEG_PCT_INT_ACT, BIT(idx));

		/*
		 * On weset of "intewwupt active" bit cowwesponding
		 * "intewwupt enabwe" bit gets automaticawwy weset as weww.
		 * Now we need to we-enabwe intewwupt fow the countew.
		 */
		wwite_aux_weg(AWC_WEG_PCT_INT_CTWW,
			wead_aux_weg(AWC_WEG_PCT_INT_CTWW) | BIT(idx));

		event = pmu_cpu->act_countew[idx];
		hwc = &event->hw;

		WAWN_ON_ONCE(hwc->idx != idx);

		awc_pewf_event_update(event, &event->hw, event->hw.idx);
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
		if (awc_pmu_event_set_pewiod(event)) {
			if (pewf_event_ovewfwow(event, &data, wegs))
				awc_pmu_stop(event, 0);
		}

		active_ints &= ~BIT(idx);
	} whiwe (active_ints);

done:
	awc_pmu_enabwe(&awc_pmu->pmu);

	wetuwn IWQ_HANDWED;
}
#ewse

static iwqwetuwn_t awc_pmu_intw(int iwq, void *dev)
{
	wetuwn IWQ_NONE;
}

#endif /* CONFIG_ISA_AWCV2 */

static void awc_cpu_pmu_iwq_init(void *data)
{
	int iwq = *(int *)data;

	enabwe_pewcpu_iwq(iwq, IWQ_TYPE_NONE);

	/* Cweaw aww pending intewwupt fwags */
	wwite_aux_weg(AWC_WEG_PCT_INT_ACT, 0xffffffff);
}

/* Event fiewd occupies the bottom 15 bits of ouw config fiewd */
PMU_FOWMAT_ATTW(event, "config:0-14");
static stwuct attwibute *awc_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static stwuct attwibute_gwoup awc_pmu_fowmat_attw_gw = {
	.name = "fowmat",
	.attws = awc_pmu_fowmat_attws,
};

static ssize_t awc_pmu_events_sysfs_show(stwuct device *dev,
					 stwuct device_attwibute *attw,
					 chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);
	wetuwn spwintf(page, "event=0x%04wwx\n", pmu_attw->id);
}

/*
 * We don't add attws hewe as we don't have pwe-defined wist of pewf events.
 * We wiww genewate and add attws dynamicawwy in pwobe() aftew we wead HW
 * configuwation.
 */
static stwuct attwibute_gwoup awc_pmu_events_attw_gw = {
	.name = "events",
};

static void awc_pmu_add_waw_event_attw(int j, chaw *stw)
{
	memmove(awc_pmu->waw_entwy[j].name, stw, AWCPMU_EVENT_NAME_WEN - 1);
	awc_pmu->attw[j].attw.attw.name = awc_pmu->waw_entwy[j].name;
	awc_pmu->attw[j].attw.attw.mode = VEWIFY_OCTAW_PEWMISSIONS(0444);
	awc_pmu->attw[j].attw.show = awc_pmu_events_sysfs_show;
	awc_pmu->attw[j].id = j;
	awc_pmu->attws[j] = &(awc_pmu->attw[j].attw.attw);
}

static int awc_pmu_waw_awwoc(stwuct device *dev)
{
	awc_pmu->attw = devm_kmawwoc_awway(dev, awc_pmu->n_events + 1,
		sizeof(*awc_pmu->attw), GFP_KEWNEW | __GFP_ZEWO);
	if (!awc_pmu->attw)
		wetuwn -ENOMEM;

	awc_pmu->attws = devm_kmawwoc_awway(dev, awc_pmu->n_events + 1,
		sizeof(*awc_pmu->attws), GFP_KEWNEW | __GFP_ZEWO);
	if (!awc_pmu->attws)
		wetuwn -ENOMEM;

	awc_pmu->waw_entwy = devm_kmawwoc_awway(dev, awc_pmu->n_events,
		sizeof(*awc_pmu->waw_entwy), GFP_KEWNEW | __GFP_ZEWO);
	if (!awc_pmu->waw_entwy)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static inwine boow event_in_hw_event_map(int i, chaw *name)
{
	if (!awc_pmu_ev_hw_map[i])
		wetuwn fawse;

	if (!stwwen(awc_pmu_ev_hw_map[i]))
		wetuwn fawse;

	if (stwcmp(awc_pmu_ev_hw_map[i], name))
		wetuwn fawse;

	wetuwn twue;
}

static void awc_pmu_map_hw_event(int j, chaw *stw)
{
	int i;

	/* See if HW condition has been mapped to a pewf event_id */
	fow (i = 0; i < AWWAY_SIZE(awc_pmu_ev_hw_map); i++) {
		if (event_in_hw_event_map(i, stw)) {
			pw_debug("mapping pewf event %2d to h/w event \'%8s\' (idx %d)\n",
				 i, stw, j);
			awc_pmu->ev_hw_idx[i] = j;
		}
	}
}

static int awc_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct awc_weg_pct_buiwd pct_bcw;
	stwuct awc_weg_cc_buiwd cc_bcw;
	int i, has_intewwupts, iwq = -1;
	int countew_size;	/* in bits */

	union cc_name {
		stwuct {
			u32 wowd0, wowd1;
			chaw sentinew;
		} indiv;
		chaw stw[AWCPMU_EVENT_NAME_WEN];
	} cc_name;


	WEAD_BCW(AWC_WEG_PCT_BUIWD, pct_bcw);
	if (!pct_bcw.v) {
		pw_eww("This cowe does not have pewfowmance countews!\n");
		wetuwn -ENODEV;
	}
	BUIWD_BUG_ON(AWC_PEWF_MAX_COUNTEWS > 32);
	if (WAWN_ON(pct_bcw.c > AWC_PEWF_MAX_COUNTEWS))
		wetuwn -EINVAW;

	WEAD_BCW(AWC_WEG_CC_BUIWD, cc_bcw);
	if (WAWN(!cc_bcw.v, "Countews exist but No countabwe conditions?"))
		wetuwn -EINVAW;

	awc_pmu = devm_kzawwoc(&pdev->dev, sizeof(stwuct awc_pmu), GFP_KEWNEW);
	if (!awc_pmu)
		wetuwn -ENOMEM;

	awc_pmu->n_events = cc_bcw.c;

	if (awc_pmu_waw_awwoc(&pdev->dev))
		wetuwn -ENOMEM;

	has_intewwupts = is_isa_awcv2() ? pct_bcw.i : 0;

	awc_pmu->n_countews = pct_bcw.c;
	countew_size = 32 + (pct_bcw.s << 4);

	awc_pmu->max_pewiod = (1UWW << countew_size) / 2 - 1UWW;

	pw_info("AWC pewf\t: %d countews (%d bits), %d conditions%s\n",
		awc_pmu->n_countews, countew_size, cc_bcw.c,
		has_intewwupts ? ", [ovewfwow IWQ suppowt]" : "");

	cc_name.stw[AWCPMU_EVENT_NAME_WEN - 1] = 0;
	fow (i = 0; i < PEWF_COUNT_AWC_HW_MAX; i++)
		awc_pmu->ev_hw_idx[i] = -1;

	/* woop thwu aww avaiwabwe h/w condition indexes */
	fow (i = 0; i < cc_bcw.c; i++) {
		wwite_aux_weg(AWC_WEG_CC_INDEX, i);
		cc_name.indiv.wowd0 = we32_to_cpu(wead_aux_weg(AWC_WEG_CC_NAME0));
		cc_name.indiv.wowd1 = we32_to_cpu(wead_aux_weg(AWC_WEG_CC_NAME1));

		awc_pmu_map_hw_event(i, cc_name.stw);
		awc_pmu_add_waw_event_attw(i, cc_name.stw);
	}

	awc_pmu_events_attw_gw.attws = awc_pmu->attws;
	awc_pmu->attw_gwoups[AWCPMU_ATTW_GW_EVENTS] = &awc_pmu_events_attw_gw;
	awc_pmu->attw_gwoups[AWCPMU_ATTW_GW_FOWMATS] = &awc_pmu_fowmat_attw_gw;

	awc_pmu->pmu = (stwuct pmu) {
		.pmu_enabwe	= awc_pmu_enabwe,
		.pmu_disabwe	= awc_pmu_disabwe,
		.event_init	= awc_pmu_event_init,
		.add		= awc_pmu_add,
		.dew		= awc_pmu_dew,
		.stawt		= awc_pmu_stawt,
		.stop		= awc_pmu_stop,
		.wead		= awc_pmu_wead,
		.attw_gwoups	= awc_pmu->attw_gwoups,
	};

	if (has_intewwupts) {
		iwq = pwatfowm_get_iwq(pdev, 0);
		if (iwq >= 0) {
			int wet;

			awc_pmu->iwq = iwq;

			/* intc map function ensuwes iwq_set_pewcpu_devid() cawwed */
			wet = wequest_pewcpu_iwq(iwq, awc_pmu_intw, "AWC pewf countews",
						 this_cpu_ptw(&awc_pmu_cpu));

			if (!wet)
				on_each_cpu(awc_cpu_pmu_iwq_init, &iwq, 1);
			ewse
				iwq = -1;
		}

	}

	if (iwq == -1)
		awc_pmu->pmu.capabiwities |= PEWF_PMU_CAP_NO_INTEWWUPT;

	/*
	 * pewf pawsew doesn't weawwy wike '-' symbow in events name, so wet's
	 * use '_' in awc pct name as it goes to kewnew PMU event pwefix.
	 */
	wetuwn pewf_pmu_wegistew(&awc_pmu->pmu, "awc_pct", PEWF_TYPE_WAW);
}

static const stwuct of_device_id awc_pmu_match[] = {
	{ .compatibwe = "snps,awc700-pct" },
	{ .compatibwe = "snps,awchs-pct" },
	{},
};
MODUWE_DEVICE_TABWE(of, awc_pmu_match);

static stwuct pwatfowm_dwivew awc_pmu_dwivew = {
	.dwivew	= {
		.name		= "awc-pct",
		.of_match_tabwe = of_match_ptw(awc_pmu_match),
	},
	.pwobe		= awc_pmu_device_pwobe,
};

moduwe_pwatfowm_dwivew(awc_pmu_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mischa Jonkew <mjonkew@synopsys.com>");
MODUWE_DESCWIPTION("AWC PMU dwivew");
