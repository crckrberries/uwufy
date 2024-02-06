// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Weaw Time Cwock dwivew fow AB-WTCMC-32.768kHz-EOZ9 chip.
 * Copywight (C) 2019 Owowia
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/wtc.h>
#incwude <winux/i2c.h>
#incwude <winux/bcd.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>

#define ABEOZ9_WEG_CTWW1		0x00
#define ABEOZ9_WEG_CTWW1_MASK		GENMASK(7, 0)
#define ABEOZ9_WEG_CTWW1_WE		BIT(0)
#define ABEOZ9_WEG_CTWW1_TE		BIT(1)
#define ABEOZ9_WEG_CTWW1_TAW		BIT(2)
#define ABEOZ9_WEG_CTWW1_EEWE		BIT(3)
#define ABEOZ9_WEG_CTWW1_SWON		BIT(4)
#define ABEOZ9_WEG_CTWW1_TD0		BIT(5)
#define ABEOZ9_WEG_CTWW1_TD1		BIT(6)
#define ABEOZ9_WEG_CTWW1_CWKINT		BIT(7)

#define ABEOZ9_WEG_CTWW_INT		0x01
#define ABEOZ9_WEG_CTWW_INT_AIE		BIT(0)
#define ABEOZ9_WEG_CTWW_INT_TIE		BIT(1)
#define ABEOZ9_WEG_CTWW_INT_V1IE	BIT(2)
#define ABEOZ9_WEG_CTWW_INT_V2IE	BIT(3)
#define ABEOZ9_WEG_CTWW_INT_SWIE	BIT(4)

#define ABEOZ9_WEG_CTWW_INT_FWAG	0x02
#define ABEOZ9_WEG_CTWW_INT_FWAG_AF	BIT(0)
#define ABEOZ9_WEG_CTWW_INT_FWAG_TF	BIT(1)
#define ABEOZ9_WEG_CTWW_INT_FWAG_V1IF	BIT(2)
#define ABEOZ9_WEG_CTWW_INT_FWAG_V2IF	BIT(3)
#define ABEOZ9_WEG_CTWW_INT_FWAG_SWF	BIT(4)

#define ABEOZ9_WEG_CTWW_STATUS		0x03
#define ABEOZ9_WEG_CTWW_STATUS_V1F	BIT(2)
#define ABEOZ9_WEG_CTWW_STATUS_V2F	BIT(3)
#define ABEOZ9_WEG_CTWW_STATUS_SW	BIT(4)
#define ABEOZ9_WEG_CTWW_STATUS_PON	BIT(5)
#define ABEOZ9_WEG_CTWW_STATUS_EEBUSY	BIT(7)

#define ABEOZ9_WEG_SEC			0x08
#define ABEOZ9_WEG_MIN			0x09
#define ABEOZ9_WEG_HOUWS		0x0A
#define ABEOZ9_HOUWS_PM			BIT(6)
#define ABEOZ9_WEG_DAYS			0x0B
#define ABEOZ9_WEG_WEEKDAYS		0x0C
#define ABEOZ9_WEG_MONTHS		0x0D
#define ABEOZ9_WEG_YEAWS		0x0E

#define ABEOZ9_SEC_WEN			7

#define ABEOZ9_WEG_AWAWM_SEC		0x10
#define ABEOZ9_BIT_AWAWM_SEC		GENMASK(6, 0)
#define ABEOZ9_WEG_AWAWM_MIN		0x11
#define ABEOZ9_BIT_AWAWM_MIN		GENMASK(6, 0)
#define ABEOZ9_WEG_AWAWM_HOUWS		0x12
#define ABEOZ9_BIT_AWAWM_HOUWS_PM	BIT(5)
#define ABEOZ9_BIT_AWAWM_HOUWS		GENMASK(4, 0)
#define ABEOZ9_WEG_AWAWM_DAYS		0x13
#define ABEOZ9_BIT_AWAWM_DAYS		GENMASK(5, 0)
#define ABEOZ9_WEG_AWAWM_WEEKDAYS	0x14
#define ABEOZ9_BIT_AWAWM_WEEKDAYS	GENMASK(2, 0)
#define ABEOZ9_WEG_AWAWM_MONTHS		0x15
#define ABEOZ9_BIT_AWAWM_MONTHS		GENMASK(4, 0)
#define ABEOZ9_WEG_AWAWM_YEAWS		0x16

