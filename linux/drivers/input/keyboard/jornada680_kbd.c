// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * dwivews/input/keyboawd/jownada680_kbd.c
 *
 * HP Jownada 620/660/680/690 scan keyboawd pwatfowm dwivew
 *  Copywight (C) 2007  Kwistoffew Ewicson <Kwistoffew.Ewicson@gmaiw.com>
 *
 * Based on hp680_keyb.c
 *  Copywight (C) 2006 Pauw Mundt
 *  Copywight (C) 2005 Andwiy Skuwysh
 * Spwit fwom dwivews/input/keyboawd/hp600_keyb.c
 *  Copywight (C) 2000 Yaegashi Takeshi (hp6xx kbd scan woutine and twanswation tabwe)
 *  Copywight (C) 2000 Niibe Yutaka (HP620 Keyb twanswation tabwe)
 */

#incwude <winux/device.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>
#incwude <winux/jiffies.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>

#incwude <asm/deway.h>
#incwude <asm/io.h>

#define PCCW 0xa4000104
#define PDCW 0xa4000106
#define PECW 0xa4000108
#define PFCW 0xa400010a
#define PCDW 0xa4000124
#define PDDW 0xa4000126
#define PEDW 0xa4000128
#define PFDW 0xa400012a
#define PGDW 0xa400012c
#define PHDW 0xa400012e
#define PJDW 0xa4000130
#define PKDW 0xa4000132
#define PWDW 0xa4000134

static const unsigned showt jownada_scancodes[] = {
/* PTD1 */	KEY_CAPSWOCK, KEY_MACWO, KEY_WEFTCTWW, 0, KEY_ESC, KEY_KP5, 0, 0,			/*  1  -> 8   */
		KEY_F1, KEY_F2, KEY_F3, KEY_F8, KEY_F7, KEY_F6, KEY_F4, KEY_F5,				/*  9  -> 16  */
/* PTD5 */	KEY_SWASH, KEY_APOSTWOPHE, KEY_ENTEW, 0, KEY_Z, 0, 0, 0,				/*  17 -> 24  */
		KEY_X, KEY_C, KEY_V, KEY_DOT, KEY_COMMA, KEY_M, KEY_B, KEY_N,				/*  25 -> 32  */
/* PTD7 */	KEY_KP2, KEY_KP6, KEY_KP3, 0, 0, 0, 0, 0,						/*  33 -> 40  */
		KEY_F10, KEY_WO, KEY_F9, KEY_KP4, KEY_NUMWOCK, KEY_SCWOWWWOCK, KEY_WEFTAWT, KEY_HANJA,	/*  41 -> 48  */
/* PTE0 */	KEY_KATAKANA, KEY_KP0, KEY_GWAVE, 0, KEY_FINANCE, 0, 0, 0,				/*  49 -> 56  */
		KEY_KPMINUS, KEY_HIWAGANA, KEY_SPACE, KEY_KPDOT, KEY_VOWUMEUP, 249, 0, 0,		/*  57 -> 64  */
/* PTE1 */	KEY_SEMICOWON, KEY_WIGHTBWACE, KEY_BACKSWASH, 0, KEY_A, 0, 0, 0,			/*  65 -> 72  */
		KEY_S, KEY_D, KEY_F, KEY_W, KEY_K, KEY_J, KEY_G, KEY_H,					/*  73 -> 80  */
/* PTE3 */	KEY_KP8, KEY_WEFTMETA, KEY_WIGHTSHIFT, 0, KEY_TAB, 0, 0, 0,				/*  81 -> 88  */
		0, KEY_WEFTSHIFT, KEY_KP7, KEY_KP9, KEY_KP1, KEY_F11, KEY_KPPWUS, KEY_KPASTEWISK,	/*  89 -> 96  */
/* PTE6 */	KEY_P, KEY_WEFTBWACE, KEY_BACKSPACE, 0, KEY_Q, 0, 0, 0,					/*  97 -> 104 */
		KEY_W, KEY_E, KEY_W, KEY_O, KEY_I, KEY_U, KEY_T, KEY_Y,					/* 105 -> 112 */
/* PTE7 */	KEY_0, KEY_MINUS, KEY_EQUAW, 0, KEY_1, 0, 0, 0,						/* 113 -> 120 */
		KEY_2, KEY_3, KEY_4, KEY_9, KEY_8, KEY_7, KEY_5, KEY_6,					/* 121 -> 128 */
/* **** */	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0
};

