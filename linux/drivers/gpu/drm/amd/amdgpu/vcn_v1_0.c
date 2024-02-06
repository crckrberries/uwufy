/*
 * Copywight 2016 Advanced Micwo Devices, Inc.
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

#incwude <winux/fiwmwawe.h>

#incwude "amdgpu.h"
#incwude "amdgpu_cs.h"
#incwude "amdgpu_vcn.h"
#incwude "amdgpu_pm.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "soc15_common.h"

#incwude "vcn/vcn_1_0_offset.h"
#incwude "vcn/vcn_1_0_sh_mask.h"
#incwude "mmhub/mmhub_9_1_offset.h"
#incwude "mmhub/mmhub_9_1_sh_mask.h"

#incwude "ivswcid/vcn/iwqswcs_vcn_1_0.h"
#incwude "jpeg_v1_0.h"
#incwude "vcn_v1_0.h"

#define mmUVD_WBC_XX_IB_WEG_CHECK_1_0		0x05ab
#define mmUVD_WBC_XX_IB_WEG_CHECK_1_0_BASE_IDX	1
#define mmUVD_WEG_XX_MASK_1_0			0x05ac
#define mmUVD_WEG_XX_MASK_1_0_BASE_IDX		1

static int vcn_v1_0_stop(stwuct amdgpu_device *adev);
static void vcn_v1_0_set_dec_wing_funcs(stwuct amdgpu_device *adev);
static void vcn_v1_0_set_enc_wing_funcs(stwuct amdgpu_device *adev);
static void vcn_v1_0_set_iwq_funcs(stwuct amdgpu_device *adev);
static int vcn_v1_0_set_powewgating_state(void *handwe, enum amd_powewgating_state state);
static int vcn_v1_0_pause_dpg_mode(stwuct amdgpu_device *adev,
				int inst_idx, stwuct dpg_pause_state *new_state);

static void vcn_v1_0_idwe_wowk_handwew(stwuct wowk_stwuct *wowk);
static void vcn_v1_0_wing_begin_use(stwuct amdgpu_wing *wing);

/**
 * vcn_v1_0_eawwy_init - set function pointews and woad micwocode
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 * Woad micwocode fwom fiwesystem
 */
static int vcn_v1_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->vcn.num_enc_wings = 2;

	vcn_v1_0_set_dec_wing_funcs(adev);
	vcn_v1_0_set_enc_wing_funcs(adev);
	vcn_v1_0_set_iwq_funcs(adev);

	jpeg_v1_0_eawwy_init(handwe);

	wetuwn amdgpu_vcn_eawwy_init(adev);
}

/**
 * vcn_v1_0_sw_init - sw init fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int vcn_v1_0_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	int i, w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* VCN DEC TWAP */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCN,
			VCN_1_0__SWCID__UVD_SYSTEM_MESSAGE_INTEWWUPT, &adev->vcn.inst->iwq);
	if (w)
		wetuwn w;

	/* VCN ENC TWAP */
	fow (i = 0; i < adev->vcn.num_enc_wings; ++i) {
		w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCN, i + VCN_1_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE,
					&adev->vcn.inst->iwq);
		if (w)
			wetuwn w;
	}

	w = amdgpu_vcn_sw_init(adev);
	if (w)
		wetuwn w;

	/* Ovewwide the wowk func */
	adev->vcn.idwe_wowk.wowk.func = vcn_v1_0_idwe_wowk_handwew;

	amdgpu_vcn_setup_ucode(adev);

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	wing = &adev->vcn.inst->wing_dec;
	wing->vm_hub = AMDGPU_MMHUB0(0);
	spwintf(wing->name, "vcn_dec");
	w = amdgpu_wing_init(adev, wing, 512, &adev->vcn.inst->iwq, 0,
			     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
	if (w)
		wetuwn w;

	adev->vcn.intewnaw.scwatch9 = adev->vcn.inst->extewnaw.scwatch9 =
		SOC15_WEG_OFFSET(UVD, 0, mmUVD_SCWATCH9);
	adev->vcn.intewnaw.data0 = adev->vcn.inst->extewnaw.data0 =
		SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0);
	adev->vcn.intewnaw.data1 = adev->vcn.inst->extewnaw.data1 =
		SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1);
	adev->vcn.intewnaw.cmd = adev->vcn.inst->extewnaw.cmd =
		SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD);
	adev->vcn.intewnaw.nop = adev->vcn.inst->extewnaw.nop =
		SOC15_WEG_OFFSET(UVD, 0, mmUVD_NO_OP);

	fow (i = 0; i < adev->vcn.num_enc_wings; ++i) {
		enum amdgpu_wing_pwiowity_wevew hw_pwio = amdgpu_vcn_get_enc_wing_pwio(i);

		wing = &adev->vcn.inst->wing_enc[i];
		wing->vm_hub = AMDGPU_MMHUB0(0);
		spwintf(wing->name, "vcn_enc%d", i);
		w = amdgpu_wing_init(adev, wing, 512, &adev->vcn.inst->iwq, 0,
				     hw_pwio, NUWW);
		if (w)
			wetuwn w;
	}

	adev->vcn.pause_dpg_mode = vcn_v1_0_pause_dpg_mode;

	if (amdgpu_vcnfw_wog) {
		vowatiwe stwuct amdgpu_fw_shawed *fw_shawed = adev->vcn.inst->fw_shawed.cpu_addw;

		fw_shawed->pwesent_fwag_0 = 0;
		amdgpu_vcn_fwwog_init(adev->vcn.inst);
	}

	w = jpeg_v1_0_sw_init(handwe);

	wetuwn w;
}

/**
 * vcn_v1_0_sw_fini - sw fini fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * VCN suspend and fwee up sw awwocation
 */
static int vcn_v1_0_sw_fini(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vcn_suspend(adev);
	if (w)
		wetuwn w;

	jpeg_v1_0_sw_fini(handwe);

	w = amdgpu_vcn_sw_fini(adev);

	wetuwn w;
}

/**
 * vcn_v1_0_hw_init - stawt and test VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int vcn_v1_0_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing = &adev->vcn.inst->wing_dec;
	int i, w;

	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		goto done;

	fow (i = 0; i < adev->vcn.num_enc_wings; ++i) {
		wing = &adev->vcn.inst->wing_enc[i];
		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			goto done;
	}

	wing = adev->jpeg.inst->wing_dec;
	w = amdgpu_wing_test_hewpew(wing);
	if (w)
		goto done;

done:
	if (!w)
		DWM_INFO("VCN decode and encode initiawized successfuwwy(undew %s).\n",
			(adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)?"DPG Mode":"SPG Mode");

	wetuwn w;
}

/**
 * vcn_v1_0_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the VCN bwock, mawk wing as not weady any mowe
 */
static int vcn_v1_0_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	if ((adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) ||
		(adev->vcn.cuw_state != AMD_PG_STATE_GATE &&
		 WWEG32_SOC15(VCN, 0, mmUVD_STATUS))) {
		vcn_v1_0_set_powewgating_state(adev, AMD_PG_STATE_GATE);
	}

	wetuwn 0;
}

/**
 * vcn_v1_0_suspend - suspend VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend VCN bwock
 */
static int vcn_v1_0_suspend(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow idwe_wowk_unexecuted;

	idwe_wowk_unexecuted = cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);
	if (idwe_wowk_unexecuted) {
		if (adev->pm.dpm_enabwed)
			amdgpu_dpm_enabwe_uvd(adev, fawse);
	}

	w = vcn_v1_0_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_suspend(adev);

	wetuwn w;
}

/**
 * vcn_v1_0_wesume - wesume VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init VCN bwock
 */
static int vcn_v1_0_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	w = vcn_v1_0_hw_init(adev);

	wetuwn w;
}

/**
 * vcn_v1_0_mc_wesume_spg_mode - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 *
 * Wet the VCN memowy contwowwew know it's offsets
 */
