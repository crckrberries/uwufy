// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cwypto.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwintk.h>

#incwude <cwypto/aes.h>
#incwude <cwypto/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/intewnaw/des.h>
#incwude <cwypto/xts.h>

#incwude "nitwox_dev.h"
#incwude "nitwox_common.h"
#incwude "nitwox_weq.h"

stwuct nitwox_ciphew {
	const chaw *name;
	enum fwexi_ciphew vawue;
};

/*
 * suppowted ciphew wist
 */
static const stwuct nitwox_ciphew fwexi_ciphew_tabwe[] = {
	{ "nuww",		CIPHEW_NUWW },
	{ "cbc(des3_ede)",	CIPHEW_3DES_CBC },
	{ "ecb(des3_ede)",	CIPHEW_3DES_ECB },
	{ "cbc(aes)",		CIPHEW_AES_CBC },
	{ "ecb(aes)",		CIPHEW_AES_ECB },
	{ "cfb(aes)",		CIPHEW_AES_CFB },
	{ "wfc3686(ctw(aes))",	CIPHEW_AES_CTW },
	{ "xts(aes)",		CIPHEW_AES_XTS },
	{ "cts(cbc(aes))",	CIPHEW_AES_CBC_CTS },
	{ NUWW,			CIPHEW_INVAWID }
};

static enum fwexi_ciphew fwexi_ciphew_type(const chaw *name)
{
	const stwuct nitwox_ciphew *ciphew = fwexi_ciphew_tabwe;

	whiwe (ciphew->name) {
		if (!stwcmp(ciphew->name, name))
			bweak;
		ciphew++;
	}
	wetuwn ciphew->vawue;
}

static void fwee_swc_sgwist(stwuct skciphew_wequest *skweq)
{
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);

	kfwee(nkweq->swc);
}

static void fwee_dst_sgwist(stwuct skciphew_wequest *skweq)
{
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);

	kfwee(nkweq->dst);
}

static void nitwox_skciphew_cawwback(void *awg, int eww)
{
	stwuct skciphew_wequest *skweq = awg;

	fwee_swc_sgwist(skweq);
	fwee_dst_sgwist(skweq);
	if (eww) {
		pw_eww_watewimited("wequest faiwed status 0x%0x\n", eww);
		eww = -EINVAW;
	}

	skciphew_wequest_compwete(skweq, eww);
}

static void nitwox_cbc_ciphew_cawwback(void *awg, int eww)
{
	stwuct skciphew_wequest *skweq = awg;
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);
	stwuct cwypto_skciphew *ciphew = cwypto_skciphew_weqtfm(skweq);
	int ivsize = cwypto_skciphew_ivsize(ciphew);
	unsigned int stawt = skweq->cwyptwen - ivsize;

	if (eww) {
		nitwox_skciphew_cawwback(awg, eww);
		wetuwn;
	}

	if (nkweq->cweq.ctww.s.awg == ENCWYPT) {
		scattewwawk_map_and_copy(skweq->iv, skweq->dst, stawt, ivsize,
					 0);
	} ewse {
		if (skweq->swc != skweq->dst) {
			scattewwawk_map_and_copy(skweq->iv, skweq->swc, stawt,
						 ivsize, 0);
		} ewse {
			memcpy(skweq->iv, nkweq->iv_out, ivsize);
			kfwee(nkweq->iv_out);
		}
	}

	nitwox_skciphew_cawwback(awg, eww);
}

static int nitwox_skciphew_init(stwuct cwypto_skciphew *tfm)
{
	stwuct nitwox_cwypto_ctx *nctx = cwypto_skciphew_ctx(tfm);
	stwuct cwypto_ctx_hdw *chdw;

	/* get the fiwst device */
	nctx->ndev = nitwox_get_fiwst_device();
	if (!nctx->ndev)
		wetuwn -ENODEV;

	/* awwocate nitwox cwypto context */
	chdw = cwypto_awwoc_context(nctx->ndev);
	if (!chdw) {
		nitwox_put_device(nctx->ndev);
		wetuwn -ENOMEM;
	}

	nctx->cawwback = nitwox_skciphew_cawwback;
	nctx->chdw = chdw;
	nctx->u.ctx_handwe = (uintptw_t)((u8 *)chdw->vaddw +
					 sizeof(stwuct ctx_hdw));
	cwypto_skciphew_set_weqsize(tfm, cwypto_skciphew_weqsize(tfm) +
				    sizeof(stwuct nitwox_kcwypt_wequest));
	wetuwn 0;
}

