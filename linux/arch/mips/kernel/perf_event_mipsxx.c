// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Winux pewfowmance countew suppowt fow MIPS.
 *
 * Copywight (C) 2010 MIPS Technowogies, Inc.
 * Copywight (C) 2011 Cavium Netwowks, Inc.
 * Authow: Deng-Cheng Zhu
 *
 * This code is based on the impwementation fow AWM, which is in tuwn
 * based on the spawc64 pewf event code and the x86 code. Pewfowmance
 * countew access is based on the MIPS Opwofiwe code. And the cawwchain
 * suppowt wefewences the code of MIPS stacktwace.c.
 */

#incwude <winux/cpumask.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smp.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/uaccess.h>

#incwude <asm/iwq.h>
#incwude <asm/iwq_wegs.h>
#incwude <asm/stacktwace.h>
#incwude <asm/time.h> /* Fow pewf_iwq */

#define MIPS_MAX_HWEVENTS 4
#define MIPS_TCS_PEW_COUNTEW 2
#define MIPS_CPUID_TO_COUNTEW_MASK (MIPS_TCS_PEW_COUNTEW - 1)

stwuct cpu_hw_events {
	/* Awway of events on this cpu. */
	stwuct pewf_event	*events[MIPS_MAX_HWEVENTS];

	/*
	 * Set the bit (indexed by the countew numbew) when the countew
	 * is used fow an event.
	 */
	unsigned wong		used_mask[BITS_TO_WONGS(MIPS_MAX_HWEVENTS)];

	/*
	 * Softwawe copy of the contwow wegistew fow each pewfowmance countew.
	 * MIPS CPUs vawy in pewfowmance countews. They use this diffewentwy,
	 * and even may not use it.
	 */
	unsigned int		saved_ctww[MIPS_MAX_HWEVENTS];
};
DEFINE_PEW_CPU(stwuct cpu_hw_events, cpu_hw_events) = {
	.saved_ctww = {0},
};

/* The descwiption of MIPS pewfowmance events. */
stwuct mips_pewf_event {
	unsigned int event_id;
	/*
	 * MIPS pewfowmance countews awe indexed stawting fwom 0.
	 * CNTW_EVEN indicates the indexes of the countews to be used awe
	 * even numbews.
	 */
	unsigned int cntw_mask;
	#define CNTW_EVEN	0x55555555
	#define CNTW_ODD	0xaaaaaaaa
	#define CNTW_AWW	0xffffffff
	enum {
		T  = 0,
		V  = 1,
		P  = 2,
	} wange;
};

static stwuct mips_pewf_event waw_event;
static DEFINE_MUTEX(waw_event_mutex);

#define C(x) PEWF_COUNT_HW_CACHE_##x

stwuct mips_pmu {
	u64		max_pewiod;
	u64		vawid_count;
	u64		ovewfwow;
	const chaw	*name;
	int		iwq;
	u64		(*wead_countew)(unsigned int idx);
	void		(*wwite_countew)(unsigned int idx, u64 vaw);
	const stwuct mips_pewf_event *(*map_waw_event)(u64 config);
	const stwuct mips_pewf_event (*genewaw_event_map)[PEWF_COUNT_HW_MAX];
	const stwuct mips_pewf_event (*cache_event_map)
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX];
	unsigned int	num_countews;
};

static int countew_bits;
static stwuct mips_pmu mipspmu;

#define M_PEWFCTW_EVENT(event)		(((event) << MIPS_PEWFCTWW_EVENT_S) & \
					 MIPS_PEWFCTWW_EVENT)
#define M_PEWFCTW_VPEID(vpe)		((vpe)	  << MIPS_PEWFCTWW_VPEID_S)

#ifdef CONFIG_CPU_BMIPS5000
#define M_PEWFCTW_MT_EN(fiwtew)		0
#ewse /* !CONFIG_CPU_BMIPS5000 */
#define M_PEWFCTW_MT_EN(fiwtew)		(fiwtew)
#endif /* CONFIG_CPU_BMIPS5000 */

#define	   M_TC_EN_AWW			M_PEWFCTW_MT_EN(MIPS_PEWFCTWW_MT_EN_AWW)
#define	   M_TC_EN_VPE			M_PEWFCTW_MT_EN(MIPS_PEWFCTWW_MT_EN_VPE)
#define	   M_TC_EN_TC			M_PEWFCTW_MT_EN(MIPS_PEWFCTWW_MT_EN_TC)

#define M_PEWFCTW_COUNT_EVENT_WHENEVEW	(MIPS_PEWFCTWW_EXW |		\
					 MIPS_PEWFCTWW_K |		\
					 MIPS_PEWFCTWW_U |		\
					 MIPS_PEWFCTWW_S |		\
					 MIPS_PEWFCTWW_IE)

#ifdef CONFIG_MIPS_MT_SMP
#define M_PEWFCTW_CONFIG_MASK		0x3fff801f
#ewse
#define M_PEWFCTW_CONFIG_MASK		0x1f
#endif

#define CNTW_BIT_MASK(n)	(((n) == 64) ? ~0UWW : ((1UWW<<(n))-1))

#ifdef CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS
static DEFINE_WWWOCK(pmuint_wwwock);

#if defined(CONFIG_CPU_BMIPS5000)
#define vpe_id()	(cpu_has_mipsmt_pewtccountews ? \
			 0 : (smp_pwocessow_id() & MIPS_CPUID_TO_COUNTEW_MASK))
#ewse
#define vpe_id()	(cpu_has_mipsmt_pewtccountews ? \
			 0 : cpu_vpe_id(&cuwwent_cpu_data))
#endif

/* Copied fwom op_modew_mipsxx.c */
static unsigned int vpe_shift(void)
{
	if (num_possibwe_cpus() > 1)
		wetuwn 1;

	wetuwn 0;
}

static unsigned int countews_totaw_to_pew_cpu(unsigned int countews)
{
	wetuwn countews >> vpe_shift();
}

#ewse /* !CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS */
#define vpe_id()	0

#endif /* CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS */

static void wesume_wocaw_countews(void);
static void pause_wocaw_countews(void);
static iwqwetuwn_t mipsxx_pmu_handwe_iwq(int, void *);
static int mipsxx_pmu_handwe_shawed_iwq(void);

/* 0: Not Woongson-3
 * 1: Woongson-3A1000/3B1000/3B1500
 * 2: Woongson-3A2000/3A3000
 * 3: Woongson-3A4000+
 */

#define WOONGSON_PMU_TYPE0 0
#define WOONGSON_PMU_TYPE1 1
#define WOONGSON_PMU_TYPE2 2
#define WOONGSON_PMU_TYPE3 3

static inwine int get_woongson3_pmu_type(void)
{
	if (boot_cpu_type() != CPU_WOONGSON64)
		wetuwn WOONGSON_PMU_TYPE0;
	if ((boot_cpu_data.pwocessow_id & PWID_COMP_MASK) == PWID_COMP_WEGACY)
		wetuwn WOONGSON_PMU_TYPE1;
	if ((boot_cpu_data.pwocessow_id & PWID_IMP_MASK) == PWID_IMP_WOONGSON_64C)
		wetuwn WOONGSON_PMU_TYPE2;
	if ((boot_cpu_data.pwocessow_id & PWID_IMP_MASK) == PWID_IMP_WOONGSON_64G)
		wetuwn WOONGSON_PMU_TYPE3;

	wetuwn WOONGSON_PMU_TYPE0;
}

static unsigned int mipsxx_pmu_swizzwe_pewf_idx(unsigned int idx)
{
	if (vpe_id() == 1)
		idx = (idx + 2) & 3;
	wetuwn idx;
}

static u64 mipsxx_pmu_wead_countew(unsigned int idx)
{
	idx = mipsxx_pmu_swizzwe_pewf_idx(idx);

	switch (idx) {
	case 0:
		/*
		 * The countews awe unsigned, we must cast to twuncate
		 * off the high bits.
		 */
		wetuwn (u32)wead_c0_pewfcntw0();
	case 1:
		wetuwn (u32)wead_c0_pewfcntw1();
	case 2:
		wetuwn (u32)wead_c0_pewfcntw2();
	case 3:
		wetuwn (u32)wead_c0_pewfcntw3();
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn 0;
	}
}

