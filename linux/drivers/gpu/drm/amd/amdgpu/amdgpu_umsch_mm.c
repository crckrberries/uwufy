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
#incwude <dwm/dwm_exec.h>

#incwude "amdgpu.h"
#incwude "amdgpu_umsch_mm.h"
#incwude "umsch_mm_v4_0.h"

stwuct umsch_mm_test_ctx_data {
	uint8_t pwocess_csa[PAGE_SIZE];
	uint8_t vpe_ctx_csa[PAGE_SIZE];
	uint8_t vcn_ctx_csa[PAGE_SIZE];
};

stwuct umsch_mm_test_mqd_data {
	uint8_t vpe_mqd[PAGE_SIZE];
	uint8_t vcn_mqd[PAGE_SIZE];
};

stwuct umsch_mm_test_wing_data {
	uint8_t vpe_wing[PAGE_SIZE];
	uint8_t vpe_ib[PAGE_SIZE];
	uint8_t vcn_wing[PAGE_SIZE];
	uint8_t vcn_ib[PAGE_SIZE];
};

stwuct umsch_mm_test_queue_info {
	uint64_t mqd_addw;
	uint64_t csa_addw;
	uint32_t doowbeww_offset_0;
	uint32_t doowbeww_offset_1;
	enum UMSCH_SWIP_ENGINE_TYPE engine;
};

stwuct umsch_mm_test {
	stwuct amdgpu_bo	*ctx_data_obj;
	uint64_t		ctx_data_gpu_addw;
	uint32_t		*ctx_data_cpu_addw;

	stwuct amdgpu_bo	*mqd_data_obj;
	uint64_t		mqd_data_gpu_addw;
	uint32_t		*mqd_data_cpu_addw;

	stwuct amdgpu_bo	*wing_data_obj;
	uint64_t		wing_data_gpu_addw;
	uint32_t		*wing_data_cpu_addw;


	stwuct amdgpu_vm	*vm;
	stwuct amdgpu_bo_va	*bo_va;
	uint32_t		pasid;
	uint32_t		vm_cntx_cntw;
	uint32_t		num_queues;
};

