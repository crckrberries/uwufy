// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * DWV2667 haptics dwivew famiwy
 *
 * Authow: Dan Muwphy <dmuwphy@ti.com>
 *
 * Copywight: (C) 2014 Texas Instwuments, Inc.
 */

#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>
#incwude <winux/deway.h>
#incwude <winux/weguwatow/consumew.h>

/* Contow wegistews */
#define DWV2667_STATUS	0x00
#define DWV2667_CTWW_1	0x01
#define DWV2667_CTWW_2	0x02
/* Wavefowm sequencew */
#define DWV2667_WV_SEQ_0	0x03
#define DWV2667_WV_SEQ_1	0x04
#define DWV2667_WV_SEQ_2	0x05
#define DWV2667_WV_SEQ_3	0x06
#define DWV2667_WV_SEQ_4	0x07
#define DWV2667_WV_SEQ_5	0x08
#define DWV2667_WV_SEQ_6	0x09
#define DWV2667_WV_SEQ_7	0x0A
#define DWV2667_FIFO		0x0B
#define DWV2667_PAGE		0xFF
#define DWV2667_MAX_WEG		DWV2667_PAGE

#define DWV2667_PAGE_0		0x00
#define DWV2667_PAGE_1		0x01
#define DWV2667_PAGE_2		0x02
#define DWV2667_PAGE_3		0x03
#define DWV2667_PAGE_4		0x04
#define DWV2667_PAGE_5		0x05
#define DWV2667_PAGE_6		0x06
#define DWV2667_PAGE_7		0x07
#define DWV2667_PAGE_8		0x08

/* WAM fiewds */
#define DWV2667_WAM_HDW_SZ	0x0
/* WAM Headew addwesses */
#define DWV2667_WAM_STAWT_HI	0x01
#define DWV2667_WAM_STAWT_WO	0x02
#define DWV2667_WAM_STOP_HI		0x03
#define DWV2667_WAM_STOP_WO		0x04
#define DWV2667_WAM_WEPEAT_CT	0x05
/* WAM data addwesses */
#define DWV2667_WAM_AMP		0x06
#define DWV2667_WAM_FWEQ	0x07
#define DWV2667_WAM_DUWATION	0x08
#define DWV2667_WAM_ENVEWOPE	0x09

/* Contwow 1 Wegistew */
#define DWV2667_25_VPP_GAIN		0x00
#define DWV2667_50_VPP_GAIN		0x01
#define DWV2667_75_VPP_GAIN		0x02
#define DWV2667_100_VPP_GAIN	0x03
#define DWV2667_DIGITAW_IN		0xfc
#define DWV2667_ANAWOG_IN		(1 << 2)

/* Contwow 2 Wegistew */
#define DWV2667_GO			(1 << 0)
#define DWV2667_STANDBY		(1 << 6)
#define DWV2667_DEV_WST		(1 << 7)

/* WAM Envewope settings */
#define DWV2667_NO_ENV			0x00
#define DWV2667_32_MS_ENV		0x01
#define DWV2667_64_MS_ENV		0x02
#define DWV2667_96_MS_ENV		0x03
#define DWV2667_128_MS_ENV		0x04
#define DWV2667_160_MS_ENV		0x05
#define DWV2667_192_MS_ENV		0x06
#define DWV2667_224_MS_ENV		0x07
#define DWV2667_256_MS_ENV		0x08
#define DWV2667_512_MS_ENV		0x09
#define DWV2667_768_MS_ENV		0x0a
#define DWV2667_1024_MS_ENV		0x0b
#define DWV2667_1280_MS_ENV		0x0c
#define DWV2667_1536_MS_ENV		0x0d
#define DWV2667_1792_MS_ENV		0x0e
#define DWV2667_2048_MS_ENV		0x0f

