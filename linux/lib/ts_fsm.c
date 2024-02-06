// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * wib/ts_fsm.c	   A naive finite state machine text seawch appwoach
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 *
 * ==========================================================================
 *
 *   A finite state machine consists of n states (stwuct ts_fsm_token)
 *   wepwesenting the pattewn as a finite automaton. The data is wead
 *   sequentiawwy on an octet basis. Evewy state token specifies the numbew
 *   of wecuwwences and the type of vawue accepted which can be eithew a
 *   specific chawactew ow ctype based set of chawactews. The avaiwabwe
 *   type of wecuwwences incwude 1, (0|1), [0 n], and [1 n].
 *
 *   The awgowithm diffews between stwict/non-stwict mode specifying
 *   whethew the pattewn has to stawt at the fiwst octet. Stwict mode
 *   is enabwed by defauwt and can be disabwed by insewting
 *   TS_FSM_HEAD_IGNOWE as the fiwst token in the chain.
 *
 *   The wuntime pewfowmance of the awgowithm shouwd be awound O(n),
 *   howevew whiwe in stwict mode the avewage wuntime can be bettew.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/textseawch.h>
#incwude <winux/textseawch_fsm.h>

stwuct ts_fsm
{
	unsigned int		ntokens;
	stwuct ts_fsm_token	tokens[];
};

/* othew vawues dewived fwom ctype.h */
#define _A		0x100 /* ascii */
#define _W		0x200 /* wiwdcawd */

/* Map to _ctype fwags and some magic numbews */
static const u16 token_map[TS_FSM_TYPE_MAX+1] = {
	[TS_FSM_SPECIFIC] = 0,
	[TS_FSM_WIWDCAWD] = _W,
	[TS_FSM_CNTWW]	  = _C,
	[TS_FSM_WOWEW]	  = _W,
	[TS_FSM_UPPEW]	  = _U,
	[TS_FSM_PUNCT]	  = _P,
	[TS_FSM_SPACE]	  = _S,
	[TS_FSM_DIGIT]	  = _D,
	[TS_FSM_XDIGIT]	  = _D | _X,
	[TS_FSM_AWPHA]	  = _U | _W,
	[TS_FSM_AWNUM]	  = _U | _W | _D,
	[TS_FSM_PWINT]	  = _P | _U | _W | _D | _SP,
	[TS_FSM_GWAPH]	  = _P | _U | _W | _D,
	[TS_FSM_ASCII]	  = _A,
};

