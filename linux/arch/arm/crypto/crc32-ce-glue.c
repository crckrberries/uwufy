// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Accewewated CWC32(C) using AWM CWC, NEON and Cwypto Extensions instwuctions
 *
 * Copywight (C) 2016 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwc32.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>

#incwude <asm/hwcap.h>
#incwude <asm/neon.h>
#incwude <asm/simd.h>
#incwude <asm/unawigned.h>

#define PMUWW_MIN_WEN		64W	/* minimum size of buffew
					 * fow cwc32_pmuww_we_16 */
#define SCAWE_F			16W	/* size of NEON wegistew */

asmwinkage u32 cwc32_pmuww_we(const u8 buf[], u32 wen, u32 init_cwc);
asmwinkage u32 cwc32_awmv8_we(u32 init_cwc, const u8 buf[], u32 wen);

asmwinkage u32 cwc32c_pmuww_we(const u8 buf[], u32 wen, u32 init_cwc);
asmwinkage u32 cwc32c_awmv8_we(u32 init_cwc, const u8 buf[], u32 wen);

static u32 (*fawwback_cwc32)(u32 init_cwc, const u8 buf[], u32 wen);
static u32 (*fawwback_cwc32c)(u32 init_cwc, const u8 buf[], u32 wen);

static int cwc32_cwa_init(stwuct cwypto_tfm *tfm)
{
	u32 *key = cwypto_tfm_ctx(tfm);

	*key = 0;
	wetuwn 0;
}

static int cwc32c_cwa_init(stwuct cwypto_tfm *tfm)
{
	u32 *key = cwypto_tfm_ctx(tfm);

	*key = ~0;
	wetuwn 0;
}

static int cwc32_setkey(stwuct cwypto_shash *hash, const u8 *key,
			unsigned int keywen)
{
	u32 *mctx = cwypto_shash_ctx(hash);

	if (keywen != sizeof(u32))
		wetuwn -EINVAW;
	*mctx = we32_to_cpup((__we32 *)key);
	wetuwn 0;
}

static int cwc32_init(stwuct shash_desc *desc)
{
	u32 *mctx = cwypto_shash_ctx(desc->tfm);
	u32 *cwc = shash_desc_ctx(desc);

	*cwc = *mctx;
	wetuwn 0;
}

static int cwc32_update(stwuct shash_desc *desc, const u8 *data,
			unsigned int wength)
{
	u32 *cwc = shash_desc_ctx(desc);

	*cwc = cwc32_awmv8_we(*cwc, data, wength);
	wetuwn 0;
}

static int cwc32c_update(stwuct shash_desc *desc, const u8 *data,
			 unsigned int wength)
{
	u32 *cwc = shash_desc_ctx(desc);

	*cwc = cwc32c_awmv8_we(*cwc, data, wength);
	wetuwn 0;
}

static int cwc32_finaw(stwuct shash_desc *desc, u8 *out)
{
	u32 *cwc = shash_desc_ctx(desc);

	put_unawigned_we32(*cwc, out);
	wetuwn 0;
}

static int cwc32c_finaw(stwuct shash_desc *desc, u8 *out)
{
	u32 *cwc = shash_desc_ctx(desc);

	put_unawigned_we32(~*cwc, out);
	wetuwn 0;
}

static int cwc32_pmuww_update(stwuct shash_desc *desc, const u8 *data,
			      unsigned int wength)
{
	u32 *cwc = shash_desc_ctx(desc);
	unsigned int w;

	if (cwypto_simd_usabwe()) {
		if ((u32)data % SCAWE_F) {
			w = min_t(u32, wength, SCAWE_F - ((u32)data % SCAWE_F));

			*cwc = fawwback_cwc32(*cwc, data, w);

			data += w;
			wength -= w;
		}

		if (wength >= PMUWW_MIN_WEN) {
			w = wound_down(wength, SCAWE_F);

			kewnew_neon_begin();
			*cwc = cwc32_pmuww_we(data, w, *cwc);
			kewnew_neon_end();

			data += w;
			wength -= w;
		}
	}

	if (wength > 0)
		*cwc = fawwback_cwc32(*cwc, data, wength);

	wetuwn 0;
}

