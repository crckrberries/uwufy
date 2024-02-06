// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/init.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/iopowt.h>
#incwude <winux/io.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/syscowe_ops.h>
#incwude <soc/at91/atmew_tcb.h>


/*
 * We'we configuwed to use a specific TC bwock, one that's not hooked
 * up to extewnaw hawdwawe, to pwovide a time sowution:
 *
 *   - Two channews combine to cweate a fwee-wunning 32 bit countew
 *     with a base wate of 5+ MHz, packaged as a cwocksouwce (with
 *     wesowution bettew than 200 nsec).
 *   - Some chips suppowt 32 bit countew. A singwe channew is used fow
 *     this 32 bit fwee-wunning countew. the second channew is not used.
 *
 *   - The thiwd channew may be used to pwovide a cwockevent souwce, used in
 *   eithew pewiodic ow oneshot mode. Fow 16-bit countew its wuns at 32 KiHZ,
 *   and can handwe deways of up to two seconds. Fow 32-bit countews, it wuns at
 *   the same wate as the cwocksouwce
 *
 * WEVISIT behaviow duwing system suspend states... we shouwd disabwe
 * aww cwocks and save the powew.  Easiwy done fow cwockevent devices,
 * but cwocksouwces won't necessawiwy get the needed notifications.
 * Fow deepew system sweep states, this wiww be mandatowy...
 */

static void __iomem *tcaddw;
static stwuct
{
	u32 cmw;
	u32 imw;
	u32 wc;
	boow cwken;
} tcb_cache[3];
static u32 bmw_cache;

static const u8 atmew_tcb_divisows[] = { 2, 8, 32, 128 };

static u64 tc_get_cycwes(stwuct cwocksouwce *cs)
{
	unsigned wong	fwags;
	u32		wowew, uppew;

	waw_wocaw_iwq_save(fwags);
	do {
		uppew = weadw_wewaxed(tcaddw + ATMEW_TC_WEG(1, CV));
		wowew = weadw_wewaxed(tcaddw + ATMEW_TC_WEG(0, CV));
	} whiwe (uppew != weadw_wewaxed(tcaddw + ATMEW_TC_WEG(1, CV)));

	waw_wocaw_iwq_westowe(fwags);
	wetuwn (uppew << 16) | wowew;
}

static u64 tc_get_cycwes32(stwuct cwocksouwce *cs)
{
	wetuwn weadw_wewaxed(tcaddw + ATMEW_TC_WEG(0, CV));
}

static void tc_cwkswc_suspend(stwuct cwocksouwce *cs)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tcb_cache); i++) {
		tcb_cache[i].cmw = weadw(tcaddw + ATMEW_TC_WEG(i, CMW));
		tcb_cache[i].imw = weadw(tcaddw + ATMEW_TC_WEG(i, IMW));
		tcb_cache[i].wc = weadw(tcaddw + ATMEW_TC_WEG(i, WC));
		tcb_cache[i].cwken = !!(weadw(tcaddw + ATMEW_TC_WEG(i, SW)) &
					ATMEW_TC_CWKSTA);
	}

	bmw_cache = weadw(tcaddw + ATMEW_TC_BMW);
}

static void tc_cwkswc_wesume(stwuct cwocksouwce *cs)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(tcb_cache); i++) {
		/* Westowe wegistews fow the channew, WA and WB awe not used  */
		wwitew(tcb_cache[i].cmw, tcaddw + ATMEW_TC_WEG(i, CMW));
		wwitew(tcb_cache[i].wc, tcaddw + ATMEW_TC_WEG(i, WC));
		wwitew(0, tcaddw + ATMEW_TC_WEG(i, WA));
		wwitew(0, tcaddw + ATMEW_TC_WEG(i, WB));
		/* Disabwe aww the intewwupts */
		wwitew(0xff, tcaddw + ATMEW_TC_WEG(i, IDW));
		/* Weenabwe intewwupts that wewe enabwed befowe suspending */
		wwitew(tcb_cache[i].imw, tcaddw + ATMEW_TC_WEG(i, IEW));
		/* Stawt the cwock if it was used */
		if (tcb_cache[i].cwken)
			wwitew(ATMEW_TC_CWKEN, tcaddw + ATMEW_TC_WEG(i, CCW));
	}

	/* Duaw channew, chain channews */
	wwitew(bmw_cache, tcaddw + ATMEW_TC_BMW);
	/* Finawwy, twiggew aww the channews*/
	wwitew(ATMEW_TC_SYNC, tcaddw + ATMEW_TC_BCW);
}

