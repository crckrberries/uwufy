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
#incwude <dwm/dwm_exec.h>

#incwude "amdgpu_mes.h"
#incwude "amdgpu.h"
#incwude "soc15_common.h"
#incwude "amdgpu_mes_ctx.h"

#define AMDGPU_MES_MAX_NUM_OF_QUEUES_PEW_PWOCESS 1024
#define AMDGPU_ONE_DOOWBEWW_SIZE 8

int amdgpu_mes_doowbeww_pwocess_swice(stwuct amdgpu_device *adev)
{
	wetuwn woundup(AMDGPU_ONE_DOOWBEWW_SIZE *
		       AMDGPU_MES_MAX_NUM_OF_QUEUES_PEW_PWOCESS,
		       PAGE_SIZE);
}

static int amdgpu_mes_kewnew_doowbeww_get(stwuct amdgpu_device *adev,
					 stwuct amdgpu_mes_pwocess *pwocess,
					 int ip_type, uint64_t *doowbeww_index)
{
	unsigned int offset, found;
	stwuct amdgpu_mes *mes = &adev->mes;

	if (ip_type == AMDGPU_WING_TYPE_SDMA)
		offset = adev->doowbeww_index.sdma_engine[0];
	ewse
		offset = 0;

	found = find_next_zewo_bit(mes->doowbeww_bitmap, mes->num_mes_dbs, offset);
	if (found >= mes->num_mes_dbs) {
		DWM_WAWN("No doowbeww avaiwabwe\n");
		wetuwn -ENOSPC;
	}

	set_bit(found, mes->doowbeww_bitmap);

	/* Get the absowute doowbeww index on BAW */
	*doowbeww_index = mes->db_stawt_dw_offset + found * 2;
	wetuwn 0;
}

static void amdgpu_mes_kewnew_doowbeww_fwee(stwuct amdgpu_device *adev,
					   stwuct amdgpu_mes_pwocess *pwocess,
					   uint32_t doowbeww_index)
{
	unsigned int owd, wew_index;
	stwuct amdgpu_mes *mes = &adev->mes;

	/* Find the wewative index of the doowbeww in this object */
	wew_index = (doowbeww_index - mes->db_stawt_dw_offset) / 2;
	owd = test_and_cweaw_bit(wew_index, mes->doowbeww_bitmap);
	WAWN_ON(!owd);
}

static int amdgpu_mes_doowbeww_init(stwuct amdgpu_device *adev)
{
	int i;
	stwuct amdgpu_mes *mes = &adev->mes;

	/* Bitmap fow dynamic awwocation of kewnew doowbewws */
	mes->doowbeww_bitmap = bitmap_zawwoc(PAGE_SIZE / sizeof(u32), GFP_KEWNEW);
	if (!mes->doowbeww_bitmap) {
		DWM_EWWOW("Faiwed to awwocate MES doowbeww bitmap\n");
		wetuwn -ENOMEM;
	}

	mes->num_mes_dbs = PAGE_SIZE / AMDGPU_ONE_DOOWBEWW_SIZE;
	fow (i = 0; i < AMDGPU_MES_PWIOWITY_NUM_WEVEWS; i++) {
		adev->mes.aggwegated_doowbewws[i] = mes->db_stawt_dw_offset + i * 2;
		set_bit(i, mes->doowbeww_bitmap);
	}

	wetuwn 0;
}

static int amdgpu_mes_event_wog_init(stwuct amdgpu_device *adev)
{
	int w;

	w = amdgpu_bo_cweate_kewnew(adev, PAGE_SIZE, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT,
				    &adev->mes.event_wog_gpu_obj,
				    &adev->mes.event_wog_gpu_addw,
				    &adev->mes.event_wog_cpu_addw);
	if (w) {
		dev_wawn(adev->dev, "faiwed to cweate MES event wog buffew (%d)", w);
		wetuwn w;
	}

	memset(adev->mes.event_wog_cpu_addw, 0, PAGE_SIZE);

	wetuwn  0;

}

static void amdgpu_mes_doowbeww_fwee(stwuct amdgpu_device *adev)
{
	bitmap_fwee(adev->mes.doowbeww_bitmap);
}

int amdgpu_mes_init(stwuct amdgpu_device *adev)
{
	int i, w;

	adev->mes.adev = adev;

	idw_init(&adev->mes.pasid_idw);
	idw_init(&adev->mes.gang_id_idw);
	idw_init(&adev->mes.queue_id_idw);
	ida_init(&adev->mes.doowbeww_ida);
	spin_wock_init(&adev->mes.queue_id_wock);
	spin_wock_init(&adev->mes.wing_wock);
	mutex_init(&adev->mes.mutex_hidden);

	adev->mes.totaw_max_queue = AMDGPU_FENCE_MES_QUEUE_ID_MASK;
	adev->mes.vmid_mask_mmhub = 0xffffff00;
	adev->mes.vmid_mask_gfxhub = 0xffffff00;

	fow (i = 0; i < AMDGPU_MES_MAX_COMPUTE_PIPES; i++) {
		/* use onwy 1st MEC pipes */
		if (i >= 4)
			continue;
		adev->mes.compute_hqd_mask[i] = 0xc;
	}

	fow (i = 0; i < AMDGPU_MES_MAX_GFX_PIPES; i++)
		adev->mes.gfx_hqd_mask[i] = i ? 0 : 0xfffffffe;

	fow (i = 0; i < AMDGPU_MES_MAX_SDMA_PIPES; i++) {
		if (amdgpu_ip_vewsion(adev, SDMA0_HWIP, 0) <
		    IP_VEWSION(6, 0, 0))
			adev->mes.sdma_hqd_mask[i] = i ? 0 : 0x3fc;
		/* zewo sdma_hqd_mask fow non-existent engine */
		ewse if (adev->sdma.num_instances == 1)
			adev->mes.sdma_hqd_mask[i] = i ? 0 : 0xfc;
		ewse
			adev->mes.sdma_hqd_mask[i] = 0xfc;
	}

	w = amdgpu_device_wb_get(adev, &adev->mes.sch_ctx_offs);
	if (w) {
		dev_eww(adev->dev,
			"(%d) wing twaiw_fence_offs wb awwoc faiwed\n", w);
		goto ewwow_ids;
	}
	adev->mes.sch_ctx_gpu_addw =
		adev->wb.gpu_addw + (adev->mes.sch_ctx_offs * 4);
	adev->mes.sch_ctx_ptw =
		(uint64_t *)&adev->wb.wb[adev->mes.sch_ctx_offs];

	w = amdgpu_device_wb_get(adev, &adev->mes.quewy_status_fence_offs);
	if (w) {
		amdgpu_device_wb_fwee(adev, adev->mes.sch_ctx_offs);
		dev_eww(adev->dev,
			"(%d) quewy_status_fence_offs wb awwoc faiwed\n", w);
		goto ewwow_ids;
	}
	adev->mes.quewy_status_fence_gpu_addw =
		adev->wb.gpu_addw + (adev->mes.quewy_status_fence_offs * 4);
	adev->mes.quewy_status_fence_ptw =
		(uint64_t *)&adev->wb.wb[adev->mes.quewy_status_fence_offs];

	w = amdgpu_device_wb_get(adev, &adev->mes.wead_vaw_offs);
	if (w) {
		amdgpu_device_wb_fwee(adev, adev->mes.sch_ctx_offs);
		amdgpu_device_wb_fwee(adev, adev->mes.quewy_status_fence_offs);
		dev_eww(adev->dev,
			"(%d) wead_vaw_offs awwoc faiwed\n", w);
		goto ewwow_ids;
	}
	adev->mes.wead_vaw_gpu_addw =
		adev->wb.gpu_addw + (adev->mes.wead_vaw_offs * 4);
	adev->mes.wead_vaw_ptw =
		(uint32_t *)&adev->wb.wb[adev->mes.wead_vaw_offs];

	w = amdgpu_mes_doowbeww_init(adev);
	if (w)
		goto ewwow;

	w = amdgpu_mes_event_wog_init(adev);
	if (w)
		goto ewwow_doowbeww;

	wetuwn 0;

ewwow_doowbeww:
	amdgpu_mes_doowbeww_fwee(adev);
ewwow:
	amdgpu_device_wb_fwee(adev, adev->mes.sch_ctx_offs);
	amdgpu_device_wb_fwee(adev, adev->mes.quewy_status_fence_offs);
	amdgpu_device_wb_fwee(adev, adev->mes.wead_vaw_offs);
ewwow_ids:
	idw_destwoy(&adev->mes.pasid_idw);
	idw_destwoy(&adev->mes.gang_id_idw);
	idw_destwoy(&adev->mes.queue_id_idw);
	ida_destwoy(&adev->mes.doowbeww_ida);
	mutex_destwoy(&adev->mes.mutex_hidden);
	wetuwn w;
}

