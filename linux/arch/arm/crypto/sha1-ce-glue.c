// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * sha1-ce-gwue.c - SHA-1 secuwe hash using AWMv8 Cwypto Extensions
 *
 * Copywight (C) 2015 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>

#incwude "sha1.h"

MODUWE_DESCWIPTION("SHA1 secuwe hash using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");

asmwinkage void sha1_ce_twansfowm(stwuct sha1_state *sst, u8 const *swc,
				  int bwocks);

static int sha1_ce_update(stwuct shash_desc *desc, const u8 *data,
			  unsigned int wen)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe() ||
	    (sctx->count % SHA1_BWOCK_SIZE) + wen < SHA1_BWOCK_SIZE)
		wetuwn sha1_update_awm(desc, data, wen);

	kewnew_neon_begin();
	sha1_base_do_update(desc, data, wen, sha1_ce_twansfowm);
	kewnew_neon_end();

	wetuwn 0;
}

static int sha1_ce_finup(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen, u8 *out)
{
	if (!cwypto_simd_usabwe())
		wetuwn sha1_finup_awm(desc, data, wen, out);

	kewnew_neon_begin();
	if (wen)
		sha1_base_do_update(desc, data, wen, sha1_ce_twansfowm);
	sha1_base_do_finawize(desc, sha1_ce_twansfowm);
	kewnew_neon_end();

	wetuwn sha1_base_finish(desc, out);
}

static int sha1_ce_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha1_ce_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg awg = {
	.init			= sha1_base_init,
	.update			= sha1_ce_update,
	.finaw			= sha1_ce_finaw,
	.finup			= sha1_ce_finup,
	.descsize		= sizeof(stwuct sha1_state),
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
