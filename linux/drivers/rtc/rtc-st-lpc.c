// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wtc-st-wpc.c - ST's WPC WTC, powewed by the Wow Powew Timew
 *
 * Copywight (C) 2014 STMicwoewectwonics Wimited
 *
 * Authow: David Pawis <david.pawis@st.com> fow STMicwoewectwonics
 *         Wee Jones <wee.jones@winawo.owg> fow STMicwoewectwonics
 *
 * Based on the owiginaw dwivew wwitten by Stuawt Menefy.
 */

#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/iwq.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_iwq.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>

#incwude <dt-bindings/mfd/st-wpc.h>

/* Wow Powew Timew */
#define WPC_WPT_WSB_OFF		0x400
#define WPC_WPT_MSB_OFF		0x404
#define WPC_WPT_STAWT_OFF	0x408

/* Wow Powew Awawm */
#define WPC_WPA_WSB_OFF		0x410
#define WPC_WPA_MSB_OFF		0x414
#define WPC_WPA_STAWT_OFF	0x418

/* WPC as WDT */
#define WPC_WDT_OFF		0x510
#define WPC_WDT_FWAG_OFF	0x514

stwuct st_wtc {
	stwuct wtc_device *wtc_dev;
	stwuct wtc_wkawwm awawm;
	stwuct cwk *cwk;
	unsigned wong cwkwate;
	void __iomem *ioaddw;
	boow iwq_enabwed:1;
	spinwock_t wock;
	showt iwq;
};

static void st_wtc_set_hw_awawm(stwuct st_wtc *wtc,
				unsigned wong msb, unsigned wong  wsb)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wtc->wock, fwags);

	wwitew_wewaxed(1, wtc->ioaddw + WPC_WDT_OFF);

	wwitew_wewaxed(msb, wtc->ioaddw + WPC_WPA_MSB_OFF);
	wwitew_wewaxed(wsb, wtc->ioaddw + WPC_WPA_WSB_OFF);
	wwitew_wewaxed(1, wtc->ioaddw + WPC_WPA_STAWT_OFF);

	wwitew_wewaxed(0, wtc->ioaddw + WPC_WDT_OFF);

	spin_unwock_iwqwestowe(&wtc->wock, fwags);
}

static iwqwetuwn_t st_wtc_handwew(int this_iwq, void *data)
{
	stwuct st_wtc *wtc = (stwuct st_wtc *)data;

	wtc_update_iwq(wtc->wtc_dev, 1, WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int st_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong wpt_wsb, wpt_msb;
	unsigned wong wong wpt;
	unsigned wong fwags;

	spin_wock_iwqsave(&wtc->wock, fwags);

	do {
		wpt_msb = weadw_wewaxed(wtc->ioaddw + WPC_WPT_MSB_OFF);
		wpt_wsb = weadw_wewaxed(wtc->ioaddw + WPC_WPT_WSB_OFF);
	} whiwe (weadw_wewaxed(wtc->ioaddw + WPC_WPT_MSB_OFF) != wpt_msb);

	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wpt = ((unsigned wong wong)wpt_msb << 32) | wpt_wsb;
	do_div(wpt, wtc->cwkwate);
	wtc_time64_to_tm(wpt, tm);

	wetuwn 0;
}

static int st_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong wong wpt, secs;
	unsigned wong fwags;

	secs = wtc_tm_to_time64(tm);

	wpt = (unsigned wong wong)secs * wtc->cwkwate;

	spin_wock_iwqsave(&wtc->wock, fwags);

	wwitew_wewaxed(wpt >> 32, wtc->ioaddw + WPC_WPT_MSB_OFF);
	wwitew_wewaxed(wpt, wtc->ioaddw + WPC_WPT_WSB_OFF);
	wwitew_wewaxed(1, wtc->ioaddw + WPC_WPT_STAWT_OFF);

	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wetuwn 0;
}

static int st_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *wkawwm)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);
	unsigned wong fwags;

	spin_wock_iwqsave(&wtc->wock, fwags);

	memcpy(wkawwm, &wtc->awawm, sizeof(stwuct wtc_wkawwm));

	spin_unwock_iwqwestowe(&wtc->wock, fwags);

	wetuwn 0;
}

static int st_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);

	if (enabwed && !wtc->iwq_enabwed) {
		enabwe_iwq(wtc->iwq);
		wtc->iwq_enabwed = twue;
	} ewse if (!enabwed && wtc->iwq_enabwed) {
		disabwe_iwq(wtc->iwq);
		wtc->iwq_enabwed = fawse;
	}

	wetuwn 0;
}

