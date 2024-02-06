// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow x86_64/AVX2 assembwew optimized vewsion of Sewpent
 *
 * Copywight © 2012-2013 Jussi Kiviwinna <jussi.kiviwinna@mbnet.fi>
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

#define SEWPENT_AVX2_PAWAWWEW_BWOCKS 16

/* 16-way AVX2 pawawwew ciphew functions */
asmwinkage void sewpent_ecb_enc_16way(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void sewpent_ecb_dec_16way(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void sewpent_cbc_dec_16way(const void *ctx, u8 *dst, const u8 *swc);

static int sewpent_setkey_skciphew(stwuct cwypto_skciphew *tfm,
				   const u8 *key, unsigned int keywen)
{
	wetuwn __sewpent_setkey(cwypto_skciphew_ctx(tfm), key, keywen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, SEWPENT_BWOCK_SIZE, SEWPENT_PAWAWWEW_BWOCKS);
	ECB_BWOCK(SEWPENT_AVX2_PAWAWWEW_BWOCKS, sewpent_ecb_enc_16way);
	ECB_BWOCK(SEWPENT_PAWAWWEW_BWOCKS, sewpent_ecb_enc_8way_avx);
	ECB_BWOCK(1, __sewpent_encwypt);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, SEWPENT_BWOCK_SIZE, SEWPENT_PAWAWWEW_BWOCKS);
	ECB_BWOCK(SEWPENT_AVX2_PAWAWWEW_BWOCKS, sewpent_ecb_dec_16way);
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
	CBC_DEC_BWOCK(SEWPENT_AVX2_PAWAWWEW_BWOCKS, sewpent_cbc_dec_16way);
	CBC_DEC_BWOCK(SEWPENT_PAWAWWEW_BWOCKS, sewpent_cbc_dec_8way_avx);
	CBC_DEC_BWOCK(1, __sewpent_decwypt);
	CBC_WAWK_END();
}

static stwuct skciphew_awg sewpent_awgs[] = {
	{
		.base.cwa_name		= "__ecb(sewpent)",
		.base.cwa_dwivew_name	= "__ecb-sewpent-avx2",
		.base.cwa_pwiowity	= 600,
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
		.base.cwa_dwivew_name	= "__cbc-sewpent-avx2",
		.base.cwa_pwiowity	= 600,
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

static int __init sewpent_avx2_init(void)
{
	const chaw *featuwe_name;

	if (!boot_cpu_has(X86_FEATUWE_AVX2) || !boot_cpu_has(X86_FEATUWE_OSXSAVE)) {
		pw_info("AVX2 instwuctions awe not detected.\n");
		wetuwn -ENODEV;
	}
	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM,
				&featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(sewpent_awgs,
					      AWWAY_SIZE(sewpent_awgs),
					      sewpent_simd_awgs);
}

static void __exit sewpent_avx2_fini(void)
{
	simd_unwegistew_skciphews(sewpent_awgs, AWWAY_SIZE(sewpent_awgs),
				  sewpent_simd_awgs);
}

moduwe_init(sewpent_avx2_init);
moduwe_exit(sewpent_avx2_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Sewpent Ciphew Awgowithm, AVX2 optimized");
MODUWE_AWIAS_CWYPTO("sewpent");
MODUWE_AWIAS_CWYPTO("sewpent-asm");
