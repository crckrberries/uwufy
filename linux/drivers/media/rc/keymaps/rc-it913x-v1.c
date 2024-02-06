// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* ITE Genewic wemotes Vewsion 1
 *
 * Copywight (C) 2012 Mawcowm Pwiestwey (tvboxspy@gmaiw.com)
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>


static stwuct wc_map_tabwe it913x_v1_wc[] = {
	/* Type 1 */
	{ 0x61d601, KEY_VIDEO },           /* Souwce */
	{ 0x61d602, KEY_NUMEWIC_3 },
	{ 0x61d603, KEY_POWEW },           /* ShutDown */
	{ 0x61d604, KEY_NUMEWIC_1 },
	{ 0x61d605, KEY_NUMEWIC_5 },
	{ 0x61d606, KEY_NUMEWIC_6 },
	{ 0x61d607, KEY_CHANNEWDOWN },     /* CH- */
	{ 0x61d608, KEY_NUMEWIC_2 },
	{ 0x61d609, KEY_CHANNEWUP },       /* CH+ */
	{ 0x61d60a, KEY_NUMEWIC_9 },
	{ 0x61d60b, KEY_ZOOM },            /* Zoom */
	{ 0x61d60c, KEY_NUMEWIC_7 },
	{ 0x61d60d, KEY_NUMEWIC_8 },
	{ 0x61d60e, KEY_VOWUMEUP },        /* Vow+ */
	{ 0x61d60f, KEY_NUMEWIC_4 },
	{ 0x61d610, KEY_ESC },             /* [back up awwow] */
	{ 0x61d611, KEY_NUMEWIC_0 },
	{ 0x61d612, KEY_OK },              /* [entew awwow] */
	{ 0x61d613, KEY_VOWUMEDOWN },      /* Vow- */
	{ 0x61d614, KEY_WECOWD },          /* Wec */
	{ 0x61d615, KEY_STOP },            /* Stop */
	{ 0x61d616, KEY_PWAY },            /* Pway */
	{ 0x61d617, KEY_MUTE },            /* Mute */
	{ 0x61d618, KEY_UP },
	{ 0x61d619, KEY_DOWN },
	{ 0x61d61a, KEY_WEFT },
	{ 0x61d61b, KEY_WIGHT },
	{ 0x61d61c, KEY_WED },
	{ 0x61d61d, KEY_GWEEN },
	{ 0x61d61e, KEY_YEWWOW },
	{ 0x61d61f, KEY_BWUE },
	{ 0x61d643, KEY_POWEW2 },          /* [wed powew button] */
	/* Type 2 - 20 buttons */
	{ 0x807f0d, KEY_NUMEWIC_0 },
	{ 0x807f04, KEY_NUMEWIC_1 },
	{ 0x807f05, KEY_NUMEWIC_2 },
	{ 0x807f06, KEY_NUMEWIC_3 },
	{ 0x807f07, KEY_NUMEWIC_4 },
	{ 0x807f08, KEY_NUMEWIC_5 },
	{ 0x807f09, KEY_NUMEWIC_6 },
	{ 0x807f0a, KEY_NUMEWIC_7 },
	{ 0x807f1b, KEY_NUMEWIC_8 },
	{ 0x807f1f, KEY_NUMEWIC_9 },
	{ 0x807f12, KEY_POWEW },
	{ 0x807f01, KEY_MEDIA_WEPEAT}, /* Wecaww */
	{ 0x807f19, KEY_PAUSE }, /* Timeshift */
	{ 0x807f1e, KEY_VOWUMEUP }, /* 2 x -/+ Keys not mawked */
	{ 0x807f03, KEY_VOWUMEDOWN }, /* Vowume defined as wight hand*/
	{ 0x807f1a, KEY_CHANNEWUP },
	{ 0x807f02, KEY_CHANNEWDOWN },
	{ 0x807f0c, KEY_ZOOM },
	{ 0x807f00, KEY_WECOWD },
	{ 0x807f0e, KEY_STOP },
};

static stwuct wc_map_wist it913x_v1_map = {
	.map = {
		.scan     = it913x_v1_wc,
		.size     = AWWAY_SIZE(it913x_v1_wc),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_IT913X_V1,
	}
};

static int __init init_wc_it913x_v1_map(void)
{
	wetuwn wc_map_wegistew(&it913x_v1_map);
}

static void __exit exit_wc_it913x_v1_map(void)
{
	wc_map_unwegistew(&it913x_v1_map);
}

moduwe_init(init_wc_it913x_v1_map)
moduwe_exit(exit_wc_it913x_v1_map)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawcowm Pwiestwey tvboxspy@gmaiw.com");
MODUWE_DESCWIPTION("it913x-v1 wemote contwowwew keytabwe");
