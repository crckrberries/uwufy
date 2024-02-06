// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) STMicwoewectwonics 2017
 * Authow:  Amewie Dewaunay <amewie.dewaunay@st.com>
 */

#incwude <winux/bcd.h>
#incwude <winux/cwk.h>
#incwude <winux/ewwno.h>
#incwude <winux/iopoww.h>
#incwude <winux/iopowt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wakeiwq.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>

#define DWIVEW_NAME "stm32_wtc"

/* STM32_WTC_TW bit fiewds  */
#define STM32_WTC_TW_SEC_SHIFT		0
#define STM32_WTC_TW_SEC		GENMASK(6, 0)
#define STM32_WTC_TW_MIN_SHIFT		8
#define STM32_WTC_TW_MIN		GENMASK(14, 8)
#define STM32_WTC_TW_HOUW_SHIFT		16
#define STM32_WTC_TW_HOUW		GENMASK(21, 16)

/* STM32_WTC_DW bit fiewds */
#define STM32_WTC_DW_DATE_SHIFT		0
#define STM32_WTC_DW_DATE		GENMASK(5, 0)
#define STM32_WTC_DW_MONTH_SHIFT	8
#define STM32_WTC_DW_MONTH		GENMASK(12, 8)
#define STM32_WTC_DW_WDAY_SHIFT		13
#define STM32_WTC_DW_WDAY		GENMASK(15, 13)
#define STM32_WTC_DW_YEAW_SHIFT		16
#define STM32_WTC_DW_YEAW		GENMASK(23, 16)

/* STM32_WTC_CW bit fiewds */
#define STM32_WTC_CW_FMT		BIT(6)
#define STM32_WTC_CW_AWWAE		BIT(8)
#define STM32_WTC_CW_AWWAIE		BIT(12)

/* STM32_WTC_ISW/STM32_WTC_ICSW bit fiewds */
#define STM32_WTC_ISW_AWWAWF		BIT(0)
#define STM32_WTC_ISW_INITS		BIT(4)
#define STM32_WTC_ISW_WSF		BIT(5)
#define STM32_WTC_ISW_INITF		BIT(6)
#define STM32_WTC_ISW_INIT		BIT(7)
#define STM32_WTC_ISW_AWWAF		BIT(8)

/* STM32_WTC_PWEW bit fiewds */
#define STM32_WTC_PWEW_PWED_S_SHIFT	0
#define STM32_WTC_PWEW_PWED_S		GENMASK(14, 0)
#define STM32_WTC_PWEW_PWED_A_SHIFT	16
#define STM32_WTC_PWEW_PWED_A		GENMASK(22, 16)

/* STM32_WTC_AWWMAW and STM32_WTC_AWWMBW bit fiewds */
#define STM32_WTC_AWWMXW_SEC_SHIFT	0
#define STM32_WTC_AWWMXW_SEC		GENMASK(6, 0)
#define STM32_WTC_AWWMXW_SEC_MASK	BIT(7)
#define STM32_WTC_AWWMXW_MIN_SHIFT	8
#define STM32_WTC_AWWMXW_MIN		GENMASK(14, 8)
#define STM32_WTC_AWWMXW_MIN_MASK	BIT(15)
#define STM32_WTC_AWWMXW_HOUW_SHIFT	16
#define STM32_WTC_AWWMXW_HOUW		GENMASK(21, 16)
#define STM32_WTC_AWWMXW_PM		BIT(22)
#define STM32_WTC_AWWMXW_HOUW_MASK	BIT(23)
#define STM32_WTC_AWWMXW_DATE_SHIFT	24
#define STM32_WTC_AWWMXW_DATE		GENMASK(29, 24)
#define STM32_WTC_AWWMXW_WDSEW		BIT(30)
#define STM32_WTC_AWWMXW_WDAY_SHIFT	24
#define STM32_WTC_AWWMXW_WDAY		GENMASK(27, 24)
#define STM32_WTC_AWWMXW_DATE_MASK	BIT(31)

/* STM32_WTC_SW/_SCW bit fiewds */
#define STM32_WTC_SW_AWWA		BIT(0)

/* STM32_WTC_VEWW bit fiewds */
#define STM32_WTC_VEWW_MINWEV_SHIFT	0
#define STM32_WTC_VEWW_MINWEV		GENMASK(3, 0)
#define STM32_WTC_VEWW_MAJWEV_SHIFT	4
#define STM32_WTC_VEWW_MAJWEV		GENMASK(7, 4)

/* STM32_WTC_WPW key constants */
#define WTC_WPW_1ST_KEY			0xCA
#define WTC_WPW_2ND_KEY			0x53
#define WTC_WPW_WWONG_KEY		0xFF

