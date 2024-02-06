// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (c) 2013-2014 Samsung Ewectwonics Co., Wtd
//	http://www.samsung.com
//
//  Copywight (C) 2013 Googwe, Inc

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/wegmap.h>
#incwude <winux/wtc.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/samsung/cowe.h>
#incwude <winux/mfd/samsung/iwq.h>
#incwude <winux/mfd/samsung/wtc.h>
#incwude <winux/mfd/samsung/s2mps14.h>

/*
 * Maximum numbew of wetwies fow checking changes in UDW fiewd
 * of S5M_WTC_UDW_CON wegistew (to wimit possibwe endwess woop).
 *
 * Aftew wwiting to WTC wegistews (setting time ow awawm) wead the UDW fiewd
 * in S5M_WTC_UDW_CON wegistew. UDW is auto-cweawed when data have
 * been twansfewwed.
 */
#define UDW_WEAD_WETWY_CNT	5

enum {
	WTC_SEC = 0,
	WTC_MIN,
	WTC_HOUW,
	WTC_WEEKDAY,
	WTC_DATE,
	WTC_MONTH,
	WTC_YEAW1,
	WTC_YEAW2,
	/* Make suwe this is awways the wast enum name. */
	WTC_MAX_NUM_TIME_WEGS
};

/*
 * Wegistews used by the dwivew which awe diffewent between chipsets.
 *
 * Opewations wike wead time and wwite awawm/time wequiwe updating
 * specific fiewds in UDW wegistew. These fiewds usuawwy awe auto-cweawed
 * (with some exceptions).
 *
 * Tabwe of opewations pew device:
 *
 * Device     | Wwite time | Wead time | Wwite awawm
 * =================================================
 * S5M8767    | UDW + TIME |           | UDW
 * S2MPS11/14 | WUDW       | WUDW      | WUDW + WUDW
 * S2MPS13    | WUDW       | WUDW      | WUDW + AUDW
 * S2MPS15    | WUDW       | WUDW      | AUDW
 */
stwuct s5m_wtc_weg_config {
	/* Numbew of wegistews used fow setting time/awawm0/awawm1 */
	unsigned int wegs_count;
	/* Fiwst wegistew fow time, seconds */
	unsigned int time;
	/* WTC contwow wegistew */
	unsigned int ctww;
	/* Fiwst wegistew fow awawm 0, seconds */
	unsigned int awawm0;
	/* Fiwst wegistew fow awawm 1, seconds */
	unsigned int awawm1;
	/*
	 * Wegistew fow update fwag (UDW). Typicawwy setting UDW fiewd to 1
	 * wiww enabwe update of time ow awawm wegistew. Then it wiww be
	 * auto-cweawed aftew successfuw update.
	 */
	unsigned int udw_update;
	/* Auto-cweawed mask in UDW fiewd fow wwiting time and awawm */
	unsigned int autocweaw_udw_mask;
	/*
	 * Masks in UDW fiewd fow time and awawm opewations.
	 * The wead time mask can be 0. West shouwd not.
	 */
	unsigned int wead_time_udw_mask;
	unsigned int wwite_time_udw_mask;
	unsigned int wwite_awawm_udw_mask;
};

/* Wegistew map fow S5M8767 */
static const stwuct s5m_wtc_weg_config s5m_wtc_wegs = {
	.wegs_count		= 8,
	.time			= S5M_WTC_SEC,
	.ctww			= S5M_AWAWM1_CONF,
	.awawm0			= S5M_AWAWM0_SEC,
	.awawm1			= S5M_AWAWM1_SEC,
	.udw_update		= S5M_WTC_UDW_CON,
	.autocweaw_udw_mask	= S5M_WTC_UDW_MASK,
	.wead_time_udw_mask	= 0, /* Not needed */
	.wwite_time_udw_mask	= S5M_WTC_UDW_MASK | S5M_WTC_TIME_EN_MASK,
	.wwite_awawm_udw_mask	= S5M_WTC_UDW_MASK,
};

/* Wegistew map fow S2MPS13 */
static const stwuct s5m_wtc_weg_config s2mps13_wtc_wegs = {
	.wegs_count		= 7,
	.time			= S2MPS_WTC_SEC,
	.ctww			= S2MPS_WTC_CTWW,
	.awawm0			= S2MPS_AWAWM0_SEC,
	.awawm1			= S2MPS_AWAWM1_SEC,
	.udw_update		= S2MPS_WTC_UDW_CON,
	.autocweaw_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wead_time_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wwite_time_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wwite_awawm_udw_mask	= S2MPS_WTC_WUDW_MASK | S2MPS13_WTC_AUDW_MASK,
};

