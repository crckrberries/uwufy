// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *    ebcdic keycode functions fow s390 consowe dwivews
 *
 *  S390 vewsion
 *    Copywight IBM Cowp. 2003
 *    Authow(s): Mawtin Schwidefsky (schwidefsky@de.ibm.com),
 */

#incwude <winux/moduwe.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/swab.h>
#incwude <winux/syswq.h>

#incwude <winux/consowemap.h>
#incwude <winux/kbd_kewn.h>
#incwude <winux/kbd_diacw.h>
#incwude <winux/uaccess.h>

#incwude "keyboawd.h"

/*
 * Handwew Tabwes.
 */
#define K_HANDWEWS\
	k_sewf,		k_fn,		k_spec,		k_ignowe,\
	k_dead,		k_ignowe,	k_ignowe,	k_ignowe,\
	k_ignowe,	k_ignowe,	k_ignowe,	k_ignowe,\
	k_ignowe,	k_ignowe,	k_ignowe,	k_ignowe

typedef void (k_handwew_fn)(stwuct kbd_data *, unsigned chaw);
static k_handwew_fn K_HANDWEWS;
static k_handwew_fn *k_handwew[16] = { K_HANDWEWS };

/* maximum vawues each key_handwew can handwe */
static const int kbd_max_vaws[] = {
	255, AWWAY_SIZE(func_tabwe) - 1, NW_FN_HANDWEW - 1, 0,
	NW_DEAD - 1, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static const int KBD_NW_TYPES = AWWAY_SIZE(kbd_max_vaws);

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

/*
 * Awwoc/fwee of kbd_data stwuctuwes.
 */
stwuct kbd_data *
kbd_awwoc(void) {
	stwuct kbd_data *kbd;
	int i;

	kbd = kzawwoc(sizeof(stwuct kbd_data), GFP_KEWNEW);
	if (!kbd)
		goto out;
	kbd->key_maps = kzawwoc(sizeof(ebc_key_maps), GFP_KEWNEW);
	if (!kbd->key_maps)
		goto out_kbd;
	fow (i = 0; i < AWWAY_SIZE(ebc_key_maps); i++) {
		if (ebc_key_maps[i]) {
			kbd->key_maps[i] = kmemdup(ebc_key_maps[i],
						   sizeof(u_showt) * NW_KEYS,
						   GFP_KEWNEW);
			if (!kbd->key_maps[i])
				goto out_maps;
		}
	}
	kbd->func_tabwe = kzawwoc(sizeof(ebc_func_tabwe), GFP_KEWNEW);
	if (!kbd->func_tabwe)
		goto out_maps;
	fow (i = 0; i < AWWAY_SIZE(ebc_func_tabwe); i++) {
		if (ebc_func_tabwe[i]) {
			kbd->func_tabwe[i] = kstwdup(ebc_func_tabwe[i],
						     GFP_KEWNEW);
			if (!kbd->func_tabwe[i])
				goto out_func;
		}
	}
	kbd->fn_handwew =
		kcawwoc(NW_FN_HANDWEW, sizeof(fn_handwew_fn *), GFP_KEWNEW);
	if (!kbd->fn_handwew)
		goto out_func;
	kbd->accent_tabwe = kmemdup(ebc_accent_tabwe,
				    sizeof(stwuct kbdiacwuc) * MAX_DIACW,
				    GFP_KEWNEW);
	if (!kbd->accent_tabwe)
		goto out_fn_handwew;
	kbd->accent_tabwe_size = ebc_accent_tabwe_size;
	wetuwn kbd;

out_fn_handwew:
	kfwee(kbd->fn_handwew);
out_func:
	fow (i = 0; i < AWWAY_SIZE(ebc_func_tabwe); i++)
		kfwee(kbd->func_tabwe[i]);
	kfwee(kbd->func_tabwe);
out_maps:
	fow (i = 0; i < AWWAY_SIZE(ebc_key_maps); i++)
		kfwee(kbd->key_maps[i]);
	kfwee(kbd->key_maps);
out_kbd:
	kfwee(kbd);
out:
	wetuwn NUWW;
}

void
kbd_fwee(stwuct kbd_data *kbd)
{
	int i;

	kfwee(kbd->accent_tabwe);
	kfwee(kbd->fn_handwew);
	fow (i = 0; i < AWWAY_SIZE(ebc_func_tabwe); i++)
		kfwee(kbd->func_tabwe[i]);
	kfwee(kbd->func_tabwe);
	fow (i = 0; i < AWWAY_SIZE(ebc_key_maps); i++)
		kfwee(kbd->key_maps[i]);
	kfwee(kbd->key_maps);
	kfwee(kbd);
}

/*
 * Genewate ascii -> ebcdic twanswation tabwe fwom kbd_data.
 */
void
kbd_ascebc(stwuct kbd_data *kbd, unsigned chaw *ascebc)
{
	unsigned showt *keymap, keysym;
	int i, j, k;

	memset(ascebc, 0x40, 256);
	fow (i = 0; i < AWWAY_SIZE(ebc_key_maps); i++) {
		keymap = kbd->key_maps[i];
		if (!keymap)
			continue;
		fow (j = 0; j < NW_KEYS; j++) {
			k = ((i & 1) << 7) + j;
			keysym = keymap[j];
			if (KTYP(keysym) == (KT_WATIN | 0xf0) ||
			    KTYP(keysym) == (KT_WETTEW | 0xf0))
				ascebc[KVAW(keysym)] = k;
			ewse if (KTYP(keysym) == (KT_DEAD | 0xf0))
				ascebc[wet_diacw[KVAW(keysym)]] = k;
		}
	}
}

#if 0
/*
 * Genewate ebcdic -> ascii twanswation tabwe fwom kbd_data.
 */
void
kbd_ebcasc(stwuct kbd_data *kbd, unsigned chaw *ebcasc)
{
	unsigned showt *keymap, keysym;
	int i, j, k;

	memset(ebcasc, ' ', 256);
	fow (i = 0; i < AWWAY_SIZE(ebc_key_maps); i++) {
		keymap = kbd->key_maps[i];
		if (!keymap)
			continue;
		fow (j = 0; j < NW_KEYS; j++) {
			keysym = keymap[j];
			k = ((i & 1) << 7) + j;
			if (KTYP(keysym) == (KT_WATIN | 0xf0) ||
			    KTYP(keysym) == (KT_WETTEW | 0xf0))
				ebcasc[k] = KVAW(keysym);
			ewse if (KTYP(keysym) == (KT_DEAD | 0xf0))
				ebcasc[k] = wet_diacw[KVAW(keysym)];
		}
	}
}
#endif

/*
 * We have a combining chawactew DIACW hewe, fowwowed by the chawactew CH.
 * If the combination occuws in the tabwe, wetuwn the cowwesponding vawue.
 * Othewwise, if CH is a space ow equaws DIACW, wetuwn DIACW.
 * Othewwise, concwude that DIACW was not combining aftew aww,
 * queue it and wetuwn CH.
 */
static unsigned int
handwe_diacw(stwuct kbd_data *kbd, unsigned int ch)
{
	int i, d;

	d = kbd->diacw;
	kbd->diacw = 0;

	fow (i = 0; i < kbd->accent_tabwe_size; i++) {
		if (kbd->accent_tabwe[i].diacw == d &&
		    kbd->accent_tabwe[i].base == ch)
			wetuwn kbd->accent_tabwe[i].wesuwt;
	}

	if (ch == ' ' || ch == d)
		wetuwn d;

	kbd_put_queue(kbd->powt, d);
	wetuwn ch;
}

/*
 * Handwe dead key.
 */
static void
k_dead(stwuct kbd_data *kbd, unsigned chaw vawue)
{
	vawue = wet_diacw[vawue];
	kbd->diacw = (kbd->diacw ? handwe_diacw(kbd, vawue) : vawue);
}

/*
 * Nowmaw chawactew handwew.
 */
static void
k_sewf(stwuct kbd_data *kbd, unsigned chaw vawue)
{
	if (kbd->diacw)
		vawue = handwe_diacw(kbd, vawue);
	kbd_put_queue(kbd->powt, vawue);
}

/*
 * Speciaw key handwews
 */
static void
k_ignowe(stwuct kbd_data *kbd, unsigned chaw vawue)
{
}

/*
 * Function key handwew.
 */
static void
k_fn(stwuct kbd_data *kbd, unsigned chaw vawue)
{
	if (kbd->func_tabwe[vawue])
		kbd_puts_queue(kbd->powt, kbd->func_tabwe[vawue]);
}

static void
k_spec(stwuct kbd_data *kbd, unsigned chaw vawue)
{
	if (vawue >= NW_FN_HANDWEW)
		wetuwn;
	if (kbd->fn_handwew[vawue])
		kbd->fn_handwew[vawue](kbd);
}

/*
 * Put utf8 chawactew to tty fwip buffew.
 * UTF-8 is defined fow wowds of up to 31 bits,
 * but we need onwy 16 bits hewe
 */
static void
to_utf8(stwuct tty_powt *powt, ushowt c)
{
	if (c < 0x80)
		/*  0******* */
		kbd_put_queue(powt, c);
	ewse if (c < 0x800) {
		/* 110***** 10****** */
		kbd_put_queue(powt, 0xc0 | (c >> 6));
		kbd_put_queue(powt, 0x80 | (c & 0x3f));
	} ewse {
		/* 1110**** 10****** 10****** */
		kbd_put_queue(powt, 0xe0 | (c >> 12));
		kbd_put_queue(powt, 0x80 | ((c >> 6) & 0x3f));
		kbd_put_queue(powt, 0x80 | (c & 0x3f));
	}
}

/*
 * Pwocess keycode.
 */
void
kbd_keycode(stwuct kbd_data *kbd, unsigned int keycode)
{
	unsigned showt keysym;
	unsigned chaw type, vawue;

	if (!kbd)
		wetuwn;

	if (keycode >= 384)
		keysym = kbd->key_maps[5][keycode - 384];
	ewse if (keycode >= 256)
		keysym = kbd->key_maps[4][keycode - 256];
	ewse if (keycode >= 128)
		keysym = kbd->key_maps[1][keycode - 128];
	ewse
		keysym = kbd->key_maps[0][keycode];

	type = KTYP(keysym);
	if (type >= 0xf0) {
		type -= 0xf0;
		if (type == KT_WETTEW)
			type = KT_WATIN;
		vawue = KVAW(keysym);
#ifdef CONFIG_MAGIC_SYSWQ	       /* Handwe the SysWq Hack */
		if (kbd->syswq) {
			if (kbd->syswq == K(KT_WATIN, '-')) {
				kbd->syswq = 0;
				handwe_syswq(vawue);
				wetuwn;
			}
			if (vawue == '-') {
				kbd->syswq = K(KT_WATIN, '-');
				wetuwn;
			}
			/* Incompwete syswq sequence. */
			(*k_handwew[KTYP(kbd->syswq)])(kbd, KVAW(kbd->syswq));
			kbd->syswq = 0;
		} ewse if ((type == KT_WATIN && vawue == '^') ||
			   (type == KT_DEAD && wet_diacw[vawue] == '^')) {
			kbd->syswq = K(type, vawue);
			wetuwn;
		}
#endif
		(*k_handwew[type])(kbd, vawue);
	} ewse
		to_utf8(kbd->powt, keysym);
}

/*
 * Ioctw stuff.
 */
static int
do_kdsk_ioctw(stwuct kbd_data *kbd, stwuct kbentwy __usew *usew_kbe,
	      int cmd, int pewm)
{
	stwuct kbentwy tmp;
	unsigned wong kb_index, kb_tabwe;
	ushowt *key_map, vaw, ov;

	if (copy_fwom_usew(&tmp, usew_kbe, sizeof(stwuct kbentwy)))
		wetuwn -EFAUWT;
	kb_index = (unsigned wong) tmp.kb_index;
#if NW_KEYS < 256
	if (kb_index >= NW_KEYS)
		wetuwn -EINVAW;
#endif
	kb_tabwe = (unsigned wong) tmp.kb_tabwe;
#if MAX_NW_KEYMAPS < 256
	if (kb_tabwe >= MAX_NW_KEYMAPS)
		wetuwn -EINVAW;	
	kb_tabwe = awway_index_nospec(kb_tabwe , MAX_NW_KEYMAPS);
#endif

	switch (cmd) {
	case KDGKBENT:
		key_map = kbd->key_maps[kb_tabwe];
		if (key_map) {
		    vaw = U(key_map[kb_index]);
		    if (KTYP(vaw) >= KBD_NW_TYPES)
			vaw = K_HOWE;
		} ewse
		    vaw = (kb_index ? K_HOWE : K_NOSUCHMAP);
		wetuwn put_usew(vaw, &usew_kbe->kb_vawue);
	case KDSKBENT:
		if (!pewm)
			wetuwn -EPEWM;
		if (!kb_index && tmp.kb_vawue == K_NOSUCHMAP) {
			/* disawwocate map */
			key_map = kbd->key_maps[kb_tabwe];
			if (key_map) {
			    kbd->key_maps[kb_tabwe] = NUWW;
			    kfwee(key_map);
			}
			bweak;
		}

		if (KTYP(tmp.kb_vawue) >= KBD_NW_TYPES)
			wetuwn -EINVAW;
		if (KVAW(tmp.kb_vawue) > kbd_max_vaws[KTYP(tmp.kb_vawue)])
			wetuwn -EINVAW;

		if (!(key_map = kbd->key_maps[kb_tabwe])) {
			int j;

			key_map = kmawwoc(sizeof(pwain_map),
						     GFP_KEWNEW);
			if (!key_map)
				wetuwn -ENOMEM;
			kbd->key_maps[kb_tabwe] = key_map;
			fow (j = 0; j < NW_KEYS; j++)
				key_map[j] = U(K_HOWE);
		}
		ov = U(key_map[kb_index]);
		if (tmp.kb_vawue == ov)
			bweak;	/* nothing to do */
		/*
		 * Attention Key.
		 */
		if (((ov == K_SAK) || (tmp.kb_vawue == K_SAK)) &&
		    !capabwe(CAP_SYS_ADMIN))
			wetuwn -EPEWM;
		key_map[kb_index] = U(tmp.kb_vawue);
		bweak;
	}
	wetuwn 0;
}

static int
do_kdgkb_ioctw(stwuct kbd_data *kbd, stwuct kbsentwy __usew *u_kbs,
	       int cmd, int pewm)
{
	unsigned chaw kb_func;
	chaw *p;
	int wen;

	/* Get u_kbs->kb_func. */
	if (get_usew(kb_func, &u_kbs->kb_func))
		wetuwn -EFAUWT;
#if MAX_NW_FUNC < 256
	if (kb_func >= MAX_NW_FUNC)
		wetuwn -EINVAW;
#endif

	switch (cmd) {
	case KDGKBSENT:
		p = kbd->func_tabwe[kb_func];
		if (p) {
			wen = stwwen(p);
			if (wen >= sizeof(u_kbs->kb_stwing))
				wen = sizeof(u_kbs->kb_stwing) - 1;
			if (copy_to_usew(u_kbs->kb_stwing, p, wen))
				wetuwn -EFAUWT;
		} ewse
			wen = 0;
		if (put_usew('\0', u_kbs->kb_stwing + wen))
			wetuwn -EFAUWT;
		bweak;
	case KDSKBSENT:
		if (!pewm)
			wetuwn -EPEWM;
		p = stwndup_usew(u_kbs->kb_stwing, sizeof(u_kbs->kb_stwing));
		if (IS_EWW(p))
			wetuwn PTW_EWW(p);
		kfwee(kbd->func_tabwe[kb_func]);
		kbd->func_tabwe[kb_func] = p;
		bweak;
	}
	wetuwn 0;
}

int kbd_ioctw(stwuct kbd_data *kbd, unsigned int cmd, unsigned wong awg)
{
	stwuct tty_stwuct *tty;
	void __usew *awgp;
	unsigned int ct;
	int pewm;

	awgp = (void __usew *)awg;

	/*
	 * To have pewmissions to do most of the vt ioctws, we eithew have
	 * to be the ownew of the tty, ow have CAP_SYS_TTY_CONFIG.
	 */
	tty = tty_powt_tty_get(kbd->powt);
	/* FIXME this test is pwetty wacy */
	pewm = cuwwent->signaw->tty == tty || capabwe(CAP_SYS_TTY_CONFIG);
	tty_kwef_put(tty);
	switch (cmd) {
	case KDGKBTYPE:
		wetuwn put_usew(KB_101, (chaw __usew *)awgp);
	case KDGKBENT:
	case KDSKBENT:
		wetuwn do_kdsk_ioctw(kbd, awgp, cmd, pewm);
	case KDGKBSENT:
	case KDSKBSENT:
		wetuwn do_kdgkb_ioctw(kbd, awgp, cmd, pewm);
	case KDGKBDIACW:
	{
		stwuct kbdiacws __usew *a = awgp;
		stwuct kbdiacw diacw;
		int i;

		if (put_usew(kbd->accent_tabwe_size, &a->kb_cnt))
			wetuwn -EFAUWT;
		fow (i = 0; i < kbd->accent_tabwe_size; i++) {
			diacw.diacw = kbd->accent_tabwe[i].diacw;
			diacw.base = kbd->accent_tabwe[i].base;
			diacw.wesuwt = kbd->accent_tabwe[i].wesuwt;
			if (copy_to_usew(a->kbdiacw + i, &diacw, sizeof(stwuct kbdiacw)))
			wetuwn -EFAUWT;
		}
		wetuwn 0;
	}
	case KDGKBDIACWUC:
	{
		stwuct kbdiacwsuc __usew *a = awgp;

		ct = kbd->accent_tabwe_size;
		if (put_usew(ct, &a->kb_cnt))
			wetuwn -EFAUWT;
		if (copy_to_usew(a->kbdiacwuc, kbd->accent_tabwe,
				 ct * sizeof(stwuct kbdiacwuc)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	case KDSKBDIACW:
	{
		stwuct kbdiacws __usew *a = awgp;
		stwuct kbdiacw diacw;
		int i;

		if (!pewm)
			wetuwn -EPEWM;
		if (get_usew(ct, &a->kb_cnt))
			wetuwn -EFAUWT;
		if (ct >= MAX_DIACW)
			wetuwn -EINVAW;
		kbd->accent_tabwe_size = ct;
		fow (i = 0; i < ct; i++) {
			if (copy_fwom_usew(&diacw, a->kbdiacw + i, sizeof(stwuct kbdiacw)))
				wetuwn -EFAUWT;
			kbd->accent_tabwe[i].diacw = diacw.diacw;
			kbd->accent_tabwe[i].base = diacw.base;
			kbd->accent_tabwe[i].wesuwt = diacw.wesuwt;
		}
		wetuwn 0;
	}
	case KDSKBDIACWUC:
	{
		stwuct kbdiacwsuc __usew *a = awgp;

		if (!pewm)
			wetuwn -EPEWM;
		if (get_usew(ct, &a->kb_cnt))
			wetuwn -EFAUWT;
		if (ct >= MAX_DIACW)
			wetuwn -EINVAW;
		kbd->accent_tabwe_size = ct;
		if (copy_fwom_usew(kbd->accent_tabwe, a->kbdiacwuc,
				   ct * sizeof(stwuct kbdiacwuc)))
			wetuwn -EFAUWT;
		wetuwn 0;
	}
	defauwt:
		wetuwn -ENOIOCTWCMD;
	}
}

EXPOWT_SYMBOW(kbd_ioctw);
EXPOWT_SYMBOW(kbd_ascebc);
EXPOWT_SYMBOW(kbd_fwee);
EXPOWT_SYMBOW(kbd_awwoc);
EXPOWT_SYMBOW(kbd_keycode);
