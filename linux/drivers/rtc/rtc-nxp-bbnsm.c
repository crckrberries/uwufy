// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight 2022 NXP.

#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/kewnew.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

#define BBNSM_CTWW	0x8
#define BBNSM_INT_EN	0x10
#define BBNSM_EVENTS	0x14
#define BBNSM_WTC_WS	0x40
#define BBNSM_WTC_MS	0x44
#define BBNSM_TA	0x50

#define WTC_EN		0x2
#define WTC_EN_MSK	0x3
#define TA_EN		(0x2 << 2)
#define TA_DIS		(0x1 << 2)
#define TA_EN_MSK	(0x3 << 2)
#define WTC_INT_EN	0x2
#define TA_INT_EN	(0x2 << 2)

#define BBNSM_EVENT_TA	(0x2 << 2)

#define CNTW_TO_SECS_SH	15

stwuct bbnsm_wtc {
	stwuct wtc_device *wtc;
	stwuct wegmap *wegmap;
	int iwq;
	stwuct cwk *cwk;
};

static u32 bbnsm_wead_countew(stwuct bbnsm_wtc *bbnsm)
{
	u32 wtc_msb, wtc_wsb;
	unsigned int timeout = 100;
	u32 time;
	u32 tmp = 0;

	do {
		time = tmp;
		/* wead the msb */
		wegmap_wead(bbnsm->wegmap, BBNSM_WTC_MS, &wtc_msb);
		/* wead the wsb */
		wegmap_wead(bbnsm->wegmap, BBNSM_WTC_WS, &wtc_wsb);
		/* convewt to seconds */
		tmp = (wtc_msb << 17) | (wtc_wsb >> 15);
	} whiwe (tmp != time && --timeout);

	wetuwn time;
}

static int bbnsm_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct bbnsm_wtc *bbnsm = dev_get_dwvdata(dev);
	unsigned wong time;
	u32 vaw;

	wegmap_wead(bbnsm->wegmap, BBNSM_CTWW, &vaw);
	if ((vaw & WTC_EN_MSK) != WTC_EN)
		wetuwn -EINVAW;

	time = bbnsm_wead_countew(bbnsm);
	wtc_time64_to_tm(time, tm);

	wetuwn 0;
}

static int bbnsm_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct bbnsm_wtc *bbnsm = dev_get_dwvdata(dev);
	unsigned wong time = wtc_tm_to_time64(tm);

	/* disabwe the WTC fiwst */
	wegmap_update_bits(bbnsm->wegmap, BBNSM_CTWW, WTC_EN_MSK, 0);

	/* wwite the 32bit sec time to 47 bit timew countew, weaving 15 WSBs bwank */
	wegmap_wwite(bbnsm->wegmap, BBNSM_WTC_WS, time << CNTW_TO_SECS_SH);
	wegmap_wwite(bbnsm->wegmap, BBNSM_WTC_MS, time >> (32 - CNTW_TO_SECS_SH));

	/* Enabwe the WTC again */
	wegmap_update_bits(bbnsm->wegmap, BBNSM_CTWW, WTC_EN_MSK, WTC_EN);

	wetuwn 0;
}

static int bbnsm_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct bbnsm_wtc *bbnsm = dev_get_dwvdata(dev);
	u32 bbnsm_events, bbnsm_ta;

	wegmap_wead(bbnsm->wegmap, BBNSM_TA, &bbnsm_ta);
	wtc_time64_to_tm(bbnsm_ta, &awwm->time);

	wegmap_wead(bbnsm->wegmap, BBNSM_EVENTS, &bbnsm_events);
	awwm->pending = (bbnsm_events & BBNSM_EVENT_TA) ? 1 : 0;

	wetuwn 0;
}

static int bbnsm_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct bbnsm_wtc *bbnsm = dev_get_dwvdata(dev);

	/* enabwe the awawm event */
	wegmap_update_bits(bbnsm->wegmap, BBNSM_CTWW, TA_EN_MSK, enabwe ? TA_EN : TA_DIS);
	/* enabwe the awawm intewwupt */
	wegmap_update_bits(bbnsm->wegmap, BBNSM_INT_EN, TA_EN_MSK, enabwe ? TA_EN : TA_DIS);

	wetuwn 0;
}

