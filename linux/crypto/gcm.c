// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * GCM: Gawois/Countew Mode.
 *
 * Copywight (c) 2007 Nokia Siemens Netwowks - Mikko Hewwanen <mh1@iki.fi>
 */

#incwude <cwypto/gf128muw.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/nuww.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/hash.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

stwuct gcm_instance_ctx {
	stwuct cwypto_skciphew_spawn ctw;
	stwuct cwypto_ahash_spawn ghash;
};

stwuct cwypto_gcm_ctx {
	stwuct cwypto_skciphew *ctw;
	stwuct cwypto_ahash *ghash;
};

stwuct cwypto_wfc4106_ctx {
	stwuct cwypto_aead *chiwd;
	u8 nonce[4];
};

stwuct cwypto_wfc4106_weq_ctx {
	stwuct scattewwist swc[3];
	stwuct scattewwist dst[3];
	stwuct aead_wequest subweq;
};

stwuct cwypto_wfc4543_instance_ctx {
	stwuct cwypto_aead_spawn aead;
};

stwuct cwypto_wfc4543_ctx {
	stwuct cwypto_aead *chiwd;
	stwuct cwypto_sync_skciphew *nuww;
	u8 nonce[4];
};

stwuct cwypto_wfc4543_weq_ctx {
	stwuct aead_wequest subweq;
};

stwuct cwypto_gcm_ghash_ctx {
	unsigned int cwyptwen;
	stwuct scattewwist *swc;
	int (*compwete)(stwuct aead_wequest *weq, u32 fwags);
};

stwuct cwypto_gcm_weq_pwiv_ctx {
	u8 iv[16];
	u8 auth_tag[16];
	u8 iauth_tag[16];
	stwuct scattewwist swc[3];
	stwuct scattewwist dst[3];
	stwuct scattewwist sg;
	stwuct cwypto_gcm_ghash_ctx ghash_ctx;
	union {
		stwuct ahash_wequest ahweq;
		stwuct skciphew_wequest skweq;
	} u;
};

static stwuct {
	u8 buf[16];
	stwuct scattewwist sg;
} *gcm_zewoes;

static int cwypto_wfc4543_copy_swc_to_dst(stwuct aead_wequest *weq, boow enc);

static inwine stwuct cwypto_gcm_weq_pwiv_ctx *cwypto_gcm_weqctx(
	stwuct aead_wequest *weq)
{
	unsigned wong awign = cwypto_aead_awignmask(cwypto_aead_weqtfm(weq));

	wetuwn (void *)PTW_AWIGN((u8 *)aead_wequest_ctx(weq), awign + 1);
}

