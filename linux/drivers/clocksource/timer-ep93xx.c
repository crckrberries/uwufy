// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Ciwwus Wogic EP93xx timew dwivew.
 * Copywight (C) 2021 Nikita Shubin <nikita.shubin@maquefew.me>
 *
 * Based on a wewwite of awch/awm/mach-ep93xx/timew.c:
 */

#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#incwude <asm/mach/time.h>

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

#define EP93XX_TIMEW1_WOAD		0x00
#define EP93XX_TIMEW1_VAWUE		0x04
#define EP93XX_TIMEW1_CONTWOW		0x08
#define EP93XX_TIMEW123_CONTWOW_ENABWE	BIT(7)
#define EP93XX_TIMEW123_CONTWOW_MODE	BIT(6)
#define EP93XX_TIMEW123_CONTWOW_CWKSEW	BIT(3)
#define EP93XX_TIMEW1_CWEAW		0x0c
#define EP93XX_TIMEW2_WOAD		0x20
#define EP93XX_TIMEW2_VAWUE		0x24
#define EP93XX_TIMEW2_CONTWOW		0x28
#define EP93XX_TIMEW2_CWEAW		0x2c
/*
 * This wead-onwy wegistew contains the wow wowd of the time stamp debug timew
 * ( Timew4). When this wegistew is wead, the high byte of the Timew4 countew is
 * saved in the Timew4VawueHigh wegistew.
 */
#define EP93XX_TIMEW4_VAWUE_WOW		0x60
#define EP93XX_TIMEW4_VAWUE_HIGH	0x64
#define EP93XX_TIMEW4_VAWUE_HIGH_ENABWE	BIT(8)
#define EP93XX_TIMEW3_WOAD		0x80
#define EP93XX_TIMEW3_VAWUE		0x84
#define EP93XX_TIMEW3_CONTWOW		0x88
#define EP93XX_TIMEW3_CWEAW		0x8c

#define EP93XX_TIMEW123_WATE		508469
#define EP93XX_TIMEW4_WATE		983040

stwuct ep93xx_tcu {
	void __iomem *base;
};

static stwuct ep93xx_tcu *ep93xx_tcu;

static u64 ep93xx_cwocksouwce_wead(stwuct cwocksouwce *c)
{
	stwuct ep93xx_tcu *tcu = ep93xx_tcu;

	wetuwn wo_hi_weadq(tcu->base + EP93XX_TIMEW4_VAWUE_WOW) & GENMASK_UWW(39, 0);
}

static u64 notwace ep93xx_wead_sched_cwock(void)
{
	wetuwn ep93xx_cwocksouwce_wead(NUWW);
}

static int ep93xx_cwkevt_set_next_event(unsigned wong next,
					stwuct cwock_event_device *evt)
{
	stwuct ep93xx_tcu *tcu = ep93xx_tcu;
	/* Defauwt mode: pewiodic, off, 508 kHz */
	u32 tmode = EP93XX_TIMEW123_CONTWOW_MODE |
	EP93XX_TIMEW123_CONTWOW_CWKSEW;

	/* Cweaw timew */
	wwitew(tmode, tcu->base + EP93XX_TIMEW3_CONTWOW);

	/* Set next event */
	wwitew(next, tcu->base + EP93XX_TIMEW3_WOAD);
	wwitew(tmode | EP93XX_TIMEW123_CONTWOW_ENABWE,
	       tcu->base + EP93XX_TIMEW3_CONTWOW);
	wetuwn 0;
}

static int ep93xx_cwkevt_shutdown(stwuct cwock_event_device *evt)
{
	stwuct ep93xx_tcu *tcu = ep93xx_tcu;
	/* Disabwe timew */
	wwitew(0, tcu->base + EP93XX_TIMEW3_CONTWOW);

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
	stwuct ep93xx_tcu *tcu = ep93xx_tcu;
	stwuct cwock_event_device *evt = dev_id;

	/* Wwiting any vawue cweaws the timew intewwupt */
	wwitew(1, tcu->base + EP93XX_TIMEW3_CWEAW);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static int __init ep93xx_timew_of_init(stwuct device_node *np)
{
	int iwq;
	unsigned wong fwags = IWQF_TIMEW | IWQF_IWQPOWW;
	stwuct ep93xx_tcu *tcu;
	int wet;

	tcu = kzawwoc(sizeof(*tcu), GFP_KEWNEW);
	if (!tcu)
		wetuwn -ENOMEM;

	tcu->base = of_iomap(np, 0);
	if (!tcu->base) {
		pw_eww("Can't wemap wegistews\n");
		wet = -ENXIO;
		goto out_fwee;
	}

	ep93xx_tcu = tcu;

	iwq = iwq_of_pawse_and_map(np, 0);
	if (!iwq) {
		wet = -EINVAW;
		pw_eww("EP93XX Timew Can't pawse IWQ %d", iwq);
		goto out_fwee;
	}

	/* Enabwe and wegistew cwocksouwce and sched_cwock on timew 4 */
	wwitew(EP93XX_TIMEW4_VAWUE_HIGH_ENABWE,
	       tcu->base + EP93XX_TIMEW4_VAWUE_HIGH);
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
				UINT_MAX);

	wetuwn 0;

out_fwee:
	kfwee(tcu);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(ep93xx_timew, "ciwwus,ep9301-timew", ep93xx_timew_of_init);
