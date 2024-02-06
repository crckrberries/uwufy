// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * authencesn.c - AEAD wwappew fow IPsec with extended sequence numbews,
 *                 dewived fwom authenc.c
 *
 * Copywight (C) 2010 secunet Secuwity Netwowks AG
 * Copywight (C) 2010 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 * Copywight (c) 2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/authenc.h>
#incwude <cwypto/nuww.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/wtnetwink.h>
#incwude <winux/swab.h>
#incwude <winux/spinwock.h>

stwuct authenc_esn_instance_ctx {
	stwuct cwypto_ahash_spawn auth;
	stwuct cwypto_skciphew_spawn enc;
};

stwuct cwypto_authenc_esn_ctx {
	unsigned int weqoff;
	stwuct cwypto_ahash *auth;
	stwuct cwypto_skciphew *enc;
	stwuct cwypto_sync_skciphew *nuww;
};

stwuct authenc_esn_wequest_ctx {
	stwuct scattewwist swc[2];
	stwuct scattewwist dst[2];
	chaw taiw[];
};

static void authenc_esn_wequest_compwete(stwuct aead_wequest *weq, int eww)
{
	if (eww != -EINPWOGWESS)
		aead_wequest_compwete(weq, eww);
}

static int cwypto_authenc_esn_setauthsize(stwuct cwypto_aead *authenc_esn,
					  unsigned int authsize)
{
	if (authsize > 0 && authsize < 4)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cwypto_authenc_esn_setkey(stwuct cwypto_aead *authenc_esn, const u8 *key,
				     unsigned int keywen)
{
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(authenc_esn);
	stwuct cwypto_ahash *auth = ctx->auth;
	stwuct cwypto_skciphew *enc = ctx->enc;
	stwuct cwypto_authenc_keys keys;
	int eww = -EINVAW;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto out;

	cwypto_ahash_cweaw_fwags(auth, CWYPTO_TFM_WEQ_MASK);
	cwypto_ahash_set_fwags(auth, cwypto_aead_get_fwags(authenc_esn) &
				     CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_ahash_setkey(auth, keys.authkey, keys.authkeywen);
	if (eww)
		goto out;

	cwypto_skciphew_cweaw_fwags(enc, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(enc, cwypto_aead_get_fwags(authenc_esn) &
					 CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(enc, keys.enckey, keys.enckeywen);
out:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn eww;
}

static int cwypto_authenc_esn_genicv_taiw(stwuct aead_wequest *weq,
					  unsigned int fwags)
{
	stwuct cwypto_aead *authenc_esn = cwypto_aead_weqtfm(weq);
	stwuct authenc_esn_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	u8 *hash = aweq_ctx->taiw;
	unsigned int authsize = cwypto_aead_authsize(authenc_esn);
	unsigned int assocwen = weq->assocwen;
	unsigned int cwyptwen = weq->cwyptwen;
	stwuct scattewwist *dst = weq->dst;
	u32 tmp[2];

	/* Move high-owdew bits of sequence numbew back. */
	scattewwawk_map_and_copy(tmp, dst, 4, 4, 0);
	scattewwawk_map_and_copy(tmp + 1, dst, assocwen + cwyptwen, 4, 0);
	scattewwawk_map_and_copy(tmp, dst, 0, 8, 1);

	scattewwawk_map_and_copy(hash, dst, assocwen + cwyptwen, authsize, 1);
	wetuwn 0;
}

static void authenc_esn_geniv_ahash_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	eww = eww ?: cwypto_authenc_esn_genicv_taiw(weq, 0);
	aead_wequest_compwete(weq, eww);
}

static int cwypto_authenc_esn_genicv(stwuct aead_wequest *weq,
				     unsigned int fwags)
{
	stwuct cwypto_aead *authenc_esn = cwypto_aead_weqtfm(weq);
	stwuct authenc_esn_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(authenc_esn);
	stwuct cwypto_ahash *auth = ctx->auth;
	u8 *hash = aweq_ctx->taiw;
	stwuct ahash_wequest *ahweq = (void *)(aweq_ctx->taiw + ctx->weqoff);
	unsigned int authsize = cwypto_aead_authsize(authenc_esn);
	unsigned int assocwen = weq->assocwen;
	unsigned int cwyptwen = weq->cwyptwen;
	stwuct scattewwist *dst = weq->dst;
	u32 tmp[2];

	if (!authsize)
		wetuwn 0;

	/* Move high-owdew bits of sequence numbew to the end. */
	scattewwawk_map_and_copy(tmp, dst, 0, 8, 0);
	scattewwawk_map_and_copy(tmp, dst, 4, 4, 1);
	scattewwawk_map_and_copy(tmp + 1, dst, assocwen + cwyptwen, 4, 1);

	sg_init_tabwe(aweq_ctx->dst, 2);
	dst = scattewwawk_ffwd(aweq_ctx->dst, dst, 4);

	ahash_wequest_set_tfm(ahweq, auth);
	ahash_wequest_set_cwypt(ahweq, dst, hash, assocwen + cwyptwen);
	ahash_wequest_set_cawwback(ahweq, fwags,
				   authenc_esn_geniv_ahash_done, weq);

	wetuwn cwypto_ahash_digest(ahweq) ?:
	       cwypto_authenc_esn_genicv_taiw(weq, aead_wequest_fwags(weq));
}


static void cwypto_authenc_esn_encwypt_done(void *data, int eww)
{
	stwuct aead_wequest *aweq = data;

	if (!eww)
		eww = cwypto_authenc_esn_genicv(aweq, 0);

	authenc_esn_wequest_compwete(aweq, eww);
}

static int cwypto_authenc_esn_copy(stwuct aead_wequest *weq, unsigned int wen)
{
	stwuct cwypto_aead *authenc_esn = cwypto_aead_weqtfm(weq);
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(authenc_esn);
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(skweq, ctx->nuww);

	skciphew_wequest_set_sync_tfm(skweq, ctx->nuww);
	skciphew_wequest_set_cawwback(skweq, aead_wequest_fwags(weq),
				      NUWW, NUWW);
	skciphew_wequest_set_cwypt(skweq, weq->swc, weq->dst, wen, NUWW);

	wetuwn cwypto_skciphew_encwypt(skweq);
}

static int cwypto_authenc_esn_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *authenc_esn = cwypto_aead_weqtfm(weq);
	stwuct authenc_esn_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(authenc_esn);
	stwuct skciphew_wequest *skweq = (void *)(aweq_ctx->taiw +
						  ctx->weqoff);
	stwuct cwypto_skciphew *enc = ctx->enc;
	unsigned int assocwen = weq->assocwen;
	unsigned int cwyptwen = weq->cwyptwen;
	stwuct scattewwist *swc, *dst;
	int eww;

	sg_init_tabwe(aweq_ctx->swc, 2);
	swc = scattewwawk_ffwd(aweq_ctx->swc, weq->swc, assocwen);
	dst = swc;

	if (weq->swc != weq->dst) {
		eww = cwypto_authenc_esn_copy(weq, assocwen);
		if (eww)
			wetuwn eww;

		sg_init_tabwe(aweq_ctx->dst, 2);
		dst = scattewwawk_ffwd(aweq_ctx->dst, weq->dst, assocwen);
	}

	skciphew_wequest_set_tfm(skweq, enc);
	skciphew_wequest_set_cawwback(skweq, aead_wequest_fwags(weq),
				      cwypto_authenc_esn_encwypt_done, weq);
	skciphew_wequest_set_cwypt(skweq, swc, dst, cwyptwen, weq->iv);

	eww = cwypto_skciphew_encwypt(skweq);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_authenc_esn_genicv(weq, aead_wequest_fwags(weq));
}

static int cwypto_authenc_esn_decwypt_taiw(stwuct aead_wequest *weq,
					   unsigned int fwags)
{
	stwuct cwypto_aead *authenc_esn = cwypto_aead_weqtfm(weq);
	unsigned int authsize = cwypto_aead_authsize(authenc_esn);
	stwuct authenc_esn_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(authenc_esn);
	stwuct skciphew_wequest *skweq = (void *)(aweq_ctx->taiw +
						  ctx->weqoff);
	stwuct cwypto_ahash *auth = ctx->auth;
	u8 *ohash = aweq_ctx->taiw;
	unsigned int cwyptwen = weq->cwyptwen - authsize;
	unsigned int assocwen = weq->assocwen;
	stwuct scattewwist *dst = weq->dst;
	u8 *ihash = ohash + cwypto_ahash_digestsize(auth);
	u32 tmp[2];

	if (!authsize)
		goto decwypt;

	/* Move high-owdew bits of sequence numbew back. */
	scattewwawk_map_and_copy(tmp, dst, 4, 4, 0);
	scattewwawk_map_and_copy(tmp + 1, dst, assocwen + cwyptwen, 4, 0);
	scattewwawk_map_and_copy(tmp, dst, 0, 8, 1);

	if (cwypto_memneq(ihash, ohash, authsize))
		wetuwn -EBADMSG;

decwypt:

	sg_init_tabwe(aweq_ctx->dst, 2);
	dst = scattewwawk_ffwd(aweq_ctx->dst, dst, assocwen);

	skciphew_wequest_set_tfm(skweq, ctx->enc);
	skciphew_wequest_set_cawwback(skweq, fwags,
				      weq->base.compwete, weq->base.data);
	skciphew_wequest_set_cwypt(skweq, dst, dst, cwyptwen, weq->iv);

	wetuwn cwypto_skciphew_decwypt(skweq);
}

static void authenc_esn_vewify_ahash_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	eww = eww ?: cwypto_authenc_esn_decwypt_taiw(weq, 0);
	authenc_esn_wequest_compwete(weq, eww);
}

static int cwypto_authenc_esn_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *authenc_esn = cwypto_aead_weqtfm(weq);
	stwuct authenc_esn_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(authenc_esn);
	stwuct ahash_wequest *ahweq = (void *)(aweq_ctx->taiw + ctx->weqoff);
	unsigned int authsize = cwypto_aead_authsize(authenc_esn);
	stwuct cwypto_ahash *auth = ctx->auth;
	u8 *ohash = aweq_ctx->taiw;
	unsigned int assocwen = weq->assocwen;
	unsigned int cwyptwen = weq->cwyptwen;
	u8 *ihash = ohash + cwypto_ahash_digestsize(auth);
	stwuct scattewwist *dst = weq->dst;
	u32 tmp[2];
	int eww;

	cwyptwen -= authsize;

	if (weq->swc != dst) {
		eww = cwypto_authenc_esn_copy(weq, assocwen + cwyptwen);
		if (eww)
			wetuwn eww;
	}

	scattewwawk_map_and_copy(ihash, weq->swc, assocwen + cwyptwen,
				 authsize, 0);

	if (!authsize)
		goto taiw;

	/* Move high-owdew bits of sequence numbew to the end. */
	scattewwawk_map_and_copy(tmp, dst, 0, 8, 0);
	scattewwawk_map_and_copy(tmp, dst, 4, 4, 1);
	scattewwawk_map_and_copy(tmp + 1, dst, assocwen + cwyptwen, 4, 1);

	sg_init_tabwe(aweq_ctx->dst, 2);
	dst = scattewwawk_ffwd(aweq_ctx->dst, dst, 4);

	ahash_wequest_set_tfm(ahweq, auth);
	ahash_wequest_set_cwypt(ahweq, dst, ohash, assocwen + cwyptwen);
	ahash_wequest_set_cawwback(ahweq, aead_wequest_fwags(weq),
				   authenc_esn_vewify_ahash_done, weq);

	eww = cwypto_ahash_digest(ahweq);
	if (eww)
		wetuwn eww;

taiw:
	wetuwn cwypto_authenc_esn_decwypt_taiw(weq, aead_wequest_fwags(weq));
}

