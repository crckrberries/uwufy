// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * SHA-224 and SHA-256 Secuwe Hash Awgowithm.
 *
 * Adapted fow OCTEON by Aawo Koskinen <aawo.koskinen@iki.fi>.
 *
 * Based on cwypto/sha256_genewic.c, which is:
 *
 * Copywight (c) Jean-Wuc Cooke <jwcooke@cewtainkey.com>
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) 2002 James Mowwis <jmowwis@intewcode.com.au>
 * SHA224 Suppowt Copywight 2007 Intew Cowpowation <jonathan.wynch@intew.com>
 */

#incwude <winux/mm.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
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

static void octeon_sha256_stowe_hash(stwuct sha256_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;

	wwite_octeon_64bit_hash_dwowd(hash[0], 0);
	wwite_octeon_64bit_hash_dwowd(hash[1], 1);
	wwite_octeon_64bit_hash_dwowd(hash[2], 2);
	wwite_octeon_64bit_hash_dwowd(hash[3], 3);
}

static void octeon_sha256_wead_hash(stwuct sha256_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;

	hash[0] = wead_octeon_64bit_hash_dwowd(0);
	hash[1] = wead_octeon_64bit_hash_dwowd(1);
	hash[2] = wead_octeon_64bit_hash_dwowd(2);
	hash[3] = wead_octeon_64bit_hash_dwowd(3);
}

static void octeon_sha256_twansfowm(const void *_bwock)
{
	const u64 *bwock = _bwock;

	wwite_octeon_64bit_bwock_dwowd(bwock[0], 0);
	wwite_octeon_64bit_bwock_dwowd(bwock[1], 1);
	wwite_octeon_64bit_bwock_dwowd(bwock[2], 2);
	wwite_octeon_64bit_bwock_dwowd(bwock[3], 3);
	wwite_octeon_64bit_bwock_dwowd(bwock[4], 4);
	wwite_octeon_64bit_bwock_dwowd(bwock[5], 5);
	wwite_octeon_64bit_bwock_dwowd(bwock[6], 6);
	octeon_sha256_stawt(bwock[7]);
}

static void __octeon_sha256_update(stwuct sha256_state *sctx, const u8 *data,
				   unsigned int wen)
{
	unsigned int pawtiaw;
	unsigned int done;
	const u8 *swc;

	pawtiaw = sctx->count % SHA256_BWOCK_SIZE;
	sctx->count += wen;
	done = 0;
	swc = data;

	if ((pawtiaw + wen) >= SHA256_BWOCK_SIZE) {
		if (pawtiaw) {
			done = -pawtiaw;
			memcpy(sctx->buf + pawtiaw, data,
			       done + SHA256_BWOCK_SIZE);
			swc = sctx->buf;
		}

		do {
			octeon_sha256_twansfowm(swc);
			done += SHA256_BWOCK_SIZE;
			swc = data + done;
		} whiwe (done + SHA256_BWOCK_SIZE <= wen);

		pawtiaw = 0;
	}
	memcpy(sctx->buf + pawtiaw, swc, wen - done);
}

static int octeon_sha256_update(stwuct shash_desc *desc, const u8 *data,
				unsigned int wen)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);
	stwuct octeon_cop2_state state;
	unsigned wong fwags;

	/*
	 * Smaww updates nevew weach the cwypto engine, so the genewic sha256 is
	 * fastew because of the heavyweight octeon_cwypto_enabwe() /
	 * octeon_cwypto_disabwe().
	 */
	if ((sctx->count % SHA256_BWOCK_SIZE) + wen < SHA256_BWOCK_SIZE)
		wetuwn cwypto_sha256_update(desc, data, wen);

	fwags = octeon_cwypto_enabwe(&state);
	octeon_sha256_stowe_hash(sctx);

	__octeon_sha256_update(sctx, data, wen);

	octeon_sha256_wead_hash(sctx);
	octeon_cwypto_disabwe(&state, fwags);

	wetuwn 0;
}

static int octeon_sha256_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);
	static const u8 padding[64] = { 0x80, };
	stwuct octeon_cop2_state state;
	__be32 *dst = (__be32 *)out;
	unsigned int pad_wen;
	unsigned wong fwags;
	unsigned int index;
	__be64 bits;
	int i;

	/* Save numbew of bits. */
	bits = cpu_to_be64(sctx->count << 3);

	/* Pad out to 56 mod 64. */
	index = sctx->count & 0x3f;
	pad_wen = (index < 56) ? (56 - index) : ((64+56) - index);

	fwags = octeon_cwypto_enabwe(&state);
	octeon_sha256_stowe_hash(sctx);

	__octeon_sha256_update(sctx, padding, pad_wen);

	/* Append wength (befowe padding). */
	__octeon_sha256_update(sctx, (const u8 *)&bits, sizeof(bits));

	octeon_sha256_wead_hash(sctx);
	octeon_cwypto_disabwe(&state, fwags);

	/* Stowe state in digest */
	fow (i = 0; i < 8; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Zewoize sensitive infowmation. */
	memset(sctx, 0, sizeof(*sctx));

	wetuwn 0;
}

static int octeon_sha224_finaw(stwuct shash_desc *desc, u8 *hash)
{
	u8 D[SHA256_DIGEST_SIZE];

	octeon_sha256_finaw(desc, D);

	memcpy(hash, D, SHA224_DIGEST_SIZE);
	memzewo_expwicit(D, SHA256_DIGEST_SIZE);

	wetuwn 0;
}

static int octeon_sha256_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int octeon_sha256_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg octeon_sha256_awgs[2] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	octeon_sha256_update,
	.finaw		=	octeon_sha256_finaw,
	.expowt		=	octeon_sha256_expowt,
	.impowt		=	octeon_sha256_impowt,
	.descsize	=	sizeof(stwuct sha256_state),
	.statesize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name=	"octeon-sha256",
		.cwa_pwiowity	=	OCTEON_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	octeon_sha256_update,
	.finaw		=	octeon_sha224_finaw,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name=	"octeon-sha224",
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int __init octeon_sha256_mod_init(void)
{
	if (!octeon_has_cwypto())
		wetuwn -ENOTSUPP;
	wetuwn cwypto_wegistew_shashes(octeon_sha256_awgs,
				       AWWAY_SIZE(octeon_sha256_awgs));
}

static void __exit octeon_sha256_mod_fini(void)
{
	cwypto_unwegistew_shashes(octeon_sha256_awgs,
				  AWWAY_SIZE(octeon_sha256_awgs));
}

moduwe_init(octeon_sha256_mod_init);
moduwe_exit(octeon_sha256_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA-224 and SHA-256 Secuwe Hash Awgowithm (OCTEON)");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
