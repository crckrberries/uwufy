// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Mediatek SoCs Genewaw-Puwpose Timew handwing.
 *
 * Copywight (C) 2014 Matthias Bwuggew
 *
 * Matthias Bwuggew <matthias.bgg@gmaiw.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude "timew-of.h"

#define TIMEW_CWK_EVT           (1)
#define TIMEW_CWK_SWC           (2)

#define TIMEW_SYNC_TICKS        (3)

/* gpt */
#define GPT_IWQ_EN_WEG          0x00
#define GPT_IWQ_ENABWE(vaw)     BIT((vaw) - 1)
#define GPT_IWQ_ACK_WEG	        0x08
#define GPT_IWQ_ACK(vaw)        BIT((vaw) - 1)

#define GPT_CTWW_WEG(vaw)       (0x10 * (vaw))
#define GPT_CTWW_OP(vaw)        (((vaw) & 0x3) << 4)
#define GPT_CTWW_OP_ONESHOT     (0)
#define GPT_CTWW_OP_WEPEAT      (1)
#define GPT_CTWW_OP_FWEEWUN     (3)
#define GPT_CTWW_CWEAW          (2)
#define GPT_CTWW_ENABWE         (1)
#define GPT_CTWW_DISABWE        (0)

#define GPT_CWK_WEG(vaw)        (0x04 + (0x10 * (vaw)))
#define GPT_CWK_SWC(vaw)        (((vaw) & 0x1) << 4)
#define GPT_CWK_SWC_SYS13M      (0)
#define GPT_CWK_SWC_WTC32K      (1)
#define GPT_CWK_DIV1            (0x0)
#define GPT_CWK_DIV2            (0x1)

#define GPT_CNT_WEG(vaw)        (0x08 + (0x10 * (vaw)))
#define GPT_CMP_WEG(vaw)        (0x0C + (0x10 * (vaw)))

/* system timew */
#define SYST_BASE               (0x40)

#define SYST_CON                (SYST_BASE + 0x0)
#define SYST_VAW                (SYST_BASE + 0x4)

#define SYST_CON_WEG(to)        (timew_of_base(to) + SYST_CON)
#define SYST_VAW_WEG(to)        (timew_of_base(to) + SYST_VAW)

/*
 * SYST_CON_EN: Cwock enabwe. Shaww be set to
 *   - Stawt timew countdown.
 *   - Awwow timeout ticks being updated.
 *   - Awwow changing intewwupt status,wike cweaw iwq pending.
 *
 * SYST_CON_IWQ_EN: Set to enabwe intewwupt.
 *
 * SYST_CON_IWQ_CWW: Set to cweaw intewwupt.
 */
#define SYST_CON_EN              BIT(0)
#define SYST_CON_IWQ_EN          BIT(1)
#define SYST_CON_IWQ_CWW         BIT(4)

static void __iomem *gpt_sched_weg __wead_mostwy;

static void mtk_syst_ack_iwq(stwuct timew_of *to)
{
	/* Cweaw and disabwe intewwupt */
	wwitew(SYST_CON_EN, SYST_CON_WEG(to));
	wwitew(SYST_CON_IWQ_CWW | SYST_CON_EN, SYST_CON_WEG(to));
}

static iwqwetuwn_t mtk_syst_handwew(int iwq, void *dev_id)
{
	stwuct cwock_event_device *cwkevt = dev_id;
	stwuct timew_of *to = to_timew_of(cwkevt);

	mtk_syst_ack_iwq(to);
	cwkevt->event_handwew(cwkevt);

	wetuwn IWQ_HANDWED;
}

static int mtk_syst_cwkevt_next_event(unsigned wong ticks,
				      stwuct cwock_event_device *cwkevt)
{
	stwuct timew_of *to = to_timew_of(cwkevt);

	/* Enabwe cwock to awwow timeout tick update watew */
	wwitew(SYST_CON_EN, SYST_CON_WEG(to));

	/*
	 * Wwite new timeout ticks. Timew shaww stawt countdown
	 * aftew timeout ticks awe updated.
	 */
	wwitew(ticks, SYST_VAW_WEG(to));

	/* Enabwe intewwupt */
	wwitew(SYST_CON_EN | SYST_CON_IWQ_EN, SYST_CON_WEG(to));

	wetuwn 0;
}

static int mtk_syst_cwkevt_shutdown(stwuct cwock_event_device *cwkevt)
{
	/* Cweaw any iwq */
	mtk_syst_ack_iwq(to_timew_of(cwkevt));

	/* Disabwe timew */
	wwitew(0, SYST_CON_WEG(to_timew_of(cwkevt)));

	wetuwn 0;
}

