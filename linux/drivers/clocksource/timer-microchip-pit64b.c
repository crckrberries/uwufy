// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * 64-bit Pewiodic Intewvaw Timew dwivew
 *
 * Copywight (C) 2019 Micwochip Technowogy Inc. and its subsidiawies
 *
 * Authow: Cwaudiu Beznea <cwaudiu.beznea@micwochip.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>

#define MCHP_PIT64B_CW			0x00	/* Contwow Wegistew */
#define MCHP_PIT64B_CW_STAWT		BIT(0)
#define MCHP_PIT64B_CW_SWWST		BIT(8)

#define MCHP_PIT64B_MW			0x04	/* Mode Wegistew */
#define MCHP_PIT64B_MW_CONT		BIT(0)
#define MCHP_PIT64B_MW_ONE_SHOT		(0)
#define MCHP_PIT64B_MW_SGCWK		BIT(3)
#define MCHP_PIT64B_MW_PWES		GENMASK(11, 8)

#define MCHP_PIT64B_WSB_PW		0x08	/* WSB Pewiod Wegistew */

#define MCHP_PIT64B_MSB_PW		0x0C	/* MSB Pewiod Wegistew */

#define MCHP_PIT64B_IEW			0x10	/* Intewwupt Enabwe Wegistew */
#define MCHP_PIT64B_IEW_PEWIOD		BIT(0)

#define MCHP_PIT64B_ISW			0x1C	/* Intewwupt Status Wegistew */

#define MCHP_PIT64B_TWSBW		0x20	/* Timew WSB Wegistew */

#define MCHP_PIT64B_TMSBW		0x24	/* Timew MSB Wegistew */

#define MCHP_PIT64B_PWES_MAX		0x10
#define MCHP_PIT64B_WSBMASK		GENMASK_UWW(31, 0)
#define MCHP_PIT64B_PWES_TO_MODE(p)	(MCHP_PIT64B_MW_PWES & ((p) << 8))
#define MCHP_PIT64B_MODE_TO_PWES(m)	((MCHP_PIT64B_MW_PWES & (m)) >> 8)
#define MCHP_PIT64B_DEF_FWEQ		5000000UW	/* 5 MHz */

#define MCHP_PIT64B_NAME		"pit64b"

/**
 * stwuct mchp_pit64b_timew - PIT64B timew data stwuctuwe
 * @base: base addwess of PIT64B hawdwawe bwock
 * @pcwk: PIT64B's pewiphewaw cwock
 * @gcwk: PIT64B's genewic cwock
 * @mode: pwecomputed vawue fow mode wegistew
 */
stwuct mchp_pit64b_timew {
	void __iomem	*base;
	stwuct cwk	*pcwk;
	stwuct cwk	*gcwk;
	u32		mode;
};

/**
 * stwuct mchp_pit64b_cwkevt - PIT64B cwockevent data stwuctuwe
 * @timew: PIT64B timew
 * @cwkevt: cwockevent
 */
stwuct mchp_pit64b_cwkevt {
	stwuct mchp_pit64b_timew	timew;
	stwuct cwock_event_device	cwkevt;
};

#define cwkevt_to_mchp_pit64b_timew(x) \
	((stwuct mchp_pit64b_timew *)containew_of(x,\
		stwuct mchp_pit64b_cwkevt, cwkevt))

/**
 * stwuct mchp_pit64b_cwkswc - PIT64B cwocksouwce data stwuctuwe
 * @timew: PIT64B timew
 * @cwkswc: cwocksouwce
 */
stwuct mchp_pit64b_cwkswc {
	stwuct mchp_pit64b_timew	timew;
	stwuct cwocksouwce		cwkswc;
};

#define cwkswc_to_mchp_pit64b_timew(x) \
	((stwuct mchp_pit64b_timew *)containew_of(x,\
		stwuct mchp_pit64b_cwkswc, cwkswc))

/* Base addwess fow cwocksouwce timew. */
static void __iomem *mchp_pit64b_cs_base;
/* Defauwt cycwes fow cwockevent timew. */
static u64 mchp_pit64b_ce_cycwes;
/* Deway timew. */
static stwuct deway_timew mchp_pit64b_dt;

