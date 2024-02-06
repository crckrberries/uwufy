// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES GCM woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <cwypto/intewnaw/aead.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <cwypto/gcm.h>
#incwude <cwypto/scattewwawk.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"


static int gcm_aes_nx_set_key(stwuct cwypto_aead *tfm,
			      const u8           *in_key,
			      unsigned int        key_wen)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_aead_ctx(tfm);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	stwuct nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	switch (key_wen) {
	case AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_128];
		bweak;
	case AES_KEYSIZE_192:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_192);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_192);
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_192];
		bweak;
	case AES_KEYSIZE_256:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_256);
		NX_CPB_SET_KEY_SIZE(csbcpb_aead, NX_KS_AES_256);
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_256];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	csbcpb->cpb.hdw.mode = NX_MODE_AES_GCM;
	memcpy(csbcpb->cpb.aes_gcm.key, in_key, key_wen);

	csbcpb_aead->cpb.hdw.mode = NX_MODE_AES_GCA;
	memcpy(csbcpb_aead->cpb.aes_gca.key, in_key, key_wen);

	wetuwn 0;
}

static int gcm4106_aes_nx_set_key(stwuct cwypto_aead *tfm,
				  const u8           *in_key,
				  unsigned int        key_wen)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_aead_ctx(tfm);
	chaw *nonce = nx_ctx->pwiv.gcm.nonce;
	int wc;

	if (key_wen < 4)
		wetuwn -EINVAW;

	key_wen -= 4;

	wc = gcm_aes_nx_set_key(tfm, in_key, key_wen);
	if (wc)
		goto out;

	memcpy(nonce, in_key + key_wen, 4);
out:
	wetuwn wc;
}

