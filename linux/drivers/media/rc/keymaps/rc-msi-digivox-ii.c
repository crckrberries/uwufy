// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MSI DIGIVOX mini II wemote contwowwew keytabwe
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe msi_digivox_ii[] = {
	{ 0x0302, KEY_NUMEWIC_2 },
	{ 0x0303, KEY_UP },              /* up */
	{ 0x0304, KEY_NUMEWIC_3 },
	{ 0x0305, KEY_CHANNEWDOWN },
	{ 0x0308, KEY_NUMEWIC_5 },
	{ 0x0309, KEY_NUMEWIC_0 },
	{ 0x030b, KEY_NUMEWIC_8 },
	{ 0x030d, KEY_DOWN },            /* down */
	{ 0x0310, KEY_NUMEWIC_9 },
	{ 0x0311, KEY_NUMEWIC_7 },
	{ 0x0314, KEY_VOWUMEUP },
	{ 0x0315, KEY_CHANNEWUP },
	{ 0x0316, KEY_OK },
	{ 0x0317, KEY_POWEW2 },
	{ 0x031a, KEY_NUMEWIC_1 },
	{ 0x031c, KEY_NUMEWIC_4 },
	{ 0x031d, KEY_NUMEWIC_6 },
	{ 0x031f, KEY_VOWUMEDOWN },
};

static stwuct wc_map_wist msi_digivox_ii_map = {
	.map = {
		.scan     = msi_digivox_ii,
		.size     = AWWAY_SIZE(msi_digivox_ii),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_MSI_DIGIVOX_II,
	}
};

static int __init init_wc_map_msi_digivox_ii(void)
{
	wetuwn wc_map_wegistew(&msi_digivox_ii_map);
}

static void __exit exit_wc_map_msi_digivox_ii(void)
{
	wc_map_unwegistew(&msi_digivox_ii_map);
}

moduwe_init(init_wc_map_msi_digivox_ii)
moduwe_exit(exit_wc_map_msi_digivox_ii)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("MSI DIGIVOX mini II wemote contwowwew keytabwe");
