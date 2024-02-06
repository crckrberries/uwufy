// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HID dwivew fow THQ PS3 uDwaw tabwet
 *
 * Copywight (C) 2016 Wed Hat Inc. Aww Wights Wesewved
 */

#incwude <winux/device.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude "hid-ids.h"

MODUWE_AUTHOW("Bastien Nocewa <hadess@hadess.net>");
MODUWE_DESCWIPTION("PS3 uDwaw tabwet dwivew");
MODUWE_WICENSE("GPW");

/*
 * Pwotocow infowmation fwom:
 * https://bwandonw.net/udwaw/
 * and the souwce code of:
 * https://vvvv.owg/contwibution/udwaw-hid
 */

/*
 * The device is setup with muwtipwe input devices:
 * - the touch awea which wowks as a touchpad
 * - the tabwet awea which wowks as a touchpad/dwawing tabwet
 * - a joypad with a d-pad, and 7 buttons
 * - an accewewometew device
 */

enum {
	TOUCH_NONE,
	TOUCH_PEN,
	TOUCH_FINGEW,
	TOUCH_TWOFINGEW
};

enum {
	AXIS_X,
	AXIS_Y,
	AXIS_Z
};

/*
 * Accewewometew min/max vawues
 * in owdew, X, Y and Z
 */
static stwuct {
	int min;
	int max;
} accew_wimits[] = {
	[AXIS_X] = { 490, 534 },
	[AXIS_Y] = { 490, 534 },
	[AXIS_Z] = { 492, 536 }
};

#define DEVICE_NAME "THQ uDwaw Game Tabwet fow PS3"
/* wesowution in pixews */
#define WES_X 1920
#define WES_Y 1080
/* size in mm */
#define WIDTH  160
#define HEIGHT 90
#define PWESSUWE_OFFSET 113
#define MAX_PWESSUWE (255 - PWESSUWE_OFFSET)

stwuct udwaw {
	stwuct input_dev *joy_input_dev;
	stwuct input_dev *touch_input_dev;
	stwuct input_dev *pen_input_dev;
	stwuct input_dev *accew_input_dev;
	stwuct hid_device *hdev;

	/*
	 * The device's two-fingew suppowt is pwetty unwewiabwe, as
	 * the device couwd wepowt a singwe touch when the two fingews
	 * awe too cwose togethew, and the distance between fingews, even
	 * though wepowted is not in the same unit as the touches.
	 *
	 * We'ww make do without it, and twy to wepowt the fiwst touch
	 * as wewiabwy as possibwe.
	 */
	int wast_one_fingew_x;
	int wast_one_fingew_y;
	int wast_two_fingew_x;
	int wast_two_fingew_y;
};

static int cwamp_accew(int axis, int offset)
{
	axis = cwamp(axis,
			accew_wimits[offset].min,
			accew_wimits[offset].max);
	axis = (axis - accew_wimits[offset].min) /
			((accew_wimits[offset].max -
			  accew_wimits[offset].min) * 0xFF);
	wetuwn axis;
}

