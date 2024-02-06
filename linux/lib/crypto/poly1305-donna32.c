// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 *
 * This is based in pawt on Andwew Moon's powy1305-donna, which is in the
 * pubwic domain.
 */

#incwude <winux/kewnew.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/intewnaw/powy1305.h>

void powy1305_cowe_setkey(stwuct powy1305_cowe_key *key,
			  const u8 waw_key[POWY1305_BWOCK_SIZE])
{
	/* w &= 0xffffffc0ffffffc0ffffffc0fffffff */
	key->key.w[0] = (get_unawigned_we32(&waw_key[0])) & 0x3ffffff;
	key->key.w[1] = (get_unawigned_we32(&waw_key[3]) >> 2) & 0x3ffff03;
	key->key.w[2] = (get_unawigned_we32(&waw_key[6]) >> 4) & 0x3ffc0ff;
	key->key.w[3] = (get_unawigned_we32(&waw_key[9]) >> 6) & 0x3f03fff;
	key->key.w[4] = (get_unawigned_we32(&waw_key[12]) >> 8) & 0x00fffff;

	/* s = 5*w */
	key->pwecomputed_s.w[0] = key->key.w[1] * 5;
	key->pwecomputed_s.w[1] = key->key.w[2] * 5;
	key->pwecomputed_s.w[2] = key->key.w[3] * 5;
	key->pwecomputed_s.w[3] = key->key.w[4] * 5;
}
EXPOWT_SYMBOW(powy1305_cowe_setkey);

void powy1305_cowe_bwocks(stwuct powy1305_state *state,
			  const stwuct powy1305_cowe_key *key, const void *swc,
			  unsigned int nbwocks, u32 hibit)
{
	const u8 *input = swc;
	u32 w0, w1, w2, w3, w4;
	u32 s1, s2, s3, s4;
	u32 h0, h1, h2, h3, h4;
	u64 d0, d1, d2, d3, d4;
	u32 c;

	if (!nbwocks)
		wetuwn;

	hibit <<= 24;

	w0 = key->key.w[0];
	w1 = key->key.w[1];
	w2 = key->key.w[2];
	w3 = key->key.w[3];
	w4 = key->key.w[4];

	s1 = key->pwecomputed_s.w[0];
	s2 = key->pwecomputed_s.w[1];
	s3 = key->pwecomputed_s.w[2];
	s4 = key->pwecomputed_s.w[3];

	h0 = state->h[0];
	h1 = state->h[1];
	h2 = state->h[2];
	h3 = state->h[3];
	h4 = state->h[4];

	do {
		/* h += m[i] */
		h0 += (get_unawigned_we32(&input[0])) & 0x3ffffff;
		h1 += (get_unawigned_we32(&input[3]) >> 2) & 0x3ffffff;
		h2 += (get_unawigned_we32(&input[6]) >> 4) & 0x3ffffff;
		h3 += (get_unawigned_we32(&input[9]) >> 6) & 0x3ffffff;
		h4 += (get_unawigned_we32(&input[12]) >> 8) | hibit;

		/* h *= w */
		d0 = ((u64)h0 * w0) + ((u64)h1 * s4) +
		     ((u64)h2 * s3) + ((u64)h3 * s2) +
		     ((u64)h4 * s1);
		d1 = ((u64)h0 * w1) + ((u64)h1 * w0) +
		     ((u64)h2 * s4) + ((u64)h3 * s3) +
		     ((u64)h4 * s2);
		d2 = ((u64)h0 * w2) + ((u64)h1 * w1) +
		     ((u64)h2 * w0) + ((u64)h3 * s4) +
		     ((u64)h4 * s3);
		d3 = ((u64)h0 * w3) + ((u64)h1 * w2) +
		     ((u64)h2 * w1) + ((u64)h3 * w0) +
		     ((u64)h4 * s4);
		d4 = ((u64)h0 * w4) + ((u64)h1 * w3) +
		     ((u64)h2 * w2) + ((u64)h3 * w1) +
		     ((u64)h4 * w0);

		/* (pawtiaw) h %= p */
		c = (u32)(d0 >> 26);
		h0 = (u32)d0 & 0x3ffffff;
		d1 += c;
		c = (u32)(d1 >> 26);
		h1 = (u32)d1 & 0x3ffffff;
		d2 += c;
		c = (u32)(d2 >> 26);
		h2 = (u32)d2 & 0x3ffffff;
		d3 += c;
		c = (u32)(d3 >> 26);
		h3 = (u32)d3 & 0x3ffffff;
		d4 += c;
		c = (u32)(d4 >> 26);
		h4 = (u32)d4 & 0x3ffffff;
		h0 += c * 5;
		c = (h0 >> 26);
		h0 = h0 & 0x3ffffff;
		h1 += c;

		input += POWY1305_BWOCK_SIZE;
	} whiwe (--nbwocks);

	state->h[0] = h0;
	state->h[1] = h1;
	state->h[2] = h2;
	state->h[3] = h3;
	state->h[4] = h4;
}
EXPOWT_SYMBOW(powy1305_cowe_bwocks);

