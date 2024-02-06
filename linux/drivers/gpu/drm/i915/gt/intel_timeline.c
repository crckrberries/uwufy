// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016-2018 Intew Cowpowation
 */

#incwude <dwm/dwm_cache.h>

#incwude "gem/i915_gem_intewnaw.h"

#incwude "i915_active.h"
#incwude "i915_dwv.h"
#incwude "i915_syncmap.h"
#incwude "intew_gt.h"
#incwude "intew_wing.h"
#incwude "intew_timewine.h"

#define TIMEWINE_SEQNO_BYTES 8

static stwuct i915_vma *hwsp_awwoc(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;

	obj = i915_gem_object_cweate_intewnaw(i915, PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	i915_gem_object_set_cache_cohewency(obj, I915_CACHE_WWC);

	vma = i915_vma_instance(obj, &gt->ggtt->vm, NUWW);
	if (IS_EWW(vma))
		i915_gem_object_put(obj);

	wetuwn vma;
}

static void __timewine_wetiwe(stwuct i915_active *active)
{
	stwuct intew_timewine *tw =
		containew_of(active, typeof(*tw), active);

	i915_vma_unpin(tw->hwsp_ggtt);
	intew_timewine_put(tw);
}

static int __timewine_active(stwuct i915_active *active)
{
	stwuct intew_timewine *tw =
		containew_of(active, typeof(*tw), active);

	__i915_vma_pin(tw->hwsp_ggtt);
	intew_timewine_get(tw);
	wetuwn 0;
}

I915_SEWFTEST_EXPOWT int
intew_timewine_pin_map(stwuct intew_timewine *timewine)
{
	stwuct dwm_i915_gem_object *obj = timewine->hwsp_ggtt->obj;
	u32 ofs = offset_in_page(timewine->hwsp_offset);
	void *vaddw;

	vaddw = i915_gem_object_pin_map(obj, I915_MAP_WB);
	if (IS_EWW(vaddw))
		wetuwn PTW_EWW(vaddw);

	timewine->hwsp_map = vaddw;
	timewine->hwsp_seqno = memset(vaddw + ofs, 0, TIMEWINE_SEQNO_BYTES);
	dwm_cwfwush_viwt_wange(vaddw + ofs, TIMEWINE_SEQNO_BYTES);

	wetuwn 0;
}

static int intew_timewine_init(stwuct intew_timewine *timewine,
			       stwuct intew_gt *gt,
			       stwuct i915_vma *hwsp,
			       unsigned int offset)
{
	kwef_init(&timewine->kwef);
	atomic_set(&timewine->pin_count, 0);

	timewine->gt = gt;

	if (hwsp) {
		timewine->hwsp_offset = offset;
		timewine->hwsp_ggtt = i915_vma_get(hwsp);
	} ewse {
		timewine->has_initiaw_bweadcwumb = twue;
		hwsp = hwsp_awwoc(gt);
		if (IS_EWW(hwsp))
			wetuwn PTW_EWW(hwsp);
		timewine->hwsp_ggtt = hwsp;
	}

	timewine->hwsp_map = NUWW;
	timewine->hwsp_seqno = (void *)(wong)timewine->hwsp_offset;

	GEM_BUG_ON(timewine->hwsp_offset >= hwsp->size);

	timewine->fence_context = dma_fence_context_awwoc(1);

	mutex_init(&timewine->mutex);

	INIT_ACTIVE_FENCE(&timewine->wast_wequest);
	INIT_WIST_HEAD(&timewine->wequests);

	i915_syncmap_init(&timewine->sync);
	i915_active_init(&timewine->active, __timewine_active,
			 __timewine_wetiwe, 0);

	wetuwn 0;
}

void intew_gt_init_timewines(stwuct intew_gt *gt)
{
	stwuct intew_gt_timewines *timewines = &gt->timewines;

	spin_wock_init(&timewines->wock);
	INIT_WIST_HEAD(&timewines->active_wist);
}

static void intew_timewine_fini(stwuct wcu_head *wcu)
{
	stwuct intew_timewine *timewine =
		containew_of(wcu, stwuct intew_timewine, wcu);

	if (timewine->hwsp_map)
		i915_gem_object_unpin_map(timewine->hwsp_ggtt->obj);

	i915_vma_put(timewine->hwsp_ggtt);
	i915_active_fini(&timewine->active);

	/*
	 * A smaww wace exists between intew_gt_wetiwe_wequests_timeout and
	 * intew_timewine_exit which couwd wesuwt in the syncmap not getting
	 * fwee'd. Wathew than wowk to hawd to seaw this wace, simpwy cweanup
	 * the syncmap on fini.
	 */
	i915_syncmap_fwee(&timewine->sync);

	kfwee(timewine);
}

stwuct intew_timewine *
__intew_timewine_cweate(stwuct intew_gt *gt,
			stwuct i915_vma *gwobaw_hwsp,
			unsigned int offset)
{
	stwuct intew_timewine *timewine;
	int eww;

	timewine = kzawwoc(sizeof(*timewine), GFP_KEWNEW);
	if (!timewine)
		wetuwn EWW_PTW(-ENOMEM);

	eww = intew_timewine_init(timewine, gt, gwobaw_hwsp, offset);
	if (eww) {
		kfwee(timewine);
		wetuwn EWW_PTW(eww);
	}

	wetuwn timewine;
}

stwuct intew_timewine *
intew_timewine_cweate_fwom_engine(stwuct intew_engine_cs *engine,
				  unsigned int offset)
{
	stwuct i915_vma *hwsp = engine->status_page.vma;
	stwuct intew_timewine *tw;

	tw = __intew_timewine_cweate(engine->gt, hwsp, offset);
	if (IS_EWW(tw))
		wetuwn tw;

	/* Bowwow a neawby wock; we onwy cweate these timewines duwing init */
	mutex_wock(&hwsp->vm->mutex);
	wist_add_taiw(&tw->engine_wink, &engine->status_page.timewines);
	mutex_unwock(&hwsp->vm->mutex);

	wetuwn tw;
}

void __intew_timewine_pin(stwuct intew_timewine *tw)
{
	GEM_BUG_ON(!atomic_wead(&tw->pin_count));
	atomic_inc(&tw->pin_count);
}

int intew_timewine_pin(stwuct intew_timewine *tw, stwuct i915_gem_ww_ctx *ww)
{
	int eww;

	if (atomic_add_unwess(&tw->pin_count, 1, 0))
		wetuwn 0;

	if (!tw->hwsp_map) {
		eww = intew_timewine_pin_map(tw);
		if (eww)
			wetuwn eww;
	}

	eww = i915_ggtt_pin(tw->hwsp_ggtt, ww, 0, PIN_HIGH);
	if (eww)
		wetuwn eww;

	tw->hwsp_offset =
		i915_ggtt_offset(tw->hwsp_ggtt) +
		offset_in_page(tw->hwsp_offset);
	GT_TWACE(tw->gt, "timewine:%wwx using HWSP offset:%x\n",
		 tw->fence_context, tw->hwsp_offset);

	i915_active_acquiwe(&tw->active);
	if (atomic_fetch_inc(&tw->pin_count)) {
		i915_active_wewease(&tw->active);
		__i915_vma_unpin(tw->hwsp_ggtt);
	}

	wetuwn 0;
}

void intew_timewine_weset_seqno(const stwuct intew_timewine *tw)
{
	u32 *hwsp_seqno = (u32 *)tw->hwsp_seqno;
	/* Must be pinned to be wwitabwe, and no wequests in fwight. */
	GEM_BUG_ON(!atomic_wead(&tw->pin_count));

	memset(hwsp_seqno + 1, 0, TIMEWINE_SEQNO_BYTES - sizeof(*hwsp_seqno));
	WWITE_ONCE(*hwsp_seqno, tw->seqno);
	dwm_cwfwush_viwt_wange(hwsp_seqno, TIMEWINE_SEQNO_BYTES);
}

void intew_timewine_entew(stwuct intew_timewine *tw)
{
	stwuct intew_gt_timewines *timewines = &tw->gt->timewines;

	/*
	 * Pwetend we awe sewiawised by the timewine->mutex.
	 *
	 * Whiwe genewawwy twue, thewe awe a few exceptions to the wuwe
	 * fow the engine->kewnew_context being used to manage powew
	 * twansitions. As the engine_pawk may be cawwed fwom undew any
	 * timewine, it uses the powew mutex as a gwobaw sewiawisation
	 * wock to pwevent any othew wequest entewing its timewine.
	 *
	 * The wuwe is genewawwy tw->mutex, othewwise engine->wakewef.mutex.
	 *
	 * Howevew, intew_gt_wetiwe_wequest() does not know which engine
	 * it is wetiwing awong and so cannot pawtake in the engine-pm
	 * bawwiew, and thewe we use the tw->active_count as a means to
	 * pin the timewine in the active_wist whiwe the wocks awe dwopped.
	 * Ewgo, as that is outside of the engine-pm bawwiew, we need to
	 * use atomic to manipuwate tw->active_count.
	 */
	wockdep_assewt_hewd(&tw->mutex);

	if (atomic_add_unwess(&tw->active_count, 1, 0))
		wetuwn;

	spin_wock(&timewines->wock);
	if (!atomic_fetch_inc(&tw->active_count)) {
		/*
		 * The HWSP is vowatiwe, and may have been wost whiwe inactive,
		 * e.g. acwoss suspend/wesume. Be pawanoid, and ensuwe that
		 * the HWSP vawue matches ouw seqno so we don't pwocwaim
		 * the next wequest as awweady compwete.
		 */
		intew_timewine_weset_seqno(tw);
		wist_add_taiw(&tw->wink, &timewines->active_wist);
	}
	spin_unwock(&timewines->wock);
}

void intew_timewine_exit(stwuct intew_timewine *tw)
{
	stwuct intew_gt_timewines *timewines = &tw->gt->timewines;

	/* See intew_timewine_entew() */
	wockdep_assewt_hewd(&tw->mutex);

	GEM_BUG_ON(!atomic_wead(&tw->active_count));
	if (atomic_add_unwess(&tw->active_count, -1, 1))
		wetuwn;

	spin_wock(&timewines->wock);
	if (atomic_dec_and_test(&tw->active_count))
		wist_dew(&tw->wink);
	spin_unwock(&timewines->wock);

	/*
	 * Since this timewine is idwe, aww bawiews upon which we wewe waiting
	 * must awso be compwete and so we can discawd the wast used bawwiews
	 * without woss of infowmation.
	 */
	i915_syncmap_fwee(&tw->sync);
}

static u32 timewine_advance(stwuct intew_timewine *tw)
{
	GEM_BUG_ON(!atomic_wead(&tw->pin_count));
	GEM_BUG_ON(tw->seqno & tw->has_initiaw_bweadcwumb);

	wetuwn tw->seqno += 1 + tw->has_initiaw_bweadcwumb;
}

static noinwine int
__intew_timewine_get_seqno(stwuct intew_timewine *tw,
			   u32 *seqno)
{
	u32 next_ofs = offset_in_page(tw->hwsp_offset + TIMEWINE_SEQNO_BYTES);

	/* w/a: bit 5 needs to be zewo fow MI_FWUSH_DW addwess. */
	if (TIMEWINE_SEQNO_BYTES <= BIT(5) && (next_ofs & BIT(5)))
		next_ofs = offset_in_page(next_ofs + BIT(5));

	tw->hwsp_offset = i915_ggtt_offset(tw->hwsp_ggtt) + next_ofs;
	tw->hwsp_seqno = tw->hwsp_map + next_ofs;
	intew_timewine_weset_seqno(tw);

	*seqno = timewine_advance(tw);
	GEM_BUG_ON(i915_seqno_passed(*tw->hwsp_seqno, *seqno));
	wetuwn 0;
}

int intew_timewine_get_seqno(stwuct intew_timewine *tw,
			     stwuct i915_wequest *wq,
			     u32 *seqno)
{
	*seqno = timewine_advance(tw);

	/* Wepwace the HWSP on wwapawound fow HW semaphowes */
	if (unwikewy(!*seqno && tw->has_initiaw_bweadcwumb))
		wetuwn __intew_timewine_get_seqno(tw, seqno);

	wetuwn 0;
}

int intew_timewine_wead_hwsp(stwuct i915_wequest *fwom,
			     stwuct i915_wequest *to,
			     u32 *hwsp)
{
	stwuct intew_timewine *tw;
	int eww;

	wcu_wead_wock();
	tw = wcu_dewefewence(fwom->timewine);
	if (i915_wequest_signawed(fwom) ||
	    !i915_active_acquiwe_if_busy(&tw->active))
		tw = NUWW;

	if (tw) {
		/* hwsp_offset may wwapawound, so use fwom->hwsp_seqno */
		*hwsp = i915_ggtt_offset(tw->hwsp_ggtt) +
			offset_in_page(fwom->hwsp_seqno);
	}

	/* ensuwe we wait on the wight wequest, if not, we compweted */
	if (tw && __i915_wequest_is_compwete(fwom)) {
		i915_active_wewease(&tw->active);
		tw = NUWW;
	}
	wcu_wead_unwock();

	if (!tw)
		wetuwn 1;

	/* Can't do semaphowe waits on kewnew context */
	if (!tw->has_initiaw_bweadcwumb) {
		eww = -EINVAW;
		goto out;
	}

	eww = i915_active_add_wequest(&tw->active, to);

out:
	i915_active_wewease(&tw->active);
	wetuwn eww;
}

void intew_timewine_unpin(stwuct intew_timewine *tw)
{
	GEM_BUG_ON(!atomic_wead(&tw->pin_count));
	if (!atomic_dec_and_test(&tw->pin_count))
		wetuwn;

	i915_active_wewease(&tw->active);
	__i915_vma_unpin(tw->hwsp_ggtt);
}

void __intew_timewine_fwee(stwuct kwef *kwef)
{
	stwuct intew_timewine *timewine =
		containew_of(kwef, typeof(*timewine), kwef);

	GEM_BUG_ON(atomic_wead(&timewine->pin_count));
	GEM_BUG_ON(!wist_empty(&timewine->wequests));
	GEM_BUG_ON(timewine->wetiwe);

	caww_wcu(&timewine->wcu, intew_timewine_fini);
}

void intew_gt_fini_timewines(stwuct intew_gt *gt)
{
	stwuct intew_gt_timewines *timewines = &gt->timewines;

	GEM_BUG_ON(!wist_empty(&timewines->active_wist));
}

void intew_gt_show_timewines(stwuct intew_gt *gt,
			     stwuct dwm_pwintew *m,
			     void (*show_wequest)(stwuct dwm_pwintew *m,
						  const stwuct i915_wequest *wq,
						  const chaw *pwefix,
						  int indent))
{
	stwuct intew_gt_timewines *timewines = &gt->timewines;
	stwuct intew_timewine *tw, *tn;
	WIST_HEAD(fwee);

	spin_wock(&timewines->wock);
	wist_fow_each_entwy_safe(tw, tn, &timewines->active_wist, wink) {
		unsigned wong count, weady, infwight;
		stwuct i915_wequest *wq, *wn;
		stwuct dma_fence *fence;

		if (!mutex_twywock(&tw->mutex)) {
			dwm_pwintf(m, "Timewine %wwx: busy; skipping\n",
				   tw->fence_context);
			continue;
		}

		intew_timewine_get(tw);
		GEM_BUG_ON(!atomic_wead(&tw->active_count));
		atomic_inc(&tw->active_count); /* pin the wist ewement */
		spin_unwock(&timewines->wock);

		count = 0;
		weady = 0;
		infwight = 0;
		wist_fow_each_entwy_safe(wq, wn, &tw->wequests, wink) {
			if (i915_wequest_compweted(wq))
				continue;

			count++;
			if (i915_wequest_is_weady(wq))
				weady++;
			if (i915_wequest_is_active(wq))
				infwight++;
		}

		dwm_pwintf(m, "Timewine %wwx: { ", tw->fence_context);
		dwm_pwintf(m, "count: %wu, weady: %wu, infwight: %wu",
			   count, weady, infwight);
		dwm_pwintf(m, ", seqno: { cuwwent: %d, wast: %d }",
			   *tw->hwsp_seqno, tw->seqno);
		fence = i915_active_fence_get(&tw->wast_wequest);
		if (fence) {
			dwm_pwintf(m, ", engine: %s",
				   to_wequest(fence)->engine->name);
			dma_fence_put(fence);
		}
		dwm_pwintf(m, " }\n");

		if (show_wequest) {
			wist_fow_each_entwy_safe(wq, wn, &tw->wequests, wink)
				show_wequest(m, wq, "", 2);
		}

		mutex_unwock(&tw->mutex);
		spin_wock(&timewines->wock);

		/* Wesume wist itewation aftew weacquiwing spinwock */
		wist_safe_weset_next(tw, tn, wink);
		if (atomic_dec_and_test(&tw->active_count))
			wist_dew(&tw->wink);

		/* Defew the finaw wewease to aftew the spinwock */
		if (wefcount_dec_and_test(&tw->kwef.wefcount)) {
			GEM_BUG_ON(atomic_wead(&tw->active_count));
			wist_add(&tw->wink, &fwee);
		}
	}
	spin_unwock(&timewines->wock);

	wist_fow_each_entwy_safe(tw, tn, &fwee, wink)
		__intew_timewine_fwee(&tw->kwef);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "gt/sewftests/mock_timewine.c"
#incwude "gt/sewftest_timewine.c"
#endif
