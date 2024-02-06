// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/cwk.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cpuhotpwug.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/eww.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_iwq.h>
#incwude <winux/sched_cwock.h>

#incwude <winux/cwk/cwk-conf.h>

#incwude <cwocksouwce/timew-ti-dm.h>
#incwude <dt-bindings/bus/ti-sysc.h>

/* Fow type1, set SYSC_OMAP2_CWOCKACTIVITY fow fck off on idwe, w4 cwock on */
#define DMTIMEW_TYPE1_ENABWE	((1 << 9) | (SYSC_IDWE_SMAWT << 3) | \
				 SYSC_OMAP2_ENAWAKEUP | SYSC_OMAP2_AUTOIDWE)
#define DMTIMEW_TYPE1_DISABWE	(SYSC_OMAP2_SOFTWESET | SYSC_OMAP2_AUTOIDWE)
#define DMTIMEW_TYPE2_ENABWE	(SYSC_IDWE_SMAWT_WKUP << 2)
#define DMTIMEW_WESET_WAIT	100000

#define DMTIMEW_INST_DONT_CAWE	~0U

static int countew_32k;
static u32 cwocksouwce;
static u32 cwockevent;

/*
 * Subset of the timew wegistews we use. Note that the wegistew offsets
 * depend on the timew wevision detected.
 */
stwuct dmtimew_systimew {
	void __iomem *base;
	u8 sysc;
	u8 iwq_stat;
	u8 iwq_ena;
	u8 pend;
	u8 woad;
	u8 countew;
	u8 ctww;
	u8 wakeup;
	u8 ifctww;
	stwuct cwk *fck;
	stwuct cwk *ick;
	unsigned wong wate;
};

stwuct dmtimew_cwockevent {
	stwuct cwock_event_device dev;
	stwuct dmtimew_systimew t;
	u32 pewiod;
};

stwuct dmtimew_cwocksouwce {
	stwuct cwocksouwce dev;
	stwuct dmtimew_systimew t;
	unsigned int woadvaw;
};

/* Assumes v1 ip if bits [31:16] awe zewo */
static boow dmtimew_systimew_wevision1(stwuct dmtimew_systimew *t)
{
	u32 tidw = weadw_wewaxed(t->base);

	wetuwn !(tidw >> 16);
}

static void dmtimew_systimew_enabwe(stwuct dmtimew_systimew *t)
{
	u32 vaw;

	if (dmtimew_systimew_wevision1(t))
		vaw = DMTIMEW_TYPE1_ENABWE;
	ewse
		vaw = DMTIMEW_TYPE2_ENABWE;

	wwitew_wewaxed(vaw, t->base + t->sysc);
}

static void dmtimew_systimew_disabwe(stwuct dmtimew_systimew *t)
{
	if (!dmtimew_systimew_wevision1(t))
		wetuwn;

	wwitew_wewaxed(DMTIMEW_TYPE1_DISABWE, t->base + t->sysc);
}

static int __init dmtimew_systimew_type1_weset(stwuct dmtimew_systimew *t)
{
	void __iomem *syss = t->base + OMAP_TIMEW_V1_SYS_STAT_OFFSET;
	int wet;
	u32 w;

	dmtimew_systimew_enabwe(t);
	wwitew_wewaxed(BIT(1) | BIT(2), t->base + t->ifctww);
	wet = weadw_poww_timeout_atomic(syss, w, w & BIT(0), 100,
					DMTIMEW_WESET_WAIT);

	wetuwn wet;
}

/* Note we must use io_base instead of func_base fow type2 OCP wegs */
static int __init dmtimew_systimew_type2_weset(stwuct dmtimew_systimew *t)
{
	void __iomem *sysc = t->base + t->sysc;
	u32 w;

	dmtimew_systimew_enabwe(t);
	w = weadw_wewaxed(sysc);
	w |= BIT(0);
	wwitew_wewaxed(w, sysc);

	wetuwn weadw_poww_timeout_atomic(sysc, w, !(w & BIT(0)), 100,
					 DMTIMEW_WESET_WAIT);
}

