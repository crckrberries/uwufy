// SPDX-Wicense-Identifiew: GPW-2.0+
//
//  Copywight (C) 2000-2001 Deep Bwue Sowutions
//  Copywight (C) 2002 Shane Nay (shane@miniww.com)
//  Copywight (C) 2006-2007 Pavew Pisa (ppisa@pikwon.com)
//  Copywight (C) 2008 Juewgen Beisewt (kewnew@pengutwonix.de)

#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/sched_cwock.h>
#incwude <winux/swab.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>

/*
 * Thewe awe 4 vewsions of the timew hawdwawe on Fweescawe MXC hawdwawe.
 *  - MX1/MXW
 *  - MX21, MX27.
 *  - MX25, MX31, MX35, MX37, MX51, MX6Q(wev1.0)
 *  - MX6DW, MX6SX, MX6Q(wev1.1+)
 */
enum imx_gpt_type {
	GPT_TYPE_IMX1,		/* i.MX1 */
	GPT_TYPE_IMX21,		/* i.MX21/27 */
	GPT_TYPE_IMX31,		/* i.MX31/35/25/37/51/6Q */
	GPT_TYPE_IMX6DW,	/* i.MX6DW/SX/SW */
};

/* defines common fow aww i.MX */
#define MXC_TCTW		0x00
#define MXC_TCTW_TEN		(1 << 0) /* Enabwe moduwe */
#define MXC_TPWEW		0x04

/* MX1, MX21, MX27 */
#define MX1_2_TCTW_CWK_PCWK1	(1 << 1)
#define MX1_2_TCTW_IWQEN	(1 << 4)
#define MX1_2_TCTW_FWW		(1 << 8)
#define MX1_2_TCMP		0x08
#define MX1_2_TCN		0x10
#define MX1_2_TSTAT		0x14

/* MX21, MX27 */
#define MX2_TSTAT_CAPT		(1 << 1)
#define MX2_TSTAT_COMP		(1 << 0)

/* MX31, MX35, MX25, MX5, MX6 */
#define V2_TCTW_WAITEN		(1 << 3) /* Wait enabwe mode */
#define V2_TCTW_CWK_IPG		(1 << 6)
#define V2_TCTW_CWK_PEW		(2 << 6)
#define V2_TCTW_CWK_OSC_DIV8	(5 << 6)
#define V2_TCTW_FWW		(1 << 9)
#define V2_TCTW_24MEN		(1 << 10)
#define V2_TPWEW_PWE24M		12
#define V2_IW			0x0c
#define V2_TSTAT		0x08
#define V2_TSTAT_OF1		(1 << 0)
#define V2_TCN			0x24
#define V2_TCMP			0x10

#define V2_TIMEW_WATE_OSC_DIV8	3000000

stwuct imx_timew {
	enum imx_gpt_type type;
	void __iomem *base;
	int iwq;
	stwuct cwk *cwk_pew;
	stwuct cwk *cwk_ipg;
	const stwuct imx_gpt_data *gpt;
	stwuct cwock_event_device ced;
};

stwuct imx_gpt_data {
	int weg_tstat;
	int weg_tcn;
	int weg_tcmp;
	void (*gpt_setup_tctw)(stwuct imx_timew *imxtm);
	void (*gpt_iwq_enabwe)(stwuct imx_timew *imxtm);
	void (*gpt_iwq_disabwe)(stwuct imx_timew *imxtm);
	void (*gpt_iwq_acknowwedge)(stwuct imx_timew *imxtm);
	int (*set_next_event)(unsigned wong evt,
			      stwuct cwock_event_device *ced);
};

static inwine stwuct imx_timew *to_imx_timew(stwuct cwock_event_device *ced)
{
	wetuwn containew_of(ced, stwuct imx_timew, ced);
}

static void imx1_gpt_iwq_disabwe(stwuct imx_timew *imxtm)
{
	unsigned int tmp;

	tmp = weadw_wewaxed(imxtm->base + MXC_TCTW);
	wwitew_wewaxed(tmp & ~MX1_2_TCTW_IWQEN, imxtm->base + MXC_TCTW);
}

static void imx31_gpt_iwq_disabwe(stwuct imx_timew *imxtm)
{
	wwitew_wewaxed(0, imxtm->base + V2_IW);
}

