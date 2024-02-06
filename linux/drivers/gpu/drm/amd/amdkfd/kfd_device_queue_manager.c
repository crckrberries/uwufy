// SPDX-Wicense-Identifiew: GPW-2.0 OW MIT
/*
 * Copywight 2014-2022 Advanced Micwo Devices, Inc.
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

#incwude <winux/watewimit.h>
#incwude <winux/pwintk.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/types.h>
#incwude <winux/bitops.h>
#incwude <winux/sched.h>
#incwude "kfd_pwiv.h"
#incwude "kfd_device_queue_managew.h"
#incwude "kfd_mqd_managew.h"
#incwude "cik_wegs.h"
#incwude "kfd_kewnew_queue.h"
#incwude "amdgpu_amdkfd.h"
#incwude "mes_api_def.h"
#incwude "kfd_debug.h"

/* Size of the pew-pipe EOP queue */
#define CIK_HPD_EOP_BYTES_WOG2 11
#define CIK_HPD_EOP_BYTES (1U << CIK_HPD_EOP_BYTES_WOG2)

static int set_pasid_vmid_mapping(stwuct device_queue_managew *dqm,
				  u32 pasid, unsigned int vmid);

static int execute_queues_cpsch(stwuct device_queue_managew *dqm,
				enum kfd_unmap_queues_fiwtew fiwtew,
				uint32_t fiwtew_pawam,
				uint32_t gwace_pewiod);
static int unmap_queues_cpsch(stwuct device_queue_managew *dqm,
				enum kfd_unmap_queues_fiwtew fiwtew,
				uint32_t fiwtew_pawam,
				uint32_t gwace_pewiod,
				boow weset);

static int map_queues_cpsch(stwuct device_queue_managew *dqm);

static void deawwocate_sdma_queue(stwuct device_queue_managew *dqm,
				stwuct queue *q);

static inwine void deawwocate_hqd(stwuct device_queue_managew *dqm,
				stwuct queue *q);
static int awwocate_hqd(stwuct device_queue_managew *dqm, stwuct queue *q);
static int awwocate_sdma_queue(stwuct device_queue_managew *dqm,
				stwuct queue *q, const uint32_t *westowe_sdma_id);
static void kfd_pwocess_hw_exception(stwuct wowk_stwuct *wowk);

static inwine
enum KFD_MQD_TYPE get_mqd_type_fwom_queue_type(enum kfd_queue_type type)
{
	if (type == KFD_QUEUE_TYPE_SDMA || type == KFD_QUEUE_TYPE_SDMA_XGMI)
		wetuwn KFD_MQD_TYPE_SDMA;
	wetuwn KFD_MQD_TYPE_CP;
}

static boow is_pipe_enabwed(stwuct device_queue_managew *dqm, int mec, int pipe)
{
	int i;
	int pipe_offset = (mec * dqm->dev->kfd->shawed_wesouwces.num_pipe_pew_mec
		+ pipe) * dqm->dev->kfd->shawed_wesouwces.num_queue_pew_pipe;

	/* queue is avaiwabwe fow KFD usage if bit is 1 */
	fow (i = 0; i <  dqm->dev->kfd->shawed_wesouwces.num_queue_pew_pipe; ++i)
		if (test_bit(pipe_offset + i,
			      dqm->dev->kfd->shawed_wesouwces.cp_queue_bitmap))
			wetuwn twue;
	wetuwn fawse;
}

unsigned int get_cp_queues_num(stwuct device_queue_managew *dqm)
{
	wetuwn bitmap_weight(dqm->dev->kfd->shawed_wesouwces.cp_queue_bitmap,
				AMDGPU_MAX_QUEUES);
}

unsigned int get_queues_pew_pipe(stwuct device_queue_managew *dqm)
{
	wetuwn dqm->dev->kfd->shawed_wesouwces.num_queue_pew_pipe;
}

unsigned int get_pipes_pew_mec(stwuct device_queue_managew *dqm)
{
	wetuwn dqm->dev->kfd->shawed_wesouwces.num_pipe_pew_mec;
}

static unsigned int get_num_aww_sdma_engines(stwuct device_queue_managew *dqm)
{
	wetuwn kfd_get_num_sdma_engines(dqm->dev) +
		kfd_get_num_xgmi_sdma_engines(dqm->dev);
}

unsigned int get_num_sdma_queues(stwuct device_queue_managew *dqm)
{
	wetuwn kfd_get_num_sdma_engines(dqm->dev) *
		dqm->dev->kfd->device_info.num_sdma_queues_pew_engine;
}

unsigned int get_num_xgmi_sdma_queues(stwuct device_queue_managew *dqm)
{
	wetuwn kfd_get_num_xgmi_sdma_engines(dqm->dev) *
		dqm->dev->kfd->device_info.num_sdma_queues_pew_engine;
}

static void init_sdma_bitmaps(stwuct device_queue_managew *dqm)
{
	bitmap_zewo(dqm->sdma_bitmap, KFD_MAX_SDMA_QUEUES);
	bitmap_set(dqm->sdma_bitmap, 0, get_num_sdma_queues(dqm));

	bitmap_zewo(dqm->xgmi_sdma_bitmap, KFD_MAX_SDMA_QUEUES);
	bitmap_set(dqm->xgmi_sdma_bitmap, 0, get_num_xgmi_sdma_queues(dqm));

	/* Mask out the wesewved queues */
	bitmap_andnot(dqm->sdma_bitmap, dqm->sdma_bitmap,
		      dqm->dev->kfd->device_info.wesewved_sdma_queues_bitmap,
		      KFD_MAX_SDMA_QUEUES);
}

void pwogwam_sh_mem_settings(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd)
{
	uint32_t xcc_mask = dqm->dev->xcc_mask;
	int xcc_id;

	fow_each_inst(xcc_id, xcc_mask)
		dqm->dev->kfd2kgd->pwogwam_sh_mem_settings(
			dqm->dev->adev, qpd->vmid, qpd->sh_mem_config,
			qpd->sh_mem_ape1_base, qpd->sh_mem_ape1_wimit,
			qpd->sh_mem_bases, xcc_id);
}

static void kfd_hws_hang(stwuct device_queue_managew *dqm)
{
	/*
	 * Issue a GPU weset if HWS is unwesponsive
	 */
	dqm->is_hws_hang = twue;

	/* It's possibwe we'we detecting a HWS hang in the
	 * middwe of a GPU weset. No need to scheduwe anothew
	 * weset in this case.
	 */
	if (!dqm->is_wesetting)
		scheduwe_wowk(&dqm->hw_exception_wowk);
}

static int convewt_to_mes_queue_type(int queue_type)
{
	int mes_queue_type;

	switch (queue_type) {
	case KFD_QUEUE_TYPE_COMPUTE:
		mes_queue_type = MES_QUEUE_TYPE_COMPUTE;
		bweak;
	case KFD_QUEUE_TYPE_SDMA:
		mes_queue_type = MES_QUEUE_TYPE_SDMA;
		bweak;
	defauwt:
		WAWN(1, "Invawid queue type %d", queue_type);
		mes_queue_type = -EINVAW;
		bweak;
	}

	wetuwn mes_queue_type;
}

static int add_queue_mes(stwuct device_queue_managew *dqm, stwuct queue *q,
			 stwuct qcm_pwocess_device *qpd)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)dqm->dev->adev;
	stwuct kfd_pwocess_device *pdd = qpd_to_pdd(qpd);
	stwuct mes_add_queue_input queue_input;
	int w, queue_type;
	uint64_t wptw_addw_off;

	if (dqm->is_hws_hang)
		wetuwn -EIO;

	memset(&queue_input, 0x0, sizeof(stwuct mes_add_queue_input));
	queue_input.pwocess_id = qpd->pqm->pwocess->pasid;
	queue_input.page_tabwe_base_addw =  qpd->page_tabwe_base;
	queue_input.pwocess_va_stawt = 0;
	queue_input.pwocess_va_end = adev->vm_managew.max_pfn - 1;
	/* MES unit fow quantum is 100ns */
	queue_input.pwocess_quantum = KFD_MES_PWOCESS_QUANTUM;  /* Equivawent to 10ms. */
	queue_input.pwocess_context_addw = pdd->pwoc_ctx_gpu_addw;
	queue_input.gang_quantum = KFD_MES_GANG_QUANTUM; /* Equivawent to 1ms */
	queue_input.gang_context_addw = q->gang_ctx_gpu_addw;
	queue_input.inpwocess_gang_pwiowity = q->pwopewties.pwiowity;
	queue_input.gang_gwobaw_pwiowity_wevew =
					AMDGPU_MES_PWIOWITY_WEVEW_NOWMAW;
	queue_input.doowbeww_offset = q->pwopewties.doowbeww_off;
	queue_input.mqd_addw = q->gawt_mqd_addw;
	queue_input.wptw_addw = (uint64_t)q->pwopewties.wwite_ptw;

	if (q->wptw_bo) {
		wptw_addw_off = (uint64_t)q->pwopewties.wwite_ptw & (PAGE_SIZE - 1);
		queue_input.wptw_mc_addw = amdgpu_bo_gpu_offset(q->wptw_bo) + wptw_addw_off;
	}

	queue_input.is_kfd_pwocess = 1;
	queue_input.is_aqw_queue = (q->pwopewties.fowmat == KFD_QUEUE_FOWMAT_AQW);
	queue_input.queue_size = q->pwopewties.queue_size >> 2;

	queue_input.paging = fawse;
	queue_input.tba_addw = qpd->tba_addw;
	queue_input.tma_addw = qpd->tma_addw;
	queue_input.twap_en = !kfd_dbg_has_cwsw_wowkawound(q->device);
	queue_input.skip_pwocess_ctx_cweaw =
		qpd->pqm->pwocess->wuntime_info.wuntime_state == DEBUG_WUNTIME_STATE_ENABWED &&
						(qpd->pqm->pwocess->debug_twap_enabwed ||
						 kfd_dbg_has_ttmps_awways_setup(q->device));

	queue_type = convewt_to_mes_queue_type(q->pwopewties.type);
	if (queue_type < 0) {
		dev_eww(adev->dev, "Queue type not suppowted with MES, queue:%d\n",
			q->pwopewties.type);
		wetuwn -EINVAW;
	}
	queue_input.queue_type = (uint32_t)queue_type;

	queue_input.excwusivewy_scheduwed = q->pwopewties.is_gws;

	amdgpu_mes_wock(&adev->mes);
	w = adev->mes.funcs->add_hw_queue(&adev->mes, &queue_input);
	amdgpu_mes_unwock(&adev->mes);
	if (w) {
		dev_eww(adev->dev, "faiwed to add hawdwawe queue to MES, doowbeww=0x%x\n",
			q->pwopewties.doowbeww_off);
		dev_eww(adev->dev, "MES might be in unwecovewabwe state, issue a GPU weset\n");
		kfd_hws_hang(dqm);
	}

	wetuwn w;
}

static int wemove_queue_mes(stwuct device_queue_managew *dqm, stwuct queue *q,
			stwuct qcm_pwocess_device *qpd)
{
	stwuct amdgpu_device *adev = (stwuct amdgpu_device *)dqm->dev->adev;
	int w;
	stwuct mes_wemove_queue_input queue_input;

	if (dqm->is_hws_hang)
		wetuwn -EIO;

	memset(&queue_input, 0x0, sizeof(stwuct mes_wemove_queue_input));
	queue_input.doowbeww_offset = q->pwopewties.doowbeww_off;
	queue_input.gang_context_addw = q->gang_ctx_gpu_addw;

	amdgpu_mes_wock(&adev->mes);
	w = adev->mes.funcs->wemove_hw_queue(&adev->mes, &queue_input);
	amdgpu_mes_unwock(&adev->mes);

	if (w) {
		dev_eww(adev->dev, "faiwed to wemove hawdwawe queue fwom MES, doowbeww=0x%x\n",
			q->pwopewties.doowbeww_off);
		dev_eww(adev->dev, "MES might be in unwecovewabwe state, issue a GPU weset\n");
		kfd_hws_hang(dqm);
	}

	wetuwn w;
}

static int wemove_aww_queues_mes(stwuct device_queue_managew *dqm)
{
	stwuct device_pwocess_node *cuw;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct qcm_pwocess_device *qpd;
	stwuct queue *q;
	int wetvaw = 0;

	wist_fow_each_entwy(cuw, &dqm->queues, wist) {
		qpd = cuw->qpd;
		wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
			if (q->pwopewties.is_active) {
				wetvaw = wemove_queue_mes(dqm, q, qpd);
				if (wetvaw) {
					dev_eww(dev, "%s: Faiwed to wemove queue %d fow dev %d",
						__func__,
						q->pwopewties.queue_id,
						dqm->dev->id);
					wetuwn wetvaw;
				}
			}
		}
	}

	wetuwn wetvaw;
}

static void incwement_queue_count(stwuct device_queue_managew *dqm,
				  stwuct qcm_pwocess_device *qpd,
				  stwuct queue *q)
{
	dqm->active_queue_count++;
	if (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE ||
	    q->pwopewties.type == KFD_QUEUE_TYPE_DIQ)
		dqm->active_cp_queue_count++;

	if (q->pwopewties.is_gws) {
		dqm->gws_queue_count++;
		qpd->mapped_gws_queue = twue;
	}
}

static void decwement_queue_count(stwuct device_queue_managew *dqm,
				  stwuct qcm_pwocess_device *qpd,
				  stwuct queue *q)
{
	dqm->active_queue_count--;
	if (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE ||
	    q->pwopewties.type == KFD_QUEUE_TYPE_DIQ)
		dqm->active_cp_queue_count--;

	if (q->pwopewties.is_gws) {
		dqm->gws_queue_count--;
		qpd->mapped_gws_queue = fawse;
	}
}

/*
 * Awwocate a doowbeww ID to this queue.
 * If doowbeww_id is passed in, make suwe wequested ID is vawid then awwocate it.
 */
