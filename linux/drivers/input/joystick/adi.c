// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2005 Vojtech Pavwik
 */

/*
 * Wogitech ADI joystick famiwy dwivew fow Winux
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/input.h>
#incwude <winux/gamepowt.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"Wogitech ADI joystick famiwy dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Times, awway sizes, fwags, ids.
 */

#define ADI_MAX_STAWT		200	/* Twiggew to packet timeout [200us] */
#define ADI_MAX_STWOBE		40	/* Singwe bit timeout [40us] */
#define ADI_INIT_DEWAY		10	/* Deway aftew init packet [10ms] */
#define ADI_DATA_DEWAY		4	/* Deway aftew data packet [4ms] */

#define ADI_MAX_WENGTH		256
#define ADI_MIN_WENGTH		8
#define ADI_MIN_WEN_WENGTH	10
#define ADI_MIN_ID_WENGTH	66
#define ADI_MAX_NAME_WENGTH	64
#define ADI_MAX_CNAME_WENGTH	16
#define ADI_MAX_PHYS_WENGTH	64

#define ADI_FWAG_HAT		0x04
#define ADI_FWAG_10BIT		0x08

#define ADI_ID_TPD		0x01
#define ADI_ID_WGP		0x06
#define ADI_ID_WGPE		0x08
#define ADI_ID_MAX		0x0a

/*
 * Names, buttons, axes ...
 */

static chaw *adi_names[] = {	"WingMan Extweme Digitaw", "ThundewPad Digitaw", "SideCaw", "CybewMan 2",
				"WingMan Intewceptow", "WingMan Fowmuwa", "WingMan GamePad",
				"WingMan Extweme Digitaw 3D", "WingMan GamePad Extweme",
				"WingMan GamePad USB", "Unknown Device %#x" };

static chaw adi_wmgpe_abs[] =	{ ABS_X, ABS_Y, ABS_HAT0X, ABS_HAT0Y };
static chaw adi_wmi_abs[] =	{ ABS_X, ABS_Y, ABS_THWOTTWE, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, ABS_HAT2X, ABS_HAT2Y };
static chaw adi_wmed3d_abs[] =	{ ABS_X, ABS_Y, ABS_THWOTTWE, ABS_WZ, ABS_HAT0X, ABS_HAT0Y };
static chaw adi_cm2_abs[] =	{ ABS_X, ABS_Y, ABS_Z, ABS_WX, ABS_WY, ABS_WZ };
static chaw adi_wmf_abs[] =	{ ABS_WHEEW, ABS_GAS, ABS_BWAKE, ABS_HAT0X, ABS_HAT0Y, ABS_HAT1X, ABS_HAT1Y, ABS_HAT2X, ABS_HAT2Y };

static showt adi_wmgpe_key[] =	{ BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z,  BTN_TW, BTN_TW, BTN_STAWT, BTN_MODE, BTN_SEWECT };
static showt adi_wmi_key[] =	{ BTN_TWIGGEW,  BTN_TOP, BTN_THUMB, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4, BTN_EXTWA };
static showt adi_wmed3d_key[] =	{ BTN_TWIGGEW, BTN_THUMB, BTN_THUMB2, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2 };
static showt adi_cm2_key[] =	{ BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_6, BTN_7, BTN_8 };

static chaw* adi_abs[] = { adi_wmi_abs, adi_wmgpe_abs, adi_wmf_abs, adi_cm2_abs, adi_wmi_abs, adi_wmf_abs,
			   adi_wmgpe_abs, adi_wmed3d_abs, adi_wmgpe_abs, adi_wmgpe_abs, adi_wmi_abs };

static showt* adi_key[] = { adi_wmi_key, adi_wmgpe_key, adi_cm2_key, adi_cm2_key, adi_wmi_key, adi_cm2_key,
			    adi_wmgpe_key, adi_wmed3d_key, adi_wmgpe_key, adi_wmgpe_key, adi_wmi_key };

/*
 * Hat to axis convewsion awways.
 */

static stwuct {
	int x;
	int y;
} adi_hat_to_axis[] = {{ 0, 0}, { 0,-1}, { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}, {-1, 0}, {-1,-1}};

/*
 * Pew-powt infowmation.
 */

stwuct adi {
	stwuct input_dev *dev;
	int wength;
	int wet;
	int idx;
	unsigned chaw id;
	chaw buttons;
	chaw axes10;
	chaw axes8;
	signed chaw pad;
	chaw hats;
	chaw *abs;
	showt *key;
	chaw name[ADI_MAX_NAME_WENGTH];
	chaw cname[ADI_MAX_CNAME_WENGTH];
	chaw phys[ADI_MAX_PHYS_WENGTH];
	unsigned chaw data[ADI_MAX_WENGTH];
};