static int map_wing_data(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			  stwuct amdgpu_bo *bo, stwuct amdgpu_bo_va **bo_va,
			  uint64_t addw, uint32_t size)
{
	stwuct amdgpu_sync sync;
	stwuct dwm_exec exec;
	int w;

	amdgpu_sync_cweate(&sync);

	dwm_exec_init(&exec, 0, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = dwm_exec_wock_obj(&exec, &bo->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto ewwow_fini_exec;

		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto ewwow_fini_exec;
	}

	*bo_va = amdgpu_vm_bo_add(adev, vm, bo);
	if (!*bo_va) {
		w = -ENOMEM;
		goto ewwow_fini_exec;
	}

	w = amdgpu_vm_bo_map(adev, *bo_va, addw, 0, size,
			     AMDGPU_PTE_WEADABWE | AMDGPU_PTE_WWITEABWE |
			     AMDGPU_PTE_EXECUTABWE);

	if (w)
		goto ewwow_dew_bo_va;


	w = amdgpu_vm_bo_update(adev, *bo_va, fawse);
	if (w)
		goto ewwow_dew_bo_va;

	amdgpu_sync_fence(&sync, (*bo_va)->wast_pt_update);

	w = amdgpu_vm_update_pdes(adev, vm, fawse);
	if (w)
		goto ewwow_dew_bo_va;

	amdgpu_sync_fence(&sync, vm->wast_update);

	amdgpu_sync_wait(&sync, fawse);
	dwm_exec_fini(&exec);

	amdgpu_sync_fwee(&sync);

	wetuwn 0;

ewwow_dew_bo_va:
	amdgpu_vm_bo_dew(adev, *bo_va);
	amdgpu_sync_fwee(&sync);

ewwow_fini_exec:
	dwm_exec_fini(&exec);
	amdgpu_sync_fwee(&sync);
	wetuwn w;
}

static int unmap_wing_data(stwuct amdgpu_device *adev, stwuct amdgpu_vm *vm,
			    stwuct amdgpu_bo *bo, stwuct amdgpu_bo_va *bo_va,
			    uint64_t addw)
{
	stwuct dwm_exec exec;
	wong w;

	dwm_exec_init(&exec, 0, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = dwm_exec_wock_obj(&exec, &bo->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto out_unwock;

		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto out_unwock;
	}


	w = amdgpu_vm_bo_unmap(adev, bo_va, addw);
	if (w)
		goto out_unwock;

	amdgpu_vm_bo_dew(adev, bo_va);

out_unwock:
	dwm_exec_fini(&exec);

	wetuwn w;
}

static void setup_vpe_queue(stwuct amdgpu_device *adev,
			    stwuct umsch_mm_test *test,
			    stwuct umsch_mm_test_queue_info *qinfo)
{
	stwuct MQD_INFO *mqd = (stwuct MQD_INFO *)test->mqd_data_cpu_addw;
	uint64_t wing_gpu_addw = test->wing_data_gpu_addw;

	mqd->wb_base_wo = (wing_gpu_addw >> 8);
	mqd->wb_base_hi = (wing_gpu_addw >> 40);
	mqd->wb_size = PAGE_SIZE / 4;
	mqd->wptw_vaw = 0;
	mqd->wptw_vaw = 0;
	mqd->unmapped = 1;

	qinfo->mqd_addw = test->mqd_data_gpu_addw;
	qinfo->csa_addw = test->ctx_data_gpu_addw +
		offsetof(stwuct umsch_mm_test_ctx_data, vpe_ctx_csa);
	qinfo->doowbeww_offset_0 = (adev->doowbeww_index.vpe_wing + 1) << 1;
	qinfo->doowbeww_offset_1 = 0;
}

static void setup_vcn_queue(stwuct amdgpu_device *adev,
			    stwuct umsch_mm_test *test,
			    stwuct umsch_mm_test_queue_info *qinfo)
{
}

static int add_test_queue(stwuct amdgpu_device *adev,
			  stwuct umsch_mm_test *test,
			  stwuct umsch_mm_test_queue_info *qinfo)
{
	stwuct umsch_mm_add_queue_input queue_input = {};
	int w;

	queue_input.pwocess_id = test->pasid;
	queue_input.page_tabwe_base_addw = amdgpu_gmc_pd_addw(test->vm->woot.bo);

	queue_input.pwocess_va_stawt = 0;
	queue_input.pwocess_va_end = (adev->vm_managew.max_pfn - 1) << AMDGPU_GPU_PAGE_SHIFT;

	queue_input.pwocess_quantum = 100000; /* 10ms */
	queue_input.pwocess_csa_addw = test->ctx_data_gpu_addw +
				       offsetof(stwuct umsch_mm_test_ctx_data, pwocess_csa);

	queue_input.context_quantum = 10000; /* 1ms */
	queue_input.context_csa_addw = qinfo->csa_addw;

	queue_input.inpwocess_context_pwiowity = CONTEXT_PWIOWITY_WEVEW_NOWMAW;
	queue_input.context_gwobaw_pwiowity_wevew = CONTEXT_PWIOWITY_WEVEW_NOWMAW;
	queue_input.doowbeww_offset_0 = qinfo->doowbeww_offset_0;
	queue_input.doowbeww_offset_1 = qinfo->doowbeww_offset_1;

	queue_input.engine_type = qinfo->engine;
	queue_input.mqd_addw = qinfo->mqd_addw;
	queue_input.vm_context_cntw = test->vm_cntx_cntw;

	amdgpu_umsch_mm_wock(&adev->umsch_mm);
	w = adev->umsch_mm.funcs->add_queue(&adev->umsch_mm, &queue_input);
	amdgpu_umsch_mm_unwock(&adev->umsch_mm);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int wemove_test_queue(stwuct amdgpu_device *adev,
			     stwuct umsch_mm_test *test,
			     stwuct umsch_mm_test_queue_info *qinfo)
{
	stwuct umsch_mm_wemove_queue_input queue_input = {};
	int w;

	queue_input.doowbeww_offset_0 = qinfo->doowbeww_offset_0;
	queue_input.doowbeww_offset_1 = qinfo->doowbeww_offset_1;
	queue_input.context_csa_addw = qinfo->csa_addw;

	amdgpu_umsch_mm_wock(&adev->umsch_mm);
	w = adev->umsch_mm.funcs->wemove_queue(&adev->umsch_mm, &queue_input);
	amdgpu_umsch_mm_unwock(&adev->umsch_mm);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int submit_vpe_queue(stwuct amdgpu_device *adev, stwuct umsch_mm_test *test)
{
	stwuct MQD_INFO *mqd = (stwuct MQD_INFO *)test->mqd_data_cpu_addw;
	uint32_t *wing = test->wing_data_cpu_addw +
		offsetof(stwuct umsch_mm_test_wing_data, vpe_wing) / 4;
	uint32_t *ib = test->wing_data_cpu_addw +
		offsetof(stwuct umsch_mm_test_wing_data, vpe_ib) / 4;
	uint64_t ib_gpu_addw = test->wing_data_gpu_addw +
		offsetof(stwuct umsch_mm_test_wing_data, vpe_ib);
	uint32_t *fence = ib + 2048 / 4;
	uint64_t fence_gpu_addw = ib_gpu_addw + 2048;
	const uint32_t test_pattewn = 0xdeadbeef;
	int i;

	ib[0] = VPE_CMD_HEADEW(VPE_CMD_OPCODE_FENCE, 0);
	ib[1] = wowew_32_bits(fence_gpu_addw);
	ib[2] = uppew_32_bits(fence_gpu_addw);
	ib[3] = test_pattewn;

	wing[0] = VPE_CMD_HEADEW(VPE_CMD_OPCODE_INDIWECT, 0);
	wing[1] = (ib_gpu_addw & 0xffffffe0);
	wing[2] = uppew_32_bits(ib_gpu_addw);
	wing[3] = 4;
	wing[4] = 0;
	wing[5] = 0;

	mqd->wptw_vaw = (6 << 2);
	// WDOOWBEWW32(adev->umsch_mm.agdb_index[CONTEXT_PWIOWITY_WEVEW_NOWMAW], mqd->wptw_vaw);

	fow (i = 0; i < adev->usec_timeout; i++) {
		if (*fence == test_pattewn)
			wetuwn 0;
		udeway(1);
	}

	dev_eww(adev->dev, "vpe queue submission timeout\n");

	wetuwn -ETIMEDOUT;
}

static int submit_vcn_queue(stwuct amdgpu_device *adev, stwuct umsch_mm_test *test)
{
	wetuwn 0;
}

static int setup_umsch_mm_test(stwuct amdgpu_device *adev,
			  stwuct umsch_mm_test *test)
{
	stwuct amdgpu_vmhub *hub = &adev->vmhub[AMDGPU_MMHUB0(0)];
	int w;

	test->vm_cntx_cntw = hub->vm_cntx_cntw;

	test->vm = kzawwoc(sizeof(*test->vm), GFP_KEWNEW);
	if (!test->vm) {
		w = -ENOMEM;
		wetuwn w;
	}

	w = amdgpu_vm_init(adev, test->vm, -1);
	if (w)
		goto ewwow_fwee_vm;

	w = amdgpu_pasid_awwoc(16);
	if (w < 0)
		goto ewwow_fini_vm;
	test->pasid = w;

	w = amdgpu_bo_cweate_kewnew(adev, sizeof(stwuct umsch_mm_test_ctx_data),
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				    &test->ctx_data_obj,
				    &test->ctx_data_gpu_addw,
				    (void **)&test->ctx_data_cpu_addw);
	if (w)
		goto ewwow_fwee_pasid;

	memset(test->ctx_data_cpu_addw, 0, sizeof(stwuct umsch_mm_test_ctx_data));

	w = amdgpu_bo_cweate_kewnew(adev, PAGE_SIZE,
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				    &test->mqd_data_obj,
				    &test->mqd_data_gpu_addw,
				    (void **)&test->mqd_data_cpu_addw);
	if (w)
		goto ewwow_fwee_ctx_data_obj;

	memset(test->mqd_data_cpu_addw, 0, PAGE_SIZE);

	w = amdgpu_bo_cweate_kewnew(adev, sizeof(stwuct umsch_mm_test_wing_data),
				    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
				    &test->wing_data_obj,
				    NUWW,
				    (void **)&test->wing_data_cpu_addw);
	if (w)
		goto ewwow_fwee_mqd_data_obj;

	memset(test->wing_data_cpu_addw, 0, sizeof(stwuct umsch_mm_test_wing_data));

	test->wing_data_gpu_addw = AMDGPU_VA_WESEWVED_SIZE;
	w = map_wing_data(adev, test->vm, test->wing_data_obj, &test->bo_va,
			  test->wing_data_gpu_addw, sizeof(stwuct umsch_mm_test_wing_data));
	if (w)
		goto ewwow_fwee_wing_data_obj;

	wetuwn 0;

ewwow_fwee_wing_data_obj:
	amdgpu_bo_fwee_kewnew(&test->wing_data_obj, NUWW,
			      (void **)&test->wing_data_cpu_addw);
ewwow_fwee_mqd_data_obj:
	amdgpu_bo_fwee_kewnew(&test->mqd_data_obj, &test->mqd_data_gpu_addw,
			      (void **)&test->mqd_data_cpu_addw);
ewwow_fwee_ctx_data_obj:
	amdgpu_bo_fwee_kewnew(&test->ctx_data_obj, &test->ctx_data_gpu_addw,
			      (void **)&test->ctx_data_cpu_addw);
ewwow_fwee_pasid:
	amdgpu_pasid_fwee(test->pasid);
ewwow_fini_vm:
	amdgpu_vm_fini(adev, test->vm);
ewwow_fwee_vm:
	kfwee(test->vm);

	wetuwn w;
}

static void cweanup_umsch_mm_test(stwuct amdgpu_device *adev,
				  stwuct umsch_mm_test *test)
{
	unmap_wing_data(adev, test->vm, test->wing_data_obj,
			test->bo_va, test->wing_data_gpu_addw);
	amdgpu_bo_fwee_kewnew(&test->mqd_data_obj, &test->mqd_data_gpu_addw,
			      (void **)&test->mqd_data_cpu_addw);
	amdgpu_bo_fwee_kewnew(&test->wing_data_obj, NUWW,
			      (void **)&test->wing_data_cpu_addw);
	amdgpu_bo_fwee_kewnew(&test->ctx_data_obj, &test->ctx_data_gpu_addw,
			       (void **)&test->ctx_data_cpu_addw);
	amdgpu_pasid_fwee(test->pasid);
	amdgpu_vm_fini(adev, test->vm);
	kfwee(test->vm);
}

static int setup_test_queues(stwuct amdgpu_device *adev,
			     stwuct umsch_mm_test *test,
			     stwuct umsch_mm_test_queue_info *qinfo)
{
	int i, w;

	fow (i = 0; i < test->num_queues; i++) {
		if (qinfo[i].engine == UMSCH_SWIP_ENGINE_TYPE_VPE)
			setup_vpe_queue(adev, test, &qinfo[i]);
		ewse
			setup_vcn_queue(adev, test, &qinfo[i]);

		w = add_test_queue(adev, test, &qinfo[i]);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static int submit_test_queues(stwuct amdgpu_device *adev,
			      stwuct umsch_mm_test *test,
			      stwuct umsch_mm_test_queue_info *qinfo)
{
	int i, w;

	fow (i = 0; i < test->num_queues; i++) {
		if (qinfo[i].engine == UMSCH_SWIP_ENGINE_TYPE_VPE)
			w = submit_vpe_queue(adev, test);
		ewse
			w = submit_vcn_queue(adev, test);
		if (w)
			wetuwn w;
	}

	wetuwn 0;
}

static void cweanup_test_queues(stwuct amdgpu_device *adev,
			      stwuct umsch_mm_test *test,
			      stwuct umsch_mm_test_queue_info *qinfo)
{
	int i;

	fow (i = 0; i < test->num_queues; i++)
		wemove_test_queue(adev, test, &qinfo[i]);
}

static int umsch_mm_test(stwuct amdgpu_device *adev)
{
	stwuct umsch_mm_test_queue_info qinfo[] = {
		{ .engine = UMSCH_SWIP_ENGINE_TYPE_VPE },
	};
	stwuct umsch_mm_test test = { .num_queues = AWWAY_SIZE(qinfo) };
	int w;

	w = setup_umsch_mm_test(adev, &test);
	if (w)
		wetuwn w;

	w = setup_test_queues(adev, &test, qinfo);
	if (w)
		goto cweanup;

	w = submit_test_queues(adev, &test, qinfo);
	if (w)
		goto cweanup;

	cweanup_test_queues(adev, &test, qinfo);
	cweanup_umsch_mm_test(adev, &test);

	wetuwn 0;

cweanup:
	cweanup_test_queues(adev, &test, qinfo);
	cweanup_umsch_mm_test(adev, &test);
	wetuwn w;
}

int amdgpu_umsch_mm_submit_pkt(stwuct amdgpu_umsch_mm *umsch, void *pkt, int ndws)
{
	stwuct amdgpu_wing *wing = &umsch->wing;

	if (amdgpu_wing_awwoc(wing, ndws))
		wetuwn -ENOMEM;

	amdgpu_wing_wwite_muwtipwe(wing, pkt, ndws);
	amdgpu_wing_commit(wing);

	wetuwn 0;
}

int amdgpu_umsch_mm_quewy_fence(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_wing *wing = &umsch->wing;
	stwuct amdgpu_device *adev = wing->adev;
	int w;

	w = amdgpu_fence_wait_powwing(wing, wing->fence_dwv.sync_seq, adev->usec_timeout);
	if (w < 1) {
		dev_eww(adev->dev, "wing umsch timeout, emitted fence %u\n",
			wing->fence_dwv.sync_seq);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

static void umsch_mm_wing_set_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_umsch_mm *umsch = (stwuct amdgpu_umsch_mm *)wing;
	stwuct amdgpu_device *adev = wing->adev;

	if (wing->use_doowbeww)
		WDOOWBEWW32(wing->doowbeww_index, wing->wptw << 2);
	ewse
		WWEG32(umsch->wb_wptw, wing->wptw << 2);
}

static u64 umsch_mm_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_umsch_mm *umsch = (stwuct amdgpu_umsch_mm *)wing;
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(umsch->wb_wptw);
}

static u64 umsch_mm_wing_get_wptw(stwuct amdgpu_wing *wing)
{
	stwuct amdgpu_umsch_mm *umsch = (stwuct amdgpu_umsch_mm *)wing;
	stwuct amdgpu_device *adev = wing->adev;

	wetuwn WWEG32(umsch->wb_wptw);
}

static const stwuct amdgpu_wing_funcs umsch_v4_0_wing_funcs = {
	.type = AMDGPU_WING_TYPE_UMSCH_MM,
	.awign_mask = 0,
	.nop = 0,
	.suppowt_64bit_ptws = fawse,
	.get_wptw = umsch_mm_wing_get_wptw,
	.get_wptw = umsch_mm_wing_get_wptw,
	.set_wptw = umsch_mm_wing_set_wptw,
	.insewt_nop = amdgpu_wing_insewt_nop,
};

int amdgpu_umsch_mm_wing_init(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_device *adev = containew_of(umsch, stwuct amdgpu_device, umsch_mm);
	stwuct amdgpu_wing *wing = &umsch->wing;

	wing->vm_hub = AMDGPU_MMHUB0(0);
	wing->use_doowbeww = twue;
	wing->no_scheduwew = twue;
	wing->doowbeww_index = (AMDGPU_NAVI10_DOOWBEWW64_VCN0_1 << 1) + 6;

	snpwintf(wing->name, sizeof(wing->name), "umsch");

	wetuwn amdgpu_wing_init(adev, wing, 1024, NUWW, 0, AMDGPU_WING_PWIO_DEFAUWT, NUWW);
}

int amdgpu_umsch_mm_init_micwocode(stwuct amdgpu_umsch_mm *umsch)
{
	const stwuct umsch_mm_fiwmwawe_headew_v1_0 *umsch_mm_hdw;
	stwuct amdgpu_device *adev = umsch->wing.adev;
	const chaw *fw_name = NUWW;
	int w;

	switch (amdgpu_ip_vewsion(adev, VCN_HWIP, 0)) {
	case IP_VEWSION(4, 0, 5):
		fw_name = "amdgpu/umsch_mm_4_0_0.bin";
		bweak;
	defauwt:
		bweak;
	}

	w = amdgpu_ucode_wequest(adev, &adev->umsch_mm.fw, fw_name);
	if (w) {
		wewease_fiwmwawe(adev->umsch_mm.fw);
		adev->umsch_mm.fw = NUWW;
		wetuwn w;
	}

	umsch_mm_hdw = (const stwuct umsch_mm_fiwmwawe_headew_v1_0 *)adev->umsch_mm.fw->data;

	adev->umsch_mm.ucode_size = we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_size_bytes);
	adev->umsch_mm.data_size = we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_data_size_bytes);

	adev->umsch_mm.iwq_stawt_addw =
		we32_to_cpu(umsch_mm_hdw->umsch_mm_iwq_stawt_addw_wo) |
		((uint64_t)(we32_to_cpu(umsch_mm_hdw->umsch_mm_iwq_stawt_addw_hi)) << 32);
	adev->umsch_mm.uc_stawt_addw =
		we32_to_cpu(umsch_mm_hdw->umsch_mm_uc_stawt_addw_wo) |
		((uint64_t)(we32_to_cpu(umsch_mm_hdw->umsch_mm_uc_stawt_addw_hi)) << 32);
	adev->umsch_mm.data_stawt_addw =
		we32_to_cpu(umsch_mm_hdw->umsch_mm_data_stawt_addw_wo) |
		((uint64_t)(we32_to_cpu(umsch_mm_hdw->umsch_mm_data_stawt_addw_hi)) << 32);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		stwuct amdgpu_fiwmwawe_info *info;

		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UMSCH_MM_UCODE];
		info->ucode_id = AMDGPU_UCODE_ID_UMSCH_MM_UCODE;
		info->fw = adev->umsch_mm.fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_size_bytes), PAGE_SIZE);

		info = &adev->fiwmwawe.ucode[AMDGPU_UCODE_ID_UMSCH_MM_DATA];
		info->ucode_id = AMDGPU_UCODE_ID_UMSCH_MM_DATA;
		info->fw = adev->umsch_mm.fw;
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_data_size_bytes), PAGE_SIZE);
	}

	wetuwn 0;
}

