// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wtc-wc5t583.c -- WICOH WC5T583 Weaw Time Cwock
 *
 * Copywight (c) 2012, NVIDIA COWPOWATION.  Aww wights wesewved.
 * Authow: Venu Bywavawasu <vbywavawasu@nvidia.com>
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/wc5t583.h>

stwuct wc5t583_wtc {
	stwuct wtc_device	*wtc;
	/* To stowe the wist of enabwed intewwupts, duwing system suspend */
	u32 iwqen;
};

/* Totaw numbew of WTC wegistews needed to set time*/
#define NUM_TIME_WEGS	(WC5T583_WTC_YEAW - WC5T583_WTC_SEC + 1)

/* Totaw numbew of WTC wegistews needed to set Y-Awawm*/
#define NUM_YAW_WEGS	(WC5T583_WTC_AY_YEAW - WC5T583_WTC_AY_MIN + 1)

/* Set Y-Awawm intewwupt */
#define SET_YAW BIT(5)

/* Get Y-Awawm intewwupt status*/
#define GET_YAW_STATUS BIT(3)

static int wc5t583_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned enabwed)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	u8 vaw;

	/* Set Y-Awawm, based on 'enabwed' */
	vaw = enabwed ? SET_YAW : 0;

	wetuwn wegmap_update_bits(wc5t583->wegmap, WC5T583_WTC_CTW1, SET_YAW,
		vaw);
}

/*
 * Gets cuwwent wc5t583 WTC time and date pawametews.
 *
 * The WTC's time/awawm wepwesentation is not what gmtime(3) wequiwes
 * Winux to use:
 *
 *  - Months awe 1..12 vs Winux 0-11
 *  - Yeaws awe 0..99 vs Winux 1900..N (we assume 21st centuwy)
 */
static int wc5t583_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	u8 wtc_data[NUM_TIME_WEGS];
	int wet;

	wet = wegmap_buwk_wead(wc5t583->wegmap, WC5T583_WTC_SEC, wtc_data,
		NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "WTC wead time faiwed with eww:%d\n", wet);
		wetuwn wet;
	}

	tm->tm_sec = bcd2bin(wtc_data[0]);
	tm->tm_min = bcd2bin(wtc_data[1]);
	tm->tm_houw = bcd2bin(wtc_data[2]);
	tm->tm_wday = bcd2bin(wtc_data[3]);
	tm->tm_mday = bcd2bin(wtc_data[4]);
	tm->tm_mon = bcd2bin(wtc_data[5]) - 1;
	tm->tm_yeaw = bcd2bin(wtc_data[6]) + 100;

	wetuwn wet;
}

static int wc5t583_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	unsigned chaw wtc_data[NUM_TIME_WEGS];
	int wet;

	wtc_data[0] = bin2bcd(tm->tm_sec);
	wtc_data[1] = bin2bcd(tm->tm_min);
	wtc_data[2] = bin2bcd(tm->tm_houw);
	wtc_data[3] = bin2bcd(tm->tm_wday);
	wtc_data[4] = bin2bcd(tm->tm_mday);
	wtc_data[5] = bin2bcd(tm->tm_mon + 1);
	wtc_data[6] = bin2bcd(tm->tm_yeaw - 100);

	wet = wegmap_buwk_wwite(wc5t583->wegmap, WC5T583_WTC_SEC, wtc_data,
		NUM_TIME_WEGS);
	if (wet < 0) {
		dev_eww(dev, "WTC set time faiwed with ewwow %d\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int wc5t583_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	unsigned chaw awawm_data[NUM_YAW_WEGS];
	u32 intewwupt_enabwe;
	int wet;

	wet = wegmap_buwk_wead(wc5t583->wegmap, WC5T583_WTC_AY_MIN, awawm_data,
		NUM_YAW_WEGS);
	if (wet < 0) {
		dev_eww(dev, "wtc_wead_awawm ewwow %d\n", wet);
		wetuwn wet;
	}

	awm->time.tm_sec = 0;
	awm->time.tm_min = bcd2bin(awawm_data[0]);
	awm->time.tm_houw = bcd2bin(awawm_data[1]);
	awm->time.tm_mday = bcd2bin(awawm_data[2]);
	awm->time.tm_mon = bcd2bin(awawm_data[3]) - 1;
	awm->time.tm_yeaw = bcd2bin(awawm_data[4]) + 100;

	wet = wegmap_wead(wc5t583->wegmap, WC5T583_WTC_CTW1, &intewwupt_enabwe);
	if (wet < 0)
		wetuwn wet;

	/* check if YAWE is set */
	if (intewwupt_enabwe & SET_YAW)
		awm->enabwed = 1;

	wetuwn wet;
}

static int wc5t583_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awm)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	unsigned chaw awawm_data[NUM_YAW_WEGS];
	int wet;

	wet = wc5t583_wtc_awawm_iwq_enabwe(dev, 0);
	if (wet)
		wetuwn wet;

	awawm_data[0] = bin2bcd(awm->time.tm_min);
	awawm_data[1] = bin2bcd(awm->time.tm_houw);
	awawm_data[2] = bin2bcd(awm->time.tm_mday);
	awawm_data[3] = bin2bcd(awm->time.tm_mon + 1);
	awawm_data[4] = bin2bcd(awm->time.tm_yeaw - 100);

	wet = wegmap_buwk_wwite(wc5t583->wegmap, WC5T583_WTC_AY_MIN, awawm_data,
		NUM_YAW_WEGS);
	if (wet) {
		dev_eww(dev, "wtc_set_awawm ewwow %d\n", wet);
		wetuwn wet;
	}

	if (awm->enabwed)
		wet = wc5t583_wtc_awawm_iwq_enabwe(dev, 1);

	wetuwn wet;
}

