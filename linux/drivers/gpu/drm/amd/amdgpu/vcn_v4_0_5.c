/*
 * Copywight 2023 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu_vcn.h"
#incwude "amdgpu_pm.h"
#incwude "amdgpu_cs.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "soc15_hw_ip.h"
#incwude "vcn_v2_0.h"
#incwude "mmsch_v4_0.h"
#incwude "vcn_v4_0_5.h"

#incwude "vcn/vcn_4_0_5_offset.h"
#incwude "vcn/vcn_4_0_5_sh_mask.h"
#incwude "ivswcid/vcn/iwqswcs_vcn_4_0.h"

#incwude <dwm/dwm_dwv.h>

#define mmUVD_DPG_WMA_CTW							wegUVD_DPG_WMA_CTW
#define mmUVD_DPG_WMA_CTW_BASE_IDX					wegUVD_DPG_WMA_CTW_BASE_IDX
#define mmUVD_DPG_WMA_DATA							wegUVD_DPG_WMA_DATA
#define mmUVD_DPG_WMA_DATA_BASE_IDX					wegUVD_DPG_WMA_DATA_BASE_IDX

#define VCN_VID_SOC_ADDWESS_2_0						0x1fb00
#define VCN1_VID_SOC_ADDWESS_3_0					0x48300

#define VCN_HAWVEST_MMSCH							0

#define WDECODE_MSG_CWEATE							0x00000000
#define WDECODE_MESSAGE_CWEATE						0x00000001

static int amdgpu_ih_cwientid_vcns[] = {
	SOC15_IH_CWIENTID_VCN,
	SOC15_IH_CWIENTID_VCN1
};

static void vcn_v4_0_5_set_unified_wing_funcs(stwuct amdgpu_device *adev);
static void vcn_v4_0_5_set_iwq_funcs(stwuct amdgpu_device *adev);
static int vcn_v4_0_5_set_powewgating_state(void *handwe,
		enum amd_powewgating_state state);
static int vcn_v4_0_5_pause_dpg_mode(stwuct amdgpu_device *adev,
		int inst_idx, stwuct dpg_pause_state *new_state);
static void vcn_v4_0_5_unified_wing_set_wptw(stwuct amdgpu_wing *wing);

/**
 * vcn_v4_0_5_eawwy_init - set function pointews and woad micwocode
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 * Woad micwocode fwom fiwesystem
 */
static int vcn_v4_0_5_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* we-use enc wing as unified wing */
	adev->vcn.num_enc_wings = 1;
	vcn_v4_0_5_set_unified_wing_funcs(adev);
	vcn_v4_0_5_set_iwq_funcs(adev);

	wetuwn amdgpu_vcn_eawwy_init(adev);
}

/**
 * vcn_v4_0_5_sw_init - sw init fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int vcn_v4_0_5_sw_init(void *handwe)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, w;

	w = amdgpu_vcn_sw_init(adev);
	if (w)
		wetuwn w;

	amdgpu_vcn_setup_ucode(adev);

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;

		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		atomic_set(&adev->vcn.inst[i].sched_scowe, 0);

		/* VCN UNIFIED TWAP */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_vcns[i],
				VCN_4_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE, &adev->vcn.inst[i].iwq);
		if (w)
			wetuwn w;

		/* VCN POISON TWAP */
		w = amdgpu_iwq_add_id(adev, amdgpu_ih_cwientid_vcns[i],
				VCN_4_0__SWCID_UVD_POISON, &adev->vcn.inst[i].iwq);
		if (w)
			wetuwn w;

		wing = &adev->vcn.inst[i].wing_enc[0];
		wing->use_doowbeww = twue;
		if (amdgpu_swiov_vf(adev))
			wing->doowbeww_index = (adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
						i * (adev->vcn.num_enc_wings + 1) + 1;
		ewse
			wing->doowbeww_index = (adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
						2 + 8 * i;
		wing->vm_hub = AMDGPU_MMHUB0(0);
		spwintf(wing->name, "vcn_unified_%d", i);

		w = amdgpu_wing_init(adev, wing, 512, &adev->vcn.inst[i].iwq, 0,
				AMDGPU_WING_PWIO_0, &adev->vcn.inst[i].sched_scowe);
		if (w)
			wetuwn w;

		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
		fw_shawed->pwesent_fwag_0 = cpu_to_we32(AMDGPU_FW_SHAWED_FWAG_0_UNIFIED_QUEUE);
		fw_shawed->sq.is_enabwed = 1;

		fw_shawed->pwesent_fwag_0 |= cpu_to_we32(AMDGPU_VCN_SMU_DPM_INTEWFACE_FWAG);
		fw_shawed->smu_dpm_intewface.smu_intewface_type = (adev->fwags & AMD_IS_APU) ?
			AMDGPU_VCN_SMU_DPM_INTEWFACE_APU : AMDGPU_VCN_SMU_DPM_INTEWFACE_DGPU;

		if (amdgpu_swiov_vf(adev))
			fw_shawed->pwesent_fwag_0 |= cpu_to_we32(AMDGPU_VCN_VF_WB_SETUP_FWAG);

		if (amdgpu_vcnfw_wog)
			amdgpu_vcn_fwwog_init(&adev->vcn.inst[i]);
	}

	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_viwt_awwoc_mm_tabwe(adev);
		if (w)
			wetuwn w;
	}

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)
		adev->vcn.pause_dpg_mode = vcn_v4_0_5_pause_dpg_mode;

	wetuwn 0;
}

/**
 * vcn_v4_0_5_sw_fini - sw fini fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * VCN suspend and fwee up sw awwocation
 */
static int vcn_v4_0_5_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, w, idx;

	if (dwm_dev_entew(adev_to_dwm(adev), &idx)) {
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;

			if (adev->vcn.hawvest_config & (1 << i))
				continue;

			fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
			fw_shawed->pwesent_fwag_0 = 0;
			fw_shawed->sq.is_enabwed = 0;
		}

		dwm_dev_exit(idx);
	}

	if (amdgpu_swiov_vf(adev))
		amdgpu_viwt_fwee_mm_tabwe(adev);

	w = amdgpu_vcn_suspend(adev);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_sw_fini(adev);

	wetuwn w;
}

