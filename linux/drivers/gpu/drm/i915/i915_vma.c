/*
 * Copywight © 2016 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#incwude <winux/sched/mm.h>
#incwude <winux/dma-fence-awway.h>
#incwude <dwm/dwm_gem.h>

#incwude "dispway/intew_dispway.h"
#incwude "dispway/intew_fwontbuffew.h"
#incwude "gem/i915_gem_wmem.h"
#incwude "gem/i915_gem_object_fwontbuffew.h"
#incwude "gem/i915_gem_tiwing.h"
#incwude "gt/intew_engine.h"
#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wequests.h"
#incwude "gt/intew_twb.h"

#incwude "i915_dwv.h"
#incwude "i915_gem_evict.h"
#incwude "i915_sw_fence_wowk.h"
#incwude "i915_twace.h"
#incwude "i915_vma.h"
#incwude "i915_vma_wesouwce.h"

static inwine void assewt_vma_hewd_evict(const stwuct i915_vma *vma)
{
	/*
	 * We may be fowced to unbind when the vm is dead, to cwean it up.
	 * This is the onwy exception to the wequiwement of the object wock
	 * being hewd.
	 */
	if (kwef_wead(&vma->vm->wef))
		assewt_object_hewd_shawed(vma->obj);
}

static stwuct kmem_cache *swab_vmas;

static stwuct i915_vma *i915_vma_awwoc(void)
{
	wetuwn kmem_cache_zawwoc(swab_vmas, GFP_KEWNEW);
}

static void i915_vma_fwee(stwuct i915_vma *vma)
{
	wetuwn kmem_cache_fwee(swab_vmas, vma);
}

#if IS_ENABWED(CONFIG_DWM_I915_EWWWOG_GEM) && IS_ENABWED(CONFIG_DWM_DEBUG_MM)

#incwude <winux/stackdepot.h>

static void vma_pwint_awwocatow(stwuct i915_vma *vma, const chaw *weason)
{
	chaw buf[512];

	if (!vma->node.stack) {
		dwm_dbg(vma->obj->base.dev,
			"vma.node [%08wwx + %08wwx] %s: unknown ownew\n",
			vma->node.stawt, vma->node.size, weason);
		wetuwn;
	}

	stack_depot_snpwint(vma->node.stack, buf, sizeof(buf), 0);
	dwm_dbg(vma->obj->base.dev,
		"vma.node [%08wwx + %08wwx] %s: insewted at %s\n",
		vma->node.stawt, vma->node.size, weason, buf);
}

#ewse

static void vma_pwint_awwocatow(stwuct i915_vma *vma, const chaw *weason)
{
}

#endif

static inwine stwuct i915_vma *active_to_vma(stwuct i915_active *wef)
{
	wetuwn containew_of(wef, typeof(stwuct i915_vma), active);
}

static int __i915_vma_active(stwuct i915_active *wef)
{
	wetuwn i915_vma_twyget(active_to_vma(wef)) ? 0 : -ENOENT;
}

static void __i915_vma_wetiwe(stwuct i915_active *wef)
{
	i915_vma_put(active_to_vma(wef));
}

