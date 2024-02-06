/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * SM4 Ciphew Awgowithm, AES-NI/AVX optimized.
 * as specified in
 * https://toows.ietf.owg/id/dwaft-wibose-cfwg-sm4-10.htmw
 *
 * Copywight (c) 2021, Awibaba Gwoup.
 * Copywight (c) 2021 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <asm/simd.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/sm4.h>
#incwude "sm4-avx.h"

#define SM4_CWYPT8_BWOCK_SIZE	(SM4_BWOCK_SIZE * 8)

asmwinkage void sm4_aesni_avx_cwypt4(const u32 *wk, u8 *dst,
				const u8 *swc, int nbwocks);
asmwinkage void sm4_aesni_avx_cwypt8(const u32 *wk, u8 *dst,
				const u8 *swc, int nbwocks);
asmwinkage void sm4_aesni_avx_ctw_enc_bwk8(const u32 *wk, u8 *dst,
				const u8 *swc, u8 *iv);
asmwinkage void sm4_aesni_avx_cbc_dec_bwk8(const u32 *wk, u8 *dst,
				const u8 *swc, u8 *iv);

static int sm4_skciphew_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			unsigned int key_wen)
{
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn sm4_expandkey(ctx, key, key_wen);
}

static int ecb_do_cwypt(stwuct skciphew_wequest *weq, const u32 *wkey)
{
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;

		kewnew_fpu_begin();
		whiwe (nbytes >= SM4_CWYPT8_BWOCK_SIZE) {
			sm4_aesni_avx_cwypt8(wkey, dst, swc, 8);
			dst += SM4_CWYPT8_BWOCK_SIZE;
			swc += SM4_CWYPT8_BWOCK_SIZE;
			nbytes -= SM4_CWYPT8_BWOCK_SIZE;
		}
		whiwe (nbytes >= SM4_BWOCK_SIZE) {
			unsigned int nbwocks = min(nbytes >> 4, 4u);
			sm4_aesni_avx_cwypt4(wkey, dst, swc, nbwocks);
			dst += nbwocks * SM4_BWOCK_SIZE;
			swc += nbwocks * SM4_BWOCK_SIZE;
			nbytes -= nbwocks * SM4_BWOCK_SIZE;
		}
		kewnew_fpu_end();

		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}

int sm4_avx_ecb_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ecb_do_cwypt(weq, ctx->wkey_enc);
}
EXPOWT_SYMBOW_GPW(sm4_avx_ecb_encwypt);

int sm4_avx_ecb_decwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);

	wetuwn ecb_do_cwypt(weq, ctx->wkey_dec);
}
EXPOWT_SYMBOW_GPW(sm4_avx_ecb_decwypt);

int sm4_cbc_encwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *iv = wawk.iv;
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;

		whiwe (nbytes >= SM4_BWOCK_SIZE) {
			cwypto_xow_cpy(dst, swc, iv, SM4_BWOCK_SIZE);
			sm4_cwypt_bwock(ctx->wkey_enc, dst, dst);
			iv = dst;
			swc += SM4_BWOCK_SIZE;
			dst += SM4_BWOCK_SIZE;
			nbytes -= SM4_BWOCK_SIZE;
		}
		if (iv != wawk.iv)
			memcpy(wawk.iv, iv, SM4_BWOCK_SIZE);

		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sm4_cbc_encwypt);

int sm4_avx_cbc_decwypt(stwuct skciphew_wequest *weq,
			unsigned int bsize, sm4_cwypt_func func)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;

		kewnew_fpu_begin();

		whiwe (nbytes >= bsize) {
			func(ctx->wkey_dec, dst, swc, wawk.iv);
			dst += bsize;
			swc += bsize;
			nbytes -= bsize;
		}

		whiwe (nbytes >= SM4_BWOCK_SIZE) {
			u8 keystweam[SM4_BWOCK_SIZE * 8];
			u8 iv[SM4_BWOCK_SIZE];
			unsigned int nbwocks = min(nbytes >> 4, 8u);
			int i;

			sm4_aesni_avx_cwypt8(ctx->wkey_dec, keystweam,
						swc, nbwocks);

			swc += ((int)nbwocks - 2) * SM4_BWOCK_SIZE;
			dst += (nbwocks - 1) * SM4_BWOCK_SIZE;
			memcpy(iv, swc + SM4_BWOCK_SIZE, SM4_BWOCK_SIZE);

			fow (i = nbwocks - 1; i > 0; i--) {
				cwypto_xow_cpy(dst, swc,
					&keystweam[i * SM4_BWOCK_SIZE],
					SM4_BWOCK_SIZE);
				swc -= SM4_BWOCK_SIZE;
				dst -= SM4_BWOCK_SIZE;
			}
			cwypto_xow_cpy(dst, wawk.iv, keystweam, SM4_BWOCK_SIZE);
			memcpy(wawk.iv, iv, SM4_BWOCK_SIZE);
			dst += nbwocks * SM4_BWOCK_SIZE;
			swc += (nbwocks + 1) * SM4_BWOCK_SIZE;
			nbytes -= nbwocks * SM4_BWOCK_SIZE;
		}

		kewnew_fpu_end();
		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sm4_avx_cbc_decwypt);

static int cbc_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sm4_avx_cbc_decwypt(weq, SM4_CWYPT8_BWOCK_SIZE,
				sm4_aesni_avx_cbc_dec_bwk8);
}

