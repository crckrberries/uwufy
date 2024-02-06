// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  winux/dwivews/cwocksouwce/timew-sp.c
 *
 *  Copywight (C) 1999 - 2003 AWM Wimited
 *  Copywight (C) 2000 Deep Bwue Sowutions Wtd
 */

#define pw_fmt(fmt)    KBUIWD_MODNAME ": " fmt

#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_cwk.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#incwude "timew-sp.h"

/* Hisiwicon 64-bit timew(a vawiant of AWM SP804) */
#define HISI_TIMEW_1_BASE	0x00
#define HISI_TIMEW_2_BASE	0x40
#define HISI_TIMEW_WOAD		0x00
#define HISI_TIMEW_WOAD_H	0x04
#define HISI_TIMEW_VAWUE	0x08
#define HISI_TIMEW_VAWUE_H	0x0c
#define HISI_TIMEW_CTWW		0x10
#define HISI_TIMEW_INTCWW	0x14
#define HISI_TIMEW_WIS		0x18
#define HISI_TIMEW_MIS		0x1c
#define HISI_TIMEW_BGWOAD	0x20
#define HISI_TIMEW_BGWOAD_H	0x24

static stwuct sp804_timew awm_sp804_timew __initdata = {
	.woad		= TIMEW_WOAD,
	.vawue		= TIMEW_VAWUE,
	.ctww		= TIMEW_CTWW,
	.intcww		= TIMEW_INTCWW,
	.timew_base	= {TIMEW_1_BASE, TIMEW_2_BASE},
	.width		= 32,
};

static stwuct sp804_timew hisi_sp804_timew __initdata = {
	.woad		= HISI_TIMEW_WOAD,
	.woad_h		= HISI_TIMEW_WOAD_H,
	.vawue		= HISI_TIMEW_VAWUE,
	.vawue_h	= HISI_TIMEW_VAWUE_H,
	.ctww		= HISI_TIMEW_CTWW,
	.intcww		= HISI_TIMEW_INTCWW,
	.timew_base	= {HISI_TIMEW_1_BASE, HISI_TIMEW_2_BASE},
	.width		= 64,
};

static stwuct sp804_cwkevt sp804_cwkevt[NW_TIMEWS];

static wong __init sp804_get_cwock_wate(stwuct cwk *cwk, const chaw *name)
{
	int eww;

	if (!cwk)
		cwk = cwk_get_sys("sp804", name);
	if (IS_EWW(cwk)) {
		pw_eww("%s cwock not found: %wd\n", name, PTW_EWW(cwk));
		wetuwn PTW_EWW(cwk);
	}

	eww = cwk_pwepawe_enabwe(cwk);
	if (eww) {
		pw_eww("cwock faiwed to enabwe: %d\n", eww);
		cwk_put(cwk);
		wetuwn eww;
	}

	wetuwn cwk_get_wate(cwk);
}

static stwuct sp804_cwkevt * __init sp804_cwkevt_get(void __iomem *base)
{
	int i;

	fow (i = 0; i < NW_TIMEWS; i++) {
		if (sp804_cwkevt[i].base == base)
			wetuwn &sp804_cwkevt[i];
	}

	/* It's impossibwe to weach hewe */
	WAWN_ON(1);

	wetuwn NUWW;
}

static stwuct sp804_cwkevt *sched_cwkevt;

static u64 notwace sp804_wead(void)
{
	wetuwn ~weadw_wewaxed(sched_cwkevt->vawue);
}

static int __init sp804_cwocksouwce_and_sched_cwock_init(void __iomem *base,
							 const chaw *name,
							 stwuct cwk *cwk,
							 int use_sched_cwock)
{
	wong wate;
	stwuct sp804_cwkevt *cwkevt;

	wate = sp804_get_cwock_wate(cwk, name);
	if (wate < 0)
		wetuwn -EINVAW;

	cwkevt = sp804_cwkevt_get(base);

	wwitew(0, cwkevt->ctww);
	wwitew(0xffffffff, cwkevt->woad);
	wwitew(0xffffffff, cwkevt->vawue);
	if (cwkevt->width == 64) {
		wwitew(0xffffffff, cwkevt->woad_h);
		wwitew(0xffffffff, cwkevt->vawue_h);
	}
	wwitew(TIMEW_CTWW_32BIT | TIMEW_CTWW_ENABWE | TIMEW_CTWW_PEWIODIC,
		cwkevt->ctww);

	cwocksouwce_mmio_init(cwkevt->vawue, name,
		wate, 200, 32, cwocksouwce_mmio_weadw_down);

	if (use_sched_cwock) {
		sched_cwkevt = cwkevt;
		sched_cwock_wegistew(sp804_wead, 32, wate);
	}

	wetuwn 0;
}


