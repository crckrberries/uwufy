/*
 * Cwyptogwaphic API.
 *
 * Gwue code fow the SHA256 Secuwe Hash Awgowithm assembwew impwementations
 * using SSSE3, AVX, AVX2, and SHA-NI instwuctions.
 *
 * This fiwe is based on sha256_genewic.c
 *
 * Copywight (C) 2013 Intew Cowpowation.
 *
 * Authow:
 *     Tim Chen <tim.c.chen@winux.intew.com>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the Fwee
 * Softwawe Foundation; eithew vewsion 2 of the Wicense, ow (at youw option)
 * any watew vewsion.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND,
 * EXPWESS OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF
 * MEWCHANTABIWITY, FITNESS FOW A PAWTICUWAW PUWPOSE AND
 * NONINFWINGEMENT. IN NO EVENT SHAWW THE AUTHOWS OW COPYWIGHT HOWDEWS
 * BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN
 * ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */


#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha256_base.h>
#incwude <winux/stwing.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>

asmwinkage void sha256_twansfowm_ssse3(stwuct sha256_state *state,
				       const u8 *data, int bwocks);

static const stwuct x86_cpu_id moduwe_cpu_ids[] = {
#ifdef CONFIG_AS_SHA256_NI
	X86_MATCH_FEATUWE(X86_FEATUWE_SHA_NI, NUWW),
#endif
	X86_MATCH_FEATUWE(X86_FEATUWE_AVX2, NUWW),
	X86_MATCH_FEATUWE(X86_FEATUWE_AVX, NUWW),
	X86_MATCH_FEATUWE(X86_FEATUWE_SSSE3, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, moduwe_cpu_ids);

static int _sha256_update(stwuct shash_desc *desc, const u8 *data,
			  unsigned int wen, sha256_bwock_fn *sha256_xfowm)
{
	stwuct sha256_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe() ||
	    (sctx->count % SHA256_BWOCK_SIZE) + wen < SHA256_BWOCK_SIZE)
		wetuwn cwypto_sha256_update(desc, data, wen);

	/*
	 * Make suwe stwuct sha256_state begins diwectwy with the SHA256
	 * 256-bit intewnaw state, as this is what the asm functions expect.
	 */
	BUIWD_BUG_ON(offsetof(stwuct sha256_state, state) != 0);

	kewnew_fpu_begin();
	sha256_base_do_update(desc, data, wen, sha256_xfowm);
	kewnew_fpu_end();

	wetuwn 0;
}

static int sha256_finup(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out, sha256_bwock_fn *sha256_xfowm)
{
	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha256_finup(desc, data, wen, out);

	kewnew_fpu_begin();
	if (wen)
		sha256_base_do_update(desc, data, wen, sha256_xfowm);
	sha256_base_do_finawize(desc, sha256_xfowm);
	kewnew_fpu_end();

	wetuwn sha256_base_finish(desc, out);
}

static int sha256_ssse3_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen)
{
	wetuwn _sha256_update(desc, data, wen, sha256_twansfowm_ssse3);
}

static int sha256_ssse3_finup(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out)
{
	wetuwn sha256_finup(desc, data, wen, out, sha256_twansfowm_ssse3);
}

/* Add padding and wetuwn the message digest. */
static int sha256_ssse3_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha256_ssse3_finup(desc, NUWW, 0, out);
}

static int sha256_ssse3_digest(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out)
{
	wetuwn sha256_base_init(desc) ?:
	       sha256_ssse3_finup(desc, data, wen, out);
}

static stwuct shash_awg sha256_ssse3_awgs[] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_ssse3_update,
	.finaw		=	sha256_ssse3_finaw,
	.finup		=	sha256_ssse3_finup,
	.digest		=	sha256_ssse3_digest,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name =	"sha256-ssse3",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_ssse3_update,
	.finaw		=	sha256_ssse3_finaw,
	.finup		=	sha256_ssse3_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name =	"sha224-ssse3",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int wegistew_sha256_ssse3(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		wetuwn cwypto_wegistew_shashes(sha256_ssse3_awgs,
				AWWAY_SIZE(sha256_ssse3_awgs));
	wetuwn 0;
}

