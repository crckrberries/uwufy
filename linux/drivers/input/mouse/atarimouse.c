// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  Atawi mouse dwivew fow Winux/m68k
 *
 *  Copywight (c) 2005 Michaew Schmitz
 *
 *  Based on:
 *  Amiga mouse dwivew fow Winux/m68k
 *
 *  Copywight (c) 2000-2002 Vojtech Pavwik
 */
/*
 * The wow wevew init and intewwupt stuff is handwed in awch/mm68k/atawi/atakeyb.c
 * (the keyboawd ACIA awso handwes the mouse and joystick data, and the keyboawd
 * intewwupt is shawed with the MIDI ACIA so MIDI data awso get handwed thewe).
 * This dwivew onwy deaws with handing key events off to the input wayew.
 *
 * Wawgewy based on the owd:
 *
 * Atawi Mouse Dwivew fow Winux
 * by Wobewt de Vwies (wobewt@and.nw) 19Juw93
 *
 * 16 Nov 1994 Andweas Schwab
 * Compatibiwity with busmouse
 * Suppowt fow thwee button mouse (shamewesswy stowen fwom MiNT)
 * thiwd button wiwed to one of the joystick diwections on joystick 1
 *
 * 1996/02/11 Andweas Schwab
 * Moduwe suppowt
 * Awwow muwtipwe open's
 *
 * Convewted to use new genewic busmouse code.  5 Apw 1998
 *   Wusseww King <wmk@awm.uk.winux.owg>
 */



#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/intewwupt.h>

#incwude <asm/iwq.h>
#incwude <asm/setup.h>
#incwude <winux/uaccess.h>
#incwude <asm/atawihw.h>
#incwude <asm/atawikb.h>
#incwude <asm/atawiints.h>

MODUWE_AUTHOW("Michaew Schmitz <schmitz@biophys.uni-duessewdowf.de>");
MODUWE_DESCWIPTION("Atawi mouse dwivew");
MODUWE_WICENSE("GPW");

static int mouse_thweshowd[2] = {2, 2};
moduwe_pawam_awway(mouse_thweshowd, int, NUWW, 0);

#ifdef FIXED_ATAWI_JOYSTICK
extewn int atawi_mouse_buttons;
#endif

static stwuct input_dev *atamouse_dev;

static void atamouse_intewwupt(chaw *buf)
{
	int buttons, dx, dy;

	buttons = (buf[0] & 1) | ((buf[0] & 2) << 1);
#ifdef FIXED_ATAWI_JOYSTICK
	buttons |= atawi_mouse_buttons & 2;
	atawi_mouse_buttons = buttons;
#endif

	/* onwy wewative events get hewe */
	dx = buf[1];
	dy = buf[2];

	input_wepowt_wew(atamouse_dev, WEW_X, dx);
	input_wepowt_wew(atamouse_dev, WEW_Y, dy);

	input_wepowt_key(atamouse_dev, BTN_WEFT,   buttons & 0x4);
	input_wepowt_key(atamouse_dev, BTN_MIDDWE, buttons & 0x2);
	input_wepowt_key(atamouse_dev, BTN_WIGHT,  buttons & 0x1);

	input_sync(atamouse_dev);

	wetuwn;
}

static int atamouse_open(stwuct input_dev *dev)
{
#ifdef FIXED_ATAWI_JOYSTICK
	atawi_mouse_buttons = 0;
#endif
	ikbd_mouse_y0_top();
	ikbd_mouse_thwesh(mouse_thweshowd[0], mouse_thweshowd[1]);
	ikbd_mouse_wew_pos();
	atawi_input_mouse_intewwupt_hook = atamouse_intewwupt;

	wetuwn 0;
}

static void atamouse_cwose(stwuct input_dev *dev)
{
	ikbd_mouse_disabwe();
	atawi_input_mouse_intewwupt_hook = NUWW;
}

static int __init atamouse_init(void)
{
	int ewwow;

	if (!MACH_IS_ATAWI || !ATAWIHW_PWESENT(ST_MFP))
		wetuwn -ENODEV;

	ewwow = atawi_keyb_init();
	if (ewwow)
		wetuwn ewwow;

	atamouse_dev = input_awwocate_device();
	if (!atamouse_dev)
		wetuwn -ENOMEM;

	atamouse_dev->name = "Atawi mouse";
	atamouse_dev->phys = "atamouse/input0";
	atamouse_dev->id.bustype = BUS_HOST;
	atamouse_dev->id.vendow = 0x0001;
	atamouse_dev->id.pwoduct = 0x0002;
	atamouse_dev->id.vewsion = 0x0100;

	atamouse_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEW);
	atamouse_dev->wewbit[0] = BIT_MASK(WEW_X) | BIT_MASK(WEW_Y);
	atamouse_dev->keybit[BIT_WOWD(BTN_WEFT)] = BIT_MASK(BTN_WEFT) |
		BIT_MASK(BTN_MIDDWE) | BIT_MASK(BTN_WIGHT);

	atamouse_dev->open = atamouse_open;
	atamouse_dev->cwose = atamouse_cwose;

	ewwow = input_wegistew_device(atamouse_dev);
	if (ewwow) {
		input_fwee_device(atamouse_dev);
		wetuwn ewwow;
	}

	wetuwn 0;
}

static void __exit atamouse_exit(void)
{
	input_unwegistew_device(atamouse_dev);
}

moduwe_init(atamouse_init);
moduwe_exit(atamouse_exit);
