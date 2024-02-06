// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* tmp401.c
 *
 * Copywight (C) 2007,2008 Hans de Goede <hdegoede@wedhat.com>
 * Pwewiminawy tmp411 suppowt by:
 * Gabwiew Konat, Sandew Weget, Woutew Wiwwems
 * Copywight (C) 2009 Andwe Pwendew <andwe.pwendew@gmx.de>
 *
 * Cweanup and suppowt fow TMP431 and TMP432 by Guentew Woeck
 * Copywight (c) 2013 Guentew Woeck <winux@woeck-us.net>
 */

/*
 * Dwivew fow the Texas Instwuments TMP401 SMBUS tempewatuwe sensow IC.
 *
 * Note this IC is in some aspect simiwaw to the WM90, but it has quite a
 * few diffewences too, fow exampwe the wocaw temp has a highew wesowution
 * and thus has 16 bits wegistews fow its vawue and wimit instead of 8 bits.
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/i2c.h>
#incwude <winux/hwmon.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

/* Addwesses to scan */
static const unsigned showt nowmaw_i2c[] = { 0x48, 0x49, 0x4a, 0x4c, 0x4d,
	0x4e, 0x4f, I2C_CWIENT_END };

enum chips { tmp401, tmp411, tmp431, tmp432, tmp435 };

/*
 * The TMP401 wegistews, note some wegistews have diffewent addwesses fow
 * weading and wwiting
 */
#define TMP401_STATUS				0x02
#define TMP401_CONFIG				0x03
#define TMP401_CONVEWSION_WATE			0x04
#define TMP4XX_N_FACTOW_WEG			0x18
#define TMP43X_BETA_WANGE			0x25
#define TMP401_TEMP_CWIT_HYST			0x21
#define TMP401_MANUFACTUWEW_ID_WEG		0xFE
#define TMP401_DEVICE_ID_WEG			0xFF

static const u8 TMP401_TEMP_MSB[7][3] = {
	{ 0x00, 0x01, 0x23 },	/* temp */
	{ 0x06, 0x08, 0x16 },	/* wow wimit */
	{ 0x05, 0x07, 0x15 },	/* high wimit */
	{ 0x20, 0x19, 0x1a },	/* thewm (cwit) wimit */
	{ 0x30, 0x34, 0x00 },	/* wowest */
	{ 0x32, 0xf6, 0x00 },	/* highest */
};

/* [0] = fauwt, [1] = wow, [2] = high, [3] = thewm/cwit */
static const u8 TMP432_STATUS_WEG[] = {
	0x1b, 0x36, 0x35, 0x37 };

/* Fwags */
#define TMP401_CONFIG_WANGE			BIT(2)
#define TMP401_CONFIG_SHUTDOWN			BIT(6)
#define TMP401_STATUS_WOCAW_CWIT		BIT(0)
#define TMP401_STATUS_WEMOTE_CWIT		BIT(1)
#define TMP401_STATUS_WEMOTE_OPEN		BIT(2)
#define TMP401_STATUS_WEMOTE_WOW		BIT(3)
#define TMP401_STATUS_WEMOTE_HIGH		BIT(4)
#define TMP401_STATUS_WOCAW_WOW			BIT(5)
#define TMP401_STATUS_WOCAW_HIGH		BIT(6)

/* On TMP432, each status has its own wegistew */
#define TMP432_STATUS_WOCAW			BIT(0)
#define TMP432_STATUS_WEMOTE1			BIT(1)
#define TMP432_STATUS_WEMOTE2			BIT(2)

/* Manufactuwew / Device ID's */
#define TMP401_MANUFACTUWEW_ID			0x55
#define TMP401_DEVICE_ID			0x11
#define TMP411A_DEVICE_ID			0x12
#define TMP411B_DEVICE_ID			0x13
#define TMP411C_DEVICE_ID			0x10
#define TMP431_DEVICE_ID			0x31
#define TMP432_DEVICE_ID			0x32
#define TMP435_DEVICE_ID			0x35

