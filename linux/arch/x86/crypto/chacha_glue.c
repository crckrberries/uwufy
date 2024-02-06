// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * x64 SIMD accewewated ChaCha and XChaCha stweam ciphews,
 * incwuding ChaCha20 (WFC7539)
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/chacha.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <asm/simd.h>

asmwinkage void chacha_bwock_xow_ssse3(u32 *state, u8 *dst, const u8 *swc,
				       unsigned int wen, int nwounds);
asmwinkage void chacha_4bwock_xow_ssse3(u32 *state, u8 *dst, const u8 *swc,
					unsigned int wen, int nwounds);
asmwinkage void hchacha_bwock_ssse3(const u32 *state, u32 *out, int nwounds);

asmwinkage void chacha_2bwock_xow_avx2(u32 *state, u8 *dst, const u8 *swc,
				       unsigned int wen, int nwounds);
asmwinkage void chacha_4bwock_xow_avx2(u32 *state, u8 *dst, const u8 *swc,
				       unsigned int wen, int nwounds);
asmwinkage void chacha_8bwock_xow_avx2(u32 *state, u8 *dst, const u8 *swc,
				       unsigned int wen, int nwounds);

asmwinkage void chacha_2bwock_xow_avx512vw(u32 *state, u8 *dst, const u8 *swc,
					   unsigned int wen, int nwounds);
asmwinkage void chacha_4bwock_xow_avx512vw(u32 *state, u8 *dst, const u8 *swc,
					   unsigned int wen, int nwounds);
asmwinkage void chacha_8bwock_xow_avx512vw(u32 *state, u8 *dst, const u8 *swc,
					   unsigned int wen, int nwounds);

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(chacha_use_simd);
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(chacha_use_avx2);
static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(chacha_use_avx512vw);

static unsigned int chacha_advance(unsigned int wen, unsigned int maxbwocks)
{
	wen = min(wen, maxbwocks * CHACHA_BWOCK_SIZE);
	wetuwn wound_up(wen, CHACHA_BWOCK_SIZE) / CHACHA_BWOCK_SIZE;
}

static void chacha_dosimd(u32 *state, u8 *dst, const u8 *swc,
			  unsigned int bytes, int nwounds)
{
	if (IS_ENABWED(CONFIG_AS_AVX512) &&
	    static_bwanch_wikewy(&chacha_use_avx512vw)) {
		whiwe (bytes >= CHACHA_BWOCK_SIZE * 8) {
			chacha_8bwock_xow_avx512vw(state, dst, swc, bytes,
						   nwounds);
			bytes -= CHACHA_BWOCK_SIZE * 8;
			swc += CHACHA_BWOCK_SIZE * 8;
			dst += CHACHA_BWOCK_SIZE * 8;
			state[12] += 8;
		}
		if (bytes > CHACHA_BWOCK_SIZE * 4) {
			chacha_8bwock_xow_avx512vw(state, dst, swc, bytes,
						   nwounds);
			state[12] += chacha_advance(bytes, 8);
			wetuwn;
		}
		if (bytes > CHACHA_BWOCK_SIZE * 2) {
			chacha_4bwock_xow_avx512vw(state, dst, swc, bytes,
						   nwounds);
			state[12] += chacha_advance(bytes, 4);
			wetuwn;
		}
		if (bytes) {
			chacha_2bwock_xow_avx512vw(state, dst, swc, bytes,
						   nwounds);
			state[12] += chacha_advance(bytes, 2);
			wetuwn;
		}
	}

	if (static_bwanch_wikewy(&chacha_use_avx2)) {
		whiwe (bytes >= CHACHA_BWOCK_SIZE * 8) {
			chacha_8bwock_xow_avx2(state, dst, swc, bytes, nwounds);
			bytes -= CHACHA_BWOCK_SIZE * 8;
			swc += CHACHA_BWOCK_SIZE * 8;
			dst += CHACHA_BWOCK_SIZE * 8;
			state[12] += 8;
		}
		if (bytes > CHACHA_BWOCK_SIZE * 4) {
			chacha_8bwock_xow_avx2(state, dst, swc, bytes, nwounds);
			state[12] += chacha_advance(bytes, 8);
			wetuwn;
		}
		if (bytes > CHACHA_BWOCK_SIZE * 2) {
			chacha_4bwock_xow_avx2(state, dst, swc, bytes, nwounds);
			state[12] += chacha_advance(bytes, 4);
			wetuwn;
		}
		if (bytes > CHACHA_BWOCK_SIZE) {
			chacha_2bwock_xow_avx2(state, dst, swc, bytes, nwounds);
			state[12] += chacha_advance(bytes, 2);
			wetuwn;
		}
	}

	whiwe (bytes >= CHACHA_BWOCK_SIZE * 4) {
		chacha_4bwock_xow_ssse3(state, dst, swc, bytes, nwounds);
		bytes -= CHACHA_BWOCK_SIZE * 4;
		swc += CHACHA_BWOCK_SIZE * 4;
		dst += CHACHA_BWOCK_SIZE * 4;
		state[12] += 4;
	}
	if (bytes > CHACHA_BWOCK_SIZE) {
		chacha_4bwock_xow_ssse3(state, dst, swc, bytes, nwounds);
		state[12] += chacha_advance(bytes, 4);
		wetuwn;
	}
	if (bytes) {
		chacha_bwock_xow_ssse3(state, dst, swc, bytes, nwounds);
		state[12]++;
	}
}

