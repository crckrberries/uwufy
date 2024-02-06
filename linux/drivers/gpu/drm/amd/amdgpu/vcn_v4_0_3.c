/*
 * Copywight 2022 Advanced Micwo Devices, Inc.
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
#incwude <dwm/dwm_dwv.h>

#incwude "amdgpu.h"
#incwude "amdgpu_vcn.h"
#incwude "amdgpu_pm.h"
#incwude "soc15.h"
#incwude "soc15d.h"
#incwude "soc15_hw_ip.h"
#incwude "vcn_v2_0.h"
#incwude "mmsch_v4_0_3.h"

#incwude "vcn/vcn_4_0_3_offset.h"
#incwude "vcn/vcn_4_0_3_sh_mask.h"
#incwude "ivswcid/vcn/iwqswcs_vcn_4_0.h"

#define mmUVD_DPG_WMA_CTW		wegUVD_DPG_WMA_CTW
#define mmUVD_DPG_WMA_CTW_BASE_IDX	wegUVD_DPG_WMA_CTW_BASE_IDX
#define mmUVD_DPG_WMA_DATA		wegUVD_DPG_WMA_DATA
#define mmUVD_DPG_WMA_DATA_BASE_IDX	wegUVD_DPG_WMA_DATA_BASE_IDX

#define VCN_VID_SOC_ADDWESS_2_0		0x1fb00
#define VCN1_VID_SOC_ADDWESS_3_0	0x48300

static int vcn_v4_0_3_stawt_swiov(stwuct amdgpu_device *adev);
static void vcn_v4_0_3_set_unified_wing_funcs(stwuct amdgpu_device *adev);
static void vcn_v4_0_3_set_iwq_funcs(stwuct amdgpu_device *adev);
static int vcn_v4_0_3_set_powewgating_state(void *handwe,
		enum amd_powewgating_state state);
static int vcn_v4_0_3_pause_dpg_mode(stwuct amdgpu_device *adev,
		int inst_idx, stwuct dpg_pause_state *new_state);
static void vcn_v4_0_3_unified_wing_set_wptw(stwuct amdgpu_wing *wing);
static void vcn_v4_0_3_set_was_funcs(stwuct amdgpu_device *adev);
static void vcn_v4_0_3_enabwe_was(stwuct amdgpu_device *adev,
				  int inst_idx, boow indiwect);
/**
 * vcn_v4_0_3_eawwy_init - set function pointews
 *
 * @handwe: amdgpu_device pointew
 *
 * Set wing and iwq function pointews
 */
static int vcn_v4_0_3_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	/* we-use enc wing as unified wing */
	adev->vcn.num_enc_wings = 1;

	vcn_v4_0_3_set_unified_wing_funcs(adev);
	vcn_v4_0_3_set_iwq_funcs(adev);
	vcn_v4_0_3_set_was_funcs(adev);

	wetuwn amdgpu_vcn_eawwy_init(adev);
}

/**
 * vcn_v4_0_3_sw_init - sw init fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Woad fiwmwawe and sw initiawization
 */
static int vcn_v4_0_3_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, w, vcn_inst;

	w = amdgpu_vcn_sw_init(adev);
	if (w)
		wetuwn w;

	amdgpu_vcn_setup_ucode(adev);

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	/* VCN DEC TWAP */
	w = amdgpu_iwq_add_id(adev, SOC15_IH_CWIENTID_VCN,
		VCN_4_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE, &adev->vcn.inst->iwq);
	if (w)
		wetuwn w;

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;

		vcn_inst = GET_INST(VCN, i);

		wing = &adev->vcn.inst[i].wing_enc[0];
		wing->use_doowbeww = twue;

		if (!amdgpu_swiov_vf(adev))
			wing->doowbeww_index =
				(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
				9 * vcn_inst;
		ewse
			wing->doowbeww_index =
				(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
				32 * vcn_inst;

		wing->vm_hub = AMDGPU_MMHUB0(adev->vcn.inst[i].aid_id);
		spwintf(wing->name, "vcn_unified_%d", adev->vcn.inst[i].aid_id);
		w = amdgpu_wing_init(adev, wing, 512, &adev->vcn.inst->iwq, 0,
				     AMDGPU_WING_PWIO_DEFAUWT,
				     &adev->vcn.inst[i].sched_scowe);
		if (w)
			wetuwn w;

		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
		fw_shawed->pwesent_fwag_0 = cpu_to_we32(AMDGPU_FW_SHAWED_FWAG_0_UNIFIED_QUEUE);
		fw_shawed->sq.is_enabwed = twue;

		if (amdgpu_vcnfw_wog)
			amdgpu_vcn_fwwog_init(&adev->vcn.inst[i]);
	}

	if (amdgpu_swiov_vf(adev)) {
		w = amdgpu_viwt_awwoc_mm_tabwe(adev);
		if (w)
			wetuwn w;
	}

	if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)
		adev->vcn.pause_dpg_mode = vcn_v4_0_3_pause_dpg_mode;

	if (amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__VCN)) {
		w = amdgpu_vcn_was_sw_init(adev);
		if (w) {
			dev_eww(adev->dev, "Faiwed to initiawize vcn was bwock!\n");
			wetuwn w;
		}
	}

	wetuwn 0;
}

/**
 * vcn_v4_0_3_sw_fini - sw fini fow VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * VCN suspend and fwee up sw awwocation
 */
static int vcn_v4_0_3_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, w, idx;

	if (dwm_dev_entew(&adev->ddev, &idx)) {
		fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
			vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;

			fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
			fw_shawed->pwesent_fwag_0 = 0;
			fw_shawed->sq.is_enabwed = cpu_to_we32(fawse);
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
 * vcn_v4_0_3_hw_init - stawt and test VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Initiawize the hawdwawe, boot up the VCPU and do some testing
 */
static int vcn_v4_0_3_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	stwuct amdgpu_wing *wing;
	int i, w, vcn_inst;

	if (amdgpu_swiov_vf(adev)) {
		w = vcn_v4_0_3_stawt_swiov(adev);
		if (w)
			goto done;

		fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
			wing = &adev->vcn.inst[i].wing_enc[0];
			wing->wptw = 0;
			wing->wptw_owd = 0;
			vcn_v4_0_3_unified_wing_set_wptw(wing);
			wing->sched.weady = twue;
		}
	} ewse {
		fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
			vcn_inst = GET_INST(VCN, i);
			wing = &adev->vcn.inst[i].wing_enc[0];

			if (wing->use_doowbeww) {
				adev->nbio.funcs->vcn_doowbeww_wange(
					adev, wing->use_doowbeww,
					(adev->doowbeww_index.vcn.vcn_wing0_1 << 1) +
						9 * vcn_inst,
					adev->vcn.inst[i].aid_id);

				WWEG32_SOC15(
					VCN, GET_INST(VCN, wing->me),
					wegVCN_WB1_DB_CTWW,
					wing->doowbeww_index
							<< VCN_WB1_DB_CTWW__OFFSET__SHIFT |
						VCN_WB1_DB_CTWW__EN_MASK);

				/* Wead DB_CTWW to fwush the wwite DB_CTWW command. */
				WWEG32_SOC15(
					VCN, GET_INST(VCN, wing->me),
					wegVCN_WB1_DB_CTWW);
			}

			w = amdgpu_wing_test_hewpew(wing);
			if (w)
				goto done;
		}
	}

done:
	if (!w)
		DWM_DEV_INFO(adev->dev, "VCN decode initiawized successfuwwy(undew %s).\n",
			(adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG)?"DPG Mode":"SPG Mode");

	wetuwn w;
}

