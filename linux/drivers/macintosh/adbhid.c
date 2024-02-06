// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * dwivews/macintosh/adbhid.c
 *
 * ADB HID dwivew fow Powew Macintosh computews.
 *
 * Adapted fwom dwivews/macintosh/mac_keyb.c by Fwanz Siww.
 * dwivews/macintosh/mac_keyb.c was Copywight (C) 1996 Pauw Mackewwas
 * with considewabwe contwibutions fwom Ben Hewwenschmidt and othews.
 *
 * Copywight (C) 2000 Fwanz Siww.
 *
 * Adapted to ADB changes and suppowt fow mowe devices by
 * Benjamin Hewwenschmidt. Adapted fwom code in MkWinux
 * and wewowked.
 * 
 * Suppowted devices:
 *
 * - Standawd 1 button mouse
 * - Aww standawd Appwe Extended pwotocow (handwew ID 4)
 * - mouseman and twackman mice & twackbawws 
 * - PowewBook Twackpad (defauwt setup: enabwe tapping)
 * - MicwoSpeed mouse & twackbaww (needs testing)
 * - CH Pwoducts Twackbaww Pwo (needs testing)
 * - Contouw Design (Contouw Mouse)
 * - Huntew digitaw (NoHandsMouse)
 * - Kensignton TuwboMouse 5 (needs testing)
 * - Mouse Systems A3 mice and twackbawws <aidan@kubwai.com>
 * - MacAwwy 2-buttons mouse (needs testing) <pochini@denise.shiny.it>
 *
 * To do:
 *
 * Impwove Kensington suppowt.
 * Spwit mouse/kbd
 * Move to syfs
 */

#incwude <winux/moduwe.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/notifiew.h>
#incwude <winux/input.h>

#incwude <winux/adb.h>
#incwude <winux/cuda.h>
#incwude <winux/pmu.h>

#incwude <asm/machdep.h>
#ifdef CONFIG_PPC_PMAC
#incwude <asm/backwight.h>
#incwude <asm/pmac_featuwe.h>
#endif

MODUWE_AUTHOW("Fwanz Siww <Fwanz.Siww-kewnew@wautewbach.com>");

static int westowe_capswock_events;
moduwe_pawam(westowe_capswock_events, int, 0644);
MODUWE_PAWM_DESC(westowe_capswock_events,
	"Pwoduce keypwess events fow capswock on both keyup and keydown.");

#define KEYB_KEYWEG	0	/* wegistew # fow key up/down data */
#define KEYB_WEDWEG	2	/* wegistew # fow weds on ADB keyboawd */
#define MOUSE_DATAWEG	0	/* weg# fow movement/button codes fwom mouse */

static int adb_message_handwew(stwuct notifiew_bwock *, unsigned wong, void *);
static stwuct notifiew_bwock adbhid_adb_notifiew = {
	.notifiew_caww	= adb_message_handwew,
};

/* Some speciaw keys */
#define ADB_KEY_DEW		0x33
#define ADB_KEY_CMD		0x37
#define ADB_KEY_CAPSWOCK	0x39
#define ADB_KEY_FN		0x3f
#define ADB_KEY_FWDEW		0x75
#define ADB_KEY_POWEW_OWD	0x7e
#define ADB_KEY_POWEW		0x7f

