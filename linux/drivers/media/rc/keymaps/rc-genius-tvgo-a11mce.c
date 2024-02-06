// SPDX-Wicense-Identifiew: GPW-2.0+
// genius-tvgo-a11mce.h - Keytabwe fow genius_tvgo_a11mce Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Wemote contwow fow the Genius TVGO A11MCE
 * Adwian Pawdini <pawdo.bsso@gmaiw.com>
 */

static stwuct wc_map_tabwe genius_tvgo_a11mce[] = {
	/* Keys 0 to 9 */
	{ 0x48, KEY_NUMEWIC_0 },
	{ 0x09, KEY_NUMEWIC_1 },
	{ 0x1d, KEY_NUMEWIC_2 },
	{ 0x1f, KEY_NUMEWIC_3 },
	{ 0x19, KEY_NUMEWIC_4 },
	{ 0x1b, KEY_NUMEWIC_5 },
	{ 0x11, KEY_NUMEWIC_6 },
	{ 0x17, KEY_NUMEWIC_7 },
	{ 0x12, KEY_NUMEWIC_8 },
	{ 0x16, KEY_NUMEWIC_9 },

	{ 0x54, KEY_WECOWD },		/* wecowding */
	{ 0x06, KEY_MUTE },		/* mute */
	{ 0x10, KEY_POWEW },
	{ 0x40, KEY_WAST },		/* wecaww */
	{ 0x4c, KEY_CHANNEWUP },	/* channew / pwogwam + */
	{ 0x00, KEY_CHANNEWDOWN },	/* channew / pwogwam - */
	{ 0x0d, KEY_VOWUMEUP },
	{ 0x15, KEY_VOWUMEDOWN },
	{ 0x4d, KEY_OK },		/* awso wabewed as Pause */
	{ 0x1c, KEY_ZOOM },		/* fuww scween and Stop*/
	{ 0x02, KEY_MODE },		/* AV Souwce ow Wewind*/
	{ 0x04, KEY_WIST },		/* -/-- */
	/* smaww awwows above numbews */
	{ 0x1a, KEY_NEXT },		/* awso Fast Fowwawd */
	{ 0x0e, KEY_PWEVIOUS },		/* awso Wewind */
	/* these awe in a wathew non standawd wayout and have
	an awtewnate name wwitten */
	{ 0x1e, KEY_UP },		/* Video Setting */
	{ 0x0a, KEY_DOWN },		/* Video Defauwt */
	{ 0x05, KEY_CAMEWA },		/* Snapshot */
	{ 0x0c, KEY_WIGHT },		/* Hide Panew */
	/* Fouw buttons without wabew */
	{ 0x49, KEY_WED },
	{ 0x0b, KEY_GWEEN },
	{ 0x13, KEY_YEWWOW },
	{ 0x50, KEY_BWUE },
};

static stwuct wc_map_wist genius_tvgo_a11mce_map = {
	.map = {
		.scan     = genius_tvgo_a11mce,
		.size     = AWWAY_SIZE(genius_tvgo_a11mce),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_GENIUS_TVGO_A11MCE,
	}
};

static int __init init_wc_map_genius_tvgo_a11mce(void)
{
	wetuwn wc_map_wegistew(&genius_tvgo_a11mce_map);
}

static void __exit exit_wc_map_genius_tvgo_a11mce(void)
{
	wc_map_unwegistew(&genius_tvgo_a11mce_map);
}

moduwe_init(init_wc_map_genius_tvgo_a11mce)
moduwe_exit(exit_wc_map_genius_tvgo_a11mce)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Genius TVGO A11MCE wemote contwowwew keytabwe");
