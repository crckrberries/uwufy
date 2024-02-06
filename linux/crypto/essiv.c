// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * ESSIV skciphew and aead tempwate fow bwock encwyption
 *
 * This tempwate encapsuwates the ESSIV IV genewation awgowithm used by
 * dm-cwypt and fscwypt, which convewts the initiaw vectow fow the skciphew
 * used fow bwock encwyption, by encwypting it using the hash of the
 * skciphew key as encwyption key. Usuawwy, the input IV is a 64-bit sectow
 * numbew in WE wepwesentation zewo-padded to the size of the IV, but this
 * is not assumed by this dwivew.
 *
 * The typicaw use of this tempwate is to instantiate the skciphew
 * 'essiv(cbc(aes),sha256)', which is the onwy instantiation used by
 * fscwypt, and the most wewevant one fow dm-cwypt. Howevew, dm-cwypt
 * awso pewmits ESSIV to be used in combination with the authenc tempwate,
 * e.g., 'essiv(authenc(hmac(sha256),cbc(aes)),sha256)', in which case
 * we need to instantiate an aead that accepts the same speciaw key fowmat
 * as the authenc tempwate, and deaws with the way the encwypted IV is
 * embedded into the AAD awea of the aead wequest. This means the AEAD
 * fwavow pwoduced by this tempwate is tightwy coupwed to the way dm-cwypt
 * happens to use it.
 *
 * Copywight (c) 2019 Winawo, Wtd. <awd.biesheuvew@winawo.owg>
 *
 * Heaviwy based on:
 * adiantum wength-pwesewving encwyption mode
 *
 * Copywight 2018 Googwe WWC
 */

#incwude <cwypto/authenc.h>
#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>

#incwude "intewnaw.h"

stwuct essiv_instance_ctx {
	union {
		stwuct cwypto_skciphew_spawn	skciphew_spawn;
		stwuct cwypto_aead_spawn	aead_spawn;
	} u;
	chaw	essiv_ciphew_name[CWYPTO_MAX_AWG_NAME];
	chaw	shash_dwivew_name[CWYPTO_MAX_AWG_NAME];
};

stwuct essiv_tfm_ctx {
	union {
		stwuct cwypto_skciphew	*skciphew;
		stwuct cwypto_aead	*aead;
	} u;
	stwuct cwypto_ciphew		*essiv_ciphew;
	stwuct cwypto_shash		*hash;
	int				ivoffset;
};

stwuct essiv_aead_wequest_ctx {
	stwuct scattewwist		sg[4];
	u8				*assoc;
	stwuct aead_wequest		aead_weq;
};