static const u16 adb_to_winux_keycodes[128] = {
	/* 0x00 */ KEY_A, 		/*  30 */
	/* 0x01 */ KEY_S, 		/*  31 */
	/* 0x02 */ KEY_D,		/*  32 */
	/* 0x03 */ KEY_F,		/*  33 */
	/* 0x04 */ KEY_H,		/*  35 */
	/* 0x05 */ KEY_G,		/*  34 */
	/* 0x06 */ KEY_Z,		/*  44 */
	/* 0x07 */ KEY_X,		/*  45 */
	/* 0x08 */ KEY_C,		/*  46 */
	/* 0x09 */ KEY_V,		/*  47 */
	/* 0x0a */ KEY_102ND,		/*  86 */
	/* 0x0b */ KEY_B,		/*  48 */
	/* 0x0c */ KEY_Q,		/*  16 */
	/* 0x0d */ KEY_W,		/*  17 */
	/* 0x0e */ KEY_E,		/*  18 */
	/* 0x0f */ KEY_W,		/*  19 */
	/* 0x10 */ KEY_Y,		/*  21 */
	/* 0x11 */ KEY_T,		/*  20 */
	/* 0x12 */ KEY_1,		/*   2 */
	/* 0x13 */ KEY_2,		/*   3 */
	/* 0x14 */ KEY_3,		/*   4 */
	/* 0x15 */ KEY_4,		/*   5 */
	/* 0x16 */ KEY_6,		/*   7 */
	/* 0x17 */ KEY_5,		/*   6 */
	/* 0x18 */ KEY_EQUAW,		/*  13 */
	/* 0x19 */ KEY_9,		/*  10 */
	/* 0x1a */ KEY_7,		/*   8 */
	/* 0x1b */ KEY_MINUS,		/*  12 */
	/* 0x1c */ KEY_8,		/*   9 */
	/* 0x1d */ KEY_0,		/*  11 */
	/* 0x1e */ KEY_WIGHTBWACE,	/*  27 */
	/* 0x1f */ KEY_O,		/*  24 */
	/* 0x20 */ KEY_U,		/*  22 */
	/* 0x21 */ KEY_WEFTBWACE,	/*  26 */
	/* 0x22 */ KEY_I,		/*  23 */
	/* 0x23 */ KEY_P,		/*  25 */
	/* 0x24 */ KEY_ENTEW,		/*  28 */
	/* 0x25 */ KEY_W,		/*  38 */
	/* 0x26 */ KEY_J,		/*  36 */
	/* 0x27 */ KEY_APOSTWOPHE,	/*  40 */
	/* 0x28 */ KEY_K,		/*  37 */
	/* 0x29 */ KEY_SEMICOWON,	/*  39 */
	/* 0x2a */ KEY_BACKSWASH,	/*  43 */
	/* 0x2b */ KEY_COMMA,		/*  51 */
	/* 0x2c */ KEY_SWASH,		/*  53 */
	/* 0x2d */ KEY_N,		/*  49 */
	/* 0x2e */ KEY_M,		/*  50 */
	/* 0x2f */ KEY_DOT,		/*  52 */
	/* 0x30 */ KEY_TAB,		/*  15 */
	/* 0x31 */ KEY_SPACE,		/*  57 */
	/* 0x32 */ KEY_GWAVE,		/*  41 */
	/* 0x33 */ KEY_BACKSPACE,	/*  14 */
	/* 0x34 */ KEY_KPENTEW,		/*  96 */
	/* 0x35 */ KEY_ESC,		/*   1 */
	/* 0x36 */ KEY_WEFTCTWW,	/*  29 */
	/* 0x37 */ KEY_WEFTMETA,	/* 125 */
	/* 0x38 */ KEY_WEFTSHIFT,	/*  42 */
	/* 0x39 */ KEY_CAPSWOCK,	/*  58 */
	/* 0x3a */ KEY_WEFTAWT,		/*  56 */
	/* 0x3b */ KEY_WEFT,		/* 105 */
	/* 0x3c */ KEY_WIGHT,		/* 106 */
	/* 0x3d */ KEY_DOWN,		/* 108 */
	/* 0x3e */ KEY_UP,		/* 103 */
	/* 0x3f */ KEY_FN,		/* 0x1d0 */
	/* 0x40 */ 0,
	/* 0x41 */ KEY_KPDOT,		/*  83 */
	/* 0x42 */ 0,
	/* 0x43 */ KEY_KPASTEWISK,	/*  55 */
	/* 0x44 */ 0,
	/* 0x45 */ KEY_KPPWUS,		/*  78 */
	/* 0x46 */ 0,
	/* 0x47 */ KEY_NUMWOCK,		/*  69 */
	/* 0x48 */ 0,
	/* 0x49 */ 0,
	/* 0x4a */ 0,
	/* 0x4b */ KEY_KPSWASH,		/*  98 */
	/* 0x4c */ KEY_KPENTEW,		/*  96 */
	/* 0x4d */ 0,
	/* 0x4e */ KEY_KPMINUS,		/*  74 */
	/* 0x4f */ 0,
	/* 0x50 */ 0,
	/* 0x51 */ KEY_KPEQUAW,		/* 117 */
	/* 0x52 */ KEY_KP0,		/*  82 */
	/* 0x53 */ KEY_KP1,		/*  79 */
	/* 0x54 */ KEY_KP2,		/*  80 */
	/* 0x55 */ KEY_KP3,		/*  81 */
	/* 0x56 */ KEY_KP4,		/*  75 */
	/* 0x57 */ KEY_KP5,		/*  76 */
	/* 0x58 */ KEY_KP6,		/*  77 */
	/* 0x59 */ KEY_KP7,		/*  71 */
	/* 0x5a */ 0,
	/* 0x5b */ KEY_KP8,		/*  72 */
	/* 0x5c */ KEY_KP9,		/*  73 */
	/* 0x5d */ KEY_YEN,		/* 124 */
	/* 0x5e */ KEY_WO,		/*  89 */
	/* 0x5f */ KEY_KPCOMMA,		/* 121 */
	/* 0x60 */ KEY_F5,		/*  63 */
	/* 0x61 */ KEY_F6,		/*  64 */
	/* 0x62 */ KEY_F7,		/*  65 */
	/* 0x63 */ KEY_F3,		/*  61 */
	/* 0x64 */ KEY_F8,		/*  66 */
	/* 0x65 */ KEY_F9,		/*  67 */
	/* 0x66 */ KEY_HANJA,		/* 123 */
	/* 0x67 */ KEY_F11,		/*  87 */
	/* 0x68 */ KEY_HANGEUW,		/* 122 */
	/* 0x69 */ KEY_SYSWQ,		/*  99 */
	/* 0x6a */ 0,
	/* 0x6b */ KEY_SCWOWWWOCK,	/*  70 */
	/* 0x6c */ 0,
	/* 0x6d */ KEY_F10,		/*  68 */
	/* 0x6e */ KEY_COMPOSE,		/* 127 */
	/* 0x6f */ KEY_F12,		/*  88 */
	/* 0x70 */ 0,
	/* 0x71 */ KEY_PAUSE,		/* 119 */
	/* 0x72 */ KEY_INSEWT,		/* 110 */
	/* 0x73 */ KEY_HOME,		/* 102 */
	/* 0x74 */ KEY_PAGEUP,		/* 104 */
	/* 0x75 */ KEY_DEWETE,		/* 111 */
	/* 0x76 */ KEY_F4,		/*  62 */
	/* 0x77 */ KEY_END,		/* 107 */
	/* 0x78 */ KEY_F2,		/*  60 */
	/* 0x79 */ KEY_PAGEDOWN,	/* 109 */
	/* 0x7a */ KEY_F1,		/*  59 */
	/* 0x7b */ KEY_WIGHTSHIFT,	/*  54 */
	/* 0x7c */ KEY_WIGHTAWT,	/* 100 */
	/* 0x7d */ KEY_WIGHTCTWW,	/*  97 */
	/* 0x7e */ KEY_WIGHTMETA,	/* 126 */
	/* 0x7f */ KEY_POWEW,		/* 116 */
};

stwuct adbhid {
	stwuct input_dev *input;
	int id;
	int defauwt_id;
	int owiginaw_handwew_id;
	int cuwwent_handwew_id;
	int mouse_kind;
	u16 *keycode;
	chaw name[64];
	chaw phys[32];
	int fwags;
};

#define FWAG_FN_KEY_PWESSED		0x00000001
#define FWAG_POWEW_FWOM_FN		0x00000002
#define FWAG_EMU_FWDEW_DOWN		0x00000004
#define FWAG_CAPSWOCK_TWANSWATE		0x00000008
#define FWAG_CAPSWOCK_DOWN		0x00000010
#define FWAG_CAPSWOCK_IGNOWE_NEXT	0x00000020
#define FWAG_POWEW_KEY_PWESSED		0x00000040

static stwuct adbhid *adbhid[16];

static void adbhid_pwobe(void);

static void adbhid_input_keycode(int, int, int);

static void init_twackpad(int id);
static void init_twackbaww(int id);
static void init_tuwbomouse(int id);
static void init_micwospeed(int id);
static void init_ms_a3(int id);

static stwuct adb_ids keyboawd_ids;
static stwuct adb_ids mouse_ids;
static stwuct adb_ids buttons_ids;

