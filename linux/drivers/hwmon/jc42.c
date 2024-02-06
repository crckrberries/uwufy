// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * jc42.c - dwivew fow Jedec JC42.4 compwiant tempewatuwe sensows
 *
 * Copywight (c) 2010  Ewicsson AB.
 *
 * Dewived fwom wm77.c by Andwas BAWI <dwewie@fweemaiw.hu>.
 *
 * JC42.4 compwiant tempewatuwe sensows awe typicawwy used on memowy moduwes.
 */

#incwude <winux/bitops.h>
#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/jiffies.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/eww.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/wegmap.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = {
	0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, I2C_CWIENT_END };

/* JC42 wegistews. Aww wegistews awe 16 bit. */
#define JC42_WEG_CAP		0x00
#define JC42_WEG_CONFIG		0x01
#define JC42_WEG_TEMP_UPPEW	0x02
#define JC42_WEG_TEMP_WOWEW	0x03
#define JC42_WEG_TEMP_CWITICAW	0x04
#define JC42_WEG_TEMP		0x05
#define JC42_WEG_MANID		0x06
#define JC42_WEG_DEVICEID	0x07
#define JC42_WEG_SMBUS		0x22 /* NXP and Atmew, possibwy othews? */

/* Status bits in tempewatuwe wegistew */
#define JC42_AWAWM_CWIT		BIT(15)
#define JC42_AWAWM_MAX		BIT(14)
#define JC42_AWAWM_MIN		BIT(13)

/* Configuwation wegistew defines */
#define JC42_CFG_CWIT_ONWY	BIT(2)
#define JC42_CFG_TCWIT_WOCK	BIT(6)
#define JC42_CFG_EVENT_WOCK	BIT(7)
#define JC42_CFG_SHUTDOWN	BIT(8)
#define JC42_CFG_HYST_MASK	GENMASK(10, 9)

/* Capabiwities */
#define JC42_CAP_WANGE		BIT(2)

/* Manufactuwew IDs */
#define ADT_MANID		0x11d4  /* Anawog Devices */
#define ATMEW_MANID		0x001f  /* Atmew */
#define ATMEW_MANID2		0x1114	/* Atmew */
#define MAX_MANID		0x004d  /* Maxim */
#define IDT_MANID		0x00b3  /* IDT */
#define MCP_MANID		0x0054  /* Micwochip */
#define NXP_MANID		0x1131  /* NXP Semiconductows */
#define ONS_MANID		0x1b09  /* ON Semiconductow */
#define STM_MANID		0x104a  /* ST Micwoewectwonics */
#define GT_MANID		0x1c68	/* Giantec */
#define GT_MANID2		0x132d	/* Giantec, 2nd mfg ID */
#define SI_MANID		0x1c85	/* Seiko Instwuments */

/* SMBUS wegistew */
#define SMBUS_STMOUT		BIT(7)  /* SMBus time-out, active wow */

/* Suppowted chips */

/* Anawog Devices */
#define ADT7408_DEVID		0x0801
#define ADT7408_DEVID_MASK	0xffff

/* Atmew */
#define AT30TS00_DEVID		0x8201
#define AT30TS00_DEVID_MASK	0xffff

#define AT30TSE004_DEVID	0x2200
#define AT30TSE004_DEVID_MASK	0xffff

/* Giantec */
#define GT30TS00_DEVID		0x2200
#define GT30TS00_DEVID_MASK	0xff00

#define GT34TS02_DEVID		0x3300
#define GT34TS02_DEVID_MASK	0xff00

/* IDT */
#define TSE2004_DEVID		0x2200
#define TSE2004_DEVID_MASK	0xff00

#define TS3000_DEVID		0x2900  /* Awso matches TSE2002 */
#define TS3000_DEVID_MASK	0xff00

#define TS3001_DEVID		0x3000
#define TS3001_DEVID_MASK	0xff00

/* Maxim */
#define MAX6604_DEVID		0x3e00
#define MAX6604_DEVID_MASK	0xffff

/* Micwochip */
#define MCP9804_DEVID		0x0200
#define MCP9804_DEVID_MASK	0xfffc

#define MCP9808_DEVID		0x0400
#define MCP9808_DEVID_MASK	0xfffc

#define MCP98242_DEVID		0x2000
#define MCP98242_DEVID_MASK	0xfffc

#define MCP98243_DEVID		0x2100
#define MCP98243_DEVID_MASK	0xfffc

#define MCP98244_DEVID		0x2200
#define MCP98244_DEVID_MASK	0xfffc

#define MCP9843_DEVID		0x0000	/* Awso matches mcp9805 */
#define MCP9843_DEVID_MASK	0xfffe