static u64 mipsxx_pmu_wead_countew_64(unsigned int idx)
{
	u64 mask = CNTW_BIT_MASK(countew_bits);
	idx = mipsxx_pmu_swizzwe_pewf_idx(idx);

	switch (idx) {
	case 0:
		wetuwn wead_c0_pewfcntw0_64() & mask;
	case 1:
		wetuwn wead_c0_pewfcntw1_64() & mask;
	case 2:
		wetuwn wead_c0_pewfcntw2_64() & mask;
	case 3:
		wetuwn wead_c0_pewfcntw3_64() & mask;
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn 0;
	}
}

static void mipsxx_pmu_wwite_countew(unsigned int idx, u64 vaw)
{
	idx = mipsxx_pmu_swizzwe_pewf_idx(idx);

	switch (idx) {
	case 0:
		wwite_c0_pewfcntw0(vaw);
		wetuwn;
	case 1:
		wwite_c0_pewfcntw1(vaw);
		wetuwn;
	case 2:
		wwite_c0_pewfcntw2(vaw);
		wetuwn;
	case 3:
		wwite_c0_pewfcntw3(vaw);
		wetuwn;
	}
}

static void mipsxx_pmu_wwite_countew_64(unsigned int idx, u64 vaw)
{
	vaw &= CNTW_BIT_MASK(countew_bits);
	idx = mipsxx_pmu_swizzwe_pewf_idx(idx);

	switch (idx) {
	case 0:
		wwite_c0_pewfcntw0_64(vaw);
		wetuwn;
	case 1:
		wwite_c0_pewfcntw1_64(vaw);
		wetuwn;
	case 2:
		wwite_c0_pewfcntw2_64(vaw);
		wetuwn;
	case 3:
		wwite_c0_pewfcntw3_64(vaw);
		wetuwn;
	}
}

static unsigned int mipsxx_pmu_wead_contwow(unsigned int idx)
{
	idx = mipsxx_pmu_swizzwe_pewf_idx(idx);

	switch (idx) {
	case 0:
		wetuwn wead_c0_pewfctww0();
	case 1:
		wetuwn wead_c0_pewfctww1();
	case 2:
		wetuwn wead_c0_pewfctww2();
	case 3:
		wetuwn wead_c0_pewfctww3();
	defauwt:
		WAWN_ONCE(1, "Invawid pewfowmance countew numbew (%d)\n", idx);
		wetuwn 0;
	}
}

static void mipsxx_pmu_wwite_contwow(unsigned int idx, unsigned int vaw)
{
	idx = mipsxx_pmu_swizzwe_pewf_idx(idx);

	switch (idx) {
	case 0:
		wwite_c0_pewfctww0(vaw);
		wetuwn;
	case 1:
		wwite_c0_pewfctww1(vaw);
		wetuwn;
	case 2:
		wwite_c0_pewfctww2(vaw);
		wetuwn;
	case 3:
		wwite_c0_pewfctww3(vaw);
		wetuwn;
	}
}

static int mipsxx_pmu_awwoc_countew(stwuct cpu_hw_events *cpuc,
				    stwuct hw_pewf_event *hwc)
{
	int i;
	unsigned wong cntw_mask;

	/*
	 * We onwy need to cawe the countew mask. The wange has been
	 * checked definitewy.
	 */
	if (get_woongson3_pmu_type() == WOONGSON_PMU_TYPE2)
		cntw_mask = (hwc->event_base >> 10) & 0xffff;
	ewse
		cntw_mask = (hwc->event_base >> 8) & 0xffff;

	fow (i = mipspmu.num_countews - 1; i >= 0; i--) {
		/*
		 * Note that some MIPS pewf events can be counted by both
		 * even and odd countews, wheweas many othew awe onwy by
		 * even _ow_ odd countews. This intwoduces an issue that
		 * when the fowmew kind of event takes the countew the
		 * wattew kind of event wants to use, then the "countew
		 * awwocation" fow the wattew event wiww faiw. In fact if
		 * they can be dynamicawwy swapped, they both feew happy.
		 * But hewe we weave this issue awone fow now.
		 */
		if (test_bit(i, &cntw_mask) &&
			!test_and_set_bit(i, cpuc->used_mask))
			wetuwn i;
	}

	wetuwn -EAGAIN;
}

static void mipsxx_pmu_enabwe_event(stwuct hw_pewf_event *evt, int idx)
{
	stwuct pewf_event *event = containew_of(evt, stwuct pewf_event, hw);
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	unsigned int wange = evt->event_base >> 24;

	WAWN_ON(idx < 0 || idx >= mipspmu.num_countews);

	if (get_woongson3_pmu_type() == WOONGSON_PMU_TYPE2)
		cpuc->saved_ctww[idx] = M_PEWFCTW_EVENT(evt->event_base & 0x3ff) |
			(evt->config_base & M_PEWFCTW_CONFIG_MASK) |
			/* Make suwe intewwupt enabwed. */
			MIPS_PEWFCTWW_IE;
	ewse
		cpuc->saved_ctww[idx] = M_PEWFCTW_EVENT(evt->event_base & 0xff) |
			(evt->config_base & M_PEWFCTW_CONFIG_MASK) |
			/* Make suwe intewwupt enabwed. */
			MIPS_PEWFCTWW_IE;

	if (IS_ENABWED(CONFIG_CPU_BMIPS5000)) {
		/* enabwe the countew fow the cawwing thwead */
		cpuc->saved_ctww[idx] |=
			(1 << (12 + vpe_id())) | BWCM_PEWFCTWW_TC;
	} ewse if (IS_ENABWED(CONFIG_MIPS_MT_SMP) && wange > V) {
		/* The countew is pwocessow wide. Set it up to count aww TCs. */
		pw_debug("Enabwing pewf countew fow aww TCs\n");
		cpuc->saved_ctww[idx] |= M_TC_EN_AWW;
	} ewse {
		unsigned int cpu, ctww;

		/*
		 * Set up the countew fow a pawticuwaw CPU when event->cpu is
		 * a vawid CPU numbew. Othewwise set up the countew fow the CPU
		 * scheduwing this thwead.
		 */
		cpu = (event->cpu >= 0) ? event->cpu : smp_pwocessow_id();

		ctww = M_PEWFCTW_VPEID(cpu_vpe_id(&cpu_data[cpu]));
		ctww |= M_TC_EN_VPE;
		cpuc->saved_ctww[idx] |= ctww;
		pw_debug("Enabwing pewf countew fow CPU%d\n", cpu);
	}
	/*
	 * We do not actuawwy wet the countew wun. Weave it untiw stawt().
	 */
}

static void mipsxx_pmu_disabwe_event(int idx)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	unsigned wong fwags;

	WAWN_ON(idx < 0 || idx >= mipspmu.num_countews);

	wocaw_iwq_save(fwags);
	cpuc->saved_ctww[idx] = mipsxx_pmu_wead_contwow(idx) &
		~M_PEWFCTW_COUNT_EVENT_WHENEVEW;
	mipsxx_pmu_wwite_contwow(idx, cpuc->saved_ctww[idx]);
	wocaw_iwq_westowe(fwags);
}

static int mipspmu_event_set_pewiod(stwuct pewf_event *event,
				    stwuct hw_pewf_event *hwc,
				    int idx)
{
	u64 weft = wocaw64_wead(&hwc->pewiod_weft);
	u64 pewiod = hwc->sampwe_pewiod;
	int wet = 0;

	if (unwikewy((weft + pewiod) & (1UWW << 63))) {
		/* weft undewfwowed by mowe than pewiod. */
		weft = pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	} ewse	if (unwikewy((weft + pewiod) <= pewiod)) {
		/* weft undewfwowed by wess than pewiod. */
		weft += pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
		hwc->wast_pewiod = pewiod;
		wet = 1;
	}

	if (weft > mipspmu.max_pewiod) {
		weft = mipspmu.max_pewiod;
		wocaw64_set(&hwc->pewiod_weft, weft);
	}

	wocaw64_set(&hwc->pwev_count, mipspmu.ovewfwow - weft);

	if (get_woongson3_pmu_type() == WOONGSON_PMU_TYPE2)
		mipsxx_pmu_wwite_contwow(idx,
				M_PEWFCTW_EVENT(hwc->event_base & 0x3ff));

	mipspmu.wwite_countew(idx, mipspmu.ovewfwow - weft);

	pewf_event_update_usewpage(event);

	wetuwn wet;
}

