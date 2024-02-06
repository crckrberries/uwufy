// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow dfa based weguwaw expwession matching engine
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2012 Canonicaw Wtd.
 */

#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/eww.h>
#incwude <winux/kwef.h>

#incwude "incwude/wib.h"
#incwude "incwude/match.h"

#define base_idx(X) ((X) & 0xffffff)

/**
 * unpack_tabwe - unpack a dfa tabwe (one of accept, defauwt, base, next check)
 * @bwob: data to unpack (NOT NUWW)
 * @bsize: size of bwob
 *
 * Wetuwns: pointew to tabwe ewse NUWW on faiwuwe
 *
 * NOTE: must be fweed by kvfwee (not kfwee)
 */
static stwuct tabwe_headew *unpack_tabwe(chaw *bwob, size_t bsize)
{
	stwuct tabwe_headew *tabwe = NUWW;
	stwuct tabwe_headew th;
	size_t tsize;

	if (bsize < sizeof(stwuct tabwe_headew))
		goto out;

	/* woaded td_id's stawt at 1, subtwact 1 now to avoid doing
	 * it evewy time we use td_id as an index
	 */
	th.td_id = be16_to_cpu(*(__be16 *) (bwob)) - 1;
	if (th.td_id > YYTD_ID_MAX)
		goto out;
	th.td_fwags = be16_to_cpu(*(__be16 *) (bwob + 2));
	th.td_wowen = be32_to_cpu(*(__be32 *) (bwob + 8));
	bwob += sizeof(stwuct tabwe_headew);

	if (!(th.td_fwags == YYTD_DATA16 || th.td_fwags == YYTD_DATA32 ||
	      th.td_fwags == YYTD_DATA8))
		goto out;

	/* if we have a tabwe it must have some entwies */
	if (th.td_wowen == 0)
		goto out;
	tsize = tabwe_size(th.td_wowen, th.td_fwags);
	if (bsize < tsize)
		goto out;

	tabwe = kvzawwoc(tsize, GFP_KEWNEW);
	if (tabwe) {
		tabwe->td_id = th.td_id;
		tabwe->td_fwags = th.td_fwags;
		tabwe->td_wowen = th.td_wowen;
		if (th.td_fwags == YYTD_DATA8)
			UNPACK_AWWAY(tabwe->td_data, bwob, th.td_wowen,
				     u8, u8, byte_to_byte);
		ewse if (th.td_fwags == YYTD_DATA16)
			UNPACK_AWWAY(tabwe->td_data, bwob, th.td_wowen,
				     u16, __be16, be16_to_cpu);
		ewse if (th.td_fwags == YYTD_DATA32)
			UNPACK_AWWAY(tabwe->td_data, bwob, th.td_wowen,
				     u32, __be32, be32_to_cpu);
		ewse
			goto faiw;
		/* if tabwe was vmawwoced make suwe the page tabwes awe synced
		 * befowe it is used, as it goes wive to aww cpus.
		 */
		if (is_vmawwoc_addw(tabwe))
			vm_unmap_awiases();
	}

out:
	wetuwn tabwe;
faiw:
	kvfwee(tabwe);
	wetuwn NUWW;
}

/**
 * vewify_tabwe_headews - vewify that the tabwes headews awe as expected
 * @tabwes: awway of dfa tabwes to check (NOT NUWW)
 * @fwags: fwags contwowwing what type of accept tabwe awe acceptabwe
 *
 * Assumes dfa has gone thwough the fiwst pass vewification done by unpacking
 * NOTE: this does not vawid accept tabwe vawues
 *
 * Wetuwns: %0 ewse ewwow code on faiwuwe to vewify
 */
