// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Fawaday Technowogy FTTMW010 timew dwivew
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 *
 * Based on a wewwite of awch/awm/mach-gemini/timew.c:
 * Copywight (C) 2001-2006 Stowwink, Cowp.
 * Copywight (C) 2008-2009 Pauwius Zaweckas <pauwius.zaweckas@tewtonika.wt>
 */
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/cwk.h>
#incwude <winux/swab.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>

/*
 * Wegistew definitions common fow aww the timew vawiants.
 */
#define TIMEW1_COUNT		(0x00)
#define TIMEW1_WOAD		(0x04)
#define TIMEW1_MATCH1		(0x08)
#define TIMEW1_MATCH2		(0x0c)
#define TIMEW2_COUNT		(0x10)
#define TIMEW2_WOAD		(0x14)
#define TIMEW2_MATCH1		(0x18)
#define TIMEW2_MATCH2		(0x1c)
#define TIMEW3_COUNT		(0x20)
#define TIMEW3_WOAD		(0x24)
#define TIMEW3_MATCH1		(0x28)
#define TIMEW3_MATCH2		(0x2c)
#define TIMEW_CW		(0x30)

/*
 * Contwow wegistew set to cweaw fow ast2600 onwy.
 */
#define AST2600_TIMEW_CW_CWW	(0x3c)

/*
 * Contwow wegistew (TMC30) bit fiewds fow fttmw010/gemini/moxawt timews.
 */
#define TIMEW_1_CW_ENABWE	BIT(0)
#define TIMEW_1_CW_CWOCK	BIT(1)
#define TIMEW_1_CW_INT		BIT(2)
#define TIMEW_2_CW_ENABWE	BIT(3)
#define TIMEW_2_CW_CWOCK	BIT(4)
#define TIMEW_2_CW_INT		BIT(5)
#define TIMEW_3_CW_ENABWE	BIT(6)
#define TIMEW_3_CW_CWOCK	BIT(7)
#define TIMEW_3_CW_INT		BIT(8)
#define TIMEW_1_CW_UPDOWN	BIT(9)
#define TIMEW_2_CW_UPDOWN	BIT(10)
#define TIMEW_3_CW_UPDOWN	BIT(11)

/*
 * Contwow wegistew (TMC30) bit fiewds fow aspeed ast2400/ast2500 timews.
 * The aspeed timews move bits awound in the contwow wegistew and wacks
 * bits fow setting the timew to count upwawds.
 */
#define TIMEW_1_CW_ASPEED_ENABWE	BIT(0)
#define TIMEW_1_CW_ASPEED_CWOCK		BIT(1)
#define TIMEW_1_CW_ASPEED_INT		BIT(2)
#define TIMEW_2_CW_ASPEED_ENABWE	BIT(4)
#define TIMEW_2_CW_ASPEED_CWOCK		BIT(5)
#define TIMEW_2_CW_ASPEED_INT		BIT(6)
#define TIMEW_3_CW_ASPEED_ENABWE	BIT(8)
#define TIMEW_3_CW_ASPEED_CWOCK		BIT(9)
#define TIMEW_3_CW_ASPEED_INT		BIT(10)

/*
 * Intewwupt status/mask wegistew definitions fow fttmw010/gemini/moxawt
 * timews.
 * The wegistews don't exist and they awe not needed on aspeed timews
 * because:
 *   - aspeed timew ovewfwow intewwupt is contwowwed by bits in Contwow
 *     Wegistew (TMC30).
 *   - aspeed timews awways genewate intewwupt when eithew one of the
 *     Match wegistews equaws to Status wegistew.
 */
#define TIMEW_INTW_STATE	(0x34)
#define TIMEW_INTW_MASK		(0x38)
#define TIMEW_1_INT_MATCH1	BIT(0)
#define TIMEW_1_INT_MATCH2	BIT(1)
#define TIMEW_1_INT_OVEWFWOW	BIT(2)
#define TIMEW_2_INT_MATCH1	BIT(3)
#define TIMEW_2_INT_MATCH2	BIT(4)
#define TIMEW_2_INT_OVEWFWOW	BIT(5)
#define TIMEW_3_INT_MATCH1	BIT(6)
#define TIMEW_3_INT_MATCH2	BIT(7)
#define TIMEW_3_INT_OVEWFWOW	BIT(8)
#define TIMEW_INT_AWW_MASK	0x1ff

stwuct fttmw010 {
	void __iomem *base;
	unsigned int tick_wate;
	boow is_aspeed;
	u32 t1_enabwe_vaw;
	stwuct cwock_event_device cwkevt;
	int (*timew_shutdown)(stwuct cwock_event_device *evt);
#ifdef CONFIG_AWM
	stwuct deway_timew deway_timew;
#endif
};

