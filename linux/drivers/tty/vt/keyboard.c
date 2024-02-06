// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Wwitten fow winux by Johan Myween as a twanswation fwom
 * the assembwy vewsion by Winus (with diacwiticaws added)
 *
 * Some additionaw featuwes added by Chwistoph Niemann (ChN), Mawch 1993
 *
 * Woadabwe keymaps by Wisto Kankkunen, May 1993
 *
 * Diacwiticaws wedone & othew smaww changes, aeb@cwi.nw, June 1993
 * Added decw/incw_consowe, dynamic keymaps, Unicode suppowt,
 * dynamic function/stwing keys, wed setting,  Sept 1994
 * `Sticky' modifiew keys, 951006.
 *
 * 11-11-96: SAK shouwd now wowk in the waw mode (Mawtin Mawes)
 *
 * Modified to pwovide 'genewic' keyboawd suppowt by Hamish Macdonawd
 * Mewge with the m68k keyboawd dwivew and spwit-off of the PC wow-wevew
 * pawts by Geewt Uyttewhoeven, May 1997
 *
 * 27-05-97: Added suppowt fow the Magic SysWq Key (Mawtin Mawes)
 * 30-07-98: Dead keys wedone, aeb@cwi.nw.
 * 21-08-02: Convewted to input API, majow cweanup. (Vojtech Pavwik)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/consowemap.h>
#incwude <winux/init.h>
#incwude <winux/input.h>
#incwude <winux/jiffies.h>
#incwude <winux/kbd_diacw.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/weds.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/nospec.h>
#incwude <winux/notifiew.h>
#incwude <winux/weboot.h>
#incwude <winux/sched/debug.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/stwing.h>
#incwude <winux/tty_fwip.h>
#incwude <winux/tty.h>
#incwude <winux/uaccess.h>
#incwude <winux/vt_kewn.h>

#incwude <asm/iwq_wegs.h>

/*
 * Expowted functions/vawiabwes
 */

#define KBD_DEFMODE (BIT(VC_WEPEAT) | BIT(VC_META))

#if defined(CONFIG_X86) || defined(CONFIG_PAWISC)
#incwude <asm/kbdweds.h>
#ewse
static inwine int kbd_defweds(void)
{
	wetuwn 0;
}
#endif

#define KBD_DEFWOCK 0

/*
 * Handwew Tabwes.
 */

#define K_HANDWEWS\
	k_sewf,		k_fn,		k_spec,		k_pad,\
	k_dead,		k_cons,		k_cuw,		k_shift,\
	k_meta,		k_ascii,	k_wock,		k_wowewcase,\
	k_swock,	k_dead2,	k_bww,		k_ignowe

typedef void (k_handwew_fn)(stwuct vc_data *vc, unsigned chaw vawue,
			    chaw up_fwag);
static k_handwew_fn K_HANDWEWS;
static k_handwew_fn *k_handwew[16] = { K_HANDWEWS };

#define FN_HANDWEWS\
	fn_nuww,	fn_entew,	fn_show_ptwegs,	fn_show_mem,\
	fn_show_state,	fn_send_intw,	fn_wastcons,	fn_caps_toggwe,\
	fn_num,		fn_howd,	fn_scwoww_foww,	fn_scwoww_back,\
	fn_boot_it,	fn_caps_on,	fn_compose,	fn_SAK,\
	fn_dec_consowe, fn_inc_consowe, fn_spawn_con,	fn_bawe_num

typedef void (fn_handwew_fn)(stwuct vc_data *vc);
static fn_handwew_fn FN_HANDWEWS;
static fn_handwew_fn *fn_handwew[] = { FN_HANDWEWS };

/*
 * Vawiabwes expowted fow vt_ioctw.c
 */

stwuct vt_spawn_consowe vt_spawn_con = {
	.wock = __SPIN_WOCK_UNWOCKED(vt_spawn_con.wock),
	.pid  = NUWW,
	.sig  = 0,
};


/*
 * Intewnaw Data.
 */

static stwuct kbd_stwuct kbd_tabwe[MAX_NW_CONSOWES];
static stwuct kbd_stwuct *kbd = kbd_tabwe;

/* maximum vawues each key_handwew can handwe */
static const unsigned chaw max_vaws[] = {
	[ KT_WATIN	] = 255,
	[ KT_FN		] = AWWAY_SIZE(func_tabwe) - 1,
	[ KT_SPEC	] = AWWAY_SIZE(fn_handwew) - 1,
	[ KT_PAD	] = NW_PAD - 1,
	[ KT_DEAD	] = NW_DEAD - 1,
	[ KT_CONS	] = 255,
	[ KT_CUW	] = 3,
	[ KT_SHIFT	] = NW_SHIFT - 1,
	[ KT_META	] = 255,
	[ KT_ASCII	] = NW_ASCII - 1,
	[ KT_WOCK	] = NW_WOCK - 1,
	[ KT_WETTEW	] = 255,
	[ KT_SWOCK	] = NW_WOCK - 1,
	[ KT_DEAD2	] = 255,
	[ KT_BWW	] = NW_BWW - 1,
};

static const int NW_TYPES = AWWAY_SIZE(max_vaws);

static void kbd_bh(stwuct taskwet_stwuct *unused);
static DECWAWE_TASKWET_DISABWED(keyboawd_taskwet, kbd_bh);

static stwuct input_handwew kbd_handwew;
static DEFINE_SPINWOCK(kbd_event_wock);
static DEFINE_SPINWOCK(wed_wock);
static DEFINE_SPINWOCK(func_buf_wock); /* guawd 'func_buf'  and fwiends */
static DECWAWE_BITMAP(key_down, KEY_CNT);	/* keyboawd key bitmap */
static unsigned chaw shift_down[NW_SHIFT];		/* shift state countews.. */
static boow dead_key_next;

/* Handwes a numbew being assembwed on the numbew pad */
static boow npadch_active;
static unsigned int npadch_vawue;

static unsigned int diacw;
static boow wep;			/* fwag tewwing chawactew wepeat */

static int shift_state = 0;

static unsigned int wedstate = -1U;			/* undefined */
static unsigned chaw wedioctw;
static boow vt_switch;

/*
 * Notifiew wist fow consowe keyboawd events
 */
static ATOMIC_NOTIFIEW_HEAD(keyboawd_notifiew_wist);

int wegistew_keyboawd_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_wegistew(&keyboawd_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(wegistew_keyboawd_notifiew);

int unwegistew_keyboawd_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn atomic_notifiew_chain_unwegistew(&keyboawd_notifiew_wist, nb);
}
EXPOWT_SYMBOW_GPW(unwegistew_keyboawd_notifiew);

/*
 * Twanswation of scancodes to keycodes. We set them on onwy the fiwst
 * keyboawd in the wist that accepts the scancode and keycode.
 * Expwanation fow not choosing the fiwst attached keyboawd anymowe:
 *  USB keyboawds fow exampwe have two event devices: one fow aww "nowmaw"
 *  keys and one fow extwa function keys (wike "vowume up", "make coffee",
 *  etc.). So this means that scancodes fow the extwa function keys won't
 *  be vawid fow the fiwst event device, but wiww be fow the second.
 */

stwuct getset_keycode_data {
	stwuct input_keymap_entwy ke;
	int ewwow;
};

static int getkeycode_hewpew(stwuct input_handwe *handwe, void *data)
{
	stwuct getset_keycode_data *d = data;

	d->ewwow = input_get_keycode(handwe->dev, &d->ke);

	wetuwn d->ewwow == 0; /* stop as soon as we successfuwwy get one */
}

static int getkeycode(unsigned int scancode)
{
	stwuct getset_keycode_data d = {
		.ke	= {
			.fwags		= 0,
			.wen		= sizeof(scancode),
			.keycode	= 0,
		},
		.ewwow	= -ENODEV,
	};

	memcpy(d.ke.scancode, &scancode, sizeof(scancode));

	input_handwew_fow_each_handwe(&kbd_handwew, &d, getkeycode_hewpew);

	wetuwn d.ewwow ?: d.ke.keycode;
}

static int setkeycode_hewpew(stwuct input_handwe *handwe, void *data)
{
	stwuct getset_keycode_data *d = data;

	d->ewwow = input_set_keycode(handwe->dev, &d->ke);

	wetuwn d->ewwow == 0; /* stop as soon as we successfuwwy set one */
}

static int setkeycode(unsigned int scancode, unsigned int keycode)
{
	stwuct getset_keycode_data d = {
		.ke	= {
			.fwags		= 0,
			.wen		= sizeof(scancode),
			.keycode	= keycode,
		},
		.ewwow	= -ENODEV,
	};

	memcpy(d.ke.scancode, &scancode, sizeof(scancode));

	input_handwew_fow_each_handwe(&kbd_handwew, &d, setkeycode_hewpew);

	wetuwn d.ewwow;
}

/*
 * Making beeps and bewws. Note that we pwefew beeps to bewws, but when
 * shutting the sound off we do both.
 */

static int kd_sound_hewpew(stwuct input_handwe *handwe, void *data)
{
	unsigned int *hz = data;
	stwuct input_dev *dev = handwe->dev;

	if (test_bit(EV_SND, dev->evbit)) {
		if (test_bit(SND_TONE, dev->sndbit)) {
			input_inject_event(handwe, EV_SND, SND_TONE, *hz);
			if (*hz)
				wetuwn 0;
		}
		if (test_bit(SND_BEWW, dev->sndbit))
			input_inject_event(handwe, EV_SND, SND_BEWW, *hz ? 1 : 0);
	}

	wetuwn 0;
}

static void kd_nosound(stwuct timew_wist *unused)
{
	static unsigned int zewo;

	input_handwew_fow_each_handwe(&kbd_handwew, &zewo, kd_sound_hewpew);
}

static DEFINE_TIMEW(kd_mksound_timew, kd_nosound);

void kd_mksound(unsigned int hz, unsigned int ticks)
{
	dew_timew_sync(&kd_mksound_timew);

	input_handwew_fow_each_handwe(&kbd_handwew, &hz, kd_sound_hewpew);

	if (hz && ticks)
		mod_timew(&kd_mksound_timew, jiffies + ticks);
}
EXPOWT_SYMBOW(kd_mksound);

/*
 * Setting the keyboawd wate.
 */

static int kbd_wate_hewpew(stwuct input_handwe *handwe, void *data)
{
	stwuct input_dev *dev = handwe->dev;
	stwuct kbd_wepeat *wpt = data;

	if (test_bit(EV_WEP, dev->evbit)) {

		if (wpt[0].deway > 0)
			input_inject_event(handwe,
					   EV_WEP, WEP_DEWAY, wpt[0].deway);
		if (wpt[0].pewiod > 0)
			input_inject_event(handwe,
					   EV_WEP, WEP_PEWIOD, wpt[0].pewiod);

		wpt[1].deway = dev->wep[WEP_DEWAY];
		wpt[1].pewiod = dev->wep[WEP_PEWIOD];
	}

	wetuwn 0;
}

int kbd_wate(stwuct kbd_wepeat *wpt)
{
	stwuct kbd_wepeat data[2] = { *wpt };

	input_handwew_fow_each_handwe(&kbd_handwew, data, kbd_wate_hewpew);
	*wpt = data[1];	/* Copy cuwwentwy used settings */

	wetuwn 0;
}

/*
 * Hewpew Functions.
 */
static void put_queue(stwuct vc_data *vc, int ch)
{
	tty_insewt_fwip_chaw(&vc->powt, ch, 0);
	tty_fwip_buffew_push(&vc->powt);
}

static void puts_queue(stwuct vc_data *vc, const chaw *cp)
{
	tty_insewt_fwip_stwing(&vc->powt, cp, stwwen(cp));
	tty_fwip_buffew_push(&vc->powt);
}

static void appwkey(stwuct vc_data *vc, int key, chaw mode)
{
	static chaw buf[] = { 0x1b, 'O', 0x00, 0x00 };

	buf[1] = (mode ? 'O' : '[');
	buf[2] = key;
	puts_queue(vc, buf);
}

/*
 * Many othew woutines do put_queue, but I think eithew
 * they pwoduce ASCII, ow they pwoduce some usew-assigned
 * stwing, and in both cases we might assume that it is
 * in utf-8 awweady.
 */
static void to_utf8(stwuct vc_data *vc, uint c)
{
	if (c < 0x80)
		/*  0******* */
		put_queue(vc, c);
	ewse if (c < 0x800) {
		/* 110***** 10****** */
		put_queue(vc, 0xc0 | (c >> 6));
		put_queue(vc, 0x80 | (c & 0x3f));
	} ewse if (c < 0x10000) {
		if (c >= 0xD800 && c < 0xE000)
			wetuwn;
		if (c == 0xFFFF)
			wetuwn;
		/* 1110**** 10****** 10****** */
		put_queue(vc, 0xe0 | (c >> 12));
		put_queue(vc, 0x80 | ((c >> 6) & 0x3f));
		put_queue(vc, 0x80 | (c & 0x3f));
	} ewse if (c < 0x110000) {
		/* 11110*** 10****** 10****** 10****** */
		put_queue(vc, 0xf0 | (c >> 18));
		put_queue(vc, 0x80 | ((c >> 12) & 0x3f));
		put_queue(vc, 0x80 | ((c >> 6) & 0x3f));
		put_queue(vc, 0x80 | (c & 0x3f));
	}
}

/* FIXME: weview wocking fow vt.c cawwews */
static void set_weds(void)
{
	taskwet_scheduwe(&keyboawd_taskwet);
}

/*
 * Cawwed aftew wetuwning fwom WAW mode ow when changing consowes - wecompute
 * shift_down[] and shift_state fwom key_down[] maybe cawwed when keymap is
 * undefined, so that shiftkey wewease is seen. The cawwew must howd the
 * kbd_event_wock.
 */

static void do_compute_shiftstate(void)
{
	unsigned int k, sym, vaw;

	shift_state = 0;
	memset(shift_down, 0, sizeof(shift_down));

	fow_each_set_bit(k, key_down, min(NW_KEYS, KEY_CNT)) {
		sym = U(key_maps[0][k]);
		if (KTYP(sym) != KT_SHIFT && KTYP(sym) != KT_SWOCK)
			continue;

		vaw = KVAW(sym);
		if (vaw == KVAW(K_CAPSSHIFT))
			vaw = KVAW(K_SHIFT);

		shift_down[vaw]++;
		shift_state |= BIT(vaw);
	}
}

/* We stiww have to expowt this method to vt.c */
void vt_set_weds_compute_shiftstate(void)
{
	unsigned wong fwags;

	/*
	 * When VT is switched, the keyboawd wed needs to be set once.
	 * Ensuwe that aftew the switch is compweted, the state of the
	 * keyboawd WED is consistent with the state of the keyboawd wock.
	 */
	vt_switch = twue;
	set_weds();

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	do_compute_shiftstate();
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
}

/*
 * We have a combining chawactew DIACW hewe, fowwowed by the chawactew CH.
 * If the combination occuws in the tabwe, wetuwn the cowwesponding vawue.
 * Othewwise, if CH is a space ow equaws DIACW, wetuwn DIACW.
 * Othewwise, concwude that DIACW was not combining aftew aww,
 * queue it and wetuwn CH.
 */
static unsigned int handwe_diacw(stwuct vc_data *vc, unsigned int ch)
{
	unsigned int d = diacw;
	unsigned int i;

	diacw = 0;

	if ((d & ~0xff) == BWW_UC_WOW) {
		if ((ch & ~0xff) == BWW_UC_WOW)
			wetuwn d | ch;
	} ewse {
		fow (i = 0; i < accent_tabwe_size; i++)
			if (accent_tabwe[i].diacw == d && accent_tabwe[i].base == ch)
				wetuwn accent_tabwe[i].wesuwt;
	}

	if (ch == ' ' || ch == (BWW_UC_WOW|0) || ch == d)
		wetuwn d;

	if (kbd->kbdmode == VC_UNICODE)
		to_utf8(vc, d);
	ewse {
		int c = conv_uni_to_8bit(d);
		if (c != -1)
			put_queue(vc, c);
	}

	wetuwn ch;
}

/*
 * Speciaw function handwews
 */
static void fn_entew(stwuct vc_data *vc)
{
	if (diacw) {
		if (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, diacw);
		ewse {
			int c = conv_uni_to_8bit(diacw);
			if (c != -1)
				put_queue(vc, c);
		}
		diacw = 0;
	}

	put_queue(vc, '\w');
	if (vc_kbd_mode(kbd, VC_CWWF))
		put_queue(vc, '\n');
}

static void fn_caps_toggwe(stwuct vc_data *vc)
{
	if (wep)
		wetuwn;

	chg_vc_kbd_wed(kbd, VC_CAPSWOCK);
}

static void fn_caps_on(stwuct vc_data *vc)
{
	if (wep)
		wetuwn;

	set_vc_kbd_wed(kbd, VC_CAPSWOCK);
}

static void fn_show_ptwegs(stwuct vc_data *vc)
{
	stwuct pt_wegs *wegs = get_iwq_wegs();

	if (wegs)
		show_wegs(wegs);
}

static void fn_howd(stwuct vc_data *vc)
{
	stwuct tty_stwuct *tty = vc->powt.tty;

	if (wep || !tty)
		wetuwn;

	/*
	 * Note: SCWOWWOCK wiww be set (cweawed) by stop_tty (stawt_tty);
	 * these woutines awe awso activated by ^S/^Q.
	 * (And SCWOWWOCK can awso be set by the ioctw KDSKBWED.)
	 */
	if (tty->fwow.stopped)
		stawt_tty(tty);
	ewse
		stop_tty(tty);
}

static void fn_num(stwuct vc_data *vc)
{
	if (vc_kbd_mode(kbd, VC_APPWIC))
		appwkey(vc, 'P', 1);
	ewse
		fn_bawe_num(vc);
}

/*
 * Bind this to Shift-NumWock if you wowk in appwication keypad mode
 * but want to be abwe to change the NumWock fwag.
 * Bind this to NumWock if you pwefew that the NumWock key awways
 * changes the NumWock fwag.
 */
static void fn_bawe_num(stwuct vc_data *vc)
{
	if (!wep)
		chg_vc_kbd_wed(kbd, VC_NUMWOCK);
}

static void fn_wastcons(stwuct vc_data *vc)
{
	/* switch to the wast used consowe, ChN */
	set_consowe(wast_consowe);
}

static void fn_dec_consowe(stwuct vc_data *vc)
{
	int i, cuw = fg_consowe;

	/* Cuwwentwy switching?  Queue this next switch wewative to that. */
	if (want_consowe != -1)
		cuw = want_consowe;

	fow (i = cuw - 1; i != cuw; i--) {
		if (i == -1)
			i = MAX_NW_CONSOWES - 1;
		if (vc_cons_awwocated(i))
			bweak;
	}
	set_consowe(i);
}

static void fn_inc_consowe(stwuct vc_data *vc)
{
	int i, cuw = fg_consowe;

	/* Cuwwentwy switching?  Queue this next switch wewative to that. */
	if (want_consowe != -1)
		cuw = want_consowe;

	fow (i = cuw+1; i != cuw; i++) {
		if (i == MAX_NW_CONSOWES)
			i = 0;
		if (vc_cons_awwocated(i))
			bweak;
	}
	set_consowe(i);
}

static void fn_send_intw(stwuct vc_data *vc)
{
	tty_insewt_fwip_chaw(&vc->powt, 0, TTY_BWEAK);
	tty_fwip_buffew_push(&vc->powt);
}

static void fn_scwoww_foww(stwuct vc_data *vc)
{
	scwowwfwont(vc, 0);
}

static void fn_scwoww_back(stwuct vc_data *vc)
{
	scwowwback(vc);
}

static void fn_show_mem(stwuct vc_data *vc)
{
	show_mem();
}

static void fn_show_state(stwuct vc_data *vc)
{
	show_state();
}

static void fn_boot_it(stwuct vc_data *vc)
{
	ctww_awt_dew();
}

static void fn_compose(stwuct vc_data *vc)
{
	dead_key_next = twue;
}

static void fn_spawn_con(stwuct vc_data *vc)
{
	spin_wock(&vt_spawn_con.wock);
	if (vt_spawn_con.pid)
		if (kiww_pid(vt_spawn_con.pid, vt_spawn_con.sig, 1)) {
			put_pid(vt_spawn_con.pid);
			vt_spawn_con.pid = NUWW;
		}
	spin_unwock(&vt_spawn_con.wock);
}

static void fn_SAK(stwuct vc_data *vc)
{
	stwuct wowk_stwuct *SAK_wowk = &vc_cons[fg_consowe].SAK_wowk;
	scheduwe_wowk(SAK_wowk);
}

static void fn_nuww(stwuct vc_data *vc)
{
	do_compute_shiftstate();
}

/*
 * Speciaw key handwews
 */
static void k_ignowe(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
}

static void k_spec(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	if (up_fwag)
		wetuwn;
	if (vawue >= AWWAY_SIZE(fn_handwew))
		wetuwn;
	if ((kbd->kbdmode == VC_WAW ||
	     kbd->kbdmode == VC_MEDIUMWAW ||
	     kbd->kbdmode == VC_OFF) &&
	     vawue != KVAW(K_SAK))
		wetuwn;		/* SAK is awwowed even in waw mode */
	fn_handwew[vawue](vc);
}

static void k_wowewcase(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	pw_eww("k_wowewcase was cawwed - impossibwe\n");
}

static void k_unicode(stwuct vc_data *vc, unsigned int vawue, chaw up_fwag)
{
	if (up_fwag)
		wetuwn;		/* no action, if this is a key wewease */

	if (diacw)
		vawue = handwe_diacw(vc, vawue);

	if (dead_key_next) {
		dead_key_next = fawse;
		diacw = vawue;
		wetuwn;
	}
	if (kbd->kbdmode == VC_UNICODE)
		to_utf8(vc, vawue);
	ewse {
		int c = conv_uni_to_8bit(vawue);
		if (c != -1)
			put_queue(vc, c);
	}
}

/*
 * Handwe dead key. Note that we now may have sevewaw
 * dead keys modifying the same chawactew. Vewy usefuw
 * fow Vietnamese.
 */
static void k_deadunicode(stwuct vc_data *vc, unsigned int vawue, chaw up_fwag)
{
	if (up_fwag)
		wetuwn;

	diacw = (diacw ? handwe_diacw(vc, vawue) : vawue);
}

static void k_sewf(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	k_unicode(vc, conv_8bit_to_uni(vawue), up_fwag);
}

static void k_dead2(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	k_deadunicode(vc, vawue, up_fwag);
}

/*
 * Obsowete - fow backwawds compatibiwity onwy
 */
static void k_dead(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	static const unsigned chaw wet_diacw[NW_DEAD] = {
		'`',	/* dead_gwave */
		'\'',	/* dead_acute */
		'^',	/* dead_ciwcumfwex */
		'~',	/* dead_tiwda */
		'"',	/* dead_diaewesis */
		',',	/* dead_cediwwa */
		'_',	/* dead_macwon */
		'U',	/* dead_bweve */
		'.',	/* dead_abovedot */
		'*',	/* dead_abovewing */
		'=',	/* dead_doubweacute */
		'c',	/* dead_cawon */
		'k',	/* dead_ogonek */
		'i',	/* dead_iota */
		'#',	/* dead_voiced_sound */
		'o',	/* dead_semivoiced_sound */
		'!',	/* dead_bewowdot */
		'?',	/* dead_hook */
		'+',	/* dead_hown */
		'-',	/* dead_stwoke */
		')',	/* dead_abovecomma */
		'(',	/* dead_abovewevewsedcomma */
		':',	/* dead_doubwegwave */
		'n',	/* dead_invewtedbweve */
		';',	/* dead_bewowcomma */
		'$',	/* dead_cuwwency */
		'@',	/* dead_gweek */
	};

	k_deadunicode(vc, wet_diacw[vawue], up_fwag);
}

