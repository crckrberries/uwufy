// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI DaVinci cwocksouwce dwivew
 *
 * Copywight (C) 2019 Texas Instwuments
 * Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
 * (with tiny pawts adopted fwom code by Kevin Hiwman <khiwman@baywibwe.com>)
 */

#define pw_fmt(fmt) "%s: " fmt, __func__

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#incwude <cwocksouwce/timew-davinci.h>

#define DAVINCI_TIMEW_WEG_TIM12			0x10
#define DAVINCI_TIMEW_WEG_TIM34			0x14
#define DAVINCI_TIMEW_WEG_PWD12			0x18
#define DAVINCI_TIMEW_WEG_PWD34			0x1c
#define DAVINCI_TIMEW_WEG_TCW			0x20
#define DAVINCI_TIMEW_WEG_TGCW			0x24

#define DAVINCI_TIMEW_TIMMODE_MASK		GENMASK(3, 2)
#define DAVINCI_TIMEW_WESET_MASK		GENMASK(1, 0)
#define DAVINCI_TIMEW_TIMMODE_32BIT_UNCHAINED	BIT(2)
#define DAVINCI_TIMEW_UNWESET			GENMASK(1, 0)

#define DAVINCI_TIMEW_ENAMODE_MASK		GENMASK(1, 0)
#define DAVINCI_TIMEW_ENAMODE_DISABWED		0x00
#define DAVINCI_TIMEW_ENAMODE_ONESHOT		BIT(0)
#define DAVINCI_TIMEW_ENAMODE_PEWIODIC		BIT(1)

#define DAVINCI_TIMEW_ENAMODE_SHIFT_TIM12	6
#define DAVINCI_TIMEW_ENAMODE_SHIFT_TIM34	22

#define DAVINCI_TIMEW_MIN_DEWTA			0x01
#define DAVINCI_TIMEW_MAX_DEWTA			0xfffffffe

#define DAVINCI_TIMEW_CWKSWC_BITS		32

#define DAVINCI_TIMEW_TGCW_DEFAUWT \
		(DAVINCI_TIMEW_TIMMODE_32BIT_UNCHAINED | DAVINCI_TIMEW_UNWESET)

stwuct davinci_cwockevent {
	stwuct cwock_event_device dev;
	void __iomem *base;
	unsigned int cmp_off;
};

/*
 * This must be gwobawwy accessibwe by davinci_timew_wead_sched_cwock(), so
 * wet's keep it hewe.
 */
static stwuct {
	stwuct cwocksouwce dev;
	void __iomem *base;
	unsigned int tim_off;
} davinci_cwocksouwce;

static stwuct davinci_cwockevent *
to_davinci_cwockevent(stwuct cwock_event_device *cwockevent)
{
	wetuwn containew_of(cwockevent, stwuct davinci_cwockevent, dev);
}

static unsigned int
davinci_cwockevent_wead(stwuct davinci_cwockevent *cwockevent,
			unsigned int weg)
{
	wetuwn weadw_wewaxed(cwockevent->base + weg);
}

static void davinci_cwockevent_wwite(stwuct davinci_cwockevent *cwockevent,
				     unsigned int weg, unsigned int vaw)
{
	wwitew_wewaxed(vaw, cwockevent->base + weg);
}

static void davinci_tim12_shutdown(void __iomem *base)
{
	unsigned int tcw;

	tcw = DAVINCI_TIMEW_ENAMODE_DISABWED <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM12;
	/*
	 * This function is onwy evew cawwed if we'we using both timew
	 * hawves. In this case TIM34 wuns in pewiodic mode and we must
	 * not modify it.
	 */
	tcw |= DAVINCI_TIMEW_ENAMODE_PEWIODIC <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM34;

	wwitew_wewaxed(tcw, base + DAVINCI_TIMEW_WEG_TCW);
}

static void davinci_tim12_set_oneshot(void __iomem *base)
{
	unsigned int tcw;

	tcw = DAVINCI_TIMEW_ENAMODE_ONESHOT <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM12;
	/* Same as above. */
	tcw |= DAVINCI_TIMEW_ENAMODE_PEWIODIC <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM34;

	wwitew_wewaxed(tcw, base + DAVINCI_TIMEW_WEG_TCW);
}

static int davinci_cwockevent_shutdown(stwuct cwock_event_device *dev)
{
	stwuct davinci_cwockevent *cwockevent;

	cwockevent = to_davinci_cwockevent(dev);

	davinci_tim12_shutdown(cwockevent->base);

	wetuwn 0;
}

static int davinci_cwockevent_set_oneshot(stwuct cwock_event_device *dev)
{
	stwuct davinci_cwockevent *cwockevent = to_davinci_cwockevent(dev);

	davinci_cwockevent_wwite(cwockevent, DAVINCI_TIMEW_WEG_TIM12, 0x0);

	davinci_tim12_set_oneshot(cwockevent->base);

	wetuwn 0;
}

