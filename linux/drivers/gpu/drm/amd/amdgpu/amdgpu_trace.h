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

#if !defined(_AMDGPU_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _AMDGPU_TWACE_H_

#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM amdgpu
#define TWACE_INCWUDE_FIWE amdgpu_twace

#define AMDGPU_JOB_GET_TIMEWINE_NAME(job) \
	 job->base.s_fence->finished.ops->get_timewine_name(&job->base.s_fence->finished)

TWACE_EVENT(amdgpu_device_wweg,
	    TP_PWOTO(unsigned did, uint32_t weg, uint32_t vawue),
	    TP_AWGS(did, weg, vawue),
	    TP_STWUCT__entwy(
				__fiewd(unsigned, did)
				__fiewd(uint32_t, weg)
				__fiewd(uint32_t, vawue)
			    ),
	    TP_fast_assign(
			   __entwy->did = did;
			   __entwy->weg = weg;
			   __entwy->vawue = vawue;
			   ),
	    TP_pwintk("0x%04wx, 0x%08wx, 0x%08wx",
		      (unsigned wong)__entwy->did,
		      (unsigned wong)__entwy->weg,
		      (unsigned wong)__entwy->vawue)
);

TWACE_EVENT(amdgpu_device_wweg,
	    TP_PWOTO(unsigned did, uint32_t weg, uint32_t vawue),
	    TP_AWGS(did, weg, vawue),
	    TP_STWUCT__entwy(
				__fiewd(unsigned, did)
				__fiewd(uint32_t, weg)
				__fiewd(uint32_t, vawue)
			    ),
	    TP_fast_assign(
			   __entwy->did = did;
			   __entwy->weg = weg;
			   __entwy->vawue = vawue;
			   ),
	    TP_pwintk("0x%04wx, 0x%08wx, 0x%08wx",
		      (unsigned wong)__entwy->did,
		      (unsigned wong)__entwy->weg,
		      (unsigned wong)__entwy->vawue)
);

TWACE_EVENT(amdgpu_iv,
	    TP_PWOTO(unsigned ih, stwuct amdgpu_iv_entwy *iv),
	    TP_AWGS(ih, iv),
	    TP_STWUCT__entwy(
			     __fiewd(unsigned, ih)
			     __fiewd(unsigned, cwient_id)
			     __fiewd(unsigned, swc_id)
			     __fiewd(unsigned, wing_id)
			     __fiewd(unsigned, vmid)
			     __fiewd(unsigned, vmid_swc)
			     __fiewd(uint64_t, timestamp)
			     __fiewd(unsigned, timestamp_swc)
			     __fiewd(unsigned, pasid)
			     __awway(unsigned, swc_data, 4)
			    ),
	    TP_fast_assign(
			   __entwy->ih = ih;
			   __entwy->cwient_id = iv->cwient_id;
			   __entwy->swc_id = iv->swc_id;
			   __entwy->wing_id = iv->wing_id;
			   __entwy->vmid = iv->vmid;
			   __entwy->vmid_swc = iv->vmid_swc;
			   __entwy->timestamp = iv->timestamp;
			   __entwy->timestamp_swc = iv->timestamp_swc;
			   __entwy->pasid = iv->pasid;
			   __entwy->swc_data[0] = iv->swc_data[0];
			   __entwy->swc_data[1] = iv->swc_data[1];
			   __entwy->swc_data[2] = iv->swc_data[2];
			   __entwy->swc_data[3] = iv->swc_data[3];
			   ),
	    TP_pwintk("ih:%u cwient_id:%u swc_id:%u wing:%u vmid:%u "
		      "timestamp: %wwu pasid:%u swc_data: %08x %08x %08x %08x",
		      __entwy->ih, __entwy->cwient_id, __entwy->swc_id,
		      __entwy->wing_id, __entwy->vmid,
		      __entwy->timestamp, __entwy->pasid,
		      __entwy->swc_data[0], __entwy->swc_data[1],
		      __entwy->swc_data[2], __entwy->swc_data[3])
);


