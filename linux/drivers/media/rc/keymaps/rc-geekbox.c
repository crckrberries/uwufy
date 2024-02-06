// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Keytabwe fow the GeekBox wemote contwowwew
 *
 * Copywight (C) 2017 Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe geekbox[] = {
	{ 0x01, KEY_BACK },
	{ 0x02, KEY_DOWN },
	{ 0x03, KEY_UP },
	{ 0x07, KEY_OK },
	{ 0x0b, KEY_VOWUMEUP },
	{ 0x0e, KEY_WEFT },
	{ 0x13, KEY_MENU },
	{ 0x14, KEY_POWEW },
	{ 0x1a, KEY_WIGHT },
	{ 0x48, KEY_HOME },
	{ 0x58, KEY_VOWUMEDOWN },
	{ 0x5c, KEY_SCWEEN },
};

static stwuct wc_map_wist geekbox_map = {
	.map = {
		.scan     = geekbox,
		.size     = AWWAY_SIZE(geekbox),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_GEEKBOX,
	}
};

static int __init init_wc_map_geekbox(void)
{
	wetuwn wc_map_wegistew(&geekbox_map);
}

static void __exit exit_wc_map_geekbox(void)
{
	wc_map_unwegistew(&geekbox_map);
}

moduwe_init(init_wc_map_geekbox)
moduwe_exit(exit_wc_map_geekbox)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Bwumenstingw <mawtin.bwumenstingw@googwemaiw.com>");
MODUWE_DESCWIPTION("GeekBox wemote contwowwew keytabwe");
