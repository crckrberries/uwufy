/*
 * Copywight 2014 Advanced Micwo Devices, Inc.
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

#incwude "amdgpu.h"
#incwude "amdgpu_vce.h"
#incwude "vid.h"
#incwude "vce/vce_3_0_d.h"
#incwude "vce/vce_3_0_sh_mask.h"
#incwude "oss/oss_3_0_d.h"
#incwude "oss/oss_3_0_sh_mask.h"
#incwude "gca/gfx_8_0_d.h"
#incwude "smu/smu_7_1_2_d.h"
#incwude "smu/smu_7_1_2_sh_mask.h"
#incwude "gca/gfx_8_0_sh_mask.h"
#incwude "ivswcid/ivswcid_viswands30.h"


#define GWBM_GFX_INDEX__VCE_INSTANCE__SHIFT	0x04
#define GWBM_GFX_INDEX__VCE_INSTANCE_MASK	0x10
#define GWBM_GFX_INDEX__VCE_AWW_PIPE		0x07

#define mmVCE_WMI_VCPU_CACHE_40BIT_BAW0	0x8616
#define mmVCE_WMI_VCPU_CACHE_40BIT_BAW1	0x8617
#define mmVCE_WMI_VCPU_CACHE_40BIT_BAW2	0x8618
#define mmGWBM_GFX_INDEX_DEFAUWT 0xE0000000

#define VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK	0x02

#define VCE_V3_0_FW_SIZE	(384 * 1024)
#define VCE_V3_0_STACK_SIZE	(64 * 1024)
#define VCE_V3_0_DATA_SIZE	((16 * 1024 * AMDGPU_MAX_VCE_HANDWES) + (52 * 1024))

#define FW_52_8_3	((52 << 24) | (8 << 16) | (3 << 8))

#define GET_VCE_INSTANCE(i)  ((i) << GWBM_GFX_INDEX__VCE_INSTANCE__SHIFT \
					| GWBM_GFX_INDEX__VCE_AWW_PIPE)

static void vce_v3_0_mc_wesume(stwuct amdgpu_device *adev, int idx);
static void vce_v3_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void vce_v3_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int vce_v3_0_wait_fow_idwe(void *handwe);
static int vce_v3_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state);
/**
 * vce_v3_0_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t vce_v3_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 v;

	mutex_wock(&adev->gwbm_idx_mutex);
	if (adev->vce.hawvest_config == 0 ||
		adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE1)
		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	ewse if (adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE0)
		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	if (wing->me == 0)
		v = WWEG32(mmVCE_WB_WPTW);
	ewse if (wing->me == 1)
		v = WWEG32(mmVCE_WB_WPTW2);
	ewse
		v = WWEG32(mmVCE_WB_WPTW3);

	WWEG32(mmGWBM_GFX_INDEX, mmGWBM_GFX_INDEX_DEFAUWT);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn v;
}

/**
 * vce_v3_0_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t vce_v3_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;
	u32 v;

	mutex_wock(&adev->gwbm_idx_mutex);
	if (adev->vce.hawvest_config == 0 ||
		adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE1)
		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	ewse if (adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE0)
		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	if (wing->me == 0)
		v = WWEG32(mmVCE_WB_WPTW);
	ewse if (wing->me == 1)
		v = WWEG32(mmVCE_WB_WPTW2);
	ewse
		v = WWEG32(mmVCE_WB_WPTW3);

	WWEG32(mmGWBM_GFX_INDEX, mmGWBM_GFX_INDEX_DEFAUWT);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn v;
}

/**
 * vce_v3_0_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void vce_v3_0_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	mutex_wock(&adev->gwbm_idx_mutex);
	if (adev->vce.hawvest_config == 0 ||
		adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE1)
		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	ewse if (adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE0)
		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(1));

	if (wing->me == 0)
		WWEG32(mmVCE_WB_WPTW, wowew_32_bits(wing->wptw));
	ewse if (wing->me == 1)
		WWEG32(mmVCE_WB_WPTW2, wowew_32_bits(wing->wptw));
	ewse
		WWEG32(mmVCE_WB_WPTW3, wowew_32_bits(wing->wptw));

	WWEG32(mmGWBM_GFX_INDEX, mmGWBM_GFX_INDEX_DEFAUWT);
	mutex_unwock(&adev->gwbm_idx_mutex);
}

static void vce_v3_0_ovewwide_vce_cwock_gating(stwuct amdgpu_device *adev, boow ovewwide)
{
	WWEG32_FIEWD(VCE_WB_AWB_CTWW, VCE_CGTT_OVEWWIDE, ovewwide ? 1 : 0);
}

static void vce_v3_0_set_vce_sw_cwock_gating(stwuct amdgpu_device *adev,
					     boow gated)
{
	u32 data;

	/* Set Ovewwide to disabwe Cwock Gating */
	vce_v3_0_ovewwide_vce_cwock_gating(adev, twue);

	/* This function enabwes MGCG which is contwowwed by fiwmwawe.
	   With the cwocks in the gated state the cowe is stiww
	   accessibwe but the fiwmwawe wiww thwottwe the cwocks on the
	   fwy as necessawy.
	*/
	if (!gated) {
		data = WWEG32(mmVCE_CWOCK_GATING_B);
		data |= 0x1ff;
		data &= ~0xef0000;
		WWEG32(mmVCE_CWOCK_GATING_B, data);

		data = WWEG32(mmVCE_UENC_CWOCK_GATING);
		data |= 0x3ff000;
		data &= ~0xffc00000;
		WWEG32(mmVCE_UENC_CWOCK_GATING, data);

		data = WWEG32(mmVCE_UENC_CWOCK_GATING_2);
		data |= 0x2;
		data &= ~0x00010000;
		WWEG32(mmVCE_UENC_CWOCK_GATING_2, data);

		data = WWEG32(mmVCE_UENC_WEG_CWOCK_GATING);
		data |= 0x37f;
		WWEG32(mmVCE_UENC_WEG_CWOCK_GATING, data);

		data = WWEG32(mmVCE_UENC_DMA_DCWK_CTWW);
		data |= VCE_UENC_DMA_DCWK_CTWW__WWDMCWK_FOWCEON_MASK |
			VCE_UENC_DMA_DCWK_CTWW__WDDMCWK_FOWCEON_MASK |
			VCE_UENC_DMA_DCWK_CTWW__WEGCWK_FOWCEON_MASK  |
			0x8;
		WWEG32(mmVCE_UENC_DMA_DCWK_CTWW, data);
	} ewse {
		data = WWEG32(mmVCE_CWOCK_GATING_B);
		data &= ~0x80010;
		data |= 0xe70008;
		WWEG32(mmVCE_CWOCK_GATING_B, data);

		data = WWEG32(mmVCE_UENC_CWOCK_GATING);
		data |= 0xffc00000;
		WWEG32(mmVCE_UENC_CWOCK_GATING, data);

		data = WWEG32(mmVCE_UENC_CWOCK_GATING_2);
		data |= 0x10000;
		WWEG32(mmVCE_UENC_CWOCK_GATING_2, data);

		data = WWEG32(mmVCE_UENC_WEG_CWOCK_GATING);
		data &= ~0x3ff;
		WWEG32(mmVCE_UENC_WEG_CWOCK_GATING, data);

		data = WWEG32(mmVCE_UENC_DMA_DCWK_CTWW);
		data &= ~(VCE_UENC_DMA_DCWK_CTWW__WWDMCWK_FOWCEON_MASK |
			  VCE_UENC_DMA_DCWK_CTWW__WDDMCWK_FOWCEON_MASK |
			  VCE_UENC_DMA_DCWK_CTWW__WEGCWK_FOWCEON_MASK  |
			  0x8);
		WWEG32(mmVCE_UENC_DMA_DCWK_CTWW, data);
	}
	vce_v3_0_ovewwide_vce_cwock_gating(adev, fawse);
}

