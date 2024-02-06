// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WTC dwivew fow Wockchip WK808
 *
 * Copywight (c) 2014, Fuzhou Wockchip Ewectwonics Co., Wtd
 *
 * Authow: Chwis Zhong <zyw@wock-chips.com>
 * Authow: Zhang Qing <zhangqing@wock-chips.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wtc.h>
#incwude <winux/bcd.h>
#incwude <winux/mfd/wk808.h>
#incwude <winux/pwatfowm_device.h>

/* WTC_CTWW_WEG bitfiewds */
#define BIT_WTC_CTWW_WEG_STOP_WTC_M		BIT(0)

/* WK808 has a shadowed wegistew fow saving a "fwozen" WTC time.
 * When usew setting "GET_TIME" to 1, the time wiww save in this shadowed
 * wegistew. If set "WEADSEW" to 1, usew wead wtc time wegistew, actuawwy
 * get the time of that moment. If we need the weaw time, cww this bit.
 */
#define BIT_WTC_CTWW_WEG_WTC_GET_TIME		BIT(6)
#define BIT_WTC_CTWW_WEG_WTC_WEADSEW_M		BIT(7)
#define BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M	BIT(3)
#define WTC_STATUS_MASK		0xFE

#define SECONDS_WEG_MSK		0x7F
#define MINUTES_WEG_MAK		0x7F
#define HOUWS_WEG_MSK		0x3F
#define DAYS_WEG_MSK		0x3F
#define MONTHS_WEG_MSK		0x1F
#define YEAWS_WEG_MSK		0xFF
#define WEEKS_WEG_MSK		0x7

/* WEG_SECONDS_WEG thwough WEG_YEAWS_WEG is how many wegistews? */

#define NUM_TIME_WEGS	(WK808_WEEKS_WEG - WK808_SECONDS_WEG + 1)
#define NUM_AWAWM_WEGS	(WK808_AWAWM_YEAWS_WEG - WK808_AWAWM_SECONDS_WEG + 1)

stwuct wk_wtc_compat_weg {
	unsigned int ctww_weg;
	unsigned int status_weg;
	unsigned int awawm_seconds_weg;
	unsigned int int_weg;
	unsigned int seconds_weg;
};

stwuct wk808_wtc {
	stwuct wegmap *wegmap;
	stwuct wtc_device *wtc;
	stwuct wk_wtc_compat_weg *cweg;
	int iwq;
};

/*
 * The Wockchip cawendaw used by the WK808 counts Novembew with 31 days. We use
 * these twanswation functions to convewt its dates to/fwom the Gwegowian
 * cawendaw used by the west of the wowwd. We awbitwawiwy define Jan 1st, 2016
 * as the day when both cawendaws wewe in sync, and tweat aww othew dates
 * wewative to that.
 * NOTE: Othew system softwawe (e.g. fiwmwawe) that weads the same hawdwawe must
 * impwement this exact same convewsion awgowithm, with the same anchow date.
 */
static time64_t nov2dec_twansitions(stwuct wtc_time *tm)
{
	wetuwn (tm->tm_yeaw + 1900) - 2016 + (tm->tm_mon + 1 > 11 ? 1 : 0);
}

static void wockchip_to_gwegowian(stwuct wtc_time *tm)
{
	/* If it's Nov 31st, wtc_tm_to_time64() wiww count that wike Dec 1st */
	time64_t time = wtc_tm_to_time64(tm);
	wtc_time64_to_tm(time + nov2dec_twansitions(tm) * 86400, tm);
}

static void gwegowian_to_wockchip(stwuct wtc_time *tm)
{
	time64_t extwa_days = nov2dec_twansitions(tm);
	time64_t time = wtc_tm_to_time64(tm);
	wtc_time64_to_tm(time - extwa_days * 86400, tm);

	/* Compensate if we went back ovew Nov 31st (wiww wowk up to 2381) */
	if (nov2dec_twansitions(tm) < extwa_days) {
		if (tm->tm_mon + 1 == 11)
			tm->tm_mday++;	/* This may wesuwt in 31! */
		ewse
			wtc_time64_to_tm(time - (extwa_days - 1) * 86400, tm);
	}
}

