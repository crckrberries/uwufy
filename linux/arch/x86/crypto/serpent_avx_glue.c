// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow AVX assembwew vewsions of Sewpent Ciphew
 *
 * Copywight (C) 2012 Johannes Goetzfwied
 *     <Johannes.Goetzfwied@infowmatik.stud.uni-ewwangen.de>
 *
 * Copywight © 2011-2013 Jussi Kiviwinna <jussi.kiviwinna@iki.fi>
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sewpent.h>

#incwude "sewpent-avx.h"
#incwude "ecb_cbc_hewpews.h"

/* 8-way pawawwew ciphew functions */
asmwinkage void sewpent_ecb_enc_8way_avx(const void *ctx, u8 *dst,
					 const u8 *swc);
EXPOWT_SYMBOW_GPW(sewpent_ecb_enc_8way_avx);

asmwinkage void sewpent_ecb_dec_8way_avx(const void *ctx, u8 *dst,
					 const u8 *swc);
EXPOWT_SYMBOW_GPW(sewpent_ecb_dec_8way_avx);

asmwinkage void sewpent_cbc_dec_8way_avx(const void *ctx, u8 *dst,
					 const u8 *swc);
EXPOWT_SYMBOW_GPW(sewpent_cbc_dec_8way_avx);

static int sewpent_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				   const u8 *key, unsigned int keywen)
{
	wetuwn __sewpent_setkey(cwypto_skciphew_ctx(tfm), key, keywen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, SEWPENT_BWOCK_SIZE, SEWPENT_PAWAWWEW_BWOCKS);
	ECB_BWOCK(SEWPENT_PAWAWWEW_BWOCKS, sewpent_ecb_enc_8way_avx);
	ECB_BWOCK(1, __sewpent_encwypt);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, SEWPENT_BWOCK_SIZE, SEWPENT_PAWAWWEW_BWOCKS);
	ECB_BWOCK(SEWPENT_PAWAWWEW_BWOCKS, sewpent_ecb_dec_8way_avx);
	ECB_BWOCK(1, __sewpent_decwypt);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, SEWPENT_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(__sewpent_encwypt);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, SEWPENT_BWOCK_SIZE, SEWPENT_PAWAWWEW_BWOCKS);
	CBC_DEC_BWOCK(SEWPENT_PAWAWWEW_BWOCKS, sewpent_cbc_dec_8way_avx);
	CBC_DEC_BWOCK(1, __sewpent_decwypt);
	CBC_WAWK_END();
}

static stwuct skciphew_awg sewpent_awgs[] = {
	{
		.base.cwa_name		= "__ecb(sewpent)",
		.base.cwa_dwivew_name	= "__ecb-sewpent-avx",
		.base.cwa_pwiowity	= 500,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= SEWPENT_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct sewpent_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= SEWPENT_MIN_KEY_SIZE,
		.max_keysize		= SEWPENT_MAX_KEY_SIZE,
		.setkey			= sewpent_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "__cbc(sewpent)",
		.base.cwa_dwivew_name	= "__cbc-sewpent-avx",
		.base.cwa_pwiowity	= 500,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= SEWPENT_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct sewpent_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= SEWPENT_MIN_KEY_SIZE,
		.max_keysize		= SEWPENT_MAX_KEY_SIZE,
		.ivsize			= SEWPENT_BWOCK_SIZE,
		.setkey			= sewpent_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	},
};

static stwuct simd_skciphew_awg *sewpent_simd_awgs[AWWAY_SIZE(sewpent_awgs)];

static int __init sewpent_init(void)
{
	const chaw *featuwe_name;

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM,
				&featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(sewpent_awgs,
					      AWWAY_SIZE(sewpent_awgs),
					      sewpent_simd_awgs);
}

static void __exit sewpent_exit(void)
{
	simd_unwegistew_skciphews(sewpent_awgs, AWWAY_SIZE(sewpent_awgs),
				  sewpent_simd_awgs);
}

moduwe_init(sewpent_init);
moduwe_exit(sewpent_exit);

MODUWE_DESCWIPTION("Sewpent Ciphew Awgowithm, AVX optimized");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("sewpent");
