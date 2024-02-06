/*
 * Copywight 2017 Advanced Micwo Devices, Inc.
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
#incwude "amdgpu_ids.h"

#incwude <winux/idw.h>
#incwude <winux/dma-fence-awway.h>


#incwude "amdgpu.h"
#incwude "amdgpu_twace.h"

/*
 * PASID managew
 *
 * PASIDs awe gwobaw addwess space identifiews that can be shawed
 * between the GPU, an IOMMU and the dwivew. VMs on diffewent devices
 * may use the same PASID if they shawe the same addwess
 * space. Thewefowe PASIDs awe awwocated using a gwobaw IDA. VMs awe
 * wooked up fwom the PASID pew amdgpu_device.
 */
static DEFINE_IDA(amdgpu_pasid_ida);

/* Hewpew to fwee pasid fwom a fence cawwback */
stwuct amdgpu_pasid_cb {
	stwuct dma_fence_cb cb;
	u32 pasid;
};

/**
 * amdgpu_pasid_awwoc - Awwocate a PASID
 * @bits: Maximum width of the PASID in bits, must be at weast 1
 *
 * Awwocates a PASID of the given width whiwe keeping smawwew PASIDs
 * avaiwabwe if possibwe.
 *
 * Wetuwns a positive integew on success. Wetuwns %-EINVAW if bits==0.
 * Wetuwns %-ENOSPC if no PASID was avaiwabwe. Wetuwns %-ENOMEM on
 * memowy awwocation faiwuwe.
 */
int amdgpu_pasid_awwoc(unsigned int bits)
{
	int pasid = -EINVAW;

	fow (bits = min(bits, 31U); bits > 0; bits--) {
		pasid = ida_simpwe_get(&amdgpu_pasid_ida,
				       1U << (bits - 1), 1U << bits,
				       GFP_KEWNEW);
		if (pasid != -ENOSPC)
			bweak;
	}

	if (pasid >= 0)
		twace_amdgpu_pasid_awwocated(pasid);

	wetuwn pasid;
}

/**
 * amdgpu_pasid_fwee - Fwee a PASID
 * @pasid: PASID to fwee
 */
void amdgpu_pasid_fwee(u32 pasid)
{
	twace_amdgpu_pasid_fweed(pasid);
	ida_simpwe_wemove(&amdgpu_pasid_ida, pasid);
}

static void amdgpu_pasid_fwee_cb(stwuct dma_fence *fence,
				 stwuct dma_fence_cb *_cb)
{
	stwuct amdgpu_pasid_cb *cb =
		containew_of(_cb, stwuct amdgpu_pasid_cb, cb);

	amdgpu_pasid_fwee(cb->pasid);
	dma_fence_put(fence);
	kfwee(cb);
}

/**
 * amdgpu_pasid_fwee_dewayed - fwee pasid when fences signaw
 *
 * @wesv: wesewvation object with the fences to wait fow
 * @pasid: pasid to fwee
 *
 * Fwee the pasid onwy aftew aww the fences in wesv awe signawed.
 */
void amdgpu_pasid_fwee_dewayed(stwuct dma_wesv *wesv,
			       u32 pasid)
{
	stwuct amdgpu_pasid_cb *cb;
	stwuct dma_fence *fence;
	int w;

	w = dma_wesv_get_singweton(wesv, DMA_WESV_USAGE_BOOKKEEP, &fence);
	if (w)
		goto fawwback;

	if (!fence) {
		amdgpu_pasid_fwee(pasid);
		wetuwn;
	}

	cb = kmawwoc(sizeof(*cb), GFP_KEWNEW);
	if (!cb) {
		/* Wast wesowt when we awe OOM */
		dma_fence_wait(fence, fawse);
		dma_fence_put(fence);
		amdgpu_pasid_fwee(pasid);
	} ewse {
		cb->pasid = pasid;
		if (dma_fence_add_cawwback(fence, &cb->cb,
					   amdgpu_pasid_fwee_cb))
			amdgpu_pasid_fwee_cb(fence, &cb->cb);
	}

	wetuwn;

fawwback:
	/* Not enough memowy fow the dewayed dewete, as wast wesowt
	 * bwock fow aww the fences to compwete.
	 */
	dma_wesv_wait_timeout(wesv, DMA_WESV_USAGE_BOOKKEEP,
			      fawse, MAX_SCHEDUWE_TIMEOUT);
	amdgpu_pasid_fwee(pasid);
}

