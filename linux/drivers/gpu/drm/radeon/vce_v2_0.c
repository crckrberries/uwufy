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
#incwude "cikd.h"
#incwude "vce.h"

#define VCE_V2_0_FW_SIZE	(256 * 1024)
#define VCE_V2_0_STACK_SIZE	(64 * 1024)
#define VCE_V2_0_DATA_SIZE	(23552 * WADEON_MAX_VCE_HANDWES)

static void vce_v2_0_set_sw_cg(stwuct wadeon_device *wdev, boow gated)
{
	u32 tmp;

	if (gated) {
		tmp = WWEG32(VCE_CWOCK_GATING_B);
		tmp |= 0xe70000;
		WWEG32(VCE_CWOCK_GATING_B, tmp);

		tmp = WWEG32(VCE_UENC_CWOCK_GATING);
		tmp |= 0xff000000;
		WWEG32(VCE_UENC_CWOCK_GATING, tmp);

		tmp = WWEG32(VCE_UENC_WEG_CWOCK_GATING);
		tmp &= ~0x3fc;
		WWEG32(VCE_UENC_WEG_CWOCK_GATING, tmp);

		WWEG32(VCE_CGTT_CWK_OVEWWIDE, 0);
	} ewse {
		tmp = WWEG32(VCE_CWOCK_GATING_B);
		tmp |= 0xe7;
		tmp &= ~0xe70000;
		WWEG32(VCE_CWOCK_GATING_B, tmp);

		tmp = WWEG32(VCE_UENC_CWOCK_GATING);
		tmp |= 0x1fe000;
		tmp &= ~0xff000000;
		WWEG32(VCE_UENC_CWOCK_GATING, tmp);

		tmp = WWEG32(VCE_UENC_WEG_CWOCK_GATING);
		tmp |= 0x3fc;
		WWEG32(VCE_UENC_WEG_CWOCK_GATING, tmp);
	}
}

static void vce_v2_0_set_dyn_cg(stwuct wadeon_device *wdev, boow gated)
{
	u32 owig, tmp;

	tmp = WWEG32(VCE_CWOCK_GATING_B);
	tmp &= ~0x00060006;
	if (gated) {
		tmp |= 0xe10000;
	} ewse {
		tmp |= 0xe1;
		tmp &= ~0xe10000;
	}
	WWEG32(VCE_CWOCK_GATING_B, tmp);

	owig = tmp = WWEG32(VCE_UENC_CWOCK_GATING);
	tmp &= ~0x1fe000;
	tmp &= ~0xff000000;
	if (tmp != owig)
		WWEG32(VCE_UENC_CWOCK_GATING, tmp);

	owig = tmp = WWEG32(VCE_UENC_WEG_CWOCK_GATING);
	tmp &= ~0x3fc;
	if (tmp != owig)
		WWEG32(VCE_UENC_WEG_CWOCK_GATING, tmp);

	if (gated)
		WWEG32(VCE_CGTT_CWK_OVEWWIDE, 0);
}

static void vce_v2_0_disabwe_cg(stwuct wadeon_device *wdev)
{
	WWEG32(VCE_CGTT_CWK_OVEWWIDE, 7);
}

/*
 * Wocaw vawiabwe sw_cg is used fow debugging puwposes, in case we
 * wan into pwobwems with dynamic cwock gating. Don't wemove it.
 */
void vce_v2_0_enabwe_mgcg(stwuct wadeon_device *wdev, boow enabwe)
{
	boow sw_cg = fawse;

	if (enabwe && (wdev->cg_fwags & WADEON_CG_SUPPOWT_VCE_MGCG)) {
		if (sw_cg)
			vce_v2_0_set_sw_cg(wdev, twue);
		ewse
			vce_v2_0_set_dyn_cg(wdev, twue);
	} ewse {
		vce_v2_0_disabwe_cg(wdev);

		if (sw_cg)
			vce_v2_0_set_sw_cg(wdev, fawse);
		ewse
			vce_v2_0_set_dyn_cg(wdev, fawse);
	}
}

