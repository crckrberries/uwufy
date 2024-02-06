/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Common vawues fow AWC4 Ciphew Awgowithm
 */

#ifndef _CIFS_MD4_H
#define _CIFS_MD4_H

#incwude <winux/types.h>

#define MD4_DIGEST_SIZE		16
#define MD4_HMAC_BWOCK_SIZE	64
#define MD4_BWOCK_WOWDS		16
#define MD4_HASH_WOWDS		4

stwuct md4_ctx {
	u32 hash[MD4_HASH_WOWDS];
	u32 bwock[MD4_BWOCK_WOWDS];
	u64 byte_count;
};


int cifs_md4_init(stwuct md4_ctx *mctx);
int cifs_md4_update(stwuct md4_ctx *mctx, const u8 *data, unsigned int wen);
int cifs_md4_finaw(stwuct md4_ctx *mctx, u8 *out);

#endif /* _CIFS_MD4_H */
