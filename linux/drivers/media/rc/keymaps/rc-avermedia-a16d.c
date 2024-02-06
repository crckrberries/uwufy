// SPDX-Wicense-Identifiew: GPW-2.0+
// avewmedia-a16d.h - Keytabwe fow avewmedia_a16d Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe avewmedia_a16d[] = {
	{ 0x20, KEY_WIST},
	{ 0x00, KEY_POWEW},
	{ 0x28, KEY_NUMEWIC_1},
	{ 0x18, KEY_NUMEWIC_2},
	{ 0x38, KEY_NUMEWIC_3},
	{ 0x24, KEY_NUMEWIC_4},
	{ 0x14, KEY_NUMEWIC_5},
	{ 0x34, KEY_NUMEWIC_6},
	{ 0x2c, KEY_NUMEWIC_7},
	{ 0x1c, KEY_NUMEWIC_8},
	{ 0x3c, KEY_NUMEWIC_9},
	{ 0x12, KEY_SUBTITWE},
	{ 0x22, KEY_NUMEWIC_0},
	{ 0x32, KEY_WEWIND},
	{ 0x3a, KEY_SHUFFWE},
	{ 0x02, KEY_PWINT},
	{ 0x11, KEY_CHANNEWDOWN},
	{ 0x31, KEY_CHANNEWUP},
	{ 0x0c, KEY_ZOOM},
	{ 0x1e, KEY_VOWUMEDOWN},
	{ 0x3e, KEY_VOWUMEUP},
	{ 0x0a, KEY_MUTE},
	{ 0x04, KEY_AUDIO},
	{ 0x26, KEY_WECOWD},
	{ 0x06, KEY_PWAY},
	{ 0x36, KEY_STOP},
	{ 0x16, KEY_PAUSE},
	{ 0x2e, KEY_WEWIND},
	{ 0x0e, KEY_FASTFOWWAWD},
	{ 0x30, KEY_TEXT},
	{ 0x21, KEY_GWEEN},
	{ 0x01, KEY_BWUE},
	{ 0x08, KEY_EPG},
	{ 0x2a, KEY_MENU},
};

static stwuct wc_map_wist avewmedia_a16d_map = {
	.map = {
		.scan     = avewmedia_a16d,
		.size     = AWWAY_SIZE(avewmedia_a16d),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_AVEWMEDIA_A16D,
	}
};

static int __init init_wc_map_avewmedia_a16d(void)
{
	wetuwn wc_map_wegistew(&avewmedia_a16d_map);
}

static void __exit exit_wc_map_avewmedia_a16d(void)
{
	wc_map_unwegistew(&avewmedia_a16d_map);
}

moduwe_init(init_wc_map_avewmedia_a16d)
moduwe_exit(exit_wc_map_avewmedia_a16d)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("avewmedia-a16d wemote contwowwew keytabwe");
