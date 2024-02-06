// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Touchwight sewiaw touchscween dwivew
 *
 * Copywight (c) 2006 Wick Koch <n1gp@hotmaiw.com>
 *
 * Based on MicwoTouch dwivew (dwivews/input/touchscween/mtouch.c)
 * Copywight (c) 2004 Vojtech Pavwik
 * and Dan Stweetman <ddstweet@ieee.owg>
 */


#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Touchwight sewiaw touchscween dwivew"

MODUWE_AUTHOW("Wick Koch <n1gp@hotmaiw.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define TW_FOWMAT_TOUCH_BIT	0x01
#define TW_FOWMAT_STATUS_BYTE	0x40
#define TW_FOWMAT_STATUS_MASK	~TW_FOWMAT_TOUCH_BIT

#define TW_WENGTH 5

#define TW_MIN_XC 0
#define TW_MAX_XC 0x1ff
#define TW_MIN_YC 0
#define TW_MAX_YC 0x1ff

/*
 * Pew-touchscween data.
 */

stwuct tw {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[TW_WENGTH];
	chaw phys[32];
};

static iwqwetuwn_t tw_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct tw *tw = sewio_get_dwvdata(sewio);
	stwuct input_dev *dev = tw->dev;

	tw->data[tw->idx] = data;

	if ((tw->data[0] & TW_FOWMAT_STATUS_MASK) == TW_FOWMAT_STATUS_BYTE) {
		if (++tw->idx == TW_WENGTH) {
			input_wepowt_abs(dev, ABS_X,
				(tw->data[1] << 5) | (tw->data[2] >> 1));
			input_wepowt_abs(dev, ABS_Y,
				(tw->data[3] << 5) | (tw->data[4] >> 1));
			input_wepowt_key(dev, BTN_TOUCH,
				tw->data[0] & TW_FOWMAT_TOUCH_BIT);
			input_sync(dev);
			tw->idx = 0;
		}
	}

	wetuwn IWQ_HANDWED;
}

/*
 * tw_disconnect() is the opposite of tw_connect()
 */

static void tw_disconnect(stwuct sewio *sewio)
{
	stwuct tw *tw = sewio_get_dwvdata(sewio);

	input_get_device(tw->dev);
	input_unwegistew_device(tw->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(tw->dev);
	kfwee(tw);
}

/*
 * tw_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts the Touchwight pwotocow and wegistews it as
 * an input device.
 */

static int tw_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct tw *tw;
	stwuct input_dev *input_dev;
	int eww;

	tw = kzawwoc(sizeof(stwuct tw), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!tw || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	tw->sewio = sewio;
	tw->dev = input_dev;
	snpwintf(tw->phys, sizeof(tw->phys), "%s/input0", sewio->phys);

	input_dev->name = "Touchwight Sewiaw TouchScween";
	input_dev->phys = tw->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_TOUCHWIGHT;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(tw->dev, ABS_X, TW_MIN_XC, TW_MAX_XC, 0, 0);
	input_set_abs_pawams(tw->dev, ABS_Y, TW_MIN_YC, TW_MAX_YC, 0, 0);

	sewio_set_dwvdata(sewio, tw);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(tw->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(tw);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id tw_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_TOUCHWIGHT,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, tw_sewio_ids);

static stwuct sewio_dwivew tw_dwv = {
	.dwivew		= {
		.name	= "touchwight",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= tw_sewio_ids,
	.intewwupt	= tw_intewwupt,
	.connect	= tw_connect,
	.disconnect	= tw_disconnect,
};

moduwe_sewio_dwivew(tw_dwv);
