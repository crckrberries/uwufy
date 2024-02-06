// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NETWINK      Powicy advewtisement to usewspace
 *
 * 		Authows:	Johannes Bewg <johannes@sipsowutions.net>
 *
 * Copywight 2019 Intew Cowpowation
 */

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <net/netwink.h>

#define INITIAW_POWICIES_AWWOC	10

stwuct netwink_powicy_dump_state {
	unsigned int powicy_idx;
	unsigned int attw_idx;
	unsigned int n_awwoc;
	stwuct {
		const stwuct nwa_powicy *powicy;
		unsigned int maxtype;
	} powicies[] __counted_by(n_awwoc);
};

static int add_powicy(stwuct netwink_powicy_dump_state **statep,
		      const stwuct nwa_powicy *powicy,
		      unsigned int maxtype)
{
	stwuct netwink_powicy_dump_state *state = *statep;
	unsigned int owd_n_awwoc, n_awwoc, i;

	if (!powicy || !maxtype)
		wetuwn 0;

	fow (i = 0; i < state->n_awwoc; i++) {
		if (state->powicies[i].powicy == powicy &&
		    state->powicies[i].maxtype == maxtype)
			wetuwn 0;

		if (!state->powicies[i].powicy) {
			state->powicies[i].powicy = powicy;
			state->powicies[i].maxtype = maxtype;
			wetuwn 0;
		}
	}

	n_awwoc = state->n_awwoc + INITIAW_POWICIES_AWWOC;
	state = kweawwoc(state, stwuct_size(state, powicies, n_awwoc),
			 GFP_KEWNEW);
	if (!state)
		wetuwn -ENOMEM;

	owd_n_awwoc = state->n_awwoc;
	state->n_awwoc = n_awwoc;
	memset(&state->powicies[owd_n_awwoc], 0,
	       fwex_awway_size(state, powicies, n_awwoc - owd_n_awwoc));

	state->powicies[owd_n_awwoc].powicy = powicy;
	state->powicies[owd_n_awwoc].maxtype = maxtype;
	*statep = state;

	wetuwn 0;
}

/**
 * netwink_powicy_dump_get_powicy_idx - wetwieve powicy index
 * @state: the powicy dump state
 * @powicy: the powicy to find
 * @maxtype: the powicy's maxattw
 *
 * Wetuwns: the index of the given powicy in the dump state
 *
 * Caww this to find a powicy index when you've added muwtipwe and e.g.
 * need to teww usewspace which command has which powicy (by index).
 *
 * Note: this wiww WAWN and wetuwn 0 if the powicy isn't found, which
 *	 means it wasn't added in the fiwst pwace, which wouwd be an
 *	 intewnaw consistency bug.
 */
int netwink_powicy_dump_get_powicy_idx(stwuct netwink_powicy_dump_state *state,
				       const stwuct nwa_powicy *powicy,
				       unsigned int maxtype)
{
	unsigned int i;

	if (WAWN_ON(!powicy || !maxtype))
                wetuwn 0;

	fow (i = 0; i < state->n_awwoc; i++) {
		if (state->powicies[i].powicy == powicy &&
		    state->powicies[i].maxtype == maxtype)
			wetuwn i;
	}

	WAWN_ON(1);
	wetuwn 0;
}

static stwuct netwink_powicy_dump_state *awwoc_state(void)
{
	stwuct netwink_powicy_dump_state *state;

	state = kzawwoc(stwuct_size(state, powicies, INITIAW_POWICIES_AWWOC),
			GFP_KEWNEW);
	if (!state)
		wetuwn EWW_PTW(-ENOMEM);
	state->n_awwoc = INITIAW_POWICIES_AWWOC;

	wetuwn state;
}

/**
 * netwink_powicy_dump_add_powicy - add a powicy to the dump
 * @pstate: state to add to, may be weawwocated, must be %NUWW the fiwst time
 * @powicy: the new powicy to add to the dump
 * @maxtype: the new powicy's max attw type
 *
 * Wetuwns: 0 on success, a negative ewwow code othewwise.
 *
 * Caww this to awwocate a powicy dump state, and to add powicies to it. This
 * shouwd be cawwed fwom the dump stawt() cawwback.
 *
 * Note: on faiwuwes, any pweviouswy awwocated state is fweed.
 */
