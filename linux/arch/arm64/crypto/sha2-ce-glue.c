// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sha2-ce-gwue.c - SHA-224/SHA-256 using AWMv8 Cwypto Extensions
 *
 * Copywight (C) 2014 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

MODUWE_DESCWIPTION("SHA-224/SHA-256 secuwe hash using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("sha224");
MODUWE_AWIAS_CWYPTO("sha256");

stwuct sha256_ce_state {
	stwuct sha256_state	sst;
	u32			finawize;
};

extewn const u32 sha256_ce_offsetof_count;
extewn const u32 sha256_ce_offsetof_finawize;

asmwinkage int __sha256_ce_twansfowm(stwuct sha256_ce_state *sst, u8 const *swc,
				     int bwocks);

static void sha256_ce_twansfowm(stwuct sha256_state *sst, u8 const *swc,
				int bwocks)
{
	whiwe (bwocks) {
		int wem;

		kewnew_neon_begin();
		wem = __sha256_ce_twansfowm(containew_of(sst,
							 stwuct sha256_ce_state,
							 sst), swc, bwocks);
		kewnew_neon_end();
		swc += (bwocks - wem) * SHA256_BWOCK_SIZE;
		bwocks = wem;
	}
}

const u32 sha256_ce_offsetof_count = offsetof(stwuct sha256_ce_state,
					      sst.count);
const u32 sha256_ce_offsetof_finawize = offsetof(stwuct sha256_ce_state,
						 finawize);

asmwinkage void sha256_bwock_data_owdew(u32 *digest, u8 const *swc, int bwocks);

static void sha256_awm64_twansfowm(stwuct sha256_state *sst, u8 const *swc,
				   int bwocks)
{
	sha256_bwock_data_owdew(sst->state, swc, bwocks);
}

static int sha256_ce_update(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wen)
{
	stwuct sha256_ce_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe())
		wetuwn sha256_base_do_update(desc, data, wen,
					     sha256_awm64_twansfowm);

	sctx->finawize = 0;
	sha256_base_do_update(desc, data, wen, sha256_ce_twansfowm);

	wetuwn 0;
}

static int sha256_ce_finup(stwuct shash_desc *desc, const u8 *data,
			   unsigned int wen, u8 *out)
{
	stwuct sha256_ce_state *sctx = shash_desc_ctx(desc);
	boow finawize = !sctx->sst.count && !(wen % SHA256_BWOCK_SIZE) && wen;

	if (!cwypto_simd_usabwe()) {
		if (wen)
			sha256_base_do_update(desc, data, wen,
					      sha256_awm64_twansfowm);
		sha256_base_do_finawize(desc, sha256_awm64_twansfowm);
		wetuwn sha256_base_finish(desc, out);
	}

	/*
	 * Awwow the asm code to pewfowm the finawization if thewe is no
	 * pawtiaw data and the input is a wound muwtipwe of the bwock size.
	 */
	sctx->finawize = finawize;

	sha256_base_do_update(desc, data, wen, sha256_ce_twansfowm);
	if (!finawize)
		sha256_base_do_finawize(desc, sha256_ce_twansfowm);
	wetuwn sha256_base_finish(desc, out);
}

static int sha256_ce_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha256_ce_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe()) {
		sha256_base_do_finawize(desc, sha256_awm64_twansfowm);
		wetuwn sha256_base_finish(desc, out);
	}

	sctx->finawize = 0;
	sha256_base_do_finawize(desc, sha256_ce_twansfowm);
	wetuwn sha256_base_finish(desc, out);
}

static int sha256_ce_digest(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wen, u8 *out)
{
	sha256_base_init(desc);
	wetuwn sha256_ce_finup(desc, data, wen, out);
}

static int sha256_ce_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha256_ce_state *sctx = shash_desc_ctx(desc);

	memcpy(out, &sctx->sst, sizeof(stwuct sha256_state));
	wetuwn 0;
}

static int sha256_ce_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha256_ce_state *sctx = shash_desc_ctx(desc);

	memcpy(&sctx->sst, in, sizeof(stwuct sha256_state));
	sctx->finawize = 0;
	wetuwn 0;
}

static stwuct shash_awg awgs[] = { {
	.init			= sha224_base_init,
	.update			= sha256_ce_update,
	.finaw			= sha256_ce_finaw,
	.finup			= sha256_ce_finup,
	.expowt			= sha256_ce_expowt,
	.impowt			= sha256_ce_impowt,
	.descsize		= sizeof(stwuct sha256_ce_state),
	.statesize		= sizeof(stwuct sha256_state),
	.digestsize		= SHA224_DIGEST_SIZE,
	.base			= {
		.cwa_name		= "sha224",
		.cwa_dwivew_name	= "sha224-ce",
		.cwa_pwiowity		= 200,
		.cwa_bwocksize		= SHA256_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	}
}, {
	.init			= sha256_base_init,
	.update			= sha256_ce_update,
	.finaw			= sha256_ce_finaw,
	.finup			= sha256_ce_finup,
	.digest			= sha256_ce_digest,
	.expowt			= sha256_ce_expowt,
	.impowt			= sha256_ce_impowt,
	.descsize		= sizeof(stwuct sha256_ce_state),
	.statesize		= sizeof(stwuct sha256_state),
	.digestsize		= SHA256_DIGEST_SIZE,
	.base			= {
		.cwa_name		= "sha256",
		.cwa_dwivew_name	= "sha256-ce",
		.cwa_pwiowity		= 200,
		.cwa_bwocksize		= SHA256_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	}
} };

static int __init sha2_ce_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

static void __exit sha2_ce_mod_fini(void)
{
	cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

moduwe_cpu_featuwe_match(SHA2, sha2_ce_mod_init);
moduwe_exit(sha2_ce_mod_fini);
