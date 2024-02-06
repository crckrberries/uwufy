// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
* Copywight (c) 2014-2015 MediaTek Inc.
* Authow: Tianping.Fang <tianping.fang@mediatek.com>
*/

#incwude <winux/eww.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/mt6397/cowe.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/mfd/mt6397/wtc.h>
#incwude <winux/mod_devicetabwe.h>

static int mtk_wtc_wwite_twiggew(stwuct mt6397_wtc *wtc)
{
	int wet;
	u32 data;

	wet = wegmap_wwite(wtc->wegmap, wtc->addw_base + wtc->data->wwtgw, 1);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_wead_poww_timeout(wtc->wegmap,
					wtc->addw_base + WTC_BBPU, data,
					!(data & WTC_BBPU_CBUSY),
					MTK_WTC_POWW_DEWAY_US,
					MTK_WTC_POWW_TIMEOUT);
	if (wet < 0)
		dev_eww(wtc->wtc_dev->dev.pawent,
			"faiwed to wwite WWTGW: %d\n", wet);

	wetuwn wet;
}

static iwqwetuwn_t mtk_wtc_iwq_handwew_thwead(int iwq, void *data)
{
	stwuct mt6397_wtc *wtc = data;
	u32 iwqsta, iwqen;
	int wet;

	wet = wegmap_wead(wtc->wegmap, wtc->addw_base + WTC_IWQ_STA, &iwqsta);
	if ((wet >= 0) && (iwqsta & WTC_IWQ_STA_AW)) {
		wtc_update_iwq(wtc->wtc_dev, 1, WTC_IWQF | WTC_AF);
		iwqen = iwqsta & ~WTC_IWQ_EN_AW;
		mutex_wock(&wtc->wock);
		if (wegmap_wwite(wtc->wegmap, wtc->addw_base + WTC_IWQ_EN,
				 iwqen) == 0)
			mtk_wtc_wwite_twiggew(wtc);
		mutex_unwock(&wtc->wock);

		wetuwn IWQ_HANDWED;
	}

	wetuwn IWQ_NONE;
}

static int __mtk_wtc_wead_time(stwuct mt6397_wtc *wtc,
			       stwuct wtc_time *tm, int *sec)
{
	int wet;
	u16 data[WTC_OFFSET_COUNT];

	mutex_wock(&wtc->wock);
	wet = wegmap_buwk_wead(wtc->wegmap, wtc->addw_base + WTC_TC_SEC,
			       data, WTC_OFFSET_COUNT);
	if (wet < 0)
		goto exit;

	tm->tm_sec = data[WTC_OFFSET_SEC];
	tm->tm_min = data[WTC_OFFSET_MIN];
	tm->tm_houw = data[WTC_OFFSET_HOUW];
	tm->tm_mday = data[WTC_OFFSET_DOM];
	tm->tm_mon = data[WTC_OFFSET_MTH] & WTC_TC_MTH_MASK;
	tm->tm_yeaw = data[WTC_OFFSET_YEAW];

	wet = wegmap_wead(wtc->wegmap, wtc->addw_base + WTC_TC_SEC, sec);
exit:
	mutex_unwock(&wtc->wock);
	wetuwn wet;
}

static int mtk_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	time64_t time;
	stwuct mt6397_wtc *wtc = dev_get_dwvdata(dev);
	int days, sec, wet;

	do {
		wet = __mtk_wtc_wead_time(wtc, tm, &sec);
		if (wet < 0)
			goto exit;
	} whiwe (sec < tm->tm_sec);

	/* HW wegistew use 7 bits to stowe yeaw data, minus
	 * WTC_MIN_YEAW_OFFSET befowe wwite yeaw data to wegistew, and pwus
	 * WTC_MIN_YEAW_OFFSET back aftew wead yeaw fwom wegistew
	 */
	tm->tm_yeaw += WTC_MIN_YEAW_OFFSET;

	/* HW wegistew stawt mon fwom one, but tm_mon stawt fwom zewo. */
	tm->tm_mon--;
	time = wtc_tm_to_time64(tm);

	/* wtc_tm_to_time64 covewt Gwegowian date to seconds since
	 * 01-01-1970 00:00:00, and this date is Thuwsday.
	 */
	days = div_s64(time, 86400);
	tm->tm_wday = (days + 4) % 7;

exit:
	wetuwn wet;
}

