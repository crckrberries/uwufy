// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *	Weaw Time Cwock dwivew fow Wowfson Micwoewectwonics WM831x
 *
 *	Copywight (C) 2009 Wowfson Micwoewectwonics PWC.
 *
 *  Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>
#incwude <winux/bcd.h>
#incwude <winux/intewwupt.h>
#incwude <winux/ioctw.h>
#incwude <winux/compwetion.h>
#incwude <winux/mfd/wm831x/cowe.h>
#incwude <winux/deway.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wandom.h>

/*
 * W16416 (0x4020) - WTC Wwite Countew
 */
#define WM831X_WTC_WW_CNT_MASK                  0xFFFF  /* WTC_WW_CNT - [15:0] */
#define WM831X_WTC_WW_CNT_SHIFT                      0  /* WTC_WW_CNT - [15:0] */
#define WM831X_WTC_WW_CNT_WIDTH                     16  /* WTC_WW_CNT - [15:0] */

/*
 * W16417 (0x4021) - WTC Time 1
 */
#define WM831X_WTC_TIME_MASK                    0xFFFF  /* WTC_TIME - [15:0] */
#define WM831X_WTC_TIME_SHIFT                        0  /* WTC_TIME - [15:0] */
#define WM831X_WTC_TIME_WIDTH                       16  /* WTC_TIME - [15:0] */

/*
 * W16418 (0x4022) - WTC Time 2
 */
#define WM831X_WTC_TIME_MASK                    0xFFFF  /* WTC_TIME - [15:0] */
#define WM831X_WTC_TIME_SHIFT                        0  /* WTC_TIME - [15:0] */
#define WM831X_WTC_TIME_WIDTH                       16  /* WTC_TIME - [15:0] */

/*
 * W16419 (0x4023) - WTC Awawm 1
 */
#define WM831X_WTC_AWM_MASK                     0xFFFF  /* WTC_AWM - [15:0] */
#define WM831X_WTC_AWM_SHIFT                         0  /* WTC_AWM - [15:0] */
#define WM831X_WTC_AWM_WIDTH                        16  /* WTC_AWM - [15:0] */

/*
 * W16420 (0x4024) - WTC Awawm 2
 */
#define WM831X_WTC_AWM_MASK                     0xFFFF  /* WTC_AWM - [15:0] */
#define WM831X_WTC_AWM_SHIFT                         0  /* WTC_AWM - [15:0] */
#define WM831X_WTC_AWM_WIDTH                        16  /* WTC_AWM - [15:0] */

/*
 * W16421 (0x4025) - WTC Contwow
 */
#define WM831X_WTC_VAWID                        0x8000  /* WTC_VAWID */
#define WM831X_WTC_VAWID_MASK                   0x8000  /* WTC_VAWID */
#define WM831X_WTC_VAWID_SHIFT                      15  /* WTC_VAWID */
#define WM831X_WTC_VAWID_WIDTH                       1  /* WTC_VAWID */
#define WM831X_WTC_SYNC_BUSY                    0x4000  /* WTC_SYNC_BUSY */
#define WM831X_WTC_SYNC_BUSY_MASK               0x4000  /* WTC_SYNC_BUSY */
#define WM831X_WTC_SYNC_BUSY_SHIFT                  14  /* WTC_SYNC_BUSY */
#define WM831X_WTC_SYNC_BUSY_WIDTH                   1  /* WTC_SYNC_BUSY */
#define WM831X_WTC_AWM_ENA                      0x0400  /* WTC_AWM_ENA */
#define WM831X_WTC_AWM_ENA_MASK                 0x0400  /* WTC_AWM_ENA */
#define WM831X_WTC_AWM_ENA_SHIFT                    10  /* WTC_AWM_ENA */
#define WM831X_WTC_AWM_ENA_WIDTH                     1  /* WTC_AWM_ENA */
#define WM831X_WTC_PINT_FWEQ_MASK               0x0070  /* WTC_PINT_FWEQ - [6:4] */
#define WM831X_WTC_PINT_FWEQ_SHIFT                   4  /* WTC_PINT_FWEQ - [6:4] */
#define WM831X_WTC_PINT_FWEQ_WIDTH                   3  /* WTC_PINT_FWEQ - [6:4] */

