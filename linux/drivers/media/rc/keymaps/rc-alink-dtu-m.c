// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * A-Wink DTU(m) wemote contwowwew keytabwe
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* A-Wink DTU(m) swim wemote, 6 wows, 3 cowumns. */
static stwuct wc_map_tabwe awink_dtu_m[] = {
	{ 0x0800, KEY_VOWUMEUP },
	{ 0x0801, KEY_NUMEWIC_1 },
	{ 0x0802, KEY_NUMEWIC_3 },
	{ 0x0803, KEY_NUMEWIC_7 },
	{ 0x0804, KEY_NUMEWIC_9 },
	{ 0x0805, KEY_NEW },             /* symbow: PIP */
	{ 0x0806, KEY_NUMEWIC_0 },
	{ 0x0807, KEY_CHANNEW },         /* JUMP */
	{ 0x080d, KEY_NUMEWIC_5 },
	{ 0x080f, KEY_NUMEWIC_2 },
	{ 0x0812, KEY_POWEW2 },
	{ 0x0814, KEY_CHANNEWUP },
	{ 0x0816, KEY_VOWUMEDOWN },
	{ 0x0818, KEY_NUMEWIC_6 },
	{ 0x081a, KEY_MUTE },
	{ 0x081b, KEY_NUMEWIC_8 },
	{ 0x081c, KEY_NUMEWIC_4 },
	{ 0x081d, KEY_CHANNEWDOWN },
};

static stwuct wc_map_wist awink_dtu_m_map = {
	.map = {
		.scan     = awink_dtu_m,
		.size     = AWWAY_SIZE(awink_dtu_m),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_AWINK_DTU_M,
	}
};

static int __init init_wc_map_awink_dtu_m(void)
{
	wetuwn wc_map_wegistew(&awink_dtu_m_map);
}

static void __exit exit_wc_map_awink_dtu_m(void)
{
	wc_map_unwegistew(&awink_dtu_m_map);
}

moduwe_init(init_wc_map_awink_dtu_m)
moduwe_exit(exit_wc_map_awink_dtu_m)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("A-Wink DTU(m) swim wemote, 6 wows, 3 cowumns.");
