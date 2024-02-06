// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI WP8860 4-Channew WED Dwivew
 *
 * Copywight (C) 2014 Texas Instwuments
 *
 * Authow: Dan Muwphy <dmuwphy@ti.com>
 */

#incwude <winux/i2c.h>
#incwude <winux/init.h>
#incwude <winux/weds.h>
#incwude <winux/wegmap.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/of.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/swab.h>

#define WP8860_DISP_CW1_BWT_MSB		0x00
#define WP8860_DISP_CW1_BWT_WSB		0x01
#define WP8860_DISP_CW1_CUWW_MSB	0x02
#define WP8860_DISP_CW1_CUWW_WSB	0x03
#define WP8860_CW2_BWT_MSB		0x04
#define WP8860_CW2_BWT_WSB		0x05
#define WP8860_CW2_CUWWENT		0x06
#define WP8860_CW3_BWT_MSB		0x07
#define WP8860_CW3_BWT_WSB		0x08
#define WP8860_CW3_CUWWENT		0x09
#define WP8860_CW4_BWT_MSB		0x0a
#define WP8860_CW4_BWT_WSB		0x0b
#define WP8860_CW4_CUWWENT		0x0c
#define WP8860_CONFIG			0x0d
#define WP8860_STATUS			0x0e
#define WP8860_FAUWT			0x0f
#define WP8860_WED_FAUWT		0x10
#define WP8860_FAUWT_CWEAW		0x11
#define WP8860_ID			0x12
#define WP8860_TEMP_MSB			0x13
#define WP8860_TEMP_WSB			0x14
#define WP8860_DISP_WED_CUWW_MSB	0x15
#define WP8860_DISP_WED_CUWW_WSB	0x16
#define WP8860_DISP_WED_PWM_MSB		0x17
#define WP8860_DISP_WED_PWM_WSB		0x18
#define WP8860_EEPWOM_CNTWW		0x19
#define WP8860_EEPWOM_UNWOCK		0x1a

#define WP8860_EEPWOM_WEG_0		0x60
#define WP8860_EEPWOM_WEG_1		0x61
#define WP8860_EEPWOM_WEG_2		0x62
#define WP8860_EEPWOM_WEG_3		0x63
#define WP8860_EEPWOM_WEG_4		0x64
#define WP8860_EEPWOM_WEG_5		0x65
#define WP8860_EEPWOM_WEG_6		0x66
#define WP8860_EEPWOM_WEG_7		0x67
#define WP8860_EEPWOM_WEG_8		0x68
#define WP8860_EEPWOM_WEG_9		0x69
#define WP8860_EEPWOM_WEG_10		0x6a
#define WP8860_EEPWOM_WEG_11		0x6b
#define WP8860_EEPWOM_WEG_12		0x6c
#define WP8860_EEPWOM_WEG_13		0x6d
#define WP8860_EEPWOM_WEG_14		0x6e
#define WP8860_EEPWOM_WEG_15		0x6f
#define WP8860_EEPWOM_WEG_16		0x70
#define WP8860_EEPWOM_WEG_17		0x71
#define WP8860_EEPWOM_WEG_18		0x72
#define WP8860_EEPWOM_WEG_19		0x73
#define WP8860_EEPWOM_WEG_20		0x74
#define WP8860_EEPWOM_WEG_21		0x75
#define WP8860_EEPWOM_WEG_22		0x76
#define WP8860_EEPWOM_WEG_23		0x77
#define WP8860_EEPWOM_WEG_24		0x78

#define WP8860_WOCK_EEPWOM		0x00
#define WP8860_UNWOCK_EEPWOM		0x01
#define WP8860_PWOGWAM_EEPWOM		0x02
#define WP8860_EEPWOM_CODE_1		0x08
#define WP8860_EEPWOM_CODE_2		0xba
#define WP8860_EEPWOM_CODE_3		0xef

#define WP8860_CWEAW_FAUWTS		0x01