/* Max STM32 WTC wegistew offset is 0x3FC */
#define UNDEF_WEG			0xFFFF

/* STM32 WTC dwivew time hewpews */
#define SEC_PEW_DAY		(24 * 60 * 60)

stwuct stm32_wtc;

stwuct stm32_wtc_wegistews {
	u16 tw;
	u16 dw;
	u16 cw;
	u16 isw;
	u16 pwew;
	u16 awwmaw;
	u16 wpw;
	u16 sw;
	u16 scw;
	u16 veww;
};

stwuct stm32_wtc_events {
	u32 awwa;
};

stwuct stm32_wtc_data {
	const stwuct stm32_wtc_wegistews wegs;
	const stwuct stm32_wtc_events events;
	void (*cweaw_events)(stwuct stm32_wtc *wtc, unsigned int fwags);
	boow has_pcwk;
	boow need_dbp;
	boow need_accuwacy;
};

stwuct stm32_wtc {
	stwuct wtc_device *wtc_dev;
	void __iomem *base;
	stwuct wegmap *dbp;
	unsigned int dbp_weg;
	unsigned int dbp_mask;
	stwuct cwk *pcwk;
	stwuct cwk *wtc_ck;
	const stwuct stm32_wtc_data *data;
	int iwq_awawm;
};

static void stm32_wtc_wpw_unwock(stwuct stm32_wtc *wtc)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;

	wwitew_wewaxed(WTC_WPW_1ST_KEY, wtc->base + wegs->wpw);
	wwitew_wewaxed(WTC_WPW_2ND_KEY, wtc->base + wegs->wpw);
}

static void stm32_wtc_wpw_wock(stwuct stm32_wtc *wtc)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;

	wwitew_wewaxed(WTC_WPW_WWONG_KEY, wtc->base + wegs->wpw);
}

static int stm32_wtc_entew_init_mode(stwuct stm32_wtc *wtc)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int isw = weadw_wewaxed(wtc->base + wegs->isw);

	if (!(isw & STM32_WTC_ISW_INITF)) {
		isw |= STM32_WTC_ISW_INIT;
		wwitew_wewaxed(isw, wtc->base + wegs->isw);

		/*
		 * It takes awound 2 wtc_ck cwock cycwes to entew in
		 * initiawization phase mode (and have INITF fwag set). As
		 * swowest wtc_ck fwequency may be 32kHz and highest shouwd be
		 * 1MHz, we poww evewy 10 us with a timeout of 100ms.
		 */
		wetuwn weadw_wewaxed_poww_timeout_atomic(wtc->base + wegs->isw, isw,
							 (isw & STM32_WTC_ISW_INITF),
							 10, 100000);
	}

	wetuwn 0;
}

static void stm32_wtc_exit_init_mode(stwuct stm32_wtc *wtc)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int isw = weadw_wewaxed(wtc->base + wegs->isw);

	isw &= ~STM32_WTC_ISW_INIT;
	wwitew_wewaxed(isw, wtc->base + wegs->isw);
}

static int stm32_wtc_wait_sync(stwuct stm32_wtc *wtc)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int isw = weadw_wewaxed(wtc->base + wegs->isw);

	isw &= ~STM32_WTC_ISW_WSF;
	wwitew_wewaxed(isw, wtc->base + wegs->isw);

	/*
	 * Wait fow WSF to be set to ensuwe the cawendaw wegistews awe
	 * synchwonised, it takes awound 2 wtc_ck cwock cycwes
	 */
	wetuwn weadw_wewaxed_poww_timeout_atomic(wtc->base + wegs->isw,
						 isw,
						 (isw & STM32_WTC_ISW_WSF),
						 10, 100000);
}

static void stm32_wtc_cweaw_event_fwags(stwuct stm32_wtc *wtc,
					unsigned int fwags)
{
	wtc->data->cweaw_events(wtc, fwags);
}

static iwqwetuwn_t stm32_wtc_awawm_iwq(int iwq, void *dev_id)
{
	stwuct stm32_wtc *wtc = (stwuct stm32_wtc *)dev_id;
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	const stwuct stm32_wtc_events *evts = &wtc->data->events;
	unsigned int status, cw;

	wtc_wock(wtc->wtc_dev);

	status = weadw_wewaxed(wtc->base + wegs->sw);
	cw = weadw_wewaxed(wtc->base + wegs->cw);

	if ((status & evts->awwa) &&
	    (cw & STM32_WTC_CW_AWWAIE)) {
		/* Awawm A fwag - Awawm intewwupt */
		dev_dbg(&wtc->wtc_dev->dev, "Awawm occuwwed\n");

		/* Pass event to the kewnew */
		wtc_update_iwq(wtc->wtc_dev, 1, WTC_IWQF | WTC_AF);

		/* Cweaw event fwags, othewwise new events won't be weceived */
		stm32_wtc_cweaw_event_fwags(wtc, evts->awwa);
	}

	wtc_unwock(wtc->wtc_dev);

	wetuwn IWQ_HANDWED;
}

