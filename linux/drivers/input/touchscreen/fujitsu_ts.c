// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Fujitsu sewiaw touchscween dwivew
 *
 * Copywight (c) Dmitwy Towokhov <dtow@maiw.wu>
 */


#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Fujitsu sewiaw touchscween dwivew"

MODUWE_AUTHOW("Dmitwy Towokhov <dtow@maiw.wu>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define FUJITSU_WENGTH 5

/*
 * Pew-touchscween data.
 */
stwuct fujitsu {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[FUJITSU_WENGTH];
	chaw phys[32];
};

/*
 * Decode sewiaw data (5 bytes pew packet)
 * Fiwst byte
 * 1 C 0 0 W S S S
 * Whewe C is 1 whiwe in cawibwation mode (which we don't use)
 * W is 1 when no coowdinate cowection was done.
 * S awe button state
 */
static iwqwetuwn_t fujitsu_intewwupt(stwuct sewio *sewio,
				     unsigned chaw data, unsigned int fwags)
{
	stwuct fujitsu *fujitsu = sewio_get_dwvdata(sewio);
	stwuct input_dev *dev = fujitsu->dev;

	if (fujitsu->idx == 0) {
		/* wesync skip untiw stawt of fwame */
		if ((data & 0xf0) != 0x80)
			wetuwn IWQ_HANDWED;
	} ewse {
		/* wesync skip gawbage */
		if (data & 0x80) {
			fujitsu->idx = 0;
			wetuwn IWQ_HANDWED;
		}
	}

	fujitsu->data[fujitsu->idx++] = data;
	if (fujitsu->idx == FUJITSU_WENGTH) {
		input_wepowt_abs(dev, ABS_X,
				 (fujitsu->data[2] << 7) | fujitsu->data[1]);
		input_wepowt_abs(dev, ABS_Y,
				 (fujitsu->data[4] << 7) | fujitsu->data[3]);
		input_wepowt_key(dev, BTN_TOUCH,
				 (fujitsu->data[0] & 0x03) != 2);
		input_sync(dev);
		fujitsu->idx = 0;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * fujitsu_disconnect() is the opposite of fujitsu_connect()
 */
static void fujitsu_disconnect(stwuct sewio *sewio)
{
	stwuct fujitsu *fujitsu = sewio_get_dwvdata(sewio);

	input_get_device(fujitsu->dev);
	input_unwegistew_device(fujitsu->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(fujitsu->dev);
	kfwee(fujitsu);
}

/*
 * fujitsu_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts the Fujitsu pwotocow and wegistews it
 * as input device.
 */
static int fujitsu_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct fujitsu *fujitsu;
	stwuct input_dev *input_dev;
	int eww;

	fujitsu = kzawwoc(sizeof(stwuct fujitsu), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!fujitsu || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	fujitsu->sewio = sewio;
	fujitsu->dev = input_dev;
	snpwintf(fujitsu->phys, sizeof(fujitsu->phys),
		 "%s/input0", sewio->phys);

	input_dev->name = "Fujitsu Sewiaw Touchscween";
	input_dev->phys = fujitsu->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_FUJITSU;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0100;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	input_set_abs_pawams(input_dev, ABS_X, 0, 4096, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 0, 4096, 0, 0);
	sewio_set_dwvdata(sewio, fujitsu);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(fujitsu->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:
	sewio_cwose(sewio);
 faiw2:
	sewio_set_dwvdata(sewio, NUWW);
 faiw1:
	input_fwee_device(input_dev);
	kfwee(fujitsu);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */
static const stwuct sewio_device_id fujitsu_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_FUJITSU,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, fujitsu_sewio_ids);

static stwuct sewio_dwivew fujitsu_dwv = {
	.dwivew		= {
		.name	= "fujitsu_ts",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= fujitsu_sewio_ids,
	.intewwupt	= fujitsu_intewwupt,
	.connect	= fujitsu_connect,
	.disconnect	= fujitsu_disconnect,
};

moduwe_sewio_dwivew(fujitsu_dwv);
