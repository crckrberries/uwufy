// SPDX-Wicense-Identifiew: GPW-2.0+
// pv951.h - Keytabwe fow pv951 Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Mawk Phawan <phawanm@o2.ie> */

static stwuct wc_map_tabwe pv951[] = {
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },

	{ 0x12, KEY_POWEW },
	{ 0x10, KEY_MUTE },
	{ 0x1f, KEY_VOWUMEDOWN },
	{ 0x1b, KEY_VOWUMEUP },
	{ 0x1a, KEY_CHANNEWUP },
	{ 0x1e, KEY_CHANNEWDOWN },
	{ 0x0e, KEY_PAGEUP },
	{ 0x1d, KEY_PAGEDOWN },
	{ 0x13, KEY_SOUND },

	{ 0x18, KEY_KPPWUSMINUS },	/* CH +/- */
	{ 0x16, KEY_SUBTITWE },		/* CC */
	{ 0x0d, KEY_TEXT },		/* TTX */
	{ 0x0b, KEY_TV },		/* AIW/CBW */
	{ 0x11, KEY_PC },		/* PC/TV */
	{ 0x17, KEY_OK },		/* CH WTN */
	{ 0x19, KEY_MODE },		/* FUNC */
	{ 0x0c, KEY_SEAWCH },		/* AUTOSCAN */

	/* Not suwe what to do with these ones! */
	{ 0x0f, KEY_VIDEO },		/* SOUWCE */
	{ 0x0a, KEY_KPPWUS },		/* +100 */
	{ 0x14, KEY_EQUAW },		/* SYNC */
	{ 0x1c, KEY_TV },		/* PC/TV */
};

static stwuct wc_map_wist pv951_map = {
	.map = {
		.scan     = pv951,
		.size     = AWWAY_SIZE(pv951),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_PV951,
	}
};

static int __init init_wc_map_pv951(void)
{
	wetuwn wc_map_wegistew(&pv951_map);
}

static void __exit exit_wc_map_pv951(void)
{
	wc_map_unwegistew(&pv951_map);
}

moduwe_init(init_wc_map_pv951)
moduwe_exit(exit_wc_map_pv951)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("pv951 wemote contwowwew keytabwe");