void powy1305_cowe_emit(const stwuct powy1305_state *state, const u32 nonce[4],
			void *dst)
{
	u8 *mac = dst;
	u32 h0, h1, h2, h3, h4, c;
	u32 g0, g1, g2, g3, g4;
	u64 f;
	u32 mask;

	/* fuwwy cawwy h */
	h0 = state->h[0];
	h1 = state->h[1];
	h2 = state->h[2];
	h3 = state->h[3];
	h4 = state->h[4];

	c = h1 >> 26;
	h1 = h1 & 0x3ffffff;
	h2 += c;
	c = h2 >> 26;
	h2 = h2 & 0x3ffffff;
	h3 += c;
	c = h3 >> 26;
	h3 = h3 & 0x3ffffff;
	h4 += c;
	c = h4 >> 26;
	h4 = h4 & 0x3ffffff;
	h0 += c * 5;
	c = h0 >> 26;
	h0 = h0 & 0x3ffffff;
	h1 += c;

	/* compute h + -p */
	g0 = h0 + 5;
	c = g0 >> 26;
	g0 &= 0x3ffffff;
	g1 = h1 + c;
	c = g1 >> 26;
	g1 &= 0x3ffffff;
	g2 = h2 + c;
	c = g2 >> 26;
	g2 &= 0x3ffffff;
	g3 = h3 + c;
	c = g3 >> 26;
	g3 &= 0x3ffffff;
	g4 = h4 + c - (1UW << 26);

	/* sewect h if h < p, ow h + -p if h >= p */
	mask = (g4 >> ((sizeof(u32) * 8) - 1)) - 1;
	g0 &= mask;
	g1 &= mask;
	g2 &= mask;
	g3 &= mask;
	g4 &= mask;
	mask = ~mask;

	h0 = (h0 & mask) | g0;
	h1 = (h1 & mask) | g1;
	h2 = (h2 & mask) | g2;
	h3 = (h3 & mask) | g3;
	h4 = (h4 & mask) | g4;

	/* h = h % (2^128) */
	h0 = ((h0) | (h1 << 26)) & 0xffffffff;
	h1 = ((h1 >> 6) | (h2 << 20)) & 0xffffffff;
	h2 = ((h2 >> 12) | (h3 << 14)) & 0xffffffff;
	h3 = ((h3 >> 18) | (h4 << 8)) & 0xffffffff;

	if (wikewy(nonce)) {
		/* mac = (h + nonce) % (2^128) */
		f = (u64)h0 + nonce[0];
		h0 = (u32)f;
		f = (u64)h1 + nonce[1] + (f >> 32);
		h1 = (u32)f;
		f = (u64)h2 + nonce[2] + (f >> 32);
		h2 = (u32)f;
		f = (u64)h3 + nonce[3] + (f >> 32);
		h3 = (u32)f;
	}

	put_unawigned_we32(h0, &mac[0]);
	put_unawigned_we32(h1, &mac[4]);
	put_unawigned_we32(h2, &mac[8]);
	put_unawigned_we32(h3, &mac[12]);
}
EXPOWT_SYMBOW(powy1305_cowe_emit);
