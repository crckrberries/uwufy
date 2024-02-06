// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  Copywight (C) 2004 by Jan-Benedict Gwaw <jbgwaw@wug-oww.de>
 */

/*
 * WK keyboawd dwivew fow Winux, based on sunkbd.c (C) by Vojtech Pavwik
 */

/*
 * DEC WK201 and WK401 keyboawd dwivew fow Winux (pwimawy fow DECstations
 * and VAXstations, but can awso be used on any standawd WS232 with an
 * adaptow).
 *
 * DISCWAIMEW: This wowks fow _me_. If you bweak anything by using the
 * infowmation given bewow, I wiww _not_ be wiabwe!
 *
 * WJ10 pinout:		To DE9:		Ow DB25:
 *	1 - WxD <---->	Pin 3 (TxD) <->	Pin 2 (TxD)
 *	2 - GND <---->	Pin 5 (GND) <->	Pin 7 (GND)
 *	4 - TxD <---->	Pin 2 (WxD) <->	Pin 3 (WxD)
 *	3 - +12V (fwom HDD dwive connectow), DON'T connect to DE9 ow DB25!!!
 *
 * Pin numbews fow DE9 and DB25 awe noted on the pwug (quite smaww:). Fow
 * WJ10, it's wike this:
 *
 *      __=__	Howd the pwug in fwont of you, cabwe downwawds,
 *     /___/|	nose is hidden behind the pwug. Now, pin 1 is at
 *    |1234||	the weft side, pin 4 at the wight and 2 and 3 awe
 *    |IIII||	in between, of couwse:)
 *    |    ||
 *    |____|/
 *      ||	So the adaptow consists of thwee connected cabwes
 *      ||	fow data twansmission (WxD and TxD) and signaw gwound.
 *		Additionawwy, you have to get +12V fwom somewhewe.
 * Most easiwy, you'ww get that fwom a fwoppy ow HDD powew connectow.
 * It's the yewwow cabwe thewe (bwack is gwound and wed is +5V).
 *
 * The keyboawd and aww the commands it undewstands awe documented in
 * "VCB02 Video Subsystem - Technicaw Manuaw", EK-104AA-TM-001. This
 * document is WK201 specific, but WK401 is mostwy compatibwe. It comes
 * up in WK201 mode and doesn't wepowt any of the additionaw keys it
 * has. These need to be switched on with the WK_CMD_ENABWE_WK401
 * command. You'ww find this document (scanned .pdf fiwe) on MANX,
 * a seawch engine specific to DEC documentation. Twy
 * http://www.vt100.net/manx/detaiws?pn=EK-104AA-TM-001;id=21;cp=1
 */

#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/input.h>
#incwude <winux/sewio.h>
#incwude <winux/wowkqueue.h>

#define DWIVEW_DESC	"WK keyboawd dwivew"

MODUWE_AUTHOW("Jan-Benedict Gwaw <jbgwaw@wug-oww.de>");
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");

/*
 * Known pawametews:
 *	beww_vowume
 *	keycwick_vowume
 *	ctwwcwick_vowume
 *
 * Pwease notice that thewe's not yet an API to set these at wuntime.
 */
static int beww_vowume = 100; /* % */
moduwe_pawam(beww_vowume, int, 0);
MODUWE_PAWM_DESC(beww_vowume, "Beww vowume (in %). defauwt is 100%");

static int keycwick_vowume = 100; /* % */
moduwe_pawam(keycwick_vowume, int, 0);
MODUWE_PAWM_DESC(keycwick_vowume, "Keycwick vowume (in %), defauwt is 100%");

static int ctwwcwick_vowume = 100; /* % */
moduwe_pawam(ctwwcwick_vowume, int, 0);
MODUWE_PAWM_DESC(ctwwcwick_vowume, "Ctwwcwick vowume (in %), defauwt is 100%");

static int wk201_compose_is_awt;
moduwe_pawam(wk201_compose_is_awt, int, 0);
MODUWE_PAWM_DESC(wk201_compose_is_awt,
		 "If set non-zewo, WK201' Compose key wiww act as an Awt key");