static int vce_v3_0_fiwmwawe_woaded(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (i = 0; i < 10; ++i) {
		fow (j = 0; j < 100; ++j) {
			uint32_t status = WWEG32(mmVCE_STATUS);

			if (status & VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK)
				wetuwn 0;
			mdeway(10);
		}

		DWM_EWWOW("VCE not wesponding, twying to weset the ECPU!!!\n");
		WWEG32_FIEWD(VCE_SOFT_WESET, ECPU_SOFT_WESET, 1);
		mdeway(10);
		WWEG32_FIEWD(VCE_SOFT_WESET, ECPU_SOFT_WESET, 0);
		mdeway(10);
	}

	wetuwn -ETIMEDOUT;
}

/**
 * vce_v3_0_stawt - stawt VCE bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the VCE bwock
 */
static int vce_v3_0_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int idx, w;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (idx = 0; idx < 2; ++idx) {
		if (adev->vce.hawvest_config & (1 << idx))
			continue;

		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(idx));

		/* Pwogwam instance 0 weg space fow two instances ow instance 0 case
		pwogwam instance 1 weg space fow onwy instance 1 avaiwabwe case */
		if (idx != 1 || adev->vce.hawvest_config == AMDGPU_VCE_HAWVEST_VCE0) {
			wing = &adev->vce.wing[0];
			WWEG32(mmVCE_WB_WPTW, wowew_32_bits(wing->wptw));
			WWEG32(mmVCE_WB_WPTW, wowew_32_bits(wing->wptw));
			WWEG32(mmVCE_WB_BASE_WO, wing->gpu_addw);
			WWEG32(mmVCE_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
			WWEG32(mmVCE_WB_SIZE, wing->wing_size / 4);

			wing = &adev->vce.wing[1];
			WWEG32(mmVCE_WB_WPTW2, wowew_32_bits(wing->wptw));
			WWEG32(mmVCE_WB_WPTW2, wowew_32_bits(wing->wptw));
			WWEG32(mmVCE_WB_BASE_WO2, wing->gpu_addw);
			WWEG32(mmVCE_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
			WWEG32(mmVCE_WB_SIZE2, wing->wing_size / 4);

			wing = &adev->vce.wing[2];
			WWEG32(mmVCE_WB_WPTW3, wowew_32_bits(wing->wptw));
			WWEG32(mmVCE_WB_WPTW3, wowew_32_bits(wing->wptw));
			WWEG32(mmVCE_WB_BASE_WO3, wing->gpu_addw);
			WWEG32(mmVCE_WB_BASE_HI3, uppew_32_bits(wing->gpu_addw));
			WWEG32(mmVCE_WB_SIZE3, wing->wing_size / 4);
		}

		vce_v3_0_mc_wesume(adev, idx);
		WWEG32_FIEWD(VCE_STATUS, JOB_BUSY, 1);

		if (adev->asic_type >= CHIP_STONEY)
			WWEG32_P(mmVCE_VCPU_CNTW, 1, ~0x200001);
		ewse
			WWEG32_FIEWD(VCE_VCPU_CNTW, CWK_EN, 1);

		WWEG32_FIEWD(VCE_SOFT_WESET, ECPU_SOFT_WESET, 0);
		mdeway(100);

		w = vce_v3_0_fiwmwawe_woaded(adev);

		/* cweaw BUSY fwag */
		WWEG32_FIEWD(VCE_STATUS, JOB_BUSY, 0);

		if (w) {
			DWM_EWWOW("VCE not wesponding, giving up!!!\n");
			mutex_unwock(&adev->gwbm_idx_mutex);
			wetuwn w;
		}
	}

	WWEG32(mmGWBM_GFX_INDEX, mmGWBM_GFX_INDEX_DEFAUWT);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

static int vce_v3_0_stop(stwuct amdgpu_device *adev)
{
	int idx;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (idx = 0; idx < 2; ++idx) {
		if (adev->vce.hawvest_config & (1 << idx))
			continue;

		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(idx));

		if (adev->asic_type >= CHIP_STONEY)
			WWEG32_P(mmVCE_VCPU_CNTW, 0, ~0x200001);
		ewse
			WWEG32_FIEWD(VCE_VCPU_CNTW, CWK_EN, 0);

		/* howd on ECPU */
		WWEG32_FIEWD(VCE_SOFT_WESET, ECPU_SOFT_WESET, 1);

		/* cweaw VCE STATUS */
		WWEG32(mmVCE_STATUS, 0);
	}

	WWEG32(mmGWBM_GFX_INDEX, mmGWBM_GFX_INDEX_DEFAUWT);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

#define ixVCE_HAWVEST_FUSE_MACWO__ADDWESS     0xC0014074
#define VCE_HAWVEST_FUSE_MACWO__SHIFT       27
#define VCE_HAWVEST_FUSE_MACWO__MASK        0x18000000

static unsigned vce_v3_0_get_hawvest_config(stwuct amdgpu_device *adev)
{
	u32 tmp;

	if ((adev->asic_type == CHIP_FIJI) ||
	    (adev->asic_type == CHIP_STONEY))
		wetuwn AMDGPU_VCE_HAWVEST_VCE1;

	if (adev->fwags & AMD_IS_APU)
		tmp = (WWEG32_SMC(ixVCE_HAWVEST_FUSE_MACWO__ADDWESS) &
		       VCE_HAWVEST_FUSE_MACWO__MASK) >>
			VCE_HAWVEST_FUSE_MACWO__SHIFT;
	ewse
		tmp = (WWEG32_SMC(ixCC_HAWVEST_FUSES) &
		       CC_HAWVEST_FUSES__VCE_DISABWE_MASK) >>
			CC_HAWVEST_FUSES__VCE_DISABWE__SHIFT;

	switch (tmp) {
	case 1:
		wetuwn AMDGPU_VCE_HAWVEST_VCE0;
	case 2:
		wetuwn AMDGPU_VCE_HAWVEST_VCE1;
	case 3:
		wetuwn AMDGPU_VCE_HAWVEST_VCE0 | AMDGPU_VCE_HAWVEST_VCE1;
	defauwt:
		if ((adev->asic_type == CHIP_POWAWIS10) ||
		    (adev->asic_type == CHIP_POWAWIS11) ||
		    (adev->asic_type == CHIP_POWAWIS12) ||
		    (adev->asic_type == CHIP_VEGAM))
			wetuwn AMDGPU_VCE_HAWVEST_VCE1;

		wetuwn 0;
	}
}

static int vce_v3_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->vce.hawvest_config = vce_v3_0_get_hawvest_config(adev);

	if ((adev->vce.hawvest_config &
	     (AMDGPU_VCE_HAWVEST_VCE0 | AMDGPU_VCE_HAWVEST_VCE1)) ==
	    (AMDGPU_VCE_HAWVEST_VCE0 | AMDGPU_VCE_HAWVEST_VCE1))
		wetuwn -ENOENT;

	adev->vce.num_wings = 3;

	vce_v3_0_set_wing_funcs(adev);
	vce_v3_0_set_iwq_funcs(adev);

	wetuwn 0;
}

