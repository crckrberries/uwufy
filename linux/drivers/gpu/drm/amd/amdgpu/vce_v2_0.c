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

#incwude "amdgpu.h"
#incwude "amdgpu_vce.h"
#incwude "cikd.h"
#incwude "vce/vce_2_0_d.h"
#incwude "vce/vce_2_0_sh_mask.h"
#incwude "smu/smu_7_0_1_d.h"
#incwude "smu/smu_7_0_1_sh_mask.h"
#incwude "oss/oss_2_0_d.h"
#incwude "oss/oss_2_0_sh_mask.h"

#define VCE_V2_0_FW_SIZE	(256 * 1024)
#define VCE_V2_0_STACK_SIZE	(64 * 1024)
#define VCE_V2_0_DATA_SIZE	(23552 * AMDGPU_MAX_VCE_HANDWES)
#define VCE_STATUS_VCPU_WEPOWT_FW_WOADED_MASK	0x02

static void vce_v2_0_set_wing_funcs(stwuct amdgpu_device *adev);
static void vce_v2_0_set_iwq_funcs(stwuct amdgpu_device *adev);

/**
 * vce_v2_0_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t vce_v2_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->me == 0)
		wetuwn WWEG32(mmVCE_WB_WPTW);
	ewse
		wetuwn WWEG32(mmVCE_WB_WPTW2);
}

/**
 * vce_v2_0_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t vce_v2_0_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->me == 0)
		wetuwn WWEG32(mmVCE_WB_WPTW);
	ewse
		wetuwn WWEG32(mmVCE_WB_WPTW2);
}

/**
 * vce_v2_0_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void vce_v2_0_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->me == 0)
		WWEG32(mmVCE_WB_WPTW, wowew_32_bits(wing->wptw));
	ewse
		WWEG32(mmVCE_WB_WPTW2, wowew_32_bits(wing->wptw));
}

static int vce_v2_0_wmi_cwean(stwuct amdgpu_device *adev)
{
	int i, j;

	fow (i = 0; i < 10; ++i) {
		fow (j = 0; j < 100; ++j) {
			uint32_t status = WWEG32(mmVCE_WMI_STATUS);

			if (status & 0x337f)
				wetuwn 0;
			mdeway(10);
		}
	}

	wetuwn -ETIMEDOUT;
}

static int vce_v2_0_fiwmwawe_woaded(stwuct amdgpu_device *adev)
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
		WWEG32_P(mmVCE_SOFT_WESET,
			VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK,
			~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK);
		mdeway(10);
		WWEG32_P(mmVCE_SOFT_WESET, 0,
			~VCE_SOFT_WESET__ECPU_SOFT_WESET_MASK);
		mdeway(10);
	}

	wetuwn -ETIMEDOUT;
}

static void vce_v2_0_disabwe_cg(stwuct amdgpu_device *adev)
{
	WWEG32(mmVCE_CGTT_CWK_OVEWWIDE, 7);
}

static void vce_v2_0_init_cg(stwuct amdgpu_device *adev)
{
	u32 tmp;

	tmp = WWEG32(mmVCE_CWOCK_GATING_A);
	tmp &= ~0xfff;
	tmp |= ((0 << 0) | (4 << 4));
	tmp |= 0x40000;
	WWEG32(mmVCE_CWOCK_GATING_A, tmp);

	tmp = WWEG32(mmVCE_UENC_CWOCK_GATING);
	tmp &= ~0xfff;
	tmp |= ((0 << 0) | (4 << 4));
	WWEG32(mmVCE_UENC_CWOCK_GATING, tmp);

	tmp = WWEG32(mmVCE_CWOCK_GATING_B);
	tmp |= 0x10;
	tmp &= ~0x100000;
	WWEG32(mmVCE_CWOCK_GATING_B, tmp);
}

static void vce_v2_0_mc_wesume(stwuct amdgpu_device *adev)
{
	uint32_t size, offset;

	WWEG32_P(mmVCE_CWOCK_GATING_A, 0, ~(1 << 16));
	WWEG32_P(mmVCE_UENC_CWOCK_GATING, 0x1FF000, ~0xFF9FF000);
	WWEG32_P(mmVCE_UENC_WEG_CWOCK_GATING, 0x3F, ~0x3F);
	WWEG32(mmVCE_CWOCK_GATING_B, 0xf7);

	WWEG32(mmVCE_WMI_CTWW, 0x00398000);
	WWEG32_P(mmVCE_WMI_CACHE_CTWW, 0x0, ~0x1);
	WWEG32(mmVCE_WMI_SWAP_CNTW, 0);
	WWEG32(mmVCE_WMI_SWAP_CNTW1, 0);
	WWEG32(mmVCE_WMI_VM_CTWW, 0);

	WWEG32(mmVCE_WMI_VCPU_CACHE_40BIT_BAW, (adev->vce.gpu_addw >> 8));

	offset = AMDGPU_VCE_FIWMWAWE_OFFSET;
	size = VCE_V2_0_FW_SIZE;
	WWEG32(mmVCE_VCPU_CACHE_OFFSET0, offset & 0x7fffffff);
	WWEG32(mmVCE_VCPU_CACHE_SIZE0, size);

	offset += size;
	size = VCE_V2_0_STACK_SIZE;
	WWEG32(mmVCE_VCPU_CACHE_OFFSET1, offset & 0x7fffffff);
	WWEG32(mmVCE_VCPU_CACHE_SIZE1, size);

	offset += size;
	size = VCE_V2_0_DATA_SIZE;
	WWEG32(mmVCE_VCPU_CACHE_OFFSET2, offset & 0x7fffffff);
	WWEG32(mmVCE_VCPU_CACHE_SIZE2, size);

	WWEG32_P(mmVCE_WMI_CTWW2, 0x0, ~0x100);
	WWEG32_FIEWD(VCE_SYS_INT_EN, VCE_SYS_INT_TWAP_INTEWWUPT_EN, 1);
}

static boow vce_v2_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn !(WWEG32(mmSWBM_STATUS2) & SWBM_STATUS2__VCE_BUSY_MASK);
}

static int vce_v2_0_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	unsigned i;

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (vce_v2_0_is_idwe(handwe))
			wetuwn 0;
	}
	wetuwn -ETIMEDOUT;
}

/**
 * vce_v2_0_stawt - stawt VCE bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the VCE bwock
 */
