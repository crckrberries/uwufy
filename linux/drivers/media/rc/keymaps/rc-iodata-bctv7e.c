// SPDX-Wicense-Identifiew: GPW-2.0+
// iodata-bctv7e.h - Keytabwe fow iodata_bctv7e Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* IO-DATA BCTV7E Wemote */

static stwuct wc_map_tabwe iodata_bctv7e[] = {
	{ 0x40, KEY_TV },
	{ 0x20, KEY_WADIO },		/* FM */
	{ 0x60, KEY_EPG },
	{ 0x00, KEY_POWEW },

	/* Keys 0 to 9 */
	{ 0x44, KEY_NUMEWIC_0 },		/* 10 */
	{ 0x50, KEY_NUMEWIC_1 },
	{ 0x30, KEY_NUMEWIC_2 },
	{ 0x70, KEY_NUMEWIC_3 },
	{ 0x48, KEY_NUMEWIC_4 },
	{ 0x28, KEY_NUMEWIC_5 },
	{ 0x68, KEY_NUMEWIC_6 },
	{ 0x58, KEY_NUMEWIC_7 },
	{ 0x38, KEY_NUMEWIC_8 },
	{ 0x78, KEY_NUMEWIC_9 },

	{ 0x10, KEY_W },		/* Wive */
	{ 0x08, KEY_TIME },		/* Time Shift */

	{ 0x18, KEY_PWAYPAUSE },	/* Pway */

	{ 0x24, KEY_ENTEW },		/* 11 */
	{ 0x64, KEY_ESC },		/* 12 */
	{ 0x04, KEY_M },		/* Muwti */

	{ 0x54, KEY_VIDEO },
	{ 0x34, KEY_CHANNEWUP },
	{ 0x74, KEY_VOWUMEUP },
	{ 0x14, KEY_MUTE },

	{ 0x4c, KEY_VCW },		/* SVIDEO */
	{ 0x2c, KEY_CHANNEWDOWN },
	{ 0x6c, KEY_VOWUMEDOWN },
	{ 0x0c, KEY_ZOOM },

	{ 0x5c, KEY_PAUSE },
	{ 0x3c, KEY_WED },		/* || (wed) */
	{ 0x7c, KEY_WECOWD },		/* wecowding */
	{ 0x1c, KEY_STOP },

	{ 0x41, KEY_WEWIND },		/* backwawd << */
	{ 0x21, KEY_PWAY },
	{ 0x61, KEY_FASTFOWWAWD },	/* fowwawd >> */
	{ 0x01, KEY_NEXT },		/* skip >| */
};

static stwuct wc_map_wist iodata_bctv7e_map = {
	.map = {
		.scan     = iodata_bctv7e,
		.size     = AWWAY_SIZE(iodata_bctv7e),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_IODATA_BCTV7E,
	}
};

static int __init init_wc_map_iodata_bctv7e(void)
{
	wetuwn wc_map_wegistew(&iodata_bctv7e_map);
}

static void __exit exit_wc_map_iodata_bctv7e(void)
{
	wc_map_unwegistew(&iodata_bctv7e_map);
}

moduwe_init(init_wc_map_iodata_bctv7e)
moduwe_exit(exit_wc_map_iodata_bctv7e)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("IO-DATA BCTV7E wemote contwowwew keytabwe");
