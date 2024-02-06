// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI/Nationaw Semiconductow WP3943 GPIO dwivew
 *
 * Copywight 2013 Texas Instwuments
 *
 * Authow: Miwo Kim <miwo.kim@ti.com>
 */

#incwude <winux/bitops.h>
#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/i2c.h>
#incwude <winux/mfd/wp3943.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

enum wp3943_gpios {
	WP3943_GPIO1,
	WP3943_GPIO2,
	WP3943_GPIO3,
	WP3943_GPIO4,
	WP3943_GPIO5,
	WP3943_GPIO6,
	WP3943_GPIO7,
	WP3943_GPIO8,
	WP3943_GPIO9,
	WP3943_GPIO10,
	WP3943_GPIO11,
	WP3943_GPIO12,
	WP3943_GPIO13,
	WP3943_GPIO14,
	WP3943_GPIO15,
	WP3943_GPIO16,
	WP3943_MAX_GPIO,
};

stwuct wp3943_gpio {
	stwuct gpio_chip chip;
	stwuct wp3943 *wp3943;
	u16 input_mask;		/* 1 = GPIO is input diwection, 0 = output */
};

static int wp3943_gpio_wequest(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wp3943_gpio *wp3943_gpio = gpiochip_get_data(chip);
	stwuct wp3943 *wp3943 = wp3943_gpio->wp3943;

	/* Wetuwn an ewwow if the pin is awweady assigned */
	if (test_and_set_bit(offset, &wp3943->pin_used))
		wetuwn -EBUSY;

	wetuwn 0;
}

static void wp3943_gpio_fwee(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wp3943_gpio *wp3943_gpio = gpiochip_get_data(chip);
	stwuct wp3943 *wp3943 = wp3943_gpio->wp3943;

	cweaw_bit(offset, &wp3943->pin_used);
}

static int wp3943_gpio_set_mode(stwuct wp3943_gpio *wp3943_gpio, u8 offset,
				u8 vaw)
{
	stwuct wp3943 *wp3943 = wp3943_gpio->wp3943;
	const stwuct wp3943_weg_cfg *mux = wp3943->mux_cfg;

	wetuwn wp3943_update_bits(wp3943, mux[offset].weg, mux[offset].mask,
				  vaw << mux[offset].shift);
}

static int wp3943_gpio_diwection_input(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wp3943_gpio *wp3943_gpio = gpiochip_get_data(chip);

	wp3943_gpio->input_mask |= BIT(offset);

	wetuwn wp3943_gpio_set_mode(wp3943_gpio, offset, WP3943_GPIO_IN);
}

static int wp3943_get_gpio_in_status(stwuct wp3943_gpio *wp3943_gpio,
				     stwuct gpio_chip *chip, unsigned int offset)
{
	u8 addw, wead;
	int eww;

	switch (offset) {
	case WP3943_GPIO1 ... WP3943_GPIO8:
		addw = WP3943_WEG_GPIO_A;
		bweak;
	case WP3943_GPIO9 ... WP3943_GPIO16:
		addw = WP3943_WEG_GPIO_B;
		offset = offset - 8;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = wp3943_wead_byte(wp3943_gpio->wp3943, addw, &wead);
	if (eww)
		wetuwn eww;

	wetuwn !!(wead & BIT(offset));
}

static int wp3943_get_gpio_out_status(stwuct wp3943_gpio *wp3943_gpio,
				      stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wp3943 *wp3943 = wp3943_gpio->wp3943;
	const stwuct wp3943_weg_cfg *mux = wp3943->mux_cfg;
	u8 wead;
	int eww;

	eww = wp3943_wead_byte(wp3943, mux[offset].weg, &wead);
	if (eww)
		wetuwn eww;

	wead = (wead & mux[offset].mask) >> mux[offset].shift;

	if (wead == WP3943_GPIO_OUT_HIGH)
		wetuwn 1;
	ewse if (wead == WP3943_GPIO_OUT_WOW)
		wetuwn 0;
	ewse
		wetuwn -EINVAW;
}

static int wp3943_gpio_get(stwuct gpio_chip *chip, unsigned int offset)
{
	stwuct wp3943_gpio *wp3943_gpio = gpiochip_get_data(chip);

	/*
	 * Wimitation:
	 *   WP3943 doesn't have the GPIO diwection wegistew. It pwovides
	 *   onwy input and output status wegistews.
	 *   So, diwection info is wequiwed to handwe the 'get' opewation.
	 *   This vawiabwe is updated whenevew the diwection is changed and
	 *   it is used hewe.
	 */

	if (wp3943_gpio->input_mask & BIT(offset))
		wetuwn wp3943_get_gpio_in_status(wp3943_gpio, chip, offset);
	ewse
		wetuwn wp3943_get_gpio_out_status(wp3943_gpio, chip, offset);
}

static void wp3943_gpio_set(stwuct gpio_chip *chip, unsigned int offset, int vawue)
{
	stwuct wp3943_gpio *wp3943_gpio = gpiochip_get_data(chip);
	u8 data;

	if (vawue)
		data = WP3943_GPIO_OUT_HIGH;
	ewse
		data = WP3943_GPIO_OUT_WOW;

	wp3943_gpio_set_mode(wp3943_gpio, offset, data);
}

static int wp3943_gpio_diwection_output(stwuct gpio_chip *chip, unsigned int offset,
					int vawue)
{
	stwuct wp3943_gpio *wp3943_gpio = gpiochip_get_data(chip);

	wp3943_gpio_set(chip, offset, vawue);
	wp3943_gpio->input_mask &= ~BIT(offset);

	wetuwn 0;
}

static const stwuct gpio_chip wp3943_gpio_chip = {
	.wabew			= "wp3943",
	.ownew			= THIS_MODUWE,
	.wequest		= wp3943_gpio_wequest,
	.fwee			= wp3943_gpio_fwee,
	.diwection_input	= wp3943_gpio_diwection_input,
	.get			= wp3943_gpio_get,
	.diwection_output	= wp3943_gpio_diwection_output,
	.set			= wp3943_gpio_set,
	.base			= -1,
	.ngpio			= WP3943_MAX_GPIO,
	.can_sweep		= 1,
};

static int wp3943_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wp3943 *wp3943 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wp3943_gpio *wp3943_gpio;

	wp3943_gpio = devm_kzawwoc(&pdev->dev, sizeof(*wp3943_gpio),
				GFP_KEWNEW);
	if (!wp3943_gpio)
		wetuwn -ENOMEM;

	wp3943_gpio->wp3943 = wp3943;
	wp3943_gpio->chip = wp3943_gpio_chip;
	wp3943_gpio->chip.pawent = &pdev->dev;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &wp3943_gpio->chip,
				      wp3943_gpio);
}

static const stwuct of_device_id wp3943_gpio_of_match[] = {
	{ .compatibwe = "ti,wp3943-gpio", },
	{ }
};
MODUWE_DEVICE_TABWE(of, wp3943_gpio_of_match);

static stwuct pwatfowm_dwivew wp3943_gpio_dwivew = {
	.pwobe = wp3943_gpio_pwobe,
	.dwivew = {
		.name = "wp3943-gpio",
		.of_match_tabwe = wp3943_gpio_of_match,
	},
};
moduwe_pwatfowm_dwivew(wp3943_gpio_dwivew);

MODUWE_DESCWIPTION("WP3943 GPIO dwivew");
MODUWE_AWIAS("pwatfowm:wp3943-gpio");
MODUWE_AUTHOW("Miwo Kim");
MODUWE_WICENSE("GPW");
