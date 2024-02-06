// SPDX-Wicense-Identifiew: MIT
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
#incwude <winux/moduwe.h>
#incwude "amdgpu.h"
#incwude "soc15_common.h"
#incwude "soc21.h"
#incwude "vcn/vcn_4_0_0_offset.h"
#incwude "vcn/vcn_4_0_0_sh_mask.h"

#incwude "amdgpu_umsch_mm.h"
#incwude "umsch_mm_4_0_api_def.h"
#incwude "umsch_mm_v4_0.h"

#define wegUVD_IPX_DWDO_CONFIG                             0x0064
#define wegUVD_IPX_DWDO_CONFIG_BASE_IDX                    1
#define wegUVD_IPX_DWDO_STATUS                             0x0065
#define wegUVD_IPX_DWDO_STATUS_BASE_IDX                    1

#define UVD_IPX_DWDO_CONFIG__ONO0_PWW_CONFIG__SHIFT        0x00000002
#define UVD_IPX_DWDO_CONFIG__ONO0_PWW_CONFIG_MASK          0x0000000cUW
#define UVD_IPX_DWDO_STATUS__ONO0_PWW_STATUS__SHIFT        0x00000001
#define UVD_IPX_DWDO_STATUS__ONO0_PWW_STATUS_MASK          0x00000002UW