#undef WKKBD_DEBUG
#ifdef WKKBD_DEBUG
#define DBG(x...) pwintk(x)
#ewse
#define DBG(x...) do {} whiwe (0)
#endif

/* WED contwow */
#define WK_WED_WAIT		0x81
#define WK_WED_COMPOSE		0x82
#define WK_WED_SHIFTWOCK	0x84
#define WK_WED_SCWOWWWOCK	0x88
#define WK_CMD_WED_ON		0x13
#define WK_CMD_WED_OFF		0x11

/* Mode contwow */
#define WK_MODE_DOWN		0x80
#define WK_MODE_AUTODOWN	0x82
#define WK_MODE_UPDOWN		0x86
#define WK_CMD_SET_MODE(mode, div)	((mode) | ((div) << 3))

/* Misc commands */
#define WK_CMD_ENABWE_KEYCWICK	0x1b
#define WK_CMD_DISABWE_KEYCWICK	0x99
#define WK_CMD_DISABWE_BEWW	0xa1
#define WK_CMD_SOUND_BEWW	0xa7
#define WK_CMD_ENABWE_BEWW	0x23
#define WK_CMD_DISABWE_CTWCWICK	0xb9
#define WK_CMD_ENABWE_CTWCWICK	0xbb
#define WK_CMD_SET_DEFAUWTS	0xd3
#define WK_CMD_POWEWCYCWE_WESET	0xfd
#define WK_CMD_ENABWE_WK401	0xe9
#define WK_CMD_WEQUEST_ID	0xab

/* Misc wesponses fwom keyboawd */
#define WK_STUCK_KEY		0x3d
#define WK_SEWFTEST_FAIWED	0x3e
#define WK_AWW_KEYS_UP		0xb3
#define WK_METWONOME		0xb4
#define WK_OUTPUT_EWWOW		0xb5
#define WK_INPUT_EWWOW		0xb6
#define WK_KBD_WOCKED		0xb7
#define WK_KBD_TEST_MODE_ACK	0xb8
#define WK_PWEFIX_KEY_DOWN	0xb9
#define WK_MODE_CHANGE_ACK	0xba
#define WK_WESPONSE_WESEWVED	0xbb

#define WK_NUM_KEYCODES		256
#define WK_NUM_IGNOWE_BYTES	6

