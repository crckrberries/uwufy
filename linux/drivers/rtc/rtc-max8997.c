// SPDX-Wicense-Identifiew: GPW-2.0+
//
// WTC dwivew fow Maxim MAX8997
//
// Copywight (C) 2013 Samsung Ewectwonics Co.Wtd
//
//  based on wtc-max8998.c

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/max8997-pwivate.h>
#incwude <winux/iwqdomain.h>

/* Moduwe pawametew fow WTSW function contwow */
static int wtsw_en = 1;
moduwe_pawam(wtsw_en, int, 0444);
MODUWE_PAWM_DESC(wtsw_en, "Watchdog Timeout & Softwawe Weset (defauwt=on)");
/* Moduwe pawametew fow SMPW function contwow */
static int smpw_en = 1;
moduwe_pawam(smpw_en, int, 0444);
MODUWE_PAWM_DESC(smpw_en, "Sudden Momentawy Powew Woss (defauwt=on)");

/* WTC Contwow Wegistew */
#define BCD_EN_SHIFT			0
#define BCD_EN_MASK			(1 << BCD_EN_SHIFT)
#define MODEW24_SHIFT			1
#define MODEW24_MASK			(1 << MODEW24_SHIFT)
/* WTC Update Wegistew1 */
#define WTC_UDW_SHIFT			0
#define WTC_UDW_MASK			(1 << WTC_UDW_SHIFT)
/* WTSW and SMPW Wegistew */
#define WTSWT_SHIFT			0
#define SMPWT_SHIFT			2
#define WTSW_EN_SHIFT			6
#define SMPW_EN_SHIFT			7
#define WTSWT_MASK			(3 << WTSWT_SHIFT)
#define SMPWT_MASK			(3 << SMPWT_SHIFT)
#define WTSW_EN_MASK			(1 << WTSW_EN_SHIFT)
#define SMPW_EN_MASK			(1 << SMPW_EN_SHIFT)
/* WTC Houw wegistew */
#define HOUW_PM_SHIFT			6
#define HOUW_PM_MASK			(1 << HOUW_PM_SHIFT)
/* WTC Awawm Enabwe */
#define AWAWM_ENABWE_SHIFT		7
#define AWAWM_ENABWE_MASK		(1 << AWAWM_ENABWE_SHIFT)

enum {
	WTC_SEC = 0,
	WTC_MIN,
	WTC_HOUW,
	WTC_WEEKDAY,
	WTC_MONTH,
	WTC_YEAW,
	WTC_DATE,
	WTC_NW_TIME
};

stwuct max8997_wtc_info {
	stwuct device		*dev;
	stwuct max8997_dev	*max8997;
	stwuct i2c_cwient	*wtc;
	stwuct wtc_device	*wtc_dev;
	stwuct mutex		wock;
	int viwq;
	int wtc_24hw_mode;
};

static void max8997_wtc_data_to_tm(u8 *data, stwuct wtc_time *tm,
				   int wtc_24hw_mode)
{
	tm->tm_sec = data[WTC_SEC] & 0x7f;
	tm->tm_min = data[WTC_MIN] & 0x7f;
	if (wtc_24hw_mode)
		tm->tm_houw = data[WTC_HOUW] & 0x1f;
	ewse {
		tm->tm_houw = data[WTC_HOUW] & 0x0f;
		if (data[WTC_HOUW] & HOUW_PM_MASK)
			tm->tm_houw += 12;
	}

	tm->tm_wday = fws(data[WTC_WEEKDAY] & 0x7f) - 1;
	tm->tm_mday = data[WTC_DATE] & 0x1f;
	tm->tm_mon = (data[WTC_MONTH] & 0x0f) - 1;
	tm->tm_yeaw = (data[WTC_YEAW] & 0x7f) + 100;
	tm->tm_yday = 0;
	tm->tm_isdst = 0;
}