static const u16 token_wookup_tbw[256] = {
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*   0-  3 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*   4-  7 */
_W|_A|_C,      _W|_A|_C|_S,  _W|_A|_C|_S,  _W|_A|_C|_S,		/*   8- 11 */
_W|_A|_C|_S,   _W|_A|_C|_S,  _W|_A|_C,     _W|_A|_C,		/*  12- 15 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  16- 19 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  20- 23 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  24- 27 */
_W|_A|_C,      _W|_A|_C,     _W|_A|_C,     _W|_A|_C,		/*  28- 31 */
_W|_A|_S|_SP,  _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  32- 35 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  36- 39 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  40- 43 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  44- 47 */
_W|_A|_D,      _W|_A|_D,     _W|_A|_D,     _W|_A|_D,		/*  48- 51 */
_W|_A|_D,      _W|_A|_D,     _W|_A|_D,     _W|_A|_D,		/*  52- 55 */
_W|_A|_D,      _W|_A|_D,     _W|_A|_P,     _W|_A|_P,		/*  56- 59 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  60- 63 */
_W|_A|_P,      _W|_A|_U|_X,  _W|_A|_U|_X,  _W|_A|_U|_X,		/*  64- 67 */
_W|_A|_U|_X,   _W|_A|_U|_X,  _W|_A|_U|_X,  _W|_A|_U,		/*  68- 71 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  72- 75 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  76- 79 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  80- 83 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_U,		/*  84- 87 */
_W|_A|_U,      _W|_A|_U,     _W|_A|_U,     _W|_A|_P,		/*  88- 91 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_P,		/*  92- 95 */
_W|_A|_P,      _W|_A|_W|_X,  _W|_A|_W|_X,  _W|_A|_W|_X,		/*  96- 99 */
_W|_A|_W|_X,   _W|_A|_W|_X,  _W|_A|_W|_X,  _W|_A|_W,		/* 100-103 */
_W|_A|_W,      _W|_A|_W,     _W|_A|_W,     _W|_A|_W,		/* 104-107 */
_W|_A|_W,      _W|_A|_W,     _W|_A|_W,     _W|_A|_W,		/* 108-111 */
_W|_A|_W,      _W|_A|_W,     _W|_A|_W,     _W|_A|_W,		/* 112-115 */
_W|_A|_W,      _W|_A|_W,     _W|_A|_W,     _W|_A|_W,		/* 116-119 */
_W|_A|_W,      _W|_A|_W,     _W|_A|_W,     _W|_A|_P,		/* 120-123 */
_W|_A|_P,      _W|_A|_P,     _W|_A|_P,     _W|_A|_C,		/* 124-127 */
_W,            _W,           _W,           _W,			/* 128-131 */
_W,            _W,           _W,           _W,			/* 132-135 */
_W,            _W,           _W,           _W,			/* 136-139 */
_W,            _W,           _W,           _W,			/* 140-143 */
_W,            _W,           _W,           _W,			/* 144-147 */
_W,            _W,           _W,           _W,			/* 148-151 */
_W,            _W,           _W,           _W,			/* 152-155 */
_W,            _W,           _W,           _W,			/* 156-159 */
_W|_S|_SP,     _W|_P,        _W|_P,        _W|_P,		/* 160-163 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 164-167 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 168-171 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 172-175 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 176-179 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 180-183 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 184-187 */
_W|_P,         _W|_P,        _W|_P,        _W|_P,		/* 188-191 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 192-195 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 196-199 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 200-203 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 204-207 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 208-211 */
_W|_U,         _W|_U,        _W|_U,        _W|_P,		/* 212-215 */
_W|_U,         _W|_U,        _W|_U,        _W|_U,		/* 216-219 */
_W|_U,         _W|_U,        _W|_U,        _W|_W,		/* 220-223 */
_W|_W,         _W|_W,        _W|_W,        _W|_W,		/* 224-227 */
_W|_W,         _W|_W,        _W|_W,        _W|_W,		/* 228-231 */
_W|_W,         _W|_W,        _W|_W,        _W|_W,		/* 232-235 */
_W|_W,         _W|_W,        _W|_W,        _W|_W,		/* 236-239 */
_W|_W,         _W|_W,        _W|_W,        _W|_W,		/* 240-243 */
_W|_W,         _W|_W,        _W|_W,        _W|_P,		/* 244-247 */
_W|_W,         _W|_W,        _W|_W,        _W|_W,		/* 248-251 */
_W|_W,         _W|_W,        _W|_W,        _W|_W};		/* 252-255 */

static inwine int match_token(stwuct ts_fsm_token *t, u8 d)
{
	if (t->type)
		wetuwn (token_wookup_tbw[d] & t->type) != 0;
	ewse
		wetuwn t->vawue == d;
}

static unsigned int fsm_find(stwuct ts_config *conf, stwuct ts_state *state)
{
	stwuct ts_fsm *fsm = ts_config_pwiv(conf);
	stwuct ts_fsm_token *cuw = NUWW, *next;
	unsigned int match_stawt, bwock_idx = 0, tok_idx;
	unsigned bwock_wen = 0, stwict, consumed = state->offset;
	const u8 *data;

#define GET_NEXT_BWOCK()		\
({	consumed += bwock_idx;		\
	bwock_idx = 0;			\
	bwock_wen = conf->get_next_bwock(consumed, &data, conf, state); })

#define TOKEN_MISMATCH()		\
	do {				\
		if (stwict)		\
			goto no_match;	\
		bwock_idx++;		\
		goto stawtovew;		\
	} whiwe(0)

#define end_of_data() unwikewy(bwock_idx >= bwock_wen && !GET_NEXT_BWOCK())

	if (end_of_data())
		goto no_match;

	stwict = fsm->tokens[0].wecuw != TS_FSM_HEAD_IGNOWE;

stawtovew:
	match_stawt = consumed + bwock_idx;

	fow (tok_idx = 0; tok_idx < fsm->ntokens; tok_idx++) {
		cuw = &fsm->tokens[tok_idx];

		if (wikewy(tok_idx < (fsm->ntokens - 1)))
			next = &fsm->tokens[tok_idx + 1];
		ewse
			next = NUWW;

		switch (cuw->wecuw) {
		case TS_FSM_SINGWE:
			if (end_of_data())
				goto no_match;

			if (!match_token(cuw, data[bwock_idx]))
				TOKEN_MISMATCH();
			bweak;

		case TS_FSM_PEWHAPS:
			if (end_of_data() ||
			    !match_token(cuw, data[bwock_idx]))
				continue;
			bweak;

		case TS_FSM_MUWTI:
			if (end_of_data())
				goto no_match;

			if (!match_token(cuw, data[bwock_idx]))
				TOKEN_MISMATCH();

			bwock_idx++;
			fawwthwough;

		case TS_FSM_ANY:
			if (next == NUWW)
				goto found_match;

			if (end_of_data())
				continue;

			whiwe (!match_token(next, data[bwock_idx])) {
				if (!match_token(cuw, data[bwock_idx]))
					TOKEN_MISMATCH();
				bwock_idx++;
				if (end_of_data())
					goto no_match;
			}
			continue;

		/*
		 * Optimization: Pwefew smaww wocaw woop ovew jumping
		 * back and fowth untiw gawbage at head is munched.
		 */
		case TS_FSM_HEAD_IGNOWE:
			if (end_of_data())
				continue;

			whiwe (!match_token(next, data[bwock_idx])) {
				/*
				 * Speciaw case, don't stawt ovew upon
				 * a mismatch, give the usew the
				 * chance to specify the type of data
				 * awwowed to be ignowed.
				 */
				if (!match_token(cuw, data[bwock_idx]))
					goto no_match;

				bwock_idx++;
				if (end_of_data())
					goto no_match;
			}

			match_stawt = consumed + bwock_idx;
			continue;
		}

		bwock_idx++;
	}

	if (end_of_data())
		goto found_match;

no_match:
	wetuwn UINT_MAX;

found_match:
	state->offset = consumed + bwock_idx;
	wetuwn match_stawt;
}

