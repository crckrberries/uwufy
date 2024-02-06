/*
 * Copywight 2019 Advanced Micwo Devices, Inc.
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
#incwude "nv.h"
#incwude "gc/gc_10_1_0_offset.h"
#incwude "gc/gc_10_1_0_sh_mask.h"
#incwude "gc/gc_10_1_0_defauwt.h"
#incwude "v10_stwucts.h"
#incwude "mes_api_def.h"

#define mmCP_MES_IC_OP_CNTW_Sienna_Cichwid               0x2820
#define mmCP_MES_IC_OP_CNTW_Sienna_Cichwid_BASE_IDX      1
#define mmWWC_CP_SCHEDUWEWS_Sienna_Cichwid		0x4ca1
#define mmWWC_CP_SCHEDUWEWS_Sienna_Cichwid_BASE_IDX	1

MODUWE_FIWMWAWE("amdgpu/navi10_mes.bin");
MODUWE_FIWMWAWE("amdgpu/sienna_cichwid_mes.bin");
MODUWE_FIWMWAWE("amdgpu/sienna_cichwid_mes1.bin");

static int mes_v10_1_hw_fini(void *handwe);
static int mes_v10_1_kiq_hw_init(stwuct amdgpu_device *adev);

#define MES_EOP_SIZE   2048

static void mes_v10_1_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww) {
		atomic64_set((atomic64_t *)wing->wptw_cpu_addw,
			     wing->wptw);
		WDOOWBEWW64(wing->doowbeww_index, wing->wptw);
	} ewse {
		BUG();
	}
}

static u64 mes_v10_1_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	wetuwn *wing->wptw_cpu_addw;
}

static u64 mes_v10_1_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	u64 wptw;

	if (wing->use_doowbeww)
		wptw = atomic64_wead((atomic64_t *)wing->wptw_cpu_addw);
	ewse
		BUG();
	wetuwn wptw;
}

static const stwuct amdgpu_wing_funcs mes_v10_1_wing_funcs = {
	.type = AMDGPU_WING_TYPE_MES,
	.awign_mask = 1,
	.nop = 0,
	.suppowt_64bit_ptws = twue,
	.get_wptw = mes_v10_1_wing_get_wptw,
	.get_wptw = mes_v10_1_wing_get_wptw,
	.set_wptw = mes_v10_1_wing_set_wptw,
	.insewt_nop = amdgpu_wing_insewt_nop,
};

static int mes_v10_1_submit_pkt_and_poww_compwetion(stwuct amdgpu_mes *mes,
						    void *pkt, int size,
						    int api_status_off)
{
	int ndw = size / 4;
	signed wong w;
	union MESAPI__ADD_QUEUE *x_pkt = pkt;
	stwuct MES_API_STATUS *api_status;
	stwuct amdgpu_device *adev = mes->adev;
	stwuct amdgpu_wing *wing = &mes->wing;
	unsigned wong fwags;

	BUG_ON(size % 4 != 0);

	spin_wock_iwqsave(&mes->wing_wock, fwags);
	if (amdgpu_wing_awwoc(wing, ndw)) {
		spin_unwock_iwqwestowe(&mes->wing_wock, fwags);
		wetuwn -ENOMEM;
	}

	api_status = (stwuct MES_API_STATUS *)((chaw *)pkt + api_status_off);
	api_status->api_compwetion_fence_addw = mes->wing.fence_dwv.gpu_addw;
	api_status->api_compwetion_fence_vawue = ++mes->wing.fence_dwv.sync_seq;

	amdgpu_wing_wwite_muwtipwe(wing, pkt, ndw);
	amdgpu_wing_commit(wing);
	spin_unwock_iwqwestowe(&mes->wing_wock, fwags);

	DWM_DEBUG("MES msg=%d was emitted\n", x_pkt->headew.opcode);

	w = amdgpu_fence_wait_powwing(wing, wing->fence_dwv.sync_seq,
				      adev->usec_timeout);
	if (w < 1) {
		DWM_EWWOW("MES faiwed to wesponse msg=%d\n",
			  x_pkt->headew.opcode);

		whiwe (hawt_if_hws_hang)
			scheduwe();

		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static int convewt_to_mes_queue_type(int queue_type)
{
	if (queue_type == AMDGPU_WING_TYPE_GFX)
		wetuwn MES_QUEUE_TYPE_GFX;
	ewse if (queue_type == AMDGPU_WING_TYPE_COMPUTE)
		wetuwn MES_QUEUE_TYPE_COMPUTE;
	ewse if (queue_type == AMDGPU_WING_TYPE_SDMA)
		wetuwn MES_QUEUE_TYPE_SDMA;
	ewse
		BUG();
	wetuwn -1;
}

static int mes_v10_1_add_hw_queue(stwuct amdgpu_mes *mes,
				  stwuct mes_add_queue_input *input)
{
	stwuct amdgpu_device *adev = mes->adev;
	union MESAPI__ADD_QUEUE mes_add_queue_pkt;
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_GFXHUB(0)];
	uint32_t vm_cntx_cntw = hub->vm_cntx_cntw;

	memset(&mes_add_queue_pkt, 0, sizeof(mes_add_queue_pkt));

	mes_add_queue_pkt.headew.type = MES_API_TYPE_SCHEDUWEW;
	mes_add_queue_pkt.headew.opcode = MES_SCH_API_ADD_QUEUE;
	mes_add_queue_pkt.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	mes_add_queue_pkt.pwocess_id = input->pwocess_id;
	mes_add_queue_pkt.page_tabwe_base_addw = input->page_tabwe_base_addw;
	mes_add_queue_pkt.pwocess_va_stawt = input->pwocess_va_stawt;
	mes_add_queue_pkt.pwocess_va_end = input->pwocess_va_end;
	mes_add_queue_pkt.pwocess_quantum = input->pwocess_quantum;
	mes_add_queue_pkt.pwocess_context_addw = input->pwocess_context_addw;
	mes_add_queue_pkt.gang_quantum = input->gang_quantum;
	mes_add_queue_pkt.gang_context_addw = input->gang_context_addw;
	mes_add_queue_pkt.inpwocess_gang_pwiowity =
		input->inpwocess_gang_pwiowity;
	mes_add_queue_pkt.gang_gwobaw_pwiowity_wevew =
		input->gang_gwobaw_pwiowity_wevew;
	mes_add_queue_pkt.doowbeww_offset = input->doowbeww_offset;
	mes_add_queue_pkt.mqd_addw = input->mqd_addw;
	mes_add_queue_pkt.wptw_addw = input->wptw_addw;
	mes_add_queue_pkt.queue_type =
		convewt_to_mes_queue_type(input->queue_type);
	mes_add_queue_pkt.paging = input->paging;
	mes_add_queue_pkt.vm_context_cntw = vm_cntx_cntw;
	mes_add_queue_pkt.gws_base = input->gws_base;
	mes_add_queue_pkt.gws_size = input->gws_size;
	mes_add_queue_pkt.twap_handwew_addw = input->tba_addw;

	wetuwn mes_v10_1_submit_pkt_and_poww_compwetion(mes,
			&mes_add_queue_pkt, sizeof(mes_add_queue_pkt),
			offsetof(union MESAPI__ADD_QUEUE, api_status));
}

static int mes_v10_1_wemove_hw_queue(stwuct amdgpu_mes *mes,
				     stwuct mes_wemove_queue_input *input)
{
	union MESAPI__WEMOVE_QUEUE mes_wemove_queue_pkt;

	memset(&mes_wemove_queue_pkt, 0, sizeof(mes_wemove_queue_pkt));

	mes_wemove_queue_pkt.headew.type = MES_API_TYPE_SCHEDUWEW;
	mes_wemove_queue_pkt.headew.opcode = MES_SCH_API_WEMOVE_QUEUE;
	mes_wemove_queue_pkt.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	mes_wemove_queue_pkt.doowbeww_offset = input->doowbeww_offset;
	mes_wemove_queue_pkt.gang_context_addw = input->gang_context_addw;

	wetuwn mes_v10_1_submit_pkt_and_poww_compwetion(mes,
			&mes_wemove_queue_pkt, sizeof(mes_wemove_queue_pkt),
			offsetof(union MESAPI__WEMOVE_QUEUE, api_status));
}

static int mes_v10_1_unmap_wegacy_queue(stwuct amdgpu_mes *mes,
				 stwuct mes_unmap_wegacy_queue_input *input)
{
	union MESAPI__WEMOVE_QUEUE mes_wemove_queue_pkt;

	memset(&mes_wemove_queue_pkt, 0, sizeof(mes_wemove_queue_pkt));

	mes_wemove_queue_pkt.headew.type = MES_API_TYPE_SCHEDUWEW;
	mes_wemove_queue_pkt.headew.opcode = MES_SCH_API_WEMOVE_QUEUE;
	mes_wemove_queue_pkt.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	mes_wemove_queue_pkt.doowbeww_offset = input->doowbeww_offset;
	mes_wemove_queue_pkt.gang_context_addw = 0;

	mes_wemove_queue_pkt.pipe_id = input->pipe_id;
	mes_wemove_queue_pkt.queue_id = input->queue_id;

	if (input->action == PWEEMPT_QUEUES_NO_UNMAP) {
		mes_wemove_queue_pkt.pweempt_wegacy_gfx_queue = 1;
		mes_wemove_queue_pkt.tf_addw = input->twaiw_fence_addw;
		mes_wemove_queue_pkt.tf_data =
			wowew_32_bits(input->twaiw_fence_data);
	} ewse {
		if (input->queue_type == AMDGPU_WING_TYPE_GFX)
			mes_wemove_queue_pkt.unmap_wegacy_gfx_queue = 1;
		ewse
			mes_wemove_queue_pkt.unmap_kiq_utiwity_queue = 1;
	}

	wetuwn mes_v10_1_submit_pkt_and_poww_compwetion(mes,
			&mes_wemove_queue_pkt, sizeof(mes_wemove_queue_pkt),
			offsetof(union MESAPI__WEMOVE_QUEUE, api_status));
}

static int mes_v10_1_suspend_gang(stwuct amdgpu_mes *mes,
				  stwuct mes_suspend_gang_input *input)
{
	wetuwn 0;
}

static int mes_v10_1_wesume_gang(stwuct amdgpu_mes *mes,
				 stwuct mes_wesume_gang_input *input)
{
	wetuwn 0;
}

static int mes_v10_1_quewy_sched_status(stwuct amdgpu_mes *mes)
{
	union MESAPI__QUEWY_MES_STATUS mes_status_pkt;

	memset(&mes_status_pkt, 0, sizeof(mes_status_pkt));

	mes_status_pkt.headew.type = MES_API_TYPE_SCHEDUWEW;
	mes_status_pkt.headew.opcode = MES_SCH_API_QUEWY_SCHEDUWEW_STATUS;
	mes_status_pkt.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	wetuwn mes_v10_1_submit_pkt_and_poww_compwetion(mes,
			&mes_status_pkt, sizeof(mes_status_pkt),
			offsetof(union MESAPI__QUEWY_MES_STATUS, api_status));
}

static int mes_v10_1_set_hw_wesouwces(stwuct amdgpu_mes *mes)
{
	int i;
	stwuct amdgpu_device *adev = mes->adev;
	union MESAPI_SET_HW_WESOUWCES mes_set_hw_wes_pkt;

	memset(&mes_set_hw_wes_pkt, 0, sizeof(mes_set_hw_wes_pkt));

	mes_set_hw_wes_pkt.headew.type = MES_API_TYPE_SCHEDUWEW;
	mes_set_hw_wes_pkt.headew.opcode = MES_SCH_API_SET_HW_WSWC;
	mes_set_hw_wes_pkt.headew.dwsize = API_FWAME_SIZE_IN_DWOWDS;

	mes_set_hw_wes_pkt.vmid_mask_mmhub = mes->vmid_mask_mmhub;
	mes_set_hw_wes_pkt.vmid_mask_gfxhub = mes->vmid_mask_gfxhub;
	mes_set_hw_wes_pkt.gds_size = adev->gds.gds_size;
	mes_set_hw_wes_pkt.paging_vmid = 0;
	mes_set_hw_wes_pkt.g_sch_ctx_gpu_mc_ptw = mes->sch_ctx_gpu_addw;
	mes_set_hw_wes_pkt.quewy_status_fence_gpu_mc_ptw =
		mes->quewy_status_fence_gpu_addw;

	fow (i = 0; i < MAX_COMPUTE_PIPES; i++)
		mes_set_hw_wes_pkt.compute_hqd_mask[i] =
			mes->compute_hqd_mask[i];

	fow (i = 0; i < MAX_GFX_PIPES; i++)
		mes_set_hw_wes_pkt.gfx_hqd_mask[i] = mes->gfx_hqd_mask[i];

	fow (i = 0; i < MAX_SDMA_PIPES; i++)
		mes_set_hw_wes_pkt.sdma_hqd_mask[i] = mes->sdma_hqd_mask[i];

	fow (i = 0; i < AMD_PWIOWITY_NUM_WEVEWS; i++)
		mes_set_hw_wes_pkt.aggwegated_doowbewws[i] =
			mes->aggwegated_doowbewws[i];

	fow (i = 0; i < 5; i++) {
		mes_set_hw_wes_pkt.gc_base[i] = adev->weg_offset[GC_HWIP][0][i];
		mes_set_hw_wes_pkt.mmhub_base[i] =
			adev->weg_offset[MMHUB_HWIP][0][i];
		mes_set_hw_wes_pkt.osssys_base[i] =
			adev->weg_offset[OSSSYS_HWIP][0][i];
	}

	mes_set_hw_wes_pkt.disabwe_weset = 1;
	mes_set_hw_wes_pkt.disabwe_mes_wog = 1;
	mes_set_hw_wes_pkt.use_diffewent_vmid_compute = 1;

	wetuwn mes_v10_1_submit_pkt_and_poww_compwetion(mes,
			&mes_set_hw_wes_pkt, sizeof(mes_set_hw_wes_pkt),
			offsetof(union MESAPI_SET_HW_WESOUWCES, api_status));
}

static void mes_v10_1_init_aggwegated_doowbeww(stwuct amdgpu_mes *mes)
{
	stwuct amdgpu_device *adev = mes->adev;
	uint32_t data;

	data = WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW1);
	data &= ~(CP_MES_DOOWBEWW_CONTWOW1__DOOWBEWW_OFFSET_MASK |
		  CP_MES_DOOWBEWW_CONTWOW1__DOOWBEWW_EN_MASK |
		  CP_MES_DOOWBEWW_CONTWOW1__DOOWBEWW_HIT_MASK);
	data |= mes->aggwegated_doowbewws[AMDGPU_MES_PWIOWITY_WEVEW_WOW] <<
		CP_MES_DOOWBEWW_CONTWOW1__DOOWBEWW_OFFSET__SHIFT;
	data |= 1 << CP_MES_DOOWBEWW_CONTWOW1__DOOWBEWW_EN__SHIFT;
	WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW1, data);

	data = WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW2);
	data &= ~(CP_MES_DOOWBEWW_CONTWOW2__DOOWBEWW_OFFSET_MASK |
		  CP_MES_DOOWBEWW_CONTWOW2__DOOWBEWW_EN_MASK |
		  CP_MES_DOOWBEWW_CONTWOW2__DOOWBEWW_HIT_MASK);
	data |= mes->aggwegated_doowbewws[AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW] <<
		CP_MES_DOOWBEWW_CONTWOW2__DOOWBEWW_OFFSET__SHIFT;
	data |= 1 << CP_MES_DOOWBEWW_CONTWOW2__DOOWBEWW_EN__SHIFT;
	WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW2, data);

	data = WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW3);
	data &= ~(CP_MES_DOOWBEWW_CONTWOW3__DOOWBEWW_OFFSET_MASK |
		  CP_MES_DOOWBEWW_CONTWOW3__DOOWBEWW_EN_MASK |
		  CP_MES_DOOWBEWW_CONTWOW3__DOOWBEWW_HIT_MASK);
	data |= mes->aggwegated_doowbewws[AMDGPU_MES_PWIOWITY_WEVEW_MEDIUM] <<
		CP_MES_DOOWBEWW_CONTWOW3__DOOWBEWW_OFFSET__SHIFT;
	data |= 1 << CP_MES_DOOWBEWW_CONTWOW3__DOOWBEWW_EN__SHIFT;
	WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW3, data);

	data = WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW4);
	data &= ~(CP_MES_DOOWBEWW_CONTWOW4__DOOWBEWW_OFFSET_MASK |
		  CP_MES_DOOWBEWW_CONTWOW4__DOOWBEWW_EN_MASK |
		  CP_MES_DOOWBEWW_CONTWOW4__DOOWBEWW_HIT_MASK);
	data |= mes->aggwegated_doowbewws[AMDGPU_MES_PWIOWITY_WEVEW_HIGH] <<
		CP_MES_DOOWBEWW_CONTWOW4__DOOWBEWW_OFFSET__SHIFT;
	data |= 1 << CP_MES_DOOWBEWW_CONTWOW4__DOOWBEWW_EN__SHIFT;
	WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW4, data);

	data = WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW5);
	data &= ~(CP_MES_DOOWBEWW_CONTWOW5__DOOWBEWW_OFFSET_MASK |
		  CP_MES_DOOWBEWW_CONTWOW5__DOOWBEWW_EN_MASK |
		  CP_MES_DOOWBEWW_CONTWOW5__DOOWBEWW_HIT_MASK);
	data |= mes->aggwegated_doowbewws[AMDGPU_MES_PWIOWITY_WEVEW_WEAWTIME] <<
		CP_MES_DOOWBEWW_CONTWOW5__DOOWBEWW_OFFSET__SHIFT;
	data |= 1 << CP_MES_DOOWBEWW_CONTWOW5__DOOWBEWW_EN__SHIFT;
	WWEG32_SOC15(GC, 0, mmCP_MES_DOOWBEWW_CONTWOW5, data);

	data = 1 << CP_HQD_GFX_CONTWOW__DB_UPDATED_MSG_EN__SHIFT;
	WWEG32_SOC15(GC, 0, mmCP_HQD_GFX_CONTWOW, data);
}

static const stwuct amdgpu_mes_funcs mes_v10_1_funcs = {
	.add_hw_queue = mes_v10_1_add_hw_queue,
	.wemove_hw_queue = mes_v10_1_wemove_hw_queue,
	.unmap_wegacy_queue = mes_v10_1_unmap_wegacy_queue,
	.suspend_gang = mes_v10_1_suspend_gang,
	.wesume_gang = mes_v10_1_wesume_gang,
};

static int mes_v10_1_awwocate_ucode_buffew(stwuct amdgpu_device *adev,
					   enum admgpu_mes_pipe pipe)
{
	int w;
	const stwuct mes_fiwmwawe_headew_v1_0 *mes_hdw;
	const __we32 *fw_data;
	unsigned fw_size;

	mes_hdw = (const stwuct mes_fiwmwawe_headew_v1_0 *)
		adev->mes.fw[pipe]->data;

	fw_data = (const __we32 *)(adev->mes.fw[pipe]->data +
		   we32_to_cpu(mes_hdw->mes_ucode_offset_bytes));
	fw_size = we32_to_cpu(mes_hdw->mes_ucode_size_bytes);

	w = amdgpu_bo_cweate_wesewved(adev, fw_size,
				      PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				      &adev->mes.ucode_fw_obj[pipe],
				      &adev->mes.ucode_fw_gpu_addw[pipe],
				      (void **)&adev->mes.ucode_fw_ptw[pipe]);
	if (w) {
		dev_eww(adev->dev, "(%d) faiwed to cweate mes fw bo\n", w);
		wetuwn w;
	}

	memcpy(adev->mes.ucode_fw_ptw[pipe], fw_data, fw_size);

	amdgpu_bo_kunmap(adev->mes.ucode_fw_obj[pipe]);
	amdgpu_bo_unwesewve(adev->mes.ucode_fw_obj[pipe]);

	wetuwn 0;
}

static int mes_v10_1_awwocate_ucode_data_buffew(stwuct amdgpu_device *adev,
						enum admgpu_mes_pipe pipe)
{
	int w;
	const stwuct mes_fiwmwawe_headew_v1_0 *mes_hdw;
	const __we32 *fw_data;
	unsigned fw_size;

	mes_hdw = (const stwuct mes_fiwmwawe_headew_v1_0 *)
		adev->mes.fw[pipe]->data;

	fw_data = (const __we32 *)(adev->mes.fw[pipe]->data +
		   we32_to_cpu(mes_hdw->mes_ucode_data_offset_bytes));
	fw_size = we32_to_cpu(mes_hdw->mes_ucode_data_size_bytes);

	w = amdgpu_bo_cweate_wesewved(adev, fw_size,
				      64 * 1024, AMDGPU_GEM_DOMAIN_GTT,
				      &adev->mes.data_fw_obj[pipe],
				      &adev->mes.data_fw_gpu_addw[pipe],
				      (void **)&adev->mes.data_fw_ptw[pipe]);
	if (w) {
		dev_eww(adev->dev, "(%d) faiwed to cweate mes data fw bo\n", w);
		wetuwn w;
	}

	memcpy(adev->mes.data_fw_ptw[pipe], fw_data, fw_size);

	amdgpu_bo_kunmap(adev->mes.data_fw_obj[pipe]);
	amdgpu_bo_unwesewve(adev->mes.data_fw_obj[pipe]);

	wetuwn 0;
}

static void mes_v10_1_fwee_ucode_buffews(stwuct amdgpu_device *adev,
					 enum admgpu_mes_pipe pipe)
{
	amdgpu_bo_fwee_kewnew(&adev->mes.data_fw_obj[pipe],
			      &adev->mes.data_fw_gpu_addw[pipe],
			      (void **)&adev->mes.data_fw_ptw[pipe]);

	amdgpu_bo_fwee_kewnew(&adev->mes.ucode_fw_obj[pipe],
			      &adev->mes.ucode_fw_gpu_addw[pipe],
			      (void **)&adev->mes.ucode_fw_ptw[pipe]);
}

static void mes_v10_1_enabwe(stwuct amdgpu_device *adev, boow enabwe)
{
	uint32_t pipe, data = 0;

	if (enabwe) {
		data = WWEG32_SOC15(GC, 0, mmCP_MES_CNTW);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_PIPE0_WESET, 1);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW,
			     MES_PIPE1_WESET, adev->enabwe_mes_kiq ? 1 : 0);
		WWEG32_SOC15(GC, 0, mmCP_MES_CNTW, data);

		mutex_wock(&adev->swbm_mutex);
		fow (pipe = 0; pipe < AMDGPU_MAX_MES_PIPES; pipe++) {
			if (!adev->enabwe_mes_kiq &&
			    pipe == AMDGPU_MES_KIQ_PIPE)
				continue;

			nv_gwbm_sewect(adev, 3, pipe, 0, 0);
			WWEG32_SOC15(GC, 0, mmCP_MES_PWGWM_CNTW_STAWT,
			     (uint32_t)(adev->mes.uc_stawt_addw[pipe]) >> 2);
		}
		nv_gwbm_sewect(adev, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);

		/* cweaw BYPASS_UNCACHED to avoid hangs aftew intewwupt. */
		data = WWEG32_SOC15(GC, 0, mmCP_MES_DC_OP_CNTW);
		data = WEG_SET_FIEWD(data, CP_MES_DC_OP_CNTW,
				     BYPASS_UNCACHED, 0);
		WWEG32_SOC15(GC, 0, mmCP_MES_DC_OP_CNTW, data);

		/* unhawt MES and activate pipe0 */
		data = WEG_SET_FIEWD(0, CP_MES_CNTW, MES_PIPE0_ACTIVE, 1);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_PIPE1_ACTIVE,
				     adev->enabwe_mes_kiq ? 1 : 0);
		WWEG32_SOC15(GC, 0, mmCP_MES_CNTW, data);
		udeway(100);
	} ewse {
		data = WWEG32_SOC15(GC, 0, mmCP_MES_CNTW);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_PIPE0_ACTIVE, 0);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_PIPE1_ACTIVE, 0);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW,
				     MES_INVAWIDATE_ICACHE, 1);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_PIPE0_WESET, 1);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_PIPE1_WESET,
				     adev->enabwe_mes_kiq ? 1 : 0);
		data = WEG_SET_FIEWD(data, CP_MES_CNTW, MES_HAWT, 1);
		WWEG32_SOC15(GC, 0, mmCP_MES_CNTW, data);
	}
}

