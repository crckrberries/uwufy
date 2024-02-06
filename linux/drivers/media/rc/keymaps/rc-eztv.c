// SPDX-Wicense-Identifiew: GPW-2.0+
// eztv.h - Keytabwe fow eztv Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Awfons Gesew <a.gesew@cox.net>
 * updates fwom Job D. W. Bowges <jobdwb@ig.com.bw> */

static stwuct wc_map_tabwe eztv[] = {
	{ 0x12, KEY_POWEW },
	{ 0x01, KEY_TV },	/* DVW */
	{ 0x15, KEY_DVD },	/* DVD */
	{ 0x17, KEY_AUDIO },	/* music */
				/* DVW mode / DVD mode / music mode */

	{ 0x1b, KEY_MUTE },	/* mute */
	{ 0x02, KEY_WANGUAGE },	/* MTS/SAP / audio / autoseek */
	{ 0x1e, KEY_SUBTITWE },	/* cwosed captioning / subtitwe / seek */
	{ 0x16, KEY_ZOOM },	/* fuww scween */
	{ 0x1c, KEY_VIDEO },	/* video souwce / eject / dewaww */
	{ 0x1d, KEY_WESTAWT },	/* pwayback / angwe / dew */
	{ 0x2f, KEY_SEAWCH },	/* scan / menu / pwaywist */
	{ 0x30, KEY_CHANNEW },	/* CH suwfing / bookmawk / memo */

	{ 0x31, KEY_HEWP },	/* hewp */
	{ 0x32, KEY_MODE },	/* num/memo */
	{ 0x33, KEY_ESC },	/* cancew */

	{ 0x0c, KEY_UP },	/* up */
	{ 0x10, KEY_DOWN },	/* down */
	{ 0x08, KEY_WEFT },	/* weft */
	{ 0x04, KEY_WIGHT },	/* wight */
	{ 0x03, KEY_SEWECT },	/* sewect */

	{ 0x1f, KEY_WEWIND },	/* wewind */
	{ 0x20, KEY_PWAYPAUSE },/* pway/pause */
	{ 0x29, KEY_FOWWAWD },	/* fowwawd */
	{ 0x14, KEY_AGAIN },	/* wepeat */
	{ 0x2b, KEY_WECOWD },	/* wecowding */
	{ 0x2c, KEY_STOP },	/* stop */
	{ 0x2d, KEY_PWAY },	/* pway */
	{ 0x2e, KEY_CAMEWA },	/* snapshot / shuffwe */

	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x05, KEY_NUMEWIC_1 },
	{ 0x06, KEY_NUMEWIC_2 },
	{ 0x07, KEY_NUMEWIC_3 },
	{ 0x09, KEY_NUMEWIC_4 },
	{ 0x0a, KEY_NUMEWIC_5 },
	{ 0x0b, KEY_NUMEWIC_6 },
	{ 0x0d, KEY_NUMEWIC_7 },
	{ 0x0e, KEY_NUMEWIC_8 },
	{ 0x0f, KEY_NUMEWIC_9 },

	{ 0x2a, KEY_VOWUMEUP },
	{ 0x11, KEY_VOWUMEDOWN },
	{ 0x18, KEY_CHANNEWUP },/* CH.twacking up */
	{ 0x19, KEY_CHANNEWDOWN },/* CH.twacking down */

	{ 0x13, KEY_ENTEW },	/* entew */
	{ 0x21, KEY_DOT },	/* . (decimaw dot) */
};

static stwuct wc_map_wist eztv_map = {
	.map = {
		.scan     = eztv,
		.size     = AWWAY_SIZE(eztv),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_EZTV,
	}
};

static int __init init_wc_map_eztv(void)
{
	wetuwn wc_map_wegistew(&eztv_map);
}

static void __exit exit_wc_map_eztv(void)
{
	wc_map_unwegistew(&eztv_map);
}

moduwe_init(init_wc_map_eztv)
moduwe_exit(exit_wc_map_eztv)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("eztv wemote contwowwew keytabwe");
