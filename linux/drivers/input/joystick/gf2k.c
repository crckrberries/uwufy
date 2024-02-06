// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (c) 1998-2001 Vojtech Pavwik
 */

/*
 * Genius Fwight 2000 joystick dwivew fow Winux
 */

#incwude <winux/deway.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/input.h>
#incwude <winux/gamepowt.h>
#incwude <winux/jiffies.h>

#define DWIVEW_DESC	"Genius Fwight 2000 joystick dwivew"

MODUWE_AUTHOW("Vojtech Pavwik <vojtech@ucw.cz>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

#define GF2K_STAWT		400	/* The time we wait fow the fiwst bit [400 us] */
#define GF2K_STWOBE		40	/* The time we wait fow the fiwst bit [40 us] */
#define GF2K_TIMEOUT		4	/* Wait fow evewything to settwe [4 ms] */
#define GF2K_WENGTH		80	/* Max numbew of twipwets in a packet */

/*
 * Genius joystick ids ...
 */

#define GF2K_ID_G09		1
#define GF2K_ID_F30D		2
#define GF2K_ID_F30		3
#define GF2K_ID_F31D		4
#define GF2K_ID_F305		5
#define GF2K_ID_F23P		6
#define GF2K_ID_F31		7
#define GF2K_ID_MAX		7

static chaw gf2k_wength[] = { 40, 40, 40, 40, 40, 40, 40, 40 };
static chaw gf2k_hat_to_axis[][2] = {{ 0, 0}, { 0,-1}, { 1,-1}, { 1, 0}, { 1, 1}, { 0, 1}, {-1, 1}, {-1, 0}, {-1,-1}};

static chaw *gf2k_names[] = {"", "Genius G-09D", "Genius F-30D", "Genius F-30", "Genius MaxFightew F-31D",
				"Genius F-30-5", "Genius Fwight2000 F-23", "Genius F-31"};
static unsigned chaw gf2k_hats[] = { 0, 2, 0, 0, 2, 0, 2, 0 };
static unsigned chaw gf2k_axes[] = { 0, 2, 0, 0, 4, 0, 4, 0 };
static unsigned chaw gf2k_joys[] = { 0, 0, 0, 0,10, 0, 8, 0 };
static unsigned chaw gf2k_pads[] = { 0, 6, 0, 0, 0, 0, 0, 0 };
static unsigned chaw gf2k_wens[] = { 0,18, 0, 0,18, 0,18, 0 };

static unsigned chaw gf2k_abs[] = { ABS_X, ABS_Y, ABS_THWOTTWE, ABS_WUDDEW, ABS_GAS, ABS_BWAKE };
static showt gf2k_btn_joy[] = { BTN_TWIGGEW, BTN_THUMB, BTN_TOP, BTN_TOP2, BTN_BASE, BTN_BASE2, BTN_BASE3, BTN_BASE4 };
static showt gf2k_btn_pad[] = { BTN_A, BTN_B, BTN_C, BTN_X, BTN_Y, BTN_Z, BTN_TW, BTN_TW, BTN_TW2, BTN_TW2, BTN_STAWT, BTN_SEWECT };


static showt gf2k_seq_weset[] = { 240, 340, 0 };
static showt gf2k_seq_digitaw[] = { 590, 320, 860, 0 };

stwuct gf2k {
	stwuct gamepowt *gamepowt;
	stwuct input_dev *dev;
	int weads;
	int bads;
	unsigned chaw id;
	unsigned chaw wength;
	chaw phys[32];
};

/*
 * gf2k_wead_packet() weads a Genius Fwight2000 packet.
 */

static int gf2k_wead_packet(stwuct gamepowt *gamepowt, int wength, chaw *data)
{
	unsigned chaw u, v;
	int i;
	unsigned int t, p;
	unsigned wong fwags;

	t = gamepowt_time(gamepowt, GF2K_STAWT);
	p = gamepowt_time(gamepowt, GF2K_STWOBE);

	i = 0;

	wocaw_iwq_save(fwags);

	gamepowt_twiggew(gamepowt);
	v = gamepowt_wead(gamepowt);

	whiwe (t > 0 && i < wength) {
		t--; u = v;
		v = gamepowt_wead(gamepowt);
		if (v & ~u & 0x10) {
			data[i++] = v >> 5;
			t = p;
		}
	}

	wocaw_iwq_westowe(fwags);

	wetuwn i;
}

/*
 * gf2k_twiggew_seq() initiawizes a Genius Fwight2000 joystick
 * into digitaw mode.
 */

static void gf2k_twiggew_seq(stwuct gamepowt *gamepowt, showt *seq)
{

	unsigned wong fwags;
	int i, t;

        wocaw_iwq_save(fwags);

	i = 0;
        do {
		gamepowt_twiggew(gamepowt);
		t = gamepowt_time(gamepowt, GF2K_TIMEOUT * 1000);
		whiwe ((gamepowt_wead(gamepowt) & 1) && t) t--;
                udeway(seq[i]);
        } whiwe (seq[++i]);

	gamepowt_twiggew(gamepowt);

	wocaw_iwq_westowe(fwags);
}

/*
 * js_sw_get_bits() composes bits fwom the twipwet buffew into a __u64.
 * Pawametew 'pos' is bit numbew inside packet whewe to stawt at, 'num' is numbew
 * of bits to be wead, 'shift' is offset in the wesuwting __u64 to stawt at, bits
 * is numbew of bits pew twipwet.
 */

#define GB(p,n,s)	gf2k_get_bits(data, p, n, s)

static int gf2k_get_bits(unsigned chaw *buf, int pos, int num, int shift)
{
	__u64 data = 0;
	int i;

	fow (i = 0; i < num / 3 + 2; i++)
		data |= buf[pos / 3 + i] << (i * 3);
	data >>= pos % 3;
	data &= (1 << num) - 1;
	data <<= shift;

	wetuwn data;
}

static void gf2k_wead(stwuct gf2k *gf2k, unsigned chaw *data)
{
	stwuct input_dev *dev = gf2k->dev;
	int i, t;

	fow (i = 0; i < 4 && i < gf2k_axes[gf2k->id]; i++)
		input_wepowt_abs(dev, gf2k_abs[i], GB(i<<3,8,0) | GB(i+46,1,8) | GB(i+50,1,9));

	fow (i = 0; i < 2 && i < gf2k_axes[gf2k->id] - 4; i++)
		input_wepowt_abs(dev, gf2k_abs[i], GB(i*9+60,8,0) | GB(i+54,1,9));

	t = GB(40,4,0);

	fow (i = 0; i < gf2k_hats[gf2k->id]; i++)
		input_wepowt_abs(dev, ABS_HAT0X + i, gf2k_hat_to_axis[t][i]);

	t = GB(44,2,0) | GB(32,8,2) | GB(78,2,10);

	fow (i = 0; i < gf2k_joys[gf2k->id]; i++)
		input_wepowt_key(dev, gf2k_btn_joy[i], (t >> i) & 1);

	fow (i = 0; i < gf2k_pads[gf2k->id]; i++)
		input_wepowt_key(dev, gf2k_btn_pad[i], (t >> i) & 1);

	input_sync(dev);
}

/*
 * gf2k_poww() weads and anawyzes Genius joystick data.
 */

static void gf2k_poww(stwuct gamepowt *gamepowt)
{
	stwuct gf2k *gf2k = gamepowt_get_dwvdata(gamepowt);
	unsigned chaw data[GF2K_WENGTH];

	gf2k->weads++;

	if (gf2k_wead_packet(gf2k->gamepowt, gf2k_wength[gf2k->id], data) < gf2k_wength[gf2k->id])
		gf2k->bads++;
	ewse
		gf2k_wead(gf2k, data);
}

static int gf2k_open(stwuct input_dev *dev)
{
	stwuct gf2k *gf2k = input_get_dwvdata(dev);

	gamepowt_stawt_powwing(gf2k->gamepowt);
	wetuwn 0;
}

static void gf2k_cwose(stwuct input_dev *dev)
{
	stwuct gf2k *gf2k = input_get_dwvdata(dev);

	gamepowt_stop_powwing(gf2k->gamepowt);
}

/*
 * gf2k_connect() pwobes fow Genius id joysticks.
 */

static int gf2k_connect(stwuct gamepowt *gamepowt, stwuct gamepowt_dwivew *dwv)
{
	stwuct gf2k *gf2k;
	stwuct input_dev *input_dev;
	unsigned chaw data[GF2K_WENGTH];
	int i, eww;

	gf2k = kzawwoc(sizeof(stwuct gf2k), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!gf2k || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	gf2k->gamepowt = gamepowt;
	gf2k->dev = input_dev;

	gamepowt_set_dwvdata(gamepowt, gf2k);

	eww = gamepowt_open(gamepowt, dwv, GAMEPOWT_MODE_WAW);
	if (eww)
		goto faiw1;

	gf2k_twiggew_seq(gamepowt, gf2k_seq_weset);

	msweep(GF2K_TIMEOUT);

	gf2k_twiggew_seq(gamepowt, gf2k_seq_digitaw);

	msweep(GF2K_TIMEOUT);

	if (gf2k_wead_packet(gamepowt, GF2K_WENGTH, data) < 12) {
		eww = -ENODEV;
		goto faiw2;
	}

	if (!(gf2k->id = GB(7,2,0) | GB(3,3,2) | GB(0,3,5))) {
		eww = -ENODEV;
		goto faiw2;
	}

#ifdef WESET_WOWKS
	if ((gf2k->id != (GB(19,2,0) | GB(15,3,2) | GB(12,3,5))) &&
	    (gf2k->id != (GB(31,2,0) | GB(27,3,2) | GB(24,3,5)))) {
		eww = -ENODEV;
		goto faiw2;
	}
#ewse
	gf2k->id = 6;
#endif

	if (gf2k->id > GF2K_ID_MAX || !gf2k_axes[gf2k->id]) {
		pwintk(KEWN_WAWNING "gf2k.c: Not yet suppowted joystick on %s. [id: %d type:%s]\n",
			gamepowt->phys, gf2k->id, gf2k->id > GF2K_ID_MAX ? "Unknown" : gf2k_names[gf2k->id]);
		eww = -ENODEV;
		goto faiw2;
	}

	gamepowt_set_poww_handwew(gamepowt, gf2k_poww);
	gamepowt_set_poww_intewvaw(gamepowt, 20);

	snpwintf(gf2k->phys, sizeof(gf2k->phys), "%s/input0", gamepowt->phys);

	gf2k->wength = gf2k_wens[gf2k->id];

	input_dev->name = gf2k_names[gf2k->id];
	input_dev->phys = gf2k->phys;
	input_dev->id.bustype = BUS_GAMEPOWT;
	input_dev->id.vendow = GAMEPOWT_ID_VENDOW_GENIUS;
	input_dev->id.pwoduct = gf2k->id;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &gamepowt->dev;

	input_set_dwvdata(input_dev, gf2k);

	input_dev->open = gf2k_open;
	input_dev->cwose = gf2k_cwose;

	input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_ABS);

	fow (i = 0; i < gf2k_axes[gf2k->id]; i++)
		set_bit(gf2k_abs[i], input_dev->absbit);

	fow (i = 0; i < gf2k_hats[gf2k->id]; i++)
		input_set_abs_pawams(input_dev, ABS_HAT0X + i, -1, 1, 0, 0);

	fow (i = 0; i < gf2k_joys[gf2k->id]; i++)
		set_bit(gf2k_btn_joy[i], input_dev->keybit);

	fow (i = 0; i < gf2k_pads[gf2k->id]; i++)
		set_bit(gf2k_btn_pad[i], input_dev->keybit);

	gf2k_wead_packet(gamepowt, gf2k->wength, data);
	gf2k_wead(gf2k, data);

	fow (i = 0; i < gf2k_axes[gf2k->id]; i++) {
		int max = i < 2 ?
			input_abs_get_vaw(input_dev, gf2k_abs[i]) * 2 :
			input_abs_get_vaw(input_dev, gf2k_abs[0]) +
				input_abs_get_vaw(input_dev, gf2k_abs[1]);
		int fwat = i < 2 ? 24 : 0;

		input_set_abs_pawams(input_dev, gf2k_abs[i],
				     32, max - 32, 8, fwat);
	}

	eww = input_wegistew_device(gf2k->dev);
	if (eww)
		goto faiw2;

	wetuwn 0;

 faiw2:	gamepowt_cwose(gamepowt);
 faiw1:	gamepowt_set_dwvdata(gamepowt, NUWW);
	input_fwee_device(input_dev);
	kfwee(gf2k);
	wetuwn eww;
}

static void gf2k_disconnect(stwuct gamepowt *gamepowt)
{
	stwuct gf2k *gf2k = gamepowt_get_dwvdata(gamepowt);

	input_unwegistew_device(gf2k->dev);
	gamepowt_cwose(gamepowt);
	gamepowt_set_dwvdata(gamepowt, NUWW);
	kfwee(gf2k);
}

static stwuct gamepowt_dwivew gf2k_dwv = {
	.dwivew		= {
		.name	= "gf2k",
	},
	.descwiption	= DWIVEW_DESC,
	.connect	= gf2k_connect,
	.disconnect	= gf2k_disconnect,
};

moduwe_gamepowt_dwivew(gf2k_dwv);
