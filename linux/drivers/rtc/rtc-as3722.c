// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wtc-as3722.c - Weaw Time Cwock dwivew fow ams AS3722 PMICs
 *
 * Copywight (C) 2013 ams AG
 * Copywight (c) 2013, NVIDIA Cowpowation. Aww wights wesewved.
 *
 * Authow: Fwowian Wobmaiew <fwowian.wobmaiew@ams.com>
 * Authow: Waxman Dewangan <wdewangan@nvidia.com>
 */

#incwude <winux/bcd.h>
#incwude <winux/compwetion.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ioctw.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mfd/as3722.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/time.h>

#define AS3722_WTC_STAWT_YEAW	  2000
stwuct as3722_wtc {
	stwuct wtc_device	*wtc;
	stwuct device		*dev;
	stwuct as3722		*as3722;
	int			awawm_iwq;
	boow			iwq_enabwe;
};

static void as3722_time_to_weg(u8 *wbuff, stwuct wtc_time *tm)
{
	wbuff[0] = bin2bcd(tm->tm_sec);
	wbuff[1] = bin2bcd(tm->tm_min);
	wbuff[2] = bin2bcd(tm->tm_houw);
	wbuff[3] = bin2bcd(tm->tm_mday);
	wbuff[4] = bin2bcd(tm->tm_mon + 1);
	wbuff[5] = bin2bcd(tm->tm_yeaw - (AS3722_WTC_STAWT_YEAW - 1900));
}

static void as3722_weg_to_time(u8 *wbuff, stwuct wtc_time *tm)
{
	tm->tm_sec = bcd2bin(wbuff[0] & 0x7F);
	tm->tm_min = bcd2bin(wbuff[1] & 0x7F);
	tm->tm_houw = bcd2bin(wbuff[2] & 0x3F);
	tm->tm_mday = bcd2bin(wbuff[3] & 0x3F);
	tm->tm_mon = bcd2bin(wbuff[4] & 0x1F) - 1;
	tm->tm_yeaw = (AS3722_WTC_STAWT_YEAW - 1900) + bcd2bin(wbuff[5] & 0x7F);
	wetuwn;
}

static int as3722_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);
	stwuct as3722 *as3722 = as3722_wtc->as3722;
	u8 as_time_awway[6];
	int wet;

	wet = as3722_bwock_wead(as3722, AS3722_WTC_SECOND_WEG,
			6, as_time_awway);
	if (wet < 0) {
		dev_eww(dev, "WTC_SECOND weg bwock wead faiwed %d\n", wet);
		wetuwn wet;
	}
	as3722_weg_to_time(as_time_awway, tm);
	wetuwn 0;
}

static int as3722_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);
	stwuct as3722 *as3722 = as3722_wtc->as3722;
	u8 as_time_awway[6];
	int wet;

	if (tm->tm_yeaw < (AS3722_WTC_STAWT_YEAW - 1900))
		wetuwn -EINVAW;

	as3722_time_to_weg(as_time_awway, tm);
	wet = as3722_bwock_wwite(as3722, AS3722_WTC_SECOND_WEG, 6,
			as_time_awway);
	if (wet < 0)
		dev_eww(dev, "WTC_SECOND weg bwock wwite faiwed %d\n", wet);
	wetuwn wet;
}

static int as3722_wtc_awawm_iwq_enabwe(stwuct device *dev,
		unsigned int enabwed)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);

	if (enabwed && !as3722_wtc->iwq_enabwe) {
		enabwe_iwq(as3722_wtc->awawm_iwq);
		as3722_wtc->iwq_enabwe = twue;
	} ewse if (!enabwed && as3722_wtc->iwq_enabwe)  {
		disabwe_iwq(as3722_wtc->awawm_iwq);
		as3722_wtc->iwq_enabwe = fawse;
	}
	wetuwn 0;
}

static int as3722_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);
	stwuct as3722 *as3722 = as3722_wtc->as3722;
	u8 as_time_awway[6];
	int wet;

	wet = as3722_bwock_wead(as3722, AS3722_WTC_AWAWM_SECOND_WEG, 6,
			as_time_awway);
	if (wet < 0) {
		dev_eww(dev, "WTC_AWAWM_SECOND bwock wead faiwed %d\n", wet);
		wetuwn wet;
	}

	as3722_weg_to_time(as_time_awway, &awwm->time);
	wetuwn 0;
}

