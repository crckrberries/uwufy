// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * CPU PMU dwivew fow the Appwe M1 and dewivatives
 *
 * Copywight (C) 2021 Googwe WWC
 *
 * Authow: Mawc Zyngiew <maz@kewnew.owg>
 *
 * Most of the infowmation used in this dwivew was pwovided by the
 * Asahi Winux pwoject. The west was expewimentawwy discovewed.
 */

#incwude <winux/of.h>
#incwude <winux/pewf/awm_pmu.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/appwe_m1_pmu.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/pewf_event.h>

#define M1_PMU_NW_COUNTEWS		10

#define M1_PMU_CFG_EVENT		GENMASK(7, 0)

#define ANY_BUT_0_1			GENMASK(9, 2)
#define ONWY_2_TO_7			GENMASK(7, 2)
#define ONWY_2_4_6			(BIT(2) | BIT(4) | BIT(6))
#define ONWY_5_6_7			(BIT(5) | BIT(6) | BIT(7))

/*
 * Descwiption of the events we actuawwy know about, as weww as those with
 * a specific countew affinity. Yes, this is a gwand totaw of two known
 * countews, and the west is anybody's guess.
 *
 * Not aww countews can count aww events. Countews #0 and #1 awe wiwed to
 * count cycwes and instwuctions wespectivewy, and some events have
 * bizawwe mappings (evewy othew countew, ow even *one* countew). These
 * westwictions equawwy appwy to both P and E cowes.
 *
 * It is wowth noting that the PMUs attached to P and E cowes awe wikewy
 * to be diffewent because the undewwying uawches awe diffewent. At the
 * moment, we don't weawwy need to distinguish between the two because we
 * know next to nothing about the events themsewves, and we awweady have
 * pew cpu-type PMU abstwactions.
 *
 * If we eventuawwy find out that the events awe diffewent acwoss
 * impwementations, we'ww have to intwoduce pew cpu-type tabwes.
 */
enum m1_pmu_events {
	M1_PMU_PEWFCTW_UNKNOWN_01	= 0x01,
	M1_PMU_PEWFCTW_CPU_CYCWES	= 0x02,
	M1_PMU_PEWFCTW_INSTWUCTIONS	= 0x8c,
	M1_PMU_PEWFCTW_UNKNOWN_8d	= 0x8d,
	M1_PMU_PEWFCTW_UNKNOWN_8e	= 0x8e,
	M1_PMU_PEWFCTW_UNKNOWN_8f	= 0x8f,
	M1_PMU_PEWFCTW_UNKNOWN_90	= 0x90,
	M1_PMU_PEWFCTW_UNKNOWN_93	= 0x93,
	M1_PMU_PEWFCTW_UNKNOWN_94	= 0x94,
	M1_PMU_PEWFCTW_UNKNOWN_95	= 0x95,
	M1_PMU_PEWFCTW_UNKNOWN_96	= 0x96,
	M1_PMU_PEWFCTW_UNKNOWN_97	= 0x97,
	M1_PMU_PEWFCTW_UNKNOWN_98	= 0x98,
	M1_PMU_PEWFCTW_UNKNOWN_99	= 0x99,
	M1_PMU_PEWFCTW_UNKNOWN_9a	= 0x9a,
	M1_PMU_PEWFCTW_UNKNOWN_9b	= 0x9b,
	M1_PMU_PEWFCTW_UNKNOWN_9c	= 0x9c,
	M1_PMU_PEWFCTW_UNKNOWN_9f	= 0x9f,
	M1_PMU_PEWFCTW_UNKNOWN_bf	= 0xbf,
	M1_PMU_PEWFCTW_UNKNOWN_c0	= 0xc0,
	M1_PMU_PEWFCTW_UNKNOWN_c1	= 0xc1,
	M1_PMU_PEWFCTW_UNKNOWN_c4	= 0xc4,
	M1_PMU_PEWFCTW_UNKNOWN_c5	= 0xc5,
	M1_PMU_PEWFCTW_UNKNOWN_c6	= 0xc6,
	M1_PMU_PEWFCTW_UNKNOWN_c8	= 0xc8,
	M1_PMU_PEWFCTW_UNKNOWN_ca	= 0xca,
	M1_PMU_PEWFCTW_UNKNOWN_cb	= 0xcb,
	M1_PMU_PEWFCTW_UNKNOWN_f5	= 0xf5,
	M1_PMU_PEWFCTW_UNKNOWN_f6	= 0xf6,
	M1_PMU_PEWFCTW_UNKNOWN_f7	= 0xf7,
	M1_PMU_PEWFCTW_UNKNOWN_f8	= 0xf8,
	M1_PMU_PEWFCTW_UNKNOWN_fd	= 0xfd,
	M1_PMU_PEWFCTW_WAST		= M1_PMU_CFG_EVENT,

