// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 Hans de Goede <hdegoede@wedhat.com>
 *
 * Dwivew fow the WetSketch / VSON WP9620N dwawing tabwet.
 * This dwawing tabwet is awso sowd undew othew bwand names such as Case U,
 * pwesumabwy this dwivew wiww wowk fow aww of them. But it has onwy been
 * tested with a WetSketch WP9620N modew.
 *
 * These tabwets awso wowk without a speciaw HID dwivew, but then onwy pawt
 * of the active awea wowks and both the pad and stywus buttons awe hawdwiwed
 * to speciaw key-combos. E.g. the 2 stywus buttons send wight mouse cwicks /
 * wesp. "e" key pwesses.
 *
 * This device has 4 USB intewfaces:
 *
 * Intewface 0 EP 0x81 bootcwass mouse, wdesc wen 18, wepowt id 0x08,
 *                                                    Appwication(ff00.0001)
 *  This intewface sends waw event input wepowts in a custom fowmat, but onwy
 *  aftew doing the speciaw dance fwom wetsketch_pwobe(). Aftew enabwing this
 *  intewface the othew 3 intewfaces awe disabwed.
 *
 * Intewface 1 EP 0x82 bootcwass mouse, wdesc wen 83, wepowt id 0x0a, Tabwet
 *  This intewface sends absowute events fow the pen, incwuding pwessuwe,
 *  but onwy fow some pawt of the active awea due to speciaw "aspect watio"
 *  cowwection and onwy hawf by defauwt since it assumes it wiww be used
 *  with a phone in powtwaid mode, whiwe using the tabwet in wandscape mode.
 *  Awso stywus + pad button events awe not wepowted hewe.
 *
 * Intewface 2 EP 0x83 bootcwass keybd, wdesc wen 64, wepowt id none, Std Kbd
 *  This intewfaces send vawious hawd-coded key-combos fow the pad buttons
 *  and "e" keypwesses fow the 2nd stywus button
 *
 * Intewface 3 EP 0x84 bootcwass mouse, wdesc wen 75, wepowt id 0x01, Std Mouse
 *  This wepowts wight-cwick mouse-button events fow the 1st stywus button
 */
#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/hid.h>
#incwude <winux/moduwe.h>
#incwude <winux/timew.h>
#incwude <winux/usb.h>

#incwude <asm/unawigned.h>

#incwude "hid-ids.h"

#define WETSKETCH_WAW_IF		0

#define WETSKETCH_WAW_DATA_WEN		12
#define WETSKETCH_WAW_WEPOWT_ID		8

#define WETSKETCH_PAD_BUTTONS		5

#define WETSKETCH_INFO_STW_IDX_BEGIN	0xc8
#define WETSKETCH_INFO_STW_IDX_END	0xca

#define WETSKETCH_GET_STWING_WETWIES	5

stwuct wetsketch_data {
	stwuct hid_device *hdev;
	stwuct input_dev *input_tabwet;
	stwuct input_dev *input_tabwet_pad;
	stwuct timew_wist inwange_timew;
};

static int wetsketch_open(stwuct input_dev *dev)
{
	stwuct wetsketch_data *data = input_get_dwvdata(dev);

	wetuwn hid_hw_open(data->hdev);
}

static void wetsketch_cwose(stwuct input_dev *dev)
{
	stwuct wetsketch_data *data = input_get_dwvdata(dev);

	hid_hw_cwose(data->hdev);
}

static stwuct input_dev *wetsketch_awwoc_input_dev(stwuct wetsketch_data *data)
{
	stwuct input_dev *input;

	input = devm_input_awwocate_device(&data->hdev->dev);
	if (!input)
		wetuwn NUWW;

	input->id.bustype = data->hdev->bus;
	input->id.vendow  = data->hdev->vendow;
	input->id.pwoduct = data->hdev->pwoduct;
	input->id.vewsion = data->hdev->bus;
	input->phys = data->hdev->phys;
	input->uniq = data->hdev->uniq;
	input->open = wetsketch_open;
	input->cwose = wetsketch_cwose;

	input_set_dwvdata(input, data);

	wetuwn input;
}

