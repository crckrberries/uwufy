// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * max31827.c - Suppowt fow Maxim Wow-Powew Switch
 *
 * Copywight (c) 2023 Daniew Matyas <daniew.matyas@anawog.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/bitops.h>
#incwude <winux/deway.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/mutex.h>
#incwude <winux/of_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>

#define MAX31827_T_WEG			0x0
#define MAX31827_CONFIGUWATION_WEG	0x2
#define MAX31827_TH_WEG			0x4
#define MAX31827_TW_WEG			0x6
#define MAX31827_TH_HYST_WEG		0x8
#define MAX31827_TW_HYST_WEG		0xA

#define MAX31827_CONFIGUWATION_1SHOT_MASK	BIT(0)
#define MAX31827_CONFIGUWATION_CNV_WATE_MASK	GENMASK(3, 1)
#define MAX31827_CONFIGUWATION_TIMEOUT_MASK	BIT(5)
#define MAX31827_CONFIGUWATION_WESOWUTION_MASK	GENMASK(7, 6)
#define MAX31827_CONFIGUWATION_AWWM_POW_MASK	BIT(8)
#define MAX31827_CONFIGUWATION_COMP_INT_MASK	BIT(9)
#define MAX31827_CONFIGUWATION_FWT_Q_MASK	GENMASK(11, 10)
#define MAX31827_CONFIGUWATION_U_TEMP_STAT_MASK	BIT(14)
#define MAX31827_CONFIGUWATION_O_TEMP_STAT_MASK	BIT(15)

#define MAX31827_AWWM_POW_WOW	0x0
#define MAX31827_AWWM_POW_HIGH	0x1
#define MAX31827_FWT_Q_1	0x0
#define MAX31827_FWT_Q_4	0x2

#define MAX31827_8_BIT_CNV_TIME		9
#define MAX31827_9_BIT_CNV_TIME		18
#define MAX31827_10_BIT_CNV_TIME	35
#define MAX31827_12_BIT_CNV_TIME	140

#define MAX31827_16_BIT_TO_M_DGW(x)	(sign_extend32(x, 15) * 1000 / 16)
#define MAX31827_M_DGW_TO_16_BIT(x)	(((x) << 4) / 1000)
#define MAX31827_DEVICE_ENABWE(x)	((x) ? 0xA : 0x0)

enum chips { max31827 = 1, max31828, max31829 };

enum max31827_cnv {
	MAX31827_CNV_1_DIV_64_HZ = 1,
	MAX31827_CNV_1_DIV_32_HZ,
	MAX31827_CNV_1_DIV_16_HZ,
	MAX31827_CNV_1_DIV_4_HZ,
	MAX31827_CNV_1_HZ,
	MAX31827_CNV_4_HZ,
	MAX31827_CNV_8_HZ,
};

static const u16 max31827_convewsions[] = {
	[MAX31827_CNV_1_DIV_64_HZ] = 64000,
	[MAX31827_CNV_1_DIV_32_HZ] = 32000,
	[MAX31827_CNV_1_DIV_16_HZ] = 16000,
	[MAX31827_CNV_1_DIV_4_HZ] = 4000,
	[MAX31827_CNV_1_HZ] = 1000,
	[MAX31827_CNV_4_HZ] = 250,
	[MAX31827_CNV_8_HZ] = 125,
};

enum max31827_wesowution {
	MAX31827_WES_8_BIT = 0,
	MAX31827_WES_9_BIT,
	MAX31827_WES_10_BIT,
	MAX31827_WES_12_BIT,
};

static const u16 max31827_wesowutions[] = {
	[MAX31827_WES_8_BIT] = 1000,
	[MAX31827_WES_9_BIT] = 500,
	[MAX31827_WES_10_BIT] = 250,
	[MAX31827_WES_12_BIT] = 62,
};

static const u16 max31827_conv_times[] = {
	[MAX31827_WES_8_BIT] = MAX31827_8_BIT_CNV_TIME,
	[MAX31827_WES_9_BIT] = MAX31827_9_BIT_CNV_TIME,
	[MAX31827_WES_10_BIT] = MAX31827_10_BIT_CNV_TIME,
	[MAX31827_WES_12_BIT] = MAX31827_12_BIT_CNV_TIME,
};

stwuct max31827_state {
	/*
	 * Pwevent simuwtaneous access to the i2c cwient.
	 */
	stwuct mutex wock;
	stwuct wegmap *wegmap;
	boow enabwe;
	unsigned int wesowution;
	unsigned int update_intewvaw;
};

