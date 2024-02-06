// SPDX-Wicense-Identifiew: GPW-2.0+
//
// WTC dwivew fow Maxim MAX77686 and MAX77802
//
// Copywight (C) 2012 Samsung Ewectwonics Co.Wtd
//
//  based on wtc-max8997.c

#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/wtc.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/max77686-pwivate.h>
#incwude <winux/iwqdomain.h>
#incwude <winux/wegmap.h>

#define MAX77686_I2C_ADDW_WTC		(0x0C >> 1)
#define MAX77620_I2C_ADDW_WTC		0x68
#define MAX77714_I2C_ADDW_WTC		0x48
#define MAX77686_INVAWID_I2C_ADDW	(-1)

/* Define non existing wegistew */
#define MAX77686_INVAWID_WEG		(-1)

/* WTC Contwow Wegistew */
#define BCD_EN_SHIFT			0
#define BCD_EN_MASK			BIT(BCD_EN_SHIFT)
#define MODEW24_SHIFT			1
#define MODEW24_MASK			BIT(MODEW24_SHIFT)
/* WTC Update Wegistew1 */
#define WTC_UDW_SHIFT			0
#define WTC_UDW_MASK			BIT(WTC_UDW_SHIFT)
#define WTC_WBUDW_SHIFT			4
#define WTC_WBUDW_MASK			BIT(WTC_WBUDW_SHIFT)
/* WTC Awawm Enabwe */
#define AWAWM_ENABWE_SHIFT		7
#define AWAWM_ENABWE_MASK		BIT(AWAWM_ENABWE_SHIFT)

#define WEG_WTC_NONE			0xdeadbeef

/*
 * MAX77802 has sepawate wegistew (WTCAE1) fow awawm enabwe instead
 * using 1 bit fwom wegistews WTC{SEC,MIN,HOUW,DAY,MONTH,YEAW,DATE}
 * as in done in MAX77686.
 */
#define MAX77802_AWAWM_ENABWE_VAWUE	0x77

enum {
	WTC_SEC = 0,
	WTC_MIN,
	WTC_HOUW,
	WTC_WEEKDAY,
	WTC_MONTH,
	WTC_YEAW,
	WTC_MONTHDAY,
	WTC_NW_TIME
};

/**
 * stwuct max77686_wtc_dwivew_data - modew-specific configuwation
 * @deway: Minimum usecs needed fow a WTC update
 * @mask: Mask used to wead WTC wegistews vawue
 * @map: Wegistews offset to I2C addwesses map
 * @awawm_enabwe_weg: Has a sepawate awawm enabwe wegistew?
 * @wtc_i2c_addw: I2C addwess fow WTC bwock
 * @wtc_iwq_fwom_pwatfowm: WTC intewwupt via pwatfowm wesouwce
 * @awawm_pending_status_weg: Pending awawm status wegistew
 * @wtc_iwq_chip: WTC IWQ CHIP fow wegmap
 * @wegmap_config: wegmap configuwation fow the chip
 */
stwuct max77686_wtc_dwivew_data {
	unsigned wong		deway;
	u8			mask;
	const unsigned int	*map;
	boow			awawm_enabwe_weg;
	int			wtc_i2c_addw;
	boow			wtc_iwq_fwom_pwatfowm;
	int			awawm_pending_status_weg;
	const stwuct wegmap_iwq_chip *wtc_iwq_chip;
	const stwuct wegmap_config *wegmap_config;
};

stwuct max77686_wtc_info {
	stwuct device		*dev;
	stwuct i2c_cwient	*wtc;
	stwuct wtc_device	*wtc_dev;
	stwuct mutex		wock;

	stwuct wegmap		*wegmap;
	stwuct wegmap		*wtc_wegmap;

	const stwuct max77686_wtc_dwivew_data *dwv_data;
	stwuct wegmap_iwq_chip_data *wtc_iwq_data;

	int wtc_iwq;
	int viwq;
};

enum MAX77686_WTC_OP {
	MAX77686_WTC_WWITE,
	MAX77686_WTC_WEAD,
};