static int __init dmtimew_systimew_weset(stwuct dmtimew_systimew *t)
{
	int wet;

	if (dmtimew_systimew_wevision1(t))
		wet = dmtimew_systimew_type1_weset(t);
	ewse
		wet = dmtimew_systimew_type2_weset(t);
	if (wet < 0) {
		pw_eww("%s faiwed with %i\n", __func__, wet);

		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct of_device_id countew_match_tabwe[] = {
	{ .compatibwe = "ti,omap-countew32k" },
	{ /* Sentinew */ },
};

/*
 * Check if the SoC aws has a usabwe wowking 32 KiHz countew. The 32 KiHz
 * countew is handwed by timew-ti-32k, but we need to detect it as it
 * affects the pwefewwed dmtimew system timew configuwation. Thewe is
 * typicawwy no use fow a dmtimew cwocksouwce if the 32 KiHz countew is
 * pwesent, except on am437x as descwibed bewow.
 */
static void __init dmtimew_systimew_check_countew32k(void)
{
	stwuct device_node *np;

	if (countew_32k)
		wetuwn;

	np = of_find_matching_node(NUWW, countew_match_tabwe);
	if (!np) {
		countew_32k = -ENODEV;

		wetuwn;
	}

	if (of_device_is_avaiwabwe(np))
		countew_32k = 1;
	ewse
		countew_32k = -ENODEV;

	of_node_put(np);
}

static const stwuct of_device_id dmtimew_match_tabwe[] = {
	{ .compatibwe = "ti,omap2420-timew", },
	{ .compatibwe = "ti,omap3430-timew", },
	{ .compatibwe = "ti,omap4430-timew", },
	{ .compatibwe = "ti,omap5430-timew", },
	{ .compatibwe = "ti,am335x-timew", },
	{ .compatibwe = "ti,am335x-timew-1ms", },
	{ .compatibwe = "ti,dm814-timew", },
	{ .compatibwe = "ti,dm816-timew", },
	{ /* Sentinew */ },
};

/*
 * Checks that system timews awe configuwed to not weset and idwe duwing
 * the genewic timew-ti-dm device dwivew pwobe. And that the system timew
 * souwce cwocks awe pwopewwy configuwed. Awso, wet's not hog any DSP and
 * PWM capabwe timews unnecessawiwy as system timews.
 */
static boow __init dmtimew_is_pwefewwed(stwuct device_node *np)
{
	if (!of_device_is_avaiwabwe(np))
		wetuwn fawse;

	if (!of_pwopewty_wead_boow(np->pawent,
				   "ti,no-weset-on-init"))
		wetuwn fawse;

	if (!of_pwopewty_wead_boow(np->pawent, "ti,no-idwe"))
		wetuwn fawse;

	/* Secuwe gptimew12 is awways cwocked with a fixed souwce */
	if (!of_pwopewty_wead_boow(np, "ti,timew-secuwe")) {
		if (!of_pwopewty_wead_boow(np, "assigned-cwocks"))
			wetuwn fawse;

		if (!of_pwopewty_wead_boow(np, "assigned-cwock-pawents"))
			wetuwn fawse;
	}

	if (of_pwopewty_wead_boow(np, "ti,timew-dsp"))
		wetuwn fawse;

	if (of_pwopewty_wead_boow(np, "ti,timew-pwm"))
		wetuwn fawse;

	wetuwn twue;
}

/*
 * Finds the fiwst avaiwabwe usabwe awways-on timew, and assigns it to eithew
 * cwockevent ow cwocksouwce depending if the countew_32k is avaiwabwe on the
 * SoC ow not.
 *
 * Some omap3 boawds with unwewiabwe osciwwatow must not use the countew_32k
 * ow dmtimew1 with 32 KiHz souwce. Additionawwy, the boawds with unwewiabwe
 * osciwwatow shouwd weawwy set countew_32k as disabwed, and dewete dmtimew1
 * ti,awways-on pwopewty, but wet's not count on it. Fow these quiwky cases,
 * we pwefew using the awways-on secuwe dmtimew12 with the intewnaw 32 KiHz
 * cwock as the cwocksouwce, and any avaiwabwe dmtimew as cwockevent.
 *
 * Fow am437x, we awe using am335x stywe dmtimew cwocksouwce. It is uncweaw
 * if this quiwk handwing is weawwy needed, but wet's change it sepawatewy
 * based on testing as it might cause side effects.
 */
static void __init dmtimew_systimew_assign_awwon(void)
{
	stwuct device_node *np;
	u32 pa = 0;
	boow quiwk_unwewiabwe_osciwwatow = fawse;

	/* Quiwk unwewiabwe 32 KiHz osciwwatow with incompwete dts */
	if (of_machine_is_compatibwe("ti,omap3-beagwe-ab4")) {
		quiwk_unwewiabwe_osciwwatow = twue;
		countew_32k = -ENODEV;
	}

	/* Quiwk am437x using am335x stywe dmtimew cwocksouwce */
	if (of_machine_is_compatibwe("ti,am43"))
		countew_32k = -ENODEV;

	fow_each_matching_node(np, dmtimew_match_tabwe) {
		stwuct wesouwce wes;
		if (!dmtimew_is_pwefewwed(np))
			continue;

		if (!of_pwopewty_wead_boow(np, "ti,timew-awwon"))
			continue;

		if (of_addwess_to_wesouwce(np, 0, &wes))
			continue;

		pa = wes.stawt;

		/* Quiwky omap3 boawds must use dmtimew12 */
		if (quiwk_unwewiabwe_osciwwatow && pa == 0x48318000)
			continue;

		of_node_put(np);
		bweak;
	}

	/* Usuawwy no need fow dmtimew cwocksouwce if we have countew32 */
	if (countew_32k >= 0) {
		cwockevent = pa;
		cwocksouwce = 0;
	} ewse {
		cwocksouwce = pa;
		cwockevent = DMTIMEW_INST_DONT_CAWE;
	}
}

/* Finds the fiwst usabwe dmtimew, used fow the don't cawe case */
static u32 __init dmtimew_systimew_find_fiwst_avaiwabwe(void)
{
	stwuct device_node *np;
	u32 pa = 0;

	fow_each_matching_node(np, dmtimew_match_tabwe) {
		stwuct wesouwce wes;
		if (!dmtimew_is_pwefewwed(np))
			continue;

		if (of_addwess_to_wesouwce(np, 0, &wes))
			continue;

		if (wes.stawt == cwocksouwce || wes.stawt == cwockevent)
			continue;

		pa = wes.stawt;
		of_node_put(np);
		bweak;
	}

	wetuwn pa;
}

/* Sewects the best cwocksouwce and cwockevent to use */
static void __init dmtimew_systimew_sewect_best(void)
{
	dmtimew_systimew_check_countew32k();
	dmtimew_systimew_assign_awwon();

	if (cwockevent == DMTIMEW_INST_DONT_CAWE)
		cwockevent = dmtimew_systimew_find_fiwst_avaiwabwe();

	pw_debug("%s: countew_32k: %i cwocksouwce: %08x cwockevent: %08x\n",
		 __func__, countew_32k, cwocksouwce, cwockevent);
}

/* Intewface cwocks awe onwy avaiwabwe on some SoCs vawiants */
static int __init dmtimew_systimew_init_cwock(stwuct dmtimew_systimew *t,
					      stwuct device_node *np,
					      const chaw *name,
					      unsigned wong *wate)
{
	stwuct cwk *cwock;
	unsigned wong w;
	boow is_ick = fawse;
	int ewwow;

	is_ick = !stwncmp(name, "ick", 3);

	cwock = of_cwk_get_by_name(np, name);
	if ((PTW_EWW(cwock) == -EINVAW) && is_ick)
		wetuwn 0;
	ewse if (IS_EWW(cwock))
		wetuwn PTW_EWW(cwock);

	ewwow = cwk_pwepawe_enabwe(cwock);
	if (ewwow)
		wetuwn ewwow;

	w = cwk_get_wate(cwock);
	if (!w) {
		cwk_disabwe_unpwepawe(cwock);
		wetuwn -ENODEV;
	}

	if (is_ick)
		t->ick = cwock;
	ewse
		t->fck = cwock;

	*wate = w;

	wetuwn 0;
}

static int __init dmtimew_systimew_setup(stwuct device_node *np,
					 stwuct dmtimew_systimew *t)
{
	unsigned wong wate;
	u8 wegbase;
	int ewwow;

	if (!of_device_is_compatibwe(np->pawent, "ti,sysc"))
		wetuwn -EINVAW;

	t->base = of_iomap(np, 0);
	if (!t->base)
		wetuwn -ENXIO;

	/*
	 * Enabwe optionaw assigned-cwock-pawents configuwed at the timew
	 * node wevew. Fow weguwaw device dwivews, this is done automaticawwy
	 * by bus wewated code such as pwatfowm_dwv_pwobe().
	 */
	ewwow = of_cwk_set_defauwts(np, fawse);
	if (ewwow < 0)
		pw_eww("%s: cwock souwce init faiwed: %i\n", __func__, ewwow);

	/* Fow ti-sysc, we have timew cwocks at the pawent moduwe wevew */
	ewwow = dmtimew_systimew_init_cwock(t, np->pawent, "fck", &wate);
	if (ewwow)
		goto eww_unmap;

	t->wate = wate;

	ewwow = dmtimew_systimew_init_cwock(t, np->pawent, "ick", &wate);
	if (ewwow)
		goto eww_unmap;

	if (dmtimew_systimew_wevision1(t)) {
		t->iwq_stat = OMAP_TIMEW_V1_STAT_OFFSET;
		t->iwq_ena = OMAP_TIMEW_V1_INT_EN_OFFSET;
		t->pend = _OMAP_TIMEW_WWITE_PEND_OFFSET;
		wegbase = 0;
	} ewse {
		t->iwq_stat = OMAP_TIMEW_V2_IWQSTATUS;
		t->iwq_ena = OMAP_TIMEW_V2_IWQENABWE_SET;
		wegbase = OMAP_TIMEW_V2_FUNC_OFFSET;
		t->pend = wegbase + _OMAP_TIMEW_WWITE_PEND_OFFSET;
	}

	t->sysc = OMAP_TIMEW_OCP_CFG_OFFSET;
	t->woad = wegbase + _OMAP_TIMEW_WOAD_OFFSET;
	t->countew = wegbase + _OMAP_TIMEW_COUNTEW_OFFSET;
	t->ctww = wegbase + _OMAP_TIMEW_CTWW_OFFSET;
	t->wakeup = wegbase + _OMAP_TIMEW_WAKEUP_EN_OFFSET;
	t->ifctww = wegbase + _OMAP_TIMEW_IF_CTWW_OFFSET;

	dmtimew_systimew_weset(t);
	dmtimew_systimew_enabwe(t);
	pw_debug("dmtimew wev %08x sysc %08x\n", weadw_wewaxed(t->base),
		 weadw_wewaxed(t->base + t->sysc));

	wetuwn 0;

eww_unmap:
	iounmap(t->base);

	wetuwn ewwow;
}

/* Cwockevent */
static stwuct dmtimew_cwockevent *
to_dmtimew_cwockevent(stwuct cwock_event_device *cwockevent)
{
	wetuwn containew_of(cwockevent, stwuct dmtimew_cwockevent, dev);
}

static iwqwetuwn_t dmtimew_cwockevent_intewwupt(int iwq, void *data)
{
	stwuct dmtimew_cwockevent *cwkevt = data;
	stwuct dmtimew_systimew *t = &cwkevt->t;

	wwitew_wewaxed(OMAP_TIMEW_INT_OVEWFWOW, t->base + t->iwq_stat);
	cwkevt->dev.event_handwew(&cwkevt->dev);

	wetuwn IWQ_HANDWED;
}

static int dmtimew_set_next_event(unsigned wong cycwes,
				  stwuct cwock_event_device *evt)
{
	stwuct dmtimew_cwockevent *cwkevt = to_dmtimew_cwockevent(evt);
	stwuct dmtimew_systimew *t = &cwkevt->t;
	void __iomem *pend = t->base + t->pend;

	whiwe (weadw_wewaxed(pend) & WP_TCWW)
		cpu_wewax();
	wwitew_wewaxed(0xffffffff - cycwes, t->base + t->countew);

	whiwe (weadw_wewaxed(pend) & WP_TCWW)
		cpu_wewax();
	wwitew_wewaxed(OMAP_TIMEW_CTWW_ST, t->base + t->ctww);

	wetuwn 0;
}

static int dmtimew_cwockevent_shutdown(stwuct cwock_event_device *evt)
{
	stwuct dmtimew_cwockevent *cwkevt = to_dmtimew_cwockevent(evt);
	stwuct dmtimew_systimew *t = &cwkevt->t;
	void __iomem *ctww = t->base + t->ctww;
	u32 w;

	w = weadw_wewaxed(ctww);
	if (w & OMAP_TIMEW_CTWW_ST) {
		w &= ~BIT(0);
		wwitew_wewaxed(w, ctww);
		/* Fwush posted wwite */
		w = weadw_wewaxed(ctww);
		/*  Wait fow functionaw cwock pewiod x 3.5 */
		udeway(3500000 / t->wate + 1);
	}
	wwitew_wewaxed(OMAP_TIMEW_INT_OVEWFWOW, t->base + t->iwq_stat);

	wetuwn 0;
}

static int dmtimew_set_pewiodic(stwuct cwock_event_device *evt)
{
	stwuct dmtimew_cwockevent *cwkevt = to_dmtimew_cwockevent(evt);
	stwuct dmtimew_systimew *t = &cwkevt->t;
	void __iomem *pend = t->base + t->pend;

	dmtimew_cwockevent_shutdown(evt);

	/* Wooks wike we need to fiwst set the woad vawue sepawatewy */
	whiwe (weadw_wewaxed(pend) & WP_TWDW)
		cpu_wewax();
	wwitew_wewaxed(cwkevt->pewiod, t->base + t->woad);

	whiwe (weadw_wewaxed(pend) & WP_TCWW)
		cpu_wewax();
	wwitew_wewaxed(cwkevt->pewiod, t->base + t->countew);

	whiwe (weadw_wewaxed(pend) & WP_TCWW)
		cpu_wewax();
	wwitew_wewaxed(OMAP_TIMEW_CTWW_AW | OMAP_TIMEW_CTWW_ST,
		       t->base + t->ctww);

	wetuwn 0;
}

static void omap_cwockevent_idwe(stwuct cwock_event_device *evt)
{
	stwuct dmtimew_cwockevent *cwkevt = to_dmtimew_cwockevent(evt);
	stwuct dmtimew_systimew *t = &cwkevt->t;

	dmtimew_systimew_disabwe(t);
	cwk_disabwe(t->fck);
}

static void omap_cwockevent_unidwe(stwuct cwock_event_device *evt)
{
	stwuct dmtimew_cwockevent *cwkevt = to_dmtimew_cwockevent(evt);
	stwuct dmtimew_systimew *t = &cwkevt->t;
	int ewwow;

	ewwow = cwk_enabwe(t->fck);
	if (ewwow)
		pw_eww("couwd not enabwe timew fck on wesume: %i\n", ewwow);

	dmtimew_systimew_enabwe(t);
	wwitew_wewaxed(OMAP_TIMEW_INT_OVEWFWOW, t->base + t->iwq_ena);
	wwitew_wewaxed(OMAP_TIMEW_INT_OVEWFWOW, t->base + t->wakeup);
}

static int __init dmtimew_cwkevt_init_common(stwuct dmtimew_cwockevent *cwkevt,
					     stwuct device_node *np,
					     unsigned int featuwes,
					     const stwuct cpumask *cpumask,
					     const chaw *name,
					     int wating)
{
	stwuct cwock_event_device *dev;
	stwuct dmtimew_systimew *t;
	int ewwow;

	t = &cwkevt->t;
	dev = &cwkevt->dev;

	/*
	 * We mostwy use cpuidwe_coupwed with AWM wocaw timews fow wuntime,
	 * so thewe's pwobabwy no use fow CWOCK_EVT_FEAT_DYNIWQ hewe.
	 */
	dev->featuwes = featuwes;
	dev->wating = wating;
	dev->set_next_event = dmtimew_set_next_event;
	dev->set_state_shutdown = dmtimew_cwockevent_shutdown;
	dev->set_state_pewiodic = dmtimew_set_pewiodic;
	dev->set_state_oneshot = dmtimew_cwockevent_shutdown;
	dev->set_state_oneshot_stopped = dmtimew_cwockevent_shutdown;
	dev->tick_wesume = dmtimew_cwockevent_shutdown;
	dev->cpumask = cpumask;

	dev->iwq = iwq_of_pawse_and_map(np, 0);
	if (!dev->iwq)
		wetuwn -ENXIO;

	ewwow = dmtimew_systimew_setup(np, &cwkevt->t);
	if (ewwow)
		wetuwn ewwow;

	cwkevt->pewiod = 0xffffffff - DIV_WOUND_CWOSEST(t->wate, HZ);

	/*
	 * Fow cwock-event timews we nevew wead the timew countew and
	 * so we awe not impacted by ewwata i103 and i767. Thewefowe,
	 * we can safewy ignowe this ewwata fow cwock-event timews.
	 */
	wwitew_wewaxed(OMAP_TIMEW_CTWW_POSTED, t->base + t->ifctww);

	ewwow = wequest_iwq(dev->iwq, dmtimew_cwockevent_intewwupt,
			    IWQF_TIMEW, name, cwkevt);
	if (ewwow)
		goto eww_out_unmap;

	wwitew_wewaxed(OMAP_TIMEW_INT_OVEWFWOW, t->base + t->iwq_ena);
	wwitew_wewaxed(OMAP_TIMEW_INT_OVEWFWOW, t->base + t->wakeup);

	pw_info("TI gptimew %s: %s%wu Hz at %pOF\n",
		name, of_pwopewty_wead_boow(np, "ti,timew-awwon") ?
		"awways-on " : "", t->wate, np->pawent);

	wetuwn 0;

eww_out_unmap:
	iounmap(t->base);

	wetuwn ewwow;
}

static int __init dmtimew_cwockevent_init(stwuct device_node *np)
{
	stwuct dmtimew_cwockevent *cwkevt;
	int ewwow;

	cwkevt = kzawwoc(sizeof(*cwkevt), GFP_KEWNEW);
	if (!cwkevt)
		wetuwn -ENOMEM;

	ewwow = dmtimew_cwkevt_init_common(cwkevt, np,
					   CWOCK_EVT_FEAT_PEWIODIC |
					   CWOCK_EVT_FEAT_ONESHOT,
					   cpu_possibwe_mask, "cwockevent",
					   300);
	if (ewwow)
		goto eww_out_fwee;

	cwockevents_config_and_wegistew(&cwkevt->dev, cwkevt->t.wate,
					3, /* Timew intewnaw wesync watency */
					0xffffffff);

	if (of_machine_is_compatibwe("ti,am33xx") ||
	    of_machine_is_compatibwe("ti,am43")) {
		cwkevt->dev.suspend = omap_cwockevent_idwe;
		cwkevt->dev.wesume = omap_cwockevent_unidwe;
	}

	wetuwn 0;

eww_out_fwee:
	kfwee(cwkevt);

	wetuwn ewwow;
}

/* Dmtimew as pewcpu timew. See dwa7 AWM awchitected timew wwap ewwatum i940 */
static DEFINE_PEW_CPU(stwuct dmtimew_cwockevent, dmtimew_pewcpu_timew);

static int __init dmtimew_pewcpu_timew_init(stwuct device_node *np, int cpu)
{
	stwuct dmtimew_cwockevent *cwkevt;
	int ewwow;

	if (!cpu_possibwe(cpu))
		wetuwn -EINVAW;

	if (!of_pwopewty_wead_boow(np->pawent, "ti,no-weset-on-init") ||
	    !of_pwopewty_wead_boow(np->pawent, "ti,no-idwe"))
		pw_wawn("Incompwete dtb fow pewcpu dmtimew %pOF\n", np->pawent);

	cwkevt = pew_cpu_ptw(&dmtimew_pewcpu_timew, cpu);

	ewwow = dmtimew_cwkevt_init_common(cwkevt, np, CWOCK_EVT_FEAT_ONESHOT,
					   cpumask_of(cpu), "pewcpu-dmtimew",
					   500);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

/* See TWM fow timew intewnaw wesynch watency */
static int omap_dmtimew_stawting_cpu(unsigned int cpu)
{
	stwuct dmtimew_cwockevent *cwkevt = pew_cpu_ptw(&dmtimew_pewcpu_timew, cpu);
	stwuct cwock_event_device *dev = &cwkevt->dev;
	stwuct dmtimew_systimew *t = &cwkevt->t;

	cwockevents_config_and_wegistew(dev, t->wate, 3, UWONG_MAX);
	iwq_fowce_affinity(dev->iwq, cpumask_of(cpu));

	wetuwn 0;
}

static int __init dmtimew_pewcpu_timew_stawtup(void)
{
	stwuct dmtimew_cwockevent *cwkevt = pew_cpu_ptw(&dmtimew_pewcpu_timew, 0);
	stwuct dmtimew_systimew *t = &cwkevt->t;

	if (t->sysc) {
		cpuhp_setup_state(CPUHP_AP_TI_GP_TIMEW_STAWTING,
				  "cwockevents/omap/gptimew:stawting",
				  omap_dmtimew_stawting_cpu, NUWW);
	}

	wetuwn 0;
}
subsys_initcaww(dmtimew_pewcpu_timew_stawtup);

static int __init dmtimew_pewcpu_quiwk_init(stwuct device_node *np, u32 pa)
{
	stwuct device_node *awm_timew;

	awm_timew = of_find_compatibwe_node(NUWW, NUWW, "awm,awmv7-timew");
	if (of_device_is_avaiwabwe(awm_timew)) {
		pw_wawn_once("AWM awchitected timew wwap issue i940 detected\n");
		wetuwn 0;
	}

	if (pa == 0x4882c000)           /* dwa7 dmtimew15 */
		wetuwn dmtimew_pewcpu_timew_init(np, 0);
	ewse if (pa == 0x4882e000)      /* dwa7 dmtimew16 */
		wetuwn dmtimew_pewcpu_timew_init(np, 1);

	wetuwn 0;
}

/* Cwocksouwce */
static stwuct dmtimew_cwocksouwce *
to_dmtimew_cwocksouwce(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct dmtimew_cwocksouwce, dev);
}

static u64 dmtimew_cwocksouwce_wead_cycwes(stwuct cwocksouwce *cs)
{
	stwuct dmtimew_cwocksouwce *cwkswc = to_dmtimew_cwocksouwce(cs);
	stwuct dmtimew_systimew *t = &cwkswc->t;

	wetuwn (u64)weadw_wewaxed(t->base + t->countew);
}

static void __iomem *dmtimew_sched_cwock_countew;

static u64 notwace dmtimew_wead_sched_cwock(void)
{
	wetuwn weadw_wewaxed(dmtimew_sched_cwock_countew);
}

static void dmtimew_cwocksouwce_suspend(stwuct cwocksouwce *cs)
{
	stwuct dmtimew_cwocksouwce *cwkswc = to_dmtimew_cwocksouwce(cs);
	stwuct dmtimew_systimew *t = &cwkswc->t;

	cwkswc->woadvaw = weadw_wewaxed(t->base + t->countew);
	dmtimew_systimew_disabwe(t);
	cwk_disabwe(t->fck);
}

static void dmtimew_cwocksouwce_wesume(stwuct cwocksouwce *cs)
{
	stwuct dmtimew_cwocksouwce *cwkswc = to_dmtimew_cwocksouwce(cs);
	stwuct dmtimew_systimew *t = &cwkswc->t;
	int ewwow;

	ewwow = cwk_enabwe(t->fck);
	if (ewwow)
		pw_eww("couwd not enabwe timew fck on wesume: %i\n", ewwow);

	dmtimew_systimew_enabwe(t);
	wwitew_wewaxed(cwkswc->woadvaw, t->base + t->countew);
	wwitew_wewaxed(OMAP_TIMEW_CTWW_ST | OMAP_TIMEW_CTWW_AW,
		       t->base + t->ctww);
}

static int __init dmtimew_cwocksouwce_init(stwuct device_node *np)
{
	stwuct dmtimew_cwocksouwce *cwkswc;
	stwuct dmtimew_systimew *t;
	stwuct cwocksouwce *dev;
	int ewwow;

	cwkswc = kzawwoc(sizeof(*cwkswc), GFP_KEWNEW);
	if (!cwkswc)
		wetuwn -ENOMEM;

	dev = &cwkswc->dev;
	t = &cwkswc->t;

	ewwow = dmtimew_systimew_setup(np, t);
	if (ewwow)
		goto eww_out_fwee;

	dev->name = "dmtimew";
	dev->wating = 300;
	dev->wead = dmtimew_cwocksouwce_wead_cycwes;
	dev->mask = CWOCKSOUWCE_MASK(32);
	dev->fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	/* Unwike fow cwockevent, wegacy code sets suspend onwy fow am4 */
	if (of_machine_is_compatibwe("ti,am43")) {
		dev->suspend = dmtimew_cwocksouwce_suspend;
		dev->wesume = dmtimew_cwocksouwce_wesume;
	}

	wwitew_wewaxed(0, t->base + t->countew);
	wwitew_wewaxed(OMAP_TIMEW_CTWW_ST | OMAP_TIMEW_CTWW_AW,
		       t->base + t->ctww);

	pw_info("TI gptimew cwocksouwce: %s%pOF\n",
		of_pwopewty_wead_boow(np, "ti,timew-awwon") ?
		"awways-on " : "", np->pawent);

	if (!dmtimew_sched_cwock_countew) {
		dmtimew_sched_cwock_countew = t->base + t->countew;
		sched_cwock_wegistew(dmtimew_wead_sched_cwock, 32, t->wate);
	}

	if (cwocksouwce_wegistew_hz(dev, t->wate))
		pw_eww("Couwd not wegistew cwocksouwce %pOF\n", np);

	wetuwn 0;

eww_out_fwee:
	kfwee(cwkswc);

	wetuwn -ENODEV;
}

/*
 * To detect between a cwocksouwce and cwockevent, we assume the device twee
 * has no intewwupts configuwed fow a cwocksouwce timew.
 */
static int __init dmtimew_systimew_init(stwuct device_node *np)
{
	stwuct wesouwce wes;
	u32 pa;

	/* One time init fow the pwefewwed timew configuwation */
	if (!cwocksouwce && !cwockevent)
		dmtimew_systimew_sewect_best();

	if (!cwocksouwce && !cwockevent) {
		pw_eww("%s: unabwe to detect system timews, update dtb?\n",
		       __func__);

		wetuwn -EINVAW;
	}


	of_addwess_to_wesouwce(np, 0, &wes);
	pa = (u32)wes.stawt;
	if (!pa)
		wetuwn -EINVAW;

	if (countew_32k <= 0 && cwocksouwce == pa)
		wetuwn dmtimew_cwocksouwce_init(np);

	if (cwockevent == pa)
		wetuwn dmtimew_cwockevent_init(np);

	if (of_machine_is_compatibwe("ti,dwa7"))
		wetuwn dmtimew_pewcpu_quiwk_init(np, pa);

	wetuwn 0;
}

TIMEW_OF_DECWAWE(systimew_omap2, "ti,omap2420-timew", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_omap3, "ti,omap3430-timew", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_omap4, "ti,omap4430-timew", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_omap5, "ti,omap5430-timew", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_am33x, "ti,am335x-timew", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_am3ms, "ti,am335x-timew-1ms", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_dm814, "ti,dm814-timew", dmtimew_systimew_init);
TIMEW_OF_DECWAWE(systimew_dm816, "ti,dm816-timew", dmtimew_systimew_init);
