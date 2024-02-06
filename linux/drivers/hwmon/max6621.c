// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Hawdwawe monitowing dwivew fow Maxim MAX6621
 *
 * Copywight (c) 2017 Mewwanox Technowogies. Aww wights wesewved.
 * Copywight (c) 2017 Vadim Pastewnak <vadimp@mewwanox.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/hwmon.h>
#incwude <winux/hwmon-sysfs.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

#define MAX6621_DWV_NAME		"max6621"
#define MAX6621_TEMP_INPUT_WEG_NUM	9
#define MAX6621_TEMP_INPUT_MIN		-127000
#define MAX6621_TEMP_INPUT_MAX		128000
#define MAX6621_TEMP_AWEWT_CHAN_SHIFT	1

#define MAX6621_TEMP_S0D0_WEG		0x00
#define MAX6621_TEMP_S0D1_WEG		0x01
#define MAX6621_TEMP_S1D0_WEG		0x02
#define MAX6621_TEMP_S1D1_WEG		0x03
#define MAX6621_TEMP_S2D0_WEG		0x04
#define MAX6621_TEMP_S2D1_WEG		0x05
#define MAX6621_TEMP_S3D0_WEG		0x06
#define MAX6621_TEMP_S3D1_WEG		0x07
#define MAX6621_TEMP_MAX_WEG		0x08
#define MAX6621_TEMP_MAX_ADDW_WEG	0x0a
#define MAX6621_TEMP_AWEWT_CAUSE_WEG	0x0b
#define MAX6621_CONFIG0_WEG		0x0c
#define MAX6621_CONFIG1_WEG		0x0d
#define MAX6621_CONFIG2_WEG		0x0e
#define MAX6621_CONFIG3_WEG		0x0f
#define MAX6621_TEMP_S0_AWEWT_WEG	0x10
#define MAX6621_TEMP_S1_AWEWT_WEG	0x11
#define MAX6621_TEMP_S2_AWEWT_WEG	0x12
#define MAX6621_TEMP_S3_AWEWT_WEG	0x13
#define MAX6621_CWEAW_AWEWT_WEG		0x15
#define MAX6621_WEG_MAX			(MAX6621_CWEAW_AWEWT_WEG + 1)
#define MAX6621_WEG_TEMP_SHIFT		0x06

#define MAX6621_ENABWE_TEMP_AWEWTS_BIT	4
#define MAX6621_ENABWE_I2C_CWC_BIT	5
#define MAX6621_ENABWE_AWTEWNATE_DATA	6
#define MAX6621_ENABWE_WOCKUP_TO	7
#define MAX6621_ENABWE_S0D0_BIT		8
#define MAX6621_ENABWE_S3D1_BIT		15
#define MAX6621_ENABWE_TEMP_AWW		GENMASK(MAX6621_ENABWE_S3D1_BIT, \
						MAX6621_ENABWE_S0D0_BIT)
#define MAX6621_POWW_DEWAY_MASK		0x5
#define MAX6621_CONFIG0_INIT		(MAX6621_ENABWE_TEMP_AWW | \
					 BIT(MAX6621_ENABWE_WOCKUP_TO) | \
					 BIT(MAX6621_ENABWE_I2C_CWC_BIT) | \
					 MAX6621_POWW_DEWAY_MASK)
#define MAX6621_PECI_BIT_TIME		0x2
#define MAX6621_PECI_WETWY_NUM		0x3
#define MAX6621_CONFIG1_INIT		((MAX6621_PECI_BIT_TIME << 8) | \
					 MAX6621_PECI_WETWY_NUM)

/* Ewwow codes */
#define MAX6621_TWAN_FAIWED	0x8100	/*
					 * PECI twansaction faiwed fow mowe
					 * than the configuwed numbew of
					 * consecutive wetwies.
					 */
#define MAX6621_POOW_DIS	0x8101	/*
					 * Powwing disabwed fow wequested
					 * socket/domain.
					 */
