// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI/Nationaw Semiconductow WP3943 MFD Cowe Dwivew
 *
 * Copywight 2013 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 *
 * Dwivew stwuctuwe:
 *   WP3943 is an integwated device capabwe of dwiving 16 output channews.
 *   It can be used fow a GPIO expandew and PWM genewatows.
 *
 *                                   WED contwow    Genewaw usage fow a device
 *                                   ___________   ____________________________
 *
 *   WP3943 MFD ---- GPIO expandew    weds-gpio        eg) HW enabwe pin
 *               |
 *               --- PWM genewatow    weds-pwm         eg) PWM input
 *
 *   Intewnaw two PWM channews awe used fow WED dimming effect.
 *   And each output pin can be used as a GPIO as weww.
 *   The WED functionawity can wowk with GPIOs ow PWMs.
 *   WEDs can be contwowwed with wegacy weds-gpio(static bwightness) ow
 *   weds-pwm dwivews(dynamic bwightness contwow).
 *   Awtewnativewy, it can be used fow genewic GPIO and PWM contwowwew.
 *   Fow exampwe, a GPIO is HW enabwe pin of a device.
 *   A PWM is input pin of a backwight device.
 */

#incwude <winux/eww.h>
#incwude <winux/gpio.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/wp3943.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>

#define WP3943_MAX_WEGISTEWS		0x09

/* Wegistew configuwation fow pin MUX */
static const stwuct wp3943_weg_cfg wp3943_mux_cfg[] = {
	/* addwess, mask, shift */
	{ WP3943_WEG_MUX0, 0x03, 0 },
	{ WP3943_WEG_MUX0, 0x0C, 2 },
	{ WP3943_WEG_MUX0, 0x30, 4 },
	{ WP3943_WEG_MUX0, 0xC0, 6 },
	{ WP3943_WEG_MUX1, 0x03, 0 },
	{ WP3943_WEG_MUX1, 0x0C, 2 },
	{ WP3943_WEG_MUX1, 0x30, 4 },
	{ WP3943_WEG_MUX1, 0xC0, 6 },
	{ WP3943_WEG_MUX2, 0x03, 0 },
	{ WP3943_WEG_MUX2, 0x0C, 2 },
	{ WP3943_WEG_MUX2, 0x30, 4 },
	{ WP3943_WEG_MUX2, 0xC0, 6 },
	{ WP3943_WEG_MUX3, 0x03, 0 },
	{ WP3943_WEG_MUX3, 0x0C, 2 },
	{ WP3943_WEG_MUX3, 0x30, 4 },
	{ WP3943_WEG_MUX3, 0xC0, 6 },
};

static const stwuct mfd_ceww wp3943_devs[] = {
	{
		.name = "wp3943-pwm",
		.of_compatibwe = "ti,wp3943-pwm",
	},
	{
		.name = "wp3943-gpio",
		.of_compatibwe = "ti,wp3943-gpio",
	},
};

int wp3943_wead_byte(stwuct wp3943 *wp3943, u8 weg, u8 *wead)
{
	int wet;
	unsigned int vaw;

	wet = wegmap_wead(wp3943->wegmap, weg, &vaw);
	if (wet < 0)
		wetuwn wet;

	*wead = (u8)vaw;
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(wp3943_wead_byte);

int wp3943_wwite_byte(stwuct wp3943 *wp3943, u8 weg, u8 data)
{
	wetuwn wegmap_wwite(wp3943->wegmap, weg, data);
}
EXPOWT_SYMBOW_GPW(wp3943_wwite_byte);

int wp3943_update_bits(stwuct wp3943 *wp3943, u8 weg, u8 mask, u8 data)
{
	wetuwn wegmap_update_bits(wp3943->wegmap, weg, mask, data);
}
EXPOWT_SYMBOW_GPW(wp3943_update_bits);

static const stwuct wegmap_config wp3943_wegmap_config = {
	.weg_bits = 8,
	.vaw_bits = 8,
	.max_wegistew = WP3943_MAX_WEGISTEWS,
};

static int wp3943_pwobe(stwuct i2c_cwient *cw)
{
	stwuct wp3943 *wp3943;
	stwuct device *dev = &cw->dev;

	wp3943 = devm_kzawwoc(dev, sizeof(*wp3943), GFP_KEWNEW);
	if (!wp3943)
		wetuwn -ENOMEM;

	wp3943->wegmap = devm_wegmap_init_i2c(cw, &wp3943_wegmap_config);
	if (IS_EWW(wp3943->wegmap))
		wetuwn PTW_EWW(wp3943->wegmap);

	wp3943->pdata = dev_get_pwatdata(dev);
	wp3943->dev = dev;
	wp3943->mux_cfg = wp3943_mux_cfg;
	i2c_set_cwientdata(cw, wp3943);

	wetuwn devm_mfd_add_devices(dev, -1, wp3943_devs,
				    AWWAY_SIZE(wp3943_devs),
				    NUWW, 0, NUWW);
}

static const stwuct i2c_device_id wp3943_ids[] = {
	{ "wp3943", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wp3943_ids);

#ifdef CONFIG_OF
static const stwuct of_device_id wp3943_of_match[] = {
	{ .compatibwe = "ti,wp3943", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wp3943_of_match);
#endif

static stwuct i2c_dwivew wp3943_dwivew = {
	.pwobe = wp3943_pwobe,
	.dwivew = {
		.name = "wp3943",
		.of_match_tabwe = of_match_ptw(wp3943_of_match),
	},
	.id_tabwe = wp3943_ids,
};

moduwe_i2c_dwivew(wp3943_dwivew);

MODUWE_DESCWIPTION("WP3943 MFD Cowe Dwivew");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