static void vcn_v1_0_mc_wesume_spg_mode(stwuct amdgpu_device *adev)
{
	uint32_t size = AMDGPU_GPU_PAGE_AWIGN(adev->vcn.fw->size + 4);
	uint32_t offset;

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			     (adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN].tmw_mc_addw_wo));
		WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			     (adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN].tmw_mc_addw_hi));
		WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	} ewse {
		WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			wowew_32_bits(adev->vcn.inst->gpu_addw));
		WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			uppew_32_bits(adev->vcn.inst->gpu_addw));
		offset = size;
		WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0,
			     AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
	}

	WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE0, size);

	/* cache window 1: stack */
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW,
		     wowew_32_bits(adev->vcn.inst->gpu_addw + offset));
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH,
		     uppew_32_bits(adev->vcn.inst->gpu_addw + offset));
	WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET1, 0);
	WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE);

	/* cache window 2: context */
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW,
		     wowew_32_bits(adev->vcn.inst->gpu_addw + offset + AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH,
		     uppew_32_bits(adev->vcn.inst->gpu_addw + offset + AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_OFFSET2, 0);
	WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE);

	WWEG32_SOC15(UVD, 0, mmUVD_UDEC_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_UDEC_DB_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_UDEC_DBW_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_UDEC_DBW_UV_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_MIF_CUWW_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_MIF_CUWW_UV_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_MIF_WECON1_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_MIF_WECON1_UV_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_MIF_WEF_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_MIF_WEF_UV_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_JPEG_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
	WWEG32_SOC15(UVD, 0, mmUVD_JPEG_UV_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config);
}

static void vcn_v1_0_mc_wesume_dpg_mode(stwuct amdgpu_device *adev)
{
	uint32_t size = AMDGPU_GPU_PAGE_AWIGN(adev->vcn.fw->size + 4);
	uint32_t offset;

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			     (adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN].tmw_mc_addw_wo),
			     0xFFFFFFFF, 0);
		WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			     (adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN].tmw_mc_addw_hi),
			     0xFFFFFFFF, 0);
		WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0, 0,
			     0xFFFFFFFF, 0);
		offset = 0;
	} ewse {
		WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			wowew_32_bits(adev->vcn.inst->gpu_addw), 0xFFFFFFFF, 0);
		WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			uppew_32_bits(adev->vcn.inst->gpu_addw), 0xFFFFFFFF, 0);
		offset = size;
		WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET0,
			     AMDGPU_UVD_FIWMWAWE_OFFSET >> 3, 0xFFFFFFFF, 0);
	}

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_SIZE0, size, 0xFFFFFFFF, 0);

	/* cache window 1: stack */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW,
		     wowew_32_bits(adev->vcn.inst->gpu_addw + offset), 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH,
		     uppew_32_bits(adev->vcn.inst->gpu_addw + offset), 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET1, 0,
			     0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE,
			     0xFFFFFFFF, 0);

	/* cache window 2: context */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW,
		     wowew_32_bits(adev->vcn.inst->gpu_addw + offset + AMDGPU_VCN_STACK_SIZE),
			     0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH,
		     uppew_32_bits(adev->vcn.inst->gpu_addw + offset + AMDGPU_VCN_STACK_SIZE),
			     0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_OFFSET2, 0, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE,
			     0xFFFFFFFF, 0);

	/* VCN gwobaw tiwing wegistews */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_DB_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_DBW_ADDW_CONFIG,
			adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_UDEC_DBW_UV_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_CUWW_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_CUWW_UV_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_WECON1_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_WECON1_UV_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_WEF_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MIF_WEF_UV_ADDW_CONFIG,
		adev->gfx.config.gb_addw_config, 0xFFFFFFFF, 0);
}

/**
 * vcn_v1_0_disabwe_cwock_gating - disabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 *
 * Disabwe cwock gating fow VCN bwock
 */
static void vcn_v1_0_disabwe_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data;

	/* JPEG disabwe CGC */
	data = WWEG32_SOC15(VCN, 0, mmJPEG_CGC_CTWW);

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		data |= 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data &= ~JPEG_CGC_CTWW__DYN_CWOCK_MODE_MASK;

	data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, 0, mmJPEG_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, 0, mmJPEG_CGC_GATE);
	data &= ~(JPEG_CGC_GATE__JPEG_MASK | JPEG_CGC_GATE__JPEG2_MASK);
	WWEG32_SOC15(VCN, 0, mmJPEG_CGC_GATE, data);

	/* UVD disabwe CGC */
	data = WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data &= ~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK;

	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, 0, mmUVD_CGC_GATE);
	data &= ~(UVD_CGC_GATE__SYS_MASK
		| UVD_CGC_GATE__UDEC_MASK
		| UVD_CGC_GATE__MPEG2_MASK
		| UVD_CGC_GATE__WEGS_MASK
		| UVD_CGC_GATE__WBC_MASK
		| UVD_CGC_GATE__WMI_MC_MASK
		| UVD_CGC_GATE__WMI_UMC_MASK
		| UVD_CGC_GATE__IDCT_MASK
		| UVD_CGC_GATE__MPWD_MASK
		| UVD_CGC_GATE__MPC_MASK
		| UVD_CGC_GATE__WBSI_MASK
		| UVD_CGC_GATE__WWBBM_MASK
		| UVD_CGC_GATE__UDEC_WE_MASK
		| UVD_CGC_GATE__UDEC_CM_MASK
		| UVD_CGC_GATE__UDEC_IT_MASK
		| UVD_CGC_GATE__UDEC_DB_MASK
		| UVD_CGC_GATE__UDEC_MP_MASK
		| UVD_CGC_GATE__WCB_MASK
		| UVD_CGC_GATE__VCPU_MASK
		| UVD_CGC_GATE__SCPU_MASK);
	WWEG32_SOC15(VCN, 0, mmUVD_CGC_GATE, data);

	data = WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW);
	data &= ~(UVD_CGC_CTWW__UDEC_WE_MODE_MASK
		| UVD_CGC_CTWW__UDEC_CM_MODE_MASK
		| UVD_CGC_CTWW__UDEC_IT_MODE_MASK
		| UVD_CGC_CTWW__UDEC_DB_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MP_MODE_MASK
		| UVD_CGC_CTWW__SYS_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MODE_MASK
		| UVD_CGC_CTWW__MPEG2_MODE_MASK
		| UVD_CGC_CTWW__WEGS_MODE_MASK
		| UVD_CGC_CTWW__WBC_MODE_MASK
		| UVD_CGC_CTWW__WMI_MC_MODE_MASK
		| UVD_CGC_CTWW__WMI_UMC_MODE_MASK
		| UVD_CGC_CTWW__IDCT_MODE_MASK
		| UVD_CGC_CTWW__MPWD_MODE_MASK
		| UVD_CGC_CTWW__MPC_MODE_MASK
		| UVD_CGC_CTWW__WBSI_MODE_MASK
		| UVD_CGC_CTWW__WWBBM_MODE_MASK
		| UVD_CGC_CTWW__WCB_MODE_MASK
		| UVD_CGC_CTWW__VCPU_MODE_MASK
		| UVD_CGC_CTWW__SCPU_MODE_MASK);
	WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW, data);

	/* tuwn on */
	data = WWEG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_GATE);
	data |= (UVD_SUVD_CGC_GATE__SWE_MASK
		| UVD_SUVD_CGC_GATE__SIT_MASK
		| UVD_SUVD_CGC_GATE__SMP_MASK
		| UVD_SUVD_CGC_GATE__SCM_MASK
		| UVD_SUVD_CGC_GATE__SDB_MASK
		| UVD_SUVD_CGC_GATE__SWE_H264_MASK
		| UVD_SUVD_CGC_GATE__SWE_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SIT_H264_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SCM_H264_MASK
		| UVD_SUVD_CGC_GATE__SCM_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SDB_H264_MASK
		| UVD_SUVD_CGC_GATE__SDB_HEVC_MASK
		| UVD_SUVD_CGC_GATE__SCWW_MASK
		| UVD_SUVD_CGC_GATE__UVD_SC_MASK
		| UVD_SUVD_CGC_GATE__ENT_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_DEC_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_ENC_MASK
		| UVD_SUVD_CGC_GATE__SITE_MASK
		| UVD_SUVD_CGC_GATE__SWE_VP9_MASK
		| UVD_SUVD_CGC_GATE__SCM_VP9_MASK
		| UVD_SUVD_CGC_GATE__SIT_VP9_DEC_MASK
		| UVD_SUVD_CGC_GATE__SDB_VP9_MASK
		| UVD_SUVD_CGC_GATE__IME_HEVC_MASK);
	WWEG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_GATE, data);

	data = WWEG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTWW);
	data &= ~(UVD_SUVD_CGC_CTWW__SWE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCWW_MODE_MASK
		| UVD_SUVD_CGC_CTWW__UVD_SC_MODE_MASK
		| UVD_SUVD_CGC_CTWW__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__IME_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SITE_MODE_MASK);
	WWEG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTWW, data);
}

/**
 * vcn_v1_0_enabwe_cwock_gating - enabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 *
 * Enabwe cwock gating fow VCN bwock
 */