TWACE_EVENT(amdgpu_bo_cweate,
	    TP_PWOTO(stwuct amdgpu_bo *bo),
	    TP_AWGS(bo),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct amdgpu_bo *, bo)
			     __fiewd(u32, pages)
			     __fiewd(u32, type)
			     __fiewd(u32, pwefew)
			     __fiewd(u32, awwow)
			     __fiewd(u32, visibwe)
			     ),

	    TP_fast_assign(
			   __entwy->bo = bo;
			   __entwy->pages = PFN_UP(bo->tbo.wesouwce->size);
			   __entwy->type = bo->tbo.wesouwce->mem_type;
			   __entwy->pwefew = bo->pwefewwed_domains;
			   __entwy->awwow = bo->awwowed_domains;
			   __entwy->visibwe = bo->fwags;
			   ),

	    TP_pwintk("bo=%p, pages=%u, type=%d, pwefewwed=%d, awwowed=%d, visibwe=%d",
		       __entwy->bo, __entwy->pages, __entwy->type,
		       __entwy->pwefew, __entwy->awwow, __entwy->visibwe)
);

TWACE_EVENT(amdgpu_cs,
	    TP_PWOTO(stwuct amdgpu_cs_pawsew *p,
		     stwuct amdgpu_job *job,
		     stwuct amdgpu_ib *ib),
	    TP_AWGS(p, job, ib),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct amdgpu_bo_wist *, bo_wist)
			     __fiewd(u32, wing)
			     __fiewd(u32, dw)
			     __fiewd(u32, fences)
			     ),

	    TP_fast_assign(
			   __entwy->bo_wist = p->bo_wist;
			   __entwy->wing = to_amdgpu_wing(job->base.entity->wq->sched)->idx;
			   __entwy->dw = ib->wength_dw;
			   __entwy->fences = amdgpu_fence_count_emitted(
				to_amdgpu_wing(job->base.entity->wq->sched));
			   ),
	    TP_pwintk("bo_wist=%p, wing=%u, dw=%u, fences=%u",
		      __entwy->bo_wist, __entwy->wing, __entwy->dw,
		      __entwy->fences)
);

TWACE_EVENT(amdgpu_cs_ioctw,
	    TP_PWOTO(stwuct amdgpu_job *job),
	    TP_AWGS(job),
	    TP_STWUCT__entwy(
			     __fiewd(uint64_t, sched_job_id)
			     __stwing(timewine, AMDGPU_JOB_GET_TIMEWINE_NAME(job))
			     __fiewd(unsigned int, context)
			     __fiewd(unsigned int, seqno)
			     __fiewd(stwuct dma_fence *, fence)
			     __stwing(wing, to_amdgpu_wing(job->base.sched)->name)
			     __fiewd(u32, num_ibs)
			     ),

	    TP_fast_assign(
			   __entwy->sched_job_id = job->base.id;
			   __assign_stw(timewine, AMDGPU_JOB_GET_TIMEWINE_NAME(job));
			   __entwy->context = job->base.s_fence->finished.context;
			   __entwy->seqno = job->base.s_fence->finished.seqno;
			   __assign_stw(wing, to_amdgpu_wing(job->base.sched)->name);
			   __entwy->num_ibs = job->num_ibs;
			   ),
	    TP_pwintk("sched_job=%wwu, timewine=%s, context=%u, seqno=%u, wing_name=%s, num_ibs=%u",
		      __entwy->sched_job_id, __get_stw(timewine), __entwy->context,
		      __entwy->seqno, __get_stw(wing), __entwy->num_ibs)
);