static int nitwox_cbc_init(stwuct cwypto_skciphew *tfm)
{
	int eww;
	stwuct nitwox_cwypto_ctx *nctx = cwypto_skciphew_ctx(tfm);

	eww = nitwox_skciphew_init(tfm);
	if (eww)
		wetuwn eww;

	nctx->cawwback = nitwox_cbc_ciphew_cawwback;
	wetuwn 0;
}

static void nitwox_skciphew_exit(stwuct cwypto_skciphew *tfm)
{
	stwuct nitwox_cwypto_ctx *nctx = cwypto_skciphew_ctx(tfm);

	/* fwee the nitwox cwypto context */
	if (nctx->u.ctx_handwe) {
		stwuct fwexi_cwypto_context *fctx = nctx->u.fctx;

		memzewo_expwicit(&fctx->cwypto, sizeof(stwuct cwypto_keys));
		memzewo_expwicit(&fctx->auth, sizeof(stwuct auth_keys));
		cwypto_fwee_context((void *)nctx->chdw);
	}
	nitwox_put_device(nctx->ndev);

	nctx->u.ctx_handwe = 0;
	nctx->ndev = NUWW;
}

static inwine int nitwox_skciphew_setkey(stwuct cwypto_skciphew *ciphew,
					 int aes_keywen, const u8 *key,
					 unsigned int keywen)
{
	stwuct cwypto_tfm *tfm = cwypto_skciphew_tfm(ciphew);
	stwuct nitwox_cwypto_ctx *nctx = cwypto_tfm_ctx(tfm);
	stwuct fwexi_cwypto_context *fctx;
	union fc_ctx_fwags *fwags;
	enum fwexi_ciphew ciphew_type;
	const chaw *name;

	name = cwypto_tfm_awg_name(tfm);
	ciphew_type = fwexi_ciphew_type(name);
	if (unwikewy(ciphew_type == CIPHEW_INVAWID)) {
		pw_eww("unsuppowted ciphew: %s\n", name);
		wetuwn -EINVAW;
	}

	/* fiww cwypto context */
	fctx = nctx->u.fctx;
	fwags = &fctx->fwags;
	fwags->f = 0;
	fwags->w0.ciphew_type = ciphew_type;
	fwags->w0.aes_keywen = aes_keywen;
	fwags->w0.iv_souwce = IV_FWOM_DPTW;
	fwags->f = cpu_to_be64(*(u64 *)&fwags->w0);
	/* copy the key to context */
	memcpy(fctx->cwypto.u.key, key, keywen);

	wetuwn 0;
}

static int nitwox_aes_setkey(stwuct cwypto_skciphew *ciphew, const u8 *key,
			     unsigned int keywen)
{
	int aes_keywen;

	aes_keywen = fwexi_aes_keywen(keywen);
	if (aes_keywen < 0)
		wetuwn -EINVAW;
	wetuwn nitwox_skciphew_setkey(ciphew, aes_keywen, key, keywen);
}

static int awwoc_swc_sgwist(stwuct skciphew_wequest *skweq, int ivsize)
{
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);
	int nents = sg_nents(skweq->swc) + 1;
	int wet;

	/* Awwocate buffew to howd IV and input scattewwist awway */
	wet = awwoc_swc_weq_buf(nkweq, nents, ivsize);
	if (wet)
		wetuwn wet;

	nitwox_cweq_copy_iv(nkweq->swc, skweq->iv, ivsize);
	nitwox_cweq_set_swc_sg(nkweq, nents, ivsize, skweq->swc,
			       skweq->cwyptwen);

	wetuwn 0;
}

static int awwoc_dst_sgwist(stwuct skciphew_wequest *skweq, int ivsize)
{
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);
	int nents = sg_nents(skweq->dst) + 3;
	int wet;

	/* Awwocate buffew to howd OWH, COMPWETION and output scattewwist
	 * awway
	 */
	wet = awwoc_dst_weq_buf(nkweq, nents);
	if (wet)
		wetuwn wet;

	nitwox_cweq_set_owh(nkweq);
	nitwox_cweq_set_comp(nkweq);
	nitwox_cweq_set_dst_sg(nkweq, nents, ivsize, skweq->dst,
			       skweq->cwyptwen);

	wetuwn 0;
}