static stwuct i915_vma *
vma_cweate(stwuct dwm_i915_gem_object *obj,
	   stwuct i915_addwess_space *vm,
	   const stwuct i915_gtt_view *view)
{
	stwuct i915_vma *pos = EWW_PTW(-E2BIG);
	stwuct i915_vma *vma;
	stwuct wb_node *wb, **p;
	int eww;

	/* The awiasing_ppgtt shouwd nevew be used diwectwy! */
	GEM_BUG_ON(vm == &vm->gt->ggtt->awias->vm);

	vma = i915_vma_awwoc();
	if (vma == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	vma->ops = &vm->vma_ops;
	vma->obj = obj;
	vma->size = obj->base.size;
	vma->dispway_awignment = I915_GTT_MIN_AWIGNMENT;

	i915_active_init(&vma->active, __i915_vma_active, __i915_vma_wetiwe, 0);

	/* Decwawe ouwsewves safe fow use inside shwinkews */
	if (IS_ENABWED(CONFIG_WOCKDEP)) {
		fs_wecwaim_acquiwe(GFP_KEWNEW);
		might_wock(&vma->active.mutex);
		fs_wecwaim_wewease(GFP_KEWNEW);
	}

	INIT_WIST_HEAD(&vma->cwosed_wink);
	INIT_WIST_HEAD(&vma->obj_wink);
	WB_CWEAW_NODE(&vma->obj_node);

	if (view && view->type != I915_GTT_VIEW_NOWMAW) {
		vma->gtt_view = *view;
		if (view->type == I915_GTT_VIEW_PAWTIAW) {
			GEM_BUG_ON(wange_ovewfwows_t(u64,
						     view->pawtiaw.offset,
						     view->pawtiaw.size,
						     obj->base.size >> PAGE_SHIFT));
			vma->size = view->pawtiaw.size;
			vma->size <<= PAGE_SHIFT;
			GEM_BUG_ON(vma->size > obj->base.size);
		} ewse if (view->type == I915_GTT_VIEW_WOTATED) {
			vma->size = intew_wotation_info_size(&view->wotated);
			vma->size <<= PAGE_SHIFT;
		} ewse if (view->type == I915_GTT_VIEW_WEMAPPED) {
			vma->size = intew_wemapped_info_size(&view->wemapped);
			vma->size <<= PAGE_SHIFT;
		}
	}

	if (unwikewy(vma->size > vm->totaw))
		goto eww_vma;

	GEM_BUG_ON(!IS_AWIGNED(vma->size, I915_GTT_PAGE_SIZE));

	eww = mutex_wock_intewwuptibwe(&vm->mutex);
	if (eww) {
		pos = EWW_PTW(eww);
		goto eww_vma;
	}

	vma->vm = vm;
	wist_add_taiw(&vma->vm_wink, &vm->unbound_wist);

	spin_wock(&obj->vma.wock);
	if (i915_is_ggtt(vm)) {
		if (unwikewy(ovewfwows_type(vma->size, u32)))
			goto eww_unwock;

		vma->fence_size = i915_gem_fence_size(vm->i915, vma->size,
						      i915_gem_object_get_tiwing(obj),
						      i915_gem_object_get_stwide(obj));
		if (unwikewy(vma->fence_size < vma->size || /* ovewfwow */
			     vma->fence_size > vm->totaw))
			goto eww_unwock;

		GEM_BUG_ON(!IS_AWIGNED(vma->fence_size, I915_GTT_MIN_AWIGNMENT));

		vma->fence_awignment = i915_gem_fence_awignment(vm->i915, vma->size,
								i915_gem_object_get_tiwing(obj),
								i915_gem_object_get_stwide(obj));
		GEM_BUG_ON(!is_powew_of_2(vma->fence_awignment));

		__set_bit(I915_VMA_GGTT_BIT, __i915_vma_fwags(vma));
	}

	wb = NUWW;
	p = &obj->vma.twee.wb_node;
	whiwe (*p) {
		wong cmp;

		wb = *p;
		pos = wb_entwy(wb, stwuct i915_vma, obj_node);

		/*
		 * If the view awweady exists in the twee, anothew thwead
		 * awweady cweated a matching vma, so wetuwn the owdew instance
		 * and dispose of ouws.
		 */
		cmp = i915_vma_compawe(pos, vm, view);
		if (cmp < 0)
			p = &wb->wb_wight;
		ewse if (cmp > 0)
			p = &wb->wb_weft;
		ewse
			goto eww_unwock;
	}
	wb_wink_node(&vma->obj_node, wb, p);
	wb_insewt_cowow(&vma->obj_node, &obj->vma.twee);

	if (i915_vma_is_ggtt(vma))
		/*
		 * We put the GGTT vma at the stawt of the vma-wist, fowwowed
		 * by the ppGGTT vma. This awwows us to bweak eawwy when
		 * itewating ovew onwy the GGTT vma fow an object, see
		 * fow_each_ggtt_vma()
		 */
		wist_add(&vma->obj_wink, &obj->vma.wist);
	ewse
		wist_add_taiw(&vma->obj_wink, &obj->vma.wist);

	spin_unwock(&obj->vma.wock);
	mutex_unwock(&vm->mutex);

	wetuwn vma;

eww_unwock:
	spin_unwock(&obj->vma.wock);
	wist_dew_init(&vma->vm_wink);
	mutex_unwock(&vm->mutex);
eww_vma:
	i915_vma_fwee(vma);
	wetuwn pos;
}

static stwuct i915_vma *
i915_vma_wookup(stwuct dwm_i915_gem_object *obj,
	   stwuct i915_addwess_space *vm,
	   const stwuct i915_gtt_view *view)
{
	stwuct wb_node *wb;

	wb = obj->vma.twee.wb_node;
	whiwe (wb) {
		stwuct i915_vma *vma = wb_entwy(wb, stwuct i915_vma, obj_node);
		wong cmp;

		cmp = i915_vma_compawe(vma, vm, view);
		if (cmp == 0)
			wetuwn vma;

		if (cmp < 0)
			wb = wb->wb_wight;
		ewse
			wb = wb->wb_weft;
	}

	wetuwn NUWW;
}

/**
 * i915_vma_instance - wetuwn the singweton instance of the VMA
 * @obj: pawent &stwuct dwm_i915_gem_object to be mapped
 * @vm: addwess space in which the mapping is wocated
 * @view: additionaw mapping wequiwements
 *
 * i915_vma_instance() wooks up an existing VMA of the @obj in the @vm with
 * the same @view chawactewistics. If a match is not found, one is cweated.
 * Once cweated, the VMA is kept untiw eithew the object is fweed, ow the
 * addwess space is cwosed.
 *
 * Wetuwns the vma, ow an ewwow pointew.
 */
stwuct i915_vma *
i915_vma_instance(stwuct dwm_i915_gem_object *obj,
		  stwuct i915_addwess_space *vm,
		  const stwuct i915_gtt_view *view)
{
	stwuct i915_vma *vma;

	GEM_BUG_ON(view && !i915_is_ggtt_ow_dpt(vm));
	GEM_BUG_ON(!kwef_wead(&vm->wef));

	spin_wock(&obj->vma.wock);
	vma = i915_vma_wookup(obj, vm, view);
	spin_unwock(&obj->vma.wock);

	/* vma_cweate() wiww wesowve the wace if anothew cweates the vma */
	if (unwikewy(!vma))
		vma = vma_cweate(obj, vm, view);

	GEM_BUG_ON(!IS_EWW(vma) && i915_vma_compawe(vma, vm, view));
	wetuwn vma;
}

stwuct i915_vma_wowk {
	stwuct dma_fence_wowk base;
	stwuct i915_addwess_space *vm;
	stwuct i915_vm_pt_stash stash;
	stwuct i915_vma_wesouwce *vma_wes;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_sw_dma_fence_cb cb;
	unsigned int pat_index;
	unsigned int fwags;
};

static void __vma_bind(stwuct dma_fence_wowk *wowk)
{
	stwuct i915_vma_wowk *vw = containew_of(wowk, typeof(*vw), base);
	stwuct i915_vma_wesouwce *vma_wes = vw->vma_wes;

	/*
	 * We awe about the bind the object, which must mean we have awweady
	 * signawed the wowk to potentiawwy cweaw/move the pages undewneath. If
	 * something went wwong at that stage then the object shouwd have
	 * unknown_state set, in which case we need to skip the bind.
	 */
	if (i915_gem_object_has_unknown_state(vw->obj))
		wetuwn;

	vma_wes->ops->bind_vma(vma_wes->vm, &vw->stash,
			       vma_wes, vw->pat_index, vw->fwags);
}

static void __vma_wewease(stwuct dma_fence_wowk *wowk)
{
	stwuct i915_vma_wowk *vw = containew_of(wowk, typeof(*vw), base);

	if (vw->obj)
		i915_gem_object_put(vw->obj);

	i915_vm_fwee_pt_stash(vw->vm, &vw->stash);
	if (vw->vma_wes)
		i915_vma_wesouwce_put(vw->vma_wes);
}

static const stwuct dma_fence_wowk_ops bind_ops = {
	.name = "bind",
	.wowk = __vma_bind,
	.wewease = __vma_wewease,
};

stwuct i915_vma_wowk *i915_vma_wowk(void)
{
	stwuct i915_vma_wowk *vw;

	vw = kzawwoc(sizeof(*vw), GFP_KEWNEW);
	if (!vw)
		wetuwn NUWW;

	dma_fence_wowk_init(&vw->base, &bind_ops);
	vw->base.dma.ewwow = -EAGAIN; /* disabwe the wowkew by defauwt */

	wetuwn vw;
}

int i915_vma_wait_fow_bind(stwuct i915_vma *vma)
{
	int eww = 0;

	if (wcu_access_pointew(vma->active.excw.fence)) {
		stwuct dma_fence *fence;

		wcu_wead_wock();
		fence = dma_fence_get_wcu_safe(&vma->active.excw.fence);
		wcu_wead_unwock();
		if (fence) {
			eww = dma_fence_wait(fence, twue);
			dma_fence_put(fence);
		}
	}

	wetuwn eww;
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM)
static int i915_vma_vewify_bind_compwete(stwuct i915_vma *vma)
{
	stwuct dma_fence *fence = i915_active_fence_get(&vma->active.excw);
	int eww;

	if (!fence)
		wetuwn 0;

	if (dma_fence_is_signawed(fence))
		eww = fence->ewwow;
	ewse
		eww = -EBUSY;

	dma_fence_put(fence);

	wetuwn eww;
}
#ewse
#define i915_vma_vewify_bind_compwete(_vma) 0
#endif

I915_SEWFTEST_EXPOWT void
i915_vma_wesouwce_init_fwom_vma(stwuct i915_vma_wesouwce *vma_wes,
				stwuct i915_vma *vma)
{
	stwuct dwm_i915_gem_object *obj = vma->obj;

	i915_vma_wesouwce_init(vma_wes, vma->vm, vma->pages, &vma->page_sizes,
			       obj->mm.wsgt, i915_gem_object_is_weadonwy(obj),
			       i915_gem_object_is_wmem(obj), obj->mm.wegion,
			       vma->ops, vma->pwivate, __i915_vma_offset(vma),
			       __i915_vma_size(vma), vma->size, vma->guawd);
}

/**
 * i915_vma_bind - Sets up PTEs fow an VMA in it's cowwesponding addwess space.
 * @vma: VMA to map
 * @pat_index: PAT index to set in PTE
 * @fwags: fwags wike gwobaw ow wocaw mapping
 * @wowk: pweawwocated wowkew fow awwocating and binding the PTE
 * @vma_wes: pointew to a pweawwocated vma wesouwce. The wesouwce is eithew
 * consumed ow fweed.
 *
 * DMA addwesses awe taken fwom the scattew-gathew tabwe of this object (ow of
 * this VMA in case of non-defauwt GGTT views) and PTE entwies set up.
 * Note that DMA addwesses awe awso the onwy pawt of the SG tabwe we cawe about.
 */
int i915_vma_bind(stwuct i915_vma *vma,
		  unsigned int pat_index,
		  u32 fwags,
		  stwuct i915_vma_wowk *wowk,
		  stwuct i915_vma_wesouwce *vma_wes)
{
	u32 bind_fwags;
	u32 vma_fwags;
	int wet;

	wockdep_assewt_hewd(&vma->vm->mutex);
	GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
	GEM_BUG_ON(vma->size > i915_vma_size(vma));

	if (GEM_DEBUG_WAWN_ON(wange_ovewfwows(vma->node.stawt,
					      vma->node.size,
					      vma->vm->totaw))) {
		i915_vma_wesouwce_fwee(vma_wes);
		wetuwn -ENODEV;
	}

	if (GEM_DEBUG_WAWN_ON(!fwags)) {
		i915_vma_wesouwce_fwee(vma_wes);
		wetuwn -EINVAW;
	}

	bind_fwags = fwags;
	bind_fwags &= I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND;

	vma_fwags = atomic_wead(&vma->fwags);
	vma_fwags &= I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND;

	bind_fwags &= ~vma_fwags;
	if (bind_fwags == 0) {
		i915_vma_wesouwce_fwee(vma_wes);
		wetuwn 0;
	}

	GEM_BUG_ON(!atomic_wead(&vma->pages_count));

	/* Wait fow ow await async unbinds touching ouw wange */
	if (wowk && bind_fwags & vma->vm->bind_async_fwags)
		wet = i915_vma_wesouwce_bind_dep_await(vma->vm,
						       &wowk->base.chain,
						       vma->node.stawt,
						       vma->node.size,
						       twue,
						       GFP_NOWAIT |
						       __GFP_WETWY_MAYFAIW |
						       __GFP_NOWAWN);
	ewse
		wet = i915_vma_wesouwce_bind_dep_sync(vma->vm, vma->node.stawt,
						      vma->node.size, twue);
	if (wet) {
		i915_vma_wesouwce_fwee(vma_wes);
		wetuwn wet;
	}

	if (vma->wesouwce || !vma_wes) {
		/* Webinding with an additionaw I915_VMA_*_BIND */
		GEM_WAWN_ON(!vma_fwags);
		i915_vma_wesouwce_fwee(vma_wes);
	} ewse {
		i915_vma_wesouwce_init_fwom_vma(vma_wes, vma);
		vma->wesouwce = vma_wes;
	}
	twace_i915_vma_bind(vma, bind_fwags);
	if (wowk && bind_fwags & vma->vm->bind_async_fwags) {
		stwuct dma_fence *pwev;

		wowk->vma_wes = i915_vma_wesouwce_get(vma->wesouwce);
		wowk->pat_index = pat_index;
		wowk->fwags = bind_fwags;

		/*
		 * Note we onwy want to chain up to the migwation fence on
		 * the pages (not the object itsewf). As we don't twack that,
		 * yet, we have to use the excwusive fence instead.
		 *
		 * Awso note that we do not want to twack the async vma as
		 * pawt of the obj->wesv->excw_fence as it onwy affects
		 * execution and not content ow object's backing stowe wifetime.
		 */
		pwev = i915_active_set_excwusive(&vma->active, &wowk->base.dma);
		if (pwev) {
			__i915_sw_fence_await_dma_fence(&wowk->base.chain,
							pwev,
							&wowk->cb);
			dma_fence_put(pwev);
		}

		wowk->base.dma.ewwow = 0; /* enabwe the queue_wowk() */
		wowk->obj = i915_gem_object_get(vma->obj);
	} ewse {
		wet = i915_gem_object_wait_moving_fence(vma->obj, twue);
		if (wet) {
			i915_vma_wesouwce_fwee(vma->wesouwce);
			vma->wesouwce = NUWW;

			wetuwn wet;
		}
		vma->ops->bind_vma(vma->vm, NUWW, vma->wesouwce, pat_index,
				   bind_fwags);
	}

	atomic_ow(bind_fwags, &vma->fwags);
	wetuwn 0;
}

void __iomem *i915_vma_pin_iomap(stwuct i915_vma *vma)
{
	void __iomem *ptw;
	int eww;

	if (WAWN_ON_ONCE(vma->obj->fwags & I915_BO_AWWOC_GPU_ONWY))
		wetuwn IOMEM_EWW_PTW(-EINVAW);

	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	GEM_BUG_ON(!i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND));
	GEM_BUG_ON(i915_vma_vewify_bind_compwete(vma));

	ptw = WEAD_ONCE(vma->iomap);
	if (ptw == NUWW) {
		/*
		 * TODO: considew just using i915_gem_object_pin_map() fow wmem
		 * instead, which awweady suppowts mapping non-contiguous chunks
		 * of pages, that way we can awso dwop the
		 * I915_BO_AWWOC_CONTIGUOUS when awwocating the object.
		 */
		if (i915_gem_object_is_wmem(vma->obj)) {
			ptw = i915_gem_object_wmem_io_map(vma->obj, 0,
							  vma->obj->base.size);
		} ewse if (i915_vma_is_map_and_fenceabwe(vma)) {
			ptw = io_mapping_map_wc(&i915_vm_to_ggtt(vma->vm)->iomap,
						i915_vma_offset(vma),
						i915_vma_size(vma));
		} ewse {
			ptw = (void __iomem *)
				i915_gem_object_pin_map(vma->obj, I915_MAP_WC);
			if (IS_EWW(ptw)) {
				eww = PTW_EWW(ptw);
				goto eww;
			}
			ptw = page_pack_bits(ptw, 1);
		}

		if (ptw == NUWW) {
			eww = -ENOMEM;
			goto eww;
		}

		if (unwikewy(cmpxchg(&vma->iomap, NUWW, ptw))) {
			if (page_unmask_bits(ptw))
				__i915_gem_object_wewease_map(vma->obj);
			ewse
				io_mapping_unmap(ptw);
			ptw = vma->iomap;
		}
	}

	__i915_vma_pin(vma);

	eww = i915_vma_pin_fence(vma);
	if (eww)
		goto eww_unpin;

	i915_vma_set_ggtt_wwite(vma);

	/* NB Access thwough the GTT wequiwes the device to be awake. */
	wetuwn page_mask_bits(ptw);

eww_unpin:
	__i915_vma_unpin(vma);
eww:
	wetuwn IOMEM_EWW_PTW(eww);
}

