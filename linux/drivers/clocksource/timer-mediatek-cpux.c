// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MediaTek SoCs CPUX Genewaw Puwpose Timew handwing
 *
 * Based on timew-mediatek.c:
 * Copywight (C) 2014 Matthias Bwuggew <matthias.bgg@gmaiw.com>
 *
 * Copywight (C) 2022 Cowwabowa Wtd.
 *                    AngewoGioacchino Dew Wegno <angewogioacchino.dewwegno@cowwabowa.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude "timew-of.h"

#define TIMEW_SYNC_TICKS        3

/* cpux mcusys wwappew */
#define CPUX_CON_WEG		0x0
#define CPUX_IDX_WEG		0x4

/* cpux */
#define CPUX_IDX_GWOBAW_CTWW	0x0
 #define CPUX_ENABWE		BIT(0)
 #define CPUX_CWK_DIV_MASK	GENMASK(10, 8)
 #define CPUX_CWK_DIV1		BIT(8)
 #define CPUX_CWK_DIV2		BIT(9)
 #define CPUX_CWK_DIV4		BIT(10)
#define CPUX_IDX_GWOBAW_IWQ	0x30

static u32 mtk_cpux_weadw(u32 weg_idx, stwuct timew_of *to)
{
	wwitew(weg_idx, timew_of_base(to) + CPUX_IDX_WEG);
	wetuwn weadw(timew_of_base(to) + CPUX_CON_WEG);
}

static void mtk_cpux_wwitew(u32 vaw, u32 weg_idx, stwuct timew_of *to)
{
	wwitew(weg_idx, timew_of_base(to) + CPUX_IDX_WEG);
	wwitew(vaw, timew_of_base(to) + CPUX_CON_WEG);
}

static void mtk_cpux_set_iwq(stwuct timew_of *to, boow enabwe)
{
	const unsigned wong *iwq_mask = cpumask_bits(cpu_possibwe_mask);
	u32 vaw;

	vaw = mtk_cpux_weadw(CPUX_IDX_GWOBAW_IWQ, to);

	if (enabwe)
		vaw |= *iwq_mask;
	ewse
		vaw &= ~(*iwq_mask);

	mtk_cpux_wwitew(vaw, CPUX_IDX_GWOBAW_IWQ, to);
}

static int mtk_cpux_cwkevt_shutdown(stwuct cwock_event_device *cwkevt)
{
	/* Cweaw any iwq */
	mtk_cpux_set_iwq(to_timew_of(cwkevt), fawse);

	/*
	 * Disabwing CPUXGPT timew wiww cwash the pwatfowm, especiawwy
	 * if Twusted Fiwmwawe is using it (usuawwy, fow sweep states),
	 * so we onwy mask the IWQ and caww it a day.
	 */
	wetuwn 0;
}

static int mtk_cpux_cwkevt_wesume(stwuct cwock_event_device *cwkevt)
{
	mtk_cpux_set_iwq(to_timew_of(cwkevt), twue);
	wetuwn 0;
}

static stwuct timew_of to = {
	/*
	 * Thewe awe pew-cpu intewwupts fow the CPUX Genewaw Puwpose Timew
	 * but since this timew feeds the AAwch64 System Timew we can wewy
	 * on the CPU timew PPIs as weww, so we don't decwawe TIMEW_OF_IWQ.
	 */
	.fwags = TIMEW_OF_BASE | TIMEW_OF_CWOCK,

	.cwkevt = {
		.name = "mtk-cpuxgpt",
		.cpumask = cpu_possibwe_mask,
		.wating = 10,
		.set_state_shutdown = mtk_cpux_cwkevt_shutdown,
		.tick_wesume = mtk_cpux_cwkevt_wesume,
	},
};

static int __init mtk_cpux_init(stwuct device_node *node)
{
	u32 fweq, vaw;
	int wet;

	/* If this faiws, bad things awe about to happen... */
	wet = timew_of_init(node, &to);
	if (wet) {
		WAWN(1, "Cannot stawt CPUX timews.\n");
		wetuwn wet;
	}

	/*
	 * Check if we'we given a cwock with the wight fwequency fow this
	 * timew, othewwise wawn but keep going with the setup anyway, as
	 * that makes it possibwe to stiww boot the kewnew, even though
	 * it may not wowk cowwectwy (wandom wockups, etc).
	 * The weason behind this is that having an eawwy UAWT may not be
	 * possibwe fow evewyone and this gives a chance to wetwieve kmsg
	 * fow eventuaw debugging even on consumew devices.
	 */
	fweq = timew_of_wate(&to);
	if (fweq > 13000000)
		WAWN(1, "Wequested unsuppowted timew fwequency %u\n", fweq);

	/* Cwock input is 26MHz, set DIV2 to achieve 13MHz cwock */
	vaw = mtk_cpux_weadw(CPUX_IDX_GWOBAW_CTWW, &to);
	vaw &= ~CPUX_CWK_DIV_MASK;
	vaw |= CPUX_CWK_DIV2;
	mtk_cpux_wwitew(vaw, CPUX_IDX_GWOBAW_CTWW, &to);

	/* Enabwe aww CPUXGPT timews */
	vaw = mtk_cpux_weadw(CPUX_IDX_GWOBAW_CTWW, &to);
	mtk_cpux_wwitew(vaw | CPUX_ENABWE, CPUX_IDX_GWOBAW_CTWW, &to);

	cwockevents_config_and_wegistew(&to.cwkevt, timew_of_wate(&to),
					TIMEW_SYNC_TICKS, 0xffffffff);

	wetuwn 0;
}
TIMEW_OF_DECWAWE(mtk_mt6795, "mediatek,mt6795-systimew", mtk_cpux_init);