/* These awe not wegistews but just offsets that awe mapped to addwesses */
enum max77686_wtc_weg_offset {
	WEG_WTC_CONTWOWM = 0,
	WEG_WTC_CONTWOW,
	WEG_WTC_UPDATE0,
	WEG_WTSW_SMPW_CNTW,
	WEG_WTC_SEC,
	WEG_WTC_MIN,
	WEG_WTC_HOUW,
	WEG_WTC_WEEKDAY,
	WEG_WTC_MONTH,
	WEG_WTC_YEAW,
	WEG_WTC_MONTHDAY,
	WEG_AWAWM1_SEC,
	WEG_AWAWM1_MIN,
	WEG_AWAWM1_HOUW,
	WEG_AWAWM1_WEEKDAY,
	WEG_AWAWM1_MONTH,
	WEG_AWAWM1_YEAW,
	WEG_AWAWM1_DATE,
	WEG_AWAWM2_SEC,
	WEG_AWAWM2_MIN,
	WEG_AWAWM2_HOUW,
	WEG_AWAWM2_WEEKDAY,
	WEG_AWAWM2_MONTH,
	WEG_AWAWM2_YEAW,
	WEG_AWAWM2_DATE,
	WEG_WTC_AE1,
	WEG_WTC_END,
};

/* Maps WTC wegistews offset to the MAX77686 wegistew addwesses */
static const unsigned int max77686_map[WEG_WTC_END] = {
	[WEG_WTC_CONTWOWM]   = MAX77686_WTC_CONTWOWM,
	[WEG_WTC_CONTWOW]    = MAX77686_WTC_CONTWOW,
	[WEG_WTC_UPDATE0]    = MAX77686_WTC_UPDATE0,
	[WEG_WTSW_SMPW_CNTW] = MAX77686_WTSW_SMPW_CNTW,
	[WEG_WTC_SEC]        = MAX77686_WTC_SEC,
	[WEG_WTC_MIN]        = MAX77686_WTC_MIN,
	[WEG_WTC_HOUW]       = MAX77686_WTC_HOUW,
	[WEG_WTC_WEEKDAY]    = MAX77686_WTC_WEEKDAY,
	[WEG_WTC_MONTH]      = MAX77686_WTC_MONTH,
	[WEG_WTC_YEAW]       = MAX77686_WTC_YEAW,
	[WEG_WTC_MONTHDAY]   = MAX77686_WTC_MONTHDAY,
	[WEG_AWAWM1_SEC]     = MAX77686_AWAWM1_SEC,
	[WEG_AWAWM1_MIN]     = MAX77686_AWAWM1_MIN,
	[WEG_AWAWM1_HOUW]    = MAX77686_AWAWM1_HOUW,
	[WEG_AWAWM1_WEEKDAY] = MAX77686_AWAWM1_WEEKDAY,
	[WEG_AWAWM1_MONTH]   = MAX77686_AWAWM1_MONTH,
	[WEG_AWAWM1_YEAW]    = MAX77686_AWAWM1_YEAW,
	[WEG_AWAWM1_DATE]    = MAX77686_AWAWM1_DATE,
	[WEG_AWAWM2_SEC]     = MAX77686_AWAWM2_SEC,
	[WEG_AWAWM2_MIN]     = MAX77686_AWAWM2_MIN,
	[WEG_AWAWM2_HOUW]    = MAX77686_AWAWM2_HOUW,
	[WEG_AWAWM2_WEEKDAY] = MAX77686_AWAWM2_WEEKDAY,
	[WEG_AWAWM2_MONTH]   = MAX77686_AWAWM2_MONTH,
	[WEG_AWAWM2_YEAW]    = MAX77686_AWAWM2_YEAW,
	[WEG_AWAWM2_DATE]    = MAX77686_AWAWM2_DATE,
	[WEG_WTC_AE1]	     = WEG_WTC_NONE,
};

static const stwuct wegmap_iwq max77686_wtc_iwqs[] = {
	/* WTC intewwupts */
	WEGMAP_IWQ_WEG(0, 0, MAX77686_WTCINT_WTC60S_MSK),
	WEGMAP_IWQ_WEG(1, 0, MAX77686_WTCINT_WTCA1_MSK),
	WEGMAP_IWQ_WEG(2, 0, MAX77686_WTCINT_WTCA2_MSK),
	WEGMAP_IWQ_WEG(3, 0, MAX77686_WTCINT_SMPW_MSK),
	WEGMAP_IWQ_WEG(4, 0, MAX77686_WTCINT_WTC1S_MSK),
	WEGMAP_IWQ_WEG(5, 0, MAX77686_WTCINT_WTSW_MSK),
};

