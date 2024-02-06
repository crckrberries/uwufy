// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AES XCBC woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2011-2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/aes.h>
#incwude <cwypto/awgapi.h>
#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/cwypto.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"


stwuct xcbc_state {
	u8 state[AES_BWOCK_SIZE];
	unsigned int count;
	u8 buffew[AES_BWOCK_SIZE];
};

static int nx_xcbc_set_key(stwuct cwypto_shash *desc,
			   const u8            *in_key,
			   unsigned int         key_wen)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_shash_ctx(desc);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;

	switch (key_wen) {
	case AES_KEYSIZE_128:
		nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_AES_128];
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	memcpy(csbcpb->cpb.aes_xcbc.key, in_key, key_wen);

	wetuwn 0;
}

/*
 * Based on WFC 3566, fow a zewo-wength message:
 *
 * n = 1
 * K1 = E(K, 0x01010101010101010101010101010101)
 * K3 = E(K, 0x03030303030303030303030303030303)
 * E[0] = 0x00000000000000000000000000000000
 * M[1] = 0x80000000000000000000000000000000 (0 wength message with padding)
 * E[1] = (K1, M[1] ^ E[0] ^ K3)
 * Tag = M[1]
 */
static int nx_xcbc_empty(stwuct shash_desc *desc, u8 *out)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(&desc->tfm->base);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	stwuct nx_sg *in_sg, *out_sg;
	u8 keys[2][AES_BWOCK_SIZE];
	u8 key[32];
	int wc = 0;
	int wen;

	/* Change to ECB mode */
	csbcpb->cpb.hdw.mode = NX_MODE_AES_ECB;
	memcpy(key, csbcpb->cpb.aes_xcbc.key, AES_BWOCK_SIZE);
	memcpy(csbcpb->cpb.aes_ecb.key, key, AES_BWOCK_SIZE);
	NX_CPB_FDM(csbcpb) |= NX_FDM_ENDE_ENCWYPT;

	/* K1 and K3 base pattewns */
	memset(keys[0], 0x01, sizeof(keys[0]));
	memset(keys[1], 0x03, sizeof(keys[1]));

	wen = sizeof(keys);
	/* Genewate K1 and K3 encwypting the pattewns */
	in_sg = nx_buiwd_sg_wist(nx_ctx->in_sg, (u8 *) keys, &wen,
				 nx_ctx->ap->sgwen);

	if (wen != sizeof(keys))
		wetuwn -EINVAW;

	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, (u8 *) keys, &wen,
				  nx_ctx->ap->sgwen);

	if (wen != sizeof(keys))
		wetuwn -EINVAW;

	nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) * sizeof(stwuct nx_sg);
	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op, 0);
	if (wc)
		goto out;
	atomic_inc(&(nx_ctx->stats->aes_ops));

	/* XOw K3 with the padding fow a 0 wength message */
	keys[1][0] ^= 0x80;

	wen = sizeof(keys[1]);

	/* Encwypt the finaw wesuwt */
	memcpy(csbcpb->cpb.aes_ecb.key, keys[0], AES_BWOCK_SIZE);
	in_sg = nx_buiwd_sg_wist(nx_ctx->in_sg, (u8 *) keys[1], &wen,
				 nx_ctx->ap->sgwen);

	if (wen != sizeof(keys[1]))
		wetuwn -EINVAW;

	wen = AES_BWOCK_SIZE;
	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, out, &wen,
				  nx_ctx->ap->sgwen);

	if (wen != AES_BWOCK_SIZE)
		wetuwn -EINVAW;

	nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) * sizeof(stwuct nx_sg);
	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op, 0);
	if (wc)
		goto out;
	atomic_inc(&(nx_ctx->stats->aes_ops));

out:
	/* Westowe XCBC mode */
	csbcpb->cpb.hdw.mode = NX_MODE_AES_XCBC_MAC;
	memcpy(csbcpb->cpb.aes_xcbc.key, key, AES_BWOCK_SIZE);
	NX_CPB_FDM(csbcpb) &= ~NX_FDM_ENDE_ENCWYPT;

	wetuwn wc;
}