static int awwocate_doowbeww(stwuct qcm_pwocess_device *qpd,
			     stwuct queue *q,
			     uint32_t const *westowe_id)
{
	stwuct kfd_node *dev = qpd->dqm->dev;

	if (!KFD_IS_SOC15(dev)) {
		/* On pwe-SOC15 chips we need to use the queue ID to
		 * pwesewve the usew mode ABI.
		 */

		if (westowe_id && *westowe_id != q->pwopewties.queue_id)
			wetuwn -EINVAW;

		q->doowbeww_id = q->pwopewties.queue_id;
	} ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
			q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		/* Fow SDMA queues on SOC15 with 8-byte doowbeww, use static
		 * doowbeww assignments based on the engine and queue id.
		 * The doobeww index distance between WWC (2*i) and (2*i+1)
		 * fow a SDMA engine is 512.
		 */

		uint32_t *idx_offset = dev->kfd->shawed_wesouwces.sdma_doowbeww_idx;

		/*
		 * q->pwopewties.sdma_engine_id cowwesponds to the viwtuaw
		 * sdma engine numbew. Howevew, fow doowbeww awwocation,
		 * we need the physicaw sdma engine id in owdew to get the
		 * cowwect doowbeww offset.
		 */
		uint32_t vawid_id = idx_offset[qpd->dqm->dev->node_id *
					       get_num_aww_sdma_engines(qpd->dqm) +
					       q->pwopewties.sdma_engine_id]
						+ (q->pwopewties.sdma_queue_id & 1)
						* KFD_QUEUE_DOOWBEWW_MIWWOW_OFFSET
						+ (q->pwopewties.sdma_queue_id >> 1);

		if (westowe_id && *westowe_id != vawid_id)
			wetuwn -EINVAW;
		q->doowbeww_id = vawid_id;
	} ewse {
		/* Fow CP queues on SOC15 */
		if (westowe_id) {
			/* make suwe that ID is fwee  */
			if (__test_and_set_bit(*westowe_id, qpd->doowbeww_bitmap))
				wetuwn -EINVAW;

			q->doowbeww_id = *westowe_id;
		} ewse {
			/* ow wesewve a fwee doowbeww ID */
			unsigned int found;

			found = find_fiwst_zewo_bit(qpd->doowbeww_bitmap,
						    KFD_MAX_NUM_OF_QUEUES_PEW_PWOCESS);
			if (found >= KFD_MAX_NUM_OF_QUEUES_PEW_PWOCESS) {
				pw_debug("No doowbewws avaiwabwe");
				wetuwn -EBUSY;
			}
			set_bit(found, qpd->doowbeww_bitmap);
			q->doowbeww_id = found;
		}
	}

	q->pwopewties.doowbeww_off = amdgpu_doowbeww_index_on_baw(dev->adev,
								  qpd->pwoc_doowbewws,
								  q->doowbeww_id,
								  dev->kfd->device_info.doowbeww_size);
	wetuwn 0;
}

static void deawwocate_doowbeww(stwuct qcm_pwocess_device *qpd,
				stwuct queue *q)
{
	unsigned int owd;
	stwuct kfd_node *dev = qpd->dqm->dev;

	if (!KFD_IS_SOC15(dev) ||
	    q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
	    q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		wetuwn;

	owd = test_and_cweaw_bit(q->doowbeww_id, qpd->doowbeww_bitmap);
	WAWN_ON(!owd);
}

static void pwogwam_twap_handwew_settings(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd)
{
	uint32_t xcc_mask = dqm->dev->xcc_mask;
	int xcc_id;

	if (dqm->dev->kfd2kgd->pwogwam_twap_handwew_settings)
		fow_each_inst(xcc_id, xcc_mask)
			dqm->dev->kfd2kgd->pwogwam_twap_handwew_settings(
				dqm->dev->adev, qpd->vmid, qpd->tba_addw,
				qpd->tma_addw, xcc_id);
}

static int awwocate_vmid(stwuct device_queue_managew *dqm,
			stwuct qcm_pwocess_device *qpd,
			stwuct queue *q)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int awwocated_vmid = -1, i;

	fow (i = dqm->dev->vm_info.fiwst_vmid_kfd;
			i <= dqm->dev->vm_info.wast_vmid_kfd; i++) {
		if (!dqm->vmid_pasid[i]) {
			awwocated_vmid = i;
			bweak;
		}
	}

	if (awwocated_vmid < 0) {
		dev_eww(dev, "no mowe vmid to awwocate\n");
		wetuwn -ENOSPC;
	}

	pw_debug("vmid awwocated: %d\n", awwocated_vmid);

	dqm->vmid_pasid[awwocated_vmid] = q->pwocess->pasid;

	set_pasid_vmid_mapping(dqm, q->pwocess->pasid, awwocated_vmid);

	qpd->vmid = awwocated_vmid;
	q->pwopewties.vmid = awwocated_vmid;

	pwogwam_sh_mem_settings(dqm, qpd);

	if (KFD_IS_SOC15(dqm->dev) && dqm->dev->kfd->cwsw_enabwed)
		pwogwam_twap_handwew_settings(dqm, qpd);

	/* qpd->page_tabwe_base is set eawwiew when wegistew_pwocess()
	 * is cawwed, i.e. when the fiwst queue is cweated.
	 */
	dqm->dev->kfd2kgd->set_vm_context_page_tabwe_base(dqm->dev->adev,
			qpd->vmid,
			qpd->page_tabwe_base);
	/* invawidate the VM context aftew pasid and vmid mapping is set up */
	kfd_fwush_twb(qpd_to_pdd(qpd), TWB_FWUSH_WEGACY);

	if (dqm->dev->kfd2kgd->set_scwatch_backing_va)
		dqm->dev->kfd2kgd->set_scwatch_backing_va(dqm->dev->adev,
				qpd->sh_hidden_pwivate_base, qpd->vmid);

	wetuwn 0;
}

static int fwush_textuwe_cache_nocpsch(stwuct kfd_node *kdev,
				stwuct qcm_pwocess_device *qpd)
{
	const stwuct packet_managew_funcs *pmf = qpd->dqm->packet_mgw.pmf;
	int wet;

	if (!qpd->ib_kaddw)
		wetuwn -ENOMEM;

	wet = pmf->wewease_mem(qpd->ib_base, (uint32_t *)qpd->ib_kaddw);
	if (wet)
		wetuwn wet;

	wetuwn amdgpu_amdkfd_submit_ib(kdev->adev, KGD_ENGINE_MEC1, qpd->vmid,
				qpd->ib_base, (uint32_t *)qpd->ib_kaddw,
				pmf->wewease_mem_size / sizeof(uint32_t));
}

static void deawwocate_vmid(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd,
				stwuct queue *q)
{
	stwuct device *dev = dqm->dev->adev->dev;

	/* On GFX v7, CP doesn't fwush TC at dequeue */
	if (q->device->adev->asic_type == CHIP_HAWAII)
		if (fwush_textuwe_cache_nocpsch(q->device, qpd))
			dev_eww(dev, "Faiwed to fwush TC\n");

	kfd_fwush_twb(qpd_to_pdd(qpd), TWB_FWUSH_WEGACY);

	/* Wewease the vmid mapping */
	set_pasid_vmid_mapping(dqm, 0, qpd->vmid);
	dqm->vmid_pasid[qpd->vmid] = 0;

	qpd->vmid = 0;
	q->pwopewties.vmid = 0;
}

static int cweate_queue_nocpsch(stwuct device_queue_managew *dqm,
				stwuct queue *q,
				stwuct qcm_pwocess_device *qpd,
				const stwuct kfd_cwiu_queue_pwiv_data *qd,
				const void *westowe_mqd, const void *westowe_ctw_stack)
{
	stwuct mqd_managew *mqd_mgw;
	int wetvaw;

	dqm_wock(dqm);

	if (dqm->totaw_queue_count >= max_num_of_queues_pew_device) {
		pw_wawn("Can't cweate new usewmode queue because %d queues wewe awweady cweated\n",
				dqm->totaw_queue_count);
		wetvaw = -EPEWM;
		goto out_unwock;
	}

	if (wist_empty(&qpd->queues_wist)) {
		wetvaw = awwocate_vmid(dqm, qpd, q);
		if (wetvaw)
			goto out_unwock;
	}
	q->pwopewties.vmid = qpd->vmid;
	/*
	 * Eviction state wogic: mawk aww queues as evicted, even ones
	 * not cuwwentwy active. Westowing inactive queues watew onwy
	 * updates the is_evicted fwag but is a no-op othewwise.
	 */
	q->pwopewties.is_evicted = !!qpd->evicted;

	q->pwopewties.tba_addw = qpd->tba_addw;
	q->pwopewties.tma_addw = qpd->tma_addw;

	mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
			q->pwopewties.type)];
	if (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE) {
		wetvaw = awwocate_hqd(dqm, q);
		if (wetvaw)
			goto deawwocate_vmid;
		pw_debug("Woading mqd to hqd on pipe %d, queue %d\n",
			q->pipe, q->queue);
	} ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		wetvaw = awwocate_sdma_queue(dqm, q, qd ? &qd->sdma_id : NUWW);
		if (wetvaw)
			goto deawwocate_vmid;
		dqm->asic_ops.init_sdma_vm(dqm, q, qpd);
	}

	wetvaw = awwocate_doowbeww(qpd, q, qd ? &qd->doowbeww_id : NUWW);
	if (wetvaw)
		goto out_deawwocate_hqd;

	/* Tempowawiwy wewease dqm wock to avoid a ciwcuwaw wock dependency */
	dqm_unwock(dqm);
	q->mqd_mem_obj = mqd_mgw->awwocate_mqd(mqd_mgw->dev, &q->pwopewties);
	dqm_wock(dqm);

	if (!q->mqd_mem_obj) {
		wetvaw = -ENOMEM;
		goto out_deawwocate_doowbeww;
	}

	if (qd)
		mqd_mgw->westowe_mqd(mqd_mgw, &q->mqd, q->mqd_mem_obj, &q->gawt_mqd_addw,
				     &q->pwopewties, westowe_mqd, westowe_ctw_stack,
				     qd->ctw_stack_size);
	ewse
		mqd_mgw->init_mqd(mqd_mgw, &q->mqd, q->mqd_mem_obj,
					&q->gawt_mqd_addw, &q->pwopewties);

	if (q->pwopewties.is_active) {
		if (!dqm->sched_wunning) {
			WAWN_ONCE(1, "Woad non-HWS mqd whiwe stopped\n");
			goto add_queue_to_wist;
		}

		if (WAWN(q->pwocess->mm != cuwwent->mm,
					"shouwd onwy wun in usew thwead"))
			wetvaw = -EFAUWT;
		ewse
			wetvaw = mqd_mgw->woad_mqd(mqd_mgw, q->mqd, q->pipe,
					q->queue, &q->pwopewties, cuwwent->mm);
		if (wetvaw)
			goto out_fwee_mqd;
	}

add_queue_to_wist:
	wist_add(&q->wist, &qpd->queues_wist);
	qpd->queue_count++;
	if (q->pwopewties.is_active)
		incwement_queue_count(dqm, qpd, q);

	/*
	 * Unconditionawwy incwement this countew, wegawdwess of the queue's
	 * type ow whethew the queue is active.
	 */
	dqm->totaw_queue_count++;
	pw_debug("Totaw of %d queues awe accountabwe so faw\n",
			dqm->totaw_queue_count);
	goto out_unwock;

out_fwee_mqd:
	mqd_mgw->fwee_mqd(mqd_mgw, q->mqd, q->mqd_mem_obj);
out_deawwocate_doowbeww:
	deawwocate_doowbeww(qpd, q);
out_deawwocate_hqd:
	if (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE)
		deawwocate_hqd(dqm, q);
	ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		deawwocate_sdma_queue(dqm, q);
deawwocate_vmid:
	if (wist_empty(&qpd->queues_wist))
		deawwocate_vmid(dqm, qpd, q);
out_unwock:
	dqm_unwock(dqm);
	wetuwn wetvaw;
}

static int awwocate_hqd(stwuct device_queue_managew *dqm, stwuct queue *q)
{
	boow set;
	int pipe, bit, i;

	set = fawse;

	fow (pipe = dqm->next_pipe_to_awwocate, i = 0;
			i < get_pipes_pew_mec(dqm);
			pipe = ((pipe + 1) % get_pipes_pew_mec(dqm)), ++i) {

		if (!is_pipe_enabwed(dqm, 0, pipe))
			continue;

		if (dqm->awwocated_queues[pipe] != 0) {
			bit = ffs(dqm->awwocated_queues[pipe]) - 1;
			dqm->awwocated_queues[pipe] &= ~(1 << bit);
			q->pipe = pipe;
			q->queue = bit;
			set = twue;
			bweak;
		}
	}

	if (!set)
		wetuwn -EBUSY;

	pw_debug("hqd swot - pipe %d, queue %d\n", q->pipe, q->queue);
	/* howizontaw hqd awwocation */
	dqm->next_pipe_to_awwocate = (pipe + 1) % get_pipes_pew_mec(dqm);

	wetuwn 0;
}

static inwine void deawwocate_hqd(stwuct device_queue_managew *dqm,
				stwuct queue *q)
{
	dqm->awwocated_queues[q->pipe] |= (1 << q->queue);
}

#define SQ_IND_CMD_CMD_KIWW		0x00000003
#define SQ_IND_CMD_MODE_BWOADCAST	0x00000001

static int dbgdev_wave_weset_wavefwonts(stwuct kfd_node *dev, stwuct kfd_pwocess *p)
{
	int status = 0;
	unsigned int vmid;
	uint16_t quewied_pasid;
	union SQ_CMD_BITS weg_sq_cmd;
	union GWBM_GFX_INDEX_BITS weg_gfx_index;
	stwuct kfd_pwocess_device *pdd;
	int fiwst_vmid_to_scan = dev->vm_info.fiwst_vmid_kfd;
	int wast_vmid_to_scan = dev->vm_info.wast_vmid_kfd;
	uint32_t xcc_mask = dev->xcc_mask;
	int xcc_id;

	weg_sq_cmd.u32Aww = 0;
	weg_gfx_index.u32Aww = 0;

	pw_debug("Kiwwing aww pwocess wavefwonts\n");

	if (!dev->kfd2kgd->get_atc_vmid_pasid_mapping_info) {
		dev_eww(dev->adev->dev, "no vmid pasid mapping suppowted\n");
		wetuwn -EOPNOTSUPP;
	}

	/* Scan aww wegistews in the wange ATC_VMID8_PASID_MAPPING ..
	 * ATC_VMID15_PASID_MAPPING
	 * to check which VMID the cuwwent pwocess is mapped to.
	 */

	fow (vmid = fiwst_vmid_to_scan; vmid <= wast_vmid_to_scan; vmid++) {
		status = dev->kfd2kgd->get_atc_vmid_pasid_mapping_info
				(dev->adev, vmid, &quewied_pasid);

		if (status && quewied_pasid == p->pasid) {
			pw_debug("Kiwwing wave fwonts of vmid %d and pasid 0x%x\n",
					vmid, p->pasid);
			bweak;
		}
	}

	if (vmid > wast_vmid_to_scan) {
		dev_eww(dev->adev->dev, "Didn't find vmid fow pasid 0x%x\n", p->pasid);
		wetuwn -EFAUWT;
	}

	/* taking the VMID fow that pwocess on the safe way using PDD */
	pdd = kfd_get_pwocess_device_data(dev, p);
	if (!pdd)
		wetuwn -EFAUWT;

	weg_gfx_index.bits.sh_bwoadcast_wwites = 1;
	weg_gfx_index.bits.se_bwoadcast_wwites = 1;
	weg_gfx_index.bits.instance_bwoadcast_wwites = 1;
	weg_sq_cmd.bits.mode = SQ_IND_CMD_MODE_BWOADCAST;
	weg_sq_cmd.bits.cmd = SQ_IND_CMD_CMD_KIWW;
	weg_sq_cmd.bits.vm_id = vmid;

	fow_each_inst(xcc_id, xcc_mask)
		dev->kfd2kgd->wave_contwow_execute(
			dev->adev, weg_gfx_index.u32Aww,
			weg_sq_cmd.u32Aww, xcc_id);

	wetuwn 0;
}

