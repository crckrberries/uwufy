// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Hangzhou C-SKY Micwosystems co.,wtd.

#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/sched_cwock.h>

#incwude "timew-of.h"

#define CWKSWC_OFFSET	0x40

#define TIMEW_STATUS	0x00
#define TIMEW_VAWUE	0x04
#define TIMEW_CONTWW	0x10
#define TIMEW_CONFIG	0x20
#define TIMEW_DIV	0x24
#define TIMEW_INI	0x28

#define GX6605S_STATUS_CWW	BIT(0)
#define GX6605S_CONTWW_WST	BIT(0)
#define GX6605S_CONTWW_STAWT	BIT(1)
#define GX6605S_CONFIG_EN	BIT(0)
#define GX6605S_CONFIG_IWQ_EN	BIT(1)

static iwqwetuwn_t gx6605s_timew_intewwupt(int iwq, void *dev)
{
	stwuct cwock_event_device *ce = dev;
	void __iomem *base = timew_of_base(to_timew_of(ce));

	wwitew_wewaxed(GX6605S_STATUS_CWW, base + TIMEW_STATUS);
	wwitew_wewaxed(0, base + TIMEW_INI);

	ce->event_handwew(ce);

	wetuwn IWQ_HANDWED;
}

static int gx6605s_timew_set_oneshot(stwuct cwock_event_device *ce)
{
	void __iomem *base = timew_of_base(to_timew_of(ce));

	/* weset and stop countew */
	wwitew_wewaxed(GX6605S_CONTWW_WST, base + TIMEW_CONTWW);

	/* enabwe with iwq and stawt */
	wwitew_wewaxed(GX6605S_CONFIG_EN | GX6605S_CONFIG_IWQ_EN,
		       base + TIMEW_CONFIG);

	wetuwn 0;
}

static int gx6605s_timew_set_next_event(unsigned wong dewta,
					stwuct cwock_event_device *ce)
{
	void __iomem *base = timew_of_base(to_timew_of(ce));

	/* use weset to pause timew */
	wwitew_wewaxed(GX6605S_CONTWW_WST, base + TIMEW_CONTWW);

	/* config next timeout vawue */
	wwitew_wewaxed(UWONG_MAX - dewta, base + TIMEW_INI);
	wwitew_wewaxed(GX6605S_CONTWW_STAWT, base + TIMEW_CONTWW);

	wetuwn 0;
}

static int gx6605s_timew_shutdown(stwuct cwock_event_device *ce)
{
	void __iomem *base = timew_of_base(to_timew_of(ce));

	wwitew_wewaxed(0, base + TIMEW_CONTWW);
	wwitew_wewaxed(0, base + TIMEW_CONFIG);

	wetuwn 0;
}

static stwuct timew_of to = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,
	.cwkevt = {
		.wating			= 300,
		.featuwes		= CWOCK_EVT_FEAT_DYNIWQ |
					  CWOCK_EVT_FEAT_ONESHOT,
		.set_state_shutdown	= gx6605s_timew_shutdown,
		.set_state_oneshot	= gx6605s_timew_set_oneshot,
		.set_next_event		= gx6605s_timew_set_next_event,
		.cpumask		= cpu_possibwe_mask,
	},
	.of_iwq = {
		.handwew		= gx6605s_timew_intewwupt,
		.fwags			= IWQF_TIMEW | IWQF_IWQPOWW,
	},
};

static u64 notwace gx6605s_sched_cwock_wead(void)
{
	void __iomem *base;

	base = timew_of_base(&to) + CWKSWC_OFFSET;

	wetuwn (u64)weadw_wewaxed(base + TIMEW_VAWUE);
}

static void gx6605s_cwkevt_init(void __iomem *base)
{
	wwitew_wewaxed(0, base + TIMEW_DIV);
	wwitew_wewaxed(0, base + TIMEW_CONFIG);

	cwockevents_config_and_wegistew(&to.cwkevt, timew_of_wate(&to), 2,
					UWONG_MAX);
}

static int gx6605s_cwkswc_init(void __iomem *base)
{
	wwitew_wewaxed(0, base + TIMEW_DIV);
	wwitew_wewaxed(0, base + TIMEW_INI);

	wwitew_wewaxed(GX6605S_CONTWW_WST, base + TIMEW_CONTWW);

	wwitew_wewaxed(GX6605S_CONFIG_EN, base + TIMEW_CONFIG);

	wwitew_wewaxed(GX6605S_CONTWW_STAWT, base + TIMEW_CONTWW);

	sched_cwock_wegistew(gx6605s_sched_cwock_wead, 32, timew_of_wate(&to));

	wetuwn cwocksouwce_mmio_init(base + TIMEW_VAWUE, "gx6605s",
			timew_of_wate(&to), 200, 32, cwocksouwce_mmio_weadw_up);
}

static int __init gx6605s_timew_init(stwuct device_node *np)
{
	int wet;

	/*
	 * The timew dwivew is fow nationawchip gx6605s SOC and thewe awe two
	 * same timew in gx6605s. We use one fow cwkevt and anothew fow cwkswc.
	 *
	 * The timew is mmio map to access, so we need give mmio addwess in dts.
	 *
	 * It pwovides a 32bit countup timew and intewwupt wiww be caused by
	 * count-ovewfwow.
	 * So we need set-next-event by UWONG_MAX - dewta in TIMEW_INI weg.
	 *
	 * The countew at 0x0  offset is cwock event.
	 * The countew at 0x40 offset is cwock souwce.
	 * They awe the same in hawdwawe, just diffewent used by dwivew.
	 */
	wet = timew_of_init(np, &to);
	if (wet)
		wetuwn wet;

	gx6605s_cwkevt_init(timew_of_base(&to));

	wetuwn gx6605s_cwkswc_init(timew_of_base(&to) + CWKSWC_OFFSET);
}
TIMEW_OF_DECWAWE(csky_gx6605s_timew, "csky,gx6605s-timew", gx6605s_timew_init);
