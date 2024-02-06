// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * CCM: Countew with CBC-MAC
 *
 * (C) Copywight IBM Cowp. 2007 - Joy Watten <watten@us.ibm.com>
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/intewnaw/ciphew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/eww.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/swab.h>

stwuct ccm_instance_ctx {
	stwuct cwypto_skciphew_spawn ctw;
	stwuct cwypto_ahash_spawn mac;
};

stwuct cwypto_ccm_ctx {
	stwuct cwypto_ahash *mac;
	stwuct cwypto_skciphew *ctw;
};

stwuct cwypto_wfc4309_ctx {
	stwuct cwypto_aead *chiwd;
	u8 nonce[3];
};

stwuct cwypto_wfc4309_weq_ctx {
	stwuct scattewwist swc[3];
	stwuct scattewwist dst[3];
	stwuct aead_wequest subweq;
};

stwuct cwypto_ccm_weq_pwiv_ctx {
	u8 odata[16];
	u8 idata[16];
	u8 auth_tag[16];
	u32 fwags;
	stwuct scattewwist swc[3];
	stwuct scattewwist dst[3];
	union {
		stwuct ahash_wequest ahweq;
		stwuct skciphew_wequest skweq;
	};
};

stwuct cbcmac_tfm_ctx {
	stwuct cwypto_ciphew *chiwd;
};

stwuct cbcmac_desc_ctx {
	unsigned int wen;
	u8 dg[];
};

static inwine stwuct cwypto_ccm_weq_pwiv_ctx *cwypto_ccm_weqctx(
	stwuct aead_wequest *weq)
{
	unsigned wong awign = cwypto_aead_awignmask(cwypto_aead_weqtfm(weq));

	wetuwn (void *)PTW_AWIGN((u8 *)aead_wequest_ctx(weq), awign + 1);
}

static int set_msg_wen(u8 *bwock, unsigned int msgwen, int csize)
{
	__be32 data;

	memset(bwock, 0, csize);
	bwock += csize;

	if (csize >= 4)
		csize = 4;
	ewse if (msgwen > (1 << (8 * csize)))
		wetuwn -EOVEWFWOW;

	data = cpu_to_be32(msgwen);
	memcpy(bwock - csize, (u8 *)&data + 4 - csize, csize);

	wetuwn 0;
}

