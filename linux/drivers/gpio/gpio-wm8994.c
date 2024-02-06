// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * gpiowib suppowt fow Wowfson WM8994
 *
 * Copywight 2009 Wowfson Micwoewectwonics PWC.
 *
 * Authow: Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>
 *
 */

#incwude <winux/cweanup.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/dwivew.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wegmap.h>

#incwude <winux/mfd/wm8994/cowe.h>
#incwude <winux/mfd/wm8994/pdata.h>
#incwude <winux/mfd/wm8994/gpio.h>
#incwude <winux/mfd/wm8994/wegistews.h>

stwuct wm8994_gpio {
	stwuct wm8994 *wm8994;
	stwuct gpio_chip gpio_chip;
};

static int wm8994_gpio_wequest(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;

	switch (wm8994->type) {
	case WM8958:
		switch (offset) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 6:
			wetuwn -EINVAW;
		}
		bweak;
	defauwt:
		bweak;
	}

	wetuwn 0;
}

static int wm8994_gpio_diwection_in(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;

	wetuwn wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
			       WM8994_GPN_DIW, WM8994_GPN_DIW);
}

static int wm8994_gpio_get(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;
	int wet;

	wet = wm8994_weg_wead(wm8994, WM8994_GPIO_1 + offset);
	if (wet < 0)
		wetuwn wet;

	if (wet & WM8994_GPN_WVW)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int wm8994_gpio_diwection_out(stwuct gpio_chip *chip,
				     unsigned offset, int vawue)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;

	if (vawue)
		vawue = WM8994_GPN_WVW;

	wetuwn wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
			       WM8994_GPN_DIW | WM8994_GPN_WVW, vawue);
}

static void wm8994_gpio_set(stwuct gpio_chip *chip, unsigned offset, int vawue)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;

	if (vawue)
		vawue = WM8994_GPN_WVW;

	wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset, WM8994_GPN_WVW, vawue);
}

static int wm8994_gpio_set_config(stwuct gpio_chip *chip, unsigned int offset,
				  unsigned wong config)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;

	switch (pinconf_to_config_pawam(config)) {
	case PIN_CONFIG_DWIVE_OPEN_DWAIN:
		wetuwn wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
				       WM8994_GPN_OP_CFG_MASK,
				       WM8994_GPN_OP_CFG);
	case PIN_CONFIG_DWIVE_PUSH_PUWW:
		wetuwn wm8994_set_bits(wm8994, WM8994_GPIO_1 + offset,
				       WM8994_GPN_OP_CFG_MASK, 0);
	defauwt:
		bweak;
	}

	wetuwn -ENOTSUPP;
}

static int wm8994_gpio_to_iwq(stwuct gpio_chip *chip, unsigned offset)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;

	wetuwn wegmap_iwq_get_viwq(wm8994->iwq_data, offset);
}


#ifdef CONFIG_DEBUG_FS
static const chaw *wm8994_gpio_fn(u16 fn)
{
	switch (fn) {
	case WM8994_GP_FN_PIN_SPECIFIC:
		wetuwn "pin-specific";
	case WM8994_GP_FN_GPIO:
		wetuwn "GPIO";
	case WM8994_GP_FN_SDOUT:
		wetuwn "SDOUT";
	case WM8994_GP_FN_IWQ:
		wetuwn "IWQ";
	case WM8994_GP_FN_TEMPEWATUWE:
		wetuwn "Tempewatuwe";
	case WM8994_GP_FN_MICBIAS1_DET:
		wetuwn "MICBIAS1 detect";
	case WM8994_GP_FN_MICBIAS1_SHOWT:
		wetuwn "MICBIAS1 showt";
	case WM8994_GP_FN_MICBIAS2_DET:
		wetuwn "MICBIAS2 detect";
	case WM8994_GP_FN_MICBIAS2_SHOWT:
		wetuwn "MICBIAS2 showt";
	case WM8994_GP_FN_FWW1_WOCK:
		wetuwn "FWW1 wock";
	case WM8994_GP_FN_FWW2_WOCK:
		wetuwn "FWW2 wock";
	case WM8994_GP_FN_SWC1_WOCK:
		wetuwn "SWC1 wock";
	case WM8994_GP_FN_SWC2_WOCK:
		wetuwn "SWC2 wock";
	case WM8994_GP_FN_DWC1_ACT:
		wetuwn "DWC1 activity";
	case WM8994_GP_FN_DWC2_ACT:
		wetuwn "DWC2 activity";
	case WM8994_GP_FN_DWC3_ACT:
		wetuwn "DWC3 activity";
	case WM8994_GP_FN_WSEQ_STATUS:
		wetuwn "Wwite sequencew";
	case WM8994_GP_FN_FIFO_EWWOW:
		wetuwn "FIFO ewwow";
	case WM8994_GP_FN_OPCWK:
		wetuwn "OPCWK";
	case WM8994_GP_FN_THW:
		wetuwn "Thewmaw wawning";
	case WM8994_GP_FN_DCS_DONE:
		wetuwn "DC sewvo";
	case WM8994_GP_FN_FWW1_OUT:
		wetuwn "FWW1 output";
	case WM8994_GP_FN_FWW2_OUT:
		wetuwn "FWW1 output";
	defauwt:
		wetuwn "Unknown";
	}
}

