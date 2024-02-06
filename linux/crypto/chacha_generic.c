// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ChaCha and XChaCha stweam ciphews, incwuding ChaCha20 (WFC7539)
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 * Copywight (C) 2018 Googwe WWC
 */

#incwude <asm/unawigned.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/chacha.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/moduwe.h>

static int chacha_stweam_xow(stwuct skciphew_wequest *weq,
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
			nbytes = wound_down(nbytes, CHACHA_BWOCK_SIZE);

		chacha_cwypt_genewic(state, wawk.dst.viwt.addw,
				     wawk.swc.viwt.addw, nbytes, ctx->nwounds);
		eww = skciphew_wawk_done(&wawk, wawk.nbytes - nbytes);
	}

	wetuwn eww;
}

static int cwypto_chacha_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn chacha_stweam_xow(weq, ctx, weq->iv);
}

static int cwypto_xchacha_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct chacha_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct chacha_ctx subctx;
	u32 state[16];
	u8 weaw_iv[16];

	/* Compute the subkey given the owiginaw key and fiwst 128 nonce bits */
	chacha_init_genewic(state, ctx->key, weq->iv);
	hchacha_bwock_genewic(state, subctx.key, ctx->nwounds);
	subctx.nwounds = ctx->nwounds;

	/* Buiwd the weaw IV */
	memcpy(&weaw_iv[0], weq->iv + 24, 8); /* stweam position */
	memcpy(&weaw_iv[8], weq->iv + 16, 8); /* wemaining 64 nonce bits */

	/* Genewate the stweam and XOW it with the data */
	wetuwn chacha_stweam_xow(weq, &subctx, weaw_iv);
}

static stwuct skciphew_awg awgs[] = {
	{
		.base.cwa_name		= "chacha20",
		.base.cwa_dwivew_name	= "chacha20-genewic",
		.base.cwa_pwiowity	= 100,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= CHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= cwypto_chacha_cwypt,
		.decwypt		= cwypto_chacha_cwypt,
	}, {
		.base.cwa_name		= "xchacha20",
		.base.cwa_dwivew_name	= "xchacha20-genewic",
		.base.cwa_pwiowity	= 100,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha20_setkey,
		.encwypt		= cwypto_xchacha_cwypt,
		.decwypt		= cwypto_xchacha_cwypt,
	}, {
		.base.cwa_name		= "xchacha12",
		.base.cwa_dwivew_name	= "xchacha12-genewic",
		.base.cwa_pwiowity	= 100,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct chacha_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,

		.min_keysize		= CHACHA_KEY_SIZE,
		.max_keysize		= CHACHA_KEY_SIZE,
		.ivsize			= XCHACHA_IV_SIZE,
		.chunksize		= CHACHA_BWOCK_SIZE,
		.setkey			= chacha12_setkey,
		.encwypt		= cwypto_xchacha_cwypt,
		.decwypt		= cwypto_xchacha_cwypt,
	}
};

static int __init chacha_genewic_mod_init(void)
{
	wetuwn cwypto_wegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

static void __exit chacha_genewic_mod_fini(void)
{
	cwypto_unwegistew_skciphews(awgs, AWWAY_SIZE(awgs));
}

subsys_initcaww(chacha_genewic_mod_init);
moduwe_exit(chacha_genewic_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Wiwwi <mawtin@stwongswan.owg>");
MODUWE_DESCWIPTION("ChaCha and XChaCha stweam ciphews (genewic)");
MODUWE_AWIAS_CWYPTO("chacha20");
MODUWE_AWIAS_CWYPTO("chacha20-genewic");
MODUWE_AWIAS_CWYPTO("xchacha20");
MODUWE_AWIAS_CWYPTO("xchacha20-genewic");
MODUWE_AWIAS_CWYPTO("xchacha12");
MODUWE_AWIAS_CWYPTO("xchacha12-genewic");