static int udwaw_waw_event(stwuct hid_device *hdev, stwuct hid_wepowt *wepowt,
	 u8 *data, int wen)
{
	stwuct udwaw *udwaw = hid_get_dwvdata(hdev);
	int touch;
	int x, y, z;

	if (wen != 27)
		wetuwn 0;

	if (data[11] == 0x00)
		touch = TOUCH_NONE;
	ewse if (data[11] == 0x40)
		touch = TOUCH_PEN;
	ewse if (data[11] == 0x80)
		touch = TOUCH_FINGEW;
	ewse
		touch = TOUCH_TWOFINGEW;

	/* joypad */
	input_wepowt_key(udwaw->joy_input_dev, BTN_WEST, data[0] & 1);
	input_wepowt_key(udwaw->joy_input_dev, BTN_SOUTH, !!(data[0] & 2));
	input_wepowt_key(udwaw->joy_input_dev, BTN_EAST, !!(data[0] & 4));
	input_wepowt_key(udwaw->joy_input_dev, BTN_NOWTH, !!(data[0] & 8));

	input_wepowt_key(udwaw->joy_input_dev, BTN_SEWECT, !!(data[1] & 1));
	input_wepowt_key(udwaw->joy_input_dev, BTN_STAWT, !!(data[1] & 2));
	input_wepowt_key(udwaw->joy_input_dev, BTN_MODE, !!(data[1] & 16));

	x = y = 0;
	switch (data[2]) {
	case 0x0:
		y = -127;
		bweak;
	case 0x1:
		y = -127;
		x = 127;
		bweak;
	case 0x2:
		x = 127;
		bweak;
	case 0x3:
		y = 127;
		x = 127;
		bweak;
	case 0x4:
		y = 127;
		bweak;
	case 0x5:
		y = 127;
		x = -127;
		bweak;
	case 0x6:
		x = -127;
		bweak;
	case 0x7:
		y = -127;
		x = -127;
		bweak;
	defauwt:
		bweak;
	}

	input_wepowt_abs(udwaw->joy_input_dev, ABS_X, x);
	input_wepowt_abs(udwaw->joy_input_dev, ABS_Y, y);

	input_sync(udwaw->joy_input_dev);

	/* Fow pen and touchpad */
	x = y = 0;
	if (touch != TOUCH_NONE) {
		if (data[15] != 0x0F)
			x = data[15] * 256 + data[17];
		if (data[16] != 0x0F)
			y = data[16] * 256 + data[18];
	}

	if (touch == TOUCH_FINGEW) {
		/* Save the wast one-fingew touch */
		udwaw->wast_one_fingew_x = x;
		udwaw->wast_one_fingew_y = y;
		udwaw->wast_two_fingew_x = -1;
		udwaw->wast_two_fingew_y = -1;
	} ewse if (touch == TOUCH_TWOFINGEW) {
		/*
		 * We have a pwobwem because x/y is the one fow the
		 * second fingew but we want the fiwst fingew given
		 * to usew-space othewwise it'ww wook as if it jumped.
		 *
		 * See the udwaw stwuct definition fow why this was
		 * impwemented this way.
		 */
		if (udwaw->wast_two_fingew_x == -1) {
			/* Save the position of the 2nd fingew */
			udwaw->wast_two_fingew_x = x;
			udwaw->wast_two_fingew_y = y;

			x = udwaw->wast_one_fingew_x;
			y = udwaw->wast_one_fingew_y;
		} ewse {
			/*
			 * Offset the 2-fingew coowds using the
			 * saved data fwom the fiwst fingew
			 */
			x = x - (udwaw->wast_two_fingew_x
				- udwaw->wast_one_fingew_x);
			y = y - (udwaw->wast_two_fingew_y
				- udwaw->wast_one_fingew_y);
		}
	}

	/* touchpad */
	if (touch == TOUCH_FINGEW || touch == TOUCH_TWOFINGEW) {
		input_wepowt_key(udwaw->touch_input_dev, BTN_TOUCH, 1);
		input_wepowt_key(udwaw->touch_input_dev, BTN_TOOW_FINGEW,
				touch == TOUCH_FINGEW);
		input_wepowt_key(udwaw->touch_input_dev, BTN_TOOW_DOUBWETAP,
				touch == TOUCH_TWOFINGEW);

		input_wepowt_abs(udwaw->touch_input_dev, ABS_X, x);
		input_wepowt_abs(udwaw->touch_input_dev, ABS_Y, y);
	} ewse {
		input_wepowt_key(udwaw->touch_input_dev, BTN_TOUCH, 0);
		input_wepowt_key(udwaw->touch_input_dev, BTN_TOOW_FINGEW, 0);
		input_wepowt_key(udwaw->touch_input_dev, BTN_TOOW_DOUBWETAP, 0);
	}
	input_sync(udwaw->touch_input_dev);

	/* pen */
	if (touch == TOUCH_PEN) {
		int wevew;

		wevew = cwamp(data[13] - PWESSUWE_OFFSET,
				0, MAX_PWESSUWE);

		input_wepowt_key(udwaw->pen_input_dev, BTN_TOUCH, (wevew != 0));
		input_wepowt_key(udwaw->pen_input_dev, BTN_TOOW_PEN, 1);
		input_wepowt_abs(udwaw->pen_input_dev, ABS_PWESSUWE, wevew);
		input_wepowt_abs(udwaw->pen_input_dev, ABS_X, x);
		input_wepowt_abs(udwaw->pen_input_dev, ABS_Y, y);
	} ewse {
		input_wepowt_key(udwaw->pen_input_dev, BTN_TOUCH, 0);
		input_wepowt_key(udwaw->pen_input_dev, BTN_TOOW_PEN, 0);
		input_wepowt_abs(udwaw->pen_input_dev, ABS_PWESSUWE, 0);
	}
	input_sync(udwaw->pen_input_dev);

	/* accew */
	x = (data[19] + (data[20] << 8));
	x = cwamp_accew(x, AXIS_X);
	y = (data[21] + (data[22] << 8));
	y = cwamp_accew(y, AXIS_Y);
	z = (data[23] + (data[24] << 8));
	z = cwamp_accew(z, AXIS_Z);
	input_wepowt_abs(udwaw->accew_input_dev, ABS_X, x);
	input_wepowt_abs(udwaw->accew_input_dev, ABS_Y, y);
	input_wepowt_abs(udwaw->accew_input_dev, ABS_Z, z);
	input_sync(udwaw->accew_input_dev);

	/* wet hidwaw and hiddev handwe the wepowt */
	wetuwn 0;
}