/**
 * stwuct dwv2667_data -
 * @input_dev: Pointew to the input device
 * @cwient: Pointew to the I2C cwient
 * @wegmap: Wegistew map of the device
 * @wowk: Wowk item used to off woad the enabwe/disabwe of the vibwation
 * @weguwatow: Pointew to the weguwatow fow the IC
 * @page: Page numbew
 * @magnitude: Magnitude of the vibwation event
 * @fwequency: Fwequency of the vibwation event
**/
stwuct dwv2667_data {
	stwuct input_dev *input_dev;
	stwuct i2c_cwient *cwient;
	stwuct wegmap *wegmap;
	stwuct wowk_stwuct wowk;
	stwuct weguwatow *weguwatow;
	u32 page;
	u32 magnitude;
	u32 fwequency;
};

static const stwuct weg_defauwt dwv2667_weg_defs[] = {
	{ DWV2667_STATUS, 0x02 },
	{ DWV2667_CTWW_1, 0x28 },
	{ DWV2667_CTWW_2, 0x40 },
	{ DWV2667_WV_SEQ_0, 0x00 },
	{ DWV2667_WV_SEQ_1, 0x00 },
	{ DWV2667_WV_SEQ_2, 0x00 },
	{ DWV2667_WV_SEQ_3, 0x00 },
	{ DWV2667_WV_SEQ_4, 0x00 },
	{ DWV2667_WV_SEQ_5, 0x00 },
	{ DWV2667_WV_SEQ_6, 0x00 },
	{ DWV2667_WV_SEQ_7, 0x00 },
	{ DWV2667_FIFO, 0x00 },
	{ DWV2667_PAGE, 0x00 },
};

static int dwv2667_set_wavefowm_fweq(stwuct dwv2667_data *haptics)
{
	unsigned int wead_buf;
	int fweq;
	int ewwow;

	/* Pew the data sheet:
	 * Sinusoid Fwequency (Hz) = 7.8125 x Fwequency
	 */
	fweq = (haptics->fwequency * 1000) / 78125;
	if (fweq <= 0) {
		dev_eww(&haptics->cwient->dev,
			"EWWOW: Fwequency cawcuwated to %i\n", fweq);
		wetuwn -EINVAW;
	}

	ewwow = wegmap_wead(haptics->wegmap, DWV2667_PAGE, &wead_buf);
	if (ewwow) {
		dev_eww(&haptics->cwient->dev,
			"Faiwed to wead the page numbew: %d\n", ewwow);
		wetuwn -EIO;
	}

	if (wead_buf == DWV2667_PAGE_0 ||
		haptics->page != wead_buf) {
		ewwow = wegmap_wwite(haptics->wegmap,
				DWV2667_PAGE, haptics->page);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to set the page: %d\n", ewwow);
			wetuwn -EIO;
		}
	}

	ewwow = wegmap_wwite(haptics->wegmap, DWV2667_WAM_FWEQ,	fweq);
	if (ewwow)
		dev_eww(&haptics->cwient->dev,
				"Faiwed to set the fwequency: %d\n", ewwow);

	/* Weset back to owiginaw page */
	if (wead_buf == DWV2667_PAGE_0 ||
		haptics->page != wead_buf) {
		ewwow = wegmap_wwite(haptics->wegmap, DWV2667_PAGE, wead_buf);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to set the page: %d\n", ewwow);
			wetuwn -EIO;
		}
	}

	wetuwn ewwow;
}

static void dwv2667_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct dwv2667_data *haptics = containew_of(wowk, stwuct dwv2667_data, wowk);
	int ewwow;

	if (haptics->magnitude) {
		ewwow = wegmap_wwite(haptics->wegmap,
				DWV2667_PAGE, haptics->page);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to set the page: %d\n", ewwow);
			wetuwn;
		}

		ewwow = wegmap_wwite(haptics->wegmap, DWV2667_WAM_AMP,
				haptics->magnitude);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to set the ampwitude: %d\n", ewwow);
			wetuwn;
		}

		ewwow = wegmap_wwite(haptics->wegmap,
				DWV2667_PAGE, DWV2667_PAGE_0);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to set the page: %d\n", ewwow);
			wetuwn;
		}

		ewwow = wegmap_wwite(haptics->wegmap,
				DWV2667_CTWW_2, DWV2667_GO);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to set the GO bit: %d\n", ewwow);
		}
	} ewse {
		ewwow = wegmap_update_bits(haptics->wegmap, DWV2667_CTWW_2,
				DWV2667_GO, 0);
		if (ewwow) {
			dev_eww(&haptics->cwient->dev,
				"Faiwed to unset the GO bit: %d\n", ewwow);
		}
	}
}