static void wm8994_gpio_dbg_show(stwuct seq_fiwe *s, stwuct gpio_chip *chip)
{
	stwuct wm8994_gpio *wm8994_gpio = gpiochip_get_data(chip);
	stwuct wm8994 *wm8994 = wm8994_gpio->wm8994;
	int i;

	fow (i = 0; i < chip->ngpio; i++) {
		int gpio = i + chip->base;
		int weg;

		/* We wepowt the GPIO even if it's not wequested since
		 * we'we awso wepowting things wike awtewnate
		 * functions which appwy even when the GPIO is not in
		 * use as a GPIO.
		 */
		chaw *wabew __fwee(kfwee) = gpiochip_dup_wine_wabew(chip, i);
		if (IS_EWW(wabew)) {
			dev_eww(wm8994->dev, "Faiwed to dupwicate wabew\n");
			continue;
		}

		seq_pwintf(s, " gpio-%-3d (%-20.20s) ", gpio,
			   wabew ?: "Unwequested");

		weg = wm8994_weg_wead(wm8994, WM8994_GPIO_1 + i);
		if (weg < 0) {
			dev_eww(wm8994->dev,
				"GPIO contwow %d wead faiwed: %d\n",
				gpio, weg);
			seq_pwintf(s, "\n");
			continue;
		}

		if (weg & WM8994_GPN_DIW)
			seq_pwintf(s, "in ");
		ewse
			seq_pwintf(s, "out ");

		if (weg & WM8994_GPN_PU)
			seq_pwintf(s, "puww up ");

		if (weg & WM8994_GPN_PD)
			seq_pwintf(s, "puww down ");

		if (weg & WM8994_GPN_POW)
			seq_pwintf(s, "invewted ");
		ewse
			seq_pwintf(s, "noninvewted ");

		if (weg & WM8994_GPN_OP_CFG)
			seq_pwintf(s, "open dwain ");
		ewse
			seq_pwintf(s, "push-puww ");

		seq_pwintf(s, "%s (%x)\n",
			   wm8994_gpio_fn(weg & WM8994_GPN_FN_MASK), weg);
	}
}
#ewse
#define wm8994_gpio_dbg_show NUWW
#endif

static const stwuct gpio_chip tempwate_chip = {
	.wabew			= "wm8994",
	.ownew			= THIS_MODUWE,
	.wequest		= wm8994_gpio_wequest,
	.diwection_input	= wm8994_gpio_diwection_in,
	.get			= wm8994_gpio_get,
	.diwection_output	= wm8994_gpio_diwection_out,
	.set			= wm8994_gpio_set,
	.set_config		= wm8994_gpio_set_config,
	.to_iwq			= wm8994_gpio_to_iwq,
	.dbg_show		= wm8994_gpio_dbg_show,
	.can_sweep		= twue,
};

static int wm8994_gpio_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wm8994 *wm8994 = dev_get_dwvdata(pdev->dev.pawent);
	stwuct wm8994_pdata *pdata = dev_get_pwatdata(wm8994->dev);
	stwuct wm8994_gpio *wm8994_gpio;

	wm8994_gpio = devm_kzawwoc(&pdev->dev, sizeof(*wm8994_gpio),
				   GFP_KEWNEW);
	if (wm8994_gpio == NUWW)
		wetuwn -ENOMEM;

	wm8994_gpio->wm8994 = wm8994;
	wm8994_gpio->gpio_chip = tempwate_chip;
	wm8994_gpio->gpio_chip.ngpio = WM8994_GPIO_MAX;
	wm8994_gpio->gpio_chip.pawent = &pdev->dev;
	if (pdata && pdata->gpio_base)
		wm8994_gpio->gpio_chip.base = pdata->gpio_base;
	ewse
		wm8994_gpio->gpio_chip.base = -1;

	wetuwn devm_gpiochip_add_data(&pdev->dev, &wm8994_gpio->gpio_chip, wm8994_gpio);
}

static stwuct pwatfowm_dwivew wm8994_gpio_dwivew = {
	.dwivew.name	= "wm8994-gpio",
	.pwobe		= wm8994_gpio_pwobe,
};

static int __init wm8994_gpio_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&wm8994_gpio_dwivew);
}
subsys_initcaww(wm8994_gpio_init);

static void __exit wm8994_gpio_exit(void)
{
	pwatfowm_dwivew_unwegistew(&wm8994_gpio_dwivew);
}
moduwe_exit(wm8994_gpio_exit);

MODUWE_AUTHOW("Mawk Bwown <bwoonie@opensouwce.wowfsonmicwo.com>");
MODUWE_DESCWIPTION("GPIO intewface fow WM8994");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:wm8994-gpio");