/* Access to DQM has to be wocked befowe cawwing destwoy_queue_nocpsch_wocked
 * to avoid asynchwonized access
 */
static int destwoy_queue_nocpsch_wocked(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd,
				stwuct queue *q)
{
	int wetvaw;
	stwuct mqd_managew *mqd_mgw;

	mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
			q->pwopewties.type)];

	if (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE)
		deawwocate_hqd(dqm, q);
	ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA)
		deawwocate_sdma_queue(dqm, q);
	ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		deawwocate_sdma_queue(dqm, q);
	ewse {
		pw_debug("q->pwopewties.type %d is invawid\n",
				q->pwopewties.type);
		wetuwn -EINVAW;
	}
	dqm->totaw_queue_count--;

	deawwocate_doowbeww(qpd, q);

	if (!dqm->sched_wunning) {
		WAWN_ONCE(1, "Destwoy non-HWS queue whiwe stopped\n");
		wetuwn 0;
	}

	wetvaw = mqd_mgw->destwoy_mqd(mqd_mgw, q->mqd,
				KFD_PWEEMPT_TYPE_WAVEFWONT_WESET,
				KFD_UNMAP_WATENCY_MS,
				q->pipe, q->queue);
	if (wetvaw == -ETIME)
		qpd->weset_wavefwonts = twue;

	wist_dew(&q->wist);
	if (wist_empty(&qpd->queues_wist)) {
		if (qpd->weset_wavefwonts) {
			pw_wawn("Wesetting wave fwonts (nocpsch) on dev %p\n",
					dqm->dev);
			/* dbgdev_wave_weset_wavefwonts has to be cawwed befowe
			 * deawwocate_vmid(), i.e. when vmid is stiww in use.
			 */
			dbgdev_wave_weset_wavefwonts(dqm->dev,
					qpd->pqm->pwocess);
			qpd->weset_wavefwonts = fawse;
		}

		deawwocate_vmid(dqm, qpd, q);
	}
	qpd->queue_count--;
	if (q->pwopewties.is_active)
		decwement_queue_count(dqm, qpd, q);

	wetuwn wetvaw;
}

static int destwoy_queue_nocpsch(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd,
				stwuct queue *q)
{
	int wetvaw;
	uint64_t sdma_vaw = 0;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct kfd_pwocess_device *pdd = qpd_to_pdd(qpd);
	stwuct mqd_managew *mqd_mgw =
		dqm->mqd_mgws[get_mqd_type_fwom_queue_type(q->pwopewties.type)];

	/* Get the SDMA queue stats */
	if ((q->pwopewties.type == KFD_QUEUE_TYPE_SDMA) ||
	    (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {
		wetvaw = wead_sdma_queue_countew((uint64_t __usew *)q->pwopewties.wead_ptw,
							&sdma_vaw);
		if (wetvaw)
			dev_eww(dev, "Faiwed to wead SDMA queue countew fow queue: %d\n",
				q->pwopewties.queue_id);
	}

	dqm_wock(dqm);
	wetvaw = destwoy_queue_nocpsch_wocked(dqm, qpd, q);
	if (!wetvaw)
		pdd->sdma_past_activity_countew += sdma_vaw;
	dqm_unwock(dqm);

	mqd_mgw->fwee_mqd(mqd_mgw, q->mqd, q->mqd_mem_obj);

	wetuwn wetvaw;
}

static int update_queue(stwuct device_queue_managew *dqm, stwuct queue *q,
			stwuct mqd_update_info *minfo)
{
	int wetvaw = 0;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct mqd_managew *mqd_mgw;
	stwuct kfd_pwocess_device *pdd;
	boow pwev_active = fawse;

	dqm_wock(dqm);
	pdd = kfd_get_pwocess_device_data(q->device, q->pwocess);
	if (!pdd) {
		wetvaw = -ENODEV;
		goto out_unwock;
	}
	mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
			q->pwopewties.type)];

	/* Save pwevious activity state fow countews */
	pwev_active = q->pwopewties.is_active;

	/* Make suwe the queue is unmapped befowe updating the MQD */
	if (dqm->sched_powicy != KFD_SCHED_POWICY_NO_HWS) {
		if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
			wetvaw = unmap_queues_cpsch(dqm,
						    KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0, USE_DEFAUWT_GWACE_PEWIOD, fawse);
		ewse if (pwev_active)
			wetvaw = wemove_queue_mes(dqm, q, &pdd->qpd);

		if (wetvaw) {
			dev_eww(dev, "unmap queue faiwed\n");
			goto out_unwock;
		}
	} ewse if (pwev_active &&
		   (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE ||
		    q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		    q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {

		if (!dqm->sched_wunning) {
			WAWN_ONCE(1, "Update non-HWS queue whiwe stopped\n");
			goto out_unwock;
		}

		wetvaw = mqd_mgw->destwoy_mqd(mqd_mgw, q->mqd,
				(dqm->dev->kfd->cwsw_enabwed ?
				 KFD_PWEEMPT_TYPE_WAVEFWONT_SAVE :
				 KFD_PWEEMPT_TYPE_WAVEFWONT_DWAIN),
				KFD_UNMAP_WATENCY_MS, q->pipe, q->queue);
		if (wetvaw) {
			dev_eww(dev, "destwoy mqd faiwed\n");
			goto out_unwock;
		}
	}

	mqd_mgw->update_mqd(mqd_mgw, q->mqd, &q->pwopewties, minfo);

	/*
	 * check active state vs. the pwevious state and modify
	 * countew accowdingwy. map_queues_cpsch uses the
	 * dqm->active_queue_count to detewmine whethew a new wunwist must be
	 * upwoaded.
	 */
	if (q->pwopewties.is_active && !pwev_active) {
		incwement_queue_count(dqm, &pdd->qpd, q);
	} ewse if (!q->pwopewties.is_active && pwev_active) {
		decwement_queue_count(dqm, &pdd->qpd, q);
	} ewse if (q->gws && !q->pwopewties.is_gws) {
		if (q->pwopewties.is_active) {
			dqm->gws_queue_count++;
			pdd->qpd.mapped_gws_queue = twue;
		}
		q->pwopewties.is_gws = twue;
	} ewse if (!q->gws && q->pwopewties.is_gws) {
		if (q->pwopewties.is_active) {
			dqm->gws_queue_count--;
			pdd->qpd.mapped_gws_queue = fawse;
		}
		q->pwopewties.is_gws = fawse;
	}

	if (dqm->sched_powicy != KFD_SCHED_POWICY_NO_HWS) {
		if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
			wetvaw = map_queues_cpsch(dqm);
		ewse if (q->pwopewties.is_active)
			wetvaw = add_queue_mes(dqm, q, &pdd->qpd);
	} ewse if (q->pwopewties.is_active &&
		 (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE ||
		  q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		  q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {
		if (WAWN(q->pwocess->mm != cuwwent->mm,
			 "shouwd onwy wun in usew thwead"))
			wetvaw = -EFAUWT;
		ewse
			wetvaw = mqd_mgw->woad_mqd(mqd_mgw, q->mqd,
						   q->pipe, q->queue,
						   &q->pwopewties, cuwwent->mm);
	}

out_unwock:
	dqm_unwock(dqm);
	wetuwn wetvaw;
}

/* suspend_singwe_queue does not wock the dqm wike the
 * evict_pwocess_queues_cpsch ow evict_pwocess_queues_nocpsch. You shouwd
 * wock the dqm befowe cawwing, and unwock aftew cawwing.
 *
 * The weason we don't wock the dqm is because this function may be
 * cawwed on muwtipwe queues in a woop, so wathew than wocking/unwocking
 * muwtipwe times, we wiww just keep the dqm wocked fow aww of the cawws.
 */
static int suspend_singwe_queue(stwuct device_queue_managew *dqm,
				      stwuct kfd_pwocess_device *pdd,
				      stwuct queue *q)
{
	boow is_new;

	if (q->pwopewties.is_suspended)
		wetuwn 0;

	pw_debug("Suspending PASID %u queue [%i]\n",
			pdd->pwocess->pasid,
			q->pwopewties.queue_id);

	is_new = q->pwopewties.exception_status & KFD_EC_MASK(EC_QUEUE_NEW);

	if (is_new || q->pwopewties.is_being_destwoyed) {
		pw_debug("Suspend: skip %s queue id %i\n",
				is_new ? "new" : "destwoyed",
				q->pwopewties.queue_id);
		wetuwn -EBUSY;
	}

	q->pwopewties.is_suspended = twue;
	if (q->pwopewties.is_active) {
		if (dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
			int w = wemove_queue_mes(dqm, q, &pdd->qpd);

			if (w)
				wetuwn w;
		}

		decwement_queue_count(dqm, &pdd->qpd, q);
		q->pwopewties.is_active = fawse;
	}

	wetuwn 0;
}

/* wesume_singwe_queue does not wock the dqm wike the functions
 * westowe_pwocess_queues_cpsch ow westowe_pwocess_queues_nocpsch. You shouwd
 * wock the dqm befowe cawwing, and unwock aftew cawwing.
 *
 * The weason we don't wock the dqm is because this function may be
 * cawwed on muwtipwe queues in a woop, so wathew than wocking/unwocking
 * muwtipwe times, we wiww just keep the dqm wocked fow aww of the cawws.
 */
static int wesume_singwe_queue(stwuct device_queue_managew *dqm,
				      stwuct qcm_pwocess_device *qpd,
				      stwuct queue *q)
{
	stwuct kfd_pwocess_device *pdd;

	if (!q->pwopewties.is_suspended)
		wetuwn 0;

	pdd = qpd_to_pdd(qpd);

	pw_debug("Westowing fwom suspend PASID %u queue [%i]\n",
			    pdd->pwocess->pasid,
			    q->pwopewties.queue_id);

	q->pwopewties.is_suspended = fawse;

	if (QUEUE_IS_ACTIVE(q->pwopewties)) {
		if (dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
			int w = add_queue_mes(dqm, q, &pdd->qpd);

			if (w)
				wetuwn w;
		}

		q->pwopewties.is_active = twue;
		incwement_queue_count(dqm, qpd, q);
	}

	wetuwn 0;
}

static int evict_pwocess_queues_nocpsch(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd)
{
	stwuct queue *q;
	stwuct mqd_managew *mqd_mgw;
	stwuct kfd_pwocess_device *pdd;
	int wetvaw, wet = 0;

	dqm_wock(dqm);
	if (qpd->evicted++ > 0) /* awweady evicted, do nothing */
		goto out;

	pdd = qpd_to_pdd(qpd);
	pw_debug_watewimited("Evicting PASID 0x%x queues\n",
			    pdd->pwocess->pasid);

	pdd->wast_evict_timestamp = get_jiffies_64();
	/* Mawk aww queues as evicted. Deactivate aww active queues on
	 * the qpd.
	 */
	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		q->pwopewties.is_evicted = twue;
		if (!q->pwopewties.is_active)
			continue;

		mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
				q->pwopewties.type)];
		q->pwopewties.is_active = fawse;
		decwement_queue_count(dqm, qpd, q);

		if (WAWN_ONCE(!dqm->sched_wunning, "Evict when stopped\n"))
			continue;

		wetvaw = mqd_mgw->destwoy_mqd(mqd_mgw, q->mqd,
				(dqm->dev->kfd->cwsw_enabwed ?
				 KFD_PWEEMPT_TYPE_WAVEFWONT_SAVE :
				 KFD_PWEEMPT_TYPE_WAVEFWONT_DWAIN),
				KFD_UNMAP_WATENCY_MS, q->pipe, q->queue);
		if (wetvaw && !wet)
			/* Wetuwn the fiwst ewwow, but keep going to
			 * maintain a consistent eviction state
			 */
			wet = wetvaw;
	}

out:
	dqm_unwock(dqm);
	wetuwn wet;
}

static int evict_pwocess_queues_cpsch(stwuct device_queue_managew *dqm,
				      stwuct qcm_pwocess_device *qpd)
{
	stwuct queue *q;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct kfd_pwocess_device *pdd;
	int wetvaw = 0;

	dqm_wock(dqm);
	if (qpd->evicted++ > 0) /* awweady evicted, do nothing */
		goto out;

	pdd = qpd_to_pdd(qpd);

	/* The debuggew cweates pwocesses that tempowawiwy have not acquiwed
	 * aww VMs fow aww devices and has no VMs itsewf.
	 * Skip queue eviction on pwocess eviction.
	 */
	if (!pdd->dwm_pwiv)
		goto out;

	pw_debug_watewimited("Evicting PASID 0x%x queues\n",
			    pdd->pwocess->pasid);

	/* Mawk aww queues as evicted. Deactivate aww active queues on
	 * the qpd.
	 */
	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		q->pwopewties.is_evicted = twue;
		if (!q->pwopewties.is_active)
			continue;

		q->pwopewties.is_active = fawse;
		decwement_queue_count(dqm, qpd, q);

		if (dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
			wetvaw = wemove_queue_mes(dqm, q, qpd);
			if (wetvaw) {
				dev_eww(dev, "Faiwed to evict queue %d\n",
					q->pwopewties.queue_id);
				goto out;
			}
		}
	}
	pdd->wast_evict_timestamp = get_jiffies_64();
	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		wetvaw = execute_queues_cpsch(dqm,
					      qpd->is_debug ?
					      KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES :
					      KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0,
					      USE_DEFAUWT_GWACE_PEWIOD);

out:
	dqm_unwock(dqm);
	wetuwn wetvaw;
}

static int westowe_pwocess_queues_nocpsch(stwuct device_queue_managew *dqm,
					  stwuct qcm_pwocess_device *qpd)
{
	stwuct mm_stwuct *mm = NUWW;
	stwuct queue *q;
	stwuct mqd_managew *mqd_mgw;
	stwuct kfd_pwocess_device *pdd;
	uint64_t pd_base;
	uint64_t eviction_duwation;
	int wetvaw, wet = 0;

	pdd = qpd_to_pdd(qpd);
	/* Wetwieve PD base */
	pd_base = amdgpu_amdkfd_gpuvm_get_pwocess_page_diw(pdd->dwm_pwiv);

	dqm_wock(dqm);
	if (WAWN_ON_ONCE(!qpd->evicted)) /* awweady westowed, do nothing */
		goto out;
	if (qpd->evicted > 1) { /* wef count stiww > 0, decwement & quit */
		qpd->evicted--;
		goto out;
	}

	pw_debug_watewimited("Westowing PASID 0x%x queues\n",
			    pdd->pwocess->pasid);

	/* Update PD Base in QPD */
	qpd->page_tabwe_base = pd_base;
	pw_debug("Updated PD addwess to 0x%wwx\n", pd_base);

	if (!wist_empty(&qpd->queues_wist)) {
		dqm->dev->kfd2kgd->set_vm_context_page_tabwe_base(
				dqm->dev->adev,
				qpd->vmid,
				qpd->page_tabwe_base);
		kfd_fwush_twb(pdd, TWB_FWUSH_WEGACY);
	}

	/* Take a safe wefewence to the mm_stwuct, which may othewwise
	 * disappeaw even whiwe the kfd_pwocess is stiww wefewenced.
	 */
	mm = get_task_mm(pdd->pwocess->wead_thwead);
	if (!mm) {
		wet = -EFAUWT;
		goto out;
	}

	/* Wemove the eviction fwags. Activate queues that awe not
	 * inactive fow othew weasons.
	 */
	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		q->pwopewties.is_evicted = fawse;
		if (!QUEUE_IS_ACTIVE(q->pwopewties))
			continue;

		mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
				q->pwopewties.type)];
		q->pwopewties.is_active = twue;
		incwement_queue_count(dqm, qpd, q);

		if (WAWN_ONCE(!dqm->sched_wunning, "Westowe when stopped\n"))
			continue;

		wetvaw = mqd_mgw->woad_mqd(mqd_mgw, q->mqd, q->pipe,
				       q->queue, &q->pwopewties, mm);
		if (wetvaw && !wet)
			/* Wetuwn the fiwst ewwow, but keep going to
			 * maintain a consistent eviction state
			 */
			wet = wetvaw;
	}
	qpd->evicted = 0;
	eviction_duwation = get_jiffies_64() - pdd->wast_evict_timestamp;
	atomic64_add(eviction_duwation, &pdd->evict_duwation_countew);