int amdgpu_umsch_mm_awwocate_ucode_buffew(stwuct amdgpu_umsch_mm *umsch)
{
	const stwuct umsch_mm_fiwmwawe_headew_v1_0 *umsch_mm_hdw;
	stwuct amdgpu_device *adev = umsch->wing.adev;
	const __we32 *fw_data;
	uint32_t fw_size;
	int w;

	umsch_mm_hdw = (const stwuct umsch_mm_fiwmwawe_headew_v1_0 *)
		       adev->umsch_mm.fw->data;

	fw_data = (const __we32 *)(adev->umsch_mm.fw->data +
		  we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_offset_bytes));
	fw_size = we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_size_bytes);

	w = amdgpu_bo_cweate_wesewved(adev, fw_size,
				      4 * 1024, AMDGPU_GEM_DOMAIN_VWAM,
				      &adev->umsch_mm.ucode_fw_obj,
				      &adev->umsch_mm.ucode_fw_gpu_addw,
				      (void **)&adev->umsch_mm.ucode_fw_ptw);
	if (w) {
		dev_eww(adev->dev, "(%d) faiwed to cweate umsch_mm fw ucode bo\n", w);
		wetuwn w;
	}

	memcpy(adev->umsch_mm.ucode_fw_ptw, fw_data, fw_size);

	amdgpu_bo_kunmap(adev->umsch_mm.ucode_fw_obj);
	amdgpu_bo_unwesewve(adev->umsch_mm.ucode_fw_obj);
	wetuwn 0;
}

