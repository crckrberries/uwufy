// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sha512-neon-gwue.c - accewewated SHA-384/512 fow AWM NEON
 *
 * Copywight (C) 2015 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha512_base.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

#incwude <asm/simd.h>
#incwude <asm/neon.h>

#incwude "sha512.h"

MODUWE_AWIAS_CWYPTO("sha384-neon");
MODUWE_AWIAS_CWYPTO("sha512-neon");

asmwinkage void sha512_bwock_data_owdew_neon(stwuct sha512_state *state,
					     const u8 *swc, int bwocks);

static int sha512_neon_update(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe() ||
	    (sctx->count[0] % SHA512_BWOCK_SIZE) + wen < SHA512_BWOCK_SIZE)
		wetuwn sha512_awm_update(desc, data, wen);

	kewnew_neon_begin();
	sha512_base_do_update(desc, data, wen, sha512_bwock_data_owdew_neon);
	kewnew_neon_end();

	wetuwn 0;
}

static int sha512_neon_finup(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen, u8 *out)
{
	if (!cwypto_simd_usabwe())
		wetuwn sha512_awm_finup(desc, data, wen, out);

	kewnew_neon_begin();
	if (wen)
		sha512_base_do_update(desc, data, wen,
				      sha512_bwock_data_owdew_neon);
	sha512_base_do_finawize(desc, sha512_bwock_data_owdew_neon);
	kewnew_neon_end();

	wetuwn sha512_base_finish(desc, out);
}

static int sha512_neon_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha512_neon_finup(desc, NUWW, 0, out);
}

stwuct shash_awg sha512_neon_awgs[] = { {
	.init			= sha384_base_init,
	.update			= sha512_neon_update,
	.finaw			= sha512_neon_finaw,
	.finup			= sha512_neon_finup,
	.descsize		= sizeof(stwuct sha512_state),
	.digestsize		= SHA384_DIGEST_SIZE,
	.base			= {
		.cwa_name		= "sha384",
		.cwa_dwivew_name	= "sha384-neon",
		.cwa_pwiowity		= 300,
		.cwa_bwocksize		= SHA384_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,

	}
},  {
	.init			= sha512_base_init,
	.update			= sha512_neon_update,
	.finaw			= sha512_neon_finaw,
	.finup			= sha512_neon_finup,
	.descsize		= sizeof(stwuct sha512_state),
	.digestsize		= SHA512_DIGEST_SIZE,
	.base			= {
		.cwa_name		= "sha512",
		.cwa_dwivew_name	= "sha512-neon",
		.cwa_pwiowity		= 300,
		.cwa_bwocksize		= SHA512_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	}
} };