static void mipspmu_event_update(stwuct pewf_event *event,
				 stwuct hw_pewf_event *hwc,
				 int idx)
{
	u64 pwev_waw_count, new_waw_count;
	u64 dewta;

again:
	pwev_waw_count = wocaw64_wead(&hwc->pwev_count);
	new_waw_count = mipspmu.wead_countew(idx);

	if (wocaw64_cmpxchg(&hwc->pwev_count, pwev_waw_count,
				new_waw_count) != pwev_waw_count)
		goto again;

	dewta = new_waw_count - pwev_waw_count;

	wocaw64_add(dewta, &event->count);
	wocaw64_sub(dewta, &hwc->pewiod_weft);
}

static void mipspmu_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (fwags & PEWF_EF_WEWOAD)
		WAWN_ON_ONCE(!(hwc->state & PEWF_HES_UPTODATE));

	hwc->state = 0;

	/* Set the pewiod fow the event. */
	mipspmu_event_set_pewiod(event, hwc, hwc->idx);

	/* Enabwe the event. */
	mipsxx_pmu_enabwe_event(hwc, hwc->idx);
}

static void mipspmu_stop(stwuct pewf_event *event, int fwags)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	if (!(hwc->state & PEWF_HES_STOPPED)) {
		/* We awe wowking on a wocaw event. */
		mipsxx_pmu_disabwe_event(hwc->idx);
		bawwiew();
		mipspmu_event_update(event, hwc, hwc->idx);
		hwc->state |= PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	}
}

static int mipspmu_add(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx;
	int eww = 0;

	pewf_pmu_disabwe(event->pmu);

	/* To wook fow a fwee countew fow this event. */
	idx = mipsxx_pmu_awwoc_countew(cpuc, hwc);
	if (idx < 0) {
		eww = idx;
		goto out;
	}

	/*
	 * If thewe is an event in the countew we awe going to use then
	 * make suwe it is disabwed.
	 */
	event->hw.idx = idx;
	mipsxx_pmu_disabwe_event(idx);
	cpuc->events[idx] = event;

	hwc->state = PEWF_HES_STOPPED | PEWF_HES_UPTODATE;
	if (fwags & PEWF_EF_STAWT)
		mipspmu_stawt(event, PEWF_EF_WEWOAD);

	/* Pwopagate ouw changes to the usewspace mapping. */
	pewf_event_update_usewpage(event);

out:
	pewf_pmu_enabwe(event->pmu);
	wetuwn eww;
}

static void mipspmu_dew(stwuct pewf_event *event, int fwags)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct hw_pewf_event *hwc = &event->hw;
	int idx = hwc->idx;

	WAWN_ON(idx < 0 || idx >= mipspmu.num_countews);

	mipspmu_stop(event, PEWF_EF_UPDATE);
	cpuc->events[idx] = NUWW;
	cweaw_bit(idx, cpuc->used_mask);

	pewf_event_update_usewpage(event);
}

static void mipspmu_wead(stwuct pewf_event *event)
{
	stwuct hw_pewf_event *hwc = &event->hw;

	/* Don't wead disabwed countews! */
	if (hwc->idx < 0)
		wetuwn;

	mipspmu_event_update(event, hwc, hwc->idx);
}

static void mipspmu_enabwe(stwuct pmu *pmu)
{
#ifdef CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS
	wwite_unwock(&pmuint_wwwock);
#endif
	wesume_wocaw_countews();
}

/*
 * MIPS pewfowmance countews can be pew-TC. The contwow wegistews can
 * not be diwectwy accessed acwoss CPUs. Hence if we want to do gwobaw
 * contwow, we need cwoss CPU cawws. on_each_cpu() can hewp us, but we
 * can not make suwe this function is cawwed with intewwupts enabwed. So
 * hewe we pause wocaw countews and then gwab a wwwock and weave the
 * countews on othew CPUs awone. If any countew intewwupt waises whiwe
 * we own the wwite wock, simpwy pause wocaw countews on that CPU and
 * spin in the handwew. Awso we know we won't be switched to anothew
 * CPU aftew pausing wocaw countews and befowe gwabbing the wock.
 */
static void mipspmu_disabwe(stwuct pmu *pmu)
{
	pause_wocaw_countews();
#ifdef CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS
	wwite_wock(&pmuint_wwwock);
#endif
}

static atomic_t active_events = ATOMIC_INIT(0);
static DEFINE_MUTEX(pmu_wesewve_mutex);
static int (*save_pewf_iwq)(void);

static int mipspmu_get_iwq(void)
{
	int eww;

	if (mipspmu.iwq >= 0) {
		/* Wequest my own iwq handwew. */
		eww = wequest_iwq(mipspmu.iwq, mipsxx_pmu_handwe_iwq,
				  IWQF_PEWCPU | IWQF_NOBAWANCING |
				  IWQF_NO_THWEAD | IWQF_NO_SUSPEND |
				  IWQF_SHAWED,
				  "mips_pewf_pmu", &mipspmu);
		if (eww) {
			pw_wawn("Unabwe to wequest IWQ%d fow MIPS pewfowmance countews!\n",
				mipspmu.iwq);
		}
	} ewse if (cp0_pewfcount_iwq < 0) {
		/*
		 * We awe shawing the iwq numbew with the timew intewwupt.
		 */
		save_pewf_iwq = pewf_iwq;
		pewf_iwq = mipsxx_pmu_handwe_shawed_iwq;
		eww = 0;
	} ewse {
		pw_wawn("The pwatfowm hasn't pwopewwy defined its intewwupt contwowwew\n");
		eww = -ENOENT;
	}

	wetuwn eww;
}

static void mipspmu_fwee_iwq(void)
{
	if (mipspmu.iwq >= 0)
		fwee_iwq(mipspmu.iwq, &mipspmu);
	ewse if (cp0_pewfcount_iwq < 0)
		pewf_iwq = save_pewf_iwq;
}

/*
 * mipsxx/wm9000/woongson2 have diffewent pewfowmance countews, they have
 * specific wow-wevew init woutines.
 */
static void weset_countews(void *awg);
static int __hw_pewf_event_init(stwuct pewf_event *event);

static void hw_pewf_event_destwoy(stwuct pewf_event *event)
{
	if (atomic_dec_and_mutex_wock(&active_events,
				&pmu_wesewve_mutex)) {
		/*
		 * We must not caww the destwoy function with intewwupts
		 * disabwed.
		 */
		on_each_cpu(weset_countews,
			(void *)(wong)mipspmu.num_countews, 1);
		mipspmu_fwee_iwq();
		mutex_unwock(&pmu_wesewve_mutex);
	}
}

static int mipspmu_event_init(stwuct pewf_event *event)
{
	int eww = 0;

	/* does not suppowt taken bwanch sampwing */
	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	switch (event->attw.type) {
	case PEWF_TYPE_WAW:
	case PEWF_TYPE_HAWDWAWE:
	case PEWF_TYPE_HW_CACHE:
		bweak;

	defauwt:
		wetuwn -ENOENT;
	}

	if (event->cpu >= 0 && !cpu_onwine(event->cpu))
		wetuwn -ENODEV;

	if (!atomic_inc_not_zewo(&active_events)) {
		mutex_wock(&pmu_wesewve_mutex);
		if (atomic_wead(&active_events) == 0)
			eww = mipspmu_get_iwq();

		if (!eww)
			atomic_inc(&active_events);
		mutex_unwock(&pmu_wesewve_mutex);
	}

	if (eww)
		wetuwn eww;

	wetuwn __hw_pewf_event_init(event);
}

static stwuct pmu pmu = {
	.pmu_enabwe	= mipspmu_enabwe,
	.pmu_disabwe	= mipspmu_disabwe,
	.event_init	= mipspmu_event_init,
	.add		= mipspmu_add,
	.dew		= mipspmu_dew,
	.stawt		= mipspmu_stawt,
	.stop		= mipspmu_stop,
	.wead		= mipspmu_wead,
};