static int cwypto_authenc_esn_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct authenc_esn_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_ahash *auth;
	stwuct cwypto_skciphew *enc;
	stwuct cwypto_sync_skciphew *nuww;
	int eww;

	auth = cwypto_spawn_ahash(&ictx->auth);
	if (IS_EWW(auth))
		wetuwn PTW_EWW(auth);

	enc = cwypto_spawn_skciphew(&ictx->enc);
	eww = PTW_EWW(enc);
	if (IS_EWW(enc))
		goto eww_fwee_ahash;

	nuww = cwypto_get_defauwt_nuww_skciphew();
	eww = PTW_EWW(nuww);
	if (IS_EWW(nuww))
		goto eww_fwee_skciphew;

	ctx->auth = auth;
	ctx->enc = enc;
	ctx->nuww = nuww;

	ctx->weqoff = 2 * cwypto_ahash_digestsize(auth);

	cwypto_aead_set_weqsize(
		tfm,
		sizeof(stwuct authenc_esn_wequest_ctx) +
		ctx->weqoff +
		max_t(unsigned int,
		      cwypto_ahash_weqsize(auth) +
		      sizeof(stwuct ahash_wequest),
		      sizeof(stwuct skciphew_wequest) +
		      cwypto_skciphew_weqsize(enc)));

	wetuwn 0;

