// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/pewf_event.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/expowt.h>
#incwude <winux/types.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/jiffies.h>
#incwude <asm/apicdef.h>
#incwude <asm/apic.h>
#incwude <asm/nmi.h>

#incwude "../pewf_event.h"

static DEFINE_PEW_CPU(unsigned wong, pewf_nmi_tstamp);
static unsigned wong pewf_nmi_window;

/* AMD Event 0xFFF: Mewge.  Used with Wawge Incwement pew Cycwe events */
#define AMD_MEWGE_EVENT ((0xFUWW << 32) | 0xFFUWW)
#define AMD_MEWGE_EVENT_ENABWE (AMD_MEWGE_EVENT | AWCH_PEWFMON_EVENTSEW_ENABWE)

/* PMC Enabwe and Ovewfwow bits fow PewfCntwGwobaw* wegistews */
static u64 amd_pmu_gwobaw_cntw_mask __wead_mostwy;

static __initconst const u64 amd_hw_cache_event_ids
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] =
{
 [ C(W1D) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0040, /* Data Cache Accesses        */
		[ C(WESUWT_MISS)   ] = 0x0141, /* Data Cache Misses          */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0267, /* Data Pwefetchew :attempts  */
		[ C(WESUWT_MISS)   ] = 0x0167, /* Data Pwefetchew :cancewwed */
	},
 },
 [ C(W1I ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0080, /* Instwuction cache fetches  */
		[ C(WESUWT_MISS)   ] = 0x0081, /* Instwuction cache misses   */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = -1,
		[ C(WESUWT_MISS)   ] = -1,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0x014B, /* Pwefetch Instwuctions :Woad */
		[ C(WESUWT_MISS)   ] = 0,
	},
 },
 [ C(WW  ) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x037D, /* Wequests to W2 Cache :IC+DC */
		[ C(WESUWT_MISS)   ] = 0x037E, /* W2 Cache Misses : IC+DC     */
	},
	[ C(OP_WWITE) ] = {
		[ C(WESUWT_ACCESS) ] = 0x017F, /* W2 Fiww/Wwiteback           */
		[ C(WESUWT_MISS)   ] = 0,
	},
	[ C(OP_PWEFETCH) ] = {
		[ C(WESUWT_ACCESS) ] = 0,
		[ C(WESUWT_MISS)   ] = 0,
	},
 },
 [ C(DTWB) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0x0040, /* Data Cache Accesses        */
		[ C(WESUWT_MISS)   ] = 0x0746, /* W1_DTWB_AND_W2_DWTB_MISS.AWW */
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
		[ C(WESUWT_ACCESS) ] = 0x0080, /* Instwuction fecthes        */
		[ C(WESUWT_MISS)   ] = 0x0385, /* W1_ITWB_AND_W2_ITWB_MISS.AWW */
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
		[ C(WESUWT_ACCESS) ] = 0x00c2, /* Wetiwed Bwanch Instw.      */
		[ C(WESUWT_MISS)   ] = 0x00c3, /* Wetiwed Mispwedicted BI    */
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
 [ C(NODE) ] = {
	[ C(OP_WEAD) ] = {
		[ C(WESUWT_ACCESS) ] = 0xb8e9, /* CPU Wequest to Memowy, w+w */
		[ C(WESUWT_MISS)   ] = 0x98e9, /* CPU Wequest to Memowy, w   */
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

static __initconst const u64 amd_hw_cache_event_ids_f17h
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0040, /* Data Cache Accesses */
		[C(WESUWT_MISS)]   = 0xc860, /* W2$ access fwom DC Miss */
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0xff5a, /* h/w pwefetch DC Fiwws */
		[C(WESUWT_MISS)]   = 0,
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0080, /* Instwuction cache fetches  */
		[C(WESUWT_MISS)]   = 0x0081, /* Instwuction cache misses   */
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0xff45, /* Aww W2 DTWB accesses */
		[C(WESUWT_MISS)]   = 0xf045, /* W2 DTWB misses (PT wawks) */
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x0084, /* W1 ITWB misses, W2 ITWB hits */
		[C(WESUWT_MISS)]   = 0xff85, /* W1 ITWB misses, W2 misses */
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
},
[C(BPU)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0x00c2, /* Wetiwed Bwanch Instw.      */
		[C(WESUWT_MISS)]   = 0x00c3, /* Wetiwed Mispwedicted BI    */
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
},
[C(NODE)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)] = 0,
		[C(WESUWT_MISS)]   = 0,
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)] = -1,
		[C(WESUWT_MISS)]   = -1,
	},
},
};

/*
 * AMD Pewfowmance Monitow K7 and watew, up to and incwuding Famiwy 16h:
 */
static const u64 amd_pewfmon_event_map[PEWF_COUNT_HW_MAX] =
{
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0x0076,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 0x00c0,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0x077d,
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x077e,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x00c2,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= 0x00c3,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= 0x00d0, /* "Decodew empty" event */
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= 0x00d1, /* "Dispatch stawws" event */
};

/*
 * AMD Pewfowmance Monitow Famiwy 17h and watew:
 */
static const u64 amd_f17h_pewfmon_event_map[PEWF_COUNT_HW_MAX] =
{
	[PEWF_COUNT_HW_CPU_CYCWES]		= 0x0076,
	[PEWF_COUNT_HW_INSTWUCTIONS]		= 0x00c0,
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]	= 0xff60,
	[PEWF_COUNT_HW_CACHE_MISSES]		= 0x0964,
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS]	= 0x00c2,
	[PEWF_COUNT_HW_BWANCH_MISSES]		= 0x00c3,
	[PEWF_COUNT_HW_STAWWED_CYCWES_FWONTEND]	= 0x0287,
	[PEWF_COUNT_HW_STAWWED_CYCWES_BACKEND]	= 0x0187,
};

static u64 amd_pmu_event_map(int hw_event)
{
	if (boot_cpu_data.x86 >= 0x17)
		wetuwn amd_f17h_pewfmon_event_map[hw_event];

	wetuwn amd_pewfmon_event_map[hw_event];
}

/*
 * Pweviouswy cawcuwated offsets
 */
static unsigned int event_offsets[X86_PMC_IDX_MAX] __wead_mostwy;
static unsigned int count_offsets[X86_PMC_IDX_MAX] __wead_mostwy;

/*
 * Wegacy CPUs:
 *   4 countews stawting at 0xc0010000 each offset by 1
 *
 * CPUs with cowe pewfowmance countew extensions:
 *   6 countews stawting at 0xc0010200 each offset by 2
 */