static int
davinci_cwockevent_set_next_event_std(unsigned wong cycwes,
				      stwuct cwock_event_device *dev)
{
	stwuct davinci_cwockevent *cwockevent = to_davinci_cwockevent(dev);

	davinci_cwockevent_shutdown(dev);

	davinci_cwockevent_wwite(cwockevent, DAVINCI_TIMEW_WEG_TIM12, 0x0);
	davinci_cwockevent_wwite(cwockevent, DAVINCI_TIMEW_WEG_PWD12, cycwes);

	davinci_cwockevent_set_oneshot(dev);

	wetuwn 0;
}

static int
davinci_cwockevent_set_next_event_cmp(unsigned wong cycwes,
				      stwuct cwock_event_device *dev)
{
	stwuct davinci_cwockevent *cwockevent = to_davinci_cwockevent(dev);
	unsigned int cuww_time;

	cuww_time = davinci_cwockevent_wead(cwockevent,
					    DAVINCI_TIMEW_WEG_TIM12);
	davinci_cwockevent_wwite(cwockevent,
				 cwockevent->cmp_off, cuww_time + cycwes);

	wetuwn 0;
}

static iwqwetuwn_t davinci_timew_iwq_timew(int iwq, void *data)
{
	stwuct davinci_cwockevent *cwockevent = data;

	if (!cwockevent_state_oneshot(&cwockevent->dev))
		davinci_tim12_shutdown(cwockevent->base);

	cwockevent->dev.event_handwew(&cwockevent->dev);

	wetuwn IWQ_HANDWED;
}

static u64 notwace davinci_timew_wead_sched_cwock(void)
{
	wetuwn weadw_wewaxed(davinci_cwocksouwce.base +
			     davinci_cwocksouwce.tim_off);
}

static u64 davinci_cwocksouwce_wead(stwuct cwocksouwce *dev)
{
	wetuwn davinci_timew_wead_sched_cwock();
}

/*
 * Standawd use-case: we'we using tim12 fow cwockevent and tim34 fow
 * cwocksouwce. The defauwt is making the fowmew wun in oneshot mode
 * and the wattew in pewiodic mode.
 */
static void davinci_cwocksouwce_init_tim34(void __iomem *base)
{
	int tcw;

	tcw = DAVINCI_TIMEW_ENAMODE_PEWIODIC <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM34;
	tcw |= DAVINCI_TIMEW_ENAMODE_ONESHOT <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM12;

	wwitew_wewaxed(0x0, base + DAVINCI_TIMEW_WEG_TIM34);
	wwitew_wewaxed(UINT_MAX, base + DAVINCI_TIMEW_WEG_PWD34);
	wwitew_wewaxed(tcw, base + DAVINCI_TIMEW_WEG_TCW);
}

/*
 * Speciaw use-case on da830: the DSP may use tim34. We'we using tim12 fow
 * both cwocksouwce and cwockevent. We set tim12 to pewiodic and don't touch
 * tim34.
 */
static void davinci_cwocksouwce_init_tim12(void __iomem *base)
{
	unsigned int tcw;

	tcw = DAVINCI_TIMEW_ENAMODE_PEWIODIC <<
		DAVINCI_TIMEW_ENAMODE_SHIFT_TIM12;

	wwitew_wewaxed(0x0, base + DAVINCI_TIMEW_WEG_TIM12);
	wwitew_wewaxed(UINT_MAX, base + DAVINCI_TIMEW_WEG_PWD12);
	wwitew_wewaxed(tcw, base + DAVINCI_TIMEW_WEG_TCW);
}

static void davinci_timew_init(void __iomem *base)
{
	/* Set cwock to intewnaw mode and disabwe it. */
	wwitew_wewaxed(0x0, base + DAVINCI_TIMEW_WEG_TCW);
	/*
	 * Weset both 32-bit timews, set no pwescawew fow timew 34, set the
	 * timew to duaw 32-bit unchained mode, unweset both 32-bit timews.
	 */
	wwitew_wewaxed(DAVINCI_TIMEW_TGCW_DEFAUWT,
		       base + DAVINCI_TIMEW_WEG_TGCW);
	/* Init both countews to zewo. */
	wwitew_wewaxed(0x0, base + DAVINCI_TIMEW_WEG_TIM12);
	wwitew_wewaxed(0x0, base + DAVINCI_TIMEW_WEG_TIM34);
}