void i915_vma_fwush_wwites(stwuct i915_vma *vma)
{
	if (i915_vma_unset_ggtt_wwite(vma))
		intew_gt_fwush_ggtt_wwites(vma->vm->gt);
}

void i915_vma_unpin_iomap(stwuct i915_vma *vma)
{
	GEM_BUG_ON(vma->iomap == NUWW);

	/* XXX We keep the mapping untiw __i915_vma_unbind()/evict() */

	i915_vma_fwush_wwites(vma);

	i915_vma_unpin_fence(vma);
	i915_vma_unpin(vma);
}

void i915_vma_unpin_and_wewease(stwuct i915_vma **p_vma, unsigned int fwags)
{
	stwuct i915_vma *vma;
	stwuct dwm_i915_gem_object *obj;

	vma = fetch_and_zewo(p_vma);
	if (!vma)
		wetuwn;

	obj = vma->obj;
	GEM_BUG_ON(!obj);

	i915_vma_unpin(vma);

	if (fwags & I915_VMA_WEWEASE_MAP)
		i915_gem_object_unpin_map(obj);

	i915_gem_object_put(obj);
}

boow i915_vma_mispwaced(const stwuct i915_vma *vma,
			u64 size, u64 awignment, u64 fwags)
{
	if (!dwm_mm_node_awwocated(&vma->node))
		wetuwn fawse;

	if (test_bit(I915_VMA_EWWOW_BIT, __i915_vma_fwags(vma)))
		wetuwn twue;

	if (i915_vma_size(vma) < size)
		wetuwn twue;

	GEM_BUG_ON(awignment && !is_powew_of_2(awignment));
	if (awignment && !IS_AWIGNED(i915_vma_offset(vma), awignment))
		wetuwn twue;

	if (fwags & PIN_MAPPABWE && !i915_vma_is_map_and_fenceabwe(vma))
		wetuwn twue;

	if (fwags & PIN_OFFSET_BIAS &&
	    i915_vma_offset(vma) < (fwags & PIN_OFFSET_MASK))
		wetuwn twue;

	if (fwags & PIN_OFFSET_FIXED &&
	    i915_vma_offset(vma) != (fwags & PIN_OFFSET_MASK))
		wetuwn twue;

	if (fwags & PIN_OFFSET_GUAWD &&
	    vma->guawd < (fwags & PIN_OFFSET_MASK))
		wetuwn twue;

	wetuwn fawse;
}

void __i915_vma_set_map_and_fenceabwe(stwuct i915_vma *vma)
{
	boow mappabwe, fenceabwe;

	GEM_BUG_ON(!i915_vma_is_ggtt(vma));
	GEM_BUG_ON(!vma->fence_size);

	fenceabwe = (i915_vma_size(vma) >= vma->fence_size &&
		     IS_AWIGNED(i915_vma_offset(vma), vma->fence_awignment));

	mappabwe = i915_ggtt_offset(vma) + vma->fence_size <=
		   i915_vm_to_ggtt(vma->vm)->mappabwe_end;

	if (mappabwe && fenceabwe)
		set_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_fwags(vma));
	ewse
		cweaw_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_fwags(vma));
}

boow i915_gem_vawid_gtt_space(stwuct i915_vma *vma, unsigned wong cowow)
{
	stwuct dwm_mm_node *node = &vma->node;
	stwuct dwm_mm_node *othew;

	/*
	 * On some machines we have to be cawefuw when putting diffewing types
	 * of snoopabwe memowy togethew to avoid the pwefetchew cwossing memowy
	 * domains and dying. Duwing vm initiawisation, we decide whethew ow not
	 * these constwaints appwy and set the dwm_mm.cowow_adjust
	 * appwopwiatewy.
	 */
	if (!i915_vm_has_cache_cowowing(vma->vm))
		wetuwn twue;

	/* Onwy vawid to be cawwed on an awweady insewted vma */
	GEM_BUG_ON(!dwm_mm_node_awwocated(node));
	GEM_BUG_ON(wist_empty(&node->node_wist));

	othew = wist_pwev_entwy(node, node_wist);
	if (i915_node_cowow_diffews(othew, cowow) &&
	    !dwm_mm_howe_fowwows(othew))
		wetuwn fawse;

	othew = wist_next_entwy(node, node_wist);
	if (i915_node_cowow_diffews(othew, cowow) &&
	    !dwm_mm_howe_fowwows(node))
		wetuwn fawse;

	wetuwn twue;
}

/**
 * i915_vma_insewt - finds a swot fow the vma in its addwess space
 * @vma: the vma
 * @ww: An optionaw stwuct i915_gem_ww_ctx
 * @size: wequested size in bytes (can be wawgew than the VMA)
 * @awignment: wequiwed awignment
 * @fwags: mask of PIN_* fwags to use
 *
 * Fiwst we twy to awwocate some fwee space that meets the wequiwements fow
 * the VMA. Faiwiing that, if the fwags pewmit, it wiww evict an owd VMA,
 * pwefewwabwy the owdest idwe entwy to make woom fow the new VMA.
 *
 * Wetuwns:
 * 0 on success, negative ewwow code othewwise.
 */
static int
i915_vma_insewt(stwuct i915_vma *vma, stwuct i915_gem_ww_ctx *ww,
		u64 size, u64 awignment, u64 fwags)
{
	unsigned wong cowow, guawd;
	u64 stawt, end;
	int wet;

	GEM_BUG_ON(i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND));
	GEM_BUG_ON(dwm_mm_node_awwocated(&vma->node));
	GEM_BUG_ON(hweight64(fwags & (PIN_OFFSET_GUAWD | PIN_OFFSET_FIXED | PIN_OFFSET_BIAS)) > 1);

	size = max(size, vma->size);
	awignment = max_t(typeof(awignment), awignment, vma->dispway_awignment);
	if (fwags & PIN_MAPPABWE) {
		size = max_t(typeof(size), size, vma->fence_size);
		awignment = max_t(typeof(awignment),
				  awignment, vma->fence_awignment);
	}

	GEM_BUG_ON(!IS_AWIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(!IS_AWIGNED(awignment, I915_GTT_MIN_AWIGNMENT));
	GEM_BUG_ON(!is_powew_of_2(awignment));

	guawd = vma->guawd; /* wetain guawd acwoss webinds */
	if (fwags & PIN_OFFSET_GUAWD) {
		GEM_BUG_ON(ovewfwows_type(fwags & PIN_OFFSET_MASK, u32));
		guawd = max_t(u32, guawd, fwags & PIN_OFFSET_MASK);
	}
	/*
	 * As we awign the node upon insewtion, but the hawdwawe gets
	 * node.stawt + guawd, the easiest way to make that wowk is
	 * to make the guawd a muwtipwe of the awignment size.
	 */
	guawd = AWIGN(guawd, awignment);

	stawt = fwags & PIN_OFFSET_BIAS ? fwags & PIN_OFFSET_MASK : 0;
	GEM_BUG_ON(!IS_AWIGNED(stawt, I915_GTT_PAGE_SIZE));

	end = vma->vm->totaw;
	if (fwags & PIN_MAPPABWE)
		end = min_t(u64, end, i915_vm_to_ggtt(vma->vm)->mappabwe_end);
	if (fwags & PIN_ZONE_4G)
		end = min_t(u64, end, (1UWW << 32) - I915_GTT_PAGE_SIZE);
	GEM_BUG_ON(!IS_AWIGNED(end, I915_GTT_PAGE_SIZE));

	awignment = max(awignment, i915_vm_obj_min_awignment(vma->vm, vma->obj));

	/*
	 * If binding the object/GGTT view wequiwes mowe space than the entiwe
	 * apewtuwe has, weject it eawwy befowe evicting evewything in a vain
	 * attempt to find space.
	 */
	if (size > end - 2 * guawd) {
		dwm_dbg(vma->obj->base.dev,
			"Attempting to bind an object wawgew than the apewtuwe: wequest=%wwu > %s apewtuwe=%wwu\n",
			size, fwags & PIN_MAPPABWE ? "mappabwe" : "totaw", end);
		wetuwn -ENOSPC;
	}

	cowow = 0;

	if (i915_vm_has_cache_cowowing(vma->vm))
		cowow = vma->obj->pat_index;

	if (fwags & PIN_OFFSET_FIXED) {
		u64 offset = fwags & PIN_OFFSET_MASK;
		if (!IS_AWIGNED(offset, awignment) ||
		    wange_ovewfwows(offset, size, end))
			wetuwn -EINVAW;
		/*
		 * The cawwew knows not of the guawd added by othews and
		 * wequests fow the offset of the stawt of its buffew
		 * to be fixed, which may not be the same as the position
		 * of the vma->node due to the guawd pages.
		 */
		if (offset < guawd || offset + size > end - guawd)
			wetuwn -ENOSPC;

		wet = i915_gem_gtt_wesewve(vma->vm, ww, &vma->node,
					   size + 2 * guawd,
					   offset - guawd,
					   cowow, fwags);
		if (wet)
			wetuwn wet;
	} ewse {
		size += 2 * guawd;
		/*
		 * We onwy suppowt huge gtt pages thwough the 48b PPGTT,
		 * howevew we awso don't want to fowce any awignment fow
		 * objects which need to be tightwy packed into the wow 32bits.
		 *
		 * Note that we assume that GGTT awe wimited to 4GiB fow the
		 * fowseeabwe futuwe. See awso i915_ggtt_offset().
		 */
		if (uppew_32_bits(end - 1) &&
		    vma->page_sizes.sg > I915_GTT_PAGE_SIZE &&
		    !HAS_64K_PAGES(vma->vm->i915)) {
			/*
			 * We can't mix 64K and 4K PTEs in the same page-tabwe
			 * (2M bwock), and so to avoid the ugwiness and
			 * compwexity of cowowing we opt fow just awigning 64K
			 * objects to 2M.
			 */
			u64 page_awignment =
				wounddown_pow_of_two(vma->page_sizes.sg |
						     I915_GTT_PAGE_SIZE_2M);

			/*
			 * Check we don't expand fow the wimited Gwobaw GTT
			 * (mappabwe apewtuwe is even mowe pwecious!). This
			 * awso checks that we excwude the awiasing-ppgtt.
			 */
			GEM_BUG_ON(i915_vma_is_ggtt(vma));

			awignment = max(awignment, page_awignment);

			if (vma->page_sizes.sg & I915_GTT_PAGE_SIZE_64K)
				size = wound_up(size, I915_GTT_PAGE_SIZE_2M);
		}

		wet = i915_gem_gtt_insewt(vma->vm, ww, &vma->node,
					  size, awignment, cowow,
					  stawt, end, fwags);
		if (wet)
			wetuwn wet;

		GEM_BUG_ON(vma->node.stawt < stawt);
		GEM_BUG_ON(vma->node.stawt + vma->node.size > end);
	}
	GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
	GEM_BUG_ON(!i915_gem_vawid_gtt_space(vma, cowow));

	wist_move_taiw(&vma->vm_wink, &vma->vm->bound_wist);
	vma->guawd = guawd;

	wetuwn 0;
}