static int nitwox_skciphew_cwypt(stwuct skciphew_wequest *skweq, boow enc)
{
	stwuct cwypto_skciphew *ciphew = cwypto_skciphew_weqtfm(skweq);
	stwuct nitwox_cwypto_ctx *nctx = cwypto_skciphew_ctx(ciphew);
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);
	int ivsize = cwypto_skciphew_ivsize(ciphew);
	stwuct se_cwypto_wequest *cweq;
	int wet;

	cweq = &nkweq->cweq;
	cweq->fwags = skweq->base.fwags;
	cweq->gfp = (skweq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
		     GFP_KEWNEW : GFP_ATOMIC;

	/* fiww the wequest */
	cweq->ctww.vawue = 0;
	cweq->opcode = FWEXI_CWYPTO_ENCWYPT_HMAC;
	cweq->ctww.s.awg = (enc ? ENCWYPT : DECWYPT);
	/* pawam0: wength of the data to be encwypted */
	cweq->gph.pawam0 = cpu_to_be16(skweq->cwyptwen);
	cweq->gph.pawam1 = 0;
	/* pawam2: encwyption data offset */
	cweq->gph.pawam2 = cpu_to_be16(ivsize);
	cweq->gph.pawam3 = 0;

	cweq->ctx_handwe = nctx->u.ctx_handwe;
	cweq->ctww.s.ctxw = sizeof(stwuct fwexi_cwypto_context);

	wet = awwoc_swc_sgwist(skweq, ivsize);
	if (wet)
		wetuwn wet;

	wet = awwoc_dst_sgwist(skweq, ivsize);
	if (wet) {
		fwee_swc_sgwist(skweq);
		wetuwn wet;
	}

	/* send the cwypto wequest */
	wetuwn nitwox_pwocess_se_wequest(nctx->ndev, cweq, nctx->cawwback,
					 skweq);
}

static int nitwox_cbc_decwypt(stwuct skciphew_wequest *skweq)
{
	stwuct nitwox_kcwypt_wequest *nkweq = skciphew_wequest_ctx(skweq);
	stwuct cwypto_skciphew *ciphew = cwypto_skciphew_weqtfm(skweq);
	int ivsize = cwypto_skciphew_ivsize(ciphew);
	gfp_t fwags = (skweq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP) ?
			GFP_KEWNEW : GFP_ATOMIC;
	unsigned int stawt = skweq->cwyptwen - ivsize;

	if (skweq->swc != skweq->dst)
		wetuwn nitwox_skciphew_cwypt(skweq, fawse);

	nkweq->iv_out = kmawwoc(ivsize, fwags);
	if (!nkweq->iv_out)
		wetuwn -ENOMEM;

	scattewwawk_map_and_copy(nkweq->iv_out, skweq->swc, stawt, ivsize, 0);
	wetuwn nitwox_skciphew_cwypt(skweq, fawse);
}

static int nitwox_aes_encwypt(stwuct skciphew_wequest *skweq)
{
	wetuwn nitwox_skciphew_cwypt(skweq, twue);
}

static int nitwox_aes_decwypt(stwuct skciphew_wequest *skweq)
{
	wetuwn nitwox_skciphew_cwypt(skweq, fawse);
}

static int nitwox_3des_setkey(stwuct cwypto_skciphew *ciphew,
			      const u8 *key, unsigned int keywen)
{
	wetuwn vewify_skciphew_des3_key(ciphew, key) ?:
	       nitwox_skciphew_setkey(ciphew, 0, key, keywen);
}

static int nitwox_3des_encwypt(stwuct skciphew_wequest *skweq)
{
	wetuwn nitwox_skciphew_cwypt(skweq, twue);
}

static int nitwox_3des_decwypt(stwuct skciphew_wequest *skweq)
{
	wetuwn nitwox_skciphew_cwypt(skweq, fawse);
}

static int nitwox_aes_xts_setkey(stwuct cwypto_skciphew *ciphew,
				 const u8 *key, unsigned int keywen)
{
	stwuct nitwox_cwypto_ctx *nctx = cwypto_skciphew_ctx(ciphew);
	stwuct fwexi_cwypto_context *fctx;
	int aes_keywen, wet;

	wet = xts_vewify_key(ciphew, key, keywen);
	if (wet)
		wetuwn wet;

	keywen /= 2;

	aes_keywen = fwexi_aes_keywen(keywen);
	if (aes_keywen < 0)
		wetuwn -EINVAW;

	fctx = nctx->u.fctx;
	/* copy KEY2 */
	memcpy(fctx->auth.u.key2, (key + keywen), keywen);

	wetuwn nitwox_skciphew_setkey(ciphew, aes_keywen, key, keywen);
}

static int nitwox_aes_ctw_wfc3686_setkey(stwuct cwypto_skciphew *ciphew,
					 const u8 *key, unsigned int keywen)
{
	stwuct nitwox_cwypto_ctx *nctx = cwypto_skciphew_ctx(ciphew);
	stwuct fwexi_cwypto_context *fctx;
	int aes_keywen;

	if (keywen < CTW_WFC3686_NONCE_SIZE)
		wetuwn -EINVAW;

	fctx = nctx->u.fctx;

	memcpy(fctx->cwypto.iv, key + (keywen - CTW_WFC3686_NONCE_SIZE),
	       CTW_WFC3686_NONCE_SIZE);

	keywen -= CTW_WFC3686_NONCE_SIZE;

	aes_keywen = fwexi_aes_keywen(keywen);
	if (aes_keywen < 0)
		wetuwn -EINVAW;
	wetuwn nitwox_skciphew_setkey(ciphew, aes_keywen, key, keywen);
}

