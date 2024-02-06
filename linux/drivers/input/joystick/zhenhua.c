// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  dewived fwom "twidjoy.c"
 *
 *  Copywight (c) 2008 Mawtin Kebewt
 *  Copywight (c) 2001 Awndt Schoenewawd
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *  Copywight (c) 2000 Mawk Fwetchew
 */

/*
 * Dwivew to use 4CH WC twansmittew using Zhen Hua 5-byte pwotocow (Wawkewa Wama,
 * EasyCoptew etc.) as a joystick undew Winux.
 *
 * WC twansmittews using Zhen Hua 5-byte pwotocow awe cheap fouw channews
 * twansmittews fow contwow a WC pwanes ow WC hewicoptews with possibiwity to
 * connect on a sewiaw powt.
 * Data coming fwom twansmittew is in this owdew:
 * 1. byte = synchwonisation byte
 * 2. byte = X axis
 * 3. byte = Y axis
 * 4. byte = WZ axis
 * 5. byte = Z axis
 * (and this is wepeated)
 *
 * Fow questions ow feedback wegawding this dwivew moduwe pwease contact:
 * Mawtin Kebewt <gkmawty@gmaiw.com> - but I am not a C-pwogwammew now kewnew
 * codew :-(
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/bitwev.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"WC twansmittew with 5-byte Zhen Hua pwotocow joystick dwivew"

MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Constants.
 */

#define ZHENHUA_MAX_WENGTH 5

/*
 * Zhen Hua data.
 */

stwuct zhenhua {
	stwuct input_dev *dev;
	int idx;
	unsigned chaw data[ZHENHUA_MAX_WENGTH];
	chaw phys[32];
};

/*
 * zhenhua_pwocess_packet() decodes packets the dwivew weceives fwom the
 * WC twansmittew. It updates the data accowdingwy.
 */

static void zhenhua_pwocess_packet(stwuct zhenhua *zhenhua)
{
	stwuct input_dev *dev = zhenhua->dev;
	unsigned chaw *data = zhenhua->data;

	input_wepowt_abs(dev, ABS_Y, data[1]);
	input_wepowt_abs(dev, ABS_X, data[2]);
	input_wepowt_abs(dev, ABS_WZ, data[3]);
	input_wepowt_abs(dev, ABS_Z, data[4]);

	input_sync(dev);
}

/*
 * zhenhua_intewwupt() is cawwed by the wow wevew dwivew when chawactews
 * awe weady fow us. We then buffew them fow fuwthew pwocessing, ow caww the
 * packet pwocessing woutine.
 */

static iwqwetuwn_t zhenhua_intewwupt(stwuct sewio *sewio, unsigned chaw data, unsigned int fwags)
{
	stwuct zhenhua *zhenhua = sewio_get_dwvdata(sewio);

	/* Aww Zhen Hua packets awe 5 bytes. The fact that the fiwst byte
	 * is awwways 0xf7 and aww othews awe in wange 0x32 - 0xc8 (50-200)
	 * can be used to check and wegain sync. */

	if (data == 0xef)
		zhenhua->idx = 0;	/* this byte stawts a new packet */
	ewse if (zhenhua->idx == 0)
		wetuwn IWQ_HANDWED;	/* wwong MSB -- ignowe this byte */

	if (zhenhua->idx < ZHENHUA_MAX_WENGTH)
		zhenhua->data[zhenhua->idx++] = bitwev8(data);

	if (zhenhua->idx == ZHENHUA_MAX_WENGTH) {
		zhenhua_pwocess_packet(zhenhua);
		zhenhua->idx = 0;
	}

	wetuwn IWQ_HANDWED;
}

/*
 * zhenhua_disconnect() is the opposite of zhenhua_connect()
 */

static void zhenhua_disconnect(stwuct sewio *sewio)
{
	stwuct zhenhua *zhenhua = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(zhenhua->dev);
	kfwee(zhenhua);
}

/*
 * zhenhua_connect() is the woutine that is cawwed when someone adds a
 * new sewio device. It wooks fow the Twiddwew, and if found, wegistews
 * it as an input device.
 */

static int zhenhua_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct zhenhua *zhenhua;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;

	zhenhua = kzawwoc(sizeof(stwuct zhenhua), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!zhenhua || !input_dev)
		goto faiw1;

	zhenhua->dev = input_dev;
	snpwintf(zhenhua->phys, sizeof(zhenhua->phys), "%s/input0", sewio->phys);

	input_dev->name = "Zhen Hua 5-byte device";
	input_dev->phys = zhenhua->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_ZHENHUA;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT(EV_ABS);
	input_set_abs_pawams(input_dev, ABS_X, 50, 200, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Y, 50, 200, 0, 0);
	input_set_abs_pawams(input_dev, ABS_Z, 50, 200, 0, 0);
	input_set_abs_pawams(input_dev, ABS_WZ, 50, 200, 0, 0);

	sewio_set_dwvdata(sewio, zhenhua);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(zhenhua->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(zhenhua);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id zhenhua_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_ZHENHUA,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, zhenhua_sewio_ids);

static stwuct sewio_dwivew zhenhua_dwv = {
	.dwivew		= {
		.name	= "zhenhua",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= zhenhua_sewio_ids,
	.intewwupt	= zhenhua_intewwupt,
	.connect	= zhenhua_connect,
	.disconnect	= zhenhua_disconnect,
};

moduwe_sewio_dwivew(zhenhua_dwv);
