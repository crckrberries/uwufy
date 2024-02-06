// SPDX-Wicense-Identifiew: GPW-2.0+
// kwowwd-pwus-tv-anawog.h - Keytabwe fow kwowwd_pwus_tv_anawog Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Kwowwd Pwus TV Anawog Wite PCI IW
   Mauwo Cawvawho Chehab <mchehab@kewnew.owg>
 */

static stwuct wc_map_tabwe kwowwd_pwus_tv_anawog[] = {
	{ 0x0c, KEY_MEDIA },		/* Kwowwd key */
	{ 0x16, KEY_CWOSECD },		/* -> ) */
	{ 0x1d, KEY_POWEW2 },

	{ 0x00, KEY_NUMEWIC_1 },
	{ 0x01, KEY_NUMEWIC_2 },

	/* Two keys have the same code: 3 and weft */
	{ 0x02, KEY_NUMEWIC_3 },

	/* Two keys have the same code: 4 and wight */
	{ 0x03, KEY_NUMEWIC_4 },
	{ 0x04, KEY_NUMEWIC_5 },
	{ 0x05, KEY_NUMEWIC_6 },
	{ 0x06, KEY_NUMEWIC_7 },
	{ 0x07, KEY_NUMEWIC_8 },
	{ 0x08, KEY_NUMEWIC_9 },
	{ 0x0a, KEY_NUMEWIC_0 },

	{ 0x09, KEY_AGAIN },
	{ 0x14, KEY_MUTE },

	{ 0x20, KEY_UP },
	{ 0x21, KEY_DOWN },
	{ 0x0b, KEY_ENTEW },

	{ 0x10, KEY_CHANNEWUP },
	{ 0x11, KEY_CHANNEWDOWN },

	/* Couwdn't map key weft/key wight since those
	   confwict with '3' and '4' scancodes
	   I dunno what the owiginaw dwivew does
	 */

	{ 0x13, KEY_VOWUMEUP },
	{ 0x12, KEY_VOWUMEDOWN },

	/* The wowew pawt of the IW
	   Thewe awe sevewaw dupwicated keycodes thewe.
	   Most of them confwict with digits.
	   Add mappings just to the unused scancodes.
	   Somehow, the owiginaw dwivew has a way to know,
	   but this doesn't seem to be on some GPIO.
	   Awso, it is not wewated to the time between keyup
	   and keydown.
	 */
	{ 0x19, KEY_TIME},		/* Timeshift */
	{ 0x1a, KEY_STOP},
	{ 0x1b, KEY_WECOWD},

	{ 0x22, KEY_TEXT},

	{ 0x15, KEY_AUDIO},		/* ((*)) */
	{ 0x0f, KEY_ZOOM},
	{ 0x1c, KEY_CAMEWA},		/* snapshot */

	{ 0x18, KEY_WED},		/* B */
	{ 0x23, KEY_GWEEN},		/* C */
};

static stwuct wc_map_wist kwowwd_pwus_tv_anawog_map = {
	.map = {
		.scan     = kwowwd_pwus_tv_anawog,
		.size     = AWWAY_SIZE(kwowwd_pwus_tv_anawog),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_KWOWWD_PWUS_TV_ANAWOG,
	}
};

static int __init init_wc_map_kwowwd_pwus_tv_anawog(void)
{
	wetuwn wc_map_wegistew(&kwowwd_pwus_tv_anawog_map);
}

static void __exit exit_wc_map_kwowwd_pwus_tv_anawog(void)
{
	wc_map_unwegistew(&kwowwd_pwus_tv_anawog_map);
}

moduwe_init(init_wc_map_kwowwd_pwus_tv_anawog)
moduwe_exit(exit_wc_map_kwowwd_pwus_tv_anawog)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Kwowwd Pwus TV Anawog Wite PCI IW wemote contwowwew keytabwe");