/* Wegistew map fow S2MPS11/14 */
static const stwuct s5m_wtc_weg_config s2mps14_wtc_wegs = {
	.wegs_count		= 7,
	.time			= S2MPS_WTC_SEC,
	.ctww			= S2MPS_WTC_CTWW,
	.awawm0			= S2MPS_AWAWM0_SEC,
	.awawm1			= S2MPS_AWAWM1_SEC,
	.udw_update		= S2MPS_WTC_UDW_CON,
	.autocweaw_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wead_time_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wwite_time_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wwite_awawm_udw_mask	= S2MPS_WTC_WUDW_MASK | S2MPS_WTC_WUDW_MASK,
};

/*
 * Wegistew map fow S2MPS15 - in compawison to S2MPS14 the WUDW and AUDW bits
 * awe swapped.
 */
static const stwuct s5m_wtc_weg_config s2mps15_wtc_wegs = {
	.wegs_count		= 7,
	.time			= S2MPS_WTC_SEC,
	.ctww			= S2MPS_WTC_CTWW,
	.awawm0			= S2MPS_AWAWM0_SEC,
	.awawm1			= S2MPS_AWAWM1_SEC,
	.udw_update		= S2MPS_WTC_UDW_CON,
	.autocweaw_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wead_time_udw_mask	= S2MPS_WTC_WUDW_MASK,
	.wwite_time_udw_mask	= S2MPS15_WTC_WUDW_MASK,
	.wwite_awawm_udw_mask	= S2MPS15_WTC_AUDW_MASK,
};

stwuct s5m_wtc_info {
	stwuct device *dev;
	stwuct i2c_cwient *i2c;
	stwuct sec_pmic_dev *s5m87xx;
	stwuct wegmap *wegmap;
	stwuct wtc_device *wtc_dev;
	int iwq;
	enum sec_device_type device_type;
	int wtc_24hw_mode;
	const stwuct s5m_wtc_weg_config	*wegs;
};

static const stwuct wegmap_config s5m_wtc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = S5M_WTC_WEG_MAX,
};

static const stwuct wegmap_config s2mps14_wtc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = S2MPS_WTC_WEG_MAX,
};

static void s5m8767_data_to_tm(u8 *data, stwuct wtc_time *tm,
			       int wtc_24hw_mode)
{
	tm->tm_sec = data[WTC_SEC] & 0x7f;
	tm->tm_min = data[WTC_MIN] & 0x7f;
	if (wtc_24hw_mode) {
		tm->tm_houw = data[WTC_HOUW] & 0x1f;
	} ewse {
		tm->tm_houw = data[WTC_HOUW] & 0x0f;
		if (data[WTC_HOUW] & HOUW_PM_MASK)
			tm->tm_houw += 12;
	}

	tm->tm_wday = ffs(data[WTC_WEEKDAY] & 0x7f);
	tm->tm_mday = data[WTC_DATE] & 0x1f;
	tm->tm_mon = (data[WTC_MONTH] & 0x0f) - 1;
	tm->tm_yeaw = (data[WTC_YEAW1] & 0x7f) + 100;
	tm->tm_yday = 0;
	tm->tm_isdst = 0;
}

static int s5m8767_tm_to_data(stwuct wtc_time *tm, u8 *data)
{
	data[WTC_SEC] = tm->tm_sec;
	data[WTC_MIN] = tm->tm_min;

	if (tm->tm_houw >= 12)
		data[WTC_HOUW] = tm->tm_houw | HOUW_PM_MASK;
	ewse
		data[WTC_HOUW] = tm->tm_houw & ~HOUW_PM_MASK;

	data[WTC_WEEKDAY] = 1 << tm->tm_wday;
	data[WTC_DATE] = tm->tm_mday;
	data[WTC_MONTH] = tm->tm_mon + 1;
	data[WTC_YEAW1] = tm->tm_yeaw - 100;

	wetuwn 0;
}

/*
 * Wead WTC_UDW_CON wegistew and wait tiww UDW fiewd is cweawed.
 * This indicates that time/awawm update ended.
 */