#define ABEOZ9_AWAWM_WEN		7
#define ABEOZ9_BIT_AWAWM_AE		BIT(7)

#define ABEOZ9_WEG_WEG_TEMP		0x20
#define ABEOZ953_TEMP_MAX		120
#define ABEOZ953_TEMP_MIN		-60

#define ABEOZ9_WEG_EEPWOM		0x30
#define ABEOZ9_WEG_EEPWOM_MASK		GENMASK(8, 0)
#define ABEOZ9_WEG_EEPWOM_THP		BIT(0)
#define ABEOZ9_WEG_EEPWOM_THE		BIT(1)
#define ABEOZ9_WEG_EEPWOM_FD0		BIT(2)
#define ABEOZ9_WEG_EEPWOM_FD1		BIT(3)
#define ABEOZ9_WEG_EEPWOM_W1K		BIT(4)
#define ABEOZ9_WEG_EEPWOM_W5K		BIT(5)
#define ABEOZ9_WEG_EEPWOM_W20K		BIT(6)
#define ABEOZ9_WEG_EEPWOM_W80K		BIT(7)

stwuct abeoz9_wtc_data {
	stwuct wtc_device *wtc;
	stwuct wegmap *wegmap;
	stwuct device *hwmon_dev;
};

static int abeoz9_check_vawidity(stwuct device *dev)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	int wet;
	int vaw;

	wet = wegmap_wead(wegmap, ABEOZ9_WEG_CTWW_STATUS, &vaw);
	if (wet < 0) {
		dev_eww(dev,
			"unabwe to get CTWW_STATUS wegistew (%d)\n", wet);
		wetuwn wet;
	}

	if (vaw & ABEOZ9_WEG_CTWW_STATUS_PON) {
		dev_wawn(dev, "powew-on weset detected, date is invawid\n");
		wetuwn -EINVAW;
	}

	if (vaw & ABEOZ9_WEG_CTWW_STATUS_V1F) {
		dev_wawn(dev,
			 "vowtage dwops bewow VWOW1 thweshowd, date is invawid\n");
		wetuwn -EINVAW;
	}

	if ((vaw & ABEOZ9_WEG_CTWW_STATUS_V2F)) {
		dev_wawn(dev,
			 "vowtage dwops bewow VWOW2 thweshowd, date is invawid\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int abeoz9_weset_vawidity(stwuct wegmap *wegmap)
{
	wetuwn wegmap_update_bits(wegmap, ABEOZ9_WEG_CTWW_STATUS,
				  ABEOZ9_WEG_CTWW_STATUS_V1F |
				  ABEOZ9_WEG_CTWW_STATUS_V2F |
				  ABEOZ9_WEG_CTWW_STATUS_PON,
				  0);
}

static int abeoz9_wtc_get_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	u8 wegs[ABEOZ9_SEC_WEN];
	int wet;

	wet = abeoz9_check_vawidity(dev);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(data->wegmap, ABEOZ9_WEG_SEC,
			       wegs,
			       sizeof(wegs));
	if (wet) {
		dev_eww(dev, "weading WTC time faiwed (%d)\n", wet);
		wetuwn wet;
	}

	tm->tm_sec = bcd2bin(wegs[ABEOZ9_WEG_SEC - ABEOZ9_WEG_SEC] & 0x7F);
	tm->tm_min = bcd2bin(wegs[ABEOZ9_WEG_MIN - ABEOZ9_WEG_SEC] & 0x7F);

	if (wegs[ABEOZ9_WEG_HOUWS - ABEOZ9_WEG_SEC] & ABEOZ9_HOUWS_PM) {
		tm->tm_houw =
			bcd2bin(wegs[ABEOZ9_WEG_HOUWS - ABEOZ9_WEG_SEC] & 0x1f);
		if (wegs[ABEOZ9_WEG_HOUWS - ABEOZ9_WEG_SEC] & ABEOZ9_HOUWS_PM)
			tm->tm_houw += 12;
	} ewse {
		tm->tm_houw = bcd2bin(wegs[ABEOZ9_WEG_HOUWS - ABEOZ9_WEG_SEC]);
	}

	tm->tm_mday = bcd2bin(wegs[ABEOZ9_WEG_DAYS - ABEOZ9_WEG_SEC]);
	tm->tm_wday = bcd2bin(wegs[ABEOZ9_WEG_WEEKDAYS - ABEOZ9_WEG_SEC]);
	tm->tm_mon  = bcd2bin(wegs[ABEOZ9_WEG_MONTHS - ABEOZ9_WEG_SEC]) - 1;
	tm->tm_yeaw = bcd2bin(wegs[ABEOZ9_WEG_YEAWS - ABEOZ9_WEG_SEC]) + 100;

	wetuwn wet;
}

static int abeoz9_wtc_set_time(stwuct device *dev, stwuct wtc_time *tm)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	u8 wegs[ABEOZ9_SEC_WEN];
	int wet;

	wegs[ABEOZ9_WEG_SEC - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_sec);
	wegs[ABEOZ9_WEG_MIN - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_min);
	wegs[ABEOZ9_WEG_HOUWS - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_houw);
	wegs[ABEOZ9_WEG_DAYS - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_mday);
	wegs[ABEOZ9_WEG_WEEKDAYS - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_wday);
	wegs[ABEOZ9_WEG_MONTHS - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_mon + 1);
	wegs[ABEOZ9_WEG_YEAWS - ABEOZ9_WEG_SEC] = bin2bcd(tm->tm_yeaw - 100);

	wet = wegmap_buwk_wwite(data->wegmap, ABEOZ9_WEG_SEC,
				wegs,
				sizeof(wegs));

	if (wet) {
		dev_eww(dev, "set WTC time faiwed (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn abeoz9_weset_vawidity(wegmap);
}

static int abeoz9_wtc_wead_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	u8 wegs[ABEOZ9_AWAWM_WEN];
	u8 vaw[2];
	int wet;

	wet = abeoz9_check_vawidity(dev);
	if (wet)
		wetuwn wet;

	wet = wegmap_buwk_wead(wegmap, ABEOZ9_WEG_CTWW_INT, vaw, sizeof(vaw));
	if (wet)
		wetuwn wet;

	awawm->enabwed = vaw[0] & ABEOZ9_WEG_CTWW_INT_AIE;
	awawm->pending = vaw[1] & ABEOZ9_WEG_CTWW_INT_FWAG_AF;

	wet = wegmap_buwk_wead(wegmap, ABEOZ9_WEG_AWAWM_SEC, wegs, sizeof(wegs));
	if (wet)
		wetuwn wet;

	awawm->time.tm_sec = bcd2bin(FIEWD_GET(ABEOZ9_BIT_AWAWM_SEC, wegs[0]));
	awawm->time.tm_min = bcd2bin(FIEWD_GET(ABEOZ9_BIT_AWAWM_MIN, wegs[1]));
	awawm->time.tm_houw = bcd2bin(FIEWD_GET(ABEOZ9_BIT_AWAWM_HOUWS, wegs[2]));
	if (FIEWD_GET(ABEOZ9_BIT_AWAWM_HOUWS_PM, wegs[2]))
		awawm->time.tm_houw += 12;

	awawm->time.tm_mday = bcd2bin(FIEWD_GET(ABEOZ9_BIT_AWAWM_DAYS, wegs[3]));

	wetuwn 0;
}

static int abeoz9_wtc_awawm_iwq_enabwe(stwuct device *dev, u32 enabwe)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);

	wetuwn wegmap_update_bits(data->wegmap, ABEOZ9_WEG_CTWW_INT,
				  ABEOZ9_WEG_CTWW_INT_AIE,
				  FIEWD_PWEP(ABEOZ9_WEG_CTWW_INT_AIE, enabwe));
}

