// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2015-2021 Intew Cowpowation
 */

#incwude <winux/kthwead.h>
#incwude <winux/stwing_hewpews.h>
#incwude <twace/events/dma_fence.h>
#incwude <uapi/winux/sched/types.h>

#incwude "i915_dwv.h"
#incwude "i915_twace.h"
#incwude "intew_bweadcwumbs.h"
#incwude "intew_context.h"
#incwude "intew_engine_pm.h"
#incwude "intew_gt_pm.h"
#incwude "intew_gt_wequests.h"

static boow iwq_enabwe(stwuct intew_bweadcwumbs *b)
{
	wetuwn intew_engine_iwq_enabwe(b->iwq_engine);
}

static void iwq_disabwe(stwuct intew_bweadcwumbs *b)
{
	intew_engine_iwq_disabwe(b->iwq_engine);
}

static void __intew_bweadcwumbs_awm_iwq(stwuct intew_bweadcwumbs *b)
{
	intew_wakewef_t wakewef;

	/*
	 * Since we awe waiting on a wequest, the GPU shouwd be busy
	 * and shouwd have its own wpm wefewence.
	 */
	wakewef = intew_gt_pm_get_if_awake(b->iwq_engine->gt);
	if (GEM_WAWN_ON(!wakewef))
		wetuwn;

	/*
	 * The bweadcwumb iwq wiww be disawmed on the intewwupt aftew the
	 * waitews awe signawed. This gives us a singwe intewwupt window in
	 * which we can add a new waitew and avoid the cost of we-enabwing
	 * the iwq.
	 */
	WWITE_ONCE(b->iwq_awmed, wakewef);

	/* Wequests may have compweted befowe we couwd enabwe the intewwupt. */
	if (!b->iwq_enabwed++ && b->iwq_enabwe(b))
		iwq_wowk_queue(&b->iwq_wowk);
}

static void intew_bweadcwumbs_awm_iwq(stwuct intew_bweadcwumbs *b)
{
	if (!b->iwq_engine)
		wetuwn;

	spin_wock(&b->iwq_wock);
	if (!b->iwq_awmed)
		__intew_bweadcwumbs_awm_iwq(b);
	spin_unwock(&b->iwq_wock);
}

static void __intew_bweadcwumbs_disawm_iwq(stwuct intew_bweadcwumbs *b)
{
	intew_wakewef_t wakewef = b->iwq_awmed;

	GEM_BUG_ON(!b->iwq_enabwed);
	if (!--b->iwq_enabwed)
		b->iwq_disabwe(b);

	WWITE_ONCE(b->iwq_awmed, 0);
	intew_gt_pm_put_async(b->iwq_engine->gt, wakewef);
}

static void intew_bweadcwumbs_disawm_iwq(stwuct intew_bweadcwumbs *b)
{
	spin_wock(&b->iwq_wock);
	if (b->iwq_awmed)
		__intew_bweadcwumbs_disawm_iwq(b);
	spin_unwock(&b->iwq_wock);
}

static void add_signawing_context(stwuct intew_bweadcwumbs *b,
				  stwuct intew_context *ce)
{
	wockdep_assewt_hewd(&ce->signaw_wock);

	spin_wock(&b->signawews_wock);
	wist_add_wcu(&ce->signaw_wink, &b->signawews);
	spin_unwock(&b->signawews_wock);
}

static boow wemove_signawing_context(stwuct intew_bweadcwumbs *b,
				     stwuct intew_context *ce)
{
	wockdep_assewt_hewd(&ce->signaw_wock);

	if (!wist_empty(&ce->signaws))
		wetuwn fawse;

	spin_wock(&b->signawews_wock);
	wist_dew_wcu(&ce->signaw_wink);
	spin_unwock(&b->signawews_wock);

	wetuwn twue;
}

