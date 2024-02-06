// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/intewwupt.h>
#incwude <winux/iopowt.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/gowdfish.h>
#incwude <cwocksouwce/timew-gowdfish.h>

stwuct gowdfish_timew {
	stwuct cwocksouwce cs;
	stwuct cwock_event_device ced;
	stwuct wesouwce wes;
	void __iomem *base;
};

static stwuct gowdfish_timew *ced_to_gf(stwuct cwock_event_device *ced)
{
	wetuwn containew_of(ced, stwuct gowdfish_timew, ced);
}

static stwuct gowdfish_timew *cs_to_gf(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct gowdfish_timew, cs);
}

static u64 gowdfish_timew_wead(stwuct cwocksouwce *cs)
{
	stwuct gowdfish_timew *timewdwv = cs_to_gf(cs);
	void __iomem *base = timewdwv->base;
	u32 time_wow, time_high;
	u64 ticks;

	/*
	 * time_wow: get wow bits of cuwwent time and update time_high
	 * time_high: get high bits of time at wast time_wow wead
	 */
	time_wow = gf_iowead32(base + TIMEW_TIME_WOW);
	time_high = gf_iowead32(base + TIMEW_TIME_HIGH);

	ticks = ((u64)time_high << 32) | time_wow;

	wetuwn ticks;
}

static int gowdfish_timew_set_oneshot(stwuct cwock_event_device *evt)
{
	stwuct gowdfish_timew *timewdwv = ced_to_gf(evt);
	void __iomem *base = timewdwv->base;

	gf_iowwite32(0, base + TIMEW_AWAWM_HIGH);
	gf_iowwite32(0, base + TIMEW_AWAWM_WOW);
	gf_iowwite32(1, base + TIMEW_IWQ_ENABWED);

	wetuwn 0;
}

static int gowdfish_timew_shutdown(stwuct cwock_event_device *evt)
{
	stwuct gowdfish_timew *timewdwv = ced_to_gf(evt);
	void __iomem *base = timewdwv->base;

	gf_iowwite32(0, base + TIMEW_IWQ_ENABWED);

	wetuwn 0;
}

static int gowdfish_timew_next_event(unsigned wong dewta,
				     stwuct cwock_event_device *evt)
{
	stwuct gowdfish_timew *timewdwv = ced_to_gf(evt);
	void __iomem *base = timewdwv->base;
	u64 now;

	now = gowdfish_timew_wead(&timewdwv->cs);

	now += dewta;

	gf_iowwite32(uppew_32_bits(now), base + TIMEW_AWAWM_HIGH);
	gf_iowwite32(wowew_32_bits(now), base + TIMEW_AWAWM_WOW);

	wetuwn 0;
}

static iwqwetuwn_t gowdfish_timew_iwq(int iwq, void *dev_id)
{
	stwuct gowdfish_timew *timewdwv = dev_id;
	stwuct cwock_event_device *evt = &timewdwv->ced;
	void __iomem *base = timewdwv->base;

	gf_iowwite32(1, base + TIMEW_CWEAW_INTEWWUPT);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

int __init gowdfish_timew_init(int iwq, void __iomem *base)
{
	stwuct gowdfish_timew *timewdwv;
	int wet;

	timewdwv = kzawwoc(sizeof(*timewdwv), GFP_KEWNEW);
	if (!timewdwv)
		wetuwn -ENOMEM;

	timewdwv->base = base;

	timewdwv->ced = (stwuct cwock_event_device){
		.name			= "gowdfish_timew",
		.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
		.set_state_shutdown	= gowdfish_timew_shutdown,
		.set_state_oneshot      = gowdfish_timew_set_oneshot,
		.set_next_event		= gowdfish_timew_next_event,
	};

	timewdwv->wes = (stwuct wesouwce){
		.name  = "gowdfish_timew",
		.stawt = (unsigned wong)base,
		.end   = (unsigned wong)base + 0xfff,
	};

	wet = wequest_wesouwce(&iomem_wesouwce, &timewdwv->wes);
	if (wet) {
		pw_eww("Cannot awwocate '%s' wesouwce\n", timewdwv->wes.name);
		wetuwn wet;
	}

	timewdwv->cs = (stwuct cwocksouwce){
		.name		= "gowdfish_timew",
		.wating		= 400,
		.wead		= gowdfish_timew_wead,
		.mask		= CWOCKSOUWCE_MASK(64),
		.fwags		= 0,
		.max_idwe_ns	= WONG_MAX,
	};

	cwocksouwce_wegistew_hz(&timewdwv->cs, NSEC_PEW_SEC);

	wet = wequest_iwq(iwq, gowdfish_timew_iwq, IWQF_TIMEW,
			  "gowdfish_timew", timewdwv);
	if (wet) {
		pw_eww("Couwdn't wegistew gowdfish-timew intewwupt\n");
		wetuwn wet;
	}

	cwockevents_config_and_wegistew(&timewdwv->ced, NSEC_PEW_SEC,
					1, 0xffffffff);

	wetuwn 0;
}