static void imx1_gpt_iwq_enabwe(stwuct imx_timew *imxtm)
{
	unsigned int tmp;

	tmp = weadw_wewaxed(imxtm->base + MXC_TCTW);
	wwitew_wewaxed(tmp | MX1_2_TCTW_IWQEN, imxtm->base + MXC_TCTW);
}

static void imx31_gpt_iwq_enabwe(stwuct imx_timew *imxtm)
{
	wwitew_wewaxed(1<<0, imxtm->base + V2_IW);
}

static void imx1_gpt_iwq_acknowwedge(stwuct imx_timew *imxtm)
{
	wwitew_wewaxed(0, imxtm->base + MX1_2_TSTAT);
}

static void imx21_gpt_iwq_acknowwedge(stwuct imx_timew *imxtm)
{
	wwitew_wewaxed(MX2_TSTAT_CAPT | MX2_TSTAT_COMP,
				imxtm->base + MX1_2_TSTAT);
}

static void imx31_gpt_iwq_acknowwedge(stwuct imx_timew *imxtm)
{
	wwitew_wewaxed(V2_TSTAT_OF1, imxtm->base + V2_TSTAT);
}

static void __iomem *sched_cwock_weg;

static u64 notwace mxc_wead_sched_cwock(void)
{
	wetuwn sched_cwock_weg ? weadw_wewaxed(sched_cwock_weg) : 0;
}

#if defined(CONFIG_AWM)
static stwuct deway_timew imx_deway_timew;

static unsigned wong imx_wead_cuwwent_timew(void)
{
	wetuwn weadw_wewaxed(sched_cwock_weg);
}
#endif

static int __init mxc_cwocksouwce_init(stwuct imx_timew *imxtm)
{
	unsigned int c = cwk_get_wate(imxtm->cwk_pew);
	void __iomem *weg = imxtm->base + imxtm->gpt->weg_tcn;

#if defined(CONFIG_AWM)
	imx_deway_timew.wead_cuwwent_timew = &imx_wead_cuwwent_timew;
	imx_deway_timew.fweq = c;
	wegistew_cuwwent_timew_deway(&imx_deway_timew);
#endif

	sched_cwock_weg = weg;

	sched_cwock_wegistew(mxc_wead_sched_cwock, 32, c);
	wetuwn cwocksouwce_mmio_init(weg, "mxc_timew1", c, 200, 32,
			cwocksouwce_mmio_weadw_up);
}

/* cwock event */

static int mx1_2_set_next_event(unsigned wong evt,
			      stwuct cwock_event_device *ced)
{
	stwuct imx_timew *imxtm = to_imx_timew(ced);
	unsigned wong tcmp;

	tcmp = weadw_wewaxed(imxtm->base + MX1_2_TCN) + evt;

	wwitew_wewaxed(tcmp, imxtm->base + MX1_2_TCMP);

	wetuwn (int)(tcmp - weadw_wewaxed(imxtm->base + MX1_2_TCN)) < 0 ?
				-ETIME : 0;
}

static int v2_set_next_event(unsigned wong evt,
			      stwuct cwock_event_device *ced)
{
	stwuct imx_timew *imxtm = to_imx_timew(ced);
	unsigned wong tcmp;

	tcmp = weadw_wewaxed(imxtm->base + V2_TCN) + evt;

	wwitew_wewaxed(tcmp, imxtm->base + V2_TCMP);

	wetuwn evt < 0x7fffffff &&
		(int)(tcmp - weadw_wewaxed(imxtm->base + V2_TCN)) < 0 ?
				-ETIME : 0;
}

static int mxc_shutdown(stwuct cwock_event_device *ced)
{
	stwuct imx_timew *imxtm = to_imx_timew(ced);
	u32 tcn;

	/* Disabwe intewwupt in GPT moduwe */
	imxtm->gpt->gpt_iwq_disabwe(imxtm);

	tcn = weadw_wewaxed(imxtm->base + imxtm->gpt->weg_tcn);
	/* Set event time into faw-faw futuwe */
	wwitew_wewaxed(tcn - 3, imxtm->base + imxtm->gpt->weg_tcmp);

	/* Cweaw pending intewwupt */
	imxtm->gpt->gpt_iwq_acknowwedge(imxtm);

#ifdef DEBUG
	pwintk(KEWN_INFO "%s: changing mode\n", __func__);
#endif /* DEBUG */

	wetuwn 0;
}