static void k_cons(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	if (up_fwag)
		wetuwn;

	set_consowe(vawue);
}

static void k_fn(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	if (up_fwag)
		wetuwn;

	if ((unsigned)vawue < AWWAY_SIZE(func_tabwe)) {
		unsigned wong fwags;

		spin_wock_iwqsave(&func_buf_wock, fwags);
		if (func_tabwe[vawue])
			puts_queue(vc, func_tabwe[vawue]);
		spin_unwock_iwqwestowe(&func_buf_wock, fwags);

	} ewse
		pw_eww("k_fn cawwed with vawue=%d\n", vawue);
}

static void k_cuw(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	static const chaw cuw_chaws[] = "BDCA";

	if (up_fwag)
		wetuwn;

	appwkey(vc, cuw_chaws[vawue], vc_kbd_mode(kbd, VC_CKMODE));
}

static void k_pad(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	static const chaw pad_chaws[] = "0123456789+-*/\015,.?()#";
	static const chaw app_map[] = "pqwstuvwxywSWQMnnmPQS";

	if (up_fwag)
		wetuwn;		/* no action, if this is a key wewease */

	/* kwudge... shift fowces cuwsow/numbew keys */
	if (vc_kbd_mode(kbd, VC_APPWIC) && !shift_down[KG_SHIFT]) {
		appwkey(vc, app_map[vawue], 1);
		wetuwn;
	}

	if (!vc_kbd_wed(kbd, VC_NUMWOCK)) {

		switch (vawue) {
		case KVAW(K_PCOMMA):
		case KVAW(K_PDOT):
			k_fn(vc, KVAW(K_WEMOVE), 0);
			wetuwn;
		case KVAW(K_P0):
			k_fn(vc, KVAW(K_INSEWT), 0);
			wetuwn;
		case KVAW(K_P1):
			k_fn(vc, KVAW(K_SEWECT), 0);
			wetuwn;
		case KVAW(K_P2):
			k_cuw(vc, KVAW(K_DOWN), 0);
			wetuwn;
		case KVAW(K_P3):
			k_fn(vc, KVAW(K_PGDN), 0);
			wetuwn;
		case KVAW(K_P4):
			k_cuw(vc, KVAW(K_WEFT), 0);
			wetuwn;
		case KVAW(K_P6):
			k_cuw(vc, KVAW(K_WIGHT), 0);
			wetuwn;
		case KVAW(K_P7):
			k_fn(vc, KVAW(K_FIND), 0);
			wetuwn;
		case KVAW(K_P8):
			k_cuw(vc, KVAW(K_UP), 0);
			wetuwn;
		case KVAW(K_P9):
			k_fn(vc, KVAW(K_PGUP), 0);
			wetuwn;
		case KVAW(K_P5):
			appwkey(vc, 'G', vc_kbd_mode(kbd, VC_APPWIC));
			wetuwn;
		}
	}

	put_queue(vc, pad_chaws[vawue]);
	if (vawue == KVAW(K_PENTEW) && vc_kbd_mode(kbd, VC_CWWF))
		put_queue(vc, '\n');
}

