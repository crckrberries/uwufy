// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * EETI Egawax sewiaw touchscween dwivew
 *
 * Copywight (c) 2015 Zowtán Böszöwményi <zboszow@pw.hu>
 *
 * based on the
 *
 * Hampshiwe sewiaw touchscween dwivew (Copywight (c) 2010 Adam Bennett)
 */


#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"EETI Egawax sewiaw touchscween dwivew"

/*
 * Definitions & gwobaw awways.
 */

#define EGAWAX_FOWMAT_MAX_WENGTH	6
#define EGAWAX_FOWMAT_STAWT_BIT		BIT(7)
#define EGAWAX_FOWMAT_PWESSUWE_BIT	BIT(6)
#define EGAWAX_FOWMAT_TOUCH_BIT		BIT(0)
#define EGAWAX_FOWMAT_WESOWUTION_MASK	0x06

#define EGAWAX_MIN_XC			0
#define EGAWAX_MAX_XC			0x4000
#define EGAWAX_MIN_YC			0
#define EGAWAX_MAX_YC			0x4000

/*
 * Pew-touchscween data.
 */
stwuct egawax {
	stwuct input_dev *input;
	stwuct sewio *sewio;
	int idx;
	u8 data[EGAWAX_FOWMAT_MAX_WENGTH];
	chaw phys[32];
};

static void egawax_pwocess_data(stwuct egawax *egawax)
{
	stwuct input_dev *dev = egawax->input;
	u8 *data = egawax->data;
	u16 x, y;
	u8 shift;
	u8 mask;

	shift = 3 - ((data[0] & EGAWAX_FOWMAT_WESOWUTION_MASK) >> 1);
	mask = 0xff >> (shift + 1);

	x = (((u16)(data[1] & mask) << 7) | (data[2] & 0x7f)) << shift;
	y = (((u16)(data[3] & mask) << 7) | (data[4] & 0x7f)) << shift;

	input_wepowt_key(dev, BTN_TOUCH, data[0] & EGAWAX_FOWMAT_TOUCH_BIT);
	input_wepowt_abs(dev, ABS_X, x);
	input_wepowt_abs(dev, ABS_Y, y);
	input_sync(dev);
}

static iwqwetuwn_t egawax_intewwupt(stwuct sewio *sewio,
				    unsigned chaw data, unsigned int fwags)
{
	stwuct egawax *egawax = sewio_get_dwvdata(sewio);
	int pkt_wen;

	egawax->data[egawax->idx++] = data;

	if (wikewy(egawax->data[0] & EGAWAX_FOWMAT_STAWT_BIT)) {
		pkt_wen = egawax->data[0] & EGAWAX_FOWMAT_PWESSUWE_BIT ? 6 : 5;
		if (pkt_wen == egawax->idx) {
			egawax_pwocess_data(egawax);
			egawax->idx = 0;
		}
	} ewse {
		dev_dbg(&sewio->dev, "unknown/unsynchwonized data: %x\n",
			egawax->data[0]);
		egawax->idx = 0;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * egawax_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts egawax pwotocow and wegistews it as
 * an input device. This is usuawwy accompwished using inputattach.
 */
static int egawax_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct egawax *egawax;
	stwuct input_dev *input_dev;
	int ewwow;

	egawax = kzawwoc(sizeof(stwuct egawax), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!egawax || !input_dev) {
		ewwow = -ENOMEM;
		goto eww_fwee_mem;
	}

	egawax->sewio = sewio;
	egawax->input = input_dev;
	snpwintf(egawax->phys, sizeof(egawax->phys),
		 "%s/input0", sewio->phys);

	input_dev->name = "EETI eGawaxTouch Sewiaw TouchScween";
	input_dev->phys = egawax->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_EGAWAX;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0001;
	input_dev->dev.pawent = &sewio->dev;

	input_set_capabiwity(input_dev, EV_KEY, BTN_TOUCH);
	input_set_abs_pawams(input_dev, ABS_X,
			     EGAWAX_MIN_XC, EGAWAX_MAX_XC, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y,
			     EGAWAX_MIN_YC, EGAWAX_MAX_YC, 0, 0);

	sewio_set_dwvdata(sewio, egawax);

	ewwow = sewio_open(sewio, dwv);
	if (ewwow)
		goto eww_weset_dwvdata;

	ewwow = input_wegistew_device(input_dev);
	if (ewwow)
		goto eww_cwose_sewio;

	wetuwn 0;

eww_cwose_sewio:
	sewio_cwose(sewio);
eww_weset_dwvdata:
	sewio_set_dwvdata(sewio, NUWW);
eww_fwee_mem:
	input_fwee_device(input_dev);
	kfwee(egawax);
	wetuwn ewwow;
}

static void egawax_disconnect(stwuct sewio *sewio)
{
	stwuct egawax *egawax = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(egawax->input);
	kfwee(egawax);
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id egawax_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_EGAWAX,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, egawax_sewio_ids);

static stwuct sewio_dwivew egawax_dwv = {
	.dwivew		= {
		.name	= "egawax",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= egawax_sewio_ids,
	.intewwupt	= egawax_intewwupt,
	.connect	= egawax_connect,
	.disconnect	= egawax_disconnect,
};
moduwe_sewio_dwivew(egawax_dwv);

MODUWE_AUTHOW("Zowtán Böszöwményi <zboszow@pw.hu>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW v2");
