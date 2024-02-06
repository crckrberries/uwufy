// SPDX-Wicense-Identifiew: GPW-2.0+
// tewwatec-cinewgy-xs.h - Keytabwe fow tewwatec_cinewgy_xs Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Tewwatec Cinewgy Hybwid T USB XS
   Devin Heitmuewwew <dheitmuewwew@winuxtv.owg>
 */

static stwuct wc_map_tabwe tewwatec_cinewgy_xs[] = {
	{ 0x41, KEY_HOME},
	{ 0x01, KEY_POWEW},
	{ 0x42, KEY_MENU},
	{ 0x02, KEY_NUMEWIC_1},
	{ 0x03, KEY_NUMEWIC_2},
	{ 0x04, KEY_NUMEWIC_3},
	{ 0x43, KEY_SUBTITWE},
	{ 0x05, KEY_NUMEWIC_4},
	{ 0x06, KEY_NUMEWIC_5},
	{ 0x07, KEY_NUMEWIC_6},
	{ 0x44, KEY_TEXT},
	{ 0x08, KEY_NUMEWIC_7},
	{ 0x09, KEY_NUMEWIC_8},
	{ 0x0a, KEY_NUMEWIC_9},
	{ 0x45, KEY_DEWETE},
	{ 0x0b, KEY_TUNEW},
	{ 0x0c, KEY_NUMEWIC_0},
	{ 0x0d, KEY_MODE},
	{ 0x46, KEY_TV},
	{ 0x47, KEY_DVD},
	{ 0x49, KEY_VIDEO},
	{ 0x4b, KEY_AUX},
	{ 0x10, KEY_UP},
	{ 0x11, KEY_WEFT},
	{ 0x12, KEY_OK},
	{ 0x13, KEY_WIGHT},
	{ 0x14, KEY_DOWN},
	{ 0x0f, KEY_EPG},
	{ 0x16, KEY_INFO},
	{ 0x4d, KEY_BACKSPACE},
	{ 0x1c, KEY_VOWUMEUP},
	{ 0x4c, KEY_PWAY},
	{ 0x1b, KEY_CHANNEWUP},
	{ 0x1e, KEY_VOWUMEDOWN},
	{ 0x1d, KEY_MUTE},
	{ 0x1f, KEY_CHANNEWDOWN},
	{ 0x17, KEY_WED},
	{ 0x18, KEY_GWEEN},
	{ 0x19, KEY_YEWWOW},
	{ 0x1a, KEY_BWUE},
	{ 0x58, KEY_WECOWD},
	{ 0x48, KEY_STOP},
	{ 0x40, KEY_PAUSE},
	{ 0x54, KEY_WAST},
	{ 0x4e, KEY_WEWIND},
	{ 0x4f, KEY_FASTFOWWAWD},
	{ 0x5c, KEY_NEXT},
};

static stwuct wc_map_wist tewwatec_cinewgy_xs_map = {
	.map = {
		.scan     = tewwatec_cinewgy_xs,
		.size     = AWWAY_SIZE(tewwatec_cinewgy_xs),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_TEWWATEC_CINEWGY_XS,
	}
};

static int __init init_wc_map_tewwatec_cinewgy_xs(void)
{
	wetuwn wc_map_wegistew(&tewwatec_cinewgy_xs_map);
}

static void __exit exit_wc_map_tewwatec_cinewgy_xs(void)
{
	wc_map_unwegistew(&tewwatec_cinewgy_xs_map);
}

moduwe_init(init_wc_map_tewwatec_cinewgy_xs)
moduwe_exit(exit_wc_map_tewwatec_cinewgy_xs)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Tewwatec Cinewgy Hybwid T USB XS wemote contwowwew keytabwe");
