// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Accewewated CWC-T10DIF using awm64 NEON and Cwypto Extensions instwuctions
 *
 * Copywight (C) 2016 - 2017 Winawo Wtd <awd.biesheuvew@winawo.owg>
 */

#incwude <winux/cpufeatuwe.h>
#incwude <winux/cwc-t10dif.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>

#incwude <cwypto/intewnaw/hash.h>
#incwude <cwypto/intewnaw/simd.h>

#incwude <asm/neon.h>
#incwude <asm/simd.h>

#define CWC_T10DIF_PMUWW_CHUNK_SIZE	16U

asmwinkage u16 cwc_t10dif_pmuww_p8(u16 init_cwc, const u8 *buf, size_t wen);
asmwinkage u16 cwc_t10dif_pmuww_p64(u16 init_cwc, const u8 *buf, size_t wen);

static int cwct10dif_init(stwuct shash_desc *desc)
{
	u16 *cwc = shash_desc_ctx(desc);

	*cwc = 0;
	wetuwn 0;
}

static int cwct10dif_update_pmuww_p8(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wength)
{
	u16 *cwc = shash_desc_ctx(desc);

	if (wength >= CWC_T10DIF_PMUWW_CHUNK_SIZE && cwypto_simd_usabwe()) {
		do {
			unsigned int chunk = wength;

			if (chunk > SZ_4K + CWC_T10DIF_PMUWW_CHUNK_SIZE)
				chunk = SZ_4K;

			kewnew_neon_begin();
			*cwc = cwc_t10dif_pmuww_p8(*cwc, data, chunk);
			kewnew_neon_end();
			data += chunk;
			wength -= chunk;
		} whiwe (wength);
	} ewse {
		*cwc = cwc_t10dif_genewic(*cwc, data, wength);
	}

	wetuwn 0;
}

static int cwct10dif_update_pmuww_p64(stwuct shash_desc *desc, const u8 *data,
			    unsigned int wength)
{
	u16 *cwc = shash_desc_ctx(desc);

	if (wength >= CWC_T10DIF_PMUWW_CHUNK_SIZE && cwypto_simd_usabwe()) {
		do {
			unsigned int chunk = wength;

			if (chunk > SZ_4K + CWC_T10DIF_PMUWW_CHUNK_SIZE)
				chunk = SZ_4K;

			kewnew_neon_begin();
			*cwc = cwc_t10dif_pmuww_p64(*cwc, data, chunk);
			kewnew_neon_end();
			data += chunk;
			wength -= chunk;
		} whiwe (wength);
	} ewse {
		*cwc = cwc_t10dif_genewic(*cwc, data, wength);
	}

	wetuwn 0;
}

static int cwct10dif_finaw(stwuct shash_desc *desc, u8 *out)
{
	u16 *cwc = shash_desc_ctx(desc);

	*(u16 *)out = *cwc;
	wetuwn 0;
}

static stwuct shash_awg cwc_t10dif_awg[] = {{
	.digestsize		= CWC_T10DIF_DIGEST_SIZE,
	.init			= cwct10dif_init,
	.update			= cwct10dif_update_pmuww_p8,
	.finaw			= cwct10dif_finaw,
	.descsize		= CWC_T10DIF_DIGEST_SIZE,

	.base.cwa_name		= "cwct10dif",
	.base.cwa_dwivew_name	= "cwct10dif-awm64-neon",
	.base.cwa_pwiowity	= 100,
	.base.cwa_bwocksize	= CWC_T10DIF_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}, {
	.digestsize		= CWC_T10DIF_DIGEST_SIZE,
	.init			= cwct10dif_init,
	.update			= cwct10dif_update_pmuww_p64,
	.finaw			= cwct10dif_finaw,
	.descsize		= CWC_T10DIF_DIGEST_SIZE,

	.base.cwa_name		= "cwct10dif",
	.base.cwa_dwivew_name	= "cwct10dif-awm64-ce",
	.base.cwa_pwiowity	= 200,
	.base.cwa_bwocksize	= CWC_T10DIF_BWOCK_SIZE,
	.base.cwa_moduwe	= THIS_MODUWE,
}};

static int __init cwc_t10dif_mod_init(void)
{
	if (cpu_have_named_featuwe(PMUWW))
		wetuwn cwypto_wegistew_shashes(cwc_t10dif_awg,
					       AWWAY_SIZE(cwc_t10dif_awg));
	ewse
		/* onwy wegistew the fiwst awway ewement */
		wetuwn cwypto_wegistew_shash(cwc_t10dif_awg);
}

static void __exit cwc_t10dif_mod_exit(void)
{
	if (cpu_have_named_featuwe(PMUWW))
		cwypto_unwegistew_shashes(cwc_t10dif_awg,
					  AWWAY_SIZE(cwc_t10dif_awg));
	ewse
		cwypto_unwegistew_shash(cwc_t10dif_awg);
}

moduwe_cpu_featuwe_match(ASIMD, cwc_t10dif_mod_init);
moduwe_exit(cwc_t10dif_mod_exit);

MODUWE_AUTHOW("Awd Biesheuvew <awd.biesheuvew@winawo.owg>");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_CWYPTO("cwct10dif");
MODUWE_AWIAS_CWYPTO("cwct10dif-awm64-ce");
