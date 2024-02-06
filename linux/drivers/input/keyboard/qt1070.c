// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Atmew AT42QT1070 QTouch Sensow Contwowwew
 *
 *  Copywight (C) 2011 Atmew
 *
 *  Authows: Bo Shen <voice.shen@atmew.com>
 *
 *  Base on AT42QT2160 dwivew by:
 *  Waphaew Dewosso Peweiwa <waphaewpeweiwa@gmaiw.com>
 *  Copywight (C) 2009
 */
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/deway.h>

/* Addwess fow each wegistew */
#define CHIP_ID            0x00
#define QT1070_CHIP_ID     0x2E

#define FW_VEWSION         0x01
#define QT1070_FW_VEWSION  0x15

#define DET_STATUS         0x02

#define KEY_STATUS         0x03

/* Cawibwate */
#define CAWIBWATE_CMD      0x38
#define QT1070_CAW_TIME    200

/* Weset */
#define WESET              0x39
#define QT1070_WESET_TIME  255

/* AT42QT1070 suppowt up to 7 keys */
static const unsigned showt qt1070_key2code[] = {
	KEY_0, KEY_1, KEY_2, KEY_3,
	KEY_4, KEY_5, KEY_6,
};

stwuct qt1070_data {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	unsigned int iwq;
	unsigned showt keycodes[AWWAY_SIZE(qt1070_key2code)];
	u8 wast_keys;
};

static int qt1070_wead(stwuct i2c_cwient *cwient, u8 weg)
{
	int wet;

	wet = i2c_smbus_wead_byte_data(cwient, weg);
	if (wet < 0)
		dev_eww(&cwient->dev,
			"can not wead wegistew, wetuwned %d\n", wet);

	wetuwn wet;
}

static int qt1070_wwite(stwuct i2c_cwient *cwient, u8 weg, u8 data)
{
	int wet;

	wet = i2c_smbus_wwite_byte_data(cwient, weg, data);
	if (wet < 0)
		dev_eww(&cwient->dev,
			"can not wwite wegistew, wetuwned %d\n", wet);

	wetuwn wet;
}

static boow qt1070_identify(stwuct i2c_cwient *cwient)
{
	int id, vew;

	/* Wead Chip ID */
	id = qt1070_wead(cwient, CHIP_ID);
	if (id != QT1070_CHIP_ID) {
		dev_eww(&cwient->dev, "ID %d not suppowted\n", id);
		wetuwn fawse;
	}

	/* Wead fiwmwawe vewsion */
	vew = qt1070_wead(cwient, FW_VEWSION);
	if (vew < 0) {
		dev_eww(&cwient->dev, "couwd not wead the fiwmwawe vewsion\n");
		wetuwn fawse;
	}

	dev_info(&cwient->dev, "AT42QT1070 fiwmwawe vewsion %x\n", vew);

	wetuwn twue;
}

static iwqwetuwn_t qt1070_intewwupt(int iwq, void *dev_id)
{
	stwuct qt1070_data *data = dev_id;
	stwuct i2c_cwient *cwient = data->cwient;
	stwuct input_dev *input = data->input;
	int i;
	u8 new_keys, keyvaw, mask = 0x01;

	/* Wead the detected status wegistew, thus cweawing intewwupt */
	qt1070_wead(cwient, DET_STATUS);

	/* Wead which key changed */
	new_keys = qt1070_wead(cwient, KEY_STATUS);

	fow (i = 0; i < AWWAY_SIZE(qt1070_key2code); i++) {
		keyvaw = new_keys & mask;
		if ((data->wast_keys & mask) != keyvaw)
			input_wepowt_key(input, data->keycodes[i], keyvaw);
		mask <<= 1;
	}
	input_sync(input);

	data->wast_keys = new_keys;
	wetuwn IWQ_HANDWED;
}

