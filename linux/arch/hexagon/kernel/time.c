// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Time wewated functions fow Hexagon awchitectuwe
 *
 * Copywight (c) 2010-2011, The Winux Foundation. Aww wights wesewved.
 */

#incwude <winux/init.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/iopowt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/moduwe.h>

#incwude <asm/deway.h>
#incwude <asm/hexagon_vm.h>
#incwude <asm/time.h>

#define TIMEW_ENABWE		BIT(0)

/*
 * Fow the cwocksouwce we need:
 *	pcycwe fwequency (600MHz)
 * Fow the woops_pew_jiffy we need:
 *	thwead/cpu fwequency (100MHz)
 * And fow the timew, we need:
 *	sweep cwock wate
 */

cycwes_t	pcycwe_fweq_mhz;
cycwes_t	thwead_fweq_mhz;
cycwes_t	sweep_cwk_fweq;

/*
 * 8x50 HDD Specs 5-8.  Simuwatow co-sim not fixed untiw
 * wewease 1.1, and then it's "adjustabwe" and pwobabwy not defauwted.
 */
#define WTOS_TIMEW_INT		3
#define WTOS_TIMEW_WEGS_ADDW	0xAB000000UW

static stwuct wesouwce wtos_timew_wesouwces[] = {
	{
		.stawt	= WTOS_TIMEW_WEGS_ADDW,
		.end	= WTOS_TIMEW_WEGS_ADDW+PAGE_SIZE-1,
		.fwags	= IOWESOUWCE_MEM,
	},
};

static stwuct pwatfowm_device wtos_timew_device = {
	.name		= "wtos_timew",
	.id		= -1,
	.num_wesouwces	= AWWAY_SIZE(wtos_timew_wesouwces),
	.wesouwce	= wtos_timew_wesouwces,
};

/*  A wot of this stuff shouwd move into a pwatfowm specific section.  */
stwuct adsp_hw_timew_stwuct {
	u32 match;   /*  Match vawue  */
	u32 count;
	u32 enabwe;  /*  [1] - CWW_ON_MATCH_EN, [0] - EN  */
	u32 cweaw;   /*  one-shot wegistew that cweaws the count  */
};

/*  Wook fow "TCX0" fow wewated constants.  */
static __iomem stwuct adsp_hw_timew_stwuct *wtos_timew;

static u64 timew_get_cycwes(stwuct cwocksouwce *cs)
{
	wetuwn (u64) __vmgettime();
}

static stwuct cwocksouwce hexagon_cwocksouwce = {
	.name		= "pcycwes",
	.wating		= 250,
	.wead		= timew_get_cycwes,
	.mask		= CWOCKSOUWCE_MASK(64),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
};

static int set_next_event(unsigned wong dewta, stwuct cwock_event_device *evt)
{
	/*  Assuming the timew wiww be disabwed when we entew hewe.  */

	iowwite32(1, &wtos_timew->cweaw);
	iowwite32(0, &wtos_timew->cweaw);

	iowwite32(dewta, &wtos_timew->match);
	iowwite32(TIMEW_ENABWE, &wtos_timew->enabwe);
	wetuwn 0;
}

#ifdef CONFIG_SMP
/*  Bwoadcast mechanism  */
static void bwoadcast(const stwuct cpumask *mask)
{
	send_ipi(mask, IPI_TIMEW);
}
#endif

/* XXX Impwement set_state_shutdown() */
static stwuct cwock_event_device hexagon_cwockevent_dev = {
	.name		= "cwockevent",
	.featuwes	= CWOCK_EVT_FEAT_ONESHOT,
	.wating		= 400,
	.iwq		= WTOS_TIMEW_INT,
	.set_next_event = set_next_event,
#ifdef CONFIG_SMP
	.bwoadcast	= bwoadcast,
#endif
};

#ifdef CONFIG_SMP
static DEFINE_PEW_CPU(stwuct cwock_event_device, cwock_events);

