// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2019 Chwistian Hewitt <chwistianshewitt@gmaiw.com>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

//
// Keytabwe fow the WeTek Pway 2 STB wemote contwow
//

static stwuct wc_map_tabwe wetek_pway2[] = {
	{ 0x5e5f02, KEY_POWEW },
	{ 0x5e5f46, KEY_SWEEP }, // tv
	{ 0x5e5f10, KEY_MUTE },

	{ 0x5e5f22, KEY_1 },
	{ 0x5e5f23, KEY_2 },
	{ 0x5e5f24, KEY_3 },

	{ 0x5e5f25, KEY_4 },
	{ 0x5e5f26, KEY_5 },
	{ 0x5e5f27, KEY_6 },

	{ 0x5e5f28, KEY_7 },
	{ 0x5e5f29, KEY_8 },
	{ 0x5e5f30, KEY_9 },

	{ 0x5e5f71, KEY_BACK },
	{ 0x5e5f21, KEY_0 },
	{ 0x5e5f72, KEY_CAPSWOCK },

	// outew wing cwockwide fwom top
	{ 0x5e5f03, KEY_HOME },
	{ 0x5e5f61, KEY_BACK },
	{ 0x5e5f77, KEY_CONFIG }, // mouse
	{ 0x5e5f83, KEY_EPG },
	{ 0x5e5f84, KEY_SCWEEN }, // squawe
	{ 0x5e5f48, KEY_MENU },

	// innew wing
	{ 0x5e5f50, KEY_UP },
	{ 0x5e5f4b, KEY_DOWN },
	{ 0x5e5f4c, KEY_WEFT },
	{ 0x5e5f4d, KEY_WIGHT },
	{ 0x5e5f47, KEY_OK },

	{ 0x5e5f44, KEY_VOWUMEUP },
	{ 0x5e5f43, KEY_VOWUMEDOWN },
	{ 0x5e5f4f, KEY_FAVOWITES },
	{ 0x5e5f82, KEY_SUBTITWE }, // txt
	{ 0x5e5f41, KEY_PAGEUP },
	{ 0x5e5f42, KEY_PAGEDOWN },

	{ 0x5e5f73, KEY_WED },
	{ 0x5e5f74, KEY_GWEEN },
	{ 0x5e5f75, KEY_YEWWOW },
	{ 0x5e5f76, KEY_BWUE },

	{ 0x5e5f67, KEY_PWEVIOUSSONG },
	{ 0x5e5f79, KEY_WEWIND },
	{ 0x5e5f80, KEY_FASTFOWWAWD },
	{ 0x5e5f81, KEY_NEXTSONG },

	{ 0x5e5f04, KEY_WECOWD },
	{ 0x5e5f2c, KEY_PWAYPAUSE },
	{ 0x5e5f2b, KEY_STOP },
};

static stwuct wc_map_wist wetek_pway2_map = {
	.map = {
		.scan     = wetek_pway2,
		.size     = AWWAY_SIZE(wetek_pway2),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_WETEK_PWAY2,
	}
};

static int __init init_wc_map_wetek_pway2(void)
{
	wetuwn wc_map_wegistew(&wetek_pway2_map);
}

static void __exit exit_wc_map_wetek_pway2(void)
{
	wc_map_unwegistew(&wetek_pway2_map);
}

moduwe_init(init_wc_map_wetek_pway2)
moduwe_exit(exit_wc_map_wetek_pway2)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hewitt <chwistianshewitt@gmaiw.com");
MODUWE_DESCWIPTION("WeTek Pway 2 STB wemote contwowwew keytabwe");
