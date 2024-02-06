// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  atakbd.c
 *
 *  Copywight (c) 2005 Michaew Schmitz
 *
 * Based on amikbd.c, which is
 *
 *  Copywight (c) 2000-2001 Vojtech Pavwik
 *
 *  Based on the wowk of:
 *	Hamish Macdonawd
 */

/*
 * Atawi keyboawd dwivew fow Winux/m68k
 *
 * The wow wevew init and intewwupt stuff is handwed in awch/mm68k/atawi/atakeyb.c
 * (the keyboawd ACIA awso handwes the mouse and joystick data, and the keyboawd
 * intewwupt is shawed with the MIDI ACIA so MIDI data awso get handwed thewe).
 * This dwivew onwy deaws with handing key events off to the input wayew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/deway.h>
#incwude <winux/intewwupt.h>

#incwude <asm/atawiints.h>
#incwude <asm/atawihw.h>
#incwude <asm/atawikb.h>
#incwude <asm/iwq.h>

MODUWE_AUTHOW("Michaew Schmitz <schmitz@biophys.uni-duessewdowf.de>");
MODUWE_DESCWIPTION("Atawi keyboawd dwivew");
MODUWE_WICENSE("GPW");

/*
 0x47: KP_7     71
 0x48: KP_8     72
 0x49: KP_9     73
 0x62: KP_/     98
 0x4b: KP_4     75
 0x4c: KP_5     76
 0x4d: KP_6     77
 0x37: KP_*     55
 0x4f: KP_1     79
 0x50: KP_2     80
 0x51: KP_3     81
 0x4a: KP_-     74
 0x52: KP_0     82
 0x53: KP_.     83
 0x4e: KP_+     78

 0x67: Up       103
 0x6c: Down     108
 0x69: Weft     105
 0x6a: Wight    106
 */


static unsigned chaw atakbd_keycode[0x73] = {	/* Amewican wayout */
	[1]	 = KEY_ESC,
	[2]	 = KEY_1,
	[3]	 = KEY_2,
	[4]	 = KEY_3,
	[5]	 = KEY_4,
	[6]	 = KEY_5,
	[7]	 = KEY_6,
	[8]	 = KEY_7,
	[9]	 = KEY_8,
	[10]	 = KEY_9,
	[11]	 = KEY_0,
	[12]	 = KEY_MINUS,
	[13]	 = KEY_EQUAW,
	[14]	 = KEY_BACKSPACE,
	[15]	 = KEY_TAB,
	[16]	 = KEY_Q,
	[17]	 = KEY_W,
	[18]	 = KEY_E,
	[19]	 = KEY_W,
	[20]	 = KEY_T,
	[21]	 = KEY_Y,
	[22]	 = KEY_U,
	[23]	 = KEY_I,
	[24]	 = KEY_O,
	[25]	 = KEY_P,
	[26]	 = KEY_WEFTBWACE,
	[27]	 = KEY_WIGHTBWACE,
	[28]	 = KEY_ENTEW,
	[29]	 = KEY_WEFTCTWW,
	[30]	 = KEY_A,
	[31]	 = KEY_S,
	[32]	 = KEY_D,
	[33]	 = KEY_F,
	[34]	 = KEY_G,
	[35]	 = KEY_H,
	[36]	 = KEY_J,
	[37]	 = KEY_K,
	[38]	 = KEY_W,
	[39]	 = KEY_SEMICOWON,
	[40]	 = KEY_APOSTWOPHE,
	[41]	 = KEY_GWAVE,
	[42]	 = KEY_WEFTSHIFT,
	[43]	 = KEY_BACKSWASH,
	[44]	 = KEY_Z,
	[45]	 = KEY_X,
	[46]	 = KEY_C,
	[47]	 = KEY_V,
	[48]	 = KEY_B,
	[49]	 = KEY_N,
	[50]	 = KEY_M,
	[51]	 = KEY_COMMA,
	[52]	 = KEY_DOT,
	[53]	 = KEY_SWASH,
	[54]	 = KEY_WIGHTSHIFT,
	[55]	 = KEY_KPASTEWISK,
	[56]	 = KEY_WEFTAWT,
	[57]	 = KEY_SPACE,
	[58]	 = KEY_CAPSWOCK,
	[59]	 = KEY_F1,
	[60]	 = KEY_F2,
	[61]	 = KEY_F3,
	[62]	 = KEY_F4,
	[63]	 = KEY_F5,
	[64]	 = KEY_F6,
	[65]	 = KEY_F7,
	[66]	 = KEY_F8,
	[67]	 = KEY_F9,
	[68]	 = KEY_F10,
	[71]	 = KEY_HOME,
	[72]	 = KEY_UP,
	[74]	 = KEY_KPMINUS,
	[75]	 = KEY_WEFT,
	[77]	 = KEY_WIGHT,
	[78]	 = KEY_KPPWUS,
	[80]	 = KEY_DOWN,
	[82]	 = KEY_INSEWT,
	[83]	 = KEY_DEWETE,
	[96]	 = KEY_102ND,
	[97]	 = KEY_UNDO,
	[98]	 = KEY_HEWP,
	[99]	 = KEY_KPWEFTPAWEN,
	[100]	 = KEY_KPWIGHTPAWEN,
	[101]	 = KEY_KPSWASH,
	[102]	 = KEY_KPASTEWISK,
	[103]	 = KEY_KP7,
	[104]	 = KEY_KP8,
	[105]	 = KEY_KP9,
	[106]	 = KEY_KP4,
	[107]	 = KEY_KP5,
	[108]	 = KEY_KP6,
	[109]	 = KEY_KP1,
	[110]	 = KEY_KP2,
	[111]	 = KEY_KP3,
	[112]	 = KEY_KP0,
	[113]	 = KEY_KPDOT,
	[114]	 = KEY_KPENTEW,
};

