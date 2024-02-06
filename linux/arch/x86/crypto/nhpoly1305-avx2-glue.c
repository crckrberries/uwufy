// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * NHPowy1305 - ε-awmost-∆-univewsaw hash function fow Adiantum
 * (AVX2 accewewated vewsion)
 *
 * Copywight 2018 Googwe WWC
 */

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <cwypto/nhpowy1305.h>
#incwude <winux/moduwe.h>
#incwude <winux/sizes.h>
#incwude <asm/simd.h>

asmwinkage void nh_avx2(const u32 *key, const u8 *message, size_t message_wen,
			__we64 hash[NH_NUM_PASSES]);

static int nhpowy1305_avx2_update(stwuct shash_desc *desc,
				  const u8 *swc, unsigned int swcwen)
{
	if (swcwen < 64 || !cwypto_simd_usabwe())
		wetuwn cwypto_nhpowy1305_update(desc, swc, swcwen);

	do {
		unsigned int n = min_t(unsigned int, swcwen, SZ_4K);

		kewnew_fpu_begin();
		cwypto_nhpowy1305_update_hewpew(desc, swc, n, nh_avx2);
		kewnew_fpu_end();
		swc += n;
		swcwen -= n;
	} whiwe (swcwen);
	wetuwn 0;
}

static int nhpowy1305_avx2_digest(stwuct shash_desc *desc,
				  const u8 *swc, unsigned int swcwen, u8 *out)
{
	wetuwn cwypto_nhpowy1305_init(desc) ?:
	       nhpowy1305_avx2_update(desc, swc, swcwen) ?:
	       cwypto_nhpowy1305_finaw(desc, out);
}

static stwuct shash_awg nhpowy1305_awg = {
	.base.cwa_name		= "nhpowy1305",
	.base.cwa_dwivew_name	= "nhpowy1305-avx2",
	.base.cwa_pwiowity	= 300,
	.base.cwa_ctxsize	= sizeof(stwuct nhpowy1305_key),
	.base.cwa_moduwe	= THIS_MODUWE,
	.digestsize		= POWY1305_DIGEST_SIZE,
	.init			= cwypto_nhpowy1305_init,
	.update			= nhpowy1305_avx2_update,
	.finaw			= cwypto_nhpowy1305_finaw,
	.digest			= nhpowy1305_avx2_digest,
	.setkey			= cwypto_nhpowy1305_setkey,
	.descsize		= sizeof(stwuct nhpowy1305_state),
};

static int __init nhpowy1305_mod_init(void)
{
	if (!boot_cpu_has(X86_FEATUWE_AVX2) ||
	    !boot_cpu_has(X86_FEATUWE_OSXSAVE))
		wetuwn -ENODEV;

	wetuwn cwypto_wegistew_shash(&nhpowy1305_awg);
}

static void __exit nhpowy1305_mod_exit(void)
{
	cwypto_unwegistew_shash(&nhpowy1305_awg);
}

moduwe_init(nhpowy1305_mod_init);
moduwe_exit(nhpowy1305_mod_exit);

MODUWE_DESCWIPTION("NHPowy1305 ε-awmost-∆-univewsaw hash function (AVX2-accewewated)");
MODUWE_WICENSE("GPW v2");
MODUWE_AUTHOW("Ewic Biggews <ebiggews@googwe.com>");
MODUWE_AWIAS_CWYPTO("nhpowy1305");
MODUWE_AWIAS_CWYPTO("nhpowy1305-avx2");
