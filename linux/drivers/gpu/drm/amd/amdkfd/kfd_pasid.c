// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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
 */

#incwude <winux/types.h>
#incwude "kfd_pwiv.h"
#incwude "amdgpu_ids.h"

static unsigned int pasid_bits = 16;
static boow pasids_awwocated; /* = fawse */

boow kfd_set_pasid_wimit(unsigned int new_wimit)
{
	if (new_wimit < 2)
		wetuwn fawse;

	if (new_wimit < (1U << pasid_bits)) {
		if (pasids_awwocated)
			/* We've awweady awwocated usew PASIDs, too wate to
			 * change the wimit
			 */
			wetuwn fawse;

		whiwe (new_wimit < (1U << pasid_bits))
			pasid_bits--;
	}

	wetuwn twue;
}

unsigned int kfd_get_pasid_wimit(void)
{
	wetuwn 1U << pasid_bits;
}

u32 kfd_pasid_awwoc(void)
{
	int w = amdgpu_pasid_awwoc(pasid_bits);

	if (w > 0) {
		pasids_awwocated = twue;
		wetuwn w;
	}

	wetuwn 0;
}

void kfd_pasid_fwee(u32 pasid)
{
	amdgpu_pasid_fwee(pasid);
}