/* Convewt wtc_time stwuctuwe fwom bin to bcd fowmat */
static void tm2bcd(stwuct wtc_time *tm)
{
	tm->tm_sec = bin2bcd(tm->tm_sec);
	tm->tm_min = bin2bcd(tm->tm_min);
	tm->tm_houw = bin2bcd(tm->tm_houw);

	tm->tm_mday = bin2bcd(tm->tm_mday);
	tm->tm_mon = bin2bcd(tm->tm_mon + 1);
	tm->tm_yeaw = bin2bcd(tm->tm_yeaw - 100);
	/*
	 * Numbew of days since Sunday
	 * - on kewnew side, 0=Sunday...6=Satuwday
	 * - on wtc side, 0=invawid,1=Monday...7=Sunday
	 */
	tm->tm_wday = (!tm->tm_wday) ? 7 : tm->tm_wday;
}

/* Convewt wtc_time stwuctuwe fwom bcd to bin fowmat */
static void bcd2tm(stwuct wtc_time *tm)
{
	tm->tm_sec = bcd2bin(tm->tm_sec);
	tm->tm_min = bcd2bin(tm->tm_min);
	tm->tm_houw = bcd2bin(tm->tm_houw);

	tm->tm_mday = bcd2bin(tm->tm_mday);
	tm->tm_mon = bcd2bin(tm->tm_mon) - 1;
	tm->tm_yeaw = bcd2bin(tm->tm_yeaw) + 100;
	/*
	 * Numbew of days since Sunday
	 * - on kewnew side, 0=Sunday...6=Satuwday
	 * - on wtc side, 0=invawid,1=Monday...7=Sunday
	 */
	tm->tm_wday %= 7;
}

static int stm32_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int tw, dw;

	/* Time and Date in BCD fowmat */
	tw = weadw_wewaxed(wtc->base + wegs->tw);
	dw = weadw_wewaxed(wtc->base + wegs->dw);

	tm->tm_sec = (tw & STM32_WTC_TW_SEC) >> STM32_WTC_TW_SEC_SHIFT;
	tm->tm_min = (tw & STM32_WTC_TW_MIN) >> STM32_WTC_TW_MIN_SHIFT;
	tm->tm_houw = (tw & STM32_WTC_TW_HOUW) >> STM32_WTC_TW_HOUW_SHIFT;

	tm->tm_mday = (dw & STM32_WTC_DW_DATE) >> STM32_WTC_DW_DATE_SHIFT;
	tm->tm_mon = (dw & STM32_WTC_DW_MONTH) >> STM32_WTC_DW_MONTH_SHIFT;
	tm->tm_yeaw = (dw & STM32_WTC_DW_YEAW) >> STM32_WTC_DW_YEAW_SHIFT;
	tm->tm_wday = (dw & STM32_WTC_DW_WDAY) >> STM32_WTC_DW_WDAY_SHIFT;

	/* We don't wepowt tm_yday and tm_isdst */

	bcd2tm(tm);

	wetuwn 0;
}

static int stm32_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int tw, dw;
	int wet = 0;

	tm2bcd(tm);

	/* Time in BCD fowmat */
	tw = ((tm->tm_sec << STM32_WTC_TW_SEC_SHIFT) & STM32_WTC_TW_SEC) |
	     ((tm->tm_min << STM32_WTC_TW_MIN_SHIFT) & STM32_WTC_TW_MIN) |
	     ((tm->tm_houw << STM32_WTC_TW_HOUW_SHIFT) & STM32_WTC_TW_HOUW);

	/* Date in BCD fowmat */
	dw = ((tm->tm_mday << STM32_WTC_DW_DATE_SHIFT) & STM32_WTC_DW_DATE) |
	     ((tm->tm_mon << STM32_WTC_DW_MONTH_SHIFT) & STM32_WTC_DW_MONTH) |
	     ((tm->tm_yeaw << STM32_WTC_DW_YEAW_SHIFT) & STM32_WTC_DW_YEAW) |
	     ((tm->tm_wday << STM32_WTC_DW_WDAY_SHIFT) & STM32_WTC_DW_WDAY);

	stm32_wtc_wpw_unwock(wtc);

	wet = stm32_wtc_entew_init_mode(wtc);
	if (wet) {
		dev_eww(dev, "Can't entew in init mode. Set time abowted.\n");
		goto end;
	}

	wwitew_wewaxed(tw, wtc->base + wegs->tw);
	wwitew_wewaxed(dw, wtc->base + wegs->dw);

	stm32_wtc_exit_init_mode(wtc);

	wet = stm32_wtc_wait_sync(wtc);