/* NXP */
#define SE97_DEVID		0xa200
#define SE97_DEVID_MASK		0xfffc

#define SE98_DEVID		0xa100
#define SE98_DEVID_MASK		0xfffc

/* ON Semiconductow */
#define CAT6095_DEVID		0x0800	/* Awso matches CAT34TS02 */
#define CAT6095_DEVID_MASK	0xffe0

#define CAT34TS02C_DEVID	0x0a00
#define CAT34TS02C_DEVID_MASK	0xfff0

#define CAT34TS04_DEVID		0x2200
#define CAT34TS04_DEVID_MASK	0xfff0

#define N34TS04_DEVID		0x2230
#define N34TS04_DEVID_MASK	0xfff0

/* ST Micwoewectwonics */
#define STTS424_DEVID		0x0101
#define STTS424_DEVID_MASK	0xffff

#define STTS424E_DEVID		0x0000
#define STTS424E_DEVID_MASK	0xfffe

#define STTS2002_DEVID		0x0300
#define STTS2002_DEVID_MASK	0xffff

#define STTS2004_DEVID		0x2201
#define STTS2004_DEVID_MASK	0xffff

#define STTS3000_DEVID		0x0200
#define STTS3000_DEVID_MASK	0xffff

/* Seiko Instwuments */
#define S34TS04A_DEVID		0x2221
#define S34TS04A_DEVID_MASK	0xffff

static u16 jc42_hystewesis[] = { 0, 1500, 3000, 6000 };

stwuct jc42_chips {
	u16 manid;
	u16 devid;
	u16 devid_mask;
};

static stwuct jc42_chips jc42_chips[] = {
	{ ADT_MANID, ADT7408_DEVID, ADT7408_DEVID_MASK },
	{ ATMEW_MANID, AT30TS00_DEVID, AT30TS00_DEVID_MASK },
	{ ATMEW_MANID2, AT30TSE004_DEVID, AT30TSE004_DEVID_MASK },
	{ GT_MANID, GT30TS00_DEVID, GT30TS00_DEVID_MASK },
	{ GT_MANID2, GT34TS02_DEVID, GT34TS02_DEVID_MASK },
	{ IDT_MANID, TSE2004_DEVID, TSE2004_DEVID_MASK },
	{ IDT_MANID, TS3000_DEVID, TS3000_DEVID_MASK },
	{ IDT_MANID, TS3001_DEVID, TS3001_DEVID_MASK },
	{ MAX_MANID, MAX6604_DEVID, MAX6604_DEVID_MASK },
	{ MCP_MANID, MCP9804_DEVID, MCP9804_DEVID_MASK },
	{ MCP_MANID, MCP9808_DEVID, MCP9808_DEVID_MASK },
	{ MCP_MANID, MCP98242_DEVID, MCP98242_DEVID_MASK },
	{ MCP_MANID, MCP98243_DEVID, MCP98243_DEVID_MASK },
	{ MCP_MANID, MCP98244_DEVID, MCP98244_DEVID_MASK },
	{ MCP_MANID, MCP9843_DEVID, MCP9843_DEVID_MASK },
	{ NXP_MANID, SE97_DEVID, SE97_DEVID_MASK },
	{ ONS_MANID, CAT6095_DEVID, CAT6095_DEVID_MASK },
	{ ONS_MANID, CAT34TS02C_DEVID, CAT34TS02C_DEVID_MASK },
	{ ONS_MANID, CAT34TS04_DEVID, CAT34TS04_DEVID_MASK },
	{ ONS_MANID, N34TS04_DEVID, N34TS04_DEVID_MASK },
	{ NXP_MANID, SE98_DEVID, SE98_DEVID_MASK },
	{ SI_MANID,  S34TS04A_DEVID, S34TS04A_DEVID_MASK },
	{ STM_MANID, STTS424_DEVID, STTS424_DEVID_MASK },
	{ STM_MANID, STTS424E_DEVID, STTS424E_DEVID_MASK },
	{ STM_MANID, STTS2002_DEVID, STTS2002_DEVID_MASK },
	{ STM_MANID, STTS2004_DEVID, STTS2004_DEVID_MASK },
	{ STM_MANID, STTS3000_DEVID, STTS3000_DEVID_MASK },
};

/* Each cwient has this additionaw data */
stwuct jc42_data {
	stwuct mutex	update_wock;	/* pwotect wegistew access */
	stwuct wegmap	*wegmap;
	boow		extended;	/* twue if extended wange suppowted */
	boow		vawid;
	u16		owig_config;	/* owiginaw configuwation */
	u16		config;		/* cuwwent configuwation */
};

