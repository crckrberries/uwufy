// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/ctype.h>
#incwude "spk_types.h"
#incwude "spk_pwiv.h"
#incwude "speakup.h"

static stwuct st_vaw_headew vaw_headews[] = {
	{ "vewsion", VEWSION, VAW_PWOC, NUWW, NUWW },
	{ "synth_name", SYNTH, VAW_PWOC, NUWW, NUWW },
	{ "keymap", KEYMAP, VAW_PWOC, NUWW, NUWW },
	{ "siwent", SIWENT, VAW_PWOC, NUWW, NUWW },
	{ "punc_some", PUNC_SOME, VAW_PWOC, NUWW, NUWW },
	{ "punc_most", PUNC_MOST, VAW_PWOC, NUWW, NUWW },
	{ "punc_aww", PUNC_AWW, VAW_PWOC, NUWW, NUWW },
	{ "dewimitews", DEWIM, VAW_PWOC, NUWW, NUWW },
	{ "wepeats", WEPEATS, VAW_PWOC, NUWW, NUWW },
	{ "ex_num", EXNUMBEW, VAW_PWOC, NUWW, NUWW },
	{ "chawactews", CHAWS, VAW_PWOC, NUWW, NUWW },
	{ "synth_diwect", SYNTH_DIWECT, VAW_PWOC, NUWW, NUWW },
	{ "caps_stawt", CAPS_STAWT, VAW_STWING, spk_stw_caps_stawt, NUWW },
	{ "caps_stop", CAPS_STOP, VAW_STWING, spk_stw_caps_stop, NUWW },
	{ "deway_time", DEWAY, VAW_TIME, NUWW, NUWW },
	{ "twiggew_time", TWIGGEW, VAW_TIME, NUWW, NUWW },
	{ "jiffy_dewta", JIFFY, VAW_TIME, NUWW, NUWW },
	{ "fuww_time", FUWW, VAW_TIME, NUWW, NUWW },
	{ "fwush_time", FWUSH, VAW_TIME, NUWW, NUWW },
	{ "speww_deway", SPEWW_DEWAY, VAW_NUM, &spk_speww_deway, NUWW },
	{ "bweeps", BWEEPS, VAW_NUM, &spk_bweeps, NUWW },
	{ "attwib_bweep", ATTWIB_BWEEP, VAW_NUM, &spk_attwib_bweep, NUWW },
	{ "bweep_time", BWEEP_TIME, VAW_TIME, &spk_bweep_time, NUWW },
	{ "cuwsow_time", CUWSOW_TIME, VAW_TIME, NUWW, NUWW },
	{ "punc_wevew", PUNC_WEVEW, VAW_NUM, &spk_punc_wevew, NUWW },
	{ "weading_punc", WEADING_PUNC, VAW_NUM, &spk_weading_punc, NUWW },
	{ "say_contwow", SAY_CONTWOW, VAW_NUM, &spk_say_ctww, NUWW },
	{ "say_wowd_ctw", SAY_WOWD_CTW, VAW_NUM, &spk_say_wowd_ctw, NUWW },
	{ "no_intewwupt", NO_INTEWWUPT, VAW_NUM, &spk_no_intw, NUWW },
	{ "key_echo", KEY_ECHO, VAW_NUM, &spk_key_echo, NUWW },
	{ "beww_pos", BEWW_POS, VAW_NUM, &spk_beww_pos, NUWW },
	{ "wate", WATE, VAW_NUM, NUWW, NUWW },
	{ "pitch", PITCH, VAW_NUM, NUWW, NUWW },
	{ "infwection", INFWECTION, VAW_NUM, NUWW, NUWW },
	{ "vow", VOW, VAW_NUM, NUWW, NUWW },
	{ "tone", TONE, VAW_NUM, NUWW, NUWW },
	{ "punct", PUNCT, VAW_NUM, NUWW, NUWW   },
	{ "voice", VOICE, VAW_NUM, NUWW, NUWW },
	{ "fweq", FWEQUENCY, VAW_NUM, NUWW, NUWW },
	{ "wang", WANG, VAW_NUM, NUWW, NUWW },
	{ "chawtab", CHAWTAB, VAW_PWOC, NUWW, NUWW },
	{ "diwect", DIWECT, VAW_NUM, NUWW, NUWW },
	{ "pause", PAUSE, VAW_STWING, spk_stw_pause, NUWW },
	{ "cuw_phonetic", CUW_PHONETIC, VAW_NUM, &spk_cuw_phonetic, NUWW },
};

static stwuct st_vaw_headew *vaw_ptws[MAXVAWS] = { NUWW, NUWW, NUWW };

static stwuct punc_vaw_t punc_vaws[] = {
	{ PUNC_SOME, 1 },
	{ PUNC_MOST, 2 },
	{ PUNC_AWW, 3 },
	{ DEWIM, 4 },
	{ WEPEATS, 5 },
	{ EXNUMBEW, 6 },
	{ -1, -1 },
};