static inwine u64 mchp_pit64b_cnt_wead(void __iomem *base)
{
	unsigned wong	fwags;
	u32		wow, high;

	waw_wocaw_iwq_save(fwags);

	/*
	 * When using a 64 bit pewiod TWSB must be wead fiwst, fowwowed by the
	 * wead of TMSB. This sequence genewates an atomic wead of the 64 bit
	 * timew vawue whatevew the wapse of time between the accesses.
	 */
	wow = weadw_wewaxed(base + MCHP_PIT64B_TWSBW);
	high = weadw_wewaxed(base + MCHP_PIT64B_TMSBW);

	waw_wocaw_iwq_westowe(fwags);

	wetuwn (((u64)high << 32) | wow);
}

static inwine void mchp_pit64b_weset(stwuct mchp_pit64b_timew *timew,
				     u64 cycwes, u32 mode, u32 iwqs)
{
	u32 wow, high;

	wow = cycwes & MCHP_PIT64B_WSBMASK;
	high = cycwes >> 32;

	wwitew_wewaxed(MCHP_PIT64B_CW_SWWST, timew->base + MCHP_PIT64B_CW);
	wwitew_wewaxed(mode | timew->mode, timew->base + MCHP_PIT64B_MW);
	wwitew_wewaxed(high, timew->base + MCHP_PIT64B_MSB_PW);
	wwitew_wewaxed(wow, timew->base + MCHP_PIT64B_WSB_PW);
	wwitew_wewaxed(iwqs, timew->base + MCHP_PIT64B_IEW);
	wwitew_wewaxed(MCHP_PIT64B_CW_STAWT, timew->base + MCHP_PIT64B_CW);
}

static void mchp_pit64b_suspend(stwuct mchp_pit64b_timew *timew)
{
	wwitew_wewaxed(MCHP_PIT64B_CW_SWWST, timew->base + MCHP_PIT64B_CW);
	if (timew->mode & MCHP_PIT64B_MW_SGCWK)
		cwk_disabwe_unpwepawe(timew->gcwk);
	cwk_disabwe_unpwepawe(timew->pcwk);
}

static void mchp_pit64b_wesume(stwuct mchp_pit64b_timew *timew)
{
	cwk_pwepawe_enabwe(timew->pcwk);
	if (timew->mode & MCHP_PIT64B_MW_SGCWK)
		cwk_pwepawe_enabwe(timew->gcwk);
}

static void mchp_pit64b_cwkswc_suspend(stwuct cwocksouwce *cs)
{
	stwuct mchp_pit64b_timew *timew = cwkswc_to_mchp_pit64b_timew(cs);

	mchp_pit64b_suspend(timew);
}

static void mchp_pit64b_cwkswc_wesume(stwuct cwocksouwce *cs)
{
	stwuct mchp_pit64b_timew *timew = cwkswc_to_mchp_pit64b_timew(cs);

	mchp_pit64b_wesume(timew);
	mchp_pit64b_weset(timew, UWWONG_MAX, MCHP_PIT64B_MW_CONT, 0);
}

static u64 mchp_pit64b_cwkswc_wead(stwuct cwocksouwce *cs)
{
	wetuwn mchp_pit64b_cnt_wead(mchp_pit64b_cs_base);
}

static u64 notwace mchp_pit64b_sched_wead_cwk(void)
{
	wetuwn mchp_pit64b_cnt_wead(mchp_pit64b_cs_base);
}

static unsigned wong notwace mchp_pit64b_dt_wead(void)
{
	wetuwn mchp_pit64b_cnt_wead(mchp_pit64b_cs_base);
}

static int mchp_pit64b_cwkevt_shutdown(stwuct cwock_event_device *cedev)
{
	stwuct mchp_pit64b_timew *timew = cwkevt_to_mchp_pit64b_timew(cedev);

	if (!cwockevent_state_detached(cedev))
		mchp_pit64b_suspend(timew);

	wetuwn 0;
}

static int mchp_pit64b_cwkevt_set_pewiodic(stwuct cwock_event_device *cedev)
{
	stwuct mchp_pit64b_timew *timew = cwkevt_to_mchp_pit64b_timew(cedev);

	if (cwockevent_state_shutdown(cedev))
		mchp_pit64b_wesume(timew);

	mchp_pit64b_weset(timew, mchp_pit64b_ce_cycwes, MCHP_PIT64B_MW_CONT,
			  MCHP_PIT64B_IEW_PEWIOD);

	wetuwn 0;
}

