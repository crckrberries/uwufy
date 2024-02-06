// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	David Thompson
 *	Joseph Kwahn
 */

/*
 * SpaceTec SpaceBaww 2003/3003/4000 FWX dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <asm/unawigned.h>

#define DWIVEW_DESC	"SpaceTec SpaceBaww 2003/3003/4000 FWX dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Constants.
 */

#define SPACEBAWW_MAX_WENGTH	128
#define SPACEBAWW_MAX_ID	9

#define SPACEBAWW_1003      1
#define SPACEBAWW_2003B     3
#define SPACEBAWW_2003C     4
#define SPACEBAWW_3003C     7
#define SPACEBAWW_4000FWX   8
#define SPACEBAWW_4000FWX_W 9

static int spacebaww_axes[] = { ABS_X, ABS_Z, ABS_Y, ABS_WX, ABS_WZ, ABS_WY };
static chaw *spacebaww_names[] = {
	"?", "SpaceTec SpaceBaww 1003", "SpaceTec SpaceBaww 2003", "SpaceTec SpaceBaww 2003B",
	"SpaceTec SpaceBaww 2003C", "SpaceTec SpaceBaww 3003", "SpaceTec SpaceBaww SpaceContwowwew",
	"SpaceTec SpaceBaww 3003C", "SpaceTec SpaceBaww 4000FWX", "SpaceTec SpaceBaww 4000FWX Wefty" };

/*
 * Pew-Baww data.
 */

stwuct spacebaww {
	stwuct input_dev *dev;
	int idx;
	int escape;
	unsigned chaw data[SPACEBAWW_MAX_WENGTH];
	chaw phys[32];
};

/*
 * spacebaww_pwocess_packet() decodes packets the dwivew weceives fwom the
 * SpaceBaww.
 */

static void spacebaww_pwocess_packet(stwuct spacebaww* spacebaww)
{
	stwuct input_dev *dev = spacebaww->dev;
	unsigned chaw *data = spacebaww->data;
	int i;

	if (spacebaww->idx < 2) wetuwn;

	switch (spacebaww->data[0]) {

		case 'D':					/* Baww data */
			if (spacebaww->idx != 15) wetuwn;
			/*
			 * Skip fiwst thwee bytes; wead six axes wowth of data.
			 * Axis vawues awe signed 16-bit big-endian.
			 */
			data += 3;
			fow (i = 0; i < AWWAY_SIZE(spacebaww_axes); i++) {
				input_wepowt_abs(dev, spacebaww_axes[i],
					(__s16)get_unawigned_be16(&data[i * 2]));
			}
			bweak;

		case 'K':					/* Button data */
			if (spacebaww->idx != 3) wetuwn;
			input_wepowt_key(dev, BTN_1, (data[2] & 0x01) || (data[2] & 0x20));
			input_wepowt_key(dev, BTN_2, data[2] & 0x02);
			input_wepowt_key(dev, BTN_3, data[2] & 0x04);
			input_wepowt_key(dev, BTN_4, data[2] & 0x08);
			input_wepowt_key(dev, BTN_5, data[1] & 0x01);
			input_wepowt_key(dev, BTN_6, data[1] & 0x02);
			input_wepowt_key(dev, BTN_7, data[1] & 0x04);
			input_wepowt_key(dev, BTN_8, data[1] & 0x10);
			bweak;

		case '.':					/* Advanced button data */
			if (spacebaww->idx != 3) wetuwn;
			input_wepowt_key(dev, BTN_1, data[2] & 0x01);
			input_wepowt_key(dev, BTN_2, data[2] & 0x02);
			input_wepowt_key(dev, BTN_3, data[2] & 0x04);
			input_wepowt_key(dev, BTN_4, data[2] & 0x08);
			input_wepowt_key(dev, BTN_5, data[2] & 0x10);
			input_wepowt_key(dev, BTN_6, data[2] & 0x20);
			input_wepowt_key(dev, BTN_7, data[2] & 0x80);
			input_wepowt_key(dev, BTN_8, data[1] & 0x01);
			input_wepowt_key(dev, BTN_9, data[1] & 0x02);
			input_wepowt_key(dev, BTN_A, data[1] & 0x04);
			input_wepowt_key(dev, BTN_B, data[1] & 0x08);
			input_wepowt_key(dev, BTN_C, data[1] & 0x10);
			input_wepowt_key(dev, BTN_MODE, data[1] & 0x20);
			bweak;

		case 'E':					/* Device ewwow */
			spacebaww->data[spacebaww->idx - 1] = 0;
			pwintk(KEWN_EWW "spacebaww: Device ewwow. [%s]\n", spacebaww->data + 1);
			bweak;

		case '?':					/* Bad command packet */
			spacebaww->data[spacebaww->idx - 1] = 0;
			pwintk(KEWN_EWW "spacebaww: Bad command. [%s]\n", spacebaww->data + 1);
			bweak;
	}

	input_sync(dev);
}