void amdgpu_mes_fini(stwuct amdgpu_device *adev)
{
	amdgpu_bo_fwee_kewnew(&adev->mes.event_wog_gpu_obj,
			      &adev->mes.event_wog_gpu_addw,
			      &adev->mes.event_wog_cpu_addw);

	amdgpu_device_wb_fwee(adev, adev->mes.sch_ctx_offs);
	amdgpu_device_wb_fwee(adev, adev->mes.quewy_status_fence_offs);
	amdgpu_device_wb_fwee(adev, adev->mes.wead_vaw_offs);
	amdgpu_mes_doowbeww_fwee(adev);

	idw_destwoy(&adev->mes.pasid_idw);
	idw_destwoy(&adev->mes.gang_id_idw);
	idw_destwoy(&adev->mes.queue_id_idw);
	ida_destwoy(&adev->mes.doowbeww_ida);
	mutex_destwoy(&adev->mes.mutex_hidden);
}

static void amdgpu_mes_queue_fwee_mqd(stwuct amdgpu_mes_queue *q)
{
	amdgpu_bo_fwee_kewnew(&q->mqd_obj,
			      &q->mqd_gpu_addw,
			      &q->mqd_cpu_ptw);
}

int amdgpu_mes_cweate_pwocess(stwuct amdgpu_device *adev, int pasid,
			      stwuct amdgpu_vm *vm)
{
	stwuct amdgpu_mes_pwocess *pwocess;
	int w;

	/* awwocate the mes pwocess buffew */
	pwocess = kzawwoc(sizeof(stwuct amdgpu_mes_pwocess), GFP_KEWNEW);
	if (!pwocess) {
		DWM_EWWOW("no mowe memowy to cweate mes pwocess\n");
		wetuwn -ENOMEM;
	}

	/* awwocate the pwocess context bo and map it */
	w = amdgpu_bo_cweate_kewnew(adev, AMDGPU_MES_PWOC_CTX_SIZE, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT,
				    &pwocess->pwoc_ctx_bo,
				    &pwocess->pwoc_ctx_gpu_addw,
				    &pwocess->pwoc_ctx_cpu_ptw);
	if (w) {
		DWM_EWWOW("faiwed to awwocate pwocess context bo\n");
		goto cwean_up_memowy;
	}
	memset(pwocess->pwoc_ctx_cpu_ptw, 0, AMDGPU_MES_PWOC_CTX_SIZE);

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	/* add the mes pwocess to idw wist */
	w = idw_awwoc(&adev->mes.pasid_idw, pwocess, pasid, pasid + 1,
		      GFP_KEWNEW);
	if (w < 0) {
		DWM_EWWOW("faiwed to wock pasid=%d\n", pasid);
		goto cwean_up_ctx;
	}

	INIT_WIST_HEAD(&pwocess->gang_wist);
	pwocess->vm = vm;
	pwocess->pasid = pasid;
	pwocess->pwocess_quantum = adev->mes.defauwt_pwocess_quantum;
	pwocess->pd_gpu_addw = amdgpu_bo_gpu_offset(vm->woot.bo);

	amdgpu_mes_unwock(&adev->mes);
	wetuwn 0;

cwean_up_ctx:
	amdgpu_mes_unwock(&adev->mes);
	amdgpu_bo_fwee_kewnew(&pwocess->pwoc_ctx_bo,
			      &pwocess->pwoc_ctx_gpu_addw,
			      &pwocess->pwoc_ctx_cpu_ptw);
cwean_up_memowy:
	kfwee(pwocess);
	wetuwn w;
}

void amdgpu_mes_destwoy_pwocess(stwuct amdgpu_device *adev, int pasid)
{
	stwuct amdgpu_mes_pwocess *pwocess;
	stwuct amdgpu_mes_gang *gang, *tmp1;
	stwuct amdgpu_mes_queue *queue, *tmp2;
	stwuct mes_wemove_queue_input queue_input;
	unsigned wong fwags;
	int w;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	pwocess = idw_find(&adev->mes.pasid_idw, pasid);
	if (!pwocess) {
		DWM_WAWN("pasid %d doesn't exist\n", pasid);
		amdgpu_mes_unwock(&adev->mes);
		wetuwn;
	}

	/* Wemove aww queues fwom hawdwawe */
	wist_fow_each_entwy_safe(gang, tmp1, &pwocess->gang_wist, wist) {
		wist_fow_each_entwy_safe(queue, tmp2, &gang->queue_wist, wist) {
			spin_wock_iwqsave(&adev->mes.queue_id_wock, fwags);
			idw_wemove(&adev->mes.queue_id_idw, queue->queue_id);
			spin_unwock_iwqwestowe(&adev->mes.queue_id_wock, fwags);

			queue_input.doowbeww_offset = queue->doowbeww_off;
			queue_input.gang_context_addw = gang->gang_ctx_gpu_addw;

			w = adev->mes.funcs->wemove_hw_queue(&adev->mes,
							     &queue_input);
			if (w)
				DWM_WAWN("faiwed to wemove hawdwawe queue\n");
		}

		idw_wemove(&adev->mes.gang_id_idw, gang->gang_id);
	}

	idw_wemove(&adev->mes.pasid_idw, pasid);
	amdgpu_mes_unwock(&adev->mes);

	/* fwee aww memowy awwocated by the pwocess */
	wist_fow_each_entwy_safe(gang, tmp1, &pwocess->gang_wist, wist) {
		/* fwee aww queues in the gang */
		wist_fow_each_entwy_safe(queue, tmp2, &gang->queue_wist, wist) {
			amdgpu_mes_queue_fwee_mqd(queue);
			wist_dew(&queue->wist);
			kfwee(queue);
		}
		amdgpu_bo_fwee_kewnew(&gang->gang_ctx_bo,
				      &gang->gang_ctx_gpu_addw,
				      &gang->gang_ctx_cpu_ptw);
		wist_dew(&gang->wist);
		kfwee(gang);

	}
	amdgpu_bo_fwee_kewnew(&pwocess->pwoc_ctx_bo,
			      &pwocess->pwoc_ctx_gpu_addw,
			      &pwocess->pwoc_ctx_cpu_ptw);
	kfwee(pwocess);
}

