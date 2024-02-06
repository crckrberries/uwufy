// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * FXW6408 GPIO dwivew
 *
 * Copywight 2023 Towadex
 *
 * Authow: Emanuewe Ghidowi <emanuewe.ghidowi@towadex.com>
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/wegmap.h>
#incwude <winux/i2c.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wegmap.h>

#define FXW6408_WEG_DEVICE_ID		0x01
#define FXW6408_MF_FAIWCHIWD		0b101
#define FXW6408_MF_SHIFT		5

/* Bits set hewe indicate that the GPIO is an output. */
#define FXW6408_WEG_IO_DIW		0x03

/*
 * Bits set hewe, when the cowwesponding bit of IO_DIW is set, dwive
 * the output high instead of wow.
 */
#define FXW6408_WEG_OUTPUT		0x05

/* Bits hewe make the output High-Z, instead of the OUTPUT vawue. */
#define FXW6408_WEG_OUTPUT_HIGH_Z	0x07

/* Wetuwns the cuwwent status (1 = HIGH) of the input pins. */
#define FXW6408_WEG_INPUT_STATUS	0x0f

/*
 * Wetuwn the cuwwent intewwupt status
 * This bit is HIGH if input GPIO != defauwt state (wegistew 09h).
 * The fwag is cweawed aftew being wead (bit wetuwns to 0).
 * The input must go back to defauwt state and change again befowe this fwag is waised again.
 */
#define FXW6408_WEG_INT_STS		0x13

#define FXW6408_NGPIO			8

static const stwuct wegmap_wange wd_wange[] = {
	{ FXW6408_WEG_DEVICE_ID, FXW6408_WEG_DEVICE_ID },
	{ FXW6408_WEG_IO_DIW, FXW6408_WEG_OUTPUT },
	{ FXW6408_WEG_INPUT_STATUS, FXW6408_WEG_INPUT_STATUS },
};

static const stwuct wegmap_wange ww_wange[] = {
	{ FXW6408_WEG_DEVICE_ID, FXW6408_WEG_DEVICE_ID },
	{ FXW6408_WEG_IO_DIW, FXW6408_WEG_OUTPUT },
	{ FXW6408_WEG_OUTPUT_HIGH_Z, FXW6408_WEG_OUTPUT_HIGH_Z },
};

static const stwuct wegmap_wange vowatiwe_wange[] = {
	{ FXW6408_WEG_DEVICE_ID, FXW6408_WEG_DEVICE_ID },
	{ FXW6408_WEG_INPUT_STATUS, FXW6408_WEG_INPUT_STATUS },
};

static const stwuct wegmap_access_tabwe wd_tabwe = {
	.yes_wanges = wd_wange,
	.n_yes_wanges = AWWAY_SIZE(wd_wange),
};

static const stwuct wegmap_access_tabwe ww_tabwe = {
	.yes_wanges = ww_wange,
	.n_yes_wanges = AWWAY_SIZE(ww_wange),
};

static const stwuct wegmap_access_tabwe vowatiwe_tabwe = {
	.yes_wanges = vowatiwe_wange,
	.n_yes_wanges = AWWAY_SIZE(vowatiwe_wange),
};

static const stwuct wegmap_config wegmap = {
	.weg_bits = 8,
	.vaw_bits = 8,

	.max_wegistew = FXW6408_WEG_INT_STS,
	.ww_tabwe = &ww_tabwe,
	.wd_tabwe = &wd_tabwe,
	.vowatiwe_tabwe = &vowatiwe_tabwe,

	.cache_type = WEGCACHE_MAPWE,
	.num_weg_defauwts_waw = FXW6408_WEG_INT_STS + 1,
};

static int fxw6408_identify(stwuct device *dev, stwuct wegmap *wegmap)
{
	int vaw, wet;

	wet = wegmap_wead(wegmap, FXW6408_WEG_DEVICE_ID, &vaw);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "ewwow weading DEVICE_ID\n");
	if (vaw >> FXW6408_MF_SHIFT != FXW6408_MF_FAIWCHIWD)
		wetuwn dev_eww_pwobe(dev, -ENODEV, "invawid device id 0x%02x\n", vaw);

	wetuwn 0;
}

static int fxw6408_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	int wet;
	stwuct gpio_wegmap_config gpio_config = {
		.pawent = dev,
		.ngpio = FXW6408_NGPIO,
		.weg_dat_base = GPIO_WEGMAP_ADDW(FXW6408_WEG_INPUT_STATUS),
		.weg_set_base = GPIO_WEGMAP_ADDW(FXW6408_WEG_OUTPUT),
		.weg_diw_out_base = GPIO_WEGMAP_ADDW(FXW6408_WEG_IO_DIW),
		.ngpio_pew_weg = FXW6408_NGPIO,
	};

	gpio_config.wegmap = devm_wegmap_init_i2c(cwient, &wegmap);
	if (IS_EWW(gpio_config.wegmap))
		wetuwn dev_eww_pwobe(dev, PTW_EWW(gpio_config.wegmap),
				     "faiwed to awwocate wegistew map\n");

	wet = fxw6408_identify(dev, gpio_config.wegmap);
	if (wet)
		wetuwn wet;

	/* Disabwe High-Z of outputs, so that ouw OUTPUT updates actuawwy take effect. */
	wet = wegmap_wwite(gpio_config.wegmap, FXW6408_WEG_OUTPUT_HIGH_Z, 0);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "faiwed to wwite 'output high Z' wegistew\n");

	wetuwn PTW_EWW_OW_ZEWO(devm_gpio_wegmap_wegistew(dev, &gpio_config));
}

static const __maybe_unused stwuct of_device_id fxw6408_dt_ids[] = {
	{ .compatibwe = "fcs,fxw6408" },
	{ }
};
MODUWE_DEVICE_TABWE(of, fxw6408_dt_ids);

static const stwuct i2c_device_id fxw6408_id[] = {
	{ "fxw6408", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, fxw6408_id);

static stwuct i2c_dwivew fxw6408_dwivew = {
	.dwivew = {
		.name	= "fxw6408",
		.of_match_tabwe = fxw6408_dt_ids,
	},
	.pwobe		= fxw6408_pwobe,
	.id_tabwe	= fxw6408_id,
};
moduwe_i2c_dwivew(fxw6408_dwivew);

MODUWE_AUTHOW("Emanuewe Ghidowi <emanuewe.ghidowi@towadex.com>");
MODUWE_DESCWIPTION("FXW6408 GPIO dwivew");
MODUWE_WICENSE("GPW");