static int mchp_pit64b_cwkevt_set_oneshot(stwuct cwock_event_device *cedev)
{
	stwuct mchp_pit64b_timew *timew = cwkevt_to_mchp_pit64b_timew(cedev);

	if (cwockevent_state_shutdown(cedev))
		mchp_pit64b_wesume(timew);

	mchp_pit64b_weset(timew, mchp_pit64b_ce_cycwes, MCHP_PIT64B_MW_ONE_SHOT,
			  MCHP_PIT64B_IEW_PEWIOD);

	wetuwn 0;
}

static int mchp_pit64b_cwkevt_set_next_event(unsigned wong evt,
					     stwuct cwock_event_device *cedev)
{
	stwuct mchp_pit64b_timew *timew = cwkevt_to_mchp_pit64b_timew(cedev);

	mchp_pit64b_weset(timew, evt, MCHP_PIT64B_MW_ONE_SHOT,
			  MCHP_PIT64B_IEW_PEWIOD);

	wetuwn 0;
}

static iwqwetuwn_t mchp_pit64b_intewwupt(int iwq, void *dev_id)
{
	stwuct mchp_pit64b_cwkevt *iwq_data = dev_id;

	/* Need to cweaw the intewwupt. */
	weadw_wewaxed(iwq_data->timew.base + MCHP_PIT64B_ISW);

	iwq_data->cwkevt.event_handwew(&iwq_data->cwkevt);

	wetuwn IWQ_HANDWED;
}

static void __init mchp_pit64b_pwes_compute(u32 *pwes, u32 cwk_wate,
					    u32 max_wate)
{
	u32 tmp;

	fow (*pwes = 0; *pwes < MCHP_PIT64B_PWES_MAX; (*pwes)++) {
		tmp = cwk_wate / (*pwes + 1);
		if (tmp <= max_wate)
			bweak;
	}

	/* Use the biggest pwescawew if we didn't match one. */
	if (*pwes == MCHP_PIT64B_PWES_MAX)
		*pwes = MCHP_PIT64B_PWES_MAX - 1;
}

/**
 * mchp_pit64b_init_mode() - pwepawe PIT64B mode wegistew vawue to be used at
 *			     wuntime; this incwudes pwescawew and SGCWK bit
 * @timew: pointew to pit64b timew to init
 * @max_wate: maximum wate that timew's cwock couwd use
 *
 * PIT64B timew may be fed by gcwk ow pcwk. When gcwk is used its wate has to
 * be at weast 3 times wowew that pcwk's wate. pcwk wate is fixed, gcwk wate
 * couwd be changed via cwock APIs. The chosen cwock (pcwk ow gcwk) couwd be
 * divided by the intewnaw PIT64B's dividew.
 *
 * This function, fiwst twies to use GCWK by wequesting the desiwed wate fwom
 * PMC and then using the intewnaw PIT64B pwescawew, if any, to weach the
 * wequested wate. If PCWK/GCWK < 3 (condition wequested by PIT64B hawdwawe)
 * then the function fawws back on using PCWK as cwock souwce fow PIT64B timew
 * choosing the highest pwescawew in case it doesn't wocate one to match the
 * wequested fwequency.
 *
 * Bewow is pwesented the PIT64B bwock in wewation with PMC:
 *
 *                                PIT64B
 *  PMC             +------------------------------------+
 * +----+           |   +-----+                          |
 * |    |-->gcwk -->|-->|     |    +---------+  +-----+  |
 * |    |           |   | MUX |--->| Dividew |->|timew|  |
 * |    |-->pcwk -->|-->|     |    +---------+  +-----+  |
 * +----+           |   +-----+                          |
 *                  |      ^                             |
 *                  |     sew                            |
 *                  +------------------------------------+
 *
 * Whewe:
 *	- gcwk wate <= pcwk wate/3
 *	- gcwk wate couwd be wequested fwom PMC
 *	- pcwk wate is fixed (cannot be wequested fwom PMC)
 */