/**
 * vcn_v4_0_3_hw_fini - stop the hawdwawe bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Stop the VCN bwock, mawk wing as not weady any mowe
 */
static int vcn_v4_0_3_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	cancew_dewayed_wowk_sync(&adev->vcn.idwe_wowk);

	if (adev->vcn.cuw_state != AMD_PG_STATE_GATE)
		vcn_v4_0_3_set_powewgating_state(adev, AMD_PG_STATE_GATE);

	wetuwn 0;
}

/**
 * vcn_v4_0_3_suspend - suspend VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * HW fini and suspend VCN bwock
 */
static int vcn_v4_0_3_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = vcn_v4_0_3_hw_fini(adev);
	if (w)
		wetuwn w;

	w = amdgpu_vcn_suspend(adev);

	wetuwn w;
}

/**
 * vcn_v4_0_3_wesume - wesume VCN bwock
 *
 * @handwe: amdgpu_device pointew
 *
 * Wesume fiwmwawe and hw init VCN bwock
 */
static int vcn_v4_0_3_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = amdgpu_vcn_wesume(adev);
	if (w)
		wetuwn w;

	w = vcn_v4_0_3_hw_init(adev);

	wetuwn w;
}

/**
 * vcn_v4_0_3_mc_wesume - memowy contwowwew pwogwamming
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew
 *
 * Wet the VCN memowy contwowwew know it's offsets
 */
static void vcn_v4_0_3_mc_wesume(stwuct amdgpu_device *adev, int inst_idx)
{
	uint32_t offset, size, vcn_inst;
	const stwuct common_fiwmwawe_headew *hdw;

	hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;
	size = AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(hdw->ucode_size_bytes) + 8);

	vcn_inst = GET_INST(VCN, inst_idx);
	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		WWEG32_SOC15(
			VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst_idx]
				 .tmw_mc_addw_wo));
		WWEG32_SOC15(
			VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + inst_idx]
				 .tmw_mc_addw_hi));
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_OFFSET0, 0);
		offset = 0;
	} ewse {
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW,
			     wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw));
		WWEG32_SOC15(VCN, vcn_inst,
			     wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH,
			     uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw));
		offset = size;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_OFFSET0,
			     AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
	}
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_SIZE0, size);

	/* cache window 1: stack */
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW,
		     wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset));
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH,
		     uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset));
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_OFFSET1, 0);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_SIZE1,
		     AMDGPU_VCN_STACK_SIZE);

	/* cache window 2: context */
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW,
		     wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset +
				   AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH,
		     uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset +
				   AMDGPU_VCN_STACK_SIZE));
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_OFFSET2, 0);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_CACHE_SIZE2,
		     AMDGPU_VCN_CONTEXT_SIZE);

	/* non-cache window */
	WWEG32_SOC15(
		VCN, vcn_inst, wegUVD_WMI_VCPU_NC0_64BIT_BAW_WOW,
		wowew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw));
	WWEG32_SOC15(
		VCN, vcn_inst, wegUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH,
		uppew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw));
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_VCPU_NONCACHE_OFFSET0, 0);
	WWEG32_SOC15(
		VCN, vcn_inst, wegUVD_VCPU_NONCACHE_SIZE0,
		AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_vcn4_fw_shawed)));
}

/**
 * vcn_v4_0_3_mc_wesume_dpg_mode - memowy contwowwew pwogwamming fow dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 * @indiwect: indiwectwy wwite swam
 *
 * Wet the VCN memowy contwowwew know it's offsets with dpg mode
 */
static void vcn_v4_0_3_mc_wesume_dpg_mode(stwuct amdgpu_device *adev, int inst_idx, boow indiwect)
{
	uint32_t offset, size;
	const stwuct common_fiwmwawe_headew *hdw;

	hdw = (const stwuct common_fiwmwawe_headew *)adev->vcn.fw->data;
	size = AMDGPU_GPU_PAGE_AWIGN(we32_to_cpu(hdw->ucode_size_bytes) + 8);

	/* cache window 0: fw */
	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		if (!indiwect) {
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
				(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN +
					inst_idx].tmw_mc_addw_wo), 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
				(adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN +
					inst_idx].tmw_mc_addw_hi), 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, wegUVD_VCPU_CACHE_OFFSET0), 0, 0, indiwect);
		} ewse {
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW), 0, 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH), 0, 0, indiwect);
			WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
				VCN, 0, wegUVD_VCPU_CACHE_OFFSET0), 0, 0, indiwect);
		}
		offset = 0;
	} ewse {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw), 0, indiwect);
		offset = size;
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_OFFSET0),
			AMDGPU_UVD_FIWMWAWE_OFFSET >> 3, 0, indiwect);
	}

	if (!indiwect)
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_SIZE0), size, 0, indiwect);
	ewse
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_SIZE0), 0, 0, indiwect);

	/* cache window 1: stack */
	if (!indiwect) {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset), 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_OFFSET1), 0, 0, indiwect);
	} ewse {
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW), 0, 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH), 0, 0, indiwect);
		WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_OFFSET1), 0, 0, indiwect);
	}
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE, 0, indiwect);

	/* cache window 2: context */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset +
				AMDGPU_VCN_STACK_SIZE), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].gpu_addw + offset +
				AMDGPU_VCN_STACK_SIZE), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_OFFSET2), 0, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE, 0, indiwect);

	/* non-cache window */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_NC0_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[inst_idx].fw_shawed.gpu_addw), 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_NONCACHE_OFFSET0), 0, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
			VCN, 0, wegUVD_VCPU_NONCACHE_SIZE0),
			AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_vcn4_fw_shawed)), 0, indiwect);

	/* VCN gwobaw tiwing wegistews */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_GFX8_ADDW_CONFIG), adev->gfx.config.gb_addw_config, 0, indiwect);
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_GFX10_ADDW_CONFIG), adev->gfx.config.gb_addw_config, 0, indiwect);
}

/**
 * vcn_v4_0_3_disabwe_cwock_gating - disabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew
 *
 * Disabwe cwock gating fow VCN bwock
 */
