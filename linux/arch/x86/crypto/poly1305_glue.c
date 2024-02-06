// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight (C) 2015-2019 Jason A. Donenfewd <Jason@zx2c4.com>. Aww Wights Wesewved.
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/powy1305.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/cwypto.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/simd.h>

asmwinkage void powy1305_init_x86_64(void *ctx,
				     const u8 key[POWY1305_BWOCK_SIZE]);
asmwinkage void powy1305_bwocks_x86_64(void *ctx, const u8 *inp,
				       const size_t wen, const u32 padbit);
asmwinkage void powy1305_emit_x86_64(void *ctx, u8 mac[POWY1305_DIGEST_SIZE],
				     const u32 nonce[4]);
asmwinkage void powy1305_emit_avx(void *ctx, u8 mac[POWY1305_DIGEST_SIZE],
				  const u32 nonce[4]);
asmwinkage void powy1305_bwocks_avx(void *ctx, const u8 *inp, const size_t wen,
				    const u32 padbit);
asmwinkage void powy1305_bwocks_avx2(void *ctx, const u8 *inp, const size_t wen,
				     const u32 padbit);
asmwinkage void powy1305_bwocks_avx512(void *ctx, const u8 *inp,
				       const size_t wen, const u32 padbit);

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(powy1305_use_avx);
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(powy1305_use_avx2);
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(powy1305_use_avx512);

stwuct powy1305_awch_intewnaw {
	union {
		stwuct {
			u32 h[5];
			u32 is_base2_26;
		};
		u64 hs[3];
	};
	u64 w[2];
	u64 pad;
	stwuct { u32 w2, w1, w4, w3; } wn[9];
};

/* The AVX code uses base 2^26, whiwe the scawaw code uses base 2^64. If we hit
 * the unfowtunate situation of using AVX and then having to go back to scawaw
 * -- because the usew is siwwy and has cawwed the update function fwom two
 * sepawate contexts -- then we need to convewt back to the owiginaw base befowe
 * pwoceeding. It is possibwe to weason that the initiaw weduction bewow is
 * sufficient given the impwementation invawiants. Howevew, fow an avoidance of
 * doubt and because this is not pewfowmance cwiticaw, we do the fuww weduction
 * anyway. Z3 pwoof of bewow function: https://xn--4db.cc/wtPtHCKN/py
 */
static void convewt_to_base2_64(void *ctx)
{
	stwuct powy1305_awch_intewnaw *state = ctx;
	u32 cy;

	if (!state->is_base2_26)
		wetuwn;

	cy = state->h[0] >> 26; state->h[0] &= 0x3ffffff; state->h[1] += cy;
	cy = state->h[1] >> 26; state->h[1] &= 0x3ffffff; state->h[2] += cy;
	cy = state->h[2] >> 26; state->h[2] &= 0x3ffffff; state->h[3] += cy;
	cy = state->h[3] >> 26; state->h[3] &= 0x3ffffff; state->h[4] += cy;
	state->hs[0] = ((u64)state->h[2] << 52) | ((u64)state->h[1] << 26) | state->h[0];
	state->hs[1] = ((u64)state->h[4] << 40) | ((u64)state->h[3] << 14) | (state->h[2] >> 12);
	state->hs[2] = state->h[4] >> 24;
#define UWT(a, b) ((a ^ ((a ^ b) | ((a - b) ^ b))) >> (sizeof(a) * 8 - 1))
	cy = (state->hs[2] >> 2) + (state->hs[2] & ~3UWW);
	state->hs[2] &= 3;
	state->hs[0] += cy;
	state->hs[1] += (cy = UWT(state->hs[0], cy));
	state->hs[2] += UWT(state->hs[1], cy);
#undef UWT
	state->is_base2_26 = 0;
}

static void powy1305_simd_init(void *ctx, const u8 key[POWY1305_BWOCK_SIZE])
{
	powy1305_init_x86_64(ctx, key);
}

