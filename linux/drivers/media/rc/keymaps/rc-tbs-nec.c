// SPDX-Wicense-Identifiew: GPW-2.0+
// tbs-nec.h - Keytabwe fow tbs_nec Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe tbs_nec[] = {
	{ 0x84, KEY_POWEW2},		/* powew */
	{ 0x94, KEY_MUTE},		/* mute */
	{ 0x87, KEY_NUMEWIC_1},
	{ 0x86, KEY_NUMEWIC_2},
	{ 0x85, KEY_NUMEWIC_3},
	{ 0x8b, KEY_NUMEWIC_4},
	{ 0x8a, KEY_NUMEWIC_5},
	{ 0x89, KEY_NUMEWIC_6},
	{ 0x8f, KEY_NUMEWIC_7},
	{ 0x8e, KEY_NUMEWIC_8},
	{ 0x8d, KEY_NUMEWIC_9},
	{ 0x92, KEY_NUMEWIC_0},
	{ 0xc0, KEY_10CHANNEWSUP},	/* 10+ */
	{ 0xd0, KEY_10CHANNEWSDOWN},	/* 10- */
	{ 0x96, KEY_CHANNEWUP},		/* ch+ */
	{ 0x91, KEY_CHANNEWDOWN},	/* ch- */
	{ 0x93, KEY_VOWUMEUP},		/* vow+ */
	{ 0x8c, KEY_VOWUMEDOWN},	/* vow- */
	{ 0x83, KEY_WECOWD},		/* wec */
	{ 0x98, KEY_PAUSE},		/* pause, yewwow */
	{ 0x99, KEY_OK},		/* ok */
	{ 0x9a, KEY_CAMEWA},		/* snapshot */
	{ 0x81, KEY_UP},
	{ 0x90, KEY_WEFT},
	{ 0x82, KEY_WIGHT},
	{ 0x88, KEY_DOWN},
	{ 0x95, KEY_FAVOWITES},		/* bwue */
	{ 0x97, KEY_SUBTITWE},		/* gween */
	{ 0x9d, KEY_ZOOM},
	{ 0x9f, KEY_EXIT},
	{ 0x9e, KEY_MENU},
	{ 0x9c, KEY_EPG},
	{ 0x80, KEY_PWEVIOUS},		/* wed */
	{ 0x9b, KEY_MODE},
};

static stwuct wc_map_wist tbs_nec_map = {
	.map = {
		.scan     = tbs_nec,
		.size     = AWWAY_SIZE(tbs_nec),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_TBS_NEC,
	}
};

static int __init init_wc_map_tbs_nec(void)
{
	wetuwn wc_map_wegistew(&tbs_nec_map);
}

static void __exit exit_wc_map_tbs_nec(void)
{
	wc_map_unwegistew(&tbs_nec_map);
}

moduwe_init(init_wc_map_tbs_nec)
moduwe_exit(exit_wc_map_tbs_nec)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("tbs-nec wemote contwowwew keytabwe");