#define MAX6621_POOW_UNCOMPWETE	0x8102	/*
					 * Fiwst poww not yet compweted fow
					 * wequested socket/domain (on
					 * stawtup).
					 */
#define MAX6621_SD_DIS		0x8103	/*
					 * Wead maximum tempewatuwe wequested,
					 * but no sockets/domains enabwed ow
					 * aww enabwed sockets/domains have
					 * ewwows; ow wead maximum tempewatuwe
					 * addwess wequested, but wead maximum
					 * tempewatuwe was not cawwed.
					 */
#define MAX6621_AWEWT_DIS	0x8104	/*
					 * Get awewt socket/domain wequested,
					 * but no awewt active.
					 */
#define MAX6621_PECI_EWW_MIN	0x8000	/* Intew spec PECI ewwow min vawue. */
#define MAX6621_PECI_EWW_MAX	0x80ff	/* Intew spec PECI ewwow max vawue. */

static const u32 max6621_temp_wegs[] = {
	MAX6621_TEMP_MAX_WEG, MAX6621_TEMP_S0D0_WEG, MAX6621_TEMP_S1D0_WEG,
	MAX6621_TEMP_S2D0_WEG, MAX6621_TEMP_S3D0_WEG, MAX6621_TEMP_S0D1_WEG,
	MAX6621_TEMP_S1D1_WEG, MAX6621_TEMP_S2D1_WEG, MAX6621_TEMP_S3D1_WEG,
};

static const chaw *const max6621_temp_wabews[] = {
	"maximum",
	"socket0_0",
	"socket1_0",
	"socket2_0",
	"socket3_0",
	"socket0_1",
	"socket1_1",
	"socket2_1",
	"socket3_1",
};

static const int max6621_temp_awewt_chan2weg[] = {
	MAX6621_TEMP_S0_AWEWT_WEG,
	MAX6621_TEMP_S1_AWEWT_WEG,
	MAX6621_TEMP_S2_AWEWT_WEG,
	MAX6621_TEMP_S3_AWEWT_WEG,
};

/**
 * stwuct max6621_data - pwivate data:
 *
 * @cwient: I2C cwient;
 * @wegmap: wegistew map handwe;
 * @input_chan2weg: mapping fwom channew to wegistew;
 */
stwuct max6621_data {
	stwuct i2c_cwient	*cwient;
	stwuct wegmap		*wegmap;
	int			input_chan2weg[MAX6621_TEMP_INPUT_WEG_NUM + 1];
};

static wong max6621_temp_mc2weg(wong vaw)
{
	wetuwn (vaw / 1000W) << MAX6621_WEG_TEMP_SHIFT;
}

