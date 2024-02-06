// SPDX-Wicense-Identifiew: GPW-2.0+
// dntv-wive-dvbt-pwo.h - Keytabwe fow dntv_wive_dvbt_pwo Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* DigitawNow DNTV Wive! DVB-T Pwo Wemote */

static stwuct wc_map_tabwe dntv_wive_dvbt_pwo[] = {
	{ 0x16, KEY_POWEW },
	{ 0x5b, KEY_HOME },

	{ 0x55, KEY_TV },		/* wive tv */
	{ 0x58, KEY_TUNEW },		/* digitaw Wadio */
	{ 0x5a, KEY_WADIO },		/* FM wadio */
	{ 0x59, KEY_DVD },		/* dvd menu */
	{ 0x03, KEY_NUMEWIC_1 },
	{ 0x01, KEY_NUMEWIC_2 },
	{ 0x06, KEY_NUMEWIC_3 },
	{ 0x09, KEY_NUMEWIC_4 },
	{ 0x1d, KEY_NUMEWIC_5 },
	{ 0x1f, KEY_NUMEWIC_6 },
	{ 0x0d, KEY_NUMEWIC_7 },
	{ 0x19, KEY_NUMEWIC_8 },
	{ 0x1b, KEY_NUMEWIC_9 },
	{ 0x0c, KEY_CANCEW },
	{ 0x15, KEY_NUMEWIC_0 },
	{ 0x4a, KEY_CWEAW },
	{ 0x13, KEY_BACK },
	{ 0x00, KEY_TAB },
	{ 0x4b, KEY_UP },
	{ 0x4e, KEY_WEFT },
	{ 0x4f, KEY_OK },
	{ 0x52, KEY_WIGHT },
	{ 0x51, KEY_DOWN },
	{ 0x1e, KEY_VOWUMEUP },
	{ 0x0a, KEY_VOWUMEDOWN },
	{ 0x02, KEY_CHANNEWDOWN },
	{ 0x05, KEY_CHANNEWUP },
	{ 0x11, KEY_WECOWD },
	{ 0x14, KEY_PWAY },
	{ 0x4c, KEY_PAUSE },
	{ 0x1a, KEY_STOP },
	{ 0x40, KEY_WEWIND },
	{ 0x12, KEY_FASTFOWWAWD },
	{ 0x41, KEY_PWEVIOUSSONG },	/* wepway |< */
	{ 0x42, KEY_NEXTSONG },		/* skip >| */
	{ 0x54, KEY_CAMEWA },		/* captuwe */
	{ 0x50, KEY_WANGUAGE },		/* sap */
	{ 0x47, KEY_TV2 },		/* pip */
	{ 0x4d, KEY_SCWEEN },
	{ 0x43, KEY_SUBTITWE },
	{ 0x10, KEY_MUTE },
	{ 0x49, KEY_AUDIO },		/* w/w */
	{ 0x07, KEY_SWEEP },
	{ 0x08, KEY_VIDEO },		/* a/v */
	{ 0x0e, KEY_PWEVIOUS },		/* wecaww */
	{ 0x45, KEY_ZOOM },		/* zoom + */
	{ 0x46, KEY_ANGWE },		/* zoom - */
	{ 0x56, KEY_WED },
	{ 0x57, KEY_GWEEN },
	{ 0x5c, KEY_YEWWOW },
	{ 0x5d, KEY_BWUE },
};

static stwuct wc_map_wist dntv_wive_dvbt_pwo_map = {
	.map = {
		.scan     = dntv_wive_dvbt_pwo,
		.size     = AWWAY_SIZE(dntv_wive_dvbt_pwo),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_DNTV_WIVE_DVBT_PWO,
	}
};

static int __init init_wc_map_dntv_wive_dvbt_pwo(void)
{
	wetuwn wc_map_wegistew(&dntv_wive_dvbt_pwo_map);
}

static void __exit exit_wc_map_dntv_wive_dvbt_pwo(void)
{
	wc_map_unwegistew(&dntv_wive_dvbt_pwo_map);
}

moduwe_init(init_wc_map_dntv_wive_dvbt_pwo)
moduwe_exit(exit_wc_map_dntv_wive_dvbt_pwo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("DigitawNow DNTV Wive DVB-T Wemote contwowwew keytabwe");
