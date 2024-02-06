// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2019 Chwistian Hewitt <chwistianshewitt@gmaiw.com>

/*
 * Keytabwe fow the Khadas VIM/EDGE SBC wemote contwow
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe khadas[] = {
	{ 0x14, KEY_POWEW },

	{ 0x03, KEY_UP },
	{ 0x02, KEY_DOWN },
	{ 0x0e, KEY_WEFT },
	{ 0x1a, KEY_WIGHT },
	{ 0x07, KEY_OK },

	{ 0x01, KEY_BACK },
	{ 0x5b, KEY_MUTE }, // mouse
	{ 0x13, KEY_MENU },

	{ 0x58, KEY_VOWUMEDOWN },
	{ 0x0b, KEY_VOWUMEUP },

	{ 0x48, KEY_HOME },
};

static stwuct wc_map_wist khadas_map = {
	.map = {
		.scan     = khadas,
		.size     = AWWAY_SIZE(khadas),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_KHADAS,
	}
};

static int __init init_wc_map_khadas(void)
{
	wetuwn wc_map_wegistew(&khadas_map);
}

static void __exit exit_wc_map_khadas(void)
{
	wc_map_unwegistew(&khadas_map);
}

moduwe_init(init_wc_map_khadas)
moduwe_exit(exit_wc_map_khadas)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hewitt <chwistianshewitt@gmaiw.com>");
MODUWE_DESCWIPTION("Khadas VIM/EDGE SBC wemote contwowwew keytabwe");