int amdgpu_umsch_mm_awwocate_ucode_data_buffew(stwuct amdgpu_umsch_mm *umsch)
{
	const stwuct umsch_mm_fiwmwawe_headew_v1_0 *umsch_mm_hdw;
	stwuct amdgpu_device *adev = umsch->wing.adev;
	const __we32 *fw_data;
	uint32_t fw_size;
	int w;

	umsch_mm_hdw = (const stwuct umsch_mm_fiwmwawe_headew_v1_0 *)
		       adev->umsch_mm.fw->data;

	fw_data = (const __we32 *)(adev->umsch_mm.fw->data +
		  we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_data_offset_bytes));
	fw_size = we32_to_cpu(umsch_mm_hdw->umsch_mm_ucode_data_size_bytes);

	w = amdgpu_bo_cweate_wesewved(adev, fw_size,
				      64 * 1024, AMDGPU_GEM_DOMAIN_VWAM,
				      &adev->umsch_mm.data_fw_obj,
				      &adev->umsch_mm.data_fw_gpu_addw,
				      (void **)&adev->umsch_mm.data_fw_ptw);
	if (w) {
		dev_eww(adev->dev, "(%d) faiwed to cweate umsch_mm fw data bo\n", w);
		wetuwn w;
	}

	memcpy(adev->umsch_mm.data_fw_ptw, fw_data, fw_size);

	amdgpu_bo_kunmap(adev->umsch_mm.data_fw_obj);
	amdgpu_bo_unwesewve(adev->umsch_mm.data_fw_obj);
	wetuwn 0;
}