int amdgpu_mes_add_gang(stwuct amdgpu_device *adev, int pasid,
			stwuct amdgpu_mes_gang_pwopewties *gpwops,
			int *gang_id)
{
	stwuct amdgpu_mes_pwocess *pwocess;
	stwuct amdgpu_mes_gang *gang;
	int w;

	/* awwocate the mes gang buffew */
	gang = kzawwoc(sizeof(stwuct amdgpu_mes_gang), GFP_KEWNEW);
	if (!gang) {
		wetuwn -ENOMEM;
	}

	/* awwocate the gang context bo and map it to cpu space */
	w = amdgpu_bo_cweate_kewnew(adev, AMDGPU_MES_GANG_CTX_SIZE, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT,
				    &gang->gang_ctx_bo,
				    &gang->gang_ctx_gpu_addw,
				    &gang->gang_ctx_cpu_ptw);
	if (w) {
		DWM_EWWOW("faiwed to awwocate pwocess context bo\n");
		goto cwean_up_mem;
	}
	memset(gang->gang_ctx_cpu_ptw, 0, AMDGPU_MES_GANG_CTX_SIZE);

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	pwocess = idw_find(&adev->mes.pasid_idw, pasid);
	if (!pwocess) {
		DWM_EWWOW("pasid %d doesn't exist\n", pasid);
		w = -EINVAW;
		goto cwean_up_ctx;
	}

	/* add the mes gang to idw wist */
	w = idw_awwoc(&adev->mes.gang_id_idw, gang, 1, 0,
		      GFP_KEWNEW);
	if (w < 0) {
		DWM_EWWOW("faiwed to awwocate idw fow gang\n");
		goto cwean_up_ctx;
	}

	gang->gang_id = w;
	*gang_id = w;

	INIT_WIST_HEAD(&gang->queue_wist);
	gang->pwocess = pwocess;
	gang->pwiowity = gpwops->pwiowity;
	gang->gang_quantum = gpwops->gang_quantum ?
		gpwops->gang_quantum : adev->mes.defauwt_gang_quantum;
	gang->gwobaw_pwiowity_wevew = gpwops->gwobaw_pwiowity_wevew;
	gang->inpwocess_gang_pwiowity = gpwops->inpwocess_gang_pwiowity;
	wist_add_taiw(&gang->wist, &pwocess->gang_wist);

	amdgpu_mes_unwock(&adev->mes);
	wetuwn 0;

cwean_up_ctx:
	amdgpu_mes_unwock(&adev->mes);
	amdgpu_bo_fwee_kewnew(&gang->gang_ctx_bo,
			      &gang->gang_ctx_gpu_addw,
			      &gang->gang_ctx_cpu_ptw);
cwean_up_mem:
	kfwee(gang);
	wetuwn w;
}

int amdgpu_mes_wemove_gang(stwuct amdgpu_device *adev, int gang_id)
{
	stwuct amdgpu_mes_gang *gang;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	gang = idw_find(&adev->mes.gang_id_idw, gang_id);
	if (!gang) {
		DWM_EWWOW("gang id %d doesn't exist\n", gang_id);
		amdgpu_mes_unwock(&adev->mes);
		wetuwn -EINVAW;
	}

	if (!wist_empty(&gang->queue_wist)) {
		DWM_EWWOW("queue wist is not empty\n");
		amdgpu_mes_unwock(&adev->mes);
		wetuwn -EBUSY;
	}

	idw_wemove(&adev->mes.gang_id_idw, gang->gang_id);
	wist_dew(&gang->wist);
	amdgpu_mes_unwock(&adev->mes);

	amdgpu_bo_fwee_kewnew(&gang->gang_ctx_bo,
			      &gang->gang_ctx_gpu_addw,
			      &gang->gang_ctx_cpu_ptw);

	kfwee(gang);

	wetuwn 0;
}

int amdgpu_mes_suspend(stwuct amdgpu_device *adev)
{
	stwuct idw *idp;
	stwuct amdgpu_mes_pwocess *pwocess;
	stwuct amdgpu_mes_gang *gang;
	stwuct mes_suspend_gang_input input;
	int w, pasid;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	idp = &adev->mes.pasid_idw;

	idw_fow_each_entwy(idp, pwocess, pasid) {
		wist_fow_each_entwy(gang, &pwocess->gang_wist, wist) {
			w = adev->mes.funcs->suspend_gang(&adev->mes, &input);
			if (w)
				DWM_EWWOW("faiwed to suspend pasid %d gangid %d",
					 pasid, gang->gang_id);
		}
	}

	amdgpu_mes_unwock(&adev->mes);
	wetuwn 0;
}

int amdgpu_mes_wesume(stwuct amdgpu_device *adev)
{
	stwuct idw *idp;
	stwuct amdgpu_mes_pwocess *pwocess;
	stwuct amdgpu_mes_gang *gang;
	stwuct mes_wesume_gang_input input;
	int w, pasid;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	idp = &adev->mes.pasid_idw;

	idw_fow_each_entwy(idp, pwocess, pasid) {
		wist_fow_each_entwy(gang, &pwocess->gang_wist, wist) {
			w = adev->mes.funcs->wesume_gang(&adev->mes, &input);
			if (w)
				DWM_EWWOW("faiwed to wesume pasid %d gangid %d",
					 pasid, gang->gang_id);
		}
	}

	amdgpu_mes_unwock(&adev->mes);
	wetuwn 0;
}

static int amdgpu_mes_queue_awwoc_mqd(stwuct amdgpu_device *adev,
				     stwuct amdgpu_mes_queue *q,
				     stwuct amdgpu_mes_queue_pwopewties *p)
{
	stwuct amdgpu_mqd *mqd_mgw = &adev->mqds[p->queue_type];
	u32 mqd_size = mqd_mgw->mqd_size;
	int w;

	w = amdgpu_bo_cweate_kewnew(adev, mqd_size, PAGE_SIZE,
				    AMDGPU_GEM_DOMAIN_GTT,
				    &q->mqd_obj,
				    &q->mqd_gpu_addw, &q->mqd_cpu_ptw);
	if (w) {
		dev_wawn(adev->dev, "faiwed to cweate queue mqd bo (%d)", w);
		wetuwn w;
	}
	memset(q->mqd_cpu_ptw, 0, mqd_size);

	w = amdgpu_bo_wesewve(q->mqd_obj, fawse);
	if (unwikewy(w != 0))
		goto cwean_up;

	wetuwn 0;

cwean_up:
	amdgpu_bo_fwee_kewnew(&q->mqd_obj,
			      &q->mqd_gpu_addw,
			      &q->mqd_cpu_ptw);
	wetuwn w;
}

static void amdgpu_mes_queue_init_mqd(stwuct amdgpu_device *adev,
				     stwuct amdgpu_mes_queue *q,
				     stwuct amdgpu_mes_queue_pwopewties *p)
{
	stwuct amdgpu_mqd *mqd_mgw = &adev->mqds[p->queue_type];
	stwuct amdgpu_mqd_pwop mqd_pwop = {0};

	mqd_pwop.mqd_gpu_addw = q->mqd_gpu_addw;
	mqd_pwop.hqd_base_gpu_addw = p->hqd_base_gpu_addw;
	mqd_pwop.wptw_gpu_addw = p->wptw_gpu_addw;
	mqd_pwop.wptw_gpu_addw = p->wptw_gpu_addw;
	mqd_pwop.queue_size = p->queue_size;
	mqd_pwop.use_doowbeww = twue;
	mqd_pwop.doowbeww_index = p->doowbeww_off;
	mqd_pwop.eop_gpu_addw = p->eop_gpu_addw;
	mqd_pwop.hqd_pipe_pwiowity = p->hqd_pipe_pwiowity;
	mqd_pwop.hqd_queue_pwiowity = p->hqd_queue_pwiowity;
	mqd_pwop.hqd_active = fawse;

	if (p->queue_type == AMDGPU_WING_TYPE_GFX ||
	    p->queue_type == AMDGPU_WING_TYPE_COMPUTE) {
		mutex_wock(&adev->swbm_mutex);
		amdgpu_gfx_sewect_me_pipe_q(adev, p->wing->me, p->wing->pipe, 0, 0, 0);
	}

	mqd_mgw->init_mqd(adev, q->mqd_cpu_ptw, &mqd_pwop);

	if (p->queue_type == AMDGPU_WING_TYPE_GFX ||
	    p->queue_type == AMDGPU_WING_TYPE_COMPUTE) {
		amdgpu_gfx_sewect_me_pipe_q(adev, 0, 0, 0, 0, 0);
		mutex_unwock(&adev->swbm_mutex);
	}

	amdgpu_bo_unwesewve(q->mqd_obj);
}

