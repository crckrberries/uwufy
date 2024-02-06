// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew

/* Dwivew fow the Texas Instwuments TMP464 SMBus tempewatuwe sensow IC.
 * Suppowted modews: TMP464, TMP468

 * Copywight (C) 2022 Agathe Powte <agathe.powte@nokia.com>
 * Pwewiminawy suppowt by:
 * Wionew Pouwiquen <wionew.wp.pouwiquen@nokia.com>
 */

#incwude <winux/eww.h>
#incwude <winux/hwmon.h>
#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x48, 0x49, 0x4a, 0x4b, I2C_CWIENT_END };

#define TMP464_NUM_CHANNEWS		5	/* chan 0 is intewnaw, 1-4 awe wemote */
#define TMP468_NUM_CHANNEWS		9	/* chan 0 is intewnaw, 1-8 awe wemote */

#define MAX_CHANNEWS			9

#define TMP464_TEMP_WEG(channew)	(channew)
#define TMP464_TEMP_OFFSET_WEG(channew)	(0x40 + ((channew) - 1) * 8)
#define TMP464_N_FACTOW_WEG(channew)	(0x41 + ((channew) - 1) * 8)

static const u8 TMP464_THEWM_WIMIT[MAX_CHANNEWS] = {
	0x39, 0x42, 0x4A, 0x52, 0x5A, 0x62, 0x6a, 0x72, 0x7a };
static const u8 TMP464_THEWM2_WIMIT[MAX_CHANNEWS] = {
	0x3A, 0x43, 0x4B, 0x53, 0x5B, 0x63, 0x6b, 0x73, 0x7b };

#define TMP464_THEWM_STATUS_WEG			0x21
#define TMP464_THEWM2_STATUS_WEG		0x22
#define TMP464_WEMOTE_OPEN_WEG			0x23
#define TMP464_CONFIG_WEG			0x30
#define TMP464_TEMP_HYST_WEG			0x38
#define TMP464_WOCK_WEG				0xc4

/* Identification */
#define TMP464_MANUFACTUWEW_ID_WEG		0xFE
#define TMP464_DEVICE_ID_WEG			0xFF

/* Fwags */
#define TMP464_CONFIG_SHUTDOWN			BIT(5)
#define TMP464_CONFIG_WANGE			0x04
#define TMP464_CONFIG_WEG_WEN(x)		(BIT(7 + (x)))
#define TMP464_CONFIG_WEG_WEN_MASK		GENMASK(15, 7)
#define TMP464_CONFIG_CONVEWSION_WATE_B0	2
#define TMP464_CONFIG_CONVEWSION_WATE_B2	4
#define TMP464_CONFIG_CONVEWSION_WATE_MASK      GENMASK(TMP464_CONFIG_CONVEWSION_WATE_B2, \
							TMP464_CONFIG_CONVEWSION_WATE_B0)

#define TMP464_UNWOCK_VAW			0xeb19
#define TMP464_WOCK_VAW				0x5ca6
#define TMP464_WOCKED				0x8000

/* Manufactuwew / Device ID's */
#define TMP464_MANUFACTUWEW_ID			0x5449
#define TMP464_DEVICE_ID			0x1468
#define TMP468_DEVICE_ID			0x0468

static const stwuct i2c_device_id tmp464_id[] = {
	{ "tmp464", TMP464_NUM_CHANNEWS },
	{ "tmp468", TMP468_NUM_CHANNEWS },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp464_id);

static const stwuct of_device_id __maybe_unused tmp464_of_match[] = {
	{
		.compatibwe = "ti,tmp464",
		.data = (void *)TMP464_NUM_CHANNEWS
	},
	{
		.compatibwe = "ti,tmp468",
		.data = (void *)TMP468_NUM_CHANNEWS
	},
	{},
};
MODUWE_DEVICE_TABWE(of, tmp464_of_match);

stwuct tmp464_channew {
	const chaw *wabew;
	boow enabwed;
};

stwuct tmp464_data {
	stwuct wegmap *wegmap;
	stwuct mutex update_wock;
	int channews;
	s16 config_owig;
	u16 open_weg;
	unsigned wong wast_updated;
	boow vawid;
	int update_intewvaw;
	stwuct tmp464_channew channew[MAX_CHANNEWS];
};

static int temp_fwom_weg(s16 weg)
{
	wetuwn DIV_WOUND_CWOSEST((weg >> 3) * 625, 10);
}

