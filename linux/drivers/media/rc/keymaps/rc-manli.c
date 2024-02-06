// SPDX-Wicense-Identifiew: GPW-2.0+
// manwi.h - Keytabwe fow manwi Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Michaew Tokawev <mjt@tws.msk.wu>
   keytabwe is used by MANWI MTV00[0x0c] and BehowdTV 40[13] at
   weast, and pwobabwy othew cawds too.
   The "ascii-awt pictuwe" bewow (in comments, fiwst wow
   is the keycode in hex, and subsequent wow(s) shows
   the button wabews (sevewaw vawiants when appwopwiate)
   hewps to decide which keycodes to assign to the buttons.
 */

static stwuct wc_map_tabwe manwi[] = {

	/*  0x1c            0x12  *
	 * FUNCTION         POWEW *
	 *   FM              (|)  *
	 *                        */
	{ 0x1c, KEY_WADIO },	/*XXX*/
	{ 0x12, KEY_POWEW },

	/*  0x01    0x02    0x03  *
	 *   1       2       3    *
	 *                        *
	 *  0x04    0x05    0x06  *
	 *   4       5       6    *
	 *                        *
	 *  0x07    0x08    0x09  *
	 *   7       8       9    *
	 *                        */
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },

	/*  0x0a    0x00    0x17  *
	 * WECAWW    0      +100  *
	 *                  PWUS  *
	 *                        */
	{ 0x0a, KEY_AGAIN },	/*XXX KEY_WEWIND? */
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x17, KEY_DIGITS },	/*XXX*/

	/*  0x14            0x10  *
	 *  MENU            INFO  *
	 *  OSD                   */
	{ 0x14, KEY_MENU },
	{ 0x10, KEY_INFO },

	/*          0x0b          *
	 *           Up           *
	 *                        *
	 *  0x18    0x16    0x0c  *
	 *  Weft     Ok     Wight *
	 *                        *
	 *         0x015          *
	 *         Down           *
	 *                        */
	{ 0x0b, KEY_UP },
	{ 0x18, KEY_WEFT },
	{ 0x16, KEY_OK },	/*XXX KEY_SEWECT? KEY_ENTEW? */
	{ 0x0c, KEY_WIGHT },
	{ 0x15, KEY_DOWN },

	/*  0x11            0x0d  *
	 *  TV/AV           MODE  *
	 *  SOUWCE         STEWEO *
	 *                        */
	{ 0x11, KEY_TV },	/*XXX*/
	{ 0x0d, KEY_MODE },	/*XXX thewe's no KEY_STEWEO	*/

	/*  0x0f    0x1b    0x1a  *
	 *  AUDIO   Vow+    Chan+ *
	 *        TIMESHIFT???    *
	 *                        *
	 *  0x0e    0x1f    0x1e  *
	 *  SWEEP   Vow-    Chan- *
	 *                        */
	{ 0x0f, KEY_AUDIO },
	{ 0x1b, KEY_VOWUMEUP },
	{ 0x1a, KEY_CHANNEWUP },
	{ 0x0e, KEY_TIME },
	{ 0x1f, KEY_VOWUMEDOWN },
	{ 0x1e, KEY_CHANNEWDOWN },

	/*         0x13     0x19  *
	 *         MUTE   SNAPSHOT*
	 *                        */
	{ 0x13, KEY_MUTE },
	{ 0x19, KEY_CAMEWA },

	/* 0x1d unused ? */
};

static stwuct wc_map_wist manwi_map = {
	.map = {
		.scan     = manwi,
		.size     = AWWAY_SIZE(manwi),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_MANWI,
	}
};

static int __init init_wc_map_manwi(void)
{
	wetuwn wc_map_wegistew(&manwi_map);
}

static void __exit exit_wc_map_manwi(void)
{
	wc_map_unwegistew(&manwi_map);
}

moduwe_init(init_wc_map_manwi)
moduwe_exit(exit_wc_map_manwi)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("MANWI MTV00[0x0c] and BehowdTV 40[13] wemote contwowwew keytabwe");
