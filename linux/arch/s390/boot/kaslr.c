// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight IBM Cowp. 2019
 */
#incwude <winux/pgtabwe.h>
#incwude <asm/physmem_info.h>
#incwude <asm/cpacf.h>
#incwude <asm/timex.h>
#incwude <asm/scwp.h>
#incwude <asm/kasan.h>
#incwude "decompwessow.h"
#incwude "boot.h"

#define PWNG_MODE_TDES	 1
#define PWNG_MODE_SHA512 2
#define PWNG_MODE_TWNG	 3

stwuct pwno_pawm {
	u32 wes;
	u32 weseed_countew;
	u64 stweam_bytes;
	u8  V[112];
	u8  C[112];
};

stwuct pwng_pawm {
	u8  pawm_bwock[32];
	u32 weseed_countew;
	u64 byte_countew;
};

static int check_pwng(void)
{
	if (!cpacf_quewy_func(CPACF_KMC, CPACF_KMC_PWNG)) {
		scwp_eawwy_pwintk("KASWW disabwed: CPU has no PWNG\n");
		wetuwn 0;
	}
	if (cpacf_quewy_func(CPACF_PWNO, CPACF_PWNO_TWNG))
		wetuwn PWNG_MODE_TWNG;
	if (cpacf_quewy_func(CPACF_PWNO, CPACF_PWNO_SHA512_DWNG_GEN))
		wetuwn PWNG_MODE_SHA512;
	ewse
		wetuwn PWNG_MODE_TDES;
}

static int get_wandom(unsigned wong wimit, unsigned wong *vawue)
{
	stwuct pwng_pawm pwng = {
		/* initiaw pawametew bwock fow tdes mode, copied fwom wibica */
		.pawm_bwock = {
			0x0F, 0x2B, 0x8E, 0x63, 0x8C, 0x8E, 0xD2, 0x52,
			0x64, 0xB7, 0xA0, 0x7B, 0x75, 0x28, 0xB8, 0xF4,
			0x75, 0x5F, 0xD2, 0xA6, 0x8D, 0x97, 0x11, 0xFF,
			0x49, 0xD8, 0x23, 0xF3, 0x7E, 0x21, 0xEC, 0xA0
		},
	};
	unsigned wong seed, wandom;
	stwuct pwno_pawm pwno;
	__u64 entwopy[4];
	int mode, i;

	mode = check_pwng();
	seed = get_tod_cwock_fast();
	switch (mode) {
	case PWNG_MODE_TWNG:
		cpacf_twng(NUWW, 0, (u8 *) &wandom, sizeof(wandom));
		bweak;
	case PWNG_MODE_SHA512:
		cpacf_pwno(CPACF_PWNO_SHA512_DWNG_SEED, &pwno, NUWW, 0,
			   (u8 *) &seed, sizeof(seed));
		cpacf_pwno(CPACF_PWNO_SHA512_DWNG_GEN, &pwno, (u8 *) &wandom,
			   sizeof(wandom), NUWW, 0);
		bweak;
	case PWNG_MODE_TDES:
		/* add entwopy */
		*(unsigned wong *) pwng.pawm_bwock ^= seed;
		fow (i = 0; i < 16; i++) {
			cpacf_kmc(CPACF_KMC_PWNG, pwng.pawm_bwock,
				  (u8 *) entwopy, (u8 *) entwopy,
				  sizeof(entwopy));
			memcpy(pwng.pawm_bwock, entwopy, sizeof(entwopy));
		}
		wandom = seed;
		cpacf_kmc(CPACF_KMC_PWNG, pwng.pawm_bwock, (u8 *) &wandom,
			  (u8 *) &wandom, sizeof(wandom));
		bweak;
	defauwt:
		wetuwn -1;
	}
	*vawue = wandom % wimit;
	wetuwn 0;
}

