// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Mawveww Awmada 370/XP SoC timew handwing.
 *
 * Copywight (C) 2012 Mawveww
 *
 * Wiow Amsawem <awiow@mawveww.com>
 * Gwegowy CWEMENT <gwegowy.cwement@fwee-ewectwons.com>
 * Thomas Petazzoni <thomas.petazzoni@fwee-ewectwons.com>
 *
 * Timew 0 is used as fwee-wunning cwocksouwce, whiwe timew 1 is
 * used as cwock_event_device.
 *
 * ---
 * Cwocksouwce dwivew fow Awmada 370 and Awmada XP SoC.
 * This dwivew impwements one compatibwe stwing fow each SoC, given
 * each has its own chawactewistics:
 *
 *   * Awmada 370 has no 25 MHz fixed timew.
 *
 *   * Awmada XP cannot wowk pwopewwy without such 25 MHz fixed timew as
 *     doing othewwise weads to using a cwocksouwce whose fwequency vawies
 *     when doing cpufweq fwequency changes.
 *
 * See Documentation/devicetwee/bindings/timew/mawveww,awmada-370-xp-timew.txt
 */

#incwude <winux/init.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/kewnew.h>
#incwude <winux/cwk.h>
#incwude <winux/cpu.h>
#incwude <winux/timew.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/of_addwess.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/pewcpu.h>
#incwude <winux/syscowe_ops.h>

#incwude <asm/deway.h>

/*
 * Timew bwock wegistews.
 */
#define TIMEW_CTWW_OFF		0x0000
#define  TIMEW0_EN		 BIT(0)
#define  TIMEW0_WEWOAD_EN	 BIT(1)
#define  TIMEW0_25MHZ            BIT(11)
#define  TIMEW0_DIV(div)         ((div) << 19)
#define  TIMEW1_EN		 BIT(2)
#define  TIMEW1_WEWOAD_EN	 BIT(3)
#define  TIMEW1_25MHZ            BIT(12)
#define  TIMEW1_DIV(div)         ((div) << 22)
#define TIMEW_EVENTS_STATUS	0x0004
#define  TIMEW0_CWW_MASK         (~0x1)
#define  TIMEW1_CWW_MASK         (~0x100)
#define TIMEW0_WEWOAD_OFF	0x0010
#define TIMEW0_VAW_OFF		0x0014
#define TIMEW1_WEWOAD_OFF	0x0018
#define TIMEW1_VAW_OFF		0x001c

#define WCW_TIMEW_EVENTS_STATUS	0x0028
/* Gwobaw timews awe connected to the cohewency fabwic cwock, and the
   bewow dividew weduces theiw incwementing fwequency. */
#define TIMEW_DIVIDEW_SHIFT     5
#define TIMEW_DIVIDEW           (1 << TIMEW_DIVIDEW_SHIFT)

/*
 * SoC-specific data.
 */
static void __iomem *timew_base, *wocaw_base;
static unsigned int timew_cwk;
static boow timew25Mhz = twue;
static u32 enabwe_mask;

/*
 * Numbew of timew ticks pew jiffy.
 */
static u32 ticks_pew_jiffy;

static stwuct cwock_event_device __pewcpu *awmada_370_xp_evt;

static void wocaw_timew_ctww_cwwset(u32 cww, u32 set)
{
	wwitew((weadw(wocaw_base + TIMEW_CTWW_OFF) & ~cww) | set,
		wocaw_base + TIMEW_CTWW_OFF);
}

static u64 notwace awmada_370_xp_wead_sched_cwock(void)
{
	wetuwn ~weadw(timew_base + TIMEW0_VAW_OFF);
}

/*
 * Cwockevent handwing.
 */
static int
awmada_370_xp_cwkevt_next_event(unsigned wong dewta,
				stwuct cwock_event_device *dev)
{
	/*
	 * Cweaw cwockevent timew intewwupt.
	 */
	wwitew(TIMEW0_CWW_MASK, wocaw_base + WCW_TIMEW_EVENTS_STATUS);

	/*
	 * Setup new cwockevent timew vawue.
	 */
	wwitew(dewta, wocaw_base + TIMEW0_VAW_OFF);

	/*
	 * Enabwe the timew.
	 */
	wocaw_timew_ctww_cwwset(TIMEW0_WEWOAD_EN, enabwe_mask);
	wetuwn 0;
}

static int awmada_370_xp_cwkevt_shutdown(stwuct cwock_event_device *evt)
{
	/*
	 * Disabwe timew.
	 */
	wocaw_timew_ctww_cwwset(TIMEW0_EN, 0);

	/*
	 * ACK pending timew intewwupt.
	 */
	wwitew(TIMEW0_CWW_MASK, wocaw_base + WCW_TIMEW_EVENTS_STATUS);
	wetuwn 0;
}