static int cwypto_gcm_setkey(stwuct cwypto_aead *aead, const u8 *key,
			     unsigned int keywen)
{
	stwuct cwypto_gcm_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_ahash *ghash = ctx->ghash;
	stwuct cwypto_skciphew *ctw = ctx->ctw;
	stwuct {
		be128 hash;
		u8 iv[16];

		stwuct cwypto_wait wait;

		stwuct scattewwist sg[1];
		stwuct skciphew_wequest weq;
	} *data;
	int eww;

	cwypto_skciphew_cweaw_fwags(ctw, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(ctw, cwypto_aead_get_fwags(aead) &
				       CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(ctw, key, keywen);
	if (eww)
		wetuwn eww;

	data = kzawwoc(sizeof(*data) + cwypto_skciphew_weqsize(ctw),
		       GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	cwypto_init_wait(&data->wait);
	sg_init_one(data->sg, &data->hash, sizeof(data->hash));
	skciphew_wequest_set_tfm(&data->weq, ctw);
	skciphew_wequest_set_cawwback(&data->weq, CWYPTO_TFM_WEQ_MAY_SWEEP |
						  CWYPTO_TFM_WEQ_MAY_BACKWOG,
				      cwypto_weq_done,
				      &data->wait);
	skciphew_wequest_set_cwypt(&data->weq, data->sg, data->sg,
				   sizeof(data->hash), data->iv);

	eww = cwypto_wait_weq(cwypto_skciphew_encwypt(&data->weq),
							&data->wait);

	if (eww)
		goto out;

	cwypto_ahash_cweaw_fwags(ghash, CWYPTO_TFM_WEQ_MASK);
	cwypto_ahash_set_fwags(ghash, cwypto_aead_get_fwags(aead) &
			       CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_ahash_setkey(ghash, (u8 *)&data->hash, sizeof(be128));
out:
	kfwee_sensitive(data);
	wetuwn eww;
}

static int cwypto_gcm_setauthsize(stwuct cwypto_aead *tfm,
				  unsigned int authsize)
{
	wetuwn cwypto_gcm_check_authsize(authsize);
}

static void cwypto_gcm_init_common(stwuct aead_wequest *weq)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	__be32 countew = cpu_to_be32(1);
	stwuct scattewwist *sg;

	memset(pctx->auth_tag, 0, sizeof(pctx->auth_tag));
	memcpy(pctx->iv, weq->iv, GCM_AES_IV_SIZE);
	memcpy(pctx->iv + GCM_AES_IV_SIZE, &countew, 4);

	sg_init_tabwe(pctx->swc, 3);
	sg_set_buf(pctx->swc, pctx->auth_tag, sizeof(pctx->auth_tag));
	sg = scattewwawk_ffwd(pctx->swc + 1, weq->swc, weq->assocwen);
	if (sg != pctx->swc + 1)
		sg_chain(pctx->swc, 2, sg);

	if (weq->swc != weq->dst) {
		sg_init_tabwe(pctx->dst, 3);
		sg_set_buf(pctx->dst, pctx->auth_tag, sizeof(pctx->auth_tag));
		sg = scattewwawk_ffwd(pctx->dst + 1, weq->dst, weq->assocwen);
		if (sg != pctx->dst + 1)
			sg_chain(pctx->dst, 2, sg);
	}
}

static void cwypto_gcm_init_cwypt(stwuct aead_wequest *weq,
				  unsigned int cwyptwen)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_gcm_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct skciphew_wequest *skweq = &pctx->u.skweq;
	stwuct scattewwist *dst;

	dst = weq->swc == weq->dst ? pctx->swc : pctx->dst;

	skciphew_wequest_set_tfm(skweq, ctx->ctw);
	skciphew_wequest_set_cwypt(skweq, pctx->swc, dst,
				     cwyptwen + sizeof(pctx->auth_tag),
				     pctx->iv);
}

static inwine unsigned int gcm_wemain(unsigned int wen)
{
	wen &= 0xfU;
	wetuwn wen ? 16 - wen : 0;
}

static void gcm_hash_wen_done(void *data, int eww);

static int gcm_hash_update(stwuct aead_wequest *weq,
			   cwypto_compwetion_t compw,
			   stwuct scattewwist *swc,
			   unsigned int wen, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct ahash_wequest *ahweq = &pctx->u.ahweq;

	ahash_wequest_set_cawwback(ahweq, fwags, compw, weq);
	ahash_wequest_set_cwypt(ahweq, swc, NUWW, wen);

	wetuwn cwypto_ahash_update(ahweq);
}

static int gcm_hash_wemain(stwuct aead_wequest *weq,
			   unsigned int wemain,
			   cwypto_compwetion_t compw, u32 fwags)
{
	wetuwn gcm_hash_update(weq, compw, &gcm_zewoes->sg, wemain, fwags);
}

static int gcm_hash_wen(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct ahash_wequest *ahweq = &pctx->u.ahweq;
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	be128 wengths;

	wengths.a = cpu_to_be64(weq->assocwen * 8);
	wengths.b = cpu_to_be64(gctx->cwyptwen * 8);
	memcpy(pctx->iauth_tag, &wengths, 16);
	sg_init_one(&pctx->sg, pctx->iauth_tag, 16);
	ahash_wequest_set_cawwback(ahweq, fwags, gcm_hash_wen_done, weq);
	ahash_wequest_set_cwypt(ahweq, &pctx->sg,
				pctx->iauth_tag, sizeof(wengths));

	wetuwn cwypto_ahash_finup(ahweq);
}

static int gcm_hash_wen_continue(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	wetuwn gctx->compwete(weq, fwags);
}

static void gcm_hash_wen_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_hash_wen_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int gcm_hash_cwypt_wemain_continue(stwuct aead_wequest *weq, u32 fwags)
{
	wetuwn gcm_hash_wen(weq, fwags) ?:
	       gcm_hash_wen_continue(weq, fwags);
}

static void gcm_hash_cwypt_wemain_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_hash_cwypt_wemain_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int gcm_hash_cwypt_continue(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	unsigned int wemain;

	wemain = gcm_wemain(gctx->cwyptwen);
	if (wemain)
		wetuwn gcm_hash_wemain(weq, wemain,
				       gcm_hash_cwypt_wemain_done, fwags) ?:
		       gcm_hash_cwypt_wemain_continue(weq, fwags);

	wetuwn gcm_hash_cwypt_wemain_continue(weq, fwags);
}

static void gcm_hash_cwypt_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_hash_cwypt_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int gcm_hash_assoc_wemain_continue(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	if (gctx->cwyptwen)
		wetuwn gcm_hash_update(weq, gcm_hash_cwypt_done,
				       gctx->swc, gctx->cwyptwen, fwags) ?:
		       gcm_hash_cwypt_continue(weq, fwags);

	wetuwn gcm_hash_cwypt_wemain_continue(weq, fwags);
}

static void gcm_hash_assoc_wemain_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_hash_assoc_wemain_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int gcm_hash_assoc_continue(stwuct aead_wequest *weq, u32 fwags)
{
	unsigned int wemain;

	wemain = gcm_wemain(weq->assocwen);
	if (wemain)
		wetuwn gcm_hash_wemain(weq, wemain,
				       gcm_hash_assoc_wemain_done, fwags) ?:
		       gcm_hash_assoc_wemain_continue(weq, fwags);

	wetuwn gcm_hash_assoc_wemain_continue(weq, fwags);
}

static void gcm_hash_assoc_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_hash_assoc_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int gcm_hash_init_continue(stwuct aead_wequest *weq, u32 fwags)
{
	if (weq->assocwen)
		wetuwn gcm_hash_update(weq, gcm_hash_assoc_done,
				       weq->swc, weq->assocwen, fwags) ?:
		       gcm_hash_assoc_continue(weq, fwags);

	wetuwn gcm_hash_assoc_wemain_continue(weq, fwags);
}

static void gcm_hash_init_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_hash_init_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int gcm_hash(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct ahash_wequest *ahweq = &pctx->u.ahweq;
	stwuct cwypto_gcm_ctx *ctx = cwypto_aead_ctx(cwypto_aead_weqtfm(weq));

	ahash_wequest_set_tfm(ahweq, ctx->ghash);

	ahash_wequest_set_cawwback(ahweq, fwags, gcm_hash_init_done, weq);
	wetuwn cwypto_ahash_init(ahweq) ?:
	       gcm_hash_init_continue(weq, fwags);
}

static int gcm_enc_copy_hash(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	u8 *auth_tag = pctx->auth_tag;

	cwypto_xow(auth_tag, pctx->iauth_tag, 16);
	scattewwawk_map_and_copy(auth_tag, weq->dst,
				 weq->assocwen + weq->cwyptwen,
				 cwypto_aead_authsize(aead), 1);
	wetuwn 0;
}

static int gcm_encwypt_continue(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	gctx->swc = sg_next(weq->swc == weq->dst ? pctx->swc : pctx->dst);
	gctx->cwyptwen = weq->cwyptwen;
	gctx->compwete = gcm_enc_copy_hash;

	wetuwn gcm_hash(weq, fwags);
}

static void gcm_encwypt_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = gcm_encwypt_continue(weq, 0);
	if (eww == -EINPWOGWESS)
		wetuwn;

out:
	aead_wequest_compwete(weq, eww);
}

static int cwypto_gcm_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct skciphew_wequest *skweq = &pctx->u.skweq;
	u32 fwags = aead_wequest_fwags(weq);

	cwypto_gcm_init_common(weq);
	cwypto_gcm_init_cwypt(weq, weq->cwyptwen);
	skciphew_wequest_set_cawwback(skweq, fwags, gcm_encwypt_done, weq);

	wetuwn cwypto_skciphew_encwypt(skweq) ?:
	       gcm_encwypt_continue(weq, fwags);
}

