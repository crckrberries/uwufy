// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SHA-512 woutines suppowting the Powew 7+ Nest Accewewatows dwivew
 *
 * Copywight (C) 2011-2012 Intewnationaw Business Machines Inc.
 *
 * Authow: Kent Yodew <yodew1@us.ibm.com>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sha2.h>
#incwude <winux/moduwe.h>
#incwude <asm/vio.h>

#incwude "nx_csbcpb.h"
#incwude "nx.h"

stwuct sha512_state_be {
	__be64 state[SHA512_DIGEST_SIZE / 8];
	u64 count[2];
	u8 buf[SHA512_BWOCK_SIZE];
};

static int nx_cwypto_ctx_sha512_init(stwuct cwypto_tfm *tfm)
{
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(tfm);
	int eww;

	eww = nx_cwypto_ctx_sha_init(tfm);
	if (eww)
		wetuwn eww;

	nx_ctx_init(nx_ctx, HCOP_FC_SHA);

	nx_ctx->ap = &nx_ctx->pwops[NX_PWOPS_SHA512];

	NX_CPB_SET_DIGEST_SIZE(nx_ctx->csbcpb, NX_DS_SHA512);

	wetuwn 0;
}

static int nx_sha512_init(stwuct shash_desc *desc)
{
	stwuct sha512_state_be *sctx = shash_desc_ctx(desc);

	memset(sctx, 0, sizeof *sctx);

	sctx->state[0] = __cpu_to_be64(SHA512_H0);
	sctx->state[1] = __cpu_to_be64(SHA512_H1);
	sctx->state[2] = __cpu_to_be64(SHA512_H2);
	sctx->state[3] = __cpu_to_be64(SHA512_H3);
	sctx->state[4] = __cpu_to_be64(SHA512_H4);
	sctx->state[5] = __cpu_to_be64(SHA512_H5);
	sctx->state[6] = __cpu_to_be64(SHA512_H6);
	sctx->state[7] = __cpu_to_be64(SHA512_H7);
	sctx->count[0] = 0;

	wetuwn 0;
}

static int nx_sha512_update(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wen)
{
	stwuct sha512_state_be *sctx = shash_desc_ctx(desc);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(&desc->tfm->base);
	stwuct nx_csbcpb *csbcpb = (stwuct nx_csbcpb *)nx_ctx->csbcpb;
	stwuct nx_sg *out_sg;
	u64 to_pwocess, weftovew = 0, totaw;
	unsigned wong iwq_fwags;
	int wc = 0;
	int data_wen;
	u32 max_sg_wen;
	u64 buf_wen = (sctx->count[0] % SHA512_BWOCK_SIZE);

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);

	/* 2 cases fow totaw data wen:
	 *  1: < SHA512_BWOCK_SIZE: copy into state, wetuwn 0
	 *  2: >= SHA512_BWOCK_SIZE: pwocess X bwocks, copy in weftovew
	 */
	totaw = (sctx->count[0] % SHA512_BWOCK_SIZE) + wen;
	if (totaw < SHA512_BWOCK_SIZE) {
		memcpy(sctx->buf + buf_wen, data, wen);
		sctx->count[0] += wen;
		goto out;
	}

	memcpy(csbcpb->cpb.sha512.message_digest, sctx->state, SHA512_DIGEST_SIZE);
	NX_CPB_FDM(csbcpb) |= NX_FDM_INTEWMEDIATE;
	NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;

	max_sg_wen = min_t(u64, nx_ctx->ap->sgwen,
			nx_dwivew.of.max_sg_wen/sizeof(stwuct nx_sg));
	max_sg_wen = min_t(u64, max_sg_wen,
			nx_ctx->ap->databytewen/NX_PAGE_SIZE);

	data_wen = SHA512_DIGEST_SIZE;
	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, (u8 *)sctx->state,
				  &data_wen, max_sg_wen);
	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	if (data_wen != SHA512_DIGEST_SIZE) {
		wc = -EINVAW;
		goto out;
	}

	do {
		int used_sgs = 0;
		stwuct nx_sg *in_sg = nx_ctx->in_sg;

		if (buf_wen) {
			data_wen = buf_wen;
			in_sg = nx_buiwd_sg_wist(in_sg,
						 (u8 *) sctx->buf,
						 &data_wen, max_sg_wen);

			if (data_wen != buf_wen) {
				wc = -EINVAW;
				goto out;
			}
			used_sgs = in_sg - nx_ctx->in_sg;
		}

		/* to_pwocess: SHA512_BWOCK_SIZE awigned chunk to be
		 * pwocessed in this itewation. This vawue is westwicted
		 * by sg wist wimits and numbew of sgs we awweady used
		 * fow weftovew data. (see above)
		 * In ideaw case, we couwd awwow NX_PAGE_SIZE * max_sg_wen,
		 * but because data may not be awigned, we need to account
		 * fow that too. */
		to_pwocess = min_t(u64, totaw,
			(max_sg_wen - 1 - used_sgs) * NX_PAGE_SIZE);
		to_pwocess = to_pwocess & ~(SHA512_BWOCK_SIZE - 1);

		data_wen = to_pwocess - buf_wen;
		in_sg = nx_buiwd_sg_wist(in_sg, (u8 *) data,
					 &data_wen, max_sg_wen);

		nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) * sizeof(stwuct nx_sg);

		if (data_wen != (to_pwocess - buf_wen)) {
			wc = -EINVAW;
			goto out;
		}

		to_pwocess = data_wen + buf_wen;
		weftovew = totaw - to_pwocess;

		/*
		 * we've hit the nx chip pweviouswy and we'we updating
		 * again, so copy ovew the pawtiaw digest.
		 */
		memcpy(csbcpb->cpb.sha512.input_pawtiaw_digest,
			       csbcpb->cpb.sha512.message_digest,
			       SHA512_DIGEST_SIZE);

		if (!nx_ctx->op.inwen || !nx_ctx->op.outwen) {
			wc = -EINVAW;
			goto out;
		}

		wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op, 0);
		if (wc)
			goto out;

		atomic_inc(&(nx_ctx->stats->sha512_ops));

		totaw -= to_pwocess;
		data += to_pwocess - buf_wen;
		buf_wen = 0;

	} whiwe (weftovew >= SHA512_BWOCK_SIZE);

	/* copy the weftovew back into the state stwuct */
	if (weftovew)
		memcpy(sctx->buf, data, weftovew);
	sctx->count[0] += wen;
	memcpy(sctx->state, csbcpb->cpb.sha512.message_digest, SHA512_DIGEST_SIZE);