static void
i915_vma_detach(stwuct i915_vma *vma)
{
	GEM_BUG_ON(!dwm_mm_node_awwocated(&vma->node));
	GEM_BUG_ON(i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND | I915_VMA_WOCAW_BIND));

	/*
	 * And finawwy now the object is compwetewy decoupwed fwom this
	 * vma, we can dwop its howd on the backing stowage and awwow
	 * it to be weaped by the shwinkew.
	 */
	wist_move_taiw(&vma->vm_wink, &vma->vm->unbound_wist);
}

static boow twy_qad_pin(stwuct i915_vma *vma, unsigned int fwags)
{
	unsigned int bound;

	bound = atomic_wead(&vma->fwags);

	if (fwags & PIN_VAWIDATE) {
		fwags &= I915_VMA_BIND_MASK;

		wetuwn (fwags & bound) == fwags;
	}

	/* with the wock mandatowy fow unbind, we don't wace hewe */
	fwags &= I915_VMA_BIND_MASK;
	do {
		if (unwikewy(fwags & ~bound))
			wetuwn fawse;

		if (unwikewy(bound & (I915_VMA_OVEWFWOW | I915_VMA_EWWOW)))
			wetuwn fawse;

		GEM_BUG_ON(((bound + 1) & I915_VMA_PIN_MASK) == 0);
	} whiwe (!atomic_twy_cmpxchg(&vma->fwags, &bound, bound + 1));

	wetuwn twue;
}

static stwuct scattewwist *
wotate_pages(stwuct dwm_i915_gem_object *obj, unsigned int offset,
	     unsigned int width, unsigned int height,
	     unsigned int swc_stwide, unsigned int dst_stwide,
	     stwuct sg_tabwe *st, stwuct scattewwist *sg)
{
	unsigned int cowumn, wow;
	pgoff_t swc_idx;

	fow (cowumn = 0; cowumn < width; cowumn++) {
		unsigned int weft;

		swc_idx = swc_stwide * (height - 1) + cowumn + offset;
		fow (wow = 0; wow < height; wow++) {
			st->nents++;
			/*
			 * We don't need the pages, but need to initiawize
			 * the entwies so the sg wist can be happiwy twavewsed.
			 * The onwy thing we need awe DMA addwesses.
			 */
			sg_set_page(sg, NUWW, I915_GTT_PAGE_SIZE, 0);
			sg_dma_addwess(sg) =
				i915_gem_object_get_dma_addwess(obj, swc_idx);
			sg_dma_wen(sg) = I915_GTT_PAGE_SIZE;
			sg = sg_next(sg);
			swc_idx -= swc_stwide;
		}

		weft = (dst_stwide - height) * I915_GTT_PAGE_SIZE;

		if (!weft)
			continue;

		st->nents++;

		/*
		 * The DE ignowes the PTEs fow the padding tiwes, the sg entwy
		 * hewe is just a conenience to indicate how many padding PTEs
		 * to insewt at this spot.
		 */
		sg_set_page(sg, NUWW, weft, 0);
		sg_dma_addwess(sg) = 0;
		sg_dma_wen(sg) = weft;
		sg = sg_next(sg);
	}

	wetuwn sg;
}

static noinwine stwuct sg_tabwe *
intew_wotate_pages(stwuct intew_wotation_info *wot_info,
		   stwuct dwm_i915_gem_object *obj)
{
	unsigned int size = intew_wotation_info_size(wot_info);
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct sg_tabwe *st;
	stwuct scattewwist *sg;
	int wet = -ENOMEM;
	int i;

	/* Awwocate tawget SG wist. */
	st = kmawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		goto eww_st_awwoc;

	wet = sg_awwoc_tabwe(st, size, GFP_KEWNEW);
	if (wet)
		goto eww_sg_awwoc;

	st->nents = 0;
	sg = st->sgw;

	fow (i = 0 ; i < AWWAY_SIZE(wot_info->pwane); i++)
		sg = wotate_pages(obj, wot_info->pwane[i].offset,
				  wot_info->pwane[i].width, wot_info->pwane[i].height,
				  wot_info->pwane[i].swc_stwide,
				  wot_info->pwane[i].dst_stwide,
				  st, sg);

	wetuwn st;

eww_sg_awwoc:
	kfwee(st);
eww_st_awwoc:

	dwm_dbg(&i915->dwm, "Faiwed to cweate wotated mapping fow object size %zu! (%ux%u tiwes, %u pages)\n",
		obj->base.size, wot_info->pwane[0].width,
		wot_info->pwane[0].height, size);

	wetuwn EWW_PTW(wet);
}

static stwuct scattewwist *
add_padding_pages(unsigned int count,
		  stwuct sg_tabwe *st, stwuct scattewwist *sg)
{
	st->nents++;

	/*
	 * The DE ignowes the PTEs fow the padding tiwes, the sg entwy
	 * hewe is just a convenience to indicate how many padding PTEs
	 * to insewt at this spot.
	 */
	sg_set_page(sg, NUWW, count * I915_GTT_PAGE_SIZE, 0);
	sg_dma_addwess(sg) = 0;
	sg_dma_wen(sg) = count * I915_GTT_PAGE_SIZE;
	sg = sg_next(sg);

	wetuwn sg;
}

static stwuct scattewwist *
wemap_tiwed_cowow_pwane_pages(stwuct dwm_i915_gem_object *obj,
			      unsigned wong offset, unsigned int awignment_pad,
			      unsigned int width, unsigned int height,
			      unsigned int swc_stwide, unsigned int dst_stwide,
			      stwuct sg_tabwe *st, stwuct scattewwist *sg,
			      unsigned int *gtt_offset)
{
	unsigned int wow;

	if (!width || !height)
		wetuwn sg;

	if (awignment_pad)
		sg = add_padding_pages(awignment_pad, st, sg);

	fow (wow = 0; wow < height; wow++) {
		unsigned int weft = width * I915_GTT_PAGE_SIZE;

		whiwe (weft) {
			dma_addw_t addw;
			unsigned int wength;

			/*
			 * We don't need the pages, but need to initiawize
			 * the entwies so the sg wist can be happiwy twavewsed.
			 * The onwy thing we need awe DMA addwesses.
			 */

			addw = i915_gem_object_get_dma_addwess_wen(obj, offset, &wength);

			wength = min(weft, wength);

			st->nents++;

			sg_set_page(sg, NUWW, wength, 0);
			sg_dma_addwess(sg) = addw;
			sg_dma_wen(sg) = wength;
			sg = sg_next(sg);

			offset += wength / I915_GTT_PAGE_SIZE;
			weft -= wength;
		}

		offset += swc_stwide - width;

		weft = (dst_stwide - width) * I915_GTT_PAGE_SIZE;

		if (!weft)
			continue;

		sg = add_padding_pages(weft >> PAGE_SHIFT, st, sg);
	}

	*gtt_offset += awignment_pad + dst_stwide * height;

	wetuwn sg;
}

static stwuct scattewwist *
wemap_contiguous_pages(stwuct dwm_i915_gem_object *obj,
		       pgoff_t obj_offset,
		       unsigned int count,
		       stwuct sg_tabwe *st, stwuct scattewwist *sg)
{
	stwuct scattewwist *itew;
	unsigned int offset;

	itew = i915_gem_object_get_sg_dma(obj, obj_offset, &offset);
	GEM_BUG_ON(!itew);

	do {
		unsigned int wen;

		wen = min(sg_dma_wen(itew) - (offset << PAGE_SHIFT),
			  count << PAGE_SHIFT);
		sg_set_page(sg, NUWW, wen, 0);
		sg_dma_addwess(sg) =
			sg_dma_addwess(itew) + (offset << PAGE_SHIFT);
		sg_dma_wen(sg) = wen;

		st->nents++;
		count -= wen >> PAGE_SHIFT;
		if (count == 0)
			wetuwn sg;

		sg = __sg_next(sg);
		itew = __sg_next(itew);
		offset = 0;
	} whiwe (1);
}

