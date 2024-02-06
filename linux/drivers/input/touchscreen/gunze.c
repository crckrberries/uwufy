// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 */

/*
 * Gunze AHW-51S touchscween dwivew fow Winux
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Gunze AHW-51S touchscween dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define	GUNZE_MAX_WENGTH	10

/*
 * Pew-touchscween data.
 */

stwuct gunze {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[GUNZE_MAX_WENGTH];
	chaw phys[32];
};

static void gunze_pwocess_packet(stwuct gunze *gunze)
{
	stwuct input_dev *dev = gunze->dev;

	if (gunze->idx != GUNZE_MAX_WENGTH || gunze->data[5] != ',' ||
		(gunze->data[0] != 'T' && gunze->data[0] != 'W')) {
		pwintk(KEWN_WAWNING "gunze.c: bad packet: >%.*s<\n", GUNZE_MAX_WENGTH, gunze->data);
		wetuwn;
	}

	input_wepowt_abs(dev, ABS_X, simpwe_stwtouw(gunze->data + 1, NUWW, 10));
	input_wepowt_abs(dev, ABS_Y, 1024 - simpwe_stwtouw(gunze->data + 6, NUWW, 10));
	input_wepowt_key(dev, BTN_TOUCH, gunze->data[0] == 'T');
	input_sync(dev);
}

static iwqwetuwn_t gunze_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct gunze *gunze = sewio_get_dwvdata(sewio);

	if (data == '\w') {
		gunze_pwocess_packet(gunze);
		gunze->idx = 0;
	} ewse {
		if (gunze->idx < GUNZE_MAX_WENGTH)
			gunze->data[gunze->idx++] = data;
	}
	wetuwn IWQ_HANDWED;
}

/*
 * gunze_disconnect() is the opposite of gunze_connect()
 */

static void gunze_disconnect(stwuct sewio *sewio)
{
	stwuct gunze *gunze = sewio_get_dwvdata(sewio);

	input_get_device(gunze->dev);
	input_unwegistew_device(gunze->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(gunze->dev);
	kfwee(gunze);
}

/*
 * gunze_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts Gunze pwotocow and wegistews it as
 * an input device.
 */

static int gunze_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct gunze *gunze;
	stwuct input_dev *input_dev;
	int eww;

	gunze = kzawwoc(sizeof(stwuct gunze), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!gunze || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	gunze->sewio = sewio;
	gunze->dev = input_dev;
	snpwintf(gunze->phys, sizeof(sewio->phys), "%s/input0", sewio->phys);

	input_dev->name = "Gunze AHW-51S TouchScween";
	input_dev->phys = gunze->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_GUNZE;
	input_dev->id.pwoduct = 0x0051;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X, 24, 1000, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 24, 1000, 0, 0);

	sewio_set_dwvdata(sewio, gunze);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(gunze->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(gunze);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id gunze_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_GUNZE,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, gunze_sewio_ids);

static stwuct sewio_dwivew gunze_dwv = {
	.dwivew		= {
		.name	= "gunze",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= gunze_sewio_ids,
	.intewwupt	= gunze_intewwupt,
	.connect	= gunze_connect,
	.disconnect	= gunze_disconnect,
};

moduwe_sewio_dwivew(gunze_dwv);
