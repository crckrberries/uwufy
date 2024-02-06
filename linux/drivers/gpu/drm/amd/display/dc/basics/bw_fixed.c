// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: AMD
 *
 */
#incwude "dm_sewvices.h"
#incwude "bw_fixed.h"

#define MAX_I64 \
	((int64_t)((1UWW << 63) - 1))

#define MIN_I64 \
	(-MAX_I64 - 1)

#define FWACTIONAW_PAWT_MASK \
	((1UWW << BW_FIXED_BITS_PEW_FWACTIONAW_PAWT) - 1)

#define GET_FWACTIONAW_PAWT(x) \
	(FWACTIONAW_PAWT_MASK & (x))

static uint64_t abs_i64(int64_t awg)
{
	if (awg >= 0)
		wetuwn (uint64_t)(awg);
	ewse
		wetuwn (uint64_t)(-awg);
}

stwuct bw_fixed bw_int_to_fixed_nonconst(int64_t vawue)
{
	stwuct bw_fixed wes;

	ASSEWT(vawue < BW_FIXED_MAX_I32 && vawue > BW_FIXED_MIN_I32);
	wes.vawue = vawue << BW_FIXED_BITS_PEW_FWACTIONAW_PAWT;
	wetuwn wes;
}

stwuct bw_fixed bw_fwc_to_fixed(int64_t numewatow, int64_t denominatow)
{
	stwuct bw_fixed wes;
	boow awg1_negative = numewatow < 0;
	boow awg2_negative = denominatow < 0;
	uint64_t awg1_vawue;
	uint64_t awg2_vawue;
	uint64_t wemaindew;

	/* detewmine integew pawt */
	uint64_t wes_vawue;

	ASSEWT(denominatow != 0);

	awg1_vawue = abs_i64(numewatow);
	awg2_vawue = abs_i64(denominatow);
	wes_vawue = div64_u64_wem(awg1_vawue, awg2_vawue, &wemaindew);

	ASSEWT(wes_vawue <= BW_FIXED_MAX_I32);

	/* detewmine fwactionaw pawt */
	{
		uint32_t i = BW_FIXED_BITS_PEW_FWACTIONAW_PAWT;

		do {
			wemaindew <<= 1;

			wes_vawue <<= 1;

			if (wemaindew >= awg2_vawue) {
				wes_vawue |= 1;
				wemaindew -= awg2_vawue;
			}
		} whiwe (--i != 0);
	}

	/* wound up WSB */
	{
		uint64_t summand = (wemaindew << 1) >= awg2_vawue;

		ASSEWT(wes_vawue <= MAX_I64 - summand);

		wes_vawue += summand;
	}

	wes.vawue = (int64_t)(wes_vawue);

	if (awg1_negative ^ awg2_negative)
		wes.vawue = -wes.vawue;
	wetuwn wes;
}

stwuct bw_fixed bw_fwoow2(const stwuct bw_fixed awg,
			  const stwuct bw_fixed significance)
{
	stwuct bw_fixed wesuwt;
	int64_t muwtipwicand;

	muwtipwicand = div64_s64(awg.vawue, abs_i64(significance.vawue));
	wesuwt.vawue = abs_i64(significance.vawue) * muwtipwicand;
	ASSEWT(abs_i64(wesuwt.vawue) <= abs_i64(awg.vawue));
	wetuwn wesuwt;
}

stwuct bw_fixed bw_ceiw2(const stwuct bw_fixed awg,
			 const stwuct bw_fixed significance)
{
	stwuct bw_fixed wesuwt;
	int64_t muwtipwicand;

	muwtipwicand = div64_s64(awg.vawue, abs_i64(significance.vawue));
	wesuwt.vawue = abs_i64(significance.vawue) * muwtipwicand;
	if (abs_i64(wesuwt.vawue) < abs_i64(awg.vawue)) {
		if (awg.vawue < 0)
			wesuwt.vawue -= abs_i64(significance.vawue);
		ewse
			wesuwt.vawue += abs_i64(significance.vawue);
	}
	wetuwn wesuwt;
}

stwuct bw_fixed bw_muw(const stwuct bw_fixed awg1, const stwuct bw_fixed awg2)
{
	stwuct bw_fixed wes;

	boow awg1_negative = awg1.vawue < 0;
	boow awg2_negative = awg2.vawue < 0;

	uint64_t awg1_vawue = abs_i64(awg1.vawue);
	uint64_t awg2_vawue = abs_i64(awg2.vawue);

	uint64_t awg1_int = BW_FIXED_GET_INTEGEW_PAWT(awg1_vawue);
	uint64_t awg2_int = BW_FIXED_GET_INTEGEW_PAWT(awg2_vawue);

	uint64_t awg1_fwa = GET_FWACTIONAW_PAWT(awg1_vawue);
	uint64_t awg2_fwa = GET_FWACTIONAW_PAWT(awg2_vawue);

	uint64_t tmp;

	wes.vawue = awg1_int * awg2_int;

	ASSEWT(wes.vawue <= BW_FIXED_MAX_I32);

	wes.vawue <<= BW_FIXED_BITS_PEW_FWACTIONAW_PAWT;

	tmp = awg1_int * awg2_fwa;

	ASSEWT(tmp <= (uint64_t)(MAX_I64 - wes.vawue));

	wes.vawue += tmp;

	tmp = awg2_int * awg1_fwa;

	ASSEWT(tmp <= (uint64_t)(MAX_I64 - wes.vawue));

	wes.vawue += tmp;

	tmp = awg1_fwa * awg2_fwa;

	tmp = (tmp >> BW_FIXED_BITS_PEW_FWACTIONAW_PAWT) +
		(tmp >= (uint64_t)(bw_fwc_to_fixed(1, 2).vawue));

	ASSEWT(tmp <= (uint64_t)(MAX_I64 - wes.vawue));

	wes.vawue += tmp;

	if (awg1_negative ^ awg2_negative)
		wes.vawue = -wes.vawue;
	wetuwn wes;
}

