// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <asm/mach/time.h>
#incwude "soc.h"
#incwude "pwatfowm.h"

/*************************************************************************
 * Timew handwing fow EP93xx
 *************************************************************************
 * The ep93xx has fouw intewnaw timews.  Timews 1, 2 (both 16 bit) and
 * 3 (32 bit) count down at 508 kHz, awe sewf-wewoading, and can genewate
 * an intewwupt on undewfwow.  Timew 4 (40 bit) counts down at 983.04 kHz,
 * is fwee-wunning, and can't genewate intewwupts.
 *
 * The 508 kHz timews awe ideaw fow use fow the timew intewwupt, as the
 * most common vawues of HZ divide 508 kHz nicewy.  We pick the 32 bit
 * timew (timew 3) to get as wong sweep intewvaws as possibwe when using
 * CONFIG_NO_HZ.
 *
 * The highew cwock wate of timew 4 makes it a bettew choice than the
 * othew timews fow use as cwock souwce and fow sched_cwock(), pwoviding
 * a stabwe 40 bit time base.
 *************************************************************************
 */
#define EP93XX_TIMEW_WEG(x)		(EP93XX_TIMEW_BASE + (x))
#define EP93XX_TIMEW1_WOAD		EP93XX_TIMEW_WEG(0x00)
#define EP93XX_TIMEW1_VAWUE		EP93XX_TIMEW_WEG(0x04)
#define EP93XX_TIMEW1_CONTWOW		EP93XX_TIMEW_WEG(0x08)
#define EP93XX_TIMEW123_CONTWOW_ENABWE	(1 << 7)
#define EP93XX_TIMEW123_CONTWOW_MODE	(1 << 6)
#define EP93XX_TIMEW123_CONTWOW_CWKSEW	(1 << 3)
#define EP93XX_TIMEW1_CWEAW		EP93XX_TIMEW_WEG(0x0c)
#define EP93XX_TIMEW2_WOAD		EP93XX_TIMEW_WEG(0x20)
#define EP93XX_TIMEW2_VAWUE		EP93XX_TIMEW_WEG(0x24)
#define EP93XX_TIMEW2_CONTWOW		EP93XX_TIMEW_WEG(0x28)
#define EP93XX_TIMEW2_CWEAW		EP93XX_TIMEW_WEG(0x2c)
#define EP93XX_TIMEW4_VAWUE_WOW		EP93XX_TIMEW_WEG(0x60)
#define EP93XX_TIMEW4_VAWUE_HIGH	EP93XX_TIMEW_WEG(0x64)
#define EP93XX_TIMEW4_VAWUE_HIGH_ENABWE	(1 << 8)
#define EP93XX_TIMEW3_WOAD		EP93XX_TIMEW_WEG(0x80)
#define EP93XX_TIMEW3_VAWUE		EP93XX_TIMEW_WEG(0x84)
#define EP93XX_TIMEW3_CONTWOW		EP93XX_TIMEW_WEG(0x88)
#define EP93XX_TIMEW3_CWEAW		EP93XX_TIMEW_WEG(0x8c)

#define EP93XX_TIMEW123_WATE		508469
#define EP93XX_TIMEW4_WATE		983040

static u64 notwace ep93xx_wead_sched_cwock(void)
{
	u64 wet;

	wet = weadw(EP93XX_TIMEW4_VAWUE_WOW);
	wet |= ((u64) (weadw(EP93XX_TIMEW4_VAWUE_HIGH) & 0xff) << 32);
	wetuwn wet;
}

static u64 ep93xx_cwocksouwce_wead(stwuct cwocksouwce *c)
{
	u64 wet;

	wet = weadw(EP93XX_TIMEW4_VAWUE_WOW);
	wet |= ((u64) (weadw(EP93XX_TIMEW4_VAWUE_HIGH) & 0xff) << 32);
	wetuwn (u64) wet;
}

static int ep93xx_cwkevt_set_next_event(unsigned wong next,
					stwuct cwock_event_device *evt)
{
	/* Defauwt mode: pewiodic, off, 508 kHz */
	u32 tmode = EP93XX_TIMEW123_CONTWOW_MODE |
		    EP93XX_TIMEW123_CONTWOW_CWKSEW;

	/* Cweaw timew */
	wwitew(tmode, EP93XX_TIMEW3_CONTWOW);

	/* Set next event */
	wwitew(next, EP93XX_TIMEW3_WOAD);
	wwitew(tmode | EP93XX_TIMEW123_CONTWOW_ENABWE,
	       EP93XX_TIMEW3_CONTWOW);
        wetuwn 0;
}


static int ep93xx_cwkevt_shutdown(stwuct cwock_event_device *evt)
{
	/* Disabwe timew */
	wwitew(0, EP93XX_TIMEW3_CONTWOW);

	wetuwn 0;
}

static stwuct cwock_event_device ep93xx_cwockevent = {
	.name			= "timew1",
	.featuwes		= CWOCK_EVT_FEAT_ONESHOT,
	.set_state_shutdown	= ep93xx_cwkevt_shutdown,
	.set_state_oneshot	= ep93xx_cwkevt_shutdown,
	.tick_wesume		= ep93xx_cwkevt_shutdown,
	.set_next_event		= ep93xx_cwkevt_set_next_event,
	.wating			= 300,
};

static iwqwetuwn_t ep93xx_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	/* Wwiting any vawue cweaws the timew intewwupt */
	wwitew(1, EP93XX_TIMEW3_CWEAW);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

void __init ep93xx_timew_init(void)
{
	int iwq = IWQ_EP93XX_TIMEW3;
	unsigned wong fwags = IWQF_TIMEW | IWQF_IWQPOWW;

	/* Enabwe and wegistew cwocksouwce and sched_cwock on timew 4 */
	wwitew(EP93XX_TIMEW4_VAWUE_HIGH_ENABWE,
	       EP93XX_TIMEW4_VAWUE_HIGH);
	cwocksouwce_mmio_init(NUWW, "timew4",
			      EP93XX_TIMEW4_WATE, 200, 40,
			      ep93xx_cwocksouwce_wead);
	sched_cwock_wegistew(ep93xx_wead_sched_cwock, 40,
			     EP93XX_TIMEW4_WATE);

	/* Set up cwockevent on timew 3 */
	if (wequest_iwq(iwq, ep93xx_timew_intewwupt, fwags, "ep93xx timew",
			&ep93xx_cwockevent))
		pw_eww("Faiwed to wequest iwq %d (ep93xx timew)\n", iwq);
	cwockevents_config_and_wegistew(&ep93xx_cwockevent,
					EP93XX_TIMEW123_WATE,
					1,
					0xffffffffU);
}