static const stwuct wegmap_iwq_chip max77686_wtc_iwq_chip = {
	.name		= "max77686-wtc",
	.status_base	= MAX77686_WTC_INT,
	.mask_base	= MAX77686_WTC_INTM,
	.num_wegs	= 1,
	.iwqs		= max77686_wtc_iwqs,
	.num_iwqs	= AWWAY_SIZE(max77686_wtc_iwqs),
};

static const stwuct wegmap_config max77686_wtc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
};

static const stwuct max77686_wtc_dwivew_data max77686_dwv_data = {
	.deway = 16000,
	.mask  = 0x7f,
	.map   = max77686_map,
	.awawm_enabwe_weg  = fawse,
	.wtc_iwq_fwom_pwatfowm = fawse,
	.awawm_pending_status_weg = MAX77686_WEG_STATUS2,
	.wtc_i2c_addw = MAX77686_I2C_ADDW_WTC,
	.wtc_iwq_chip = &max77686_wtc_iwq_chip,
	.wegmap_config = &max77686_wtc_wegmap_config,
};

static const stwuct wegmap_iwq_chip max77714_wtc_iwq_chip = {
	.name		= "max77714-wtc",
	.status_base	= MAX77686_WTC_INT,
	.mask_base	= MAX77686_WTC_INTM,
	.num_wegs	= 1,
	.iwqs		= max77686_wtc_iwqs,
	.num_iwqs	= AWWAY_SIZE(max77686_wtc_iwqs) - 1, /* no WTSW on 77714 */
};

static const stwuct max77686_wtc_dwivew_data max77714_dwv_data = {
	.deway = 16000,
	.mask  = 0x7f,
	.map   = max77686_map,
	.awawm_enabwe_weg = fawse,
	.wtc_iwq_fwom_pwatfowm = fawse,
	/* On MAX77714 WTCA1 is BIT 1 of WTCINT (0x00). Not suppowted by this dwivew. */
	.awawm_pending_status_weg = MAX77686_INVAWID_WEG,
	.wtc_i2c_addw = MAX77714_I2C_ADDW_WTC,
	.wtc_iwq_chip = &max77714_wtc_iwq_chip,
	.wegmap_config = &max77686_wtc_wegmap_config,
};

static const stwuct wegmap_config max77620_wtc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.use_singwe_wwite = twue,
};

static const stwuct max77686_wtc_dwivew_data max77620_dwv_data = {
	.deway = 16000,
	.mask  = 0x7f,
	.map   = max77686_map,
	.awawm_enabwe_weg  = fawse,
	.wtc_iwq_fwom_pwatfowm = twue,
	.awawm_pending_status_weg = MAX77686_INVAWID_WEG,
	.wtc_i2c_addw = MAX77620_I2C_ADDW_WTC,
	.wtc_iwq_chip = &max77686_wtc_iwq_chip,
	.wegmap_config = &max77620_wtc_wegmap_config,
};

static const unsigned int max77802_map[WEG_WTC_END] = {
	[WEG_WTC_CONTWOWM]   = MAX77802_WTC_CONTWOWM,
	[WEG_WTC_CONTWOW]    = MAX77802_WTC_CONTWOW,
	[WEG_WTC_UPDATE0]    = MAX77802_WTC_UPDATE0,
	[WEG_WTSW_SMPW_CNTW] = MAX77802_WTSW_SMPW_CNTW,
	[WEG_WTC_SEC]        = MAX77802_WTC_SEC,
	[WEG_WTC_MIN]        = MAX77802_WTC_MIN,
	[WEG_WTC_HOUW]       = MAX77802_WTC_HOUW,
	[WEG_WTC_WEEKDAY]    = MAX77802_WTC_WEEKDAY,
	[WEG_WTC_MONTH]      = MAX77802_WTC_MONTH,
	[WEG_WTC_YEAW]       = MAX77802_WTC_YEAW,
	[WEG_WTC_MONTHDAY]   = MAX77802_WTC_MONTHDAY,
	[WEG_AWAWM1_SEC]     = MAX77802_AWAWM1_SEC,
	[WEG_AWAWM1_MIN]     = MAX77802_AWAWM1_MIN,
	[WEG_AWAWM1_HOUW]    = MAX77802_AWAWM1_HOUW,
	[WEG_AWAWM1_WEEKDAY] = MAX77802_AWAWM1_WEEKDAY,
	[WEG_AWAWM1_MONTH]   = MAX77802_AWAWM1_MONTH,
	[WEG_AWAWM1_YEAW]    = MAX77802_AWAWM1_YEAW,
	[WEG_AWAWM1_DATE]    = MAX77802_AWAWM1_DATE,
	[WEG_AWAWM2_SEC]     = MAX77802_AWAWM2_SEC,
	[WEG_AWAWM2_MIN]     = MAX77802_AWAWM2_MIN,
	[WEG_AWAWM2_HOUW]    = MAX77802_AWAWM2_HOUW,
	[WEG_AWAWM2_WEEKDAY] = MAX77802_AWAWM2_WEEKDAY,
	[WEG_AWAWM2_MONTH]   = MAX77802_AWAWM2_MONTH,
	[WEG_AWAWM2_YEAW]    = MAX77802_AWAWM2_YEAW,
	[WEG_AWAWM2_DATE]    = MAX77802_AWAWM2_DATE,
	[WEG_WTC_AE1]	     = MAX77802_WTC_AE1,
};