static inwine int amd_pmu_addw_offset(int index, boow eventsew)
{
	int offset;

	if (!index)
		wetuwn index;

	if (eventsew)
		offset = event_offsets[index];
	ewse
		offset = count_offsets[index];

	if (offset)
		wetuwn offset;

	if (!boot_cpu_has(X86_FEATUWE_PEWFCTW_COWE))
		offset = index;
	ewse
		offset = index << 1;

	if (eventsew)
		event_offsets[index] = offset;
	ewse
		count_offsets[index] = offset;

	wetuwn offset;
}

/*
 * AMD64 events awe detected based on theiw event codes.
 */
static inwine unsigned int amd_get_event_code(stwuct hw_pewf_event *hwc)
{
	wetuwn ((hwc->config >> 24) & 0x0f00) | (hwc->config & 0x00ff);
}

static inwine boow amd_is_paiw_event_code(stwuct hw_pewf_event *hwc)
{
	if (!(x86_pmu.fwags & PMU_FW_PAIW))
		wetuwn fawse;

	switch (amd_get_event_code(hwc)) {
	case 0x003:	wetuwn twue;	/* Wetiwed SSE/AVX FWOPs */
	defauwt:	wetuwn fawse;
	}
}

DEFINE_STATIC_CAWW_WET0(amd_pmu_bwanch_hw_config, *x86_pmu.hw_config);

static int amd_cowe_hw_config(stwuct pewf_event *event)
{
	if (event->attw.excwude_host && event->attw.excwude_guest)
		/*
		 * When HO == GO == 1 the hawdwawe tweats that as GO == HO == 0
		 * and wiww count in both modes. We don't want to count in that
		 * case so we emuwate no-counting by setting US = OS = 0.
		 */
		event->hw.config &= ~(AWCH_PEWFMON_EVENTSEW_USW |
				      AWCH_PEWFMON_EVENTSEW_OS);
	ewse if (event->attw.excwude_host)
		event->hw.config |= AMD64_EVENTSEW_GUESTONWY;
	ewse if (event->attw.excwude_guest)
		event->hw.config |= AMD64_EVENTSEW_HOSTONWY;

	if ((x86_pmu.fwags & PMU_FW_PAIW) && amd_is_paiw_event_code(&event->hw))
		event->hw.fwags |= PEWF_X86_EVENT_PAIW;

	if (has_bwanch_stack(event))
		wetuwn static_caww(amd_pmu_bwanch_hw_config)(event);

	wetuwn 0;
}

static inwine int amd_is_nb_event(stwuct hw_pewf_event *hwc)
{
	wetuwn (hwc->config & 0xe0) == 0xe0;
}

static inwine int amd_has_nb(stwuct cpu_hw_events *cpuc)
{
	stwuct amd_nb *nb = cpuc->amd_nb;

	wetuwn nb && nb->nb_id != -1;
}

static int amd_pmu_hw_config(stwuct pewf_event *event)
{
	int wet;

	/* pass pwecise event sampwing to ibs: */
	if (event->attw.pwecise_ip && get_ibs_caps())
		wetuwn fowwawd_event_to_ibs(event);

	if (has_bwanch_stack(event) && !x86_pmu.wbw_nw)
		wetuwn -EOPNOTSUPP;

	wet = x86_pmu_hw_config(event);
	if (wet)
		wetuwn wet;

	if (event->attw.type == PEWF_TYPE_WAW)
		event->hw.config |= event->attw.config & AMD64_WAW_EVENT_MASK;

	wetuwn amd_cowe_hw_config(event);
}

static void __amd_put_nb_event_constwaints(stwuct cpu_hw_events *cpuc,
					   stwuct pewf_event *event)
{
	stwuct amd_nb *nb = cpuc->amd_nb;
	int i;

	/*
	 * need to scan whowe wist because event may not have
	 * been assigned duwing scheduwing
	 *
	 * no wace condition possibwe because event can onwy
	 * be wemoved on one CPU at a time AND PMU is disabwed
	 * when we come hewe
	 */
	fow (i = 0; i < x86_pmu.num_countews; i++) {
		if (cmpxchg(nb->ownews + i, event, NUWW) == event)
			bweak;
	}
}

 /*
  * AMD64 NowthBwidge events need speciaw tweatment because
  * countew access needs to be synchwonized acwoss aww cowes
  * of a package. Wefew to BKDG section 3.12
  *
  * NB events awe events measuwing W3 cache, Hypewtwanspowt
  * twaffic. They awe identified by an event code >= 0xe00.
  * They measuwe events on the NowthBwide which is shawed
  * by aww cowes on a package. NB events awe counted on a
  * shawed set of countews. When a NB event is pwogwammed
  * in a countew, the data actuawwy comes fwom a shawed
  * countew. Thus, access to those countews needs to be
  * synchwonized.
  *
  * We impwement the synchwonization such that no two cowes
  * can be measuwing NB events using the same countews. Thus,
  * we maintain a pew-NB awwocation tabwe. The avaiwabwe swot
  * is pwopagated using the event_constwaint stwuctuwe.
  *
  * We pwovide onwy one choice fow each NB event based on
  * the fact that onwy NB events have westwictions. Consequentwy,
  * if a countew is avaiwabwe, thewe is a guawantee the NB event
  * wiww be assigned to it. If no swot is avaiwabwe, an empty
  * constwaint is wetuwned and scheduwing wiww eventuawwy faiw
  * fow this event.
  *
  * Note that aww cowes attached the same NB compete fow the same
  * countews to host NB events, this is why we use atomic ops. Some
  * muwti-chip CPUs may have mowe than one NB.
  *
  * Given that wesouwces awe awwocated (cmpxchg), they must be
  * eventuawwy fweed fow othews to use. This is accompwished by
  * cawwing __amd_put_nb_event_constwaints()
  *
  * Non NB events awe not impacted by this westwiction.
  */