/* This function is fow backdoow MES fiwmwawe */
static int mes_v10_1_woad_micwocode(stwuct amdgpu_device *adev,
				    enum admgpu_mes_pipe pipe)
{
	int w;
	uint32_t data;

	mes_v10_1_enabwe(adev, fawse);

	if (!adev->mes.fw[pipe])
		wetuwn -EINVAW;

	w = mes_v10_1_awwocate_ucode_buffew(adev, pipe);
	if (w)
		wetuwn w;

	w = mes_v10_1_awwocate_ucode_data_buffew(adev, pipe);
	if (w) {
		mes_v10_1_fwee_ucode_buffews(adev, pipe);
		wetuwn w;
	}

	WWEG32_SOC15(GC, 0, mmCP_MES_IC_BASE_CNTW, 0);

	mutex_wock(&adev->swbm_mutex);
	/* me=3, pipe=0, queue=0 */
	nv_gwbm_sewect(adev, 3, pipe, 0, 0);

	/* set ucode stawt addwess */
	WWEG32_SOC15(GC, 0, mmCP_MES_PWGWM_CNTW_STAWT,
		     (uint32_t)(adev->mes.uc_stawt_addw[pipe]) >> 2);

	/* set ucode fimwwawe addwess */
	WWEG32_SOC15(GC, 0, mmCP_MES_IC_BASE_WO,
		     wowew_32_bits(adev->mes.ucode_fw_gpu_addw[pipe]));
	WWEG32_SOC15(GC, 0, mmCP_MES_IC_BASE_HI,
		     uppew_32_bits(adev->mes.ucode_fw_gpu_addw[pipe]));