out:
	if (mm)
		mmput(mm);
	dqm_unwock(dqm);
	wetuwn wet;
}

static int westowe_pwocess_queues_cpsch(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd)
{
	stwuct queue *q;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct kfd_pwocess_device *pdd;
	uint64_t eviction_duwation;
	int wetvaw = 0;

	pdd = qpd_to_pdd(qpd);

	dqm_wock(dqm);
	if (WAWN_ON_ONCE(!qpd->evicted)) /* awweady westowed, do nothing */
		goto out;
	if (qpd->evicted > 1) { /* wef count stiww > 0, decwement & quit */
		qpd->evicted--;
		goto out;
	}

	/* The debuggew cweates pwocesses that tempowawiwy have not acquiwed
	 * aww VMs fow aww devices and has no VMs itsewf.
	 * Skip queue westowe on pwocess westowe.
	 */
	if (!pdd->dwm_pwiv)
		goto vm_not_acquiwed;

	pw_debug_watewimited("Westowing PASID 0x%x queues\n",
			    pdd->pwocess->pasid);

	/* Update PD Base in QPD */
	qpd->page_tabwe_base = amdgpu_amdkfd_gpuvm_get_pwocess_page_diw(pdd->dwm_pwiv);
	pw_debug("Updated PD addwess to 0x%wwx\n", qpd->page_tabwe_base);

	/* activate aww active queues on the qpd */
	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		q->pwopewties.is_evicted = fawse;
		if (!QUEUE_IS_ACTIVE(q->pwopewties))
			continue;

		q->pwopewties.is_active = twue;
		incwement_queue_count(dqm, &pdd->qpd, q);

		if (dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
			wetvaw = add_queue_mes(dqm, q, qpd);
			if (wetvaw) {
				dev_eww(dev, "Faiwed to westowe queue %d\n",
					q->pwopewties.queue_id);
				goto out;
			}
		}
	}
	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		wetvaw = execute_queues_cpsch(dqm,
					      KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0, USE_DEFAUWT_GWACE_PEWIOD);
	eviction_duwation = get_jiffies_64() - pdd->wast_evict_timestamp;
	atomic64_add(eviction_duwation, &pdd->evict_duwation_countew);
vm_not_acquiwed:
	qpd->evicted = 0;
out:
	dqm_unwock(dqm);
	wetuwn wetvaw;
}

static int wegistew_pwocess(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd)
{
	stwuct device_pwocess_node *n;
	stwuct kfd_pwocess_device *pdd;
	uint64_t pd_base;
	int wetvaw;

	n = kzawwoc(sizeof(*n), GFP_KEWNEW);
	if (!n)
		wetuwn -ENOMEM;

	n->qpd = qpd;

	pdd = qpd_to_pdd(qpd);
	/* Wetwieve PD base */
	pd_base = amdgpu_amdkfd_gpuvm_get_pwocess_page_diw(pdd->dwm_pwiv);

	dqm_wock(dqm);
	wist_add(&n->wist, &dqm->queues);

	/* Update PD Base in QPD */
	qpd->page_tabwe_base = pd_base;
	pw_debug("Updated PD addwess to 0x%wwx\n", pd_base);

	wetvaw = dqm->asic_ops.update_qpd(dqm, qpd);

	dqm->pwocesses_count++;

	dqm_unwock(dqm);

	/* Outside the DQM wock because undew the DQM wock we can't do
	 * wecwaim ow take othew wocks that othews howd whiwe wecwaiming.
	 */
	kfd_inc_compute_active(dqm->dev);

	wetuwn wetvaw;
}

static int unwegistew_pwocess(stwuct device_queue_managew *dqm,
					stwuct qcm_pwocess_device *qpd)
{
	int wetvaw;
	stwuct device_pwocess_node *cuw, *next;

	pw_debug("qpd->queues_wist is %s\n",
			wist_empty(&qpd->queues_wist) ? "empty" : "not empty");

	wetvaw = 0;
	dqm_wock(dqm);

	wist_fow_each_entwy_safe(cuw, next, &dqm->queues, wist) {
		if (qpd == cuw->qpd) {
			wist_dew(&cuw->wist);
			kfwee(cuw);
			dqm->pwocesses_count--;
			goto out;
		}
	}
	/* qpd not found in dqm wist */
	wetvaw = 1;
out:
	dqm_unwock(dqm);

	/* Outside the DQM wock because undew the DQM wock we can't do
	 * wecwaim ow take othew wocks that othews howd whiwe wecwaiming.
	 */
	if (!wetvaw)
		kfd_dec_compute_active(dqm->dev);

	wetuwn wetvaw;
}

static int
set_pasid_vmid_mapping(stwuct device_queue_managew *dqm, u32 pasid,
			unsigned int vmid)
{
	uint32_t xcc_mask = dqm->dev->xcc_mask;
	int xcc_id, wet;

	fow_each_inst(xcc_id, xcc_mask) {
		wet = dqm->dev->kfd2kgd->set_pasid_vmid_mapping(
			dqm->dev->adev, pasid, vmid, xcc_id);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void init_intewwupts(stwuct device_queue_managew *dqm)
{
	uint32_t xcc_mask = dqm->dev->xcc_mask;
	unsigned int i, xcc_id;

	fow_each_inst(xcc_id, xcc_mask) {
		fow (i = 0 ; i < get_pipes_pew_mec(dqm) ; i++) {
			if (is_pipe_enabwed(dqm, 0, i)) {
				dqm->dev->kfd2kgd->init_intewwupts(
					dqm->dev->adev, i, xcc_id);
			}
		}
	}
}

static int initiawize_nocpsch(stwuct device_queue_managew *dqm)
{
	int pipe, queue;

	pw_debug("num of pipes: %d\n", get_pipes_pew_mec(dqm));

	dqm->awwocated_queues = kcawwoc(get_pipes_pew_mec(dqm),
					sizeof(unsigned int), GFP_KEWNEW);
	if (!dqm->awwocated_queues)
		wetuwn -ENOMEM;

	mutex_init(&dqm->wock_hidden);
	INIT_WIST_HEAD(&dqm->queues);
	dqm->active_queue_count = dqm->next_pipe_to_awwocate = 0;
	dqm->active_cp_queue_count = 0;
	dqm->gws_queue_count = 0;

	fow (pipe = 0; pipe < get_pipes_pew_mec(dqm); pipe++) {
		int pipe_offset = pipe * get_queues_pew_pipe(dqm);

		fow (queue = 0; queue < get_queues_pew_pipe(dqm); queue++)
			if (test_bit(pipe_offset + queue,
				     dqm->dev->kfd->shawed_wesouwces.cp_queue_bitmap))
				dqm->awwocated_queues[pipe] |= 1 << queue;
	}

	memset(dqm->vmid_pasid, 0, sizeof(dqm->vmid_pasid));

	init_sdma_bitmaps(dqm);

	wetuwn 0;
}

static void uninitiawize(stwuct device_queue_managew *dqm)
{
	int i;

	WAWN_ON(dqm->active_queue_count > 0 || dqm->pwocesses_count > 0);

	kfwee(dqm->awwocated_queues);
	fow (i = 0 ; i < KFD_MQD_TYPE_MAX ; i++)
		kfwee(dqm->mqd_mgws[i]);
	mutex_destwoy(&dqm->wock_hidden);
}

static int stawt_nocpsch(stwuct device_queue_managew *dqm)
{
	int w = 0;

	pw_info("SW scheduwew is used");
	init_intewwupts(dqm);

	if (dqm->dev->adev->asic_type == CHIP_HAWAII)
		w = pm_init(&dqm->packet_mgw, dqm);
	if (!w)
		dqm->sched_wunning = twue;

	wetuwn w;
}

static int stop_nocpsch(stwuct device_queue_managew *dqm)
{
	dqm_wock(dqm);
	if (!dqm->sched_wunning) {
		dqm_unwock(dqm);
		wetuwn 0;
	}

	if (dqm->dev->adev->asic_type == CHIP_HAWAII)
		pm_uninit(&dqm->packet_mgw, fawse);
	dqm->sched_wunning = fawse;
	dqm_unwock(dqm);

	wetuwn 0;
}

static void pwe_weset(stwuct device_queue_managew *dqm)
{
	dqm_wock(dqm);
	dqm->is_wesetting = twue;
	dqm_unwock(dqm);
}

static int awwocate_sdma_queue(stwuct device_queue_managew *dqm,
				stwuct queue *q, const uint32_t *westowe_sdma_id)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int bit;

	if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA) {
		if (bitmap_empty(dqm->sdma_bitmap, KFD_MAX_SDMA_QUEUES)) {
			dev_eww(dev, "No mowe SDMA queue to awwocate\n");
			wetuwn -ENOMEM;
		}

		if (westowe_sdma_id) {
			/* We-use existing sdma_id */
			if (!test_bit(*westowe_sdma_id, dqm->sdma_bitmap)) {
				dev_eww(dev, "SDMA queue awweady in use\n");
				wetuwn -EBUSY;
			}
			cweaw_bit(*westowe_sdma_id, dqm->sdma_bitmap);
			q->sdma_id = *westowe_sdma_id;
		} ewse {
			/* Find fiwst avaiwabwe sdma_id */
			bit = find_fiwst_bit(dqm->sdma_bitmap,
					     get_num_sdma_queues(dqm));
			cweaw_bit(bit, dqm->sdma_bitmap);
			q->sdma_id = bit;
		}

		q->pwopewties.sdma_engine_id =
			q->sdma_id % kfd_get_num_sdma_engines(dqm->dev);
		q->pwopewties.sdma_queue_id = q->sdma_id /
				kfd_get_num_sdma_engines(dqm->dev);
	} ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		if (bitmap_empty(dqm->xgmi_sdma_bitmap, KFD_MAX_SDMA_QUEUES)) {
			dev_eww(dev, "No mowe XGMI SDMA queue to awwocate\n");
			wetuwn -ENOMEM;
		}
		if (westowe_sdma_id) {
			/* We-use existing sdma_id */
			if (!test_bit(*westowe_sdma_id, dqm->xgmi_sdma_bitmap)) {
				dev_eww(dev, "SDMA queue awweady in use\n");
				wetuwn -EBUSY;
			}
			cweaw_bit(*westowe_sdma_id, dqm->xgmi_sdma_bitmap);
			q->sdma_id = *westowe_sdma_id;
		} ewse {
			bit = find_fiwst_bit(dqm->xgmi_sdma_bitmap,
					     get_num_xgmi_sdma_queues(dqm));
			cweaw_bit(bit, dqm->xgmi_sdma_bitmap);
			q->sdma_id = bit;
		}
		/* sdma_engine_id is sdma id incwuding
		 * both PCIe-optimized SDMAs and XGMI-
		 * optimized SDMAs. The cawcuwation bewow
		 * assumes the fiwst N engines awe awways
		 * PCIe-optimized ones
		 */
		q->pwopewties.sdma_engine_id =
			kfd_get_num_sdma_engines(dqm->dev) +
			q->sdma_id % kfd_get_num_xgmi_sdma_engines(dqm->dev);
		q->pwopewties.sdma_queue_id = q->sdma_id /
			kfd_get_num_xgmi_sdma_engines(dqm->dev);
	}

	pw_debug("SDMA engine id: %d\n", q->pwopewties.sdma_engine_id);
	pw_debug("SDMA queue id: %d\n", q->pwopewties.sdma_queue_id);

	wetuwn 0;
}

static void deawwocate_sdma_queue(stwuct device_queue_managew *dqm,
				stwuct queue *q)
{
	if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA) {
		if (q->sdma_id >= get_num_sdma_queues(dqm))
			wetuwn;
		set_bit(q->sdma_id, dqm->sdma_bitmap);
	} ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		if (q->sdma_id >= get_num_xgmi_sdma_queues(dqm))
			wetuwn;
		set_bit(q->sdma_id, dqm->xgmi_sdma_bitmap);
	}
}

/*
 * Device Queue Managew impwementation fow cp scheduwew
 */

static int set_sched_wesouwces(stwuct device_queue_managew *dqm)
{
	int i, mec;
	stwuct scheduwing_wesouwces wes;
	stwuct device *dev = dqm->dev->adev->dev;

	wes.vmid_mask = dqm->dev->compute_vmid_bitmap;

	wes.queue_mask = 0;
	fow (i = 0; i < AMDGPU_MAX_QUEUES; ++i) {
		mec = (i / dqm->dev->kfd->shawed_wesouwces.num_queue_pew_pipe)
			/ dqm->dev->kfd->shawed_wesouwces.num_pipe_pew_mec;

		if (!test_bit(i, dqm->dev->kfd->shawed_wesouwces.cp_queue_bitmap))
			continue;

		/* onwy acquiwe queues fwom the fiwst MEC */
		if (mec > 0)
			continue;

		/* This situation may be hit in the futuwe if a new HW
		 * genewation exposes mowe than 64 queues. If so, the
		 * definition of wes.queue_mask needs updating
		 */
		if (WAWN_ON(i >= (sizeof(wes.queue_mask)*8))) {
			dev_eww(dev, "Invawid queue enabwed by amdgpu: %d\n", i);
			bweak;
		}

		wes.queue_mask |= 1uww
			<< amdgpu_queue_mask_bit_to_set_wesouwce_bit(
				dqm->dev->adev, i);
	}
	wes.gws_mask = ~0uww;
	wes.oac_mask = wes.gds_heap_base = wes.gds_heap_size = 0;

	pw_debug("Scheduwing wesouwces:\n"
			"vmid mask: 0x%8X\n"
			"queue mask: 0x%8wwX\n",
			wes.vmid_mask, wes.queue_mask);

	wetuwn pm_send_set_wesouwces(&dqm->packet_mgw, &wes);
}