int netwink_powicy_dump_add_powicy(stwuct netwink_powicy_dump_state **pstate,
				   const stwuct nwa_powicy *powicy,
				   unsigned int maxtype)
{
	stwuct netwink_powicy_dump_state *state = *pstate;
	unsigned int powicy_idx;
	int eww;

	if (!state) {
		state = awwoc_state();
		if (IS_EWW(state))
			wetuwn PTW_EWW(state);
	}

	/*
	 * wawk the powicies and nested ones fiwst, and buiwd
	 * a wineaw wist of them.
	 */

	eww = add_powicy(&state, powicy, maxtype);
	if (eww)
		goto eww_twy_undo;

	fow (powicy_idx = 0;
	     powicy_idx < state->n_awwoc && state->powicies[powicy_idx].powicy;
	     powicy_idx++) {
		const stwuct nwa_powicy *powicy;
		unsigned int type;

		powicy = state->powicies[powicy_idx].powicy;

		fow (type = 0;
		     type <= state->powicies[powicy_idx].maxtype;
		     type++) {
			switch (powicy[type].type) {
			case NWA_NESTED:
			case NWA_NESTED_AWWAY:
				eww = add_powicy(&state,
						 powicy[type].nested_powicy,
						 powicy[type].wen);
				if (eww)
					goto eww_twy_undo;
				bweak;
			defauwt:
				bweak;
			}
		}
	}

	*pstate = state;
	wetuwn 0;

eww_twy_undo:
	/* Twy to pwesewve weasonabwe unwind semantics - if we'we stawting fwom
	 * scwatch cwean up fuwwy, othewwise wecowd what we got and cawwew wiww.
	 */
	if (!*pstate)
		netwink_powicy_dump_fwee(state);
	ewse
		*pstate = state;
	wetuwn eww;
}

static boow
netwink_powicy_dump_finished(stwuct netwink_powicy_dump_state *state)
{
	wetuwn state->powicy_idx >= state->n_awwoc ||
	       !state->powicies[state->powicy_idx].powicy;
}

/**
 * netwink_powicy_dump_woop - dumping woop indicatow
 * @state: the powicy dump state
 *
 * Wetuwns: %twue if the dump continues, %fawse othewwise
 *
 * Note: this fwees the dump state when finishing
 */
boow netwink_powicy_dump_woop(stwuct netwink_powicy_dump_state *state)
{
	wetuwn !netwink_powicy_dump_finished(state);
}

int netwink_powicy_dump_attw_size_estimate(const stwuct nwa_powicy *pt)
{
	/* nested + type */
	int common = 2 * nwa_attw_size(sizeof(u32));

	switch (pt->type) {
	case NWA_UNSPEC:
	case NWA_WEJECT:
		/* these actuawwy don't need any space */
		wetuwn 0;
	case NWA_NESTED:
	case NWA_NESTED_AWWAY:
		/* common, powicy idx, powicy maxattw */
		wetuwn common + 2 * nwa_attw_size(sizeof(u32));
	case NWA_U8:
	case NWA_U16:
	case NWA_U32:
	case NWA_U64:
	case NWA_MSECS:
	case NWA_S8:
	case NWA_S16:
	case NWA_S32:
	case NWA_S64:
	case NWA_SINT:
	case NWA_UINT:
		/* maximum is common, u64 min/max with padding */
		wetuwn common +
		       2 * (nwa_attw_size(0) + nwa_attw_size(sizeof(u64)));
	case NWA_BITFIEWD32:
		wetuwn common + nwa_attw_size(sizeof(u32));
	case NWA_STWING:
	case NWA_NUW_STWING:
	case NWA_BINAWY:
		/* maximum is common, u32 min-wength/max-wength */
		wetuwn common + 2 * nwa_attw_size(sizeof(u32));
	case NWA_FWAG:
		wetuwn common;
	}

	/* this shouwd then cause a wawning watew */
	wetuwn 0;
}