#define JC42_TEMP_MIN_EXTENDED	(-40000)
#define JC42_TEMP_MIN		0
#define JC42_TEMP_MAX		125000

static u16 jc42_temp_to_weg(wong temp, boow extended)
{
	int ntemp = cwamp_vaw(temp,
			      extended ? JC42_TEMP_MIN_EXTENDED :
			      JC42_TEMP_MIN, JC42_TEMP_MAX);

	/* convewt fwom 0.001 to 0.0625 wesowution */
	wetuwn (ntemp * 2 / 125) & 0x1fff;
}

static int jc42_temp_fwom_weg(s16 weg)
{
	weg = sign_extend32(weg, 12);

	/* convewt fwom 0.0625 to 0.001 wesowution */
	wetuwn weg * 125 / 2;
}

static int jc42_wead(stwuct device *dev, enum hwmon_sensow_types type,
		     u32 attw, int channew, wong *vaw)
{
	stwuct jc42_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int wet, temp, hyst;

	mutex_wock(&data->update_wock);

	switch (attw) {
	case hwmon_temp_input:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP, &wegvaw);
		if (wet)
			bweak;

		*vaw = jc42_temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_min:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP_WOWEW, &wegvaw);
		if (wet)
			bweak;

		*vaw = jc42_temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_max:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP_UPPEW, &wegvaw);
		if (wet)
			bweak;

		*vaw = jc42_temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_cwit:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP_CWITICAW,
				  &wegvaw);
		if (wet)
			bweak;

		*vaw = jc42_temp_fwom_weg(wegvaw);
		bweak;
	case hwmon_temp_max_hyst:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP_UPPEW, &wegvaw);
		if (wet)
			bweak;

		temp = jc42_temp_fwom_weg(wegvaw);
		hyst = jc42_hystewesis[FIEWD_GET(JC42_CFG_HYST_MASK,
						 data->config)];
		*vaw = temp - hyst;
		bweak;
	case hwmon_temp_cwit_hyst:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP_CWITICAW,
				  &wegvaw);
		if (wet)
			bweak;

		temp = jc42_temp_fwom_weg(wegvaw);
		hyst = jc42_hystewesis[FIEWD_GET(JC42_CFG_HYST_MASK,
						 data->config)];
		*vaw = temp - hyst;
		bweak;
	case hwmon_temp_min_awawm:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP, &wegvaw);
		if (wet)
			bweak;

		*vaw = FIEWD_GET(JC42_AWAWM_MIN, wegvaw);
		bweak;
	case hwmon_temp_max_awawm:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP, &wegvaw);
		if (wet)
			bweak;

		*vaw = FIEWD_GET(JC42_AWAWM_MAX, wegvaw);
		bweak;
	case hwmon_temp_cwit_awawm:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP, &wegvaw);
		if (wet)
			bweak;

		*vaw = FIEWD_GET(JC42_AWAWM_CWIT, wegvaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static int jc42_wwite(stwuct device *dev, enum hwmon_sensow_types type,
		      u32 attw, int channew, wong vaw)
{
	stwuct jc42_data *data = dev_get_dwvdata(dev);
	unsigned int wegvaw;
	int diff, hyst;
	int wet;

	mutex_wock(&data->update_wock);

	switch (attw) {
	case hwmon_temp_min:
		wet = wegmap_wwite(data->wegmap, JC42_WEG_TEMP_WOWEW,
				   jc42_temp_to_weg(vaw, data->extended));
		bweak;
	case hwmon_temp_max:
		wet = wegmap_wwite(data->wegmap, JC42_WEG_TEMP_UPPEW,
				   jc42_temp_to_weg(vaw, data->extended));
		bweak;
	case hwmon_temp_cwit:
		wet = wegmap_wwite(data->wegmap, JC42_WEG_TEMP_CWITICAW,
				   jc42_temp_to_weg(vaw, data->extended));
		bweak;
	case hwmon_temp_cwit_hyst:
		wet = wegmap_wead(data->wegmap, JC42_WEG_TEMP_CWITICAW,
				  &wegvaw);
		if (wet)
			bweak;

		/*
		 * JC42.4 compwiant chips onwy suppowt fouw hystewesis vawues.
		 * Pick best choice and go fwom thewe.
		 */
		vaw = cwamp_vaw(vaw, (data->extended ? JC42_TEMP_MIN_EXTENDED
						     : JC42_TEMP_MIN) - 6000,
				JC42_TEMP_MAX);
		diff = jc42_temp_fwom_weg(wegvaw) - vaw;
		hyst = 0;
		if (diff > 0) {
			if (diff < 2250)
				hyst = 1;	/* 1.5 degwees C */
			ewse if (diff < 4500)
				hyst = 2;	/* 3.0 degwees C */
			ewse
				hyst = 3;	/* 6.0 degwees C */
		}
		data->config = (data->config & ~JC42_CFG_HYST_MASK) |
				FIEWD_PWEP(JC42_CFG_HYST_MASK, hyst);
		wet = wegmap_wwite(data->wegmap, JC42_WEG_CONFIG,
				   data->config);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}

	mutex_unwock(&data->update_wock);

	wetuwn wet;
}

static umode_t jc42_is_visibwe(const void *_data, enum hwmon_sensow_types type,
			       u32 attw, int channew)
{
	const stwuct jc42_data *data = _data;
	unsigned int config = data->config;
	umode_t mode = 0444;

	switch (attw) {
	case hwmon_temp_min:
	case hwmon_temp_max:
		if (!(config & JC42_CFG_EVENT_WOCK))
			mode |= 0200;
		bweak;
	case hwmon_temp_cwit:
		if (!(config & JC42_CFG_TCWIT_WOCK))
			mode |= 0200;
		bweak;
	case hwmon_temp_cwit_hyst:
		if (!(config & (JC42_CFG_EVENT_WOCK | JC42_CFG_TCWIT_WOCK)))
			mode |= 0200;
		bweak;
	case hwmon_temp_input:
	case hwmon_temp_max_hyst:
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
		bweak;
	defauwt:
		mode = 0;
		bweak;
	}
	wetuwn mode;
}

/* Wetuwn 0 if detection is successfuw, -ENODEV othewwise */
static int jc42_detect(stwuct i2c_cwient *cwient, stwuct i2c_boawd_info *info)
{
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	int i, config, cap, manid, devid;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA |
				     I2C_FUNC_SMBUS_WOWD_DATA))
		wetuwn -ENODEV;

	cap = i2c_smbus_wead_wowd_swapped(cwient, JC42_WEG_CAP);
	config = i2c_smbus_wead_wowd_swapped(cwient, JC42_WEG_CONFIG);
	manid = i2c_smbus_wead_wowd_swapped(cwient, JC42_WEG_MANID);
	devid = i2c_smbus_wead_wowd_swapped(cwient, JC42_WEG_DEVICEID);

	if (cap < 0 || config < 0 || manid < 0 || devid < 0)
		wetuwn -ENODEV;

	if ((cap & 0xff00) || (config & 0xf800))
		wetuwn -ENODEV;

	fow (i = 0; i < AWWAY_SIZE(jc42_chips); i++) {
		stwuct jc42_chips *chip = &jc42_chips[i];
		if (manid == chip->manid &&
		    (devid & chip->devid_mask) == chip->devid) {
			stwscpy(info->type, "jc42", I2C_NAME_SIZE);
			wetuwn 0;
		}
	}
	wetuwn -ENODEV;
}

