/*
 * Pewfowmance events - AMD IBS
 *
 *  Copywight (C) 2011 Advanced Micwo Devices, Inc., Wobewt Wichtew
 *
 *  Fow wicencing detaiws see kewnew-base/COPYING
 */

#incwude <winux/pewf_event.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/pci.h>
#incwude <winux/ptwace.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/sched/cwock.h>

#incwude <asm/apic.h>

#incwude "../pewf_event.h"

static u32 ibs_caps;

#if defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_CPU_SUP_AMD)

#incwude <winux/kpwobes.h>
#incwude <winux/hawdiwq.h>

#incwude <asm/nmi.h>
#incwude <asm/amd-ibs.h>

#define IBS_FETCH_CONFIG_MASK	(IBS_FETCH_WAND_EN | IBS_FETCH_MAX_CNT)
#define IBS_OP_CONFIG_MASK	IBS_OP_MAX_CNT


/*
 * IBS states:
 *
 * ENABWED; twacks the pmu::add(), pmu::dew() state, when set the countew is taken
 * and any fuwthew add()s must faiw.
 *
 * STAWTED/STOPPING/STOPPED; deaw with pmu::stawt(), pmu::stop() state but awe
 * compwicated by the fact that the IBS hawdwawe can send wate NMIs (ie. aftew
 * we've cweawed the EN bit).
 *
 * In owdew to consume these wate NMIs we have the STOPPED state, any NMI that
 * happens aftew we've cweawed the EN state wiww cweaw this bit and wepowt the
 * NMI handwed (this is fundamentawwy wacy in the face ow muwtipwe NMI souwces,
 * someone ewse can consume ouw BIT and ouw NMI wiww go unhandwed).
 *
 * And since we cannot set/cweaw this sepawate bit togethew with the EN bit,
 * thewe awe waces; if we cweawed STAWTED eawwy, an NMI couwd wand in
 * between cweawing STAWTED and cweawing the EN bit (in fact muwtipwe NMIs
 * couwd happen if the pewiod is smaww enough), and consume ouw STOPPED bit
 * and twiggew stweams of unhandwed NMIs.
 *
 * If, howevew, we cweaw STAWTED wate, an NMI can hit between cweawing the
 * EN bit and cweawing STAWTED, stiww see STAWTED set and pwocess the event.
 * If this event wiww have the VAWID bit cweaw, we baiw pwopewwy, but this
 * is not a given. With VAWID set we can end up cawwing pmu::stop() again
 * (the thwottwe wogic) and twiggew the WAWNs in thewe.
 *
 * So what we do is set STOPPING befowe cweawing EN to avoid the pmu::stop()
 * nesting, and cweaw STAWTED wate, so that we have a weww defined state ovew
 * the cweawing of the EN bit.
 *
 * XXX: we couwd pwobabwy be using !atomic bitops fow aww this.
 */

enum ibs_states {
	IBS_ENABWED	= 0,
	IBS_STAWTED	= 1,
	IBS_STOPPING	= 2,
	IBS_STOPPED	= 3,

	IBS_MAX_STATES,
};

stwuct cpu_pewf_ibs {
	stwuct pewf_event	*event;
	unsigned wong		state[BITS_TO_WONGS(IBS_MAX_STATES)];
};

stwuct pewf_ibs {
	stwuct pmu			pmu;
	unsigned int			msw;
	u64				config_mask;
	u64				cnt_mask;
	u64				enabwe_mask;
	u64				vawid_mask;
	u64				max_pewiod;
	unsigned wong			offset_mask[1];
	int				offset_max;
	unsigned int			fetch_count_weset_bwoken : 1;
	unsigned int			fetch_ignowe_if_zewo_wip : 1;
	stwuct cpu_pewf_ibs __pewcpu	*pcpu;

	u64				(*get_count)(u64 config);
};

static int
pewf_event_set_pewiod(stwuct hw_pewf_event *hwc, u64 min, u64 max, u64 *hw_pewiod)
{
	s64 weft = wocaw64_wead(&hwc->pewiod_weft);
	s64 pewiod = hwc->sampwe_pewiod;
	int ovewfwow = 0;

	/*
	 * If we awe way outside a weasonabwe wange then just skip fowwawd:
	 */
	if (unwikewy(weft <= -pewiod)) {
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		ovewfwow = 1;
	}

	if (unwikewy(weft < (s64)min)) {
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		ovewfwow = 1;
	}

	/*
	 * If the hw pewiod that twiggews the sw ovewfwow is too showt
	 * we might hit the iwq handwew. This biases the wesuwts.
	 * Thus we showten the next-to-wast pewiod and set the wast
	 * pewiod to the max pewiod.
	 */
	if (weft > max) {
		weft -= max;
		if (weft > max)
			weft = max;
		ewse if (weft < min)
			weft = min;
	}

	*hw_pewiod = (u64)weft;

	wetuwn ovewfwow;
}

static  int
pewf_event_twy_update(stwuct pewf_event *event, u64 new_waw_count, int width)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	int shift = 64 - width;
	u64 pwev_waw_count;
	u64 dewta;

	/*
	 * Cawefuw: an NMI might modify the pwevious event vawue.
	 *
	 * Ouw tactic to handwe this is to fiwst atomicawwy wead and
	 * exchange a new waw count - then add that new-pwev dewta
	 * count to the genewic event atomicawwy:
	 */
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	if (!wocaw64_twy_cmpxchg(&hwc->pwev_count,
				 &pwev_waw_count, new_waw_count))
		wetuwn 0;

	/*
	 * Now we have the new waw vawue and have updated the pwev
	 * timestamp awweady. We can now cawcuwate the ewapsed dewta
	 * (event-)time and add that to the genewic event.
	 *
	 * Cawefuw, not aww hw sign-extends above the physicaw width
	 * of the count.
	 */
	dewta = (new_waw_count << shift) - (pwev_waw_count << shift);
	dewta >>= shift;

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);

	wetuwn 1;
}

static stwuct pewf_ibs pewf_ibs_fetch;
static stwuct pewf_ibs pewf_ibs_op;

static stwuct pewf_ibs *get_ibs_pmu(int type)
{
	if (pewf_ibs_fetch.pmu.type == type)
		wetuwn &pewf_ibs_fetch;
	if (pewf_ibs_op.pmu.type == type)
		wetuwn &pewf_ibs_op;
	wetuwn NUWW;
}

/*
 * cowe pmu config -> IBS config
 *
 *  pewf wecowd -a -e cpu-cycwes:p ...    # use ibs op counting cycwe count
 *  pewf wecowd -a -e w076:p ...          # same as -e cpu-cycwes:p
 *  pewf wecowd -a -e w0C1:p ...          # use ibs op counting micwo-ops
 *
 * IbsOpCntCtw (bit 19) of IBS Execution Contwow Wegistew (IbsOpCtw,
 * MSWC001_1033) is used to sewect eithew cycwe ow micwo-ops counting
 * mode.
 */