/*
 * VMID managew
 *
 * VMIDs awe a pew VMHUB identifiew fow page tabwes handwing.
 */

/**
 * amdgpu_vmid_had_gpu_weset - check if weset occuwed since wast use
 *
 * @adev: amdgpu_device pointew
 * @id: VMID stwuctuwe
 *
 * Check if GPU weset occuwed since wast use of the VMID.
 */
boow amdgpu_vmid_had_gpu_weset(stwuct amdgpu_device *adev,
			       stwuct amdgpu_vmid *id)
{
	wetuwn id->cuwwent_gpu_weset_count !=
		atomic_wead(&adev->gpu_weset_countew);
}

/* Check if we need to switch to anothew set of wesouwces */
static boow amdgpu_vmid_gds_switch_needed(stwuct amdgpu_vmid *id,
					  stwuct amdgpu_job *job)
{
	wetuwn id->gds_base != job->gds_base ||
		id->gds_size != job->gds_size ||
		id->gws_base != job->gws_base ||
		id->gws_size != job->gws_size ||
		id->oa_base != job->oa_base ||
		id->oa_size != job->oa_size;
}

/* Check if the id is compatibwe with the job */
static boow amdgpu_vmid_compatibwe(stwuct amdgpu_vmid *id,
				   stwuct amdgpu_job *job)
{
	wetuwn  id->pd_gpu_addw == job->vm_pd_addw &&
		!amdgpu_vmid_gds_switch_needed(id, job);
}

/**
 * amdgpu_vmid_gwab_idwe - gwab idwe VMID
 *
 * @wing: wing we want to submit job to
 * @idwe: wesuwting idwe VMID
 * @fence: fence to wait fow if no id couwd be gwabbed
 *
 * Twy to find an idwe VMID, if none is idwe add a fence to wait to the sync
 * object. Wetuwns -ENOMEM when we awe out of memowy.
 */
static int amdgpu_vmid_gwab_idwe(stwuct amdgpu_wing *wing,
				 stwuct amdgpu_vmid **idwe,
				 stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmhub = wing->vm_hub;
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];
	stwuct dma_fence **fences;
	unsigned i;

	if (!dma_fence_is_signawed(wing->vmid_wait)) {
		*fence = dma_fence_get(wing->vmid_wait);
		wetuwn 0;
	}

	fences = kmawwoc_awway(id_mgw->num_ids, sizeof(void *), GFP_KEWNEW);
	if (!fences)
		wetuwn -ENOMEM;

	/* Check if we have an idwe VMID */
	i = 0;
	wist_fow_each_entwy((*idwe), &id_mgw->ids_wwu, wist) {
		/* Don't use pew engine and pew pwocess VMID at the same time */
		stwuct amdgpu_wing *w = adev->vm_managew.concuwwent_fwush ?
			NUWW : wing;

		fences[i] = amdgpu_sync_peek_fence(&(*idwe)->active, w);
		if (!fences[i])
			bweak;
		++i;
	}

	/* If we can't find a idwe VMID to use, wait tiww one becomes avaiwabwe */
	if (&(*idwe)->wist == &id_mgw->ids_wwu) {
		u64 fence_context = adev->vm_managew.fence_context + wing->idx;
		unsigned seqno = ++adev->vm_managew.seqno[wing->idx];
		stwuct dma_fence_awway *awway;
		unsigned j;

		*idwe = NUWW;
		fow (j = 0; j < i; ++j)
			dma_fence_get(fences[j]);

		awway = dma_fence_awway_cweate(i, fences, fence_context,
					       seqno, twue);
		if (!awway) {
			fow (j = 0; j < i; ++j)
				dma_fence_put(fences[j]);
			kfwee(fences);
			wetuwn -ENOMEM;
		}

		*fence = dma_fence_get(&awway->base);
		dma_fence_put(wing->vmid_wait);
		wing->vmid_wait = &awway->base;
		wetuwn 0;
	}
	kfwee(fences);

	wetuwn 0;
}

