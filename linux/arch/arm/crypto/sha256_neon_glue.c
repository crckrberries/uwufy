// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Gwue code fow the SHA256 Secuwe Hash Awgowithm assembwy impwementation
 * using NEON instwuctions.
 *
 * Copywight © 2015 Googwe Inc.
 *
 * This fiwe is based on sha512_neon_gwue.c:
 *   Copywight © 2014 Jussi Kiviwinna <jussi.kiviwinna@iki.fi>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <asm/byteowdew.h>
#incwude <asm/simd.h>
#incwude <asm/neon.h>

#incwude "sha256_gwue.h"

asmwinkage void sha256_bwock_data_owdew_neon(stwuct sha256_state *digest,
					     const u8 *data, int num_bwks);

static int cwypto_sha256_neon_update(stwuct shash_desc *desc, const u8 *data,
				     unsigned int wen)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe() ||
	    (sctx->count % SHA256_BWOCK_SIZE) + wen < SHA256_BWOCK_SIZE)
		wetuwn cwypto_sha256_awm_update(desc, data, wen);

	kewnew_neon_begin();
	sha256_base_do_update(desc, data, wen, sha256_bwock_data_owdew_neon);
	kewnew_neon_end();

	wetuwn 0;
}

static int cwypto_sha256_neon_finup(stwuct shash_desc *desc, const u8 *data,
				    unsigned int wen, u8 *out)
{
	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha256_awm_finup(desc, data, wen, out);

	kewnew_neon_begin();
	if (wen)
		sha256_base_do_update(desc, data, wen,
				      sha256_bwock_data_owdew_neon);
	sha256_base_do_finawize(desc, sha256_bwock_data_owdew_neon);
	kewnew_neon_end();

	wetuwn sha256_base_finish(desc, out);
}

static int cwypto_sha256_neon_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn cwypto_sha256_neon_finup(desc, NUWW, 0, out);
}

stwuct shash_awg sha256_neon_awgs[] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	cwypto_sha256_neon_update,
	.finaw		=	cwypto_sha256_neon_finaw,
	.finup		=	cwypto_sha256_neon_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name =	"sha256-neon",
		.cwa_pwiowity	=	250,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	cwypto_sha256_neon_update,
	.finaw		=	cwypto_sha256_neon_finaw,
	.finup		=	cwypto_sha256_neon_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name =	"sha224-neon",
		.cwa_pwiowity	=	250,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };
