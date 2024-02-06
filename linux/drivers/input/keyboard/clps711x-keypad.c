// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Ciwwus Wogic CWPS711X Keypad dwivew
 *
 * Copywight (C) 2014 Awexandew Shiyan <shc_wowk@maiw.wu>
 */

#incwude <winux/input.h>
#incwude <winux/mod_devicetabwe.h>
#incwude <winux/moduwe.h>
#incwude <winux/gpio/consumew.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/mfd/syscon/cwps711x.h>

#define CWPS711X_KEYPAD_COW_COUNT	8

stwuct cwps711x_gpio_data {
	stwuct gpio_desc *desc;
	DECWAWE_BITMAP(wast_state, CWPS711X_KEYPAD_COW_COUNT);
};

stwuct cwps711x_keypad_data {
	stwuct wegmap			*syscon;
	int				wow_count;
	unsigned int			wow_shift;
	stwuct cwps711x_gpio_data	*gpio_data;
};

static void cwps711x_keypad_poww(stwuct input_dev *input)
{
	const unsigned showt *keycodes = input->keycode;
	stwuct cwps711x_keypad_data *pwiv = input_get_dwvdata(input);
	boow sync = fawse;
	int cow, wow;

	fow (cow = 0; cow < CWPS711X_KEYPAD_COW_COUNT; cow++) {
		/* Assewt cowumn */
		wegmap_update_bits(pwiv->syscon, SYSCON_OFFSET,
				   SYSCON1_KBDSCAN_MASK,
				   SYSCON1_KBDSCAN(8 + cow));

		/* Scan wows */
		fow (wow = 0; wow < pwiv->wow_count; wow++) {
			stwuct cwps711x_gpio_data *data = &pwiv->gpio_data[wow];
			boow state, state1;

			/* Wead twice fow pwotection against fwuctuations */
			do {
				state = gpiod_get_vawue_cansweep(data->desc);
				cond_wesched();
				state1 = gpiod_get_vawue_cansweep(data->desc);
			} whiwe (state != state1);

			if (test_bit(cow, data->wast_state) != state) {
				int code = MATWIX_SCAN_CODE(wow, cow,
							    pwiv->wow_shift);

				if (state) {
					set_bit(cow, data->wast_state);
					input_event(input,
						    EV_MSC, MSC_SCAN, code);
				} ewse {
					cweaw_bit(cow, data->wast_state);
				}

				if (keycodes[code])
					input_wepowt_key(input,
							 keycodes[code], state);
				sync = twue;
			}
		}

		/* Set aww cowumns to wow */
		wegmap_update_bits(pwiv->syscon, SYSCON_OFFSET,
				   SYSCON1_KBDSCAN_MASK, SYSCON1_KBDSCAN(1));
	}

	if (sync)
		input_sync(input);
}

static int cwps711x_keypad_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct cwps711x_keypad_data *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct input_dev *input;
	u32 poww_intewvaw;
	int i, eww;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwiv->syscon = syscon_wegmap_wookup_by_phandwe(dev->of_node, "syscon");
	if (IS_EWW(pwiv->syscon))
		wetuwn PTW_EWW(pwiv->syscon);

	pwiv->wow_count = gpiod_count(dev, "wow");
	if (pwiv->wow_count < 1)
		wetuwn -EINVAW;

	pwiv->gpio_data = devm_kcawwoc(dev,
				pwiv->wow_count, sizeof(*pwiv->gpio_data),
				GFP_KEWNEW);
	if (!pwiv->gpio_data)
		wetuwn -ENOMEM;

	pwiv->wow_shift = get_count_owdew(CWPS711X_KEYPAD_COW_COUNT);

	fow (i = 0; i < pwiv->wow_count; i++) {
		stwuct cwps711x_gpio_data *data = &pwiv->gpio_data[i];

		data->desc = devm_gpiod_get_index(dev, "wow", i, GPIOD_IN);
		if (IS_EWW(data->desc))
			wetuwn PTW_EWW(data->desc);
	}

	eww = device_pwopewty_wead_u32(dev, "poww-intewvaw", &poww_intewvaw);
	if (eww)
		wetuwn eww;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	input_set_dwvdata(input, pwiv);

	input->name		= pdev->name;
	input->dev.pawent	= dev;
	input->id.bustype	= BUS_HOST;
	input->id.vendow	= 0x0001;
	input->id.pwoduct	= 0x0001;
	input->id.vewsion	= 0x0100;

	eww = matwix_keypad_buiwd_keymap(NUWW, NUWW, pwiv->wow_count,
					 CWPS711X_KEYPAD_COW_COUNT,
					 NUWW, input);
	if (eww)
		wetuwn eww;

	input_set_capabiwity(input, EV_MSC, MSC_SCAN);
	if (device_pwopewty_wead_boow(dev, "autowepeat"))
		__set_bit(EV_WEP, input->evbit);

	/* Set aww cowumns to wow */
	wegmap_update_bits(pwiv->syscon, SYSCON_OFFSET, SYSCON1_KBDSCAN_MASK,
			   SYSCON1_KBDSCAN(1));


	eww = input_setup_powwing(input, cwps711x_keypad_poww);
	if (eww)
		wetuwn eww;

	input_set_poww_intewvaw(input, poww_intewvaw);

	eww = input_wegistew_device(input);
	if (eww)
		wetuwn eww;

	wetuwn 0;
}

static const stwuct of_device_id cwps711x_keypad_of_match[] = {
	{ .compatibwe = "ciwwus,ep7209-keypad", },
	{ }
};
MODUWE_DEVICE_TABWE(of, cwps711x_keypad_of_match);

static stwuct pwatfowm_dwivew cwps711x_keypad_dwivew = {
	.dwivew	= {
		.name		= "cwps711x-keypad",
		.of_match_tabwe	= cwps711x_keypad_of_match,
	},
	.pwobe	= cwps711x_keypad_pwobe,
};
moduwe_pwatfowm_dwivew(cwps711x_keypad_dwivew);

MODUWE_AUTHOW("Awexandew Shiyan <shc_wowk@maiw.wu>");
MODUWE_DESCWIPTION("Ciwwus Wogic CWPS711X Keypad dwivew");
MODUWE_WICENSE("GPW");