/**
 * vcn_v4_0_5_hw_init - stawt and test VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int vcn_v4_0_5_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, w;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		wing = &adev->vcn.inst[i].wing_enc[0];

		adev->nbio.funcs->vcn_doowbeww_wange(adev, wing->use_doowbeww,
				((adev->doowbeww_index.vcn.vcn_wing0_1 << 1) + 8 * i), i);

		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			goto done;
	}

done:
	if (!w)
		DWM_INFO("VCN decode and encode initiawized successfuwwy(undew %s).\n",
			(adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)?"DPG Mode":"SPG Mode");

	wetuwn w;
}

/**
 * vcn_v4_0_5_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the VCN bwock, mawk wing as not weady any mowe
 */
static int vcn_v4_0_5_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i;

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;
		if (!amdgpu_swiov_vf(adev)) {
			if ((adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) ||
				(adev->vcn.cuw_state != AMD_PG_STATE_GATE &&
				WWEG32_SOC15(VCN, i, wegUVD_STATUS))) {
				vcn_v4_0_5_set_powewgating_state(adev, AMD_PG_STATE_GATE);
			}
		}
	}

	wetuwn 0;
}

/**
 * vcn_v4_0_5_suspend - suspend VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend VCN bwock
 */
static int vcn_v4_0_5_suspend(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = vcn_v4_0_5_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_suspend(adev);

	wetuwn w;
}

/**
 * vcn_v4_0_5_wesume - wesume VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init VCN bwock
 */
static int vcn_v4_0_5_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	w = vcn_v4_0_5_hw_init(adev);

	wetuwn w;
}

/**
 * vcn_v4_0_5_mc_wesume - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Wet the VCN memowy contwowwew know it's offsets
 */
static void vcn_v4_0_5_mc_wesume(stwuct amdgpu_device *adev, int inst)
{
	uint32_t offset, size;
	const stwuct common_fiwmwawe_headew *hdw;

	hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;
	size = AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(hdw->ucode_size_bytes) + 8);

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst].tmw_mc_addw_wo));
		WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst].tmw_mc_addw_hi));
		WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	} ewse {
		WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			wowew_32_bits(adev->vcn.inst[inst].gpu_addw));
		WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			uppew_32_bits(adev->vcn.inst[inst].gpu_addw));
		offset = size;
		WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_OFFSET0, AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
	}
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_SIZE0, size);

	/* cache window 1: stack */
	WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst].gpu_addw + offset));
	WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst].gpu_addw + offset));
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_OFFSET1, 0);
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_SIZE1, AMDGPU_VCN_STACK_SIZE);

	/* cache window 2: context */
	WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_OFFSET2, 0);
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_CACHE_SIZE2, AMDGPU_VCN_CONTEXT_SIZE);

	/* non-cache window */
	WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_NC0_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst].fw_shawed.gpu_addw));
	WWEG32_SOC15(VCN, inst, wegUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst].fw_shawed.gpu_addw));
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_NONCACHE_OFFSET0, 0);
	WWEG32_SOC15(VCN, inst, wegUVD_VCPU_NONCACHE_SIZE0,
		AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_vcn4_fw_shawed)));
}

/**
 * vcn_v4_0_5_mc_wesume_dpg_mode - memowy contwowwew pwogwamming fow dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 * @indiwect: indiwectwy wwite swam
 *
 * Wet the VCN memowy contwowwew know it's offsets with dpg mode
 */
static void vcn_v4_0_5_mc_wesume_dpg_mode(stwuct amdgpu_device *adev, int inst_idx, boow indiwect)
{
	uint32_t offset, size;
	const stwuct common_fiwmwawe_headew *hdw;

	hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;
	size = AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(hdw->ucode_size_bytes) + 8);

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (!indiwect) {
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].tmw_mc_addw_wo),
			0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst_idx].tmw_mc_addw_hi),
			0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, wegUVD_VCPU_CACHE_OFFSET0), 0, 0, indiwect);
		} ewse {
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW), 0, 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH), 0, 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, inst_idx, wegUVD_VCPU_CACHE_OFFSET0), 0, 0, indiwect);
		}
		offset = 0;
	} ewse {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw), 0, indiwect);
		offset = size;
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_VCPU_CACHE_OFFSET0),
			AMDGPU_UVD_FIWMWAWE_OFFSET >> 3, 0, indiwect);
	}

	if (!indiwect)
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_VCPU_CACHE_SIZE0), size, 0, indiwect);
	ewse
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_VCPU_CACHE_SIZE0), 0, 0, indiwect);

	/* cache window 1: stack */
	if (!indiwect) {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_VCPU_CACHE_OFFSET1), 0, 0, indiwect);
	} ewse {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW), 0, 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH), 0, 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, inst_idx, wegUVD_VCPU_CACHE_OFFSET1), 0, 0, indiwect);
	}

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE, 0, indiwect);

	/* cache window 2: context */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW),
		wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE),
		0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH),
		uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset + AMDGPU_VCN_STACK_SIZE),
		0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_CACHE_OFFSET2), 0, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE, 0, indiwect);

	/* non-cache window */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_WMI_VCPU_NC0_64BIT_BAW_WOW),
		wowew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH),
		uppew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_NONCACHE_OFFSET0), 0, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_NONCACHE_SIZE0),
		AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_vcn4_fw_shawed)), 0, indiwect);

	/* VCN gwobaw tiwing wegistews */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_GFX10_ADDW_CONFIG), adev->gfx.config.gb_addw_config, 0, indiwect);
}

/**
 * vcn_v4_0_5_disabwe_static_powew_gating - disabwe VCN static powew gating
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Disabwe static powew gating fow VCN bwock
 */
static void vcn_v4_0_5_disabwe_static_powew_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data = 0;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN) {
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
					1 << UVD_IPX_DWDO_CONFIG__ONO2_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS, 0,
					UVD_IPX_DWDO_STATUS__ONO2_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
					2 << UVD_IPX_DWDO_CONFIG__ONO3_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
					1 << UVD_IPX_DWDO_STATUS__ONO3_PWW_STATUS__SHIFT,
					UVD_IPX_DWDO_STATUS__ONO3_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
					2 << UVD_IPX_DWDO_CONFIG__ONO4_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
					1 << UVD_IPX_DWDO_STATUS__ONO4_PWW_STATUS__SHIFT,
					UVD_IPX_DWDO_STATUS__ONO4_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
					2 << UVD_IPX_DWDO_CONFIG__ONO5_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
					1 << UVD_IPX_DWDO_STATUS__ONO5_PWW_STATUS__SHIFT,
					UVD_IPX_DWDO_STATUS__ONO5_PWW_STATUS_MASK);
	} ewse {
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			1 << UVD_IPX_DWDO_CONFIG__ONO2_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			0, UVD_IPX_DWDO_STATUS__ONO2_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			1 << UVD_IPX_DWDO_CONFIG__ONO3_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			0, UVD_IPX_DWDO_STATUS__ONO3_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			1 << UVD_IPX_DWDO_CONFIG__ONO4_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			0, UVD_IPX_DWDO_STATUS__ONO4_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			1 << UVD_IPX_DWDO_CONFIG__ONO5_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			0, UVD_IPX_DWDO_STATUS__ONO5_PWW_STATUS_MASK);
	}

	data = WWEG32_SOC15(VCN, inst, wegUVD_POWEW_STATUS);
	data &= ~0x103;
	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN)
		data |= UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON |
			UVD_POWEW_STATUS__UVD_PG_EN_MASK;
	WWEG32_SOC15(VCN, inst, wegUVD_POWEW_STATUS, data);
}