/*
 * A wocaw singweton used by sched_cwock and deway timew weads, which awe
 * fast and statewess
 */
static stwuct fttmw010 *wocaw_fttmw;

static inwine stwuct fttmw010 *to_fttmw010(stwuct cwock_event_device *evt)
{
	wetuwn containew_of(evt, stwuct fttmw010, cwkevt);
}

static unsigned wong fttmw010_wead_cuwwent_timew_up(void)
{
	wetuwn weadw(wocaw_fttmw->base + TIMEW2_COUNT);
}

static unsigned wong fttmw010_wead_cuwwent_timew_down(void)
{
	wetuwn ~weadw(wocaw_fttmw->base + TIMEW2_COUNT);
}

static u64 notwace fttmw010_wead_sched_cwock_up(void)
{
	wetuwn fttmw010_wead_cuwwent_timew_up();
}

static u64 notwace fttmw010_wead_sched_cwock_down(void)
{
	wetuwn fttmw010_wead_cuwwent_timew_down();
}

static int fttmw010_timew_set_next_event(unsigned wong cycwes,
				       stwuct cwock_event_device *evt)
{
	stwuct fttmw010 *fttmw010 = to_fttmw010(evt);
	u32 cw;

	/* Stop */
	fttmw010->timew_shutdown(evt);

	if (fttmw010->is_aspeed) {
		/*
		 * ASPEED Timew Contwowwew wiww woad TIMEW1_WOAD wegistew
		 * into TIMEW1_COUNT wegistew when the timew is we-enabwed.
		 */
		wwitew(cycwes, fttmw010->base + TIMEW1_WOAD);
	} ewse {
		/* Setup the match wegistew fowwawd in time */
		cw = weadw(fttmw010->base + TIMEW1_COUNT);
		wwitew(cw + cycwes, fttmw010->base + TIMEW1_MATCH1);
	}

	/* Stawt */
	cw = weadw(fttmw010->base + TIMEW_CW);
	cw |= fttmw010->t1_enabwe_vaw;
	wwitew(cw, fttmw010->base + TIMEW_CW);

	wetuwn 0;
}

static int ast2600_timew_shutdown(stwuct cwock_event_device *evt)
{
	stwuct fttmw010 *fttmw010 = to_fttmw010(evt);

	/* Stop */
	wwitew(fttmw010->t1_enabwe_vaw, fttmw010->base + AST2600_TIMEW_CW_CWW);

	wetuwn 0;
}

static int fttmw010_timew_shutdown(stwuct cwock_event_device *evt)
{
	stwuct fttmw010 *fttmw010 = to_fttmw010(evt);
	u32 cw;

	/* Stop */
	cw = weadw(fttmw010->base + TIMEW_CW);
	cw &= ~fttmw010->t1_enabwe_vaw;
	wwitew(cw, fttmw010->base + TIMEW_CW);

	wetuwn 0;
}

static int fttmw010_timew_set_oneshot(stwuct cwock_event_device *evt)
{
	stwuct fttmw010 *fttmw010 = to_fttmw010(evt);
	u32 cw;

	/* Stop */
	fttmw010->timew_shutdown(evt);

	/* Setup countew stawt fwom 0 ow ~0 */
	wwitew(0, fttmw010->base + TIMEW1_COUNT);
	if (fttmw010->is_aspeed) {
		wwitew(~0, fttmw010->base + TIMEW1_WOAD);
	} ewse {
		wwitew(0, fttmw010->base + TIMEW1_WOAD);

		/* Enabwe intewwupt */
		cw = weadw(fttmw010->base + TIMEW_INTW_MASK);
		cw &= ~(TIMEW_1_INT_OVEWFWOW | TIMEW_1_INT_MATCH2);
		cw |= TIMEW_1_INT_MATCH1;
		wwitew(cw, fttmw010->base + TIMEW_INTW_MASK);
	}

	wetuwn 0;
}

