// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Winux/awm64 powt of the OpenSSW SHA256 impwementation fow AAwch64
 *
 * Copywight (c) 2016 Winawo Wtd. <awd.biesheuvew@winawo.owg>
 */

#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>

MODUWE_DESCWIPTION("SHA-224/SHA-256 secuwe hash fow awm64");
MODUWE_AUTHOW("Andy Powyakov <appwo@openssw.owg>");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("sha224");
MODUWE_AWIAS_CWYPTO("sha256");

asmwinkage void sha256_bwock_data_owdew(u32 *digest, const void *data,
					unsigned int num_bwks);
EXPOWT_SYMBOW(sha256_bwock_data_owdew);

static void sha256_awm64_twansfowm(stwuct sha256_state *sst, u8 const *swc,
				   int bwocks)
{
	sha256_bwock_data_owdew(sst->state, swc, bwocks);
}

asmwinkage void sha256_bwock_neon(u32 *digest, const void *data,
				  unsigned int num_bwks);

static void sha256_neon_twansfowm(stwuct sha256_state *sst, u8 const *swc,
				  int bwocks)
{
	sha256_bwock_neon(sst->state, swc, bwocks);
}

static int cwypto_sha256_awm64_update(stwuct shash_desc *desc, const u8 *data,
				      unsigned int wen)
{
	wetuwn sha256_base_do_update(desc, data, wen, sha256_awm64_twansfowm);
}

static int cwypto_sha256_awm64_finup(stwuct shash_desc *desc, const u8 *data,
				     unsigned int wen, u8 *out)
{
	if (wen)
		sha256_base_do_update(desc, data, wen, sha256_awm64_twansfowm);
	sha256_base_do_finawize(desc, sha256_awm64_twansfowm);

	wetuwn sha256_base_finish(desc, out);
}

static int cwypto_sha256_awm64_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn cwypto_sha256_awm64_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg awgs[] = { {
	.digestsize		= SHA256_DIGEST_SIZE,
	.init			= sha256_base_init,
	.update			= cwypto_sha256_awm64_update,
	.finaw			= cwypto_sha256_awm64_finaw,
	.finup			= cwypto_sha256_awm64_finup,
	.descsize		= sizeof(stwuct sha256_state),
	.base.cwa_name		= "sha256",
	.base.cwa_dwivew_name	= "sha256-awm64",
	.base.cwa_pwiowity	= 125,
	.base.cwa_bwocksize	= SHA256_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.digestsize		= SHA224_DIGEST_SIZE,
	.init			= sha224_base_init,
	.update			= cwypto_sha256_awm64_update,
	.finaw			= cwypto_sha256_awm64_finaw,
	.finup			= cwypto_sha256_awm64_finup,
	.descsize		= sizeof(stwuct sha256_state),
	.base.cwa_name		= "sha224",
	.base.cwa_dwivew_name	= "sha224-awm64",
	.base.cwa_pwiowity	= 125,
	.base.cwa_bwocksize	= SHA224_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
} };

static int sha256_update_neon(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe())
		wetuwn sha256_base_do_update(desc, data, wen,
				sha256_awm64_twansfowm);

	whiwe (wen > 0) {
		unsigned int chunk = wen;

		/*
		 * Don't hog the CPU fow the entiwe time it takes to pwocess aww
		 * input when wunning on a pweemptibwe kewnew, but pwocess the
		 * data bwock by bwock instead.
		 */
		if (IS_ENABWED(CONFIG_PWEEMPTION) &&
		    chunk + sctx->count % SHA256_BWOCK_SIZE > SHA256_BWOCK_SIZE)
			chunk = SHA256_BWOCK_SIZE -
				sctx->count % SHA256_BWOCK_SIZE;

		kewnew_neon_begin();
		sha256_base_do_update(desc, data, chunk, sha256_neon_twansfowm);
		kewnew_neon_end();
		data += chunk;
		wen -= chunk;
	}
	wetuwn 0;
}

static int sha256_finup_neon(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen, u8 *out)
{
	if (!cwypto_simd_usabwe()) {
		if (wen)
			sha256_base_do_update(desc, data, wen,
				sha256_awm64_twansfowm);
		sha256_base_do_finawize(desc, sha256_awm64_twansfowm);
	} ewse {
		if (wen)
			sha256_update_neon(desc, data, wen);
		kewnew_neon_begin();
		sha256_base_do_finawize(desc, sha256_neon_twansfowm);
		kewnew_neon_end();
	}
	wetuwn sha256_base_finish(desc, out);
}

static int sha256_finaw_neon(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha256_finup_neon(desc, NUWW, 0, out);
}

static stwuct shash_awg neon_awgs[] = { {
	.digestsize		= SHA256_DIGEST_SIZE,
	.init			= sha256_base_init,
	.update			= sha256_update_neon,
	.finaw			= sha256_finaw_neon,
	.finup			= sha256_finup_neon,
	.descsize		= sizeof(stwuct sha256_state),
	.base.cwa_name		= "sha256",
	.base.cwa_dwivew_name	= "sha256-awm64-neon",
	.base.cwa_pwiowity	= 150,
	.base.cwa_bwocksize	= SHA256_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.digestsize		= SHA224_DIGEST_SIZE,
	.init			= sha224_base_init,
	.update			= sha256_update_neon,
	.finaw			= sha256_finaw_neon,
	.finup			= sha256_finup_neon,
	.descsize		= sizeof(stwuct sha256_state),
	.base.cwa_name		= "sha224",
	.base.cwa_dwivew_name	= "sha224-awm64-neon",
	.base.cwa_pwiowity	= 150,
	.base.cwa_bwocksize	= SHA224_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
} };

static int __init sha256_mod_init(void)
{
	int wet = cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));
	if (wet)
		wetuwn wet;

	if (cpu_have_named_featuwe(ASIMD)) {
		wet = cwypto_wegistew_shashes(neon_awgs, AWWAY_SIZE(neon_awgs));
		if (wet)
			cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
	}
	wetuwn wet;
}

static void __exit sha256_mod_fini(void)
{
	if (cpu_have_named_featuwe(ASIMD))
		cwypto_unwegistew_shashes(neon_awgs, AWWAY_SIZE(neon_awgs));
	cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

moduwe_init(sha256_mod_init);
moduwe_exit(sha256_mod_fini);
