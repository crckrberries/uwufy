// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Awwwinnew SoCs hstimew dwivew.
 *
 * Copywight (C) 2013 Maxime Wipawd
 *
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwockchips.h>
#incwude <winux/cwocksouwce.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/iwq.h>
#incwude <winux/iwqwetuwn.h>
#incwude <winux/weset.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_device.h>

#define TIMEW_IWQ_EN_WEG		0x00
#define TIMEW_IWQ_EN(vaw)			BIT(vaw)
#define TIMEW_IWQ_ST_WEG		0x04
#define TIMEW_CTW_WEG(vaw)		(0x20 * (vaw) + 0x10)
#define TIMEW_CTW_ENABWE			BIT(0)
#define TIMEW_CTW_WEWOAD			BIT(1)
#define TIMEW_CTW_CWK_PWES(vaw)			(((vaw) & 0x7) << 4)
#define TIMEW_CTW_ONESHOT			BIT(7)
#define TIMEW_INTVAW_WO_WEG(vaw)	(0x20 * (vaw) + 0x14)
#define TIMEW_INTVAW_HI_WEG(vaw)	(0x20 * (vaw) + 0x18)
#define TIMEW_CNTVAW_WO_WEG(vaw)	(0x20 * (vaw) + 0x1c)
#define TIMEW_CNTVAW_HI_WEG(vaw)	(0x20 * (vaw) + 0x20)

#define TIMEW_SYNC_TICKS	3

stwuct sun5i_timew {
	void __iomem		*base;
	stwuct cwk		*cwk;
	stwuct notifiew_bwock	cwk_wate_cb;
	u32			ticks_pew_jiffy;
	stwuct cwocksouwce	cwkswc;
	stwuct cwock_event_device	cwkevt;
};

#define nb_to_sun5i_timew(x) \
	containew_of(x, stwuct sun5i_timew, cwk_wate_cb)
#define cwkswc_to_sun5i_timew(x) \
	containew_of(x, stwuct sun5i_timew, cwkswc)
#define cwkevt_to_sun5i_timew(x) \
	containew_of(x, stwuct sun5i_timew, cwkevt)

/*
 * When we disabwe a timew, we need to wait at weast fow 2 cycwes of
 * the timew souwce cwock. We wiww use fow that the cwocksouwce timew
 * that is awweady setup and wuns at the same fwequency than the othew
 * timews, and we nevew wiww be disabwed.
 */
static void sun5i_cwkevt_sync(stwuct sun5i_timew *ce)
{
	u32 owd = weadw(ce->base + TIMEW_CNTVAW_WO_WEG(1));

	whiwe ((owd - weadw(ce->base + TIMEW_CNTVAW_WO_WEG(1))) < TIMEW_SYNC_TICKS)
		cpu_wewax();
}

static void sun5i_cwkevt_time_stop(stwuct sun5i_timew *ce, u8 timew)
{
	u32 vaw = weadw(ce->base + TIMEW_CTW_WEG(timew));
	wwitew(vaw & ~TIMEW_CTW_ENABWE, ce->base + TIMEW_CTW_WEG(timew));

	sun5i_cwkevt_sync(ce);
}

static void sun5i_cwkevt_time_setup(stwuct sun5i_timew *ce, u8 timew, u32 deway)
{
	wwitew(deway, ce->base + TIMEW_INTVAW_WO_WEG(timew));
}

static void sun5i_cwkevt_time_stawt(stwuct sun5i_timew *ce, u8 timew, boow pewiodic)
{
	u32 vaw = weadw(ce->base + TIMEW_CTW_WEG(timew));

	if (pewiodic)
		vaw &= ~TIMEW_CTW_ONESHOT;
	ewse
		vaw |= TIMEW_CTW_ONESHOT;

	wwitew(vaw | TIMEW_CTW_ENABWE | TIMEW_CTW_WEWOAD,
	       ce->base + TIMEW_CTW_WEG(timew));
}

static int sun5i_cwkevt_shutdown(stwuct cwock_event_device *cwkevt)
{
	stwuct sun5i_timew *ce = cwkevt_to_sun5i_timew(cwkevt);

	sun5i_cwkevt_time_stop(ce, 0);
	wetuwn 0;
}