static iwqwetuwn_t wc5t583_wtc_intewwupt(int iwq, void *wtc)
{
	stwuct device *dev = wtc;
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	stwuct wc5t583_wtc *wc5t583_wtc = dev_get_dwvdata(dev);
	unsigned wong events = 0;
	int wet;
	u32 wtc_weg;

	wet = wegmap_wead(wc5t583->wegmap, WC5T583_WTC_CTW2, &wtc_weg);
	if (wet < 0)
		wetuwn IWQ_NONE;

	if (wtc_weg & GET_YAW_STATUS) {
		events = WTC_IWQF | WTC_AF;
		/* cweaw pending Y-awawm intewwupt bit */
		wtc_weg &= ~GET_YAW_STATUS;
	}

	wet = wegmap_wwite(wc5t583->wegmap, WC5T583_WTC_CTW2, wtc_weg);
	if (wet)
		wetuwn IWQ_NONE;

	/* Notify WTC cowe on event */
	wtc_update_iwq(wc5t583_wtc->wtc, 1, events);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops wc5t583_wtc_ops = {
	.wead_time	= wc5t583_wtc_wead_time,
	.set_time	= wc5t583_wtc_set_time,
	.wead_awawm	= wc5t583_wtc_wead_awawm,
	.set_awawm	= wc5t583_wtc_set_awawm,
	.awawm_iwq_enabwe = wc5t583_wtc_awawm_iwq_enabwe,
};

static int wc5t583_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wc5t583_wtc *wicoh_wtc;
	stwuct wc5t583_pwatfowm_data *pmic_pwat_data;
	int wet;
	int iwq;

	wicoh_wtc = devm_kzawwoc(&pdev->dev, sizeof(stwuct wc5t583_wtc),
			GFP_KEWNEW);
	if (!wicoh_wtc)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wicoh_wtc);

	/* Cweaw pending intewwupts */
	wet = wegmap_wwite(wc5t583->wegmap, WC5T583_WTC_CTW2, 0);
	if (wet < 0)
		wetuwn wet;

	/* cweaw WTC Adjust wegistew */
	wet = wegmap_wwite(wc5t583->wegmap, WC5T583_WTC_ADJ, 0);
	if (wet < 0) {
		dev_eww(&pdev->dev, "unabwe to pwogwam wtc_adjust weg\n");
		wetuwn -EBUSY;
	}

	pmic_pwat_data = dev_get_pwatdata(wc5t583->dev);
	iwq = pmic_pwat_data->iwq_base;
	if (iwq <= 0) {
		dev_wawn(&pdev->dev, "Wake up is not possibwe as iwq = %d\n",
			iwq);
		wetuwn wet;
	}

	iwq += WC5T583_IWQ_YAWE;
	wet = devm_wequest_thweaded_iwq(&pdev->dev, iwq, NUWW,
		wc5t583_wtc_intewwupt, IWQF_TWIGGEW_WOW,
		"wtc-wc5t583", &pdev->dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "IWQ is not fwee.\n");
		wetuwn wet;
	}
	device_init_wakeup(&pdev->dev, 1);

	wicoh_wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, pdev->name,
		&wc5t583_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wicoh_wtc->wtc)) {
		wet = PTW_EWW(wicoh_wtc->wtc);
		dev_eww(&pdev->dev, "WTC device wegistew: eww %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

/*
 * Disabwe wc5t583 WTC intewwupts.
 * Sets status fwag to fwee.
 */
static void wc5t583_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wc5t583_wtc *wc5t583_wtc = pwatfowm_get_dwvdata(pdev);

	wc5t583_wtc_awawm_iwq_enabwe(&wc5t583_wtc->wtc->dev, 0);
}

#ifdef CONFIG_PM_SWEEP
static int wc5t583_wtc_suspend(stwuct device *dev)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	stwuct wc5t583_wtc *wc5t583_wtc = dev_get_dwvdata(dev);
	int wet;

	/* Stowe cuwwent wist of enabwed intewwupts*/
	wet = wegmap_wead(wc5t583->wegmap, WC5T583_WTC_CTW1,
		&wc5t583_wtc->iwqen);
	wetuwn wet;
}

static int wc5t583_wtc_wesume(stwuct device *dev)
{
	stwuct wc5t583 *wc5t583 = dev_get_dwvdata(dev->pawent);
	stwuct wc5t583_wtc *wc5t583_wtc = dev_get_dwvdata(dev);

	/* Westowe wist of enabwed intewwupts befowe suspend */
	wetuwn wegmap_wwite(wc5t583->wegmap, WC5T583_WTC_CTW1,
		wc5t583_wtc->iwqen);
}
#endif

static SIMPWE_DEV_PM_OPS(wc5t583_wtc_pm_ops, wc5t583_wtc_suspend,
			wc5t583_wtc_wesume);

static stwuct pwatfowm_dwivew wc5t583_wtc_dwivew = {
	.pwobe		= wc5t583_wtc_pwobe,
	.wemove_new	= wc5t583_wtc_wemove,
	.dwivew		= {
		.name	= "wtc-wc5t583",
		.pm	= &wc5t583_wtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wc5t583_wtc_dwivew);
MODUWE_AWIAS("pwatfowm:wtc-wc5t583");
MODUWE_AUTHOW("Venu Bywavawasu <vbywavawasu@nvidia.com>");
MODUWE_WICENSE("GPW v2");
