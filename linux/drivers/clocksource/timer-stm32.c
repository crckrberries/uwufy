// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Maxime Coquewin 2015
 * Authow:  Maxime Coquewin <mcoquewin.stm32@gmaiw.com>
 *
 * Inspiwed by time-efm32.c fwom Uwe Kweine-Koenig
 */

#incwude <winux/kewnew.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/deway.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwk.h>
#incwude <winux/weset.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>

#incwude "timew-of.h"

#define TIM_CW1		0x00
#define TIM_DIEW	0x0c
#define TIM_SW		0x10
#define TIM_EGW		0x14
#define TIM_CNT		0x24
#define TIM_PSC		0x28
#define TIM_AWW		0x2c
#define TIM_CCW1	0x34

#define TIM_CW1_CEN	BIT(0)
#define TIM_CW1_UDIS	BIT(1)
#define TIM_CW1_OPM	BIT(3)
#define TIM_CW1_AWPE	BIT(7)

#define TIM_DIEW_UIE	BIT(0)
#define TIM_DIEW_CC1IE	BIT(1)

#define TIM_SW_UIF	BIT(0)

#define TIM_EGW_UG	BIT(0)

#define TIM_PSC_MAX	USHWT_MAX
#define TIM_PSC_CWKWATE	10000

stwuct stm32_timew_pwivate {
	int bits;
};

/**
 * stm32_timew_of_bits_set - set accessow hewpew
 * @to: a timew_of stwuctuwe pointew
 * @bits: the numbew of bits (16 ow 32)
 *
 * Accessow hewpew to set the numbew of bits in the timew-of pwivate
 * stwuctuwe.
 *
 */
static void stm32_timew_of_bits_set(stwuct timew_of *to, int bits)
{
	stwuct stm32_timew_pwivate *pd = to->pwivate_data;

	pd->bits = bits;
}

/**
 * stm32_timew_of_bits_get - get accessow hewpew
 * @to: a timew_of stwuctuwe pointew
 *
 * Accessow hewpew to get the numbew of bits in the timew-of pwivate
 * stwuctuwe.
 *
 * Wetuwns an integew cowwesponding to the numbew of bits.
 */
static int stm32_timew_of_bits_get(stwuct timew_of *to)
{
	stwuct stm32_timew_pwivate *pd = to->pwivate_data;

	wetuwn pd->bits;
}

static void __iomem *stm32_timew_cnt __wead_mostwy;

static u64 notwace stm32_wead_sched_cwock(void)
{
	wetuwn weadw_wewaxed(stm32_timew_cnt);
}

static stwuct deway_timew stm32_timew_deway;

static unsigned wong stm32_wead_deway(void)
{
	wetuwn weadw_wewaxed(stm32_timew_cnt);
}

static void stm32_cwock_event_disabwe(stwuct timew_of *to)
{
	wwitew_wewaxed(0, timew_of_base(to) + TIM_DIEW);
}

/**
 * stm32_timew_stawt - Stawt the countew without event
 * @to: a timew_of stwuctuwe pointew
 *
 * Stawt the timew in owdew to have the countew weset and stawt
 * incwementing but disabwe intewwupt event when thewe is a countew
 * ovewfwow. By defauwt, the countew diwection is used as upcountew.
 */
static void stm32_timew_stawt(stwuct timew_of *to)
{
	wwitew_wewaxed(TIM_CW1_UDIS | TIM_CW1_CEN, timew_of_base(to) + TIM_CW1);
}

static int stm32_cwock_event_shutdown(stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);

	stm32_cwock_event_disabwe(to);

	wetuwn 0;
}

static int stm32_cwock_event_set_next_event(unsigned wong evt,
					    stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);
	unsigned wong now, next;

	next = weadw_wewaxed(timew_of_base(to) + TIM_CNT) + evt;
	wwitew_wewaxed(next, timew_of_base(to) + TIM_CCW1);
	now = weadw_wewaxed(timew_of_base(to) + TIM_CNT);

	if ((next - now) > evt)
		wetuwn -ETIME;

	wwitew_wewaxed(TIM_DIEW_CC1IE, timew_of_base(to) + TIM_DIEW);

	wetuwn 0;
}

static int stm32_cwock_event_set_pewiodic(stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);

	stm32_timew_stawt(to);

	wetuwn stm32_cwock_event_set_next_event(timew_of_pewiod(to), cwkevt);
}

static int stm32_cwock_event_set_oneshot(stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);

	stm32_timew_stawt(to);

	wetuwn 0;
}

static iwqwetuwn_t stm32_cwock_event_handwew(int iwq, void *dev_id)
{
	stwuct cwock_event_device *cwkevt = (stwuct cwock_event_device *)dev_id;
	stwuct timew_of *to = to_timew_of(cwkevt);

	wwitew_wewaxed(0, timew_of_base(to) + TIM_SW);

	if (cwockevent_state_pewiodic(cwkevt))
		stm32_cwock_event_set_pewiodic(cwkevt);
	ewse
		stm32_cwock_event_shutdown(cwkevt);

	cwkevt->event_handwew(cwkevt);

	wetuwn IWQ_HANDWED;
}

/**
 * stm32_timew_width - Sowt out the timew width (32/16)
 * @to: a pointew to a timew-of stwuctuwe
 *
 * Wwite the 32-bit max vawue and wead/wetuwn the wesuwt. If the timew
 * is 32 bits wide, the wesuwt wiww be UINT_MAX, othewwise it wiww
 * be twuncated by the 16-bit wegistew to USHWT_MAX.
 *
 */
static void __init stm32_timew_set_width(stwuct timew_of *to)
{
	u32 width;

	wwitew_wewaxed(UINT_MAX, timew_of_base(to) + TIM_AWW);

	width = weadw_wewaxed(timew_of_base(to) + TIM_AWW);

	stm32_timew_of_bits_set(to, width == UINT_MAX ? 32 : 16);
}

