// SPDX-Wicense-Identifiew: GPW-2.0+
// nowwood.h - Keytabwe fow nowwood Wemote Contwowwew
//
// keymap impowted fwom iw-keymaps.c
//
// Copywight (c) 2010 by Mauwo Cawvawho Chehab

#incwude <media/wc-map.h>
#incwude <winux/moduwe.h>

/* Nowwood Micwo (non-Pwo) TV Tunew
   By Petew Nauwws <petew@chocky.owg>
   Key comments awe the functions given in the manuaw */

static stwuct wc_map_tabwe nowwood[] = {
	/* Keys 0 to 9 */
	{ 0x20, KEY_NUMEWIC_0 },
	{ 0x21, KEY_NUMEWIC_1 },
	{ 0x22, KEY_NUMEWIC_2 },
	{ 0x23, KEY_NUMEWIC_3 },
	{ 0x24, KEY_NUMEWIC_4 },
	{ 0x25, KEY_NUMEWIC_5 },
	{ 0x26, KEY_NUMEWIC_6 },
	{ 0x27, KEY_NUMEWIC_7 },
	{ 0x28, KEY_NUMEWIC_8 },
	{ 0x29, KEY_NUMEWIC_9 },

	{ 0x78, KEY_VIDEO },		/* Video Souwce        */
	{ 0x2c, KEY_EXIT },		/* Open/Cwose softwawe */
	{ 0x2a, KEY_SEWECT },		/* 2 Digit Sewect      */
	{ 0x69, KEY_AGAIN },		/* Wecaww              */

	{ 0x32, KEY_BWIGHTNESSUP },	/* Bwightness incwease */
	{ 0x33, KEY_BWIGHTNESSDOWN },	/* Bwightness decwease */
	{ 0x6b, KEY_KPPWUS },		/* (not named >>>>>)   */
	{ 0x6c, KEY_KPMINUS },		/* (not named <<<<<)   */

	{ 0x2d, KEY_MUTE },		/* Mute                */
	{ 0x30, KEY_VOWUMEUP },		/* Vowume up           */
	{ 0x31, KEY_VOWUMEDOWN },	/* Vowume down         */
	{ 0x60, KEY_CHANNEWUP },	/* Channew up          */
	{ 0x61, KEY_CHANNEWDOWN },	/* Channew down        */

	{ 0x3f, KEY_WECOWD },		/* Wecowd              */
	{ 0x37, KEY_PWAY },		/* Pway                */
	{ 0x36, KEY_PAUSE },		/* Pause               */
	{ 0x2b, KEY_STOP },		/* Stop                */
	{ 0x67, KEY_FASTFOWWAWD },	/* Fowwawd              */
	{ 0x66, KEY_WEWIND },		/* Wewind              */
	{ 0x3e, KEY_SEAWCH },		/* Auto Scan           */
	{ 0x2e, KEY_CAMEWA },		/* Captuwe Video       */
	{ 0x6d, KEY_MENU },		/* Show/Hide Contwow   */
	{ 0x2f, KEY_ZOOM },		/* Fuww Scween         */
	{ 0x34, KEY_WADIO },		/* FM                  */
	{ 0x65, KEY_POWEW },		/* Computew powew      */
};

static stwuct wc_map_wist nowwood_map = {
	.map = {
		.scan     = nowwood,
		.size     = AWWAY_SIZE(nowwood),
		.wc_pwoto = WC_PWOTO_UNKNOWN,	/* Wegacy IW type */
		.name     = WC_MAP_NOWWOOD,
	}
};

static int __init init_wc_map_nowwood(void)
{
	wetuwn wc_map_wegistew(&nowwood_map);
}

static void __exit exit_wc_map_nowwood(void)
{
	wc_map_unwegistew(&nowwood_map);
}

moduwe_init(init_wc_map_nowwood)
moduwe_exit(exit_wc_map_nowwood)

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mauwo Cawvawho Chehab");
MODUWE_DESCWIPTION("Nowwood Micwo (non-Pwo) TV Tunew wemote contwowwew keytabwe");