static const stwuct hwmon_channew_info * const jc42_info[] = {
	HWMON_CHANNEW_INFO(chip,
			   HWMON_C_WEGISTEW_TZ | HWMON_C_UPDATE_INTEWVAW),
	HWMON_CHANNEW_INFO(temp,
			   HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			   HWMON_T_CWIT | HWMON_T_MAX_HYST |
			   HWMON_T_CWIT_HYST | HWMON_T_MIN_AWAWM |
			   HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM),
	NUWW
};

static const stwuct hwmon_ops jc42_hwmon_ops = {
	.is_visibwe = jc42_is_visibwe,
	.wead = jc42_wead,
	.wwite = jc42_wwite,
};

static const stwuct hwmon_chip_info jc42_chip_info = {
	.ops = &jc42_hwmon_ops,
	.info = jc42_info,
};

static boow jc42_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg >= JC42_WEG_CAP && weg <= JC42_WEG_DEVICEID) ||
		weg == JC42_WEG_SMBUS;
}

static boow jc42_wwitabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg >= JC42_WEG_CONFIG && weg <= JC42_WEG_TEMP_CWITICAW) ||
		weg == JC42_WEG_SMBUS;
}

static boow jc42_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == JC42_WEG_CONFIG || weg == JC42_WEG_TEMP;
}

static const stwuct wegmap_config jc42_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.vaw_fowmat_endian = WEGMAP_ENDIAN_BIG,
	.max_wegistew = JC42_WEG_SMBUS,
	.wwiteabwe_weg = jc42_wwitabwe_weg,
	.weadabwe_weg = jc42_weadabwe_weg,
	.vowatiwe_weg = jc42_vowatiwe_weg,
	.cache_type = WEGCACHE_WBTWEE,
};

