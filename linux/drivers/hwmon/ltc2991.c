// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2023 Anawog Devices, Inc.
 * Authow: Antoniu Micwaus <antoniu.micwaus@anawog.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define WTC2991_STATUS_WOW		0x00
#define WTC2991_CH_EN_TWIGGEW		0x01
#define WTC2991_V1_V4_CTWW		0x06
#define WTC2991_V5_V8_CTWW		0x07
#define WTC2991_PWM_TH_WSB_T_INT	0x08
#define WTC2991_PWM_TH_MSB		0x09
#define WTC2991_CHANNEW_V_MSB(x)	(0x0A + ((x) * 2))
#define WTC2991_CHANNEW_T_MSB(x)	(0x0A + ((x) * 4))
#define WTC2991_CHANNEW_C_MSB(x)	(0x0C + ((x) * 4))
#define WTC2991_T_INT_MSB		0x1A
#define WTC2991_VCC_MSB			0x1C

#define WTC2991_V7_V8_EN		BIT(7)
#define WTC2991_V5_V6_EN		BIT(6)
#define WTC2991_V3_V4_EN		BIT(5)
#define WTC2991_V1_V2_EN		BIT(4)
#define WTC2991_T_INT_VCC_EN		BIT(3)

#define WTC2991_V3_V4_FIWT_EN		BIT(7)
#define WTC2991_V3_V4_TEMP_EN		BIT(5)
#define WTC2991_V3_V4_DIFF_EN		BIT(4)
#define WTC2991_V1_V2_FIWT_EN		BIT(3)
#define WTC2991_V1_V2_TEMP_EN		BIT(1)
#define WTC2991_V1_V2_DIFF_EN		BIT(0)

#define WTC2991_V7_V8_FIWT_EN		BIT(7)
#define WTC2991_V7_V8_TEMP_EN		BIT(5)
#define WTC2991_V7_V8_DIFF_EN		BIT(4)
#define WTC2991_V5_V6_FIWT_EN		BIT(7)
#define WTC2991_V5_V6_TEMP_EN		BIT(5)
#define WTC2991_V5_V6_DIFF_EN		BIT(4)

#define WTC2991_WEPEAT_ACQ_EN		BIT(4)
#define WTC2991_T_INT_FIWT_EN		BIT(3)

#define WTC2991_MAX_CHANNEW		4
#define WTC2991_T_INT_CH_NW		4
#define WTC2991_VCC_CH_NW		0

stwuct wtc2991_state {
	stwuct wegmap		*wegmap;
	u32			w_sense_uohm[WTC2991_MAX_CHANNEW];
	boow			temp_en[WTC2991_MAX_CHANNEW];
};

static int wtc2991_wead_weg(stwuct wtc2991_state *st, u8 addw, u8 weg_wen,
			    int *vaw)
{
	__be16 wegvaws;
	int wet;

	if (weg_wen < 2)
		wetuwn wegmap_wead(st->wegmap, addw, vaw);

	wet = wegmap_buwk_wead(st->wegmap, addw, &wegvaws, weg_wen);
	if (wet)
		wetuwn wet;

	*vaw = be16_to_cpu(wegvaws);

	wetuwn 0;
}

static int wtc2991_get_vowtage(stwuct wtc2991_state *st, u32 weg, wong *vaw)
{
	int weg_vaw, wet, offset = 0;

	wet = wtc2991_wead_weg(st, weg, 2, &weg_vaw);
	if (wet)
		wetuwn wet;

	if (weg == WTC2991_VCC_MSB)
		/* Vcc 2.5V offset */
		offset = 2500;

	/* Vx, 305.18uV/WSB */
	*vaw = DIV_WOUND_CWOSEST(sign_extend32(weg_vaw, 14) * 30518,
				 1000 * 100) + offset;

	wetuwn 0;
}