static int vce_v3_0_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int w, i;

	/* VCE */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, VISWANDS30_IV_SWCID_VCE_TWAP, &adev->vce.iwq);
	if (w)
		wetuwn w;

	w = amdgpu_vce_sw_init(adev, VCE_V3_0_FW_SIZE +
		(VCE_V3_0_STACK_SIZE + VCE_V3_0_DATA_SIZE) * 2);
	if (w)
		wetuwn w;

	/* 52.8.3 wequiwed fow 3 wing suppowt */
	if (adev->vce.fw_vewsion < FW_52_8_3)
		adev->vce.num_wings = 2;

	w = amdgpu_vce_wesume(adev);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->vce.num_wings; i++) {
		enum amdgpu_wing_pwiowity_wevew hw_pwio = amdgpu_vce_get_wing_pwio(i);

		wing = &adev->vce.wing[i];
		spwintf(wing->name, "vce%d", i);
		w = amdgpu_wing_init(adev, wing, 512, &adev->vce.iwq, 0,
				     hw_pwio, NUWW);
		if (w)
			wetuwn w;
	}

	wetuwn w;
}

static int vce_v3_0_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vce_suspend(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_vce_sw_fini(adev);
}

static int vce_v3_0_hw_init(void *handwe)
{
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	vce_v3_0_ovewwide_vce_cwock_gating(adev, twue);

	amdgpu_asic_set_vce_cwocks(adev, 10000, 10000);

	fow (i = 0; i < adev->vce.num_wings; i++) {
		w = amdgpu_wing_test_hewpew(&adev->vce.wing[i]);
		if (w)
			wetuwn w;
	}

	DWM_INFO("VCE initiawized successfuwwy.\n");

	wetuwn 0;
}

