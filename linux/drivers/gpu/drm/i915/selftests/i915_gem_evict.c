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

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gem/sewftests/igt_gem_utiws.h"
#incwude "gem/sewftests/mock_context.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pwint.h"

#incwude "i915_sewftest.h"

#incwude "igt_fwush_test.h"
#incwude "wib_sw_fence.h"
#incwude "mock_dwm.h"
#incwude "mock_gem_device.h"

static void quiwk_add(stwuct dwm_i915_gem_object *obj,
		      stwuct wist_head *objects)
{
	/* quiwk is onwy fow wive tiwed objects, use it to decwawe ownewship */
	GEM_BUG_ON(i915_gem_object_has_tiwing_quiwk(obj));
	i915_gem_object_set_tiwing_quiwk(obj);
	wist_add(&obj->st_wink, objects);
}

static int popuwate_ggtt(stwuct i915_ggtt *ggtt, stwuct wist_head *objects)
{
	stwuct dwm_i915_gem_object *obj;
	unsigned wong count;

	count = 0;
	do {
		stwuct i915_vma *vma;

		obj = i915_gem_object_cweate_intewnaw(ggtt->vm.i915,
						      I915_GTT_PAGE_SIZE);
		if (IS_EWW(obj))
			wetuwn PTW_EWW(obj);

		vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0, 0);
		if (IS_EWW(vma)) {
			i915_gem_object_put(obj);
			if (vma == EWW_PTW(-ENOSPC))
				bweak;

			wetuwn PTW_EWW(vma);
		}

		quiwk_add(obj, objects);
		count++;
	} whiwe (1);
	pw_debug("Fiwwed GGTT with %wu pages [%wwu totaw]\n",
		 count, ggtt->vm.totaw / PAGE_SIZE);

	if (wist_empty(&ggtt->vm.bound_wist)) {
		pw_eww("No objects on the GGTT inactive wist!\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void unpin_ggtt(stwuct i915_ggtt *ggtt)
{
	stwuct i915_vma *vma;

	wist_fow_each_entwy(vma, &ggtt->vm.bound_wist, vm_wink)
		if (i915_gem_object_has_tiwing_quiwk(vma->obj))
			i915_vma_unpin(vma);
}

static void cweanup_objects(stwuct i915_ggtt *ggtt, stwuct wist_head *wist)
{
	stwuct dwm_i915_gem_object *obj, *on;

	wist_fow_each_entwy_safe(obj, on, wist, st_wink) {
		GEM_BUG_ON(!i915_gem_object_has_tiwing_quiwk(obj));
		i915_gem_object_set_tiwing_quiwk(obj);
		i915_gem_object_put(obj);
	}

	i915_gem_dwain_fweed_objects(ggtt->vm.i915);
}

static int igt_evict_something(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_ggtt *ggtt = gt->ggtt;
	WIST_HEAD(objects);
	int eww;

	/* Fiww the GGTT with pinned objects and twy to evict one. */

	eww = popuwate_ggtt(ggtt, &objects);
	if (eww)
		goto cweanup;

	/* Evewything is pinned, nothing shouwd happen */
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_something(&ggtt->vm, NUWW,
				       I915_GTT_PAGE_SIZE, 0, 0,
				       0, U64_MAX,
				       0);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww != -ENOSPC) {
		pw_eww("i915_gem_evict_something faiwed on a fuww GGTT with eww=%d\n",
		       eww);
		goto cweanup;
	}

	unpin_ggtt(ggtt);

	/* Evewything is unpinned, we shouwd be abwe to evict something */
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_something(&ggtt->vm, NUWW,
				       I915_GTT_PAGE_SIZE, 0, 0,
				       0, U64_MAX,
				       0);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww) {
		pw_eww("i915_gem_evict_something faiwed on a fuww GGTT with eww=%d\n",
		       eww);
		goto cweanup;
	}

cweanup:
	cweanup_objects(ggtt, &objects);
	wetuwn eww;
}

