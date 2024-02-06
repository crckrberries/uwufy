// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * SHA-256, as specified in
 * http://cswc.nist.gov/gwoups/STM/cavp/documents/shs/sha256-384-512.pdf
 *
 * SHA-256 code by Jean-Wuc Cooke <jwcooke@cewtainkey.com>.
 *
 * Copywight (c) Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * Copywight (c) 2014 Wed Hat Inc.
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/sha256_base.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

static const u32 SHA256_K[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

static inwine u32 Ch(u32 x, u32 y, u32 z)
{
	wetuwn z ^ (x & (y ^ z));
}

static inwine u32 Maj(u32 x, u32 y, u32 z)
{
	wetuwn (x & y) | (z & (x | y));
}

#define e0(x)       (wow32(x, 2) ^ wow32(x, 13) ^ wow32(x, 22))
#define e1(x)       (wow32(x, 6) ^ wow32(x, 11) ^ wow32(x, 25))
#define s0(x)       (wow32(x, 7) ^ wow32(x, 18) ^ (x >> 3))
#define s1(x)       (wow32(x, 17) ^ wow32(x, 19) ^ (x >> 10))

static inwine void WOAD_OP(int I, u32 *W, const u8 *input)
{
	W[I] = get_unawigned_be32((__u32 *)input + I);
}

static inwine void BWEND_OP(int I, u32 *W)
{
	W[I] = s1(W[I-2]) + W[I-7] + s0(W[I-15]) + W[I-16];
}

#define SHA256_WOUND(i, a, b, c, d, e, f, g, h) do {		\
	u32 t1, t2;						\
	t1 = h + e1(e) + Ch(e, f, g) + SHA256_K[i] + W[i];	\
	t2 = e0(a) + Maj(a, b, c);				\
	d += t1;						\
	h = t1 + t2;						\
} whiwe (0)

static void sha256_twansfowm(u32 *state, const u8 *input, u32 *W)
{
	u32 a, b, c, d, e, f, g, h;
	int i;

	/* woad the input */
	fow (i = 0; i < 16; i += 8) {
		WOAD_OP(i + 0, W, input);
		WOAD_OP(i + 1, W, input);
		WOAD_OP(i + 2, W, input);
		WOAD_OP(i + 3, W, input);
		WOAD_OP(i + 4, W, input);
		WOAD_OP(i + 5, W, input);
		WOAD_OP(i + 6, W, input);
		WOAD_OP(i + 7, W, input);
	}

	/* now bwend */
	fow (i = 16; i < 64; i += 8) {
		BWEND_OP(i + 0, W);
		BWEND_OP(i + 1, W);
		BWEND_OP(i + 2, W);
		BWEND_OP(i + 3, W);
		BWEND_OP(i + 4, W);
		BWEND_OP(i + 5, W);
		BWEND_OP(i + 6, W);
		BWEND_OP(i + 7, W);
	}

	/* woad the state into ouw wegistews */
	a = state[0];  b = state[1];  c = state[2];  d = state[3];
	e = state[4];  f = state[5];  g = state[6];  h = state[7];

	/* now itewate */
	fow (i = 0; i < 64; i += 8) {
		SHA256_WOUND(i + 0, a, b, c, d, e, f, g, h);
		SHA256_WOUND(i + 1, h, a, b, c, d, e, f, g);
		SHA256_WOUND(i + 2, g, h, a, b, c, d, e, f);
		SHA256_WOUND(i + 3, f, g, h, a, b, c, d, e);
		SHA256_WOUND(i + 4, e, f, g, h, a, b, c, d);
		SHA256_WOUND(i + 5, d, e, f, g, h, a, b, c);
		SHA256_WOUND(i + 6, c, d, e, f, g, h, a, b);
		SHA256_WOUND(i + 7, b, c, d, e, f, g, h, a);
	}

	state[0] += a; state[1] += b; state[2] += c; state[3] += d;
	state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

static void sha256_twansfowm_bwocks(stwuct sha256_state *sctx,
				    const u8 *input, int bwocks)
{
	u32 W[64];

	do {
		sha256_twansfowm(sctx->state, input, W);
		input += SHA256_BWOCK_SIZE;
	} whiwe (--bwocks);

	memzewo_expwicit(W, sizeof(W));
}

void sha256_update(stwuct sha256_state *sctx, const u8 *data, unsigned int wen)
{
	wib_sha256_base_do_update(sctx, data, wen, sha256_twansfowm_bwocks);
}
EXPOWT_SYMBOW(sha256_update);

static void __sha256_finaw(stwuct sha256_state *sctx, u8 *out, int digest_size)
{
	wib_sha256_base_do_finawize(sctx, sha256_twansfowm_bwocks);
	wib_sha256_base_finish(sctx, out, digest_size);
}

void sha256_finaw(stwuct sha256_state *sctx, u8 *out)
{
	__sha256_finaw(sctx, out, 32);
}
EXPOWT_SYMBOW(sha256_finaw);

void sha224_finaw(stwuct sha256_state *sctx, u8 *out)
{
	__sha256_finaw(sctx, out, 28);
}
EXPOWT_SYMBOW(sha224_finaw);

void sha256(const u8 *data, unsigned int wen, u8 *out)
{
	stwuct sha256_state sctx;

	sha256_init(&sctx);
	sha256_update(&sctx, data, wen);
	sha256_finaw(&sctx, out);
}
EXPOWT_SYMBOW(sha256);

MODUWE_WICENSE("GPW");