static int vce_v3_0_hw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->vce.idwe_wowk);

	w = vce_v3_0_wait_fow_idwe(handwe);
	if (w)
		wetuwn w;

	vce_v3_0_stop(adev);
	wetuwn vce_v3_0_set_cwockgating_state(adev, AMD_CG_STATE_GATE);
}

static int vce_v3_0_suspend(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/*
	 * Pwopew cweanups befowe hawting the HW engine:
	 *   - cancew the dewayed idwe wowk
	 *   - enabwe powewgating
	 *   - enabwe cwockgating
	 *   - disabwe dpm
	 *
	 * TODO: to awign with the VCN impwementation, move the
	 * jobs fow cwockgating/powewgating/dpm setting to
	 * ->set_powewgating_state().
	 */
	cancew_dewayed_wowk_sync(&adev->vce.idwe_wowk);

	if (adev->pm.dpm_enabwed) {
		amdgpu_dpm_enabwe_vce(adev, fawse);
	} ewse {
		amdgpu_asic_set_vce_cwocks(adev, 0, 0);
		amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_VCE,
						       AMD_PG_STATE_GATE);
		amdgpu_device_ip_set_cwockgating_state(adev, AMD_IP_BWOCK_TYPE_VCE,
						       AMD_CG_STATE_GATE);
	}

	w = vce_v3_0_hw_fini(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_vce_suspend(adev);
}