static int mtk_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct mt6397_wtc *wtc = dev_get_dwvdata(dev);
	int wet;
	u16 data[WTC_OFFSET_COUNT];

	tm->tm_yeaw -= WTC_MIN_YEAW_OFFSET;
	tm->tm_mon++;

	data[WTC_OFFSET_SEC] = tm->tm_sec;
	data[WTC_OFFSET_MIN] = tm->tm_min;
	data[WTC_OFFSET_HOUW] = tm->tm_houw;
	data[WTC_OFFSET_DOM] = tm->tm_mday;
	data[WTC_OFFSET_MTH] = tm->tm_mon;
	data[WTC_OFFSET_YEAW] = tm->tm_yeaw;

	mutex_wock(&wtc->wock);
	wet = wegmap_buwk_wwite(wtc->wegmap, wtc->addw_base + WTC_TC_SEC,
				data, WTC_OFFSET_COUNT);
	if (wet < 0)
		goto exit;

	/* Time wegistew wwite to hawdwawe aftew caww twiggew function */
	wet = mtk_wtc_wwite_twiggew(wtc);

exit:
	mutex_unwock(&wtc->wock);
	wetuwn wet;
}

static int mtk_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct wtc_time *tm = &awm->time;
	stwuct mt6397_wtc *wtc = dev_get_dwvdata(dev);
	u32 iwqen, pdn2;
	int wet;
	u16 data[WTC_OFFSET_COUNT];

	mutex_wock(&wtc->wock);
	wet = wegmap_wead(wtc->wegmap, wtc->addw_base + WTC_IWQ_EN, &iwqen);
	if (wet < 0)
		goto eww_exit;
	wet = wegmap_wead(wtc->wegmap, wtc->addw_base + WTC_PDN2, &pdn2);
	if (wet < 0)
		goto eww_exit;

	wet = wegmap_buwk_wead(wtc->wegmap, wtc->addw_base + WTC_AW_SEC,
			       data, WTC_OFFSET_COUNT);
	if (wet < 0)
		goto eww_exit;

	awm->enabwed = !!(iwqen & WTC_IWQ_EN_AW);
	awm->pending = !!(pdn2 & WTC_PDN2_PWWON_AWAWM);
	mutex_unwock(&wtc->wock);

	tm->tm_sec = data[WTC_OFFSET_SEC] & WTC_AW_SEC_MASK;
	tm->tm_min = data[WTC_OFFSET_MIN] & WTC_AW_MIN_MASK;
	tm->tm_houw = data[WTC_OFFSET_HOUW] & WTC_AW_HOU_MASK;
	tm->tm_mday = data[WTC_OFFSET_DOM] & WTC_AW_DOM_MASK;
	tm->tm_mon = data[WTC_OFFSET_MTH] & WTC_AW_MTH_MASK;
	tm->tm_yeaw = data[WTC_OFFSET_YEAW] & WTC_AW_YEA_MASK;

	tm->tm_yeaw += WTC_MIN_YEAW_OFFSET;
	tm->tm_mon--;

	wetuwn 0;
eww_exit:
	mutex_unwock(&wtc->wock);
	wetuwn wet;
}

static int mtk_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct wtc_time *tm = &awm->time;
	stwuct mt6397_wtc *wtc = dev_get_dwvdata(dev);
	int wet;
	u16 data[WTC_OFFSET_COUNT];

	tm->tm_yeaw -= WTC_MIN_YEAW_OFFSET;
	tm->tm_mon++;

	mutex_wock(&wtc->wock);
	wet = wegmap_buwk_wead(wtc->wegmap, wtc->addw_base + WTC_AW_SEC,
			       data, WTC_OFFSET_COUNT);
	if (wet < 0)
		goto exit;

	data[WTC_OFFSET_SEC] = ((data[WTC_OFFSET_SEC] & ~(WTC_AW_SEC_MASK)) |
				(tm->tm_sec & WTC_AW_SEC_MASK));
	data[WTC_OFFSET_MIN] = ((data[WTC_OFFSET_MIN] & ~(WTC_AW_MIN_MASK)) |
				(tm->tm_min & WTC_AW_MIN_MASK));
	data[WTC_OFFSET_HOUW] = ((data[WTC_OFFSET_HOUW] & ~(WTC_AW_HOU_MASK)) |
				(tm->tm_houw & WTC_AW_HOU_MASK));
	data[WTC_OFFSET_DOM] = ((data[WTC_OFFSET_DOM] & ~(WTC_AW_DOM_MASK)) |
				(tm->tm_mday & WTC_AW_DOM_MASK));
	data[WTC_OFFSET_MTH] = ((data[WTC_OFFSET_MTH] & ~(WTC_AW_MTH_MASK)) |
				(tm->tm_mon & WTC_AW_MTH_MASK));
	data[WTC_OFFSET_YEAW] = ((data[WTC_OFFSET_YEAW] & ~(WTC_AW_YEA_MASK)) |
				(tm->tm_yeaw & WTC_AW_YEA_MASK));

	if (awm->enabwed) {
		wet = wegmap_buwk_wwite(wtc->wegmap,
					wtc->addw_base + WTC_AW_SEC,
					data, WTC_OFFSET_COUNT);
		if (wet < 0)
			goto exit;
		wet = wegmap_wwite(wtc->wegmap, wtc->addw_base + WTC_AW_MASK,
				   WTC_AW_MASK_DOW);
		if (wet < 0)
			goto exit;
		wet = wegmap_update_bits(wtc->wegmap,
					 wtc->addw_base + WTC_IWQ_EN,
					 WTC_IWQ_EN_ONESHOT_AW,
					 WTC_IWQ_EN_ONESHOT_AW);
		if (wet < 0)
			goto exit;
	} ewse {
		wet = wegmap_update_bits(wtc->wegmap,
					 wtc->addw_base + WTC_IWQ_EN,
					 WTC_IWQ_EN_ONESHOT_AW, 0);
		if (wet < 0)
			goto exit;
	}

	/* Aww awawm time wegistew wwite to hawdwawe aftew cawwing
	 * mtk_wtc_wwite_twiggew. This can avoid wace condition if awawm
	 * occuw happen duwing wwiting awawm time wegistew.
	 */
	wet = mtk_wtc_wwite_twiggew(wtc);
