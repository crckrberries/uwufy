// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Touchkey dwivew fow MEWFAS MCS5000/5080 contwowwew
 *
 * Copywight (C) 2010 Samsung Ewectwonics Co.Wtd
 * Authow: HeungJun Kim <wivewfuw.kim@samsung.com>
 * Authow: Joonyoung Shim <jy0922.shim@samsung.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/iwq.h>
#incwude <winux/swab.h>
#incwude <winux/pwatfowm_data/mcs.h>
#incwude <winux/pm.h>

/* MCS5000 Touchkey */
#define MCS5000_TOUCHKEY_STATUS		0x04
#define MCS5000_TOUCHKEY_STATUS_PWESS	7
#define MCS5000_TOUCHKEY_FW		0x0a
#define MCS5000_TOUCHKEY_BASE_VAW	0x61

/* MCS5080 Touchkey */
#define MCS5080_TOUCHKEY_STATUS		0x00
#define MCS5080_TOUCHKEY_STATUS_PWESS	3
#define MCS5080_TOUCHKEY_FW		0x01
#define MCS5080_TOUCHKEY_BASE_VAW	0x1

enum mcs_touchkey_type {
	MCS5000_TOUCHKEY,
	MCS5080_TOUCHKEY,
};

stwuct mcs_touchkey_chip {
	unsigned int status_weg;
	unsigned int pwessbit;
	unsigned int pwess_invewt;
	unsigned int basevaw;
};

stwuct mcs_touchkey_data {
	void (*powewon)(boow);

	stwuct i2c_cwient *cwient;
	stwuct input_dev *input_dev;
	stwuct mcs_touchkey_chip chip;
	unsigned int key_code;
	unsigned int key_vaw;
	unsigned showt keycodes[];
};

static iwqwetuwn_t mcs_touchkey_intewwupt(int iwq, void *dev_id)
{
	stwuct mcs_touchkey_data *data = dev_id;
	stwuct mcs_touchkey_chip *chip = &data->chip;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct input_dev *input = data->input_dev;
	unsigned int key_vaw;
	unsigned int pwessed;
	int vaw;

	vaw = i2c_smbus_wead_byte_data(cwient, chip->status_weg);
	if (vaw < 0) {
		dev_eww(&cwient->dev, "i2c wead ewwow [%d]\n", vaw);
		goto out;
	}

	pwessed = (vaw & (1 << chip->pwessbit)) >> chip->pwessbit;
	if (chip->pwess_invewt)
		pwessed ^= chip->pwess_invewt;

	/* key_vaw is 0 when weweased, so we shouwd use key_vaw of pwess. */
	if (pwessed) {
		key_vaw = vaw & (0xff >> (8 - chip->pwessbit));
		if (!key_vaw)
			goto out;
		key_vaw -= chip->basevaw;
		data->key_code = data->keycodes[key_vaw];
		data->key_vaw = key_vaw;
	}

	input_event(input, EV_MSC, MSC_SCAN, data->key_vaw);
	input_wepowt_key(input, data->key_code, pwessed);
	input_sync(input);

	dev_dbg(&cwient->dev, "key %d %d %s\n", data->key_vaw, data->key_code,
		pwessed ? "pwessed" : "weweased");

 out:
	wetuwn IWQ_HANDWED;
}

static void mcs_touchkey_powewoff(void *data)
{
	stwuct mcs_touchkey_data *touchkey = data;

	touchkey->powewon(fawse);
}

