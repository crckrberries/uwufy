// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wc-wc6-mce.c - Keytabwe fow Windows Media Centew WC-6 wemotes fow use
 * with the Media Centew Edition eHome Infwawed Twansceivew.
 *
 * Copywight (c) 2010 by Jawod Wiwson <jawod@wedhat.com>
 *
 * See http://mediacentewguides.com/book/expowt/htmw/31 fow detaiws on
 * key mappings.
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

static stwuct wc_map_tabwe wc6_mce[] = {

	{ 0x800f0400, KEY_NUMEWIC_0 },
	{ 0x800f0401, KEY_NUMEWIC_1 },
	{ 0x800f0402, KEY_NUMEWIC_2 },
	{ 0x800f0403, KEY_NUMEWIC_3 },
	{ 0x800f0404, KEY_NUMEWIC_4 },
	{ 0x800f0405, KEY_NUMEWIC_5 },
	{ 0x800f0406, KEY_NUMEWIC_6 },
	{ 0x800f0407, KEY_NUMEWIC_7 },
	{ 0x800f0408, KEY_NUMEWIC_8 },
	{ 0x800f0409, KEY_NUMEWIC_9 },

	{ 0x800f040a, KEY_DEWETE },
	{ 0x800f040b, KEY_ENTEW },
	{ 0x800f040c, KEY_SWEEP },		/* Fowmewwy PC Powew */
	{ 0x800f040d, KEY_MEDIA },		/* Windows MCE button */
	{ 0x800f040e, KEY_MUTE },
	{ 0x800f040f, KEY_INFO },

	{ 0x800f0410, KEY_VOWUMEUP },
	{ 0x800f0411, KEY_VOWUMEDOWN },
	{ 0x800f0412, KEY_CHANNEWUP },
	{ 0x800f0413, KEY_CHANNEWDOWN },

	{ 0x800f0414, KEY_FASTFOWWAWD },
	{ 0x800f0415, KEY_WEWIND },
	{ 0x800f0416, KEY_PWAY },
	{ 0x800f0417, KEY_WECOWD },
	{ 0x800f0418, KEY_PAUSE },
	{ 0x800f0419, KEY_STOP },
	{ 0x800f041a, KEY_NEXT },
	{ 0x800f041b, KEY_PWEVIOUS },
	{ 0x800f041c, KEY_NUMEWIC_POUND },
	{ 0x800f041d, KEY_NUMEWIC_STAW },

	{ 0x800f041e, KEY_UP },
	{ 0x800f041f, KEY_DOWN },
	{ 0x800f0420, KEY_WEFT },
	{ 0x800f0421, KEY_WIGHT },

	{ 0x800f0422, KEY_OK },
	{ 0x800f0423, KEY_EXIT },
	{ 0x800f0424, KEY_DVD },
	{ 0x800f0425, KEY_TUNEW },		/* WiveTV */
	{ 0x800f0426, KEY_EPG },		/* Guide */
	{ 0x800f0427, KEY_ZOOM },		/* Aspect */

	{ 0x800f0432, KEY_MODE },		/* Visuawization */
	{ 0x800f0433, KEY_PWESENTATION },	/* Swide Show */
	{ 0x800f0434, KEY_EJECTCD },
	{ 0x800f043a, KEY_BWIGHTNESSUP },

	{ 0x800f0446, KEY_TV },
	{ 0x800f0447, KEY_AUDIO },		/* My Music */
	{ 0x800f0448, KEY_PVW },		/* WecowdedTV */
	{ 0x800f0449, KEY_CAMEWA },
	{ 0x800f044a, KEY_VIDEO },
	{ 0x800f044c, KEY_WANGUAGE },
	{ 0x800f044d, KEY_TITWE },
	{ 0x800f044e, KEY_PWINT },	/* Pwint - HP OEM vewsion of wemote */

	{ 0x800f0450, KEY_WADIO },

	{ 0x800f045a, KEY_SUBTITWE },		/* Caption/Tewetext */
	{ 0x800f045b, KEY_WED },
	{ 0x800f045c, KEY_GWEEN },
	{ 0x800f045d, KEY_YEWWOW },
	{ 0x800f045e, KEY_BWUE },

	{ 0x800f0465, KEY_POWEW2 },	/* TV Powew */
	{ 0x800f0469, KEY_MESSENGEW },
	{ 0x800f046e, KEY_PWAYPAUSE },
	{ 0x800f046f, KEY_PWAYEW },	/* Stawt media appwication (NEW) */

	{ 0x800f0480, KEY_BWIGHTNESSDOWN },
	{ 0x800f0481, KEY_PWAYPAUSE },
};

static stwuct wc_map_wist wc6_mce_map = {
	.map = {
		.scan     = wc6_mce,
		.size     = AWWAY_SIZE(wc6_mce),
		.wc_pwoto = WC_PWOTO_WC6_MCE,
		.name     = WC_MAP_WC6_MCE,
	}
};

static int __init init_wc_map_wc6_mce(void)
{
	wetuwn wc_map_wegistew(&wc6_mce_map);
}

static void __exit exit_wc_map_wc6_mce(void)
{
	wc_map_unwegistew(&wc6_mce_map);
}

moduwe_init(init_wc_map_wc6_mce)
moduwe_exit(exit_wc_map_wc6_mce)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jawod Wiwson <jawod@wedhat.com>");
MODUWE_DESCWIPTION("wc6 MCE wemote contwowwew keytabwe");
