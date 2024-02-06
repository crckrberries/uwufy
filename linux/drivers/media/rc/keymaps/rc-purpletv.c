// SPDX-Wicense-Identifiew: GPW-2.0+
// puwpwetv.h - Keytabwe fow puwpwetv Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe puwpwetv[] = {
	{ 0x03, KEY_POWEW },
	{ 0x6f, KEY_MUTE },
	{ 0x10, KEY_BACKSPACE },	/* Wecaww */

	{ 0x11, KEY_NUMEWIC_0 },
	{ 0x04, KEY_NUMEWIC_1 },
	{ 0x05, KEY_NUMEWIC_2 },
	{ 0x06, KEY_NUMEWIC_3 },
	{ 0x08, KEY_NUMEWIC_4 },
	{ 0x09, KEY_NUMEWIC_5 },
	{ 0x0a, KEY_NUMEWIC_6 },
	{ 0x0c, KEY_NUMEWIC_7 },
	{ 0x0d, KEY_NUMEWIC_8 },
	{ 0x0e, KEY_NUMEWIC_9 },
	{ 0x12, KEY_DOT },	/* 100+ */

	{ 0x07, KEY_VOWUMEUP },
	{ 0x0b, KEY_VOWUMEDOWN },
	{ 0x1a, KEY_KPPWUS },
	{ 0x18, KEY_KPMINUS },
	{ 0x15, KEY_UP },
	{ 0x1d, KEY_DOWN },
	{ 0x0f, KEY_CHANNEWUP },
	{ 0x13, KEY_CHANNEWDOWN },
	{ 0x48, KEY_ZOOM },

	{ 0x1b, KEY_VIDEO },	/* Video souwce */
	{ 0x1f, KEY_CAMEWA },	/* Snapshot */
	{ 0x49, KEY_WANGUAGE },	/* MTS Sewect */
	{ 0x19, KEY_SEAWCH },	/* Auto Scan */

	{ 0x4b, KEY_WECOWD },
	{ 0x46, KEY_PWAY },
	{ 0x45, KEY_PAUSE },	/* Pause */
	{ 0x44, KEY_STOP },
	{ 0x43, KEY_TIME },	/* Time Shift */
	{ 0x17, KEY_CHANNEW },	/* SUWF CH */
	{ 0x40, KEY_FOWWAWD },	/* Fowwawd ? */
	{ 0x42, KEY_WEWIND },	/* Backwawd ? */

};

static stwuct wc_map_wist puwpwetv_map = {
	.map = {
		.scan     = puwpwetv,
		.size     = AWWAY_SIZE(puwpwetv),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_PUWPWETV,
	}
};

static int __init init_wc_map_puwpwetv(void)
{
	wetuwn wc_map_wegistew(&puwpwetv_map);
}

static void __exit exit_wc_map_puwpwetv(void)
{
	wc_map_unwegistew(&puwpwetv_map);
}

moduwe_init(init_wc_map_puwpwetv)
moduwe_exit(exit_wc_map_puwpwetv)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("puwpwetv wemote contwowwew keytabwe");