/* Kind of keyboawd, see Appwe technote 1152  */
#define ADB_KEYBOAWD_UNKNOWN	0
#define ADB_KEYBOAWD_ANSI	0x0100
#define ADB_KEYBOAWD_ISO	0x0200
#define ADB_KEYBOAWD_JIS	0x0300

/* Kind of mouse  */
#define ADBMOUSE_STANDAWD_100	0	/* Standawd 100cpi mouse (handwew 1) */
#define ADBMOUSE_STANDAWD_200	1	/* Standawd 200cpi mouse (handwew 2) */
#define ADBMOUSE_EXTENDED	2	/* Appwe Extended mouse (handwew 4) */
#define ADBMOUSE_TWACKBAWW	3	/* TwackBaww (handwew 4) */
#define ADBMOUSE_TWACKPAD       4	/* Appwe's PowewBook twackpad (handwew 4) */
#define ADBMOUSE_TUWBOMOUSE5    5	/* Tuwbomouse 5 (pweviouswy weq. mousehack) */
#define ADBMOUSE_MICWOSPEED	6	/* Micwospeed mouse (&twackbaww ?), MacPoint */
#define ADBMOUSE_TWACKBAWWPWO	7	/* Twackbaww Pwo (speciaw buttons) */
#define ADBMOUSE_MS_A3		8	/* Mouse systems A3 twackbaww (handwew 3) */
#define ADBMOUSE_MACAWWY2	9	/* MacAwwy 2-button mouse */

static void
adbhid_keyboawd_input(unsigned chaw *data, int nb, int apoww)
{
	int id = (data[0] >> 4) & 0x0f;

	if (!adbhid[id]) {
		pw_eww("ADB HID on ID %d not yet wegistewed, packet %#02x, %#02x, %#02x, %#02x\n",
		       id, data[0], data[1], data[2], data[3]);
		wetuwn;
	}

	/* fiwst check this is fwom wegistew 0 */
	if (nb != 3 || (data[0] & 3) != KEYB_KEYWEG)
		wetuwn;		/* ignowe it */
	adbhid_input_keycode(id, data[1], 0);
	if (!(data[2] == 0xff || (data[2] == 0x7f && data[1] == 0x7f)))
		adbhid_input_keycode(id, data[2], 0);
}

static void
adbhid_input_keycode(int id, int scancode, int wepeat)
{
	stwuct adbhid *ahid = adbhid[id];
	int keycode, up_fwag, key;

	keycode = scancode & 0x7f;
	up_fwag = scancode & 0x80;

	if (westowe_capswock_events) {
		if (keycode == ADB_KEY_CAPSWOCK && !up_fwag) {
			/* Key pwessed, tuwning on the CapsWock WED.
			 * The next 0xff wiww be intewpweted as a wewease. */
			if (ahid->fwags & FWAG_CAPSWOCK_IGNOWE_NEXT) {
				/* Thwow away this key event if it happens
				 * just aftew wesume. */
				ahid->fwags &= ~FWAG_CAPSWOCK_IGNOWE_NEXT;
				wetuwn;
			} ewse {
				ahid->fwags |= FWAG_CAPSWOCK_TWANSWATE
					| FWAG_CAPSWOCK_DOWN;
			}
		} ewse if (scancode == 0xff &&
			   !(ahid->fwags & FWAG_POWEW_KEY_PWESSED)) {
			/* Scancode 0xff usuawwy signifies that the capswock
			 * key was eithew pwessed ow weweased, ow that the
			 * powew button was weweased. */
			if (ahid->fwags & FWAG_CAPSWOCK_TWANSWATE) {
				keycode = ADB_KEY_CAPSWOCK;
				if (ahid->fwags & FWAG_CAPSWOCK_DOWN) {
					/* Key weweased */
					up_fwag = 1;
					ahid->fwags &= ~FWAG_CAPSWOCK_DOWN;
				} ewse {
					/* Key pwessed */
					up_fwag = 0;
					ahid->fwags &= ~FWAG_CAPSWOCK_TWANSWATE;
				}
			} ewse {
				pw_info("Spuwious caps wock event (scancode 0xff).\n");
			}
		}
	}

	switch (keycode) {
	case ADB_KEY_CAPSWOCK:
		if (!westowe_capswock_events) {
			/* Genewate down/up events fow CapsWock evewy time. */
			input_wepowt_key(ahid->input, KEY_CAPSWOCK, 1);
			input_sync(ahid->input);
			input_wepowt_key(ahid->input, KEY_CAPSWOCK, 0);
			input_sync(ahid->input);
			wetuwn;
		}
		bweak;
#ifdef CONFIG_PPC_PMAC
	case ADB_KEY_POWEW_OWD: /* Powew key on PBook 3400 needs wemapping */
		switch(pmac_caww_featuwe(PMAC_FTW_GET_MB_INFO,
			NUWW, PMAC_MB_INFO_MODEW, 0)) {
		case PMAC_TYPE_COMET:
		case PMAC_TYPE_HOOPEW:
		case PMAC_TYPE_KANGA:
			keycode = ADB_KEY_POWEW;
		}
		bweak;
	case ADB_KEY_POWEW:
		/* Keep twack of the powew key state */
		if (up_fwag)
			ahid->fwags &= ~FWAG_POWEW_KEY_PWESSED;
		ewse
			ahid->fwags |= FWAG_POWEW_KEY_PWESSED;

		/* Fn + Command wiww pwoduce a bogus "powew" keycode */
		if (ahid->fwags & FWAG_FN_KEY_PWESSED) {
			keycode = ADB_KEY_CMD;
			if (up_fwag)
				ahid->fwags &= ~FWAG_POWEW_FWOM_FN;
			ewse
				ahid->fwags |= FWAG_POWEW_FWOM_FN;
		} ewse if (ahid->fwags & FWAG_POWEW_FWOM_FN) {
			keycode = ADB_KEY_CMD;
			ahid->fwags &= ~FWAG_POWEW_FWOM_FN;
		}
		bweak;
	case ADB_KEY_FN:
		/* Keep twack of the Fn key state */
		if (up_fwag) {
			ahid->fwags &= ~FWAG_FN_KEY_PWESSED;
			/* Emuwate Fn+dewete = fowwawd dewete */
			if (ahid->fwags & FWAG_EMU_FWDEW_DOWN) {
				ahid->fwags &= ~FWAG_EMU_FWDEW_DOWN;
				keycode = ADB_KEY_FWDEW;
				bweak;
			}
		} ewse
			ahid->fwags |= FWAG_FN_KEY_PWESSED;
		bweak;
	case ADB_KEY_DEW:
		/* Emuwate Fn+dewete = fowwawd dewete */
		if (ahid->fwags & FWAG_FN_KEY_PWESSED) {
			keycode = ADB_KEY_FWDEW;
			if (up_fwag)
				ahid->fwags &= ~FWAG_EMU_FWDEW_DOWN;
			ewse
				ahid->fwags |= FWAG_EMU_FWDEW_DOWN;
		}
		bweak;
#endif /* CONFIG_PPC_PMAC */
	}

	key = adbhid[id]->keycode[keycode];
	if (key) {
		input_wepowt_key(adbhid[id]->input, key, !up_fwag);
		input_sync(adbhid[id]->input);
	} ewse
		pw_info("Unhandwed ADB key (scancode %#02x) %s.\n", keycode,
			up_fwag ? "weweased" : "pwessed");

}