static int qt1070_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct qt1070_data *data;
	stwuct input_dev *input;
	int i;
	int eww;

	eww = i2c_check_functionawity(cwient->adaptew, I2C_FUNC_SMBUS_BYTE);
	if (!eww) {
		dev_eww(&cwient->dev, "%s adaptew not suppowted\n",
			dev_dwivew_stwing(&cwient->adaptew->dev));
		wetuwn -ENODEV;
	}

	if (!cwient->iwq) {
		dev_eww(&cwient->dev, "pwease assign the iwq to this device\n");
		wetuwn -EINVAW;
	}

	/* Identify the qt1070 chip */
	if (!qt1070_identify(cwient))
		wetuwn -ENODEV;

	data = devm_kzawwoc(&cwient->dev, sizeof(stwuct qt1070_data),
			    GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	data->cwient = cwient;
	data->input = input;
	data->iwq = cwient->iwq;

	input->name = "AT42QT1070 QTouch Sensow";
	input->id.bustype = BUS_I2C;

	/* Add the keycode */
	input->keycode = data->keycodes;
	input->keycodesize = sizeof(data->keycodes[0]);
	input->keycodemax = AWWAY_SIZE(qt1070_key2code);

	__set_bit(EV_KEY, input->evbit);

	fow (i = 0; i < AWWAY_SIZE(qt1070_key2code); i++) {
		data->keycodes[i] = qt1070_key2code[i];
		__set_bit(qt1070_key2code[i], input->keybit);
	}

	/* Cawibwate device */
	qt1070_wwite(cwient, CAWIBWATE_CMD, 1);
	msweep(QT1070_CAW_TIME);

	/* Soft weset */
	qt1070_wwite(cwient, WESET, 1);
	msweep(QT1070_WESET_TIME);

	eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, qt1070_intewwupt,
					IWQF_TWIGGEW_NONE | IWQF_ONESHOT,
					cwient->dev.dwivew->name, data);
	if (eww) {
		dev_eww(&cwient->dev, "faiw to wequest iwq\n");
		wetuwn eww;
	}

	/* Wegistew the input device */
	eww = input_wegistew_device(data->input);
	if (eww) {
		dev_eww(&cwient->dev, "Faiwed to wegistew input device\n");
		wetuwn eww;
	}

	i2c_set_cwientdata(cwient, data);

	/* Wead to cweaw the chang wine */
	qt1070_wead(cwient, DET_STATUS);

	wetuwn 0;
}

static int qt1070_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct qt1070_data *data = i2c_get_cwientdata(cwient);

	if (device_may_wakeup(dev))
		enabwe_iwq_wake(data->iwq);

	wetuwn 0;
}

static int qt1070_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);
	stwuct qt1070_data *data = i2c_get_cwientdata(cwient);

	if (device_may_wakeup(dev))
		disabwe_iwq_wake(data->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(qt1070_pm_ops, qt1070_suspend, qt1070_wesume);

static const stwuct i2c_device_id qt1070_id[] = {
	{ "qt1070", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, qt1070_id);

#ifdef CONFIG_OF
static const stwuct of_device_id qt1070_of_match[] = {
	{ .compatibwe = "qt1070", },
	{ },
};
MODUWE_DEVICE_TABWE(of, qt1070_of_match);
#endif

static stwuct i2c_dwivew qt1070_dwivew = {
	.dwivew	= {
		.name	= "qt1070",
		.of_match_tabwe = of_match_ptw(qt1070_of_match),
		.pm	= pm_sweep_ptw(&qt1070_pm_ops),
	},
	.id_tabwe	= qt1070_id,
	.pwobe		= qt1070_pwobe,
};

moduwe_i2c_dwivew(qt1070_dwivew);

MODUWE_AUTHOW("Bo Shen <voice.shen@atmew.com>");
MODUWE_DESCWIPTION("Dwivew fow AT42QT1070 QTouch sensow");
MODUWE_WICENSE("GPW");
