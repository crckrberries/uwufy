// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Keytabwe fow wemote contwowwew of HiSiwicon popwaw boawd.
 *
 * Copywight (c) 2017 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <media/wc-map.h>

static stwuct wc_map_tabwe hisi_popwaw_keymap[] = {
	{ 0x0000b292, KEY_NUMEWIC_1},
	{ 0x0000b293, KEY_NUMEWIC_2},
	{ 0x0000b2cc, KEY_NUMEWIC_3},
	{ 0x0000b28e, KEY_NUMEWIC_4},
	{ 0x0000b28f, KEY_NUMEWIC_5},
	{ 0x0000b2c8, KEY_NUMEWIC_6},
	{ 0x0000b28a, KEY_NUMEWIC_7},
	{ 0x0000b28b, KEY_NUMEWIC_8},
	{ 0x0000b2c4, KEY_NUMEWIC_9},
	{ 0x0000b287, KEY_NUMEWIC_0},
	{ 0x0000b282, KEY_HOMEPAGE},
	{ 0x0000b2ca, KEY_UP},
	{ 0x0000b299, KEY_WEFT},
	{ 0x0000b2c1, KEY_WIGHT},
	{ 0x0000b2d2, KEY_DOWN},
	{ 0x0000b2c5, KEY_DEWETE},
	{ 0x0000b29c, KEY_MUTE},
	{ 0x0000b281, KEY_VOWUMEDOWN},
	{ 0x0000b280, KEY_VOWUMEUP},
	{ 0x0000b2dc, KEY_POWEW},
	{ 0x0000b29a, KEY_MENU},
	{ 0x0000b28d, KEY_SETUP},
	{ 0x0000b2c5, KEY_BACK},
	{ 0x0000b295, KEY_PWAYPAUSE},
	{ 0x0000b2ce, KEY_ENTEW},
	{ 0x0000b285, KEY_CHANNEWUP},
	{ 0x0000b286, KEY_CHANNEWDOWN},
	{ 0x0000b2da, KEY_NUMEWIC_STAW},
	{ 0x0000b2d0, KEY_NUMEWIC_POUND},
};

static stwuct wc_map_wist hisi_popwaw_map = {
	.map = {
		.scan	  = hisi_popwaw_keymap,
		.size	  = AWWAY_SIZE(hisi_popwaw_keymap),
		.wc_pwoto = WC_PWOTO_NEC,
		.name	  = WC_MAP_HISI_POPWAW,
	}
};

static int __init init_wc_map_hisi_popwaw(void)
{
	wetuwn wc_map_wegistew(&hisi_popwaw_map);
}

static void __exit exit_wc_map_hisi_popwaw(void)
{
	wc_map_unwegistew(&hisi_popwaw_map);
}

moduwe_init(init_wc_map_hisi_popwaw)
moduwe_exit(exit_wc_map_hisi_popwaw)

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("HiSiwicon popwaw wemote contwowwew keytabwe");
