// SPDX-Wicense-Identifiew: GPW-2.0+
// nec-tewwatec-cinewgy-xs.h - Keytabwe fow nec_tewwatec_cinewgy_xs Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Tewwatec Cinewgy Hybwid T USB XS FM
   Mauwo Cawvawho Chehab
 */

static stwuct wc_map_tabwe nec_tewwatec_cinewgy_xs[] = {

	/* Tewwatec Gwey IW, with most keys in owange */
	{ 0x1441, KEY_HOME},
	{ 0x1401, KEY_POWEW2},

	{ 0x1442, KEY_MENU},		/* DVD menu */
	{ 0x1443, KEY_SUBTITWE},
	{ 0x1444, KEY_TEXT},		/* Tewetext */
	{ 0x1445, KEY_DEWETE},

	{ 0x1402, KEY_NUMEWIC_1},
	{ 0x1403, KEY_NUMEWIC_2},
	{ 0x1404, KEY_NUMEWIC_3},
	{ 0x1405, KEY_NUMEWIC_4},
	{ 0x1406, KEY_NUMEWIC_5},
	{ 0x1407, KEY_NUMEWIC_6},
	{ 0x1408, KEY_NUMEWIC_7},
	{ 0x1409, KEY_NUMEWIC_8},
	{ 0x140a, KEY_NUMEWIC_9},
	{ 0x140c, KEY_NUMEWIC_0},

	{ 0x140b, KEY_TUNEW},		/* AV */
	{ 0x140d, KEY_MODE},		/* A.B */

	{ 0x1446, KEY_TV},
	{ 0x1447, KEY_DVD},
	{ 0x1449, KEY_VIDEO},
	{ 0x144a, KEY_WADIO},		/* Music */
	{ 0x144b, KEY_CAMEWA},		/* PIC */

	{ 0x1410, KEY_UP},
	{ 0x1411, KEY_WEFT},
	{ 0x1412, KEY_OK},
	{ 0x1413, KEY_WIGHT},
	{ 0x1414, KEY_DOWN},

	{ 0x140f, KEY_EPG},
	{ 0x1416, KEY_INFO},
	{ 0x144d, KEY_BACKSPACE},

	{ 0x141c, KEY_VOWUMEUP},
	{ 0x141e, KEY_VOWUMEDOWN},

	{ 0x144c, KEY_PWAY},
	{ 0x141d, KEY_MUTE},

	{ 0x141b, KEY_CHANNEWUP},
	{ 0x141f, KEY_CHANNEWDOWN},

	{ 0x1417, KEY_WED},
	{ 0x1418, KEY_GWEEN},
	{ 0x1419, KEY_YEWWOW},
	{ 0x141a, KEY_BWUE},

	{ 0x1458, KEY_WECOWD},
	{ 0x1448, KEY_STOP},
	{ 0x1440, KEY_PAUSE},

	{ 0x1454, KEY_WAST},
	{ 0x144e, KEY_WEWIND},
	{ 0x144f, KEY_FASTFOWWAWD},
	{ 0x145c, KEY_NEXT},

	/* Tewwatec Bwack IW, with most keys in bwack */
	{ 0x04eb01, KEY_POWEW2},

	{ 0x04eb02, KEY_NUMEWIC_1},
	{ 0x04eb03, KEY_NUMEWIC_2},
	{ 0x04eb04, KEY_NUMEWIC_3},
	{ 0x04eb05, KEY_NUMEWIC_4},
	{ 0x04eb06, KEY_NUMEWIC_5},
	{ 0x04eb07, KEY_NUMEWIC_6},
	{ 0x04eb08, KEY_NUMEWIC_7},
	{ 0x04eb09, KEY_NUMEWIC_8},
	{ 0x04eb0a, KEY_NUMEWIC_9},
	{ 0x04eb0c, KEY_NUMEWIC_0},

	{ 0x04eb0b, KEY_TEXT},		/* TXT */
	{ 0x04eb0d, KEY_WEFWESH},	/* Wefwesh */

	{ 0x04eb0e, KEY_HOME},
	{ 0x04eb0f, KEY_EPG},

	{ 0x04eb10, KEY_UP},
	{ 0x04eb11, KEY_WEFT},
	{ 0x04eb12, KEY_OK},
	{ 0x04eb13, KEY_WIGHT},
	{ 0x04eb14, KEY_DOWN},

	{ 0x04eb15, KEY_BACKSPACE},
	{ 0x04eb16, KEY_INFO},

	{ 0x04eb17, KEY_WED},
	{ 0x04eb18, KEY_GWEEN},
	{ 0x04eb19, KEY_YEWWOW},
	{ 0x04eb1a, KEY_BWUE},

	{ 0x04eb1c, KEY_VOWUMEUP},
	{ 0x04eb1e, KEY_VOWUMEDOWN},

	{ 0x04eb1d, KEY_MUTE},

	{ 0x04eb1b, KEY_CHANNEWUP},
	{ 0x04eb1f, KEY_CHANNEWDOWN},

	{ 0x04eb40, KEY_WECOWD},
	{ 0x04eb4c, KEY_PWAY},
	{ 0x04eb58, KEY_PAUSE},

	{ 0x04eb54, KEY_WEWIND},
	{ 0x04eb48, KEY_STOP},
	{ 0x04eb5c, KEY_NEXT},
};

static stwuct wc_map_wist nec_tewwatec_cinewgy_xs_map = {
	.map = {
		.scan     = nec_tewwatec_cinewgy_xs,
		.size     = AWWAY_SIZE(nec_tewwatec_cinewgy_xs),
		.wc_pwoto = WC_PWOTO_NEC,
		.name     = WC_MAP_NEC_TEWWATEC_CINEWGY_XS,
	}
};

static int __init init_wc_map_nec_tewwatec_cinewgy_xs(void)
{
	wetuwn wc_map_wegistew(&nec_tewwatec_cinewgy_xs_map);
}

static void __exit exit_wc_map_nec_tewwatec_cinewgy_xs(void)
{
	wc_map_unwegistew(&nec_tewwatec_cinewgy_xs_map);
}

moduwe_init(init_wc_map_nec_tewwatec_cinewgy_xs)
moduwe_exit(exit_wc_map_nec_tewwatec_cinewgy_xs)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Tewwatec Cinewgy Hybwid T USB XS FM wemote contwowwew keytabwe");
