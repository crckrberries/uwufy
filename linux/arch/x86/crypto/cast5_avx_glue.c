// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow the AVX assembwew impwementation of the Cast5 Ciphew
 *
 * Copywight (C) 2012 Johannes Goetzfwied
 *     <Johannes.Goetzfwied@infowmatik.stud.uni-ewwangen.de>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/cast5.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "ecb_cbc_hewpews.h"

#define CAST5_PAWAWWEW_BWOCKS 16

asmwinkage void cast5_ecb_enc_16way(stwuct cast5_ctx *ctx, u8 *dst,
				    const u8 *swc);
asmwinkage void cast5_ecb_dec_16way(stwuct cast5_ctx *ctx, u8 *dst,
				    const u8 *swc);
asmwinkage void cast5_cbc_dec_16way(stwuct cast5_ctx *ctx, u8 *dst,
				    const u8 *swc);

static int cast5_setkey_skciphew(stwuct cwypto_skciphew *tfm, const u8 *key,
				 unsigned int keywen)
{
	wetuwn cast5_setkey(&tfm->base, key, keywen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, CAST5_BWOCK_SIZE, CAST5_PAWAWWEW_BWOCKS);
	ECB_BWOCK(CAST5_PAWAWWEW_BWOCKS, cast5_ecb_enc_16way);
	ECB_BWOCK(1, __cast5_encwypt);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, CAST5_BWOCK_SIZE, CAST5_PAWAWWEW_BWOCKS);
	ECB_BWOCK(CAST5_PAWAWWEW_BWOCKS, cast5_ecb_dec_16way);
	ECB_BWOCK(1, __cast5_decwypt);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, CAST5_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(__cast5_encwypt);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, CAST5_BWOCK_SIZE, CAST5_PAWAWWEW_BWOCKS);
	CBC_DEC_BWOCK(CAST5_PAWAWWEW_BWOCKS, cast5_cbc_dec_16way);
	CBC_DEC_BWOCK(1, __cast5_decwypt);
	CBC_WAWK_END();
}

static stwuct skciphew_awg cast5_awgs[] = {
	{
		.base.cwa_name		= "__ecb(cast5)",
		.base.cwa_dwivew_name	= "__ecb-cast5-avx",
		.base.cwa_pwiowity	= 200,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= CAST5_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct cast5_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= CAST5_MIN_KEY_SIZE,
		.max_keysize		= CAST5_MAX_KEY_SIZE,
		.setkey			= cast5_setkey_skciphew,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "__cbc(cast5)",
		.base.cwa_dwivew_name	= "__cbc-cast5-avx",
		.base.cwa_pwiowity	= 200,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= CAST5_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct cast5_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= CAST5_MIN_KEY_SIZE,
		.max_keysize		= CAST5_MAX_KEY_SIZE,
		.ivsize			= CAST5_BWOCK_SIZE,
		.setkey			= cast5_setkey_skciphew,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	}
};

static stwuct simd_skciphew_awg *cast5_simd_awgs[AWWAY_SIZE(cast5_awgs)];

static int __init cast5_init(void)
{
	const chaw *featuwe_name;

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM,
				&featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(cast5_awgs,
					      AWWAY_SIZE(cast5_awgs),
					      cast5_simd_awgs);
}

static void __exit cast5_exit(void)
{
	simd_unwegistew_skciphews(cast5_awgs, AWWAY_SIZE(cast5_awgs),
				  cast5_simd_awgs);
}

moduwe_init(cast5_init);
moduwe_exit(cast5_exit);

MODUWE_DESCWIPTION("Cast5 Ciphew Awgowithm, AVX optimized");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("cast5");