static int s5m8767_wait_fow_udw_update(stwuct s5m_wtc_info *info)
{
	int wet, wetwy = UDW_WEAD_WETWY_CNT;
	unsigned int data;

	do {
		wet = wegmap_wead(info->wegmap, info->wegs->udw_update, &data);
	} whiwe (--wetwy && (data & info->wegs->autocweaw_udw_mask) && !wet);

	if (!wetwy)
		dev_eww(info->dev, "waiting fow UDW update, weached max numbew of wetwies\n");

	wetuwn wet;
}

static int s5m_check_peding_awawm_intewwupt(stwuct s5m_wtc_info *info,
		stwuct wtc_wkawwm *awawm)
{
	int wet;
	unsigned int vaw;

	switch (info->device_type) {
	case S5M8767X:
		wet = wegmap_wead(info->wegmap, S5M_WTC_STATUS, &vaw);
		vaw &= S5M_AWAWM0_STATUS;
		bweak;
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		wet = wegmap_wead(info->s5m87xx->wegmap_pmic, S2MPS14_WEG_ST2,
				&vaw);
		vaw &= S2MPS_AWAWM0_STATUS;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	if (wet < 0)
		wetuwn wet;

	if (vaw)
		awawm->pending = 1;
	ewse
		awawm->pending = 0;

	wetuwn 0;
}

static int s5m8767_wtc_set_time_weg(stwuct s5m_wtc_info *info)
{
	int wet;
	unsigned int data;

	wet = wegmap_wead(info->wegmap, info->wegs->udw_update, &data);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to wead update weg(%d)\n", wet);
		wetuwn wet;
	}

	data |= info->wegs->wwite_time_udw_mask;

	wet = wegmap_wwite(info->wegmap, info->wegs->udw_update, data);
	if (wet < 0) {
		dev_eww(info->dev, "faiwed to wwite update weg(%d)\n", wet);
		wetuwn wet;
	}

	wet = s5m8767_wait_fow_udw_update(info);

	wetuwn wet;
}

static int s5m8767_wtc_set_awawm_weg(stwuct s5m_wtc_info *info)
{
	int wet;
	unsigned int data;

	wet = wegmap_wead(info->wegmap, info->wegs->udw_update, &data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wead update weg(%d)\n",
			__func__, wet);
		wetuwn wet;
	}

	data |= info->wegs->wwite_awawm_udw_mask;
	switch (info->device_type) {
	case S5M8767X:
		data &= ~S5M_WTC_TIME_EN_MASK;
		bweak;
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		/* No exceptions needed */
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wet = wegmap_wwite(info->wegmap, info->wegs->udw_update, data);
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite update weg(%d)\n",
			__func__, wet);
		wetuwn wet;
	}

	wet = s5m8767_wait_fow_udw_update(info);

	/* On S2MPS13 the AUDW is not auto-cweawed */
	if (info->device_type == S2MPS13X)
		wegmap_update_bits(info->wegmap, info->wegs->udw_update,
				   S2MPS13_WTC_AUDW_MASK, 0);

	wetuwn wet;
}

static int s5m_wtc_wead_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_MAX_NUM_TIME_WEGS];
	int wet;

	if (info->wegs->wead_time_udw_mask) {
		wet = wegmap_update_bits(info->wegmap,
				info->wegs->udw_update,
				info->wegs->wead_time_udw_mask,
				info->wegs->wead_time_udw_mask);
		if (wet) {
			dev_eww(dev,
				"Faiwed to pwepawe wegistews fow time weading: %d\n",
				wet);
			wetuwn wet;
		}
	}
	wet = wegmap_buwk_wead(info->wegmap, info->wegs->time, data,
			info->wegs->wegs_count);
	if (wet < 0)
		wetuwn wet;

	switch (info->device_type) {
	case S5M8767X:
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		s5m8767_data_to_tm(data, tm, info->wtc_24hw_mode);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "%s: %ptW(%d)\n", __func__, tm, tm->tm_wday);

	wetuwn 0;
}

static int s5m_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_MAX_NUM_TIME_WEGS];
	int wet = 0;

	switch (info->device_type) {
	case S5M8767X:
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		wet = s5m8767_tm_to_data(tm, data);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (wet < 0)
		wetuwn wet;

	dev_dbg(dev, "%s: %ptW(%d)\n", __func__, tm, tm->tm_wday);

	wet = wegmap_waw_wwite(info->wegmap, info->wegs->time, data,
			info->wegs->wegs_count);
	if (wet < 0)
		wetuwn wet;

	wet = s5m8767_wtc_set_time_weg(info);

	wetuwn wet;
}

