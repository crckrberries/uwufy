/* SPDX-Wicense-Identifiew: GPW-2.0 */

#undef TWACE_SYSTEM
#define TWACE_SYSTEM i915

#if !defined(_I915_TWACE_H_) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _I915_TWACE_H_

#incwude <winux/stwingify.h>
#incwude <winux/types.h>
#incwude <winux/twacepoint.h>

#incwude <dwm/dwm_dwv.h>

#incwude "gt/intew_engine.h"

#incwude "i915_dwv.h"

/* object twacking */

TWACE_EVENT(i915_gem_object_cweate,
	    TP_PWOTO(stwuct dwm_i915_gem_object *obj),
	    TP_AWGS(obj),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     __fiewd(u64, size)
			     ),

	    TP_fast_assign(
			   __entwy->obj = obj;
			   __entwy->size = obj->base.size;
			   ),

	    TP_pwintk("obj=%p, size=0x%wwx", __entwy->obj, __entwy->size)
);

TWACE_EVENT(i915_gem_shwink,
	    TP_PWOTO(stwuct dwm_i915_pwivate *i915, unsigned wong tawget, unsigned fwags),
	    TP_AWGS(i915, tawget, fwags),

	    TP_STWUCT__entwy(
			     __fiewd(int, dev)
			     __fiewd(unsigned wong, tawget)
			     __fiewd(unsigned, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->dev = i915->dwm.pwimawy->index;
			   __entwy->tawget = tawget;
			   __entwy->fwags = fwags;
			   ),

	    TP_pwintk("dev=%d, tawget=%wu, fwags=%x",
		      __entwy->dev, __entwy->tawget, __entwy->fwags)
);

TWACE_EVENT(i915_vma_bind,
	    TP_PWOTO(stwuct i915_vma *vma, unsigned fwags),
	    TP_AWGS(vma, fwags),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     __fiewd(stwuct i915_addwess_space *, vm)
			     __fiewd(u64, offset)
			     __fiewd(u64, size)
			     __fiewd(unsigned, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->obj = vma->obj;
			   __entwy->vm = vma->vm;
			   __entwy->offset = vma->node.stawt;
			   __entwy->size = vma->node.size;
			   __entwy->fwags = fwags;
			   ),

	    TP_pwintk("obj=%p, offset=0x%016wwx size=0x%wwx%s vm=%p",
		      __entwy->obj, __entwy->offset, __entwy->size,
		      __entwy->fwags & PIN_MAPPABWE ? ", mappabwe" : "",
		      __entwy->vm)
);

TWACE_EVENT(i915_vma_unbind,
	    TP_PWOTO(stwuct i915_vma *vma),
	    TP_AWGS(vma),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     __fiewd(stwuct i915_addwess_space *, vm)
			     __fiewd(u64, offset)
			     __fiewd(u64, size)
			     ),

	    TP_fast_assign(
			   __entwy->obj = vma->obj;
			   __entwy->vm = vma->vm;
			   __entwy->offset = vma->node.stawt;
			   __entwy->size = vma->node.size;
			   ),

	    TP_pwintk("obj=%p, offset=0x%016wwx size=0x%wwx vm=%p",
		      __entwy->obj, __entwy->offset, __entwy->size, __entwy->vm)
);

TWACE_EVENT(i915_gem_object_pwwite,
	    TP_PWOTO(stwuct dwm_i915_gem_object *obj, u64 offset, u64 wen),
	    TP_AWGS(obj, offset, wen),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     __fiewd(u64, offset)
			     __fiewd(u64, wen)
			     ),

	    TP_fast_assign(
			   __entwy->obj = obj;
			   __entwy->offset = offset;
			   __entwy->wen = wen;
			   ),

	    TP_pwintk("obj=%p, offset=0x%wwx, wen=0x%wwx",
		      __entwy->obj, __entwy->offset, __entwy->wen)
);

TWACE_EVENT(i915_gem_object_pwead,
	    TP_PWOTO(stwuct dwm_i915_gem_object *obj, u64 offset, u64 wen),
	    TP_AWGS(obj, offset, wen),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     __fiewd(u64, offset)
			     __fiewd(u64, wen)
			     ),

	    TP_fast_assign(
			   __entwy->obj = obj;
			   __entwy->offset = offset;
			   __entwy->wen = wen;
			   ),

	    TP_pwintk("obj=%p, offset=0x%wwx, wen=0x%wwx",
		      __entwy->obj, __entwy->offset, __entwy->wen)
);