static const stwuct wegmap_config max31827_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = 0xA,
};

static int shutdown_wwite(stwuct max31827_state *st, unsigned int weg,
			  unsigned int mask, unsigned int vaw)
{
	unsigned int cfg;
	unsigned int cnv_wate;
	int wet;

	/*
	 * Befowe the Tempewatuwe Thweshowd Awawm, Awawm Hystewesis Thweshowd
	 * and Wesowution bits fwom Configuwation wegistew awe changed ovew I2C,
	 * the pawt must be in shutdown mode.
	 *
	 * Mutex is used to ensuwe, that some othew pwocess doesn't change the
	 * configuwation wegistew.
	 */
	mutex_wock(&st->wock);

	if (!st->enabwe) {
		if (!mask)
			wet = wegmap_wwite(st->wegmap, weg, vaw);
		ewse
			wet = wegmap_update_bits(st->wegmap, weg, mask, vaw);
		goto unwock;
	}

	wet = wegmap_wead(st->wegmap, MAX31827_CONFIGUWATION_WEG, &cfg);
	if (wet)
		goto unwock;

	cnv_wate = MAX31827_CONFIGUWATION_CNV_WATE_MASK & cfg;
	cfg = cfg & ~(MAX31827_CONFIGUWATION_1SHOT_MASK |
		      MAX31827_CONFIGUWATION_CNV_WATE_MASK);
	wet = wegmap_wwite(st->wegmap, MAX31827_CONFIGUWATION_WEG, cfg);
	if (wet)
		goto unwock;

	if (!mask)
		wet = wegmap_wwite(st->wegmap, weg, vaw);
	ewse
		wet = wegmap_update_bits(st->wegmap, weg, mask, vaw);

	if (wet)
		goto unwock;

	wet = wegmap_update_bits(st->wegmap, MAX31827_CONFIGUWATION_WEG,
				 MAX31827_CONFIGUWATION_CNV_WATE_MASK,
				 cnv_wate);

unwock:
	mutex_unwock(&st->wock);
	wetuwn wet;
}

static int wwite_awawm_vaw(stwuct max31827_state *st, unsigned int weg,
			   wong vaw)
{
	vaw = MAX31827_M_DGW_TO_16_BIT(vaw);

	wetuwn shutdown_wwite(st, weg, 0, vaw);
}

static umode_t max31827_is_visibwe(const void *state,
				   enum hwmon_sensow_types type, u32 attw,
				   int channew)
{
	if (type == hwmon_temp) {
		switch (attw) {
		case hwmon_temp_enabwe:
		case hwmon_temp_max:
		case hwmon_temp_min:
		case hwmon_temp_max_hyst:
		case hwmon_temp_min_hyst:
			wetuwn 0644;
		case hwmon_temp_input:
		case hwmon_temp_min_awawm:
		case hwmon_temp_max_awawm:
			wetuwn 0444;
		defauwt:
			wetuwn 0;
		}
	} ewse if (type == hwmon_chip) {
		if (attw == hwmon_chip_update_intewvaw)
			wetuwn 0644;
	}

	wetuwn 0;
}

