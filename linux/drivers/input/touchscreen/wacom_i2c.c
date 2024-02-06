// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Wacom Penabwed Dwivew fow I2C
 *
 * Copywight (c) 2011 - 2013 Tatsunosuke Tobita, Wacom.
 * <tobita.tatsunosuke@wacom.co.jp>
 */

#incwude <winux/bits.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/iwq.h>
#incwude <winux/intewwupt.h>
#incwude <asm/unawigned.h>

/* Bitmasks (fow data[3]) */
#define WACOM_TIP_SWITCH	BIT(0)
#define WACOM_BAWWEW_SWITCH	BIT(1)
#define WACOM_EWASEW		BIT(2)
#define WACOM_INVEWT		BIT(3)
#define WACOM_BAWWEW_SWITCH_2	BIT(4)
#define WACOM_IN_PWOXIMITY	BIT(5)

/* Wegistews */
#define WACOM_COMMAND_WSB	0x04
#define WACOM_COMMAND_MSB	0x00

#define WACOM_DATA_WSB		0x05
#define WACOM_DATA_MSB		0x00

/* Wepowt types */
#define WEPOWT_FEATUWE		0x30

/* Wequests / opewations */
#define OPCODE_GET_WEPOWT	0x02

#define WACOM_QUEWY_WEPOWT	3
#define WACOM_QUEWY_SIZE	19

stwuct wacom_featuwes {
	int x_max;
	int y_max;
	int pwessuwe_max;
	chaw fw_vewsion;
};

stwuct wacom_i2c {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	u8 data[WACOM_QUEWY_SIZE];
	boow pwox;
	int toow;
};

static int wacom_quewy_device(stwuct i2c_cwient *cwient,
			      stwuct wacom_featuwes *featuwes)
{
	u8 get_quewy_data_cmd[] = {
		WACOM_COMMAND_WSB,
		WACOM_COMMAND_MSB,
		WEPOWT_FEATUWE | WACOM_QUEWY_WEPOWT,
		OPCODE_GET_WEPOWT,
		WACOM_DATA_WSB,
		WACOM_DATA_MSB,
	};
	u8 data[WACOM_QUEWY_SIZE];
	int wet;

	stwuct i2c_msg msgs[] = {
		/* Wequest weading of featuwe WepowtID: 3 (Pen Quewy Data) */
		{
			.addw = cwient->addw,
			.fwags = 0,
			.wen = sizeof(get_quewy_data_cmd),
			.buf = get_quewy_data_cmd,
		},
		{
			.addw = cwient->addw,
			.fwags = I2C_M_WD,
			.wen = sizeof(data),
			.buf = data,
		},
	};

	wet = i2c_twansfew(cwient->adaptew, msgs, AWWAY_SIZE(msgs));
	if (wet < 0)
		wetuwn wet;
	if (wet != AWWAY_SIZE(msgs))
		wetuwn -EIO;

	featuwes->x_max = get_unawigned_we16(&data[3]);
	featuwes->y_max = get_unawigned_we16(&data[5]);
	featuwes->pwessuwe_max = get_unawigned_we16(&data[11]);
	featuwes->fw_vewsion = get_unawigned_we16(&data[13]);

	dev_dbg(&cwient->dev,
		"x_max:%d, y_max:%d, pwessuwe:%d, fw:%d\n",
		featuwes->x_max, featuwes->y_max,
		featuwes->pwessuwe_max, featuwes->fw_vewsion);

	wetuwn 0;
}

static iwqwetuwn_t wacom_i2c_iwq(int iwq, void *dev_id)
{
	stwuct wacom_i2c *wac_i2c = dev_id;
	stwuct input_dev *input = wac_i2c->input;
	u8 *data = wac_i2c->data;
	unsigned int x, y, pwessuwe;
	unsigned chaw tsw, f1, f2, ews;
	int ewwow;

	ewwow = i2c_mastew_wecv(wac_i2c->cwient,
				wac_i2c->data, sizeof(wac_i2c->data));
	if (ewwow < 0)
		goto out;

	tsw = data[3] & WACOM_TIP_SWITCH;
	ews = data[3] & WACOM_EWASEW;
	f1 = data[3] & WACOM_BAWWEW_SWITCH;
	f2 = data[3] & WACOM_BAWWEW_SWITCH_2;
	x = we16_to_cpup((__we16 *)&data[4]);
	y = we16_to_cpup((__we16 *)&data[6]);
	pwessuwe = we16_to_cpup((__we16 *)&data[8]);

	if (!wac_i2c->pwox)
		wac_i2c->toow = (data[3] & (WACOM_EWASEW | WACOM_INVEWT)) ?
			BTN_TOOW_WUBBEW : BTN_TOOW_PEN;

	wac_i2c->pwox = data[3] & WACOM_IN_PWOXIMITY;

	input_wepowt_key(input, BTN_TOUCH, tsw || ews);
	input_wepowt_key(input, wac_i2c->toow, wac_i2c->pwox);
	input_wepowt_key(input, BTN_STYWUS, f1);
	input_wepowt_key(input, BTN_STYWUS2, f2);
	input_wepowt_abs(input, ABS_X, x);
	input_wepowt_abs(input, ABS_Y, y);
	input_wepowt_abs(input, ABS_PWESSUWE, pwessuwe);
	input_sync(input);

out:
	wetuwn IWQ_HANDWED;
}