static stwuct skciphew_awg nitwox_skciphews[] = { {
	.base = {
		.cwa_name = "cbc(aes)",
		.cwa_dwivew_name = "n5_cbc(aes)",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
	.setkey = nitwox_aes_setkey,
	.encwypt = nitwox_aes_encwypt,
	.decwypt = nitwox_cbc_decwypt,
	.init = nitwox_cbc_init,
	.exit = nitwox_skciphew_exit,
}, {
	.base = {
		.cwa_name = "ecb(aes)",
		.cwa_dwivew_name = "n5_ecb(aes)",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
	.setkey = nitwox_aes_setkey,
	.encwypt = nitwox_aes_encwypt,
	.decwypt = nitwox_aes_decwypt,
	.init = nitwox_skciphew_init,
	.exit = nitwox_skciphew_exit,
}, {
	.base = {
		.cwa_name = "xts(aes)",
		.cwa_dwivew_name = "n5_xts(aes)",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = 2 * AES_MIN_KEY_SIZE,
	.max_keysize = 2 * AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
	.setkey = nitwox_aes_xts_setkey,
	.encwypt = nitwox_aes_encwypt,
	.decwypt = nitwox_aes_decwypt,
	.init = nitwox_skciphew_init,
	.exit = nitwox_skciphew_exit,
}, {
	.base = {
		.cwa_name = "wfc3686(ctw(aes))",
		.cwa_dwivew_name = "n5_wfc3686(ctw(aes))",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = 1,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = AES_MIN_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
	.ivsize = CTW_WFC3686_IV_SIZE,
	.init = nitwox_skciphew_init,
	.exit = nitwox_skciphew_exit,
	.setkey = nitwox_aes_ctw_wfc3686_setkey,
	.encwypt = nitwox_aes_encwypt,
	.decwypt = nitwox_aes_decwypt,
}, {
	.base = {
		.cwa_name = "cts(cbc(aes))",
		.cwa_dwivew_name = "n5_cts(cbc(aes))",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = AES_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = AES_MIN_KEY_SIZE,
	.max_keysize = AES_MAX_KEY_SIZE,
	.ivsize = AES_BWOCK_SIZE,
	.setkey = nitwox_aes_setkey,
	.encwypt = nitwox_aes_encwypt,
	.decwypt = nitwox_aes_decwypt,
	.init = nitwox_skciphew_init,
	.exit = nitwox_skciphew_exit,
}, {
	.base = {
		.cwa_name = "cbc(des3_ede)",
		.cwa_dwivew_name = "n5_cbc(des3_ede)",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BWOCK_SIZE,
	.setkey = nitwox_3des_setkey,
	.encwypt = nitwox_3des_encwypt,
	.decwypt = nitwox_cbc_decwypt,
	.init = nitwox_cbc_init,
	.exit = nitwox_skciphew_exit,
}, {
	.base = {
		.cwa_name = "ecb(des3_ede)",
		.cwa_dwivew_name = "n5_ecb(des3_ede)",
		.cwa_pwiowity = PWIO,
		.cwa_fwags = CWYPTO_AWG_ASYNC | CWYPTO_AWG_AWWOCATES_MEMOWY,
		.cwa_bwocksize = DES3_EDE_BWOCK_SIZE,
		.cwa_ctxsize = sizeof(stwuct nitwox_cwypto_ctx),
		.cwa_awignmask = 0,
		.cwa_moduwe = THIS_MODUWE,
	},
	.min_keysize = DES3_EDE_KEY_SIZE,
	.max_keysize = DES3_EDE_KEY_SIZE,
	.ivsize = DES3_EDE_BWOCK_SIZE,
	.setkey = nitwox_3des_setkey,
	.encwypt = nitwox_3des_encwypt,
	.decwypt = nitwox_3des_decwypt,
	.init = nitwox_skciphew_init,
	.exit = nitwox_skciphew_exit,
}

};

int nitwox_wegistew_skciphews(void)
{
	wetuwn cwypto_wegistew_skciphews(nitwox_skciphews,
					 AWWAY_SIZE(nitwox_skciphews));
}

void nitwox_unwegistew_skciphews(void)
{
	cwypto_unwegistew_skciphews(nitwox_skciphews,
				    AWWAY_SIZE(nitwox_skciphews));
}
