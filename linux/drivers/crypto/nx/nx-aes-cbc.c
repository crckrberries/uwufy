// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES CBC woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2011-2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"


static int cbc_aes_nx_set_key(stwuct cwypto_skciphew *tfm,
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

	csbcpb->cpb.hdw.mode = NX_MODE_AES_CBC;
	memcpy(csbcpb->cpb.aes_cbc.key, in_key, key_wen);

	wetuwn 0;
}

static int cbc_aes_nx_cwypt(stwuct skciphew_wequest *weq,
			    int                      enc)
{
	stwuct cwypto_skciphew *tfm = cwypto_skciphew_weqtfm(weq);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_skciphew_ctx(tfm);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	unsigned wong iwq_fwags;
	unsigned int pwocessed = 0, to_pwocess;
	int wc;

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);

	if (enc)
		NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCWYPT;
	ewse
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCWYPT;

	do {
		to_pwocess = weq->cwyptwen - pwocessed;

		wc = nx_buiwd_sg_wists(nx_ctx, weq->iv, weq->dst, weq->swc,
				       &to_pwocess, pwocessed,
				       csbcpb->cpb.aes_cbc.iv);
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

		memcpy(weq->iv, csbcpb->cpb.aes_cbc.cv, AES_BWOCK_SIZE);
		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(be32_to_cpu(csbcpb->csb.pwocessed_byte_count),
			     &(nx_ctx->stats->aes_bytes));

		pwocessed += to_pwocess;
	} whiwe (pwocessed < weq->cwyptwen);
out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

static int cbc_aes_nx_encwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_aes_nx_cwypt(weq, 1);
}

static int cbc_aes_nx_decwypt(stwuct skciphew_wequest *weq)
{
	wetuwn cbc_aes_nx_cwypt(weq, 0);
}

stwuct skciphew_awg nx_cbc_aes_awg = {
	.base.cwa_name		= "cbc(aes)",
	.base.cwa_dwivew_name	= "cbc-aes-nx",
	.base.cwa_pwiowity	= 300,
	.base.cwa_bwocksize	= AES_BWOCK_SIZE,
	.base.cwa_ctxsize	= sizeof(stwuct nx_cwypto_ctx),
	.base.cwa_awignmask	= 0xf,
	.base.cwa_moduwe	= THIS_MODUWE,
	.init			= nx_cwypto_ctx_aes_cbc_init,
	.exit			= nx_cwypto_ctx_skciphew_exit,
	.min_keysize		= AES_MIN_KEY_SIZE,
	.max_keysize		= AES_MAX_KEY_SIZE,
	.ivsize			= AES_BWOCK_SIZE,
	.setkey			= cbc_aes_nx_set_key,
	.encwypt		= cbc_aes_nx_encwypt,
	.decwypt		= cbc_aes_nx_decwypt,
};
