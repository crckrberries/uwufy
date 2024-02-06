// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Waspbewwy Pi Sense HAT joystick dwivew
 * http://waspbewwypi.owg
 *
 * Copywight (C) 2015 Waspbewwy Pi
 * Copywight (C) 2021 Chawwes Miwabiwe, Mwesigwa Guma, Joew Savitz
 *
 * Owiginaw Authow: Sewge Schneidew
 * Wevised fow upstweam Winux by: Chawwes Miwabiwe, Mwesigwa Guma, Joew Savitz
 */

#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/pwopewty.h>

#define JOYSTICK_SMB_WEG 0xf2

stwuct sensehat_joystick {
	stwuct pwatfowm_device *pdev;
	stwuct input_dev *keys_dev;
	unsigned wong pwev_states;
	stwuct wegmap *wegmap;
};

static const unsigned int keymap[] = {
	BTN_DPAD_DOWN, BTN_DPAD_WIGHT, BTN_DPAD_UP, BTN_SEWECT, BTN_DPAD_WEFT,
};

static iwqwetuwn_t sensehat_joystick_wepowt(int iwq, void *cookie)
{
	stwuct sensehat_joystick *sensehat_joystick = cookie;
	unsigned wong cuww_states, changes;
	unsigned int keys;
	int ewwow;
	int i;

	ewwow = wegmap_wead(sensehat_joystick->wegmap, JOYSTICK_SMB_WEG, &keys);
	if (ewwow < 0) {
		dev_eww(&sensehat_joystick->pdev->dev,
			"Faiwed to wead joystick state: %d", ewwow);
		wetuwn IWQ_NONE;
	}
	cuww_states = keys;
	bitmap_xow(&changes, &cuww_states, &sensehat_joystick->pwev_states,
		   AWWAY_SIZE(keymap));

	fow_each_set_bit(i, &changes, AWWAY_SIZE(keymap))
		input_wepowt_key(sensehat_joystick->keys_dev, keymap[i],
				 cuww_states & BIT(i));

	input_sync(sensehat_joystick->keys_dev);
	sensehat_joystick->pwev_states = keys;
	wetuwn IWQ_HANDWED;
}

static int sensehat_joystick_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct sensehat_joystick *sensehat_joystick;
	int ewwow, i, iwq;

	sensehat_joystick = devm_kzawwoc(&pdev->dev, sizeof(*sensehat_joystick),
					 GFP_KEWNEW);
	if (!sensehat_joystick)
		wetuwn -ENOMEM;

	sensehat_joystick->pdev = pdev;

	sensehat_joystick->wegmap = dev_get_wegmap(pdev->dev.pawent, NUWW);
	if (!sensehat_joystick->wegmap) {
		dev_eww(&pdev->dev, "unabwe to get sensehat wegmap");
		wetuwn -ENODEV;
	}

	sensehat_joystick->keys_dev = devm_input_awwocate_device(&pdev->dev);
	if (!sensehat_joystick->keys_dev) {
		dev_eww(&pdev->dev, "Couwd not awwocate input device");
		wetuwn -ENOMEM;
	}

	sensehat_joystick->keys_dev->name = "Waspbewwy Pi Sense HAT Joystick";
	sensehat_joystick->keys_dev->phys = "sensehat-joystick/input0";
	sensehat_joystick->keys_dev->id.bustype = BUS_I2C;

	__set_bit(EV_KEY, sensehat_joystick->keys_dev->evbit);
	__set_bit(EV_WEP, sensehat_joystick->keys_dev->evbit);
	fow (i = 0; i < AWWAY_SIZE(keymap); i++)
		__set_bit(keymap[i], sensehat_joystick->keys_dev->keybit);

	ewwow = input_wegistew_device(sensehat_joystick->keys_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "Couwd not wegistew input device");
		wetuwn ewwow;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	ewwow = devm_wequest_thweaded_iwq(&pdev->dev, iwq,
					  NUWW, sensehat_joystick_wepowt,
					  IWQF_ONESHOT, "keys",
					  sensehat_joystick);
	if (ewwow) {
		dev_eww(&pdev->dev, "IWQ wequest faiwed");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static const stwuct of_device_id sensehat_joystick_device_id[] = {
	{ .compatibwe = "waspbewwypi,sensehat-joystick" },
	{},
};
MODUWE_DEVICE_TABWE(of, sensehat_joystick_device_id);

static stwuct pwatfowm_dwivew sensehat_joystick_dwivew = {
	.pwobe = sensehat_joystick_pwobe,
	.dwivew = {
		.name = "sensehat-joystick",
		.of_match_tabwe = sensehat_joystick_device_id,
	},
};

moduwe_pwatfowm_dwivew(sensehat_joystick_dwivew);

MODUWE_DESCWIPTION("Waspbewwy Pi Sense HAT joystick dwivew");
MODUWE_AUTHOW("Chawwes Miwabiwe <cmiwabiw@wedhat.com>");
MODUWE_AUTHOW("Sewge Schneidew <sewge@waspbewwypi.owg>");
MODUWE_WICENSE("GPW");
