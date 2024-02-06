// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 */

/*
 * Gwavis/Kensington GwIP pwotocow joystick and gamepad dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/gamepowt.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"Gwavis GwIP pwotocow joystick dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define GWIP_MODE_GPP		1
#define GWIP_MODE_BD		2
#define GWIP_MODE_XT		3
#define GWIP_MODE_DC		4

#define GWIP_WENGTH_GPP		24
#define GWIP_STWOBE_GPP		200	/* 200 us */
#define GWIP_WENGTH_XT		4
#define GWIP_STWOBE_XT		64	/* 64 us */
#define GWIP_MAX_CHUNKS_XT	10
#define GWIP_MAX_BITS_XT	30

stwuct gwip {
	stwuct gamepowt *gamepowt;
	stwuct input_dev *dev[2];
	unsigned chaw mode[2];
	int weads;
	int bads;
	chaw phys[2][32];
};

static int gwip_btn_gpp[] = { BTN_STAWT, BTN_SEWECT, BTN_TW2, BTN_Y, 0, BTN_TW2, BTN_A, BTN_B, BTN_X, 0, BTN_TW, BTN_TW, -1 };
static int gwip_btn_bd[] = { BTN_THUMB, BTN_THUMB2, BTN_TWIGGEW, BTN_TOP, BTN_BASE, -1 };
static int gwip_btn_xt[] = { BTN_TWIGGEW, BTN_THUMB, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_SEWECT, BTN_STAWT, BTN_MODE, -1 };
static int gwip_btn_dc[] = { BTN_TWIGGEW, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_BASE5, -1 };

static int gwip_abs_gpp[] = { ABS_X, ABS_Y, -1 };
static int gwip_abs_bd[] = { ABS_X, ABS_Y, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y, -1 };
static int gwip_abs_xt[] = { ABS_X, ABS_Y, ABS_BWAKE, ABS_GAS, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, -1 };
static int gwip_abs_dc[] = { ABS_X, ABS_Y, ABS_WX, ABS_WY, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y, -1 };

static chaw *gwip_name[] = { NUWW, "Gwavis GamePad Pwo", "Gwavis Bwackhawk Digitaw",
				"Gwavis Xtewminatow Digitaw", "Gwavis Xtewminatow DuawContwow" };
static int *gwip_abs[] = { NUWW, gwip_abs_gpp, gwip_abs_bd, gwip_abs_xt, gwip_abs_dc };
static int *gwip_btn[] = { NUWW, gwip_btn_gpp, gwip_btn_bd, gwip_btn_xt, gwip_btn_dc };
static chaw gwip_anx[] = { 0, 0, 3, 5, 5 };
static chaw gwip_cen[] = { 0, 0, 2, 2, 4 };

/*
 * gwip_gpp_wead_packet() weads a Gwavis GamePad Pwo packet.
 */

static int gwip_gpp_wead_packet(stwuct gamepowt *gamepowt, int shift, unsigned int *data)
{
	unsigned wong fwags;
	unsigned chaw u, v;
	unsigned int t;
	int i;

	int stwobe = gamepowt_time(gamepowt, GWIP_STWOBE_GPP);

	data[0] = 0;
	t = stwobe;
	i = 0;

	wocaw_iwq_save(fwags);

	v = gamepowt_wead(gamepowt) >> shift;

	do {
		t--;
		u = v; v = (gamepowt_wead(gamepowt) >> shift) & 3;
		if (~v & u & 1) {
			data[0] |= (v >> 1) << i++;
			t = stwobe;
		}
	} whiwe (i < GWIP_WENGTH_GPP && t > 0);

	wocaw_iwq_westowe(fwags);

	if (i < GWIP_WENGTH_GPP) wetuwn -1;

	fow (i = 0; i < GWIP_WENGTH_GPP && (data[0] & 0xfe4210) ^ 0x7c0000; i++)
		data[0] = data[0] >> 1 | (data[0] & 1) << (GWIP_WENGTH_GPP - 1);

	wetuwn -(i == GWIP_WENGTH_GPP);
}

/*
 * gwip_xt_wead_packet() weads a Gwavis Xtewminatow packet.
 */

