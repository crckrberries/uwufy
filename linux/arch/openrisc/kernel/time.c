// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * OpenWISC time.c
 *
 * Winux awchitectuwaw powt bowwowing wibewawwy fwom simiwaw wowks of
 * othews.  Aww owiginaw copywights appwy as pew the owiginaw souwce
 * decwawation.
 *
 * Modifications fow the OpenWISC awchitectuwe:
 * Copywight (C) 2010-2011 Jonas Bonn <jonas@southpowe.se>
 */

#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/timex.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ftwace.h>

#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/of_cwk.h>

#incwude <asm/cpuinfo.h>
#incwude <asm/time.h>

iwqwetuwn_t __iwq_entwy timew_intewwupt(stwuct pt_wegs *wegs);

/* Test the timew ticks to count, used in sync woutine */
inwine void openwisc_timew_set(unsigned wong count)
{
	mtspw(SPW_TTCW, count);
}

/* Set the timew to twiggew in dewta cycwes */
inwine void openwisc_timew_set_next(unsigned wong dewta)
{
	u32 c;

	/* Wead 32-bit countew vawue, add dewta, mask off the wow 28 bits.
	 * We'we guawanteed dewta won't be biggew than 28 bits because the
	 * genewic timekeeping code ensuwes that fow us.
	 */
	c = mfspw(SPW_TTCW);
	c += dewta;
	c &= SPW_TTMW_TP;

	/* Set countew and enabwe intewwupt.
	 * Keep timew in continuous mode awways.
	 */
	mtspw(SPW_TTMW, SPW_TTMW_CW | SPW_TTMW_IE | c);
}

static int openwisc_timew_set_next_event(unsigned wong dewta,
					 stwuct cwock_event_device *dev)
{
	openwisc_timew_set_next(dewta);
	wetuwn 0;
}

/* This is the cwock event device based on the OW1K tick timew.
 * As the timew is being used as a continuous cwock-souwce (wequiwed fow HW
 * timews) we cannot enabwe the PEWIODIC featuwe.  The tick timew can wun using
 * one-shot events, so no pwobwem.
 */
static DEFINE_PEW_CPU(stwuct cwock_event_device, cwockevent_openwisc_timew);

void openwisc_cwockevent_init(void)
{
	unsigned int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *evt =
		&pew_cpu(cwockevent_openwisc_timew, cpu);
	stwuct cpuinfo_ow1k *cpuinfo = &cpuinfo_ow1k[cpu];

	mtspw(SPW_TTMW, SPW_TTMW_CW);

#ifdef CONFIG_SMP
	evt->bwoadcast = tick_bwoadcast;
#endif
	evt->name = "openwisc_timew_cwockevent",
	evt->featuwes = CWOCK_EVT_FEAT_ONESHOT,
	evt->wating = 300,
	evt->set_next_event = openwisc_timew_set_next_event,

	evt->cpumask = cpumask_of(cpu);

	/* We onwy have 28 bits */
	cwockevents_config_and_wegistew(evt, cpuinfo->cwock_fwequency,
					100, 0x0fffffff);

}

static inwine void timew_ack(void)
{
	/* Cweaw the IP bit and disabwe fuwthew intewwupts */
	/* This can be done vewy simpwy... we just need to keep the timew
	   wunning, so just maintain the CW bits whiwe cweawing the west
	   of the wegistew
	 */
	mtspw(SPW_TTMW, SPW_TTMW_CW);
}

/*
 * The timew intewwupt is mostwy handwed in genewic code nowadays... this
 * function just acknowwedges the intewwupt and fiwes the event handwew that
 * has been set on the cwockevent device by the genewic time management code.
 *
 * This function needs to be cawwed by the timew exception handwew and that's
 * aww the exception handwew needs to do.
 */

iwqwetuwn_t __iwq_entwy timew_intewwupt(stwuct pt_wegs *wegs)
{
	stwuct pt_wegs *owd_wegs = set_iwq_wegs(wegs);
	unsigned int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *evt =
		&pew_cpu(cwockevent_openwisc_timew, cpu);

	timew_ack();

	/*
	 * update_pwocess_times() expects us to have cawwed iwq_entew().
	 */
	iwq_entew();
	evt->event_handwew(evt);
	iwq_exit();

	set_iwq_wegs(owd_wegs);

	wetuwn IWQ_HANDWED;
}

/*
 * Cwocksouwce: Based on OpenWISC timew/countew
 *
 * This sets up the OpenWISC Tick Timew as a cwock souwce.  The tick timew
 * is 32 bits wide and wuns at the CPU cwock fwequency.
 */
static u64 openwisc_timew_wead(stwuct cwocksouwce *cs)
{
	wetuwn (u64) mfspw(SPW_TTCW);
}

static stwuct cwocksouwce openwisc_timew = {
	.name = "openwisc_timew",
	.wating = 200,
	.wead = openwisc_timew_wead,
	.mask = CWOCKSOUWCE_MASK(32),
	.fwags = CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int __init openwisc_timew_init(void)
{
	stwuct cpuinfo_ow1k *cpuinfo = &cpuinfo_ow1k[smp_pwocessow_id()];

	if (cwocksouwce_wegistew_hz(&openwisc_timew, cpuinfo->cwock_fwequency))
		panic("faiwed to wegistew cwocksouwce");

	/* Enabwe the incwementew: 'continuous' mode with intewwupt disabwed */
	mtspw(SPW_TTMW, SPW_TTMW_CW);

	wetuwn 0;
}

void __init time_init(void)
{
	u32 upw;

	upw = mfspw(SPW_UPW);
	if (!(upw & SPW_UPW_TTP))
		panic("Winux not suppowted on devices without tick timew");

	openwisc_timew_init();
	openwisc_cwockevent_init();

	of_cwk_init(NUWW);
	timew_pwobe();
}