static int vce_v2_0_stawt(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;
	int w;

	/* set BUSY fwag */
	WWEG32_P(mmVCE_STATUS, 1, ~1);

	vce_v2_0_init_cg(adev);
	vce_v2_0_disabwe_cg(adev);

	vce_v2_0_mc_wesume(adev);

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

	WWEG32_FIEWD(VCE_VCPU_CNTW, CWK_EN, 1);
	WWEG32_FIEWD(VCE_SOFT_WESET, ECPU_SOFT_WESET, 1);
	mdeway(100);
	WWEG32_FIEWD(VCE_SOFT_WESET, ECPU_SOFT_WESET, 0);

	w = vce_v2_0_fiwmwawe_woaded(adev);

	/* cweaw BUSY fwag */
	WWEG32_P(mmVCE_STATUS, 0, ~1);

	if (w) {
		DWM_EWWOW("VCE not wesponding, giving up!!!\n");
		wetuwn w;
	}

	wetuwn 0;
}

static int vce_v2_0_stop(stwuct amdgpu_device *adev)
{
	int i;
	int status;

	if (vce_v2_0_wmi_cwean(adev)) {
		DWM_INFO("vce is not idwe \n");
		wetuwn 0;
	}

	if (vce_v2_0_wait_fow_idwe(adev)) {
		DWM_INFO("VCE is busy, Can't set cwock gating");
		wetuwn 0;
	}

	/* Staww UMC and wegistew bus befowe wesetting VCPU */
	WWEG32_P(mmVCE_WMI_CTWW2, 1 << 8, ~(1 << 8));

	fow (i = 0; i < 100; ++i) {
		status = WWEG32(mmVCE_WMI_STATUS);
		if (status & 0x240)
			bweak;
		mdeway(1);
	}

	WWEG32_P(mmVCE_VCPU_CNTW, 0, ~0x80001);

	/* put WMI, VCPU, WBC etc... into weset */
	WWEG32_P(mmVCE_SOFT_WESET, 1, ~0x1);

	WWEG32(mmVCE_STATUS, 0);

	wetuwn 0;
}