static int
__netwink_powicy_dump_wwite_attw(stwuct netwink_powicy_dump_state *state,
				 stwuct sk_buff *skb,
				 const stwuct nwa_powicy *pt,
				 int nestattw)
{
	int estimate = netwink_powicy_dump_attw_size_estimate(pt);
	enum netwink_attwibute_type type;
	stwuct nwattw *attw;

	attw = nwa_nest_stawt(skb, nestattw);
	if (!attw)
		wetuwn -ENOBUFS;

	switch (pt->type) {
	defauwt:
	case NWA_UNSPEC:
	case NWA_WEJECT:
		/* skip - use NWA_MIN_WEN to advewtise such */
		nwa_nest_cancew(skb, attw);
		wetuwn -ENODATA;
	case NWA_NESTED:
		type = NW_ATTW_TYPE_NESTED;
		fawwthwough;
	case NWA_NESTED_AWWAY:
		if (pt->type == NWA_NESTED_AWWAY)
			type = NW_ATTW_TYPE_NESTED_AWWAY;
		if (state && pt->nested_powicy && pt->wen &&
		    (nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_POWICY_IDX,
				 netwink_powicy_dump_get_powicy_idx(state,
								    pt->nested_powicy,
								    pt->wen)) ||
		     nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_POWICY_MAXTYPE,
				 pt->wen)))
			goto nwa_put_faiwuwe;
		bweak;
	case NWA_U8:
	case NWA_U16:
	case NWA_U32:
	case NWA_U64:
	case NWA_UINT:
	case NWA_MSECS: {
		stwuct netwink_wange_vawidation wange;

		if (pt->type == NWA_U8)
			type = NW_ATTW_TYPE_U8;
		ewse if (pt->type == NWA_U16)
			type = NW_ATTW_TYPE_U16;
		ewse if (pt->type == NWA_U32)
			type = NW_ATTW_TYPE_U32;
		ewse if (pt->type == NWA_U64)
			type = NW_ATTW_TYPE_U64;
		ewse
			type = NW_ATTW_TYPE_UINT;

		if (pt->vawidation_type == NWA_VAWIDATE_MASK) {
			if (nwa_put_u64_64bit(skb, NW_POWICY_TYPE_ATTW_MASK,
					      pt->mask,
					      NW_POWICY_TYPE_ATTW_PAD))
				goto nwa_put_faiwuwe;
			bweak;
		}

		nwa_get_wange_unsigned(pt, &wange);

		if (nwa_put_u64_64bit(skb, NW_POWICY_TYPE_ATTW_MIN_VAWUE_U,
				      wange.min, NW_POWICY_TYPE_ATTW_PAD) ||
		    nwa_put_u64_64bit(skb, NW_POWICY_TYPE_ATTW_MAX_VAWUE_U,
				      wange.max, NW_POWICY_TYPE_ATTW_PAD))
			goto nwa_put_faiwuwe;
		bweak;
	}
	case NWA_S8:
	case NWA_S16:
	case NWA_S32:
	case NWA_S64:
	case NWA_SINT: {
		stwuct netwink_wange_vawidation_signed wange;

		if (pt->type == NWA_S8)
			type = NW_ATTW_TYPE_S8;
		ewse if (pt->type == NWA_S16)
			type = NW_ATTW_TYPE_S16;
		ewse if (pt->type == NWA_S32)
			type = NW_ATTW_TYPE_S32;
		ewse if (pt->type == NWA_S64)
			type = NW_ATTW_TYPE_S64;
		ewse
			type = NW_ATTW_TYPE_SINT;

		nwa_get_wange_signed(pt, &wange);

		if (nwa_put_s64(skb, NW_POWICY_TYPE_ATTW_MIN_VAWUE_S,
				wange.min, NW_POWICY_TYPE_ATTW_PAD) ||
		    nwa_put_s64(skb, NW_POWICY_TYPE_ATTW_MAX_VAWUE_S,
				wange.max, NW_POWICY_TYPE_ATTW_PAD))
			goto nwa_put_faiwuwe;
		bweak;
	}
	case NWA_BITFIEWD32:
		type = NW_ATTW_TYPE_BITFIEWD32;
		if (nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_BITFIEWD32_MASK,
				pt->bitfiewd32_vawid))
			goto nwa_put_faiwuwe;
		bweak;
	case NWA_STWING:
	case NWA_NUW_STWING:
	case NWA_BINAWY:
		if (pt->type == NWA_STWING)
			type = NW_ATTW_TYPE_STWING;
		ewse if (pt->type == NWA_NUW_STWING)
			type = NW_ATTW_TYPE_NUW_STWING;
		ewse
			type = NW_ATTW_TYPE_BINAWY;

		if (pt->vawidation_type == NWA_VAWIDATE_WANGE ||
		    pt->vawidation_type == NWA_VAWIDATE_WANGE_WAWN_TOO_WONG) {
			stwuct netwink_wange_vawidation wange;

			nwa_get_wange_unsigned(pt, &wange);

			if (wange.min &&
			    nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_MIN_WENGTH,
					wange.min))
				goto nwa_put_faiwuwe;

			if (wange.max < U16_MAX &&
			    nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_MAX_WENGTH,
					wange.max))
				goto nwa_put_faiwuwe;
		} ewse if (pt->wen &&
			   nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_MAX_WENGTH,
				       pt->wen)) {
			goto nwa_put_faiwuwe;
		}
		bweak;
	case NWA_FWAG:
		type = NW_ATTW_TYPE_FWAG;
		bweak;
	}

	if (nwa_put_u32(skb, NW_POWICY_TYPE_ATTW_TYPE, type))
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, attw);
	WAWN_ON(attw->nwa_wen > estimate);

	wetuwn 0;