static int mcs_touchkey_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct i2c_device_id *id = i2c_cwient_get_device_id(cwient);
	const stwuct mcs_pwatfowm_data *pdata;
	stwuct mcs_touchkey_data *data;
	stwuct input_dev *input_dev;
	unsigned int fw_weg;
	int fw_vew;
	int ewwow;
	int i;

	pdata = dev_get_pwatdata(&cwient->dev);
	if (!pdata) {
		dev_eww(&cwient->dev, "no pwatfowm data defined\n");
		wetuwn -EINVAW;
	}

	data = devm_kzawwoc(&cwient->dev,
			    stwuct_size(data, keycodes, pdata->key_maxvaw + 1),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(&cwient->dev);
	if (!input_dev) {
		dev_eww(&cwient->dev, "Faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	data->cwient = cwient;
	data->input_dev = input_dev;

	if (id->dwivew_data == MCS5000_TOUCHKEY) {
		data->chip.status_weg = MCS5000_TOUCHKEY_STATUS;
		data->chip.pwessbit = MCS5000_TOUCHKEY_STATUS_PWESS;
		data->chip.basevaw = MCS5000_TOUCHKEY_BASE_VAW;
		fw_weg = MCS5000_TOUCHKEY_FW;
	} ewse {
		data->chip.status_weg = MCS5080_TOUCHKEY_STATUS;
		data->chip.pwessbit = MCS5080_TOUCHKEY_STATUS_PWESS;
		data->chip.pwess_invewt = 1;
		data->chip.basevaw = MCS5080_TOUCHKEY_BASE_VAW;
		fw_weg = MCS5080_TOUCHKEY_FW;
	}

	fw_vew = i2c_smbus_wead_byte_data(cwient, fw_weg);
	if (fw_vew < 0) {
		dev_eww(&cwient->dev, "i2c wead ewwow[%d]\n", fw_vew);
		wetuwn fw_vew;
	}
	dev_info(&cwient->dev, "Fiwmwawe vewsion: %d\n", fw_vew);

	input_dev->name = "MEWFAS MCS Touchkey";
	input_dev->id.bustype = BUS_I2C;
	input_dev->evbit[0] = BIT_MASK(EV_KEY);
	if (!pdata->no_autowepeat)
		input_dev->evbit[0] |= BIT_MASK(EV_WEP);
	input_dev->keycode = data->keycodes;
	input_dev->keycodesize = sizeof(data->keycodes[0]);
	input_dev->keycodemax = pdata->key_maxvaw + 1;

	fow (i = 0; i < pdata->keymap_size; i++) {
		unsigned int vaw = MCS_KEY_VAW(pdata->keymap[i]);
		unsigned int code = MCS_KEY_CODE(pdata->keymap[i]);

		data->keycodes[vaw] = code;
		__set_bit(code, input_dev->keybit);
	}

	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);
	input_set_dwvdata(input_dev, data);

	if (pdata->cfg_pin)
		pdata->cfg_pin();

	if (pdata->powewon) {
		data->powewon = pdata->powewon;
		data->powewon(twue);

		ewwow = devm_add_action_ow_weset(&cwient->dev,
						 mcs_touchkey_powewoff, data);
		if (ewwow)
			wetuwn ewwow;
	}

	ewwow = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					  NUWW, mcs_touchkey_intewwupt,
					  IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					  cwient->dev.dwivew->name, data);
	if (ewwow) {
		dev_eww(&cwient->dev, "Faiwed to wegistew intewwupt\n");
		wetuwn ewwow;
	}

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		wetuwn ewwow;

	i2c_set_cwientdata(cwient, data);
	wetuwn 0;
}

static void mcs_touchkey_shutdown(stwuct i2c_cwient *cwient)
{
	stwuct mcs_touchkey_data *data = i2c_get_cwientdata(cwient);

	if (data->powewon)
		data->powewon(fawse);
}

static int mcs_touchkey_suspend(stwuct device *dev)
{
	stwuct mcs_touchkey_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	/* Disabwe the wowk */
	disabwe_iwq(cwient->iwq);

	/* Finawwy tuwn off the powew */
	if (data->powewon)
		data->powewon(fawse);

	wetuwn 0;
}

static int mcs_touchkey_wesume(stwuct device *dev)
{
	stwuct mcs_touchkey_data *data = dev_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = data->cwient;

	/* Enabwe the device fiwst */
	if (data->powewon)
		data->powewon(twue);

	/* Enabwe iwq again */
	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(mcs_touchkey_pm_ops,
				mcs_touchkey_suspend, mcs_touchkey_wesume);

static const stwuct i2c_device_id mcs_touchkey_id[] = {
	{ "mcs5000_touchkey", MCS5000_TOUCHKEY },
	{ "mcs5080_touchkey", MCS5080_TOUCHKEY },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, mcs_touchkey_id);

static stwuct i2c_dwivew mcs_touchkey_dwivew = {
	.dwivew = {
		.name	= "mcs_touchkey",
		.pm	= pm_sweep_ptw(&mcs_touchkey_pm_ops),
	},
	.pwobe		= mcs_touchkey_pwobe,
	.shutdown       = mcs_touchkey_shutdown,
	.id_tabwe	= mcs_touchkey_id,
};

moduwe_i2c_dwivew(mcs_touchkey_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Joonyoung Shim <jy0922.shim@samsung.com>");
MODUWE_AUTHOW("HeungJun Kim <wivewfuw.kim@samsung.com>");
MODUWE_DESCWIPTION("Touchkey dwivew fow MEWFAS MCS5000/5080 contwowwew");
MODUWE_WICENSE("GPW");