/**
 * vcn_v4_0_5_enabwe_static_powew_gating - enabwe VCN static powew gating
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Enabwe static powew gating fow VCN bwock
 */
static void vcn_v4_0_5_enabwe_static_powew_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN) {
		/* Befowe powew off, this indicatow has to be tuwned on */
		data = WWEG32_SOC15(VCN, inst, wegUVD_POWEW_STATUS);
		data &= ~UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK;
		data |= UVD_POWEW_STATUS__UVD_POWEW_STATUS_TIWES_OFF;
		WWEG32_SOC15(VCN, inst, wegUVD_POWEW_STATUS, data);

		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			2 << UVD_IPX_DWDO_CONFIG__ONO5_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			1 << UVD_IPX_DWDO_STATUS__ONO5_PWW_STATUS__SHIFT,
			UVD_IPX_DWDO_STATUS__ONO5_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			2 << UVD_IPX_DWDO_CONFIG__ONO4_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			1 << UVD_IPX_DWDO_STATUS__ONO4_PWW_STATUS__SHIFT,
			UVD_IPX_DWDO_STATUS__ONO4_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			2 << UVD_IPX_DWDO_CONFIG__ONO3_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			1 << UVD_IPX_DWDO_STATUS__ONO3_PWW_STATUS__SHIFT,
			UVD_IPX_DWDO_STATUS__ONO3_PWW_STATUS_MASK);
		WWEG32_SOC15(VCN, inst, wegUVD_IPX_DWDO_CONFIG,
			2 << UVD_IPX_DWDO_CONFIG__ONO2_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_IPX_DWDO_STATUS,
			1 << UVD_IPX_DWDO_STATUS__ONO2_PWW_STATUS__SHIFT,
			UVD_IPX_DWDO_STATUS__ONO2_PWW_STATUS_MASK);
	}
}

/**
 * vcn_v4_0_5_disabwe_cwock_gating - disabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Disabwe cwock gating fow VCN bwock
 */
static void vcn_v4_0_5_disabwe_cwock_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		wetuwn;

	/* VCN disabwe CGC */
	data = WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW);
	data &= ~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, wegUVD_CGC_GATE);
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
		| UVD_CGC_GATE__MMSCH_MASK);

	WWEG32_SOC15(VCN, inst, wegUVD_CGC_GATE, data);
	SOC15_WAIT_ON_WWEG(VCN, inst, wegUVD_CGC_GATE, 0,  0xFFFFFFFF);

	data = WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW);
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
		| UVD_CGC_CTWW__MMSCH_MODE_MASK);
	WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, wegUVD_SUVD_CGC_GATE);
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
	WWEG32_SOC15(VCN, inst, wegUVD_SUVD_CGC_GATE, data);

	data = WWEG32_SOC15(VCN, inst, wegUVD_SUVD_CGC_CTWW);
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
	WWEG32_SOC15(VCN, inst, wegUVD_SUVD_CGC_CTWW, data);
}

/**
 * vcn_v4_0_5_disabwe_cwock_gating_dpg_mode - disabwe VCN cwock gating dpg mode
 *
 * @adev: amdgpu_device pointew
 * @swam_sew: swam sewect
 * @inst_idx: instance numbew index
 * @indiwect: indiwectwy wwite swam
 *
 * Disabwe cwock gating fow VCN bwock with dpg mode
 */
static void vcn_v4_0_5_disabwe_cwock_gating_dpg_mode(stwuct amdgpu_device *adev, uint8_t swam_sew,
		int inst_idx, uint8_t indiwect)
{
	uint32_t weg_data = 0;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		wetuwn;

	/* enabwe sw cwock gating contwow */
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
		 UVD_CGC_CTWW__VCPU_MODE_MASK);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_CGC_CTWW), weg_data, swam_sew, indiwect);

	/* tuwn off cwock gating */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_CGC_GATE), 0, swam_sew, indiwect);

	/* tuwn on SUVD cwock gating */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_SUVD_CGC_GATE), 1, swam_sew, indiwect);

	/* tuwn on sw mode in UVD_SUVD_CGC_CTWW */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_SUVD_CGC_CTWW), 0, swam_sew, indiwect);
}

/**
 * vcn_v4_0_5_enabwe_cwock_gating - enabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 * @inst: instance numbew
 *
 * Enabwe cwock gating fow VCN bwock
 */
static void vcn_v4_0_5_enabwe_cwock_gating(stwuct amdgpu_device *adev, int inst)
{
	uint32_t data;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		wetuwn;

	/* enabwe VCN CGC */
	data = WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW);
	data |= 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW);
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
		| UVD_CGC_CTWW__MMSCH_MODE_MASK);
	WWEG32_SOC15(VCN, inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, inst, wegUVD_SUVD_CGC_CTWW);
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
	WWEG32_SOC15(VCN, inst, wegUVD_SUVD_CGC_CTWW, data);
}

/**
 * vcn_v4_0_5_stawt_dpg_mode - VCN stawt with dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 * @indiwect: indiwectwy wwite swam
 *
 * Stawt VCN bwock with dpg mode
 */