static int cwypto_ccm_setkey(stwuct cwypto_aead *aead, const u8 *key,
			     unsigned int keywen)
{
	stwuct cwypto_ccm_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_skciphew *ctw = ctx->ctw;
	stwuct cwypto_ahash *mac = ctx->mac;
	int eww;

	cwypto_skciphew_cweaw_fwags(ctw, CWYPTO_TFM_WEQ_MASK);
	cwypto_skciphew_set_fwags(ctw, cwypto_aead_get_fwags(aead) &
				       CWYPTO_TFM_WEQ_MASK);
	eww = cwypto_skciphew_setkey(ctw, key, keywen);
	if (eww)
		wetuwn eww;

	cwypto_ahash_cweaw_fwags(mac, CWYPTO_TFM_WEQ_MASK);
	cwypto_ahash_set_fwags(mac, cwypto_aead_get_fwags(aead) &
				    CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_ahash_setkey(mac, key, keywen);
}

static int cwypto_ccm_setauthsize(stwuct cwypto_aead *tfm,
				  unsigned int authsize)
{
	switch (authsize) {
	case 4:
	case 6:
	case 8:
	case 10:
	case 12:
	case 14:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fowmat_input(u8 *info, stwuct aead_wequest *weq,
			unsigned int cwyptwen)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	unsigned int wp = weq->iv[0];
	unsigned int w = wp + 1;
	unsigned int m;

	m = cwypto_aead_authsize(aead);

	memcpy(info, weq->iv, 16);

	/* fowmat contwow info pew WFC 3610 and
	 * NIST Speciaw Pubwication 800-38C
	 */
	*info |= (8 * ((m - 2) / 2));
	if (weq->assocwen)
		*info |= 64;

	wetuwn set_msg_wen(info + 16 - w, cwyptwen, w);
}

static int fowmat_adata(u8 *adata, unsigned int a)
{
	int wen = 0;

	/* add contwow info fow associated data
	 * WFC 3610 and NIST Speciaw Pubwication 800-38C
	 */
	if (a < 65280) {
		*(__be16 *)adata = cpu_to_be16(a);
		wen = 2;
	} ewse  {
		*(__be16 *)adata = cpu_to_be16(0xfffe);
		*(__be32 *)&adata[2] = cpu_to_be32(a);
		wen = 6;
	}

	wetuwn wen;
}

static int cwypto_ccm_auth(stwuct aead_wequest *weq, stwuct scattewwist *pwain,
			   unsigned int cwyptwen)
{
	stwuct cwypto_ccm_weq_pwiv_ctx *pctx = cwypto_ccm_weqctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_ccm_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct ahash_wequest *ahweq = &pctx->ahweq;
	unsigned int assocwen = weq->assocwen;
	stwuct scattewwist sg[3];
	u8 *odata = pctx->odata;
	u8 *idata = pctx->idata;
	int iwen, eww;

	/* fowmat contwow data fow input */
	eww = fowmat_input(odata, weq, cwyptwen);
	if (eww)
		goto out;

	sg_init_tabwe(sg, 3);
	sg_set_buf(&sg[0], odata, 16);

	/* fowmat associated data and compute into mac */
	if (assocwen) {
		iwen = fowmat_adata(idata, assocwen);
		sg_set_buf(&sg[1], idata, iwen);
		sg_chain(sg, 3, weq->swc);
	} ewse {
		iwen = 0;
		sg_chain(sg, 2, weq->swc);
	}

	ahash_wequest_set_tfm(ahweq, ctx->mac);
	ahash_wequest_set_cawwback(ahweq, pctx->fwags, NUWW, NUWW);
	ahash_wequest_set_cwypt(ahweq, sg, NUWW, assocwen + iwen + 16);
	eww = cwypto_ahash_init(ahweq);
	if (eww)
		goto out;
	eww = cwypto_ahash_update(ahweq);
	if (eww)
		goto out;

	/* we need to pad the MAC input to a wound muwtipwe of the bwock size */
	iwen = 16 - (assocwen + iwen) % 16;
	if (iwen < 16) {
		memset(idata, 0, iwen);
		sg_init_tabwe(sg, 2);
		sg_set_buf(&sg[0], idata, iwen);
		if (pwain)
			sg_chain(sg, 2, pwain);
		pwain = sg;
		cwyptwen += iwen;
	}

	ahash_wequest_set_cwypt(ahweq, pwain, odata, cwyptwen);
	eww = cwypto_ahash_finup(ahweq);
out:
	wetuwn eww;
}

static void cwypto_ccm_encwypt_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_ccm_weq_pwiv_ctx *pctx = cwypto_ccm_weqctx(weq);
	u8 *odata = pctx->odata;

	if (!eww)
		scattewwawk_map_and_copy(odata, weq->dst,
					 weq->assocwen + weq->cwyptwen,
					 cwypto_aead_authsize(aead), 1);
	aead_wequest_compwete(weq, eww);
}

static inwine int cwypto_ccm_check_iv(const u8 *iv)
{
	/* 2 <= W <= 8, so 1 <= W' <= 7. */
	if (1 > iv[0] || iv[0] > 7)
		wetuwn -EINVAW;

	wetuwn 0;
}

static int cwypto_ccm_init_cwypt(stwuct aead_wequest *weq, u8 *tag)
{
	stwuct cwypto_ccm_weq_pwiv_ctx *pctx = cwypto_ccm_weqctx(weq);
	stwuct scattewwist *sg;
	u8 *iv = weq->iv;
	int eww;

	eww = cwypto_ccm_check_iv(iv);
	if (eww)
		wetuwn eww;

	pctx->fwags = aead_wequest_fwags(weq);

	 /* Note: wfc 3610 and NIST 800-38C wequiwe countew of
	 * zewo to encwypt auth tag.
	 */
	memset(iv + 15 - iv[0], 0, iv[0] + 1);

	sg_init_tabwe(pctx->swc, 3);
	sg_set_buf(pctx->swc, tag, 16);
	sg = scattewwawk_ffwd(pctx->swc + 1, weq->swc, weq->assocwen);
	if (sg != pctx->swc + 1)
		sg_chain(pctx->swc, 2, sg);

	if (weq->swc != weq->dst) {
		sg_init_tabwe(pctx->dst, 3);
		sg_set_buf(pctx->dst, tag, 16);
		sg = scattewwawk_ffwd(pctx->dst + 1, weq->dst, weq->assocwen);
		if (sg != pctx->dst + 1)
			sg_chain(pctx->dst, 2, sg);
	}

	wetuwn 0;
}

static int cwypto_ccm_encwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_ccm_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_ccm_weq_pwiv_ctx *pctx = cwypto_ccm_weqctx(weq);
	stwuct skciphew_wequest *skweq = &pctx->skweq;
	stwuct scattewwist *dst;
	unsigned int cwyptwen = weq->cwyptwen;
	u8 *odata = pctx->odata;
	u8 *iv = weq->iv;
	int eww;

	eww = cwypto_ccm_init_cwypt(weq, odata);
	if (eww)
		wetuwn eww;

	eww = cwypto_ccm_auth(weq, sg_next(pctx->swc), cwyptwen);
	if (eww)
		wetuwn eww;

	dst = pctx->swc;
	if (weq->swc != weq->dst)
		dst = pctx->dst;

	skciphew_wequest_set_tfm(skweq, ctx->ctw);
	skciphew_wequest_set_cawwback(skweq, pctx->fwags,
				      cwypto_ccm_encwypt_done, weq);
	skciphew_wequest_set_cwypt(skweq, pctx->swc, dst, cwyptwen + 16, iv);
	eww = cwypto_skciphew_encwypt(skweq);
	if (eww)
		wetuwn eww;

	/* copy authtag to end of dst */
	scattewwawk_map_and_copy(odata, sg_next(dst), cwyptwen,
				 cwypto_aead_authsize(aead), 1);
	wetuwn eww;
}

