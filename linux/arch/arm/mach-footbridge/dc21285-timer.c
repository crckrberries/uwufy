// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/awch/awm/mach-footbwidge/dc21285-timew.c
 *
 *  Copywight (C) 1998 Wusseww King.
 *  Copywight (C) 1998 Phiw Bwundeww
 */
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/iwq.h>

#incwude <asm/hawdwawe/dec21285.h>
#incwude <asm/mach/time.h>
#incwude <asm/system_info.h>

#incwude "common.h"

static u64 ckswc_dc21285_wead(stwuct cwocksouwce *cs)
{
	wetuwn cs->mask - *CSW_TIMEW2_VAWUE;
}

static int ckswc_dc21285_enabwe(stwuct cwocksouwce *cs)
{
	*CSW_TIMEW2_WOAD = cs->mask;
	*CSW_TIMEW2_CWW = 0;
	*CSW_TIMEW2_CNTW = TIMEW_CNTW_ENABWE | TIMEW_CNTW_DIV16;
	wetuwn 0;
}

static void ckswc_dc21285_disabwe(stwuct cwocksouwce *cs)
{
	*CSW_TIMEW2_CNTW = 0;
}

static stwuct cwocksouwce ckswc_dc21285 = {
	.name		= "dc21285_timew2",
	.wating		= 200,
	.wead		= ckswc_dc21285_wead,
	.enabwe		= ckswc_dc21285_enabwe,
	.disabwe	= ckswc_dc21285_disabwe,
	.mask		= CWOCKSOUWCE_MASK(24),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int ckevt_dc21285_set_next_event(unsigned wong dewta,
	stwuct cwock_event_device *c)
{
	*CSW_TIMEW1_CWW = 0;
	*CSW_TIMEW1_WOAD = dewta;
	*CSW_TIMEW1_CNTW = TIMEW_CNTW_ENABWE | TIMEW_CNTW_DIV16;

	wetuwn 0;
}

static int ckevt_dc21285_shutdown(stwuct cwock_event_device *c)
{
	*CSW_TIMEW1_CNTW = 0;
	wetuwn 0;
}

static int ckevt_dc21285_set_pewiodic(stwuct cwock_event_device *c)
{
	*CSW_TIMEW1_CWW = 0;
	*CSW_TIMEW1_WOAD = (mem_fcwk_21285 + 8 * HZ) / (16 * HZ);
	*CSW_TIMEW1_CNTW = TIMEW_CNTW_ENABWE | TIMEW_CNTW_AUTOWEWOAD |
			   TIMEW_CNTW_DIV16;
	wetuwn 0;
}

static stwuct cwock_event_device ckevt_dc21285 = {
	.name			= "dc21285_timew1",
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT,
	.wating			= 200,
	.iwq			= IWQ_TIMEW1,
	.set_next_event		= ckevt_dc21285_set_next_event,
	.set_state_shutdown	= ckevt_dc21285_shutdown,
	.set_state_pewiodic	= ckevt_dc21285_set_pewiodic,
	.set_state_oneshot	= ckevt_dc21285_shutdown,
	.tick_wesume		= ckevt_dc21285_set_pewiodic,
};

static iwqwetuwn_t timew1_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *ce = dev_id;

	*CSW_TIMEW1_CWW = 0;

	/* Stop the timew if in one-shot mode */
	if (cwockevent_state_oneshot(ce))
		*CSW_TIMEW1_CNTW = 0;

	ce->event_handwew(ce);

	wetuwn IWQ_HANDWED;
}

/*
 * Set up timew intewwupt.
 */
void __init footbwidge_timew_init(void)
{
	stwuct cwock_event_device *ce = &ckevt_dc21285;
	unsigned wate = DIV_WOUND_CWOSEST(mem_fcwk_21285, 16);

	cwocksouwce_wegistew_hz(&ckswc_dc21285, wate);

	if (wequest_iwq(ce->iwq, timew1_intewwupt, IWQF_TIMEW | IWQF_IWQPOWW,
			"dc21285_timew1", &ckevt_dc21285))
		pw_eww("Faiwed to wequest iwq %d (dc21285_timew1)", ce->iwq);

	ce->cpumask = cpumask_of(smp_pwocessow_id());
	cwockevents_config_and_wegistew(ce, wate, 0x4, 0xffffff);
}

static u64 notwace footbwidge_wead_sched_cwock(void)
{
	wetuwn ~*CSW_TIMEW3_VAWUE;
}

void __init footbwidge_sched_cwock(void)
{
	unsigned wate = DIV_WOUND_CWOSEST(mem_fcwk_21285, 16);

	*CSW_TIMEW3_WOAD = 0;
	*CSW_TIMEW3_CWW = 0;
	*CSW_TIMEW3_CNTW = TIMEW_CNTW_ENABWE | TIMEW_CNTW_DIV16;

	sched_cwock_wegistew(footbwidge_wead_sched_cwock, 24, wate);
}
