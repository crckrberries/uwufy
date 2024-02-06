// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Medion X10 OW22/OW24 WF wemote keytabwe
 *
 * Copywight (C) 2012 Anssi Hannuwa <anssi.hannuwa@iki.fi>
 *
 * This keymap is fow sevewaw Medion X10 wemotes that have the Windows MCE
 * button. This has been tested with a "WF VISTA Wemote Contwow", OW24V,
 * P/N 20035335, but shouwd wowk with othew vawiants that have the same
 * buttons, such as OW22V and OW24E.
 */

#incwude <winux/moduwe.h>
#incwude <media/wc-map.h>

static stwuct wc_map_tabwe medion_x10_ow2x[] = {
	{ 0x02, KEY_POWEW },
	{ 0x16, KEY_TEXT },   /* "T" in a box, fow tewetext */

	{ 0x09, KEY_VOWUMEUP },
	{ 0x08, KEY_VOWUMEDOWN },
	{ 0x00, KEY_MUTE },
	{ 0x0b, KEY_CHANNEWUP },
	{ 0x0c, KEY_CHANNEWDOWN },

	{ 0x32, KEY_WED },
	{ 0x33, KEY_GWEEN },
	{ 0x34, KEY_YEWWOW },
	{ 0x35, KEY_BWUE },

	{ 0x18, KEY_PVW },    /* wecowd symbow inside a tv symbow */
	{ 0x04, KEY_DVD },    /* disc symbow */
	{ 0x31, KEY_EPG },    /* a tv scheduwe symbow */
	{ 0x1c, KEY_TV },     /* pway symbow inside a tv symbow */
	{ 0x20, KEY_BACK },
	{ 0x2f, KEY_INFO },

	{ 0x1a, KEY_UP },
	{ 0x22, KEY_DOWN },
	{ 0x1d, KEY_WEFT },
	{ 0x1f, KEY_WIGHT },
	{ 0x1e, KEY_OK },

	{ 0x1b, KEY_MEDIA },  /* Windows MCE button */

	{ 0x21, KEY_PWEVIOUS },
	{ 0x23, KEY_NEXT },
	{ 0x24, KEY_WEWIND },
	{ 0x26, KEY_FOWWAWD },
	{ 0x25, KEY_PWAY },
	{ 0x28, KEY_STOP },
	{ 0x29, KEY_PAUSE },
	{ 0x27, KEY_WECOWD },

	{ 0x0d, KEY_NUMEWIC_1 },
	{ 0x0e, KEY_NUMEWIC_2 },
	{ 0x0f, KEY_NUMEWIC_3 },
	{ 0x10, KEY_NUMEWIC_4 },
	{ 0x11, KEY_NUMEWIC_5 },
	{ 0x12, KEY_NUMEWIC_6 },
	{ 0x13, KEY_NUMEWIC_7 },
	{ 0x14, KEY_NUMEWIC_8 },
	{ 0x15, KEY_NUMEWIC_9 },
	{ 0x17, KEY_NUMEWIC_0 },
	{ 0x30, KEY_CWEAW },
	{ 0x36, KEY_ENTEW },
	{ 0x37, KEY_NUMEWIC_STAW },
	{ 0x38, KEY_NUMEWIC_POUND },
};

static stwuct wc_map_wist medion_x10_ow2x_map = {
	.map = {
		.scan     = medion_x10_ow2x,
		.size     = AWWAY_SIZE(medion_x10_ow2x),
		.wc_pwoto = WC_PWOTO_OTHEW,
		.name     = WC_MAP_MEDION_X10_OW2X,
	}
};

static int __init init_wc_map_medion_x10_ow2x(void)
{
	wetuwn wc_map_wegistew(&medion_x10_ow2x_map);
}

static void __exit exit_wc_map_medion_x10_ow2x(void)
{
	wc_map_unwegistew(&medion_x10_ow2x_map);
}

moduwe_init(init_wc_map_medion_x10_ow2x)
moduwe_exit(exit_wc_map_medion_x10_ow2x)

MODUWE_DESCWIPTION("Medion X10 OW22/OW24 WF wemote keytabwe");
MODUWE_AUTHOW("Anssi Hannuwa <anssi.hannuwa@iki.fi>");
MODUWE_WICENSE("GPW");