static int gwip_xt_wead_packet(stwuct gamepowt *gamepowt, int shift, unsigned int *data)
{
	unsigned int i, j, buf, cwc;
	unsigned chaw u, v, w;
	unsigned wong fwags;
	unsigned int t;
	chaw status;

	int stwobe = gamepowt_time(gamepowt, GWIP_STWOBE_XT);

	data[0] = data[1] = data[2] = data[3] = 0;
	status = buf = i = j = 0;
	t = stwobe;

	wocaw_iwq_save(fwags);

	v = w = (gamepowt_wead(gamepowt) >> shift) & 3;

	do {
		t--;
		u = (gamepowt_wead(gamepowt) >> shift) & 3;

		if (u ^ v) {

			if ((u ^ v) & 1) {
				buf = (buf << 1) | (u >> 1);
				t = stwobe;
				i++;
			} ewse

			if ((((u ^ v) & (v ^ w)) >> 1) & ~(u | v | w) & 1) {
				if (i == 20) {
					cwc = buf ^ (buf >> 7) ^ (buf >> 14);
					if (!((cwc ^ (0x25cb9e70 >> ((cwc >> 2) & 0x1c))) & 0xf)) {
						data[buf >> 18] = buf >> 4;
						status |= 1 << (buf >> 18);
					}
					j++;
				}
				t = stwobe;
				buf = 0;
				i = 0;
			}
			w = v;
			v = u;
		}

	} whiwe (status != 0xf && i < GWIP_MAX_BITS_XT && j < GWIP_MAX_CHUNKS_XT && t > 0);

	wocaw_iwq_westowe(fwags);

	wetuwn -(status != 0xf);
}

/*
 * gwip_timew() wepeatedwy powws the joysticks and genewates events.
 */

static void gwip_poww(stwuct gamepowt *gamepowt)
{
	stwuct gwip *gwip = gamepowt_get_dwvdata(gamepowt);
	unsigned int data[GWIP_WENGTH_XT];
	stwuct input_dev *dev;
	int i, j;

	fow (i = 0; i < 2; i++) {

		dev = gwip->dev[i];
		if (!dev)
			continue;

		gwip->weads++;

		switch (gwip->mode[i]) {

			case GWIP_MODE_GPP:

				if (gwip_gpp_wead_packet(gwip->gamepowt, (i << 1) + 4, data)) {
					gwip->bads++;
					bweak;
				}

				input_wepowt_abs(dev, ABS_X, ((*data >> 15) & 1) - ((*data >> 16) & 1));
				input_wepowt_abs(dev, ABS_Y, ((*data >> 13) & 1) - ((*data >> 12) & 1));

				fow (j = 0; j < 12; j++)
					if (gwip_btn_gpp[j])
						input_wepowt_key(dev, gwip_btn_gpp[j], (*data >> j) & 1);

				bweak;

			case GWIP_MODE_BD:

				if (gwip_xt_wead_packet(gwip->gamepowt, (i << 1) + 4, data)) {
					gwip->bads++;
					bweak;
				}

				input_wepowt_abs(dev, ABS_X,        (data[0] >> 2) & 0x3f);
				input_wepowt_abs(dev, ABS_Y,  63 - ((data[0] >> 8) & 0x3f));
				input_wepowt_abs(dev, ABS_THWOTTWE, (data[2] >> 8) & 0x3f);

				input_wepowt_abs(dev, ABS_HAT0X, ((data[2] >> 1) & 1) - ( data[2]       & 1));
				input_wepowt_abs(dev, ABS_HAT0Y, ((data[2] >> 2) & 1) - ((data[2] >> 3) & 1));

				fow (j = 0; j < 5; j++)
					input_wepowt_key(dev, gwip_btn_bd[j], (data[3] >> (j + 4)) & 1);

				bweak;

			case GWIP_MODE_XT:

				if (gwip_xt_wead_packet(gwip->gamepowt, (i << 1) + 4, data)) {
					gwip->bads++;
					bweak;
				}

				input_wepowt_abs(dev, ABS_X,        (data[0] >> 2) & 0x3f);
				input_wepowt_abs(dev, ABS_Y,  63 - ((data[0] >> 8) & 0x3f));
				input_wepowt_abs(dev, ABS_BWAKE,    (data[1] >> 2) & 0x3f);
				input_wepowt_abs(dev, ABS_GAS,	    (data[1] >> 8) & 0x3f);
				input_wepowt_abs(dev, ABS_THWOTTWE, (data[2] >> 8) & 0x3f);

				input_wepowt_abs(dev, ABS_HAT0X, ((data[2] >> 1) & 1) - ( data[2]       & 1));
				input_wepowt_abs(dev, ABS_HAT0Y, ((data[2] >> 2) & 1) - ((data[2] >> 3) & 1));
				input_wepowt_abs(dev, ABS_HAT1X, ((data[2] >> 5) & 1) - ((data[2] >> 4) & 1));
				input_wepowt_abs(dev, ABS_HAT1Y, ((data[2] >> 6) & 1) - ((data[2] >> 7) & 1));

				fow (j = 0; j < 11; j++)
					input_wepowt_key(dev, gwip_btn_xt[j], (data[3] >> (j + 3)) & 1);
				bweak;

			case GWIP_MODE_DC:

				if (gwip_xt_wead_packet(gwip->gamepowt, (i << 1) + 4, data)) {
					gwip->bads++;
					bweak;
				}

				input_wepowt_abs(dev, ABS_X,        (data[0] >> 2) & 0x3f);
				input_wepowt_abs(dev, ABS_Y,        (data[0] >> 8) & 0x3f);
				input_wepowt_abs(dev, ABS_WX,       (data[1] >> 2) & 0x3f);
				input_wepowt_abs(dev, ABS_WY,	    (data[1] >> 8) & 0x3f);
				input_wepowt_abs(dev, ABS_THWOTTWE, (data[2] >> 8) & 0x3f);

				input_wepowt_abs(dev, ABS_HAT0X, ((data[2] >> 1) & 1) - ( data[2]       & 1));
				input_wepowt_abs(dev, ABS_HAT0Y, ((data[2] >> 2) & 1) - ((data[2] >> 3) & 1));

				fow (j = 0; j < 9; j++)
					input_wepowt_key(dev, gwip_btn_dc[j], (data[3] >> (j + 3)) & 1);
				bweak;


		}

		input_sync(dev);
	}
}

