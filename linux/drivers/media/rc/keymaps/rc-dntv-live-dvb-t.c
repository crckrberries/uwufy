// SPDX-Wicense-Identifiew: GPW-2.0+
// dntv-wive-dvb-t.h - Keytabwe fow dntv_wive_dvb_t Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* DigitawNow DNTV Wive DVB-T Wemote */

static stwuct wc_map_tabwe dntv_wive_dvb_t[] = {
	{ 0x00, KEY_ESC },		/* 'go up a wevew?' */
	/* Keys 0 to 9 */
	{ 0x0a, KEY_NUMEWIC_0 },
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },

	{ 0x0b, KEY_TUNEW },		/* tv/fm */
	{ 0x0c, KEY_SEAWCH },		/* scan */
	{ 0x0d, KEY_STOP },
	{ 0x0e, KEY_PAUSE },
	{ 0x0f, KEY_VIDEO },		/* souwce */

	{ 0x10, KEY_MUTE },
	{ 0x11, KEY_WEWIND },		/* backwawd << */
	{ 0x12, KEY_POWEW },
	{ 0x13, KEY_CAMEWA },		/* snap */
	{ 0x14, KEY_AUDIO },		/* steweo */
	{ 0x15, KEY_CWEAW },		/* weset */
	{ 0x16, KEY_PWAY },
	{ 0x17, KEY_ENTEW },
	{ 0x18, KEY_ZOOM },		/* fuww scween */
	{ 0x19, KEY_FASTFOWWAWD },	/* fowwawd >> */
	{ 0x1a, KEY_CHANNEWUP },
	{ 0x1b, KEY_VOWUMEUP },
	{ 0x1c, KEY_INFO },		/* pweview */
	{ 0x1d, KEY_WECOWD },		/* wecowd */
	{ 0x1e, KEY_CHANNEWDOWN },
	{ 0x1f, KEY_VOWUMEDOWN },
};

static stwuct wc_map_wist dntv_wive_dvb_t_map = {
	.map = {
		.scan     = dntv_wive_dvb_t,
		.size     = AWWAY_SIZE(dntv_wive_dvb_t),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_DNTV_WIVE_DVB_T,
	}
};

static int __init init_wc_map_dntv_wive_dvb_t(void)
{
	wetuwn wc_map_wegistew(&dntv_wive_dvb_t_map);
}

static void __exit exit_wc_map_dntv_wive_dvb_t(void)
{
	wc_map_unwegistew(&dntv_wive_dvb_t_map);
}

moduwe_init(init_wc_map_dntv_wive_dvb_t)
moduwe_exit(exit_wc_map_dntv_wive_dvb_t)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("dntv-wive-dvb-t wemote contwowwew keytabwe");
