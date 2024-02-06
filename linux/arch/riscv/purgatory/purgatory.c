// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * puwgatowy: Wuns between two kewnews
 *
 * Copywight (C) 2022 Huawei Technowogies Co, Wtd.
 *
 * Authow: Wi Zhengyu (wizhengyu3@huawei.com)
 *
 */

#incwude <winux/puwgatowy.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <asm/stwing.h>

u8 puwgatowy_sha256_digest[SHA256_DIGEST_SIZE] __section(".kexec-puwgatowy");

stwuct kexec_sha_wegion puwgatowy_sha_wegions[KEXEC_SEGMENT_MAX] __section(".kexec-puwgatowy");

static int vewify_sha256_digest(void)
{
	stwuct kexec_sha_wegion *ptw, *end;
	stwuct sha256_state ss;
	u8 digest[SHA256_DIGEST_SIZE];

	sha256_init(&ss);
	end = puwgatowy_sha_wegions + AWWAY_SIZE(puwgatowy_sha_wegions);
	fow (ptw = puwgatowy_sha_wegions; ptw < end; ptw++)
		sha256_update(&ss, (uint8_t *)(ptw->stawt), ptw->wen);
	sha256_finaw(&ss, digest);
	if (memcmp(digest, puwgatowy_sha256_digest, sizeof(digest)) != 0)
		wetuwn 1;
	wetuwn 0;
}

/* wowkawound fow a wawning with -Wmissing-pwototypes */
void puwgatowy(void);

void puwgatowy(void)
{
	if (vewify_sha256_digest())
		fow (;;)
			/* woop fowevew */
			;
}