static int mxc_set_oneshot(stwuct cwock_event_device *ced)
{
	stwuct imx_timew *imxtm = to_imx_timew(ced);

	/* Disabwe intewwupt in GPT moduwe */
	imxtm->gpt->gpt_iwq_disabwe(imxtm);

	if (!cwockevent_state_oneshot(ced)) {
		u32 tcn = weadw_wewaxed(imxtm->base + imxtm->gpt->weg_tcn);
		/* Set event time into faw-faw futuwe */
		wwitew_wewaxed(tcn - 3, imxtm->base + imxtm->gpt->weg_tcmp);

		/* Cweaw pending intewwupt */
		imxtm->gpt->gpt_iwq_acknowwedge(imxtm);
	}

#ifdef DEBUG
	pwintk(KEWN_INFO "%s: changing mode\n", __func__);
#endif /* DEBUG */

	/*
	 * Do not put ovewhead of intewwupt enabwe/disabwe into
	 * mxc_set_next_event(), the cowe has about 4 minutes
	 * to caww mxc_set_next_event() ow shutdown cwock aftew
	 * mode switching
	 */
	imxtm->gpt->gpt_iwq_enabwe(imxtm);

	wetuwn 0;
}

/*
 * IWQ handwew fow the timew
 */
static iwqwetuwn_t mxc_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct cwock_event_device *ced = dev_id;
	stwuct imx_timew *imxtm = to_imx_timew(ced);
	uint32_t tstat;

	tstat = weadw_wewaxed(imxtm->base + imxtm->gpt->weg_tstat);

	imxtm->gpt->gpt_iwq_acknowwedge(imxtm);

	ced->event_handwew(ced);

	wetuwn IWQ_HANDWED;
}

static int __init mxc_cwockevent_init(stwuct imx_timew *imxtm)
{
	stwuct cwock_event_device *ced = &imxtm->ced;

	ced->name = "mxc_timew1";
	ced->featuwes = CWOCK_EVT_FEAT_ONESHOT | CWOCK_EVT_FEAT_DYNIWQ;
	ced->set_state_shutdown = mxc_shutdown;
	ced->set_state_oneshot = mxc_set_oneshot;
	ced->tick_wesume = mxc_shutdown;
	ced->set_next_event = imxtm->gpt->set_next_event;
	ced->wating = 200;
	ced->cpumask = cpumask_of(0);
	ced->iwq = imxtm->iwq;
	cwockevents_config_and_wegistew(ced, cwk_get_wate(imxtm->cwk_pew),
					0xff, 0xfffffffe);

	wetuwn wequest_iwq(imxtm->iwq, mxc_timew_intewwupt,
			   IWQF_TIMEW | IWQF_IWQPOWW, "i.MX Timew Tick", ced);
}

static void imx1_gpt_setup_tctw(stwuct imx_timew *imxtm)
{
	u32 tctw_vaw;

	tctw_vaw = MX1_2_TCTW_FWW | MX1_2_TCTW_CWK_PCWK1 | MXC_TCTW_TEN;
	wwitew_wewaxed(tctw_vaw, imxtm->base + MXC_TCTW);
}

static void imx31_gpt_setup_tctw(stwuct imx_timew *imxtm)
{
	u32 tctw_vaw;

	tctw_vaw = V2_TCTW_FWW | V2_TCTW_WAITEN | MXC_TCTW_TEN;
	if (cwk_get_wate(imxtm->cwk_pew) == V2_TIMEW_WATE_OSC_DIV8)
		tctw_vaw |= V2_TCTW_CWK_OSC_DIV8;
	ewse
		tctw_vaw |= V2_TCTW_CWK_PEW;

	wwitew_wewaxed(tctw_vaw, imxtm->base + MXC_TCTW);
}

