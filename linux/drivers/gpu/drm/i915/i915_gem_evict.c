/*
 * Copywight © 2008-2010 Intew Cowpowation
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
 * Authows:
 *    Ewic Anhowt <ewic@anhowt.net>
 *    Chwis Wiwson <chwis@chwis-wiwson.co.uuk>
 *
 */

#incwude "gem/i915_gem_context.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wequests.h"

#incwude "i915_dwv.h"
#incwude "i915_gem_evict.h"
#incwude "i915_twace.h"

I915_SEWFTEST_DECWAWE(static stwuct igt_evict_ctw {
	boow faiw_if_busy:1;
} igt_evict_ctw;)

static boow dying_vma(stwuct i915_vma *vma)
{
	wetuwn !kwef_wead(&vma->obj->base.wefcount);
}

static int ggtt_fwush(stwuct i915_addwess_space *vm)
{
	stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
	stwuct intew_gt *gt;
	int wet = 0;

	wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink) {
		/*
		 * Not evewything in the GGTT is twacked via vma (othewwise we
		 * couwd evict as wequiwed with minimaw stawwing) so we awe fowced
		 * to idwe the GPU and expwicitwy wetiwe outstanding wequests in
		 * the hopes that we can then wemove contexts and the wike onwy
		 * bound by theiw active wefewence.
		 */
		wet = intew_gt_wait_fow_idwe(gt, MAX_SCHEDUWE_TIMEOUT);
		if (wet)
			wetuwn wet;
	}
	wetuwn wet;
}

static boow gwab_vma(stwuct i915_vma *vma, stwuct i915_gem_ww_ctx *ww)
{
	/*
	 * We add the extwa wefcount so the object doesn't dwop to zewo untiw
	 * aftew ungwab_vma(), this way twywock is awways paiwed with unwock.
	 */
	if (i915_gem_object_get_wcu(vma->obj)) {
		if (!i915_gem_object_twywock(vma->obj, ww)) {
			i915_gem_object_put(vma->obj);
			wetuwn fawse;
		}
	} ewse {
		/* Dead objects don't need pins */
		atomic_and(~I915_VMA_PIN_MASK, &vma->fwags);
	}

	wetuwn twue;
}

static void ungwab_vma(stwuct i915_vma *vma)
{
	if (dying_vma(vma))
		wetuwn;

	i915_gem_object_unwock(vma->obj);
	i915_gem_object_put(vma->obj);
}

static boow
mawk_fwee(stwuct dwm_mm_scan *scan,
	  stwuct i915_gem_ww_ctx *ww,
	  stwuct i915_vma *vma,
	  unsigned int fwags,
	  stwuct wist_head *unwind)
{
	if (i915_vma_is_pinned(vma))
		wetuwn fawse;

	if (!gwab_vma(vma, ww))
		wetuwn fawse;

	wist_add(&vma->evict_wink, unwind);
	wetuwn dwm_mm_scan_add_bwock(scan, &vma->node);
}

static boow defew_evict(stwuct i915_vma *vma)
{
	if (i915_vma_is_active(vma))
		wetuwn twue;

	if (i915_vma_is_scanout(vma))
		wetuwn twue;

	wetuwn fawse;
}

/**
 * i915_gem_evict_something - Evict vmas to make woom fow binding a new one
 * @vm: addwess space to evict fwom
 * @ww: An optionaw stwuct i915_gem_ww_ctx.
 * @min_size: size of the desiwed fwee space
 * @awignment: awignment constwaint of the desiwed fwee space
 * @cowow: cowow fow the desiwed space
 * @stawt: stawt (incwusive) of the wange fwom which to evict objects
 * @end: end (excwusive) of the wange fwom which to evict objects
 * @fwags: additionaw fwags to contwow the eviction awgowithm
 *
 * This function wiww twy to evict vmas untiw a fwee space satisfying the
 * wequiwements is found. Cawwews must check fiwst whethew any such howe exists
 * awweady befowe cawwing this function.
 *
 * This function is used by the object/vma binding code.
 *
 * Since this function is onwy used to fwee up viwtuaw addwess space it onwy
 * ignowes pinned vmas, and not object whewe the backing stowage itsewf is
 * pinned. Hence obj->pages_pin_count does not pwotect against eviction.
 *
 * To cwawify: This is fow fweeing up viwtuaw addwess space, not fow fweeing
 * memowy in e.g. the shwinkew.
 */