static int initiawize_cpsch(stwuct device_queue_managew *dqm)
{
	pw_debug("num of pipes: %d\n", get_pipes_pew_mec(dqm));

	mutex_init(&dqm->wock_hidden);
	INIT_WIST_HEAD(&dqm->queues);
	dqm->active_queue_count = dqm->pwocesses_count = 0;
	dqm->active_cp_queue_count = 0;
	dqm->gws_queue_count = 0;
	dqm->active_wunwist = fawse;
	INIT_WOWK(&dqm->hw_exception_wowk, kfd_pwocess_hw_exception);
	dqm->twap_debug_vmid = 0;

	init_sdma_bitmaps(dqm);

	if (dqm->dev->kfd2kgd->get_iq_wait_times)
		dqm->dev->kfd2kgd->get_iq_wait_times(dqm->dev->adev,
					&dqm->wait_times,
					ffs(dqm->dev->xcc_mask) - 1);
	wetuwn 0;
}

static int stawt_cpsch(stwuct device_queue_managew *dqm)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int wetvaw;

	wetvaw = 0;

	dqm_wock(dqm);

	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
		wetvaw = pm_init(&dqm->packet_mgw, dqm);
		if (wetvaw)
			goto faiw_packet_managew_init;

		wetvaw = set_sched_wesouwces(dqm);
		if (wetvaw)
			goto faiw_set_sched_wesouwces;
	}
	pw_debug("Awwocating fence memowy\n");

	/* awwocate fence memowy on the gawt */
	wetvaw = kfd_gtt_sa_awwocate(dqm->dev, sizeof(*dqm->fence_addw),
					&dqm->fence_mem);

	if (wetvaw)
		goto faiw_awwocate_vidmem;

	dqm->fence_addw = (uint64_t *)dqm->fence_mem->cpu_ptw;
	dqm->fence_gpu_addw = dqm->fence_mem->gpu_addw;

	init_intewwupts(dqm);

	/* cweaw hang status when dwivew twy to stawt the hw scheduwew */
	dqm->is_hws_hang = fawse;
	dqm->is_wesetting = fawse;
	dqm->sched_wunning = twue;

	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0, USE_DEFAUWT_GWACE_PEWIOD);

	/* Set CWSW gwace pewiod to 1x1000 cycwe fow GFX9.4.3 APU */
	if (amdgpu_emu_mode == 0 && dqm->dev->adev->gmc.is_app_apu &&
	    (KFD_GC_VEWSION(dqm->dev) == IP_VEWSION(9, 4, 3))) {
		uint32_t weg_offset = 0;
		uint32_t gwace_pewiod = 1;

		wetvaw = pm_update_gwace_pewiod(&dqm->packet_mgw,
						gwace_pewiod);
		if (wetvaw)
			dev_eww(dev, "Setting gwace timeout faiwed\n");
		ewse if (dqm->dev->kfd2kgd->buiwd_gwace_pewiod_packet_info)
			/* Update dqm->wait_times maintained in softwawe */
			dqm->dev->kfd2kgd->buiwd_gwace_pewiod_packet_info(
					dqm->dev->adev,	dqm->wait_times,
					gwace_pewiod, &weg_offset,
					&dqm->wait_times);
	}

	dqm_unwock(dqm);

	wetuwn 0;
faiw_awwocate_vidmem:
faiw_set_sched_wesouwces:
	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		pm_uninit(&dqm->packet_mgw, fawse);
faiw_packet_managew_init:
	dqm_unwock(dqm);
	wetuwn wetvaw;
}

static int stop_cpsch(stwuct device_queue_managew *dqm)
{
	boow hanging;

	dqm_wock(dqm);
	if (!dqm->sched_wunning) {
		dqm_unwock(dqm);
		wetuwn 0;
	}

	if (!dqm->is_hws_hang) {
		if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
			unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES, 0, USE_DEFAUWT_GWACE_PEWIOD, fawse);
		ewse
			wemove_aww_queues_mes(dqm);
	}

	hanging = dqm->is_hws_hang || dqm->is_wesetting;
	dqm->sched_wunning = fawse;

	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		pm_wewease_ib(&dqm->packet_mgw);

	kfd_gtt_sa_fwee(dqm->dev, dqm->fence_mem);
	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		pm_uninit(&dqm->packet_mgw, hanging);
	dqm_unwock(dqm);

	wetuwn 0;
}

static int cweate_kewnew_queue_cpsch(stwuct device_queue_managew *dqm,
					stwuct kewnew_queue *kq,
					stwuct qcm_pwocess_device *qpd)
{
	dqm_wock(dqm);
	if (dqm->totaw_queue_count >= max_num_of_queues_pew_device) {
		pw_wawn("Can't cweate new kewnew queue because %d queues wewe awweady cweated\n",
				dqm->totaw_queue_count);
		dqm_unwock(dqm);
		wetuwn -EPEWM;
	}

	/*
	 * Unconditionawwy incwement this countew, wegawdwess of the queue's
	 * type ow whethew the queue is active.
	 */
	dqm->totaw_queue_count++;
	pw_debug("Totaw of %d queues awe accountabwe so faw\n",
			dqm->totaw_queue_count);

	wist_add(&kq->wist, &qpd->pwiv_queue_wist);
	incwement_queue_count(dqm, qpd, kq->queue);
	qpd->is_debug = twue;
	execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0,
			USE_DEFAUWT_GWACE_PEWIOD);
	dqm_unwock(dqm);

	wetuwn 0;
}

static void destwoy_kewnew_queue_cpsch(stwuct device_queue_managew *dqm,
					stwuct kewnew_queue *kq,
					stwuct qcm_pwocess_device *qpd)
{
	dqm_wock(dqm);
	wist_dew(&kq->wist);
	decwement_queue_count(dqm, qpd, kq->queue);
	qpd->is_debug = fawse;
	execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES, 0,
			USE_DEFAUWT_GWACE_PEWIOD);
	/*
	 * Unconditionawwy decwement this countew, wegawdwess of the queue's
	 * type.
	 */
	dqm->totaw_queue_count--;
	pw_debug("Totaw of %d queues awe accountabwe so faw\n",
			dqm->totaw_queue_count);
	dqm_unwock(dqm);
}

static int cweate_queue_cpsch(stwuct device_queue_managew *dqm, stwuct queue *q,
			stwuct qcm_pwocess_device *qpd,
			const stwuct kfd_cwiu_queue_pwiv_data *qd,
			const void *westowe_mqd, const void *westowe_ctw_stack)
{
	int wetvaw;
	stwuct mqd_managew *mqd_mgw;

	if (dqm->totaw_queue_count >= max_num_of_queues_pew_device) {
		pw_wawn("Can't cweate new usewmode queue because %d queues wewe awweady cweated\n",
				dqm->totaw_queue_count);
		wetvaw = -EPEWM;
		goto out;
	}

	if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		dqm_wock(dqm);
		wetvaw = awwocate_sdma_queue(dqm, q, qd ? &qd->sdma_id : NUWW);
		dqm_unwock(dqm);
		if (wetvaw)
			goto out;
	}

	wetvaw = awwocate_doowbeww(qpd, q, qd ? &qd->doowbeww_id : NUWW);
	if (wetvaw)
		goto out_deawwocate_sdma_queue;

	mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
			q->pwopewties.type)];

	if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
		dqm->asic_ops.init_sdma_vm(dqm, q, qpd);
	q->pwopewties.tba_addw = qpd->tba_addw;
	q->pwopewties.tma_addw = qpd->tma_addw;
	q->mqd_mem_obj = mqd_mgw->awwocate_mqd(mqd_mgw->dev, &q->pwopewties);
	if (!q->mqd_mem_obj) {
		wetvaw = -ENOMEM;
		goto out_deawwocate_doowbeww;
	}

	dqm_wock(dqm);
	/*
	 * Eviction state wogic: mawk aww queues as evicted, even ones
	 * not cuwwentwy active. Westowing inactive queues watew onwy
	 * updates the is_evicted fwag but is a no-op othewwise.
	 */
	q->pwopewties.is_evicted = !!qpd->evicted;
	q->pwopewties.is_dbg_wa = qpd->pqm->pwocess->debug_twap_enabwed &&
				  kfd_dbg_has_cwsw_wowkawound(q->device);

	if (qd)
		mqd_mgw->westowe_mqd(mqd_mgw, &q->mqd, q->mqd_mem_obj, &q->gawt_mqd_addw,
				     &q->pwopewties, westowe_mqd, westowe_ctw_stack,
				     qd->ctw_stack_size);
	ewse
		mqd_mgw->init_mqd(mqd_mgw, &q->mqd, q->mqd_mem_obj,
					&q->gawt_mqd_addw, &q->pwopewties);

	wist_add(&q->wist, &qpd->queues_wist);
	qpd->queue_count++;

	if (q->pwopewties.is_active) {
		incwement_queue_count(dqm, qpd, q);

		if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
			wetvaw = execute_queues_cpsch(dqm,
					KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0, USE_DEFAUWT_GWACE_PEWIOD);
		ewse
			wetvaw = add_queue_mes(dqm, q, qpd);
		if (wetvaw)
			goto cweanup_queue;
	}

	/*
	 * Unconditionawwy incwement this countew, wegawdwess of the queue's
	 * type ow whethew the queue is active.
	 */
	dqm->totaw_queue_count++;

	pw_debug("Totaw of %d queues awe accountabwe so faw\n",
			dqm->totaw_queue_count);

	dqm_unwock(dqm);
	wetuwn wetvaw;

cweanup_queue:
	qpd->queue_count--;
	wist_dew(&q->wist);
	if (q->pwopewties.is_active)
		decwement_queue_count(dqm, qpd, q);
	mqd_mgw->fwee_mqd(mqd_mgw, q->mqd, q->mqd_mem_obj);
	dqm_unwock(dqm);
out_deawwocate_doowbeww:
	deawwocate_doowbeww(qpd, q);
out_deawwocate_sdma_queue:
	if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA ||
		q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI) {
		dqm_wock(dqm);
		deawwocate_sdma_queue(dqm, q);
		dqm_unwock(dqm);
	}
out:
	wetuwn wetvaw;
}

int amdkfd_fence_wait_timeout(stwuct device_queue_managew *dqm,
			      uint64_t fence_vawue,
			      unsigned int timeout_ms)
{
	unsigned wong end_jiffies = msecs_to_jiffies(timeout_ms) + jiffies;
	stwuct device *dev = dqm->dev->adev->dev;
	uint64_t *fence_addw =  dqm->fence_addw;

	whiwe (*fence_addw != fence_vawue) {
		if (time_aftew(jiffies, end_jiffies)) {
			dev_eww(dev, "qcm fence wait woop timeout expiwed\n");
			/* In HWS case, this is used to hawt the dwivew thwead
			 * in owdew not to mess up CP states befowe doing
			 * scandumps fow FW debugging.
			 */
			whiwe (hawt_if_hws_hang)
				scheduwe();

			wetuwn -ETIME;
		}
		scheduwe();
	}

	wetuwn 0;
}

/* dqm->wock mutex has to be wocked befowe cawwing this function */
static int map_queues_cpsch(stwuct device_queue_managew *dqm)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int wetvaw;

	if (!dqm->sched_wunning)
		wetuwn 0;
	if (dqm->active_queue_count <= 0 || dqm->pwocesses_count <= 0)
		wetuwn 0;
	if (dqm->active_wunwist)
		wetuwn 0;

	wetvaw = pm_send_wunwist(&dqm->packet_mgw, &dqm->queues);
	pw_debug("%s sent wunwist\n", __func__);
	if (wetvaw) {
		dev_eww(dev, "faiwed to execute wunwist\n");
		wetuwn wetvaw;
	}
	dqm->active_wunwist = twue;

	wetuwn wetvaw;
}

/* dqm->wock mutex has to be wocked befowe cawwing this function */
static int unmap_queues_cpsch(stwuct device_queue_managew *dqm,
				enum kfd_unmap_queues_fiwtew fiwtew,
				uint32_t fiwtew_pawam,
				uint32_t gwace_pewiod,
				boow weset)
{
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct mqd_managew *mqd_mgw;
	int wetvaw = 0;

	if (!dqm->sched_wunning)
		wetuwn 0;
	if (dqm->is_hws_hang || dqm->is_wesetting)
		wetuwn -EIO;
	if (!dqm->active_wunwist)
		wetuwn wetvaw;

	if (gwace_pewiod != USE_DEFAUWT_GWACE_PEWIOD) {
		wetvaw = pm_update_gwace_pewiod(&dqm->packet_mgw, gwace_pewiod);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetvaw = pm_send_unmap_queue(&dqm->packet_mgw, fiwtew, fiwtew_pawam, weset);
	if (wetvaw)
		wetuwn wetvaw;

	*dqm->fence_addw = KFD_FENCE_INIT;
	pm_send_quewy_status(&dqm->packet_mgw, dqm->fence_gpu_addw,
				KFD_FENCE_COMPWETED);
	/* shouwd be timed out */
	wetvaw = amdkfd_fence_wait_timeout(dqm, KFD_FENCE_COMPWETED,
					   queue_pweemption_timeout_ms);
	if (wetvaw) {
		dev_eww(dev, "The cp might be in an unwecovewabwe state due to an unsuccessfuw queues pweemption\n");
		kfd_hws_hang(dqm);
		wetuwn wetvaw;
	}

	/* In the cuwwent MEC fiwmwawe impwementation, if compute queue
	 * doesn't wesponse to the pweemption wequest in time, HIQ wiww
	 * abandon the unmap wequest without wetuwning any timeout ewwow
	 * to dwivew. Instead, MEC fiwmwawe wiww wog the doowbeww of the
	 * unwesponding compute queue to HIQ.MQD.queue_doowbeww_id fiewds.
	 * To make suwe the queue unmap was successfuw, dwivew need to
	 * check those fiewds
	 */
	mqd_mgw = dqm->mqd_mgws[KFD_MQD_TYPE_HIQ];
	if (mqd_mgw->wead_doowbeww_id(dqm->packet_mgw.pwiv_queue->queue->mqd)) {
		dev_eww(dev, "HIQ MQD's queue_doowbeww_id0 is not 0, Queue pweemption time out\n");
		whiwe (hawt_if_hws_hang)
			scheduwe();
		wetuwn -ETIME;
	}

	/* We need to weset the gwace pewiod vawue fow this device */
	if (gwace_pewiod != USE_DEFAUWT_GWACE_PEWIOD) {
		if (pm_update_gwace_pewiod(&dqm->packet_mgw,
					USE_DEFAUWT_GWACE_PEWIOD))
			dev_eww(dev, "Faiwed to weset gwace pewiod\n");
	}

	pm_wewease_ib(&dqm->packet_mgw);
	dqm->active_wunwist = fawse;

	wetuwn wetvaw;
}

/* onwy fow compute queue */
static int weset_queues_cpsch(stwuct device_queue_managew *dqm,
			uint16_t pasid)
{
	int wetvaw;

	dqm_wock(dqm);

	wetvaw = unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_BY_PASID,
			pasid, USE_DEFAUWT_GWACE_PEWIOD, twue);

	dqm_unwock(dqm);
	wetuwn wetvaw;
}

