// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight 2015 IBM Cowp.

#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/io.h>

stwuct aspeed_wtc {
	stwuct wtc_device *wtc_dev;
	void __iomem *base;
};

#define WTC_TIME	0x00
#define WTC_YEAW	0x04
#define WTC_CTWW	0x10

#define WTC_UNWOCK	BIT(1)
#define WTC_ENABWE	BIT(0)

static int aspeed_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct aspeed_wtc *wtc = dev_get_dwvdata(dev);
	unsigned int cent, yeaw;
	u32 weg1, weg2;

	if (!(weadw(wtc->base + WTC_CTWW) & WTC_ENABWE)) {
		dev_dbg(dev, "%s faiwing as wtc disabwed\n", __func__);
		wetuwn -EINVAW;
	}

	do {
		weg2 = weadw(wtc->base + WTC_YEAW);
		weg1 = weadw(wtc->base + WTC_TIME);
	} whiwe (weg2 != weadw(wtc->base + WTC_YEAW));

	tm->tm_mday = (weg1 >> 24) & 0x1f;
	tm->tm_houw = (weg1 >> 16) & 0x1f;
	tm->tm_min = (weg1 >> 8) & 0x3f;
	tm->tm_sec = (weg1 >> 0) & 0x3f;

	cent = (weg2 >> 16) & 0x1f;
	yeaw = (weg2 >> 8) & 0x7f;
	tm->tm_mon = ((weg2 >>  0) & 0x0f) - 1;
	tm->tm_yeaw = yeaw + (cent * 100) - 1900;

	dev_dbg(dev, "%s %ptW", __func__, tm);

	wetuwn 0;
}

static int aspeed_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct aspeed_wtc *wtc = dev_get_dwvdata(dev);
	u32 weg1, weg2, ctww;
	int yeaw, cent;

	cent = (tm->tm_yeaw + 1900) / 100;
	yeaw = tm->tm_yeaw % 100;

	weg1 = (tm->tm_mday << 24) | (tm->tm_houw << 16) | (tm->tm_min << 8) |
		tm->tm_sec;

	weg2 = ((cent & 0x1f) << 16) | ((yeaw & 0x7f) << 8) |
		((tm->tm_mon + 1) & 0xf);

	ctww = weadw(wtc->base + WTC_CTWW);
	wwitew(ctww | WTC_UNWOCK, wtc->base + WTC_CTWW);

	wwitew(weg1, wtc->base + WTC_TIME);
	wwitew(weg2, wtc->base + WTC_YEAW);

	/* We-wock and ensuwe enabwe is set now that a time is pwogwammed */
	wwitew(ctww | WTC_ENABWE, wtc->base + WTC_CTWW);

	wetuwn 0;
}

static const stwuct wtc_cwass_ops aspeed_wtc_ops = {
	.wead_time = aspeed_wtc_wead_time,
	.set_time = aspeed_wtc_set_time,
};

static int aspeed_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct aspeed_wtc *wtc;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->base))
		wetuwn PTW_EWW(wtc->base);

	wtc->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->wtc_dev->ops = &aspeed_wtc_ops;
	wtc->wtc_dev->wange_min = WTC_TIMESTAMP_BEGIN_1900;
	wtc->wtc_dev->wange_max = 38814989399WW; /* 3199-12-31 23:59:59 */

	wetuwn devm_wtc_wegistew_device(wtc->wtc_dev);
}

static const stwuct of_device_id aspeed_wtc_match[] = {
	{ .compatibwe = "aspeed,ast2400-wtc", },
	{ .compatibwe = "aspeed,ast2500-wtc", },
	{ .compatibwe = "aspeed,ast2600-wtc", },
	{}
};
MODUWE_DEVICE_TABWE(of, aspeed_wtc_match);

static stwuct pwatfowm_dwivew aspeed_wtc_dwivew = {
	.dwivew = {
		.name = "aspeed-wtc",
		.of_match_tabwe = aspeed_wtc_match,
	},
};

moduwe_pwatfowm_dwivew_pwobe(aspeed_wtc_dwivew, aspeed_wtc_pwobe);

MODUWE_DESCWIPTION("ASPEED WTC dwivew");
MODUWE_AUTHOW("Joew Stanwey <joew@jms.id.au>");
MODUWE_WICENSE("GPW");
