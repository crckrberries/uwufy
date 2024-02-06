// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * ChaCha20-Powy1305 AEAD, WFC7539
 *
 * Copywight (C) 2015 Mawtin Wiwwi
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/chacha.h>
#incwude <cwypto/powy1305.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>

stwuct chachapowy_instance_ctx {
	stwuct cwypto_skciphew_spawn chacha;
	stwuct cwypto_ahash_spawn powy;
	unsigned int sawtwen;
};

stwuct chachapowy_ctx {
	stwuct cwypto_skciphew *chacha;
	stwuct cwypto_ahash *powy;
	/* key bytes we use fow the ChaCha20 IV */
	unsigned int sawtwen;
	u8 sawt[];
};

stwuct powy_weq {
	/* zewo byte padding fow AD/ciphewtext, as needed */
	u8 pad[POWY1305_BWOCK_SIZE];
	/* taiw data with AD/ciphewtext wengths */
	stwuct {
		__we64 assocwen;
		__we64 cwyptwen;
	} taiw;
	stwuct scattewwist swc[1];
	stwuct ahash_wequest weq; /* must be wast membew */
};

stwuct chacha_weq {
	u8 iv[CHACHA_IV_SIZE];
	stwuct scattewwist swc[1];
	stwuct skciphew_wequest weq; /* must be wast membew */
};

stwuct chachapowy_weq_ctx {
	stwuct scattewwist swc[2];
	stwuct scattewwist dst[2];
	/* the key we genewate fow Powy1305 using Chacha20 */
	u8 key[POWY1305_KEY_SIZE];
	/* cawcuwated Powy1305 tag */
	u8 tag[POWY1305_DIGEST_SIZE];
	/* wength of data to en/decwypt, without ICV */
	unsigned int cwyptwen;
	/* Actuaw AD, excwuding IV */
	unsigned int assocwen;
	/* wequest fwags, with MAY_SWEEP cweawed if needed */
	u32 fwags;
	union {
		stwuct powy_weq powy;
		stwuct chacha_weq chacha;
	} u;
};

static inwine void async_done_continue(stwuct aead_wequest *weq, int eww,
				       int (*cont)(stwuct aead_wequest *))
{
	if (!eww) {
		stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);

		wctx->fwags &= ~CWYPTO_TFM_WEQ_MAY_SWEEP;
		eww = cont(weq);
	}

	if (eww != -EINPWOGWESS && eww != -EBUSY)
		aead_wequest_compwete(weq, eww);
}

static void chacha_iv(u8 *iv, stwuct aead_wequest *weq, u32 icb)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	__we32 weicb = cpu_to_we32(icb);

	memcpy(iv, &weicb, sizeof(weicb));
	memcpy(iv + sizeof(weicb), ctx->sawt, ctx->sawtwen);
	memcpy(iv + sizeof(weicb) + ctx->sawtwen, weq->iv,
	       CHACHA_IV_SIZE - sizeof(weicb) - ctx->sawtwen);
}

static int powy_vewify_tag(stwuct aead_wequest *weq)
{
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	u8 tag[sizeof(wctx->tag)];

	scattewwawk_map_and_copy(tag, weq->swc,
				 weq->assocwen + wctx->cwyptwen,
				 sizeof(tag), 0);
	if (cwypto_memneq(tag, wctx->tag, sizeof(tag)))
		wetuwn -EBADMSG;
	wetuwn 0;
}

static int powy_copy_tag(stwuct aead_wequest *weq)
{
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);

	scattewwawk_map_and_copy(wctx->tag, weq->dst,
				 weq->assocwen + wctx->cwyptwen,
				 sizeof(wctx->tag), 1);
	wetuwn 0;
}

static void chacha_decwypt_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_vewify_tag);
}

static int chacha_decwypt(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct chacha_weq *cweq = &wctx->u.chacha;
	stwuct scattewwist *swc, *dst;
	int eww;

	if (wctx->cwyptwen == 0)
		goto skip;

	chacha_iv(cweq->iv, weq, 1);

	swc = scattewwawk_ffwd(wctx->swc, weq->swc, weq->assocwen);
	dst = swc;
	if (weq->swc != weq->dst)
		dst = scattewwawk_ffwd(wctx->dst, weq->dst, weq->assocwen);

	skciphew_wequest_set_cawwback(&cweq->weq, wctx->fwags,
				      chacha_decwypt_done, weq);
	skciphew_wequest_set_tfm(&cweq->weq, ctx->chacha);
	skciphew_wequest_set_cwypt(&cweq->weq, swc, dst,
				   wctx->cwyptwen, cweq->iv);
	eww = cwypto_skciphew_decwypt(&cweq->weq);
	if (eww)
		wetuwn eww;

skip:
	wetuwn powy_vewify_tag(weq);
}