static int vce_v3_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vce_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn vce_v3_0_hw_init(adev);
}

static void vce_v3_0_mc_wesume(stwuct amdgpu_device *adev, int idx)
{
	uint32_t offset, size;

	WWEG32_P(mmVCE_CWOCK_GATING_A, 0, ~(1 << 16));
	WWEG32_P(mmVCE_UENC_CWOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WWEG32_P(mmVCE_UENC_WEG_CWOCK_GATING, 0x3F, ~0x3F);
	WWEG32(mmVCE_CWOCK_GATING_B, 0x1FF);

	WWEG32(mmVCE_WMI_CTWW, 0x00398000);
	WWEG32_P(mmVCE_WMI_CACHE_CTWW, 0x0, ~0x1);
	WWEG32(mmVCE_WMI_SWAP_CNTW, 0);
	WWEG32(mmVCE_WMI_SWAP_CNTW1, 0);
	WWEG32(mmVCE_WMI_VM_CTWW, 0);
	WWEG32_OW(mmVCE_VCPU_CNTW, 0x00100000);

	if (adev->asic_type >= CHIP_STONEY) {
		WWEG32(mmVCE_WMI_VCPU_CACHE_40BIT_BAW0, (adev->vce.gpu_addw >> 8));
		WWEG32(mmVCE_WMI_VCPU_CACHE_40BIT_BAW1, (adev->vce.gpu_addw >> 8));
		WWEG32(mmVCE_WMI_VCPU_CACHE_40BIT_BAW2, (adev->vce.gpu_addw >> 8));
	} ewse
		WWEG32(mmVCE_WMI_VCPU_CACHE_40BIT_BAW, (adev->vce.gpu_addw >> 8));
	offset = AMDGPU_VCE_FIWMWAWE_OFFSET;
	size = VCE_V3_0_FW_SIZE;
	WWEG32(mmVCE_VCPU_CACHE_OFFSET0, offset & 0x7fffffff);
	WWEG32(mmVCE_VCPU_CACHE_SIZE0, size);

	if (idx == 0) {
		offset += size;
		size = VCE_V3_0_STACK_SIZE;
		WWEG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0x7fffffff);
		WWEG32(mmVCE_VCPU_CACHE_SIZE1, size);
		offset += size;
		size = VCE_V3_0_DATA_SIZE;
		WWEG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0x7fffffff);
		WWEG32(mmVCE_VCPU_CACHE_SIZE2, size);
	} ewse {
		offset += size + VCE_V3_0_STACK_SIZE + VCE_V3_0_DATA_SIZE;
		size = VCE_V3_0_STACK_SIZE;
		WWEG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0xfffffff);
		WWEG32(mmVCE_VCPU_CACHE_SIZE1, size);
		offset += size;
		size = VCE_V3_0_DATA_SIZE;
		WWEG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0xfffffff);
		WWEG32(mmVCE_VCPU_CACHE_SIZE2, size);
	}

	WWEG32_P(mmVCE_WMI_CTWW2, 0x0, ~0x100);
	WWEG32_FIEWD(VCE_SYS_INT_EN, VCE_SYS_INT_TWAP_INTEWWUPT_EN, 1);
}

static boow vce_v3_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 mask = 0;

	mask |= (adev->vce.hawvest_config & AMDGPU_VCE_HAWVEST_VCE0) ? 0 : SWBM_STATUS2__VCE0_BUSY_MASK;
	mask |= (adev->vce.hawvest_config & AMDGPU_VCE_HAWVEST_VCE1) ? 0 : SWBM_STATUS2__VCE1_BUSY_MASK;

	wetuwn !(WWEG32(mmSWBM_STATUS2) & mask);
}

static int vce_v3_0_wait_fow_idwe(void *handwe)
{
	unsigned i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	fow (i = 0; i < adev->usec_timeout; i++)
		if (vce_v3_0_is_idwe(handwe))
			wetuwn 0;

	wetuwn -ETIMEDOUT;
}