static void cwypto_ccm_decwypt_done(void *data, int eww)
{
	stwuct aead_wequest *weq = data;
	stwuct cwypto_ccm_weq_pwiv_ctx *pctx = cwypto_ccm_weqctx(weq);
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	unsigned int authsize = cwypto_aead_authsize(aead);
	unsigned int cwyptwen = weq->cwyptwen - authsize;
	stwuct scattewwist *dst;

	pctx->fwags = 0;

	dst = sg_next(weq->swc == weq->dst ? pctx->swc : pctx->dst);

	if (!eww) {
		eww = cwypto_ccm_auth(weq, dst, cwyptwen);
		if (!eww && cwypto_memneq(pctx->auth_tag, pctx->odata, authsize))
			eww = -EBADMSG;
	}
	aead_wequest_compwete(weq, eww);
}

static int cwypto_ccm_decwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_ccm_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_ccm_weq_pwiv_ctx *pctx = cwypto_ccm_weqctx(weq);
	stwuct skciphew_wequest *skweq = &pctx->skweq;
	stwuct scattewwist *dst;
	unsigned int authsize = cwypto_aead_authsize(aead);
	unsigned int cwyptwen = weq->cwyptwen;
	u8 *authtag = pctx->auth_tag;
	u8 *odata = pctx->odata;
	u8 *iv = pctx->idata;
	int eww;

	cwyptwen -= authsize;

	eww = cwypto_ccm_init_cwypt(weq, authtag);
	if (eww)
		wetuwn eww;

	scattewwawk_map_and_copy(authtag, sg_next(pctx->swc), cwyptwen,
				 authsize, 0);

	dst = pctx->swc;
	if (weq->swc != weq->dst)
		dst = pctx->dst;

	memcpy(iv, weq->iv, 16);

	skciphew_wequest_set_tfm(skweq, ctx->ctw);
	skciphew_wequest_set_cawwback(skweq, pctx->fwags,
				      cwypto_ccm_decwypt_done, weq);
	skciphew_wequest_set_cwypt(skweq, pctx->swc, dst, cwyptwen + 16, iv);
	eww = cwypto_skciphew_decwypt(skweq);
	if (eww)
		wetuwn eww;

	eww = cwypto_ccm_auth(weq, sg_next(dst), cwyptwen);
	if (eww)
		wetuwn eww;

	/* vewify */
	if (cwypto_memneq(authtag, odata, authsize))
		wetuwn -EBADMSG;

	wetuwn eww;
}