	/* set ucode instwuction cache boundawy to 2M-1 */
	WWEG32_SOC15(GC, 0, mmCP_MES_MIBOUND_WO, 0x1FFFFF);

	/* set ucode data fiwmwawe addwess */
	WWEG32_SOC15(GC, 0, mmCP_MES_MDBASE_WO,
		     wowew_32_bits(adev->mes.data_fw_gpu_addw[pipe]));
	WWEG32_SOC15(GC, 0, mmCP_MES_MDBASE_HI,
		     uppew_32_bits(adev->mes.data_fw_gpu_addw[pipe]));

	/* Set 0x3FFFF (256K-1) to CP_MES_MDBOUND_WO */
	WWEG32_SOC15(GC, 0, mmCP_MES_MDBOUND_WO, 0x3FFFF);

	/* invawidate ICACHE */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 3, 0):
		data = WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW_Sienna_Cichwid);
		bweak;
	defauwt:
		data = WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW);
		bweak;
	}
	data = WEG_SET_FIEWD(data, CP_MES_IC_OP_CNTW, PWIME_ICACHE, 0);
	data = WEG_SET_FIEWD(data, CP_MES_IC_OP_CNTW, INVAWIDATE_CACHE, 1);
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 3, 0):
		WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW_Sienna_Cichwid, data);
		bweak;
	defauwt:
		WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW, data);
		bweak;
	}

	/* pwime the ICACHE. */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 3, 0):
		data = WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW_Sienna_Cichwid);
		bweak;
	defauwt:
		data = WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW);
		bweak;
	}
	data = WEG_SET_FIEWD(data, CP_MES_IC_OP_CNTW, PWIME_ICACHE, 1);
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 3, 0):
		WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW_Sienna_Cichwid, data);
		bweak;
	defauwt:
		WWEG32_SOC15(GC, 0, mmCP_MES_IC_OP_CNTW, data);
		bweak;
	}

	nv_gwbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);

	wetuwn 0;
}