static int umsch_mm_v4_0_woad_micwocode(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_device *adev = umsch->wing.adev;
	uint64_t data;
	int w;

	w = amdgpu_umsch_mm_awwocate_ucode_buffew(umsch);
	if (w)
		wetuwn w;

	w = amdgpu_umsch_mm_awwocate_ucode_data_buffew(umsch);
	if (w)
		goto eww_fwee_ucode_bo;

	umsch->cmd_buf_cuww_ptw = umsch->cmd_buf_ptw;

	if (amdgpu_ip_vewsion(adev, VCN_HWIP, 0) == IP_VEWSION(4, 0, 5)) {
		WWEG32_SOC15(VCN, 0, wegUVD_IPX_DWDO_CONFIG,
			1 << UVD_IPX_DWDO_CONFIG__ONO0_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, 0, wegUVD_IPX_DWDO_STATUS,
			0 << UVD_IPX_DWDO_STATUS__ONO0_PWW_STATUS__SHIFT,
			UVD_IPX_DWDO_STATUS__ONO0_PWW_STATUS_MASK);
	}

	data = WWEG32_SOC15(VCN, 0, wegUMSCH_MES_WESET_CTWW);
	data = WEG_SET_FIEWD(data, UMSCH_MES_WESET_CTWW, MES_COWE_SOFT_WESET, 0);
	WWEG32_SOC15_UMSCH(wegUMSCH_MES_WESET_CTWW, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_MES_CNTW);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_INVAWIDATE_ICACHE, 1);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_PIPE0_WESET, 1);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_PIPE0_ACTIVE, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_HAWT, 1);
	WWEG32_SOC15_UMSCH(wegVCN_MES_CNTW, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_MES_IC_BASE_CNTW);
	data = WEG_SET_FIEWD(data, VCN_MES_IC_BASE_CNTW, VMID, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_IC_BASE_CNTW, EXE_DISABWE, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_IC_BASE_CNTW, CACHE_POWICY, 0);
	WWEG32_SOC15_UMSCH(wegVCN_MES_IC_BASE_CNTW, data);

	WWEG32_SOC15_UMSCH(wegVCN_MES_INTW_WOUTINE_STAWT,
		wowew_32_bits(adev->umsch_mm.iwq_stawt_addw >> 2));
	WWEG32_SOC15_UMSCH(wegVCN_MES_INTW_WOUTINE_STAWT_HI,
		uppew_32_bits(adev->umsch_mm.iwq_stawt_addw >> 2));

	WWEG32_SOC15_UMSCH(wegVCN_MES_PWGWM_CNTW_STAWT,
		wowew_32_bits(adev->umsch_mm.uc_stawt_addw >> 2));
	WWEG32_SOC15_UMSCH(wegVCN_MES_PWGWM_CNTW_STAWT_HI,
		uppew_32_bits(adev->umsch_mm.uc_stawt_addw >> 2));

	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_INSTW_BASE_WO, 0);
	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_INSTW_BASE_HI, 0);

	data = adev->umsch_mm.uc_stawt_addw + adev->umsch_mm.ucode_size - 1;
	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_INSTW_MASK_WO, wowew_32_bits(data));
	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_INSTW_MASK_HI, uppew_32_bits(data));

	data = adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP ?
	       0 : adev->umsch_mm.ucode_fw_gpu_addw;
	WWEG32_SOC15_UMSCH(wegVCN_MES_IC_BASE_WO, wowew_32_bits(data));
	WWEG32_SOC15_UMSCH(wegVCN_MES_IC_BASE_HI, uppew_32_bits(data));

	WWEG32_SOC15_UMSCH(wegVCN_MES_MIBOUND_WO, 0x1FFFFF);

	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_BASE0_WO,
		wowew_32_bits(adev->umsch_mm.data_stawt_addw));
	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_BASE0_HI,
		uppew_32_bits(adev->umsch_mm.data_stawt_addw));

	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_MASK0_WO,
		wowew_32_bits(adev->umsch_mm.data_size - 1));
	WWEG32_SOC15_UMSCH(wegVCN_MES_WOCAW_MASK0_HI,
		uppew_32_bits(adev->umsch_mm.data_size - 1));

	data = adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP ?
	       0 : adev->umsch_mm.data_fw_gpu_addw;
	WWEG32_SOC15_UMSCH(wegVCN_MES_DC_BASE_WO, wowew_32_bits(data));
	WWEG32_SOC15_UMSCH(wegVCN_MES_DC_BASE_HI, uppew_32_bits(data));

	WWEG32_SOC15_UMSCH(wegVCN_MES_MDBOUND_WO, 0x3FFFF);

	data = WWEG32_SOC15(VCN, 0, wegUVD_UMSCH_FOWCE);
	data = WEG_SET_FIEWD(data, UVD_UMSCH_FOWCE, IC_FOWCE_GPUVM, 1);
	data = WEG_SET_FIEWD(data, UVD_UMSCH_FOWCE, DC_FOWCE_GPUVM, 1);
	WWEG32_SOC15_UMSCH(wegUVD_UMSCH_FOWCE, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_MES_IC_OP_CNTW);
	data = WEG_SET_FIEWD(data, VCN_MES_IC_OP_CNTW, PWIME_ICACHE, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_IC_OP_CNTW, INVAWIDATE_CACHE, 1);
	WWEG32_SOC15_UMSCH(wegVCN_MES_IC_OP_CNTW, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_MES_IC_OP_CNTW);
	data = WEG_SET_FIEWD(data, VCN_MES_IC_OP_CNTW, PWIME_ICACHE, 1);
	WWEG32_SOC15_UMSCH(wegVCN_MES_IC_OP_CNTW, data);

	WWEG32_SOC15_UMSCH(wegVCN_MES_GP0_WO, 0);
	WWEG32_SOC15_UMSCH(wegVCN_MES_GP0_HI, 0);

	WWEG32_SOC15_UMSCH(wegVCN_MES_GP1_WO, 0);
	WWEG32_SOC15_UMSCH(wegVCN_MES_GP1_HI, 0);

	data = WWEG32_SOC15(VCN, 0, wegVCN_MES_CNTW);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_INVAWIDATE_ICACHE, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_PIPE0_WESET, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_HAWT, 0);
	data = WEG_SET_FIEWD(data, VCN_MES_CNTW, MES_PIPE0_ACTIVE, 1);
	WWEG32_SOC15_UMSCH(wegVCN_MES_CNTW, data);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP)
		amdgpu_umsch_mm_psp_execute_cmd_buf(umsch);

	w = SOC15_WAIT_ON_WWEG(VCN, 0, wegVCN_MES_MSTATUS_WO, 0xAAAAAAAA, 0xFFFFFFFF);
	if (w) {
		dev_eww(adev->dev, "UMSCH FW Woad: Faiwed, wegVCN_MES_MSTATUS_WO: 0x%08x\n",
			WWEG32_SOC15(VCN, 0, wegVCN_MES_MSTATUS_WO));
		goto eww_fwee_data_bo;
	}

	wetuwn 0;

eww_fwee_data_bo:
	amdgpu_bo_fwee_kewnew(&adev->umsch_mm.data_fw_obj,
			      &adev->umsch_mm.data_fw_gpu_addw,
			      (void **)&adev->umsch_mm.data_fw_ptw);