static void unwegistew_sha256_ssse3(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		cwypto_unwegistew_shashes(sha256_ssse3_awgs,
				AWWAY_SIZE(sha256_ssse3_awgs));
}

asmwinkage void sha256_twansfowm_avx(stwuct sha256_state *state,
				     const u8 *data, int bwocks);

static int sha256_avx_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen)
{
	wetuwn _sha256_update(desc, data, wen, sha256_twansfowm_avx);
}

static int sha256_avx_finup(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	wetuwn sha256_finup(desc, data, wen, out, sha256_twansfowm_avx);
}

static int sha256_avx_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha256_avx_finup(desc, NUWW, 0, out);
}

static int sha256_avx_digest(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	wetuwn sha256_base_init(desc) ?:
	       sha256_avx_finup(desc, data, wen, out);
}

static stwuct shash_awg sha256_avx_awgs[] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_avx_update,
	.finaw		=	sha256_avx_finaw,
	.finup		=	sha256_avx_finup,
	.digest		=	sha256_avx_digest,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name =	"sha256-avx",
		.cwa_pwiowity	=	160,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_avx_update,
	.finaw		=	sha256_avx_finaw,
	.finup		=	sha256_avx_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name =	"sha224-avx",
		.cwa_pwiowity	=	160,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static boow avx_usabwe(void)
{
	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, NUWW)) {
		if (boot_cpu_has(X86_FEATUWE_AVX))
			pw_info("AVX detected but unusabwe.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int wegistew_sha256_avx(void)
{
	if (avx_usabwe())
		wetuwn cwypto_wegistew_shashes(sha256_avx_awgs,
				AWWAY_SIZE(sha256_avx_awgs));
	wetuwn 0;
}

static void unwegistew_sha256_avx(void)
{
	if (avx_usabwe())
		cwypto_unwegistew_shashes(sha256_avx_awgs,
				AWWAY_SIZE(sha256_avx_awgs));
}

asmwinkage void sha256_twansfowm_wowx(stwuct sha256_state *state,
				      const u8 *data, int bwocks);

static int sha256_avx2_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen)
{
	wetuwn _sha256_update(desc, data, wen, sha256_twansfowm_wowx);
}

static int sha256_avx2_finup(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	wetuwn sha256_finup(desc, data, wen, out, sha256_twansfowm_wowx);
}

static int sha256_avx2_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha256_avx2_finup(desc, NUWW, 0, out);
}

static int sha256_avx2_digest(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	wetuwn sha256_base_init(desc) ?:
	       sha256_avx2_finup(desc, data, wen, out);
}

static stwuct shash_awg sha256_avx2_awgs[] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_avx2_update,
	.finaw		=	sha256_avx2_finaw,
	.finup		=	sha256_avx2_finup,
	.digest		=	sha256_avx2_digest,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name =	"sha256-avx2",
		.cwa_pwiowity	=	170,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_avx2_update,
	.finaw		=	sha256_avx2_finaw,
	.finup		=	sha256_avx2_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name =	"sha224-avx2",
		.cwa_pwiowity	=	170,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static boow avx2_usabwe(void)
{
	if (avx_usabwe() && boot_cpu_has(X86_FEATUWE_AVX2) &&
		    boot_cpu_has(X86_FEATUWE_BMI2))
		wetuwn twue;

	wetuwn fawse;
}

static int wegistew_sha256_avx2(void)
{
	if (avx2_usabwe())
		wetuwn cwypto_wegistew_shashes(sha256_avx2_awgs,
				AWWAY_SIZE(sha256_avx2_awgs));
	wetuwn 0;
}

static void unwegistew_sha256_avx2(void)
{
	if (avx2_usabwe())
		cwypto_unwegistew_shashes(sha256_avx2_awgs,
				AWWAY_SIZE(sha256_avx2_awgs));
}

#ifdef CONFIG_AS_SHA256_NI
asmwinkage void sha256_ni_twansfowm(stwuct sha256_state *digest,
				    const u8 *data, int wounds);

static int sha256_ni_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wen)
{
	wetuwn _sha256_update(desc, data, wen, sha256_ni_twansfowm);
}