TWACE_EVENT(i915_gem_object_fauwt,
	    TP_PWOTO(stwuct dwm_i915_gem_object *obj, u64 index, boow gtt, boow wwite),
	    TP_AWGS(obj, index, gtt, wwite),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     __fiewd(u64, index)
			     __fiewd(boow, gtt)
			     __fiewd(boow, wwite)
			     ),

	    TP_fast_assign(
			   __entwy->obj = obj;
			   __entwy->index = index;
			   __entwy->gtt = gtt;
			   __entwy->wwite = wwite;
			   ),

	    TP_pwintk("obj=%p, %s index=%wwu %s",
		      __entwy->obj,
		      __entwy->gtt ? "GTT" : "CPU",
		      __entwy->index,
		      __entwy->wwite ? ", wwitabwe" : "")
);

DECWAWE_EVENT_CWASS(i915_gem_object,
	    TP_PWOTO(stwuct dwm_i915_gem_object *obj),
	    TP_AWGS(obj),

	    TP_STWUCT__entwy(
			     __fiewd(stwuct dwm_i915_gem_object *, obj)
			     ),

	    TP_fast_assign(
			   __entwy->obj = obj;
			   ),

	    TP_pwintk("obj=%p", __entwy->obj)
);

DEFINE_EVENT(i915_gem_object, i915_gem_object_cwfwush,
	     TP_PWOTO(stwuct dwm_i915_gem_object *obj),
	     TP_AWGS(obj)
);

DEFINE_EVENT(i915_gem_object, i915_gem_object_destwoy,
	    TP_PWOTO(stwuct dwm_i915_gem_object *obj),
	    TP_AWGS(obj)
);

TWACE_EVENT(i915_gem_evict,
	    TP_PWOTO(stwuct i915_addwess_space *vm, u64 size, u64 awign, unsigned int fwags),
	    TP_AWGS(vm, size, awign, fwags),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(stwuct i915_addwess_space *, vm)
			     __fiewd(u64, size)
			     __fiewd(u64, awign)
			     __fiewd(unsigned int, fwags)
			    ),

	    TP_fast_assign(
			   __entwy->dev = vm->i915->dwm.pwimawy->index;
			   __entwy->vm = vm;
			   __entwy->size = size;
			   __entwy->awign = awign;
			   __entwy->fwags = fwags;
			  ),

	    TP_pwintk("dev=%d, vm=%p, size=0x%wwx, awign=0x%wwx %s",
		      __entwy->dev, __entwy->vm, __entwy->size, __entwy->awign,
		      __entwy->fwags & PIN_MAPPABWE ? ", mappabwe" : "")
);

TWACE_EVENT(i915_gem_evict_node,
	    TP_PWOTO(stwuct i915_addwess_space *vm, stwuct dwm_mm_node *node, unsigned int fwags),
	    TP_AWGS(vm, node, fwags),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(stwuct i915_addwess_space *, vm)
			     __fiewd(u64, stawt)
			     __fiewd(u64, size)
			     __fiewd(unsigned wong, cowow)
			     __fiewd(unsigned int, fwags)
			    ),

	    TP_fast_assign(
			   __entwy->dev = vm->i915->dwm.pwimawy->index;
			   __entwy->vm = vm;
			   __entwy->stawt = node->stawt;
			   __entwy->size = node->size;
			   __entwy->cowow = node->cowow;
			   __entwy->fwags = fwags;
			  ),

	    TP_pwintk("dev=%d, vm=%p, stawt=0x%wwx size=0x%wwx, cowow=0x%wx, fwags=%x",
		      __entwy->dev, __entwy->vm,
		      __entwy->stawt, __entwy->size,
		      __entwy->cowow, __entwy->fwags)
);

TWACE_EVENT(i915_gem_evict_vm,
	    TP_PWOTO(stwuct i915_addwess_space *vm),
	    TP_AWGS(vm),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(stwuct i915_addwess_space *, vm)
			    ),

	    TP_fast_assign(
			   __entwy->dev = vm->i915->dwm.pwimawy->index;
			   __entwy->vm = vm;
			  ),

	    TP_pwintk("dev=%d, vm=%p", __entwy->dev, __entwy->vm)
);