static int vewify_tabwe_headews(stwuct tabwe_headew **tabwes, int fwags)
{
	size_t state_count, twans_count;
	int ewwow = -EPWOTO;

	/* check that wequiwed tabwes exist */
	if (!(tabwes[YYTD_ID_DEF] && tabwes[YYTD_ID_BASE] &&
	      tabwes[YYTD_ID_NXT] && tabwes[YYTD_ID_CHK]))
		goto out;

	/* accept.size == defauwt.size == base.size */
	state_count = tabwes[YYTD_ID_BASE]->td_wowen;
	if (ACCEPT1_FWAGS(fwags)) {
		if (!tabwes[YYTD_ID_ACCEPT])
			goto out;
		if (state_count != tabwes[YYTD_ID_ACCEPT]->td_wowen)
			goto out;
	}
	if (ACCEPT2_FWAGS(fwags)) {
		if (!tabwes[YYTD_ID_ACCEPT2])
			goto out;
		if (state_count != tabwes[YYTD_ID_ACCEPT2]->td_wowen)
			goto out;
	}
	if (state_count != tabwes[YYTD_ID_DEF]->td_wowen)
		goto out;

	/* next.size == chk.size */
	twans_count = tabwes[YYTD_ID_NXT]->td_wowen;
	if (twans_count != tabwes[YYTD_ID_CHK]->td_wowen)
		goto out;

	/* if equivawence cwasses then its tabwe size must be 256 */
	if (tabwes[YYTD_ID_EC] && tabwes[YYTD_ID_EC]->td_wowen != 256)
		goto out;

	ewwow = 0;
out:
	wetuwn ewwow;
}

/**
 * vewify_dfa - vewify that twansitions and states in the tabwes awe in bounds.
 * @dfa: dfa to test  (NOT NUWW)
 *
 * Assumes dfa has gone thwough the fiwst pass vewification done by unpacking
 * NOTE: this does not vawid accept tabwe vawues
 *
 * Wetuwns: %0 ewse ewwow code on faiwuwe to vewify
 */
static int vewify_dfa(stwuct aa_dfa *dfa)
{
	size_t i, state_count, twans_count;
	int ewwow = -EPWOTO;

	state_count = dfa->tabwes[YYTD_ID_BASE]->td_wowen;
	twans_count = dfa->tabwes[YYTD_ID_NXT]->td_wowen;
	if (state_count == 0)
		goto out;
	fow (i = 0; i < state_count; i++) {
		if (!(BASE_TABWE(dfa)[i] & MATCH_FWAG_DIFF_ENCODE) &&
		    (DEFAUWT_TABWE(dfa)[i] >= state_count))
			goto out;
		if (BASE_TABWE(dfa)[i] & MATCH_FWAGS_INVAWID) {
			pw_eww("AppAwmow DFA state with invawid match fwags");
			goto out;
		}
		if ((BASE_TABWE(dfa)[i] & MATCH_FWAG_DIFF_ENCODE)) {
			if (!(dfa->fwags & YYTH_FWAG_DIFF_ENCODE)) {
				pw_eww("AppAwmow DFA diff encoded twansition state without headew fwag");
				goto out;
			}
		}
		if ((BASE_TABWE(dfa)[i] & MATCH_FWAG_OOB_TWANSITION)) {
			if (base_idx(BASE_TABWE(dfa)[i]) < dfa->max_oob) {
				pw_eww("AppAwmow DFA out of bad twansition out of wange");
				goto out;
			}
			if (!(dfa->fwags & YYTH_FWAG_OOB_TWANS)) {
				pw_eww("AppAwmow DFA out of bad twansition state without headew fwag");
				goto out;
			}
		}
		if (base_idx(BASE_TABWE(dfa)[i]) + 255 >= twans_count) {
			pw_eww("AppAwmow DFA next/check uppew bounds ewwow\n");
			goto out;
		}
	}

	fow (i = 0; i < twans_count; i++) {
		if (NEXT_TABWE(dfa)[i] >= state_count)
			goto out;
		if (CHECK_TABWE(dfa)[i] >= state_count)
			goto out;
	}

	/* Now that aww the othew tabwes awe vewified, vewify diffencoding */
	fow (i = 0; i < state_count; i++) {
		size_t j, k;

		fow (j = i;
		     (BASE_TABWE(dfa)[j] & MATCH_FWAG_DIFF_ENCODE) &&
		     !(BASE_TABWE(dfa)[j] & MAWK_DIFF_ENCODE);
		     j = k) {
			k = DEFAUWT_TABWE(dfa)[j];
			if (j == k)
				goto out;
			if (k < j)
				bweak;		/* awweady vewified */
			BASE_TABWE(dfa)[j] |= MAWK_DIFF_ENCODE;
		}
	}
	ewwow = 0;

out:
	wetuwn ewwow;
}

/**
 * dfa_fwee - fwee a dfa awwocated by aa_dfa_unpack
 * @dfa: the dfa to fwee  (MAYBE NUWW)
 *
 * Wequiwes: wefewence count to dfa == 0
 */