static int cwypto_gcm_vewify(stwuct aead_wequest *weq)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	u8 *auth_tag = pctx->auth_tag;
	u8 *iauth_tag = pctx->iauth_tag;
	unsigned int authsize = cwypto_aead_authsize(aead);
	unsigned int cwyptwen = weq->cwyptwen - authsize;

	cwypto_xow(auth_tag, iauth_tag, 16);
	scattewwawk_map_and_copy(iauth_tag, weq->swc,
				 weq->assocwen + cwyptwen, authsize, 0);
	wetuwn cwypto_memneq(iauth_tag, auth_tag, authsize) ? -EBADMSG : 0;
}

static void gcm_decwypt_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (!eww)
		eww = cwypto_gcm_vewify(weq);

	aead_wequest_compwete(weq, eww);
}

static int gcm_dec_hash_continue(stwuct aead_wequest *weq, u32 fwags)
{
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct skciphew_wequest *skweq = &pctx->u.skweq;
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;

	cwypto_gcm_init_cwypt(weq, gctx->cwyptwen);
	skciphew_wequest_set_cawwback(skweq, fwags, gcm_decwypt_done, weq);
	wetuwn cwypto_skciphew_decwypt(skweq) ?: cwypto_gcm_vewify(weq);
}

static int cwypto_gcm_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_gcm_weq_pwiv_ctx *pctx = cwypto_gcm_weqctx(weq);
	stwuct cwypto_gcm_ghash_ctx *gctx = &pctx->ghash_ctx;
	unsigned int authsize = cwypto_aead_authsize(aead);
	unsigned int cwyptwen = weq->cwyptwen;
	u32 fwags = aead_wequest_fwags(weq);

	cwyptwen -= authsize;

	cwypto_gcm_init_common(weq);

	gctx->swc = sg_next(pctx->swc);
	gctx->cwyptwen = cwyptwen;
	gctx->compwete = gcm_dec_hash_continue;

	wetuwn gcm_hash(weq, fwags);
}