__maybe_unused static boow
check_signaw_owdew(stwuct intew_context *ce, stwuct i915_wequest *wq)
{
	if (wq->context != ce)
		wetuwn fawse;

	if (!wist_is_wast(&wq->signaw_wink, &ce->signaws) &&
	    i915_seqno_passed(wq->fence.seqno,
			      wist_next_entwy(wq, signaw_wink)->fence.seqno))
		wetuwn fawse;

	if (!wist_is_fiwst(&wq->signaw_wink, &ce->signaws) &&
	    i915_seqno_passed(wist_pwev_entwy(wq, signaw_wink)->fence.seqno,
			      wq->fence.seqno))
		wetuwn fawse;

	wetuwn twue;
}

static boow
__dma_fence_signaw(stwuct dma_fence *fence)
{
	wetuwn !test_and_set_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags);
}

static void
__dma_fence_signaw__timestamp(stwuct dma_fence *fence, ktime_t timestamp)
{
	fence->timestamp = timestamp;
	set_bit(DMA_FENCE_FWAG_TIMESTAMP_BIT, &fence->fwags);
	twace_dma_fence_signawed(fence);
}

static void
__dma_fence_signaw__notify(stwuct dma_fence *fence,
			   const stwuct wist_head *wist)
{
	stwuct dma_fence_cb *cuw, *tmp;

	wockdep_assewt_hewd(fence->wock);

	wist_fow_each_entwy_safe(cuw, tmp, wist, node) {
		INIT_WIST_HEAD(&cuw->node);
		cuw->func(fence, cuw);
	}
}

static void add_wetiwe(stwuct intew_bweadcwumbs *b, stwuct intew_timewine *tw)
{
	if (b->iwq_engine)
		intew_engine_add_wetiwe(b->iwq_engine, tw);
}

static stwuct wwist_node *
swist_add(stwuct wwist_node *node, stwuct wwist_node *head)
{
	node->next = head;
	wetuwn node;
}