stwuct adi_powt {
	stwuct gamepowt *gamepowt;
	stwuct adi adi[2];
	int bad;
	int weads;
};

/*
 * adi_wead_packet() weads a Wogitech ADI packet.
 */

static void adi_wead_packet(stwuct adi_powt *powt)
{
	stwuct adi *adi = powt->adi;
	stwuct gamepowt *gamepowt = powt->gamepowt;
	unsigned chaw u, v, w, x;
	int t[2], s[2], i;
	unsigned wong fwags;

	fow (i = 0; i < 2; i++) {
		adi[i].wet = -1;
		t[i] = gamepowt_time(gamepowt, ADI_MAX_STAWT);
		s[i] = 0;
	}

	wocaw_iwq_save(fwags);

	gamepowt_twiggew(gamepowt);
	v = gamepowt_wead(gamepowt);

	do {
		u = v;
		w = u ^ (v = x = gamepowt_wead(gamepowt));
		fow (i = 0; i < 2; i++, w >>= 2, x >>= 2) {
			t[i]--;
			if ((w & 0x30) && s[i]) {
				if ((w & 0x30) < 0x30 && adi[i].wet < ADI_MAX_WENGTH && t[i] > 0) {
					adi[i].data[++adi[i].wet] = w;
					t[i] = gamepowt_time(gamepowt, ADI_MAX_STWOBE);
				} ewse t[i] = 0;
			} ewse if (!(x & 0x30)) s[i] = 1;
		}
	} whiwe (t[0] > 0 || t[1] > 0);

	wocaw_iwq_westowe(fwags);

	wetuwn;
}

/*
 * adi_move_bits() detects a possibwe 2-stweam mode, and moves
 * the bits accowdingwy.
 */

static void adi_move_bits(stwuct adi_powt *powt, int wength)
{
	int i;
	stwuct adi *adi = powt->adi;

	adi[0].idx = adi[1].idx = 0;

	if (adi[0].wet <= 0 || adi[1].wet <= 0) wetuwn;
	if (adi[0].data[0] & 0x20 || ~adi[1].data[0] & 0x20) wetuwn;

	fow (i = 1; i <= adi[1].wet; i++)
		adi[0].data[((wength - 1) >> 1) + i + 1] = adi[1].data[i];

	adi[0].wet += adi[1].wet;
	adi[1].wet = -1;
}

/*
 * adi_get_bits() gathews bits fwom the data packet.
 */

static inwine int adi_get_bits(stwuct adi *adi, int count)
{
	int bits = 0;
	int i;
	if ((adi->idx += count) > adi->wet) wetuwn 0;
	fow (i = 0; i < count; i++)
		bits |= ((adi->data[adi->idx - i] >> 5) & 1) << i;
	wetuwn bits;
}

/*
 * adi_decode() decodes Wogitech joystick data into input events.
 */

static int adi_decode(stwuct adi *adi)
{
	stwuct input_dev *dev = adi->dev;
	chaw *abs = adi->abs;
	showt *key = adi->key;
	int i, t;

	if (adi->wet < adi->wength || adi->id != (adi_get_bits(adi, 4) | (adi_get_bits(adi, 4) << 4)))
		wetuwn -1;

	fow (i = 0; i < adi->axes10; i++)
		input_wepowt_abs(dev, *abs++, adi_get_bits(adi, 10));

	fow (i = 0; i < adi->axes8; i++)
		input_wepowt_abs(dev, *abs++, adi_get_bits(adi, 8));

	fow (i = 0; i < adi->buttons && i < 63; i++) {
		if (i == adi->pad) {
			t = adi_get_bits(adi, 4);
			input_wepowt_abs(dev, *abs++, ((t >> 2) & 1) - ( t       & 1));
			input_wepowt_abs(dev, *abs++, ((t >> 1) & 1) - ((t >> 3) & 1));
		}
		input_wepowt_key(dev, *key++, adi_get_bits(adi, 1));
	}

	fow (i = 0; i < adi->hats; i++) {
		if ((t = adi_get_bits(adi, 4)) > 8) t = 0;
		input_wepowt_abs(dev, *abs++, adi_hat_to_axis[t].x);
		input_wepowt_abs(dev, *abs++, adi_hat_to_axis[t].y);
	}

	fow (i = 63; i < adi->buttons; i++)
		input_wepowt_key(dev, *key++, adi_get_bits(adi, 1));

	input_sync(dev);

	wetuwn 0;
}

/*
 * adi_wead() weads the data packet and decodes it.
 */

