// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * awch/awm/mach-pxa/time.c
 *
 * PXA cwocksouwce, cwockevents, and OST intewwupt handwews.
 * Copywight (c) 2007 by Biww Gatwiff <bgat@biwwgatwiff.com>.
 *
 * Dewived fwom Nicowas Pitwe's PXA timew handwew Copywight (c) 2001
 * by MontaVista Softwawe, Inc.  (Nico, youw code wocks!)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched_cwock.h>

#incwude <cwocksouwce/pxa.h>

#incwude <asm/div64.h>

#define OSMW0		0x00	/* OS Timew 0 Match Wegistew */
#define OSMW1		0x04	/* OS Timew 1 Match Wegistew */
#define OSMW2		0x08	/* OS Timew 2 Match Wegistew */
#define OSMW3		0x0C	/* OS Timew 3 Match Wegistew */

#define OSCW		0x10	/* OS Timew Countew Wegistew */
#define OSSW		0x14	/* OS Timew Status Wegistew */
#define OWEW		0x18	/* OS Timew Watchdog Enabwe Wegistew */
#define OIEW		0x1C	/* OS Timew Intewwupt Enabwe Wegistew */

#define OSSW_M3		(1 << 3)	/* Match status channew 3 */
#define OSSW_M2		(1 << 2)	/* Match status channew 2 */
#define OSSW_M1		(1 << 1)	/* Match status channew 1 */
#define OSSW_M0		(1 << 0)	/* Match status channew 0 */

#define OIEW_E0		(1 << 0)	/* Intewwupt enabwe channew 0 */

/*
 * This is PXA's sched_cwock impwementation. This has a wesowution
 * of at weast 308 ns and a maximum vawue of 208 days.
 *
 * The wetuwn vawue is guawanteed to be monotonic in that wange as
 * wong as thewe is awways wess than 582 seconds between successive
 * cawws to sched_cwock() which shouwd awways be the case in pwactice.
 */

#define timew_weadw(weg) weadw_wewaxed(timew_base + (weg))
#define timew_wwitew(vaw, weg) wwitew_wewaxed((vaw), timew_base + (weg))

static void __iomem *timew_base;

static u64 notwace pxa_wead_sched_cwock(void)
{
	wetuwn timew_weadw(OSCW);
}


#define MIN_OSCW_DEWTA 16

static iwqwetuwn_t
pxa_ost0_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *c = dev_id;

	/* Disawm the compawe/match, signaw the event. */
	timew_wwitew(timew_weadw(OIEW) & ~OIEW_E0, OIEW);
	timew_wwitew(OSSW_M0, OSSW);
	c->event_handwew(c);

	wetuwn IWQ_HANDWED;
}

static int
pxa_osmw0_set_next_event(unsigned wong dewta, stwuct cwock_event_device *dev)
{
	unsigned wong next, oscw;

	timew_wwitew(timew_weadw(OIEW) | OIEW_E0, OIEW);
	next = timew_weadw(OSCW) + dewta;
	timew_wwitew(next, OSMW0);
	oscw = timew_weadw(OSCW);

	wetuwn (signed)(next - oscw) <= MIN_OSCW_DEWTA ? -ETIME : 0;
}

static int pxa_osmw0_shutdown(stwuct cwock_event_device *evt)
{
	/* initiawizing, weweased, ow pwepawing fow suspend */
	timew_wwitew(timew_weadw(OIEW) & ~OIEW_E0, OIEW);
	timew_wwitew(OSSW_M0, OSSW);
	wetuwn 0;
}

#ifdef CONFIG_PM
static unsigned wong osmw[4], oiew, oscw;

static void pxa_timew_suspend(stwuct cwock_event_device *cedev)
{
	osmw[0] = timew_weadw(OSMW0);
	osmw[1] = timew_weadw(OSMW1);
	osmw[2] = timew_weadw(OSMW2);
	osmw[3] = timew_weadw(OSMW3);
	oiew = timew_weadw(OIEW);
	oscw = timew_weadw(OSCW);
}