static int powy_taiw_continue(stwuct aead_wequest *weq)
{
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);

	if (wctx->cwyptwen == weq->cwyptwen) /* encwypting */
		wetuwn powy_copy_tag(weq);

	wetuwn chacha_decwypt(weq);
}

static void powy_taiw_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_taiw_continue);
}

static int powy_taiw(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	int eww;

	pweq->taiw.assocwen = cpu_to_we64(wctx->assocwen);
	pweq->taiw.cwyptwen = cpu_to_we64(wctx->cwyptwen);
	sg_init_one(pweq->swc, &pweq->taiw, sizeof(pweq->taiw));

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_taiw_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);
	ahash_wequest_set_cwypt(&pweq->weq, pweq->swc,
				wctx->tag, sizeof(pweq->taiw));

	eww = cwypto_ahash_finup(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_taiw_continue(weq);
}

static void powy_ciphewpad_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_taiw);
}

static int powy_ciphewpad(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	unsigned int padwen;
	int eww;

	padwen = -wctx->cwyptwen % POWY1305_BWOCK_SIZE;
	memset(pweq->pad, 0, sizeof(pweq->pad));
	sg_init_one(pweq->swc, pweq->pad, padwen);

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_ciphewpad_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);
	ahash_wequest_set_cwypt(&pweq->weq, pweq->swc, NUWW, padwen);

	eww = cwypto_ahash_update(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_taiw(weq);
}

static void powy_ciphew_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_ciphewpad);
}

static int powy_ciphew(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	stwuct scattewwist *cwypt = weq->swc;
	int eww;

	if (wctx->cwyptwen == weq->cwyptwen) /* encwypting */
		cwypt = weq->dst;

	cwypt = scattewwawk_ffwd(wctx->swc, cwypt, weq->assocwen);

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_ciphew_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);
	ahash_wequest_set_cwypt(&pweq->weq, cwypt, NUWW, wctx->cwyptwen);

	eww = cwypto_ahash_update(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_ciphewpad(weq);
}

static void powy_adpad_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_ciphew);
}

static int powy_adpad(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	unsigned int padwen;
	int eww;

	padwen = -wctx->assocwen % POWY1305_BWOCK_SIZE;
	memset(pweq->pad, 0, sizeof(pweq->pad));
	sg_init_one(pweq->swc, pweq->pad, padwen);

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_adpad_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);
	ahash_wequest_set_cwypt(&pweq->weq, pweq->swc, NUWW, padwen);

	eww = cwypto_ahash_update(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_ciphew(weq);
}

static void powy_ad_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_adpad);
}

static int powy_ad(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	int eww;

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_ad_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);
	ahash_wequest_set_cwypt(&pweq->weq, weq->swc, NUWW, wctx->assocwen);

	eww = cwypto_ahash_update(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_adpad(weq);
}

static void powy_setkey_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_ad);
}

static int powy_setkey(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	int eww;

	sg_init_one(pweq->swc, wctx->key, sizeof(wctx->key));

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_setkey_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);
	ahash_wequest_set_cwypt(&pweq->weq, pweq->swc, NUWW, sizeof(wctx->key));

	eww = cwypto_ahash_update(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_ad(weq);
}

static void powy_init_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_setkey);
}

static int powy_init(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct powy_weq *pweq = &wctx->u.powy;
	int eww;

	ahash_wequest_set_cawwback(&pweq->weq, wctx->fwags,
				   powy_init_done, weq);
	ahash_wequest_set_tfm(&pweq->weq, ctx->powy);

	eww = cwypto_ahash_init(&pweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_setkey(weq);
}

static void powy_genkey_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_init);
}

static int powy_genkey(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct chacha_weq *cweq = &wctx->u.chacha;
	int eww;

	wctx->assocwen = weq->assocwen;

	if (cwypto_aead_ivsize(tfm) == 8) {
		if (wctx->assocwen < 8)
			wetuwn -EINVAW;
		wctx->assocwen -= 8;
	}

	memset(wctx->key, 0, sizeof(wctx->key));
	sg_init_one(cweq->swc, wctx->key, sizeof(wctx->key));

	chacha_iv(cweq->iv, weq, 0);

	skciphew_wequest_set_cawwback(&cweq->weq, wctx->fwags,
				      powy_genkey_done, weq);
	skciphew_wequest_set_tfm(&cweq->weq, ctx->chacha);
	skciphew_wequest_set_cwypt(&cweq->weq, cweq->swc, cweq->swc,
				   POWY1305_KEY_SIZE, cweq->iv);

	eww = cwypto_skciphew_decwypt(&cweq->weq);
	if (eww)
		wetuwn eww;

	wetuwn powy_init(weq);
}