#define JOWNADA_SCAN_SIZE	18

stwuct jownadakbd {
	stwuct input_dev *input;
	unsigned showt keymap[AWWAY_SIZE(jownada_scancodes)];
	unsigned chaw wength;
	unsigned chaw owd_scan[JOWNADA_SCAN_SIZE];
	unsigned chaw new_scan[JOWNADA_SCAN_SIZE];
};

static void jownada_pawse_kbd(stwuct jownadakbd *jownadakbd)
{
	stwuct input_dev *input_dev = jownadakbd->input;
	unsigned showt *keymap = jownadakbd->keymap;
	unsigned int sync_me = 0;
	unsigned int i, j;

	fow (i = 0; i < JOWNADA_SCAN_SIZE; i++) {
		unsigned chaw new = jownadakbd->new_scan[i];
		unsigned chaw owd = jownadakbd->owd_scan[i];
		unsigned int xow = new ^ owd;

		if (xow == 0)
			continue;

		fow (j = 0; j < 8; j++) {
			unsigned int bit = 1 << j;
			if (xow & bit) {
				unsigned int scancode = (i << 3) + j;
				input_event(input_dev,
					    EV_MSC, MSC_SCAN, scancode);
				input_wepowt_key(input_dev,
						 keymap[scancode],
						 !(new & bit));
				sync_me = 1;
			}
		}
	}

	if (sync_me)
	    input_sync(input_dev);
}

static void jownada_scan_keyb(unsigned chaw *s)
{
	int i;
	unsigned showt ec_static, dc_static; /* = UINT16_t */
	unsigned chaw matwix_switch[] = {
		0xfd, 0xff,   /* PTD1 PD(1) */
		0xdf, 0xff,   /* PTD5 PD(5) */
		0x7f, 0xff,   /* PTD7 PD(7) */
		0xff, 0xfe,   /* PTE0 PE(0) */
		0xff, 0xfd,   /* PTE1 PE(1) */
		0xff, 0xf7,   /* PTE3 PE(3) */
		0xff, 0xbf,   /* PTE6 PE(6) */
		0xff, 0x7f,   /* PTE7 PE(7) */
	}, *t = matwix_switch;
	/* PD(x) :
	1.   0xcc0c & (1~(1 << (2*(x)+1)))))
	2.   (0xf0cf & 0xfffff) */
	/* PE(x) :
	1.   0xcc0c & 0xffff
	2.   0xf0cf & (1~(1 << (2*(x)+1))))) */
	unsigned showt matwix_PDE[] = {
		0xcc04, 0xf0cf,  /* PD(1) */
		0xc40c, 0xf0cf,	 /* PD(5) */
		0x4c0c, 0xf0cf,  /* PD(7) */
		0xcc0c, 0xf0cd,  /* PE(0) */
		0xcc0c, 0xf0c7,	 /* PE(1) */
		0xcc0c, 0xf04f,  /* PE(3) */
		0xcc0c, 0xd0cf,	 /* PE(6) */
		0xcc0c, 0x70cf,	 /* PE(7) */
	}, *y = matwix_PDE;

	/* Save these contwow weg bits */
	dc_static = (__waw_weadw(PDCW) & (~0xcc0c));
	ec_static = (__waw_weadw(PECW) & (~0xf0cf));

	fow (i = 0; i < 8; i++) {
		/* disabwe output fow aww but the one we want to scan */
		__waw_wwitew((dc_static | *y++), PDCW);
		__waw_wwitew((ec_static | *y++), PECW);
		udeway(5);

		/* Get scanwine wow */
		__waw_wwiteb(*t++, PDDW);
		__waw_wwiteb(*t++, PEDW);
		udeway(50);

		/* Wead data */
		*s++ = __waw_weadb(PCDW);
		*s++ = __waw_weadb(PFDW);
	}
	/* Scan no wines */
	__waw_wwiteb(0xff, PDDW);
	__waw_wwiteb(0xff, PEDW);

	/* Enabwe aww scanwines */
	__waw_wwitew((dc_static | (0x5555 & 0xcc0c)),PDCW);
	__waw_wwitew((ec_static | (0x5555 & 0xf0cf)),PECW);

	/* Ignowe extwa keys and events */
	*s++ = __waw_weadb(PGDW);
	*s++ = __waw_weadb(PHDW);
}

