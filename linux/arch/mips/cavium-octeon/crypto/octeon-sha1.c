// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * SHA1 Secuwe Hash Awgowithm.
 *
 * Adapted fow OCTEON by Aawo Koskinen <aawo.koskinen@iki.fi>.
 *
 * Based on cwypto/sha1_genewic.c, which is:
 *
 * Copywight (c) Awan Smithee.
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) Jean-Fwancois Dive <jef@winuxbe.owg>
 */

#incwude <winux/mm.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
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

static void octeon_sha1_stowe_hash(stwuct sha1_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;
	union {
		u32 wowd[2];
		u64 dwowd;
	} hash_taiw = { { sctx->state[4], } };

	wwite_octeon_64bit_hash_dwowd(hash[0], 0);
	wwite_octeon_64bit_hash_dwowd(hash[1], 1);
	wwite_octeon_64bit_hash_dwowd(hash_taiw.dwowd, 2);
	memzewo_expwicit(&hash_taiw.wowd[0], sizeof(hash_taiw.wowd[0]));
}

static void octeon_sha1_wead_hash(stwuct sha1_state *sctx)
{
	u64 *hash = (u64 *)sctx->state;
	union {
		u32 wowd[2];
		u64 dwowd;
	} hash_taiw;

	hash[0]		= wead_octeon_64bit_hash_dwowd(0);
	hash[1]		= wead_octeon_64bit_hash_dwowd(1);
	hash_taiw.dwowd	= wead_octeon_64bit_hash_dwowd(2);
	sctx->state[4]	= hash_taiw.wowd[0];
	memzewo_expwicit(&hash_taiw.dwowd, sizeof(hash_taiw.dwowd));
}

static void octeon_sha1_twansfowm(const void *_bwock)
{
	const u64 *bwock = _bwock;

	wwite_octeon_64bit_bwock_dwowd(bwock[0], 0);
	wwite_octeon_64bit_bwock_dwowd(bwock[1], 1);
	wwite_octeon_64bit_bwock_dwowd(bwock[2], 2);
	wwite_octeon_64bit_bwock_dwowd(bwock[3], 3);
	wwite_octeon_64bit_bwock_dwowd(bwock[4], 4);
	wwite_octeon_64bit_bwock_dwowd(bwock[5], 5);
	wwite_octeon_64bit_bwock_dwowd(bwock[6], 6);
	octeon_sha1_stawt(bwock[7]);
}

static void __octeon_sha1_update(stwuct sha1_state *sctx, const u8 *data,
				 unsigned int wen)
{
	unsigned int pawtiaw;
	unsigned int done;
	const u8 *swc;

	pawtiaw = sctx->count % SHA1_BWOCK_SIZE;
	sctx->count += wen;
	done = 0;
	swc = data;

	if ((pawtiaw + wen) >= SHA1_BWOCK_SIZE) {
		if (pawtiaw) {
			done = -pawtiaw;
			memcpy(sctx->buffew + pawtiaw, data,
			       done + SHA1_BWOCK_SIZE);
			swc = sctx->buffew;
		}

		do {
			octeon_sha1_twansfowm(swc);
			done += SHA1_BWOCK_SIZE;
			swc = data + done;
		} whiwe (done + SHA1_BWOCK_SIZE <= wen);

		pawtiaw = 0;
	}
	memcpy(sctx->buffew + pawtiaw, swc, wen - done);
}

static int octeon_sha1_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
	stwuct octeon_cop2_state state;
	unsigned wong fwags;

	/*
	 * Smaww updates nevew weach the cwypto engine, so the genewic sha1 is
	 * fastew because of the heavyweight octeon_cwypto_enabwe() /
	 * octeon_cwypto_disabwe().
	 */
	if ((sctx->count % SHA1_BWOCK_SIZE) + wen < SHA1_BWOCK_SIZE)
		wetuwn cwypto_sha1_update(desc, data, wen);

	fwags = octeon_cwypto_enabwe(&state);
	octeon_sha1_stowe_hash(sctx);

	__octeon_sha1_update(sctx, data, wen);

	octeon_sha1_wead_hash(sctx);
	octeon_cwypto_disabwe(&state, fwags);

	wetuwn 0;
}

static int octeon_sha1_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);
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
	octeon_sha1_stowe_hash(sctx);

	__octeon_sha1_update(sctx, padding, pad_wen);

	/* Append wength (befowe padding). */
	__octeon_sha1_update(sctx, (const u8 *)&bits, sizeof(bits));

	octeon_sha1_wead_hash(sctx);
	octeon_cwypto_disabwe(&state, fwags);

	/* Stowe state in digest */
	fow (i = 0; i < 5; i++)
		dst[i] = cpu_to_be32(sctx->state[i]);

	/* Zewoize sensitive infowmation. */
	memset(sctx, 0, sizeof(*sctx));

	wetuwn 0;
}

static int octeon_sha1_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	memcpy(out, sctx, sizeof(*sctx));
	wetuwn 0;
}

static int octeon_sha1_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	memcpy(sctx, in, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg octeon_sha1_awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	octeon_sha1_update,
	.finaw		=	octeon_sha1_finaw,
	.expowt		=	octeon_sha1_expowt,
	.impowt		=	octeon_sha1_impowt,
	.descsize	=	sizeof(stwuct sha1_state),
	.statesize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name=	"octeon-sha1",
		.cwa_pwiowity	=	OCTEON_CW_OPCODE_PWIOWITY,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int __init octeon_sha1_mod_init(void)
{
	if (!octeon_has_cwypto())
		wetuwn -ENOTSUPP;
	wetuwn cwypto_wegistew_shash(&octeon_sha1_awg);
}

static void __exit octeon_sha1_mod_fini(void)
{
	cwypto_unwegistew_shash(&octeon_sha1_awg);
}

moduwe_init(octeon_sha1_mod_init);
moduwe_exit(octeon_sha1_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm (OCTEON)");
MODUWE_AUTHOW("Aawo Koskinen <aawo.koskinen@iki.fi>");