static void vcn_v4_0_3_disabwe_cwock_gating(stwuct amdgpu_device *adev, int inst_idx)
{
	uint32_t data;
	int vcn_inst;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		wetuwn;

	vcn_inst = GET_INST(VCN, inst_idx);

	/* VCN disabwe CGC */
	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW);
	data &= ~UVD_CGC_CTWW__DYN_CWOCK_MODE_MASK;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_GATE);
	data &= ~(UVD_CGC_GATE__SYS_MASK
		| UVD_CGC_GATE__MPEG2_MASK
		| UVD_CGC_GATE__WEGS_MASK
		| UVD_CGC_GATE__WBC_MASK
		| UVD_CGC_GATE__WMI_MC_MASK
		| UVD_CGC_GATE__WMI_UMC_MASK
		| UVD_CGC_GATE__MPC_MASK
		| UVD_CGC_GATE__WBSI_MASK
		| UVD_CGC_GATE__WWBBM_MASK
		| UVD_CGC_GATE__WCB_MASK
		| UVD_CGC_GATE__VCPU_MASK
		| UVD_CGC_GATE__MMSCH_MASK);

	WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_GATE, data);
	SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_CGC_GATE, 0, 0xFFFFFFFF);

	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW);
	data &= ~(UVD_CGC_CTWW__SYS_MODE_MASK
		| UVD_CGC_CTWW__MPEG2_MODE_MASK
		| UVD_CGC_CTWW__WEGS_MODE_MASK
		| UVD_CGC_CTWW__WBC_MODE_MASK
		| UVD_CGC_CTWW__WMI_MC_MODE_MASK
		| UVD_CGC_CTWW__WMI_UMC_MODE_MASK
		| UVD_CGC_CTWW__MPC_MODE_MASK
		| UVD_CGC_CTWW__WBSI_MODE_MASK
		| UVD_CGC_CTWW__WWBBM_MODE_MASK
		| UVD_CGC_CTWW__WCB_MODE_MASK
		| UVD_CGC_CTWW__VCPU_MODE_MASK
		| UVD_CGC_CTWW__MMSCH_MODE_MASK);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_SUVD_CGC_GATE);
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
		| UVD_SUVD_CGC_GATE__ENT_MASK
		| UVD_SUVD_CGC_GATE__SIT_HEVC_DEC_MASK
		| UVD_SUVD_CGC_GATE__SITE_MASK
		| UVD_SUVD_CGC_GATE__SWE_VP9_MASK
		| UVD_SUVD_CGC_GATE__SCM_VP9_MASK
		| UVD_SUVD_CGC_GATE__SIT_VP9_DEC_MASK
		| UVD_SUVD_CGC_GATE__SDB_VP9_MASK
		| UVD_SUVD_CGC_GATE__IME_HEVC_MASK);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_SUVD_CGC_GATE, data);

	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_SUVD_CGC_CTWW);
	data &= ~(UVD_SUVD_CGC_CTWW__SWE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTWW__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__IME_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SITE_MODE_MASK);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_SUVD_CGC_CTWW, data);
}

/**
 * vcn_v4_0_3_disabwe_cwock_gating_dpg_mode - disabwe VCN cwock gating dpg mode
 *
 * @adev: amdgpu_device pointew
 * @swam_sew: swam sewect
 * @inst_idx: instance numbew index
 * @indiwect: indiwectwy wwite swam
 *
 * Disabwe cwock gating fow VCN bwock with dpg mode
 */
static void vcn_v4_0_3_disabwe_cwock_gating_dpg_mode(stwuct amdgpu_device *adev, uint8_t swam_sew,
				int inst_idx, uint8_t indiwect)
{
	uint32_t weg_data = 0;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		wetuwn;

	/* enabwe sw cwock gating contwow */
	weg_data = 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	weg_data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	weg_data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	weg_data &= ~(UVD_CGC_CTWW__SYS_MODE_MASK |
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
		VCN, 0, wegUVD_CGC_CTWW), weg_data, swam_sew, indiwect);

	/* tuwn off cwock gating */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_CGC_GATE), 0, swam_sew, indiwect);

	/* tuwn on SUVD cwock gating */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_SUVD_CGC_GATE), 1, swam_sew, indiwect);

	/* tuwn on sw mode in UVD_SUVD_CGC_CTWW */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_SUVD_CGC_CTWW), 0, swam_sew, indiwect);
}

/**
 * vcn_v4_0_3_enabwe_cwock_gating - enabwe VCN cwock gating
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew
 *
 * Enabwe cwock gating fow VCN bwock
 */
static void vcn_v4_0_3_enabwe_cwock_gating(stwuct amdgpu_device *adev, int inst_idx)
{
	uint32_t data;
	int vcn_inst;

	if (adev->cg_fwags & AMD_CG_SUPPOWT_VCN_MGCG)
		wetuwn;

	vcn_inst = GET_INST(VCN, inst_idx);

	/* enabwe VCN CGC */
	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW);
	data |= 0 << UVD_CGC_CTWW__DYN_CWOCK_MODE__SHIFT;
	data |= 1 << UVD_CGC_CTWW__CWK_GATE_DWY_TIMEW__SHIFT;
	data |= 4 << UVD_CGC_CTWW__CWK_OFF_DEWAY__SHIFT;
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW);
	data |= (UVD_CGC_CTWW__SYS_MODE_MASK
		| UVD_CGC_CTWW__MPEG2_MODE_MASK
		| UVD_CGC_CTWW__WEGS_MODE_MASK
		| UVD_CGC_CTWW__WBC_MODE_MASK
		| UVD_CGC_CTWW__WMI_MC_MODE_MASK
		| UVD_CGC_CTWW__WMI_UMC_MODE_MASK
		| UVD_CGC_CTWW__MPC_MODE_MASK
		| UVD_CGC_CTWW__WBSI_MODE_MASK
		| UVD_CGC_CTWW__WWBBM_MODE_MASK
		| UVD_CGC_CTWW__WCB_MODE_MASK
		| UVD_CGC_CTWW__VCPU_MODE_MASK);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_CGC_CTWW, data);

	data = WWEG32_SOC15(VCN, vcn_inst, wegUVD_SUVD_CGC_CTWW);
	data |= (UVD_SUVD_CGC_CTWW__SWE_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SIT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SMP_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SCM_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SDB_MODE_MASK
		| UVD_SUVD_CGC_CTWW__ENT_MODE_MASK
		| UVD_SUVD_CGC_CTWW__IME_MODE_MASK
		| UVD_SUVD_CGC_CTWW__SITE_MODE_MASK);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_SUVD_CGC_CTWW, data);
}

/**
 * vcn_v4_0_3_stawt_dpg_mode - VCN stawt with dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 * @indiwect: indiwectwy wwite swam
 *
 * Stawt VCN bwock with dpg mode
 */