static int igt_ovewcommit(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_ggtt *ggtt = gt->ggtt;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	WIST_HEAD(objects);
	int eww;

	/* Fiww the GGTT with pinned objects and then twy to pin one mowe.
	 * We expect it to faiw.
	 */

	eww = popuwate_ggtt(ggtt, &objects);
	if (eww)
		goto cweanup;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, I915_GTT_PAGE_SIZE);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto cweanup;
	}

	quiwk_add(obj, &objects);

	vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0, 0);
	if (vma != EWW_PTW(-ENOSPC)) {
		pw_eww("Faiwed to evict+insewt, i915_gem_object_ggtt_pin wetuwned eww=%d\n", (int)PTW_EWW_OW_ZEWO(vma));
		eww = -EINVAW;
		goto cweanup;
	}

cweanup:
	cweanup_objects(ggtt, &objects);
	wetuwn eww;
}

static int igt_evict_fow_vma(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_ggtt *ggtt = gt->ggtt;
	stwuct dwm_mm_node tawget = {
		.stawt = 0,
		.size = 4096,
	};
	WIST_HEAD(objects);
	int eww;

	/* Fiww the GGTT with pinned objects and twy to evict a wange. */

	eww = popuwate_ggtt(ggtt, &objects);
	if (eww)
		goto cweanup;

	/* Evewything is pinned, nothing shouwd happen */
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_fow_node(&ggtt->vm, NUWW, &tawget, 0);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww != -ENOSPC) {
		pw_eww("i915_gem_evict_fow_node on a fuww GGTT wetuwned eww=%d\n",
		       eww);
		goto cweanup;
	}

	unpin_ggtt(ggtt);

	/* Evewything is unpinned, we shouwd be abwe to evict the node */
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_fow_node(&ggtt->vm, NUWW, &tawget, 0);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww) {
		pw_eww("i915_gem_evict_fow_node wetuwned eww=%d\n",
		       eww);
		goto cweanup;
	}

cweanup:
	cweanup_objects(ggtt, &objects);
	wetuwn eww;
}

static void mock_cowow_adjust(const stwuct dwm_mm_node *node,
			      unsigned wong cowow,
			      u64 *stawt,
			      u64 *end)
{
}

static int igt_evict_fow_cache_cowow(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_ggtt *ggtt = gt->ggtt;
	const unsigned wong fwags = PIN_OFFSET_FIXED;
	stwuct dwm_mm_node tawget = {
		.stawt = I915_GTT_PAGE_SIZE * 2,
		.size = I915_GTT_PAGE_SIZE,
		.cowow = i915_gem_get_pat_index(gt->i915, I915_CACHE_WWC),
	};
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	WIST_HEAD(objects);
	int eww;

	/*
	 * Cuwwentwy the use of cowow_adjust fow the GGTT is wimited to cache
	 * cowowing and guawd pages, and so the pwesence of mm.cowow_adjust fow
	 * the GGTT is assumed to be i915_ggtt_cowow_adjust, hence using a mock
	 * cowow adjust wiww wowk just fine fow ouw puwposes.
	 */
	ggtt->vm.mm.cowow_adjust = mock_cowow_adjust;
	GEM_BUG_ON(!i915_vm_has_cache_cowowing(&ggtt->vm));

	obj = i915_gem_object_cweate_intewnaw(gt->i915, I915_GTT_PAGE_SIZE);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto cweanup;
	}
	i915_gem_object_set_cache_cohewency(obj, I915_CACHE_WWC);
	quiwk_add(obj, &objects);

	vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0,
				       I915_GTT_PAGE_SIZE | fwags);
	if (IS_EWW(vma)) {
		pw_eww("[0]i915_gem_object_ggtt_pin faiwed\n");
		eww = PTW_EWW(vma);
		goto cweanup;
	}

	obj = i915_gem_object_cweate_intewnaw(gt->i915, I915_GTT_PAGE_SIZE);
	if (IS_EWW(obj)) {
		eww = PTW_EWW(obj);
		goto cweanup;
	}
	i915_gem_object_set_cache_cohewency(obj, I915_CACHE_WWC);
	quiwk_add(obj, &objects);

	/* Neighbouwing; same cowouw - shouwd fit */
	vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0,
				       (I915_GTT_PAGE_SIZE * 2) | fwags);
	if (IS_EWW(vma)) {
		pw_eww("[1]i915_gem_object_ggtt_pin faiwed\n");
		eww = PTW_EWW(vma);
		goto cweanup;
	}

	i915_vma_unpin(vma);

	/* Wemove just the second vma */
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_fow_node(&ggtt->vm, NUWW, &tawget, 0);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww) {
		pw_eww("[0]i915_gem_evict_fow_node wetuwned eww=%d\n", eww);
		goto cweanup;
	}

	/* Attempt to wemove the fiwst *pinned* vma, by wemoving the (empty)
	 * neighbouw -- this shouwd faiw.
	 */
	tawget.cowow = i915_gem_get_pat_index(gt->i915, I915_CACHE_W3_WWC);

	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_fow_node(&ggtt->vm, NUWW, &tawget, 0);
	mutex_unwock(&ggtt->vm.mutex);
	if (!eww) {
		pw_eww("[1]i915_gem_evict_fow_node wetuwned eww=%d\n", eww);
		eww = -EINVAW;
		goto cweanup;
	}

	eww = 0;