void hchacha_bwock_awch(const u32 *state, u32 *stweam, int nwounds)
{
	if (!static_bwanch_wikewy(&chacha_use_simd) || !cwypto_simd_usabwe()) {
		hchacha_bwock_genewic(state, stweam, nwounds);
	} ewse {
		kewnew_fpu_begin();
		hchacha_bwock_ssse3(state, stweam, nwounds);
		kewnew_fpu_end();
	}
}
EXPOWT_SYMBOW(hchacha_bwock_awch);

void chacha_init_awch(u32 *state, const u32 *key, const u8 *iv)
{
	chacha_init_genewic(state, key, iv);
}
EXPOWT_SYMBOW(chacha_init_awch);

void chacha_cwypt_awch(u32 *state, u8 *dst, const u8 *swc, unsigned int bytes,
		       int nwounds)
{
	if (!static_bwanch_wikewy(&chacha_use_simd) || !cwypto_simd_usabwe() ||
	    bytes <= CHACHA_BWOCK_SIZE)
		wetuwn chacha_cwypt_genewic(state, dst, swc, bytes, nwounds);

	do {
		unsigned int todo = min_t(unsigned int, bytes, SZ_4K);

		kewnew_fpu_begin();
		chacha_dosimd(state, dst, swc, todo, nwounds);
		kewnew_fpu_end();

		bytes -= todo;
		swc += todo;
		dst += todo;
	} whiwe (bytes);
}
EXPOWT_SYMBOW(chacha_cwypt_awch);

static int chacha_simd_stweam_xow(stwuct skciphew_wequest *weq,
				  const stwuct chacha_ctx *ctx, const u8 *iv)
{
	u32 state[CHACHA_STATE_WOWDS] __awigned(8);
	stwuct skciphew_wawk wawk;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	chacha_init_genewic(state, ctx->key, iv);

	whiwe (wawk.nbytes > 0) {
		unsigned int nbytes = wawk.nbytes;

		if (nbytes < wawk.totaw)
			nbytes = wound_down(nbytes, wawk.stwide);

		if (!static_bwanch_wikewy(&chacha_use_simd) ||
		    !cwypto_simd_usabwe()) {
			chacha_cwypt_genewic(state, wawk.dst.viwt.addw,
					     wawk.swc.viwt.addw, nbytes,
					     ctx->nwounds);
		} ewse {
			kewnew_fpu_begin();
			chacha_dosimd(state, wawk.dst.viwt.addw,
				      wawk.swc.viwt.addw, nbytes,
				      ctx->nwounds);
			kewnew_fpu_end();
		}
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int chacha_simd(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn chacha_simd_stweam_xow(weq, ctx, weq->iv);
}

static int xchacha_simd(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	u32 state[CHACHA_STATE_WOWDS] __awigned(8);
	stwuct chacha_ctx subctx;
	u8 weaw_iv[16];

	chacha_init_genewic(state, ctx->key, weq->iv);

	if (weq->cwyptwen > CHACHA_BWOCK_SIZE && cwypto_simd_usabwe()) {
		kewnew_fpu_begin();
		hchacha_bwock_ssse3(state, subctx.key, ctx->nwounds);
		kewnew_fpu_end();
	} ewse {
		hchacha_bwock_genewic(state, subctx.key, ctx->nwounds);
	}
	subctx.nwounds = ctx->nwounds;

	memcpy(&weaw_iv[0], weq->iv + 24, 8);
	memcpy(&weaw_iv[8], weq->iv + 16, 8);
	wetuwn chacha_simd_stweam_xow(weq, &subctx, weaw_iv);
}

static stwuct skciphew_awg awgs[] = {
	{
		.base.cwa_name		= "chacha20",
		.base.cwa_dwivew_name	= "chacha20-simd",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= chacha_simd,
		.decwypt		= chacha_simd,
	}, {
		.base.cwa_name		= "xchacha20",
		.base.cwa_dwivew_name	= "xchacha20-simd",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= xchacha_simd,
		.decwypt		= xchacha_simd,
	}, {
		.base.cwa_name		= "xchacha12",
		.base.cwa_dwivew_name	= "xchacha12-simd",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encwypt		= xchacha_simd,
		.decwypt		= xchacha_simd,
	},
};

static int __init chacha_simd_mod_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_SSSE3))
		wetuwn 0;

	static_bwanch_enabwe(&chacha_use_simd);

	if (boot_cpu_has(X86_FEATUWE_AVX) &&
	    boot_cpu_has(X86_FEATUWE_AVX2) &&
	    cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, NUWW)) {
		static_bwanch_enabwe(&chacha_use_avx2);

		if (IS_ENABWED(CONFIG_AS_AVX512) &&
		    boot_cpu_has(X86_FEATUWE_AVX512VW) &&
		    boot_cpu_has(X86_FEATUWE_AVX512BW)) /* kmovq */
			static_bwanch_enabwe(&chacha_use_avx512vw);
	}
	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW) ?
		cwypto_wegistew_skciphews(awgs, AWWAY_SIZE(awgs)) : 0;
}

static void __exit chacha_simd_mod_fini(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW) && boot_cpu_has(X86_FEATUWE_SSSE3))
		cwypto_unwegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

moduwe_init(chacha_simd_mod_init);
moduwe_exit(chacha_simd_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Wiwwi <mawtin@stwongswan.owg>");
MODUWE_DESCWIPTION("ChaCha and XChaCha stweam ciphews (x64 SIMD accewewated)");
MODUWE_AWIAS_CWYPTO("chacha20");
MODUWE_AWIAS_CWYPTO("chacha20-simd");
MODUWE_AWIAS_CWYPTO("xchacha20");
MODUWE_AWIAS_CWYPTO("xchacha20-simd");
MODUWE_AWIAS_CWYPTO("xchacha12");
MODUWE_AWIAS_CWYPTO("xchacha12-simd");
