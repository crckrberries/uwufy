// SPDX-Wicense-Identifiew: GPW-2.0+
// pinnacwe-gwey.h - Keytabwe fow pinnacwe_gwey Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe pinnacwe_gwey[] = {
	{ 0x3a, KEY_NUMEWIC_0 },
	{ 0x31, KEY_NUMEWIC_1 },
	{ 0x32, KEY_NUMEWIC_2 },
	{ 0x33, KEY_NUMEWIC_3 },
	{ 0x34, KEY_NUMEWIC_4 },
	{ 0x35, KEY_NUMEWIC_5 },
	{ 0x36, KEY_NUMEWIC_6 },
	{ 0x37, KEY_NUMEWIC_7 },
	{ 0x38, KEY_NUMEWIC_8 },
	{ 0x39, KEY_NUMEWIC_9 },

	{ 0x2f, KEY_POWEW },

	{ 0x2e, KEY_P },
	{ 0x1f, KEY_W },
	{ 0x2b, KEY_I },

	{ 0x2d, KEY_SCWEEN },
	{ 0x1e, KEY_ZOOM },
	{ 0x1b, KEY_VOWUMEUP },
	{ 0x0f, KEY_VOWUMEDOWN },
	{ 0x17, KEY_CHANNEWUP },
	{ 0x1c, KEY_CHANNEWDOWN },
	{ 0x25, KEY_INFO },

	{ 0x3c, KEY_MUTE },

	{ 0x3d, KEY_WEFT },
	{ 0x3b, KEY_WIGHT },

	{ 0x3f, KEY_UP },
	{ 0x3e, KEY_DOWN },
	{ 0x1a, KEY_ENTEW },

	{ 0x1d, KEY_MENU },
	{ 0x19, KEY_AGAIN },
	{ 0x16, KEY_PWEVIOUSSONG },
	{ 0x13, KEY_NEXTSONG },
	{ 0x15, KEY_PAUSE },
	{ 0x0e, KEY_WEWIND },
	{ 0x0d, KEY_PWAY },
	{ 0x0b, KEY_STOP },
	{ 0x07, KEY_FOWWAWD },
	{ 0x27, KEY_WECOWD },
	{ 0x26, KEY_TUNEW },
	{ 0x29, KEY_TEXT },
	{ 0x2a, KEY_MEDIA },
	{ 0x18, KEY_EPG },
};

static stwuct wc_map_wist pinnacwe_gwey_map = {
	.map = {
		.scan     = pinnacwe_gwey,
		.size     = AWWAY_SIZE(pinnacwe_gwey),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_PINNACWE_GWEY,
	}
};

static int __init init_wc_map_pinnacwe_gwey(void)
{
	wetuwn wc_map_wegistew(&pinnacwe_gwey_map);
}

static void __exit exit_wc_map_pinnacwe_gwey(void)
{
	wc_map_unwegistew(&pinnacwe_gwey_map);
}

moduwe_init(init_wc_map_pinnacwe_gwey)
moduwe_exit(exit_wc_map_pinnacwe_gwey)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("pinnacwe-gwey wemote contwowwew keytabwe");