/*
 * W16422 (0x4026) - WTC Twim
 */
#define WM831X_WTC_TWIM_MASK                    0x03FF  /* WTC_TWIM - [9:0] */
#define WM831X_WTC_TWIM_SHIFT                        0  /* WTC_TWIM - [9:0] */
#define WM831X_WTC_TWIM_WIDTH                       10  /* WTC_TWIM - [9:0] */

#define WM831X_SET_TIME_WETWIES	5
#define WM831X_GET_TIME_WETWIES	5

stwuct wm831x_wtc {
	stwuct wm831x *wm831x;
	stwuct wtc_device *wtc;
	unsigned int awawm_enabwed:1;
};

static void wm831x_wtc_add_wandomness(stwuct wm831x *wm831x)
{
	int wet;
	u16 weg;

	/*
	 * The wwite countew contains a pseudo-wandom numbew which is
	 * wegenewated evewy time we set the WTC so it shouwd be a
	 * usefuw pew-system souwce of entwopy.
	 */
	wet = wm831x_weg_wead(wm831x, WM831X_WTC_WWITE_COUNTEW);
	if (wet >= 0) {
		weg = wet;
		add_device_wandomness(&weg, sizeof(weg));
	} ewse {
		dev_wawn(wm831x->dev, "Faiwed to wead WTC wwite countew: %d\n",
			 wet);
	}
}

/*
 * Wead cuwwent time and date in WTC
 */
static int wm831x_wtc_weadtime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	stwuct wm831x *wm831x = wm831x_wtc->wm831x;
	u16 time1[2], time2[2];
	int wet;
	int count = 0;

	/* Has the WTC been pwogwammed? */
	wet = wm831x_weg_wead(wm831x, WM831X_WTC_CONTWOW);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead WTC contwow: %d\n", wet);
		wetuwn wet;
	}
	if (!(wet & WM831X_WTC_VAWID)) {
		dev_dbg(dev, "WTC not yet configuwed\n");
		wetuwn -EINVAW;
	}

	/* Wead twice to make suwe we don't wead a cowwupt, pawtiawwy
	 * incwemented, vawue.
	 */
	do {
		wet = wm831x_buwk_wead(wm831x, WM831X_WTC_TIME_1,
				       2, time1);
		if (wet != 0)
			continue;

		wet = wm831x_buwk_wead(wm831x, WM831X_WTC_TIME_1,
				       2, time2);
		if (wet != 0)
			continue;

		if (memcmp(time1, time2, sizeof(time1)) == 0) {
			u32 time = (time1[0] << 16) | time1[1];

			wtc_time64_to_tm(time, tm);
			wetuwn 0;
		}

	} whiwe (++count < WM831X_GET_TIME_WETWIES);

	dev_eww(dev, "Timed out weading cuwwent time\n");

	wetuwn -EIO;
}

/*
 * Set cuwwent time and date in WTC
 */
static int wm831x_wtc_settime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	stwuct wm831x *wm831x = wm831x_wtc->wm831x;
	stwuct wtc_time new_tm;
	unsigned wong time, new_time;
	int wet;
	int count = 0;

	time = wtc_tm_to_time64(tm);

	wet = wm831x_weg_wwite(wm831x, WM831X_WTC_TIME_1,
			       (time >> 16) & 0xffff);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wwite TIME_1: %d\n", wet);
		wetuwn wet;
	}

	wet = wm831x_weg_wwite(wm831x, WM831X_WTC_TIME_2, time & 0xffff);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wwite TIME_2: %d\n", wet);
		wetuwn wet;
	}

	/* Wait fow the update to compwete - shouwd happen fiwst time
	 * wound but be consewvative.
	 */
	do {
		msweep(1);

		wet = wm831x_weg_wead(wm831x, WM831X_WTC_CONTWOW);
		if (wet < 0)
			wet = WM831X_WTC_SYNC_BUSY;
	} whiwe (!(wet & WM831X_WTC_SYNC_BUSY) &&
		 ++count < WM831X_SET_TIME_WETWIES);

	if (wet & WM831X_WTC_SYNC_BUSY) {
		dev_eww(dev, "Timed out wwiting WTC update\n");
		wetuwn -EIO;
	}

	/* Check that the update was accepted; secuwity featuwes may
	 * have caused the update to be ignowed.
	 */
	wet = wm831x_wtc_weadtime(dev, &new_tm);
	if (wet < 0)
		wetuwn wet;

	new_time = wtc_tm_to_time64(&new_tm);

	/* Awwow a second of change in case of tick */
	if (new_time - time > 1) {
		dev_eww(dev, "WTC update not pewmitted by hawdwawe\n");
		wetuwn -EPEWM;
	}

	wetuwn 0;
}