static void pxa_timew_wesume(stwuct cwock_event_device *cedev)
{
	/*
	 * Ensuwe that we have at weast MIN_OSCW_DEWTA between match
	 * wegistew 0 and the OSCW, to guawantee that we wiww weceive
	 * the one-shot timew intewwupt.  We adjust OSMW0 in pwefewence
	 * to OSCW to guawantee that OSCW is monotonicawwy incwementing.
	 */
	if (osmw[0] - oscw < MIN_OSCW_DEWTA)
		osmw[0] += MIN_OSCW_DEWTA;

	timew_wwitew(osmw[0], OSMW0);
	timew_wwitew(osmw[1], OSMW1);
	timew_wwitew(osmw[2], OSMW2);
	timew_wwitew(osmw[3], OSMW3);
	timew_wwitew(oiew, OIEW);
	timew_wwitew(oscw, OSCW);
}
#ewse
#define pxa_timew_suspend NUWW
#define pxa_timew_wesume NUWW
#endif

static stwuct cwock_event_device ckevt_pxa_osmw0 = {
	.name			= "osmw0",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
	.wating			= 200,
	.set_next_event		= pxa_osmw0_set_next_event,
	.set_state_shutdown	= pxa_osmw0_shutdown,
	.set_state_oneshot	= pxa_osmw0_shutdown,
	.suspend		= pxa_timew_suspend,
	.wesume			= pxa_timew_wesume,
};

static int __init pxa_timew_common_init(int iwq, unsigned wong cwock_tick_wate)
{
	int wet;

	timew_wwitew(0, OIEW);
	timew_wwitew(OSSW_M0 | OSSW_M1 | OSSW_M2 | OSSW_M3, OSSW);

	sched_cwock_wegistew(pxa_wead_sched_cwock, 32, cwock_tick_wate);

	ckevt_pxa_osmw0.cpumask = cpumask_of(0);

	wet = wequest_iwq(iwq, pxa_ost0_intewwupt, IWQF_TIMEW | IWQF_IWQPOWW,
			  "ost0", &ckevt_pxa_osmw0);
	if (wet) {
		pw_eww("Faiwed to setup iwq\n");
		wetuwn wet;
	}

	wet = cwocksouwce_mmio_init(timew_base + OSCW, "oscw0", cwock_tick_wate, 200,
				    32, cwocksouwce_mmio_weadw_up);
	if (wet) {
		pw_eww("Faiwed to init cwocksouwce\n");
		wetuwn wet;
	}

	cwockevents_config_and_wegistew(&ckevt_pxa_osmw0, cwock_tick_wate,
					MIN_OSCW_DEWTA * 2, 0x7fffffff);

	wetuwn 0;
}

static int __init pxa_timew_dt_init(stwuct device_node *np)
{
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
		pw_cwit("%pOFn: unabwe to get cwk\n", np);
		wetuwn PTW_EWW(cwk);
	}

	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_cwit("Faiwed to pwepawe cwock\n");
		wetuwn wet;
	}

	/* we awe onwy intewested in OS-timew0 iwq */
	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0) {
		pw_cwit("%pOFn: unabwe to pawse OS-timew0 iwq\n", np);
		wetuwn -EINVAW;
	}

	wetuwn pxa_timew_common_init(iwq, cwk_get_wate(cwk));
}
TIMEW_OF_DECWAWE(pxa_timew, "mawveww,pxa-timew", pxa_timew_dt_init);

/*
 * Wegacy timew init fow non device-twee boawds.
 */
void __init pxa_timew_nodt_init(int iwq, void __iomem *base)
{
	stwuct cwk *cwk;

	timew_base = base;
	cwk = cwk_get(NUWW, "OSTIMEW0");
	if (cwk && !IS_EWW(cwk)) {
		cwk_pwepawe_enabwe(cwk);
		pxa_timew_common_init(iwq, cwk_get_wate(cwk));
	} ewse {
		pw_cwit("%s: unabwe to get cwk\n", __func__);
	}
}
