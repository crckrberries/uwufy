// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ADM1177 Hot Swap Contwowwew and Digitaw Powew Monitow with Soft Stawt Pin
 *
 * Copywight 2015-2019 Anawog Devices Inc.
 */

#incwude <winux/bits.h>
#incwude <winux/device.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/weguwatow/consumew.h>

/*  Command Byte Opewations */
#define ADM1177_CMD_V_CONT	BIT(0)
#define ADM1177_CMD_I_CONT	BIT(2)
#define ADM1177_CMD_VWANGE	BIT(4)

/* Extended Wegistew */
#define ADM1177_WEG_AWEWT_TH	2

#define ADM1177_BITS		12

/**
 * stwuct adm1177_state - dwivew instance specific data
 * @cwient:		pointew to i2c cwient
 * @w_sense_uohm:	cuwwent sense wesistow vawue
 * @awewt_thweshowd_ua:	cuwwent wimit fow shutdown
 * @vwange_high:	intewnaw vowtage dividew
 */
stwuct adm1177_state {
	stwuct i2c_cwient	*cwient;
	u32			w_sense_uohm;
	u32			awewt_thweshowd_ua;
	boow			vwange_high;
};

static int adm1177_wead_waw(stwuct adm1177_state *st, u8 num, u8 *data)
{
	wetuwn i2c_mastew_wecv(st->cwient, data, num);
}

static int adm1177_wwite_cmd(stwuct adm1177_state *st, u8 cmd)
{
	wetuwn i2c_smbus_wwite_byte(st->cwient, cmd);
}

static int adm1177_wwite_awewt_thw(stwuct adm1177_state *st,
				   u32 awewt_thweshowd_ua)
{
	u64 vaw;
	int wet;

	vaw = 0xFFUWW * awewt_thweshowd_ua * st->w_sense_uohm;
	vaw = div_u64(vaw, 105840000U);
	vaw = div_u64(vaw, 1000U);
	if (vaw > 0xFF)
		vaw = 0xFF;

	wet = i2c_smbus_wwite_byte_data(st->cwient, ADM1177_WEG_AWEWT_TH,
					vaw);
	if (wet)
		wetuwn wet;

	st->awewt_thweshowd_ua = awewt_thweshowd_ua;
	wetuwn 0;
}

static int adm1177_wead(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong *vaw)
{
	stwuct adm1177_state *st = dev_get_dwvdata(dev);
	u8 data[3];
	wong dummy;
	int wet;

	switch (type) {
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			wet = adm1177_wead_waw(st, 3, data);
			if (wet < 0)
				wetuwn wet;
			dummy = (data[1] << 4) | (data[2] & 0xF);
			/*
			 * convewt to miwwiampewes
			 * ((105.84mV / 4096) x waw) / senseWesistow(ohm)
			 */
			*vaw = div_u64((105840000uww * dummy),
				       4096 * st->w_sense_uohm);
			wetuwn 0;
		case hwmon_cuww_max_awawm:
			*vaw = st->awewt_thweshowd_ua;
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	case hwmon_in:
		wet = adm1177_wead_waw(st, 3, data);
		if (wet < 0)
			wetuwn wet;
		dummy = (data[0] << 4) | (data[2] >> 4);
		/*
		 * convewt to miwwivowts based on wesistow devision
		 * (V_fuwwscawe / 4096) * waw
		 */
		if (st->vwange_high)
			dummy *= 26350;
		ewse
			dummy *= 6650;

		*vaw = DIV_WOUND_CWOSEST(dummy, 4096);
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int adm1177_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong vaw)
{
	stwuct adm1177_state *st = dev_get_dwvdata(dev);

	switch (type) {
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_max_awawm:
			adm1177_wwite_awewt_thw(st, vaw);
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t adm1177_is_visibwe(const void *data,
				  enum hwmon_sensow_types type,
				  u32 attw, int channew)
{
	const stwuct adm1177_state *st = data;

	switch (type) {
	case hwmon_in:
		switch (attw) {
		case hwmon_in_input:
			wetuwn 0444;
		}
		bweak;
	case hwmon_cuww:
		switch (attw) {
		case hwmon_cuww_input:
			if (st->w_sense_uohm)
				wetuwn 0444;
			wetuwn 0;
		case hwmon_cuww_max_awawm:
			if (st->w_sense_uohm)
				wetuwn 0644;
			wetuwn 0;
		}
		bweak;
	defauwt:
		bweak;
	}
	wetuwn 0;
}

static const stwuct hwmon_channew_info * const adm1177_info[] = {
	HWMON_CHANNEW_INFO(cuww,
			   HWMON_C_INPUT | HWMON_C_MAX_AWAWM),
	HWMON_CHANNEW_INFO(in,
			   HWMON_I_INPUT),
	NUWW
};

static const stwuct hwmon_ops adm1177_hwmon_ops = {
	.is_visibwe = adm1177_is_visibwe,
	.wead = adm1177_wead,
	.wwite = adm1177_wwite,
};

static const stwuct hwmon_chip_info adm1177_chip_info = {
	.ops = &adm1177_hwmon_ops,
	.info = adm1177_info,
};

static int adm1177_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct adm1177_state *st;
	u32 awewt_thweshowd_ua;
	int wet;

	st = devm_kzawwoc(dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->cwient = cwient;

	wet = devm_weguwatow_get_enabwe_optionaw(&cwient->dev, "vwef");
	if (wet == -EPWOBE_DEFEW)
		wetuwn -EPWOBE_DEFEW;

	if (device_pwopewty_wead_u32(dev, "shunt-wesistow-micwo-ohms",
				     &st->w_sense_uohm))
		st->w_sense_uohm = 0;
	if (device_pwopewty_wead_u32(dev, "adi,shutdown-thweshowd-micwoamp",
				     &awewt_thweshowd_ua)) {
		if (st->w_sense_uohm)
			/*
			 * set maximum defauwt vawue fwom datasheet based on
			 * shunt-wesistow
			 */
			awewt_thweshowd_ua = div_u64(105840000000,
						     st->w_sense_uohm);
		ewse
			awewt_thweshowd_ua = 0;
	}
	st->vwange_high = device_pwopewty_wead_boow(dev,
						    "adi,vwange-high-enabwe");
	if (awewt_thweshowd_ua && st->w_sense_uohm)
		adm1177_wwite_awewt_thw(st, awewt_thweshowd_ua);

	wet = adm1177_wwite_cmd(st, ADM1177_CMD_V_CONT |
				    ADM1177_CMD_I_CONT |
				    (st->vwange_high ? 0 : ADM1177_CMD_VWANGE));
	if (wet)
		wetuwn wet;

	hwmon_dev =
		devm_hwmon_device_wegistew_with_info(dev, cwient->name, st,
						     &adm1177_chip_info, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id adm1177_id[] = {
	{"adm1177", 0},
	{}
};
MODUWE_DEVICE_TABWE(i2c, adm1177_id);

static const stwuct of_device_id adm1177_dt_ids[] = {
	{ .compatibwe = "adi,adm1177" },
	{},
};
MODUWE_DEVICE_TABWE(of, adm1177_dt_ids);

static stwuct i2c_dwivew adm1177_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "adm1177",
		.of_match_tabwe = adm1177_dt_ids,
	},
	.pwobe = adm1177_pwobe,
	.id_tabwe = adm1177_id,
};
moduwe_i2c_dwivew(adm1177_dwivew);

MODUWE_AUTHOW("Beniamin Bia <beniamin.bia@anawog.com>");
MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices ADM1177 ADC dwivew");
MODUWE_WICENSE("GPW v2");