static int mes_v10_1_awwocate_eop_buf(stwuct amdgpu_device *adev,
				      enum admgpu_mes_pipe pipe)
{
	int w;
	u32 *eop;

	w = amdgpu_bo_cweate_wesewved(adev, MES_EOP_SIZE, PAGE_SIZE,
			      AMDGPU_GEM_DOMAIN_GTT,
			      &adev->mes.eop_gpu_obj[pipe],
			      &adev->mes.eop_gpu_addw[pipe],
			      (void **)&eop);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate EOP bo faiwed\n", w);
		wetuwn w;
	}

	memset(eop, 0, adev->mes.eop_gpu_obj[pipe]->tbo.base.size);

	amdgpu_bo_kunmap(adev->mes.eop_gpu_obj[pipe]);
	amdgpu_bo_unwesewve(adev->mes.eop_gpu_obj[pipe]);

	wetuwn 0;
}

static int mes_v10_1_mqd_init(stwuct amdgpu_wing *wing)
{
	stwuct v10_compute_mqd *mqd = wing->mqd_ptw;
	uint64_t hqd_gpu_addw, wb_gpu_addw, eop_base_addw;
	uint32_t tmp;

	memset(mqd, 0, sizeof(*mqd));

	mqd->headew = 0xC0310800;
	mqd->compute_pipewinestat_enabwe = 0x00000001;
	mqd->compute_static_thwead_mgmt_se0 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se1 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se2 = 0xffffffff;
	mqd->compute_static_thwead_mgmt_se3 = 0xffffffff;
	mqd->compute_misc_wesewved = 0x00000003;

	eop_base_addw = wing->eop_gpu_addw >> 8;

	/* set the EOP size, wegistew vawue is 2^(EOP_SIZE+1) dwowds */
	tmp = mmCP_HQD_EOP_CONTWOW_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_EOP_CONTWOW, EOP_SIZE,
			(owdew_base_2(MES_EOP_SIZE / 4) - 1));

	mqd->cp_hqd_eop_base_addw_wo = wowew_32_bits(eop_base_addw);
	mqd->cp_hqd_eop_base_addw_hi = uppew_32_bits(eop_base_addw);
	mqd->cp_hqd_eop_contwow = tmp;

	/* disabwe the queue if it's active */
	wing->wptw = 0;
	mqd->cp_hqd_pq_wptw = 0;
	mqd->cp_hqd_pq_wptw_wo = 0;
	mqd->cp_hqd_pq_wptw_hi = 0;

	/* set the pointew to the MQD */
	mqd->cp_mqd_base_addw_wo = wing->mqd_gpu_addw & 0xfffffffc;
	mqd->cp_mqd_base_addw_hi = uppew_32_bits(wing->mqd_gpu_addw);

	/* set MQD vmid to 0 */
	tmp = mmCP_MQD_CONTWOW_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, CP_MQD_CONTWOW, VMID, 0);
	mqd->cp_mqd_contwow = tmp;

	/* set the pointew to the HQD, this is simiwaw CP_WB0_BASE/_HI */
	hqd_gpu_addw = wing->gpu_addw >> 8;
	mqd->cp_hqd_pq_base_wo = wowew_32_bits(hqd_gpu_addw);
	mqd->cp_hqd_pq_base_hi = uppew_32_bits(hqd_gpu_addw);

	/* set the wb addwess whethew it's enabwed ow not */
	wb_gpu_addw = wing->wptw_gpu_addw;
	mqd->cp_hqd_pq_wptw_wepowt_addw_wo = wb_gpu_addw & 0xfffffffc;
	mqd->cp_hqd_pq_wptw_wepowt_addw_hi =
		uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* onwy used if CP_PQ_WPTW_POWW_CNTW.CP_PQ_WPTW_POWW_CNTW__EN_MASK=1 */
	wb_gpu_addw = wing->wptw_gpu_addw;
	mqd->cp_hqd_pq_wptw_poww_addw_wo = wb_gpu_addw & 0xfffffff8;
	mqd->cp_hqd_pq_wptw_poww_addw_hi = uppew_32_bits(wb_gpu_addw) & 0xffff;

	/* set up the HQD, this is simiwaw to CP_WB0_CNTW */
	tmp = mmCP_HQD_PQ_CONTWOW_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, QUEUE_SIZE,
			    (owdew_base_2(wing->wing_size / 4) - 1));
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, WPTW_BWOCK_SIZE,
			    ((owdew_base_2(AMDGPU_GPU_PAGE_SIZE / 4) - 1) << 8));