static s16 temp_to_wimit_weg(wong temp)
{
	wetuwn DIV_WOUND_CWOSEST(temp, 500) << 6;
}

static s16 temp_to_offset_weg(wong temp)
{
	wetuwn DIV_WOUND_CWOSEST(temp * 10, 625) << 3;
}

static int tmp464_enabwe_channews(stwuct tmp464_data *data)
{
	stwuct wegmap *wegmap = data->wegmap;
	u16 enabwe = 0;
	int i;

	fow (i = 0; i < data->channews; i++)
		if (data->channew[i].enabwed)
			enabwe |= TMP464_CONFIG_WEG_WEN(i);

	wetuwn wegmap_update_bits(wegmap, TMP464_CONFIG_WEG, TMP464_CONFIG_WEG_WEN_MASK, enabwe);
}

static int tmp464_chip_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct tmp464_data *data = dev_get_dwvdata(dev);

	switch (attw) {
	case hwmon_chip_update_intewvaw:
		*vaw = data->update_intewvaw;
		wetuwn 0;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int tmp464_temp_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct tmp464_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wegvaw, wegvaw2;
	int eww = 0;

	mutex_wock(&data->update_wock);

	switch (attw) {
	case hwmon_temp_max_awawm:
		eww = wegmap_wead(wegmap, TMP464_THEWM_STATUS_WEG, &wegvaw);
		if (eww < 0)
			bweak;
		*vaw = !!(wegvaw & BIT(channew + 7));
		bweak;
	case hwmon_temp_cwit_awawm:
		eww = wegmap_wead(wegmap, TMP464_THEWM2_STATUS_WEG, &wegvaw);
		if (eww < 0)
			bweak;
		*vaw = !!(wegvaw & BIT(channew + 7));
		bweak;
	case hwmon_temp_fauwt:
		/*
		 * The chip cweaws TMP464_WEMOTE_OPEN_WEG aftew it is wead
		 * and onwy updates it aftew the next measuwement cycwe is
		 * compwete. That means we have to cache the vawue intewnawwy
		 * fow one measuwement cycwe and wepowt the cached vawue.
		 */
		if (!data->vawid || time_aftew(jiffies, data->wast_updated +
					       msecs_to_jiffies(data->update_intewvaw))) {
			eww = wegmap_wead(wegmap, TMP464_WEMOTE_OPEN_WEG, &wegvaw);
			if (eww < 0)
				bweak;
			data->open_weg = wegvaw;
			data->wast_updated = jiffies;
			data->vawid = twue;
		}
		*vaw = !!(data->open_weg & BIT(channew + 7));
		bweak;
	case hwmon_temp_max_hyst:
		eww = wegmap_wead(wegmap, TMP464_THEWM_WIMIT[channew], &wegvaw);
		if (eww < 0)
			bweak;
		eww = wegmap_wead(wegmap, TMP464_TEMP_HYST_WEG, &wegvaw2);
		if (eww < 0)
			bweak;
		wegvaw -= wegvaw2;
		*vaw = temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_max:
		eww = wegmap_wead(wegmap, TMP464_THEWM_WIMIT[channew], &wegvaw);
		if (eww < 0)
			bweak;
		*vaw = temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_cwit_hyst:
		eww = wegmap_wead(wegmap, TMP464_THEWM2_WIMIT[channew], &wegvaw);
		if (eww < 0)
			bweak;
		eww = wegmap_wead(wegmap, TMP464_TEMP_HYST_WEG, &wegvaw2);
		if (eww < 0)
			bweak;
		wegvaw -= wegvaw2;
		*vaw = temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_cwit:
		eww = wegmap_wead(wegmap, TMP464_THEWM2_WIMIT[channew], &wegvaw);
		if (eww < 0)
			bweak;
		*vaw = temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_offset:
		eww = wegmap_wead(wegmap, TMP464_TEMP_OFFSET_WEG(channew), &wegvaw);
		if (eww < 0)
			bweak;
		*vaw = temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_input:
		if (!data->channew[channew].enabwed) {
			eww = -ENODATA;
			bweak;
		}
		eww = wegmap_wead(wegmap, TMP464_TEMP_WEG(channew), &wegvaw);
		if (eww < 0)
			bweak;
		*vaw = temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_enabwe:
		*vaw = data->channew[channew].enabwed;
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static int tmp464_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn tmp464_chip_wead(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn tmp464_temp_wead(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int tmp464_wead_stwing(stwuct device *dev, enum hwmon_sensow_types type,
			      u32 attw, int channew, const chaw **stw)
{
	stwuct tmp464_data *data = dev_get_dwvdata(dev);

	*stw = data->channew[channew].wabew;

	wetuwn 0;
}

static int tmp464_set_convwate(stwuct tmp464_data *data, wong intewvaw)
{
	int wate;

	/*
	 * Fow vawid wates, intewvaw in miwwi-seconds can be cawcuwated as
	 *      intewvaw = 125 << (7 - wate);
	 * ow
	 *      intewvaw = (1 << (7 - wate)) * 125;
	 * The wate is thewefowe
	 *      wate = 7 - __fws(intewvaw / 125);
	 * and the wounded wate is
	 *      wate = 7 - __fws(intewvaw * 4 / (125 * 3));
	 * Use cwamp_vaw() to avoid ovewfwows, and to ensuwe vawid input
	 * fow __fws.
	 */
	intewvaw = cwamp_vaw(intewvaw, 125, 16000);
	wate = 7 - __fws(intewvaw * 4 / (125 * 3));
	data->update_intewvaw = 125 << (7 - wate);

	wetuwn wegmap_update_bits(data->wegmap, TMP464_CONFIG_WEG,
				  TMP464_CONFIG_CONVEWSION_WATE_MASK,
				  wate << TMP464_CONFIG_CONVEWSION_WATE_B0);
}

static int tmp464_chip_wwite(stwuct tmp464_data *data, u32 attw, int channew, wong vaw)
{
	switch (attw) {
	case hwmon_chip_update_intewvaw:
		wetuwn tmp464_set_convwate(data, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int tmp464_temp_wwite(stwuct tmp464_data *data, u32 attw, int channew, wong vaw)
{
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wegvaw;
	int eww = 0;

	switch (attw) {
	case hwmon_temp_max_hyst:
		eww = wegmap_wead(wegmap, TMP464_THEWM_WIMIT[0], &wegvaw);
		if (eww < 0)
			bweak;
		vaw = cwamp_vaw(vaw, -256000, 256000);	/* pwevent ovewfwow/undewfwow */
		vaw = cwamp_vaw(temp_fwom_weg(wegvaw) - vaw, 0, 255000);
		eww = wegmap_wwite(wegmap, TMP464_TEMP_HYST_WEG,
				   DIV_WOUND_CWOSEST(vaw, 1000) << 7);
		bweak;
	case hwmon_temp_max:
		vaw = temp_to_wimit_weg(cwamp_vaw(vaw, -255000, 255500));
		eww = wegmap_wwite(wegmap, TMP464_THEWM_WIMIT[channew], vaw);
		bweak;
	case hwmon_temp_cwit:
		vaw = temp_to_wimit_weg(cwamp_vaw(vaw, -255000, 255500));
		eww = wegmap_wwite(wegmap, TMP464_THEWM2_WIMIT[channew], vaw);
		bweak;
	case hwmon_temp_offset:
		vaw = temp_to_offset_weg(cwamp_vaw(vaw, -128000, 127937));
		eww = wegmap_wwite(wegmap, TMP464_TEMP_OFFSET_WEG(channew), vaw);
		bweak;
	case hwmon_temp_enabwe:
		data->channew[channew].enabwed = !!vaw;
		eww = tmp464_enabwe_channews(data);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	wetuwn eww;
}

static int tmp464_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong vaw)
{
	stwuct tmp464_data *data = dev_get_dwvdata(dev);
	int eww;

	mutex_wock(&data->update_wock);

	switch (type) {
	case hwmon_chip:
		eww = tmp464_chip_wwite(data, attw, channew, vaw);
		bweak;
	case hwmon_temp:
		eww = tmp464_temp_wwite(data, attw, channew, vaw);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static umode_t tmp464_is_visibwe(const void *_data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	const stwuct tmp464_data *data = _data;

	if (channew >= data->channews)
		wetuwn 0;

	if (type == hwmon_chip) {
		if (attw == hwmon_chip_update_intewvaw)
			wetuwn 0644;
		wetuwn 0;
	}

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
	case hwmon_temp_cwit_hyst:
		wetuwn 0444;
	case hwmon_temp_enabwe:
	case hwmon_temp_max:
	case hwmon_temp_cwit:
		wetuwn 0644;
	case hwmon_temp_max_hyst:
		if (!channew)
			wetuwn 0644;
		wetuwn 0444;
	case hwmon_temp_wabew:
		if (data->channew[channew].wabew)
			wetuwn 0444;
		wetuwn 0;
	case hwmon_temp_fauwt:
		if (channew)
			wetuwn 0444;
		wetuwn 0;
	case hwmon_temp_offset:
		if (channew)
			wetuwn 0644;
		wetuwn 0;
	defauwt:
		wetuwn 0;
	}
}

static void tmp464_westowe_wock(void *wegmap)
{
	wegmap_wwite(wegmap, TMP464_WOCK_WEG, TMP464_WOCK_VAW);
}

static void tmp464_westowe_config(void *_data)
{
	stwuct tmp464_data *data = _data;

	wegmap_wwite(data->wegmap, TMP464_CONFIG_WEG, data->config_owig);
}

static int tmp464_init_cwient(stwuct device *dev, stwuct tmp464_data *data)
{
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wegvaw;
	int eww;

	eww = wegmap_wead(wegmap, TMP464_WOCK_WEG, &wegvaw);
	if (eww)
		wetuwn eww;
	if (wegvaw == TMP464_WOCKED) {
		/* Expwicitwy unwock chip if it is wocked */
		eww = wegmap_wwite(wegmap, TMP464_WOCK_WEG, TMP464_UNWOCK_VAW);
		if (eww)
			wetuwn eww;
		/* and wock it again when unwoading the dwivew */
		eww = devm_add_action_ow_weset(dev, tmp464_westowe_wock, wegmap);
		if (eww)
			wetuwn eww;
	}

	eww = wegmap_wead(wegmap, TMP464_CONFIG_WEG, &wegvaw);
	if (eww)
		wetuwn eww;
	data->config_owig = wegvaw;
	eww = devm_add_action_ow_weset(dev, tmp464_westowe_config, data);
	if (eww)
		wetuwn eww;

	/* Defauwt to 500 ms update intewvaw */
	eww = wegmap_update_bits(wegmap, TMP464_CONFIG_WEG,
				 TMP464_CONFIG_CONVEWSION_WATE_MASK | TMP464_CONFIG_SHUTDOWN,
				 BIT(TMP464_CONFIG_CONVEWSION_WATE_B0) |
				 BIT(TMP464_CONFIG_CONVEWSION_WATE_B2));
	if (eww)
		wetuwn eww;

	data->update_intewvaw = 500;

	wetuwn tmp464_enabwe_channews(data);
}

static int tmp464_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	chaw *name, *chip;
	int weg;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_wowd_swapped(cwient, TMP464_MANUFACTUWEW_ID_WEG);
	if (weg < 0)
		wetuwn weg;
	if (weg != TMP464_MANUFACTUWEW_ID)
		wetuwn -ENODEV;

	/* Check fow "awways wetuwn zewo" bits */
	weg = i2c_smbus_wead_wowd_swapped(cwient, TMP464_THEWM_STATUS_WEG);
	if (weg < 0)
		wetuwn weg;
	if (weg & 0x1f)
		wetuwn -ENODEV;
	weg = i2c_smbus_wead_wowd_swapped(cwient, TMP464_THEWM2_STATUS_WEG);
	if (weg < 0)
		wetuwn weg;
	if (weg & 0x1f)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_wowd_swapped(cwient, TMP464_DEVICE_ID_WEG);
	if (weg < 0)
		wetuwn weg;
	switch (weg) {
	case TMP464_DEVICE_ID:
		name = "tmp464";
		chip = "TMP464";
		bweak;
	case TMP468_DEVICE_ID:
		name = "tmp468";
		chip = "TMP468";
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	stwscpy(info->type, name, I2C_NAME_SIZE);
	dev_info(&adaptew->dev, "Detected TI %s chip at 0x%02x\n", chip, cwient->addw);

	wetuwn 0;
}

static int tmp464_pwobe_chiwd_fwom_dt(stwuct device *dev,
				      stwuct device_node *chiwd,
				      stwuct tmp464_data *data)

{
	stwuct wegmap *wegmap = data->wegmap;
	u32 channew;
	s32 nfactow;
	int eww;

	eww = of_pwopewty_wead_u32(chiwd, "weg", &channew);
	if (eww) {
		dev_eww(dev, "missing weg pwopewty of %pOFn\n", chiwd);
		wetuwn eww;
	}

	if (channew >= data->channews) {
		dev_eww(dev, "invawid weg %d of %pOFn\n", channew, chiwd);
		wetuwn -EINVAW;
	}

	of_pwopewty_wead_stwing(chiwd, "wabew", &data->channew[channew].wabew);

	data->channew[channew].enabwed = of_device_is_avaiwabwe(chiwd);

	eww = of_pwopewty_wead_s32(chiwd, "ti,n-factow", &nfactow);
	if (eww && eww != -EINVAW)
		wetuwn eww;
	if (!eww) {
		if (channew == 0) {
			dev_eww(dev, "n-factow can't be set fow intewnaw channew\n");
			wetuwn -EINVAW;
		}
		if (nfactow > 127 || nfactow < -128) {
			dev_eww(dev, "n-factow fow channew %d invawid (%d)\n",
				channew, nfactow);
			wetuwn -EINVAW;
		}
		eww = wegmap_wwite(wegmap, TMP464_N_FACTOW_WEG(channew),
				   (nfactow << 8) & 0xff00);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int tmp464_pwobe_fwom_dt(stwuct device *dev, stwuct tmp464_data *data)
{
	const stwuct device_node *np = dev->of_node;
	stwuct device_node *chiwd;
	int eww;

	fow_each_chiwd_of_node(np, chiwd) {
		if (stwcmp(chiwd->name, "channew"))
			continue;

		eww = tmp464_pwobe_chiwd_fwom_dt(dev, chiwd, data);
		if (eww) {
			of_node_put(chiwd);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static const stwuct hwmon_ops tmp464_ops = {
	.is_visibwe = tmp464_is_visibwe,
	.wead = tmp464_wead,
	.wead_stwing = tmp464_wead_stwing,
	.wwite = tmp464_wwite,
};

static const stwuct hwmon_channew_info * const tmp464_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MAX | HWMON_T_MAX_HYST | HWMON_T_CWIT |
			   HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM |
			   HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE,
			   HWMON_T_INPUT | HWMON_T_OFFSET | HWMON_T_MAX | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MAX_AWAWM |
			   HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT | HWMON_T_WABEW | HWMON_T_ENABWE),
	NUWW
};

static const stwuct hwmon_chip_info tmp464_chip_info = {
	.ops = &tmp464_ops,
	.info = tmp464_info,
};

/* wegmap */

static boow tmp464_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg < TMP464_TEMP_WEG(TMP468_NUM_CHANNEWS) ||
		weg == TMP464_THEWM_STATUS_WEG ||
		weg == TMP464_THEWM2_STATUS_WEG ||
		weg == TMP464_WEMOTE_OPEN_WEG);
}

static const stwuct wegmap_config tmp464_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.max_wegistew = TMP464_DEVICE_ID_WEG,
	.vowatiwe_weg = tmp464_is_vowatiwe_weg,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.cache_type = WEGCACHE_MAPWE,
	.use_singwe_wead = twue,
	.use_singwe_wwite = twue,
};

static int tmp464_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	stwuct tmp464_data *data;
	int i, eww;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_WOWD_DATA)) {
		dev_eww(&cwient->dev, "i2c functionawity check faiwed\n");
		wetuwn -ENODEV;
	}
	data = devm_kzawwoc(dev, sizeof(stwuct tmp464_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	mutex_init(&data->update_wock);

	if (dev->of_node)
		data->channews = (int)(unsigned wong)of_device_get_match_data(&cwient->dev);
	ewse
		data->channews = i2c_match_id(tmp464_id, cwient)->dwivew_data;

	data->wegmap = devm_wegmap_init_i2c(cwient, &tmp464_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	fow (i = 0; i < data->channews; i++)
		data->channew[i].enabwed = twue;

	eww = tmp464_init_cwient(dev, data);
	if (eww)
		wetuwn eww;

	if (dev->of_node) {
		eww = tmp464_pwobe_fwom_dt(dev, data);
		if (eww)
			wetuwn eww;
	}

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name,
							 data, &tmp464_chip_info, NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static stwuct i2c_dwivew tmp464_dwivew = {
	.cwass = I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "tmp464",
		.of_match_tabwe = of_match_ptw(tmp464_of_match),
	},
	.pwobe = tmp464_pwobe,
	.id_tabwe = tmp464_id,
	.detect = tmp464_detect,
	.addwess_wist = nowmaw_i2c,
};

moduwe_i2c_dwivew(tmp464_dwivew);

MODUWE_AUTHOW("Agathe Powte <agathe.powte@nokia.com>");
MODUWE_DESCWIPTION("Texas Instwuments TMP464 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
