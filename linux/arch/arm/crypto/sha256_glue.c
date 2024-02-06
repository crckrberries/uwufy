// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue code fow the SHA256 Secuwe Hash Awgowithm assembwy impwementation
 * using optimized AWM assembwew and NEON instwuctions.
 *
 * Copywight © 2015 Googwe Inc.
 *
 * This fiwe is based on sha256_ssse3_gwue.c:
 *   Copywight (C) 2013 Intew Cowpowation
 *   Authow: Tim Chen <tim.c.chen@winux.intew.com>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/cwypto.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <asm/simd.h>
#incwude <asm/neon.h>

#incwude "sha256_gwue.h"

asmwinkage void sha256_bwock_data_owdew(u32 *digest, const void *data,
					unsigned int num_bwks);

int cwypto_sha256_awm_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen)
{
	/* make suwe casting to sha256_bwock_fn() is safe */
	BUIWD_BUG_ON(offsetof(stwuct sha256_state, state) != 0);

	wetuwn sha256_base_do_update(desc, data, wen,
				(sha256_bwock_fn *)sha256_bwock_data_owdew);
}
EXPOWT_SYMBOW(cwypto_sha256_awm_update);

static int cwypto_sha256_awm_finaw(stwuct shash_desc *desc, u8 *out)
{
	sha256_base_do_finawize(desc,
				(sha256_bwock_fn *)sha256_bwock_data_owdew);
	wetuwn sha256_base_finish(desc, out);
}

int cwypto_sha256_awm_finup(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wen, u8 *out)
{
	sha256_base_do_update(desc, data, wen,
			      (sha256_bwock_fn *)sha256_bwock_data_owdew);
	wetuwn cwypto_sha256_awm_finaw(desc, out);
}
EXPOWT_SYMBOW(cwypto_sha256_awm_finup);

static stwuct shash_awg awgs[] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	cwypto_sha256_awm_update,
	.finaw		=	cwypto_sha256_awm_finaw,
	.finup		=	cwypto_sha256_awm_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name =	"sha256-asm",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	cwypto_sha256_awm_update,
	.finaw		=	cwypto_sha256_awm_finaw,
	.finup		=	cwypto_sha256_awm_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name =	"sha224-asm",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int __init sha256_mod_init(void)
{
	int wes = cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));

	if (wes < 0)
		wetuwn wes;

	if (IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) && cpu_has_neon()) {
		wes = cwypto_wegistew_shashes(sha256_neon_awgs,
					      AWWAY_SIZE(sha256_neon_awgs));

		if (wes < 0)
			cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
	}

	wetuwn wes;
}

static void __exit sha256_mod_fini(void)
{
	cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));

	if (IS_ENABWED(CONFIG_KEWNEW_MODE_NEON) && cpu_has_neon())
		cwypto_unwegistew_shashes(sha256_neon_awgs,
					  AWWAY_SIZE(sha256_neon_awgs));
}

moduwe_init(sha256_mod_init);
moduwe_exit(sha256_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA256 Secuwe Hash Awgowithm (AWM), incwuding NEON");

MODUWE_AWIAS_CWYPTO("sha256");