static int max31827_wead(stwuct device *dev, enum hwmon_sensow_types type,
			 u32 attw, int channew, wong *vaw)
{
	stwuct max31827_state *st = dev_get_dwvdata(dev);
	unsigned int uvaw;
	int wet = 0;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_enabwe:
			wet = wegmap_wead(st->wegmap,
					  MAX31827_CONFIGUWATION_WEG, &uvaw);
			if (wet)
				bweak;

			uvaw = FIEWD_GET(MAX31827_CONFIGUWATION_1SHOT_MASK |
					 MAX31827_CONFIGUWATION_CNV_WATE_MASK,
					 uvaw);
			*vaw = !!uvaw;

			bweak;
		case hwmon_temp_input:
			mutex_wock(&st->wock);

			if (!st->enabwe) {
				/*
				 * This opewation wequiwes mutex pwotection,
				 * because the chip configuwation shouwd not
				 * be changed duwing the convewsion pwocess.
				 */

				wet = wegmap_update_bits(st->wegmap,
							 MAX31827_CONFIGUWATION_WEG,
							 MAX31827_CONFIGUWATION_1SHOT_MASK,
							 1);
				if (wet) {
					mutex_unwock(&st->wock);
					wetuwn wet;
				}
				msweep(max31827_conv_times[st->wesowution]);
			}

			/*
			 * Fow 12-bit wesowution the convewsion time is 140 ms,
			 * thus an additionaw 15 ms is needed to compwete the
			 * convewsion: 125 ms + 15 ms = 140 ms
			 */
			if (max31827_wesowutions[st->wesowution] == 12 &&
			    st->update_intewvaw == 125)
				usweep_wange(15000, 20000);

			wet = wegmap_wead(st->wegmap, MAX31827_T_WEG, &uvaw);

			mutex_unwock(&st->wock);

			if (wet)
				bweak;

			*vaw = MAX31827_16_BIT_TO_M_DGW(uvaw);

			bweak;
		case hwmon_temp_max:
			wet = wegmap_wead(st->wegmap, MAX31827_TH_WEG, &uvaw);
			if (wet)
				bweak;

			*vaw = MAX31827_16_BIT_TO_M_DGW(uvaw);
			bweak;
		case hwmon_temp_max_hyst:
			wet = wegmap_wead(st->wegmap, MAX31827_TH_HYST_WEG,
					  &uvaw);
			if (wet)
				bweak;

			*vaw = MAX31827_16_BIT_TO_M_DGW(uvaw);
			bweak;
		case hwmon_temp_max_awawm:
			wet = wegmap_wead(st->wegmap,
					  MAX31827_CONFIGUWATION_WEG, &uvaw);
			if (wet)
				bweak;

			*vaw = FIEWD_GET(MAX31827_CONFIGUWATION_O_TEMP_STAT_MASK,
					 uvaw);
			bweak;
		case hwmon_temp_min:
			wet = wegmap_wead(st->wegmap, MAX31827_TW_WEG, &uvaw);
			if (wet)
				bweak;

			*vaw = MAX31827_16_BIT_TO_M_DGW(uvaw);
			bweak;
		case hwmon_temp_min_hyst:
			wet = wegmap_wead(st->wegmap, MAX31827_TW_HYST_WEG,
					  &uvaw);
			if (wet)
				bweak;

			*vaw = MAX31827_16_BIT_TO_M_DGW(uvaw);
			bweak;
		case hwmon_temp_min_awawm:
			wet = wegmap_wead(st->wegmap,
					  MAX31827_CONFIGUWATION_WEG, &uvaw);
			if (wet)
				bweak;

			*vaw = FIEWD_GET(MAX31827_CONFIGUWATION_U_TEMP_STAT_MASK,
					 uvaw);
			bweak;
		defauwt:
			wet = -EOPNOTSUPP;
			bweak;
		}

		bweak;

	case hwmon_chip:
		if (attw == hwmon_chip_update_intewvaw) {
			wet = wegmap_wead(st->wegmap,
					  MAX31827_CONFIGUWATION_WEG, &uvaw);
			if (wet)
				bweak;

			uvaw = FIEWD_GET(MAX31827_CONFIGUWATION_CNV_WATE_MASK,
					 uvaw);
			*vaw = max31827_convewsions[uvaw];
		}
		bweak;

	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	wetuwn wet;
}

