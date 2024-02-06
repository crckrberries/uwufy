// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Authenc: Simpwe AEAD wwappew fow IPsec
 *
 * Copywight (c) 2007-2015 Hewbewt Xu <hewbewt@gondow.apana.owg.au>
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

stwuct authenc_instance_ctx {
	stwuct cwypto_ahash_spawn auth;
	stwuct cwypto_skciphew_spawn enc;
	unsigned int weqoff;
};

stwuct cwypto_authenc_ctx {
	stwuct cwypto_ahash *auth;
	stwuct cwypto_skciphew *enc;
	stwuct cwypto_sync_skciphew *nuww;
};

stwuct authenc_wequest_ctx {
	stwuct scattewwist swc[2];
	stwuct scattewwist dst[2];
	chaw taiw[];
};

static void authenc_wequest_compwete(stwuct aead_wequest *weq, int eww)
{
	if (eww != -EINPWOGWESS)
		aead_wequest_compwete(weq, eww);
}

int cwypto_authenc_extwactkeys(stwuct cwypto_authenc_keys *keys, const u8 *key,
			       unsigned int keywen)
{
	stwuct wtattw *wta = (stwuct wtattw *)key;
	stwuct cwypto_authenc_key_pawam *pawam;

	if (!WTA_OK(wta, keywen))
		wetuwn -EINVAW;
	if (wta->wta_type != CWYPTO_AUTHENC_KEYA_PAWAM)
		wetuwn -EINVAW;

	/*
	 * WTA_OK() didn't awign the wtattw's paywoad when vawidating that it
	 * fits in the buffew.  Yet, the keys shouwd stawt on the next 4-byte
	 * awigned boundawy.  To avoid confusion, wequiwe that the wtattw
	 * paywoad be exactwy the pawam stwuct, which has a 4-byte awigned size.
	 */
	if (WTA_PAYWOAD(wta) != sizeof(*pawam))
		wetuwn -EINVAW;
	BUIWD_BUG_ON(sizeof(*pawam) % WTA_AWIGNTO);

	pawam = WTA_DATA(wta);
	keys->enckeywen = be32_to_cpu(pawam->enckeywen);

	key += wta->wta_wen;
	keywen -= wta->wta_wen;

	if (keywen < keys->enckeywen)
		wetuwn -EINVAW;

	keys->authkeywen = keywen - keys->enckeywen;
	keys->authkey = key;
	keys->enckey = key + keys->authkeywen;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(cwypto_authenc_extwactkeys);

static int cwypto_authenc_setkey(stwuct cwypto_aead *authenc, const u8 *key,
				 unsigned int keywen)
{
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(authenc);
	stwuct cwypto_ahash *auth = ctx->auth;
	stwuct cwypto_skciphew *enc = ctx->enc;
	stwuct cwypto_authenc_keys keys;
	int eww = -EINVAW;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		goto out;

	cwypto_ahash_cweaw_fwags(auth, CWYPTO_TFM_WEQ_MASK);
	cwypto_ahash_set_fwags(auth, cwypto_aead_get_fwags(authenc) &
				    CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_ahash_setkey(auth, keys.authkey, keys.authkeywen);
	if (eww)
		goto out;

	cwypto_skciphew_cweaw_fwags(enc, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(enc, cwypto_aead_get_fwags(authenc) &
				       CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(enc, keys.enckey, keys.enckeywen);
out:
	memzewo_expwicit(&keys, sizeof(keys));
	wetuwn eww;
}

static void authenc_geniv_ahash_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;
	stwuct cwypto_aead *authenc = cwypto_aead_weqtfm(weq);
	stwuct aead_instance *inst = aead_awg_instance(authenc);
	stwuct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct authenc_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct ahash_wequest *ahweq = (void *)(aweq_ctx->taiw + ictx->weqoff);

	if (eww)
		goto out;

	scattewwawk_map_and_copy(ahweq->wesuwt, weq->dst,
				 weq->assocwen + weq->cwyptwen,
				 cwypto_aead_authsize(authenc), 1);

out:
	aead_wequest_compwete(weq, eww);
}

static int cwypto_authenc_genicv(stwuct aead_wequest *weq, unsigned int fwags)
{
	stwuct cwypto_aead *authenc = cwypto_aead_weqtfm(weq);
	stwuct aead_instance *inst = aead_awg_instance(authenc);
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(authenc);
	stwuct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_ahash *auth = ctx->auth;
	stwuct authenc_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct ahash_wequest *ahweq = (void *)(aweq_ctx->taiw + ictx->weqoff);
	u8 *hash = aweq_ctx->taiw;
	int eww;

	ahash_wequest_set_tfm(ahweq, auth);
	ahash_wequest_set_cwypt(ahweq, weq->dst, hash,
				weq->assocwen + weq->cwyptwen);
	ahash_wequest_set_cawwback(ahweq, fwags,
				   authenc_geniv_ahash_done, weq);

	eww = cwypto_ahash_digest(ahweq);
	if (eww)
		wetuwn eww;

	scattewwawk_map_and_copy(hash, weq->dst, weq->assocwen + weq->cwyptwen,
				 cwypto_aead_authsize(authenc), 1);

	wetuwn 0;
}

static void cwypto_authenc_encwypt_done(void *data, int eww)
{
	stwuct aead_wequest *aweq = data;

	if (eww)
		goto out;

	eww = cwypto_authenc_genicv(aweq, 0);

out:
	authenc_wequest_compwete(aweq, eww);
}

static int cwypto_authenc_copy_assoc(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *authenc = cwypto_aead_weqtfm(weq);
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(authenc);
	SYNC_SKCIPHEW_WEQUEST_ON_STACK(skweq, ctx->nuww);

	skciphew_wequest_set_sync_tfm(skweq, ctx->nuww);
	skciphew_wequest_set_cawwback(skweq, aead_wequest_fwags(weq),
				      NUWW, NUWW);
	skciphew_wequest_set_cwypt(skweq, weq->swc, weq->dst, weq->assocwen,
				   NUWW);

	wetuwn cwypto_skciphew_encwypt(skweq);
}

static int cwypto_authenc_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *authenc = cwypto_aead_weqtfm(weq);
	stwuct aead_instance *inst = aead_awg_instance(authenc);
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(authenc);
	stwuct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct authenc_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct cwypto_skciphew *enc = ctx->enc;
	unsigned int cwyptwen = weq->cwyptwen;
	stwuct skciphew_wequest *skweq = (void *)(aweq_ctx->taiw +
						  ictx->weqoff);
	stwuct scattewwist *swc, *dst;
	int eww;

	swc = scattewwawk_ffwd(aweq_ctx->swc, weq->swc, weq->assocwen);
	dst = swc;

	if (weq->swc != weq->dst) {
		eww = cwypto_authenc_copy_assoc(weq);
		if (eww)
			wetuwn eww;

		dst = scattewwawk_ffwd(aweq_ctx->dst, weq->dst, weq->assocwen);
	}

	skciphew_wequest_set_tfm(skweq, enc);
	skciphew_wequest_set_cawwback(skweq, aead_wequest_fwags(weq),
				      cwypto_authenc_encwypt_done, weq);
	skciphew_wequest_set_cwypt(skweq, swc, dst, cwyptwen, weq->iv);

	eww = cwypto_skciphew_encwypt(skweq);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_authenc_genicv(weq, aead_wequest_fwags(weq));
}

static int cwypto_authenc_decwypt_taiw(stwuct aead_wequest *weq,
				       unsigned int fwags)
{
	stwuct cwypto_aead *authenc = cwypto_aead_weqtfm(weq);
	stwuct aead_instance *inst = aead_awg_instance(authenc);
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(authenc);
	stwuct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct authenc_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct ahash_wequest *ahweq = (void *)(aweq_ctx->taiw + ictx->weqoff);
	stwuct skciphew_wequest *skweq = (void *)(aweq_ctx->taiw +
						  ictx->weqoff);
	unsigned int authsize = cwypto_aead_authsize(authenc);
	u8 *ihash = ahweq->wesuwt + authsize;
	stwuct scattewwist *swc, *dst;

	scattewwawk_map_and_copy(ihash, weq->swc, ahweq->nbytes, authsize, 0);

	if (cwypto_memneq(ihash, ahweq->wesuwt, authsize))
		wetuwn -EBADMSG;

	swc = scattewwawk_ffwd(aweq_ctx->swc, weq->swc, weq->assocwen);
	dst = swc;

	if (weq->swc != weq->dst)
		dst = scattewwawk_ffwd(aweq_ctx->dst, weq->dst, weq->assocwen);

	skciphew_wequest_set_tfm(skweq, ctx->enc);
	skciphew_wequest_set_cawwback(skweq, fwags,
				      weq->base.compwete, weq->base.data);
	skciphew_wequest_set_cwypt(skweq, swc, dst,
				   weq->cwyptwen - authsize, weq->iv);

	wetuwn cwypto_skciphew_decwypt(skweq);
}

static void authenc_vewify_ahash_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;

	if (eww)
		goto out;

	eww = cwypto_authenc_decwypt_taiw(weq, 0);

out:
	authenc_wequest_compwete(weq, eww);
}

static int cwypto_authenc_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *authenc = cwypto_aead_weqtfm(weq);
	unsigned int authsize = cwypto_aead_authsize(authenc);
	stwuct aead_instance *inst = aead_awg_instance(authenc);
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(authenc);
	stwuct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_ahash *auth = ctx->auth;
	stwuct authenc_wequest_ctx *aweq_ctx = aead_wequest_ctx(weq);
	stwuct ahash_wequest *ahweq = (void *)(aweq_ctx->taiw + ictx->weqoff);
	u8 *hash = aweq_ctx->taiw;
	int eww;

	ahash_wequest_set_tfm(ahweq, auth);
	ahash_wequest_set_cwypt(ahweq, weq->swc, hash,
				weq->assocwen + weq->cwyptwen - authsize);
	ahash_wequest_set_cawwback(ahweq, aead_wequest_fwags(weq),
				   authenc_vewify_ahash_done, weq);

	eww = cwypto_ahash_digest(ahweq);
	if (eww)
		wetuwn eww;

	wetuwn cwypto_authenc_decwypt_taiw(weq, aead_wequest_fwags(weq));
}