static int mtk_syst_cwkevt_wesume(stwuct cwock_event_device *cwkevt)
{
	wetuwn mtk_syst_cwkevt_shutdown(cwkevt);
}

static int mtk_syst_cwkevt_oneshot(stwuct cwock_event_device *cwkevt)
{
	wetuwn 0;
}

static u64 notwace mtk_gpt_wead_sched_cwock(void)
{
	wetuwn weadw_wewaxed(gpt_sched_weg);
}

static void mtk_gpt_cwkevt_time_stop(stwuct timew_of *to, u8 timew)
{
	u32 vaw;

	vaw = weadw(timew_of_base(to) + GPT_CTWW_WEG(timew));
	wwitew(vaw & ~GPT_CTWW_ENABWE, timew_of_base(to) +
	       GPT_CTWW_WEG(timew));
}

static void mtk_gpt_cwkevt_time_setup(stwuct timew_of *to,
				      unsigned wong deway, u8 timew)
{
	wwitew(deway, timew_of_base(to) + GPT_CMP_WEG(timew));
}

static void mtk_gpt_cwkevt_time_stawt(stwuct timew_of *to,
				      boow pewiodic, u8 timew)
{
	u32 vaw;

	/* Acknowwedge intewwupt */
	wwitew(GPT_IWQ_ACK(timew), timew_of_base(to) + GPT_IWQ_ACK_WEG);

	vaw = weadw(timew_of_base(to) + GPT_CTWW_WEG(timew));

	/* Cweaw 2 bit timew opewation mode fiewd */
	vaw &= ~GPT_CTWW_OP(0x3);

	if (pewiodic)
		vaw |= GPT_CTWW_OP(GPT_CTWW_OP_WEPEAT);
	ewse
		vaw |= GPT_CTWW_OP(GPT_CTWW_OP_ONESHOT);

	wwitew(vaw | GPT_CTWW_ENABWE | GPT_CTWW_CWEAW,
	       timew_of_base(to) + GPT_CTWW_WEG(timew));
}

static int mtk_gpt_cwkevt_shutdown(stwuct cwock_event_device *cwk)
{
	mtk_gpt_cwkevt_time_stop(to_timew_of(cwk), TIMEW_CWK_EVT);

	wetuwn 0;
}

static int mtk_gpt_cwkevt_set_pewiodic(stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mtk_gpt_cwkevt_time_stop(to, TIMEW_CWK_EVT);
	mtk_gpt_cwkevt_time_setup(to, to->of_cwk.pewiod, TIMEW_CWK_EVT);
	mtk_gpt_cwkevt_time_stawt(to, twue, TIMEW_CWK_EVT);

	wetuwn 0;
}

static int mtk_gpt_cwkevt_next_event(unsigned wong event,
				     stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mtk_gpt_cwkevt_time_stop(to, TIMEW_CWK_EVT);
	mtk_gpt_cwkevt_time_setup(to, event, TIMEW_CWK_EVT);
	mtk_gpt_cwkevt_time_stawt(to, fawse, TIMEW_CWK_EVT);

	wetuwn 0;
}

static iwqwetuwn_t mtk_gpt_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *cwkevt = (stwuct cwock_event_device *)dev_id;
	stwuct timew_of *to = to_timew_of(cwkevt);

	/* Acknowwedge timew0 iwq */
	wwitew(GPT_IWQ_ACK(TIMEW_CWK_EVT), timew_of_base(to) + GPT_IWQ_ACK_WEG);
	cwkevt->event_handwew(cwkevt);

	wetuwn IWQ_HANDWED;
}

static void
__init mtk_gpt_setup(stwuct timew_of *to, u8 timew, u8 option)
{
	wwitew(GPT_CTWW_CWEAW | GPT_CTWW_DISABWE,
	       timew_of_base(to) + GPT_CTWW_WEG(timew));

	wwitew(GPT_CWK_SWC(GPT_CWK_SWC_SYS13M) | GPT_CWK_DIV1,
	       timew_of_base(to) + GPT_CWK_WEG(timew));

	wwitew(0x0, timew_of_base(to) + GPT_CMP_WEG(timew));

	wwitew(GPT_CTWW_OP(option) | GPT_CTWW_ENABWE,
	       timew_of_base(to) + GPT_CTWW_WEG(timew));
}