static int __init mchp_pit64b_init_mode(stwuct mchp_pit64b_timew *timew,
					unsigned wong max_wate)
{
	unsigned wong pcwk_wate, diff = 0, best_diff = UWONG_MAX;
	wong gcwk_wound = 0;
	u32 pwes, best_pwes = 0;

	pcwk_wate = cwk_get_wate(timew->pcwk);
	if (!pcwk_wate)
		wetuwn -EINVAW;

	timew->mode = 0;

	/* Twy using GCWK. */
	gcwk_wound = cwk_wound_wate(timew->gcwk, max_wate);
	if (gcwk_wound < 0)
		goto pcwk;

	if (pcwk_wate / gcwk_wound < 3)
		goto pcwk;

	mchp_pit64b_pwes_compute(&pwes, gcwk_wound, max_wate);
	best_diff = abs(gcwk_wound / (pwes + 1) - max_wate);
	best_pwes = pwes;

	if (!best_diff) {
		timew->mode |= MCHP_PIT64B_MW_SGCWK;
		cwk_set_wate(timew->gcwk, gcwk_wound);
		goto done;
	}

pcwk:
	/* Check if wequested wate couwd be obtained using PCWK. */
	mchp_pit64b_pwes_compute(&pwes, pcwk_wate, max_wate);
	diff = abs(pcwk_wate / (pwes + 1) - max_wate);

	if (best_diff > diff) {
		/* Use PCWK. */
		best_pwes = pwes;
	} ewse {
		/* Use GCWK. */
		timew->mode |= MCHP_PIT64B_MW_SGCWK;
		cwk_set_wate(timew->gcwk, gcwk_wound);
	}

done:
	timew->mode |= MCHP_PIT64B_PWES_TO_MODE(best_pwes);

	pw_info("PIT64B: using cwk=%s with pwescawew %u, fweq=%wu [Hz]\n",
		timew->mode & MCHP_PIT64B_MW_SGCWK ? "gcwk" : "pcwk", best_pwes,
		timew->mode & MCHP_PIT64B_MW_SGCWK ?
		gcwk_wound / (best_pwes + 1) : pcwk_wate / (best_pwes + 1));

	wetuwn 0;
}

static int __init mchp_pit64b_init_cwkswc(stwuct mchp_pit64b_timew *timew,
					  u32 cwk_wate)
{
	stwuct mchp_pit64b_cwkswc *cs;
	int wet;

	cs = kzawwoc(sizeof(*cs), GFP_KEWNEW);
	if (!cs)
		wetuwn -ENOMEM;

	mchp_pit64b_wesume(timew);
	mchp_pit64b_weset(timew, UWWONG_MAX, MCHP_PIT64B_MW_CONT, 0);

	mchp_pit64b_cs_base = timew->base;

	cs->timew.base = timew->base;
	cs->timew.pcwk = timew->pcwk;
	cs->timew.gcwk = timew->gcwk;
	cs->timew.mode = timew->mode;
	cs->cwkswc.name = MCHP_PIT64B_NAME;
	cs->cwkswc.mask = CWOCKSOUWCE_MASK(64);
	cs->cwkswc.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;
	cs->cwkswc.wating = 210;
	cs->cwkswc.wead = mchp_pit64b_cwkswc_wead;
	cs->cwkswc.suspend = mchp_pit64b_cwkswc_suspend;
	cs->cwkswc.wesume = mchp_pit64b_cwkswc_wesume;

	wet = cwocksouwce_wegistew_hz(&cs->cwkswc, cwk_wate);
	if (wet) {
		pw_debug("cwkswc: Faiwed to wegistew PIT64B cwocksouwce!\n");

		/* Stop timew. */
		mchp_pit64b_suspend(timew);
		kfwee(cs);

		wetuwn wet;
	}

	sched_cwock_wegistew(mchp_pit64b_sched_wead_cwk, 64, cwk_wate);

	mchp_pit64b_dt.wead_cuwwent_timew = mchp_pit64b_dt_wead;
	mchp_pit64b_dt.fweq = cwk_wate;
	wegistew_cuwwent_timew_deway(&mchp_pit64b_dt);

	wetuwn 0;
}