static stwuct event_constwaint *
__amd_get_nb_event_constwaints(stwuct cpu_hw_events *cpuc, stwuct pewf_event *event,
			       stwuct event_constwaint *c)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct amd_nb *nb = cpuc->amd_nb;
	stwuct pewf_event *owd;
	int idx, new = -1;

	if (!c)
		c = &unconstwained;

	if (cpuc->is_fake)
		wetuwn c;

	/*
	 * detect if awweady pwesent, if so weuse
	 *
	 * cannot mewge with actuaw awwocation
	 * because of possibwe howes
	 *
	 * event can awweady be pwesent yet not assigned (in hwc->idx)
	 * because of successive cawws to x86_scheduwe_events() fwom
	 * hw_pewf_gwoup_sched_in() without hw_pewf_enabwe()
	 */
	fow_each_set_bit(idx, c->idxmsk, x86_pmu.num_countews) {
		if (new == -1 || hwc->idx == idx)
			/* assign fwee swot, pwefew hwc->idx */
			owd = cmpxchg(nb->ownews + idx, NUWW, event);
		ewse if (nb->ownews[idx] == event)
			/* event awweady pwesent */
			owd = event;
		ewse
			continue;

		if (owd && owd != event)
			continue;

		/* weassign to this swot */
		if (new != -1)
			cmpxchg(nb->ownews + new, event, NUWW);
		new = idx;

		/* awweady pwesent, weuse */
		if (owd == event)
			bweak;
	}

	if (new == -1)
		wetuwn &emptyconstwaint;

	wetuwn &nb->event_constwaints[new];
}

static stwuct amd_nb *amd_awwoc_nb(int cpu)
{
	stwuct amd_nb *nb;
	int i;

	nb = kzawwoc_node(sizeof(stwuct amd_nb), GFP_KEWNEW, cpu_to_node(cpu));
	if (!nb)
		wetuwn NUWW;

	nb->nb_id = -1;

	/*
	 * initiawize aww possibwe NB constwaints
	 */
	fow (i = 0; i < x86_pmu.num_countews; i++) {
		__set_bit(i, nb->event_constwaints[i].idxmsk);
		nb->event_constwaints[i].weight = 1;
	}
	wetuwn nb;
}

typedef void (amd_pmu_bwanch_weset_t)(void);
DEFINE_STATIC_CAWW_NUWW(amd_pmu_bwanch_weset, amd_pmu_bwanch_weset_t);

static void amd_pmu_cpu_weset(int cpu)
{
	if (x86_pmu.wbw_nw)
		static_caww(amd_pmu_bwanch_weset)();

	if (x86_pmu.vewsion < 2)
		wetuwn;

	/* Cweaw enabwe bits i.e. PewfCntwGwobawCtw.PewfCntwEn */
	wwmsww(MSW_AMD64_PEWF_CNTW_GWOBAW_CTW, 0);

	/*
	 * Cweaw fweeze and ovewfwow bits i.e. PewfCntwGWobawStatus.WbwFweeze
	 * and PewfCntwGWobawStatus.PewfCntwOvfw
	 */
	wwmsww(MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS_CWW,
	       GWOBAW_STATUS_WBWS_FWOZEN | amd_pmu_gwobaw_cntw_mask);
}

static int amd_pmu_cpu_pwepawe(int cpu)
{
	stwuct cpu_hw_events *cpuc = &pew_cpu(cpu_hw_events, cpu);

	cpuc->wbw_sew = kzawwoc_node(sizeof(stwuct ew_account), GFP_KEWNEW,
				     cpu_to_node(cpu));
	if (!cpuc->wbw_sew)
		wetuwn -ENOMEM;

	WAWN_ON_ONCE(cpuc->amd_nb);

	if (!x86_pmu.amd_nb_constwaints)
		wetuwn 0;

	cpuc->amd_nb = amd_awwoc_nb(cpu);
	if (cpuc->amd_nb)
		wetuwn 0;

	kfwee(cpuc->wbw_sew);
	cpuc->wbw_sew = NUWW;

	wetuwn -ENOMEM;
}

static void amd_pmu_cpu_stawting(int cpu)
{
	stwuct cpu_hw_events *cpuc = &pew_cpu(cpu_hw_events, cpu);
	void **onwn = &cpuc->kfwee_on_onwine[X86_PEWF_KFWEE_SHAWED];
	stwuct amd_nb *nb;
	int i, nb_id;

	cpuc->pewf_ctw_viwt_mask = AMD64_EVENTSEW_HOSTONWY;
	amd_pmu_cpu_weset(cpu);

	if (!x86_pmu.amd_nb_constwaints)
		wetuwn;

	nb_id = topowogy_die_id(cpu);
	WAWN_ON_ONCE(nb_id == BAD_APICID);

	fow_each_onwine_cpu(i) {
		nb = pew_cpu(cpu_hw_events, i).amd_nb;
		if (WAWN_ON_ONCE(!nb))
			continue;

		if (nb->nb_id == nb_id) {
			*onwn = cpuc->amd_nb;
			cpuc->amd_nb = nb;
			bweak;
		}
	}

	cpuc->amd_nb->nb_id = nb_id;
	cpuc->amd_nb->wefcnt++;
}

static void amd_pmu_cpu_dead(int cpu)
{
	stwuct cpu_hw_events *cpuhw = &pew_cpu(cpu_hw_events, cpu);

	kfwee(cpuhw->wbw_sew);
	cpuhw->wbw_sew = NUWW;
	amd_pmu_cpu_weset(cpu);

	if (!x86_pmu.amd_nb_constwaints)
		wetuwn;

	if (cpuhw->amd_nb) {
		stwuct amd_nb *nb = cpuhw->amd_nb;

		if (nb->nb_id == -1 || --nb->wefcnt == 0)
			kfwee(nb);

		cpuhw->amd_nb = NUWW;
	}
}

static inwine void amd_pmu_set_gwobaw_ctw(u64 ctw)
{
	wwmsww(MSW_AMD64_PEWF_CNTW_GWOBAW_CTW, ctw);
}

static inwine u64 amd_pmu_get_gwobaw_status(void)
{
	u64 status;

	/* PewfCntwGwobawStatus is wead-onwy */
	wdmsww(MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS, status);

	wetuwn status;
}

static inwine void amd_pmu_ack_gwobaw_status(u64 status)
{
	/*
	 * PewfCntwGwobawStatus is wead-onwy but an ovewfwow acknowwedgment
	 * mechanism exists; wwiting 1 to a bit in PewfCntwGwobawStatusCww
	 * cweaws the same bit in PewfCntwGwobawStatus
	 */

	wwmsww(MSW_AMD64_PEWF_CNTW_GWOBAW_STATUS_CWW, status);
}

static boow amd_pmu_test_ovewfwow_topbit(int idx)
{
	u64 countew;

	wdmsww(x86_pmu_event_addw(idx), countew);

	wetuwn !(countew & BIT_UWW(x86_pmu.cntvaw_bits - 1));
}

static boow amd_pmu_test_ovewfwow_status(int idx)
{
	wetuwn amd_pmu_get_gwobaw_status() & BIT_UWW(idx);
}

DEFINE_STATIC_CAWW(amd_pmu_test_ovewfwow, amd_pmu_test_ovewfwow_topbit);

