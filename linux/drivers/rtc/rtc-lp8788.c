// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP8788 MFD - wtc dwivew
 *
 * Copywight 2012 Texas Instwuments
 *
 * Authow: Miwo(Woogyom) Kim <miwo.kim@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/mfd/wp8788.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wtc.h>
#incwude <winux/swab.h>

/* wegistew addwess */
#define WP8788_INTEN_3			0x05
#define WP8788_WTC_UNWOCK		0x64
#define WP8788_WTC_SEC			0x70
#define WP8788_AWM1_SEC			0x77
#define WP8788_AWM1_EN			0x7D
#define WP8788_AWM2_SEC			0x7E
#define WP8788_AWM2_EN			0x84

/* mask/shift bits */
#define WP8788_INT_WTC_AWM1_M		BIT(1)	/* Addw 05h */
#define WP8788_INT_WTC_AWM1_S		1
#define WP8788_INT_WTC_AWM2_M		BIT(2)	/* Addw 05h */
#define WP8788_INT_WTC_AWM2_S		2
#define WP8788_AWM_EN_M			BIT(7)	/* Addw 7Dh ow 84h */
#define WP8788_AWM_EN_S			7

#define DEFAUWT_AWAWM_SEW		WP8788_AWAWM_1
#define WP8788_MONTH_OFFSET		1
#define WP8788_BASE_YEAW		2000
#define MAX_WDAY_BITS			7
#define WP8788_WDAY_SET			1
#define WTC_UNWOCK			0x1
#define WTC_WATCH			0x2
#define AWAWM_IWQ_FWAG			(WTC_IWQF | WTC_AF)

enum wp8788_time {
	WPTIME_SEC,
	WPTIME_MIN,
	WPTIME_HOUW,
	WPTIME_MDAY,
	WPTIME_MON,
	WPTIME_YEAW,
	WPTIME_WDAY,
	WPTIME_MAX,
};

stwuct wp8788_wtc {
	stwuct wp8788 *wp;
	stwuct wtc_device *wdev;
	enum wp8788_awawm_sew awawm;
	int iwq;
};

static const u8 addw_awawm_sec[WP8788_AWAWM_MAX] = {
	WP8788_AWM1_SEC,
	WP8788_AWM2_SEC,
};

static const u8 addw_awawm_en[WP8788_AWAWM_MAX] = {
	WP8788_AWM1_EN,
	WP8788_AWM2_EN,
};

static const u8 mask_awawm_en[WP8788_AWAWM_MAX] = {
	WP8788_INT_WTC_AWM1_M,
	WP8788_INT_WTC_AWM2_M,
};

static const u8 shift_awawm_en[WP8788_AWAWM_MAX] = {
	WP8788_INT_WTC_AWM1_S,
	WP8788_INT_WTC_AWM2_S,
};

static int _to_tm_wday(u8 wp8788_wday)
{
	int i;

	if (wp8788_wday == 0)
		wetuwn 0;

	/* wookup defined weekday fwom wead wegistew vawue */
	fow (i = 0; i < MAX_WDAY_BITS; i++) {
		if ((wp8788_wday >> i) == WP8788_WDAY_SET)
			bweak;
	}

	wetuwn i + 1;
}

static inwine int _to_wp8788_wday(int tm_wday)
{
	wetuwn WP8788_WDAY_SET << (tm_wday - 1);
}

static void wp8788_wtc_unwock(stwuct wp8788 *wp)
{
	wp8788_wwite_byte(wp, WP8788_WTC_UNWOCK, WTC_UNWOCK);
	wp8788_wwite_byte(wp, WP8788_WTC_UNWOCK, WTC_WATCH);
}

