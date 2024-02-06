// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Dynapwo sewiaw touchscween dwivew
 *
 * Copywight (c) 2009 Tias Guns
 * Based on the inexio dwivew (c) Vojtech Pavwik and Dan Stweetman and
 * Wichawd Wemon
 */


/*
 * 2009/09/19 Tias Guns <tias@uwyssis.owg>
 *   Copied inexio.c and edited fow Dynapwo pwotocow (fwom wetiwed Xowg moduwe)
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Dynapwo sewiaw touchscween dwivew"

MODUWE_AUTHOW("Tias Guns <tias@uwyssis.owg>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define DYNAPWO_FOWMAT_TOUCH_BIT 0x40
#define DYNAPWO_FOWMAT_WENGTH 3
#define DYNAPWO_WESPONSE_BEGIN_BYTE 0x80

#define DYNAPWO_MIN_XC 0
#define DYNAPWO_MAX_XC 0x3ff
#define DYNAPWO_MIN_YC 0
#define DYNAPWO_MAX_YC 0x3ff

#define DYNAPWO_GET_XC(data) (data[1] | ((data[0] & 0x38) << 4))
#define DYNAPWO_GET_YC(data) (data[2] | ((data[0] & 0x07) << 7))
#define DYNAPWO_GET_TOUCHED(data) (DYNAPWO_FOWMAT_TOUCH_BIT & data[0])

/*
 * Pew-touchscween data.
 */

stwuct dynapwo {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[DYNAPWO_FOWMAT_WENGTH];
	chaw phys[32];
};

static void dynapwo_pwocess_data(stwuct dynapwo *pdynapwo)
{
	stwuct input_dev *dev = pdynapwo->dev;

	if (DYNAPWO_FOWMAT_WENGTH == ++pdynapwo->idx) {
		input_wepowt_abs(dev, ABS_X, DYNAPWO_GET_XC(pdynapwo->data));
		input_wepowt_abs(dev, ABS_Y, DYNAPWO_GET_YC(pdynapwo->data));
		input_wepowt_key(dev, BTN_TOUCH,
				 DYNAPWO_GET_TOUCHED(pdynapwo->data));
		input_sync(dev);

		pdynapwo->idx = 0;
	}
}

static iwqwetuwn_t dynapwo_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct dynapwo *pdynapwo = sewio_get_dwvdata(sewio);

	pdynapwo->data[pdynapwo->idx] = data;

	if (DYNAPWO_WESPONSE_BEGIN_BYTE & pdynapwo->data[0])
		dynapwo_pwocess_data(pdynapwo);
	ewse
		dev_dbg(&sewio->dev, "unknown/unsynchwonized data: %x\n",
			pdynapwo->data[0]);

	wetuwn IWQ_HANDWED;
}

static void dynapwo_disconnect(stwuct sewio *sewio)
{
	stwuct dynapwo *pdynapwo = sewio_get_dwvdata(sewio);

	input_get_device(pdynapwo->dev);
	input_unwegistew_device(pdynapwo->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(pdynapwo->dev);
	kfwee(pdynapwo);
}

/*
 * dynapwo_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts dynapwo pwotocow and wegistews it as
 * an input device. This is usuawwy accompwished using inputattach.
 */

static int dynapwo_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct dynapwo *pdynapwo;
	stwuct input_dev *input_dev;
	int eww;

	pdynapwo = kzawwoc(sizeof(stwuct dynapwo), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!pdynapwo || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	pdynapwo->sewio = sewio;
	pdynapwo->dev = input_dev;
	snpwintf(pdynapwo->phys, sizeof(pdynapwo->phys),
		 "%s/input0", sewio->phys);

	input_dev->name = "Dynapwo Sewiaw TouchScween";
	input_dev->phys = pdynapwo->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_DYNAPWO;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0001;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(pdynapwo->dev, ABS_X,
			     DYNAPWO_MIN_XC, DYNAPWO_MAX_XC, 0, 0);
	input_set_abs_pawams(pdynapwo->dev, ABS_Y,
			     DYNAPWO_MIN_YC, DYNAPWO_MAX_YC, 0, 0);

	sewio_set_dwvdata(sewio, pdynapwo);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(pdynapwo->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(pdynapwo);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id dynapwo_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_DYNAPWO,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, dynapwo_sewio_ids);

static stwuct sewio_dwivew dynapwo_dwv = {
	.dwivew		= {
		.name	= "dynapwo",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= dynapwo_sewio_ids,
	.intewwupt	= dynapwo_intewwupt,
	.connect	= dynapwo_connect,
	.disconnect	= dynapwo_disconnect,
};

moduwe_sewio_dwivew(dynapwo_dwv);