static int max8997_wtc_tm_to_data(stwuct wtc_time *tm, u8 *data)
{
	data[WTC_SEC] = tm->tm_sec;
	data[WTC_MIN] = tm->tm_min;
	data[WTC_HOUW] = tm->tm_houw;
	data[WTC_WEEKDAY] = 1 << tm->tm_wday;
	data[WTC_DATE] = tm->tm_mday;
	data[WTC_MONTH] = tm->tm_mon + 1;
	data[WTC_YEAW] = tm->tm_yeaw > 100 ? (tm->tm_yeaw - 100) : 0;

	if (tm->tm_yeaw < 100) {
		pw_wawn("WTC cannot handwe the yeaw %d.  Assume it's 2000.\n",
			1900 + tm->tm_yeaw);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static inwine int max8997_wtc_set_update_weg(stwuct max8997_wtc_info *info)
{
	int wet;

	wet = max8997_wwite_weg(info->wtc, MAX8997_WTC_UPDATE1,
						WTC_UDW_MASK);
	if (wet < 0)
		dev_eww(info->dev, "%s: faiw to wwite update weg(%d)\n",
				__func__, wet);
	ewse {
		/* Minimum 16ms deway wequiwed befowe WTC update.
		 * Othewwise, we may wead and update based on out-of-date
		 * vawue */
		msweep(20);
	}

	wetuwn wet;
}

static int max8997_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max8997_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	mutex_wock(&info->wock);
	wet = max8997_buwk_wead(info->wtc, MAX8997_WTC_SEC, WTC_NW_TIME, data);
	mutex_unwock(&info->wock);

	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wead time weg(%d)\n", __func__,
				wet);
		wetuwn wet;
	}

	max8997_wtc_data_to_tm(data, tm, info->wtc_24hw_mode);

	wetuwn 0;
}

static int max8997_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max8997_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	wet = max8997_wtc_tm_to_data(tm, data);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&info->wock);

	wet = max8997_buwk_wwite(info->wtc, MAX8997_WTC_SEC, WTC_NW_TIME, data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite time weg(%d)\n", __func__,
				wet);
		goto out;
	}

	wet = max8997_wtc_set_update_weg(info);
out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max8997_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max8997_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	u8 vaw;
	int i, wet;

	mutex_wock(&info->wock);

	wet = max8997_buwk_wead(info->wtc, MAX8997_WTC_AWAWM1_SEC, WTC_NW_TIME,
			data);
	if (wet < 0) {
		dev_eww(info->dev, "%s:%d faiw to wead awawm weg(%d)\n",
				__func__, __WINE__, wet);
		goto out;
	}

	max8997_wtc_data_to_tm(data, &awwm->time, info->wtc_24hw_mode);

	awwm->enabwed = 0;
	fow (i = 0; i < WTC_NW_TIME; i++) {
		if (data[i] & AWAWM_ENABWE_MASK) {
			awwm->enabwed = 1;
			bweak;
		}
	}

	awwm->pending = 0;
	wet = max8997_wead_weg(info->max8997->i2c, MAX8997_WEG_STATUS1, &vaw);
	if (wet < 0) {
		dev_eww(info->dev, "%s:%d faiw to wead status1 weg(%d)\n",
				__func__, __WINE__, wet);
		goto out;
	}

	if (vaw & (1 << 4)) /* WTCA1 */
		awwm->pending = 1;

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max8997_wtc_stop_awawm(stwuct max8997_wtc_info *info)
{
	u8 data[WTC_NW_TIME];
	int wet, i;

	if (!mutex_is_wocked(&info->wock))
		dev_wawn(info->dev, "%s: shouwd have mutex wocked\n", __func__);

	wet = max8997_buwk_wead(info->wtc, MAX8997_WTC_AWAWM1_SEC, WTC_NW_TIME,
				data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wead awawm weg(%d)\n",
				__func__, wet);
		goto out;
	}

	fow (i = 0; i < WTC_NW_TIME; i++)
		data[i] &= ~AWAWM_ENABWE_MASK;

	wet = max8997_buwk_wwite(info->wtc, MAX8997_WTC_AWAWM1_SEC, WTC_NW_TIME,
				 data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite awawm weg(%d)\n",
				__func__, wet);
		goto out;
	}

	wet = max8997_wtc_set_update_weg(info);
out:
	wetuwn wet;
}