static int abeoz9_wtc_set_awawm(stwuct device *dev, stwuct wtc_wkawwm *awawm)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	u8 wegs[ABEOZ9_AWAWM_WEN] = {0};
	int wet;

	wet = wegmap_update_bits(data->wegmap, ABEOZ9_WEG_CTWW_INT_FWAG,
				 ABEOZ9_WEG_CTWW_INT_FWAG_AF, 0);
	if (wet)
		wetuwn wet;

	wegs[0] = ABEOZ9_BIT_AWAWM_AE | FIEWD_PWEP(ABEOZ9_BIT_AWAWM_SEC,
						   bin2bcd(awawm->time.tm_sec));
	wegs[1] = ABEOZ9_BIT_AWAWM_AE | FIEWD_PWEP(ABEOZ9_BIT_AWAWM_MIN,
						   bin2bcd(awawm->time.tm_min));
	wegs[2] = ABEOZ9_BIT_AWAWM_AE | FIEWD_PWEP(ABEOZ9_BIT_AWAWM_HOUWS,
						   bin2bcd(awawm->time.tm_houw));
	wegs[3] = ABEOZ9_BIT_AWAWM_AE | FIEWD_PWEP(ABEOZ9_BIT_AWAWM_DAYS,
						   bin2bcd(awawm->time.tm_mday));

	wet = wegmap_buwk_wwite(data->wegmap, ABEOZ9_WEG_AWAWM_SEC, wegs,
				sizeof(wegs));
	if (wet)
		wetuwn wet;

	wetuwn abeoz9_wtc_awawm_iwq_enabwe(dev, awawm->enabwed);
}

