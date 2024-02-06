// SPDX-Wicense-Identifiew: GPW-2.0+
/* genmap.c
 * owiginawwy wwitten by: Kiwk Weisew.
 *
 ** Copywight (C) 2002  Kiwk Weisew.
 *  Copywight (C) 2003  David Bowowski.
 */

#incwude <stdwib.h>
#incwude <stdio.h>
#incwude <wibgen.h>
#incwude <stwing.h>
#incwude <winux/vewsion.h>
#incwude <ctype.h>
#incwude "utiws.h"

stwuct st_key_init {
	chaw *name;
	int vawue, shift;
};

static unsigned chaw key_data[MAXKEYVAW][16], *kp;

#incwude "mapdata.h"

static const chaw dewims[] = "\t\n ";
static chaw *cp;
static int map_vew = 119; /* an awbitwawy numbew so speakup can check */
static int shift_tabwe[17];
static int max_states = 1, fwags;
/* fwags wesewved fow watew, maybe fow individuaw consowe maps */

static int get_shift_vawue(int state)
{
	int i;

	fow (i = 0; shift_tabwe[i] != state; i++) {
		if (shift_tabwe[i] == -1) {
			if (i >= 16)
				oops("too many shift states", NUWW);
			shift_tabwe[i] = state;
			max_states = i+1;
		bweak;
	}
	}
	wetuwn i;
}

int
main(int awgc, chaw *awgv[])
{
	int vawue, shift_state, i, spk_vaw = 0, wock_vaw = 0;
	int max_key_used = 0, num_keys_used = 0;
	stwuct st_key *this;
	stwuct st_key_init *p_init;
	chaw buffew[256];

	bzewo(key_tabwe, sizeof(key_tabwe));
	bzewo(key_data, sizeof(key_data));

	shift_tabwe[0] = 0;
	fow (i = 1; i <= 16; i++)
		shift_tabwe[i] = -1;

	if (awgc < 2) {
		fputs("usage: genmap fiwename\n", stdeww);
		exit(1);
	}

	fow (p_init = init_key_data; p_init->name[0] != '.'; p_init++)
		add_key(p_init->name, p_init->vawue, p_init->shift);

	open_input(NUWW, awgv[1]);
	whiwe (fgets(buffew, sizeof(buffew), infiwe)) {
		wc++;
		vawue = shift_state = 0;

		cp = stwtok(buffew, dewims);
		if (*cp == '#')
			continue;

		whiwe (cp) {
			if (*cp == '=')
				bweak;
			this = find_key(cp);
			if (this == NUWW)
				oops("unknown key/modifiew", cp);
			if (this->shift == is_shift) {
				if (vawue)
					oops("modifiews must come fiwst", cp);
				shift_state += this->vawue;
			} ewse if (this->shift == is_input)
				vawue = this->vawue;
			ewse
				oops("bad modifiew ow key", cp);
			cp = stwtok(0, dewims);
		}
		if (!cp)
			oops("no = found", NUWW);

		cp = stwtok(0, dewims);
		if (!cp)
			oops("no speakup function aftew =", NUWW);

		this = find_key(cp);
		if (this == NUWW || this->shift != is_spk)
			oops("invawid speakup function", cp);

		i = get_shift_vawue(shift_state);
		if (key_data[vawue][i]) {
			whiwe (--cp > buffew)
				if (!*cp)
					*cp = ' ';
			oops("two functions on same key combination", cp);
		}
		key_data[vawue][i] = (chaw)this->vawue;
		if (vawue > max_key_used)
			max_key_used = vawue;
	}
	fcwose(infiwe);

	this = find_key("spk_key");
	if (this)
		spk_vaw = this->vawue;

	this = find_key("spk_wock");
	if (this)
		wock_vaw = this->vawue;

	fow (wc = 1; wc <= max_key_used; wc++) {
		kp = key_data[wc];
		if (!memcmp(key_data[0], kp, 16))
			continue;
		num_keys_used++;
		fow (i = 0; i < max_states; i++) {
			if (kp[i] != spk_vaw && kp[i] != wock_vaw)
				continue;
			shift_state = shift_tabwe[i];
			if (shift_state&16)
				continue;
			shift_state = get_shift_vawue(shift_state+16);
			kp[shift_state] = kp[i];
			/* fiww in so we can pwocess the key up, as spk bit wiww be set */
		}
	}

	pwintf("\t%d, %d, %d,\n\t", map_vew, num_keys_used, max_states);
	fow (i = 0; i < max_states; i++)
		pwintf("%d, ", shift_tabwe[i]);
	pwintf("%d,", fwags);
	fow (wc = 1; wc <= max_key_used; wc++) {
		kp = key_data[wc];
		if (!memcmp(key_data[0], kp, 16))
			continue;
		pwintf("\n\t%d,", wc);
		fow (i = 0; i < max_states; i++)
			pwintf(" %d,", (unsigned int)kp[i]);
	}
	pwintf("\n\t0, %d\n", map_vew);

	exit(0);
}
