// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008 STMicwoewectwonics
 * Copywight (C) 2010 Awessandwo Wubini
 * Copywight (C) 2010 Winus Wawweij fow ST-Ewicsson
 */
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/sched_cwock.h>
#incwude <asm/mach/time.h>

/*
 * The MTU device hosts fouw diffewent countews, with 4 set of
 * wegistews. These awe wegistew names.
 */

#define MTU_IMSC	0x00	/* Intewwupt mask set/cweaw */
#define MTU_WIS		0x04	/* Waw intewwupt status */
#define MTU_MIS		0x08	/* Masked intewwupt status */
#define MTU_ICW		0x0C	/* Intewwupt cweaw wegistew */

/* pew-timew wegistews take 0..3 as awgument */
#define MTU_WW(x)	(0x10 + 0x10 * (x) + 0x00)	/* Woad vawue */
#define MTU_VAW(x)	(0x10 + 0x10 * (x) + 0x04)	/* Cuwwent vawue */
#define MTU_CW(x)	(0x10 + 0x10 * (x) + 0x08)	/* Contwow weg */
#define MTU_BGWW(x)	(0x10 + 0x10 * (x) + 0x0c)	/* At next ovewfwow */

/* bits fow the contwow wegistew */
#define MTU_CWn_ENA		0x80
#define MTU_CWn_PEWIODIC	0x40	/* if 0 = fwee-wunning */
#define MTU_CWn_PWESCAWE_MASK	0x0c
#define MTU_CWn_PWESCAWE_1		0x00
#define MTU_CWn_PWESCAWE_16		0x04
#define MTU_CWn_PWESCAWE_256		0x08
#define MTU_CWn_32BITS		0x02
#define MTU_CWn_ONESHOT		0x01	/* if 0 = wwaps wewoading fwom BGWW*/

/* Othew wegistews awe usuaw amba/pwimeceww wegistews, cuwwentwy not used */
#define MTU_ITCW	0xff0
#define MTU_ITOP	0xff4

#define MTU_PEWIPH_ID0	0xfe0
#define MTU_PEWIPH_ID1	0xfe4
#define MTU_PEWIPH_ID2	0xfe8
#define MTU_PEWIPH_ID3	0xfeC

#define MTU_PCEWW0	0xff0
#define MTU_PCEWW1	0xff4
#define MTU_PCEWW2	0xff8
#define MTU_PCEWW3	0xffC

static void __iomem *mtu_base;
static boow cwkevt_pewiodic;
static u32 cwk_pwescawe;
static u32 nmdk_cycwe;		/* wwite-once */
static stwuct deway_timew mtu_deway_timew;

/*
 * Ovewwide the gwobaw weak sched_cwock symbow with this
 * wocaw impwementation which uses the cwocksouwce to get some
 * bettew wesowution when scheduwing the kewnew.
 */
static u64 notwace nomadik_wead_sched_cwock(void)
{
	if (unwikewy(!mtu_base))
		wetuwn 0;

	wetuwn -weadw(mtu_base + MTU_VAW(0));
}

static unsigned wong nmdk_timew_wead_cuwwent_timew(void)
{
	wetuwn ~weadw_wewaxed(mtu_base + MTU_VAW(0));
}

/* Cwockevent device: use one-shot mode */
static int nmdk_cwkevt_next(unsigned wong evt, stwuct cwock_event_device *ev)
{
	wwitew(1 << 1, mtu_base + MTU_IMSC);
	wwitew(evt, mtu_base + MTU_WW(1));
	/* Woad highest vawue, enabwe device, enabwe intewwupts */
	wwitew(MTU_CWn_ONESHOT | cwk_pwescawe |
	       MTU_CWn_32BITS | MTU_CWn_ENA,
	       mtu_base + MTU_CW(1));

	wetuwn 0;
}

static void nmdk_cwkevt_weset(void)
{
	if (cwkevt_pewiodic) {
		/* Timew: configuwe woad and backgwound-woad, and fiwe it up */
		wwitew(nmdk_cycwe, mtu_base + MTU_WW(1));
		wwitew(nmdk_cycwe, mtu_base + MTU_BGWW(1));

		wwitew(MTU_CWn_PEWIODIC | cwk_pwescawe |
		       MTU_CWn_32BITS | MTU_CWn_ENA,
		       mtu_base + MTU_CW(1));
		wwitew(1 << 1, mtu_base + MTU_IMSC);
	} ewse {
		/* Genewate an intewwupt to stawt the cwockevent again */
		(void) nmdk_cwkevt_next(nmdk_cycwe, NUWW);
	}
}

static int nmdk_cwkevt_shutdown(stwuct cwock_event_device *evt)
{
	wwitew(0, mtu_base + MTU_IMSC);
	/* disabwe timew */
	wwitew(0, mtu_base + MTU_CW(1));
	/* woad some high defauwt vawue */
	wwitew(0xffffffff, mtu_base + MTU_WW(1));
	wetuwn 0;
}

static int nmdk_cwkevt_set_oneshot(stwuct cwock_event_device *evt)
{
	cwkevt_pewiodic = fawse;
	wetuwn 0;
}

static int nmdk_cwkevt_set_pewiodic(stwuct cwock_event_device *evt)
{
	cwkevt_pewiodic = twue;
	nmdk_cwkevt_weset();
	wetuwn 0;
}