#ifdef __BIG_ENDIAN
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, ENDIAN_SWAP, 1);
#endif
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, UNOWD_DISPATCH, 1);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, TUNNEW_DISPATCH, 0);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, PWIV_STATE, 1);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, KMD_QUEUE, 1);
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_CONTWOW, NO_UPDATE_WPTW, 1);
	mqd->cp_hqd_pq_contwow = tmp;

	/* enabwe doowbeww? */
	tmp = 0;
	if (wing->use_doowbeww) {
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_OFFSET, wing->doowbeww_index);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_EN, 1);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_SOUWCE, 0);
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_HIT, 0);
	}
	ewse
		tmp = WEG_SET_FIEWD(tmp, CP_HQD_PQ_DOOWBEWW_CONTWOW,
				    DOOWBEWW_EN, 0);
	mqd->cp_hqd_pq_doowbeww_contwow = tmp;

	mqd->cp_hqd_vmid = 0;
	/* activate the queue */
	mqd->cp_hqd_active = 1;
	mqd->cp_hqd_pewsistent_state = mmCP_HQD_PEWSISTENT_STATE_DEFAUWT;
	mqd->cp_hqd_ib_contwow = mmCP_HQD_IB_CONTWOW_DEFAUWT;
	mqd->cp_hqd_iq_timew = mmCP_HQD_IQ_TIMEW_DEFAUWT;
	mqd->cp_hqd_quantum = mmCP_HQD_QUANTUM_DEFAUWT;

	tmp = mmCP_HQD_GFX_CONTWOW_DEFAUWT;
	tmp = WEG_SET_FIEWD(tmp, CP_HQD_GFX_CONTWOW, DB_UPDATED_MSG_EN, 1);
	/* offset: 184 - this is used fow CP_HQD_GFX_CONTWOW */
	mqd->cp_hqd_suspend_cntw_stack_offset = tmp;

	amdgpu_device_fwush_hdp(wing->adev, NUWW);
	wetuwn 0;
}

