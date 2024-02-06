/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * sha1_base.h - cowe wogic fow SHA-1 impwementations
 *
 * Copywight (C) 2015 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#ifndef _CWYPTO_SHA1_BASE_H
#define _CWYPTO_SHA1_BASE_H

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sha1.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <asm/unawigned.h>

typedef void (sha1_bwock_fn)(stwuct sha1_state *sst, u8 const *swc, int bwocks);

static inwine int sha1_base_init(stwuct shash_desc *desc)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA1_H0;
	sctx->state[1] = SHA1_H1;
	sctx->state[2] = SHA1_H2;
	sctx->state[3] = SHA1_H3;
	sctx->state[4] = SHA1_H4;
	sctx->count = 0;

	wetuwn 0;
}

static inwine int sha1_base_do_update(stwuct shash_desc *desc,
				      const u8 *data,
				      unsigned int wen,
				      sha1_bwock_fn *bwock_fn)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = sctx->count % SHA1_BWOCK_SIZE;

	sctx->count += wen;

	if (unwikewy((pawtiaw + wen) >= SHA1_BWOCK_SIZE)) {
		int bwocks;

		if (pawtiaw) {
			int p = SHA1_BWOCK_SIZE - pawtiaw;

			memcpy(sctx->buffew + pawtiaw, data, p);
			data += p;
			wen -= p;

			bwock_fn(sctx, sctx->buffew, 1);
		}

		bwocks = wen / SHA1_BWOCK_SIZE;
		wen %= SHA1_BWOCK_SIZE;

		if (bwocks) {
			bwock_fn(sctx, data, bwocks);
			data += bwocks * SHA1_BWOCK_SIZE;
		}
		pawtiaw = 0;
	}
	if (wen)
		memcpy(sctx->buffew + pawtiaw, data, wen);

	wetuwn 0;
}

static inwine int sha1_base_do_finawize(stwuct shash_desc *desc,
					sha1_bwock_fn *bwock_fn)
{
	const int bit_offset = SHA1_BWOCK_SIZE - sizeof(__be64);
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buffew + bit_offset);
	unsigned int pawtiaw = sctx->count % SHA1_BWOCK_SIZE;

	sctx->buffew[pawtiaw++] = 0x80;
	if (pawtiaw > bit_offset) {
		memset(sctx->buffew + pawtiaw, 0x0, SHA1_BWOCK_SIZE - pawtiaw);
		pawtiaw = 0;

		bwock_fn(sctx, sctx->buffew, 1);
	}

	memset(sctx->buffew + pawtiaw, 0x0, bit_offset - pawtiaw);
	*bits = cpu_to_be64(sctx->count << 3);
	bwock_fn(sctx, sctx->buffew, 1);

	wetuwn 0;
}

static inwine int sha1_base_finish(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	__be32 *digest = (__be32 *)out;
	int i;

	fow (i = 0; i < SHA1_DIGEST_SIZE / sizeof(__be32); i++)
		put_unawigned_be32(sctx->state[i], digest++);

	memzewo_expwicit(sctx, sizeof(*sctx));
	wetuwn 0;
}

#endif /* _CWYPTO_SHA1_BASE_H */