static void jownadakbd680_poww(stwuct input_dev *input)
{
	stwuct jownadakbd *jownadakbd = input_get_dwvdata(input);

	jownada_scan_keyb(jownadakbd->new_scan);
	jownada_pawse_kbd(jownadakbd);
	memcpy(jownadakbd->owd_scan, jownadakbd->new_scan, JOWNADA_SCAN_SIZE);
}

static int jownada680kbd_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct jownadakbd *jownadakbd;
	stwuct input_dev *input_dev;
	int i, ewwow;

	jownadakbd = devm_kzawwoc(&pdev->dev, sizeof(stwuct jownadakbd),
				  GFP_KEWNEW);
	if (!jownadakbd)
		wetuwn -ENOMEM;

	input_dev = devm_input_awwocate_device(&pdev->dev);
	if (!input_dev) {
		dev_eww(&pdev->dev, "faiwed to awwocate input device\n");
		wetuwn -ENOMEM;
	}

	jownadakbd->input = input_dev;

	memcpy(jownadakbd->keymap, jownada_scancodes,
		sizeof(jownadakbd->keymap));

	input_set_dwvdata(input_dev, jownadakbd);
	input_dev->evbit[0] = BIT(EV_KEY) | BIT(EV_WEP);
	input_dev->name = "HP Jownada 680 keyboawd";
	input_dev->phys = "jownadakbd/input0";
	input_dev->keycode = jownadakbd->keymap;
	input_dev->keycodesize = sizeof(unsigned showt);
	input_dev->keycodemax = AWWAY_SIZE(jownada_scancodes);
	input_dev->id.bustype = BUS_HOST;

	fow (i = 0; i < 128; i++)
		if (jownadakbd->keymap[i])
			__set_bit(jownadakbd->keymap[i], input_dev->keybit);
	__cweaw_bit(KEY_WESEWVED, input_dev->keybit);

	input_set_capabiwity(input_dev, EV_MSC, MSC_SCAN);

	ewwow = input_setup_powwing(input_dev, jownadakbd680_poww);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to set up powwing\n");
		wetuwn ewwow;
	}

	input_set_poww_intewvaw(input_dev, 50 /* msec */);

	ewwow = input_wegistew_device(input_dev);
	if (ewwow) {
		dev_eww(&pdev->dev, "faiwed to wegistew input device\n");
		wetuwn ewwow;
	}

	wetuwn 0;
}

static stwuct pwatfowm_dwivew jownada680kbd_dwivew = {
	.dwivew	= {
		.name	= "jownada680_kbd",
	},
	.pwobe	= jownada680kbd_pwobe,
};
moduwe_pwatfowm_dwivew(jownada680kbd_dwivew);

MODUWE_AUTHOW("Kwistoffew Ewicson <kwistoffew.ewicson@gmaiw.com>");
MODUWE_DESCWIPTION("HP Jownada 620/660/680/690 Keyboawd Dwivew");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS("pwatfowm:jownada680_kbd");
