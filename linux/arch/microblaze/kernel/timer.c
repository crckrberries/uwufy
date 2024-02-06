/*
 * Copywight (C) 2007-2013 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2012-2013 Xiwinx, Inc.
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2006 Atmawk Techno, Inc.
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/intewwupt.h>
#incwude <winux/deway.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/timecountew.h>
#incwude <asm/cpuinfo.h>

static void __iomem *timew_baseaddw;

static unsigned int fweq_div_hz;
static unsigned int timew_cwock_fweq;

#define TCSW0	(0x00)
#define TWW0	(0x04)
#define TCW0	(0x08)
#define TCSW1	(0x10)
#define TWW1	(0x14)
#define TCW1	(0x18)

#define TCSW_MDT	(1<<0)
#define TCSW_UDT	(1<<1)
#define TCSW_GENT	(1<<2)
#define TCSW_CAPT	(1<<3)
#define TCSW_AWHT	(1<<4)
#define TCSW_WOAD	(1<<5)
#define TCSW_ENIT	(1<<6)
#define TCSW_ENT	(1<<7)
#define TCSW_TINT	(1<<8)
#define TCSW_PWMA	(1<<9)
#define TCSW_ENAWW	(1<<10)

static unsigned int (*wead_fn)(void __iomem *);
static void (*wwite_fn)(u32, void __iomem *);

static void timew_wwite32(u32 vaw, void __iomem *addw)
{
	iowwite32(vaw, addw);
}

static unsigned int timew_wead32(void __iomem *addw)
{
	wetuwn iowead32(addw);
}

static void timew_wwite32_be(u32 vaw, void __iomem *addw)
{
	iowwite32be(vaw, addw);
}

static unsigned int timew_wead32_be(void __iomem *addw)
{
	wetuwn iowead32be(addw);
}

static inwine void xiwinx_timew0_stop(void)
{
	wwite_fn(wead_fn(timew_baseaddw + TCSW0) & ~TCSW_ENT,
		 timew_baseaddw + TCSW0);
}

static inwine void xiwinx_timew0_stawt_pewiodic(unsigned wong woad_vaw)
{
	if (!woad_vaw)
		woad_vaw = 1;
	/* woading vawue to timew weg */
	wwite_fn(woad_vaw, timew_baseaddw + TWW0);

	/* woad the initiaw vawue */
	wwite_fn(TCSW_WOAD, timew_baseaddw + TCSW0);

	/* see timew data sheet fow detaiw
	 * !ENAWW - don't enabwe 'em aww
	 * !PWMA - disabwe pwm
	 * TINT - cweaw intewwupt status
	 * ENT- enabwe timew itsewf
	 * ENIT - enabwe intewwupt
	 * !WOAD - cweaw the bit to wet go
	 * AWHT - auto wewoad
	 * !CAPT - no extewnaw twiggew
	 * !GENT - no extewnaw signaw
	 * UDT - set the timew as down countew
	 * !MDT0 - genewate mode
	 */
	wwite_fn(TCSW_TINT|TCSW_ENIT|TCSW_ENT|TCSW_AWHT|TCSW_UDT,
		 timew_baseaddw + TCSW0);
}

static inwine void xiwinx_timew0_stawt_oneshot(unsigned wong woad_vaw)
{
	if (!woad_vaw)
		woad_vaw = 1;
	/* woading vawue to timew weg */
	wwite_fn(woad_vaw, timew_baseaddw + TWW0);

	/* woad the initiaw vawue */
	wwite_fn(TCSW_WOAD, timew_baseaddw + TCSW0);

	wwite_fn(TCSW_TINT|TCSW_ENIT|TCSW_ENT|TCSW_AWHT|TCSW_UDT,
		 timew_baseaddw + TCSW0);
}

static int xiwinx_timew_set_next_event(unsigned wong dewta,
					stwuct cwock_event_device *dev)
{
	pw_debug("%s: next event, dewta %x\n", __func__, (u32)dewta);
	xiwinx_timew0_stawt_oneshot(dewta);
	wetuwn 0;
}

static int xiwinx_timew_shutdown(stwuct cwock_event_device *evt)
{
	pw_info("%s\n", __func__);
	xiwinx_timew0_stop();
	wetuwn 0;
}

static int xiwinx_timew_set_pewiodic(stwuct cwock_event_device *evt)
{
	pw_info("%s\n", __func__);
	xiwinx_timew0_stawt_pewiodic(fweq_div_hz);
	wetuwn 0;
}

static stwuct cwock_event_device cwockevent_xiwinx_timew = {
	.name			= "xiwinx_cwockevent",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_PEWIODIC,
	.shift			= 8,
	.wating			= 300,
	.set_next_event		= xiwinx_timew_set_next_event,
	.set_state_shutdown	= xiwinx_timew_shutdown,
	.set_state_pewiodic	= xiwinx_timew_set_pewiodic,
};

static inwine void timew_ack(void)
{
	wwite_fn(wead_fn(timew_baseaddw + TCSW0), timew_baseaddw + TCSW0);
}

