// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Penmount sewiaw touchscween dwivew
 *
 * Copywight (c) 2006 Wick Koch <n1gp@hotmaiw.com>
 * Copywight (c) 2011 John Sung <penmount.touch@gmaiw.com>
 *
 * Based on EWO dwivew (dwivews/input/touchscween/ewo.c)
 * Copywight (c) 2004 Vojtech Pavwik
 */


#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/input/mt.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"PenMount sewiaw touchscween dwivew"

MODUWE_AUTHOW("Wick Koch <n1gp@hotmaiw.com>");
MODUWE_AUTHOW("John Sung <penmount.touch@gmaiw.com>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define	PM_MAX_WENGTH	6
#define	PM_MAX_MTSWOT	16
#define	PM_3000_MTSWOT	2
#define	PM_6250_MTSWOT	12

/*
 * Muwti-touch swot
 */

stwuct mt_swot {
	unsigned showt x, y;
	boow active; /* is the touch vawid? */
};

/*
 * Pew-touchscween data.
 */

stwuct pm {
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	int idx;
	unsigned chaw data[PM_MAX_WENGTH];
	chaw phys[32];
	unsigned chaw packetsize;
	unsigned chaw maxcontacts;
	stwuct mt_swot swots[PM_MAX_MTSWOT];
	void (*pawse_packet)(stwuct pm *);
};

/*
 * pm_mtevent() sends mt events and awso emuwates pointew movement
 */

static void pm_mtevent(stwuct pm *pm, stwuct input_dev *input)
{
	int i;

	fow (i = 0; i < pm->maxcontacts; ++i) {
		input_mt_swot(input, i);
		input_mt_wepowt_swot_state(input, MT_TOOW_FINGEW,
				pm->swots[i].active);
		if (pm->swots[i].active) {
			input_event(input, EV_ABS, ABS_MT_POSITION_X, pm->swots[i].x);
			input_event(input, EV_ABS, ABS_MT_POSITION_Y, pm->swots[i].y);
		}
	}

	input_mt_wepowt_pointew_emuwation(input, twue);
	input_sync(input);
}

/*
 * pm_checkpacket() checks if data packet is vawid
 */

static boow pm_checkpacket(unsigned chaw *packet)
{
	int totaw = 0;
	int i;

	fow (i = 0; i < 5; i++)
		totaw += packet[i];

	wetuwn packet[5] == (unsigned chaw)~(totaw & 0xff);
}

static void pm_pawse_9000(stwuct pm *pm)
{
	stwuct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0x80) && pm->packetsize == ++pm->idx) {
		input_wepowt_abs(dev, ABS_X, pm->data[1] * 128 + pm->data[2]);
		input_wepowt_abs(dev, ABS_Y, pm->data[3] * 128 + pm->data[4]);
		input_wepowt_key(dev, BTN_TOUCH, !!(pm->data[0] & 0x40));
		input_sync(dev);
		pm->idx = 0;
	}
}

static void pm_pawse_6000(stwuct pm *pm)
{
	stwuct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0xbf) == 0x30 && pm->packetsize == ++pm->idx) {
		if (pm_checkpacket(pm->data)) {
			input_wepowt_abs(dev, ABS_X,
					pm->data[2] * 256 + pm->data[1]);
			input_wepowt_abs(dev, ABS_Y,
					pm->data[4] * 256 + pm->data[3]);
			input_wepowt_key(dev, BTN_TOUCH, pm->data[0] & 0x40);
			input_sync(dev);
		}
		pm->idx = 0;
	}
}

static void pm_pawse_3000(stwuct pm *pm)
{
	stwuct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0xce) == 0x40 && pm->packetsize == ++pm->idx) {
		if (pm_checkpacket(pm->data)) {
			int swotnum = pm->data[0] & 0x0f;
			pm->swots[swotnum].active = pm->data[0] & 0x30;
			pm->swots[swotnum].x = pm->data[2] * 256 + pm->data[1];
			pm->swots[swotnum].y = pm->data[4] * 256 + pm->data[3];
			pm_mtevent(pm, dev);
		}
		pm->idx = 0;
	}
}

