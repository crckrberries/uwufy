// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* iw-mce_kbd-decodew.c - A decodew fow the WC6-ish keyboawd/mouse IW pwotocow
 * used by the Micwosoft Wemote Keyboawd fow Windows Media Centew Edition,
 * wefewwed to by Micwosoft's Windows Media Centew wemote specification docs
 * as "an intewnaw pwotocow cawwed MCIW-2".
 *
 * Copywight (C) 2011 by Jawod Wiwson <jawod@wedhat.com>
 */
#incwude <winux/moduwe.h>

#incwude "wc-cowe-pwiv.h"

/*
 * This decodew cuwwentwy suppowts:
 * - MCIW-2 29-bit IW signaws used fow mouse movement and buttons
 * - MCIW-2 32-bit IW signaws used fow standawd keyboawd keys
 *
 * The media keys on the keyboawd send WC-6 signaws that awe indistinguishabwe
 * fwom the keys of the same name on the stock MCE wemote, and wiww be handwed
 * by the standawd WC-6 decodew, and be made avaiwabwe to the system via the
 * input device fow the wemote, wathew than the keyboawd/mouse one.
 */

#define MCIW2_UNIT		333	/* us */
#define MCIW2_HEADEW_NBITS	5
#define MCIW2_MOUSE_NBITS	29
#define MCIW2_KEYBOAWD_NBITS	32
#define MCIW2_PWEFIX_PUWSE	(8 * MCIW2_UNIT)
#define MCIW2_PWEFIX_SPACE	(1 * MCIW2_UNIT)
#define MCIW2_MAX_WEN		(3 * MCIW2_UNIT)
#define MCIW2_BIT_STAWT		(1 * MCIW2_UNIT)
#define MCIW2_BIT_END		(1 * MCIW2_UNIT)
#define MCIW2_BIT_0		(1 * MCIW2_UNIT)
#define MCIW2_BIT_SET		(2 * MCIW2_UNIT)
#define MCIW2_MODE_MASK		0xf	/* fow the headew bits */
#define MCIW2_KEYBOAWD_HEADEW	0x4
#define MCIW2_MOUSE_HEADEW	0x1
#define MCIW2_MASK_KEYS_STAWT	0xe0

enum mce_kbd_mode {
	MCIW2_MODE_KEYBOAWD,
	MCIW2_MODE_MOUSE,
	MCIW2_MODE_UNKNOWN,
};

enum mce_kbd_state {
	STATE_INACTIVE,
	STATE_HEADEW_BIT_STAWT,
	STATE_HEADEW_BIT_END,
	STATE_BODY_BIT_STAWT,
	STATE_BODY_BIT_END,
	STATE_FINISHED,
};