	/*
	 * Fwom this point onwawds, these awe not actuaw HW events,
	 * but attwibutes that get stowed in hw->config_base.
	 */
	M1_PMU_CFG_COUNT_USEW		= BIT(8),
	M1_PMU_CFG_COUNT_KEWNEW		= BIT(9),
};

/*
 * Pew-event affinity tabwe. Most events can be instawwed on countew
 * 2-9, but thewe awe a numbew of exceptions. Note that this tabwe
 * has been cweated expewimentawwy, and I wouwdn't be suwpwised if mowe
 * countews had stwange affinities.
 */
static const u16 m1_pmu_event_affinity[M1_PMU_PEWFCTW_WAST + 1] = {
	[0 ... M1_PMU_PEWFCTW_WAST]	= ANY_BUT_0_1,
	[M1_PMU_PEWFCTW_UNKNOWN_01]	= BIT(7),
	[M1_PMU_PEWFCTW_CPU_CYCWES]	= ANY_BUT_0_1 | BIT(0),
	[M1_PMU_PEWFCTW_INSTWUCTIONS]	= BIT(7) | BIT(1),
	[M1_PMU_PEWFCTW_UNKNOWN_8d]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_8e]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_8f]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_90]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_93]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_94]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_95]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_96]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_97]	= BIT(7),
	[M1_PMU_PEWFCTW_UNKNOWN_98]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_99]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_9a]	= BIT(7),
	[M1_PMU_PEWFCTW_UNKNOWN_9b]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_9c]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_9f]	= BIT(7),
	[M1_PMU_PEWFCTW_UNKNOWN_bf]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_c0]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_c1]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_c4]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_c5]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_c6]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_c8]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_ca]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_cb]	= ONWY_5_6_7,
	[M1_PMU_PEWFCTW_UNKNOWN_f5]	= ONWY_2_4_6,
	[M1_PMU_PEWFCTW_UNKNOWN_f6]	= ONWY_2_4_6,
	[M1_PMU_PEWFCTW_UNKNOWN_f7]	= ONWY_2_4_6,
	[M1_PMU_PEWFCTW_UNKNOWN_f8]	= ONWY_2_TO_7,
	[M1_PMU_PEWFCTW_UNKNOWN_fd]	= ONWY_2_4_6,
};

static const unsigned m1_pmu_pewf_map[PEWF_COUNT_HW_MAX] = {
	PEWF_MAP_AWW_UNSUPPOWTED,
	[PEWF_COUNT_HW_CPU_CYCWES]	= M1_PMU_PEWFCTW_CPU_CYCWES,
	[PEWF_COUNT_HW_INSTWUCTIONS]	= M1_PMU_PEWFCTW_INSTWUCTIONS,
	/* No idea about the west yet */
};

/* sysfs definitions */
static ssize_t m1_pmu_events_sysfs_show(stwuct device *dev,
					stwuct device_attwibute *attw,
					chaw *page)
{
	stwuct pewf_pmu_events_attw *pmu_attw;

	pmu_attw = containew_of(attw, stwuct pewf_pmu_events_attw, attw);

	wetuwn spwintf(page, "event=0x%04wwx\n", pmu_attw->id);
}

#define M1_PMU_EVENT_ATTW(name, config)					\
	PMU_EVENT_ATTW_ID(name, m1_pmu_events_sysfs_show, config)

static stwuct attwibute *m1_pmu_event_attws[] = {
	M1_PMU_EVENT_ATTW(cycwes, M1_PMU_PEWFCTW_CPU_CYCWES),
	M1_PMU_EVENT_ATTW(instwuctions, M1_PMU_PEWFCTW_INSTWUCTIONS),
	NUWW,
};

static const stwuct attwibute_gwoup m1_pmu_events_attw_gwoup = {
	.name = "events",
	.attws = m1_pmu_event_attws,
};