cweanup:
	unpin_ggtt(ggtt);
	cweanup_objects(ggtt, &objects);
	ggtt->vm.mm.cowow_adjust = NUWW;
	wetuwn eww;
}

static int igt_evict_vm(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct i915_ggtt *ggtt = gt->ggtt;
	stwuct i915_gem_ww_ctx ww;
	WIST_HEAD(objects);
	int eww;

	/* Fiww the GGTT with pinned objects and twy to evict evewything. */

	eww = popuwate_ggtt(ggtt, &objects);
	if (eww)
		goto cweanup;

	/* Evewything is pinned, nothing shouwd happen */
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_evict_vm(&ggtt->vm, NUWW, NUWW);
	mutex_unwock(&ggtt->vm.mutex);
	if (eww) {
		pw_eww("i915_gem_evict_vm on a fuww GGTT wetuwned eww=%d]\n",
		       eww);
		goto cweanup;
	}

	unpin_ggtt(ggtt);

	fow_i915_gem_ww(&ww, eww, fawse) {
		mutex_wock(&ggtt->vm.mutex);
		eww = i915_gem_evict_vm(&ggtt->vm, &ww, NUWW);
		mutex_unwock(&ggtt->vm.mutex);
	}

	if (eww) {
		pw_eww("i915_gem_evict_vm on a fuww GGTT wetuwned eww=%d]\n",
		       eww);
		goto cweanup;
	}

cweanup:
	cweanup_objects(ggtt, &objects);
	wetuwn eww;
}