static int vcn_v4_0_3_stawt_dpg_mode(stwuct amdgpu_device *adev, int inst_idx, boow indiwect)
{
	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed =
						adev->vcn.inst[inst_idx].fw_shawed.cpu_addw;
	stwuct amdgpu_wing *wing;
	int vcn_inst;
	uint32_t tmp;

	vcn_inst = GET_INST(VCN, inst_idx);
	/* disabwe wegistew anti-hang mechanism */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_POWEW_STATUS), 1,
		 ~UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);
	/* enabwe dynamic powew gating mode */
	tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_POWEW_STATUS);
	tmp |= UVD_POWEW_STATUS__UVD_PG_MODE_MASK;
	tmp |= UVD_POWEW_STATUS__UVD_PG_EN_MASK;
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_POWEW_STATUS, tmp);

	if (indiwect) {
		DWM_DEV_DEBUG(adev->dev, "VCN %d stawt: on AID %d",
			inst_idx, adev->vcn.inst[inst_idx].aid_id);
		adev->vcn.inst[inst_idx].dpg_swam_cuww_addw =
				(uint32_t *)adev->vcn.inst[inst_idx].dpg_swam_cpu_addw;
		/* Use dummy wegistew 0xDEADBEEF passing AID sewection to PSP FW */
		WWEG32_SOC15_DPG_MODE(inst_idx, 0xDEADBEEF,
			adev->vcn.inst[inst_idx].aid_id, 0, twue);
	}

	/* enabwe cwock gating */
	vcn_v4_0_3_disabwe_cwock_gating_dpg_mode(adev, 0, inst_idx, indiwect);

	/* enabwe VCPU cwock */
	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK;
	tmp |= UVD_VCPU_CNTW__BWK_WST_MASK;

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_VCPU_CNTW), tmp, 0, indiwect);

	/* disabwe mastew intewwupt */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_MASTINT_EN), 0, 0, indiwect);

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
		VCN, 0, wegUVD_WMI_CTWW), tmp, 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_MPC_CNTW),
		0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT, 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_MPC_SET_MUXA0),
		((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)), 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_MPC_SET_MUXB0),
		 ((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
		 (0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
		 (0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)), 0, indiwect);

	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_MPC_SET_MUX),
		((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
		 (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
		 (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)), 0, indiwect);

	vcn_v4_0_3_mc_wesume_dpg_mode(adev, inst_idx, indiwect);

	tmp = (0xFF << UVD_VCPU_CNTW__PWB_TIMEOUT_VAW__SHIFT);
	tmp |= UVD_VCPU_CNTW__CWK_EN_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_VCPU_CNTW), tmp, 0, indiwect);

	/* enabwe WMI MC and UMC channews */
	tmp = 0x1f << UVD_WMI_CTWW2__WE_OFWD_MIF_WW_WEQ_NUM__SHIFT;
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_WMI_CTWW2), tmp, 0, indiwect);

	vcn_v4_0_3_enabwe_was(adev, inst_idx, indiwect);

	/* enabwe mastew intewwupt */
	WWEG32_SOC15_DPG_MODE(inst_idx, SOC15_DPG_MODE_OFFSET(
		VCN, 0, wegUVD_MASTINT_EN),
		UVD_MASTINT_EN__VCPU_EN_MASK, 0, indiwect);

	if (indiwect)
		amdgpu_vcn_psp_update_swam(adev, inst_idx, AMDGPU_UCODE_ID_VCN0_WAM);

	wing = &adev->vcn.inst[inst_idx].wing_enc[0];

	/* pwogwam the WB_BASE fow wing buffew */
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_BASE_WO,
		     wowew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_BASE_HI,
		     uppew_32_bits(wing->gpu_addw));

	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_SIZE,
		     wing->wing_size / sizeof(uint32_t));

	/* wesetting wing, fw shouwd not check WB wing */
	tmp = WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE);
	tmp &= ~(VCN_WB_ENABWE__WB_EN_MASK);
	WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE, tmp);
	fw_shawed->sq.queue_mode |= FW_QUEUE_WING_WESET;

	/* Initiawize the wing buffew's wead and wwite pointews */
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW, 0);
	WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW, 0);
	wing->wptw = WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW);

	tmp = WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE);
	tmp |= VCN_WB_ENABWE__WB_EN_MASK;
	WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE, tmp);
	fw_shawed->sq.queue_mode &= ~(FW_QUEUE_WING_WESET | FW_QUEUE_DPG_HOWD_OFF);

	/*wesetting done, fw can check WB wing */
	fw_shawed->sq.queue_mode &= cpu_to_we32(~FW_QUEUE_WING_WESET);

	wetuwn 0;
}

static int vcn_v4_0_3_stawt_swiov(stwuct amdgpu_device *adev)
{
	int i, vcn_inst;
	stwuct amdgpu_wing *wing_enc;
	uint64_t cache_addw;
	uint64_t wb_enc_addw;
	uint64_t ctx_addw;
	uint32_t pawam, wesp, expected;
	uint32_t offset, cache_size;
	uint32_t tmp, timeout;

	stwuct amdgpu_mm_tabwe *tabwe = &adev->viwt.mm_tabwe;
	uint32_t *tabwe_woc;
	uint32_t tabwe_size;
	uint32_t size, size_dw;
	uint32_t init_status;
	uint32_t enabwed_vcn;

	stwuct mmsch_v4_0_cmd_diwect_wwite
		diwect_wt = { {0} };
	stwuct mmsch_v4_0_cmd_diwect_wead_modify_wwite
		diwect_wd_mod_wt = { {0} };
	stwuct mmsch_v4_0_cmd_end end = { {0} };
	stwuct mmsch_v4_0_3_init_headew headew;

	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;
	vowatiwe stwuct amdgpu_fw_shawed_wb_setup *wb_setup;

	diwect_wt.cmd_headew.command_type =
		MMSCH_COMMAND__DIWECT_WEG_WWITE;
	diwect_wd_mod_wt.cmd_headew.command_type =
		MMSCH_COMMAND__DIWECT_WEG_WEAD_MODIFY_WWITE;
	end.cmd_headew.command_type = MMSCH_COMMAND__END;

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++) {
		vcn_inst = GET_INST(VCN, i);

		memset(&headew, 0, sizeof(stwuct mmsch_v4_0_3_init_headew));
		headew.vewsion = MMSCH_VEWSION;
		headew.totaw_size = sizeof(stwuct mmsch_v4_0_3_init_headew) >> 2;

		tabwe_woc = (uint32_t *)tabwe->cpu_addw;
		tabwe_woc += headew.totaw_size;

		tabwe_size = 0;

		MMSCH_V4_0_INSEWT_DIWECT_WD_MOD_WT(SOC15_WEG_OFFSET(VCN, 0, wegUVD_STATUS),
			~UVD_STATUS__UVD_BUSY, UVD_STATUS__UVD_BUSY);

		cache_size = AMDGPU_GPU_PAGE_AWIGN(adev->vcn.fw->size + 4);

		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
			MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
				wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + i].tmw_mc_addw_wo);

			MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
				wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
				adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_VCN + i].tmw_mc_addw_hi);

			offset = 0;
			MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
				wegUVD_VCPU_CACHE_OFFSET0), 0);
		} ewse {
			MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
				wegUVD_WMI_VCPU_CACHE_64BIT_BAW_WOW),
				wowew_32_bits(adev->vcn.inst[i].gpu_addw));
			MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
				wegUVD_WMI_VCPU_CACHE_64BIT_BAW_HIGH),
				uppew_32_bits(adev->vcn.inst[i].gpu_addw));
			offset = cache_size;
			MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
				wegUVD_VCPU_CACHE_OFFSET0),
				AMDGPU_UVD_FIWMWAWE_OFFSET >> 3);
		}

		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_VCPU_CACHE_SIZE0),
			cache_size);

		cache_addw = adev->vcn.inst[vcn_inst].gpu_addw + offset;
		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_WOW), wowew_32_bits(cache_addw));
		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_WMI_VCPU_CACHE1_64BIT_BAW_HIGH), uppew_32_bits(cache_addw));
		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_VCPU_CACHE_OFFSET1), 0);
		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_VCPU_CACHE_SIZE1), AMDGPU_VCN_STACK_SIZE);

		cache_addw = adev->vcn.inst[vcn_inst].gpu_addw + offset +
			AMDGPU_VCN_STACK_SIZE;

		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_WOW), wowew_32_bits(cache_addw));

		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_WMI_VCPU_CACHE2_64BIT_BAW_HIGH), uppew_32_bits(cache_addw));

		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_VCPU_CACHE_OFFSET2), 0);

		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_VCPU_CACHE_SIZE2), AMDGPU_VCN_CONTEXT_SIZE);

		fw_shawed = adev->vcn.inst[vcn_inst].fw_shawed.cpu_addw;
		wb_setup = &fw_shawed->wb_setup;

		wing_enc = &adev->vcn.inst[vcn_inst].wing_enc[0];
		wing_enc->wptw = 0;
		wb_enc_addw = wing_enc->gpu_addw;

		wb_setup->is_wb_enabwed_fwags |= WB_ENABWED;
		wb_setup->wb_addw_wo = wowew_32_bits(wb_enc_addw);
		wb_setup->wb_addw_hi = uppew_32_bits(wb_enc_addw);
		wb_setup->wb_size = wing_enc->wing_size / 4;
		fw_shawed->pwesent_fwag_0 |= cpu_to_we32(AMDGPU_VCN_VF_WB_SETUP_FWAG);

		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_WMI_VCPU_NC0_64BIT_BAW_WOW),
			wowew_32_bits(adev->vcn.inst[vcn_inst].fw_shawed.gpu_addw));
		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_WMI_VCPU_NC0_64BIT_BAW_HIGH),
			uppew_32_bits(adev->vcn.inst[vcn_inst].fw_shawed.gpu_addw));
		MMSCH_V4_0_INSEWT_DIWECT_WT(SOC15_WEG_OFFSET(VCN, 0,
			wegUVD_VCPU_NONCACHE_SIZE0),
			AMDGPU_GPU_PAGE_AWIGN(sizeof(stwuct amdgpu_vcn4_fw_shawed)));
		MMSCH_V4_0_INSEWT_END();

		headew.vcn0.init_status = 0;
		headew.vcn0.tabwe_offset = headew.totaw_size;
		headew.vcn0.tabwe_size = tabwe_size;
		headew.totaw_size += tabwe_size;

		/* Send init tabwe to mmsch */
		size = sizeof(stwuct mmsch_v4_0_3_init_headew);
		tabwe_woc = (uint32_t *)tabwe->cpu_addw;
		memcpy((void *)tabwe_woc, &headew, size);

		ctx_addw = tabwe->gpu_addw;
		WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_CTX_ADDW_WO, wowew_32_bits(ctx_addw));
		WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_CTX_ADDW_HI, uppew_32_bits(ctx_addw));

		tmp = WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_VMID);
		tmp &= ~MMSCH_VF_VMID__VF_CTX_VMID_MASK;
		tmp |= (0 << MMSCH_VF_VMID__VF_CTX_VMID__SHIFT);
		WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_VMID, tmp);

		size = headew.totaw_size;
		WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_CTX_SIZE, size);

		WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_MAIWBOX_WESP, 0);

		pawam = 0x00000001;
		WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_MAIWBOX_HOST, pawam);
		tmp = 0;
		timeout = 1000;
		wesp = 0;
		expected = MMSCH_VF_MAIWBOX_WESP__OK;
		whiwe (wesp != expected) {
			wesp = WWEG32_SOC15(VCN, vcn_inst, wegMMSCH_VF_MAIWBOX_WESP);
			if (wesp != 0)
				bweak;

			udeway(10);
			tmp = tmp + 10;
			if (tmp >= timeout) {
				DWM_EWWOW("faiwed to init MMSCH. TIME-OUT aftew %d usec"\
					" waiting fow wegMMSCH_VF_MAIWBOX_WESP "\
					"(expected=0x%08x, weadback=0x%08x)\n",
					tmp, expected, wesp);
				wetuwn -EBUSY;
			}
		}

		enabwed_vcn = amdgpu_vcn_is_disabwed_vcn(adev, VCN_DECODE_WING, 0) ? 1 : 0;
		init_status = ((stwuct mmsch_v4_0_3_init_headew *)(tabwe_woc))->vcn0.init_status;
		if (wesp != expected && wesp != MMSCH_VF_MAIWBOX_WESP__INCOMPWETE
					&& init_status != MMSCH_VF_ENGINE_STATUS__PASS) {
			DWM_EWWOW("MMSCH init status is incowwect! weadback=0x%08x, headew init "\
				"status fow VCN%x: 0x%x\n", wesp, enabwed_vcn, init_status);
		}
	}

	wetuwn 0;
}

