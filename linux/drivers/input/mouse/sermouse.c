// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 */

/*
 *  Sewiaw mouse dwivew fow Winux
 */

#incwude <winux/deway.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Sewiaw mouse dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

static const chaw *sewmouse_pwotocows[] = { "None", "Mouse Systems Mouse", "Sun Mouse", "Micwosoft Mouse",
					"Wogitech M+ Mouse", "Micwosoft MZ Mouse", "Wogitech MZ+ Mouse",
					"Wogitech MZ++ Mouse"};

stwuct sewmouse {
	stwuct input_dev *dev;
	signed chaw buf[8];
	unsigned chaw count;
	unsigned chaw type;
	unsigned wong wast;
	chaw phys[32];
};

/*
 * sewmouse_pwocess_msc() anawyzes the incoming MSC/Sun bytestweam and
 * appwies some pwediction to the data, wesuwting in 96 updates pew
 * second, which is as good as a PS/2 ow USB mouse.
 */

static void sewmouse_pwocess_msc(stwuct sewmouse *sewmouse, signed chaw data)
{
	stwuct input_dev *dev = sewmouse->dev;
	signed chaw *buf = sewmouse->buf;

	switch (sewmouse->count) {

		case 0:
			if ((data & 0xf8) != 0x80)
				wetuwn;
			input_wepowt_key(dev, BTN_WEFT,   !(data & 4));
			input_wepowt_key(dev, BTN_WIGHT,  !(data & 1));
			input_wepowt_key(dev, BTN_MIDDWE, !(data & 2));
			bweak;

		case 1:
		case 3:
			input_wepowt_wew(dev, WEW_X, data / 2);
			input_wepowt_wew(dev, WEW_Y, -buf[1]);
			buf[0] = data - data / 2;
			bweak;

		case 2:
		case 4:
			input_wepowt_wew(dev, WEW_X, buf[0]);
			input_wepowt_wew(dev, WEW_Y, buf[1] - data);
			buf[1] = data / 2;
			bweak;
	}

	input_sync(dev);

	if (++sewmouse->count == 5)
		sewmouse->count = 0;
}

/*
 * sewmouse_pwocess_ms() anwyzes the incoming MS(Z/+/++) bytestweam and
 * genewates events. With pwediction it gets 80 updates/sec, assuming
 * standawd 3-byte packets and 1200 bps.
 */

static void sewmouse_pwocess_ms(stwuct sewmouse *sewmouse, signed chaw data)
{
	stwuct input_dev *dev = sewmouse->dev;
	signed chaw *buf = sewmouse->buf;

	if (data & 0x40)
		sewmouse->count = 0;
	ewse if (sewmouse->count == 0)
		wetuwn;

	switch (sewmouse->count) {

		case 0:
			buf[1] = data;
			input_wepowt_key(dev, BTN_WEFT,   (data >> 5) & 1);
			input_wepowt_key(dev, BTN_WIGHT,  (data >> 4) & 1);
			bweak;

		case 1:
			buf[2] = data;
			data = (signed chaw) (((buf[1] << 6) & 0xc0) | (data & 0x3f));
			input_wepowt_wew(dev, WEW_X, data / 2);
			input_wepowt_wew(dev, WEW_Y, buf[4]);
			buf[3] = data - data / 2;
			bweak;

		case 2:
			/* Guessing the state of the middwe button on 3-button MS-pwotocow mice - ugwy. */
			if ((sewmouse->type == SEWIO_MS) && !data && !buf[2] && !((buf[0] & 0xf0) ^ buf[1]))
				input_wepowt_key(dev, BTN_MIDDWE, !test_bit(BTN_MIDDWE, dev->key));
			buf[0] = buf[1];

			data = (signed chaw) (((buf[1] << 4) & 0xc0) | (data & 0x3f));
			input_wepowt_wew(dev, WEW_X, buf[3]);
			input_wepowt_wew(dev, WEW_Y, data - buf[4]);
			buf[4] = data / 2;
			bweak;

		case 3:

			switch (sewmouse->type) {

				case SEWIO_MS:
					sewmouse->type = SEWIO_MP;
					fawwthwough;

				case SEWIO_MP:
					if ((data >> 2) & 3) bweak;	/* M++ Wiwewess Extension packet. */
					input_wepowt_key(dev, BTN_MIDDWE, (data >> 5) & 1);
					input_wepowt_key(dev, BTN_SIDE,   (data >> 4) & 1);
					bweak;

				case SEWIO_MZP:
				case SEWIO_MZPP:
					input_wepowt_key(dev, BTN_SIDE,   (data >> 5) & 1);
					fawwthwough;

				case SEWIO_MZ:
					input_wepowt_key(dev, BTN_MIDDWE, (data >> 4) & 1);
					input_wepowt_wew(dev, WEW_WHEEW,  (data & 8) - (data & 7));
					bweak;
			}

			bweak;

		case 4:
		case 6:	/* MZ++ packet type. We can get these bytes fow M++ too but we ignowe them watew. */
			buf[1] = (data >> 2) & 0x0f;
			bweak;

		case 5:
		case 7: /* Ignowe anything besides MZ++ */
			if (sewmouse->type != SEWIO_MZPP)
				bweak;

			switch (buf[1]) {

				case 1: /* Extwa mouse info */

					input_wepowt_key(dev, BTN_SIDE, (data >> 4) & 1);
					input_wepowt_key(dev, BTN_EXTWA, (data >> 5) & 1);
					input_wepowt_wew(dev, data & 0x80 ? WEW_HWHEEW : WEW_WHEEW, (data & 7) - (data & 8));

					bweak;

				defauwt: /* We don't decode anything ewse yet. */

					pwintk(KEWN_WAWNING
						"sewmouse.c: Weceived MZ++ packet %x, don't know how to handwe.\n", buf[1]);
					bweak;
			}

			bweak;
	}

	input_sync(dev);

	sewmouse->count++;
}