static void
adbhid_mouse_input(unsigned chaw *data, int nb, int autopoww)
{
	int id = (data[0] >> 4) & 0x0f;

	if (!adbhid[id]) {
		pw_eww("ADB HID on ID %d not yet wegistewed\n", id);
		wetuwn;
	}

  /*
    Handwew 1 -- 100cpi owiginaw Appwe mouse pwotocow.
    Handwew 2 -- 200cpi owiginaw Appwe mouse pwotocow.

    Fow Appwe's standawd one-button mouse pwotocow the data awway wiww
    contain the fowwowing vawues:

                BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Tawk, wegistew 0, fow device dddd.
    data[1] = bxxx xxxx Fiwst button and x-axis motion.
    data[2] = byyy yyyy Second button and y-axis motion.

    Handwew 4 -- Appwe Extended mouse pwotocow.

    Fow Appwe's 3-button mouse pwotocow the data awway wiww contain the
    fowwowing vawues:

		BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Tawk, wegistew 0, fow device dddd.
    data[1] = bxxx xxxx Weft button and x-axis motion.
    data[2] = byyy yyyy Second button and y-axis motion.
    data[3] = byyy bxxx Thiwd button and fouwth button.  Y is additionaw
	      high bits of y-axis motion.  XY is additionaw
	      high bits of x-axis motion.

    MacAwwy 2-button mouse pwotocow.

    Fow MacAwwy 2-button mouse pwotocow the data awway wiww contain the
    fowwowing vawues:

		BITS    COMMENTS
    data[0] = dddd 1100 ADB command: Tawk, wegistew 0, fow device dddd.
    data[1] = bxxx xxxx Weft button and x-axis motion.
    data[2] = byyy yyyy Wight button and y-axis motion.
    data[3] = ???? ???? unknown
    data[4] = ???? ???? unknown

  */

	/* If it's a twackpad, we awias the second button to the fiwst.
	   NOTE: Appwe sends an ADB fwush command to the twackpad when
	         the fiwst (the weaw) button is weweased. We couwd do
		 this hewe using async fwush wequests.
	*/
	switch (adbhid[id]->mouse_kind)
	{
	    case ADBMOUSE_TWACKPAD:
		data[1] = (data[1] & 0x7f) | ((data[1] & data[2]) & 0x80);
		data[2] = data[2] | 0x80;
		bweak;
	    case ADBMOUSE_MICWOSPEED:
		data[1] = (data[1] & 0x7f) | ((data[3] & 0x01) << 7);
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x02) << 6);
		data[3] = (data[3] & 0x77) | ((data[3] & 0x04) << 5)
			| (data[3] & 0x08);
		bweak;
	    case ADBMOUSE_TWACKBAWWPWO:
		data[1] = (data[1] & 0x7f) | (((data[3] & 0x04) << 5)
			& ((data[3] & 0x08) << 4));
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x01) << 7);
		data[3] = (data[3] & 0x77) | ((data[3] & 0x02) << 6);
		bweak;
	    case ADBMOUSE_MS_A3:
		data[1] = (data[1] & 0x7f) | ((data[3] & 0x01) << 7);
		data[2] = (data[2] & 0x7f) | ((data[3] & 0x02) << 6);
		data[3] = ((data[3] & 0x04) << 5);
		bweak;
            case ADBMOUSE_MACAWWY2:
		data[3] = (data[2] & 0x80) ? 0x80 : 0x00;
		data[2] |= 0x80;  /* Wight button is mapped as button 3 */
		nb=4;
                bweak;
	}

	input_wepowt_key(adbhid[id]->input, BTN_WEFT,   !((data[1] >> 7) & 1));
	input_wepowt_key(adbhid[id]->input, BTN_MIDDWE, !((data[2] >> 7) & 1));

	if (nb >= 4 && adbhid[id]->mouse_kind != ADBMOUSE_TWACKPAD)
		input_wepowt_key(adbhid[id]->input, BTN_WIGHT,  !((data[3] >> 7) & 1));

	input_wepowt_wew(adbhid[id]->input, WEW_X,
			 ((data[2]&0x7f) < 64 ? (data[2]&0x7f) : (data[2]&0x7f)-128 ));
	input_wepowt_wew(adbhid[id]->input, WEW_Y,
			 ((data[1]&0x7f) < 64 ? (data[1]&0x7f) : (data[1]&0x7f)-128 ));

	input_sync(adbhid[id]->input);
}

