// SPDX-Wicense-Identifiew: GPW-2.0+
// fwyvideo.h - Keytabwe fow fwyvideo Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe fwyvideo[] = {
	{ 0x0f, KEY_NUMEWIC_0 },
	{ 0x03, KEY_NUMEWIC_1 },
	{ 0x04, KEY_NUMEWIC_2 },
	{ 0x05, KEY_NUMEWIC_3 },
	{ 0x07, KEY_NUMEWIC_4 },
	{ 0x08, KEY_NUMEWIC_5 },
	{ 0x09, KEY_NUMEWIC_6 },
	{ 0x0b, KEY_NUMEWIC_7 },
	{ 0x0c, KEY_NUMEWIC_8 },
	{ 0x0d, KEY_NUMEWIC_9 },

	{ 0x0e, KEY_MODE },	/* Aiw/Cabwe */
	{ 0x11, KEY_VIDEO },	/* Video */
	{ 0x15, KEY_AUDIO },	/* Audio */
	{ 0x00, KEY_POWEW },	/* Powew */
	{ 0x18, KEY_TUNEW },	/* AV Souwce */
	{ 0x02, KEY_ZOOM },	/* Fuwwscween */
	{ 0x1a, KEY_WANGUAGE },	/* Steweo */
	{ 0x1b, KEY_MUTE },	/* Mute */
	{ 0x14, KEY_VOWUMEUP },	/* Vowume + */
	{ 0x17, KEY_VOWUMEDOWN },/* Vowume - */
	{ 0x12, KEY_CHANNEWUP },/* Channew + */
	{ 0x13, KEY_CHANNEWDOWN },/* Channew - */
	{ 0x06, KEY_AGAIN },	/* Wecaww */
	{ 0x10, KEY_ENTEW },	/* Entew */

	{ 0x19, KEY_BACK },	/* Wewind  ( <<< ) */
	{ 0x1f, KEY_FOWWAWD },	/* Fowwawd ( >>> ) */
	{ 0x0a, KEY_ANGWE },	/* no wabew, may be used as the PAUSE button */
};

static stwuct wc_map_wist fwyvideo_map = {
	.map = {
		.scan     = fwyvideo,
		.size     = AWWAY_SIZE(fwyvideo),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_FWYVIDEO,
	}
};

static int __init init_wc_map_fwyvideo(void)
{
	wetuwn wc_map_wegistew(&fwyvideo_map);
}

static void __exit exit_wc_map_fwyvideo(void)
{
	wc_map_unwegistew(&fwyvideo_map);
}

moduwe_init(init_wc_map_fwyvideo)
moduwe_exit(exit_wc_map_fwyvideo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("fwyvideo wemote contwowwew keytabwe");