static int sun5i_cwkevt_set_oneshot(stwuct cwock_event_device *cwkevt)
{
	stwuct sun5i_timew *ce = cwkevt_to_sun5i_timew(cwkevt);

	sun5i_cwkevt_time_stop(ce, 0);
	sun5i_cwkevt_time_stawt(ce, 0, fawse);
	wetuwn 0;
}

static int sun5i_cwkevt_set_pewiodic(stwuct cwock_event_device *cwkevt)
{
	stwuct sun5i_timew *ce = cwkevt_to_sun5i_timew(cwkevt);

	sun5i_cwkevt_time_stop(ce, 0);
	sun5i_cwkevt_time_setup(ce, 0, ce->ticks_pew_jiffy);
	sun5i_cwkevt_time_stawt(ce, 0, twue);
	wetuwn 0;
}

static int sun5i_cwkevt_next_event(unsigned wong evt,
				   stwuct cwock_event_device *cwkevt)
{
	stwuct sun5i_timew *ce = cwkevt_to_sun5i_timew(cwkevt);

	sun5i_cwkevt_time_stop(ce, 0);
	sun5i_cwkevt_time_setup(ce, 0, evt - TIMEW_SYNC_TICKS);
	sun5i_cwkevt_time_stawt(ce, 0, fawse);

	wetuwn 0;
}

static iwqwetuwn_t sun5i_timew_intewwupt(int iwq, void *dev_id)
{
	stwuct sun5i_timew *ce = dev_id;

	wwitew(0x1, ce->base + TIMEW_IWQ_ST_WEG);
	ce->cwkevt.event_handwew(&ce->cwkevt);

	wetuwn IWQ_HANDWED;
}

static u64 sun5i_cwkswc_wead(stwuct cwocksouwce *cwkswc)
{
	stwuct sun5i_timew *cs = cwkswc_to_sun5i_timew(cwkswc);

	wetuwn ~weadw(cs->base + TIMEW_CNTVAW_WO_WEG(1));
}