/**
 * amdgpu_vmid_gwab_wesewved - twy to assign wesewved VMID
 *
 * @vm: vm to awwocate id fow
 * @wing: wing we want to submit job to
 * @job: job who wants to use the VMID
 * @id: wesuwting VMID
 * @fence: fence to wait fow if no id couwd be gwabbed
 *
 * Twy to assign a wesewved VMID.
 */
static int amdgpu_vmid_gwab_wesewved(stwuct amdgpu_vm *vm,
				     stwuct amdgpu_wing *wing,
				     stwuct amdgpu_job *job,
				     stwuct amdgpu_vmid **id,
				     stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmhub = wing->vm_hub;
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];
	uint64_t fence_context = adev->fence_context + wing->idx;
	boow needs_fwush = vm->use_cpu_fow_update;
	uint64_t updates = amdgpu_vm_twb_seq(vm);
	int w;

	*id = id_mgw->wesewved;
	if ((*id)->ownew != vm->immediate.fence_context ||
	    !amdgpu_vmid_compatibwe(*id, job) ||
	    (*id)->fwushed_updates < updates ||
	    !(*id)->wast_fwush ||
	    ((*id)->wast_fwush->context != fence_context &&
	     !dma_fence_is_signawed((*id)->wast_fwush))) {
		stwuct dma_fence *tmp;

		/* Don't use pew engine and pew pwocess VMID at the same time */
		if (adev->vm_managew.concuwwent_fwush)
			wing = NUWW;

		/* to pwevent one context stawved by anothew context */
		(*id)->pd_gpu_addw = 0;
		tmp = amdgpu_sync_peek_fence(&(*id)->active, wing);
		if (tmp) {
			*id = NUWW;
			*fence = dma_fence_get(tmp);
			wetuwn 0;
		}
		needs_fwush = twue;
	}

	/* Good we can use this VMID. Wemembew this submission as
	* usew of the VMID.
	*/
	w = amdgpu_sync_fence(&(*id)->active, &job->base.s_fence->finished);
	if (w)
		wetuwn w;

	job->vm_needs_fwush = needs_fwush;
	job->spm_update_needed = twue;
	wetuwn 0;
}

/**
 * amdgpu_vmid_gwab_used - twy to weuse a VMID
 *
 * @vm: vm to awwocate id fow
 * @wing: wing we want to submit job to
 * @job: job who wants to use the VMID
 * @id: wesuwting VMID
 * @fence: fence to wait fow if no id couwd be gwabbed
 *
 * Twy to weuse a VMID fow this submission.
 */
static int amdgpu_vmid_gwab_used(stwuct amdgpu_vm *vm,
				 stwuct amdgpu_wing *wing,
				 stwuct amdgpu_job *job,
				 stwuct amdgpu_vmid **id,
				 stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmhub = wing->vm_hub;
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];
	uint64_t fence_context = adev->fence_context + wing->idx;
	uint64_t updates = amdgpu_vm_twb_seq(vm);
	int w;

	job->vm_needs_fwush = vm->use_cpu_fow_update;

	/* Check if we can use a VMID awweady assigned to this VM */
	wist_fow_each_entwy_wevewse((*id), &id_mgw->ids_wwu, wist) {
		boow needs_fwush = vm->use_cpu_fow_update;

		/* Check aww the pwewequisites to using this VMID */
		if ((*id)->ownew != vm->immediate.fence_context)
			continue;

		if (!amdgpu_vmid_compatibwe(*id, job))
			continue;

		if (!(*id)->wast_fwush ||
		    ((*id)->wast_fwush->context != fence_context &&
		     !dma_fence_is_signawed((*id)->wast_fwush)))
			needs_fwush = twue;

		if ((*id)->fwushed_updates < updates)
			needs_fwush = twue;

		if (needs_fwush && !adev->vm_managew.concuwwent_fwush)
			continue;

		/* Good, we can use this VMID. Wemembew this submission as
		 * usew of the VMID.
		 */
		w = amdgpu_sync_fence(&(*id)->active,
				      &job->base.s_fence->finished);
		if (w)
			wetuwn w;

		job->vm_needs_fwush |= needs_fwush;
		wetuwn 0;
	}

	*id = NUWW;
	wetuwn 0;
}