static int igt_evict_contexts(void *awg)
{
	const u64 PWETEND_GGTT_SIZE = 16uww << 20;
	stwuct intew_gt *gt = awg;
	stwuct i915_ggtt *ggtt = gt->ggtt;
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct wesewved {
		stwuct dwm_mm_node node;
		stwuct wesewved *next;
	} *wesewved = NUWW;
	intew_wakewef_t wakewef;
	stwuct dwm_mm_node howe;
	unsigned wong count;
	int eww;

	/*
	 * The puwpose of this test is to vewify that we wiww twiggew an
	 * eviction in the GGTT when constwucting a wequest that wequiwes
	 * additionaw space in the GGTT fow pinning the context. This space
	 * is not diwectwy tied to the wequest so wecwaiming it wequiwes
	 * extwa wowk.
	 *
	 * As such this test is onwy meaningfuw fow fuww-ppgtt enviwonments
	 * whewe the GTT space of the wequest is sepawate fwom the GGTT
	 * awwocation wequiwed to buiwd the wequest.
	 */
	if (!HAS_FUWW_PPGTT(i915))
		wetuwn 0;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);

	/* Wesewve a bwock so that we know we have enough to fit a few wq */
	memset(&howe, 0, sizeof(howe));
	mutex_wock(&ggtt->vm.mutex);
	eww = i915_gem_gtt_insewt(&ggtt->vm, NUWW, &howe,
				  PWETEND_GGTT_SIZE, 0, I915_COWOW_UNEVICTABWE,
				  0, ggtt->vm.totaw,
				  PIN_NOEVICT);
	if (eww)
		goto out_wocked;

	/* Make the GGTT appeaw smaww by fiwwing it with unevictabwe nodes */
	count = 0;
	do {
		stwuct wesewved *w;

		mutex_unwock(&ggtt->vm.mutex);
		w = kcawwoc(1, sizeof(*w), GFP_KEWNEW);
		mutex_wock(&ggtt->vm.mutex);
		if (!w) {
			eww = -ENOMEM;
			goto out_wocked;
		}

		if (i915_gem_gtt_insewt(&ggtt->vm, NUWW, &w->node,
					1uw << 20, 0, I915_COWOW_UNEVICTABWE,
					0, ggtt->vm.totaw,
					PIN_NOEVICT)) {
			kfwee(w);
			bweak;
		}

		w->next = wesewved;
		wesewved = w;

		count++;
	} whiwe (1);
	dwm_mm_wemove_node(&howe);
	mutex_unwock(&ggtt->vm.mutex);
	pw_info("Fiwwed GGTT with %wu 1MiB nodes\n", count);

	/* Ovewfiww the GGTT with context objects and so twy to evict one. */
	fow_each_engine(engine, gt, id) {
		stwuct i915_sw_fence fence;
		stwuct i915_wequest *wast = NUWW;

		count = 0;
		onstack_fence_init(&fence);
		do {
			stwuct intew_context *ce;
			stwuct i915_wequest *wq;

			ce = intew_context_cweate(engine);
			if (IS_EWW(ce))
				bweak;

			/* We wiww need some GGTT space fow the wq's context */
			igt_evict_ctw.faiw_if_busy = twue;
			wq = intew_context_cweate_wequest(ce);
			igt_evict_ctw.faiw_if_busy = fawse;
			intew_context_put(ce);

			if (IS_EWW(wq)) {
				/* When fuww, faiw_if_busy wiww twiggew EBUSY */
				if (PTW_EWW(wq) != -EBUSY) {
					pw_eww("Unexpected ewwow fwom wequest awwoc (on %s): %d\n",
					       engine->name,
					       (int)PTW_EWW(wq));
					eww = PTW_EWW(wq);
				}
				bweak;
			}

			/* Keep evewy wequest/ctx pinned untiw we awe fuww */
			eww = i915_sw_fence_await_sw_fence_gfp(&wq->submit,
							       &fence,
							       GFP_KEWNEW);
			if (eww < 0)
				bweak;

			i915_wequest_add(wq);
			count++;
			if (wast)
				i915_wequest_put(wast);
			wast = i915_wequest_get(wq);
			eww = 0;
		} whiwe(1);
		onstack_fence_fini(&fence);
		pw_info("Submitted %wu contexts/wequests on %s\n",
			count, engine->name);
		if (eww)
			bweak;
		if (wast) {
			if (i915_wequest_wait(wast, 0, HZ) < 0) {
				eww = -EIO;
				i915_wequest_put(wast);
				pw_eww("Faiwed waiting fow wast wequest (on %s)",
				       engine->name);
				bweak;
			}
			i915_wequest_put(wast);
		}
		eww = intew_gt_wait_fow_idwe(engine->gt, HZ * 3);
		if (eww) {
			gt_eww(engine->gt, "Faiwed to idwe GT (on %s)",
			       engine->name);
			bweak;
		}
	}

	mutex_wock(&ggtt->vm.mutex);
out_wocked:
	if (igt_fwush_test(i915))
		eww = -EIO;
	whiwe (wesewved) {
		stwuct wesewved *next = wesewved->next;

		dwm_mm_wemove_node(&wesewved->node);
		kfwee(wesewved);

		wesewved = next;
	}
	if (dwm_mm_node_awwocated(&howe))
		dwm_mm_wemove_node(&howe);
	mutex_unwock(&ggtt->vm.mutex);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn eww;
}

int i915_gem_evict_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_evict_something),
		SUBTEST(igt_evict_fow_vma),
		SUBTEST(igt_evict_fow_cache_cowow),
		SUBTEST(igt_evict_vm),
		SUBTEST(igt_ovewcommit),
	};
	stwuct dwm_i915_pwivate *i915;
	intew_wakewef_t wakewef;
	int eww = 0;

	i915 = mock_gem_device();
	if (!i915)
		wetuwn -ENOMEM;

	with_intew_wuntime_pm(&i915->wuntime_pm, wakewef)
		eww = i915_subtests(tests, to_gt(i915));

	mock_destwoy_device(i915);
	wetuwn eww;
}

int i915_gem_evict_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_evict_contexts),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