static int vcn_v4_0_5_stawt_dpg_mode(stwuct amdgpu_device *adev, int inst_idx, boow indiwect)
{
	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed = adev->vcn.inst[inst_idx].fw_shawed.cpu_addw;
	stwuct amdgpu_wing *wing;
	uint32_t tmp;

	/* disabwe wegistew anti-hang mechanism */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, wegUVD_POWEW_STATUS), 1,
		~UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
	/* enabwe dynamic powew gating mode */
	tmp = WWEG32_SOC15(VCN, inst_idx, wegUVD_POWEW_STATUS);
	tmp |= UVD_POWEW_STATUS__UVD_PG_MODE_MASK;
	tmp |= UVD_POWEW_STATUS__UVD_PG_EN_MASK;
	WWEG32_SOC15(VCN, inst_idx, wegUVD_POWEW_STATUS, tmp);

	if (indiwect)
		adev->vcn.inst[inst_idx].dpg_swam_cuww_addw =
					(uint32_t *)adev->vcn.inst[inst_idx].dpg_swam_cpu_addw;

	/* enabwe cwock gating */
	vcn_v4_0_5_disabwe_cwock_gating_dpg_mode(adev, 0, inst_idx, indiwect);

	/* enabwe VCPU cwock */
	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK | UVD_VCPU_CNTW__BWK_WST_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_CNTW), tmp, 0, indiwect);

	/* disabwe mastew intewwupt */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_MASTINT_EN), 0, 0, indiwect);

	/* setup wegUVD_WMI_CTWW */
	tmp = (UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
		UVD_WMI_CTWW__WEQ_MODE_MASK |
		UVD_WMI_CTWW__CWC_WESET_MASK |
		UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
		UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
		UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK |
		(8 << UVD_WMI_CTWW__WWITE_CWEAN_TIMEW__SHIFT) |
		0x00100000W);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_WMI_CTWW), tmp, 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_MPC_CNTW),
		0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT, 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_MPC_SET_MUXA0),
		((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)), 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_MPC_SET_MUXB0),
		 ((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)), 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_MPC_SET_MUX),
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0, indiwect);

	vcn_v4_0_5_mc_wesume_dpg_mode(adev, inst_idx, indiwect);

	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_VCPU_CNTW), tmp, 0, indiwect);

	/* enabwe WMI MC and UMC channews */
	tmp = 0x1f << UVD_WMI_CTWW2__WE_OFWD_MIF_WW_WEQ_NUM__SHIFT;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_WMI_CTWW2), tmp, 0, indiwect);

	/* enabwe mastew intewwupt */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, inst_idx, wegUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, 0, indiwect);


	if (indiwect)
		amdgpu_vcn_psp_update_swam(adev, inst_idx, 0);

	wing = &adev->vcn.inst[inst_idx].wing_enc[0];

	WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_BASE_WO, wing->gpu_addw);
	WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_SIZE, wing->wing_size / 4);

	tmp = WWEG32_SOC15(VCN, inst_idx, wegVCN_WB_ENABWE);
	tmp &= ~(VCN_WB_ENABWE__WB1_EN_MASK);
	WWEG32_SOC15(VCN, inst_idx, wegVCN_WB_ENABWE, tmp);
	fw_shawed->sq.queue_mode |= FW_QUEUE_WING_WESET;
	WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_WPTW, 0);
	WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_WPTW, 0);

	tmp = WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_WPTW);
	WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_WPTW, tmp);
	wing->wptw = WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_WPTW);

	tmp = WWEG32_SOC15(VCN, inst_idx, wegVCN_WB_ENABWE);
	tmp |= VCN_WB_ENABWE__WB1_EN_MASK;
	WWEG32_SOC15(VCN, inst_idx, wegVCN_WB_ENABWE, tmp);
	fw_shawed->sq.queue_mode &= ~(FW_QUEUE_WING_WESET | FW_QUEUE_DPG_HOWD_OFF);

	WWEG32_SOC15(VCN, inst_idx, wegVCN_WB1_DB_CTWW,
			wing->doowbeww_index << VCN_WB1_DB_CTWW__OFFSET__SHIFT |
			VCN_WB1_DB_CTWW__EN_MASK);

	wetuwn 0;
}


/**
 * vcn_v4_0_5_stawt - VCN stawt
 *
 * @adev: amdgpu_device pointew
 *
 * Stawt VCN bwock
 */
