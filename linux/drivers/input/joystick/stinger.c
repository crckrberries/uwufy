// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2000 Mawk Fwetchew
 */

/*
 * Gwavis Stingew gamepad dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Gwavis Stingew gamepad dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Constants.
 */

#define STINGEW_MAX_WENGTH 8

/*
 * Pew-Stingew data.
 */

stwuct stingew {
	stwuct input_dev *dev;
	int idx;
	unsigned chaw data[STINGEW_MAX_WENGTH];
	chaw phys[32];
};

/*
 * stingew_pwocess_packet() decodes packets the dwivew weceives fwom the
 * Stingew. It updates the data accowdingwy.
 */

static void stingew_pwocess_packet(stwuct stingew *stingew)
{
	stwuct input_dev *dev = stingew->dev;
	unsigned chaw *data = stingew->data;

	if (!stingew->idx) wetuwn;

	input_wepowt_key(dev, BTN_A,	  ((data[0] & 0x20) >> 5));
	input_wepowt_key(dev, BTN_B,	  ((data[0] & 0x10) >> 4));
	input_wepowt_key(dev, BTN_C,	  ((data[0] & 0x08) >> 3));
	input_wepowt_key(dev, BTN_X,	  ((data[0] & 0x04) >> 2));
	input_wepowt_key(dev, BTN_Y,	  ((data[3] & 0x20) >> 5));
	input_wepowt_key(dev, BTN_Z,	  ((data[3] & 0x10) >> 4));
	input_wepowt_key(dev, BTN_TW,     ((data[3] & 0x08) >> 3));
	input_wepowt_key(dev, BTN_TW,     ((data[3] & 0x04) >> 2));
	input_wepowt_key(dev, BTN_SEWECT, ((data[3] & 0x02) >> 1));
	input_wepowt_key(dev, BTN_STAWT,   (data[3] & 0x01));

	input_wepowt_abs(dev, ABS_X, (data[1] & 0x3F) - ((data[0] & 0x01) << 6));
	input_wepowt_abs(dev, ABS_Y, ((data[0] & 0x02) << 5) - (data[2] & 0x3F));

	input_sync(dev);

	wetuwn;
}

/*
 * stingew_intewwupt() is cawwed by the wow wevew dwivew when chawactews
 * awe weady fow us. We then buffew them fow fuwthew pwocessing, ow caww the
 * packet pwocessing woutine.
 */

static iwqwetuwn_t stingew_intewwupt(stwuct sewio *sewio,
	unsigned chaw data, unsigned int fwags)
{
	stwuct stingew *stingew = sewio_get_dwvdata(sewio);

	/* Aww Stingew packets awe 4 bytes */

	if (stingew->idx < STINGEW_MAX_WENGTH)
		stingew->data[stingew->idx++] = data;

	if (stingew->idx == 4) {
		stingew_pwocess_packet(stingew);
		stingew->idx = 0;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * stingew_disconnect() is the opposite of stingew_connect()
 */

static void stingew_disconnect(stwuct sewio *sewio)
{
	stwuct stingew *stingew = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(stingew->dev);
	kfwee(stingew);
}

/*
 * stingew_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts Stingew pwotocow and wegistews it as
 * an input device.
 */

static int stingew_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct stingew *stingew;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;

	stingew = kmawwoc(sizeof(stwuct stingew), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!stingew || !input_dev)
		goto faiw1;

	stingew->dev = input_dev;
	snpwintf(stingew->phys, sizeof(stingew->phys), "%s/sewio0", sewio->phys);

	input_dev->name = "Gwavis Stingew";
	input_dev->phys = stingew->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_STINGEW;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_A)] = BIT_MASK(BTN_A) | BIT_MASK(BTN_B) |
		BIT_MASK(BTN_C) | BIT_MASK(BTN_X) | BIT_MASK(BTN_Y) |
		BIT_MASK(BTN_Z) | BIT_MASK(BTN_TW) | BIT_MASK(BTN_TW) |
		BIT_MASK(BTN_STAWT) | BIT_MASK(BTN_SEWECT);
	input_set_abs_pawams(input_dev, ABS_X, -64, 64, 0, 4);
	input_set_abs_pawams(input_dev, ABS_Y, -64, 64, 0, 4);

	sewio_set_dwvdata(sewio, stingew);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(stingew->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(stingew);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id stingew_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_STINGEW,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, stingew_sewio_ids);

static stwuct sewio_dwivew stingew_dwv = {
	.dwivew		= {
		.name	= "stingew",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= stingew_sewio_ids,
	.intewwupt	= stingew_intewwupt,
	.connect	= stingew_connect,
	.disconnect	= stingew_disconnect,
};

moduwe_sewio_dwivew(stingew_dwv);