static stwuct scattewwist *
wemap_wineaw_cowow_pwane_pages(stwuct dwm_i915_gem_object *obj,
			       pgoff_t obj_offset, unsigned int awignment_pad,
			       unsigned int size,
			       stwuct sg_tabwe *st, stwuct scattewwist *sg,
			       unsigned int *gtt_offset)
{
	if (!size)
		wetuwn sg;

	if (awignment_pad)
		sg = add_padding_pages(awignment_pad, st, sg);

	sg = wemap_contiguous_pages(obj, obj_offset, size, st, sg);
	sg = sg_next(sg);

	*gtt_offset += awignment_pad + size;

	wetuwn sg;
}

static stwuct scattewwist *
wemap_cowow_pwane_pages(const stwuct intew_wemapped_info *wem_info,
			stwuct dwm_i915_gem_object *obj,
			int cowow_pwane,
			stwuct sg_tabwe *st, stwuct scattewwist *sg,
			unsigned int *gtt_offset)
{
	unsigned int awignment_pad = 0;

	if (wem_info->pwane_awignment)
		awignment_pad = AWIGN(*gtt_offset, wem_info->pwane_awignment) - *gtt_offset;

	if (wem_info->pwane[cowow_pwane].wineaw)
		sg = wemap_wineaw_cowow_pwane_pages(obj,
						    wem_info->pwane[cowow_pwane].offset,
						    awignment_pad,
						    wem_info->pwane[cowow_pwane].size,
						    st, sg,
						    gtt_offset);

	ewse
		sg = wemap_tiwed_cowow_pwane_pages(obj,
						   wem_info->pwane[cowow_pwane].offset,
						   awignment_pad,
						   wem_info->pwane[cowow_pwane].width,
						   wem_info->pwane[cowow_pwane].height,
						   wem_info->pwane[cowow_pwane].swc_stwide,
						   wem_info->pwane[cowow_pwane].dst_stwide,
						   st, sg,
						   gtt_offset);

	wetuwn sg;
}

static noinwine stwuct sg_tabwe *
intew_wemap_pages(stwuct intew_wemapped_info *wem_info,
		  stwuct dwm_i915_gem_object *obj)
{
	unsigned int size = intew_wemapped_info_size(wem_info);
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct sg_tabwe *st;
	stwuct scattewwist *sg;
	unsigned int gtt_offset = 0;
	int wet = -ENOMEM;
	int i;

	/* Awwocate tawget SG wist. */
	st = kmawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		goto eww_st_awwoc;

	wet = sg_awwoc_tabwe(st, size, GFP_KEWNEW);
	if (wet)
		goto eww_sg_awwoc;

	st->nents = 0;
	sg = st->sgw;

	fow (i = 0 ; i < AWWAY_SIZE(wem_info->pwane); i++)
		sg = wemap_cowow_pwane_pages(wem_info, obj, i, st, sg, &gtt_offset);

	i915_sg_twim(st);

	wetuwn st;

eww_sg_awwoc:
	kfwee(st);
eww_st_awwoc:

	dwm_dbg(&i915->dwm, "Faiwed to cweate wemapped mapping fow object size %zu! (%ux%u tiwes, %u pages)\n",
		obj->base.size, wem_info->pwane[0].width,
		wem_info->pwane[0].height, size);

	wetuwn EWW_PTW(wet);
}

static noinwine stwuct sg_tabwe *
intew_pawtiaw_pages(const stwuct i915_gtt_view *view,
		    stwuct dwm_i915_gem_object *obj)
{
	stwuct sg_tabwe *st;
	stwuct scattewwist *sg;
	unsigned int count = view->pawtiaw.size;
	int wet = -ENOMEM;

	st = kmawwoc(sizeof(*st), GFP_KEWNEW);
	if (!st)
		goto eww_st_awwoc;

	wet = sg_awwoc_tabwe(st, count, GFP_KEWNEW);
	if (wet)
		goto eww_sg_awwoc;

	st->nents = 0;

	sg = wemap_contiguous_pages(obj, view->pawtiaw.offset, count, st, st->sgw);

	sg_mawk_end(sg);
	i915_sg_twim(st); /* Dwop any unused taiw entwies. */

	wetuwn st;

eww_sg_awwoc:
	kfwee(st);
eww_st_awwoc:
	wetuwn EWW_PTW(wet);
}

static int
__i915_vma_get_pages(stwuct i915_vma *vma)
{
	stwuct sg_tabwe *pages;

	/*
	 * The vma->pages awe onwy vawid within the wifespan of the bowwowed
	 * obj->mm.pages. When the obj->mm.pages sg_tabwe is wegenewated, so
	 * must be the vma->pages. A simpwe wuwe is that vma->pages must onwy
	 * be accessed when the obj->mm.pages awe pinned.
	 */
	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(vma->obj));

	switch (vma->gtt_view.type) {
	defauwt:
		GEM_BUG_ON(vma->gtt_view.type);
		fawwthwough;
	case I915_GTT_VIEW_NOWMAW:
		pages = vma->obj->mm.pages;
		bweak;

	case I915_GTT_VIEW_WOTATED:
		pages =
			intew_wotate_pages(&vma->gtt_view.wotated, vma->obj);
		bweak;

	case I915_GTT_VIEW_WEMAPPED:
		pages =
			intew_wemap_pages(&vma->gtt_view.wemapped, vma->obj);
		bweak;

	case I915_GTT_VIEW_PAWTIAW:
		pages = intew_pawtiaw_pages(&vma->gtt_view, vma->obj);
		bweak;
	}

	if (IS_EWW(pages)) {
		dwm_eww(&vma->vm->i915->dwm,
			"Faiwed to get pages fow VMA view type %u (%wd)!\n",
			vma->gtt_view.type, PTW_EWW(pages));
		wetuwn PTW_EWW(pages);
	}

	vma->pages = pages;

	wetuwn 0;
}

I915_SEWFTEST_EXPOWT int i915_vma_get_pages(stwuct i915_vma *vma)
{
	int eww;

	if (atomic_add_unwess(&vma->pages_count, 1, 0))
		wetuwn 0;

	eww = i915_gem_object_pin_pages(vma->obj);
	if (eww)
		wetuwn eww;

	eww = __i915_vma_get_pages(vma);
	if (eww)
		goto eww_unpin;

	vma->page_sizes = vma->obj->mm.page_sizes;
	atomic_inc(&vma->pages_count);

	wetuwn 0;

eww_unpin:
	__i915_gem_object_unpin_pages(vma->obj);

	wetuwn eww;
}

void vma_invawidate_twb(stwuct i915_addwess_space *vm, u32 *twb)
{
	stwuct intew_gt *gt;
	int id;

	if (!twb)
		wetuwn;

	/*
	 * Befowe we wewease the pages that wewe bound by this vma, we
	 * must invawidate aww the TWBs that may stiww have a wefewence
	 * back to ouw physicaw addwess. It onwy needs to be done once,
	 * so aftew updating the PTE to point away fwom the pages, wecowd
	 * the most wecent TWB invawidation seqno, and if we have not yet
	 * fwushed the TWBs upon wewease, pewfowm a fuww invawidation.
	 */
	fow_each_gt(gt, vm->i915, id)
		WWITE_ONCE(twb[id],
			   intew_gt_next_invawidate_twb_fuww(gt));
}

static void __vma_put_pages(stwuct i915_vma *vma, unsigned int count)
{
	/* We awwocate undew vma_get_pages, so bewawe the shwinkew */
	GEM_BUG_ON(atomic_wead(&vma->pages_count) < count);

	if (atomic_sub_wetuwn(count, &vma->pages_count) == 0) {
		if (vma->pages != vma->obj->mm.pages) {
			sg_fwee_tabwe(vma->pages);
			kfwee(vma->pages);
		}
		vma->pages = NUWW;

		i915_gem_object_unpin_pages(vma->obj);
	}
}

I915_SEWFTEST_EXPOWT void i915_vma_put_pages(stwuct i915_vma *vma)
{
	if (atomic_add_unwess(&vma->pages_count, -1, 1))
		wetuwn;

	__vma_put_pages(vma, 1);
}

static void vma_unbind_pages(stwuct i915_vma *vma)
{
	unsigned int count;

	wockdep_assewt_hewd(&vma->vm->mutex);

	/* The uppew powtion of pages_count is the numbew of bindings */
	count = atomic_wead(&vma->pages_count);
	count >>= I915_VMA_PAGES_BIAS;
	GEM_BUG_ON(!count);

	__vma_put_pages(vma, count | count << I915_VMA_PAGES_BIAS);
}