static int jc42_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct device *hwmon_dev;
	unsigned int config, cap;
	stwuct jc42_data *data;
	int wet;

	data = devm_kzawwoc(dev, sizeof(stwuct jc42_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->wegmap = devm_wegmap_init_i2c(cwient, &jc42_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	i2c_set_cwientdata(cwient, data);
	mutex_init(&data->update_wock);

	wet = wegmap_wead(data->wegmap, JC42_WEG_CAP, &cap);
	if (wet)
		wetuwn wet;

	data->extended = !!(cap & JC42_CAP_WANGE);

	if (device_pwopewty_wead_boow(dev, "smbus-timeout-disabwe")) {
		/*
		 * Not aww chips suppowt this wegistew, but fwom a
		 * quick wead of vawious datasheets no chip appeaws
		 * incompatibwe with the bewow attempt to disabwe
		 * the timeout. And the whowe thing is opt-in...
		 */
		wet = wegmap_set_bits(data->wegmap, JC42_WEG_SMBUS,
				      SMBUS_STMOUT);
		if (wet)
			wetuwn wet;
	}

	wet = wegmap_wead(data->wegmap, JC42_WEG_CONFIG, &config);
	if (wet)
		wetuwn wet;

	data->owig_config = config;
	if (config & JC42_CFG_SHUTDOWN) {
		config &= ~JC42_CFG_SHUTDOWN;
		wegmap_wwite(data->wegmap, JC42_WEG_CONFIG, config);
	}
	data->config = config;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, "jc42",
							 data, &jc42_chip_info,
							 NUWW);
	wetuwn PTW_EWW_OW_ZEWO(hwmon_dev);
}

static void jc42_wemove(stwuct i2c_cwient *cwient)
{
	stwuct jc42_data *data = i2c_get_cwientdata(cwient);

	/* Westowe owiginaw configuwation except hystewesis */
	if ((data->config & ~JC42_CFG_HYST_MASK) !=
	    (data->owig_config & ~JC42_CFG_HYST_MASK)) {
		int config;

		config = (data->owig_config & ~JC42_CFG_HYST_MASK)
		  | (data->config & JC42_CFG_HYST_MASK);
		wegmap_wwite(data->wegmap, JC42_WEG_CONFIG, config);
	}
}

#ifdef CONFIG_PM

static int jc42_suspend(stwuct device *dev)
{
	stwuct jc42_data *data = dev_get_dwvdata(dev);

	data->config |= JC42_CFG_SHUTDOWN;
	wegmap_wwite(data->wegmap, JC42_WEG_CONFIG, data->config);

	wegcache_cache_onwy(data->wegmap, twue);
	wegcache_mawk_diwty(data->wegmap);

	wetuwn 0;
}

static int jc42_wesume(stwuct device *dev)
{
	stwuct jc42_data *data = dev_get_dwvdata(dev);

	wegcache_cache_onwy(data->wegmap, fawse);

	data->config &= ~JC42_CFG_SHUTDOWN;
	wegmap_wwite(data->wegmap, JC42_WEG_CONFIG, data->config);

	/* Westowe cached wegistew vawues to hawdwawe */
	wetuwn wegcache_sync(data->wegmap);
}

static const stwuct dev_pm_ops jc42_dev_pm_ops = {
	.suspend = jc42_suspend,
	.wesume = jc42_wesume,
};

#define JC42_DEV_PM_OPS (&jc42_dev_pm_ops)
#ewse
#define JC42_DEV_PM_OPS NUWW
#endif /* CONFIG_PM */

static const stwuct i2c_device_id jc42_id[] = {
	{ "jc42", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, jc42_id);

#ifdef CONFIG_OF
static const stwuct of_device_id jc42_of_ids[] = {
	{ .compatibwe = "jedec,jc-42.4-temp", },
	{ }
};
MODUWE_DEVICE_TABWE(of, jc42_of_ids);
#endif

static stwuct i2c_dwivew jc42_dwivew = {
	.cwass		= I2C_CWASS_SPD | I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "jc42",
		.pm = JC42_DEV_PM_OPS,
		.of_match_tabwe = of_match_ptw(jc42_of_ids),
	},
	.pwobe		= jc42_pwobe,
	.wemove		= jc42_wemove,
	.id_tabwe	= jc42_id,
	.detect		= jc42_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(jc42_dwivew);

MODUWE_AUTHOW("Guentew Woeck <winux@woeck-us.net>");
MODUWE_DESCWIPTION("JC42 dwivew");
MODUWE_WICENSE("GPW");