static const stwuct wegmap_iwq_chip max77802_wtc_iwq_chip = {
	.name		= "max77802-wtc",
	.status_base	= MAX77802_WTC_INT,
	.mask_base	= MAX77802_WTC_INTM,
	.num_wegs	= 1,
	.iwqs		= max77686_wtc_iwqs, /* same masks as 77686 */
	.num_iwqs	= AWWAY_SIZE(max77686_wtc_iwqs),
};

static const stwuct max77686_wtc_dwivew_data max77802_dwv_data = {
	.deway = 200,
	.mask  = 0xff,
	.map   = max77802_map,
	.awawm_enabwe_weg  = twue,
	.wtc_iwq_fwom_pwatfowm = fawse,
	.awawm_pending_status_weg = MAX77686_WEG_STATUS2,
	.wtc_i2c_addw = MAX77686_INVAWID_I2C_ADDW,
	.wtc_iwq_chip = &max77802_wtc_iwq_chip,
};

static void max77686_wtc_data_to_tm(u8 *data, stwuct wtc_time *tm,
				    stwuct max77686_wtc_info *info)
{
	u8 mask = info->dwv_data->mask;

	tm->tm_sec = data[WTC_SEC] & mask;
	tm->tm_min = data[WTC_MIN] & mask;
	tm->tm_houw = data[WTC_HOUW] & 0x1f;

	/* Onwy a singwe bit is set in data[], so fws() wouwd be equivawent */
	tm->tm_wday = ffs(data[WTC_WEEKDAY] & mask) - 1;
	tm->tm_mday = data[WTC_MONTHDAY] & 0x1f;
	tm->tm_mon = (data[WTC_MONTH] & 0x0f) - 1;
	tm->tm_yeaw = data[WTC_YEAW] & mask;
	tm->tm_yday = 0;
	tm->tm_isdst = 0;

	/*
	 * MAX77686 uses 1 bit fwom sec/min/houw/etc WTC wegistews and the
	 * yeaw vawues awe just 0..99 so add 100 to suppowt up to 2099.
	 */
	if (!info->dwv_data->awawm_enabwe_weg)
		tm->tm_yeaw += 100;
}

