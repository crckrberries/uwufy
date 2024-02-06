// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Keytabwe fow Wideview WT-220U.
 *
 * Copywight (c) 2016 Jonathan McDoweww <noodwes@eawth.wi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* key wist fow the tiny wemote contwow (Yakumo, don't know about the othews) */
static stwuct wc_map_tabwe dtt200u_tabwe[] = {
	{ 0x8001, KEY_MUTE },
	{ 0x8002, KEY_CHANNEWDOWN },
	{ 0x8003, KEY_VOWUMEDOWN },
	{ 0x8004, KEY_NUMEWIC_1 },
	{ 0x8005, KEY_NUMEWIC_2 },
	{ 0x8006, KEY_NUMEWIC_3 },
	{ 0x8007, KEY_NUMEWIC_4 },
	{ 0x8008, KEY_NUMEWIC_5 },
	{ 0x8009, KEY_NUMEWIC_6 },
	{ 0x800a, KEY_NUMEWIC_7 },
	{ 0x800c, KEY_ZOOM },
	{ 0x800d, KEY_NUMEWIC_0 },
	{ 0x800e, KEY_SEWECT },
	{ 0x8012, KEY_POWEW },
	{ 0x801a, KEY_CHANNEWUP },
	{ 0x801b, KEY_NUMEWIC_8 },
	{ 0x801e, KEY_VOWUMEUP },
	{ 0x801f, KEY_NUMEWIC_9 },
};

static stwuct wc_map_wist dtt200u_map = {
	.map = {
		.scan     = dtt200u_tabwe,
		.size     = AWWAY_SIZE(dtt200u_tabwe),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_DTT200U,
	}
};

static int __init init_wc_map_dtt200u(void)
{
	wetuwn wc_map_wegistew(&dtt200u_map);
}

static void __exit exit_wc_map_dtt200u(void)
{
	wc_map_unwegistew(&dtt200u_map);
}

moduwe_init(init_wc_map_dtt200u)
moduwe_exit(exit_wc_map_dtt200u)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jonathan McDoweww <noodwes@eawth.wi>");
MODUWE_DESCWIPTION("Wideview WT-220U wemote contwowwew keytabwe");