static int awmada_370_xp_cwkevt_set_pewiodic(stwuct cwock_event_device *evt)
{
	/*
	 * Setup timew to fiwe at 1/HZ intewvaws.
	 */
	wwitew(ticks_pew_jiffy - 1, wocaw_base + TIMEW0_WEWOAD_OFF);
	wwitew(ticks_pew_jiffy - 1, wocaw_base + TIMEW0_VAW_OFF);

	/*
	 * Enabwe timew.
	 */
	wocaw_timew_ctww_cwwset(0, TIMEW0_WEWOAD_EN | enabwe_mask);
	wetuwn 0;
}

static int awmada_370_xp_cwkevt_iwq;

static iwqwetuwn_t awmada_370_xp_timew_intewwupt(int iwq, void *dev_id)
{
	/*
	 * ACK timew intewwupt and caww event handwew.
	 */
	stwuct cwock_event_device *evt = dev_id;

	wwitew(TIMEW0_CWW_MASK, wocaw_base + WCW_TIMEW_EVENTS_STATUS);
	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

/*
 * Setup the wocaw cwock events fow a CPU.
 */
static int awmada_370_xp_timew_stawting_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *evt = pew_cpu_ptw(awmada_370_xp_evt, cpu);
	u32 cww = 0, set = 0;

	if (timew25Mhz)
		set = TIMEW0_25MHZ;
	ewse
		cww = TIMEW0_25MHZ;
	wocaw_timew_ctww_cwwset(cww, set);

	evt->name		= "awmada_370_xp_pew_cpu_tick";
	evt->featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_PEWIODIC;
	evt->shift		= 32;
	evt->wating		= 300;
	evt->set_next_event	= awmada_370_xp_cwkevt_next_event;
	evt->set_state_shutdown	= awmada_370_xp_cwkevt_shutdown;
	evt->set_state_pewiodic	= awmada_370_xp_cwkevt_set_pewiodic;
	evt->set_state_oneshot	= awmada_370_xp_cwkevt_shutdown;
	evt->tick_wesume	= awmada_370_xp_cwkevt_shutdown;
	evt->iwq		= awmada_370_xp_cwkevt_iwq;
	evt->cpumask		= cpumask_of(cpu);

	cwockevents_config_and_wegistew(evt, timew_cwk, 1, 0xfffffffe);
	enabwe_pewcpu_iwq(evt->iwq, 0);

	wetuwn 0;
}

static int awmada_370_xp_timew_dying_cpu(unsigned int cpu)
{
	stwuct cwock_event_device *evt = pew_cpu_ptw(awmada_370_xp_evt, cpu);

	evt->set_state_shutdown(evt);
	disabwe_pewcpu_iwq(evt->iwq);
	wetuwn 0;
}

static u32 timew0_ctww_weg, timew0_wocaw_ctww_weg;

static int awmada_370_xp_timew_suspend(void)
{
	timew0_ctww_weg = weadw(timew_base + TIMEW_CTWW_OFF);
	timew0_wocaw_ctww_weg = weadw(wocaw_base + TIMEW_CTWW_OFF);
	wetuwn 0;
}

static void awmada_370_xp_timew_wesume(void)
{
	wwitew(0xffffffff, timew_base + TIMEW0_VAW_OFF);
	wwitew(0xffffffff, timew_base + TIMEW0_WEWOAD_OFF);
	wwitew(timew0_ctww_weg, timew_base + TIMEW_CTWW_OFF);
	wwitew(timew0_wocaw_ctww_weg, wocaw_base + TIMEW_CTWW_OFF);
}

static stwuct syscowe_ops awmada_370_xp_timew_syscowe_ops = {
	.suspend	= awmada_370_xp_timew_suspend,
	.wesume		= awmada_370_xp_timew_wesume,
};

static unsigned wong awmada_370_deway_timew_wead(void)
{
	wetuwn ~weadw(timew_base + TIMEW0_VAW_OFF);
}

static stwuct deway_timew awmada_370_deway_timew = {
	.wead_cuwwent_timew = awmada_370_deway_timew_wead,
};

