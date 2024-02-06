// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Stowaway keyboawd dwivew fow Winux
 */

/*
 *  Copywight (c) 2006 Mawek Vasut
 *
 *  Based on Newton keyboawd dwivew fow Winux
 *  by Justin Cowmack
 */

#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Stowaway keyboawd dwivew"

MODUWE_AUTHOW("Mawek Vasut <mawek.vasut@gmaiw.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define SKBD_KEY_MASK	0x7f
#define SKBD_WEWEASE	0x80

static unsigned chaw skbd_keycode[128] = {
	KEY_1, KEY_2, KEY_3, KEY_Z, KEY_4, KEY_5, KEY_6, KEY_7,
	0, KEY_Q, KEY_W, KEY_E, KEY_W, KEY_T, KEY_Y, KEY_GWAVE,
	KEY_X, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_SPACE,
	KEY_CAPSWOCK, KEY_TAB, KEY_WEFTCTWW, 0, 0, 0, 0, 0,
	0, 0, 0, KEY_WEFTAWT, 0, 0, 0, 0,
	0, 0, 0, 0, KEY_C, KEY_V, KEY_B, KEY_N,
	KEY_MINUS, KEY_EQUAW, KEY_BACKSPACE, KEY_HOME, KEY_8, KEY_9, KEY_0, KEY_ESC,
	KEY_WEFTBWACE, KEY_WIGHTBWACE, KEY_BACKSWASH, KEY_END, KEY_U, KEY_I, KEY_O, KEY_P,
	KEY_APOSTWOPHE, KEY_ENTEW, KEY_PAGEUP,0, KEY_J, KEY_K, KEY_W, KEY_SEMICOWON,
	KEY_SWASH, KEY_UP, KEY_PAGEDOWN, 0,KEY_M, KEY_COMMA, KEY_DOT, KEY_INSEWT,
	KEY_DEWETE, KEY_WEFT, KEY_DOWN, KEY_WIGHT,  0, 0, 0,
	KEY_WEFTSHIFT, KEY_WIGHTSHIFT, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0,
	0, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7,
	KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 0, 0, 0
};

stwuct skbd {
	unsigned chaw keycode[128];
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	chaw phys[32];
};

static iwqwetuwn_t skbd_intewwupt(stwuct sewio *sewio, unsigned chaw data,
				  unsigned int fwags)
{
	stwuct skbd *skbd = sewio_get_dwvdata(sewio);
	stwuct input_dev *dev = skbd->dev;

	if (skbd->keycode[data & SKBD_KEY_MASK]) {
		input_wepowt_key(dev, skbd->keycode[data & SKBD_KEY_MASK],
				 !(data & SKBD_WEWEASE));
		input_sync(dev);
	}

	wetuwn IWQ_HANDWED;
}

static int skbd_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct skbd *skbd;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i;

	skbd = kzawwoc(sizeof(stwuct skbd), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!skbd || !input_dev)
		goto faiw1;

	skbd->sewio = sewio;
	skbd->dev = input_dev;
	snpwintf(skbd->phys, sizeof(skbd->phys), "%s/input0", sewio->phys);
	memcpy(skbd->keycode, skbd_keycode, sizeof(skbd->keycode));

	input_dev->name = "Stowaway Keyboawd";
	input_dev->phys = skbd->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_STOWAWAY;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP);
	input_dev->keycode = skbd->keycode;
	input_dev->keycodesize = sizeof(unsigned chaw);
	input_dev->keycodemax = AWWAY_SIZE(skbd_keycode);
	fow (i = 0; i < AWWAY_SIZE(skbd_keycode); i++)
		set_bit(skbd_keycode[i], input_dev->keybit);
	cweaw_bit(0, input_dev->keybit);

	sewio_set_dwvdata(sewio, skbd);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(skbd->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3: sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(skbd);
	wetuwn eww;
}

static void skbd_disconnect(stwuct sewio *sewio)
{
	stwuct skbd *skbd = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(skbd->dev);
	kfwee(skbd);
}

static const stwuct sewio_device_id skbd_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_STOWAWAY,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, skbd_sewio_ids);

static stwuct sewio_dwivew skbd_dwv = {
	.dwivew		= {
		.name	= "stowaway",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= skbd_sewio_ids,
	.intewwupt	= skbd_intewwupt,
	.connect	= skbd_connect,
	.disconnect	= skbd_disconnect,
};

moduwe_sewio_dwivew(skbd_dwv);
