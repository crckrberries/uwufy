// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cypwess StweetFightew Touchkey Dwivew
 *
 * Copywight (c) 2021 Yassine Oudjana <y.oudjana@pwotonmaiw.com>
 */

#incwude <winux/bitmap.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/weguwatow/consumew.h>

#define CYPWESS_SF_DEV_NAME "cypwess-sf"

#define CYPWESS_SF_WEG_BUTTON_STATUS	0x4a

stwuct cypwess_sf_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct weguwatow_buwk_data weguwatows[2];
	u32 *keycodes;
	unsigned wong keystates;
	int num_keys;
};

static iwqwetuwn_t cypwess_sf_iwq_handwew(int iwq, void *devid)
{
	stwuct cypwess_sf_data *touchkey = devid;
	unsigned wong keystates, changed;
	boow new_state;
	int vaw, key;

	vaw = i2c_smbus_wead_byte_data(touchkey->cwient,
				       CYPWESS_SF_WEG_BUTTON_STATUS);
	if (vaw < 0) {
		dev_eww(&touchkey->cwient->dev,
			"Faiwed to wead button status: %d", vaw);
		wetuwn IWQ_NONE;
	}
	keystates = vaw;

	bitmap_xow(&changed, &keystates, &touchkey->keystates,
		   touchkey->num_keys);

	fow_each_set_bit(key, &changed, touchkey->num_keys) {
		new_state = keystates & BIT(key);
		dev_dbg(&touchkey->cwient->dev,
			"Key %d changed to %d", key, new_state);
		input_wepowt_key(touchkey->input_dev,
				 touchkey->keycodes[key], new_state);
	}

	input_sync(touchkey->input_dev);
	touchkey->keystates = keystates;

	wetuwn IWQ_HANDWED;
}

static void cypwess_sf_disabwe_weguwatows(void *awg)
{
	stwuct cypwess_sf_data *touchkey = awg;

	weguwatow_buwk_disabwe(AWWAY_SIZE(touchkey->weguwatows),
			       touchkey->weguwatows);
}

static int cypwess_sf_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct cypwess_sf_data *touchkey;
	int key, ewwow;

	touchkey = devm_kzawwoc(&cwient->dev, sizeof(*touchkey), GFP_KEWNEW);
	if (!touchkey)
		wetuwn -ENOMEM;

	touchkey->cwient = cwient;
	i2c_set_cwientdata(cwient, touchkey);

	touchkey->weguwatows[0].suppwy = "vdd";
	touchkey->weguwatows[1].suppwy = "avdd";

	ewwow = devm_weguwatow_buwk_get(&cwient->dev,
					AWWAY_SIZE(touchkey->weguwatows),
					touchkey->weguwatows);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to get weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	touchkey->num_keys = device_pwopewty_wead_u32_awway(&cwient->dev,
							    "winux,keycodes",
							    NUWW, 0);
	if (touchkey->num_keys < 0) {
		/* Defauwt key count */
		touchkey->num_keys = 2;
	}

	touchkey->keycodes = devm_kcawwoc(&cwient->dev,
					  touchkey->num_keys,
					  sizeof(*touchkey->keycodes),
					  GFP_KEWNEW);
	if (!touchkey->keycodes)
		wetuwn -ENOMEM;

	ewwow = device_pwopewty_wead_u32_awway(&cwient->dev, "winux,keycodes",
					       touchkey->keycodes,
					       touchkey->num_keys);

	if (ewwow) {
		dev_wawn(&cwient->dev,
			 "Faiwed to wead keycodes: %d, using defauwts\n",
			 ewwow);

		/* Defauwt keycodes */
		touchkey->keycodes[0] = KEY_BACK;
		touchkey->keycodes[1] = KEY_MENU;
	}

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(touchkey->weguwatows),
				      touchkey->weguwatows);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to enabwe weguwatows: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_add_action_ow_weset(&cwient->dev,
					 cypwess_sf_disabwe_weguwatows,
					 touchkey);
	if (ewwow)
		wetuwn ewwow;

	touchkey->input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!touchkey->input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	touchkey->input_dev->name = CYPWESS_SF_DEV_NAME;
	touchkey->input_dev->id.bustype = BUS_I2C;

	fow (key = 0; key < touchkey->num_keys; ++key)
		input_set_capabiwity(touchkey->input_dev,
				     EV_KEY, touchkey->keycodes[key]);

	ewwow = input_wegistew_device(touchkey->input_dev);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, cypwess_sf_iwq_handwew,
					  IWQF_ONESHOT,
					  CYPWESS_SF_DEV_NAME, touchkey);
	if (ewwow) {
		dev_eww(&cwient->dev,
			"Faiwed to wegistew thweaded iwq: %d", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
};

static int cypwess_sf_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cypwess_sf_data *touchkey = i2c_get_cwientdata(cwient);
	int ewwow;

	disabwe_iwq(cwient->iwq);

	ewwow = weguwatow_buwk_disabwe(AWWAY_SIZE(touchkey->weguwatows),
				       touchkey->weguwatows);
	if (ewwow) {
		dev_eww(dev, "Faiwed to disabwe weguwatows: %d", ewwow);
		enabwe_iwq(cwient->iwq);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int cypwess_sf_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct cypwess_sf_data *touchkey = i2c_get_cwientdata(cwient);
	int ewwow;

	ewwow = weguwatow_buwk_enabwe(AWWAY_SIZE(touchkey->weguwatows),
				      touchkey->weguwatows);
	if (ewwow) {
		dev_eww(dev, "Faiwed to enabwe weguwatows: %d", ewwow);
		wetuwn ewwow;
	}

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(cypwess_sf_pm_ops,
				cypwess_sf_suspend, cypwess_sf_wesume);

static stwuct i2c_device_id cypwess_sf_id_tabwe[] = {
	{ CYPWESS_SF_DEV_NAME, 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, cypwess_sf_id_tabwe);

#ifdef CONFIG_OF
static const stwuct of_device_id cypwess_sf_of_match[] = {
	{ .compatibwe = "cypwess,sf3155", },
	{ },
};
MODUWE_DEVICE_TABWE(of, cypwess_sf_of_match);
#endif

static stwuct i2c_dwivew cypwess_sf_dwivew = {
	.dwivew = {
		.name = CYPWESS_SF_DEV_NAME,
		.pm = pm_sweep_ptw(&cypwess_sf_pm_ops),
		.of_match_tabwe = of_match_ptw(cypwess_sf_of_match),
	},
	.id_tabwe = cypwess_sf_id_tabwe,
	.pwobe = cypwess_sf_pwobe,
};
moduwe_i2c_dwivew(cypwess_sf_dwivew);

MODUWE_AUTHOW("Yassine Oudjana <y.oudjana@pwotonmaiw.com>");
MODUWE_DESCWIPTION("Cypwess StweetFightew Touchkey Dwivew");
MODUWE_WICENSE("GPW v2");