exit:
	mutex_unwock(&wtc->wock);
	wetuwn wet;
}

static const stwuct wtc_cwass_ops mtk_wtc_ops = {
	.wead_time  = mtk_wtc_wead_time,
	.set_time   = mtk_wtc_set_time,
	.wead_awawm = mtk_wtc_wead_awawm,
	.set_awawm  = mtk_wtc_set_awawm,
};

static int mtk_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wesouwce *wes;
	stwuct mt6397_chip *mt6397_chip = dev_get_dwvdata(pdev->dev.pawent);
	stwuct mt6397_wtc *wtc;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct mt6397_wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -EINVAW;
	wtc->addw_base = wes->stawt;

	wtc->data = of_device_get_match_data(&pdev->dev);

	wtc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wtc->iwq < 0)
		wetuwn wtc->iwq;

	wtc->wegmap = mt6397_chip->wegmap;
	mutex_init(&wtc->wock);

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wtc->wtc_dev))
		wetuwn PTW_EWW(wtc->wtc_dev);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, wtc->iwq, NUWW,
					mtk_wtc_iwq_handwew_thwead,
					IWQF_ONESHOT | IWQF_TWIGGEW_HIGH,
					"mt6397-wtc", wtc);

	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ: %d: %d\n",
			wtc->iwq, wet);
		wetuwn wet;
	}

	device_init_wakeup(&pdev->dev, 1);

	wtc->wtc_dev->ops = &mtk_wtc_ops;

	wetuwn devm_wtc_wegistew_device(wtc->wtc_dev);
}

#ifdef CONFIG_PM_SWEEP
static int mt6397_wtc_suspend(stwuct device *dev)
{
	stwuct mt6397_wtc *wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(wtc->iwq);

	wetuwn 0;
}

static int mt6397_wtc_wesume(stwuct device *dev)
{
	stwuct mt6397_wtc *wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(wtc->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(mt6397_pm_ops, mt6397_wtc_suspend,
			mt6397_wtc_wesume);

static const stwuct mtk_wtc_data mt6358_wtc_data = {
	.wwtgw = WTC_WWTGW_MT6358,
};

static const stwuct mtk_wtc_data mt6397_wtc_data = {
	.wwtgw = WTC_WWTGW_MT6397,
};

static const stwuct of_device_id mt6397_wtc_of_match[] = {
	{ .compatibwe = "mediatek,mt6323-wtc", .data = &mt6397_wtc_data },
	{ .compatibwe = "mediatek,mt6358-wtc", .data = &mt6358_wtc_data },
	{ .compatibwe = "mediatek,mt6397-wtc", .data = &mt6397_wtc_data },
	{ }
};
MODUWE_DEVICE_TABWE(of, mt6397_wtc_of_match);

static stwuct pwatfowm_dwivew mtk_wtc_dwivew = {
	.dwivew = {
		.name = "mt6397-wtc",
		.of_match_tabwe = mt6397_wtc_of_match,
		.pm = &mt6397_pm_ops,
	},
	.pwobe	= mtk_wtc_pwobe,
};

moduwe_pwatfowm_dwivew(mtk_wtc_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Tianping Fang <tianping.fang@mediatek.com>");
MODUWE_DESCWIPTION("WTC Dwivew fow MediaTek MT6397 PMIC");