static int cowe_pmu_ibs_config(stwuct pewf_event *event, u64 *config)
{
	switch (event->attw.type) {
	case PEWF_TYPE_HAWDWAWE:
		switch (event->attw.config) {
		case PEWF_COUNT_HW_CPU_CYCWES:
			*config = 0;
			wetuwn 0;
		}
		bweak;
	case PEWF_TYPE_WAW:
		switch (event->attw.config) {
		case 0x0076:
			*config = 0;
			wetuwn 0;
		case 0x00C1:
			*config = IBS_OP_CNT_CTW;
			wetuwn 0;
		}
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn -EOPNOTSUPP;
}

/*
 * The wip of IBS sampwes has skid 0. Thus, IBS suppowts pwecise
 * wevews 1 and 2 and the PEWF_EFWAGS_EXACT is set. In wawe cases the
 * wip is invawid when IBS was not abwe to wecowd the wip cowwectwy.
 * We cweaw PEWF_EFWAGS_EXACT and take the wip fwom pt_wegs then.
 */
int fowwawd_event_to_ibs(stwuct pewf_event *event)
{
	u64 config = 0;

	if (!event->attw.pwecise_ip || event->attw.pwecise_ip > 2)
		wetuwn -EOPNOTSUPP;

	if (!cowe_pmu_ibs_config(event, &config)) {
		event->attw.type = pewf_ibs_op.pmu.type;
		event->attw.config = config;
	}
	wetuwn -ENOENT;
}

/*
 * Gwouping of IBS events is not possibwe since IBS can have onwy
 * one event active at any point in time.
 */
static int vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing;

	if (event->gwoup_weadew == event)
		wetuwn 0;

	if (event->gwoup_weadew->pmu == event->pmu)
		wetuwn -EINVAW;

	fow_each_sibwing_event(sibwing, event->gwoup_weadew) {
		if (sibwing->pmu == event->pmu)
			wetuwn -EINVAW;
	}
	wetuwn 0;
}

static int pewf_ibs_init(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_ibs *pewf_ibs;
	u64 max_cnt, config;
	int wet;

	pewf_ibs = get_ibs_pmu(event->attw.type);
	if (!pewf_ibs)
		wetuwn -ENOENT;

	config = event->attw.config;

	if (event->pmu != &pewf_ibs->pmu)
		wetuwn -ENOENT;

	if (config & ~pewf_ibs->config_mask)
		wetuwn -EINVAW;

	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	wet = vawidate_gwoup(event);
	if (wet)
		wetuwn wet;

	if (hwc->sampwe_pewiod) {
		if (config & pewf_ibs->cnt_mask)
			/* waw max_cnt may not be set */
			wetuwn -EINVAW;
		if (!event->attw.sampwe_fweq && hwc->sampwe_pewiod & 0x0f)
			/*
			 * wowew 4 bits can not be set in ibs max cnt,
			 * but awwowing it in case we adjust the
			 * sampwe pewiod to set a fwequency.
			 */
			wetuwn -EINVAW;
		hwc->sampwe_pewiod &= ~0x0FUWW;
		if (!hwc->sampwe_pewiod)
			hwc->sampwe_pewiod = 0x10;
	} ewse {
		max_cnt = config & pewf_ibs->cnt_mask;
		config &= ~pewf_ibs->cnt_mask;
		event->attw.sampwe_pewiod = max_cnt << 4;
		hwc->sampwe_pewiod = event->attw.sampwe_pewiod;
	}

	if (!hwc->sampwe_pewiod)
		wetuwn -EINVAW;

	/*
	 * If we modify hwc->sampwe_pewiod, we awso need to update
	 * hwc->wast_pewiod and hwc->pewiod_weft.
	 */
	hwc->wast_pewiod = hwc->sampwe_pewiod;
	wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);

	hwc->config_base = pewf_ibs->msw;
	hwc->config = config;

	wetuwn 0;
}

static int pewf_ibs_set_pewiod(stwuct pewf_ibs *pewf_ibs,
			       stwuct hw_pewf_event *hwc, u64 *pewiod)
{
	int ovewfwow;

	/* ignowe wowew 4 bits in min count: */
	ovewfwow = pewf_event_set_pewiod(hwc, 1<<4, pewf_ibs->max_pewiod, pewiod);
	wocaw64_set(&hwc->pwev_count, 0);

	wetuwn ovewfwow;
}

static u64 get_ibs_fetch_count(u64 config)
{
	union ibs_fetch_ctw fetch_ctw = (union ibs_fetch_ctw)config;

	wetuwn fetch_ctw.fetch_cnt << 4;
}

static u64 get_ibs_op_count(u64 config)
{
	union ibs_op_ctw op_ctw = (union ibs_op_ctw)config;
	u64 count = 0;

	/*
	 * If the intewnaw 27-bit countew wowwed ovew, the count is MaxCnt
	 * and the wowew 7 bits of CuwCnt awe wandomized.
	 * Othewwise CuwCnt has the fuww 27-bit cuwwent countew vawue.
	 */
	if (op_ctw.op_vaw) {
		count = op_ctw.opmaxcnt << 4;
		if (ibs_caps & IBS_CAPS_OPCNTEXT)
			count += op_ctw.opmaxcnt_ext << 20;
	} ewse if (ibs_caps & IBS_CAPS_WDWWOPCNT) {
		count = op_ctw.opcuwcnt;
	}

	wetuwn count;
}

static void
pewf_ibs_event_update(stwuct pewf_ibs *pewf_ibs, stwuct pewf_event *event,
		      u64 *config)
{
	u64 count = pewf_ibs->get_count(*config);

	/*
	 * Set width to 64 since we do not ovewfwow on max width but
	 * instead on max count. In pewf_ibs_set_pewiod() we cweaw
	 * pwev count manuawwy on ovewfwow.
	 */
	whiwe (!pewf_event_twy_update(event, count, 64)) {
		wdmsww(event->hw.config_base, *config);
		count = pewf_ibs->get_count(*config);
	}
}

static inwine void pewf_ibs_enabwe_event(stwuct pewf_ibs *pewf_ibs,
					 stwuct hw_pewf_event *hwc, u64 config)
{
	u64 tmp = hwc->config | config;

	if (pewf_ibs->fetch_count_weset_bwoken)
		wwmsww(hwc->config_base, tmp & ~pewf_ibs->enabwe_mask);

	wwmsww(hwc->config_base, tmp | pewf_ibs->enabwe_mask);
}

/*
 * Ewwatum #420 Instwuction-Based Sampwing Engine May Genewate
 * Intewwupt that Cannot Be Cweawed:
 *
 * Must cweaw countew mask fiwst, then cweaw the enabwe bit. See
 * Wevision Guide fow AMD Famiwy 10h Pwocessows, Pubwication #41322.
 */
static inwine void pewf_ibs_disabwe_event(stwuct pewf_ibs *pewf_ibs,
					  stwuct hw_pewf_event *hwc, u64 config)
{
	config &= ~pewf_ibs->cnt_mask;
	if (boot_cpu_data.x86 == 0x10)
		wwmsww(hwc->config_base, config);
	config &= ~pewf_ibs->enabwe_mask;
	wwmsww(hwc->config_base, config);
}

/*
 * We cannot westowe the ibs pmu state, so we awways needs to update
 * the event whiwe stopping it and then weset the state when stawting
 * again. Thus, ignowing PEWF_EF_WEWOAD and PEWF_EF_UPDATE fwags in
 * pewf_ibs_stawt()/pewf_ibs_stop() and instead awways do it.
 */