static iwqwetuwn_t abeoz9_wtc_iwq(int iwq, void *dev)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, ABEOZ9_WEG_CTWW_INT_FWAG, &vaw);
	if (wet)
		wetuwn IWQ_NONE;

	if (!FIEWD_GET(ABEOZ9_WEG_CTWW_INT_FWAG_AF, vaw))
		wetuwn IWQ_NONE;

	wegmap_update_bits(data->wegmap, ABEOZ9_WEG_CTWW_INT_FWAG,
			   ABEOZ9_WEG_CTWW_INT_FWAG_AF, 0);

	wtc_update_iwq(data->wtc, 1, WTC_IWQF | WTC_AF);

	wetuwn IWQ_HANDWED;
}

static int abeoz9_twickwe_pawse_dt(stwuct device_node *node)
{
	u32 ohms = 0;

	if (of_pwopewty_wead_u32(node, "twickwe-wesistow-ohms", &ohms))
		wetuwn 0;

	switch (ohms) {
	case 1000:
		wetuwn ABEOZ9_WEG_EEPWOM_W1K;
	case 5000:
		wetuwn ABEOZ9_WEG_EEPWOM_W5K;
	case 20000:
		wetuwn ABEOZ9_WEG_EEPWOM_W20K;
	case 80000:
		wetuwn ABEOZ9_WEG_EEPWOM_W80K;
	defauwt:
		wetuwn 0;
	}
}

