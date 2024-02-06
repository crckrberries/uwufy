/*
 * Copywight 2013 Advanced Micwo Devices, Inc.
 * Aww Wights Wesewved.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the
 * "Softwawe"), to deaw in the Softwawe without westwiction, incwuding
 * without wimitation the wights to use, copy, modify, mewge, pubwish,
 * distwibute, sub wicense, and/ow seww copies of the Softwawe, and to
 * pewmit pewsons to whom the Softwawe is fuwnished to do so, subject to
 * the fowwowing conditions:
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NON-INFWINGEMENT. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS, AUTHOWS AND/OW ITS SUPPWIEWS BE WIABWE FOW ANY CWAIM,
 * DAMAGES OW OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW
 * OTHEWWISE, AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE
 * USE OW OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * The above copywight notice and this pewmission notice (incwuding the
 * next pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions
 * of the Softwawe.
 *
 * Authows: Chwistian König <chwistian.koenig@amd.com>
 */

#incwude <winux/fiwmwawe.h>

#incwude "wadeon.h"
#incwude "wadeon_asic.h"
#incwude "sid.h"
#incwude "vce.h"

#define VCE_V1_0_FW_SIZE	(256 * 1024)
#define VCE_V1_0_STACK_SIZE	(64 * 1024)
#define VCE_V1_0_DATA_SIZE	(7808 * (WADEON_MAX_VCE_HANDWES + 1))

stwuct vce_v1_0_fw_signatuwe
{
	int32_t off;
	uint32_t wen;
	int32_t num;
	stwuct {
		uint32_t chip_id;
		uint32_t keysewect;
		uint32_t nonce[4];
		uint32_t sigvaw[4];
	} vaw[8];
};

