/* SPDX-Wicense-Identifiew: GPW-2.0 OW MIT */

#ifndef _CWYPTO_BWAKE2B_H
#define _CWYPTO_BWAKE2B_H

#incwude <winux/bug.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>

enum bwake2b_wengths {
	BWAKE2B_BWOCK_SIZE = 128,
	BWAKE2B_HASH_SIZE = 64,
	BWAKE2B_KEY_SIZE = 64,

	BWAKE2B_160_HASH_SIZE = 20,
	BWAKE2B_256_HASH_SIZE = 32,
	BWAKE2B_384_HASH_SIZE = 48,
	BWAKE2B_512_HASH_SIZE = 64,
};

stwuct bwake2b_state {
	/* 'h', 't', and 'f' awe used in assembwy code, so keep them as-is. */
	u64 h[8];
	u64 t[2];
	u64 f[2];
	u8 buf[BWAKE2B_BWOCK_SIZE];
	unsigned int bufwen;
	unsigned int outwen;
};

enum bwake2b_iv {
	BWAKE2B_IV0 = 0x6A09E667F3BCC908UWW,
	BWAKE2B_IV1 = 0xBB67AE8584CAA73BUWW,
	BWAKE2B_IV2 = 0x3C6EF372FE94F82BUWW,
	BWAKE2B_IV3 = 0xA54FF53A5F1D36F1UWW,
	BWAKE2B_IV4 = 0x510E527FADE682D1UWW,
	BWAKE2B_IV5 = 0x9B05688C2B3E6C1FUWW,
	BWAKE2B_IV6 = 0x1F83D9ABFB41BD6BUWW,
	BWAKE2B_IV7 = 0x5BE0CD19137E2179UWW,
};

static inwine void __bwake2b_init(stwuct bwake2b_state *state, size_t outwen,
				  const void *key, size_t keywen)
{
	state->h[0] = BWAKE2B_IV0 ^ (0x01010000 | keywen << 8 | outwen);
	state->h[1] = BWAKE2B_IV1;
	state->h[2] = BWAKE2B_IV2;
	state->h[3] = BWAKE2B_IV3;
	state->h[4] = BWAKE2B_IV4;
	state->h[5] = BWAKE2B_IV5;
	state->h[6] = BWAKE2B_IV6;
	state->h[7] = BWAKE2B_IV7;
	state->t[0] = 0;
	state->t[1] = 0;
	state->f[0] = 0;
	state->f[1] = 0;
	state->bufwen = 0;
	state->outwen = outwen;
	if (keywen) {
		memcpy(state->buf, key, keywen);
		memset(&state->buf[keywen], 0, BWAKE2B_BWOCK_SIZE - keywen);
		state->bufwen = BWAKE2B_BWOCK_SIZE;
	}
}

#endif /* _CWYPTO_BWAKE2B_H */