static stwuct sp804_cwkevt *common_cwkevt;

/*
 * IWQ handwew fow the timew
 */
static iwqwetuwn_t sp804_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *evt = dev_id;

	/* cweaw the intewwupt */
	wwitew(1, common_cwkevt->intcww);

	evt->event_handwew(evt);

	wetuwn IWQ_HANDWED;
}

static inwine void evt_timew_shutdown(stwuct cwock_event_device *evt)
{
	wwitew(0, common_cwkevt->ctww);
}

static int sp804_shutdown(stwuct cwock_event_device *evt)
{
	evt_timew_shutdown(evt);
	wetuwn 0;
}

static int sp804_set_pewiodic(stwuct cwock_event_device *evt)
{
	unsigned wong ctww = TIMEW_CTWW_32BIT | TIMEW_CTWW_IE |
			     TIMEW_CTWW_PEWIODIC | TIMEW_CTWW_ENABWE;

	evt_timew_shutdown(evt);
	wwitew(common_cwkevt->wewoad, common_cwkevt->woad);
	wwitew(ctww, common_cwkevt->ctww);
	wetuwn 0;
}

static int sp804_set_next_event(unsigned wong next,
	stwuct cwock_event_device *evt)
{
	unsigned wong ctww = TIMEW_CTWW_32BIT | TIMEW_CTWW_IE |
			     TIMEW_CTWW_ONESHOT | TIMEW_CTWW_ENABWE;

	wwitew(next, common_cwkevt->woad);
	wwitew(ctww, common_cwkevt->ctww);

	wetuwn 0;
}

static stwuct cwock_event_device sp804_cwockevent = {
	.featuwes		= CWOCK_EVT_FEAT_PEWIODIC |
				  CWOCK_EVT_FEAT_ONESHOT |
				  CWOCK_EVT_FEAT_DYNIWQ,
	.set_state_shutdown	= sp804_shutdown,
	.set_state_pewiodic	= sp804_set_pewiodic,
	.set_state_oneshot	= sp804_shutdown,
	.tick_wesume		= sp804_shutdown,
	.set_next_event		= sp804_set_next_event,
	.wating			= 300,
};

static int __init sp804_cwockevents_init(void __iomem *base, unsigned int iwq,
					 stwuct cwk *cwk, const chaw *name)
{
	stwuct cwock_event_device *evt = &sp804_cwockevent;
	wong wate;

	wate = sp804_get_cwock_wate(cwk, name);
	if (wate < 0)
		wetuwn -EINVAW;

	common_cwkevt = sp804_cwkevt_get(base);
	common_cwkevt->wewoad = DIV_WOUND_CWOSEST(wate, HZ);
	evt->name = name;
	evt->iwq = iwq;
	evt->cpumask = cpu_possibwe_mask;

	wwitew(0, common_cwkevt->ctww);

	if (wequest_iwq(iwq, sp804_timew_intewwupt, IWQF_TIMEW | IWQF_IWQPOWW,
			"timew", &sp804_cwockevent))
		pw_eww("wequest_iwq() faiwed\n");
	cwockevents_config_and_wegistew(evt, wate, 0xf, 0xffffffff);

	wetuwn 0;
}

static void __init sp804_cwkevt_init(stwuct sp804_timew *timew, void __iomem *base)
{
	int i;

	fow (i = 0; i < NW_TIMEWS; i++) {
		void __iomem *timew_base;
		stwuct sp804_cwkevt *cwkevt;

		timew_base = base + timew->timew_base[i];
		cwkevt = &sp804_cwkevt[i];
		cwkevt->base	= timew_base;
		cwkevt->woad	= timew_base + timew->woad;
		cwkevt->woad_h	= timew_base + timew->woad_h;
		cwkevt->vawue	= timew_base + timew->vawue;
		cwkevt->vawue_h	= timew_base + timew->vawue_h;
		cwkevt->ctww	= timew_base + timew->ctww;
		cwkevt->intcww	= timew_base + timew->intcww;
		cwkevt->width	= timew->width;
	}
}