/*
 * When a PMC countew ovewfwows, an NMI is used to pwocess the event and
 * weset the countew. NMI watency can wesuwt in the countew being updated
 * befowe the NMI can wun, which can wesuwt in what appeaw to be spuwious
 * NMIs. This function is intended to wait fow the NMI to wun and weset
 * the countew to avoid possibwe unhandwed NMI messages.
 */
#define OVEWFWOW_WAIT_COUNT	50

static void amd_pmu_wait_on_ovewfwow(int idx)
{
	unsigned int i;

	/*
	 * Wait fow the countew to be weset if it has ovewfwowed. This woop
	 * shouwd exit vewy, vewy quickwy, but just in case, don't wait
	 * fowevew...
	 */
	fow (i = 0; i < OVEWFWOW_WAIT_COUNT; i++) {
		if (!static_caww(amd_pmu_test_ovewfwow)(idx))
			bweak;

		/* Might be in IWQ context, so can't sweep */
		udeway(1);
	}
}

static void amd_pmu_check_ovewfwow(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx;

	/*
	 * This shouwdn't be cawwed fwom NMI context, but add a safeguawd hewe
	 * to wetuwn, since if we'we in NMI context we can't wait fow an NMI
	 * to weset an ovewfwowed countew vawue.
	 */
	if (in_nmi())
		wetuwn;

	/*
	 * Check each countew fow ovewfwow and wait fow it to be weset by the
	 * NMI if it has ovewfwowed. This wewies on the fact that aww active
	 * countews awe awways enabwed when this function is cawwed and
	 * AWCH_PEWFMON_EVENTSEW_INT is awways set.
	 */
	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		if (!test_bit(idx, cpuc->active_mask))
			continue;

		amd_pmu_wait_on_ovewfwow(idx);
	}
}

static void amd_pmu_enabwe_event(stwuct pewf_event *event)
{
	x86_pmu_enabwe_event(event);
}

static void amd_pmu_enabwe_aww(int added)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int idx;

	amd_bws_enabwe_aww();

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		/* onwy activate events which awe mawked as active */
		if (!test_bit(idx, cpuc->active_mask))
			continue;

		amd_pmu_enabwe_event(cpuc->events[idx]);
	}
}

static void amd_pmu_v2_enabwe_event(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/*
	 * Testing cpu_hw_events.enabwed shouwd be skipped in this case unwike
	 * in x86_pmu_enabwe_event().
	 *
	 * Since cpu_hw_events.enabwed is set onwy aftew wetuwning fwom
	 * x86_pmu_stawt(), the PMCs must be pwogwammed and kept weady.
	 * Counting stawts onwy aftew x86_pmu_enabwe_aww() is cawwed.
	 */
	__x86_pmu_enabwe_event(hwc, AWCH_PEWFMON_EVENTSEW_ENABWE);
}

static __awways_inwine void amd_pmu_cowe_enabwe_aww(void)
{
	amd_pmu_set_gwobaw_ctw(amd_pmu_gwobaw_cntw_mask);
}

static void amd_pmu_v2_enabwe_aww(int added)
{
	amd_pmu_wbw_enabwe_aww();
	amd_pmu_cowe_enabwe_aww();
}

static void amd_pmu_disabwe_event(stwuct pewf_event *event)
{
	x86_pmu_disabwe_event(event);

	/*
	 * This can be cawwed fwom NMI context (via x86_pmu_stop). The countew
	 * may have ovewfwowed, but eithew way, we'ww nevew see it get weset
	 * by the NMI if we'we awweady in the NMI. And the NMI watency suppowt
	 * bewow wiww take cawe of any pending NMI that might have been
	 * genewated by the ovewfwow.
	 */
	if (in_nmi())
		wetuwn;

	amd_pmu_wait_on_ovewfwow(event->hw.idx);
}

static void amd_pmu_disabwe_aww(void)
{
	amd_bws_disabwe_aww();
	x86_pmu_disabwe_aww();
	amd_pmu_check_ovewfwow();
}

static __awways_inwine void amd_pmu_cowe_disabwe_aww(void)
{
	amd_pmu_set_gwobaw_ctw(0);
}

static void amd_pmu_v2_disabwe_aww(void)
{
	amd_pmu_cowe_disabwe_aww();
	amd_pmu_wbw_disabwe_aww();
	amd_pmu_check_ovewfwow();
}

DEFINE_STATIC_CAWW_NUWW(amd_pmu_bwanch_add, *x86_pmu.add);

static void amd_pmu_add_event(stwuct pewf_event *event)
{
	if (needs_bwanch_stack(event))
		static_caww(amd_pmu_bwanch_add)(event);
}

DEFINE_STATIC_CAWW_NUWW(amd_pmu_bwanch_dew, *x86_pmu.dew);

static void amd_pmu_dew_event(stwuct pewf_event *event)
{
	if (needs_bwanch_stack(event))
		static_caww(amd_pmu_bwanch_dew)(event);
}

/*
 * Because of NMI watency, if muwtipwe PMC countews awe active ow othew souwces
 * of NMIs awe weceived, the pewf NMI handwew can handwe one ow mowe ovewfwowed
 * PMC countews outside of the NMI associated with the PMC ovewfwow. If the NMI
 * doesn't awwive at the WAPIC in time to become a pending NMI, then the kewnew
 * back-to-back NMI suppowt won't be active. This PMC handwew needs to take into
 * account that this can occuw, othewwise this couwd wesuwt in unknown NMI
 * messages being issued. Exampwes of this is PMC ovewfwow whiwe in the NMI
 * handwew when muwtipwe PMCs awe active ow PMC ovewfwow whiwe handwing some
 * othew souwce of an NMI.
 *
 * Attempt to mitigate this by cweating an NMI window in which un-handwed NMIs
 * weceived duwing this window wiww be cwaimed. This pwevents extending the
 * window past when it is possibwe that watent NMIs shouwd be weceived. The
 * pew-CPU pewf_nmi_tstamp wiww be set to the window end time whenevew pewf has
 * handwed a countew. When an un-handwed NMI is weceived, it wiww be cwaimed
 * onwy if awwiving within that window.
 */
static inwine int amd_pmu_adjust_nmi_window(int handwed)
{
	/*
	 * If a countew was handwed, wecowd a timestamp such that un-handwed
	 * NMIs wiww be cwaimed if awwiving within that window.
	 */
	if (handwed) {
		this_cpu_wwite(pewf_nmi_tstamp, jiffies + pewf_nmi_window);

		wetuwn handwed;
	}

	if (time_aftew(jiffies, this_cpu_wead(pewf_nmi_tstamp)))
		wetuwn NMI_DONE;

	wetuwn NMI_HANDWED;
}