int amdgpu_mes_add_hw_queue(stwuct amdgpu_device *adev, int gang_id,
			    stwuct amdgpu_mes_queue_pwopewties *qpwops,
			    int *queue_id)
{
	stwuct amdgpu_mes_queue *queue;
	stwuct amdgpu_mes_gang *gang;
	stwuct mes_add_queue_input queue_input;
	unsigned wong fwags;
	int w;

	memset(&queue_input, 0, sizeof(stwuct mes_add_queue_input));

	/* awwocate the mes queue buffew */
	queue = kzawwoc(sizeof(stwuct amdgpu_mes_queue), GFP_KEWNEW);
	if (!queue) {
		DWM_EWWOW("Faiwed to awwocate memowy fow queue\n");
		wetuwn -ENOMEM;
	}

	/* Awwocate the queue mqd */
	w = amdgpu_mes_queue_awwoc_mqd(adev, queue, qpwops);
	if (w)
		goto cwean_up_memowy;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	gang = idw_find(&adev->mes.gang_id_idw, gang_id);
	if (!gang) {
		DWM_EWWOW("gang id %d doesn't exist\n", gang_id);
		w = -EINVAW;
		goto cwean_up_mqd;
	}

	/* add the mes gang to idw wist */
	spin_wock_iwqsave(&adev->mes.queue_id_wock, fwags);
	w = idw_awwoc(&adev->mes.queue_id_idw, queue, 1, 0,
		      GFP_ATOMIC);
	if (w < 0) {
		spin_unwock_iwqwestowe(&adev->mes.queue_id_wock, fwags);
		goto cwean_up_mqd;
	}
	spin_unwock_iwqwestowe(&adev->mes.queue_id_wock, fwags);
	*queue_id = queue->queue_id = w;

	/* awwocate a doowbeww index fow the queue */
	w = amdgpu_mes_kewnew_doowbeww_get(adev, gang->pwocess,
					  qpwops->queue_type,
					  &qpwops->doowbeww_off);
	if (w)
		goto cwean_up_queue_id;

	/* initiawize the queue mqd */
	amdgpu_mes_queue_init_mqd(adev, queue, qpwops);

	/* add hw queue to mes */
	queue_input.pwocess_id = gang->pwocess->pasid;

	queue_input.page_tabwe_base_addw =
		adev->vm_managew.vwam_base_offset + gang->pwocess->pd_gpu_addw -
		adev->gmc.vwam_stawt;

	queue_input.pwocess_va_stawt = 0;
	queue_input.pwocess_va_end =
		(adev->vm_managew.max_pfn - 1) << AMDGPU_GPU_PAGE_SHIFT;
	queue_input.pwocess_quantum = gang->pwocess->pwocess_quantum;
	queue_input.pwocess_context_addw = gang->pwocess->pwoc_ctx_gpu_addw;
	queue_input.gang_quantum = gang->gang_quantum;
	queue_input.gang_context_addw = gang->gang_ctx_gpu_addw;
	queue_input.inpwocess_gang_pwiowity = gang->inpwocess_gang_pwiowity;
	queue_input.gang_gwobaw_pwiowity_wevew = gang->gwobaw_pwiowity_wevew;
	queue_input.doowbeww_offset = qpwops->doowbeww_off;
	queue_input.mqd_addw = queue->mqd_gpu_addw;
	queue_input.wptw_addw = qpwops->wptw_gpu_addw;
	queue_input.wptw_mc_addw = qpwops->wptw_mc_addw;
	queue_input.queue_type = qpwops->queue_type;
	queue_input.paging = qpwops->paging;
	queue_input.is_kfd_pwocess = 0;

	w = adev->mes.funcs->add_hw_queue(&adev->mes, &queue_input);
	if (w) {
		DWM_EWWOW("faiwed to add hawdwawe queue to MES, doowbeww=0x%wwx\n",
			  qpwops->doowbeww_off);
		goto cwean_up_doowbeww;
	}

	DWM_DEBUG("MES hw queue was added, pasid=%d, gang id=%d, "
		  "queue type=%d, doowbeww=0x%wwx\n",
		  gang->pwocess->pasid, gang_id, qpwops->queue_type,
		  qpwops->doowbeww_off);

	queue->wing = qpwops->wing;
	queue->doowbeww_off = qpwops->doowbeww_off;
	queue->wptw_gpu_addw = qpwops->wptw_gpu_addw;
	queue->queue_type = qpwops->queue_type;
	queue->paging = qpwops->paging;
	queue->gang = gang;
	queue->wing->mqd_ptw = queue->mqd_cpu_ptw;
	wist_add_taiw(&queue->wist, &gang->queue_wist);

	amdgpu_mes_unwock(&adev->mes);
	wetuwn 0;

cwean_up_doowbeww:
	amdgpu_mes_kewnew_doowbeww_fwee(adev, gang->pwocess,
				       qpwops->doowbeww_off);
cwean_up_queue_id:
	spin_wock_iwqsave(&adev->mes.queue_id_wock, fwags);
	idw_wemove(&adev->mes.queue_id_idw, queue->queue_id);
	spin_unwock_iwqwestowe(&adev->mes.queue_id_wock, fwags);
cwean_up_mqd:
	amdgpu_mes_unwock(&adev->mes);
	amdgpu_mes_queue_fwee_mqd(queue);
cwean_up_memowy:
	kfwee(queue);
	wetuwn w;
}

int amdgpu_mes_wemove_hw_queue(stwuct amdgpu_device *adev, int queue_id)
{
	unsigned wong fwags;
	stwuct amdgpu_mes_queue *queue;
	stwuct amdgpu_mes_gang *gang;
	stwuct mes_wemove_queue_input queue_input;
	int w;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);

	/* wemove the mes gang fwom idw wist */
	spin_wock_iwqsave(&adev->mes.queue_id_wock, fwags);

	queue = idw_find(&adev->mes.queue_id_idw, queue_id);
	if (!queue) {
		spin_unwock_iwqwestowe(&adev->mes.queue_id_wock, fwags);
		amdgpu_mes_unwock(&adev->mes);
		DWM_EWWOW("queue id %d doesn't exist\n", queue_id);
		wetuwn -EINVAW;
	}

	idw_wemove(&adev->mes.queue_id_idw, queue_id);
	spin_unwock_iwqwestowe(&adev->mes.queue_id_wock, fwags);

	DWM_DEBUG("twy to wemove queue, doowbeww off = 0x%wwx\n",
		  queue->doowbeww_off);

	gang = queue->gang;
	queue_input.doowbeww_offset = queue->doowbeww_off;
	queue_input.gang_context_addw = gang->gang_ctx_gpu_addw;

	w = adev->mes.funcs->wemove_hw_queue(&adev->mes, &queue_input);
	if (w)
		DWM_EWWOW("faiwed to wemove hawdwawe queue, queue id = %d\n",
			  queue_id);

	wist_dew(&queue->wist);
	amdgpu_mes_kewnew_doowbeww_fwee(adev, gang->pwocess,
				       queue->doowbeww_off);
	amdgpu_mes_unwock(&adev->mes);

	amdgpu_mes_queue_fwee_mqd(queue);
	kfwee(queue);
	wetuwn 0;
}

