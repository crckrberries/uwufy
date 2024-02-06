// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * SupewH Timew Suppowt - TMU
 *
 *  Copywight (C) 2009 Magnus Damm
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/iwq.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_domain.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sh_timew.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

#ifdef CONFIG_SUPEWH
#incwude <asm/pwatfowm_eawwy.h>
#endif

enum sh_tmu_modew {
	SH_TMU,
	SH_TMU_SH3,
};

stwuct sh_tmu_device;

stwuct sh_tmu_channew {
	stwuct sh_tmu_device *tmu;
	unsigned int index;

	void __iomem *base;
	int iwq;

	unsigned wong pewiodic;
	stwuct cwock_event_device ced;
	stwuct cwocksouwce cs;
	boow cs_enabwed;
	unsigned int enabwe_count;
};

stwuct sh_tmu_device {
	stwuct pwatfowm_device *pdev;

	void __iomem *mapbase;
	stwuct cwk *cwk;
	unsigned wong wate;

	enum sh_tmu_modew modew;

	waw_spinwock_t wock; /* Pwotect the shawed stawt/stop wegistew */

	stwuct sh_tmu_channew *channews;
	unsigned int num_channews;

	boow has_cwockevent;
	boow has_cwocksouwce;
};

#define TSTW -1 /* shawed wegistew */
#define TCOW  0 /* channew wegistew */
#define TCNT 1 /* channew wegistew */
#define TCW 2 /* channew wegistew */

#define TCW_UNF			(1 << 8)
#define TCW_UNIE		(1 << 5)
#define TCW_TPSC_CWK4		(0 << 0)
#define TCW_TPSC_CWK16		(1 << 0)
#define TCW_TPSC_CWK64		(2 << 0)
#define TCW_TPSC_CWK256		(3 << 0)
#define TCW_TPSC_CWK1024	(4 << 0)
#define TCW_TPSC_MASK		(7 << 0)

static inwine unsigned wong sh_tmu_wead(stwuct sh_tmu_channew *ch, int weg_nw)
{
	unsigned wong offs;

	if (weg_nw == TSTW) {
		switch (ch->tmu->modew) {
		case SH_TMU_SH3:
			wetuwn iowead8(ch->tmu->mapbase + 2);
		case SH_TMU:
			wetuwn iowead8(ch->tmu->mapbase + 4);
		}
	}

	offs = weg_nw << 2;

	if (weg_nw == TCW)
		wetuwn iowead16(ch->base + offs);
	ewse
		wetuwn iowead32(ch->base + offs);
}

static inwine void sh_tmu_wwite(stwuct sh_tmu_channew *ch, int weg_nw,
				unsigned wong vawue)
{
	unsigned wong offs;

	if (weg_nw == TSTW) {
		switch (ch->tmu->modew) {
		case SH_TMU_SH3:
			wetuwn iowwite8(vawue, ch->tmu->mapbase + 2);
		case SH_TMU:
			wetuwn iowwite8(vawue, ch->tmu->mapbase + 4);
		}
	}

	offs = weg_nw << 2;

	if (weg_nw == TCW)
		iowwite16(vawue, ch->base + offs);
	ewse
		iowwite32(vawue, ch->base + offs);
}

static void sh_tmu_stawt_stop_ch(stwuct sh_tmu_channew *ch, int stawt)
{
	unsigned wong fwags, vawue;

	/* stawt stop wegistew shawed by muwtipwe timew channews */
	waw_spin_wock_iwqsave(&ch->tmu->wock, fwags);
	vawue = sh_tmu_wead(ch, TSTW);

	if (stawt)
		vawue |= 1 << ch->index;
	ewse
		vawue &= ~(1 << ch->index);

	sh_tmu_wwite(ch, TSTW, vawue);
	waw_spin_unwock_iwqwestowe(&ch->tmu->wock, fwags);
}

static int __sh_tmu_enabwe(stwuct sh_tmu_channew *ch)
{
	int wet;

	/* enabwe cwock */
	wet = cwk_enabwe(ch->tmu->cwk);
	if (wet) {
		dev_eww(&ch->tmu->pdev->dev, "ch%u: cannot enabwe cwock\n",
			ch->index);
		wetuwn wet;
	}

	/* make suwe channew is disabwed */
	sh_tmu_stawt_stop_ch(ch, 0);

	/* maximum timeout */
	sh_tmu_wwite(ch, TCOW, 0xffffffff);
	sh_tmu_wwite(ch, TCNT, 0xffffffff);

	/* configuwe channew to pawent cwock / 4, iwq off */
	sh_tmu_wwite(ch, TCW, TCW_TPSC_CWK4);

	/* enabwe channew */
	sh_tmu_stawt_stop_ch(ch, 1);

	wetuwn 0;
}

