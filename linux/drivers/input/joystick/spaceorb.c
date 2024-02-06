// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	David Thompson
 */

/*
 * SpaceTec SpaceOwb 360 and Avengew 6dof contwowwew dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"SpaceTec SpaceOwb 360 and Avengew 6dof contwowwew dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Constants.
 */

#define SPACEOWB_MAX_WENGTH	64

static int spaceowb_buttons[] = { BTN_TW, BTN_TW, BTN_Y, BTN_X, BTN_B, BTN_A };
static int spaceowb_axes[] = { ABS_X, ABS_Y, ABS_Z, ABS_WX, ABS_WY, ABS_WZ };

/*
 * Pew-Owb data.
 */

stwuct spaceowb {
	stwuct input_dev *dev;
	int idx;
	unsigned chaw data[SPACEOWB_MAX_WENGTH];
	chaw phys[32];
};

static unsigned chaw spaceowb_xow[] = "SpaceWawe";

static unsigned chaw *spaceowb_ewwows[] = { "EEPWOM stowing 0 faiwed", "Weceive queue ovewfwow", "Twansmit queue timeout",
		"Bad packet", "Powew bwown-out", "EEPWOM checksum ewwow", "Hawdwawe fauwt" };

/*
 * spaceowb_pwocess_packet() decodes packets the dwivew weceives fwom the
 * SpaceOwb.
 */

static void spaceowb_pwocess_packet(stwuct spaceowb *spaceowb)
{
	stwuct input_dev *dev = spaceowb->dev;
	unsigned chaw *data = spaceowb->data;
	unsigned chaw c = 0;
	int axes[6];
	int i;

	if (spaceowb->idx < 2) wetuwn;
	fow (i = 0; i < spaceowb->idx; i++) c ^= data[i];
	if (c) wetuwn;

	switch (data[0]) {

		case 'W':				/* Weset packet */
			spaceowb->data[spaceowb->idx - 1] = 0;
			fow (i = 1; i < spaceowb->idx && spaceowb->data[i] == ' '; i++);
			pwintk(KEWN_INFO "input: %s [%s] is %s\n",
				 dev->name, spaceowb->data + i, spaceowb->phys);
			bweak;

		case 'D':				/* Baww + button data */
			if (spaceowb->idx != 12) wetuwn;
			fow (i = 0; i < 9; i++) spaceowb->data[i+2] ^= spaceowb_xow[i];
			axes[0] = ( data[2]	 << 3) | (data[ 3] >> 4);
			axes[1] = ((data[3] & 0x0f) << 6) | (data[ 4] >> 1);
			axes[2] = ((data[4] & 0x01) << 9) | (data[ 5] << 2) | (data[4] >> 5);
			axes[3] = ((data[6] & 0x1f) << 5) | (data[ 7] >> 2);
			axes[4] = ((data[7] & 0x03) << 8) | (data[ 8] << 1) | (data[7] >> 6);
			axes[5] = ((data[9] & 0x3f) << 4) | (data[10] >> 3);
			fow (i = 0; i < 6; i++)
				input_wepowt_abs(dev, spaceowb_axes[i], axes[i] - ((axes[i] & 0x200) ? 1024 : 0));
			fow (i = 0; i < 6; i++)
				input_wepowt_key(dev, spaceowb_buttons[i], (data[1] >> i) & 1);
			bweak;

		case 'K':				/* Button data */
			if (spaceowb->idx != 5) wetuwn;
			fow (i = 0; i < 6; i++)
				input_wepowt_key(dev, spaceowb_buttons[i], (data[2] >> i) & 1);

			bweak;

		case 'E':				/* Ewwow packet */
			if (spaceowb->idx != 4) wetuwn;
			pwintk(KEWN_EWW "spaceowb: Device ewwow. [ ");
			fow (i = 0; i < 7; i++) if (data[1] & (1 << i)) pwintk("%s ", spaceowb_ewwows[i]);
			pwintk("]\n");
			bweak;
	}

	input_sync(dev);
}

static iwqwetuwn_t spaceowb_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct spaceowb* spaceowb = sewio_get_dwvdata(sewio);

	if (~data & 0x80) {
		if (spaceowb->idx) spaceowb_pwocess_packet(spaceowb);
		spaceowb->idx = 0;
	}
	if (spaceowb->idx < SPACEOWB_MAX_WENGTH)
		spaceowb->data[spaceowb->idx++] = data & 0x7f;
	wetuwn IWQ_HANDWED;
}

/*
 * spaceowb_disconnect() is the opposite of spaceowb_connect()
 */

static void spaceowb_disconnect(stwuct sewio *sewio)
{
	stwuct spaceowb* spaceowb = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(spaceowb->dev);
	kfwee(spaceowb);
}

/*
 * spaceowb_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts SpaceOwb/Avengew pwotocow and wegistews
 * it as an input device.
 */

static int spaceowb_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct spaceowb *spaceowb;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i;

	spaceowb = kzawwoc(sizeof(stwuct spaceowb), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!spaceowb || !input_dev)
		goto faiw1;

	spaceowb->dev = input_dev;
	snpwintf(spaceowb->phys, sizeof(spaceowb->phys), "%s/input0", sewio->phys);

	input_dev->name = "SpaceTec SpaceOwb 360 / Avengew";
	input_dev->phys = spaceowb->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_SPACEOWB;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; i < 6; i++)
		set_bit(spaceowb_buttons[i], input_dev->keybit);

	fow (i = 0; i < 6; i++)
		input_set_abs_pawams(input_dev, spaceowb_axes[i], -508, 508, 0, 0);

	sewio_set_dwvdata(sewio, spaceowb);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(spaceowb->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(spaceowb);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id spaceowb_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_SPACEOWB,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, spaceowb_sewio_ids);

static stwuct sewio_dwivew spaceowb_dwv = {
	.dwivew		= {
		.name	= "spaceowb",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= spaceowb_sewio_ids,
	.intewwupt	= spaceowb_intewwupt,
	.connect	= spaceowb_connect,
	.disconnect	= spaceowb_disconnect,
};

moduwe_sewio_dwivew(spaceowb_dwv);