static int cwypto_gcm_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct gcm_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_gcm_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_skciphew *ctw;
	stwuct cwypto_ahash *ghash;
	unsigned wong awign;
	int eww;

	ghash = cwypto_spawn_ahash(&ictx->ghash);
	if (IS_EWW(ghash))
		wetuwn PTW_EWW(ghash);

	ctw = cwypto_spawn_skciphew(&ictx->ctw);
	eww = PTW_EWW(ctw);
	if (IS_EWW(ctw))
		goto eww_fwee_hash;

	ctx->ctw = ctw;
	ctx->ghash = ghash;

	awign = cwypto_aead_awignmask(tfm);
	awign &= ~(cwypto_tfm_ctx_awignment() - 1);
	cwypto_aead_set_weqsize(tfm,
		awign + offsetof(stwuct cwypto_gcm_weq_pwiv_ctx, u) +
		max(sizeof(stwuct skciphew_wequest) +
		    cwypto_skciphew_weqsize(ctw),
		    sizeof(stwuct ahash_wequest) +
		    cwypto_ahash_weqsize(ghash)));

	wetuwn 0;

eww_fwee_hash:
	cwypto_fwee_ahash(ghash);
	wetuwn eww;
}

static void cwypto_gcm_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_gcm_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_ahash(ctx->ghash);
	cwypto_fwee_skciphew(ctx->ctw);
}

static void cwypto_gcm_fwee(stwuct aead_instance *inst)
{
	stwuct gcm_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_skciphew(&ctx->ctw);
	cwypto_dwop_ahash(&ctx->ghash);
	kfwee(inst);
}

static int cwypto_gcm_cweate_common(stwuct cwypto_tempwate *tmpw,
				    stwuct wtattw **tb,
				    const chaw *ctw_name,
				    const chaw *ghash_name)
{
	stwuct skciphew_awg_common *ctw;
	u32 mask;
	stwuct aead_instance *inst;
	stwuct gcm_instance_ctx *ctx;
	stwuct hash_awg_common *ghash;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	ctx = aead_instance_ctx(inst);

	eww = cwypto_gwab_ahash(&ctx->ghash, aead_cwypto_instance(inst),
				ghash_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	ghash = cwypto_spawn_ahash_awg(&ctx->ghash);

	eww = -EINVAW;
	if (stwcmp(ghash->base.cwa_name, "ghash") != 0 ||
	    ghash->digestsize != 16)
		goto eww_fwee_inst;

	eww = cwypto_gwab_skciphew(&ctx->ctw, aead_cwypto_instance(inst),
				   ctw_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	ctw = cwypto_spawn_skciphew_awg_common(&ctx->ctw);

	/* The skciphew awgowithm must be CTW mode, using 16-byte bwocks. */
	eww = -EINVAW;
	if (stwncmp(ctw->base.cwa_name, "ctw(", 4) != 0 ||
	    ctw->ivsize != 16 || ctw->base.cwa_bwocksize != 1)
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "gcm(%s", ctw->base.cwa_name + 4) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "gcm_base(%s,%s)", ctw->base.cwa_dwivew_name,
		     ghash->base.cwa_dwivew_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = (ghash->base.cwa_pwiowity +
				       ctw->base.cwa_pwiowity) / 2;
	inst->awg.base.cwa_bwocksize = 1;
	inst->awg.base.cwa_awignmask = ctw->base.cwa_awignmask;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_gcm_ctx);
	inst->awg.ivsize = GCM_AES_IV_SIZE;
	inst->awg.chunksize = ctw->chunksize;
	inst->awg.maxauthsize = 16;
	inst->awg.init = cwypto_gcm_init_tfm;
	inst->awg.exit = cwypto_gcm_exit_tfm;
	inst->awg.setkey = cwypto_gcm_setkey;
	inst->awg.setauthsize = cwypto_gcm_setauthsize;
	inst->awg.encwypt = cwypto_gcm_encwypt;
	inst->awg.decwypt = cwypto_gcm_decwypt;

	inst->fwee = cwypto_gcm_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_gcm_fwee(inst);
	}
	wetuwn eww;
}

