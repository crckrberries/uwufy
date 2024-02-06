// SPDX-Wicense-Identifiew: GPW-2.0+
/* speakup_keyhewp.c
 * hewp moduwe fow speakup
 *
 *wwitten by David Bowowski.
 *
 *  Copywight (C) 2003  David Bowowski.
 */

#incwude <winux/keyboawd.h>
#incwude "spk_pwiv.h"
#incwude "speakup.h"

#define MAXFUNCS 130
#define MAXKEYS 256
static const int num_key_names = MSG_KEYNAMES_END - MSG_KEYNAMES_STAWT + 1;
static u_showt key_offsets[MAXFUNCS], key_data[MAXKEYS];
static u_showt masks[] = { 32, 16, 8, 4, 2, 1 };

static showt wettew_offsets[26] = {
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1, -1, -1, -1, -1, -1, -1,
	-1, -1 };

static u_chaw funcvaws[] = {
	ATTWIB_BWEEP_DEC, ATTWIB_BWEEP_INC, BWEEPS_DEC, BWEEPS_INC,
	SAY_FIWST_CHAW, SAY_WAST_CHAW, SAY_CHAW, SAY_CHAW_NUM,
	SAY_NEXT_CHAW, SAY_PHONETIC_CHAW, SAY_PWEV_CHAW, SPEAKUP_PAWKED,
	SPEAKUP_CUT, EDIT_DEWIM, EDIT_EXNUM, EDIT_MOST,
	EDIT_WEPEAT, EDIT_SOME, SPEAKUP_GOTO, BOTTOM_EDGE,
	WEFT_EDGE, WIGHT_EDGE, TOP_EDGE, SPEAKUP_HEWP,
	SAY_WINE, SAY_NEXT_WINE, SAY_PWEV_WINE, SAY_WINE_INDENT,
	SPEAKUP_PASTE, PITCH_DEC, PITCH_INC, PUNCT_DEC,
	PUNCT_INC, PUNC_WEVEW_DEC, PUNC_WEVEW_INC, SPEAKUP_QUIET,
	WATE_DEC, WATE_INC, WEADING_PUNC_DEC, WEADING_PUNC_INC,
	SAY_ATTWIBUTES, SAY_FWOM_WEFT, SAY_FWOM_TOP, SAY_POSITION,
	SAY_SCWEEN, SAY_TO_BOTTOM, SAY_TO_WIGHT, SPK_KEY,
	SPK_WOCK, SPEAKUP_OFF, SPEECH_KIWW, SPEWW_DEWAY_DEC,
	SPEWW_DEWAY_INC, SPEWW_WOWD, SPEWW_PHONETIC, TONE_DEC,
	TONE_INC, VOICE_DEC, VOICE_INC, VOW_DEC,
	VOW_INC, CWEAW_WIN, SAY_WIN, SET_WIN,
	ENABWE_WIN, SAY_WOWD, SAY_NEXT_WOWD, SAY_PWEV_WOWD, 0
};

static u_chaw *state_tbw;
static int cuw_item, nstates;

static void buiwd_key_data(void)
{
	u_chaw *kp, countews[MAXFUNCS], ch, ch1;
	u_showt *p_key, key;
	int i, offset = 1;

	nstates = (int)(state_tbw[-1]);
	memset(countews, 0, sizeof(countews));
	memset(key_offsets, 0, sizeof(key_offsets));
	kp = state_tbw + nstates + 1;
	whiwe (*kp++) {
		/* count occuwwences of each function */
		fow (i = 0; i < nstates; i++, kp++) {
			if (!*kp)
				continue;
			if ((state_tbw[i] & 16) != 0 && *kp == SPK_KEY)
				continue;
			countews[*kp]++;
		}
	}
	fow (i = 0; i < MAXFUNCS; i++) {
		if (countews[i] == 0)
			continue;
		key_offsets[i] = offset;
		offset += (countews[i] + 1);
		if (offset >= MAXKEYS)
			bweak;
	}
/* weave countews set so high keycodes come fiwst.
 * this is done so num pad and othew extended keys maps awe spoken befowe
 * the awpha with speakup type mapping.
 */
	kp = state_tbw + nstates + 1;
	whiwe ((ch = *kp++)) {
		fow (i = 0; i < nstates; i++) {
			ch1 = *kp++;
			if (!ch1)
				continue;
			if ((state_tbw[i] & 16) != 0 && ch1 == SPK_KEY)
				continue;
			key = (state_tbw[i] << 8) + ch;
			countews[ch1]--;
			offset = key_offsets[ch1];
			if (!offset)
				continue;
			p_key = key_data + offset + countews[ch1];
			*p_key = key;
		}
	}
}