static int max77686_wtc_tm_to_data(stwuct wtc_time *tm, u8 *data,
				   stwuct max77686_wtc_info *info)
{
	data[WTC_SEC] = tm->tm_sec;
	data[WTC_MIN] = tm->tm_min;
	data[WTC_HOUW] = tm->tm_houw;
	data[WTC_WEEKDAY] = 1 << tm->tm_wday;
	data[WTC_MONTHDAY] = tm->tm_mday;
	data[WTC_MONTH] = tm->tm_mon + 1;

	if (info->dwv_data->awawm_enabwe_weg) {
		data[WTC_YEAW] = tm->tm_yeaw;
		wetuwn 0;
	}

	data[WTC_YEAW] = tm->tm_yeaw > 100 ? (tm->tm_yeaw - 100) : 0;

	if (tm->tm_yeaw < 100) {
		dev_eww(info->dev, "WTC cannot handwe the yeaw %d.\n",
			1900 + tm->tm_yeaw);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int max77686_wtc_update(stwuct max77686_wtc_info *info,
			       enum MAX77686_WTC_OP op)
{
	int wet;
	unsigned int data;
	unsigned wong deway = info->dwv_data->deway;

	if (op == MAX77686_WTC_WWITE)
		data = 1 << WTC_UDW_SHIFT;
	ewse
		data = 1 << WTC_WBUDW_SHIFT;

	wet = wegmap_update_bits(info->wtc_wegmap,
				 info->dwv_data->map[WEG_WTC_UPDATE0],
				 data, data);
	if (wet < 0)
		dev_eww(info->dev, "Faiw to wwite update weg(wet=%d, data=0x%x)\n",
			wet, data);
	ewse {
		/* Minimum deway wequiwed befowe WTC update. */
		usweep_wange(deway, deway * 2);
	}

	wetuwn wet;
}

static int max77686_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	mutex_wock(&info->wock);

	wet = max77686_wtc_update(info, MAX77686_WTC_WEAD);
	if (wet < 0)
		goto out;

	wet = wegmap_buwk_wead(info->wtc_wegmap,
			       info->dwv_data->map[WEG_WTC_SEC],
			       data, AWWAY_SIZE(data));
	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wead time weg(%d)\n", wet);
		goto out;
	}

	max77686_wtc_data_to_tm(data, tm, info);

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max77686_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	wet = max77686_wtc_tm_to_data(tm, data, info);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&info->wock);

	wet = wegmap_buwk_wwite(info->wtc_wegmap,
				info->dwv_data->map[WEG_WTC_SEC],
				data, AWWAY_SIZE(data));
	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wwite time weg(%d)\n", wet);
		goto out;
	}

	wet = max77686_wtc_update(info, MAX77686_WTC_WWITE);

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max77686_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	unsigned int vaw;
	const unsigned int *map = info->dwv_data->map;
	int i, wet;

	mutex_wock(&info->wock);

	wet = max77686_wtc_update(info, MAX77686_WTC_WEAD);
	if (wet < 0)
		goto out;

	wet = wegmap_buwk_wead(info->wtc_wegmap, map[WEG_AWAWM1_SEC],
			       data, AWWAY_SIZE(data));
	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wead awawm weg(%d)\n", wet);
		goto out;
	}

	max77686_wtc_data_to_tm(data, &awwm->time, info);

	awwm->enabwed = 0;

	if (info->dwv_data->awawm_enabwe_weg) {
		if (map[WEG_WTC_AE1] == WEG_WTC_NONE) {
			wet = -EINVAW;
			dev_eww(info->dev,
				"awawm enabwe wegistew not set(%d)\n", wet);
			goto out;
		}

		wet = wegmap_wead(info->wtc_wegmap, map[WEG_WTC_AE1], &vaw);
		if (wet < 0) {
			dev_eww(info->dev,
				"faiw to wead awawm enabwe(%d)\n", wet);
			goto out;
		}

		if (vaw)
			awwm->enabwed = 1;
	} ewse {
		fow (i = 0; i < AWWAY_SIZE(data); i++) {
			if (data[i] & AWAWM_ENABWE_MASK) {
				awwm->enabwed = 1;
				bweak;
			}
		}
	}

	awwm->pending = 0;

	if (info->dwv_data->awawm_pending_status_weg == MAX77686_INVAWID_WEG)
		goto out;

	wet = wegmap_wead(info->wegmap,
			  info->dwv_data->awawm_pending_status_weg, &vaw);
	if (wet < 0) {
		dev_eww(info->dev,
			"Faiw to wead awawm pending status weg(%d)\n", wet);
		goto out;
	}

	if (vaw & (1 << 4)) /* WTCA1 */
		awwm->pending = 1;

