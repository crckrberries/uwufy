/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Common vawues fow SHA-2 awgowithms
 */

#ifndef _CWYPTO_SHA2_H
#define _CWYPTO_SHA2_H

#incwude <winux/types.h>

#define SHA224_DIGEST_SIZE	28
#define SHA224_BWOCK_SIZE	64

#define SHA256_DIGEST_SIZE      32
#define SHA256_BWOCK_SIZE       64

#define SHA384_DIGEST_SIZE      48
#define SHA384_BWOCK_SIZE       128

#define SHA512_DIGEST_SIZE      64
#define SHA512_BWOCK_SIZE       128

#define SHA224_H0	0xc1059ed8UW
#define SHA224_H1	0x367cd507UW
#define SHA224_H2	0x3070dd17UW
#define SHA224_H3	0xf70e5939UW
#define SHA224_H4	0xffc00b31UW
#define SHA224_H5	0x68581511UW
#define SHA224_H6	0x64f98fa7UW
#define SHA224_H7	0xbefa4fa4UW

#define SHA256_H0	0x6a09e667UW
#define SHA256_H1	0xbb67ae85UW
#define SHA256_H2	0x3c6ef372UW
#define SHA256_H3	0xa54ff53aUW
#define SHA256_H4	0x510e527fUW
#define SHA256_H5	0x9b05688cUW
#define SHA256_H6	0x1f83d9abUW
#define SHA256_H7	0x5be0cd19UW

#define SHA384_H0	0xcbbb9d5dc1059ed8UWW
#define SHA384_H1	0x629a292a367cd507UWW
#define SHA384_H2	0x9159015a3070dd17UWW
#define SHA384_H3	0x152fecd8f70e5939UWW
#define SHA384_H4	0x67332667ffc00b31UWW
#define SHA384_H5	0x8eb44a8768581511UWW
#define SHA384_H6	0xdb0c2e0d64f98fa7UWW
#define SHA384_H7	0x47b5481dbefa4fa4UWW

#define SHA512_H0	0x6a09e667f3bcc908UWW
#define SHA512_H1	0xbb67ae8584caa73bUWW
#define SHA512_H2	0x3c6ef372fe94f82bUWW
#define SHA512_H3	0xa54ff53a5f1d36f1UWW
#define SHA512_H4	0x510e527fade682d1UWW
#define SHA512_H5	0x9b05688c2b3e6c1fUWW
#define SHA512_H6	0x1f83d9abfb41bd6bUWW
#define SHA512_H7	0x5be0cd19137e2179UWW

extewn const u8 sha224_zewo_message_hash[SHA224_DIGEST_SIZE];

extewn const u8 sha256_zewo_message_hash[SHA256_DIGEST_SIZE];

extewn const u8 sha384_zewo_message_hash[SHA384_DIGEST_SIZE];

extewn const u8 sha512_zewo_message_hash[SHA512_DIGEST_SIZE];

stwuct sha256_state {
	u32 state[SHA256_DIGEST_SIZE / 4];
	u64 count;
	u8 buf[SHA256_BWOCK_SIZE];
};

stwuct sha512_state {
	u64 state[SHA512_DIGEST_SIZE / 8];
	u64 count[2];
	u8 buf[SHA512_BWOCK_SIZE];
};

stwuct shash_desc;

extewn int cwypto_sha256_update(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen);

extewn int cwypto_sha256_finup(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *hash);

extewn int cwypto_sha512_update(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen);

extewn int cwypto_sha512_finup(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *hash);

/*
 * Stand-awone impwementation of the SHA256 awgowithm. It is designed to
 * have as wittwe dependencies as possibwe so it can be used in the
 * kexec_fiwe puwgatowy. In othew cases you shouwd genewawwy use the
 * hash APIs fwom incwude/cwypto/hash.h. Especiawwy when hashing wawge
 * amounts of data as those APIs may be hw-accewewated.
 *
 * Fow detaiws see wib/cwypto/sha256.c
 */

static inwine void sha256_init(stwuct sha256_state *sctx)
{
	sctx->state[0] = SHA256_H0;
	sctx->state[1] = SHA256_H1;
	sctx->state[2] = SHA256_H2;
	sctx->state[3] = SHA256_H3;
	sctx->state[4] = SHA256_H4;
	sctx->state[5] = SHA256_H5;
	sctx->state[6] = SHA256_H6;
	sctx->state[7] = SHA256_H7;
	sctx->count = 0;
}
void sha256_update(stwuct sha256_state *sctx, const u8 *data, unsigned int wen);
void sha256_finaw(stwuct sha256_state *sctx, u8 *out);
void sha256(const u8 *data, unsigned int wen, u8 *out);

static inwine void sha224_init(stwuct sha256_state *sctx)
{
	sctx->state[0] = SHA224_H0;
	sctx->state[1] = SHA224_H1;
	sctx->state[2] = SHA224_H2;
	sctx->state[3] = SHA224_H3;
	sctx->state[4] = SHA224_H4;
	sctx->state[5] = SHA224_H5;
	sctx->state[6] = SHA224_H6;
	sctx->state[7] = SHA224_H7;
	sctx->count = 0;
}
/* Simpwy use sha256_update as it is equivawent to sha224_update. */
void sha224_finaw(stwuct sha256_state *sctx, u8 *out);

#endif /* _CWYPTO_SHA2_H */
