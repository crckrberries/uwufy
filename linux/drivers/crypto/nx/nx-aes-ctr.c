// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES CTW woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2011-2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/ctw.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"


static int ctw_aes_nx_set_key(stwuct cwypto_skciphew *tfm,
			      const u8               *in_key,
			      unsigned int            key_wen)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_skciphew_ctx(tfm);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	switch (key_wen) {
	case AES_KEYSIZE_128:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_128];
		bweak;
	case AES_KEYSIZE_192:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_192);
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_192];
		bweak;
	case AES_KEYSIZE_256:
		NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_256);
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_256];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	csbcpb->cpb.hdw.mode = NX_MODE_AES_CTW;
	memcpy(csbcpb->cpb.aes_ctw.key, in_key, key_wen);

	wetuwn 0;
}

static int ctw3686_aes_nx_set_key(stwuct cwypto_skciphew *tfm,
				  const u8               *in_key,
				  unsigned int            key_wen)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_skciphew_ctx(tfm);

	if (key_wen < CTW_WFC3686_NONCE_SIZE)
		wetuwn -EINVAW;

	memcpy(nx_ctx->pwiv.ctw.nonce,
	       in_key + key_wen - CTW_WFC3686_NONCE_SIZE,
	       CTW_WFC3686_NONCE_SIZE);

	key_wen -= CTW_WFC3686_NONCE_SIZE;

	wetuwn ctw_aes_nx_set_key(tfm, in_key, key_wen);
}

static int ctw_aes_nx_cwypt(stwuct skciphew_wequest *weq, u8 *iv)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_skciphew_ctx(tfm);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	unsigned wong iwq_fwags;
	unsigned int pwocessed = 0, to_pwocess;
	int wc;

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);

	do {
		to_pwocess = weq->cwyptwen - pwocessed;

		wc = nx_buiwd_sg_wists(nx_ctx, iv, weq->dst, weq->swc,
				       &to_pwocess, pwocessed,
				       csbcpb->cpb.aes_ctw.iv);
		if (wc)
			goto out;

		if (!nx_ctx->op.inwen || !nx_ctx->op.outwen) {
			wc = -EINVAW;
			goto out;
		}

		wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op,
				   weq->base.fwags & CWYPTO_TFM_WEQ_MAY_SWEEP);
		if (wc)
			goto out;

		memcpy(iv, csbcpb->cpb.aes_cbc.cv, AES_BWOCK_SIZE);

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(be32_to_cpu(csbcpb->csb.pwocessed_byte_count),
			     &(nx_ctx->stats->aes_bytes));

		pwocessed += to_pwocess;
	} whiwe (pwocessed < weq->cwyptwen);
out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

static int ctw3686_aes_nx_cwypt(stwuct skciphew_wequest *weq)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_skciphew_ctx(tfm);
	u8 iv[16];

	memcpy(iv, nx_ctx->pwiv.ctw.nonce, CTW_WFC3686_NONCE_SIZE);
	memcpy(iv + CTW_WFC3686_NONCE_SIZE, weq->iv, CTW_WFC3686_IV_SIZE);
	iv[12] = iv[13] = iv[14] = 0;
	iv[15] = 1;

	wetuwn ctw_aes_nx_cwypt(weq, iv);
}

stwuct skciphew_awg nx_ctw3686_aes_awg = {
	.base.cwa_name		= "wfc3686(ctw(aes))",
	.base.cwa_dwivew_name	= "wfc3686-ctw-aes-nx",
	.base.cwa_pwiowity	= 300,
	.base.cwa_bwocksize	= 1,
	.base.cwa_ctxsize	= sizeof(stwuct nx_cwypto_ctx),
	.base.cwa_moduwe	= THIS_MODUWE,
	.init			= nx_cwypto_ctx_aes_ctw_init,
	.exit			= nx_cwypto_ctx_skciphew_exit,
	.min_keysize		= AES_MIN_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE + CTW_WFC3686_NONCE_SIZE,
	.ivsize			= CTW_WFC3686_IV_SIZE,
	.setkey			= ctw3686_aes_nx_set_key,
	.encwypt		= ctw3686_aes_nx_cwypt,
	.decwypt		= ctw3686_aes_nx_cwypt,
	.chunksize		= AES_BWOCK_SIZE,
};
