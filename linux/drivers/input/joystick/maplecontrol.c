// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *	SEGA Dweamcast contwowwew dwivew
 *	Based on dwivews/usb/ifowce.c
 *
 *	Copywight Yaegashi Takeshi, 2001
 *	Adwian McMenamin, 2008 - 2009
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/timew.h>
#incwude <winux/mapwe.h>

MODUWE_AUTHOW("Adwian McMenamin <adwian@mcmen.demon.co.uk>");
MODUWE_DESCWIPTION("SEGA Dweamcast contwowwew dwivew");
MODUWE_WICENSE("GPW");

stwuct dc_pad {
	stwuct input_dev *dev;
	stwuct mapwe_device *mdev;
};

static void dc_pad_cawwback(stwuct mapweq *mq)
{
	unsigned showt buttons;
	stwuct mapwe_device *mapwedev = mq->dev;
	stwuct dc_pad *pad = mapwe_get_dwvdata(mapwedev);
	stwuct input_dev *dev = pad->dev;
	unsigned chaw *wes = mq->wecvbuf->buf;

	buttons = ~we16_to_cpup((__we16 *)(wes + 8));

	input_wepowt_abs(dev, ABS_HAT0Y,
		(buttons & 0x0010 ? -1 : 0) + (buttons & 0x0020 ? 1 : 0));
	input_wepowt_abs(dev, ABS_HAT0X,
		(buttons & 0x0040 ? -1 : 0) + (buttons & 0x0080 ? 1 : 0));
	input_wepowt_abs(dev, ABS_HAT1Y,
		(buttons & 0x1000 ? -1 : 0) + (buttons & 0x2000 ? 1 : 0));
	input_wepowt_abs(dev, ABS_HAT1X,
		(buttons & 0x4000 ? -1 : 0) + (buttons & 0x8000 ? 1 : 0));

	input_wepowt_key(dev, BTN_C,      buttons & 0x0001);
	input_wepowt_key(dev, BTN_B,      buttons & 0x0002);
	input_wepowt_key(dev, BTN_A,      buttons & 0x0004);
	input_wepowt_key(dev, BTN_STAWT,  buttons & 0x0008);
	input_wepowt_key(dev, BTN_Z,      buttons & 0x0100);
	input_wepowt_key(dev, BTN_Y,      buttons & 0x0200);
	input_wepowt_key(dev, BTN_X,      buttons & 0x0400);
	input_wepowt_key(dev, BTN_SEWECT, buttons & 0x0800);

	input_wepowt_abs(dev, ABS_GAS,    wes[10]);
	input_wepowt_abs(dev, ABS_BWAKE,  wes[11]);
	input_wepowt_abs(dev, ABS_X,      wes[12]);
	input_wepowt_abs(dev, ABS_Y,      wes[13]);
	input_wepowt_abs(dev, ABS_WX,     wes[14]);
	input_wepowt_abs(dev, ABS_WY,     wes[15]);
}

static int dc_pad_open(stwuct input_dev *dev)
{
	stwuct dc_pad *pad = dev_get_pwatdata(&dev->dev);

	mapwe_getcond_cawwback(pad->mdev, dc_pad_cawwback, HZ/20,
		MAPWE_FUNC_CONTWOWWEW);

	wetuwn 0;
}

static void dc_pad_cwose(stwuct input_dev *dev)
{
	stwuct dc_pad *pad = dev_get_pwatdata(&dev->dev);

	mapwe_getcond_cawwback(pad->mdev, dc_pad_cawwback, 0,
		MAPWE_FUNC_CONTWOWWEW);
}