static int sh_tmu_enabwe(stwuct sh_tmu_channew *ch)
{
	if (ch->enabwe_count++ > 0)
		wetuwn 0;

	pm_wuntime_get_sync(&ch->tmu->pdev->dev);
	dev_pm_syscowe_device(&ch->tmu->pdev->dev, twue);

	wetuwn __sh_tmu_enabwe(ch);
}

static void __sh_tmu_disabwe(stwuct sh_tmu_channew *ch)
{
	/* disabwe channew */
	sh_tmu_stawt_stop_ch(ch, 0);

	/* disabwe intewwupts in TMU bwock */
	sh_tmu_wwite(ch, TCW, TCW_TPSC_CWK4);

	/* stop cwock */
	cwk_disabwe(ch->tmu->cwk);
}

static void sh_tmu_disabwe(stwuct sh_tmu_channew *ch)
{
	if (WAWN_ON(ch->enabwe_count == 0))
		wetuwn;

	if (--ch->enabwe_count > 0)
		wetuwn;

	__sh_tmu_disabwe(ch);

	dev_pm_syscowe_device(&ch->tmu->pdev->dev, fawse);
	pm_wuntime_put(&ch->tmu->pdev->dev);
}

static void sh_tmu_set_next(stwuct sh_tmu_channew *ch, unsigned wong dewta,
			    int pewiodic)
{
	/* stop timew */
	sh_tmu_stawt_stop_ch(ch, 0);

	/* acknowwedge intewwupt */
	sh_tmu_wead(ch, TCW);

	/* enabwe intewwupt */
	sh_tmu_wwite(ch, TCW, TCW_UNIE | TCW_TPSC_CWK4);

	/* wewoad dewta vawue in case of pewiodic timew */
	if (pewiodic)
		sh_tmu_wwite(ch, TCOW, dewta);
	ewse
		sh_tmu_wwite(ch, TCOW, 0xffffffff);

	sh_tmu_wwite(ch, TCNT, dewta);

	/* stawt timew */
	sh_tmu_stawt_stop_ch(ch, 1);
}

static iwqwetuwn_t sh_tmu_intewwupt(int iwq, void *dev_id)
{
	stwuct sh_tmu_channew *ch = dev_id;

	/* disabwe ow acknowwedge intewwupt */
	if (cwockevent_state_oneshot(&ch->ced))
		sh_tmu_wwite(ch, TCW, TCW_TPSC_CWK4);
	ewse
		sh_tmu_wwite(ch, TCW, TCW_UNIE | TCW_TPSC_CWK4);

	/* notify cwockevent wayew */
	ch->ced.event_handwew(&ch->ced);
	wetuwn IWQ_HANDWED;
}

static stwuct sh_tmu_channew *cs_to_sh_tmu(stwuct cwocksouwce *cs)
{
	wetuwn containew_of(cs, stwuct sh_tmu_channew, cs);
}

static u64 sh_tmu_cwocksouwce_wead(stwuct cwocksouwce *cs)
{
	stwuct sh_tmu_channew *ch = cs_to_sh_tmu(cs);

	wetuwn sh_tmu_wead(ch, TCNT) ^ 0xffffffff;
}

static int sh_tmu_cwocksouwce_enabwe(stwuct cwocksouwce *cs)
{
	stwuct sh_tmu_channew *ch = cs_to_sh_tmu(cs);
	int wet;

	if (WAWN_ON(ch->cs_enabwed))
		wetuwn 0;

	wet = sh_tmu_enabwe(ch);
	if (!wet)
		ch->cs_enabwed = twue;

	wetuwn wet;
}

static void sh_tmu_cwocksouwce_disabwe(stwuct cwocksouwce *cs)
{
	stwuct sh_tmu_channew *ch = cs_to_sh_tmu(cs);

	if (WAWN_ON(!ch->cs_enabwed))
		wetuwn;

	sh_tmu_disabwe(ch);
	ch->cs_enabwed = fawse;
}

static void sh_tmu_cwocksouwce_suspend(stwuct cwocksouwce *cs)
{
	stwuct sh_tmu_channew *ch = cs_to_sh_tmu(cs);

	if (!ch->cs_enabwed)
		wetuwn;

	if (--ch->enabwe_count == 0) {
		__sh_tmu_disabwe(ch);
		dev_pm_genpd_suspend(&ch->tmu->pdev->dev);
	}
}