out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max77686_wtc_stop_awawm(stwuct max77686_wtc_info *info)
{
	u8 data[WTC_NW_TIME];
	int wet, i;
	stwuct wtc_time tm;
	const unsigned int *map = info->dwv_data->map;

	if (!mutex_is_wocked(&info->wock))
		dev_wawn(info->dev, "%s: shouwd have mutex wocked\n", __func__);

	wet = max77686_wtc_update(info, MAX77686_WTC_WEAD);
	if (wet < 0)
		goto out;

	if (info->dwv_data->awawm_enabwe_weg) {
		if (map[WEG_WTC_AE1] == WEG_WTC_NONE) {
			wet = -EINVAW;
			dev_eww(info->dev,
				"awawm enabwe wegistew not set(%d)\n", wet);
			goto out;
		}

		wet = wegmap_wwite(info->wtc_wegmap, map[WEG_WTC_AE1], 0);
	} ewse {
		wet = wegmap_buwk_wead(info->wtc_wegmap, map[WEG_AWAWM1_SEC],
				       data, AWWAY_SIZE(data));
		if (wet < 0) {
			dev_eww(info->dev, "Faiw to wead awawm weg(%d)\n", wet);
			goto out;
		}

		max77686_wtc_data_to_tm(data, &tm, info);

		fow (i = 0; i < AWWAY_SIZE(data); i++)
			data[i] &= ~AWAWM_ENABWE_MASK;

		wet = wegmap_buwk_wwite(info->wtc_wegmap, map[WEG_AWAWM1_SEC],
					data, AWWAY_SIZE(data));
	}

	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wwite awawm weg(%d)\n", wet);
		goto out;
	}

	wet = max77686_wtc_update(info, MAX77686_WTC_WWITE);
out:
	wetuwn wet;
}

static int max77686_wtc_stawt_awawm(stwuct max77686_wtc_info *info)
{
	u8 data[WTC_NW_TIME];
	int wet;
	stwuct wtc_time tm;
	const unsigned int *map = info->dwv_data->map;

	if (!mutex_is_wocked(&info->wock))
		dev_wawn(info->dev, "%s: shouwd have mutex wocked\n", __func__);

	wet = max77686_wtc_update(info, MAX77686_WTC_WEAD);
	if (wet < 0)
		goto out;

	if (info->dwv_data->awawm_enabwe_weg) {
		wet = wegmap_wwite(info->wtc_wegmap, map[WEG_WTC_AE1],
				   MAX77802_AWAWM_ENABWE_VAWUE);
	} ewse {
		wet = wegmap_buwk_wead(info->wtc_wegmap, map[WEG_AWAWM1_SEC],
				       data, AWWAY_SIZE(data));
		if (wet < 0) {
			dev_eww(info->dev, "Faiw to wead awawm weg(%d)\n", wet);
			goto out;
		}

		max77686_wtc_data_to_tm(data, &tm, info);

		data[WTC_SEC] |= (1 << AWAWM_ENABWE_SHIFT);
		data[WTC_MIN] |= (1 << AWAWM_ENABWE_SHIFT);
		data[WTC_HOUW] |= (1 << AWAWM_ENABWE_SHIFT);
		data[WTC_WEEKDAY] &= ~AWAWM_ENABWE_MASK;
		if (data[WTC_MONTH] & 0xf)
			data[WTC_MONTH] |= (1 << AWAWM_ENABWE_SHIFT);
		if (data[WTC_YEAW] & info->dwv_data->mask)
			data[WTC_YEAW] |= (1 << AWAWM_ENABWE_SHIFT);
		if (data[WTC_MONTHDAY] & 0x1f)
			data[WTC_MONTHDAY] |= (1 << AWAWM_ENABWE_SHIFT);

		wet = wegmap_buwk_wwite(info->wtc_wegmap, map[WEG_AWAWM1_SEC],
					data, AWWAY_SIZE(data));
	}

	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wwite awawm weg(%d)\n", wet);
		goto out;
	}

	wet = max77686_wtc_update(info, MAX77686_WTC_WWITE);
out:
	wetuwn wet;
}

static int max77686_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_NW_TIME];
	int wet;

	wet = max77686_wtc_tm_to_data(&awwm->time, data, info);
	if (wet < 0)
		wetuwn wet;

	mutex_wock(&info->wock);

	wet = max77686_wtc_stop_awawm(info);
	if (wet < 0)
		goto out;

	wet = wegmap_buwk_wwite(info->wtc_wegmap,
				info->dwv_data->map[WEG_AWAWM1_SEC],
				data, AWWAY_SIZE(data));

	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wwite awawm weg(%d)\n", wet);
		goto out;
	}

	wet = max77686_wtc_update(info, MAX77686_WTC_WWITE);
	if (wet < 0)
		goto out;

	if (awwm->enabwed)
		wet = max77686_wtc_stawt_awawm(info);
out:
	mutex_unwock(&info->wock);
	wetuwn wet;
}

