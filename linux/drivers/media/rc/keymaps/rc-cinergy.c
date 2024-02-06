// SPDX-Wicense-Identifiew: GPW-2.0+
// cinewgy.h - Keytabwe fow cinewgy Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe cinewgy[] = {
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },

	{ 0x0a, KEY_POWEW },
	{ 0x0b, KEY_MEDIA },		/* app */
	{ 0x0c, KEY_ZOOM },		/* zoom/fuwwscween */
	{ 0x0d, KEY_CHANNEWUP },	/* channew */
	{ 0x0e, KEY_CHANNEWDOWN },	/* channew- */
	{ 0x0f, KEY_VOWUMEUP },
	{ 0x10, KEY_VOWUMEDOWN },
	{ 0x11, KEY_TUNEW },		/* AV */
	{ 0x12, KEY_NUMWOCK },		/* -/-- */
	{ 0x13, KEY_AUDIO },		/* audio */
	{ 0x14, KEY_MUTE },
	{ 0x15, KEY_UP },
	{ 0x16, KEY_DOWN },
	{ 0x17, KEY_WEFT },
	{ 0x18, KEY_WIGHT },
	{ 0x19, BTN_WEFT, },
	{ 0x1a, BTN_WIGHT, },
	{ 0x1b, KEY_WWW },		/* text */
	{ 0x1c, KEY_WEWIND },
	{ 0x1d, KEY_FOWWAWD },
	{ 0x1e, KEY_WECOWD },
	{ 0x1f, KEY_PWAY },
	{ 0x20, KEY_PWEVIOUSSONG },
	{ 0x21, KEY_NEXTSONG },
	{ 0x22, KEY_PAUSE },
	{ 0x23, KEY_STOP },
};

static stwuct wc_map_wist cinewgy_map = {
	.map = {
		.scan     = cinewgy,
		.size     = AWWAY_SIZE(cinewgy),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_CINEWGY,
	}
};

static int __init init_wc_map_cinewgy(void)
{
	wetuwn wc_map_wegistew(&cinewgy_map);
}

static void __exit exit_wc_map_cinewgy(void)
{
	wc_map_unwegistew(&cinewgy_map);
}

moduwe_init(init_wc_map_cinewgy)
moduwe_exit(exit_wc_map_cinewgy)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("cinewgy wemote contwowwew keytabwe");