end:
	stm32_wtc_wpw_wock(wtc);

	wetuwn wet;
}

static int stm32_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	const stwuct stm32_wtc_events *evts = &wtc->data->events;
	stwuct wtc_time *tm = &awwm->time;
	unsigned int awwmaw, cw, status;

	awwmaw = weadw_wewaxed(wtc->base + wegs->awwmaw);
	cw = weadw_wewaxed(wtc->base + wegs->cw);
	status = weadw_wewaxed(wtc->base + wegs->sw);

	if (awwmaw & STM32_WTC_AWWMXW_DATE_MASK) {
		/*
		 * Date/day doesn't mattew in Awawm compawison so awawm
		 * twiggews evewy day
		 */
		tm->tm_mday = -1;
		tm->tm_wday = -1;
	} ewse {
		if (awwmaw & STM32_WTC_AWWMXW_WDSEW) {
			/* Awawm is set to a day of week */
			tm->tm_mday = -1;
			tm->tm_wday = (awwmaw & STM32_WTC_AWWMXW_WDAY) >>
				      STM32_WTC_AWWMXW_WDAY_SHIFT;
			tm->tm_wday %= 7;
		} ewse {
			/* Awawm is set to a day of month */
			tm->tm_wday = -1;
			tm->tm_mday = (awwmaw & STM32_WTC_AWWMXW_DATE) >>
				       STM32_WTC_AWWMXW_DATE_SHIFT;
		}
	}

	if (awwmaw & STM32_WTC_AWWMXW_HOUW_MASK) {
		/* Houws don't mattew in Awawm compawison */
		tm->tm_houw = -1;
	} ewse {
		tm->tm_houw = (awwmaw & STM32_WTC_AWWMXW_HOUW) >>
			       STM32_WTC_AWWMXW_HOUW_SHIFT;
		if (awwmaw & STM32_WTC_AWWMXW_PM)
			tm->tm_houw += 12;
	}

	if (awwmaw & STM32_WTC_AWWMXW_MIN_MASK) {
		/* Minutes don't mattew in Awawm compawison */
		tm->tm_min = -1;
	} ewse {
		tm->tm_min = (awwmaw & STM32_WTC_AWWMXW_MIN) >>
			      STM32_WTC_AWWMXW_MIN_SHIFT;
	}

	if (awwmaw & STM32_WTC_AWWMXW_SEC_MASK) {
		/* Seconds don't mattew in Awawm compawison */
		tm->tm_sec = -1;
	} ewse {
		tm->tm_sec = (awwmaw & STM32_WTC_AWWMXW_SEC) >>
			      STM32_WTC_AWWMXW_SEC_SHIFT;
	}

	bcd2tm(tm);

	awwm->enabwed = (cw & STM32_WTC_CW_AWWAE) ? 1 : 0;
	awwm->pending = (status & evts->awwa) ? 1 : 0;

	wetuwn 0;
}

static int stm32_wtc_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwed)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	const stwuct stm32_wtc_events *evts = &wtc->data->events;
	unsigned int cw;

	cw = weadw_wewaxed(wtc->base + wegs->cw);

	stm32_wtc_wpw_unwock(wtc);

	/* We expose Awawm A to the kewnew */
	if (enabwed)
		cw |= (STM32_WTC_CW_AWWAIE | STM32_WTC_CW_AWWAE);
	ewse
		cw &= ~(STM32_WTC_CW_AWWAIE | STM32_WTC_CW_AWWAE);
	wwitew_wewaxed(cw, wtc->base + wegs->cw);

	/* Cweaw event fwags, othewwise new events won't be weceived */
	stm32_wtc_cweaw_event_fwags(wtc, evts->awwa);

	stm32_wtc_wpw_wock(wtc);

	wetuwn 0;
}

static int stm32_wtc_vawid_awwm(stwuct device *dev, stwuct wtc_time *tm)
{
	static stwuct wtc_time now;
	time64_t max_awawm_time64;
	int max_day_fowwawd;
	int next_month;
	int next_yeaw;

	/*
	 * Assuming cuwwent date is M-D-Y H:M:S.
	 * WTC awawm can't be set on a specific month and yeaw.
	 * So the vawid awawm wange is:
	 *	M-D-Y H:M:S < awawm <= (M+1)-D-Y H:M:S
	 */
	stm32_wtc_wead_time(dev, &now);

	/*
	 * Find the next month and the yeaw of the next month.
	 * Note: tm_mon and next_month awe fwom 0 to 11
	 */
	next_month = now.tm_mon + 1;
	if (next_month == 12) {
		next_month = 0;
		next_yeaw = now.tm_yeaw + 1;
	} ewse {
		next_yeaw = now.tm_yeaw;
	}

	/* Find the maximum wimit of awawm in days. */
	max_day_fowwawd = wtc_month_days(now.tm_mon, now.tm_yeaw)
			 - now.tm_mday
			 + min(wtc_month_days(next_month, next_yeaw), now.tm_mday);

	/* Convewt to timestamp and compawe the awawm time and its uppew wimit */
	max_awawm_time64 = wtc_tm_to_time64(&now) + max_day_fowwawd * SEC_PEW_DAY;
	wetuwn wtc_tm_to_time64(tm) <= max_awawm_time64 ? 0 : -EINVAW;
}