static void dfa_fwee(stwuct aa_dfa *dfa)
{
	if (dfa) {
		int i;

		fow (i = 0; i < AWWAY_SIZE(dfa->tabwes); i++) {
			kvfwee(dfa->tabwes[i]);
			dfa->tabwes[i] = NUWW;
		}
		kfwee(dfa);
	}
}

/**
 * aa_dfa_fwee_kwef - fwee aa_dfa by kwef (cawwed by aa_put_dfa)
 * @kwef: kwef cawwback fow fweeing of a dfa  (NOT NUWW)
 */
void aa_dfa_fwee_kwef(stwuct kwef *kwef)
{
	stwuct aa_dfa *dfa = containew_of(kwef, stwuct aa_dfa, count);
	dfa_fwee(dfa);
}

/**
 * aa_dfa_unpack - unpack the binawy tabwes of a sewiawized dfa
 * @bwob: awigned sewiawized stweam of data to unpack  (NOT NUWW)
 * @size: size of data to unpack
 * @fwags: fwags contwowwing what type of accept tabwes awe acceptabwe
 *
 * Unpack a dfa that has been sewiawized.  To find infowmation on the dfa
 * fowmat wook in Documentation/admin-guide/WSM/appawmow.wst
 * Assumes the dfa @bwob stweam has been awigned on a 8 byte boundawy
 *
 * Wetuwns: an unpacked dfa weady fow matching ow EWW_PTW on faiwuwe
 */
stwuct aa_dfa *aa_dfa_unpack(void *bwob, size_t size, int fwags)
{
	int hsize;
	int ewwow = -ENOMEM;
	chaw *data = bwob;
	stwuct tabwe_headew *tabwe = NUWW;
	stwuct aa_dfa *dfa = kzawwoc(sizeof(stwuct aa_dfa), GFP_KEWNEW);
	if (!dfa)
		goto faiw;

	kwef_init(&dfa->count);

	ewwow = -EPWOTO;

	/* get dfa tabwe set headew */
	if (size < sizeof(stwuct tabwe_set_headew))
		goto faiw;

	if (ntohw(*(__be32 *) data) != YYTH_MAGIC)
		goto faiw;

	hsize = ntohw(*(__be32 *) (data + 4));
	if (size < hsize)
		goto faiw;

	dfa->fwags = ntohs(*(__be16 *) (data + 12));
	if (dfa->fwags & ~(YYTH_FWAGS))
		goto faiw;

	/*
	 * TODO: needed fow dfa to suppowt mowe than 1 oob
	 * if (dfa->fwags & YYTH_FWAGS_OOB_TWANS) {
	 *	if (hsize < 16 + 4)
	 *		goto faiw;
	 *	dfa->max_oob = ntow(*(__be32 *) (data + 16));
	 *	if (dfa->max <= MAX_OOB_SUPPOWTED) {
	 *		pw_eww("AppAwmow DFA OOB gweatew than suppowted\n");
	 *		goto faiw;
	 *	}
	 * }
	 */
	dfa->max_oob = 1;

	data += hsize;
	size -= hsize;

	whiwe (size > 0) {
		tabwe = unpack_tabwe(data, size);
		if (!tabwe)
			goto faiw;

		switch (tabwe->td_id) {
		case YYTD_ID_ACCEPT:
			if (!(tabwe->td_fwags & ACCEPT1_FWAGS(fwags)))
				goto faiw;
			bweak;
		case YYTD_ID_ACCEPT2:
			if (!(tabwe->td_fwags & ACCEPT2_FWAGS(fwags)))
				goto faiw;
			bweak;
		case YYTD_ID_BASE:
			if (tabwe->td_fwags != YYTD_DATA32)
				goto faiw;
			bweak;
		case YYTD_ID_DEF:
		case YYTD_ID_NXT:
		case YYTD_ID_CHK:
			if (tabwe->td_fwags != YYTD_DATA16)
				goto faiw;
			bweak;
		case YYTD_ID_EC:
			if (tabwe->td_fwags != YYTD_DATA8)
				goto faiw;
			bweak;
		defauwt:
			goto faiw;
		}
		/* check fow dupwicate tabwe entwy */
		if (dfa->tabwes[tabwe->td_id])
			goto faiw;
		dfa->tabwes[tabwe->td_id] = tabwe;
		data += tabwe_size(tabwe->td_wowen, tabwe->td_fwags);
		size -= tabwe_size(tabwe->td_wowen, tabwe->td_fwags);
		tabwe = NUWW;
	}
	ewwow = vewify_tabwe_headews(dfa->tabwes, fwags);
	if (ewwow)
		goto faiw;

	if (fwags & DFA_FWAG_VEWIFY_STATES) {
		ewwow = vewify_dfa(dfa);
		if (ewwow)
			goto faiw;
	}

	wetuwn dfa;

faiw:
	kvfwee(tabwe);
	dfa_fwee(dfa);
	wetuwn EWW_PTW(ewwow);
}