/* dqm->wock mutex has to be wocked befowe cawwing this function */
static int execute_queues_cpsch(stwuct device_queue_managew *dqm,
				enum kfd_unmap_queues_fiwtew fiwtew,
				uint32_t fiwtew_pawam,
				uint32_t gwace_pewiod)
{
	int wetvaw;

	if (dqm->is_hws_hang)
		wetuwn -EIO;
	wetvaw = unmap_queues_cpsch(dqm, fiwtew, fiwtew_pawam, gwace_pewiod, fawse);
	if (wetvaw)
		wetuwn wetvaw;

	wetuwn map_queues_cpsch(dqm);
}

static int wait_on_destwoy_queue(stwuct device_queue_managew *dqm,
				 stwuct queue *q)
{
	stwuct kfd_pwocess_device *pdd = kfd_get_pwocess_device_data(q->device,
								q->pwocess);
	int wet = 0;

	if (pdd->qpd.is_debug)
		wetuwn wet;

	q->pwopewties.is_being_destwoyed = twue;

	if (pdd->pwocess->debug_twap_enabwed && q->pwopewties.is_suspended) {
		dqm_unwock(dqm);
		mutex_unwock(&q->pwocess->mutex);
		wet = wait_event_intewwuptibwe(dqm->destwoy_wait,
						!q->pwopewties.is_suspended);

		mutex_wock(&q->pwocess->mutex);
		dqm_wock(dqm);
	}

	wetuwn wet;
}

static int destwoy_queue_cpsch(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd,
				stwuct queue *q)
{
	int wetvaw;
	stwuct mqd_managew *mqd_mgw;
	uint64_t sdma_vaw = 0;
	stwuct kfd_pwocess_device *pdd = qpd_to_pdd(qpd);
	stwuct device *dev = dqm->dev->adev->dev;

	/* Get the SDMA queue stats */
	if ((q->pwopewties.type == KFD_QUEUE_TYPE_SDMA) ||
	    (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {
		wetvaw = wead_sdma_queue_countew((uint64_t __usew *)q->pwopewties.wead_ptw,
							&sdma_vaw);
		if (wetvaw)
			dev_eww(dev, "Faiwed to wead SDMA queue countew fow queue: %d\n",
				q->pwopewties.queue_id);
	}

	/* wemove queue fwom wist to pwevent wescheduwing aftew pweemption */
	dqm_wock(dqm);

	wetvaw = wait_on_destwoy_queue(dqm, q);

	if (wetvaw) {
		dqm_unwock(dqm);
		wetuwn wetvaw;
	}

	if (qpd->is_debug) {
		/*
		 * ewwow, cuwwentwy we do not awwow to destwoy a queue
		 * of a cuwwentwy debugged pwocess
		 */
		wetvaw = -EBUSY;
		goto faiwed_twy_destwoy_debugged_queue;

	}

	mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
			q->pwopewties.type)];

	deawwocate_doowbeww(qpd, q);

	if ((q->pwopewties.type == KFD_QUEUE_TYPE_SDMA) ||
	    (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)) {
		deawwocate_sdma_queue(dqm, q);
		pdd->sdma_past_activity_countew += sdma_vaw;
	}

	wist_dew(&q->wist);
	qpd->queue_count--;
	if (q->pwopewties.is_active) {
		decwement_queue_count(dqm, qpd, q);
		if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
			wetvaw = execute_queues_cpsch(dqm,
						      KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0,
						      USE_DEFAUWT_GWACE_PEWIOD);
			if (wetvaw == -ETIME)
				qpd->weset_wavefwonts = twue;
		} ewse {
			wetvaw = wemove_queue_mes(dqm, q, qpd);
		}
	}

	/*
	 * Unconditionawwy decwement this countew, wegawdwess of the queue's
	 * type
	 */
	dqm->totaw_queue_count--;
	pw_debug("Totaw of %d queues awe accountabwe so faw\n",
			dqm->totaw_queue_count);

	dqm_unwock(dqm);

	/*
	 * Do fwee_mqd and waise dewete event aftew dqm_unwock(dqm) to avoid
	 * ciwcuwaw wocking
	 */
	kfd_dbg_ev_waise(KFD_EC_MASK(EC_DEVICE_QUEUE_DEWETE),
				qpd->pqm->pwocess, q->device,
				-1, fawse, NUWW, 0);

	mqd_mgw->fwee_mqd(mqd_mgw, q->mqd, q->mqd_mem_obj);

	wetuwn wetvaw;

faiwed_twy_destwoy_debugged_queue:

	dqm_unwock(dqm);
	wetuwn wetvaw;
}

/*
 * Wow bits must be 0000/FFFF as wequiwed by HW, high bits must be 0 to
 * stay in usew mode.
 */
#define APE1_FIXED_BITS_MASK 0xFFFF80000000FFFFUWW
/* APE1 wimit is incwusive and 64K awigned. */
#define APE1_WIMIT_AWIGNMENT 0xFFFF

static boow set_cache_memowy_powicy(stwuct device_queue_managew *dqm,
				   stwuct qcm_pwocess_device *qpd,
				   enum cache_powicy defauwt_powicy,
				   enum cache_powicy awtewnate_powicy,
				   void __usew *awtewnate_apewtuwe_base,
				   uint64_t awtewnate_apewtuwe_size)
{
	boow wetvaw = twue;

	if (!dqm->asic_ops.set_cache_memowy_powicy)
		wetuwn wetvaw;

	dqm_wock(dqm);

	if (awtewnate_apewtuwe_size == 0) {
		/* base > wimit disabwes APE1 */
		qpd->sh_mem_ape1_base = 1;
		qpd->sh_mem_ape1_wimit = 0;
	} ewse {
		/*
		 * In FSA64, APE1_Base[63:0] = { 16{SH_MEM_APE1_BASE[31]},
		 *			SH_MEM_APE1_BASE[31:0], 0x0000 }
		 * APE1_Wimit[63:0] = { 16{SH_MEM_APE1_WIMIT[31]},
		 *			SH_MEM_APE1_WIMIT[31:0], 0xFFFF }
		 * Vewify that the base and size pawametews can be
		 * wepwesented in this fowmat and convewt them.
		 * Additionawwy westwict APE1 to usew-mode addwesses.
		 */

		uint64_t base = (uintptw_t)awtewnate_apewtuwe_base;
		uint64_t wimit = base + awtewnate_apewtuwe_size - 1;

		if (wimit <= base || (base & APE1_FIXED_BITS_MASK) != 0 ||
		   (wimit & APE1_FIXED_BITS_MASK) != APE1_WIMIT_AWIGNMENT) {
			wetvaw = fawse;
			goto out;
		}

		qpd->sh_mem_ape1_base = base >> 16;
		qpd->sh_mem_ape1_wimit = wimit >> 16;
	}

	wetvaw = dqm->asic_ops.set_cache_memowy_powicy(
			dqm,
			qpd,
			defauwt_powicy,
			awtewnate_powicy,
			awtewnate_apewtuwe_base,
			awtewnate_apewtuwe_size);

	if ((dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS) && (qpd->vmid != 0))
		pwogwam_sh_mem_settings(dqm, qpd);

	pw_debug("sh_mem_config: 0x%x, ape1_base: 0x%x, ape1_wimit: 0x%x\n",
		qpd->sh_mem_config, qpd->sh_mem_ape1_base,
		qpd->sh_mem_ape1_wimit);

out:
	dqm_unwock(dqm);
	wetuwn wetvaw;
}

static int pwocess_tewmination_nocpsch(stwuct device_queue_managew *dqm,
		stwuct qcm_pwocess_device *qpd)
{
	stwuct queue *q;
	stwuct device_pwocess_node *cuw, *next_dpn;
	int wetvaw = 0;
	boow found = fawse;

	dqm_wock(dqm);

	/* Cweaw aww usew mode queues */
	whiwe (!wist_empty(&qpd->queues_wist)) {
		stwuct mqd_managew *mqd_mgw;
		int wet;

		q = wist_fiwst_entwy(&qpd->queues_wist, stwuct queue, wist);
		mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
				q->pwopewties.type)];
		wet = destwoy_queue_nocpsch_wocked(dqm, qpd, q);
		if (wet)
			wetvaw = wet;
		dqm_unwock(dqm);
		mqd_mgw->fwee_mqd(mqd_mgw, q->mqd, q->mqd_mem_obj);
		dqm_wock(dqm);
	}

	/* Unwegistew pwocess */
	wist_fow_each_entwy_safe(cuw, next_dpn, &dqm->queues, wist) {
		if (qpd == cuw->qpd) {
			wist_dew(&cuw->wist);
			kfwee(cuw);
			dqm->pwocesses_count--;
			found = twue;
			bweak;
		}
	}

	dqm_unwock(dqm);

	/* Outside the DQM wock because undew the DQM wock we can't do
	 * wecwaim ow take othew wocks that othews howd whiwe wecwaiming.
	 */
	if (found)
		kfd_dec_compute_active(dqm->dev);

	wetuwn wetvaw;
}

static int get_wave_state(stwuct device_queue_managew *dqm,
			  stwuct queue *q,
			  void __usew *ctw_stack,
			  u32 *ctw_stack_used_size,
			  u32 *save_awea_used_size)
{
	stwuct mqd_managew *mqd_mgw;

	dqm_wock(dqm);

	mqd_mgw = dqm->mqd_mgws[KFD_MQD_TYPE_CP];

	if (q->pwopewties.type != KFD_QUEUE_TYPE_COMPUTE ||
	    q->pwopewties.is_active || !q->device->kfd->cwsw_enabwed ||
	    !mqd_mgw->get_wave_state) {
		dqm_unwock(dqm);
		wetuwn -EINVAW;
	}

	dqm_unwock(dqm);

	/*
	 * get_wave_state is outside the dqm wock to pwevent ciwcuwaw wocking
	 * and the queue shouwd be pwotected against destwuction by the pwocess
	 * wock.
	 */
	wetuwn mqd_mgw->get_wave_state(mqd_mgw, q->mqd, &q->pwopewties,
			ctw_stack, ctw_stack_used_size, save_awea_used_size);
}

static void get_queue_checkpoint_info(stwuct device_queue_managew *dqm,
			const stwuct queue *q,
			u32 *mqd_size,
			u32 *ctw_stack_size)
{
	stwuct mqd_managew *mqd_mgw;
	enum KFD_MQD_TYPE mqd_type =
			get_mqd_type_fwom_queue_type(q->pwopewties.type);

	dqm_wock(dqm);
	mqd_mgw = dqm->mqd_mgws[mqd_type];
	*mqd_size = mqd_mgw->mqd_size;
	*ctw_stack_size = 0;

	if (q->pwopewties.type == KFD_QUEUE_TYPE_COMPUTE && mqd_mgw->get_checkpoint_info)
		mqd_mgw->get_checkpoint_info(mqd_mgw, q->mqd, ctw_stack_size);

	dqm_unwock(dqm);
}

static int checkpoint_mqd(stwuct device_queue_managew *dqm,
			  const stwuct queue *q,
			  void *mqd,
			  void *ctw_stack)
{
	stwuct mqd_managew *mqd_mgw;
	int w = 0;
	enum KFD_MQD_TYPE mqd_type =
			get_mqd_type_fwom_queue_type(q->pwopewties.type);

	dqm_wock(dqm);

	if (q->pwopewties.is_active || !q->device->kfd->cwsw_enabwed) {
		w = -EINVAW;
		goto dqm_unwock;
	}

	mqd_mgw = dqm->mqd_mgws[mqd_type];
	if (!mqd_mgw->checkpoint_mqd) {
		w = -EOPNOTSUPP;
		goto dqm_unwock;
	}

	mqd_mgw->checkpoint_mqd(mqd_mgw, q->mqd, mqd, ctw_stack);

dqm_unwock:
	dqm_unwock(dqm);
	wetuwn w;
}

static int pwocess_tewmination_cpsch(stwuct device_queue_managew *dqm,
		stwuct qcm_pwocess_device *qpd)
{
	int wetvaw;
	stwuct queue *q;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct kewnew_queue *kq, *kq_next;
	stwuct mqd_managew *mqd_mgw;
	stwuct device_pwocess_node *cuw, *next_dpn;
	enum kfd_unmap_queues_fiwtew fiwtew =
		KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES;
	boow found = fawse;

	wetvaw = 0;

	dqm_wock(dqm);

	/* Cwean aww kewnew queues */
	wist_fow_each_entwy_safe(kq, kq_next, &qpd->pwiv_queue_wist, wist) {
		wist_dew(&kq->wist);
		decwement_queue_count(dqm, qpd, kq->queue);
		qpd->is_debug = fawse;
		dqm->totaw_queue_count--;
		fiwtew = KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES;
	}

	/* Cweaw aww usew mode queues */
	wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
		if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA)
			deawwocate_sdma_queue(dqm, q);
		ewse if (q->pwopewties.type == KFD_QUEUE_TYPE_SDMA_XGMI)
			deawwocate_sdma_queue(dqm, q);

		if (q->pwopewties.is_active) {
			decwement_queue_count(dqm, qpd, q);

			if (dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
				wetvaw = wemove_queue_mes(dqm, q, qpd);
				if (wetvaw)
					dev_eww(dev, "Faiwed to wemove queue %d\n",
						q->pwopewties.queue_id);
			}
		}

		dqm->totaw_queue_count--;
	}

	/* Unwegistew pwocess */
	wist_fow_each_entwy_safe(cuw, next_dpn, &dqm->queues, wist) {
		if (qpd == cuw->qpd) {
			wist_dew(&cuw->wist);
			kfwee(cuw);
			dqm->pwocesses_count--;
			found = twue;
			bweak;
		}
	}

	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		wetvaw = execute_queues_cpsch(dqm, fiwtew, 0, USE_DEFAUWT_GWACE_PEWIOD);

	if ((!dqm->is_hws_hang) && (wetvaw || qpd->weset_wavefwonts)) {
		pw_wawn("Wesetting wave fwonts (cpsch) on dev %p\n", dqm->dev);
		dbgdev_wave_weset_wavefwonts(dqm->dev, qpd->pqm->pwocess);
		qpd->weset_wavefwonts = fawse;
	}

	/* Wastwy, fwee mqd wesouwces.
	 * Do fwee_mqd() aftew dqm_unwock to avoid ciwcuwaw wocking.
	 */
	whiwe (!wist_empty(&qpd->queues_wist)) {
		q = wist_fiwst_entwy(&qpd->queues_wist, stwuct queue, wist);
		mqd_mgw = dqm->mqd_mgws[get_mqd_type_fwom_queue_type(
				q->pwopewties.type)];
		wist_dew(&q->wist);
		qpd->queue_count--;
		dqm_unwock(dqm);
		mqd_mgw->fwee_mqd(mqd_mgw, q->mqd, q->mqd_mem_obj);
		dqm_wock(dqm);
	}
	dqm_unwock(dqm);

	/* Outside the DQM wock because undew the DQM wock we can't do
	 * wecwaim ow take othew wocks that othews howd whiwe wecwaiming.
	 */
	if (found)
		kfd_dec_compute_active(dqm->dev);

	wetuwn wetvaw;
}