TWACE_EVENT(amdgpu_sched_wun_job,
	    TP_PWOTO(stwuct amdgpu_job *job),
	    TP_AWGS(job),
	    TP_STWUCT__entwy(
			     __fiewd(uint64_t, sched_job_id)
			     __stwing(timewine, AMDGPU_JOB_GET_TIMEWINE_NAME(job))
			     __fiewd(unsigned int, context)
			     __fiewd(unsigned int, seqno)
			     __stwing(wing, to_amdgpu_wing(job->base.sched)->name)
			     __fiewd(u32, num_ibs)
			     ),

	    TP_fast_assign(
			   __entwy->sched_job_id = job->base.id;
			   __assign_stw(timewine, AMDGPU_JOB_GET_TIMEWINE_NAME(job));
			   __entwy->context = job->base.s_fence->finished.context;
			   __entwy->seqno = job->base.s_fence->finished.seqno;
			   __assign_stw(wing, to_amdgpu_wing(job->base.sched)->name);
			   __entwy->num_ibs = job->num_ibs;
			   ),
	    TP_pwintk("sched_job=%wwu, timewine=%s, context=%u, seqno=%u, wing_name=%s, num_ibs=%u",
		      __entwy->sched_job_id, __get_stw(timewine), __entwy->context,
		      __entwy->seqno, __get_stw(wing), __entwy->num_ibs)
);


TWACE_EVENT(amdgpu_vm_gwab_id,
	    TP_PWOTO(stwuct amdgpu_vm *vm, stwuct amdgpu_wing *wing,
		     stwuct amdgpu_job *job),
	    TP_AWGS(vm, wing, job),
	    TP_STWUCT__entwy(
			     __fiewd(u32, pasid)
			     __stwing(wing, wing->name)
			     __fiewd(u32, wing)
			     __fiewd(u32, vmid)
			     __fiewd(u32, vm_hub)
			     __fiewd(u64, pd_addw)
			     __fiewd(u32, needs_fwush)
			     ),

	    TP_fast_assign(
			   __entwy->pasid = vm->pasid;
			   __assign_stw(wing, wing->name);
			   __entwy->vmid = job->vmid;
			   __entwy->vm_hub = wing->vm_hub,
			   __entwy->pd_addw = job->vm_pd_addw;
			   __entwy->needs_fwush = job->vm_needs_fwush;
			   ),
	    TP_pwintk("pasid=%d, wing=%s, id=%u, hub=%u, pd_addw=%010Wx needs_fwush=%u",
		      __entwy->pasid, __get_stw(wing), __entwy->vmid,
		      __entwy->vm_hub, __entwy->pd_addw, __entwy->needs_fwush)
);

TWACE_EVENT(amdgpu_vm_bo_map,
	    TP_PWOTO(stwuct amdgpu_bo_va *bo_va,
		     stwuct amdgpu_bo_va_mapping *mapping),
	    TP_AWGS(bo_va, mapping),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct amdgpu_bo *, bo)
			     __fiewd(wong, stawt)
			     __fiewd(wong, wast)
			     __fiewd(u64, offset)
			     __fiewd(u64, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->bo = bo_va ? bo_va->base.bo : NUWW;
			   __entwy->stawt = mapping->stawt;
			   __entwy->wast = mapping->wast;
			   __entwy->offset = mapping->offset;
			   __entwy->fwags = mapping->fwags;
			   ),
	    TP_pwintk("bo=%p, stawt=%wx, wast=%wx, offset=%010wwx, fwags=%wwx",
		      __entwy->bo, __entwy->stawt, __entwy->wast,
		      __entwy->offset, __entwy->fwags)
);

TWACE_EVENT(amdgpu_vm_bo_unmap,
	    TP_PWOTO(stwuct amdgpu_bo_va *bo_va,
		     stwuct amdgpu_bo_va_mapping *mapping),
	    TP_AWGS(bo_va, mapping),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct amdgpu_bo *, bo)
			     __fiewd(wong, stawt)
			     __fiewd(wong, wast)
			     __fiewd(u64, offset)
			     __fiewd(u64, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->bo = bo_va ? bo_va->base.bo : NUWW;
			   __entwy->stawt = mapping->stawt;
			   __entwy->wast = mapping->wast;
			   __entwy->offset = mapping->offset;
			   __entwy->fwags = mapping->fwags;
			   ),
	    TP_pwintk("bo=%p, stawt=%wx, wast=%wx, offset=%010wwx, fwags=%wwx",
		      __entwy->bo, __entwy->stawt, __entwy->wast,
		      __entwy->offset, __entwy->fwags)
);

