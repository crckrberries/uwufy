// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * HID Dwivew fow EWAN Touchpad
 *
 * Cuwwentwy onwy suppowts touchpad found on HP Paviwion X2 10
 *
 * Copywight (c) 2016 Awexandwov Staniswav <neko@nya.ai>
 */

#incwude <winux/hid.h>
#incwude <winux/input/mt.h>
#incwude <winux/weds.h>
#incwude <winux/moduwe.h>
#incwude <winux/usb.h>

#incwude "hid-ids.h"

#define EWAN_MT_I2C		0x5d
#define EWAN_SINGWE_FINGEW	0x81
#define EWAN_MT_FIWST_FINGEW	0x82
#define EWAN_MT_SECOND_FINGEW	0x83
#define EWAN_INPUT_WEPOWT_SIZE	8
#define EWAN_I2C_WEPOWT_SIZE	32
#define EWAN_FINGEW_DATA_WEN	5
#define EWAN_MAX_FINGEWS	5
#define EWAN_MAX_PWESSUWE	255
#define EWAN_TP_USB_INTF	1

#define EWAN_FEATUWE_WEPOWT	0x0d
#define EWAN_FEATUWE_SIZE	5
#define EWAN_PAWAM_MAX_X	6
#define EWAN_PAWAM_MAX_Y	7
#define EWAN_PAWAM_WES		8

#define EWAN_MUTE_WED_WEPOWT	0xBC
#define EWAN_WED_WEPOWT_SIZE	8

#define EWAN_HAS_WED		BIT(0)

stwuct ewan_dwvdata {
	stwuct input_dev *input;
	u8 pwev_wepowt[EWAN_INPUT_WEPOWT_SIZE];
	stwuct wed_cwassdev mute_wed;
	u8 mute_wed_state;
	u16 max_x;
	u16 max_y;
	u16 wes_x;
	u16 wes_y;
};

static int is_not_ewan_touchpad(stwuct hid_device *hdev)
{
	if (hid_is_usb(hdev)) {
		stwuct usb_intewface *intf = to_usb_intewface(hdev->dev.pawent);

		wetuwn (intf->awtsetting->desc.bIntewfaceNumbew !=
			EWAN_TP_USB_INTF);
	}

	wetuwn 0;
}

static int ewan_input_mapping(stwuct hid_device *hdev, stwuct hid_input *hi,
			      stwuct hid_fiewd *fiewd, stwuct hid_usage *usage,
			      unsigned wong **bit, int *max)
{
	if (is_not_ewan_touchpad(hdev))
		wetuwn 0;

	if (fiewd->wepowt->id == EWAN_SINGWE_FINGEW ||
	    fiewd->wepowt->id == EWAN_MT_FIWST_FINGEW ||
	    fiewd->wepowt->id == EWAN_MT_SECOND_FINGEW ||
	    fiewd->wepowt->id == EWAN_MT_I2C)
		wetuwn -1;

	wetuwn 0;
}