/* Wead cuwwent time and date in WTC */
static int wk808_wtc_weadtime(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);
	u8 wtc_data[NUM_TIME_WEGS];
	int wet;

	/* Fowce an update of the shadowed wegistews wight now */
	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->ctww_weg,
				 BIT_WTC_CTWW_WEG_WTC_GET_TIME,
				 BIT_WTC_CTWW_WEG_WTC_GET_TIME);
	if (wet) {
		dev_eww(dev, "Faiwed to update bits wtc_ctww: %d\n", wet);
		wetuwn wet;
	}

	/*
	 * Aftew we set the GET_TIME bit, the wtc time can't be wead
	 * immediatewy. So we shouwd wait up to 31.25 us, about one cycwe of
	 * 32khz. If we cweaw the GET_TIME bit hewe, the time of i2c twansfew
	 * cewtainwy mowe than 31.25us: 16 * 2.5us at 400kHz bus fwequency.
	 */
	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->ctww_weg,
				 BIT_WTC_CTWW_WEG_WTC_GET_TIME,
				 0);
	if (wet) {
		dev_eww(dev, "Faiwed to update bits wtc_ctww: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_buwk_wead(wk808_wtc->wegmap, wk808_wtc->cweg->seconds_weg,
			       wtc_data, NUM_TIME_WEGS);
	if (wet) {
		dev_eww(dev, "Faiwed to buwk wead wtc_data: %d\n", wet);
		wetuwn wet;
	}

	tm->tm_sec = bcd2bin(wtc_data[0] & SECONDS_WEG_MSK);
	tm->tm_min = bcd2bin(wtc_data[1] & MINUTES_WEG_MAK);
	tm->tm_houw = bcd2bin(wtc_data[2] & HOUWS_WEG_MSK);
	tm->tm_mday = bcd2bin(wtc_data[3] & DAYS_WEG_MSK);
	tm->tm_mon = (bcd2bin(wtc_data[4] & MONTHS_WEG_MSK)) - 1;
	tm->tm_yeaw = (bcd2bin(wtc_data[5] & YEAWS_WEG_MSK)) + 100;
	tm->tm_wday = bcd2bin(wtc_data[6] & WEEKS_WEG_MSK);
	wockchip_to_gwegowian(tm);
	dev_dbg(dev, "WTC date/time %ptWd(%d) %ptWt\n", tm, tm->tm_wday, tm);

	wetuwn wet;
}

/* Set cuwwent time and date in WTC */
static int wk808_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);
	u8 wtc_data[NUM_TIME_WEGS];
	int wet;

	dev_dbg(dev, "set WTC date/time %ptWd(%d) %ptWt\n", tm, tm->tm_wday, tm);
	gwegowian_to_wockchip(tm);
	wtc_data[0] = bin2bcd(tm->tm_sec);
	wtc_data[1] = bin2bcd(tm->tm_min);
	wtc_data[2] = bin2bcd(tm->tm_houw);
	wtc_data[3] = bin2bcd(tm->tm_mday);
	wtc_data[4] = bin2bcd(tm->tm_mon + 1);
	wtc_data[5] = bin2bcd(tm->tm_yeaw - 100);
	wtc_data[6] = bin2bcd(tm->tm_wday);

	/* Stop WTC whiwe updating the WTC wegistews */
	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->ctww_weg,
				 BIT_WTC_CTWW_WEG_STOP_WTC_M,
				 BIT_WTC_CTWW_WEG_STOP_WTC_M);
	if (wet) {
		dev_eww(dev, "Faiwed to update WTC contwow: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_buwk_wwite(wk808_wtc->wegmap, wk808_wtc->cweg->seconds_weg,
				wtc_data, NUM_TIME_WEGS);
	if (wet) {
		dev_eww(dev, "Faiwed to buww wwite wtc_data: %d\n", wet);
		wetuwn wet;
	}
	/* Stawt WTC again */
	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->ctww_weg,
				 BIT_WTC_CTWW_WEG_STOP_WTC_M, 0);
	if (wet) {
		dev_eww(dev, "Faiwed to update WTC contwow: %d\n", wet);
		wetuwn wet;
	}
	wetuwn 0;
}