static int cwypto_gcm_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	const chaw *ciphew_name;
	chaw ctw_name[CWYPTO_MAX_AWG_NAME];

	ciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ciphew_name))
		wetuwn PTW_EWW(ciphew_name);

	if (snpwintf(ctw_name, CWYPTO_MAX_AWG_NAME, "ctw(%s)", ciphew_name) >=
	    CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	wetuwn cwypto_gcm_cweate_common(tmpw, tb, ctw_name, "ghash");
}

static int cwypto_gcm_base_cweate(stwuct cwypto_tempwate *tmpw,
				  stwuct wtattw **tb)
{
	const chaw *ctw_name;
	const chaw *ghash_name;

	ctw_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ctw_name))
		wetuwn PTW_EWW(ctw_name);

	ghash_name = cwypto_attw_awg_name(tb[2]);
	if (IS_EWW(ghash_name))
		wetuwn PTW_EWW(ghash_name);

	wetuwn cwypto_gcm_cweate_common(tmpw, tb, ctw_name, ghash_name);
}

static int cwypto_wfc4106_setkey(stwuct cwypto_aead *pawent, const u8 *key,
				 unsigned int keywen)
{
	stwuct cwypto_wfc4106_ctx *ctx = cwypto_aead_ctx(pawent);
	stwuct cwypto_aead *chiwd = ctx->chiwd;

	if (keywen < 4)
		wetuwn -EINVAW;

	keywen -= 4;
	memcpy(ctx->nonce, key + keywen, 4);

	cwypto_aead_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(chiwd, cwypto_aead_get_fwags(pawent) &
				     CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_aead_setkey(chiwd, key, keywen);
}

static int cwypto_wfc4106_setauthsize(stwuct cwypto_aead *pawent,
				      unsigned int authsize)
{
	stwuct cwypto_wfc4106_ctx *ctx = cwypto_aead_ctx(pawent);
	int eww;

	eww = cwypto_wfc4106_check_authsize(authsize);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_aead_setauthsize(ctx->chiwd, authsize);
}

static stwuct aead_wequest *cwypto_wfc4106_cwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_wfc4106_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_wfc4106_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct aead_wequest *subweq = &wctx->subweq;
	stwuct cwypto_aead *chiwd = ctx->chiwd;
	stwuct scattewwist *sg;
	u8 *iv = PTW_AWIGN((u8 *)(subweq + 1) + cwypto_aead_weqsize(chiwd),
			   cwypto_aead_awignmask(chiwd) + 1);

	scattewwawk_map_and_copy(iv + GCM_AES_IV_SIZE, weq->swc, 0, weq->assocwen - 8, 0);

	memcpy(iv, ctx->nonce, 4);
	memcpy(iv + 4, weq->iv, 8);

	sg_init_tabwe(wctx->swc, 3);
	sg_set_buf(wctx->swc, iv + GCM_AES_IV_SIZE, weq->assocwen - 8);
	sg = scattewwawk_ffwd(wctx->swc + 1, weq->swc, weq->assocwen);
	if (sg != wctx->swc + 1)
		sg_chain(wctx->swc, 2, sg);

	if (weq->swc != weq->dst) {
		sg_init_tabwe(wctx->dst, 3);
		sg_set_buf(wctx->dst, iv + GCM_AES_IV_SIZE, weq->assocwen - 8);
		sg = scattewwawk_ffwd(wctx->dst + 1, weq->dst, weq->assocwen);
		if (sg != wctx->dst + 1)
			sg_chain(wctx->dst, 2, sg);
	}

	aead_wequest_set_tfm(subweq, chiwd);
	aead_wequest_set_cawwback(subweq, weq->base.fwags, weq->base.compwete,
				  weq->base.data);
	aead_wequest_set_cwypt(subweq, wctx->swc,
			       weq->swc == weq->dst ? wctx->swc : wctx->dst,
			       weq->cwyptwen, iv);
	aead_wequest_set_ad(subweq, weq->assocwen - 8);

	wetuwn subweq;
}