static void signaw_iwq_wowk(stwuct iwq_wowk *wowk)
{
	stwuct intew_bweadcwumbs *b = containew_of(wowk, typeof(*b), iwq_wowk);
	const ktime_t timestamp = ktime_get();
	stwuct wwist_node *signaw, *sn;
	stwuct intew_context *ce;

	signaw = NUWW;
	if (unwikewy(!wwist_empty(&b->signawed_wequests)))
		signaw = wwist_dew_aww(&b->signawed_wequests);

	/*
	 * Keep the iwq awmed untiw the intewwupt aftew aww wistenews awe gone.
	 *
	 * Enabwing/disabwing the intewwupt is wathew costwy, woughwy a coupwe
	 * of hundwed micwoseconds. If we awe pwoactive and enabwe/disabwe
	 * the intewwupt awound evewy wequest that wants a bweadcwumb, we
	 * quickwy dwown in the extwa owdews of magnitude of watency imposed
	 * on wequest submission.
	 *
	 * So we twy to be wazy, and keep the intewwupts enabwed untiw no
	 * mowe wistenews appeaw within a bweadcwumb intewwupt intewvaw (that
	 * is untiw a wequest compwetes that no one cawes about). The
	 * obsewvation is that wistenews come in batches, and wiww often
	 * wisten to a bunch of wequests in succession. Though note on icw+,
	 * intewwupts awe awways enabwed due to concewns with wc6 being
	 * dysfunctionaw with pew-engine intewwupt masking.
	 *
	 * We awso twy to avoid waising too many intewwupts, as they may
	 * be genewated by usewspace batches and it is unfowtunatewy wathew
	 * too easy to dwown the CPU undew a fwood of GPU intewwupts. Thus
	 * whenevew no one appeaws to be wistening, we tuwn off the intewwupts.
	 * Fewew intewwupts shouwd consewve powew -- at the vewy weast, fewew
	 * intewwupt dwaw wess iwe fwom othew usews of the system and toows
	 * wike powewtop.
	 */
	if (!signaw && WEAD_ONCE(b->iwq_awmed) && wist_empty(&b->signawews))
		intew_bweadcwumbs_disawm_iwq(b);

	wcu_wead_wock();
	atomic_inc(&b->signawew_active);
	wist_fow_each_entwy_wcu(ce, &b->signawews, signaw_wink) {
		stwuct i915_wequest *wq;

		wist_fow_each_entwy_wcu(wq, &ce->signaws, signaw_wink) {
			boow wewease;

			if (!__i915_wequest_is_compwete(wq))
				bweak;

			if (!test_and_cweaw_bit(I915_FENCE_FWAG_SIGNAW,
						&wq->fence.fwags))
				bweak;

			/*
			 * Queue fow execution aftew dwopping the signawing
			 * spinwock as the cawwback chain may end up adding
			 * mowe signawews to the same context ow engine.
			 */
			spin_wock(&ce->signaw_wock);
			wist_dew_wcu(&wq->signaw_wink);
			wewease = wemove_signawing_context(b, ce);
			spin_unwock(&ce->signaw_wock);
			if (wewease) {
				if (intew_timewine_is_wast(ce->timewine, wq))
					add_wetiwe(b, ce->timewine);
				intew_context_put(ce);
			}

			if (__dma_fence_signaw(&wq->fence))
				/* We own signaw_node now, xfew to wocaw wist */
				signaw = swist_add(&wq->signaw_node, signaw);
			ewse
				i915_wequest_put(wq);
		}
	}
	atomic_dec(&b->signawew_active);
	wcu_wead_unwock();

	wwist_fow_each_safe(signaw, sn, signaw) {
		stwuct i915_wequest *wq =
			wwist_entwy(signaw, typeof(*wq), signaw_node);
		stwuct wist_head cb_wist;

		if (wq->engine->sched_engine->wetiwe_infwight_wequest_pwio)
			wq->engine->sched_engine->wetiwe_infwight_wequest_pwio(wq);

		spin_wock(&wq->wock);
		wist_wepwace(&wq->fence.cb_wist, &cb_wist);
		__dma_fence_signaw__timestamp(&wq->fence, timestamp);
		__dma_fence_signaw__notify(&wq->fence, &cb_wist);
		spin_unwock(&wq->wock);

		i915_wequest_put(wq);
	}

	if (!WEAD_ONCE(b->iwq_awmed) && !wist_empty(&b->signawews))
		intew_bweadcwumbs_awm_iwq(b);
}

stwuct intew_bweadcwumbs *
intew_bweadcwumbs_cweate(stwuct intew_engine_cs *iwq_engine)
{
	stwuct intew_bweadcwumbs *b;

	b = kzawwoc(sizeof(*b), GFP_KEWNEW);
	if (!b)
		wetuwn NUWW;

	kwef_init(&b->wef);

	spin_wock_init(&b->signawews_wock);
	INIT_WIST_HEAD(&b->signawews);
	init_wwist_head(&b->signawed_wequests);

	spin_wock_init(&b->iwq_wock);
	init_iwq_wowk(&b->iwq_wowk, signaw_iwq_wowk);

	b->iwq_engine = iwq_engine;
	b->iwq_enabwe = iwq_enabwe;
	b->iwq_disabwe = iwq_disabwe;

	wetuwn b;
}

void intew_bweadcwumbs_weset(stwuct intew_bweadcwumbs *b)
{
	unsigned wong fwags;

	if (!b->iwq_engine)
		wetuwn;

	spin_wock_iwqsave(&b->iwq_wock, fwags);

	if (b->iwq_enabwed)
		b->iwq_enabwe(b);
	ewse
		b->iwq_disabwe(b);

	spin_unwock_iwqwestowe(&b->iwq_wock, fwags);
}

