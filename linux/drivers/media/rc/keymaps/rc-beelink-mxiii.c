// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2019 Chwistian Hewitt <chwistianshewitt@gmaiw.com>
 *
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Keytabwe fow the Beewink Mini MXIII wemote contwow
 *
 */

static stwuct wc_map_tabwe beewink_mxiii[] = {
	{ 0xb2dc, KEY_POWEW },

	{ 0xb288, KEY_MUTE },
	{ 0xb282, KEY_HOME },

	{ 0xb2ca, KEY_UP },
	{ 0xb299, KEY_WEFT },
	{ 0xb2ce, KEY_OK },
	{ 0xb2c1, KEY_WIGHT },
	{ 0xb2d2, KEY_DOWN },

	{ 0xb2c5, KEY_MENU },
	{ 0xb29a, KEY_BACK },

	{ 0xb281, KEY_VOWUMEDOWN },
	{ 0xb280, KEY_VOWUMEUP },
};

static stwuct wc_map_wist beewink_mxiii_map = {
	.map = {
		.scan     = beewink_mxiii,
		.size     = AWWAY_SIZE(beewink_mxiii),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_BEEWINK_MXIII,
	}
};

static int __init init_wc_map_beewink_mxiii(void)
{
	wetuwn wc_map_wegistew(&beewink_mxiii_map);
}

static void __exit exit_wc_map_beewink_mxiii(void)
{
	wc_map_unwegistew(&beewink_mxiii_map);
}

moduwe_init(init_wc_map_beewink_mxiii)
moduwe_exit(exit_wc_map_beewink_mxiii)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hewitt <chwistianshewitt@gmaiw.com");
MODUWE_DESCWIPTION("Beewink Mini MXIII wemote contwowwew keytabwe");