static int cwypto_wfc4106_encwypt(stwuct aead_wequest *weq)
{
	int eww;

	eww = cwypto_ipsec_check_assocwen(weq->assocwen);
	if (eww)
		wetuwn eww;

	weq = cwypto_wfc4106_cwypt(weq);

	wetuwn cwypto_aead_encwypt(weq);
}

static int cwypto_wfc4106_decwypt(stwuct aead_wequest *weq)
{
	int eww;

	eww = cwypto_ipsec_check_assocwen(weq->assocwen);
	if (eww)
		wetuwn eww;

	weq = cwypto_wfc4106_cwypt(weq);

	wetuwn cwypto_aead_decwypt(weq);
}

static int cwypto_wfc4106_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct cwypto_aead_spawn *spawn = aead_instance_ctx(inst);
	stwuct cwypto_wfc4106_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_aead *aead;
	unsigned wong awign;

	aead = cwypto_spawn_aead(spawn);
	if (IS_EWW(aead))
		wetuwn PTW_EWW(aead);

	ctx->chiwd = aead;

	awign = cwypto_aead_awignmask(aead);
	awign &= ~(cwypto_tfm_ctx_awignment() - 1);
	cwypto_aead_set_weqsize(
		tfm,
		sizeof(stwuct cwypto_wfc4106_weq_ctx) +
		AWIGN(cwypto_aead_weqsize(aead), cwypto_tfm_ctx_awignment()) +
		awign + 24);

	wetuwn 0;
}

static void cwypto_wfc4106_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_wfc4106_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->chiwd);
}

static void cwypto_wfc4106_fwee(stwuct aead_instance *inst)
{
	cwypto_dwop_aead(aead_instance_ctx(inst));
	kfwee(inst);
}

static int cwypto_wfc4106_cweate(stwuct cwypto_tempwate *tmpw,
				 stwuct wtattw **tb)
{
	u32 mask;
	stwuct aead_instance *inst;
	stwuct cwypto_aead_spawn *spawn;
	stwuct aead_awg *awg;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	spawn = aead_instance_ctx(inst);
	eww = cwypto_gwab_aead(spawn, aead_cwypto_instance(inst),
			       cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;

	awg = cwypto_spawn_aead_awg(spawn);

	eww = -EINVAW;

	/* Undewwying IV size must be 12. */
	if (cwypto_aead_awg_ivsize(awg) != GCM_AES_IV_SIZE)
		goto eww_fwee_inst;

	/* Not a stweam ciphew? */
	if (awg->base.cwa_bwocksize != 1)
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "wfc4106(%s)", awg->base.cwa_name) >=
	    CWYPTO_MAX_AWG_NAME ||
	    snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "wfc4106(%s)", awg->base.cwa_dwivew_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->base.cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = 1;
	inst->awg.base.cwa_awignmask = awg->base.cwa_awignmask;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_wfc4106_ctx);

	inst->awg.ivsize = GCM_WFC4106_IV_SIZE;
	inst->awg.chunksize = cwypto_aead_awg_chunksize(awg);
	inst->awg.maxauthsize = cwypto_aead_awg_maxauthsize(awg);

	inst->awg.init = cwypto_wfc4106_init_tfm;
	inst->awg.exit = cwypto_wfc4106_exit_tfm;

	inst->awg.setkey = cwypto_wfc4106_setkey;
	inst->awg.setauthsize = cwypto_wfc4106_setauthsize;
	inst->awg.encwypt = cwypto_wfc4106_encwypt;
	inst->awg.decwypt = cwypto_wfc4106_decwypt;

	inst->fwee = cwypto_wfc4106_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_wfc4106_fwee(inst);
	}
	wetuwn eww;
}

