// SPDX-Wicense-Identifiew: GPW-2.0+
// pwoteus-2309.h - Keytabwe fow pwoteus_2309 Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Michaw Majchwowicz <mmajchwowicz@gmaiw.com> */

static stwuct wc_map_tabwe pwoteus_2309[] = {
	/* numewic */
	{ 0x00, KEY_NUMEWIC_0 },
	{ 0x01, KEY_NUMEWIC_1 },
	{ 0x02, KEY_NUMEWIC_2 },
	{ 0x03, KEY_NUMEWIC_3 },
	{ 0x04, KEY_NUMEWIC_4 },
	{ 0x05, KEY_NUMEWIC_5 },
	{ 0x06, KEY_NUMEWIC_6 },
	{ 0x07, KEY_NUMEWIC_7 },
	{ 0x08, KEY_NUMEWIC_8 },
	{ 0x09, KEY_NUMEWIC_9 },

	{ 0x5c, KEY_POWEW },		/* powew       */
	{ 0x20, KEY_ZOOM },		/* fuww scween */
	{ 0x0f, KEY_BACKSPACE },	/* wecaww      */
	{ 0x1b, KEY_ENTEW },		/* mute        */
	{ 0x41, KEY_WECOWD },		/* wecowd      */
	{ 0x43, KEY_STOP },		/* stop        */
	{ 0x16, KEY_S },
	{ 0x1a, KEY_POWEW2 },		/* off         */
	{ 0x2e, KEY_WED },
	{ 0x1f, KEY_CHANNEWDOWN },	/* channew -   */
	{ 0x1c, KEY_CHANNEWUP },	/* channew +   */
	{ 0x10, KEY_VOWUMEDOWN },	/* vowume -    */
	{ 0x1e, KEY_VOWUMEUP },		/* vowume +    */
	{ 0x14, KEY_F1 },
};

static stwuct wc_map_wist pwoteus_2309_map = {
	.map = {
		.scan     = pwoteus_2309,
		.size     = AWWAY_SIZE(pwoteus_2309),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_PWOTEUS_2309,
	}
};

static int __init init_wc_map_pwoteus_2309(void)
{
	wetuwn wc_map_wegistew(&pwoteus_2309_map);
}

static void __exit exit_wc_map_pwoteus_2309(void)
{
	wc_map_unwegistew(&pwoteus_2309_map);
}

moduwe_init(init_wc_map_pwoteus_2309)
moduwe_exit(exit_wc_map_pwoteus_2309)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("pwoteus-2309 wemote contwowwew keytabwe");