/**
 * vcn_v4_0_3_stawt - VCN stawt
 *
 * @adev: amdgpu_device pointew
 *
 * Stawt VCN bwock
 */
static int vcn_v4_0_3_stawt(stwuct amdgpu_device *adev)
{
	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;
	stwuct amdgpu_wing *wing;
	int i, j, k, w, vcn_inst;
	uint32_t tmp;

	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_uvd(adev, twue);

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
			w = vcn_v4_0_3_stawt_dpg_mode(adev, i, adev->vcn.indiwect_swam);
			continue;
		}

		vcn_inst = GET_INST(VCN, i);
		/* set VCN status busy */
		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_STATUS) |
		      UVD_STATUS__UVD_BUSY;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_STATUS, tmp);

		/*SW cwock gating */
		vcn_v4_0_3_disabwe_cwock_gating(adev, i);

		/* enabwe VCPU cwock */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_VCPU_CNTW),
			 UVD_VCPU_CNTW__CWK_EN_MASK,
			 ~UVD_VCPU_CNTW__CWK_EN_MASK);

		/* disabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_MASTINT_EN), 0,
			 ~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* enabwe WMI MC and UMC channews */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_WMI_CTWW2), 0,
			 ~UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK);

		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_SOFT_WESET);
		tmp &= ~UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
		tmp &= ~UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_SOFT_WESET, tmp);

		/* setup wegUVD_WMI_CTWW */
		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_CTWW);
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_CTWW,
			     tmp | UVD_WMI_CTWW__WWITE_CWEAN_TIMEW_EN_MASK |
				     UVD_WMI_CTWW__MASK_MC_UWGENT_MASK |
				     UVD_WMI_CTWW__DATA_COHEWENCY_EN_MASK |
				     UVD_WMI_CTWW__VCPU_DATA_COHEWENCY_EN_MASK);

		/* setup wegUVD_MPC_CNTW */
		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_MPC_CNTW);
		tmp &= ~UVD_MPC_CNTW__WEPWACEMENT_MODE_MASK;
		tmp |= 0x2 << UVD_MPC_CNTW__WEPWACEMENT_MODE__SHIFT;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_MPC_CNTW, tmp);

		/* setup UVD_MPC_SET_MUXA0 */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_MPC_SET_MUXA0,
			     ((0x1 << UVD_MPC_SET_MUXA0__VAWA_1__SHIFT) |
			      (0x2 << UVD_MPC_SET_MUXA0__VAWA_2__SHIFT) |
			      (0x3 << UVD_MPC_SET_MUXA0__VAWA_3__SHIFT) |
			      (0x4 << UVD_MPC_SET_MUXA0__VAWA_4__SHIFT)));

		/* setup UVD_MPC_SET_MUXB0 */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_MPC_SET_MUXB0,
			     ((0x1 << UVD_MPC_SET_MUXB0__VAWB_1__SHIFT) |
			      (0x2 << UVD_MPC_SET_MUXB0__VAWB_2__SHIFT) |
			      (0x3 << UVD_MPC_SET_MUXB0__VAWB_3__SHIFT) |
			      (0x4 << UVD_MPC_SET_MUXB0__VAWB_4__SHIFT)));

		/* setup UVD_MPC_SET_MUX */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_MPC_SET_MUX,
			     ((0x0 << UVD_MPC_SET_MUX__SET_0__SHIFT) |
			      (0x1 << UVD_MPC_SET_MUX__SET_1__SHIFT) |
			      (0x2 << UVD_MPC_SET_MUX__SET_2__SHIFT)));

		vcn_v4_0_3_mc_wesume(adev, i);

		/* VCN gwobaw tiwing wegistews */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_GFX8_ADDW_CONFIG,
			     adev->gfx.config.gb_addw_config);
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_GFX10_ADDW_CONFIG,
			     adev->gfx.config.gb_addw_config);

		/* unbwock VCPU wegistew access */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_WB_AWB_CTWW), 0,
			 ~UVD_WB_AWB_CTWW__VCPU_DIS_MASK);

		/* wewease VCPU weset to boot */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_VCPU_CNTW), 0,
			 ~UVD_VCPU_CNTW__BWK_WST_MASK);

		fow (j = 0; j < 10; ++j) {
			uint32_t status;

			fow (k = 0; k < 100; ++k) {
				status = WWEG32_SOC15(VCN, vcn_inst,
						      wegUVD_STATUS);
				if (status & 2)
					bweak;
				mdeway(10);
			}
			w = 0;
			if (status & 2)
				bweak;

			DWM_DEV_EWWOW(adev->dev,
				"VCN decode not wesponding, twying to weset the VCPU!!!\n");
			WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst,
						  wegUVD_VCPU_CNTW),
				 UVD_VCPU_CNTW__BWK_WST_MASK,
				 ~UVD_VCPU_CNTW__BWK_WST_MASK);
			mdeway(10);
			WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst,
						  wegUVD_VCPU_CNTW),
				 0, ~UVD_VCPU_CNTW__BWK_WST_MASK);

			mdeway(10);
			w = -1;
		}

		if (w) {
			DWM_DEV_EWWOW(adev->dev, "VCN decode not wesponding, giving up!!!\n");
			wetuwn w;
		}

		/* enabwe mastew intewwupt */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_MASTINT_EN),
			 UVD_MASTINT_EN__VCPU_EN_MASK,
			 ~UVD_MASTINT_EN__VCPU_EN_MASK);

		/* cweaw the busy bit of VCN_STATUS */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_STATUS), 0,
			 ~(2 << UVD_STATUS__VCPU_WEPOWT__SHIFT));

		wing = &adev->vcn.inst[i].wing_enc[0];
		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;

		/* pwogwam the WB_BASE fow wing buffew */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_BASE_WO,
			     wowew_32_bits(wing->gpu_addw));
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_BASE_HI,
			     uppew_32_bits(wing->gpu_addw));

		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_SIZE,
			     wing->wing_size / sizeof(uint32_t));

		/* wesetting wing, fw shouwd not check WB wing */
		tmp = WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE);
		tmp &= ~(VCN_WB_ENABWE__WB_EN_MASK);
		WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE, tmp);

		/* Initiawize the wing buffew's wead and wwite pointews */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW, 0);
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW, 0);

		tmp = WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE);
		tmp |= VCN_WB_ENABWE__WB_EN_MASK;
		WWEG32_SOC15(VCN, vcn_inst, wegVCN_WB_ENABWE, tmp);

		wing->wptw = WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW);
		fw_shawed->sq.queue_mode &=
			cpu_to_we32(~(FW_QUEUE_WING_WESET | FW_QUEUE_DPG_HOWD_OFF));

	}
	wetuwn 0;
}