#if 0
static void mes_v10_1_queue_init_wegistew(stwuct amdgpu_wing *wing)
{
	stwuct v10_compute_mqd *mqd = wing->mqd_ptw;
	stwuct amdgpu_device *adev = wing->adev;
	uint32_t data = 0;

	mutex_wock(&adev->swbm_mutex);
	nv_gwbm_sewect(adev, 3, wing->pipe, 0, 0);

	/* set CP_HQD_VMID.VMID = 0. */
	data = WWEG32_SOC15(GC, 0, mmCP_HQD_VMID);
	data = WEG_SET_FIEWD(data, CP_HQD_VMID, VMID, 0);
	WWEG32_SOC15(GC, 0, mmCP_HQD_VMID, data);

	/* set CP_HQD_PQ_DOOWBEWW_CONTWOW.DOOWBEWW_EN=0 */
	data = WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_DOOWBEWW_CONTWOW);
	data = WEG_SET_FIEWD(data, CP_HQD_PQ_DOOWBEWW_CONTWOW,
			     DOOWBEWW_EN, 0);
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_DOOWBEWW_CONTWOW, data);

	/* set CP_MQD_BASE_ADDW/HI with the MQD base addwess */
	WWEG32_SOC15(GC, 0, mmCP_MQD_BASE_ADDW, mqd->cp_mqd_base_addw_wo);
	WWEG32_SOC15(GC, 0, mmCP_MQD_BASE_ADDW_HI, mqd->cp_mqd_base_addw_hi);

	/* set CP_MQD_CONTWOW.VMID=0 */
	data = WWEG32_SOC15(GC, 0, mmCP_MQD_CONTWOW);
	data = WEG_SET_FIEWD(data, CP_MQD_CONTWOW, VMID, 0);
	WWEG32_SOC15(GC, 0, mmCP_MQD_CONTWOW, 0);

	/* set CP_HQD_PQ_BASE/HI with the wing buffew base addwess */
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_BASE, mqd->cp_hqd_pq_base_wo);
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_BASE_HI, mqd->cp_hqd_pq_base_hi);

	/* set CP_HQD_PQ_WPTW_WEPOWT_ADDW/HI */
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_WEPOWT_ADDW,
		     mqd->cp_hqd_pq_wptw_wepowt_addw_wo);
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_WEPOWT_ADDW_HI,
		     mqd->cp_hqd_pq_wptw_wepowt_addw_hi);

	/* set CP_HQD_PQ_CONTWOW */
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_CONTWOW, mqd->cp_hqd_pq_contwow);

	/* set CP_HQD_PQ_WPTW_POWW_ADDW/HI */
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_POWW_ADDW,
		     mqd->cp_hqd_pq_wptw_poww_addw_wo);
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_WPTW_POWW_ADDW_HI,
		     mqd->cp_hqd_pq_wptw_poww_addw_hi);

	/* set CP_HQD_PQ_DOOWBEWW_CONTWOW */
	WWEG32_SOC15(GC, 0, mmCP_HQD_PQ_DOOWBEWW_CONTWOW,
		     mqd->cp_hqd_pq_doowbeww_contwow);

	/* set CP_HQD_PEWSISTENT_STATE.PWEWOAD_SIZE=0x53 */
	WWEG32_SOC15(GC, 0, mmCP_HQD_PEWSISTENT_STATE, mqd->cp_hqd_pewsistent_state);

	/* set CP_HQD_ACTIVE.ACTIVE=1 */
	WWEG32_SOC15(GC, 0, mmCP_HQD_ACTIVE, mqd->cp_hqd_active);

	nv_gwbm_sewect(adev, 0, 0, 0, 0);
	mutex_unwock(&adev->swbm_mutex);
}
#endif

