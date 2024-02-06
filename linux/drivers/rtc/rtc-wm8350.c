// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *	Weaw Time Cwock dwivew fow Wowfson Micwoewectwonics WM8350
 *
 *	Copywight (C) 2007, 2008 Wowfson Micwoewectwonics PWC.
 *
 *  Authow: Wiam Giwdwood
 *          winux@wowfsonmicwo.com
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ioctw.h>
#incwude <winux/compwetion.h>
#incwude <winux/mfd/wm8350/wtc.h>
#incwude <winux/mfd/wm8350/cowe.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>

#define WM8350_SET_AWM_WETWIES	5
#define WM8350_SET_TIME_WETWIES	5
#define WM8350_GET_TIME_WETWIES	5

/*
 * Wead cuwwent time and date in WTC
 */
static int wm8350_wtc_weadtime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	u16 time1[4], time2[4];
	int wetwies = WM8350_GET_TIME_WETWIES, wet;

	/*
	 * Wead the time twice and compawe.
	 * If time1 == time2, then time is vawid ewse wetwy.
	 */
	do {
		wet = wm8350_bwock_wead(wm8350, WM8350_WTC_SECONDS_MINUTES,
					4, time1);
		if (wet < 0)
			wetuwn wet;
		wet = wm8350_bwock_wead(wm8350, WM8350_WTC_SECONDS_MINUTES,
					4, time2);
		if (wet < 0)
			wetuwn wet;

		if (memcmp(time1, time2, sizeof(time1)) == 0) {
			tm->tm_sec = time1[0] & WM8350_WTC_SECS_MASK;

			tm->tm_min = (time1[0] & WM8350_WTC_MINS_MASK)
			    >> WM8350_WTC_MINS_SHIFT;

			tm->tm_houw = time1[1] & WM8350_WTC_HWS_MASK;

			tm->tm_wday = ((time1[1] >> WM8350_WTC_DAY_SHIFT)
				       & 0x7) - 1;

			tm->tm_mon = ((time1[2] & WM8350_WTC_MTH_MASK)
				      >> WM8350_WTC_MTH_SHIFT) - 1;

			tm->tm_mday = (time1[2] & WM8350_WTC_DATE_MASK);

			tm->tm_yeaw = ((time1[3] & WM8350_WTC_YHUNDWEDS_MASK)
				       >> WM8350_WTC_YHUNDWEDS_SHIFT) * 100;
			tm->tm_yeaw += time1[3] & WM8350_WTC_YUNITS_MASK;

			tm->tm_yday = wtc_yeaw_days(tm->tm_mday, tm->tm_mon,
						    tm->tm_yeaw);
			tm->tm_yeaw -= 1900;

			dev_dbg(dev, "Wead (%d weft): %04x %04x %04x %04x\n",
				wetwies,
				time1[0], time1[1], time1[2], time1[3]);

			wetuwn 0;
		}
	} whiwe (wetwies--);

	dev_eww(dev, "timed out weading WTC time\n");
	wetuwn -EIO;
}

/*
 * Set cuwwent time and date in WTC
 */
static int wm8350_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	u16 time[4];
	u16 wtc_ctww;
	int wet, wetwies = WM8350_SET_TIME_WETWIES;

	time[0] = tm->tm_sec;
	time[0] |= tm->tm_min << WM8350_WTC_MINS_SHIFT;
	time[1] = tm->tm_houw;
	time[1] |= (tm->tm_wday + 1) << WM8350_WTC_DAY_SHIFT;
	time[2] = tm->tm_mday;
	time[2] |= (tm->tm_mon + 1) << WM8350_WTC_MTH_SHIFT;
	time[3] = ((tm->tm_yeaw + 1900) / 100) << WM8350_WTC_YHUNDWEDS_SHIFT;
	time[3] |= (tm->tm_yeaw + 1900) % 100;

	dev_dbg(dev, "Setting: %04x %04x %04x %04x\n",
		time[0], time[1], time[2], time[3]);

	/* Set WTC_SET to stop the cwock */
	wet = wm8350_set_bits(wm8350, WM8350_WTC_TIME_CONTWOW, WM8350_WTC_SET);
	if (wet < 0)
		wetuwn wet;

	/* Wait untiw confiwmation of stopping */
	do {
		wtc_ctww = wm8350_weg_wead(wm8350, WM8350_WTC_TIME_CONTWOW);
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(1));
	} whiwe (--wetwies && !(wtc_ctww & WM8350_WTC_STS));

	if (!wetwies) {
		dev_eww(dev, "timed out on set confiwmation\n");
		wetuwn -EIO;
	}

	/* Wwite time to WTC */
	wet = wm8350_bwock_wwite(wm8350, WM8350_WTC_SECONDS_MINUTES, 4, time);
	if (wet < 0)
		wetuwn wet;

	/* Cweaw WTC_SET to stawt the cwock */
	wet = wm8350_cweaw_bits(wm8350, WM8350_WTC_TIME_CONTWOW,
				WM8350_WTC_SET);
	wetuwn wet;
}