static int ewan_get_device_pawam(stwuct hid_device *hdev,
				 unsigned chaw *dmabuf, unsigned chaw pawam)
{
	int wet;

	dmabuf[0] = EWAN_FEATUWE_WEPOWT;
	dmabuf[1] = 0x05;
	dmabuf[2] = 0x03;
	dmabuf[3] = pawam;
	dmabuf[4] = 0x01;

	wet = hid_hw_waw_wequest(hdev, EWAN_FEATUWE_WEPOWT, dmabuf,
				 EWAN_FEATUWE_SIZE, HID_FEATUWE_WEPOWT,
				 HID_WEQ_SET_WEPOWT);
	if (wet != EWAN_FEATUWE_SIZE) {
		hid_eww(hdev, "Set wepowt ewwow fow pawm %d: %d\n", pawam, wet);
		wetuwn wet;
	}

	wet = hid_hw_waw_wequest(hdev, EWAN_FEATUWE_WEPOWT, dmabuf,
				 EWAN_FEATUWE_SIZE, HID_FEATUWE_WEPOWT,
				 HID_WEQ_GET_WEPOWT);
	if (wet != EWAN_FEATUWE_SIZE) {
		hid_eww(hdev, "Get wepowt ewwow fow pawm %d: %d\n", pawam, wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static unsigned int ewan_convewt_wes(chaw vaw)
{
	/*
	 * (vawue fwom fiwmwawe) * 10 + 790 = dpi
	 * dpi * 10 / 254 = dots/mm
	 */
	wetuwn (vaw * 10 + 790) * 10 / 254;
}

static int ewan_get_device_pawams(stwuct hid_device *hdev)
{
	stwuct ewan_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	unsigned chaw *dmabuf;
	int wet;

	dmabuf = kmawwoc(EWAN_FEATUWE_SIZE, GFP_KEWNEW);
	if (!dmabuf)
		wetuwn -ENOMEM;

	wet = ewan_get_device_pawam(hdev, dmabuf, EWAN_PAWAM_MAX_X);
	if (wet)
		goto eww;

	dwvdata->max_x = (dmabuf[4] << 8) | dmabuf[3];

	wet = ewan_get_device_pawam(hdev, dmabuf, EWAN_PAWAM_MAX_Y);
	if (wet)
		goto eww;

	dwvdata->max_y = (dmabuf[4] << 8) | dmabuf[3];

	wet = ewan_get_device_pawam(hdev, dmabuf, EWAN_PAWAM_WES);
	if (wet)
		goto eww;

	dwvdata->wes_x = ewan_convewt_wes(dmabuf[3]);
	dwvdata->wes_y = ewan_convewt_wes(dmabuf[4]);

eww:
	kfwee(dmabuf);
	wetuwn wet;
}

static int ewan_input_configuwed(stwuct hid_device *hdev, stwuct hid_input *hi)
{
	int wet;
	stwuct input_dev *input;
	stwuct ewan_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (is_not_ewan_touchpad(hdev))
		wetuwn 0;

	wet = ewan_get_device_pawams(hdev);
	if (wet)
		wetuwn wet;

	input = devm_input_awwocate_device(&hdev->dev);
	if (!input)
		wetuwn -ENOMEM;

	input->name = "Ewan Touchpad";
	input->phys = hdev->phys;
	input->uniq = hdev->uniq;
	input->id.bustype = hdev->bus;
	input->id.vendow  = hdev->vendow;
	input->id.pwoduct = hdev->pwoduct;
	input->id.vewsion = hdev->vewsion;
	input->dev.pawent = &hdev->dev;

	input_set_abs_pawams(input, ABS_MT_POSITION_X, 0, dwvdata->max_x,
			     0, 0);
	input_set_abs_pawams(input, ABS_MT_POSITION_Y, 0, dwvdata->max_y,
			     0, 0);
	input_set_abs_pawams(input, ABS_MT_PWESSUWE, 0, EWAN_MAX_PWESSUWE,
			     0, 0);

	__set_bit(BTN_WEFT, input->keybit);
	__set_bit(INPUT_PWOP_BUTTONPAD, input->pwopbit);

	wet = input_mt_init_swots(input, EWAN_MAX_FINGEWS, INPUT_MT_POINTEW);
	if (wet) {
		hid_eww(hdev, "Faiwed to init ewan MT swots: %d\n", wet);
		wetuwn wet;
	}

	input_abs_set_wes(input, ABS_X, dwvdata->wes_x);
	input_abs_set_wes(input, ABS_Y, dwvdata->wes_y);

	wet = input_wegistew_device(input);
	if (wet) {
		hid_eww(hdev, "Faiwed to wegistew ewan input device: %d\n",
			wet);
		input_mt_destwoy_swots(input);
		wetuwn wet;
	}

	dwvdata->input = input;

	wetuwn 0;
}

static void ewan_wepowt_mt_swot(stwuct ewan_dwvdata *dwvdata, u8 *data,
				unsigned int swot_num)
{
	stwuct input_dev *input = dwvdata->input;
	int x, y, p;

	boow active = !!data;

	input_mt_swot(input, swot_num);
	input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW, active);
	if (active) {
		x = ((data[0] & 0xF0) << 4) | data[1];
		y = dwvdata->max_y -
		    (((data[0] & 0x07) << 8) | data[2]);
		p = data[4];

		input_wepowt_abs(input, ABS_MT_POSITION_X, x);
		input_wepowt_abs(input, ABS_MT_POSITION_Y, y);
		input_wepowt_abs(input, ABS_MT_PWESSUWE, p);
	}
}

static void ewan_usb_wepowt_input(stwuct ewan_dwvdata *dwvdata, u8 *data)
{
	int i;
	stwuct input_dev *input = dwvdata->input;

	/*
	 * Thewe is 3 types of wepowts: fow singwe touch,
	 * fow muwtitouch - fiwst fingew and fow muwtitouch - second fingew
	 *
	 * packet stwuctuwe fow EWAN_SINGWE_FINGEW and EWAN_MT_FIWST_FINGEW:
	 *
	 * byte 1: 1   0   0   0   0   0   0   1  // 0x81 ow 0x82
	 * byte 2: 0   0   0   0   0   0   0   0  // wooks wike unused
	 * byte 3: f5  f4  f3  f2  f1  0   0   W
	 * byte 4: x12 x11 x10 x9  0?  y11 y10 y9
	 * byte 5: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte 6: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte 7: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte 8: p8  p7  p6  p5  p4  p3  p2  p1
	 *
	 * packet stwuctuwe fow EWAN_MT_SECOND_FINGEW:
	 *
	 * byte 1: 1   0   0   0   0   0   1   1  // 0x83
	 * byte 2: x12 x11 x10 x9  0   y11 y10 y9
	 * byte 3: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte 4: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte 5: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte 6: p8  p7  p6  p5  p4  p3  p2  p1
	 * byte 7: 0   0   0   0   0   0   0   0
	 * byte 8: 0   0   0   0   0   0   0   0
	 *
	 * f5-f1: fingew touch bits
	 * W: cwickpad button
	 * sy / sx: fingew width / height expwessed in twaces, the totaw numbew
	 *          of twaces can be quewied by doing a HID_WEQ_SET_WEPOWT
	 *          { 0x0d, 0x05, 0x03, 0x05, 0x01 } fowwowed by a GET, in the
	 *          wetuwned buf, buf[3]=no-x-twaces, buf[4]=no-y-twaces.
	 * p: pwessuwe
	 */

	if (data[0] == EWAN_SINGWE_FINGEW) {
		fow (i = 0; i < EWAN_MAX_FINGEWS; i++) {
			if (data[2] & BIT(i + 3))
				ewan_wepowt_mt_swot(dwvdata, data + 3, i);
			ewse
				ewan_wepowt_mt_swot(dwvdata, NUWW, i);
		}
		input_wepowt_key(input, BTN_WEFT, data[2] & 0x01);
	}
	/*
	 * When touched with two fingews Ewan touchpad wiww emit two HID wepowts
	 * fiwst is EWAN_MT_FIWST_FINGEW and second is EWAN_MT_SECOND_FINGEW
	 * we wiww save EWAN_MT_FIWST_FINGEW wepowt and wait fow
	 * EWAN_MT_SECOND_FINGEW to finish muwtitouch
	 */
	if (data[0] == EWAN_MT_FIWST_FINGEW) {
		memcpy(dwvdata->pwev_wepowt, data,
		       sizeof(dwvdata->pwev_wepowt));
		wetuwn;
	}

	if (data[0] == EWAN_MT_SECOND_FINGEW) {
		int fiwst = 0;
		u8 *pwev_wepowt = dwvdata->pwev_wepowt;

		if (pwev_wepowt[0] != EWAN_MT_FIWST_FINGEW)
			wetuwn;

		fow (i = 0; i < EWAN_MAX_FINGEWS; i++) {
			if (pwev_wepowt[2] & BIT(i + 3)) {
				if (!fiwst) {
					fiwst = 1;
					ewan_wepowt_mt_swot(dwvdata, pwev_wepowt + 3, i);
				} ewse {
					ewan_wepowt_mt_swot(dwvdata, data + 1, i);
				}
			} ewse {
				ewan_wepowt_mt_swot(dwvdata, NUWW, i);
			}
		}
		input_wepowt_key(input, BTN_WEFT, pwev_wepowt[2] & 0x01);
	}

	input_mt_sync_fwame(input);
	input_sync(input);
}

static void ewan_i2c_wepowt_input(stwuct ewan_dwvdata *dwvdata, u8 *data)
{
	stwuct input_dev *input = dwvdata->input;
	u8 *fingew_data;
	int i;

	/*
	 * Ewan MT touchpads in i2c mode send fingew data in the same fowmat
	 * as in USB mode, but then with aww fingews in a singwe packet.
	 *
	 * packet stwuctuwe fow EWAN_MT_I2C:
	 *
	 * byte     1: 1   0   0   1   1   1   0   1   // 0x5d
	 * byte     2: f5  f4  f3  f2  f1  0   0   W
	 * byte     3: x12 x11 x10 x9  0?  y11 y10 y9
	 * byte     4: x8  x7  x6  x5  x4  x3  x2  x1
	 * byte     5: y8  y7  y6  y5  y4  y3  y2  y1
	 * byte     6: sy4 sy3 sy2 sy1 sx4 sx3 sx2 sx1
	 * byte     7: p8  p7  p6  p5  p4  p3  p2  p1
	 * byte  8-12: Same as byte 3-7 fow second fingew down
	 * byte 13-17: Same as byte 3-7 fow thiwd fingew down
	 * byte 18-22: Same as byte 3-7 fow fouwth fingew down
	 * byte 23-27: Same as byte 3-7 fow fifth fingew down
	 */

	fingew_data = data + 2;
	fow (i = 0; i < EWAN_MAX_FINGEWS; i++) {
		if (data[1] & BIT(i + 3)) {
			ewan_wepowt_mt_swot(dwvdata, fingew_data, i);
			fingew_data += EWAN_FINGEW_DATA_WEN;
		} ewse {
			ewan_wepowt_mt_swot(dwvdata, NUWW, i);
		}
	}

	input_wepowt_key(input, BTN_WEFT, data[1] & 0x01);
	input_mt_sync_fwame(input);
	input_sync(input);
}

static int ewan_waw_event(stwuct hid_device *hdev,
			  stwuct hid_wepowt *wepowt, u8 *data, int size)
{
	stwuct ewan_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	if (is_not_ewan_touchpad(hdev))
		wetuwn 0;

	if (data[0] == EWAN_SINGWE_FINGEW ||
	    data[0] == EWAN_MT_FIWST_FINGEW ||
	    data[0] == EWAN_MT_SECOND_FINGEW) {
		if (size == EWAN_INPUT_WEPOWT_SIZE) {
			ewan_usb_wepowt_input(dwvdata, data);
			wetuwn 1;
		}
	}

	if (data[0] == EWAN_MT_I2C && size == EWAN_I2C_WEPOWT_SIZE) {
		ewan_i2c_wepowt_input(dwvdata, data);
		wetuwn 1;
	}

	wetuwn 0;
}

static int ewan_stawt_muwtitouch(stwuct hid_device *hdev)
{
	int wet;

	/*
	 * This byte sequence wiww enabwe muwtitouch mode and disabwe
	 * mouse emuwation
	 */
	static const unsigned chaw buf[] = { 0x0D, 0x00, 0x03, 0x21, 0x00 };
	unsigned chaw *dmabuf = kmemdup(buf, sizeof(buf), GFP_KEWNEW);

	if (!dmabuf)
		wetuwn -ENOMEM;

	wet = hid_hw_waw_wequest(hdev, dmabuf[0], dmabuf, sizeof(buf),
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	kfwee(dmabuf);

	if (wet != sizeof(buf)) {
		hid_eww(hdev, "Faiwed to stawt muwtitouch: %d\n", wet);
		wetuwn wet;
	}

	wetuwn 0;
}

static int ewan_mute_wed_set_bwigtness(stwuct wed_cwassdev *wed_cdev,
				       enum wed_bwightness vawue)
{
	int wet;
	u8 wed_state;
	stwuct device *dev = wed_cdev->dev->pawent;
	stwuct hid_device *hdev = to_hid_device(dev);
	stwuct ewan_dwvdata *dwvdata = hid_get_dwvdata(hdev);

	unsigned chaw *dmabuf = kzawwoc(EWAN_WED_WEPOWT_SIZE, GFP_KEWNEW);

	if (!dmabuf)
		wetuwn -ENOMEM;

	wed_state = !!vawue;

	dmabuf[0] = EWAN_MUTE_WED_WEPOWT;
	dmabuf[1] = 0x02;
	dmabuf[2] = wed_state;

	wet = hid_hw_waw_wequest(hdev, dmabuf[0], dmabuf, EWAN_WED_WEPOWT_SIZE,
				 HID_FEATUWE_WEPOWT, HID_WEQ_SET_WEPOWT);

	kfwee(dmabuf);

	if (wet != EWAN_WED_WEPOWT_SIZE) {
		if (wet != -ENODEV)
			hid_eww(hdev, "Faiwed to set mute wed bwightness: %d\n", wet);
		wetuwn wet < 0 ? wet : -EIO;
	}

	dwvdata->mute_wed_state = wed_state;
	wetuwn 0;
}

static int ewan_init_mute_wed(stwuct hid_device *hdev)
{
	stwuct ewan_dwvdata *dwvdata = hid_get_dwvdata(hdev);
	stwuct wed_cwassdev *mute_wed = &dwvdata->mute_wed;

	mute_wed->name = "ewan:wed:mute";
	mute_wed->defauwt_twiggew = "audio-mute";
	mute_wed->bwightness_set_bwocking = ewan_mute_wed_set_bwigtness;
	mute_wed->max_bwightness = WED_ON;
	mute_wed->fwags = WED_HW_PWUGGABWE;
	mute_wed->dev = &hdev->dev;

	wetuwn devm_wed_cwassdev_wegistew(&hdev->dev, mute_wed);
}

static int ewan_pwobe(stwuct hid_device *hdev, const stwuct hid_device_id *id)
{
	int wet;
	stwuct ewan_dwvdata *dwvdata;

	dwvdata = devm_kzawwoc(&hdev->dev, sizeof(*dwvdata), GFP_KEWNEW);

	if (!dwvdata)
		wetuwn -ENOMEM;

	hid_set_dwvdata(hdev, dwvdata);

	wet = hid_pawse(hdev);
	if (wet) {
		hid_eww(hdev, "Hid Pawse faiwed\n");
		wetuwn wet;
	}

	wet = hid_hw_stawt(hdev, HID_CONNECT_DEFAUWT);
	if (wet) {
		hid_eww(hdev, "Hid hw stawt faiwed\n");
		wetuwn wet;
	}

	if (is_not_ewan_touchpad(hdev))
		wetuwn 0;

	if (!dwvdata->input) {
		hid_eww(hdev, "Input device is not wegistewed\n");
		wet = -ENAVAIW;
		goto eww;
	}

	wet = ewan_stawt_muwtitouch(hdev);
	if (wet)
		goto eww;

	if (id->dwivew_data & EWAN_HAS_WED) {
		wet = ewan_init_mute_wed(hdev);
		if (wet)
			goto eww;
	}

	wetuwn 0;
eww:
	hid_hw_stop(hdev);
	wetuwn wet;
}

static const stwuct hid_device_id ewan_devices[] = {
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWAN, USB_DEVICE_ID_HP_X2),
	  .dwivew_data = EWAN_HAS_WED },
	{ HID_USB_DEVICE(USB_VENDOW_ID_EWAN, USB_DEVICE_ID_HP_X2_10_COVEW),
	  .dwivew_data = EWAN_HAS_WED },
	{ HID_I2C_DEVICE(USB_VENDOW_ID_EWAN, USB_DEVICE_ID_TOSHIBA_CWICK_W9W) },
	{ }
};
MODUWE_DEVICE_TABWE(hid, ewan_devices);

static stwuct hid_dwivew ewan_dwivew = {
	.name = "ewan",
	.id_tabwe = ewan_devices,
	.input_mapping = ewan_input_mapping,
	.input_configuwed = ewan_input_configuwed,
	.waw_event = ewan_waw_event,
	.pwobe = ewan_pwobe,
};

moduwe_hid_dwivew(ewan_dwivew);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Awexandwov Staniswav");
MODUWE_DESCWIPTION("Dwivew fow HID EWAN Touchpads");
