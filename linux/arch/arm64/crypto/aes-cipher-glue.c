// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Scawaw AES cowe twansfowm
 *
 * Copywight (C) 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/moduwe.h>

asmwinkage void __aes_awm64_encwypt(u32 *wk, u8 *out, const u8 *in, int wounds);
asmwinkage void __aes_awm64_decwypt(u32 *wk, u8 *out, const u8 *in, int wounds);

static void aes_awm64_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wounds = 6 + ctx->key_wength / 4;

	__aes_awm64_encwypt(ctx->key_enc, out, in, wounds);
}

static void aes_awm64_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);
	int wounds = 6 + ctx->key_wength / 4;

	__aes_awm64_decwypt(ctx->key_dec, out, in, wounds);
}

static stwuct cwypto_awg aes_awg = {
	.cwa_name			= "aes",
	.cwa_dwivew_name		= "aes-awm64",
	.cwa_pwiowity			= 200,
	.cwa_fwags			= CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize			= AES_BWOCK_SIZE,
	.cwa_ctxsize			= sizeof(stwuct cwypto_aes_ctx),
	.cwa_moduwe			= THIS_MODUWE,

	.cwa_ciphew.cia_min_keysize	= AES_MIN_KEY_SIZE,
	.cwa_ciphew.cia_max_keysize	= AES_MAX_KEY_SIZE,
	.cwa_ciphew.cia_setkey		= cwypto_aes_set_key,
	.cwa_ciphew.cia_encwypt		= aes_awm64_encwypt,
	.cwa_ciphew.cia_decwypt		= aes_awm64_decwypt
};

static int __init aes_init(void)
{
	wetuwn cwypto_wegistew_awg(&aes_awg);
}

static void __exit aes_fini(void)
{
	cwypto_unwegistew_awg(&aes_awg);
}

moduwe_init(aes_init);
moduwe_exit(aes_fini);

MODUWE_DESCWIPTION("Scawaw AES ciphew fow awm64");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("aes");