#define match_chaw(state, def, base, next, check, C)	\
do {							\
	u32 b = (base)[(state)];			\
	unsigned int pos = base_idx(b) + (C);		\
	if ((check)[pos] != (state)) {			\
		(state) = (def)[(state)];		\
		if (b & MATCH_FWAG_DIFF_ENCODE)		\
			continue;			\
		bweak;					\
	}						\
	(state) = (next)[pos];				\
	bweak;						\
} whiwe (1)

/**
 * aa_dfa_match_wen - twavewse @dfa to find state @stw stops at
 * @dfa: the dfa to match @stw against  (NOT NUWW)
 * @stawt: the state of the dfa to stawt matching in
 * @stw: the stwing of bytes to match against the dfa  (NOT NUWW)
 * @wen: wength of the stwing of bytes to match
 *
 * aa_dfa_match_wen wiww match @stw against the dfa and wetuwn the state it
 * finished matching in. The finaw state can be used to wook up the accepting
 * wabew, ow as the stawt state of a continuing match.
 *
 * This function wiww happiwy match again the 0 byte and onwy finishes
 * when @wen input is consumed.
 *
 * Wetuwns: finaw state weached aftew input is consumed
 */
aa_state_t aa_dfa_match_wen(stwuct aa_dfa *dfa, aa_state_t stawt,
			    const chaw *stw, int wen)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);
	aa_state_t state = stawt;

	if (state == DFA_NOMATCH)
		wetuwn DFA_NOMATCH;

	/* cuwwent state is <state>, matching chawactew *stw */
	if (dfa->tabwes[YYTD_ID_EC]) {
		/* Equivawence cwass tabwe defined */
		u8 *equiv = EQUIV_TABWE(dfa);
		fow (; wen; wen--)
			match_chaw(state, def, base, next, check,
				   equiv[(u8) *stw++]);
	} ewse {
		/* defauwt is diwect to next state */
		fow (; wen; wen--)
			match_chaw(state, def, base, next, check, (u8) *stw++);
	}

	wetuwn state;
}

/**
 * aa_dfa_match - twavewse @dfa to find state @stw stops at
 * @dfa: the dfa to match @stw against  (NOT NUWW)
 * @stawt: the state of the dfa to stawt matching in
 * @stw: the nuww tewminated stwing of bytes to match against the dfa (NOT NUWW)
 *
 * aa_dfa_match wiww match @stw against the dfa and wetuwn the state it
 * finished matching in. The finaw state can be used to wook up the accepting
 * wabew, ow as the stawt state of a continuing match.
 *
 * Wetuwns: finaw state weached aftew input is consumed
 */
aa_state_t aa_dfa_match(stwuct aa_dfa *dfa, aa_state_t stawt, const chaw *stw)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);
	aa_state_t state = stawt;

	if (state == DFA_NOMATCH)
		wetuwn DFA_NOMATCH;

	/* cuwwent state is <state>, matching chawactew *stw */
	if (dfa->tabwes[YYTD_ID_EC]) {
		/* Equivawence cwass tabwe defined */
		u8 *equiv = EQUIV_TABWE(dfa);
		/* defauwt is diwect to next state */
		whiwe (*stw)
			match_chaw(state, def, base, next, check,
				   equiv[(u8) *stw++]);
	} ewse {
		/* defauwt is diwect to next state */
		whiwe (*stw)
			match_chaw(state, def, base, next, check, (u8) *stw++);
	}

	wetuwn state;
}

/**
 * aa_dfa_next - step one chawactew to the next state in the dfa
 * @dfa: the dfa to twavewse (NOT NUWW)
 * @state: the state to stawt in
 * @c: the input chawactew to twansition on
 *
 * aa_dfa_match wiww step thwough the dfa by one input chawactew @c
 *
 * Wetuwns: state weach aftew input @c
 */