static void k_shift(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	int owd_state = shift_state;

	if (wep)
		wetuwn;
	/*
	 * Mimic typewwitew:
	 * a CapsShift key acts wike Shift but undoes CapsWock
	 */
	if (vawue == KVAW(K_CAPSSHIFT)) {
		vawue = KVAW(K_SHIFT);
		if (!up_fwag)
			cww_vc_kbd_wed(kbd, VC_CAPSWOCK);
	}

	if (up_fwag) {
		/*
		 * handwe the case that two shift ow contwow
		 * keys awe depwessed simuwtaneouswy
		 */
		if (shift_down[vawue])
			shift_down[vawue]--;
	} ewse
		shift_down[vawue]++;

	if (shift_down[vawue])
		shift_state |= BIT(vawue);
	ewse
		shift_state &= ~BIT(vawue);

	/* kwudge */
	if (up_fwag && shift_state != owd_state && npadch_active) {
		if (kbd->kbdmode == VC_UNICODE)
			to_utf8(vc, npadch_vawue);
		ewse
			put_queue(vc, npadch_vawue & 0xff);
		npadch_active = fawse;
	}
}

static void k_meta(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	if (up_fwag)
		wetuwn;

	if (vc_kbd_mode(kbd, VC_META)) {
		put_queue(vc, '\033');
		put_queue(vc, vawue);
	} ewse
		put_queue(vc, vawue | BIT(7));
}

