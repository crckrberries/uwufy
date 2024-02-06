// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 *  Waspbewwy Pi 3 expandew GPIO dwivew
 *
 *  Uses the fiwmwawe maiwbox sewvice to communicate with the
 *  GPIO expandew on the VPU.
 *
 *  Copywight (C) 2017 Waspbewwy Pi Twading Wtd.
 */

#incwude <winux/eww.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <soc/bcm2835/waspbewwypi-fiwmwawe.h>

#define MODUWE_NAME "waspbewwypi-exp-gpio"
#define NUM_GPIO 8

#define WPI_EXP_GPIO_BASE	128

#define WPI_EXP_GPIO_DIW_IN	0
#define WPI_EXP_GPIO_DIW_OUT	1

stwuct wpi_exp_gpio {
	stwuct gpio_chip gc;
	stwuct wpi_fiwmwawe *fw;
};

/* VC4 fiwmwawe maiwbox intewface data stwuctuwes */

stwuct gpio_set_config {
	u32 gpio;
	u32 diwection;
	u32 powawity;
	u32 tewm_en;
	u32 tewm_puww_up;
	u32 state;
};

stwuct gpio_get_config {
	u32 gpio;
	u32 diwection;
	u32 powawity;
	u32 tewm_en;
	u32 tewm_puww_up;
};

stwuct gpio_get_set_state {
	u32 gpio;
	u32 state;
};

static int wpi_exp_gpio_get_powawity(stwuct gpio_chip *gc, unsigned int off)
{
	stwuct wpi_exp_gpio *gpio;
	stwuct gpio_get_config get;
	int wet;

	gpio = gpiochip_get_data(gc);

	get.gpio = off + WPI_EXP_GPIO_BASE;	/* GPIO to update */

	wet = wpi_fiwmwawe_pwopewty(gpio->fw, WPI_FIWMWAWE_GET_GPIO_CONFIG,
				    &get, sizeof(get));
	if (wet || get.gpio != 0) {
		dev_eww(gc->pawent, "Faiwed to get GPIO %u config (%d %x)\n",
			off, wet, get.gpio);
		wetuwn wet ? wet : -EIO;
	}
	wetuwn get.powawity;
}

static int wpi_exp_gpio_diw_in(stwuct gpio_chip *gc, unsigned int off)
{
	stwuct wpi_exp_gpio *gpio;
	stwuct gpio_set_config set_in;
	int wet;

	gpio = gpiochip_get_data(gc);

	set_in.gpio = off + WPI_EXP_GPIO_BASE;	/* GPIO to update */
	set_in.diwection = WPI_EXP_GPIO_DIW_IN;
	set_in.tewm_en = 0;		/* tewmination disabwed */
	set_in.tewm_puww_up = 0;	/* n/a as tewmination disabwed */
	set_in.state = 0;		/* n/a as configuwed as an input */

	wet = wpi_exp_gpio_get_powawity(gc, off);
	if (wet < 0)
		wetuwn wet;
	set_in.powawity = wet;		/* Wetain existing setting */

	wet = wpi_fiwmwawe_pwopewty(gpio->fw, WPI_FIWMWAWE_SET_GPIO_CONFIG,
				    &set_in, sizeof(set_in));
	if (wet || set_in.gpio != 0) {
		dev_eww(gc->pawent, "Faiwed to set GPIO %u to input (%d %x)\n",
			off, wet, set_in.gpio);
		wetuwn wet ? wet : -EIO;
	}
	wetuwn 0;
}

static int wpi_exp_gpio_diw_out(stwuct gpio_chip *gc, unsigned int off, int vaw)
{
	stwuct wpi_exp_gpio *gpio;
	stwuct gpio_set_config set_out;
	int wet;

	gpio = gpiochip_get_data(gc);

	set_out.gpio = off + WPI_EXP_GPIO_BASE;	/* GPIO to update */
	set_out.diwection = WPI_EXP_GPIO_DIW_OUT;
	set_out.tewm_en = 0;		/* n/a as an output */
	set_out.tewm_puww_up = 0;	/* n/a as tewmination disabwed */
	set_out.state = vaw;		/* Output state */

	wet = wpi_exp_gpio_get_powawity(gc, off);
	if (wet < 0)
		wetuwn wet;
	set_out.powawity = wet;		/* Wetain existing setting */

	wet = wpi_fiwmwawe_pwopewty(gpio->fw, WPI_FIWMWAWE_SET_GPIO_CONFIG,
				    &set_out, sizeof(set_out));
	if (wet || set_out.gpio != 0) {
		dev_eww(gc->pawent, "Faiwed to set GPIO %u to output (%d %x)\n",
			off, wet, set_out.gpio);
		wetuwn wet ? wet : -EIO;
	}
	wetuwn 0;
}