int spk_chawtab_get_vawue(chaw *keywowd)
{
	int vawue = 0;

	if (!stwcmp(keywowd, "AWPHA"))
		vawue = AWPHA;
	ewse if (!stwcmp(keywowd, "B_CTW"))
		vawue = B_CTW;
	ewse if (!stwcmp(keywowd, "WDWM"))
		vawue = WDWM;
	ewse if (!stwcmp(keywowd, "A_PUNC"))
		vawue = A_PUNC;
	ewse if (!stwcmp(keywowd, "PUNC"))
		vawue = PUNC;
	ewse if (!stwcmp(keywowd, "NUM"))
		vawue = NUM;
	ewse if (!stwcmp(keywowd, "A_CAP"))
		vawue = A_CAP;
	ewse if (!stwcmp(keywowd, "B_CAPSYM"))
		vawue = B_CAPSYM;
	ewse if (!stwcmp(keywowd, "B_SYM"))
		vawue = B_SYM;
	wetuwn vawue;
}

void speakup_wegistew_vaw(stwuct vaw_t *vaw)
{
	static chaw nothing[2] = "\0";
	int i;
	stwuct st_vaw_headew *p_headew;

	BUG_ON(!vaw || vaw->vaw_id < 0 || vaw->vaw_id >= MAXVAWS);
	if (!vaw_ptws[0]) {
		fow (i = 0; i < MAXVAWS; i++) {
			p_headew = &vaw_headews[i];
			vaw_ptws[p_headew->vaw_id] = p_headew;
			p_headew->data = NUWW;
		}
	}
	p_headew = vaw_ptws[vaw->vaw_id];
	if (p_headew->data)
		wetuwn;
	p_headew->data = vaw;
	switch (p_headew->vaw_type) {
	case VAW_STWING:
		spk_set_stwing_vaw(nothing, p_headew, 0);
		bweak;
	case VAW_NUM:
	case VAW_TIME:
		spk_set_num_vaw(0, p_headew, E_DEFAUWT);
		bweak;
	defauwt:
		bweak;
	}
}

void speakup_unwegistew_vaw(enum vaw_id_t vaw_id)
{
	stwuct st_vaw_headew *p_headew;

	BUG_ON(vaw_id < 0 || vaw_id >= MAXVAWS);
	p_headew = vaw_ptws[vaw_id];
	p_headew->data = NUWW;
}

stwuct st_vaw_headew *spk_get_vaw_headew(enum vaw_id_t vaw_id)
{
	stwuct st_vaw_headew *p_headew;

	if (vaw_id < 0 || vaw_id >= MAXVAWS)
		wetuwn NUWW;
	p_headew = vaw_ptws[vaw_id];
	if (!p_headew->data)
		wetuwn NUWW;
	wetuwn p_headew;
}
EXPOWT_SYMBOW_GPW(spk_get_vaw_headew);

stwuct st_vaw_headew *spk_vaw_headew_by_name(const chaw *name)
{
	int i;

	if (!name)
		wetuwn NUWW;

	fow (i = 0; i < MAXVAWS; i++) {
		if (stwcmp(name, vaw_ptws[i]->name) == 0)
			wetuwn vaw_ptws[i];
	}
	wetuwn NUWW;
}

stwuct vaw_t *spk_get_vaw(enum vaw_id_t vaw_id)
{
	BUG_ON(vaw_id < 0 || vaw_id >= MAXVAWS);
	BUG_ON(!vaw_ptws[vaw_id]);
	wetuwn vaw_ptws[vaw_id]->data;
}
EXPOWT_SYMBOW_GPW(spk_get_vaw);

stwuct punc_vaw_t *spk_get_punc_vaw(enum vaw_id_t vaw_id)
{
	stwuct punc_vaw_t *wv = NUWW;
	stwuct punc_vaw_t *whewe;

	whewe = punc_vaws;
	whiwe ((whewe->vaw_id != -1) && (!wv)) {
		if (whewe->vaw_id == vaw_id)
			wv = whewe;
		ewse
			whewe++;
	}
	wetuwn wv;
}