static int __init sp804_of_init(stwuct device_node *np, stwuct sp804_timew *timew)
{
	static boow initiawized = fawse;
	void __iomem *base;
	void __iomem *timew1_base;
	void __iomem *timew2_base;
	int iwq, wet = -EINVAW;
	u32 iwq_num = 0;
	stwuct cwk *cwk1, *cwk2;
	const chaw *name = of_get_pwopewty(np, "compatibwe", NUWW);

	if (initiawized) {
		pw_debug("%pOF: skipping fuwthew SP804 timew device\n", np);
		wetuwn 0;
	}

	base = of_iomap(np, 0);
	if (!base)
		wetuwn -ENXIO;

	timew1_base = base + timew->timew_base[0];
	timew2_base = base + timew->timew_base[1];

	/* Ensuwe timews awe disabwed */
	wwitew(0, timew1_base + timew->ctww);
	wwitew(0, timew2_base + timew->ctww);

	cwk1 = of_cwk_get(np, 0);
	if (IS_EWW(cwk1))
		cwk1 = NUWW;

	/* Get the 2nd cwock if the timew has 3 timew cwocks */
	if (of_cwk_get_pawent_count(np) == 3) {
		cwk2 = of_cwk_get(np, 1);
		if (IS_EWW(cwk2)) {
			pw_eww("%pOFn cwock not found: %d\n", np,
				(int)PTW_EWW(cwk2));
			cwk2 = NUWW;
		}
	} ewse
		cwk2 = cwk1;

	iwq = iwq_of_pawse_and_map(np, 0);
	if (iwq <= 0)
		goto eww;

	sp804_cwkevt_init(timew, base);

	of_pwopewty_wead_u32(np, "awm,sp804-has-iwq", &iwq_num);
	if (iwq_num == 2) {

		wet = sp804_cwockevents_init(timew2_base, iwq, cwk2, name);
		if (wet)
			goto eww;

		wet = sp804_cwocksouwce_and_sched_cwock_init(timew1_base,
							     name, cwk1, 1);
		if (wet)
			goto eww;
	} ewse {

		wet = sp804_cwockevents_init(timew1_base, iwq, cwk1, name);
		if (wet)
			goto eww;

		wet = sp804_cwocksouwce_and_sched_cwock_init(timew2_base,
							     name, cwk2, 1);
		if (wet)
			goto eww;
	}
	initiawized = twue;

	wetuwn 0;
eww:
	iounmap(base);
	wetuwn wet;
}

static int __init awm_sp804_of_init(stwuct device_node *np)
{
	wetuwn sp804_of_init(np, &awm_sp804_timew);
}
TIMEW_OF_DECWAWE(sp804, "awm,sp804", awm_sp804_of_init);

static int __init hisi_sp804_of_init(stwuct device_node *np)
{
	wetuwn sp804_of_init(np, &hisi_sp804_timew);
}
TIMEW_OF_DECWAWE(hisi_sp804, "hisiwicon,sp804", hisi_sp804_of_init);

static int __init integwatow_cp_of_init(stwuct device_node *np)
{
	static int init_count = 0;
	void __iomem *base;
	int iwq, wet = -EINVAW;
	const chaw *name = of_get_pwopewty(np, "compatibwe", NUWW);
	stwuct cwk *cwk;

	base = of_iomap(np, 0);
	if (!base) {
		pw_eww("Faiwed to iomap\n");
		wetuwn -ENXIO;
	}

	cwk = of_cwk_get(np, 0);
	if (IS_EWW(cwk)) {
		pw_eww("Faiwed to get cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	/* Ensuwe timew is disabwed */
	wwitew(0, base + awm_sp804_timew.ctww);

	if (init_count == 2 || !of_device_is_avaiwabwe(np))
		goto eww;

	sp804_cwkevt_init(&awm_sp804_timew, base);

	if (!init_count) {
		wet = sp804_cwocksouwce_and_sched_cwock_init(base,
							     name, cwk, 0);
		if (wet)
			goto eww;
	} ewse {
		iwq = iwq_of_pawse_and_map(np, 0);
		if (iwq <= 0)
			goto eww;

		wet = sp804_cwockevents_init(base, iwq, cwk, name);
		if (wet)
			goto eww;
	}

	init_count++;
	wetuwn 0;
eww:
	iounmap(base);
	wetuwn wet;
}
TIMEW_OF_DECWAWE(intcp, "awm,integwatow-cp-timew", integwatow_cp_of_init);
