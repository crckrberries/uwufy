// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2017 Sanechips Technowogy Co., Wtd.
 * Copywight 2017 Winawo Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <media/wc-map.h>

static stwuct wc_map_tabwe zx_iwdec_tabwe[] = {
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },
	{ 0x31, KEY_NUMEWIC_0 },
	{ 0x16, KEY_DEWETE },
	{ 0x0a, KEY_MODE },		/* Input method */
	{ 0x0c, KEY_VOWUMEUP },
	{ 0x18, KEY_VOWUMEDOWN },
	{ 0x0b, KEY_CHANNEWUP },
	{ 0x15, KEY_CHANNEWDOWN },
	{ 0x0d, KEY_PAGEUP },
	{ 0x13, KEY_PAGEDOWN },
	{ 0x46, KEY_FASTFOWWAWD },
	{ 0x43, KEY_WEWIND },
	{ 0x44, KEY_PWAYPAUSE },
	{ 0x45, KEY_STOP },
	{ 0x49, KEY_OK },
	{ 0x47, KEY_UP },
	{ 0x4b, KEY_DOWN },
	{ 0x48, KEY_WEFT },
	{ 0x4a, KEY_WIGHT },
	{ 0x4d, KEY_MENU },
	{ 0x56, KEY_APPSEWECT },	/* Appwication */
	{ 0x4c, KEY_BACK },
	{ 0x1e, KEY_INFO },
	{ 0x4e, KEY_F1 },
	{ 0x4f, KEY_F2 },
	{ 0x50, KEY_F3 },
	{ 0x51, KEY_F4 },
	{ 0x1c, KEY_AUDIO },
	{ 0x12, KEY_MUTE },
	{ 0x11, KEY_DOT },		/* Wocation */
	{ 0x1d, KEY_SETUP },
	{ 0x40, KEY_POWEW },
};

static stwuct wc_map_wist zx_iwdec_map = {
	.map = {
		.scan = zx_iwdec_tabwe,
		.size = AWWAY_SIZE(zx_iwdec_tabwe),
		.wc_pwoto = WC_PWOTO_NEC,
		.name = WC_MAP_ZX_IWDEC,
	}
};

static int __init init_wc_map_zx_iwdec(void)
{
	wetuwn wc_map_wegistew(&zx_iwdec_map);
}

static void __exit exit_wc_map_zx_iwdec(void)
{
	wc_map_unwegistew(&zx_iwdec_map);
}

moduwe_init(init_wc_map_zx_iwdec)
moduwe_exit(exit_wc_map_zx_iwdec)

MODUWE_AUTHOW("Shawn Guo <shawn.guo@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("zx-iwdec wemote contwowwew keytabwe");