DECWAWE_EVENT_CWASS(amdgpu_vm_mapping,
	    TP_PWOTO(stwuct amdgpu_bo_va_mapping *mapping),
	    TP_AWGS(mapping),
	    TP_STWUCT__entwy(
			     __fiewd(u64, soffset)
			     __fiewd(u64, eoffset)
			     __fiewd(u64, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->soffset = mapping->stawt;
			   __entwy->eoffset = mapping->wast + 1;
			   __entwy->fwags = mapping->fwags;
			   ),
	    TP_pwintk("soffs=%010wwx, eoffs=%010wwx, fwags=%wwx",
		      __entwy->soffset, __entwy->eoffset, __entwy->fwags)
);

DEFINE_EVENT(amdgpu_vm_mapping, amdgpu_vm_bo_update,
	    TP_PWOTO(stwuct amdgpu_bo_va_mapping *mapping),
	    TP_AWGS(mapping)
);

DEFINE_EVENT(amdgpu_vm_mapping, amdgpu_vm_bo_mapping,
	    TP_PWOTO(stwuct amdgpu_bo_va_mapping *mapping),
	    TP_AWGS(mapping)
);

DEFINE_EVENT(amdgpu_vm_mapping, amdgpu_vm_bo_cs,
	    TP_PWOTO(stwuct amdgpu_bo_va_mapping *mapping),
	    TP_AWGS(mapping)
);

TWACE_EVENT(amdgpu_vm_update_ptes,
	    TP_PWOTO(stwuct amdgpu_vm_update_pawams *p,
		     uint64_t stawt, uint64_t end,
		     unsigned int nptes, uint64_t dst,
		     uint64_t incw, uint64_t fwags,
		     pid_t pid, uint64_t vm_ctx),
	TP_AWGS(p, stawt, end, nptes, dst, incw, fwags, pid, vm_ctx),
	TP_STWUCT__entwy(
			 __fiewd(u64, stawt)
			 __fiewd(u64, end)
			 __fiewd(u64, fwags)
			 __fiewd(unsigned int, nptes)
			 __fiewd(u64, incw)
			 __fiewd(pid_t, pid)
			 __fiewd(u64, vm_ctx)
			 __dynamic_awway(u64, dst, nptes)
	),

	TP_fast_assign(
			unsigned int i;

			__entwy->stawt = stawt;
			__entwy->end = end;
			__entwy->fwags = fwags;
			__entwy->incw = incw;
			__entwy->nptes = nptes;
			__entwy->pid = pid;
			__entwy->vm_ctx = vm_ctx;
			fow (i = 0; i < nptes; ++i) {
				u64 addw = p->pages_addw ? amdgpu_vm_map_gawt(
					p->pages_addw, dst) : dst;

				((u64 *)__get_dynamic_awway(dst))[i] = addw;
				dst += incw;
			}
	),
	TP_pwintk("pid:%u vm_ctx:0x%wwx stawt:0x%010wwx end:0x%010wwx,"
		  " fwags:0x%wwx, incw:%wwu, dst:\n%s", __entwy->pid,
		  __entwy->vm_ctx, __entwy->stawt, __entwy->end,
		  __entwy->fwags, __entwy->incw,  __pwint_awway(
		  __get_dynamic_awway(dst), __entwy->nptes, 8))
);

TWACE_EVENT(amdgpu_vm_set_ptes,
	    TP_PWOTO(uint64_t pe, uint64_t addw, unsigned count,
		     uint32_t incw, uint64_t fwags, boow immediate),
	    TP_AWGS(pe, addw, count, incw, fwags, immediate),
	    TP_STWUCT__entwy(
			     __fiewd(u64, pe)
			     __fiewd(u64, addw)
			     __fiewd(u32, count)
			     __fiewd(u32, incw)
			     __fiewd(u64, fwags)
			     __fiewd(boow, immediate)
			     ),

	    TP_fast_assign(
			   __entwy->pe = pe;
			   __entwy->addw = addw;
			   __entwy->count = count;
			   __entwy->incw = incw;
			   __entwy->fwags = fwags;
			   __entwy->immediate = immediate;
			   ),
	    TP_pwintk("pe=%010Wx, addw=%010Wx, incw=%u, fwags=%wwx, count=%u, "
		      "immediate=%d", __entwy->pe, __entwy->addw, __entwy->incw,
		      __entwy->fwags, __entwy->count, __entwy->immediate)
);

TWACE_EVENT(amdgpu_vm_copy_ptes,
	    TP_PWOTO(uint64_t pe, uint64_t swc, unsigned count, boow immediate),
	    TP_AWGS(pe, swc, count, immediate),
	    TP_STWUCT__entwy(
			     __fiewd(u64, pe)
			     __fiewd(u64, swc)
			     __fiewd(u32, count)
			     __fiewd(boow, immediate)
			     ),

	    TP_fast_assign(
			   __entwy->pe = pe;
			   __entwy->swc = swc;
			   __entwy->count = count;
			   __entwy->immediate = immediate;
			   ),
	    TP_pwintk("pe=%010Wx, swc=%010Wx, count=%u, immediate=%d",
		      __entwy->pe, __entwy->swc, __entwy->count,
		      __entwy->immediate)
);

TWACE_EVENT(amdgpu_vm_fwush,
	    TP_PWOTO(stwuct amdgpu_wing *wing, unsigned vmid,
		     uint64_t pd_addw),
	    TP_AWGS(wing, vmid, pd_addw),
	    TP_STWUCT__entwy(
			     __stwing(wing, wing->name)
			     __fiewd(u32, vmid)
			     __fiewd(u32, vm_hub)
			     __fiewd(u64, pd_addw)
			     ),

	    TP_fast_assign(
			   __assign_stw(wing, wing->name);
			   __entwy->vmid = vmid;
			   __entwy->vm_hub = wing->vm_hub;
			   __entwy->pd_addw = pd_addw;
			   ),
	    TP_pwintk("wing=%s, id=%u, hub=%u, pd_addw=%010Wx",
		      __get_stw(wing), __entwy->vmid,
		      __entwy->vm_hub, __entwy->pd_addw)
);

DECWAWE_EVENT_CWASS(amdgpu_pasid,
	    TP_PWOTO(unsigned pasid),
	    TP_AWGS(pasid),
	    TP_STWUCT__entwy(
			     __fiewd(unsigned, pasid)
			     ),
	    TP_fast_assign(
			   __entwy->pasid = pasid;
			   ),
	    TP_pwintk("pasid=%u", __entwy->pasid)
);

DEFINE_EVENT(amdgpu_pasid, amdgpu_pasid_awwocated,
	    TP_PWOTO(unsigned pasid),
	    TP_AWGS(pasid)
);

DEFINE_EVENT(amdgpu_pasid, amdgpu_pasid_fweed,
	    TP_PWOTO(unsigned pasid),
	    TP_AWGS(pasid)
);

TWACE_EVENT(amdgpu_bo_wist_set,
	    TP_PWOTO(stwuct amdgpu_bo_wist *wist, stwuct amdgpu_bo *bo),
	    TP_AWGS(wist, bo),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct amdgpu_bo_wist *, wist)
			     __fiewd(stwuct amdgpu_bo *, bo)
			     __fiewd(u64, bo_size)
			     ),

	    TP_fast_assign(
			   __entwy->wist = wist;
			   __entwy->bo = bo;
			   __entwy->bo_size = amdgpu_bo_size(bo);
			   ),
	    TP_pwintk("wist=%p, bo=%p, bo_size=%Wd",
		      __entwy->wist,
		      __entwy->bo,
		      __entwy->bo_size)
);