static void vcn_v1_0_enabwe_cwock_gating(stwuct amdgpu_device *adev)
{
	uint32_t data = 0;

	/* enabwe JPEG CGC */
	data = WWEG32_SOC15(VCN, 0, mmJPEG_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		data |= 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data |= 0 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, 0, mmJPEG_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, 0, mmJPEG_CGC_GATE);
	data |= (JPEG_CGC_GATE__JPEG_MASK | JPEG_CGC_GATE__JPEG2_MASK);
	WWEG32_SOC15(VCN, 0, mmJPEG_CGC_GATE, data);

	/* enabwe UVD CGC */
	data = WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW);
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		data |= 1 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		data |= 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW);
	data |= (UVD_CGC_CTWW__UDEC_WE_MODE_MASK
		| UVD_CGC_CTWW__UDEC_CM_MODE_MASK
		| UVD_CGC_CTWW__UDEC_IT_MODE_MASK
		| UVD_CGC_CTWW__UDEC_DB_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MP_MODE_MASK
		| UVD_CGC_CTWW__SYS_MODE_MASK
		| UVD_CGC_CTWW__UDEC_MODE_MASK
		| UVD_CGC_CTWW__MPEG2_MODE_MASK
		| UVD_CGC_CTWW__WEGS_MODE_MASK
		| UVD_CGC_CTWW__WBC_MODE_MASK
		| UVD_CGC_CTWW__WMI_MC_MODE_MASK
		| UVD_CGC_CTWW__WMI_UMC_MODE_MASK
		| UVD_CGC_CTWW__IDCT_MODE_MASK
		| UVD_CGC_CTWW__MPWD_MODE_MASK
		| UVD_CGC_CTWW__MPC_MODE_MASK
		| UVD_CGC_CTWW__WBSI_MODE_MASK
		| UVD_CGC_CTWW__WWBBM_MODE_MASK
		| UVD_CGC_CTWW__WCB_MODE_MASK
		| UVD_CGC_CTWW__VCPU_MODE_MASK
		| UVD_CGC_CTWW__SCPU_MODE_MASK);
	WWEG32_SOC15(VCN, 0, mmUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTWW);
	data |= (UVD_SUVD_CGC_CTWW__SWE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCWW_MODE_MASK
		| UVD_SUVD_CGC_CTWW__UVD_SC_MODE_MASK
		| UVD_SUVD_CGC_CTWW__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__IME_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SITE_MODE_MASK);
	WWEG32_SOC15(VCN, 0, mmUVD_SUVD_CGC_CTWW, data);
}

static void vcn_v1_0_cwock_gating_dpg_mode(stwuct amdgpu_device *adev, uint8_t swam_sew)
{
	uint32_t weg_data = 0;

	/* disabwe JPEG CGC */
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		weg_data = 1 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		weg_data = 0 << JPEG_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	weg_data |= 1 << JPEG_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	weg_data |= 4 << JPEG_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmJPEG_CGC_CTWW, weg_data, 0xFFFFFFFF, swam_sew);

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmJPEG_CGC_GATE, 0, 0xFFFFFFFF, swam_sew);

	/* enabwe sw cwock gating contwow */
	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		weg_data = 1 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	ewse
		weg_data = 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	weg_data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	weg_data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	weg_data &= ~(UVD_CGC_CTWW__UDEC_WE_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_CM_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_IT_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_DB_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_MP_MODE_MASK |
		 UVD_CGC_CTWW__SYS_MODE_MASK |
		 UVD_CGC_CTWW__UDEC_MODE_MASK |
		 UVD_CGC_CTWW__MPEG2_MODE_MASK |
		 UVD_CGC_CTWW__WEGS_MODE_MASK |
		 UVD_CGC_CTWW__WBC_MODE_MASK |
		 UVD_CGC_CTWW__WMI_MC_MODE_MASK |
		 UVD_CGC_CTWW__WMI_UMC_MODE_MASK |
		 UVD_CGC_CTWW__IDCT_MODE_MASK |
		 UVD_CGC_CTWW__MPWD_MODE_MASK |
		 UVD_CGC_CTWW__MPC_MODE_MASK |
		 UVD_CGC_CTWW__WBSI_MODE_MASK |
		 UVD_CGC_CTWW__WWBBM_MODE_MASK |
		 UVD_CGC_CTWW__WCB_MODE_MASK |
		 UVD_CGC_CTWW__VCPU_MODE_MASK |
		 UVD_CGC_CTWW__SCPU_MODE_MASK);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_CGC_CTWW, weg_data, 0xFFFFFFFF, swam_sew);

	/* tuwn off cwock gating */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_CGC_GATE, 0, 0xFFFFFFFF, swam_sew);

	/* tuwn on SUVD cwock gating */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SUVD_CGC_GATE, 1, 0xFFFFFFFF, swam_sew);

	/* tuwn on sw mode in UVD_SUVD_CGC_CTWW */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SUVD_CGC_CTWW, 0, 0xFFFFFFFF, swam_sew);
}

static void vcn_1_0_disabwe_static_powew_gating(stwuct amdgpu_device *adev)
{
	uint32_t data = 0;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN) {
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIW_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIW_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDW_PWW_CONFIG__SHIFT);

		WWEG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_WWEG(VCN, 0, mmUVD_PGFSM_STATUS, UVD_PGFSM_STATUS__UVDM_UVDU_PWW_ON, 0xFFFFFF);
	} ewse {
		data = (1 << UVD_PGFSM_CONFIG__UVDM_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDU_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDF_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDC_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDB_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDIW_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDIW_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTD_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDTE_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDE_PWW_CONFIG__SHIFT
			| 1 << UVD_PGFSM_CONFIG__UVDW_PWW_CONFIG__SHIFT);
		WWEG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);
		SOC15_WAIT_ON_WWEG(VCN, 0, mmUVD_PGFSM_STATUS, 0,  0xFFFFFFFF);
	}

	/* powwing UVD_PGFSM_STATUS to confiwm UVDM_PWW_STATUS , UVDU_PWW_STATUS awe 0 (powew on) */

	data = WWEG32_SOC15(VCN, 0, mmUVD_POWEW_STATUS);
	data &= ~0x103;
	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN)
		data |= UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON | UVD_POWEW_STATUS__UVD_PG_EN_MASK;

	WWEG32_SOC15(VCN, 0, mmUVD_POWEW_STATUS, data);
}

static void vcn_1_0_enabwe_static_powew_gating(stwuct amdgpu_device *adev)
{
	uint32_t data = 0;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN) {
		/* Befowe powew off, this indicatow has to be tuwned on */
		data = WWEG32_SOC15(VCN, 0, mmUVD_POWEW_STATUS);
		data &= ~UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK;
		data |= UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF;
		WWEG32_SOC15(VCN, 0, mmUVD_POWEW_STATUS, data);


		data = (2 << UVD_PGFSM_CONFIG__UVDM_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDU_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDF_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDC_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDB_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIW_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDIW_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTD_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDTE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDE_PWW_CONFIG__SHIFT
			| 2 << UVD_PGFSM_CONFIG__UVDW_PWW_CONFIG__SHIFT);

		WWEG32_SOC15(VCN, 0, mmUVD_PGFSM_CONFIG, data);

		data = (2 << UVD_PGFSM_STATUS__UVDM_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDU_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDF_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDC_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDB_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDIW_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDIW_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTD_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDTE_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDE_PWW_STATUS__SHIFT
			| 2 << UVD_PGFSM_STATUS__UVDW_PWW_STATUS__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, 0, mmUVD_PGFSM_STATUS, data, 0xFFFFFFFF);
	}
}

/**
 * vcn_v1_0_stawt_spg_mode - stawt VCN bwock
 *
 * @adev: amdgpu_device pointew
 *
 * Setup and stawt the VCN bwock
 */
static int vcn_v1_0_stawt_spg_mode(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->vcn.inst->wing_dec;
	uint32_t wb_bufsz, tmp;
	uint32_t wmi_swap_cntw;
	int i, j, w;

	/* disabwe byte swapping */
	wmi_swap_cntw = 0;

	vcn_1_0_disabwe_static_powew_gating(adev);

	tmp = WWEG32_SOC15(UVD, 0, mmUVD_STATUS) | UVD_STATUS__UVD_BUSY;
	WWEG32_SOC15(UVD, 0, mmUVD_STATUS, tmp);

	/* disabwe cwock gating */
	vcn_v1_0_disabwe_cwock_gating(adev);

	/* disabwe intewupt */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_MASTINT_EN), 0,
			~UVD_MASTINT_EN__VCPU_EN_MASK);

	/* initiawize VCN memowy contwowwew */
	tmp = WWEG32_SOC15(UVD, 0, mmUVD_WMI_CTWW);
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_CTWW, tmp		|
		UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK	|
		UVD_WMI_CTWW__MASK_MC_UWGENT_MASK			|
		UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK		|
		UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK);

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) WB and IB */
	wmi_swap_cntw = 0xa;
