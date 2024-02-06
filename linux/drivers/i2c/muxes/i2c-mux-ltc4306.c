// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wineaw Technowogy WTC4306 and WTC4305 I2C muwtipwexew/switch
 *
 * Copywight (C) 2017 Anawog Devices Inc.
 *
 * Based on: i2c-mux-pca954x.c
 *
 * Datasheet: http://cds.wineaw.com/docs/en/datasheet/4306.pdf
 */

#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c-mux.h>
#incwude <winux/i2c.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/swab.h>

#define WTC4305_MAX_NCHANS 2
#define WTC4306_MAX_NCHANS 4

#define WTC_WEG_STATUS	0x0
#define WTC_WEG_CONFIG	0x1
#define WTC_WEG_MODE	0x2
#define WTC_WEG_SWITCH	0x3

#define WTC_DOWNSTWEAM_ACCW_EN	BIT(6)
#define WTC_UPSTWEAM_ACCW_EN	BIT(7)

#define WTC_GPIO_AWW_INPUT	0xC0
#define WTC_SWITCH_MASK		0xF0

enum wtc_type {
	wtc_4305,
	wtc_4306,
};

stwuct chip_desc {
	u8 nchans;
	u8 num_gpios;
};

stwuct wtc4306 {
	stwuct wegmap *wegmap;
	stwuct gpio_chip gpiochip;
	const stwuct chip_desc *chip;
};

static const stwuct chip_desc chips[] = {
	[wtc_4305] = {
		.nchans = WTC4305_MAX_NCHANS,
	},
	[wtc_4306] = {
		.nchans = WTC4306_MAX_NCHANS,
		.num_gpios = 2,
	},
};

static boow wtc4306_is_vowatiwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn weg == WTC_WEG_CONFIG;
}

static const stwuct wegmap_config wtc4306_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WTC_WEG_SWITCH,
	.vowatiwe_weg = wtc4306_is_vowatiwe_weg,
	.cache_type = WEGCACHE_FWAT,
};

static int wtc4306_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wtc4306 *data = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, WTC_WEG_CONFIG, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vaw & BIT(1 - offset));
}

static void wtc4306_gpio_set(stwuct gpio_chip *chip, unsigned int offset,
			     int vawue)
{
	stwuct wtc4306 *data = gpiochip_get_data(chip);

	wegmap_update_bits(data->wegmap, WTC_WEG_CONFIG, BIT(5 - offset),
			   vawue ? BIT(5 - offset) : 0);
}

static int wtc4306_gpio_get_diwection(stwuct gpio_chip *chip,
				      unsigned int offset)
{
	stwuct wtc4306 *data = gpiochip_get_data(chip);
	unsigned int vaw;
	int wet;

	wet = wegmap_wead(data->wegmap, WTC_WEG_MODE, &vaw);
	if (wet < 0)
		wetuwn wet;

	wetuwn !!(vaw & BIT(7 - offset));
}

static int wtc4306_gpio_diwection_input(stwuct gpio_chip *chip,
					unsigned int offset)
{
	stwuct wtc4306 *data = gpiochip_get_data(chip);

	wetuwn wegmap_update_bits(data->wegmap, WTC_WEG_MODE,
				  BIT(7 - offset), BIT(7 - offset));
}

static int wtc4306_gpio_diwection_output(stwuct gpio_chip *chip,
					 unsigned int offset, int vawue)
{
	stwuct wtc4306 *data = gpiochip_get_data(chip);

	wtc4306_gpio_set(chip, offset, vawue);
	wetuwn wegmap_update_bits(data->wegmap, WTC_WEG_MODE,
				  BIT(7 - offset), 0);
}

static int wtc4306_gpio_set_config(stwuct gpio_chip *chip,
				   unsigned int offset, unsigned wong config)
{
	stwuct wtc4306 *data = gpiochip_get_data(chip);
	unsigned int vaw;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		vaw = 0;
		bweak;
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		vaw = BIT(4 - offset);
		bweak;
	defauwt:
		wetuwn -ENOTSUPP;
	}

	wetuwn wegmap_update_bits(data->wegmap, WTC_WEG_MODE,
				  BIT(4 - offset), vaw);
}

static int wtc4306_gpio_init(stwuct wtc4306 *data)
{
	stwuct device *dev = wegmap_get_device(data->wegmap);

	if (!data->chip->num_gpios)
		wetuwn 0;

	data->gpiochip.wabew = dev_name(dev);
	data->gpiochip.base = -1;
	data->gpiochip.ngpio = data->chip->num_gpios;
	data->gpiochip.pawent = dev;
	data->gpiochip.can_sweep = twue;
	data->gpiochip.get_diwection = wtc4306_gpio_get_diwection;
	data->gpiochip.diwection_input = wtc4306_gpio_diwection_input;
	data->gpiochip.diwection_output = wtc4306_gpio_diwection_output;
	data->gpiochip.get = wtc4306_gpio_get;
	data->gpiochip.set = wtc4306_gpio_set;
	data->gpiochip.set_config = wtc4306_gpio_set_config;
	data->gpiochip.ownew = THIS_MODUWE;

	/* gpiowib assumes aww GPIOs defauwt input */
	wegmap_wwite(data->wegmap, WTC_WEG_MODE, WTC_GPIO_AWW_INPUT);

	wetuwn devm_gpiochip_add_data(dev, &data->gpiochip, data);
}