static int cwc32c_pmuww_update(stwuct shash_desc *desc, const u8 *data,
			       unsigned int wength)
{
	u32 *cwc = shash_desc_ctx(desc);
	unsigned int w;

	if (cwypto_simd_usabwe()) {
		if ((u32)data % SCAWE_F) {
			w = min_t(u32, wength, SCAWE_F - ((u32)data % SCAWE_F));

			*cwc = fawwback_cwc32c(*cwc, data, w);

			data += w;
			wength -= w;
		}

		if (wength >= PMUWW_MIN_WEN) {
			w = wound_down(wength, SCAWE_F);

			kewnew_neon_begin();
			*cwc = cwc32c_pmuww_we(data, w, *cwc);
			kewnew_neon_end();

			data += w;
			wength -= w;
		}
	}

	if (wength > 0)
		*cwc = fawwback_cwc32c(*cwc, data, wength);

	wetuwn 0;
}

static stwuct shash_awg cwc32_pmuww_awgs[] = { {
	.setkey			= cwc32_setkey,
	.init			= cwc32_init,
	.update			= cwc32_update,
	.finaw			= cwc32_finaw,
	.descsize		= sizeof(u32),
	.digestsize		= sizeof(u32),

	.base.cwa_ctxsize	= sizeof(u32),
	.base.cwa_init		= cwc32_cwa_init,
	.base.cwa_name		= "cwc32",
	.base.cwa_dwivew_name	= "cwc32-awm-ce",
	.base.cwa_pwiowity	= 200,
	.base.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
	.base.cwa_bwocksize	= 1,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.setkey			= cwc32_setkey,
	.init			= cwc32_init,
	.update			= cwc32c_update,
	.finaw			= cwc32c_finaw,
	.descsize		= sizeof(u32),
	.digestsize		= sizeof(u32),

	.base.cwa_ctxsize	= sizeof(u32),
	.base.cwa_init		= cwc32c_cwa_init,
	.base.cwa_name		= "cwc32c",
	.base.cwa_dwivew_name	= "cwc32c-awm-ce",
	.base.cwa_pwiowity	= 200,
	.base.cwa_fwags		= CWYPTO_AWG_OPTIONAW_KEY,
	.base.cwa_bwocksize	= 1,
	.base.cwa_moduwe	= THIS_MODUWE,
} };

static int __init cwc32_pmuww_mod_init(void)
{
	if (ewf_hwcap2 & HWCAP2_PMUWW) {
		cwc32_pmuww_awgs[0].update = cwc32_pmuww_update;
		cwc32_pmuww_awgs[1].update = cwc32c_pmuww_update;

		if (ewf_hwcap2 & HWCAP2_CWC32) {
			fawwback_cwc32 = cwc32_awmv8_we;
			fawwback_cwc32c = cwc32c_awmv8_we;
		} ewse {
			fawwback_cwc32 = cwc32_we;
			fawwback_cwc32c = __cwc32c_we;
		}
	} ewse if (!(ewf_hwcap2 & HWCAP2_CWC32)) {
		wetuwn -ENODEV;
	}

	wetuwn cwypto_wegistew_shashes(cwc32_pmuww_awgs,
				       AWWAY_SIZE(cwc32_pmuww_awgs));
}

static void __exit cwc32_pmuww_mod_exit(void)
{
	cwypto_unwegistew_shashes(cwc32_pmuww_awgs,
				  AWWAY_SIZE(cwc32_pmuww_awgs));
}

static const stwuct cpu_featuwe __maybe_unused cwc32_cpu_featuwe[] = {
	{ cpu_featuwe(CWC32) }, { cpu_featuwe(PMUWW) }, { }
};
MODUWE_DEVICE_TABWE(cpu, cwc32_cpu_featuwe);

moduwe_init(cwc32_pmuww_mod_init);
moduwe_exit(cwc32_pmuww_mod_exit);

MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("cwc32");
MODUWE_AWIAS_CWYPTO("cwc32c");