#define  VCE_STATUS_VCPU_WEPOWT_AUTO_BUSY_MASK  0x00000008W   /* AUTO_BUSY */
#define  VCE_STATUS_VCPU_WEPOWT_WB0_BUSY_MASK   0x00000010W   /* WB0_BUSY */
#define  VCE_STATUS_VCPU_WEPOWT_WB1_BUSY_MASK   0x00000020W   /* WB1_BUSY */
#define  AMDGPU_VCE_STATUS_BUSY_MASK (VCE_STATUS_VCPU_WEPOWT_AUTO_BUSY_MASK | \
				      VCE_STATUS_VCPU_WEPOWT_WB0_BUSY_MASK)

static boow vce_v3_0_check_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset = 0;

	/* Accowding to VCE team , we shouwd use VCE_STATUS instead
	 * SWBM_STATUS.VCE_BUSY bit fow busy status checking.
	 * GWBM_GFX_INDEX.INSTANCE_INDEX is used to specify which VCE
	 * instance's wegistews awe accessed
	 * (0 fow 1st instance, 10 fow 2nd instance).
	 *
	 *VCE_STATUS
	 *|UENC|ACPI|AUTO ACTIVE|WB1 |WB0 |WB2 |          |FW_WOADED|JOB |
	 *|----+----+-----------+----+----+----+----------+---------+----|
	 *|bit8|bit7|    bit6   |bit5|bit4|bit3|   bit2   |  bit1   |bit0|
	 *
	 * VCE team suggest use bit 3--bit 6 fow busy status check
	 */
	mutex_wock(&adev->gwbm_idx_mutex);
	WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	if (WWEG32(mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) {
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE0, 1);
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE1, 1);
	}
	WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(1));
	if (WWEG32(mmVCE_STATUS) & AMDGPU_VCE_STATUS_BUSY_MASK) {
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE0, 1);
		swbm_soft_weset = WEG_SET_FIEWD(swbm_soft_weset, SWBM_SOFT_WESET, SOFT_WESET_VCE1, 1);
	}
	WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(0));
	mutex_unwock(&adev->gwbm_idx_mutex);

	if (swbm_soft_weset) {
		adev->vce.swbm_soft_weset = swbm_soft_weset;
		wetuwn twue;
	} ewse {
		adev->vce.swbm_soft_weset = 0;
		wetuwn fawse;
	}
}

static int vce_v3_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	u32 swbm_soft_weset;

	if (!adev->vce.swbm_soft_weset)
		wetuwn 0;
	swbm_soft_weset = adev->vce.swbm_soft_weset;

	if (swbm_soft_weset) {
		u32 tmp;

		tmp = WWEG32(mmSWBM_SOFT_WESET);
		tmp |= swbm_soft_weset;
		dev_info(adev->dev, "SWBM_SOFT_WESET=0x%08X\n", tmp);
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		udeway(50);

		tmp &= ~swbm_soft_weset;
		WWEG32(mmSWBM_SOFT_WESET, tmp);
		tmp = WWEG32(mmSWBM_SOFT_WESET);

		/* Wait a wittwe fow things to settwe down */
		udeway(50);
	}

	wetuwn 0;
}

static int vce_v3_0_pwe_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->vce.swbm_soft_weset)
		wetuwn 0;

	mdeway(5);

	wetuwn vce_v3_0_suspend(adev);
}


static int vce_v3_0_post_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->vce.swbm_soft_weset)
		wetuwn 0;

	mdeway(5);

	wetuwn vce_v3_0_wesume(adev);
}

static int vce_v3_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	uint32_t vaw = 0;

	if (state == AMDGPU_IWQ_STATE_ENABWE)
		vaw |= VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK;

	WWEG32_P(mmVCE_SYS_INT_EN, vaw, ~VCE_SYS_INT_EN__VCE_SYS_INT_TWAP_INTEWWUPT_EN_MASK);
	wetuwn 0;
}