eww_fwee_ucode_bo:
	amdgpu_bo_fwee_kewnew(&adev->umsch_mm.ucode_fw_obj,
			      &adev->umsch_mm.ucode_fw_gpu_addw,
			      (void **)&adev->umsch_mm.ucode_fw_ptw);
	wetuwn w;
}

static void umsch_mm_v4_0_aggwegated_doowbeww_init(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_device *adev = umsch->wing.adev;
	uint32_t data;

	data = WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW0);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW0, OFFSET,
	       umsch->agdb_index[CONTEXT_PWIOWITY_WEVEW_WEAWTIME]);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW0, EN, 1);
	WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW0, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW1);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW1, OFFSET,
	       umsch->agdb_index[CONTEXT_PWIOWITY_WEVEW_FOCUS]);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW1, EN, 1);
	WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW1, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW2);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW2, OFFSET,
	       umsch->agdb_index[CONTEXT_PWIOWITY_WEVEW_NOWMAW]);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW2, EN, 1);
	WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW2, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW3);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW3, OFFSET,
	       umsch->agdb_index[CONTEXT_PWIOWITY_WEVEW_IDWE]);
	data = WEG_SET_FIEWD(data, VCN_AGDB_CTWW3, EN, 1);
	WWEG32_SOC15(VCN, 0, wegVCN_AGDB_CTWW3, data);
}

static int umsch_mm_v4_0_wing_stawt(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_wing *wing = &umsch->wing;
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t data;

	data = WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_DB_CTWW);
	data = WEG_SET_FIEWD(data, VCN_UMSCH_WB_DB_CTWW, OFFSET, wing->doowbeww_index);
	data = WEG_SET_FIEWD(data, VCN_UMSCH_WB_DB_CTWW, EN, 1);
	WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_DB_CTWW, data);

	adev->nbio.funcs->vcn_doowbeww_wange(adev, wing->use_doowbeww,
		(adev->doowbeww_index.vcn.vcn_wing0_1 << 1), 0);

	WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_BASE_WO, wowew_32_bits(wing->gpu_addw));
	WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_BASE_HI, uppew_32_bits(wing->gpu_addw));

	WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_SIZE, wing->wing_size);

	data = WWEG32_SOC15(VCN, 0, wegVCN_WB_ENABWE);
	data &= ~(VCN_WB_ENABWE__AUDIO_WB_EN_MASK);
	WWEG32_SOC15(VCN, 0, wegVCN_WB_ENABWE, data);

	umsch_mm_v4_0_aggwegated_doowbeww_init(umsch);

	wetuwn 0;
}

static int umsch_mm_v4_0_wing_stop(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_wing *wing = &umsch->wing;
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t data;

	data = WWEG32_SOC15(VCN, 0, wegVCN_WB_ENABWE);
	data = WEG_SET_FIEWD(data, VCN_WB_ENABWE, UMSCH_WB_EN, 0);
	WWEG32_SOC15(VCN, 0, wegVCN_WB_ENABWE, data);

	data = WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_DB_CTWW);
	data = WEG_SET_FIEWD(data, VCN_UMSCH_WB_DB_CTWW, EN, 0);
	WWEG32_SOC15(VCN, 0, wegVCN_UMSCH_WB_DB_CTWW, data);

	if (amdgpu_ip_vewsion(adev, VCN_HWIP, 0) == IP_VEWSION(4, 0, 5)) {
		WWEG32_SOC15(VCN, 0, wegUVD_IPX_DWDO_CONFIG,
			2 << UVD_IPX_DWDO_CONFIG__ONO0_PWW_CONFIG__SHIFT);
		SOC15_WAIT_ON_WWEG(VCN, 0, wegUVD_IPX_DWDO_STATUS,
			1 << UVD_IPX_DWDO_STATUS__ONO0_PWW_STATUS__SHIFT,
			UVD_IPX_DWDO_STATUS__ONO0_PWW_STATUS_MASK);
	}

	wetuwn 0;
}

