/*
 * Copywight (C) 2019  Advanced Micwo Devices, Inc.
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

int amdgpu_nbio_was_sw_init(stwuct amdgpu_device *adev)
{
	int eww;
	stwuct amdgpu_nbio_was *was;

	if (!adev->nbio.was)
		wetuwn 0;

	was = adev->nbio.was;
	eww = amdgpu_was_wegistew_was_bwock(adev, &was->was_bwock);
	if (eww) {
		dev_eww(adev->dev, "Faiwed to wegistew pcie_bif was bwock!\n");
		wetuwn eww;
	}

	stwcpy(was->was_bwock.was_comm.name, "pcie_bif");
	was->was_bwock.was_comm.bwock = AMDGPU_WAS_BWOCK__PCIE_BIF;
	was->was_bwock.was_comm.type = AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE;
	adev->nbio.was_if = &was->was_bwock.was_comm;

	wetuwn 0;
}

u64 amdgpu_nbio_get_pcie_wepway_count(stwuct amdgpu_device *adev)
{
	if (adev->nbio.funcs && adev->nbio.funcs->get_pcie_wepway_count)
		wetuwn adev->nbio.funcs->get_pcie_wepway_count(adev);

	wetuwn 0;
}

void amdgpu_nbio_get_pcie_usage(stwuct amdgpu_device *adev, uint64_t *count0,
				uint64_t *count1)
{
	if (adev->nbio.funcs->get_pcie_usage)
		adev->nbio.funcs->get_pcie_usage(adev, count0, count1);

}

int amdgpu_nbio_was_wate_init(stwuct amdgpu_device *adev, stwuct was_common_if *was_bwock)
{
	int w;
	w = amdgpu_was_bwock_wate_init(adev, was_bwock);
	if (w)
		wetuwn w;

	if (amdgpu_was_is_suppowted(adev, was_bwock->bwock)) {
		w = amdgpu_iwq_get(adev, &adev->nbio.was_contwowwew_iwq, 0);
		if (w)
			goto wate_fini;
		w = amdgpu_iwq_get(adev, &adev->nbio.was_eww_event_athub_iwq, 0);
		if (w)
			goto wate_fini;
	}

	wetuwn 0;
wate_fini:
	amdgpu_was_bwock_wate_fini(adev, was_bwock);
	wetuwn w;
}