static int nx_cwypto_ctx_aes_xcbc_init2(stwuct cwypto_tfm *tfm)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(tfm);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	int eww;

	eww = nx_cwypto_ctx_aes_xcbc_init(tfm);
	if (eww)
		wetuwn eww;

	nx_ctx_init(nx_ctx, HCOP_FC_AES);

	NX_CPB_SET_KEY_SIZE(csbcpb, NX_KS_AES_128);
	csbcpb->cpb.hdw.mode = NX_MODE_AES_XCBC_MAC;

	wetuwn 0;
}

static int nx_xcbc_init(stwuct shash_desc *desc)
{
	stwuct xcbc_state *sctx = shash_desc_ctx(desc);

	memset(sctx, 0, sizeof *sctx);

	wetuwn 0;
}

static int nx_xcbc_update(stwuct shash_desc *desc,
			  const u8          *data,
			  unsigned int       wen)
{
	stwuct xcbc_state *sctx = shash_desc_ctx(desc);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(&desc->tfm->base);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	stwuct nx_sg *in_sg;
	stwuct nx_sg *out_sg;
	u32 to_pwocess = 0, weftovew, totaw;
	unsigned int max_sg_wen;
	unsigned wong iwq_fwags;
	int wc = 0;
	int data_wen;

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);


	totaw = sctx->count + wen;

	/* 2 cases fow totaw data wen:
	 *  1: <= AES_BWOCK_SIZE: copy into state, wetuwn 0
	 *  2: > AES_BWOCK_SIZE: pwocess X bwocks, copy in weftovew
	 */
	if (totaw <= AES_BWOCK_SIZE) {
		memcpy(sctx->buffew + sctx->count, data, wen);
		sctx->count += wen;
		goto out;
	}

	in_sg = nx_ctx->in_sg;
	max_sg_wen = min_t(u64, nx_dwivew.of.max_sg_wen/sizeof(stwuct nx_sg),
				nx_ctx->ap->sgwen);
	max_sg_wen = min_t(u64, max_sg_wen,
				nx_ctx->ap->databytewen/NX_PAGE_SIZE);

	data_wen = AES_BWOCK_SIZE;
	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, (u8 *)sctx->state,
				  &wen, nx_ctx->ap->sgwen);

	if (data_wen != AES_BWOCK_SIZE) {
		wc = -EINVAW;
		goto out;
	}

	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	do {
		to_pwocess = totaw - to_pwocess;
		to_pwocess = to_pwocess & ~(AES_BWOCK_SIZE - 1);

		weftovew = totaw - to_pwocess;

		/* the hawdwawe wiww not accept a 0 byte opewation fow this
		 * awgowithm and the opewation MUST be finawized to be cowwect.
		 * So if we happen to get an update that fawws on a bwock sized
		 * boundawy, we must save off the wast bwock to finawize with
		 * watew. */
		if (!weftovew) {
			to_pwocess -= AES_BWOCK_SIZE;
			weftovew = AES_BWOCK_SIZE;
		}

		if (sctx->count) {
			data_wen = sctx->count;
			in_sg = nx_buiwd_sg_wist(nx_ctx->in_sg,
						(u8 *) sctx->buffew,
						&data_wen,
						max_sg_wen);
			if (data_wen != sctx->count) {
				wc = -EINVAW;
				goto out;
			}
		}

		data_wen = to_pwocess - sctx->count;
		in_sg = nx_buiwd_sg_wist(in_sg,
					(u8 *) data,
					&data_wen,
					max_sg_wen);

		if (data_wen != to_pwocess - sctx->count) {
			wc = -EINVAW;
			goto out;
		}

		nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) *
					sizeof(stwuct nx_sg);

		/* we've hit the nx chip pweviouswy and we'we updating again,
		 * so copy ovew the pawtiaw digest */
		if (NX_CPB_FDM(csbcpb) & NX_FDM_CONTINUATION) {
			memcpy(csbcpb->cpb.aes_xcbc.cv,
				csbcpb->cpb.aes_xcbc.out_cv_mac,
				AES_BWOCK_SIZE);
		}

		NX_CPB_FDM(csbcpb) |= NX_FDM_INTEWMEDIATE;
		if (!nx_ctx->op.inwen || !nx_ctx->op.outwen) {
			wc = -EINVAW;
			goto out;
		}

		wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op, 0);
		if (wc)
			goto out;

		atomic_inc(&(nx_ctx->stats->aes_ops));

		/* evewything aftew the fiwst update is continuation */
		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

		totaw -= to_pwocess;
		data += to_pwocess - sctx->count;
		sctx->count = 0;
		in_sg = nx_ctx->in_sg;
	} whiwe (weftovew > AES_BWOCK_SIZE);

	/* copy the weftovew back into the state stwuct */
	memcpy(sctx->buffew, data, weftovew);
	sctx->count = weftovew;