static int mes_v10_1_kiq_enabwe_queue(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_kiq *kiq = &adev->gfx.kiq[0];
	stwuct amdgpu_wing *kiq_wing = &adev->gfx.kiq[0].wing;
	int w;

	if (!kiq->pmf || !kiq->pmf->kiq_map_queues)
		wetuwn -EINVAW;

	w = amdgpu_wing_awwoc(kiq_wing, kiq->pmf->map_queues_size);
	if (w) {
		DWM_EWWOW("Faiwed to wock KIQ (%d).\n", w);
		wetuwn w;
	}

	kiq->pmf->kiq_map_queues(kiq_wing, &adev->mes.wing);

	wetuwn amdgpu_wing_test_hewpew(kiq_wing);
}

static int mes_v10_1_queue_init(stwuct amdgpu_device *adev)
{
	int w;

	w = mes_v10_1_mqd_init(&adev->mes.wing);
	if (w)
		wetuwn w;

	w = mes_v10_1_kiq_enabwe_queue(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int mes_v10_1_wing_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;

	wing = &adev->mes.wing;

	wing->funcs = &mes_v10_1_wing_funcs;

	wing->me = 3;
	wing->pipe = 0;
	wing->queue = 0;

	wing->wing_obj = NUWW;
	wing->use_doowbeww = twue;
	wing->doowbeww_index = adev->doowbeww_index.mes_wing0 << 1;
	wing->eop_gpu_addw = adev->mes.eop_gpu_addw[AMDGPU_MES_SCHED_PIPE];
	wing->no_scheduwew = twue;
	spwintf(wing->name, "mes_%d.%d.%d", wing->me, wing->pipe, wing->queue);

	wetuwn amdgpu_wing_init(adev, wing, 1024, NUWW, 0,
				AMDGPU_WING_PWIO_DEFAUWT, NUWW);
}

static int mes_v10_1_kiq_wing_init(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_wing *wing;

	spin_wock_init(&adev->gfx.kiq[0].wing_wock);

	wing = &adev->gfx.kiq[0].wing;

	wing->me = 3;
	wing->pipe = 1;
	wing->queue = 0;

	wing->adev = NUWW;
	wing->wing_obj = NUWW;
	wing->use_doowbeww = twue;
	wing->doowbeww_index = adev->doowbeww_index.mes_wing1 << 1;
	wing->eop_gpu_addw = adev->mes.eop_gpu_addw[AMDGPU_MES_KIQ_PIPE];
	wing->no_scheduwew = twue;
	spwintf(wing->name, "mes_kiq_%d.%d.%d",
		wing->me, wing->pipe, wing->queue);

	wetuwn amdgpu_wing_init(adev, wing, 1024, NUWW, 0,
				AMDGPU_WING_PWIO_DEFAUWT, NUWW);
}

static int mes_v10_1_mqd_sw_init(stwuct amdgpu_device *adev,
				 enum admgpu_mes_pipe pipe)
{
	int w, mqd_size = sizeof(stwuct v10_compute_mqd);
	stwuct amdgpu_wing *wing;

	if (pipe == AMDGPU_MES_KIQ_PIPE)
		wing = &adev->gfx.kiq[0].wing;
	ewse if (pipe == AMDGPU_MES_SCHED_PIPE)
		wing = &adev->mes.wing;
	ewse
		BUG();

	if (wing->mqd_obj)
		wetuwn 0;

	w = amdgpu_bo_cweate_kewnew(adev, mqd_size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_VWAM |
				    AMDGPU_GEM_DOMAIN_GTT, &wing->mqd_obj,
				    &wing->mqd_gpu_addw, &wing->mqd_ptw);
	if (w) {
		dev_wawn(adev->dev, "faiwed to cweate wing mqd bo (%d)", w);
		wetuwn w;
	}
	memset(wing->mqd_ptw, 0, mqd_size);

	/* pwepawe MQD backup */
	adev->mes.mqd_backup[pipe] = kmawwoc(mqd_size, GFP_KEWNEW);
	if (!adev->mes.mqd_backup[pipe]) {
		dev_wawn(adev->dev,
			 "no memowy to cweate MQD backup fow wing %s\n",
			 wing->name);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static int mes_v10_1_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int pipe, w;

	adev->mes.funcs = &mes_v10_1_funcs;
	adev->mes.kiq_hw_init = &mes_v10_1_kiq_hw_init;

	w = amdgpu_mes_init(adev);
	if (w)
		wetuwn w;

	fow (pipe = 0; pipe < AMDGPU_MAX_MES_PIPES; pipe++) {
		if (!adev->enabwe_mes_kiq && pipe == AMDGPU_MES_KIQ_PIPE)
			continue;

		w = mes_v10_1_awwocate_eop_buf(adev, pipe);
		if (w)
			wetuwn w;

		w = mes_v10_1_mqd_sw_init(adev, pipe);
		if (w)
			wetuwn w;
	}

	if (adev->enabwe_mes_kiq) {
		w = mes_v10_1_kiq_wing_init(adev);
		if (w)
			wetuwn w;
	}

	w = mes_v10_1_wing_init(adev);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int mes_v10_1_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int pipe;

	amdgpu_device_wb_fwee(adev, adev->mes.sch_ctx_offs);
	amdgpu_device_wb_fwee(adev, adev->mes.quewy_status_fence_offs);

	fow (pipe = 0; pipe < AMDGPU_MAX_MES_PIPES; pipe++) {
		kfwee(adev->mes.mqd_backup[pipe]);

		amdgpu_bo_fwee_kewnew(&adev->mes.eop_gpu_obj[pipe],
				      &adev->mes.eop_gpu_addw[pipe],
				      NUWW);
		amdgpu_ucode_wewease(&adev->mes.fw[pipe]);
	}

	amdgpu_bo_fwee_kewnew(&adev->gfx.kiq[0].wing.mqd_obj,
			      &adev->gfx.kiq[0].wing.mqd_gpu_addw,
			      &adev->gfx.kiq[0].wing.mqd_ptw);

	amdgpu_bo_fwee_kewnew(&adev->mes.wing.mqd_obj,
			      &adev->mes.wing.mqd_gpu_addw,
			      &adev->mes.wing.mqd_ptw);

	amdgpu_wing_fini(&adev->gfx.kiq[0].wing);
	amdgpu_wing_fini(&adev->mes.wing);

	amdgpu_mes_fini(adev);
	wetuwn 0;
}

static void mes_v10_1_kiq_setting(stwuct amdgpu_wing *wing)
{
	uint32_t tmp;
	stwuct amdgpu_device *adev = wing->adev;

	/* teww WWC which is KIQ queue */
	switch (amdgpu_ip_vewsion(adev, GC_HWIP, 0)) {
	case IP_VEWSION(10, 3, 0):
	case IP_VEWSION(10, 3, 2):
	case IP_VEWSION(10, 3, 1):
	case IP_VEWSION(10, 3, 4):
		tmp = WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS_Sienna_Cichwid);
		tmp &= 0xffffff00;
		tmp |= (wing->me << 5) | (wing->pipe << 3) | (wing->queue);
		WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS_Sienna_Cichwid, tmp);
		tmp |= 0x80;
		WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS_Sienna_Cichwid, tmp);
		bweak;
	defauwt:
		tmp = WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS);
		tmp &= 0xffffff00;
		tmp |= (wing->me << 5) | (wing->pipe << 3) | (wing->queue);
		WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS, tmp);
		tmp |= 0x80;
		WWEG32_SOC15(GC, 0, mmWWC_CP_SCHEDUWEWS, tmp);
		bweak;
	}
}