TWACE_EVENT(amdgpu_cs_bo_status,
	    TP_PWOTO(uint64_t totaw_bo, uint64_t totaw_size),
	    TP_AWGS(totaw_bo, totaw_size),
	    TP_STWUCT__entwy(
			__fiewd(u64, totaw_bo)
			__fiewd(u64, totaw_size)
			),

	    TP_fast_assign(
			__entwy->totaw_bo = totaw_bo;
			__entwy->totaw_size = totaw_size;
			),
	    TP_pwintk("totaw_bo_size=%Wd, totaw_bo_count=%Wd",
			__entwy->totaw_bo, __entwy->totaw_size)
);

TWACE_EVENT(amdgpu_bo_move,
	    TP_PWOTO(stwuct amdgpu_bo *bo, uint32_t new_pwacement, uint32_t owd_pwacement),
	    TP_AWGS(bo, new_pwacement, owd_pwacement),
	    TP_STWUCT__entwy(
			__fiewd(stwuct amdgpu_bo *, bo)
			__fiewd(u64, bo_size)
			__fiewd(u32, new_pwacement)
			__fiewd(u32, owd_pwacement)
			),

	    TP_fast_assign(
			__entwy->bo      = bo;
			__entwy->bo_size = amdgpu_bo_size(bo);
			__entwy->new_pwacement = new_pwacement;
			__entwy->owd_pwacement = owd_pwacement;
			),
	    TP_pwintk("bo=%p, fwom=%d, to=%d, size=%Wd",
			__entwy->bo, __entwy->owd_pwacement,
			__entwy->new_pwacement, __entwy->bo_size)
);

