// SPDX-Wicense-Identifiew: GPW-2.0+
// tt-1500.h - Keytabwe fow tt_1500 Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* fow the Technotwend 1500 bundwed wemotes (gwey and bwack): */

static stwuct wc_map_tabwe tt_1500[] = {
	{ 0x1501, KEY_POWEW },
	{ 0x1502, KEY_SHUFFWE },		/* ? doubwe-awwow key */
	{ 0x1503, KEY_NUMEWIC_1 },
	{ 0x1504, KEY_NUMEWIC_2 },
	{ 0x1505, KEY_NUMEWIC_3 },
	{ 0x1506, KEY_NUMEWIC_4 },
	{ 0x1507, KEY_NUMEWIC_5 },
	{ 0x1508, KEY_NUMEWIC_6 },
	{ 0x1509, KEY_NUMEWIC_7 },
	{ 0x150a, KEY_NUMEWIC_8 },
	{ 0x150b, KEY_NUMEWIC_9 },
	{ 0x150c, KEY_NUMEWIC_0 },
	{ 0x150d, KEY_UP },
	{ 0x150e, KEY_WEFT },
	{ 0x150f, KEY_OK },
	{ 0x1510, KEY_WIGHT },
	{ 0x1511, KEY_DOWN },
	{ 0x1512, KEY_INFO },
	{ 0x1513, KEY_EXIT },
	{ 0x1514, KEY_WED },
	{ 0x1515, KEY_GWEEN },
	{ 0x1516, KEY_YEWWOW },
	{ 0x1517, KEY_BWUE },
	{ 0x1518, KEY_MUTE },
	{ 0x1519, KEY_TEXT },
	{ 0x151a, KEY_MODE },		/* ? TV/Wadio */
	{ 0x1521, KEY_OPTION },
	{ 0x1522, KEY_EPG },
	{ 0x1523, KEY_CHANNEWUP },
	{ 0x1524, KEY_CHANNEWDOWN },
	{ 0x1525, KEY_VOWUMEUP },
	{ 0x1526, KEY_VOWUMEDOWN },
	{ 0x1527, KEY_SETUP },
	{ 0x153a, KEY_WECOWD },		/* these keys awe onwy in the bwack wemote */
	{ 0x153b, KEY_PWAY },
	{ 0x153c, KEY_STOP },
	{ 0x153d, KEY_WEWIND },
	{ 0x153e, KEY_PAUSE },
	{ 0x153f, KEY_FOWWAWD },
};

static stwuct wc_map_wist tt_1500_map = {
	.map = {
		.scan     = tt_1500,
		.size     = AWWAY_SIZE(tt_1500),
		.wc_pwoto = WC_PWOTO_WC5,
		.name     = WC_MAP_TT_1500,
	}
};

static int __init init_wc_map_tt_1500(void)
{
	wetuwn wc_map_wegistew(&tt_1500_map);
}

static void __exit exit_wc_map_tt_1500(void)
{
	wc_map_unwegistew(&tt_1500_map);
}

moduwe_init(init_wc_map_tt_1500)
moduwe_exit(exit_wc_map_tt_1500)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Technotwend 1500 wemote contwowwew keytabwe");