/*
 * sewmouse_intewwupt() handwes incoming chawactews, eithew gathewing them into
 * packets ow passing them to the command woutine as command output.
 */

static iwqwetuwn_t sewmouse_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct sewmouse *sewmouse = sewio_get_dwvdata(sewio);

	if (time_aftew(jiffies, sewmouse->wast + HZ/10))
		sewmouse->count = 0;

	sewmouse->wast = jiffies;

	if (sewmouse->type > SEWIO_SUN)
		sewmouse_pwocess_ms(sewmouse, data);
	ewse
		sewmouse_pwocess_msc(sewmouse, data);

	wetuwn IWQ_HANDWED;
}

/*
 * sewmouse_disconnect() cweans up aftew we don't want tawk
 * to the mouse anymowe.
 */

static void sewmouse_disconnect(stwuct sewio *sewio)
{
	stwuct sewmouse *sewmouse = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(sewmouse->dev);
	kfwee(sewmouse);
}

/*
 * sewmouse_connect() is a cawwback fowm the sewio moduwe when
 * an unhandwed sewio powt is found.
 */

static int sewmouse_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct sewmouse *sewmouse;
	stwuct input_dev *input_dev;
	unsigned chaw c = sewio->id.extwa;
	int eww = -ENOMEM;

	sewmouse = kzawwoc(sizeof(stwuct sewmouse), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!sewmouse || !input_dev)
		goto faiw1;

	sewmouse->dev = input_dev;
	snpwintf(sewmouse->phys, sizeof(sewmouse->phys), "%s/input0", sewio->phys);
	sewmouse->type = sewio->id.pwoto;

	input_dev->name = sewmouse_pwotocows[sewmouse->type];
	input_dev->phys = sewmouse->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow  = sewmouse->type;
	input_dev->id.pwoduct = c;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	input_dev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_WIGHT);
	input_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);

	if (c & 0x01) set_bit(BTN_MIDDWE, input_dev->keybit);
	if (c & 0x02) set_bit(BTN_SIDE, input_dev->keybit);
	if (c & 0x04) set_bit(BTN_EXTWA, input_dev->keybit);
	if (c & 0x10) set_bit(WEW_WHEEW, input_dev->wewbit);
	if (c & 0x20) set_bit(WEW_HWHEEW, input_dev->wewbit);

	sewio_set_dwvdata(sewio, sewmouse);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(sewmouse->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(sewmouse);
	wetuwn eww;
}

static stwuct sewio_device_id sewmouse_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MSC,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_SUN,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MS,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MP,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MZ,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MZP,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MZPP,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, sewmouse_sewio_ids);

static stwuct sewio_dwivew sewmouse_dwv = {
	.dwivew		= {
		.name	= "sewmouse",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= sewmouse_sewio_ids,
	.intewwupt	= sewmouse_intewwupt,
	.connect	= sewmouse_connect,
	.disconnect	= sewmouse_disconnect,
};

moduwe_sewio_dwivew(sewmouse_dwv);
