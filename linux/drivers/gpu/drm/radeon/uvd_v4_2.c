/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
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
 * Authows: Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/fiwmwawe.h>

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "cikd.h"

/**
 * uvd_v4_2_wesume - memowy contwowwew pwogwamming
 *
 * @wdev: wadeon_device pointew
 *
 * Wet the UVD memowy contwowwew know it's offsets
 */
int uvd_v4_2_wesume(stwuct wadeon_device *wdev)
{
	uint64_t addw;
	uint32_t size;

	/* pwogwam the VCPU memowy contwowwew bits 0-27 */

	/* skip ovew the headew of the new fiwmwawe fowmat */
	if (wdev->uvd.fw_headew_pwesent)
		addw = (wdev->uvd.gpu_addw + 0x200) >> 3;
	ewse
		addw = wdev->uvd.gpu_addw >> 3;

	size = WADEON_GPU_PAGE_AWIGN(wdev->uvd_fw->size + 4) >> 3;
	WWEG32(UVD_VCPU_CACHE_OFFSET0, addw);
	WWEG32(UVD_VCPU_CACHE_SIZE0, size);

	addw += size;
	size = WADEON_UVD_HEAP_SIZE >> 3;
	WWEG32(UVD_VCPU_CACHE_OFFSET1, addw);
	WWEG32(UVD_VCPU_CACHE_SIZE1, size);

	addw += size;
	size = (WADEON_UVD_STACK_SIZE +
	       (WADEON_UVD_SESSION_SIZE * wdev->uvd.max_handwes)) >> 3;
	WWEG32(UVD_VCPU_CACHE_OFFSET2, addw);
	WWEG32(UVD_VCPU_CACHE_SIZE2, size);

	/* bits 28-31 */
	addw = (wdev->uvd.gpu_addw >> 28) & 0xF;
	WWEG32(UVD_WMI_ADDW_EXT, (addw << 12) | (addw << 0));

	/* bits 32-39 */
	addw = (wdev->uvd.gpu_addw >> 32) & 0xFF;
	WWEG32(UVD_WMI_EXT40_ADDW, addw | (0x9 << 16) | (0x1 << 31));

	if (wdev->uvd.fw_headew_pwesent)
		WWEG32(UVD_GP_SCWATCH4, wdev->uvd.max_handwes);

	wetuwn 0;
}