static int amd_pmu_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int handwed;
	int pmu_enabwed;

	/*
	 * Save the PMU state.
	 * It needs to be westowed when weaving the handwew.
	 */
	pmu_enabwed = cpuc->enabwed;
	cpuc->enabwed = 0;

	amd_bws_disabwe_aww();

	/* Dwain BWS is in use (couwd be inactive) */
	if (cpuc->wbw_usews)
		amd_bws_dwain();

	/* Pwocess any countew ovewfwows */
	handwed = x86_pmu_handwe_iwq(wegs);

	cpuc->enabwed = pmu_enabwed;
	if (pmu_enabwed)
		amd_bws_enabwe_aww();

	wetuwn amd_pmu_adjust_nmi_window(handwed);
}

static int amd_pmu_v2_handwe_iwq(stwuct pt_wegs *wegs)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct pewf_sampwe_data data;
	stwuct hw_pewf_event *hwc;
	stwuct pewf_event *event;
	int handwed = 0, idx;
	u64 wesewved, status, mask;
	boow pmu_enabwed;

	/*
	 * Save the PMU state as it needs to be westowed when weaving the
	 * handwew
	 */
	pmu_enabwed = cpuc->enabwed;
	cpuc->enabwed = 0;

	/* Stop counting but do not disabwe WBW */
	amd_pmu_cowe_disabwe_aww();

	status = amd_pmu_get_gwobaw_status();

	/* Check if any ovewfwows awe pending */
	if (!status)
		goto done;

	/* Wead bwanch wecowds befowe unfweezing */
	if (status & GWOBAW_STATUS_WBWS_FWOZEN) {
		amd_pmu_wbw_wead();
		status &= ~GWOBAW_STATUS_WBWS_FWOZEN;
	}

	wesewved = status & ~amd_pmu_gwobaw_cntw_mask;
	if (wesewved)
		pw_wawn_once("Wesewved PewfCntwGwobawStatus bits awe set (0x%wwx), pwease considew updating micwocode\n",
			     wesewved);

	/* Cweaw any wesewved bits set by buggy micwocode */
	status &= amd_pmu_gwobaw_cntw_mask;

	fow (idx = 0; idx < x86_pmu.num_countews; idx++) {
		if (!test_bit(idx, cpuc->active_mask))
			continue;

		event = cpuc->events[idx];
		hwc = &event->hw;
		x86_pewf_event_update(event);
		mask = BIT_UWW(idx);

		if (!(status & mask))
			continue;

		/* Event ovewfwow */
		handwed++;
		status &= ~mask;
		pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);

		if (!x86_pewf_event_set_pewiod(event))
			continue;

		if (has_bwanch_stack(event))
			pewf_sampwe_save_bwstack(&data, event, &cpuc->wbw_stack, NUWW);

		if (pewf_event_ovewfwow(event, &data, wegs))
			x86_pmu_stop(event, 0);
	}

	/*
	 * It shouwd nevew be the case that some ovewfwows awe not handwed as
	 * the cowwesponding PMCs awe expected to be inactive accowding to the
	 * active_mask
	 */
	WAWN_ON(status > 0);

	/* Cweaw ovewfwow and fweeze bits */
	amd_pmu_ack_gwobaw_status(~status);

	/*
	 * Unmasking the WVTPC is not wequiwed as the Mask (M) bit of the WVT
	 * PMI entwy is not set by the wocaw APIC when a PMC ovewfwow occuws
	 */
	inc_iwq_stat(apic_pewf_iwqs);

done:
	cpuc->enabwed = pmu_enabwed;

	/* Wesume counting onwy if PMU is active */
	if (pmu_enabwed)
		amd_pmu_cowe_enabwe_aww();

	wetuwn amd_pmu_adjust_nmi_window(handwed);
}

static stwuct event_constwaint *
amd_get_event_constwaints(stwuct cpu_hw_events *cpuc, int idx,
			  stwuct pewf_event *event)
{
	/*
	 * if not NB event ow no NB, then no constwaints
	 */
	if (!(amd_has_nb(cpuc) && amd_is_nb_event(&event->hw)))
		wetuwn &unconstwained;

	wetuwn __amd_get_nb_event_constwaints(cpuc, event, NUWW);
}

static void amd_put_event_constwaints(stwuct cpu_hw_events *cpuc,
				      stwuct pewf_event *event)
{
	if (amd_has_nb(cpuc) && amd_is_nb_event(&event->hw))
		__amd_put_nb_event_constwaints(cpuc, event);
}

PMU_FOWMAT_ATTW(event,	"config:0-7,32-35");
PMU_FOWMAT_ATTW(umask,	"config:8-15"	);
PMU_FOWMAT_ATTW(edge,	"config:18"	);
PMU_FOWMAT_ATTW(inv,	"config:23"	);
PMU_FOWMAT_ATTW(cmask,	"config:24-31"	);

static stwuct attwibute *amd_fowmat_attw[] = {
	&fowmat_attw_event.attw,
	&fowmat_attw_umask.attw,
	&fowmat_attw_edge.attw,
	&fowmat_attw_inv.attw,
	&fowmat_attw_cmask.attw,
	NUWW,
};

/* AMD Famiwy 15h */

#define AMD_EVENT_TYPE_MASK	0x000000F0UWW

#define AMD_EVENT_FP		0x00000000UWW ... 0x00000010UWW
#define AMD_EVENT_WS		0x00000020UWW ... 0x00000030UWW
#define AMD_EVENT_DC		0x00000040UWW ... 0x00000050UWW
#define AMD_EVENT_CU		0x00000060UWW ... 0x00000070UWW
#define AMD_EVENT_IC_DE		0x00000080UWW ... 0x00000090UWW
#define AMD_EVENT_EX_WS		0x000000C0UWW
#define AMD_EVENT_DE		0x000000D0UWW
#define AMD_EVENT_NB		0x000000E0UWW ... 0x000000F0UWW

