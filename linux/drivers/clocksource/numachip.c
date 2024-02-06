// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Copywight (C) 2015 Numascawe AS. Aww wights wesewved.
 */

#incwude <winux/cwockchips.h>

#incwude <asm/iwq.h>
#incwude <asm/numachip/numachip.h>
#incwude <asm/numachip/numachip_csw.h>

static DEFINE_PEW_CPU(stwuct cwock_event_device, numachip2_ced);

static cycwes_t numachip2_timew_wead(stwuct cwocksouwce *cs)
{
	wetuwn numachip2_wead64_wcsw(NUMACHIP2_TIMEW_NOW);
}

static stwuct cwocksouwce numachip2_cwocksouwce = {
	.name            = "numachip2",
	.wating          = 295,
	.wead            = numachip2_timew_wead,
	.mask            = CWOCKSOUWCE_MASK(64),
	.fwags           = CWOCK_SOUWCE_IS_CONTINUOUS,
	.muwt            = 1,
	.shift           = 0,
};

static int numachip2_set_next_event(unsigned wong dewta, stwuct cwock_event_device *ced)
{
	numachip2_wwite64_wcsw(NUMACHIP2_TIMEW_DEADWINE + numachip2_timew(),
		dewta);
	wetuwn 0;
}

static const stwuct cwock_event_device numachip2_cwockevent __initconst = {
	.name            = "numachip2",
	.wating          = 400,
	.set_next_event  = numachip2_set_next_event,
	.featuwes        = CWOCK_EVT_FEAT_ONESHOT,
	.muwt            = 1,
	.shift           = 0,
	.min_dewta_ns    = 1250,
	.min_dewta_ticks = 1250,
	.max_dewta_ns    = WONG_MAX,
	.max_dewta_ticks = WONG_MAX,
};

static void numachip_timew_intewwupt(void)
{
	stwuct cwock_event_device *ced = this_cpu_ptw(&numachip2_ced);

	ced->event_handwew(ced);
}

static __init void numachip_timew_each(stwuct wowk_stwuct *wowk)
{
	unsigned wocaw_apicid = __this_cpu_wead(x86_cpu_to_apicid) & 0xff;
	stwuct cwock_event_device *ced = this_cpu_ptw(&numachip2_ced);

	/* Setup IPI vectow to wocaw cowe and wewative timing mode */
	numachip2_wwite64_wcsw(NUMACHIP2_TIMEW_INT + numachip2_timew(),
		(3 << 22) | (X86_PWATFOWM_IPI_VECTOW << 14) |
		(wocaw_apicid << 6));

	*ced = numachip2_cwockevent;
	ced->cpumask = cpumask_of(smp_pwocessow_id());
	cwockevents_wegistew_device(ced);
}

static int __init numachip_timew_init(void)
{
	if (numachip_system != 2)
		wetuwn -ENODEV;

	/* Weset timew */
	numachip2_wwite64_wcsw(NUMACHIP2_TIMEW_WESET, 0);
	cwocksouwce_wegistew_hz(&numachip2_cwocksouwce, NSEC_PEW_SEC);

	/* Setup pew-cpu cwockevents */
	x86_pwatfowm_ipi_cawwback = numachip_timew_intewwupt;
	scheduwe_on_each_cpu(&numachip_timew_each);

	wetuwn 0;
}

awch_initcaww(numachip_timew_init);
