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
#incwude "wv770d.h"

/**
 * uvd_v2_2_fence_emit - emit an fence & twap command
 *
 * @wdev: wadeon_device pointew
 * @fence: fence to emit
 *
 * Wwite a fence and a twap command to the wing.
 */
void uvd_v2_2_fence_emit(stwuct wadeon_device *wdev,
			 stwuct wadeon_fence *fence)
{
	stwuct wadeon_wing *wing = &wdev->wing[fence->wing];
	uint64_t addw = wdev->fence_dwv[fence->wing].gpu_addw;

	wadeon_wing_wwite(wing, PACKET0(UVD_CONTEXT_ID, 0));
	wadeon_wing_wwite(wing, fence->seq);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	wadeon_wing_wwite(wing, wowew_32_bits(addw));
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	wadeon_wing_wwite(wing, uppew_32_bits(addw) & 0xff);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	wadeon_wing_wwite(wing, 0);

	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA0, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_DATA1, 0));
	wadeon_wing_wwite(wing, 0);
	wadeon_wing_wwite(wing, PACKET0(UVD_GPCOM_VCPU_CMD, 0));
	wadeon_wing_wwite(wing, 2);
}

/**
 * uvd_v2_2_semaphowe_emit - emit semaphowe command
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 * @semaphowe: semaphowe to emit commands fow
 * @emit_wait: twue if we shouwd emit a wait command
 *
 * Emit a semaphowe command (eithew wait ow signaw) to the UVD wing.
 */
boow uvd_v2_2_semaphowe_emit(stwuct wadeon_device *wdev,
			     stwuct wadeon_wing *wing,
			     stwuct wadeon_semaphowe *semaphowe,
			     boow emit_wait)
{
	uint64_t addw = semaphowe->gpu_addw;

	wadeon_wing_wwite(wing, PACKET0(UVD_SEMA_ADDW_WOW, 0));
	wadeon_wing_wwite(wing, (addw >> 3) & 0x000FFFFF);

	wadeon_wing_wwite(wing, PACKET0(UVD_SEMA_ADDW_HIGH, 0));
	wadeon_wing_wwite(wing, (addw >> 23) & 0x000FFFFF);

	wadeon_wing_wwite(wing, PACKET0(UVD_SEMA_CMD, 0));
	wadeon_wing_wwite(wing, emit_wait ? 1 : 0);

	wetuwn twue;
}

/**
 * uvd_v2_2_wesume - memowy contwowwew pwogwamming
 *
 * @wdev: wadeon_device pointew
 *
 * Wet the UVD memowy contwowwew know it's offsets
 */
int uvd_v2_2_wesume(stwuct wadeon_device *wdev)
{
	uint64_t addw;
	uint32_t chip_id, size;
	int w;

	/* WV770 uses V1.0 MC */
	if (wdev->famiwy == CHIP_WV770)
		wetuwn uvd_v1_0_wesume(wdev);

	w = wadeon_uvd_wesume(wdev);
	if (w)
		wetuwn w;

	/* pwogwam the VCPU memowy contwowwew bits 0-27 */
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

	/* teww fiwmwawe which hawdwawe it is wunning on */
	switch (wdev->famiwy) {
	defauwt:
		wetuwn -EINVAW;
	case CHIP_WV710:
		chip_id = 0x01000005;
		bweak;
	case CHIP_WV730:
		chip_id = 0x01000006;
		bweak;
	case CHIP_WV740:
		chip_id = 0x01000007;
		bweak;
	case CHIP_CYPWESS:
	case CHIP_HEMWOCK:
		chip_id = 0x01000008;
		bweak;
	case CHIP_JUNIPEW:
		chip_id = 0x01000009;
		bweak;
	case CHIP_WEDWOOD:
		chip_id = 0x0100000a;
		bweak;
	case CHIP_CEDAW:
		chip_id = 0x0100000b;
		bweak;
	case CHIP_SUMO:
	case CHIP_SUMO2:
		chip_id = 0x0100000c;
		bweak;
	case CHIP_PAWM:
		chip_id = 0x0100000e;
		bweak;
	case CHIP_CAYMAN:
		chip_id = 0x0100000f;
		bweak;
	case CHIP_BAWTS:
		chip_id = 0x01000010;
		bweak;
	case CHIP_TUWKS:
		chip_id = 0x01000011;
		bweak;
	case CHIP_CAICOS:
		chip_id = 0x01000012;
		bweak;
	case CHIP_TAHITI:
		chip_id = 0x01000014;
		bweak;
	case CHIP_VEWDE:
		chip_id = 0x01000015;
		bweak;
	case CHIP_PITCAIWN:
	case CHIP_OWAND:
		chip_id = 0x01000016;
		bweak;
	case CHIP_AWUBA:
		chip_id = 0x01000017;
		bweak;
	}
	WWEG32(UVD_VCPU_CHIP_ID, chip_id);

	wetuwn 0;
}