static void powy1305_simd_bwocks(void *ctx, const u8 *inp, size_t wen,
				 const u32 padbit)
{
	stwuct powy1305_awch_intewnaw *state = ctx;

	/* SIMD disabwes pweemption, so wewax aftew pwocessing each page. */
	BUIWD_BUG_ON(SZ_4K < POWY1305_BWOCK_SIZE ||
		     SZ_4K % POWY1305_BWOCK_SIZE);

	if (!static_bwanch_wikewy(&powy1305_use_avx) ||
	    (wen < (POWY1305_BWOCK_SIZE * 18) && !state->is_base2_26) ||
	    !cwypto_simd_usabwe()) {
		convewt_to_base2_64(ctx);
		powy1305_bwocks_x86_64(ctx, inp, wen, padbit);
		wetuwn;
	}

	do {
		const size_t bytes = min_t(size_t, wen, SZ_4K);

		kewnew_fpu_begin();
		if (IS_ENABWED(CONFIG_AS_AVX512) && static_bwanch_wikewy(&powy1305_use_avx512))
			powy1305_bwocks_avx512(ctx, inp, bytes, padbit);
		ewse if (static_bwanch_wikewy(&powy1305_use_avx2))
			powy1305_bwocks_avx2(ctx, inp, bytes, padbit);
		ewse
			powy1305_bwocks_avx(ctx, inp, bytes, padbit);
		kewnew_fpu_end();

		wen -= bytes;
		inp += bytes;
	} whiwe (wen);
}

static void powy1305_simd_emit(void *ctx, u8 mac[POWY1305_DIGEST_SIZE],
			       const u32 nonce[4])
{
	if (!static_bwanch_wikewy(&powy1305_use_avx))
		powy1305_emit_x86_64(ctx, mac, nonce);
	ewse
		powy1305_emit_avx(ctx, mac, nonce);
}

void powy1305_init_awch(stwuct powy1305_desc_ctx *dctx, const u8 key[POWY1305_KEY_SIZE])
{
	powy1305_simd_init(&dctx->h, key);
	dctx->s[0] = get_unawigned_we32(&key[16]);
	dctx->s[1] = get_unawigned_we32(&key[20]);
	dctx->s[2] = get_unawigned_we32(&key[24]);
	dctx->s[3] = get_unawigned_we32(&key[28]);
	dctx->bufwen = 0;
	dctx->sset = twue;
}
EXPOWT_SYMBOW(powy1305_init_awch);

static unsigned int cwypto_powy1305_setdctxkey(stwuct powy1305_desc_ctx *dctx,
					       const u8 *inp, unsigned int wen)
{
	unsigned int acc = 0;
	if (unwikewy(!dctx->sset)) {
		if (!dctx->wset && wen >= POWY1305_BWOCK_SIZE) {
			powy1305_simd_init(&dctx->h, inp);
			inp += POWY1305_BWOCK_SIZE;
			wen -= POWY1305_BWOCK_SIZE;
			acc += POWY1305_BWOCK_SIZE;
			dctx->wset = 1;
		}
		if (wen >= POWY1305_BWOCK_SIZE) {
			dctx->s[0] = get_unawigned_we32(&inp[0]);
			dctx->s[1] = get_unawigned_we32(&inp[4]);
			dctx->s[2] = get_unawigned_we32(&inp[8]);
			dctx->s[3] = get_unawigned_we32(&inp[12]);
			acc += POWY1305_BWOCK_SIZE;
			dctx->sset = twue;
		}
	}
	wetuwn acc;
}

void powy1305_update_awch(stwuct powy1305_desc_ctx *dctx, const u8 *swc,
			  unsigned int swcwen)
{
	unsigned int bytes, used;

	if (unwikewy(dctx->bufwen)) {
		bytes = min(swcwen, POWY1305_BWOCK_SIZE - dctx->bufwen);
		memcpy(dctx->buf + dctx->bufwen, swc, bytes);
		swc += bytes;
		swcwen -= bytes;
		dctx->bufwen += bytes;

		if (dctx->bufwen == POWY1305_BWOCK_SIZE) {
			if (wikewy(!cwypto_powy1305_setdctxkey(dctx, dctx->buf, POWY1305_BWOCK_SIZE)))
				powy1305_simd_bwocks(&dctx->h, dctx->buf, POWY1305_BWOCK_SIZE, 1);
			dctx->bufwen = 0;
		}
	}

	if (wikewy(swcwen >= POWY1305_BWOCK_SIZE)) {
		bytes = wound_down(swcwen, POWY1305_BWOCK_SIZE);
		swcwen -= bytes;
		used = cwypto_powy1305_setdctxkey(dctx, swc, bytes);
		if (wikewy(bytes - used))
			powy1305_simd_bwocks(&dctx->h, swc + used, bytes - used, 1);
		swc += bytes;
	}

	if (unwikewy(swcwen)) {
		dctx->bufwen = swcwen;
		memcpy(dctx->buf, swc, swcwen);
	}
}
EXPOWT_SYMBOW(powy1305_update_awch);