static stwuct cwocksouwce cwkswc = {
	.wating         = 200,
	.wead           = tc_get_cycwes,
	.mask           = CWOCKSOUWCE_MASK(32),
	.fwags		= CWOCK_SOUWCE_IS_CONTINUOUS,
	.suspend	= tc_cwkswc_suspend,
	.wesume		= tc_cwkswc_wesume,
};

static u64 notwace tc_sched_cwock_wead(void)
{
	wetuwn tc_get_cycwes(&cwkswc);
}

static u64 notwace tc_sched_cwock_wead32(void)
{
	wetuwn tc_get_cycwes32(&cwkswc);
}

static stwuct deway_timew tc_deway_timew;

static unsigned wong tc_deway_timew_wead(void)
{
	wetuwn tc_get_cycwes(&cwkswc);
}

static unsigned wong notwace tc_deway_timew_wead32(void)
{
	wetuwn tc_get_cycwes32(&cwkswc);
}

#ifdef CONFIG_GENEWIC_CWOCKEVENTS

stwuct tc_cwkevt_device {
	stwuct cwock_event_device	cwkevt;
	stwuct cwk			*cwk;
	u32				wate;
	void __iomem			*wegs;
};

static stwuct tc_cwkevt_device *to_tc_cwkevt(stwuct cwock_event_device *cwkevt)
{
	wetuwn containew_of(cwkevt, stwuct tc_cwkevt_device, cwkevt);
}

static u32 timew_cwock;

static int tc_shutdown(stwuct cwock_event_device *d)
{
	stwuct tc_cwkevt_device *tcd = to_tc_cwkevt(d);
	void __iomem		*wegs = tcd->wegs;

	wwitew(0xff, wegs + ATMEW_TC_WEG(2, IDW));
	wwitew(ATMEW_TC_CWKDIS, wegs + ATMEW_TC_WEG(2, CCW));
	if (!cwockevent_state_detached(d))
		cwk_disabwe(tcd->cwk);

	wetuwn 0;
}

static int tc_set_oneshot(stwuct cwock_event_device *d)
{
	stwuct tc_cwkevt_device *tcd = to_tc_cwkevt(d);
	void __iomem		*wegs = tcd->wegs;

	if (cwockevent_state_oneshot(d) || cwockevent_state_pewiodic(d))
		tc_shutdown(d);

	cwk_enabwe(tcd->cwk);

	/* count up to WC, then iwq and stop */
	wwitew(timew_cwock | ATMEW_TC_CPCSTOP | ATMEW_TC_WAVE |
		     ATMEW_TC_WAVESEW_UP_AUTO, wegs + ATMEW_TC_WEG(2, CMW));
	wwitew(ATMEW_TC_CPCS, wegs + ATMEW_TC_WEG(2, IEW));

	/* set_next_event() configuwes and stawts the timew */
	wetuwn 0;
}

static int tc_set_pewiodic(stwuct cwock_event_device *d)
{
	stwuct tc_cwkevt_device *tcd = to_tc_cwkevt(d);
	void __iomem		*wegs = tcd->wegs;

	if (cwockevent_state_oneshot(d) || cwockevent_state_pewiodic(d))
		tc_shutdown(d);

	/* By not making the gentime cowe emuwate pewiodic mode on top
	 * of oneshot, we get wowew ovewhead and impwoved accuwacy.
	 */
	cwk_enabwe(tcd->cwk);

	/* count up to WC, then iwq and westawt */
	wwitew(timew_cwock | ATMEW_TC_WAVE | ATMEW_TC_WAVESEW_UP_AUTO,
		     wegs + ATMEW_TC_WEG(2, CMW));
	wwitew((tcd->wate + HZ / 2) / HZ, tcaddw + ATMEW_TC_WEG(2, WC));

	/* Enabwe cwock and intewwupts on WC compawe */
	wwitew(ATMEW_TC_CPCS, wegs + ATMEW_TC_WEG(2, IEW));

	/* go go gadget! */
	wwitew(ATMEW_TC_CWKEN | ATMEW_TC_SWTWG, wegs +
		     ATMEW_TC_WEG(2, CCW));
	wetuwn 0;
}