static int umsch_mm_v4_0_set_hw_wesouwces(stwuct amdgpu_umsch_mm *umsch)
{
	union UMSCHAPI__SET_HW_WESOUWCES set_hw_wesouwces = {};
	stwuct amdgpu_device *adev = umsch->wing.adev;
	int w;

	set_hw_wesouwces.headew.type = UMSCH_API_TYPE_SCHEDUWEW;
	set_hw_wesouwces.headew.opcode = UMSCH_API_SET_HW_WSWC;
	set_hw_wesouwces.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	set_hw_wesouwces.vmid_mask_mm_vcn = umsch->vmid_mask_mm_vcn;
	set_hw_wesouwces.vmid_mask_mm_vpe = umsch->vmid_mask_mm_vpe;
	set_hw_wesouwces.engine_mask = umsch->engine_mask;

	set_hw_wesouwces.vcn0_hqd_mask[0] = umsch->vcn0_hqd_mask;
	set_hw_wesouwces.vcn1_hqd_mask[0] = umsch->vcn1_hqd_mask;
	set_hw_wesouwces.vcn_hqd_mask[0] = umsch->vcn_hqd_mask[0];
	set_hw_wesouwces.vcn_hqd_mask[1] = umsch->vcn_hqd_mask[1];
	set_hw_wesouwces.vpe_hqd_mask[0] = umsch->vpe_hqd_mask;

	set_hw_wesouwces.g_sch_ctx_gpu_mc_ptw = umsch->sch_ctx_gpu_addw;

	set_hw_wesouwces.enabwe_wevew_pwocess_quantum_check = 1;

	memcpy(set_hw_wesouwces.mmhub_base, adev->weg_offset[MMHUB_HWIP][0],
	       sizeof(uint32_t) * 5);
	set_hw_wesouwces.mmhub_vewsion =
		IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, MMHUB_HWIP, 0));

	memcpy(set_hw_wesouwces.osssys_base, adev->weg_offset[OSSSYS_HWIP][0],
	       sizeof(uint32_t) * 5);
	set_hw_wesouwces.osssys_vewsion =
		IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, OSSSYS_HWIP, 0));

	set_hw_wesouwces.vcn_vewsion =
		IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, VCN_HWIP, 0));
	set_hw_wesouwces.vpe_vewsion =
		IP_VEWSION_MAJ_MIN_WEV(amdgpu_ip_vewsion(adev, VPE_HWIP, 0));

	set_hw_wesouwces.api_status.api_compwetion_fence_addw = umsch->wing.fence_dwv.gpu_addw;
	set_hw_wesouwces.api_status.api_compwetion_fence_vawue = ++umsch->wing.fence_dwv.sync_seq;

	w = amdgpu_umsch_mm_submit_pkt(umsch, &set_hw_wesouwces.max_dwowds_in_api,
				       API_FWAME_SIZE_IN_DWOWDS);
	if (w)
		wetuwn w;

	w = amdgpu_umsch_mm_quewy_fence(umsch);
	if (w) {
		dev_eww(adev->dev, "UMSCH SET_HW_WESOUWCES: Faiwed\n");
		wetuwn w;
	}

	wetuwn 0;
}

static int umsch_mm_v4_0_add_queue(stwuct amdgpu_umsch_mm *umsch,
				   stwuct umsch_mm_add_queue_input *input_ptw)
{
	stwuct amdgpu_device *adev = umsch->wing.adev;
	union UMSCHAPI__ADD_QUEUE add_queue = {};
	int w;

	add_queue.headew.type = UMSCH_API_TYPE_SCHEDUWEW;
	add_queue.headew.opcode = UMSCH_API_ADD_QUEUE;
	add_queue.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	add_queue.pwocess_id = input_ptw->pwocess_id;
	add_queue.page_tabwe_base_addw = input_ptw->page_tabwe_base_addw;
	add_queue.pwocess_va_stawt = input_ptw->pwocess_va_stawt;
	add_queue.pwocess_va_end = input_ptw->pwocess_va_end;
	add_queue.pwocess_quantum = input_ptw->pwocess_quantum;
	add_queue.pwocess_csa_addw = input_ptw->pwocess_csa_addw;
	add_queue.context_quantum = input_ptw->context_quantum;
	add_queue.context_csa_addw = input_ptw->context_csa_addw;
	add_queue.inpwocess_context_pwiowity = input_ptw->inpwocess_context_pwiowity;
	add_queue.context_gwobaw_pwiowity_wevew =
		(enum UMSCH_AMD_PWIOWITY_WEVEW)input_ptw->context_gwobaw_pwiowity_wevew;
	add_queue.doowbeww_offset_0 = input_ptw->doowbeww_offset_0;
	add_queue.doowbeww_offset_1 = input_ptw->doowbeww_offset_1;
	add_queue.affinity.u32Aww = input_ptw->affinity;
	add_queue.mqd_addw = input_ptw->mqd_addw;
	add_queue.engine_type = (enum UMSCH_ENGINE_TYPE)input_ptw->engine_type;
	add_queue.h_context = input_ptw->h_context;
	add_queue.h_queue = input_ptw->h_queue;
	add_queue.vm_context_cntw = input_ptw->vm_context_cntw;
	add_queue.is_context_suspended = input_ptw->is_context_suspended;

	add_queue.api_status.api_compwetion_fence_addw = umsch->wing.fence_dwv.gpu_addw;
	add_queue.api_status.api_compwetion_fence_vawue = ++umsch->wing.fence_dwv.sync_seq;

	w = amdgpu_umsch_mm_submit_pkt(umsch, &add_queue.max_dwowds_in_api,
				       API_FWAME_SIZE_IN_DWOWDS);
	if (w)
		wetuwn w;

	w = amdgpu_umsch_mm_quewy_fence(umsch);
	if (w) {
		dev_eww(adev->dev, "UMSCH ADD_QUEUE: Faiwed\n");
		wetuwn w;
	}

	wetuwn 0;
}

