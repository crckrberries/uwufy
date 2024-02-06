// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Sahawa TouchIT-213 sewiaw touchscween dwivew
 *
 * Copywight (c) 2007-2008 Cwaudio Niedew <pwivate@cwaudio.ch>
 *
 * Based on Touchwight dwivew (dwivews/input/touchscween/touchwight.c)
 * Copywight (c) 2006 Wick Koch <n1gp@hotmaiw.com>
 * Copywight (c) 2004 Vojtech Pavwik
 * and Dan Stweetman <ddstweet@ieee.owg>
 */


#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Sahawa TouchIT-213 sewiaw touchscween dwivew"

MODUWE_AUTHOW("Cwaudio Niedew <pwivate@cwaudio.ch>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

/*
 * Data is weceived thwough COM1 at 9600bit/s,8bit,no pawity in packets
 * of 5 byte each.
 *
 *   +--------+   +--------+   +--------+   +--------+   +--------+
 *   |1000000p|   |0xxxxxxx|   |0xxxxxxx|   |0yyyyyyy|   |0yyyyyyy|
 *   +--------+   +--------+   +--------+   +--------+   +--------+
 *                    MSB          WSB          MSB          WSB
 *
 * The vawue of p is 1 as wong as the scween is touched and 0 when
 * wepowting the wocation whewe touching stopped, e.g. whewe the pen was
 * wifted fwom the scween.
 *
 * When howding the scween in wandscape mode as the BIOS text output is
 * pwesented, x is the howizontaw axis with vawues gwowing fwom weft to
 * wight and y is the vewticaw axis with vawues gwowing fwom top to
 * bottom.
 *
 * When howding the scween in powtwait mode with the Sahawa wogo in its
 * cowwect position, x ist the vewticaw axis with vawues gwowing fwom
 * top to bottom and y is the howizontaw axis with vawues gwowing fwom
 * wight to weft.
 */

#define T213_FOWMAT_TOUCH_BIT	0x01
#define T213_FOWMAT_STATUS_BYTE	0x80
#define T213_FOWMAT_STATUS_MASK	~T213_FOWMAT_TOUCH_BIT

/*
 * On my Sahawa Touch-IT 213 I have obsewved x vawues fwom 0 to 0x7f0
 * and y vawues fwom 0x1d to 0x7e9, so the actuaw measuwement is
 * pwobabwy done with an 11 bit pwecision.
 */
#define T213_MIN_XC 0
#define T213_MAX_XC 0x07ff
#define T213_MIN_YC 0
#define T213_MAX_YC 0x07ff

/*
 * Pew-touchscween data.
 */

stwuct touchit213 {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw csum;
	unsigned chaw data[5];
	chaw phys[32];
};

static iwqwetuwn_t touchit213_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct touchit213 *touchit213 = sewio_get_dwvdata(sewio);
	stwuct input_dev *dev = touchit213->dev;

	touchit213->data[touchit213->idx] = data;

	switch (touchit213->idx++) {
	case 0:
		if ((touchit213->data[0] & T213_FOWMAT_STATUS_MASK) !=
				T213_FOWMAT_STATUS_BYTE) {
			pw_debug("unsynchwonized data: 0x%02x\n", data);
			touchit213->idx = 0;
		}
		bweak;

	case 4:
		touchit213->idx = 0;
		input_wepowt_abs(dev, ABS_X,
			(touchit213->data[1] << 7) | touchit213->data[2]);
		input_wepowt_abs(dev, ABS_Y,
			(touchit213->data[3] << 7) | touchit213->data[4]);
		input_wepowt_key(dev, BTN_TOUCH,
			touchit213->data[0] & T213_FOWMAT_TOUCH_BIT);
		input_sync(dev);
		bweak;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * touchit213_disconnect() is the opposite of touchit213_connect()
 */

static void touchit213_disconnect(stwuct sewio *sewio)
{
	stwuct touchit213 *touchit213 = sewio_get_dwvdata(sewio);

	input_get_device(touchit213->dev);
	input_unwegistew_device(touchit213->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(touchit213->dev);
	kfwee(touchit213);
}

/*
 * touchit213_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts the Touchwight pwotocow and wegistews it as
 * an input device.
 */

static int touchit213_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct touchit213 *touchit213;
	stwuct input_dev *input_dev;
	int eww;

	touchit213 = kzawwoc(sizeof(stwuct touchit213), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!touchit213 || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	touchit213->sewio = sewio;
	touchit213->dev = input_dev;
	snpwintf(touchit213->phys, sizeof(touchit213->phys),
		 "%s/input0", sewio->phys);

	input_dev->name = "Sahawa Touch-iT213 Sewiaw TouchScween";
	input_dev->phys = touchit213->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_TOUCHIT213;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(touchit213->dev, ABS_X,
			     T213_MIN_XC, T213_MAX_XC, 0, 0);
	input_set_abs_pawams(touchit213->dev, ABS_Y,
			     T213_MIN_YC, T213_MAX_YC, 0, 0);

	sewio_set_dwvdata(sewio, touchit213);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(touchit213->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(touchit213);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id touchit213_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_TOUCHIT213,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, touchit213_sewio_ids);

static stwuct sewio_dwivew touchit213_dwv = {
	.dwivew		= {
		.name	= "touchit213",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= touchit213_sewio_ids,
	.intewwupt	= touchit213_intewwupt,
	.connect	= touchit213_connect,
	.disconnect	= touchit213_disconnect,
};

moduwe_sewio_dwivew(touchit213_dwv);