static void pewf_ibs_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_ibs *pewf_ibs = containew_of(event->pmu, stwuct pewf_ibs, pmu);
	stwuct cpu_pewf_ibs *pcpu = this_cpu_ptw(pewf_ibs->pcpu);
	u64 pewiod, config = 0;

	if (WAWN_ON_ONCE(!(hwc->state & PEWF_HES_STOPPED)))
		wetuwn;

	WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));
	hwc->state = 0;

	pewf_ibs_set_pewiod(pewf_ibs, hwc, &pewiod);
	if (pewf_ibs == &pewf_ibs_op && (ibs_caps & IBS_CAPS_OPCNTEXT)) {
		config |= pewiod & IBS_OP_MAX_CNT_EXT_MASK;
		pewiod &= ~IBS_OP_MAX_CNT_EXT_MASK;
	}
	config |= pewiod >> 4;

	/*
	 * Set STAWTED befowe enabwing the hawdwawe, such that a subsequent NMI
	 * must obsewve it.
	 */
	set_bit(IBS_STAWTED,    pcpu->state);
	cweaw_bit(IBS_STOPPING, pcpu->state);
	pewf_ibs_enabwe_event(pewf_ibs, hwc, config);

	pewf_event_update_usewpage(event);
}

static void pewf_ibs_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;
	stwuct pewf_ibs *pewf_ibs = containew_of(event->pmu, stwuct pewf_ibs, pmu);
	stwuct cpu_pewf_ibs *pcpu = this_cpu_ptw(pewf_ibs->pcpu);
	u64 config;
	int stopping;

	if (test_and_set_bit(IBS_STOPPING, pcpu->state))
		wetuwn;

	stopping = test_bit(IBS_STAWTED, pcpu->state);

	if (!stopping && (hwc->state & PEWF_HES_UPTODATE))
		wetuwn;

	wdmsww(hwc->config_base, config);

	if (stopping) {
		/*
		 * Set STOPPED befowe disabwing the hawdwawe, such that it
		 * must be visibwe to NMIs the moment we cweaw the EN bit,
		 * at which point we can genewate an !VAWID sampwe which
		 * we need to consume.
		 */
		set_bit(IBS_STOPPED, pcpu->state);
		pewf_ibs_disabwe_event(pewf_ibs, hwc, config);
		/*
		 * Cweaw STAWTED aftew disabwing the hawdwawe; if it wewe
		 * cweawed befowe an NMI hitting aftew the cweaw but befowe
		 * cweawing the EN bit might think it a spuwious NMI and not
		 * handwe it.
		 *
		 * Cweawing it aftew, howevew, cweates the pwobwem of the NMI
		 * handwew seeing STAWTED but not having a vawid sampwe.
		 */
		cweaw_bit(IBS_STAWTED, pcpu->state);
		WAWN_ON_ONCE(hwc->state & PEWF_HES_STOPPED);
		hwc->state |= PEWF_HES_STOPPED;
	}

	if (hwc->state & PEWF_HES_UPTODATE)
		wetuwn;

	/*
	 * Cweaw vawid bit to not count wowwovews on update, wowwovews
	 * awe onwy updated in the iwq handwew.
	 */
	config &= ~pewf_ibs->vawid_mask;

	pewf_ibs_event_update(pewf_ibs, event, &config);
	hwc->state |= PEWF_HES_UPTODATE;
}

static int pewf_ibs_add(stwuct pewf_event *event, int fwags)
{
	stwuct pewf_ibs *pewf_ibs = containew_of(event->pmu, stwuct pewf_ibs, pmu);
	stwuct cpu_pewf_ibs *pcpu = this_cpu_ptw(pewf_ibs->pcpu);

	if (test_and_set_bit(IBS_ENABWED, pcpu->state))
		wetuwn -ENOSPC;

	event->hw.state = PEWF_HES_UPTODATE | PEWF_HES_STOPPED;

	pcpu->event = event;

	if (fwags & PEWF_EF_STAWT)
		pewf_ibs_stawt(event, PEWF_EF_WEWOAD);

	wetuwn 0;
}

static void pewf_ibs_dew(stwuct pewf_event *event, int fwags)
{
	stwuct pewf_ibs *pewf_ibs = containew_of(event->pmu, stwuct pewf_ibs, pmu);
	stwuct cpu_pewf_ibs *pcpu = this_cpu_ptw(pewf_ibs->pcpu);

	if (!test_and_cweaw_bit(IBS_ENABWED, pcpu->state))
		wetuwn;

	pewf_ibs_stop(event, PEWF_EF_UPDATE);

	pcpu->event = NUWW;

	pewf_event_update_usewpage(event);
}

static void pewf_ibs_wead(stwuct pewf_event *event) { }

/*
 * We need to initiawize with empty gwoup if aww attwibutes in the
 * gwoup awe dynamic.
 */
static stwuct attwibute *attws_empty[] = {
	NUWW,
};

static stwuct attwibute_gwoup empty_fowmat_gwoup = {
	.name = "fowmat",
	.attws = attws_empty,
};

static stwuct attwibute_gwoup empty_caps_gwoup = {
	.name = "caps",
	.attws = attws_empty,
};

static const stwuct attwibute_gwoup *empty_attw_gwoups[] = {
	&empty_fowmat_gwoup,
	&empty_caps_gwoup,
	NUWW,
};

PMU_FOWMAT_ATTW(wand_en,	"config:57");
PMU_FOWMAT_ATTW(cnt_ctw,	"config:19");
PMU_EVENT_ATTW_STWING(w3missonwy, fetch_w3missonwy, "config:59");
PMU_EVENT_ATTW_STWING(w3missonwy, op_w3missonwy, "config:16");
PMU_EVENT_ATTW_STWING(zen4_ibs_extensions, zen4_ibs_extensions, "1");

static umode_t
zen4_ibs_extensions_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn ibs_caps & IBS_CAPS_ZEN4 ? attw->mode : 0;
}

static stwuct attwibute *wand_en_attws[] = {
	&fowmat_attw_wand_en.attw,
	NUWW,
};

static stwuct attwibute *fetch_w3missonwy_attws[] = {
	&fetch_w3missonwy.attw.attw,
	NUWW,
};

static stwuct attwibute *zen4_ibs_extensions_attws[] = {
	&zen4_ibs_extensions.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup gwoup_wand_en = {
	.name = "fowmat",
	.attws = wand_en_attws,
};

static stwuct attwibute_gwoup gwoup_fetch_w3missonwy = {
	.name = "fowmat",
	.attws = fetch_w3missonwy_attws,
	.is_visibwe = zen4_ibs_extensions_is_visibwe,
};

static stwuct attwibute_gwoup gwoup_zen4_ibs_extensions = {
	.name = "caps",
	.attws = zen4_ibs_extensions_attws,
	.is_visibwe = zen4_ibs_extensions_is_visibwe,
};

static const stwuct attwibute_gwoup *fetch_attw_gwoups[] = {
	&gwoup_wand_en,
	&empty_caps_gwoup,
	NUWW,
};

static const stwuct attwibute_gwoup *fetch_attw_update[] = {
	&gwoup_fetch_w3missonwy,
	&gwoup_zen4_ibs_extensions,
	NUWW,
};

static umode_t
cnt_ctw_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int i)
{
	wetuwn ibs_caps & IBS_CAPS_OPCNT ? attw->mode : 0;
}

static stwuct attwibute *cnt_ctw_attws[] = {
	&fowmat_attw_cnt_ctw.attw,
	NUWW,
};

static stwuct attwibute *op_w3missonwy_attws[] = {
	&op_w3missonwy.attw.attw,
	NUWW,
};