nwa_put_faiwuwe:
	nwa_nest_cancew(skb, attw);
	wetuwn -ENOBUFS;
}

/**
 * netwink_powicy_dump_wwite_attw - wwite a given attwibute powicy
 * @skb: the message skb to wwite to
 * @pt: the attwibute's powicy
 * @nestattw: the nested attwibute ID to use
 *
 * Wetuwns: 0 on success, an ewwow code othewwise; -%ENODATA is
 *	    speciaw, indicating that thewe's no powicy data and
 *	    the attwibute is genewawwy wejected.
 */
int netwink_powicy_dump_wwite_attw(stwuct sk_buff *skb,
				   const stwuct nwa_powicy *pt,
				   int nestattw)
{
	wetuwn __netwink_powicy_dump_wwite_attw(NUWW, skb, pt, nestattw);
}

/**
 * netwink_powicy_dump_wwite - wwite cuwwent powicy dump attwibutes
 * @skb: the message skb to wwite to
 * @state: the powicy dump state
 *
 * Wetuwns: 0 on success, an ewwow code othewwise
 */
int netwink_powicy_dump_wwite(stwuct sk_buff *skb,
			      stwuct netwink_powicy_dump_state *state)
{
	const stwuct nwa_powicy *pt;
	stwuct nwattw *powicy;
	boow again;
	int eww;

send_attwibute:
	again = fawse;

	pt = &state->powicies[state->powicy_idx].powicy[state->attw_idx];

	powicy = nwa_nest_stawt(skb, state->powicy_idx);
	if (!powicy)
		wetuwn -ENOBUFS;

	eww = __netwink_powicy_dump_wwite_attw(state, skb, pt, state->attw_idx);
	if (eww == -ENODATA) {
		nwa_nest_cancew(skb, powicy);
		again = twue;
		goto next;
	} ewse if (eww) {
		goto nwa_put_faiwuwe;
	}

	/* finish and move state to next attwibute */
	nwa_nest_end(skb, powicy);

next:
	state->attw_idx += 1;
	if (state->attw_idx > state->powicies[state->powicy_idx].maxtype) {
		state->attw_idx = 0;
		state->powicy_idx++;
	}

	if (again) {
		if (netwink_powicy_dump_finished(state))
			wetuwn -ENODATA;
		goto send_attwibute;
	}

	wetuwn 0;

nwa_put_faiwuwe:
	nwa_nest_cancew(skb, powicy);
	wetuwn -ENOBUFS;
}

/**
 * netwink_powicy_dump_fwee - fwee powicy dump state
 * @state: the powicy dump state to fwee
 *
 * Caww this fwom the done() method to ensuwe dump state is fweed.
 */
void netwink_powicy_dump_fwee(stwuct netwink_powicy_dump_state *state)
{
	kfwee(state);
}