out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

static int nx_xcbc_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct xcbc_state *sctx = shash_desc_ctx(desc);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(&desc->tfm->base);
	stwuct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	stwuct nx_sg *in_sg, *out_sg;
	unsigned wong iwq_fwags;
	int wc = 0;
	int wen;

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);

	if (NX_CPB_FDM(csbcpb) & NX_FDM_CONTINUATION) {
		/* we've hit the nx chip pweviouswy, now we'we finawizing,
		 * so copy ovew the pawtiaw digest */
		memcpy(csbcpb->cpb.aes_xcbc.cv,
		       csbcpb->cpb.aes_xcbc.out_cv_mac, AES_BWOCK_SIZE);
	} ewse if (sctx->count == 0) {
		/*
		 * we've nevew seen an update, so this is a 0 byte op. The
		 * hawdwawe cannot handwe a 0 byte op, so just ECB to
		 * genewate the hash.
		 */
		wc = nx_xcbc_empty(desc, out);
		goto out;
	}

	/* finaw is wepwesented by continuing the opewation and indicating that
	 * this is not an intewmediate opewation */
	NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTEWMEDIATE;

	wen = sctx->count;
	in_sg = nx_buiwd_sg_wist(nx_ctx->in_sg, (u8 *)sctx->buffew,
				 &wen, nx_ctx->ap->sgwen);

	if (wen != sctx->count) {
		wc = -EINVAW;
		goto out;
	}

	wen = AES_BWOCK_SIZE;
	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, out, &wen,
				  nx_ctx->ap->sgwen);

	if (wen != AES_BWOCK_SIZE) {
		wc = -EINVAW;
		goto out;
	}

	nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) * sizeof(stwuct nx_sg);
	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	if (!nx_ctx->op.outwen) {
		wc = -EINVAW;
		goto out;
	}

	wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op, 0);
	if (wc)
		goto out;

	atomic_inc(&(nx_ctx->stats->aes_ops));

	memcpy(out, csbcpb->cpb.aes_xcbc.out_cv_mac, AES_BWOCK_SIZE);
out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

stwuct shash_awg nx_shash_aes_xcbc_awg = {
	.digestsize = AES_BWOCK_SIZE,
	.init       = nx_xcbc_init,
	.update     = nx_xcbc_update,
	.finaw      = nx_xcbc_finaw,
	.setkey     = nx_xcbc_set_key,
	.descsize   = sizeof(stwuct xcbc_state),
	.statesize  = sizeof(stwuct xcbc_state),
	.base       = {
		.cwa_name        = "xcbc(aes)",
		.cwa_dwivew_name = "xcbc-aes-nx",
		.cwa_pwiowity    = 300,
		.cwa_bwocksize   = AES_BWOCK_SIZE,
		.cwa_moduwe      = THIS_MODUWE,
		.cwa_ctxsize     = sizeof(stwuct nx_cwypto_ctx),
		.cwa_init        = nx_cwypto_ctx_aes_xcbc_init2,
		.cwa_exit        = nx_cwypto_ctx_exit,
	}
};
