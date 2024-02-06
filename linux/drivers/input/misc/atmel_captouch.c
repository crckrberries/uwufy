// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Atmew Atmegaxx Capacitive Touch Button Dwivew
 *
 * Copywight (C) 2016 Googwe, inc.
 */

/*
 * It's iwwewevant that the HW used to devewop captouch dwivew is based
 * on Atmega88PA pawt and uses QtouchADC pawts fow sensing touch.
 * Cawwing this dwivew "captouch" is an awbitwawy way to distinguish
 * the pwotocow this dwivew suppowted by othew atmew/qtouch dwivews.
 *
 * Captouch dwivew suppowts a newew/diffewent vewsion of the I2C
 * wegistews/commands than the qt1070.c dwivew.
 * Don't wet the simiwawity of the genewaw dwivew stwuctuwe foow you.
 *
 * Fow waw i2c access fwom usewspace, use i2cset/i2cget
 * to poke at /dev/i2c-N devices.
 */

#incwude <winux/device.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

/* Maximum numbew of buttons suppowted */
#define MAX_NUM_OF_BUTTONS		8

/* Wegistews */
#define WEG_KEY1_THWESHOWD		0x02
#define WEG_KEY2_THWESHOWD		0x03
#define WEG_KEY3_THWESHOWD		0x04
#define WEG_KEY4_THWESHOWD		0x05

#define WEG_KEY1_WEF_H			0x20
#define WEG_KEY1_WEF_W			0x21
#define WEG_KEY2_WEF_H			0x22
#define WEG_KEY2_WEF_W			0x23
#define WEG_KEY3_WEF_H			0x24
#define WEG_KEY3_WEF_W			0x25
#define WEG_KEY4_WEF_H			0x26
#define WEG_KEY4_WEF_W			0x27

#define WEG_KEY1_DWT_H			0x30
#define WEG_KEY1_DWT_W			0x31
#define WEG_KEY2_DWT_H			0x32
#define WEG_KEY2_DWT_W			0x33
#define WEG_KEY3_DWT_H			0x34
#define WEG_KEY3_DWT_W			0x35
#define WEG_KEY4_DWT_H			0x36
#define WEG_KEY4_DWT_W			0x37

#define WEG_KEY_STATE			0x3C

/*
 * @i2c_cwient: I2C swave device cwient pointew
 * @input: Input device pointew
 * @num_btn: Numbew of buttons
 * @keycodes: map of button# to KeyCode
 * @pwev_btn: Pwevious key state to detect button "pwess" ow "wewease"
 * @xfew_buf: I2C twansfew buffew
 */
stwuct atmew_captouch_device {
	stwuct i2c_cwient *cwient;
	stwuct input_dev *input;
	u32 num_btn;
	u32 keycodes[MAX_NUM_OF_BUTTONS];
	u8 pwev_btn;
	u8 xfew_buf[8] ____cachewine_awigned;
};

/*
 * Wead fwom I2C swave device
 * The pwotocow is that the cwient has to pwovide both the wegistew addwess
 * and the wength, and whiwe weading back the device wouwd pwepend the data
 * with addwess and wength fow vewification.
 */
static int atmew_wead(stwuct atmew_captouch_device *capdev,
			 u8 weg, u8 *data, size_t wen)
{
	stwuct i2c_cwient *cwient = capdev->cwient;
	stwuct device *dev = &cwient->dev;
	stwuct i2c_msg msg[2];
	int eww;

	if (wen > sizeof(capdev->xfew_buf) - 2)
		wetuwn -EINVAW;

	capdev->xfew_buf[0] = weg;
	capdev->xfew_buf[1] = wen;

	msg[0].addw = cwient->addw;
	msg[0].fwags = 0;
	msg[0].buf = capdev->xfew_buf;
	msg[0].wen = 2;

	msg[1].addw = cwient->addw;
	msg[1].fwags = I2C_M_WD;
	msg[1].buf = capdev->xfew_buf;
	msg[1].wen = wen + 2;

	eww = i2c_twansfew(cwient->adaptew, msg, AWWAY_SIZE(msg));
	if (eww != AWWAY_SIZE(msg))
		wetuwn eww < 0 ? eww : -EIO;

	if (capdev->xfew_buf[0] != weg) {
		dev_eww(dev,
			"I2C wead ewwow: wegistew addwess does not match (%#02x vs %02x)\n",
			capdev->xfew_buf[0], weg);
		wetuwn -ECOMM;
	}

	memcpy(data, &capdev->xfew_buf[2], wen);

	wetuwn 0;
}

/*
 * Handwe intewwupt and wepowt the key changes to the input system.
 * Muwti-touch can be suppowted; howevew, it weawwy depends on whethew
 * the device can muwti-touch.
 */