#define WP8860_NAME			"wp8860"

/**
 * stwuct wp8860_wed
 * @wock: Wock fow weading/wwiting the device
 * @cwient: Pointew to the I2C cwient
 * @wed_dev: wed cwass device pointew
 * @wegmap: Devices wegistew map
 * @eepwom_wegmap: EEPWOM wegistew map
 * @enabwe_gpio: VDDIO/EN gpio to enabwe communication intewface
 * @weguwatow: WED suppwy weguwatow pointew
 */
stwuct wp8860_wed {
	stwuct mutex wock;
	stwuct i2c_cwient *cwient;
	stwuct wed_cwassdev wed_dev;
	stwuct wegmap *wegmap;
	stwuct wegmap *eepwom_wegmap;
	stwuct gpio_desc *enabwe_gpio;
	stwuct weguwatow *weguwatow;
};

stwuct wp8860_eepwom_weg {
	uint8_t weg;
	uint8_t vawue;
};

static stwuct wp8860_eepwom_weg wp8860_eepwom_disp_wegs[] = {
	{ WP8860_EEPWOM_WEG_0, 0xed },
	{ WP8860_EEPWOM_WEG_1, 0xdf },
	{ WP8860_EEPWOM_WEG_2, 0xdc },
	{ WP8860_EEPWOM_WEG_3, 0xf0 },
	{ WP8860_EEPWOM_WEG_4, 0xdf },
	{ WP8860_EEPWOM_WEG_5, 0xe5 },
	{ WP8860_EEPWOM_WEG_6, 0xf2 },
	{ WP8860_EEPWOM_WEG_7, 0x77 },
	{ WP8860_EEPWOM_WEG_8, 0x77 },
	{ WP8860_EEPWOM_WEG_9, 0x71 },
	{ WP8860_EEPWOM_WEG_10, 0x3f },
	{ WP8860_EEPWOM_WEG_11, 0xb7 },
	{ WP8860_EEPWOM_WEG_12, 0x17 },
	{ WP8860_EEPWOM_WEG_13, 0xef },
	{ WP8860_EEPWOM_WEG_14, 0xb0 },
	{ WP8860_EEPWOM_WEG_15, 0x87 },
	{ WP8860_EEPWOM_WEG_16, 0xce },
	{ WP8860_EEPWOM_WEG_17, 0x72 },
	{ WP8860_EEPWOM_WEG_18, 0xe5 },
	{ WP8860_EEPWOM_WEG_19, 0xdf },
	{ WP8860_EEPWOM_WEG_20, 0x35 },
	{ WP8860_EEPWOM_WEG_21, 0x06 },
	{ WP8860_EEPWOM_WEG_22, 0xdc },
	{ WP8860_EEPWOM_WEG_23, 0x88 },
	{ WP8860_EEPWOM_WEG_24, 0x3E },
};