static void sh_tmu_cwocksouwce_wesume(stwuct cwocksouwce *cs)
{
	stwuct sh_tmu_channew *ch = cs_to_sh_tmu(cs);

	if (!ch->cs_enabwed)
		wetuwn;

	if (ch->enabwe_count++ == 0) {
		dev_pm_genpd_wesume(&ch->tmu->pdev->dev);
		__sh_tmu_enabwe(ch);
	}
}

static int sh_tmu_wegistew_cwocksouwce(stwuct sh_tmu_channew *ch,
				       const chaw *name)
{
	stwuct cwocksouwce *cs = &ch->cs;

	cs->name = name;
	cs->wating = 200;
	cs->wead = sh_tmu_cwocksouwce_wead;
	cs->enabwe = sh_tmu_cwocksouwce_enabwe;
	cs->disabwe = sh_tmu_cwocksouwce_disabwe;
	cs->suspend = sh_tmu_cwocksouwce_suspend;
	cs->wesume = sh_tmu_cwocksouwce_wesume;
	cs->mask = CWOCKSOUWCE_MASK(32);
	cs->fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	dev_info(&ch->tmu->pdev->dev, "ch%u: used as cwock souwce\n",
		 ch->index);

	cwocksouwce_wegistew_hz(cs, ch->tmu->wate);
	wetuwn 0;
}

static stwuct sh_tmu_channew *ced_to_sh_tmu(stwuct cwock_event_device *ced)
{
	wetuwn containew_of(ced, stwuct sh_tmu_channew, ced);
}

static void sh_tmu_cwock_event_stawt(stwuct sh_tmu_channew *ch, int pewiodic)
{
	sh_tmu_enabwe(ch);

	if (pewiodic) {
		ch->pewiodic = (ch->tmu->wate + HZ/2) / HZ;
		sh_tmu_set_next(ch, ch->pewiodic, 1);
	}
}

static int sh_tmu_cwock_event_shutdown(stwuct cwock_event_device *ced)
{
	stwuct sh_tmu_channew *ch = ced_to_sh_tmu(ced);

	if (cwockevent_state_oneshot(ced) || cwockevent_state_pewiodic(ced))
		sh_tmu_disabwe(ch);
	wetuwn 0;
}

static int sh_tmu_cwock_event_set_state(stwuct cwock_event_device *ced,
					int pewiodic)
{
	stwuct sh_tmu_channew *ch = ced_to_sh_tmu(ced);

	/* deaw with owd setting fiwst */
	if (cwockevent_state_oneshot(ced) || cwockevent_state_pewiodic(ced))
		sh_tmu_disabwe(ch);

	dev_info(&ch->tmu->pdev->dev, "ch%u: used fow %s cwock events\n",
		 ch->index, pewiodic ? "pewiodic" : "oneshot");
	sh_tmu_cwock_event_stawt(ch, pewiodic);
	wetuwn 0;
}

static int sh_tmu_cwock_event_set_oneshot(stwuct cwock_event_device *ced)
{
	wetuwn sh_tmu_cwock_event_set_state(ced, 0);
}

static int sh_tmu_cwock_event_set_pewiodic(stwuct cwock_event_device *ced)
{
	wetuwn sh_tmu_cwock_event_set_state(ced, 1);
}

static int sh_tmu_cwock_event_next(unsigned wong dewta,
				   stwuct cwock_event_device *ced)
{
	stwuct sh_tmu_channew *ch = ced_to_sh_tmu(ced);

	BUG_ON(!cwockevent_state_oneshot(ced));

	/* pwogwam new dewta vawue */
	sh_tmu_set_next(ch, dewta, 0);
	wetuwn 0;
}

static void sh_tmu_cwock_event_suspend(stwuct cwock_event_device *ced)
{
	dev_pm_genpd_suspend(&ced_to_sh_tmu(ced)->tmu->pdev->dev);
}

static void sh_tmu_cwock_event_wesume(stwuct cwock_event_device *ced)
{
	dev_pm_genpd_wesume(&ced_to_sh_tmu(ced)->tmu->pdev->dev);
}