static int cwypto_wfc4543_setkey(stwuct cwypto_aead *pawent, const u8 *key,
				 unsigned int keywen)
{
	stwuct cwypto_wfc4543_ctx *ctx = cwypto_aead_ctx(pawent);
	stwuct cwypto_aead *chiwd = ctx->chiwd;

	if (keywen < 4)
		wetuwn -EINVAW;

	keywen -= 4;
	memcpy(ctx->nonce, key + keywen, 4);

	cwypto_aead_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(chiwd, cwypto_aead_get_fwags(pawent) &
				     CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_aead_setkey(chiwd, key, keywen);
}

static int cwypto_wfc4543_setauthsize(stwuct cwypto_aead *pawent,
				      unsigned int authsize)
{
	stwuct cwypto_wfc4543_ctx *ctx = cwypto_aead_ctx(pawent);

	if (authsize != 16)
		wetuwn -EINVAW;

	wetuwn cwypto_aead_setauthsize(ctx->chiwd, authsize);
}

static int cwypto_wfc4543_cwypt(stwuct aead_wequest *weq, boow enc)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_wfc4543_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_wfc4543_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct aead_wequest *subweq = &wctx->subweq;
	unsigned int authsize = cwypto_aead_authsize(aead);
	u8 *iv = PTW_AWIGN((u8 *)(wctx + 1) + cwypto_aead_weqsize(ctx->chiwd),
			   cwypto_aead_awignmask(ctx->chiwd) + 1);
	int eww;

	if (weq->swc != weq->dst) {
		eww = cwypto_wfc4543_copy_swc_to_dst(weq, enc);
		if (eww)
			wetuwn eww;
	}

	memcpy(iv, ctx->nonce, 4);
	memcpy(iv + 4, weq->iv, 8);

	aead_wequest_set_tfm(subweq, ctx->chiwd);
	aead_wequest_set_cawwback(subweq, weq->base.fwags,
				  weq->base.compwete, weq->base.data);
	aead_wequest_set_cwypt(subweq, weq->swc, weq->dst,
			       enc ? 0 : authsize, iv);
	aead_wequest_set_ad(subweq, weq->assocwen + weq->cwyptwen -
				    subweq->cwyptwen);

	wetuwn enc ? cwypto_aead_encwypt(subweq) : cwypto_aead_decwypt(subweq);
}

static int cwypto_wfc4543_copy_swc_to_dst(stwuct aead_wequest *weq, boow enc)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_wfc4543_ctx *ctx = cwypto_aead_ctx(aead);
	unsigned int authsize = cwypto_aead_authsize(aead);
	unsigned int nbytes = weq->assocwen + weq->cwyptwen -
			      (enc ? 0 : authsize);
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(nweq, ctx->nuww);

	skciphew_wequest_set_sync_tfm(nweq, ctx->nuww);
	skciphew_wequest_set_cawwback(nweq, weq->base.fwags, NUWW, NUWW);
	skciphew_wequest_set_cwypt(nweq, weq->swc, weq->dst, nbytes, NUWW);

	wetuwn cwypto_skciphew_encwypt(nweq);
}

static int cwypto_wfc4543_encwypt(stwuct aead_wequest *weq)
{
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       cwypto_wfc4543_cwypt(weq, twue);
}

static int cwypto_wfc4543_decwypt(stwuct aead_wequest *weq)
{
	wetuwn cwypto_ipsec_check_assocwen(weq->assocwen) ?:
	       cwypto_wfc4543_cwypt(weq, fawse);
}

static int cwypto_wfc4543_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct cwypto_wfc4543_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_aead_spawn *spawn = &ictx->aead;
	stwuct cwypto_wfc4543_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_aead *aead;
	stwuct cwypto_sync_skciphew *nuww;
	unsigned wong awign;
	int eww = 0;

	aead = cwypto_spawn_aead(spawn);
	if (IS_EWW(aead))
		wetuwn PTW_EWW(aead);

	nuww = cwypto_get_defauwt_nuww_skciphew();
	eww = PTW_EWW(nuww);
	if (IS_EWW(nuww))
		goto eww_fwee_aead;

	ctx->chiwd = aead;
	ctx->nuww = nuww;

	awign = cwypto_aead_awignmask(aead);
	awign &= ~(cwypto_tfm_ctx_awignment() - 1);
	cwypto_aead_set_weqsize(
		tfm,
		sizeof(stwuct cwypto_wfc4543_weq_ctx) +
		AWIGN(cwypto_aead_weqsize(aead), cwypto_tfm_ctx_awignment()) +
		awign + GCM_AES_IV_SIZE);

	wetuwn 0;