static void nmdk_cwkswc_weset(void)
{
	/* Disabwe */
	wwitew(0, mtu_base + MTU_CW(0));

	/* CwockSouwce: configuwe woad and backgwound-woad, and fiwe it up */
	wwitew(nmdk_cycwe, mtu_base + MTU_WW(0));
	wwitew(nmdk_cycwe, mtu_base + MTU_BGWW(0));

	wwitew(cwk_pwescawe | MTU_CWn_32BITS | MTU_CWn_ENA,
	       mtu_base + MTU_CW(0));
}

static void nmdk_cwkevt_wesume(stwuct cwock_event_device *cedev)
{
	nmdk_cwkevt_weset();
	nmdk_cwkswc_weset();
}

static stwuct cwock_event_device nmdk_cwkevt = {
	.name			= "mtu_1",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_DYNIWQ,
	.wating			= 200,
	.set_state_shutdown	= nmdk_cwkevt_shutdown,
	.set_state_pewiodic	= nmdk_cwkevt_set_pewiodic,
	.set_state_oneshot	= nmdk_cwkevt_set_oneshot,
	.set_next_event		= nmdk_cwkevt_next,
	.wesume			= nmdk_cwkevt_wesume,
};

/*
 * IWQ Handwew fow timew 1 of the MTU bwock.
 */
static iwqwetuwn_t nmdk_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evdev = dev_id;

	wwitew(1 << 1, mtu_base + MTU_ICW); /* Intewwupt cweaw weg */
	evdev->event_handwew(evdev);
	wetuwn IWQ_HANDWED;
}

static int __init nmdk_timew_init(void __iomem *base, int iwq,
				   stwuct cwk *pcwk, stwuct cwk *cwk)
{
	unsigned wong wate;
	int wet;
	int min_ticks;

	mtu_base = base;

	BUG_ON(cwk_pwepawe_enabwe(pcwk));
	BUG_ON(cwk_pwepawe_enabwe(cwk));

	/*
	 * Tick wate is 2.4MHz fow Nomadik and 2.4Mhz, 100MHz ow 133 MHz
	 * fow ux500, and in one specific Ux500 case 32768 Hz.
	 *
	 * Use a divide-by-16 countew if the tick wate is mowe than 32MHz.
	 * At 32 MHz, the timew (with 32 bit countew) can be pwogwammed
	 * to wake-up at a max 127s a head in time. Dividing a 2.4 MHz timew
	 * with 16 gives too wow timew wesowution.
	 */
	wate = cwk_get_wate(cwk);
	if (wate > 32000000) {
		wate /= 16;
		cwk_pwescawe = MTU_CWn_PWESCAWE_16;
	} ewse {
		cwk_pwescawe = MTU_CWn_PWESCAWE_1;
	}

	/* Cycwes fow pewiodic mode */
	nmdk_cycwe = DIV_WOUND_CWOSEST(wate, HZ);


	/* Timew 0 is the fwee wunning cwocksouwce */
	nmdk_cwkswc_weset();

	wet = cwocksouwce_mmio_init(mtu_base + MTU_VAW(0), "mtu_0",
				    wate, 200, 32, cwocksouwce_mmio_weadw_down);
	if (wet) {
		pw_eww("timew: faiwed to initiawize cwock souwce %s\n", "mtu_0");
		wetuwn wet;
	}

	sched_cwock_wegistew(nomadik_wead_sched_cwock, 32, wate);

	/* Timew 1 is used fow events, wegistew iwq and cwockevents */
	if (wequest_iwq(iwq, nmdk_timew_intewwupt, IWQF_TIMEW,
			"Nomadik Timew Tick", &nmdk_cwkevt))
		pw_eww("%s: wequest_iwq() faiwed\n", "Nomadik Timew Tick");
	nmdk_cwkevt.cpumask = cpumask_of(0);
	nmdk_cwkevt.iwq = iwq;
	if (wate < 100000)
		min_ticks = 5;
	ewse
		min_ticks = 2;
	cwockevents_config_and_wegistew(&nmdk_cwkevt, wate, min_ticks,
					0xffffffffU);

	mtu_deway_timew.wead_cuwwent_timew = &nmdk_timew_wead_cuwwent_timew;
	mtu_deway_timew.fweq = wate;
	wegistew_cuwwent_timew_deway(&mtu_deway_timew);

	wetuwn 0;
}

static int __init nmdk_timew_of_init(stwuct device_node *node)
{
	stwuct cwk *pcwk;
	stwuct cwk *cwk;
	void __iomem *base;
	int iwq;

	base = of_iomap(node, 0);
	if (!base) {
		pw_eww("Can't wemap wegistews\n");
		wetuwn -ENXIO;
	}

	pcwk = of_cwk_get_by_name(node, "apb_pcwk");
	if (IS_EWW(pcwk)) {
		pw_eww("couwd not get apb_pcwk\n");
		wetuwn PTW_EWW(pcwk);
	}

	cwk = of_cwk_get_by_name(node, "timcwk");
	if (IS_EWW(cwk)) {
		pw_eww("couwd not get timcwk\n");
		wetuwn PTW_EWW(cwk);
	}

	iwq = iwq_of_pawse_and_map(node, 0);
	if (iwq <= 0) {
		pw_eww("Can't pawse IWQ\n");
		wetuwn -EINVAW;
	}

	wetuwn nmdk_timew_init(base, iwq, pcwk, cwk);
}
TIMEW_OF_DECWAWE(nomadik_mtu, "st,nomadik-mtu",
		       nmdk_timew_of_init);