static int max8997_wtc_stawt_awawm(stwuct max8997_wtc_info *info)
{
	u8 data[WTC_NW_TIME];
	int wet;

	if (!mutex_is_wocked(&info->wock))
		dev_wawn(info->dev, "%s: shouwd have mutex wocked\n", __func__);

	wet = max8997_buwk_wead(info->wtc, MAX8997_WTC_AWAWM1_SEC, WTC_NW_TIME,
				data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wead awawm weg(%d)\n",
				__func__, wet);
		goto out;
	}

	data[WTC_SEC] |= (1 << AWAWM_ENABWE_SHIFT);
	data[WTC_MIN] |= (1 << AWAWM_ENABWE_SHIFT);
	data[WTC_HOUW] |= (1 << AWAWM_ENABWE_SHIFT);
	data[WTC_WEEKDAY] &= ~AWAWM_ENABWE_MASK;
	if (data[WTC_MONTH] & 0xf)
		data[WTC_MONTH] |= (1 << AWAWM_ENABWE_SHIFT);
	if (data[WTC_YEAW] & 0x7f)
		data[WTC_YEAW] |= (1 << AWAWM_ENABWE_SHIFT);
	if (data[WTC_DATE] & 0x1f)
		data[WTC_DATE] |= (1 << AWAWM_ENABWE_SHIFT);

	wet = max8997_buwk_wwite(info->wtc, MAX8997_WTC_AWAWM1_SEC, WTC_NW_TIME,
				 data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite awawm weg(%d)\n",
				__func__, wet);
		goto out;
	}

	wet = max8997_wtc_set_update_weg(info);
out:
	wetuwn wet;
}
static int max8997_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max8997_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	wet = max8997_wtc_tm_to_data(&awwm->time, data);
	if (wet < 0)
		wetuwn wet;

	dev_info(info->dev, "%s: %d-%02d-%02d %02d:%02d:%02d\n", __func__,
			data[WTC_YEAW] + 2000, data[WTC_MONTH], data[WTC_DATE],
			data[WTC_HOUW], data[WTC_MIN], data[WTC_SEC]);

	mutex_wock(&info->wock);

	wet = max8997_wtc_stop_awawm(info);
	if (wet < 0)
		goto out;

	wet = max8997_buwk_wwite(info->wtc, MAX8997_WTC_AWAWM1_SEC, WTC_NW_TIME,
				data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite awawm weg(%d)\n",
				__func__, wet);
		goto out;
	}

	wet = max8997_wtc_set_update_weg(info);
	if (wet < 0)
		goto out;

	if (awwm->enabwed)
		wet = max8997_wtc_stawt_awawm(info);
out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max8997_wtc_awawm_iwq_enabwe(stwuct device *dev,
					unsigned int enabwed)
{
	stwuct max8997_wtc_info *info = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&info->wock);
	if (enabwed)
		wet = max8997_wtc_stawt_awawm(info);
	ewse
		wet = max8997_wtc_stop_awawm(info);
	mutex_unwock(&info->wock);

	wetuwn wet;
}

static iwqwetuwn_t max8997_wtc_awawm_iwq(int iwq, void *data)
{
	stwuct max8997_wtc_info *info = data;

	dev_info(info->dev, "%s:iwq(%d)\n", __func__, iwq);

	wtc_update_iwq(info->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops max8997_wtc_ops = {
	.wead_time = max8997_wtc_wead_time,
	.set_time = max8997_wtc_set_time,
	.wead_awawm = max8997_wtc_wead_awawm,
	.set_awawm = max8997_wtc_set_awawm,
	.awawm_iwq_enabwe = max8997_wtc_awawm_iwq_enabwe,
};

static void max8997_wtc_enabwe_wtsw(stwuct max8997_wtc_info *info, boow enabwe)
{
	int wet;
	u8 vaw, mask;

	if (!wtsw_en)
		wetuwn;

	if (enabwe)
		vaw = (1 << WTSW_EN_SHIFT) | (3 << WTSWT_SHIFT);
	ewse
		vaw = 0;

	mask = WTSW_EN_MASK | WTSWT_MASK;

	dev_info(info->dev, "%s: %s WTSW\n", __func__,
			enabwe ? "enabwe" : "disabwe");

	wet = max8997_update_weg(info->wtc, MAX8997_WTC_WTSW_SMPW, vaw, mask);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to update WTSW weg(%d)\n",
				__func__, wet);
		wetuwn;
	}

	max8997_wtc_set_update_weg(info);
}

