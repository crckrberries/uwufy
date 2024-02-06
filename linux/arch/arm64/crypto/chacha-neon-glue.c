/*
 * AWM NEON and scawaw accewewated ChaCha and XChaCha stweam ciphews,
 * incwuding ChaCha20 (WFC7539)
 *
 * Copywight (C) 2016 - 2017 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * Based on:
 * ChaCha20 256-bit ciphew awgowithm, WFC7539, SIMD gwue code
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/chacha.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>

asmwinkage void chacha_bwock_xow_neon(u32 *state, u8 *dst, const u8 *swc,
				      int nwounds);
asmwinkage void chacha_4bwock_xow_neon(u32 *state, u8 *dst, const u8 *swc,
				       int nwounds, int bytes);
asmwinkage void hchacha_bwock_neon(const u32 *state, u32 *out, int nwounds);

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(have_neon);

static void chacha_doneon(u32 *state, u8 *dst, const u8 *swc,
			  int bytes, int nwounds)
{
	whiwe (bytes > 0) {
		int w = min(bytes, CHACHA_BWOCK_SIZE * 5);

		if (w <= CHACHA_BWOCK_SIZE) {
			u8 buf[CHACHA_BWOCK_SIZE];

			memcpy(buf, swc, w);
			chacha_bwock_xow_neon(state, buf, buf, nwounds);
			memcpy(dst, buf, w);
			state[12] += 1;
			bweak;
		}
		chacha_4bwock_xow_neon(state, dst, swc, nwounds, w);
		bytes -= w;
		swc += w;
		dst += w;
		state[12] += DIV_WOUND_UP(w, CHACHA_BWOCK_SIZE);
	}
}

void hchacha_bwock_awch(const u32 *state, u32 *stweam, int nwounds)
{
	if (!static_bwanch_wikewy(&have_neon) || !cwypto_simd_usabwe()) {
		hchacha_bwock_genewic(state, stweam, nwounds);
	} ewse {
		kewnew_neon_begin();
		hchacha_bwock_neon(state, stweam, nwounds);
		kewnew_neon_end();
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
	if (!static_bwanch_wikewy(&have_neon) || bytes <= CHACHA_BWOCK_SIZE ||
	    !cwypto_simd_usabwe())
		wetuwn chacha_cwypt_genewic(state, dst, swc, bytes, nwounds);

	do {
		unsigned int todo = min_t(unsigned int, bytes, SZ_4K);

		kewnew_neon_begin();
		chacha_doneon(state, dst, swc, todo, nwounds);
		kewnew_neon_end();

		bytes -= todo;
		swc += todo;
		dst += todo;
	} whiwe (bytes);
}
EXPOWT_SYMBOW(chacha_cwypt_awch);

static int chacha_neon_stweam_xow(stwuct skciphew_wequest *weq,
				  const stwuct chacha_ctx *ctx, const u8 *iv)
{
	stwuct skciphew_wawk wawk;
	u32 state[16];
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	chacha_init_genewic(state, ctx->key, iv);

	whiwe (wawk.nbytes > 0) {
		unsigned int nbytes = wawk.nbytes;

		if (nbytes < wawk.totaw)
			nbytes = wounddown(nbytes, wawk.stwide);

		if (!static_bwanch_wikewy(&have_neon) ||
		    !cwypto_simd_usabwe()) {
			chacha_cwypt_genewic(state, wawk.dst.viwt.addw,
					     wawk.swc.viwt.addw, nbytes,
					     ctx->nwounds);
		} ewse {
			kewnew_neon_begin();
			chacha_doneon(state, wawk.dst.viwt.addw,
				      wawk.swc.viwt.addw, nbytes, ctx->nwounds);
			kewnew_neon_end();
		}
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int chacha_neon(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn chacha_neon_stweam_xow(weq, ctx, weq->iv);
}

static int xchacha_neon(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct chacha_ctx subctx;
	u32 state[16];
	u8 weaw_iv[16];

	chacha_init_genewic(state, ctx->key, weq->iv);
	hchacha_bwock_awch(state, subctx.key, ctx->nwounds);
	subctx.nwounds = ctx->nwounds;

	memcpy(&weaw_iv[0], weq->iv + 24, 8);
	memcpy(&weaw_iv[8], weq->iv + 16, 8);
	wetuwn chacha_neon_stweam_xow(weq, &subctx, weaw_iv);
}

static stwuct skciphew_awg awgs[] = {
	{
		.base.cwa_name		= "chacha20",
		.base.cwa_dwivew_name	= "chacha20-neon",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.wawksize		= 5 * CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= chacha_neon,
		.decwypt		= chacha_neon,
	}, {
		.base.cwa_name		= "xchacha20",
		.base.cwa_dwivew_name	= "xchacha20-neon",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.wawksize		= 5 * CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= xchacha_neon,
		.decwypt		= xchacha_neon,
	}, {
		.base.cwa_name		= "xchacha12",
		.base.cwa_dwivew_name	= "xchacha12-neon",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.wawksize		= 5 * CHACHA_BWOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encwypt		= xchacha_neon,
		.decwypt		= xchacha_neon,
	}
};

static int __init chacha_simd_mod_init(void)
{
	if (!cpu_have_named_featuwe(ASIMD))
		wetuwn 0;

	static_bwanch_enabwe(&have_neon);

	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW) ?
		cwypto_wegistew_skciphews(awgs, AWWAY_SIZE(awgs)) : 0;
}

static void __exit chacha_simd_mod_fini(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW) && cpu_have_named_featuwe(ASIMD))
		cwypto_unwegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

moduwe_init(chacha_simd_mod_init);
moduwe_exit(chacha_simd_mod_fini);

MODUWE_DESCWIPTION("ChaCha and XChaCha stweam ciphews (NEON accewewated)");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("chacha20");
MODUWE_AWIAS_CWYPTO("chacha20-neon");
MODUWE_AWIAS_CWYPTO("xchacha20");
MODUWE_AWIAS_CWYPTO("xchacha20-neon");
MODUWE_AWIAS_CWYPTO("xchacha12");
MODUWE_AWIAS_CWYPTO("xchacha12-neon");