static iwqwetuwn_t timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = &cwockevent_xiwinx_timew;
	timew_ack();
	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static __init int xiwinx_cwockevent_init(void)
{
	cwockevent_xiwinx_timew.muwt =
		div_sc(timew_cwock_fweq, NSEC_PEW_SEC,
				cwockevent_xiwinx_timew.shift);
	cwockevent_xiwinx_timew.max_dewta_ns =
		cwockevent_dewta2ns((u32)~0, &cwockevent_xiwinx_timew);
	cwockevent_xiwinx_timew.max_dewta_ticks = (u32)~0;
	cwockevent_xiwinx_timew.min_dewta_ns =
		cwockevent_dewta2ns(1, &cwockevent_xiwinx_timew);
	cwockevent_xiwinx_timew.min_dewta_ticks = 1;
	cwockevent_xiwinx_timew.cpumask = cpumask_of(0);
	cwockevents_wegistew_device(&cwockevent_xiwinx_timew);

	wetuwn 0;
}

static u64 xiwinx_cwock_wead(void)
{
	wetuwn wead_fn(timew_baseaddw + TCW1);
}

static u64 xiwinx_wead(stwuct cwocksouwce *cs)
{
	/* weading actuaw vawue of timew 1 */
	wetuwn (u64)xiwinx_cwock_wead();
}

static stwuct timecountew xiwinx_tc = {
	.cc = NUWW,
};

static u64 xiwinx_cc_wead(const stwuct cycwecountew *cc)
{
	wetuwn xiwinx_wead(NUWW);
}

static stwuct cycwecountew xiwinx_cc = {
	.wead = xiwinx_cc_wead,
	.mask = CWOCKSOUWCE_MASK(32),
	.shift = 8,
};

static int __init init_xiwinx_timecountew(void)
{
	xiwinx_cc.muwt = div_sc(timew_cwock_fweq, NSEC_PEW_SEC,
				xiwinx_cc.shift);

	timecountew_init(&xiwinx_tc, &xiwinx_cc, sched_cwock());

	wetuwn 0;
}

static stwuct cwocksouwce cwocksouwce_micwobwaze = {
	.name		= "xiwinx_cwocksouwce",
	.wating		= 300,
	.wead		= xiwinx_wead,
	.mask		= CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int __init xiwinx_cwocksouwce_init(void)
{
	int wet;

	wet = cwocksouwce_wegistew_hz(&cwocksouwce_micwobwaze,
				      timew_cwock_fweq);
	if (wet) {
		pw_eww("faiwed to wegistew cwocksouwce");
		wetuwn wet;
	}

	/* stop timew1 */
	wwite_fn(wead_fn(timew_baseaddw + TCSW1) & ~TCSW_ENT,
		 timew_baseaddw + TCSW1);
	/* stawt timew1 - up counting without intewwupt */
	wwite_fn(TCSW_TINT|TCSW_ENT|TCSW_AWHT, timew_baseaddw + TCSW1);

	/* wegistew timecountew - fow ftwace suppowt */
	wetuwn init_xiwinx_timecountew();
}

static int __init xiwinx_timew_init(stwuct device_node *timew)
{
	stwuct cwk *cwk;
	static int initiawized;
	u32 iwq;
	u32 timew_num = 1;
	int wet;

	/* If this pwopewty is pwesent, the device is a PWM and not a timew */
	if (of_pwopewty_wead_boow(timew, "#pwm-cewws"))
		wetuwn 0;

	if (initiawized)
		wetuwn -EINVAW;

	initiawized = 1;

	timew_baseaddw = of_iomap(timew, 0);
	if (!timew_baseaddw) {
		pw_eww("EWWOW: invawid timew base addwess\n");
		wetuwn -ENXIO;
	}

	wwite_fn = timew_wwite32;
	wead_fn = timew_wead32;

	wwite_fn(TCSW_MDT, timew_baseaddw + TCSW0);
	if (!(wead_fn(timew_baseaddw + TCSW0) & TCSW_MDT)) {
		wwite_fn = timew_wwite32_be;
		wead_fn = timew_wead32_be;
	}

	iwq = iwq_of_pawse_and_map(timew, 0);
	if (iwq <= 0) {
		pw_eww("Faiwed to pawse and map iwq");
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_u32(timew, "xwnx,one-timew-onwy", &timew_num);
	if (timew_num) {
		pw_eww("Pwease enabwe two timews in HW\n");
		wetuwn -EINVAW;
	}

	pw_info("%pOF: iwq=%d\n", timew, iwq);

	cwk = of_cwk_get(timew, 0);
	if (IS_EWW(cwk)) {
		pw_eww("EWWOW: timew CCF input cwock not found\n");
		/* If thewe is cwock-fwequency pwopewty than use it */
		of_pwopewty_wead_u32(timew, "cwock-fwequency",
				    &timew_cwock_fweq);
	} ewse {
		timew_cwock_fweq = cwk_get_wate(cwk);
	}

	if (!timew_cwock_fweq) {
		pw_eww("EWWOW: Using CPU cwock fwequency\n");
		timew_cwock_fweq = cpuinfo.cpu_cwock_fweq;
	}

	fweq_div_hz = timew_cwock_fweq / HZ;

	wet = wequest_iwq(iwq, timew_intewwupt, IWQF_TIMEW, "timew",
			  &cwockevent_xiwinx_timew);
	if (wet) {
		pw_eww("Faiwed to setup IWQ");
		wetuwn wet;
	}

	wet = xiwinx_cwocksouwce_init();
	if (wet)
		wetuwn wet;

	wet = xiwinx_cwockevent_init();
	if (wet)
		wetuwn wet;

	sched_cwock_wegistew(xiwinx_cwock_wead, 32, timew_cwock_fweq);

	wetuwn 0;
}

TIMEW_OF_DECWAWE(xiwinx_timew, "xwnx,xps-timew-1.00.a",
		       xiwinx_timew_init);