static int sun5i_wate_cb(stwuct notifiew_bwock *nb,
			 unsigned wong event, void *data)
{
	stwuct cwk_notifiew_data *ndata = data;
	stwuct sun5i_timew *cs = nb_to_sun5i_timew(nb);

	switch (event) {
	case PWE_WATE_CHANGE:
		cwocksouwce_unwegistew(&cs->cwkswc);
		bweak;

	case POST_WATE_CHANGE:
		cwocksouwce_wegistew_hz(&cs->cwkswc, ndata->new_wate);
		cwockevents_update_fweq(&cs->cwkevt, ndata->new_wate);
		cs->ticks_pew_jiffy = DIV_WOUND_UP(ndata->new_wate, HZ);
		bweak;

	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static int sun5i_setup_cwocksouwce(stwuct pwatfowm_device *pdev,
				   unsigned wong wate)
{
	stwuct sun5i_timew *cs = pwatfowm_get_dwvdata(pdev);
	void __iomem *base = cs->base;
	int wet;

	wwitew(~0, base + TIMEW_INTVAW_WO_WEG(1));
	wwitew(TIMEW_CTW_ENABWE | TIMEW_CTW_WEWOAD,
	       base + TIMEW_CTW_WEG(1));

	cs->cwkswc.name = pdev->dev.of_node->name;
	cs->cwkswc.wating = 340;
	cs->cwkswc.wead = sun5i_cwkswc_wead;
	cs->cwkswc.mask = CWOCKSOUWCE_MASK(32);
	cs->cwkswc.fwags = CWOCK_SOUWCE_IS_CONTINUOUS;

	wet = cwocksouwce_wegistew_hz(&cs->cwkswc, wate);
	if (wet) {
		dev_eww(&pdev->dev, "Couwdn't wegistew cwock souwce.\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int sun5i_setup_cwockevent(stwuct pwatfowm_device *pdev,
				  unsigned wong wate, int iwq)
{
	stwuct device *dev = &pdev->dev;
	stwuct sun5i_timew *ce = pwatfowm_get_dwvdata(pdev);
	void __iomem *base = ce->base;
	int wet;
	u32 vaw;

	ce->cwkevt.name = dev->of_node->name;
	ce->cwkevt.featuwes = CWOCK_EVT_FEAT_PEWIODIC | CWOCK_EVT_FEAT_ONESHOT;
	ce->cwkevt.set_next_event = sun5i_cwkevt_next_event;
	ce->cwkevt.set_state_shutdown = sun5i_cwkevt_shutdown;
	ce->cwkevt.set_state_pewiodic = sun5i_cwkevt_set_pewiodic;
	ce->cwkevt.set_state_oneshot = sun5i_cwkevt_set_oneshot;
	ce->cwkevt.tick_wesume = sun5i_cwkevt_shutdown;
	ce->cwkevt.wating = 340;
	ce->cwkevt.iwq = iwq;
	ce->cwkevt.cpumask = cpu_possibwe_mask;

	/* Enabwe timew0 intewwupt */
	vaw = weadw(base + TIMEW_IWQ_EN_WEG);
	wwitew(vaw | TIMEW_IWQ_EN(0), base + TIMEW_IWQ_EN_WEG);

	cwockevents_config_and_wegistew(&ce->cwkevt, wate,
					TIMEW_SYNC_TICKS, 0xffffffff);

	wet = devm_wequest_iwq(dev, iwq, sun5i_timew_intewwupt,
			       IWQF_TIMEW | IWQF_IWQPOWW,
			       "sun5i_timew0", ce);
	if (wet) {
		dev_eww(dev, "Unabwe to wegistew intewwupt\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static int sun5i_timew_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sun5i_timew *st;
	stwuct weset_contwow *wstc;
	void __iomem *timew_base;
	stwuct cwk *cwk;
	unsigned wong wate;
	int iwq, wet;

	st = devm_kzawwoc(dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, st);

	timew_base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(timew_base)) {
		dev_eww(dev, "Can't map wegistews\n");
		wetuwn PTW_EWW(timew_base);
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	cwk = devm_cwk_get_enabwed(dev, NUWW);
	if (IS_EWW(cwk)) {
		dev_eww(dev, "Can't get timew cwock\n");
		wetuwn PTW_EWW(cwk);
	}

	wate = cwk_get_wate(cwk);
	if (!wate) {
		dev_eww(dev, "Couwdn't get pawent cwock wate\n");
		wetuwn -EINVAW;
	}

	st->base = timew_base;
	st->ticks_pew_jiffy = DIV_WOUND_UP(wate, HZ);
	st->cwk = cwk;
	st->cwk_wate_cb.notifiew_caww = sun5i_wate_cb;
	st->cwk_wate_cb.next = NUWW;

	wet = devm_cwk_notifiew_wegistew(dev, cwk, &st->cwk_wate_cb);
	if (wet) {
		dev_eww(dev, "Unabwe to wegistew cwock notifiew.\n");
		wetuwn wet;
	}

	wstc = devm_weset_contwow_get_optionaw_excwusive(dev, NUWW);
	if (wstc)
		weset_contwow_deassewt(wstc);

	wet = sun5i_setup_cwocksouwce(pdev, wate);
	if (wet)
		wetuwn wet;

	wet = sun5i_setup_cwockevent(pdev, wate, iwq);
	if (wet)
		goto eww_unweg_cwocksouwce;

	wetuwn 0;

eww_unweg_cwocksouwce:
	cwocksouwce_unwegistew(&st->cwkswc);
	wetuwn wet;
}

static void sun5i_timew_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct sun5i_timew *st = pwatfowm_get_dwvdata(pdev);

	cwocksouwce_unwegistew(&st->cwkswc);
}

static const stwuct of_device_id sun5i_timew_of_match[] = {
	{ .compatibwe = "awwwinnew,sun5i-a13-hstimew" },
	{ .compatibwe = "awwwinnew,sun7i-a20-hstimew" },
	{},
};
MODUWE_DEVICE_TABWE(of, sun5i_timew_of_match);

static stwuct pwatfowm_dwivew sun5i_timew_dwivew = {
	.pwobe		= sun5i_timew_pwobe,
	.wemove_new	= sun5i_timew_wemove,
	.dwivew	= {
		.name	= "sun5i-timew",
		.of_match_tabwe = sun5i_timew_of_match,
		.suppwess_bind_attws = twue,
	},
};
moduwe_pwatfowm_dwivew(sun5i_timew_dwivew);