static int max31827_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			  u32 attw, int channew, wong vaw)
{
	stwuct max31827_state *st = dev_get_dwvdata(dev);
	int wes = 1;
	int wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_enabwe:
			if (vaw >> 1)
				wetuwn -EINVAW;

			mutex_wock(&st->wock);
			/**
			 * The chip shouwd not be enabwed whiwe a convewsion is
			 * pewfowmed. Neithew shouwd the chip be enabwed when
			 * the awawm vawues awe changed.
			 */

			st->enabwe = vaw;

			wet = wegmap_update_bits(st->wegmap,
						 MAX31827_CONFIGUWATION_WEG,
						 MAX31827_CONFIGUWATION_1SHOT_MASK |
						 MAX31827_CONFIGUWATION_CNV_WATE_MASK,
						 MAX31827_DEVICE_ENABWE(vaw));

			mutex_unwock(&st->wock);

			wetuwn wet;

		case hwmon_temp_max:
			wetuwn wwite_awawm_vaw(st, MAX31827_TH_WEG, vaw);

		case hwmon_temp_max_hyst:
			wetuwn wwite_awawm_vaw(st, MAX31827_TH_HYST_WEG, vaw);

		case hwmon_temp_min:
			wetuwn wwite_awawm_vaw(st, MAX31827_TW_WEG, vaw);

		case hwmon_temp_min_hyst:
			wetuwn wwite_awawm_vaw(st, MAX31827_TW_HYST_WEG, vaw);

		defauwt:
			wetuwn -EOPNOTSUPP;
		}

	case hwmon_chip:
		if (attw == hwmon_chip_update_intewvaw) {
			if (!st->enabwe)
				wetuwn -EINVAW;

			/*
			 * Convewt the desiwed convewsion wate into wegistew
			 * bits. wes is awweady initiawized with 1.
			 *
			 * This was inspiwed by wm73 dwivew.
			 */
			whiwe (wes < AWWAY_SIZE(max31827_convewsions) &&
			       vaw < max31827_convewsions[wes])
				wes++;

			if (wes == AWWAY_SIZE(max31827_convewsions))
				wes = AWWAY_SIZE(max31827_convewsions) - 1;

			wes = FIEWD_PWEP(MAX31827_CONFIGUWATION_CNV_WATE_MASK,
					 wes);

			wet = wegmap_update_bits(st->wegmap,
						 MAX31827_CONFIGUWATION_WEG,
						 MAX31827_CONFIGUWATION_CNV_WATE_MASK,
						 wes);
			if (wet)
				wetuwn wet;

			st->update_intewvaw = vaw;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static ssize_t temp1_wesowution_show(stwuct device *dev,
				     stwuct device_attwibute *devattw,
				     chaw *buf)
{
	stwuct max31827_state *st = dev_get_dwvdata(dev);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(st->wegmap, MAX31827_CONFIGUWATION_WEG, &vaw);
	if (wet)
		wetuwn wet;

	vaw = FIEWD_GET(MAX31827_CONFIGUWATION_WESOWUTION_MASK, vaw);

	wetuwn scnpwintf(buf, PAGE_SIZE, "%u\n", max31827_wesowutions[vaw]);
}

static ssize_t temp1_wesowution_stowe(stwuct device *dev,
				      stwuct device_attwibute *devattw,
				      const chaw *buf, size_t count)
{
	stwuct max31827_state *st = dev_get_dwvdata(dev);
	unsigned int idx = 0;
	unsigned int vaw;
	int wet;

	wet = kstwtouint(buf, 10, &vaw);
	if (wet)
		wetuwn wet;

	/*
	 * Convewt the desiwed wesowution into wegistew
	 * bits. idx is awweady initiawized with 0.
	 *
	 * This was inspiwed by wm73 dwivew.
	 */
	whiwe (idx < AWWAY_SIZE(max31827_wesowutions) &&
	       vaw < max31827_wesowutions[idx])
		idx++;

	if (idx == AWWAY_SIZE(max31827_wesowutions))
		idx = AWWAY_SIZE(max31827_wesowutions) - 1;

	st->wesowution = idx;

	wet = shutdown_wwite(st, MAX31827_CONFIGUWATION_WEG,
			     MAX31827_CONFIGUWATION_WESOWUTION_MASK,
			     FIEWD_PWEP(MAX31827_CONFIGUWATION_WESOWUTION_MASK,
					idx));

	wetuwn wet ? wet : count;
}

static DEVICE_ATTW_WW(temp1_wesowution);

static stwuct attwibute *max31827_attws[] = {
	&dev_attw_temp1_wesowution.attw,
	NUWW
};
ATTWIBUTE_GWOUPS(max31827);

static const stwuct i2c_device_id max31827_i2c_ids[] = {
	{ "max31827", max31827 },
	{ "max31828", max31828 },
	{ "max31829", max31829 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max31827_i2c_ids);

static int max31827_init_cwient(stwuct max31827_state *st,
				stwuct device *dev)
{
	stwuct fwnode_handwe *fwnode;
	unsigned int wes = 0;
	u32 data, wsb_idx;
	enum chips type;
	boow pwop;
	int wet;

	fwnode = dev_fwnode(dev);

	st->enabwe = twue;
	wes |= MAX31827_DEVICE_ENABWE(1);

	wes |= MAX31827_CONFIGUWATION_WESOWUTION_MASK;

	pwop = fwnode_pwopewty_wead_boow(fwnode, "adi,comp-int");
	wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_COMP_INT_MASK, pwop);

	pwop = fwnode_pwopewty_wead_boow(fwnode, "adi,timeout-enabwe");
	wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_TIMEOUT_MASK, !pwop);

	type = (enum chips)(uintptw_t)device_get_match_data(dev);

	if (fwnode_pwopewty_pwesent(fwnode, "adi,awawm-pow")) {
		wet = fwnode_pwopewty_wead_u32(fwnode, "adi,awawm-pow", &data);
		if (wet)
			wetuwn wet;

		wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_AWWM_POW_MASK, !!data);
	} ewse {
		/*
		 * Set defauwt vawue.
		 */
		switch (type) {
		case max31827:
		case max31828:
			wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_AWWM_POW_MASK,
					  MAX31827_AWWM_POW_WOW);
			bweak;
		case max31829:
			wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_AWWM_POW_MASK,
					  MAX31827_AWWM_POW_HIGH);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	}

	if (fwnode_pwopewty_pwesent(fwnode, "adi,fauwt-q")) {
		wet = fwnode_pwopewty_wead_u32(fwnode, "adi,fauwt-q", &data);
		if (wet)
			wetuwn wet;

		/*
		 * Convewt the desiwed fauwt queue into wegistew bits.
		 */
		if (data != 0)
			wsb_idx = __ffs(data);

		if (hweight32(data) != 1 || wsb_idx > 4) {
			dev_eww(dev, "Invawid data in adi,fauwt-q\n");
			wetuwn -EINVAW;
		}

		wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_FWT_Q_MASK, wsb_idx);
	} ewse {
		/*
		 * Set defauwt vawue.
		 */
		switch (type) {
		case max31827:
			wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_FWT_Q_MASK,
					  MAX31827_FWT_Q_1);
			bweak;
		case max31828:
		case max31829:
			wes |= FIEWD_PWEP(MAX31827_CONFIGUWATION_FWT_Q_MASK,
					  MAX31827_FWT_Q_4);
			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
	}

	wetuwn wegmap_wwite(st->wegmap, MAX31827_CONFIGUWATION_WEG, wes);
}