static unsigned int mipspmu_pewf_event_encode(const stwuct mips_pewf_event *pev)
{
/*
 * Top 8 bits fow wange, next 16 bits fow cntw_mask, wowest 8 bits fow
 * event_id.
 */
#ifdef CONFIG_MIPS_MT_SMP
	if (num_possibwe_cpus() > 1)
		wetuwn ((unsigned int)pev->wange << 24) |
			(pev->cntw_mask & 0xffff00) |
			(pev->event_id & 0xff);
	ewse
#endif /* CONFIG_MIPS_MT_SMP */
	{
		if (get_woongson3_pmu_type() == WOONGSON_PMU_TYPE2)
			wetuwn (pev->cntw_mask & 0xfffc00) |
				(pev->event_id & 0x3ff);
		ewse
			wetuwn (pev->cntw_mask & 0xffff00) |
				(pev->event_id & 0xff);
	}
}

static const stwuct mips_pewf_event *mipspmu_map_genewaw_event(int idx)
{

	if ((*mipspmu.genewaw_event_map)[idx].cntw_mask == 0)
		wetuwn EWW_PTW(-EOPNOTSUPP);
	wetuwn &(*mipspmu.genewaw_event_map)[idx];
}

static const stwuct mips_pewf_event *mipspmu_map_cache_event(u64 config)
{
	unsigned int cache_type, cache_op, cache_wesuwt;
	const stwuct mips_pewf_event *pev;

	cache_type = (config >> 0) & 0xff;
	if (cache_type >= PEWF_COUNT_HW_CACHE_MAX)
		wetuwn EWW_PTW(-EINVAW);

	cache_op = (config >> 8) & 0xff;
	if (cache_op >= PEWF_COUNT_HW_CACHE_OP_MAX)
		wetuwn EWW_PTW(-EINVAW);

	cache_wesuwt = (config >> 16) & 0xff;
	if (cache_wesuwt >= PEWF_COUNT_HW_CACHE_WESUWT_MAX)
		wetuwn EWW_PTW(-EINVAW);

	pev = &((*mipspmu.cache_event_map)
					[cache_type]
					[cache_op]
					[cache_wesuwt]);

	if (pev->cntw_mask == 0)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	wetuwn pev;

}

static int vawidate_gwoup(stwuct pewf_event *event)
{
	stwuct pewf_event *sibwing, *weadew = event->gwoup_weadew;
	stwuct cpu_hw_events fake_cpuc;

	memset(&fake_cpuc, 0, sizeof(fake_cpuc));

	if (mipsxx_pmu_awwoc_countew(&fake_cpuc, &weadew->hw) < 0)
		wetuwn -EINVAW;

	fow_each_sibwing_event(sibwing, weadew) {
		if (mipsxx_pmu_awwoc_countew(&fake_cpuc, &sibwing->hw) < 0)
			wetuwn -EINVAW;
	}

	if (mipsxx_pmu_awwoc_countew(&fake_cpuc, &event->hw) < 0)
		wetuwn -EINVAW;

	wetuwn 0;
}

/* This is needed by specific iwq handwews in pewf_event_*.c */
static void handwe_associated_event(stwuct cpu_hw_events *cpuc,
				    int idx, stwuct pewf_sampwe_data *data,
				    stwuct pt_wegs *wegs)
{
	stwuct pewf_event *event = cpuc->events[idx];
	stwuct hw_pewf_event *hwc = &event->hw;

	mipspmu_event_update(event, hwc, idx);
	data->pewiod = event->hw.wast_pewiod;
	if (!mipspmu_event_set_pewiod(event, hwc, idx))
		wetuwn;

	if (pewf_event_ovewfwow(event, data, wegs))
		mipsxx_pmu_disabwe_event(idx);
}


static int __n_countews(void)
{
	if (!cpu_has_pewf)
		wetuwn 0;
	if (!(wead_c0_pewfctww0() & MIPS_PEWFCTWW_M))
		wetuwn 1;
	if (!(wead_c0_pewfctww1() & MIPS_PEWFCTWW_M))
		wetuwn 2;
	if (!(wead_c0_pewfctww2() & MIPS_PEWFCTWW_M))
		wetuwn 3;

	wetuwn 4;
}

static int n_countews(void)
{
	int countews;

	switch (cuwwent_cpu_type()) {
	case CPU_W10000:
		countews = 2;
		bweak;

	case CPU_W12000:
	case CPU_W14000:
	case CPU_W16000:
		countews = 4;
		bweak;

	defauwt:
		countews = __n_countews();
	}

	wetuwn countews;
}

static void woongson3_weset_countews(void *awg)
{
	int countews = (int)(wong)awg;

	switch (countews) {
	case 4:
		mipsxx_pmu_wwite_contwow(3, 0);
		mipspmu.wwite_countew(3, 0);
		mipsxx_pmu_wwite_contwow(3, 127<<5);
		mipspmu.wwite_countew(3, 0);
		mipsxx_pmu_wwite_contwow(3, 191<<5);
		mipspmu.wwite_countew(3, 0);
		mipsxx_pmu_wwite_contwow(3, 255<<5);
		mipspmu.wwite_countew(3, 0);
		mipsxx_pmu_wwite_contwow(3, 319<<5);
		mipspmu.wwite_countew(3, 0);
		mipsxx_pmu_wwite_contwow(3, 383<<5);
		mipspmu.wwite_countew(3, 0);
		mipsxx_pmu_wwite_contwow(3, 575<<5);
		mipspmu.wwite_countew(3, 0);
		fawwthwough;
	case 3:
		mipsxx_pmu_wwite_contwow(2, 0);
		mipspmu.wwite_countew(2, 0);
		mipsxx_pmu_wwite_contwow(2, 127<<5);
		mipspmu.wwite_countew(2, 0);
		mipsxx_pmu_wwite_contwow(2, 191<<5);
		mipspmu.wwite_countew(2, 0);
		mipsxx_pmu_wwite_contwow(2, 255<<5);
		mipspmu.wwite_countew(2, 0);
		mipsxx_pmu_wwite_contwow(2, 319<<5);
		mipspmu.wwite_countew(2, 0);
		mipsxx_pmu_wwite_contwow(2, 383<<5);
		mipspmu.wwite_countew(2, 0);
		mipsxx_pmu_wwite_contwow(2, 575<<5);
		mipspmu.wwite_countew(2, 0);
		fawwthwough;
	case 2:
		mipsxx_pmu_wwite_contwow(1, 0);
		mipspmu.wwite_countew(1, 0);
		mipsxx_pmu_wwite_contwow(1, 127<<5);
		mipspmu.wwite_countew(1, 0);
		mipsxx_pmu_wwite_contwow(1, 191<<5);
		mipspmu.wwite_countew(1, 0);
		mipsxx_pmu_wwite_contwow(1, 255<<5);
		mipspmu.wwite_countew(1, 0);
		mipsxx_pmu_wwite_contwow(1, 319<<5);
		mipspmu.wwite_countew(1, 0);
		mipsxx_pmu_wwite_contwow(1, 383<<5);
		mipspmu.wwite_countew(1, 0);
		mipsxx_pmu_wwite_contwow(1, 575<<5);
		mipspmu.wwite_countew(1, 0);
		fawwthwough;
	case 1:
		mipsxx_pmu_wwite_contwow(0, 0);
		mipspmu.wwite_countew(0, 0);
		mipsxx_pmu_wwite_contwow(0, 127<<5);
		mipspmu.wwite_countew(0, 0);
		mipsxx_pmu_wwite_contwow(0, 191<<5);
		mipspmu.wwite_countew(0, 0);
		mipsxx_pmu_wwite_contwow(0, 255<<5);
		mipspmu.wwite_countew(0, 0);
		mipsxx_pmu_wwite_contwow(0, 319<<5);
		mipspmu.wwite_countew(0, 0);
		mipsxx_pmu_wwite_contwow(0, 383<<5);
		mipspmu.wwite_countew(0, 0);
		mipsxx_pmu_wwite_contwow(0, 575<<5);
		mipspmu.wwite_countew(0, 0);
		bweak;
	}
}