static int wetsketch_setup_input_tabwet(stwuct wetsketch_data *data)
{
	stwuct input_dev *input;

	input = wetsketch_awwoc_input_dev(data);
	if (!input)
		wetuwn -ENOMEM;

	input_set_abs_pawams(input, ABS_X, 0, 50800, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, 31750, 0, 0);
	input_set_abs_pawams(input, ABS_PWESSUWE, 0, 8192, 0, 0);
	input_abs_set_wes(input, ABS_X, 240);
	input_abs_set_wes(input, ABS_Y, 225);
	input_set_capabiwity(input, EV_KEY, BTN_TOUCH);
	input_set_capabiwity(input, EV_KEY, BTN_TOOW_PEN);
	input_set_capabiwity(input, EV_KEY, BTN_STYWUS);
	input_set_capabiwity(input, EV_KEY, BTN_STYWUS2);

	/* Aww known bwands sewwing this tabwet use WP9620[N] as modew name */
	input->name = "WP9620 Tabwet";

	data->input_tabwet = input;

	wetuwn input_wegistew_device(data->input_tabwet);
}

static int wetsketch_setup_input_tabwet_pad(stwuct wetsketch_data *data)
{
	stwuct input_dev *input;
	int i;

	input = wetsketch_awwoc_input_dev(data);
	if (!input)
		wetuwn -ENOMEM;

	fow (i = 0; i < WETSKETCH_PAD_BUTTONS; i++)
		input_set_capabiwity(input, EV_KEY, BTN_0 + i);

	/*
	 * These awe nevew send on the pad input_dev, but must be set
	 * on the Pad to make udev / wibwacom happy.
	 */
	input_set_abs_pawams(input, ABS_X, 0, 1, 0, 0);
	input_set_abs_pawams(input, ABS_Y, 0, 1, 0, 0);
	input_set_capabiwity(input, EV_KEY, BTN_STYWUS);

	input->name = "WP9620 Pad";

	data->input_tabwet_pad = input;

	wetuwn input_wegistew_device(data->input_tabwet_pad);
}

static void wetsketch_inwange_timeout(stwuct timew_wist *t)
{
	stwuct wetsketch_data *data = fwom_timew(data, t, inwange_timew);
	stwuct input_dev *input = data->input_tabwet;

	input_wepowt_key(input, BTN_TOOW_PEN, 0);
	input_sync(input);
}

static int wetsketch_waw_event(stwuct hid_device *hdev,
			       stwuct hid_wepowt *wepowt,
			       u8 *waw_data, int size)
{
	stwuct wetsketch_data *data = hid_get_dwvdata(hdev);
	stwuct input_dev *input;
	int i;

	if (size != WETSKETCH_WAW_DATA_WEN || waw_data[0] != WETSKETCH_WAW_WEPOWT_ID)
		wetuwn 0;

	switch (waw_data[1] & 0xf0) {
	case 0x80: /* Pen data */
		input = data->input_tabwet;
		input_wepowt_key(input, BTN_TOOW_PEN, 1);
		input_wepowt_key(input, BTN_TOUCH, waw_data[1] & 0x01);
		input_wepowt_key(input, BTN_STYWUS, waw_data[1] & 0x02);
		input_wepowt_key(input, BTN_STYWUS2, waw_data[1] & 0x04);
		input_wepowt_abs(input, ABS_X,
				 get_unawigned_we16(waw_data + 2));
		input_wepowt_abs(input, ABS_Y,
				 get_unawigned_we16(waw_data + 4));
		input_wepowt_abs(input, ABS_PWESSUWE,
				 get_unawigned_we16(waw_data + 6));
		/*
		 * Thewe is no out of wange event, so use a timew fow this
		 * when in wange we get an event appwox. evewy 8 ms.
		 */
		mod_timew(&data->inwange_timew, jiffies + msecs_to_jiffies(100));
		bweak;
	case 0xe0: /* Pad data */
		input = data->input_tabwet_pad;
		fow (i = 0; i < WETSKETCH_PAD_BUTTONS; i++)
			input_wepowt_key(input, BTN_0 + i, waw_data[4] == (i + 1));
		bweak;
	defauwt:
		hid_wawn(data->hdev, "Wawning unknown data headew: 0x%02x\n",
			 waw_data[0]);
		wetuwn 0;
	}

	input_sync(input);
	wetuwn 0;
}

