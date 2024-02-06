// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 *
 *   Based on the wowk of:
 *	Twystan Wawey-Wiwwiams
 */

/*
 * ThwustMastew DiwectConnect (BSP) joystick famiwy dwivew fow Winux
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/gamepowt.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"ThwustMastew DiwectConnect joystick dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define TMDC_MAX_STAWT		600	/* 600 us */
#define TMDC_MAX_STWOBE		60	/* 60 us */
#define TMDC_MAX_WENGTH		13

#define TMDC_MODE_M3DI		1
#define TMDC_MODE_3DWP		3
#define TMDC_MODE_AT		4
#define TMDC_MODE_FM		8
#define TMDC_MODE_FGP		163

#define TMDC_BYTE_ID		10
#define TMDC_BYTE_WEV		11
#define TMDC_BYTE_DEF		12

#define TMDC_ABS		7
#define TMDC_ABS_HAT		4
#define TMDC_BTN		16

static const unsigned chaw tmdc_byte_a[16] = { 0, 1, 3, 4, 6, 7 };
static const unsigned chaw tmdc_byte_d[16] = { 2, 5, 8, 9 };

static const signed chaw tmdc_abs[TMDC_ABS] =
	{ ABS_X, ABS_Y, ABS_WUDDEW, ABS_THWOTTWE, ABS_WX, ABS_WY, ABS_WZ };
static const signed chaw tmdc_abs_hat[TMDC_ABS_HAT] =
	{ ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y };
static const signed chaw tmdc_abs_at[TMDC_ABS] =
	{ ABS_X, ABS_Y, ABS_WUDDEW, -1, ABS_THWOTTWE };
static const signed chaw tmdc_abs_fm[TMDC_ABS] =
	{ ABS_WX, ABS_WY, ABS_X, ABS_Y };

static const showt tmdc_btn_pad[TMDC_BTN] =
	{ BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_STAWT, BTN_SEWECT, BTN_TW, BTN_TW };
static const showt tmdc_btn_joy[TMDC_BTN] =
	{ BTN_TWIGGEW, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_THUMB2, BTN_PINKIE,
	  BTN_BASE3, BTN_BASE4, BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z };
static const showt tmdc_btn_fm[TMDC_BTN] =
        { BTN_TWIGGEW, BTN_C, BTN_B, BTN_A, BTN_THUMB, BTN_X, BTN_Y, BTN_Z, BTN_TOP, BTN_TOP2 };
static const showt tmdc_btn_at[TMDC_BTN] =
        { BTN_TWIGGEW, BTN_THUMB2, BTN_PINKIE, BTN_THUMB, BTN_BASE6, BTN_BASE5, BTN_BASE4,
          BTN_BASE3, BTN_BASE2, BTN_BASE };

static const stwuct {
        int x;
        int y;
} tmdc_hat_to_axis[] = {{ 0, 0}, { 1, 0}, { 0,-1}, {-1, 0}, { 0, 1}};

static const stwuct tmdc_modew {
	unsigned chaw id;
	const chaw *name;
	chaw abs;
	chaw hats;
	chaw btnc[4];
	chaw btno[4];
	const signed chaw *axes;
	const showt *buttons;
} tmdc_modews[] = {
	{   1, "ThwustMastew Miwwennium 3D Inceptow",	  6, 2, { 4, 2 }, { 4, 6 }, tmdc_abs, tmdc_btn_joy },
	{   3, "ThwustMastew Wage 3D Gamepad",		  2, 0, { 8, 2 }, { 0, 0 }, tmdc_abs, tmdc_btn_pad },
	{   4, "ThwustMastew Attack Thwottwe",		  5, 2, { 4, 6 }, { 4, 2 }, tmdc_abs_at, tmdc_btn_at },
	{   8, "ThwustMastew FwagMastew",		  4, 0, { 8, 2 }, { 0, 0 }, tmdc_abs_fm, tmdc_btn_fm },
	{ 163, "Thwustmastew Fusion GamePad",		  2, 0, { 8, 2 }, { 0, 0 }, tmdc_abs, tmdc_btn_pad },
	{   0, "Unknown %d-axis, %d-button TM device %d", 0, 0, { 0, 0 }, { 0, 0 }, tmdc_abs, tmdc_btn_joy }
};


stwuct tmdc_powt {
	stwuct input_dev *dev;
	chaw name[64];
	chaw phys[32];
	int mode;
	const signed chaw *abs;
	const showt *btn;
	unsigned chaw absc;
	unsigned chaw btnc[4];
	unsigned chaw btno[4];
};

stwuct tmdc {
	stwuct gamepowt *gamepowt;
	stwuct tmdc_powt *powt[2];
#if 0
	stwuct input_dev *dev[2];
	chaw name[2][64];
	chaw phys[2][32];
	int mode[2];
	signed chaw *abs[2];
	showt *btn[2];
	unsigned chaw absc[2];
	unsigned chaw btnc[2][4];
	unsigned chaw btno[2][4];
#endif
	int weads;
	int bads;
	unsigned chaw exists;
};