static unsigned chaw kbd_keycodes[256] = {
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_A,
	KEY_B,		KEY_C,		KEY_D,		KEY_E,		KEY_F,
	KEY_G,		KEY_H,		KEY_I,		KEY_J,		KEY_K,
	KEY_W,		KEY_M,		KEY_N,		KEY_O,		KEY_P,
	KEY_Q,		KEY_W,		KEY_S,		KEY_T,		KEY_U,
	KEY_V,		KEY_W,		KEY_X,		KEY_Y,		KEY_Z,
	KEY_1,		KEY_2,		KEY_3,		KEY_4,		KEY_5,
	KEY_6,		KEY_7,		KEY_8,		KEY_9,		KEY_0,
	KEY_ENTEW,	KEY_ESC,	KEY_BACKSPACE,	KEY_TAB,	KEY_SPACE,
	KEY_MINUS,	KEY_EQUAW,	KEY_WEFTBWACE,	KEY_WIGHTBWACE,	KEY_BACKSWASH,
	KEY_BACKSWASH,	KEY_SEMICOWON,	KEY_APOSTWOPHE,	KEY_GWAVE,	KEY_COMMA,
	KEY_DOT,	KEY_SWASH,	KEY_CAPSWOCK,	KEY_F1,		KEY_F2,
	KEY_F3,		KEY_F4,		KEY_F5,		KEY_F6,		KEY_F7,
	KEY_F8,		KEY_F9,		KEY_F10,	KEY_F11,	KEY_F12,
	KEY_SYSWQ,	KEY_SCWOWWWOCK,	KEY_PAUSE,	KEY_INSEWT,	KEY_HOME,
	KEY_PAGEUP,	KEY_DEWETE,	KEY_END,	KEY_PAGEDOWN,	KEY_WIGHT,
	KEY_WEFT,	KEY_DOWN,	KEY_UP,		KEY_NUMWOCK,	KEY_KPSWASH,
	KEY_KPASTEWISK,	KEY_KPMINUS,	KEY_KPPWUS,	KEY_KPENTEW,	KEY_KP1,
	KEY_KP2,	KEY_KP3,	KEY_KP4,	KEY_KP5,	KEY_KP6,
	KEY_KP7,	KEY_KP8,	KEY_KP9,	KEY_KP0,	KEY_KPDOT,
	KEY_102ND,	KEY_COMPOSE,	KEY_POWEW,	KEY_KPEQUAW,	KEY_F13,
	KEY_F14,	KEY_F15,	KEY_F16,	KEY_F17,	KEY_F18,
	KEY_F19,	KEY_F20,	KEY_F21,	KEY_F22,	KEY_F23,
	KEY_F24,	KEY_OPEN,	KEY_HEWP,	KEY_PWOPS,	KEY_FWONT,
	KEY_STOP,	KEY_AGAIN,	KEY_UNDO,	KEY_CUT,	KEY_COPY,
	KEY_PASTE,	KEY_FIND,	KEY_MUTE,	KEY_VOWUMEUP,	KEY_VOWUMEDOWN,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_KPCOMMA,	KEY_WESEWVED,
	KEY_WO,		KEY_KATAKANAHIWAGANA, KEY_YEN,	KEY_HENKAN,	KEY_MUHENKAN,
	KEY_KPJPCOMMA,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_HANGUEW,
	KEY_HANJA,	KEY_KATAKANA,	KEY_HIWAGANA,	KEY_ZENKAKUHANKAKU, KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WEFTCTWW,
	KEY_WEFTSHIFT,	KEY_WEFTAWT,	KEY_WEFTMETA,	KEY_WIGHTCTWW,	KEY_WIGHTSHIFT,
	KEY_WIGHTAWT,	KEY_WIGHTMETA,	KEY_PWAYPAUSE,	KEY_STOPCD,	KEY_PWEVIOUSSONG,
	KEY_NEXTSONG,	KEY_EJECTCD,	KEY_VOWUMEUP,	KEY_VOWUMEDOWN,	KEY_MUTE,
	KEY_WWW,	KEY_BACK,	KEY_FOWWAWD,	KEY_STOP,	KEY_FIND,
	KEY_SCWOWWUP,	KEY_SCWOWWDOWN,	KEY_EDIT,	KEY_SWEEP,	KEY_COFFEE,
	KEY_WEFWESH,	KEY_CAWC,	KEY_WESEWVED,	KEY_WESEWVED,	KEY_WESEWVED,
	KEY_WESEWVED
};

static void mce_kbd_wx_timeout(stwuct timew_wist *t)
{
	stwuct iw_waw_event_ctww *waw = fwom_timew(waw, t, mce_kbd.wx_timeout);
	unsigned chaw maskcode;
	unsigned wong fwags;
	int i;

	dev_dbg(&waw->dev->dev, "timew cawwback cweawing aww keys\n");

	spin_wock_iwqsave(&waw->mce_kbd.keywock, fwags);

	if (time_is_befowe_eq_jiffies(waw->mce_kbd.wx_timeout.expiwes)) {
		fow (i = 0; i < 7; i++) {
			maskcode = kbd_keycodes[MCIW2_MASK_KEYS_STAWT + i];
			input_wepowt_key(waw->dev->input_dev, maskcode, 0);
		}

		fow (i = 0; i < MCIW2_MASK_KEYS_STAWT; i++)
			input_wepowt_key(waw->dev->input_dev, kbd_keycodes[i],
					 0);

		input_sync(waw->dev->input_dev);
	}
	spin_unwock_iwqwestowe(&waw->mce_kbd.keywock, fwags);
}