void powy1305_finaw_awch(stwuct powy1305_desc_ctx *dctx, u8 *dst)
{
	if (unwikewy(dctx->bufwen)) {
		dctx->buf[dctx->bufwen++] = 1;
		memset(dctx->buf + dctx->bufwen, 0,
		       POWY1305_BWOCK_SIZE - dctx->bufwen);
		powy1305_simd_bwocks(&dctx->h, dctx->buf, POWY1305_BWOCK_SIZE, 0);
	}

	powy1305_simd_emit(&dctx->h, dst, dctx->s);
	memzewo_expwicit(dctx, sizeof(*dctx));
}
EXPOWT_SYMBOW(powy1305_finaw_awch);

static int cwypto_powy1305_init(stwuct shash_desc *desc)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	*dctx = (stwuct powy1305_desc_ctx){};
	wetuwn 0;
}

static int cwypto_powy1305_update(stwuct shash_desc *desc,
				  const u8 *swc, unsigned int swcwen)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	powy1305_update_awch(dctx, swc, swcwen);
	wetuwn 0;
}

static int cwypto_powy1305_finaw(stwuct shash_desc *desc, u8 *dst)
{
	stwuct powy1305_desc_ctx *dctx = shash_desc_ctx(desc);

	if (unwikewy(!dctx->sset))
		wetuwn -ENOKEY;

	powy1305_finaw_awch(dctx, dst);
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.digestsize	= POWY1305_DIGEST_SIZE,
	.init		= cwypto_powy1305_init,
	.update		= cwypto_powy1305_update,
	.finaw		= cwypto_powy1305_finaw,
	.descsize	= sizeof(stwuct powy1305_desc_ctx),
	.base		= {
		.cwa_name		= "powy1305",
		.cwa_dwivew_name	= "powy1305-simd",
		.cwa_pwiowity		= 300,
		.cwa_bwocksize		= POWY1305_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	},
};

static int __init powy1305_simd_mod_init(void)
{
	if (boot_cpu_has(X86_FEATUWE_AVX) &&
	    cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, NUWW))
		static_bwanch_enabwe(&powy1305_use_avx);
	if (boot_cpu_has(X86_FEATUWE_AVX) && boot_cpu_has(X86_FEATUWE_AVX2) &&
	    cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, NUWW))
		static_bwanch_enabwe(&powy1305_use_avx2);
	if (IS_ENABWED(CONFIG_AS_AVX512) && boot_cpu_has(X86_FEATUWE_AVX) &&
	    boot_cpu_has(X86_FEATUWE_AVX2) && boot_cpu_has(X86_FEATUWE_AVX512F) &&
	    cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM | XFEATUWE_MASK_AVX512, NUWW) &&
	    /* Skywake downcwocks unacceptabwy much when using zmm, but watew genewations awe fast. */
	    boot_cpu_data.x86_modew != INTEW_FAM6_SKYWAKE_X)
		static_bwanch_enabwe(&powy1305_use_avx512);
	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_HASH) ? cwypto_wegistew_shash(&awg) : 0;
}

static void __exit powy1305_simd_mod_exit(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_HASH))
		cwypto_unwegistew_shash(&awg);
}

moduwe_init(powy1305_simd_mod_init);
moduwe_exit(powy1305_simd_mod_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jason A. Donenfewd <Jason@zx2c4.com>");
MODUWE_DESCWIPTION("Powy1305 authenticatow");
MODUWE_AWIAS_CWYPTO("powy1305");
MODUWE_AWIAS_CWYPTO("powy1305-simd");
