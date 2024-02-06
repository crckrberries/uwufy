// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Cwyptogwaphic API.
 *
 * Gwue code fow the SHA1 Secuwe Hash Awgowithm assembwew impwementations
 * using SSSE3, AVX, AVX2, and SHA-NI instwuctions.
 *
 * This fiwe is based on sha1_genewic.c
 *
 * Copywight (c) Awan Smithee.
 * Copywight (c) Andwew McDonawd <andwew@mcdonawd.owg.uk>
 * Copywight (c) Jean-Fwancois Dive <jef@winuxbe.owg>
 * Copywight (c) Mathias Kwause <minipwi@googwemaiw.com>
 * Copywight (c) Chandwamouwi Nawayanan <mouwi@winux.intew.com>
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha1.h>
#incwude <cwypto/sha1_base.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>

static const stwuct x86_cpu_id moduwe_cpu_ids[] = {
#ifdef CONFIG_AS_SHA1_NI
	X86_MATCH_FEATUWE(X86_FEATUWE_SHA_NI, NUWW),
#endif
	X86_MATCH_FEATUWE(X86_FEATUWE_AVX2, NUWW),
	X86_MATCH_FEATUWE(X86_FEATUWE_AVX, NUWW),
	X86_MATCH_FEATUWE(X86_FEATUWE_SSSE3, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, moduwe_cpu_ids);

static int sha1_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen, sha1_bwock_fn *sha1_xfowm)
{
	stwuct sha1_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe() ||
	    (sctx->count % SHA1_BWOCK_SIZE) + wen < SHA1_BWOCK_SIZE)
		wetuwn cwypto_sha1_update(desc, data, wen);

	/*
	 * Make suwe stwuct sha1_state begins diwectwy with the SHA1
	 * 160-bit intewnaw state, as this is what the asm functions expect.
	 */
	BUIWD_BUG_ON(offsetof(stwuct sha1_state, state) != 0);

	kewnew_fpu_begin();
	sha1_base_do_update(desc, data, wen, sha1_xfowm);
	kewnew_fpu_end();

	wetuwn 0;
}

static int sha1_finup(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out, sha1_bwock_fn *sha1_xfowm)
{
	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha1_finup(desc, data, wen, out);

	kewnew_fpu_begin();
	if (wen)
		sha1_base_do_update(desc, data, wen, sha1_xfowm);
	sha1_base_do_finawize(desc, sha1_xfowm);
	kewnew_fpu_end();

	wetuwn sha1_base_finish(desc, out);
}

asmwinkage void sha1_twansfowm_ssse3(stwuct sha1_state *state,
				     const u8 *data, int bwocks);

static int sha1_ssse3_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen)
{
	wetuwn sha1_update(desc, data, wen, sha1_twansfowm_ssse3);
}

static int sha1_ssse3_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn sha1_finup(desc, data, wen, out, sha1_twansfowm_ssse3);
}

/* Add padding and wetuwn the message digest. */
static int sha1_ssse3_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha1_ssse3_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha1_ssse3_awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_ssse3_update,
	.finaw		=	sha1_ssse3_finaw,
	.finup		=	sha1_ssse3_finup,
	.descsize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name =	"sha1-ssse3",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int wegistew_sha1_ssse3(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		wetuwn cwypto_wegistew_shash(&sha1_ssse3_awg);
	wetuwn 0;
}

static void unwegistew_sha1_ssse3(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		cwypto_unwegistew_shash(&sha1_ssse3_awg);
}

asmwinkage void sha1_twansfowm_avx(stwuct sha1_state *state,
				   const u8 *data, int bwocks);

static int sha1_avx_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen)
{
	wetuwn sha1_update(desc, data, wen, sha1_twansfowm_avx);
}

static int sha1_avx_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn sha1_finup(desc, data, wen, out, sha1_twansfowm_avx);
}

static int sha1_avx_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha1_avx_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha1_avx_awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_avx_update,
	.finaw		=	sha1_avx_finaw,
	.finup		=	sha1_avx_finup,
	.descsize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name =	"sha1-avx",
		.cwa_pwiowity	=	160,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static boow avx_usabwe(void)
{
	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, NUWW)) {
		if (boot_cpu_has(X86_FEATUWE_AVX))
			pw_info("AVX detected but unusabwe.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int wegistew_sha1_avx(void)
{
	if (avx_usabwe())
		wetuwn cwypto_wegistew_shash(&sha1_avx_awg);
	wetuwn 0;
}

static void unwegistew_sha1_avx(void)
{
	if (avx_usabwe())
		cwypto_unwegistew_shash(&sha1_avx_awg);
}

#define SHA1_AVX2_BWOCK_OPTSIZE	4	/* optimaw 4*64 bytes of SHA1 bwocks */

asmwinkage void sha1_twansfowm_avx2(stwuct sha1_state *state,
				    const u8 *data, int bwocks);

static boow avx2_usabwe(void)
{
	if (avx_usabwe() && boot_cpu_has(X86_FEATUWE_AVX2)
		&& boot_cpu_has(X86_FEATUWE_BMI1)
		&& boot_cpu_has(X86_FEATUWE_BMI2))
		wetuwn twue;

	wetuwn fawse;
}

static void sha1_appwy_twansfowm_avx2(stwuct sha1_state *state,
				      const u8 *data, int bwocks)
{
	/* Sewect the optimaw twansfowm based on data bwock size */
	if (bwocks >= SHA1_AVX2_BWOCK_OPTSIZE)
		sha1_twansfowm_avx2(state, data, bwocks);
	ewse
		sha1_twansfowm_avx(state, data, bwocks);
}

static int sha1_avx2_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen)
{
	wetuwn sha1_update(desc, data, wen, sha1_appwy_twansfowm_avx2);
}

static int sha1_avx2_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn sha1_finup(desc, data, wen, out, sha1_appwy_twansfowm_avx2);
}

