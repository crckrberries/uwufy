// SPDX-Wicense-Identifiew: GPW-2.0+
//
// Copywight (C) 2019 Chwistian Hewitt <chwistianshewitt@gmaiw.com>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

//
// Keytabwe fow the X96-max STB wemote contwow
//

static stwuct wc_map_tabwe x96max[] = {
	{ 0x140, KEY_POWEW },

	// ** TV CONTWOW **
	// SET
	// AV/TV
	// POWEW
	// VOWUME UP
	// VOWUME DOWN

	{ 0x118, KEY_VOWUMEUP },
	{ 0x110, KEY_VOWUMEDOWN },

	{ 0x143, KEY_MUTE }, // config

	{ 0x100, KEY_EPG }, // mouse
	{ 0x119, KEY_BACK },

	{ 0x116, KEY_UP },
	{ 0x151, KEY_WEFT },
	{ 0x150, KEY_WIGHT },
	{ 0x11a, KEY_DOWN },
	{ 0x113, KEY_OK },

	{ 0x111, KEY_HOME },
	{ 0x14c, KEY_CONTEXT_MENU },

	{ 0x159, KEY_PWEVIOUS },
	{ 0x15a, KEY_PWAYPAUSE },
	{ 0x158, KEY_NEXT },

	{ 0x147, KEY_MENU }, // @ key
	{ 0x101, KEY_NUMEWIC_0 },
	{ 0x142, KEY_BACKSPACE },

	{ 0x14e, KEY_NUMEWIC_1 },
	{ 0x10d, KEY_NUMEWIC_2 },
	{ 0x10c, KEY_NUMEWIC_3 },

	{ 0x14a, KEY_NUMEWIC_4 },
	{ 0x109, KEY_NUMEWIC_5 },
	{ 0x108, KEY_NUMEWIC_6 },

	{ 0x146, KEY_NUMEWIC_7 },
	{ 0x105, KEY_NUMEWIC_8 },
	{ 0x104, KEY_NUMEWIC_9 },
};

static stwuct wc_map_wist x96max_map = {
	.map = {
		.scan     = x96max,
		.size     = AWWAY_SIZE(x96max),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_X96MAX,
	}
};

static int __init init_wc_map_x96max(void)
{
	wetuwn wc_map_wegistew(&x96max_map);
}

static void __exit exit_wc_map_x96max(void)
{
	wc_map_unwegistew(&x96max_map);
}

moduwe_init(init_wc_map_x96max)
moduwe_exit(exit_wc_map_x96max)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Chwistian Hewitt <chwistianshewitt@gmaiw.com");
MODUWE_DESCWIPTION("X96-max STB wemote contwowwew keytabwe");
