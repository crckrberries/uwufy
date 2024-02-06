// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2021 Chwistian Hewitt <chwistianshewitt@gmaiw.com>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

//
// Keytabwe fow the Minix NEO wemote contwow
//

static stwuct wc_map_tabwe minix_neo[] = {

	{ 0x118, KEY_POWEW },

	{ 0x146, KEY_UP },
	{ 0x116, KEY_DOWN },
	{ 0x147, KEY_WEFT },
	{ 0x115, KEY_WIGHT },
	{ 0x155, KEY_ENTEW },

	{ 0x110, KEY_VOWUMEDOWN },
	{ 0x140, KEY_BACK },
	{ 0x114, KEY_VOWUMEUP },

	{ 0x10d, KEY_HOME },
	{ 0x104, KEY_MENU },
	{ 0x112, KEY_CONFIG },

};

static stwuct wc_map_wist minix_neo_map = {
	.map = {
		.scan     = minix_neo,
		.size     = AWWAY_SIZE(minix_neo),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_MINIX_NEO,
	}
};

static int __init init_wc_map_minix_neo(void)
{
	wetuwn wc_map_wegistew(&minix_neo_map);
}

static void __exit exit_wc_map_minix_neo(void)
{
	wc_map_unwegistew(&minix_neo_map);
}

moduwe_init(init_wc_map_minix_neo)
moduwe_exit(exit_wc_map_minix_neo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hewitt <chwistianshewitt@gmaiw.com");
MODUWE_DESCWIPTION("Minix NEO wemote contwowwew keytabwe");