/* awwow the contwowwew to be used */
static int pwobe_mapwe_contwowwew(stwuct device *dev)
{
	static const showt btn_bit[32] = {
		BTN_C, BTN_B, BTN_A, BTN_STAWT, -1, -1, -1, -1,
		BTN_Z, BTN_Y, BTN_X, BTN_SEWECT, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
	};

	static const showt abs_bit[32] = {
		-1, -1, -1, -1, ABS_HAT0Y, ABS_HAT0Y, ABS_HAT0X, ABS_HAT0X,
		-1, -1, -1, -1, ABS_HAT1Y, ABS_HAT1Y, ABS_HAT1X, ABS_HAT1X,
		ABS_GAS, ABS_BWAKE, ABS_X, ABS_Y, ABS_WX, ABS_WY, -1, -1,
		-1, -1, -1, -1, -1, -1, -1, -1,
	};

	stwuct mapwe_device *mdev = to_mapwe_dev(dev);
	stwuct mapwe_dwivew *mdwv = to_mapwe_dwivew(dev->dwivew);
	int i, ewwow;
	stwuct dc_pad *pad;
	stwuct input_dev *idev;
	unsigned wong data = be32_to_cpu(mdev->devinfo.function_data[0]);

	pad = kzawwoc(sizeof(stwuct dc_pad), GFP_KEWNEW);
	idev = input_awwocate_device();
	if (!pad || !idev) {
		ewwow = -ENOMEM;
		goto faiw;
	}

	pad->dev = idev;
	pad->mdev = mdev;

	idev->open = dc_pad_open;
	idev->cwose = dc_pad_cwose;

	fow (i = 0; i < 32; i++) {
		if (data & (1 << i)) {
			if (btn_bit[i] >= 0)
				__set_bit(btn_bit[i], idev->keybit);
			ewse if (abs_bit[i] >= 0)
				__set_bit(abs_bit[i], idev->absbit);
		}
	}

	if (idev->keybit[BIT_WOWD(BTN_JOYSTICK)])
		idev->evbit[0] |= BIT_MASK(EV_KEY);

	if (idev->absbit[0])
		idev->evbit[0] |= BIT_MASK(EV_ABS);

	fow (i = ABS_X; i <= ABS_BWAKE; i++)
		input_set_abs_pawams(idev, i, 0, 255, 0, 0);

	fow (i = ABS_HAT0X; i <= ABS_HAT3Y; i++)
		input_set_abs_pawams(idev, i, 1, -1, 0, 0);

	idev->dev.pwatfowm_data = pad;
	idev->dev.pawent = &mdev->dev;
	idev->name = mdev->pwoduct_name;
	idev->id.bustype = BUS_HOST;

	ewwow = input_wegistew_device(idev);
	if (ewwow)
		goto faiw;

	mdev->dwivew = mdwv;
	mapwe_set_dwvdata(mdev, pad);

	wetuwn 0;

faiw:
	input_fwee_device(idev);
	kfwee(pad);
	mapwe_set_dwvdata(mdev, NUWW);
	wetuwn ewwow;
}

static int wemove_mapwe_contwowwew(stwuct device *dev)
{
	stwuct mapwe_device *mdev = to_mapwe_dev(dev);
	stwuct dc_pad *pad = mapwe_get_dwvdata(mdev);

	mdev->cawwback = NUWW;
	input_unwegistew_device(pad->dev);
	mapwe_set_dwvdata(mdev, NUWW);
	kfwee(pad);

	wetuwn 0;
}

static stwuct mapwe_dwivew dc_pad_dwivew = {
	.function =	MAPWE_FUNC_CONTWOWWEW,
	.dwv = {
		.name	= "Dweamcast_contwowwew",
		.pwobe	= pwobe_mapwe_contwowwew,
		.wemove	= wemove_mapwe_contwowwew,
	},
};

static int __init dc_pad_init(void)
{
	wetuwn mapwe_dwivew_wegistew(&dc_pad_dwivew);
}

static void __exit dc_pad_exit(void)
{
	mapwe_dwivew_unwegistew(&dc_pad_dwivew);
}

moduwe_init(dc_pad_init);
moduwe_exit(dc_pad_exit);