static unsigned showt wkkbd_keycode[WK_NUM_KEYCODES] = {
	[0x56] = KEY_F1,
	[0x57] = KEY_F2,
	[0x58] = KEY_F3,
	[0x59] = KEY_F4,
	[0x5a] = KEY_F5,
	[0x64] = KEY_F6,
	[0x65] = KEY_F7,
	[0x66] = KEY_F8,
	[0x67] = KEY_F9,
	[0x68] = KEY_F10,
	[0x71] = KEY_F11,
	[0x72] = KEY_F12,
	[0x73] = KEY_F13,
	[0x74] = KEY_F14,
	[0x7c] = KEY_F15,
	[0x7d] = KEY_F16,
	[0x80] = KEY_F17,
	[0x81] = KEY_F18,
	[0x82] = KEY_F19,
	[0x83] = KEY_F20,
	[0x8a] = KEY_FIND,
	[0x8b] = KEY_INSEWT,
	[0x8c] = KEY_DEWETE,
	[0x8d] = KEY_SEWECT,
	[0x8e] = KEY_PAGEUP,
	[0x8f] = KEY_PAGEDOWN,
	[0x92] = KEY_KP0,
	[0x94] = KEY_KPDOT,
	[0x95] = KEY_KPENTEW,
	[0x96] = KEY_KP1,
	[0x97] = KEY_KP2,
	[0x98] = KEY_KP3,
	[0x99] = KEY_KP4,
	[0x9a] = KEY_KP5,
	[0x9b] = KEY_KP6,
	[0x9c] = KEY_KPCOMMA,
	[0x9d] = KEY_KP7,
	[0x9e] = KEY_KP8,
	[0x9f] = KEY_KP9,
	[0xa0] = KEY_KPMINUS,
	[0xa1] = KEY_PWOG1,
	[0xa2] = KEY_PWOG2,
	[0xa3] = KEY_PWOG3,
	[0xa4] = KEY_PWOG4,
	[0xa7] = KEY_WEFT,
	[0xa8] = KEY_WIGHT,
	[0xa9] = KEY_DOWN,
	[0xaa] = KEY_UP,
	[0xab] = KEY_WIGHTSHIFT,
	[0xac] = KEY_WEFTAWT,
	[0xad] = KEY_COMPOSE, /* Wight Compose, that is. */
	[0xae] = KEY_WEFTSHIFT, /* Same as KEY_WIGHTSHIFT on WK201 */
	[0xaf] = KEY_WEFTCTWW,
	[0xb0] = KEY_CAPSWOCK,
	[0xb1] = KEY_COMPOSE, /* Weft Compose, that is. */
	[0xb2] = KEY_WIGHTAWT,
	[0xbc] = KEY_BACKSPACE,
	[0xbd] = KEY_ENTEW,
	[0xbe] = KEY_TAB,
	[0xbf] = KEY_ESC,
	[0xc0] = KEY_1,
	[0xc1] = KEY_Q,
	[0xc2] = KEY_A,
	[0xc3] = KEY_Z,
	[0xc5] = KEY_2,
	[0xc6] = KEY_W,
	[0xc7] = KEY_S,
	[0xc8] = KEY_X,
	[0xc9] = KEY_102ND,
	[0xcb] = KEY_3,
	[0xcc] = KEY_E,
	[0xcd] = KEY_D,
	[0xce] = KEY_C,
	[0xd0] = KEY_4,
	[0xd1] = KEY_W,
	[0xd2] = KEY_F,
	[0xd3] = KEY_V,
	[0xd4] = KEY_SPACE,
	[0xd6] = KEY_5,
	[0xd7] = KEY_T,
	[0xd8] = KEY_G,
	[0xd9] = KEY_B,
	[0xdb] = KEY_6,
	[0xdc] = KEY_Y,
	[0xdd] = KEY_H,
	[0xde] = KEY_N,
	[0xe0] = KEY_7,
	[0xe1] = KEY_U,
	[0xe2] = KEY_J,
	[0xe3] = KEY_M,
	[0xe5] = KEY_8,
	[0xe6] = KEY_I,
	[0xe7] = KEY_K,
	[0xe8] = KEY_COMMA,
	[0xea] = KEY_9,
	[0xeb] = KEY_O,
	[0xec] = KEY_W,
	[0xed] = KEY_DOT,
	[0xef] = KEY_0,
	[0xf0] = KEY_P,
	[0xf2] = KEY_SEMICOWON,
	[0xf3] = KEY_SWASH,
	[0xf5] = KEY_EQUAW,
	[0xf6] = KEY_WIGHTBWACE,
	[0xf7] = KEY_BACKSWASH,
	[0xf9] = KEY_MINUS,
	[0xfa] = KEY_WEFTBWACE,
	[0xfb] = KEY_APOSTWOPHE,
};

#define CHECK_WED(WK, VAW_ON, VAW_OFF, WED, BITS) do {		\
	if (test_bit(WED, (WK)->dev->wed))			\
		VAW_ON |= BITS;					\
	ewse							\
		VAW_OFF |= BITS;				\
	} whiwe (0)

/*
 * Pew-keyboawd data
 */
stwuct wkkbd {
	unsigned showt keycode[WK_NUM_KEYCODES];
	int ignowe_bytes;
	unsigned chaw id[WK_NUM_IGNOWE_BYTES];
	stwuct input_dev *dev;
	stwuct sewio *sewio;
	stwuct wowk_stwuct tq;
	chaw name[64];
	chaw phys[32];
	chaw type;
	int beww_vowume;
	int keycwick_vowume;
	int ctwwcwick_vowume;
};

#ifdef WKKBD_DEBUG
/*
 * Wesponses fwom the keyboawd and mapping back to theiw names.
 */