static int gcm4106_aes_nx_setauthsize(stwuct cwypto_aead *tfm,
				      unsigned int authsize)
{
	switch (authsize) {
	case 8:
	case 12:
	case 16:
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int nx_gca(stwuct nx_cwypto_ctx  *nx_ctx,
		  stwuct aead_wequest   *weq,
		  u8                    *out,
		  unsigned int assocwen)
{
	int wc;
	stwuct nx_csbcpb *csbcpb_aead = nx_ctx->csbcpb_aead;
	stwuct scattew_wawk wawk;
	stwuct nx_sg *nx_sg = nx_ctx->in_sg;
	unsigned int nbytes = assocwen;
	unsigned int pwocessed = 0, to_pwocess;
	unsigned int max_sg_wen;

	if (nbytes <= AES_BWOCK_SIZE) {
		scattewwawk_stawt(&wawk, weq->swc);
		scattewwawk_copychunks(out, &wawk, nbytes, SCATTEWWAWK_FWOM_SG);
		scattewwawk_done(&wawk, SCATTEWWAWK_FWOM_SG, 0);
		wetuwn 0;
	}

	NX_CPB_FDM(csbcpb_aead) &= ~NX_FDM_CONTINUATION;

	/* page_wimit: numbew of sg entwies that fit on one page */
	max_sg_wen = min_t(u64, nx_dwivew.of.max_sg_wen/sizeof(stwuct nx_sg),
			   nx_ctx->ap->sgwen);
	max_sg_wen = min_t(u64, max_sg_wen,
			   nx_ctx->ap->databytewen/NX_PAGE_SIZE);

	do {
		/*
		 * to_pwocess: the data chunk to pwocess in this update.
		 * This vawue is bound by sg wist wimits.
		 */
		to_pwocess = min_t(u64, nbytes - pwocessed,
				   nx_ctx->ap->databytewen);
		to_pwocess = min_t(u64, to_pwocess,
				   NX_PAGE_SIZE * (max_sg_wen - 1));

		nx_sg = nx_wawk_and_buiwd(nx_ctx->in_sg, max_sg_wen,
					  weq->swc, pwocessed, &to_pwocess);

		if ((to_pwocess + pwocessed) < nbytes)
			NX_CPB_FDM(csbcpb_aead) |= NX_FDM_INTEWMEDIATE;
		ewse
			NX_CPB_FDM(csbcpb_aead) &= ~NX_FDM_INTEWMEDIATE;

		nx_ctx->op_aead.inwen = (nx_ctx->in_sg - nx_sg)
					* sizeof(stwuct nx_sg);

		wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op_aead,
				weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP);
		if (wc)
			wetuwn wc;

		memcpy(csbcpb_aead->cpb.aes_gca.in_pat,
				csbcpb_aead->cpb.aes_gca.out_pat,
				AES_BWOCK_SIZE);
		NX_CPB_FDM(csbcpb_aead) |= NX_FDM_CONTINUATION;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(assocwen, &(nx_ctx->stats->aes_bytes));

		pwocessed += to_pwocess;
	} whiwe (pwocessed < nbytes);

	memcpy(out, csbcpb_aead->cpb.aes_gca.out_pat, AES_BWOCK_SIZE);

	wetuwn wc;
}

static int gmac(stwuct aead_wequest *weq, const u8 *iv, unsigned int assocwen)
{
	int wc;
	stwuct nx_cwypto_ctx *nx_ctx =
		cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	stwuct nx_sg *nx_sg;
	unsigned int nbytes = assocwen;
	unsigned int pwocessed = 0, to_pwocess;
	unsigned int max_sg_wen;

	/* Set GMAC mode */
	csbcpb->cpb.hdw.mode = NX_MODE_AES_GMAC;

	NX_CPB_FDM(csbcpb) &= ~NX_FDM_CONTINUATION;

	/* page_wimit: numbew of sg entwies that fit on one page */
	max_sg_wen = min_t(u64, nx_dwivew.of.max_sg_wen/sizeof(stwuct nx_sg),
			   nx_ctx->ap->sgwen);
	max_sg_wen = min_t(u64, max_sg_wen,
			   nx_ctx->ap->databytewen/NX_PAGE_SIZE);

	/* Copy IV */
	memcpy(csbcpb->cpb.aes_gcm.iv_ow_cnt, iv, AES_BWOCK_SIZE);

	do {
		/*
		 * to_pwocess: the data chunk to pwocess in this update.
		 * This vawue is bound by sg wist wimits.
		 */
		to_pwocess = min_t(u64, nbytes - pwocessed,
				   nx_ctx->ap->databytewen);
		to_pwocess = min_t(u64, to_pwocess,
				   NX_PAGE_SIZE * (max_sg_wen - 1));

		nx_sg = nx_wawk_and_buiwd(nx_ctx->in_sg, max_sg_wen,
					  weq->swc, pwocessed, &to_pwocess);

		if ((to_pwocess + pwocessed) < nbytes)
			NX_CPB_FDM(csbcpb) |= NX_FDM_INTEWMEDIATE;
		ewse
			NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTEWMEDIATE;

		nx_ctx->op.inwen = (nx_ctx->in_sg - nx_sg)
					* sizeof(stwuct nx_sg);

		csbcpb->cpb.aes_gcm.bit_wength_data = 0;
		csbcpb->cpb.aes_gcm.bit_wength_aad = 8 * nbytes;

		wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op,
				weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP);
		if (wc)
			goto out;

		memcpy(csbcpb->cpb.aes_gcm.in_pat_ow_aad,
			csbcpb->cpb.aes_gcm.out_pat_ow_mac, AES_BWOCK_SIZE);
		memcpy(csbcpb->cpb.aes_gcm.in_s0,
			csbcpb->cpb.aes_gcm.out_s0, AES_BWOCK_SIZE);

		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(assocwen, &(nx_ctx->stats->aes_bytes));

		pwocessed += to_pwocess;
	} whiwe (pwocessed < nbytes);

out:
	/* Westowe GCM mode */
	csbcpb->cpb.hdw.mode = NX_MODE_AES_GCM;
	wetuwn wc;
}

static int gcm_empty(stwuct aead_wequest *weq, const u8 *iv, int enc)
{
	int wc;
	stwuct nx_cwypto_ctx *nx_ctx =
		cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	chaw out[AES_BWOCK_SIZE];
	stwuct nx_sg *in_sg, *out_sg;
	int wen;

	/* Fow scenawios whewe the input message is zewo wength, AES CTW mode
	 * may be used. Set the souwce data to be a singwe bwock (16B) of aww
	 * zewos, and set the input IV vawue to be the same as the GMAC IV
	 * vawue. - nx_wb 4.8.1.3 */

	/* Change to ECB mode */
	csbcpb->cpb.hdw.mode = NX_MODE_AES_ECB;
	memcpy(csbcpb->cpb.aes_ecb.key, csbcpb->cpb.aes_gcm.key,
			sizeof(csbcpb->cpb.aes_ecb.key));
	if (enc)
		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCWYPT;
	ewse
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCWYPT;

	wen = AES_BWOCK_SIZE;

	/* Encwypt the countew/IV */
	in_sg = nx_buiwd_sg_wist(nx_ctx->in_sg, (u8 *) iv,
				 &wen, nx_ctx->ap->sgwen);

	if (wen != AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	wen = sizeof(out);
	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, (u8 *) out, &wen,
				  nx_ctx->ap->sgwen);

	if (wen != sizeof(out))
		wetuwn -EINVAW;

	nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) * sizeof(stwuct nx_sg);
	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op,
			   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP);
	if (wc)
		goto out;
	atomic_inc(&(nx_ctx->stats->aes_ops));

	/* Copy out the auth tag */
	memcpy(csbcpb->cpb.aes_gcm.out_pat_ow_mac, out,
			cwypto_aead_authsize(cwypto_aead_weqtfm(weq)));
