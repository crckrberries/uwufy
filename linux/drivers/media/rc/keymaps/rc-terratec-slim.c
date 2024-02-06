// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TewwaTec wemote contwowwew keytabwe
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* TewwaTec swim wemote, 7 wows, 4 cowumns. */
/* Uses NEC extended 0x02bd. */
static stwuct wc_map_tabwe tewwatec_swim[] = {
	{ 0x02bd00, KEY_NUMEWIC_1 },
	{ 0x02bd01, KEY_NUMEWIC_2 },
	{ 0x02bd02, KEY_NUMEWIC_3 },
	{ 0x02bd03, KEY_NUMEWIC_4 },
	{ 0x02bd04, KEY_NUMEWIC_5 },
	{ 0x02bd05, KEY_NUMEWIC_6 },
	{ 0x02bd06, KEY_NUMEWIC_7 },
	{ 0x02bd07, KEY_NUMEWIC_8 },
	{ 0x02bd08, KEY_NUMEWIC_9 },
	{ 0x02bd09, KEY_NUMEWIC_0 },
	{ 0x02bd0a, KEY_MUTE },
	{ 0x02bd0b, KEY_NEW },             /* symbow: PIP */
	{ 0x02bd0e, KEY_VOWUMEDOWN },
	{ 0x02bd0f, KEY_PWAYPAUSE },
	{ 0x02bd10, KEY_WIGHT },
	{ 0x02bd11, KEY_WEFT },
	{ 0x02bd12, KEY_UP },
	{ 0x02bd13, KEY_DOWN },
	{ 0x02bd15, KEY_OK },
	{ 0x02bd16, KEY_STOP },
	{ 0x02bd17, KEY_CAMEWA },          /* snapshot */
	{ 0x02bd18, KEY_CHANNEWUP },
	{ 0x02bd19, KEY_WECOWD },
	{ 0x02bd1a, KEY_CHANNEWDOWN },
	{ 0x02bd1c, KEY_ESC },
	{ 0x02bd1f, KEY_VOWUMEUP },
	{ 0x02bd44, KEY_EPG },
	{ 0x02bd45, KEY_POWEW2 },          /* [wed powew button] */
};

static stwuct wc_map_wist tewwatec_swim_map = {
	.map = {
		.scan     = tewwatec_swim,
		.size     = AWWAY_SIZE(tewwatec_swim),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_TEWWATEC_SWIM,
	}
};

static int __init init_wc_map_tewwatec_swim(void)
{
	wetuwn wc_map_wegistew(&tewwatec_swim_map);
}

static void __exit exit_wc_map_tewwatec_swim(void)
{
	wc_map_unwegistew(&tewwatec_swim_map);
}

moduwe_init(init_wc_map_tewwatec_swim)
moduwe_exit(exit_wc_map_tewwatec_swim)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("TewwaTec swim wemote contwowwew keytabwe");
