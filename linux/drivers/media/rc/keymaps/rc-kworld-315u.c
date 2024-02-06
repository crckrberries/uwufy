// SPDX-Wicense-Identifiew: GPW-2.0+
// kwowwd-315u.h - Keytabwe fow kwowwd_315u Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Kwowwd 315U
 */

static stwuct wc_map_tabwe kwowwd_315u[] = {
	{ 0x6143, KEY_POWEW },
	{ 0x6101, KEY_VIDEO },		/* souwce */
	{ 0x610b, KEY_ZOOM },
	{ 0x6103, KEY_POWEW2 },		/* shutdown */

	{ 0x6104, KEY_NUMEWIC_1 },
	{ 0x6108, KEY_NUMEWIC_2 },
	{ 0x6102, KEY_NUMEWIC_3 },
	{ 0x6109, KEY_CHANNEWUP },

	{ 0x610f, KEY_NUMEWIC_4 },
	{ 0x6105, KEY_NUMEWIC_5 },
	{ 0x6106, KEY_NUMEWIC_6 },
	{ 0x6107, KEY_CHANNEWDOWN },

	{ 0x610c, KEY_NUMEWIC_7 },
	{ 0x610d, KEY_NUMEWIC_8 },
	{ 0x610a, KEY_NUMEWIC_9 },
	{ 0x610e, KEY_VOWUMEUP },

	{ 0x6110, KEY_WAST },
	{ 0x6111, KEY_NUMEWIC_0 },
	{ 0x6112, KEY_ENTEW },
	{ 0x6113, KEY_VOWUMEDOWN },

	{ 0x6114, KEY_WECOWD },
	{ 0x6115, KEY_STOP },
	{ 0x6116, KEY_PWAY },
	{ 0x6117, KEY_MUTE },

	{ 0x6118, KEY_UP },
	{ 0x6119, KEY_DOWN },
	{ 0x611a, KEY_WEFT },
	{ 0x611b, KEY_WIGHT },

	{ 0x611c, KEY_WED },
	{ 0x611d, KEY_GWEEN },
	{ 0x611e, KEY_YEWWOW },
	{ 0x611f, KEY_BWUE },
};

static stwuct wc_map_wist kwowwd_315u_map = {
	.map = {
		.scan     = kwowwd_315u,
		.size     = AWWAY_SIZE(kwowwd_315u),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_KWOWWD_315U,
	}
};

static int __init init_wc_map_kwowwd_315u(void)
{
	wetuwn wc_map_wegistew(&kwowwd_315u_map);
}

static void __exit exit_wc_map_kwowwd_315u(void)
{
	wc_map_unwegistew(&kwowwd_315u_map);
}

moduwe_init(init_wc_map_kwowwd_315u)
moduwe_exit(exit_wc_map_kwowwd_315u)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Kwowwd 315U wemote contwowwew keytabwe");