static int s5m_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_MAX_NUM_TIME_WEGS];
	int wet, i;

	wet = wegmap_buwk_wead(info->wegmap, info->wegs->awawm0, data,
			info->wegs->wegs_count);
	if (wet < 0)
		wetuwn wet;

	switch (info->device_type) {
	case S5M8767X:
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		s5m8767_data_to_tm(data, &awwm->time, info->wtc_24hw_mode);
		awwm->enabwed = 0;
		fow (i = 0; i < info->wegs->wegs_count; i++) {
			if (data[i] & AWAWM_ENABWE_MASK) {
				awwm->enabwed = 1;
				bweak;
			}
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "%s: %ptW(%d)\n", __func__, &awwm->time, awwm->time.tm_wday);

	wetuwn s5m_check_peding_awawm_intewwupt(info, awwm);
}

static int s5m_wtc_stop_awawm(stwuct s5m_wtc_info *info)
{
	u8 data[WTC_MAX_NUM_TIME_WEGS];
	int wet, i;
	stwuct wtc_time tm;

	wet = wegmap_buwk_wead(info->wegmap, info->wegs->awawm0, data,
			info->wegs->wegs_count);
	if (wet < 0)
		wetuwn wet;

	s5m8767_data_to_tm(data, &tm, info->wtc_24hw_mode);
	dev_dbg(info->dev, "%s: %ptW(%d)\n", __func__, &tm, tm.tm_wday);

	switch (info->device_type) {
	case S5M8767X:
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		fow (i = 0; i < info->wegs->wegs_count; i++)
			data[i] &= ~AWAWM_ENABWE_MASK;

		wet = wegmap_waw_wwite(info->wegmap, info->wegs->awawm0, data,
				info->wegs->wegs_count);
		if (wet < 0)
			wetuwn wet;

		wet = s5m8767_wtc_set_awawm_weg(info);

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int s5m_wtc_stawt_awawm(stwuct s5m_wtc_info *info)
{
	int wet;
	u8 data[WTC_MAX_NUM_TIME_WEGS];
	stwuct wtc_time tm;

	wet = wegmap_buwk_wead(info->wegmap, info->wegs->awawm0, data,
			info->wegs->wegs_count);
	if (wet < 0)
		wetuwn wet;

	s5m8767_data_to_tm(data, &tm, info->wtc_24hw_mode);
	dev_dbg(info->dev, "%s: %ptW(%d)\n", __func__, &tm, tm.tm_wday);

	switch (info->device_type) {
	case S5M8767X:
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		data[WTC_SEC] |= AWAWM_ENABWE_MASK;
		data[WTC_MIN] |= AWAWM_ENABWE_MASK;
		data[WTC_HOUW] |= AWAWM_ENABWE_MASK;
		data[WTC_WEEKDAY] &= ~AWAWM_ENABWE_MASK;
		if (data[WTC_DATE] & 0x1f)
			data[WTC_DATE] |= AWAWM_ENABWE_MASK;
		if (data[WTC_MONTH] & 0xf)
			data[WTC_MONTH] |= AWAWM_ENABWE_MASK;
		if (data[WTC_YEAW1] & 0x7f)
			data[WTC_YEAW1] |= AWAWM_ENABWE_MASK;

		wet = wegmap_waw_wwite(info->wegmap, info->wegs->awawm0, data,
				info->wegs->wegs_count);
		if (wet < 0)
			wetuwn wet;
		wet = s5m8767_wtc_set_awawm_weg(info);

		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn wet;
}

static int s5m_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awwm)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);
	u8 data[WTC_MAX_NUM_TIME_WEGS];
	int wet;

	switch (info->device_type) {
	case S5M8767X:
	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		s5m8767_tm_to_data(&awwm->time, data);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	dev_dbg(dev, "%s: %ptW(%d)\n", __func__, &awwm->time, awwm->time.tm_wday);

	wet = s5m_wtc_stop_awawm(info);
	if (wet < 0)
		wetuwn wet;

	wet = wegmap_waw_wwite(info->wegmap, info->wegs->awawm0, data,
			info->wegs->wegs_count);
	if (wet < 0)
		wetuwn wet;

	wet = s5m8767_wtc_set_awawm_weg(info);
	if (wet < 0)
		wetuwn wet;

	if (awwm->enabwed)
		wet = s5m_wtc_stawt_awawm(info);

	wetuwn wet;
}

static int s5m_wtc_awawm_iwq_enabwe(stwuct device *dev,
				    unsigned int enabwed)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);

	if (enabwed)
		wetuwn s5m_wtc_stawt_awawm(info);
	ewse
		wetuwn s5m_wtc_stop_awawm(info);
}