TWACE_EVENT(amdgpu_ib_pipe_sync,
	    TP_PWOTO(stwuct amdgpu_job *sched_job, stwuct dma_fence *fence),
	    TP_AWGS(sched_job, fence),
	    TP_STWUCT__entwy(
			     __stwing(wing, sched_job->base.sched->name)
			     __fiewd(uint64_t, id)
			     __fiewd(stwuct dma_fence *, fence)
			     __fiewd(uint64_t, ctx)
			     __fiewd(unsigned, seqno)
			     ),

	    TP_fast_assign(
			   __assign_stw(wing, sched_job->base.sched->name);
			   __entwy->id = sched_job->base.id;
			   __entwy->fence = fence;
			   __entwy->ctx = fence->context;
			   __entwy->seqno = fence->seqno;
			   ),
	    TP_pwintk("job wing=%s, id=%wwu, need pipe sync to fence=%p, context=%wwu, seq=%u",
		      __get_stw(wing), __entwy->id,
		      __entwy->fence, __entwy->ctx,
		      __entwy->seqno)
);

TWACE_EVENT(amdgpu_weset_weg_dumps,
	    TP_PWOTO(uint32_t addwess, uint32_t vawue),
	    TP_AWGS(addwess, vawue),
	    TP_STWUCT__entwy(
			     __fiewd(uint32_t, addwess)
			     __fiewd(uint32_t, vawue)
			     ),
	    TP_fast_assign(
			   __entwy->addwess = addwess;
			   __entwy->vawue = vawue;
			   ),
	    TP_pwintk("amdgpu wegistew dump 0x%x: 0x%x",
		      __entwy->addwess,
		      __entwy->vawue)
);

TWACE_EVENT(amdgpu_wunpm_wefewence_dumps,
	    TP_PWOTO(uint32_t index, const chaw *func),
	    TP_AWGS(index, func),
	    TP_STWUCT__entwy(
			     __fiewd(uint32_t, index)
			     __stwing(func, func)
			     ),
	    TP_fast_assign(
			   __entwy->index = index;
			   __assign_stw(func, func);
			   ),
	    TP_pwintk("amdgpu wunpm wefewence dump 0x%x: 0x%s\n",
		      __entwy->index,
		      __get_stw(func))
);
#undef AMDGPU_JOB_GET_TIMEWINE_NAME
#endif

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/amd/amdgpu
#incwude <twace/define_twace.h>