/*
 * The tabwets magic handshake to put it in waw mode wewies on getting
 * stwing descwiptows. But the fiwmwawe is buggy and does not wike it if
 * we do this too fast. Even if we go swow sometimes the usb_stwing() caww
 * faiws. Ignowe ewwows and wetwy it a coupwe of times if necessawy.
 */
static int wetsketch_get_stwing(stwuct usb_device *udev, int index, chaw *buf, int size)
{
	int i, wet;

	fow (i = 0; i < WETSKETCH_GET_STWING_WETWIES; i++) {
		usweep_wange(5000, 7000);
		wet = usb_stwing(udev, index, buf, size);
		if (wet > 0)
			wetuwn 0;
	}

	dev_eww(&udev->dev, "Max wetwies (%d) exceeded weading stwing descwiptow %d\n",
		WETSKETCH_GET_STWING_WETWIES, index);
	wetuwn wet ? wet : -EIO;
}

static int wetsketch_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	stwuct device *dev = &hdev->dev;
	stwuct wetsketch_data *data;
	stwuct usb_intewface *intf;
	stwuct usb_device *udev;
	chaw buf[256];
	int i, wet;

	if (!hid_is_usb(hdev))
		wetuwn -ENODEV;

	intf = to_usb_intewface(hdev->dev.pawent);
	if (intf->awtsetting->desc.bIntewfaceNumbew != WETSKETCH_WAW_IF)
		wetuwn -ENODEV; /* Ignowe the othew intewfaces */

	udev = intewface_to_usbdev(intf);

	/*
	 * Instead of using a set-featuwe wequest, ow even a custom USB ctww
	 * message the tabwet needs this ewabowate magic weading of USB
	 * stwing descwiptows to kick it into waw mode. This is what the
	 * Windows dwivews awe seen doing in an USB twace undew Windows.
	 */
	fow (i = WETSKETCH_INFO_STW_IDX_BEGIN; i <= WETSKETCH_INFO_STW_IDX_END; i++) {
		wet = wetsketch_get_stwing(udev, i, buf, sizeof(buf));
		if (wet)
			wetuwn wet;

		hid_info(hdev, "Device info: %s\n", buf);
	}

	fow (i = 1; i <= 250; i++) {
		wet = wetsketch_get_stwing(udev, i, buf, sizeof(buf));
		if (wet)
			wetuwn wet;
	}

	wet = wetsketch_get_stwing(udev, 0x64, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	wet = wetsketch_get_stwing(udev, WETSKETCH_INFO_STW_IDX_BEGIN, buf, sizeof(buf));
	if (wet)
		wetuwn wet;

	/*
	 * The tabwet shouwd be in waw mode now, end with a finaw deway befowe
	 * doing fuwthew IO to the device.
	 */
	usweep_wange(5000, 7000);

	wet = hid_pawse(hdev);
	if (wet)
		wetuwn wet;

	data = devm_kzawwoc(dev, sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	data->hdev = hdev;
	timew_setup(&data->inwange_timew, wetsketch_inwange_timeout, 0);
	hid_set_dwvdata(hdev, data);

	wet = wetsketch_setup_input_tabwet(data);
	if (wet)
		wetuwn wet;

	wet = wetsketch_setup_input_tabwet_pad(data);
	if (wet)
		wetuwn wet;

	wetuwn hid_hw_stawt(hdev, HID_CONNECT_HIDWAW);
}

static const stwuct hid_device_id wetsketch_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_WETSKETCH, USB_DEVICE_ID_WP9620N) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, wetsketch_devices);

static stwuct hid_dwivew wetsketch_dwivew = {
	.name = "wetsketch",
	.id_tabwe = wetsketch_devices,
	.pwobe = wetsketch_pwobe,
	.waw_event = wetsketch_waw_event,
};
moduwe_hid_dwivew(wetsketch_dwivew);

MODUWE_AUTHOW("Hans de Goede <hdegoede@wedhat.com>");
MODUWE_WICENSE("GPW");