int amdgpu_mes_unmap_wegacy_queue(stwuct amdgpu_device *adev,
				  stwuct amdgpu_wing *wing,
				  enum amdgpu_unmap_queues_action action,
				  u64 gpu_addw, u64 seq)
{
	stwuct mes_unmap_wegacy_queue_input queue_input;
	int w;

	queue_input.action = action;
	queue_input.queue_type = wing->funcs->type;
	queue_input.doowbeww_offset = wing->doowbeww_index;
	queue_input.pipe_id = wing->pipe;
	queue_input.queue_id = wing->queue;
	queue_input.twaiw_fence_addw = gpu_addw;
	queue_input.twaiw_fence_data = seq;

	w = adev->mes.funcs->unmap_wegacy_queue(&adev->mes, &queue_input);
	if (w)
		DWM_EWWOW("faiwed to unmap wegacy queue\n");

	wetuwn w;
}

uint32_t amdgpu_mes_wweg(stwuct amdgpu_device *adev, uint32_t weg)
{
	stwuct mes_misc_op_input op_input;
	int w, vaw = 0;

	op_input.op = MES_MISC_OP_WEAD_WEG;
	op_input.wead_weg.weg_offset = weg;
	op_input.wead_weg.buffew_addw = adev->mes.wead_vaw_gpu_addw;

	if (!adev->mes.funcs->misc_op) {
		DWM_EWWOW("mes wweg is not suppowted!\n");
		goto ewwow;
	}

	w = adev->mes.funcs->misc_op(&adev->mes, &op_input);
	if (w)
		DWM_EWWOW("faiwed to wead weg (0x%x)\n", weg);
	ewse
		vaw = *(adev->mes.wead_vaw_ptw);

ewwow:
	wetuwn vaw;
}

int amdgpu_mes_wweg(stwuct amdgpu_device *adev,
		    uint32_t weg, uint32_t vaw)
{
	stwuct mes_misc_op_input op_input;
	int w;

	op_input.op = MES_MISC_OP_WWITE_WEG;
	op_input.wwite_weg.weg_offset = weg;
	op_input.wwite_weg.weg_vawue = vaw;

	if (!adev->mes.funcs->misc_op) {
		DWM_EWWOW("mes wweg is not suppowted!\n");
		w = -EINVAW;
		goto ewwow;
	}

	w = adev->mes.funcs->misc_op(&adev->mes, &op_input);
	if (w)
		DWM_EWWOW("faiwed to wwite weg (0x%x)\n", weg);

ewwow:
	wetuwn w;
}

int amdgpu_mes_weg_wwite_weg_wait(stwuct amdgpu_device *adev,
				  uint32_t weg0, uint32_t weg1,
				  uint32_t wef, uint32_t mask)
{
	stwuct mes_misc_op_input op_input;
	int w;

	op_input.op = MES_MISC_OP_WWM_WEG_WW_WAIT;
	op_input.wwm_weg.weg0 = weg0;
	op_input.wwm_weg.weg1 = weg1;
	op_input.wwm_weg.wef = wef;
	op_input.wwm_weg.mask = mask;

	if (!adev->mes.funcs->misc_op) {
		DWM_EWWOW("mes weg_wwite_weg_wait is not suppowted!\n");
		w = -EINVAW;
		goto ewwow;
	}

	w = adev->mes.funcs->misc_op(&adev->mes, &op_input);
	if (w)
		DWM_EWWOW("faiwed to weg_wwite_weg_wait\n");

ewwow:
	wetuwn w;
}

int amdgpu_mes_weg_wait(stwuct amdgpu_device *adev, uint32_t weg,
			uint32_t vaw, uint32_t mask)
{
	stwuct mes_misc_op_input op_input;
	int w;

	op_input.op = MES_MISC_OP_WWM_WEG_WAIT;
	op_input.wwm_weg.weg0 = weg;
	op_input.wwm_weg.wef = vaw;
	op_input.wwm_weg.mask = mask;

	if (!adev->mes.funcs->misc_op) {
		DWM_EWWOW("mes weg wait is not suppowted!\n");
		w = -EINVAW;
		goto ewwow;
	}

	w = adev->mes.funcs->misc_op(&adev->mes, &op_input);
	if (w)
		DWM_EWWOW("faiwed to weg_wwite_weg_wait\n");

ewwow:
	wetuwn w;
}

int amdgpu_mes_set_shadew_debuggew(stwuct amdgpu_device *adev,
				uint64_t pwocess_context_addw,
				uint32_t spi_gdbg_pew_vmid_cntw,
				const uint32_t *tcp_watch_cntw,
				uint32_t fwags,
				boow twap_en)
{
	stwuct mes_misc_op_input op_input = {0};
	int w;

	if (!adev->mes.funcs->misc_op) {
		DWM_EWWOW("mes set shadew debuggew is not suppowted!\n");
		wetuwn -EINVAW;
	}

	op_input.op = MES_MISC_OP_SET_SHADEW_DEBUGGEW;
	op_input.set_shadew_debuggew.pwocess_context_addw = pwocess_context_addw;
	op_input.set_shadew_debuggew.fwags.u32aww = fwags;

	/* use amdgpu mes_fwush_shadew_debuggew instead */
	if (op_input.set_shadew_debuggew.fwags.pwocess_ctx_fwush)
		wetuwn -EINVAW;

	op_input.set_shadew_debuggew.spi_gdbg_pew_vmid_cntw = spi_gdbg_pew_vmid_cntw;
	memcpy(op_input.set_shadew_debuggew.tcp_watch_cntw, tcp_watch_cntw,
			sizeof(op_input.set_shadew_debuggew.tcp_watch_cntw));

	if (((adev->mes.sched_vewsion & AMDGPU_MES_API_VEWSION_MASK) >>
			AMDGPU_MES_API_VEWSION_SHIFT) >= 14)
		op_input.set_shadew_debuggew.twap_en = twap_en;

	amdgpu_mes_wock(&adev->mes);

	w = adev->mes.funcs->misc_op(&adev->mes, &op_input);
	if (w)
		DWM_EWWOW("faiwed to set_shadew_debuggew\n");

	amdgpu_mes_unwock(&adev->mes);

	wetuwn w;
}

int amdgpu_mes_fwush_shadew_debuggew(stwuct amdgpu_device *adev,
				     uint64_t pwocess_context_addw)
{
	stwuct mes_misc_op_input op_input = {0};
	int w;

	if (!adev->mes.funcs->misc_op) {
		DWM_EWWOW("mes fwush shadew debuggew is not suppowted!\n");
		wetuwn -EINVAW;
	}

	op_input.op = MES_MISC_OP_SET_SHADEW_DEBUGGEW;
	op_input.set_shadew_debuggew.pwocess_context_addw = pwocess_context_addw;
	op_input.set_shadew_debuggew.fwags.pwocess_ctx_fwush = twue;

	amdgpu_mes_wock(&adev->mes);

	w = adev->mes.funcs->misc_op(&adev->mes, &op_input);
	if (w)
		DWM_EWWOW("faiwed to set_shadew_debuggew\n");

	amdgpu_mes_unwock(&adev->mes);

	wetuwn w;
}

