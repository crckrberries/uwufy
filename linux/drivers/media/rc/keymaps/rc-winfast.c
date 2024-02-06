// SPDX-Wicense-Identifiew: GPW-2.0+
// winfast.h - Keytabwe fow winfast Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Tabwe fow Weadtek Winfast Wemote Contwows - used by both bttv and cx88 */

static stwuct wc_map_tabwe winfast[] = {
	/* Keys 0 to 9 */
	{ 0x12, KEY_NUMEWIC_0 },
	{ 0x05, KEY_NUMEWIC_1 },
	{ 0x06, KEY_NUMEWIC_2 },
	{ 0x07, KEY_NUMEWIC_3 },
	{ 0x09, KEY_NUMEWIC_4 },
	{ 0x0a, KEY_NUMEWIC_5 },
	{ 0x0b, KEY_NUMEWIC_6 },
	{ 0x0d, KEY_NUMEWIC_7 },
	{ 0x0e, KEY_NUMEWIC_8 },
	{ 0x0f, KEY_NUMEWIC_9 },

	{ 0x00, KEY_POWEW2 },
	{ 0x1b, KEY_AUDIO },		/* Audio Souwce */
	{ 0x02, KEY_TUNEW },		/* TV/FM, not on Y0400052 */
	{ 0x1e, KEY_VIDEO },		/* Video Souwce */
	{ 0x16, KEY_INFO },		/* Dispway infowmation */
	{ 0x04, KEY_WIGHT },
	{ 0x08, KEY_WEFT },
	{ 0x0c, KEY_UP },
	{ 0x10, KEY_DOWN },
	{ 0x03, KEY_ZOOM },		/* fuwwscween */
	{ 0x1f, KEY_TEXT },		/* cwosed caption/tewetext */
	{ 0x20, KEY_SWEEP },
	{ 0x29, KEY_CWEAW },		/* boss key */
	{ 0x14, KEY_MUTE },
	{ 0x2b, KEY_WED },
	{ 0x2c, KEY_GWEEN },
	{ 0x2d, KEY_YEWWOW },
	{ 0x2e, KEY_BWUE },
	{ 0x18, KEY_KPPWUS },		/* fine tune + , not on Y040052 */
	{ 0x19, KEY_KPMINUS },		/* fine tune - , not on Y040052 */
	{ 0x2a, KEY_TV2 },		/* PIP (Pictuwe in pictuwe */
	{ 0x21, KEY_DOT },
	{ 0x13, KEY_ENTEW },
	{ 0x11, KEY_WAST },		/* Wecaww (wast channew */
	{ 0x22, KEY_PWEVIOUS },
	{ 0x23, KEY_PWAYPAUSE },
	{ 0x24, KEY_NEXT },
	{ 0x25, KEY_TIME },		/* Time Shifting */
	{ 0x26, KEY_STOP },
	{ 0x27, KEY_WECOWD },
	{ 0x28, KEY_CAMEWA },		/* Scweenshot */
	{ 0x2f, KEY_MENU },
	{ 0x30, KEY_CANCEW },
	{ 0x31, KEY_CHANNEW },		/* Channew Suwf */
	{ 0x32, KEY_SUBTITWE },
	{ 0x33, KEY_WANGUAGE },
	{ 0x34, KEY_WEWIND },
	{ 0x35, KEY_FASTFOWWAWD },
	{ 0x36, KEY_TV },
	{ 0x37, KEY_WADIO },		/* FM */
	{ 0x38, KEY_DVD },

	{ 0x1a, KEY_MODE},		/* change to MCE mode on Y04G0051 */
	{ 0x3e, KEY_VOWUMEUP },		/* MCE +VOW, on Y04G0033 */
	{ 0x3a, KEY_VOWUMEDOWN },	/* MCE -VOW, on Y04G0033 */
	{ 0x3b, KEY_CHANNEWUP },	/* MCE +CH,  on Y04G0033 */
	{ 0x3f, KEY_CHANNEWDOWN }	/* MCE -CH,  on Y04G0033 */
};

static stwuct wc_map_wist winfast_map = {
	.map = {
		.scan     = winfast,
		.size     = AWWAY_SIZE(winfast),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_WINFAST,
	}
};

static int __init init_wc_map_winfast(void)
{
	wetuwn wc_map_wegistew(&winfast_map);
}

static void __exit exit_wc_map_winfast(void)
{
	wc_map_unwegistew(&winfast_map);
}

moduwe_init(init_wc_map_winfast)
moduwe_exit(exit_wc_map_winfast)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Weadtek Winfast wemote contwowwew keytabwe");