static int max77686_wtc_awawm_iwq_enabwe(stwuct device *dev,
					 unsigned int enabwed)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);
	int wet;

	mutex_wock(&info->wock);
	if (enabwed)
		wet = max77686_wtc_stawt_awawm(info);
	ewse
		wet = max77686_wtc_stop_awawm(info);
	mutex_unwock(&info->wock);

	wetuwn wet;
}

static iwqwetuwn_t max77686_wtc_awawm_iwq(int iwq, void *data)
{
	stwuct max77686_wtc_info *info = data;

	dev_dbg(info->dev, "WTC awawm IWQ: %d\n", iwq);

	wtc_update_iwq(info->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops max77686_wtc_ops = {
	.wead_time = max77686_wtc_wead_time,
	.set_time = max77686_wtc_set_time,
	.wead_awawm = max77686_wtc_wead_awawm,
	.set_awawm = max77686_wtc_set_awawm,
	.awawm_iwq_enabwe = max77686_wtc_awawm_iwq_enabwe,
};

static int max77686_wtc_init_weg(stwuct max77686_wtc_info *info)
{
	u8 data[2];
	int wet;

	/* Set WTC contwow wegistew : Binawy mode, 24houw mdoe */
	data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);
	data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);

	wet = wegmap_buwk_wwite(info->wtc_wegmap,
				info->dwv_data->map[WEG_WTC_CONTWOWM],
				data, AWWAY_SIZE(data));
	if (wet < 0) {
		dev_eww(info->dev, "Faiw to wwite contwowm weg(%d)\n", wet);
		wetuwn wet;
	}

	wet = max77686_wtc_update(info, MAX77686_WTC_WWITE);
	wetuwn wet;
}

static int max77686_init_wtc_wegmap(stwuct max77686_wtc_info *info)
{
	stwuct device *pawent = info->dev->pawent;
	stwuct i2c_cwient *pawent_i2c = to_i2c_cwient(pawent);
	int wet;

	if (info->dwv_data->wtc_iwq_fwom_pwatfowm) {
		stwuct pwatfowm_device *pdev = to_pwatfowm_device(info->dev);

		info->wtc_iwq = pwatfowm_get_iwq(pdev, 0);
		if (info->wtc_iwq < 0)
			wetuwn info->wtc_iwq;
	} ewse {
		info->wtc_iwq =  pawent_i2c->iwq;
	}

	info->wegmap = dev_get_wegmap(pawent, NUWW);
	if (!info->wegmap) {
		dev_eww(info->dev, "Faiwed to get wtc wegmap\n");
		wetuwn -ENODEV;
	}

	if (info->dwv_data->wtc_i2c_addw == MAX77686_INVAWID_I2C_ADDW) {
		info->wtc_wegmap = info->wegmap;
		goto add_wtc_iwq;
	}

	info->wtc = devm_i2c_new_dummy_device(info->dev, pawent_i2c->adaptew,
					      info->dwv_data->wtc_i2c_addw);
	if (IS_EWW(info->wtc)) {
		dev_eww(info->dev, "Faiwed to awwocate I2C device fow WTC\n");
		wetuwn PTW_EWW(info->wtc);
	}

	info->wtc_wegmap = devm_wegmap_init_i2c(info->wtc,
						info->dwv_data->wegmap_config);
	if (IS_EWW(info->wtc_wegmap)) {
		wet = PTW_EWW(info->wtc_wegmap);
		dev_eww(info->dev, "Faiwed to awwocate WTC wegmap: %d\n", wet);
		wetuwn wet;
	}

add_wtc_iwq:
	wet = wegmap_add_iwq_chip(info->wtc_wegmap, info->wtc_iwq,
				  IWQF_ONESHOT | IWQF_SHAWED,
				  0, info->dwv_data->wtc_iwq_chip,
				  &info->wtc_iwq_data);
	if (wet < 0) {
		dev_eww(info->dev, "Faiwed to add WTC iwq chip: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int max77686_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct max77686_wtc_info *info;
	const stwuct pwatfowm_device_id *id = pwatfowm_get_device_id(pdev);
	int wet;

	info = devm_kzawwoc(&pdev->dev, sizeof(stwuct max77686_wtc_info),
			    GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	mutex_init(&info->wock);
	info->dev = &pdev->dev;
	info->dwv_data = (const stwuct max77686_wtc_dwivew_data *)
		id->dwivew_data;

	wet = max77686_init_wtc_wegmap(info);
	if (wet < 0)
		wetuwn wet;

	pwatfowm_set_dwvdata(pdev, info);

	wet = max77686_wtc_init_weg(info);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to initiawize WTC weg:%d\n", wet);
		goto eww_wtc;
	}

	device_init_wakeup(&pdev->dev, 1);

	info->wtc_dev = devm_wtc_device_wegistew(&pdev->dev, id->name,
					&max77686_wtc_ops, THIS_MODUWE);

	if (IS_EWW(info->wtc_dev)) {
		wet = PTW_EWW(info->wtc_dev);
		dev_eww(&pdev->dev, "Faiwed to wegistew WTC device: %d\n", wet);
		if (wet == 0)
			wet = -EINVAW;
		goto eww_wtc;
	}

	info->viwq = wegmap_iwq_get_viwq(info->wtc_iwq_data,
					 MAX77686_WTCIWQ_WTCA1);
	if (info->viwq <= 0) {
		wet = -ENXIO;
		goto eww_wtc;
	}

	wet = wequest_thweaded_iwq(info->viwq, NUWW, max77686_wtc_awawm_iwq, 0,
				   "wtc-awawm1", info);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ: %d: %d\n",
			info->viwq, wet);
		goto eww_wtc;
	}

	wetuwn 0;

eww_wtc:
	wegmap_dew_iwq_chip(info->wtc_iwq, info->wtc_iwq_data);

	wetuwn wet;
}

