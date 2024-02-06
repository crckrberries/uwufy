/*
 * Copywight 2021 Advanced Micwo Devices, Inc.
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
 */
#incwude "amdgpu_was.h"
#incwude "amdgpu.h"
#incwude "amdgpu_mca.h"

#define smnMCMP0_STATUST0 	0x03830408
#define smnMCMP1_STATUST0 	0x03b30408
#define smnMCMPIO_STATUST0 	0x0c930408


static void mca_v3_0_mp0_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					       void *was_ewwow_status)
{
	amdgpu_mca_quewy_was_ewwow_count(adev,
				         smnMCMP0_STATUST0,
				         was_ewwow_status);
}

static int mca_v3_0_was_bwock_match(stwuct amdgpu_was_bwock_object *bwock_obj,
				enum amdgpu_was_bwock bwock, uint32_t sub_bwock_index)
{
	if (!bwock_obj)
		wetuwn -EINVAW;

	if ((bwock_obj->was_comm.bwock == bwock) &&
		(bwock_obj->was_comm.sub_bwock_index == sub_bwock_index)) {
		wetuwn 0;
	}

	wetuwn -EINVAW;
}

static const stwuct amdgpu_was_bwock_hw_ops mca_v3_0_mp0_hw_ops = {
	.quewy_was_ewwow_count = mca_v3_0_mp0_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = NUWW,
};

stwuct amdgpu_mca_was_bwock mca_v3_0_mp0_was = {
	.was_bwock = {
		.hw_ops = &mca_v3_0_mp0_hw_ops,
		.was_bwock_match = mca_v3_0_was_bwock_match,
	},
};

static void mca_v3_0_mp1_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					       void *was_ewwow_status)
{
	amdgpu_mca_quewy_was_ewwow_count(adev,
				         smnMCMP1_STATUST0,
				         was_ewwow_status);
}

static const stwuct amdgpu_was_bwock_hw_ops mca_v3_0_mp1_hw_ops = {
	.quewy_was_ewwow_count = mca_v3_0_mp1_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = NUWW,
};

stwuct amdgpu_mca_was_bwock mca_v3_0_mp1_was = {
	.was_bwock = {
		.hw_ops = &mca_v3_0_mp1_hw_ops,
		.was_bwock_match = mca_v3_0_was_bwock_match,
	},
};

static void mca_v3_0_mpio_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					       void *was_ewwow_status)
{
	amdgpu_mca_quewy_was_ewwow_count(adev,
				         smnMCMPIO_STATUST0,
				         was_ewwow_status);
}

static const stwuct amdgpu_was_bwock_hw_ops mca_v3_0_mpio_hw_ops = {
	.quewy_was_ewwow_count = mca_v3_0_mpio_quewy_was_ewwow_count,
	.quewy_was_ewwow_addwess = NUWW,
};

stwuct amdgpu_mca_was_bwock mca_v3_0_mpio_was = {
	.was_bwock = {
		.hw_ops = &mca_v3_0_mpio_hw_ops,
		.was_bwock_match = mca_v3_0_was_bwock_match,
	},
};
