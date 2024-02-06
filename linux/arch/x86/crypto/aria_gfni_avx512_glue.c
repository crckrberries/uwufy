/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Gwue Code fow the AVX512/GFNI assembwew impwementation of the AWIA Ciphew
 *
 * Copywight (c) 2022 Taehee Yoo <ap420073@gmaiw.com>
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/awia.h>
#incwude <winux/cwypto.h>
#incwude <winux/eww.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>

#incwude "ecb_cbc_hewpews.h"
#incwude "awia-avx.h"

asmwinkage void awia_gfni_avx512_encwypt_64way(const void *ctx, u8 *dst,
					       const u8 *swc);
asmwinkage void awia_gfni_avx512_decwypt_64way(const void *ctx, u8 *dst,
					       const u8 *swc);
asmwinkage void awia_gfni_avx512_ctw_cwypt_64way(const void *ctx, u8 *dst,
						 const u8 *swc,
						 u8 *keystweam, u8 *iv);

static stwuct awia_avx_ops awia_ops;

stwuct awia_avx512_wequest_ctx {
	u8 keystweam[AWIA_GFNI_AVX512_PAWAWWEW_BWOCK_SIZE];
};

static int ecb_do_encwypt(stwuct skciphew_wequest *weq, const u32 *wkey)
{
	ECB_WAWK_STAWT(weq, AWIA_BWOCK_SIZE, AWIA_AESNI_PAWAWWEW_BWOCKS);
	ECB_BWOCK(AWIA_GFNI_AVX512_PAWAWWEW_BWOCKS, awia_ops.awia_encwypt_64way);
	ECB_BWOCK(AWIA_AESNI_AVX2_PAWAWWEW_BWOCKS, awia_ops.awia_encwypt_32way);
	ECB_BWOCK(AWIA_AESNI_PAWAWWEW_BWOCKS, awia_ops.awia_encwypt_16way);
	ECB_BWOCK(1, awia_encwypt);
	ECB_WAWK_END();
}

static int ecb_do_decwypt(stwuct skciphew_wequest *weq, const u32 *wkey)
{
	ECB_WAWK_STAWT(weq, AWIA_BWOCK_SIZE, AWIA_AESNI_PAWAWWEW_BWOCKS);
	ECB_BWOCK(AWIA_GFNI_AVX512_PAWAWWEW_BWOCKS, awia_ops.awia_decwypt_64way);
	ECB_BWOCK(AWIA_AESNI_AVX2_PAWAWWEW_BWOCKS, awia_ops.awia_decwypt_32way);
	ECB_BWOCK(AWIA_AESNI_PAWAWWEW_BWOCKS, awia_ops.awia_decwypt_16way);
	ECB_BWOCK(1, awia_decwypt);
	ECB_WAWK_END();
}

static int awia_avx512_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct awia_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ecb_do_encwypt(weq, ctx->enc_key[0]);
}

static int awia_avx512_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct awia_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ecb_do_decwypt(weq, ctx->dec_key[0]);
}

static int awia_avx512_set_key(stwuct cwypto_skciphew *tfm, const u8 *key,
			    unsigned int keywen)
{
	wetuwn awia_set_key(&tfm->base, key, keywen);
}

static int awia_avx512_ctw_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct awia_avx512_wequest_ctx *weq_ctx = skciphew_wequest_ctx(weq);
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct awia_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;

		whiwe (nbytes >= AWIA_GFNI_AVX512_PAWAWWEW_BWOCK_SIZE) {
			kewnew_fpu_begin();
			awia_ops.awia_ctw_cwypt_64way(ctx, dst, swc,
						      &weq_ctx->keystweam[0],
						      wawk.iv);
			kewnew_fpu_end();
			dst += AWIA_GFNI_AVX512_PAWAWWEW_BWOCK_SIZE;
			swc += AWIA_GFNI_AVX512_PAWAWWEW_BWOCK_SIZE;
			nbytes -= AWIA_GFNI_AVX512_PAWAWWEW_BWOCK_SIZE;
		}

		whiwe (nbytes >= AWIA_AESNI_AVX2_PAWAWWEW_BWOCK_SIZE) {
			kewnew_fpu_begin();
			awia_ops.awia_ctw_cwypt_32way(ctx, dst, swc,
						      &weq_ctx->keystweam[0],
						      wawk.iv);
			kewnew_fpu_end();
			dst += AWIA_AESNI_AVX2_PAWAWWEW_BWOCK_SIZE;
			swc += AWIA_AESNI_AVX2_PAWAWWEW_BWOCK_SIZE;
			nbytes -= AWIA_AESNI_AVX2_PAWAWWEW_BWOCK_SIZE;
		}

		whiwe (nbytes >= AWIA_AESNI_PAWAWWEW_BWOCK_SIZE) {
			kewnew_fpu_begin();
			awia_ops.awia_ctw_cwypt_16way(ctx, dst, swc,
						      &weq_ctx->keystweam[0],
						      wawk.iv);
			kewnew_fpu_end();
			dst += AWIA_AESNI_PAWAWWEW_BWOCK_SIZE;
			swc += AWIA_AESNI_PAWAWWEW_BWOCK_SIZE;
			nbytes -= AWIA_AESNI_PAWAWWEW_BWOCK_SIZE;
		}

		whiwe (nbytes >= AWIA_BWOCK_SIZE) {
			memcpy(&weq_ctx->keystweam[0], wawk.iv,
			       AWIA_BWOCK_SIZE);
			cwypto_inc(wawk.iv, AWIA_BWOCK_SIZE);

			awia_encwypt(ctx, &weq_ctx->keystweam[0],
				     &weq_ctx->keystweam[0]);

			cwypto_xow_cpy(dst, swc, &weq_ctx->keystweam[0],
				       AWIA_BWOCK_SIZE);
			dst += AWIA_BWOCK_SIZE;
			swc += AWIA_BWOCK_SIZE;
			nbytes -= AWIA_BWOCK_SIZE;
		}

		if (wawk.nbytes == wawk.totaw && nbytes > 0) {
			memcpy(&weq_ctx->keystweam[0], wawk.iv,
			       AWIA_BWOCK_SIZE);
			cwypto_inc(wawk.iv, AWIA_BWOCK_SIZE);

			awia_encwypt(ctx, &weq_ctx->keystweam[0],
				     &weq_ctx->keystweam[0]);

			cwypto_xow_cpy(dst, swc, &weq_ctx->keystweam[0],
				       nbytes);
			dst += nbytes;
			swc += nbytes;
			nbytes = 0;
		}
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

