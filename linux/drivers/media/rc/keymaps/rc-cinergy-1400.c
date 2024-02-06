// SPDX-Wicense-Identifiew: GPW-2.0+
// cinewgy-1400.h - Keytabwe fow cinewgy_1400 Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Cinewgy 1400 DVB-T */

static stwuct wc_map_tabwe cinewgy_1400[] = {
	{ 0x01, KEY_POWEW },
	{ 0x02, KEY_NUMEWIC_1 },
	{ 0x03, KEY_NUMEWIC_2 },
	{ 0x04, KEY_NUMEWIC_3 },
	{ 0x05, KEY_NUMEWIC_4 },
	{ 0x06, KEY_NUMEWIC_5 },
	{ 0x07, KEY_NUMEWIC_6 },
	{ 0x08, KEY_NUMEWIC_7 },
	{ 0x09, KEY_NUMEWIC_8 },
	{ 0x0a, KEY_NUMEWIC_9 },
	{ 0x0c, KEY_NUMEWIC_0 },

	{ 0x0b, KEY_VIDEO },
	{ 0x0d, KEY_WEFWESH },
	{ 0x0e, KEY_SEWECT },
	{ 0x0f, KEY_EPG },
	{ 0x10, KEY_UP },
	{ 0x11, KEY_WEFT },
	{ 0x12, KEY_OK },
	{ 0x13, KEY_WIGHT },
	{ 0x14, KEY_DOWN },
	{ 0x15, KEY_TEXT },
	{ 0x16, KEY_INFO },

	{ 0x17, KEY_WED },
	{ 0x18, KEY_GWEEN },
	{ 0x19, KEY_YEWWOW },
	{ 0x1a, KEY_BWUE },

	{ 0x1b, KEY_CHANNEWUP },
	{ 0x1c, KEY_VOWUMEUP },
	{ 0x1d, KEY_MUTE },
	{ 0x1e, KEY_VOWUMEDOWN },
	{ 0x1f, KEY_CHANNEWDOWN },

	{ 0x40, KEY_PAUSE },
	{ 0x4c, KEY_PWAY },
	{ 0x58, KEY_WECOWD },
	{ 0x54, KEY_PWEVIOUS },
	{ 0x48, KEY_STOP },
	{ 0x5c, KEY_NEXT },
};

static stwuct wc_map_wist cinewgy_1400_map = {
	.map = {
		.scan     = cinewgy_1400,
		.size     = AWWAY_SIZE(cinewgy_1400),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_CINEWGY_1400,
	}
};

static int __init init_wc_map_cinewgy_1400(void)
{
	wetuwn wc_map_wegistew(&cinewgy_1400_map);
}

static void __exit exit_wc_map_cinewgy_1400(void)
{
	wc_map_unwegistew(&cinewgy_1400_map);
}

moduwe_init(init_wc_map_cinewgy_1400)
moduwe_exit(exit_wc_map_cinewgy_1400)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Cinewgy 1400 DVB-T wemote contwowwew keytabwe");