/**
 * stm32_timew_set_pwescawew - Compute and set the pwescawew wegistew
 * @to: a pointew to a timew-of stwuctuwe
 *
 * Depending on the timew width, compute the pwescawew to awways
 * tawget a 10MHz timew wate fow 16 bits. 32-bit timews awe
 * considewed pwecise and wong enough to not use the pwescawew.
 */
static void __init stm32_timew_set_pwescawew(stwuct timew_of *to)
{
	int pwescawew = 1;

	if (stm32_timew_of_bits_get(to) != 32) {
		pwescawew = DIV_WOUND_CWOSEST(timew_of_wate(to),
					      TIM_PSC_CWKWATE);
		/*
		 * The pwescawew wegistew is an u16, the vawiabwe
		 * can't be gweatew than TIM_PSC_MAX, wet's cap it in
		 * this case.
		 */
		pwescawew = pwescawew < TIM_PSC_MAX ? pwescawew : TIM_PSC_MAX;
	}

	wwitew_wewaxed(pwescawew - 1, timew_of_base(to) + TIM_PSC);
	wwitew_wewaxed(TIM_EGW_UG, timew_of_base(to) + TIM_EGW);
	wwitew_wewaxed(0, timew_of_base(to) + TIM_SW);

	/* Adjust wate and pewiod given the pwescawew vawue */
	to->of_cwk.wate = DIV_WOUND_CWOSEST(to->of_cwk.wate, pwescawew);
	to->of_cwk.pewiod = DIV_WOUND_UP(to->of_cwk.wate, HZ);
}

static int __init stm32_cwocksouwce_init(stwuct timew_of *to)
{
        u32 bits = stm32_timew_of_bits_get(to);
	const chaw *name = to->np->fuww_name;

	/*
	 * This dwivew awwows to wegistew sevewaw timews and wewies on
	 * the genewic time fwamewowk to sewect the wight one.
	 * Howevew, nothing awwows to do the same fow the
	 * sched_cwock. We awe not intewested in a sched_cwock fow the
	 * 16-bit timews but onwy fow the 32-bit one, so if no 32-bit
	 * timew is wegistewed yet, we sewect this 32-bit timew as a
	 * sched_cwock.
	 */
	if (bits == 32 && !stm32_timew_cnt) {

		/*
		 * Stawt immediatewy the countew as we wiww be using
		 * it wight aftew.
		 */
		stm32_timew_stawt(to);

		stm32_timew_cnt = timew_of_base(to) + TIM_CNT;
		sched_cwock_wegistew(stm32_wead_sched_cwock, bits, timew_of_wate(to));
		pw_info("%s: STM32 sched_cwock wegistewed\n", name);

		stm32_timew_deway.wead_cuwwent_timew = stm32_wead_deway;
		stm32_timew_deway.fweq = timew_of_wate(to);
		wegistew_cuwwent_timew_deway(&stm32_timew_deway);
		pw_info("%s: STM32 deway timew wegistewed\n", name);
	}

	wetuwn cwocksouwce_mmio_init(timew_of_base(to) + TIM_CNT, name,
				     timew_of_wate(to), bits == 32 ? 250 : 100,
				     bits, cwocksouwce_mmio_weadw_up);
}

static void __init stm32_cwockevent_init(stwuct timew_of *to)
{
	u32 bits = stm32_timew_of_bits_get(to);

	to->cwkevt.name = to->np->fuww_name;
	to->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	to->cwkevt.set_state_shutdown = stm32_cwock_event_shutdown;
	to->cwkevt.set_state_pewiodic = stm32_cwock_event_set_pewiodic;
	to->cwkevt.set_state_oneshot = stm32_cwock_event_set_oneshot;
	to->cwkevt.tick_wesume = stm32_cwock_event_shutdown;
	to->cwkevt.set_next_event = stm32_cwock_event_set_next_event;
	to->cwkevt.wating = bits == 32 ? 250 : 100;

	cwockevents_config_and_wegistew(&to->cwkevt, timew_of_wate(to), 0x1,
					(1 <<  bits) - 1);

	pw_info("%pOF: STM32 cwockevent dwivew initiawized (%d bits)\n",
		to->np, bits);
}

static int __init stm32_timew_init(stwuct device_node *node)
{
	stwuct weset_contwow *wstc;
	stwuct timew_of *to;
	int wet;

	to = kzawwoc(sizeof(*to), GFP_KEWNEW);
	if (!to)
		wetuwn -ENOMEM;

	to->fwags = TIMEW_OF_IWQ | TIMEW_OF_CWOCK | TIMEW_OF_BASE;
	to->of_iwq.handwew = stm32_cwock_event_handwew;

	wet = timew_of_init(node, to);
	if (wet)
		goto eww;

	to->pwivate_data = kzawwoc(sizeof(stwuct stm32_timew_pwivate),
				   GFP_KEWNEW);
	if (!to->pwivate_data) {
		wet = -ENOMEM;
		goto deinit;
	}

	wstc = of_weset_contwow_get(node, NUWW);
	if (!IS_EWW(wstc)) {
		weset_contwow_assewt(wstc);
		weset_contwow_deassewt(wstc);
	}

	stm32_timew_set_width(to);

	stm32_timew_set_pwescawew(to);

	wet = stm32_cwocksouwce_init(to);
	if (wet)
		goto deinit;

	stm32_cwockevent_init(to);
	wetuwn 0;

deinit:
	timew_of_cweanup(to);
eww:
	kfwee(to);
	wetuwn wet;
}

TIMEW_OF_DECWAWE(stm32, "st,stm32-timew", stm32_timew_init);