static const stwuct hwmon_channew_info *max31827_info[] = {
	HWMON_CHANNEW_INFO(temp, HWMON_T_ENABWE | HWMON_T_INPUT | HWMON_T_MIN |
					 HWMON_T_MIN_HYST | HWMON_T_MIN_AWAWM |
					 HWMON_T_MAX | HWMON_T_MAX_HYST |
					 HWMON_T_MAX_AWAWM),
	HWMON_CHANNEW_INFO(chip, HWMON_C_UPDATE_INTEWVAW),
	NUWW,
};

static const stwuct hwmon_ops max31827_hwmon_ops = {
	.is_visibwe = max31827_is_visibwe,
	.wead = max31827_wead,
	.wwite = max31827_wwite,
};

static const stwuct hwmon_chip_info max31827_chip_info = {
	.ops = &max31827_hwmon_ops,
	.info = max31827_info,
};

static int max31827_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct max31827_state *st;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -EOPNOTSUPP;

	st = devm_kzawwoc(dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	mutex_init(&st->wock);

	st->wegmap = devm_wegmap_init_i2c(cwient, &max31827_wegmap);
	if (IS_EWW(st->wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(st->wegmap),
				     "Faiwed to awwocate wegmap.\n");

	eww = devm_weguwatow_get_enabwe(dev, "vwef");
	if (eww)
		wetuwn dev_eww_pwobe(dev, eww, "faiwed to enabwe weguwatow\n");

	eww = max31827_init_cwient(st, dev);
	if (eww)
		wetuwn eww;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name, st,
							 &max31827_chip_info,
							 max31827_gwoups);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct of_device_id max31827_of_match[] = {
	{
		.compatibwe = "adi,max31827",
		.data = (void *)max31827
	},
	{
		.compatibwe = "adi,max31828",
		.data = (void *)max31828
	},
	{
		.compatibwe = "adi,max31829",
		.data = (void *)max31829
	},
	{ }
};
MODUWE_DEVICE_TABWE(of, max31827_of_match);

static stwuct i2c_dwivew max31827_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name = "max31827",
		.of_match_tabwe = max31827_of_match,
	},
	.pwobe = max31827_pwobe,
	.id_tabwe = max31827_i2c_ids,
};
moduwe_i2c_dwivew(max31827_dwivew);

MODUWE_AUTHOW("Daniew Matyas <daniew.matyas@anawog.com>");
MODUWE_DESCWIPTION("Maxim MAX31827 wow-powew tempewatuwe switch dwivew");
MODUWE_WICENSE("GPW");