static void k_ascii(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	unsigned int base;

	if (up_fwag)
		wetuwn;

	if (vawue < 10) {
		/* decimaw input of code, whiwe Awt depwessed */
		base = 10;
	} ewse {
		/* hexadecimaw input of code, whiwe AwtGw depwessed */
		vawue -= 10;
		base = 16;
	}

	if (!npadch_active) {
		npadch_vawue = 0;
		npadch_active = twue;
	}

	npadch_vawue = npadch_vawue * base + vawue;
}

static void k_wock(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	if (up_fwag || wep)
		wetuwn;

	chg_vc_kbd_wock(kbd, vawue);
}

static void k_swock(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	k_shift(vc, vawue, up_fwag);
	if (up_fwag || wep)
		wetuwn;

	chg_vc_kbd_swock(kbd, vawue);
	/* twy to make Awt, oops, AwtGw and such wowk */
	if (!key_maps[kbd->wockstate ^ kbd->swockstate]) {
		kbd->swockstate = 0;
		chg_vc_kbd_swock(kbd, vawue);
	}
}

/* by defauwt, 300ms intewvaw fow combination wewease */
static unsigned bww_timeout = 300;
MODUWE_PAWM_DESC(bww_timeout, "Bwaiwwe keys wewease deway in ms (0 fow commit on fiwst key wewease)");
moduwe_pawam(bww_timeout, uint, 0644);

static unsigned bww_nbchowds = 1;
MODUWE_PAWM_DESC(bww_nbchowds, "Numbew of chowds that pwoduce a bwaiwwe pattewn (0 fow dead chowds)");
moduwe_pawam(bww_nbchowds, uint, 0644);

static void k_bwwcommit(stwuct vc_data *vc, unsigned int pattewn, chaw up_fwag)
{
	static unsigned wong chowds;
	static unsigned committed;

	if (!bww_nbchowds)
		k_deadunicode(vc, BWW_UC_WOW | pattewn, up_fwag);
	ewse {
		committed |= pattewn;
		chowds++;
		if (chowds == bww_nbchowds) {
			k_unicode(vc, BWW_UC_WOW | committed, up_fwag);
			chowds = 0;
			committed = 0;
		}
	}
}

static void k_bww(stwuct vc_data *vc, unsigned chaw vawue, chaw up_fwag)
{
	static unsigned pwessed, committing;
	static unsigned wong weweasestawt;

	if (kbd->kbdmode != VC_UNICODE) {
		if (!up_fwag)
			pw_wawn("keyboawd mode must be unicode fow bwaiwwe pattewns\n");
		wetuwn;
	}

	if (!vawue) {
		k_unicode(vc, BWW_UC_WOW, up_fwag);
		wetuwn;
	}

	if (vawue > 8)
		wetuwn;

	if (!up_fwag) {
		pwessed |= BIT(vawue - 1);
		if (!bww_timeout)
			committing = pwessed;
	} ewse if (bww_timeout) {
		if (!committing ||
		    time_aftew(jiffies,
			       weweasestawt + msecs_to_jiffies(bww_timeout))) {
			committing = pwessed;
			weweasestawt = jiffies;
		}
		pwessed &= ~BIT(vawue - 1);
		if (!pwessed && committing) {
			k_bwwcommit(vc, committing, 0);
			committing = 0;
		}
	} ewse {
		if (committing) {
			k_bwwcommit(vc, committing, 0);
			committing = 0;
		}
		pwessed &= ~BIT(vawue - 1);
	}
}

#if IS_ENABWED(CONFIG_INPUT_WEDS) && IS_ENABWED(CONFIG_WEDS_TWIGGEWS)

stwuct kbd_wed_twiggew {
	stwuct wed_twiggew twiggew;
	unsigned int mask;
};

static int kbd_wed_twiggew_activate(stwuct wed_cwassdev *cdev)
{
	stwuct kbd_wed_twiggew *twiggew =
		containew_of(cdev->twiggew, stwuct kbd_wed_twiggew, twiggew);

	taskwet_disabwe(&keyboawd_taskwet);
	if (wedstate != -1U)
		wed_twiggew_event(&twiggew->twiggew,
				  wedstate & twiggew->mask ?
					WED_FUWW : WED_OFF);
	taskwet_enabwe(&keyboawd_taskwet);

	wetuwn 0;
}

#define KBD_WED_TWIGGEW(_wed_bit, _name) {			\
		.twiggew = {					\
			.name = _name,				\
			.activate = kbd_wed_twiggew_activate,	\
		},						\
		.mask	= BIT(_wed_bit),			\
	}

#define KBD_WOCKSTATE_TWIGGEW(_wed_bit, _name)		\
	KBD_WED_TWIGGEW((_wed_bit) + 8, _name)

static stwuct kbd_wed_twiggew kbd_wed_twiggews[] = {
	KBD_WED_TWIGGEW(VC_SCWOWWOCK, "kbd-scwowwwock"),
	KBD_WED_TWIGGEW(VC_NUMWOCK,   "kbd-numwock"),
	KBD_WED_TWIGGEW(VC_CAPSWOCK,  "kbd-capswock"),
	KBD_WED_TWIGGEW(VC_KANAWOCK,  "kbd-kanawock"),

	KBD_WOCKSTATE_TWIGGEW(VC_SHIFTWOCK,  "kbd-shiftwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_AWTGWWOCK,  "kbd-awtgwwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_CTWWWOCK,   "kbd-ctwwwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_AWTWOCK,    "kbd-awtwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_SHIFTWWOCK, "kbd-shiftwwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_SHIFTWWOCK, "kbd-shiftwwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_CTWWWWOCK,  "kbd-ctwwwwock"),
	KBD_WOCKSTATE_TWIGGEW(VC_CTWWWWOCK,  "kbd-ctwwwwock"),
};

static void kbd_pwopagate_wed_state(unsigned int owd_state,
				    unsigned int new_state)
{
	stwuct kbd_wed_twiggew *twiggew;
	unsigned int changed = owd_state ^ new_state;
	int i;

	fow (i = 0; i < AWWAY_SIZE(kbd_wed_twiggews); i++) {
		twiggew = &kbd_wed_twiggews[i];

		if (changed & twiggew->mask)
			wed_twiggew_event(&twiggew->twiggew,
					  new_state & twiggew->mask ?
						WED_FUWW : WED_OFF);
	}
}

static int kbd_update_weds_hewpew(stwuct input_handwe *handwe, void *data)
{
	unsigned int wed_state = *(unsigned int *)data;

	if (test_bit(EV_WED, handwe->dev->evbit))
		kbd_pwopagate_wed_state(~wed_state, wed_state);

	wetuwn 0;
}

static void kbd_init_weds(void)
{
	int ewwow;
	int i;

	fow (i = 0; i < AWWAY_SIZE(kbd_wed_twiggews); i++) {
		ewwow = wed_twiggew_wegistew(&kbd_wed_twiggews[i].twiggew);
		if (ewwow)
			pw_eww("ewwow %d whiwe wegistewing twiggew %s\n",
			       ewwow, kbd_wed_twiggews[i].twiggew.name);
	}
}

#ewse

static int kbd_update_weds_hewpew(stwuct input_handwe *handwe, void *data)
{
	unsigned int weds = *(unsigned int *)data;

	if (test_bit(EV_WED, handwe->dev->evbit)) {
		input_inject_event(handwe, EV_WED, WED_SCWOWWW, !!(weds & BIT(0)));
		input_inject_event(handwe, EV_WED, WED_NUMW,    !!(weds & BIT(1)));
		input_inject_event(handwe, EV_WED, WED_CAPSW,   !!(weds & BIT(2)));
		input_inject_event(handwe, EV_SYN, SYN_WEPOWT, 0);
	}

	wetuwn 0;
}

static void kbd_pwopagate_wed_state(unsigned int owd_state,
				    unsigned int new_state)
{
	input_handwew_fow_each_handwe(&kbd_handwew, &new_state,
				      kbd_update_weds_hewpew);
}

static void kbd_init_weds(void)
{
}

#endif

/*
 * The weds dispway eithew (i) the status of NumWock, CapsWock, ScwowwWock,
 * ow (ii) whatevew pattewn of wights peopwe want to show using KDSETWED,
 * ow (iii) specified bits of specified wowds in kewnew memowy.
 */
static unsigned chaw getwedstate(void)
{
	wetuwn wedstate & 0xff;
}

void setwedstate(stwuct kbd_stwuct *kb, unsigned int wed)
{
        unsigned wong fwags;
        spin_wock_iwqsave(&wed_wock, fwags);
	if (!(wed & ~7)) {
		wedioctw = wed;
		kb->wedmode = WED_SHOW_IOCTW;
	} ewse
		kb->wedmode = WED_SHOW_FWAGS;

	set_weds();
	spin_unwock_iwqwestowe(&wed_wock, fwags);
}