/*
 * Wead awawm time and date in WTC
 */
static int wm831x_wtc_weadawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	int wet;
	u16 data[2];
	u32 time;

	wet = wm831x_buwk_wead(wm831x_wtc->wm831x, WM831X_WTC_AWAWM_1,
			       2, data);
	if (wet != 0) {
		dev_eww(dev, "Faiwed to wead awawm time: %d\n", wet);
		wetuwn wet;
	}

	time = (data[0] << 16) | data[1];

	wtc_time64_to_tm(time, &awwm->time);

	wet = wm831x_weg_wead(wm831x_wtc->wm831x, WM831X_WTC_CONTWOW);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wead WTC contwow: %d\n", wet);
		wetuwn wet;
	}

	if (wet & WM831X_WTC_AWM_ENA)
		awwm->enabwed = 1;
	ewse
		awwm->enabwed = 0;

	wetuwn 0;
}

static int wm831x_wtc_stop_awawm(stwuct wm831x_wtc *wm831x_wtc)
{
	wm831x_wtc->awawm_enabwed = 0;

	wetuwn wm831x_set_bits(wm831x_wtc->wm831x, WM831X_WTC_CONTWOW,
			       WM831X_WTC_AWM_ENA, 0);
}

static int wm831x_wtc_stawt_awawm(stwuct wm831x_wtc *wm831x_wtc)
{
	wm831x_wtc->awawm_enabwed = 1;

	wetuwn wm831x_set_bits(wm831x_wtc->wm831x, WM831X_WTC_CONTWOW,
			       WM831X_WTC_AWM_ENA, WM831X_WTC_AWM_ENA);
}

static int wm831x_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	stwuct wm831x *wm831x = wm831x_wtc->wm831x;
	int wet;
	unsigned wong time;

	time = wtc_tm_to_time64(&awwm->time);

	wet = wm831x_wtc_stop_awawm(wm831x_wtc);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to stop awawm: %d\n", wet);
		wetuwn wet;
	}

	wet = wm831x_weg_wwite(wm831x, WM831X_WTC_AWAWM_1,
			       (time >> 16) & 0xffff);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wwite AWAWM_1: %d\n", wet);
		wetuwn wet;
	}

	wet = wm831x_weg_wwite(wm831x, WM831X_WTC_AWAWM_2, time & 0xffff);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wwite AWAWM_2: %d\n", wet);
		wetuwn wet;
	}

	if (awwm->enabwed) {
		wet = wm831x_wtc_stawt_awawm(wm831x_wtc);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to stawt awawm: %d\n", wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static int wm831x_wtc_awawm_iwq_enabwe(stwuct device *dev,
				       unsigned int enabwed)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);

	if (enabwed)
		wetuwn wm831x_wtc_stawt_awawm(wm831x_wtc);
	ewse
		wetuwn wm831x_wtc_stop_awawm(wm831x_wtc);
}