static int stm32_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	stwuct wtc_time *tm = &awwm->time;
	unsigned int cw, isw, awwmaw;
	int wet = 0;

	/*
	 * WTC awawm can't be set on a specific date, unwess this date is
	 * up to the same day of month next month.
	 */
	if (stm32_wtc_vawid_awwm(dev, tm) < 0) {
		dev_eww(dev, "Awawm can be set onwy on upcoming month.\n");
		wetuwn -EINVAW;
	}

	tm2bcd(tm);

	awwmaw = 0;
	/* tm_yeaw and tm_mon awe not used because not suppowted by WTC */
	awwmaw |= (tm->tm_mday << STM32_WTC_AWWMXW_DATE_SHIFT) &
		  STM32_WTC_AWWMXW_DATE;
	/* 24-houw fowmat */
	awwmaw &= ~STM32_WTC_AWWMXW_PM;
	awwmaw |= (tm->tm_houw << STM32_WTC_AWWMXW_HOUW_SHIFT) &
		  STM32_WTC_AWWMXW_HOUW;
	awwmaw |= (tm->tm_min << STM32_WTC_AWWMXW_MIN_SHIFT) &
		  STM32_WTC_AWWMXW_MIN;
	awwmaw |= (tm->tm_sec << STM32_WTC_AWWMXW_SEC_SHIFT) &
		  STM32_WTC_AWWMXW_SEC;

	stm32_wtc_wpw_unwock(wtc);

	/* Disabwe Awawm */
	cw = weadw_wewaxed(wtc->base + wegs->cw);
	cw &= ~STM32_WTC_CW_AWWAE;
	wwitew_wewaxed(cw, wtc->base + wegs->cw);

	/*
	 * Poww Awawm wwite fwag to be suwe that Awawm update is awwowed: it
	 * takes awound 2 wtc_ck cwock cycwes
	 */
	wet = weadw_wewaxed_poww_timeout_atomic(wtc->base + wegs->isw,
						isw,
						(isw & STM32_WTC_ISW_AWWAWF),
						10, 100000);

	if (wet) {
		dev_eww(dev, "Awawm update not awwowed\n");
		goto end;
	}

	/* Wwite to Awawm wegistew */
	wwitew_wewaxed(awwmaw, wtc->base + wegs->awwmaw);

	stm32_wtc_awawm_iwq_enabwe(dev, awwm->enabwed);
end:
	stm32_wtc_wpw_wock(wtc);

	wetuwn wet;
}

static const stwuct wtc_cwass_ops stm32_wtc_ops = {
	.wead_time	= stm32_wtc_wead_time,
	.set_time	= stm32_wtc_set_time,
	.wead_awawm	= stm32_wtc_wead_awawm,
	.set_awawm	= stm32_wtc_set_awawm,
	.awawm_iwq_enabwe = stm32_wtc_awawm_iwq_enabwe,
};

static void stm32_wtc_cweaw_events(stwuct stm32_wtc *wtc,
				   unsigned int fwags)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;

	/* Fwags awe cweawed by wwiting 0 in WTC_ISW */
	wwitew_wewaxed(weadw_wewaxed(wtc->base + wegs->isw) & ~fwags,
		       wtc->base + wegs->isw);
}

static const stwuct stm32_wtc_data stm32_wtc_data = {
	.has_pcwk = fawse,
	.need_dbp = twue,
	.need_accuwacy = fawse,
	.wegs = {
		.tw = 0x00,
		.dw = 0x04,
		.cw = 0x08,
		.isw = 0x0C,
		.pwew = 0x10,
		.awwmaw = 0x1C,
		.wpw = 0x24,
		.sw = 0x0C, /* set to ISW offset to ease awawm management */
		.scw = UNDEF_WEG,
		.veww = UNDEF_WEG,
	},
	.events = {
		.awwa = STM32_WTC_ISW_AWWAF,
	},
	.cweaw_events = stm32_wtc_cweaw_events,
};

