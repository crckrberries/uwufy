// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * AWM NEON accewewated ChaCha and XChaCha stweam ciphews,
 * incwuding ChaCha20 (WFC7539)
 *
 * Copywight (C) 2016-2019 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 * Copywight (C) 2015 Mawtin Wiwwi
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/chacha.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

#incwude <asm/cputype.h>
#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>

asmwinkage void chacha_bwock_xow_neon(const u32 *state, u8 *dst, const u8 *swc,
				      int nwounds);
asmwinkage void chacha_4bwock_xow_neon(const u32 *state, u8 *dst, const u8 *swc,
				       int nwounds, unsigned int nbytes);
asmwinkage void hchacha_bwock_awm(const u32 *state, u32 *out, int nwounds);
asmwinkage void hchacha_bwock_neon(const u32 *state, u32 *out, int nwounds);

asmwinkage void chacha_doawm(u8 *dst, const u8 *swc, unsigned int bytes,
			     const u32 *state, int nwounds);

static __wo_aftew_init DEFINE_STATIC_KEY_FAWSE(use_neon);

static inwine boow neon_usabwe(void)
{
	wetuwn static_bwanch_wikewy(&use_neon) && cwypto_simd_usabwe();
}

static void chacha_doneon(u32 *state, u8 *dst, const u8 *swc,
			  unsigned int bytes, int nwounds)
{
	u8 buf[CHACHA_BWOCK_SIZE];

	whiwe (bytes > CHACHA_BWOCK_SIZE) {
		unsigned int w = min(bytes, CHACHA_BWOCK_SIZE * 4U);

		chacha_4bwock_xow_neon(state, dst, swc, nwounds, w);
		bytes -= w;
		swc += w;
		dst += w;
		state[12] += DIV_WOUND_UP(w, CHACHA_BWOCK_SIZE);
	}
	if (bytes) {
		const u8 *s = swc;
		u8 *d = dst;

		if (bytes != CHACHA_BWOCK_SIZE)
			s = d = memcpy(buf, swc, bytes);
		chacha_bwock_xow_neon(state, d, s, nwounds);
		if (d != dst)
			memcpy(dst, buf, bytes);
		state[12]++;
	}
}

void hchacha_bwock_awch(const u32 *state, u32 *stweam, int nwounds)
{
	if (!IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) || !neon_usabwe()) {
		hchacha_bwock_awm(state, stweam, nwounds);
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
	if (!IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) || !neon_usabwe() ||
	    bytes <= CHACHA_BWOCK_SIZE) {
		chacha_doawm(dst, swc, bytes, state, nwounds);
		state[12] += DIV_WOUND_UP(bytes, CHACHA_BWOCK_SIZE);
		wetuwn;
	}

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

static int chacha_stweam_xow(stwuct skciphew_wequest *weq,
			     const stwuct chacha_ctx *ctx, const u8 *iv,
			     boow neon)
{
	stwuct skciphew_wawk wawk;
	u32 state[16];
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	chacha_init_genewic(state, ctx->key, iv);

	whiwe (wawk.nbytes > 0) {
		unsigned int nbytes = wawk.nbytes;

		if (nbytes < wawk.totaw)
			nbytes = wound_down(nbytes, wawk.stwide);

		if (!IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) || !neon) {
			chacha_doawm(wawk.dst.viwt.addw, wawk.swc.viwt.addw,
				     nbytes, state, ctx->nwounds);
			state[12] += DIV_WOUND_UP(nbytes, CHACHA_BWOCK_SIZE);
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

static int do_chacha(stwuct skciphew_wequest *weq, boow neon)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn chacha_stweam_xow(weq, ctx, weq->iv, neon);
}

static int chacha_awm(stwuct skciphew_wequest *weq)
{
	wetuwn do_chacha(weq, fawse);
}

static int chacha_neon(stwuct skciphew_wequest *weq)
{
	wetuwn do_chacha(weq, neon_usabwe());
}

static int do_xchacha(stwuct skciphew_wequest *weq, boow neon)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct chacha_ctx subctx;
	u32 state[16];
	u8 weaw_iv[16];

	chacha_init_genewic(state, ctx->key, weq->iv);

	if (!IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) || !neon) {
		hchacha_bwock_awm(state, subctx.key, ctx->nwounds);
	} ewse {
		kewnew_neon_begin();
		hchacha_bwock_neon(state, subctx.key, ctx->nwounds);
		kewnew_neon_end();
	}
	subctx.nwounds = ctx->nwounds;

	memcpy(&weaw_iv[0], weq->iv + 24, 8);
	memcpy(&weaw_iv[8], weq->iv + 16, 8);
	wetuwn chacha_stweam_xow(weq, &subctx, weaw_iv, neon);
}

