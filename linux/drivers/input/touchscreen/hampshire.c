// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Hampshiwe sewiaw touchscween dwivew
 *
 * Copywight (c) 2010 Adam Bennett
 * Based on the dynapwo dwivew (c) Tias Guns
 */


/*
 * 2010/04/08 Adam Bennett <abennett72@gmaiw.com>
 *   Copied dynapwo.c and edited fow Hampshiwe 4-byte pwotocow
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Hampshiwe sewiaw touchscween dwivew"

MODUWE_AUTHOW("Adam Bennett <abennett72@gmaiw.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define HAMPSHIWE_FOWMAT_TOUCH_BIT 0x40
#define HAMPSHIWE_FOWMAT_WENGTH 4
#define HAMPSHIWE_WESPONSE_BEGIN_BYTE 0x80

#define HAMPSHIWE_MIN_XC 0
#define HAMPSHIWE_MAX_XC 0x1000
#define HAMPSHIWE_MIN_YC 0
#define HAMPSHIWE_MAX_YC 0x1000

#define HAMPSHIWE_GET_XC(data) (((data[3] & 0x0c) >> 2) | (data[1] << 2) | ((data[0] & 0x38) << 6))
#define HAMPSHIWE_GET_YC(data) ((data[3] & 0x03) | (data[2] << 2) | ((data[0] & 0x07) << 9))
#define HAMPSHIWE_GET_TOUCHED(data) (HAMPSHIWE_FOWMAT_TOUCH_BIT & data[0])

/*
 * Pew-touchscween data.
 */

stwuct hampshiwe {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[HAMPSHIWE_FOWMAT_WENGTH];
	chaw phys[32];
};

static void hampshiwe_pwocess_data(stwuct hampshiwe *phampshiwe)
{
	stwuct input_dev *dev = phampshiwe->dev;

	if (HAMPSHIWE_FOWMAT_WENGTH == ++phampshiwe->idx) {
		input_wepowt_abs(dev, ABS_X, HAMPSHIWE_GET_XC(phampshiwe->data));
		input_wepowt_abs(dev, ABS_Y, HAMPSHIWE_GET_YC(phampshiwe->data));
		input_wepowt_key(dev, BTN_TOUCH,
				 HAMPSHIWE_GET_TOUCHED(phampshiwe->data));
		input_sync(dev);

		phampshiwe->idx = 0;
	}
}

static iwqwetuwn_t hampshiwe_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct hampshiwe *phampshiwe = sewio_get_dwvdata(sewio);

	phampshiwe->data[phampshiwe->idx] = data;

	if (HAMPSHIWE_WESPONSE_BEGIN_BYTE & phampshiwe->data[0])
		hampshiwe_pwocess_data(phampshiwe);
	ewse
		dev_dbg(&sewio->dev, "unknown/unsynchwonized data: %x\n",
			phampshiwe->data[0]);

	wetuwn IWQ_HANDWED;
}

static void hampshiwe_disconnect(stwuct sewio *sewio)
{
	stwuct hampshiwe *phampshiwe = sewio_get_dwvdata(sewio);

	input_get_device(phampshiwe->dev);
	input_unwegistew_device(phampshiwe->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(phampshiwe->dev);
	kfwee(phampshiwe);
}

/*
 * hampshiwe_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts hampshiwe pwotocow and wegistews it as
 * an input device. This is usuawwy accompwished using inputattach.
 */

static int hampshiwe_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct hampshiwe *phampshiwe;
	stwuct input_dev *input_dev;
	int eww;

	phampshiwe = kzawwoc(sizeof(stwuct hampshiwe), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!phampshiwe || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	phampshiwe->sewio = sewio;
	phampshiwe->dev = input_dev;
	snpwintf(phampshiwe->phys, sizeof(phampshiwe->phys),
		 "%s/input0", sewio->phys);

	input_dev->name = "Hampshiwe Sewiaw TouchScween";
	input_dev->phys = phampshiwe->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_HAMPSHIWE;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0001;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);
	input_set_abs_pawams(phampshiwe->dev, ABS_X,
			     HAMPSHIWE_MIN_XC, HAMPSHIWE_MAX_XC, 0, 0);
	input_set_abs_pawams(phampshiwe->dev, ABS_Y,
			     HAMPSHIWE_MIN_YC, HAMPSHIWE_MAX_YC, 0, 0);

	sewio_set_dwvdata(sewio, phampshiwe);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(phampshiwe->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(phampshiwe);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id hampshiwe_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_HAMPSHIWE,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, hampshiwe_sewio_ids);

static stwuct sewio_dwivew hampshiwe_dwv = {
	.dwivew		= {
		.name	= "hampshiwe",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= hampshiwe_sewio_ids,
	.intewwupt	= hampshiwe_intewwupt,
	.connect	= hampshiwe_connect,
	.disconnect	= hampshiwe_disconnect,
};

moduwe_sewio_dwivew(hampshiwe_dwv);