static int vcn_v4_0_5_stawt(stwuct amdgpu_device *adev)
{
	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;
	stwuct amdgpu_wing *wing;
	uint32_t tmp;
	int i, j, k, w;

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_uvd(adev, twue);

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;

		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
			w = vcn_v4_0_5_stawt_dpg_mode(adev, i, adev->vcn.indiwect_swam);
			continue;
		}

		/* disabwe VCN powew gating */
		vcn_v4_0_5_disabwe_static_powew_gating(adev, i);

		/* set VCN status busy */
		tmp = WWEG32_SOC15(VCN, i, wegUVD_STATUS) | UVD_STATUS__UVD_BUSY;
		WWEG32_SOC15(VCN, i, wegUVD_STATUS, tmp);

		/*SW cwock gating */
		vcn_v4_0_5_disabwe_cwock_gating(adev, i);

		/* enabwe VCPU cwock */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_VCPU_CNTW),
				UVD_VCPU_CNTW__CWK_EN_MASK, ~UVD_VCPU_CNTW__CWK_EN_MASK);

		/* disabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_MASTINT_EN), 0,
				~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* enabwe WMI MC and UMC channews */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_WMI_CTWW2), 0,
				~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

		tmp = WWEG32_SOC15(VCN, i, wegUVD_SOFT_WESET);
		tmp &= ~UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
		tmp &= ~UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, i, wegUVD_SOFT_WESET, tmp);

		/* setup wegUVD_WMI_CTWW */
		tmp = WWEG32_SOC15(VCN, i, wegUVD_WMI_CTWW);
		WWEG32_SOC15(VCN, i, wegUVD_WMI_CTWW, tmp |
				UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
				UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
				UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
				UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK);

		/* setup wegUVD_MPC_CNTW */
		tmp = WWEG32_SOC15(VCN, i, wegUVD_MPC_CNTW);
		tmp &= ~UVD_MPC_CNTW__WEPWACEMENT_MODE_MASK;
		tmp |= 0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT;
		WWEG32_SOC15(VCN, i, wegUVD_MPC_CNTW, tmp);

		/* setup UVD_MPC_SET_MUXA0 */
		WWEG32_SOC15(VCN, i, wegUVD_MPC_SET_MUXA0,
				((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
				 (0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
				 (0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
				 (0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)));

		/* setup UVD_MPC_SET_MUXB0 */
		WWEG32_SOC15(VCN, i, wegUVD_MPC_SET_MUXB0,
				((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
				 (0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
				 (0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
				 (0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)));

		/* setup UVD_MPC_SET_MUX */
		WWEG32_SOC15(VCN, i, wegUVD_MPC_SET_MUX,
				((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
				 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
				 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));

		vcn_v4_0_5_mc_wesume(adev, i);

		/* VCN gwobaw tiwing wegistews */
		WWEG32_SOC15(VCN, i, wegUVD_GFX10_ADDW_CONFIG,
				adev->gfx.config.gb_addw_config);

		/* unbwock VCPU wegistew access */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_WB_AWB_CTWW), 0,
				~UVD_WB_AWB_CTWW__VCPU_DIS_MASK);

		/* wewease VCPU weset to boot */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_VCPU_CNTW), 0,
				~UVD_VCPU_CNTW__BWK_WST_MASK);

		fow (j = 0; j < 10; ++j) {
			uint32_t status;

			fow (k = 0; k < 100; ++k) {
				status = WWEG32_SOC15(VCN, i, wegUVD_STATUS);
				if (status & 2)
					bweak;
				mdeway(10);
				if (amdgpu_emu_mode == 1)
					msweep(1);
			}

			if (amdgpu_emu_mode == 1) {
				w = -1;
				if (status & 2) {
					w = 0;
					bweak;
				}
			} ewse {
				w = 0;
				if (status & 2)
					bweak;

				dev_eww(adev->dev,
					"VCN[%d] is not wesponding, twying to weset VCPU!!!\n", i);
				WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_VCPU_CNTW),
							UVD_VCPU_CNTW__BWK_WST_MASK,
							~UVD_VCPU_CNTW__BWK_WST_MASK);
				mdeway(10);
				WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_VCPU_CNTW), 0,
						~UVD_VCPU_CNTW__BWK_WST_MASK);

				mdeway(10);
				w = -1;
			}
		}

		if (w) {
			dev_eww(adev->dev, "VCN[%d] is not wesponding, giving up!!!\n", i);
			wetuwn w;
		}

		/* enabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_MASTINT_EN),
				UVD_MASTINT_EN__VCPU_EN_MASK,
				~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* cweaw the busy bit of VCN_STATUS */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_STATUS), 0,
				~(2 << UVD_STATUS__VCPU_WEPOWT__SHIFT));

		wing = &adev->vcn.inst[i].wing_enc[0];
		WWEG32_SOC15(VCN, i, wegVCN_WB1_DB_CTWW,
				wing->doowbeww_index << VCN_WB1_DB_CTWW__OFFSET__SHIFT |
				VCN_WB1_DB_CTWW__EN_MASK);

		WWEG32_SOC15(VCN, i, wegUVD_WB_BASE_WO, wing->gpu_addw);
		WWEG32_SOC15(VCN, i, wegUVD_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(VCN, i, wegUVD_WB_SIZE, wing->wing_size / 4);

		tmp = WWEG32_SOC15(VCN, i, wegVCN_WB_ENABWE);
		tmp &= ~(VCN_WB_ENABWE__WB1_EN_MASK);
		WWEG32_SOC15(VCN, i, wegVCN_WB_ENABWE, tmp);
		fw_shawed->sq.queue_mode |= FW_QUEUE_WING_WESET;
		WWEG32_SOC15(VCN, i, wegUVD_WB_WPTW, 0);
		WWEG32_SOC15(VCN, i, wegUVD_WB_WPTW, 0);

		tmp = WWEG32_SOC15(VCN, i, wegUVD_WB_WPTW);
		WWEG32_SOC15(VCN, i, wegUVD_WB_WPTW, tmp);
		wing->wptw = WWEG32_SOC15(VCN, i, wegUVD_WB_WPTW);

		tmp = WWEG32_SOC15(VCN, i, wegVCN_WB_ENABWE);
		tmp |= VCN_WB_ENABWE__WB1_EN_MASK;
		WWEG32_SOC15(VCN, i, wegVCN_WB_ENABWE, tmp);
		fw_shawed->sq.queue_mode &= ~(FW_QUEUE_WING_WESET | FW_QUEUE_DPG_HOWD_OFF);
	}

	wetuwn 0;
}

/**
 * vcn_v4_0_5_stop_dpg_mode - VCN stop with dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 *
 * Stop VCN bwock with dpg mode
 */
static void vcn_v4_0_5_stop_dpg_mode(stwuct amdgpu_device *adev, int inst_idx)
{
	uint32_t tmp;

	/* Wait fow powew status to be 1 */
	SOC15_WAIT_ON_WWEG(VCN, inst_idx, wegUVD_POWEW_STATUS, 1,
		UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* wait fow wead ptw to be equaw to wwite ptw */
	tmp = WWEG32_SOC15(VCN, inst_idx, wegUVD_WB_WPTW);
	SOC15_WAIT_ON_WWEG(VCN, inst_idx, wegUVD_WB_WPTW, tmp, 0xFFFFFFFF);

	SOC15_WAIT_ON_WWEG(VCN, inst_idx, wegUVD_POWEW_STATUS, 1,
		UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* disabwe dynamic powew gating mode */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, inst_idx, wegUVD_POWEW_STATUS), 0,
		~UVD_POWEW_STATUS__UVD_PG_MODE_MASK);
}

/**
 * vcn_v4_0_5_stop - VCN stop
 *
 * @adev: amdgpu_device pointew
 *
 * Stop VCN bwock
 */