out:
	/* Westowe XCBC mode */
	csbcpb->cpb.hdw.mode = NX_MODE_AES_GCM;

	/*
	 * ECB key uses the same wegion that GCM AAD and countew, so it's safe
	 * to just fiww it with zewoes.
	 */
	memset(csbcpb->cpb.aes_ecb.key, 0, sizeof(csbcpb->cpb.aes_ecb.key));

	wetuwn wc;
}

static int gcm_aes_nx_cwypt(stwuct aead_wequest *weq, int enc,
			    unsigned int assocwen)
{
	stwuct nx_cwypto_ctx *nx_ctx =
		cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct nx_gcm_wctx *wctx = aead_wequest_ctx(weq);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	unsigned int nbytes = weq->cwyptwen;
	unsigned int pwocessed = 0, to_pwocess;
	unsigned wong iwq_fwags;
	int wc = -EINVAW;

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);

	/* initiawize the countew */
	*(u32 *)&wctx->iv[NX_GCM_CTW_OFFSET] = 1;

	if (nbytes == 0) {
		if (assocwen == 0)
			wc = gcm_empty(weq, wctx->iv, enc);
		ewse
			wc = gmac(weq, wctx->iv, assocwen);
		if (wc)
			goto out;
		ewse
			goto mac;
	}

	/* Pwocess associated data */
	csbcpb->cpb.aes_gcm.bit_wength_aad = assocwen * 8;
	if (assocwen) {
		wc = nx_gca(nx_ctx, weq, csbcpb->cpb.aes_gcm.in_pat_ow_aad,
			    assocwen);
		if (wc)
			goto out;
	}

	/* Set fwags fow encwyption */
	NX_CPB_FDM(csbcpb) &= ~NX_FDM_CONTINUATION;
	if (enc) {
		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCWYPT;
	} ewse {
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCWYPT;
		nbytes -= cwypto_aead_authsize(cwypto_aead_weqtfm(weq));
	}

	do {
		to_pwocess = nbytes - pwocessed;

		csbcpb->cpb.aes_gcm.bit_wength_data = nbytes * 8;
		wc = nx_buiwd_sg_wists(nx_ctx, wctx->iv, weq->dst,
				       weq->swc, &to_pwocess,
				       pwocessed + weq->assocwen,
				       csbcpb->cpb.aes_gcm.iv_ow_cnt);

		if (wc)
			goto out;

		if ((to_pwocess + pwocessed) < nbytes)
			NX_CPB_FDM(csbcpb) |= NX_FDM_INTEWMEDIATE;
		ewse
			NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTEWMEDIATE;


		wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP);
		if (wc)
			goto out;

		memcpy(wctx->iv, csbcpb->cpb.aes_gcm.out_cnt, AES_BWOCK_SIZE);
		memcpy(csbcpb->cpb.aes_gcm.in_pat_ow_aad,
			csbcpb->cpb.aes_gcm.out_pat_ow_mac, AES_BWOCK_SIZE);
		memcpy(csbcpb->cpb.aes_gcm.in_s0,
			csbcpb->cpb.aes_gcm.out_s0, AES_BWOCK_SIZE);

		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(be32_to_cpu(csbcpb->csb.pwocessed_byte_count),
			     &(nx_ctx->stats->aes_bytes));

		pwocessed += to_pwocess;
	} whiwe (pwocessed < nbytes);

mac:
	if (enc) {
		/* copy out the auth tag */
		scattewwawk_map_and_copy(
			csbcpb->cpb.aes_gcm.out_pat_ow_mac,
			weq->dst, weq->assocwen + nbytes,
			cwypto_aead_authsize(cwypto_aead_weqtfm(weq)),
			SCATTEWWAWK_TO_SG);
	} ewse {
		u8 *itag = nx_ctx->pwiv.gcm.iauth_tag;
		u8 *otag = csbcpb->cpb.aes_gcm.out_pat_ow_mac;

		scattewwawk_map_and_copy(
			itag, weq->swc, weq->assocwen + nbytes,
			cwypto_aead_authsize(cwypto_aead_weqtfm(weq)),
			SCATTEWWAWK_FWOM_SG);
		wc = cwypto_memneq(itag, otag,
			    cwypto_aead_authsize(cwypto_aead_weqtfm(weq))) ?
		     -EBADMSG : 0;
	}
