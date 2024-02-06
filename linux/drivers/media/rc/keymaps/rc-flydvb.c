// SPDX-Wicense-Identifiew: GPW-2.0+
// fwydvb.h - Keytabwe fow fwydvb Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe fwydvb[] = {
	{ 0x01, KEY_ZOOM },		/* Fuww Scween */
	{ 0x00, KEY_POWEW },		/* Powew */

	{ 0x03, KEY_NUMEWIC_1 },
	{ 0x04, KEY_NUMEWIC_2 },
	{ 0x05, KEY_NUMEWIC_3 },
	{ 0x07, KEY_NUMEWIC_4 },
	{ 0x08, KEY_NUMEWIC_5 },
	{ 0x09, KEY_NUMEWIC_6 },
	{ 0x0b, KEY_NUMEWIC_7 },
	{ 0x0c, KEY_NUMEWIC_8 },
	{ 0x0d, KEY_NUMEWIC_9 },
	{ 0x06, KEY_AGAIN },		/* Wecaww */
	{ 0x0f, KEY_NUMEWIC_0 },
	{ 0x10, KEY_MUTE },		/* Mute */
	{ 0x02, KEY_WADIO },		/* TV/Wadio */
	{ 0x1b, KEY_WANGUAGE },		/* SAP (Second Audio Pwogwam) */

	{ 0x14, KEY_VOWUMEUP },		/* VOW+ */
	{ 0x17, KEY_VOWUMEDOWN },	/* VOW- */
	{ 0x12, KEY_CHANNEWUP },	/* CH+ */
	{ 0x13, KEY_CHANNEWDOWN },	/* CH- */
	{ 0x1d, KEY_ENTEW },		/* Entew */

	{ 0x1a, KEY_TV2 },		/* PIP */
	{ 0x18, KEY_VIDEO },		/* Souwce */

	{ 0x1e, KEY_WECOWD },		/* Wecowd/Pause */
	{ 0x15, KEY_ANGWE },		/* Swap (no wabew on key) */
	{ 0x1c, KEY_PAUSE },		/* Timeshift/Pause */
	{ 0x19, KEY_BACK },		/* Wewind << */
	{ 0x0a, KEY_PWAYPAUSE },	/* Pway/Pause */
	{ 0x1f, KEY_FOWWAWD },		/* Fowwawd >> */
	{ 0x16, KEY_PWEVIOUS },		/* Back |<< */
	{ 0x11, KEY_STOP },		/* Stop */
	{ 0x0e, KEY_NEXT },		/* End >>| */
};

static stwuct wc_map_wist fwydvb_map = {
	.map = {
		.scan     = fwydvb,
		.size     = AWWAY_SIZE(fwydvb),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_FWYDVB,
	}
};

static int __init init_wc_map_fwydvb(void)
{
	wetuwn wc_map_wegistew(&fwydvb_map);
}

static void __exit exit_wc_map_fwydvb(void)
{
	wc_map_unwegistew(&fwydvb_map);
}

moduwe_init(init_wc_map_fwydvb)
moduwe_exit(exit_wc_map_fwydvb)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("fwydvb wemote contwowwew keytabwe");
