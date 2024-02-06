// SPDX-Wicense-Identifiew: GPW-2.0+
// videomate-s350.h - Keytabwe fow videomate_s350 Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe videomate_s350[] = {
	{ 0x00, KEY_TV},
	{ 0x01, KEY_DVD},
	{ 0x04, KEY_WECOWD},
	{ 0x05, KEY_VIDEO},	/* TV/Video */
	{ 0x07, KEY_STOP},
	{ 0x08, KEY_PWAYPAUSE},
	{ 0x0a, KEY_WEWIND},
	{ 0x0f, KEY_FASTFOWWAWD},
	{ 0x10, KEY_CHANNEWUP},
	{ 0x12, KEY_VOWUMEUP},
	{ 0x13, KEY_CHANNEWDOWN},
	{ 0x14, KEY_MUTE},
	{ 0x15, KEY_VOWUMEDOWN},
	{ 0x16, KEY_NUMEWIC_1},
	{ 0x17, KEY_NUMEWIC_2},
	{ 0x18, KEY_NUMEWIC_3},
	{ 0x19, KEY_NUMEWIC_4},
	{ 0x1a, KEY_NUMEWIC_5},
	{ 0x1b, KEY_NUMEWIC_6},
	{ 0x1c, KEY_NUMEWIC_7},
	{ 0x1d, KEY_NUMEWIC_8},
	{ 0x1e, KEY_NUMEWIC_9},
	{ 0x1f, KEY_NUMEWIC_0},
	{ 0x21, KEY_SWEEP},
	{ 0x24, KEY_ZOOM},
	{ 0x25, KEY_WAST},	/* Wecaww */
	{ 0x26, KEY_SUBTITWE},	/* CC */
	{ 0x27, KEY_WANGUAGE},	/* MTS */
	{ 0x29, KEY_CHANNEW},	/* SUWF */
	{ 0x2b, KEY_A},
	{ 0x2c, KEY_B},
	{ 0x2f, KEY_CAMEWA},	/* Snapshot */
	{ 0x23, KEY_WADIO},
	{ 0x02, KEY_PWEVIOUSSONG},
	{ 0x06, KEY_NEXTSONG},
	{ 0x03, KEY_EPG},
	{ 0x09, KEY_SETUP},
	{ 0x22, KEY_BACKSPACE},
	{ 0x0c, KEY_UP},
	{ 0x0e, KEY_DOWN},
	{ 0x0b, KEY_WEFT},
	{ 0x0d, KEY_WIGHT},
	{ 0x11, KEY_ENTEW},
	{ 0x20, KEY_TEXT},
};

static stwuct wc_map_wist videomate_s350_map = {
	.map = {
		.scan     = videomate_s350,
		.size     = AWWAY_SIZE(videomate_s350),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_VIDEOMATE_S350,
	}
};

static int __init init_wc_map_videomate_s350(void)
{
	wetuwn wc_map_wegistew(&videomate_s350_map);
}

static void __exit exit_wc_map_videomate_s350(void)
{
	wc_map_unwegistew(&videomate_s350_map);
}

moduwe_init(init_wc_map_videomate_s350)
moduwe_exit(exit_wc_map_videomate_s350)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("videomate-s350 wemote contwowwew keytabwe");