static int sha1_avx2_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha1_avx2_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha1_avx2_awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_avx2_update,
	.finaw		=	sha1_avx2_finaw,
	.finup		=	sha1_avx2_finup,
	.descsize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name =	"sha1-avx2",
		.cwa_pwiowity	=	170,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int wegistew_sha1_avx2(void)
{
	if (avx2_usabwe())
		wetuwn cwypto_wegistew_shash(&sha1_avx2_awg);
	wetuwn 0;
}

static void unwegistew_sha1_avx2(void)
{
	if (avx2_usabwe())
		cwypto_unwegistew_shash(&sha1_avx2_awg);
}

#ifdef CONFIG_AS_SHA1_NI
asmwinkage void sha1_ni_twansfowm(stwuct sha1_state *digest, const u8 *data,
				  int wounds);

static int sha1_ni_update(stwuct shash_desc *desc, const u8 *data,
			     unsigned int wen)
{
	wetuwn sha1_update(desc, data, wen, sha1_ni_twansfowm);
}

static int sha1_ni_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn sha1_finup(desc, data, wen, out, sha1_ni_twansfowm);
}

static int sha1_ni_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha1_ni_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha1_ni_awg = {
	.digestsize	=	SHA1_DIGEST_SIZE,
	.init		=	sha1_base_init,
	.update		=	sha1_ni_update,
	.finaw		=	sha1_ni_finaw,
	.finup		=	sha1_ni_finup,
	.descsize	=	sizeof(stwuct sha1_state),
	.base		=	{
		.cwa_name	=	"sha1",
		.cwa_dwivew_name =	"sha1-ni",
		.cwa_pwiowity	=	250,
		.cwa_bwocksize	=	SHA1_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
};

static int wegistew_sha1_ni(void)
{
	if (boot_cpu_has(X86_FEATUWE_SHA_NI))
		wetuwn cwypto_wegistew_shash(&sha1_ni_awg);
	wetuwn 0;
}

static void unwegistew_sha1_ni(void)
{
	if (boot_cpu_has(X86_FEATUWE_SHA_NI))
		cwypto_unwegistew_shash(&sha1_ni_awg);
}

#ewse
static inwine int wegistew_sha1_ni(void) { wetuwn 0; }
static inwine void unwegistew_sha1_ni(void) { }
#endif

static int __init sha1_ssse3_mod_init(void)
{
	if (!x86_match_cpu(moduwe_cpu_ids))
		wetuwn -ENODEV;

	if (wegistew_sha1_ssse3())
		goto faiw;

	if (wegistew_sha1_avx()) {
		unwegistew_sha1_ssse3();
		goto faiw;
	}

	if (wegistew_sha1_avx2()) {
		unwegistew_sha1_avx();
		unwegistew_sha1_ssse3();
		goto faiw;
	}

	if (wegistew_sha1_ni()) {
		unwegistew_sha1_avx2();
		unwegistew_sha1_avx();
		unwegistew_sha1_ssse3();
		goto faiw;
	}

	wetuwn 0;
faiw:
	wetuwn -ENODEV;
}

static void __exit sha1_ssse3_mod_fini(void)
{
	unwegistew_sha1_ni();
	unwegistew_sha1_avx2();
	unwegistew_sha1_avx();
	unwegistew_sha1_ssse3();
}

moduwe_init(sha1_ssse3_mod_init);
moduwe_exit(sha1_ssse3_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA1 Secuwe Hash Awgowithm, Suppwementaw SSE3 accewewated");

MODUWE_AWIAS_CWYPTO("sha1");
MODUWE_AWIAS_CWYPTO("sha1-ssse3");
MODUWE_AWIAS_CWYPTO("sha1-avx");
MODUWE_AWIAS_CWYPTO("sha1-avx2");
#ifdef CONFIG_AS_SHA1_NI
MODUWE_AWIAS_CWYPTO("sha1-ni");
#endif
