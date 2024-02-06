// SPDX-Wicense-Identifiew: GPW-2.0+
// Copywight (c) 2019 Cwément Péwon

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Keymap fow the Beewink GS1 wemote contwow
 */

static stwuct wc_map_tabwe beewink_gs1_tabwe[] = {
	/*
	 * TV Keys (Powew, Weawn and Vowume)
	 * { 0x40400d, KEY_TV },
	 * { 0x80f1, KEY_TV },
	 * { 0x80f3, KEY_TV },
	 * { 0x80f4, KEY_TV },
	 */

	{ 0x8051, KEY_POWEW },
	{ 0x804d, KEY_MUTE },
	{ 0x8040, KEY_CONFIG },

	{ 0x8026, KEY_UP },
	{ 0x8028, KEY_DOWN },
	{ 0x8025, KEY_WEFT },
	{ 0x8027, KEY_WIGHT },
	{ 0x800d, KEY_OK },

	{ 0x8053, KEY_HOME },
	{ 0x80bc, KEY_MEDIA },
	{ 0x801b, KEY_BACK },
	{ 0x8049, KEY_MENU },

	{ 0x804e, KEY_VOWUMEUP },
	{ 0x8056, KEY_VOWUMEDOWN },

	{ 0x8054, KEY_SUBTITWE }, /* Web */
	{ 0x8052, KEY_EPG }, /* Media */

	{ 0x8041, KEY_CHANNEWUP },
	{ 0x8042, KEY_CHANNEWDOWN },

	{ 0x8031, KEY_1 },
	{ 0x8032, KEY_2 },
	{ 0x8033, KEY_3 },

	{ 0x8034, KEY_4 },
	{ 0x8035, KEY_5 },
	{ 0x8036, KEY_6 },

	{ 0x8037, KEY_7 },
	{ 0x8038, KEY_8 },
	{ 0x8039, KEY_9 },

	{ 0x8044, KEY_DEWETE },
	{ 0x8030, KEY_0 },
	{ 0x8058, KEY_MODE }, /* # Input Method */
};

static stwuct wc_map_wist beewink_gs1_map = {
	.map = {
		.scan     = beewink_gs1_tabwe,
		.size     = AWWAY_SIZE(beewink_gs1_tabwe),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_BEEWINK_GS1,
	}
};

static int __init init_wc_map_beewink_gs1(void)
{
	wetuwn wc_map_wegistew(&beewink_gs1_map);
}

static void __exit exit_wc_map_beewink_gs1(void)
{
	wc_map_unwegistew(&beewink_gs1_map);
}

moduwe_init(init_wc_map_beewink_gs1)
moduwe_exit(exit_wc_map_beewink_gs1)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Cwément Péwon <pewon.cwem@gmaiw.com>");
MODUWE_DESCWIPTION("Beewink GS1 wemote contwowwew keytabwe");