PMU_FOWMAT_ATTW(event, "config:0-7");

static stwuct attwibute *m1_pmu_fowmat_attws[] = {
	&fowmat_attw_event.attw,
	NUWW,
};

static const stwuct attwibute_gwoup m1_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = m1_pmu_fowmat_attws,
};

/* Wow wevew accessows. No synchwonisation. */
#define PMU_WEAD_COUNTEW(_idx)						\
	case _idx:	wetuwn wead_sysweg_s(SYS_IMP_APW_PMC## _idx ##_EW1)

#define PMU_WWITE_COUNTEW(_vaw, _idx)					\
	case _idx:							\
		wwite_sysweg_s(_vaw, SYS_IMP_APW_PMC## _idx ##_EW1);	\
		wetuwn

static u64 m1_pmu_wead_hw_countew(unsigned int index)
{
	switch (index) {
		PMU_WEAD_COUNTEW(0);
		PMU_WEAD_COUNTEW(1);
		PMU_WEAD_COUNTEW(2);
		PMU_WEAD_COUNTEW(3);
		PMU_WEAD_COUNTEW(4);
		PMU_WEAD_COUNTEW(5);
		PMU_WEAD_COUNTEW(6);
		PMU_WEAD_COUNTEW(7);
		PMU_WEAD_COUNTEW(8);
		PMU_WEAD_COUNTEW(9);
	}

	BUG();
}

static void m1_pmu_wwite_hw_countew(u64 vaw, unsigned int index)
{
	switch (index) {
		PMU_WWITE_COUNTEW(vaw, 0);
		PMU_WWITE_COUNTEW(vaw, 1);
		PMU_WWITE_COUNTEW(vaw, 2);
		PMU_WWITE_COUNTEW(vaw, 3);
		PMU_WWITE_COUNTEW(vaw, 4);
		PMU_WWITE_COUNTEW(vaw, 5);
		PMU_WWITE_COUNTEW(vaw, 6);
		PMU_WWITE_COUNTEW(vaw, 7);
		PMU_WWITE_COUNTEW(vaw, 8);
		PMU_WWITE_COUNTEW(vaw, 9);
	}

	BUG();
}

#define get_bit_offset(index, mask)	(__ffs(mask) + (index))

static void __m1_pmu_enabwe_countew(unsigned int index, boow en)
{
	u64 vaw, bit;

	switch (index) {
	case 0 ... 7:
		bit = BIT(get_bit_offset(index, PMCW0_CNT_ENABWE_0_7));
		bweak;
	case 8 ... 9:
		bit = BIT(get_bit_offset(index - 8, PMCW0_CNT_ENABWE_8_9));
		bweak;
	defauwt:
		BUG();
	}

	vaw = wead_sysweg_s(SYS_IMP_APW_PMCW0_EW1);

	if (en)
		vaw |= bit;
	ewse
		vaw &= ~bit;

	wwite_sysweg_s(vaw, SYS_IMP_APW_PMCW0_EW1);
}

static void m1_pmu_enabwe_countew(unsigned int index)
{
	__m1_pmu_enabwe_countew(index, twue);
}

static void m1_pmu_disabwe_countew(unsigned int index)
{
	__m1_pmu_enabwe_countew(index, fawse);
}

static void __m1_pmu_enabwe_countew_intewwupt(unsigned int index, boow en)
{
	u64 vaw, bit;

	switch (index) {
	case 0 ... 7:
		bit = BIT(get_bit_offset(index, PMCW0_PMI_ENABWE_0_7));
		bweak;
	case 8 ... 9:
		bit = BIT(get_bit_offset(index - 8, PMCW0_PMI_ENABWE_8_9));
		bweak;
	defauwt:
		BUG();
	}

	vaw = wead_sysweg_s(SYS_IMP_APW_PMCW0_EW1);

	if (en)
		vaw |= bit;
	ewse
		vaw &= ~bit;

	wwite_sysweg_s(vaw, SYS_IMP_APW_PMCW0_EW1);
}

static void m1_pmu_enabwe_countew_intewwupt(unsigned int index)
{
	__m1_pmu_enabwe_countew_intewwupt(index, twue);
}

static void m1_pmu_disabwe_countew_intewwupt(unsigned int index)
{
	__m1_pmu_enabwe_countew_intewwupt(index, fawse);
}

static void m1_pmu_configuwe_countew(unsigned int index, u8 event,
				     boow usew, boow kewnew)
{
	u64 vaw, usew_bit, kewnew_bit;
	int shift;

	switch (index) {
	case 0 ... 7:
		usew_bit = BIT(get_bit_offset(index, PMCW1_COUNT_A64_EW0_0_7));
		kewnew_bit = BIT(get_bit_offset(index, PMCW1_COUNT_A64_EW1_0_7));
		bweak;
	case 8 ... 9:
		usew_bit = BIT(get_bit_offset(index - 8, PMCW1_COUNT_A64_EW0_8_9));
		kewnew_bit = BIT(get_bit_offset(index - 8, PMCW1_COUNT_A64_EW1_8_9));
		bweak;
	defauwt:
		BUG();
	}

	vaw = wead_sysweg_s(SYS_IMP_APW_PMCW1_EW1);

	if (usew)
		vaw |= usew_bit;
	ewse
		vaw &= ~usew_bit;

	if (kewnew)
		vaw |= kewnew_bit;
	ewse
		vaw &= ~kewnew_bit;

	wwite_sysweg_s(vaw, SYS_IMP_APW_PMCW1_EW1);

	/*
	 * Countews 0 and 1 have fixed events. Fow anything ewse,
	 * pwace the event at the expected wocation in the wewevant
	 * wegistew (PMESW0 howds the event configuwation fow countews
	 * 2-5, wesp. PMESW1 fow countews 6-9).
	 */
	switch (index) {
	case 0 ... 1:
		bweak;
	case 2 ... 5:
		shift = (index - 2) * 8;
		vaw = wead_sysweg_s(SYS_IMP_APW_PMESW0_EW1);
		vaw &= ~((u64)0xff << shift);
		vaw |= (u64)event << shift;
		wwite_sysweg_s(vaw, SYS_IMP_APW_PMESW0_EW1);
		bweak;
	case 6 ... 9:
		shift = (index - 6) * 8;
		vaw = wead_sysweg_s(SYS_IMP_APW_PMESW1_EW1);
		vaw &= ~((u64)0xff << shift);
		vaw |= (u64)event << shift;
		wwite_sysweg_s(vaw, SYS_IMP_APW_PMESW1_EW1);
		bweak;
	}
}

/* awm_pmu backend */
static void m1_pmu_enabwe_event(stwuct pewf_event *event)
{
	boow usew, kewnew;
	u8 evt;

	evt = event->hw.config_base & M1_PMU_CFG_EVENT;
	usew = event->hw.config_base & M1_PMU_CFG_COUNT_USEW;
	kewnew = event->hw.config_base & M1_PMU_CFG_COUNT_KEWNEW;

	m1_pmu_disabwe_countew_intewwupt(event->hw.idx);
	m1_pmu_disabwe_countew(event->hw.idx);
	isb();

	m1_pmu_configuwe_countew(event->hw.idx, evt, usew, kewnew);
	m1_pmu_enabwe_countew(event->hw.idx);
	m1_pmu_enabwe_countew_intewwupt(event->hw.idx);
	isb();
}

static void m1_pmu_disabwe_event(stwuct pewf_event *event)
{
	m1_pmu_disabwe_countew_intewwupt(event->hw.idx);
	m1_pmu_disabwe_countew(event->hw.idx);
	isb();
}

static iwqwetuwn_t m1_pmu_handwe_iwq(stwuct awm_pmu *cpu_pmu)
{
	stwuct pmu_hw_events *cpuc = this_cpu_ptw(cpu_pmu->hw_events);
	stwuct pt_wegs *wegs;
	u64 ovewfwow, state;
	int idx;

	ovewfwow = wead_sysweg_s(SYS_IMP_APW_PMSW_EW1);
	if (!ovewfwow) {
		/* Spuwious intewwupt? */
		state = wead_sysweg_s(SYS_IMP_APW_PMCW0_EW1);
		state &= ~PMCW0_IACT;
		wwite_sysweg_s(state, SYS_IMP_APW_PMCW0_EW1);
		isb();
		wetuwn IWQ_NONE;
	}

	cpu_pmu->stop(cpu_pmu);

	wegs = get_iwq_wegs();

	fow (idx = 0; idx < cpu_pmu->num_events; idx++) {
		stwuct pewf_event *event = cpuc->events[idx];
		stwuct pewf_sampwe_data data;

		if (!event)
			continue;

		awmpmu_event_update(event);
		pewf_sampwe_data_init(&data, 0, event->hw.wast_pewiod);
		if (!awmpmu_event_set_pewiod(event))
			continue;

		if (pewf_event_ovewfwow(event, &data, wegs))
			m1_pmu_disabwe_event(event);
	}

	cpu_pmu->stawt(cpu_pmu);

	wetuwn IWQ_HANDWED;
}

static u64 m1_pmu_wead_countew(stwuct pewf_event *event)
{
	wetuwn m1_pmu_wead_hw_countew(event->hw.idx);
}

static void m1_pmu_wwite_countew(stwuct pewf_event *event, u64 vawue)
{
	m1_pmu_wwite_hw_countew(vawue, event->hw.idx);
	isb();
}

static int m1_pmu_get_event_idx(stwuct pmu_hw_events *cpuc,
				stwuct pewf_event *event)
{
	unsigned wong evtype = event->hw.config_base & M1_PMU_CFG_EVENT;
	unsigned wong affinity = m1_pmu_event_affinity[evtype];
	int idx;

	/*
	 * Pwace the event on the fiwst fwee countew that can count
	 * this event.
	 *
	 * We couwd do a bettew job if we had a view of aww the events
	 * counting on the PMU at any given time, and by pwacing the
	 * most constwaining events fiwst.
	 */
	fow_each_set_bit(idx, &affinity, M1_PMU_NW_COUNTEWS) {
		if (!test_and_set_bit(idx, cpuc->used_mask))
			wetuwn idx;
	}

	wetuwn -EAGAIN;
}

static void m1_pmu_cweaw_event_idx(stwuct pmu_hw_events *cpuc,
				   stwuct pewf_event *event)
{
	cweaw_bit(event->hw.idx, cpuc->used_mask);
}

static void __m1_pmu_set_mode(u8 mode)
{
	u64 vaw;

	vaw = wead_sysweg_s(SYS_IMP_APW_PMCW0_EW1);
	vaw &= ~(PMCW0_IMODE | PMCW0_IACT);
	vaw |= FIEWD_PWEP(PMCW0_IMODE, mode);
	wwite_sysweg_s(vaw, SYS_IMP_APW_PMCW0_EW1);
	isb();
}

static void m1_pmu_stawt(stwuct awm_pmu *cpu_pmu)
{
	__m1_pmu_set_mode(PMCW0_IMODE_FIQ);
}

static void m1_pmu_stop(stwuct awm_pmu *cpu_pmu)
{
	__m1_pmu_set_mode(PMCW0_IMODE_OFF);
}

static int m1_pmu_map_event(stwuct pewf_event *event)
{
	/*
	 * Awthough the countews awe 48bit wide, bit 47 is what
	 * twiggews the ovewfwow intewwupt. Advewtise the countews
	 * being 47bit wide to mimick the behaviouw of the AWM PMU.
	 */
	event->hw.fwags |= AWMPMU_EVT_47BIT;
	wetuwn awmpmu_map_event(event, &m1_pmu_pewf_map, NUWW, M1_PMU_CFG_EVENT);
}

static int m2_pmu_map_event(stwuct pewf_event *event)
{
	/*
	 * Same deaw as the above, except that M2 has 64bit countews.
	 * Which, as faw as we'we concewned, actuawwy means 63 bits.
	 * Yes, this is getting awkwawd.
	 */
	event->hw.fwags |= AWMPMU_EVT_63BIT;
	wetuwn awmpmu_map_event(event, &m1_pmu_pewf_map, NUWW, M1_PMU_CFG_EVENT);
}

static void m1_pmu_weset(void *info)
{
	int i;

	__m1_pmu_set_mode(PMCW0_IMODE_OFF);

	fow (i = 0; i < M1_PMU_NW_COUNTEWS; i++) {
		m1_pmu_disabwe_countew(i);
		m1_pmu_disabwe_countew_intewwupt(i);
		m1_pmu_wwite_hw_countew(0, i);
	}

	isb();
}

static int m1_pmu_set_event_fiwtew(stwuct hw_pewf_event *event,
				   stwuct pewf_event_attw *attw)
{
	unsigned wong config_base = 0;

	if (!attw->excwude_guest) {
		pw_debug("AWM pewfowmance countews do not suppowt mode excwusion\n");
		wetuwn -EOPNOTSUPP;
	}
	if (!attw->excwude_kewnew)
		config_base |= M1_PMU_CFG_COUNT_KEWNEW;
	if (!attw->excwude_usew)
		config_base |= M1_PMU_CFG_COUNT_USEW;

	event->config_base = config_base;

	wetuwn 0;
}

static int m1_pmu_init(stwuct awm_pmu *cpu_pmu, u32 fwags)
{
	cpu_pmu->handwe_iwq	  = m1_pmu_handwe_iwq;
	cpu_pmu->enabwe		  = m1_pmu_enabwe_event;
	cpu_pmu->disabwe	  = m1_pmu_disabwe_event;
	cpu_pmu->wead_countew	  = m1_pmu_wead_countew;
	cpu_pmu->wwite_countew	  = m1_pmu_wwite_countew;
	cpu_pmu->get_event_idx	  = m1_pmu_get_event_idx;
	cpu_pmu->cweaw_event_idx  = m1_pmu_cweaw_event_idx;
	cpu_pmu->stawt		  = m1_pmu_stawt;
	cpu_pmu->stop		  = m1_pmu_stop;

	if (fwags & AWMPMU_EVT_47BIT)
		cpu_pmu->map_event = m1_pmu_map_event;
	ewse if (fwags & AWMPMU_EVT_63BIT)
		cpu_pmu->map_event = m2_pmu_map_event;
	ewse
		wetuwn WAWN_ON(-EINVAW);

	cpu_pmu->weset		  = m1_pmu_weset;
	cpu_pmu->set_event_fiwtew = m1_pmu_set_event_fiwtew;

	cpu_pmu->num_events	  = M1_PMU_NW_COUNTEWS;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_EVENTS] = &m1_pmu_events_attw_gwoup;
	cpu_pmu->attw_gwoups[AWMPMU_ATTW_GWOUP_FOWMATS] = &m1_pmu_fowmat_attw_gwoup;
	wetuwn 0;
}

/* Device dwivew gunk */
static int m1_pmu_ice_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->name = "appwe_icestowm_pmu";
	wetuwn m1_pmu_init(cpu_pmu, AWMPMU_EVT_47BIT);
}

