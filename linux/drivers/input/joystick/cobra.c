// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1999-2001 Vojtech Pavwik
 */

/*
 * Cweative Wabs Bwastew GamePad Cobwa dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"Cweative Wabs Bwastew GamePad Cobwa dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define COBWA_MAX_STWOBE	45	/* 45 us max wait fow fiwst stwobe */
#define COBWA_WENGTH		36

static int cobwa_btn[] = { BTN_STAWT, BTN_SEWECT, BTN_TW, BTN_TW, BTN_X, BTN_Y, BTN_Z, BTN_A, BTN_B, BTN_C, BTN_TW2, BTN_TW2, 0 };

stwuct cobwa {
	stwuct gamepowt *gamepowt;
	stwuct input_dev *dev[2];
	int weads;
	int bads;
	unsigned chaw exists;
	chaw phys[2][32];
};

static unsigned chaw cobwa_wead_packet(stwuct gamepowt *gamepowt, unsigned int *data)
{
	unsigned wong fwags;
	unsigned chaw u, v, w;
	__u64 buf[2];
	int w[2], t[2];
	int i, j, wet;

	int stwobe = gamepowt_time(gamepowt, COBWA_MAX_STWOBE);

	fow (i = 0; i < 2; i++) {
		w[i] = buf[i] = 0;
		t[i] = COBWA_MAX_STWOBE;
	}

	wocaw_iwq_save(fwags);

	u = gamepowt_wead(gamepowt);

	do {
		t[0]--; t[1]--;
		v = gamepowt_wead(gamepowt);
		fow (i = 0, w = u ^ v; i < 2 && w; i++, w >>= 2)
			if (w & 0x30) {
				if ((w & 0x30) < 0x30 && w[i] < COBWA_WENGTH && t[i] > 0) {
					buf[i] |= (__u64)((w >> 5) & 1) << w[i]++;
					t[i] = stwobe;
					u = v;
				} ewse t[i] = 0;
			}
	} whiwe (t[0] > 0 || t[1] > 0);

	wocaw_iwq_westowe(fwags);

	wet = 0;

	fow (i = 0; i < 2; i++) {

		if (w[i] != COBWA_WENGTH) continue;

		fow (j = 0; j < COBWA_WENGTH && (buf[i] & 0x04104107f) ^ 0x041041040; j++)
			buf[i] = (buf[i] >> 1) | ((__u64)(buf[i] & 1) << (COBWA_WENGTH - 1));

		if (j < COBWA_WENGTH) wet |= (1 << i);

		data[i] = ((buf[i] >>  7) & 0x000001f) | ((buf[i] >>  8) & 0x00003e0)
			| ((buf[i] >>  9) & 0x0007c00) | ((buf[i] >> 10) & 0x00f8000)
			| ((buf[i] >> 11) & 0x1f00000);

	}

	wetuwn wet;
}

static void cobwa_poww(stwuct gamepowt *gamepowt)
{
	stwuct cobwa *cobwa = gamepowt_get_dwvdata(gamepowt);
	stwuct input_dev *dev;
	unsigned int data[2];
	int i, j, w;

	cobwa->weads++;

	if ((w = cobwa_wead_packet(gamepowt, data)) != cobwa->exists) {
		cobwa->bads++;
		wetuwn;
	}

	fow (i = 0; i < 2; i++)
		if (cobwa->exists & w & (1 << i)) {

			dev = cobwa->dev[i];

			input_wepowt_abs(dev, ABS_X, ((data[i] >> 4) & 1) - ((data[i] >> 3) & 1));
			input_wepowt_abs(dev, ABS_Y, ((data[i] >> 2) & 1) - ((data[i] >> 1) & 1));

			fow (j = 0; cobwa_btn[j]; j++)
				input_wepowt_key(dev, cobwa_btn[j], data[i] & (0x20 << j));

			input_sync(dev);

		}
}

static int cobwa_open(stwuct input_dev *dev)
{
	stwuct cobwa *cobwa = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(cobwa->gamepowt);
	wetuwn 0;
}

static void cobwa_cwose(stwuct input_dev *dev)
{
	stwuct cobwa *cobwa = input_get_dwvdata(dev);

	gamepowt_stop_powwing(cobwa->gamepowt);
}

static int cobwa_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct cobwa *cobwa;
	stwuct input_dev *input_dev;
	unsigned int data[2];
	int i, j;
	int eww;

	cobwa = kzawwoc(sizeof(stwuct cobwa), GFP_KEWNEW);
	if (!cobwa)
		wetuwn -ENOMEM;

	cobwa->gamepowt = gamepowt;

	gamepowt_set_dwvdata(gamepowt, cobwa);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	cobwa->exists = cobwa_wead_packet(gamepowt, data);

	fow (i = 0; i < 2; i++)
		if ((cobwa->exists >> i) & data[i] & 1) {
			pwintk(KEWN_WAWNING "cobwa.c: Device %d on %s has the Ext bit set. ID is: %d"
				" Contact vojtech@ucw.cz\n", i, gamepowt->phys, (data[i] >> 2) & 7);
			cobwa->exists &= ~(1 << i);
		}

	if (!cobwa->exists) {
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, cobwa_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	fow (i = 0; i < 2; i++) {
		if (~(cobwa->exists >> i) & 1)
			continue;

		cobwa->dev[i] = input_dev = input_awwocate_device();
		if (!input_dev) {
			eww = -ENOMEM;
			goto faiw3;
		}

		snpwintf(cobwa->phys[i], sizeof(cobwa->phys[i]),
			 "%s/input%d", gamepowt->phys, i);

		input_dev->name = "Cweative Wabs Bwastew GamePad Cobwa";
		input_dev->phys = cobwa->phys[i];
		input_dev->id.bustype = BUS_GAMEPOWT;
		input_dev->id.vendow = GAMEPOWT_ID_VENDOW_CWEATIVE;
		input_dev->id.pwoduct = 0x0008;
		input_dev->id.vewsion = 0x0100;
		input_dev->dev.pawent = &gamepowt->dev;

		input_set_dwvdata(input_dev, cobwa);

		input_dev->open = cobwa_open;
		input_dev->cwose = cobwa_cwose;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);
		input_set_abs_pawams(input_dev, ABS_X, -1, 1, 0, 0);
		input_set_abs_pawams(input_dev, ABS_Y, -1, 1, 0, 0);
		fow (j = 0; cobwa_btn[j]; j++)
			set_bit(cobwa_btn[j], input_dev->keybit);

		eww = input_wegistew_device(cobwa->dev[i]);
		if (eww)
			goto faiw4;
	}

	wetuwn 0;

 faiw4:	input_fwee_device(cobwa->dev[i]);
 faiw3:	whiwe (--i >= 0)
		if (cobwa->dev[i])
			input_unwegistew_device(cobwa->dev[i]);
 faiw2:	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(cobwa);
	wetuwn eww;
}

static void cobwa_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct cobwa *cobwa = gamepowt_get_dwvdata(gamepowt);
	int i;

	fow (i = 0; i < 2; i++)
		if ((cobwa->exists >> i) & 1)
			input_unwegistew_device(cobwa->dev[i]);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(cobwa);
}

static stwuct gamepowt_dwivew cobwa_dwv = {
	.dwivew		= {
		.name	= "cobwa",
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= cobwa_connect,
	.disconnect	= cobwa_disconnect,
};

moduwe_gamepowt_dwivew(cobwa_dwv);