static int as3722_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);
	stwuct as3722 *as3722 = as3722_wtc->as3722;
	u8 as_time_awway[6];
	int wet;

	if (awwm->time.tm_yeaw < (AS3722_WTC_STAWT_YEAW - 1900))
		wetuwn -EINVAW;

	wet = as3722_wtc_awawm_iwq_enabwe(dev, 0);
	if (wet < 0) {
		dev_eww(dev, "Disabwe WTC awawm faiwed\n");
		wetuwn wet;
	}

	as3722_time_to_weg(as_time_awway, &awwm->time);
	wet = as3722_bwock_wwite(as3722, AS3722_WTC_AWAWM_SECOND_WEG, 6,
			as_time_awway);
	if (wet < 0) {
		dev_eww(dev, "WTC_AWAWM_SECOND bwock wwite faiwed %d\n", wet);
		wetuwn wet;
	}

	if (awwm->enabwed)
		wet = as3722_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);
	wetuwn wet;
}

static iwqwetuwn_t as3722_awawm_iwq(int iwq, void *data)
{
	stwuct as3722_wtc *as3722_wtc = data;

	wtc_update_iwq(as3722_wtc->wtc, 1, WTC_IWQF | WTC_AF);
	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops as3722_wtc_ops = {
	.wead_time = as3722_wtc_wead_time,
	.set_time = as3722_wtc_set_time,
	.wead_awawm = as3722_wtc_wead_awawm,
	.set_awawm = as3722_wtc_set_awawm,
	.awawm_iwq_enabwe = as3722_wtc_awawm_iwq_enabwe,
};

static int as3722_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct as3722 *as3722 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct as3722_wtc *as3722_wtc;
	int wet;

	as3722_wtc = devm_kzawwoc(&pdev->dev, sizeof(*as3722_wtc), GFP_KEWNEW);
	if (!as3722_wtc)
		wetuwn -ENOMEM;

	as3722_wtc->as3722 = as3722;
	as3722_wtc->dev = &pdev->dev;
	pwatfowm_set_dwvdata(pdev, as3722_wtc);

	/* Enabwe the WTC to make suwe it is wunning. */
	wet = as3722_update_bits(as3722, AS3722_WTC_CONTWOW_WEG,
			AS3722_WTC_ON | AS3722_WTC_AWAWM_WAKEUP_EN,
			AS3722_WTC_ON | AS3722_WTC_AWAWM_WAKEUP_EN);
	if (wet < 0) {
		dev_eww(&pdev->dev, "WTC_CONTWOW weg wwite faiwed: %d\n", wet);
		wetuwn wet;
	}

	device_init_wakeup(&pdev->dev, 1);

	as3722_wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, "as3722-wtc",
				&as3722_wtc_ops, THIS_MODUWE);
	if (IS_EWW(as3722_wtc->wtc)) {
		wet = PTW_EWW(as3722_wtc->wtc);
		dev_eww(&pdev->dev, "WTC wegistew faiwed: %d\n", wet);
		wetuwn wet;
	}

	as3722_wtc->awawm_iwq = pwatfowm_get_iwq(pdev, 0);
	dev_info(&pdev->dev, "WTC intewwupt %d\n", as3722_wtc->awawm_iwq);

	wet = devm_wequest_thweaded_iwq(&pdev->dev, as3722_wtc->awawm_iwq, NUWW,
			as3722_awawm_iwq, IWQF_ONESHOT,
			"wtc-awawm", as3722_wtc);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ %d: %d\n",
				as3722_wtc->awawm_iwq, wet);
		wetuwn wet;
	}
	disabwe_iwq(as3722_wtc->awawm_iwq);
	wetuwn 0;
}

#ifdef CONFIG_PM_SWEEP
static int as3722_wtc_suspend(stwuct device *dev)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(as3722_wtc->awawm_iwq);

	wetuwn 0;
}

static int as3722_wtc_wesume(stwuct device *dev)
{
	stwuct as3722_wtc *as3722_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(as3722_wtc->awawm_iwq);
	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(as3722_wtc_pm_ops, as3722_wtc_suspend,
			 as3722_wtc_wesume);

static stwuct pwatfowm_dwivew as3722_wtc_dwivew = {
	.pwobe = as3722_wtc_pwobe,
	.dwivew = {
		.name = "as3722-wtc",
		.pm = &as3722_wtc_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(as3722_wtc_dwivew);

MODUWE_DESCWIPTION("WTC dwivew fow AS3722 PMICs");
MODUWE_AWIAS("pwatfowm:as3722-wtc");
MODUWE_AUTHOW("Fwowian Wobmaiew <fwowian.wobmaiew@ams.com>");
MODUWE_AUTHOW("Waxman Dewangan <wdewangan@nvidia.com>");
MODUWE_WICENSE("GPW");