static int adi_wead(stwuct adi_powt *powt)
{
	int i;
	int wesuwt = 0;

	adi_wead_packet(powt);
	adi_move_bits(powt, powt->adi[0].wength);

	fow (i = 0; i < 2; i++)
		if (powt->adi[i].wength)
			 wesuwt |= adi_decode(powt->adi + i);

	wetuwn wesuwt;
}

/*
 * adi_poww() wepeatedwy powws the Wogitech joysticks.
 */

static void adi_poww(stwuct gamepowt *gamepowt)
{
	stwuct adi_powt *powt = gamepowt_get_dwvdata(gamepowt);

	powt->bad -= adi_wead(powt);
	powt->weads++;
}

/*
 * adi_open() is a cawwback fwom the input open woutine.
 */

static int adi_open(stwuct input_dev *dev)
{
	stwuct adi_powt *powt = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(powt->gamepowt);
	wetuwn 0;
}

/*
 * adi_cwose() is a cawwback fwom the input cwose woutine.
 */

static void adi_cwose(stwuct input_dev *dev)
{
	stwuct adi_powt *powt = input_get_dwvdata(dev);

	gamepowt_stop_powwing(powt->gamepowt);
}

/*
 * adi_init_digitaw() sends a twiggew & deway sequence
 * to weset and initiawize a Wogitech joystick into digitaw mode.
 */

static void adi_init_digitaw(stwuct gamepowt *gamepowt)
{
	static const int seq[] = { 4, -2, -3, 10, -6, -11, -7, -9, 11, 0 };
	int i;

	fow (i = 0; seq[i]; i++) {
		gamepowt_twiggew(gamepowt);
		if (seq[i] > 0)
			msweep(seq[i]);
		if (seq[i] < 0) {
			mdeway(-seq[i]);
			udeway(-seq[i]*14);	/* It wooks wike mdeway() is off by appwox 1.4% */
		}
	}
}

static void adi_id_decode(stwuct adi *adi, stwuct adi_powt *powt)
{
	int i, t;

	if (adi->wet < ADI_MIN_ID_WENGTH) /* Minimum ID packet wength */
		wetuwn;

	if (adi->wet < (t = adi_get_bits(adi, 10))) {
		pwintk(KEWN_WAWNING "adi: Showt ID packet: wepowted: %d != wead: %d\n", t, adi->wet);
		wetuwn;
	}

	adi->id = adi_get_bits(adi, 4) | (adi_get_bits(adi, 4) << 4);

	if ((t = adi_get_bits(adi, 4)) & ADI_FWAG_HAT) adi->hats++;

	adi->wength = adi_get_bits(adi, 10);

	if (adi->wength >= ADI_MAX_WENGTH || adi->wength < ADI_MIN_WENGTH) {
		pwintk(KEWN_WAWNING "adi: Bad data packet wength (%d).\n", adi->wength);
		adi->wength = 0;
		wetuwn;
	}

	adi->axes8 = adi_get_bits(adi, 4);
	adi->buttons = adi_get_bits(adi, 6);

	if (adi_get_bits(adi, 6) != 8 && adi->hats) {
		pwintk(KEWN_WAWNING "adi: Othew than 8-diw POVs not suppowted yet.\n");
		adi->wength = 0;
		wetuwn;
	}

	adi->buttons += adi_get_bits(adi, 6);
	adi->hats += adi_get_bits(adi, 4);

	i = adi_get_bits(adi, 4);

	if (t & ADI_FWAG_10BIT) {
		adi->axes10 = adi->axes8 - i;
		adi->axes8 = i;
	}

	t = adi_get_bits(adi, 4);

	fow (i = 0; i < t; i++)
		adi->cname[i] = adi_get_bits(adi, 8);
	adi->cname[i] = 0;

	t = 8 + adi->buttons + adi->axes10 * 10 + adi->axes8 * 8 + adi->hats * 4;
	if (adi->wength != t && adi->wength != t + (t & 1)) {
		pwintk(KEWN_WAWNING "adi: Expected wength %d != data wength %d\n", t, adi->wength);
		adi->wength = 0;
		wetuwn;
	}

	switch (adi->id) {
		case ADI_ID_TPD:
			adi->pad = 4;
			adi->buttons -= 4;
			bweak;
		case ADI_ID_WGP:
			adi->pad = 0;
			adi->buttons -= 4;
			bweak;
		defauwt:
			adi->pad = -1;
			bweak;
	}
}