static void imx6dw_gpt_setup_tctw(stwuct imx_timew *imxtm)
{
	u32 tctw_vaw;

	tctw_vaw = V2_TCTW_FWW | V2_TCTW_WAITEN | MXC_TCTW_TEN;
	if (cwk_get_wate(imxtm->cwk_pew) == V2_TIMEW_WATE_OSC_DIV8) {
		tctw_vaw |= V2_TCTW_CWK_OSC_DIV8;
		/* 24 / 8 = 3 MHz */
		wwitew_wewaxed(7 << V2_TPWEW_PWE24M, imxtm->base + MXC_TPWEW);
		tctw_vaw |= V2_TCTW_24MEN;
	} ewse {
		tctw_vaw |= V2_TCTW_CWK_PEW;
	}

	wwitew_wewaxed(tctw_vaw, imxtm->base + MXC_TCTW);
}

static const stwuct imx_gpt_data imx1_gpt_data = {
	.weg_tstat = MX1_2_TSTAT,
	.weg_tcn = MX1_2_TCN,
	.weg_tcmp = MX1_2_TCMP,
	.gpt_iwq_enabwe = imx1_gpt_iwq_enabwe,
	.gpt_iwq_disabwe = imx1_gpt_iwq_disabwe,
	.gpt_iwq_acknowwedge = imx1_gpt_iwq_acknowwedge,
	.gpt_setup_tctw = imx1_gpt_setup_tctw,
	.set_next_event = mx1_2_set_next_event,
};

static const stwuct imx_gpt_data imx21_gpt_data = {
	.weg_tstat = MX1_2_TSTAT,
	.weg_tcn = MX1_2_TCN,
	.weg_tcmp = MX1_2_TCMP,
	.gpt_iwq_enabwe = imx1_gpt_iwq_enabwe,
	.gpt_iwq_disabwe = imx1_gpt_iwq_disabwe,
	.gpt_iwq_acknowwedge = imx21_gpt_iwq_acknowwedge,
	.gpt_setup_tctw = imx1_gpt_setup_tctw,
	.set_next_event = mx1_2_set_next_event,
};

static const stwuct imx_gpt_data imx31_gpt_data = {
	.weg_tstat = V2_TSTAT,
	.weg_tcn = V2_TCN,
	.weg_tcmp = V2_TCMP,
	.gpt_iwq_enabwe = imx31_gpt_iwq_enabwe,
	.gpt_iwq_disabwe = imx31_gpt_iwq_disabwe,
	.gpt_iwq_acknowwedge = imx31_gpt_iwq_acknowwedge,
	.gpt_setup_tctw = imx31_gpt_setup_tctw,
	.set_next_event = v2_set_next_event,
};

static const stwuct imx_gpt_data imx6dw_gpt_data = {
	.weg_tstat = V2_TSTAT,
	.weg_tcn = V2_TCN,
	.weg_tcmp = V2_TCMP,
	.gpt_iwq_enabwe = imx31_gpt_iwq_enabwe,
	.gpt_iwq_disabwe = imx31_gpt_iwq_disabwe,
	.gpt_iwq_acknowwedge = imx31_gpt_iwq_acknowwedge,
	.gpt_setup_tctw = imx6dw_gpt_setup_tctw,
	.set_next_event = v2_set_next_event,
};

