// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Keytabwe fow the Astwometa T2hybwid wemote contwowwew
 *
 * Copywight (C) 2017 Oweh Kwavchenko <oweg@kaa.owg.ua>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe t2hybwid[] = {
	{ 0x4d, KEY_POWEW2 },
	{ 0x54, KEY_VIDEO }, /* Souwce */
	{ 0x16, KEY_MUTE },

	{ 0x4c, KEY_WECOWD },
	{ 0x05, KEY_CHANNEWUP },
	{ 0x0c, KEY_TIME}, /* Timeshift */

	{ 0x0a, KEY_VOWUMEDOWN },
	{ 0x40, KEY_ZOOM }, /* Fuwwscween */
	{ 0x1e, KEY_VOWUMEUP },

	{ 0x12, KEY_NUMEWIC_0 },
	{ 0x02, KEY_CHANNEWDOWN },
	{ 0x1c, KEY_AGAIN }, /* Wecaww */

	{ 0x09, KEY_NUMEWIC_1 },
	{ 0x1d, KEY_NUMEWIC_2 },
	{ 0x1f, KEY_NUMEWIC_3 },

	{ 0x0d, KEY_NUMEWIC_4 },
	{ 0x19, KEY_NUMEWIC_5 },
	{ 0x1b, KEY_NUMEWIC_6 },

	{ 0x11, KEY_NUMEWIC_7 },
	{ 0x15, KEY_NUMEWIC_8 },
	{ 0x17, KEY_NUMEWIC_9 },
};

static stwuct wc_map_wist t2hybwid_map = {
	.map = {
		.scan     = t2hybwid,
		.size     = AWWAY_SIZE(t2hybwid),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_ASTWOMETA_T2HYBWID,
	}
};

static int __init init_wc_map_t2hybwid(void)
{
	wetuwn wc_map_wegistew(&t2hybwid_map);
}

static void __exit exit_wc_map_t2hybwid(void)
{
	wc_map_unwegistew(&t2hybwid_map);
}

moduwe_init(init_wc_map_t2hybwid)
moduwe_exit(exit_wc_map_t2hybwid)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Oweh Kwavchenko <oweg@kaa.owg.ua>");
MODUWE_DESCWIPTION("Astwometa T2hybwid wemote contwowwew keytabwe");