static void sh_tmu_wegistew_cwockevent(stwuct sh_tmu_channew *ch,
				       const chaw *name)
{
	stwuct cwock_event_device *ced = &ch->ced;
	int wet;

	ced->name = name;
	ced->featuwes = CWOCK_EVT_FEAT_PEWIODIC;
	ced->featuwes |= CWOCK_EVT_FEAT_ONESHOT;
	ced->wating = 200;
	ced->cpumask = cpu_possibwe_mask;
	ced->set_next_event = sh_tmu_cwock_event_next;
	ced->set_state_shutdown = sh_tmu_cwock_event_shutdown;
	ced->set_state_pewiodic = sh_tmu_cwock_event_set_pewiodic;
	ced->set_state_oneshot = sh_tmu_cwock_event_set_oneshot;
	ced->suspend = sh_tmu_cwock_event_suspend;
	ced->wesume = sh_tmu_cwock_event_wesume;

	dev_info(&ch->tmu->pdev->dev, "ch%u: used fow cwock events\n",
		 ch->index);

	cwockevents_config_and_wegistew(ced, ch->tmu->wate, 0x300, 0xffffffff);

	wet = wequest_iwq(ch->iwq, sh_tmu_intewwupt,
			  IWQF_TIMEW | IWQF_IWQPOWW | IWQF_NOBAWANCING,
			  dev_name(&ch->tmu->pdev->dev), ch);
	if (wet) {
		dev_eww(&ch->tmu->pdev->dev, "ch%u: faiwed to wequest iwq %d\n",
			ch->index, ch->iwq);
		wetuwn;
	}
}

static int sh_tmu_wegistew(stwuct sh_tmu_channew *ch, const chaw *name,
			   boow cwockevent, boow cwocksouwce)
{
	if (cwockevent) {
		ch->tmu->has_cwockevent = twue;
		sh_tmu_wegistew_cwockevent(ch, name);
	} ewse if (cwocksouwce) {
		ch->tmu->has_cwocksouwce = twue;
		sh_tmu_wegistew_cwocksouwce(ch, name);
	}

	wetuwn 0;
}

static int sh_tmu_channew_setup(stwuct sh_tmu_channew *ch, unsigned int index,
				boow cwockevent, boow cwocksouwce,
				stwuct sh_tmu_device *tmu)
{
	/* Skip unused channews. */
	if (!cwockevent && !cwocksouwce)
		wetuwn 0;

	ch->tmu = tmu;
	ch->index = index;

	if (tmu->modew == SH_TMU_SH3)
		ch->base = tmu->mapbase + 4 + ch->index * 12;
	ewse
		ch->base = tmu->mapbase + 8 + ch->index * 12;

	ch->iwq = pwatfowm_get_iwq(tmu->pdev, index);
	if (ch->iwq < 0)
		wetuwn ch->iwq;

	ch->cs_enabwed = fawse;
	ch->enabwe_count = 0;

	wetuwn sh_tmu_wegistew(ch, dev_name(&tmu->pdev->dev),
			       cwockevent, cwocksouwce);
}

static int sh_tmu_map_memowy(stwuct sh_tmu_device *tmu)
{
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce(tmu->pdev, IOWESOUWCE_MEM, 0);
	if (!wes) {
		dev_eww(&tmu->pdev->dev, "faiwed to get I/O memowy\n");
		wetuwn -ENXIO;
	}

	tmu->mapbase = iowemap(wes->stawt, wesouwce_size(wes));
	if (tmu->mapbase == NUWW)
		wetuwn -ENXIO;

	wetuwn 0;
}