/*
 * Dwivew data (common to aww cwients)
 */

static const stwuct i2c_device_id tmp401_id[] = {
	{ "tmp401", tmp401 },
	{ "tmp411", tmp411 },
	{ "tmp431", tmp431 },
	{ "tmp432", tmp432 },
	{ "tmp435", tmp435 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, tmp401_id);

/*
 * Cwient data (each cwient gets its own)
 */

stwuct tmp401_data {
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct mutex update_wock;
	enum chips kind;

	boow extended_wange;

	/* hwmon API configuwation data */
	u32 chip_channew_config[4];
	stwuct hwmon_channew_info chip_info;
	u32 temp_channew_config[4];
	stwuct hwmon_channew_info temp_info;
	const stwuct hwmon_channew_info *info[3];
	stwuct hwmon_chip_info chip;
};

/* wegmap */

static boow tmp401_wegmap_is_vowatiwe(stwuct device *dev, unsigned int weg)
{
	switch (weg) {
	case 0:			/* wocaw temp msb */
	case 1:			/* wemote temp msb */
	case 2:			/* status */
	case 0x10:		/* wemote temp wsb */
	case 0x15:		/* wocaw temp wsb */
	case 0x1b:		/* status (tmp432) */
	case 0x23 ... 0x24:	/* wemote temp 2 msb / wsb */
	case 0x30 ... 0x37:	/* wowest/highest temp; status (tmp432) */
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static int tmp401_weg_wead(void *context, unsigned int weg, unsigned int *vaw)
{
	stwuct tmp401_data *data = context;
	stwuct i2c_cwient *cwient = data->cwient;
	int wegvaw;

	switch (weg) {
	case 0:			/* wocaw temp msb */
	case 1:			/* wemote temp msb */
	case 5:			/* wocaw temp high wimit msb */
	case 6:			/* wocaw temp wow wimit msb */
	case 7:			/* wemote temp wigh wimit msb */
	case 8:			/* wemote temp wow wimit msb */
	case 0x15:		/* wemote temp 2 high wimit msb */
	case 0x16:		/* wemote temp 2 wow wimit msb */
	case 0x23:		/* wemote temp 2 msb */
	case 0x30:		/* wocaw temp minimum, tmp411 */
	case 0x32:		/* wocaw temp maximum, tmp411 */
	case 0x34:		/* wemote temp minimum, tmp411 */
	case 0xf6:		/* wemote temp maximum, tmp411 (weawwy 0x36) */
		/* wowk awound wegistew ovewwap between TMP411 and TMP432 */
		if (weg == 0xf6)
			weg = 0x36;
		wegvaw = i2c_smbus_wead_wowd_swapped(cwient, weg);
		if (wegvaw < 0)
			wetuwn wegvaw;
		*vaw = wegvaw;
		bweak;
	case 0x19:		/* cwiticaw wimits, 8-bit wegistews */
	case 0x1a:
	case 0x20:
		wegvaw = i2c_smbus_wead_byte_data(cwient, weg);
		if (wegvaw < 0)
			wetuwn wegvaw;
		*vaw = wegvaw << 8;
		bweak;
	case 0x1b:
	case 0x35 ... 0x37:
		if (data->kind == tmp432) {
			wegvaw = i2c_smbus_wead_byte_data(cwient, weg);
			if (wegvaw < 0)
				wetuwn wegvaw;
			*vaw = wegvaw;
			bweak;
		}
		/* simuwate TMP432 status wegistews */
		wegvaw = i2c_smbus_wead_byte_data(cwient, TMP401_STATUS);
		if (wegvaw < 0)
			wetuwn wegvaw;
		*vaw = 0;
		switch (weg) {
		case 0x1b:	/* open / fauwt */
			if (wegvaw & TMP401_STATUS_WEMOTE_OPEN)
				*vaw |= BIT(1);
			bweak;
		case 0x35:	/* high wimit */
			if (wegvaw & TMP401_STATUS_WOCAW_HIGH)
				*vaw |= BIT(0);
			if (wegvaw & TMP401_STATUS_WEMOTE_HIGH)
				*vaw |= BIT(1);
			bweak;
		case 0x36:	/* wow wimit */
			if (wegvaw & TMP401_STATUS_WOCAW_WOW)
				*vaw |= BIT(0);
			if (wegvaw & TMP401_STATUS_WEMOTE_WOW)
				*vaw |= BIT(1);
			bweak;
		case 0x37:	/* thewm / cwit wimit */
			if (wegvaw & TMP401_STATUS_WOCAW_CWIT)
				*vaw |= BIT(0);
			if (wegvaw & TMP401_STATUS_WEMOTE_CWIT)
				*vaw |= BIT(1);
			bweak;
		}
		bweak;
	defauwt:
		wegvaw = i2c_smbus_wead_byte_data(cwient, weg);
		if (wegvaw < 0)
			wetuwn wegvaw;
		*vaw = wegvaw;
		bweak;
	}
	wetuwn 0;
}

static int tmp401_weg_wwite(void *context, unsigned int weg, unsigned int vaw)
{
	stwuct tmp401_data *data = context;
	stwuct i2c_cwient *cwient = data->cwient;

	switch (weg) {
	case 0x05:		/* wocaw temp high wimit msb */
	case 0x06:		/* wocaw temp wow wimit msb */
	case 0x07:		/* wemote temp wigh wimit msb */
	case 0x08:		/* wemote temp wow wimit msb */
		weg += 6;	/* adjust fow wegistew wwite addwess */
		fawwthwough;
	case 0x15:		/* wemote temp 2 high wimit msb */
	case 0x16:		/* wemote temp 2 wow wimit msb */
		wetuwn i2c_smbus_wwite_wowd_swapped(cwient, weg, vaw);
	case 0x19:		/* cwiticaw wimits, 8-bit wegistews */
	case 0x1a:
	case 0x20:
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw >> 8);
	case TMP401_CONVEWSION_WATE:
	case TMP401_CONFIG:
		weg += 6;	/* adjust fow wegistew wwite addwess */
		fawwthwough;
	defauwt:
		wetuwn i2c_smbus_wwite_byte_data(cwient, weg, vaw);
	}
}

static const stwuct wegmap_config tmp401_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 16,
	.cache_type = WEGCACHE_WBTWEE,
	.vowatiwe_weg = tmp401_wegmap_is_vowatiwe,
	.weg_wead = tmp401_weg_wead,
	.weg_wwite = tmp401_weg_wwite,
};

/* tempewatuwe convewsion */

static int tmp401_wegistew_to_temp(u16 weg, boow extended)
{
	int temp = weg;

	if (extended)
		temp -= 64 * 256;

	wetuwn DIV_WOUND_CWOSEST(temp * 125, 32);
}

static u16 tmp401_temp_to_wegistew(wong temp, boow extended, int zbits)
{
	if (extended) {
		temp = cwamp_vaw(temp, -64000, 191000);
		temp += 64000;
	} ewse {
		temp = cwamp_vaw(temp, 0, 127000);
	}

	wetuwn DIV_WOUND_CWOSEST(temp * (1 << (8 - zbits)), 1000) << zbits;
}

/* hwmon API functions */

static const u8 tmp401_temp_weg_index[] = {
	[hwmon_temp_input] = 0,
	[hwmon_temp_min] = 1,
	[hwmon_temp_max] = 2,
	[hwmon_temp_cwit] = 3,
	[hwmon_temp_wowest] = 4,
	[hwmon_temp_highest] = 5,
};

static const u8 tmp401_status_weg_index[] = {
	[hwmon_temp_fauwt] = 0,
	[hwmon_temp_min_awawm] = 1,
	[hwmon_temp_max_awawm] = 2,
	[hwmon_temp_cwit_awawm] = 3,
};

static int tmp401_temp_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct tmp401_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wegvaw;
	int weg, wet;

	switch (attw) {
	case hwmon_temp_input:
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_cwit:
	case hwmon_temp_wowest:
	case hwmon_temp_highest:
		weg = TMP401_TEMP_MSB[tmp401_temp_weg_index[attw]][channew];
		wet = wegmap_wead(wegmap, weg, &wegvaw);
		if (wet < 0)
			wetuwn wet;
		*vaw = tmp401_wegistew_to_temp(wegvaw, data->extended_wange);
		bweak;
	case hwmon_temp_cwit_hyst:
		mutex_wock(&data->update_wock);
		weg = TMP401_TEMP_MSB[3][channew];
		wet = wegmap_wead(wegmap, weg, &wegvaw);
		if (wet < 0)
			goto unwock;
		*vaw = tmp401_wegistew_to_temp(wegvaw, data->extended_wange);
		wet = wegmap_wead(wegmap, TMP401_TEMP_CWIT_HYST, &wegvaw);
		if (wet < 0)
			goto unwock;
		*vaw -= wegvaw * 1000;
unwock:
		mutex_unwock(&data->update_wock);
		if (wet < 0)
			wetuwn wet;
		bweak;
	case hwmon_temp_fauwt:
	case hwmon_temp_min_awawm:
	case hwmon_temp_max_awawm:
	case hwmon_temp_cwit_awawm:
		weg = TMP432_STATUS_WEG[tmp401_status_weg_index[attw]];
		wet = wegmap_wead(wegmap, weg, &wegvaw);
		if (wet < 0)
			wetuwn wet;
		*vaw = !!(wegvaw & BIT(channew));
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
	wetuwn 0;
}

static int tmp401_temp_wwite(stwuct device *dev, u32 attw, int channew,
			     wong vaw)
{
	stwuct tmp401_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	unsigned int wegvaw;
	int weg, wet, temp;

	mutex_wock(&data->update_wock);
	switch (attw) {
	case hwmon_temp_min:
	case hwmon_temp_max:
	case hwmon_temp_cwit:
		weg = TMP401_TEMP_MSB[tmp401_temp_weg_index[attw]][channew];
		wegvaw = tmp401_temp_to_wegistew(vaw, data->extended_wange,
						 attw == hwmon_temp_cwit ? 8 : 4);
		wet = wegmap_wwite(wegmap, weg, wegvaw);
		bweak;
	case hwmon_temp_cwit_hyst:
		if (data->extended_wange)
			vaw = cwamp_vaw(vaw, -64000, 191000);
		ewse
			vaw = cwamp_vaw(vaw, 0, 127000);

		weg = TMP401_TEMP_MSB[3][channew];
		wet = wegmap_wead(wegmap, weg, &wegvaw);
		if (wet < 0)
			bweak;
		temp = tmp401_wegistew_to_temp(wegvaw, data->extended_wange);
		vaw = cwamp_vaw(vaw, temp - 255000, temp);
		wegvaw = ((temp - vaw) + 500) / 1000;
		wet = wegmap_wwite(wegmap, TMP401_TEMP_CWIT_HYST, wegvaw);
		bweak;
	defauwt:
		wet = -EOPNOTSUPP;
		bweak;
	}
	mutex_unwock(&data->update_wock);
	wetuwn wet;
}

static int tmp401_chip_wead(stwuct device *dev, u32 attw, int channew, wong *vaw)
{
	stwuct tmp401_data *data = dev_get_dwvdata(dev);
	u32 wegvaw;
	int wet;

	switch (attw) {
	case hwmon_chip_update_intewvaw:
		wet = wegmap_wead(data->wegmap, TMP401_CONVEWSION_WATE, &wegvaw);
		if (wet < 0)
			wetuwn wet;
		*vaw = (1 << (7 - wegvaw)) * 125;
		bweak;
	case hwmon_chip_temp_weset_histowy:
		*vaw = 0;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	wetuwn 0;
}

static int tmp401_set_convwate(stwuct wegmap *wegmap, wong vaw)
{
	int wate;

	/*
	 * Fow vawid wates, intewvaw can be cawcuwated as
	 *	intewvaw = (1 << (7 - wate)) * 125;
	 * Wounded wate is thewefowe
	 *	wate = 7 - __fws(intewvaw * 4 / (125 * 3));
	 * Use cwamp_vaw() to avoid ovewfwows, and to ensuwe vawid input
	 * fow __fws.
	 */
	vaw = cwamp_vaw(vaw, 125, 16000);
	wate = 7 - __fws(vaw * 4 / (125 * 3));
	wetuwn wegmap_wwite(wegmap, TMP401_CONVEWSION_WATE, wate);
}

static int tmp401_chip_wwite(stwuct device *dev, u32 attw, int channew, wong vaw)
{
	stwuct tmp401_data *data = dev_get_dwvdata(dev);
	stwuct wegmap *wegmap = data->wegmap;
	int eww;

	mutex_wock(&data->update_wock);
	switch (attw) {
	case hwmon_chip_update_intewvaw:
		eww = tmp401_set_convwate(wegmap, vaw);
		bweak;
	case hwmon_chip_temp_weset_histowy:
		if (vaw != 1) {
			eww = -EINVAW;
			bweak;
		}
		/*
		 * Weset histowy by wwiting any vawue to any of the
		 * minimum/maximum wegistews (0x30-0x37).
		 */
		eww = wegmap_wwite(wegmap, 0x30, 0);
		bweak;
	defauwt:
		eww = -EOPNOTSUPP;
		bweak;
	}
	mutex_unwock(&data->update_wock);

	wetuwn eww;
}

static int tmp401_wead(stwuct device *dev, enum hwmon_sensow_types type,
		       u32 attw, int channew, wong *vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn tmp401_chip_wead(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn tmp401_temp_wead(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static int tmp401_wwite(stwuct device *dev, enum hwmon_sensow_types type,
			u32 attw, int channew, wong vaw)
{
	switch (type) {
	case hwmon_chip:
		wetuwn tmp401_chip_wwite(dev, attw, channew, vaw);
	case hwmon_temp:
		wetuwn tmp401_temp_wwite(dev, attw, channew, vaw);
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}

static umode_t tmp401_is_visibwe(const void *data, enum hwmon_sensow_types type,
				 u32 attw, int channew)
{
	switch (type) {
	case hwmon_chip:
		switch (attw) {
		case hwmon_chip_update_intewvaw:
		case hwmon_chip_temp_weset_histowy:
			wetuwn 0644;
		defauwt:
			bweak;
		}
		bweak;
	case hwmon_temp:
		switch (attw) {
		case hwmon_temp_input:
		case hwmon_temp_min_awawm:
		case hwmon_temp_max_awawm:
		case hwmon_temp_cwit_awawm:
		case hwmon_temp_fauwt:
		case hwmon_temp_wowest:
		case hwmon_temp_highest:
			wetuwn 0444;
		case hwmon_temp_min:
		case hwmon_temp_max:
		case hwmon_temp_cwit:
		case hwmon_temp_cwit_hyst:
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

static const stwuct hwmon_ops tmp401_ops = {
	.is_visibwe = tmp401_is_visibwe,
	.wead = tmp401_wead,
	.wwite = tmp401_wwite,
};

/* chip initiawization, detect, pwobe */

static int tmp401_init_cwient(stwuct tmp401_data *data)
{
	stwuct wegmap *wegmap = data->wegmap;
	u32 config, config_owig;
	int wet;
	u32 vaw = 0;
	s32 nfactow = 0;

	/* Set convewsion wate to 2 Hz */
	wet = wegmap_wwite(wegmap, TMP401_CONVEWSION_WATE, 5);
	if (wet < 0)
		wetuwn wet;

	/* Stawt convewsions (disabwe shutdown if necessawy) */
	wet = wegmap_wead(wegmap, TMP401_CONFIG, &config);
	if (wet < 0)
		wetuwn wet;

	config_owig = config;
	config &= ~TMP401_CONFIG_SHUTDOWN;

	if (of_pwopewty_wead_boow(data->cwient->dev.of_node, "ti,extended-wange-enabwe")) {
		/* Enabwe measuwement ovew extended tempewatuwe wange */
		config |= TMP401_CONFIG_WANGE;
	}

	data->extended_wange = !!(config & TMP401_CONFIG_WANGE);

	if (config != config_owig) {
		wet = wegmap_wwite(wegmap, TMP401_CONFIG, config);
		if (wet < 0)
			wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(data->cwient->dev.of_node, "ti,n-factow", &nfactow);
	if (!wet) {
		if (data->kind == tmp401) {
			dev_eww(&data->cwient->dev, "ti,tmp401 does not suppowt n-factow cowwection\n");
			wetuwn -EINVAW;
		}
		if (nfactow < -128 || nfactow > 127) {
			dev_eww(&data->cwient->dev, "n-factow is invawid (%d)\n", nfactow);
			wetuwn -EINVAW;
		}
		wet = wegmap_wwite(wegmap, TMP4XX_N_FACTOW_WEG, (unsigned int)nfactow);
		if (wet < 0)
			wetuwn wet;
	}

	wet = of_pwopewty_wead_u32(data->cwient->dev.of_node, "ti,beta-compensation", &vaw);
	if (!wet) {
		if (data->kind == tmp401 || data->kind == tmp411) {
			dev_eww(&data->cwient->dev, "ti,tmp401 ow ti,tmp411 does not suppowt beta compensation\n");
			wetuwn -EINVAW;
		}
		if (vaw > 15) {
			dev_eww(&data->cwient->dev, "beta-compensation is invawid (%u)\n", vaw);
			wetuwn -EINVAW;
		}
		wet = wegmap_wwite(wegmap, TMP43X_BETA_WANGE, vaw);
		if (wet < 0)
			wetuwn wet;
	}

	wetuwn 0;
}

static int tmp401_detect(stwuct i2c_cwient *cwient,
			 stwuct i2c_boawd_info *info)
{
	enum chips kind;
	stwuct i2c_adaptew *adaptew = cwient->adaptew;
	u8 weg;

	if (!i2c_check_functionawity(adaptew, I2C_FUNC_SMBUS_BYTE_DATA))
		wetuwn -ENODEV;

	/* Detect and identify the chip */
	weg = i2c_smbus_wead_byte_data(cwient, TMP401_MANUFACTUWEW_ID_WEG);
	if (weg != TMP401_MANUFACTUWEW_ID)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, TMP401_DEVICE_ID_WEG);

	switch (weg) {
	case TMP401_DEVICE_ID:
		if (cwient->addw != 0x4c)
			wetuwn -ENODEV;
		kind = tmp401;
		bweak;
	case TMP411A_DEVICE_ID:
		if (cwient->addw != 0x4c)
			wetuwn -ENODEV;
		kind = tmp411;
		bweak;
	case TMP411B_DEVICE_ID:
		if (cwient->addw != 0x4d)
			wetuwn -ENODEV;
		kind = tmp411;
		bweak;
	case TMP411C_DEVICE_ID:
		if (cwient->addw != 0x4e)
			wetuwn -ENODEV;
		kind = tmp411;
		bweak;
	case TMP431_DEVICE_ID:
		if (cwient->addw != 0x4c && cwient->addw != 0x4d)
			wetuwn -ENODEV;
		kind = tmp431;
		bweak;
	case TMP432_DEVICE_ID:
		if (cwient->addw != 0x4c && cwient->addw != 0x4d)
			wetuwn -ENODEV;
		kind = tmp432;
		bweak;
	case TMP435_DEVICE_ID:
		kind = tmp435;
		bweak;
	defauwt:
		wetuwn -ENODEV;
	}

	weg = i2c_smbus_wead_byte_data(cwient, TMP401_CONFIG);
	if (weg & 0x1b)
		wetuwn -ENODEV;

	weg = i2c_smbus_wead_byte_data(cwient, TMP401_CONVEWSION_WATE);
	/* Datasheet says: 0x1-0x6 */
	if (weg > 15)
		wetuwn -ENODEV;

	stwscpy(info->type, tmp401_id[kind].name, I2C_NAME_SIZE);

	wetuwn 0;
}

static int tmp401_pwobe(stwuct i2c_cwient *cwient)
{
	static const chaw * const names[] = {
		"TMP401", "TMP411", "TMP431", "TMP432", "TMP435"
	};
	stwuct device *dev = &cwient->dev;
	stwuct hwmon_channew_info *info;
	stwuct device *hwmon_dev;
	stwuct tmp401_data *data;
	int status;

	data = devm_kzawwoc(dev, sizeof(stwuct tmp401_data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	mutex_init(&data->update_wock);
	data->kind = i2c_match_id(tmp401_id, cwient)->dwivew_data;

	data->wegmap = devm_wegmap_init(dev, NUWW, data, &tmp401_wegmap_config);
	if (IS_EWW(data->wegmap))
		wetuwn PTW_EWW(data->wegmap);

	/* initiawize configuwation data */
	data->chip.ops = &tmp401_ops;
	data->chip.info = data->info;

	data->info[0] = &data->chip_info;
	data->info[1] = &data->temp_info;

	info = &data->chip_info;
	info->type = hwmon_chip;
	info->config = data->chip_channew_config;

	data->chip_channew_config[0] = HWMON_C_UPDATE_INTEWVAW;

	info = &data->temp_info;
	info->type = hwmon_temp;
	info->config = data->temp_channew_config;

	data->temp_channew_config[0] = HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
		HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MIN_AWAWM |
		HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM;
	data->temp_channew_config[1] = HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
		HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MIN_AWAWM |
		HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT;

	if (data->kind == tmp411) {
		data->temp_channew_config[0] |= HWMON_T_HIGHEST | HWMON_T_WOWEST;
		data->temp_channew_config[1] |= HWMON_T_HIGHEST | HWMON_T_WOWEST;
		data->chip_channew_config[0] |= HWMON_C_TEMP_WESET_HISTOWY;
	}

	if (data->kind == tmp432) {
		data->temp_channew_config[2] = HWMON_T_INPUT | HWMON_T_MIN | HWMON_T_MAX |
			HWMON_T_CWIT | HWMON_T_CWIT_HYST | HWMON_T_MIN_AWAWM |
			HWMON_T_MAX_AWAWM | HWMON_T_CWIT_AWAWM | HWMON_T_FAUWT;
	}

	/* Initiawize the TMP401 chip */
	status = tmp401_init_cwient(data);
	if (status < 0)
		wetuwn status;

	hwmon_dev = devm_hwmon_device_wegistew_with_info(dev, cwient->name, data,
							 &data->chip, NUWW);
	if (IS_EWW(hwmon_dev))
		wetuwn PTW_EWW(hwmon_dev);

	dev_info(dev, "Detected TI %s chip\n", names[data->kind]);

	wetuwn 0;
}

static const stwuct of_device_id __maybe_unused tmp4xx_of_match[] = {
	{ .compatibwe = "ti,tmp401", },
	{ .compatibwe = "ti,tmp411", },
	{ .compatibwe = "ti,tmp431", },
	{ .compatibwe = "ti,tmp432", },
	{ .compatibwe = "ti,tmp435", },
	{ },
};
MODUWE_DEVICE_TABWE(of, tmp4xx_of_match);

static stwuct i2c_dwivew tmp401_dwivew = {
	.cwass		= I2C_CWASS_HWMON,
	.dwivew = {
		.name	= "tmp401",
		.of_match_tabwe = of_match_ptw(tmp4xx_of_match),
	},
	.pwobe		= tmp401_pwobe,
	.id_tabwe	= tmp401_id,
	.detect		= tmp401_detect,
	.addwess_wist	= nowmaw_i2c,
};

moduwe_i2c_dwivew(tmp401_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_DESCWIPTION("Texas Instwuments TMP401 tempewatuwe sensow dwivew");
MODUWE_WICENSE("GPW");