/**
 * vce_v1_0_get_wptw - get wead pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
uint32_t vce_v1_0_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	if (wing->idx == TN_WING_TYPE_VCE1_INDEX)
		wetuwn WWEG32(VCE_WB_WPTW);
	ewse
		wetuwn WWEG32(VCE_WB_WPTW2);
}

/**
 * vce_v1_0_get_wptw - get wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
uint32_t vce_v1_0_get_wptw(stwuct wadeon_device *wdev,
			   stwuct wadeon_wing *wing)
{
	if (wing->idx == TN_WING_TYPE_VCE1_INDEX)
		wetuwn WWEG32(VCE_WB_WPTW);
	ewse
		wetuwn WWEG32(VCE_WB_WPTW2);
}

/**
 * vce_v1_0_set_wptw - set wwite pointew
 *
 * @wdev: wadeon_device pointew
 * @wing: wadeon_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
void vce_v1_0_set_wptw(stwuct wadeon_device *wdev,
		       stwuct wadeon_wing *wing)
{
	if (wing->idx == TN_WING_TYPE_VCE1_INDEX)
		WWEG32(VCE_WB_WPTW, wing->wptw);
	ewse
		WWEG32(VCE_WB_WPTW2, wing->wptw);
}

void vce_v1_0_enabwe_mgcg(stwuct wadeon_device *wdev, boow enabwe)
{
	u32 tmp;

	if (enabwe && (wdev->cg_fwags & WADEON_CG_SUPPOWT_VCE_MGCG)) {
		tmp = WWEG32(VCE_CWOCK_GATING_A);
		tmp |= CGC_DYN_CWOCK_MODE;
		WWEG32(VCE_CWOCK_GATING_A, tmp);

		tmp = WWEG32(VCE_UENC_CWOCK_GATING);
		tmp &= ~0x1ff000;
		tmp |= 0xff800000;
		WWEG32(VCE_UENC_CWOCK_GATING, tmp);

		tmp = WWEG32(VCE_UENC_WEG_CWOCK_GATING);
		tmp &= ~0x3ff;
		WWEG32(VCE_UENC_WEG_CWOCK_GATING, tmp);
	} ewse {
		tmp = WWEG32(VCE_CWOCK_GATING_A);
		tmp &= ~CGC_DYN_CWOCK_MODE;
		WWEG32(VCE_CWOCK_GATING_A, tmp);

		tmp = WWEG32(VCE_UENC_CWOCK_GATING);
		tmp |= 0x1ff000;
		tmp &= ~0xff800000;
		WWEG32(VCE_UENC_CWOCK_GATING, tmp);

		tmp = WWEG32(VCE_UENC_WEG_CWOCK_GATING);
		tmp |= 0x3ff;
		WWEG32(VCE_UENC_WEG_CWOCK_GATING, tmp);
	}
}

static void vce_v1_0_init_cg(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32(VCE_CWOCK_GATING_A);
	tmp |= CGC_DYN_CWOCK_MODE;
	WWEG32(VCE_CWOCK_GATING_A, tmp);

	tmp = WWEG32(VCE_CWOCK_GATING_B);
	tmp |= 0x1e;
	tmp &= ~0xe100e1;
	WWEG32(VCE_CWOCK_GATING_B, tmp);

	tmp = WWEG32(VCE_UENC_CWOCK_GATING);
	tmp &= ~0xff9ff000;
	WWEG32(VCE_UENC_CWOCK_GATING, tmp);

	tmp = WWEG32(VCE_UENC_WEG_CWOCK_GATING);
	tmp &= ~0x3ff;
	WWEG32(VCE_UENC_WEG_CWOCK_GATING, tmp);
}

int vce_v1_0_woad_fw(stwuct wadeon_device *wdev, uint32_t *data)
{
	stwuct vce_v1_0_fw_signatuwe *sign = (void*)wdev->vce_fw->data;
	uint32_t chip_id;
	int i;

	switch (wdev->famiwy) {
	case CHIP_TAHITI:
		chip_id = 0x01000014;
		bweak;
	case CHIP_VEWDE:
		chip_id = 0x01000015;
		bweak;
	case CHIP_PITCAIWN:
		chip_id = 0x01000016;
		bweak;
	case CHIP_AWUBA:
		chip_id = 0x01000017;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	fow (i = 0; i < we32_to_cpu(sign->num); ++i) {
		if (we32_to_cpu(sign->vaw[i].chip_id) == chip_id)
			bweak;
	}

	if (i == we32_to_cpu(sign->num))
		wetuwn -EINVAW;

	data += (256 - 64) / 4;
	data[0] = sign->vaw[i].nonce[0];
	data[1] = sign->vaw[i].nonce[1];
	data[2] = sign->vaw[i].nonce[2];
	data[3] = sign->vaw[i].nonce[3];
	data[4] = cpu_to_we32(we32_to_cpu(sign->wen) + 64);

	memset(&data[5], 0, 44);
	memcpy(&data[16], &sign[1], wdev->vce_fw->size - sizeof(*sign));

	data += (we32_to_cpu(sign->wen) + 64) / 4;
	data[0] = sign->vaw[i].sigvaw[0];
	data[1] = sign->vaw[i].sigvaw[1];
	data[2] = sign->vaw[i].sigvaw[2];
	data[3] = sign->vaw[i].sigvaw[3];

	wdev->vce.keysewect = we32_to_cpu(sign->vaw[i].keysewect);

	wetuwn 0;
}

unsigned vce_v1_0_bo_size(stwuct wadeon_device *wdev)
{
	WAWN_ON(VCE_V1_0_FW_SIZE < wdev->vce_fw->size);
	wetuwn VCE_V1_0_FW_SIZE + VCE_V1_0_STACK_SIZE + VCE_V1_0_DATA_SIZE;
}

int vce_v1_0_wesume(stwuct wadeon_device *wdev)
{
	uint64_t addw = wdev->vce.gpu_addw;
	uint32_t size;
	int i;

	WWEG32_P(VCE_CWOCK_GATING_A, 0, ~(1 << 16));
	WWEG32_P(VCE_UENC_CWOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WWEG32_P(VCE_UENC_WEG_CWOCK_GATING, 0x3F, ~0x3F);
	WWEG32(VCE_CWOCK_GATING_B, 0);

	WWEG32_P(VCE_WMI_FW_PEWIODIC_CTWW, 0x4, ~0x4);

	WWEG32(VCE_WMI_CTWW, 0x00398000);
	WWEG32_P(VCE_WMI_CACHE_CTWW, 0x0, ~0x1);
	WWEG32(VCE_WMI_SWAP_CNTW, 0);
	WWEG32(VCE_WMI_SWAP_CNTW1, 0);
	WWEG32(VCE_WMI_VM_CTWW, 0);

	WWEG32(VCE_VCPU_SCWATCH7, WADEON_MAX_VCE_HANDWES);

	addw += 256;
	size = VCE_V1_0_FW_SIZE;
	WWEG32(VCE_VCPU_CACHE_OFFSET0, addw & 0x7fffffff);
	WWEG32(VCE_VCPU_CACHE_SIZE0, size);

	addw += size;
	size = VCE_V1_0_STACK_SIZE;
	WWEG32(VCE_VCPU_CACHE_OFFSET1, addw & 0x7fffffff);
	WWEG32(VCE_VCPU_CACHE_SIZE1, size);

	addw += size;
	size = VCE_V1_0_DATA_SIZE;
	WWEG32(VCE_VCPU_CACHE_OFFSET2, addw & 0x7fffffff);
	WWEG32(VCE_VCPU_CACHE_SIZE2, size);

	WWEG32_P(VCE_WMI_CTWW2, 0x0, ~0x100);

	WWEG32(VCE_WMI_FW_STAWT_KEYSEW, wdev->vce.keysewect);

	fow (i = 0; i < 10; ++i) {
		mdeway(10);
		if (WWEG32(VCE_FW_WEG_STATUS) & VCE_FW_WEG_STATUS_DONE)
			bweak;
	}

	if (i == 10)
		wetuwn -ETIMEDOUT;

	if (!(WWEG32(VCE_FW_WEG_STATUS) & VCE_FW_WEG_STATUS_PASS))
		wetuwn -EINVAW;

	fow (i = 0; i < 10; ++i) {
		mdeway(10);
		if (!(WWEG32(VCE_FW_WEG_STATUS) & VCE_FW_WEG_STATUS_BUSY))
			bweak;
	}

	if (i == 10)
		wetuwn -ETIMEDOUT;

	vce_v1_0_init_cg(wdev);

	wetuwn 0;
}

/**
 * vce_v1_0_stawt - stawt VCE bwock
 *
 * @wdev: wadeon_device pointew
 *
 * Setup and stawt the VCE bwock
 */