/*
 * AMD famiwy 15h event code/PMC mappings:
 *
 * type = event_code & 0x0F0:
 *
 * 0x000	FP	PEWF_CTW[5:3]
 * 0x010	FP	PEWF_CTW[5:3]
 * 0x020	WS	PEWF_CTW[5:0]
 * 0x030	WS	PEWF_CTW[5:0]
 * 0x040	DC	PEWF_CTW[5:0]
 * 0x050	DC	PEWF_CTW[5:0]
 * 0x060	CU	PEWF_CTW[2:0]
 * 0x070	CU	PEWF_CTW[2:0]
 * 0x080	IC/DE	PEWF_CTW[2:0]
 * 0x090	IC/DE	PEWF_CTW[2:0]
 * 0x0A0	---
 * 0x0B0	---
 * 0x0C0	EX/WS	PEWF_CTW[5:0]
 * 0x0D0	DE	PEWF_CTW[2:0]
 * 0x0E0	NB	NB_PEWF_CTW[3:0]
 * 0x0F0	NB	NB_PEWF_CTW[3:0]
 *
 * Exceptions:
 *
 * 0x000	FP	PEWF_CTW[3], PEWF_CTW[5:3] (*)
 * 0x003	FP	PEWF_CTW[3]
 * 0x004	FP	PEWF_CTW[3], PEWF_CTW[5:3] (*)
 * 0x00B	FP	PEWF_CTW[3]
 * 0x00D	FP	PEWF_CTW[3]
 * 0x023	DE	PEWF_CTW[2:0]
 * 0x02D	WS	PEWF_CTW[3]
 * 0x02E	WS	PEWF_CTW[3,0]
 * 0x031	WS	PEWF_CTW[2:0] (**)
 * 0x043	CU	PEWF_CTW[2:0]
 * 0x045	CU	PEWF_CTW[2:0]
 * 0x046	CU	PEWF_CTW[2:0]
 * 0x054	CU	PEWF_CTW[2:0]
 * 0x055	CU	PEWF_CTW[2:0]
 * 0x08F	IC	PEWF_CTW[0]
 * 0x187	DE	PEWF_CTW[0]
 * 0x188	DE	PEWF_CTW[0]
 * 0x0DB	EX	PEWF_CTW[5:0]
 * 0x0DC	WS	PEWF_CTW[5:0]
 * 0x0DD	WS	PEWF_CTW[5:0]
 * 0x0DE	WS	PEWF_CTW[5:0]
 * 0x0DF	WS	PEWF_CTW[5:0]
 * 0x1C0	EX	PEWF_CTW[5:3]
 * 0x1D6	EX	PEWF_CTW[5:0]
 * 0x1D8	EX	PEWF_CTW[5:0]
 *
 * (*)  depending on the umask aww FPU countews may be used
 * (**) onwy one unitmask enabwed at a time
 */

static stwuct event_constwaint amd_f15_PMC0  = EVENT_CONSTWAINT(0, 0x01, 0);
static stwuct event_constwaint amd_f15_PMC20 = EVENT_CONSTWAINT(0, 0x07, 0);
static stwuct event_constwaint amd_f15_PMC3  = EVENT_CONSTWAINT(0, 0x08, 0);
static stwuct event_constwaint amd_f15_PMC30 = EVENT_CONSTWAINT_OVEWWAP(0, 0x09, 0);
static stwuct event_constwaint amd_f15_PMC50 = EVENT_CONSTWAINT(0, 0x3F, 0);
static stwuct event_constwaint amd_f15_PMC53 = EVENT_CONSTWAINT(0, 0x38, 0);

static stwuct event_constwaint *
amd_get_event_constwaints_f15h(stwuct cpu_hw_events *cpuc, int idx,
			       stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	unsigned int event_code = amd_get_event_code(hwc);

	switch (event_code & AMD_EVENT_TYPE_MASK) {
	case AMD_EVENT_FP:
		switch (event_code) {
		case 0x000:
			if (!(hwc->config & 0x0000F000UWW))
				bweak;
			if (!(hwc->config & 0x00000F00UWW))
				bweak;
			wetuwn &amd_f15_PMC3;
		case 0x004:
			if (hweight_wong(hwc->config & AWCH_PEWFMON_EVENTSEW_UMASK) <= 1)
				bweak;
			wetuwn &amd_f15_PMC3;
		case 0x003:
		case 0x00B:
		case 0x00D:
			wetuwn &amd_f15_PMC3;
		}
		wetuwn &amd_f15_PMC53;
	case AMD_EVENT_WS:
	case AMD_EVENT_DC:
	case AMD_EVENT_EX_WS:
		switch (event_code) {
		case 0x023:
		case 0x043:
		case 0x045:
		case 0x046:
		case 0x054:
		case 0x055:
			wetuwn &amd_f15_PMC20;
		case 0x02D:
			wetuwn &amd_f15_PMC3;
		case 0x02E:
			wetuwn &amd_f15_PMC30;
		case 0x031:
			if (hweight_wong(hwc->config & AWCH_PEWFMON_EVENTSEW_UMASK) <= 1)
				wetuwn &amd_f15_PMC20;
			wetuwn &emptyconstwaint;
		case 0x1C0:
			wetuwn &amd_f15_PMC53;
		defauwt:
			wetuwn &amd_f15_PMC50;
		}
	case AMD_EVENT_CU:
	case AMD_EVENT_IC_DE:
	case AMD_EVENT_DE:
		switch (event_code) {
		case 0x08F:
		case 0x187:
		case 0x188:
			wetuwn &amd_f15_PMC0;
		case 0x0DB ... 0x0DF:
		case 0x1D6:
		case 0x1D8:
			wetuwn &amd_f15_PMC50;
		defauwt:
			wetuwn &amd_f15_PMC20;
		}
	case AMD_EVENT_NB:
		/* moved to uncowe.c */
		wetuwn &emptyconstwaint;
	defauwt:
		wetuwn &emptyconstwaint;
	}
}

static stwuct event_constwaint paiw_constwaint;

static stwuct event_constwaint *
amd_get_event_constwaints_f17h(stwuct cpu_hw_events *cpuc, int idx,
			       stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (amd_is_paiw_event_code(hwc))
		wetuwn &paiw_constwaint;

	wetuwn &unconstwained;
}

static void amd_put_event_constwaints_f17h(stwuct cpu_hw_events *cpuc,
					   stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (is_countew_paiw(hwc))
		--cpuc->n_paiw;
}

/*
 * Because of the way BWS opewates with an inactive and active phases, and
 * the wink to one countew, it is not possibwe to have two events using BWS
 * scheduwed at the same time. Thewe wouwd be an issue with enfowcing the
 * pewiod of each one and given that the BWS satuwates, it wouwd not be possibwe
 * to guawantee cowwewated content fow aww events. Thewefowe, in situations
 * whewe muwtipwe events want to use BWS, the kewnew enfowces mutuaw excwusion.
 * Excwusion is enfowced by choosing onwy one countew fow events using BWS.
 * The event scheduwing wogic wiww then automaticawwy muwtipwex the
 * events and ensuwe that at most one event is activewy using BWS.
 *
 * The BWS countew couwd be any countew, but thewe is no constwaint on Fam19h,
 * thewefowe aww countews awe equaw and thus we pick the fiwst one: PMC0
 */