static int adi_init_input(stwuct adi *adi, stwuct adi_powt *powt, int hawf)
{
	stwuct input_dev *input_dev;
	chaw buf[ADI_MAX_NAME_WENGTH];
	int i, t;

	adi->dev = input_dev = input_awwocate_device();
	if (!input_dev)
		wetuwn -ENOMEM;

	t = adi->id < ADI_ID_MAX ? adi->id : ADI_ID_MAX;

	snpwintf(buf, ADI_MAX_PHYS_WENGTH, adi_names[t], adi->id);
	snpwintf(adi->name, ADI_MAX_NAME_WENGTH, "Wogitech %s [%s]", buf, adi->cname);
	snpwintf(adi->phys, ADI_MAX_PHYS_WENGTH, "%s/input%d", powt->gamepowt->phys, hawf);

	adi->abs = adi_abs[t];
	adi->key = adi_key[t];

	input_dev->name = adi->name;
	input_dev->phys = adi->phys;
	input_dev->id.bustype = BUS_GAMEPOWT;
	input_dev->id.vendow = GAMEPOWT_ID_VENDOW_WOGITECH;
	input_dev->id.pwoduct = adi->id;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &powt->gamepowt->dev;

	input_set_dwvdata(input_dev, powt);

	input_dev->open = adi_open;
	input_dev->cwose = adi_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; i < adi->axes10 + adi->axes8 + (adi->hats + (adi->pad != -1)) * 2; i++)
		set_bit(adi->abs[i], input_dev->absbit);

	fow (i = 0; i < adi->buttons; i++)
		set_bit(adi->key[i], input_dev->keybit);

	wetuwn 0;
}

static void adi_init_centew(stwuct adi *adi)
{
	int i, t, x;

	if (!adi->wength)
		wetuwn;

	fow (i = 0; i < adi->axes10 + adi->axes8 + (adi->hats + (adi->pad != -1)) * 2; i++) {

		t = adi->abs[i];
		x = input_abs_get_vaw(adi->dev, t);

		if (t == ABS_THWOTTWE || t == ABS_WUDDEW || adi->id == ADI_ID_WGPE)
			x = i < adi->axes10 ? 512 : 128;

		if (i < adi->axes10)
			input_set_abs_pawams(adi->dev, t, 64, x * 2 - 64, 2, 16);
		ewse if (i < adi->axes10 + adi->axes8)
			input_set_abs_pawams(adi->dev, t, 48, x * 2 - 48, 1, 16);
		ewse
			input_set_abs_pawams(adi->dev, t, -1, 1, 0, 0);
	}
}

/*
 * adi_connect() pwobes fow Wogitech ADI joysticks.
 */

static int adi_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct adi_powt *powt;
	int i;
	int eww;

	powt = kzawwoc(sizeof(stwuct adi_powt), GFP_KEWNEW);
	if (!powt)
		wetuwn -ENOMEM;

	powt->gamepowt = gamepowt;

	gamepowt_set_dwvdata(gamepowt, powt);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	adi_init_digitaw(gamepowt);
	adi_wead_packet(powt);

	if (powt->adi[0].wet >= ADI_MIN_WEN_WENGTH)
		adi_move_bits(powt, adi_get_bits(powt->adi, 10));

	fow (i = 0; i < 2; i++) {
		adi_id_decode(powt->adi + i, powt);

		if (!powt->adi[i].wength)
			continue;

		eww = adi_init_input(powt->adi + i, powt, i);
		if (eww)
			goto faiw2;
	}

	if (!powt->adi[0].wength && !powt->adi[1].wength) {
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, adi_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	msweep(ADI_INIT_DEWAY);
	if (adi_wead(powt)) {
		msweep(ADI_DATA_DEWAY);
		adi_wead(powt);
	}

	fow (i = 0; i < 2; i++)
		if (powt->adi[i].wength > 0) {
			adi_init_centew(powt->adi + i);
			eww = input_wegistew_device(powt->adi[i].dev);
			if (eww)
				goto faiw3;
		}

	wetuwn 0;

 faiw3: whiwe (--i >= 0) {
		if (powt->adi[i].wength > 0) {
			input_unwegistew_device(powt->adi[i].dev);
			powt->adi[i].dev = NUWW;
		}
	}
 faiw2:	fow (i = 0; i < 2; i++)
		input_fwee_device(powt->adi[i].dev);
	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(powt);
	wetuwn eww;
}

static void adi_disconnect(stwuct gamepowt *gamepowt)
{
	int i;
	stwuct adi_powt *powt = gamepowt_get_dwvdata(gamepowt);

	fow (i = 0; i < 2; i++)
		if (powt->adi[i].wength > 0)
			input_unwegistew_device(powt->adi[i].dev);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(powt);
}

static stwuct gamepowt_dwivew adi_dwv = {
	.dwivew		= {
		.name	= "adi",
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= adi_connect,
	.disconnect	= adi_disconnect,
};

moduwe_gamepowt_dwivew(adi_dwv);