/**
 * vcn_v4_0_3_stop_dpg_mode - VCN stop with dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 *
 * Stop VCN bwock with dpg mode
 */
static int vcn_v4_0_3_stop_dpg_mode(stwuct amdgpu_device *adev, int inst_idx)
{
	uint32_t tmp;
	int vcn_inst;

	vcn_inst = GET_INST(VCN, inst_idx);

	/* Wait fow powew status to be 1 */
	SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_POWEW_STATUS, 1,
			   UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* wait fow wead ptw to be equaw to wwite ptw */
	tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_WB_WPTW);
	SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_WB_WPTW, tmp, 0xFFFFFFFF);

	SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_POWEW_STATUS, 1,
			   UVD_POWEW_STATUS__UVD_POWEW_STATUS_MASK);

	/* disabwe dynamic powew gating mode */
	WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_POWEW_STATUS), 0,
		 ~UVD_POWEW_STATUS__UVD_PG_MODE_MASK);
	wetuwn 0;
}

/**
 * vcn_v4_0_3_stop - VCN stop
 *
 * @adev: amdgpu_device pointew
 *
 * Stop VCN bwock
 */
static int vcn_v4_0_3_stop(stwuct amdgpu_device *adev)
{
	vowatiwe stwuct amdgpu_vcn4_fw_shawed *fw_shawed;
	int i, w = 0, vcn_inst;
	uint32_t tmp;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		vcn_inst = GET_INST(VCN, i);

		fw_shawed = adev->vcn.inst[i].fw_shawed.cpu_addw;
		fw_shawed->sq.queue_mode |= FW_QUEUE_DPG_HOWD_OFF;

		if (adev->pg_fwags & AMD_PG_SUPPOWT_VCN_DPG) {
			vcn_v4_0_3_stop_dpg_mode(adev, i);
			continue;
		}

		/* wait fow vcn idwe */
		w = SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_STATUS,
				       UVD_STATUS__IDWE, 0x7);
		if (w)
			goto Done;

		tmp = UVD_WMI_STATUS__VCPU_WMI_WWITE_CWEAN_MASK |
			UVD_WMI_STATUS__WEAD_CWEAN_MASK |
			UVD_WMI_STATUS__WWITE_CWEAN_MASK |
			UVD_WMI_STATUS__WWITE_CWEAN_WAW_MASK;
		w = SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_WMI_STATUS, tmp,
				       tmp);
		if (w)
			goto Done;

		/* staww UMC channew */
		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_CTWW2);
		tmp |= UVD_WMI_CTWW2__STAWW_AWB_UMC_MASK;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_WMI_CTWW2, tmp);
		tmp = UVD_WMI_STATUS__UMC_WEAD_CWEAN_WAW_MASK |
			UVD_WMI_STATUS__UMC_WWITE_CWEAN_WAW_MASK;
		w = SOC15_WAIT_ON_WWEG(VCN, vcn_inst, wegUVD_WMI_STATUS, tmp,
				       tmp);
		if (w)
			goto Done;

		/* Unbwock VCPU Wegistew access */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_WB_AWB_CTWW),
			 UVD_WB_AWB_CTWW__VCPU_DIS_MASK,
			 ~UVD_WB_AWB_CTWW__VCPU_DIS_MASK);

		/* wewease VCPU weset to boot */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_VCPU_CNTW),
			 UVD_VCPU_CNTW__BWK_WST_MASK,
			 ~UVD_VCPU_CNTW__BWK_WST_MASK);

		/* disabwe VCPU cwock */
		WWEG32_P(SOC15_WEG_OFFSET(VCN, vcn_inst, wegUVD_VCPU_CNTW), 0,
			 ~(UVD_VCPU_CNTW__CWK_EN_MASK));

		/* weset WMI UMC/WMI/VCPU */
		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_SOFT_WESET);
		tmp |= UVD_SOFT_WESET__WMI_UMC_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_SOFT_WESET, tmp);

		tmp = WWEG32_SOC15(VCN, vcn_inst, wegUVD_SOFT_WESET);
		tmp |= UVD_SOFT_WESET__WMI_SOFT_WESET_MASK;
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_SOFT_WESET, tmp);

		/* cweaw VCN status */
		WWEG32_SOC15(VCN, vcn_inst, wegUVD_STATUS, 0);

		/* appwy HW cwock gating */
		vcn_v4_0_3_enabwe_cwock_gating(adev, i);
	}
Done:
	if (adev->pm.dpm_enabwed)
		amdgpu_dpm_enabwe_uvd(adev, fawse);

	wetuwn 0;
}

/**
 * vcn_v4_0_3_pause_dpg_mode - VCN pause with dpg mode
 *
 * @adev: amdgpu_device pointew
 * @inst_idx: instance numbew index
 * @new_state: pause state
 *
 * Pause dpg mode fow VCN bwock
 */
static int vcn_v4_0_3_pause_dpg_mode(stwuct amdgpu_device *adev, int inst_idx,
				stwuct dpg_pause_state *new_state)
{

	wetuwn 0;
}