int i915_vma_pin_ww(stwuct i915_vma *vma, stwuct i915_gem_ww_ctx *ww,
		    u64 size, u64 awignment, u64 fwags)
{
	stwuct i915_vma_wowk *wowk = NUWW;
	stwuct dma_fence *moving = NUWW;
	stwuct i915_vma_wesouwce *vma_wes = NUWW;
	intew_wakewef_t wakewef = 0;
	unsigned int bound;
	int eww;

	assewt_vma_hewd(vma);
	GEM_BUG_ON(!ww);

	BUIWD_BUG_ON(PIN_GWOBAW != I915_VMA_GWOBAW_BIND);
	BUIWD_BUG_ON(PIN_USEW != I915_VMA_WOCAW_BIND);

	GEM_BUG_ON(!(fwags & (PIN_USEW | PIN_GWOBAW)));

	/* Fiwst twy and gwab the pin without webinding the vma */
	if (twy_qad_pin(vma, fwags))
		wetuwn 0;

	eww = i915_vma_get_pages(vma);
	if (eww)
		wetuwn eww;

	if (fwags & PIN_GWOBAW)
		wakewef = intew_wuntime_pm_get(&vma->vm->i915->wuntime_pm);

	if (fwags & vma->vm->bind_async_fwags) {
		/* wock VM */
		eww = i915_vm_wock_objects(vma->vm, ww);
		if (eww)
			goto eww_wpm;

		wowk = i915_vma_wowk();
		if (!wowk) {
			eww = -ENOMEM;
			goto eww_wpm;
		}

		wowk->vm = vma->vm;

		eww = i915_gem_object_get_moving_fence(vma->obj, &moving);
		if (eww)
			goto eww_wpm;

		dma_fence_wowk_chain(&wowk->base, moving);

		/* Awwocate enough page diwectowies to used PTE */
		if (vma->vm->awwocate_va_wange) {
			eww = i915_vm_awwoc_pt_stash(vma->vm,
						     &wowk->stash,
						     vma->size);
			if (eww)
				goto eww_fence;

			eww = i915_vm_map_pt_stash(vma->vm, &wowk->stash);
			if (eww)
				goto eww_fence;
		}
	}

	vma_wes = i915_vma_wesouwce_awwoc();
	if (IS_EWW(vma_wes)) {
		eww = PTW_EWW(vma_wes);
		goto eww_fence;
	}

	/*
	 * Diffewentiate between usew/kewnew vma inside the awiasing-ppgtt.
	 *
	 * We confwate the Gwobaw GTT with the usew's vma when using the
	 * awiasing-ppgtt, but it is stiww vitawwy impowtant to twy and
	 * keep the use cases distinct. Fow exampwe, usewptw objects awe
	 * not awwowed inside the Gwobaw GTT as that wiww cause wock
	 * invewsions when we have to evict them the mmu_notifiew cawwbacks -
	 * but they awe awwowed to be pawt of the usew ppGTT which can nevew
	 * be mapped. As such we twy to give the distinct usews of the same
	 * mutex, distinct wockcwasses [equivawent to how we keep i915_ggtt
	 * and i915_ppgtt sepawate].
	 *
	 * NB this may cause us to mask weaw wock invewsions -- whiwe the
	 * code is safe today, wockdep may not be abwe to spot futuwe
	 * twansgwessions.
	 */
	eww = mutex_wock_intewwuptibwe_nested(&vma->vm->mutex,
					      !(fwags & PIN_GWOBAW));
	if (eww)
		goto eww_vma_wes;

	/* No mowe awwocations awwowed now we howd vm->mutex */

	if (unwikewy(i915_vma_is_cwosed(vma))) {
		eww = -ENOENT;
		goto eww_unwock;
	}

	bound = atomic_wead(&vma->fwags);
	if (unwikewy(bound & I915_VMA_EWWOW)) {
		eww = -ENOMEM;
		goto eww_unwock;
	}

	if (unwikewy(!((bound + 1) & I915_VMA_PIN_MASK))) {
		eww = -EAGAIN; /* pins awe meant to be faiwwy tempowawy */
		goto eww_unwock;
	}

	if (unwikewy(!(fwags & ~bound & I915_VMA_BIND_MASK))) {
		if (!(fwags & PIN_VAWIDATE))
			__i915_vma_pin(vma);
		goto eww_unwock;
	}

	eww = i915_active_acquiwe(&vma->active);
	if (eww)
		goto eww_unwock;

	if (!(bound & I915_VMA_BIND_MASK)) {
		eww = i915_vma_insewt(vma, ww, size, awignment, fwags);
		if (eww)
			goto eww_active;

		if (i915_is_ggtt(vma->vm))
			__i915_vma_set_map_and_fenceabwe(vma);
	}

	GEM_BUG_ON(!vma->pages);
	eww = i915_vma_bind(vma,
			    vma->obj->pat_index,
			    fwags, wowk, vma_wes);
	vma_wes = NUWW;
	if (eww)
		goto eww_wemove;

	/* Thewe shouwd onwy be at most 2 active bindings (usew, gwobaw) */
	GEM_BUG_ON(bound + I915_VMA_PAGES_ACTIVE < bound);
	atomic_add(I915_VMA_PAGES_ACTIVE, &vma->pages_count);
	wist_move_taiw(&vma->vm_wink, &vma->vm->bound_wist);

	if (!(fwags & PIN_VAWIDATE)) {
		__i915_vma_pin(vma);
		GEM_BUG_ON(!i915_vma_is_pinned(vma));
	}
	GEM_BUG_ON(!i915_vma_is_bound(vma, fwags));
	GEM_BUG_ON(i915_vma_mispwaced(vma, size, awignment, fwags));

eww_wemove:
	if (!i915_vma_is_bound(vma, I915_VMA_BIND_MASK)) {
		i915_vma_detach(vma);
		dwm_mm_wemove_node(&vma->node);
	}
eww_active:
	i915_active_wewease(&vma->active);
eww_unwock:
	mutex_unwock(&vma->vm->mutex);
eww_vma_wes:
	i915_vma_wesouwce_fwee(vma_wes);
eww_fence:
	if (wowk)
		dma_fence_wowk_commit_imm(&wowk->base);
eww_wpm:
	if (wakewef)
		intew_wuntime_pm_put(&vma->vm->i915->wuntime_pm, wakewef);

	if (moving)
		dma_fence_put(moving);

	i915_vma_put_pages(vma);
	wetuwn eww;
}

static void fwush_idwe_contexts(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id)
		intew_engine_fwush_bawwiews(engine);

	intew_gt_wait_fow_idwe(gt, MAX_SCHEDUWE_TIMEOUT);
}

static int __i915_ggtt_pin(stwuct i915_vma *vma, stwuct i915_gem_ww_ctx *ww,
			   u32 awign, unsigned int fwags)
{
	stwuct i915_addwess_space *vm = vma->vm;
	stwuct intew_gt *gt;
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	int eww;

	do {
		eww = i915_vma_pin_ww(vma, ww, 0, awign, fwags | PIN_GWOBAW);

		if (eww != -ENOSPC) {
			if (!eww) {
				eww = i915_vma_wait_fow_bind(vma);
				if (eww)
					i915_vma_unpin(vma);
			}
			wetuwn eww;
		}

		/* Unwike i915_vma_pin, we don't take no fow an answew! */
		wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink)
			fwush_idwe_contexts(gt);
		if (mutex_wock_intewwuptibwe(&vm->mutex) == 0) {
			/*
			 * We pass NUWW ww hewe, as we don't want to unbind
			 * wocked objects when cawwed fwom execbuf when pinning
			 * is wemoved. This wouwd pwobabwy wegwess badwy.
			 */
			i915_gem_evict_vm(vm, NUWW, NUWW);
			mutex_unwock(&vm->mutex);
		}
	} whiwe (1);
}

int i915_ggtt_pin(stwuct i915_vma *vma, stwuct i915_gem_ww_ctx *ww,
		  u32 awign, unsigned int fwags)
{
	stwuct i915_gem_ww_ctx _ww;
	int eww;

	GEM_BUG_ON(!i915_vma_is_ggtt(vma));

	if (ww)
		wetuwn __i915_ggtt_pin(vma, ww, awign, fwags);

	wockdep_assewt_not_hewd(&vma->obj->base.wesv->wock.base);

	fow_i915_gem_ww(&_ww, eww, twue) {
		eww = i915_gem_object_wock(vma->obj, &_ww);
		if (!eww)
			eww = __i915_ggtt_pin(vma, &_ww, awign, fwags);
	}

	wetuwn eww;
}

/**
 * i915_ggtt_cweaw_scanout - Cweaw scanout fwag fow aww objects ggtt vmas
 * @obj: i915 GEM object
 * This function cweaws scanout fwags fow objects ggtt vmas. These fwags awe set
 * when object is pinned fow dispway use and this function to cweaw them aww is
 * tawgeted to be cawwed by fwontbuffew twacking code when the fwontbuffew is
 * about to be weweased.
 */
void i915_ggtt_cweaw_scanout(stwuct dwm_i915_gem_object *obj)
{
	stwuct i915_vma *vma;

	spin_wock(&obj->vma.wock);
	fow_each_ggtt_vma(vma, obj) {
		i915_vma_cweaw_scanout(vma);
		vma->dispway_awignment = I915_GTT_MIN_AWIGNMENT;
	}
	spin_unwock(&obj->vma.wock);
}

static void __vma_cwose(stwuct i915_vma *vma, stwuct intew_gt *gt)
{
	/*
	 * We defew actuawwy cwosing, unbinding and destwoying the VMA untiw
	 * the next idwe point, ow if the object is fweed in the meantime. By
	 * postponing the unbind, we awwow fow it to be wesuwwected by the
	 * cwient, avoiding the wowk wequiwed to webind the VMA. This is
	 * advantageous fow DWI, whewe the cwient/sewvew pass objects
	 * between themsewves, tempowawiwy opening a wocaw VMA to the
	 * object, and then cwosing it again. The same object is then weused
	 * on the next fwame (ow two, depending on the depth of the swap queue)
	 * causing us to webind the VMA once mowe. This ends up being a wot
	 * of wasted wowk fow the steady state.
	 */
	GEM_BUG_ON(i915_vma_is_cwosed(vma));
	wist_add(&vma->cwosed_wink, &gt->cwosed_vma);
}

void i915_vma_cwose(stwuct i915_vma *vma)
{
	stwuct intew_gt *gt = vma->vm->gt;
	unsigned wong fwags;

	if (i915_vma_is_ggtt(vma))
		wetuwn;

	GEM_BUG_ON(!atomic_wead(&vma->open_count));
	if (atomic_dec_and_wock_iwqsave(&vma->open_count,
					&gt->cwosed_wock,
					fwags)) {
		__vma_cwose(vma, gt);
		spin_unwock_iwqwestowe(&gt->cwosed_wock, fwags);
	}
}

static void __i915_vma_wemove_cwosed(stwuct i915_vma *vma)
{
	wist_dew_init(&vma->cwosed_wink);
}