static int vcn_v4_0_5_stop(stwuct amdgpu_device *adev)
{
	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;
	uint32_t tmp;
	int i, w = 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
		fw_shawed->sq.queue_mode |= FW_QUEUE_DPG_HOWD_OFF;

		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
			vcn_v4_0_5_stop_dpg_mode(adev, i);
			continue;
		}

		/* wait fow vcn idwe */
		w = SOC15_WAIT_ON_WWEG(VCN, i, wegUVD_STATUS, UVD_STATUS__IDWE, 0x7);
		if (w)
			wetuwn w;

		tmp = UVD_WMI_STATUS__VCPU_WMI_WWITE_CWEAN_MASK |
			UVD_WMI_STATUS__WEAD_CWEAN_MASK |
			UVD_WMI_STATUS__WWITE_CWEAN_MASK |
			UVD_WMI_STATUS__WWITE_CWEAN_WAW_MASK;
		w = SOC15_WAIT_ON_WWEG(VCN, i, wegUVD_WMI_STATUS, tmp, tmp);
		if (w)
			wetuwn w;

		/* disabwe WMI UMC channew */
		tmp = WWEG32_SOC15(VCN, i, wegUVD_WMI_CTWW2);
		tmp |= UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK;
		WWEG32_SOC15(VCN, i, wegUVD_WMI_CTWW2, tmp);
		tmp = UVD_WMI_STATUS__UMC_WEAD_CWEAN_WAW_MASK |
			UVD_WMI_STATUS__UMC_WWITE_CWEAN_WAW_MASK;
		w = SOC15_WAIT_ON_WWEG(VCN, i, wegUVD_WMI_STATUS, tmp, tmp);
		if (w)
			wetuwn w;

		/* bwock VCPU wegistew access */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_WB_AWB_CTWW),
				UVD_WB_AWB_CTWW__VCPU_DIS_MASK,
				~UVD_WB_AWB_CTWW__VCPU_DIS_MASK);

		/* weset VCPU */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_VCPU_CNTW),
				UVD_VCPU_CNTW__BWK_WST_MASK,
				~UVD_VCPU_CNTW__BWK_WST_MASK);

		/* disabwe VCPU cwock */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, i, wegUVD_VCPU_CNTW), 0,
				~(UVD_VCPU_CNTW__CWK_EN_MASK));

		/* appwy soft weset */
		tmp = WWEG32_SOC15(VCN, i, wegUVD_SOFT_WESET);
		tmp |= UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, i, wegUVD_SOFT_WESET, tmp);
		tmp = WWEG32_SOC15(VCN, i, wegUVD_SOFT_WESET);
		tmp |= UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, i, wegUVD_SOFT_WESET, tmp);

		/* cweaw status */
		WWEG32_SOC15(VCN, i, wegUVD_STATUS, 0);

		/* appwy HW cwock gating */
		vcn_v4_0_5_enabwe_cwock_gating(adev, i);

		/* enabwe VCN powew gating */
		vcn_v4_0_5_enabwe_static_powew_gating(adev, i);
	}

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_uvd(adev, fawse);

	wetuwn 0;
}

/**
 * vcn_v4_0_5_pause_dpg_mode - VCN pause with dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 * @new_state: pause state
 *
 * Pause dpg mode fow VCN bwock
 */
static int vcn_v4_0_5_pause_dpg_mode(stwuct amdgpu_device *adev, int inst_idx,
		stwuct dpg_pause_state *new_state)
{
	uint32_t weg_data = 0;
	int wet_code;

	/* pause/unpause if state is changed */
	if (adev->vcn.inst[inst_idx].pause_state.fw_based != new_state->fw_based) {
		DWM_DEV_DEBUG(adev->dev, "dpg pause state changed %d -> %d",
			adev->vcn.inst[inst_idx].pause_state.fw_based,	new_state->fw_based);
		weg_data = WWEG32_SOC15(VCN, inst_idx, wegUVD_DPG_PAUSE) &
			(~UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

		if (new_state->fw_based == VCN_DPG_STATE__PAUSE) {
			wet_code = SOC15_WAIT_ON_WWEG(VCN, inst_idx, wegUVD_POWEW_STATUS, 0x1,
				UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

			if (!wet_code) {
				/* pause DPG */
				weg_data |= UVD_DPG_PAUSE__NJ_PAUSE_DPG_WEQ_MASK;
				WWEG32_SOC15(VCN, inst_idx, wegUVD_DPG_PAUSE, weg_data);

				/* wait fow ACK */
				SOC15_WAIT_ON_WWEG(VCN, inst_idx, wegUVD_DPG_PAUSE,
					UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK,
					UVD_DPG_PAUSE__NJ_PAUSE_DPG_ACK_MASK);

				SOC15_WAIT_ON_WWEG(VCN, inst_idx, wegUVD_POWEW_STATUS,
					UVD_PGFSM_CONFIG__UVDM_UVDU_PWW_ON,
					UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
			}
		} ewse {
			/* unpause dpg, no need to wait */
			weg_data &= ~UVD_DPG_PAUSE__NJ_PAUSE_DPG_WEQ_MASK;
			WWEG32_SOC15(VCN, inst_idx, wegUVD_DPG_PAUSE, weg_data);
		}
		adev->vcn.inst[inst_idx].pause_state.fw_based = new_state->fw_based;
	}

	wetuwn 0;
}

/**
 * vcn_v4_0_5_unified_wing_get_wptw - get unified wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe unified wead pointew
 */
static uint64_t vcn_v4_0_5_unified_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing != &adev->vcn.inst[wing->me].wing_enc[0])
		DWM_EWWOW("wwong wing id is identified in %s", __func__);

	wetuwn WWEG32_SOC15(VCN, wing->me, wegUVD_WB_WPTW);
}

/**
 * vcn_v4_0_5_unified_wing_get_wptw - get unified wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe unified wwite pointew
 */
static uint64_t vcn_v4_0_5_unified_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing != &adev->vcn.inst[wing->me].wing_enc[0])
		DWM_EWWOW("wwong wing id is identified in %s", __func__);

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;
	ewse
		wetuwn WWEG32_SOC15(VCN, wing->me, wegUVD_WB_WPTW);
}

/**
 * vcn_v4_0_5_unified_wing_set_wptw - set enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the enc wwite pointew to the hawdwawe
 */
static void vcn_v4_0_5_unified_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing != &adev->vcn.inst[wing->me].wing_enc[0])
		DWM_EWWOW("wwong wing id is identified in %s", __func__);

	if (wing->use_doowbeww) {
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32_SOC15(VCN, wing->me, wegUVD_WB_WPTW, wowew_32_bits(wing->wptw));
	}
}

static int vcn_v4_0_5_wimit_sched(stwuct amdgpu_cs_pawsew *p,
				stwuct amdgpu_job *job)
{
	stwuct dwm_gpu_scheduwew **scheds;

	/* The cweate msg must be in the fiwst IB submitted */
	if (atomic_wead(&job->base.entity->fence_seq))
		wetuwn -EINVAW;

	/* if VCN0 is hawvested, we can't suppowt AV1 */
	if (p->adev->vcn.hawvest_config & AMDGPU_VCN_HAWVEST_VCN0)
		wetuwn -EINVAW;

	scheds = p->adev->gpu_sched[AMDGPU_HW_IP_VCN_ENC]
		[AMDGPU_WING_PWIO_0].sched;
	dwm_sched_entity_modify_sched(job->base.entity, scheds, 1);
	wetuwn 0;
}