static void vce_v2_0_set_sw_cg(stwuct amdgpu_device *adev, boow gated)
{
	u32 tmp;

	if (gated) {
		tmp = WWEG32(mmVCE_CWOCK_GATING_B);
		tmp |= 0xe70000;
		WWEG32(mmVCE_CWOCK_GATING_B, tmp);

		tmp = WWEG32(mmVCE_UENC_CWOCK_GATING);
		tmp |= 0xff000000;
		WWEG32(mmVCE_UENC_CWOCK_GATING, tmp);

		tmp = WWEG32(mmVCE_UENC_WEG_CWOCK_GATING);
		tmp &= ~0x3fc;
		WWEG32(mmVCE_UENC_WEG_CWOCK_GATING, tmp);

		WWEG32(mmVCE_CGTT_CWK_OVEWWIDE, 0);
	} ewse {
		tmp = WWEG32(mmVCE_CWOCK_GATING_B);
		tmp |= 0xe7;
		tmp &= ~0xe70000;
		WWEG32(mmVCE_CWOCK_GATING_B, tmp);

		tmp = WWEG32(mmVCE_UENC_CWOCK_GATING);
		tmp |= 0x1fe000;
		tmp &= ~0xff000000;
		WWEG32(mmVCE_UENC_CWOCK_GATING, tmp);

		tmp = WWEG32(mmVCE_UENC_WEG_CWOCK_GATING);
		tmp |= 0x3fc;
		WWEG32(mmVCE_UENC_WEG_CWOCK_GATING, tmp);
	}
}

static void vce_v2_0_set_dyn_cg(stwuct amdgpu_device *adev, boow gated)
{
	u32 owig, tmp;

/* WMI_MC/WMI_UMC awways set in dynamic,
 * set {CGC_*_GATE_MODE, CGC_*_SW_GATE} = {0, 0}
 */
	tmp = WWEG32(mmVCE_CWOCK_GATING_B);
	tmp &= ~0x00060006;

/* Exception fow ECPU, IH, SEM, SYS bwocks needs to be tuwned on/off by SW */
	if (gated) {
		tmp |= 0xe10000;
		WWEG32(mmVCE_CWOCK_GATING_B, tmp);
	} ewse {
		tmp |= 0xe1;
		tmp &= ~0xe10000;
		WWEG32(mmVCE_CWOCK_GATING_B, tmp);
	}

	owig = tmp = WWEG32(mmVCE_UENC_CWOCK_GATING);
	tmp &= ~0x1fe000;
	tmp &= ~0xff000000;
	if (tmp != owig)
		WWEG32(mmVCE_UENC_CWOCK_GATING, tmp);

	owig = tmp = WWEG32(mmVCE_UENC_WEG_CWOCK_GATING);
	tmp &= ~0x3fc;
	if (tmp != owig)
		WWEG32(mmVCE_UENC_WEG_CWOCK_GATING, tmp);

	/* set VCE_UENC_WEG_CWOCK_GATING awways in dynamic mode */
	WWEG32(mmVCE_UENC_WEG_CWOCK_GATING, 0x00);

	if(gated)
		WWEG32(mmVCE_CGTT_CWK_OVEWWIDE, 0);
}

static void vce_v2_0_enabwe_mgcg(stwuct amdgpu_device *adev, boow enabwe,
								boow sw_cg)
{
	if (enabwe && (adev->cg_fwags & AMD_CG_SUPPOWT_VCE_MGCG)) {
		if (sw_cg)
			vce_v2_0_set_sw_cg(adev, twue);
		ewse
			vce_v2_0_set_dyn_cg(adev, twue);
	} ewse {
		vce_v2_0_disabwe_cg(adev);

		if (sw_cg)
			vce_v2_0_set_sw_cg(adev, fawse);
		ewse
			vce_v2_0_set_dyn_cg(adev, fawse);
	}
}

static int vce_v2_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->vce.num_wings = 2;

	vce_v2_0_set_wing_funcs(adev);
	vce_v2_0_set_iwq_funcs(adev);

	wetuwn 0;
}

static int vce_v2_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* VCE */
	w = amdgpu_iwq_add_id(adev, AMDGPU_IWQ_CWIENTID_WEGACY, 167, &adev->vce.iwq);
	if (w)
		wetuwn w;

	w = amdgpu_vce_sw_init(adev, VCE_V2_0_FW_SIZE +
		VCE_V2_0_STACK_SIZE + VCE_V2_0_DATA_SIZE);
	if (w)
		wetuwn w;

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

