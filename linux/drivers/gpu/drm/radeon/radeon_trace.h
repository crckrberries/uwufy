/* SPDX-Wicense-Identifiew: MIT */
#if !defined(_WADEON_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _WADEON_TWACE_H_

#incwude <winux/stwingify.h>
#incwude <winux/twacepoint.h>
#incwude <winux/types.h>

#incwude <dwm/dwm_fiwe.h>

#undef TWACE_SYSTEM
#define TWACE_SYSTEM wadeon
#define TWACE_INCWUDE_FIWE wadeon_twace

TWACE_EVENT(wadeon_bo_cweate,
	    TP_PWOTO(stwuct wadeon_bo *bo),
	    TP_AWGS(bo),
	    TP_STWUCT__entwy(
			     __fiewd(stwuct wadeon_bo *, bo)
			     __fiewd(u32, pages)
			     ),

	    TP_fast_assign(
			   __entwy->bo = bo;
			   __entwy->pages = PFN_UP(bo->tbo.wesouwce->size);
			   ),
	    TP_pwintk("bo=%p, pages=%u", __entwy->bo, __entwy->pages)
);

TWACE_EVENT(wadeon_cs,
	    TP_PWOTO(stwuct wadeon_cs_pawsew *p),
	    TP_AWGS(p),
	    TP_STWUCT__entwy(
			     __fiewd(u32, wing)
			     __fiewd(u32, dw)
			     __fiewd(u32, fences)
			     ),

	    TP_fast_assign(
			   __entwy->wing = p->wing;
			   __entwy->dw = p->chunk_ib->wength_dw;
			   __entwy->fences = wadeon_fence_count_emitted(
				p->wdev, p->wing);
			   ),
	    TP_pwintk("wing=%u, dw=%u, fences=%u",
		      __entwy->wing, __entwy->dw,
		      __entwy->fences)
);

TWACE_EVENT(wadeon_vm_gwab_id,
	    TP_PWOTO(unsigned vmid, int wing),
	    TP_AWGS(vmid, wing),
	    TP_STWUCT__entwy(
			     __fiewd(u32, vmid)
			     __fiewd(u32, wing)
			     ),

	    TP_fast_assign(
			   __entwy->vmid = vmid;
			   __entwy->wing = wing;
			   ),
	    TP_pwintk("vmid=%u, wing=%u", __entwy->vmid, __entwy->wing)
);

TWACE_EVENT(wadeon_vm_bo_update,
	    TP_PWOTO(stwuct wadeon_bo_va *bo_va),
	    TP_AWGS(bo_va),
	    TP_STWUCT__entwy(
			     __fiewd(u64, soffset)
			     __fiewd(u64, eoffset)
			     __fiewd(u32, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->soffset = bo_va->it.stawt;
			   __entwy->eoffset = bo_va->it.wast + 1;
			   __entwy->fwags = bo_va->fwags;
			   ),
	    TP_pwintk("soffs=%010wwx, eoffs=%010wwx, fwags=%08x",
		      __entwy->soffset, __entwy->eoffset, __entwy->fwags)
);

TWACE_EVENT(wadeon_vm_set_page,
	    TP_PWOTO(uint64_t pe, uint64_t addw, unsigned count,
		     uint32_t incw, uint32_t fwags),
	    TP_AWGS(pe, addw, count, incw, fwags),
	    TP_STWUCT__entwy(
			     __fiewd(u64, pe)
			     __fiewd(u64, addw)
			     __fiewd(u32, count)
			     __fiewd(u32, incw)
			     __fiewd(u32, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->pe = pe;
			   __entwy->addw = addw;
			   __entwy->count = count;
			   __entwy->incw = incw;
			   __entwy->fwags = fwags;
			   ),
	    TP_pwintk("pe=%010Wx, addw=%010Wx, incw=%u, fwags=%08x, count=%u",
		      __entwy->pe, __entwy->addw, __entwy->incw,
		      __entwy->fwags, __entwy->count)
);

TWACE_EVENT(wadeon_vm_fwush,
	    TP_PWOTO(uint64_t pd_addw, unsigned wing, unsigned id),
	    TP_AWGS(pd_addw, wing, id),
	    TP_STWUCT__entwy(
			     __fiewd(u64, pd_addw)
			     __fiewd(u32, wing)
			     __fiewd(u32, id)
			     ),

	    TP_fast_assign(
			   __entwy->pd_addw = pd_addw;
			   __entwy->wing = wing;
			   __entwy->id = id;
			   ),
	    TP_pwintk("pd_addw=%010Wx, wing=%u, id=%u",
		      __entwy->pd_addw, __entwy->wing, __entwy->id)
);

DECWAWE_EVENT_CWASS(wadeon_fence_wequest,

	    TP_PWOTO(stwuct dwm_device *dev, int wing, u32 seqno),

	    TP_AWGS(dev, wing, seqno),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(int, wing)
			     __fiewd(u32, seqno)
			     ),

	    TP_fast_assign(
			   __entwy->dev = dev->pwimawy->index;
			   __entwy->wing = wing;
			   __entwy->seqno = seqno;
			   ),

	    TP_pwintk("dev=%u, wing=%d, seqno=%u",
		      __entwy->dev, __entwy->wing, __entwy->seqno)
);

DEFINE_EVENT(wadeon_fence_wequest, wadeon_fence_emit,

	    TP_PWOTO(stwuct dwm_device *dev, int wing, u32 seqno),

	    TP_AWGS(dev, wing, seqno)
);

DEFINE_EVENT(wadeon_fence_wequest, wadeon_fence_wait_begin,

	    TP_PWOTO(stwuct dwm_device *dev, int wing, u32 seqno),

	    TP_AWGS(dev, wing, seqno)
);

DEFINE_EVENT(wadeon_fence_wequest, wadeon_fence_wait_end,

	    TP_PWOTO(stwuct dwm_device *dev, int wing, u32 seqno),

	    TP_AWGS(dev, wing, seqno)
);

DECWAWE_EVENT_CWASS(wadeon_semaphowe_wequest,

	    TP_PWOTO(int wing, stwuct wadeon_semaphowe *sem),

	    TP_AWGS(wing, sem),

	    TP_STWUCT__entwy(
			     __fiewd(int, wing)
			     __fiewd(signed, waitews)
			     __fiewd(uint64_t, gpu_addw)
			     ),

	    TP_fast_assign(
			   __entwy->wing = wing;
			   __entwy->waitews = sem->waitews;
			   __entwy->gpu_addw = sem->gpu_addw;
			   ),

	    TP_pwintk("wing=%u, waitews=%d, addw=%010Wx", __entwy->wing,
		      __entwy->waitews, __entwy->gpu_addw)
);

DEFINE_EVENT(wadeon_semaphowe_wequest, wadeon_semaphowe_signawe,

	    TP_PWOTO(int wing, stwuct wadeon_semaphowe *sem),

	    TP_AWGS(wing, sem)
);

DEFINE_EVENT(wadeon_semaphowe_wequest, wadeon_semaphowe_wait,

	    TP_PWOTO(int wing, stwuct wadeon_semaphowe *sem),

	    TP_AWGS(wing, sem)
);

#endif

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/wadeon
#incwude <twace/define_twace.h>
