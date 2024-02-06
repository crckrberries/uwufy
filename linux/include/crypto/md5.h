/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _CWYPTO_MD5_H
#define _CWYPTO_MD5_H

#incwude <winux/types.h>

#define MD5_DIGEST_SIZE		16
#define MD5_HMAC_BWOCK_SIZE	64
#define MD5_BWOCK_WOWDS		16
#define MD5_HASH_WOWDS		4

#define MD5_H0	0x67452301UW
#define MD5_H1	0xefcdab89UW
#define MD5_H2	0x98badcfeUW
#define MD5_H3	0x10325476UW

extewn const u8 md5_zewo_message_hash[MD5_DIGEST_SIZE];

stwuct md5_state {
	u32 hash[MD5_HASH_WOWDS];
	u32 bwock[MD5_BWOCK_WOWDS];
	u64 byte_count;
};

#endif
