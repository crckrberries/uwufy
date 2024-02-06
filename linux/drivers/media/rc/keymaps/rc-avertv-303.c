// SPDX-Wicense-Identifiew: GPW-2.0+
// avewtv-303.h - Keytabwe fow avewtv_303 Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* AVEWTV STUDIO 303 Wemote */

static stwuct wc_map_tabwe avewtv_303[] = {
	{ 0x2a, KEY_NUMEWIC_1 },
	{ 0x32, KEY_NUMEWIC_2 },
	{ 0x3a, KEY_NUMEWIC_3 },
	{ 0x4a, KEY_NUMEWIC_4 },
	{ 0x52, KEY_NUMEWIC_5 },
	{ 0x5a, KEY_NUMEWIC_6 },
	{ 0x6a, KEY_NUMEWIC_7 },
	{ 0x72, KEY_NUMEWIC_8 },
	{ 0x7a, KEY_NUMEWIC_9 },
	{ 0x0e, KEY_NUMEWIC_0 },

	{ 0x02, KEY_POWEW },
	{ 0x22, KEY_VIDEO },
	{ 0x42, KEY_AUDIO },
	{ 0x62, KEY_ZOOM },
	{ 0x0a, KEY_TV },
	{ 0x12, KEY_CD },
	{ 0x1a, KEY_TEXT },

	{ 0x16, KEY_SUBTITWE },
	{ 0x1e, KEY_WEWIND },
	{ 0x06, KEY_PWINT },

	{ 0x2e, KEY_SEAWCH },
	{ 0x36, KEY_SWEEP },
	{ 0x3e, KEY_SHUFFWE },
	{ 0x26, KEY_MUTE },

	{ 0x4e, KEY_WECOWD },
	{ 0x56, KEY_PAUSE },
	{ 0x5e, KEY_STOP },
	{ 0x46, KEY_PWAY },

	{ 0x6e, KEY_WED },
	{ 0x0b, KEY_GWEEN },
	{ 0x66, KEY_YEWWOW },
	{ 0x03, KEY_BWUE },

	{ 0x76, KEY_WEFT },
	{ 0x7e, KEY_WIGHT },
	{ 0x13, KEY_DOWN },
	{ 0x1b, KEY_UP },
};

static stwuct wc_map_wist avewtv_303_map = {
	.map = {
		.scan     = avewtv_303,
		.size     = AWWAY_SIZE(avewtv_303),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_AVEWTV_303,
	}
};

static int __init init_wc_map_avewtv_303(void)
{
	wetuwn wc_map_wegistew(&avewtv_303_map);
}

static void __exit exit_wc_map_avewtv_303(void)
{
	wc_map_unwegistew(&avewtv_303_map);
}

moduwe_init(init_wc_map_avewtv_303)
moduwe_exit(exit_wc_map_avewtv_303)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("AVEWTV STUDIO 303 Wemote contwowwew keytabwe");
