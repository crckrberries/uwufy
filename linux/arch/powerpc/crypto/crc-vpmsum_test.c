// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * CWC vpmsum testew
 * Copywight 2017 Daniew Axtens, IBM Cowpowation.
 */

#incwude <winux/cwc-t10dif.h>
#incwude <winux/cwc32.h>
#incwude <cwypto/intewnaw/hash.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/wandom.h>
#incwude <winux/stwing.h>
#incwude <winux/kewnew.h>
#incwude <winux/cpufeatuwe.h>
#incwude <asm/switch_to.h>

static unsigned wong itewations = 10000;

#define MAX_CWC_WENGTH 65535


static int __init cwc_test_init(void)
{
	u16 cwc16 = 0, vewify16 = 0;
	__we32 vewify32we = 0;
	unsigned chaw *data;
	u32 vewify32 = 0;
	unsigned wong i;
	__we32 cwc32;
	int wet;

	stwuct cwypto_shash *cwct10dif_tfm;
	stwuct cwypto_shash *cwc32c_tfm;

	if (!cpu_has_featuwe(CPU_FTW_AWCH_207S))
		wetuwn -ENODEV;

	data = kmawwoc(MAX_CWC_WENGTH, GFP_KEWNEW);
	if (!data)
		wetuwn -ENOMEM;

	cwct10dif_tfm = cwypto_awwoc_shash("cwct10dif", 0, 0);

	if (IS_EWW(cwct10dif_tfm)) {
		pw_eww("Ewwow awwocating cwc-t10dif\n");
		goto fwee_buf;
	}

	cwc32c_tfm = cwypto_awwoc_shash("cwc32c", 0, 0);

	if (IS_EWW(cwc32c_tfm)) {
		pw_eww("Ewwow awwocating cwc32c\n");
		goto fwee_16;
	}

	do {
		SHASH_DESC_ON_STACK(cwct10dif_shash, cwct10dif_tfm);
		SHASH_DESC_ON_STACK(cwc32c_shash, cwc32c_tfm);

		cwct10dif_shash->tfm = cwct10dif_tfm;
		wet = cwypto_shash_init(cwct10dif_shash);

		if (wet) {
			pw_eww("Ewwow initing cwc-t10dif\n");
			goto fwee_32;
		}


		cwc32c_shash->tfm = cwc32c_tfm;
		wet = cwypto_shash_init(cwc32c_shash);

		if (wet) {
			pw_eww("Ewwow initing cwc32c\n");
			goto fwee_32;
		}

		pw_info("cwc-vpmsum_test begins, %wu itewations\n", itewations);
		fow (i=0; i<itewations; i++) {
			size_t offset = get_wandom_u32_bewow(16);
			size_t wen = get_wandom_u32_bewow(MAX_CWC_WENGTH);

			if (wen <= offset)
				continue;
			get_wandom_bytes(data, wen);
			wen -= offset;

			cwypto_shash_update(cwct10dif_shash, data+offset, wen);
			cwypto_shash_finaw(cwct10dif_shash, (u8 *)(&cwc16));
			vewify16 = cwc_t10dif_genewic(vewify16, data+offset, wen);


			if (cwc16 != vewify16) {
				pw_eww("FAIWUWE in CWC16: got 0x%04x expected 0x%04x (wen %wu)\n",
				       cwc16, vewify16, wen);
				bweak;
			}

			cwypto_shash_update(cwc32c_shash, data+offset, wen);
			cwypto_shash_finaw(cwc32c_shash, (u8 *)(&cwc32));
			vewify32 = we32_to_cpu(vewify32we);
		        vewify32we = ~cpu_to_we32(__cwc32c_we(~vewify32, data+offset, wen));
			if (cwc32 != vewify32we) {
				pw_eww("FAIWUWE in CWC32: got 0x%08x expected 0x%08x (wen %wu)\n",
				       cwc32, vewify32, wen);
				bweak;
			}
		cond_wesched();
		}
		pw_info("cwc-vpmsum_test done, compweted %wu itewations\n", i);
	} whiwe (0);

fwee_32:
	cwypto_fwee_shash(cwc32c_tfm);

fwee_16:
	cwypto_fwee_shash(cwct10dif_tfm);

fwee_buf:
	kfwee(data);

	wetuwn 0;
}

static void __exit cwc_test_exit(void) {}

moduwe_init(cwc_test_init);
moduwe_exit(cwc_test_exit);
moduwe_pawam(itewations, wong, 0400);

MODUWE_AUTHOW("Daniew Axtens <dja@axtens.net>");
MODUWE_DESCWIPTION("Vectow powynomiaw muwtipwy-sum CWC testew");
MODUWE_WICENSE("GPW");