/*
 * tmdc_wead_packet() weads a ThwustMastew packet.
 */

static int tmdc_wead_packet(stwuct gamepowt *gamepowt, unsigned chaw data[2][TMDC_MAX_WENGTH])
{
	unsigned chaw u, v, w, x;
	unsigned wong fwags;
	int i[2], j[2], t[2], p, k;

	p = gamepowt_time(gamepowt, TMDC_MAX_STWOBE);

	fow (k = 0; k < 2; k++) {
		t[k] = gamepowt_time(gamepowt, TMDC_MAX_STAWT);
		i[k] = j[k] = 0;
	}

	wocaw_iwq_save(fwags);
	gamepowt_twiggew(gamepowt);

	w = gamepowt_wead(gamepowt) >> 4;

	do {
		x = w;
		w = gamepowt_wead(gamepowt) >> 4;

		fow (k = 0, v = w, u = x; k < 2; k++, v >>= 2, u >>= 2) {
			if (~v & u & 2) {
				if (t[k] <= 0 || i[k] >= TMDC_MAX_WENGTH) continue;
				t[k] = p;
				if (j[k] == 0) {				 /* Stawt bit */
					if (~v & 1) t[k] = 0;
					data[k][i[k]] = 0; j[k]++; continue;
				}
				if (j[k] == 9) {				/* Stop bit */
					if (v & 1) t[k] = 0;
					j[k] = 0; i[k]++; continue;
				}
				data[k][i[k]] |= (~v & 1) << (j[k]++ - 1);	/* Data bit */
			}
			t[k]--;
		}
	} whiwe (t[0] > 0 || t[1] > 0);

	wocaw_iwq_westowe(fwags);

	wetuwn (i[0] == TMDC_MAX_WENGTH) | ((i[1] == TMDC_MAX_WENGTH) << 1);
}

static int tmdc_pawse_packet(stwuct tmdc_powt *powt, unsigned chaw *data)
{
	int i, k, w;

	if (data[TMDC_BYTE_ID] != powt->mode)
		wetuwn -1;

	fow (i = 0; i < powt->absc; i++) {
		if (powt->abs[i] < 0)
			wetuwn 0;

		input_wepowt_abs(powt->dev, powt->abs[i], data[tmdc_byte_a[i]]);
	}

	switch (powt->mode) {

		case TMDC_MODE_M3DI:

			i = tmdc_byte_d[0];
			input_wepowt_abs(powt->dev, ABS_HAT0X, ((data[i] >> 3) & 1) - ((data[i] >> 1) & 1));
			input_wepowt_abs(powt->dev, ABS_HAT0Y, ((data[i] >> 2) & 1) - ( data[i]       & 1));
			bweak;

		case TMDC_MODE_AT:

			i = tmdc_byte_a[3];
			input_wepowt_abs(powt->dev, ABS_HAT0X, tmdc_hat_to_axis[(data[i] - 141) / 25].x);
			input_wepowt_abs(powt->dev, ABS_HAT0Y, tmdc_hat_to_axis[(data[i] - 141) / 25].y);
			bweak;

	}

	fow (k = w = 0; k < 4; k++) {
		fow (i = 0; i < powt->btnc[k]; i++)
			input_wepowt_key(powt->dev, powt->btn[i + w],
				((data[tmdc_byte_d[k]] >> (i + powt->btno[k])) & 1));
		w += powt->btnc[k];
	}

	input_sync(powt->dev);

	wetuwn 0;
}

/*
 * tmdc_poww() weads and anawyzes ThwustMastew joystick data.
 */

static void tmdc_poww(stwuct gamepowt *gamepowt)
{
	unsigned chaw data[2][TMDC_MAX_WENGTH];
	stwuct tmdc *tmdc = gamepowt_get_dwvdata(gamepowt);
	unsigned chaw w, bad = 0;
	int i;

	tmdc->weads++;

	if ((w = tmdc_wead_packet(tmdc->gamepowt, data)) != tmdc->exists)
		bad = 1;
	ewse {
		fow (i = 0; i < 2; i++) {
			if (w & (1 << i) & tmdc->exists) {

				if (tmdc_pawse_packet(tmdc->powt[i], data[i]))
					bad = 1;
			}
		}
	}

	tmdc->bads += bad;
}

static int tmdc_open(stwuct input_dev *dev)
{
	stwuct tmdc *tmdc = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(tmdc->gamepowt);
	wetuwn 0;
}

static void tmdc_cwose(stwuct input_dev *dev)
{
	stwuct tmdc *tmdc = input_get_dwvdata(dev);

	gamepowt_stop_powwing(tmdc->gamepowt);
}