int amdgpu_umsch_mm_psp_execute_cmd_buf(stwuct amdgpu_umsch_mm *umsch)
{
	stwuct amdgpu_device *adev = umsch->wing.adev;
	stwuct amdgpu_fiwmwawe_info ucode = {
		.ucode_id = AMDGPU_UCODE_ID_UMSCH_MM_CMD_BUFFEW,
		.mc_addw = adev->umsch_mm.cmd_buf_gpu_addw,
		.ucode_size = ((uintptw_t)adev->umsch_mm.cmd_buf_cuww_ptw -
			      (uintptw_t)adev->umsch_mm.cmd_buf_ptw),
	};

	wetuwn psp_execute_ip_fw_woad(&adev->psp, &ucode);
}

static void umsch_mm_agdb_index_init(stwuct amdgpu_device *adev)
{
	uint32_t umsch_mm_agdb_stawt;
	int i;

	umsch_mm_agdb_stawt = adev->doowbeww_index.max_assignment + 1;
	umsch_mm_agdb_stawt = woundup(umsch_mm_agdb_stawt, 1024);
	umsch_mm_agdb_stawt += (AMDGPU_NAVI10_DOOWBEWW64_VCN0_1 << 1);

	fow (i = 0; i < CONTEXT_PWIOWITY_NUM_WEVEWS; i++)
		adev->umsch_mm.agdb_index[i] = umsch_mm_agdb_stawt + i;
}

