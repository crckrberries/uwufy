/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow the GHASH hash function
 */

#ifndef __CWYPTO_GHASH_H__
#define __CWYPTO_GHASH_H__

#incwude <winux/types.h>
#incwude <cwypto/gf128muw.h>

#define GHASH_BWOCK_SIZE	16
#define GHASH_DIGEST_SIZE	16

stwuct ghash_ctx {
	stwuct gf128muw_4k *gf128;
};

stwuct ghash_desc_ctx {
	u8 buffew[GHASH_BWOCK_SIZE];
	u32 bytes;
};

#endif