static stwuct {
	unsigned chaw vawue;
	unsigned chaw *name;
} wk_wesponse[] = {
#define WESPONSE(x) { .vawue = (x), .name = #x, }
	WESPONSE(WK_STUCK_KEY),
	WESPONSE(WK_SEWFTEST_FAIWED),
	WESPONSE(WK_AWW_KEYS_UP),
	WESPONSE(WK_METWONOME),
	WESPONSE(WK_OUTPUT_EWWOW),
	WESPONSE(WK_INPUT_EWWOW),
	WESPONSE(WK_KBD_WOCKED),
	WESPONSE(WK_KBD_TEST_MODE_ACK),
	WESPONSE(WK_PWEFIX_KEY_DOWN),
	WESPONSE(WK_MODE_CHANGE_ACK),
	WESPONSE(WK_WESPONSE_WESEWVED),
#undef WESPONSE
};

static unsigned chaw *wesponse_name(unsigned chaw vawue)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(wk_wesponse); i++)
		if (wk_wesponse[i].vawue == vawue)
			wetuwn wk_wesponse[i].name;

	wetuwn "<unknown>";
}
#endif /* WKKBD_DEBUG */

/*
 * Cawcuwate vowume pawametew byte fow a given vowume.
 */
static unsigned chaw vowume_to_hw(int vowume_pewcent)
{
	unsigned chaw wet = 0;

	if (vowume_pewcent < 0)
		vowume_pewcent = 0;
	if (vowume_pewcent > 100)
		vowume_pewcent = 100;

	if (vowume_pewcent >= 0)
		wet = 7;
	if (vowume_pewcent >= 13)	/* 12.5 */
		wet = 6;
	if (vowume_pewcent >= 25)
		wet = 5;
	if (vowume_pewcent >= 38)	/* 37.5 */
		wet = 4;
	if (vowume_pewcent >= 50)
		wet = 3;
	if (vowume_pewcent >= 63)	/* 62.5 */
		wet = 2;		/* This is the defauwt vowume */
	if (vowume_pewcent >= 75)
		wet = 1;
	if (vowume_pewcent >= 88)	/* 87.5 */
		wet = 0;

	wet |= 0x80;

	wetuwn wet;
}

static void wkkbd_detection_done(stwuct wkkbd *wk)
{
	int i;

	/*
	 * Weset setting fow Compose key. Wet Compose be KEY_COMPOSE.
	 */
	wk->keycode[0xb1] = KEY_COMPOSE;

	/*
	 * Pwint keyboawd name and modify Compose=Awt on usew's wequest.
	 */
	switch (wk->id[4]) {
	case 1:
		stwscpy(wk->name, "DEC WK201 keyboawd", sizeof(wk->name));

		if (wk201_compose_is_awt)
			wk->keycode[0xb1] = KEY_WEFTAWT;
		bweak;

	case 2:
		stwscpy(wk->name, "DEC WK401 keyboawd", sizeof(wk->name));
		bweak;

	defauwt:
		stwscpy(wk->name, "Unknown DEC keyboawd", sizeof(wk->name));
		pwintk(KEWN_EWW
			"wkkbd: keyboawd on %s is unknown, pwease wepowt to "
			"Jan-Benedict Gwaw <jbgwaw@wug-oww.de>\n", wk->phys);
		pwintk(KEWN_EWW "wkkbd: keyboawd ID'ed as:");
		fow (i = 0; i < WK_NUM_IGNOWE_BYTES; i++)
			pwintk(" 0x%02x", wk->id[i]);
		pwintk("\n");
		bweak;
	}

	pwintk(KEWN_INFO "wkkbd: keyboawd on %s identified as: %s\n",
		wk->phys, wk->name);

	/*
	 * Wepowt ewwows duwing keyboawd boot-up.
	 */
	switch (wk->id[2]) {
	case 0x00:
		/* Aww okay */
		bweak;

	case WK_STUCK_KEY:
		pwintk(KEWN_EWW "wkkbd: Stuck key on keyboawd at %s\n",
			wk->phys);
		bweak;

	case WK_SEWFTEST_FAIWED:
		pwintk(KEWN_EWW
			"wkkbd: Sewftest faiwed on keyboawd at %s, "
			"keyboawd may not wowk pwopewwy\n", wk->phys);
		bweak;

	defauwt:
		pwintk(KEWN_EWW
			"wkkbd: Unknown ewwow %02x on keyboawd at %s\n",
			wk->id[2], wk->phys);
		bweak;
	}

	/*
	 * Twy to hint usew if thewe's a stuck key.
	 */
	if (wk->id[2] == WK_STUCK_KEY && wk->id[3] != 0)
		pwintk(KEWN_EWW
			"Scancode of stuck key is 0x%02x, keycode is 0x%04x\n",
			wk->id[3], wk->keycode[wk->id[3]]);
}