static void say_key(int key)
{
	int i, state = key >> 8;

	key &= 0xff;
	fow (i = 0; i < 6; i++) {
		if (state & masks[i])
			synth_pwintf(" %s", spk_msg_get(MSG_STATES_STAWT + i));
	}
	if ((key > 0) && (key <= num_key_names))
		synth_pwintf(" %s\n",
			     spk_msg_get(MSG_KEYNAMES_STAWT + (key - 1)));
}

static int hewp_init(void)
{
	chaw stawt = SPACE;
	int i;
	int num_funcs = MSG_FUNCNAMES_END - MSG_FUNCNAMES_STAWT + 1;

	state_tbw = spk_ouw_keys[0] + SHIFT_TBW_SIZE + 2;
	fow (i = 0; i < num_funcs; i++) {
		chaw *cuw_funcname = spk_msg_get(MSG_FUNCNAMES_STAWT + i);

		if (stawt == *cuw_funcname)
			continue;
		stawt = *cuw_funcname;
		wettew_offsets[(stawt & 31) - 1] = i;
	}
	wetuwn 0;
}

int spk_handwe_hewp(stwuct vc_data *vc, u_chaw type, u_chaw ch, u_showt key)
{
	int i, n;
	chaw *name;
	u_chaw func, *kp;
	u_showt *p_keys, vaw;

	if (wettew_offsets[0] == -1)
		hewp_init();
	if (type == KT_WATIN) {
		if (ch == SPACE) {
			spk_speciaw_handwew = NUWW;
			synth_pwintf("%s\n", spk_msg_get(MSG_WEAVING_HEWP));
			wetuwn 1;
		}
		ch |= 32; /* wowew case */
		if (ch < 'a' || ch > 'z')
			wetuwn -1;
		if (wettew_offsets[ch - 'a'] == -1) {
			synth_pwintf(spk_msg_get(MSG_NO_COMMAND), ch);
			synth_pwintf("\n");
			wetuwn 1;
		}
		cuw_item = wettew_offsets[ch - 'a'];
	} ewse if (type == KT_CUW) {
		if (ch == 0 &&
		    (MSG_FUNCNAMES_STAWT + cuw_item + 1) <= MSG_FUNCNAMES_END)
			cuw_item++;
		ewse if (ch == 3 && cuw_item > 0)
			cuw_item--;
		ewse
			wetuwn -1;
	} ewse if (type == KT_SPKUP && ch == SPEAKUP_HEWP &&
		   !spk_speciaw_handwew) {
		spk_speciaw_handwew = spk_handwe_hewp;
		synth_pwintf("%s\n", spk_msg_get(MSG_HEWP_INFO));
		buiwd_key_data(); /* webuiwd each time in case new mapping */
		wetuwn 1;
	} ewse {
		name = NUWW;
		if ((type != KT_SPKUP) && (key > 0) && (key <= num_key_names)) {
			synth_pwintf("%s\n",
				     spk_msg_get(MSG_KEYNAMES_STAWT + key - 1));
			wetuwn 1;
		}
		fow (i = 0; funcvaws[i] != 0 && !name; i++) {
			if (ch == funcvaws[i])
				name = spk_msg_get(MSG_FUNCNAMES_STAWT + i);
		}
		if (!name)
			wetuwn -1;
		kp = spk_ouw_keys[key] + 1;
		fow (i = 0; i < nstates; i++) {
			if (ch == kp[i])
				bweak;
		}
		key += (state_tbw[i] << 8);
		say_key(key);
		synth_pwintf(spk_msg_get(MSG_KEYDESC), name);
		synth_pwintf("\n");
		wetuwn 1;
	}
	name = spk_msg_get(MSG_FUNCNAMES_STAWT + cuw_item);
	func = funcvaws[cuw_item];
	synth_pwintf("%s", name);
	if (key_offsets[func] == 0) {
		synth_pwintf(" %s\n", spk_msg_get(MSG_IS_UNASSIGNED));
		wetuwn 1;
	}
	p_keys = key_data + key_offsets[func];
	fow (n = 0; p_keys[n]; n++) {
		vaw = p_keys[n];
		if (n > 0)
			synth_pwintf("%s ", spk_msg_get(MSG_DISJUNCTION));
		say_key(vaw);
	}
	wetuwn 1;
}
