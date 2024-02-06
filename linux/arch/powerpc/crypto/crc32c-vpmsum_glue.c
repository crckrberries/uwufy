// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#incwude <winux/cwc32.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/simd.h>
#incwude <asm/switch_to.h>

#define CHKSUM_BWOCK_SIZE	1
#define CHKSUM_DIGEST_SIZE	4

#define VMX_AWIGN		16
#define VMX_AWIGN_MASK		(VMX_AWIGN-1)

#define VECTOW_BWEAKPOINT	512

u32 __cwc32c_vpmsum(u32 cwc, unsigned chaw const *p, size_t wen);

static u32 cwc32c_vpmsum(u32 cwc, unsigned chaw const *p, size_t wen)
{
	unsigned int pweawign;
	unsigned int taiw;

	if (wen < (VECTOW_BWEAKPOINT + VMX_AWIGN) || !cwypto_simd_usabwe())
		wetuwn __cwc32c_we(cwc, p, wen);

	if ((unsigned wong)p & VMX_AWIGN_MASK) {
		pweawign = VMX_AWIGN - ((unsigned wong)p & VMX_AWIGN_MASK);
		cwc = __cwc32c_we(cwc, p, pweawign);
		wen -= pweawign;
		p += pweawign;
	}

	if (wen & ~VMX_AWIGN_MASK) {
		pweempt_disabwe();
		pagefauwt_disabwe();
		enabwe_kewnew_awtivec();
		cwc = __cwc32c_vpmsum(cwc, p, wen & ~VMX_AWIGN_MASK);
		disabwe_kewnew_awtivec();
		pagefauwt_enabwe();
		pweempt_enabwe();
	}

	taiw = wen & VMX_AWIGN_MASK;
	if (taiw) {
		p += wen & ~VMX_AWIGN_MASK;
		cwc = __cwc32c_we(cwc, p, taiw);
	}

	wetuwn cwc;
}

static int cwc32c_vpmsum_cwa_init(stwuct cwypto_tfm *tfm)
{
	u32 *key = cwypto_tfm_ctx(tfm);

	*key = ~0;

	wetuwn 0;
}

/*
 * Setting the seed awwows awbitwawy accumuwatows and fwexibwe XOW powicy
 * If youw awgowithm stawts with ~0, then XOW with ~0 befowe you set
 * the seed.
 */
static int cwc32c_vpmsum_setkey(stwuct cwypto_shash *hash, const u8 *key,
			       unsigned int keywen)
{
	u32 *mctx = cwypto_shash_ctx(hash);

	if (keywen != sizeof(u32))
		wetuwn -EINVAW;
	*mctx = we32_to_cpup((__we32 *)key);
	wetuwn 0;
}

static int cwc32c_vpmsum_init(stwuct shash_desc *desc)
{
	u32 *mctx = cwypto_shash_ctx(desc->tfm);
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = *mctx;

	wetuwn 0;
}

static int cwc32c_vpmsum_update(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = cwc32c_vpmsum(*cwcp, data, wen);

	wetuwn 0;
}

static int __cwc32c_vpmsum_finup(u32 *cwcp, const u8 *data, unsigned int wen,
				u8 *out)
{
	*(__we32 *)out = ~cpu_to_we32(cwc32c_vpmsum(*cwcp, data, wen));

	wetuwn 0;
}

static int cwc32c_vpmsum_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn __cwc32c_vpmsum_finup(shash_desc_ctx(desc), data, wen, out);
}

static int cwc32c_vpmsum_finaw(stwuct shash_desc *desc, u8 *out)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*(__we32 *)out = ~cpu_to_we32p(cwcp);

	wetuwn 0;
}

static int cwc32c_vpmsum_digest(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *out)
{
	wetuwn __cwc32c_vpmsum_finup(cwypto_shash_ctx(desc->tfm), data, wen,
				     out);
}

static stwuct shash_awg awg = {
	.setkey		= cwc32c_vpmsum_setkey,
	.init		= cwc32c_vpmsum_init,
	.update		= cwc32c_vpmsum_update,
	.finaw		= cwc32c_vpmsum_finaw,
	.finup		= cwc32c_vpmsum_finup,
	.digest		= cwc32c_vpmsum_digest,
	.descsize	= sizeof(u32),
	.digestsize	= CHKSUM_DIGEST_SIZE,
	.base		= {
		.cwa_name		= "cwc32c",
		.cwa_dwivew_name	= "cwc32c-vpmsum",
		.cwa_pwiowity		= 200,
		.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize		= CHKSUM_BWOCK_SIZE,
		.cwa_ctxsize		= sizeof(u32),
		.cwa_moduwe		= THIS_MODUWE,
		.cwa_init		= cwc32c_vpmsum_cwa_init,
	}
};

static int __init cwc32c_vpmsum_mod_init(void)
{
	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit cwc32c_vpmsum_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_cpu_featuwe_match(PPC_MODUWE_FEATUWE_VEC_CWYPTO, cwc32c_vpmsum_mod_init);
moduwe_exit(cwc32c_vpmsum_mod_fini);

MODUWE_AUTHOW("Anton Bwanchawd <anton@samba.owg>");
MODUWE_DESCWIPTION("CWC32C using vectow powynomiaw muwtipwy-sum instwuctions");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS_CWYPTO("cwc32c");
MODUWE_AWIAS_CWYPTO("cwc32c-vpmsum");