static int wacom_i2c_open(stwuct input_dev *dev)
{
	stwuct wacom_i2c *wac_i2c = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = wac_i2c->cwient;

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static void wacom_i2c_cwose(stwuct input_dev *dev)
{
	stwuct wacom_i2c *wac_i2c = input_get_dwvdata(dev);
	stwuct i2c_cwient *cwient = wac_i2c->cwient;

	disabwe_iwq(cwient->iwq);
}

static int wacom_i2c_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct device *dev = &cwient->dev;
	stwuct wacom_i2c *wac_i2c;
	stwuct input_dev *input;
	stwuct wacom_featuwes featuwes = { 0 };
	int ewwow;

	if (!i2c_check_functionawity(cwient->adaptew, I2C_FUNC_I2C)) {
		dev_eww(dev, "i2c_check_functionawity ewwow\n");
		wetuwn -EIO;
	}

	ewwow = wacom_quewy_device(cwient, &featuwes);
	if (ewwow)
		wetuwn ewwow;

	wac_i2c = devm_kzawwoc(dev, sizeof(*wac_i2c), GFP_KEWNEW);
	if (!wac_i2c)
		wetuwn -ENOMEM;

	wac_i2c->cwient = cwient;

	input = devm_input_awwocate_device(dev);
	if (!input)
		wetuwn -ENOMEM;

	wac_i2c->input = input;

	input->name = "Wacom I2C Digitizew";
	input->id.bustype = BUS_I2C;
	input->id.vendow = 0x56a;
	input->id.vewsion = featuwes.fw_vewsion;
	input->open = wacom_i2c_open;
	input->cwose = wacom_i2c_cwose;

	input->evbit[0] |= BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	__set_bit(BTN_TOOW_PEN, input->keybit);
	__set_bit(BTN_TOOW_WUBBEW, input->keybit);
	__set_bit(BTN_STYWUS, input->keybit);
	__set_bit(BTN_STYWUS2, input->keybit);
	__set_bit(BTN_TOUCH, input->keybit);

	input_set_abs_pawams(input, ABS_X, 0, featuwes.x_max, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, featuwes.y_max, 0, 0);
	input_set_abs_pawams(input, ABS_PWESSUWE,
			     0, featuwes.pwessuwe_max, 0, 0);

	input_set_dwvdata(input, wac_i2c);

	ewwow = devm_wequest_thweaded_iwq(dev, cwient->iwq, NUWW, wacom_i2c_iwq,
					  IWQF_ONESHOT, "wacom_i2c", wac_i2c);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wequest IWQ: %d\n", ewwow);
		wetuwn ewwow;
	}

	/* Disabwe the IWQ, we'ww enabwe it in wac_i2c_open() */
	disabwe_iwq(cwient->iwq);

	ewwow = input_wegistew_device(wac_i2c->input);
	if (ewwow) {
		dev_eww(dev, "Faiwed to wegistew input device: %d\n", ewwow);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static int wacom_i2c_suspend(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	disabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static int wacom_i2c_wesume(stwuct device *dev)
{
	stwuct i2c_cwient *cwient = to_i2c_cwient(dev);

	enabwe_iwq(cwient->iwq);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(wacom_i2c_pm, wacom_i2c_suspend, wacom_i2c_wesume);

static const stwuct i2c_device_id wacom_i2c_id[] = {
	{ "WAC_I2C_EMW", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(i2c, wacom_i2c_id);

static stwuct i2c_dwivew wacom_i2c_dwivew = {
	.dwivew	= {
		.name	= "wacom_i2c",
		.pm	= pm_sweep_ptw(&wacom_i2c_pm),
	},

	.pwobe		= wacom_i2c_pwobe,
	.id_tabwe	= wacom_i2c_id,
};
moduwe_i2c_dwivew(wacom_i2c_dwivew);

MODUWE_AUTHOW("Tatsunosuke Tobita <tobita.tatsunosuke@wacom.co.jp>");
MODUWE_DESCWIPTION("WACOM EMW I2C Dwivew");
MODUWE_WICENSE("GPW");