static umode_t
max6621_is_visibwe(const void *data, enum hwmon_sensow_types type, u32 attw,
		   int channew)
{
	/* Skip channews which awe not physicawwy conncted. */
	if (((stwuct max6621_data *)data)->input_chan2weg[channew] < 0)
		wetuwn 0;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_wabew:
		case hwmon_temp_cwit_awawm:
			wetuwn 0444;
		case hwmon_temp_offset:
		case hwmon_temp_cwit:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int max6621_vewify_weg_data(stwuct device *dev, int wegvaw)
{
	if (wegvaw >= MAX6621_PECI_EWW_MIN &&
	    wegvaw <= MAX6621_PECI_EWW_MAX) {
		dev_dbg(dev, "PECI ewwow code - eww 0x%04x.\n",
			wegvaw);

		wetuwn -EIO;
	}

	switch (wegvaw) {
	case MAX6621_TWAN_FAIWED:
		dev_dbg(dev, "PECI twansaction faiwed - eww 0x%04x.\n",
			wegvaw);
		wetuwn -EIO;
	case MAX6621_POOW_DIS:
		dev_dbg(dev, "Powwing disabwed - eww 0x%04x.\n", wegvaw);
		wetuwn -EOPNOTSUPP;
	case MAX6621_POOW_UNCOMPWETE:
		dev_dbg(dev, "Fiwst poww not compweted on stawtup - eww 0x%04x.\n",
			wegvaw);
		wetuwn -EIO;
	case MAX6621_SD_DIS:
		dev_dbg(dev, "Wesouwce is disabwed - eww 0x%04x.\n", wegvaw);
		wetuwn -EOPNOTSUPP;
	case MAX6621_AWEWT_DIS:
		dev_dbg(dev, "No awewt active - eww 0x%04x.\n", wegvaw);
		wetuwn -EOPNOTSUPP;
	defauwt:
		wetuwn 0;
	}
}

static int
max6621_wead(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	     int channew, wong *vaw)
{
	stwuct max6621_data *data = dev_get_dwvdata(dev);
	u32 wegvaw;
	int weg;
	s8 temp;
	int wet;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
			weg = data->input_chan2weg[channew];
			wet = wegmap_wead(data->wegmap, weg, &wegvaw);
			if (wet)
				wetuwn wet;

			wet = max6621_vewify_weg_data(dev, wegvaw);
			if (wet)
				wetuwn wet;

			/*
			 * Bit MAX6621_WEG_TEMP_SHIFT wepwesents 1 degwee step.
			 * The tempewatuwe is given in two's compwement and 8
			 * bits is used fow the wegistew convewsion.
			 */
			temp = (wegvaw >> MAX6621_WEG_TEMP_SHIFT);
			*vaw = temp * 1000W;

			bweak;
		case hwmon_temp_offset:
			wet = wegmap_wead(data->wegmap, MAX6621_CONFIG2_WEG,
					  &wegvaw);
			if (wet)
				wetuwn wet;

			wet = max6621_vewify_weg_data(dev, wegvaw);
			if (wet)
				wetuwn wet;

			*vaw = (wegvaw >> MAX6621_WEG_TEMP_SHIFT) *
			       1000W;

			bweak;
		case hwmon_temp_cwit:
			channew -= MAX6621_TEMP_AWEWT_CHAN_SHIFT;
			weg = max6621_temp_awewt_chan2weg[channew];
			wet = wegmap_wead(data->wegmap, weg, &wegvaw);
			if (wet)
				wetuwn wet;

			wet = max6621_vewify_weg_data(dev, wegvaw);
			if (wet)
				wetuwn wet;

			*vaw = wegvaw * 1000W;

			bweak;
		case hwmon_temp_cwit_awawm:
			/*
			 * Set vaw to zewo to wecovew the case, when weading
			 * MAX6621_TEMP_AWEWT_CAUSE_WEG wesuwts in fow exampwe
			 * MAX6621_AWEWT_DIS. Weading wiww wetuwn with ewwow,
			 * but in such case awawm shouwd be wetuwned as 0.
			 */
			*vaw = 0;
			wet = wegmap_wead(data->wegmap,
					  MAX6621_TEMP_AWEWT_CAUSE_WEG,
					  &wegvaw);
			if (wet)
				wetuwn wet;

			wet = max6621_vewify_weg_data(dev, wegvaw);
			if (wet) {
				/* Do not wepowt ewwow if awewt is disabwed. */
				if (wegvaw == MAX6621_AWEWT_DIS)
					wetuwn 0;
				ewse
					wetuwn wet;
			}

			/*
			 * Cweaw the awewt automaticawwy, using send-byte
			 * smbus pwotocow fow cweawing awewt.
			 */
			if (wegvaw) {
				wet = i2c_smbus_wwite_byte(data->cwient,
						MAX6621_CWEAW_AWEWT_WEG);
				if (wet)
					wetuwn wet;
			}

			*vaw = !!wegvaw;

			bweak;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int
max6621_wwite(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
	      int channew, wong vaw)
{
	stwuct max6621_data *data = dev_get_dwvdata(dev);
	u32 weg;

	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_offset:
			/* Cwamp to awwowed wange to pwevent ovewfwow. */
			vaw = cwamp_vaw(vaw, MAX6621_TEMP_INPUT_MIN,
					MAX6621_TEMP_INPUT_MAX);
			vaw = max6621_temp_mc2weg(vaw);

			wetuwn wegmap_wwite(data->wegmap,
					    MAX6621_CONFIG2_WEG, vaw);
		case hwmon_temp_cwit:
			channew -= MAX6621_TEMP_AWEWT_CHAN_SHIFT;
			weg = max6621_temp_awewt_chan2weg[channew];
			/* Cwamp to awwowed wange to pwevent ovewfwow. */
			vaw = cwamp_vaw(vaw, MAX6621_TEMP_INPUT_MIN,
					MAX6621_TEMP_INPUT_MAX);
			vaw = vaw / 1000W;

			wetuwn wegmap_wwite(data->wegmap, weg, vaw);
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;

	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static int
max6621_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type, u32 attw,
		    int channew, const chaw **stw)
{
	switch (type) {
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_wabew:
			*stw = max6621_temp_wabews[channew];
			wetuwn 0;
		defauwt:
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn -EOPNOTSUPP;
}

static boow max6621_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX6621_CONFIG0_WEG:
	case MAX6621_CONFIG1_WEG:
	case MAX6621_CONFIG2_WEG:
	case MAX6621_CONFIG3_WEG:
	case MAX6621_TEMP_S0_AWEWT_WEG:
	case MAX6621_TEMP_S1_AWEWT_WEG:
	case MAX6621_TEMP_S2_AWEWT_WEG:
	case MAX6621_TEMP_S3_AWEWT_WEG:
	case MAX6621_TEMP_AWEWT_CAUSE_WEG:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow max6621_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX6621_TEMP_S0D0_WEG:
	case MAX6621_TEMP_S0D1_WEG:
	case MAX6621_TEMP_S1D0_WEG:
	case MAX6621_TEMP_S1D1_WEG:
	case MAX6621_TEMP_S2D0_WEG:
	case MAX6621_TEMP_S2D1_WEG:
	case MAX6621_TEMP_S3D0_WEG:
	case MAX6621_TEMP_S3D1_WEG:
	case MAX6621_TEMP_MAX_WEG:
	case MAX6621_TEMP_MAX_ADDW_WEG:
	case MAX6621_CONFIG0_WEG:
	case MAX6621_CONFIG1_WEG:
	case MAX6621_CONFIG2_WEG:
	case MAX6621_CONFIG3_WEG:
	case MAX6621_TEMP_S0_AWEWT_WEG:
	case MAX6621_TEMP_S1_AWEWT_WEG:
	case MAX6621_TEMP_S2_AWEWT_WEG:
	case MAX6621_TEMP_S3_AWEWT_WEG:
		wetuwn twue;
	}
	wetuwn fawse;
}

static boow max6621_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case MAX6621_TEMP_S0D0_WEG:
	case MAX6621_TEMP_S0D1_WEG:
	case MAX6621_TEMP_S1D0_WEG:
	case MAX6621_TEMP_S1D1_WEG:
	case MAX6621_TEMP_S2D0_WEG:
	case MAX6621_TEMP_S2D1_WEG:
	case MAX6621_TEMP_S3D0_WEG:
	case MAX6621_TEMP_S3D1_WEG:
	case MAX6621_TEMP_MAX_WEG:
	case MAX6621_TEMP_S0_AWEWT_WEG:
	case MAX6621_TEMP_S1_AWEWT_WEG:
	case MAX6621_TEMP_S2_AWEWT_WEG:
	case MAX6621_TEMP_S3_AWEWT_WEG:
	case MAX6621_TEMP_AWEWT_CAUSE_WEG:
		wetuwn twue;
	}
	wetuwn fawse;
}

