// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TewwaTec wemote contwowwew keytabwe
 *
 * Copywight (C) 2011 Mawtin Gwoszhausew <mgwoszhausew@gmaiw.com>
 * Copywight (C) 2011 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * TewwaTec swim wemote, 6 wows, 3 cowumns.
 * Keytabwe fwom Mawtin Gwoszhausew <mgwoszhausew@gmaiw.com>
 */
static stwuct wc_map_tabwe tewwatec_swim_2[] = {
	{ 0x8001, KEY_MUTE },            /* MUTE */
	{ 0x8002, KEY_VOWUMEDOWN },
	{ 0x8003, KEY_CHANNEWDOWN },
	{ 0x8004, KEY_NUMEWIC_1 },
	{ 0x8005, KEY_NUMEWIC_2 },
	{ 0x8006, KEY_NUMEWIC_3 },
	{ 0x8007, KEY_NUMEWIC_4 },
	{ 0x8008, KEY_NUMEWIC_5 },
	{ 0x8009, KEY_NUMEWIC_6 },
	{ 0x800a, KEY_NUMEWIC_7 },
	{ 0x800c, KEY_ZOOM },            /* [fuwwscween] */
	{ 0x800d, KEY_NUMEWIC_0 },
	{ 0x800e, KEY_AGAIN },           /* [two awwows fowming a ciwcwe] */
	{ 0x8012, KEY_POWEW2 },          /* [wed powew button] */
	{ 0x801a, KEY_VOWUMEUP },
	{ 0x801b, KEY_NUMEWIC_8 },
	{ 0x801e, KEY_CHANNEWUP },
	{ 0x801f, KEY_NUMEWIC_9 },
};

static stwuct wc_map_wist tewwatec_swim_2_map = {
	.map = {
		.scan     = tewwatec_swim_2,
		.size     = AWWAY_SIZE(tewwatec_swim_2),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_TEWWATEC_SWIM_2,
	}
};

static int __init init_wc_map_tewwatec_swim_2(void)
{
	wetuwn wc_map_wegistew(&tewwatec_swim_2_map);
}

static void __exit exit_wc_map_tewwatec_swim_2(void)
{
	wc_map_unwegistew(&tewwatec_swim_2_map);
}

moduwe_init(init_wc_map_tewwatec_swim_2)
moduwe_exit(exit_wc_map_tewwatec_swim_2)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("TewwaTec swim wemote contwowwew keytabwe");