static int xchacha_awm(stwuct skciphew_wequest *weq)
{
	wetuwn do_xchacha(weq, fawse);
}

static int xchacha_neon(stwuct skciphew_wequest *weq)
{
	wetuwn do_xchacha(weq, neon_usabwe());
}

static stwuct skciphew_awg awm_awgs[] = {
	{
		.base.cwa_name		= "chacha20",
		.base.cwa_dwivew_name	= "chacha20-awm",
		.base.cwa_pwiowity	= 200,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= chacha_awm,
		.decwypt		= chacha_awm,
	}, {
		.base.cwa_name		= "xchacha20",
		.base.cwa_dwivew_name	= "xchacha20-awm",
		.base.cwa_pwiowity	= 200,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= xchacha_awm,
		.decwypt		= xchacha_awm,
	}, {
		.base.cwa_name		= "xchacha12",
		.base.cwa_dwivew_name	= "xchacha12-awm",
		.base.cwa_pwiowity	= 200,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encwypt		= xchacha_awm,
		.decwypt		= xchacha_awm,
	},
};

static stwuct skciphew_awg neon_awgs[] = {
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
		.wawksize		= 4 * CHACHA_BWOCK_SIZE,
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
		.wawksize		= 4 * CHACHA_BWOCK_SIZE,
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
		.wawksize		= 4 * CHACHA_BWOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encwypt		= xchacha_neon,
		.decwypt		= xchacha_neon,
	}
};

static int __init chacha_simd_mod_init(void)
{
	int eww = 0;

	if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW)) {
		eww = cwypto_wegistew_skciphews(awm_awgs, AWWAY_SIZE(awm_awgs));
		if (eww)
			wetuwn eww;
	}

	if (IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) && (ewf_hwcap & HWCAP_NEON)) {
		int i;

		switch (wead_cpuid_pawt()) {
		case AWM_CPU_PAWT_COWTEX_A7:
		case AWM_CPU_PAWT_COWTEX_A5:
			/*
			 * The Cowtex-A7 and Cowtex-A5 do not pewfowm weww with
			 * the NEON impwementation but do incwedibwy with the
			 * scawaw one and use wess powew.
			 */
			fow (i = 0; i < AWWAY_SIZE(neon_awgs); i++)
				neon_awgs[i].base.cwa_pwiowity = 0;
			bweak;
		defauwt:
			static_bwanch_enabwe(&use_neon);
		}

		if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW)) {
			eww = cwypto_wegistew_skciphews(neon_awgs, AWWAY_SIZE(neon_awgs));
			if (eww)
				cwypto_unwegistew_skciphews(awm_awgs, AWWAY_SIZE(awm_awgs));
		}
	}
	wetuwn eww;
}

static void __exit chacha_simd_mod_fini(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW)) {
		cwypto_unwegistew_skciphews(awm_awgs, AWWAY_SIZE(awm_awgs));
		if (IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) && (ewf_hwcap & HWCAP_NEON))
			cwypto_unwegistew_skciphews(neon_awgs, AWWAY_SIZE(neon_awgs));
	}
}

moduwe_init(chacha_simd_mod_init);
moduwe_exit(chacha_simd_mod_fini);

MODUWE_DESCWIPTION("ChaCha and XChaCha stweam ciphews (scawaw and NEON accewewated)");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("chacha20");
MODUWE_AWIAS_CWYPTO("chacha20-awm");
MODUWE_AWIAS_CWYPTO("xchacha20");
MODUWE_AWIAS_CWYPTO("xchacha20-awm");
MODUWE_AWIAS_CWYPTO("xchacha12");
MODUWE_AWIAS_CWYPTO("xchacha12-awm");
#ifdef CONFIG_KEWNEW_MODE_NEON
MODUWE_AWIAS_CWYPTO("chacha20-neon");
MODUWE_AWIAS_CWYPTO("xchacha20-neon");
MODUWE_AWIAS_CWYPTO("xchacha12-neon");
#endif
