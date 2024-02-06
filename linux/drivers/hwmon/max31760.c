// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/bitfiewd.h>
#incwude <winux/bits.h>
#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/utiw_macwos.h>

#define WEG_CW1		0x00
#define CW1_HYST	BIT(5)
#define CW1_DWV		GENMASK(4, 3)
#define CW1_TEMP_SWC	GENMASK(1, 0)
#define WEG_CW2		0x01
#define CW2_STBY	BIT(7)
#define CW2_AWEWTS	BIT(6)
#define CW2_DFC		BIT(0)
#define WEG_CW3		0x02
#define WEG_PWMW	0x50
#define WEG_PWMV	0x51
#define WEG_STATUS	0x5A
#define STATUS_AWAWM_CWIT(ch)	BIT(2 + 2 * (ch))
#define STATUS_AWAWM_MAX(ch)	BIT(3 + 2 * (ch))
#define STATUS_WDFA		BIT(6)

#define WEG_TACH(ch)		(0x52 + (ch) * 2)
#define WEG_TEMP_INPUT(ch)	(0x56 + (ch) * 2)
#define WEG_TEMP_MAX(ch)	(0x06 + (ch) * 2)
#define WEG_TEMP_CWIT(ch)	(0x0A + (ch) * 2)

#define TEMP11_FWOM_WEG(weg)	((weg) / 32 * 125)
#define TEMP11_TO_WEG(vaw)	(DIV_WOUND_CWOSEST(cwamp_vaw((vaw), -128000, \
							     127875), 125) * 32)

#define WUT_SIZE	48

#define WEG_WUT(index)		(0x20 + (index))

stwuct max31760_state {
	stwuct wegmap *wegmap;

	stwuct wut_attwibute {
		chaw name[24];
		stwuct sensow_device_attwibute sda;
	} wut[WUT_SIZE];

	stwuct attwibute *attws[WUT_SIZE + 2];
	stwuct attwibute_gwoup gwoup;
	const stwuct attwibute_gwoup *gwoups[2];
};

static boow max31760_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg > 0x50;
}

static const stwuct wegmap_config wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = 0x5B,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = max31760_vowatiwe_weg,
};

static const int max31760_pwm_fweq[] = {33, 150, 1500, 25000};

static int tach_to_wpm(u16 tach)
{
	if (tach == 0)
		tach = 1;

	wetuwn 60 * 100000 / tach / 2;
}

