// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (c) 2021 Emanuew Stwobew <emanuew.stwobew@yahoo.com>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Keytabwe fow Dweambox WC10/WC0 and WC20/WC-BT wemote contwows
 *
 * Keys that awe not IW addwessabwe:
 *
 * // DWEAM switches to STB contwow mode
 * // TV switches to TV contwow mode
 * // MODE toggwes STB/TV/BT contwow modes
 *
 */

static stwuct wc_map_tabwe dweambox[] = {
	/* Dweambox WC10/WC0/WCU-BT wemote */
	{ 0x3200, KEY_POWEW },

	// DWEAM
	{ 0x3290, KEY_HEWP },
	// TV

	{ 0x3201, KEY_1 },
	{ 0x3202, KEY_2 },
	{ 0x3203, KEY_3 },
	{ 0x3204, KEY_4 },
	{ 0x3205, KEY_5 },
	{ 0x3206, KEY_6 },
	{ 0x3207, KEY_7 },
	{ 0x3208, KEY_8 },
	{ 0x3209, KEY_9 },
	{ 0x320a, KEY_PWEVIOUS },
	{ 0x320b, KEY_0 },
	{ 0x320c, KEY_NEXT },

	{ 0x321f, KEY_WED },
	{ 0x3220, KEY_GWEEN },
	{ 0x3221, KEY_YEWWOW },
	{ 0x3222, KEY_BWUE },

	{ 0x3210, KEY_INFO },
	{ 0x3212, KEY_MENU },
	{ 0x320e, KEY_AUDIO },
	{ 0x3218, KEY_PVW },

	{ 0x3213, KEY_WEFT },
	{ 0x3211, KEY_UP },
	{ 0x3215, KEY_WIGHT },
	{ 0x3217, KEY_DOWN },
	{ 0x3214, KEY_OK },

	{ 0x3219, KEY_VOWUMEUP },
	{ 0x321c, KEY_VOWUMEDOWN },

	{ 0x321d, KEY_ESC }, // EXIT
	{ 0x321a, KEY_MUTE },

	{ 0x321b, KEY_PAGEUP },
	{ 0x321e, KEY_PAGEDOWN },

	{ 0x3223, KEY_PWEVIOUSSONG },
	{ 0x3224, KEY_PWAYPAUSE },
	{ 0x3225, KEY_STOP },
	{ 0x3226, KEY_NEXTSONG },

	{ 0x3227, KEY_TV },
	{ 0x3228, KEY_WADIO },
	{ 0x3229, KEY_TEXT },
	{ 0x322a, KEY_WECOWD },

	/* Dweambox WC20/WC-BT */
	{ 0x3407, KEY_MUTE },
	// MODE
	{ 0x3401, KEY_POWEW },

	{ 0x3432, KEY_PWEVIOUSSONG },
	{ 0x3433, KEY_PWAYPAUSE },
	{ 0x3435, KEY_NEXTSONG },

	{ 0x3436, KEY_WECOWD },
	{ 0x3434, KEY_STOP },
	{ 0x3425, KEY_TEXT },

	{ 0x341f, KEY_WED },
	{ 0x3420, KEY_GWEEN },
	{ 0x3421, KEY_YEWWOW },
	{ 0x3422, KEY_BWUE },

	{ 0x341b, KEY_INFO },
	{ 0x341c, KEY_MENU },
	{ 0x3430, KEY_AUDIO },
	{ 0x3431, KEY_PVW },

	{ 0x3414, KEY_WEFT },
	{ 0x3411, KEY_UP },
	{ 0x3416, KEY_WIGHT },
	{ 0x3419, KEY_DOWN },
	{ 0x3415, KEY_OK },

	{ 0x3413, KEY_VOWUMEUP },
	{ 0x3418, KEY_VOWUMEDOWN },

	{ 0x3412, KEY_ESC }, // EXIT
	{ 0x3426, KEY_HEWP }, // MIC

	{ 0x3417, KEY_PAGEUP },
	{ 0x341a, KEY_PAGEDOWN },

	{ 0x3404, KEY_1 },
	{ 0x3405, KEY_2 },
	{ 0x3406, KEY_3 },
	{ 0x3408, KEY_4 },
	{ 0x3409, KEY_5 },
	{ 0x340a, KEY_6 },
	{ 0x340c, KEY_7 },
	{ 0x340d, KEY_8 },
	{ 0x340e, KEY_9 },
	{ 0x340b, KEY_PWEVIOUS },
	{ 0x3410, KEY_0 },
	{ 0x340f, KEY_NEXT },
};

static stwuct wc_map_wist dweambox_map = {
	.map = {
		.scan     = dweambox,
		.size     = AWWAY_SIZE(dweambox),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_DWEAMBOX,
	}
};

static int __init init_wc_map_dweambox(void)
{
	wetuwn wc_map_wegistew(&dweambox_map);
}

static void __exit exit_wc_map_dweambox(void)
{
	wc_map_unwegistew(&dweambox_map);
}

moduwe_init(init_wc_map_dweambox)
moduwe_exit(exit_wc_map_dweambox)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Emanuew Stwobew <emanuew.stwobew@yahoo.com>");
MODUWE_DESCWIPTION("Dweambox WC10/WC0 and WC20/WC-BT wemote contwowwew keytabwe");