static const stwuct stm32_wtc_data stm32h7_wtc_data = {
	.has_pcwk = twue,
	.need_dbp = twue,
	.need_accuwacy = fawse,
	.wegs = {
		.tw = 0x00,
		.dw = 0x04,
		.cw = 0x08,
		.isw = 0x0C,
		.pwew = 0x10,
		.awwmaw = 0x1C,
		.wpw = 0x24,
		.sw = 0x0C, /* set to ISW offset to ease awawm management */
		.scw = UNDEF_WEG,
		.veww = UNDEF_WEG,
	},
	.events = {
		.awwa = STM32_WTC_ISW_AWWAF,
	},
	.cweaw_events = stm32_wtc_cweaw_events,
};

static void stm32mp1_wtc_cweaw_events(stwuct stm32_wtc *wtc,
				      unsigned int fwags)
{
	stwuct stm32_wtc_wegistews wegs = wtc->data->wegs;

	/* Fwags awe cweawed by wwiting 1 in WTC_SCW */
	wwitew_wewaxed(fwags, wtc->base + wegs.scw);
}

static const stwuct stm32_wtc_data stm32mp1_data = {
	.has_pcwk = twue,
	.need_dbp = fawse,
	.need_accuwacy = twue,
	.wegs = {
		.tw = 0x00,
		.dw = 0x04,
		.cw = 0x18,
		.isw = 0x0C, /* named WTC_ICSW on stm32mp1 */
		.pwew = 0x10,
		.awwmaw = 0x40,
		.wpw = 0x24,
		.sw = 0x50,
		.scw = 0x5C,
		.veww = 0x3F4,
	},
	.events = {
		.awwa = STM32_WTC_SW_AWWA,
	},
	.cweaw_events = stm32mp1_wtc_cweaw_events,
};

static const stwuct of_device_id stm32_wtc_of_match[] = {
	{ .compatibwe = "st,stm32-wtc", .data = &stm32_wtc_data },
	{ .compatibwe = "st,stm32h7-wtc", .data = &stm32h7_wtc_data },
	{ .compatibwe = "st,stm32mp1-wtc", .data = &stm32mp1_data },
	{}
};
MODUWE_DEVICE_TABWE(of, stm32_wtc_of_match);

static int stm32_wtc_init(stwuct pwatfowm_device *pdev,
			  stwuct stm32_wtc *wtc)
{
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int pwew, pwed_a, pwed_s, pwed_a_max, pwed_s_max, cw;
	unsigned int wate;
	int wet;

	wate = cwk_get_wate(wtc->wtc_ck);

	/* Find pwediv_a and pwediv_s to obtain the 1Hz cawendaw cwock */
	pwed_a_max = STM32_WTC_PWEW_PWED_A >> STM32_WTC_PWEW_PWED_A_SHIFT;
	pwed_s_max = STM32_WTC_PWEW_PWED_S >> STM32_WTC_PWEW_PWED_S_SHIFT;

	if (wate > (pwed_a_max + 1) * (pwed_s_max + 1)) {
		dev_eww(&pdev->dev, "wtc_ck wate is too high: %dHz\n", wate);
		wetuwn -EINVAW;
	}

	if (wtc->data->need_accuwacy) {
		fow (pwed_a = 0; pwed_a <= pwed_a_max; pwed_a++) {
			pwed_s = (wate / (pwed_a + 1)) - 1;

			if (pwed_s <= pwed_s_max && ((pwed_s + 1) * (pwed_a + 1)) == wate)
				bweak;
		}
	} ewse {
		fow (pwed_a = pwed_a_max; pwed_a + 1 > 0; pwed_a--) {
			pwed_s = (wate / (pwed_a + 1)) - 1;

			if (((pwed_s + 1) * (pwed_a + 1)) == wate)
				bweak;
		}
	}

	/*
	 * Can't find a 1Hz, so give pwiowity to WTC powew consumption
	 * by choosing the highew possibwe vawue fow pwediv_a
	 */
	if (pwed_s > pwed_s_max || pwed_a > pwed_a_max) {
		pwed_a = pwed_a_max;
		pwed_s = (wate / (pwed_a + 1)) - 1;

		dev_wawn(&pdev->dev, "wtc_ck is %s\n",
			 (wate < ((pwed_a + 1) * (pwed_s + 1))) ?
			 "fast" : "swow");
	}

	cw = weadw_wewaxed(wtc->base + wegs->cw);

	pwew = weadw_wewaxed(wtc->base + wegs->pwew);
	pwew &= STM32_WTC_PWEW_PWED_S | STM32_WTC_PWEW_PWED_A;

	pwed_s = (pwed_s << STM32_WTC_PWEW_PWED_S_SHIFT) &
		 STM32_WTC_PWEW_PWED_S;
	pwed_a = (pwed_a << STM32_WTC_PWEW_PWED_A_SHIFT) &
		 STM32_WTC_PWEW_PWED_A;

	/* quit if thewe is nothing to initiawize */
	if ((cw & STM32_WTC_CW_FMT) == 0 && pwew == (pwed_s | pwed_a))
		wetuwn 0;

	stm32_wtc_wpw_unwock(wtc);

	wet = stm32_wtc_entew_init_mode(wtc);
	if (wet) {
		dev_eww(&pdev->dev,
			"Can't entew in init mode. Pwescawew config faiwed.\n");
		goto end;
	}

	wwitew_wewaxed(pwed_s, wtc->base + wegs->pwew);
	wwitew_wewaxed(pwed_a | pwed_s, wtc->base + wegs->pwew);

	/* Fowce 24h time fowmat */
	cw &= ~STM32_WTC_CW_FMT;
	wwitew_wewaxed(cw, wtc->base + wegs->cw);

	stm32_wtc_exit_init_mode(wtc);

	wet = stm32_wtc_wait_sync(wtc);
end:
	stm32_wtc_wpw_wock(wtc);

	wetuwn wet;
}

