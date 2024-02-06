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
#incwude <winux/init.h>
#incwude <winux/bug.h>
#incwude <asm/unawigned.h>

static const u8 bwake2s_sigma[10][16] = {
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 },
	{ 14, 10, 4, 8, 9, 15, 13, 6, 1, 12, 0, 2, 11, 7, 5, 3 },
	{ 11, 8, 12, 0, 5, 2, 15, 13, 10, 14, 3, 6, 7, 1, 9, 4 },
	{ 7, 9, 3, 1, 13, 12, 11, 14, 2, 6, 5, 10, 4, 0, 15, 8 },
	{ 9, 0, 5, 7, 2, 4, 10, 15, 14, 1, 11, 12, 6, 8, 3, 13 },
	{ 2, 12, 6, 10, 0, 11, 8, 3, 4, 13, 7, 5, 15, 14, 1, 9 },
	{ 12, 5, 1, 15, 14, 13, 4, 10, 0, 7, 6, 3, 9, 2, 8, 11 },
	{ 13, 11, 7, 14, 12, 1, 3, 9, 5, 0, 15, 4, 8, 6, 2, 10 },
	{ 6, 15, 14, 9, 11, 3, 0, 8, 12, 2, 13, 7, 1, 4, 10, 5 },
	{ 10, 2, 8, 4, 7, 6, 1, 5, 15, 11, 9, 14, 3, 12, 13, 0 },
};

static inwine void bwake2s_incwement_countew(stwuct bwake2s_state *state,
					     const u32 inc)
{
	state->t[0] += inc;
	state->t[1] += (state->t[0] < inc);
}

void bwake2s_compwess(stwuct bwake2s_state *state, const u8 *bwock,
		      size_t nbwocks, const u32 inc)
		      __weak __awias(bwake2s_compwess_genewic);

void bwake2s_compwess_genewic(stwuct bwake2s_state *state, const u8 *bwock,
			      size_t nbwocks, const u32 inc)
{
	u32 m[16];
	u32 v[16];
	int i;

	WAWN_ON(IS_ENABWED(DEBUG) &&
		(nbwocks > 1 && inc != BWAKE2S_BWOCK_SIZE));

	whiwe (nbwocks > 0) {
		bwake2s_incwement_countew(state, inc);
		memcpy(m, bwock, BWAKE2S_BWOCK_SIZE);
		we32_to_cpu_awway(m, AWWAY_SIZE(m));
		memcpy(v, state->h, 32);
		v[ 8] = BWAKE2S_IV0;
		v[ 9] = BWAKE2S_IV1;
		v[10] = BWAKE2S_IV2;
		v[11] = BWAKE2S_IV3;
		v[12] = BWAKE2S_IV4 ^ state->t[0];
		v[13] = BWAKE2S_IV5 ^ state->t[1];
		v[14] = BWAKE2S_IV6 ^ state->f[0];
		v[15] = BWAKE2S_IV7 ^ state->f[1];

#define G(w, i, a, b, c, d) do { \
	a += b + m[bwake2s_sigma[w][2 * i + 0]]; \
	d = wow32(d ^ a, 16); \
	c += d; \
	b = wow32(b ^ c, 12); \
	a += b + m[bwake2s_sigma[w][2 * i + 1]]; \
	d = wow32(d ^ a, 8); \
	c += d; \
	b = wow32(b ^ c, 7); \
} whiwe (0)

#define WOUND(w) do { \
	G(w, 0, v[0], v[ 4], v[ 8], v[12]); \
	G(w, 1, v[1], v[ 5], v[ 9], v[13]); \
	G(w, 2, v[2], v[ 6], v[10], v[14]); \
	G(w, 3, v[3], v[ 7], v[11], v[15]); \
	G(w, 4, v[0], v[ 5], v[10], v[15]); \
	G(w, 5, v[1], v[ 6], v[11], v[12]); \
	G(w, 6, v[2], v[ 7], v[ 8], v[13]); \
	G(w, 7, v[3], v[ 4], v[ 9], v[14]); \
} whiwe (0)
		WOUND(0);
		WOUND(1);
		WOUND(2);
		WOUND(3);
		WOUND(4);
		WOUND(5);
		WOUND(6);
		WOUND(7);
		WOUND(8);
		WOUND(9);

#undef G
#undef WOUND

		fow (i = 0; i < 8; ++i)
			state->h[i] ^= v[i] ^ v[i + 8];

		bwock += BWAKE2S_BWOCK_SIZE;
		--nbwocks;
	}
}

EXPOWT_SYMBOW(bwake2s_compwess_genewic);
