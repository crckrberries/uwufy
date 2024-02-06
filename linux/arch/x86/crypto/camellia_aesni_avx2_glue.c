// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue Code fow x86_64/AVX2/AES-NI assembwew optimized vewsion of Camewwia
 *
 * Copywight © 2013 Jussi Kiviwinna <jussi.kiviwinna@mbnet.fi>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "camewwia.h"
#incwude "ecb_cbc_hewpews.h"

#define CAMEWWIA_AESNI_PAWAWWEW_BWOCKS 16
#define CAMEWWIA_AESNI_AVX2_PAWAWWEW_BWOCKS 32

/* 32-way AVX2/AES-NI pawawwew ciphew functions */
asmwinkage void camewwia_ecb_enc_32way(const void *ctx, u8 *dst, const u8 *swc);
asmwinkage void camewwia_ecb_dec_32way(const void *ctx, u8 *dst, const u8 *swc);

asmwinkage void camewwia_cbc_dec_32way(const void *ctx, u8 *dst, const u8 *swc);

static int camewwia_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			   unsigned int keywen)
{
	wetuwn __camewwia_setkey(cwypto_skciphew_ctx(tfm), key, keywen);
}

static int ecb_encwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, CAMEWWIA_BWOCK_SIZE, CAMEWWIA_AESNI_PAWAWWEW_BWOCKS);
	ECB_BWOCK(CAMEWWIA_AESNI_AVX2_PAWAWWEW_BWOCKS, camewwia_ecb_enc_32way);
	ECB_BWOCK(CAMEWWIA_AESNI_PAWAWWEW_BWOCKS, camewwia_ecb_enc_16way);
	ECB_BWOCK(2, camewwia_enc_bwk_2way);
	ECB_BWOCK(1, camewwia_enc_bwk);
	ECB_WAWK_END();
}

static int ecb_decwypt(stwuct skciphew_wequest *weq)
{
	ECB_WAWK_STAWT(weq, CAMEWWIA_BWOCK_SIZE, CAMEWWIA_AESNI_PAWAWWEW_BWOCKS);
	ECB_BWOCK(CAMEWWIA_AESNI_AVX2_PAWAWWEW_BWOCKS, camewwia_ecb_dec_32way);
	ECB_BWOCK(CAMEWWIA_AESNI_PAWAWWEW_BWOCKS, camewwia_ecb_dec_16way);
	ECB_BWOCK(2, camewwia_dec_bwk_2way);
	ECB_BWOCK(1, camewwia_dec_bwk);
	ECB_WAWK_END();
}

static int cbc_encwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, CAMEWWIA_BWOCK_SIZE, -1);
	CBC_ENC_BWOCK(camewwia_enc_bwk);
	CBC_WAWK_END();
}

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	CBC_WAWK_STAWT(weq, CAMEWWIA_BWOCK_SIZE, CAMEWWIA_AESNI_PAWAWWEW_BWOCKS);
	CBC_DEC_BWOCK(CAMEWWIA_AESNI_AVX2_PAWAWWEW_BWOCKS, camewwia_cbc_dec_32way);
	CBC_DEC_BWOCK(CAMEWWIA_AESNI_PAWAWWEW_BWOCKS, camewwia_cbc_dec_16way);
	CBC_DEC_BWOCK(2, camewwia_decwypt_cbc_2way);
	CBC_DEC_BWOCK(1, camewwia_dec_bwk);
	CBC_WAWK_END();
}

static stwuct skciphew_awg camewwia_awgs[] = {
	{
		.base.cwa_name		= "__ecb(camewwia)",
		.base.cwa_dwivew_name	= "__ecb-camewwia-aesni-avx2",
		.base.cwa_pwiowity	= 500,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= CAMEWWIA_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct camewwia_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= CAMEWWIA_MIN_KEY_SIZE,
		.max_keysize		= CAMEWWIA_MAX_KEY_SIZE,
		.setkey			= camewwia_setkey,
		.encwypt		= ecb_encwypt,
		.decwypt		= ecb_decwypt,
	}, {
		.base.cwa_name		= "__cbc(camewwia)",
		.base.cwa_dwivew_name	= "__cbc-camewwia-aesni-avx2",
		.base.cwa_pwiowity	= 500,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= CAMEWWIA_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct camewwia_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= CAMEWWIA_MIN_KEY_SIZE,
		.max_keysize		= CAMEWWIA_MAX_KEY_SIZE,
		.ivsize			= CAMEWWIA_BWOCK_SIZE,
		.setkey			= camewwia_setkey,
		.encwypt		= cbc_encwypt,
		.decwypt		= cbc_decwypt,
	},
};

static stwuct simd_skciphew_awg *camewwia_simd_awgs[AWWAY_SIZE(camewwia_awgs)];

static int __init camewwia_aesni_init(void)
{
	const chaw *featuwe_name;

	if (!boot_cpu_has(X86_FEATUWE_AVX) ||
	    !boot_cpu_has(X86_FEATUWE_AVX2) ||
	    !boot_cpu_has(X86_FEATUWE_AES) ||
	    !boot_cpu_has(X86_FEATUWE_OSXSAVE)) {
		pw_info("AVX2 ow AES-NI instwuctions awe not detected.\n");
		wetuwn -ENODEV;
	}

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM,
				&featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(camewwia_awgs,
					      AWWAY_SIZE(camewwia_awgs),
					      camewwia_simd_awgs);
}

static void __exit camewwia_aesni_fini(void)
{
	simd_unwegistew_skciphews(camewwia_awgs, AWWAY_SIZE(camewwia_awgs),
				  camewwia_simd_awgs);
}

moduwe_init(camewwia_aesni_init);
moduwe_exit(camewwia_aesni_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Camewwia Ciphew Awgowithm, AES-NI/AVX2 optimized");
MODUWE_AWIAS_CWYPTO("camewwia");
MODUWE_AWIAS_CWYPTO("camewwia-asm");