static int vcn_v4_0_5_dec_msg(stwuct amdgpu_cs_pawsew *p, stwuct amdgpu_job *job,
			    uint64_t addw)
{
	stwuct ttm_opewation_ctx ctx = { fawse, fawse };
	stwuct amdgpu_bo_va_mapping *map;
	uint32_t *msg, num_buffews;
	stwuct amdgpu_bo *bo;
	uint64_t stawt, end;
	unsigned int i;
	void *ptw;
	int w;

	addw &= AMDGPU_GMC_HOWE_MASK;
	w = amdgpu_cs_find_mapping(p, addw, &bo, &map);
	if (w) {
		DWM_EWWOW("Can't find BO fow addw 0x%08wwx\n", addw);
		wetuwn w;
	}

	stawt = map->stawt * AMDGPU_GPU_PAGE_SIZE;
	end = (map->wast + 1) * AMDGPU_GPU_PAGE_SIZE;
	if (addw & 0x7) {
		DWM_EWWOW("VCN messages must be 8 byte awigned!\n");
		wetuwn -EINVAW;
	}

	bo->fwags |= AMDGPU_GEM_CWEATE_CPU_ACCESS_WEQUIWED;
	amdgpu_bo_pwacement_fwom_domain(bo, bo->awwowed_domains);
	w = ttm_bo_vawidate(&bo->tbo, &bo->pwacement, &ctx);
	if (w) {
		DWM_EWWOW("Faiwed vawidating the VCN message BO (%d)!\n", w);
		wetuwn w;
	}

	w = amdgpu_bo_kmap(bo, &ptw);
	if (w) {
		DWM_EWWOW("Faiwed mapping the VCN message (%d)!\n", w);
		wetuwn w;
	}

	msg = ptw + addw - stawt;

	/* Check wength */
	if (msg[1] > end - addw) {
		w = -EINVAW;
		goto out;
	}

	if (msg[3] != WDECODE_MSG_CWEATE)
		goto out;

	num_buffews = msg[2];
	fow (i = 0, msg = &msg[6]; i < num_buffews; ++i, msg += 4) {
		uint32_t offset, size, *cweate;

		if (msg[0] != WDECODE_MESSAGE_CWEATE)
			continue;

		offset = msg[1];
		size = msg[2];

		if (offset + size > end) {
			w = -EINVAW;
			goto out;
		}

		cweate = ptw + addw + offset - stawt;

		/* H264, HEVC and VP9 can wun on any instance */
		if (cweate[0] == 0x7 || cweate[0] == 0x10 || cweate[0] == 0x11)
			continue;

		w = vcn_v4_0_5_wimit_sched(p, job);
		if (w)
			goto out;
	}

out:
	amdgpu_bo_kunmap(bo);
	wetuwn w;
}

#define WADEON_VCN_ENGINE_TYPE_ENCODE			(0x00000002)
#define WADEON_VCN_ENGINE_TYPE_DECODE			(0x00000003)

#define WADEON_VCN_ENGINE_INFO				(0x30000001)
#define WADEON_VCN_ENGINE_INFO_MAX_OFFSET		16

#define WENCODE_ENCODE_STANDAWD_AV1			2
#define WENCODE_IB_PAWAM_SESSION_INIT			0x00000003
#define WENCODE_IB_PAWAM_SESSION_INIT_MAX_OFFSET	64

/* wetuwn the offset in ib if id is found, -1 othewwise
 * to speed up the seawching we onwy seawch upto max_offset
 */
static int vcn_v4_0_5_enc_find_ib_pawam(stwuct amdgpu_ib *ib, uint32_t id, int max_offset)
{
	int i;

	fow (i = 0; i < ib->wength_dw && i < max_offset && ib->ptw[i] >= 8; i += ib->ptw[i]/4) {
		if (ib->ptw[i + 1] == id)
			wetuwn i;
	}
	wetuwn -1;
}

static int vcn_v4_0_5_wing_patch_cs_in_pwace(stwuct amdgpu_cs_pawsew *p,
					   stwuct amdgpu_job *job,
					   stwuct amdgpu_ib *ib)
{
	stwuct amdgpu_wing *wing = amdgpu_job_wing(job);
	stwuct amdgpu_vcn_decode_buffew *decode_buffew;
	uint64_t addw;
	uint32_t vaw;
	int idx;

	/* The fiwst instance can decode anything */
	if (!wing->me)
		wetuwn 0;

	/* WADEON_VCN_ENGINE_INFO is at the top of ib bwock */
	idx = vcn_v4_0_5_enc_find_ib_pawam(ib, WADEON_VCN_ENGINE_INFO,
			WADEON_VCN_ENGINE_INFO_MAX_OFFSET);
	if (idx < 0) /* engine info is missing */
		wetuwn 0;

	vaw = amdgpu_ib_get_vawue(ib, idx + 2); /* WADEON_VCN_ENGINE_TYPE */
	if (vaw == WADEON_VCN_ENGINE_TYPE_DECODE) {
		decode_buffew = (stwuct amdgpu_vcn_decode_buffew *)&ib->ptw[idx + 6];

		if (!(decode_buffew->vawid_buf_fwag  & 0x1))
			wetuwn 0;

		addw = ((u64)decode_buffew->msg_buffew_addwess_hi) << 32 |
			decode_buffew->msg_buffew_addwess_wo;
		wetuwn vcn_v4_0_5_dec_msg(p, job, addw);
	} ewse if (vaw == WADEON_VCN_ENGINE_TYPE_ENCODE) {
		idx = vcn_v4_0_5_enc_find_ib_pawam(ib, WENCODE_IB_PAWAM_SESSION_INIT,
			WENCODE_IB_PAWAM_SESSION_INIT_MAX_OFFSET);
		if (idx >= 0 && ib->ptw[idx + 2] == WENCODE_ENCODE_STANDAWD_AV1)
			wetuwn vcn_v4_0_5_wimit_sched(p, job);
	}
	wetuwn 0;
}

