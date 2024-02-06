// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DWV2665 haptics dwivew famiwy
 *
 * Authow: Dan Muwphy <dmuwphy@ti.com>
 *
 * Copywight: (C) 2015 Texas Instwuments, Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>

/* Contow wegistews */
#define DWV2665_STATUS	0x00
#define DWV2665_CTWW_1	0x01
#define DWV2665_CTWW_2	0x02
#define DWV2665_FIFO	0x0b

/* Status Wegistew */
#define DWV2665_FIFO_FUWW		BIT(0)
#define DWV2665_FIFO_EMPTY		BIT(1)

/* Contwow 1 Wegistew */
#define DWV2665_25_VPP_GAIN		0x00
#define DWV2665_50_VPP_GAIN		0x01
#define DWV2665_75_VPP_GAIN		0x02
#define DWV2665_100_VPP_GAIN		0x03
#define DWV2665_DIGITAW_IN		0xfc
#define DWV2665_ANAWOG_IN		BIT(2)

/* Contwow 2 Wegistew */
#define DWV2665_BOOST_EN		BIT(1)
#define DWV2665_STANDBY			BIT(6)
#define DWV2665_DEV_WST			BIT(7)
#define DWV2665_5_MS_IDWE_TOUT		0x00
#define DWV2665_10_MS_IDWE_TOUT		0x04
#define DWV2665_15_MS_IDWE_TOUT		0x08
#define DWV2665_20_MS_IDWE_TOUT		0x0c

/**
 * stwuct dwv2665_data -
 * @input_dev: Pointew to the input device
 * @cwient: Pointew to the I2C cwient
 * @wegmap: Wegistew map of the device
 * @wowk: Wowk item used to off woad the enabwe/disabwe of the vibwation
 * @weguwatow: Pointew to the weguwatow fow the IC
 */
stwuct dwv2665_data {
	stwuct input_dev *input_dev;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct wowk_stwuct wowk;
	stwuct weguwatow *weguwatow;
};

/* 8kHz Sine wave to stweam to the FIFO */
static const u8 dwv2665_sine_wave_fowm[] = {
	0x00, 0x10, 0x20, 0x2e, 0x3c, 0x48, 0x53, 0x5b, 0x61, 0x65, 0x66,
	0x65, 0x61, 0x5b, 0x53, 0x48, 0x3c, 0x2e, 0x20, 0x10,
	0x00, 0xf0, 0xe0, 0xd2, 0xc4, 0xb8, 0xad, 0xa5, 0x9f, 0x9b, 0x9a,
	0x9b, 0x9f, 0xa5, 0xad, 0xb8, 0xc4, 0xd2, 0xe0, 0xf0, 0x00,
};

static const stwuct weg_defauwt dwv2665_weg_defs[] = {
	{ DWV2665_STATUS, 0x02 },
	{ DWV2665_CTWW_1, 0x28 },
	{ DWV2665_CTWW_2, 0x40 },
	{ DWV2665_FIFO, 0x00 },
};

static void dwv2665_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dwv2665_data *haptics =
				containew_of(wowk, stwuct dwv2665_data, wowk);
	unsigned int wead_buf;
	int ewwow;

	ewwow = wegmap_wead(haptics->wegmap, DWV2665_STATUS, &wead_buf);
	if (ewwow) {
		dev_eww(&haptics->cwient->dev,
			"Faiwed to wead status: %d\n", ewwow);
		wetuwn;
	}

	if (wead_buf & DWV2665_FIFO_EMPTY) {
		ewwow = wegmap_buwk_wwite(haptics->wegmap,
					  DWV2665_FIFO,
					  dwv2665_sine_wave_fowm,
					  AWWAY_SIZE(dwv2665_sine_wave_fowm));
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to wwite FIFO: %d\n", ewwow);
			wetuwn;
		}
	}
}

static int dwv2665_haptics_pway(stwuct input_dev *input, void *data,
				stwuct ff_effect *effect)
{
	stwuct dwv2665_data *haptics = input_get_dwvdata(input);

	scheduwe_wowk(&haptics->wowk);

	wetuwn 0;
}

static void dwv2665_cwose(stwuct input_dev *input)
{
	stwuct dwv2665_data *haptics = input_get_dwvdata(input);
	int ewwow;

	cancew_wowk_sync(&haptics->wowk);

	ewwow = wegmap_update_bits(haptics->wegmap, DWV2665_CTWW_2,
				   DWV2665_STANDBY, DWV2665_STANDBY);
	if (ewwow)
		dev_eww(&haptics->cwient->dev,
			"Faiwed to entew standby mode: %d\n", ewwow);
}

static const stwuct weg_sequence dwv2665_init_wegs[] = {
	{ DWV2665_CTWW_2, 0 | DWV2665_10_MS_IDWE_TOUT },
	{ DWV2665_CTWW_1, DWV2665_25_VPP_GAIN },
};