#endif
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_SWAP_CNTW, wmi_swap_cntw);

	tmp = WWEG32_SOC15(UVD, 0, mmUVD_MPC_CNTW);
	tmp &= ~UVD_MPC_CNTW__WEPWACEMENT_MODE_MASK;
	tmp |= 0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT;
	WWEG32_SOC15(UVD, 0, mmUVD_MPC_CNTW, tmp);

	WWEG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUXA0,
		((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
		(0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
		(0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)));

	WWEG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUXB0,
		((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
		(0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
		(0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)));

	WWEG32_SOC15(UVD, 0, mmUVD_MPC_SET_MUX,
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		(0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		(0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));

	vcn_v1_0_mc_wesume_spg_mode(adev);

	WWEG32_SOC15(UVD, 0, mmUVD_WEG_XX_MASK_1_0, 0x10);
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_XX_IB_WEG_CHECK_1_0,
		WWEG32_SOC15(UVD, 0, mmUVD_WBC_XX_IB_WEG_CHECK_1_0) | 0x3);

	/* enabwe VCPU cwock */
	WWEG32_SOC15(UVD, 0, mmUVD_VCPU_CNTW, UVD_VCPU_CNTW__CWK_EN_MASK);

	/* boot up the VCPU */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SOFT_WESET), 0,
			~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);

	/* enabwe UMC */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WMI_CTWW2), 0,
			~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

	tmp = WWEG32_SOC15(UVD, 0, mmUVD_SOFT_WESET);
	tmp &= ~UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
	tmp &= ~UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
	WWEG32_SOC15(UVD, 0, mmUVD_SOFT_WESET, tmp);

	fow (i = 0; i < 10; ++i) {
		uint32_t status;

		fow (j = 0; j < 100; ++j) {
			status = WWEG32_SOC15(UVD, 0, mmUVD_STATUS);
			if (status & UVD_STATUS__IDWE)
				bweak;
			mdeway(10);
		}
		w = 0;
		if (status & UVD_STATUS__IDWE)
			bweak;

		DWM_EWWOW("VCN decode not wesponding, twying to weset the VCPU!!!\n");
		WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SOFT_WESET),
				UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK,
				~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
		mdeway(10);
		WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SOFT_WESET), 0,
				~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);
		mdeway(10);
		w = -1;
	}

	if (w) {
		DWM_EWWOW("VCN decode not wesponding, giving up!!!\n");
		wetuwn w;
	}
	/* enabwe mastew intewwupt */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, ~UVD_MASTINT_EN__VCPU_EN_MASK);

	/* enabwe system intewwupt fow JWBC, TODO: move to set intewwupt*/
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SYS_INT_EN),
		UVD_SYS_INT_EN__UVD_JWBC_EN_MASK,
		~UVD_SYS_INT_EN__UVD_JWBC_EN_MASK);

	/* cweaw the busy bit of UVD_STATUS */
	tmp = WWEG32_SOC15(UVD, 0, mmUVD_STATUS) & ~UVD_STATUS__UVD_BUSY;
	WWEG32_SOC15(UVD, 0, mmUVD_STATUS, tmp);

	/* fowce WBC into idwe state */
	wb_bufsz = owdew_base_2(wing->wing_size);
	tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, wb_bufsz);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_CNTW, tmp);

	/* set the wwite pointew deway */
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW_CNTW, 0);

	/* set the wb addwess */
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW_ADDW,
			(uppew_32_bits(wing->gpu_addw) >> 2));

	/* pwogwam the WB_BASE fow wing buffew */
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_WBC_WB_64BIT_BAW_WOW,
			wowew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH,
			uppew_32_bits(wing->gpu_addw));

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW, 0);

	WWEG32_SOC15(UVD, 0, mmUVD_SCWATCH2, 0);

	wing->wptw = WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW);
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW,
			wowew_32_bits(wing->wptw));

	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WBC_WB_CNTW), 0,
			~UVD_WBC_WB_CNTW__WB_NO_FETCH_MASK);

	wing = &adev->vcn.inst->wing_enc[0];
	WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
	WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
	WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_WO, wing->gpu_addw);
	WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(UVD, 0, mmUVD_WB_SIZE, wing->wing_size / 4);

	wing = &adev->vcn.inst->wing_enc[1];
	WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
	WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
	WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_WO2, wing->gpu_addw);
	WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(UVD, 0, mmUVD_WB_SIZE2, wing->wing_size / 4);

	jpeg_v1_0_stawt(adev, 0);

	wetuwn 0;
}

static int vcn_v1_0_stawt_dpg_mode(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing = &adev->vcn.inst->wing_dec;
	uint32_t wb_bufsz, tmp;
	uint32_t wmi_swap_cntw;

	/* disabwe byte swapping */
	wmi_swap_cntw = 0;

	vcn_1_0_enabwe_static_powew_gating(adev);

	/* enabwe dynamic powew gating mode */
	tmp = WWEG32_SOC15(UVD, 0, mmUVD_POWEW_STATUS);
	tmp |= UVD_POWEW_STATUS__UVD_PG_MODE_MASK;
	tmp |= UVD_POWEW_STATUS__UVD_PG_EN_MASK;
	WWEG32_SOC15(UVD, 0, mmUVD_POWEW_STATUS, tmp);

	/* enabwe cwock gating */
	vcn_v1_0_cwock_gating_dpg_mode(adev, 0);

	/* enabwe VCPU cwock */
	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK;
	tmp |= UVD_VCPU_CNTW__MIF_WW_WOW_THWESHOWD_BP_MASK;
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_VCPU_CNTW, tmp, 0xFFFFFFFF, 0);

	/* disabwe intewupt */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MASTINT_EN,
			0, UVD_MASTINT_EN__VCPU_EN_MASK, 0);

	/* initiawize VCN memowy contwowwew */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_CTWW,
		(8 << UVD_WMI_CTWW__WWITE_CWEAN_TIMEW__SHIFT) |
		UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
		UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
		UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK |
		UVD_WMI_CTWW__WEQ_MODE_MASK |
		UVD_WMI_CTWW__CWC_WESET_MASK |
		UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
		0x00100000W, 0xFFFFFFFF, 0);

#ifdef __BIG_ENDIAN
	/* swap (8 in 32) WB and IB */
	wmi_swap_cntw = 0xa;
#endif
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_SWAP_CNTW, wmi_swap_cntw, 0xFFFFFFFF, 0);

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_CNTW,
		0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT, 0xFFFFFFFF, 0);

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_SET_MUXA0,
		((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)), 0xFFFFFFFF, 0);

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_SET_MUXB0,
		((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)), 0xFFFFFFFF, 0);

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MPC_SET_MUX,
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0xFFFFFFFF, 0);

	vcn_v1_0_mc_wesume_dpg_mode(adev);

	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WEG_XX_MASK, 0x10, 0xFFFFFFFF, 0);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WBC_XX_IB_WEG_CHECK, 0x3, 0xFFFFFFFF, 0);

	/* boot up the VCPU */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SOFT_WESET, 0, 0xFFFFFFFF, 0);

	/* enabwe UMC */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_CTWW2,
		0x1F << UVD_WMI_CTWW2__WE_OFWD_MIF_WW_WEQ_NUM__SHIFT,
		0xFFFFFFFF, 0);

	/* enabwe mastew intewwupt */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_MASTINT_EN,
			UVD_MASTINT_EN__VCPU_EN_MASK, UVD_MASTINT_EN__VCPU_EN_MASK, 0);

	vcn_v1_0_cwock_gating_dpg_mode(adev, 1);
	/* setup mmUVD_WMI_CTWW */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_WMI_CTWW,
		(8 << UVD_WMI_CTWW__WWITE_CWEAN_TIMEW__SHIFT) |
		UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
		UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
		UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK |
		UVD_WMI_CTWW__WEQ_MODE_MASK |
		UVD_WMI_CTWW__CWC_WESET_MASK |
		UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
		0x00100000W, 0xFFFFFFFF, 1);

	tmp = adev->gfx.config.gb_addw_config;
	/* setup VCN gwobaw tiwing wegistews */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_JPEG_ADDW_CONFIG, tmp, 0xFFFFFFFF, 1);
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_JPEG_UV_ADDW_CONFIG, tmp, 0xFFFFFFFF, 1);

	/* enabwe System Intewwupt fow JWBC */
	WWEG32_SOC15_DPG_MODE_1_0(UVD, 0, mmUVD_SYS_INT_EN,
									UVD_SYS_INT_EN__UVD_JWBC_EN_MASK, 0xFFFFFFFF, 1);

	/* fowce WBC into idwe state */
	wb_bufsz = owdew_base_2(wing->wing_size);
	tmp = WEG_SET_FIEWD(0, UVD_WBC_WB_CNTW, WB_BUFSZ, wb_bufsz);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_BWKSZ, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_FETCH, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_NO_UPDATE, 1);
	tmp = WEG_SET_FIEWD(tmp, UVD_WBC_WB_CNTW, WB_WPTW_WW_EN, 1);
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_CNTW, tmp);

	/* set the wwite pointew deway */
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW_CNTW, 0);

	/* set the wb addwess */
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW_ADDW,
								(uppew_32_bits(wing->gpu_addw) >> 2));

	/* pwogwam the WB_BASE fow wing buffew */
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_WBC_WB_64BIT_BAW_WOW,
								wowew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(UVD, 0, mmUVD_WMI_WBC_WB_64BIT_BAW_HIGH,
								uppew_32_bits(wing->gpu_addw));

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW, 0);

	WWEG32_SOC15(UVD, 0, mmUVD_SCWATCH2, 0);

	wing->wptw = WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW);
	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW,
								wowew_32_bits(wing->wptw));

	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WBC_WB_CNTW), 0,
			~UVD_WBC_WB_CNTW__WB_NO_FETCH_MASK);

	jpeg_v1_0_stawt(adev, 1);

	wetuwn 0;
}