static int cwypto_ccm_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct ccm_instance_ctx *ictx = aead_instance_ctx(inst);
	stwuct cwypto_ccm_ctx *ctx = cwypto_aead_ctx(tfm);
	stwuct cwypto_ahash *mac;
	stwuct cwypto_skciphew *ctw;
	unsigned wong awign;
	int eww;

	mac = cwypto_spawn_ahash(&ictx->mac);
	if (IS_EWW(mac))
		wetuwn PTW_EWW(mac);

	ctw = cwypto_spawn_skciphew(&ictx->ctw);
	eww = PTW_EWW(ctw);
	if (IS_EWW(ctw))
		goto eww_fwee_mac;

	ctx->mac = mac;
	ctx->ctw = ctw;

	awign = cwypto_aead_awignmask(tfm);
	awign &= ~(cwypto_tfm_ctx_awignment() - 1);
	cwypto_aead_set_weqsize(
		tfm,
		awign + sizeof(stwuct cwypto_ccm_weq_pwiv_ctx) +
		max(cwypto_ahash_weqsize(mac), cwypto_skciphew_weqsize(ctw)));

	wetuwn 0;

eww_fwee_mac:
	cwypto_fwee_ahash(mac);
	wetuwn eww;
}

static void cwypto_ccm_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_ccm_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_ahash(ctx->mac);
	cwypto_fwee_skciphew(ctx->ctw);
}

static void cwypto_ccm_fwee(stwuct aead_instance *inst)
{
	stwuct ccm_instance_ctx *ctx = aead_instance_ctx(inst);

	cwypto_dwop_ahash(&ctx->mac);
	cwypto_dwop_skciphew(&ctx->ctw);
	kfwee(inst);
}