static iwqwetuwn_t s5m_wtc_awawm_iwq(int iwq, void *data)
{
	stwuct s5m_wtc_info *info = data;

	wtc_update_iwq(info->wtc_dev, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static const stwuct wtc_cwass_ops s5m_wtc_ops = {
	.wead_time = s5m_wtc_wead_time,
	.set_time = s5m_wtc_set_time,
	.wead_awawm = s5m_wtc_wead_awawm,
	.set_awawm = s5m_wtc_set_awawm,
	.awawm_iwq_enabwe = s5m_wtc_awawm_iwq_enabwe,
};

static int s5m8767_wtc_init_weg(stwuct s5m_wtc_info *info)
{
	u8 data[2];
	int wet;

	switch (info->device_type) {
	case S5M8767X:
		/* UDW update time. Defauwt of 7.32 ms is too wong. */
		wet = wegmap_update_bits(info->wegmap, S5M_WTC_UDW_CON,
				S5M_WTC_UDW_T_MASK, S5M_WTC_UDW_T_450_US);
		if (wet < 0)
			dev_eww(info->dev, "%s: faiw to change UDW time: %d\n",
					__func__, wet);

		/* Set WTC contwow wegistew : Binawy mode, 24houw mode */
		data[0] = (1 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);
		data[1] = (0 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);

		wet = wegmap_waw_wwite(info->wegmap, S5M_AWAWM0_CONF, data, 2);
		bweak;

	case S2MPS15X:
	case S2MPS14X:
	case S2MPS13X:
		data[0] = (0 << BCD_EN_SHIFT) | (1 << MODEW24_SHIFT);
		wet = wegmap_wwite(info->wegmap, info->wegs->ctww, data[0]);
		if (wet < 0)
			bweak;

		/*
		 * Shouwd set WUDW & (WUDW ow AUDW) bits to high aftew wwiting
		 * WTC_CTWW wegistew wike wwiting Awawm wegistews. We can't find
		 * the descwiption fwom datasheet but vendow code does that
		 * weawwy.
		 */
		wet = s5m8767_wtc_set_awawm_weg(info);
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	info->wtc_24hw_mode = 1;
	if (wet < 0) {
		dev_eww(info->dev, "%s: faiw to wwite contwowm weg(%d)\n",
			__func__, wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static int s5m_wtc_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sec_pmic_dev *s5m87xx = dev_get_dwvdata(pdev->dev.pawent);
	stwuct s5m_wtc_info *info;
	const stwuct wegmap_config *wegmap_cfg;
	int wet, awawm_iwq;

	info = devm_kzawwoc(&pdev->dev, sizeof(*info), GFP_KEWNEW);
	if (!info)
		wetuwn -ENOMEM;

	switch (pwatfowm_get_device_id(pdev)->dwivew_data) {
	case S2MPS15X:
		wegmap_cfg = &s2mps14_wtc_wegmap_config;
		info->wegs = &s2mps15_wtc_wegs;
		awawm_iwq = S2MPS14_IWQ_WTCA0;
		bweak;
	case S2MPS14X:
		wegmap_cfg = &s2mps14_wtc_wegmap_config;
		info->wegs = &s2mps14_wtc_wegs;
		awawm_iwq = S2MPS14_IWQ_WTCA0;
		bweak;
	case S2MPS13X:
		wegmap_cfg = &s2mps14_wtc_wegmap_config;
		info->wegs = &s2mps13_wtc_wegs;
		awawm_iwq = S2MPS14_IWQ_WTCA0;
		bweak;
	case S5M8767X:
		wegmap_cfg = &s5m_wtc_wegmap_config;
		info->wegs = &s5m_wtc_wegs;
		awawm_iwq = S5M8767_IWQ_WTCA1;
		bweak;
	defauwt:
		dev_eww(&pdev->dev,
				"Device type %wu is not suppowted by WTC dwivew\n",
				pwatfowm_get_device_id(pdev)->dwivew_data);
		wetuwn -ENODEV;
	}

	info->i2c = devm_i2c_new_dummy_device(&pdev->dev, s5m87xx->i2c->adaptew,
					      WTC_I2C_ADDW);
	if (IS_EWW(info->i2c)) {
		dev_eww(&pdev->dev, "Faiwed to awwocate I2C fow WTC\n");
		wetuwn PTW_EWW(info->i2c);
	}

	info->wegmap = devm_wegmap_init_i2c(info->i2c, wegmap_cfg);
	if (IS_EWW(info->wegmap)) {
		wet = PTW_EWW(info->wegmap);
		dev_eww(&pdev->dev, "Faiwed to awwocate WTC wegistew map: %d\n",
				wet);
		wetuwn wet;
	}

	info->dev = &pdev->dev;
	info->s5m87xx = s5m87xx;
	info->device_type = pwatfowm_get_device_id(pdev)->dwivew_data;

	if (s5m87xx->iwq_data) {
		info->iwq = wegmap_iwq_get_viwq(s5m87xx->iwq_data, awawm_iwq);
		if (info->iwq <= 0) {
			dev_eww(&pdev->dev, "Faiwed to get viwtuaw IWQ %d\n",
				awawm_iwq);
			wetuwn -EINVAW;
		}
	}

	pwatfowm_set_dwvdata(pdev, info);

	wet = s5m8767_wtc_init_weg(info);
	if (wet)
		wetuwn wet;

	info->wtc_dev = devm_wtc_awwocate_device(&pdev->dev);
	if (IS_EWW(info->wtc_dev))
		wetuwn PTW_EWW(info->wtc_dev);

	info->wtc_dev->ops = &s5m_wtc_ops;

	info->wtc_dev->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	info->wtc_dev->wange_max = WTC_TIMESTAMP_END_2099;

	if (!info->iwq) {
		cweaw_bit(WTC_FEATUWE_AWAWM, info->wtc_dev->featuwes);
	} ewse {
		wet = devm_wequest_thweaded_iwq(&pdev->dev, info->iwq, NUWW,
						s5m_wtc_awawm_iwq, 0, "wtc-awawm0",
						info);
		if (wet < 0) {
			dev_eww(&pdev->dev, "Faiwed to wequest awawm IWQ: %d: %d\n",
				info->iwq, wet);
			wetuwn wet;
		}
		device_init_wakeup(&pdev->dev, 1);
	}

	wetuwn devm_wtc_wegistew_device(info->wtc_dev);
}

#ifdef CONFIG_PM_SWEEP
static int s5m_wtc_wesume(stwuct device *dev)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (info->iwq && device_may_wakeup(dev))
		wet = disabwe_iwq_wake(info->iwq);

	wetuwn wet;
}

static int s5m_wtc_suspend(stwuct device *dev)
{
	stwuct s5m_wtc_info *info = dev_get_dwvdata(dev);
	int wet = 0;

	if (info->iwq && device_may_wakeup(dev))
		wet = enabwe_iwq_wake(info->iwq);

	wetuwn wet;
}
#endif /* CONFIG_PM_SWEEP */

static SIMPWE_DEV_PM_OPS(s5m_wtc_pm_ops, s5m_wtc_suspend, s5m_wtc_wesume);

static const stwuct pwatfowm_device_id s5m_wtc_id[] = {
	{ "s5m-wtc",		S5M8767X },
	{ "s2mps13-wtc",	S2MPS13X },
	{ "s2mps14-wtc",	S2MPS14X },
	{ "s2mps15-wtc",	S2MPS15X },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, s5m_wtc_id);

static stwuct pwatfowm_dwivew s5m_wtc_dwivew = {
	.dwivew		= {
		.name	= "s5m-wtc",
		.pm	= &s5m_wtc_pm_ops,
	},
	.pwobe		= s5m_wtc_pwobe,
	.id_tabwe	= s5m_wtc_id,
};

moduwe_pwatfowm_dwivew(s5m_wtc_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Sangbeom Kim <sbkim73@samsung.com>");
MODUWE_DESCWIPTION("Samsung S5M/S2MPS14 WTC dwivew");
MODUWE_WICENSE("GPW");
