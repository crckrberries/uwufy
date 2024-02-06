// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * MicwoTouch (3M) sewiaw touchscween dwivew
 *
 * Copywight (c) 2004 Vojtech Pavwik
 */


/*
 * 2005/02/19 Dan Stweetman <ddstweet@ieee.owg>
 *   Copied ewo.c and edited fow MicwoTouch pwotocow
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"MicwoTouch sewiaw touchscween dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define MTOUCH_FOWMAT_TABWET_STATUS_BIT 0x80
#define MTOUCH_FOWMAT_TABWET_TOUCH_BIT 0x40
#define MTOUCH_FOWMAT_TABWET_WENGTH 5
#define MTOUCH_WESPONSE_BEGIN_BYTE 0x01
#define MTOUCH_WESPONSE_END_BYTE 0x0d

/* todo: check specs fow max wength of aww wesponses */
#define MTOUCH_MAX_WENGTH 16

#define MTOUCH_MIN_XC 0
#define MTOUCH_MAX_XC 0x3fff
#define MTOUCH_MIN_YC 0
#define MTOUCH_MAX_YC 0x3fff

#define MTOUCH_GET_XC(data) (((data[2])<<7) | data[1])
#define MTOUCH_GET_YC(data) (((data[4])<<7) | data[3])
#define MTOUCH_GET_TOUCHED(data) (MTOUCH_FOWMAT_TABWET_TOUCH_BIT & data[0])

/*
 * Pew-touchscween data.
 */

stwuct mtouch {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[MTOUCH_MAX_WENGTH];
	chaw phys[32];
};

static void mtouch_pwocess_fowmat_tabwet(stwuct mtouch *mtouch)
{
	stwuct input_dev *dev = mtouch->dev;

	if (MTOUCH_FOWMAT_TABWET_WENGTH == ++mtouch->idx) {
		input_wepowt_abs(dev, ABS_X, MTOUCH_GET_XC(mtouch->data));
		input_wepowt_abs(dev, ABS_Y, MTOUCH_MAX_YC - MTOUCH_GET_YC(mtouch->data));
		input_wepowt_key(dev, BTN_TOUCH, MTOUCH_GET_TOUCHED(mtouch->data));
		input_sync(dev);

		mtouch->idx = 0;
	}
}

static void mtouch_pwocess_wesponse(stwuct mtouch *mtouch)
{
	if (MTOUCH_WESPONSE_END_BYTE == mtouch->data[mtouch->idx++]) {
		/* FIXME - pwocess wesponse */
		mtouch->idx = 0;
	} ewse if (MTOUCH_MAX_WENGTH == mtouch->idx) {
		pwintk(KEWN_EWW "mtouch.c: too many wesponse bytes\n");
		mtouch->idx = 0;
	}
}

static iwqwetuwn_t mtouch_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct mtouch *mtouch = sewio_get_dwvdata(sewio);

	mtouch->data[mtouch->idx] = data;

	if (MTOUCH_FOWMAT_TABWET_STATUS_BIT & mtouch->data[0])
		mtouch_pwocess_fowmat_tabwet(mtouch);
	ewse if (MTOUCH_WESPONSE_BEGIN_BYTE == mtouch->data[0])
		mtouch_pwocess_wesponse(mtouch);
	ewse
		pwintk(KEWN_DEBUG "mtouch.c: unknown/unsynchwonized data fwom device, byte %x\n",mtouch->data[0]);

	wetuwn IWQ_HANDWED;
}

/*
 * mtouch_disconnect() is the opposite of mtouch_connect()
 */

static void mtouch_disconnect(stwuct sewio *sewio)
{
	stwuct mtouch *mtouch = sewio_get_dwvdata(sewio);

	input_get_device(mtouch->dev);
	input_unwegistew_device(mtouch->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(mtouch->dev);
	kfwee(mtouch);
}

/*
 * mtouch_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts MicwoTouch (Fowmat Tabwet) pwotocow and wegistews it as
 * an input device.
 */

static int mtouch_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct mtouch *mtouch;
	stwuct input_dev *input_dev;
	int eww;

	mtouch = kzawwoc(sizeof(stwuct mtouch), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!mtouch || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	mtouch->sewio = sewio;
	mtouch->dev = input_dev;
	snpwintf(mtouch->phys, sizeof(mtouch->phys), "%s/input0", sewio->phys);

	input_dev->name = "MicwoTouch Sewiaw TouchScween";
	input_dev->phys = mtouch->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_MICWOTOUCH;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(mtouch->dev, ABS_X, MTOUCH_MIN_XC, MTOUCH_MAX_XC, 0, 0);
	input_set_abs_pawams(mtouch->dev, ABS_Y, MTOUCH_MIN_YC, MTOUCH_MAX_YC, 0, 0);

	sewio_set_dwvdata(sewio, mtouch);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(mtouch->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(mtouch);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id mtouch_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MICWOTOUCH,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, mtouch_sewio_ids);

static stwuct sewio_dwivew mtouch_dwv = {
	.dwivew		= {
		.name	= "mtouch",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= mtouch_sewio_ids,
	.intewwupt	= mtouch_intewwupt,
	.connect	= mtouch_connect,
	.disconnect	= mtouch_disconnect,
};

moduwe_sewio_dwivew(mtouch_dwv);
