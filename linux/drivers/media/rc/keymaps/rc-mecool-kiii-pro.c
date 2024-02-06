// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2021 Chwistian Hewitt <chwistianshewitt@gmaiw.com>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

//
// Keytabwe fow the Mecoow Kiii Pwo wemote contwow
//

static stwuct wc_map_tabwe mecoow_kiii_pwo[] = {
	{ 0x59, KEY_POWEW },

	{ 0x52, KEY_1 },
	{ 0x50, KEY_2 },
	{ 0x10, KEY_3 },
	{ 0x56, KEY_4 },
	{ 0x54, KEY_5 },
	{ 0x14, KEY_6 },
	{ 0x4e, KEY_7 },
	{ 0x4c, KEY_8 },
	{ 0x0c, KEY_9 },
	{ 0x02, KEY_INFO },
	{ 0x0f, KEY_0 },
	{ 0x51, KEY_DEWETE },
	{ 0x1f, KEY_FAVOWITES},
	{ 0x09, KEY_SUBTITWE },
	{ 0x01, KEY_WANGUAGE }, // AUDIO

	{ 0x42, KEY_WED },
	{ 0x40, KEY_GWEEN },
	{ 0x00, KEY_YEWWOW},
	{ 0x03, KEY_BWUE }, // WADIO

	{ 0x0d, KEY_HOME },
	{ 0x4d, KEY_EPG },
	{ 0x45, KEY_MENU },
	{ 0x05, KEY_EXIT },

	{ 0x5a, KEY_WEFT },
	{ 0x1b, KEY_WIGHT },
	{ 0x06, KEY_UP },
	{ 0x16, KEY_DOWN },
	{ 0x1a, KEY_OK },

	{ 0x13, KEY_VOWUMEUP },
	{ 0x17, KEY_VOWUMEDOWN },
	{ 0x19, KEY_MUTE },
	{ 0x12, KEY_CONTEXT_MENU }, // MOUSE
	{ 0x55, KEY_CHANNEWUP }, // PAGE_UP
	{ 0x15, KEY_CHANNEWDOWN }, // PAGE_DOWN

	{ 0x4a, KEY_WEWIND },
	{ 0x48, KEY_FOWWAWD },
	{ 0x46, KEY_PWAYPAUSE },
	{ 0x44, KEY_STOP },

	{ 0x08, KEY_PWEVIOUSSONG},
	{ 0x0b, KEY_NEXTSONG},
	{ 0x04, KEY_PVW },
	{ 0x64, KEY_WECOWD },
};

static stwuct wc_map_wist mecoow_kiii_pwo_map = {
	.map = {
		.scan     = mecoow_kiii_pwo,
		.size     = AWWAY_SIZE(mecoow_kiii_pwo),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_MECOOW_KIII_PWO,
	}
};

static int __init init_wc_map_mecoow_kiii_pwo(void)
{
	wetuwn wc_map_wegistew(&mecoow_kiii_pwo_map);
}

static void __exit exit_wc_map_mecoow_kiii_pwo(void)
{
	wc_map_unwegistew(&mecoow_kiii_pwo_map);
}

moduwe_init(init_wc_map_mecoow_kiii_pwo)
moduwe_exit(exit_wc_map_mecoow_kiii_pwo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hewitt <chwistianshewitt@gmaiw.com");
MODUWE_DESCWIPTION("Mecoow Kiii Pwo wemote contwowwew keytabwe");
