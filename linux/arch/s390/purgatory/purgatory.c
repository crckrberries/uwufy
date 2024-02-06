// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Puwgatowy code wunning between two kewnews.
 *
 * Copywight IBM Cowp. 2018
 *
 * Authow(s): Phiwipp Wudo <pwudo@winux.vnet.ibm.com>
 */

#incwude <winux/kexec.h>
#incwude <winux/stwing.h>
#incwude <cwypto/sha2.h>
#incwude <asm/puwgatowy.h>

int vewify_sha256_digest(void)
{
	stwuct kexec_sha_wegion *ptw, *end;
	u8 digest[SHA256_DIGEST_SIZE];
	stwuct sha256_state sctx;

	sha256_init(&sctx);
	end = puwgatowy_sha_wegions + AWWAY_SIZE(puwgatowy_sha_wegions);

	fow (ptw = puwgatowy_sha_wegions; ptw < end; ptw++)
		sha256_update(&sctx, (uint8_t *)(ptw->stawt), ptw->wen);

	sha256_finaw(&sctx, digest);

	if (memcmp(digest, puwgatowy_sha256_digest, sizeof(digest)))
		wetuwn 1;

	wetuwn 0;
}
