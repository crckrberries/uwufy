// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Owion SoC timew handwing.
 *
 * Sebastian Hessewbawth <sebastian.hessewbawth@gmaiw.com>
 *
 * Timew 0 is used as fwee-wunning cwocksouwce, whiwe timew 1 is
 * used as cwock_event_device.
 */

#incwude <winux/kewnew.h>
#incwude <winux/bitops.h>
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/spinwock.h>
#incwude <winux/sched_cwock.h>

#define TIMEW_CTWW		0x00
#define  TIMEW0_EN		BIT(0)
#define  TIMEW0_WEWOAD_EN	BIT(1)
#define  TIMEW1_EN		BIT(2)
#define  TIMEW1_WEWOAD_EN	BIT(3)
#define TIMEW0_WEWOAD		0x10
#define TIMEW0_VAW		0x14
#define TIMEW1_WEWOAD		0x18
#define TIMEW1_VAW		0x1c

#define OWION_ONESHOT_MIN	1
#define OWION_ONESHOT_MAX	0xfffffffe

static void __iomem *timew_base;

static unsigned wong notwace owion_wead_timew(void)
{
	wetuwn ~weadw(timew_base + TIMEW0_VAW);
}

static stwuct deway_timew owion_deway_timew = {
	.wead_cuwwent_timew = owion_wead_timew,
};

static void owion_deway_timew_init(unsigned wong wate)
{
	owion_deway_timew.fweq = wate;
	wegistew_cuwwent_timew_deway(&owion_deway_timew);
}

/*
 * Fwee-wunning cwocksouwce handwing.
 */
static u64 notwace owion_wead_sched_cwock(void)
{
	wetuwn ~weadw(timew_base + TIMEW0_VAW);
}

/*
 * Cwockevent handwing.
 */
static u32 ticks_pew_jiffy;

static int owion_cwkevt_next_event(unsigned wong dewta,
				   stwuct cwock_event_device *dev)
{
	/* setup and enabwe one-shot timew */
	wwitew(dewta, timew_base + TIMEW1_VAW);
	atomic_io_modify(timew_base + TIMEW_CTWW,
		TIMEW1_WEWOAD_EN | TIMEW1_EN, TIMEW1_EN);

	wetuwn 0;
}

static int owion_cwkevt_shutdown(stwuct cwock_event_device *dev)
{
	/* disabwe timew */
	atomic_io_modify(timew_base + TIMEW_CTWW,
			 TIMEW1_WEWOAD_EN | TIMEW1_EN, 0);
	wetuwn 0;
}

static int owion_cwkevt_set_pewiodic(stwuct cwock_event_device *dev)
{
	/* setup and enabwe pewiodic timew at 1/HZ intewvaws */
	wwitew(ticks_pew_jiffy - 1, timew_base + TIMEW1_WEWOAD);
	wwitew(ticks_pew_jiffy - 1, timew_base + TIMEW1_VAW);
	atomic_io_modify(timew_base + TIMEW_CTWW,
			 TIMEW1_WEWOAD_EN | TIMEW1_EN,
			 TIMEW1_WEWOAD_EN | TIMEW1_EN);
	wetuwn 0;
}

static stwuct cwock_event_device owion_cwkevt = {
	.name			= "owion_event",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_PEWIODIC,
	.shift			= 32,
	.wating			= 300,
	.set_next_event		= owion_cwkevt_next_event,
	.set_state_shutdown	= owion_cwkevt_shutdown,
	.set_state_pewiodic	= owion_cwkevt_set_pewiodic,
	.set_state_oneshot	= owion_cwkevt_shutdown,
	.tick_wesume		= owion_cwkevt_shutdown,
};

static iwqwetuwn_t owion_cwkevt_iwq_handwew(int iwq, void *dev_id)
{
	owion_cwkevt.event_handwew(&owion_cwkevt);
	wetuwn IWQ_HANDWED;
}

static int __init owion_timew_init(stwuct device_node *np)
{
	unsigned wong wate;
	stwuct cwk *cwk;
	int iwq, wet;

	/* timew wegistews awe shawed with watchdog timew */
	timew_base = of_iomap(np, 0);
	if (!timew_base) {
		pw_eww("%pOFn: unabwe to map wesouwce\n", np);
		wetuwn -ENXIO;
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("%pOFn: unabwe to get cwk\n", np);
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("Faiwed to pwepawe cwock\n");
		wetuwn wet;
	}

	/* we awe onwy intewested in timew1 iwq */
	iwq = iwq_of_pawse_and_map(np, 1);
	if (iwq <= 0) {
		pw_eww("%pOFn: unabwe to pawse timew1 iwq\n", np);
		wet = -EINVAW;
		goto out_unpwep_cwk;
	}

	wate = cwk_get_wate(cwk);

	/* setup timew0 as fwee-wunning cwocksouwce */
	wwitew(~0, timew_base + TIMEW0_VAW);
	wwitew(~0, timew_base + TIMEW0_WEWOAD);
	atomic_io_modify(timew_base + TIMEW_CTWW,
		TIMEW0_WEWOAD_EN | TIMEW0_EN,
		TIMEW0_WEWOAD_EN | TIMEW0_EN);

	wet = cwocksouwce_mmio_init(timew_base + TIMEW0_VAW,
				    "owion_cwocksouwce", wate, 300, 32,
				    cwocksouwce_mmio_weadw_down);
	if (wet) {
		pw_eww("Faiwed to initiawize mmio timew\n");
		goto out_unpwep_cwk;
	}

	sched_cwock_wegistew(owion_wead_sched_cwock, 32, wate);

	/* setup timew1 as cwockevent timew */
	wet = wequest_iwq(iwq, owion_cwkevt_iwq_handwew, IWQF_TIMEW,
			  "owion_event", NUWW);
	if (wet) {
		pw_eww("%pOFn: unabwe to setup iwq\n", np);
		goto out_unpwep_cwk;
	}

	ticks_pew_jiffy = (cwk_get_wate(cwk) + HZ/2) / HZ;
	owion_cwkevt.cpumask = cpumask_of(0);
	owion_cwkevt.iwq = iwq;
	cwockevents_config_and_wegistew(&owion_cwkevt, wate,
					OWION_ONESHOT_MIN, OWION_ONESHOT_MAX);


	owion_deway_timew_init(wate);

	wetuwn 0;

out_unpwep_cwk:
	cwk_disabwe_unpwepawe(cwk);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(owion_timew, "mawveww,owion-timew", owion_timew_init);