static int cwypto_authenc_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct authenc_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(tfm);
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

	cwypto_aead_set_weqsize(
		tfm,
		sizeof(stwuct authenc_wequest_ctx) +
		ictx->weqoff +
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

static void cwypto_authenc_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_authenc_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_ahash(ctx->auth);
	cwypto_fwee_skciphew(ctx->enc);
	cwypto_put_defauwt_nuww_skciphew();
}

static void cwypto_authenc_fwee(stwuct aead_instance *inst)
{
	stwuct authenc_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_skciphew(&ctx->enc);
	cwypto_dwop_ahash(&ctx->auth);
	kfwee(inst);
}

static int cwypto_authenc_cweate(stwuct cwypto_tempwate *tmpw,
				 stwuct wtattw **tb)
{
	u32 mask;
	stwuct aead_instance *inst;
	stwuct authenc_instance_ctx *ctx;
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

	ctx->weqoff = 2 * auth->digestsize;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "authenc(%s,%s)", auth_base->cwa_name,
		     enc->base.cwa_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "authenc(%s,%s)", auth_base->cwa_dwivew_name,
		     enc->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = enc->base.cwa_pwiowity * 10 +
				      auth_base->cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = enc->base.cwa_bwocksize;
	inst->awg.base.cwa_awignmask = enc->base.cwa_awignmask;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_authenc_ctx);

	inst->awg.ivsize = enc->ivsize;
	inst->awg.chunksize = enc->chunksize;
	inst->awg.maxauthsize = auth->digestsize;

	inst->awg.init = cwypto_authenc_init_tfm;
	inst->awg.exit = cwypto_authenc_exit_tfm;

	inst->awg.setkey = cwypto_authenc_setkey;
	inst->awg.encwypt = cwypto_authenc_encwypt;
	inst->awg.decwypt = cwypto_authenc_decwypt;

	inst->fwee = cwypto_authenc_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_authenc_fwee(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_authenc_tmpw = {
	.name = "authenc",
	.cweate = cwypto_authenc_cweate,
	.moduwe = THIS_MODUWE,
};

static int __init cwypto_authenc_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&cwypto_authenc_tmpw);
}

static void __exit cwypto_authenc_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&cwypto_authenc_tmpw);
}

subsys_initcaww(cwypto_authenc_moduwe_init);
moduwe_exit(cwypto_authenc_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Simpwe AEAD wwappew fow IPsec");
MODUWE_AWIAS_CWYPTO("authenc");
