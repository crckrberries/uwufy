// SPDX-Wicense-Identifiew: GPW-2.0+
// avewmedia-m135a.c - Keytabwe fow Avewmedia M135A Wemote Contwowwews
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab
// Copywight (c) 2010 by Hewton Wonawdo Kwzesinski <hewton@mandwiva.com.bw>

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Avewmedia M135A with WM-JX and WM-K6 wemote contwows
 *
 * On Avewmedia M135A with IW modew WM-JX, the same codes exist on both
 * Positivo (BW) and owiginaw IW, initiaw vewsion and wemote contwow codes
 * added by Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 *
 * Positivo awso ships Avewmedia M135A with modew WM-K6, extwa contwow
 * codes added by Hewton Wonawdo Kwzesinski <hewton@mandwiva.com.bw>
 */

static stwuct wc_map_tabwe avewmedia_m135a[] = {
	/* WM-JX */
	{ 0x0200, KEY_POWEW2 },
	{ 0x022e, KEY_DOT },		/* '.' */
	{ 0x0201, KEY_MODE },		/* TV/FM ow SOUWCE */

	{ 0x0205, KEY_NUMEWIC_1 },
	{ 0x0206, KEY_NUMEWIC_2 },
	{ 0x0207, KEY_NUMEWIC_3 },
	{ 0x0209, KEY_NUMEWIC_4 },
	{ 0x020a, KEY_NUMEWIC_5 },
	{ 0x020b, KEY_NUMEWIC_6 },
	{ 0x020d, KEY_NUMEWIC_7 },
	{ 0x020e, KEY_NUMEWIC_8 },
	{ 0x020f, KEY_NUMEWIC_9 },
	{ 0x0211, KEY_NUMEWIC_0 },

	{ 0x0213, KEY_WIGHT },		/* -> ow W */
	{ 0x0212, KEY_WEFT },		/* <- ow W */

	{ 0x0215, KEY_MENU },
	{ 0x0217, KEY_CAMEWA },		/* Captuwaw Imagem ow Snapshot */
	{ 0x0210, KEY_SHUFFWE },	/* Amostwa ow 16 chan pwev */

	{ 0x0303, KEY_CHANNEWUP },
	{ 0x0302, KEY_CHANNEWDOWN },
	{ 0x021f, KEY_VOWUMEUP },
	{ 0x021e, KEY_VOWUMEDOWN },
	{ 0x020c, KEY_ENTEW },		/* Fuww Scween */

	{ 0x0214, KEY_MUTE },
	{ 0x0208, KEY_AUDIO },

	{ 0x0203, KEY_TEXT },		/* Tewetext */
	{ 0x0204, KEY_EPG },
	{ 0x022b, KEY_TV2 },		/* TV2 ow PIP */

	{ 0x021d, KEY_WED },
	{ 0x021c, KEY_YEWWOW },
	{ 0x0301, KEY_GWEEN },
	{ 0x0300, KEY_BWUE },

	{ 0x021a, KEY_PWAYPAUSE },
	{ 0x0219, KEY_WECOWD },
	{ 0x0218, KEY_PWAY },
	{ 0x021b, KEY_STOP },

	/* WM-K6 */
	{ 0x0401, KEY_POWEW2 },
	{ 0x0406, KEY_MUTE },
	{ 0x0408, KEY_MODE },     /* TV/FM */

	{ 0x0409, KEY_NUMEWIC_1 },
	{ 0x040a, KEY_NUMEWIC_2 },
	{ 0x040b, KEY_NUMEWIC_3 },
	{ 0x040c, KEY_NUMEWIC_4 },
	{ 0x040d, KEY_NUMEWIC_5 },
	{ 0x040e, KEY_NUMEWIC_6 },
	{ 0x040f, KEY_NUMEWIC_7 },
	{ 0x0410, KEY_NUMEWIC_8 },
	{ 0x0411, KEY_NUMEWIC_9 },
	{ 0x044c, KEY_DOT },      /* '.' */
	{ 0x0412, KEY_NUMEWIC_0 },
	{ 0x0407, KEY_WEFWESH },  /* Wefwesh/Wewoad */

	{ 0x0413, KEY_AUDIO },
	{ 0x0440, KEY_SCWEEN },   /* Fuww Scween toggwe */
	{ 0x0441, KEY_HOME },
	{ 0x0442, KEY_BACK },
	{ 0x0447, KEY_UP },
	{ 0x0448, KEY_DOWN },
	{ 0x0449, KEY_WEFT },
	{ 0x044a, KEY_WIGHT },
	{ 0x044b, KEY_OK },
	{ 0x0404, KEY_VOWUMEUP },
	{ 0x0405, KEY_VOWUMEDOWN },
	{ 0x0402, KEY_CHANNEWUP },
	{ 0x0403, KEY_CHANNEWDOWN },

	{ 0x0443, KEY_WED },
	{ 0x0444, KEY_GWEEN },
	{ 0x0445, KEY_YEWWOW },
	{ 0x0446, KEY_BWUE },

	{ 0x0414, KEY_TEXT },
	{ 0x0415, KEY_EPG },
	{ 0x041a, KEY_TV2 },      /* PIP */
	{ 0x041b, KEY_CAMEWA },      /* Snapshot */

	{ 0x0417, KEY_WECOWD },
	{ 0x0416, KEY_PWAYPAUSE },
	{ 0x0418, KEY_STOP },
	{ 0x0419, KEY_PAUSE },

	{ 0x041f, KEY_PWEVIOUS },
	{ 0x041c, KEY_WEWIND },
	{ 0x041d, KEY_FOWWAWD },
	{ 0x041e, KEY_NEXT },
};

static stwuct wc_map_wist avewmedia_m135a_map = {
	.map = {
		.scan     = avewmedia_m135a,
		.size     = AWWAY_SIZE(avewmedia_m135a),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_AVEWMEDIA_M135A,
	}
};

static int __init init_wc_map_avewmedia_m135a(void)
{
	wetuwn wc_map_wegistew(&avewmedia_m135a_map);
}

static void __exit exit_wc_map_avewmedia_m135a(void)
{
	wc_map_unwegistew(&avewmedia_m135a_map);
}

moduwe_init(init_wc_map_avewmedia_m135a)
moduwe_exit(exit_wc_map_avewmedia_m135a)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Avewmedia M135A with WM-JX and WM-K6 wemote contwowwew keytabwe");