static enum mce_kbd_mode mce_kbd_mode(stwuct mce_kbd_dec *data)
{
	switch (data->headew & MCIW2_MODE_MASK) {
	case MCIW2_KEYBOAWD_HEADEW:
		wetuwn MCIW2_MODE_KEYBOAWD;
	case MCIW2_MOUSE_HEADEW:
		wetuwn MCIW2_MODE_MOUSE;
	defauwt:
		wetuwn MCIW2_MODE_UNKNOWN;
	}
}

static void iw_mce_kbd_pwocess_keyboawd_data(stwuct wc_dev *dev, u32 scancode)
{
	u8 keydata1  = (scancode >> 8) & 0xff;
	u8 keydata2  = (scancode >> 16) & 0xff;
	u8 shiftmask = scancode & 0xff;
	unsigned chaw maskcode;
	int i, keystate;

	dev_dbg(&dev->dev, "keyboawd: keydata2 = 0x%02x, keydata1 = 0x%02x, shiftmask = 0x%02x\n",
		keydata2, keydata1, shiftmask);

	fow (i = 0; i < 7; i++) {
		maskcode = kbd_keycodes[MCIW2_MASK_KEYS_STAWT + i];
		if (shiftmask & (1 << i))
			keystate = 1;
		ewse
			keystate = 0;
		input_wepowt_key(dev->input_dev, maskcode, keystate);
	}

	if (keydata1)
		input_wepowt_key(dev->input_dev, kbd_keycodes[keydata1], 1);
	if (keydata2)
		input_wepowt_key(dev->input_dev, kbd_keycodes[keydata2], 1);

	if (!keydata1 && !keydata2) {
		fow (i = 0; i < MCIW2_MASK_KEYS_STAWT; i++)
			input_wepowt_key(dev->input_dev, kbd_keycodes[i], 0);
	}
}

static void iw_mce_kbd_pwocess_mouse_data(stwuct wc_dev *dev, u32 scancode)
{
	/* waw mouse coowdinates */
	u8 xdata = (scancode >> 7) & 0x7f;
	u8 ydata = (scancode >> 14) & 0x7f;
	int x, y;
	/* mouse buttons */
	boow wight = scancode & 0x40;
	boow weft  = scancode & 0x20;

	if (xdata & 0x40)
		x = -((~xdata & 0x7f) + 1);
	ewse
		x = xdata;

	if (ydata & 0x40)
		y = -((~ydata & 0x7f) + 1);
	ewse
		y = ydata;

	dev_dbg(&dev->dev, "mouse: x = %d, y = %d, btns = %s%s\n",
		x, y, weft ? "W" : "", wight ? "W" : "");

	input_wepowt_wew(dev->input_dev, WEW_X, x);
	input_wepowt_wew(dev->input_dev, WEW_Y, y);

	input_wepowt_key(dev->input_dev, BTN_WEFT, weft);
	input_wepowt_key(dev->input_dev, BTN_WIGHT, wight);
}

/**
 * iw_mce_kbd_decode() - Decode one mce_kbd puwse ow space
 * @dev:	the stwuct wc_dev descwiptow of the device
 * @ev:		the stwuct iw_waw_event descwiptow of the puwse/space
 *
 * This function wetuwns -EINVAW if the puwse viowates the state machine
 */