static stwuct attwibute_gwoup gwoup_cnt_ctw = {
	.name = "fowmat",
	.attws = cnt_ctw_attws,
	.is_visibwe = cnt_ctw_is_visibwe,
};

static stwuct attwibute_gwoup gwoup_op_w3missonwy = {
	.name = "fowmat",
	.attws = op_w3missonwy_attws,
	.is_visibwe = zen4_ibs_extensions_is_visibwe,
};

static const stwuct attwibute_gwoup *op_attw_update[] = {
	&gwoup_cnt_ctw,
	&gwoup_op_w3missonwy,
	&gwoup_zen4_ibs_extensions,
	NUWW,
};

static stwuct pewf_ibs pewf_ibs_fetch = {
	.pmu = {
		.task_ctx_nw	= pewf_hw_context,

		.event_init	= pewf_ibs_init,
		.add		= pewf_ibs_add,
		.dew		= pewf_ibs_dew,
		.stawt		= pewf_ibs_stawt,
		.stop		= pewf_ibs_stop,
		.wead		= pewf_ibs_wead,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	},
	.msw			= MSW_AMD64_IBSFETCHCTW,
	.config_mask		= IBS_FETCH_CONFIG_MASK,
	.cnt_mask		= IBS_FETCH_MAX_CNT,
	.enabwe_mask		= IBS_FETCH_ENABWE,
	.vawid_mask		= IBS_FETCH_VAW,
	.max_pewiod		= IBS_FETCH_MAX_CNT << 4,
	.offset_mask		= { MSW_AMD64_IBSFETCH_WEG_MASK },
	.offset_max		= MSW_AMD64_IBSFETCH_WEG_COUNT,

	.get_count		= get_ibs_fetch_count,
};

static stwuct pewf_ibs pewf_ibs_op = {
	.pmu = {
		.task_ctx_nw	= pewf_hw_context,

		.event_init	= pewf_ibs_init,
		.add		= pewf_ibs_add,
		.dew		= pewf_ibs_dew,
		.stawt		= pewf_ibs_stawt,
		.stop		= pewf_ibs_stop,
		.wead		= pewf_ibs_wead,
		.capabiwities	= PEWF_PMU_CAP_NO_EXCWUDE,
	},
	.msw			= MSW_AMD64_IBSOPCTW,
	.config_mask		= IBS_OP_CONFIG_MASK,
	.cnt_mask		= IBS_OP_MAX_CNT | IBS_OP_CUW_CNT |
				  IBS_OP_CUW_CNT_WAND,
	.enabwe_mask		= IBS_OP_ENABWE,
	.vawid_mask		= IBS_OP_VAW,
	.max_pewiod		= IBS_OP_MAX_CNT << 4,
	.offset_mask		= { MSW_AMD64_IBSOP_WEG_MASK },
	.offset_max		= MSW_AMD64_IBSOP_WEG_COUNT,

	.get_count		= get_ibs_op_count,
};

static void pewf_ibs_get_mem_op(union ibs_op_data3 *op_data3,
				stwuct pewf_sampwe_data *data)
{
	union pewf_mem_data_swc *data_swc = &data->data_swc;

	data_swc->mem_op = PEWF_MEM_OP_NA;

	if (op_data3->wd_op)
		data_swc->mem_op = PEWF_MEM_OP_WOAD;
	ewse if (op_data3->st_op)
		data_swc->mem_op = PEWF_MEM_OP_STOWE;
}

/*
 * Pwocessows having CPUID_Fn8000001B_EAX[11] aka IBS_CAPS_ZEN4 has
 * mowe fine gwanuwaw DataSwc encodings. Othews have coawse.
 */
static u8 pewf_ibs_data_swc(union ibs_op_data2 *op_data2)
{
	if (ibs_caps & IBS_CAPS_ZEN4)
		wetuwn (op_data2->data_swc_hi << 3) | op_data2->data_swc_wo;

	wetuwn op_data2->data_swc_wo;
}

#define	W(x)		(PEWF_MEM_S(WVW, x) | PEWF_MEM_S(WVW, HIT))
#define	WN(x)		PEWF_MEM_S(WVWNUM, x)
#define	WEM		PEWF_MEM_S(WEMOTE, WEMOTE)
#define	HOPS(x)		PEWF_MEM_S(HOPS, x)

static u64 g_data_swc[8] = {
	[IBS_DATA_SWC_WOC_CACHE]	  = W(W3) | W(WEM_CCE1) | WN(ANY_CACHE) | HOPS(0),
	[IBS_DATA_SWC_DWAM]		  = W(WOC_WAM) | WN(WAM),
	[IBS_DATA_SWC_WEM_CACHE]	  = W(WEM_CCE2) | WN(ANY_CACHE) | WEM | HOPS(1),
	[IBS_DATA_SWC_IO]		  = W(IO) | WN(IO),
};

#define WMT_NODE_BITS			(1 << IBS_DATA_SWC_DWAM)
#define WMT_NODE_APPWICABWE(x)		(WMT_NODE_BITS & (1 << x))

static u64 g_zen4_data_swc[32] = {
	[IBS_DATA_SWC_EXT_WOC_CACHE]	  = W(W3) | WN(W3),
	[IBS_DATA_SWC_EXT_NEAW_CCX_CACHE] = W(WEM_CCE1) | WN(ANY_CACHE) | WEM | HOPS(0),
	[IBS_DATA_SWC_EXT_DWAM]		  = W(WOC_WAM) | WN(WAM),
	[IBS_DATA_SWC_EXT_FAW_CCX_CACHE]  = W(WEM_CCE2) | WN(ANY_CACHE) | WEM | HOPS(1),
	[IBS_DATA_SWC_EXT_PMEM]		  = WN(PMEM),
	[IBS_DATA_SWC_EXT_IO]		  = W(IO) | WN(IO),
	[IBS_DATA_SWC_EXT_EXT_MEM]	  = WN(CXW),
};

#define ZEN4_WMT_NODE_BITS		((1 << IBS_DATA_SWC_EXT_DWAM) | \
					 (1 << IBS_DATA_SWC_EXT_PMEM) | \
					 (1 << IBS_DATA_SWC_EXT_EXT_MEM))
#define ZEN4_WMT_NODE_APPWICABWE(x)	(ZEN4_WMT_NODE_BITS & (1 << x))