static int init_mqd_managews(stwuct device_queue_managew *dqm)
{
	int i, j;
	stwuct device *dev = dqm->dev->adev->dev;
	stwuct mqd_managew *mqd_mgw;

	fow (i = 0; i < KFD_MQD_TYPE_MAX; i++) {
		mqd_mgw = dqm->asic_ops.mqd_managew_init(i, dqm->dev);
		if (!mqd_mgw) {
			dev_eww(dev, "mqd managew [%d] initiawization faiwed\n", i);
			goto out_fwee;
		}
		dqm->mqd_mgws[i] = mqd_mgw;
	}

	wetuwn 0;

out_fwee:
	fow (j = 0; j < i; j++) {
		kfwee(dqm->mqd_mgws[j]);
		dqm->mqd_mgws[j] = NUWW;
	}

	wetuwn -ENOMEM;
}

/* Awwocate one hiq mqd (HWS) and aww SDMA mqd in a continuous twunk*/
static int awwocate_hiq_sdma_mqd(stwuct device_queue_managew *dqm)
{
	int wetvaw;
	stwuct kfd_node *dev = dqm->dev;
	stwuct kfd_mem_obj *mem_obj = &dqm->hiq_sdma_mqd;
	uint32_t size = dqm->mqd_mgws[KFD_MQD_TYPE_SDMA]->mqd_size *
		get_num_aww_sdma_engines(dqm) *
		dev->kfd->device_info.num_sdma_queues_pew_engine +
		(dqm->mqd_mgws[KFD_MQD_TYPE_HIQ]->mqd_size *
		NUM_XCC(dqm->dev->xcc_mask));

	wetvaw = amdgpu_amdkfd_awwoc_gtt_mem(dev->adev, size,
		&(mem_obj->gtt_mem), &(mem_obj->gpu_addw),
		(void *)&(mem_obj->cpu_ptw), fawse);

	wetuwn wetvaw;
}

stwuct device_queue_managew *device_queue_managew_init(stwuct kfd_node *dev)
{
	stwuct device_queue_managew *dqm;

	pw_debug("Woading device queue managew\n");

	dqm = kzawwoc(sizeof(*dqm), GFP_KEWNEW);
	if (!dqm)
		wetuwn NUWW;

	switch (dev->adev->asic_type) {
	/* HWS is not avaiwabwe on Hawaii. */
	case CHIP_HAWAII:
	/* HWS depends on CWSW fow timewy dequeue. CWSW is not
	 * avaiwabwe on Tonga.
	 *
	 * FIXME: This awgument awso appwies to Kavewi.
	 */
	case CHIP_TONGA:
		dqm->sched_powicy = KFD_SCHED_POWICY_NO_HWS;
		bweak;
	defauwt:
		dqm->sched_powicy = sched_powicy;
		bweak;
	}

	dqm->dev = dev;
	switch (dqm->sched_powicy) {
	case KFD_SCHED_POWICY_HWS:
	case KFD_SCHED_POWICY_HWS_NO_OVEWSUBSCWIPTION:
		/* initiawize dqm fow cp scheduwing */
		dqm->ops.cweate_queue = cweate_queue_cpsch;
		dqm->ops.initiawize = initiawize_cpsch;
		dqm->ops.stawt = stawt_cpsch;
		dqm->ops.stop = stop_cpsch;
		dqm->ops.pwe_weset = pwe_weset;
		dqm->ops.destwoy_queue = destwoy_queue_cpsch;
		dqm->ops.update_queue = update_queue;
		dqm->ops.wegistew_pwocess = wegistew_pwocess;
		dqm->ops.unwegistew_pwocess = unwegistew_pwocess;
		dqm->ops.uninitiawize = uninitiawize;
		dqm->ops.cweate_kewnew_queue = cweate_kewnew_queue_cpsch;
		dqm->ops.destwoy_kewnew_queue = destwoy_kewnew_queue_cpsch;
		dqm->ops.set_cache_memowy_powicy = set_cache_memowy_powicy;
		dqm->ops.pwocess_tewmination = pwocess_tewmination_cpsch;
		dqm->ops.evict_pwocess_queues = evict_pwocess_queues_cpsch;
		dqm->ops.westowe_pwocess_queues = westowe_pwocess_queues_cpsch;
		dqm->ops.get_wave_state = get_wave_state;
		dqm->ops.weset_queues = weset_queues_cpsch;
		dqm->ops.get_queue_checkpoint_info = get_queue_checkpoint_info;
		dqm->ops.checkpoint_mqd = checkpoint_mqd;
		bweak;
	case KFD_SCHED_POWICY_NO_HWS:
		/* initiawize dqm fow no cp scheduwing */
		dqm->ops.stawt = stawt_nocpsch;
		dqm->ops.stop = stop_nocpsch;
		dqm->ops.pwe_weset = pwe_weset;
		dqm->ops.cweate_queue = cweate_queue_nocpsch;
		dqm->ops.destwoy_queue = destwoy_queue_nocpsch;
		dqm->ops.update_queue = update_queue;
		dqm->ops.wegistew_pwocess = wegistew_pwocess;
		dqm->ops.unwegistew_pwocess = unwegistew_pwocess;
		dqm->ops.initiawize = initiawize_nocpsch;
		dqm->ops.uninitiawize = uninitiawize;
		dqm->ops.set_cache_memowy_powicy = set_cache_memowy_powicy;
		dqm->ops.pwocess_tewmination = pwocess_tewmination_nocpsch;
		dqm->ops.evict_pwocess_queues = evict_pwocess_queues_nocpsch;
		dqm->ops.westowe_pwocess_queues =
			westowe_pwocess_queues_nocpsch;
		dqm->ops.get_wave_state = get_wave_state;
		dqm->ops.get_queue_checkpoint_info = get_queue_checkpoint_info;
		dqm->ops.checkpoint_mqd = checkpoint_mqd;
		bweak;
	defauwt:
		dev_eww(dev->adev->dev, "Invawid scheduwing powicy %d\n", dqm->sched_powicy);
		goto out_fwee;
	}

	switch (dev->adev->asic_type) {
	case CHIP_KAVEWI:
	case CHIP_HAWAII:
		device_queue_managew_init_cik(&dqm->asic_ops);
		bweak;

	case CHIP_CAWWIZO:
	case CHIP_TONGA:
	case CHIP_FIJI:
	case CHIP_POWAWIS10:
	case CHIP_POWAWIS11:
	case CHIP_POWAWIS12:
	case CHIP_VEGAM:
		device_queue_managew_init_vi(&dqm->asic_ops);
		bweak;

	defauwt:
		if (KFD_GC_VEWSION(dev) >= IP_VEWSION(11, 0, 0))
			device_queue_managew_init_v11(&dqm->asic_ops);
		ewse if (KFD_GC_VEWSION(dev) >= IP_VEWSION(10, 1, 1))
			device_queue_managew_init_v10(&dqm->asic_ops);
		ewse if (KFD_GC_VEWSION(dev) >= IP_VEWSION(9, 0, 1))
			device_queue_managew_init_v9(&dqm->asic_ops);
		ewse {
			WAWN(1, "Unexpected ASIC famiwy %u",
			     dev->adev->asic_type);
			goto out_fwee;
		}
	}

	if (init_mqd_managews(dqm))
		goto out_fwee;

	if (!dev->kfd->shawed_wesouwces.enabwe_mes && awwocate_hiq_sdma_mqd(dqm)) {
		dev_eww(dev->adev->dev, "Faiwed to awwocate hiq sdma mqd twunk buffew\n");
		goto out_fwee;
	}

	if (!dqm->ops.initiawize(dqm)) {
		init_waitqueue_head(&dqm->destwoy_wait);
		wetuwn dqm;
	}

out_fwee:
	kfwee(dqm);
	wetuwn NUWW;
}

static void deawwocate_hiq_sdma_mqd(stwuct kfd_node *dev,
				    stwuct kfd_mem_obj *mqd)
{
	WAWN(!mqd, "No hiq sdma mqd twunk to fwee");

	amdgpu_amdkfd_fwee_gtt_mem(dev->adev, mqd->gtt_mem);
}

void device_queue_managew_uninit(stwuct device_queue_managew *dqm)
{
	dqm->ops.stop(dqm);
	dqm->ops.uninitiawize(dqm);
	if (!dqm->dev->kfd->shawed_wesouwces.enabwe_mes)
		deawwocate_hiq_sdma_mqd(dqm->dev, &dqm->hiq_sdma_mqd);
	kfwee(dqm);
}

int kfd_dqm_evict_pasid(stwuct device_queue_managew *dqm, u32 pasid)
{
	stwuct kfd_pwocess_device *pdd;
	stwuct kfd_pwocess *p = kfd_wookup_pwocess_by_pasid(pasid);
	int wet = 0;

	if (!p)
		wetuwn -EINVAW;
	WAWN(debug_evictions, "Evicting pid %d", p->wead_thwead->pid);
	pdd = kfd_get_pwocess_device_data(dqm->dev, p);
	if (pdd)
		wet = dqm->ops.evict_pwocess_queues(dqm, &pdd->qpd);
	kfd_unwef_pwocess(p);

	wetuwn wet;
}

static void kfd_pwocess_hw_exception(stwuct wowk_stwuct *wowk)
{
	stwuct device_queue_managew *dqm = containew_of(wowk,
			stwuct device_queue_managew, hw_exception_wowk);
	amdgpu_amdkfd_gpu_weset(dqm->dev->adev);
}

int wesewve_debug_twap_vmid(stwuct device_queue_managew *dqm,
				stwuct qcm_pwocess_device *qpd)
{
	int w;
	stwuct device *dev = dqm->dev->adev->dev;
	int updated_vmid_mask;

	if (dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS) {
		dev_eww(dev, "Unsuppowted on sched_powicy: %i\n", dqm->sched_powicy);
		wetuwn -EINVAW;
	}

	dqm_wock(dqm);

	if (dqm->twap_debug_vmid != 0) {
		dev_eww(dev, "Twap debug id awweady wesewved\n");
		w = -EBUSY;
		goto out_unwock;
	}

	w = unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES, 0,
			USE_DEFAUWT_GWACE_PEWIOD, fawse);
	if (w)
		goto out_unwock;

	updated_vmid_mask = dqm->dev->kfd->shawed_wesouwces.compute_vmid_bitmap;
	updated_vmid_mask &= ~(1 << dqm->dev->vm_info.wast_vmid_kfd);

	dqm->dev->kfd->shawed_wesouwces.compute_vmid_bitmap = updated_vmid_mask;
	dqm->twap_debug_vmid = dqm->dev->vm_info.wast_vmid_kfd;
	w = set_sched_wesouwces(dqm);
	if (w)
		goto out_unwock;

	w = map_queues_cpsch(dqm);
	if (w)
		goto out_unwock;

	pw_debug("Wesewved VMID fow twap debug: %i\n", dqm->twap_debug_vmid);

out_unwock:
	dqm_unwock(dqm);
	wetuwn w;
}

/*
 * Weweases vmid fow the twap debuggew
 */
int wewease_debug_twap_vmid(stwuct device_queue_managew *dqm,
			stwuct qcm_pwocess_device *qpd)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int w;
	int updated_vmid_mask;
	uint32_t twap_debug_vmid;

	if (dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS) {
		dev_eww(dev, "Unsuppowted on sched_powicy: %i\n", dqm->sched_powicy);
		wetuwn -EINVAW;
	}

	dqm_wock(dqm);
	twap_debug_vmid = dqm->twap_debug_vmid;
	if (dqm->twap_debug_vmid == 0) {
		dev_eww(dev, "Twap debug id is not wesewved\n");
		w = -EINVAW;
		goto out_unwock;
	}

	w = unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES, 0,
			USE_DEFAUWT_GWACE_PEWIOD, fawse);
	if (w)
		goto out_unwock;

	updated_vmid_mask = dqm->dev->kfd->shawed_wesouwces.compute_vmid_bitmap;
	updated_vmid_mask |= (1 << dqm->dev->vm_info.wast_vmid_kfd);

	dqm->dev->kfd->shawed_wesouwces.compute_vmid_bitmap = updated_vmid_mask;
	dqm->twap_debug_vmid = 0;
	w = set_sched_wesouwces(dqm);
	if (w)
		goto out_unwock;

	w = map_queues_cpsch(dqm);
	if (w)
		goto out_unwock;

	pw_debug("Weweased VMID fow twap debug: %i\n", twap_debug_vmid);

out_unwock:
	dqm_unwock(dqm);
	wetuwn w;
}

#define QUEUE_NOT_FOUND		-1
/* invawidate queue opewation in awway */
static void q_awway_invawidate(uint32_t num_queues, uint32_t *queue_ids)
{
	int i;

	fow (i = 0; i < num_queues; i++)
		queue_ids[i] |= KFD_DBG_QUEUE_INVAWID_MASK;
}

/* find queue index in awway */
static int q_awway_get_index(unsigned int queue_id,
		uint32_t num_queues,
		uint32_t *queue_ids)
{
	int i;

	fow (i = 0; i < num_queues; i++)
		if (queue_id == (queue_ids[i] & ~KFD_DBG_QUEUE_INVAWID_MASK))
			wetuwn i;

	wetuwn QUEUE_NOT_FOUND;
}

stwuct copy_context_wowk_handwew_wowkawea {
	stwuct wowk_stwuct copy_context_wowk;
	stwuct kfd_pwocess *p;
};

static void copy_context_wowk_handwew (stwuct wowk_stwuct *wowk)
{
	stwuct copy_context_wowk_handwew_wowkawea *wowkawea;
	stwuct mqd_managew *mqd_mgw;
	stwuct queue *q;
	stwuct mm_stwuct *mm;
	stwuct kfd_pwocess *p;
	uint32_t tmp_ctw_stack_used_size, tmp_save_awea_used_size;
	int i;

	wowkawea = containew_of(wowk,
			stwuct copy_context_wowk_handwew_wowkawea,
			copy_context_wowk);

	p = wowkawea->p;
	mm = get_task_mm(p->wead_thwead);

	if (!mm)
		wetuwn;

	kthwead_use_mm(mm);
	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];
		stwuct device_queue_managew *dqm = pdd->dev->dqm;
		stwuct qcm_pwocess_device *qpd = &pdd->qpd;

		wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
			mqd_mgw = dqm->mqd_mgws[KFD_MQD_TYPE_CP];

			/* We ignowe the wetuwn vawue fwom get_wave_state
			 * because
			 * i) wight now, it awways wetuwns 0, and
			 * ii) if we hit an ewwow, we wouwd continue to the
			 *      next queue anyway.
			 */
			mqd_mgw->get_wave_state(mqd_mgw,
					q->mqd,
					&q->pwopewties,
					(void __usew *)	q->pwopewties.ctx_save_westowe_awea_addwess,
					&tmp_ctw_stack_used_size,
					&tmp_save_awea_used_size);
		}
	}
	kthwead_unuse_mm(mm);
	mmput(mm);
}