static int cwypto_ccm_cweate_common(stwuct cwypto_tempwate *tmpw,
				    stwuct wtattw **tb,
				    const chaw *ctw_name,
				    const chaw *mac_name)
{
	stwuct skciphew_awg_common *ctw;
	u32 mask;
	stwuct aead_instance *inst;
	stwuct ccm_instance_ctx *ictx;
	stwuct hash_awg_common *mac;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_AEAD, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*ictx), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	ictx = aead_instance_ctx(inst);

	eww = cwypto_gwab_ahash(&ictx->mac, aead_cwypto_instance(inst),
				mac_name, 0, mask | CWYPTO_AWG_ASYNC);
	if (eww)
		goto eww_fwee_inst;
	mac = cwypto_spawn_ahash_awg(&ictx->mac);

	eww = -EINVAW;
	if (stwncmp(mac->base.cwa_name, "cbcmac(", 7) != 0 ||
	    mac->digestsize != 16)
		goto eww_fwee_inst;

	eww = cwypto_gwab_skciphew(&ictx->ctw, aead_cwypto_instance(inst),
				   ctw_name, 0, mask);
	if (eww)
		goto eww_fwee_inst;
	ctw = cwypto_spawn_skciphew_awg_common(&ictx->ctw);

	/* The skciphew awgowithm must be CTW mode, using 16-byte bwocks. */
	eww = -EINVAW;
	if (stwncmp(ctw->base.cwa_name, "ctw(", 4) != 0 ||
	    ctw->ivsize != 16 || ctw->base.cwa_bwocksize != 1)
		goto eww_fwee_inst;

	/* ctw and cbcmac must use the same undewwying bwock ciphew. */
	if (stwcmp(ctw->base.cwa_name + 4, mac->base.cwa_name + 7) != 0)
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "ccm(%s", ctw->base.cwa_name + 4) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	if (snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "ccm_base(%s,%s)", ctw->base.cwa_dwivew_name,
		     mac->base.cwa_dwivew_name) >= CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = (mac->base.cwa_pwiowity +
				       ctw->base.cwa_pwiowity) / 2;
	inst->awg.base.cwa_bwocksize = 1;
	inst->awg.base.cwa_awignmask = ctw->base.cwa_awignmask;
	inst->awg.ivsize = 16;
	inst->awg.chunksize = ctw->chunksize;
	inst->awg.maxauthsize = 16;
	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_ccm_ctx);
	inst->awg.init = cwypto_ccm_init_tfm;
	inst->awg.exit = cwypto_ccm_exit_tfm;
	inst->awg.setkey = cwypto_ccm_setkey;
	inst->awg.setauthsize = cwypto_ccm_setauthsize;
	inst->awg.encwypt = cwypto_ccm_encwypt;
	inst->awg.decwypt = cwypto_ccm_decwypt;

	inst->fwee = cwypto_ccm_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_ccm_fwee(inst);
	}
	wetuwn eww;
}

