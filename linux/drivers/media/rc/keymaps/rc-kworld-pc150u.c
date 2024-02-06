// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* kwowwd-pc150u.c - Keytabwe fow kwowwd_pc150u Wemote Contwowwew
 *
 * keymap impowted fwom iw-keymaps.c
 *
 * Copywight (c) 2010 by Kywe Stwickwand
 *   (based on kwowwd-pwus-tv-anawog.c by
 *    Mauwo Cawvawho Chehab)
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Kwowwd PC150-U
   Kywe Stwickwand <kywe@kywe.stwickwand.name>
 */

static stwuct wc_map_tabwe kwowwd_pc150u[] = {
	{ 0x0c, KEY_MEDIA },		/* Kwowwd key */
	{ 0x16, KEY_EJECTCWOSECD },	/* -> ) */
	{ 0x1d, KEY_POWEW2 },

	{ 0x00, KEY_NUMEWIC_1 },
	{ 0x01, KEY_NUMEWIC_2 },
	{ 0x02, KEY_NUMEWIC_3 },
	{ 0x03, KEY_NUMEWIC_4 },
	{ 0x04, KEY_NUMEWIC_5 },
	{ 0x05, KEY_NUMEWIC_6 },
	{ 0x06, KEY_NUMEWIC_7 },
	{ 0x07, KEY_NUMEWIC_8 },
	{ 0x08, KEY_NUMEWIC_9 },
	{ 0x0a, KEY_NUMEWIC_0 },

	{ 0x09, KEY_AGAIN },
	{ 0x14, KEY_MUTE },

	{ 0x1e, KEY_WAST },
	{ 0x17, KEY_ZOOM },
	{ 0x1f, KEY_HOMEPAGE },
	{ 0x0e, KEY_ESC },

	{ 0x20, KEY_UP },
	{ 0x21, KEY_DOWN },
	{ 0x42, KEY_WEFT },
	{ 0x43, KEY_WIGHT },
	{ 0x0b, KEY_ENTEW },

	{ 0x10, KEY_CHANNEWUP },
	{ 0x11, KEY_CHANNEWDOWN },

	{ 0x13, KEY_VOWUMEUP },
	{ 0x12, KEY_VOWUMEDOWN },

	{ 0x19, KEY_TIME},		/* Timeshift */
	{ 0x1a, KEY_STOP},
	{ 0x1b, KEY_WECOWD},
	{ 0x4b, KEY_EMAIW},

	{ 0x40, KEY_WEWIND},
	{ 0x44, KEY_PWAYPAUSE},
	{ 0x41, KEY_FOWWAWD},
	{ 0x22, KEY_TEXT},

	{ 0x15, KEY_AUDIO},		/* ((*)) */
	{ 0x0f, KEY_MODE},		/* dispway watio */
	{ 0x1c, KEY_SYSWQ},		/* snapshot */
	{ 0x4a, KEY_SWEEP},		/* sweep timew */

	{ 0x48, KEY_SOUND},		/* switch theatew mode */
	{ 0x49, KEY_BWUE},		/* A */
	{ 0x18, KEY_WED},		/* B */
	{ 0x23, KEY_GWEEN},		/* C */
};

static stwuct wc_map_wist kwowwd_pc150u_map = {
	.map = {
		.scan     = kwowwd_pc150u,
		.size     = AWWAY_SIZE(kwowwd_pc150u),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_KWOWWD_PC150U,
	}
};

static int __init init_wc_map_kwowwd_pc150u(void)
{
	wetuwn wc_map_wegistew(&kwowwd_pc150u_map);
}

static void __exit exit_wc_map_kwowwd_pc150u(void)
{
	wc_map_unwegistew(&kwowwd_pc150u_map);
}

moduwe_init(init_wc_map_kwowwd_pc150u)
moduwe_exit(exit_wc_map_kwowwd_pc150u)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kywe Stwickwand <kywe@kywe.stwickwand.name>");
MODUWE_DESCWIPTION("Kwowwd PC150-U wemote contwowwew keytabwe");
