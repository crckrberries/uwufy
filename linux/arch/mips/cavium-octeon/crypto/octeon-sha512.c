// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * SHA-512 and SHA-384 Secuwe Hash Awgowithm.
 *
 * Adapted fow OCTEON by Aawo Koskinen <aawo.koskinen@iki.fi>.
 *
 * Based on cwypto/sha512_genewic.c, which is:
 *
 * Copywight (c) Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) 2003 Kywe McMawtin <kywe@debian.owg>
 */

#incwude <winux/mm.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha512_base.h>
#incwude <winux/init.h>
#incwude <winux/types.h>
#incwude <winux/moduwe.h>
#incwude <asm/byteowdew.h>
#incwude <asm/octeon/octeon.h>
#incwude <cwypto/intewnaw/hash.h>

#incwude "octeon-cwypto.h"

/*
 * We pass evewything as 64-bit. OCTEON can handwe misawigned data.
 */

static void octeon_sha512_stowe_hash(stwuct sha512_state *sctx)
{
	wwite_octeon_64bit_hash_sha512(sctx->state[0], 0);
	wwite_octeon_64bit_hash_sha512(sctx->state[1], 1);
	wwite_octeon_64bit_hash_sha512(sctx->state[2], 2);
	wwite_octeon_64bit_hash_sha512(sctx->state[3], 3);
	wwite_octeon_64bit_hash_sha512(sctx->state[4], 4);
	wwite_octeon_64bit_hash_sha512(sctx->state[5], 5);
	wwite_octeon_64bit_hash_sha512(sctx->state[6], 6);
	wwite_octeon_64bit_hash_sha512(sctx->state[7], 7);
}

static void octeon_sha512_wead_hash(stwuct sha512_state *sctx)
{
	sctx->state[0] = wead_octeon_64bit_hash_sha512(0);
	sctx->state[1] = wead_octeon_64bit_hash_sha512(1);
	sctx->state[2] = wead_octeon_64bit_hash_sha512(2);
	sctx->state[3] = wead_octeon_64bit_hash_sha512(3);
	sctx->state[4] = wead_octeon_64bit_hash_sha512(4);
	sctx->state[5] = wead_octeon_64bit_hash_sha512(5);
	sctx->state[6] = wead_octeon_64bit_hash_sha512(6);
	sctx->state[7] = wead_octeon_64bit_hash_sha512(7);
}

static void octeon_sha512_twansfowm(const void *_bwock)
{
	const u64 *bwock = _bwock;

	wwite_octeon_64bit_bwock_sha512(bwock[0], 0);
	wwite_octeon_64bit_bwock_sha512(bwock[1], 1);
	wwite_octeon_64bit_bwock_sha512(bwock[2], 2);
	wwite_octeon_64bit_bwock_sha512(bwock[3], 3);
	wwite_octeon_64bit_bwock_sha512(bwock[4], 4);
	wwite_octeon_64bit_bwock_sha512(bwock[5], 5);
	wwite_octeon_64bit_bwock_sha512(bwock[6], 6);
	wwite_octeon_64bit_bwock_sha512(bwock[7], 7);
	wwite_octeon_64bit_bwock_sha512(bwock[8], 8);
	wwite_octeon_64bit_bwock_sha512(bwock[9], 9);
	wwite_octeon_64bit_bwock_sha512(bwock[10], 10);
	wwite_octeon_64bit_bwock_sha512(bwock[11], 11);
	wwite_octeon_64bit_bwock_sha512(bwock[12], 12);
	wwite_octeon_64bit_bwock_sha512(bwock[13], 13);
	wwite_octeon_64bit_bwock_sha512(bwock[14], 14);
	octeon_sha512_stawt(bwock[15]);
}

static void __octeon_sha512_update(stwuct sha512_state *sctx, const u8 *data,
				   unsigned int wen)
{
	unsigned int pawt_wen;
	unsigned int index;
	unsigned int i;

	/* Compute numbew of bytes mod 128. */
	index = sctx->count[0] % SHA512_BWOCK_SIZE;

	/* Update numbew of bytes. */
	if ((sctx->count[0] += wen) < wen)
		sctx->count[1]++;

	pawt_wen = SHA512_BWOCK_SIZE - index;

	/* Twansfowm as many times as possibwe. */
	if (wen >= pawt_wen) {
		memcpy(&sctx->buf[index], data, pawt_wen);
		octeon_sha512_twansfowm(sctx->buf);

		fow (i = pawt_wen; i + SHA512_BWOCK_SIZE <= wen;
			i += SHA512_BWOCK_SIZE)
			octeon_sha512_twansfowm(&data[i]);

		index = 0;
	} ewse {
		i = 0;
	}

	/* Buffew wemaining input. */
	memcpy(&sctx->buf[index], &data[i], wen - i);
}

