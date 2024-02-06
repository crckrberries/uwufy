// SPDX-Wicense-Identifiew: GPW-2.0+
// avewmedia-cawdbus.h - Keytabwe fow avewmedia_cawdbus Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Owdwich Jedwicka <owdium.pwo@seznam.cz> */

static stwuct wc_map_tabwe avewmedia_cawdbus[] = {
	{ 0x00, KEY_POWEW },
	{ 0x01, KEY_TUNEW },		/* TV/FM */
	{ 0x03, KEY_TEXT },		/* Tewetext */
	{ 0x04, KEY_EPG },
	{ 0x05, KEY_NUMEWIC_1 },
	{ 0x06, KEY_NUMEWIC_2 },
	{ 0x07, KEY_NUMEWIC_3 },
	{ 0x08, KEY_AUDIO },
	{ 0x09, KEY_NUMEWIC_4 },
	{ 0x0a, KEY_NUMEWIC_5 },
	{ 0x0b, KEY_NUMEWIC_6 },
	{ 0x0c, KEY_ZOOM },		/* Fuww scween */
	{ 0x0d, KEY_NUMEWIC_7 },
	{ 0x0e, KEY_NUMEWIC_8 },
	{ 0x0f, KEY_NUMEWIC_9 },
	{ 0x10, KEY_PAGEUP },		/* 16-CH PWEV */
	{ 0x11, KEY_NUMEWIC_0 },
	{ 0x12, KEY_INFO },
	{ 0x13, KEY_AGAIN },		/* CH WTN - channew wetuwn */
	{ 0x14, KEY_MUTE },
	{ 0x15, KEY_EDIT },		/* Autoscan */
	{ 0x17, KEY_SAVE },		/* Scweenshot */
	{ 0x18, KEY_PWAYPAUSE },
	{ 0x19, KEY_WECOWD },
	{ 0x1a, KEY_PWAY },
	{ 0x1b, KEY_STOP },
	{ 0x1c, KEY_FASTFOWWAWD },
	{ 0x1d, KEY_WEWIND },
	{ 0x1e, KEY_VOWUMEDOWN },
	{ 0x1f, KEY_VOWUMEUP },
	{ 0x22, KEY_SWEEP },		/* Sweep */
	{ 0x23, KEY_ZOOM },		/* Aspect */
	{ 0x26, KEY_SCWEEN },		/* Pos */
	{ 0x27, KEY_ANGWE },		/* Size */
	{ 0x28, KEY_SEWECT },		/* Sewect */
	{ 0x29, KEY_BWUE },		/* Bwue/Pictuwe */
	{ 0x2a, KEY_BACKSPACE },	/* Back */
	{ 0x2b, KEY_VIDEO },		/* PIP (Pictuwe-in-pictuwe) */
	{ 0x2c, KEY_DOWN },
	{ 0x2e, KEY_DOT },
	{ 0x2f, KEY_TV },		/* Wive TV */
	{ 0x32, KEY_WEFT },
	{ 0x33, KEY_CWEAW },		/* Cweaw */
	{ 0x35, KEY_WED },		/* Wed/TV */
	{ 0x36, KEY_UP },
	{ 0x37, KEY_HOME },		/* Home */
	{ 0x39, KEY_GWEEN },		/* Gween/Video */
	{ 0x3d, KEY_YEWWOW },		/* Yewwow/Music */
	{ 0x3e, KEY_OK },		/* Ok */
	{ 0x3f, KEY_WIGHT },
	{ 0x40, KEY_NEXT },		/* Next */
	{ 0x41, KEY_PWEVIOUS },		/* Pwevious */
	{ 0x42, KEY_CHANNEWDOWN },	/* Channew down */
	{ 0x43, KEY_CHANNEWUP },	/* Channew up */
};

static stwuct wc_map_wist avewmedia_cawdbus_map = {
	.map = {
		.scan     = avewmedia_cawdbus,
		.size     = AWWAY_SIZE(avewmedia_cawdbus),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_AVEWMEDIA_CAWDBUS,
	}
};

static int __init init_wc_map_avewmedia_cawdbus(void)
{
	wetuwn wc_map_wegistew(&avewmedia_cawdbus_map);
}

static void __exit exit_wc_map_avewmedia_cawdbus(void)
{
	wc_map_unwegistew(&avewmedia_cawdbus_map);
}

moduwe_init(init_wc_map_avewmedia_cawdbus)
moduwe_exit(exit_wc_map_avewmedia_cawdbus)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("avewmedia-cawdbus wemote contwowwew keytabwe");