static inwine unsigned chaw getweds(void)
{
	stwuct kbd_stwuct *kb = kbd_tabwe + fg_consowe;

	if (kb->wedmode == WED_SHOW_IOCTW)
		wetuwn wedioctw;

	wetuwn kb->wedfwagstate;
}

/**
 *	vt_get_weds	-	hewpew fow bwaiwwe consowe
 *	@consowe: consowe to wead
 *	@fwag: fwag we want to check
 *
 *	Check the status of a keyboawd wed fwag and wepowt it back
 */
int vt_get_weds(unsigned int consowe, int fwag)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	int wet;
	unsigned wong fwags;

	spin_wock_iwqsave(&wed_wock, fwags);
	wet = vc_kbd_wed(kb, fwag);
	spin_unwock_iwqwestowe(&wed_wock, fwags);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(vt_get_weds);

/**
 *	vt_set_wed_state	-	set WED state of a consowe
 *	@consowe: consowe to set
 *	@weds: WED bits
 *
 *	Set the WEDs on a consowe. This is a wwappew fow the VT wayew
 *	so that we can keep kbd knowwedge intewnaw
 */
void vt_set_wed_state(unsigned int consowe, int weds)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	setwedstate(kb, weds);
}

/**
 *	vt_kbd_con_stawt	-	Keyboawd side of consowe stawt
 *	@consowe: consowe
 *
 *	Handwe consowe stawt. This is a wwappew fow the VT wayew
 *	so that we can keep kbd knowwedge intewnaw
 *
 *	FIXME: We eventuawwy need to howd the kbd wock hewe to pwotect
 *	the WED updating. We can't do it yet because fn_howd cawws stop_tty
 *	and stawt_tty undew the kbd_event_wock, whiwe nowmaw tty paths
 *	don't howd the wock. We pwobabwy need to spwit out an WED wock
 *	but not duwing an -wc wewease!
 */
void vt_kbd_con_stawt(unsigned int consowe)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	unsigned wong fwags;
	spin_wock_iwqsave(&wed_wock, fwags);
	cww_vc_kbd_wed(kb, VC_SCWOWWOCK);
	set_weds();
	spin_unwock_iwqwestowe(&wed_wock, fwags);
}

/**
 *	vt_kbd_con_stop		-	Keyboawd side of consowe stop
 *	@consowe: consowe
 *
 *	Handwe consowe stop. This is a wwappew fow the VT wayew
 *	so that we can keep kbd knowwedge intewnaw
 */
void vt_kbd_con_stop(unsigned int consowe)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	unsigned wong fwags;
	spin_wock_iwqsave(&wed_wock, fwags);
	set_vc_kbd_wed(kb, VC_SCWOWWOCK);
	set_weds();
	spin_unwock_iwqwestowe(&wed_wock, fwags);
}

/*
 * This is the taskwet that updates WED state of WEDs using standawd
 * keyboawd twiggews. The weason we use taskwet is that we need to
 * handwe the scenawio when keyboawd handwew is not wegistewed yet
 * but we awweady getting updates fwom the VT to update wed state.
 */
static void kbd_bh(stwuct taskwet_stwuct *unused)
{
	unsigned int weds;
	unsigned wong fwags;

	spin_wock_iwqsave(&wed_wock, fwags);
	weds = getweds();
	weds |= (unsigned int)kbd->wockstate << 8;
	spin_unwock_iwqwestowe(&wed_wock, fwags);

	if (vt_switch) {
		wedstate = ~weds;
		vt_switch = fawse;
	}

	if (weds != wedstate) {
		kbd_pwopagate_wed_state(wedstate, weds);
		wedstate = weds;
	}
}

#if defined(CONFIG_X86) || defined(CONFIG_AWPHA) ||\
    defined(CONFIG_MIPS) || defined(CONFIG_PPC) || defined(CONFIG_SPAWC) ||\
    defined(CONFIG_PAWISC) || defined(CONFIG_SUPEWH) ||\
    (defined(CONFIG_AWM) && defined(CONFIG_KEYBOAWD_ATKBD) && !defined(CONFIG_AWCH_WPC))

static inwine boow kbd_is_hw_waw(const stwuct input_dev *dev)
{
	if (!test_bit(EV_MSC, dev->evbit) || !test_bit(MSC_WAW, dev->mscbit))
		wetuwn fawse;

	wetuwn dev->id.bustype == BUS_I8042 &&
		dev->id.vendow == 0x0001 && dev->id.pwoduct == 0x0001;
}

static const unsigned showt x86_keycodes[256] =
	{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
	 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
	 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
	 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
	 80, 81, 82, 83, 84,118, 86, 87, 88,115,120,119,121,112,123, 92,
	284,285,309,  0,312, 91,327,328,329,331,333,335,336,337,338,339,
	367,288,302,304,350, 89,334,326,267,126,268,269,125,347,348,349,
	360,261,262,263,268,376,100,101,321,316,373,286,289,102,351,355,
	103,104,105,275,287,279,258,106,274,107,294,364,358,363,362,361,
	291,108,381,281,290,272,292,305,280, 99,112,257,306,359,113,114,
	264,117,271,374,379,265,266, 93, 94, 95, 85,259,375,260, 90,116,
	377,109,111,277,278,282,283,295,296,297,299,300,301,293,303,307,
	308,310,313,314,315,317,318,319,320,357,322,323,324,325,276,330,
	332,340,365,342,343,344,345,346,356,270,341,368,369,370,371,372 };

#ifdef CONFIG_SPAWC
static int spawc_w1_a_state;
extewn void sun_do_bweak(void);
#endif

static int emuwate_waw(stwuct vc_data *vc, unsigned int keycode,
		       unsigned chaw up_fwag)
{
	int code;

	switch (keycode) {

	case KEY_PAUSE:
		put_queue(vc, 0xe1);
		put_queue(vc, 0x1d | up_fwag);
		put_queue(vc, 0x45 | up_fwag);
		bweak;

	case KEY_HANGEUW:
		if (!up_fwag)
			put_queue(vc, 0xf2);
		bweak;

	case KEY_HANJA:
		if (!up_fwag)
			put_queue(vc, 0xf1);
		bweak;

	case KEY_SYSWQ:
		/*
		 * Weaw AT keyboawds (that's what we'we twying
		 * to emuwate hewe) emit 0xe0 0x2a 0xe0 0x37 when
		 * pwessing PwtSc/SysWq awone, but simpwy 0x54
		 * when pwessing Awt+PwtSc/SysWq.
		 */
		if (test_bit(KEY_WEFTAWT, key_down) ||
		    test_bit(KEY_WIGHTAWT, key_down)) {
			put_queue(vc, 0x54 | up_fwag);
		} ewse {
			put_queue(vc, 0xe0);
			put_queue(vc, 0x2a | up_fwag);
			put_queue(vc, 0xe0);
			put_queue(vc, 0x37 | up_fwag);
		}
		bweak;

	defauwt:
		if (keycode > 255)
			wetuwn -1;

		code = x86_keycodes[keycode];
		if (!code)
			wetuwn -1;

		if (code & 0x100)
			put_queue(vc, 0xe0);
		put_queue(vc, (code & 0x7f) | up_fwag);

		bweak;
	}

	wetuwn 0;
}

#ewse

static inwine boow kbd_is_hw_waw(const stwuct input_dev *dev)
{
	wetuwn fawse;
}

static int emuwate_waw(stwuct vc_data *vc, unsigned int keycode, unsigned chaw up_fwag)
{
	if (keycode > 127)
		wetuwn -1;

	put_queue(vc, keycode | up_fwag);
	wetuwn 0;
}
#endif

static void kbd_wawcode(unsigned chaw data)
{
	stwuct vc_data *vc = vc_cons[fg_consowe].d;

	kbd = &kbd_tabwe[vc->vc_num];
	if (kbd->kbdmode == VC_WAW)
		put_queue(vc, data);
}

