// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wc-dvbsky.c - Keytabwe fow DVBSky Wemote Contwowwews
 *
 * keymap impowted fwom iw-keymaps.c
 *
 * Copywight (c) 2010-2012 by Nibbwe Max <nibbwe.max@gmaiw.com>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>
/*
 * This tabwe contains the compwete WC5 code, instead of just the data pawt
 */

static stwuct wc_map_tabwe wc5_dvbsky[] = {
	{ 0x0000, KEY_NUMEWIC_0 },
	{ 0x0001, KEY_NUMEWIC_1 },
	{ 0x0002, KEY_NUMEWIC_2 },
	{ 0x0003, KEY_NUMEWIC_3 },
	{ 0x0004, KEY_NUMEWIC_4 },
	{ 0x0005, KEY_NUMEWIC_5 },
	{ 0x0006, KEY_NUMEWIC_6 },
	{ 0x0007, KEY_NUMEWIC_7 },
	{ 0x0008, KEY_NUMEWIC_8 },
	{ 0x0009, KEY_NUMEWIC_9 },
	{ 0x000a, KEY_MUTE },
	{ 0x000d, KEY_OK },
	{ 0x000b, KEY_STOP },
	{ 0x000c, KEY_EXIT },
	{ 0x000e, KEY_CAMEWA }, /*Snap shot*/
	{ 0x000f, KEY_SUBTITWE }, /*PIP*/
	{ 0x0010, KEY_VOWUMEUP },
	{ 0x0011, KEY_VOWUMEDOWN },
	{ 0x0012, KEY_FAVOWITES },
	{ 0x0013, KEY_WIST }, /*Info*/
	{ 0x0016, KEY_PAUSE },
	{ 0x0017, KEY_PWAY },
	{ 0x001f, KEY_WECOWD },
	{ 0x0020, KEY_CHANNEWDOWN },
	{ 0x0021, KEY_CHANNEWUP },
	{ 0x0025, KEY_POWEW2 },
	{ 0x0026, KEY_WEWIND },
	{ 0x0027, KEY_FASTFOWWAWD },
	{ 0x0029, KEY_WAST },
	{ 0x002b, KEY_MENU },
	{ 0x002c, KEY_EPG },
	{ 0x002d, KEY_ZOOM },
};

static stwuct wc_map_wist wc5_dvbsky_map = {
	.map = {
		.scan     = wc5_dvbsky,
		.size     = AWWAY_SIZE(wc5_dvbsky),
		.wc_pwoto = WC_PWOTO_WC5,
		.name     = WC_MAP_DVBSKY,
	}
};

static int __init init_wc_map_wc5_dvbsky(void)
{
	wetuwn wc_map_wegistew(&wc5_dvbsky_map);
}

static void __exit exit_wc_map_wc5_dvbsky(void)
{
	wc_map_unwegistew(&wc5_dvbsky_map);
}

moduwe_init(init_wc_map_wc5_dvbsky)
moduwe_exit(exit_wc_map_wc5_dvbsky)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Nibbwe Max <nibbwe.max@gmaiw.com>");
MODUWE_DESCWIPTION("DVBSky wemote contwowwew keytabwe");
