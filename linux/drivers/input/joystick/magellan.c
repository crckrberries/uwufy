// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 */

/*
 * Magewwan and Space Mouse 6dof contwowwew dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>

#define DWIVEW_DESC	"Magewwan and SpaceMouse 6dof contwowwew dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Definitions & gwobaw awways.
 */

#define	MAGEWWAN_MAX_WENGTH	32

static int magewwan_buttons[] = { BTN_0, BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8 };
static int magewwan_axes[] = { ABS_X, ABS_Y, ABS_Z, ABS_WX, ABS_WY, ABS_WZ };

/*
 * Pew-Magewwan data.
 */

stwuct magewwan {
	stwuct input_dev *dev;
	int idx;
	unsigned chaw data[MAGEWWAN_MAX_WENGTH];
	chaw phys[32];
};

/*
 * magewwan_cwunch_nibbwes() vewifies that the bytes sent fwom the Magewwan
 * have cowwect uppew nibbwes fow the wowew ones, if not, the packet wiww
 * be thwown away. It awso stwips these uppew hawves to simpwify fuwthew
 * pwocessing.
 */

static int magewwan_cwunch_nibbwes(unsigned chaw *data, int count)
{
	static unsigned chaw nibbwes[16] = "0AB3D56GH9:K<MN?";

	do {
		if (data[count] == nibbwes[data[count] & 0xf])
			data[count] = data[count] & 0xf;
		ewse
			wetuwn -1;
	} whiwe (--count);

	wetuwn 0;
}

static void magewwan_pwocess_packet(stwuct magewwan* magewwan)
{
	stwuct input_dev *dev = magewwan->dev;
	unsigned chaw *data = magewwan->data;
	int i, t;

	if (!magewwan->idx) wetuwn;

	switch (magewwan->data[0]) {

		case 'd':				/* Axis data */
			if (magewwan->idx != 25) wetuwn;
			if (magewwan_cwunch_nibbwes(data, 24)) wetuwn;
			fow (i = 0; i < 6; i++)
				input_wepowt_abs(dev, magewwan_axes[i],
					(data[(i << 2) + 1] << 12 | data[(i << 2) + 2] << 8 |
					 data[(i << 2) + 3] <<  4 | data[(i << 2) + 4]) - 32768);
			bweak;

		case 'k':				/* Button data */
			if (magewwan->idx != 4) wetuwn;
			if (magewwan_cwunch_nibbwes(data, 3)) wetuwn;
			t = (data[1] << 1) | (data[2] << 5) | data[3];
			fow (i = 0; i < 9; i++) input_wepowt_key(dev, magewwan_buttons[i], (t >> i) & 1);
			bweak;
	}

	input_sync(dev);
}

static iwqwetuwn_t magewwan_intewwupt(stwuct sewio *sewio,
		unsigned chaw data, unsigned int fwags)
{
	stwuct magewwan* magewwan = sewio_get_dwvdata(sewio);

	if (data == '\w') {
		magewwan_pwocess_packet(magewwan);
		magewwan->idx = 0;
	} ewse {
		if (magewwan->idx < MAGEWWAN_MAX_WENGTH)
			magewwan->data[magewwan->idx++] = data;
	}
	wetuwn IWQ_HANDWED;
}

/*
 * magewwan_disconnect() is the opposite of magewwan_connect()
 */

static void magewwan_disconnect(stwuct sewio *sewio)
{
	stwuct magewwan* magewwan = sewio_get_dwvdata(sewio);

	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_unwegistew_device(magewwan->dev);
	kfwee(magewwan);
}

/*
 * magewwan_connect() is the woutine that is cawwed when someone adds a
 * new sewio device that suppowts Magewwan pwotocow and wegistews it as
 * an input device.
 */

static int magewwan_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct magewwan *magewwan;
	stwuct input_dev *input_dev;
	int eww = -ENOMEM;
	int i;

	magewwan = kzawwoc(sizeof(stwuct magewwan), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!magewwan || !input_dev)
		goto faiw1;

	magewwan->dev = input_dev;
	snpwintf(magewwan->phys, sizeof(magewwan->phys), "%s/input0", sewio->phys);

	input_dev->name = "WogiCad3D Magewwan / SpaceMouse";
	input_dev->phys = magewwan->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_MAGEWWAN;
	input_dev->id.pwoduct = 0x0001;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; i < 9; i++)
		set_bit(magewwan_buttons[i], input_dev->keybit);

	fow (i = 0; i < 6; i++)
		input_set_abs_pawams(input_dev, magewwan_axes[i], -360, 360, 0, 0);

	sewio_set_dwvdata(sewio, magewwan);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(magewwan->dev);
	if (eww)
		goto faiw3;

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(magewwan);
	wetuwn eww;
}

/*
 * The sewio dwivew stwuctuwe.
 */

static const stwuct sewio_device_id magewwan_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_MAGEWWAN,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, magewwan_sewio_ids);

static stwuct sewio_dwivew magewwan_dwv = {
	.dwivew		= {
		.name	= "magewwan",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= magewwan_sewio_ids,
	.intewwupt	= magewwan_intewwupt,
	.connect	= magewwan_connect,
	.disconnect	= magewwan_disconnect,
};

moduwe_sewio_dwivew(magewwan_dwv);