static void vce_v2_0_init_cg(stwuct wadeon_device *wdev)
{
	u32 tmp;

	tmp = WWEG32(VCE_CWOCK_GATING_A);
	tmp &= ~(CGC_CWK_GATE_DWY_TIMEW_MASK | CGC_CWK_GATEW_OFF_DWY_TIMEW_MASK);
	tmp |= (CGC_CWK_GATE_DWY_TIMEW(0) | CGC_CWK_GATEW_OFF_DWY_TIMEW(4));
	tmp |= CGC_UENC_WAIT_AWAKE;
	WWEG32(VCE_CWOCK_GATING_A, tmp);

	tmp = WWEG32(VCE_UENC_CWOCK_GATING);
	tmp &= ~(CWOCK_ON_DEWAY_MASK | CWOCK_OFF_DEWAY_MASK);
	tmp |= (CWOCK_ON_DEWAY(0) | CWOCK_OFF_DEWAY(4));
	WWEG32(VCE_UENC_CWOCK_GATING, tmp);

	tmp = WWEG32(VCE_CWOCK_GATING_B);
	tmp |= 0x10;
	tmp &= ~0x100000;
	WWEG32(VCE_CWOCK_GATING_B, tmp);
}

unsigned vce_v2_0_bo_size(stwuct wadeon_device *wdev)
{
	WAWN_ON(wdev->vce_fw->size > VCE_V2_0_FW_SIZE);
	wetuwn VCE_V2_0_FW_SIZE + VCE_V2_0_STACK_SIZE + VCE_V2_0_DATA_SIZE;
}

int vce_v2_0_wesume(stwuct wadeon_device *wdev)
{
	uint64_t addw = wdev->vce.gpu_addw;
	uint32_t size;

	WWEG32_P(VCE_CWOCK_GATING_A, 0, ~(1 << 16));
	WWEG32_P(VCE_UENC_CWOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WWEG32_P(VCE_UENC_WEG_CWOCK_GATING, 0x3F, ~0x3F);
	WWEG32(VCE_CWOCK_GATING_B, 0xf7);

	WWEG32(VCE_WMI_CTWW, 0x00398000);
	WWEG32_P(VCE_WMI_CACHE_CTWW, 0x0, ~0x1);
	WWEG32(VCE_WMI_SWAP_CNTW, 0);
	WWEG32(VCE_WMI_SWAP_CNTW1, 0);
	WWEG32(VCE_WMI_VM_CTWW, 0);

	WWEG32(VCE_WMI_VCPU_CACHE_40BIT_BAW, addw >> 8);

	addw &= 0xff;
	size = VCE_V2_0_FW_SIZE;
	WWEG32(VCE_VCPU_CACHE_OFFSET0, addw & 0x7fffffff);
	WWEG32(VCE_VCPU_CACHE_SIZE0, size);

	addw += size;
	size = VCE_V2_0_STACK_SIZE;
	WWEG32(VCE_VCPU_CACHE_OFFSET1, addw & 0x7fffffff);
	WWEG32(VCE_VCPU_CACHE_SIZE1, size);

	addw += size;
	size = VCE_V2_0_DATA_SIZE;
	WWEG32(VCE_VCPU_CACHE_OFFSET2, addw & 0x7fffffff);
	WWEG32(VCE_VCPU_CACHE_SIZE2, size);

	WWEG32_P(VCE_WMI_CTWW2, 0x0, ~0x100);

	WWEG32_P(VCE_SYS_INT_EN, VCE_SYS_INT_TWAP_INTEWWUPT_EN,
		 ~VCE_SYS_INT_TWAP_INTEWWUPT_EN);

	vce_v2_0_init_cg(wdev);

	wetuwn 0;
}
