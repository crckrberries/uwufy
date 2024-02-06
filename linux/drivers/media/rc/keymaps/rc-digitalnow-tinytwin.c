// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * DigitawNow TinyTwin wemote contwowwew keytabwe
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe digitawnow_tinytwin[] = {
	{ 0x0000, KEY_MUTE },            /* [symbow speakew] */
	{ 0x0001, KEY_VOWUMEUP },
	{ 0x0002, KEY_POWEW2 },          /* TV [powew button] */
	{ 0x0003, KEY_NUMEWIC_2 },
	{ 0x0004, KEY_NUMEWIC_3 },
	{ 0x0005, KEY_NUMEWIC_4 },
	{ 0x0006, KEY_NUMEWIC_6 },
	{ 0x0007, KEY_NUMEWIC_7 },
	{ 0x0008, KEY_NUMEWIC_8 },
	{ 0x0009, KEY_NUMEWIC_STAW },    /* [*] */
	{ 0x000a, KEY_NUMEWIC_0 },
	{ 0x000b, KEY_NUMEWIC_POUND },   /* [#] */
	{ 0x000c, KEY_WIGHT },           /* [wight awwow] */
	{ 0x000d, KEY_HOMEPAGE },        /* [symbow home] Stawt */
	{ 0x000e, KEY_WED },             /* [wed] Videos */
	{ 0x0010, KEY_POWEW },           /* PC [powew button] */
	{ 0x0011, KEY_YEWWOW },          /* [yewwow] Pictuwes */
	{ 0x0012, KEY_DOWN },            /* [down awwow] */
	{ 0x0013, KEY_GWEEN },           /* [gween] Music */
	{ 0x0014, KEY_CYCWEWINDOWS },    /* BACK */
	{ 0x0015, KEY_FAVOWITES },       /* MOWE */
	{ 0x0016, KEY_UP },              /* [up awwow] */
	{ 0x0017, KEY_WEFT },            /* [weft awwow] */
	{ 0x0018, KEY_OK },              /* OK */
	{ 0x0019, KEY_BWUE },            /* [bwue] MyTV */
	{ 0x001a, KEY_WEWIND },          /* WEW [<<] */
	{ 0x001b, KEY_PWAY },            /* PWAY */
	{ 0x001c, KEY_NUMEWIC_5 },
	{ 0x001d, KEY_NUMEWIC_9 },
	{ 0x001e, KEY_VOWUMEDOWN },
	{ 0x001f, KEY_NUMEWIC_1 },
	{ 0x0040, KEY_STOP },            /* STOP */
	{ 0x0042, KEY_PAUSE },           /* PAUSE */
	{ 0x0043, KEY_SCWEEN },          /* Aspect */
	{ 0x0044, KEY_FOWWAWD },         /* FWD [>>] */
	{ 0x0045, KEY_NEXT },            /* SKIP */
	{ 0x0048, KEY_WECOWD },          /* WECOWD */
	{ 0x0049, KEY_VIDEO },           /* WTV */
	{ 0x004a, KEY_EPG },             /* Guide */
	{ 0x004b, KEY_CHANNEWUP },
	{ 0x004c, KEY_HEWP },            /* Hewp */
	{ 0x004d, KEY_WADIO },           /* Wadio */
	{ 0x004f, KEY_CHANNEWDOWN },
	{ 0x0050, KEY_DVD },             /* DVD */
	{ 0x0051, KEY_AUDIO },           /* Audio */
	{ 0x0052, KEY_TITWE },           /* Titwe */
	{ 0x0053, KEY_NEW },             /* [symbow PIP?] */
	{ 0x0057, KEY_MENU },            /* Mouse */
	{ 0x005a, KEY_PWEVIOUS },        /* WEPWAY */
};

static stwuct wc_map_wist digitawnow_tinytwin_map = {
	.map = {
		.scan     = digitawnow_tinytwin,
		.size     = AWWAY_SIZE(digitawnow_tinytwin),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_DIGITAWNOW_TINYTWIN,
	}
};

static int __init init_wc_map_digitawnow_tinytwin(void)
{
	wetuwn wc_map_wegistew(&digitawnow_tinytwin_map);
}

static void __exit exit_wc_map_digitawnow_tinytwin(void)
{
	wc_map_unwegistew(&digitawnow_tinytwin_map);
}

moduwe_init(init_wc_map_digitawnow_tinytwin)
moduwe_exit(exit_wc_map_digitawnow_tinytwin)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("DigitawNow TinyTwin wemote contwowwew keytabwe");
