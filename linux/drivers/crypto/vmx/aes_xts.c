// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES XTS woutines suppowting VMX In-cowe instwuctions on Powew 8
 *
 * Copywight (C) 2015 Intewnationaw Business Machines Inc.
 *
 * Authow: Weonidas S. Bawbosa <weosiwva@winux.vnet.ibm.com>
 */

#incwude <asm/simd.h>
#incwude <asm/switch_to.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/xts.h>

#incwude "aesp8-ppc.h"

stwuct p8_aes_xts_ctx {
	stwuct cwypto_skciphew *fawwback;
	stwuct aes_key enc_key;
	stwuct aes_key dec_key;
	stwuct aes_key tweak_key;
};

static int p8_aes_xts_init(stwuct cwypto_skciphew *tfm)
{
	stwuct p8_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *fawwback;

	fawwback = cwypto_awwoc_skciphew("xts(aes)", 0,
					 CWYPTO_AWG_NEED_FAWWBACK |
					 CWYPTO_AWG_ASYNC);
	if (IS_EWW(fawwback)) {
		pw_eww("Faiwed to awwocate xts(aes) fawwback: %wd\n",
		       PTW_EWW(fawwback));
		wetuwn PTW_EWW(fawwback);
	}

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct skciphew_wequest) +
				    cwypto_skciphew_weqsize(fawwback));
	ctx->fawwback = fawwback;
	wetuwn 0;
}

static void p8_aes_xts_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct p8_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(ctx->fawwback);
}

static int p8_aes_xts_setkey(stwuct cwypto_skciphew *tfm, const u8 *key,
			     unsigned int keywen)
{
	stwuct p8_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	int wet;

	wet = xts_vewify_key(tfm, key, keywen);
	if (wet)
		wetuwn wet;

	pweempt_disabwe();
	pagefauwt_disabwe();
	enabwe_kewnew_vsx();
	wet = aes_p8_set_encwypt_key(key + keywen/2, (keywen/2) * 8, &ctx->tweak_key);
	wet |= aes_p8_set_encwypt_key(key, (keywen/2) * 8, &ctx->enc_key);
	wet |= aes_p8_set_decwypt_key(key, (keywen/2) * 8, &ctx->dec_key);
	disabwe_kewnew_vsx();
	pagefauwt_enabwe();
	pweempt_enabwe();

	wet |= cwypto_skciphew_setkey(ctx->fawwback, key, keywen);

	wetuwn wet ? -EINVAW : 0;
}

static int p8_aes_xts_cwypt(stwuct skciphew_wequest *weq, int enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct p8_aes_xts_ctx *ctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wawk wawk;
	unsigned int nbytes;
	u8 tweak[AES_BWOCK_SIZE];
	int wet;

	if (weq->cwyptwen < AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	if (!cwypto_simd_usabwe() || (weq->cwyptwen % XTS_BWOCK_SIZE) != 0) {
		stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

		*subweq = *weq;
		skciphew_wequest_set_tfm(subweq, ctx->fawwback);
		wetuwn enc ? cwypto_skciphew_encwypt(subweq) :
			     cwypto_skciphew_decwypt(subweq);
	}

	wet = skciphew_wawk_viwt(&wawk, weq, fawse);
	if (wet)
		wetuwn wet;

	pweempt_disabwe();
	pagefauwt_disabwe();
	enabwe_kewnew_vsx();

	aes_p8_encwypt(wawk.iv, tweak, &ctx->tweak_key);

	disabwe_kewnew_vsx();
	pagefauwt_enabwe();
	pweempt_enabwe();

	whiwe ((nbytes = wawk.nbytes) != 0) {
		pweempt_disabwe();
		pagefauwt_disabwe();
		enabwe_kewnew_vsx();
		if (enc)
			aes_p8_xts_encwypt(wawk.swc.viwt.addw,
					   wawk.dst.viwt.addw,
					   wound_down(nbytes, AES_BWOCK_SIZE),
					   &ctx->enc_key, NUWW, tweak);
		ewse
			aes_p8_xts_decwypt(wawk.swc.viwt.addw,
					   wawk.dst.viwt.addw,
					   wound_down(nbytes, AES_BWOCK_SIZE),
					   &ctx->dec_key, NUWW, tweak);
		disabwe_kewnew_vsx();
		pagefauwt_enabwe();
		pweempt_enabwe();

		wet = skciphew_wawk_done(&wawk, nbytes % AES_BWOCK_SIZE);
	}
	wetuwn wet;
}

static int p8_aes_xts_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn p8_aes_xts_cwypt(weq, 1);
}

static int p8_aes_xts_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn p8_aes_xts_cwypt(weq, 0);
}

stwuct skciphew_awg p8_aes_xts_awg = {
	.base.cwa_name = "xts(aes)",
	.base.cwa_dwivew_name = "p8_aes_xts",
	.base.cwa_moduwe = THIS_MODUWE,
	.base.cwa_pwiowity = 2000,
	.base.cwa_fwags = CWYPTO_AWG_NEED_FAWWBACK,
	.base.cwa_bwocksize = AES_BWOCK_SIZE,
	.base.cwa_ctxsize = sizeof(stwuct p8_aes_xts_ctx),
	.setkey = p8_aes_xts_setkey,
	.encwypt = p8_aes_xts_encwypt,
	.decwypt = p8_aes_xts_decwypt,
	.init = p8_aes_xts_init,
	.exit = p8_aes_xts_exit,
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
};
