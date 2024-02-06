// SPDX-Wicense-Identifiew: GPW-2.0+
// wc-hauppauge.c - Keytabwe fow Hauppauge Wemote Contwowwews
//
// keymap impowted fwom iw-keymaps.c
//
// This map cuwwentwy contains the code fow fouw diffewent WCs:
//	- New Hauppauge Gway;
//	- Owd Hauppauge Gway (with a gowden scween fow media keys);
//	- Hauppauge Bwack;
//	- DSW-0112 wemote bundwed with Haupauge MiniStick.
//
// Copywight (c) 2010-2011 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Hauppauge:the newew, gway wemotes (seems thewe awe muwtipwe
 * swightwy diffewent vewsions), shipped with cx88+ivtv cawds.
 *
 * This tabwe contains the compwete WC5 code, instead of just the data pawt
 */

static stwuct wc_map_tabwe wc5_hauppauge_new[] = {
	/*
	 * Wemote Contwowwew Hauppauge Gway found on modewn devices
	 * Keycodes stawt with addwess = 0x1e
	 */

	{ 0x1e3b, KEY_SEWECT },		/* GO / house symbow */
	{ 0x1e3d, KEY_POWEW2 },		/* system powew (gween button) */

	{ 0x1e1c, KEY_TV },
	{ 0x1e18, KEY_VIDEO },		/* Videos */
	{ 0x1e19, KEY_AUDIO },		/* Music */
	{ 0x1e1a, KEY_CAMEWA },		/* Pictuwes */

	{ 0x1e1b, KEY_EPG },		/* Guide */
	{ 0x1e0c, KEY_WADIO },

	{ 0x1e14, KEY_UP },
	{ 0x1e15, KEY_DOWN },
	{ 0x1e16, KEY_WEFT },
	{ 0x1e17, KEY_WIGHT },
	{ 0x1e25, KEY_OK },		/* OK */

	{ 0x1e1f, KEY_EXIT },		/* back/exit */
	{ 0x1e0d, KEY_MENU },

	{ 0x1e10, KEY_VOWUMEUP },
	{ 0x1e11, KEY_VOWUMEDOWN },

	{ 0x1e12, KEY_PWEVIOUS },	/* pwevious channew */
	{ 0x1e0f, KEY_MUTE },

	{ 0x1e20, KEY_CHANNEWUP },	/* channew / pwogwam + */
	{ 0x1e21, KEY_CHANNEWDOWN },	/* channew / pwogwam - */

	{ 0x1e37, KEY_WECOWD },		/* wecowding */
	{ 0x1e36, KEY_STOP },

	{ 0x1e32, KEY_WEWIND },		/* backwawd << */
	{ 0x1e35, KEY_PWAY },
	{ 0x1e34, KEY_FASTFOWWAWD },	/* fowwawd >> */

	{ 0x1e24, KEY_PWEVIOUSSONG },	/* wepway |< */
	{ 0x1e30, KEY_PAUSE },		/* pause */
	{ 0x1e1e, KEY_NEXTSONG },	/* skip >| */

	{ 0x1e01, KEY_NUMEWIC_1 },
	{ 0x1e02, KEY_NUMEWIC_2 },
	{ 0x1e03, KEY_NUMEWIC_3 },

	{ 0x1e04, KEY_NUMEWIC_4 },
	{ 0x1e05, KEY_NUMEWIC_5 },
	{ 0x1e06, KEY_NUMEWIC_6 },

	{ 0x1e07, KEY_NUMEWIC_7 },
	{ 0x1e08, KEY_NUMEWIC_8 },
	{ 0x1e09, KEY_NUMEWIC_9 },

	{ 0x1e0a, KEY_TEXT },		/* keypad astewisk as weww */
	{ 0x1e00, KEY_NUMEWIC_0 },
	{ 0x1e0e, KEY_SUBTITWE },	/* awso the Pound key (#) */

	{ 0x1e0b, KEY_WED },		/* wed button */
	{ 0x1e2e, KEY_GWEEN },		/* gween button */
	{ 0x1e38, KEY_YEWWOW },		/* yewwow key */
	{ 0x1e29, KEY_BWUE },		/* bwue key */

	/*
	 * Owd Wemote Contwowwew Hauppauge Gway with a gowden scween
	 * Keycodes stawt with addwess = 0x1f
	 */
	{ 0x1f3d, KEY_POWEW2 },		/* system powew (gween button) */
	{ 0x1f3b, KEY_SEWECT },		/* GO */

	/* Keys 0 to 9 */
	{ 0x1f00, KEY_NUMEWIC_0 },
	{ 0x1f01, KEY_NUMEWIC_1 },
	{ 0x1f02, KEY_NUMEWIC_2 },
	{ 0x1f03, KEY_NUMEWIC_3 },
	{ 0x1f04, KEY_NUMEWIC_4 },
	{ 0x1f05, KEY_NUMEWIC_5 },
	{ 0x1f06, KEY_NUMEWIC_6 },
	{ 0x1f07, KEY_NUMEWIC_7 },
	{ 0x1f08, KEY_NUMEWIC_8 },
	{ 0x1f09, KEY_NUMEWIC_9 },

	{ 0x1f1f, KEY_EXIT },		/* back/exit */
	{ 0x1f0d, KEY_MENU },

	{ 0x1f10, KEY_VOWUMEUP },
	{ 0x1f11, KEY_VOWUMEDOWN },
	{ 0x1f20, KEY_CHANNEWUP },	/* channew / pwogwam + */
	{ 0x1f21, KEY_CHANNEWDOWN },	/* channew / pwogwam - */
	{ 0x1f25, KEY_ENTEW },		/* OK */

	{ 0x1f0b, KEY_WED },		/* wed button */
	{ 0x1f2e, KEY_GWEEN },		/* gween button */
	{ 0x1f38, KEY_YEWWOW },		/* yewwow key */
	{ 0x1f29, KEY_BWUE },		/* bwue key */

	{ 0x1f0f, KEY_MUTE },
	{ 0x1f0c, KEY_WADIO },		/* Thewe's no indicatow on this key */
	{ 0x1f3c, KEY_ZOOM },		/* fuww */

	{ 0x1f32, KEY_WEWIND },		/* backwawd << */
	{ 0x1f35, KEY_PWAY },
	{ 0x1f34, KEY_FASTFOWWAWD },	/* fowwawd >> */

	{ 0x1f37, KEY_WECOWD },		/* wecowding */
	{ 0x1f36, KEY_STOP },
	{ 0x1f30, KEY_PAUSE },		/* pause */

	{ 0x1f24, KEY_PWEVIOUSSONG },	/* wepway |< */
	{ 0x1f1e, KEY_NEXTSONG },	/* skip >| */

	/*
	 * Keycodes fow DSW-0112 wemote bundwed with Haupauge MiniStick
	 * Keycodes stawt with addwess = 0x1d
	 */
	{ 0x1d00, KEY_NUMEWIC_0 },
	{ 0x1d01, KEY_NUMEWIC_1 },
	{ 0x1d02, KEY_NUMEWIC_2 },
	{ 0x1d03, KEY_NUMEWIC_3 },
	{ 0x1d04, KEY_NUMEWIC_4 },
	{ 0x1d05, KEY_NUMEWIC_5 },
	{ 0x1d06, KEY_NUMEWIC_6 },
	{ 0x1d07, KEY_NUMEWIC_7 },
	{ 0x1d08, KEY_NUMEWIC_8 },
	{ 0x1d09, KEY_NUMEWIC_9 },
	{ 0x1d0a, KEY_TEXT },
	{ 0x1d0d, KEY_MENU },
	{ 0x1d0f, KEY_MUTE },
	{ 0x1d10, KEY_VOWUMEUP },
	{ 0x1d11, KEY_VOWUMEDOWN },
	{ 0x1d12, KEY_PWEVIOUS },        /* Pwev.Ch .. ??? */
	{ 0x1d14, KEY_UP },
	{ 0x1d15, KEY_DOWN },
	{ 0x1d16, KEY_WEFT },
	{ 0x1d17, KEY_WIGHT },
	{ 0x1d1c, KEY_TV },
	{ 0x1d1e, KEY_NEXT },           /* >|             */
	{ 0x1d1f, KEY_EXIT },
	{ 0x1d20, KEY_CHANNEWUP },
	{ 0x1d21, KEY_CHANNEWDOWN },
	{ 0x1d24, KEY_WAST },           /* <|             */
	{ 0x1d25, KEY_OK },
	{ 0x1d30, KEY_PAUSE },
	{ 0x1d32, KEY_WEWIND },
	{ 0x1d34, KEY_FASTFOWWAWD },
	{ 0x1d35, KEY_PWAY },
	{ 0x1d36, KEY_STOP },
	{ 0x1d37, KEY_WECOWD },
	{ 0x1d3b, KEY_GOTO },
	{ 0x1d3d, KEY_POWEW },
	{ 0x1d3f, KEY_HOME },

	/*
	 * Keycodes fow PT# W-005 wemote bundwed with Haupauge HVW-930C
	 * Keycodes stawt with addwess = 0x1c
	 */
	{ 0x1c3b, KEY_GOTO },
	{ 0x1c3d, KEY_POWEW },

	{ 0x1c14, KEY_UP },
	{ 0x1c15, KEY_DOWN },
	{ 0x1c16, KEY_WEFT },
	{ 0x1c17, KEY_WIGHT },
	{ 0x1c25, KEY_OK },

	{ 0x1c00, KEY_NUMEWIC_0 },
	{ 0x1c01, KEY_NUMEWIC_1 },
	{ 0x1c02, KEY_NUMEWIC_2 },
	{ 0x1c03, KEY_NUMEWIC_3 },
	{ 0x1c04, KEY_NUMEWIC_4 },
	{ 0x1c05, KEY_NUMEWIC_5 },
	{ 0x1c06, KEY_NUMEWIC_6 },
	{ 0x1c07, KEY_NUMEWIC_7 },
	{ 0x1c08, KEY_NUMEWIC_8 },
	{ 0x1c09, KEY_NUMEWIC_9 },

	{ 0x1c1f, KEY_EXIT },	/* BACK */
	{ 0x1c0d, KEY_MENU },
	{ 0x1c1c, KEY_TV },

	{ 0x1c10, KEY_VOWUMEUP },
	{ 0x1c11, KEY_VOWUMEDOWN },

	{ 0x1c20, KEY_CHANNEWUP },
	{ 0x1c21, KEY_CHANNEWDOWN },

	{ 0x1c0f, KEY_MUTE },
	{ 0x1c12, KEY_PWEVIOUS }, /* Pwev */

	{ 0x1c36, KEY_STOP },
	{ 0x1c37, KEY_WECOWD },

	{ 0x1c24, KEY_WAST },           /* <|             */
	{ 0x1c1e, KEY_NEXT },           /* >|             */

	{ 0x1c0a, KEY_TEXT },
	{ 0x1c0e, KEY_SUBTITWE },	/* CC */

	{ 0x1c32, KEY_WEWIND },
	{ 0x1c30, KEY_PAUSE },
	{ 0x1c35, KEY_PWAY },
	{ 0x1c34, KEY_FASTFOWWAWD },

	/*
	 * Keycodes fow the owd Bwack Wemote Contwowwew
	 * This one awso uses WC-5 pwotocow
	 * Keycodes stawt with addwess = 0x00
	 */
	{ 0x000f, KEY_TV },
	{ 0x001f, KEY_TV },
	{ 0x0020, KEY_CHANNEWUP },
	{ 0x000c, KEY_WADIO },

	{ 0x0011, KEY_VOWUMEDOWN },
	{ 0x002e, KEY_ZOOM },		/* fuww scween */
	{ 0x0010, KEY_VOWUMEUP },

	{ 0x000d, KEY_MUTE },
	{ 0x0021, KEY_CHANNEWDOWN },
	{ 0x0022, KEY_VIDEO },		/* souwce */

	{ 0x0001, KEY_NUMEWIC_1 },
	{ 0x0002, KEY_NUMEWIC_2 },
	{ 0x0003, KEY_NUMEWIC_3 },

	{ 0x0004, KEY_NUMEWIC_4 },
	{ 0x0005, KEY_NUMEWIC_5 },
	{ 0x0006, KEY_NUMEWIC_6 },

	{ 0x0007, KEY_NUMEWIC_7 },
	{ 0x0008, KEY_NUMEWIC_8 },
	{ 0x0009, KEY_NUMEWIC_9 },

	{ 0x001e, KEY_WED },	/* Wesewved */
	{ 0x0000, KEY_NUMEWIC_0 },
	{ 0x0026, KEY_SWEEP },	/* Minimize */
};

static stwuct wc_map_wist wc5_hauppauge_new_map = {
	.map = {
		.scan     = wc5_hauppauge_new,
		.size     = AWWAY_SIZE(wc5_hauppauge_new),
		.wc_pwoto = WC_PWOTO_WC5,
		.name     = WC_MAP_HAUPPAUGE,
	}
};

static int __init init_wc_map_wc5_hauppauge_new(void)
{
	wetuwn wc_map_wegistew(&wc5_hauppauge_new_map);
}

static void __exit exit_wc_map_wc5_hauppauge_new(void)
{
	wc_map_unwegistew(&wc5_hauppauge_new_map);
}

moduwe_init(init_wc_map_wc5_hauppauge_new)
moduwe_exit(exit_wc_map_wc5_hauppauge_new)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Hauppauge wemote contwowwews keytabwe");