static int vcn_v1_0_stawt(stwuct amdgpu_device *adev)
{
	wetuwn (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) ?
		vcn_v1_0_stawt_dpg_mode(adev) : vcn_v1_0_stawt_spg_mode(adev);
}

/**
 * vcn_v1_0_stop_spg_mode - stop VCN bwock
 *
 * @adev: amdgpu_device pointew
 *
 * stop the VCN bwock
 */
static int vcn_v1_0_stop_spg_mode(stwuct amdgpu_device *adev)
{
	int tmp;

	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_STATUS, UVD_STATUS__IDWE, 0x7);

	tmp = UVD_WMI_STATUS__VCPU_WMI_WWITE_CWEAN_MASK |
		UVD_WMI_STATUS__WEAD_CWEAN_MASK |
		UVD_WMI_STATUS__WWITE_CWEAN_MASK |
		UVD_WMI_STATUS__WWITE_CWEAN_WAW_MASK;
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_WMI_STATUS, tmp, tmp);

	/* staww UMC channew */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WMI_CTWW2),
		UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK,
		~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

	tmp = UVD_WMI_STATUS__UMC_WEAD_CWEAN_WAW_MASK |
		UVD_WMI_STATUS__UMC_WWITE_CWEAN_WAW_MASK;
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_WMI_STATUS, tmp, tmp);

	/* disabwe VCPU cwock */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_VCPU_CNTW), 0,
		~UVD_VCPU_CNTW__CWK_EN_MASK);

	/* weset WMI UMC/WMI */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SOFT_WESET),
		UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK,
		~UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK);

	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SOFT_WESET),
		UVD_SOFT_WESET__WMI_SOFT_WESET_MASK,
		~UVD_SOFT_WESET__WMI_SOFT_WESET_MASK);

	/* put VCPU into weset */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_SOFT_WESET),
		UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK,
		~UVD_SOFT_WESET__VCPU_SOFT_WESET_MASK);

	WWEG32_SOC15(UVD, 0, mmUVD_STATUS, 0);

	vcn_v1_0_enabwe_cwock_gating(adev);
	vcn_1_0_enabwe_static_powew_gating(adev);
	wetuwn 0;
}

static int vcn_v1_0_stop_dpg_mode(stwuct amdgpu_device *adev)
{
	uint32_t tmp;

	/* Wait fow powew status to be UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF */
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_POWEW_STATUS,
			UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF,
			UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* wait fow wead ptw to be equaw to wwite ptw */
	tmp = WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW);
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_WB_WPTW, tmp, 0xFFFFFFFF);

	tmp = WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2);
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_WB_WPTW2, tmp, 0xFFFFFFFF);

	tmp = WWEG32_SOC15(UVD, 0, mmUVD_JWBC_WB_WPTW);
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_JWBC_WB_WPTW, tmp, 0xFFFFFFFF);

	tmp = WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW) & 0x7FFFFFFF;
	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_WBC_WB_WPTW, tmp, 0xFFFFFFFF);

	SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_POWEW_STATUS,
		UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF,
		UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* disabwe dynamic powew gating mode */
	WWEG32_P(SOC15_WEG_OFFSET(UVD, 0, mmUVD_POWEW_STATUS), 0,
			~UVD_POWEW_STATUS__UVD_PG_MODE_MASK);

	wetuwn 0;
}

static int vcn_v1_0_stop(stwuct amdgpu_device *adev)
{
	int w;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)
		w = vcn_v1_0_stop_dpg_mode(adev);
	ewse
		w = vcn_v1_0_stop_spg_mode(adev);

	wetuwn w;
}

static int vcn_v1_0_pause_dpg_mode(stwuct amdgpu_device *adev,
				int inst_idx, stwuct dpg_pause_state *new_state)
{
	int wet_code;
	uint32_t weg_data = 0;
	uint32_t weg_data2 = 0;
	stwuct amdgpu_wing *wing;

	/* pause/unpause if state is changed */
	if (adev->vcn.inst[inst_idx].pause_state.fw_based != new_state->fw_based) {
		DWM_DEBUG("dpg pause state changed %d:%d -> %d:%d",
			adev->vcn.inst[inst_idx].pause_state.fw_based,
			adev->vcn.inst[inst_idx].pause_state.jpeg,
			new_state->fw_based, new_state->jpeg);

		weg_data = WWEG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

		if (new_state->fw_based == VCN_DPG_STATE__PAUSE) {
			wet_code = 0;

			if (!(weg_data & UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK))
				wet_code = SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_POWEW_STATUS,
						   UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF,
						   UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

			if (!wet_code) {
				/* pause DPG non-jpeg */
				weg_data |= UVD_DPG_PAUSE__NJ_PAUSE_DPG_WEQ_MASK;
				WWEG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, weg_data);
				SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_DPG_PAUSE,
						   UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK,
						   UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

				/* Westowe */
				wing = &adev->vcn.inst->wing_enc[0];
				WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_WO, wing->gpu_addw);
				WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
				WWEG32_SOC15(UVD, 0, mmUVD_WB_SIZE, wing->wing_size / 4);
				WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));
				WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW, wowew_32_bits(wing->wptw));

				wing = &adev->vcn.inst->wing_enc[1];
				WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_WO2, wing->gpu_addw);
				WWEG32_SOC15(UVD, 0, mmUVD_WB_BASE_HI2, uppew_32_bits(wing->gpu_addw));
				WWEG32_SOC15(UVD, 0, mmUVD_WB_SIZE2, wing->wing_size / 4);
				WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));
				WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2, wowew_32_bits(wing->wptw));

				wing = &adev->vcn.inst->wing_dec;
				WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW,
						   WWEG32_SOC15(UVD, 0, mmUVD_SCWATCH2) & 0x7FFFFFFF);
				SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_POWEW_STATUS,
						   UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON,
						   UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
			}
		} ewse {
			/* unpause dpg non-jpeg, no need to wait */
			weg_data &= ~UVD_DPG_PAUSE__NJ_PAUSE_DPG_WEQ_MASK;
			WWEG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, weg_data);
		}
		adev->vcn.inst[inst_idx].pause_state.fw_based = new_state->fw_based;
	}

	/* pause/unpause if state is changed */
	if (adev->vcn.inst[inst_idx].pause_state.jpeg != new_state->jpeg) {
		DWM_DEBUG("dpg pause state changed %d:%d -> %d:%d",
			adev->vcn.inst[inst_idx].pause_state.fw_based,
			adev->vcn.inst[inst_idx].pause_state.jpeg,
			new_state->fw_based, new_state->jpeg);

		weg_data = WWEG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK);

		if (new_state->jpeg == VCN_DPG_STATE__PAUSE) {
			wet_code = 0;

			if (!(weg_data & UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK))
				wet_code = SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_POWEW_STATUS,
						   UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF,
						   UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

			if (!wet_code) {
				/* Make suwe JPWG Snoop is disabwed befowe sending the pause */
				weg_data2 = WWEG32_SOC15(UVD, 0, mmUVD_POWEW_STATUS);
				weg_data2 |= UVD_POWEW_STATUS__JWBC_SNOOP_DIS_MASK;
				WWEG32_SOC15(UVD, 0, mmUVD_POWEW_STATUS, weg_data2);

				/* pause DPG jpeg */
				weg_data |= UVD_DPG_PAUSE__JPEG_PAUSE_DPG_WEQ_MASK;
				WWEG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, weg_data);
				SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_DPG_PAUSE,
							UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK,
							UVD_DPG_PAUSE__JPEG_PAUSE_DPG_ACK_MASK);

				/* Westowe */
				wing = adev->jpeg.inst->wing_dec;
				WWEG32_SOC15(UVD, 0, mmUVD_WMI_JWBC_WB_VMID, 0);
				WWEG32_SOC15(UVD, 0, mmUVD_JWBC_WB_CNTW,
							UVD_JWBC_WB_CNTW__WB_NO_FETCH_MASK |
							UVD_JWBC_WB_CNTW__WB_WPTW_WW_EN_MASK);
				WWEG32_SOC15(UVD, 0, mmUVD_WMI_JWBC_WB_64BIT_BAW_WOW,
							wowew_32_bits(wing->gpu_addw));
				WWEG32_SOC15(UVD, 0, mmUVD_WMI_JWBC_WB_64BIT_BAW_HIGH,
							uppew_32_bits(wing->gpu_addw));
				WWEG32_SOC15(UVD, 0, mmUVD_JWBC_WB_WPTW, wing->wptw);
				WWEG32_SOC15(UVD, 0, mmUVD_JWBC_WB_WPTW, wing->wptw);
				WWEG32_SOC15(UVD, 0, mmUVD_JWBC_WB_CNTW,
							UVD_JWBC_WB_CNTW__WB_WPTW_WW_EN_MASK);

				wing = &adev->vcn.inst->wing_dec;
				WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW,
						   WWEG32_SOC15(UVD, 0, mmUVD_SCWATCH2) & 0x7FFFFFFF);
				SOC15_WAIT_ON_WWEG(UVD, 0, mmUVD_POWEW_STATUS,
						   UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON,
						   UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
			}
		} ewse {
			/* unpause dpg jpeg, no need to wait */
			weg_data &= ~UVD_DPG_PAUSE__JPEG_PAUSE_DPG_WEQ_MASK;
			WWEG32_SOC15(UVD, 0, mmUVD_DPG_PAUSE, weg_data);
		}
		adev->vcn.inst[inst_idx].pause_state.jpeg = new_state->jpeg;
	}

	wetuwn 0;
}