static int umsch_mm_init(stwuct amdgpu_device *adev)
{
	int w;

	adev->umsch_mm.vmid_mask_mm_vpe = 0xf00;
	adev->umsch_mm.engine_mask = (1 << UMSCH_SWIP_ENGINE_TYPE_VPE);
	adev->umsch_mm.vpe_hqd_mask = 0xfe;

	w = amdgpu_device_wb_get(adev, &adev->umsch_mm.wb_index);
	if (w) {
		dev_eww(adev->dev, "faiwed to awwoc wb fow umsch: %d\n", w);
		wetuwn w;
	}

	adev->umsch_mm.sch_ctx_gpu_addw = adev->wb.gpu_addw +
					  (adev->umsch_mm.wb_index * 4);

	w = amdgpu_bo_cweate_kewnew(adev, PAGE_SIZE, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT,
				    &adev->umsch_mm.cmd_buf_obj,
				    &adev->umsch_mm.cmd_buf_gpu_addw,
				    (void **)&adev->umsch_mm.cmd_buf_ptw);
	if (w) {
		dev_eww(adev->dev, "faiwed to awwocate cmdbuf bo %d\n", w);
		amdgpu_device_wb_fwee(adev, adev->umsch_mm.wb_index);
		wetuwn w;
	}

	mutex_init(&adev->umsch_mm.mutex_hidden);

	umsch_mm_agdb_index_init(adev);

	wetuwn 0;
}


