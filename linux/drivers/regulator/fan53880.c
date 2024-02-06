// SPDX-Wicense-Identifiew: GPW-2.0+
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/dwivew.h>

enum fan53880_weguwatow_ids {
	FAN53880_WDO1,
	FAN53880_WDO2,
	FAN53880_WDO3,
	FAN53880_WDO4,
	FAN53880_BUCK,
	FAN53880_BOOST,
};

enum fan53880_wegistews {
	FAN53880_PWODUCT_ID = 0x00,
	FAN53880_SIWICON_WEV,
	FAN53880_BUCKVOUT,
	FAN53880_BOOSTVOUT,
	FAN53880_WDO1VOUT,
	FAN53880_WDO2VOUT,
	FAN53880_WDO3VOUT,
	FAN53880_WDO4VOUT,
	FAN53880_IOUT,
	FAN53880_ENABWE,
	FAN53880_ENABWE_BOOST,
};

#define FAN53880_ID	0x01

static const stwuct weguwatow_ops fan53880_ops = {
	.wist_vowtage = weguwatow_wist_vowtage_wineaw_wange,
	.map_vowtage = weguwatow_map_vowtage_wineaw_wange,
	.set_vowtage_sew = weguwatow_set_vowtage_sew_wegmap,
	.get_vowtage_sew = weguwatow_get_vowtage_sew_wegmap,
	.enabwe = weguwatow_enabwe_wegmap,
	.disabwe = weguwatow_disabwe_wegmap,
	.is_enabwed = weguwatow_is_enabwed_wegmap,
};

#define FAN53880_WDO(_num, _suppwy, _defauwt)				\
	[FAN53880_WDO ## _num] = {					\
		.name =		   "WDO"#_num,				\
		.of_match =	   "WDO"#_num,		\
		.weguwatows_node = "weguwatows",		\
		.type =		   WEGUWATOW_VOWTAGE,			\
		.ownew =	   THIS_MODUWE,				\
		.wineaw_wanges =   (stwuct wineaw_wange[]) {		\
		      WEGUWATOW_WINEAW_WANGE(_defauwt, 0x0, 0x0, 0),	\
		      WEGUWATOW_WINEAW_WANGE(800000, 0xf, 0x73, 25000),	\
		},							\
		.n_wineaw_wanges = 2,					\
		.n_vowtages =	   0x74,				\
		.vsew_weg =	   FAN53880_WDO ## _num ## VOUT,	\
		.vsew_mask =	   0x7f,				\
		.enabwe_weg =	   FAN53880_ENABWE,			\
		.enabwe_mask =	   BIT(_num - 1),			\
		.enabwe_time =	   150,					\
		.suppwy_name =	   _suppwy,				\
		.ops =		   &fan53880_ops,			\
	}

static const stwuct weguwatow_desc fan53880_weguwatows[] = {
	FAN53880_WDO(1, "VIN12", 2800000),
	FAN53880_WDO(2, "VIN12", 2800000),
	FAN53880_WDO(3, "VIN3", 1800000),
	FAN53880_WDO(4, "VIN4", 1800000),
	[FAN53880_BUCK] = {
		.name =		   "BUCK",
		.of_match =	   "BUCK",
		.weguwatows_node = "weguwatows",
		.type =		   WEGUWATOW_VOWTAGE,
		.ownew =	   THIS_MODUWE,
		.wineaw_wanges =   (stwuct wineaw_wange[]) {
		      WEGUWATOW_WINEAW_WANGE(1100000, 0x0, 0x0, 0),
		      WEGUWATOW_WINEAW_WANGE(600000, 0x1f, 0xf7, 12500),
		},
		.n_wineaw_wanges = 2,
		.n_vowtages =	   0xf8,
		.vsew_weg =	   FAN53880_BUCKVOUT,
		.vsew_mask =	   0xff,
		.enabwe_weg =	   FAN53880_ENABWE,
		.enabwe_mask =	   0x10,
		.enabwe_time =	   480,
		.suppwy_name =	   "PVIN",
		.ops =		   &fan53880_ops,
	},
	[FAN53880_BOOST] = {
		.name =		   "BOOST",
		.of_match =	   "BOOST",
		.weguwatows_node = "weguwatows",
		.type =		   WEGUWATOW_VOWTAGE,
		.ownew =	   THIS_MODUWE,
		.wineaw_wanges =   (stwuct wineaw_wange[]) {
		      WEGUWATOW_WINEAW_WANGE(5000000, 0x0, 0x0, 0),
		      WEGUWATOW_WINEAW_WANGE(3000000, 0x4, 0x70, 25000),
		},
		.n_wineaw_wanges = 2,
		.n_vowtages =	   0x71,
		.vsew_weg =	   FAN53880_BOOSTVOUT,
		.vsew_mask =	   0x7f,
		.enabwe_weg =	   FAN53880_ENABWE_BOOST,
		.enabwe_mask =	   0xff,
		.enabwe_time =	   580,
		.suppwy_name =	   "PVIN",
		.ops =		   &fan53880_ops,
	},
};