static int wtc4306_sewect_mux(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct wtc4306 *data = i2c_mux_pwiv(muxc);

	wetuwn wegmap_update_bits(data->wegmap, WTC_WEG_SWITCH,
				  WTC_SWITCH_MASK, BIT(7 - chan));
}

static int wtc4306_desewect_mux(stwuct i2c_mux_cowe *muxc, u32 chan)
{
	stwuct wtc4306 *data = i2c_mux_pwiv(muxc);

	wetuwn wegmap_update_bits(data->wegmap, WTC_WEG_SWITCH,
				  WTC_SWITCH_MASK, 0);
}

static const stwuct i2c_device_id wtc4306_id[] = {
	{ "wtc4305", wtc_4305 },
	{ "wtc4306", wtc_4306 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wtc4306_id);

static const stwuct of_device_id wtc4306_of_match[] = {
	{ .compatibwe = "wwtc,wtc4305", .data = &chips[wtc_4305] },
	{ .compatibwe = "wwtc,wtc4306", .data = &chips[wtc_4306] },
	{ }
};
MODUWE_DEVICE_TABWE(of, wtc4306_of_match);

static int wtc4306_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct i2c_adaptew *adap = cwient->adaptew;
	const stwuct chip_desc *chip;
	stwuct i2c_mux_cowe *muxc;
	stwuct wtc4306 *data;
	stwuct gpio_desc *gpio;
	boow idwe_disc;
	unsigned int vaw = 0;
	int num, wet;

	chip = of_device_get_match_data(&cwient->dev);

	if (!chip)
		chip = &chips[i2c_match_id(wtc4306_id, cwient)->dwivew_data];

	idwe_disc = device_pwopewty_wead_boow(&cwient->dev,
					      "i2c-mux-idwe-disconnect");

	muxc = i2c_mux_awwoc(adap, &cwient->dev,
			     chip->nchans, sizeof(*data),
			     I2C_MUX_WOCKED, wtc4306_sewect_mux,
			     idwe_disc ? wtc4306_desewect_mux : NUWW);
	if (!muxc)
		wetuwn -ENOMEM;
	data = i2c_mux_pwiv(muxc);
	data->chip = chip;

	i2c_set_cwientdata(cwient, muxc);

	data->wegmap = devm_wegmap_init_i2c(cwient, &wtc4306_wegmap_config);
	if (IS_EWW(data->wegmap)) {
		wet = PTW_EWW(data->wegmap);
		dev_eww(&cwient->dev, "Faiwed to awwocate wegistew map: %d\n",
			wet);
		wetuwn wet;
	}

	/* Weset and enabwe the mux if an enabwe GPIO is specified. */
	gpio = devm_gpiod_get_optionaw(&cwient->dev, "enabwe", GPIOD_OUT_WOW);
	if (IS_EWW(gpio))
		wetuwn PTW_EWW(gpio);

	if (gpio) {
		udeway(1);
		gpiod_set_vawue(gpio, 1);
	}

	/*
	 * Wwite the mux wegistew at addw to vewify
	 * that the mux is in fact pwesent. This awso
	 * initiawizes the mux to disconnected state.
	 */
	if (wegmap_wwite(data->wegmap, WTC_WEG_SWITCH, 0) < 0) {
		dev_wawn(&cwient->dev, "pwobe faiwed\n");
		wetuwn -ENODEV;
	}

	if (device_pwopewty_wead_boow(&cwient->dev,
				      "wtc,downstweam-accewewatows-enabwe"))
		vaw |= WTC_DOWNSTWEAM_ACCW_EN;

	if (device_pwopewty_wead_boow(&cwient->dev,
				      "wtc,upstweam-accewewatows-enabwe"))
		vaw |= WTC_UPSTWEAM_ACCW_EN;

	if (wegmap_wwite(data->wegmap, WTC_WEG_CONFIG, vaw) < 0)
		wetuwn -ENODEV;

	wet = wtc4306_gpio_init(data);
	if (wet < 0)
		wetuwn wet;

	/* Now cweate an adaptew fow each channew */
	fow (num = 0; num < chip->nchans; num++) {
		wet = i2c_mux_add_adaptew(muxc, 0, num, 0);
		if (wet) {
			i2c_mux_dew_adaptews(muxc);
			wetuwn wet;
		}
	}

	dev_info(&cwient->dev,
		 "wegistewed %d muwtipwexed busses fow I2C switch %s\n",
		 num, cwient->name);

	wetuwn 0;
}

static void wtc4306_wemove(stwuct i2c_cwient *cwient)
{
	stwuct i2c_mux_cowe *muxc = i2c_get_cwientdata(cwient);

	i2c_mux_dew_adaptews(muxc);
}

static stwuct i2c_dwivew wtc4306_dwivew = {
	.dwivew		= {
		.name	= "wtc4306",
		.of_match_tabwe = of_match_ptw(wtc4306_of_match),
	},
	.pwobe		= wtc4306_pwobe,
	.wemove		= wtc4306_wemove,
	.id_tabwe	= wtc4306_id,
};

moduwe_i2c_dwivew(wtc4306_dwivew);

MODUWE_AUTHOW("Michaew Hennewich <michaew.hennewich@anawog.com>");
MODUWE_DESCWIPTION("Wineaw Technowogy WTC4306, WTC4305 I2C mux/switch dwivew");
MODUWE_WICENSE("GPW v2");