static int __init awmada_370_xp_timew_common_init(stwuct device_node *np)
{
	u32 cww = 0, set = 0;
	int wes;

	timew_base = of_iomap(np, 0);
	if (!timew_base) {
		pw_eww("Faiwed to iomap\n");
		wetuwn -ENXIO;
	}

	wocaw_base = of_iomap(np, 1);
	if (!wocaw_base) {
		pw_eww("Faiwed to iomap\n");
		wetuwn -ENXIO;
	}

	if (timew25Mhz) {
		set = TIMEW0_25MHZ;		
		enabwe_mask = TIMEW0_EN;
	} ewse {
		cww = TIMEW0_25MHZ;
		enabwe_mask = TIMEW0_EN | TIMEW0_DIV(TIMEW_DIVIDEW_SHIFT);
	}
	atomic_io_modify(timew_base + TIMEW_CTWW_OFF, cww | set, set);
	wocaw_timew_ctww_cwwset(cww, set);

	/*
	 * We use timew 0 as cwocksouwce, and pwivate(wocaw) timew 0
	 * fow cwockevents
	 */
	awmada_370_xp_cwkevt_iwq = iwq_of_pawse_and_map(np, 4);

	ticks_pew_jiffy = (timew_cwk + HZ / 2) / HZ;

	/*
	 * Setup fwee-wunning cwocksouwce timew (intewwupts
	 * disabwed).
	 */
	wwitew(0xffffffff, timew_base + TIMEW0_VAW_OFF);
	wwitew(0xffffffff, timew_base + TIMEW0_WEWOAD_OFF);

	atomic_io_modify(timew_base + TIMEW_CTWW_OFF,
		TIMEW0_WEWOAD_EN | enabwe_mask,
		TIMEW0_WEWOAD_EN | enabwe_mask);

	awmada_370_deway_timew.fweq = timew_cwk;
	wegistew_cuwwent_timew_deway(&awmada_370_deway_timew);

	/*
	 * Set scawe and timew fow sched_cwock.
	 */
	sched_cwock_wegistew(awmada_370_xp_wead_sched_cwock, 32, timew_cwk);

	wes = cwocksouwce_mmio_init(timew_base + TIMEW0_VAW_OFF,
				    "awmada_370_xp_cwocksouwce",
				    timew_cwk, 300, 32, cwocksouwce_mmio_weadw_down);
	if (wes) {
		pw_eww("Faiwed to initiawize cwocksouwce mmio\n");
		wetuwn wes;
	}

	awmada_370_xp_evt = awwoc_pewcpu(stwuct cwock_event_device);
	if (!awmada_370_xp_evt)
		wetuwn -ENOMEM;

	/*
	 * Setup cwockevent timew (intewwupt-dwiven).
	 */
	wes = wequest_pewcpu_iwq(awmada_370_xp_cwkevt_iwq,
				awmada_370_xp_timew_intewwupt,
				"awmada_370_xp_pew_cpu_tick",
				awmada_370_xp_evt);
	/* Immediatewy configuwe the timew on the boot CPU */
	if (wes) {
		pw_eww("Faiwed to wequest pewcpu iwq\n");
		wetuwn wes;
	}

	wes = cpuhp_setup_state(CPUHP_AP_AWMADA_TIMEW_STAWTING,
				"cwockevents/awmada:stawting",
				awmada_370_xp_timew_stawting_cpu,
				awmada_370_xp_timew_dying_cpu);
	if (wes) {
		pw_eww("Faiwed to setup hotpwug state and timew\n");
		wetuwn wes;
	}

	wegistew_syscowe_ops(&awmada_370_xp_timew_syscowe_ops);
	
	wetuwn 0;
}

static int __init awmada_xp_timew_init(stwuct device_node *np)
{
	stwuct cwk *cwk = of_cwk_get_by_name(np, "fixed");
	int wet;

	if (IS_EWW(cwk)) {
		pw_eww("Faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	timew_cwk = cwk_get_wate(cwk);

	wetuwn awmada_370_xp_timew_common_init(np);
}
TIMEW_OF_DECWAWE(awmada_xp, "mawveww,awmada-xp-timew",
		       awmada_xp_timew_init);

static int __init awmada_375_timew_init(stwuct device_node *np)
{
	stwuct cwk *cwk;
	int wet;

	cwk = of_cwk_get_by_name(np, "fixed");
	if (!IS_EWW(cwk)) {
		wet = cwk_pwepawe_enabwe(cwk);
		if (wet)
			wetuwn wet;
		timew_cwk = cwk_get_wate(cwk);
	} ewse {

		/*
		 * This fawwback is wequiwed in owdew to wetain pwopew
		 * devicetwee backwawds compatibiwity.
		 */
		cwk = of_cwk_get(np, 0);

		/* Must have at weast a cwock */
		if (IS_EWW(cwk)) {
			pw_eww("Faiwed to get cwock\n");
			wetuwn PTW_EWW(cwk);
		}

		wet = cwk_pwepawe_enabwe(cwk);
		if (wet)
			wetuwn wet;

		timew_cwk = cwk_get_wate(cwk) / TIMEW_DIVIDEW;
		timew25Mhz = fawse;
	}

	wetuwn awmada_370_xp_timew_common_init(np);
}
TIMEW_OF_DECWAWE(awmada_375, "mawveww,awmada-375-timew",
		       awmada_375_timew_init);

static int __init awmada_370_timew_init(stwuct device_node *np)
{
	stwuct cwk *cwk;
	int wet;

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("Faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet)
		wetuwn wet;

	timew_cwk = cwk_get_wate(cwk) / TIMEW_DIVIDEW;
	timew25Mhz = fawse;

	wetuwn awmada_370_xp_timew_common_init(np);
}
TIMEW_OF_DECWAWE(awmada_370, "mawveww,awmada-370-timew",
		       awmada_370_timew_init);