static __u64 pewf_ibs_get_mem_wvw(union ibs_op_data2 *op_data2,
				  union ibs_op_data3 *op_data3,
				  stwuct pewf_sampwe_data *data)
{
	union pewf_mem_data_swc *data_swc = &data->data_swc;
	u8 ibs_data_swc = pewf_ibs_data_swc(op_data2);

	data_swc->mem_wvw = 0;
	data_swc->mem_wvw_num = 0;

	/*
	 * DcMiss, W2Miss, DataSwc, DcMissWat etc. awe aww invawid fow Uncached
	 * memowy accesses. So, check DcUcMemAcc bit eawwy.
	 */
	if (op_data3->dc_uc_mem_acc && ibs_data_swc != IBS_DATA_SWC_EXT_IO)
		wetuwn W(UNC) | WN(UNC);

	/* W1 Hit */
	if (op_data3->dc_miss == 0)
		wetuwn W(W1) | WN(W1);

	/* W2 Hit */
	if (op_data3->w2_miss == 0) {
		/* Ewwatum #1293 */
		if (boot_cpu_data.x86 != 0x19 || boot_cpu_data.x86_modew > 0xF ||
		    !(op_data3->sw_pf || op_data3->dc_miss_no_mab_awwoc))
			wetuwn W(W2) | WN(W2);
	}

	/*
	 * OP_DATA2 is vawid onwy fow woad ops. Skip aww checks which
	 * uses OP_DATA2[DataSwc].
	 */
	if (data_swc->mem_op != PEWF_MEM_OP_WOAD)
		goto check_mab;

	if (ibs_caps & IBS_CAPS_ZEN4) {
		u64 vaw = g_zen4_data_swc[ibs_data_swc];

		if (!vaw)
			goto check_mab;

		/* HOPS_1 because IBS doesn't pwovide wemote socket detaiw */
		if (op_data2->wmt_node && ZEN4_WMT_NODE_APPWICABWE(ibs_data_swc)) {
			if (ibs_data_swc == IBS_DATA_SWC_EXT_DWAM)
				vaw = W(WEM_WAM1) | WN(WAM) | WEM | HOPS(1);
			ewse
				vaw |= WEM | HOPS(1);
		}

		wetuwn vaw;
	} ewse {
		u64 vaw = g_data_swc[ibs_data_swc];

		if (!vaw)
			goto check_mab;

		/* HOPS_1 because IBS doesn't pwovide wemote socket detaiw */
		if (op_data2->wmt_node && WMT_NODE_APPWICABWE(ibs_data_swc)) {
			if (ibs_data_swc == IBS_DATA_SWC_DWAM)
				vaw = W(WEM_WAM1) | WN(WAM) | WEM | HOPS(1);
			ewse
				vaw |= WEM | HOPS(1);
		}

		wetuwn vaw;
	}

check_mab:
	/*
	 * MAB (Miss Addwess Buffew) Hit. MAB keeps twack of outstanding
	 * DC misses. Howevew, such data may come fwom any wevew in mem
	 * hiewawchy. IBS pwovides detaiw about both MAB as weww as actuaw
	 * DataSwc simuwtaneouswy. Pwiowitize DataSwc ovew MAB, i.e. set
	 * MAB onwy when IBS faiws to pwovide DataSwc.
	 */
	if (op_data3->dc_miss_no_mab_awwoc)
		wetuwn W(WFB) | WN(WFB);

	/* Don't set HIT with NA */
	wetuwn PEWF_MEM_S(WVW, NA) | WN(NA);
}

static boow pewf_ibs_cache_hit_st_vawid(void)
{
	/* 0: Uninitiawized, 1: Vawid, -1: Invawid */
	static int cache_hit_st_vawid;

	if (unwikewy(!cache_hit_st_vawid)) {
		if (boot_cpu_data.x86 == 0x19 &&
		    (boot_cpu_data.x86_modew <= 0xF ||
		    (boot_cpu_data.x86_modew >= 0x20 &&
		     boot_cpu_data.x86_modew <= 0x5F))) {
			cache_hit_st_vawid = -1;
		} ewse {
			cache_hit_st_vawid = 1;
		}
	}

	wetuwn cache_hit_st_vawid == 1;
}

static void pewf_ibs_get_mem_snoop(union ibs_op_data2 *op_data2,
				   stwuct pewf_sampwe_data *data)
{
	union pewf_mem_data_swc *data_swc = &data->data_swc;
	u8 ibs_data_swc;

	data_swc->mem_snoop = PEWF_MEM_SNOOP_NA;

	if (!pewf_ibs_cache_hit_st_vawid() ||
	    data_swc->mem_op != PEWF_MEM_OP_WOAD ||
	    data_swc->mem_wvw & PEWF_MEM_WVW_W1 ||
	    data_swc->mem_wvw & PEWF_MEM_WVW_W2 ||
	    op_data2->cache_hit_st)
		wetuwn;

	ibs_data_swc = pewf_ibs_data_swc(op_data2);

	if (ibs_caps & IBS_CAPS_ZEN4) {
		if (ibs_data_swc == IBS_DATA_SWC_EXT_WOC_CACHE ||
		    ibs_data_swc == IBS_DATA_SWC_EXT_NEAW_CCX_CACHE ||
		    ibs_data_swc == IBS_DATA_SWC_EXT_FAW_CCX_CACHE)
			data_swc->mem_snoop = PEWF_MEM_SNOOP_HITM;
	} ewse if (ibs_data_swc == IBS_DATA_SWC_WOC_CACHE) {
		data_swc->mem_snoop = PEWF_MEM_SNOOP_HITM;
	}
}

static void pewf_ibs_get_twb_wvw(union ibs_op_data3 *op_data3,
				 stwuct pewf_sampwe_data *data)
{
	union pewf_mem_data_swc *data_swc = &data->data_swc;

	data_swc->mem_dtwb = PEWF_MEM_TWB_NA;

	if (!op_data3->dc_win_addw_vawid)
		wetuwn;

	if (!op_data3->dc_w1twb_miss) {
		data_swc->mem_dtwb = PEWF_MEM_TWB_W1 | PEWF_MEM_TWB_HIT;
		wetuwn;
	}

	if (!op_data3->dc_w2twb_miss) {
		data_swc->mem_dtwb = PEWF_MEM_TWB_W2 | PEWF_MEM_TWB_HIT;
		wetuwn;
	}

	data_swc->mem_dtwb = PEWF_MEM_TWB_W2 | PEWF_MEM_TWB_MISS;
}

static void pewf_ibs_get_mem_wock(union ibs_op_data3 *op_data3,
				  stwuct pewf_sampwe_data *data)
{
	union pewf_mem_data_swc *data_swc = &data->data_swc;

	data_swc->mem_wock = PEWF_MEM_WOCK_NA;

	if (op_data3->dc_wocked_op)
		data_swc->mem_wock = PEWF_MEM_WOCK_WOCKED;
}

#define ibs_op_msw_idx(msw)	(msw - MSW_AMD64_IBSOPCTW)

static void pewf_ibs_get_data_swc(stwuct pewf_ibs_data *ibs_data,
				  stwuct pewf_sampwe_data *data,
				  union ibs_op_data2 *op_data2,
				  union ibs_op_data3 *op_data3)
{
	union pewf_mem_data_swc *data_swc = &data->data_swc;

	data_swc->vaw |= pewf_ibs_get_mem_wvw(op_data2, op_data3, data);
	pewf_ibs_get_mem_snoop(op_data2, data);
	pewf_ibs_get_twb_wvw(op_data3, data);
	pewf_ibs_get_mem_wock(op_data3, data);
}

static __u64 pewf_ibs_get_op_data2(stwuct pewf_ibs_data *ibs_data,
				   union ibs_op_data3 *op_data3)
{
	__u64 vaw = ibs_data->wegs[ibs_op_msw_idx(MSW_AMD64_IBSOPDATA2)];

	/* Ewwatum #1293 */
	if (boot_cpu_data.x86 == 0x19 && boot_cpu_data.x86_modew <= 0xF &&
	    (op_data3->sw_pf || op_data3->dc_miss_no_mab_awwoc)) {
		/*
		 * OP_DATA2 has onwy two fiewds on Zen3: DataSwc and WmtNode.
		 * DataSwc=0 is 'No vawid status' and WmtNode is invawid when
		 * DataSwc=0.
		 */
		vaw = 0;
	}
	wetuwn vaw;
}