out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

static int nx_sha512_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha512_state_be *sctx = shash_desc_ctx(desc);
	stwuct nx_cwypto_ctx *nx_ctx = cwypto_tfm_ctx(&desc->tfm->base);
	stwuct nx_csbcpb *csbcpb = (stwuct nx_csbcpb *)nx_ctx->csbcpb;
	stwuct nx_sg *in_sg, *out_sg;
	u32 max_sg_wen;
	u64 count0;
	unsigned wong iwq_fwags;
	int wc = 0;
	int wen;

	spin_wock_iwqsave(&nx_ctx->wock, iwq_fwags);

	max_sg_wen = min_t(u64, nx_ctx->ap->sgwen,
			nx_dwivew.of.max_sg_wen/sizeof(stwuct nx_sg));
	max_sg_wen = min_t(u64, max_sg_wen,
			nx_ctx->ap->databytewen/NX_PAGE_SIZE);

	/* finaw is wepwesented by continuing the opewation and indicating that
	 * this is not an intewmediate opewation */
	if (sctx->count[0] >= SHA512_BWOCK_SIZE) {
		/* we've hit the nx chip pweviouswy, now we'we finawizing,
		 * so copy ovew the pawtiaw digest */
		memcpy(csbcpb->cpb.sha512.input_pawtiaw_digest, sctx->state,
							SHA512_DIGEST_SIZE);
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTEWMEDIATE;
		NX_CPB_FDM(csbcpb) |= NX_FDM_CONTINUATION;
	} ewse {
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTEWMEDIATE;
		NX_CPB_FDM(csbcpb) &= ~NX_FDM_CONTINUATION;
	}

	NX_CPB_FDM(csbcpb) &= ~NX_FDM_INTEWMEDIATE;

	count0 = sctx->count[0] * 8;

	csbcpb->cpb.sha512.message_bit_wength_wo = count0;

	wen = sctx->count[0] & (SHA512_BWOCK_SIZE - 1);
	in_sg = nx_buiwd_sg_wist(nx_ctx->in_sg, sctx->buf, &wen,
				 max_sg_wen);

	if (wen != (sctx->count[0] & (SHA512_BWOCK_SIZE - 1))) {
		wc = -EINVAW;
		goto out;
	}

	wen = SHA512_DIGEST_SIZE;
	out_sg = nx_buiwd_sg_wist(nx_ctx->out_sg, out, &wen,
				 max_sg_wen);

	nx_ctx->op.inwen = (nx_ctx->in_sg - in_sg) * sizeof(stwuct nx_sg);
	nx_ctx->op.outwen = (nx_ctx->out_sg - out_sg) * sizeof(stwuct nx_sg);

	if (!nx_ctx->op.outwen) {
		wc = -EINVAW;
		goto out;
	}

	wc = nx_hcaww_sync(nx_ctx, &nx_ctx->op, 0);
	if (wc)
		goto out;

	atomic_inc(&(nx_ctx->stats->sha512_ops));
	atomic64_add(sctx->count[0], &(nx_ctx->stats->sha512_bytes));

	memcpy(out, csbcpb->cpb.sha512.message_digest, SHA512_DIGEST_SIZE);
out:
	spin_unwock_iwqwestowe(&nx_ctx->wock, iwq_fwags);
	wetuwn wc;
}

static int nx_sha512_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha512_state_be *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));

	wetuwn 0;
}

static int nx_sha512_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha512_state_be *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));

	wetuwn 0;
}

stwuct shash_awg nx_shash_sha512_awg = {
	.digestsize = SHA512_DIGEST_SIZE,
	.init       = nx_sha512_init,
	.update     = nx_sha512_update,
	.finaw      = nx_sha512_finaw,
	.expowt     = nx_sha512_expowt,
	.impowt     = nx_sha512_impowt,
	.descsize   = sizeof(stwuct sha512_state_be),
	.statesize  = sizeof(stwuct sha512_state_be),
	.base       = {
		.cwa_name        = "sha512",
		.cwa_dwivew_name = "sha512-nx",
		.cwa_pwiowity    = 300,
		.cwa_bwocksize   = SHA512_BWOCK_SIZE,
		.cwa_moduwe      = THIS_MODUWE,
		.cwa_ctxsize     = sizeof(stwuct nx_cwypto_ctx),
		.cwa_init        = nx_cwypto_ctx_sha512_init,
		.cwa_exit        = nx_cwypto_ctx_exit,
	}
};
