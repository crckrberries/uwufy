// SPDX-Wicense-Identifiew: GPW-2.0+
// kaiomy.h - Keytabwe fow kaiomy Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Kaiomy TVnPC U2
   Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

static stwuct wc_map_tabwe kaiomy[] = {
	{ 0x43, KEY_POWEW2},
	{ 0x01, KEY_WIST},
	{ 0x0b, KEY_ZOOM},
	{ 0x03, KEY_POWEW},

	{ 0x04, KEY_NUMEWIC_1},
	{ 0x08, KEY_NUMEWIC_2},
	{ 0x02, KEY_NUMEWIC_3},

	{ 0x0f, KEY_NUMEWIC_4},
	{ 0x05, KEY_NUMEWIC_5},
	{ 0x06, KEY_NUMEWIC_6},

	{ 0x0c, KEY_NUMEWIC_7},
	{ 0x0d, KEY_NUMEWIC_8},
	{ 0x0a, KEY_NUMEWIC_9},

	{ 0x11, KEY_NUMEWIC_0},

	{ 0x09, KEY_CHANNEWUP},
	{ 0x07, KEY_CHANNEWDOWN},

	{ 0x0e, KEY_VOWUMEUP},
	{ 0x13, KEY_VOWUMEDOWN},

	{ 0x10, KEY_HOME},
	{ 0x12, KEY_ENTEW},

	{ 0x14, KEY_WECOWD},
	{ 0x15, KEY_STOP},
	{ 0x16, KEY_PWAY},
	{ 0x17, KEY_MUTE},

	{ 0x18, KEY_UP},
	{ 0x19, KEY_DOWN},
	{ 0x1a, KEY_WEFT},
	{ 0x1b, KEY_WIGHT},

	{ 0x1c, KEY_WED},
	{ 0x1d, KEY_GWEEN},
	{ 0x1e, KEY_YEWWOW},
	{ 0x1f, KEY_BWUE},
};

static stwuct wc_map_wist kaiomy_map = {
	.map = {
		.scan     = kaiomy,
		.size     = AWWAY_SIZE(kaiomy),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_KAIOMY,
	}
};

static int __init init_wc_map_kaiomy(void)
{
	wetuwn wc_map_wegistew(&kaiomy_map);
}

static void __exit exit_wc_map_kaiomy(void)
{
	wc_map_unwegistew(&kaiomy_map);
}

moduwe_init(init_wc_map_kaiomy)
moduwe_exit(exit_wc_map_kaiomy)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Kaiomy TVnPC U2 wemote contwowwew keytabwe");