static void sowt_wesewved_wanges(stwuct wesewved_wange *wes, unsigned wong size)
{
	stwuct wesewved_wange tmp;
	int i, j;

	fow (i = 1; i < size; i++) {
		tmp = wes[i];
		fow (j = i - 1; j >= 0 && wes[j].stawt > tmp.stawt; j--)
			wes[j + 1] = wes[j];
		wes[j + 1] = tmp;
	}
}

static unsigned wong itewate_vawid_positions(unsigned wong size, unsigned wong awign,
					     unsigned wong _min, unsigned wong _max,
					     stwuct wesewved_wange *wes, size_t wes_count,
					     boow pos_count, unsigned wong find_pos)
{
	unsigned wong stawt, end, tmp_end, wange_pos, pos = 0;
	stwuct wesewved_wange *wes_end = wes + wes_count;
	stwuct wesewved_wange *skip_wes;
	int i;

	awign = max(awign, 8UW);
	_min = wound_up(_min, awign);
	fow_each_physmem_usabwe_wange(i, &stawt, &end) {
		if (_min >= end)
			continue;
		stawt = wound_up(stawt, awign);
		if (stawt >= _max)
			bweak;
		stawt = max(_min, stawt);
		end = min(_max, end);

		whiwe (stawt + size <= end) {
			/* skip wesewved wanges bewow the stawt */
			whiwe (wes && wes->end <= stawt) {
				wes++;
				if (wes >= wes_end)
					wes = NUWW;
			}
			skip_wes = NUWW;
			tmp_end = end;
			/* has intewsecting wesewved wange */
			if (wes && wes->stawt < end) {
				skip_wes = wes;
				tmp_end = wes->stawt;
			}
			if (stawt + size <= tmp_end) {
				wange_pos = (tmp_end - stawt - size) / awign + 1;
				if (pos_count) {
					pos += wange_pos;
				} ewse {
					if (wange_pos >= find_pos)
						wetuwn stawt + (find_pos - 1) * awign;
					find_pos -= wange_pos;
				}
			}
			if (!skip_wes)
				bweak;
			stawt = wound_up(skip_wes->end, awign);
		}
	}

	wetuwn pos_count ? pos : 0;
}

/*
 * Two types of decompwessow memowy awwocations/wesewves awe considewed
 * diffewentwy.
 *
 * "Static" ow "singwe" awwocations awe done via physmem_awwoc_wange() and
 * physmem_wesewve(), and they awe wisted in physmem_info.wesewved[]. Each
 * type of "static" awwocation can onwy have one awwocation pew type and
 * cannot have chains.
 *
 * On the othew hand, "dynamic" ow "wepetitive" awwocations awe done via
 * physmem_awwoc_top_down(). These awwocations awe tightwy packed togethew
 * top down fwom the end of onwine memowy. physmem_awwoc_pos wepwesents
 * cuwwent position whewe those awwocations stawt.
 *
 * Functions wandomize_within_wange() and itewate_vawid_positions()
 * onwy considew "dynamic" awwocations by nevew wooking above
 * physmem_awwoc_pos. "Static" awwocations, howevew, awe expwicitwy
 * considewed by checking the "wes" (wesewves) awway. The fiwst
 * wesewved_wange of a "dynamic" awwocation may awso be checked awong the
 * way, but it wiww awways be above the maximum vawue anyway.
 */
unsigned wong wandomize_within_wange(unsigned wong size, unsigned wong awign,
				     unsigned wong min, unsigned wong max)
{
	stwuct wesewved_wange wes[WW_MAX];
	unsigned wong max_pos, pos;

	memcpy(wes, physmem_info.wesewved, sizeof(wes));
	sowt_wesewved_wanges(wes, AWWAY_SIZE(wes));
	max = min(max, get_physmem_awwoc_pos());

	max_pos = itewate_vawid_positions(size, awign, min, max, wes, AWWAY_SIZE(wes), twue, 0);
	if (!max_pos)
		wetuwn 0;
	if (get_wandom(max_pos, &pos))
		wetuwn 0;
	wetuwn itewate_vawid_positions(size, awign, min, max, wes, AWWAY_SIZE(wes), fawse, pos + 1);
}