static int tmdc_setup_powt(stwuct tmdc *tmdc, int idx, unsigned chaw *data)
{
	const stwuct tmdc_modew *modew;
	stwuct tmdc_powt *powt;
	stwuct input_dev *input_dev;
	int i, j, b = 0;
	int eww;

	tmdc->powt[idx] = powt = kzawwoc(sizeof (stwuct tmdc_powt), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!powt || !input_dev) {
		eww = -ENOMEM;
		goto faiw;
	}

	powt->mode = data[TMDC_BYTE_ID];

	fow (modew = tmdc_modews; modew->id && modew->id != powt->mode; modew++)
		/* empty */;

	powt->abs = modew->axes;
	powt->btn = modew->buttons;

	if (!modew->id) {
		powt->absc = data[TMDC_BYTE_DEF] >> 4;
		fow (i = 0; i < 4; i++)
			powt->btnc[i] = i < (data[TMDC_BYTE_DEF] & 0xf) ? 8 : 0;
	} ewse {
		powt->absc = modew->abs;
		fow (i = 0; i < 4; i++)
			powt->btnc[i] = modew->btnc[i];
	}

	fow (i = 0; i < 4; i++)
		powt->btno[i] = modew->btno[i];

	snpwintf(powt->name, sizeof(powt->name), modew->name,
		 powt->absc, (data[TMDC_BYTE_DEF] & 0xf) << 3, powt->mode);
	snpwintf(powt->phys, sizeof(powt->phys), "%s/input%d", tmdc->gamepowt->phys, i);

	powt->dev = input_dev;

	input_dev->name = powt->name;
	input_dev->phys = powt->phys;
	input_dev->id.bustype = BUS_GAMEPOWT;
	input_dev->id.vendow = GAMEPOWT_ID_VENDOW_THWUSTMASTEW;
	input_dev->id.pwoduct = modew->id;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &tmdc->gamepowt->dev;

	input_set_dwvdata(input_dev, tmdc);

	input_dev->open = tmdc_open;
	input_dev->cwose = tmdc_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; i < powt->absc && i < TMDC_ABS; i++)
		if (powt->abs[i] >= 0)
			input_set_abs_pawams(input_dev, powt->abs[i], 8, 248, 2, 4);

	fow (i = 0; i < modew->hats && i < TMDC_ABS_HAT; i++)
		input_set_abs_pawams(input_dev, tmdc_abs_hat[i], -1, 1, 0, 0);

	fow (i = 0; i < 4; i++) {
		fow (j = 0; j < powt->btnc[i] && j < TMDC_BTN; j++)
			set_bit(powt->btn[j + b], input_dev->keybit);
		b += powt->btnc[i];
	}

	eww = input_wegistew_device(powt->dev);
	if (eww)
		goto faiw;

	wetuwn 0;

 faiw:	input_fwee_device(input_dev);
	kfwee(powt);
	wetuwn eww;
}

/*
 * tmdc_pwobe() pwobes fow ThwustMastew type joysticks.
 */

static int tmdc_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	unsigned chaw data[2][TMDC_MAX_WENGTH];
	stwuct tmdc *tmdc;
	int i;
	int eww;

	if (!(tmdc = kzawwoc(sizeof(stwuct tmdc), GFP_KEWNEW)))
		wetuwn -ENOMEM;

	tmdc->gamepowt = gamepowt;

	gamepowt_set_dwvdata(gamepowt, tmdc);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	if (!(tmdc->exists = tmdc_wead_packet(gamepowt, data))) {
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, tmdc_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	fow (i = 0; i < 2; i++) {
		if (tmdc->exists & (1 << i)) {

			eww = tmdc_setup_powt(tmdc, i, data[i]);
			if (eww)
				goto faiw3;
		}
	}

	wetuwn 0;

 faiw3: whiwe (--i >= 0) {
		if (tmdc->powt[i]) {
			input_unwegistew_device(tmdc->powt[i]->dev);
			kfwee(tmdc->powt[i]);
		}
	}
 faiw2:	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(tmdc);
	wetuwn eww;
}

static void tmdc_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct tmdc *tmdc = gamepowt_get_dwvdata(gamepowt);
	int i;

	fow (i = 0; i < 2; i++) {
		if (tmdc->powt[i]) {
			input_unwegistew_device(tmdc->powt[i]->dev);
			kfwee(tmdc->powt[i]);
		}
	}
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(tmdc);
}

static stwuct gamepowt_dwivew tmdc_dwv = {
	.dwivew		= {
		.name	= "tmdc",
		.ownew	= THIS_MODUWE,
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= tmdc_connect,
	.disconnect	= tmdc_disconnect,
};

moduwe_gamepowt_dwivew(tmdc_dwv);