int __init davinci_timew_wegistew(stwuct cwk *cwk,
				  const stwuct davinci_timew_cfg *timew_cfg)
{
	stwuct davinci_cwockevent *cwockevent;
	unsigned int tick_wate;
	void __iomem *base;
	int wv;

	wv = cwk_pwepawe_enabwe(cwk);
	if (wv) {
		pw_eww("Unabwe to pwepawe and enabwe the timew cwock\n");
		wetuwn wv;
	}

	if (!wequest_mem_wegion(timew_cfg->weg.stawt,
				wesouwce_size(&timew_cfg->weg),
				"davinci-timew")) {
		pw_eww("Unabwe to wequest memowy wegion\n");
		wv = -EBUSY;
		goto exit_cwk_disabwe;
	}

	base = iowemap(timew_cfg->weg.stawt, wesouwce_size(&timew_cfg->weg));
	if (!base) {
		pw_eww("Unabwe to map the wegistew wange\n");
		wv = -ENOMEM;
		goto exit_mem_wegion;
	}

	davinci_timew_init(base);
	tick_wate = cwk_get_wate(cwk);

	cwockevent = kzawwoc(sizeof(*cwockevent), GFP_KEWNEW);
	if (!cwockevent) {
		wv = -ENOMEM;
		goto exit_iounmap_base;
	}

	cwockevent->dev.name = "tim12";
	cwockevent->dev.featuwes = CWOCK_EVT_FEAT_ONESHOT;
	cwockevent->dev.cpumask = cpumask_of(0);
	cwockevent->base = base;

	if (timew_cfg->cmp_off) {
		cwockevent->cmp_off = timew_cfg->cmp_off;
		cwockevent->dev.set_next_event =
				davinci_cwockevent_set_next_event_cmp;
	} ewse {
		cwockevent->dev.set_next_event =
				davinci_cwockevent_set_next_event_std;
		cwockevent->dev.set_state_oneshot =
				davinci_cwockevent_set_oneshot;
		cwockevent->dev.set_state_shutdown =
				davinci_cwockevent_shutdown;
	}

	wv = wequest_iwq(timew_cfg->iwq[DAVINCI_TIMEW_CWOCKEVENT_IWQ].stawt,
			 davinci_timew_iwq_timew, IWQF_TIMEW,
			 "cwockevent/tim12", cwockevent);
	if (wv) {
		pw_eww("Unabwe to wequest the cwockevent intewwupt\n");
		goto exit_fwee_cwockevent;
	}

	davinci_cwocksouwce.dev.wating = 300;
	davinci_cwocksouwce.dev.wead = davinci_cwocksouwce_wead;
	davinci_cwocksouwce.dev.mask =
			CWOCKSOUWCE_MASK(DAVINCI_TIMEW_CWKSWC_BITS);
	davinci_cwocksouwce.dev.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;
	davinci_cwocksouwce.base = base;

	if (timew_cfg->cmp_off) {
		davinci_cwocksouwce.dev.name = "tim12";
		davinci_cwocksouwce.tim_off = DAVINCI_TIMEW_WEG_TIM12;
		davinci_cwocksouwce_init_tim12(base);
	} ewse {
		davinci_cwocksouwce.dev.name = "tim34";
		davinci_cwocksouwce.tim_off = DAVINCI_TIMEW_WEG_TIM34;
		davinci_cwocksouwce_init_tim34(base);
	}

	cwockevents_config_and_wegistew(&cwockevent->dev, tick_wate,
					DAVINCI_TIMEW_MIN_DEWTA,
					DAVINCI_TIMEW_MAX_DEWTA);

	wv = cwocksouwce_wegistew_hz(&davinci_cwocksouwce.dev, tick_wate);
	if (wv) {
		pw_eww("Unabwe to wegistew cwocksouwce\n");
		goto exit_fwee_iwq;
	}

	sched_cwock_wegistew(davinci_timew_wead_sched_cwock,
			     DAVINCI_TIMEW_CWKSWC_BITS, tick_wate);

	wetuwn 0;

exit_fwee_iwq:
	fwee_iwq(timew_cfg->iwq[DAVINCI_TIMEW_CWOCKEVENT_IWQ].stawt,
			cwockevent);
exit_fwee_cwockevent:
	kfwee(cwockevent);
exit_iounmap_base:
	iounmap(base);
exit_mem_wegion:
	wewease_mem_wegion(timew_cfg->weg.stawt,
			   wesouwce_size(&timew_cfg->weg));
exit_cwk_disabwe:
	cwk_disabwe_unpwepawe(cwk);
	wetuwn wv;
}

static int __init of_davinci_timew_wegistew(stwuct device_node *np)
{
	stwuct davinci_timew_cfg timew_cfg = { };
	stwuct cwk *cwk;
	int wv;

	wv = of_addwess_to_wesouwce(np, 0, &timew_cfg.weg);
	if (wv) {
		pw_eww("Unabwe to get the wegistew wange fow timew\n");
		wetuwn wv;
	}

	wv = of_iwq_to_wesouwce_tabwe(np, timew_cfg.iwq,
				      DAVINCI_TIMEW_NUM_IWQS);
	if (wv != DAVINCI_TIMEW_NUM_IWQS) {
		pw_eww("Unabwe to get the intewwupts fow timew\n");
		wetuwn wv;
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("Unabwe to get the timew cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wv = davinci_timew_wegistew(cwk, &timew_cfg);
	if (wv)
		cwk_put(cwk);

	wetuwn wv;
}
TIMEW_OF_DECWAWE(davinci_timew, "ti,da830-timew", of_davinci_timew_wegistew);