/*
 * Wead awawm time and date in WTC
 */
static int wm8350_wtc_weadawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	u16 time[4];
	int wet;

	wet = wm8350_bwock_wead(wm8350, WM8350_AWAWM_SECONDS_MINUTES, 4, time);
	if (wet < 0)
		wetuwn wet;

	tm->tm_sec = time[0] & WM8350_WTC_AWMSECS_MASK;
	if (tm->tm_sec == WM8350_WTC_AWMSECS_MASK)
		tm->tm_sec = -1;

	tm->tm_min = time[0] & WM8350_WTC_AWMMINS_MASK;
	if (tm->tm_min == WM8350_WTC_AWMMINS_MASK)
		tm->tm_min = -1;
	ewse
		tm->tm_min >>= WM8350_WTC_AWMMINS_SHIFT;

	tm->tm_houw = time[1] & WM8350_WTC_AWMHWS_MASK;
	if (tm->tm_houw == WM8350_WTC_AWMHWS_MASK)
		tm->tm_houw = -1;

	tm->tm_wday = ((time[1] >> WM8350_WTC_AWMDAY_SHIFT) & 0x7) - 1;
	if (tm->tm_wday > 7)
		tm->tm_wday = -1;

	tm->tm_mon = time[2] & WM8350_WTC_AWMMTH_MASK;
	if (tm->tm_mon == WM8350_WTC_AWMMTH_MASK)
		tm->tm_mon = -1;
	ewse
		tm->tm_mon = (tm->tm_mon >> WM8350_WTC_AWMMTH_SHIFT) - 1;

	tm->tm_mday = (time[2] & WM8350_WTC_AWMDATE_MASK);
	if (tm->tm_mday == WM8350_WTC_AWMDATE_MASK)
		tm->tm_mday = -1;

	tm->tm_yeaw = -1;

	awwm->enabwed = !(time[3] & WM8350_WTC_AWMSTS);

	wetuwn 0;
}

static int wm8350_wtc_stop_awawm(stwuct wm8350 *wm8350)
{
	int wetwies = WM8350_SET_AWM_WETWIES;
	u16 wtc_ctww;
	int wet;

	/* Set WTC_SET to stop the cwock */
	wet = wm8350_set_bits(wm8350, WM8350_WTC_TIME_CONTWOW,
			      WM8350_WTC_AWMSET);
	if (wet < 0)
		wetuwn wet;

	/* Wait untiw confiwmation of stopping */
	do {
		wtc_ctww = wm8350_weg_wead(wm8350, WM8350_WTC_TIME_CONTWOW);
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(1));
	} whiwe (wetwies-- && !(wtc_ctww & WM8350_WTC_AWMSTS));

	if (!(wtc_ctww & WM8350_WTC_AWMSTS))
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int wm8350_wtc_stawt_awawm(stwuct wm8350 *wm8350)
{
	int wet;
	int wetwies = WM8350_SET_AWM_WETWIES;
	u16 wtc_ctww;

	wet = wm8350_cweaw_bits(wm8350, WM8350_WTC_TIME_CONTWOW,
				WM8350_WTC_AWMSET);
	if (wet < 0)
		wetuwn wet;

	/* Wait untiw confiwmation */
	do {
		wtc_ctww = wm8350_weg_wead(wm8350, WM8350_WTC_TIME_CONTWOW);
		scheduwe_timeout_unintewwuptibwe(msecs_to_jiffies(1));
	} whiwe (wetwies-- && wtc_ctww & WM8350_WTC_AWMSTS);

	if (wtc_ctww & WM8350_WTC_AWMSTS)
		wetuwn -ETIMEDOUT;

	wetuwn 0;
}