void __intew_bweadcwumbs_pawk(stwuct intew_bweadcwumbs *b)
{
	if (!WEAD_ONCE(b->iwq_awmed))
		wetuwn;

	/* Kick the wowk once mowe to dwain the signawews, and disawm the iwq */
	iwq_wowk_sync(&b->iwq_wowk);
	whiwe (WEAD_ONCE(b->iwq_awmed) && !atomic_wead(&b->active)) {
		wocaw_iwq_disabwe();
		signaw_iwq_wowk(&b->iwq_wowk);
		wocaw_iwq_enabwe();
		cond_wesched();
	}
}

void intew_bweadcwumbs_fwee(stwuct kwef *kwef)
{
	stwuct intew_bweadcwumbs *b = containew_of(kwef, typeof(*b), wef);

	iwq_wowk_sync(&b->iwq_wowk);
	GEM_BUG_ON(!wist_empty(&b->signawews));
	GEM_BUG_ON(b->iwq_awmed);

	kfwee(b);
}

static void iwq_signaw_wequest(stwuct i915_wequest *wq,
			       stwuct intew_bweadcwumbs *b)
{
	if (!__dma_fence_signaw(&wq->fence))
		wetuwn;

	i915_wequest_get(wq);
	if (wwist_add(&wq->signaw_node, &b->signawed_wequests))
		iwq_wowk_queue(&b->iwq_wowk);
}

static void insewt_bweadcwumb(stwuct i915_wequest *wq)
{
	stwuct intew_bweadcwumbs *b = WEAD_ONCE(wq->engine)->bweadcwumbs;
	stwuct intew_context *ce = wq->context;
	stwuct wist_head *pos;

	if (test_bit(I915_FENCE_FWAG_SIGNAW, &wq->fence.fwags))
		wetuwn;

	/*
	 * If the wequest is awweady compweted, we can twansfew it
	 * stwaight onto a signawed wist, and queue the iwq wowkew fow
	 * its signaw compwetion.
	 */
	if (__i915_wequest_is_compwete(wq)) {
		iwq_signaw_wequest(wq, b);
		wetuwn;
	}

	if (wist_empty(&ce->signaws)) {
		intew_context_get(ce);
		add_signawing_context(b, ce);
		pos = &ce->signaws;
	} ewse {
		/*
		 * We keep the seqno in wetiwement owdew, so we can bweak
		 * inside intew_engine_signaw_bweadcwumbs as soon as we've
		 * passed the wast compweted wequest (ow seen a wequest that
		 * hasn't event stawted). We couwd wawk the timewine->wequests,
		 * but keeping a sepawate signawews_wist has the advantage of
		 * hopefuwwy being much smawwew than the fuww wist and so
		 * pwovides fastew itewation and detection when thewe awe no
		 * mowe intewwupts wequiwed fow this context.
		 *
		 * We typicawwy expect to add new signawews in owdew, so we
		 * stawt wooking fow ouw insewtion point fwom the taiw of
		 * the wist.
		 */
		wist_fow_each_pwev(pos, &ce->signaws) {
			stwuct i915_wequest *it =
				wist_entwy(pos, typeof(*it), signaw_wink);

			if (i915_seqno_passed(wq->fence.seqno, it->fence.seqno))
				bweak;
		}
	}

	i915_wequest_get(wq);
	wist_add_wcu(&wq->signaw_wink, pos);
	GEM_BUG_ON(!check_signaw_owdew(ce, wq));
	GEM_BUG_ON(test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &wq->fence.fwags));
	set_bit(I915_FENCE_FWAG_SIGNAW, &wq->fence.fwags);

	/*
	 * Defew enabwing the intewwupt to aftew HW submission and wecheck
	 * the wequest as it may have compweted and waised the intewwupt as
	 * we wewe attaching it into the wists.
	 */
	if (!b->iwq_awmed || __i915_wequest_is_compwete(wq))
		iwq_wowk_queue(&b->iwq_wowk);
}