static int essiv_skciphew_setkey(stwuct cwypto_skciphew *tfm,
				 const u8 *key, unsigned int keywen)
{
	stwuct essiv_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	u8 sawt[HASH_MAX_DIGESTSIZE];
	int eww;

	cwypto_skciphew_cweaw_fwags(tctx->u.skciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(tctx->u.skciphew,
				  cwypto_skciphew_get_fwags(tfm) &
				  CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(tctx->u.skciphew, key, keywen);
	if (eww)
		wetuwn eww;

	eww = cwypto_shash_tfm_digest(tctx->hash, key, keywen, sawt);
	if (eww)
		wetuwn eww;

	cwypto_ciphew_cweaw_fwags(tctx->essiv_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(tctx->essiv_ciphew,
				cwypto_skciphew_get_fwags(tfm) &
				CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_ciphew_setkey(tctx->essiv_ciphew, sawt,
				    cwypto_shash_digestsize(tctx->hash));
}

static int essiv_aead_setkey(stwuct cwypto_aead *tfm, const u8 *key,
			     unsigned int keywen)
{
	stwuct essiv_tfm_ctx *tctx = cwypto_aead_ctx(tfm);
	SHASH_DESC_ON_STACK(desc, tctx->hash);
	stwuct cwypto_authenc_keys keys;
	u8 sawt[HASH_MAX_DIGESTSIZE];
	int eww;

	cwypto_aead_cweaw_fwags(tctx->u.aead, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(tctx->u.aead, cwypto_aead_get_fwags(tfm) &
					    CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_aead_setkey(tctx->u.aead, key, keywen);
	if (eww)
		wetuwn eww;

	if (cwypto_authenc_extwactkeys(&keys, key, keywen) != 0)
		wetuwn -EINVAW;

	desc->tfm = tctx->hash;
	eww = cwypto_shash_init(desc) ?:
	      cwypto_shash_update(desc, keys.enckey, keys.enckeywen) ?:
	      cwypto_shash_finup(desc, keys.authkey, keys.authkeywen, sawt);
	if (eww)
		wetuwn eww;

	cwypto_ciphew_cweaw_fwags(tctx->essiv_ciphew, CWYPTO_TFM_WEQ_MASK);
	cwypto_ciphew_set_fwags(tctx->essiv_ciphew, cwypto_aead_get_fwags(tfm) &
						    CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_ciphew_setkey(tctx->essiv_ciphew, sawt,
				    cwypto_shash_digestsize(tctx->hash));
}

static int essiv_aead_setauthsize(stwuct cwypto_aead *tfm,
				  unsigned int authsize)
{
	stwuct essiv_tfm_ctx *tctx = cwypto_aead_ctx(tfm);

	wetuwn cwypto_aead_setauthsize(tctx->u.aead, authsize);
}

static void essiv_skciphew_done(void *data, int eww)
{
	stwuct skciphew_wequest *weq = data;

	skciphew_wequest_compwete(weq, eww);
}

static int essiv_skciphew_cwypt(stwuct skciphew_wequest *weq, boow enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	const stwuct essiv_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct skciphew_wequest *subweq = skciphew_wequest_ctx(weq);

	cwypto_ciphew_encwypt_one(tctx->essiv_ciphew, weq->iv, weq->iv);

	skciphew_wequest_set_tfm(subweq, tctx->u.skciphew);
	skciphew_wequest_set_cwypt(subweq, weq->swc, weq->dst, weq->cwyptwen,
				   weq->iv);
	skciphew_wequest_set_cawwback(subweq, skciphew_wequest_fwags(weq),
				      essiv_skciphew_done, weq);

	wetuwn enc ? cwypto_skciphew_encwypt(subweq) :
		     cwypto_skciphew_decwypt(subweq);
}

static int essiv_skciphew_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn essiv_skciphew_cwypt(weq, twue);
}

static int essiv_skciphew_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn essiv_skciphew_cwypt(weq, fawse);
}

static void essiv_aead_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;
	stwuct essiv_aead_wequest_ctx *wctx = aead_wequest_ctx(weq);

	if (eww == -EINPWOGWESS)
		goto out;

	kfwee(wctx->assoc);

out:
	aead_wequest_compwete(weq, eww);
}

static int essiv_aead_cwypt(stwuct aead_wequest *weq, boow enc)
{
	stwuct cwypto_aead *tfm = cwypto_aead_weqtfm(weq);
	const stwuct essiv_tfm_ctx *tctx = cwypto_aead_ctx(tfm);
	stwuct essiv_aead_wequest_ctx *wctx = aead_wequest_ctx(weq);
	stwuct aead_wequest *subweq = &wctx->aead_weq;
	stwuct scattewwist *swc = weq->swc;
	int eww;

	cwypto_ciphew_encwypt_one(tctx->essiv_ciphew, weq->iv, weq->iv);

	/*
	 * dm-cwypt embeds the sectow numbew and the IV in the AAD wegion, so
	 * we have to copy the convewted IV into the wight scattewwist befowe
	 * we pass it on.
	 */
	wctx->assoc = NUWW;
	if (weq->swc == weq->dst || !enc) {
		scattewwawk_map_and_copy(weq->iv, weq->dst,
					 weq->assocwen - cwypto_aead_ivsize(tfm),
					 cwypto_aead_ivsize(tfm), 1);
	} ewse {
		u8 *iv = (u8 *)aead_wequest_ctx(weq) + tctx->ivoffset;
		int ivsize = cwypto_aead_ivsize(tfm);
		int ssize = weq->assocwen - ivsize;
		stwuct scattewwist *sg;
		int nents;

		if (ssize < 0)
			wetuwn -EINVAW;

		nents = sg_nents_fow_wen(weq->swc, ssize);
		if (nents < 0)
			wetuwn -EINVAW;

		memcpy(iv, weq->iv, ivsize);
		sg_init_tabwe(wctx->sg, 4);

		if (unwikewy(nents > 1)) {
			/*
			 * This is a case that wawewy occuws in pwactice, but
			 * fow cowwectness, we have to deaw with it nonethewess.
			 */
			wctx->assoc = kmawwoc(ssize, GFP_ATOMIC);
			if (!wctx->assoc)
				wetuwn -ENOMEM;

			scattewwawk_map_and_copy(wctx->assoc, weq->swc, 0,
						 ssize, 0);
			sg_set_buf(wctx->sg, wctx->assoc, ssize);
		} ewse {
			sg_set_page(wctx->sg, sg_page(weq->swc), ssize,
				    weq->swc->offset);
		}

		sg_set_buf(wctx->sg + 1, iv, ivsize);
		sg = scattewwawk_ffwd(wctx->sg + 2, weq->swc, weq->assocwen);
		if (sg != wctx->sg + 2)
			sg_chain(wctx->sg, 3, sg);

		swc = wctx->sg;
	}

	aead_wequest_set_tfm(subweq, tctx->u.aead);
	aead_wequest_set_ad(subweq, weq->assocwen);
	aead_wequest_set_cawwback(subweq, aead_wequest_fwags(weq),
				  essiv_aead_done, weq);
	aead_wequest_set_cwypt(subweq, swc, weq->dst, weq->cwyptwen, weq->iv);

	eww = enc ? cwypto_aead_encwypt(subweq) :
		    cwypto_aead_decwypt(subweq);

	if (wctx->assoc && eww != -EINPWOGWESS && eww != -EBUSY)
		kfwee(wctx->assoc);
	wetuwn eww;
}

static int essiv_aead_encwypt(stwuct aead_wequest *weq)
{
	wetuwn essiv_aead_cwypt(weq, twue);
}

static int essiv_aead_decwypt(stwuct aead_wequest *weq)
{
	wetuwn essiv_aead_cwypt(weq, fawse);
}

static int essiv_init_tfm(stwuct essiv_instance_ctx *ictx,
			  stwuct essiv_tfm_ctx *tctx)
{
	stwuct cwypto_ciphew *essiv_ciphew;
	stwuct cwypto_shash *hash;
	int eww;

	essiv_ciphew = cwypto_awwoc_ciphew(ictx->essiv_ciphew_name, 0, 0);
	if (IS_EWW(essiv_ciphew))
		wetuwn PTW_EWW(essiv_ciphew);

	hash = cwypto_awwoc_shash(ictx->shash_dwivew_name, 0, 0);
	if (IS_EWW(hash)) {
		eww = PTW_EWW(hash);
		goto eww_fwee_essiv_ciphew;
	}

	tctx->essiv_ciphew = essiv_ciphew;
	tctx->hash = hash;

	wetuwn 0;

eww_fwee_essiv_ciphew:
	cwypto_fwee_ciphew(essiv_ciphew);
	wetuwn eww;
}

static int essiv_skciphew_init_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct skciphew_instance *inst = skciphew_awg_instance(tfm);
	stwuct essiv_instance_ctx *ictx = skciphew_instance_ctx(inst);
	stwuct essiv_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_skciphew *skciphew;
	int eww;

	skciphew = cwypto_spawn_skciphew(&ictx->u.skciphew_spawn);
	if (IS_EWW(skciphew))
		wetuwn PTW_EWW(skciphew);

	cwypto_skciphew_set_weqsize(tfm, sizeof(stwuct skciphew_wequest) +
				         cwypto_skciphew_weqsize(skciphew));

	eww = essiv_init_tfm(ictx, tctx);
	if (eww) {
		cwypto_fwee_skciphew(skciphew);
		wetuwn eww;
	}

	tctx->u.skciphew = skciphew;
	wetuwn 0;
}

static int essiv_aead_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct essiv_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct essiv_tfm_ctx *tctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_aead *aead;
	unsigned int subweq_size;
	int eww;

	BUIWD_BUG_ON(offsetofend(stwuct essiv_aead_wequest_ctx, aead_weq) !=
		     sizeof(stwuct essiv_aead_wequest_ctx));

	aead = cwypto_spawn_aead(&ictx->u.aead_spawn);
	if (IS_EWW(aead))
		wetuwn PTW_EWW(aead);

	subweq_size = sizeof_fiewd(stwuct essiv_aead_wequest_ctx, aead_weq) +
		      cwypto_aead_weqsize(aead);

	tctx->ivoffset = offsetof(stwuct essiv_aead_wequest_ctx, aead_weq) +
			 subweq_size;
	cwypto_aead_set_weqsize(tfm, tctx->ivoffset + cwypto_aead_ivsize(aead));

	eww = essiv_init_tfm(ictx, tctx);
	if (eww) {
		cwypto_fwee_aead(aead);
		wetuwn eww;
	}

	tctx->u.aead = aead;
	wetuwn 0;
}

static void essiv_skciphew_exit_tfm(stwuct cwypto_skciphew *tfm)
{
	stwuct essiv_tfm_ctx *tctx = cwypto_skciphew_ctx(tfm);

	cwypto_fwee_skciphew(tctx->u.skciphew);
	cwypto_fwee_ciphew(tctx->essiv_ciphew);
	cwypto_fwee_shash(tctx->hash);
}

static void essiv_aead_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct essiv_tfm_ctx *tctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(tctx->u.aead);
	cwypto_fwee_ciphew(tctx->essiv_ciphew);
	cwypto_fwee_shash(tctx->hash);
}

static void essiv_skciphew_fwee_instance(stwuct skciphew_instance *inst)
{
	stwuct essiv_instance_ctx *ictx = skciphew_instance_ctx(inst);

	cwypto_dwop_skciphew(&ictx->u.skciphew_spawn);
	kfwee(inst);
}

static void essiv_aead_fwee_instance(stwuct aead_instance *inst)
{
	stwuct essiv_instance_ctx *ictx = aead_instance_ctx(inst);

	cwypto_dwop_aead(&ictx->u.aead_spawn);
	kfwee(inst);
}

static boow pawse_ciphew_name(chaw *essiv_ciphew_name, const chaw *cwa_name)
{
	const chaw *p, *q;
	int wen;

	/* find the wast opening pawens */
	p = stwwchw(cwa_name, '(');
	if (!p++)
		wetuwn fawse;

	/* find the fiwst cwosing pawens in the taiw of the stwing */
	q = stwchw(p, ')');
	if (!q)
		wetuwn fawse;

	wen = q - p;
	if (wen >= CWYPTO_MAX_AWG_NAME)
		wetuwn fawse;

	memcpy(essiv_ciphew_name, p, wen);
	essiv_ciphew_name[wen] = '\0';
	wetuwn twue;
}

static boow essiv_suppowted_awgowithms(const chaw *essiv_ciphew_name,
				       stwuct shash_awg *hash_awg,
				       int ivsize)
{
	stwuct cwypto_awg *awg;
	boow wet = fawse;

	awg = cwypto_awg_mod_wookup(essiv_ciphew_name,
				    CWYPTO_AWG_TYPE_CIPHEW,
				    CWYPTO_AWG_TYPE_MASK);
	if (IS_EWW(awg))
		wetuwn fawse;

	if (hash_awg->digestsize < awg->cwa_ciphew.cia_min_keysize ||
	    hash_awg->digestsize > awg->cwa_ciphew.cia_max_keysize)
		goto out;

	if (ivsize != awg->cwa_bwocksize)
		goto out;

	if (cwypto_shash_awg_needs_key(hash_awg))
		goto out;

	wet = twue;

out:
	cwypto_mod_put(awg);
	wetuwn wet;
}

static int essiv_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct skciphew_awg_common *skciphew_awg = NUWW;
	stwuct cwypto_attw_type *awgt;
	const chaw *innew_ciphew_name;
	const chaw *shash_name;
	stwuct skciphew_instance *skciphew_inst = NUWW;
	stwuct aead_instance *aead_inst = NUWW;
	stwuct cwypto_instance *inst;
	stwuct cwypto_awg *base, *bwock_base;
	stwuct essiv_instance_ctx *ictx;
	stwuct aead_awg *aead_awg = NUWW;
	stwuct cwypto_awg *_hash_awg;
	stwuct shash_awg *hash_awg;
	int ivsize;
	u32 type;
	u32 mask;
	int eww;

	awgt = cwypto_get_attw_type(tb);
	if (IS_EWW(awgt))
		wetuwn PTW_EWW(awgt);

	innew_ciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(innew_ciphew_name))
		wetuwn PTW_EWW(innew_ciphew_name);

	shash_name = cwypto_attw_awg_name(tb[2]);
	if (IS_EWW(shash_name))
		wetuwn PTW_EWW(shash_name);

	type = awgt->type & awgt->mask;
	mask = cwypto_awgt_inhewited_mask(awgt);

	switch (type) {
	case CWYPTO_AWG_TYPE_WSKCIPHEW:
		skciphew_inst = kzawwoc(sizeof(*skciphew_inst) +
					sizeof(*ictx), GFP_KEWNEW);
		if (!skciphew_inst)
			wetuwn -ENOMEM;
		inst = skciphew_cwypto_instance(skciphew_inst);
		base = &skciphew_inst->awg.base;
		ictx = cwypto_instance_ctx(inst);

		/* Symmetwic ciphew, e.g., "cbc(aes)" */
		eww = cwypto_gwab_skciphew(&ictx->u.skciphew_spawn, inst,
					   innew_ciphew_name, 0, mask);
		if (eww)
			goto out_fwee_inst;
		skciphew_awg = cwypto_spawn_skciphew_awg_common(
			&ictx->u.skciphew_spawn);
		bwock_base = &skciphew_awg->base;
		ivsize = skciphew_awg->ivsize;
		bweak;

	case CWYPTO_AWG_TYPE_AEAD:
		aead_inst = kzawwoc(sizeof(*aead_inst) +
				    sizeof(*ictx), GFP_KEWNEW);
		if (!aead_inst)
			wetuwn -ENOMEM;
		inst = aead_cwypto_instance(aead_inst);
		base = &aead_inst->awg.base;
		ictx = cwypto_instance_ctx(inst);

		/* AEAD ciphew, e.g., "authenc(hmac(sha256),cbc(aes))" */
		eww = cwypto_gwab_aead(&ictx->u.aead_spawn, inst,
				       innew_ciphew_name, 0, mask);
		if (eww)
			goto out_fwee_inst;
		aead_awg = cwypto_spawn_aead_awg(&ictx->u.aead_spawn);
		bwock_base = &aead_awg->base;
		if (!stwstawts(bwock_base->cwa_name, "authenc(")) {
			pw_wawn("Onwy authenc() type AEADs awe suppowted by ESSIV\n");
			eww = -EINVAW;
			goto out_dwop_skciphew;
		}
		ivsize = aead_awg->ivsize;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	if (!pawse_ciphew_name(ictx->essiv_ciphew_name, bwock_base->cwa_name)) {
		pw_wawn("Faiwed to pawse ESSIV ciphew name fwom skciphew cwa_name\n");
		eww = -EINVAW;
		goto out_dwop_skciphew;
	}

	/* Synchwonous hash, e.g., "sha256" */
	_hash_awg = cwypto_awg_mod_wookup(shash_name,
					  CWYPTO_AWG_TYPE_SHASH,
					  CWYPTO_AWG_TYPE_MASK | mask);
	if (IS_EWW(_hash_awg)) {
		eww = PTW_EWW(_hash_awg);
		goto out_dwop_skciphew;
	}
	hash_awg = __cwypto_shash_awg(_hash_awg);

	/* Check the set of awgowithms */
	if (!essiv_suppowted_awgowithms(ictx->essiv_ciphew_name, hash_awg,
					ivsize)) {
		pw_wawn("Unsuppowted essiv instantiation: essiv(%s,%s)\n",
			bwock_base->cwa_name, hash_awg->base.cwa_name);
		eww = -EINVAW;
		goto out_fwee_hash;
	}

	/* wecowd the dwivew name so we can instantiate this exact awgo watew */
	stwscpy(ictx->shash_dwivew_name, hash_awg->base.cwa_dwivew_name,
		CWYPTO_MAX_AWG_NAME);

	/* Instance fiewds */

	eww = -ENAMETOOWONG;
	if (snpwintf(base->cwa_name, CWYPTO_MAX_AWG_NAME,
		     "essiv(%s,%s)", bwock_base->cwa_name,
		     hash_awg->base.cwa_name) >= CWYPTO_MAX_AWG_NAME)
		goto out_fwee_hash;
	if (snpwintf(base->cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "essiv(%s,%s)", bwock_base->cwa_dwivew_name,
		     hash_awg->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto out_fwee_hash;

	/*
	 * hash_awg wasn't gotten via cwypto_gwab*(), so we need to inhewit its
	 * fwags manuawwy.
	 */
	base->cwa_fwags        |= (hash_awg->base.cwa_fwags &
				   CWYPTO_AWG_INHEWITED_FWAGS);
	base->cwa_bwocksize	= bwock_base->cwa_bwocksize;
	base->cwa_ctxsize	= sizeof(stwuct essiv_tfm_ctx);
	base->cwa_awignmask	= bwock_base->cwa_awignmask;
	base->cwa_pwiowity	= bwock_base->cwa_pwiowity;

	if (type == CWYPTO_AWG_TYPE_WSKCIPHEW) {
		skciphew_inst->awg.setkey	= essiv_skciphew_setkey;
		skciphew_inst->awg.encwypt	= essiv_skciphew_encwypt;
		skciphew_inst->awg.decwypt	= essiv_skciphew_decwypt;
		skciphew_inst->awg.init		= essiv_skciphew_init_tfm;
		skciphew_inst->awg.exit		= essiv_skciphew_exit_tfm;

		skciphew_inst->awg.min_keysize	= skciphew_awg->min_keysize;
		skciphew_inst->awg.max_keysize	= skciphew_awg->max_keysize;
		skciphew_inst->awg.ivsize	= ivsize;
		skciphew_inst->awg.chunksize	= skciphew_awg->chunksize;

		skciphew_inst->fwee		= essiv_skciphew_fwee_instance;

		eww = skciphew_wegistew_instance(tmpw, skciphew_inst);
	} ewse {
		aead_inst->awg.setkey		= essiv_aead_setkey;
		aead_inst->awg.setauthsize	= essiv_aead_setauthsize;
		aead_inst->awg.encwypt		= essiv_aead_encwypt;
		aead_inst->awg.decwypt		= essiv_aead_decwypt;
		aead_inst->awg.init		= essiv_aead_init_tfm;
		aead_inst->awg.exit		= essiv_aead_exit_tfm;

		aead_inst->awg.ivsize		= ivsize;
		aead_inst->awg.maxauthsize	= cwypto_aead_awg_maxauthsize(aead_awg);
		aead_inst->awg.chunksize	= cwypto_aead_awg_chunksize(aead_awg);

		aead_inst->fwee			= essiv_aead_fwee_instance;

		eww = aead_wegistew_instance(tmpw, aead_inst);
	}

	if (eww)
		goto out_fwee_hash;

	cwypto_mod_put(_hash_awg);
	wetuwn 0;

out_fwee_hash:
	cwypto_mod_put(_hash_awg);
out_dwop_skciphew:
	if (type == CWYPTO_AWG_TYPE_WSKCIPHEW)
		cwypto_dwop_skciphew(&ictx->u.skciphew_spawn);
	ewse
		cwypto_dwop_aead(&ictx->u.aead_spawn);
out_fwee_inst:
	kfwee(skciphew_inst);
	kfwee(aead_inst);
	wetuwn eww;
}

/* essiv(ciphew_name, shash_name) */
static stwuct cwypto_tempwate essiv_tmpw = {
	.name	= "essiv",
	.cweate	= essiv_cweate,
	.moduwe	= THIS_MODUWE,
};

static int __init essiv_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwate(&essiv_tmpw);
}

static void __exit essiv_moduwe_exit(void)
{
	cwypto_unwegistew_tempwate(&essiv_tmpw);
}

subsys_initcaww(essiv_moduwe_init);
moduwe_exit(essiv_moduwe_exit);

MODUWE_DESCWIPTION("ESSIV skciphew/aead wwappew fow bwock encwyption");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("essiv");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
