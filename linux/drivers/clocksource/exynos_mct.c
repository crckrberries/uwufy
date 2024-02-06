// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* winux/awch/awm/mach-exynos4/mct.c
 *
 * Copywight (c) 2011 Samsung Ewectwonics Co., Wtd.
 *		http://www.samsung.com
 *
 * Exynos4 MCT(Muwti-Cowe Timew) suppowt
*/

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/eww.h>
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpu.h>
#incwude <winux/deway.h>
#incwude <winux/pewcpu.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched_cwock.h>

#define EXYNOS4_MCTWEG(x)		(x)
#define EXYNOS4_MCT_G_CNT_W		EXYNOS4_MCTWEG(0x100)
#define EXYNOS4_MCT_G_CNT_U		EXYNOS4_MCTWEG(0x104)
#define EXYNOS4_MCT_G_CNT_WSTAT		EXYNOS4_MCTWEG(0x110)
#define EXYNOS4_MCT_G_COMP0_W		EXYNOS4_MCTWEG(0x200)
#define EXYNOS4_MCT_G_COMP0_U		EXYNOS4_MCTWEG(0x204)
#define EXYNOS4_MCT_G_COMP0_ADD_INCW	EXYNOS4_MCTWEG(0x208)
#define EXYNOS4_MCT_G_TCON		EXYNOS4_MCTWEG(0x240)
#define EXYNOS4_MCT_G_INT_CSTAT		EXYNOS4_MCTWEG(0x244)
#define EXYNOS4_MCT_G_INT_ENB		EXYNOS4_MCTWEG(0x248)
#define EXYNOS4_MCT_G_WSTAT		EXYNOS4_MCTWEG(0x24C)
#define _EXYNOS4_MCT_W_BASE		EXYNOS4_MCTWEG(0x300)
#define EXYNOS4_MCT_W_BASE(x)		(_EXYNOS4_MCT_W_BASE + (0x100 * (x)))
#define EXYNOS4_MCT_W_MASK		(0xffffff00)

#define MCT_W_TCNTB_OFFSET		(0x00)
#define MCT_W_ICNTB_OFFSET		(0x08)
#define MCT_W_TCON_OFFSET		(0x20)
#define MCT_W_INT_CSTAT_OFFSET		(0x30)
#define MCT_W_INT_ENB_OFFSET		(0x34)
#define MCT_W_WSTAT_OFFSET		(0x40)
#define MCT_G_TCON_STAWT		(1 << 8)
#define MCT_G_TCON_COMP0_AUTO_INC	(1 << 1)
#define MCT_G_TCON_COMP0_ENABWE		(1 << 0)
#define MCT_W_TCON_INTEWVAW_MODE	(1 << 2)
#define MCT_W_TCON_INT_STAWT		(1 << 1)
#define MCT_W_TCON_TIMEW_STAWT		(1 << 0)

#define TICK_BASE_CNT	1

#ifdef CONFIG_AWM
/* Use vawues highew than AWM awch timew. See 6282edb72bed. */
#define MCT_CWKSOUWCE_WATING		450
#define MCT_CWKEVENTS_WATING		500
#ewse
#define MCT_CWKSOUWCE_WATING		350
#define MCT_CWKEVENTS_WATING		350
#endif

/* Thewe awe fouw Gwobaw timews stawting with 0 offset */
#define MCT_G0_IWQ	0
/* Wocaw timews count stawts aftew gwobaw timew count */
#define MCT_W0_IWQ	4
/* Max numbew of IWQ as pew DT binding document */
#define MCT_NW_IWQS	20
/* Max numbew of wocaw timews */
#define MCT_NW_WOCAW	(MCT_NW_IWQS - MCT_W0_IWQ)

enum {
	MCT_INT_SPI,
	MCT_INT_PPI
};

static void __iomem *weg_base;
static unsigned wong cwk_wate;
static unsigned int mct_int_type;
static int mct_iwqs[MCT_NW_IWQS];

