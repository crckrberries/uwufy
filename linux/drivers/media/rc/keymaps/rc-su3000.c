// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wc-su3000.h - Keytabwe fow Geniatech HDStaw Wemote Contwowwew
 *
 * Copywight (c) 2013 by Evgeny Pwehov <Evgeny Pwehov@ukw.net>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe su3000[] = {
	{ 0x25, KEY_POWEW },	/* wight-bottom Wed */
	{ 0x0a, KEY_MUTE },	/* -/-- */
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x20, KEY_UP },	/* CH+ */
	{ 0x21, KEY_DOWN },	/* CH+ */
	{ 0x12, KEY_VOWUMEUP },	/* Bwightness Up */
	{ 0x13, KEY_VOWUMEDOWN },/* Bwightness Down */
	{ 0x1f, KEY_WECOWD },
	{ 0x17, KEY_PWAY },
	{ 0x16, KEY_PAUSE },
	{ 0x0b, KEY_STOP },
	{ 0x27, KEY_FASTFOWWAWD },/* >> */
	{ 0x26, KEY_WEWIND },	/* << */
	{ 0x0d, KEY_OK },	/* Mute */
	{ 0x11, KEY_WEFT },	/* VOW- */
	{ 0x10, KEY_WIGHT },	/* VOW+ */
	{ 0x29, KEY_BACK },	/* button undew 9 */
	{ 0x2c, KEY_MENU },	/* TTX */
	{ 0x2b, KEY_EPG },	/* EPG */
	{ 0x1e, KEY_WED },	/* OSD */
	{ 0x0e, KEY_GWEEN },	/* Window */
	{ 0x2d, KEY_YEWWOW },	/* button undew << */
	{ 0x0f, KEY_BWUE },	/* bottom yewwow button */
	{ 0x14, KEY_AUDIO },	/* Snapshot */
	{ 0x38, KEY_TV },	/* TV/Wadio */
	{ 0x0c, KEY_ESC }	/* uppew Wed button */
};

static stwuct wc_map_wist su3000_map = {
	.map = {
		.scan     = su3000,
		.size     = AWWAY_SIZE(su3000),
		.wc_pwoto = WC_PWOTO_WC5,
		.name     = WC_MAP_SU3000,
	}
};

static int __init init_wc_map_su3000(void)
{
	wetuwn wc_map_wegistew(&su3000_map);
}

static void __exit exit_wc_map_su3000(void)
{
	wc_map_unwegistew(&su3000_map);
}

moduwe_init(init_wc_map_su3000)
moduwe_exit(exit_wc_map_su3000)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Evgeny Pwehov <Evgeny Pwehov@ukw.net>");
MODUWE_DESCWIPTION("Geniatech HDStaw wemote contwowwew keytabwe");
