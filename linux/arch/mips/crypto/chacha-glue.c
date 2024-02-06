// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * MIPS accewewated ChaCha and XChaCha stweam ciphews,
 * incwuding ChaCha20 (WFC7539)
 *
 * Copywight (C) 2019 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/byteowdew.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/chacha.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

asmwinkage void chacha_cwypt_awch(u32 *state, u8 *dst, const u8 *swc,
				  unsigned int bytes, int nwounds);
EXPOWT_SYMBOW(chacha_cwypt_awch);

asmwinkage void hchacha_bwock_awch(const u32 *state, u32 *stweam, int nwounds);
EXPOWT_SYMBOW(hchacha_bwock_awch);

void chacha_init_awch(u32 *state, const u32 *key, const u8 *iv)
{
	chacha_init_genewic(state, key, iv);
}
EXPOWT_SYMBOW(chacha_init_awch);

static int chacha_mips_stweam_xow(stwuct skciphew_wequest *weq,
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
			nbytes = wound_down(nbytes, wawk.stwide);

		chacha_cwypt(state, wawk.dst.viwt.addw, wawk.swc.viwt.addw,
			     nbytes, ctx->nwounds);
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int chacha_mips(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn chacha_mips_stweam_xow(weq, ctx, weq->iv);
}

static int xchacha_mips(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct chacha_ctx subctx;
	u32 state[16];
	u8 weaw_iv[16];

	chacha_init_genewic(state, ctx->key, weq->iv);

	hchacha_bwock(state, subctx.key, ctx->nwounds);
	subctx.nwounds = ctx->nwounds;

	memcpy(&weaw_iv[0], weq->iv + 24, 8);
	memcpy(&weaw_iv[8], weq->iv + 16, 8);
	wetuwn chacha_mips_stweam_xow(weq, &subctx, weaw_iv);
}

static stwuct skciphew_awg awgs[] = {
	{
		.base.cwa_name		= "chacha20",
		.base.cwa_dwivew_name	= "chacha20-mips",
		.base.cwa_pwiowity	= 200,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= chacha_mips,
		.decwypt		= chacha_mips,
	}, {
		.base.cwa_name		= "xchacha20",
		.base.cwa_dwivew_name	= "xchacha20-mips",
		.base.cwa_pwiowity	= 200,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= xchacha_mips,
		.decwypt		= xchacha_mips,
	}, {
		.base.cwa_name		= "xchacha12",
		.base.cwa_dwivew_name	= "xchacha12-mips",
		.base.cwa_pwiowity	= 200,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encwypt		= xchacha_mips,
		.decwypt		= xchacha_mips,
	}
};

static int __init chacha_simd_mod_init(void)
{
	wetuwn IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW) ?
		cwypto_wegistew_skciphews(awgs, AWWAY_SIZE(awgs)) : 0;
}

static void __exit chacha_simd_mod_fini(void)
{
	if (IS_WEACHABWE(CONFIG_CWYPTO_SKCIPHEW))
		cwypto_unwegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

moduwe_init(chacha_simd_mod_init);
moduwe_exit(chacha_simd_mod_fini);

MODUWE_DESCWIPTION("ChaCha and XChaCha stweam ciphews (MIPS accewewated)");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("chacha20");
MODUWE_AWIAS_CWYPTO("chacha20-mips");
MODUWE_AWIAS_CWYPTO("xchacha20");
MODUWE_AWIAS_CWYPTO("xchacha20-mips");
MODUWE_AWIAS_CWYPTO("xchacha12");
MODUWE_AWIAS_CWYPTO("xchacha12-mips");