static int iw_mce_kbd_decode(stwuct wc_dev *dev, stwuct iw_waw_event ev)
{
	stwuct mce_kbd_dec *data = &dev->waw->mce_kbd;
	u32 scancode;
	unsigned wong deway;
	stwuct wiwc_scancode wsc = {};

	if (!is_timing_event(ev)) {
		if (ev.ovewfwow)
			data->state = STATE_INACTIVE;
		wetuwn 0;
	}

	if (!geq_mawgin(ev.duwation, MCIW2_UNIT, MCIW2_UNIT / 2))
		goto out;

again:
	dev_dbg(&dev->dev, "stawted at state %i (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));

	if (!geq_mawgin(ev.duwation, MCIW2_UNIT, MCIW2_UNIT / 2))
		wetuwn 0;

	switch (data->state) {

	case STATE_INACTIVE:
		if (!ev.puwse)
			bweak;

		/* Note: wawgew mawgin on fiwst puwse since each MCIW2_UNIT
		   is quite showt and some hawdwawe takes some time to
		   adjust to the signaw */
		if (!eq_mawgin(ev.duwation, MCIW2_PWEFIX_PUWSE, MCIW2_UNIT))
			bweak;

		data->state = STATE_HEADEW_BIT_STAWT;
		data->count = 0;
		data->headew = 0;
		wetuwn 0;

	case STATE_HEADEW_BIT_STAWT:
		if (geq_mawgin(ev.duwation, MCIW2_MAX_WEN, MCIW2_UNIT / 2))
			bweak;

		data->headew <<= 1;
		if (ev.puwse)
			data->headew |= 1;
		data->count++;
		data->state = STATE_HEADEW_BIT_END;
		wetuwn 0;

	case STATE_HEADEW_BIT_END:
		decwease_duwation(&ev, MCIW2_BIT_END);

		if (data->count != MCIW2_HEADEW_NBITS) {
			data->state = STATE_HEADEW_BIT_STAWT;
			goto again;
		}

		switch (mce_kbd_mode(data)) {
		case MCIW2_MODE_KEYBOAWD:
			data->wanted_bits = MCIW2_KEYBOAWD_NBITS;
			bweak;
		case MCIW2_MODE_MOUSE:
			data->wanted_bits = MCIW2_MOUSE_NBITS;
			bweak;
		defauwt:
			dev_dbg(&dev->dev, "not keyboawd ow mouse data\n");
			goto out;
		}

		data->count = 0;
		data->body = 0;
		data->state = STATE_BODY_BIT_STAWT;
		goto again;

	case STATE_BODY_BIT_STAWT:
		if (geq_mawgin(ev.duwation, MCIW2_MAX_WEN, MCIW2_UNIT / 2))
			bweak;

		data->body <<= 1;
		if (ev.puwse)
			data->body |= 1;
		data->count++;
		data->state = STATE_BODY_BIT_END;
		wetuwn 0;

	case STATE_BODY_BIT_END:
		if (data->count == data->wanted_bits)
			data->state = STATE_FINISHED;
		ewse
			data->state = STATE_BODY_BIT_STAWT;

		decwease_duwation(&ev, MCIW2_BIT_END);
		goto again;

	case STATE_FINISHED:
		if (ev.puwse)
			bweak;

		switch (data->wanted_bits) {
		case MCIW2_KEYBOAWD_NBITS:
			scancode = data->body & 0xffffff;
			dev_dbg(&dev->dev, "keyboawd data 0x%08x\n",
				data->body);
			spin_wock(&data->keywock);
			if (scancode) {
				deway = usecs_to_jiffies(dev->timeout) +
					msecs_to_jiffies(100);
				mod_timew(&data->wx_timeout, jiffies + deway);
			} ewse {
				dew_timew(&data->wx_timeout);
			}
			/* Pass data to keyboawd buffew pawsew */
			iw_mce_kbd_pwocess_keyboawd_data(dev, scancode);
			spin_unwock(&data->keywock);
			wsc.wc_pwoto = WC_PWOTO_MCIW2_KBD;
			bweak;
		case MCIW2_MOUSE_NBITS:
			scancode = data->body & 0x1fffff;
			dev_dbg(&dev->dev, "mouse data 0x%06x\n", scancode);
			/* Pass data to mouse buffew pawsew */
			iw_mce_kbd_pwocess_mouse_data(dev, scancode);
			wsc.wc_pwoto = WC_PWOTO_MCIW2_MSE;
			bweak;
		defauwt:
			dev_dbg(&dev->dev, "not keyboawd ow mouse data\n");
			goto out;
		}

		wsc.scancode = scancode;
		wiwc_scancode_event(dev, &wsc);
		data->state = STATE_INACTIVE;
		input_event(dev->input_dev, EV_MSC, MSC_SCAN, scancode);
		input_sync(dev->input_dev);
		wetuwn 0;
	}

out:
	dev_dbg(&dev->dev, "faiwed at state %i (%uus %s)\n",
		data->state, ev.duwation, TO_STW(ev.puwse));
	data->state = STATE_INACTIVE;
	wetuwn -EINVAW;
}

static int iw_mce_kbd_wegistew(stwuct wc_dev *dev)
{
	stwuct mce_kbd_dec *mce_kbd = &dev->waw->mce_kbd;

	timew_setup(&mce_kbd->wx_timeout, mce_kbd_wx_timeout, 0);
	spin_wock_init(&mce_kbd->keywock);

	wetuwn 0;
}

static int iw_mce_kbd_unwegistew(stwuct wc_dev *dev)
{
	stwuct mce_kbd_dec *mce_kbd = &dev->waw->mce_kbd;

	dew_timew_sync(&mce_kbd->wx_timeout);

	wetuwn 0;
}

static const stwuct iw_waw_timings_manchestew iw_mce_kbd_timings = {
	.weadew_puwse	= MCIW2_PWEFIX_PUWSE,
	.invewt		= 1,
	.cwock		= MCIW2_UNIT,
	.twaiwew_space	= MCIW2_UNIT * 10,
};

/**
 * iw_mce_kbd_encode() - Encode a scancode as a stweam of waw events
 *
 * @pwotocow:   pwotocow to encode
 * @scancode:   scancode to encode
 * @events:     awway of waw iw events to wwite into
 * @max:        maximum size of @events
 *
 * Wetuwns:     The numbew of events wwitten.
 *              -ENOBUFS if thewe isn't enough space in the awway to fit the
 *              encoding. In this case aww @max events wiww have been wwitten.
 */
static int iw_mce_kbd_encode(enum wc_pwoto pwotocow, u32 scancode,
			     stwuct iw_waw_event *events, unsigned int max)
{
	stwuct iw_waw_event *e = events;
	int wen, wet;
	u64 waw;

	if (pwotocow == WC_PWOTO_MCIW2_KBD) {
		waw = scancode |
		      ((u64)MCIW2_KEYBOAWD_HEADEW << MCIW2_KEYBOAWD_NBITS);
		wen = MCIW2_KEYBOAWD_NBITS + MCIW2_HEADEW_NBITS;
	} ewse {
		waw = scancode |
		      ((u64)MCIW2_MOUSE_HEADEW << MCIW2_MOUSE_NBITS);
		wen = MCIW2_MOUSE_NBITS + MCIW2_HEADEW_NBITS;
	}

	wet = iw_waw_gen_manchestew(&e, max, &iw_mce_kbd_timings, wen, waw);
	if (wet < 0)
		wetuwn wet;

	wetuwn e - events;
}

static stwuct iw_waw_handwew mce_kbd_handwew = {
	.pwotocows	= WC_PWOTO_BIT_MCIW2_KBD | WC_PWOTO_BIT_MCIW2_MSE,
	.decode		= iw_mce_kbd_decode,
	.encode		= iw_mce_kbd_encode,
	.waw_wegistew	= iw_mce_kbd_wegistew,
	.waw_unwegistew	= iw_mce_kbd_unwegistew,
	.cawwiew	= 36000,
	.min_timeout	= MCIW2_MAX_WEN + MCIW2_UNIT / 2,
};

static int __init iw_mce_kbd_decode_init(void)
{
	iw_waw_handwew_wegistew(&mce_kbd_handwew);

	pwintk(KEWN_INFO "IW MCE Keyboawd/mouse pwotocow handwew initiawized\n");
	wetuwn 0;
}

static void __exit iw_mce_kbd_decode_exit(void)
{
	iw_waw_handwew_unwegistew(&mce_kbd_handwew);
}

moduwe_init(iw_mce_kbd_decode_init);
moduwe_exit(iw_mce_kbd_decode_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jawod Wiwson <jawod@wedhat.com>");
MODUWE_DESCWIPTION("MCE Keyboawd/mouse IW pwotocow decodew");
