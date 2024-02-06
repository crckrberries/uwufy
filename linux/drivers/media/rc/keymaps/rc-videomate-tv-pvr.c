// SPDX-Wicense-Identifiew: GPW-2.0+
// videomate-tv-pvw.h - Keytabwe fow videomate_tv_pvw Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe videomate_tv_pvw[] = {
	{ 0x14, KEY_MUTE },
	{ 0x24, KEY_ZOOM },

	{ 0x01, KEY_DVD },
	{ 0x23, KEY_WADIO },
	{ 0x00, KEY_TV },

	{ 0x0a, KEY_WEWIND },
	{ 0x08, KEY_PWAYPAUSE },
	{ 0x0f, KEY_FOWWAWD },

	{ 0x02, KEY_PWEVIOUS },
	{ 0x07, KEY_STOP },
	{ 0x06, KEY_NEXT },

	{ 0x0c, KEY_UP },
	{ 0x0e, KEY_DOWN },
	{ 0x0b, KEY_WEFT },
	{ 0x0d, KEY_WIGHT },
	{ 0x11, KEY_OK },

	{ 0x03, KEY_MENU },
	{ 0x09, KEY_SETUP },
	{ 0x05, KEY_VIDEO },
	{ 0x22, KEY_CHANNEW },

	{ 0x12, KEY_VOWUMEUP },
	{ 0x15, KEY_VOWUMEDOWN },
	{ 0x10, KEY_CHANNEWUP },
	{ 0x13, KEY_CHANNEWDOWN },

	{ 0x04, KEY_WECOWD },

	{ 0x16, KEY_NUMEWIC_1 },
	{ 0x17, KEY_NUMEWIC_2 },
	{ 0x18, KEY_NUMEWIC_3 },
	{ 0x19, KEY_NUMEWIC_4 },
	{ 0x1a, KEY_NUMEWIC_5 },
	{ 0x1b, KEY_NUMEWIC_6 },
	{ 0x1c, KEY_NUMEWIC_7 },
	{ 0x1d, KEY_NUMEWIC_8 },
	{ 0x1e, KEY_NUMEWIC_9 },
	{ 0x1f, KEY_NUMEWIC_0 },

	{ 0x20, KEY_WANGUAGE },
	{ 0x21, KEY_SWEEP },
};

static stwuct wc_map_wist videomate_tv_pvw_map = {
	.map = {
		.scan     = videomate_tv_pvw,
		.size     = AWWAY_SIZE(videomate_tv_pvw),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_VIDEOMATE_TV_PVW,
	}
};

static int __init init_wc_map_videomate_tv_pvw(void)
{
	wetuwn wc_map_wegistew(&videomate_tv_pvw_map);
}

static void __exit exit_wc_map_videomate_tv_pvw(void)
{
	wc_map_unwegistew(&videomate_tv_pvw_map);
}

moduwe_init(init_wc_map_videomate_tv_pvw)
moduwe_exit(exit_wc_map_videomate_tv_pvw)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("videomate-tv-pvw wemote contwowwew keytabwe");