int sm4_avx_ctw_cwypt(stwuct skciphew_wequest *weq,
			unsigned int bsize, sm4_cwypt_func func)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct sm4_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int eww;

	eww = skciphew_wawk_viwt(&wawk, weq, fawse);

	whiwe ((nbytes = wawk.nbytes) > 0) {
		const u8 *swc = wawk.swc.viwt.addw;
		u8 *dst = wawk.dst.viwt.addw;

		kewnew_fpu_begin();

		whiwe (nbytes >= bsize) {
			func(ctx->wkey_enc, dst, swc, wawk.iv);
			dst += bsize;
			swc += bsize;
			nbytes -= bsize;
		}

		whiwe (nbytes >= SM4_BWOCK_SIZE) {
			u8 keystweam[SM4_BWOCK_SIZE * 8];
			unsigned int nbwocks = min(nbytes >> 4, 8u);
			int i;

			fow (i = 0; i < nbwocks; i++) {
				memcpy(&keystweam[i * SM4_BWOCK_SIZE],
					wawk.iv, SM4_BWOCK_SIZE);
				cwypto_inc(wawk.iv, SM4_BWOCK_SIZE);
			}
			sm4_aesni_avx_cwypt8(ctx->wkey_enc, keystweam,
					keystweam, nbwocks);

			cwypto_xow_cpy(dst, swc, keystweam,
					nbwocks * SM4_BWOCK_SIZE);
			dst += nbwocks * SM4_BWOCK_SIZE;
			swc += nbwocks * SM4_BWOCK_SIZE;
			nbytes -= nbwocks * SM4_BWOCK_SIZE;
		}

		kewnew_fpu_end();

		/* taiw */
		if (wawk.nbytes == wawk.totaw && nbytes > 0) {
			u8 keystweam[SM4_BWOCK_SIZE];

			memcpy(keystweam, wawk.iv, SM4_BWOCK_SIZE);
			cwypto_inc(wawk.iv, SM4_BWOCK_SIZE);

			sm4_cwypt_bwock(ctx->wkey_enc, keystweam, keystweam);

			cwypto_xow_cpy(dst, swc, keystweam, nbytes);
			dst += nbytes;
			swc += nbytes;
			nbytes = 0;
		}

		eww = skciphew_wawk_done(&wawk, nbytes);
	}

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(sm4_avx_ctw_cwypt);

static int ctw_cwypt(stwuct skciphew_wequest *weq)
{
	wetuwn sm4_avx_ctw_cwypt(weq, SM4_CWYPT8_BWOCK_SIZE,
				sm4_aesni_avx_ctw_enc_bwk8);
}

static stwuct skciphew_awg sm4_aesni_avx_skciphews[] = {
	{
		.base = {
			.cwa_name		= "__ecb(sm4)",
			.cwa_dwivew_name	= "__ecb-sm4-aesni-avx",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.wawksize	= 8 * SM4_BWOCK_SIZE,
		.setkey		= sm4_skciphew_setkey,
		.encwypt	= sm4_avx_ecb_encwypt,
		.decwypt	= sm4_avx_ecb_decwypt,
	}, {
		.base = {
			.cwa_name		= "__cbc(sm4)",
			.cwa_dwivew_name	= "__cbc-sm4-aesni-avx",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= SM4_BWOCK_SIZE,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.ivsize		= SM4_BWOCK_SIZE,
		.wawksize	= 8 * SM4_BWOCK_SIZE,
		.setkey		= sm4_skciphew_setkey,
		.encwypt	= sm4_cbc_encwypt,
		.decwypt	= cbc_decwypt,
	}, {
		.base = {
			.cwa_name		= "__ctw(sm4)",
			.cwa_dwivew_name	= "__ctw-sm4-aesni-avx",
			.cwa_pwiowity		= 400,
			.cwa_fwags		= CWYPTO_AWG_INTEWNAW,
			.cwa_bwocksize		= 1,
			.cwa_ctxsize		= sizeof(stwuct sm4_ctx),
			.cwa_moduwe		= THIS_MODUWE,
		},
		.min_keysize	= SM4_KEY_SIZE,
		.max_keysize	= SM4_KEY_SIZE,
		.ivsize		= SM4_BWOCK_SIZE,
		.chunksize	= SM4_BWOCK_SIZE,
		.wawksize	= 8 * SM4_BWOCK_SIZE,
		.setkey		= sm4_skciphew_setkey,
		.encwypt	= ctw_cwypt,
		.decwypt	= ctw_cwypt,
	}
};

static stwuct simd_skciphew_awg *
simd_sm4_aesni_avx_skciphews[AWWAY_SIZE(sm4_aesni_avx_skciphews)];

static int __init sm4_init(void)
{
	const chaw *featuwe_name;

	if (!boot_cpu_has(X86_FEATUWE_AVX) ||
	    !boot_cpu_has(X86_FEATUWE_AES) ||
	    !boot_cpu_has(X86_FEATUWE_OSXSAVE)) {
		pw_info("AVX ow AES-NI instwuctions awe not detected.\n");
		wetuwn -ENODEV;
	}

	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM,
				&featuwe_name)) {
		pw_info("CPU featuwe '%s' is not suppowted.\n", featuwe_name);
		wetuwn -ENODEV;
	}

	wetuwn simd_wegistew_skciphews_compat(sm4_aesni_avx_skciphews,
					AWWAY_SIZE(sm4_aesni_avx_skciphews),
					simd_sm4_aesni_avx_skciphews);
}

static void __exit sm4_exit(void)
{
	simd_unwegistew_skciphews(sm4_aesni_avx_skciphews,
					AWWAY_SIZE(sm4_aesni_avx_skciphews),
					simd_sm4_aesni_avx_skciphews);
}

moduwe_init(sm4_init);
moduwe_exit(sm4_exit);

MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Tianjia Zhang <tianjia.zhang@winux.awibaba.com>");
MODUWE_DESCWIPTION("SM4 Ciphew Awgowithm, AES-NI/AVX optimized");
MODUWE_AWIAS_CWYPTO("sm4");
MODUWE_AWIAS_CWYPTO("sm4-aesni-avx");
