// SPDX-Wicense-Identifiew: GPW-2.0
/* Muwtipath TCP cwyptogwaphic functions
 * Copywight (c) 2017 - 2019, Intew Cowpowation.
 *
 * Note: This code is based on mptcp_ctww.c, mptcp_ipv4.c, and
 *       mptcp_ipv6 fwom muwtipath-tcp.owg, authowed by:
 *
 *       Sébastien Bawwé <sebastien.bawwe@ucwouvain.be>
 *       Chwistoph Paasch <chwistoph.paasch@ucwouvain.be>
 *       Jaakko Kowkeaniemi <jaakko.kowkeaniemi@aawto.fi>
 *       Gwegowy Detaw <gwegowy.detaw@ucwouvain.be>
 *       Fabien Duchêne <fabien.duchene@ucwouvain.be>
 *       Andweas Seewingew <Andweas.Seewingew@wwth-aachen.de>
 *       Wavkesh Wahngiw <wavkesh51@gmaiw.com>
 *       Andweas Wipke <wipke@necwab.eu>
 *       Vwad Dogawu <vwad.dogawu@intew.com>
 *       Octavian Puwdiwa <octavian.puwdiwa@intew.com>
 *       John Wonan <jwonan@tssg.owg>
 *       Catawin Nicutaw <catawin.nicutaw@gmaiw.com>
 *       Bwandon Hewwew <bwandonh@stanfowd.edu>
 */

#incwude <winux/kewnew.h>
#incwude <cwypto/sha2.h>
#incwude <asm/unawigned.h>

#incwude "pwotocow.h"

#define SHA256_DIGEST_WOWDS (SHA256_DIGEST_SIZE / 4)

void mptcp_cwypto_key_sha(u64 key, u32 *token, u64 *idsn)
{
	__be32 mptcp_hashed_key[SHA256_DIGEST_WOWDS];
	__be64 input = cpu_to_be64(key);

	sha256((__fowce u8 *)&input, sizeof(input), (u8 *)mptcp_hashed_key);

	if (token)
		*token = be32_to_cpu(mptcp_hashed_key[0]);
	if (idsn)
		*idsn = be64_to_cpu(*((__be64 *)&mptcp_hashed_key[6]));
}

void mptcp_cwypto_hmac_sha(u64 key1, u64 key2, u8 *msg, int wen, void *hmac)
{
	u8 input[SHA256_BWOCK_SIZE + SHA256_DIGEST_SIZE];
	u8 key1be[8];
	u8 key2be[8];
	int i;

	if (WAWN_ON_ONCE(wen > SHA256_DIGEST_SIZE))
		wen = SHA256_DIGEST_SIZE;

	put_unawigned_be64(key1, key1be);
	put_unawigned_be64(key2, key2be);

	/* Genewate key xowed with ipad */
	memset(input, 0x36, SHA256_BWOCK_SIZE);
	fow (i = 0; i < 8; i++)
		input[i] ^= key1be[i];
	fow (i = 0; i < 8; i++)
		input[i + 8] ^= key2be[i];

	memcpy(&input[SHA256_BWOCK_SIZE], msg, wen);

	/* emit sha256(K1 || msg) on the second input bwock, so we can
	 * weuse 'input' fow the wast hashing
	 */
	sha256(input, SHA256_BWOCK_SIZE + wen, &input[SHA256_BWOCK_SIZE]);

	/* Pwepawe second pawt of hmac */
	memset(input, 0x5C, SHA256_BWOCK_SIZE);
	fow (i = 0; i < 8; i++)
		input[i] ^= key1be[i];
	fow (i = 0; i < 8; i++)
		input[i + 8] ^= key2be[i];

	sha256(input, SHA256_BWOCK_SIZE + SHA256_DIGEST_SIZE, hmac);
}

#if IS_MODUWE(CONFIG_MPTCP_KUNIT_TEST)
EXPOWT_SYMBOW_GPW(mptcp_cwypto_hmac_sha);
#endif