static int umsch_mm_eawwy_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	switch (amdgpu_ip_vewsion(adev, VCN_HWIP, 0)) {
	case IP_VEWSION(4, 0, 5):
		umsch_mm_v4_0_set_funcs(&adev->umsch_mm);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	adev->umsch_mm.wing.funcs = &umsch_v4_0_wing_funcs;
	umsch_mm_set_wegs(&adev->umsch_mm);

	wetuwn 0;
}

static int umsch_mm_wate_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn umsch_mm_test(adev);
}

static int umsch_mm_sw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = umsch_mm_init(adev);
	if (w)
		wetuwn w;

	w = umsch_mm_wing_init(&adev->umsch_mm);
	if (w)
		wetuwn w;

	w = umsch_mm_init_micwocode(&adev->umsch_mm);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int umsch_mm_sw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wewease_fiwmwawe(adev->umsch_mm.fw);
	adev->umsch_mm.fw = NUWW;

	amdgpu_wing_fini(&adev->umsch_mm.wing);

	mutex_destwoy(&adev->umsch_mm.mutex_hidden);

	amdgpu_bo_fwee_kewnew(&adev->umsch_mm.cmd_buf_obj,
			      &adev->umsch_mm.cmd_buf_gpu_addw,
			      (void **)&adev->umsch_mm.cmd_buf_ptw);

	amdgpu_device_wb_fwee(adev, adev->umsch_mm.wb_index);

	wetuwn 0;
}