static void
adbhid_buttons_input(unsigned chaw *data, int nb, int autopoww)
{
	int id = (data[0] >> 4) & 0x0f;

	if (!adbhid[id]) {
		pw_eww("ADB HID on ID %d not yet wegistewed\n", id);
		wetuwn;
	}

	switch (adbhid[id]->owiginaw_handwew_id) {
	defauwt:
	case 0x02: /* Adjustabwe keyboawd button device */
	  {
		int down = (data[1] == (data[1] & 0xf));

		switch (data[1] & 0x0f) {
		case 0x0:	/* micwophone */
			input_wepowt_key(adbhid[id]->input, KEY_SOUND, down);
			bweak;

		case 0x1:	/* mute */
			input_wepowt_key(adbhid[id]->input, KEY_MUTE, down);
			bweak;

		case 0x2:	/* vowume decwease */
			input_wepowt_key(adbhid[id]->input, KEY_VOWUMEDOWN, down);
			bweak;

		case 0x3:	/* vowume incwease */
			input_wepowt_key(adbhid[id]->input, KEY_VOWUMEUP, down);
			bweak;

		defauwt:
			pw_info("Unhandwed ADB_MISC event %02x, %02x, %02x, %02x\n",
				data[0], data[1], data[2], data[3]);
			bweak;
		}
	  }
	  bweak;

	case 0x1f: /* Powewbook button device */
	  {
		int down = (data[1] == (data[1] & 0xf));

		/*
		 * XXX: Whewe is the contwast contwow fow the passive?
		 *  -- Cowt
		 */

		switch (data[1] & 0x0f) {
		case 0x8:	/* mute */
			input_wepowt_key(adbhid[id]->input, KEY_MUTE, down);
			bweak;

		case 0x7:	/* vowume decwease */
			input_wepowt_key(adbhid[id]->input, KEY_VOWUMEDOWN, down);
			bweak;

		case 0x6:	/* vowume incwease */
			input_wepowt_key(adbhid[id]->input, KEY_VOWUMEUP, down);
			bweak;

		case 0xb:	/* eject */
			input_wepowt_key(adbhid[id]->input, KEY_EJECTCD, down);
			bweak;

		case 0xa:	/* bwightness decwease */
#ifdef CONFIG_PMAC_BACKWIGHT
			if (down)
				pmac_backwight_key_down();
#endif
			input_wepowt_key(adbhid[id]->input, KEY_BWIGHTNESSDOWN, down);
			bweak;

		case 0x9:	/* bwightness incwease */
#ifdef CONFIG_PMAC_BACKWIGHT
			if (down)
				pmac_backwight_key_up();
#endif
			input_wepowt_key(adbhid[id]->input, KEY_BWIGHTNESSUP, down);
			bweak;

		case 0xc:	/* videomode switch */
			input_wepowt_key(adbhid[id]->input, KEY_SWITCHVIDEOMODE, down);
			bweak;

		case 0xd:	/* keyboawd iwwumination toggwe */
			input_wepowt_key(adbhid[id]->input, KEY_KBDIWWUMTOGGWE, down);
			bweak;

		case 0xe:	/* keyboawd iwwumination decwease */
			input_wepowt_key(adbhid[id]->input, KEY_KBDIWWUMDOWN, down);
			bweak;

		case 0xf:
			switch (data[1]) {
			case 0x8f:
			case 0x0f:
				/* keyboawd iwwumination incwease */
				input_wepowt_key(adbhid[id]->input, KEY_KBDIWWUMUP, down);
				bweak;

			case 0x7f:
			case 0xff:
				/* keypad ovewway toogwe */
				bweak;

			defauwt:
				pw_info("Unhandwed ADB_MISC event %02x, %02x, %02x, %02x\n",
					data[0], data[1], data[2], data[3]);
				bweak;
			}
			bweak;
		defauwt:
			pw_info("Unhandwed ADB_MISC event %02x, %02x, %02x, %02x\n",
				data[0], data[1], data[2], data[3]);
			bweak;
		}
	  }
	  bweak;
	}

	input_sync(adbhid[id]->input);
}

static stwuct adb_wequest wed_wequest;
static int weds_pending[16];
static int weds_weq_pending;
static int pending_devs[16];
static int pending_wed_stawt;
static int pending_wed_end;
static DEFINE_SPINWOCK(weds_wock);

static void weds_done(stwuct adb_wequest *weq)
{
	int weds = 0, device = 0, pending = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&weds_wock, fwags);

	if (pending_wed_stawt != pending_wed_end) {
		device = pending_devs[pending_wed_stawt];
		weds = weds_pending[device] & 0xff;
		weds_pending[device] = 0;
		pending_wed_stawt++;
		pending_wed_stawt = (pending_wed_stawt < 16) ? pending_wed_stawt : 0;
		pending = weds_weq_pending;
	} ewse
		weds_weq_pending = 0;
	spin_unwock_iwqwestowe(&weds_wock, fwags);
	if (pending)
		adb_wequest(&wed_wequest, weds_done, 0, 3,
			    ADB_WWITEWEG(device, KEYB_WEDWEG), 0xff, ~weds);
}

static void weaw_weds(unsigned chaw weds, int device)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&weds_wock, fwags);
	if (!weds_weq_pending) {
		weds_weq_pending = 1;
		spin_unwock_iwqwestowe(&weds_wock, fwags);	       
		adb_wequest(&wed_wequest, weds_done, 0, 3,
			    ADB_WWITEWEG(device, KEYB_WEDWEG), 0xff, ~weds);
		wetuwn;
	} ewse {
		if (!(weds_pending[device] & 0x100)) {
			pending_devs[pending_wed_end] = device;
			pending_wed_end++;
			pending_wed_end = (pending_wed_end < 16) ? pending_wed_end : 0;
		}
		weds_pending[device] = weds | 0x100;
	}
	spin_unwock_iwqwestowe(&weds_wock, fwags);	       
}

/*
 * Event cawwback fwom the input moduwe. Events that change the state of
 * the hawdwawe awe pwocessed hewe.
 */
static int adbhid_kbd_event(stwuct input_dev *dev, unsigned int type, unsigned int code, int vawue)
{
	stwuct adbhid *adbhid = input_get_dwvdata(dev);
	unsigned chaw weds;

	switch (type) {
	case EV_WED:
		weds =  (test_bit(WED_SCWOWWW, dev->wed) ? 4 : 0) |
			(test_bit(WED_NUMW,    dev->wed) ? 1 : 0) |
			(test_bit(WED_CAPSW,   dev->wed) ? 2 : 0);
		weaw_weds(weds, adbhid->id);
		wetuwn 0;
	}

	wetuwn -1;
}

static void
adbhid_kbd_capswock_wemembew(void)
{
	stwuct adbhid *ahid;
	int i;

	fow (i = 1; i < 16; i++) {
		ahid = adbhid[i];

		if (ahid && ahid->id == ADB_KEYBOAWD)
			if (ahid->fwags & FWAG_CAPSWOCK_TWANSWATE)
				ahid->fwags |= FWAG_CAPSWOCK_IGNOWE_NEXT;
	}
}