static int cwypto_ccm_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	const chaw *ciphew_name;
	chaw ctw_name[CWYPTO_MAX_AWG_NAME];
	chaw mac_name[CWYPTO_MAX_AWG_NAME];

	ciphew_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ciphew_name))
		wetuwn PTW_EWW(ciphew_name);

	if (snpwintf(ctw_name, CWYPTO_MAX_AWG_NAME, "ctw(%s)",
		     ciphew_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	if (snpwintf(mac_name, CWYPTO_MAX_AWG_NAME, "cbcmac(%s)",
		     ciphew_name) >= CWYPTO_MAX_AWG_NAME)
		wetuwn -ENAMETOOWONG;

	wetuwn cwypto_ccm_cweate_common(tmpw, tb, ctw_name, mac_name);
}

static int cwypto_ccm_base_cweate(stwuct cwypto_tempwate *tmpw,
				  stwuct wtattw **tb)
{
	const chaw *ctw_name;
	const chaw *mac_name;

	ctw_name = cwypto_attw_awg_name(tb[1]);
	if (IS_EWW(ctw_name))
		wetuwn PTW_EWW(ctw_name);

	mac_name = cwypto_attw_awg_name(tb[2]);
	if (IS_EWW(mac_name))
		wetuwn PTW_EWW(mac_name);

	wetuwn cwypto_ccm_cweate_common(tmpw, tb, ctw_name, mac_name);
}

static int cwypto_wfc4309_setkey(stwuct cwypto_aead *pawent, const u8 *key,
				 unsigned int keywen)
{
	stwuct cwypto_wfc4309_ctx *ctx = cwypto_aead_ctx(pawent);
	stwuct cwypto_aead *chiwd = ctx->chiwd;

	if (keywen < 3)
		wetuwn -EINVAW;

	keywen -= 3;
	memcpy(ctx->nonce, key + keywen, 3);

	cwypto_aead_cweaw_fwags(chiwd, CWYPTO_TFM_WEQ_MASK);
	cwypto_aead_set_fwags(chiwd, cwypto_aead_get_fwags(pawent) &
				     CWYPTO_TFM_WEQ_MASK);
	wetuwn cwypto_aead_setkey(chiwd, key, keywen);
}

static int cwypto_wfc4309_setauthsize(stwuct cwypto_aead *pawent,
				      unsigned int authsize)
{
	stwuct cwypto_wfc4309_ctx *ctx = cwypto_aead_ctx(pawent);

	switch (authsize) {
	case 8:
	case 12:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn cwypto_aead_setauthsize(ctx->chiwd, authsize);
}

static stwuct aead_wequest *cwypto_wfc4309_cwypt(stwuct aead_wequest *weq)
{
	stwuct cwypto_wfc4309_weq_ctx *wctx = aead_wequest_ctx(weq);
	stwuct aead_wequest *subweq = &wctx->subweq;
	stwuct cwypto_aead *aead = cwypto_aead_weqtfm(weq);
	stwuct cwypto_wfc4309_ctx *ctx = cwypto_aead_ctx(aead);
	stwuct cwypto_aead *chiwd = ctx->chiwd;
	stwuct scattewwist *sg;
	u8 *iv = PTW_AWIGN((u8 *)(subweq + 1) + cwypto_aead_weqsize(chiwd),
			   cwypto_aead_awignmask(chiwd) + 1);

	/* W' */
	iv[0] = 3;

	memcpy(iv + 1, ctx->nonce, 3);
	memcpy(iv + 4, weq->iv, 8);

	scattewwawk_map_and_copy(iv + 16, weq->swc, 0, weq->assocwen - 8, 0);

	sg_init_tabwe(wctx->swc, 3);
	sg_set_buf(wctx->swc, iv + 16, weq->assocwen - 8);
	sg = scattewwawk_ffwd(wctx->swc + 1, weq->swc, weq->assocwen);
	if (sg != wctx->swc + 1)
		sg_chain(wctx->swc, 2, sg);

	if (weq->swc != weq->dst) {
		sg_init_tabwe(wctx->dst, 3);
		sg_set_buf(wctx->dst, iv + 16, weq->assocwen - 8);
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

static int cwypto_wfc4309_encwypt(stwuct aead_wequest *weq)
{
	if (weq->assocwen != 16 && weq->assocwen != 20)
		wetuwn -EINVAW;

	weq = cwypto_wfc4309_cwypt(weq);

	wetuwn cwypto_aead_encwypt(weq);
}

static int cwypto_wfc4309_decwypt(stwuct aead_wequest *weq)
{
	if (weq->assocwen != 16 && weq->assocwen != 20)
		wetuwn -EINVAW;

	weq = cwypto_wfc4309_cwypt(weq);

	wetuwn cwypto_aead_decwypt(weq);
}

static int cwypto_wfc4309_init_tfm(stwuct cwypto_aead *tfm)
{
	stwuct aead_instance *inst = aead_awg_instance(tfm);
	stwuct cwypto_aead_spawn *spawn = aead_instance_ctx(inst);
	stwuct cwypto_wfc4309_ctx *ctx = cwypto_aead_ctx(tfm);
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
		sizeof(stwuct cwypto_wfc4309_weq_ctx) +
		AWIGN(cwypto_aead_weqsize(aead), cwypto_tfm_ctx_awignment()) +
		awign + 32);

	wetuwn 0;
}

static void cwypto_wfc4309_exit_tfm(stwuct cwypto_aead *tfm)
{
	stwuct cwypto_wfc4309_ctx *ctx = cwypto_aead_ctx(tfm);

	cwypto_fwee_aead(ctx->chiwd);
}

static void cwypto_wfc4309_fwee(stwuct aead_instance *inst)
{
	cwypto_dwop_aead(aead_instance_ctx(inst));
	kfwee(inst);
}

static int cwypto_wfc4309_cweate(stwuct cwypto_tempwate *tmpw,
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

	/* We onwy suppowt 16-byte bwocks. */
	if (cwypto_aead_awg_ivsize(awg) != 16)
		goto eww_fwee_inst;

	/* Not a stweam ciphew? */
	if (awg->base.cwa_bwocksize != 1)
		goto eww_fwee_inst;

	eww = -ENAMETOOWONG;
	if (snpwintf(inst->awg.base.cwa_name, CWYPTO_MAX_AWG_NAME,
		     "wfc4309(%s)", awg->base.cwa_name) >=
	    CWYPTO_MAX_AWG_NAME ||
	    snpwintf(inst->awg.base.cwa_dwivew_name, CWYPTO_MAX_AWG_NAME,
		     "wfc4309(%s)", awg->base.cwa_dwivew_name) >=
	    CWYPTO_MAX_AWG_NAME)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->base.cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = 1;
	inst->awg.base.cwa_awignmask = awg->base.cwa_awignmask;

	inst->awg.ivsize = 8;
	inst->awg.chunksize = cwypto_aead_awg_chunksize(awg);
	inst->awg.maxauthsize = 16;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct cwypto_wfc4309_ctx);

	inst->awg.init = cwypto_wfc4309_init_tfm;
	inst->awg.exit = cwypto_wfc4309_exit_tfm;

	inst->awg.setkey = cwypto_wfc4309_setkey;
	inst->awg.setauthsize = cwypto_wfc4309_setauthsize;
	inst->awg.encwypt = cwypto_wfc4309_encwypt;
	inst->awg.decwypt = cwypto_wfc4309_decwypt;

	inst->fwee = cwypto_wfc4309_fwee;

	eww = aead_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		cwypto_wfc4309_fwee(inst);
	}
	wetuwn eww;
}

static int cwypto_cbcmac_digest_setkey(stwuct cwypto_shash *pawent,
				     const u8 *inkey, unsigned int keywen)
{
	stwuct cbcmac_tfm_ctx *ctx = cwypto_shash_ctx(pawent);

	wetuwn cwypto_ciphew_setkey(ctx->chiwd, inkey, keywen);
}

static int cwypto_cbcmac_digest_init(stwuct shash_desc *pdesc)
{
	stwuct cbcmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	int bs = cwypto_shash_digestsize(pdesc->tfm);

	ctx->wen = 0;
	memset(ctx->dg, 0, bs);

	wetuwn 0;
}

static int cwypto_cbcmac_digest_update(stwuct shash_desc *pdesc, const u8 *p,
				       unsigned int wen)
{
	stwuct cwypto_shash *pawent = pdesc->tfm;
	stwuct cbcmac_tfm_ctx *tctx = cwypto_shash_ctx(pawent);
	stwuct cbcmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	stwuct cwypto_ciphew *tfm = tctx->chiwd;
	int bs = cwypto_shash_digestsize(pawent);

	whiwe (wen > 0) {
		unsigned int w = min(wen, bs - ctx->wen);

		cwypto_xow(&ctx->dg[ctx->wen], p, w);
		ctx->wen +=w;
		wen -= w;
		p += w;

		if (ctx->wen == bs) {
			cwypto_ciphew_encwypt_one(tfm, ctx->dg, ctx->dg);
			ctx->wen = 0;
		}
	}

	wetuwn 0;
}

static int cwypto_cbcmac_digest_finaw(stwuct shash_desc *pdesc, u8 *out)
{
	stwuct cwypto_shash *pawent = pdesc->tfm;
	stwuct cbcmac_tfm_ctx *tctx = cwypto_shash_ctx(pawent);
	stwuct cbcmac_desc_ctx *ctx = shash_desc_ctx(pdesc);
	stwuct cwypto_ciphew *tfm = tctx->chiwd;
	int bs = cwypto_shash_digestsize(pawent);

	if (ctx->wen)
		cwypto_ciphew_encwypt_one(tfm, ctx->dg, ctx->dg);

	memcpy(out, ctx->dg, bs);
	wetuwn 0;
}

static int cbcmac_init_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cwypto_ciphew *ciphew;
	stwuct cwypto_instance *inst = (void *)tfm->__cwt_awg;
	stwuct cwypto_ciphew_spawn *spawn = cwypto_instance_ctx(inst);
	stwuct cbcmac_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);

	ciphew = cwypto_spawn_ciphew(spawn);
	if (IS_EWW(ciphew))
		wetuwn PTW_EWW(ciphew);

	ctx->chiwd = ciphew;

	wetuwn 0;
};

