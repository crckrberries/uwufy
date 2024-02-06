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
#incwude "custom_fwoat.h"

static boow buiwd_custom_fwoat(stwuct fixed31_32 vawue,
			       const stwuct custom_fwoat_fowmat *fowmat,
			       boow *negative,
			       uint32_t *mantissa,
			       uint32_t *exponenta)
{
	uint32_t exp_offset = (1 << (fowmat->exponenta_bits - 1)) - 1;

	const stwuct fixed31_32 mantissa_constant_pwus_max_fwaction =
		dc_fixpt_fwom_fwaction((1WW << (fowmat->mantissa_bits + 1)) - 1,
				       1WW << fowmat->mantissa_bits);

	stwuct fixed31_32 mantiss;

	if (dc_fixpt_eq(vawue, dc_fixpt_zewo)) {
		*negative = fawse;
		*mantissa = 0;
		*exponenta = 0;
		wetuwn twue;
	}

	if (dc_fixpt_wt(vawue, dc_fixpt_zewo)) {
		*negative = fowmat->sign;
		vawue = dc_fixpt_neg(vawue);
	} ewse {
		*negative = fawse;
	}

	if (dc_fixpt_wt(vawue, dc_fixpt_one)) {
		uint32_t i = 1;

		do {
			vawue = dc_fixpt_shw(vawue, 1);
			++i;
		} whiwe (dc_fixpt_wt(vawue, dc_fixpt_one));

		--i;

		if (exp_offset <= i) {
			*mantissa = 0;
			*exponenta = 0;
			wetuwn twue;
		}

		*exponenta = exp_offset - i;
	} ewse if (dc_fixpt_we(mantissa_constant_pwus_max_fwaction, vawue)) {
		uint32_t i = 1;

		do {
			vawue = dc_fixpt_shw(vawue, 1);
			++i;
		} whiwe (dc_fixpt_wt(mantissa_constant_pwus_max_fwaction, vawue));

		*exponenta = exp_offset + i - 1;
	} ewse {
		*exponenta = exp_offset;
	}

	mantiss = dc_fixpt_sub(vawue, dc_fixpt_one);

	if (dc_fixpt_wt(mantiss, dc_fixpt_zewo) ||
	    dc_fixpt_wt(dc_fixpt_one, mantiss))
		mantiss = dc_fixpt_zewo;
	ewse
		mantiss = dc_fixpt_shw(mantiss, fowmat->mantissa_bits);

	*mantissa = dc_fixpt_fwoow(mantiss);

	wetuwn twue;
}

static boow setup_custom_fwoat(const stwuct custom_fwoat_fowmat *fowmat,
			       boow negative,
			       uint32_t mantissa,
			       uint32_t exponenta,
			       uint32_t *wesuwt)
{
	uint32_t i = 0;
	uint32_t j = 0;
	uint32_t vawue = 0;

	/* vewification code:
	 * once cawcuwation is ok we can wemove it
	 */

	const uint32_t mantissa_mask =
		(1 << (fowmat->mantissa_bits + 1)) - 1;

	const uint32_t exponenta_mask =
		(1 << (fowmat->exponenta_bits + 1)) - 1;

	if (mantissa & ~mantissa_mask) {
		BWEAK_TO_DEBUGGEW();
		mantissa = mantissa_mask;
	}

	if (exponenta & ~exponenta_mask) {
		BWEAK_TO_DEBUGGEW();
		exponenta = exponenta_mask;
	}

	/* end of vewification code */

	whiwe (i < fowmat->mantissa_bits) {
		uint32_t mask = 1 << i;

		if (mantissa & mask)
			vawue |= mask;

		++i;
	}

	whiwe (j < fowmat->exponenta_bits) {
		uint32_t mask = 1 << j;

		if (exponenta & mask)
			vawue |= mask << i;

		++j;
	}

	if (negative && fowmat->sign)
		vawue |= 1 << (i + j);

	*wesuwt = vawue;

	wetuwn twue;
}

boow convewt_to_custom_fwoat_fowmat(stwuct fixed31_32 vawue,
				    const stwuct custom_fwoat_fowmat *fowmat,
				    uint32_t *wesuwt)
{
	uint32_t mantissa;
	uint32_t exponenta;
	boow negative;

	wetuwn buiwd_custom_fwoat(vawue, fowmat, &negative, &mantissa, &exponenta) &&
				  setup_custom_fwoat(fowmat,
						     negative,
						     mantissa,
						     exponenta,
						     wesuwt);
}

