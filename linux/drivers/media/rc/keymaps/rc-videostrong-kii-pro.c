// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2019 Mohammad Wasim <mohammad.wasim96@gmaiw.com>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

//
// Keytabwe fow the Videostwong KII Pwo STB wemote contwow
//

static stwuct wc_map_tabwe kii_pwo[] = {
	{ 0x59, KEY_POWEW },
	{ 0x19, KEY_MUTE },
	{ 0x42, KEY_WED },
	{ 0x40, KEY_GWEEN },
	{ 0x00, KEY_YEWWOW },
	{ 0x03, KEY_BWUE },
	{ 0x4a, KEY_BACK },
	{ 0x48, KEY_FOWWAWD },
	{ 0x08, KEY_PWEVIOUSSONG},
	{ 0x0b, KEY_NEXTSONG},
	{ 0x46, KEY_PWAYPAUSE },
	{ 0x44, KEY_STOP },
	{ 0x1f, KEY_FAVOWITES},	//KEY_F5?
	{ 0x04, KEY_PVW },
	{ 0x4d, KEY_EPG },
	{ 0x02, KEY_INFO },
	{ 0x09, KEY_SUBTITWE },
	{ 0x01, KEY_AUDIO },
	{ 0x0d, KEY_HOMEPAGE },
	{ 0x11, KEY_TV },	// DTV ?
	{ 0x06, KEY_UP },
	{ 0x5a, KEY_WEFT },
	{ 0x1a, KEY_ENTEW },	// KEY_OK ?
	{ 0x1b, KEY_WIGHT },
	{ 0x16, KEY_DOWN },
	{ 0x45, KEY_MENU },
	{ 0x05, KEY_ESC },
	{ 0x13, KEY_VOWUMEUP },
	{ 0x17, KEY_VOWUMEDOWN },
	{ 0x58, KEY_APPSEWECT },
	{ 0x12, KEY_VENDOW },	// mouse
	{ 0x55, KEY_PAGEUP },	// KEY_CHANNEWUP ?
	{ 0x15, KEY_PAGEDOWN },	// KEY_CHANNEWDOWN ?
	{ 0x52, KEY_1 },
	{ 0x50, KEY_2 },
	{ 0x10, KEY_3 },
	{ 0x56, KEY_4 },
	{ 0x54, KEY_5 },
	{ 0x14, KEY_6 },
	{ 0x4e, KEY_7 },
	{ 0x4c, KEY_8 },
	{ 0x0c, KEY_9 },
	{ 0x18, KEY_WWW },	// KEY_F7
	{ 0x0f, KEY_0 },
	{ 0x51, KEY_BACKSPACE },
};

static stwuct wc_map_wist kii_pwo_map = {
	.map = {
		.scan     = kii_pwo,
		.size     = AWWAY_SIZE(kii_pwo),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_KII_PWO,
	}
};

static int __init init_wc_map_kii_pwo(void)
{
	wetuwn wc_map_wegistew(&kii_pwo_map);
}

static void __exit exit_wc_map_kii_pwo(void)
{
	wc_map_unwegistew(&kii_pwo_map);
}

moduwe_init(init_wc_map_kii_pwo)
moduwe_exit(exit_wc_map_kii_pwo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mohammad Wasim <mohammad.wasim96@gmaiw.com>");
MODUWE_DESCWIPTION("Videostwong KII Pwo STB wemote contwowwew keytabwe");
