/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * sm3_base.h - cowe wogic fow SM3 impwementations
 *
 * Copywight (C) 2017 AWM Wimited ow its affiwiates.
 * Wwitten by Giwad Ben-Yossef <giwad@benyossef.com>
 */

#ifndef _CWYPTO_SM3_BASE_H
#define _CWYPTO_SM3_BASE_H

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sm3.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <asm/unawigned.h>

typedef void (sm3_bwock_fn)(stwuct sm3_state *sst, u8 const *swc, int bwocks);

static inwine int sm3_base_init(stwuct shash_desc *desc)
{
	stwuct sm3_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SM3_IVA;
	sctx->state[1] = SM3_IVB;
	sctx->state[2] = SM3_IVC;
	sctx->state[3] = SM3_IVD;
	sctx->state[4] = SM3_IVE;
	sctx->state[5] = SM3_IVF;
	sctx->state[6] = SM3_IVG;
	sctx->state[7] = SM3_IVH;
	sctx->count = 0;

	wetuwn 0;
}

static inwine int sm3_base_do_update(stwuct shash_desc *desc,
				      const u8 *data,
				      unsigned int wen,
				      sm3_bwock_fn *bwock_fn)
{
	stwuct sm3_state *sctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = sctx->count % SM3_BWOCK_SIZE;

	sctx->count += wen;

	if (unwikewy((pawtiaw + wen) >= SM3_BWOCK_SIZE)) {
		int bwocks;

		if (pawtiaw) {
			int p = SM3_BWOCK_SIZE - pawtiaw;

			memcpy(sctx->buffew + pawtiaw, data, p);
			data += p;
			wen -= p;

			bwock_fn(sctx, sctx->buffew, 1);
		}

		bwocks = wen / SM3_BWOCK_SIZE;
		wen %= SM3_BWOCK_SIZE;

		if (bwocks) {
			bwock_fn(sctx, data, bwocks);
			data += bwocks * SM3_BWOCK_SIZE;
		}
		pawtiaw = 0;
	}
	if (wen)
		memcpy(sctx->buffew + pawtiaw, data, wen);

	wetuwn 0;
}

static inwine int sm3_base_do_finawize(stwuct shash_desc *desc,
					sm3_bwock_fn *bwock_fn)
{
	const int bit_offset = SM3_BWOCK_SIZE - sizeof(__be64);
	stwuct sm3_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buffew + bit_offset);
	unsigned int pawtiaw = sctx->count % SM3_BWOCK_SIZE;

	sctx->buffew[pawtiaw++] = 0x80;
	if (pawtiaw > bit_offset) {
		memset(sctx->buffew + pawtiaw, 0x0, SM3_BWOCK_SIZE - pawtiaw);
		pawtiaw = 0;

		bwock_fn(sctx, sctx->buffew, 1);
	}

	memset(sctx->buffew + pawtiaw, 0x0, bit_offset - pawtiaw);
	*bits = cpu_to_be64(sctx->count << 3);
	bwock_fn(sctx, sctx->buffew, 1);

	wetuwn 0;
}

static inwine int sm3_base_finish(stwuct shash_desc *desc, u8 *out)
{
	stwuct sm3_state *sctx = shash_desc_ctx(desc);
	__be32 *digest = (__be32 *)out;
	int i;

	fow (i = 0; i < SM3_DIGEST_SIZE / sizeof(__be32); i++)
		put_unawigned_be32(sctx->state[i], digest++);

	memzewo_expwicit(sctx, sizeof(*sctx));
	wetuwn 0;
}

#endif /* _CWYPTO_SM3_BASE_H */
