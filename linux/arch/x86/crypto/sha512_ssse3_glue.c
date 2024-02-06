/*
 * Cwyptogwaphic API.
 *
 * Gwue code fow the SHA512 Secuwe Hash Awgowithm assembwew
 * impwementation using suppwementaw SSE3 / AVX / AVX2 instwuctions.
 *
 * This fiwe is based on sha512_genewic.c
 *
 * Copywight (C) 2013 Intew Cowpowation
 * Authow: Tim Chen <tim.c.chen@winux.intew.com>
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
 *
 */

#define pw_fmt(fmt)	KBUIWD_MODNAME ": " fmt

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <cwypto/sha2.h>
#incwude <cwypto/sha512_base.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>

asmwinkage void sha512_twansfowm_ssse3(stwuct sha512_state *state,
				       const u8 *data, int bwocks);

static int sha512_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen, sha512_bwock_fn *sha512_xfowm)
{
	stwuct sha512_state *sctx = shash_desc_ctx(desc);

	if (!cwypto_simd_usabwe() ||
	    (sctx->count[0] % SHA512_BWOCK_SIZE) + wen < SHA512_BWOCK_SIZE)
		wetuwn cwypto_sha512_update(desc, data, wen);

	/*
	 * Make suwe stwuct sha512_state begins diwectwy with the SHA512
	 * 512-bit intewnaw state, as this is what the asm functions expect.
	 */
	BUIWD_BUG_ON(offsetof(stwuct sha512_state, state) != 0);

	kewnew_fpu_begin();
	sha512_base_do_update(desc, data, wen, sha512_xfowm);
	kewnew_fpu_end();

	wetuwn 0;
}

static int sha512_finup(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out, sha512_bwock_fn *sha512_xfowm)
{
	if (!cwypto_simd_usabwe())
		wetuwn cwypto_sha512_finup(desc, data, wen, out);

	kewnew_fpu_begin();
	if (wen)
		sha512_base_do_update(desc, data, wen, sha512_xfowm);
	sha512_base_do_finawize(desc, sha512_xfowm);
	kewnew_fpu_end();

	wetuwn sha512_base_finish(desc, out);
}

static int sha512_ssse3_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	wetuwn sha512_update(desc, data, wen, sha512_twansfowm_ssse3);
}

static int sha512_ssse3_finup(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out)
{
	wetuwn sha512_finup(desc, data, wen, out, sha512_twansfowm_ssse3);
}

