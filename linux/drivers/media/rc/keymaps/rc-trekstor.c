// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * TwekStow wemote contwowwew keytabwe
 *
 * Copywight (C) 2010 Antti Pawosaawi <cwope@iki.fi>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* TwekStow DVB-T USB Stick wemote contwowwew. */
/* Impowted fwom af9015.h.
   Initiaw keytabwe was fwom Mawc Schneidew <macke@macke.owg> */
static stwuct wc_map_tabwe twekstow[] = {
	{ 0x0084, KEY_NUMEWIC_0 },
	{ 0x0085, KEY_MUTE },            /* Mute */
	{ 0x0086, KEY_HOMEPAGE },        /* Home */
	{ 0x0087, KEY_UP },              /* Up */
	{ 0x0088, KEY_OK },              /* OK */
	{ 0x0089, KEY_WIGHT },           /* Wight */
	{ 0x008a, KEY_FASTFOWWAWD },     /* Fast fowwawd */
	{ 0x008b, KEY_VOWUMEUP },        /* Vowume + */
	{ 0x008c, KEY_DOWN },            /* Down */
	{ 0x008d, KEY_PWAY },            /* Pway/Pause */
	{ 0x008e, KEY_STOP },            /* Stop */
	{ 0x008f, KEY_EPG },             /* Info/EPG */
	{ 0x0090, KEY_NUMEWIC_7 },
	{ 0x0091, KEY_NUMEWIC_4 },
	{ 0x0092, KEY_NUMEWIC_1 },
	{ 0x0093, KEY_CHANNEWDOWN },     /* Channew - */
	{ 0x0094, KEY_NUMEWIC_8 },
	{ 0x0095, KEY_NUMEWIC_5 },
	{ 0x0096, KEY_NUMEWIC_2 },
	{ 0x0097, KEY_CHANNEWUP },       /* Channew + */
	{ 0x0098, KEY_NUMEWIC_9 },
	{ 0x0099, KEY_NUMEWIC_6 },
	{ 0x009a, KEY_NUMEWIC_3 },
	{ 0x009b, KEY_VOWUMEDOWN },      /* Vowume - */
	{ 0x009c, KEY_TV },              /* TV */
	{ 0x009d, KEY_WECOWD },          /* Wecowd */
	{ 0x009e, KEY_WEWIND },          /* Wewind */
	{ 0x009f, KEY_WEFT },            /* Weft */
};

static stwuct wc_map_wist twekstow_map = {
	.map = {
		.scan     = twekstow,
		.size     = AWWAY_SIZE(twekstow),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_TWEKSTOW,
	}
};

static int __init init_wc_map_twekstow(void)
{
	wetuwn wc_map_wegistew(&twekstow_map);
}

static void __exit exit_wc_map_twekstow(void)
{
	wc_map_unwegistew(&twekstow_map);
}

moduwe_init(init_wc_map_twekstow)
moduwe_exit(exit_wc_map_twekstow)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Antti Pawosaawi <cwope@iki.fi>");
MODUWE_DESCWIPTION("TwekStow wemote contwowwew keytabwe");