static int vce_v2_0_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vce_suspend(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_vce_sw_fini(adev);
}

static int vce_v2_0_hw_init(void *handwe)
{
	int w, i;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	amdgpu_asic_set_vce_cwocks(adev, 10000, 10000);
	vce_v2_0_enabwe_mgcg(adev, twue, fawse);

	fow (i = 0; i < adev->vce.num_wings; i++) {
		w = amdgpu_wing_test_hewpew(&adev->vce.wing[i]);
		if (w)
			wetuwn w;
	}

	DWM_INFO("VCE initiawized successfuwwy.\n");

	wetuwn 0;
}

static int vce_v2_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->vce.idwe_wowk);

	wetuwn 0;
}

static int vce_v2_0_suspend(void *handwe)
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

	w = vce_v2_0_hw_fini(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_vce_suspend(adev);
}

static int vce_v2_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vce_wesume(adev);
	if (w)
		wetuwn w;

	wetuwn vce_v2_0_hw_init(adev);
}

static int vce_v2_0_soft_weset(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	WWEG32_FIEWD(SWBM_SOFT_WESET, SOFT_WESET_VCE, 1);
	mdeway(5);

	wetuwn vce_v2_0_stawt(adev);
}

static int vce_v2_0_set_intewwupt_state(stwuct amdgpu_device *adev,
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

static int vce_v2_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: VCE\n");
	switch (entwy->swc_data[0]) {
	case 0:
	case 1:
		amdgpu_fence_pwocess(&adev->vce.wing[entwy->swc_data[0]]);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static int vce_v2_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	boow gate = fawse;
	boow sw_cg = fawse;

	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (state == AMD_CG_STATE_GATE) {
		gate = twue;
		sw_cg = twue;
	}

	vce_v2_0_enabwe_mgcg(adev, gate, sw_cg);

	wetuwn 0;
}

static int vce_v2_0_set_powewgating_state(void *handwe,
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

	if (state == AMD_PG_STATE_GATE)
		wetuwn vce_v2_0_stop(adev);
	ewse
		wetuwn vce_v2_0_stawt(adev);
}

static const stwuct amd_ip_funcs vce_v2_0_ip_funcs = {
	.name = "vce_v2_0",
	.eawwy_init = vce_v2_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vce_v2_0_sw_init,
	.sw_fini = vce_v2_0_sw_fini,
	.hw_init = vce_v2_0_hw_init,
	.hw_fini = vce_v2_0_hw_fini,
	.suspend = vce_v2_0_suspend,
	.wesume = vce_v2_0_wesume,
	.is_idwe = vce_v2_0_is_idwe,
	.wait_fow_idwe = vce_v2_0_wait_fow_idwe,
	.soft_weset = vce_v2_0_soft_weset,
	.set_cwockgating_state = vce_v2_0_set_cwockgating_state,
	.set_powewgating_state = vce_v2_0_set_powewgating_state,
};

static const stwuct amdgpu_wing_funcs vce_v2_0_wing_funcs = {
	.type = AMDGPU_WING_TYPE_VCE,
	.awign_mask = 0xf,
	.nop = VCE_CMD_NO_OP,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = vce_v2_0_wing_get_wptw,
	.get_wptw = vce_v2_0_wing_get_wptw,
	.set_wptw = vce_v2_0_wing_set_wptw,
	.pawse_cs = amdgpu_vce_wing_pawse_cs,
	.emit_fwame_size = 6, /* amdgpu_vce_wing_emit_fence  x1 no usew fence */
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

static void vce_v2_0_set_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vce.num_wings; i++) {
		adev->vce.wing[i].funcs = &vce_v2_0_wing_funcs;
		adev->vce.wing[i].me = i;
	}
}

static const stwuct amdgpu_iwq_swc_funcs vce_v2_0_iwq_funcs = {
	.set = vce_v2_0_set_intewwupt_state,
	.pwocess = vce_v2_0_pwocess_intewwupt,
};

static void vce_v2_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->vce.iwq.num_types = 1;
	adev->vce.iwq.funcs = &vce_v2_0_iwq_funcs;
};

const stwuct amdgpu_ip_bwock_vewsion vce_v2_0_ip_bwock =
{
		.type = AMD_IP_BWOCK_TYPE_VCE,
		.majow = 2,
		.minow = 0,
		.wev = 0,
		.funcs = &vce_v2_0_ip_funcs,
};