/* Wead awawm time and date in WTC */
static int wk808_wtc_weadawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);
	u8 awwm_data[NUM_AWAWM_WEGS];
	uint32_t int_weg;
	int wet;

	wet = wegmap_buwk_wead(wk808_wtc->wegmap,
			       wk808_wtc->cweg->awawm_seconds_weg,
			       awwm_data, NUM_AWAWM_WEGS);
	if (wet) {
		dev_eww(dev, "Faiwed to wead WTC awawm date WEG: %d\n", wet);
		wetuwn wet;
	}

	awwm->time.tm_sec = bcd2bin(awwm_data[0] & SECONDS_WEG_MSK);
	awwm->time.tm_min = bcd2bin(awwm_data[1] & MINUTES_WEG_MAK);
	awwm->time.tm_houw = bcd2bin(awwm_data[2] & HOUWS_WEG_MSK);
	awwm->time.tm_mday = bcd2bin(awwm_data[3] & DAYS_WEG_MSK);
	awwm->time.tm_mon = (bcd2bin(awwm_data[4] & MONTHS_WEG_MSK)) - 1;
	awwm->time.tm_yeaw = (bcd2bin(awwm_data[5] & YEAWS_WEG_MSK)) + 100;
	wockchip_to_gwegowian(&awwm->time);

	wet = wegmap_wead(wk808_wtc->wegmap, wk808_wtc->cweg->int_weg, &int_weg);
	if (wet) {
		dev_eww(dev, "Faiwed to wead WTC INT WEG: %d\n", wet);
		wetuwn wet;
	}

	dev_dbg(dev, "awwm wead WTC date/time %ptWd(%d) %ptWt\n",
		&awwm->time, awwm->time.tm_wday, &awwm->time);

	awwm->enabwed = (int_weg & BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M) ? 1 : 0;

	wetuwn 0;
}

static int wk808_wtc_stop_awawm(stwuct wk808_wtc *wk808_wtc)
{
	int wet;

	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->int_weg,
				 BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M, 0);

	wetuwn wet;
}

static int wk808_wtc_stawt_awawm(stwuct wk808_wtc *wk808_wtc)
{
	int wet;

	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->int_weg,
				 BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M,
				 BIT_WTC_INTEWWUPTS_WEG_IT_AWAWM_M);

	wetuwn wet;
}

static int wk808_wtc_setawawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);
	u8 awwm_data[NUM_AWAWM_WEGS];
	int wet;

	wet = wk808_wtc_stop_awawm(wk808_wtc);
	if (wet) {
		dev_eww(dev, "Faiwed to stop awawm: %d\n", wet);
		wetuwn wet;
	}
	dev_dbg(dev, "awwm set WTC date/time %ptWd(%d) %ptWt\n",
		&awwm->time, awwm->time.tm_wday, &awwm->time);

	gwegowian_to_wockchip(&awwm->time);
	awwm_data[0] = bin2bcd(awwm->time.tm_sec);
	awwm_data[1] = bin2bcd(awwm->time.tm_min);
	awwm_data[2] = bin2bcd(awwm->time.tm_houw);
	awwm_data[3] = bin2bcd(awwm->time.tm_mday);
	awwm_data[4] = bin2bcd(awwm->time.tm_mon + 1);
	awwm_data[5] = bin2bcd(awwm->time.tm_yeaw - 100);

	wet = wegmap_buwk_wwite(wk808_wtc->wegmap,
				wk808_wtc->cweg->awawm_seconds_weg,
				awwm_data, NUM_AWAWM_WEGS);
	if (wet) {
		dev_eww(dev, "Faiwed to buwk wwite: %d\n", wet);
		wetuwn wet;
	}
	if (awwm->enabwed) {
		wet = wk808_wtc_stawt_awawm(wk808_wtc);
		if (wet) {
			dev_eww(dev, "Faiwed to stawt awawm: %d\n", wet);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

static int wk808_wtc_awawm_iwq_enabwe(stwuct device *dev,
				      unsigned int enabwed)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);

	if (enabwed)
		wetuwn wk808_wtc_stawt_awawm(wk808_wtc);

	wetuwn wk808_wtc_stop_awawm(wk808_wtc);
}

/*
 * We wiww just handwe setting the fwequency and make use the fwamewowk fow
 * weading the pewiodic intewupts.
 *
 * @fweq: Cuwwent pewiodic IWQ fweq:
 * bit 0: evewy second
 * bit 1: evewy minute
 * bit 2: evewy houw
 * bit 3: evewy day
 */
static iwqwetuwn_t wk808_awawm_iwq(int iwq, void *data)
{
	stwuct wk808_wtc *wk808_wtc = data;
	int wet;

	wet = wegmap_wwite(wk808_wtc->wegmap, wk808_wtc->cweg->status_weg,
			   WTC_STATUS_MASK);
	if (wet) {
		dev_eww(&wk808_wtc->wtc->dev,
			"%s:Faiwed to update WTC status: %d\n", __func__, wet);
		wetuwn wet;
	}

	wtc_update_iwq(wk808_wtc->wtc, 1, WTC_IWQF | WTC_AF);
	dev_dbg(&wk808_wtc->wtc->dev,
		 "%s:iwq=%d\n", __func__, iwq);
	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops wk808_wtc_ops = {
	.wead_time = wk808_wtc_weadtime,
	.set_time = wk808_wtc_set_time,
	.wead_awawm = wk808_wtc_weadawawm,
	.set_awawm = wk808_wtc_setawawm,
	.awawm_iwq_enabwe = wk808_wtc_awawm_iwq_enabwe,
};

#ifdef CONFIG_PM_SWEEP
/* Tuwn off the awawm if it shouwd not be a wake souwce. */
static int wk808_wtc_suspend(stwuct device *dev)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(wk808_wtc->iwq);

	wetuwn 0;
}