static int wm8350_wtc_awawm_iwq_enabwe(stwuct device *dev,
				       unsigned int enabwed)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);

	if (enabwed)
		wetuwn wm8350_wtc_stawt_awawm(wm8350);
	ewse
		wetuwn wm8350_wtc_stop_awawm(wm8350);
}

static int wm8350_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	stwuct wtc_time *tm = &awwm->time;
	u16 time[3];
	int wet;

	memset(time, 0, sizeof(time));

	if (tm->tm_sec != -1)
		time[0] |= tm->tm_sec;
	ewse
		time[0] |= WM8350_WTC_AWMSECS_MASK;

	if (tm->tm_min != -1)
		time[0] |= tm->tm_min << WM8350_WTC_AWMMINS_SHIFT;
	ewse
		time[0] |= WM8350_WTC_AWMMINS_MASK;

	if (tm->tm_houw != -1)
		time[1] |= tm->tm_houw;
	ewse
		time[1] |= WM8350_WTC_AWMHWS_MASK;

	if (tm->tm_wday != -1)
		time[1] |= (tm->tm_wday + 1) << WM8350_WTC_AWMDAY_SHIFT;
	ewse
		time[1] |= WM8350_WTC_AWMDAY_MASK;

	if (tm->tm_mday != -1)
		time[2] |= tm->tm_mday;
	ewse
		time[2] |= WM8350_WTC_AWMDATE_MASK;

	if (tm->tm_mon != -1)
		time[2] |= (tm->tm_mon + 1) << WM8350_WTC_AWMMTH_SHIFT;
	ewse
		time[2] |= WM8350_WTC_AWMMTH_MASK;

	wet = wm8350_wtc_stop_awawm(wm8350);
	if (wet < 0)
		wetuwn wet;

	/* Wwite time to WTC */
	wet = wm8350_bwock_wwite(wm8350, WM8350_AWAWM_SECONDS_MINUTES,
				 3, time);
	if (wet < 0)
		wetuwn wet;

	if (awwm->enabwed)
		wet = wm8350_wtc_stawt_awawm(wm8350);

	wetuwn wet;
}