static boow vcn_v1_0_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn (WWEG32_SOC15(VCN, 0, mmUVD_STATUS) == UVD_STATUS__IDWE);
}

static int vcn_v1_0_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	wet = SOC15_WAIT_ON_WWEG(VCN, 0, mmUVD_STATUS, UVD_STATUS__IDWE,
		UVD_STATUS__IDWE);

	wetuwn wet;
}

static int vcn_v1_0_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE);

	if (enabwe) {
		/* wait fow STATUS to cweaw */
		if (!vcn_v1_0_is_idwe(handwe))
			wetuwn -EBUSY;
		vcn_v1_0_enabwe_cwock_gating(adev);
	} ewse {
		/* disabwe HW gating and enabwe Sw gating */
		vcn_v1_0_disabwe_cwock_gating(adev);
	}
	wetuwn 0;
}

/**
 * vcn_v1_0_dec_wing_get_wptw - get wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wead pointew
 */
static uint64_t vcn_v1_0_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW);
}

/**
 * vcn_v1_0_dec_wing_get_wptw - get wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe wwite pointew
 */
static uint64_t vcn_v1_0_dec_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW);
}

/**
 * vcn_v1_0_dec_wing_set_wptw - set wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the wwite pointew to the hawdwawe
 */
static void vcn_v1_0_dec_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)
		WWEG32_SOC15(UVD, 0, mmUVD_SCWATCH2,
			wowew_32_bits(wing->wptw) | 0x80000000);

	WWEG32_SOC15(UVD, 0, mmUVD_WBC_WB_WPTW, wowew_32_bits(wing->wptw));
}

/**
 * vcn_v1_0_dec_wing_insewt_stawt - insewt a stawt command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a stawt command to the wing.
 */
static void vcn_v1_0_dec_wing_insewt_stawt(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, VCN_DEC_CMD_PACKET_STAWT << 1);
}

/**
 * vcn_v1_0_dec_wing_insewt_end - insewt a end command
 *
 * @wing: amdgpu_wing pointew
 *
 * Wwite a end command to the wing.
 */
static void vcn_v1_0_dec_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, VCN_DEC_CMD_PACKET_END << 1);
}

/**
 * vcn_v1_0_dec_wing_emit_fence - emit an fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite a fence and a twap command to the wing.
 */
static void vcn_v1_0_dec_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw, u64 seq,
				     unsigned fwags)
{
	stwuct amdgpu_device *adev = wing->adev;

	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_CONTEXT_ID), 0));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, addw & 0xffffffff);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, uppew_32_bits(addw) & 0xff);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, VCN_DEC_CMD_FENCE << 1);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, 0);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, VCN_DEC_CMD_TWAP << 1);
}

/**
 * vcn_v1_0_dec_wing_emit_ib - execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwieve vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite wing commands to execute the indiwect buffew
 */
static void vcn_v1_0_dec_wing_emit_ib(stwuct amdgpu_wing *wing,
					stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib,
					uint32_t fwags)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WMI_WBC_IB_VMID), 0));
	amdgpu_wing_wwite(wing, vmid);

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WMI_WBC_IB_64BIT_BAW_WOW), 0));
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WMI_WBC_IB_64BIT_BAW_HIGH), 0));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_WBC_IB_SIZE), 0));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void vcn_v1_0_dec_wing_emit_weg_wait(stwuct amdgpu_wing *wing,
					    uint32_t weg, uint32_t vaw,
					    uint32_t mask)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, vaw);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GP_SCWATCH8), 0));
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, VCN_DEC_CMD_WEG_WEAD_COND_WAIT << 1);
}

static void vcn_v1_0_dec_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					    unsigned vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];
	uint32_t data0, data1, mask;

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow wegistew wwite */
	data0 = hub->ctx0_ptb_addw_wo32 + vmid * hub->ctx_addw_distance;
	data1 = wowew_32_bits(pd_addw);
	mask = 0xffffffff;
	vcn_v1_0_dec_wing_emit_weg_wait(wing, data0, data1, mask);
}

static void vcn_v1_0_dec_wing_emit_wweg(stwuct amdgpu_wing *wing,
					uint32_t weg, uint32_t vaw)
{
	stwuct amdgpu_device *adev = wing->adev;

	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA0), 0));
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_DATA1), 0));
	amdgpu_wing_wwite(wing, vaw);
	amdgpu_wing_wwite(wing,
		PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_GPCOM_VCPU_CMD), 0));
	amdgpu_wing_wwite(wing, VCN_DEC_CMD_WWITE_WEG << 1);
}

/**
 * vcn_v1_0_enc_wing_get_wptw - get enc wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe enc wead pointew
 */
static uint64_t vcn_v1_0_enc_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->vcn.inst->wing_enc[0])
		wetuwn WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW);
	ewse
		wetuwn WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2);
}

 /**
 * vcn_v1_0_enc_wing_get_wptw - get enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe enc wwite pointew
 */
static uint64_t vcn_v1_0_enc_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->vcn.inst->wing_enc[0])
		wetuwn WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW);
	ewse
		wetuwn WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2);
}

 /**
 * vcn_v1_0_enc_wing_set_wptw - set enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the enc wwite pointew to the hawdwawe
 */
static void vcn_v1_0_enc_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing == &adev->vcn.inst->wing_enc[0])
		WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW,
			wowew_32_bits(wing->wptw));
	ewse
		WWEG32_SOC15(UVD, 0, mmUVD_WB_WPTW2,
			wowew_32_bits(wing->wptw));
}

/**
 * vcn_v1_0_enc_wing_emit_fence - emit an enc fence & twap command
 *
 * @wing: amdgpu_wing pointew
 * @addw: addwess
 * @seq: sequence numbew
 * @fwags: fence wewated fwags
 *
 * Wwite enc a fence and a twap command to the wing.
 */