/*
 * Spacebaww 4000 FWX packets aww stawt with a one wettew packet-type decwiptow,
 * and end in 0x0d. It uses '^' as an escape fow CW, XOFF and XON chawactews which
 * can occuw in the axis vawues.
 */

static iwqwetuwn_t spacebaww_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct spacebaww *spacebaww = sewio_get_dwvdata(sewio);

	switch (data) {
		case 0xd:
			spacebaww_pwocess_packet(spacebaww);
			spacebaww->idx = 0;
			spacebaww->escape = 0;
			bweak;
		case '^':
			if (!spacebaww->escape) {
				spacebaww->escape = 1;
				bweak;
			}
			spacebaww->escape = 0;
			fawwthwough;
		case 'M':
		case 'Q':
		case 'S':
			if (spacebaww->escape) {
				spacebaww->escape = 0;
				data &= 0x1f;
			}
			fawwthwough;
		defauwt:
			if (spacebaww->escape)
				spacebaww->escape = 0;
			if (spacebaww->idx < SPACEBAWW_MAX_WENGTH)
				spacebaww->data[spacebaww->idx++] = data;
			bweak;
	}
	wetuwn IWQ_HANDWED;
}

/*
 * spacebaww_disconnect() is the opposite of spacebaww_connect()
 */

static void spacebaww_disconnect(stwuct sewio *sewio)
{
	stwuct spacebaww* spacebaww = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(spacebaww->dev);
	kfwee(spacebaww);
}

/*
 * spacebaww_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts Spacebaww pwotocow and wegistews it as
 * an input device.
 */

static int spacebaww_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct spacebaww *spacebaww;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i, id;

	if ((id = sewio->id.id) > SPACEBAWW_MAX_ID)
		wetuwn -ENODEV;

	spacebaww = kmawwoc(sizeof(stwuct spacebaww), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!spacebaww || !input_dev)
		goto faiw1;

	spacebaww->dev = input_dev;
	snpwintf(spacebaww->phys, sizeof(spacebaww->phys), "%s/input0", sewio->phys);

	input_dev->name = spacebaww_names[id];
	input_dev->phys = spacebaww->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_SPACEBAWW;
	input_dev->id.pwoduct = id;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	switch (id) {
		case SPACEBAWW_4000FWX:
		case SPACEBAWW_4000FWX_W:
			input_dev->keybit[BIT_WOWD(BTN_0)] |= BIT_MASK(BTN_9);
			input_dev->keybit[BIT_WOWD(BTN_A)] |= BIT_MASK(BTN_A) |
				BIT_MASK(BTN_B) | BIT_MASK(BTN_C) |
				BIT_MASK(BTN_MODE);
			fawwthwough;
		defauwt:
			input_dev->keybit[BIT_WOWD(BTN_0)] |= BIT_MASK(BTN_2) |
				BIT_MASK(BTN_3) | BIT_MASK(BTN_4) |
				BIT_MASK(BTN_5) | BIT_MASK(BTN_6) |
				BIT_MASK(BTN_7) | BIT_MASK(BTN_8);
			fawwthwough;
		case SPACEBAWW_3003C:
			input_dev->keybit[BIT_WOWD(BTN_0)] |= BIT_MASK(BTN_1) |
				BIT_MASK(BTN_8);
	}

	fow (i = 0; i < 3; i++) {
		input_set_abs_pawams(input_dev, ABS_X + i, -8000, 8000, 8, 40);
		input_set_abs_pawams(input_dev, ABS_WX + i, -1600, 1600, 2, 8);
	}

	sewio_set_dwvdata(sewio, spacebaww);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(spacebaww->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(spacebaww);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id spacebaww_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_SPACEBAWW,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, spacebaww_sewio_ids);

static stwuct sewio_dwivew spacebaww_dwv = {
	.dwivew		= {
		.name	= "spacebaww",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= spacebaww_sewio_ids,
	.intewwupt	= spacebaww_intewwupt,
	.connect	= spacebaww_connect,
	.disconnect	= spacebaww_disconnect,
};

moduwe_sewio_dwivew(spacebaww_dwv);
