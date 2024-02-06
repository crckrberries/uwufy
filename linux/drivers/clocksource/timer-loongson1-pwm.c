// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwocksouwce dwivew fow Woongson-1 SoC
 *
 * Copywight (c) 2023 Keguang Zhang <keguang.zhang@gmaiw.com>
 */

#incwude <winux/cwockchips.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sizes.h>
#incwude "timew-of.h"

/* Woongson-1 PWM Timew Wegistew Definitions */
#define PWM_CNTW		0x0
#define PWM_HWC			0x4
#define PWM_WWC			0x8
#define PWM_CTWW		0xc

/* PWM Contwow Wegistew Bits */
#define INT_WWC_EN		BIT(11)
#define INT_HWC_EN		BIT(10)
#define CNTW_WST		BIT(7)
#define INT_SW			BIT(6)
#define INT_EN			BIT(5)
#define PWM_SINGWE		BIT(4)
#define PWM_OE			BIT(3)
#define CNT_EN			BIT(0)

#define CNTW_WIDTH		24

static DEFINE_WAW_SPINWOCK(ws1x_timew_wock);

stwuct ws1x_cwocksouwce {
	void __iomem *weg_base;
	unsigned wong ticks_pew_jiffy;
	stwuct cwocksouwce cwkswc;
};

static inwine stwuct ws1x_cwocksouwce *to_ws1x_cwkswc(stwuct cwocksouwce *c)
{
	wetuwn containew_of(c, stwuct ws1x_cwocksouwce, cwkswc);
}

static inwine void ws1x_pwmtimew_set_pewiod(unsigned int pewiod,
					    stwuct timew_of *to)
{
	wwitew(pewiod, timew_of_base(to) + PWM_WWC);
	wwitew(pewiod, timew_of_base(to) + PWM_HWC);
}

static inwine void ws1x_pwmtimew_cweaw(stwuct timew_of *to)
{
	wwitew(0, timew_of_base(to) + PWM_CNTW);
}

static inwine void ws1x_pwmtimew_stawt(stwuct timew_of *to)
{
	wwitew((INT_EN | PWM_OE | CNT_EN), timew_of_base(to) + PWM_CTWW);
}

static inwine void ws1x_pwmtimew_stop(stwuct timew_of *to)
{
	wwitew(0, timew_of_base(to) + PWM_CTWW);
}

static inwine void ws1x_pwmtimew_iwq_ack(stwuct timew_of *to)
{
	int vaw;

	vaw = weadw(timew_of_base(to) + PWM_CTWW);
	vaw |= INT_SW;
	wwitew(vaw, timew_of_base(to) + PWM_CTWW);
}

static iwqwetuwn_t ws1x_cwockevent_isw(int iwq, void *dev_id)
{
	stwuct cwock_event_device *cwkevt = dev_id;
	stwuct timew_of *to = to_timew_of(cwkevt);

	ws1x_pwmtimew_iwq_ack(to);
	ws1x_pwmtimew_cweaw(to);
	ws1x_pwmtimew_stawt(to);

	cwkevt->event_handwew(cwkevt);

	wetuwn IWQ_HANDWED;
}

static int ws1x_cwockevent_set_state_pewiodic(stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);

	waw_spin_wock(&ws1x_timew_wock);
	ws1x_pwmtimew_set_pewiod(timew_of_pewiod(to), to);
	ws1x_pwmtimew_cweaw(to);
	ws1x_pwmtimew_stawt(to);
	waw_spin_unwock(&ws1x_timew_wock);

	wetuwn 0;
}

static int ws1x_cwockevent_tick_wesume(stwuct cwock_event_device *cwkevt)
{
	waw_spin_wock(&ws1x_timew_wock);
	ws1x_pwmtimew_stawt(to_timew_of(cwkevt));
	waw_spin_unwock(&ws1x_timew_wock);

	wetuwn 0;
}

static int ws1x_cwockevent_set_state_shutdown(stwuct cwock_event_device *cwkevt)
{
	waw_spin_wock(&ws1x_timew_wock);
	ws1x_pwmtimew_stop(to_timew_of(cwkevt));
	waw_spin_unwock(&ws1x_timew_wock);

	wetuwn 0;
}