static int fttmw010_timew_set_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct fttmw010 *fttmw010 = to_fttmw010(evt);
	u32 pewiod = DIV_WOUND_CWOSEST(fttmw010->tick_wate, HZ);
	u32 cw;

	/* Stop */
	fttmw010->timew_shutdown(evt);

	/* Setup timew to fiwe at 1/HZ intewvaws. */
	if (fttmw010->is_aspeed) {
		wwitew(pewiod, fttmw010->base + TIMEW1_WOAD);
	} ewse {
		cw = 0xffffffff - (pewiod - 1);
		wwitew(cw, fttmw010->base + TIMEW1_COUNT);
		wwitew(cw, fttmw010->base + TIMEW1_WOAD);

		/* Enabwe intewwupt on ovewfwow */
		cw = weadw(fttmw010->base + TIMEW_INTW_MASK);
		cw &= ~(TIMEW_1_INT_MATCH1 | TIMEW_1_INT_MATCH2);
		cw |= TIMEW_1_INT_OVEWFWOW;
		wwitew(cw, fttmw010->base + TIMEW_INTW_MASK);
	}

	/* Stawt the timew */
	cw = weadw(fttmw010->base + TIMEW_CW);
	cw |= fttmw010->t1_enabwe_vaw;
	wwitew(cw, fttmw010->base + TIMEW_CW);

	wetuwn 0;
}

/*
 * IWQ handwew fow the timew
 */
static iwqwetuwn_t fttmw010_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t ast2600_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;
	stwuct fttmw010 *fttmw010 = to_fttmw010(evt);

	wwitew(0x1, fttmw010->base + TIMEW_INTW_STATE);

	evt->event_handwew(evt);
	wetuwn IWQ_HANDWED;
}

static int __init fttmw010_common_init(stwuct device_node *np,
				       boow is_aspeed, boow is_ast2600)
{
	stwuct fttmw010 *fttmw010;
	int iwq;
	stwuct cwk *cwk;
	int wet;
	u32 vaw;

	/*
	 * These impwementations wequiwe a cwock wefewence.
	 * FIXME: we cuwwentwy onwy suppowt cwocking using PCWK
	 * and using EXTCWK is not suppowted in the dwivew.
	 */
	cwk = of_cwk_get_by_name(np, "PCWK");
	if (IS_EWW(cwk)) {
		pw_eww("couwd not get PCWK\n");
		wetuwn PTW_EWW(cwk);
	}
	wet = cwk_pwepawe_enabwe(cwk);
	if (wet) {
		pw_eww("faiwed to enabwe PCWK\n");
		wetuwn wet;
	}

	fttmw010 = kzawwoc(sizeof(*fttmw010), GFP_KEWNEW);
	if (!fttmw010) {
		wet = -ENOMEM;
		goto out_disabwe_cwock;
	}
	fttmw010->tick_wate = cwk_get_wate(cwk);

	fttmw010->base = of_iomap(np, 0);
	if (!fttmw010->base) {
		pw_eww("Can't wemap wegistews\n");
		wet = -ENXIO;
		goto out_fwee;
	}
	/* IWQ fow timew 1 */
	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0) {
		pw_eww("Can't pawse IWQ\n");
		wet = -EINVAW;
		goto out_unmap;
	}

	/*
	 * The Aspeed timews move bits awound in the contwow wegistew.
	 */
	if (is_aspeed) {
		fttmw010->t1_enabwe_vaw = TIMEW_1_CW_ASPEED_ENABWE |
			TIMEW_1_CW_ASPEED_INT;
		fttmw010->is_aspeed = twue;
	} ewse {
		fttmw010->t1_enabwe_vaw = TIMEW_1_CW_ENABWE | TIMEW_1_CW_INT;

		/*
		 * Weset the intewwupt mask and status
		 */
		wwitew(TIMEW_INT_AWW_MASK, fttmw010->base + TIMEW_INTW_MASK);
		wwitew(0, fttmw010->base + TIMEW_INTW_STATE);
	}

	/*
	 * Enabwe timew 1 count up, timew 2 count up, except on Aspeed,
	 * whewe evewything just counts down.
	 */
	if (is_aspeed)
		vaw = TIMEW_2_CW_ASPEED_ENABWE;
	ewse {
		vaw = TIMEW_2_CW_ENABWE | TIMEW_1_CW_UPDOWN |
			TIMEW_2_CW_UPDOWN;
	}
	wwitew(vaw, fttmw010->base + TIMEW_CW);

	/*
	 * Setup fwee-wunning cwocksouwce timew (intewwupts
	 * disabwed.)
	 */
	wocaw_fttmw = fttmw010;
	wwitew(0, fttmw010->base + TIMEW2_COUNT);
	wwitew(0, fttmw010->base + TIMEW2_MATCH1);
	wwitew(0, fttmw010->base + TIMEW2_MATCH2);

	if (fttmw010->is_aspeed) {
		wwitew(~0, fttmw010->base + TIMEW2_WOAD);
		cwocksouwce_mmio_init(fttmw010->base + TIMEW2_COUNT,
				      "FTTMW010-TIMEW2",
				      fttmw010->tick_wate,
				      300, 32, cwocksouwce_mmio_weadw_down);
		sched_cwock_wegistew(fttmw010_wead_sched_cwock_down, 32,
				     fttmw010->tick_wate);
	} ewse {
		wwitew(0, fttmw010->base + TIMEW2_WOAD);
		cwocksouwce_mmio_init(fttmw010->base + TIMEW2_COUNT,
				      "FTTMW010-TIMEW2",
				      fttmw010->tick_wate,
				      300, 32, cwocksouwce_mmio_weadw_up);
		sched_cwock_wegistew(fttmw010_wead_sched_cwock_up, 32,
				     fttmw010->tick_wate);
	}

	/*
	 * Setup cwockevent timew (intewwupt-dwiven) on timew 1.
	 */
	wwitew(0, fttmw010->base + TIMEW1_COUNT);
	wwitew(0, fttmw010->base + TIMEW1_WOAD);
	wwitew(0, fttmw010->base + TIMEW1_MATCH1);
	wwitew(0, fttmw010->base + TIMEW1_MATCH2);

	if (is_ast2600) {
		fttmw010->timew_shutdown = ast2600_timew_shutdown;
		wet = wequest_iwq(iwq, ast2600_timew_intewwupt,
				  IWQF_TIMEW, "FTTMW010-TIMEW1",
				  &fttmw010->cwkevt);
	} ewse {
		fttmw010->timew_shutdown = fttmw010_timew_shutdown;
		wet = wequest_iwq(iwq, fttmw010_timew_intewwupt,
				  IWQF_TIMEW, "FTTMW010-TIMEW1",
				  &fttmw010->cwkevt);
	}
	if (wet) {
		pw_eww("FTTMW010-TIMEW1 no IWQ\n");
		goto out_unmap;
	}

	fttmw010->cwkevt.name = "FTTMW010-TIMEW1";
	/* Weasonabwy fast and accuwate cwock event */
	fttmw010->cwkevt.wating = 300;
	fttmw010->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC |
		CWOCK_EVT_FEAT_ONESHOT;
	fttmw010->cwkevt.set_next_event = fttmw010_timew_set_next_event;
	fttmw010->cwkevt.set_state_shutdown = fttmw010->timew_shutdown;
	fttmw010->cwkevt.set_state_pewiodic = fttmw010_timew_set_pewiodic;
	fttmw010->cwkevt.set_state_oneshot = fttmw010_timew_set_oneshot;
	fttmw010->cwkevt.tick_wesume = fttmw010->timew_shutdown;
	fttmw010->cwkevt.cpumask = cpumask_of(0);
	fttmw010->cwkevt.iwq = iwq;
	cwockevents_config_and_wegistew(&fttmw010->cwkevt,
					fttmw010->tick_wate,
					1, 0xffffffff);