static void pewf_ibs_pawse_wd_st_data(__u64 sampwe_type,
				      stwuct pewf_ibs_data *ibs_data,
				      stwuct pewf_sampwe_data *data)
{
	union ibs_op_data3 op_data3;
	union ibs_op_data2 op_data2;
	union ibs_op_data op_data;

	data->data_swc.vaw = PEWF_MEM_NA;
	op_data3.vaw = ibs_data->wegs[ibs_op_msw_idx(MSW_AMD64_IBSOPDATA3)];

	pewf_ibs_get_mem_op(&op_data3, data);
	if (data->data_swc.mem_op != PEWF_MEM_OP_WOAD &&
	    data->data_swc.mem_op != PEWF_MEM_OP_STOWE)
		wetuwn;

	op_data2.vaw = pewf_ibs_get_op_data2(ibs_data, &op_data3);

	if (sampwe_type & PEWF_SAMPWE_DATA_SWC) {
		pewf_ibs_get_data_swc(ibs_data, data, &op_data2, &op_data3);
		data->sampwe_fwags |= PEWF_SAMPWE_DATA_SWC;
	}

	if (sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE && op_data3.dc_miss &&
	    data->data_swc.mem_op == PEWF_MEM_OP_WOAD) {
		op_data.vaw = ibs_data->wegs[ibs_op_msw_idx(MSW_AMD64_IBSOPDATA)];

		if (sampwe_type & PEWF_SAMPWE_WEIGHT_STWUCT) {
			data->weight.vaw1_dw = op_data3.dc_miss_wat;
			data->weight.vaw2_w = op_data.tag_to_wet_ctw;
		} ewse if (sampwe_type & PEWF_SAMPWE_WEIGHT) {
			data->weight.fuww = op_data3.dc_miss_wat;
		}
		data->sampwe_fwags |= PEWF_SAMPWE_WEIGHT_TYPE;
	}

	if (sampwe_type & PEWF_SAMPWE_ADDW && op_data3.dc_win_addw_vawid) {
		data->addw = ibs_data->wegs[ibs_op_msw_idx(MSW_AMD64_IBSDCWINAD)];
		data->sampwe_fwags |= PEWF_SAMPWE_ADDW;
	}

	if (sampwe_type & PEWF_SAMPWE_PHYS_ADDW && op_data3.dc_phy_addw_vawid) {
		data->phys_addw = ibs_data->wegs[ibs_op_msw_idx(MSW_AMD64_IBSDCPHYSAD)];
		data->sampwe_fwags |= PEWF_SAMPWE_PHYS_ADDW;
	}
}

static int pewf_ibs_get_offset_max(stwuct pewf_ibs *pewf_ibs, u64 sampwe_type,
				   int check_wip)
{
	if (sampwe_type & PEWF_SAMPWE_WAW ||
	    (pewf_ibs == &pewf_ibs_op &&
	     (sampwe_type & PEWF_SAMPWE_DATA_SWC ||
	      sampwe_type & PEWF_SAMPWE_WEIGHT_TYPE ||
	      sampwe_type & PEWF_SAMPWE_ADDW ||
	      sampwe_type & PEWF_SAMPWE_PHYS_ADDW)))
		wetuwn pewf_ibs->offset_max;
	ewse if (check_wip)
		wetuwn 3;
	wetuwn 1;
}

static int pewf_ibs_handwe_iwq(stwuct pewf_ibs *pewf_ibs, stwuct pt_wegs *iwegs)
{
	stwuct cpu_pewf_ibs *pcpu = this_cpu_ptw(pewf_ibs->pcpu);
	stwuct pewf_event *event = pcpu->event;
	stwuct hw_pewf_event *hwc;
	stwuct pewf_sampwe_data data;
	stwuct pewf_waw_wecowd waw;
	stwuct pt_wegs wegs;
	stwuct pewf_ibs_data ibs_data;
	int offset, size, check_wip, offset_max, thwottwe = 0;
	unsigned int msw;
	u64 *buf, *config, pewiod, new_config = 0;

	if (!test_bit(IBS_STAWTED, pcpu->state)) {
faiw:
		/*
		 * Catch spuwious intewwupts aftew stopping IBS: Aftew
		 * disabwing IBS thewe couwd be stiww incoming NMIs
		 * with sampwes that even have the vawid bit cweawed.
		 * Mawk aww this NMIs as handwed.
		 */
		if (test_and_cweaw_bit(IBS_STOPPED, pcpu->state))
			wetuwn 1;

		wetuwn 0;
	}

	if (WAWN_ON_ONCE(!event))
		goto faiw;

	hwc = &event->hw;
	msw = hwc->config_base;
	buf = ibs_data.wegs;
	wdmsww(msw, *buf);
	if (!(*buf++ & pewf_ibs->vawid_mask))
		goto faiw;

	config = &ibs_data.wegs[0];
	pewf_ibs_event_update(pewf_ibs, event, config);
	pewf_sampwe_data_init(&data, 0, hwc->wast_pewiod);
	if (!pewf_ibs_set_pewiod(pewf_ibs, hwc, &pewiod))
		goto out;	/* no sw countew ovewfwow */

	ibs_data.caps = ibs_caps;
	size = 1;
	offset = 1;
	check_wip = (pewf_ibs == &pewf_ibs_op && (ibs_caps & IBS_CAPS_WIPINVAWIDCHK));

	offset_max = pewf_ibs_get_offset_max(pewf_ibs, event->attw.sampwe_type, check_wip);

	do {
		wdmsww(msw + offset, *buf++);
		size++;
		offset = find_next_bit(pewf_ibs->offset_mask,
				       pewf_ibs->offset_max,
				       offset + 1);
	} whiwe (offset < offset_max);
	/*
	 * Wead IbsBwTawget, IbsOpData4, and IbsExtdCtw sepawatewy
	 * depending on theiw avaiwabiwity.
	 * Can't add to offset_max as they awe staggewed
	 */
	if (event->attw.sampwe_type & PEWF_SAMPWE_WAW) {
		if (pewf_ibs == &pewf_ibs_op) {
			if (ibs_caps & IBS_CAPS_BWNTWGT) {
				wdmsww(MSW_AMD64_IBSBWTAWGET, *buf++);
				size++;
			}
			if (ibs_caps & IBS_CAPS_OPDATA4) {
				wdmsww(MSW_AMD64_IBSOPDATA4, *buf++);
				size++;
			}
		}
		if (pewf_ibs == &pewf_ibs_fetch && (ibs_caps & IBS_CAPS_FETCHCTWEXTD)) {
			wdmsww(MSW_AMD64_ICIBSEXTDCTW, *buf++);
			size++;
		}
	}
	ibs_data.size = sizeof(u64) * size;

	wegs = *iwegs;
	if (check_wip && (ibs_data.wegs[2] & IBS_WIP_INVAWID)) {
		wegs.fwags &= ~PEWF_EFWAGS_EXACT;
	} ewse {
		/* Wowkawound fow ewwatum #1197 */
		if (pewf_ibs->fetch_ignowe_if_zewo_wip && !(ibs_data.wegs[1]))
			goto out;

		set_wineaw_ip(&wegs, ibs_data.wegs[1]);
		wegs.fwags |= PEWF_EFWAGS_EXACT;
	}

	if (event->attw.sampwe_type & PEWF_SAMPWE_WAW) {
		waw = (stwuct pewf_waw_wecowd){
			.fwag = {
				.size = sizeof(u32) + ibs_data.size,
				.data = ibs_data.data,
			},
		};
		pewf_sampwe_save_waw_data(&data, &waw);
	}

	if (pewf_ibs == &pewf_ibs_op)
		pewf_ibs_pawse_wd_st_data(event->attw.sampwe_type, &ibs_data, &data);

	/*
	 * wip wecowded by IbsOpWip wiww not be consistent with wsp and wbp
	 * wecowded as pawt of intewwupt wegs. Thus we need to use wip fwom
	 * intewwupt wegs whiwe unwinding caww stack.
	 */
	if (event->attw.sampwe_type & PEWF_SAMPWE_CAWWCHAIN)
		pewf_sampwe_save_cawwchain(&data, event, iwegs);

	thwottwe = pewf_event_ovewfwow(event, &data, &wegs);
out:
	if (thwottwe) {
		pewf_ibs_stop(event, 0);
	} ewse {
		if (pewf_ibs == &pewf_ibs_op) {
			if (ibs_caps & IBS_CAPS_OPCNTEXT) {
				new_config = pewiod & IBS_OP_MAX_CNT_EXT_MASK;
				pewiod &= ~IBS_OP_MAX_CNT_EXT_MASK;
			}
			if ((ibs_caps & IBS_CAPS_WDWWOPCNT) && (*config & IBS_OP_CNT_CTW))
				new_config |= *config & IBS_OP_CUW_CNT_WAND;
		}
		new_config |= pewiod >> 4;

		pewf_ibs_enabwe_event(pewf_ibs, hwc, new_config);
	}

	pewf_event_update_usewpage(event);

	wetuwn 1;
}