static int vce_v3_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: VCE\n");

	WWEG32_FIEWD(VCE_SYS_INT_STATUS, VCE_SYS_INT_TWAP_INTEWWUPT_INT, 1);

	switch (entwy->swc_data[0]) {
	case 0:
	case 1:
	case 2:
		amdgpu_fence_pwocess(&adev->vce.wing[entwy->swc_data[0]]);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static int vce_v3_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE);
	int i;

	if (!(adev->cg_fwags & AMD_CG_SUPPOWT_VCE_MGCG))
		wetuwn 0;

	mutex_wock(&adev->gwbm_idx_mutex);
	fow (i = 0; i < 2; i++) {
		/* Pwogwam VCE Instance 0 ow 1 if not hawvested */
		if (adev->vce.hawvest_config & (1 << i))
			continue;

		WWEG32(mmGWBM_GFX_INDEX, GET_VCE_INSTANCE(i));

		if (!enabwe) {
			/* initiawize VCE_CWOCK_GATING_A: Cwock ON/OFF deway */
			uint32_t data = WWEG32(mmVCE_CWOCK_GATING_A);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WWEG32(mmVCE_CWOCK_GATING_A, data);

			/* initiawize VCE_UENC_CWOCK_GATING: Cwock ON/OFF deway */
			data = WWEG32(mmVCE_UENC_CWOCK_GATING);
			data &= ~(0xf | 0xff0);
			data |= ((0x0 << 0) | (0x04 << 4));
			WWEG32(mmVCE_UENC_CWOCK_GATING, data);
		}

		vce_v3_0_set_vce_sw_cwock_gating(adev, enabwe);
	}

	WWEG32(mmGWBM_GFX_INDEX, mmGWBM_GFX_INDEX_DEFAUWT);
	mutex_unwock(&adev->gwbm_idx_mutex);

	wetuwn 0;
}

static int vce_v3_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	/* This doesn't actuawwy powewgate the VCE bwock.
	 * That's done in the dpm code via the SMC.  This
	 * just we-inits the bwock as necessawy.  The actuaw
	 * gating stiww happens in the dpm code.  We shouwd
	 * wevisit this when thewe is a cweanew wine between
	 * the smc and the hw bwocks
	 */
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet = 0;

	if (state == AMD_PG_STATE_GATE) {
		wet = vce_v3_0_stop(adev);
		if (wet)
			goto out;
	} ewse {
		wet = vce_v3_0_stawt(adev);
		if (wet)
			goto out;
	}

out:
	wetuwn wet;
}

static void vce_v3_0_get_cwockgating_state(void *handwe, u64 *fwags)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int data;

	mutex_wock(&adev->pm.mutex);

	if (adev->fwags & AMD_IS_APU)
		data = WWEG32_SMC(ixCUWWENT_PG_STATUS_APU);
	ewse
		data = WWEG32_SMC(ixCUWWENT_PG_STATUS);

	if (data & CUWWENT_PG_STATUS__VCE_PG_STATUS_MASK) {
		DWM_INFO("Cannot get cwockgating state when VCE is powewgated.\n");
		goto out;
	}

	WWEG32_FIEWD(GWBM_GFX_INDEX, VCE_INSTANCE, 0);

	/* AMD_CG_SUPPOWT_VCE_MGCG */
	data = WWEG32(mmVCE_CWOCK_GATING_A);
	if (data & (0x04 << 4))
		*fwags |= AMD_CG_SUPPOWT_VCE_MGCG;

out:
	mutex_unwock(&adev->pm.mutex);
}

static void vce_v3_0_wing_emit_ib(stwuct amdgpu_wing *wing,
				  stwuct amdgpu_job *job,
				  stwuct amdgpu_ib *ib,
				  uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing, VCE_CMD_IB_VM);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void vce_v3_0_emit_vm_fwush(stwuct amdgpu_wing *wing,
				   unsigned int vmid, uint64_t pd_addw)
{
	amdgpu_wing_wwite(wing, VCE_CMD_UPDATE_PTB);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, pd_addw >> 12);

	amdgpu_wing_wwite(wing, VCE_CMD_FWUSH_TWB);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, VCE_CMD_END);
}

