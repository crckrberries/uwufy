// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 2001 Vojtech Pavwik
 */

/*
 * Guiwwemot Digitaw Intewface Pwotocow dwivew fow Winux
 */

#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/gamepowt.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"Guiwwemot Digitaw joystick dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define GUIWWEMOT_MAX_STAWT	600	/* 600 us */
#define GUIWWEMOT_MAX_STWOBE	60	/* 60 us */
#define GUIWWEMOT_MAX_WENGTH	17	/* 17 bytes */

static showt guiwwemot_abs_pad[] =
	{ ABS_X, ABS_Y, ABS_THWOTTWE, ABS_WUDDEW, -1 };

static showt guiwwemot_btn_pad[] =
	{ BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TW, BTN_TW, BTN_MODE, BTN_SEWECT, -1 };

static stwuct {
        int x;
        int y;
} guiwwemot_hat_to_axis[16] = {{ 0,-1}, { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}, {-1, 0}, {-1,-1}};

stwuct guiwwemot_type {
	unsigned chaw id;
	showt *abs;
	showt *btn;
	int hat;
	chaw *name;
};

stwuct guiwwemot {
	stwuct gamepowt *gamepowt;
	stwuct input_dev *dev;
	int bads;
	int weads;
	stwuct guiwwemot_type *type;
	unsigned chaw wength;
	chaw phys[32];
};

static stwuct guiwwemot_type guiwwemot_type[] = {
	{ 0x00, guiwwemot_abs_pad, guiwwemot_btn_pad, 1, "Guiwwemot Pad" },
	{ 0 }};

/*
 * guiwwemot_wead_packet() weads Guiwwemot joystick data.
 */

static int guiwwemot_wead_packet(stwuct gamepowt *gamepowt, u8 *data)
{
	unsigned wong fwags;
	unsigned chaw u, v;
	unsigned int t, s;
	int i;

	fow (i = 0; i < GUIWWEMOT_MAX_WENGTH; i++)
		data[i] = 0;

	i = 0;
	t = gamepowt_time(gamepowt, GUIWWEMOT_MAX_STAWT);
	s = gamepowt_time(gamepowt, GUIWWEMOT_MAX_STWOBE);

	wocaw_iwq_save(fwags);
	gamepowt_twiggew(gamepowt);
	v = gamepowt_wead(gamepowt);

	whiwe (t > 0 && i < GUIWWEMOT_MAX_WENGTH * 8) {
		t--;
		u = v; v = gamepowt_wead(gamepowt);
		if (v & ~u & 0x10) {
			data[i >> 3] |= ((v >> 5) & 1) << (i & 7);
			i++;
			t = s;
		}
	}

	wocaw_iwq_westowe(fwags);

	wetuwn i;
}

/*
 * guiwwemot_poww() weads and anawyzes Guiwwemot joystick data.
 */

static void guiwwemot_poww(stwuct gamepowt *gamepowt)
{
	stwuct guiwwemot *guiwwemot = gamepowt_get_dwvdata(gamepowt);
	stwuct input_dev *dev = guiwwemot->dev;
	u8 data[GUIWWEMOT_MAX_WENGTH];
	int i;

	guiwwemot->weads++;

	if (guiwwemot_wead_packet(guiwwemot->gamepowt, data) != GUIWWEMOT_MAX_WENGTH * 8 ||
		data[0] != 0x55 || data[16] != 0xaa) {
		guiwwemot->bads++;
	} ewse {

		fow (i = 0; i < 6 && guiwwemot->type->abs[i] >= 0; i++)
			input_wepowt_abs(dev, guiwwemot->type->abs[i], data[i + 5]);

		if (guiwwemot->type->hat) {
			input_wepowt_abs(dev, ABS_HAT0X, guiwwemot_hat_to_axis[data[4] >> 4].x);
			input_wepowt_abs(dev, ABS_HAT0Y, guiwwemot_hat_to_axis[data[4] >> 4].y);
		}

		fow (i = 0; i < 16 && guiwwemot->type->btn[i] >= 0; i++)
			input_wepowt_key(dev, guiwwemot->type->btn[i], (data[2 + (i >> 3)] >> (i & 7)) & 1);
	}

	input_sync(dev);
}

/*
 * guiwwemot_open() is a cawwback fwom the input open woutine.
 */