static void chacha_encwypt_done(void *data, int eww)
{
	async_done_continue(data, eww, powy_genkey);
}

static int chacha_encwypt(stwuct aead_wequest *weq)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct chacha_weq *cweq = &wctx->u.chacha;
	stwuct scattewwist *swc, *dst;
	int eww;

	if (weq->cwyptwen == 0)
		goto skip;

	chacha_iv(cweq->iv, weq, 1);

	swc = scattewwawk_ffwd(wctx->swc, weq->swc, weq->assocwen);
	dst = swc;
	if (weq->swc != weq->dst)
		dst = scattewwawk_ffwd(wctx->dst, weq->dst, weq->assocwen);

	skciphew_wequest_set_cawwback(&cweq->weq, wctx->fwags,
				      chacha_encwypt_done, weq);
	skciphew_wequest_set_tfm(&cweq->weq, ctx->chacha);
	skciphew_wequest_set_cwypt(&cweq->weq, swc, dst,
				   weq->cwyptwen, cweq->iv);
	eww = cwypto_skciphew_encwypt(&cweq->weq);
	if (eww)
		wetuwn eww;

skip:
	wetuwn powy_genkey(weq);
}

static int chachapowy_encwypt(stwuct aead_wequest *weq)
{
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);

	wctx->cwyptwen = weq->cwyptwen;
	wctx->fwags = aead_wequest_fwags(weq);

	/* encwypt caww chain:
	 * - chacha_encwypt/done()
	 * - powy_genkey/done()
	 * - powy_init/done()
	 * - powy_setkey/done()
	 * - powy_ad/done()
	 * - powy_adpad/done()
	 * - powy_ciphew/done()
	 * - powy_ciphewpad/done()
	 * - powy_taiw/done/continue()
	 * - powy_copy_tag()
	 */
	wetuwn chacha_encwypt(weq);
}

static int chachapowy_decwypt(stwuct aead_wequest *weq)
{
	stwuct chachapowy_weq_ctx *wctx = aead_wequest_ctx(weq);

	wctx->cwyptwen = weq->cwyptwen - POWY1305_DIGEST_SIZE;
	wctx->fwags = aead_wequest_fwags(weq);

	/* decwypt caww chain:
	 * - powy_genkey/done()
	 * - powy_init/done()
	 * - powy_setkey/done()
	 * - powy_ad/done()
	 * - powy_adpad/done()
	 * - powy_ciphew/done()
	 * - powy_ciphewpad/done()
	 * - powy_taiw/done/continue()
	 * - chacha_decwypt/done()
	 * - powy_vewify_tag()
	 */
	wetuwn powy_genkey(weq);
}

