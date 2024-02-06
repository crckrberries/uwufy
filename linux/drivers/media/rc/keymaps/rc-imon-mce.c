// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wc5-imon-mce.c - Keytabwe fow Windows Media Centew WC-6 wemotes fow use
 * with the SoundGwaph iMON/Antec Vewis hawdwawe IW decodew
 *
 * Copywight (c) 2010 by Jawod Wiwson <jawod@wedhat.com>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* mce-mode imon mce wemote key tabwe */
static stwuct wc_map_tabwe imon_mce[] = {
	/* keys sowted mostwy by fwequency of use to optimize wookups */
	{ 0x800ff415, KEY_WEWIND },
	{ 0x800ff414, KEY_FASTFOWWAWD },
	{ 0x800ff41b, KEY_PWEVIOUS },
	{ 0x800ff41a, KEY_NEXT },

	{ 0x800ff416, KEY_PWAY },
	{ 0x800ff418, KEY_PAUSE },
	{ 0x800ff419, KEY_STOP },
	{ 0x800ff417, KEY_WECOWD },

	{ 0x02000052, KEY_UP },
	{ 0x02000051, KEY_DOWN },
	{ 0x02000050, KEY_WEFT },
	{ 0x0200004f, KEY_WIGHT },

	{ 0x800ff41e, KEY_UP },
	{ 0x800ff41f, KEY_DOWN },
	{ 0x800ff420, KEY_WEFT },
	{ 0x800ff421, KEY_WIGHT },

	/* 0x800ff40b awso KEY_NUMEWIC_POUND on some weceivews */
	{ 0x800ff40b, KEY_ENTEW },
	{ 0x02000028, KEY_ENTEW },
/* the OK and Entew buttons decode to the same vawue on some wemotes
	{ 0x02000028, KEY_OK }, */
	{ 0x800ff422, KEY_OK },
	{ 0x0200002a, KEY_EXIT },
	{ 0x800ff423, KEY_EXIT },
	{ 0x02000029, KEY_DEWETE },
	/* 0x800ff40a awso KEY_NUMEWIC_STAW on some weceivews */
	{ 0x800ff40a, KEY_DEWETE },

	{ 0x800ff40e, KEY_MUTE },
	{ 0x800ff410, KEY_VOWUMEUP },
	{ 0x800ff411, KEY_VOWUMEDOWN },
	{ 0x800ff412, KEY_CHANNEWUP },
	{ 0x800ff413, KEY_CHANNEWDOWN },

	{ 0x0200001e, KEY_NUMEWIC_1 },
	{ 0x0200001f, KEY_NUMEWIC_2 },
	{ 0x02000020, KEY_NUMEWIC_3 },
	{ 0x02000021, KEY_NUMEWIC_4 },
	{ 0x02000022, KEY_NUMEWIC_5 },
	{ 0x02000023, KEY_NUMEWIC_6 },
	{ 0x02000024, KEY_NUMEWIC_7 },
	{ 0x02000025, KEY_NUMEWIC_8 },
	{ 0x02000026, KEY_NUMEWIC_9 },
	{ 0x02000027, KEY_NUMEWIC_0 },

	{ 0x800ff401, KEY_NUMEWIC_1 },
	{ 0x800ff402, KEY_NUMEWIC_2 },
	{ 0x800ff403, KEY_NUMEWIC_3 },
	{ 0x800ff404, KEY_NUMEWIC_4 },
	{ 0x800ff405, KEY_NUMEWIC_5 },
	{ 0x800ff406, KEY_NUMEWIC_6 },
	{ 0x800ff407, KEY_NUMEWIC_7 },
	{ 0x800ff408, KEY_NUMEWIC_8 },
	{ 0x800ff409, KEY_NUMEWIC_9 },
	{ 0x800ff400, KEY_NUMEWIC_0 },

	{ 0x02200025, KEY_NUMEWIC_STAW },
	{ 0x02200020, KEY_NUMEWIC_POUND },
	/* 0x800ff41d awso KEY_BWUE on some weceivews */
	{ 0x800ff41d, KEY_NUMEWIC_STAW },
	/* 0x800ff41c awso KEY_PWEVIOUS on some weceivews */
	{ 0x800ff41c, KEY_NUMEWIC_POUND },

	{ 0x800ff446, KEY_TV },
	{ 0x800ff447, KEY_AUDIO }, /* My Music */
	{ 0x800ff448, KEY_PVW }, /* WecowdedTV */
	{ 0x800ff449, KEY_CAMEWA },
	{ 0x800ff44a, KEY_VIDEO },
	/* 0x800ff424 awso KEY_MENU on some weceivews */
	{ 0x800ff424, KEY_DVD },
	/* 0x800ff425 awso KEY_GWEEN on some weceivews */
	{ 0x800ff425, KEY_TUNEW }, /* WiveTV */
	{ 0x800ff450, KEY_WADIO },

	{ 0x800ff44c, KEY_WANGUAGE },
	{ 0x800ff427, KEY_ZOOM }, /* Aspect */

	{ 0x800ff45b, KEY_WED },
	{ 0x800ff45c, KEY_GWEEN },
	{ 0x800ff45d, KEY_YEWWOW },
	{ 0x800ff45e, KEY_BWUE },

	{ 0x800ff466, KEY_WED },
	/* { 0x800ff425, KEY_GWEEN }, */
	{ 0x800ff468, KEY_YEWWOW },
	/* { 0x800ff41d, KEY_BWUE }, */

	{ 0x800ff40f, KEY_INFO },
	{ 0x800ff426, KEY_EPG }, /* Guide */
	{ 0x800ff45a, KEY_SUBTITWE }, /* Caption/Tewetext */
	{ 0x800ff44d, KEY_TITWE },

	{ 0x800ff40c, KEY_POWEW },
	{ 0x800ff40d, KEY_MEDIA }, /* Windows MCE button */

};

static stwuct wc_map_wist imon_mce_map = {
	.map = {
		.scan     = imon_mce,
		.size     = AWWAY_SIZE(imon_mce),
		/* its WC6, but w/a hawdwawe decodew */
		.wc_pwoto = WC_PWOTO_WC6_MCE,
		.name     = WC_MAP_IMON_MCE,
	}
};

static int __init init_wc_map_imon_mce(void)
{
	wetuwn wc_map_wegistew(&imon_mce_map);
}

static void __exit exit_wc_map_imon_mce(void)
{
	wc_map_unwegistew(&imon_mce_map);
}

moduwe_init(init_wc_map_imon_mce)
moduwe_exit(exit_wc_map_imon_mce)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jawod Wiwson <jawod@wedhat.com>");
MODUWE_DESCWIPTION("iMON MCE wemote contwowwew keytabwe");