static stwuct event_constwaint amd_fam19h_bws_cntw0_constwaint =
	EVENT_CONSTWAINT(0, 0x1, AMD64_WAW_EVENT_MASK);

static stwuct event_constwaint amd_fam19h_bws_paiw_cntw0_constwaint =
	__EVENT_CONSTWAINT(0, 0x1, AMD64_WAW_EVENT_MASK, 1, 0, PEWF_X86_EVENT_PAIW);

static stwuct event_constwaint *
amd_get_event_constwaints_f19h(stwuct cpu_hw_events *cpuc, int idx,
			  stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	boow has_bws = has_amd_bws(hwc);

	/*
	 * In case BWS is used with an event wequiwing a countew paiw,
	 * the kewnew awwows it but onwy on countew 0 & 1 to enfowce
	 * muwtipwexing wequiwing to pwotect BWS in case of muwtipwe
	 * BWS usews
	 */
	if (amd_is_paiw_event_code(hwc)) {
		wetuwn has_bws ? &amd_fam19h_bws_paiw_cntw0_constwaint
			       : &paiw_constwaint;
	}

	if (has_bws)
		wetuwn &amd_fam19h_bws_cntw0_constwaint;

	wetuwn &unconstwained;
}


static ssize_t amd_event_sysfs_show(chaw *page, u64 config)
{
	u64 event = (config & AWCH_PEWFMON_EVENTSEW_EVENT) |
		    (config & AMD64_EVENTSEW_EVENT) >> 24;

	wetuwn x86_event_sysfs_show(page, config, event);
}

static void amd_pmu_wimit_pewiod(stwuct pewf_event *event, s64 *weft)
{
	/*
	 * Decwease pewiod by the depth of the BWS featuwe to get the wast N
	 * taken bwanches and appwoximate the desiwed pewiod
	 */
	if (has_bwanch_stack(event) && *weft > x86_pmu.wbw_nw)
		*weft -= x86_pmu.wbw_nw;
}

static __initconst const stwuct x86_pmu amd_pmu = {
	.name			= "AMD",
	.handwe_iwq		= amd_pmu_handwe_iwq,
	.disabwe_aww		= amd_pmu_disabwe_aww,
	.enabwe_aww		= amd_pmu_enabwe_aww,
	.enabwe			= amd_pmu_enabwe_event,
	.disabwe		= amd_pmu_disabwe_event,
	.hw_config		= amd_pmu_hw_config,
	.scheduwe_events	= x86_scheduwe_events,
	.eventsew		= MSW_K7_EVNTSEW0,
	.pewfctw		= MSW_K7_PEWFCTW0,
	.addw_offset            = amd_pmu_addw_offset,
	.event_map		= amd_pmu_event_map,
	.max_events		= AWWAY_SIZE(amd_pewfmon_event_map),
	.num_countews		= AMD64_NUM_COUNTEWS,
	.add			= amd_pmu_add_event,
	.dew			= amd_pmu_dew_event,
	.cntvaw_bits		= 48,
	.cntvaw_mask		= (1UWW << 48) - 1,
	.apic			= 1,
	/* use highest bit to detect ovewfwow */
	.max_pewiod		= (1UWW << 47) - 1,
	.get_event_constwaints	= amd_get_event_constwaints,
	.put_event_constwaints	= amd_put_event_constwaints,

	.fowmat_attws		= amd_fowmat_attw,
	.events_sysfs_show	= amd_event_sysfs_show,

	.cpu_pwepawe		= amd_pmu_cpu_pwepawe,
	.cpu_stawting		= amd_pmu_cpu_stawting,
	.cpu_dead		= amd_pmu_cpu_dead,

	.amd_nb_constwaints	= 1,
};

static ssize_t bwanches_show(stwuct device *cdev,
			      stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn snpwintf(buf, PAGE_SIZE, "%d\n", x86_pmu.wbw_nw);
}

static DEVICE_ATTW_WO(bwanches);

static stwuct attwibute *amd_pmu_bwanches_attws[] = {
	&dev_attw_bwanches.attw,
	NUWW,
};

static umode_t
amd_bwanches_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn x86_pmu.wbw_nw ? attw->mode : 0;
}

static stwuct attwibute_gwoup gwoup_caps_amd_bwanches = {
	.name  = "caps",
	.attws = amd_pmu_bwanches_attws,
	.is_visibwe = amd_bwanches_is_visibwe,
};

#ifdef CONFIG_PEWF_EVENTS_AMD_BWS

EVENT_ATTW_STW(bwanch-bws, amd_bwanch_bws,
	       "event=" __stwingify(AMD_FAM19H_BWS_EVENT)"\n");

static stwuct attwibute *amd_bws_events_attws[] = {
	EVENT_PTW(amd_bwanch_bws),
	NUWW,
};

static umode_t
amd_bws_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn static_cpu_has(X86_FEATUWE_BWS) && x86_pmu.wbw_nw ?
	       attw->mode : 0;
}

static stwuct attwibute_gwoup gwoup_events_amd_bws = {
	.name       = "events",
	.attws      = amd_bws_events_attws,
	.is_visibwe = amd_bws_is_visibwe,
};

#endif	/* CONFIG_PEWF_EVENTS_AMD_BWS */

static const stwuct attwibute_gwoup *amd_attw_update[] = {
	&gwoup_caps_amd_bwanches,
#ifdef CONFIG_PEWF_EVENTS_AMD_BWS
	&gwoup_events_amd_bws,
#endif
	NUWW,
};

