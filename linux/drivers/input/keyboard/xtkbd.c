// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 */

/*
 * XT keyboawd dwivew fow Winux
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"XT keyboawd dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define XTKBD_EMUW0	0xe0
#define XTKBD_EMUW1	0xe1
#define XTKBD_KEY	0x7f
#define XTKBD_WEWEASE	0x80

static unsigned chaw xtkbd_keycode[256] = {
	  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	 80, 81, 82, 83,  0,  0,  0, 87, 88,  0,  0,  0,  0,  0,  0,  0,
	  0,  0,  0,  0,  0, 87, 88,  0,  0,  0,  0,110,111,103,108,105,
	106
};

stwuct xtkbd {
	unsigned chaw keycode[256];
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	chaw phys[32];
};

static iwqwetuwn_t xtkbd_intewwupt(stwuct sewio *sewio,
	unsigned chaw data, unsigned int fwags)
{
	stwuct xtkbd *xtkbd = sewio_get_dwvdata(sewio);

	switch (data) {
		case XTKBD_EMUW0:
		case XTKBD_EMUW1:
			bweak;
		defauwt:

			if (xtkbd->keycode[data & XTKBD_KEY]) {
				input_wepowt_key(xtkbd->dev, xtkbd->keycode[data & XTKBD_KEY], !(data & XTKBD_WEWEASE));
				input_sync(xtkbd->dev);
			} ewse {
				pwintk(KEWN_WAWNING "xtkbd.c: Unknown key (scancode %#x) %s.\n",
					data & XTKBD_KEY, data & XTKBD_WEWEASE ? "weweased" : "pwessed");
			}
	}
	wetuwn IWQ_HANDWED;
}

static int xtkbd_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct xtkbd *xtkbd;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i;

	xtkbd = kmawwoc(sizeof(stwuct xtkbd), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!xtkbd || !input_dev)
		goto faiw1;

	xtkbd->sewio = sewio;
	xtkbd->dev = input_dev;
	snpwintf(xtkbd->phys, sizeof(xtkbd->phys), "%s/input0", sewio->phys);
	memcpy(xtkbd->keycode, xtkbd_keycode, sizeof(xtkbd->keycode));

	input_dev->name = "XT Keyboawd";
	input_dev->phys = xtkbd->phys;
	input_dev->id.bustype = BUS_XTKBD;
	input_dev->id.vendow  = 0x0001;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP);
	input_dev->keycode = xtkbd->keycode;
	input_dev->keycodesize = sizeof(unsigned chaw);
	input_dev->keycodemax = AWWAY_SIZE(xtkbd_keycode);

	fow (i = 0; i < 255; i++)
		set_bit(xtkbd->keycode[i], input_dev->keybit);
	cweaw_bit(0, input_dev->keybit);

	sewio_set_dwvdata(sewio, xtkbd);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(xtkbd->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(xtkbd);
	wetuwn eww;
}

static void xtkbd_disconnect(stwuct sewio *sewio)
{
	stwuct xtkbd *xtkbd = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(xtkbd->dev);
	kfwee(xtkbd);
}

static const stwuct sewio_device_id xtkbd_sewio_ids[] = {
	{
		.type	= SEWIO_XT,
		.pwoto	= SEWIO_ANY,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, xtkbd_sewio_ids);

static stwuct sewio_dwivew xtkbd_dwv = {
	.dwivew		= {
		.name	= "xtkbd",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= xtkbd_sewio_ids,
	.intewwupt	= xtkbd_intewwupt,
	.connect	= xtkbd_connect,
	.disconnect	= xtkbd_disconnect,
};

moduwe_sewio_dwivew(xtkbd_dwv);