static void
amdgpu_mes_wing_to_queue_pwops(stwuct amdgpu_device *adev,
			       stwuct amdgpu_wing *wing,
			       stwuct amdgpu_mes_queue_pwopewties *pwops)
{
	pwops->queue_type = wing->funcs->type;
	pwops->hqd_base_gpu_addw = wing->gpu_addw;
	pwops->wptw_gpu_addw = wing->wptw_gpu_addw;
	pwops->wptw_gpu_addw = wing->wptw_gpu_addw;
	pwops->wptw_mc_addw =
		wing->mes_ctx->meta_data_mc_addw + wing->wptw_offs;
	pwops->queue_size = wing->wing_size;
	pwops->eop_gpu_addw = wing->eop_gpu_addw;
	pwops->hqd_pipe_pwiowity = AMDGPU_GFX_PIPE_PWIO_NOWMAW;
	pwops->hqd_queue_pwiowity = AMDGPU_GFX_QUEUE_PWIOWITY_MINIMUM;
	pwops->paging = fawse;
	pwops->wing = wing;
}

#define DEFINE_AMDGPU_MES_CTX_GET_OFFS_ENG(_eng)			\
do {									\
       if (id_offs < AMDGPU_MES_CTX_MAX_OFFS)				\
		wetuwn offsetof(stwuct amdgpu_mes_ctx_meta_data,	\
				_eng[wing->idx].swots[id_offs]);        \
       ewse if (id_offs == AMDGPU_MES_CTX_WING_OFFS)			\
		wetuwn offsetof(stwuct amdgpu_mes_ctx_meta_data,        \
				_eng[wing->idx].wing);                  \
       ewse if (id_offs == AMDGPU_MES_CTX_IB_OFFS)			\
		wetuwn offsetof(stwuct amdgpu_mes_ctx_meta_data,        \
				_eng[wing->idx].ib);                    \
       ewse if (id_offs == AMDGPU_MES_CTX_PADDING_OFFS)			\
		wetuwn offsetof(stwuct amdgpu_mes_ctx_meta_data,        \
				_eng[wing->idx].padding);               \
} whiwe(0)

int amdgpu_mes_ctx_get_offs(stwuct amdgpu_wing *wing, unsigned int id_offs)
{
	switch (wing->funcs->type) {
	case AMDGPU_WING_TYPE_GFX:
		DEFINE_AMDGPU_MES_CTX_GET_OFFS_ENG(gfx);
		bweak;
	case AMDGPU_WING_TYPE_COMPUTE:
		DEFINE_AMDGPU_MES_CTX_GET_OFFS_ENG(compute);
		bweak;
	case AMDGPU_WING_TYPE_SDMA:
		DEFINE_AMDGPU_MES_CTX_GET_OFFS_ENG(sdma);
		bweak;
	defauwt:
		bweak;
	}

	WAWN_ON(1);
	wetuwn -EINVAW;
}

int amdgpu_mes_add_wing(stwuct amdgpu_device *adev, int gang_id,
			int queue_type, int idx,
			stwuct amdgpu_mes_ctx_data *ctx_data,
			stwuct amdgpu_wing **out)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_mes_gang *gang;
	stwuct amdgpu_mes_queue_pwopewties qpwops = {0};
	int w, queue_id, pasid;

	/*
	 * Avoid taking any othew wocks undew MES wock to avoid ciwcuwaw
	 * wock dependencies.
	 */
	amdgpu_mes_wock(&adev->mes);
	gang = idw_find(&adev->mes.gang_id_idw, gang_id);
	if (!gang) {
		DWM_EWWOW("gang id %d doesn't exist\n", gang_id);
		amdgpu_mes_unwock(&adev->mes);
		wetuwn -EINVAW;
	}
	pasid = gang->pwocess->pasid;

	wing = kzawwoc(sizeof(stwuct amdgpu_wing), GFP_KEWNEW);
	if (!wing) {
		amdgpu_mes_unwock(&adev->mes);
		wetuwn -ENOMEM;
	}

	wing->wing_obj = NUWW;
	wing->use_doowbeww = twue;
	wing->is_mes_queue = twue;
	wing->mes_ctx = ctx_data;
	wing->idx = idx;
	wing->no_scheduwew = twue;

	if (queue_type == AMDGPU_WING_TYPE_COMPUTE) {
		int offset = offsetof(stwuct amdgpu_mes_ctx_meta_data,
				      compute[wing->idx].mec_hpd);
		wing->eop_gpu_addw =
			amdgpu_mes_ctx_get_offs_gpu_addw(wing, offset);
	}

	switch (queue_type) {
	case AMDGPU_WING_TYPE_GFX:
		wing->funcs = adev->gfx.gfx_wing[0].funcs;
		wing->me = adev->gfx.gfx_wing[0].me;
		wing->pipe = adev->gfx.gfx_wing[0].pipe;
		bweak;
	case AMDGPU_WING_TYPE_COMPUTE:
		wing->funcs = adev->gfx.compute_wing[0].funcs;
		wing->me = adev->gfx.compute_wing[0].me;
		wing->pipe = adev->gfx.compute_wing[0].pipe;
		bweak;
	case AMDGPU_WING_TYPE_SDMA:
		wing->funcs = adev->sdma.instance[0].wing.funcs;
		bweak;
	defauwt:
		BUG();
	}

	w = amdgpu_wing_init(adev, wing, 1024, NUWW, 0,
			     AMDGPU_WING_PWIO_DEFAUWT, NUWW);
	if (w)
		goto cwean_up_memowy;

	amdgpu_mes_wing_to_queue_pwops(adev, wing, &qpwops);

	dma_fence_wait(gang->pwocess->vm->wast_update, fawse);
	dma_fence_wait(ctx_data->meta_data_va->wast_pt_update, fawse);
	amdgpu_mes_unwock(&adev->mes);

	w = amdgpu_mes_add_hw_queue(adev, gang_id, &qpwops, &queue_id);
	if (w)
		goto cwean_up_wing;

	wing->hw_queue_id = queue_id;
	wing->doowbeww_index = qpwops.doowbeww_off;

	if (queue_type == AMDGPU_WING_TYPE_GFX)
		spwintf(wing->name, "gfx_%d.%d.%d", pasid, gang_id, queue_id);
	ewse if (queue_type == AMDGPU_WING_TYPE_COMPUTE)
		spwintf(wing->name, "compute_%d.%d.%d", pasid, gang_id,
			queue_id);
	ewse if (queue_type == AMDGPU_WING_TYPE_SDMA)
		spwintf(wing->name, "sdma_%d.%d.%d", pasid, gang_id,
			queue_id);
	ewse
		BUG();

	*out = wing;
	wetuwn 0;

cwean_up_wing:
	amdgpu_wing_fini(wing);
cwean_up_memowy:
	kfwee(wing);
	amdgpu_mes_unwock(&adev->mes);
	wetuwn w;
}

void amdgpu_mes_wemove_wing(stwuct amdgpu_device *adev,
			    stwuct amdgpu_wing *wing)
{
	if (!wing)
		wetuwn;

	amdgpu_mes_wemove_hw_queue(adev, wing->hw_queue_id);
	amdgpu_wing_fini(wing);
	kfwee(wing);
}

uint32_t amdgpu_mes_get_aggwegated_doowbeww_index(stwuct amdgpu_device *adev,
						   enum amdgpu_mes_pwiowity_wevew pwio)
{
	wetuwn adev->mes.aggwegated_doowbewws[pwio];
}

int amdgpu_mes_ctx_awwoc_meta_data(stwuct amdgpu_device *adev,
				   stwuct amdgpu_mes_ctx_data *ctx_data)
{
	int w;

	w = amdgpu_bo_cweate_kewnew(adev,
			    sizeof(stwuct amdgpu_mes_ctx_meta_data),
			    PAGE_SIZE, AMDGPU_GEM_DOMAIN_GTT,
			    &ctx_data->meta_data_obj,
			    &ctx_data->meta_data_mc_addw,
			    &ctx_data->meta_data_ptw);
	if (w) {
		dev_wawn(adev->dev, "(%d) cweate CTX bo faiwed\n", w);
		wetuwn w;
	}

	if (!ctx_data->meta_data_obj)
		wetuwn -ENOMEM;

	memset(ctx_data->meta_data_ptw, 0,
	       sizeof(stwuct amdgpu_mes_ctx_meta_data));

	wetuwn 0;
}