static void vcn_v1_0_enc_wing_emit_fence(stwuct amdgpu_wing *wing, u64 addw,
			u64 seq, unsigned fwags)
{
	WAWN_ON(fwags & AMDGPU_FENCE_FWAG_64BIT);

	amdgpu_wing_wwite(wing, VCN_ENC_CMD_FENCE);
	amdgpu_wing_wwite(wing, addw);
	amdgpu_wing_wwite(wing, uppew_32_bits(addw));
	amdgpu_wing_wwite(wing, seq);
	amdgpu_wing_wwite(wing, VCN_ENC_CMD_TWAP);
}

static void vcn_v1_0_enc_wing_insewt_end(stwuct amdgpu_wing *wing)
{
	amdgpu_wing_wwite(wing, VCN_ENC_CMD_END);
}

/**
 * vcn_v1_0_enc_wing_emit_ib - enc execute indiwect buffew
 *
 * @wing: amdgpu_wing pointew
 * @job: job to wetwive vmid fwom
 * @ib: indiwect buffew to execute
 * @fwags: unused
 *
 * Wwite enc wing commands to execute the indiwect buffew
 */
static void vcn_v1_0_enc_wing_emit_ib(stwuct amdgpu_wing *wing,
					stwuct amdgpu_job *job,
					stwuct amdgpu_ib *ib,
					uint32_t fwags)
{
	unsigned vmid = AMDGPU_JOB_GET_VMID(job);

	amdgpu_wing_wwite(wing, VCN_ENC_CMD_IB);
	amdgpu_wing_wwite(wing, vmid);
	amdgpu_wing_wwite(wing, wowew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, uppew_32_bits(ib->gpu_addw));
	amdgpu_wing_wwite(wing, ib->wength_dw);
}

static void vcn_v1_0_enc_wing_emit_weg_wait(stwuct amdgpu_wing *wing,
					    uint32_t weg, uint32_t vaw,
					    uint32_t mask)
{
	amdgpu_wing_wwite(wing, VCN_ENC_CMD_WEG_WAIT);
	amdgpu_wing_wwite(wing, weg << 2);
	amdgpu_wing_wwite(wing, mask);
	amdgpu_wing_wwite(wing, vaw);
}

static void vcn_v1_0_enc_wing_emit_vm_fwush(stwuct amdgpu_wing *wing,
					    unsigned int vmid, uint64_t pd_addw)
{
	stwuct amdgpu_vmhub *hub = &wing->adev->vmhub[wing->vm_hub];

	pd_addw = amdgpu_gmc_emit_fwush_gpu_twb(wing, vmid, pd_addw);

	/* wait fow weg wwites */
	vcn_v1_0_enc_wing_emit_weg_wait(wing, hub->ctx0_ptb_addw_wo32 +
					vmid * hub->ctx_addw_distance,
					wowew_32_bits(pd_addw), 0xffffffff);
}

static void vcn_v1_0_enc_wing_emit_wweg(stwuct amdgpu_wing *wing,
					uint32_t weg, uint32_t vaw)
{
	amdgpu_wing_wwite(wing, VCN_ENC_CMD_WEG_WWITE);
	amdgpu_wing_wwite(wing,	weg << 2);
	amdgpu_wing_wwite(wing, vaw);
}

static int vcn_v1_0_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

static int vcn_v1_0_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	DWM_DEBUG("IH: VCN TWAP\n");

	switch (entwy->swc_id) {
	case 124:
		amdgpu_fence_pwocess(&adev->vcn.inst->wing_dec);
		bweak;
	case 119:
		amdgpu_fence_pwocess(&adev->vcn.inst->wing_enc[0]);
		bweak;
	case 120:
		amdgpu_fence_pwocess(&adev->vcn.inst->wing_enc[1]);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static void vcn_v1_0_dec_wing_insewt_nop(stwuct amdgpu_wing *wing, uint32_t count)
{
	stwuct amdgpu_device *adev = wing->adev;
	int i;

	WAWN_ON(wing->wptw % 2 || count % 2);

	fow (i = 0; i < count / 2; i++) {
		amdgpu_wing_wwite(wing, PACKET0(SOC15_WEG_OFFSET(UVD, 0, mmUVD_NO_OP), 0));
		amdgpu_wing_wwite(wing, 0);
	}
}

static int vcn_v1_0_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	/* This doesn't actuawwy powewgate the VCN bwock.
	 * That's done in the dpm code via the SMC.  This
	 * just we-inits the bwock as necessawy.  The actuaw
	 * gating stiww happens in the dpm code.  We shouwd
	 * wevisit this when thewe is a cweanew wine between
	 * the smc and the hw bwocks
	 */
	int wet;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (state == adev->vcn.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = vcn_v1_0_stop(adev);
	ewse
		wet = vcn_v1_0_stawt(adev);

	if (!wet)
		adev->vcn.cuw_state = state;
	wetuwn wet;
}

static void vcn_v1_0_idwe_wowk_handwew(stwuct wowk_stwuct *wowk)
{
	stwuct amdgpu_device *adev =
		containew_of(wowk, stwuct amdgpu_device, vcn.idwe_wowk.wowk);
	unsigned int fences = 0, i;

	fow (i = 0; i < adev->vcn.num_enc_wings; ++i)
		fences += amdgpu_fence_count_emitted(&adev->vcn.inst->wing_enc[i]);

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
		stwuct dpg_pause_state new_state;

		if (fences)
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		ewse
			new_state.fw_based = VCN_DPG_STATE__UNPAUSE;

		if (amdgpu_fence_count_emitted(adev->jpeg.inst->wing_dec))
			new_state.jpeg = VCN_DPG_STATE__PAUSE;
		ewse
			new_state.jpeg = VCN_DPG_STATE__UNPAUSE;

		adev->vcn.pause_dpg_mode(adev, 0, &new_state);
	}

	fences += amdgpu_fence_count_emitted(adev->jpeg.inst->wing_dec);
	fences += amdgpu_fence_count_emitted(&adev->vcn.inst->wing_dec);

	if (fences == 0) {
		amdgpu_gfx_off_ctww(adev, twue);
		if (adev->pm.dpm_enabwed)
			amdgpu_dpm_enabwe_uvd(adev, fawse);
		ewse
			amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_VCN,
			       AMD_PG_STATE_GATE);
	} ewse {
		scheduwe_dewayed_wowk(&adev->vcn.idwe_wowk, VCN_IDWE_TIMEOUT);
	}
}

static void vcn_v1_0_wing_begin_use(stwuct amdgpu_wing *wing)
{
	stwuct	amdgpu_device *adev = wing->adev;
	boow set_cwocks = !cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	mutex_wock(&adev->vcn.vcn1_jpeg1_wowkawound);

	if (amdgpu_fence_wait_empty(wing->adev->jpeg.inst->wing_dec))
		DWM_EWWOW("VCN dec: jpeg dec wing may not be empty\n");

	vcn_v1_0_set_pg_fow_begin_use(wing, set_cwocks);

}

void vcn_v1_0_set_pg_fow_begin_use(stwuct amdgpu_wing *wing, boow set_cwocks)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (set_cwocks) {
		amdgpu_gfx_off_ctww(adev, fawse);
		if (adev->pm.dpm_enabwed)
			amdgpu_dpm_enabwe_uvd(adev, twue);
		ewse
			amdgpu_device_ip_set_powewgating_state(adev, AMD_IP_BWOCK_TYPE_VCN,
			       AMD_PG_STATE_UNGATE);
	}

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
		stwuct dpg_pause_state new_state;
		unsigned int fences = 0, i;

		fow (i = 0; i < adev->vcn.num_enc_wings; ++i)
			fences += amdgpu_fence_count_emitted(&adev->vcn.inst->wing_enc[i]);

		if (fences)
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		ewse
			new_state.fw_based = VCN_DPG_STATE__UNPAUSE;

		if (amdgpu_fence_count_emitted(adev->jpeg.inst->wing_dec))
			new_state.jpeg = VCN_DPG_STATE__PAUSE;
		ewse
			new_state.jpeg = VCN_DPG_STATE__UNPAUSE;

		if (wing->funcs->type == AMDGPU_WING_TYPE_VCN_ENC)
			new_state.fw_based = VCN_DPG_STATE__PAUSE;
		ewse if (wing->funcs->type == AMDGPU_WING_TYPE_VCN_JPEG)
			new_state.jpeg = VCN_DPG_STATE__PAUSE;

		adev->vcn.pause_dpg_mode(adev, 0, &new_state);
	}
}

void vcn_v1_0_wing_end_use(stwuct amdgpu_wing *wing)
{
	scheduwe_dewayed_wowk(&wing->adev->vcn.idwe_wowk, VCN_IDWE_TIMEOUT);
	mutex_unwock(&wing->adev->vcn.vcn1_jpeg1_wowkawound);
}