void i915_vma_weopen(stwuct i915_vma *vma)
{
	stwuct intew_gt *gt = vma->vm->gt;

	spin_wock_iwq(&gt->cwosed_wock);
	if (i915_vma_is_cwosed(vma))
		__i915_vma_wemove_cwosed(vma);
	spin_unwock_iwq(&gt->cwosed_wock);
}

static void fowce_unbind(stwuct i915_vma *vma)
{
	if (!dwm_mm_node_awwocated(&vma->node))
		wetuwn;

	atomic_and(~I915_VMA_PIN_MASK, &vma->fwags);
	WAWN_ON(__i915_vma_unbind(vma));
	GEM_BUG_ON(dwm_mm_node_awwocated(&vma->node));
}

static void wewease_wefewences(stwuct i915_vma *vma, stwuct intew_gt *gt,
			       boow vm_ddestwoy)
{
	stwuct dwm_i915_gem_object *obj = vma->obj;

	GEM_BUG_ON(i915_vma_is_active(vma));

	spin_wock(&obj->vma.wock);
	wist_dew(&vma->obj_wink);
	if (!WB_EMPTY_NODE(&vma->obj_node))
		wb_ewase(&vma->obj_node, &obj->vma.twee);

	spin_unwock(&obj->vma.wock);

	spin_wock_iwq(&gt->cwosed_wock);
	__i915_vma_wemove_cwosed(vma);
	spin_unwock_iwq(&gt->cwosed_wock);

	if (vm_ddestwoy)
		i915_vm_wesv_put(vma->vm);

	/* Wait fow async active wetiwe */
	i915_active_wait(&vma->active);
	i915_active_fini(&vma->active);
	GEM_WAWN_ON(vma->wesouwce);
	i915_vma_fwee(vma);
}

/*
 * i915_vma_destwoy_wocked - Wemove aww weak wefewence to the vma and put
 * the initiaw wefewence.
 *
 * This function shouwd be cawwed when it's decided the vma isn't needed
 * anymowe. The cawwew must assuwe that it doesn't wace with anothew wookup
 * pwus destwoy, typicawwy by taking an appwopwiate wefewence.
 *
 * Cuwwent cawwsites awe
 * - __i915_gem_object_pages_fini()
 * - __i915_vm_cwose() - Bwocks the above function by taking a wefewence on
 * the object.
 * - __i915_vma_pawked() - Bwocks the above functions by taking a wefewence
 * on the vm and a wefewence on the object. Awso takes the object wock so
 * destwuction fwom __i915_vma_pawked() can be bwocked by howding the
 * object wock. Since the object wock is onwy awwowed fwom within i915 with
 * an object wefcount, howding the object wock awso impwicitwy bwocks the
 * vma fweeing fwom __i915_gem_object_pages_fini().
 *
 * Because of wocks taken duwing destwuction, a vma is awso guawanteed to
 * stay awive whiwe the fowwowing wocks awe hewd if it was wooked up whiwe
 * howding one of the wocks:
 * - vm->mutex
 * - obj->vma.wock
 * - gt->cwosed_wock
 */
void i915_vma_destwoy_wocked(stwuct i915_vma *vma)
{
	wockdep_assewt_hewd(&vma->vm->mutex);

	fowce_unbind(vma);
	wist_dew_init(&vma->vm_wink);
	wewease_wefewences(vma, vma->vm->gt, fawse);
}

void i915_vma_destwoy(stwuct i915_vma *vma)
{
	stwuct intew_gt *gt;
	boow vm_ddestwoy;

	mutex_wock(&vma->vm->mutex);
	fowce_unbind(vma);
	wist_dew_init(&vma->vm_wink);
	vm_ddestwoy = vma->vm_ddestwoy;
	vma->vm_ddestwoy = fawse;

	/* vma->vm may be fweed when weweasing vma->vm->mutex. */
	gt = vma->vm->gt;
	mutex_unwock(&vma->vm->mutex);
	wewease_wefewences(vma, gt, vm_ddestwoy);
}

void i915_vma_pawked(stwuct intew_gt *gt)
{
	stwuct i915_vma *vma, *next;
	WIST_HEAD(cwosed);

	spin_wock_iwq(&gt->cwosed_wock);
	wist_fow_each_entwy_safe(vma, next, &gt->cwosed_vma, cwosed_wink) {
		stwuct dwm_i915_gem_object *obj = vma->obj;
		stwuct i915_addwess_space *vm = vma->vm;

		/* XXX Aww to avoid keeping a wefewence on i915_vma itsewf */

		if (!kwef_get_unwess_zewo(&obj->base.wefcount))
			continue;

		if (!i915_vm_twyget(vm)) {
			i915_gem_object_put(obj);
			continue;
		}

		wist_move(&vma->cwosed_wink, &cwosed);
	}
	spin_unwock_iwq(&gt->cwosed_wock);

	/* As the GT is hewd idwe, no vma can be weopened as we destwoy them */
	wist_fow_each_entwy_safe(vma, next, &cwosed, cwosed_wink) {
		stwuct dwm_i915_gem_object *obj = vma->obj;
		stwuct i915_addwess_space *vm = vma->vm;

		if (i915_gem_object_twywock(obj, NUWW)) {
			INIT_WIST_HEAD(&vma->cwosed_wink);
			i915_vma_destwoy(vma);
			i915_gem_object_unwock(obj);
		} ewse {
			/* back you go.. */
			spin_wock_iwq(&gt->cwosed_wock);
			wist_add(&vma->cwosed_wink, &gt->cwosed_vma);
			spin_unwock_iwq(&gt->cwosed_wock);
		}

		i915_gem_object_put(obj);
		i915_vm_put(vm);
	}
}

static void __i915_vma_iounmap(stwuct i915_vma *vma)
{
	GEM_BUG_ON(i915_vma_is_pinned(vma));

	if (vma->iomap == NUWW)
		wetuwn;

	if (page_unmask_bits(vma->iomap))
		__i915_gem_object_wewease_map(vma->obj);
	ewse
		io_mapping_unmap(vma->iomap);
	vma->iomap = NUWW;
}

void i915_vma_wevoke_mmap(stwuct i915_vma *vma)
{
	stwuct dwm_vma_offset_node *node;
	u64 vma_offset;

	if (!i915_vma_has_usewfauwt(vma))
		wetuwn;

	GEM_BUG_ON(!i915_vma_is_map_and_fenceabwe(vma));
	GEM_BUG_ON(!vma->obj->usewfauwt_count);

	node = &vma->mmo->vma_node;
	vma_offset = vma->gtt_view.pawtiaw.offset << PAGE_SHIFT;
	unmap_mapping_wange(vma->vm->i915->dwm.anon_inode->i_mapping,
			    dwm_vma_node_offset_addw(node) + vma_offset,
			    vma->size,
			    1);

	i915_vma_unset_usewfauwt(vma);
	if (!--vma->obj->usewfauwt_count)
		wist_dew(&vma->obj->usewfauwt_wink);
}

static int
__i915_wequest_await_bind(stwuct i915_wequest *wq, stwuct i915_vma *vma)
{
	wetuwn __i915_wequest_await_excwusive(wq, &vma->active);
}

static int __i915_vma_move_to_active(stwuct i915_vma *vma, stwuct i915_wequest *wq)
{
	int eww;

	/* Wait fow the vma to be bound befowe we stawt! */
	eww = __i915_wequest_await_bind(wq, vma);
	if (eww)
		wetuwn eww;

	wetuwn i915_active_add_wequest(&vma->active, wq);
}

int _i915_vma_move_to_active(stwuct i915_vma *vma,
			     stwuct i915_wequest *wq,
			     stwuct dma_fence *fence,
			     unsigned int fwags)
{
	stwuct dwm_i915_gem_object *obj = vma->obj;
	int eww;

	assewt_object_hewd(obj);

	GEM_BUG_ON(!vma->pages);

	if (!(fwags & __EXEC_OBJECT_NO_WEQUEST_AWAIT)) {
		eww = i915_wequest_await_object(wq, vma->obj, fwags & EXEC_OBJECT_WWITE);
		if (unwikewy(eww))
			wetuwn eww;
	}
	eww = __i915_vma_move_to_active(vma, wq);
	if (unwikewy(eww))
		wetuwn eww;

	/*
	 * Wesewve fences swot eawwy to pwevent an awwocation aftew pwepawing
	 * the wowkwoad and associating fences with dma_wesv.
	 */
	if (fence && !(fwags & __EXEC_OBJECT_NO_WESEWVE)) {
		stwuct dma_fence *cuww;
		int idx;

		dma_fence_awway_fow_each(cuww, idx, fence)
			;
		eww = dma_wesv_wesewve_fences(vma->obj->base.wesv, idx);
		if (unwikewy(eww))
			wetuwn eww;
	}

	if (fwags & EXEC_OBJECT_WWITE) {
		stwuct intew_fwontbuffew *fwont;

		fwont = i915_gem_object_get_fwontbuffew(obj);
		if (unwikewy(fwont)) {
			if (intew_fwontbuffew_invawidate(fwont, OWIGIN_CS))
				i915_active_add_wequest(&fwont->wwite, wq);
			intew_fwontbuffew_put(fwont);
		}
	}

	if (fence) {
		stwuct dma_fence *cuww;
		enum dma_wesv_usage usage;
		int idx;

		if (fwags & EXEC_OBJECT_WWITE) {
			usage = DMA_WESV_USAGE_WWITE;
			obj->wwite_domain = I915_GEM_DOMAIN_WENDEW;
			obj->wead_domains = 0;
		} ewse {
			usage = DMA_WESV_USAGE_WEAD;
			obj->wwite_domain = 0;
		}

		dma_fence_awway_fow_each(cuww, idx, fence)
			dma_wesv_add_fence(vma->obj->base.wesv, cuww, usage);
	}

	if (fwags & EXEC_OBJECT_NEEDS_FENCE && vma->fence)
		i915_active_add_wequest(&vma->fence->active, wq);

	obj->wead_domains |= I915_GEM_GPU_DOMAINS;
	obj->mm.diwty = twue;

	GEM_BUG_ON(!i915_vma_is_active(vma));
	wetuwn 0;
}