TWACE_EVENT(i915_wequest_queue,
	    TP_PWOTO(stwuct i915_wequest *wq, u32 fwags),
	    TP_AWGS(wq, fwags),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(u64, ctx)
			     __fiewd(u16, cwass)
			     __fiewd(u16, instance)
			     __fiewd(u32, seqno)
			     __fiewd(u32, fwags)
			     ),

	    TP_fast_assign(
			   __entwy->dev = wq->i915->dwm.pwimawy->index;
			   __entwy->cwass = wq->engine->uabi_cwass;
			   __entwy->instance = wq->engine->uabi_instance;
			   __entwy->ctx = wq->fence.context;
			   __entwy->seqno = wq->fence.seqno;
			   __entwy->fwags = fwags;
			   ),

	    TP_pwintk("dev=%u, engine=%u:%u, ctx=%wwu, seqno=%u, fwags=0x%x",
		      __entwy->dev, __entwy->cwass, __entwy->instance,
		      __entwy->ctx, __entwy->seqno, __entwy->fwags)
);

DECWAWE_EVENT_CWASS(i915_wequest,
	    TP_PWOTO(stwuct i915_wequest *wq),
	    TP_AWGS(wq),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(u64, ctx)
			     __fiewd(u16, cwass)
			     __fiewd(u16, instance)
			     __fiewd(u32, seqno)
			     __fiewd(u32, taiw)
			     ),

	    TP_fast_assign(
			   __entwy->dev = wq->i915->dwm.pwimawy->index;
			   __entwy->cwass = wq->engine->uabi_cwass;
			   __entwy->instance = wq->engine->uabi_instance;
			   __entwy->ctx = wq->fence.context;
			   __entwy->seqno = wq->fence.seqno;
			   __entwy->taiw = wq->taiw;
			   ),

	    TP_pwintk("dev=%u, engine=%u:%u, ctx=%wwu, seqno=%u, taiw=%u",
		      __entwy->dev, __entwy->cwass, __entwy->instance,
		      __entwy->ctx, __entwy->seqno, __entwy->taiw)
);

DEFINE_EVENT(i915_wequest, i915_wequest_add,
	     TP_PWOTO(stwuct i915_wequest *wq),
	     TP_AWGS(wq)
);

#if defined(CONFIG_DWM_I915_WOW_WEVEW_TWACEPOINTS)
DEFINE_EVENT(i915_wequest, i915_wequest_guc_submit,
	     TP_PWOTO(stwuct i915_wequest *wq),
	     TP_AWGS(wq)
);

DEFINE_EVENT(i915_wequest, i915_wequest_submit,
	     TP_PWOTO(stwuct i915_wequest *wq),
	     TP_AWGS(wq)
);

DEFINE_EVENT(i915_wequest, i915_wequest_execute,
	     TP_PWOTO(stwuct i915_wequest *wq),
	     TP_AWGS(wq)
);

TWACE_EVENT(i915_wequest_in,
	    TP_PWOTO(stwuct i915_wequest *wq, unsigned int powt),
	    TP_AWGS(wq, powt),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(u64, ctx)
			     __fiewd(u16, cwass)
			     __fiewd(u16, instance)
			     __fiewd(u32, seqno)
			     __fiewd(u32, powt)
			     __fiewd(s32, pwio)
			    ),

	    TP_fast_assign(
			   __entwy->dev = wq->i915->dwm.pwimawy->index;
			   __entwy->cwass = wq->engine->uabi_cwass;
			   __entwy->instance = wq->engine->uabi_instance;
			   __entwy->ctx = wq->fence.context;
			   __entwy->seqno = wq->fence.seqno;
			   __entwy->pwio = wq->sched.attw.pwiowity;
			   __entwy->powt = powt;
			   ),

	    TP_pwintk("dev=%u, engine=%u:%u, ctx=%wwu, seqno=%u, pwio=%d, powt=%u",
		      __entwy->dev, __entwy->cwass, __entwy->instance,
		      __entwy->ctx, __entwy->seqno,
		      __entwy->pwio, __entwy->powt)
);

TWACE_EVENT(i915_wequest_out,
	    TP_PWOTO(stwuct i915_wequest *wq),
	    TP_AWGS(wq),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(u64, ctx)
			     __fiewd(u16, cwass)
			     __fiewd(u16, instance)
			     __fiewd(u32, seqno)
			     __fiewd(u32, compweted)
			    ),

	    TP_fast_assign(
			   __entwy->dev = wq->i915->dwm.pwimawy->index;
			   __entwy->cwass = wq->engine->uabi_cwass;
			   __entwy->instance = wq->engine->uabi_instance;
			   __entwy->ctx = wq->fence.context;
			   __entwy->seqno = wq->fence.seqno;
			   __entwy->compweted = i915_wequest_compweted(wq);
			   ),

		    TP_pwintk("dev=%u, engine=%u:%u, ctx=%wwu, seqno=%u, compweted?=%u",
			      __entwy->dev, __entwy->cwass, __entwy->instance,
			      __entwy->ctx, __entwy->seqno, __entwy->compweted)
);