eww_fwee_skciphew:
	cwypto_fwee_skciphew(enc);
eww_fwee_ahash:
	cwypto_fwee_ahash(auth);
	wetuwn eww;
}

static void cwypto_authenc_esn_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_authenc_esn_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_ahash(ctx->auth);
	cwypto_fwee_skciphew(ctx->enc);
	cwypto_put_defauwt_nuww_skciphew();
}

static void cwypto_authenc_esn_fwee(stwuct aead_instance *inst)
{
	stwuct authenc_esn_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_skciphew(&ctx->enc);
	cwypto_dwop_ahash(&ctx->auth);
	kfwee(inst);
}

static int cwypto_authenc_esn_cweate(stwuct cwypto_tempwate *tmpw,
				     stwuct wtattw **tb)
{
	u32 mask;
	stwuct aead_instance *inst;
	stwuct authenc_esn_instance_ctx *ctx;
	stwuct skciphew_awg_common *enc;
	stwuct hash_awg_common *auth;
	stwuct cwypto_awg *auth_base;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ctx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	ctx = aead_instance_ctx(inst);

	eww = cwypto_gwab_ahash(&ctx->auth, aead_cwypto_instance(inst),
				cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	auth = cwypto_spawn_ahash_awg(&ctx->auth);
	auth_base = &auth->base;

	eww = cwypto_gwab_skciphew(&ctx->enc, aead_cwypto_instance(inst),
				   cwypto_attw_awg_name(tb[2]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	enc = cwypto_spawn_skciphew_awg_common(&ctx->enc);

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "authencesn(%s,%s)", auth_base->cwa_name,
		     enc->base.cwa_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "authencesn(%s,%s)", auth_base->cwa_dwivew_name,
		     enc->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = enc->base.cwa_pwiowity * 10 +
				      auth_base->cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = enc->base.cwa_bwocksize;
	inst->awg.base.cwa_awignmask = enc->base.cwa_awignmask;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_authenc_esn_ctx);

	inst->awg.ivsize = enc->ivsize;
	inst->awg.chunksize = enc->chunksize;
	inst->awg.maxauthsize = auth->digestsize;

	inst->awg.init = cwypto_authenc_esn_init_tfm;
	inst->awg.exit = cwypto_authenc_esn_exit_tfm;

	inst->awg.setkey = cwypto_authenc_esn_setkey;
	inst->awg.setauthsize = cwypto_authenc_esn_setauthsize;
	inst->awg.encwypt = cwypto_authenc_esn_encwypt;
	inst->awg.decwypt = cwypto_authenc_esn_decwypt;

	inst->fwee = cwypto_authenc_esn_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_authenc_esn_fwee(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_authenc_esn_tmpw = {
	.name = "authencesn",
	.cweate = cwypto_authenc_esn_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_authenc_esn_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_authenc_esn_tmpw);
}

static void __exit cwypto_authenc_esn_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_authenc_esn_tmpw);
}

subsys_initcaww(cwypto_authenc_esn_moduwe_init);
moduwe_exit(cwypto_authenc_esn_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Steffen Kwassewt <steffen.kwassewt@secunet.com>");
MODUWE_DESCWIPTION("AEAD wwappew fow IPsec with extended sequence numbews");
MODUWE_AWIAS_CWYPTO("authencesn");
