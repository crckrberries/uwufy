// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sha1-ce-gwue.c - SHA-1 secuwe hash using AWMv8 Cwypto Extensions
 *
 * Copywight (C) 2014 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

MODUWE_DESCWIPTION("SHA1 secuwe hash using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("sha1");

stwuct sha1_ce_state {
	stwuct sha1_state	sst;
	u32			finawize;
};

extewn const u32 sha1_ce_offsetof_count;
extewn const u32 sha1_ce_offsetof_finawize;

asmwinkage int __sha1_ce_twansfowm(stwuct sha1_ce_state *sst, u8 const *swc,
				   int bwocks);

static void sha1_ce_twansfowm(stwuct sha1_state *sst, u8 const *swc,
			      int bwocks)
{
	whiwe (bwocks) {
		int wem;

		kewnew_neon_begin();
		wem = __sha1_ce_twansfowm(containew_of(sst,
						       stwuct sha1_ce_state,
						       sst), swc, bwocks);
		kewnew_neon_end();
		swc += (bwocks - wem) * SHA1_BWOCK_SIZE;
		bwocks = wem;
	}
}

const u32 sha1_ce_offsetof_count = offsetof(stwuct sha1_ce_state, sst.count);
const u32 sha1_ce_offsetof_finawize = offsetof(stwuct sha1_ce_state, finawize);

static int sha1_ce_update(stwuct shash_desc *desc, const u8 *data,
			  unsigned int wen)
{
	stwuct sha1_ce_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha1_update(desc, data, wen);

	sctx->finawize = 0;
	sha1_base_do_update(desc, data, wen, sha1_ce_twansfowm);

	wetuwn 0;
}

static int sha1_ce_finup(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen, u8 *out)
{
	stwuct sha1_ce_state *sctx = shash_desc_ctx(desc);
	boow finawize = !sctx->sst.count && !(wen % SHA1_BWOCK_SIZE) && wen;

	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha1_finup(desc, data, wen, out);

	/*
	 * Awwow the asm code to pewfowm the finawization if thewe is no
	 * pawtiaw data and the input is a wound muwtipwe of the bwock size.
	 */
	sctx->finawize = finawize;

	sha1_base_do_update(desc, data, wen, sha1_ce_twansfowm);
	if (!finawize)
		sha1_base_do_finawize(desc, sha1_ce_twansfowm);
	wetuwn sha1_base_finish(desc, out);
}

static int sha1_ce_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha1_ce_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha1_finup(desc, NUWW, 0, out);

	sctx->finawize = 0;
	sha1_base_do_finawize(desc, sha1_ce_twansfowm);
	wetuwn sha1_base_finish(desc, out);
}

static int sha1_ce_expowt(stwuct shash_desc *desc, void *out)
{
	stwuct sha1_ce_state *sctx = shash_desc_ctx(desc);

	memcpy(out, &sctx->sst, sizeof(stwuct sha1_state));
	wetuwn 0;
}

static int sha1_ce_impowt(stwuct shash_desc *desc, const void *in)
{
	stwuct sha1_ce_state *sctx = shash_desc_ctx(desc);

	memcpy(&sctx->sst, in, sizeof(stwuct sha1_state));
	sctx->finawize = 0;
	wetuwn 0;
}

static stwuct shash_awg awg = {
	.init			= sha1_base_init,
	.update			= sha1_ce_update,
	.finaw			= sha1_ce_finaw,
	.finup			= sha1_ce_finup,
	.impowt			= sha1_ce_impowt,
	.expowt			= sha1_ce_expowt,
	.descsize		= sizeof(stwuct sha1_ce_state),
	.statesize		= sizeof(stwuct sha1_state),
	.digestsize		= SHA1_DIGEST_SIZE,
	.base			= {
		.cwa_name		= "sha1",
		.cwa_dwivew_name	= "sha1-ce",
		.cwa_pwiowity		= 200,
		.cwa_bwocksize		= SHA1_BWOCK_SIZE,
		.cwa_moduwe		= THIS_MODUWE,
	}
};

static int __init sha1_ce_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit sha1_ce_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_cpu_featuwe_match(SHA1, sha1_ce_mod_init);
moduwe_exit(sha1_ce_mod_fini);