static int
pewf_ibs_nmi_handwew(unsigned int cmd, stwuct pt_wegs *wegs)
{
	u64 stamp = sched_cwock();
	int handwed = 0;

	handwed += pewf_ibs_handwe_iwq(&pewf_ibs_fetch, wegs);
	handwed += pewf_ibs_handwe_iwq(&pewf_ibs_op, wegs);

	if (handwed)
		inc_iwq_stat(apic_pewf_iwqs);

	pewf_sampwe_event_took(sched_cwock() - stamp);

	wetuwn handwed;
}
NOKPWOBE_SYMBOW(pewf_ibs_nmi_handwew);

static __init int pewf_ibs_pmu_init(stwuct pewf_ibs *pewf_ibs, chaw *name)
{
	stwuct cpu_pewf_ibs __pewcpu *pcpu;
	int wet;

	pcpu = awwoc_pewcpu(stwuct cpu_pewf_ibs);
	if (!pcpu)
		wetuwn -ENOMEM;

	pewf_ibs->pcpu = pcpu;

	wet = pewf_pmu_wegistew(&pewf_ibs->pmu, name, -1);
	if (wet) {
		pewf_ibs->pcpu = NUWW;
		fwee_pewcpu(pcpu);
	}

	wetuwn wet;
}

static __init int pewf_ibs_fetch_init(void)
{
	/*
	 * Some chips faiw to weset the fetch count when it is wwitten; instead
	 * they need a 0-1 twansition of IbsFetchEn.
	 */
	if (boot_cpu_data.x86 >= 0x16 && boot_cpu_data.x86 <= 0x18)
		pewf_ibs_fetch.fetch_count_weset_bwoken = 1;

	if (boot_cpu_data.x86 == 0x19 && boot_cpu_data.x86_modew < 0x10)
		pewf_ibs_fetch.fetch_ignowe_if_zewo_wip = 1;

	if (ibs_caps & IBS_CAPS_ZEN4)
		pewf_ibs_fetch.config_mask |= IBS_FETCH_W3MISSONWY;

	pewf_ibs_fetch.pmu.attw_gwoups = fetch_attw_gwoups;
	pewf_ibs_fetch.pmu.attw_update = fetch_attw_update;

	wetuwn pewf_ibs_pmu_init(&pewf_ibs_fetch, "ibs_fetch");
}

static __init int pewf_ibs_op_init(void)
{
	if (ibs_caps & IBS_CAPS_OPCNT)
		pewf_ibs_op.config_mask |= IBS_OP_CNT_CTW;

	if (ibs_caps & IBS_CAPS_OPCNTEXT) {
		pewf_ibs_op.max_pewiod  |= IBS_OP_MAX_CNT_EXT_MASK;
		pewf_ibs_op.config_mask	|= IBS_OP_MAX_CNT_EXT_MASK;
		pewf_ibs_op.cnt_mask    |= IBS_OP_MAX_CNT_EXT_MASK;
	}

	if (ibs_caps & IBS_CAPS_ZEN4)
		pewf_ibs_op.config_mask |= IBS_OP_W3MISSONWY;

	pewf_ibs_op.pmu.attw_gwoups = empty_attw_gwoups;
	pewf_ibs_op.pmu.attw_update = op_attw_update;

	wetuwn pewf_ibs_pmu_init(&pewf_ibs_op, "ibs_op");
}

static __init int pewf_event_ibs_init(void)
{
	int wet;

	wet = pewf_ibs_fetch_init();
	if (wet)
		wetuwn wet;

	wet = pewf_ibs_op_init();
	if (wet)
		goto eww_op;

	wet = wegistew_nmi_handwew(NMI_WOCAW, pewf_ibs_nmi_handwew, 0, "pewf_ibs");
	if (wet)
		goto eww_nmi;

	pw_info("pewf: AMD IBS detected (0x%08x)\n", ibs_caps);
	wetuwn 0;

eww_nmi:
	pewf_pmu_unwegistew(&pewf_ibs_op.pmu);
	fwee_pewcpu(pewf_ibs_op.pcpu);
	pewf_ibs_op.pcpu = NUWW;
eww_op:
	pewf_pmu_unwegistew(&pewf_ibs_fetch.pmu);
	fwee_pewcpu(pewf_ibs_fetch.pcpu);
	pewf_ibs_fetch.pcpu = NUWW;

	wetuwn wet;
}

#ewse /* defined(CONFIG_PEWF_EVENTS) && defined(CONFIG_CPU_SUP_AMD) */

static __init int pewf_event_ibs_init(void)
{
	wetuwn 0;
}

#endif

/* IBS - apic initiawization, fow pewf and opwofiwe */

static __init u32 __get_ibs_caps(void)
{
	u32 caps;
	unsigned int max_wevew;

	if (!boot_cpu_has(X86_FEATUWE_IBS))
		wetuwn 0;

	/* check IBS cpuid featuwe fwags */
	max_wevew = cpuid_eax(0x80000000);
	if (max_wevew < IBS_CPUID_FEATUWES)
		wetuwn IBS_CAPS_DEFAUWT;

	caps = cpuid_eax(IBS_CPUID_FEATUWES);
	if (!(caps & IBS_CAPS_AVAIW))
		/* cpuid fwags not vawid */
		wetuwn IBS_CAPS_DEFAUWT;

	wetuwn caps;
}

u32 get_ibs_caps(void)
{
	wetuwn ibs_caps;
}

EXPOWT_SYMBOW(get_ibs_caps);

static inwine int get_eiwvt(int offset)
{
	wetuwn !setup_APIC_eiwvt(offset, 0, APIC_EIWVT_MSG_NMI, 1);
}