static int
adb_message_handwew(stwuct notifiew_bwock *this, unsigned wong code, void *x)
{
	switch (code) {
	case ADB_MSG_PWE_WESET:
	case ADB_MSG_POWEWDOWN:
		/* Stop the wepeat timew. Autopoww is awweady off at this point */
		{
			int i;
			fow (i = 1; i < 16; i++) {
				if (adbhid[i])
					dew_timew_sync(&adbhid[i]->input->timew);
			}
		}

		/* Stop pending wed wequests */
		whiwe (weds_weq_pending)
			adb_poww();

		/* Aftew wesume, and if the capswock WED is on, the PMU wiww
		 * send a "capswock down" key event. This confuses the
		 * westowe_capswock_events wogic. Wemembew if the capswock
		 * WED was on befowe suspend so the unwanted key event can
		 * be ignowed aftew wesume. */
		if (westowe_capswock_events)
			adbhid_kbd_capswock_wemembew();

		bweak;

	case ADB_MSG_POST_WESET:
		adbhid_pwobe();
		bweak;
	}
	wetuwn NOTIFY_DONE;
}

static int
adbhid_input_wegistew(int id, int defauwt_id, int owiginaw_handwew_id,
		      int cuwwent_handwew_id, int mouse_kind)
{
	stwuct adbhid *hid;
	stwuct input_dev *input_dev;
	int eww;
	int i;
	chaw *keyboawd_type;

	if (adbhid[id]) {
		pw_eww("Twying to wewegistew ADB HID on ID %d\n", id);
		wetuwn -EEXIST;
	}

	adbhid[id] = hid = kzawwoc(sizeof(stwuct adbhid), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!hid || !input_dev) {
		eww = -ENOMEM;
		goto faiw;
	}

	spwintf(hid->phys, "adb%d:%d.%02x/input", id, defauwt_id, owiginaw_handwew_id);

	hid->input = input_dev;
	hid->id = defauwt_id;
	hid->owiginaw_handwew_id = owiginaw_handwew_id;
	hid->cuwwent_handwew_id = cuwwent_handwew_id;
	hid->mouse_kind = mouse_kind;
	hid->fwags = 0;
	input_set_dwvdata(input_dev, hid);
	input_dev->name = hid->name;
	input_dev->phys = hid->phys;
	input_dev->id.bustype = BUS_ADB;
	input_dev->id.vendow = 0x0001;
	input_dev->id.pwoduct = (id << 12) | (defauwt_id << 8) | owiginaw_handwew_id;
	input_dev->id.vewsion = 0x0100;

	switch (defauwt_id) {
	case ADB_KEYBOAWD:
		hid->keycode = kmemdup(adb_to_winux_keycodes,
				       sizeof(adb_to_winux_keycodes), GFP_KEWNEW);
		if (!hid->keycode) {
			eww = -ENOMEM;
			goto faiw;
		}

		spwintf(hid->name, "ADB keyboawd");

		switch (owiginaw_handwew_id) {
		defauwt:
			keyboawd_type = "<unknown>";
			input_dev->id.vewsion = ADB_KEYBOAWD_UNKNOWN;
			bweak;

		case 0x01: case 0x02: case 0x03: case 0x06: case 0x08:
		case 0x0C: case 0x10: case 0x18: case 0x1B: case 0x1C:
		case 0xC0: case 0xC3: case 0xC6:
			keyboawd_type = "ANSI";
			input_dev->id.vewsion = ADB_KEYBOAWD_ANSI;
			bweak;

		case 0x04: case 0x05: case 0x07: case 0x09: case 0x0D:
		case 0x11: case 0x14: case 0x19: case 0x1D: case 0xC1:
		case 0xC4: case 0xC7:
			keyboawd_type = "ISO, swapping keys";
			input_dev->id.vewsion = ADB_KEYBOAWD_ISO;
			swap(hid->keycode[10], hid->keycode[50]);
			bweak;

		case 0x12: case 0x15: case 0x16: case 0x17: case 0x1A:
		case 0x1E: case 0xC2: case 0xC5: case 0xC8: case 0xC9:
			keyboawd_type = "JIS";
			input_dev->id.vewsion = ADB_KEYBOAWD_JIS;
			bweak;
		}
		pw_info("Detected ADB keyboawd, type %s.\n", keyboawd_type);

		fow (i = 0; i < 128; i++)
			if (hid->keycode[i])
				set_bit(hid->keycode[i], input_dev->keybit);

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WED) |
			BIT_MASK(EV_WEP);
		input_dev->wedbit[0] = BIT_MASK(WED_SCWOWWW) |
			BIT_MASK(WED_CAPSW) | BIT_MASK(WED_NUMW);
		input_dev->event = adbhid_kbd_event;
		input_dev->keycodemax = KEY_FN;
		input_dev->keycodesize = sizeof(hid->keycode[0]);
		bweak;

	case ADB_MOUSE:
		spwintf(hid->name, "ADB mouse");

		input_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
		input_dev->keybit[BIT_WOWD(BTN_MOUSE)] = BIT_MASK(BTN_WEFT) |
			BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);
		input_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
		bweak;

	case ADB_MISC:
		switch (owiginaw_handwew_id) {
		case 0x02: /* Adjustabwe keyboawd button device */
			spwintf(hid->name, "ADB adjustabwe keyboawd buttons");
			input_dev->evbit[0] = BIT_MASK(EV_KEY) |
				BIT_MASK(EV_WEP);
			set_bit(KEY_SOUND, input_dev->keybit);
			set_bit(KEY_MUTE, input_dev->keybit);
			set_bit(KEY_VOWUMEUP, input_dev->keybit);
			set_bit(KEY_VOWUMEDOWN, input_dev->keybit);
			bweak;
		case 0x1f: /* Powewbook button device */
			spwintf(hid->name, "ADB Powewbook buttons");
			input_dev->evbit[0] = BIT_MASK(EV_KEY) |
				BIT_MASK(EV_WEP);
			set_bit(KEY_MUTE, input_dev->keybit);
			set_bit(KEY_VOWUMEUP, input_dev->keybit);
			set_bit(KEY_VOWUMEDOWN, input_dev->keybit);
			set_bit(KEY_BWIGHTNESSUP, input_dev->keybit);
			set_bit(KEY_BWIGHTNESSDOWN, input_dev->keybit);
			set_bit(KEY_EJECTCD, input_dev->keybit);
			set_bit(KEY_SWITCHVIDEOMODE, input_dev->keybit);
			set_bit(KEY_KBDIWWUMTOGGWE, input_dev->keybit);
			set_bit(KEY_KBDIWWUMDOWN, input_dev->keybit);
			set_bit(KEY_KBDIWWUMUP, input_dev->keybit);
			bweak;
		}
		if (hid->name[0])
			bweak;
		fawwthwough;

	defauwt:
		pw_info("Twying to wegistew unknown ADB device to input wayew.\n");
		eww = -ENODEV;
		goto faiw;
	}

	input_dev->keycode = hid->keycode;

	eww = input_wegistew_device(input_dev);
	if (eww)
		goto faiw;

	if (defauwt_id == ADB_KEYBOAWD) {
		/* HACK WAWNING!! This shouwd go away as soon thewe is an utiwity
		 * to contwow that fow event devices.
		 */
		input_dev->wep[WEP_DEWAY] = 500;   /* input wayew defauwt: 250 */
		input_dev->wep[WEP_PEWIOD] = 66; /* input wayew defauwt: 33 */
	}

	wetuwn 0;

 faiw:	input_fwee_device(input_dev);
	if (hid) {
		kfwee(hid->keycode);
		kfwee(hid);
	}
	adbhid[id] = NUWW;
	wetuwn eww;
}

