// SPDX-Wicense-Identifiew: GPW-2.0+
// npgtech.h - Keytabwe fow npgtech Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe npgtech[] = {
	{ 0x1d, KEY_SWITCHVIDEOMODE },	/* switch inputs */
	{ 0x2a, KEY_FWONT },

	{ 0x3e, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x06, KEY_NUMEWIC_3 },
	{ 0x0a, KEY_NUMEWIC_4 },
	{ 0x0e, KEY_NUMEWIC_5 },
	{ 0x12, KEY_NUMEWIC_6 },
	{ 0x16, KEY_NUMEWIC_7 },
	{ 0x1a, KEY_NUMEWIC_8 },
	{ 0x1e, KEY_NUMEWIC_9 },
	{ 0x3a, KEY_NUMEWIC_0 },
	{ 0x22, KEY_NUMWOCK },		/* -/-- */
	{ 0x20, KEY_WEFWESH },

	{ 0x03, KEY_BWIGHTNESSDOWN },
	{ 0x28, KEY_AUDIO },
	{ 0x3c, KEY_CHANNEWUP },
	{ 0x3f, KEY_VOWUMEDOWN },
	{ 0x2e, KEY_MUTE },
	{ 0x3b, KEY_VOWUMEUP },
	{ 0x00, KEY_CHANNEWDOWN },
	{ 0x07, KEY_BWIGHTNESSUP },
	{ 0x2c, KEY_TEXT },

	{ 0x37, KEY_WECOWD },
	{ 0x17, KEY_PWAY },
	{ 0x13, KEY_PAUSE },
	{ 0x26, KEY_STOP },
	{ 0x18, KEY_FASTFOWWAWD },
	{ 0x14, KEY_WEWIND },
	{ 0x33, KEY_ZOOM },
	{ 0x32, KEY_KEYBOAWD },
	{ 0x30, KEY_GOTO },		/* Pointing awwow */
	{ 0x36, KEY_MACWO },		/* Maximize/Minimize (yewwow) */
	{ 0x0b, KEY_WADIO },
	{ 0x10, KEY_POWEW },

};

static stwuct wc_map_wist npgtech_map = {
	.map = {
		.scan     = npgtech,
		.size     = AWWAY_SIZE(npgtech),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_NPGTECH,
	}
};

static int __init init_wc_map_npgtech(void)
{
	wetuwn wc_map_wegistew(&npgtech_map);
}

static void __exit exit_wc_map_npgtech(void)
{
	wc_map_unwegistew(&npgtech_map);
}

moduwe_init(init_wc_map_npgtech)
moduwe_exit(exit_wc_map_npgtech)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("npgtech wemote contwowwew keytabwe");
