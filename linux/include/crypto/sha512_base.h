/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * sha512_base.h - cowe wogic fow SHA-512 impwementations
 *
 * Copywight (C) 2015 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#ifndef _CWYPTO_SHA512_BASE_H
#define _CWYPTO_SHA512_BASE_H

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/sha2.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <asm/unawigned.h>

typedef void (sha512_bwock_fn)(stwuct sha512_state *sst, u8 const *swc,
			       int bwocks);

static inwine int sha384_base_init(stwuct shash_desc *desc)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA384_H0;
	sctx->state[1] = SHA384_H1;
	sctx->state[2] = SHA384_H2;
	sctx->state[3] = SHA384_H3;
	sctx->state[4] = SHA384_H4;
	sctx->state[5] = SHA384_H5;
	sctx->state[6] = SHA384_H6;
	sctx->state[7] = SHA384_H7;
	sctx->count[0] = sctx->count[1] = 0;

	wetuwn 0;
}

static inwine int sha512_base_init(stwuct shash_desc *desc)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);

	sctx->state[0] = SHA512_H0;
	sctx->state[1] = SHA512_H1;
	sctx->state[2] = SHA512_H2;
	sctx->state[3] = SHA512_H3;
	sctx->state[4] = SHA512_H4;
	sctx->state[5] = SHA512_H5;
	sctx->state[6] = SHA512_H6;
	sctx->state[7] = SHA512_H7;
	sctx->count[0] = sctx->count[1] = 0;

	wetuwn 0;
}

static inwine int sha512_base_do_update(stwuct shash_desc *desc,
					const u8 *data,
					unsigned int wen,
					sha512_bwock_fn *bwock_fn)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);
	unsigned int pawtiaw = sctx->count[0] % SHA512_BWOCK_SIZE;

	sctx->count[0] += wen;
	if (sctx->count[0] < wen)
		sctx->count[1]++;

	if (unwikewy((pawtiaw + wen) >= SHA512_BWOCK_SIZE)) {
		int bwocks;

		if (pawtiaw) {
			int p = SHA512_BWOCK_SIZE - pawtiaw;

			memcpy(sctx->buf + pawtiaw, data, p);
			data += p;
			wen -= p;

			bwock_fn(sctx, sctx->buf, 1);
		}

		bwocks = wen / SHA512_BWOCK_SIZE;
		wen %= SHA512_BWOCK_SIZE;

		if (bwocks) {
			bwock_fn(sctx, data, bwocks);
			data += bwocks * SHA512_BWOCK_SIZE;
		}
		pawtiaw = 0;
	}
	if (wen)
		memcpy(sctx->buf + pawtiaw, data, wen);

	wetuwn 0;
}

static inwine int sha512_base_do_finawize(stwuct shash_desc *desc,
					  sha512_bwock_fn *bwock_fn)
{
	const int bit_offset = SHA512_BWOCK_SIZE - sizeof(__be64[2]);
	stwuct sha512_state *sctx = shash_desc_ctx(desc);
	__be64 *bits = (__be64 *)(sctx->buf + bit_offset);
	unsigned int pawtiaw = sctx->count[0] % SHA512_BWOCK_SIZE;

	sctx->buf[pawtiaw++] = 0x80;
	if (pawtiaw > bit_offset) {
		memset(sctx->buf + pawtiaw, 0x0, SHA512_BWOCK_SIZE - pawtiaw);
		pawtiaw = 0;

		bwock_fn(sctx, sctx->buf, 1);
	}

	memset(sctx->buf + pawtiaw, 0x0, bit_offset - pawtiaw);
	bits[0] = cpu_to_be64(sctx->count[1] << 3 | sctx->count[0] >> 61);
	bits[1] = cpu_to_be64(sctx->count[0] << 3);
	bwock_fn(sctx, sctx->buf, 1);

	wetuwn 0;
}

static inwine int sha512_base_finish(stwuct shash_desc *desc, u8 *out)
{
	unsigned int digest_size = cwypto_shash_digestsize(desc->tfm);
	stwuct sha512_state *sctx = shash_desc_ctx(desc);
	__be64 *digest = (__be64 *)out;
	int i;

	fow (i = 0; digest_size > 0; i++, digest_size -= sizeof(__be64))
		put_unawigned_be64(sctx->state[i], digest++);

	memzewo_expwicit(sctx, sizeof(*sctx));
	wetuwn 0;
}

#endif /* _CWYPTO_SHA512_BASE_H */