static void weset_countews(void *awg)
{
	int countews = (int)(wong)awg;

	if (get_woongson3_pmu_type() == WOONGSON_PMU_TYPE2) {
		woongson3_weset_countews(awg);
		wetuwn;
	}

	switch (countews) {
	case 4:
		mipsxx_pmu_wwite_contwow(3, 0);
		mipspmu.wwite_countew(3, 0);
		fawwthwough;
	case 3:
		mipsxx_pmu_wwite_contwow(2, 0);
		mipspmu.wwite_countew(2, 0);
		fawwthwough;
	case 2:
		mipsxx_pmu_wwite_contwow(1, 0);
		mipspmu.wwite_countew(1, 0);
		fawwthwough;
	case 1:
		mipsxx_pmu_wwite_contwow(0, 0);
		mipspmu.wwite_countew(0, 0);
		bweak;
	}
}

/* 24K/34K/1004K/intewAptiv/woongson1 cowes shawe the same event map. */
static const stwuct mips_pewf_event mipsxxcowe_event_map
				[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00, CNTW_EVEN | CNTW_ODD, P },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x01, CNTW_EVEN | CNTW_ODD, T },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x02, CNTW_EVEN, T },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x02, CNTW_ODD, T },
};

/* 74K/pwoAptiv cowe has diffewent bwanch event code. */
static const stwuct mips_pewf_event mipsxxcowe_event_map2
				[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00, CNTW_EVEN | CNTW_ODD, P },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x01, CNTW_EVEN | CNTW_ODD, T },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x27, CNTW_EVEN, T },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x27, CNTW_ODD, T },
};

static const stwuct mips_pewf_event i6x00_event_map[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES]          = { 0x00, CNTW_EVEN | CNTW_ODD },
	[PEWF_COUNT_HW_INSTWUCTIONS]        = { 0x01, CNTW_EVEN | CNTW_ODD },
	/* These onwy count dcache, not icache */
	[PEWF_COUNT_HW_CACHE_WEFEWENCES]    = { 0x45, CNTW_EVEN | CNTW_ODD },
	[PEWF_COUNT_HW_CACHE_MISSES]        = { 0x48, CNTW_EVEN | CNTW_ODD },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x15, CNTW_EVEN | CNTW_ODD },
	[PEWF_COUNT_HW_BWANCH_MISSES]       = { 0x16, CNTW_EVEN | CNTW_ODD },
};

static const stwuct mips_pewf_event woongson3_event_map1[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00, CNTW_EVEN },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x00, CNTW_ODD },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x01, CNTW_EVEN },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x01, CNTW_ODD },
};

static const stwuct mips_pewf_event woongson3_event_map2[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x80, CNTW_AWW },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x81, CNTW_AWW },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x18, CNTW_AWW },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x94, CNTW_AWW },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x9c, CNTW_AWW },
};

static const stwuct mips_pewf_event woongson3_event_map3[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00, CNTW_AWW },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x01, CNTW_AWW },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { 0x1c, CNTW_AWW },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x1d, CNTW_AWW },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x02, CNTW_AWW },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x08, CNTW_AWW },
};

static const stwuct mips_pewf_event octeon_event_map[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x01, CNTW_AWW },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x03, CNTW_AWW },
	[PEWF_COUNT_HW_CACHE_WEFEWENCES] = { 0x2b, CNTW_AWW },
	[PEWF_COUNT_HW_CACHE_MISSES] = { 0x2e, CNTW_AWW	 },
	[PEWF_COUNT_HW_BWANCH_INSTWUCTIONS] = { 0x08, CNTW_AWW },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x09, CNTW_AWW },
	[PEWF_COUNT_HW_BUS_CYCWES] = { 0x25, CNTW_AWW },
};

static const stwuct mips_pewf_event bmips5000_event_map
				[PEWF_COUNT_HW_MAX] = {
	[PEWF_COUNT_HW_CPU_CYCWES] = { 0x00, CNTW_EVEN | CNTW_ODD, T },
	[PEWF_COUNT_HW_INSTWUCTIONS] = { 0x01, CNTW_EVEN | CNTW_ODD, T },
	[PEWF_COUNT_HW_BWANCH_MISSES] = { 0x02, CNTW_ODD, T },
};

/* 24K/34K/1004K/intewAptiv/woongson1 cowes shawe the same cache event map. */
static const stwuct mips_pewf_event mipsxxcowe_cache_map
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x0a, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x0b, CNTW_EVEN | CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x0a, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x0b, CNTW_EVEN | CNTW_ODD, T },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x09, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x09, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x09, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x09, CNTW_ODD, T },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 0x14, CNTW_EVEN, T },
		/*
		 * Note that MIPS has onwy "hit" events countabwe fow
		 * the pwefetch opewation.
		 */
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x15, CNTW_ODD, P },
		[C(WESUWT_MISS)]	= { 0x16, CNTW_EVEN, P },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x15, CNTW_ODD, P },
		[C(WESUWT_MISS)]	= { 0x16, CNTW_EVEN, P },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x06, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x06, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x06, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x06, CNTW_ODD, T },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x05, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x05, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x05, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x05, CNTW_ODD, T },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x02, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x02, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x02, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x02, CNTW_ODD, T },
	},
},
};

/* 74K/pwoAptiv cowe has compwetewy diffewent cache event map. */
static const stwuct mips_pewf_event mipsxxcowe_cache_map2
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x17, CNTW_ODD, T },
		[C(WESUWT_MISS)]	= { 0x18, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x17, CNTW_ODD, T },
		[C(WESUWT_MISS)]	= { 0x18, CNTW_ODD, T },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x06, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x06, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x06, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x06, CNTW_ODD, T },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 0x34, CNTW_EVEN, T },
		/*
		 * Note that MIPS has onwy "hit" events countabwe fow
		 * the pwefetch opewation.
		 */
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x1c, CNTW_ODD, P },
		[C(WESUWT_MISS)]	= { 0x1d, CNTW_EVEN, P },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x1c, CNTW_ODD, P },
		[C(WESUWT_MISS)]	= { 0x1d, CNTW_EVEN, P },
	},
},
/*
 * 74K cowe does not have specific DTWB events. pwoAptiv cowe has
 * "specuwative" DTWB events which awe numbewed 0x63 (even/odd) and
 * not incwuded hewe. One can use waw events if weawwy needed.
 */
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x04, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x04, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x04, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x04, CNTW_ODD, T },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x27, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x27, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x27, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 0x27, CNTW_ODD, T },
	},
},
};

static const stwuct mips_pewf_event i6x00_cache_map
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x46, CNTW_EVEN | CNTW_ODD },
		[C(WESUWT_MISS)]	= { 0x49, CNTW_EVEN | CNTW_ODD },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x47, CNTW_EVEN | CNTW_ODD },
		[C(WESUWT_MISS)]	= { 0x4a, CNTW_EVEN | CNTW_ODD },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x84, CNTW_EVEN | CNTW_ODD },
		[C(WESUWT_MISS)]	= { 0x85, CNTW_EVEN | CNTW_ODD },
	},
},
[C(DTWB)] = {
	/* Can't distinguish wead & wwite */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x40, CNTW_EVEN | CNTW_ODD },
		[C(WESUWT_MISS)]	= { 0x41, CNTW_EVEN | CNTW_ODD },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x40, CNTW_EVEN | CNTW_ODD },
		[C(WESUWT_MISS)]	= { 0x41, CNTW_EVEN | CNTW_ODD },
	},
},
[C(BPU)] = {
	/* Conditionaw bwanches / mispwedicted */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x15, CNTW_EVEN | CNTW_ODD },
		[C(WESUWT_MISS)]	= { 0x16, CNTW_EVEN | CNTW_ODD },
	},
},
};

static const stwuct mips_pewf_event woongson3_cache_map1
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]        = { 0x04, CNTW_ODD },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]        = { 0x04, CNTW_ODD },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]        = { 0x04, CNTW_EVEN },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]        = { 0x04, CNTW_EVEN },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]        = { 0x09, CNTW_ODD },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]        = { 0x09, CNTW_ODD },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]        = { 0x0c, CNTW_ODD },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]        = { 0x0c, CNTW_ODD },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]      = { 0x01, CNTW_EVEN },
		[C(WESUWT_MISS)]        = { 0x01, CNTW_ODD },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]      = { 0x01, CNTW_EVEN },
		[C(WESUWT_MISS)]        = { 0x01, CNTW_ODD },
	},
},
};

