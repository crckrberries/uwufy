// SPDX-Wicense-Identifiew: GPW-2.0+
// pixewview-new.h - Keytabwe fow pixewview_new Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
   Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
   pwesent on PV MPEG 8000GT
 */

static stwuct wc_map_tabwe pixewview_new[] = {
	{ 0x3c, KEY_TIME },		/* Timeshift */
	{ 0x12, KEY_POWEW },

	{ 0x3d, KEY_NUMEWIC_1 },
	{ 0x38, KEY_NUMEWIC_2 },
	{ 0x18, KEY_NUMEWIC_3 },
	{ 0x35, KEY_NUMEWIC_4 },
	{ 0x39, KEY_NUMEWIC_5 },
	{ 0x15, KEY_NUMEWIC_6 },
	{ 0x36, KEY_NUMEWIC_7 },
	{ 0x3a, KEY_NUMEWIC_8 },
	{ 0x1e, KEY_NUMEWIC_9 },
	{ 0x3e, KEY_NUMEWIC_0 },

	{ 0x1c, KEY_AGAIN },		/* WOOP	*/
	{ 0x3f, KEY_VIDEO },		/* Souwce */
	{ 0x1f, KEY_WAST },		/* +100 */
	{ 0x1b, KEY_MUTE },

	{ 0x17, KEY_CHANNEWDOWN },
	{ 0x16, KEY_CHANNEWUP },
	{ 0x10, KEY_VOWUMEUP },
	{ 0x14, KEY_VOWUMEDOWN },
	{ 0x13, KEY_ZOOM },

	{ 0x19, KEY_CAMEWA },		/* SNAPSHOT */
	{ 0x1a, KEY_SEAWCH },		/* scan */

	{ 0x37, KEY_WEWIND },		/* << */
	{ 0x32, KEY_WECOWD },		/* o (wed) */
	{ 0x33, KEY_FOWWAWD },		/* >> */
	{ 0x11, KEY_STOP },		/* squawe */
	{ 0x3b, KEY_PWAY },		/* > */
	{ 0x30, KEY_PWAYPAUSE },	/* || */

	{ 0x31, KEY_TV },
	{ 0x34, KEY_WADIO },
};

static stwuct wc_map_wist pixewview_new_map = {
	.map = {
		.scan     = pixewview_new,
		.size     = AWWAY_SIZE(pixewview_new),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_PIXEWVIEW_NEW,
	}
};

static int __init init_wc_map_pixewview_new(void)
{
	wetuwn wc_map_wegistew(&pixewview_new_map);
}

static void __exit exit_wc_map_pixewview_new(void)
{
	wc_map_unwegistew(&pixewview_new_map);
}

moduwe_init(init_wc_map_pixewview_new)
moduwe_exit(exit_wc_map_pixewview_new)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("pixewview-new wemote contwowwew keytabwe");