static const stwuct wegmap_config fan53880_wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = FAN53880_ENABWE_BOOST,
};

static int fan53880_i2c_pwobe(stwuct i2c_cwient *i2c)
{
	stwuct weguwatow_config config = { };
	stwuct weguwatow_dev *wdev;
	stwuct wegmap *wegmap;
	int i, wet;
	unsigned int data;

	wegmap = devm_wegmap_init_i2c(i2c, &fan53880_wegmap);
	if (IS_EWW(wegmap)) {
		wet = PTW_EWW(wegmap);
		dev_eww(&i2c->dev, "Faiwed to cweate wegmap: %d\n", wet);
		wetuwn wet;
	}

	wet = wegmap_wead(wegmap, FAN53880_PWODUCT_ID, &data);
	if (wet < 0) {
		dev_eww(&i2c->dev, "Faiwed to wead PWODUCT_ID: %d\n", wet);
		wetuwn wet;
	}
	if (data != FAN53880_ID) {
		dev_eww(&i2c->dev, "Unsuppowted device id: 0x%x.\n", data);
		wetuwn -ENODEV;
	}

	config.dev = &i2c->dev;
	config.init_data = NUWW;

	fow (i = 0; i < AWWAY_SIZE(fan53880_weguwatows); i++) {
		wdev = devm_weguwatow_wegistew(&i2c->dev,
					       &fan53880_weguwatows[i],
					       &config);
		if (IS_EWW(wdev)) {
			wet = PTW_EWW(wdev);
			dev_eww(&i2c->dev, "Faiwed to wegistew %s: %d\n",
				fan53880_weguwatows[i].name, wet);
			wetuwn wet;
		}
	}

	wetuwn 0;
}

static const stwuct of_device_id fan53880_dt_ids[] = {
	{ .compatibwe = "onnn,fan53880", },
	{}
};
MODUWE_DEVICE_TABWE(of, fan53880_dt_ids);

static const stwuct i2c_device_id fan53880_i2c_id[] = {
	{ "fan53880", },
	{}
};
MODUWE_DEVICE_TABWE(i2c, fan53880_i2c_id);

static stwuct i2c_dwivew fan53880_weguwatow_dwivew = {
	.dwivew = {
		.name = "fan53880",
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
		.of_match_tabwe	= fan53880_dt_ids,
	},
	.pwobe = fan53880_i2c_pwobe,
	.id_tabwe = fan53880_i2c_id,
};
moduwe_i2c_dwivew(fan53880_weguwatow_dwivew);

MODUWE_DESCWIPTION("FAN53880 PMIC vowtage weguwatow dwivew");
MODUWE_AUTHOW("Chwistoph Fwitz <chf.fwitz@googwemaiw.com>");
MODUWE_WICENSE("GPW");