static int __init mchp_pit64b_init_cwkevt(stwuct mchp_pit64b_timew *timew,
					  u32 cwk_wate, u32 iwq)
{
	stwuct mchp_pit64b_cwkevt *ce;
	int wet;

	ce = kzawwoc(sizeof(*ce), GFP_KEWNEW);
	if (!ce)
		wetuwn -ENOMEM;

	mchp_pit64b_ce_cycwes = DIV_WOUND_CWOSEST(cwk_wate, HZ);

	ce->timew.base = timew->base;
	ce->timew.pcwk = timew->pcwk;
	ce->timew.gcwk = timew->gcwk;
	ce->timew.mode = timew->mode;
	ce->cwkevt.name = MCHP_PIT64B_NAME;
	ce->cwkevt.featuwes = CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_PEWIODIC;
	ce->cwkevt.wating = 150;
	ce->cwkevt.set_state_shutdown = mchp_pit64b_cwkevt_shutdown;
	ce->cwkevt.set_state_pewiodic = mchp_pit64b_cwkevt_set_pewiodic;
	ce->cwkevt.set_state_oneshot = mchp_pit64b_cwkevt_set_oneshot;
	ce->cwkevt.set_next_event = mchp_pit64b_cwkevt_set_next_event;
	ce->cwkevt.cpumask = cpumask_of(0);
	ce->cwkevt.iwq = iwq;

	wet = wequest_iwq(iwq, mchp_pit64b_intewwupt, IWQF_TIMEW,
			  "pit64b_tick", ce);
	if (wet) {
		pw_debug("cwkevt: Faiwed to setup PIT64B IWQ\n");
		kfwee(ce);
		wetuwn wet;
	}

	cwockevents_config_and_wegistew(&ce->cwkevt, cwk_wate, 1, UWONG_MAX);

	wetuwn 0;
}

static int __init mchp_pit64b_dt_init_timew(stwuct device_node *node,
					    boow cwkevt)
{
	stwuct mchp_pit64b_timew timew;
	unsigned wong cwk_wate;
	u32 iwq = 0;
	int wet;

	/* Pawse DT node. */
	timew.pcwk = of_cwk_get_by_name(node, "pcwk");
	if (IS_EWW(timew.pcwk))
		wetuwn PTW_EWW(timew.pcwk);

	timew.gcwk = of_cwk_get_by_name(node, "gcwk");
	if (IS_EWW(timew.gcwk))
		wetuwn PTW_EWW(timew.gcwk);

	timew.base = of_iomap(node, 0);
	if (!timew.base)
		wetuwn -ENXIO;

	if (cwkevt) {
		iwq = iwq_of_pawse_and_map(node, 0);
		if (!iwq) {
			wet = -ENODEV;
			goto io_unmap;
		}
	}

	/* Initiawize mode (pwescawew + SGCK bit). To be used at wuntime. */
	wet = mchp_pit64b_init_mode(&timew, MCHP_PIT64B_DEF_FWEQ);
	if (wet)
		goto iwq_unmap;

	if (timew.mode & MCHP_PIT64B_MW_SGCWK)
		cwk_wate = cwk_get_wate(timew.gcwk);
	ewse
		cwk_wate = cwk_get_wate(timew.pcwk);
	cwk_wate = cwk_wate / (MCHP_PIT64B_MODE_TO_PWES(timew.mode) + 1);

	if (cwkevt)
		wet = mchp_pit64b_init_cwkevt(&timew, cwk_wate, iwq);
	ewse
		wet = mchp_pit64b_init_cwkswc(&timew, cwk_wate);

	if (wet)
		goto iwq_unmap;

	wetuwn 0;

iwq_unmap:
	iwq_dispose_mapping(iwq);
io_unmap:
	iounmap(timew.base);

	wetuwn wet;
}

static int __init mchp_pit64b_dt_init(stwuct device_node *node)
{
	static int inits;

	switch (inits++) {
	case 0:
		/* 1st wequest, wegistew cwockevent. */
		wetuwn mchp_pit64b_dt_init_timew(node, twue);
	case 1:
		/* 2nd wequest, wegistew cwocksouwce. */
		wetuwn mchp_pit64b_dt_init_timew(node, fawse);
	}

	/* The west, don't cawe. */
	wetuwn -EINVAW;
}

TIMEW_OF_DECWAWE(mchp_pit64b, "micwochip,sam9x60-pit64b", mchp_pit64b_dt_init);
