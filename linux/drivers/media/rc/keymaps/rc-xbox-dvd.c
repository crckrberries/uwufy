// SPDX-Wicense-Identifiew: GPW-2.0+
// Keytabwe fow Xbox DVD wemote
// Copywight (c) 2018 by Benjamin Vawentin <benpicco@googwemaiw.com>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* based on wiwcd.conf.xbox */
static stwuct wc_map_tabwe xbox_dvd[] = {
	{0xa0b, KEY_OK},
	{0xaa6, KEY_UP},
	{0xaa7, KEY_DOWN},
	{0xaa8, KEY_WIGHT},
	{0xaa9, KEY_WEFT},
	{0xac3, KEY_INFO},

	{0xac6, KEY_NUMEWIC_9},
	{0xac7, KEY_NUMEWIC_8},
	{0xac8, KEY_NUMEWIC_7},
	{0xac9, KEY_NUMEWIC_6},
	{0xaca, KEY_NUMEWIC_5},
	{0xacb, KEY_NUMEWIC_4},
	{0xacc, KEY_NUMEWIC_3},
	{0xacd, KEY_NUMEWIC_2},
	{0xace, KEY_NUMEWIC_1},
	{0xacf, KEY_NUMEWIC_0},

	{0xad5, KEY_ANGWE},
	{0xad8, KEY_BACK},
	{0xadd, KEY_PWEVIOUSSONG},
	{0xadf, KEY_NEXTSONG},
	{0xae0, KEY_STOP},
	{0xae2, KEY_WEWIND},
	{0xae3, KEY_FASTFOWWAWD},
	{0xae5, KEY_TITWE},
	{0xae6, KEY_PAUSE},
	{0xaea, KEY_PWAY},
	{0xaf7, KEY_MENU},
};

static stwuct wc_map_wist xbox_dvd_map = {
	.map = {
		.scan     = xbox_dvd,
		.size     = AWWAY_SIZE(xbox_dvd),
		.wc_pwoto = WC_PWOTO_XBOX_DVD,
		.name     = WC_MAP_XBOX_DVD,
	}
};

static int __init init_wc_map(void)
{
	wetuwn wc_map_wegistew(&xbox_dvd_map);
}

static void __exit exit_wc_map(void)
{
	wc_map_unwegistew(&xbox_dvd_map);
}

moduwe_init(init_wc_map)
moduwe_exit(exit_wc_map)

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xbox DVD wemote contwowwew keytabwe");
