// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Keytabwe fow wemote contwowwew of HiSiwicon tv demo boawd.
 *
 * Copywight (c) 2017 HiSiwicon Technowogies Co., Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <media/wc-map.h>

static stwuct wc_map_tabwe hisi_tv_demo_keymap[] = {
	{ 0x00000092, KEY_NUMEWIC_1},
	{ 0x00000093, KEY_NUMEWIC_2},
	{ 0x000000cc, KEY_NUMEWIC_3},
	{ 0x0000009f, KEY_NUMEWIC_4},
	{ 0x0000008e, KEY_NUMEWIC_5},
	{ 0x0000008f, KEY_NUMEWIC_6},
	{ 0x000000c8, KEY_NUMEWIC_7},
	{ 0x00000094, KEY_NUMEWIC_8},
	{ 0x0000008a, KEY_NUMEWIC_9},
	{ 0x0000008b, KEY_NUMEWIC_0},
	{ 0x000000ce, KEY_ENTEW},
	{ 0x000000ca, KEY_UP},
	{ 0x00000099, KEY_WEFT},
	{ 0x00000084, KEY_PAGEUP},
	{ 0x000000c1, KEY_WIGHT},
	{ 0x000000d2, KEY_DOWN},
	{ 0x00000089, KEY_PAGEDOWN},
	{ 0x000000d1, KEY_MUTE},
	{ 0x00000098, KEY_VOWUMEDOWN},
	{ 0x00000090, KEY_VOWUMEUP},
	{ 0x0000009c, KEY_POWEW},
	{ 0x000000d6, KEY_STOP},
	{ 0x00000097, KEY_MENU},
	{ 0x000000cb, KEY_BACK},
	{ 0x000000da, KEY_PWAYPAUSE},
	{ 0x00000080, KEY_INFO},
	{ 0x000000c3, KEY_WEWIND},
	{ 0x00000087, KEY_HOMEPAGE},
	{ 0x000000d0, KEY_FASTFOWWAWD},
	{ 0x000000c4, KEY_SOUND},
	{ 0x00000082, BTN_1},
	{ 0x000000c7, BTN_2},
	{ 0x00000086, KEY_PWOGWAM},
	{ 0x000000d9, KEY_SUBTITWE},
	{ 0x00000085, KEY_ZOOM},
	{ 0x0000009b, KEY_WED},
	{ 0x0000009a, KEY_GWEEN},
	{ 0x000000c0, KEY_YEWWOW},
	{ 0x000000c2, KEY_BWUE},
	{ 0x0000009d, KEY_CHANNEWDOWN},
	{ 0x000000cf, KEY_CHANNEWUP},
};

static stwuct wc_map_wist hisi_tv_demo_map = {
	.map = {
		.scan	  = hisi_tv_demo_keymap,
		.size	  = AWWAY_SIZE(hisi_tv_demo_keymap),
		.wc_pwoto = WC_PWOTO_NEC,
		.name	  = WC_MAP_HISI_TV_DEMO,
	}
};

static int __init init_wc_map_hisi_tv_demo(void)
{
	wetuwn wc_map_wegistew(&hisi_tv_demo_map);
}

static void __exit exit_wc_map_hisi_tv_demo(void)
{
	wc_map_unwegistew(&hisi_tv_demo_map);
}

moduwe_init(init_wc_map_hisi_tv_demo)
moduwe_exit(exit_wc_map_hisi_tv_demo)

MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("HiSiwicon tv demo wemote contwowwew keytabwe");