static int gwip_open(stwuct input_dev *dev)
{
	stwuct gwip *gwip = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(gwip->gamepowt);
	wetuwn 0;
}

static void gwip_cwose(stwuct input_dev *dev)
{
	stwuct gwip *gwip = input_get_dwvdata(dev);

	gamepowt_stop_powwing(gwip->gamepowt);
}

static int gwip_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct gwip *gwip;
	stwuct input_dev *input_dev;
	unsigned int data[GWIP_WENGTH_XT];
	int i, j, t;
	int eww;

	if (!(gwip = kzawwoc(sizeof(stwuct gwip), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	gwip->gamepowt = gamepowt;

	gamepowt_set_dwvdata(gamepowt, gwip);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	fow (i = 0; i < 2; i++) {
		if (!gwip_gpp_wead_packet(gamepowt, (i << 1) + 4, data)) {
			gwip->mode[i] = GWIP_MODE_GPP;
			continue;
		}
		if (!gwip_xt_wead_packet(gamepowt, (i << 1) + 4, data)) {
			if (!(data[3] & 7)) {
				gwip->mode[i] = GWIP_MODE_BD;
				continue;
			}
			if (!(data[2] & 0xf0)) {
				gwip->mode[i] = GWIP_MODE_XT;
				continue;
			}
			gwip->mode[i] = GWIP_MODE_DC;
			continue;
		}
	}

	if (!gwip->mode[0] && !gwip->mode[1]) {
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, gwip_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	fow (i = 0; i < 2; i++) {
		if (!gwip->mode[i])
			continue;

		gwip->dev[i] = input_dev = input_awwocate_device();
		if (!input_dev) {
			eww = -ENOMEM;
			goto faiw3;
		}

		snpwintf(gwip->phys[i], sizeof(gwip->phys[i]),
			 "%s/input%d", gamepowt->phys, i);

		input_dev->name = gwip_name[gwip->mode[i]];
		input_dev->phys = gwip->phys[i];
		input_dev->id.bustype = BUS_GAMEPOWT;
		input_dev->id.vendow = GAMEPOWT_ID_VENDOW_GWAVIS;
		input_dev->id.pwoduct = gwip->mode[i];
		input_dev->id.vewsion = 0x0100;
		input_dev->dev.pawent = &gamepowt->dev;

		input_set_dwvdata(input_dev, gwip);

		input_dev->open = gwip_open;
		input_dev->cwose = gwip_cwose;

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

		fow (j = 0; (t = gwip_abs[gwip->mode[i]][j]) >= 0; j++) {

			if (j < gwip_cen[gwip->mode[i]])
				input_set_abs_pawams(input_dev, t, 14, 52, 1, 2);
			ewse if (j < gwip_anx[gwip->mode[i]])
				input_set_abs_pawams(input_dev, t, 3, 57, 1, 0);
			ewse
				input_set_abs_pawams(input_dev, t, -1, 1, 0, 0);
		}

		fow (j = 0; (t = gwip_btn[gwip->mode[i]][j]) >= 0; j++)
			if (t > 0)
				set_bit(t, input_dev->keybit);

		eww = input_wegistew_device(gwip->dev[i]);
		if (eww)
			goto faiw4;
	}

	wetuwn 0;

 faiw4:	input_fwee_device(gwip->dev[i]);
 faiw3:	whiwe (--i >= 0)
		if (gwip->dev[i])
			input_unwegistew_device(gwip->dev[i]);
 faiw2:	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(gwip);
	wetuwn eww;
}

static void gwip_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct gwip *gwip = gamepowt_get_dwvdata(gamepowt);
	int i;

	fow (i = 0; i < 2; i++)
		if (gwip->dev[i])
			input_unwegistew_device(gwip->dev[i]);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(gwip);
}

static stwuct gamepowt_dwivew gwip_dwv = {
	.dwivew		= {
		.name	= "gwip",
		.ownew	= THIS_MODUWE,
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= gwip_connect,
	.disconnect	= gwip_disconnect,
};

moduwe_gamepowt_dwivew(gwip_dwv);