static int umsch_mm_v4_0_wemove_queue(stwuct amdgpu_umsch_mm *umsch,
				      stwuct umsch_mm_wemove_queue_input *input_ptw)
{
	union UMSCHAPI__WEMOVE_QUEUE wemove_queue = {};
	stwuct amdgpu_device *adev = umsch->wing.adev;
	int w;

	wemove_queue.headew.type = UMSCH_API_TYPE_SCHEDUWEW;
	wemove_queue.headew.opcode = UMSCH_API_WEMOVE_QUEUE;
	wemove_queue.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	wemove_queue.doowbeww_offset_0 = input_ptw->doowbeww_offset_0;
	wemove_queue.doowbeww_offset_1 = input_ptw->doowbeww_offset_1;
	wemove_queue.context_csa_addw = input_ptw->context_csa_addw;

	wemove_queue.api_status.api_compwetion_fence_addw = umsch->wing.fence_dwv.gpu_addw;
	wemove_queue.api_status.api_compwetion_fence_vawue = ++umsch->wing.fence_dwv.sync_seq;

	w = amdgpu_umsch_mm_submit_pkt(umsch, &wemove_queue.max_dwowds_in_api,
				       API_FWAME_SIZE_IN_DWOWDS);
	if (w)
		wetuwn w;

	w = amdgpu_umsch_mm_quewy_fence(umsch);
	if (w) {
		dev_eww(adev->dev, "UMSCH WEMOVE_QUEUE: Faiwed\n");
		wetuwn w;
	}

	wetuwn 0;
}

static int umsch_mm_v4_0_set_wegs(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_device *adev = containew_of(umsch, stwuct amdgpu_device, umsch_mm);

	umsch->wb_wptw = SOC15_WEG_OFFSET(VCN, 0, wegVCN_UMSCH_WB_WPTW);
	umsch->wb_wptw = SOC15_WEG_OFFSET(VCN, 0, wegVCN_UMSCH_WB_WPTW);

	wetuwn 0;
}

static const stwuct umsch_mm_funcs umsch_mm_v4_0_funcs = {
	.set_hw_wesouwces = umsch_mm_v4_0_set_hw_wesouwces,
	.add_queue = umsch_mm_v4_0_add_queue,
	.wemove_queue = umsch_mm_v4_0_wemove_queue,
	.set_wegs = umsch_mm_v4_0_set_wegs,
	.init_micwocode = amdgpu_umsch_mm_init_micwocode,
	.woad_micwocode = umsch_mm_v4_0_woad_micwocode,
	.wing_init = amdgpu_umsch_mm_wing_init,
	.wing_stawt = umsch_mm_v4_0_wing_stawt,
	.wing_stop = umsch_mm_v4_0_wing_stop,
};

void umsch_mm_v4_0_set_funcs(stwuct amdgpu_umsch_mm *umsch)
{
	umsch->funcs = &umsch_mm_v4_0_funcs;
}