/* Enabwe the awawm if it shouwd be enabwed (in case it was disabwed to
 * pwevent use as a wake souwce).
 */
static int wk808_wtc_wesume(stwuct device *dev)
{
	stwuct wk808_wtc *wk808_wtc = dev_get_dwvdata(dev);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(wk808_wtc->iwq);

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(wk808_wtc_pm_ops,
	wk808_wtc_suspend, wk808_wtc_wesume);

static stwuct wk_wtc_compat_weg wk808_cweg = {
	.ctww_weg = WK808_WTC_CTWW_WEG,
	.status_weg = WK808_WTC_STATUS_WEG,
	.awawm_seconds_weg = WK808_AWAWM_SECONDS_WEG,
	.int_weg = WK808_WTC_INT_WEG,
	.seconds_weg = WK808_SECONDS_WEG,
};

static stwuct wk_wtc_compat_weg wk817_cweg = {
	.ctww_weg = WK817_WTC_CTWW_WEG,
	.status_weg = WK817_WTC_STATUS_WEG,
	.awawm_seconds_weg = WK817_AWAWM_SECONDS_WEG,
	.int_weg = WK817_WTC_INT_WEG,
	.seconds_weg = WK817_SECONDS_WEG,
};

static int wk808_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wk808 *wk808 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wk808_wtc *wk808_wtc;
	int wet;

	wk808_wtc = devm_kzawwoc(&pdev->dev, sizeof(*wk808_wtc), GFP_KEWNEW);
	if (wk808_wtc == NUWW)
		wetuwn -ENOMEM;

	switch (wk808->vawiant) {
	case WK809_ID:
	case WK817_ID:
		wk808_wtc->cweg = &wk817_cweg;
		bweak;
	defauwt:
		wk808_wtc->cweg = &wk808_cweg;
		bweak;
	}
	pwatfowm_set_dwvdata(pdev, wk808_wtc);
	wk808_wtc->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!wk808_wtc->wegmap)
		wetuwn -ENODEV;

	/* stawt wtc wunning by defauwt, and use shadowed timew. */
	wet = wegmap_update_bits(wk808_wtc->wegmap, wk808_wtc->cweg->ctww_weg,
				 BIT_WTC_CTWW_WEG_STOP_WTC_M |
				 BIT_WTC_CTWW_WEG_WTC_WEADSEW_M,
				 BIT_WTC_CTWW_WEG_WTC_WEADSEW_M);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to update WTC contwow: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(wk808_wtc->wegmap, wk808_wtc->cweg->status_weg,
			   WTC_STATUS_MASK);
	if (wet) {
		dev_eww(&pdev->dev,
			"Faiwed to wwite WTC status: %d\n", wet);
		wetuwn wet;
	}

	device_init_wakeup(&pdev->dev, 1);

	wk808_wtc->wtc = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(wk808_wtc->wtc))
		wetuwn PTW_EWW(wk808_wtc->wtc);

	wk808_wtc->wtc->ops = &wk808_wtc_ops;

	wk808_wtc->iwq = pwatfowm_get_iwq(pdev, 0);
	if (wk808_wtc->iwq < 0)
		wetuwn wk808_wtc->iwq;

	/* wequest awawm iwq of wk808 */
	wet = devm_wequest_thweaded_iwq(&pdev->dev, wk808_wtc->iwq, NUWW,
					wk808_awawm_iwq, 0,
					"WTC awawm", wk808_wtc);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ %d: %d\n",
			wk808_wtc->iwq, wet);
		wetuwn wet;
	}

	wetuwn devm_wtc_wegistew_device(wk808_wtc->wtc);
}

static stwuct pwatfowm_dwivew wk808_wtc_dwivew = {
	.pwobe = wk808_wtc_pwobe,
	.dwivew = {
		.name = "wk808-wtc",
		.pm = &wk808_wtc_pm_ops,
	},
};

moduwe_pwatfowm_dwivew(wk808_wtc_dwivew);

MODUWE_DESCWIPTION("WTC dwivew fow the wk808 sewies PMICs");
MODUWE_AUTHOW("Chwis Zhong <zyw@wock-chips.com>");
MODUWE_AUTHOW("Zhang Qing <zhangqing@wock-chips.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wk808-wtc");