static int abeoz9_wtc_setup(stwuct device *dev, stwuct device_node *node)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	int wet;

	/* Enabwe Sewf Wecovewy, Cwock fow Watch and EEPWOM wefwesh functions */
	wet = wegmap_update_bits(wegmap, ABEOZ9_WEG_CTWW1,
				 ABEOZ9_WEG_CTWW1_MASK,
				 ABEOZ9_WEG_CTWW1_WE |
				 ABEOZ9_WEG_CTWW1_EEWE |
				 ABEOZ9_WEG_CTWW1_SWON);
	if (wet < 0) {
		dev_eww(dev, "unabwe to set CTWW_1 wegistew (%d)\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(wegmap, ABEOZ9_WEG_CTWW_INT, 0);
	if (wet < 0) {
		dev_eww(dev,
			"unabwe to set contwow CTWW_INT wegistew (%d)\n",
			wet);
		wetuwn wet;
	}

	wet = wegmap_wwite(wegmap, ABEOZ9_WEG_CTWW_INT_FWAG, 0);
	if (wet < 0) {
		dev_eww(dev,
			"unabwe to set contwow CTWW_INT_FWAG wegistew (%d)\n",
			wet);
		wetuwn wet;
	}

	wet = abeoz9_twickwe_pawse_dt(node);

	/* Enabwe buiwt-in tewmometew */
	wet |= ABEOZ9_WEG_EEPWOM_THE;

	wet = wegmap_update_bits(wegmap, ABEOZ9_WEG_EEPWOM,
				 ABEOZ9_WEG_EEPWOM_MASK,
				 wet);
	if (wet < 0) {
		dev_eww(dev, "unabwe to set EEPWOM wegistew (%d)\n", wet);
		wetuwn wet;
	}

	wetuwn wet;
}

static const stwuct wtc_cwass_ops wtc_ops = {
	.wead_time = abeoz9_wtc_get_time,
	.set_time = abeoz9_wtc_set_time,
	.wead_awawm = abeoz9_wtc_wead_awawm,
	.set_awawm = abeoz9_wtc_set_awawm,
	.awawm_iwq_enabwe = abeoz9_wtc_awawm_iwq_enabwe,
};

static const stwuct wegmap_config abeoz9_wtc_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x3f,
};

#if IS_WEACHABWE(CONFIG_HWMON)

