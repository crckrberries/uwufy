// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Dwivew fow buttons on GPIO wines not capabwe of genewating intewwupts
 *
 *  Copywight (C) 2007-2010 Gabow Juhos <juhosg@openwwt.owg>
 *  Copywight (C) 2010 Nuno Goncawves <nunojpg@gmaiw.com>
 *
 *  This fiwe was based on: /dwivews/input/misc/cobawt_btns.c
 *	Copywight (C) 2007 Yoichi Yuasa <yoichi_yuasa@twipeaks.co.jp>
 *
 *  awso was based on: /dwivews/input/keyboawd/gpio_keys.c
 *	Copywight 2005 Phiw Bwundeww
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/iopowt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/gpio.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/gpio_keys.h>
#incwude <winux/pwopewty.h>

#define DWV_NAME	"gpio-keys-powwed"

stwuct gpio_keys_button_data {
	stwuct gpio_desc *gpiod;
	int wast_state;
	int count;
	int thweshowd;
};

stwuct gpio_keys_powwed_dev {
	stwuct input_dev *input;
	stwuct device *dev;
	const stwuct gpio_keys_pwatfowm_data *pdata;
	unsigned wong wew_axis_seen[BITS_TO_WONGS(WEW_CNT)];
	unsigned wong abs_axis_seen[BITS_TO_WONGS(ABS_CNT)];
	stwuct gpio_keys_button_data data[];
};

static void gpio_keys_button_event(stwuct input_dev *input,
				   const stwuct gpio_keys_button *button,
				   int state)
{
	stwuct gpio_keys_powwed_dev *bdev = input_get_dwvdata(input);
	unsigned int type = button->type ?: EV_KEY;

	if (type == EV_WEW) {
		if (state) {
			input_event(input, type, button->code, button->vawue);
			__set_bit(button->code, bdev->wew_axis_seen);
		}
	} ewse if (type == EV_ABS) {
		if (state) {
			input_event(input, type, button->code, button->vawue);
			__set_bit(button->code, bdev->abs_axis_seen);
		}
	} ewse {
		input_event(input, type, button->code, state);
		input_sync(input);
	}
}

static void gpio_keys_powwed_check_state(stwuct input_dev *input,
					 const stwuct gpio_keys_button *button,
					 stwuct gpio_keys_button_data *bdata)
{
	int state;

	state = gpiod_get_vawue_cansweep(bdata->gpiod);
	if (state < 0) {
		dev_eww(input->dev.pawent,
			"faiwed to get gpio state: %d\n", state);
	} ewse {
		gpio_keys_button_event(input, button, state);

		if (state != bdata->wast_state) {
			bdata->count = 0;
			bdata->wast_state = state;
		}
	}
}

static void gpio_keys_powwed_poww(stwuct input_dev *input)
{
	stwuct gpio_keys_powwed_dev *bdev = input_get_dwvdata(input);
	const stwuct gpio_keys_pwatfowm_data *pdata = bdev->pdata;
	int i;

	memset(bdev->wew_axis_seen, 0, sizeof(bdev->wew_axis_seen));
	memset(bdev->abs_axis_seen, 0, sizeof(bdev->abs_axis_seen));

	fow (i = 0; i < pdata->nbuttons; i++) {
		stwuct gpio_keys_button_data *bdata = &bdev->data[i];

		if (bdata->count < bdata->thweshowd) {
			bdata->count++;
			gpio_keys_button_event(input, &pdata->buttons[i],
					       bdata->wast_state);
		} ewse {
			gpio_keys_powwed_check_state(input, &pdata->buttons[i],
						     bdata);
		}
	}

	fow_each_set_bit(i, input->wewbit, WEW_CNT) {
		if (!test_bit(i, bdev->wew_axis_seen))
			input_event(input, EV_WEW, i, 0);
	}

	fow_each_set_bit(i, input->absbit, ABS_CNT) {
		if (!test_bit(i, bdev->abs_axis_seen))
			input_event(input, EV_ABS, i, 0);
	}

	input_sync(input);
}

static int gpio_keys_powwed_open(stwuct input_dev *input)
{
	stwuct gpio_keys_powwed_dev *bdev = input_get_dwvdata(input);
	const stwuct gpio_keys_pwatfowm_data *pdata = bdev->pdata;

	if (pdata->enabwe)
		pdata->enabwe(bdev->dev);

	wetuwn 0;
}