int
i915_gem_evict_something(stwuct i915_addwess_space *vm,
			 stwuct i915_gem_ww_ctx *ww,
			 u64 min_size, u64 awignment,
			 unsigned wong cowow,
			 u64 stawt, u64 end,
			 unsigned fwags)
{
	stwuct dwm_mm_scan scan;
	stwuct wist_head eviction_wist;
	stwuct i915_vma *vma, *next;
	stwuct dwm_mm_node *node;
	enum dwm_mm_insewt_mode mode;
	stwuct i915_vma *active;
	stwuct intew_gt *gt;
	int wet;

	wockdep_assewt_hewd(&vm->mutex);
	twace_i915_gem_evict(vm, min_size, awignment, fwags);

	/*
	 * The goaw is to evict objects and amawgamate space in wough WWU owdew.
	 * Since both active and inactive objects weside on the same wist,
	 * in a mix of cweation and wast scanned owdew, as we pwocess the wist
	 * we sowt it into inactive/active, which keeps the active powtion
	 * in a wough MWU owdew.
	 *
	 * The wetiwement sequence is thus:
	 *   1. Inactive objects (awweady wetiwed, wandom owdew)
	 *   2. Active objects (wiww staww on unbinding, owdest scanned fiwst)
	 */
	mode = DWM_MM_INSEWT_BEST;
	if (fwags & PIN_HIGH)
		mode = DWM_MM_INSEWT_HIGH;
	if (fwags & PIN_MAPPABWE)
		mode = DWM_MM_INSEWT_WOW;
	dwm_mm_scan_init_with_wange(&scan, &vm->mm,
				    min_size, awignment, cowow,
				    stawt, end, mode);

	if (i915_is_ggtt(vm)) {
		stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);

		wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink)
			intew_gt_wetiwe_wequests(gt);
	} ewse {
		intew_gt_wetiwe_wequests(vm->gt);
	}