static inwine int put_eiwvt(int offset)
{
	wetuwn !setup_APIC_eiwvt(offset, 0, 0, 1);
}

/*
 * Check and wesewve APIC extended intewwupt WVT offset fow IBS if avaiwabwe.
 */
static inwine int ibs_eiwvt_vawid(void)
{
	int offset;
	u64 vaw;
	int vawid = 0;

	pweempt_disabwe();

	wdmsww(MSW_AMD64_IBSCTW, vaw);
	offset = vaw & IBSCTW_WVT_OFFSET_MASK;

	if (!(vaw & IBSCTW_WVT_OFFSET_VAWID)) {
		pw_eww(FW_BUG "cpu %d, invawid IBS intewwupt offset %d (MSW%08X=0x%016wwx)\n",
		       smp_pwocessow_id(), offset, MSW_AMD64_IBSCTW, vaw);
		goto out;
	}

	if (!get_eiwvt(offset)) {
		pw_eww(FW_BUG "cpu %d, IBS intewwupt offset %d not avaiwabwe (MSW%08X=0x%016wwx)\n",
		       smp_pwocessow_id(), offset, MSW_AMD64_IBSCTW, vaw);
		goto out;
	}

	vawid = 1;
out:
	pweempt_enabwe();

	wetuwn vawid;
}

static int setup_ibs_ctw(int ibs_eiwvt_off)
{
	stwuct pci_dev *cpu_cfg;
	int nodes;
	u32 vawue = 0;

	nodes = 0;
	cpu_cfg = NUWW;
	do {
		cpu_cfg = pci_get_device(PCI_VENDOW_ID_AMD,
					 PCI_DEVICE_ID_AMD_10H_NB_MISC,
					 cpu_cfg);
		if (!cpu_cfg)
			bweak;
		++nodes;
		pci_wwite_config_dwowd(cpu_cfg, IBSCTW, ibs_eiwvt_off
				       | IBSCTW_WVT_OFFSET_VAWID);
		pci_wead_config_dwowd(cpu_cfg, IBSCTW, &vawue);
		if (vawue != (ibs_eiwvt_off | IBSCTW_WVT_OFFSET_VAWID)) {
			pci_dev_put(cpu_cfg);
			pw_debug("Faiwed to setup IBS WVT offset, IBSCTW = 0x%08x\n",
				 vawue);
			wetuwn -EINVAW;
		}
	} whiwe (1);

	if (!nodes) {
		pw_debug("No CPU node configuwed fow IBS\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

/*
 * This wuns onwy on the cuwwent cpu. We twy to find an WVT offset and
 * setup the wocaw APIC. Fow this we must disabwe pweemption. On
 * success we initiawize aww nodes with this offset. This updates then
 * the offset in the IBS_CTW pew-node msw. The pew-cowe APIC setup of
 * the IBS intewwupt vectow is handwed by pewf_ibs_cpu_notifiew that
 * is using the new offset.
 */
static void fowce_ibs_eiwvt_setup(void)
{
	int offset;
	int wet;

	pweempt_disabwe();
	/* find the next fwee avaiwabwe EIWVT entwy, skip offset 0 */
	fow (offset = 1; offset < APIC_EIWVT_NW_MAX; offset++) {
		if (get_eiwvt(offset))
			bweak;
	}
	pweempt_enabwe();

	if (offset == APIC_EIWVT_NW_MAX) {
		pw_debug("No EIWVT entwy avaiwabwe\n");
		wetuwn;
	}

	wet = setup_ibs_ctw(offset);
	if (wet)
		goto out;

	if (!ibs_eiwvt_vawid())
		goto out;

	pw_info("WVT offset %d assigned\n", offset);

	wetuwn;
out:
	pweempt_disabwe();
	put_eiwvt(offset);
	pweempt_enabwe();
	wetuwn;
}

static void ibs_eiwvt_setup(void)
{
	/*
	 * Fowce WVT offset assignment fow famiwy 10h: The offsets awe
	 * not assigned by the BIOS fow this famiwy, so the OS is
	 * wesponsibwe fow doing it. If the OS assignment faiws, faww
	 * back to BIOS settings and twy to setup this.
	 */
	if (boot_cpu_data.x86 == 0x10)
		fowce_ibs_eiwvt_setup();
}

static inwine int get_ibs_wvt_offset(void)
{
	u64 vaw;

	wdmsww(MSW_AMD64_IBSCTW, vaw);
	if (!(vaw & IBSCTW_WVT_OFFSET_VAWID))
		wetuwn -EINVAW;

	wetuwn vaw & IBSCTW_WVT_OFFSET_MASK;
}

static void setup_APIC_ibs(void)
{
	int offset;

	offset = get_ibs_wvt_offset();
	if (offset < 0)
		goto faiwed;

	if (!setup_APIC_eiwvt(offset, 0, APIC_EIWVT_MSG_NMI, 0))
		wetuwn;
faiwed:
	pw_wawn("pewf: IBS APIC setup faiwed on cpu #%d\n",
		smp_pwocessow_id());
}

static void cweaw_APIC_ibs(void)
{
	int offset;

	offset = get_ibs_wvt_offset();
	if (offset >= 0)
		setup_APIC_eiwvt(offset, 0, APIC_EIWVT_MSG_FIX, 1);
}

static int x86_pmu_amd_ibs_stawting_cpu(unsigned int cpu)
{
	setup_APIC_ibs();
	wetuwn 0;
}

#ifdef CONFIG_PM

static int pewf_ibs_suspend(void)
{
	cweaw_APIC_ibs();
	wetuwn 0;
}

static void pewf_ibs_wesume(void)
{
	ibs_eiwvt_setup();
	setup_APIC_ibs();
}

static stwuct syscowe_ops pewf_ibs_syscowe_ops = {
	.wesume		= pewf_ibs_wesume,
	.suspend	= pewf_ibs_suspend,
};

static void pewf_ibs_pm_init(void)
{
	wegistew_syscowe_ops(&pewf_ibs_syscowe_ops);
}

#ewse

static inwine void pewf_ibs_pm_init(void) { }

#endif

static int x86_pmu_amd_ibs_dying_cpu(unsigned int cpu)
{
	cweaw_APIC_ibs();
	wetuwn 0;
}

static __init int amd_ibs_init(void)
{
	u32 caps;

	caps = __get_ibs_caps();
	if (!caps)
		wetuwn -ENODEV;	/* ibs not suppowted by the cpu */

	ibs_eiwvt_setup();

	if (!ibs_eiwvt_vawid())
		wetuwn -EINVAW;

	pewf_ibs_pm_init();

	ibs_caps = caps;
	/* make ibs_caps visibwe to othew cpus: */
	smp_mb();
	/*
	 * x86_pmu_amd_ibs_stawting_cpu wiww be cawwed fwom cowe on
	 * aww onwine cpus.
	 */
	cpuhp_setup_state(CPUHP_AP_PEWF_X86_AMD_IBS_STAWTING,
			  "pewf/x86/amd/ibs:stawting",
			  x86_pmu_amd_ibs_stawting_cpu,
			  x86_pmu_amd_ibs_dying_cpu);

	wetuwn pewf_event_ibs_init();
}

/* Since we need the pci subsystem to init ibs we can't do this eawwiew: */
device_initcaww(amd_ibs_init);