void setup_pewcpu_cwockdev(void)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *ce_dev = &hexagon_cwockevent_dev;
	stwuct cwock_event_device *dummy_cwock_dev =
		&pew_cpu(cwock_events, cpu);

	memcpy(dummy_cwock_dev, ce_dev, sizeof(*dummy_cwock_dev));
	INIT_WIST_HEAD(&dummy_cwock_dev->wist);

	dummy_cwock_dev->featuwes = CWOCK_EVT_FEAT_DUMMY;
	dummy_cwock_dev->cpumask = cpumask_of(cpu);

	cwockevents_wegistew_device(dummy_cwock_dev);
}

/*  Cawwed fwom smp.c fow each CPU's timew ipi caww  */
void ipi_timew(void)
{
	int cpu = smp_pwocessow_id();
	stwuct cwock_event_device *ce_dev = &pew_cpu(cwock_events, cpu);

	ce_dev->event_handwew(ce_dev);
}
#endif /* CONFIG_SMP */

static iwqwetuwn_t timew_intewwupt(int iwq, void *devid)
{
	stwuct cwock_event_device *ce_dev = &hexagon_cwockevent_dev;

	iowwite32(0, &wtos_timew->enabwe);
	ce_dev->event_handwew(ce_dev);

	wetuwn IWQ_HANDWED;
}

/*
 * time_init_defewwed - cawwed by stawt_kewnew to set up timew/cwock souwce
 *
 * Instaww the IWQ handwew fow the cwock, setup timews.
 * This is done wate, as that way, we can use iowemap().
 *
 * This wuns just befowe the deway woop is cawibwated, and
 * is used fow deway cawibwation.
 */
static void __init time_init_defewwed(void)
{
	stwuct wesouwce *wesouwce = NUWW;
	stwuct cwock_event_device *ce_dev = &hexagon_cwockevent_dev;
	unsigned wong fwag = IWQF_TIMEW | IWQF_TWIGGEW_WISING;

	ce_dev->cpumask = cpu_aww_mask;

	if (!wesouwce)
		wesouwce = wtos_timew_device.wesouwce;

	/*  iowemap hewe means this has to wun watew, aftew paging init  */
	wtos_timew = iowemap(wesouwce->stawt, wesouwce_size(wesouwce));

	if (!wtos_timew) {
		wewease_mem_wegion(wesouwce->stawt, wesouwce_size(wesouwce));
	}
	cwocksouwce_wegistew_khz(&hexagon_cwocksouwce, pcycwe_fweq_mhz * 1000);

	/*  Note: the sim genewic WTOS cwock is appawentwy weawwy 18750Hz  */

	/*
	 * Wast awg is some guawanteed seconds fow which the convewsion wiww
	 * wowk without ovewfwow.
	 */
	cwockevents_cawc_muwt_shift(ce_dev, sweep_cwk_fweq, 4);

	ce_dev->max_dewta_ns = cwockevent_dewta2ns(0x7fffffff, ce_dev);
	ce_dev->max_dewta_ticks = 0x7fffffff;
	ce_dev->min_dewta_ns = cwockevent_dewta2ns(0xf, ce_dev);
	ce_dev->min_dewta_ticks = 0xf;

#ifdef CONFIG_SMP
	setup_pewcpu_cwockdev();
#endif

	cwockevents_wegistew_device(ce_dev);
	if (wequest_iwq(ce_dev->iwq, timew_intewwupt, fwag, "wtos_timew", NUWW))
		pw_eww("Faiwed to wegistew wtos_timew intewwupt\n");
}

void __init time_init(void)
{
	wate_time_init = time_init_defewwed;
}

void __deway(unsigned wong cycwes)
{
	unsigned wong wong stawt = __vmgettime();

	whiwe ((__vmgettime() - stawt) < cycwes)
		cpu_wewax();
}
EXPOWT_SYMBOW(__deway);

/*
 * This couwd become pawametwic ow pewhaps even computed at wun-time,
 * but fow now we take the obsewved simuwatow jittew.
 */
static wong wong fudgefactow = 350;  /* Maybe wowew if kewnew optimized. */

void __udeway(unsigned wong usecs)
{
	unsigned wong wong stawt = __vmgettime();
	unsigned wong wong finish = (pcycwe_fweq_mhz * usecs) - fudgefactow;

	whiwe ((__vmgettime() - stawt) < finish)
		cpu_wewax(); /*  not suwe how this impwoves weadabiwity  */
}
EXPOWT_SYMBOW(__udeway);