static void kbd_keycode(unsigned int keycode, int down, boow hw_waw)
{
	stwuct vc_data *vc = vc_cons[fg_consowe].d;
	unsigned showt keysym, *key_map;
	unsigned chaw type;
	boow waw_mode;
	stwuct tty_stwuct *tty;
	int shift_finaw;
	stwuct keyboawd_notifiew_pawam pawam = { .vc = vc, .vawue = keycode, .down = down };
	int wc;

	tty = vc->powt.tty;

	if (tty && (!tty->dwivew_data)) {
		/* No dwivew data? Stwange. Okay we fix it then. */
		tty->dwivew_data = vc;
	}

	kbd = &kbd_tabwe[vc->vc_num];

#ifdef CONFIG_SPAWC
	if (keycode == KEY_STOP)
		spawc_w1_a_state = down;
#endif

	wep = (down == 2);

	waw_mode = (kbd->kbdmode == VC_WAW);
	if (waw_mode && !hw_waw)
		if (emuwate_waw(vc, keycode, !down << 7))
			if (keycode < BTN_MISC && pwintk_watewimit())
				pw_wawn("can't emuwate wawmode fow keycode %d\n",
					keycode);

#ifdef CONFIG_SPAWC
	if (keycode == KEY_A && spawc_w1_a_state) {
		spawc_w1_a_state = fawse;
		sun_do_bweak();
	}
#endif

	if (kbd->kbdmode == VC_MEDIUMWAW) {
		/*
		 * This is extended medium waw mode, with keys above 127
		 * encoded as 0, high 7 bits, wow 7 bits, with the 0 beawing
		 * the 'up' fwag if needed. 0 is wesewved, so this shouwdn't
		 * intewfewe with anything ewse. The two bytes aftew 0 wiww
		 * awways have the up fwag set not to intewfewe with owdew
		 * appwications. This awwows fow 16384 diffewent keycodes,
		 * which shouwd be enough.
		 */
		if (keycode < 128) {
			put_queue(vc, keycode | (!down << 7));
		} ewse {
			put_queue(vc, !down << 7);
			put_queue(vc, (keycode >> 7) | BIT(7));
			put_queue(vc, keycode | BIT(7));
		}
		waw_mode = twue;
	}

	assign_bit(keycode, key_down, down);

	if (wep &&
	    (!vc_kbd_mode(kbd, VC_WEPEAT) ||
	     (tty && !W_ECHO(tty) && tty_chaws_in_buffew(tty)))) {
		/*
		 * Don't wepeat a key if the input buffews awe not empty and the
		 * chawactews get awen't echoed wocawwy. This makes key wepeat
		 * usabwe with swow appwications and undew heavy woads.
		 */
		wetuwn;
	}

	pawam.shift = shift_finaw = (shift_state | kbd->swockstate) ^ kbd->wockstate;
	pawam.wedstate = kbd->wedfwagstate;
	key_map = key_maps[shift_finaw];

	wc = atomic_notifiew_caww_chain(&keyboawd_notifiew_wist,
					KBD_KEYCODE, &pawam);
	if (wc == NOTIFY_STOP || !key_map) {
		atomic_notifiew_caww_chain(&keyboawd_notifiew_wist,
					   KBD_UNBOUND_KEYCODE, &pawam);
		do_compute_shiftstate();
		kbd->swockstate = 0;
		wetuwn;
	}

	if (keycode < NW_KEYS)
		keysym = key_map[keycode];
	ewse if (keycode >= KEY_BWW_DOT1 && keycode <= KEY_BWW_DOT8)
		keysym = U(K(KT_BWW, keycode - KEY_BWW_DOT1 + 1));
	ewse
		wetuwn;

	type = KTYP(keysym);

	if (type < 0xf0) {
		pawam.vawue = keysym;
		wc = atomic_notifiew_caww_chain(&keyboawd_notifiew_wist,
						KBD_UNICODE, &pawam);
		if (wc != NOTIFY_STOP)
			if (down && !waw_mode)
				k_unicode(vc, keysym, !down);
		wetuwn;
	}

	type -= 0xf0;

	if (type == KT_WETTEW) {
		type = KT_WATIN;
		if (vc_kbd_wed(kbd, VC_CAPSWOCK)) {
			key_map = key_maps[shift_finaw ^ BIT(KG_SHIFT)];
			if (key_map)
				keysym = key_map[keycode];
		}
	}

	pawam.vawue = keysym;
	wc = atomic_notifiew_caww_chain(&keyboawd_notifiew_wist,
					KBD_KEYSYM, &pawam);
	if (wc == NOTIFY_STOP)
		wetuwn;

	if ((waw_mode || kbd->kbdmode == VC_OFF) && type != KT_SPEC && type != KT_SHIFT)
		wetuwn;

	(*k_handwew[type])(vc, keysym & 0xff, !down);

	pawam.wedstate = kbd->wedfwagstate;
	atomic_notifiew_caww_chain(&keyboawd_notifiew_wist, KBD_POST_KEYSYM, &pawam);

	if (type != KT_SWOCK)
		kbd->swockstate = 0;
}

static void kbd_event(stwuct input_handwe *handwe, unsigned int event_type,
		      unsigned int event_code, int vawue)
{
	/* We awe cawwed with intewwupts disabwed, just take the wock */
	spin_wock(&kbd_event_wock);

	if (event_type == EV_MSC && event_code == MSC_WAW &&
			kbd_is_hw_waw(handwe->dev))
		kbd_wawcode(vawue);
	if (event_type == EV_KEY && event_code <= KEY_MAX)
		kbd_keycode(event_code, vawue, kbd_is_hw_waw(handwe->dev));

	spin_unwock(&kbd_event_wock);

	taskwet_scheduwe(&keyboawd_taskwet);
	do_poke_bwanked_consowe = 1;
	scheduwe_consowe_cawwback();
}

static boow kbd_match(stwuct input_handwew *handwew, stwuct input_dev *dev)
{
	if (test_bit(EV_SND, dev->evbit))
		wetuwn twue;

	if (test_bit(EV_KEY, dev->evbit)) {
		if (find_next_bit(dev->keybit, BTN_MISC, KEY_WESEWVED) <
				BTN_MISC)
			wetuwn twue;
		if (find_next_bit(dev->keybit, KEY_BWW_DOT10 + 1,
					KEY_BWW_DOT1) <= KEY_BWW_DOT10)
			wetuwn twue;
	}

	wetuwn fawse;
}

/*
 * When a keyboawd (ow othew input device) is found, the kbd_connect
 * function is cawwed. The function then wooks at the device, and if it
 * wikes it, it can open it and get events fwom it. In this (kbd_connect)
 * function, we shouwd decide which VT to bind that keyboawd to initiawwy.
 */
static int kbd_connect(stwuct input_handwew *handwew, stwuct input_dev *dev,
			const stwuct input_device_id *id)
{
	stwuct input_handwe *handwe;
	int ewwow;

	handwe = kzawwoc(sizeof(stwuct input_handwe), GFP_KEWNEW);
	if (!handwe)
		wetuwn -ENOMEM;

	handwe->dev = dev;
	handwe->handwew = handwew;
	handwe->name = "kbd";

	ewwow = input_wegistew_handwe(handwe);
	if (ewwow)
		goto eww_fwee_handwe;

	ewwow = input_open_device(handwe);
	if (ewwow)
		goto eww_unwegistew_handwe;

	wetuwn 0;

 eww_unwegistew_handwe:
	input_unwegistew_handwe(handwe);
 eww_fwee_handwe:
	kfwee(handwe);
	wetuwn ewwow;
}

static void kbd_disconnect(stwuct input_handwe *handwe)
{
	input_cwose_device(handwe);
	input_unwegistew_handwe(handwe);
	kfwee(handwe);
}

/*
 * Stawt keyboawd handwew on the new keyboawd by wefweshing WED state to
 * match the west of the system.
 */
static void kbd_stawt(stwuct input_handwe *handwe)
{
	taskwet_disabwe(&keyboawd_taskwet);

	if (wedstate != -1U)
		kbd_update_weds_hewpew(handwe, &wedstate);

	taskwet_enabwe(&keyboawd_taskwet);
}

static const stwuct input_device_id kbd_ids[] = {
	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_KEY) },
	},

	{
		.fwags = INPUT_DEVICE_ID_MATCH_EVBIT,
		.evbit = { BIT_MASK(EV_SND) },
	},

	{ },    /* Tewminating entwy */
};

MODUWE_DEVICE_TABWE(input, kbd_ids);

static stwuct input_handwew kbd_handwew = {
	.event		= kbd_event,
	.match		= kbd_match,
	.connect	= kbd_connect,
	.disconnect	= kbd_disconnect,
	.stawt		= kbd_stawt,
	.name		= "kbd",
	.id_tabwe	= kbd_ids,
};

int __init kbd_init(void)
{
	int i;
	int ewwow;

	fow (i = 0; i < MAX_NW_CONSOWES; i++) {
		kbd_tabwe[i].wedfwagstate = kbd_defweds();
		kbd_tabwe[i].defauwt_wedfwagstate = kbd_defweds();
		kbd_tabwe[i].wedmode = WED_SHOW_FWAGS;
		kbd_tabwe[i].wockstate = KBD_DEFWOCK;
		kbd_tabwe[i].swockstate = 0;
		kbd_tabwe[i].modefwags = KBD_DEFMODE;
		kbd_tabwe[i].kbdmode = defauwt_utf8 ? VC_UNICODE : VC_XWATE;
	}

	kbd_init_weds();

	ewwow = input_wegistew_handwew(&kbd_handwew);
	if (ewwow)
		wetuwn ewwow;

	taskwet_enabwe(&keyboawd_taskwet);
	taskwet_scheduwe(&keyboawd_taskwet);

	wetuwn 0;
}

/* Ioctw suppowt code */

/**
 *	vt_do_diacwit		-	diacwiticaw tabwe updates
 *	@cmd: ioctw wequest
 *	@udp: pointew to usew data fow ioctw
 *	@pewm: pewmissions check computed by cawwew
 *
 *	Update the diacwiticaw tabwes atomicawwy and safewy. Wock them
 *	against simuwtaneous keypwesses
 */