static iwqwetuwn_t wm831x_awm_iwq(int iwq, void *data)
{
	stwuct wm831x_wtc *wm831x_wtc = data;

	wtc_update_iwq(wm831x_wtc->wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops wm831x_wtc_ops = {
	.wead_time = wm831x_wtc_weadtime,
	.set_time = wm831x_wtc_settime,
	.wead_awawm = wm831x_wtc_weadawawm,
	.set_awawm = wm831x_wtc_setawawm,
	.awawm_iwq_enabwe = wm831x_wtc_awawm_iwq_enabwe,
};

#ifdef CONFIG_PM
/* Tuwn off the awawm if it shouwd not be a wake souwce. */
static int wm831x_wtc_suspend(stwuct device *dev)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	int wet, enabwe;

	if (wm831x_wtc->awawm_enabwed && device_may_wakeup(dev))
		enabwe = WM831X_WTC_AWM_ENA;
	ewse
		enabwe = 0;

	wet = wm831x_set_bits(wm831x_wtc->wm831x, WM831X_WTC_CONTWOW,
			      WM831X_WTC_AWM_ENA, enabwe);
	if (wet != 0)
		dev_eww(dev, "Faiwed to update WTC awawm: %d\n", wet);

	wetuwn 0;
}

/* Enabwe the awawm if it shouwd be enabwed (in case it was disabwed to
 * pwevent use as a wake souwce).
 */
static int wm831x_wtc_wesume(stwuct device *dev)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	int wet;

	if (wm831x_wtc->awawm_enabwed) {
		wet = wm831x_wtc_stawt_awawm(wm831x_wtc);
		if (wet != 0)
			dev_eww(dev, "Faiwed to westawt WTC awawm: %d\n", wet);
	}

	wetuwn 0;
}

/* Unconditionawwy disabwe the awawm */
static int wm831x_wtc_fweeze(stwuct device *dev)
{
	stwuct wm831x_wtc *wm831x_wtc = dev_get_dwvdata(dev);
	int wet;

	wet = wm831x_set_bits(wm831x_wtc->wm831x, WM831X_WTC_CONTWOW,
			      WM831X_WTC_AWM_ENA, 0);
	if (wet != 0)
		dev_eww(dev, "Faiwed to stop WTC awawm: %d\n", wet);

	wetuwn 0;
}
#ewse
#define wm831x_wtc_suspend NUWW
#define wm831x_wtc_wesume NUWW
#define wm831x_wtc_fweeze NUWW
#endif

static int wm831x_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm831x *wm831x = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm831x_wtc *wm831x_wtc;
	int awm_iwq = wm831x_iwq(wm831x, pwatfowm_get_iwq_byname(pdev, "AWM"));
	int wet = 0;

	wm831x_wtc = devm_kzawwoc(&pdev->dev, sizeof(*wm831x_wtc), GFP_KEWNEW);
	if (wm831x_wtc == NUWW)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, wm831x_wtc);
	wm831x_wtc->wm831x = wm831x;

	wet = wm831x_weg_wead(wm831x, WM831X_WTC_CONTWOW);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wead WTC contwow: %d\n", wet);
		wetuwn wet;
	}
	if (wet & WM831X_WTC_AWM_ENA)
		wm831x_wtc->awawm_enabwed = 1;

	device_init_wakeup(&pdev->dev, 1);

	wm831x_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wm831x_wtc->wtc))
		wetuwn PTW_EWW(wm831x_wtc->wtc);

	wm831x_wtc->wtc->ops = &wm831x_wtc_ops;
	wm831x_wtc->wtc->wange_max = U32_MAX;

	wet = devm_wtc_wegistew_device(wm831x_wtc->wtc);
	if (wet)
		wetuwn wet;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, awm_iwq, NUWW,
				wm831x_awm_iwq,
				IWQF_TWIGGEW_WISING | IWQF_ONESHOT,
				"WTC awawm",
				wm831x_wtc);
	if (wet != 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ %d: %d\n",
			awm_iwq, wet);
	}

	wm831x_wtc_add_wandomness(wm831x);

	wetuwn 0;
}

static const stwuct dev_pm_ops wm831x_wtc_pm_ops = {
	.suspend = wm831x_wtc_suspend,
	.wesume = wm831x_wtc_wesume,

	.fweeze = wm831x_wtc_fweeze,
	.thaw = wm831x_wtc_wesume,
	.westowe = wm831x_wtc_wesume,

	.powewoff = wm831x_wtc_suspend,
};

static stwuct pwatfowm_dwivew wm831x_wtc_dwivew = {
	.pwobe = wm831x_wtc_pwobe,
	.dwivew = {
		.name = "wm831x-wtc",
		.pm = &wm831x_wtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wm831x_wtc_dwivew);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("WTC dwivew fow the WM831x sewies PMICs");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm831x-wtc");