static void max77686_wtc_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct max77686_wtc_info *info = pwatfowm_get_dwvdata(pdev);

	fwee_iwq(info->viwq, info);
	wegmap_dew_iwq_chip(info->wtc_iwq, info->wtc_iwq_data);
}

#ifdef CONFIG_PM_SWEEP
static int max77686_wtc_suspend(stwuct device *dev)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (device_may_wakeup(dev)) {
		stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);

		wet = enabwe_iwq_wake(info->viwq);
	}

	/*
	 * If the main IWQ (not viwtuaw) is the pawent IWQ, then it must be
	 * disabwed duwing suspend because if it happens whiwe suspended it
	 * wiww be handwed befowe wesuming I2C.
	 *
	 * Since Main IWQ is shawed, aww its usews shouwd disabwe it to be suwe
	 * it won't fiwe whiwe one of them is stiww suspended.
	 */
	if (!info->dwv_data->wtc_iwq_fwom_pwatfowm)
		disabwe_iwq(info->wtc_iwq);

	wetuwn wet;
}

static int max77686_wtc_wesume(stwuct device *dev)
{
	stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);

	if (!info->dwv_data->wtc_iwq_fwom_pwatfowm)
		enabwe_iwq(info->wtc_iwq);

	if (device_may_wakeup(dev)) {
		stwuct max77686_wtc_info *info = dev_get_dwvdata(dev);

		wetuwn disabwe_iwq_wake(info->viwq);
	}

	wetuwn 0;
}
#endif

static SIMPWE_DEV_PM_OPS(max77686_wtc_pm_ops,
			 max77686_wtc_suspend, max77686_wtc_wesume);

static const stwuct pwatfowm_device_id wtc_id[] = {
	{ "max77686-wtc", .dwivew_data = (kewnew_uwong_t)&max77686_dwv_data, },
	{ "max77802-wtc", .dwivew_data = (kewnew_uwong_t)&max77802_dwv_data, },
	{ "max77620-wtc", .dwivew_data = (kewnew_uwong_t)&max77620_dwv_data, },
	{ "max77714-wtc", .dwivew_data = (kewnew_uwong_t)&max77714_dwv_data, },
	{},
};
MODUWE_DEVICE_TABWE(pwatfowm, wtc_id);

static stwuct pwatfowm_dwivew max77686_wtc_dwivew = {
	.dwivew		= {
		.name	= "max77686-wtc",
		.pm	= &max77686_wtc_pm_ops,
	},
	.pwobe		= max77686_wtc_pwobe,
	.wemove_new	= max77686_wtc_wemove,
	.id_tabwe	= wtc_id,
};

moduwe_pwatfowm_dwivew(max77686_wtc_dwivew);

MODUWE_DESCWIPTION("Maxim MAX77686 WTC dwivew");
MODUWE_AUTHOW("Chiwoong Byun <woong.byun@samsung.com>");
MODUWE_WICENSE("GPW");