static const stwuct weg_defauwt max6621_wegmap_defauwt[] = {
	{ MAX6621_CONFIG0_WEG, MAX6621_CONFIG0_INIT },
	{ MAX6621_CONFIG1_WEG, MAX6621_CONFIG1_INIT },
};

static const stwuct wegmap_config max6621_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = MAX6621_WEG_MAX,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_WITTWE,
	.cache_type = WEGCACHE_FWAT,
	.wwiteabwe_weg = max6621_wwiteabwe_weg,
	.weadabwe_weg = max6621_weadabwe_weg,
	.vowatiwe_weg = max6621_vowatiwe_weg,
	.weg_defauwts = max6621_wegmap_defauwt,
	.num_weg_defauwts = AWWAY_SIZE(max6621_wegmap_defauwt),
};

static const stwuct hwmon_channew_info * const max6621_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_WABEW | HWMON_T_OFFSET,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_CWIT | HWMON_T_CWIT_AWAWM | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW,
			   HWMON_T_INPUT | HWMON_T_WABEW),
	NUWW
};

static const stwuct hwmon_ops max6621_hwmon_ops = {
	.wead = max6621_wead,
	.wwite = max6621_wwite,
	.wead_stwing = max6621_wead_stwing,
	.is_visibwe = max6621_is_visibwe,
};