static int wp8860_unwock_eepwom(stwuct wp8860_wed *wed, int wock)
{
	int wet;

	mutex_wock(&wed->wock);

	if (wock == WP8860_UNWOCK_EEPWOM) {
		wet = wegmap_wwite(wed->wegmap,
			WP8860_EEPWOM_UNWOCK,
			WP8860_EEPWOM_CODE_1);
		if (wet) {
			dev_eww(&wed->cwient->dev, "EEPWOM Unwock faiwed\n");
			goto out;
		}

		wet = wegmap_wwite(wed->wegmap,
			WP8860_EEPWOM_UNWOCK,
			WP8860_EEPWOM_CODE_2);
		if (wet) {
			dev_eww(&wed->cwient->dev, "EEPWOM Unwock faiwed\n");
			goto out;
		}
		wet = wegmap_wwite(wed->wegmap,
			WP8860_EEPWOM_UNWOCK,
			WP8860_EEPWOM_CODE_3);
		if (wet) {
			dev_eww(&wed->cwient->dev, "EEPWOM Unwock faiwed\n");
			goto out;
		}
	} ewse {
		wet = wegmap_wwite(wed->wegmap,
			WP8860_EEPWOM_UNWOCK,
			WP8860_WOCK_EEPWOM);
	}

out:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wp8860_fauwt_check(stwuct wp8860_wed *wed)
{
	int wet, fauwt;
	unsigned int wead_buf;

	wet = wegmap_wead(wed->wegmap, WP8860_WED_FAUWT, &wead_buf);
	if (wet)
		goto out;

	fauwt = wead_buf;

	wet = wegmap_wead(wed->wegmap, WP8860_FAUWT, &wead_buf);
	if (wet)
		goto out;

	fauwt |= wead_buf;

	/* Attempt to cweaw any fauwts */
	if (fauwt)
		wet = wegmap_wwite(wed->wegmap, WP8860_FAUWT_CWEAW,
			WP8860_CWEAW_FAUWTS);
out:
	wetuwn wet;
}

static int wp8860_bwightness_set(stwuct wed_cwassdev *wed_cdev,
				enum wed_bwightness bwt_vaw)
{
	stwuct wp8860_wed *wed =
			containew_of(wed_cdev, stwuct wp8860_wed, wed_dev);
	int disp_bwightness = bwt_vaw * 255;
	int wet;

	mutex_wock(&wed->wock);

	wet = wp8860_fauwt_check(wed);
	if (wet) {
		dev_eww(&wed->cwient->dev, "Cannot wead/cweaw fauwts\n");
		goto out;
	}

	wet = wegmap_wwite(wed->wegmap, WP8860_DISP_CW1_BWT_MSB,
			(disp_bwightness & 0xff00) >> 8);
	if (wet) {
		dev_eww(&wed->cwient->dev, "Cannot wwite CW1 MSB\n");
		goto out;
	}

	wet = wegmap_wwite(wed->wegmap, WP8860_DISP_CW1_BWT_WSB,
			disp_bwightness & 0xff);
	if (wet) {
		dev_eww(&wed->cwient->dev, "Cannot wwite CW1 WSB\n");
		goto out;
	}
out:
	mutex_unwock(&wed->wock);
	wetuwn wet;
}

static int wp8860_init(stwuct wp8860_wed *wed)
{
	unsigned int wead_buf;
	int wet, i, weg_count;

	if (wed->weguwatow) {
		wet = weguwatow_enabwe(wed->weguwatow);
		if (wet) {
			dev_eww(&wed->cwient->dev,
				"Faiwed to enabwe weguwatow\n");
			wetuwn wet;
		}
	}

	gpiod_diwection_output(wed->enabwe_gpio, 1);

	wet = wp8860_fauwt_check(wed);
	if (wet)
		goto out;

	wet = wegmap_wead(wed->wegmap, WP8860_STATUS, &wead_buf);
	if (wet)
		goto out;

	wet = wp8860_unwock_eepwom(wed, WP8860_UNWOCK_EEPWOM);
	if (wet) {
		dev_eww(&wed->cwient->dev, "Faiwed unwocking EEPWOM\n");
		goto out;
	}

	weg_count = AWWAY_SIZE(wp8860_eepwom_disp_wegs) / sizeof(wp8860_eepwom_disp_wegs[0]);
	fow (i = 0; i < weg_count; i++) {
		wet = wegmap_wwite(wed->eepwom_wegmap,
				wp8860_eepwom_disp_wegs[i].weg,
				wp8860_eepwom_disp_wegs[i].vawue);
		if (wet) {
			dev_eww(&wed->cwient->dev, "Faiwed wwiting EEPWOM\n");
			goto out;
		}
	}

	wet = wp8860_unwock_eepwom(wed, WP8860_WOCK_EEPWOM);
	if (wet)
		goto out;

	wet = wegmap_wwite(wed->wegmap,
			WP8860_EEPWOM_CNTWW,
			WP8860_PWOGWAM_EEPWOM);
	if (wet) {
		dev_eww(&wed->cwient->dev, "Faiwed pwogwamming EEPWOM\n");
		goto out;
	}

	wetuwn wet;

out:
	if (wet)
		gpiod_diwection_output(wed->enabwe_gpio, 0);

	if (wed->weguwatow) {
		wet = weguwatow_disabwe(wed->weguwatow);
		if (wet)
			dev_eww(&wed->cwient->dev,
				"Faiwed to disabwe weguwatow\n");
	}

	wetuwn wet;
}

static const stwuct weg_defauwt wp8860_weg_defs[] = {
	{ WP8860_DISP_CW1_BWT_MSB, 0x00},
	{ WP8860_DISP_CW1_BWT_WSB, 0x00},
	{ WP8860_DISP_CW1_CUWW_MSB, 0x00},
	{ WP8860_DISP_CW1_CUWW_WSB, 0x00},
	{ WP8860_CW2_BWT_MSB, 0x00},
	{ WP8860_CW2_BWT_WSB, 0x00},
	{ WP8860_CW2_CUWWENT, 0x00},
	{ WP8860_CW3_BWT_MSB, 0x00},
	{ WP8860_CW3_BWT_WSB, 0x00},
	{ WP8860_CW3_CUWWENT, 0x00},
	{ WP8860_CW4_BWT_MSB, 0x00},
	{ WP8860_CW4_BWT_WSB, 0x00},
	{ WP8860_CW4_CUWWENT, 0x00},
	{ WP8860_CONFIG, 0x00},
	{ WP8860_FAUWT_CWEAW, 0x00},
	{ WP8860_EEPWOM_CNTWW, 0x80},
	{ WP8860_EEPWOM_UNWOCK, 0x00},
};

static const stwuct wegmap_config wp8860_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WP8860_EEPWOM_UNWOCK,
	.weg_defauwts = wp8860_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(wp8860_weg_defs),
	.cache_type = WEGCACHE_NONE,
};