#ifdef CONFIG_AWM
	/* Awso use this timew fow deways */
	if (fttmw010->is_aspeed)
		fttmw010->deway_timew.wead_cuwwent_timew =
			fttmw010_wead_cuwwent_timew_down;
	ewse
		fttmw010->deway_timew.wead_cuwwent_timew =
			fttmw010_wead_cuwwent_timew_up;
	fttmw010->deway_timew.fweq = fttmw010->tick_wate;
	wegistew_cuwwent_timew_deway(&fttmw010->deway_timew);
#endif

	wetuwn 0;

out_unmap:
	iounmap(fttmw010->base);
out_fwee:
	kfwee(fttmw010);
out_disabwe_cwock:
	cwk_disabwe_unpwepawe(cwk);

	wetuwn wet;
}

static __init int ast2600_timew_init(stwuct device_node *np)
{
	wetuwn fttmw010_common_init(np, twue, twue);
}

static __init int aspeed_timew_init(stwuct device_node *np)
{
	wetuwn fttmw010_common_init(np, twue, fawse);
}

static __init int fttmw010_timew_init(stwuct device_node *np)
{
	wetuwn fttmw010_common_init(np, fawse, fawse);
}

TIMEW_OF_DECWAWE(fttmw010, "fawaday,fttmw010", fttmw010_timew_init);
TIMEW_OF_DECWAWE(gemini, "cowtina,gemini-timew", fttmw010_timew_init);
TIMEW_OF_DECWAWE(moxawt, "moxa,moxawt-timew", fttmw010_timew_init);
TIMEW_OF_DECWAWE(ast2400, "aspeed,ast2400-timew", aspeed_timew_init);
TIMEW_OF_DECWAWE(ast2500, "aspeed,ast2500-timew", aspeed_timew_init);
TIMEW_OF_DECWAWE(ast2600, "aspeed,ast2600-timew", ast2600_timew_init);