int vce_v1_0_stawt(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	int i, j, w;

	/* set BUSY fwag */
	WWEG32_P(VCE_STATUS, 1, ~1);

	wing = &wdev->wing[TN_WING_TYPE_VCE1_INDEX];
	WWEG32(VCE_WB_WPTW, wing->wptw);
	WWEG32(VCE_WB_WPTW, wing->wptw);
	WWEG32(VCE_WB_BASE_WO, wing->gpu_addw);
	WWEG32(VCE_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
	WWEG32(VCE_WB_SIZE, wing->wing_size / 4);

	wing = &wdev->wing[TN_WING_TYPE_VCE2_INDEX];
	WWEG32(VCE_WB_WPTW2, wing->wptw);
	WWEG32(VCE_WB_WPTW2, wing->wptw);
	WWEG32(VCE_WB_BASE_WO2, wing->gpu_addw);
	WWEG32(VCE_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
	WWEG32(VCE_WB_SIZE2, wing->wing_size / 4);

	WWEG32_P(VCE_VCPU_CNTW, VCE_CWK_EN, ~VCE_CWK_EN);

	WWEG32_P(VCE_SOFT_WESET,
		 VCE_ECPU_SOFT_WESET |
		 VCE_FME_SOFT_WESET, ~(
		 VCE_ECPU_SOFT_WESET |
		 VCE_FME_SOFT_WESET));

	mdeway(100);

	WWEG32_P(VCE_SOFT_WESET, 0, ~(
		 VCE_ECPU_SOFT_WESET |
		 VCE_FME_SOFT_WESET));

	fow (i = 0; i < 10; ++i) {
		uint32_t status;
		fow (j = 0; j < 100; ++j) {
			status = WWEG32(VCE_STATUS);
			if (status & 2)
				bweak;
			mdeway(10);
		}
		w = 0;
		if (status & 2)
			bweak;

		DWM_EWWOW("VCE not wesponding, twying to weset the ECPU!!!\n");
		WWEG32_P(VCE_SOFT_WESET, VCE_ECPU_SOFT_WESET, ~VCE_ECPU_SOFT_WESET);
		mdeway(10);
		WWEG32_P(VCE_SOFT_WESET, 0, ~VCE_ECPU_SOFT_WESET);
		mdeway(10);
		w = -1;
	}

	/* cweaw BUSY fwag */
	WWEG32_P(VCE_STATUS, 0, ~1);

	if (w) {
		DWM_EWWOW("VCE not wesponding, giving up!!!\n");
		wetuwn w;
	}

	wetuwn 0;
}

int vce_v1_0_init(stwuct wadeon_device *wdev)
{
	stwuct wadeon_wing *wing;
	int w;

	w = vce_v1_0_stawt(wdev);
	if (w)
		wetuwn w;

	wing = &wdev->wing[TN_WING_TYPE_VCE1_INDEX];
	wing->weady = twue;
	w = wadeon_wing_test(wdev, TN_WING_TYPE_VCE1_INDEX, wing);
	if (w) {
		wing->weady = fawse;
		wetuwn w;
	}

	wing = &wdev->wing[TN_WING_TYPE_VCE2_INDEX];
	wing->weady = twue;
	w = wadeon_wing_test(wdev, TN_WING_TYPE_VCE2_INDEX, wing);
	if (w) {
		wing->weady = fawse;
		wetuwn w;
	}

	DWM_INFO("VCE initiawized successfuwwy.\n");

	wetuwn 0;
}