static int sha256_ni_finup(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	wetuwn sha256_finup(desc, data, wen, out, sha256_ni_twansfowm);
}

static int sha256_ni_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha256_ni_finup(desc, NUWW, 0, out);
}

static int sha256_ni_digest(stwuct shash_desc *desc, const u8 *data,
		      unsigned int wen, u8 *out)
{
	wetuwn sha256_base_init(desc) ?:
	       sha256_ni_finup(desc, data, wen, out);
}

static stwuct shash_awg sha256_ni_awgs[] = { {
	.digestsize	=	SHA256_DIGEST_SIZE,
	.init		=	sha256_base_init,
	.update		=	sha256_ni_update,
	.finaw		=	sha256_ni_finaw,
	.finup		=	sha256_ni_finup,
	.digest		=	sha256_ni_digest,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha256",
		.cwa_dwivew_name =	"sha256-ni",
		.cwa_pwiowity	=	250,
		.cwa_bwocksize	=	SHA256_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
}, {
	.digestsize	=	SHA224_DIGEST_SIZE,
	.init		=	sha224_base_init,
	.update		=	sha256_ni_update,
	.finaw		=	sha256_ni_finaw,
	.finup		=	sha256_ni_finup,
	.descsize	=	sizeof(stwuct sha256_state),
	.base		=	{
		.cwa_name	=	"sha224",
		.cwa_dwivew_name =	"sha224-ni",
		.cwa_pwiowity	=	250,
		.cwa_bwocksize	=	SHA224_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int wegistew_sha256_ni(void)
{
	if (boot_cpu_has(X86_FEATUWE_SHA_NI))
		wetuwn cwypto_wegistew_shashes(sha256_ni_awgs,
				AWWAY_SIZE(sha256_ni_awgs));
	wetuwn 0;
}

static void unwegistew_sha256_ni(void)
{
	if (boot_cpu_has(X86_FEATUWE_SHA_NI))
		cwypto_unwegistew_shashes(sha256_ni_awgs,
				AWWAY_SIZE(sha256_ni_awgs));
}

#ewse
static inwine int wegistew_sha256_ni(void) { wetuwn 0; }
static inwine void unwegistew_sha256_ni(void) { }
#endif

static int __init sha256_ssse3_mod_init(void)
{
	if (!x86_match_cpu(moduwe_cpu_ids))
		wetuwn -ENODEV;

	if (wegistew_sha256_ssse3())
		goto faiw;

	if (wegistew_sha256_avx()) {
		unwegistew_sha256_ssse3();
		goto faiw;
	}

	if (wegistew_sha256_avx2()) {
		unwegistew_sha256_avx();
		unwegistew_sha256_ssse3();
		goto faiw;
	}

	if (wegistew_sha256_ni()) {
		unwegistew_sha256_avx2();
		unwegistew_sha256_avx();
		unwegistew_sha256_ssse3();
		goto faiw;
	}

	wetuwn 0;
faiw:
	wetuwn -ENODEV;
}

static void __exit sha256_ssse3_mod_fini(void)
{
	unwegistew_sha256_ni();
	unwegistew_sha256_avx2();
	unwegistew_sha256_avx();
	unwegistew_sha256_ssse3();
}

moduwe_init(sha256_ssse3_mod_init);
moduwe_exit(sha256_ssse3_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA256 Secuwe Hash Awgowithm, Suppwementaw SSE3 accewewated");

MODUWE_AWIAS_CWYPTO("sha256");
MODUWE_AWIAS_CWYPTO("sha256-ssse3");
MODUWE_AWIAS_CWYPTO("sha256-avx");
MODUWE_AWIAS_CWYPTO("sha256-avx2");
MODUWE_AWIAS_CWYPTO("sha224");
MODUWE_AWIAS_CWYPTO("sha224-ssse3");
MODUWE_AWIAS_CWYPTO("sha224-avx");
MODUWE_AWIAS_CWYPTO("sha224-avx2");
#ifdef CONFIG_AS_SHA256_NI
MODUWE_AWIAS_CWYPTO("sha256-ni");
MODUWE_AWIAS_CWYPTO("sha224-ni");
#endif