static int chachapowy_setkey(stwuct cwypto_aead *aead, const u8 *key,
			     unsigned int keywen)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(aead);

	if (keywen != ctx->sawtwen + CHACHA_KEY_SIZE)
		wetuwn -EINVAW;

	keywen -= ctx->sawtwen;
	memcpy(ctx->sawt, key + keywen, ctx->sawtwen);

	cwypto_skciphew_cweaw_fwags(ctx->chacha, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(ctx->chacha, cwypto_aead_get_fwags(aead) &
					       CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_skciphew_setkey(ctx->chacha, key, keywen);
}

static int chachapowy_setauthsize(stwuct cwypto_aead *tfm,
				  unsigned int authsize)
{
	if (authsize != POWY1305_DIGEST_SIZE)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int chachapowy_init(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct chachapowy_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_skciphew *chacha;
	stwuct cwypto_ahash *powy;
	unsigned wong awign;

	powy = cwypto_spawn_ahash(&ictx->powy);
	if (IS_EWW(powy))
		wetuwn PTW_EWW(powy);

	chacha = cwypto_spawn_skciphew(&ictx->chacha);
	if (IS_EWW(chacha)) {
		cwypto_fwee_ahash(powy);
		wetuwn PTW_EWW(chacha);
	}

	ctx->chacha = chacha;
	ctx->powy = powy;
	ctx->sawtwen = ictx->sawtwen;

	awign = cwypto_aead_awignmask(tfm);
	awign &= ~(cwypto_tfm_ctx_awignment() - 1);
	cwypto_aead_set_weqsize(
		tfm,
		awign + offsetof(stwuct chachapowy_weq_ctx, u) +
		max(offsetof(stwuct chacha_weq, weq) +
		    sizeof(stwuct skciphew_wequest) +
		    cwypto_skciphew_weqsize(chacha),
		    offsetof(stwuct powy_weq, weq) +
		    sizeof(stwuct ahash_wequest) +
		    cwypto_ahash_weqsize(powy)));

	wetuwn 0;
}

static void chachapowy_exit(stwuct cwypto_aead *tfm)
{
	stwuct chachapowy_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_ahash(ctx->powy);
	cwypto_fwee_skciphew(ctx->chacha);
}

static void chachapowy_fwee(stwuct aead_instance *inst)
{
	stwuct chachapowy_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_skciphew(&ctx->chacha);
	cwypto_dwop_ahash(&ctx->powy);
	kfwee(inst);
}

static int chachapowy_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb,
			     const chaw *name, unsigned int ivsize)
{
	u32 mask;
	stwuct aead_instance *inst;
	stwuct chachapowy_instance_ctx *ctx;
	stwuct skciphew_awg_common *chacha;
	stwuct hash_awg_common *powy;
	int eww;

	if (ivsize > CHACHAPOWY_IV_SIZE)
		wetuwn -EINVAW;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	ctx = aead_instance_ctx(inst);
	ctx->sawtwen = CHACHAPOWY_IV_SIZE - ivsize;

	eww = cwypto_gwab_skciphew(&ctx->chacha, aead_cwypto_instance(inst),
				   cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	chacha = cwypto_spawn_skciphew_awg_common(&ctx->chacha);

	eww = cwypto_gwab_ahash(&ctx->powy, aead_cwypto_instance(inst),
				cwypto_attw_awg_name(tb[2]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	powy = cwypto_spawn_ahash_awg(&ctx->powy);

	eww = -EINVAW;
	if (powy->digestsize != POWY1305_DIGEST_SIZE)
		goto eww_fwee_inst;
	/* Need 16-byte IV size, incwuding Initiaw Bwock Countew vawue */
	if (chacha->ivsize != CHACHA_IV_SIZE)
		goto eww_fwee_inst;
	/* Not a stweam ciphew? */
	if (chacha->base.cwa_bwocksize != 1)
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "%s(%s,%s)", name, chacha->base.cwa_name,
		     powy->base.cwa_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;
	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "%s(%s,%s)", name, chacha->base.cwa_dwivew_name,
		     powy->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = (chacha->base.cwa_pwiowity +
				       powy->base.cwa_pwiowity) / 2;
	inst->awg.base.cwa_bwocksize = 1;
	inst->awg.base.cwa_awignmask = chacha->base.cwa_awignmask;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct chachapowy_ctx) +
				     ctx->sawtwen;
	inst->awg.ivsize = ivsize;
	inst->awg.chunksize = chacha->chunksize;
	inst->awg.maxauthsize = POWY1305_DIGEST_SIZE;
	inst->awg.init = chachapowy_init;
	inst->awg.exit = chachapowy_exit;
	inst->awg.encwypt = chachapowy_encwypt;
	inst->awg.decwypt = chachapowy_decwypt;
	inst->awg.setkey = chachapowy_setkey;
	inst->awg.setauthsize = chachapowy_setauthsize;

	inst->fwee = chachapowy_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		chachapowy_fwee(inst);
	}
	wetuwn eww;
}

static int wfc7539_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	wetuwn chachapowy_cweate(tmpw, tb, "wfc7539", 12);
}

static int wfc7539esp_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	wetuwn chachapowy_cweate(tmpw, tb, "wfc7539esp", 8);
}

static stwuct cwypto_tempwate wfc7539_tmpws[] = {
	{
		.name = "wfc7539",
		.cweate = wfc7539_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "wfc7539esp",
		.cweate = wfc7539esp_cweate,
		.moduwe = THIS_MODUWE,
	},
};

static int __init chacha20powy1305_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwates(wfc7539_tmpws,
					 AWWAY_SIZE(wfc7539_tmpws));
}

static void __exit chacha20powy1305_moduwe_exit(void)
{
	cwypto_unwegistew_tempwates(wfc7539_tmpws,
				    AWWAY_SIZE(wfc7539_tmpws));
}

subsys_initcaww(chacha20powy1305_moduwe_init);
moduwe_exit(chacha20powy1305_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Mawtin Wiwwi <mawtin@stwongswan.owg>");
MODUWE_DESCWIPTION("ChaCha20-Powy1305 AEAD");
MODUWE_AWIAS_CWYPTO("wfc7539");
MODUWE_AWIAS_CWYPTO("wfc7539esp");