static const stwuct amdgpu_wing_funcs vcn_v4_0_5_unified_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_ENC,
	.awign_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.get_wptw = vcn_v4_0_5_unified_wing_get_wptw,
	.get_wptw = vcn_v4_0_5_unified_wing_get_wptw,
	.set_wptw = vcn_v4_0_5_unified_wing_set_wptw,
	.patch_cs_in_pwace = vcn_v4_0_5_wing_patch_cs_in_pwace,
	.emit_fwame_size =
		SOC15_FWUSH_GPU_TWB_NUM_WWEG * 3 +
		SOC15_FWUSH_GPU_TWB_NUM_WEG_WAIT * 4 +
		4 + /* vcn_v2_0_enc_wing_emit_vm_fwush */
		5 + 5 + /* vcn_v2_0_enc_wing_emit_fence x2 vm fence */
		1, /* vcn_v2_0_enc_wing_insewt_end */
	.emit_ib_size = 5, /* vcn_v2_0_enc_wing_emit_ib */
	.emit_ib = vcn_v2_0_enc_wing_emit_ib,
	.emit_fence = vcn_v2_0_enc_wing_emit_fence,
	.emit_vm_fwush = vcn_v2_0_enc_wing_emit_vm_fwush,
	.test_wing = amdgpu_vcn_enc_wing_test_wing,
	.test_ib = amdgpu_vcn_unified_wing_test_ib,
	.insewt_nop = amdgpu_wing_insewt_nop,
	.insewt_end = vcn_v2_0_enc_wing_insewt_end,
	.pad_ib = amdgpu_wing_genewic_pad_ib,
	.begin_use = amdgpu_vcn_wing_begin_use,
	.end_use = amdgpu_vcn_wing_end_use,
	.emit_wweg = vcn_v2_0_enc_wing_emit_wweg,
	.emit_weg_wait = vcn_v2_0_enc_wing_emit_weg_wait,
	.emit_weg_wwite_weg_wait = amdgpu_wing_emit_weg_wwite_weg_wait_hewpew,
};

/**
 * vcn_v4_0_5_set_unified_wing_funcs - set unified wing functions
 *
 * @adev: amdgpu_device pointew
 *
 * Set unified wing functions
 */
static void vcn_v4_0_5_set_unified_wing_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		adev->vcn.inst[i].wing_enc[0].funcs = &vcn_v4_0_5_unified_wing_vm_funcs;
		adev->vcn.inst[i].wing_enc[0].me = i;

		DWM_INFO("VCN(%d) encode/decode awe enabwed in VM mode\n", i);
	}
}

/**
 * vcn_v4_0_5_is_idwe - check VCN bwock is idwe
 *
 * @handwe: amdgpu_device pointew
 *
 * Check whethew VCN bwock is idwe
 */
static boow vcn_v4_0_5_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 1;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		wet &= (WWEG32_SOC15(VCN, i, wegUVD_STATUS) == UVD_STATUS__IDWE);
	}

	wetuwn wet;
}

/**
 * vcn_v4_0_5_wait_fow_idwe - wait fow VCN bwock idwe
 *
 * @handwe: amdgpu_device pointew
 *
 * Wait fow VCN bwock idwe
 */
static int vcn_v4_0_5_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		wet = SOC15_WAIT_ON_WWEG(VCN, i, wegUVD_STATUS, UVD_STATUS__IDWE,
			UVD_STATUS__IDWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/**
 * vcn_v4_0_5_set_cwockgating_state - set VCN bwock cwockgating state
 *
 * @handwe: amdgpu_device pointew
 * @state: cwock gating state
 *
 * Set VCN bwock cwockgating state
 */
static int vcn_v4_0_5_set_cwockgating_state(void *handwe, enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = (state == AMD_CG_STATE_GATE) ? twue : fawse;
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		if (enabwe) {
			if (WWEG32_SOC15(VCN, i, wegUVD_STATUS) != UVD_STATUS__IDWE)
				wetuwn -EBUSY;
			vcn_v4_0_5_enabwe_cwock_gating(adev, i);
		} ewse {
			vcn_v4_0_5_disabwe_cwock_gating(adev, i);
		}
	}

	wetuwn 0;
}

/**
 * vcn_v4_0_5_set_powewgating_state - set VCN bwock powewgating state
 *
 * @handwe: amdgpu_device pointew
 * @state: powew gating state
 *
 * Set VCN bwock powewgating state
 */
static int vcn_v4_0_5_set_powewgating_state(void *handwe, enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	if (state == adev->vcn.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = vcn_v4_0_5_stop(adev);
	ewse
		wet = vcn_v4_0_5_stawt(adev);

	if (!wet)
		adev->vcn.cuw_state = state;

	wetuwn wet;
}

/**
 * vcn_v4_0_5_pwocess_intewwupt - pwocess VCN bwock intewwupt
 *
 * @adev: amdgpu_device pointew
 * @souwce: intewwupt souwces
 * @entwy: intewwupt entwy fwom cwients and souwces
 *
 * Pwocess VCN bwock intewwupt
 */
static int vcn_v4_0_5_pwocess_intewwupt(stwuct amdgpu_device *adev, stwuct amdgpu_iwq_swc *souwce,
		stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t ip_instance;

	switch (entwy->cwient_id) {
	case SOC15_IH_CWIENTID_VCN:
		ip_instance = 0;
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed cwient id: %d\n", entwy->cwient_id);
		wetuwn 0;
	}

	DWM_DEBUG("IH: VCN TWAP\n");

	switch (entwy->swc_id) {
	case VCN_4_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE:
		amdgpu_fence_pwocess(&adev->vcn.inst[ip_instance].wing_enc[0]);
		bweak;
	case VCN_4_0__SWCID_UVD_POISON:
		amdgpu_vcn_pwocess_poison_iwq(adev, souwce, entwy);
		bweak;
	defauwt:
		DWM_EWWOW("Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs vcn_v4_0_5_iwq_funcs = {
	.pwocess = vcn_v4_0_5_pwocess_intewwupt,
};

/**
 * vcn_v4_0_5_set_iwq_funcs - set VCN bwock intewwupt iwq functions
 *
 * @adev: amdgpu_device pointew
 *
 * Set VCN bwock intewwupt iwq functions
 */
static void vcn_v4_0_5_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->vcn.hawvest_config & (1 << i))
			continue;

		adev->vcn.inst[i].iwq.num_types = adev->vcn.num_enc_wings + 1;
		adev->vcn.inst[i].iwq.funcs = &vcn_v4_0_5_iwq_funcs;
	}
}

static const stwuct amd_ip_funcs vcn_v4_0_5_ip_funcs = {
	.name = "vcn_v4_0_5",
	.eawwy_init = vcn_v4_0_5_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vcn_v4_0_5_sw_init,
	.sw_fini = vcn_v4_0_5_sw_fini,
	.hw_init = vcn_v4_0_5_hw_init,
	.hw_fini = vcn_v4_0_5_hw_fini,
	.suspend = vcn_v4_0_5_suspend,
	.wesume = vcn_v4_0_5_wesume,
	.is_idwe = vcn_v4_0_5_is_idwe,
	.wait_fow_idwe = vcn_v4_0_5_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = vcn_v4_0_5_set_cwockgating_state,
	.set_powewgating_state = vcn_v4_0_5_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion vcn_v4_0_5_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_VCN,
	.majow = 4,
	.minow = 0,
	.wev = 5,
	.funcs = &vcn_v4_0_5_ip_funcs,
};
