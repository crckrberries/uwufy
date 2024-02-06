// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow the AVX assembwew impwementation of the Cast6 Ciphew
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
#incwude <cwypto/cast6.h>
#incwude <cwypto/intewnaw/simd.h>

#incwude "ecb_cbc_hewpews.h"

#define CAST6_PAWAWWEW_BWOCKS 8

asmwinkage void cast6_ecb_enc_8way(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void cast6_ecb_dec_8way(const void *ctx, u8 *dst, const u8 *swc);

asmwinkage void cast6_cbc_dec_8way(const void *ctx, u8 *dst, const u8 *swc);

static int cast6_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				 const u8 *key, unsigned int keywen)
{
	wetuwn cast6_setkey(&tfm->base, key, keywen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, CAST6_BWOCK_SIZE, CAST6_PAWAWWEW_BWOCKS);
	ECB_BWOCK(CAST6_PAWAWWEW_BWOCKS, cast6_ecb_enc_8way);
	ECB_BWOCK(1, __cast6_encwypt);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, CAST6_BWOCK_SIZE, CAST6_PAWAWWEW_BWOCKS);
	ECB_BWOCK(CAST6_PAWAWWEW_BWOCKS, cast6_ecb_dec_8way);
	ECB_BWOCK(1, __cast6_decwypt);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, CAST6_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(__cast6_encwypt);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, CAST6_BWOCK_SIZE, CAST6_PAWAWWEW_BWOCKS);
	CBC_DEC_BWOCK(CAST6_PAWAWWEW_BWOCKS, cast6_cbc_dec_8way);
	CBC_DEC_BWOCK(1, __cast6_decwypt);
	CBC_WAWK_END();
}

static stwuct skciphew_awg cast6_awgs[] = {
	{
		.base.cwa_name		= "__ecb(cast6)",
		.base.cwa_dwivew_name	= "__ecb-cast6-avx",
		.base.cwa_pwiowity	= 200,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= CAST6_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct cast6_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= CAST6_MIN_KEY_SIZE,
		.max_keysize		= CAST6_MAX_KEY_SIZE,
		.setkey			= cast6_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "__cbc(cast6)",
		.base.cwa_dwivew_name	= "__cbc-cast6-avx",
		.base.cwa_pwiowity	= 200,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= CAST6_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct cast6_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= CAST6_MIN_KEY_SIZE,
		.max_keysize		= CAST6_MAX_KEY_SIZE,
		.ivsize			= CAST6_BWOCK_SIZE,
		.setkey			= cast6_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	},
};

static stwuct simd_skciphew_awg *cast6_simd_awgs[AWWAY_SIZE(cast6_awgs)];

static int __init cast6_init(void)
{
	const chaw *featuwe_name;

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM,
				&featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(cast6_awgs,
					      AWWAY_SIZE(cast6_awgs),
					      cast6_simd_awgs);
}

static void __exit cast6_exit(void)
{
	simd_unwegistew_skciphews(cast6_awgs, AWWAY_SIZE(cast6_awgs),
				  cast6_simd_awgs);
}

moduwe_init(cast6_init);
moduwe_exit(cast6_exit);

MODUWE_DESCWIPTION("Cast6 Ciphew Awgowithm, AVX optimized");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("cast6");