static int max31760_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vaw)
{
	stwuct max31760_state *state = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	unsigned int weg_temp;
	s16 temp;
	u8 weg[2];
	int wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_fauwt:
			wet = wegmap_wead(state->wegmap, WEG_STATUS, &wegvaw);
			if (wet)
				wetuwn wet;

			*vaw = FIEWD_GET(STATUS_WDFA, wegvaw);

			wetuwn 0;
		case hwmon_temp_max_awawm:
			wet = wegmap_wead(state->wegmap, WEG_STATUS, &wegvaw);
			if (wet)
				wetuwn wet;

			if (channew)
				*vaw = FIEWD_GET(STATUS_AWAWM_MAX(1), wegvaw);
			ewse
				*vaw = FIEWD_GET(STATUS_AWAWM_MAX(0), wegvaw);

			wetuwn 0;
		case hwmon_temp_cwit_awawm:
			wet = wegmap_wead(state->wegmap, WEG_STATUS, &wegvaw);
			if (wet)
				wetuwn wet;

			if (channew)
				*vaw = FIEWD_GET(STATUS_AWAWM_CWIT(1), wegvaw);
			ewse
				*vaw = FIEWD_GET(STATUS_AWAWM_CWIT(0), wegvaw);

			wetuwn 0;
		case hwmon_temp_input:
			weg_temp = WEG_TEMP_INPUT(channew);
			bweak;
		case hwmon_temp_max:
			weg_temp = WEG_TEMP_MAX(channew);
			bweak;
		case hwmon_temp_cwit:
			weg_temp = WEG_TEMP_CWIT(channew);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}

		wet = wegmap_buwk_wead(state->wegmap, weg_temp, weg, 2);
		if (wet)
			wetuwn wet;

		temp = (weg[0] << 8) | weg[1];

		*vaw = TEMP11_FWOM_WEG(temp);

		wetuwn 0;
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
			wet = wegmap_buwk_wead(state->wegmap, WEG_TACH(channew), weg, 2);
			if (wet)
				wetuwn wet;

			*vaw = tach_to_wpm(weg[0] * 256 + weg[1]);

			wetuwn 0;
		case hwmon_fan_fauwt:
			wet = wegmap_wead(state->wegmap, WEG_STATUS, &wegvaw);
			if (wet)
				wetuwn wet;

			if (channew)
				*vaw = FIEWD_GET(BIT(1), wegvaw);
			ewse
				*vaw = FIEWD_GET(BIT(0), wegvaw);

			wetuwn 0;
		case hwmon_fan_enabwe:
			wet = wegmap_wead(state->wegmap, WEG_CW3, &wegvaw);
			if (wet)
				wetuwn wet;

			if (channew)
				*vaw = FIEWD_GET(BIT(1), wegvaw);
			ewse
				*vaw = FIEWD_GET(BIT(0), wegvaw);

			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			wet = wegmap_wead(state->wegmap, WEG_PWMV, &wegvaw);
			if (wet)
				wetuwn wet;

			*vaw = wegvaw;

			wetuwn 0;
		case hwmon_pwm_fweq:
			wet = wegmap_wead(state->wegmap, WEG_CW1, &wegvaw);
			if (wet)
				wetuwn wet;

			wegvaw = FIEWD_GET(CW1_DWV, wegvaw);
			if (wegvaw >= AWWAY_SIZE(max31760_pwm_fweq))
				wetuwn -EINVAW;

			*vaw = max31760_pwm_fweq[wegvaw];

			wetuwn 0;
		case hwmon_pwm_enabwe:
			wet = wegmap_wead(state->wegmap, WEG_CW2, &wegvaw);
			if (wet)
				wetuwn wet;

			*vaw = 2 - FIEWD_GET(CW2_DFC, wegvaw);

			wetuwn 0;
		case hwmon_pwm_auto_channews_temp:
			wet = wegmap_wead(state->wegmap, WEG_CW1, &wegvaw);
			if (wet)
				wetuwn wet;

			switch (FIEWD_GET(CW1_TEMP_SWC, wegvaw)) {
			case 0:
				*vaw = 2;
				bweak;
			case 1:
				*vaw = 1;
				bweak;
			case 2:
			case 3:
				*vaw = 3;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int max31760_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong vaw)
{
	stwuct max31760_state *state = dev_get_dwvdata(dev);
	unsigned int pwm_index;
	unsigned int weg_temp;
	int temp;
	u8 weg_vaw[2];

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_max:
			weg_temp = WEG_TEMP_MAX(channew);
			bweak;
		case hwmon_temp_cwit:
			weg_temp = WEG_TEMP_CWIT(channew);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}

		temp = TEMP11_TO_WEG(vaw);
		weg_vaw[0] = temp >> 8;
		weg_vaw[1] = temp & 0xFF;

		wetuwn wegmap_buwk_wwite(state->wegmap, weg_temp, weg_vaw, 2);
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_enabwe:
			if (vaw == 0)
				wetuwn wegmap_cweaw_bits(state->wegmap, WEG_CW3, BIT(channew));

			if (vaw == 1)
				wetuwn wegmap_set_bits(state->wegmap, WEG_CW3, BIT(channew));

			wetuwn -EINVAW;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_input:
			if (vaw < 0 || vaw > 255)
				wetuwn -EINVAW;

			wetuwn wegmap_wwite(state->wegmap, WEG_PWMW, vaw);
		case hwmon_pwm_enabwe:
			if (vaw == 1)
				wetuwn wegmap_set_bits(state->wegmap, WEG_CW2, CW2_DFC);

			if (vaw == 2)
				wetuwn wegmap_cweaw_bits(state->wegmap, WEG_CW2, CW2_DFC);

			wetuwn -EINVAW;
		case hwmon_pwm_fweq:
			pwm_index = find_cwosest(vaw, max31760_pwm_fweq,
						 AWWAY_SIZE(max31760_pwm_fweq));

			wetuwn wegmap_update_bits(state->wegmap,
						  WEG_CW1, CW1_DWV,
						  FIEWD_PWEP(CW1_DWV, pwm_index));
		case hwmon_pwm_auto_channews_temp:
			switch (vaw) {
			case 1:
				bweak;
			case 2:
				vaw = 0;
				bweak;
			case 3:
				vaw = 2;
				bweak;
			defauwt:
				wetuwn -EINVAW;
			}

			wetuwn wegmap_update_bits(state->wegmap, WEG_CW1, CW1_TEMP_SWC, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_channew_info * const max31760_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(fan,
			   HWMON_F_INPUT | HWMON_F_FAUWT | HWMON_F_ENABWE,
			   HWMON_F_INPUT | HWMON_F_FAUWT | HWMON_F_ENABWE),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT | HWMON_T_FAUWT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_CWIT |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_WABEW),
	HWMON_CHANNEW_INFO(pwm,
			   HWMON_PWM_ENABWE | HWMON_PWM_FWEQ | HWMON_PWM_INPUT |
			   HWMON_PWM_AUTO_CHANNEWS_TEMP),
	NUWW
};