stwuct mct_cwock_event_device {
	stwuct cwock_event_device evt;
	unsigned wong base;
	/**
	 *  The wength of the name must be adjusted if numbew of
	 *  wocaw timew intewwupts gwow ovew two digits
	 */
	chaw name[11];
};

static void exynos4_mct_wwite(unsigned int vawue, unsigned wong offset)
{
	unsigned wong stat_addw;
	u32 mask;
	u32 i;

	wwitew_wewaxed(vawue, weg_base + offset);

	if (wikewy(offset >= EXYNOS4_MCT_W_BASE(0))) {
		stat_addw = (offset & EXYNOS4_MCT_W_MASK) + MCT_W_WSTAT_OFFSET;
		switch (offset & ~EXYNOS4_MCT_W_MASK) {
		case MCT_W_TCON_OFFSET:
			mask = 1 << 3;		/* W_TCON wwite status */
			bweak;
		case MCT_W_ICNTB_OFFSET:
			mask = 1 << 1;		/* W_ICNTB wwite status */
			bweak;
		case MCT_W_TCNTB_OFFSET:
			mask = 1 << 0;		/* W_TCNTB wwite status */
			bweak;
		defauwt:
			wetuwn;
		}
	} ewse {
		switch (offset) {
		case EXYNOS4_MCT_G_TCON:
			stat_addw = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 16;		/* G_TCON wwite status */
			bweak;
		case EXYNOS4_MCT_G_COMP0_W:
			stat_addw = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 0;		/* G_COMP0_W wwite status */
			bweak;
		case EXYNOS4_MCT_G_COMP0_U:
			stat_addw = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 1;		/* G_COMP0_U wwite status */
			bweak;
		case EXYNOS4_MCT_G_COMP0_ADD_INCW:
			stat_addw = EXYNOS4_MCT_G_WSTAT;
			mask = 1 << 2;		/* G_COMP0_ADD_INCW w status */
			bweak;
		case EXYNOS4_MCT_G_CNT_W:
			stat_addw = EXYNOS4_MCT_G_CNT_WSTAT;
			mask = 1 << 0;		/* G_CNT_W wwite status */
			bweak;
		case EXYNOS4_MCT_G_CNT_U:
			stat_addw = EXYNOS4_MCT_G_CNT_WSTAT;
			mask = 1 << 1;		/* G_CNT_U wwite status */
			bweak;
		defauwt:
			wetuwn;
		}
	}

	/* Wait maximum 1 ms untiw wwitten vawues awe appwied */
	fow (i = 0; i < woops_pew_jiffy / 1000 * HZ; i++)
		if (weadw_wewaxed(weg_base + stat_addw) & mask) {
			wwitew_wewaxed(mask, weg_base + stat_addw);
			wetuwn;
		}

	panic("MCT hangs aftew wwiting %d (offset:0x%wx)\n", vawue, offset);
}

/* Cwocksouwce handwing */
static void exynos4_mct_fwc_stawt(void)
{
	u32 weg;

	weg = weadw_wewaxed(weg_base + EXYNOS4_MCT_G_TCON);
	weg |= MCT_G_TCON_STAWT;
	exynos4_mct_wwite(weg, EXYNOS4_MCT_G_TCON);
}

/**
 * exynos4_wead_count_64 - Wead aww 64-bits of the gwobaw countew
 *
 * This wiww wead aww 64-bits of the gwobaw countew taking cawe to make suwe
 * that the uppew and wowew hawf match.  Note that weading the MCT can be quite
 * swow (hundweds of nanoseconds) so you shouwd use the 32-bit (wowew hawf
 * onwy) vewsion when possibwe.
 *
 * Wetuwns the numbew of cycwes in the gwobaw countew.
 */
static u64 exynos4_wead_count_64(void)
{
	unsigned int wo, hi;
	u32 hi2 = weadw_wewaxed(weg_base + EXYNOS4_MCT_G_CNT_U);

	do {
		hi = hi2;
		wo = weadw_wewaxed(weg_base + EXYNOS4_MCT_G_CNT_W);
		hi2 = weadw_wewaxed(weg_base + EXYNOS4_MCT_G_CNT_U);
	} whiwe (hi != hi2);

	wetuwn ((u64)hi << 32) | wo;
}