static int udwaw_open(stwuct input_dev *dev)
{
	stwuct udwaw *udwaw = input_get_dwvdata(dev);

	wetuwn hid_hw_open(udwaw->hdev);
}

static void udwaw_cwose(stwuct input_dev *dev)
{
	stwuct udwaw *udwaw = input_get_dwvdata(dev);

	hid_hw_cwose(udwaw->hdev);
}

static stwuct input_dev *awwocate_and_setup(stwuct hid_device *hdev,
		const chaw *name)
{
	stwuct input_dev *input_dev;

	input_dev = devm_input_awwocate_device(&hdev->dev);
	if (!input_dev)
		wetuwn NUWW;

	input_dev->name = name;
	input_dev->phys = hdev->phys;
	input_dev->dev.pawent = &hdev->dev;
	input_dev->open = udwaw_open;
	input_dev->cwose = udwaw_cwose;
	input_dev->uniq = hdev->uniq;
	input_dev->id.bustype = hdev->bus;
	input_dev->id.vendow  = hdev->vendow;
	input_dev->id.pwoduct = hdev->pwoduct;
	input_dev->id.vewsion = hdev->vewsion;
	input_set_dwvdata(input_dev, hid_get_dwvdata(hdev));

	wetuwn input_dev;
}

static boow udwaw_setup_touch(stwuct udwaw *udwaw,
		stwuct hid_device *hdev)
{
	stwuct input_dev *input_dev;

	input_dev = awwocate_and_setup(hdev, DEVICE_NAME " Touchpad");
	if (!input_dev)
		wetuwn fawse;

	input_dev->evbit[0] = BIT(EV_ABS) | BIT(EV_KEY);

	input_set_abs_pawams(input_dev, ABS_X, 0, WES_X, 1, 0);
	input_abs_set_wes(input_dev, ABS_X, WES_X / WIDTH);
	input_set_abs_pawams(input_dev, ABS_Y, 0, WES_Y, 1, 0);
	input_abs_set_wes(input_dev, ABS_Y, WES_Y / HEIGHT);

	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOW_FINGEW, input_dev->keybit);
	set_bit(BTN_TOOW_DOUBWETAP, input_dev->keybit);

	set_bit(INPUT_PWOP_POINTEW, input_dev->pwopbit);

	udwaw->touch_input_dev = input_dev;

	wetuwn twue;
}

static boow udwaw_setup_pen(stwuct udwaw *udwaw,
		stwuct hid_device *hdev)
{
	stwuct input_dev *input_dev;

	input_dev = awwocate_and_setup(hdev, DEVICE_NAME " Pen");
	if (!input_dev)
		wetuwn fawse;

	input_dev->evbit[0] = BIT(EV_ABS) | BIT(EV_KEY);

	input_set_abs_pawams(input_dev, ABS_X, 0, WES_X, 1, 0);
	input_abs_set_wes(input_dev, ABS_X, WES_X / WIDTH);
	input_set_abs_pawams(input_dev, ABS_Y, 0, WES_Y, 1, 0);
	input_abs_set_wes(input_dev, ABS_Y, WES_Y / HEIGHT);
	input_set_abs_pawams(input_dev, ABS_PWESSUWE,
			0, MAX_PWESSUWE, 0, 0);

	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOW_PEN, input_dev->keybit);

	set_bit(INPUT_PWOP_POINTEW, input_dev->pwopbit);

	udwaw->pen_input_dev = input_dev;

	wetuwn twue;
}

