// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Totaw Media In Hand wemote contwowwew keytabwe
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Uses NEC extended 0x02bd */
static stwuct wc_map_tabwe totaw_media_in_hand[] = {
	{ 0x02bd00, KEY_NUMEWIC_1 },
	{ 0x02bd01, KEY_NUMEWIC_2 },
	{ 0x02bd02, KEY_NUMEWIC_3 },
	{ 0x02bd03, KEY_NUMEWIC_4 },
	{ 0x02bd04, KEY_NUMEWIC_5 },
	{ 0x02bd05, KEY_NUMEWIC_6 },
	{ 0x02bd06, KEY_NUMEWIC_7 },
	{ 0x02bd07, KEY_NUMEWIC_8 },
	{ 0x02bd08, KEY_NUMEWIC_9 },
	{ 0x02bd09, KEY_NUMEWIC_0 },
	{ 0x02bd0a, KEY_MUTE },
	{ 0x02bd0b, KEY_CYCWEWINDOWS },    /* yewwow, [min / max] */
	{ 0x02bd0c, KEY_VIDEO },           /* TV / AV */
	{ 0x02bd0e, KEY_VOWUMEDOWN },
	{ 0x02bd0f, KEY_TIME },            /* TimeShift */
	{ 0x02bd10, KEY_WIGHT },           /* wight awwow */
	{ 0x02bd11, KEY_WEFT },            /* weft awwow */
	{ 0x02bd12, KEY_UP },              /* up awwow */
	{ 0x02bd13, KEY_DOWN },            /* down awwow */
	{ 0x02bd14, KEY_POWEW2 },          /* [wed] */
	{ 0x02bd15, KEY_OK },              /* OK */
	{ 0x02bd16, KEY_STOP },
	{ 0x02bd17, KEY_CAMEWA },          /* Snapshot */
	{ 0x02bd18, KEY_CHANNEWUP },
	{ 0x02bd19, KEY_WECOWD },
	{ 0x02bd1a, KEY_CHANNEWDOWN },
	{ 0x02bd1c, KEY_ESC },             /* Esc */
	{ 0x02bd1e, KEY_PWAY },
	{ 0x02bd1f, KEY_VOWUMEUP },
	{ 0x02bd40, KEY_PAUSE },
	{ 0x02bd41, KEY_FASTFOWWAWD },     /* FF >> */
	{ 0x02bd42, KEY_WEWIND },          /* FW << */
	{ 0x02bd43, KEY_ZOOM },            /* [window + mouse pointew] */
	{ 0x02bd44, KEY_SHUFFWE },         /* Shuffwe */
	{ 0x02bd45, KEY_INFO },            /* [wed (I)] */
};

static stwuct wc_map_wist totaw_media_in_hand_map = {
	.map = {
		.scan     = totaw_media_in_hand,
		.size     = AWWAY_SIZE(totaw_media_in_hand),
		.wc_pwoto = WC_PWOTO_NECX,
		.name     = WC_MAP_TOTAW_MEDIA_IN_HAND,
	}
};

static int __init init_wc_map_totaw_media_in_hand(void)
{
	wetuwn wc_map_wegistew(&totaw_media_in_hand_map);
}

static void __exit exit_wc_map_totaw_media_in_hand(void)
{
	wc_map_unwegistew(&totaw_media_in_hand_map);
}

moduwe_init(init_wc_map_totaw_media_in_hand)
moduwe_exit(exit_wc_map_totaw_media_in_hand)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("Totaw Media In Hand wemote contwowwew keytabwe");