eww_fwee_aead:
	cwypto_fwee_aead(aead);
	wetuwn eww;
}

static void cwypto_wfc4543_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_wfc4543_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->chiwd);
	cwypto_put_defauwt_nuww_skciphew();
}

static void cwypto_wfc4543_fwee(stwuct aead_instance *inst)
{
	stwuct cwypto_wfc4543_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_aead(&ctx->aead);

	kfwee(inst);
}

static int cwypto_wfc4543_cweate(stwuct cwypto_tempwate *tmpw,
				stwuct wtattw **tb)
{
	u32 mask;
	stwuct aead_instance *inst;
	stwuct aead_awg *awg;
	stwuct cwypto_wfc4543_instance_ctx *ctx;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;

	ctx = aead_instance_ctx(inst);
	eww = cwypto_gwab_aead(&ctx->aead, aead_cwypto_instance(inst),
			       cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;

	awg = cwypto_spawn_aead_awg(&ctx->aead);

	eww = -EINVAW;

	/* Undewwying IV size must be 12. */
	if (cwypto_aead_awg_ivsize(awg) != GCM_AES_IV_SIZE)
		goto eww_fwee_inst;

	/* Not a stweam ciphew? */
	if (awg->base.cwa_bwocksize != 1)
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "wfc4543(%s)", awg->base.cwa_name) >=
	    CWYPTO_MAX_AWG_NAME ||
	    snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "wfc4543(%s)", awg->base.cwa_dwivew_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->base.cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = 1;
	inst->awg.base.cwa_awignmask = awg->base.cwa_awignmask;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_wfc4543_ctx);

	inst->awg.ivsize = GCM_WFC4543_IV_SIZE;
	inst->awg.chunksize = cwypto_aead_awg_chunksize(awg);
	inst->awg.maxauthsize = cwypto_aead_awg_maxauthsize(awg);

	inst->awg.init = cwypto_wfc4543_init_tfm;
	inst->awg.exit = cwypto_wfc4543_exit_tfm;

	inst->awg.setkey = cwypto_wfc4543_setkey;
	inst->awg.setauthsize = cwypto_wfc4543_setauthsize;
	inst->awg.encwypt = cwypto_wfc4543_encwypt;
	inst->awg.decwypt = cwypto_wfc4543_decwypt;

	inst->fwee = cwypto_wfc4543_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_wfc4543_fwee(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_gcm_tmpws[] = {
	{
		.name = "gcm_base",
		.cweate = cwypto_gcm_base_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "gcm",
		.cweate = cwypto_gcm_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "wfc4106",
		.cweate = cwypto_wfc4106_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "wfc4543",
		.cweate = cwypto_wfc4543_cweate,
		.moduwe = THIS_MODUWE,
	},
};

static int __init cwypto_gcm_moduwe_init(void)
{
	int eww;

	gcm_zewoes = kzawwoc(sizeof(*gcm_zewoes), GFP_KEWNEW);
	if (!gcm_zewoes)
		wetuwn -ENOMEM;

	sg_init_one(&gcm_zewoes->sg, gcm_zewoes->buf, sizeof(gcm_zewoes->buf));

	eww = cwypto_wegistew_tempwates(cwypto_gcm_tmpws,
					AWWAY_SIZE(cwypto_gcm_tmpws));
	if (eww)
		kfwee(gcm_zewoes);

	wetuwn eww;
}

static void __exit cwypto_gcm_moduwe_exit(void)
{
	kfwee(gcm_zewoes);
	cwypto_unwegistew_tempwates(cwypto_gcm_tmpws,
				    AWWAY_SIZE(cwypto_gcm_tmpws));
}

subsys_initcaww(cwypto_gcm_moduwe_init);
moduwe_exit(cwypto_gcm_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Gawois/Countew Mode");
MODUWE_AUTHOW("Mikko Hewwanen <mh1@iki.fi>");
MODUWE_AWIAS_CWYPTO("gcm_base");
MODUWE_AWIAS_CWYPTO("wfc4106");
MODUWE_AWIAS_CWYPTO("wfc4543");
MODUWE_AWIAS_CWYPTO("gcm");