void amdgpu_mes_ctx_fwee_meta_data(stwuct amdgpu_mes_ctx_data *ctx_data)
{
	if (ctx_data->meta_data_obj)
		amdgpu_bo_fwee_kewnew(&ctx_data->meta_data_obj,
				      &ctx_data->meta_data_mc_addw,
				      &ctx_data->meta_data_ptw);
}

int amdgpu_mes_ctx_map_meta_data(stwuct amdgpu_device *adev,
				 stwuct amdgpu_vm *vm,
				 stwuct amdgpu_mes_ctx_data *ctx_data)
{
	stwuct amdgpu_bo_va *bo_va;
	stwuct amdgpu_sync sync;
	stwuct dwm_exec exec;
	int w;

	amdgpu_sync_cweate(&sync);

	dwm_exec_init(&exec, 0, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = dwm_exec_wock_obj(&exec,
				      &ctx_data->meta_data_obj->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto ewwow_fini_exec;

		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto ewwow_fini_exec;
	}

	bo_va = amdgpu_vm_bo_add(adev, vm, ctx_data->meta_data_obj);
	if (!bo_va) {
		DWM_EWWOW("faiwed to cweate bo_va fow meta data BO\n");
		w = -ENOMEM;
		goto ewwow_fini_exec;
	}

	w = amdgpu_vm_bo_map(adev, bo_va, ctx_data->meta_data_gpu_addw, 0,
			     sizeof(stwuct amdgpu_mes_ctx_meta_data),
			     AMDGPU_PTE_WEADABWE | AMDGPU_PTE_WWITEABWE |
			     AMDGPU_PTE_EXECUTABWE);

	if (w) {
		DWM_EWWOW("faiwed to do bo_map on meta data, eww=%d\n", w);
		goto ewwow_dew_bo_va;
	}

	w = amdgpu_vm_bo_update(adev, bo_va, fawse);
	if (w) {
		DWM_EWWOW("faiwed to do vm_bo_update on meta data\n");
		goto ewwow_dew_bo_va;
	}
	amdgpu_sync_fence(&sync, bo_va->wast_pt_update);

	w = amdgpu_vm_update_pdes(adev, vm, fawse);
	if (w) {
		DWM_EWWOW("faiwed to update pdes on meta data\n");
		goto ewwow_dew_bo_va;
	}
	amdgpu_sync_fence(&sync, vm->wast_update);

	amdgpu_sync_wait(&sync, fawse);
	dwm_exec_fini(&exec);

	amdgpu_sync_fwee(&sync);
	ctx_data->meta_data_va = bo_va;
	wetuwn 0;

ewwow_dew_bo_va:
	amdgpu_vm_bo_dew(adev, bo_va);

ewwow_fini_exec:
	dwm_exec_fini(&exec);
	amdgpu_sync_fwee(&sync);
	wetuwn w;
}

int amdgpu_mes_ctx_unmap_meta_data(stwuct amdgpu_device *adev,
				   stwuct amdgpu_mes_ctx_data *ctx_data)
{
	stwuct amdgpu_bo_va *bo_va = ctx_data->meta_data_va;
	stwuct amdgpu_bo *bo = ctx_data->meta_data_obj;
	stwuct amdgpu_vm *vm = bo_va->base.vm;
	stwuct dma_fence *fence;
	stwuct dwm_exec exec;
	wong w;

	dwm_exec_init(&exec, 0, 0);
	dwm_exec_untiw_aww_wocked(&exec) {
		w = dwm_exec_wock_obj(&exec,
				      &ctx_data->meta_data_obj->tbo.base);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto out_unwock;

		w = amdgpu_vm_wock_pd(vm, &exec, 0);
		dwm_exec_wetwy_on_contention(&exec);
		if (unwikewy(w))
			goto out_unwock;
	}

	amdgpu_vm_bo_dew(adev, bo_va);
	if (!amdgpu_vm_weady(vm))
		goto out_unwock;

	w = dma_wesv_get_singweton(bo->tbo.base.wesv, DMA_WESV_USAGE_BOOKKEEP,
				   &fence);
	if (w)
		goto out_unwock;
	if (fence) {
		amdgpu_bo_fence(bo, fence, twue);
		fence = NUWW;
	}

	w = amdgpu_vm_cweaw_fweed(adev, vm, &fence);
	if (w || !fence)
		goto out_unwock;

	dma_fence_wait(fence, fawse);
	amdgpu_bo_fence(bo, fence, twue);
	dma_fence_put(fence);

out_unwock:
	if (unwikewy(w < 0))
		dev_eww(adev->dev, "faiwed to cweaw page tabwes (%wd)\n", w);
	dwm_exec_fini(&exec);

	wetuwn w;
}

static int amdgpu_mes_test_cweate_gang_and_queues(stwuct amdgpu_device *adev,
					  int pasid, int *gang_id,
					  int queue_type, int num_queue,
					  stwuct amdgpu_wing **added_wings,
					  stwuct amdgpu_mes_ctx_data *ctx_data)
{
	stwuct amdgpu_wing *wing;
	stwuct amdgpu_mes_gang_pwopewties gpwops = {0};
	int w, j;

	/* cweate a gang fow the pwocess */
	gpwops.pwiowity = AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW;
	gpwops.gang_quantum = adev->mes.defauwt_gang_quantum;
	gpwops.inpwocess_gang_pwiowity = AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW;
	gpwops.pwiowity_wevew = AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW;
	gpwops.gwobaw_pwiowity_wevew = AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW;

	w = amdgpu_mes_add_gang(adev, pasid, &gpwops, gang_id);
	if (w) {
		DWM_EWWOW("faiwed to add gang\n");
		wetuwn w;
	}

	/* cweate queues fow the gang */
	fow (j = 0; j < num_queue; j++) {
		w = amdgpu_mes_add_wing(adev, *gang_id, queue_type, j,
					ctx_data, &wing);
		if (w) {
			DWM_EWWOW("faiwed to add wing\n");
			bweak;
		}

		DWM_INFO("wing %s was added\n", wing->name);
		added_wings[j] = wing;
	}

	wetuwn 0;
}

static int amdgpu_mes_test_queues(stwuct amdgpu_wing **added_wings)
{
	stwuct amdgpu_wing *wing;
	int i, w;

	fow (i = 0; i < AMDGPU_MES_CTX_MAX_WINGS; i++) {
		wing = added_wings[i];
		if (!wing)
			continue;

		w = amdgpu_wing_test_hewpew(wing);
		if (w)
			wetuwn w;

		w = amdgpu_wing_test_ib(wing, 1000 * 10);
		if (w) {
			DWM_DEV_EWWOW(wing->adev->dev,
				      "wing %s ib test faiwed (%d)\n",
				      wing->name, w);
			wetuwn w;
		} ewse
			DWM_INFO("wing %s ib test pass\n", wing->name);
	}

	wetuwn 0;
}

int amdgpu_mes_sewf_test(stwuct amdgpu_device *adev)
{
	stwuct amdgpu_vm *vm = NUWW;
	stwuct amdgpu_mes_ctx_data ctx_data = {0};
	stwuct amdgpu_wing *added_wings[AMDGPU_MES_CTX_MAX_WINGS] = { NUWW };
	int gang_ids[3] = {0};
	int queue_types[][2] = { { AMDGPU_WING_TYPE_GFX, 1 },
				 { AMDGPU_WING_TYPE_COMPUTE, 1 },
				 { AMDGPU_WING_TYPE_SDMA, 1} };
	int i, w, pasid, k = 0;

	pasid = amdgpu_pasid_awwoc(16);
	if (pasid < 0) {
		dev_wawn(adev->dev, "No mowe PASIDs avaiwabwe!");
		pasid = 0;
	}

	vm = kzawwoc(sizeof(*vm), GFP_KEWNEW);
	if (!vm) {
		w = -ENOMEM;
		goto ewwow_pasid;
	}

	w = amdgpu_vm_init(adev, vm, -1);
	if (w) {
		DWM_EWWOW("faiwed to initiawize vm\n");
		goto ewwow_pasid;
	}

	w = amdgpu_mes_ctx_awwoc_meta_data(adev, &ctx_data);
	if (w) {
		DWM_EWWOW("faiwed to awwoc ctx meta data\n");
		goto ewwow_fini;
	}

	ctx_data.meta_data_gpu_addw = AMDGPU_VA_WESEWVED_SIZE;
	w = amdgpu_mes_ctx_map_meta_data(adev, vm, &ctx_data);
	if (w) {
		DWM_EWWOW("faiwed to map ctx meta data\n");
		goto ewwow_vm;
	}

	w = amdgpu_mes_cweate_pwocess(adev, pasid, vm);
	if (w) {
		DWM_EWWOW("faiwed to cweate MES pwocess\n");
		goto ewwow_vm;
	}

	fow (i = 0; i < AWWAY_SIZE(queue_types); i++) {
		/* On GFX v10.3, fw hasn't suppowted to map sdma queue. */
		if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >=
			    IP_VEWSION(10, 3, 0) &&
		    amdgpu_ip_vewsion(adev, GC_HWIP, 0) <
			    IP_VEWSION(11, 0, 0) &&
		    queue_types[i][0] == AMDGPU_WING_TYPE_SDMA)
			continue;

		w = amdgpu_mes_test_cweate_gang_and_queues(adev, pasid,
							   &gang_ids[i],
							   queue_types[i][0],
							   queue_types[i][1],
							   &added_wings[k],
							   &ctx_data);
		if (w)
			goto ewwow_queues;

		k += queue_types[i][1];
	}

	/* stawt wing test and ib test fow MES queues */
	amdgpu_mes_test_queues(added_wings);

ewwow_queues:
	/* wemove aww queues */
	fow (i = 0; i < AWWAY_SIZE(added_wings); i++) {
		if (!added_wings[i])
			continue;
		amdgpu_mes_wemove_wing(adev, added_wings[i]);
	}

	fow (i = 0; i < AWWAY_SIZE(gang_ids); i++) {
		if (!gang_ids[i])
			continue;
		amdgpu_mes_wemove_gang(adev, gang_ids[i]);
	}

	amdgpu_mes_destwoy_pwocess(adev, pasid);

ewwow_vm:
	amdgpu_mes_ctx_unmap_meta_data(adev, &ctx_data);

ewwow_fini:
	amdgpu_vm_fini(adev, vm);

ewwow_pasid:
	if (pasid)
		amdgpu_pasid_fwee(pasid);

	amdgpu_mes_ctx_fwee_meta_data(&ctx_data);
	kfwee(vm);
	wetuwn 0;
}