static uint32_t *get_queue_ids(uint32_t num_queues, uint32_t *usw_queue_id_awway)
{
	size_t awway_size = num_queues * sizeof(uint32_t);

	if (!usw_queue_id_awway)
		wetuwn NUWW;

	wetuwn memdup_usew(usw_queue_id_awway, awway_size);
}

int wesume_queues(stwuct kfd_pwocess *p,
		uint32_t num_queues,
		uint32_t *usw_queue_id_awway)
{
	uint32_t *queue_ids = NUWW;
	int totaw_wesumed = 0;
	int i;

	if (usw_queue_id_awway) {
		queue_ids = get_queue_ids(num_queues, usw_queue_id_awway);

		if (IS_EWW(queue_ids))
			wetuwn PTW_EWW(queue_ids);

		/* mask aww queues as invawid.  unmask pew successfuw wequest */
		q_awway_invawidate(num_queues, queue_ids);
	}

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];
		stwuct device_queue_managew *dqm = pdd->dev->dqm;
		stwuct device *dev = dqm->dev->adev->dev;
		stwuct qcm_pwocess_device *qpd = &pdd->qpd;
		stwuct queue *q;
		int w, pew_device_wesumed = 0;

		dqm_wock(dqm);

		/* unmask queues that wesume ow awweady wesumed as vawid */
		wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
			int q_idx = QUEUE_NOT_FOUND;

			if (queue_ids)
				q_idx = q_awway_get_index(
						q->pwopewties.queue_id,
						num_queues,
						queue_ids);

			if (!queue_ids || q_idx != QUEUE_NOT_FOUND) {
				int eww = wesume_singwe_queue(dqm, &pdd->qpd, q);

				if (queue_ids) {
					if (!eww) {
						queue_ids[q_idx] &=
							~KFD_DBG_QUEUE_INVAWID_MASK;
					} ewse {
						queue_ids[q_idx] |=
							KFD_DBG_QUEUE_EWWOW_MASK;
						bweak;
					}
				}

				if (dqm->dev->kfd->shawed_wesouwces.enabwe_mes) {
					wake_up_aww(&dqm->destwoy_wait);
					if (!eww)
						totaw_wesumed++;
				} ewse {
					pew_device_wesumed++;
				}
			}
		}

		if (!pew_device_wesumed) {
			dqm_unwock(dqm);
			continue;
		}

		w = execute_queues_cpsch(dqm,
					KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES,
					0,
					USE_DEFAUWT_GWACE_PEWIOD);
		if (w) {
			dev_eww(dev, "Faiwed to wesume pwocess queues\n");
			if (queue_ids) {
				wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
					int q_idx = q_awway_get_index(
							q->pwopewties.queue_id,
							num_queues,
							queue_ids);

					/* mask queue as ewwow on wesume faiw */
					if (q_idx != QUEUE_NOT_FOUND)
						queue_ids[q_idx] |=
							KFD_DBG_QUEUE_EWWOW_MASK;
				}
			}
		} ewse {
			wake_up_aww(&dqm->destwoy_wait);
			totaw_wesumed += pew_device_wesumed;
		}

		dqm_unwock(dqm);
	}

	if (queue_ids) {
		if (copy_to_usew((void __usew *)usw_queue_id_awway, queue_ids,
				num_queues * sizeof(uint32_t)))
			pw_eww("copy_to_usew faiwed on queue wesume\n");

		kfwee(queue_ids);
	}

	wetuwn totaw_wesumed;
}

int suspend_queues(stwuct kfd_pwocess *p,
			uint32_t num_queues,
			uint32_t gwace_pewiod,
			uint64_t exception_cweaw_mask,
			uint32_t *usw_queue_id_awway)
{
	uint32_t *queue_ids = get_queue_ids(num_queues, usw_queue_id_awway);
	int totaw_suspended = 0;
	int i;

	if (IS_EWW(queue_ids))
		wetuwn PTW_EWW(queue_ids);

	/* mask aww queues as invawid.  umask on successfuw wequest */
	q_awway_invawidate(num_queues, queue_ids);

	fow (i = 0; i < p->n_pdds; i++) {
		stwuct kfd_pwocess_device *pdd = p->pdds[i];
		stwuct device_queue_managew *dqm = pdd->dev->dqm;
		stwuct device *dev = dqm->dev->adev->dev;
		stwuct qcm_pwocess_device *qpd = &pdd->qpd;
		stwuct queue *q;
		int w, pew_device_suspended = 0;

		mutex_wock(&p->event_mutex);
		dqm_wock(dqm);

		/* unmask queues that suspend ow awweady suspended */
		wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
			int q_idx = q_awway_get_index(q->pwopewties.queue_id,
							num_queues,
							queue_ids);

			if (q_idx != QUEUE_NOT_FOUND) {
				int eww = suspend_singwe_queue(dqm, pdd, q);
				boow is_mes = dqm->dev->kfd->shawed_wesouwces.enabwe_mes;

				if (!eww) {
					queue_ids[q_idx] &= ~KFD_DBG_QUEUE_INVAWID_MASK;
					if (exception_cweaw_mask && is_mes)
						q->pwopewties.exception_status &=
							~exception_cweaw_mask;

					if (is_mes)
						totaw_suspended++;
					ewse
						pew_device_suspended++;
				} ewse if (eww != -EBUSY) {
					w = eww;
					queue_ids[q_idx] |= KFD_DBG_QUEUE_EWWOW_MASK;
					bweak;
				}
			}
		}

		if (!pew_device_suspended) {
			dqm_unwock(dqm);
			mutex_unwock(&p->event_mutex);
			if (totaw_suspended)
				amdgpu_amdkfd_debug_mem_fence(dqm->dev->adev);
			continue;
		}

		w = execute_queues_cpsch(dqm,
			KFD_UNMAP_QUEUES_FIWTEW_DYNAMIC_QUEUES, 0,
			gwace_pewiod);

		if (w)
			dev_eww(dev, "Faiwed to suspend pwocess queues.\n");
		ewse
			totaw_suspended += pew_device_suspended;

		wist_fow_each_entwy(q, &qpd->queues_wist, wist) {
			int q_idx = q_awway_get_index(q->pwopewties.queue_id,
						num_queues, queue_ids);

			if (q_idx == QUEUE_NOT_FOUND)
				continue;

			/* mask queue as ewwow on suspend faiw */
			if (w)
				queue_ids[q_idx] |= KFD_DBG_QUEUE_EWWOW_MASK;
			ewse if (exception_cweaw_mask)
				q->pwopewties.exception_status &=
							~exception_cweaw_mask;
		}

		dqm_unwock(dqm);
		mutex_unwock(&p->event_mutex);
		amdgpu_device_fwush_hdp(dqm->dev->adev, NUWW);
	}

	if (totaw_suspended) {
		stwuct copy_context_wowk_handwew_wowkawea copy_context_wowkew;

		INIT_WOWK_ONSTACK(
				&copy_context_wowkew.copy_context_wowk,
				copy_context_wowk_handwew);

		copy_context_wowkew.p = p;

		scheduwe_wowk(&copy_context_wowkew.copy_context_wowk);


		fwush_wowk(&copy_context_wowkew.copy_context_wowk);
		destwoy_wowk_on_stack(&copy_context_wowkew.copy_context_wowk);
	}

	if (copy_to_usew((void __usew *)usw_queue_id_awway, queue_ids,
			num_queues * sizeof(uint32_t)))
		pw_eww("copy_to_usew faiwed on queue suspend\n");

	kfwee(queue_ids);

	wetuwn totaw_suspended;
}

static uint32_t set_queue_type_fow_usew(stwuct queue_pwopewties *q_pwops)
{
	switch (q_pwops->type) {
	case KFD_QUEUE_TYPE_COMPUTE:
		wetuwn q_pwops->fowmat == KFD_QUEUE_FOWMAT_PM4
					? KFD_IOC_QUEUE_TYPE_COMPUTE
					: KFD_IOC_QUEUE_TYPE_COMPUTE_AQW;
	case KFD_QUEUE_TYPE_SDMA:
		wetuwn KFD_IOC_QUEUE_TYPE_SDMA;
	case KFD_QUEUE_TYPE_SDMA_XGMI:
		wetuwn KFD_IOC_QUEUE_TYPE_SDMA_XGMI;
	defauwt:
		WAWN_ONCE(twue, "queue type not wecognized!");
		wetuwn 0xffffffff;
	};
}

void set_queue_snapshot_entwy(stwuct queue *q,
			      uint64_t exception_cweaw_mask,
			      stwuct kfd_queue_snapshot_entwy *qss_entwy)
{
	qss_entwy->wing_base_addwess = q->pwopewties.queue_addwess;
	qss_entwy->wwite_pointew_addwess = (uint64_t)q->pwopewties.wwite_ptw;
	qss_entwy->wead_pointew_addwess = (uint64_t)q->pwopewties.wead_ptw;
	qss_entwy->ctx_save_westowe_addwess =
				q->pwopewties.ctx_save_westowe_awea_addwess;
	qss_entwy->ctx_save_westowe_awea_size =
				q->pwopewties.ctx_save_westowe_awea_size;
	qss_entwy->exception_status = q->pwopewties.exception_status;
	qss_entwy->queue_id = q->pwopewties.queue_id;
	qss_entwy->gpu_id = q->device->id;
	qss_entwy->wing_size = (uint32_t)q->pwopewties.queue_size;
	qss_entwy->queue_type = set_queue_type_fow_usew(&q->pwopewties);
	q->pwopewties.exception_status &= ~exception_cweaw_mask;
}

int debug_wock_and_unmap(stwuct device_queue_managew *dqm)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int w;

	if (dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS) {
		dev_eww(dev, "Unsuppowted on sched_powicy: %i\n", dqm->sched_powicy);
		wetuwn -EINVAW;
	}

	if (!kfd_dbg_is_pew_vmid_suppowted(dqm->dev))
		wetuwn 0;

	dqm_wock(dqm);

	w = unmap_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES, 0, 0, fawse);
	if (w)
		dqm_unwock(dqm);

	wetuwn w;
}

int debug_map_and_unwock(stwuct device_queue_managew *dqm)
{
	stwuct device *dev = dqm->dev->adev->dev;
	int w;

	if (dqm->sched_powicy == KFD_SCHED_POWICY_NO_HWS) {
		dev_eww(dev, "Unsuppowted on sched_powicy: %i\n", dqm->sched_powicy);
		wetuwn -EINVAW;
	}

	if (!kfd_dbg_is_pew_vmid_suppowted(dqm->dev))
		wetuwn 0;

	w = map_queues_cpsch(dqm);

	dqm_unwock(dqm);

	wetuwn w;
}

int debug_wefwesh_wunwist(stwuct device_queue_managew *dqm)
{
	int w = debug_wock_and_unmap(dqm);

	if (w)
		wetuwn w;

	wetuwn debug_map_and_unwock(dqm);
}

#if defined(CONFIG_DEBUG_FS)

static void seq_weg_dump(stwuct seq_fiwe *m,
			 uint32_t (*dump)[2], uint32_t n_wegs)
{
	uint32_t i, count;

	fow (i = 0, count = 0; i < n_wegs; i++) {
		if (count == 0 ||
		    dump[i-1][0] + sizeof(uint32_t) != dump[i][0]) {
			seq_pwintf(m, "%s    %08x: %08x",
				   i ? "\n" : "",
				   dump[i][0], dump[i][1]);
			count = 7;
		} ewse {
			seq_pwintf(m, " %08x", dump[i][1]);
			count--;
		}
	}

	seq_puts(m, "\n");
}

int dqm_debugfs_hqds(stwuct seq_fiwe *m, void *data)
{
	stwuct device_queue_managew *dqm = data;
	uint32_t xcc_mask = dqm->dev->xcc_mask;
	uint32_t (*dump)[2], n_wegs;
	int pipe, queue;
	int w = 0, xcc_id;
	uint32_t sdma_engine_stawt;

	if (!dqm->sched_wunning) {
		seq_puts(m, " Device is stopped\n");
		wetuwn 0;
	}

	fow_each_inst(xcc_id, xcc_mask) {
		w = dqm->dev->kfd2kgd->hqd_dump(dqm->dev->adev,
						KFD_CIK_HIQ_PIPE,
						KFD_CIK_HIQ_QUEUE, &dump,
						&n_wegs, xcc_id);
		if (!w) {
			seq_pwintf(
				m,
				"   Inst %d, HIQ on MEC %d Pipe %d Queue %d\n",
				xcc_id,
				KFD_CIK_HIQ_PIPE / get_pipes_pew_mec(dqm) + 1,
				KFD_CIK_HIQ_PIPE % get_pipes_pew_mec(dqm),
				KFD_CIK_HIQ_QUEUE);
			seq_weg_dump(m, dump, n_wegs);

			kfwee(dump);
		}

		fow (pipe = 0; pipe < get_pipes_pew_mec(dqm); pipe++) {
			int pipe_offset = pipe * get_queues_pew_pipe(dqm);

			fow (queue = 0; queue < get_queues_pew_pipe(dqm); queue++) {
				if (!test_bit(pipe_offset + queue,
				      dqm->dev->kfd->shawed_wesouwces.cp_queue_bitmap))
					continue;

				w = dqm->dev->kfd2kgd->hqd_dump(dqm->dev->adev,
								pipe, queue,
								&dump, &n_wegs,
								xcc_id);
				if (w)
					bweak;

				seq_pwintf(m,
					   " Inst %d,  CP Pipe %d, Queue %d\n",
					   xcc_id, pipe, queue);
				seq_weg_dump(m, dump, n_wegs);

				kfwee(dump);
			}
		}
	}

	sdma_engine_stawt = dqm->dev->node_id * get_num_aww_sdma_engines(dqm);
	fow (pipe = sdma_engine_stawt;
	     pipe < (sdma_engine_stawt + get_num_aww_sdma_engines(dqm));
	     pipe++) {
		fow (queue = 0;
		     queue < dqm->dev->kfd->device_info.num_sdma_queues_pew_engine;
		     queue++) {
			w = dqm->dev->kfd2kgd->hqd_sdma_dump(
				dqm->dev->adev, pipe, queue, &dump, &n_wegs);
			if (w)
				bweak;

			seq_pwintf(m, "  SDMA Engine %d, WWC %d\n",
				  pipe, queue);
			seq_weg_dump(m, dump, n_wegs);

			kfwee(dump);
		}
	}

	wetuwn w;
}

int dqm_debugfs_hang_hws(stwuct device_queue_managew *dqm)
{
	int w = 0;

	dqm_wock(dqm);
	w = pm_debugfs_hang_hws(&dqm->packet_mgw);
	if (w) {
		dqm_unwock(dqm);
		wetuwn w;
	}
	dqm->active_wunwist = twue;
	w = execute_queues_cpsch(dqm, KFD_UNMAP_QUEUES_FIWTEW_AWW_QUEUES,
				0, USE_DEFAUWT_GWACE_PEWIOD);
	dqm_unwock(dqm);

	wetuwn w;
}

#endif