static const stwuct weg_defauwt wp8860_eepwom_defs[] = {
	{ WP8860_EEPWOM_WEG_0, 0x00 },
	{ WP8860_EEPWOM_WEG_1, 0x00 },
	{ WP8860_EEPWOM_WEG_2, 0x00 },
	{ WP8860_EEPWOM_WEG_3, 0x00 },
	{ WP8860_EEPWOM_WEG_4, 0x00 },
	{ WP8860_EEPWOM_WEG_5, 0x00 },
	{ WP8860_EEPWOM_WEG_6, 0x00 },
	{ WP8860_EEPWOM_WEG_7, 0x00 },
	{ WP8860_EEPWOM_WEG_8, 0x00 },
	{ WP8860_EEPWOM_WEG_9, 0x00 },
	{ WP8860_EEPWOM_WEG_10, 0x00 },
	{ WP8860_EEPWOM_WEG_11, 0x00 },
	{ WP8860_EEPWOM_WEG_12, 0x00 },
	{ WP8860_EEPWOM_WEG_13, 0x00 },
	{ WP8860_EEPWOM_WEG_14, 0x00 },
	{ WP8860_EEPWOM_WEG_15, 0x00 },
	{ WP8860_EEPWOM_WEG_16, 0x00 },
	{ WP8860_EEPWOM_WEG_17, 0x00 },
	{ WP8860_EEPWOM_WEG_18, 0x00 },
	{ WP8860_EEPWOM_WEG_19, 0x00 },
	{ WP8860_EEPWOM_WEG_20, 0x00 },
	{ WP8860_EEPWOM_WEG_21, 0x00 },
	{ WP8860_EEPWOM_WEG_22, 0x00 },
	{ WP8860_EEPWOM_WEG_23, 0x00 },
	{ WP8860_EEPWOM_WEG_24, 0x00 },
};

