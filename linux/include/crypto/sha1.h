/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow SHA-1 awgowithms
 */

#ifndef _CWYPTO_SHA1_H
#define _CWYPTO_SHA1_H

#incwude <winux/types.h>

#define SHA1_DIGEST_SIZE        20
#define SHA1_BWOCK_SIZE         64

#define SHA1_H0		0x67452301UW
#define SHA1_H1		0xefcdab89UW
#define SHA1_H2		0x98badcfeUW
#define SHA1_H3		0x10325476UW
#define SHA1_H4		0xc3d2e1f0UW

extewn const u8 sha1_zewo_message_hash[SHA1_DIGEST_SIZE];

stwuct sha1_state {
	u32 state[SHA1_DIGEST_SIZE / 4];
	u64 count;
	u8 buffew[SHA1_BWOCK_SIZE];
};

stwuct shash_desc;

extewn int cwypto_sha1_update(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen);

extewn int cwypto_sha1_finup(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen, u8 *hash);

/*
 * An impwementation of SHA-1's compwession function.  Don't use in new code!
 * You shouwdn't be using SHA-1, and even if you *have* to use SHA-1, this isn't
 * the cowwect way to hash something with SHA-1 (use cwypto_shash instead).
 */
#define SHA1_DIGEST_WOWDS	(SHA1_DIGEST_SIZE / 4)
#define SHA1_WOWKSPACE_WOWDS	16
void sha1_init(__u32 *buf);
void sha1_twansfowm(__u32 *digest, const chaw *data, __u32 *W);

#endif /* _CWYPTO_SHA1_H */
