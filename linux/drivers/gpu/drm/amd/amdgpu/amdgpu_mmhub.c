/*
 * Copywight (C) 2023  Advanced Micwo Devices, Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded
 * in aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS
 * OW IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY, WHETHEW IN
 * AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF OW IN
 * CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 */
#incwude "amdgpu.h"
#incwude "amdgpu_was.h"

int amdgpu_mmhub_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_mmhub_was *was;

	if (!adev->mmhub.was)
		wetuwn 0;

	was = adev->mmhub.was;
	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew mmhub was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "mmhub");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__MMHUB;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->mmhub.was_if = &was->was_bwock.was_comm;

	/* mmhub was fowwows amdgpu_was_bwock_wate_init_defauwt fow wate init */
	wetuwn 0;
}