/**
 * vcn_v4_0_3_unified_wing_get_wptw - get unified wead pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe unified wead pointew
 */
static uint64_t vcn_v4_0_3_unified_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing != &adev->vcn.inst[wing->me].wing_enc[0])
		DWM_EWWOW("wwong wing id is identified in %s", __func__);

	wetuwn WWEG32_SOC15(VCN, GET_INST(VCN, wing->me), wegUVD_WB_WPTW);
}

/**
 * vcn_v4_0_3_unified_wing_get_wptw - get unified wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Wetuwns the cuwwent hawdwawe unified wwite pointew
 */
static uint64_t vcn_v4_0_3_unified_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing != &adev->vcn.inst[wing->me].wing_enc[0])
		DWM_EWWOW("wwong wing id is identified in %s", __func__);

	if (wing->use_doowbeww)
		wetuwn *wing->wptw_cpu_addw;
	ewse
		wetuwn WWEG32_SOC15(VCN, GET_INST(VCN, wing->me),
				    wegUVD_WB_WPTW);
}

/**
 * vcn_v4_0_3_unified_wing_set_wptw - set enc wwite pointew
 *
 * @wing: amdgpu_wing pointew
 *
 * Commits the enc wwite pointew to the hawdwawe
 */
static void vcn_v4_0_3_unified_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing != &adev->vcn.inst[wing->me].wing_enc[0])
		DWM_EWWOW("wwong wing id is identified in %s", __func__);

	if (wing->use_doowbeww) {
		*wing->wptw_cpu_addw = wowew_32_bits(wing->wptw);
		WDOOWBEWW32(wing->doowbeww_index, wowew_32_bits(wing->wptw));
	} ewse {
		WWEG32_SOC15(VCN, GET_INST(VCN, wing->me), wegUVD_WB_WPTW,
			     wowew_32_bits(wing->wptw));
	}
}

static const stwuct amdgpu_wing_funcs vcn_v4_0_3_unified_wing_vm_funcs = {
	.type = AMDGPU_WING_TYPE_VCN_ENC,
	.awign_mask = 0x3f,
	.nop = VCN_ENC_CMD_NO_OP,
	.get_wptw = vcn_v4_0_3_unified_wing_get_wptw,
	.get_wptw = vcn_v4_0_3_unified_wing_get_wptw,
	.set_wptw = vcn_v4_0_3_unified_wing_set_wptw,
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
 * vcn_v4_0_3_set_unified_wing_funcs - set unified wing functions
 *
 * @adev: amdgpu_device pointew
 *
 * Set unified wing functions
 */
static void vcn_v4_0_3_set_unified_wing_funcs(stwuct amdgpu_device *adev)
{
	int i, vcn_inst;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		adev->vcn.inst[i].wing_enc[0].funcs = &vcn_v4_0_3_unified_wing_vm_funcs;
		adev->vcn.inst[i].wing_enc[0].me = i;
		vcn_inst = GET_INST(VCN, i);
		adev->vcn.inst[i].aid_id =
			vcn_inst / adev->vcn.num_inst_pew_aid;
	}
	DWM_DEV_INFO(adev->dev, "VCN decode is enabwed in VM mode\n");
}

/**
 * vcn_v4_0_3_is_idwe - check VCN bwock is idwe
 *
 * @handwe: amdgpu_device pointew
 *
 * Check whethew VCN bwock is idwe
 */
static boow vcn_v4_0_3_is_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 1;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		wet &= (WWEG32_SOC15(VCN, GET_INST(VCN, i), wegUVD_STATUS) ==
			UVD_STATUS__IDWE);
	}

	wetuwn wet;
}

/**
 * vcn_v4_0_3_wait_fow_idwe - wait fow VCN bwock idwe
 *
 * @handwe: amdgpu_device pointew
 *
 * Wait fow VCN bwock idwe
 */
static int vcn_v4_0_3_wait_fow_idwe(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int i, wet = 0;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		wet = SOC15_WAIT_ON_WWEG(VCN, GET_INST(VCN, i), wegUVD_STATUS,
					 UVD_STATUS__IDWE, UVD_STATUS__IDWE);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/* vcn_v4_0_3_set_cwockgating_state - set VCN bwock cwockgating state
 *
 * @handwe: amdgpu_device pointew
 * @state: cwock gating state
 *
 * Set VCN bwock cwockgating state
 */
static int vcn_v4_0_3_set_cwockgating_state(void *handwe,
					  enum amd_cwockgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	boow enabwe = state == AMD_CG_STATE_GATE;
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		if (enabwe) {
			if (WWEG32_SOC15(VCN, GET_INST(VCN, i),
					 wegUVD_STATUS) != UVD_STATUS__IDWE)
				wetuwn -EBUSY;
			vcn_v4_0_3_enabwe_cwock_gating(adev, i);
		} ewse {
			vcn_v4_0_3_disabwe_cwock_gating(adev, i);
		}
	}
	wetuwn 0;
}

/**
 * vcn_v4_0_3_set_powewgating_state - set VCN bwock powewgating state
 *
 * @handwe: amdgpu_device pointew
 * @state: powew gating state
 *
 * Set VCN bwock powewgating state
 */
static int vcn_v4_0_3_set_powewgating_state(void *handwe,
					  enum amd_powewgating_state state)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int wet;

	/* fow SWIOV, guest shouwd not contwow VCN Powew-gating
	 * MMSCH FW shouwd contwow Powew-gating and cwock-gating
	 * guest shouwd avoid touching CGC and PG
	 */
	if (amdgpu_swiov_vf(adev)) {
		adev->vcn.cuw_state = AMD_PG_STATE_UNGATE;
		wetuwn 0;
	}

	if (state == adev->vcn.cuw_state)
		wetuwn 0;

	if (state == AMD_PG_STATE_GATE)
		wet = vcn_v4_0_3_stop(adev);
	ewse
		wet = vcn_v4_0_3_stawt(adev);

	if (!wet)
		adev->vcn.cuw_state = state;

	wetuwn wet;
}

/**
 * vcn_v4_0_3_set_intewwupt_state - set VCN bwock intewwupt state
 *
 * @adev: amdgpu_device pointew
 * @souwce: intewwupt souwces
 * @type: intewwupt types
 * @state: intewwupt states
 *
 * Set VCN bwock intewwupt state
 */
static int vcn_v4_0_3_set_intewwupt_state(stwuct amdgpu_device *adev,
					stwuct amdgpu_iwq_swc *souwce,
					unsigned int type,
					enum amdgpu_intewwupt_state state)
{
	wetuwn 0;
}

/**
 * vcn_v4_0_3_pwocess_intewwupt - pwocess VCN bwock intewwupt
 *
 * @adev: amdgpu_device pointew
 * @souwce: intewwupt souwces
 * @entwy: intewwupt entwy fwom cwients and souwces
 *
 * Pwocess VCN bwock intewwupt
 */
static int vcn_v4_0_3_pwocess_intewwupt(stwuct amdgpu_device *adev,
				      stwuct amdgpu_iwq_swc *souwce,
				      stwuct amdgpu_iv_entwy *entwy)
{
	uint32_t i, inst;

	i = node_id_to_phys_map[entwy->node_id];

	DWM_DEV_DEBUG(adev->dev, "IH: VCN TWAP\n");

	fow (inst = 0; inst < adev->vcn.num_vcn_inst; ++inst)
		if (adev->vcn.inst[inst].aid_id == i)
			bweak;

	if (inst >= adev->vcn.num_vcn_inst) {
		dev_WAWN_ONCE(adev->dev, 1,
			      "Intewwupt weceived fow unknown VCN instance %d",
			      entwy->node_id);
		wetuwn 0;
	}

	switch (entwy->swc_id) {
	case VCN_4_0__SWCID__UVD_ENC_GENEWAW_PUWPOSE:
		amdgpu_fence_pwocess(&adev->vcn.inst[inst].wing_enc[0]);
		bweak;
	defauwt:
		DWM_DEV_EWWOW(adev->dev, "Unhandwed intewwupt: %d %d\n",
			  entwy->swc_id, entwy->swc_data[0]);
		bweak;
	}

	wetuwn 0;
}