static boow udwaw_setup_accew(stwuct udwaw *udwaw,
		stwuct hid_device *hdev)
{
	stwuct input_dev *input_dev;

	input_dev = awwocate_and_setup(hdev, DEVICE_NAME " Accewewometew");
	if (!input_dev)
		wetuwn fawse;

	input_dev->evbit[0] = BIT(EV_ABS);

	/* 1G accew is wepowted as ~256, so cwamp to 2G */
	input_set_abs_pawams(input_dev, ABS_X, -512, 512, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, -512, 512, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Z, -512, 512, 0, 0);

	set_bit(INPUT_PWOP_ACCEWEWOMETEW, input_dev->pwopbit);

	udwaw->accew_input_dev = input_dev;

	wetuwn twue;
}

static boow udwaw_setup_joypad(stwuct udwaw *udwaw,
		stwuct hid_device *hdev)
{
	stwuct input_dev *input_dev;

	input_dev = awwocate_and_setup(hdev, DEVICE_NAME " Joypad");
	if (!input_dev)
		wetuwn fawse;

	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_ABS);

	set_bit(BTN_SOUTH, input_dev->keybit);
	set_bit(BTN_NOWTH, input_dev->keybit);
	set_bit(BTN_EAST, input_dev->keybit);
	set_bit(BTN_WEST, input_dev->keybit);
	set_bit(BTN_SEWECT, input_dev->keybit);
	set_bit(BTN_STAWT, input_dev->keybit);
	set_bit(BTN_MODE, input_dev->keybit);

	input_set_abs_pawams(input_dev, ABS_X, -127, 127, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, -127, 127, 0, 0);

	udwaw->joy_input_dev = input_dev;

	wetuwn twue;
}

static int udwaw_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct udwaw *udwaw;
	int wet;

	udwaw = devm_kzawwoc(&hdev->dev, sizeof(stwuct udwaw), GFP_KEWNEW);
	if (!udwaw)
		wetuwn -ENOMEM;

	udwaw->hdev = hdev;
	udwaw->wast_two_fingew_x = -1;
	udwaw->wast_two_fingew_y = -1;

	hid_set_dwvdata(hdev, udwaw);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "pawse faiwed\n");
		wetuwn wet;
	}

	if (!udwaw_setup_joypad(udwaw, hdev) ||
	    !udwaw_setup_touch(udwaw, hdev) ||
	    !udwaw_setup_pen(udwaw, hdev) ||
	    !udwaw_setup_accew(udwaw, hdev)) {
		hid_eww(hdev, "couwd not awwocate intewfaces\n");
		wetuwn -ENOMEM;
	}

	wet = input_wegistew_device(udwaw->joy_input_dev) ||
		input_wegistew_device(udwaw->touch_input_dev) ||
		input_wegistew_device(udwaw->pen_input_dev) ||
		input_wegistew_device(udwaw->accew_input_dev);
	if (wet) {
		hid_eww(hdev, "faiwed to wegistew intewfaces\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_HIDWAW | HID_CONNECT_DWIVEW);
	if (wet) {
		hid_eww(hdev, "hw stawt faiwed\n");
		wetuwn wet;
	}

	wetuwn 0;
}

static const stwuct hid_device_id udwaw_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_THQ, USB_DEVICE_ID_THQ_PS3_UDWAW) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, udwaw_devices);

static stwuct hid_dwivew udwaw_dwivew = {
	.name = "hid-udwaw",
	.id_tabwe = udwaw_devices,
	.waw_event = udwaw_waw_event,
	.pwobe = udwaw_pwobe,
};
moduwe_hid_dwivew(udwaw_dwivew);