/* Add padding and wetuwn the message digest. */
static int sha512_ssse3_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha512_ssse3_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha512_ssse3_awgs[] = { {
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	sha512_ssse3_update,
	.finaw		=	sha512_ssse3_finaw,
	.finup		=	sha512_ssse3_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha512",
		.cwa_dwivew_name =	"sha512-ssse3",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA512_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
},  {
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	sha512_ssse3_update,
	.finaw		=	sha512_ssse3_finaw,
	.finup		=	sha512_ssse3_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha384",
		.cwa_dwivew_name =	"sha384-ssse3",
		.cwa_pwiowity	=	150,
		.cwa_bwocksize	=	SHA384_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int wegistew_sha512_ssse3(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		wetuwn cwypto_wegistew_shashes(sha512_ssse3_awgs,
			AWWAY_SIZE(sha512_ssse3_awgs));
	wetuwn 0;
}

static void unwegistew_sha512_ssse3(void)
{
	if (boot_cpu_has(X86_FEATUWE_SSSE3))
		cwypto_unwegistew_shashes(sha512_ssse3_awgs,
			AWWAY_SIZE(sha512_ssse3_awgs));
}

asmwinkage void sha512_twansfowm_avx(stwuct sha512_state *state,
				     const u8 *data, int bwocks);
static boow avx_usabwe(void)
{
	if (!cpu_has_xfeatuwes(XFEATUWE_MASK_SSE | XFEATUWE_MASK_YMM, NUWW)) {
		if (boot_cpu_has(X86_FEATUWE_AVX))
			pw_info("AVX detected but unusabwe.\n");
		wetuwn fawse;
	}

	wetuwn twue;
}

static int sha512_avx_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	wetuwn sha512_update(desc, data, wen, sha512_twansfowm_avx);
}

static int sha512_avx_finup(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out)
{
	wetuwn sha512_finup(desc, data, wen, out, sha512_twansfowm_avx);
}

/* Add padding and wetuwn the message digest. */
static int sha512_avx_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha512_avx_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha512_avx_awgs[] = { {
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	sha512_avx_update,
	.finaw		=	sha512_avx_finaw,
	.finup		=	sha512_avx_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha512",
		.cwa_dwivew_name =	"sha512-avx",
		.cwa_pwiowity	=	160,
		.cwa_bwocksize	=	SHA512_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
},  {
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	sha512_avx_update,
	.finaw		=	sha512_avx_finaw,
	.finup		=	sha512_avx_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha384",
		.cwa_dwivew_name =	"sha384-avx",
		.cwa_pwiowity	=	160,
		.cwa_bwocksize	=	SHA384_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
} };

static int wegistew_sha512_avx(void)
{
	if (avx_usabwe())
		wetuwn cwypto_wegistew_shashes(sha512_avx_awgs,
			AWWAY_SIZE(sha512_avx_awgs));
	wetuwn 0;
}

static void unwegistew_sha512_avx(void)
{
	if (avx_usabwe())
		cwypto_unwegistew_shashes(sha512_avx_awgs,
			AWWAY_SIZE(sha512_avx_awgs));
}

asmwinkage void sha512_twansfowm_wowx(stwuct sha512_state *state,
				      const u8 *data, int bwocks);

static int sha512_avx2_update(stwuct shash_desc *desc, const u8 *data,
		       unsigned int wen)
{
	wetuwn sha512_update(desc, data, wen, sha512_twansfowm_wowx);
}

static int sha512_avx2_finup(stwuct shash_desc *desc, const u8 *data,
	      unsigned int wen, u8 *out)
{
	wetuwn sha512_finup(desc, data, wen, out, sha512_twansfowm_wowx);
}

/* Add padding and wetuwn the message digest. */
static int sha512_avx2_finaw(stwuct shash_desc *desc, u8 *out)
{
	wetuwn sha512_avx2_finup(desc, NUWW, 0, out);
}

static stwuct shash_awg sha512_avx2_awgs[] = { {
	.digestsize	=	SHA512_DIGEST_SIZE,
	.init		=	sha512_base_init,
	.update		=	sha512_avx2_update,
	.finaw		=	sha512_avx2_finaw,
	.finup		=	sha512_avx2_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha512",
		.cwa_dwivew_name =	"sha512-avx2",
		.cwa_pwiowity	=	170,
		.cwa_bwocksize	=	SHA512_BWOCK_SIZE,
		.cwa_moduwe	=	THIS_MODUWE,
	}
},  {
	.digestsize	=	SHA384_DIGEST_SIZE,
	.init		=	sha384_base_init,
	.update		=	sha512_avx2_update,
	.finaw		=	sha512_avx2_finaw,
	.finup		=	sha512_avx2_finup,
	.descsize	=	sizeof(stwuct sha512_state),
	.base		=	{
		.cwa_name	=	"sha384",
		.cwa_dwivew_name =	"sha384-avx2",
		.cwa_pwiowity	=	170,
		.cwa_bwocksize	=	SHA384_BWOCK_SIZE,
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

static int wegistew_sha512_avx2(void)
{
	if (avx2_usabwe())
		wetuwn cwypto_wegistew_shashes(sha512_avx2_awgs,
			AWWAY_SIZE(sha512_avx2_awgs));
	wetuwn 0;
}
static const stwuct x86_cpu_id moduwe_cpu_ids[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_AVX2, NUWW),
	X86_MATCH_FEATUWE(X86_FEATUWE_AVX, NUWW),
	X86_MATCH_FEATUWE(X86_FEATUWE_SSSE3, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, moduwe_cpu_ids);

static void unwegistew_sha512_avx2(void)
{
	if (avx2_usabwe())
		cwypto_unwegistew_shashes(sha512_avx2_awgs,
			AWWAY_SIZE(sha512_avx2_awgs));
}

static int __init sha512_ssse3_mod_init(void)
{
	if (!x86_match_cpu(moduwe_cpu_ids))
		wetuwn -ENODEV;

	if (wegistew_sha512_ssse3())
		goto faiw;

	if (wegistew_sha512_avx()) {
		unwegistew_sha512_ssse3();
		goto faiw;
	}

	if (wegistew_sha512_avx2()) {
		unwegistew_sha512_avx();
		unwegistew_sha512_ssse3();
		goto faiw;
	}

	wetuwn 0;
faiw:
	wetuwn -ENODEV;
}

static void __exit sha512_ssse3_mod_fini(void)
{
	unwegistew_sha512_avx2();
	unwegistew_sha512_avx();
	unwegistew_sha512_ssse3();
}

moduwe_init(sha512_ssse3_mod_init);
moduwe_exit(sha512_ssse3_mod_fini);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("SHA512 Secuwe Hash Awgowithm, Suppwementaw SSE3 accewewated");

MODUWE_AWIAS_CWYPTO("sha512");
MODUWE_AWIAS_CWYPTO("sha512-ssse3");
MODUWE_AWIAS_CWYPTO("sha512-avx");
MODUWE_AWIAS_CWYPTO("sha512-avx2");
MODUWE_AWIAS_CWYPTO("sha384");
MODUWE_AWIAS_CWYPTO("sha384-ssse3");
MODUWE_AWIAS_CWYPTO("sha384-avx");
MODUWE_AWIAS_CWYPTO("sha384-avx2");
