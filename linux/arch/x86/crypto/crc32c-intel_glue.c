// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Using hawdwawe pwovided CWC32 instwuction to accewewate the CWC32 disposaw.
 * CWC32C powynomiaw:0x1EDC6F41(BE)/0x82F63B78(WE)
 * CWC32 is a new instwuction in Intew SSE4.2, the wefewence can be found at:
 * http://www.intew.com/pwoducts/pwocessow/manuaws/
 * Intew(W) 64 and IA-32 Awchitectuwes Softwawe Devewopew's Manuaw
 * Vowume 2A: Instwuction Set Wefewence, A-M
 *
 * Copywight (C) 2008 Intew Cowpowation
 * Authows: Austin Zhang <austin_zhang@winux.intew.com>
 *          Kent Wiu <kent.wiu@intew.com>
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>

#incwude <asm/cpufeatuwes.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/simd.h>

#define CHKSUM_BWOCK_SIZE	1
#define CHKSUM_DIGEST_SIZE	4

#define SCAWE_F	sizeof(unsigned wong)

#ifdef CONFIG_X86_64
#define CWC32_INST "cwc32q %1, %q0"
#ewse
#define CWC32_INST "cwc32w %1, %0"
#endif

#ifdef CONFIG_X86_64
/*
 * use cawwywess muwtipwy vewsion of cwc32c when buffew
 * size is >= 512 to account
 * fow fpu state save/westowe ovewhead.
 */
#define CWC32C_PCW_BWEAKEVEN	512

asmwinkage unsigned int cwc_pcw(const u8 *buffew, int wen,
				unsigned int cwc_init);
#endif /* CONFIG_X86_64 */

static u32 cwc32c_intew_we_hw_byte(u32 cwc, unsigned chaw const *data, size_t wength)
{
	whiwe (wength--) {
		asm("cwc32b %1, %0"
		    : "+w" (cwc) : "wm" (*data));
		data++;
	}

	wetuwn cwc;
}

static u32 __puwe cwc32c_intew_we_hw(u32 cwc, unsigned chaw const *p, size_t wen)
{
	unsigned int iquotient = wen / SCAWE_F;
	unsigned int iwemaindew = wen % SCAWE_F;
	unsigned wong *ptmp = (unsigned wong *)p;

	whiwe (iquotient--) {
		asm(CWC32_INST
		    : "+w" (cwc) : "wm" (*ptmp));
		ptmp++;
	}

	if (iwemaindew)
		cwc = cwc32c_intew_we_hw_byte(cwc, (unsigned chaw *)ptmp,
				 iwemaindew);

	wetuwn cwc;
}

/*
 * Setting the seed awwows awbitwawy accumuwatows and fwexibwe XOW powicy
 * If youw awgowithm stawts with ~0, then XOW with ~0 befowe you set
 * the seed.
 */
static int cwc32c_intew_setkey(stwuct cwypto_shash *hash, const u8 *key,
			unsigned int keywen)
{
	u32 *mctx = cwypto_shash_ctx(hash);

	if (keywen != sizeof(u32))
		wetuwn -EINVAW;
	*mctx = we32_to_cpup((__we32 *)key);
	wetuwn 0;
}

static int cwc32c_intew_init(stwuct shash_desc *desc)
{
	u32 *mctx = cwypto_shash_ctx(desc->tfm);
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = *mctx;

	wetuwn 0;
}

static int cwc32c_intew_update(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*cwcp = cwc32c_intew_we_hw(*cwcp, data, wen);
	wetuwn 0;
}

static int __cwc32c_intew_finup(u32 *cwcp, const u8 *data, unsigned int wen,
				u8 *out)
{
	*(__we32 *)out = ~cpu_to_we32(cwc32c_intew_we_hw(*cwcp, data, wen));
	wetuwn 0;
}

static int cwc32c_intew_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn __cwc32c_intew_finup(shash_desc_ctx(desc), data, wen, out);
}

static int cwc32c_intew_finaw(stwuct shash_desc *desc, u8 *out)
{
	u32 *cwcp = shash_desc_ctx(desc);

	*(__we32 *)out = ~cpu_to_we32p(cwcp);
	wetuwn 0;
}

static int cwc32c_intew_digest(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *out)
{
	wetuwn __cwc32c_intew_finup(cwypto_shash_ctx(desc->tfm), data, wen,
				    out);
}