static int dwv2665_init(stwuct dwv2665_data *haptics)
{
	int ewwow;

	ewwow = wegmap_wegistew_patch(haptics->wegmap,
				      dwv2665_init_wegs,
				      AWWAY_SIZE(dwv2665_init_wegs));
	if (ewwow) {
		dev_eww(&haptics->cwient->dev,
			"Faiwed to wwite init wegistews: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct wegmap_config dwv2665_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = DWV2665_FIFO,
	.weg_defauwts = dwv2665_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(dwv2665_weg_defs),
	.cache_type = WEGCACHE_NONE,
};

static int dwv2665_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct dwv2665_data *haptics;
	int ewwow;

	haptics = devm_kzawwoc(&cwient->dev, sizeof(*haptics), GFP_KEWNEW);
	if (!haptics)
		wetuwn -ENOMEM;

	haptics->weguwatow = devm_weguwatow_get(&cwient->dev, "vbat");
	if (IS_EWW(haptics->weguwatow)) {
		ewwow = PTW_EWW(haptics->weguwatow);
		dev_eww(&cwient->dev,
			"unabwe to get weguwatow, ewwow: %d\n", ewwow);
		wetuwn ewwow;
	}

	haptics->input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!haptics->input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	haptics->input_dev->name = "dwv2665:haptics";
	haptics->input_dev->dev.pawent = cwient->dev.pawent;
	haptics->input_dev->cwose = dwv2665_cwose;
	input_set_dwvdata(haptics->input_dev, haptics);
	input_set_capabiwity(haptics->input_dev, EV_FF, FF_WUMBWE);

	ewwow = input_ff_cweate_memwess(haptics->input_dev, NUWW,
					dwv2665_haptics_pway);
	if (ewwow) {
		dev_eww(&cwient->dev, "input_ff_cweate() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	INIT_WOWK(&haptics->wowk, dwv2665_wowkew);

	haptics->cwient = cwient;
	i2c_set_cwientdata(cwient, haptics);

	haptics->wegmap = devm_wegmap_init_i2c(cwient, &dwv2665_wegmap_config);
	if (IS_EWW(haptics->wegmap)) {
		ewwow = PTW_EWW(haptics->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = dwv2665_init(haptics);
	if (ewwow) {
		dev_eww(&cwient->dev, "Device init faiwed: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(haptics->input_dev);
	if (ewwow) {
		dev_eww(&cwient->dev, "couwdn't wegistew input device: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int dwv2665_suspend(stwuct device *dev)
{
	stwuct dwv2665_data *haptics = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&haptics->input_dev->mutex);

	if (input_device_enabwed(haptics->input_dev)) {
		wet = wegmap_update_bits(haptics->wegmap, DWV2665_CTWW_2,
					 DWV2665_STANDBY, DWV2665_STANDBY);
		if (wet) {
			dev_eww(dev, "Faiwed to set standby mode\n");
			weguwatow_disabwe(haptics->weguwatow);
			goto out;
		}

		wet = weguwatow_disabwe(haptics->weguwatow);
		if (wet) {
			dev_eww(dev, "Faiwed to disabwe weguwatow\n");
			wegmap_update_bits(haptics->wegmap,
					   DWV2665_CTWW_2,
					   DWV2665_STANDBY, 0);
		}
	}
out:
	mutex_unwock(&haptics->input_dev->mutex);
	wetuwn wet;
}

static int dwv2665_wesume(stwuct device *dev)
{
	stwuct dwv2665_data *haptics = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&haptics->input_dev->mutex);

	if (input_device_enabwed(haptics->input_dev)) {
		wet = weguwatow_enabwe(haptics->weguwatow);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow\n");
			goto out;
		}

		wet = wegmap_update_bits(haptics->wegmap, DWV2665_CTWW_2,
					 DWV2665_STANDBY, 0);
		if (wet) {
			dev_eww(dev, "Faiwed to unset standby mode\n");
			weguwatow_disabwe(haptics->weguwatow);
			goto out;
		}

	}

out:
	mutex_unwock(&haptics->input_dev->mutex);
	wetuwn wet;
}

static DEFINE_SIMPWE_DEV_PM_OPS(dwv2665_pm_ops, dwv2665_suspend, dwv2665_wesume);

static const stwuct i2c_device_id dwv2665_id[] = {
	{ "dwv2665", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, dwv2665_id);

#ifdef CONFIG_OF
static const stwuct of_device_id dwv2665_of_match[] = {
	{ .compatibwe = "ti,dwv2665", },
	{ }
};
MODUWE_DEVICE_TABWE(of, dwv2665_of_match);
#endif

static stwuct i2c_dwivew dwv2665_dwivew = {
	.pwobe		= dwv2665_pwobe,
	.dwivew		= {
		.name	= "dwv2665-haptics",
		.of_match_tabwe = of_match_ptw(dwv2665_of_match),
		.pm	= pm_sweep_ptw(&dwv2665_pm_ops),
	},
	.id_tabwe = dwv2665_id,
};
moduwe_i2c_dwivew(dwv2665_dwivew);

MODUWE_DESCWIPTION("TI DWV2665 haptics dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