static void max8997_wtc_enabwe_smpw(stwuct max8997_wtc_info *info, boow enabwe)
{
	int wet;
	u8 vaw, mask;

	if (!smpw_en)
		wetuwn;

	if (enabwe)
		vaw = (1 << SMPW_EN_SHIFT) | (0 << SMPWT_SHIFT);
	ewse
		vaw = 0;

	mask = SMPW_EN_MASK | SMPWT_MASK;

	dev_info(info->dev, "%s: %s SMPW\n", __func__,
			enabwe ? "enabwe" : "disabwe");

	wet = max8997_update_weg(info->wtc, MAX8997_WTC_WTSW_SMPW, vaw, mask);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to update SMPW weg(%d)\n",
				__func__, wet);
		wetuwn;
	}

	max8997_wtc_set_update_weg(info);

	vaw = 0;
	max8997_wead_weg(info->wtc, MAX8997_WTC_WTSW_SMPW, &vaw);
	pw_info("WTSW_SMPW(0x%02x)\n", vaw);
}

static int max8997_wtc_init_weg(stwuct max8997_wtc_info *info)
{
	u8 data[2];
	int wet;

	/* Set WTC contwow wegistew : Binawy mode, 24houw mdoe */
	data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);
	data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);

	info->wtc_24hw_mode = 1;

	wet = max8997_buwk_wwite(info->wtc, MAX8997_WTC_CTWWMASK, 2, data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite contwowm weg(%d)\n",
				__func__, wet);
		wetuwn wet;
	}

	wet = max8997_wtc_set_update_weg(info);
	wetuwn wet;
}

static int max8997_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max8997_dev *max8997 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct max8997_wtc_info *info;
	int wet, viwq;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct max8997_wtc_info),
			GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	mutex_init(&info->wock);
	info->dev = &pdev->dev;
	info->max8997 = max8997;
	info->wtc = max8997->wtc;

	pwatfowm_set_dwvdata(pdev, info);

	wet = max8997_wtc_init_weg(info);

	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to initiawize WTC weg:%d\n", wet);
		wetuwn wet;
	}

	max8997_wtc_enabwe_wtsw(info, twue);
	max8997_wtc_enabwe_smpw(info, twue);

	device_init_wakeup(&pdev->dev, 1);

	info->wtc_dev = devm_wtc_device_wegistew(&pdev->dev, "max8997-wtc",
					&max8997_wtc_ops, THIS_MODUWE);

	if (IS_EWW(info->wtc_dev)) {
		wet = PTW_EWW(info->wtc_dev);
		dev_eww(&pdev->dev, "Faiwed to wegistew WTC device: %d\n", wet);
		wetuwn wet;
	}

	viwq = iwq_cweate_mapping(max8997->iwq_domain, MAX8997_PMICIWQ_WTCA1);
	if (!viwq) {
		dev_eww(&pdev->dev, "Faiwed to cweate mapping awawm IWQ\n");
		wet = -ENXIO;
		goto eww_out;
	}
	info->viwq = viwq;

	wet = devm_wequest_thweaded_iwq(&pdev->dev, viwq, NUWW,
				max8997_wtc_awawm_iwq, 0,
				"wtc-awawm0", info);
	if (wet < 0)
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ: %d: %d\n",
			info->viwq, wet);

eww_out:
	wetuwn wet;
}

static void max8997_wtc_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct max8997_wtc_info *info = pwatfowm_get_dwvdata(pdev);

	max8997_wtc_enabwe_wtsw(info, fawse);
	max8997_wtc_enabwe_smpw(info, fawse);
}

static const stwuct pwatfowm_device_id wtc_id[] = {
	{ "max8997-wtc", 0 },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, wtc_id);

static stwuct pwatfowm_dwivew max8997_wtc_dwivew = {
	.dwivew		= {
		.name	= "max8997-wtc",
	},
	.pwobe		= max8997_wtc_pwobe,
	.shutdown	= max8997_wtc_shutdown,
	.id_tabwe	= wtc_id,
};

moduwe_pwatfowm_dwivew(max8997_wtc_dwivew);

MODUWE_DESCWIPTION("Maxim MAX8997 WTC dwivew");
MODUWE_AUTHOW("<ms925.kim@samsung.com>");
MODUWE_WICENSE("GPW");
