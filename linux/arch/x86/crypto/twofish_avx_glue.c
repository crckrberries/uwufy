// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow AVX assembwew vewsion of Twofish Ciphew
 *
 * Copywight (C) 2012 Johannes Goetzfwied
 *     <Johannes.Goetzfwied@infowmatik.stud.uni-ewwangen.de>
 *
 * Copywight © 2013 Jussi Kiviwinna <jussi.kiviwinna@iki.fi>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/twofish.h>

#incwude "twofish.h"
#incwude "ecb_cbc_hewpews.h"

#define TWOFISH_PAWAWWEW_BWOCKS 8

/* 8-way pawawwew ciphew functions */
asmwinkage void twofish_ecb_enc_8way(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void twofish_ecb_dec_8way(const void *ctx, u8 *dst, const u8 *swc);

asmwinkage void twofish_cbc_dec_8way(const void *ctx, u8 *dst, const u8 *swc);

static int twofish_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				   const u8 *key, unsigned int keywen)
{
	wetuwn twofish_setkey(&tfm->base, key, keywen);
}

static inwine void twofish_enc_bwk_3way(const void *ctx, u8 *dst, const u8 *swc)
{
	__twofish_enc_bwk_3way(ctx, dst, swc, fawse);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, TF_BWOCK_SIZE, TWOFISH_PAWAWWEW_BWOCKS);
	ECB_BWOCK(TWOFISH_PAWAWWEW_BWOCKS, twofish_ecb_enc_8way);
	ECB_BWOCK(3, twofish_enc_bwk_3way);
	ECB_BWOCK(1, twofish_enc_bwk);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, TF_BWOCK_SIZE, TWOFISH_PAWAWWEW_BWOCKS);
	ECB_BWOCK(TWOFISH_PAWAWWEW_BWOCKS, twofish_ecb_dec_8way);
	ECB_BWOCK(3, twofish_dec_bwk_3way);
	ECB_BWOCK(1, twofish_dec_bwk);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, TF_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(twofish_enc_bwk);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, TF_BWOCK_SIZE, TWOFISH_PAWAWWEW_BWOCKS);
	CBC_DEC_BWOCK(TWOFISH_PAWAWWEW_BWOCKS, twofish_cbc_dec_8way);
	CBC_DEC_BWOCK(3, twofish_dec_bwk_cbc_3way);
	CBC_DEC_BWOCK(1, twofish_dec_bwk);
	CBC_WAWK_END();
}

static stwuct skciphew_awg twofish_awgs[] = {
	{
		.base.cwa_name		= "__ecb(twofish)",
		.base.cwa_dwivew_name	= "__ecb-twofish-avx",
		.base.cwa_pwiowity	= 400,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= TF_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct twofish_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.setkey			= twofish_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "__cbc(twofish)",
		.base.cwa_dwivew_name	= "__cbc-twofish-avx",
		.base.cwa_pwiowity	= 400,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= TF_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct twofish_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= TF_MIN_KEY_SIZE,
		.max_keysize		= TF_MAX_KEY_SIZE,
		.ivsize			= TF_BWOCK_SIZE,
		.setkey			= twofish_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	},
};

static stwuct simd_skciphew_awg *twofish_simd_awgs[AWWAY_SIZE(twofish_awgs)];

static int __init twofish_init(void)
{
	const chaw *featuwe_name;

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, &featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(twofish_awgs,
					      AWWAY_SIZE(twofish_awgs),
					      twofish_simd_awgs);
}

static void __exit twofish_exit(void)
{
	simd_unwegistew_skciphews(twofish_awgs, AWWAY_SIZE(twofish_awgs),
				  twofish_simd_awgs);
}

moduwe_init(twofish_init);
moduwe_exit(twofish_exit);

MODUWE_DESCWIPTION("Twofish Ciphew Awgowithm, AVX optimized");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("twofish");