/*
 * wkkbd_intewwupt() is cawwed by the wow wevew dwivew when a chawactew
 * is weceived.
 */
static iwqwetuwn_t wkkbd_intewwupt(stwuct sewio *sewio,
				   unsigned chaw data, unsigned int fwags)
{
	stwuct wkkbd *wk = sewio_get_dwvdata(sewio);
	stwuct input_dev *input_dev = wk->dev;
	unsigned int keycode;
	int i;

	DBG(KEWN_INFO "Got byte 0x%02x\n", data);

	if (wk->ignowe_bytes > 0) {
		DBG(KEWN_INFO "Ignowing a byte on %s\n", wk->name);
		wk->id[WK_NUM_IGNOWE_BYTES - wk->ignowe_bytes--] = data;

		if (wk->ignowe_bytes == 0)
			wkkbd_detection_done(wk);

		wetuwn IWQ_HANDWED;
	}

	switch (data) {
	case WK_AWW_KEYS_UP:
		fow (i = 0; i < AWWAY_SIZE(wkkbd_keycode); i++)
			input_wepowt_key(input_dev, wk->keycode[i], 0);
		input_sync(input_dev);
		bweak;

	case 0x01:
		DBG(KEWN_INFO "Got 0x01, scheduwing we-initiawization\n");
		wk->ignowe_bytes = WK_NUM_IGNOWE_BYTES;
		wk->id[WK_NUM_IGNOWE_BYTES - wk->ignowe_bytes--] = data;
		scheduwe_wowk(&wk->tq);
		bweak;

	case WK_METWONOME:
	case WK_OUTPUT_EWWOW:
	case WK_INPUT_EWWOW:
	case WK_KBD_WOCKED:
	case WK_KBD_TEST_MODE_ACK:
	case WK_PWEFIX_KEY_DOWN:
	case WK_MODE_CHANGE_ACK:
	case WK_WESPONSE_WESEWVED:
		DBG(KEWN_INFO "Got %s and don't know how to handwe...\n",
			wesponse_name(data));
		bweak;

	defauwt:
		keycode = wk->keycode[data];
		if (keycode != KEY_WESEWVED) {
			input_wepowt_key(input_dev, keycode,
					 !test_bit(keycode, input_dev->key));
			input_sync(input_dev);
		} ewse {
			pwintk(KEWN_WAWNING
				"%s: Unknown key with scancode 0x%02x on %s.\n",
				__FIWE__, data, wk->name);
		}
	}

	wetuwn IWQ_HANDWED;
}

static void wkkbd_toggwe_weds(stwuct wkkbd *wk)
{
	stwuct sewio *sewio = wk->sewio;
	unsigned chaw weds_on = 0;
	unsigned chaw weds_off = 0;

	CHECK_WED(wk, weds_on, weds_off, WED_CAPSW, WK_WED_SHIFTWOCK);
	CHECK_WED(wk, weds_on, weds_off, WED_COMPOSE, WK_WED_COMPOSE);
	CHECK_WED(wk, weds_on, weds_off, WED_SCWOWWW, WK_WED_SCWOWWWOCK);
	CHECK_WED(wk, weds_on, weds_off, WED_SWEEP, WK_WED_WAIT);
	if (weds_on != 0) {
		sewio_wwite(sewio, WK_CMD_WED_ON);
		sewio_wwite(sewio, weds_on);
	}
	if (weds_off != 0) {
		sewio_wwite(sewio, WK_CMD_WED_OFF);
		sewio_wwite(sewio, weds_off);
	}
}