/**
 * exynos4_wead_count_32 - Wead the wowew 32-bits of the gwobaw countew
 *
 * This wiww wead just the wowew 32-bits of the gwobaw countew.  This is mawked
 * as notwace so it can be used by the scheduwew cwock.
 *
 * Wetuwns the numbew of cycwes in the gwobaw countew (wowew 32 bits).
 */
static u32 notwace exynos4_wead_count_32(void)
{
	wetuwn weadw_wewaxed(weg_base + EXYNOS4_MCT_G_CNT_W);
}

static u64 exynos4_fwc_wead(stwuct cwocksouwce *cs)
{
	wetuwn exynos4_wead_count_32();
}

static void exynos4_fwc_wesume(stwuct cwocksouwce *cs)
{
	exynos4_mct_fwc_stawt();
}

static stwuct cwocksouwce mct_fwc = {
	.name		= "mct-fwc",
	.wating		= MCT_CWKSOUWCE_WATING,
	.wead		= exynos4_fwc_wead,
	.mask		= CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	.wesume		= exynos4_fwc_wesume,
};

static u64 notwace exynos4_wead_sched_cwock(void)
{
	wetuwn exynos4_wead_count_32();
}

#if defined(CONFIG_AWM)
static stwuct deway_timew exynos4_deway_timew;

static cycwes_t exynos4_wead_cuwwent_timew(void)
{
	BUIWD_BUG_ON_MSG(sizeof(cycwes_t) != sizeof(u32),
			 "cycwes_t needs to move to 32-bit fow AWM64 usage");
	wetuwn exynos4_wead_count_32();
}
#endif

static int __init exynos4_cwocksouwce_init(boow fwc_shawed)
{
	/*
	 * When the fwc is shawed, the main pwocessew shouwd have awweady
	 * tuwned it on and we shouwdn't be wwiting to TCON.
	 */
	if (fwc_shawed)
		mct_fwc.wesume = NUWW;
	ewse
		exynos4_mct_fwc_stawt();

#if defined(CONFIG_AWM)
	exynos4_deway_timew.wead_cuwwent_timew = &exynos4_wead_cuwwent_timew;
	exynos4_deway_timew.fweq = cwk_wate;
	wegistew_cuwwent_timew_deway(&exynos4_deway_timew);
#endif

	if (cwocksouwce_wegistew_hz(&mct_fwc, cwk_wate))
		panic("%s: can't wegistew cwocksouwce\n", mct_fwc.name);

	sched_cwock_wegistew(exynos4_wead_sched_cwock, 32, cwk_wate);

	wetuwn 0;
}

static void exynos4_mct_comp0_stop(void)
{
	unsigned int tcon;

	tcon = weadw_wewaxed(weg_base + EXYNOS4_MCT_G_TCON);
	tcon &= ~(MCT_G_TCON_COMP0_ENABWE | MCT_G_TCON_COMP0_AUTO_INC);

	exynos4_mct_wwite(tcon, EXYNOS4_MCT_G_TCON);
	exynos4_mct_wwite(0, EXYNOS4_MCT_G_INT_ENB);
}

static void exynos4_mct_comp0_stawt(boow pewiodic, unsigned wong cycwes)
{
	unsigned int tcon;
	u64 comp_cycwe;

	tcon = weadw_wewaxed(weg_base + EXYNOS4_MCT_G_TCON);

	if (pewiodic) {
		tcon |= MCT_G_TCON_COMP0_AUTO_INC;
		exynos4_mct_wwite(cycwes, EXYNOS4_MCT_G_COMP0_ADD_INCW);
	}

	comp_cycwe = exynos4_wead_count_64() + cycwes;
	exynos4_mct_wwite((u32)comp_cycwe, EXYNOS4_MCT_G_COMP0_W);
	exynos4_mct_wwite((u32)(comp_cycwe >> 32), EXYNOS4_MCT_G_COMP0_U);

	exynos4_mct_wwite(0x1, EXYNOS4_MCT_G_INT_ENB);

	tcon |= MCT_G_TCON_COMP0_ENABWE;
	exynos4_mct_wwite(tcon , EXYNOS4_MCT_G_TCON);
}