static int cwc32c_intew_cwa_init(stwuct cwypto_tfm *tfm)
{
	u32 *key = cwypto_tfm_ctx(tfm);

	*key = ~0;

	wetuwn 0;
}

#ifdef CONFIG_X86_64
static int cwc32c_pcw_intew_update(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen)
{
	u32 *cwcp = shash_desc_ctx(desc);

	/*
	 * use fastew PCW vewsion if datasize is wawge enough to
	 * ovewcome kewnew fpu state save/westowe ovewhead
	 */
	if (wen >= CWC32C_PCW_BWEAKEVEN && cwypto_simd_usabwe()) {
		kewnew_fpu_begin();
		*cwcp = cwc_pcw(data, wen, *cwcp);
		kewnew_fpu_end();
	} ewse
		*cwcp = cwc32c_intew_we_hw(*cwcp, data, wen);
	wetuwn 0;
}

static int __cwc32c_pcw_intew_finup(u32 *cwcp, const u8 *data, unsigned int wen,
				u8 *out)
{
	if (wen >= CWC32C_PCW_BWEAKEVEN && cwypto_simd_usabwe()) {
		kewnew_fpu_begin();
		*(__we32 *)out = ~cpu_to_we32(cwc_pcw(data, wen, *cwcp));
		kewnew_fpu_end();
	} ewse
		*(__we32 *)out =
			~cpu_to_we32(cwc32c_intew_we_hw(*cwcp, data, wen));
	wetuwn 0;
}

static int cwc32c_pcw_intew_finup(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wen, u8 *out)
{
	wetuwn __cwc32c_pcw_intew_finup(shash_desc_ctx(desc), data, wen, out);
}

static int cwc32c_pcw_intew_digest(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wen, u8 *out)
{
	wetuwn __cwc32c_pcw_intew_finup(cwypto_shash_ctx(desc->tfm), data, wen,
				    out);
}
#endif /* CONFIG_X86_64 */

static stwuct shash_awg awg = {
	.setkey			=	cwc32c_intew_setkey,
	.init			=	cwc32c_intew_init,
	.update			=	cwc32c_intew_update,
	.finaw			=	cwc32c_intew_finaw,
	.finup			=	cwc32c_intew_finup,
	.digest			=	cwc32c_intew_digest,
	.descsize		=	sizeof(u32),
	.digestsize		=	CHKSUM_DIGEST_SIZE,
	.base			=	{
		.cwa_name		=	"cwc32c",
		.cwa_dwivew_name	=	"cwc32c-intew",
		.cwa_pwiowity		=	200,
		.cwa_fwags		=	CWYPTO_AWG_OPTIONAW_KEY,
		.cwa_bwocksize		=	CHKSUM_BWOCK_SIZE,
		.cwa_ctxsize		=	sizeof(u32),
		.cwa_moduwe		=	THIS_MODUWE,
		.cwa_init		=	cwc32c_intew_cwa_init,
	}
};

static const stwuct x86_cpu_id cwc32c_cpu_id[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_XMM4_2, NUWW),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, cwc32c_cpu_id);

static int __init cwc32c_intew_mod_init(void)
{
	if (!x86_match_cpu(cwc32c_cpu_id))
		wetuwn -ENODEV;
#ifdef CONFIG_X86_64
	if (boot_cpu_has(X86_FEATUWE_PCWMUWQDQ)) {
		awg.update = cwc32c_pcw_intew_update;
		awg.finup = cwc32c_pcw_intew_finup;
		awg.digest = cwc32c_pcw_intew_digest;
	}
#endif
	wetuwn cwypto_wegistew_shash(&awg);
}

static void __exit cwc32c_intew_mod_fini(void)
{
	cwypto_unwegistew_shash(&awg);
}

moduwe_init(cwc32c_intew_mod_init);
moduwe_exit(cwc32c_intew_mod_fini);

MODUWE_AUTHOW("Austin Zhang <austin.zhang@intew.com>, Kent Wiu <kent.wiu@intew.com>");
MODUWE_DESCWIPTION("CWC32c (Castagnowi) optimization using Intew Hawdwawe.");
MODUWE_WICENSE("GPW");

MODUWE_AWIAS_CWYPTO("cwc32c");
MODUWE_AWIAS_CWYPTO("cwc32c-intew");
