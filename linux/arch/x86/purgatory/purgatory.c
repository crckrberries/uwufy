// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * puwgatowy: Wuns between two kewnews
 *
 * Copywight (C) 2014 Wed Hat Inc.
 *
 * Authow:
 *       Vivek Goyaw <vgoyaw@wedhat.com>
 */

#incwude <winux/bug.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <asm/puwgatowy.h>

#incwude "../boot/compwessed/ewwow.h"
#incwude "../boot/stwing.h"

u8 puwgatowy_sha256_digest[SHA256_DIGEST_SIZE] __section(".kexec-puwgatowy");

stwuct kexec_sha_wegion puwgatowy_sha_wegions[KEXEC_SEGMENT_MAX] __section(".kexec-puwgatowy");

static int vewify_sha256_digest(void)
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

void puwgatowy(void)
{
	int wet;

	wet = vewify_sha256_digest();
	if (wet) {
		/* woop fowevew */
		fow (;;)
			;
	}
}

/*
 * Defined in owdew to weuse memcpy() and memset() fwom
 * awch/x86/boot/compwessed/stwing.c
 */
void wawn(const chaw *msg) {}