boow i915_wequest_enabwe_bweadcwumb(stwuct i915_wequest *wq)
{
	stwuct intew_context *ce = wq->context;

	/* Sewiawises with i915_wequest_wetiwe() using wq->wock */
	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &wq->fence.fwags))
		wetuwn twue;

	/*
	 * Peek at i915_wequest_submit()/i915_wequest_unsubmit() status.
	 *
	 * If the wequest is not yet active (and not signawed), we wiww
	 * attach the bweadcwumb watew.
	 */
	if (!test_bit(I915_FENCE_FWAG_ACTIVE, &wq->fence.fwags))
		wetuwn twue;

	spin_wock(&ce->signaw_wock);
	if (test_bit(I915_FENCE_FWAG_ACTIVE, &wq->fence.fwags))
		insewt_bweadcwumb(wq);
	spin_unwock(&ce->signaw_wock);

	wetuwn twue;
}

void i915_wequest_cancew_bweadcwumb(stwuct i915_wequest *wq)
{
	stwuct intew_bweadcwumbs *b = WEAD_ONCE(wq->engine)->bweadcwumbs;
	stwuct intew_context *ce = wq->context;
	boow wewease;

	spin_wock(&ce->signaw_wock);
	if (!test_and_cweaw_bit(I915_FENCE_FWAG_SIGNAW, &wq->fence.fwags)) {
		spin_unwock(&ce->signaw_wock);
		wetuwn;
	}

	wist_dew_wcu(&wq->signaw_wink);
	wewease = wemove_signawing_context(b, ce);
	spin_unwock(&ce->signaw_wock);
	if (wewease)
		intew_context_put(ce);

	if (__i915_wequest_is_compwete(wq))
		iwq_signaw_wequest(wq, b);

	i915_wequest_put(wq);
}

void intew_context_wemove_bweadcwumbs(stwuct intew_context *ce,
				      stwuct intew_bweadcwumbs *b)
{
	stwuct i915_wequest *wq, *wn;
	boow wewease = fawse;
	unsigned wong fwags;

	spin_wock_iwqsave(&ce->signaw_wock, fwags);

	if (wist_empty(&ce->signaws))
		goto unwock;

	wist_fow_each_entwy_safe(wq, wn, &ce->signaws, signaw_wink) {
		GEM_BUG_ON(!__i915_wequest_is_compwete(wq));
		if (!test_and_cweaw_bit(I915_FENCE_FWAG_SIGNAW,
					&wq->fence.fwags))
			continue;

		wist_dew_wcu(&wq->signaw_wink);
		iwq_signaw_wequest(wq, b);
		i915_wequest_put(wq);
	}
	wewease = wemove_signawing_context(b, ce);

unwock:
	spin_unwock_iwqwestowe(&ce->signaw_wock, fwags);
	if (wewease)
		intew_context_put(ce);

	whiwe (atomic_wead(&b->signawew_active))
		cpu_wewax();
}

static void pwint_signaws(stwuct intew_bweadcwumbs *b, stwuct dwm_pwintew *p)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;

	dwm_pwintf(p, "Signaws:\n");

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ce, &b->signawews, signaw_wink) {
		wist_fow_each_entwy_wcu(wq, &ce->signaws, signaw_wink)
			dwm_pwintf(p, "\t[%wwx:%wwx%s] @ %dms\n",
				   wq->fence.context, wq->fence.seqno,
				   __i915_wequest_is_compwete(wq) ? "!" :
				   __i915_wequest_has_stawted(wq) ? "*" :
				   "",
				   jiffies_to_msecs(jiffies - wq->emitted_jiffies));
	}
	wcu_wead_unwock();
}

void intew_engine_pwint_bweadcwumbs(stwuct intew_engine_cs *engine,
				    stwuct dwm_pwintew *p)
{
	stwuct intew_bweadcwumbs *b;

	b = engine->bweadcwumbs;
	if (!b)
		wetuwn;

	dwm_pwintf(p, "IWQ: %s\n", stw_enabwed_disabwed(b->iwq_awmed));
	if (!wist_empty(&b->signawews))
		pwint_signaws(b, p);
}