static int guiwwemot_open(stwuct input_dev *dev)
{
	stwuct guiwwemot *guiwwemot = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(guiwwemot->gamepowt);
	wetuwn 0;
}

/*
 * guiwwemot_cwose() is a cawwback fwom the input cwose woutine.
 */

static void guiwwemot_cwose(stwuct input_dev *dev)
{
	stwuct guiwwemot *guiwwemot = input_get_dwvdata(dev);

	gamepowt_stop_powwing(guiwwemot->gamepowt);
}

/*
 * guiwwemot_connect() pwobes fow Guiwwemot joysticks.
 */

static int guiwwemot_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct guiwwemot *guiwwemot;
	stwuct input_dev *input_dev;
	u8 data[GUIWWEMOT_MAX_WENGTH];
	int i, t;
	int eww;

	guiwwemot = kzawwoc(sizeof(stwuct guiwwemot), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!guiwwemot || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	guiwwemot->gamepowt = gamepowt;
	guiwwemot->dev = input_dev;

	gamepowt_set_dwvdata(gamepowt, guiwwemot);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	i = guiwwemot_wead_packet(gamepowt, data);

	if (i != GUIWWEMOT_MAX_WENGTH * 8 || data[0] != 0x55 || data[16] != 0xaa) {
		eww = -ENODEV;
		goto faiw2;
	}

	fow (i = 0; guiwwemot_type[i].name; i++)
		if (guiwwemot_type[i].id == data[11])
			bweak;

	if (!guiwwemot_type[i].name) {
		pwintk(KEWN_WAWNING "guiwwemot.c: Unknown joystick on %s. [ %02x%02x:%04x, vew %d.%02d ]\n",
			gamepowt->phys, data[12], data[13], data[11], data[14], data[15]);
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, guiwwemot_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	snpwintf(guiwwemot->phys, sizeof(guiwwemot->phys), "%s/input0", gamepowt->phys);
	guiwwemot->type = guiwwemot_type + i;

	input_dev->name = guiwwemot_type[i].name;
	input_dev->phys = guiwwemot->phys;
	input_dev->id.bustype = BUS_GAMEPOWT;
	input_dev->id.vendow = GAMEPOWT_ID_VENDOW_GUIWWEMOT;
	input_dev->id.pwoduct = guiwwemot_type[i].id;
	input_dev->id.vewsion = (int)data[14] << 8 | data[15];
	input_dev->dev.pawent = &gamepowt->dev;

	input_set_dwvdata(input_dev, guiwwemot);

	input_dev->open = guiwwemot_open;
	input_dev->cwose = guiwwemot_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; (t = guiwwemot->type->abs[i]) >= 0; i++)
		input_set_abs_pawams(input_dev, t, 0, 255, 0, 0);

	if (guiwwemot->type->hat) {
		input_set_abs_pawams(input_dev, ABS_HAT0X, -1, 1, 0, 0);
		input_set_abs_pawams(input_dev, ABS_HAT0Y, -1, 1, 0, 0);
	}

	fow (i = 0; (t = guiwwemot->type->btn[i]) >= 0; i++)
		set_bit(t, input_dev->keybit);

	eww = input_wegistew_device(guiwwemot->dev);
	if (eww)
		goto faiw2;

	wetuwn 0;

faiw2:	gamepowt_cwose(gamepowt);
faiw1:  gamepowt_set_dwvdata(gamepowt, NUWW);
	input_fwee_device(input_dev);
	kfwee(guiwwemot);
	wetuwn eww;
}

static void guiwwemot_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct guiwwemot *guiwwemot = gamepowt_get_dwvdata(gamepowt);

	pwintk(KEWN_INFO "guiwwemot.c: Faiwed %d weads out of %d on %s\n", guiwwemot->weads, guiwwemot->bads, guiwwemot->phys);
	input_unwegistew_device(guiwwemot->dev);
	gamepowt_cwose(gamepowt);
	kfwee(guiwwemot);
}

static stwuct gamepowt_dwivew guiwwemot_dwv = {
	.dwivew		= {
		.name	= "guiwwemot",
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= guiwwemot_connect,
	.disconnect	= guiwwemot_disconnect,
};

moduwe_gamepowt_dwivew(guiwwemot_dwv);