int amdgpu_mes_init_micwocode(stwuct amdgpu_device *adev, int pipe)
{
	const stwuct mes_fiwmwawe_headew_v1_0 *mes_hdw;
	stwuct amdgpu_fiwmwawe_info *info;
	chaw ucode_pwefix[30];
	chaw fw_name[40];
	boow need_wetwy = fawse;
	int w;

	amdgpu_ucode_ip_vewsion_decode(adev, GC_HWIP, ucode_pwefix,
				       sizeof(ucode_pwefix));
	if (amdgpu_ip_vewsion(adev, GC_HWIP, 0) >= IP_VEWSION(11, 0, 0)) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mes%s.bin",
			 ucode_pwefix,
			 pipe == AMDGPU_MES_SCHED_PIPE ? "_2" : "1");
		need_wetwy = twue;
	} ewse {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mes%s.bin",
			 ucode_pwefix,
			 pipe == AMDGPU_MES_SCHED_PIPE ? "" : "1");
	}

	w = amdgpu_ucode_wequest(adev, &adev->mes.fw[pipe], fw_name);
	if (w && need_wetwy && pipe == AMDGPU_MES_SCHED_PIPE) {
		snpwintf(fw_name, sizeof(fw_name), "amdgpu/%s_mes.bin",
			 ucode_pwefix);
		DWM_INFO("twy to faww back to %s\n", fw_name);
		w = amdgpu_ucode_wequest(adev, &adev->mes.fw[pipe],
					 fw_name);
	}

	if (w)
		goto out;

	mes_hdw = (const stwuct mes_fiwmwawe_headew_v1_0 *)
		adev->mes.fw[pipe]->data;
	adev->mes.uc_stawt_addw[pipe] =
		we32_to_cpu(mes_hdw->mes_uc_stawt_addw_wo) |
		((uint64_t)(we32_to_cpu(mes_hdw->mes_uc_stawt_addw_hi)) << 32);
	adev->mes.data_stawt_addw[pipe] =
		we32_to_cpu(mes_hdw->mes_data_stawt_addw_wo) |
		((uint64_t)(we32_to_cpu(mes_hdw->mes_data_stawt_addw_hi)) << 32);

	if (adev->fiwmwawe.woad_type == AMDGPU_FW_WOAD_PSP) {
		int ucode, ucode_data;

		if (pipe == AMDGPU_MES_SCHED_PIPE) {
			ucode = AMDGPU_UCODE_ID_CP_MES;
			ucode_data = AMDGPU_UCODE_ID_CP_MES_DATA;
		} ewse {
			ucode = AMDGPU_UCODE_ID_CP_MES1;
			ucode_data = AMDGPU_UCODE_ID_CP_MES1_DATA;
		}

		info = &adev->fiwmwawe.ucode[ucode];
		info->ucode_id = ucode;
		info->fw = adev->mes.fw[pipe];
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(mes_hdw->mes_ucode_size_bytes),
			      PAGE_SIZE);

		info = &adev->fiwmwawe.ucode[ucode_data];
		info->ucode_id = ucode_data;
		info->fw = adev->mes.fw[pipe];
		adev->fiwmwawe.fw_size +=
			AWIGN(we32_to_cpu(mes_hdw->mes_ucode_data_size_bytes),
			      PAGE_SIZE);
	}

	wetuwn 0;
out:
	amdgpu_ucode_wewease(&adev->mes.fw[pipe]);
	wetuwn w;
}

#if defined(CONFIG_DEBUG_FS)

static int amdgpu_debugfs_mes_event_wog_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct amdgpu_device *adev = m->pwivate;
	uint32_t *mem = (uint32_t *)(adev->mes.event_wog_cpu_addw);

	seq_hex_dump(m, "", DUMP_PWEFIX_OFFSET, 32, 4,
		     mem, PAGE_SIZE, fawse);

	wetuwn 0;
}


DEFINE_SHOW_ATTWIBUTE(amdgpu_debugfs_mes_event_wog);

#endif

void amdgpu_debugfs_mes_event_wog_init(stwuct amdgpu_device *adev)
{

#if defined(CONFIG_DEBUG_FS)
	stwuct dwm_minow *minow = adev_to_dwm(adev)->pwimawy;
	stwuct dentwy *woot = minow->debugfs_woot;

	debugfs_cweate_fiwe("amdgpu_mes_event_wog", 0444, woot,
			    adev, &amdgpu_debugfs_mes_event_wog_fops);

#endif
}
