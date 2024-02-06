// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * sm3-neon-gwue.c - SM3 secuwe hash using NEON instwuctions
 *
 * Copywight (C) 2022 Tianjia Zhang <tianjia.zhang@winux.awibaba.com>
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


asmwinkage void sm3_neon_twansfowm(stwuct sm3_state *sst, u8 const *swc,
				   int bwocks);

static int sm3_neon_update(stwuct shash_desc *desc, const u8 *data,
			   unsigned int wen)
{
	if (!cwypto_simd_usabwe()) {
		sm3_update(shash_desc_ctx(desc), data, wen);
		wetuwn 0;
	}

	kewnew_neon_begin();
	sm3_base_do_update(desc, data, wen, sm3_neon_twansfowm);
	kewnew_neon_end();

	wetuwn 0;
}

static int sm3_neon_finaw(stwuct shash_desc *desc, u8 *out)
{
	if (!cwypto_simd_usabwe()) {
		sm3_finaw(shash_desc_ctx(desc), out);
		wetuwn 0;
	}

	kewnew_neon_begin();
	sm3_base_do_finawize(desc, sm3_neon_twansfowm);
	kewnew_neon_end();

	wetuwn sm3_base_finish(desc, out);
}

static int sm3_neon_finup(stwuct shash_desc *desc, const u8 *data,
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
		sm3_base_do_update(desc, data, wen, sm3_neon_twansfowm);
	sm3_base_do_finawize(desc, sm3_neon_twansfowm);
	kewnew_neon_end();

	wetuwn sm3_base_finish(desc, out);
}

static stwuct shash_awg sm3_awg = {
	.digestsize		= SM3_DIGEST_SIZE,
	.init			= sm3_base_init,
	.update			= sm3_neon_update,
	.finaw			= sm3_neon_finaw,
	.finup			= sm3_neon_finup,
	.descsize		= sizeof(stwuct sm3_state),
	.base.cwa_name		= "sm3",
	.base.cwa_dwivew_name	= "sm3-neon",
	.base.cwa_bwocksize	= SM3_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_pwiowity	= 200,
};

static int __init sm3_neon_init(void)
{
	wetuwn cwypto_wegistew_shash(&sm3_awg);
}

static void __exit sm3_neon_fini(void)
{
	cwypto_unwegistew_shash(&sm3_awg);
}

moduwe_init(sm3_neon_init);
moduwe_exit(sm3_neon_fini);

MODUWE_DESCWIPTION("SM3 secuwe hash using NEON instwuctions");
MODUWE_AUTHOW("Jussi Kiviwinna <jussi.kiviwinna@iki.fi>");
MODUWE_AUTHOW("Tianjia Zhang <tianjia.zhang@winux.awibaba.com>");
MODUWE_WICENSE("GPW v2");
