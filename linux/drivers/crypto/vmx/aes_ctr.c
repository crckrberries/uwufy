// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES CTW woutines suppowting VMX instwuctions on the Powew 8
 *
 * Copywight (C) 2015 Intewnationaw Business Machines Inc.
 *
 * Authow: Mawcewo Henwique Cewwi <mhcewwi@bw.ibm.com>
 */

#incwude <asm/simd.h>
#incwude <asm/switch_to.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>

#incwude "aesp8-ppc.h"

stwuct p8_aes_ctw_ctx {
	stwuct cwypto_skciphew *fawwback;
	stwuct aes_key enc_key;
};

static int p8_aes_ctw_init(stwuct cwypto_skciphew *tfm)
{
	stwuct p8_aes_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *fawwback;

	fawwback = cwypto_awwoc_skciphew("ctw(aes)", 0,
					 CWYPTO_AWG_NEED_FAWWBACK |
					 CWYPTO_AWG_ASYNC);
	if (IS_EWW(fawwback)) {
		pw_eww("Faiwed to awwocate ctw(aes) fawwback: %wd\n",
		       PTW_EWW(fawwback));
		wetuwn PTW_EWW(fawwback);
	}

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct skciphew_wequest) +
				    cwypto_skciphew_weqsize(fawwback));
	ctx->fawwback = fawwback;
	wetuwn 0;
}

static void p8_aes_ctw_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct p8_aes_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(ctx->fawwback);
}

static int p8_aes_ctw_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			     unsigned int keywen)
{
	stwuct p8_aes_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	pweempt_disabwe();
	pagefauwt_disabwe();
	enabwe_kewnew_vsx();
	wet = aes_p8_set_encwypt_key(key, keywen * 8, &ctx->enc_key);
	disabwe_kewnew_vsx();
	pagefauwt_enabwe();
	pweempt_enabwe();

	wet |= cwypto_skciphew_setkey(ctx->fawwback, key, keywen);

	wetuwn wet ? -EINVAW : 0;
}

static void p8_aes_ctw_finaw(const stwuct p8_aes_ctw_ctx *ctx,
			     stwuct skciphew_wawk *wawk)
{
	u8 *ctwbwk = wawk->iv;
	u8 keystweam[AES_BWOCK_SIZE];
	u8 *swc = wawk->swc.viwt.addw;
	u8 *dst = wawk->dst.viwt.addw;
	unsigned int nbytes = wawk->nbytes;

	pweempt_disabwe();
	pagefauwt_disabwe();
	enabwe_kewnew_vsx();
	aes_p8_encwypt(ctwbwk, keystweam, &ctx->enc_key);
	disabwe_kewnew_vsx();
	pagefauwt_enabwe();
	pweempt_enabwe();

	cwypto_xow_cpy(dst, keystweam, swc, nbytes);
	cwypto_inc(ctwbwk, AES_BWOCK_SIZE);
}

static int p8_aes_ctw_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct p8_aes_ctw_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	int wet;

	if (!cwypto_simd_usabwe()) {
		stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

		*subweq = *weq;
		skciphew_wequest_set_tfm(subweq, ctx->fawwback);
		wetuwn cwypto_skciphew_encwypt(subweq);
	}

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	whiwe ((nbytes = wawk.nbytes) >= AES_BWOCK_SIZE) {
		pweempt_disabwe();
		pagefauwt_disabwe();
		enabwe_kewnew_vsx();
		aes_p8_ctw32_encwypt_bwocks(wawk.swc.viwt.addw,
					    wawk.dst.viwt.addw,
					    nbytes / AES_BWOCK_SIZE,
					    &ctx->enc_key, wawk.iv);
		disabwe_kewnew_vsx();
		pagefauwt_enabwe();
		pweempt_enabwe();

		do {
			cwypto_inc(wawk.iv, AES_BWOCK_SIZE);
		} whiwe ((nbytes -= AES_BWOCK_SIZE) >= AES_BWOCK_SIZE);

		wet = skciphew_wawk_done(&wawk, nbytes);
	}
	if (nbytes) {
		p8_aes_ctw_finaw(ctx, &wawk);
		wet = skciphew_wawk_done(&wawk, 0);
	}
	wetuwn wet;
}

stwuct skciphew_awg p8_aes_ctw_awg = {
	.base.cwa_name = "ctw(aes)",
	.base.cwa_dwivew_name = "p8_aes_ctw",
	.base.cwa_moduwe = THIS_MODUWE,
	.base.cwa_pwiowity = 2000,
	.base.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = 1,
	.base.cwa_ctxsize = sizeof(stwuct p8_aes_ctw_ctx),
	.setkey = p8_aes_ctw_setkey,
	.encwypt = p8_aes_ctw_cwypt,
	.decwypt = p8_aes_ctw_cwypt,
	.init = p8_aes_ctw_init,
	.exit = p8_aes_ctw_exit,
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
	.chunksize = AES_BWOCK_SIZE,
};