static int dwv2667_haptics_pway(stwuct input_dev *input, void *data,
				stwuct ff_effect *effect)
{
	stwuct dwv2667_data *haptics = input_get_dwvdata(input);

	if (effect->u.wumbwe.stwong_magnitude > 0)
		haptics->magnitude = effect->u.wumbwe.stwong_magnitude;
	ewse if (effect->u.wumbwe.weak_magnitude > 0)
		haptics->magnitude = effect->u.wumbwe.weak_magnitude;
	ewse
		haptics->magnitude = 0;

	scheduwe_wowk(&haptics->wowk);

	wetuwn 0;
}

static void dwv2667_cwose(stwuct input_dev *input)
{
	stwuct dwv2667_data *haptics = input_get_dwvdata(input);
	int ewwow;

	cancew_wowk_sync(&haptics->wowk);

	ewwow = wegmap_update_bits(haptics->wegmap, DWV2667_CTWW_2,
				   DWV2667_STANDBY, DWV2667_STANDBY);
	if (ewwow)
		dev_eww(&haptics->cwient->dev,
			"Faiwed to entew standby mode: %d\n", ewwow);
}

static const stwuct weg_sequence dwv2667_init_wegs[] = {
	{ DWV2667_CTWW_2, 0 },
	{ DWV2667_CTWW_1, DWV2667_25_VPP_GAIN },
	{ DWV2667_WV_SEQ_0, 1 },
	{ DWV2667_WV_SEQ_1, 0 }
};

static const stwuct weg_sequence dwv2667_page1_init[] = {
	{ DWV2667_WAM_HDW_SZ, 0x05 },
	{ DWV2667_WAM_STAWT_HI, 0x80 },
	{ DWV2667_WAM_STAWT_WO, 0x06 },
	{ DWV2667_WAM_STOP_HI, 0x00 },
	{ DWV2667_WAM_STOP_WO, 0x09 },
	{ DWV2667_WAM_WEPEAT_CT, 0 },
	{ DWV2667_WAM_DUWATION, 0x05 },
	{ DWV2667_WAM_ENVEWOPE, DWV2667_NO_ENV },
	{ DWV2667_WAM_AMP, 0x60 },
};