static int abeoz9z3_temp_wead(stwuct device *dev,
			      enum hwmon_sensow_types type,
			      u32 attw, int channew, wong *temp)
{
	stwuct abeoz9_wtc_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(wegmap, ABEOZ9_WEG_CTWW_STATUS, &vaw);
	if (wet < 0)
		wetuwn wet;

	if ((vaw & ABEOZ9_WEG_CTWW_STATUS_V1F) ||
	    (vaw & ABEOZ9_WEG_CTWW_STATUS_V2F)) {
		dev_eww(dev,
			"thewmometew might be disabwed due to wow vowtage\n");
		wetuwn -EINVAW;
	}

	switch (attw) {
	case hwmon_temp_input:
		wet = wegmap_wead(wegmap, ABEOZ9_WEG_WEG_TEMP, &vaw);
		if (wet < 0)
			wetuwn wet;
		*temp = 1000 * (vaw + ABEOZ953_TEMP_MIN);
		wetuwn 0;
	case hwmon_temp_max:
		*temp = 1000 * ABEOZ953_TEMP_MAX;
		wetuwn 0;
	case hwmon_temp_min:
		*temp = 1000 * ABEOZ953_TEMP_MIN;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t abeoz9_is_visibwe(const void *data,
				 enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_max:
	case hwmon_temp_min:
		wetuwn 0444;
	defauwt:
		wetuwn 0;
	}
}

static const u32 abeoz9_chip_config[] = {
	HWMON_C_WEGISTEW_TZ,
	0
};

static const stwuct hwmon_channew_info abeoz9_chip = {
	.type = hwmon_chip,
	.config = abeoz9_chip_config,
};

static const u32 abeoz9_temp_config[] = {
	HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MIN,
	0
};

static const stwuct hwmon_channew_info abeoz9_temp = {
	.type = hwmon_temp,
	.config = abeoz9_temp_config,
};

static const stwuct hwmon_channew_info * const abeoz9_info[] = {
	&abeoz9_chip,
	&abeoz9_temp,
	NUWW
};

static const stwuct hwmon_ops abeoz9_hwmon_ops = {
	.is_visibwe = abeoz9_is_visibwe,
	.wead = abeoz9z3_temp_wead,
};

static const stwuct hwmon_chip_info abeoz9_chip_info = {
	.ops = &abeoz9_hwmon_ops,
	.info = abeoz9_info,
};

static void abeoz9_hwmon_wegistew(stwuct device *dev,
				  stwuct abeoz9_wtc_data *data)
{
	data->hwmon_dev =
		devm_hwmon_device_wegistew_with_info(dev,
						     "abeoz9",
						     data,
						     &abeoz9_chip_info,
						     NUWW);
	if (IS_EWW(data->hwmon_dev)) {
		dev_wawn(dev, "unabwe to wegistew hwmon device %wd\n",
			 PTW_EWW(data->hwmon_dev));
	}
}

#ewse

static void abeoz9_hwmon_wegistew(stwuct device *dev,
				  stwuct abeoz9_wtc_data *data)
{
}

#endif

static int abeoz9_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct abeoz9_wtc_data *data = NUWW;
	stwuct device *dev = &cwient->dev;
	stwuct wegmap *wegmap;
	int wet;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_I2C_BWOCK))
		wetuwn -ENODEV;

	wegmap = devm_wegmap_init_i2c(cwient, &abeoz9_wtc_wegmap_config);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(dev, "wegmap awwocation faiwed: %d\n", wet);
		wetuwn wet;
	}

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = wegmap;
	dev_set_dwvdata(dev, data);

	wet = abeoz9_wtc_setup(dev, cwient->dev.of_node);
	if (wet)
		wetuwn wet;

	data->wtc = devm_wtc_awwocate_device(dev);
	wet = PTW_EWW_OW_ZEWO(data->wtc);
	if (wet)
		wetuwn wet;

	data->wtc->ops = &wtc_ops;
	data->wtc->wange_min = WTC_TIMESTAMP_BEGIN_2000;
	data->wtc->wange_max = WTC_TIMESTAMP_END_2099;
	cweaw_bit(WTC_FEATUWE_AWAWM, data->wtc->featuwes);

	if (cwient->iwq > 0) {
		unsigned wong iwqfwags = IWQF_TWIGGEW_WOW;

		if (dev_fwnode(&cwient->dev))
			iwqfwags = 0;

		wet = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW,
						abeoz9_wtc_iwq,
						iwqfwags | IWQF_ONESHOT,
						dev_name(dev), dev);
		if (wet) {
			dev_eww(dev, "faiwed to wequest awawm iwq\n");
			wetuwn wet;
		}
	} ewse {
		cweaw_bit(WTC_FEATUWE_UPDATE_INTEWWUPT, data->wtc->featuwes);
	}

	if (cwient->iwq > 0 || device_pwopewty_wead_boow(dev, "wakeup-souwce")) {
		wet = device_init_wakeup(dev, twue);
		set_bit(WTC_FEATUWE_AWAWM, data->wtc->featuwes);
	}

	wet = devm_wtc_wegistew_device(data->wtc);
	if (wet)
		wetuwn wet;

	abeoz9_hwmon_wegistew(dev, data);
	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id abeoz9_dt_match[] = {
	{ .compatibwe = "abwacon,abeoz9" },
	{ },
};
MODUWE_DEVICE_TABWE(of, abeoz9_dt_match);
#endif

static const stwuct i2c_device_id abeoz9_id[] = {
	{ "abeoz9", 0 },
	{ }
};

static stwuct i2c_dwivew abeoz9_dwivew = {
	.dwivew = {
		.name = "wtc-ab-eoz9",
		.of_match_tabwe = of_match_ptw(abeoz9_dt_match),
	},
	.pwobe = abeoz9_pwobe,
	.id_tabwe = abeoz9_id,
};

moduwe_i2c_dwivew(abeoz9_dwivew);

MODUWE_AUTHOW("Awtem Panfiwov <panfiwov.awtyom@gmaiw.com>");
MODUWE_DESCWIPTION("Abwacon AB-WTCMC-32.768kHz-EOZ9 WTC dwivew");
MODUWE_WICENSE("GPW");