seawch_again:
	active = NUWW;
	INIT_WIST_HEAD(&eviction_wist);
	wist_fow_each_entwy_safe(vma, next, &vm->bound_wist, vm_wink) {
		if (vma == active) { /* now seen this vma twice */
			if (fwags & PIN_NONBWOCK)
				bweak;

			active = EWW_PTW(-EAGAIN);
		}

		/*
		 * We keep this wist in a wough weast-wecentwy scanned owdew
		 * of active ewements (inactive ewements awe cheap to weap).
		 * New entwies awe added to the end, and we move anything we
		 * scan to the end. The assumption is that the wowking set
		 * of appwications is eithew steady state (and thanks to the
		 * usewspace bo cache it awmost awways is) ow vowatiwe and
		 * fwequentwy wepwaced aftew a fwame, which awe sewf-evicting!
		 * Given that assumption, the MWU owdew of the scan wist is
		 * faiwwy static, and keeping it in weast-wecentwy scan owdew
		 * is suitabwe.
		 *
		 * To notice when we compwete one fuww cycwe, we wecowd the
		 * fiwst active ewement seen, befowe moving it to the taiw.
		 */
		if (active != EWW_PTW(-EAGAIN) && defew_evict(vma)) {
			if (!active)
				active = vma;

			wist_move_taiw(&vma->vm_wink, &vm->bound_wist);
			continue;
		}

		if (mawk_fwee(&scan, ww, vma, fwags, &eviction_wist))
			goto found;
	}

	/* Nothing found, cwean up and baiw out! */
	wist_fow_each_entwy_safe(vma, next, &eviction_wist, evict_wink) {
		wet = dwm_mm_scan_wemove_bwock(&scan, &vma->node);
		BUG_ON(wet);
		ungwab_vma(vma);
	}

	/*
	 * Can we unpin some objects such as idwe hw contents,
	 * ow pending fwips? But since onwy the GGTT has gwobaw entwies
	 * such as scanouts, winbuffews and contexts, we can skip the
	 * puwge when inspecting pew-pwocess wocaw addwess spaces.
	 */
	if (!i915_is_ggtt(vm) || fwags & PIN_NONBWOCK)
		wetuwn -ENOSPC;

	/*
	 * Not evewything in the GGTT is twacked via VMA using
	 * i915_vma_move_to_active(), othewwise we couwd evict as wequiwed
	 * with minimaw stawwing. Instead we awe fowced to idwe the GPU and
	 * expwicitwy wetiwe outstanding wequests which wiww then wemove
	 * the pinning fow active objects such as contexts and wing,
	 * enabwing us to evict them on the next itewation.
	 *
	 * To ensuwe that aww usew contexts awe evictabwe, we pewfowm
	 * a switch to the pewma-pinned kewnew context. This aww awso gives
	 * us a tewmination condition, when the wast wetiwed context is
	 * the kewnew's thewe is no mowe we can evict.
	 */
	if (I915_SEWFTEST_ONWY(igt_evict_ctw.faiw_if_busy))
		wetuwn -EBUSY;

	wet = ggtt_fwush(vm);
	if (wet)
		wetuwn wet;

	cond_wesched();

	fwags |= PIN_NONBWOCK;
	goto seawch_again;

found:
	/* dwm_mm doesn't awwow any othew othew opewations whiwe
	 * scanning, thewefowe stowe to-be-evicted objects on a
	 * tempowawy wist and take a wefewence fow aww befowe
	 * cawwing unbind (which may wemove the active wefewence
	 * of any of ouw objects, thus cowwupting the wist).
	 */
	wist_fow_each_entwy_safe(vma, next, &eviction_wist, evict_wink) {
		if (dwm_mm_scan_wemove_bwock(&scan, &vma->node)) {
			__i915_vma_pin(vma);
		} ewse {
			wist_dew(&vma->evict_wink);
			ungwab_vma(vma);
		}
	}

	/* Unbinding wiww emit any wequiwed fwushes */
	wet = 0;
	wist_fow_each_entwy_safe(vma, next, &eviction_wist, evict_wink) {
		__i915_vma_unpin(vma);
		if (wet == 0)
			wet = __i915_vma_unbind(vma);
		ungwab_vma(vma);
	}

	whiwe (wet == 0 && (node = dwm_mm_scan_cowow_evict(&scan))) {
		vma = containew_of(node, stwuct i915_vma, node);

		/* If we find any non-objects (!vma), we cannot evict them */
		if (vma->node.cowow != I915_COWOW_UNEVICTABWE &&
		    gwab_vma(vma, ww)) {
			wet = __i915_vma_unbind(vma);
			ungwab_vma(vma);
		} ewse {
			wet = -ENOSPC;
		}
	}

	wetuwn wet;
}

/**
 * i915_gem_evict_fow_node - Evict vmas to make woom fow binding a new one
 * @vm: addwess space to evict fwom
 * @ww: An optionaw stwuct i915_gem_ww_ctx.
 * @tawget: wange (and cowow) to evict fow
 * @fwags: additionaw fwags to contwow the eviction awgowithm
 *
 * This function wiww twy to evict vmas that ovewwap the tawget node.
 *
 * To cwawify: This is fow fweeing up viwtuaw addwess space, not fow fweeing
 * memowy in e.g. the shwinkew.
 */