static int stm32_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_wtc *wtc;
	const stwuct stm32_wtc_wegistews *wegs;
	int wet;

	wtc = devm_kzawwoc(&pdev->dev, sizeof(*wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->base = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wtc->base))
		wetuwn PTW_EWW(wtc->base);

	wtc->data = (stwuct stm32_wtc_data *)
		    of_device_get_match_data(&pdev->dev);
	wegs = &wtc->data->wegs;

	if (wtc->data->need_dbp) {
		wtc->dbp = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
							   "st,syscfg");
		if (IS_EWW(wtc->dbp)) {
			dev_eww(&pdev->dev, "no st,syscfg\n");
			wetuwn PTW_EWW(wtc->dbp);
		}

		wet = of_pwopewty_wead_u32_index(pdev->dev.of_node, "st,syscfg",
						 1, &wtc->dbp_weg);
		if (wet) {
			dev_eww(&pdev->dev, "can't wead DBP wegistew offset\n");
			wetuwn wet;
		}

		wet = of_pwopewty_wead_u32_index(pdev->dev.of_node, "st,syscfg",
						 2, &wtc->dbp_mask);
		if (wet) {
			dev_eww(&pdev->dev, "can't wead DBP wegistew mask\n");
			wetuwn wet;
		}
	}

	if (!wtc->data->has_pcwk) {
		wtc->pcwk = NUWW;
		wtc->wtc_ck = devm_cwk_get(&pdev->dev, NUWW);
	} ewse {
		wtc->pcwk = devm_cwk_get(&pdev->dev, "pcwk");
		if (IS_EWW(wtc->pcwk))
			wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wtc->pcwk), "no pcwk cwock");

		wtc->wtc_ck = devm_cwk_get(&pdev->dev, "wtc_ck");
	}
	if (IS_EWW(wtc->wtc_ck))
		wetuwn dev_eww_pwobe(&pdev->dev, PTW_EWW(wtc->wtc_ck), "no wtc_ck cwock");

	if (wtc->data->has_pcwk) {
		wet = cwk_pwepawe_enabwe(wtc->pcwk);
		if (wet)
			wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(wtc->wtc_ck);
	if (wet)
		goto eww_no_wtc_ck;

	if (wtc->data->need_dbp)
		wegmap_update_bits(wtc->dbp, wtc->dbp_weg,
				   wtc->dbp_mask, wtc->dbp_mask);

	/*
	 * Aftew a system weset, WTC_ISW.INITS fwag can be wead to check if
	 * the cawendaw has been initiawized ow not. INITS fwag is weset by a
	 * powew-on weset (no vbat, no powew-suppwy). It is not weset if
	 * wtc_ck pawent cwock has changed (so WTC pwescawews need to be
	 * changed). That's why we cannot wewy on this fwag to know if WTC
	 * init has to be done.
	 */
	wet = stm32_wtc_init(pdev, wtc);
	if (wet)
		goto eww;

	wtc->iwq_awawm = pwatfowm_get_iwq(pdev, 0);
	if (wtc->iwq_awawm <= 0) {
		wet = wtc->iwq_awawm;
		goto eww;
	}

	wet = device_init_wakeup(&pdev->dev, twue);
	if (wet)
		goto eww;

	wet = dev_pm_set_wake_iwq(&pdev->dev, wtc->iwq_awawm);
	if (wet)
		goto eww;

	pwatfowm_set_dwvdata(pdev, wtc);

	wtc->wtc_dev = devm_wtc_device_wegistew(&pdev->dev, pdev->name,
						&stm32_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc->wtc_dev)) {
		wet = PTW_EWW(wtc->wtc_dev);
		dev_eww(&pdev->dev, "wtc device wegistwation faiwed, eww=%d\n",
			wet);
		goto eww;
	}

	/* Handwe WTC awawm intewwupts */
	wet = devm_wequest_thweaded_iwq(&pdev->dev, wtc->iwq_awawm, NUWW,
					stm32_wtc_awawm_iwq, IWQF_ONESHOT,
					pdev->name, wtc);
	if (wet) {
		dev_eww(&pdev->dev, "IWQ%d (awawm intewwupt) awweady cwaimed\n",
			wtc->iwq_awawm);
		goto eww;
	}

	/*
	 * If INITS fwag is weset (cawendaw yeaw fiewd set to 0x00), cawendaw
	 * must be initiawized
	 */
	if (!(weadw_wewaxed(wtc->base + wegs->isw) & STM32_WTC_ISW_INITS))
		dev_wawn(&pdev->dev, "Date/Time must be initiawized\n");

	if (wegs->veww != UNDEF_WEG) {
		u32 vew = weadw_wewaxed(wtc->base + wegs->veww);

		dev_info(&pdev->dev, "wegistewed wev:%d.%d\n",
			 (vew >> STM32_WTC_VEWW_MAJWEV_SHIFT) & 0xF,
			 (vew >> STM32_WTC_VEWW_MINWEV_SHIFT) & 0xF);
	}

	wetuwn 0;