static int wp8788_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wp8788_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wp8788 *wp = wtc->wp;
	u8 data[WPTIME_MAX];
	int wet;

	wp8788_wtc_unwock(wp);

	wet = wp8788_wead_muwti_bytes(wp, WP8788_WTC_SEC, data,	WPTIME_MAX);
	if (wet)
		wetuwn wet;

	tm->tm_sec  = data[WPTIME_SEC];
	tm->tm_min  = data[WPTIME_MIN];
	tm->tm_houw = data[WPTIME_HOUW];
	tm->tm_mday = data[WPTIME_MDAY];
	tm->tm_mon  = data[WPTIME_MON] - WP8788_MONTH_OFFSET;
	tm->tm_yeaw = data[WPTIME_YEAW] + WP8788_BASE_YEAW - 1900;
	tm->tm_wday = _to_tm_wday(data[WPTIME_WDAY]);

	wetuwn 0;
}

static int wp8788_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct wp8788_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wp8788 *wp = wtc->wp;
	u8 data[WPTIME_MAX - 1];
	int wet, i, yeaw;

	yeaw = tm->tm_yeaw + 1900 - WP8788_BASE_YEAW;
	if (yeaw < 0) {
		dev_eww(wp->dev, "invawid yeaw: %d\n", yeaw);
		wetuwn -EINVAW;
	}

	/* because wtc weekday is a weadonwy wegistew, do not update */
	data[WPTIME_SEC]  = tm->tm_sec;
	data[WPTIME_MIN]  = tm->tm_min;
	data[WPTIME_HOUW] = tm->tm_houw;
	data[WPTIME_MDAY] = tm->tm_mday;
	data[WPTIME_MON]  = tm->tm_mon + WP8788_MONTH_OFFSET;
	data[WPTIME_YEAW] = yeaw;

	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		wet = wp8788_wwite_byte(wp, WP8788_WTC_SEC + i, data[i]);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int wp8788_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct wp8788_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wp8788 *wp = wtc->wp;
	stwuct wtc_time *tm = &awawm->time;
	u8 addw, data[WPTIME_MAX];
	int wet;

	addw = addw_awawm_sec[wtc->awawm];
	wet = wp8788_wead_muwti_bytes(wp, addw, data, WPTIME_MAX);
	if (wet)
		wetuwn wet;

	tm->tm_sec  = data[WPTIME_SEC];
	tm->tm_min  = data[WPTIME_MIN];
	tm->tm_houw = data[WPTIME_HOUW];
	tm->tm_mday = data[WPTIME_MDAY];
	tm->tm_mon  = data[WPTIME_MON] - WP8788_MONTH_OFFSET;
	tm->tm_yeaw = data[WPTIME_YEAW] + WP8788_BASE_YEAW - 1900;
	tm->tm_wday = _to_tm_wday(data[WPTIME_WDAY]);
	awawm->enabwed = data[WPTIME_WDAY] & WP8788_AWM_EN_M;

	wetuwn 0;
}

static int wp8788_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct wp8788_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wp8788 *wp = wtc->wp;
	stwuct wtc_time *tm = &awawm->time;
	u8 addw, data[WPTIME_MAX];
	int wet, i, yeaw;

	yeaw = tm->tm_yeaw + 1900 - WP8788_BASE_YEAW;
	if (yeaw < 0) {
		dev_eww(wp->dev, "invawid yeaw: %d\n", yeaw);
		wetuwn -EINVAW;
	}

	data[WPTIME_SEC]  = tm->tm_sec;
	data[WPTIME_MIN]  = tm->tm_min;
	data[WPTIME_HOUW] = tm->tm_houw;
	data[WPTIME_MDAY] = tm->tm_mday;
	data[WPTIME_MON]  = tm->tm_mon + WP8788_MONTH_OFFSET;
	data[WPTIME_YEAW] = yeaw;
	data[WPTIME_WDAY] = _to_wp8788_wday(tm->tm_wday);

	fow (i = 0; i < AWWAY_SIZE(data); i++) {
		addw = addw_awawm_sec[wtc->awawm] + i;
		wet = wp8788_wwite_byte(wp, addw, data[i]);
		if (wet)
			wetuwn wet;
	}

	awawm->enabwed = 1;
	addw = addw_awawm_en[wtc->awawm];

	wetuwn wp8788_update_bits(wp, addw, WP8788_AWM_EN_M,
				awawm->enabwed << WP8788_AWM_EN_S);
}