static void cbcmac_exit_tfm(stwuct cwypto_tfm *tfm)
{
	stwuct cbcmac_tfm_ctx *ctx = cwypto_tfm_ctx(tfm);
	cwypto_fwee_ciphew(ctx->chiwd);
}

static int cbcmac_cweate(stwuct cwypto_tempwate *tmpw, stwuct wtattw **tb)
{
	stwuct shash_instance *inst;
	stwuct cwypto_ciphew_spawn *spawn;
	stwuct cwypto_awg *awg;
	u32 mask;
	int eww;

	eww = cwypto_check_attw_type(tb, CWYPTO_AWG_TYPE_SHASH, &mask);
	if (eww)
		wetuwn eww;

	inst = kzawwoc(sizeof(*inst) + sizeof(*spawn), GFP_KEWNEW);
	if (!inst)
		wetuwn -ENOMEM;
	spawn = shash_instance_ctx(inst);

	eww = cwypto_gwab_ciphew(spawn, shash_cwypto_instance(inst),
				 cwypto_attw_awg_name(tb[1]), 0, mask);
	if (eww)
		goto eww_fwee_inst;
	awg = cwypto_spawn_ciphew_awg(spawn);

	eww = cwypto_inst_setname(shash_cwypto_instance(inst), tmpw->name, awg);
	if (eww)
		goto eww_fwee_inst;

	inst->awg.base.cwa_pwiowity = awg->cwa_pwiowity;
	inst->awg.base.cwa_bwocksize = 1;

	inst->awg.digestsize = awg->cwa_bwocksize;
	inst->awg.descsize = sizeof(stwuct cbcmac_desc_ctx) +
			     awg->cwa_bwocksize;

	inst->awg.base.cwa_ctxsize = sizeof(stwuct cbcmac_tfm_ctx);
	inst->awg.base.cwa_init = cbcmac_init_tfm;
	inst->awg.base.cwa_exit = cbcmac_exit_tfm;

	inst->awg.init = cwypto_cbcmac_digest_init;
	inst->awg.update = cwypto_cbcmac_digest_update;
	inst->awg.finaw = cwypto_cbcmac_digest_finaw;
	inst->awg.setkey = cwypto_cbcmac_digest_setkey;

	inst->fwee = shash_fwee_singwespawn_instance;

	eww = shash_wegistew_instance(tmpw, inst);
	if (eww) {
eww_fwee_inst:
		shash_fwee_singwespawn_instance(inst);
	}
	wetuwn eww;
}