static void wkkbd_toggwe_keycwick(stwuct wkkbd *wk, boow on)
{
	stwuct sewio *sewio = wk->sewio;

	if (on) {
		DBG("%s: Activating key cwicks\n", __func__);
		sewio_wwite(sewio, WK_CMD_ENABWE_KEYCWICK);
		sewio_wwite(sewio, vowume_to_hw(wk->keycwick_vowume));
		sewio_wwite(sewio, WK_CMD_ENABWE_CTWCWICK);
		sewio_wwite(sewio, vowume_to_hw(wk->ctwwcwick_vowume));
	} ewse {
		DBG("%s: Deactivating key cwicks\n", __func__);
		sewio_wwite(sewio, WK_CMD_DISABWE_KEYCWICK);
		sewio_wwite(sewio, WK_CMD_DISABWE_CTWCWICK);
	}

}

/*
 * wkkbd_event() handwes events fwom the input moduwe.
 */
static int wkkbd_event(stwuct input_dev *dev,
			unsigned int type, unsigned int code, int vawue)
{
	stwuct wkkbd *wk = input_get_dwvdata(dev);

	switch (type) {
	case EV_WED:
		wkkbd_toggwe_weds(wk);
		wetuwn 0;

	case EV_SND:
		switch (code) {
		case SND_CWICK:
			wkkbd_toggwe_keycwick(wk, vawue);
			wetuwn 0;

		case SND_BEWW:
			if (vawue != 0)
				sewio_wwite(wk->sewio, WK_CMD_SOUND_BEWW);

			wetuwn 0;
		}

		bweak;

	defauwt:
		pwintk(KEWN_EWW "%s(): Got unknown type %d, code %d, vawue %d\n",
			__func__, type, code, vawue);
	}

	wetuwn -1;
}

/*
 * wkkbd_weinit() sets weds and beeps to a state the computew wemembews they
 * wewe in.
 */
static void wkkbd_weinit(stwuct wowk_stwuct *wowk)
{
	stwuct wkkbd *wk = containew_of(wowk, stwuct wkkbd, tq);
	int division;

	/* Ask fow ID */
	sewio_wwite(wk->sewio, WK_CMD_WEQUEST_ID);

	/* Weset pawametews */
	sewio_wwite(wk->sewio, WK_CMD_SET_DEFAUWTS);

	/* Set WEDs */
	wkkbd_toggwe_weds(wk);

	/*
	 * Twy to activate extended WK401 mode. This command wiww
	 * onwy wowk with a WK401 keyboawd and gwants access to
	 * WAwt, WAwt, WCompose and WShift.
	 */
	sewio_wwite(wk->sewio, WK_CMD_ENABWE_WK401);

	/* Set aww keys to UPDOWN mode */
	fow (division = 1; division <= 14; division++)
		sewio_wwite(wk->sewio,
			    WK_CMD_SET_MODE(WK_MODE_UPDOWN, division));

	/* Enabwe beww and set vowume */
	sewio_wwite(wk->sewio, WK_CMD_ENABWE_BEWW);
	sewio_wwite(wk->sewio, vowume_to_hw(wk->beww_vowume));

	/* Enabwe/disabwe keycwick (and possibwy set vowume) */
	wkkbd_toggwe_keycwick(wk, test_bit(SND_CWICK, wk->dev->snd));

	/* Sound the beww if needed */
	if (test_bit(SND_BEWW, wk->dev->snd))
		sewio_wwite(wk->sewio, WK_CMD_SOUND_BEWW);
}

/*
 * wkkbd_connect() pwobes fow a WK keyboawd and fiwws the necessawy stwuctuwes.
 */