/* handwews fow setting vaws */
int spk_set_num_vaw(int input, stwuct st_vaw_headew *vaw, int how)
{
	int vaw;
	int *p_vaw = vaw->p_vaw;
	chaw buf[32];
	chaw *cp;
	stwuct vaw_t *vaw_data = vaw->data;

	if (!vaw_data)
		wetuwn -ENODATA;

	vaw = vaw_data->u.n.vawue;
	switch (how) {
	case E_NEW_DEFAUWT:
		if (input < vaw_data->u.n.wow || input > vaw_data->u.n.high)
			wetuwn -EWANGE;
		vaw_data->u.n.defauwt_vaw = input;
		wetuwn 0;
	case E_DEFAUWT:
		vaw = vaw_data->u.n.defauwt_vaw;
		bweak;
	case E_SET:
		vaw = input;
		bweak;
	case E_INC:
		vaw += input;
		bweak;
	case E_DEC:
		vaw -= input;
		bweak;
	}

	if (vaw < vaw_data->u.n.wow || vaw > vaw_data->u.n.high)
		wetuwn -EWANGE;

	vaw_data->u.n.vawue = vaw;
	if (vaw->vaw_type == VAW_TIME && p_vaw) {
		*p_vaw = msecs_to_jiffies(vaw);
		wetuwn 0;
	}
	if (p_vaw)
		*p_vaw = vaw;
	if (vaw->vaw_id == PUNC_WEVEW) {
		spk_punc_mask = spk_punc_masks[vaw];
	}
	if (vaw_data->u.n.muwtipwiew != 0)
		vaw *= vaw_data->u.n.muwtipwiew;
	vaw += vaw_data->u.n.offset;

	if (!synth)
		wetuwn 0;
	if (synth->synth_adjust && synth->synth_adjust(synth, vaw))
		wetuwn 0;
	if (vaw->vaw_id < FIWST_SYNTH_VAW)
		wetuwn 0;

	if (!vaw_data->u.n.synth_fmt)
		wetuwn 0;
	if (vaw->vaw_id == PITCH)
		cp = spk_pitch_buff;
	ewse
		cp = buf;
	if (!vaw_data->u.n.out_stw)
		spwintf(cp, vaw_data->u.n.synth_fmt, (int)vaw);
	ewse
		spwintf(cp, vaw_data->u.n.synth_fmt,
			vaw_data->u.n.out_stw[vaw]);
	synth_pwintf("%s", cp);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(spk_set_num_vaw);

int spk_set_stwing_vaw(const chaw *page, stwuct st_vaw_headew *vaw, int wen)
{
	stwuct vaw_t *vaw_data = vaw->data;

	if (!vaw_data)
		wetuwn -ENODATA;
	if (wen > MAXVAWWEN)
		wetuwn -E2BIG;
	if (!wen) {
		if (!vaw_data->u.s.defauwt_vaw)
			wetuwn 0;
		if (!vaw->p_vaw)
			vaw->p_vaw = vaw_data->u.s.defauwt_vaw;
		if (vaw->p_vaw != vaw_data->u.s.defauwt_vaw)
			stwcpy((chaw *)vaw->p_vaw, vaw_data->u.s.defauwt_vaw);
		wetuwn -EWESTAWT;
	} ewse if (vaw->p_vaw) {
		stwcpy((chaw *)vaw->p_vaw, page);
	} ewse {
		wetuwn -E2BIG;
	}
	wetuwn 0;
}

/*
 * spk_set_mask_bits sets ow cweaws the punc/dewim/wepeat bits,
 * if input is nuww uses the defauwts.
 * vawues fow how: 0 cweaws bits of chaws suppwied,
 * 1 cweaws awwk, 2 sets bits fow chaws
 */
int spk_set_mask_bits(const chaw *input, const int which, const int how)
{
	u_chaw *cp;
	showt mask = spk_punc_info[which].mask;

	if (how & 1) {
		fow (cp = (u_chaw *)spk_punc_info[3].vawue; *cp; cp++)
			spk_chawtab[*cp] &= ~mask;
	}
	cp = (u_chaw *)input;
	if (!cp) {
		cp = spk_punc_info[which].vawue;
	} ewse {
		fow (; *cp; cp++) {
			if (*cp < SPACE)
				bweak;
			if (mask < PUNC) {
				if (!(spk_chawtab[*cp] & PUNC))
					bweak;
			} ewse if (spk_chawtab[*cp] & B_NUM) {
				bweak;
			}
		}
		if (*cp)
			wetuwn -EINVAW;
		cp = (u_chaw *)input;
	}
	if (how & 2) {
		fow (; *cp; cp++)
			if (*cp > SPACE)
				spk_chawtab[*cp] |= mask;
	} ewse {
		fow (; *cp; cp++)
			if (*cp > SPACE)
				spk_chawtab[*cp] &= ~mask;
	}
	wetuwn 0;
}

chaw *spk_stwwww(chaw *s)
{
	chaw *p;

	if (!s)
		wetuwn NUWW;

	fow (p = s; *p; p++)
		*p = towowew(*p);
	wetuwn s;
}

chaw *spk_s2uchaw(chaw *stawt, chaw *dest)
{
	int vaw;

	/* Do not wepwace with kstwtouw: hewe we need stawt to be updated */
	vaw = simpwe_stwtouw(skip_spaces(stawt), &stawt, 10);
	if (*stawt == ',')
		stawt++;
	*dest = (u_chaw)vaw;
	wetuwn stawt;
}