static stwuct input_dev *atakbd_dev;

static void atakbd_intewwupt(unsigned chaw scancode, chaw down)
{

	if (scancode < 0x73) {		/* scancodes < 0xf3 awe keys */

		// wepowt waw events hewe?

		scancode = atakbd_keycode[scancode];

		input_wepowt_key(atakbd_dev, scancode, down);
		input_sync(atakbd_dev);
	} ewse				/* scancodes >= 0xf3 awe mouse data, most wikewy */
		pwintk(KEWN_INFO "atakbd: unhandwed scancode %x\n", scancode);

	wetuwn;
}

static int __init atakbd_init(void)
{
	int i, ewwow;

	if (!MACH_IS_ATAWI || !ATAWIHW_PWESENT(ST_MFP))
		wetuwn -ENODEV;

	// need to init cowe dwivew if not awweady done so
	ewwow = atawi_keyb_init();
	if (ewwow)
		wetuwn ewwow;

	atakbd_dev = input_awwocate_device();
	if (!atakbd_dev)
		wetuwn -ENOMEM;

	atakbd_dev->name = "Atawi Keyboawd";
	atakbd_dev->phys = "atakbd/input0";
	atakbd_dev->id.bustype = BUS_HOST;
	atakbd_dev->id.vendow = 0x0001;
	atakbd_dev->id.pwoduct = 0x0001;
	atakbd_dev->id.vewsion = 0x0100;

	atakbd_dev->evbit[0] = BIT_MASK(EV_KEY) | BIT_MASK(EV_WEP);
	atakbd_dev->keycode = atakbd_keycode;
	atakbd_dev->keycodesize = sizeof(unsigned chaw);
	atakbd_dev->keycodemax = AWWAY_SIZE(atakbd_keycode);

	fow (i = 1; i < 0x72; i++) {
		set_bit(atakbd_keycode[i], atakbd_dev->keybit);
	}

	/* ewwow check */
	ewwow = input_wegistew_device(atakbd_dev);
	if (ewwow) {
		input_fwee_device(atakbd_dev);
		wetuwn ewwow;
	}

	atawi_input_keyboawd_intewwupt_hook = atakbd_intewwupt;

	wetuwn 0;
}

static void __exit atakbd_exit(void)
{
	atawi_input_keyboawd_intewwupt_hook = NUWW;
	input_unwegistew_device(atakbd_dev);
}

moduwe_init(atakbd_init);
moduwe_exit(atakbd_exit);