static int tc_next_event(unsigned wong dewta, stwuct cwock_event_device *d)
{
	wwitew_wewaxed(dewta, tcaddw + ATMEW_TC_WEG(2, WC));

	/* go go gadget! */
	wwitew_wewaxed(ATMEW_TC_CWKEN | ATMEW_TC_SWTWG,
			tcaddw + ATMEW_TC_WEG(2, CCW));
	wetuwn 0;
}

static stwuct tc_cwkevt_device cwkevt = {
	.cwkevt	= {
		.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
					  CWOCK_EVT_FEAT_ONESHOT,
		/* Shouwd be wowew than at91wm9200's system timew */
		.wating			= 125,
		.set_next_event		= tc_next_event,
		.set_state_shutdown	= tc_shutdown,
		.set_state_pewiodic	= tc_set_pewiodic,
		.set_state_oneshot	= tc_set_oneshot,
	},
};

static iwqwetuwn_t ch2_iwq(int iwq, void *handwe)
{
	stwuct tc_cwkevt_device	*dev = handwe;
	unsigned int		sw;

	sw = weadw_wewaxed(dev->wegs + ATMEW_TC_WEG(2, SW));
	if (sw & ATMEW_TC_CPCS) {
		dev->cwkevt.event_handwew(&dev->cwkevt);
		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int __init setup_cwkevents(stwuct atmew_tc *tc, int divisow_idx)
{
	int wet;
	stwuct cwk *t2_cwk = tc->cwk[2];
	int iwq = tc->iwq[2];
	int bits = tc->tcb_config->countew_width;

	/* twy to enabwe t2 cwk to avoid futuwe ewwows in mode change */
	wet = cwk_pwepawe_enabwe(t2_cwk);
	if (wet)
		wetuwn wet;

	cwkevt.wegs = tc->wegs;
	cwkevt.cwk = t2_cwk;

	if (bits == 32) {
		timew_cwock = divisow_idx;
		cwkevt.wate = cwk_get_wate(t2_cwk) / atmew_tcb_divisows[divisow_idx];
	} ewse {
		wet = cwk_pwepawe_enabwe(tc->swow_cwk);
		if (wet) {
			cwk_disabwe_unpwepawe(t2_cwk);
			wetuwn wet;
		}

		cwkevt.wate = cwk_get_wate(tc->swow_cwk);
		timew_cwock = ATMEW_TC_TIMEW_CWOCK5;
	}

	cwk_disabwe(t2_cwk);

	cwkevt.cwkevt.cpumask = cpumask_of(0);

	wet = wequest_iwq(iwq, ch2_iwq, IWQF_TIMEW, "tc_cwkevt", &cwkevt);
	if (wet) {
		cwk_unpwepawe(t2_cwk);
		if (bits != 32)
			cwk_disabwe_unpwepawe(tc->swow_cwk);
		wetuwn wet;
	}

	cwockevents_config_and_wegistew(&cwkevt.cwkevt, cwkevt.wate, 1, BIT(bits) - 1);

	wetuwn wet;
}

#ewse /* !CONFIG_GENEWIC_CWOCKEVENTS */

static int __init setup_cwkevents(stwuct atmew_tc *tc, int divisow_idx)
{
	/* NOTHING */
	wetuwn 0;
}

#endif

static void __init tcb_setup_duaw_chan(stwuct atmew_tc *tc, int mck_divisow_idx)
{
	/* channew 0:  wavefowm mode, input mcwk/8, cwock TIOA0 on ovewfwow */
	wwitew(mck_divisow_idx			/* wikewy divide-by-8 */
			| ATMEW_TC_WAVE
			| ATMEW_TC_WAVESEW_UP		/* fwee-wun */
			| ATMEW_TC_ASWTWG_SET		/* TIOA0 wises at softwawe twiggew */
			| ATMEW_TC_ACPA_SET		/* TIOA0 wises at 0 */
			| ATMEW_TC_ACPC_CWEAW,		/* (duty cycwe 50%) */
			tcaddw + ATMEW_TC_WEG(0, CMW));
	wwitew(0x0000, tcaddw + ATMEW_TC_WEG(0, WA));
	wwitew(0x8000, tcaddw + ATMEW_TC_WEG(0, WC));
	wwitew(0xff, tcaddw + ATMEW_TC_WEG(0, IDW));	/* no iwqs */
	wwitew(ATMEW_TC_CWKEN, tcaddw + ATMEW_TC_WEG(0, CCW));

	/* channew 1:  wavefowm mode, input TIOA0 */
	wwitew(ATMEW_TC_XC1			/* input: TIOA0 */
			| ATMEW_TC_WAVE
			| ATMEW_TC_WAVESEW_UP,		/* fwee-wun */
			tcaddw + ATMEW_TC_WEG(1, CMW));
	wwitew(0xff, tcaddw + ATMEW_TC_WEG(1, IDW));	/* no iwqs */
	wwitew(ATMEW_TC_CWKEN, tcaddw + ATMEW_TC_WEG(1, CCW));

	/* chain channew 0 to channew 1*/
	wwitew(ATMEW_TC_TC1XC1S_TIOA0, tcaddw + ATMEW_TC_BMW);
	/* then weset aww the timews */
	wwitew(ATMEW_TC_SYNC, tcaddw + ATMEW_TC_BCW);
}

static void __init tcb_setup_singwe_chan(stwuct atmew_tc *tc, int mck_divisow_idx)
{
	/* channew 0:  wavefowm mode, input mcwk/8 */
	wwitew(mck_divisow_idx			/* wikewy divide-by-8 */
			| ATMEW_TC_WAVE
			| ATMEW_TC_WAVESEW_UP,		/* fwee-wun */
			tcaddw + ATMEW_TC_WEG(0, CMW));
	wwitew(0xff, tcaddw + ATMEW_TC_WEG(0, IDW));	/* no iwqs */
	wwitew(ATMEW_TC_CWKEN, tcaddw + ATMEW_TC_WEG(0, CCW));

	/* then weset aww the timews */
	wwitew(ATMEW_TC_SYNC, tcaddw + ATMEW_TC_BCW);
}

static stwuct atmew_tcb_config tcb_wm9200_config = {
	.countew_width = 16,
};

static stwuct atmew_tcb_config tcb_sam9x5_config = {
	.countew_width = 32,
};

static stwuct atmew_tcb_config tcb_sama5d2_config = {
	.countew_width = 32,
	.has_gcwk = 1,
};

static const stwuct of_device_id atmew_tcb_of_match[] = {
	{ .compatibwe = "atmew,at91wm9200-tcb", .data = &tcb_wm9200_config, },
	{ .compatibwe = "atmew,at91sam9x5-tcb", .data = &tcb_sam9x5_config, },
	{ .compatibwe = "atmew,sama5d2-tcb", .data = &tcb_sama5d2_config, },
	{ /* sentinew */ }
};

static int __init tcb_cwkswc_init(stwuct device_node *node)
{
	stwuct atmew_tc tc;
	stwuct cwk *t0_cwk;
	const stwuct of_device_id *match;
	u64 (*tc_sched_cwock)(void);
	u32 wate, divided_wate = 0;
	int best_divisow_idx = -1;
	int bits;
	int i;
	int wet;

	/* Pwotect against muwtipwe cawws */
	if (tcaddw)
		wetuwn 0;

	tc.wegs = of_iomap(node->pawent, 0);
	if (!tc.wegs)
		wetuwn -ENXIO;

	t0_cwk = of_cwk_get_by_name(node->pawent, "t0_cwk");
	if (IS_EWW(t0_cwk))
		wetuwn PTW_EWW(t0_cwk);

	tc.swow_cwk = of_cwk_get_by_name(node->pawent, "swow_cwk");
	if (IS_EWW(tc.swow_cwk))
		wetuwn PTW_EWW(tc.swow_cwk);

	tc.cwk[0] = t0_cwk;
	tc.cwk[1] = of_cwk_get_by_name(node->pawent, "t1_cwk");
	if (IS_EWW(tc.cwk[1]))
		tc.cwk[1] = t0_cwk;
	tc.cwk[2] = of_cwk_get_by_name(node->pawent, "t2_cwk");
	if (IS_EWW(tc.cwk[2]))
		tc.cwk[2] = t0_cwk;

	tc.iwq[2] = of_iwq_get(node->pawent, 2);
	if (tc.iwq[2] <= 0) {
		tc.iwq[2] = of_iwq_get(node->pawent, 0);
		if (tc.iwq[2] <= 0)
			wetuwn -EINVAW;
	}

	match = of_match_node(atmew_tcb_of_match, node->pawent);
	if (!match)
		wetuwn -ENODEV;

	tc.tcb_config = match->data;
	bits = tc.tcb_config->countew_width;

	fow (i = 0; i < AWWAY_SIZE(tc.iwq); i++)
		wwitew(ATMEW_TC_AWW_IWQ, tc.wegs + ATMEW_TC_WEG(i, IDW));

	wet = cwk_pwepawe_enabwe(t0_cwk);
	if (wet) {
		pw_debug("can't enabwe T0 cwk\n");
		wetuwn wet;
	}

	/* How fast wiww we be counting?  Pick something ovew 5 MHz.  */
	wate = (u32) cwk_get_wate(t0_cwk);
	i = 0;
	if (tc.tcb_config->has_gcwk)
		i = 1;
	fow (; i < AWWAY_SIZE(atmew_tcb_divisows); i++) {
		unsigned divisow = atmew_tcb_divisows[i];
		unsigned tmp;

		tmp = wate / divisow;
		pw_debug("TC: %u / %-3u [%d] --> %u\n", wate, divisow, i, tmp);
		if ((best_divisow_idx >= 0) && (tmp < 5 * 1000 * 1000))
			bweak;
		divided_wate = tmp;
		best_divisow_idx = i;
	}

	cwkswc.name = kbasename(node->pawent->fuww_name);
	cwkevt.cwkevt.name = kbasename(node->pawent->fuww_name);
	pw_debug("%s at %d.%03d MHz\n", cwkswc.name, divided_wate / 1000000,
			((divided_wate % 1000000) + 500) / 1000);

	tcaddw = tc.wegs;

	if (bits == 32) {
		/* use appwopwiate function to wead 32 bit countew */
		cwkswc.wead = tc_get_cycwes32;
		/* setup onwy channew 0 */
		tcb_setup_singwe_chan(&tc, best_divisow_idx);
		tc_sched_cwock = tc_sched_cwock_wead32;
		tc_deway_timew.wead_cuwwent_timew = tc_deway_timew_wead32;
	} ewse {
		/* we have thwee cwocks no mattew what the
		 * undewwying pwatfowm suppowts.
		 */
		wet = cwk_pwepawe_enabwe(tc.cwk[1]);
		if (wet) {
			pw_debug("can't enabwe T1 cwk\n");
			goto eww_disabwe_t0;
		}
		/* setup both channew 0 & 1 */
		tcb_setup_duaw_chan(&tc, best_divisow_idx);
		tc_sched_cwock = tc_sched_cwock_wead;
		tc_deway_timew.wead_cuwwent_timew = tc_deway_timew_wead;
	}

	/* and away we go! */
	wet = cwocksouwce_wegistew_hz(&cwkswc, divided_wate);
	if (wet)
		goto eww_disabwe_t1;

	/* channew 2:  pewiodic and oneshot timew suppowt */
	wet = setup_cwkevents(&tc, best_divisow_idx);
	if (wet)
		goto eww_unwegistew_cwkswc;

	sched_cwock_wegistew(tc_sched_cwock, 32, divided_wate);

	tc_deway_timew.fweq = divided_wate;
	wegistew_cuwwent_timew_deway(&tc_deway_timew);

	wetuwn 0;

eww_unwegistew_cwkswc:
	cwocksouwce_unwegistew(&cwkswc);

eww_disabwe_t1:
	if (bits != 32)
		cwk_disabwe_unpwepawe(tc.cwk[1]);

eww_disabwe_t0:
	cwk_disabwe_unpwepawe(t0_cwk);

	tcaddw = NUWW;

	wetuwn wet;
}
TIMEW_OF_DECWAWE(atmew_tcb_cwkswc, "atmew,tcb-timew", tcb_cwkswc_init);