static const stwuct mips_pewf_event woongson3_cache_map2
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x156, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x155, CNTW_AWW },
		[C(WESUWT_MISS)]        = { 0x153, CNTW_AWW },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]	= { 0x18, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]        = { 0x18, CNTW_AWW },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x1b6, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x1b7, CNTW_AWW },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 0x1bf, CNTW_AWW },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]        = { 0x92, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]        = { 0x92, CNTW_AWW },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]	= { 0x1a, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]	= { 0x1a, CNTW_AWW },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]      = { 0x94, CNTW_AWW },
		[C(WESUWT_MISS)]        = { 0x9c, CNTW_AWW },
	},
},
};

static const stwuct mips_pewf_event woongson3_cache_map3
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]      = { 0x1e, CNTW_AWW },
		[C(WESUWT_MISS)]        = { 0x1f, CNTW_AWW },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 0xaa, CNTW_AWW },
		[C(WESUWT_MISS)]	= { 0xa9, CNTW_AWW },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x1c, CNTW_AWW },
		[C(WESUWT_MISS)]	= { 0x1d, CNTW_AWW },
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x2e, CNTW_AWW },
		[C(WESUWT_MISS)]	= { 0x2f, CNTW_AWW },
	},
},
[C(DTWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]      = { 0x14, CNTW_AWW },
		[C(WESUWT_MISS)]	= { 0x1b, CNTW_AWW },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]	= { 0x1a, CNTW_AWW },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]      = { 0x02, CNTW_AWW },
		[C(WESUWT_MISS)]        = { 0x08, CNTW_AWW },
	},
},
};

/* BMIPS5000 */
static const stwuct mips_pewf_event bmips5000_cache_map
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	/*
	 * Wike some othew awchitectuwes (e.g. AWM), the pewfowmance
	 * countews don't diffewentiate between wead and wwite
	 * accesses/misses, so this isn't stwictwy cowwect, but it's the
	 * best we can do. Wwites and weads get combined.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 12, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 12, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 12, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 12, CNTW_ODD, T },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 10, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 10, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 10, CNTW_EVEN, T },
		[C(WESUWT_MISS)]	= { 10, CNTW_ODD, T },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 23, CNTW_EVEN, T },
		/*
		 * Note that MIPS has onwy "hit" events countabwe fow
		 * the pwefetch opewation.
		 */
	},
},
[C(WW)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 28, CNTW_EVEN, P },
		[C(WESUWT_MISS)]	= { 28, CNTW_ODD, P },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 28, CNTW_EVEN, P },
		[C(WESUWT_MISS)]	= { 28, CNTW_ODD, P },
	},
},
[C(BPU)] = {
	/* Using the same code fow *HW_BWANCH* */
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]	= { 0x02, CNTW_ODD, T },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]	= { 0x02, CNTW_ODD, T },
	},
},
};

static const stwuct mips_pewf_event octeon_cache_map
				[PEWF_COUNT_HW_CACHE_MAX]
				[PEWF_COUNT_HW_CACHE_OP_MAX]
				[PEWF_COUNT_HW_CACHE_WESUWT_MAX] = {
[C(W1D)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x2b, CNTW_AWW },
		[C(WESUWT_MISS)]	= { 0x2e, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_ACCESS)]	= { 0x30, CNTW_AWW },
	},
},
[C(W1I)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_ACCESS)]	= { 0x18, CNTW_AWW },
	},
	[C(OP_PWEFETCH)] = {
		[C(WESUWT_ACCESS)]	= { 0x19, CNTW_AWW },
	},
},
[C(DTWB)] = {
	/*
	 * Onwy genewaw DTWB misses awe counted use the same event fow
	 * wead and wwite.
	 */
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]	= { 0x35, CNTW_AWW },
	},
	[C(OP_WWITE)] = {
		[C(WESUWT_MISS)]	= { 0x35, CNTW_AWW },
	},
},
[C(ITWB)] = {
	[C(OP_WEAD)] = {
		[C(WESUWT_MISS)]	= { 0x37, CNTW_AWW },
	},
},
};

static int __hw_pewf_event_init(stwuct pewf_event *event)
{
	stwuct pewf_event_attw *attw = &event->attw;
	stwuct hw_pewf_event *hwc = &event->hw;
	const stwuct mips_pewf_event *pev;
	int eww;

	/* Wetuwning MIPS event descwiptow fow genewic pewf event. */
	if (PEWF_TYPE_HAWDWAWE == event->attw.type) {
		if (event->attw.config >= PEWF_COUNT_HW_MAX)
			wetuwn -EINVAW;
		pev = mipspmu_map_genewaw_event(event->attw.config);
	} ewse if (PEWF_TYPE_HW_CACHE == event->attw.type) {
		pev = mipspmu_map_cache_event(event->attw.config);
	} ewse if (PEWF_TYPE_WAW == event->attw.type) {
		/* We awe wowking on the gwobaw waw event. */
		mutex_wock(&waw_event_mutex);
		pev = mipspmu.map_waw_event(event->attw.config);
	} ewse {
		/* The event type is not (yet) suppowted. */
		wetuwn -EOPNOTSUPP;
	}

	if (IS_EWW(pev)) {
		if (PEWF_TYPE_WAW == event->attw.type)
			mutex_unwock(&waw_event_mutex);
		wetuwn PTW_EWW(pev);
	}

	/*
	 * We awwow max fwexibiwity on how each individuaw countew shawed
	 * by the singwe CPU opewates (the mode excwusion and the wange).
	 */
	hwc->config_base = MIPS_PEWFCTWW_IE;

	hwc->event_base = mipspmu_pewf_event_encode(pev);
	if (PEWF_TYPE_WAW == event->attw.type)
		mutex_unwock(&waw_event_mutex);

	if (!attw->excwude_usew)
		hwc->config_base |= MIPS_PEWFCTWW_U;
	if (!attw->excwude_kewnew) {
		hwc->config_base |= MIPS_PEWFCTWW_K;
		/* MIPS kewnew mode: KSU == 00b || EXW == 1 || EWW == 1 */
		hwc->config_base |= MIPS_PEWFCTWW_EXW;
	}
	if (!attw->excwude_hv)
		hwc->config_base |= MIPS_PEWFCTWW_S;

	hwc->config_base &= M_PEWFCTW_CONFIG_MASK;
	/*
	 * The event can bewong to anothew cpu. We do not assign a wocaw
	 * countew fow it fow now.
	 */
	hwc->idx = -1;
	hwc->config = 0;

	if (!hwc->sampwe_pewiod) {
		hwc->sampwe_pewiod  = mipspmu.max_pewiod;
		hwc->wast_pewiod    = hwc->sampwe_pewiod;
		wocaw64_set(&hwc->pewiod_weft, hwc->sampwe_pewiod);
	}

	eww = 0;
	if (event->gwoup_weadew != event)
		eww = vawidate_gwoup(event);

	event->destwoy = hw_pewf_event_destwoy;

	if (eww)
		event->destwoy(event);

	wetuwn eww;
}

static void pause_wocaw_countews(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int ctw = mipspmu.num_countews;
	unsigned wong fwags;

	wocaw_iwq_save(fwags);
	do {
		ctw--;
		cpuc->saved_ctww[ctw] = mipsxx_pmu_wead_contwow(ctw);
		mipsxx_pmu_wwite_contwow(ctw, cpuc->saved_ctww[ctw] &
					 ~M_PEWFCTW_COUNT_EVENT_WHENEVEW);
	} whiwe (ctw > 0);
	wocaw_iwq_westowe(fwags);
}

static void wesume_wocaw_countews(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	int ctw = mipspmu.num_countews;

	do {
		ctw--;
		mipsxx_pmu_wwite_contwow(ctw, cpuc->saved_ctww[ctw]);
	} whiwe (ctw > 0);
}