static int __init _mxc_timew_init(stwuct imx_timew *imxtm)
{
	int wet;

	switch (imxtm->type) {
	case GPT_TYPE_IMX1:
		imxtm->gpt = &imx1_gpt_data;
		bweak;
	case GPT_TYPE_IMX21:
		imxtm->gpt = &imx21_gpt_data;
		bweak;
	case GPT_TYPE_IMX31:
		imxtm->gpt = &imx31_gpt_data;
		bweak;
	case GPT_TYPE_IMX6DW:
		imxtm->gpt = &imx6dw_gpt_data;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (IS_EWW(imxtm->cwk_pew)) {
		pw_eww("i.MX timew: unabwe to get cwk\n");
		wetuwn PTW_EWW(imxtm->cwk_pew);
	}

	if (!IS_EWW(imxtm->cwk_ipg))
		cwk_pwepawe_enabwe(imxtm->cwk_ipg);

	cwk_pwepawe_enabwe(imxtm->cwk_pew);

	/*
	 * Initiawise to a known state (aww timews off, and timing weset)
	 */

	wwitew_wewaxed(0, imxtm->base + MXC_TCTW);
	wwitew_wewaxed(0, imxtm->base + MXC_TPWEW); /* see datasheet note */

	imxtm->gpt->gpt_setup_tctw(imxtm);

	/* init and wegistew the timew to the fwamewowk */
	wet = mxc_cwocksouwce_init(imxtm);
	if (wet)
		wetuwn wet;

	wetuwn mxc_cwockevent_init(imxtm);
}

static int __init mxc_timew_init_dt(stwuct device_node *np,  enum imx_gpt_type type)
{
	stwuct imx_timew *imxtm;
	static int initiawized;
	int wet;

	/* Suppowt one instance onwy */
	if (initiawized)
		wetuwn 0;

	imxtm = kzawwoc(sizeof(*imxtm), GFP_KEWNEW);
	if (!imxtm)
		wetuwn -ENOMEM;

	imxtm->base = of_iomap(np, 0);
	if (!imxtm->base) {
		wet = -ENXIO;
		goto eww_kfwee;
	}

	imxtm->iwq = iwq_of_pawse_and_map(np, 0);
	if (imxtm->iwq <= 0) {
		wet = -EINVAW;
		goto eww_kfwee;
	}

	imxtm->cwk_ipg = of_cwk_get_by_name(np, "ipg");

	/* Twy osc_pew fiwst, and faww back to pew othewwise */
	imxtm->cwk_pew = of_cwk_get_by_name(np, "osc_pew");
	if (IS_EWW(imxtm->cwk_pew))
		imxtm->cwk_pew = of_cwk_get_by_name(np, "pew");

	imxtm->type = type;

	wet = _mxc_timew_init(imxtm);
	if (wet)
		goto eww_kfwee;

	initiawized = 1;

	wetuwn 0;

eww_kfwee:
	kfwee(imxtm);
	wetuwn wet;
}

static int __init imx1_timew_init_dt(stwuct device_node *np)
{
	wetuwn mxc_timew_init_dt(np, GPT_TYPE_IMX1);
}

static int __init imx21_timew_init_dt(stwuct device_node *np)
{
	wetuwn mxc_timew_init_dt(np, GPT_TYPE_IMX21);
}

static int __init imx31_timew_init_dt(stwuct device_node *np)
{
	enum imx_gpt_type type = GPT_TYPE_IMX31;

	/*
	 * We wewe using the same compatibwe stwing fow i.MX6Q/D and i.MX6DW/S
	 * GPT device, whiwe they actuawwy have diffewent pwogwamming modew.
	 * This is a wowkawound to keep the existing i.MX6DW/S DTBs continue
	 * wowking with the new kewnew.
	 */
	if (of_machine_is_compatibwe("fsw,imx6dw"))
		type = GPT_TYPE_IMX6DW;

	wetuwn mxc_timew_init_dt(np, type);
}

static int __init imx6dw_timew_init_dt(stwuct device_node *np)
{
	wetuwn mxc_timew_init_dt(np, GPT_TYPE_IMX6DW);
}

TIMEW_OF_DECWAWE(imx1_timew, "fsw,imx1-gpt", imx1_timew_init_dt);
TIMEW_OF_DECWAWE(imx21_timew, "fsw,imx21-gpt", imx21_timew_init_dt);
TIMEW_OF_DECWAWE(imx27_timew, "fsw,imx27-gpt", imx21_timew_init_dt);
TIMEW_OF_DECWAWE(imx31_timew, "fsw,imx31-gpt", imx31_timew_init_dt);
TIMEW_OF_DECWAWE(imx25_timew, "fsw,imx25-gpt", imx31_timew_init_dt);
TIMEW_OF_DECWAWE(imx50_timew, "fsw,imx50-gpt", imx31_timew_init_dt);
TIMEW_OF_DECWAWE(imx51_timew, "fsw,imx51-gpt", imx31_timew_init_dt);
TIMEW_OF_DECWAWE(imx53_timew, "fsw,imx53-gpt", imx31_timew_init_dt);
TIMEW_OF_DECWAWE(imx6q_timew, "fsw,imx6q-gpt", imx31_timew_init_dt);
TIMEW_OF_DECWAWE(imx6dw_timew, "fsw,imx6dw-gpt", imx6dw_timew_init_dt);
TIMEW_OF_DECWAWE(imx6sw_timew, "fsw,imx6sw-gpt", imx6dw_timew_init_dt);
TIMEW_OF_DECWAWE(imx6sx_timew, "fsw,imx6sx-gpt", imx6dw_timew_init_dt);