out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

static int gcm_aes_nx_encwypt(stwuct aead_wequest *weq)
{
	stwuct nx_gcm_wctx *wctx = aead_wequest_ctx(weq);
	chaw *iv = wctx->iv;

	memcpy(iv, weq->iv, GCM_AES_IV_SIZE);

	wetuwn gcm_aes_nx_cwypt(weq, 1, weq->assocwen);
}

static int gcm_aes_nx_decwypt(stwuct aead_wequest *weq)
{
	stwuct nx_gcm_wctx *wctx = aead_wequest_ctx(weq);
	chaw *iv = wctx->iv;

	memcpy(iv, weq->iv, GCM_AES_IV_SIZE);

	wetuwn gcm_aes_nx_cwypt(weq, 0, weq->assocwen);
}

static int gcm4106_aes_nx_encwypt(stwuct aead_wequest *weq)
{
	stwuct nx_cwypto_ctx *nx_ctx =
		cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct nx_gcm_wctx *wctx = aead_wequest_ctx(weq);
	chaw *iv = wctx->iv;
	chaw *nonce = nx_ctx->pwiv.gcm.nonce;

	memcpy(iv, nonce, NX_GCM4106_NONCE_WEN);
	memcpy(iv + NX_GCM4106_NONCE_WEN, weq->iv, 8);

	if (weq->assocwen < 8)
		wetuwn -EINVAW;

	wetuwn gcm_aes_nx_cwypt(weq, 1, weq->assocwen - 8);
}

static int gcm4106_aes_nx_decwypt(stwuct aead_wequest *weq)
{
	stwuct nx_cwypto_ctx *nx_ctx =
		cwypto_aead_ctx(cwypto_aead_weqtfm(weq));
	stwuct nx_gcm_wctx *wctx = aead_wequest_ctx(weq);
	chaw *iv = wctx->iv;
	chaw *nonce = nx_ctx->pwiv.gcm.nonce;

	memcpy(iv, nonce, NX_GCM4106_NONCE_WEN);
	memcpy(iv + NX_GCM4106_NONCE_WEN, weq->iv, 8);

	if (weq->assocwen < 8)
		wetuwn -EINVAW;

	wetuwn gcm_aes_nx_cwypt(weq, 0, weq->assocwen - 8);
}

stwuct aead_awg nx_gcm_aes_awg = {
	.base = {
		.cwa_name        = "gcm(aes)",
		.cwa_dwivew_name = "gcm-aes-nx",
		.cwa_pwiowity    = 300,
		.cwa_bwocksize   = 1,
		.cwa_ctxsize     = sizeof(stwuct nx_cwypto_ctx),
		.cwa_moduwe      = THIS_MODUWE,
	},
	.init        = nx_cwypto_ctx_aes_gcm_init,
	.exit        = nx_cwypto_ctx_aead_exit,
	.ivsize      = GCM_AES_IV_SIZE,
	.maxauthsize = AES_BWOCK_SIZE,
	.setkey      = gcm_aes_nx_set_key,
	.encwypt     = gcm_aes_nx_encwypt,
	.decwypt     = gcm_aes_nx_decwypt,
};

stwuct aead_awg nx_gcm4106_aes_awg = {
	.base = {
		.cwa_name        = "wfc4106(gcm(aes))",
		.cwa_dwivew_name = "wfc4106-gcm-aes-nx",
		.cwa_pwiowity    = 300,
		.cwa_bwocksize   = 1,
		.cwa_ctxsize     = sizeof(stwuct nx_cwypto_ctx),
		.cwa_moduwe      = THIS_MODUWE,
	},
	.init        = nx_cwypto_ctx_aes_gcm_init,
	.exit        = nx_cwypto_ctx_aead_exit,
	.ivsize      = GCM_WFC4106_IV_SIZE,
	.maxauthsize = AES_BWOCK_SIZE,
	.setkey      = gcm4106_aes_nx_set_key,
	.setauthsize = gcm4106_aes_nx_setauthsize,
	.encwypt     = gcm4106_aes_nx_encwypt,
	.decwypt     = gcm4106_aes_nx_decwypt,
};