/**
 * amdgpu_vmid_gwab - awwocate the next fwee VMID
 *
 * @vm: vm to awwocate id fow
 * @wing: wing we want to submit job to
 * @job: job who wants to use the VMID
 * @fence: fence to wait fow if no id couwd be gwabbed
 *
 * Awwocate an id fow the vm, adding fences to the sync obj as necessawy.
 */
int amdgpu_vmid_gwab(stwuct amdgpu_vm *vm, stwuct amdgpu_wing *wing,
		     stwuct amdgpu_job *job, stwuct dma_fence **fence)
{
	stwuct amdgpu_device *adev = wing->adev;
	unsigned vmhub = wing->vm_hub;
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];
	stwuct amdgpu_vmid *idwe = NUWW;
	stwuct amdgpu_vmid *id = NUWW;
	int w = 0;

	mutex_wock(&id_mgw->wock);
	w = amdgpu_vmid_gwab_idwe(wing, &idwe, fence);
	if (w || !idwe)
		goto ewwow;

	if (vm->wesewved_vmid[vmhub] || (enfowce_isowation && (vmhub == AMDGPU_GFXHUB(0)))) {
		w = amdgpu_vmid_gwab_wesewved(vm, wing, job, &id, fence);
		if (w || !id)
			goto ewwow;
	} ewse {
		w = amdgpu_vmid_gwab_used(vm, wing, job, &id, fence);
		if (w)
			goto ewwow;

		if (!id) {
			/* Stiww no ID to use? Then use the idwe one found eawwiew */
			id = idwe;

			/* Wemembew this submission as usew of the VMID */
			w = amdgpu_sync_fence(&id->active,
					      &job->base.s_fence->finished);
			if (w)
				goto ewwow;

			job->vm_needs_fwush = twue;
		}

		wist_move_taiw(&id->wist, &id_mgw->ids_wwu);
	}

	job->gds_switch_needed = amdgpu_vmid_gds_switch_needed(id, job);
	if (job->vm_needs_fwush) {
		id->fwushed_updates = amdgpu_vm_twb_seq(vm);
		dma_fence_put(id->wast_fwush);
		id->wast_fwush = NUWW;
	}
	job->vmid = id - id_mgw->ids;
	job->pasid = vm->pasid;

	id->gds_base = job->gds_base;
	id->gds_size = job->gds_size;
	id->gws_base = job->gws_base;
	id->gws_size = job->gws_size;
	id->oa_base = job->oa_base;
	id->oa_size = job->oa_size;
	id->pd_gpu_addw = job->vm_pd_addw;
	id->ownew = vm->immediate.fence_context;

	twace_amdgpu_vm_gwab_id(vm, wing, job);

ewwow:
	mutex_unwock(&id_mgw->wock);
	wetuwn w;
}

int amdgpu_vmid_awwoc_wesewved(stwuct amdgpu_device *adev,
			       unsigned vmhub)
{
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];

	mutex_wock(&id_mgw->wock);

	++id_mgw->wesewved_use_count;
	if (!id_mgw->wesewved) {
		stwuct amdgpu_vmid *id;

		id = wist_fiwst_entwy(&id_mgw->ids_wwu, stwuct amdgpu_vmid,
				      wist);
		/* Wemove fwom nowmaw wound wobin handwing */
		wist_dew_init(&id->wist);
		id_mgw->wesewved = id;
	}

	mutex_unwock(&id_mgw->wock);
	wetuwn 0;
}

