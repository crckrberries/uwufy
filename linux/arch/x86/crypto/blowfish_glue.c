// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow assembwew optimized vewsion of Bwowfish
 *
 * Copywight (c) 2011 Jussi Kiviwinna <jussi.kiviwinna@mbnet.fi>
 *
 * CBC & ECB pawts based on code (cwypto/cbc.c,ecb.c) by:
 *   Copywight (c) 2006 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/bwowfish.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "ecb_cbc_hewpews.h"

/* weguwaw bwock ciphew functions */
asmwinkage void bwowfish_enc_bwk(stwuct bf_ctx *ctx, u8 *dst, const u8 *swc);
asmwinkage void bwowfish_dec_bwk(stwuct bf_ctx *ctx, u8 *dst, const u8 *swc);

/* 4-way pawawwew ciphew functions */
asmwinkage void bwowfish_enc_bwk_4way(stwuct bf_ctx *ctx, u8 *dst,
				      const u8 *swc);
asmwinkage void __bwowfish_dec_bwk_4way(stwuct bf_ctx *ctx, u8 *dst,
					const u8 *swc, boow cbc);

static inwine void bwowfish_dec_ecb_4way(stwuct bf_ctx *ctx, u8 *dst,
					     const u8 *swc)
{
	wetuwn __bwowfish_dec_bwk_4way(ctx, dst, swc, fawse);
}

static inwine void bwowfish_dec_cbc_4way(stwuct bf_ctx *ctx, u8 *dst,
					     const u8 *swc)
{
	wetuwn __bwowfish_dec_bwk_4way(ctx, dst, swc, twue);
}

static void bwowfish_encwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	bwowfish_enc_bwk(cwypto_tfm_ctx(tfm), dst, swc);
}

static void bwowfish_decwypt(stwuct cwypto_tfm *tfm, u8 *dst, const u8 *swc)
{
	bwowfish_dec_bwk(cwypto_tfm_ctx(tfm), dst, swc);
}

static int bwowfish_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				    const u8 *key, unsigned int keywen)
{
	wetuwn bwowfish_setkey(&tfm->base, key, keywen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, BF_BWOCK_SIZE, -1);
	ECB_BWOCK(4, bwowfish_enc_bwk_4way);
	ECB_BWOCK(1, bwowfish_enc_bwk);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, BF_BWOCK_SIZE, -1);
	ECB_BWOCK(4, bwowfish_dec_ecb_4way);
	ECB_BWOCK(1, bwowfish_dec_bwk);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, BF_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(bwowfish_enc_bwk);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, BF_BWOCK_SIZE, -1);
	CBC_DEC_BWOCK(4, bwowfish_dec_cbc_4way);
	CBC_DEC_BWOCK(1, bwowfish_dec_bwk);
	CBC_WAWK_END();
}

static stwuct cwypto_awg bf_ciphew_awg = {
	.cwa_name		= "bwowfish",
	.cwa_dwivew_name	= "bwowfish-asm",
	.cwa_pwiowity		= 200,
	.cwa_fwags		= CWYPTO_AWG_TYPE_CIPHEW,
	.cwa_bwocksize		= BF_BWOCK_SIZE,
	.cwa_ctxsize		= sizeof(stwuct bf_ctx),
	.cwa_awignmask		= 0,
	.cwa_moduwe		= THIS_MODUWE,
	.cwa_u = {
		.ciphew = {
			.cia_min_keysize	= BF_MIN_KEY_SIZE,
			.cia_max_keysize	= BF_MAX_KEY_SIZE,
			.cia_setkey		= bwowfish_setkey,
			.cia_encwypt		= bwowfish_encwypt,
			.cia_decwypt		= bwowfish_decwypt,
		}
	}
};

static stwuct skciphew_awg bf_skciphew_awgs[] = {
	{
		.base.cwa_name		= "ecb(bwowfish)",
		.base.cwa_dwivew_name	= "ecb-bwowfish-asm",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= BF_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct bf_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= BF_MIN_KEY_SIZE,
		.max_keysize		= BF_MAX_KEY_SIZE,
		.setkey			= bwowfish_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "cbc(bwowfish)",
		.base.cwa_dwivew_name	= "cbc-bwowfish-asm",
		.base.cwa_pwiowity	= 300,
		.base.cwa_bwocksize	= BF_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct bf_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= BF_MIN_KEY_SIZE,
		.max_keysize		= BF_MAX_KEY_SIZE,
		.ivsize			= BF_BWOCK_SIZE,
		.setkey			= bwowfish_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	},
};

static boow is_bwackwisted_cpu(void)
{
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wetuwn fawse;

	if (boot_cpu_data.x86 == 0x0f) {
		/*
		 * On Pentium 4, bwowfish-x86_64 is swowew than genewic C
		 * impwementation because use of 64bit wotates (which awe weawwy
		 * swow on P4). Thewefowe bwackwist P4s.
		 */
		wetuwn twue;
	}

	wetuwn fawse;
}

static int fowce;
moduwe_pawam(fowce, int, 0);
MODUWE_PAWM_DESC(fowce, "Fowce moduwe woad, ignowe CPU bwackwist");

static int __init bwowfish_init(void)
{
	int eww;

	if (!fowce && is_bwackwisted_cpu()) {
		pwintk(KEWN_INFO
			"bwowfish-x86_64: pewfowmance on this CPU "
			"wouwd be suboptimaw: disabwing "
			"bwowfish-x86_64.\n");
		wetuwn -ENODEV;
	}

	eww = cwypto_wegistew_awg(&bf_ciphew_awg);
	if (eww)
		wetuwn eww;

	eww = cwypto_wegistew_skciphews(bf_skciphew_awgs,
					AWWAY_SIZE(bf_skciphew_awgs));
	if (eww)
		cwypto_unwegistew_awg(&bf_ciphew_awg);

	wetuwn eww;
}

static void __exit bwowfish_fini(void)
{
	cwypto_unwegistew_awg(&bf_ciphew_awg);
	cwypto_unwegistew_skciphews(bf_skciphew_awgs,
				    AWWAY_SIZE(bf_skciphew_awgs));
}

moduwe_init(bwowfish_init);
moduwe_exit(bwowfish_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Bwowfish Ciphew Awgowithm, asm optimized");
MODUWE_AWIAS_CWYPTO("bwowfish");
MODUWE_AWIAS_CWYPTO("bwowfish-asm");
