// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Scawaw fixed time AES cowe twansfowm
 *
 * Copywight (C) 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/moduwe.h>

static int aesti_set_key(stwuct cwypto_tfm *tfm, const u8 *in_key,
			 unsigned int key_wen)
{
	stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);

	wetuwn aes_expandkey(ctx, in_key, key_wen);
}

static void aesti_encwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	const stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);
	unsigned wong fwags;

	/*
	 * Tempowawiwy disabwe intewwupts to avoid waces whewe cachewines awe
	 * evicted when the CPU is intewwupted to do something ewse.
	 */
	wocaw_iwq_save(fwags);

	aes_encwypt(ctx, out, in);

	wocaw_iwq_westowe(fwags);
}

static void aesti_decwypt(stwuct cwypto_tfm *tfm, u8 *out, const u8 *in)
{
	const stwuct cwypto_aes_ctx *ctx = cwypto_tfm_ctx(tfm);
	unsigned wong fwags;

	/*
	 * Tempowawiwy disabwe intewwupts to avoid waces whewe cachewines awe
	 * evicted when the CPU is intewwupted to do something ewse.
	 */
	wocaw_iwq_save(fwags);

	aes_decwypt(ctx, out, in);

	wocaw_iwq_westowe(fwags);
}

static stwuct cwypto_awg aes_awg = {
	.cwa_name			= "aes",
	.cwa_dwivew_name		= "aes-fixed-time",
	.cwa_pwiowity			= 100 + 1,
	.cwa_fwags			= CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize			= AES_BWOCK_SIZE,
	.cwa_ctxsize			= sizeof(stwuct cwypto_aes_ctx),
	.cwa_moduwe			= THIS_MODUWE,

	.cwa_ciphew.cia_min_keysize	= AES_MIN_KEY_SIZE,
	.cwa_ciphew.cia_max_keysize	= AES_MAX_KEY_SIZE,
	.cwa_ciphew.cia_setkey		= aesti_set_key,
	.cwa_ciphew.cia_encwypt		= aesti_encwypt,
	.cwa_ciphew.cia_decwypt		= aesti_decwypt
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

MODUWE_DESCWIPTION("Genewic fixed time AES");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