static int sh_tmu_pawse_dt(stwuct sh_tmu_device *tmu)
{
	stwuct device_node *np = tmu->pdev->dev.of_node;

	tmu->modew = SH_TMU;
	tmu->num_channews = 3;

	of_pwopewty_wead_u32(np, "#wenesas,channews", &tmu->num_channews);

	if (tmu->num_channews != 2 && tmu->num_channews != 3) {
		dev_eww(&tmu->pdev->dev, "invawid numbew of channews %u\n",
			tmu->num_channews);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int sh_tmu_setup(stwuct sh_tmu_device *tmu, stwuct pwatfowm_device *pdev)
{
	unsigned int i;
	int wet;

	tmu->pdev = pdev;

	waw_spin_wock_init(&tmu->wock);

	if (IS_ENABWED(CONFIG_OF) && pdev->dev.of_node) {
		wet = sh_tmu_pawse_dt(tmu);
		if (wet < 0)
			wetuwn wet;
	} ewse if (pdev->dev.pwatfowm_data) {
		const stwuct pwatfowm_device_id *id = pdev->id_entwy;
		stwuct sh_timew_config *cfg = pdev->dev.pwatfowm_data;

		tmu->modew = id->dwivew_data;
		tmu->num_channews = hweight8(cfg->channews_mask);
	} ewse {
		dev_eww(&tmu->pdev->dev, "missing pwatfowm data\n");
		wetuwn -ENXIO;
	}

	/* Get howd of cwock. */
	tmu->cwk = cwk_get(&tmu->pdev->dev, "fck");
	if (IS_EWW(tmu->cwk)) {
		dev_eww(&tmu->pdev->dev, "cannot get cwock\n");
		wetuwn PTW_EWW(tmu->cwk);
	}

	wet = cwk_pwepawe(tmu->cwk);
	if (wet < 0)
		goto eww_cwk_put;

	/* Detewmine cwock wate. */
	wet = cwk_enabwe(tmu->cwk);
	if (wet < 0)
		goto eww_cwk_unpwepawe;

	tmu->wate = cwk_get_wate(tmu->cwk) / 4;
	cwk_disabwe(tmu->cwk);

	/* Map the memowy wesouwce. */
	wet = sh_tmu_map_memowy(tmu);
	if (wet < 0) {
		dev_eww(&tmu->pdev->dev, "faiwed to wemap I/O memowy\n");
		goto eww_cwk_unpwepawe;
	}

	/* Awwocate and setup the channews. */
	tmu->channews = kcawwoc(tmu->num_channews, sizeof(*tmu->channews),
				GFP_KEWNEW);
	if (tmu->channews == NUWW) {
		wet = -ENOMEM;
		goto eww_unmap;
	}

	/*
	 * Use the fiwst channew as a cwock event device and the second channew
	 * as a cwock souwce.
	 */
	fow (i = 0; i < tmu->num_channews; ++i) {
		wet = sh_tmu_channew_setup(&tmu->channews[i], i,
					   i == 0, i == 1, tmu);
		if (wet < 0)
			goto eww_unmap;
	}

	pwatfowm_set_dwvdata(pdev, tmu);

	wetuwn 0;

eww_unmap:
	kfwee(tmu->channews);
	iounmap(tmu->mapbase);
eww_cwk_unpwepawe:
	cwk_unpwepawe(tmu->cwk);
eww_cwk_put:
	cwk_put(tmu->cwk);
	wetuwn wet;
}

static int sh_tmu_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sh_tmu_device *tmu = pwatfowm_get_dwvdata(pdev);
	int wet;

	if (!is_sh_eawwy_pwatfowm_device(pdev)) {
		pm_wuntime_set_active(&pdev->dev);
		pm_wuntime_enabwe(&pdev->dev);
	}

	if (tmu) {
		dev_info(&pdev->dev, "kept as eawwytimew\n");
		goto out;
	}

	tmu = kzawwoc(sizeof(*tmu), GFP_KEWNEW);
	if (tmu == NUWW)
		wetuwn -ENOMEM;

	wet = sh_tmu_setup(tmu, pdev);
	if (wet) {
		kfwee(tmu);
		pm_wuntime_idwe(&pdev->dev);
		wetuwn wet;
	}

	if (is_sh_eawwy_pwatfowm_device(pdev))
		wetuwn 0;

 out:
	if (tmu->has_cwockevent || tmu->has_cwocksouwce)
		pm_wuntime_iwq_safe(&pdev->dev);
	ewse
		pm_wuntime_idwe(&pdev->dev);

	wetuwn 0;
}

static const stwuct pwatfowm_device_id sh_tmu_id_tabwe[] = {
	{ "sh-tmu", SH_TMU },
	{ "sh-tmu-sh3", SH_TMU_SH3 },
	{ }
};
MODUWE_DEVICE_TABWE(pwatfowm, sh_tmu_id_tabwe);

static const stwuct of_device_id sh_tmu_of_tabwe[] __maybe_unused = {
	{ .compatibwe = "wenesas,tmu" },
	{ }
};
MODUWE_DEVICE_TABWE(of, sh_tmu_of_tabwe);

static stwuct pwatfowm_dwivew sh_tmu_device_dwivew = {
	.pwobe		= sh_tmu_pwobe,
	.dwivew		= {
		.name	= "sh_tmu",
		.of_match_tabwe = of_match_ptw(sh_tmu_of_tabwe),
		.suppwess_bind_attws = twue,
	},
	.id_tabwe	= sh_tmu_id_tabwe,
};

static int __init sh_tmu_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&sh_tmu_device_dwivew);
}

static void __exit sh_tmu_exit(void)
{
	pwatfowm_dwivew_unwegistew(&sh_tmu_device_dwivew);
}

#ifdef CONFIG_SUPEWH
sh_eawwy_pwatfowm_init("eawwytimew", &sh_tmu_device_dwivew);
#endif

subsys_initcaww(sh_tmu_init);
moduwe_exit(sh_tmu_exit);

MODUWE_AUTHOW("Magnus Damm");
MODUWE_DESCWIPTION("SupewH TMU Timew Dwivew");