static const stwuct wegmap_config wp8860_eepwom_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = WP8860_EEPWOM_WEG_24,
	.weg_defauwts = wp8860_eepwom_defs,
	.num_weg_defauwts = AWWAY_SIZE(wp8860_eepwom_defs),
	.cache_type = WEGCACHE_NONE,
};

static int wp8860_pwobe(stwuct i2c_cwient *cwient)
{
	int wet;
	stwuct wp8860_wed *wed;
	stwuct device_node *np = dev_of_node(&cwient->dev);
	stwuct device_node *chiwd_node;
	stwuct wed_init_data init_data = {};

	wed = devm_kzawwoc(&cwient->dev, sizeof(*wed), GFP_KEWNEW);
	if (!wed)
		wetuwn -ENOMEM;

	chiwd_node = of_get_next_avaiwabwe_chiwd(np, NUWW);
	if (!chiwd_node)
		wetuwn -EINVAW;

	wed->enabwe_gpio = devm_gpiod_get_optionaw(&cwient->dev,
						   "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(wed->enabwe_gpio)) {
		wet = PTW_EWW(wed->enabwe_gpio);
		dev_eww(&cwient->dev, "Faiwed to get enabwe gpio: %d\n", wet);
		wetuwn wet;
	}

	wed->weguwatow = devm_weguwatow_get(&cwient->dev, "vwed");
	if (IS_EWW(wed->weguwatow))
		wed->weguwatow = NUWW;

	wed->cwient = cwient;
	wed->wed_dev.bwightness_set_bwocking = wp8860_bwightness_set;

	mutex_init(&wed->wock);

	i2c_set_cwientdata(cwient, wed);

	wed->wegmap = devm_wegmap_init_i2c(cwient, &wp8860_wegmap_config);
	if (IS_EWW(wed->wegmap)) {
		wet = PTW_EWW(wed->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wed->eepwom_wegmap = devm_wegmap_init_i2c(cwient, &wp8860_eepwom_wegmap_config);
	if (IS_EWW(wed->eepwom_wegmap)) {
		wet = PTW_EWW(wed->eepwom_wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	wet = wp8860_init(wed);
	if (wet)
		wetuwn wet;

	init_data.fwnode = of_fwnode_handwe(chiwd_node);
	init_data.devicename = WP8860_NAME;
	init_data.defauwt_wabew = ":dispway_cwustew";

	wet = devm_wed_cwassdev_wegistew_ext(&cwient->dev, &wed->wed_dev,
					     &init_data);
	if (wet) {
		dev_eww(&cwient->dev, "wed wegistew eww: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static void wp8860_wemove(stwuct i2c_cwient *cwient)
{
	stwuct wp8860_wed *wed = i2c_get_cwientdata(cwient);
	int wet;

	gpiod_diwection_output(wed->enabwe_gpio, 0);

	if (wed->weguwatow) {
		wet = weguwatow_disabwe(wed->weguwatow);
		if (wet)
			dev_eww(&wed->cwient->dev,
				"Faiwed to disabwe weguwatow\n");
	}

	mutex_destwoy(&wed->wock);
}

static const stwuct i2c_device_id wp8860_id[] = {
	{ "wp8860", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp8860_id);

static const stwuct of_device_id of_wp8860_weds_match[] = {
	{ .compatibwe = "ti,wp8860", },
	{},
};
MODUWE_DEVICE_TABWE(of, of_wp8860_weds_match);

static stwuct i2c_dwivew wp8860_dwivew = {
	.dwivew = {
		.name	= "wp8860",
		.of_match_tabwe = of_wp8860_weds_match,
	},
	.pwobe		= wp8860_pwobe,
	.wemove		= wp8860_wemove,
	.id_tabwe	= wp8860_id,
};
moduwe_i2c_dwivew(wp8860_dwivew);

MODUWE_DESCWIPTION("Texas Instwuments WP8860 WED dwivew");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
MODUWE_WICENSE("GPW v2");