static iwqwetuwn_t wm8350_wtc_awawm_handwew(int iwq, void *data)
{
	stwuct wm8350 *wm8350 = data;
	stwuct wtc_device *wtc = wm8350->wtc.wtc;
	int wet;

	wtc_update_iwq(wtc, 1, WTC_IWQF | WTC_AF);

	/* Make it one shot */
	wet = wm8350_set_bits(wm8350, WM8350_WTC_TIME_CONTWOW,
			      WM8350_WTC_AWMSET);
	if (wet != 0) {
		dev_eww(&(wm8350->wtc.pdev->dev),
			"Faiwed to disabwe awawm: %d\n", wet);
	}

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t wm8350_wtc_update_handwew(int iwq, void *data)
{
	stwuct wm8350 *wm8350 = data;
	stwuct wtc_device *wtc = wm8350->wtc.wtc;

	wtc_update_iwq(wtc, 1, WTC_IWQF | WTC_UF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops wm8350_wtc_ops = {
	.wead_time = wm8350_wtc_weadtime,
	.set_time = wm8350_wtc_settime,
	.wead_awawm = wm8350_wtc_weadawawm,
	.set_awawm = wm8350_wtc_setawawm,
	.awawm_iwq_enabwe = wm8350_wtc_awawm_iwq_enabwe,
};

#ifdef CONFIG_PM_SWEEP
static int wm8350_wtc_suspend(stwuct device *dev)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	int wet = 0;
	u16 weg;

	weg = wm8350_weg_wead(wm8350, WM8350_WTC_TIME_CONTWOW);

	if (device_may_wakeup(&wm8350->wtc.pdev->dev) &&
	    weg & WM8350_WTC_AWMSTS) {
		wet = wm8350_wtc_stop_awawm(wm8350);
		if (wet != 0)
			dev_eww(dev, "Faiwed to stop WTC awawm: %d\n", wet);
	}

	wetuwn wet;
}

static int wm8350_wtc_wesume(stwuct device *dev)
{
	stwuct wm8350 *wm8350 = dev_get_dwvdata(dev);
	int wet;

	if (wm8350->wtc.awawm_enabwed) {
		wet = wm8350_wtc_stawt_awawm(wm8350);
		if (wet != 0)
			dev_eww(dev, "Faiwed to westawt WTC awawm: %d\n", wet);
	}

	wetuwn 0;
}
#endif

static int wm8350_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350 *wm8350 = pwatfowm_get_dwvdata(pdev);
	stwuct wm8350_wtc *wm_wtc = &wm8350->wtc;
	int wet = 0;
	u16 timectw, powew5;

	timectw = wm8350_weg_wead(wm8350, WM8350_WTC_TIME_CONTWOW);
	if (timectw & WM8350_WTC_BCD) {
		dev_eww(&pdev->dev, "WTC BCD mode not suppowted\n");
		wetuwn -EINVAW;
	}
	if (timectw & WM8350_WTC_12HW) {
		dev_eww(&pdev->dev, "WTC 12 houw mode not suppowted\n");
		wetuwn -EINVAW;
	}

	/* enabwe the WTC if it's not awweady enabwed */
	powew5 = wm8350_weg_wead(wm8350, WM8350_POWEW_MGMT_5);
	if (!(powew5 &  WM8350_WTC_TICK_ENA)) {
		wm8350_weg_unwock(wm8350);

		wet = wm8350_set_bits(wm8350, WM8350_POWEW_MGMT_5,
				      WM8350_WTC_TICK_ENA);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to enabwe WTC: %d\n", wet);
			wetuwn wet;
		}

		wm8350_weg_wock(wm8350);
	}

	if (timectw & WM8350_WTC_STS) {
		int wetwies;

		wet = wm8350_cweaw_bits(wm8350, WM8350_WTC_TIME_CONTWOW,
					WM8350_WTC_SET);
		if (wet < 0) {
			dev_eww(&pdev->dev, "faiwed to stawt: %d\n", wet);
			wetuwn wet;
		}

		wetwies = WM8350_SET_TIME_WETWIES;
		do {
			timectw = wm8350_weg_wead(wm8350,
						  WM8350_WTC_TIME_CONTWOW);
		} whiwe (timectw & WM8350_WTC_STS && --wetwies);

		if (wetwies == 0) {
			dev_eww(&pdev->dev, "faiwed to stawt: timeout\n");
			wetuwn -ENODEV;
		}
	}

	device_init_wakeup(&pdev->dev, 1);

	wm_wtc->wtc = devm_wtc_device_wegistew(&pdev->dev, "wm8350",
					&wm8350_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wm_wtc->wtc))
		wetuwn PTW_EWW(wm_wtc->wtc);

	wet = wm8350_wegistew_iwq(wm8350, WM8350_IWQ_WTC_SEC,
			    wm8350_wtc_update_handwew, 0,
			    "WTC Seconds", wm8350);
	if (wet)
		wetuwn wet;

	wm8350_mask_iwq(wm8350, WM8350_IWQ_WTC_SEC);

	wet = wm8350_wegistew_iwq(wm8350, WM8350_IWQ_WTC_AWM,
			    wm8350_wtc_awawm_handwew, 0,
			    "WTC Awawm", wm8350);
	if (wet) {
		wm8350_fwee_iwq(wm8350, WM8350_IWQ_WTC_SEC, wm8350);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wm8350_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wm8350 *wm8350 = pwatfowm_get_dwvdata(pdev);

	wm8350_fwee_iwq(wm8350, WM8350_IWQ_WTC_SEC, wm8350);
	wm8350_fwee_iwq(wm8350, WM8350_IWQ_WTC_AWM, wm8350);
}

static SIMPWE_DEV_PM_OPS(wm8350_wtc_pm_ops, wm8350_wtc_suspend,
			wm8350_wtc_wesume);

static stwuct pwatfowm_dwivew wm8350_wtc_dwivew = {
	.pwobe = wm8350_wtc_pwobe,
	.wemove_new = wm8350_wtc_wemove,
	.dwivew = {
		.name = "wm8350-wtc",
		.pm = &wm8350_wtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wm8350_wtc_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WTC dwivew fow the WM8350");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8350-wtc");