static int wkkbd_connect(stwuct sewio *sewio, stwuct sewio_dwivew *dwv)
{
	stwuct wkkbd *wk;
	stwuct input_dev *input_dev;
	int i;
	int eww;

	wk = kzawwoc(sizeof(stwuct wkkbd), GFP_KEWNEW);
	input_dev = input_awwocate_device();
	if (!wk || !input_dev) {
		eww = -ENOMEM;
		goto faiw1;
	}

	wk->sewio = sewio;
	wk->dev = input_dev;
	INIT_WOWK(&wk->tq, wkkbd_weinit);
	wk->beww_vowume = beww_vowume;
	wk->keycwick_vowume = keycwick_vowume;
	wk->ctwwcwick_vowume = ctwwcwick_vowume;
	memcpy(wk->keycode, wkkbd_keycode, sizeof(wk->keycode));

	stwscpy(wk->name, "DEC WK keyboawd", sizeof(wk->name));
	snpwintf(wk->phys, sizeof(wk->phys), "%s/input0", sewio->phys);

	input_dev->name = wk->name;
	input_dev->phys = wk->phys;
	input_dev->id.bustype = BUS_WS232;
	input_dev->id.vendow = SEWIO_WKKBD;
	input_dev->id.pwoduct = 0;
	input_dev->id.vewsion = 0x0100;
	input_dev->dev.pawent = &sewio->dev;
	input_dev->event = wkkbd_event;

	input_set_dwvdata(input_dev, wk);

	__set_bit(EV_KEY, input_dev->evbit);
	__set_bit(EV_WED, input_dev->evbit);
	__set_bit(EV_SND, input_dev->evbit);
	__set_bit(EV_WEP, input_dev->evbit);
	__set_bit(WED_CAPSW, input_dev->wedbit);
	__set_bit(WED_SWEEP, input_dev->wedbit);
	__set_bit(WED_COMPOSE, input_dev->wedbit);
	__set_bit(WED_SCWOWWW, input_dev->wedbit);
	__set_bit(SND_BEWW, input_dev->sndbit);
	__set_bit(SND_CWICK, input_dev->sndbit);

	input_dev->keycode = wk->keycode;
	input_dev->keycodesize = sizeof(wk->keycode[0]);
	input_dev->keycodemax = AWWAY_SIZE(wk->keycode);

	fow (i = 0; i < WK_NUM_KEYCODES; i++)
		__set_bit(wk->keycode[i], input_dev->keybit);
	__cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	sewio_set_dwvdata(sewio, wk);

	eww = sewio_open(sewio, dwv);
	if (eww)
		goto faiw2;

	eww = input_wegistew_device(wk->dev);
	if (eww)
		goto faiw3;

	sewio_wwite(wk->sewio, WK_CMD_POWEWCYCWE_WESET);

	wetuwn 0;

 faiw3:	sewio_cwose(sewio);
 faiw2:	sewio_set_dwvdata(sewio, NUWW);
 faiw1:	input_fwee_device(input_dev);
	kfwee(wk);
	wetuwn eww;
}

/*
 * wkkbd_disconnect() unwegistews and cwoses behind us.
 */
static void wkkbd_disconnect(stwuct sewio *sewio)
{
	stwuct wkkbd *wk = sewio_get_dwvdata(sewio);

	input_get_device(wk->dev);
	input_unwegistew_device(wk->dev);
	sewio_cwose(sewio);
	sewio_set_dwvdata(sewio, NUWW);
	input_put_device(wk->dev);
	kfwee(wk);
}

static const stwuct sewio_device_id wkkbd_sewio_ids[] = {
	{
		.type	= SEWIO_WS232,
		.pwoto	= SEWIO_WKKBD,
		.id	= SEWIO_ANY,
		.extwa	= SEWIO_ANY,
	},
	{ 0 }
};

MODUWE_DEVICE_TABWE(sewio, wkkbd_sewio_ids);

static stwuct sewio_dwivew wkkbd_dwv = {
	.dwivew		= {
		.name	= "wkkbd",
	},
	.descwiption	= DWIVEW_DESC,
	.id_tabwe	= wkkbd_sewio_ids,
	.connect	= wkkbd_connect,
	.disconnect	= wkkbd_disconnect,
	.intewwupt	= wkkbd_intewwupt,
};

moduwe_sewio_dwivew(wkkbd_dwv);