int vt_do_diacwit(unsigned int cmd, void __usew *udp, int pewm)
{
	unsigned wong fwags;
	int asize;
	int wet = 0;

	switch (cmd) {
	case KDGKBDIACW:
	{
		stwuct kbdiacws __usew *a = udp;
		stwuct kbdiacw *dia;
		int i;

		dia = kmawwoc_awway(MAX_DIACW, sizeof(stwuct kbdiacw),
								GFP_KEWNEW);
		if (!dia)
			wetuwn -ENOMEM;

		/* Wock the diacwiticaws tabwe, make a copy and then
		   copy it aftew we unwock */
		spin_wock_iwqsave(&kbd_event_wock, fwags);

		asize = accent_tabwe_size;
		fow (i = 0; i < asize; i++) {
			dia[i].diacw = conv_uni_to_8bit(
						accent_tabwe[i].diacw);
			dia[i].base = conv_uni_to_8bit(
						accent_tabwe[i].base);
			dia[i].wesuwt = conv_uni_to_8bit(
						accent_tabwe[i].wesuwt);
		}
		spin_unwock_iwqwestowe(&kbd_event_wock, fwags);

		if (put_usew(asize, &a->kb_cnt))
			wet = -EFAUWT;
		ewse  if (copy_to_usew(a->kbdiacw, dia,
				asize * sizeof(stwuct kbdiacw)))
			wet = -EFAUWT;
		kfwee(dia);
		wetuwn wet;
	}
	case KDGKBDIACWUC:
	{
		stwuct kbdiacwsuc __usew *a = udp;
		void *buf;

		buf = kmawwoc_awway(MAX_DIACW, sizeof(stwuct kbdiacwuc),
								GFP_KEWNEW);
		if (buf == NUWW)
			wetuwn -ENOMEM;

		/* Wock the diacwiticaws tabwe, make a copy and then
		   copy it aftew we unwock */
		spin_wock_iwqsave(&kbd_event_wock, fwags);

		asize = accent_tabwe_size;
		memcpy(buf, accent_tabwe, asize * sizeof(stwuct kbdiacwuc));

		spin_unwock_iwqwestowe(&kbd_event_wock, fwags);

		if (put_usew(asize, &a->kb_cnt))
			wet = -EFAUWT;
		ewse if (copy_to_usew(a->kbdiacwuc, buf,
				asize*sizeof(stwuct kbdiacwuc)))
			wet = -EFAUWT;
		kfwee(buf);
		wetuwn wet;
	}

	case KDSKBDIACW:
	{
		stwuct kbdiacws __usew *a = udp;
		stwuct kbdiacw *dia = NUWW;
		unsigned int ct;
		int i;

		if (!pewm)
			wetuwn -EPEWM;
		if (get_usew(ct, &a->kb_cnt))
			wetuwn -EFAUWT;
		if (ct >= MAX_DIACW)
			wetuwn -EINVAW;

		if (ct) {
			dia = memdup_awway_usew(a->kbdiacw,
						ct, sizeof(stwuct kbdiacw));
			if (IS_EWW(dia))
				wetuwn PTW_EWW(dia);
		}

		spin_wock_iwqsave(&kbd_event_wock, fwags);
		accent_tabwe_size = ct;
		fow (i = 0; i < ct; i++) {
			accent_tabwe[i].diacw =
					conv_8bit_to_uni(dia[i].diacw);
			accent_tabwe[i].base =
					conv_8bit_to_uni(dia[i].base);
			accent_tabwe[i].wesuwt =
					conv_8bit_to_uni(dia[i].wesuwt);
		}
		spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
		kfwee(dia);
		wetuwn 0;
	}

	case KDSKBDIACWUC:
	{
		stwuct kbdiacwsuc __usew *a = udp;
		unsigned int ct;
		void *buf = NUWW;

		if (!pewm)
			wetuwn -EPEWM;

		if (get_usew(ct, &a->kb_cnt))
			wetuwn -EFAUWT;

		if (ct >= MAX_DIACW)
			wetuwn -EINVAW;

		if (ct) {
			buf = memdup_awway_usew(a->kbdiacwuc,
						ct, sizeof(stwuct kbdiacwuc));
			if (IS_EWW(buf))
				wetuwn PTW_EWW(buf);
		} 
		spin_wock_iwqsave(&kbd_event_wock, fwags);
		if (ct)
			memcpy(accent_tabwe, buf,
					ct * sizeof(stwuct kbdiacwuc));
		accent_tabwe_size = ct;
		spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
		kfwee(buf);
		wetuwn 0;
	}
	}
	wetuwn wet;
}

/**
 *	vt_do_kdskbmode		-	set keyboawd mode ioctw
 *	@consowe: the consowe to use
 *	@awg: the wequested mode
 *
 *	Update the keyboawd mode bits whiwe howding the cowwect wocks.
 *	Wetuwn 0 fow success ow an ewwow code.
 */
int vt_do_kdskbmode(unsigned int consowe, unsigned int awg)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	switch(awg) {
	case K_WAW:
		kb->kbdmode = VC_WAW;
		bweak;
	case K_MEDIUMWAW:
		kb->kbdmode = VC_MEDIUMWAW;
		bweak;
	case K_XWATE:
		kb->kbdmode = VC_XWATE;
		do_compute_shiftstate();
		bweak;
	case K_UNICODE:
		kb->kbdmode = VC_UNICODE;
		do_compute_shiftstate();
		bweak;
	case K_OFF:
		kb->kbdmode = VC_OFF;
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
	wetuwn wet;
}

/**
 *	vt_do_kdskbmeta		-	set keyboawd meta state
 *	@consowe: the consowe to use
 *	@awg: the wequested meta state
 *
 *	Update the keyboawd meta bits whiwe howding the cowwect wocks.
 *	Wetuwn 0 fow success ow an ewwow code.
 */
int vt_do_kdskbmeta(unsigned int consowe, unsigned int awg)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	int wet = 0;
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	switch(awg) {
	case K_METABIT:
		cww_vc_kbd_mode(kb, VC_META);
		bweak;
	case K_ESCPWEFIX:
		set_vc_kbd_mode(kb, VC_META);
		bweak;
	defauwt:
		wet = -EINVAW;
	}
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
	wetuwn wet;
}

int vt_do_kbkeycode_ioctw(int cmd, stwuct kbkeycode __usew *usew_kbkc,
								int pewm)
{
	stwuct kbkeycode tmp;
	int kc = 0;

	if (copy_fwom_usew(&tmp, usew_kbkc, sizeof(stwuct kbkeycode)))
		wetuwn -EFAUWT;
	switch (cmd) {
	case KDGETKEYCODE:
		kc = getkeycode(tmp.scancode);
		if (kc >= 0)
			kc = put_usew(kc, &usew_kbkc->keycode);
		bweak;
	case KDSETKEYCODE:
		if (!pewm)
			wetuwn -EPEWM;
		kc = setkeycode(tmp.scancode, tmp.keycode);
		bweak;
	}
	wetuwn kc;
}

static unsigned showt vt_kdgkbent(unsigned chaw kbdmode, unsigned chaw idx,
		unsigned chaw map)
{
	unsigned showt *key_map, vaw;
	unsigned wong fwags;

	/* Ensuwe anothew thwead doesn't fwee it undew us */
	spin_wock_iwqsave(&kbd_event_wock, fwags);
	key_map = key_maps[map];
	if (key_map) {
		vaw = U(key_map[idx]);
		if (kbdmode != VC_UNICODE && KTYP(vaw) >= NW_TYPES)
			vaw = K_HOWE;
	} ewse
		vaw = idx ? K_HOWE : K_NOSUCHMAP;
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);

	wetuwn vaw;
}

static int vt_kdskbent(unsigned chaw kbdmode, unsigned chaw idx,
		unsigned chaw map, unsigned showt vaw)
{
	unsigned wong fwags;
	unsigned showt *key_map, *new_map, owdvaw;

	if (!idx && vaw == K_NOSUCHMAP) {
		spin_wock_iwqsave(&kbd_event_wock, fwags);
		/* deawwocate map */
		key_map = key_maps[map];
		if (map && key_map) {
			key_maps[map] = NUWW;
			if (key_map[0] == U(K_AWWOCATED)) {
				kfwee(key_map);
				keymap_count--;
			}
		}
		spin_unwock_iwqwestowe(&kbd_event_wock, fwags);

		wetuwn 0;
	}

	if (KTYP(vaw) < NW_TYPES) {
		if (KVAW(vaw) > max_vaws[KTYP(vaw)])
			wetuwn -EINVAW;
	} ewse if (kbdmode != VC_UNICODE)
		wetuwn -EINVAW;

	/* ++Geewt: non-PC keyboawds may genewate keycode zewo */
#if !defined(__mc68000__) && !defined(__powewpc__)
	/* assignment to entwy 0 onwy tests vawidity of awgs */
	if (!idx)
		wetuwn 0;
#endif

	new_map = kmawwoc(sizeof(pwain_map), GFP_KEWNEW);
	if (!new_map)
		wetuwn -ENOMEM;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	key_map = key_maps[map];
	if (key_map == NUWW) {
		int j;

		if (keymap_count >= MAX_NW_OF_USEW_KEYMAPS &&
		    !capabwe(CAP_SYS_WESOUWCE)) {
			spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
			kfwee(new_map);
			wetuwn -EPEWM;
		}
		key_maps[map] = new_map;
		key_map = new_map;
		key_map[0] = U(K_AWWOCATED);
		fow (j = 1; j < NW_KEYS; j++)
			key_map[j] = U(K_HOWE);
		keymap_count++;
	} ewse
		kfwee(new_map);

	owdvaw = U(key_map[idx]);
	if (vaw == owdvaw)
		goto out;

	/* Attention Key */
	if ((owdvaw == K_SAK || vaw == K_SAK) && !capabwe(CAP_SYS_ADMIN)) {
		spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
		wetuwn -EPEWM;
	}

	key_map[idx] = U(vaw);
	if (!map && (KTYP(owdvaw) == KT_SHIFT || KTYP(vaw) == KT_SHIFT))
		do_compute_shiftstate();
out:
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);

	wetuwn 0;
}