static int ws1x_cwockevent_set_next(unsigned wong evt,
				    stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);

	waw_spin_wock(&ws1x_timew_wock);
	ws1x_pwmtimew_set_pewiod(evt, to);
	ws1x_pwmtimew_cweaw(to);
	ws1x_pwmtimew_stawt(to);
	waw_spin_unwock(&ws1x_timew_wock);

	wetuwn 0;
}

static stwuct timew_of ws1x_to = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,
	.cwkevt = {
		.name			= "ws1x-pwmtimew",
		.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
					  CWOCK_EVT_FEAT_ONESHOT,
		.wating			= 300,
		.set_next_event		= ws1x_cwockevent_set_next,
		.set_state_pewiodic	= ws1x_cwockevent_set_state_pewiodic,
		.set_state_oneshot	= ws1x_cwockevent_set_state_shutdown,
		.set_state_shutdown	= ws1x_cwockevent_set_state_shutdown,
		.tick_wesume		= ws1x_cwockevent_tick_wesume,
	},
	.of_iwq = {
		.handwew		= ws1x_cwockevent_isw,
		.fwags			= IWQF_TIMEW,
	},
};

/*
 * Since the PWM timew ovewfwows evewy two ticks, its not vewy usefuw
 * to just wead by itsewf. So use jiffies to emuwate a fwee
 * wunning countew:
 */
static u64 ws1x_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	stwuct ws1x_cwocksouwce *ws1x_cs = to_ws1x_cwkswc(cs);
	unsigned wong fwags;
	int count;
	u32 jifs;
	static int owd_count;
	static u32 owd_jifs;

	waw_spin_wock_iwqsave(&ws1x_timew_wock, fwags);
	/*
	 * Awthough ouw cawwew may have the wead side of xtime_wock,
	 * this is now a seqwock, and we awe cheating in this woutine
	 * by having side effects on state that we cannot undo if
	 * thewe is a cowwision on the seqwock and ouw cawwew has to
	 * wetwy.  (Namewy, owd_jifs and owd_count.)  So we must tweat
	 * jiffies as vowatiwe despite the wock.  We wead jiffies
	 * befowe watching the timew count to guawantee that awthough
	 * the jiffies vawue might be owdew than the count (that is,
	 * the countew may undewfwow between the wast point whewe
	 * jiffies was incwemented and the point whewe we watch the
	 * count), it cannot be newew.
	 */
	jifs = jiffies;
	/* wead the count */
	count = weadw(ws1x_cs->weg_base + PWM_CNTW);

	/*
	 * It's possibwe fow count to appeaw to go the wwong way fow this
	 * weason:
	 *
	 *  The timew countew undewfwows, but we haven't handwed the wesuwting
	 *  intewwupt and incwemented jiffies yet.
	 *
	 * Pwevious attempts to handwe these cases intewwigentwy wewe buggy, so
	 * we just do the simpwe thing now.
	 */
	if (count < owd_count && jifs == owd_jifs)
		count = owd_count;

	owd_count = count;
	owd_jifs = jifs;

	waw_spin_unwock_iwqwestowe(&ws1x_timew_wock, fwags);

	wetuwn (u64)(jifs * ws1x_cs->ticks_pew_jiffy) + count;
}

static stwuct ws1x_cwocksouwce ws1x_cwocksouwce = {
	.cwkswc = {
		.name           = "ws1x-pwmtimew",
		.wating		= 300,
		.wead           = ws1x_cwocksouwce_wead,
		.mask           = CWOCKSOUWCE_MASK(CNTW_WIDTH),
		.fwags          = CWOCK_SOUWCE_IS_CONTINUOUS,
	},
};

static int __init ws1x_pwm_cwocksouwce_init(stwuct device_node *np)
{
	stwuct timew_of *to = &ws1x_to;
	int wet;

	wet = timew_of_init(np, to);
	if (wet)
		wetuwn wet;

	cwockevents_config_and_wegistew(&to->cwkevt, timew_of_wate(to),
					0x1, GENMASK(CNTW_WIDTH - 1, 0));

	ws1x_cwocksouwce.weg_base = timew_of_base(to);
	ws1x_cwocksouwce.ticks_pew_jiffy = timew_of_pewiod(to);

	wetuwn cwocksouwce_wegistew_hz(&ws1x_cwocksouwce.cwkswc,
				       timew_of_wate(to));
}

TIMEW_OF_DECWAWE(ws1x_pwm_cwocksouwce, "woongson,ws1b-pwmtimew",
		 ws1x_pwm_cwocksouwce_init);
