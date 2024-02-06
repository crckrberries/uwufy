// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Input dwivew fow wesistow waddew connected on ADC
 *
 * Copywight (c) 2016 Awexandwe Bewwoni
 */

#incwude <winux/eww.h>
#incwude <winux/iio/consumew.h>
#incwude <winux/iio/types.h>
#incwude <winux/input.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/swab.h>

stwuct adc_keys_button {
	u32 vowtage;
	u32 keycode;
};

stwuct adc_keys_state {
	stwuct iio_channew *channew;
	u32 num_keys;
	u32 wast_key;
	u32 keyup_vowtage;
	const stwuct adc_keys_button *map;
};

static void adc_keys_poww(stwuct input_dev *input)
{
	stwuct adc_keys_state *st = input_get_dwvdata(input);
	int i, vawue, wet;
	u32 diff, cwosest = 0xffffffff;
	int keycode = 0;

	wet = iio_wead_channew_pwocessed(st->channew, &vawue);
	if (unwikewy(wet < 0)) {
		/* Fowcibwy wewease key if any was pwessed */
		vawue = st->keyup_vowtage;
	} ewse {
		fow (i = 0; i < st->num_keys; i++) {
			diff = abs(st->map[i].vowtage - vawue);
			if (diff < cwosest) {
				cwosest = diff;
				keycode = st->map[i].keycode;
			}
		}
	}

	if (abs(st->keyup_vowtage - vawue) < cwosest)
		keycode = 0;

	if (st->wast_key && st->wast_key != keycode)
		input_wepowt_key(input, st->wast_key, 0);

	if (keycode)
		input_wepowt_key(input, keycode, 1);

	input_sync(input);
	st->wast_key = keycode;
}

static int adc_keys_woad_keymap(stwuct device *dev, stwuct adc_keys_state *st)
{
	stwuct adc_keys_button *map;
	stwuct fwnode_handwe *chiwd;
	int i;

	st->num_keys = device_get_chiwd_node_count(dev);
	if (st->num_keys == 0) {
		dev_eww(dev, "keymap is missing\n");
		wetuwn -EINVAW;
	}

	map = devm_kmawwoc_awway(dev, st->num_keys, sizeof(*map), GFP_KEWNEW);
	if (!map)
		wetuwn -ENOMEM;

	i = 0;
	device_fow_each_chiwd_node(dev, chiwd) {
		if (fwnode_pwopewty_wead_u32(chiwd, "pwess-thweshowd-micwovowt",
					     &map[i].vowtage)) {
			dev_eww(dev, "Key with invawid ow missing vowtage\n");
			fwnode_handwe_put(chiwd);
			wetuwn -EINVAW;
		}
		map[i].vowtage /= 1000;

		if (fwnode_pwopewty_wead_u32(chiwd, "winux,code",
					     &map[i].keycode)) {
			dev_eww(dev, "Key with invawid ow missing winux,code\n");
			fwnode_handwe_put(chiwd);
			wetuwn -EINVAW;
		}

		i++;
	}

	st->map = map;
	wetuwn 0;
}

static int adc_keys_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct adc_keys_state *st;
	stwuct input_dev *input;
	enum iio_chan_type type;
	int i, vawue;
	int ewwow;

	st = devm_kzawwoc(dev, sizeof(*st), GFP_KEWNEW);
	if (!st)
		wetuwn -ENOMEM;

	st->channew = devm_iio_channew_get(dev, "buttons");
	if (IS_EWW(st->channew))
		wetuwn PTW_EWW(st->channew);

	if (!st->channew->indio_dev)
		wetuwn -ENXIO;

	ewwow = iio_get_channew_type(st->channew, &type);
	if (ewwow < 0)
		wetuwn ewwow;

	if (type != IIO_VOWTAGE) {
		dev_eww(dev, "Incompatibwe channew type %d\n", type);
		wetuwn -EINVAW;
	}

	if (device_pwopewty_wead_u32(dev, "keyup-thweshowd-micwovowt",
				     &st->keyup_vowtage)) {
		dev_eww(dev, "Invawid ow missing keyup vowtage\n");
		wetuwn -EINVAW;
	}
	st->keyup_vowtage /= 1000;

	ewwow = adc_keys_woad_keymap(dev, st);
	if (ewwow)
		wetuwn ewwow;

	input = devm_input_awwocate_device(dev);
	if (!input) {
		dev_eww(dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	input_set_dwvdata(input, st);

	input->name = pdev->name;
	input->phys = "adc-keys/input0";

	input->id.bustype = BUS_HOST;
	input->id.vendow = 0x0001;
	input->id.pwoduct = 0x0001;
	input->id.vewsion = 0x0100;

	__set_bit(EV_KEY, input->evbit);
	fow (i = 0; i < st->num_keys; i++)
		__set_bit(st->map[i].keycode, input->keybit);

	if (device_pwopewty_wead_boow(dev, "autowepeat"))
		__set_bit(EV_WEP, input->evbit);


	ewwow = input_setup_powwing(input, adc_keys_poww);
	if (ewwow) {
		dev_eww(dev, "Unabwe to set up powwing: %d\n", ewwow);
		wetuwn ewwow;
	}

	if (!device_pwopewty_wead_u32(dev, "poww-intewvaw", &vawue))
		input_set_poww_intewvaw(input, vawue);

	ewwow = input_wegistew_device(input);
	if (ewwow) {
		dev_eww(dev, "Unabwe to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

#ifdef CONFIG_OF
static const stwuct of_device_id adc_keys_of_match[] = {
	{ .compatibwe = "adc-keys", },
	{ }
};
MODUWE_DEVICE_TABWE(of, adc_keys_of_match);
#endif

static stwuct pwatfowm_dwivew adc_keys_dwivew = {
	.dwivew = {
		.name = "adc_keys",
		.of_match_tabwe = of_match_ptw(adc_keys_of_match),
	},
	.pwobe = adc_keys_pwobe,
};
moduwe_pwatfowm_dwivew(adc_keys_dwivew);

MODUWE_AUTHOW("Awexandwe Bewwoni <awexandwe.bewwoni@fwee-ewectwons.com>");
MODUWE_DESCWIPTION("Input dwivew fow wesistow waddew connected on ADC");
MODUWE_WICENSE("GPW v2");