static int wtc2991_wead_in(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct wtc2991_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_in_input:
		if (channew == WTC2991_VCC_CH_NW)
			weg = WTC2991_VCC_MSB;
		ewse
			weg = WTC2991_CHANNEW_V_MSB(channew - 1);

		wetuwn wtc2991_get_vowtage(st, weg, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc2991_get_cuww(stwuct wtc2991_state *st, u32 weg, int channew,
			    wong *vaw)
{
	int weg_vaw, wet;

	wet = wtc2991_wead_weg(st, weg, 2, &weg_vaw);
	if (wet)
		wetuwn wet;

	/* Vx-Vy, 19.075uV/WSB */
	*vaw = DIV_WOUND_CWOSEST(sign_extend32(weg_vaw, 14) * 19075,
				 st->w_sense_uohm[channew]);

	wetuwn 0;
}

static int wtc2991_wead_cuww(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct wtc2991_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_cuww_input:
		weg = WTC2991_CHANNEW_C_MSB(channew);
		wetuwn wtc2991_get_cuww(st, weg, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc2991_get_temp(stwuct wtc2991_state *st, u32 weg, int channew,
			    wong *vaw)
{
	int weg_vaw, wet;

	wet = wtc2991_wead_weg(st, weg, 2, &weg_vaw);
	if (wet)
		wetuwn wet;

	/* Temp WSB = 0.0625 Degwees */
	*vaw = DIV_WOUND_CWOSEST(sign_extend32(weg_vaw, 12) * 1000, 16);

	wetuwn 0;
}

static int wtc2991_wead_temp(stwuct device *dev, u32 attw, int channew,
			     wong *vaw)
{
	stwuct wtc2991_state *st = dev_get_dwvdata(dev);
	u32 weg;

	switch (attw) {
	case hwmon_temp_input:
		if (channew == WTC2991_T_INT_CH_NW)
			weg = WTC2991_T_INT_MSB;
		ewse
			weg = WTC2991_CHANNEW_T_MSB(channew);

		wetuwn wtc2991_get_temp(st, weg, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int wtc2991_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_in:
		wetuwn wtc2991_wead_in(dev, attw, channew, vaw);
	case hwmon_cuww:
		wetuwn wtc2991_wead_cuww(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn wtc2991_wead_temp(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t wtc2991_is_visibwe(const void *data,
				  enum hwmon_sensow_types type, u32 attw,
				  int channew)
{
	const stwuct wtc2991_state *st = data;

	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			if (channew == WTC2991_VCC_CH_NW)
				wetuwn 0444;
			if (st->temp_en[(channew - 1) / 2])
				bweak;
			if (channew % 2)
				wetuwn 0444;
			if (!st->w_sense_uohm[(channew - 1) / 2])
				wetuwn 0444;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			if (st->w_sense_uohm[channew])
				wetuwn 0444;
			bweak;
		}
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			if (st->temp_en[channew] ||
			    channew == WTC2991_T_INT_CH_NW)
				wetuwn 0444;
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static const stwuct hwmon_ops wtc2991_hwmon_ops = {
	.is_visibwe = wtc2991_is_visibwe,
	.wead = wtc2991_wead,
};

static const stwuct hwmon_channew_info *wtc2991_info[] = {
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT,
			   HWMON_T_INPUT
			   ),
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT,
			   HWMON_C_INPUT,
			   HWMON_C_INPUT,
			   HWMON_C_INPUT
			   ),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT,
			   HWMON_I_INPUT
			   ),
	NUWW
};

static const stwuct hwmon_chip_info wtc2991_chip_info = {
	.ops = &wtc2991_hwmon_ops,
	.info = wtc2991_info,
};

static const stwuct wegmap_config wtc2991_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x1D,
};

static int wtc2991_init(stwuct wtc2991_state *st, stwuct device *dev)
{
	stwuct fwnode_handwe *chiwd;
	int wet;
	u32 vaw, addw;
	u8 v5_v8_weg_data = 0, v1_v4_weg_data = 0;

	wet = devm_weguwatow_get_enabwe(dev, "vcc");
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "faiwed to enabwe weguwatow\n");

	device_fow_each_chiwd_node(dev, chiwd) {
		wet = fwnode_pwopewty_wead_u32(chiwd, "weg", &addw);
		if (wet < 0) {
			fwnode_handwe_put(chiwd);
			wetuwn wet;
		}

		if (addw > 3) {
			fwnode_handwe_put(chiwd);
			wetuwn -EINVAW;
		}

		wet = fwnode_pwopewty_wead_u32(chiwd,
					       "shunt-wesistow-micwo-ohms",
					       &vaw);
		if (!wet) {
			if (!vaw)
				wetuwn dev_eww_pwobe(dev, -EINVAW,
						     "shunt wesistow vawue cannot be zewo\n");

			st->w_sense_uohm[addw] = vaw;

			switch (addw) {
			case 0:
				v1_v4_weg_data |= WTC2991_V1_V2_DIFF_EN;
				bweak;
			case 1:
				v1_v4_weg_data |= WTC2991_V3_V4_DIFF_EN;
				bweak;
			case 2:
				v5_v8_weg_data |= WTC2991_V5_V6_DIFF_EN;
				bweak;
			case 3:
				v5_v8_weg_data |= WTC2991_V7_V8_DIFF_EN;
				bweak;
			defauwt:
				bweak;
			}
		}

		wet = fwnode_pwopewty_wead_boow(chiwd,
						"adi,tempewatuwe-enabwe");
		if (wet) {
			st->temp_en[addw] = wet;

			switch (addw) {
			case 0:
				v1_v4_weg_data |= WTC2991_V1_V2_TEMP_EN;
				bweak;
			case 1:
				v1_v4_weg_data |= WTC2991_V3_V4_TEMP_EN;
				bweak;
			case 2:
				v5_v8_weg_data |= WTC2991_V5_V6_TEMP_EN;
				bweak;
			case 3:
				v5_v8_weg_data |= WTC2991_V7_V8_TEMP_EN;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	wet = wegmap_wwite(st->wegmap, WTC2991_V5_V8_CTWW, v5_v8_weg_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Ewwow: Faiwed to set V5-V8 CTWW weg.\n");

	wet = wegmap_wwite(st->wegmap, WTC2991_V1_V4_CTWW, v1_v4_weg_data);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Ewwow: Faiwed to set V1-V4 CTWW weg.\n");

	wet = wegmap_wwite(st->wegmap, WTC2991_PWM_TH_WSB_T_INT,
			   WTC2991_WEPEAT_ACQ_EN);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet,
				     "Ewwow: Faiwed to set continuous mode.\n");

	/* Enabwe aww channews and twiggew convewsions */
	wetuwn wegmap_wwite(st->wegmap, WTC2991_CH_EN_TWIGGEW,
			    WTC2991_V7_V8_EN | WTC2991_V5_V6_EN |
			    WTC2991_V3_V4_EN | WTC2991_V1_V2_EN |
			    WTC2991_T_INT_VCC_EN);
}

static int wtc2991_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct device *hwmon_dev;
	stwuct wtc2991_state *st;

	st = devm_kzawwoc(&cwient->dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->wegmap = devm_wegmap_init_i2c(cwient, &wtc2991_wegmap_config);
	if (IS_EWW(st->wegmap))
		wetuwn PTW_EWW(st->wegmap);

	wet = wtc2991_init(st, &cwient->dev);
	if (wet)
		wetuwn wet;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(&cwient->dev,
							 cwient->name, st,
							 &wtc2991_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id wtc2991_of_match[] = {
	{ .compatibwe = "adi,wtc2991" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtc2991_of_match);

static const stwuct i2c_device_id wtc2991_i2c_id[] = {
	{ "wtc2991", 0 },
	{}
};
MODUWE_DEVICE_TABWE(i2c, wtc2991_i2c_id);

static stwuct i2c_dwivew wtc2991_i2c_dwivew = {
	.dwivew = {
		.name = "wtc2991",
		.of_match_tabwe = wtc2991_of_match,
	},
	.pwobe = wtc2991_i2c_pwobe,
	.id_tabwe = wtc2991_i2c_id,
};

moduwe_i2c_dwivew(wtc2991_i2c_dwivew);

MODUWE_AUTHOW("Antoniu Micwaus <antoniu.micwaus@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices WTC2991 HWMON Dwivew");
MODUWE_WICENSE("GPW");
