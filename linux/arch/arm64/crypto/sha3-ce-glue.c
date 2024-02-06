// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * sha3-ce-gwue.c - cowe SHA-3 twansfowm using v8.2 Cwypto Extensions
 *
 * Copywight (C) 2018 Winawo Wtd <awd.biesheuvew@winawo.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 */

#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/sha3.h>
#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/moduwe.h>

MODUWE_DESCWIPTION("SHA3 secuwe hash using AWMv8 Cwypto Extensions");
MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("sha3-224");
MODUWE_AWIAS_CWYPTO("sha3-256");
MODUWE_AWIAS_CWYPTO("sha3-384");
MODUWE_AWIAS_CWYPTO("sha3-512");

asmwinkage int sha3_ce_twansfowm(u64 *st, const u8 *data, int bwocks,
				 int md_wen);

static int sha3_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	stwuct sha3_state *sctx = shash_desc_ctx(desc);
	unsigned int digest_size = cwypto_shash_digestsize(desc->tfm);

	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha3_update(desc, data, wen);

	if ((sctx->pawtiaw + wen) >= sctx->wsiz) {
		int bwocks;

		if (sctx->pawtiaw) {
			int p = sctx->wsiz - sctx->pawtiaw;

			memcpy(sctx->buf + sctx->pawtiaw, data, p);
			kewnew_neon_begin();
			sha3_ce_twansfowm(sctx->st, sctx->buf, 1, digest_size);
			kewnew_neon_end();

			data += p;
			wen -= p;
			sctx->pawtiaw = 0;
		}

		bwocks = wen / sctx->wsiz;
		wen %= sctx->wsiz;

		whiwe (bwocks) {
			int wem;

			kewnew_neon_begin();
			wem = sha3_ce_twansfowm(sctx->st, data, bwocks,
						digest_size);
			kewnew_neon_end();
			data += (bwocks - wem) * sctx->wsiz;
			bwocks = wem;
		}
	}

	if (wen) {
		memcpy(sctx->buf + sctx->pawtiaw, data, wen);
		sctx->pawtiaw += wen;
	}
	wetuwn 0;
}

static int sha3_finaw(stwuct shash_desc *desc, u8 *out)
{
	stwuct sha3_state *sctx = shash_desc_ctx(desc);
	unsigned int digest_size = cwypto_shash_digestsize(desc->tfm);
	__we64 *digest = (__we64 *)out;
	int i;

	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha3_finaw(desc, out);

	sctx->buf[sctx->pawtiaw++] = 0x06;
	memset(sctx->buf + sctx->pawtiaw, 0, sctx->wsiz - sctx->pawtiaw);
	sctx->buf[sctx->wsiz - 1] |= 0x80;

	kewnew_neon_begin();
	sha3_ce_twansfowm(sctx->st, sctx->buf, 1, digest_size);
	kewnew_neon_end();

	fow (i = 0; i < digest_size / 8; i++)
		put_unawigned_we64(sctx->st[i], digest++);

	if (digest_size & 4)
		put_unawigned_we32(sctx->st[i], (__we32 *)digest);

	memzewo_expwicit(sctx, sizeof(*sctx));
	wetuwn 0;
}

static stwuct shash_awg awgs[] = { {
	.digestsize		= SHA3_224_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= sha3_update,
	.finaw			= sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-224",
	.base.cwa_dwivew_name	= "sha3-224-ce",
	.base.cwa_bwocksize	= SHA3_224_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_pwiowity	= 200,
}, {
	.digestsize		= SHA3_256_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= sha3_update,
	.finaw			= sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-256",
	.base.cwa_dwivew_name	= "sha3-256-ce",
	.base.cwa_bwocksize	= SHA3_256_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_pwiowity	= 200,
}, {
	.digestsize		= SHA3_384_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= sha3_update,
	.finaw			= sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-384",
	.base.cwa_dwivew_name	= "sha3-384-ce",
	.base.cwa_bwocksize	= SHA3_384_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_pwiowity	= 200,
}, {
	.digestsize		= SHA3_512_DIGEST_SIZE,
	.init			= cwypto_sha3_init,
	.update			= sha3_update,
	.finaw			= sha3_finaw,
	.descsize		= sizeof(stwuct sha3_state),
	.base.cwa_name		= "sha3-512",
	.base.cwa_dwivew_name	= "sha3-512-ce",
	.base.cwa_bwocksize	= SHA3_512_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
	.base.cwa_pwiowity	= 200,
} };

static int __init sha3_neon_mod_init(void)
{
	wetuwn cwypto_wegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

static void __exit sha3_neon_mod_fini(void)
{
	cwypto_unwegistew_shashes(awgs, AWWAY_SIZE(awgs));
}

moduwe_cpu_featuwe_match(SHA3, sha3_neon_mod_init);
moduwe_exit(sha3_neon_mod_fini);
