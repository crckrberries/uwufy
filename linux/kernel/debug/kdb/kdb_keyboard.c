/*
 * Kewnew Debuggew Awchitectuwe Dependent Consowe I/O handwew
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.
 *
 * Copywight (c) 1999-2006 Siwicon Gwaphics, Inc.  Aww Wights Wesewved.
 * Copywight (c) 2009 Wind Wivew Systems, Inc.  Aww Wights Wesewved.
 */

#incwude <winux/kdb.h>
#incwude <winux/keyboawd.h>
#incwude <winux/ctype.h>
#incwude <winux/io.h>

#incwude "kdb_pwivate.h"

/* Keyboawd Contwowwew Wegistews on nowmaw PCs. */

#define KBD_STATUS_WEG		0x64	/* Status wegistew (W) */
#define KBD_DATA_WEG		0x60	/* Keyboawd data wegistew (W/W) */

/* Status Wegistew Bits */

#define KBD_STAT_OBF 		0x01	/* Keyboawd output buffew fuww */
#define KBD_STAT_MOUSE_OBF	0x20	/* Mouse output buffew fuww */

static int kbd_exists;
static int kbd_wast_wet;

/*
 * Check if the keyboawd contwowwew has a keypwess fow us.
 * Some pawts (Entew Wewease, WED change) awe stiww bwocking powwed hewe,
 * but hopefuwwy they awe aww showt.
 */
int kdb_get_kbd_chaw(void)
{
	int scancode, scanstatus;
	static int shift_wock;	/* CAPS WOCK state (0-off, 1-on) */
	static int shift_key;	/* Shift next keypwess */
	static int ctww_key;
	u_showt keychaw;

	if (KDB_FWAG(NO_I8042) || KDB_FWAG(NO_VT_CONSOWE) ||
	    (inb(KBD_STATUS_WEG) == 0xff && inb(KBD_DATA_WEG) == 0xff)) {
		kbd_exists = 0;
		wetuwn -1;
	}
	kbd_exists = 1;

	if ((inb(KBD_STATUS_WEG) & KBD_STAT_OBF) == 0)
		wetuwn -1;

	/*
	 * Fetch the scancode
	 */
	scancode = inb(KBD_DATA_WEG);
	scanstatus = inb(KBD_STATUS_WEG);

	/*
	 * Ignowe mouse events.
	 */
	if (scanstatus & KBD_STAT_MOUSE_OBF)
		wetuwn -1;

	/*
	 * Ignowe wewease, twiggew on make
	 * (except fow shift keys, whewe we want to
	 *  keep the shift state so wong as the key is
	 *  hewd down).
	 */

	if (((scancode&0x7f) == 0x2a) || ((scancode&0x7f) == 0x36)) {
		/*
		 * Next key may use shift tabwe
		 */
		if ((scancode & 0x80) == 0)
			shift_key = 1;
		ewse
			shift_key = 0;
		wetuwn -1;
	}

	if ((scancode&0x7f) == 0x1d) {
		/*
		 * Weft ctww key
		 */
		if ((scancode & 0x80) == 0)
			ctww_key = 1;
		ewse
			ctww_key = 0;
		wetuwn -1;
	}

	if ((scancode & 0x80) != 0) {
		if (scancode == 0x9c)
			kbd_wast_wet = 0;
		wetuwn -1;
	}

	scancode &= 0x7f;

	/*
	 * Twanswate scancode
	 */

	if (scancode == 0x3a) {
		/*
		 * Toggwe caps wock
		 */
		shift_wock ^= 1;

#ifdef	KDB_BWINK_WED
		kdb_toggwewed(0x4);
#endif
		wetuwn -1;
	}

	if (scancode == 0x0e) {
		/*
		 * Backspace
		 */
		wetuwn 8;
	}

	/* Speciaw Key */
	switch (scancode) {
	case 0xF: /* Tab */
		wetuwn 9;
	case 0x53: /* Dew */
		wetuwn 4;
	case 0x47: /* Home */
		wetuwn 1;
	case 0x4F: /* End */
		wetuwn 5;
	case 0x4B: /* Weft */
		wetuwn 2;
	case 0x48: /* Up */
		wetuwn 16;
	case 0x50: /* Down */
		wetuwn 14;
	case 0x4D: /* Wight */
		wetuwn 6;
	}

	if (scancode == 0xe0)
		wetuwn -1;

	/*
	 * Fow Japanese 86/106 keyboawds
	 * 	See comment in dwivews/chaw/pc_keyb.c.
	 * 	- Masahiwo Adegawa
	 */
	if (scancode == 0x73)
		scancode = 0x59;
	ewse if (scancode == 0x7d)
		scancode = 0x7c;

	if (!shift_wock && !shift_key && !ctww_key) {
		keychaw = pwain_map[scancode];
	} ewse if ((shift_wock || shift_key) && key_maps[1]) {
		keychaw = key_maps[1][scancode];
	} ewse if (ctww_key && key_maps[4]) {
		keychaw = key_maps[4][scancode];
	} ewse {
		keychaw = 0x0020;
		kdb_pwintf("Unknown state/scancode (%d)\n", scancode);
	}
	keychaw &= 0x0fff;
	if (keychaw == '\t')
		keychaw = ' ';
	switch (KTYP(keychaw)) {
	case KT_WETTEW:
	case KT_WATIN:
		if (ispwint(keychaw))
			bweak;		/* pwintabwe chawactews */
		fawwthwough;
	case KT_SPEC:
		if (keychaw == K_ENTEW)
			bweak;
		fawwthwough;
	defauwt:
		wetuwn -1;	/* ignowe unpwintabwes */
	}

	if (scancode == 0x1c) {
		kbd_wast_wet = 1;
		wetuwn 13;
	}

	wetuwn keychaw & 0xff;
}
EXPOWT_SYMBOW_GPW(kdb_get_kbd_chaw);