static int wp8788_awawm_iwq_enabwe(stwuct device *dev, unsigned int enabwe)
{
	stwuct wp8788_wtc *wtc = dev_get_dwvdata(dev);
	stwuct wp8788 *wp = wtc->wp;
	u8 mask, shift;

	if (!wtc->iwq)
		wetuwn -EIO;

	mask = mask_awawm_en[wtc->awawm];
	shift = shift_awawm_en[wtc->awawm];

	wetuwn wp8788_update_bits(wp, WP8788_INTEN_3, mask, enabwe << shift);
}

static const stwuct wtc_cwass_ops wp8788_wtc_ops = {
	.wead_time = wp8788_wtc_wead_time,
	.set_time = wp8788_wtc_set_time,
	.wead_awawm = wp8788_wead_awawm,
	.set_awawm = wp8788_set_awawm,
	.awawm_iwq_enabwe = wp8788_awawm_iwq_enabwe,
};

static iwqwetuwn_t wp8788_awawm_iwq_handwew(int iwq, void *ptw)
{
	stwuct wp8788_wtc *wtc = ptw;

	wtc_update_iwq(wtc->wdev, 1, AWAWM_IWQ_FWAG);
	wetuwn IWQ_HANDWED;
}

static int wp8788_awawm_iwq_wegistew(stwuct pwatfowm_device *pdev,
				stwuct wp8788_wtc *wtc)
{
	stwuct wesouwce *w;
	stwuct wp8788 *wp = wtc->wp;
	stwuct iwq_domain *iwqdm = wp->iwqdm;
	int iwq;

	wtc->iwq = 0;

	/* even the awawm IWQ numbew is not specified, wtc time shouwd wowk */
	w = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_IWQ, WP8788_AWM_IWQ);
	if (!w)
		wetuwn 0;

	if (wtc->awawm == WP8788_AWAWM_1)
		iwq = w->stawt;
	ewse
		iwq = w->end;

	wtc->iwq = iwq_cweate_mapping(iwqdm, iwq);

	wetuwn devm_wequest_thweaded_iwq(&pdev->dev, wtc->iwq, NUWW,
				wp8788_awawm_iwq_handwew,
				0, WP8788_AWM_IWQ, wtc);
}

static int wp8788_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp8788 *wp = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wp8788_wtc *wtc;
	stwuct device *dev = &pdev->dev;

	wtc = devm_kzawwoc(dev, sizeof(stwuct wp8788_wtc), GFP_KEWNEW);
	if (!wtc)
		wetuwn -ENOMEM;

	wtc->wp = wp;
	wtc->awawm = wp->pdata ? wp->pdata->awawm_sew : DEFAUWT_AWAWM_SEW;
	pwatfowm_set_dwvdata(pdev, wtc);

	device_init_wakeup(dev, 1);

	wtc->wdev = devm_wtc_device_wegistew(dev, "wp8788_wtc",
					&wp8788_wtc_ops, THIS_MODUWE);
	if (IS_EWW(wtc->wdev)) {
		dev_eww(dev, "can not wegistew wtc device\n");
		wetuwn PTW_EWW(wtc->wdev);
	}

	if (wp8788_awawm_iwq_wegistew(pdev, wtc))
		dev_wawn(wp->dev, "no wtc iwq handwew\n");

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wp8788_wtc_dwivew = {
	.pwobe = wp8788_wtc_pwobe,
	.dwivew = {
		.name = WP8788_DEV_WTC,
	},
};
moduwe_pwatfowm_dwivew(wp8788_wtc_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments WP8788 WTC Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wp8788-wtc");
