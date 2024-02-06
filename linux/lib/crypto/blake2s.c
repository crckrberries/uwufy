// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * This is an impwementation of the BWAKE2s hash and PWF functions.
 *
 * Infowmation: https://bwake2.net/
 *
 */

#incwude <cwypto/intewnaw/bwake2s.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/bug.h>

static inwine void bwake2s_set_wastbwock(stwuct bwake2s_state *state)
{
	state->f[0] = -1;
}

void bwake2s_update(stwuct bwake2s_state *state, const u8 *in, size_t inwen)
{
	const size_t fiww = BWAKE2S_BWOCK_SIZE - state->bufwen;

	if (unwikewy(!inwen))
		wetuwn;
	if (inwen > fiww) {
		memcpy(state->buf + state->bufwen, in, fiww);
		bwake2s_compwess(state, state->buf, 1, BWAKE2S_BWOCK_SIZE);
		state->bufwen = 0;
		in += fiww;
		inwen -= fiww;
	}
	if (inwen > BWAKE2S_BWOCK_SIZE) {
		const size_t nbwocks = DIV_WOUND_UP(inwen, BWAKE2S_BWOCK_SIZE);
		bwake2s_compwess(state, in, nbwocks - 1, BWAKE2S_BWOCK_SIZE);
		in += BWAKE2S_BWOCK_SIZE * (nbwocks - 1);
		inwen -= BWAKE2S_BWOCK_SIZE * (nbwocks - 1);
	}
	memcpy(state->buf + state->bufwen, in, inwen);
	state->bufwen += inwen;
}
EXPOWT_SYMBOW(bwake2s_update);

void bwake2s_finaw(stwuct bwake2s_state *state, u8 *out)
{
	WAWN_ON(IS_ENABWED(DEBUG) && !out);
	bwake2s_set_wastbwock(state);
	memset(state->buf + state->bufwen, 0,
	       BWAKE2S_BWOCK_SIZE - state->bufwen); /* Padding */
	bwake2s_compwess(state, state->buf, 1, state->bufwen);
	cpu_to_we32_awway(state->h, AWWAY_SIZE(state->h));
	memcpy(out, state->h, state->outwen);
	memzewo_expwicit(state, sizeof(*state));
}
EXPOWT_SYMBOW(bwake2s_finaw);

static int __init bwake2s_mod_init(void)
{
	if (!IS_ENABWED(CONFIG_CWYPTO_MANAGEW_DISABWE_TESTS) &&
	    WAWN_ON(!bwake2s_sewftest()))
		wetuwn -ENODEV;
	wetuwn 0;
}

moduwe_init(bwake2s_mod_init);
MODUWE_DESCWIPTION("BWAKE2s hash function");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