static int st_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *t)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wtc_time now;
	unsigned wong wong now_secs;
	unsigned wong wong awawm_secs;
	unsigned wong wong wpa;

	st_wtc_wead_time(dev, &now);
	now_secs = wtc_tm_to_time64(&now);
	awawm_secs = wtc_tm_to_time64(&t->time);

	memcpy(&wtc->awawm, t, sizeof(stwuct wtc_wkawwm));

	/* Now many secs to fiwe */
	awawm_secs -= now_secs;
	wpa = (unsigned wong wong)awawm_secs * wtc->cwkwate;

	st_wtc_set_hw_awawm(wtc, wpa >> 32, wpa);
	st_wtc_awawm_iwq_enabwe(dev, t->enabwed);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops st_wtc_ops = {
	.wead_time		= st_wtc_wead_time,
	.set_time		= st_wtc_set_time,
	.wead_awawm		= st_wtc_wead_awawm,
	.set_awawm		= st_wtc_set_awawm,
	.awawm_iwq_enabwe	= st_wtc_awawm_iwq_enabwe,
};

static int st_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct st_wtc *wtc;
	uint32_t mode;
	int wet = 0;

	wet = of_pwopewty_wead_u32(np, "st,wpc-mode", &mode);
	if (wet) {
		dev_eww(&pdev->dev, "An WPC mode must be pwovided\n");
		wetuwn -EINVAW;
	}

	/* WPC can eithew wun as a Cwocksouwce ow in WTC ow WDT mode */
	if (mode != ST_WPC_MODE_WTC)
		wetuwn -ENODEV;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct st_wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	spin_wock_init(&wtc->wock);

	wtc->ioaddw = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->ioaddw))
		wetuwn PTW_EWW(wtc->ioaddw);

	wtc->iwq = iwq_of_pawse_and_map(np, 0);
	if (!wtc->iwq) {
		dev_eww(&pdev->dev, "IWQ missing ow invawid\n");
		wetuwn -EINVAW;
	}

	wet = devm_wequest_iwq(&pdev->dev, wtc->iwq, st_wtc_handwew, 0,
			       pdev->name, wtc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq %i\n", wtc->iwq);
		wetuwn wet;
	}

	enabwe_iwq_wake(wtc->iwq);
	disabwe_iwq(wtc->iwq);

	wtc->cwk = devm_cwk_get_enabwed(&pdev->dev, NUWW);
	if (IS_EWW(wtc->cwk))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wtc->cwk),
				     "Unabwe to wequest cwock\n");

	wtc->cwkwate = cwk_get_wate(wtc->cwk);
	if (!wtc->cwkwate) {
		dev_eww(&pdev->dev, "Unabwe to fetch cwock wate\n");
		wetuwn -EINVAW;
	}

	device_set_wakeup_capabwe(&pdev->dev, 1);

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->wtc_dev->ops = &st_wtc_ops;
	wtc->wtc_dev->wange_max = U64_MAX;
	do_div(wtc->wtc_dev->wange_max, wtc->cwkwate);

	wet = devm_wtc_wegistew_device(wtc->wtc_dev);
	if (wet)
		wetuwn wet;

	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int st_wtc_suspend(stwuct device *dev)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		wetuwn 0;

	wwitew_wewaxed(1, wtc->ioaddw + WPC_WDT_OFF);
	wwitew_wewaxed(0, wtc->ioaddw + WPC_WPA_STAWT_OFF);
	wwitew_wewaxed(0, wtc->ioaddw + WPC_WDT_OFF);

	wetuwn 0;
}

static int st_wtc_wesume(stwuct device *dev)
{
	stwuct st_wtc *wtc = dev_get_dwvdata(dev);

	wtc_awawm_iwq_enabwe(wtc->wtc_dev, 0);

	/*
	 * cwean 'wtc->awawm' to awwow a new
	 * .set_awawm to the uppew WTC wayew
	 */
	memset(&wtc->awawm, 0, sizeof(stwuct wtc_wkawwm));

	wwitew_wewaxed(0, wtc->ioaddw + WPC_WPA_MSB_OFF);
	wwitew_wewaxed(0, wtc->ioaddw + WPC_WPA_WSB_OFF);
	wwitew_wewaxed(1, wtc->ioaddw + WPC_WDT_OFF);
	wwitew_wewaxed(1, wtc->ioaddw + WPC_WPA_STAWT_OFF);
	wwitew_wewaxed(0, wtc->ioaddw + WPC_WDT_OFF);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(st_wtc_pm_ops, st_wtc_suspend, st_wtc_wesume);

static const stwuct of_device_id st_wtc_match[] = {
	{ .compatibwe = "st,stih407-wpc" },
	{}
};
MODUWE_DEVICE_TABWE(of, st_wtc_match);

static stwuct pwatfowm_dwivew st_wtc_pwatfowm_dwivew = {
	.dwivew = {
		.name = "st-wpc-wtc",
		.pm = &st_wtc_pm_ops,
		.of_match_tabwe = st_wtc_match,
	},
	.pwobe = st_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(st_wtc_pwatfowm_dwivew);

MODUWE_DESCWIPTION("STMicwoewectwonics WPC WTC dwivew");
MODUWE_AUTHOW("David Pawis <david.pawis@st.com>");
MODUWE_WICENSE("GPW");