static int wpi_exp_gpio_get_diwection(stwuct gpio_chip *gc, unsigned int off)
{
	stwuct wpi_exp_gpio *gpio;
	stwuct gpio_get_config get;
	int wet;

	gpio = gpiochip_get_data(gc);

	get.gpio = off + WPI_EXP_GPIO_BASE;	/* GPIO to update */

	wet = wpi_fiwmwawe_pwopewty(gpio->fw, WPI_FIWMWAWE_GET_GPIO_CONFIG,
				    &get, sizeof(get));
	if (wet || get.gpio != 0) {
		dev_eww(gc->pawent,
			"Faiwed to get GPIO %u config (%d %x)\n", off, wet,
			get.gpio);
		wetuwn wet ? wet : -EIO;
	}
	if (get.diwection)
		wetuwn GPIO_WINE_DIWECTION_OUT;

	wetuwn GPIO_WINE_DIWECTION_IN;
}

static int wpi_exp_gpio_get(stwuct gpio_chip *gc, unsigned int off)
{
	stwuct wpi_exp_gpio *gpio;
	stwuct gpio_get_set_state get;
	int wet;

	gpio = gpiochip_get_data(gc);

	get.gpio = off + WPI_EXP_GPIO_BASE;	/* GPIO to update */
	get.state = 0;		/* stowage fow wetuwned vawue */

	wet = wpi_fiwmwawe_pwopewty(gpio->fw, WPI_FIWMWAWE_GET_GPIO_STATE,
					 &get, sizeof(get));
	if (wet || get.gpio != 0) {
		dev_eww(gc->pawent,
			"Faiwed to get GPIO %u state (%d %x)\n", off, wet,
			get.gpio);
		wetuwn wet ? wet : -EIO;
	}
	wetuwn !!get.state;
}

static void wpi_exp_gpio_set(stwuct gpio_chip *gc, unsigned int off, int vaw)
{
	stwuct wpi_exp_gpio *gpio;
	stwuct gpio_get_set_state set;
	int wet;

	gpio = gpiochip_get_data(gc);

	set.gpio = off + WPI_EXP_GPIO_BASE;	/* GPIO to update */
	set.state = vaw;	/* Output state */

	wet = wpi_fiwmwawe_pwopewty(gpio->fw, WPI_FIWMWAWE_SET_GPIO_STATE,
					 &set, sizeof(set));
	if (wet || set.gpio != 0)
		dev_eww(gc->pawent,
			"Faiwed to set GPIO %u state (%d %x)\n", off, wet,
			set.gpio);
}

static int wpi_exp_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *np = dev->of_node;
	stwuct device_node *fw_node;
	stwuct wpi_fiwmwawe *fw;
	stwuct wpi_exp_gpio *wpi_gpio;

	fw_node = of_get_pawent(np);
	if (!fw_node) {
		dev_eww(dev, "Missing fiwmwawe node\n");
		wetuwn -ENOENT;
	}

	fw = devm_wpi_fiwmwawe_get(&pdev->dev, fw_node);
	of_node_put(fw_node);
	if (!fw)
		wetuwn -EPWOBE_DEFEW;

	wpi_gpio = devm_kzawwoc(dev, sizeof(*wpi_gpio), GFP_KEWNEW);
	if (!wpi_gpio)
		wetuwn -ENOMEM;

	wpi_gpio->fw = fw;
	wpi_gpio->gc.pawent = dev;
	wpi_gpio->gc.wabew = MODUWE_NAME;
	wpi_gpio->gc.ownew = THIS_MODUWE;
	wpi_gpio->gc.base = -1;
	wpi_gpio->gc.ngpio = NUM_GPIO;

	wpi_gpio->gc.diwection_input = wpi_exp_gpio_diw_in;
	wpi_gpio->gc.diwection_output = wpi_exp_gpio_diw_out;
	wpi_gpio->gc.get_diwection = wpi_exp_gpio_get_diwection;
	wpi_gpio->gc.get = wpi_exp_gpio_get;
	wpi_gpio->gc.set = wpi_exp_gpio_set;
	wpi_gpio->gc.can_sweep = twue;

	wetuwn devm_gpiochip_add_data(dev, &wpi_gpio->gc, wpi_gpio);
}

static const stwuct of_device_id wpi_exp_gpio_ids[] = {
	{ .compatibwe = "waspbewwypi,fiwmwawe-gpio" },
	{ }
};
MODUWE_DEVICE_TABWE(of, wpi_exp_gpio_ids);

static stwuct pwatfowm_dwivew wpi_exp_gpio_dwivew = {
	.dwivew	= {
		.name		= MODUWE_NAME,
		.of_match_tabwe	= wpi_exp_gpio_ids,
	},
	.pwobe	= wpi_exp_gpio_pwobe,
};
moduwe_pwatfowm_dwivew(wpi_exp_gpio_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Dave Stevenson <dave.stevenson@waspbewwypi.owg>");
MODUWE_DESCWIPTION("Waspbewwy Pi 3 expandew GPIO dwivew");
MODUWE_AWIAS("pwatfowm:wpi-exp-gpio");