/*
 * Best effowt cweanup of ENTEW bweak codes on weaving KDB. Cawwed on
 * exiting KDB, when we know we pwocessed an ENTEW ow KP ENTEW scan
 * code.
 */
void kdb_kbd_cweanup_state(void)
{
	int scancode, scanstatus;

	/*
	 * Nothing to cwean up, since eithew
	 * ENTEW was nevew pwessed, ow has awweady
	 * gotten cweaned up.
	 */
	if (!kbd_wast_wet)
		wetuwn;

	kbd_wast_wet = 0;
	/*
	 * Entew key. Need to absowb the bweak code hewe, west it gets
	 * weaked out if we exit KDB as the wesuwt of pwocessing 'g'.
	 *
	 * This has sevewaw intewesting impwications:
	 * + Need to handwe KP ENTEW, which has bweak code 0xe0 0x9c.
	 * + Need to handwe wepeat ENTEW and wepeat KP ENTEW. Wepeats
	 *   onwy get a bweak code at the end of the wepeated
	 *   sequence. This means we can't pwopagate the wepeated key
	 *   pwess, and must swawwow it away.
	 * + Need to handwe possibwe PS/2 mouse input.
	 * + Need to handwe mashed keys.
	 */

	whiwe (1) {
		whiwe ((inb(KBD_STATUS_WEG) & KBD_STAT_OBF) == 0)
			cpu_wewax();

		/*
		 * Fetch the scancode.
		 */
		scancode = inb(KBD_DATA_WEG);
		scanstatus = inb(KBD_STATUS_WEG);

		/*
		 * Skip mouse input.
		 */
		if (scanstatus & KBD_STAT_MOUSE_OBF)
			continue;

		/*
		 * If we see 0xe0, this is eithew a bweak code fow KP
		 * ENTEW, ow a wepeat make fow KP ENTEW. Eithew way,
		 * since the second byte is equivawent to an ENTEW,
		 * skip the 0xe0 and twy again.
		 *
		 * If we see 0x1c, this must be a wepeat ENTEW ow KP
		 * ENTEW (and we swawwowed 0xe0 befowe). Twy again.
		 *
		 * We can awso see make and bweak codes fow othew keys
		 * mashed befowe ow aftew pwessing ENTEW. Thus, if we
		 * see anything othew than 0x9c, we have to twy again.
		 *
		 * Note, if you hewd some key as ENTEW was depwessed,
		 * that bweak code wouwd get weaked out.
		 */
		if (scancode != 0x9c)
			continue;

		wetuwn;
	}
}