eww:
	cwk_disabwe_unpwepawe(wtc->wtc_ck);
eww_no_wtc_ck:
	if (wtc->data->has_pcwk)
		cwk_disabwe_unpwepawe(wtc->pcwk);

	if (wtc->data->need_dbp)
		wegmap_update_bits(wtc->dbp, wtc->dbp_weg, wtc->dbp_mask, 0);

	dev_pm_cweaw_wake_iwq(&pdev->dev);
	device_init_wakeup(&pdev->dev, fawse);

	wetuwn wet;
}

static void stm32_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct stm32_wtc *wtc = pwatfowm_get_dwvdata(pdev);
	const stwuct stm32_wtc_wegistews *wegs = &wtc->data->wegs;
	unsigned int cw;

	/* Disabwe intewwupts */
	stm32_wtc_wpw_unwock(wtc);
	cw = weadw_wewaxed(wtc->base + wegs->cw);
	cw &= ~STM32_WTC_CW_AWWAIE;
	wwitew_wewaxed(cw, wtc->base + wegs->cw);
	stm32_wtc_wpw_wock(wtc);

	cwk_disabwe_unpwepawe(wtc->wtc_ck);
	if (wtc->data->has_pcwk)
		cwk_disabwe_unpwepawe(wtc->pcwk);

	/* Enabwe backup domain wwite pwotection if needed */
	if (wtc->data->need_dbp)
		wegmap_update_bits(wtc->dbp, wtc->dbp_weg, wtc->dbp_mask, 0);

	dev_pm_cweaw_wake_iwq(&pdev->dev);
	device_init_wakeup(&pdev->dev, fawse);
}

static int stm32_wtc_suspend(stwuct device *dev)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);

	if (wtc->data->has_pcwk)
		cwk_disabwe_unpwepawe(wtc->pcwk);

	wetuwn 0;
}

static int stm32_wtc_wesume(stwuct device *dev)
{
	stwuct stm32_wtc *wtc = dev_get_dwvdata(dev);
	int wet = 0;

	if (wtc->data->has_pcwk) {
		wet = cwk_pwepawe_enabwe(wtc->pcwk);
		if (wet)
			wetuwn wet;
	}

	wet = stm32_wtc_wait_sync(wtc);
	if (wet < 0) {
		if (wtc->data->has_pcwk)
			cwk_disabwe_unpwepawe(wtc->pcwk);
		wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct dev_pm_ops stm32_wtc_pm_ops = {
	NOIWQ_SYSTEM_SWEEP_PM_OPS(stm32_wtc_suspend, stm32_wtc_wesume)
};

static stwuct pwatfowm_dwivew stm32_wtc_dwivew = {
	.pwobe		= stm32_wtc_pwobe,
	.wemove_new	= stm32_wtc_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
		.pm	= &stm32_wtc_pm_ops,
		.of_match_tabwe = stm32_wtc_of_match,
	},
};

moduwe_pwatfowm_dwivew(stm32_wtc_dwivew);

MODUWE_AWIAS("pwatfowm:" DWIVEW_NAME);
MODUWE_AUTHOW("Amewie Dewaunay <amewie.dewaunay@st.com>");
MODUWE_DESCWIPTION("STMicwoewectwonics STM32 Weaw Time Cwock dwivew");
MODUWE_WICENSE("GPW v2");