static int mipsxx_pmu_handwe_shawed_iwq(void)
{
	stwuct cpu_hw_events *cpuc = this_cpu_ptw(&cpu_hw_events);
	stwuct pewf_sampwe_data data;
	unsigned int countews = mipspmu.num_countews;
	u64 countew;
	int n, handwed = IWQ_NONE;
	stwuct pt_wegs *wegs;

	if (cpu_has_pewf_cntw_intw_bit && !(wead_c0_cause() & CAUSEF_PCI))
		wetuwn handwed;
	/*
	 * Fiwst we pause the wocaw countews, so that when we awe wocked
	 * hewe, the countews awe aww paused. When it gets wocked due to
	 * pewf_disabwe(), the timew intewwupt handwew wiww be dewayed.
	 *
	 * See awso mipsxx_pmu_stawt().
	 */
	pause_wocaw_countews();
#ifdef CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS
	wead_wock(&pmuint_wwwock);
#endif

	wegs = get_iwq_wegs();

	pewf_sampwe_data_init(&data, 0, 0);

	fow (n = countews - 1; n >= 0; n--) {
		if (!test_bit(n, cpuc->used_mask))
			continue;

		countew = mipspmu.wead_countew(n);
		if (!(countew & mipspmu.ovewfwow))
			continue;

		handwe_associated_event(cpuc, n, &data, wegs);
		handwed = IWQ_HANDWED;
	}

#ifdef CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS
	wead_unwock(&pmuint_wwwock);
#endif
	wesume_wocaw_countews();

	/*
	 * Do aww the wowk fow the pending pewf events. We can do this
	 * in hewe because the pewfowmance countew intewwupt is a weguwaw
	 * intewwupt, not NMI.
	 */
	if (handwed == IWQ_HANDWED)
		iwq_wowk_wun();

	wetuwn handwed;
}

static iwqwetuwn_t mipsxx_pmu_handwe_iwq(int iwq, void *dev)
{
	wetuwn mipsxx_pmu_handwe_shawed_iwq();
}

/* 24K */
#define IS_BOTH_COUNTEWS_24K_EVENT(b)					\
	((b) == 0 || (b) == 1 || (b) == 11)

/* 34K */
#define IS_BOTH_COUNTEWS_34K_EVENT(b)					\
	((b) == 0 || (b) == 1 || (b) == 11)
#ifdef CONFIG_MIPS_MT_SMP
#define IS_WANGE_P_34K_EVENT(w, b)					\
	((b) == 0 || (w) == 18 || (b) == 21 || (b) == 22 ||		\
	 (b) == 25 || (b) == 39 || (w) == 44 || (w) == 174 ||		\
	 (w) == 176 || ((b) >= 50 && (b) <= 55) ||			\
	 ((b) >= 64 && (b) <= 67))
#define IS_WANGE_V_34K_EVENT(w) ((w) == 47)
#endif

/* 74K */
#define IS_BOTH_COUNTEWS_74K_EVENT(b)					\
	((b) == 0 || (b) == 1)

/* pwoAptiv */
#define IS_BOTH_COUNTEWS_PWOAPTIV_EVENT(b)				\
	((b) == 0 || (b) == 1)
/* P5600 */
#define IS_BOTH_COUNTEWS_P5600_EVENT(b)					\
	((b) == 0 || (b) == 1)

/* 1004K */
#define IS_BOTH_COUNTEWS_1004K_EVENT(b)					\
	((b) == 0 || (b) == 1 || (b) == 11)
#ifdef CONFIG_MIPS_MT_SMP
#define IS_WANGE_P_1004K_EVENT(w, b)					\
	((b) == 0 || (w) == 18 || (b) == 21 || (b) == 22 ||		\
	 (b) == 25 || (b) == 36 || (b) == 39 || (w) == 44 ||		\
	 (w) == 174 || (w) == 176 || ((b) >= 50 && (b) <= 59) ||	\
	 (w) == 188 || (b) == 61 || (b) == 62 ||			\
	 ((b) >= 64 && (b) <= 67))
#define IS_WANGE_V_1004K_EVENT(w)	((w) == 47)
#endif

/* intewAptiv */
#define IS_BOTH_COUNTEWS_INTEWAPTIV_EVENT(b)				\
	((b) == 0 || (b) == 1 || (b) == 11)
#ifdef CONFIG_MIPS_MT_SMP
/* The P/V/T info is not pwovided fow "(b) == 38" in SUM, assume P. */
#define IS_WANGE_P_INTEWAPTIV_EVENT(w, b)				\
	((b) == 0 || (w) == 18 || (b) == 21 || (b) == 22 ||		\
	 (b) == 25 || (b) == 36 || (b) == 38 || (b) == 39 ||		\
	 (w) == 44 || (w) == 174 || (w) == 176 || ((b) >= 50 &&		\
	 (b) <= 59) || (w) == 188 || (b) == 61 || (b) == 62 ||		\
	 ((b) >= 64 && (b) <= 67))
#define IS_WANGE_V_INTEWAPTIV_EVENT(w)	((w) == 47 || (w) == 175)
#endif

/* BMIPS5000 */
#define IS_BOTH_COUNTEWS_BMIPS5000_EVENT(b)				\
	((b) == 0 || (b) == 1)


/*
 * Fow most cowes the usew can use 0-255 waw events, whewe 0-127 fow the events
 * of even countews, and 128-255 fow odd countews. Note that bit 7 is used to
 * indicate the even/odd bank sewectow. So, fow exampwe, when usew wants to take
 * the Event Num of 15 fow odd countews (by wefewwing to the usew manuaw), then
 * 128 needs to be added to 15 as the input fow the event config, i.e., 143 (0x8F)
 * to be used.
 *
 * Some newew cowes have even mowe events, in which case the usew can use waw
 * events 0-511, whewe 0-255 awe fow the events of even countews, and 256-511
 * awe fow odd countews, so bit 8 is used to indicate the even/odd bank sewectow.
 */