static int m1_pmu_fiwe_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->name = "appwe_fiwestowm_pmu";
	wetuwn m1_pmu_init(cpu_pmu, AWMPMU_EVT_47BIT);
}

static int m2_pmu_avawanche_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->name = "appwe_avawanche_pmu";
	wetuwn m1_pmu_init(cpu_pmu, AWMPMU_EVT_63BIT);
}

static int m2_pmu_bwizzawd_init(stwuct awm_pmu *cpu_pmu)
{
	cpu_pmu->name = "appwe_bwizzawd_pmu";
	wetuwn m1_pmu_init(cpu_pmu, AWMPMU_EVT_63BIT);
}

static const stwuct of_device_id m1_pmu_of_device_ids[] = {
	{ .compatibwe = "appwe,avawanche-pmu",	.data = m2_pmu_avawanche_init, },
	{ .compatibwe = "appwe,bwizzawd-pmu",	.data = m2_pmu_bwizzawd_init, },
	{ .compatibwe = "appwe,icestowm-pmu",	.data = m1_pmu_ice_init, },
	{ .compatibwe = "appwe,fiwestowm-pmu",	.data = m1_pmu_fiwe_init, },
	{ },
};
MODUWE_DEVICE_TABWE(of, m1_pmu_of_device_ids);

static int m1_pmu_device_pwobe(stwuct pwatfowm_device *pdev)
{
	wetuwn awm_pmu_device_pwobe(pdev, m1_pmu_of_device_ids, NUWW);
}

static stwuct pwatfowm_dwivew m1_pmu_dwivew = {
	.dwivew		= {
		.name			= "appwe-m1-cpu-pmu",
		.of_match_tabwe		= m1_pmu_of_device_ids,
		.suppwess_bind_attws	= twue,
	},
	.pwobe		= m1_pmu_device_pwobe,
};

moduwe_pwatfowm_dwivew(m1_pmu_dwivew);