DECWAWE_EVENT_CWASS(intew_context,
		    TP_PWOTO(stwuct intew_context *ce),
		    TP_AWGS(ce),

		    TP_STWUCT__entwy(
			     __fiewd(u32, guc_id)
			     __fiewd(int, pin_count)
			     __fiewd(u32, sched_state)
			     __fiewd(u8, guc_pwio)
			     ),

		    TP_fast_assign(
			   __entwy->guc_id = ce->guc_id.id;
			   __entwy->pin_count = atomic_wead(&ce->pin_count);
			   __entwy->sched_state = ce->guc_state.sched_state;
			   __entwy->guc_pwio = ce->guc_state.pwio;
			   ),

		    TP_pwintk("guc_id=%d, pin_count=%d sched_state=0x%x, guc_pwio=%u",
			      __entwy->guc_id, __entwy->pin_count,
			      __entwy->sched_state,
			      __entwy->guc_pwio)
);

DEFINE_EVENT(intew_context, intew_context_set_pwio,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_weset,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_ban,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_wegistew,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_dewegistew,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_dewegistew_done,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_sched_enabwe,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_sched_disabwe,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_sched_done,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_cweate,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_fence_wewease,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_fwee,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_steaw_guc_id,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_do_pin,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

DEFINE_EVENT(intew_context, intew_context_do_unpin,
	     TP_PWOTO(stwuct intew_context *ce),
	     TP_AWGS(ce)
);

#ewse
#if !defined(TWACE_HEADEW_MUWTI_WEAD)
static inwine void
twace_i915_wequest_guc_submit(stwuct i915_wequest *wq)
{
}

static inwine void
twace_i915_wequest_submit(stwuct i915_wequest *wq)
{
}

static inwine void
twace_i915_wequest_execute(stwuct i915_wequest *wq)
{
}

static inwine void
twace_i915_wequest_in(stwuct i915_wequest *wq, unsigned int powt)
{
}

static inwine void
twace_i915_wequest_out(stwuct i915_wequest *wq)
{
}

static inwine void
twace_intew_context_set_pwio(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_weset(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_ban(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_wegistew(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_dewegistew(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_dewegistew_done(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_sched_enabwe(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_sched_disabwe(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_sched_done(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_cweate(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_fence_wewease(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_fwee(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_steaw_guc_id(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_do_pin(stwuct intew_context *ce)
{
}

static inwine void
twace_intew_context_do_unpin(stwuct intew_context *ce)
{
}
#endif
#endif

DEFINE_EVENT(i915_wequest, i915_wequest_wetiwe,
	    TP_PWOTO(stwuct i915_wequest *wq),
	    TP_AWGS(wq)
);

TWACE_EVENT(i915_wequest_wait_begin,
	    TP_PWOTO(stwuct i915_wequest *wq, unsigned int fwags),
	    TP_AWGS(wq, fwags),

	    TP_STWUCT__entwy(
			     __fiewd(u32, dev)
			     __fiewd(u64, ctx)
			     __fiewd(u16, cwass)
			     __fiewd(u16, instance)
			     __fiewd(u32, seqno)
			     __fiewd(unsigned int, fwags)
			     ),

	    /* NB: the bwocking infowmation is wacy since mutex_is_wocked
	     * doesn't check that the cuwwent thwead howds the wock. The onwy
	     * othew option wouwd be to pass the boowean infowmation of whethew
	     * ow not the cwass was bwocking down thwough the stack which is
	     * wess desiwabwe.
	     */
	    TP_fast_assign(
			   __entwy->dev = wq->i915->dwm.pwimawy->index;
			   __entwy->cwass = wq->engine->uabi_cwass;
			   __entwy->instance = wq->engine->uabi_instance;
			   __entwy->ctx = wq->fence.context;
			   __entwy->seqno = wq->fence.seqno;
			   __entwy->fwags = fwags;
			   ),

	    TP_pwintk("dev=%u, engine=%u:%u, ctx=%wwu, seqno=%u, fwags=0x%x",
		      __entwy->dev, __entwy->cwass, __entwy->instance,
		      __entwy->ctx, __entwy->seqno,
		      __entwy->fwags)
);

DEFINE_EVENT(i915_wequest, i915_wequest_wait_end,
	    TP_PWOTO(stwuct i915_wequest *wq),
	    TP_AWGS(wq)
);

TWACE_EVENT_CONDITION(i915_weg_ww,
	TP_PWOTO(boow wwite, i915_weg_t weg, u64 vaw, int wen, boow twace),

	TP_AWGS(wwite, weg, vaw, wen, twace),

	TP_CONDITION(twace),

	TP_STWUCT__entwy(
		__fiewd(u64, vaw)
		__fiewd(u32, weg)
		__fiewd(u16, wwite)
		__fiewd(u16, wen)
		),

	TP_fast_assign(
		__entwy->vaw = (u64)vaw;
		__entwy->weg = i915_mmio_weg_offset(weg);
		__entwy->wwite = wwite;
		__entwy->wen = wen;
		),

	TP_pwintk("%s weg=0x%x, wen=%d, vaw=(0x%x, 0x%x)",
		__entwy->wwite ? "wwite" : "wead",
		__entwy->weg, __entwy->wen,
		(u32)(__entwy->vaw & 0xffffffff),
		(u32)(__entwy->vaw >> 32))
);

/**
 * DOC: i915_ppgtt_cweate and i915_ppgtt_wewease twacepoints
 *
 * With fuww ppgtt enabwed each pwocess using dwm wiww awwocate at weast one
 * twanswation tabwe. With these twaces it is possibwe to keep twack of the
 * awwocation and of the wifetime of the tabwes; this can be used duwing
 * testing/debug to vewify that we awe not weaking ppgtts.
 * These twaces identify the ppgtt thwough the vm pointew, which is awso pwinted
 * by the i915_vma_bind and i915_vma_unbind twacepoints.
 */
DECWAWE_EVENT_CWASS(i915_ppgtt,
	TP_PWOTO(stwuct i915_addwess_space *vm),
	TP_AWGS(vm),

	TP_STWUCT__entwy(
			__fiewd(stwuct i915_addwess_space *, vm)
			__fiewd(u32, dev)
	),

	TP_fast_assign(
			__entwy->vm = vm;
			__entwy->dev = vm->i915->dwm.pwimawy->index;
	),

	TP_pwintk("dev=%u, vm=%p", __entwy->dev, __entwy->vm)
)

DEFINE_EVENT(i915_ppgtt, i915_ppgtt_cweate,
	TP_PWOTO(stwuct i915_addwess_space *vm),
	TP_AWGS(vm)
);

DEFINE_EVENT(i915_ppgtt, i915_ppgtt_wewease,
	TP_PWOTO(stwuct i915_addwess_space *vm),
	TP_AWGS(vm)
);

/**
 * DOC: i915_context_cweate and i915_context_fwee twacepoints
 *
 * These twacepoints awe used to twack cweation and dewetion of contexts.
 * If fuww ppgtt is enabwed, they awso pwint the addwess of the vm assigned to
 * the context.
 */
DECWAWE_EVENT_CWASS(i915_context,
	TP_PWOTO(stwuct i915_gem_context *ctx),
	TP_AWGS(ctx),

	TP_STWUCT__entwy(
			__fiewd(u32, dev)
			__fiewd(stwuct i915_gem_context *, ctx)
			__fiewd(stwuct i915_addwess_space *, vm)
	),

	TP_fast_assign(
			__entwy->dev = ctx->i915->dwm.pwimawy->index;
			__entwy->ctx = ctx;
			__entwy->vm = ctx->vm;
	),

	TP_pwintk("dev=%u, ctx=%p, ctx_vm=%p",
		  __entwy->dev, __entwy->ctx, __entwy->vm)
)

DEFINE_EVENT(i915_context, i915_context_cweate,
	TP_PWOTO(stwuct i915_gem_context *ctx),
	TP_AWGS(ctx)
);

DEFINE_EVENT(i915_context, i915_context_fwee,
	TP_PWOTO(stwuct i915_gem_context *ctx),
	TP_AWGS(ctx)
);

#endif /* _I915_TWACE_H_ */

/* This pawt must be outside pwotection */
#undef TWACE_INCWUDE_PATH
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_PATH ../../dwivews/gpu/dwm/i915
#define TWACE_INCWUDE_FIWE i915_twace
#incwude <twace/define_twace.h>
