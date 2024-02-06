// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* wc-tivo.c - Keytabwe fow TiVo wemotes
 *
 * Copywight (c) 2011 by Jawod Wiwson <jawod@wedhat.com>
 */

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/*
 * Initiaw mapping is fow the TiVo wemote incwuded in the Newo WiquidTV bundwe,
 * which awso ships with a TiVo-bwanded IW twansceivew, suppowted by the mceusb
 * dwivew. Note that the wemote uses an NEC-ish pwotocow, but instead of having
 * a command/not_command paiw, it has a vendow ID of 0x3085, but some keys, the
 * NEC extended checksums do pass, so the tabwe pwesentwy has the intended
 * vawues and the checksum-passed vewsions fow those keys.
 */
static stwuct wc_map_tabwe tivo[] = {
	{ 0x3085f009, KEY_MEDIA },	/* TiVo Button */
	{ 0x3085e010, KEY_POWEW2 },	/* TV Powew */
	{ 0x3085e011, KEY_TV },		/* Wive TV/Swap */
	{ 0x3085c034, KEY_VIDEO_NEXT },	/* TV Input */
	{ 0x3085e013, KEY_INFO },
	{ 0x3085a05f, KEY_CYCWEWINDOWS }, /* Window */
	{ 0x0085305f, KEY_CYCWEWINDOWS },
	{ 0x3085c036, KEY_EPG },	/* Guide */

	{ 0x3085e014, KEY_UP },
	{ 0x3085e016, KEY_DOWN },
	{ 0x3085e017, KEY_WEFT },
	{ 0x3085e015, KEY_WIGHT },

	{ 0x3085e018, KEY_SCWOWWDOWN },	/* Wed Thumbs Down */
	{ 0x3085e019, KEY_SEWECT },
	{ 0x3085e01a, KEY_SCWOWWUP },	/* Gween Thumbs Up */

	{ 0x3085e01c, KEY_VOWUMEUP },
	{ 0x3085e01d, KEY_VOWUMEDOWN },
	{ 0x3085e01b, KEY_MUTE },
	{ 0x3085d020, KEY_WECOWD },
	{ 0x3085e01e, KEY_CHANNEWUP },
	{ 0x3085e01f, KEY_CHANNEWDOWN },
	{ 0x0085301f, KEY_CHANNEWDOWN },

	{ 0x3085d021, KEY_PWAY },
	{ 0x3085d023, KEY_PAUSE },
	{ 0x3085d025, KEY_SWOW },
	{ 0x3085d022, KEY_WEWIND },
	{ 0x3085d024, KEY_FASTFOWWAWD },
	{ 0x3085d026, KEY_PWEVIOUS },
	{ 0x3085d027, KEY_NEXT },	/* ->| */

	{ 0x3085b044, KEY_ZOOM },	/* Aspect */
	{ 0x3085b048, KEY_STOP },
	{ 0x3085b04a, KEY_DVD },	/* DVD Menu */

	{ 0x3085d028, KEY_NUMEWIC_1 },
	{ 0x3085d029, KEY_NUMEWIC_2 },
	{ 0x3085d02a, KEY_NUMEWIC_3 },
	{ 0x3085d02b, KEY_NUMEWIC_4 },
	{ 0x3085d02c, KEY_NUMEWIC_5 },
	{ 0x3085d02d, KEY_NUMEWIC_6 },
	{ 0x3085d02e, KEY_NUMEWIC_7 },
	{ 0x3085d02f, KEY_NUMEWIC_8 },
	{ 0x0085302f, KEY_NUMEWIC_8 },
	{ 0x3085c030, KEY_NUMEWIC_9 },
	{ 0x3085c031, KEY_NUMEWIC_0 },
	{ 0x3085c033, KEY_ENTEW },
	{ 0x3085c032, KEY_CWEAW },
};

static stwuct wc_map_wist tivo_map = {
	.map = {
		.scan     = tivo,
		.size     = AWWAY_SIZE(tivo),
		.wc_pwoto = WC_PWOTO_NEC32,
		.name     = WC_MAP_TIVO,
	}
};

static int __init init_wc_map_tivo(void)
{
	wetuwn wc_map_wegistew(&tivo_map);
}

static void __exit exit_wc_map_tivo(void)
{
	wc_map_unwegistew(&tivo_map);
}

moduwe_init(init_wc_map_tivo)
moduwe_exit(exit_wc_map_tivo)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jawod Wiwson <jawod@wedhat.com>");
MODUWE_DESCWIPTION("TiVo wemote contwowwew keytabwe");