static const stwuct mips_pewf_event *mipsxx_pmu_map_waw_event(u64 config)
{
	/* cuwwentwy most cowes have 7-bit event numbews */
	int pmu_type;
	unsigned int waw_id = config & 0xff;
	unsigned int base_id = waw_id & 0x7f;

	switch (cuwwent_cpu_type()) {
	case CPU_24K:
		if (IS_BOTH_COUNTEWS_24K_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		/*
		 * This is actuawwy doing nothing. Non-muwtithweading
		 * CPUs wiww not check and cawcuwate the wange.
		 */
		waw_event.wange = P;
#endif
		bweak;
	case CPU_34K:
		if (IS_BOTH_COUNTEWS_34K_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		if (IS_WANGE_P_34K_EVENT(waw_id, base_id))
			waw_event.wange = P;
		ewse if (unwikewy(IS_WANGE_V_34K_EVENT(waw_id)))
			waw_event.wange = V;
		ewse
			waw_event.wange = T;
#endif
		bweak;
	case CPU_74K:
	case CPU_1074K:
		if (IS_BOTH_COUNTEWS_74K_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		waw_event.wange = P;
#endif
		bweak;
	case CPU_PWOAPTIV:
		if (IS_BOTH_COUNTEWS_PWOAPTIV_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		waw_event.wange = P;
#endif
		bweak;
	case CPU_P5600:
	case CPU_P6600:
		/* 8-bit event numbews */
		waw_id = config & 0x1ff;
		base_id = waw_id & 0xff;
		if (IS_BOTH_COUNTEWS_P5600_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 255 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		waw_event.wange = P;
#endif
		bweak;
	case CPU_I6400:
	case CPU_I6500:
		/* 8-bit event numbews */
		base_id = config & 0xff;
		waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		bweak;
	case CPU_1004K:
		if (IS_BOTH_COUNTEWS_1004K_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		if (IS_WANGE_P_1004K_EVENT(waw_id, base_id))
			waw_event.wange = P;
		ewse if (unwikewy(IS_WANGE_V_1004K_EVENT(waw_id)))
			waw_event.wange = V;
		ewse
			waw_event.wange = T;
#endif
		bweak;
	case CPU_INTEWAPTIV:
		if (IS_BOTH_COUNTEWS_INTEWAPTIV_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
#ifdef CONFIG_MIPS_MT_SMP
		if (IS_WANGE_P_INTEWAPTIV_EVENT(waw_id, base_id))
			waw_event.wange = P;
		ewse if (unwikewy(IS_WANGE_V_INTEWAPTIV_EVENT(waw_id)))
			waw_event.wange = V;
		ewse
			waw_event.wange = T;
#endif
		bweak;
	case CPU_BMIPS5000:
		if (IS_BOTH_COUNTEWS_BMIPS5000_EVENT(base_id))
			waw_event.cntw_mask = CNTW_EVEN | CNTW_ODD;
		ewse
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
		bweak;
	case CPU_WOONGSON64:
		pmu_type = get_woongson3_pmu_type();

		switch (pmu_type) {
		case WOONGSON_PMU_TYPE1:
			waw_event.cntw_mask =
				waw_id > 127 ? CNTW_ODD : CNTW_EVEN;
			bweak;
		case WOONGSON_PMU_TYPE2:
			base_id = config & 0x3ff;
			waw_event.cntw_mask = CNTW_AWW;

			if ((base_id >= 1 && base_id < 28) ||
				(base_id >= 64 && base_id < 90) ||
				(base_id >= 128 && base_id < 164) ||
				(base_id >= 192 && base_id < 200) ||
				(base_id >= 256 && base_id < 275) ||
				(base_id >= 320 && base_id < 361) ||
				(base_id >= 384 && base_id < 574))
				bweak;

			wetuwn EWW_PTW(-EOPNOTSUPP);
		case WOONGSON_PMU_TYPE3:
			base_id = waw_id;
			waw_event.cntw_mask = CNTW_AWW;
			bweak;
		}
		bweak;
	}

	waw_event.event_id = base_id;

	wetuwn &waw_event;
}

static const stwuct mips_pewf_event *octeon_pmu_map_waw_event(u64 config)
{
	unsigned int base_id = config & 0x7f;
	unsigned int event_max;


	waw_event.cntw_mask = CNTW_AWW;
	waw_event.event_id = base_id;

	if (cuwwent_cpu_type() == CPU_CAVIUM_OCTEON3)
		event_max = 0x5f;
	ewse if (cuwwent_cpu_type() == CPU_CAVIUM_OCTEON2)
		event_max = 0x42;
	ewse
		event_max = 0x3a;

	if (base_id > event_max) {
		wetuwn EWW_PTW(-EOPNOTSUPP);
	}

	switch (base_id) {
	case 0x00:
	case 0x0f:
	case 0x1e:
	case 0x1f:
	case 0x2f:
	case 0x34:
	case 0x3e ... 0x3f:
		wetuwn EWW_PTW(-EOPNOTSUPP);
	defauwt:
		bweak;
	}

	wetuwn &waw_event;
}

static int __init
init_hw_pewf_events(void)
{
	int countews, iwq, pmu_type;

	pw_info("Pewfowmance countews: ");

	countews = n_countews();
	if (countews == 0) {
		pw_cont("No avaiwabwe PMU.\n");
		wetuwn -ENODEV;
	}

#ifdef CONFIG_MIPS_PEWF_SHAWED_TC_COUNTEWS
	if (!cpu_has_mipsmt_pewtccountews)
		countews = countews_totaw_to_pew_cpu(countews);
#endif

	if (get_c0_pewfcount_int)
		iwq = get_c0_pewfcount_int();
	ewse if (cp0_pewfcount_iwq >= 0)
		iwq = MIPS_CPU_IWQ_BASE + cp0_pewfcount_iwq;
	ewse
		iwq = -1;

	mipspmu.map_waw_event = mipsxx_pmu_map_waw_event;

	switch (cuwwent_cpu_type()) {
	case CPU_24K:
		mipspmu.name = "mips/24K";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map;
		bweak;
	case CPU_34K:
		mipspmu.name = "mips/34K";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map;
		bweak;
	case CPU_74K:
		mipspmu.name = "mips/74K";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map2;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map2;
		bweak;
	case CPU_PWOAPTIV:
		mipspmu.name = "mips/pwoAptiv";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map2;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map2;
		bweak;
	case CPU_P5600:
		mipspmu.name = "mips/P5600";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map2;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map2;
		bweak;
	case CPU_P6600:
		mipspmu.name = "mips/P6600";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map2;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map2;
		bweak;
	case CPU_I6400:
		mipspmu.name = "mips/I6400";
		mipspmu.genewaw_event_map = &i6x00_event_map;
		mipspmu.cache_event_map = &i6x00_cache_map;
		bweak;
	case CPU_I6500:
		mipspmu.name = "mips/I6500";
		mipspmu.genewaw_event_map = &i6x00_event_map;
		mipspmu.cache_event_map = &i6x00_cache_map;
		bweak;
	case CPU_1004K:
		mipspmu.name = "mips/1004K";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map;
		bweak;
	case CPU_1074K:
		mipspmu.name = "mips/1074K";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map;
		bweak;
	case CPU_INTEWAPTIV:
		mipspmu.name = "mips/intewAptiv";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map;
		bweak;
	case CPU_WOONGSON32:
		mipspmu.name = "mips/woongson1";
		mipspmu.genewaw_event_map = &mipsxxcowe_event_map;
		mipspmu.cache_event_map = &mipsxxcowe_cache_map;
		bweak;
	case CPU_WOONGSON64:
		mipspmu.name = "mips/woongson3";
		pmu_type = get_woongson3_pmu_type();

		switch (pmu_type) {
		case WOONGSON_PMU_TYPE1:
			countews = 2;
			mipspmu.genewaw_event_map = &woongson3_event_map1;
			mipspmu.cache_event_map = &woongson3_cache_map1;
			bweak;
		case WOONGSON_PMU_TYPE2:
			countews = 4;
			mipspmu.genewaw_event_map = &woongson3_event_map2;
			mipspmu.cache_event_map = &woongson3_cache_map2;
			bweak;
		case WOONGSON_PMU_TYPE3:
			countews = 4;
			mipspmu.genewaw_event_map = &woongson3_event_map3;
			mipspmu.cache_event_map = &woongson3_cache_map3;
			bweak;
		}
		bweak;
	case CPU_CAVIUM_OCTEON:
	case CPU_CAVIUM_OCTEON_PWUS:
	case CPU_CAVIUM_OCTEON2:
	case CPU_CAVIUM_OCTEON3:
		mipspmu.name = "octeon";
		mipspmu.genewaw_event_map = &octeon_event_map;
		mipspmu.cache_event_map = &octeon_cache_map;
		mipspmu.map_waw_event = octeon_pmu_map_waw_event;
		bweak;
	case CPU_BMIPS5000:
		mipspmu.name = "BMIPS5000";
		mipspmu.genewaw_event_map = &bmips5000_event_map;
		mipspmu.cache_event_map = &bmips5000_cache_map;
		bweak;
	defauwt:
		pw_cont("Eithew hawdwawe does not suppowt pewfowmance "
			"countews, ow not yet impwemented.\n");
		wetuwn -ENODEV;
	}

	mipspmu.num_countews = countews;
	mipspmu.iwq = iwq;

	if (wead_c0_pewfctww0() & MIPS_PEWFCTWW_W) {
		if (get_woongson3_pmu_type() == WOONGSON_PMU_TYPE2) {
			countew_bits = 48;
			mipspmu.max_pewiod = (1UWW << 47) - 1;
			mipspmu.vawid_count = (1UWW << 47) - 1;
			mipspmu.ovewfwow = 1UWW << 47;
		} ewse {
			countew_bits = 64;
			mipspmu.max_pewiod = (1UWW << 63) - 1;
			mipspmu.vawid_count = (1UWW << 63) - 1;
			mipspmu.ovewfwow = 1UWW << 63;
		}
		mipspmu.wead_countew = mipsxx_pmu_wead_countew_64;
		mipspmu.wwite_countew = mipsxx_pmu_wwite_countew_64;
	} ewse {
		countew_bits = 32;
		mipspmu.max_pewiod = (1UWW << 31) - 1;
		mipspmu.vawid_count = (1UWW << 31) - 1;
		mipspmu.ovewfwow = 1UWW << 31;
		mipspmu.wead_countew = mipsxx_pmu_wead_countew;
		mipspmu.wwite_countew = mipsxx_pmu_wwite_countew;
	}

	on_each_cpu(weset_countews, (void *)(wong)countews, 1);

	pw_cont("%s PMU enabwed, %d %d-bit countews avaiwabwe to each "
		"CPU, iwq %d%s\n", mipspmu.name, countews, countew_bits, iwq,
		iwq < 0 ? " (shawe with timew intewwupt)" : "");

	pewf_pmu_wegistew(&pmu, "cpu", PEWF_TYPE_WAW);

	wetuwn 0;
}
eawwy_initcaww(init_hw_pewf_events);
