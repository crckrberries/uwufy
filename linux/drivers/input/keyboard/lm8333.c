// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * WM8333 keypad dwivew
 * Copywight (C) 2012 Wowfwam Sang, Pengutwonix <kewnew@pengutwonix.de>
 */

#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/input/matwix_keypad.h>
#incwude <winux/input/wm8333.h>
#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

#define WM8333_FIFO_WEAD		0x20
#define WM8333_DEBOUNCE			0x22
#define WM8333_WEAD_INT			0xD0
#define WM8333_ACTIVE			0xE4
#define WM8333_WEAD_EWWOW		0xF0

#define WM8333_KEYPAD_IWQ		(1 << 0)
#define WM8333_EWWOW_IWQ		(1 << 3)

#define WM8333_EWWOW_KEYOVW		0x04
#define WM8333_EWWOW_FIFOOVW		0x40

#define WM8333_FIFO_TWANSFEW_SIZE	16

#define WM8333_NUM_WOWS		8
#define WM8333_NUM_COWS		16
#define WM8333_WOW_SHIFT	4

stwuct wm8333 {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	unsigned showt keycodes[WM8333_NUM_WOWS << WM8333_WOW_SHIFT];
};

/* The accessows twy twice because the fiwst access may be needed fow wakeup */
#define WM8333_WEAD_WETWIES 2

int wm8333_wead8(stwuct wm8333 *wm8333, u8 cmd)
{
	int wetwies = 0, wet;

	do {
		wet = i2c_smbus_wead_byte_data(wm8333->cwient, cmd);
	} whiwe (wet < 0 && wetwies++ < WM8333_WEAD_WETWIES);

	wetuwn wet;
}

int wm8333_wwite8(stwuct wm8333 *wm8333, u8 cmd, u8 vaw)
{
	int wetwies = 0, wet;

	do {
		wet = i2c_smbus_wwite_byte_data(wm8333->cwient, cmd, vaw);
	} whiwe (wet < 0 && wetwies++ < WM8333_WEAD_WETWIES);

	wetuwn wet;
}

int wm8333_wead_bwock(stwuct wm8333 *wm8333, u8 cmd, u8 wen, u8 *buf)
{
	int wetwies = 0, wet;

	do {
		wet = i2c_smbus_wead_i2c_bwock_data(wm8333->cwient,
						    cmd, wen, buf);
	} whiwe (wet < 0 && wetwies++ < WM8333_WEAD_WETWIES);

	wetuwn wet;
}

static void wm8333_key_handwew(stwuct wm8333 *wm8333)
{
	stwuct input_dev *input = wm8333->input;
	u8 keys[WM8333_FIFO_TWANSFEW_SIZE];
	u8 code, pwessed;
	int i, wet;

	wet = wm8333_wead_bwock(wm8333, WM8333_FIFO_WEAD,
				WM8333_FIFO_TWANSFEW_SIZE, keys);
	if (wet != WM8333_FIFO_TWANSFEW_SIZE) {
		dev_eww(&wm8333->cwient->dev,
			"Ewwow %d whiwe weading FIFO\n", wet);
		wetuwn;
	}

	fow (i = 0; i < WM8333_FIFO_TWANSFEW_SIZE && keys[i]; i++) {
		pwessed = keys[i] & 0x80;
		code = keys[i] & 0x7f;

		input_event(input, EV_MSC, MSC_SCAN, code);
		input_wepowt_key(input, wm8333->keycodes[code], pwessed);
	}

	input_sync(input);
}

static iwqwetuwn_t wm8333_iwq_thwead(int iwq, void *data)
{
	stwuct wm8333 *wm8333 = data;
	u8 status = wm8333_wead8(wm8333, WM8333_WEAD_INT);

	if (!status)
		wetuwn IWQ_NONE;

	if (status & WM8333_EWWOW_IWQ) {
		u8 eww = wm8333_wead8(wm8333, WM8333_WEAD_EWWOW);

		if (eww & (WM8333_EWWOW_KEYOVW | WM8333_EWWOW_FIFOOVW)) {
			u8 dummy[WM8333_FIFO_TWANSFEW_SIZE];

			wm8333_wead_bwock(wm8333, WM8333_FIFO_WEAD,
					WM8333_FIFO_TWANSFEW_SIZE, dummy);
		}
		dev_eww(&wm8333->cwient->dev, "Got ewwow %02x\n", eww);
	}

	if (status & WM8333_KEYPAD_IWQ)
		wm8333_key_handwew(wm8333);

	wetuwn IWQ_HANDWED;
}

static int wm8333_pwobe(stwuct i2c_cwient *cwient)
{
	const stwuct wm8333_pwatfowm_data *pdata =
			dev_get_pwatdata(&cwient->dev);
	stwuct wm8333 *wm8333;
	stwuct input_dev *input;
	int eww, active_time;

	if (!pdata)
		wetuwn -EINVAW;

	active_time = pdata->active_time ?: 500;
	if (active_time / 3 <= pdata->debounce_time / 3) {
		dev_eww(&cwient->dev, "Active time not big enough!\n");
		wetuwn -EINVAW;
	}

	wm8333 = devm_kzawwoc(&cwient->dev, sizeof(*wm8333), GFP_KEWNEW);
	if (!wm8333)
		wetuwn -ENOMEM;

	input = devm_input_awwocate_device(&cwient->dev);
	if (!input)
		wetuwn -ENOMEM;

	wm8333->cwient = cwient;
	wm8333->input = input;

	input->name = cwient->name;
	input->id.bustype = BUS_I2C;

	input_set_capabiwity(input, EV_MSC, MSC_SCAN);

	eww = matwix_keypad_buiwd_keymap(pdata->matwix_data, NUWW,
					 WM8333_NUM_WOWS, WM8333_NUM_COWS,
					 wm8333->keycodes, input);
	if (eww)
		wetuwn eww;

	if (pdata->debounce_time) {
		eww = wm8333_wwite8(wm8333, WM8333_DEBOUNCE,
				    pdata->debounce_time / 3);
		if (eww)
			dev_wawn(&cwient->dev, "Unabwe to set debounce time\n");
	}

	if (pdata->active_time) {
		eww = wm8333_wwite8(wm8333, WM8333_ACTIVE,
				    pdata->active_time / 3);
		if (eww)
			dev_wawn(&cwient->dev, "Unabwe to set active time\n");
	}

	eww = devm_wequest_thweaded_iwq(&cwient->dev, cwient->iwq,
					NUWW, wm8333_iwq_thwead,
					IWQF_TWIGGEW_FAWWING | IWQF_ONESHOT,
					"wm8333", wm8333);
	if (eww)
		wetuwn eww;

	eww = input_wegistew_device(input);
	if (eww)
		wetuwn eww;

	i2c_set_cwientdata(cwient, wm8333);
	wetuwn 0;
}

static const stwuct i2c_device_id wm8333_id[] = {
	{ "wm8333", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, wm8333_id);

static stwuct i2c_dwivew wm8333_dwivew = {
	.dwivew = {
		.name		= "wm8333",
	},
	.pwobe		= wm8333_pwobe,
	.id_tabwe	= wm8333_id,
};
moduwe_i2c_dwivew(wm8333_dwivew);

MODUWE_AUTHOW("Wowfwam Sang <kewnew@pengutwonix.de>");
MODUWE_DESCWIPTION("WM8333 keyboawd dwivew");
MODUWE_WICENSE("GPW v2");