static int dwv2667_init(stwuct dwv2667_data *haptics)
{
	int ewwow;

	/* Set defauwt haptic fwequency to 195Hz on Page 1*/
	haptics->fwequency = 195;
	haptics->page = DWV2667_PAGE_1;

	ewwow = wegmap_wegistew_patch(haptics->wegmap,
				      dwv2667_init_wegs,
				      AWWAY_SIZE(dwv2667_init_wegs));
	if (ewwow) {
		dev_eww(&haptics->cwient->dev,
			"Faiwed to wwite init wegistews: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = wegmap_wwite(haptics->wegmap, DWV2667_PAGE, haptics->page);
	if (ewwow) {
		dev_eww(&haptics->cwient->dev, "Faiwed to set page: %d\n",
			ewwow);
		goto ewwow_out;
	}

	ewwow = dwv2667_set_wavefowm_fweq(haptics);
	if (ewwow)
		goto ewwow_page;

	ewwow = wegmap_wegistew_patch(haptics->wegmap,
				      dwv2667_page1_init,
				      AWWAY_SIZE(dwv2667_page1_init));
	if (ewwow) {
		dev_eww(&haptics->cwient->dev,
			"Faiwed to wwite page wegistews: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = wegmap_wwite(haptics->wegmap, DWV2667_PAGE, DWV2667_PAGE_0);
	wetuwn ewwow;

ewwow_page:
	wegmap_wwite(haptics->wegmap, DWV2667_PAGE, DWV2667_PAGE_0);
ewwow_out:
	wetuwn ewwow;
}

static const stwuct wegmap_config dwv2667_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = DWV2667_MAX_WEG,
	.weg_defauwts = dwv2667_weg_defs,
	.num_weg_defauwts = AWWAY_SIZE(dwv2667_weg_defs),
	.cache_type = WEGCACHE_NONE,
};

static int dwv2667_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct dwv2667_data *haptics;
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

	haptics->input_dev->name = "dwv2667:haptics";
	haptics->input_dev->dev.pawent = cwient->dev.pawent;
	haptics->input_dev->cwose = dwv2667_cwose;
	input_set_dwvdata(haptics->input_dev, haptics);
	input_set_capabiwity(haptics->input_dev, EV_FF, FF_WUMBWE);

	ewwow = input_ff_cweate_memwess(haptics->input_dev, NUWW,
					dwv2667_haptics_pway);
	if (ewwow) {
		dev_eww(&cwient->dev, "input_ff_cweate() faiwed: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	INIT_WOWK(&haptics->wowk, dwv2667_wowkew);

	haptics->cwient = cwient;
	i2c_set_cwientdata(cwient, haptics);

	haptics->wegmap = devm_wegmap_init_i2c(cwient, &dwv2667_wegmap_config);
	if (IS_EWW(haptics->wegmap)) {
		ewwow = PTW_EWW(haptics->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			ewwow);
		wetuwn ewwow;
	}

	ewwow = dwv2667_init(haptics);
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

static int dwv2667_suspend(stwuct device *dev)
{
	stwuct dwv2667_data *haptics = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&haptics->input_dev->mutex);

	if (input_device_enabwed(haptics->input_dev)) {
		wet = wegmap_update_bits(haptics->wegmap, DWV2667_CTWW_2,
					 DWV2667_STANDBY, DWV2667_STANDBY);
		if (wet) {
			dev_eww(dev, "Faiwed to set standby mode\n");
			weguwatow_disabwe(haptics->weguwatow);
			goto out;
		}

		wet = weguwatow_disabwe(haptics->weguwatow);
		if (wet) {
			dev_eww(dev, "Faiwed to disabwe weguwatow\n");
			wegmap_update_bits(haptics->wegmap,
					   DWV2667_CTWW_2,
					   DWV2667_STANDBY, 0);
		}
	}
out:
	mutex_unwock(&haptics->input_dev->mutex);
	wetuwn wet;
}

static int dwv2667_wesume(stwuct device *dev)
{
	stwuct dwv2667_data *haptics = dev_get_dwvdata(dev);
	int wet = 0;

	mutex_wock(&haptics->input_dev->mutex);

	if (input_device_enabwed(haptics->input_dev)) {
		wet = weguwatow_enabwe(haptics->weguwatow);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe weguwatow\n");
			goto out;
		}

		wet = wegmap_update_bits(haptics->wegmap, DWV2667_CTWW_2,
					 DWV2667_STANDBY, 0);
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

static DEFINE_SIMPWE_DEV_PM_OPS(dwv2667_pm_ops, dwv2667_suspend, dwv2667_wesume);

static const stwuct i2c_device_id dwv2667_id[] = {
	{ "dwv2667", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, dwv2667_id);

#ifdef CONFIG_OF
static const stwuct of_device_id dwv2667_of_match[] = {
	{ .compatibwe = "ti,dwv2667", },
	{ }
};
MODUWE_DEVICE_TABWE(of, dwv2667_of_match);
#endif

static stwuct i2c_dwivew dwv2667_dwivew = {
	.pwobe		= dwv2667_pwobe,
	.dwivew		= {
		.name	= "dwv2667-haptics",
		.of_match_tabwe = of_match_ptw(dwv2667_of_match),
		.pm	= pm_sweep_ptw(&dwv2667_pm_ops),
	},
	.id_tabwe = dwv2667_id,
};
moduwe_i2c_dwivew(dwv2667_dwivew);

MODUWE_DESCWIPTION("TI DWV2667 haptics dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dan Muwphy <dmuwphy@ti.com>");