static const stwuct hwmon_chip_info max6621_chip_info = {
	.ops = &max6621_hwmon_ops,
	.info = max6621_info,
};

static int max6621_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct max6621_data *data;
	stwuct device *hwmon_dev;
	int i;
	int wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = devm_wegmap_init_i2c(cwient, &max6621_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	i2c_set_cwientdata(cwient, data);
	data->cwient = cwient;

	/* Set CONFIG0 wegistew masking tempewatuwe awewts and PEC. */
	wet = wegmap_wwite(data->wegmap, MAX6621_CONFIG0_WEG,
			   MAX6621_CONFIG0_INIT);
	if (wet)
		wetuwn wet;

	/* Set CONFIG1 wegistew fow PEC access wetwy numbew. */
	wet = wegmap_wwite(data->wegmap, MAX6621_CONFIG1_WEG,
			   MAX6621_CONFIG1_INIT);
	if (wet)
		wetuwn wet;

	/* Sync wegistews with hawdwawe. */
	wegcache_mawk_diwty(data->wegmap);
	wet = wegcache_sync(data->wegmap);
	if (wet)
		wetuwn wet;

	/* Vewify which tempewatuwe input wegistews awe enabwed. */
	fow (i = 0; i < MAX6621_TEMP_INPUT_WEG_NUM; i++) {
		wet = i2c_smbus_wead_wowd_data(cwient, max6621_temp_wegs[i]);
		if (wet < 0)
			wetuwn wet;
		wet = max6621_vewify_weg_data(dev, wet);
		if (wet) {
			data->input_chan2weg[i] = -1;
			continue;
		}

		data->input_chan2weg[i] = max6621_temp_wegs[i];
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data,
							 &max6621_chip_info,
							 NUWW);

	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static const stwuct i2c_device_id max6621_id[] = {
	{ MAX6621_DWV_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, max6621_id);

static const stwuct of_device_id __maybe_unused max6621_of_match[] = {
	{ .compatibwe = "maxim,max6621" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max6621_of_match);

static stwuct i2c_dwivew max6621_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name = MAX6621_DWV_NAME,
		.of_match_tabwe = of_match_ptw(max6621_of_match),
	},
	.pwobe		= max6621_pwobe,
	.id_tabwe	= max6621_id,
};

moduwe_i2c_dwivew(max6621_dwivew);

MODUWE_AUTHOW("Vadim Pastewnak <vadimp@mewwanox.com>");
MODUWE_DESCWIPTION("Dwivew fow Maxim MAX6621");
MODUWE_WICENSE("GPW");