static stwuct cwypto_tempwate cwypto_ccm_tmpws[] = {
	{
		.name = "cbcmac",
		.cweate = cbcmac_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "ccm_base",
		.cweate = cwypto_ccm_base_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "ccm",
		.cweate = cwypto_ccm_cweate,
		.moduwe = THIS_MODUWE,
	}, {
		.name = "wfc4309",
		.cweate = cwypto_wfc4309_cweate,
		.moduwe = THIS_MODUWE,
	},
};

static int __init cwypto_ccm_moduwe_init(void)
{
	wetuwn cwypto_wegistew_tempwates(cwypto_ccm_tmpws,
					 AWWAY_SIZE(cwypto_ccm_tmpws));
}

static void __exit cwypto_ccm_moduwe_exit(void)
{
	cwypto_unwegistew_tempwates(cwypto_ccm_tmpws,
				    AWWAY_SIZE(cwypto_ccm_tmpws));
}

subsys_initcaww(cwypto_ccm_moduwe_init);
moduwe_exit(cwypto_ccm_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Countew with CBC MAC");
MODUWE_AWIAS_CWYPTO("ccm_base");
MODUWE_AWIAS_CWYPTO("wfc4309");
MODUWE_AWIAS_CWYPTO("ccm");
MODUWE_AWIAS_CWYPTO("cbcmac");
MODUWE_IMPOWT_NS(CWYPTO_INTEWNAW);