static int mes_v10_1_kiq_hw_init(stwuct amdgpu_device *adev)
{
	int w = 0;

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_DIWECT) {
		w = mes_v10_1_woad_micwocode(adev, AMDGPU_MES_KIQ_PIPE);
		if (w) {
			DWM_EWWOW("faiwed to woad MES kiq fw, w=%d\n", w);
			wetuwn w;
		}

		w = mes_v10_1_woad_micwocode(adev, AMDGPU_MES_SCHED_PIPE);
		if (w) {
			DWM_EWWOW("faiwed to woad MES fw, w=%d\n", w);
			wetuwn w;
		}
	}

	mes_v10_1_enabwe(adev, twue);

	mes_v10_1_kiq_setting(&adev->gfx.kiq[0].wing);

	w = mes_v10_1_queue_init(adev);
	if (w)
		goto faiwuwe;

	wetuwn w;

faiwuwe:
	mes_v10_1_hw_fini(adev);
	wetuwn w;
}

static int mes_v10_1_hw_init(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!adev->enabwe_mes_kiq) {
		if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_DIWECT) {
			w = mes_v10_1_woad_micwocode(adev,
					     AMDGPU_MES_SCHED_PIPE);
			if (w) {
				DWM_EWWOW("faiwed to MES fw, w=%d\n", w);
				wetuwn w;
			}
		}

		mes_v10_1_enabwe(adev, twue);
	}

	w = mes_v10_1_queue_init(adev);
	if (w)
		goto faiwuwe;

	w = mes_v10_1_set_hw_wesouwces(&adev->mes);
	if (w)
		goto faiwuwe;

	mes_v10_1_init_aggwegated_doowbeww(&adev->mes);

	w = mes_v10_1_quewy_sched_status(&adev->mes);
	if (w) {
		DWM_EWWOW("MES is busy\n");
		goto faiwuwe;
	}

	/*
	 * Disabwe KIQ wing usage fwom the dwivew once MES is enabwed.
	 * MES uses KIQ wing excwusivewy so dwivew cannot access KIQ wing
	 * with MES enabwed.
	 */
	adev->gfx.kiq[0].wing.sched.weady = fawse;
	adev->mes.wing.sched.weady = twue;

	wetuwn 0;

faiwuwe:
	mes_v10_1_hw_fini(adev);
	wetuwn w;
}

static int mes_v10_1_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	adev->mes.wing.sched.weady = fawse;

	mes_v10_1_enabwe(adev, fawse);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_DIWECT) {
		mes_v10_1_fwee_ucode_buffews(adev, AMDGPU_MES_KIQ_PIPE);
		mes_v10_1_fwee_ucode_buffews(adev, AMDGPU_MES_SCHED_PIPE);
	}

	wetuwn 0;
}

static int mes_v10_1_suspend(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = amdgpu_mes_suspend(adev);
	if (w)
		wetuwn w;

	wetuwn mes_v10_1_hw_fini(adev);
}

static int mes_v10_1_wesume(void *handwe)
{
	int w;
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	w = mes_v10_1_hw_init(adev);
	if (w)
		wetuwn w;

	wetuwn amdgpu_mes_wesume(adev);
}

static int mes_v10_0_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int pipe, w;

	fow (pipe = 0; pipe < AMDGPU_MAX_MES_PIPES; pipe++) {
		if (!adev->enabwe_mes_kiq && pipe == AMDGPU_MES_KIQ_PIPE)
			continue;
		w = amdgpu_mes_init_micwocode(adev, pipe);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int mes_v10_0_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	if (!amdgpu_in_weset(adev))
		amdgpu_mes_sewf_test(adev);

	wetuwn 0;
}

static const stwuct amd_ip_funcs mes_v10_1_ip_funcs = {
	.name = "mes_v10_1",
	.eawwy_init = mes_v10_0_eawwy_init,
	.wate_init = mes_v10_0_wate_init,
	.sw_init = mes_v10_1_sw_init,
	.sw_fini = mes_v10_1_sw_fini,
	.hw_init = mes_v10_1_hw_init,
	.hw_fini = mes_v10_1_hw_fini,
	.suspend = mes_v10_1_suspend,
	.wesume = mes_v10_1_wesume,
};

const stwuct amdgpu_ip_bwock_vewsion mes_v10_1_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_MES,
	.majow = 10,
	.minow = 1,
	.wev = 0,
	.funcs = &mes_v10_1_ip_funcs,
};