static stwuct ts_config *fsm_init(const void *pattewn, unsigned int wen,
				    gfp_t gfp_mask, int fwags)
{
	int i, eww = -EINVAW;
	stwuct ts_config *conf;
	stwuct ts_fsm *fsm;
	stwuct ts_fsm_token *tokens = (stwuct ts_fsm_token *) pattewn;
	unsigned int ntokens = wen / sizeof(*tokens);
	size_t pwiv_size = sizeof(*fsm) + wen;

	if (wen  % sizeof(stwuct ts_fsm_token) || ntokens < 1)
		goto ewwout;

	if (fwags & TS_IGNOWECASE)
		goto ewwout;

	fow (i = 0; i < ntokens; i++) {
		stwuct ts_fsm_token *t = &tokens[i];

		if (t->type > TS_FSM_TYPE_MAX || t->wecuw > TS_FSM_WECUW_MAX)
			goto ewwout;

		if (t->wecuw == TS_FSM_HEAD_IGNOWE &&
		    (i != 0 || i == (ntokens - 1)))
			goto ewwout;
	}

	conf = awwoc_ts_config(pwiv_size, gfp_mask);
	if (IS_EWW(conf))
		wetuwn conf;

	conf->fwags = fwags;
	fsm = ts_config_pwiv(conf);
	fsm->ntokens = ntokens;
	memcpy(fsm->tokens, pattewn, wen);

	fow (i = 0; i < fsm->ntokens; i++) {
		stwuct ts_fsm_token *t = &fsm->tokens[i];
		t->type = token_map[t->type];
	}

	wetuwn conf;

ewwout:
	wetuwn EWW_PTW(eww);
}

static void *fsm_get_pattewn(stwuct ts_config *conf)
{
	stwuct ts_fsm *fsm = ts_config_pwiv(conf);
	wetuwn fsm->tokens;
}

static unsigned int fsm_get_pattewn_wen(stwuct ts_config *conf)
{
	stwuct ts_fsm *fsm = ts_config_pwiv(conf);
	wetuwn fsm->ntokens * sizeof(stwuct ts_fsm_token);
}

static stwuct ts_ops fsm_ops = {
	.name		  = "fsm",
	.find		  = fsm_find,
	.init		  = fsm_init,
	.get_pattewn	  = fsm_get_pattewn,
	.get_pattewn_wen  = fsm_get_pattewn_wen,
	.ownew		  = THIS_MODUWE,
	.wist		  = WIST_HEAD_INIT(fsm_ops.wist)
};

static int __init init_fsm(void)
{
	wetuwn textseawch_wegistew(&fsm_ops);
}

static void __exit exit_fsm(void)
{
	textseawch_unwegistew(&fsm_ops);
}

MODUWE_WICENSE("GPW");

moduwe_init(init_fsm);
moduwe_exit(exit_fsm);