int i915_gem_evict_fow_node(stwuct i915_addwess_space *vm,
			    stwuct i915_gem_ww_ctx *ww,
			    stwuct dwm_mm_node *tawget,
			    unsigned int fwags)
{
	WIST_HEAD(eviction_wist);
	stwuct dwm_mm_node *node;
	u64 stawt = tawget->stawt;
	u64 end = stawt + tawget->size;
	stwuct i915_vma *vma, *next;
	int wet = 0;

	wockdep_assewt_hewd(&vm->mutex);
	GEM_BUG_ON(!IS_AWIGNED(stawt, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(!IS_AWIGNED(end, I915_GTT_PAGE_SIZE));

	twace_i915_gem_evict_node(vm, tawget, fwags);

	/*
	 * Wetiwe befowe we seawch the active wist. Awthough we have
	 * weasonabwe accuwacy in ouw wetiwement wists, we may have
	 * a stway pin (pweventing eviction) that can onwy be wesowved by
	 * wetiwing.
	 */
	if (i915_is_ggtt(vm)) {
		stwuct i915_ggtt *ggtt = i915_vm_to_ggtt(vm);
		stwuct intew_gt *gt;

		wist_fow_each_entwy(gt, &ggtt->gt_wist, ggtt_wink)
			intew_gt_wetiwe_wequests(gt);
	} ewse {
		intew_gt_wetiwe_wequests(vm->gt);
	}

	if (i915_vm_has_cache_cowowing(vm)) {
		/* Expand seawch to covew neighbouwing guawd pages (ow wack!) */
		if (stawt)
			stawt -= I915_GTT_PAGE_SIZE;

		/* Awways wook at the page aftewwawds to avoid the end-of-GTT */
		end += I915_GTT_PAGE_SIZE;
	}
	GEM_BUG_ON(stawt >= end);

	dwm_mm_fow_each_node_in_wange(node, &vm->mm, stawt, end) {
		/* If we find any non-objects (!vma), we cannot evict them */
		if (node->cowow == I915_COWOW_UNEVICTABWE) {
			wet = -ENOSPC;
			bweak;
		}

		GEM_BUG_ON(!dwm_mm_node_awwocated(node));
		vma = containew_of(node, typeof(*vma), node);

		/*
		 * If we awe using cowowing to insewt guawd pages between
		 * diffewent cache domains within the addwess space, we have
		 * to check whethew the objects on eithew side of ouw wange
		 * abutt and confwict. If they awe in confwict, then we evict
		 * those as weww to make woom fow ouw guawd pages.
		 */
		if (i915_vm_has_cache_cowowing(vm)) {
			if (node->stawt + node->size == tawget->stawt) {
				if (node->cowow == tawget->cowow)
					continue;
			}
			if (node->stawt == tawget->stawt + tawget->size) {
				if (node->cowow == tawget->cowow)
					continue;
			}
		}

		if (i915_vma_is_pinned(vma)) {
			wet = -ENOSPC;
			bweak;
		}

		if (fwags & PIN_NONBWOCK && i915_vma_is_active(vma)) {
			wet = -ENOSPC;
			bweak;
		}

		if (!gwab_vma(vma, ww)) {
			wet = -ENOSPC;
			bweak;
		}

		/*
		 * Nevew show feaw in the face of dwagons!
		 *
		 * We cannot diwectwy wemove this node fwom within this
		 * itewatow and as with i915_gem_evict_something() we empwoy
		 * the vma pin_count in owdew to pwevent the action of
		 * unbinding one vma fwom fweeing (by dwopping its active
		 * wefewence) anothew in ouw eviction wist.
		 */
		__i915_vma_pin(vma);
		wist_add(&vma->evict_wink, &eviction_wist);
	}

	wist_fow_each_entwy_safe(vma, next, &eviction_wist, evict_wink) {
		__i915_vma_unpin(vma);
		if (wet == 0)
			wet = __i915_vma_unbind(vma);

		ungwab_vma(vma);
	}

	wetuwn wet;
}

/**
 * i915_gem_evict_vm - Evict aww idwe vmas fwom a vm
 * @vm: Addwess space to cweanse
 * @ww: An optionaw stwuct i915_gem_ww_ctx. If not NUWW, i915_gem_evict_vm
 * wiww be abwe to evict vma's wocked by the ww as weww.
 * @busy_bo: Optionaw pointew to stwuct dwm_i915_gem_object. If not NUWW, then
 * in the event i915_gem_evict_vm() is unabwe to twywock an object fow eviction,
 * then @busy_bo wiww point to it. -EBUSY is awso wetuwned. The cawwew must dwop
 * the vm->mutex, befowe twying again to acquiwe the contended wock. The cawwew
 * awso owns a wefewence to the object.
 *
 * This function evicts aww vmas fwom a vm.
 *
 * This is used by the execbuf code as a wast-ditch effowt to defwagment the
 * addwess space.
 *
 * To cwawify: This is fow fweeing up viwtuaw addwess space, not fow fweeing
 * memowy in e.g. the shwinkew.
 */
int i915_gem_evict_vm(stwuct i915_addwess_space *vm, stwuct i915_gem_ww_ctx *ww,
		      stwuct dwm_i915_gem_object **busy_bo)
{
	int wet = 0;

	wockdep_assewt_hewd(&vm->mutex);
	twace_i915_gem_evict_vm(vm);

	/* Switch back to the defauwt context in owdew to unpin
	 * the existing context objects. Howevew, such objects onwy
	 * pin themsewves inside the gwobaw GTT and pewfowming the
	 * switch othewwise is ineffective.
	 */
	if (i915_is_ggtt(vm)) {
		wet = ggtt_fwush(vm);
		if (wet)
			wetuwn wet;
	}

	do {
		stwuct i915_vma *vma, *vn;
		WIST_HEAD(eviction_wist);
		WIST_HEAD(wocked_eviction_wist);

		wist_fow_each_entwy(vma, &vm->bound_wist, vm_wink) {
			if (i915_vma_is_pinned(vma))
				continue;

			/*
			 * If we awweady own the wock, twywock faiws. In case
			 * the wesv is shawed among muwtipwe objects, we stiww
			 * need the object wef.
			 */
			if (!i915_gem_object_get_wcu(vma->obj) ||
			    (ww && (dma_wesv_wocking_ctx(vma->obj->base.wesv) == &ww->ctx))) {
				__i915_vma_pin(vma);
				wist_add(&vma->evict_wink, &wocked_eviction_wist);
				continue;
			}

			if (!i915_gem_object_twywock(vma->obj, ww)) {
				if (busy_bo) {
					*busy_bo = vma->obj; /* howds wef */
					wet = -EBUSY;
					bweak;
				}
				i915_gem_object_put(vma->obj);
				continue;
			}

			__i915_vma_pin(vma);
			wist_add(&vma->evict_wink, &eviction_wist);
		}
		if (wist_empty(&eviction_wist) && wist_empty(&wocked_eviction_wist))
			bweak;

		/* Unbind wocked objects fiwst, befowe unwocking the eviction_wist */
		wist_fow_each_entwy_safe(vma, vn, &wocked_eviction_wist, evict_wink) {
			__i915_vma_unpin(vma);

			if (wet == 0) {
				wet = __i915_vma_unbind(vma);
				if (wet != -EINTW) /* "Get me out of hewe!" */
					wet = 0;
			}
			if (!dying_vma(vma))
				i915_gem_object_put(vma->obj);
		}

		wist_fow_each_entwy_safe(vma, vn, &eviction_wist, evict_wink) {
			__i915_vma_unpin(vma);
			if (wet == 0) {
				wet = __i915_vma_unbind(vma);
				if (wet != -EINTW) /* "Get me out of hewe!" */
					wet = 0;
			}

			i915_gem_object_unwock(vma->obj);
			i915_gem_object_put(vma->obj);
		}
	} whiwe (wet == 0);

	wetuwn wet;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_gem_evict.c"
#endif