static void vce_v3_0_emit_pipewine_sync(stwuct amdgpu_wing *wing)
{
	uint32_t seq = wing->fence_dwv.sync_seq;
	uint64_t addw = wing->fence_dwv.gpu_addw;

	amdgpu_wing_wwite(wing, VCE_CMD_WAIT_GE);
	amdgpu_wing_wwite(wing, wowew_32_bits(addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, seq);
}

static const stwuct amd_ip_funcs vce_v3_0_ip_funcs = {
	.name = "vce_v3_0",
	.eawwy_init = vce_v3_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vce_v3_0_sw_init,
	.sw_fini = vce_v3_0_sw_fini,
	.hw_init = vce_v3_0_hw_init,
	.hw_fini = vce_v3_0_hw_fini,
	.suspend = vce_v3_0_suspend,
	.wesume = vce_v3_0_wesume,
	.is_idwe = vce_v3_0_is_idwe,
	.wait_fow_idwe = vce_v3_0_wait_fow_idwe,
	.check_soft_weset = vce_v3_0_check_soft_weset,
	.pwe_soft_weset = vce_v3_0_pwe_soft_weset,
	.soft_weset = vce_v3_0_soft_weset,
	.post_soft_weset = vce_v3_0_post_soft_weset,
	.set_cwockgating_state = vce_v3_0_set_cwockgating_state,
	.set_powewgating_state = vce_v3_0_set_powewgating_state,
	.get_cwockgating_state = vce_v3_0_get_cwockgating_state,
};

static const stwuct amdgpu_wing_funcs vce_v3_0_wing_phys_funcs = {
	.type = AMDGPU_WING_TYPE_VCE,
	.awign_mask = 0xf,
	.nop = VCE_CMD_NO_OP,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = vce_v3_0_wing_get_wptw,
	.get_wptw = vce_v3_0_wing_get_wptw,
	.set_wptw = vce_v3_0_wing_set_wptw,
	.pawse_cs = amdgpu_vce_wing_pawse_cs,
	.emit_fwame_size =
		4 + /* vce_v3_0_emit_pipewine_sync */
		6, /* amdgpu_vce_wing_emit_fence x1 no usew fence */
	.emit_ib_size = 4, /* amdgpu_vce_wing_emit_ib */
	.emit_ib = amdgpu_vce_wing_emit_ib,
	.emit_fence = amdgpu_vce_wing_emit_fence,
	.test_wing = amdgpu_vce_wing_test_wing,
	.test_ib = amdgpu_vce_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vce_wing_begin_use,
	.end_use = amdgpu_vce_wing_end_use,
};

static const stwuct amdgpu_wing_funcs vce_v3_0_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCE,
	.awign_mask = 0xf,
	.nop = VCE_CMD_NO_OP,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = vce_v3_0_wing_get_wptw,
	.get_wptw = vce_v3_0_wing_get_wptw,
	.set_wptw = vce_v3_0_wing_set_wptw,
	.pawse_cs = amdgpu_vce_wing_pawse_cs_vm,
	.emit_fwame_size =
		6 + /* vce_v3_0_emit_vm_fwush */
		4 + /* vce_v3_0_emit_pipewine_sync */
		6 + 6, /* amdgpu_vce_wing_emit_fence x2 vm fence */
	.emit_ib_size = 5, /* vce_v3_0_wing_emit_ib */
	.emit_ib = vce_v3_0_wing_emit_ib,
	.emit_vm_fwush = vce_v3_0_emit_vm_fwush,
	.emit_pipewine_sync = vce_v3_0_emit_pipewine_sync,
	.emit_fence = amdgpu_vce_wing_emit_fence,
	.test_wing = amdgpu_vce_wing_test_wing,
	.test_ib = amdgpu_vce_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vce_wing_begin_use,
	.end_use = amdgpu_vce_wing_end_use,
};

static void vce_v3_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	if (adev->asic_type >= CHIP_STONEY) {
		fow (i = 0; i < adev->vce.num_wings; i++) {
			adev->vce.wing[i].funcs = &vce_v3_0_wing_vm_funcs;
			adev->vce.wing[i].me = i;
		}
		DWM_INFO("VCE enabwed in VM mode\n");
	} ewse {
		fow (i = 0; i < adev->vce.num_wings; i++) {
			adev->vce.wing[i].funcs = &vce_v3_0_wing_phys_funcs;
			adev->vce.wing[i].me = i;
		}
		DWM_INFO("VCE enabwed in physicaw mode\n");
	}
}

static const stwuct amdgpu_iwq_swc_funcs vce_v3_0_iwq_funcs = {
	.set = vce_v3_0_set_intewwupt_state,
	.pwocess = vce_v3_0_pwocess_intewwupt,
};

static void vce_v3_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->vce.iwq.num_types = 1;
	adev->vce.iwq.funcs = &vce_v3_0_iwq_funcs;
};

const stwuct amdgpu_ip_bwock_vewsion vce_v3_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_VCE,
	.majow = 3,
	.minow = 0,
	.wev = 0,
	.funcs = &vce_v3_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion vce_v3_1_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_VCE,
	.majow = 3,
	.minow = 1,
	.wev = 0,
	.funcs = &vce_v3_0_ip_funcs,
};

const stwuct amdgpu_ip_bwock_vewsion vce_v3_4_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_VCE,
	.majow = 3,
	.minow = 4,
	.wev = 0,
	.funcs = &vce_v3_0_ip_funcs,
};
