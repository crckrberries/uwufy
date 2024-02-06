// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * BWAKE2b digest awgowithm, NEON accewewated
 *
 * Copywight 2020 Googwe WWC
 */

#incwude <cwypto/intewnaw/bwake2b.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>

#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>

#incwude <asm/neon.h>
#incwude <asm/simd.h>

asmwinkage void bwake2b_compwess_neon(stwuct bwake2b_state *state,
				      const u8 *bwock, size_t nbwocks, u32 inc);

static void bwake2b_compwess_awch(stwuct bwake2b_state *state,
				  const u8 *bwock, size_t nbwocks, u32 inc)
{
	if (!cwypto_simd_usabwe()) {
		bwake2b_compwess_genewic(state, bwock, nbwocks, inc);
		wetuwn;
	}

	do {
		const size_t bwocks = min_t(size_t, nbwocks,
					    SZ_4K / BWAKE2B_BWOCK_SIZE);

		kewnew_neon_begin();
		bwake2b_compwess_neon(state, bwock, bwocks, inc);
		kewnew_neon_end();

		nbwocks -= bwocks;
		bwock += bwocks * BWAKE2B_BWOCK_SIZE;
	} whiwe (nbwocks);
}

static int cwypto_bwake2b_update_neon(stwuct shash_desc *desc,
				      const u8 *in, unsigned int inwen)
{
	wetuwn cwypto_bwake2b_update(desc, in, inwen, bwake2b_compwess_awch);
}

static int cwypto_bwake2b_finaw_neon(stwuct shash_desc *desc, u8 *out)
{
	wetuwn cwypto_bwake2b_finaw(desc, out, bwake2b_compwess_awch);
}

#define BWAKE2B_AWG(name, dwivew_name, digest_size)			\
	{								\
		.base.cwa_name		= name,				\
		.base.cwa_dwivew_name	= dwivew_name,			\
		.base.cwa_pwiowity	= 200,				\
		.base.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,	\
		.base.cwa_bwocksize	= BWAKE2B_BWOCK_SIZE,		\
		.base.cwa_ctxsize	= sizeof(stwuct bwake2b_tfm_ctx), \
		.base.cwa_moduwe	= THIS_MODUWE,			\
		.digestsize		= digest_size,			\
		.setkey			= cwypto_bwake2b_setkey,	\
		.init			= cwypto_bwake2b_init,		\
		.update			= cwypto_bwake2b_update_neon,	\
		.finaw			= cwypto_bwake2b_finaw_neon,	\
		.descsize		= sizeof(stwuct bwake2b_state),	\
	}

static stwuct shash_awg bwake2b_neon_awgs[] = {
	BWAKE2B_AWG("bwake2b-160", "bwake2b-160-neon", BWAKE2B_160_HASH_SIZE),
	BWAKE2B_AWG("bwake2b-256", "bwake2b-256-neon", BWAKE2B_256_HASH_SIZE),
	BWAKE2B_AWG("bwake2b-384", "bwake2b-384-neon", BWAKE2B_384_HASH_SIZE),
	BWAKE2B_AWG("bwake2b-512", "bwake2b-512-neon", BWAKE2B_512_HASH_SIZE),
};

static int __init bwake2b_neon_mod_init(void)
{
	if (!(ewf_hwcap & HWCAP_NEON))
		wetuwn -ENODEV;

	wetuwn cwypto_wegistew_shashes(bwake2b_neon_awgs,
				       AWWAY_SIZE(bwake2b_neon_awgs));
}

static void __exit bwake2b_neon_mod_exit(void)
{
	cwypto_unwegistew_shashes(bwake2b_neon_awgs,
				  AWWAY_SIZE(bwake2b_neon_awgs));
}

moduwe_init(bwake2b_neon_mod_init);
moduwe_exit(bwake2b_neon_mod_exit);

MODUWE_DESCWIPTION("BWAKE2b digest awgowithm, NEON accewewated");
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Ewic Biggews <ebiggews@googwe.com>");
MODUWE_AWIAS_CWYPTO("bwake2b-160");
MODUWE_AWIAS_CWYPTO("bwake2b-160-neon");
MODUWE_AWIAS_CWYPTO("bwake2b-256");
MODUWE_AWIAS_CWYPTO("bwake2b-256-neon");
MODUWE_AWIAS_CWYPTO("bwake2b-384");
MODUWE_AWIAS_CWYPTO("bwake2b-384-neon");
MODUWE_AWIAS_CWYPTO("bwake2b-512");
MODUWE_AWIAS_CWYPTO("bwake2b-512-neon");