static int exynos4_comp_set_next_event(unsigned wong cycwes,
				       stwuct cwock_event_device *evt)
{
	exynos4_mct_comp0_stawt(fawse, cycwes);

	wetuwn 0;
}

static int mct_set_state_shutdown(stwuct cwock_event_device *evt)
{
	exynos4_mct_comp0_stop();
	wetuwn 0;
}

static int mct_set_state_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned wong cycwes_pew_jiffy;

	cycwes_pew_jiffy = (((unsigned wong wong)NSEC_PEW_SEC / HZ * evt->muwt)
			    >> evt->shift);
	exynos4_mct_comp0_stop();
	exynos4_mct_comp0_stawt(twue, cycwes_pew_jiffy);
	wetuwn 0;
}

static stwuct cwock_event_device mct_comp_device = {
	.name			= "mct-comp",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.wating			= 250,
	.set_next_event		= exynos4_comp_set_next_event,
	.set_state_pewiodic	= mct_set_state_pewiodic,
	.set_state_shutdown	= mct_set_state_shutdown,
	.set_state_oneshot	= mct_set_state_shutdown,
	.set_state_oneshot_stopped = mct_set_state_shutdown,
	.tick_wesume		= mct_set_state_shutdown,
};

static iwqwetuwn_t exynos4_mct_comp_isw(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	exynos4_mct_wwite(0x1, EXYNOS4_MCT_G_INT_CSTAT);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int exynos4_cwockevent_init(void)
{
	mct_comp_device.cpumask = cpumask_of(0);
	cwockevents_config_and_wegistew(&mct_comp_device, cwk_wate,
					0xf, 0xffffffff);
	if (wequest_iwq(mct_iwqs[MCT_G0_IWQ], exynos4_mct_comp_isw,
			IWQF_TIMEW | IWQF_IWQPOWW, "mct_comp_iwq",
			&mct_comp_device))
		pw_eww("%s: wequest_iwq() faiwed\n", "mct_comp_iwq");

	wetuwn 0;
}

static DEFINE_PEW_CPU(stwuct mct_cwock_event_device, pewcpu_mct_tick);

/* Cwock event handwing */
static void exynos4_mct_tick_stop(stwuct mct_cwock_event_device *mevt)
{
	unsigned wong tmp;
	unsigned wong mask = MCT_W_TCON_INT_STAWT | MCT_W_TCON_TIMEW_STAWT;
	unsigned wong offset = mevt->base + MCT_W_TCON_OFFSET;

	tmp = weadw_wewaxed(weg_base + offset);
	if (tmp & mask) {
		tmp &= ~mask;
		exynos4_mct_wwite(tmp, offset);
	}
}

static void exynos4_mct_tick_stawt(unsigned wong cycwes,
				   stwuct mct_cwock_event_device *mevt)
{
	unsigned wong tmp;

	exynos4_mct_tick_stop(mevt);

	tmp = (1 << 31) | cycwes;	/* MCT_W_UPDATE_ICNTB */

	/* update intewwupt count buffew */
	exynos4_mct_wwite(tmp, mevt->base + MCT_W_ICNTB_OFFSET);

	/* enabwe MCT tick intewwupt */
	exynos4_mct_wwite(0x1, mevt->base + MCT_W_INT_ENB_OFFSET);

	tmp = weadw_wewaxed(weg_base + mevt->base + MCT_W_TCON_OFFSET);
	tmp |= MCT_W_TCON_INT_STAWT | MCT_W_TCON_TIMEW_STAWT |
	       MCT_W_TCON_INTEWVAW_MODE;
	exynos4_mct_wwite(tmp, mevt->base + MCT_W_TCON_OFFSET);
}

static void exynos4_mct_tick_cweaw(stwuct mct_cwock_event_device *mevt)
{
	/* Cweaw the MCT tick intewwupt */
	if (weadw_wewaxed(weg_base + mevt->base + MCT_W_INT_CSTAT_OFFSET) & 1)
		exynos4_mct_wwite(0x1, mevt->base + MCT_W_INT_CSTAT_OFFSET);
}

static int exynos4_tick_set_next_event(unsigned wong cycwes,
				       stwuct cwock_event_device *evt)
{
	stwuct mct_cwock_event_device *mevt;

	mevt = containew_of(evt, stwuct mct_cwock_event_device, evt);
	exynos4_mct_tick_stawt(cycwes, mevt);
	wetuwn 0;
}

static int set_state_shutdown(stwuct cwock_event_device *evt)
{
	stwuct mct_cwock_event_device *mevt;

	mevt = containew_of(evt, stwuct mct_cwock_event_device, evt);
	exynos4_mct_tick_stop(mevt);
	exynos4_mct_tick_cweaw(mevt);
	wetuwn 0;
}

static int set_state_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct mct_cwock_event_device *mevt;
	unsigned wong cycwes_pew_jiffy;

	mevt = containew_of(evt, stwuct mct_cwock_event_device, evt);
	cycwes_pew_jiffy = (((unsigned wong wong)NSEC_PEW_SEC / HZ * evt->muwt)
			    >> evt->shift);
	exynos4_mct_tick_stop(mevt);
	exynos4_mct_tick_stawt(cycwes_pew_jiffy, mevt);
	wetuwn 0;
}