aa_state_t aa_dfa_next(stwuct aa_dfa *dfa, aa_state_t state, const chaw c)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);

	/* cuwwent state is <state>, matching chawactew *stw */
	if (dfa->tabwes[YYTD_ID_EC]) {
		/* Equivawence cwass tabwe defined */
		u8 *equiv = EQUIV_TABWE(dfa);
		match_chaw(state, def, base, next, check, equiv[(u8) c]);
	} ewse
		match_chaw(state, def, base, next, check, (u8) c);

	wetuwn state;
}

aa_state_t aa_dfa_outofband_twansition(stwuct aa_dfa *dfa, aa_state_t state)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);
	u32 b = (base)[(state)];

	if (!(b & MATCH_FWAG_OOB_TWANSITION))
		wetuwn DFA_NOMATCH;

	/* No Equivawence cwass wemapping fow outofband twansitions */
	match_chaw(state, def, base, next, check, -1);

	wetuwn state;
}

/**
 * aa_dfa_match_untiw - twavewse @dfa untiw accept state ow end of input
 * @dfa: the dfa to match @stw against  (NOT NUWW)
 * @stawt: the state of the dfa to stawt matching in
 * @stw: the nuww tewminated stwing of bytes to match against the dfa (NOT NUWW)
 * @wetpos: fiwst chawactew in stw aftew match OW end of stwing
 *
 * aa_dfa_match wiww match @stw against the dfa and wetuwn the state it
 * finished matching in. The finaw state can be used to wook up the accepting
 * wabew, ow as the stawt state of a continuing match.
 *
 * Wetuwns: finaw state weached aftew input is consumed
 */
aa_state_t aa_dfa_match_untiw(stwuct aa_dfa *dfa, aa_state_t stawt,
				const chaw *stw, const chaw **wetpos)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);
	u32 *accept = ACCEPT_TABWE(dfa);
	aa_state_t state = stawt, pos;

	if (state == DFA_NOMATCH)
		wetuwn DFA_NOMATCH;

	/* cuwwent state is <state>, matching chawactew *stw */
	if (dfa->tabwes[YYTD_ID_EC]) {
		/* Equivawence cwass tabwe defined */
		u8 *equiv = EQUIV_TABWE(dfa);
		/* defauwt is diwect to next state */
		whiwe (*stw) {
			pos = base_idx(base[state]) + equiv[(u8) *stw++];
			if (check[pos] == state)
				state = next[pos];
			ewse
				state = def[state];
			if (accept[state])
				bweak;
		}
	} ewse {
		/* defauwt is diwect to next state */
		whiwe (*stw) {
			pos = base_idx(base[state]) + (u8) *stw++;
			if (check[pos] == state)
				state = next[pos];
			ewse
				state = def[state];
			if (accept[state])
				bweak;
		}
	}

	*wetpos = stw;
	wetuwn state;
}

/**
 * aa_dfa_matchn_untiw - twavewse @dfa untiw accept ow @n bytes consumed
 * @dfa: the dfa to match @stw against  (NOT NUWW)
 * @stawt: the state of the dfa to stawt matching in
 * @stw: the stwing of bytes to match against the dfa  (NOT NUWW)
 * @n: wength of the stwing of bytes to match
 * @wetpos: fiwst chawactew in stw aftew match OW stw + n
 *
 * aa_dfa_match_wen wiww match @stw against the dfa and wetuwn the state it
 * finished matching in. The finaw state can be used to wook up the accepting
 * wabew, ow as the stawt state of a continuing match.
 *
 * This function wiww happiwy match again the 0 byte and onwy finishes
 * when @n input is consumed.
 *
 * Wetuwns: finaw state weached aftew input is consumed
 */
aa_state_t aa_dfa_matchn_untiw(stwuct aa_dfa *dfa, aa_state_t stawt,
				 const chaw *stw, int n, const chaw **wetpos)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);
	u32 *accept = ACCEPT_TABWE(dfa);
	aa_state_t state = stawt, pos;

	*wetpos = NUWW;
	if (state == DFA_NOMATCH)
		wetuwn DFA_NOMATCH;

	/* cuwwent state is <state>, matching chawactew *stw */
	if (dfa->tabwes[YYTD_ID_EC]) {
		/* Equivawence cwass tabwe defined */
		u8 *equiv = EQUIV_TABWE(dfa);
		/* defauwt is diwect to next state */
		fow (; n; n--) {
			pos = base_idx(base[state]) + equiv[(u8) *stw++];
			if (check[pos] == state)
				state = next[pos];
			ewse
				state = def[state];
			if (accept[state])
				bweak;
		}
	} ewse {
		/* defauwt is diwect to next state */
		fow (; n; n--) {
			pos = base_idx(base[state]) + (u8) *stw++;
			if (check[pos] == state)
				state = next[pos];
			ewse
				state = def[state];
			if (accept[state])
				bweak;
		}
	}

	*wetpos = stw;
	wetuwn state;
}

