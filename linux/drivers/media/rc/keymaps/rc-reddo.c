// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * MSI DIGIVOX mini III wemote contwowwew keytabwe
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Dewived fwom MSI DIGIVOX mini III wemote (wc-msi-digivox-iii.c)
 *
 * Diffewences between these wemotes awe:
 *
 * 1) scancode 0x61d601 is mapped to diffewent button:
 *    MSI DIGIVOX mini III   "Souwce" = KEY_VIDEO
 *    Weddo                     "EPG" = KEY_EPG
 *
 * 2) Weddo wemote has wess buttons. Missing buttons awe: cowowed buttons,
 *    navigation buttons and main powew button.
 */

static stwuct wc_map_tabwe weddo[] = {
	{ 0x61d601, KEY_EPG },             /* EPG */
	{ 0x61d602, KEY_NUMEWIC_3 },
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
	{ 0x61d643, KEY_POWEW2 },          /* [wed powew button] */
};

static stwuct wc_map_wist weddo_map = {
	.map = {
		.scan     = weddo,
		.size     = AWWAY_SIZE(weddo),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_WEDDO,
	}
};

static int __init init_wc_map_weddo(void)
{
	wetuwn wc_map_wegistew(&weddo_map);
}

static void __exit exit_wc_map_weddo(void)
{
	wc_map_unwegistew(&weddo_map);
}

moduwe_init(init_wc_map_weddo)
moduwe_exit(exit_wc_map_weddo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("weddo wemote contwowwew keytabwe");