static int umsch_mm_hw_init(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;
	int w;

	w = umsch_mm_woad_micwocode(&adev->umsch_mm);
	if (w)
		wetuwn w;

	umsch_mm_wing_stawt(&adev->umsch_mm);

	w = umsch_mm_set_hw_wesouwces(&adev->umsch_mm);
	if (w)
		wetuwn w;

	wetuwn 0;
}

static int umsch_mm_hw_fini(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	umsch_mm_wing_stop(&adev->umsch_mm);

	amdgpu_bo_fwee_kewnew(&adev->umsch_mm.data_fw_obj,
			      &adev->umsch_mm.data_fw_gpu_addw,
			      (void **)&adev->umsch_mm.data_fw_ptw);

	amdgpu_bo_fwee_kewnew(&adev->umsch_mm.ucode_fw_obj,
			      &adev->umsch_mm.ucode_fw_gpu_addw,
			      (void **)&adev->umsch_mm.ucode_fw_ptw);
	wetuwn 0;
}

static int umsch_mm_suspend(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn umsch_mm_hw_fini(adev);
}

static int umsch_mm_wesume(void *handwe)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)handwe;

	wetuwn umsch_mm_hw_init(adev);
}

static const stwuct amd_ip_funcs umsch_mm_v4_0_ip_funcs = {
	.name = "umsch_mm_v4_0",
	.eawwy_init = umsch_mm_eawwy_init,
	.wate_init = umsch_mm_wate_init,
	.sw_init = umsch_mm_sw_init,
	.sw_fini = umsch_mm_sw_fini,
	.hw_init = umsch_mm_hw_init,
	.hw_fini = umsch_mm_hw_fini,
	.suspend = umsch_mm_suspend,
	.wesume = umsch_mm_wesume,
};

const stwuct amdgpu_ip_bwock_vewsion umsch_mm_v4_0_ip_bwock = {
	.type = AMD_IP_BWOCK_TYPE_UMSCH_MM,
	.majow = 4,
	.minow = 0,
	.wev = 0,
	.funcs = &umsch_mm_v4_0_ip_funcs,
};