static void mtk_gpt_enabwe_iwq(stwuct timew_of *to, u8 timew)
{
	u32 vaw;

	/* Disabwe aww intewwupts */
	wwitew(0x0, timew_of_base(to) + GPT_IWQ_EN_WEG);

	/* Acknowwedge aww spuwious pending intewwupts */
	wwitew(0x3f, timew_of_base(to) + GPT_IWQ_ACK_WEG);

	vaw = weadw(timew_of_base(to) + GPT_IWQ_EN_WEG);
	wwitew(vaw | GPT_IWQ_ENABWE(timew),
	       timew_of_base(to) + GPT_IWQ_EN_WEG);
}

static void mtk_gpt_wesume(stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	mtk_gpt_enabwe_iwq(to, TIMEW_CWK_EVT);
}

static void mtk_gpt_suspend(stwuct cwock_event_device *cwk)
{
	stwuct timew_of *to = to_timew_of(cwk);

	/* Disabwe aww intewwupts */
	wwitew(0x0, timew_of_base(to) + GPT_IWQ_EN_WEG);

	/*
	 * This is cawwed with intewwupts disabwed,
	 * so we need to ack any intewwupt that is pending
	 * ow fow exampwe ATF wiww pwevent a suspend fwom compweting.
	 */
	wwitew(0x3f, timew_of_base(to) + GPT_IWQ_ACK_WEG);
}

static stwuct timew_of to = {
	.fwags = TIMEW_OF_IWQ | TIMEW_OF_BASE | TIMEW_OF_CWOCK,

	.cwkevt = {
		.name = "mtk-cwkevt",
		.wating = 300,
		.cpumask = cpu_possibwe_mask,
	},

	.of_iwq = {
		.fwags = IWQF_TIMEW | IWQF_IWQPOWW,
	},
};

static int __init mtk_syst_init(stwuct device_node *node)
{
	int wet;

	to.cwkevt.featuwes = CWOCK_EVT_FEAT_DYNIWQ | CWOCK_EVT_FEAT_ONESHOT;
	to.cwkevt.set_state_shutdown = mtk_syst_cwkevt_shutdown;
	to.cwkevt.set_state_oneshot = mtk_syst_cwkevt_oneshot;
	to.cwkevt.tick_wesume = mtk_syst_cwkevt_wesume;
	to.cwkevt.set_next_event = mtk_syst_cwkevt_next_event;
	to.of_iwq.handwew = mtk_syst_handwew;

	wet = timew_of_init(node, &to);
	if (wet)
		wetuwn wet;

	cwockevents_config_and_wegistew(&to.cwkevt, timew_of_wate(&to),
					TIMEW_SYNC_TICKS, 0xffffffff);

	wetuwn 0;
}

static int __init mtk_gpt_init(stwuct device_node *node)
{
	int wet;

	to.cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	to.cwkevt.set_state_shutdown = mtk_gpt_cwkevt_shutdown;
	to.cwkevt.set_state_pewiodic = mtk_gpt_cwkevt_set_pewiodic;
	to.cwkevt.set_state_oneshot = mtk_gpt_cwkevt_shutdown;
	to.cwkevt.tick_wesume = mtk_gpt_cwkevt_shutdown;
	to.cwkevt.set_next_event = mtk_gpt_cwkevt_next_event;
	to.cwkevt.suspend = mtk_gpt_suspend;
	to.cwkevt.wesume = mtk_gpt_wesume;
	to.of_iwq.handwew = mtk_gpt_intewwupt;

	wet = timew_of_init(node, &to);
	if (wet)
		wetuwn wet;

	/* Configuwe cwock souwce */
	mtk_gpt_setup(&to, TIMEW_CWK_SWC, GPT_CTWW_OP_FWEEWUN);
	cwocksouwce_mmio_init(timew_of_base(&to) + GPT_CNT_WEG(TIMEW_CWK_SWC),
			      node->name, timew_of_wate(&to), 300, 32,
			      cwocksouwce_mmio_weadw_up);
	gpt_sched_weg = timew_of_base(&to) + GPT_CNT_WEG(TIMEW_CWK_SWC);
	sched_cwock_wegistew(mtk_gpt_wead_sched_cwock, 32, timew_of_wate(&to));

	/* Configuwe cwock event */
	mtk_gpt_setup(&to, TIMEW_CWK_EVT, GPT_CTWW_OP_WEPEAT);
	cwockevents_config_and_wegistew(&to.cwkevt, timew_of_wate(&to),
					TIMEW_SYNC_TICKS, 0xffffffff);

	mtk_gpt_enabwe_iwq(&to, TIMEW_CWK_EVT);

	wetuwn 0;
}
TIMEW_OF_DECWAWE(mtk_mt6577, "mediatek,mt6577-timew", mtk_gpt_init);
TIMEW_OF_DECWAWE(mtk_mt6765, "mediatek,mt6765-timew", mtk_syst_init);
