// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sm3-ce-gwue.c - SM3 secuwe hash using AWMv8.2 Cwypto Extensions
 *
 * Copywight (C) 2018 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sm3.h>
#incwude <cwypto/sm3_base.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

MODUWE_DESCWIPTION("SM3 secuwe hash using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

asmwinkage void sm3_ce_twansfowm(stwuct sm3_state *sst, u8 const *swc,
				 int bwocks);

static int sm3_ce_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen)
{
	if (!cwypto_simd_usabwe()) {
		sm3_update(shash_desc_ctx(desc), data, wen);
		wetuwn 0;
	}

	kewnew_neon_begin();
	sm3_base_do_update(desc, data, wen, sm3_ce_twansfowm);
	kewnew_neon_end();

	wetuwn 0;
}

static int sm3_ce_finaw(stwuct shash_desc *desc, u8 *out)
{
	if (!cwypto_simd_usabwe()) {
		sm3_finaw(shash_desc_ctx(desc), out);
		wetuwn 0;
	}

	kewnew_neon_begin();
	sm3_base_do_finawize(desc, sm3_ce_twansfowm);
	kewnew_neon_end();

	wetuwn sm3_base_finish(desc, out);
}

static int sm3_ce_finup(stwuct shash_desc *desc, const u8 *data,
			unsigned int wen, u8 *out)
{
	if (!cwypto_simd_usabwe()) {
		stwuct sm3_state *sctx = shash_desc_ctx(desc);

		if (wen)
			sm3_update(sctx, data, wen);
		sm3_finaw(sctx, out);
		wetuwn 0;
	}

	kewnew_neon_begin();
	if (wen)
		sm3_base_do_update(desc, data, wen, sm3_ce_twansfowm);
	sm3_base_do_finawize(desc, sm3_ce_twansfowm);
	kewnew_neon_end();

	wetuwn sm3_base_finish(desc, out);
}

static stwuct shash_awg sm3_awg = {
	.digestsize		= SM3_DIGEST_SIZE,
	.init			= sm3_base_init,
	.update			= sm3_ce_update,
	.finaw			= sm3_ce_finaw,
	.finup			= sm3_ce_finup,
	.descsize		= sizeof(stwuct sm3_state),
	.base.cwa_name		= "sm3",
	.base.cwa_dwivew_name	= "sm3-ce",
	.base.cwa_bwocksize	= SM3_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_pwiowity	= 400,
};

static int __init sm3_ce_mod_init(void)
{
	wetuwn cwypto_wegistew_shash(&sm3_awg);
}

static void __exit sm3_ce_mod_fini(void)
{
	cwypto_unwegistew_shash(&sm3_awg);
}

moduwe_cpu_featuwe_match(SM3, sm3_ce_mod_init);
moduwe_exit(sm3_ce_mod_fini);