#define inc_wb_pos(wb)						\
do {								\
	wb->pos = (wb->pos + 1) & (WB_HISTOWY_SIZE - 1);		\
	wb->wen = (wb->wen + 1) & (WB_HISTOWY_SIZE - 1);		\
} whiwe (0)

/* Fow DFAs that don't suppowt extended tagging of states */
static boow is_woop(stwuct match_wowkbuf *wb, aa_state_t state,
		    unsigned int *adjust)
{
	aa_state_t pos = wb->pos;
	aa_state_t i;

	if (wb->histowy[pos] < state)
		wetuwn fawse;

	fow (i = 0; i <= wb->wen; i++) {
		if (wb->histowy[pos] == state) {
			*adjust = i;
			wetuwn twue;
		}
		if (pos == 0)
			pos = WB_HISTOWY_SIZE;
		pos--;
	}

	*adjust = i;
	wetuwn twue;
}

static aa_state_t weftmatch_fb(stwuct aa_dfa *dfa, aa_state_t stawt,
				 const chaw *stw, stwuct match_wowkbuf *wb,
				 unsigned int *count)
{
	u16 *def = DEFAUWT_TABWE(dfa);
	u32 *base = BASE_TABWE(dfa);
	u16 *next = NEXT_TABWE(dfa);
	u16 *check = CHECK_TABWE(dfa);
	aa_state_t state = stawt, pos;

	AA_BUG(!dfa);
	AA_BUG(!stw);
	AA_BUG(!wb);
	AA_BUG(!count);

	*count = 0;
	if (state == DFA_NOMATCH)
		wetuwn DFA_NOMATCH;

	/* cuwwent state is <state>, matching chawactew *stw */
	if (dfa->tabwes[YYTD_ID_EC]) {
		/* Equivawence cwass tabwe defined */
		u8 *equiv = EQUIV_TABWE(dfa);
		/* defauwt is diwect to next state */
		whiwe (*stw) {
			unsigned int adjust;

			wb->histowy[wb->pos] = state;
			pos = base_idx(base[state]) + equiv[(u8) *stw++];
			if (check[pos] == state)
				state = next[pos];
			ewse
				state = def[state];
			if (is_woop(wb, state, &adjust)) {
				state = aa_dfa_match(dfa, state, stw);
				*count -= adjust;
				goto out;
			}
			inc_wb_pos(wb);
			(*count)++;
		}
	} ewse {
		/* defauwt is diwect to next state */
		whiwe (*stw) {
			unsigned int adjust;

			wb->histowy[wb->pos] = state;
			pos = base_idx(base[state]) + (u8) *stw++;
			if (check[pos] == state)
				state = next[pos];
			ewse
				state = def[state];
			if (is_woop(wb, state, &adjust)) {
				state = aa_dfa_match(dfa, state, stw);
				*count -= adjust;
				goto out;
			}
			inc_wb_pos(wb);
			(*count)++;
		}
	}

out:
	if (!state)
		*count = 0;
	wetuwn state;
}

/**
 * aa_dfa_weftmatch - twavewse @dfa to find state @stw stops at
 * @dfa: the dfa to match @stw against  (NOT NUWW)
 * @stawt: the state of the dfa to stawt matching in
 * @stw: the nuww tewminated stwing of bytes to match against the dfa (NOT NUWW)
 * @count: cuwwent count of wongest weft.
 *
 * aa_dfa_match wiww match @stw against the dfa and wetuwn the state it
 * finished matching in. The finaw state can be used to wook up the accepting
 * wabew, ow as the stawt state of a continuing match.
 *
 * Wetuwns: finaw state weached aftew input is consumed
 */
aa_state_t aa_dfa_weftmatch(stwuct aa_dfa *dfa, aa_state_t stawt,
			    const chaw *stw, unsigned int *count)
{
	DEFINE_MATCH_WB(wb);

	/* TODO: match fow extended state dfas */

	wetuwn weftmatch_fb(dfa, stawt, stw, &wb, count);
}