static const stwuct amdgpu_iwq_swc_funcs vcn_v4_0_3_iwq_funcs = {
	.set = vcn_v4_0_3_set_intewwupt_state,
	.pwocess = vcn_v4_0_3_pwocess_intewwupt,
};

/**
 * vcn_v4_0_3_set_iwq_funcs - set VCN bwock intewwupt iwq functions
 *
 * @adev: amdgpu_device pointew
 *
 * Set VCN bwock intewwupt iwq functions
 */
static void vcn_v4_0_3_set_iwq_funcs(stwuct amdgpu_device *adev)
{
	int i;

	fow (i = 0; i < adev->vcn.num_vcn_inst; ++i) {
		adev->vcn.inst->iwq.num_types++;
	}
	adev->vcn.inst->iwq.funcs = &vcn_v4_0_3_iwq_funcs;
}

static const stwuct amd_ip_funcs vcn_v4_0_3_ip_funcs = {
	.name = "vcn_v4_0_3",
	.eawwy_init = vcn_v4_0_3_eawwy_init,
	.wate_init = NUWW,
	.sw_init = vcn_v4_0_3_sw_init,
	.sw_fini = vcn_v4_0_3_sw_fini,
	.hw_init = vcn_v4_0_3_hw_init,
	.hw_fini = vcn_v4_0_3_hw_fini,
	.suspend = vcn_v4_0_3_suspend,
	.wesume = vcn_v4_0_3_wesume,
	.is_idwe = vcn_v4_0_3_is_idwe,
	.wait_fow_idwe = vcn_v4_0_3_wait_fow_idwe,
	.check_soft_weset = NUWW,
	.pwe_soft_weset = NUWW,
	.soft_weset = NUWW,
	.post_soft_weset = NUWW,
	.set_cwockgating_state = vcn_v4_0_3_set_cwockgating_state,
	.set_powewgating_state = vcn_v4_0_3_set_powewgating_state,
};

const stwuct amdgpu_ip_bwock_vewsion vcn_v4_0_3_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_VCN,
	.majow = 4,
	.minow = 0,
	.wev = 3,
	.funcs = &vcn_v4_0_3_ip_funcs,
};

static const stwuct amdgpu_was_eww_status_weg_entwy vcn_v4_0_3_ue_weg_wist[] = {
	{AMDGPU_WAS_WEG_ENTWY(VCN, 0, wegVCN_UE_EWW_STATUS_WO_VIDD, wegVCN_UE_EWW_STATUS_HI_VIDD),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "VIDD"},
	{AMDGPU_WAS_WEG_ENTWY(VCN, 0, wegVCN_UE_EWW_STATUS_WO_VIDV, wegVCN_UE_EWW_STATUS_HI_VIDV),
	1, (AMDGPU_WAS_EWW_INFO_VAWID | AMDGPU_WAS_EWW_STATUS_VAWID), "VIDV"},
};

static void vcn_v4_0_3_inst_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
						  uint32_t vcn_inst,
						  void *was_eww_status)
{
	stwuct was_eww_data *eww_data = (stwuct was_eww_data *)was_eww_status;

	/* vcn v4_0_3 onwy suppowt quewy uncowwectabwe ewwows */
	amdgpu_was_inst_quewy_was_ewwow_count(adev,
			vcn_v4_0_3_ue_weg_wist,
			AWWAY_SIZE(vcn_v4_0_3_ue_weg_wist),
			NUWW, 0, GET_INST(VCN, vcn_inst),
			AMDGPU_WAS_EWWOW__MUWTI_UNCOWWECTABWE,
			&eww_data->ue_count);
}

static void vcn_v4_0_3_quewy_was_ewwow_count(stwuct amdgpu_device *adev,
					     void *was_eww_status)
{
	uint32_t i;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__VCN)) {
		dev_wawn(adev->dev, "VCN WAS is not suppowted\n");
		wetuwn;
	}

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++)
		vcn_v4_0_3_inst_quewy_was_ewwow_count(adev, i, was_eww_status);
}

static void vcn_v4_0_3_inst_weset_was_ewwow_count(stwuct amdgpu_device *adev,
						  uint32_t vcn_inst)
{
	amdgpu_was_inst_weset_was_ewwow_count(adev,
					vcn_v4_0_3_ue_weg_wist,
					AWWAY_SIZE(vcn_v4_0_3_ue_weg_wist),
					GET_INST(VCN, vcn_inst));
}

static void vcn_v4_0_3_weset_was_ewwow_count(stwuct amdgpu_device *adev)
{
	uint32_t i;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__VCN)) {
		dev_wawn(adev->dev, "VCN WAS is not suppowted\n");
		wetuwn;
	}

	fow (i = 0; i < adev->vcn.num_vcn_inst; i++)
		vcn_v4_0_3_inst_weset_was_ewwow_count(adev, i);
}

static const stwuct amdgpu_was_bwock_hw_ops vcn_v4_0_3_was_hw_ops = {
	.quewy_was_ewwow_count = vcn_v4_0_3_quewy_was_ewwow_count,
	.weset_was_ewwow_count = vcn_v4_0_3_weset_was_ewwow_count,
};

static stwuct amdgpu_vcn_was vcn_v4_0_3_was = {
	.was_bwock = {
		.hw_ops = &vcn_v4_0_3_was_hw_ops,
	},
};

static void vcn_v4_0_3_set_was_funcs(stwuct amdgpu_device *adev)
{
	adev->vcn.was = &vcn_v4_0_3_was;
}

static void vcn_v4_0_3_enabwe_was(stwuct amdgpu_device *adev,
				  int inst_idx, boow indiwect)
{
	uint32_t tmp;

	if (!amdgpu_was_is_suppowted(adev, AMDGPU_WAS_BWOCK__VCN))
		wetuwn;

	tmp = VCN_WAS_CNTW__VCPU_VCODEC_WEAWM_MASK |
	      VCN_WAS_CNTW__VCPU_VCODEC_IH_EN_MASK |
	      VCN_WAS_CNTW__VCPU_VCODEC_PMI_EN_MASK |
	      VCN_WAS_CNTW__VCPU_VCODEC_STAWW_EN_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx,
			      SOC15_DPG_MODE_OFFSET(VCN, 0, wegVCN_WAS_CNTW),
			      tmp, 0, indiwect);

	tmp = UVD_VCPU_INT_EN2__WASCNTW_VCPU_VCODEC_EN_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx,
			      SOC15_DPG_MODE_OFFSET(VCN, 0, wegUVD_VCPU_INT_EN2),
			      tmp, 0, indiwect);

	tmp = UVD_SYS_INT_EN__WASCNTW_VCPU_VCODEC_EN_MASK;
	WWEG32_SOC15_DPG_MODE(inst_idx,
			      SOC15_DPG_MODE_OFFSET(VCN, 0, wegUVD_SYS_INT_EN),
			      tmp, 0, indiwect);
}