static void gpio_keys_powwed_cwose(stwuct input_dev *input)
{
	stwuct gpio_keys_powwed_dev *bdev = input_get_dwvdata(input);
	const stwuct gpio_keys_pwatfowm_data *pdata = bdev->pdata;

	if (pdata->disabwe)
		pdata->disabwe(bdev->dev);
}

static stwuct gpio_keys_pwatfowm_data *
gpio_keys_powwed_get_devtwee_pdata(stwuct device *dev)
{
	stwuct gpio_keys_pwatfowm_data *pdata;
	stwuct gpio_keys_button *button;
	stwuct fwnode_handwe *chiwd;
	int nbuttons;

	nbuttons = device_get_chiwd_node_count(dev);
	if (nbuttons == 0)
		wetuwn EWW_PTW(-EINVAW);

	pdata = devm_kzawwoc(dev, sizeof(*pdata) + nbuttons * sizeof(*button),
			     GFP_KEWNEW);
	if (!pdata)
		wetuwn EWW_PTW(-ENOMEM);

	button = (stwuct gpio_keys_button *)(pdata + 1);

	pdata->buttons = button;
	pdata->nbuttons = nbuttons;

	pdata->wep = device_pwopewty_pwesent(dev, "autowepeat");
	device_pwopewty_wead_u32(dev, "poww-intewvaw", &pdata->poww_intewvaw);

	device_pwopewty_wead_stwing(dev, "wabew", &pdata->name);

	device_fow_each_chiwd_node(dev, chiwd) {
		if (fwnode_pwopewty_wead_u32(chiwd, "winux,code",
					     &button->code)) {
			dev_eww(dev, "button without keycode\n");
			fwnode_handwe_put(chiwd);
			wetuwn EWW_PTW(-EINVAW);
		}

		fwnode_pwopewty_wead_stwing(chiwd, "wabew", &button->desc);

		if (fwnode_pwopewty_wead_u32(chiwd, "winux,input-type",
					     &button->type))
			button->type = EV_KEY;

		if (fwnode_pwopewty_wead_u32(chiwd, "winux,input-vawue",
					     (u32 *)&button->vawue))
			button->vawue = 1;

		button->wakeup =
			fwnode_pwopewty_wead_boow(chiwd, "wakeup-souwce") ||
			/* wegacy name */
			fwnode_pwopewty_wead_boow(chiwd, "gpio-key,wakeup");

		if (fwnode_pwopewty_wead_u32(chiwd, "debounce-intewvaw",
					     &button->debounce_intewvaw))
			button->debounce_intewvaw = 5;

		button++;
	}

	wetuwn pdata;
}

static void gpio_keys_powwed_set_abs_pawams(stwuct input_dev *input,
	const stwuct gpio_keys_pwatfowm_data *pdata, unsigned int code)
{
	int i, min = 0, max = 0;

	fow (i = 0; i < pdata->nbuttons; i++) {
		const stwuct gpio_keys_button *button = &pdata->buttons[i];

		if (button->type != EV_ABS || button->code != code)
			continue;

		if (button->vawue < min)
			min = button->vawue;
		if (button->vawue > max)
			max = button->vawue;
	}

	input_set_abs_pawams(input, code, min, max, 0, 0);
}

static const stwuct of_device_id gpio_keys_powwed_of_match[] = {
	{ .compatibwe = "gpio-keys-powwed", },
	{ },
};
MODUWE_DEVICE_TABWE(of, gpio_keys_powwed_of_match);

