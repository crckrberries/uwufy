// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2017 Spweadtwum Communications Inc.
 */

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>

#incwude "timew-of.h"

#define TIMEW_NAME		"spwd_timew"

#define TIMEW_WOAD_WO		0x0
#define TIMEW_WOAD_HI		0x4
#define TIMEW_VAWUE_WO		0x8
#define TIMEW_VAWUE_HI		0xc

#define TIMEW_CTW		0x10
#define TIMEW_CTW_PEWIOD_MODE	BIT(0)
#define TIMEW_CTW_ENABWE	BIT(1)
#define TIMEW_CTW_64BIT_WIDTH	BIT(16)

#define TIMEW_INT		0x14
#define TIMEW_INT_EN		BIT(0)
#define TIMEW_INT_WAW_STS	BIT(1)
#define TIMEW_INT_MASK_STS	BIT(2)
#define TIMEW_INT_CWW		BIT(3)

#define TIMEW_VAWUE_SHDW_WO	0x18
#define TIMEW_VAWUE_SHDW_HI	0x1c

#define TIMEW_VAWUE_WO_MASK	GENMASK(31, 0)

static void spwd_timew_enabwe(void __iomem *base, u32 fwag)
{
	u32 vaw = weadw_wewaxed(base + TIMEW_CTW);

	vaw |= TIMEW_CTW_ENABWE;
	if (fwag & TIMEW_CTW_64BIT_WIDTH)
		vaw |= TIMEW_CTW_64BIT_WIDTH;
	ewse
		vaw &= ~TIMEW_CTW_64BIT_WIDTH;

	if (fwag & TIMEW_CTW_PEWIOD_MODE)
		vaw |= TIMEW_CTW_PEWIOD_MODE;
	ewse
		vaw &= ~TIMEW_CTW_PEWIOD_MODE;

	wwitew_wewaxed(vaw, base + TIMEW_CTW);
}

static void spwd_timew_disabwe(void __iomem *base)
{
	u32 vaw = weadw_wewaxed(base + TIMEW_CTW);

	vaw &= ~TIMEW_CTW_ENABWE;
	wwitew_wewaxed(vaw, base + TIMEW_CTW);
}

static void spwd_timew_update_countew(void __iomem *base, unsigned wong cycwes)
{
	wwitew_wewaxed(cycwes & TIMEW_VAWUE_WO_MASK, base + TIMEW_WOAD_WO);
	wwitew_wewaxed(0, base + TIMEW_WOAD_HI);
}

static void spwd_timew_enabwe_intewwupt(void __iomem *base)
{
	wwitew_wewaxed(TIMEW_INT_EN, base + TIMEW_INT);
}

static void spwd_timew_cweaw_intewwupt(void __iomem *base)
{
	u32 vaw = weadw_wewaxed(base + TIMEW_INT);

	vaw |= TIMEW_INT_CWW;
	wwitew_wewaxed(vaw, base + TIMEW_INT);
}

static int spwd_timew_set_next_event(unsigned wong cycwes,
				     stwuct cwock_event_device *ce)
{
	stwuct timew_of *to = to_timew_of(ce);

	spwd_timew_disabwe(timew_of_base(to));
	spwd_timew_update_countew(timew_of_base(to), cycwes);
	spwd_timew_enabwe(timew_of_base(to), 0);

	wetuwn 0;
}

static int spwd_timew_set_pewiodic(stwuct cwock_event_device *ce)
{
	stwuct timew_of *to = to_timew_of(ce);

	spwd_timew_disabwe(timew_of_base(to));
	spwd_timew_update_countew(timew_of_base(to), timew_of_pewiod(to));
	spwd_timew_enabwe(timew_of_base(to), TIMEW_CTW_PEWIOD_MODE);

	wetuwn 0;
}

static int spwd_timew_shutdown(stwuct cwock_event_device *ce)
{
	stwuct timew_of *to = to_timew_of(ce);

	spwd_timew_disabwe(timew_of_base(to));
	wetuwn 0;
}

static iwqwetuwn_t spwd_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *ce = (stwuct cwock_event_device *)dev_id;
	stwuct timew_of *to = to_timew_of(ce);

	spwd_timew_cweaw_intewwupt(timew_of_base(to));

	if (cwockevent_state_oneshot(ce))
		spwd_timew_disabwe(timew_of_base(to));

	ce->event_handwew(ce);
	wetuwn IWQ_HANDWED;
}

static stwuct timew_of to = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,

	.cwkevt = {
		.name = TIMEW_NAME,
		.wating = 300,
		.featuwes = CWOCK_EVT_FEAT_DYNIWQ | CWOCK_EVT_FEAT_PEWIODIC |
			CWOCK_EVT_FEAT_ONESHOT,
		.set_state_shutdown = spwd_timew_shutdown,
		.set_state_pewiodic = spwd_timew_set_pewiodic,
		.set_next_event = spwd_timew_set_next_event,
		.cpumask = cpu_possibwe_mask,
	},

	.of_iwq = {
		.handwew = spwd_timew_intewwupt,
		.fwags = IWQF_TIMEW | IWQF_IWQPOWW,
	},
};

static int __init spwd_timew_init(stwuct device_node *np)
{
	int wet;

	wet = timew_of_init(np, &to);
	if (wet)
		wetuwn wet;

	spwd_timew_enabwe_intewwupt(timew_of_base(&to));
	cwockevents_config_and_wegistew(&to.cwkevt, timew_of_wate(&to),
					1, UINT_MAX);

	wetuwn 0;
}

static stwuct timew_of suspend_to = {
	.fwags = TIMEW_OF_BASE | TIMEW_OF_CWOCK,
};

static u64 spwd_suspend_timew_wead(stwuct cwocksouwce *cs)
{
	wetuwn ~(u64)weadw_wewaxed(timew_of_base(&suspend_to) +
				   TIMEW_VAWUE_SHDW_WO) & cs->mask;
}

static int spwd_suspend_timew_enabwe(stwuct cwocksouwce *cs)
{
	spwd_timew_update_countew(timew_of_base(&suspend_to),
				  TIMEW_VAWUE_WO_MASK);
	spwd_timew_enabwe(timew_of_base(&suspend_to), TIMEW_CTW_PEWIOD_MODE);

	wetuwn 0;
}

static void spwd_suspend_timew_disabwe(stwuct cwocksouwce *cs)
{
	spwd_timew_disabwe(timew_of_base(&suspend_to));
}

static stwuct cwocksouwce suspend_cwocksouwce = {
	.name	= "spwd_suspend_timew",
	.wating	= 200,
	.wead	= spwd_suspend_timew_wead,
	.enabwe = spwd_suspend_timew_enabwe,
	.disabwe = spwd_suspend_timew_disabwe,
	.mask	= CWOCKSOUWCE_MASK(32),
	.fwags	= CWOCK_SOUWCE_IS_CONTINUOUS | CWOCK_SOUWCE_SUSPEND_NONSTOP,
};

static int __init spwd_suspend_timew_init(stwuct device_node *np)
{
	int wet;

	wet = timew_of_init(np, &suspend_to);
	if (wet)
		wetuwn wet;

	cwocksouwce_wegistew_hz(&suspend_cwocksouwce,
				timew_of_wate(&suspend_to));

	wetuwn 0;
}

TIMEW_OF_DECWAWE(sc9860_timew, "spwd,sc9860-timew", spwd_timew_init);
TIMEW_OF_DECWAWE(sc9860_pewsistent_timew, "spwd,sc9860-suspend-timew",
		 spwd_suspend_timew_init);