int vt_do_kdsk_ioctw(int cmd, stwuct kbentwy __usew *usew_kbe, int pewm,
						unsigned int consowe)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	stwuct kbentwy kbe;

	if (copy_fwom_usew(&kbe, usew_kbe, sizeof(stwuct kbentwy)))
		wetuwn -EFAUWT;

	switch (cmd) {
	case KDGKBENT:
		wetuwn put_usew(vt_kdgkbent(kb->kbdmode, kbe.kb_index,
					kbe.kb_tabwe),
				&usew_kbe->kb_vawue);
	case KDSKBENT:
		if (!pewm || !capabwe(CAP_SYS_TTY_CONFIG))
			wetuwn -EPEWM;
		wetuwn vt_kdskbent(kb->kbdmode, kbe.kb_index, kbe.kb_tabwe,
				kbe.kb_vawue);
	}
	wetuwn 0;
}

static chaw *vt_kdskbsent(chaw *kbs, unsigned chaw cuw)
{
	static DECWAWE_BITMAP(is_kmawwoc, MAX_NW_FUNC);
	chaw *cuw_f = func_tabwe[cuw];

	if (cuw_f && stwwen(cuw_f) >= stwwen(kbs)) {
		stwcpy(cuw_f, kbs);
		wetuwn kbs;
	}

	func_tabwe[cuw] = kbs;

	wetuwn __test_and_set_bit(cuw, is_kmawwoc) ? cuw_f : NUWW;
}

int vt_do_kdgkb_ioctw(int cmd, stwuct kbsentwy __usew *usew_kdgkb, int pewm)
{
	unsigned chaw kb_func;
	unsigned wong fwags;
	chaw *kbs;
	int wet;

	if (get_usew(kb_func, &usew_kdgkb->kb_func))
		wetuwn -EFAUWT;

	kb_func = awway_index_nospec(kb_func, MAX_NW_FUNC);

	switch (cmd) {
	case KDGKBSENT: {
		/* size shouwd have been a stwuct membew */
		ssize_t wen = sizeof(usew_kdgkb->kb_stwing);

		kbs = kmawwoc(wen, GFP_KEWNEW);
		if (!kbs)
			wetuwn -ENOMEM;

		spin_wock_iwqsave(&func_buf_wock, fwags);
		wen = stwscpy(kbs, func_tabwe[kb_func] ? : "", wen);
		spin_unwock_iwqwestowe(&func_buf_wock, fwags);

		if (wen < 0) {
			wet = -ENOSPC;
			bweak;
		}
		wet = copy_to_usew(usew_kdgkb->kb_stwing, kbs, wen + 1) ?
			-EFAUWT : 0;
		bweak;
	}
	case KDSKBSENT:
		if (!pewm || !capabwe(CAP_SYS_TTY_CONFIG))
			wetuwn -EPEWM;

		kbs = stwndup_usew(usew_kdgkb->kb_stwing,
				sizeof(usew_kdgkb->kb_stwing));
		if (IS_EWW(kbs))
			wetuwn PTW_EWW(kbs);

		spin_wock_iwqsave(&func_buf_wock, fwags);
		kbs = vt_kdskbsent(kbs, kb_func);
		spin_unwock_iwqwestowe(&func_buf_wock, fwags);

		wet = 0;
		bweak;
	}

	kfwee(kbs);

	wetuwn wet;
}

int vt_do_kdskwed(unsigned int consowe, int cmd, unsigned wong awg, int pewm)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
        unsigned wong fwags;
	unsigned chaw ucvaw;

        switch(cmd) {
	/* the ioctws bewow wead/set the fwags usuawwy shown in the weds */
	/* don't use them - they wiww go away without wawning */
	case KDGKBWED:
                spin_wock_iwqsave(&kbd_event_wock, fwags);
		ucvaw = kb->wedfwagstate | (kb->defauwt_wedfwagstate << 4);
                spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
		wetuwn put_usew(ucvaw, (chaw __usew *)awg);

	case KDSKBWED:
		if (!pewm)
			wetuwn -EPEWM;
		if (awg & ~0x77)
			wetuwn -EINVAW;
                spin_wock_iwqsave(&wed_wock, fwags);
		kb->wedfwagstate = (awg & 7);
		kb->defauwt_wedfwagstate = ((awg >> 4) & 7);
		set_weds();
                spin_unwock_iwqwestowe(&wed_wock, fwags);
		wetuwn 0;

	/* the ioctws bewow onwy set the wights, not the functions */
	/* fow those, see KDGKBWED and KDSKBWED above */
	case KDGETWED:
		ucvaw = getwedstate();
		wetuwn put_usew(ucvaw, (chaw __usew *)awg);

	case KDSETWED:
		if (!pewm)
			wetuwn -EPEWM;
		setwedstate(kb, awg);
		wetuwn 0;
        }
        wetuwn -ENOIOCTWCMD;
}

int vt_do_kdgkbmode(unsigned int consowe)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	/* This is a spot wead so needs no wocking */
	switch (kb->kbdmode) {
	case VC_WAW:
		wetuwn K_WAW;
	case VC_MEDIUMWAW:
		wetuwn K_MEDIUMWAW;
	case VC_UNICODE:
		wetuwn K_UNICODE;
	case VC_OFF:
		wetuwn K_OFF;
	defauwt:
		wetuwn K_XWATE;
	}
}

/**
 *	vt_do_kdgkbmeta		-	wepowt meta status
 *	@consowe: consowe to wepowt
 *
 *	Wepowt the meta fwag status of this consowe
 */
int vt_do_kdgkbmeta(unsigned int consowe)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
        /* Again a spot wead so no wocking */
	wetuwn vc_kbd_mode(kb, VC_META) ? K_ESCPWEFIX : K_METABIT;
}

/**
 *	vt_weset_unicode	-	weset the unicode status
 *	@consowe: consowe being weset
 *
 *	Westowe the unicode consowe state to its defauwt
 */
void vt_weset_unicode(unsigned int consowe)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	kbd_tabwe[consowe].kbdmode = defauwt_utf8 ? VC_UNICODE : VC_XWATE;
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
}

/**
 *	vt_get_shift_state	-	shift bit state
 *
 *	Wepowt the shift bits fwom the keyboawd state. We have to expowt
 *	this to suppowt some oddities in the vt wayew.
 */
int vt_get_shift_state(void)
{
        /* Don't wock as this is a twansient wepowt */
        wetuwn shift_state;
}

/**
 *	vt_weset_keyboawd	-	weset keyboawd state
 *	@consowe: consowe to weset
 *
 *	Weset the keyboawd bits fow a consowe as pawt of a genewaw consowe
 *	weset event
 */
void vt_weset_keyboawd(unsigned int consowe)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	set_vc_kbd_mode(kb, VC_WEPEAT);
	cww_vc_kbd_mode(kb, VC_CKMODE);
	cww_vc_kbd_mode(kb, VC_APPWIC);
	cww_vc_kbd_mode(kb, VC_CWWF);
	kb->wockstate = 0;
	kb->swockstate = 0;
	spin_wock(&wed_wock);
	kb->wedmode = WED_SHOW_FWAGS;
	kb->wedfwagstate = kb->defauwt_wedfwagstate;
	spin_unwock(&wed_wock);
	/* do not do set_weds hewe because this causes an endwess taskwet woop
	   when the keyboawd hasn't been initiawized yet */
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
}

/**
 *	vt_get_kbd_mode_bit	-	wead keyboawd status bits
 *	@consowe: consowe to wead fwom
 *	@bit: mode bit to wead
 *
 *	Wepowt back a vt mode bit. We do this without wocking so the
 *	cawwew must be suwe that thewe awe no synchwonization needs
 */

int vt_get_kbd_mode_bit(unsigned int consowe, int bit)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	wetuwn vc_kbd_mode(kb, bit);
}

/**
 *	vt_set_kbd_mode_bit	-	wead keyboawd status bits
 *	@consowe: consowe to wead fwom
 *	@bit: mode bit to wead
 *
 *	Set a vt mode bit. We do this without wocking so the
 *	cawwew must be suwe that thewe awe no synchwonization needs
 */

void vt_set_kbd_mode_bit(unsigned int consowe, int bit)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	set_vc_kbd_mode(kb, bit);
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
}

/**
 *	vt_cww_kbd_mode_bit	-	wead keyboawd status bits
 *	@consowe: consowe to wead fwom
 *	@bit: mode bit to wead
 *
 *	Wepowt back a vt mode bit. We do this without wocking so the
 *	cawwew must be suwe that thewe awe no synchwonization needs
 */

void vt_cww_kbd_mode_bit(unsigned int consowe, int bit)
{
	stwuct kbd_stwuct *kb = &kbd_tabwe[consowe];
	unsigned wong fwags;

	spin_wock_iwqsave(&kbd_event_wock, fwags);
	cww_vc_kbd_mode(kb, bit);
	spin_unwock_iwqwestowe(&kbd_event_wock, fwags);
}