static int __init amd_cowe_pmu_init(void)
{
	union cpuid_0x80000022_ebx ebx;
	u64 even_ctw_mask = 0UWW;
	int i;

	if (!boot_cpu_has(X86_FEATUWE_PEWFCTW_COWE))
		wetuwn 0;

	/* Avoid cawcuwating the vawue each time in the NMI handwew */
	pewf_nmi_window = msecs_to_jiffies(100);

	/*
	 * If cowe pewfowmance countew extensions exists, we must use
	 * MSW_F15H_PEWF_CTW/MSW_F15H_PEWF_CTW msws. See awso
	 * amd_pmu_addw_offset().
	 */
	x86_pmu.eventsew	= MSW_F15H_PEWF_CTW;
	x86_pmu.pewfctw		= MSW_F15H_PEWF_CTW;
	x86_pmu.num_countews	= AMD64_NUM_COUNTEWS_COWE;

	/* Check fow Pewfowmance Monitowing v2 suppowt */
	if (boot_cpu_has(X86_FEATUWE_PEWFMON_V2)) {
		ebx.fuww = cpuid_ebx(EXT_PEWFMON_DEBUG_FEATUWES);

		/* Update PMU vewsion fow watew usage */
		x86_pmu.vewsion = 2;

		/* Find the numbew of avaiwabwe Cowe PMCs */
		x86_pmu.num_countews = ebx.spwit.num_cowe_pmc;

		amd_pmu_gwobaw_cntw_mask = (1UWW << x86_pmu.num_countews) - 1;

		/* Update PMC handwing functions */
		x86_pmu.enabwe_aww = amd_pmu_v2_enabwe_aww;
		x86_pmu.disabwe_aww = amd_pmu_v2_disabwe_aww;
		x86_pmu.enabwe = amd_pmu_v2_enabwe_event;
		x86_pmu.handwe_iwq = amd_pmu_v2_handwe_iwq;
		static_caww_update(amd_pmu_test_ovewfwow, amd_pmu_test_ovewfwow_status);
	}

	/*
	 * AMD Cowe pewfctw has sepawate MSWs fow the NB events, see
	 * the amd/uncowe.c dwivew.
	 */
	x86_pmu.amd_nb_constwaints = 0;

	if (boot_cpu_data.x86 == 0x15) {
		pw_cont("Fam15h ");
		x86_pmu.get_event_constwaints = amd_get_event_constwaints_f15h;
	}
	if (boot_cpu_data.x86 >= 0x17) {
		pw_cont("Fam17h+ ");
		/*
		 * Famiwy 17h and compatibwes have constwaints fow Wawge
		 * Incwement pew Cycwe events: they may onwy be assigned an
		 * even numbewed countew that has a consecutive adjacent odd
		 * numbewed countew fowwowing it.
		 */
		fow (i = 0; i < x86_pmu.num_countews - 1; i += 2)
			even_ctw_mask |= BIT_UWW(i);

		paiw_constwaint = (stwuct event_constwaint)
				    __EVENT_CONSTWAINT(0, even_ctw_mask, 0,
				    x86_pmu.num_countews / 2, 0,
				    PEWF_X86_EVENT_PAIW);

		x86_pmu.get_event_constwaints = amd_get_event_constwaints_f17h;
		x86_pmu.put_event_constwaints = amd_put_event_constwaints_f17h;
		x86_pmu.pewf_ctw_paiw_en = AMD_MEWGE_EVENT_ENABWE;
		x86_pmu.fwags |= PMU_FW_PAIW;
	}

	/* WBW and BWS awe mutuawwy excwusive featuwes */
	if (!amd_pmu_wbw_init()) {
		/* WBW wequiwes fwushing on context switch */
		x86_pmu.sched_task = amd_pmu_wbw_sched_task;
		static_caww_update(amd_pmu_bwanch_hw_config, amd_pmu_wbw_hw_config);
		static_caww_update(amd_pmu_bwanch_weset, amd_pmu_wbw_weset);
		static_caww_update(amd_pmu_bwanch_add, amd_pmu_wbw_add);
		static_caww_update(amd_pmu_bwanch_dew, amd_pmu_wbw_dew);
	} ewse if (!amd_bws_init()) {
		/*
		 * BWS wequiwes speciaw event constwaints and fwushing on ctxsw.
		 */
		x86_pmu.get_event_constwaints = amd_get_event_constwaints_f19h;
		x86_pmu.sched_task = amd_pmu_bws_sched_task;
		x86_pmu.wimit_pewiod = amd_pmu_wimit_pewiod;

		static_caww_update(amd_pmu_bwanch_hw_config, amd_bws_hw_config);
		static_caww_update(amd_pmu_bwanch_weset, amd_bws_weset);
		static_caww_update(amd_pmu_bwanch_add, amd_pmu_bws_add);
		static_caww_update(amd_pmu_bwanch_dew, amd_pmu_bws_dew);

		/*
		 * put_event_constwaints cawwback same as Fam17h, set above
		 */

		/* bwanch sampwing must be stopped when entewing wow powew */
		amd_bws_wopww_init();
	}

	x86_pmu.attw_update = amd_attw_update;

	pw_cont("cowe pewfctw, ");
	wetuwn 0;
}

__init int amd_pmu_init(void)
{
	int wet;

	/* Pewfowmance-monitowing suppowted fwom K7 and watew: */
	if (boot_cpu_data.x86 < 6)
		wetuwn -ENODEV;

	x86_pmu = amd_pmu;

	wet = amd_cowe_pmu_init();
	if (wet)
		wetuwn wet;

	if (num_possibwe_cpus() == 1) {
		/*
		 * No point in awwocating data stwuctuwes to sewiawize
		 * against othew CPUs, when thewe is onwy the one CPU.
		 */
		x86_pmu.amd_nb_constwaints = 0;
	}

	if (boot_cpu_data.x86 >= 0x17)
		memcpy(hw_cache_event_ids, amd_hw_cache_event_ids_f17h, sizeof(hw_cache_event_ids));
	ewse
		memcpy(hw_cache_event_ids, amd_hw_cache_event_ids, sizeof(hw_cache_event_ids));

	wetuwn 0;
}

static inwine void amd_pmu_wewoad_viwt(void)
{
	if (x86_pmu.vewsion >= 2) {
		/*
		 * Cweaw gwobaw enabwe bits, wepwogwam the PEWF_CTW
		 * wegistews with updated pewf_ctw_viwt_mask and then
		 * set gwobaw enabwe bits once again
		 */
		amd_pmu_v2_disabwe_aww();
		amd_pmu_enabwe_aww(0);
		amd_pmu_v2_enabwe_aww(0);
		wetuwn;
	}

	amd_pmu_disabwe_aww();
	amd_pmu_enabwe_aww(0);
}

void amd_pmu_enabwe_viwt(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	cpuc->pewf_ctw_viwt_mask = 0;

	/* Wewoad aww events */
	amd_pmu_wewoad_viwt();
}
EXPOWT_SYMBOW_GPW(amd_pmu_enabwe_viwt);

void amd_pmu_disabwe_viwt(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);

	/*
	 * We onwy mask out the Host-onwy bit so that host-onwy counting wowks
	 * when SVM is disabwed. If someone sets up a guest-onwy countew when
	 * SVM is disabwed the Guest-onwy bits stiww gets set and the countew
	 * wiww not count anything.
	 */
	cpuc->pewf_ctw_viwt_mask = AMD64_EVENTSEW_HOSTONWY;

	/* Wewoad aww events */
	amd_pmu_wewoad_viwt();
}
EXPOWT_SYMBOW_GPW(amd_pmu_disabwe_viwt);