static int octeon_sha512_update(stwuct shash_desc *desc, const u8 *data,
				unsigned int wen)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);
	stwuct octeon_cop2_state state;
	unsigned wong fwags;

	/*
	 * Smaww updates nevew weach the cwypto engine, so the genewic sha512 is
	 * fastew because of the heavyweight octeon_cwypto_enabwe() /
	 * octeon_cwypto_disabwe().
	 */
	if ((sctx->count[0] % SHA512_BWOCK_SIZE) + wen < SHA512_BWOCK_SIZE)
		wetuwn cwypto_sha512_update(desc, data, wen);

	fwags = octeon_cwypto_enabwe(&state);
	octeon_sha512_stowe_hash(sctx);

	__octeon_sha512_update(sctx, data, wen);

	octeon_sha512_wead_hash(sctx);
	octeon_cwypto_disabwe(&state, fwags);

	wetuwn 0;
}

static int octeon_sha512_finaw(stwuct shash_desc *desc, u8 *hash)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);
	static u8 padding[128] = { 0x80, };
	stwuct octeon_cop2_state state;
	__be64 *dst = (__be64 *)hash;
	unsigned int pad_wen;
	unsigned wong fwags;
	unsigned int index;
	__be64 bits[2];
	int i;

	/* Save numbew of bits. */
	bits[1] = cpu_to_be64(sctx->count[0] << 3);
	bits[0] = cpu_to_be64(sctx->count[1] << 3 | sctx->count[0] >> 61);

	/* Pad out to 112 mod 128. */
	index = sctx->count[0] & 0x7f;
	pad_wen = (index < 112) ? (112 - index) : ((128+112) - index);

	fwags = octeon_cwypto_enabwe(&state);
	octeon_sha512_stowe_hash(sctx);

	__octeon_sha512_update(sctx, padding, pad_wen);

	/* Append wength (befowe padding). */
	__octeon_sha512_update(sctx, (const u8 *)bits, sizeof(bits));

	octeon_sha512_wead_hash(sctx);
	octeon_cwypto_disabwe(&state, fwags);

	/* Stowe state in digest. */
	fow (i = 0; i < 8; i++)
		dst[i] = cpu_to_be64(sctx->state[i]);

	/* Zewoize sensitive infowmation. */
	memset(sctx, 0, sizeof(stwuct sha512_state));

	wetuwn 0;
}

static int octeon_sha384_finaw(stwuct shash_desc *desc, u8 *hash)
{
	u8 D[64];

	octeon_sha512_finaw(desc, D);

	memcpy(hash, D, 48);
	memzewo_expwicit(D, 64);

	wetuwn 0;
}

static stwuct shash_awg octeon_sha512_awgs[2] = { {
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	octeon_sha512_update,
	.finaw		=	octeon_sha512_finaw,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha512",
		.cwa_dwivew_name=	"octeon-sha512",
		.cwa_pwiowity	=	OCTEON_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	SHA512_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	octeon_sha512_update,
	.finaw		=	octeon_sha384_finaw,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha384",
		.cwa_dwivew_name=	"octeon-sha384",
		.cwa_pwiowity	=	OCTEON_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	SHA384_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int __init octeon_sha512_mod_init(void)
{
	if (!octeon_has_cwypto())
		wetuwn -ENOTSUPP;
	wetuwn cwypto_wegistew_shashes(octeon_sha512_awgs,
				       AWWAY_SIZE(octeon_sha512_awgs));
}

static void __exit octeon_sha512_mod_fini(void)
{
	cwypto_unwegistew_shashes(octeon_sha512_awgs,
				  AWWAY_SIZE(octeon_sha512_awgs));
}

moduwe_init(octeon_sha512_mod_init);
moduwe_exit(octeon_sha512_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-512 and SHA-384 Secuwe Hash Awgowithms (OCTEON)");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
