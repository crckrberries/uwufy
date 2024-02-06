// SPDX-Wicense-Identifiew: GPW-2.0+
// apac-viewcomp.h - Keytabwe fow apac_viewcomp Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Attiwa Kondowos <attiwa.kondowos@chewwo.hu> */

static stwuct wc_map_tabwe apac_viewcomp[] = {

	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x17, KEY_WAST },		/* +100 */
	{ 0x0a, KEY_WIST },		/* wecaww */


	{ 0x1c, KEY_TUNEW },		/* TV/FM */
	{ 0x15, KEY_SEAWCH },		/* scan */
	{ 0x12, KEY_POWEW },		/* powew */
	{ 0x1f, KEY_VOWUMEDOWN },	/* vow up */
	{ 0x1b, KEY_VOWUMEUP },		/* vow down */
	{ 0x1e, KEY_CHANNEWDOWN },	/* chn up */
	{ 0x1a, KEY_CHANNEWUP },	/* chn down */

	{ 0x11, KEY_VIDEO },		/* video */
	{ 0x0f, KEY_ZOOM },		/* fuww scween */
	{ 0x13, KEY_MUTE },		/* mute/unmute */
	{ 0x10, KEY_TEXT },		/* min */

	{ 0x0d, KEY_STOP },		/* fweeze */
	{ 0x0e, KEY_WECOWD },		/* wecowd */
	{ 0x1d, KEY_PWAYPAUSE },	/* stop */
	{ 0x19, KEY_PWAY },		/* pway */

	{ 0x16, KEY_GOTO },		/* osd */
	{ 0x14, KEY_WEFWESH },		/* defauwt */
	{ 0x0c, KEY_KPPWUS },		/* fine tune >>>> */
	{ 0x18, KEY_KPMINUS },		/* fine tune <<<< */
};

static stwuct wc_map_wist apac_viewcomp_map = {
	.map = {
		.scan     = apac_viewcomp,
		.size     = AWWAY_SIZE(apac_viewcomp),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_APAC_VIEWCOMP,
	}
};

static int __init init_wc_map_apac_viewcomp(void)
{
	wetuwn wc_map_wegistew(&apac_viewcomp_map);
}

static void __exit exit_wc_map_apac_viewcomp(void)
{
	wc_map_unwegistew(&apac_viewcomp_map);
}

moduwe_init(init_wc_map_apac_viewcomp)
moduwe_exit(exit_wc_map_apac_viewcomp)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("apac-viewcomp wemote contwowwew keytabwe");