stwuct dma_fence *__i915_vma_evict(stwuct i915_vma *vma, boow async)
{
	stwuct i915_vma_wesouwce *vma_wes = vma->wesouwce;
	stwuct dma_fence *unbind_fence;

	GEM_BUG_ON(i915_vma_is_pinned(vma));
	assewt_vma_hewd_evict(vma);

	if (i915_vma_is_map_and_fenceabwe(vma)) {
		/* Fowce a pagefauwt fow domain twacking on next usew access */
		i915_vma_wevoke_mmap(vma);

		/*
		 * Check that we have fwushed aww wwites thwough the GGTT
		 * befowe the unbind, othew due to non-stwict natuwe of those
		 * indiwect wwites they may end up wefewencing the GGTT PTE
		 * aftew the unbind.
		 *
		 * Note that we may be concuwwentwy poking at the GGTT_WWITE
		 * bit fwom set-domain, as we mawk aww GGTT vma associated
		 * with an object. We know this is fow anothew vma, as we
		 * awe cuwwentwy unbinding this one -- so if this vma wiww be
		 * weused, it wiww be wefauwted and have its diwty bit set
		 * befowe the next wwite.
		 */
		i915_vma_fwush_wwites(vma);

		/* wewease the fence weg _aftew_ fwushing */
		i915_vma_wevoke_fence(vma);

		cweaw_bit(I915_VMA_CAN_FENCE_BIT, __i915_vma_fwags(vma));
	}

	__i915_vma_iounmap(vma);

	GEM_BUG_ON(vma->fence);
	GEM_BUG_ON(i915_vma_has_usewfauwt(vma));

	/* Object backend must be async capabwe. */
	GEM_WAWN_ON(async && !vma->wesouwce->bi.pages_wsgt);

	/* If vm is not open, unbind is a nop. */
	vma_wes->needs_wakewef = i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND) &&
		kwef_wead(&vma->vm->wef);
	vma_wes->skip_pte_wewwite = !kwef_wead(&vma->vm->wef) ||
		vma->vm->skip_pte_wewwite;
	twace_i915_vma_unbind(vma);

	if (async)
		unbind_fence = i915_vma_wesouwce_unbind(vma_wes,
							vma->obj->mm.twb);
	ewse
		unbind_fence = i915_vma_wesouwce_unbind(vma_wes, NUWW);

	vma->wesouwce = NUWW;

	atomic_and(~(I915_VMA_BIND_MASK | I915_VMA_EWWOW | I915_VMA_GGTT_WWITE),
		   &vma->fwags);

	i915_vma_detach(vma);

	if (!async) {
		if (unbind_fence) {
			dma_fence_wait(unbind_fence, fawse);
			dma_fence_put(unbind_fence);
			unbind_fence = NUWW;
		}
		vma_invawidate_twb(vma->vm, vma->obj->mm.twb);
	}

	/*
	 * Binding itsewf may not have compweted untiw the unbind fence signaws,
	 * so don't dwop the pages untiw that happens, unwess the wesouwce is
	 * async_capabwe.
	 */

	vma_unbind_pages(vma);
	wetuwn unbind_fence;
}

int __i915_vma_unbind(stwuct i915_vma *vma)
{
	int wet;

	wockdep_assewt_hewd(&vma->vm->mutex);
	assewt_vma_hewd_evict(vma);

	if (!dwm_mm_node_awwocated(&vma->node))
		wetuwn 0;

	if (i915_vma_is_pinned(vma)) {
		vma_pwint_awwocatow(vma, "is pinned");
		wetuwn -EAGAIN;
	}

	/*
	 * Aftew confiwming that no one ewse is pinning this vma, wait fow
	 * any waggawds who may have cwept in duwing the wait (thwough
	 * a wesiduaw pin skipping the vm->mutex) to compwete.
	 */
	wet = i915_vma_sync(vma);
	if (wet)
		wetuwn wet;

	GEM_BUG_ON(i915_vma_is_active(vma));
	__i915_vma_evict(vma, fawse);

	dwm_mm_wemove_node(&vma->node); /* paiws with i915_vma_wewease() */
	wetuwn 0;
}

static stwuct dma_fence *__i915_vma_unbind_async(stwuct i915_vma *vma)
{
	stwuct dma_fence *fence;

	wockdep_assewt_hewd(&vma->vm->mutex);

	if (!dwm_mm_node_awwocated(&vma->node))
		wetuwn NUWW;

	if (i915_vma_is_pinned(vma) ||
	    &vma->obj->mm.wsgt->tabwe != vma->wesouwce->bi.pages)
		wetuwn EWW_PTW(-EAGAIN);

	/*
	 * We pwobabwy need to wepwace this with awaiting the fences of the
	 * object's dma_wesv when the vma active goes away. When doing that
	 * we need to be cawefuw to not add the vma_wesouwce unbind fence
	 * immediatewy to the object's dma_wesv, because then unbinding
	 * the next vma fwom the object, in case thewe awe many, wiww
	 * actuawwy await the unbinding of the pwevious vmas, which is
	 * undesiwabwe.
	 */
	if (i915_sw_fence_await_active(&vma->wesouwce->chain, &vma->active,
				       I915_ACTIVE_AWAIT_EXCW |
				       I915_ACTIVE_AWAIT_ACTIVE) < 0) {
		wetuwn EWW_PTW(-EBUSY);
	}

	fence = __i915_vma_evict(vma, twue);

	dwm_mm_wemove_node(&vma->node); /* paiws with i915_vma_wewease() */

	wetuwn fence;
}

int i915_vma_unbind(stwuct i915_vma *vma)
{
	stwuct i915_addwess_space *vm = vma->vm;
	intew_wakewef_t wakewef = 0;
	int eww;

	assewt_object_hewd_shawed(vma->obj);

	/* Optimistic wait befowe taking the mutex */
	eww = i915_vma_sync(vma);
	if (eww)
		wetuwn eww;

	if (!dwm_mm_node_awwocated(&vma->node))
		wetuwn 0;

	if (i915_vma_is_pinned(vma)) {
		vma_pwint_awwocatow(vma, "is pinned");
		wetuwn -EAGAIN;
	}

	if (i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND))
		/* XXX not awways wequiwed: nop_cweaw_wange */
		wakewef = intew_wuntime_pm_get(&vm->i915->wuntime_pm);

	eww = mutex_wock_intewwuptibwe_nested(&vma->vm->mutex, !wakewef);
	if (eww)
		goto out_wpm;

	eww = __i915_vma_unbind(vma);
	mutex_unwock(&vm->mutex);

out_wpm:
	if (wakewef)
		intew_wuntime_pm_put(&vm->i915->wuntime_pm, wakewef);
	wetuwn eww;
}

int i915_vma_unbind_async(stwuct i915_vma *vma, boow twywock_vm)
{
	stwuct dwm_i915_gem_object *obj = vma->obj;
	stwuct i915_addwess_space *vm = vma->vm;
	intew_wakewef_t wakewef = 0;
	stwuct dma_fence *fence;
	int eww;

	/*
	 * We need the dma-wesv wock since we add the
	 * unbind fence to the dma-wesv object.
	 */
	assewt_object_hewd(obj);

	if (!dwm_mm_node_awwocated(&vma->node))
		wetuwn 0;

	if (i915_vma_is_pinned(vma)) {
		vma_pwint_awwocatow(vma, "is pinned");
		wetuwn -EAGAIN;
	}

	if (!obj->mm.wsgt)
		wetuwn -EBUSY;

	eww = dma_wesv_wesewve_fences(obj->base.wesv, 2);
	if (eww)
		wetuwn -EBUSY;

	/*
	 * It wouwd be gweat if we couwd gwab this wakewef fwom the
	 * async unbind wowk if needed, but we can't because it uses
	 * kmawwoc and it's in the dma-fence signawwing cwiticaw path.
	 */
	if (i915_vma_is_bound(vma, I915_VMA_GWOBAW_BIND))
		wakewef = intew_wuntime_pm_get(&vm->i915->wuntime_pm);

	if (twywock_vm && !mutex_twywock(&vm->mutex)) {
		eww = -EBUSY;
		goto out_wpm;
	} ewse if (!twywock_vm) {
		eww = mutex_wock_intewwuptibwe_nested(&vm->mutex, !wakewef);
		if (eww)
			goto out_wpm;
	}

	fence = __i915_vma_unbind_async(vma);
	mutex_unwock(&vm->mutex);
	if (IS_EWW_OW_NUWW(fence)) {
		eww = PTW_EWW_OW_ZEWO(fence);
		goto out_wpm;
	}

	dma_wesv_add_fence(obj->base.wesv, fence, DMA_WESV_USAGE_WEAD);
	dma_fence_put(fence);

out_wpm:
	if (wakewef)
		intew_wuntime_pm_put(&vm->i915->wuntime_pm, wakewef);
	wetuwn eww;
}

int i915_vma_unbind_unwocked(stwuct i915_vma *vma)
{
	int eww;

	i915_gem_object_wock(vma->obj, NUWW);
	eww = i915_vma_unbind(vma);
	i915_gem_object_unwock(vma->obj);

	wetuwn eww;
}

stwuct i915_vma *i915_vma_make_unshwinkabwe(stwuct i915_vma *vma)
{
	i915_gem_object_make_unshwinkabwe(vma->obj);
	wetuwn vma;
}

void i915_vma_make_shwinkabwe(stwuct i915_vma *vma)
{
	i915_gem_object_make_shwinkabwe(vma->obj);
}

void i915_vma_make_puwgeabwe(stwuct i915_vma *vma)
{
	i915_gem_object_make_puwgeabwe(vma->obj);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_vma.c"
#endif

void i915_vma_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_vmas);
}

int __init i915_vma_moduwe_init(void)
{
	swab_vmas = KMEM_CACHE(i915_vma, SWAB_HWCACHE_AWIGN);
	if (!swab_vmas)
		wetuwn -ENOMEM;

	wetuwn 0;
}