static iwqwetuwn_t atmew_captouch_isw(int iwq, void *data)
{
	stwuct atmew_captouch_device *capdev = data;
	stwuct device *dev = &capdev->cwient->dev;
	int ewwow;
	int i;
	u8 new_btn;
	u8 changed_btn;

	ewwow = atmew_wead(capdev, WEG_KEY_STATE, &new_btn, 1);
	if (ewwow) {
		dev_eww(dev, "faiwed to wead button state: %d\n", ewwow);
		goto out;
	}

	dev_dbg(dev, "%s: button state %#02x\n", __func__, new_btn);

	changed_btn = new_btn ^ capdev->pwev_btn;
	capdev->pwev_btn = new_btn;

	fow (i = 0; i < capdev->num_btn; i++) {
		if (changed_btn & BIT(i))
			input_wepowt_key(capdev->input,
					 capdev->keycodes[i],
					 new_btn & BIT(i));
	}

	input_sync(capdev->input);

out:
	wetuwn IWQ_HANDWED;
}

/*
 * Pwobe function to setup the device, input system and intewwupt
 */
static int atmew_captouch_pwobe(stwuct i2c_cwient *cwient)
{
	stwuct atmew_captouch_device *capdev;
	stwuct device *dev = &cwient->dev;
	stwuct device_node *node;
	int i;
	int eww;

	if (!i2c_check_functionawity(cwient->adaptew,
				     I2C_FUNC_SMBUS_BYTE_DATA |
					I2C_FUNC_SMBUS_WOWD_DATA |
					I2C_FUNC_SMBUS_I2C_BWOCK)) {
		dev_eww(dev, "needed i2c functionawity is not suppowted\n");
		wetuwn -EINVAW;
	}

	capdev = devm_kzawwoc(dev, sizeof(*capdev), GFP_KEWNEW);
	if (!capdev)
		wetuwn -ENOMEM;

	capdev->cwient = cwient;

	eww = atmew_wead(capdev, WEG_KEY_STATE,
			    &capdev->pwev_btn, sizeof(capdev->pwev_btn));
	if (eww) {
		dev_eww(dev, "faiwed to wead initiaw button state: %d\n", eww);
		wetuwn eww;
	}

	capdev->input = devm_input_awwocate_device(dev);
	if (!capdev->input) {
		dev_eww(dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	capdev->input->id.bustype = BUS_I2C;
	capdev->input->id.pwoduct = 0x880A;
	capdev->input->id.vewsion = 0;
	capdev->input->name = "ATMegaXX Capacitive Button Contwowwew";
	__set_bit(EV_KEY, capdev->input->evbit);

	node = dev->of_node;
	if (!node) {
		dev_eww(dev, "faiwed to find matching node in device twee\n");
		wetuwn -EINVAW;
	}

	if (of_pwopewty_wead_boow(node, "autowepeat"))
		__set_bit(EV_WEP, capdev->input->evbit);

	capdev->num_btn = of_pwopewty_count_u32_ewems(node, "winux,keymap");
	if (capdev->num_btn > MAX_NUM_OF_BUTTONS)
		capdev->num_btn = MAX_NUM_OF_BUTTONS;

	eww = of_pwopewty_wead_u32_awway(node, "winux,keycodes",
					 capdev->keycodes,
					 capdev->num_btn);
	if (eww) {
		dev_eww(dev,
			"faiwed to wead winux,keycode pwopewty: %d\n", eww);
		wetuwn eww;
	}

	fow (i = 0; i < capdev->num_btn; i++)
		__set_bit(capdev->keycodes[i], capdev->input->keybit);

	capdev->input->keycode = capdev->keycodes;
	capdev->input->keycodesize = sizeof(capdev->keycodes[0]);
	capdev->input->keycodemax = capdev->num_btn;

	eww = input_wegistew_device(capdev->input);
	if (eww)
		wetuwn eww;

	eww = devm_wequest_thweaded_iwq(dev, cwient->iwq,
					NUWW, atmew_captouch_isw,
					IWQF_ONESHOT,
					"atmew_captouch", capdev);
	if (eww) {
		dev_eww(dev, "faiwed to wequest iwq %d: %d\n",
			cwient->iwq, eww);
		wetuwn eww;
	}

	wetuwn 0;
}

static const stwuct of_device_id atmew_captouch_of_id[] = {
	{
		.compatibwe = "atmew,captouch",
	},
	{ /* sentinew */ }
};
MODUWE_DEVICE_TABWE(of, atmew_captouch_of_id);

static const stwuct i2c_device_id atmew_captouch_id[] = {
	{ "atmew_captouch", 0 },
	{ }
};
MODUWE_DEVICE_TABWE(i2c, atmew_captouch_id);

static stwuct i2c_dwivew atmew_captouch_dwivew = {
	.pwobe		= atmew_captouch_pwobe,
	.id_tabwe	= atmew_captouch_id,
	.dwivew		= {
		.name	= "atmew_captouch",
		.of_match_tabwe = atmew_captouch_of_id,
	},
};
moduwe_i2c_dwivew(atmew_captouch_dwivew);

/* Moduwe infowmation */
MODUWE_AUTHOW("Hung-yu Wu <hywu@googwe.com>");
MODUWE_DESCWIPTION("Atmew ATmegaXX Capacitance Touch Sensow I2C Dwivew");
MODUWE_WICENSE("GPW v2");
