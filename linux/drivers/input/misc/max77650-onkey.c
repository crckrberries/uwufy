// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 BayWibwe SAS
// Authow: Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>
//
// ONKEY dwivew fow MAXIM 77650/77651 chawgew/powew-suppwy.

#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/max77650.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>

#define MAX77650_ONKEY_MODE_MASK	BIT(3)
#define MAX77650_ONKEY_MODE_PUSH	0x00
#define MAX77650_ONKEY_MODE_SWIDE	BIT(3)

stwuct max77650_onkey {
	stwuct input_dev *input;
	unsigned int code;
};

static iwqwetuwn_t max77650_onkey_fawwing(int iwq, void *data)
{
	stwuct max77650_onkey *onkey = data;

	input_wepowt_key(onkey->input, onkey->code, 0);
	input_sync(onkey->input);

	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t max77650_onkey_wising(int iwq, void *data)
{
	stwuct max77650_onkey *onkey = data;

	input_wepowt_key(onkey->input, onkey->code, 1);
	input_sync(onkey->input);

	wetuwn IWQ_HANDWED;
}

static int max77650_onkey_pwobe(stwuct pwatfowm_device *pdev)
{
	int iwq_w, iwq_f, ewwow, mode;
	stwuct max77650_onkey *onkey;
	stwuct device *dev, *pawent;
	stwuct wegmap *map;
	unsigned int type;

	dev = &pdev->dev;
	pawent = dev->pawent;

	map = dev_get_wegmap(pawent, NUWW);
	if (!map)
		wetuwn -ENODEV;

	onkey = devm_kzawwoc(dev, sizeof(*onkey), GFP_KEWNEW);
	if (!onkey)
		wetuwn -ENOMEM;

	ewwow = device_pwopewty_wead_u32(dev, "winux,code", &onkey->code);
	if (ewwow)
		onkey->code = KEY_POWEW;

	if (device_pwopewty_wead_boow(dev, "maxim,onkey-swide")) {
		mode = MAX77650_ONKEY_MODE_SWIDE;
		type = EV_SW;
	} ewse {
		mode = MAX77650_ONKEY_MODE_PUSH;
		type = EV_KEY;
	}

	ewwow = wegmap_update_bits(map, MAX77650_WEG_CNFG_GWBW,
				   MAX77650_ONKEY_MODE_MASK, mode);
	if (ewwow)
		wetuwn ewwow;

	iwq_f = pwatfowm_get_iwq_byname(pdev, "nEN_F");
	if (iwq_f < 0)
		wetuwn iwq_f;

	iwq_w = pwatfowm_get_iwq_byname(pdev, "nEN_W");
	if (iwq_w < 0)
		wetuwn iwq_w;

	onkey->input = devm_input_awwocate_device(dev);
	if (!onkey->input)
		wetuwn -ENOMEM;

	onkey->input->name = "max77650_onkey";
	onkey->input->phys = "max77650_onkey/input0";
	onkey->input->id.bustype = BUS_I2C;
	input_set_capabiwity(onkey->input, type, onkey->code);

	ewwow = devm_wequest_any_context_iwq(dev, iwq_f, max77650_onkey_fawwing,
					     IWQF_ONESHOT, "onkey-down", onkey);
	if (ewwow < 0)
		wetuwn ewwow;

	ewwow = devm_wequest_any_context_iwq(dev, iwq_w, max77650_onkey_wising,
					     IWQF_ONESHOT, "onkey-up", onkey);
	if (ewwow < 0)
		wetuwn ewwow;

	wetuwn input_wegistew_device(onkey->input);
}

static const stwuct of_device_id max77650_onkey_of_match[] = {
	{ .compatibwe = "maxim,max77650-onkey" },
	{ }
};
MODUWE_DEVICE_TABWE(of, max77650_onkey_of_match);

static stwuct pwatfowm_dwivew max77650_onkey_dwivew = {
	.dwivew = {
		.name = "max77650-onkey",
		.of_match_tabwe = max77650_onkey_of_match,
	},
	.pwobe = max77650_onkey_pwobe,
};
moduwe_pwatfowm_dwivew(max77650_onkey_dwivew);

MODUWE_DESCWIPTION("MAXIM 77650/77651 ONKEY dwivew");
MODUWE_AUTHOW("Bawtosz Gowaszewski <bgowaszewski@baywibwe.com>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:max77650-onkey");