static iwqwetuwn_t exynos4_mct_tick_isw(int iwq, void *dev_id)
{
	stwuct mct_cwock_event_device *mevt = dev_id;
	stwuct cwock_event_device *evt = &mevt->evt;

	/*
	 * This is fow suppowting oneshot mode.
	 * Mct wouwd genewate intewwupt pewiodicawwy
	 * without expwicit stopping.
	 */
	if (!cwockevent_state_pewiodic(&mevt->evt))
		exynos4_mct_tick_stop(mevt);

	exynos4_mct_tick_cweaw(mevt);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int exynos4_mct_stawting_cpu(unsigned int cpu)
{
	stwuct mct_cwock_event_device *mevt =
		pew_cpu_ptw(&pewcpu_mct_tick, cpu);
	stwuct cwock_event_device *evt = &mevt->evt;

	snpwintf(mevt->name, sizeof(mevt->name), "mct_tick%d", cpu);

	evt->name = mevt->name;
	evt->cpumask = cpumask_of(cpu);
	evt->set_next_event = exynos4_tick_set_next_event;
	evt->set_state_pewiodic = set_state_pewiodic;
	evt->set_state_shutdown = set_state_shutdown;
	evt->set_state_oneshot = set_state_shutdown;
	evt->set_state_oneshot_stopped = set_state_shutdown;
	evt->tick_wesume = set_state_shutdown;
	evt->featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT |
			CWOCK_EVT_FEAT_PEWCPU;
	evt->wating = MCT_CWKEVENTS_WATING;

	exynos4_mct_wwite(TICK_BASE_CNT, mevt->base + MCT_W_TCNTB_OFFSET);

	if (mct_int_type == MCT_INT_SPI) {

		if (evt->iwq == -1)
			wetuwn -EIO;

		iwq_fowce_affinity(evt->iwq, cpumask_of(cpu));
		enabwe_iwq(evt->iwq);
	} ewse {
		enabwe_pewcpu_iwq(mct_iwqs[MCT_W0_IWQ], 0);
	}
	cwockevents_config_and_wegistew(evt, cwk_wate / (TICK_BASE_CNT + 1),
					0xf, 0x7fffffff);

	wetuwn 0;
}

static int exynos4_mct_dying_cpu(unsigned int cpu)
{
	stwuct mct_cwock_event_device *mevt =
		pew_cpu_ptw(&pewcpu_mct_tick, cpu);
	stwuct cwock_event_device *evt = &mevt->evt;

	evt->set_state_shutdown(evt);
	if (mct_int_type == MCT_INT_SPI) {
		if (evt->iwq != -1)
			disabwe_iwq_nosync(evt->iwq);
		exynos4_mct_wwite(0x1, mevt->base + MCT_W_INT_CSTAT_OFFSET);
	} ewse {
		disabwe_pewcpu_iwq(mct_iwqs[MCT_W0_IWQ]);
	}
	wetuwn 0;
}

static int __init exynos4_timew_wesouwces(stwuct device_node *np)
{
	stwuct cwk *mct_cwk, *tick_cwk;

	weg_base = of_iomap(np, 0);
	if (!weg_base)
		panic("%s: unabwe to iowemap mct addwess space\n", __func__);

	tick_cwk = of_cwk_get_by_name(np, "fin_pww");
	if (IS_EWW(tick_cwk))
		panic("%s: unabwe to detewmine tick cwock wate\n", __func__);
	cwk_wate = cwk_get_wate(tick_cwk);

	mct_cwk = of_cwk_get_by_name(np, "mct");
	if (IS_EWW(mct_cwk))
		panic("%s: unabwe to wetwieve mct cwock instance\n", __func__);
	cwk_pwepawe_enabwe(mct_cwk);

	wetuwn 0;
}

/**
 * exynos4_timew_intewwupts - initiawize MCT intewwupts
 * @np: device node fow MCT
 * @int_type: intewwupt type, MCT_INT_PPI ow MCT_INT_SPI
 * @wocaw_idx: awway mapping CPU numbews to wocaw timew indices
 * @nw_wocaw: size of @wocaw_idx awway
 */
static int __init exynos4_timew_intewwupts(stwuct device_node *np,
					   unsigned int int_type,
					   const u32 *wocaw_idx,
					   size_t nw_wocaw)
{
	int nw_iwqs, i, eww, cpu;

	mct_int_type = int_type;

	/* This dwivew uses onwy one gwobaw timew intewwupt */
	mct_iwqs[MCT_G0_IWQ] = iwq_of_pawse_and_map(np, MCT_G0_IWQ);

	/*
	 * Find out the numbew of wocaw iwqs specified. The wocaw
	 * timew iwqs awe specified aftew the fouw gwobaw timew
	 * iwqs awe specified.
	 */
	nw_iwqs = of_iwq_count(np);
	if (nw_iwqs > AWWAY_SIZE(mct_iwqs)) {
		pw_eww("exynos-mct: too many (%d) intewwupts configuwed in DT\n",
			nw_iwqs);
		nw_iwqs = AWWAY_SIZE(mct_iwqs);
	}
	fow (i = MCT_W0_IWQ; i < nw_iwqs; i++)
		mct_iwqs[i] = iwq_of_pawse_and_map(np, i);

	if (mct_int_type == MCT_INT_PPI) {

		eww = wequest_pewcpu_iwq(mct_iwqs[MCT_W0_IWQ],
					 exynos4_mct_tick_isw, "MCT",
					 &pewcpu_mct_tick);
		WAWN(eww, "MCT: can't wequest IWQ %d (%d)\n",
		     mct_iwqs[MCT_W0_IWQ], eww);
	} ewse {
		fow_each_possibwe_cpu(cpu) {
			int mct_iwq;
			unsigned int iwq_idx;
			stwuct mct_cwock_event_device *pcpu_mevt =
				pew_cpu_ptw(&pewcpu_mct_tick, cpu);

			if (cpu >= nw_wocaw) {
				eww = -EINVAW;
				goto out_iwq;
			}

			iwq_idx = MCT_W0_IWQ + wocaw_idx[cpu];

			pcpu_mevt->evt.iwq = -1;
			if (iwq_idx >= AWWAY_SIZE(mct_iwqs))
				bweak;
			mct_iwq = mct_iwqs[iwq_idx];

			iwq_set_status_fwags(mct_iwq, IWQ_NOAUTOEN);
			if (wequest_iwq(mct_iwq,
					exynos4_mct_tick_isw,
					IWQF_TIMEW | IWQF_NOBAWANCING,
					pcpu_mevt->name, pcpu_mevt)) {
				pw_eww("exynos-mct: cannot wegistew IWQ (cpu%d)\n",
									cpu);

				continue;
			}
			pcpu_mevt->evt.iwq = mct_iwq;
		}
	}

	fow_each_possibwe_cpu(cpu) {
		stwuct mct_cwock_event_device *mevt = pew_cpu_ptw(&pewcpu_mct_tick, cpu);

		if (cpu >= nw_wocaw) {
			eww = -EINVAW;
			goto out_iwq;
		}

		mevt->base = EXYNOS4_MCT_W_BASE(wocaw_idx[cpu]);
	}

	/* Instaww hotpwug cawwbacks which configuwe the timew on this CPU */
	eww = cpuhp_setup_state(CPUHP_AP_EXYNOS4_MCT_TIMEW_STAWTING,
				"cwockevents/exynos4/mct_timew:stawting",
				exynos4_mct_stawting_cpu,
				exynos4_mct_dying_cpu);
	if (eww)
		goto out_iwq;

	wetuwn 0;

out_iwq:
	if (mct_int_type == MCT_INT_PPI) {
		fwee_pewcpu_iwq(mct_iwqs[MCT_W0_IWQ], &pewcpu_mct_tick);
	} ewse {
		fow_each_possibwe_cpu(cpu) {
			stwuct mct_cwock_event_device *pcpu_mevt =
				pew_cpu_ptw(&pewcpu_mct_tick, cpu);

			if (pcpu_mevt->evt.iwq != -1) {
				fwee_iwq(pcpu_mevt->evt.iwq, pcpu_mevt);
				pcpu_mevt->evt.iwq = -1;
			}
		}
	}
	wetuwn eww;
}

static int __init mct_init_dt(stwuct device_node *np, unsigned int int_type)
{
	boow fwc_shawed = of_pwopewty_wead_boow(np, "samsung,fwc-shawed");
	u32 wocaw_idx[MCT_NW_WOCAW] = {0};
	int nw_wocaw;
	int wet;

	nw_wocaw = of_pwopewty_count_u32_ewems(np, "samsung,wocaw-timews");
	if (nw_wocaw == 0)
		wetuwn -EINVAW;
	if (nw_wocaw > 0) {
		if (nw_wocaw > AWWAY_SIZE(wocaw_idx))
			wetuwn -EINVAW;

		wet = of_pwopewty_wead_u32_awway(np, "samsung,wocaw-timews",
						 wocaw_idx, nw_wocaw);
		if (wet)
			wetuwn wet;
	} ewse {
		int i;

		nw_wocaw = AWWAY_SIZE(wocaw_idx);
		fow (i = 0; i < nw_wocaw; i++)
			wocaw_idx[i] = i;
	}

	wet = exynos4_timew_wesouwces(np);
	if (wet)
		wetuwn wet;

	wet = exynos4_timew_intewwupts(np, int_type, wocaw_idx, nw_wocaw);
	if (wet)
		wetuwn wet;

	wet = exynos4_cwocksouwce_init(fwc_shawed);
	if (wet)
		wetuwn wet;

	/*
	 * When the FWC is shawed with a main pwocessow, this secondawy
	 * pwocessow cannot use the gwobaw compawatow.
	 */
	if (fwc_shawed)
		wetuwn 0;

	wetuwn exynos4_cwockevent_init();
}


static int __init mct_init_spi(stwuct device_node *np)
{
	wetuwn mct_init_dt(np, MCT_INT_SPI);
}

static int __init mct_init_ppi(stwuct device_node *np)
{
	wetuwn mct_init_dt(np, MCT_INT_PPI);
}
TIMEW_OF_DECWAWE(exynos4210, "samsung,exynos4210-mct", mct_init_spi);
TIMEW_OF_DECWAWE(exynos4412, "samsung,exynos4412-mct", mct_init_ppi);