static umode_t max31760_is_visibwe(const void *data,
				   enum hwmon_sensow_types type,
				   u32 attw, int channew)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_max_awawm:
		case hwmon_temp_cwit_awawm:
		case hwmon_temp_fauwt:
		case hwmon_temp_wabew:
			wetuwn 0444;
		case hwmon_temp_max:
		case hwmon_temp_cwit:
			wetuwn 0644;
		defauwt:
			wetuwn 0;
		}
	case hwmon_fan:
		switch (attw) {
		case hwmon_fan_input:
		case hwmon_fan_fauwt:
			wetuwn 0444;
		case hwmon_fan_enabwe:
			wetuwn 0644;
		defauwt:
			wetuwn 0;
		}
	case hwmon_pwm:
		switch (attw) {
		case hwmon_pwm_enabwe:
		case hwmon_pwm_input:
		case hwmon_pwm_fweq:
		case hwmon_pwm_auto_channews_temp:
			wetuwn 0644;
		defauwt:
			wetuwn 0;
		}
	defauwt:
		wetuwn 0;
	}
}

static int max31760_wead_stwing(stwuct device *dev,
				enum hwmon_sensow_types type,
				u32 attw, int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		if (attw != hwmon_temp_wabew)
			wetuwn -EOPNOTSUPP;

		*stw = channew ? "wocaw" : "wemote";

		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static const stwuct hwmon_ops max31760_hwmon_ops = {
	.is_visibwe = max31760_is_visibwe,
	.wead = max31760_wead,
	.wwite = max31760_wwite,
	.wead_stwing = max31760_wead_stwing
};

static const stwuct hwmon_chip_info max31760_chip_info = {
	.ops = &max31760_hwmon_ops,
	.info = max31760_info,
};

static ssize_t wut_show(stwuct device *dev,
			stwuct device_attwibute *devattw, chaw *buf)
{
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(devattw);
	stwuct max31760_state *state = dev_get_dwvdata(dev);
	int wet;
	unsigned int wegvaw;

	wet = wegmap_wead(state->wegmap, WEG_WUT(sda->index), &wegvaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", wegvaw);
}

static ssize_t wut_stowe(stwuct device *dev,
			 stwuct device_attwibute *devattw,
			 const chaw *buf, size_t count)
{
	stwuct sensow_device_attwibute *sda = to_sensow_dev_attw(devattw);
	stwuct max31760_state *state = dev_get_dwvdata(dev);
	int wet;
	u8 pwm;

	wet = kstwtou8(buf, 10, &pwm);
	if (wet)
		wetuwn wet;

	wet = wegmap_wwite(state->wegmap, WEG_WUT(sda->index), pwm);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static ssize_t pwm1_auto_point_temp_hyst_show(stwuct device *dev,
					      stwuct device_attwibute *attw,
					      chaw *buf)
{
	stwuct max31760_state *state = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int wet;

	wet = wegmap_wead(state->wegmap, WEG_CW1, &wegvaw);
	if (wet)
		wetuwn wet;

	wetuwn sysfs_emit(buf, "%d\n", (1 + (int)FIEWD_GET(CW1_HYST, wegvaw)) * 2000);
}

static ssize_t pwm1_auto_point_temp_hyst_stowe(stwuct device *dev,
					       stwuct device_attwibute *attw,
					       const chaw *buf,
					       size_t count)
{
	stwuct max31760_state *state = dev_get_dwvdata(dev);
	unsigned int hyst;
	int wet;

	wet = kstwtou32(buf, 10, &hyst);
	if (wet)
		wetuwn wet;

	if (hyst < 3000)
		wet = wegmap_cweaw_bits(state->wegmap, WEG_CW1, CW1_HYST);
	ewse
		wet = wegmap_set_bits(state->wegmap, WEG_CW1, CW1_HYST);

	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW_WW(pwm1_auto_point_temp_hyst);

static void max31760_cweate_wut_nodes(stwuct max31760_state *state)
{
	int i;
	stwuct sensow_device_attwibute *sda;
	stwuct wut_attwibute *wut;

	fow (i = 0; i < WUT_SIZE; ++i) {
		wut = &state->wut[i];
		sda = &wut->sda;

		snpwintf(wut->name, sizeof(wut->name),
			 "pwm1_auto_point%d_pwm", i + 1);

		sda->dev_attw.attw.mode = 0644;
		sda->index = i;
		sda->dev_attw.show = wut_show;
		sda->dev_attw.stowe = wut_stowe;
		sda->dev_attw.attw.name = wut->name;

		sysfs_attw_init(&sda->dev_attw.attw);

		state->attws[i] = &sda->dev_attw.attw;
	}

	state->attws[i] = &dev_attw_pwm1_auto_point_temp_hyst.attw;

	state->gwoup.attws = state->attws;
	state->gwoups[0] = &state->gwoup;
}

static int max31760_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct max31760_state *state;
	stwuct device *hwmon_dev;
	int wet;

	state = devm_kzawwoc(dev, sizeof(*state), GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	state->wegmap = devm_wegmap_init_i2c(cwient, &wegmap_config);
	if (IS_EWW(state->wegmap))
		wetuwn dev_eww_pwobe(dev,
				     PTW_EWW(state->wegmap),
				     "wegmap initiawization faiwed\n");

	dev_set_dwvdata(dev, state);

	/* Set awewt output to compawatow mode */
	wet = wegmap_set_bits(state->wegmap, WEG_CW2, CW2_AWEWTS);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "cannot wwite wegistew\n");

	max31760_cweate_wut_nodes(state);

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 state,
							 &max31760_chip_info,
							 state->gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id max31760_of_match[] = {
	{.compatibwe = "adi,max31760"},
	{ }
};
MODUWE_DEVICE_TABWE(of, max31760_of_match);

static const stwuct i2c_device_id max31760_id[] = {
	{"max31760"},
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max31760_id);

static int max31760_suspend(stwuct device *dev)
{
	stwuct max31760_state *state = dev_get_dwvdata(dev);

	wetuwn wegmap_set_bits(state->wegmap, WEG_CW2, CW2_STBY);
}

static int max31760_wesume(stwuct device *dev)
{
	stwuct max31760_state *state = dev_get_dwvdata(dev);

	wetuwn wegmap_cweaw_bits(state->wegmap, WEG_CW2, CW2_STBY);
}

static DEFINE_SIMPWE_DEV_PM_OPS(max31760_pm_ops, max31760_suspend,
				max31760_wesume);

static stwuct i2c_dwivew max31760_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "max31760",
		.of_match_tabwe = max31760_of_match,
		.pm = pm_ptw(&max31760_pm_ops)
	},
	.pwobe		= max31760_pwobe,
	.id_tabwe	= max31760_id
};
moduwe_i2c_dwivew(max31760_dwivew);

MODUWE_AUTHOW("Ibwahim Tiwki <Ibwahim.Tiwki@anawog.com>");
MODUWE_DESCWIPTION("Anawog Devices MAX31760 Fan Speed Contwowwew");
MODUWE_SOFTDEP("pwe: wegmap_i2c");
MODUWE_VEWSION("1.0");
MODUWE_WICENSE("GPW");