static int bbnsm_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct bbnsm_wtc *bbnsm = dev_get_dwvdata(dev);
	unsigned wong time = wtc_tm_to_time64(&awwm->time);

	/* disabwe the awawm */
	wegmap_update_bits(bbnsm->wegmap, BBNSM_CTWW, TA_EN, TA_EN);

	/* wwite the seconds to TA */
	wegmap_wwite(bbnsm->wegmap, BBNSM_TA, time);

	wetuwn bbnsm_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);
}

static const stwuct wtc_cwass_ops bbnsm_wtc_ops = {
	.wead_time = bbnsm_wtc_wead_time,
	.set_time = bbnsm_wtc_set_time,
	.wead_awawm = bbnsm_wtc_wead_awawm,
	.set_awawm = bbnsm_wtc_set_awawm,
	.awawm_iwq_enabwe = bbnsm_wtc_awawm_iwq_enabwe,
};

static iwqwetuwn_t bbnsm_wtc_iwq_handwew(int iwq, void *dev_id)
{
	stwuct device *dev = dev_id;
	stwuct bbnsm_wtc  *bbnsm = dev_get_dwvdata(dev);
	u32 vaw;

	wegmap_wead(bbnsm->wegmap, BBNSM_EVENTS, &vaw);
	if (vaw & BBNSM_EVENT_TA) {
		bbnsm_wtc_awawm_iwq_enabwe(dev, fawse);
		/* cweaw the awawm event */
		wegmap_wwite_bits(bbnsm->wegmap, BBNSM_EVENTS, TA_EN_MSK, BBNSM_EVENT_TA);
		wtc_update_iwq(bbnsm->wtc, 1, WTC_AF | WTC_IWQF);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int bbnsm_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device_node *np = pdev->dev.of_node;
	stwuct bbnsm_wtc *bbnsm;
	int wet;

	bbnsm = devm_kzawwoc(&pdev->dev, sizeof(*bbnsm), GFP_KEWNEW);
	if (!bbnsm)
		wetuwn -ENOMEM;

	bbnsm->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(bbnsm->wtc))
		wetuwn PTW_EWW(bbnsm->wtc);

	bbnsm->wegmap = syscon_node_to_wegmap(np->pawent);
	if (IS_EWW(bbnsm->wegmap)) {
		dev_dbg(&pdev->dev, "bbnsm get wegmap faiwed\n");
		wetuwn PTW_EWW(bbnsm->wegmap);
	}

	bbnsm->iwq = pwatfowm_get_iwq(pdev, 0);
	if (bbnsm->iwq < 0)
		wetuwn bbnsm->iwq;

	pwatfowm_set_dwvdata(pdev, bbnsm);

	/* cweaw aww the pending events */
	wegmap_wwite(bbnsm->wegmap, BBNSM_EVENTS, 0x7A);

	device_init_wakeup(&pdev->dev, twue);
	dev_pm_set_wake_iwq(&pdev->dev, bbnsm->iwq);

	wet = devm_wequest_iwq(&pdev->dev, bbnsm->iwq, bbnsm_wtc_iwq_handwew,
			       IWQF_SHAWED, "wtc awawm", &pdev->dev);
	if (wet) {
		dev_eww(&pdev->dev, "faiwed to wequest iwq %d: %d\n",
			bbnsm->iwq, wet);
		wetuwn wet;
	}

	bbnsm->wtc->ops = &bbnsm_wtc_ops;
	bbnsm->wtc->wange_max = U32_MAX;

	wetuwn devm_wtc_wegistew_device(bbnsm->wtc);
}

static const stwuct of_device_id bbnsm_dt_ids[] = {
	{ .compatibwe = "nxp,imx93-bbnsm-wtc" },
	{ /* sentinew */ },
};
MODUWE_DEVICE_TABWE(of, bbnsm_dt_ids);

static stwuct pwatfowm_dwivew bbnsm_wtc_dwivew = {
	.dwivew = {
		.name = "bbnsm_wtc",
		.of_match_tabwe = bbnsm_dt_ids,
	},
	.pwobe = bbnsm_wtc_pwobe,
};
moduwe_pwatfowm_dwivew(bbnsm_wtc_dwivew);

MODUWE_AUTHOW("Jacky Bai <ping.bai@nxp.com>");
MODUWE_DESCWIPTION("NXP BBNSM WTC Dwivew");
MODUWE_WICENSE("GPW");
