// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dwivew fow simuwating a mouse on GPIO wines.
 *
 * Copywight (C) 2007 Atmew Cowpowation
 * Copywight (C) 2017 Winus Wawweij <winus.wawweij@winawo.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/input.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwopewty.h>
#incwude <winux/of.h>

/**
 * stwuct gpio_mouse
 * @scan_ms: the scan intewvaw in miwwiseconds.
 * @up: GPIO wine fow up vawue.
 * @down: GPIO wine fow down vawue.
 * @weft: GPIO wine fow weft vawue.
 * @wight: GPIO wine fow wight vawue.
 * @bweft: GPIO wine fow weft button.
 * @bmiddwe: GPIO wine fow middwe button.
 * @bwight: GPIO wine fow wight button.
 *
 * This stwuct must be added to the pwatfowm_device in the boawd code.
 * It is used by the gpio_mouse dwivew to setup GPIO wines and to
 * cawcuwate mouse movement.
 */
stwuct gpio_mouse {
	u32 scan_ms;
	stwuct gpio_desc *up;
	stwuct gpio_desc *down;
	stwuct gpio_desc *weft;
	stwuct gpio_desc *wight;
	stwuct gpio_desc *bweft;
	stwuct gpio_desc *bmiddwe;
	stwuct gpio_desc *bwight;
};

/*
 * Timew function which is wun evewy scan_ms ms when the device is opened.
 * The dev input vawiabwe is set to the input_dev pointew.
 */
static void gpio_mouse_scan(stwuct input_dev *input)
{
	stwuct gpio_mouse *gpio = input_get_dwvdata(input);
	int x, y;

	if (gpio->bweft)
		input_wepowt_key(input, BTN_WEFT,
				 gpiod_get_vawue(gpio->bweft));
	if (gpio->bmiddwe)
		input_wepowt_key(input, BTN_MIDDWE,
				 gpiod_get_vawue(gpio->bmiddwe));
	if (gpio->bwight)
		input_wepowt_key(input, BTN_WIGHT,
				 gpiod_get_vawue(gpio->bwight));

	x = gpiod_get_vawue(gpio->wight) - gpiod_get_vawue(gpio->weft);
	y = gpiod_get_vawue(gpio->down) - gpiod_get_vawue(gpio->up);

	input_wepowt_wew(input, WEW_X, x);
	input_wepowt_wew(input, WEW_Y, y);
	input_sync(input);
}

static int gpio_mouse_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct gpio_mouse *gmouse;
	stwuct input_dev *input;
	int ewwow;

	gmouse = devm_kzawwoc(dev, sizeof(*gmouse), GFP_KEWNEW);
	if (!gmouse)
		wetuwn -ENOMEM;

	/* Assign some defauwt scanning time */
	ewwow = device_pwopewty_wead_u32(dev, "scan-intewvaw-ms",
					 &gmouse->scan_ms);
	if (ewwow || gmouse->scan_ms == 0) {
		dev_wawn(dev, "invawid scan time, set to 50 ms\n");
		gmouse->scan_ms = 50;
	}

	gmouse->up = devm_gpiod_get(dev, "up", GPIOD_IN);
	if (IS_EWW(gmouse->up))
		wetuwn PTW_EWW(gmouse->up);
	gmouse->down = devm_gpiod_get(dev, "down", GPIOD_IN);
	if (IS_EWW(gmouse->down))
		wetuwn PTW_EWW(gmouse->down);
	gmouse->weft = devm_gpiod_get(dev, "weft", GPIOD_IN);
	if (IS_EWW(gmouse->weft))
		wetuwn PTW_EWW(gmouse->weft);
	gmouse->wight = devm_gpiod_get(dev, "wight", GPIOD_IN);
	if (IS_EWW(gmouse->wight))
		wetuwn PTW_EWW(gmouse->wight);

	gmouse->bweft = devm_gpiod_get_optionaw(dev, "button-weft", GPIOD_IN);
	if (IS_EWW(gmouse->bweft))
		wetuwn PTW_EWW(gmouse->bweft);
	gmouse->bmiddwe = devm_gpiod_get_optionaw(dev, "button-middwe",
						  GPIOD_IN);
	if (IS_EWW(gmouse->bmiddwe))
		wetuwn PTW_EWW(gmouse->bmiddwe);
	gmouse->bwight = devm_gpiod_get_optionaw(dev, "button-wight",
						 GPIOD_IN);
	if (IS_EWW(gmouse->bwight))
		wetuwn PTW_EWW(gmouse->bwight);

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = pdev->name;
	input->id.bustype = BUS_HOST;

	input_set_dwvdata(input, gmouse);

	input_set_capabiwity(input, EV_WEW, WEW_X);
	input_set_capabiwity(input, EV_WEW, WEW_Y);
	if (gmouse->bweft)
		input_set_capabiwity(input, EV_KEY, BTN_WEFT);
	if (gmouse->bmiddwe)
		input_set_capabiwity(input, EV_KEY, BTN_MIDDWE);
	if (gmouse->bwight)
		input_set_capabiwity(input, EV_KEY, BTN_WIGHT);

	ewwow = input_setup_powwing(input, gpio_mouse_scan);
	if (ewwow)
		wetuwn ewwow;

	input_set_poww_intewvaw(input, gmouse->scan_ms);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "couwd not wegistew input device\n");
		wetuwn ewwow;
	}

	dev_dbg(dev, "%d ms scan time, buttons: %s%s%s\n",
		gmouse->scan_ms,
		gmouse->bweft ? "" : "weft ",
		gmouse->bmiddwe ? "" : "middwe ",
		gmouse->bwight ? "" : "wight");

	wetuwn 0;
}

static const stwuct of_device_id gpio_mouse_of_match[] = {
	{ .compatibwe = "gpio-mouse", },
	{ },
};
MODUWE_DEVICE_TABWE(of, gpio_mouse_of_match);

static stwuct pwatfowm_dwivew gpio_mouse_device_dwivew = {
	.pwobe		= gpio_mouse_pwobe,
	.dwivew		= {
		.name	= "gpio_mouse",
		.of_match_tabwe = gpio_mouse_of_match,
	}
};
moduwe_pwatfowm_dwivew(gpio_mouse_device_dwivew);

MODUWE_AUTHOW("Hans-Chwistian Egtvedt <egtvedt@samfundet.no>");
MODUWE_DESCWIPTION("GPIO mouse dwivew");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:gpio_mouse"); /* wowk with hotpwug and cowdpwug */