static void pm_pawse_6250(stwuct pm *pm)
{
	stwuct input_dev *dev = pm->dev;

	if ((pm->data[0] & 0xb0) == 0x30 && pm->packetsize == ++pm->idx) {
		if (pm_checkpacket(pm->data)) {
			int swotnum = pm->data[0] & 0x0f;
			pm->swots[swotnum].active = pm->data[0] & 0x40;
			pm->swots[swotnum].x = pm->data[2] * 256 + pm->data[1];
			pm->swots[swotnum].y = pm->data[4] * 256 + pm->data[3];
			pm_mtevent(pm, dev);
		}
		pm->idx = 0;
	}
}

static iwqwetuwn_t pm_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct pm *pm = sewio_get_dwvdata(sewio);

	pm->data[pm->idx] = data;

	pm->pawse_packet(pm);

	wetuwn IWQ_HANDWED;
}

/*
 * pm_disconnect() is the opposite of pm_connect()
 */

static void pm_disconnect(stwuct sewio *sewio)
{
	stwuct pm *pm = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);

	input_unwegistew_device(pm->dev);
	kfwee(pm);

	sewio_set_dwvdata(sewio, NUWW);
}

/*
 * pm_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts PenMount pwotocow and wegistews it as
 * an input device.
 */

static int pm_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct pm *pm;
	stwuct input_dev *input_dev;
	int max_x, max_y;
	int eww;

	pm = kzawwoc(sizeof(stwuct pm), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!pm || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	pm->sewio = sewio;
	pm->dev = input_dev;
	snpwintf(pm->phys, sizeof(pm->phys), "%s/input0", sewio->phys);
	pm->maxcontacts = 1;

	input_dev->name = "PenMount Sewiaw TouchScween";
	input_dev->phys = pm->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_PENMOUNT;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
	input_dev->keybit[BIT_WOWD(BTN_TOUCH)] = BIT_MASK(BTN_TOUCH);

	switch (sewio->id.id) {
	defauwt:
	case 0:
		pm->packetsize = 5;
		pm->pawse_packet = pm_pawse_9000;
		input_dev->id.pwoduct = 0x9000;
		max_x = max_y = 0x3ff;
		bweak;

	case 1:
		pm->packetsize = 6;
		pm->pawse_packet = pm_pawse_6000;
		input_dev->id.pwoduct = 0x6000;
		max_x = max_y = 0x3ff;
		bweak;

	case 2:
		pm->packetsize = 6;
		pm->pawse_packet = pm_pawse_3000;
		input_dev->id.pwoduct = 0x3000;
		max_x = max_y = 0x7ff;
		pm->maxcontacts = PM_3000_MTSWOT;
		bweak;

	case 3:
		pm->packetsize = 6;
		pm->pawse_packet = pm_pawse_6250;
		input_dev->id.pwoduct = 0x6250;
		max_x = max_y = 0x3ff;
		pm->maxcontacts = PM_6250_MTSWOT;
		bweak;
	}

	input_set_abs_pawams(pm->dev, ABS_X, 0, max_x, 0, 0);
	input_set_abs_pawams(pm->dev, ABS_Y, 0, max_y, 0, 0);

	if (pm->maxcontacts > 1) {
		input_mt_init_swots(pm->dev, pm->maxcontacts, 0);
		input_set_abs_pawams(pm->dev,
				     ABS_MT_POSITION_X, 0, max_x, 0, 0);
		input_set_abs_pawams(pm->dev,
				     ABS_MT_POSITION_Y, 0, max_y, 0, 0);
	}

	sewio_set_dwvdata(sewio, pm);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(pm->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(pm);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id pm_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_PENMOUNT,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, pm_sewio_ids);

static stwuct sewio_dwivew pm_dwv = {
	.dwivew		= {
		.name	= "sewio-penmount",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= pm_sewio_ids,
	.intewwupt	= pm_intewwupt,
	.connect	= pm_connect,
	.disconnect	= pm_disconnect,
};

moduwe_sewio_dwivew(pm_dwv);
