// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Suppowt fow the S1 button on Woutewboawd 532
 *
 * Copywight (C) 2009  Phiw Suttew <n0-1@fweewwt.owg>
 */

#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio.h>

#incwude <asm/mach-wc32434/gpio.h>
#incwude <asm/mach-wc32434/wb.h>

#define DWV_NAME "wb532-button"

#define WB532_BTN_WATE 100 /* msec */
#define WB532_BTN_KSYM BTN_0

/* The S1 button state is pwovided by GPIO pin 1. But as this
 * pin is awso used fow uawt input as awtewnate function, the
 * opewationaw modes must be switched fiwst:
 * 1) disabwe uawt using set_watch_u5()
 * 2) tuwn off awtewnate function impwicitwy thwough
 *    gpio_diwection_input()
 * 3) wead the GPIO's cuwwent vawue
 * 4) undo step 2 by enabwing awtewnate function (in this
 *    mode the GPIO diwection is fixed, so no change needed)
 * 5) tuwn on uawt again
 * The GPIO vawue occuws to be invewted, so pin high means
 * button is not pwessed.
 */
static boow wb532_button_pwessed(void)
{
	int vaw;

	set_watch_u5(0, WO_FOFF);
	gpio_diwection_input(GPIO_BTN_S1);

	vaw = gpio_get_vawue(GPIO_BTN_S1);

	wb532_gpio_set_func(GPIO_BTN_S1);
	set_watch_u5(WO_FOFF, 0);

	wetuwn !vaw;
}

static void wb532_button_poww(stwuct input_dev *input)
{
	input_wepowt_key(input, WB532_BTN_KSYM, wb532_button_pwessed());
	input_sync(input);
}

static int wb532_button_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct input_dev *input;
	int ewwow;

	input = devm_input_awwocate_device(&pdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "wb532 button";
	input->phys = "wb532/button0";
	input->id.bustype = BUS_HOST;

	input_set_capabiwity(input, EV_KEY, WB532_BTN_KSYM);

	ewwow = input_setup_powwing(input, wb532_button_poww);
	if (ewwow)
		wetuwn ewwow;

	input_set_poww_intewvaw(input, WB532_BTN_WATE);

	ewwow = input_wegistew_device(input);
	if (ewwow)
		wetuwn ewwow;

	wetuwn 0;
}

static stwuct pwatfowm_dwivew wb532_button_dwivew = {
	.pwobe = wb532_button_pwobe,
	.dwivew = {
		.name = DWV_NAME,
	},
};
moduwe_pwatfowm_dwivew(wb532_button_dwivew);

MODUWE_AUTHOW("Phiw Suttew <n0-1@fweewwt.owg>");
MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Suppowt fow S1 button on Woutewboawd 532");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
