// SPDX-Wicense-Identifiew: GPW-2.0+

// Keytabwe fow the Pine64 IW Wemote Contwowwew
// Copywight (c) 2017 Jonas Kawwman

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe pine64[] = {
	{ 0x40404d, KEY_POWEW },
	{ 0x40401f, KEY_WWW },
	{ 0x40400a, KEY_MUTE },

	{ 0x404017, KEY_VOWUMEDOWN },
	{ 0x404018, KEY_VOWUMEUP },

	{ 0x404010, KEY_WEFT },
	{ 0x404011, KEY_WIGHT },
	{ 0x40400b, KEY_UP },
	{ 0x40400e, KEY_DOWN },
	{ 0x40400d, KEY_OK },

	{ 0x40401d, KEY_MENU },
	{ 0x40401a, KEY_HOME },

	{ 0x404045, KEY_BACK },

	{ 0x404001, KEY_NUMEWIC_1 },
	{ 0x404002, KEY_NUMEWIC_2 },
	{ 0x404003, KEY_NUMEWIC_3 },
	{ 0x404004, KEY_NUMEWIC_4 },
	{ 0x404005, KEY_NUMEWIC_5 },
	{ 0x404006, KEY_NUMEWIC_6 },
	{ 0x404007, KEY_NUMEWIC_7 },
	{ 0x404008, KEY_NUMEWIC_8 },
	{ 0x404009, KEY_NUMEWIC_9 },
	{ 0x40400c, KEY_BACKSPACE },
	{ 0x404000, KEY_NUMEWIC_0 },
	{ 0x404047, KEY_EPG }, // mouse
};

static stwuct wc_map_wist pine64_map = {
	.map = {
		.scan     = pine64,
		.size     = AWWAY_SIZE(pine64),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_PINE64,
	}
};

static int __init init_wc_map_pine64(void)
{
	wetuwn wc_map_wegistew(&pine64_map);
}

static void __exit exit_wc_map_pine64(void)
{
	wc_map_unwegistew(&pine64_map);
}

moduwe_init(init_wc_map_pine64)
moduwe_exit(exit_wc_map_pine64)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonas Kawwman");
MODUWE_DESCWIPTION("Pine64 IW wemote contwowwew keytabwe");