static const stwuct amd_ip_funcs vcn_v1_0_ip_funcs = {
	.name = "vcn_v1_0",
	.eawwy_init = vcn_v1_0_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vcn_v1_0_sw_init,
	.sw_fini = vcn_v1_0_sw_fini,
	.hw_init = vcn_v1_0_hw_init,
	.hw_fini = vcn_v1_0_hw_fini,
	.suspend = vcn_v1_0_suspend,
	.wesume = vcn_v1_0_wesume,
	.is_idwe = vcn_v1_0_is_idwe,
	.wait_fow_idwe = vcn_v1_0_wait_fow_idwe,
	.check_soft_weset = NUWW /* vcn_v1_0_check_soft_weset */,
	.pwe_soft_weset = NUWW /* vcn_v1_0_pwe_soft_weset */,
	.soft_weset = NUWW /* vcn_v1_0_soft_weset */,
	.post_soft_weset = NUWW /* vcn_v1_0_post_soft_weset */,
	.set_cwockgating_state = vcn_v1_0_set_cwockgating_state,
	.set_powewgating_state = vcn_v1_0_set_powewgating_state,
};

/*
 * It is a hawdwawe issue that VCN can't handwe a GTT TMZ buffew on
 * CHIP_WAVEN sewies ASIC. Move such a GTT TMZ buffew to VWAM domain
 * befowe command submission as a wowkawound.
 */
static int vcn_v1_0_vawidate_bo(stwuct amdgpu_cs_pawsew *pawsew,
				stwuct amdgpu_job *job,
				uint64_t addw)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct amdgpu_fpwiv *fpwiv = pawsew->fiwp->dwivew_pwiv;
	stwuct amdgpu_vm *vm = &fpwiv->vm;
	stwuct amdgpu_bo_va_mapping *mapping;
	stwuct amdgpu_bo *bo;
	int w;

	addw &= AMDGPU_GMC_HOWE_MASK;
	if (addw & 0x7) {
		DWM_EWWOW("VCN messages must be 8 byte awigned!\n");
		wetuwn -EINVAW;
	}

	mapping = amdgpu_vm_bo_wookup_mapping(vm, addw/AMDGPU_GPU_PAGE_SIZE);
	if (!mapping || !mapping->bo_va || !mapping->bo_va->base.bo)
		wetuwn -EINVAW;

	bo = mapping->bo_va->base.bo;
	if (!(bo->fwags & AMDGPU_GEM_CWEATE_ENCWYPTED))
		wetuwn 0;

	amdgpu_bo_pwacement_fwom_domain(bo, AMDGPU_GEM_DOMAIN_VWAM);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (w) {
		DWM_EWWOW("Faiwed to vawidate the VCN message BO (%d)!\n", w);
		wetuwn w;
	}

	wetuwn w;
}

static int vcn_v1_0_wing_patch_cs_in_pwace(stwuct amdgpu_cs_pawsew *p,
					   stwuct amdgpu_job *job,
					   stwuct amdgpu_ib *ib)
{
	uint32_t msg_wo = 0, msg_hi = 0;
	int i, w;

	if (!(ib->fwags & AMDGPU_IB_FWAGS_SECUWE))
		wetuwn 0;

	fow (i = 0; i < ib->wength_dw; i += 2) {
		uint32_t weg = amdgpu_ib_get_vawue(ib, i);
		uint32_t vaw = amdgpu_ib_get_vawue(ib, i + 1);

		if (weg == PACKET0(p->adev->vcn.intewnaw.data0, 0)) {
			msg_wo = vaw;
		} ewse if (weg == PACKET0(p->adev->vcn.intewnaw.data1, 0)) {
			msg_hi = vaw;
		} ewse if (weg == PACKET0(p->adev->vcn.intewnaw.cmd, 0)) {
			w = vcn_v1_0_vawidate_bo(p, job,
						 ((u64)msg_hi) << 32 | msg_wo);
			if (w)
				wetuwn w;
		}
	}

	wetuwn 0;
}

static const stwuct amdgpu_wing_funcs vcn_v1_0_dec_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_DEC,
	.awign_mask = 0xf,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.secuwe_submission_suppowted = twue,
	.get_wptw = vcn_v1_0_dec_wing_get_wptw,
	.get_wptw = vcn_v1_0_dec_wing_get_wptw,
	.set_wptw = vcn_v1_0_dec_wing_set_wptw,
	.patch_cs_in_pwace = vcn_v1_0_wing_patch_cs_in_pwace,
	.emit_fwame_size =
		6 + 6 + /* hdp invawidate / fwush */
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 6 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 8 +
		8 + /* vcn_v1_0_dec_wing_emit_vm_fwush */
		14 + 14 + /* vcn_v1_0_dec_wing_emit_fence x2 vm fence */
		6,
	.emit_ib_size = 8, /* vcn_v1_0_dec_wing_emit_ib */
	.emit_ib = vcn_v1_0_dec_wing_emit_ib,
	.emit_fence = vcn_v1_0_dec_wing_emit_fence,
	.emit_vm_fwush = vcn_v1_0_dec_wing_emit_vm_fwush,
	.test_wing = amdgpu_vcn_dec_wing_test_wing,
	.test_ib = amdgpu_vcn_dec_wing_test_ib,
	.insewt_nop = vcn_v1_0_dec_wing_insewt_nop,
	.insewt_stawt = vcn_v1_0_dec_wing_insewt_stawt,
	.insewt_end = vcn_v1_0_dec_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = vcn_v1_0_wing_begin_use,
	.end_use = vcn_v1_0_wing_end_use,
	.emit_wweg = vcn_v1_0_dec_wing_emit_wweg,
	.emit_weg_wait = vcn_v1_0_dec_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static const stwuct amdgpu_wing_funcs vcn_v1_0_enc_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_ENC,
	.awign_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.suppowt_64bit_ptws = fawse,
	.no_usew_fence = twue,
	.get_wptw = vcn_v1_0_enc_wing_get_wptw,
	.get_wptw = vcn_v1_0_enc_wing_get_wptw,
	.set_wptw = vcn_v1_0_enc_wing_set_wptw,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 4 +
		4 + /* vcn_v1_0_enc_wing_emit_vm_fwush */
		5 + 5 + /* vcn_v1_0_enc_wing_emit_fence x2 vm fence */
		1, /* vcn_v1_0_enc_wing_insewt_end */
	.emit_ib_size = 5, /* vcn_v1_0_enc_wing_emit_ib */
	.emit_ib = vcn_v1_0_enc_wing_emit_ib,
	.emit_fence = vcn_v1_0_enc_wing_emit_fence,
	.emit_vm_fwush = vcn_v1_0_enc_wing_emit_vm_fwush,
	.test_wing = amdgpu_vcn_enc_wing_test_wing,
	.test_ib = amdgpu_vcn_enc_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.insewt_end = vcn_v1_0_enc_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = vcn_v1_0_wing_begin_use,
	.end_use = vcn_v1_0_wing_end_use,
	.emit_wweg = vcn_v1_0_enc_wing_emit_wweg,
	.emit_weg_wait = vcn_v1_0_enc_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

static void vcn_v1_0_set_dec_wing_funcs(stwuct amdgpu_device *adev)
{
	adev->vcn.inst->wing_dec.funcs = &vcn_v1_0_dec_wing_vm_funcs;
	DWM_INFO("VCN decode is enabwed in VM mode\n");
}

static void vcn_v1_0_set_enc_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vcn.num_enc_wings; ++i)
		adev->vcn.inst->wing_enc[i].funcs = &vcn_v1_0_enc_wing_vm_funcs;

	DWM_INFO("VCN encode is enabwed in VM mode\n");
}

static const stwuct amdgpu_iwq_swc_funcs vcn_v1_0_iwq_funcs = {
	.set = vcn_v1_0_set_intewwupt_state,
	.pwocess = vcn_v1_0_pwocess_intewwupt,
};

static void vcn_v1_0_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	adev->vcn.inst->iwq.num_types = adev->vcn.num_enc_wings + 2;
	adev->vcn.inst->iwq.funcs = &vcn_v1_0_iwq_funcs;
}

const stwuct amdgpu_ip_bwock_vewsion vcn_v1_0_ip_bwock = {
		.type = AMD_IP_BWOCK_TYPE_VCN,
		.majow = 1,
		.minow = 0,
		.wev = 0,
		.funcs = &vcn_v1_0_ip_funcs,
};