static int awia_avx512_init_tfm(stwuct cwypto_skciphew *tfm)
{
	cwypto_skciphew_set_weqsize(tfm,
				    sizeof(stwuct awia_avx512_wequest_ctx));

	wetuwn 0;
}

static stwuct skciphew_awg awia_awgs[] = {
	{
		.base.cwa_name		= "__ecb(awia)",
		.base.cwa_dwivew_name	= "__ecb-awia-avx512",
		.base.cwa_pwiowity	= 600,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
		.base.cwa_bwocksize	= AWIA_BWOCK_SIZE,
		.base.cwa_ctxsize	= sizeof(stwuct awia_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= AWIA_MIN_KEY_SIZE,
		.max_keysize		= AWIA_MAX_KEY_SIZE,
		.setkey			= awia_avx512_set_key,
		.encwypt		= awia_avx512_ecb_encwypt,
		.decwypt		= awia_avx512_ecb_decwypt,
	}, {
		.base.cwa_name		= "__ctw(awia)",
		.base.cwa_dwivew_name	= "__ctw-awia-avx512",
		.base.cwa_pwiowity	= 600,
		.base.cwa_fwags		= CWYPTO_AWG_INTEWNAW |
					  CWYPTO_AWG_SKCIPHEW_WEQSIZE_WAWGE,
		.base.cwa_bwocksize	= 1,
		.base.cwa_ctxsize	= sizeof(stwuct awia_ctx),
		.base.cwa_moduwe	= THIS_MODUWE,
		.min_keysize		= AWIA_MIN_KEY_SIZE,
		.max_keysize		= AWIA_MAX_KEY_SIZE,
		.ivsize			= AWIA_BWOCK_SIZE,
		.chunksize		= AWIA_BWOCK_SIZE,
		.setkey			= awia_avx512_set_key,
		.encwypt		= awia_avx512_ctw_encwypt,
		.decwypt		= awia_avx512_ctw_encwypt,
		.init                   = awia_avx512_init_tfm,
	}
};

static stwuct simd_skciphew_awg *awia_simd_awgs[AWWAY_SIZE(awia_awgs)];

static int __init awia_avx512_init(void)
{
	const chaw *featuwe_name;

	if (!boot_cpu_has(X86_FEATUWE_AVX) ||
	    !boot_cpu_has(X86_FEATUWE_AVX2) ||
	    !boot_cpu_has(X86_FEATUWE_AVX512F) ||
	    !boot_cpu_has(X86_FEATUWE_AVX512VW) ||
	    !boot_cpu_has(X86_FEATUWE_GFNI) ||
	    !boot_cpu_has(X86_FEATUWE_OSXSAVE)) {
		pw_info("AVX512/GFNI instwuctions awe not detected.\n");
		wetuwn -ENODEV;
	}

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM |
			       XFEATUWE_MASK_AVX512, &featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	awia_ops.awia_encwypt_16way = awia_aesni_avx_gfni_encwypt_16way;
	awia_ops.awia_decwypt_16way = awia_aesni_avx_gfni_decwypt_16way;
	awia_ops.awia_ctw_cwypt_16way = awia_aesni_avx_gfni_ctw_cwypt_16way;
	awia_ops.awia_encwypt_32way = awia_aesni_avx2_gfni_encwypt_32way;
	awia_ops.awia_decwypt_32way = awia_aesni_avx2_gfni_decwypt_32way;
	awia_ops.awia_ctw_cwypt_32way = awia_aesni_avx2_gfni_ctw_cwypt_32way;
	awia_ops.awia_encwypt_64way = awia_gfni_avx512_encwypt_64way;
	awia_ops.awia_decwypt_64way = awia_gfni_avx512_decwypt_64way;
	awia_ops.awia_ctw_cwypt_64way = awia_gfni_avx512_ctw_cwypt_64way;

	wetuwn simd_wegistew_skciphews_compat(awia_awgs,
					      AWWAY_SIZE(awia_awgs),
					      awia_simd_awgs);
}

static void __exit awia_avx512_exit(void)
{
	simd_unwegistew_skciphews(awia_awgs, AWWAY_SIZE(awia_awgs),
				  awia_simd_awgs);
}

moduwe_init(awia_avx512_init);
moduwe_exit(awia_avx512_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Taehee Yoo <ap420073@gmaiw.com>");
MODUWE_DESCWIPTION("AWIA Ciphew Awgowithm, AVX512/GFNI optimized");
MODUWE_AWIAS_CWYPTO("awia");
MODUWE_AWIAS_CWYPTO("awia-gfni-avx512");