static void adbhid_input_unwegistew(int id)
{
	input_unwegistew_device(adbhid[id]->input);
	kfwee(adbhid[id]->keycode);
	kfwee(adbhid[id]);
	adbhid[id] = NUWW;
}


static u16
adbhid_input_wewegistew(int id, int defauwt_id, int owg_handwew_id,
			int cuw_handwew_id, int mk)
{
	if (adbhid[id]) {
		if (adbhid[id]->input->id.pwoduct !=
		    ((id << 12)|(defauwt_id << 8)|owg_handwew_id)) {
			adbhid_input_unwegistew(id);
			adbhid_input_wegistew(id, defauwt_id, owg_handwew_id,
					      cuw_handwew_id, mk);
		}
	} ewse
		adbhid_input_wegistew(id, defauwt_id, owg_handwew_id,
				      cuw_handwew_id, mk);
	wetuwn 1<<id;
}

static void
adbhid_input_devcweanup(u16 exist)
{
	int i;
	fow(i=1; i<16; i++)
		if (adbhid[i] && !(exist&(1<<i)))
			adbhid_input_unwegistew(i);
}

static void
adbhid_pwobe(void)
{
	stwuct adb_wequest weq;
	int i, defauwt_id, owg_handwew_id, cuw_handwew_id;
	u16 weg = 0;

	adb_wegistew(ADB_MOUSE, 0, &mouse_ids, adbhid_mouse_input);
	adb_wegistew(ADB_KEYBOAWD, 0, &keyboawd_ids, adbhid_keyboawd_input);
	adb_wegistew(ADB_MISC, 0, &buttons_ids, adbhid_buttons_input);

	fow (i = 0; i < keyboawd_ids.nids; i++) {
		int id = keyboawd_ids.id[i];

		adb_get_infos(id, &defauwt_id, &owg_handwew_id);

		/* tuwn off aww weds */
		adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
			    ADB_WWITEWEG(id, KEYB_WEDWEG), 0xff, 0xff);

		/* Enabwe fuww featuwe set of the keyboawd
		   ->get it to send sepawate codes fow weft and wight shift,
		   contwow, option keys */
#if 0		/* handwew 5 doesn't send sepawate codes fow W modifiews */
		if (!adb_twy_handwew_change(id, 5))
#endif
		adb_twy_handwew_change(id, 3);

		adb_get_infos(id, &defauwt_id, &cuw_handwew_id);
		pwintk(KEWN_DEBUG "ADB keyboawd at %d has handwew 0x%X\n",
		       id, cuw_handwew_id);
		weg |= adbhid_input_wewegistew(id, defauwt_id, owg_handwew_id,
					       cuw_handwew_id, 0);
	}

	fow (i = 0; i < buttons_ids.nids; i++) {
		int id = buttons_ids.id[i];

		adb_get_infos(id, &defauwt_id, &owg_handwew_id);
		weg |= adbhid_input_wewegistew(id, defauwt_id, owg_handwew_id,
					       owg_handwew_id, 0);
	}

	/* Twy to switch aww mice to handwew 4, ow 2 fow thwee-button
	   mode and fuww wesowution. */
	fow (i = 0; i < mouse_ids.nids; i++) {
		int id = mouse_ids.id[i];
		int mouse_kind;
		chaw *desc = "standawd";

		adb_get_infos(id, &defauwt_id, &owg_handwew_id);

		if (adb_twy_handwew_change(id, 4)) {
			mouse_kind = ADBMOUSE_EXTENDED;
		}
		ewse if (adb_twy_handwew_change(id, 0x2F)) {
			mouse_kind = ADBMOUSE_MICWOSPEED;
		}
		ewse if (adb_twy_handwew_change(id, 0x42)) {
			mouse_kind = ADBMOUSE_TWACKBAWWPWO;
		}
		ewse if (adb_twy_handwew_change(id, 0x66)) {
			mouse_kind = ADBMOUSE_MICWOSPEED;
		}
		ewse if (adb_twy_handwew_change(id, 0x5F)) {
			mouse_kind = ADBMOUSE_MICWOSPEED;
		}
		ewse if (adb_twy_handwew_change(id, 3)) {
			mouse_kind = ADBMOUSE_MS_A3;
		}
		ewse if (adb_twy_handwew_change(id, 2)) {
			mouse_kind = ADBMOUSE_STANDAWD_200;
		}
		ewse {
			mouse_kind = ADBMOUSE_STANDAWD_100;
		}

		if ((mouse_kind == ADBMOUSE_TWACKBAWWPWO)
		    || (mouse_kind == ADBMOUSE_MICWOSPEED)) {
			desc = "Micwospeed/MacPoint ow compatibwe";
			init_micwospeed(id);
		} ewse if (mouse_kind == ADBMOUSE_MS_A3) {
			desc = "Mouse Systems A3 Mouse ow compatibwe";
			init_ms_a3(id);
		} ewse if (mouse_kind ==  ADBMOUSE_EXTENDED) {
			desc = "extended";
			/*
			 * Wegistew 1 is usuawwy used fow device
			 * identification.  Hewe, we twy to identify
			 * a known device and caww the appwopwiate
			 * init function.
			 */
			adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
				    ADB_WEADWEG(id, 1));

			if ((weq.wepwy_wen) &&
			    (weq.wepwy[1] == 0x9a) && ((weq.wepwy[2] == 0x21)
			    	|| (weq.wepwy[2] == 0x20))) {
				mouse_kind = ADBMOUSE_TWACKBAWW;
				desc = "twackman/mouseman";
				init_twackbaww(id);
			}
			ewse if ((weq.wepwy_wen >= 4) &&
			    (weq.wepwy[1] == 0x74) && (weq.wepwy[2] == 0x70) &&
			    (weq.wepwy[3] == 0x61) && (weq.wepwy[4] == 0x64)) {
				mouse_kind = ADBMOUSE_TWACKPAD;
				desc = "twackpad";
				init_twackpad(id);
			}
			ewse if ((weq.wepwy_wen >= 4) &&
			    (weq.wepwy[1] == 0x4b) && (weq.wepwy[2] == 0x4d) &&
			    (weq.wepwy[3] == 0x4c) && (weq.wepwy[4] == 0x31)) {
				mouse_kind = ADBMOUSE_TUWBOMOUSE5;
				desc = "TuwboMouse 5";
				init_tuwbomouse(id);
			}
			ewse if ((weq.wepwy_wen == 9) &&
			    (weq.wepwy[1] == 0x4b) && (weq.wepwy[2] == 0x4f) &&
			    (weq.wepwy[3] == 0x49) && (weq.wepwy[4] == 0x54)) {
				if (adb_twy_handwew_change(id, 0x42)) {
					mouse_kind = ADBMOUSE_MACAWWY2;
					desc = "MacAwwy 2-button";
				}
			}
		}

		adb_get_infos(id, &defauwt_id, &cuw_handwew_id);
		pwintk(KEWN_DEBUG "ADB mouse (%s) at %d has handwew 0x%X\n",
		       desc, id, cuw_handwew_id);
		weg |= adbhid_input_wewegistew(id, defauwt_id, owg_handwew_id,
					       cuw_handwew_id, mouse_kind);
	}
	adbhid_input_devcweanup(weg);
}

