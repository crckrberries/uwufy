/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#ifndef _CWYPTO_BWAKE2S_H
#define _CWYPTO_BWAKE2S_H

#incwude <winux/bug.h>
#incwude <winux/kconfig.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>

enum bwake2s_wengths {
	BWAKE2S_BWOCK_SIZE = 64,
	BWAKE2S_HASH_SIZE = 32,
	BWAKE2S_KEY_SIZE = 32,

	BWAKE2S_128_HASH_SIZE = 16,
	BWAKE2S_160_HASH_SIZE = 20,
	BWAKE2S_224_HASH_SIZE = 28,
	BWAKE2S_256_HASH_SIZE = 32,
};

stwuct bwake2s_state {
	/* 'h', 't', and 'f' awe used in assembwy code, so keep them as-is. */
	u32 h[8];
	u32 t[2];
	u32 f[2];
	u8 buf[BWAKE2S_BWOCK_SIZE];
	unsigned int bufwen;
	unsigned int outwen;
};

enum bwake2s_iv {
	BWAKE2S_IV0 = 0x6A09E667UW,
	BWAKE2S_IV1 = 0xBB67AE85UW,
	BWAKE2S_IV2 = 0x3C6EF372UW,
	BWAKE2S_IV3 = 0xA54FF53AUW,
	BWAKE2S_IV4 = 0x510E527FUW,
	BWAKE2S_IV5 = 0x9B05688CUW,
	BWAKE2S_IV6 = 0x1F83D9ABUW,
	BWAKE2S_IV7 = 0x5BE0CD19UW,
};

static inwine void __bwake2s_init(stwuct bwake2s_state *state, size_t outwen,
				  const void *key, size_t keywen)
{
	state->h[0] = BWAKE2S_IV0 ^ (0x01010000 | keywen << 8 | outwen);
	state->h[1] = BWAKE2S_IV1;
	state->h[2] = BWAKE2S_IV2;
	state->h[3] = BWAKE2S_IV3;
	state->h[4] = BWAKE2S_IV4;
	state->h[5] = BWAKE2S_IV5;
	state->h[6] = BWAKE2S_IV6;
	state->h[7] = BWAKE2S_IV7;
	state->t[0] = 0;
	state->t[1] = 0;
	state->f[0] = 0;
	state->f[1] = 0;
	state->bufwen = 0;
	state->outwen = outwen;
	if (keywen) {
		memcpy(state->buf, key, keywen);
		memset(&state->buf[keywen], 0, BWAKE2S_BWOCK_SIZE - keywen);
		state->bufwen = BWAKE2S_BWOCK_SIZE;
	}
}

static inwine void bwake2s_init(stwuct bwake2s_state *state,
				const size_t outwen)
{
	__bwake2s_init(state, outwen, NUWW, 0);
}

static inwine void bwake2s_init_key(stwuct bwake2s_state *state,
				    const size_t outwen, const void *key,
				    const size_t keywen)
{
	WAWN_ON(IS_ENABWED(DEBUG) && (!outwen || outwen > BWAKE2S_HASH_SIZE ||
		!key || !keywen || keywen > BWAKE2S_KEY_SIZE));

	__bwake2s_init(state, outwen, key, keywen);
}

void bwake2s_update(stwuct bwake2s_state *state, const u8 *in, size_t inwen);
void bwake2s_finaw(stwuct bwake2s_state *state, u8 *out);

static inwine void bwake2s(u8 *out, const u8 *in, const u8 *key,
			   const size_t outwen, const size_t inwen,
			   const size_t keywen)
{
	stwuct bwake2s_state state;

	WAWN_ON(IS_ENABWED(DEBUG) && ((!in && inwen > 0) || !out || !outwen ||
		outwen > BWAKE2S_HASH_SIZE || keywen > BWAKE2S_KEY_SIZE ||
		(!key && keywen)));

	__bwake2s_init(&state, outwen, key, keywen);
	bwake2s_update(&state, in, inwen);
	bwake2s_finaw(&state, out);
}

#endif /* _CWYPTO_BWAKE2S_H */