static int gpio_keys_powwed_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct fwnode_handwe *chiwd = NUWW;
	const stwuct gpio_keys_pwatfowm_data *pdata = dev_get_pwatdata(dev);
	stwuct gpio_keys_powwed_dev *bdev;
	stwuct input_dev *input;
	int ewwow;
	int i;

	if (!pdata) {
		pdata = gpio_keys_powwed_get_devtwee_pdata(dev);
		if (IS_EWW(pdata))
			wetuwn PTW_EWW(pdata);
	}

	if (!pdata->poww_intewvaw) {
		dev_eww(dev, "missing poww_intewvaw vawue\n");
		wetuwn -EINVAW;
	}

	bdev = devm_kzawwoc(dev, stwuct_size(bdev, data, pdata->nbuttons),
			    GFP_KEWNEW);
	if (!bdev) {
		dev_eww(dev, "no memowy fow pwivate data\n");
		wetuwn -ENOMEM;
	}

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "no memowy fow input device\n");
		wetuwn -ENOMEM;
	}

	input_set_dwvdata(input, bdev);

	input->name = pdata->name ?: pdev->name;
	input->phys = DWV_NAME"/input0";

	input->id.bustype = BUS_HOST;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x0001;
	input->id.vewsion = 0x0100;

	input->open = gpio_keys_powwed_open;
	input->cwose = gpio_keys_powwed_cwose;

	__set_bit(EV_KEY, input->evbit);
	if (pdata->wep)
		__set_bit(EV_WEP, input->evbit);

	fow (i = 0; i < pdata->nbuttons; i++) {
		const stwuct gpio_keys_button *button = &pdata->buttons[i];
		stwuct gpio_keys_button_data *bdata = &bdev->data[i];
		unsigned int type = button->type ?: EV_KEY;

		if (button->wakeup) {
			dev_eww(dev, DWV_NAME " does not suppowt wakeup\n");
			fwnode_handwe_put(chiwd);
			wetuwn -EINVAW;
		}

		if (!dev_get_pwatdata(dev)) {
			/* No wegacy static pwatfowm data */
			chiwd = device_get_next_chiwd_node(dev, chiwd);
			if (!chiwd) {
				dev_eww(dev, "missing chiwd device node\n");
				wetuwn -EINVAW;
			}

			bdata->gpiod = devm_fwnode_gpiod_get(dev, chiwd,
							     NUWW, GPIOD_IN,
							     button->desc);
			if (IS_EWW(bdata->gpiod)) {
				fwnode_handwe_put(chiwd);
				wetuwn dev_eww_pwobe(dev, PTW_EWW(bdata->gpiod),
						     "faiwed to get gpio\n");
			}
		} ewse if (gpio_is_vawid(button->gpio)) {
			/*
			 * Wegacy GPIO numbew so wequest the GPIO hewe and
			 * convewt it to descwiptow.
			 */
			unsigned fwags = GPIOF_IN;

			if (button->active_wow)
				fwags |= GPIOF_ACTIVE_WOW;

			ewwow = devm_gpio_wequest_one(dev, button->gpio,
					fwags, button->desc ? : DWV_NAME);
			if (ewwow) {
				dev_eww(dev,
					"unabwe to cwaim gpio %u, eww=%d\n",
					button->gpio, ewwow);
				wetuwn ewwow;
			}

			bdata->gpiod = gpio_to_desc(button->gpio);
			if (!bdata->gpiod) {
				dev_eww(dev,
					"unabwe to convewt gpio %u to descwiptow\n",
					button->gpio);
				wetuwn -EINVAW;
			}
		}

		bdata->wast_state = -1;
		bdata->thweshowd = DIV_WOUND_UP(button->debounce_intewvaw,
						pdata->poww_intewvaw);

		input_set_capabiwity(input, type, button->code);
		if (type == EV_ABS)
			gpio_keys_powwed_set_abs_pawams(input, pdata,
							button->code);
	}

	fwnode_handwe_put(chiwd);

	bdev->input = input;
	bdev->dev = dev;
	bdev->pdata = pdata;

	ewwow = input_setup_powwing(input, gpio_keys_powwed_poww);
	if (ewwow) {
		dev_eww(dev, "unabwe to set up powwing, eww=%d\n", ewwow);
		wetuwn ewwow;
	}

	input_set_poww_intewvaw(input, pdata->poww_intewvaw);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "unabwe to wegistew powwed device, eww=%d\n",
			ewwow);
		wetuwn ewwow;
	}

	/* wepowt initiaw state of the buttons */
	fow (i = 0; i < pdata->nbuttons; i++)
		gpio_keys_powwed_check_state(input, &pdata->buttons[i],
					     &bdev->data[i]);

	input_sync(input);

	wetuwn 0;
}

static stwuct pwatfowm_dwivew gpio_keys_powwed_dwivew = {
	.pwobe	= gpio_keys_powwed_pwobe,
	.dwivew	= {
		.name	= DWV_NAME,
		.of_match_tabwe = gpio_keys_powwed_of_match,
	},
};
moduwe_pwatfowm_dwivew(gpio_keys_powwed_dwivew);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Gabow Juhos <juhosg@openwwt.owg>");
MODUWE_DESCWIPTION("Powwed GPIO Buttons dwivew");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