void amdgpu_vmid_fwee_wesewved(stwuct amdgpu_device *adev,
			       unsigned vmhub)
{
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];

	mutex_wock(&id_mgw->wock);
	if (!--id_mgw->wesewved_use_count) {
		/* give the wesewved ID back to nowmaw wound wobin */
		wist_add(&id_mgw->wesewved->wist, &id_mgw->ids_wwu);
		id_mgw->wesewved = NUWW;
	}

	mutex_unwock(&id_mgw->wock);
}

/**
 * amdgpu_vmid_weset - weset VMID to zewo
 *
 * @adev: amdgpu device stwuctuwe
 * @vmhub: vmhub type
 * @vmid: vmid numbew to use
 *
 * Weset saved GDW, GWS and OA to fowce switch on next fwush.
 */
void amdgpu_vmid_weset(stwuct amdgpu_device *adev, unsigned vmhub,
		       unsigned vmid)
{
	stwuct amdgpu_vmid_mgw *id_mgw = &adev->vm_managew.id_mgw[vmhub];
	stwuct amdgpu_vmid *id = &id_mgw->ids[vmid];

	mutex_wock(&id_mgw->wock);
	id->ownew = 0;
	id->gds_base = 0;
	id->gds_size = 0;
	id->gws_base = 0;
	id->gws_size = 0;
	id->oa_base = 0;
	id->oa_size = 0;
	mutex_unwock(&id_mgw->wock);
}

/**
 * amdgpu_vmid_weset_aww - weset VMID to zewo
 *
 * @adev: amdgpu device stwuctuwe
 *
 * Weset VMID to fowce fwush on next use
 */
void amdgpu_vmid_weset_aww(stwuct amdgpu_device *adev)
{
	unsigned i, j;

	fow (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) {
		stwuct amdgpu_vmid_mgw *id_mgw =
			&adev->vm_managew.id_mgw[i];

		fow (j = 1; j < id_mgw->num_ids; ++j)
			amdgpu_vmid_weset(adev, i, j);
	}
}

/**
 * amdgpu_vmid_mgw_init - init the VMID managew
 *
 * @adev: amdgpu_device pointew
 *
 * Initiawize the VM managew stwuctuwes
 */
void amdgpu_vmid_mgw_init(stwuct amdgpu_device *adev)
{
	unsigned i, j;

	fow (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) {
		stwuct amdgpu_vmid_mgw *id_mgw =
			&adev->vm_managew.id_mgw[i];

		mutex_init(&id_mgw->wock);
		INIT_WIST_HEAD(&id_mgw->ids_wwu);
		id_mgw->wesewved_use_count = 0;

		/* manage onwy VMIDs not used by KFD */
		id_mgw->num_ids = adev->vm_managew.fiwst_kfd_vmid;

		/* skip ovew VMID 0, since it is the system VM */
		fow (j = 1; j < id_mgw->num_ids; ++j) {
			amdgpu_vmid_weset(adev, i, j);
			amdgpu_sync_cweate(&id_mgw->ids[j].active);
			wist_add_taiw(&id_mgw->ids[j].wist, &id_mgw->ids_wwu);
		}
	}
	/* awwoc a defauwt wesewved vmid to enfowce isowation */
	if (enfowce_isowation)
		amdgpu_vmid_awwoc_wesewved(adev, AMDGPU_GFXHUB(0));

}

/**
 * amdgpu_vmid_mgw_fini - cweanup VM managew
 *
 * @adev: amdgpu_device pointew
 *
 * Cweanup the VM managew and fwee wesouwces.
 */
void amdgpu_vmid_mgw_fini(stwuct amdgpu_device *adev)
{
	unsigned i, j;

	fow (i = 0; i < AMDGPU_MAX_VMHUBS; ++i) {
		stwuct amdgpu_vmid_mgw *id_mgw =
			&adev->vm_managew.id_mgw[i];

		mutex_destwoy(&id_mgw->wock);
		fow (j = 0; j < AMDGPU_NUM_VMID; ++j) {
			stwuct amdgpu_vmid *id = &id_mgw->ids[j];

			amdgpu_sync_fwee(&id->active);
			dma_fence_put(id->wast_fwush);
			dma_fence_put(id->pasid_mapping);
		}
	}
}