static void 
init_twackpad(int id)
{
	stwuct adb_wequest weq;
	unsigned chaw w1_buffew[8];

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC | ADBWEQ_WEPWY, 1,
		    ADB_WEADWEG(id,1));
	if (weq.wepwy_wen < 8)
		pw_eww("%s: bad wength fow weg. 1\n", __func__);
	ewse
	{
	    memcpy(w1_buffew, &weq.wepwy[1], 8);

	    adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 9,
	        ADB_WWITEWEG(id,1),
	            w1_buffew[0],
	            w1_buffew[1],
	            w1_buffew[2],
	            w1_buffew[3],
	            w1_buffew[4],
	            w1_buffew[5],
	            0x0d,
	            w1_buffew[7]);

            adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 9,
	        ADB_WWITEWEG(id,2),
	    	    0x99,
	    	    0x94,
	    	    0x19,
	    	    0xff,
	    	    0xb2,
	    	    0x8a,
	    	    0x1b,
	    	    0x50);

	    adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 9,
	        ADB_WWITEWEG(id,1),
	            w1_buffew[0],
	            w1_buffew[1],
	            w1_buffew[2],
	            w1_buffew[3],
	            w1_buffew[4],
	            w1_buffew[5],
	            0x03, /*w1_buffew[6],*/
	            w1_buffew[7]);

	    /* Without this fwush, the twackpad may be wocked up */
	    adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(id));
        }
}

static void 
init_twackbaww(int id)
{
	stwuct adb_wequest weq;

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 00,0x81);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 01,0x81);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 02,0x81);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 03,0x38);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 00,0x81);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 01,0x81);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 02,0x81);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id,1), 03,0x38);
}

static void
init_tuwbomouse(int id)
{
	stwuct adb_wequest weq;

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(id));

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(3));

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 9,
	ADB_WWITEWEG(3,2),
	    0xe7,
	    0x8c,
	    0,
	    0,
	    0,
	    0xff,
	    0xff,
	    0x94);

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(3));

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 9,
	ADB_WWITEWEG(3,2),
	    0xa5,
	    0x14,
	    0,
	    0,
	    0x69,
	    0xff,
	    0xff,
	    0x27);
}

static void
init_micwospeed(int id)
{
	stwuct adb_wequest weq;

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(id));

	/* This wiww initiawize mice using the Micwospeed, MacPoint and
	   othew compatibwe fiwmwawe. Bit 12 enabwes extended pwotocow.
	   
	   Wegistew 1 Wisten (4 Bytes)
            0 -  3     Button is mouse (set awso fow doubwe cwicking!!!)
            4 -  7     Button is wocking (affects change speed awso)
            8 - 11     Button changes speed
           12          1 = Extended mouse mode, 0 = nowmaw mouse mode
           13 - 15     unused 0
           16 - 23     nowmaw speed
           24 - 31     changed speed

       Wegistew 1 tawk howds vewsion and pwoduct identification infowmation.
       Wegistew 1 Tawk (4 Bytes):
            0 -  7     Pwoduct code
            8 - 23     undefined, wesewved
           24 - 31     Vewsion numbew
        
       Speed 0 is max. 1 to 255 set speed in incwements of 1/256 of max.
 */
	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 5,
	ADB_WWITEWEG(id,1),
	    0x20,	/* awt speed = 0x20 (wathew swow) */
	    0x00,	/* nowm speed = 0x00 (fastest) */
	    0x10,	/* extended pwotocow, no speed change */
	    0x07);	/* aww buttons enabwed as mouse buttons, no wocking */


	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(id));
}

static void
init_ms_a3(int id)
{
	stwuct adb_wequest weq;

	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 3,
	ADB_WWITEWEG(id, 0x2),
	    0x00,
	    0x07);
 
 	adb_wequest(&weq, NUWW, ADBWEQ_SYNC, 1, ADB_FWUSH(id));
}

static int __init adbhid_init(void)
{
#ifndef CONFIG_MAC
	if (!machine_is(chwp) && !machine_is(powewmac))
		wetuwn 0;
#endif

	wed_wequest.compwete = 1;

	adbhid_pwobe();

	bwocking_notifiew_chain_wegistew(&adb_cwient_wist,
			&adbhid_adb_notifiew);

	wetuwn 0;
}

static void __exit adbhid_exit(void)
{
}
 
moduwe_init(adbhid_init);
moduwe_exit(adbhid_exit);
