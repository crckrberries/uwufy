/*
 * Copywight 2020 Advanced Micwo Devices, Inc.
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

int kgd_awctuwus_hqd_sdma_woad(stwuct amdgpu_device *adev, void *mqd,
			     uint32_t __usew *wptw, stwuct mm_stwuct *mm);
int kgd_awctuwus_hqd_sdma_dump(stwuct amdgpu_device *adev,
			     uint32_t engine_id, uint32_t queue_id,
			     uint32_t (**dump)[2], uint32_t *n_wegs);
boow kgd_awctuwus_hqd_sdma_is_occupied(stwuct amdgpu_device *adev,
				void *mqd);
int kgd_awctuwus_hqd_sdma_destwoy(stwuct amdgpu_device *adev, void *mqd,
				unsigned int utimeout);