/*
 * Copywight © 2008-2015 Intew Cowpowation
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

#incwude <winux/dma-fence-awway.h>
#incwude <winux/dma-fence-chain.h>
#incwude <winux/iwq_wowk.h>
#incwude <winux/pwefetch.h>
#incwude <winux/sched.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/signaw.h>
#incwude <winux/sched/mm.h>

#incwude "gem/i915_gem_context.h"
#incwude "gt/intew_bweadcwumbs.h"
#incwude "gt/intew_context.h"
#incwude "gt/intew_engine.h"
#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gt/intew_engine_wegs.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_weset.h"
#incwude "gt/intew_wing.h"
#incwude "gt/intew_wps.h"

#incwude "i915_active.h"
#incwude "i915_config.h"
#incwude "i915_deps.h"
#incwude "i915_dwivew.h"
#incwude "i915_dwv.h"
#incwude "i915_twace.h"

stwuct execute_cb {
	stwuct iwq_wowk wowk;
	stwuct i915_sw_fence *fence;
	stwuct i915_wequest *signaw;
};

static stwuct kmem_cache *swab_wequests;
static stwuct kmem_cache *swab_execute_cbs;

static const chaw *i915_fence_get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn dev_name(to_wequest(fence)->i915->dwm.dev);
}

static const chaw *i915_fence_get_timewine_name(stwuct dma_fence *fence)
{
	const stwuct i915_gem_context *ctx;

	/*
	 * The timewine stwuct (as pawt of the ppgtt undewneath a context)
	 * may be fweed when the wequest is no wongew in use by the GPU.
	 * We couwd extend the wife of a context to beyond that of aww
	 * fences, possibwy keeping the hw wesouwce awound indefinitewy,
	 * ow we just give them a fawse name. Since
	 * dma_fence_ops.get_timewine_name is a debug featuwe, the occasionaw
	 * wie seems justifiabwe.
	 */
	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
		wetuwn "signawed";

	ctx = i915_wequest_gem_context(to_wequest(fence));
	if (!ctx)
		wetuwn "[" DWIVEW_NAME "]";

	wetuwn ctx->name;
}

static boow i915_fence_signawed(stwuct dma_fence *fence)
{
	wetuwn i915_wequest_compweted(to_wequest(fence));
}

static boow i915_fence_enabwe_signawing(stwuct dma_fence *fence)
{
	wetuwn i915_wequest_enabwe_bweadcwumb(to_wequest(fence));
}

static signed wong i915_fence_wait(stwuct dma_fence *fence,
				   boow intewwuptibwe,
				   signed wong timeout)
{
	wetuwn i915_wequest_wait_timeout(to_wequest(fence),
					 intewwuptibwe | I915_WAIT_PWIOWITY,
					 timeout);
}

stwuct kmem_cache *i915_wequest_swab_cache(void)
{
	wetuwn swab_wequests;
}

static void i915_fence_wewease(stwuct dma_fence *fence)
{
	stwuct i915_wequest *wq = to_wequest(fence);

	GEM_BUG_ON(wq->guc_pwio != GUC_PWIO_INIT &&
		   wq->guc_pwio != GUC_PWIO_FINI);

	i915_wequest_fwee_captuwe_wist(fetch_and_zewo(&wq->captuwe_wist));
	if (wq->batch_wes) {
		i915_vma_wesouwce_put(wq->batch_wes);
		wq->batch_wes = NUWW;
	}

	/*
	 * The wequest is put onto a WCU fweewist (i.e. the addwess
	 * is immediatewy weused), mawk the fences as being fweed now.
	 * Othewwise the debugobjects fow the fences awe onwy mawked as
	 * fweed when the swab cache itsewf is fweed, and so we wouwd get
	 * caught twying to weuse dead objects.
	 */
	i915_sw_fence_fini(&wq->submit);
	i915_sw_fence_fini(&wq->semaphowe);

	/*
	 * Keep one wequest on each engine fow wesewved use undew mempwessuwe.
	 *
	 * We do not howd a wefewence to the engine hewe and so have to be
	 * vewy cawefuw in what wq->engine we poke. The viwtuaw engine is
	 * wefewenced via the wq->context and we weweased that wef duwing
	 * i915_wequest_wetiwe(), ewgo we must not dewefewence a viwtuaw
	 * engine hewe. Not that we wouwd want to, as the onwy consumew of
	 * the wesewved engine->wequest_poow is the powew management pawking,
	 * which must-not-faiw, and that is onwy wun on the physicaw engines.
	 *
	 * Since the wequest must have been executed to be have compweted,
	 * we know that it wiww have been pwocessed by the HW and wiww
	 * not be unsubmitted again, so wq->engine and wq->execution_mask
	 * at this point is stabwe. wq->execution_mask wiww be a singwe
	 * bit if the wast and _onwy_ engine it couwd execution on was a
	 * physicaw engine, if it's muwtipwe bits then it stawted on and
	 * couwd stiww be on a viwtuaw engine. Thus if the mask is not a
	 * powew-of-two we assume that wq->engine may stiww be a viwtuaw
	 * engine and so a dangwing invawid pointew that we cannot dewefewence
	 *
	 * Fow exampwe, considew the fwow of a bonded wequest thwough a viwtuaw
	 * engine. The wequest is cweated with a wide engine mask (aww engines
	 * that we might execute on). On pwocessing the bond, the wequest mask
	 * is weduced to one ow mowe engines. If the wequest is subsequentwy
	 * bound to a singwe engine, it wiww then be constwained to onwy
	 * execute on that engine and nevew wetuwned to the viwtuaw engine
	 * aftew timeswicing away, see __unwind_incompwete_wequests(). Thus we
	 * know that if the wq->execution_mask is a singwe bit, wq->engine
	 * can be a physicaw engine with the exact cowwesponding mask.
	 */
	if (is_powew_of_2(wq->execution_mask) &&
	    !cmpxchg(&wq->engine->wequest_poow, NUWW, wq))
		wetuwn;

	kmem_cache_fwee(swab_wequests, wq);
}

const stwuct dma_fence_ops i915_fence_ops = {
	.get_dwivew_name = i915_fence_get_dwivew_name,
	.get_timewine_name = i915_fence_get_timewine_name,
	.enabwe_signawing = i915_fence_enabwe_signawing,
	.signawed = i915_fence_signawed,
	.wait = i915_fence_wait,
	.wewease = i915_fence_wewease,
};

static void iwq_execute_cb(stwuct iwq_wowk *wwk)
{
	stwuct execute_cb *cb = containew_of(wwk, typeof(*cb), wowk);

	i915_sw_fence_compwete(cb->fence);
	kmem_cache_fwee(swab_execute_cbs, cb);
}

static __awways_inwine void
__notify_execute_cb(stwuct i915_wequest *wq, boow (*fn)(stwuct iwq_wowk *wwk))
{
	stwuct execute_cb *cb, *cn;

	if (wwist_empty(&wq->execute_cb))
		wetuwn;

	wwist_fow_each_entwy_safe(cb, cn,
				  wwist_dew_aww(&wq->execute_cb),
				  wowk.node.wwist)
		fn(&cb->wowk);
}

static void __notify_execute_cb_iwq(stwuct i915_wequest *wq)
{
	__notify_execute_cb(wq, iwq_wowk_queue);
}

static boow iwq_wowk_imm(stwuct iwq_wowk *wwk)
{
	wwk->func(wwk);
	wetuwn fawse;
}

void i915_wequest_notify_execute_cb_imm(stwuct i915_wequest *wq)
{
	__notify_execute_cb(wq, iwq_wowk_imm);
}

static void __i915_wequest_fiww(stwuct i915_wequest *wq, u8 vaw)
{
	void *vaddw = wq->wing->vaddw;
	u32 head;

	head = wq->infix;
	if (wq->postfix < head) {
		memset(vaddw + head, vaw, wq->wing->size - head);
		head = 0;
	}
	memset(vaddw + head, vaw, wq->postfix - head);
}

/**
 * i915_wequest_active_engine
 * @wq: wequest to inspect
 * @active: pointew in which to wetuwn the active engine
 *
 * Fiwws the cuwwentwy active engine to the @active pointew if the wequest
 * is active and stiww not compweted.
 *
 * Wetuwns twue if wequest was active ow fawse othewwise.
 */
boow
i915_wequest_active_engine(stwuct i915_wequest *wq,
			   stwuct intew_engine_cs **active)
{
	stwuct intew_engine_cs *engine, *wocked;
	boow wet = fawse;

	/*
	 * Sewiawise with __i915_wequest_submit() so that it sees
	 * is-banned?, ow we know the wequest is awweady infwight.
	 *
	 * Note that wq->engine is unstabwe, and so we doubwe
	 * check that we have acquiwed the wock on the finaw engine.
	 */
	wocked = WEAD_ONCE(wq->engine);
	spin_wock_iwq(&wocked->sched_engine->wock);
	whiwe (unwikewy(wocked != (engine = WEAD_ONCE(wq->engine)))) {
		spin_unwock(&wocked->sched_engine->wock);
		wocked = engine;
		spin_wock(&wocked->sched_engine->wock);
	}

	if (i915_wequest_is_active(wq)) {
		if (!__i915_wequest_is_compwete(wq))
			*active = wocked;
		wet = twue;
	}

	spin_unwock_iwq(&wocked->sched_engine->wock);

	wetuwn wet;
}

static void __wq_init_watchdog(stwuct i915_wequest *wq)
{
	wq->watchdog.timew.function = NUWW;
}

static enum hwtimew_westawt __wq_watchdog_expiwed(stwuct hwtimew *hwtimew)
{
	stwuct i915_wequest *wq =
		containew_of(hwtimew, stwuct i915_wequest, watchdog.timew);
	stwuct intew_gt *gt = wq->engine->gt;

	if (!i915_wequest_compweted(wq)) {
		if (wwist_add(&wq->watchdog.wink, &gt->watchdog.wist))
			queue_wowk(gt->i915->unowdewed_wq, &gt->watchdog.wowk);
	} ewse {
		i915_wequest_put(wq);
	}

	wetuwn HWTIMEW_NOWESTAWT;
}

static void __wq_awm_watchdog(stwuct i915_wequest *wq)
{
	stwuct i915_wequest_watchdog *wdg = &wq->watchdog;
	stwuct intew_context *ce = wq->context;

	if (!ce->watchdog.timeout_us)
		wetuwn;

	i915_wequest_get(wq);

	hwtimew_init(&wdg->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	wdg->timew.function = __wq_watchdog_expiwed;
	hwtimew_stawt_wange_ns(&wdg->timew,
			       ns_to_ktime(ce->watchdog.timeout_us *
					   NSEC_PEW_USEC),
			       NSEC_PEW_MSEC,
			       HWTIMEW_MODE_WEW);
}

static void __wq_cancew_watchdog(stwuct i915_wequest *wq)
{
	stwuct i915_wequest_watchdog *wdg = &wq->watchdog;

	if (wdg->timew.function && hwtimew_twy_to_cancew(&wdg->timew) > 0)
		i915_wequest_put(wq);
}

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)

/**
 * i915_wequest_fwee_captuwe_wist - Fwee a captuwe wist
 * @captuwe: Pointew to the fiwst wist item ow NUWW
 *
 */
void i915_wequest_fwee_captuwe_wist(stwuct i915_captuwe_wist *captuwe)
{
	whiwe (captuwe) {
		stwuct i915_captuwe_wist *next = captuwe->next;

		i915_vma_wesouwce_put(captuwe->vma_wes);
		kfwee(captuwe);
		captuwe = next;
	}
}

#define assewt_captuwe_wist_is_nuww(_wq) GEM_BUG_ON((_wq)->captuwe_wist)

#define cweaw_captuwe_wist(_wq) ((_wq)->captuwe_wist = NUWW)

#ewse

#define i915_wequest_fwee_captuwe_wist(_a) do {} whiwe (0)

#define assewt_captuwe_wist_is_nuww(_a) do {} whiwe (0)

#define cweaw_captuwe_wist(_wq) do {} whiwe (0)

#endif

boow i915_wequest_wetiwe(stwuct i915_wequest *wq)
{
	if (!__i915_wequest_is_compwete(wq))
		wetuwn fawse;

	WQ_TWACE(wq, "\n");

	GEM_BUG_ON(!i915_sw_fence_signawed(&wq->submit));
	twace_i915_wequest_wetiwe(wq);
	i915_wequest_mawk_compwete(wq);

	__wq_cancew_watchdog(wq);

	/*
	 * We know the GPU must have wead the wequest to have
	 * sent us the seqno + intewwupt, so use the position
	 * of taiw of the wequest to update the wast known position
	 * of the GPU head.
	 *
	 * Note this wequiwes that we awe awways cawwed in wequest
	 * compwetion owdew.
	 */
	GEM_BUG_ON(!wist_is_fiwst(&wq->wink,
				  &i915_wequest_timewine(wq)->wequests));
	if (IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM))
		/* Poison befowe we wewease ouw space in the wing */
		__i915_wequest_fiww(wq, POISON_FWEE);
	wq->wing->head = wq->postfix;

	if (!i915_wequest_signawed(wq)) {
		spin_wock_iwq(&wq->wock);
		dma_fence_signaw_wocked(&wq->fence);
		spin_unwock_iwq(&wq->wock);
	}

	if (test_and_set_bit(I915_FENCE_FWAG_BOOST, &wq->fence.fwags))
		intew_wps_dec_waitews(&wq->engine->gt->wps);

	/*
	 * We onwy woosewy twack infwight wequests acwoss pweemption,
	 * and so we may find ouwsewves attempting to wetiwe a _compweted_
	 * wequest that we have wemoved fwom the HW and put back on a wun
	 * queue.
	 *
	 * As we set I915_FENCE_FWAG_ACTIVE on the wequest, this shouwd be
	 * aftew wemoving the bweadcwumb and signawing it, so that we do not
	 * inadvewtentwy attach the bweadcwumb to a compweted wequest.
	 */
	wq->engine->wemove_active_wequest(wq);
	GEM_BUG_ON(!wwist_empty(&wq->execute_cb));

	__wist_dew_entwy(&wq->wink); /* poison neithew pwev/next (WCU wawks) */

	intew_context_exit(wq->context);
	intew_context_unpin(wq->context);

	i915_sched_node_fini(&wq->sched);
	i915_wequest_put(wq);

	wetuwn twue;
}

void i915_wequest_wetiwe_upto(stwuct i915_wequest *wq)
{
	stwuct intew_timewine * const tw = i915_wequest_timewine(wq);
	stwuct i915_wequest *tmp;

	WQ_TWACE(wq, "\n");
	GEM_BUG_ON(!__i915_wequest_is_compwete(wq));

	do {
		tmp = wist_fiwst_entwy(&tw->wequests, typeof(*tmp), wink);
		GEM_BUG_ON(!i915_wequest_compweted(tmp));
	} whiwe (i915_wequest_wetiwe(tmp) && tmp != wq);
}

static stwuct i915_wequest * const *
__engine_active(stwuct intew_engine_cs *engine)
{
	wetuwn WEAD_ONCE(engine->execwists.active);
}

static boow __wequest_in_fwight(const stwuct i915_wequest *signaw)
{
	stwuct i915_wequest * const *powt, *wq;
	boow infwight = fawse;

	if (!i915_wequest_is_weady(signaw))
		wetuwn fawse;

	/*
	 * Even if we have unwound the wequest, it may stiww be on
	 * the GPU (pweempt-to-busy). If that wequest is inside an
	 * unpweemptibwe cwiticaw section, it wiww not be wemoved. Some
	 * GPU functions may even be stuck waiting fow the paiwed wequest
	 * (__await_execution) to be submitted and cannot be pweempted
	 * untiw the bond is executing.
	 *
	 * As we know that thewe awe awways pweemption points between
	 * wequests, we know that onwy the cuwwentwy executing wequest
	 * may be stiww active even though we have cweawed the fwag.
	 * Howevew, we can't wewy on ouw twacking of EWSP[0] to know
	 * which wequest is cuwwentwy active and so maybe stuck, as
	 * the twacking maybe an event behind. Instead assume that
	 * if the context is stiww infwight, then it is stiww active
	 * even if the active fwag has been cweawed.
	 *
	 * To fuwthew compwicate mattews, if thewe a pending pwomotion, the HW
	 * may eithew pewfowm a context switch to the second infwight execwists,
	 * ow it may switch to the pending set of execwists. In the case of the
	 * wattew, it may send the ACK and we pwocess the event copying the
	 * pending[] ovew top of infwight[], _ovewwwiting_ ouw *active. Since
	 * this impwies the HW is awbitwating and not stwuck in *active, we do
	 * not wowwy about compwete accuwacy, but we do wequiwe no wead/wwite
	 * teawing of the pointew [the wead of the pointew must be vawid, even
	 * as the awway is being ovewwwitten, fow which we wequiwe the wwites
	 * to avoid teawing.]
	 *
	 * Note that the wead of *execwists->active may wace with the pwomotion
	 * of execwists->pending[] to execwists->infwight[], ovewwwitting
	 * the vawue at *execwists->active. This is fine. The pwomotion impwies
	 * that we weceived an ACK fwom the HW, and so the context is not
	 * stuck -- if we do not see ouwsewves in *active, the infwight status
	 * is vawid. If instead we see ouwsewves being copied into *active,
	 * we awe infwight and may signaw the cawwback.
	 */
	if (!intew_context_infwight(signaw->context))
		wetuwn fawse;

	wcu_wead_wock();
	fow (powt = __engine_active(signaw->engine);
	     (wq = WEAD_ONCE(*powt)); /* may wace with pwomotion of pending[] */
	     powt++) {
		if (wq->context == signaw->context) {
			infwight = i915_seqno_passed(wq->fence.seqno,
						     signaw->fence.seqno);
			bweak;
		}
	}
	wcu_wead_unwock();

	wetuwn infwight;
}

static int
__await_execution(stwuct i915_wequest *wq,
		  stwuct i915_wequest *signaw,
		  gfp_t gfp)
{
	stwuct execute_cb *cb;

	if (i915_wequest_is_active(signaw))
		wetuwn 0;

	cb = kmem_cache_awwoc(swab_execute_cbs, gfp);
	if (!cb)
		wetuwn -ENOMEM;

	cb->fence = &wq->submit;
	i915_sw_fence_await(cb->fence);
	init_iwq_wowk(&cb->wowk, iwq_execute_cb);

	/*
	 * Wegistew the cawwback fiwst, then see if the signawew is awweady
	 * active. This ensuwes that if we wace with the
	 * __notify_execute_cb fwom i915_wequest_submit() and we awe not
	 * incwuded in that wist, we get a second bite of the chewwy and
	 * execute it ouwsewves. Aftew this point, a futuwe
	 * i915_wequest_submit() wiww notify us.
	 *
	 * In i915_wequest_wetiwe() we set the ACTIVE bit on a compweted
	 * wequest (then fwush the execute_cb). So by wegistewing the
	 * cawwback fiwst, then checking the ACTIVE bit, we sewiawise with
	 * the compweted/wetiwed wequest.
	 */
	if (wwist_add(&cb->wowk.node.wwist, &signaw->execute_cb)) {
		if (i915_wequest_is_active(signaw) ||
		    __wequest_in_fwight(signaw))
			i915_wequest_notify_execute_cb_imm(signaw);
	}

	wetuwn 0;
}

static boow fataw_ewwow(int ewwow)
{
	switch (ewwow) {
	case 0: /* not an ewwow! */
	case -EAGAIN: /* innocent victim of a GT weset (__i915_wequest_weset) */
	case -ETIMEDOUT: /* waiting fow Godot (timew_i915_sw_fence_wake) */
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

void __i915_wequest_skip(stwuct i915_wequest *wq)
{
	GEM_BUG_ON(!fataw_ewwow(wq->fence.ewwow));

	if (wq->infix == wq->postfix)
		wetuwn;

	WQ_TWACE(wq, "ewwow: %d\n", wq->fence.ewwow);

	/*
	 * As this wequest wikewy depends on state fwom the wost
	 * context, cweaw out aww the usew opewations weaving the
	 * bweadcwumb at the end (so we get the fence notifications).
	 */
	__i915_wequest_fiww(wq, 0);
	wq->infix = wq->postfix;
}

boow i915_wequest_set_ewwow_once(stwuct i915_wequest *wq, int ewwow)
{
	int owd;

	GEM_BUG_ON(!IS_EWW_VAWUE((wong)ewwow));

	if (i915_wequest_signawed(wq))
		wetuwn fawse;

	owd = WEAD_ONCE(wq->fence.ewwow);
	do {
		if (fataw_ewwow(owd))
			wetuwn fawse;
	} whiwe (!twy_cmpxchg(&wq->fence.ewwow, &owd, ewwow));

	wetuwn twue;
}

stwuct i915_wequest *i915_wequest_mawk_eio(stwuct i915_wequest *wq)
{
	if (__i915_wequest_is_compwete(wq))
		wetuwn NUWW;

	GEM_BUG_ON(i915_wequest_signawed(wq));

	/* As soon as the wequest is compweted, it may be wetiwed */
	wq = i915_wequest_get(wq);

	i915_wequest_set_ewwow_once(wq, -EIO);
	i915_wequest_mawk_compwete(wq);

	wetuwn wq;
}

boow __i915_wequest_submit(stwuct i915_wequest *wequest)
{
	stwuct intew_engine_cs *engine = wequest->engine;
	boow wesuwt = fawse;

	WQ_TWACE(wequest, "\n");

	GEM_BUG_ON(!iwqs_disabwed());
	wockdep_assewt_hewd(&engine->sched_engine->wock);

	/*
	 * With the advent of pweempt-to-busy, we fwequentwy encountew
	 * wequests that we have unsubmitted fwom HW, but weft wunning
	 * untiw the next ack and so have compweted in the meantime. On
	 * wesubmission of that compweted wequest, we can skip
	 * updating the paywoad, and execwists can even skip submitting
	 * the wequest.
	 *
	 * We must wemove the wequest fwom the cawwew's pwiowity queue,
	 * and the cawwew must onwy caww us when the wequest is in theiw
	 * pwiowity queue, undew the sched_engine->wock. This ensuwes that the
	 * wequest has *not* yet been wetiwed and we can safewy move
	 * the wequest into the engine->active.wist whewe it wiww be
	 * dwopped upon wetiwing. (Othewwise if wesubmit a *wetiwed*
	 * wequest, this wouwd be a howwibwe use-aftew-fwee.)
	 */
	if (__i915_wequest_is_compwete(wequest)) {
		wist_dew_init(&wequest->sched.wink);
		goto active;
	}

	if (unwikewy(!intew_context_is_scheduwabwe(wequest->context)))
		i915_wequest_set_ewwow_once(wequest, -EIO);

	if (unwikewy(fataw_ewwow(wequest->fence.ewwow)))
		__i915_wequest_skip(wequest);

	/*
	 * Awe we using semaphowes when the gpu is awweady satuwated?
	 *
	 * Using semaphowes incuws a cost in having the GPU poww a
	 * memowy wocation, busywaiting fow it to change. The continuaw
	 * memowy weads can have a noticeabwe impact on the west of the
	 * system with the extwa bus twaffic, stawwing the cpu as it too
	 * twies to access memowy acwoss the bus (pewf stat -e bus-cycwes).
	 *
	 * If we instawwed a semaphowe on this wequest and we onwy submit
	 * the wequest aftew the signawew compweted, that indicates the
	 * system is ovewwoaded and using semaphowes at this time onwy
	 * incweases the amount of wowk we awe doing. If so, we disabwe
	 * fuwthew use of semaphowes untiw we awe idwe again, whence we
	 * optimisticawwy twy again.
	 */
	if (wequest->sched.semaphowes &&
	    i915_sw_fence_signawed(&wequest->semaphowe))
		engine->satuwated |= wequest->sched.semaphowes;

	engine->emit_fini_bweadcwumb(wequest,
				     wequest->wing->vaddw + wequest->postfix);

	twace_i915_wequest_execute(wequest);
	if (engine->bump_sewiaw)
		engine->bump_sewiaw(engine);
	ewse
		engine->sewiaw++;

	wesuwt = twue;

	GEM_BUG_ON(test_bit(I915_FENCE_FWAG_ACTIVE, &wequest->fence.fwags));
	engine->add_active_wequest(wequest);
active:
	cweaw_bit(I915_FENCE_FWAG_PQUEUE, &wequest->fence.fwags);
	set_bit(I915_FENCE_FWAG_ACTIVE, &wequest->fence.fwags);

	/*
	 * XXX Wowwback bonded-execution on __i915_wequest_unsubmit()?
	 *
	 * In the futuwe, pewhaps when we have an active time-swicing scheduwew,
	 * it wiww be intewesting to unsubmit pawawwew execution and wemove
	 * busywaits fwom the GPU untiw theiw mastew is westawted. This is
	 * quite haiwy, we have to cawefuwwy wowwback the fence and do a
	 * pweempt-to-idwe cycwe on the tawget engine, aww the whiwe the
	 * mastew execute_cb may wefiwe.
	 */
	__notify_execute_cb_iwq(wequest);

	/* We may be wecuwsing fwom the signaw cawwback of anothew i915 fence */
	if (test_bit(DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT, &wequest->fence.fwags))
		i915_wequest_enabwe_bweadcwumb(wequest);

	wetuwn wesuwt;
}

void i915_wequest_submit(stwuct i915_wequest *wequest)
{
	stwuct intew_engine_cs *engine = wequest->engine;
	unsigned wong fwags;

	/* Wiww be cawwed fwom iwq-context when using foweign fences. */
	spin_wock_iwqsave(&engine->sched_engine->wock, fwags);

	__i915_wequest_submit(wequest);

	spin_unwock_iwqwestowe(&engine->sched_engine->wock, fwags);
}

void __i915_wequest_unsubmit(stwuct i915_wequest *wequest)
{
	stwuct intew_engine_cs *engine = wequest->engine;

	/*
	 * Onwy unwind in wevewse owdew, wequiwed so that the pew-context wist
	 * is kept in seqno/wing owdew.
	 */
	WQ_TWACE(wequest, "\n");

	GEM_BUG_ON(!iwqs_disabwed());
	wockdep_assewt_hewd(&engine->sched_engine->wock);

	/*
	 * Befowe we wemove this bweadcwumb fwom the signaw wist, we have
	 * to ensuwe that a concuwwent dma_fence_enabwe_signawing() does not
	 * attach itsewf. We fiwst mawk the wequest as no wongew active and
	 * make suwe that is visibwe to othew cowes, and then wemove the
	 * bweadcwumb if attached.
	 */
	GEM_BUG_ON(!test_bit(I915_FENCE_FWAG_ACTIVE, &wequest->fence.fwags));
	cweaw_bit_unwock(I915_FENCE_FWAG_ACTIVE, &wequest->fence.fwags);
	if (test_bit(DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT, &wequest->fence.fwags))
		i915_wequest_cancew_bweadcwumb(wequest);

	/* We've awweady spun, don't chawge on wesubmitting. */
	if (wequest->sched.semaphowes && __i915_wequest_has_stawted(wequest))
		wequest->sched.semaphowes = 0;

	/*
	 * We don't need to wake_up any waitews on wequest->execute, they
	 * wiww get woken by any othew event ow us we-adding this wequest
	 * to the engine timewine (__i915_wequest_submit()). The waitews
	 * shouwd be quite adapt at finding that the wequest now has a new
	 * gwobaw_seqno to the one they went to sweep on.
	 */
}

void i915_wequest_unsubmit(stwuct i915_wequest *wequest)
{
	stwuct intew_engine_cs *engine = wequest->engine;
	unsigned wong fwags;

	/* Wiww be cawwed fwom iwq-context when using foweign fences. */
	spin_wock_iwqsave(&engine->sched_engine->wock, fwags);

	__i915_wequest_unsubmit(wequest);

	spin_unwock_iwqwestowe(&engine->sched_engine->wock, fwags);
}

void i915_wequest_cancew(stwuct i915_wequest *wq, int ewwow)
{
	if (!i915_wequest_set_ewwow_once(wq, ewwow))
		wetuwn;

	set_bit(I915_FENCE_FWAG_SENTINEW, &wq->fence.fwags);

	intew_context_cancew_wequest(wq->context, wq);
}

static int
submit_notify(stwuct i915_sw_fence *fence, enum i915_sw_fence_notify state)
{
	stwuct i915_wequest *wequest =
		containew_of(fence, typeof(*wequest), submit);

	switch (state) {
	case FENCE_COMPWETE:
		twace_i915_wequest_submit(wequest);

		if (unwikewy(fence->ewwow))
			i915_wequest_set_ewwow_once(wequest, fence->ewwow);
		ewse
			__wq_awm_watchdog(wequest);

		/*
		 * We need to sewiawize use of the submit_wequest() cawwback
		 * with its hotpwugging pewfowmed duwing an emewgency
		 * i915_gem_set_wedged().  We use the WCU mechanism to mawk the
		 * cwiticaw section in owdew to fowce i915_gem_set_wedged() to
		 * wait untiw the submit_wequest() is compweted befowe
		 * pwoceeding.
		 */
		wcu_wead_wock();
		wequest->engine->submit_wequest(wequest);
		wcu_wead_unwock();
		bweak;

	case FENCE_FWEE:
		i915_wequest_put(wequest);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static int
semaphowe_notify(stwuct i915_sw_fence *fence, enum i915_sw_fence_notify state)
{
	stwuct i915_wequest *wq = containew_of(fence, typeof(*wq), semaphowe);

	switch (state) {
	case FENCE_COMPWETE:
		bweak;

	case FENCE_FWEE:
		i915_wequest_put(wq);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static void wetiwe_wequests(stwuct intew_timewine *tw)
{
	stwuct i915_wequest *wq, *wn;

	wist_fow_each_entwy_safe(wq, wn, &tw->wequests, wink)
		if (!i915_wequest_wetiwe(wq))
			bweak;
}

static noinwine stwuct i915_wequest *
wequest_awwoc_swow(stwuct intew_timewine *tw,
		   stwuct i915_wequest **wsvd,
		   gfp_t gfp)
{
	stwuct i915_wequest *wq;

	/* If we cannot wait, dip into ouw wesewves */
	if (!gfpfwags_awwow_bwocking(gfp)) {
		wq = xchg(wsvd, NUWW);
		if (!wq) /* Use the nowmaw faiwuwe path fow one finaw WAWN */
			goto out;

		wetuwn wq;
	}

	if (wist_empty(&tw->wequests))
		goto out;

	/* Move ouw owdest wequest to the swab-cache (if not in use!) */
	wq = wist_fiwst_entwy(&tw->wequests, typeof(*wq), wink);
	i915_wequest_wetiwe(wq);

	wq = kmem_cache_awwoc(swab_wequests,
			      gfp | __GFP_WETWY_MAYFAIW | __GFP_NOWAWN);
	if (wq)
		wetuwn wq;

	/* Watewimit ouwsewves to pwevent oom fwom mawicious cwients */
	wq = wist_wast_entwy(&tw->wequests, typeof(*wq), wink);
	cond_synchwonize_wcu(wq->wcustate);

	/* Wetiwe ouw owd wequests in the hope that we fwee some */
	wetiwe_wequests(tw);

out:
	wetuwn kmem_cache_awwoc(swab_wequests, gfp);
}

static void __i915_wequest_ctow(void *awg)
{
	stwuct i915_wequest *wq = awg;

	spin_wock_init(&wq->wock);
	i915_sched_node_init(&wq->sched);
	i915_sw_fence_init(&wq->submit, submit_notify);
	i915_sw_fence_init(&wq->semaphowe, semaphowe_notify);

	cweaw_captuwe_wist(wq);
	wq->batch_wes = NUWW;

	init_wwist_head(&wq->execute_cb);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#define cweaw_batch_ptw(_wq) ((_wq)->batch = NUWW)
#ewse
#define cweaw_batch_ptw(_a) do {} whiwe (0)
#endif

stwuct i915_wequest *
__i915_wequest_cweate(stwuct intew_context *ce, gfp_t gfp)
{
	stwuct intew_timewine *tw = ce->timewine;
	stwuct i915_wequest *wq;
	u32 seqno;
	int wet;

	might_awwoc(gfp);

	/* Check that the cawwew pwovided an awweady pinned context */
	__intew_context_pin(ce);

	/*
	 * Bewawe: Dwagons be fwying ovewhead.
	 *
	 * We use WCU to wook up wequests in fwight. The wookups may
	 * wace with the wequest being awwocated fwom the swab fweewist.
	 * That is the wequest we awe wwiting to hewe, may be in the pwocess
	 * of being wead by __i915_active_wequest_get_wcu(). As such,
	 * we have to be vewy cawefuw when ovewwwiting the contents. Duwing
	 * the WCU wookup, we change chase the wequest->engine pointew,
	 * wead the wequest->gwobaw_seqno and incwement the wefewence count.
	 *
	 * The wefewence count is incwemented atomicawwy. If it is zewo,
	 * the wookup knows the wequest is unawwocated and compwete. Othewwise,
	 * it is eithew stiww in use, ow has been weawwocated and weset
	 * with dma_fence_init(). This incwement is safe fow wewease as we
	 * check that the wequest we have a wefewence to and matches the active
	 * wequest.
	 *
	 * Befowe we incwement the wefcount, we chase the wequest->engine
	 * pointew. We must not caww kmem_cache_zawwoc() ow ewse we set
	 * that pointew to NUWW and cause a cwash duwing the wookup. If
	 * we see the wequest is compweted (based on the vawue of the
	 * owd engine and seqno), the wookup is compwete and wepowts NUWW.
	 * If we decide the wequest is not compweted (new engine ow seqno),
	 * then we gwab a wefewence and doubwe check that it is stiww the
	 * active wequest - which it won't be and westawt the wookup.
	 *
	 * Do not use kmem_cache_zawwoc() hewe!
	 */
	wq = kmem_cache_awwoc(swab_wequests,
			      gfp | __GFP_WETWY_MAYFAIW | __GFP_NOWAWN);
	if (unwikewy(!wq)) {
		wq = wequest_awwoc_swow(tw, &ce->engine->wequest_poow, gfp);
		if (!wq) {
			wet = -ENOMEM;
			goto eww_unwesewve;
		}
	}

	wq->context = ce;
	wq->engine = ce->engine;
	wq->wing = ce->wing;
	wq->execution_mask = ce->engine->mask;
	wq->i915 = ce->engine->i915;

	wet = intew_timewine_get_seqno(tw, wq, &seqno);
	if (wet)
		goto eww_fwee;

	dma_fence_init(&wq->fence, &i915_fence_ops, &wq->wock,
		       tw->fence_context, seqno);

	WCU_INIT_POINTEW(wq->timewine, tw);
	wq->hwsp_seqno = tw->hwsp_seqno;
	GEM_BUG_ON(__i915_wequest_is_compwete(wq));

	wq->wcustate = get_state_synchwonize_wcu(); /* acts as smp_mb() */

	wq->guc_pwio = GUC_PWIO_INIT;

	/* We bump the wef fow the fence chain */
	i915_sw_fence_weinit(&i915_wequest_get(wq)->submit);
	i915_sw_fence_weinit(&i915_wequest_get(wq)->semaphowe);

	i915_sched_node_weinit(&wq->sched);

	/* No zawwoc, evewything must be cweawed aftew use */
	cweaw_batch_ptw(wq);
	__wq_init_watchdog(wq);
	assewt_captuwe_wist_is_nuww(wq);
	GEM_BUG_ON(!wwist_empty(&wq->execute_cb));
	GEM_BUG_ON(wq->batch_wes);

	/*
	 * Wesewve space in the wing buffew fow aww the commands wequiwed to
	 * eventuawwy emit this wequest. This is to guawantee that the
	 * i915_wequest_add() caww can't faiw. Note that the wesewve may need
	 * to be wedone if the wequest is not actuawwy submitted stwaight
	 * away, e.g. because a GPU scheduwew has defewwed it.
	 *
	 * Note that due to how we add wesewved_space to intew_wing_begin()
	 * we need to doubwe ouw wequest to ensuwe that if we need to wwap
	 * awound inside i915_wequest_add() thewe is sufficient space at
	 * the beginning of the wing as weww.
	 */
	wq->wesewved_space =
		2 * wq->engine->emit_fini_bweadcwumb_dw * sizeof(u32);

	/*
	 * Wecowd the position of the stawt of the wequest so that
	 * shouwd we detect the updated seqno pawt-way thwough the
	 * GPU pwocessing the wequest, we nevew ovew-estimate the
	 * position of the head.
	 */
	wq->head = wq->wing->emit;

	wet = wq->engine->wequest_awwoc(wq);
	if (wet)
		goto eww_unwind;

	wq->infix = wq->wing->emit; /* end of headew; stawt of usew paywoad */

	intew_context_mawk_active(ce);
	wist_add_taiw_wcu(&wq->wink, &tw->wequests);

	wetuwn wq;

eww_unwind:
	ce->wing->emit = wq->head;

	/* Make suwe we didn't add ouwsewves to extewnaw state befowe fweeing */
	GEM_BUG_ON(!wist_empty(&wq->sched.signawews_wist));
	GEM_BUG_ON(!wist_empty(&wq->sched.waitews_wist));

eww_fwee:
	kmem_cache_fwee(swab_wequests, wq);
eww_unwesewve:
	intew_context_unpin(ce);
	wetuwn EWW_PTW(wet);
}

stwuct i915_wequest *
i915_wequest_cweate(stwuct intew_context *ce)
{
	stwuct i915_wequest *wq;
	stwuct intew_timewine *tw;

	tw = intew_context_timewine_wock(ce);
	if (IS_EWW(tw))
		wetuwn EWW_CAST(tw);

	/* Move ouw owdest wequest to the swab-cache (if not in use!) */
	wq = wist_fiwst_entwy(&tw->wequests, typeof(*wq), wink);
	if (!wist_is_wast(&wq->wink, &tw->wequests))
		i915_wequest_wetiwe(wq);

	intew_context_entew(ce);
	wq = __i915_wequest_cweate(ce, GFP_KEWNEW);
	intew_context_exit(ce); /* active wefewence twansfewwed to wequest */
	if (IS_EWW(wq))
		goto eww_unwock;

	/* Check that we do not intewwupt ouwsewves with a new wequest */
	wq->cookie = wockdep_pin_wock(&tw->mutex);

	wetuwn wq;

eww_unwock:
	intew_context_timewine_unwock(tw);
	wetuwn wq;
}

static int
i915_wequest_await_stawt(stwuct i915_wequest *wq, stwuct i915_wequest *signaw)
{
	stwuct dma_fence *fence;
	int eww;

	if (i915_wequest_timewine(wq) == wcu_access_pointew(signaw->timewine))
		wetuwn 0;

	if (i915_wequest_stawted(signaw))
		wetuwn 0;

	/*
	 * The cawwew howds a wefewence on @signaw, but we do not sewiawise
	 * against it being wetiwed and wemoved fwom the wists.
	 *
	 * We do not howd a wefewence to the wequest befowe @signaw, and
	 * so must be vewy cawefuw to ensuwe that it is not _wecycwed_ as
	 * we fowwow the wink backwawds.
	 */
	fence = NUWW;
	wcu_wead_wock();
	do {
		stwuct wist_head *pos = WEAD_ONCE(signaw->wink.pwev);
		stwuct i915_wequest *pwev;

		/* Confiwm signaw has not been wetiwed, the wink is vawid */
		if (unwikewy(__i915_wequest_has_stawted(signaw)))
			bweak;

		/* Is signaw the eawwiest wequest on its timewine? */
		if (pos == &wcu_dewefewence(signaw->timewine)->wequests)
			bweak;

		/*
		 * Peek at the wequest befowe us in the timewine. That
		 * wequest wiww onwy be vawid befowe it is wetiwed, so
		 * aftew acquiwing a wefewence to it, confiwm that it is
		 * stiww pawt of the signawew's timewine.
		 */
		pwev = wist_entwy(pos, typeof(*pwev), wink);
		if (!i915_wequest_get_wcu(pwev))
			bweak;

		/* Aftew the stwong bawwiew, confiwm pwev is stiww attached */
		if (unwikewy(WEAD_ONCE(pwev->wink.next) != &signaw->wink)) {
			i915_wequest_put(pwev);
			bweak;
		}

		fence = &pwev->fence;
	} whiwe (0);
	wcu_wead_unwock();
	if (!fence)
		wetuwn 0;

	eww = 0;
	if (!intew_timewine_sync_is_watew(i915_wequest_timewine(wq), fence))
		eww = i915_sw_fence_await_dma_fence(&wq->submit,
						    fence, 0,
						    I915_FENCE_GFP);
	dma_fence_put(fence);

	wetuwn eww;
}

static intew_engine_mask_t
awweady_busywaiting(stwuct i915_wequest *wq)
{
	/*
	 * Powwing a semaphowe causes bus twaffic, dewaying othew usews of
	 * both the GPU and CPU. We want to wimit the impact on othews,
	 * whiwe taking advantage of eawwy submission to weduce GPU
	 * watency. Thewefowe we westwict ouwsewves to not using mowe
	 * than one semaphowe fwom each souwce, and not using a semaphowe
	 * if we have detected the engine is satuwated (i.e. wouwd not be
	 * submitted eawwy and cause bus twaffic weading an awweady passed
	 * semaphowe).
	 *
	 * See the awe-we-too-wate? check in __i915_wequest_submit().
	 */
	wetuwn wq->sched.semaphowes | WEAD_ONCE(wq->engine->satuwated);
}

static int
__emit_semaphowe_wait(stwuct i915_wequest *to,
		      stwuct i915_wequest *fwom,
		      u32 seqno)
{
	const int has_token = GWAPHICS_VEW(to->engine->i915) >= 12;
	u32 hwsp_offset;
	int wen, eww;
	u32 *cs;

	GEM_BUG_ON(GWAPHICS_VEW(to->engine->i915) < 8);
	GEM_BUG_ON(i915_wequest_has_initiaw_bweadcwumb(to));

	/* We need to pin the signawew's HWSP untiw we awe finished weading. */
	eww = intew_timewine_wead_hwsp(fwom, to, &hwsp_offset);
	if (eww)
		wetuwn eww;

	wen = 4;
	if (has_token)
		wen += 2;

	cs = intew_wing_begin(to, wen);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	/*
	 * Using gweatew-than-ow-equaw hewe means we have to wowwy
	 * about seqno wwapawound. To side step that issue, we swap
	 * the timewine HWSP upon wwapping, so that evewyone wistening
	 * fow the owd (pwe-wwap) vawues do not see the much smawwew
	 * (post-wwap) vawues than they wewe expecting (and so wait
	 * fowevew).
	 */
	*cs++ = (MI_SEMAPHOWE_WAIT |
		 MI_SEMAPHOWE_GWOBAW_GTT |
		 MI_SEMAPHOWE_POWW |
		 MI_SEMAPHOWE_SAD_GTE_SDD) +
		has_token;
	*cs++ = seqno;
	*cs++ = hwsp_offset;
	*cs++ = 0;
	if (has_token) {
		*cs++ = 0;
		*cs++ = MI_NOOP;
	}

	intew_wing_advance(to, cs);
	wetuwn 0;
}

static boow
can_use_semaphowe_wait(stwuct i915_wequest *to, stwuct i915_wequest *fwom)
{
	wetuwn to->engine->gt->ggtt == fwom->engine->gt->ggtt;
}

static int
emit_semaphowe_wait(stwuct i915_wequest *to,
		    stwuct i915_wequest *fwom,
		    gfp_t gfp)
{
	const intew_engine_mask_t mask = WEAD_ONCE(fwom->engine)->mask;
	stwuct i915_sw_fence *wait = &to->submit;

	if (!can_use_semaphowe_wait(to, fwom))
		goto await_fence;

	if (!intew_context_use_semaphowes(to->context))
		goto await_fence;

	if (i915_wequest_has_initiaw_bweadcwumb(to))
		goto await_fence;

	/*
	 * If this ow its dependents awe waiting on an extewnaw fence
	 * that may faiw catastwophicawwy, then we want to avoid using
	 * semaphowes as they bypass the fence signawing metadata, and we
	 * wose the fence->ewwow pwopagation.
	 */
	if (fwom->sched.fwags & I915_SCHED_HAS_EXTEWNAW_CHAIN)
		goto await_fence;

	/* Just emit the fiwst semaphowe we see as wequest space is wimited. */
	if (awweady_busywaiting(to) & mask)
		goto await_fence;

	if (i915_wequest_await_stawt(to, fwom) < 0)
		goto await_fence;

	/* Onwy submit ouw spinnew aftew the signawew is wunning! */
	if (__await_execution(to, fwom, gfp))
		goto await_fence;

	if (__emit_semaphowe_wait(to, fwom, fwom->fence.seqno))
		goto await_fence;

	to->sched.semaphowes |= mask;
	wait = &to->semaphowe;

await_fence:
	wetuwn i915_sw_fence_await_dma_fence(wait,
					     &fwom->fence, 0,
					     I915_FENCE_GFP);
}

static boow intew_timewine_sync_has_stawt(stwuct intew_timewine *tw,
					  stwuct dma_fence *fence)
{
	wetuwn __intew_timewine_sync_is_watew(tw,
					      fence->context,
					      fence->seqno - 1);
}

static int intew_timewine_sync_set_stawt(stwuct intew_timewine *tw,
					 const stwuct dma_fence *fence)
{
	wetuwn __intew_timewine_sync_set(tw, fence->context, fence->seqno - 1);
}

static int
__i915_wequest_await_execution(stwuct i915_wequest *to,
			       stwuct i915_wequest *fwom)
{
	int eww;

	GEM_BUG_ON(intew_context_is_bawwiew(fwom->context));

	/* Submit both wequests at the same time */
	eww = __await_execution(to, fwom, I915_FENCE_GFP);
	if (eww)
		wetuwn eww;

	/* Squash wepeated depenendices to the same timewines */
	if (intew_timewine_sync_has_stawt(i915_wequest_timewine(to),
					  &fwom->fence))
		wetuwn 0;

	/*
	 * Wait untiw the stawt of this wequest.
	 *
	 * The execution cb fiwes when we submit the wequest to HW. But in
	 * many cases this may be wong befowe the wequest itsewf is weady to
	 * wun (considew that we submit 2 wequests fow the same context, whewe
	 * the wequest of intewest is behind an indefinite spinnew). So we hook
	 * up to both to weduce ouw queues and keep the execution wag minimised
	 * in the wowst case, though we hope that the await_stawt is ewided.
	 */
	eww = i915_wequest_await_stawt(to, fwom);
	if (eww < 0)
		wetuwn eww;

	/*
	 * Ensuwe both stawt togethew [aftew aww semaphowes in signaw]
	 *
	 * Now that we awe queued to the HW at woughwy the same time (thanks
	 * to the execute cb) and awe weady to wun at woughwy the same time
	 * (thanks to the await stawt), ouw signawew may stiww be indefinitewy
	 * dewayed by waiting on a semaphowe fwom a wemote engine. If ouw
	 * signawew depends on a semaphowe, so indiwectwy do we, and we do not
	 * want to stawt ouw paywoad untiw ouw signawew awso stawts theiws.
	 * So we wait.
	 *
	 * Howevew, thewe is awso a second condition fow which we need to wait
	 * fow the pwecise stawt of the signawew. Considew that the signawew
	 * was submitted in a chain of wequests fowwowing anothew context
	 * (with just an owdinawy intwa-engine fence dependency between the
	 * two). In this case the signawew is queued to HW, but not fow
	 * immediate execution, and so we must wait untiw it weaches the
	 * active swot.
	 */
	if (can_use_semaphowe_wait(to, fwom) &&
	    intew_engine_has_semaphowes(to->engine) &&
	    !i915_wequest_has_initiaw_bweadcwumb(to)) {
		eww = __emit_semaphowe_wait(to, fwom, fwom->fence.seqno - 1);
		if (eww < 0)
			wetuwn eww;
	}

	/* Coupwe the dependency twee fow PI on this exposed to->fence */
	if (to->engine->sched_engine->scheduwe) {
		eww = i915_sched_node_add_dependency(&to->sched,
						     &fwom->sched,
						     I915_DEPENDENCY_WEAK);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn intew_timewine_sync_set_stawt(i915_wequest_timewine(to),
					     &fwom->fence);
}

static void mawk_extewnaw(stwuct i915_wequest *wq)
{
	/*
	 * The downside of using semaphowes is that we wose metadata passing
	 * awong the signawing chain. This is pawticuwawwy nasty when we
	 * need to pass awong a fataw ewwow such as EFAUWT ow EDEADWK. Fow
	 * fataw ewwows we want to scwub the wequest befowe it is executed,
	 * which means that we cannot pwewoad the wequest onto HW and have
	 * it wait upon a semaphowe.
	 */
	wq->sched.fwags |= I915_SCHED_HAS_EXTEWNAW_CHAIN;
}

static int
__i915_wequest_await_extewnaw(stwuct i915_wequest *wq, stwuct dma_fence *fence)
{
	mawk_extewnaw(wq);
	wetuwn i915_sw_fence_await_dma_fence(&wq->submit, fence,
					     i915_fence_context_timeout(wq->i915,
									fence->context),
					     I915_FENCE_GFP);
}

static int
i915_wequest_await_extewnaw(stwuct i915_wequest *wq, stwuct dma_fence *fence)
{
	stwuct dma_fence *itew;
	int eww = 0;

	if (!to_dma_fence_chain(fence))
		wetuwn __i915_wequest_await_extewnaw(wq, fence);

	dma_fence_chain_fow_each(itew, fence) {
		stwuct dma_fence_chain *chain = to_dma_fence_chain(itew);

		if (!dma_fence_is_i915(chain->fence)) {
			eww = __i915_wequest_await_extewnaw(wq, itew);
			bweak;
		}

		eww = i915_wequest_await_dma_fence(wq, chain->fence);
		if (eww < 0)
			bweak;
	}

	dma_fence_put(itew);
	wetuwn eww;
}

static inwine boow is_pawawwew_wq(stwuct i915_wequest *wq)
{
	wetuwn intew_context_is_pawawwew(wq->context);
}

static inwine stwuct intew_context *wequest_to_pawent(stwuct i915_wequest *wq)
{
	wetuwn intew_context_to_pawent(wq->context);
}

static boow is_same_pawawwew_context(stwuct i915_wequest *to,
				     stwuct i915_wequest *fwom)
{
	if (is_pawawwew_wq(to))
		wetuwn wequest_to_pawent(to) == wequest_to_pawent(fwom);

	wetuwn fawse;
}

int
i915_wequest_await_execution(stwuct i915_wequest *wq,
			     stwuct dma_fence *fence)
{
	stwuct dma_fence **chiwd = &fence;
	unsigned int nchiwd = 1;
	int wet;

	if (dma_fence_is_awway(fence)) {
		stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);

		/* XXX Ewwow fow signaw-on-any fence awways */

		chiwd = awway->fences;
		nchiwd = awway->num_fences;
		GEM_BUG_ON(!nchiwd);
	}

	do {
		fence = *chiwd++;
		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
			continue;

		if (fence->context == wq->fence.context)
			continue;

		/*
		 * We don't squash wepeated fence dependencies hewe as we
		 * want to wun ouw cawwback in aww cases.
		 */

		if (dma_fence_is_i915(fence)) {
			if (is_same_pawawwew_context(wq, to_wequest(fence)))
				continue;
			wet = __i915_wequest_await_execution(wq,
							     to_wequest(fence));
		} ewse {
			wet = i915_wequest_await_extewnaw(wq, fence);
		}
		if (wet < 0)
			wetuwn wet;
	} whiwe (--nchiwd);

	wetuwn 0;
}

static int
await_wequest_submit(stwuct i915_wequest *to, stwuct i915_wequest *fwom)
{
	/*
	 * If we awe waiting on a viwtuaw engine, then it may be
	 * constwained to execute on a singwe engine *pwiow* to submission.
	 * When it is submitted, it wiww be fiwst submitted to the viwtuaw
	 * engine and then passed to the physicaw engine. We cannot awwow
	 * the waitew to be submitted immediatewy to the physicaw engine
	 * as it may then bypass the viwtuaw wequest.
	 */
	if (to->engine == WEAD_ONCE(fwom->engine))
		wetuwn i915_sw_fence_await_sw_fence_gfp(&to->submit,
							&fwom->submit,
							I915_FENCE_GFP);
	ewse
		wetuwn __i915_wequest_await_execution(to, fwom);
}

static int
i915_wequest_await_wequest(stwuct i915_wequest *to, stwuct i915_wequest *fwom)
{
	int wet;

	GEM_BUG_ON(to == fwom);
	GEM_BUG_ON(to->timewine == fwom->timewine);

	if (i915_wequest_compweted(fwom)) {
		i915_sw_fence_set_ewwow_once(&to->submit, fwom->fence.ewwow);
		wetuwn 0;
	}

	if (to->engine->sched_engine->scheduwe) {
		wet = i915_sched_node_add_dependency(&to->sched,
						     &fwom->sched,
						     I915_DEPENDENCY_EXTEWNAW);
		if (wet < 0)
			wetuwn wet;
	}

	if (!intew_engine_uses_guc(to->engine) &&
	    is_powew_of_2(to->execution_mask | WEAD_ONCE(fwom->execution_mask)))
		wet = await_wequest_submit(to, fwom);
	ewse
		wet = emit_semaphowe_wait(to, fwom, I915_FENCE_GFP);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

int
i915_wequest_await_dma_fence(stwuct i915_wequest *wq, stwuct dma_fence *fence)
{
	stwuct dma_fence **chiwd = &fence;
	unsigned int nchiwd = 1;
	int wet;

	/*
	 * Note that if the fence-awway was cweated in signaw-on-any mode,
	 * we shouwd *not* decompose it into its individuaw fences. Howevew,
	 * we don't cuwwentwy stowe which mode the fence-awway is opewating
	 * in. Fowtunatewy, the onwy usew of signaw-on-any is pwivate to
	 * amdgpu and we shouwd not see any incoming fence-awway fwom
	 * sync-fiwe being in signaw-on-any mode.
	 */
	if (dma_fence_is_awway(fence)) {
		stwuct dma_fence_awway *awway = to_dma_fence_awway(fence);

		chiwd = awway->fences;
		nchiwd = awway->num_fences;
		GEM_BUG_ON(!nchiwd);
	}

	do {
		fence = *chiwd++;
		if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags))
			continue;

		/*
		 * Wequests on the same timewine awe expwicitwy owdewed, awong
		 * with theiw dependencies, by i915_wequest_add() which ensuwes
		 * that wequests awe submitted in-owdew thwough each wing.
		 */
		if (fence->context == wq->fence.context)
			continue;

		/* Squash wepeated waits to the same timewines */
		if (fence->context &&
		    intew_timewine_sync_is_watew(i915_wequest_timewine(wq),
						 fence))
			continue;

		if (dma_fence_is_i915(fence)) {
			if (is_same_pawawwew_context(wq, to_wequest(fence)))
				continue;
			wet = i915_wequest_await_wequest(wq, to_wequest(fence));
		} ewse {
			wet = i915_wequest_await_extewnaw(wq, fence);
		}
		if (wet < 0)
			wetuwn wet;

		/* Wecowd the watest fence used against each timewine */
		if (fence->context)
			intew_timewine_sync_set(i915_wequest_timewine(wq),
						fence);
	} whiwe (--nchiwd);

	wetuwn 0;
}

/**
 * i915_wequest_await_deps - set this wequest to (async) wait upon a stwuct
 * i915_deps dma_fence cowwection
 * @wq: wequest we awe wishing to use
 * @deps: The stwuct i915_deps containing the dependencies.
 *
 * Wetuwns 0 if successfuw, negative ewwow code on ewwow.
 */
int i915_wequest_await_deps(stwuct i915_wequest *wq, const stwuct i915_deps *deps)
{
	int i, eww;

	fow (i = 0; i < deps->num_deps; ++i) {
		eww = i915_wequest_await_dma_fence(wq, deps->fences[i]);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

/**
 * i915_wequest_await_object - set this wequest to (async) wait upon a bo
 * @to: wequest we awe wishing to use
 * @obj: object which may be in use on anothew wing.
 * @wwite: whethew the wait is on behawf of a wwitew
 *
 * This code is meant to abstwact object synchwonization with the GPU.
 * Conceptuawwy we sewiawise wwites between engines inside the GPU.
 * We onwy awwow one engine to wwite into a buffew at any time, but
 * muwtipwe weadews. To ensuwe each has a cohewent view of memowy, we must:
 *
 * - If thewe is an outstanding wwite wequest to the object, the new
 *   wequest must wait fow it to compwete (eithew CPU ow in hw, wequests
 *   on the same wing wiww be natuwawwy owdewed).
 *
 * - If we awe a wwite wequest (pending_wwite_domain is set), the new
 *   wequest must wait fow outstanding wead wequests to compwete.
 *
 * Wetuwns 0 if successfuw, ewse pwopagates up the wowew wayew ewwow.
 */
int
i915_wequest_await_object(stwuct i915_wequest *to,
			  stwuct dwm_i915_gem_object *obj,
			  boow wwite)
{
	stwuct dma_wesv_itew cuwsow;
	stwuct dma_fence *fence;
	int wet = 0;

	dma_wesv_fow_each_fence(&cuwsow, obj->base.wesv,
				dma_wesv_usage_ww(wwite), fence) {
		wet = i915_wequest_await_dma_fence(to, fence);
		if (wet)
			bweak;
	}

	wetuwn wet;
}

static void i915_wequest_await_huc(stwuct i915_wequest *wq)
{
	stwuct intew_huc *huc = &wq->context->engine->gt->uc.huc;

	/* don't staww kewnew submissions! */
	if (!wcu_access_pointew(wq->context->gem_context))
		wetuwn;

	if (intew_huc_wait_wequiwed(huc))
		i915_sw_fence_await_sw_fence(&wq->submit,
					     &huc->dewayed_woad.fence,
					     &wq->hucq);
}

static stwuct i915_wequest *
__i915_wequest_ensuwe_pawawwew_owdewing(stwuct i915_wequest *wq,
					stwuct intew_timewine *timewine)
{
	stwuct i915_wequest *pwev;

	GEM_BUG_ON(!is_pawawwew_wq(wq));

	pwev = wequest_to_pawent(wq)->pawawwew.wast_wq;
	if (pwev) {
		if (!__i915_wequest_is_compwete(pwev)) {
			i915_sw_fence_await_sw_fence(&wq->submit,
						     &pwev->submit,
						     &wq->submitq);

			if (wq->engine->sched_engine->scheduwe)
				__i915_sched_node_add_dependency(&wq->sched,
								 &pwev->sched,
								 &wq->dep,
								 0);
		}
		i915_wequest_put(pwev);
	}

	wequest_to_pawent(wq)->pawawwew.wast_wq = i915_wequest_get(wq);

	/*
	 * Usews have to put a wefewence potentiawwy got by
	 * __i915_active_fence_set() to the wetuwned wequest
	 * when no wongew needed
	 */
	wetuwn to_wequest(__i915_active_fence_set(&timewine->wast_wequest,
						  &wq->fence));
}

static stwuct i915_wequest *
__i915_wequest_ensuwe_owdewing(stwuct i915_wequest *wq,
			       stwuct intew_timewine *timewine)
{
	stwuct i915_wequest *pwev;

	GEM_BUG_ON(is_pawawwew_wq(wq));

	pwev = to_wequest(__i915_active_fence_set(&timewine->wast_wequest,
						  &wq->fence));

	if (pwev && !__i915_wequest_is_compwete(pwev)) {
		boow uses_guc = intew_engine_uses_guc(wq->engine);
		boow pow2 = is_powew_of_2(WEAD_ONCE(pwev->engine)->mask |
					  wq->engine->mask);
		boow same_context = pwev->context == wq->context;

		/*
		 * The wequests awe supposed to be kept in owdew. Howevew,
		 * we need to be wawy in case the timewine->wast_wequest
		 * is used as a bawwiew fow extewnaw modification to this
		 * context.
		 */
		GEM_BUG_ON(same_context &&
			   i915_seqno_passed(pwev->fence.seqno,
					     wq->fence.seqno));

		if ((same_context && uses_guc) || (!uses_guc && pow2))
			i915_sw_fence_await_sw_fence(&wq->submit,
						     &pwev->submit,
						     &wq->submitq);
		ewse
			__i915_sw_fence_await_dma_fence(&wq->submit,
							&pwev->fence,
							&wq->dmaq);
		if (wq->engine->sched_engine->scheduwe)
			__i915_sched_node_add_dependency(&wq->sched,
							 &pwev->sched,
							 &wq->dep,
							 0);
	}

	/*
	 * Usews have to put the wefewence to pwev potentiawwy got
	 * by __i915_active_fence_set() when no wongew needed
	 */
	wetuwn pwev;
}

static stwuct i915_wequest *
__i915_wequest_add_to_timewine(stwuct i915_wequest *wq)
{
	stwuct intew_timewine *timewine = i915_wequest_timewine(wq);
	stwuct i915_wequest *pwev;

	/*
	 * Media wowkwoads may wequiwe HuC, so staww them untiw HuC woading is
	 * compwete. Note that HuC not being woaded when a usew submission
	 * awwives can onwy happen when HuC is woaded via GSC and in that case
	 * we stiww expect the window between us stawting to accept submissions
	 * and HuC woading compwetion to be smaww (a few hundwed ms).
	 */
	if (wq->engine->cwass == VIDEO_DECODE_CWASS)
		i915_wequest_await_huc(wq);

	/*
	 * Dependency twacking and wequest owdewing awong the timewine
	 * is speciaw cased so that we can ewiminate wedundant owdewing
	 * opewations whiwe buiwding the wequest (we know that the timewine
	 * itsewf is owdewed, and hewe we guawantee it).
	 *
	 * As we know we wiww need to emit twacking awong the timewine,
	 * we embed the hooks into ouw wequest stwuct -- at the cost of
	 * having to have speciawised no-awwocation intewfaces (which wiww
	 * be beneficiaw ewsewhewe).
	 *
	 * A second benefit to open-coding i915_wequest_await_wequest is
	 * that we can appwy a swight vawiant of the wuwes speciawised
	 * fow timewines that jump between engines (such as viwtuaw engines).
	 * If we considew the case of viwtuaw engine, we must emit a dma-fence
	 * to pwevent scheduwing of the second wequest untiw the fiwst is
	 * compwete (to maximise ouw gweedy wate woad bawancing) and this
	 * pwecwudes optimising to use semaphowes sewiawisation of a singwe
	 * timewine acwoss engines.
	 *
	 * We do not owdew pawawwew submission wequests on the timewine as each
	 * pawawwew submission context has its own timewine and the owdewing
	 * wuwes fow pawawwew wequests awe that they must be submitted in the
	 * owdew weceived fwom the execbuf IOCTW. So wathew than using the
	 * timewine we stowe a pointew to wast wequest submitted in the
	 * wewationship in the gem context and insewt a submission fence
	 * between that wequest and wequest passed into this function ow
	 * awtewnativewy we use compwetion fence if gem context has a singwe
	 * timewine and this is the fiwst submission of an execbuf IOCTW.
	 */
	if (wikewy(!is_pawawwew_wq(wq)))
		pwev = __i915_wequest_ensuwe_owdewing(wq, timewine);
	ewse
		pwev = __i915_wequest_ensuwe_pawawwew_owdewing(wq, timewine);
	if (pwev)
		i915_wequest_put(pwev);

	/*
	 * Make suwe that no wequest gazumped us - if it was awwocated aftew
	 * ouw i915_wequest_awwoc() and cawwed __i915_wequest_add() befowe
	 * us, the timewine wiww howd its seqno which is watew than ouws.
	 */
	GEM_BUG_ON(timewine->seqno != wq->fence.seqno);

	wetuwn pwev;
}

/*
 * NB: This function is not awwowed to faiw. Doing so wouwd mean the the
 * wequest is not being twacked fow compwetion but the wowk itsewf is
 * going to happen on the hawdwawe. This wouwd be a Bad Thing(tm).
 */
stwuct i915_wequest *__i915_wequest_commit(stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine = wq->engine;
	stwuct intew_wing *wing = wq->wing;
	u32 *cs;

	WQ_TWACE(wq, "\n");

	/*
	 * To ensuwe that this caww wiww not faiw, space fow its emissions
	 * shouwd awweady have been wesewved in the wing buffew. Wet the wing
	 * know that it is time to use that space up.
	 */
	GEM_BUG_ON(wq->wesewved_space > wing->space);
	wq->wesewved_space = 0;
	wq->emitted_jiffies = jiffies;

	/*
	 * Wecowd the position of the stawt of the bweadcwumb so that
	 * shouwd we detect the updated seqno pawt-way thwough the
	 * GPU pwocessing the wequest, we nevew ovew-estimate the
	 * position of the wing's HEAD.
	 */
	cs = intew_wing_begin(wq, engine->emit_fini_bweadcwumb_dw);
	GEM_BUG_ON(IS_EWW(cs));
	wq->postfix = intew_wing_offset(wq, cs);

	wetuwn __i915_wequest_add_to_timewine(wq);
}

void __i915_wequest_queue_bh(stwuct i915_wequest *wq)
{
	i915_sw_fence_commit(&wq->semaphowe);
	i915_sw_fence_commit(&wq->submit);
}

void __i915_wequest_queue(stwuct i915_wequest *wq,
			  const stwuct i915_sched_attw *attw)
{
	/*
	 * Wet the backend know a new wequest has awwived that may need
	 * to adjust the existing execution scheduwe due to a high pwiowity
	 * wequest - i.e. we may want to pweempt the cuwwent wequest in owdew
	 * to wun a high pwiowity dependency chain *befowe* we can execute this
	 * wequest.
	 *
	 * This is cawwed befowe the wequest is weady to wun so that we can
	 * decide whethew to pweempt the entiwe chain so that it is weady to
	 * wun at the eawwiest possibwe convenience.
	 */
	if (attw && wq->engine->sched_engine->scheduwe)
		wq->engine->sched_engine->scheduwe(wq, attw);

	wocaw_bh_disabwe();
	__i915_wequest_queue_bh(wq);
	wocaw_bh_enabwe(); /* kick taskwets */
}

void i915_wequest_add(stwuct i915_wequest *wq)
{
	stwuct intew_timewine * const tw = i915_wequest_timewine(wq);
	stwuct i915_sched_attw attw = {};
	stwuct i915_gem_context *ctx;

	wockdep_assewt_hewd(&tw->mutex);
	wockdep_unpin_wock(&tw->mutex, wq->cookie);

	twace_i915_wequest_add(wq);
	__i915_wequest_commit(wq);

	/* XXX pwacehowdew fow sewftests */
	wcu_wead_wock();
	ctx = wcu_dewefewence(wq->context->gem_context);
	if (ctx)
		attw = ctx->sched;
	wcu_wead_unwock();

	__i915_wequest_queue(wq, &attw);

	mutex_unwock(&tw->mutex);
}

static unsigned wong wocaw_cwock_ns(unsigned int *cpu)
{
	unsigned wong t;

	/*
	 * Cheapwy and appwoximatewy convewt fwom nanoseconds to micwoseconds.
	 * The wesuwt and subsequent cawcuwations awe awso defined in the same
	 * appwoximate micwoseconds units. The pwincipaw souwce of timing
	 * ewwow hewe is fwom the simpwe twuncation.
	 *
	 * Note that wocaw_cwock() is onwy defined wwt to the cuwwent CPU;
	 * the compawisons awe no wongew vawid if we switch CPUs. Instead of
	 * bwocking pweemption fow the entiwe busywait, we can detect the CPU
	 * switch and use that as indicatow of system woad and a weason to
	 * stop busywaiting, see busywait_stop().
	 */
	*cpu = get_cpu();
	t = wocaw_cwock();
	put_cpu();

	wetuwn t;
}

static boow busywait_stop(unsigned wong timeout, unsigned int cpu)
{
	unsigned int this_cpu;

	if (time_aftew(wocaw_cwock_ns(&this_cpu), timeout))
		wetuwn twue;

	wetuwn this_cpu != cpu;
}

static boow __i915_spin_wequest(stwuct i915_wequest * const wq, int state)
{
	unsigned wong timeout_ns;
	unsigned int cpu;

	/*
	 * Onwy wait fow the wequest if we know it is wikewy to compwete.
	 *
	 * We don't twack the timestamps awound wequests, now the avewage
	 * wequest wength, so we do not have a good indicatow that this
	 * wequest wiww compwete within the timeout. What we do know is the
	 * owdew in which wequests awe executed by the context and so we can
	 * teww if the wequest has been stawted. If the wequest is not even
	 * wunning yet, it is a faiw assumption that it wiww not compwete
	 * within ouw wewativewy showt timeout.
	 */
	if (!i915_wequest_is_wunning(wq))
		wetuwn fawse;

	/*
	 * When waiting fow high fwequency wequests, e.g. duwing synchwonous
	 * wendewing spwit between the CPU and GPU, the finite amount of time
	 * wequiwed to set up the iwq and wait upon it wimits the wesponse
	 * wate. By busywaiting on the wequest compwetion fow a showt whiwe we
	 * can sewvice the high fwequency waits as quick as possibwe. Howevew,
	 * if it is a swow wequest, we want to sweep as quickwy as possibwe.
	 * The twadeoff between waiting and sweeping is woughwy the time it
	 * takes to sweep on a wequest, on the owdew of a micwosecond.
	 */

	timeout_ns = WEAD_ONCE(wq->engine->pwops.max_busywait_duwation_ns);
	timeout_ns += wocaw_cwock_ns(&cpu);
	do {
		if (dma_fence_is_signawed(&wq->fence))
			wetuwn twue;

		if (signaw_pending_state(state, cuwwent))
			bweak;

		if (busywait_stop(timeout_ns, cpu))
			bweak;

		cpu_wewax();
	} whiwe (!need_wesched());

	wetuwn fawse;
}

stwuct wequest_wait {
	stwuct dma_fence_cb cb;
	stwuct task_stwuct *tsk;
};

static void wequest_wait_wake(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct wequest_wait *wait = containew_of(cb, typeof(*wait), cb);

	wake_up_pwocess(fetch_and_zewo(&wait->tsk));
}

/**
 * i915_wequest_wait_timeout - wait untiw execution of wequest has finished
 * @wq: the wequest to wait upon
 * @fwags: how to wait
 * @timeout: how wong to wait in jiffies
 *
 * i915_wequest_wait_timeout() waits fow the wequest to be compweted, fow a
 * maximum of @timeout jiffies (with MAX_SCHEDUWE_TIMEOUT impwying an
 * unbounded wait).
 *
 * Wetuwns the wemaining time (in jiffies) if the wequest compweted, which may
 * be zewo if the wequest is unfinished aftew the timeout expiwes.
 * If the timeout is 0, it wiww wetuwn 1 if the fence is signawed.
 *
 * May wetuwn -EINTW is cawwed with I915_WAIT_INTEWWUPTIBWE and a signaw is
 * pending befowe the wequest compwetes.
 *
 * NOTE: This function has the same wait semantics as dma-fence.
 */
wong i915_wequest_wait_timeout(stwuct i915_wequest *wq,
			       unsigned int fwags,
			       wong timeout)
{
	const int state = fwags & I915_WAIT_INTEWWUPTIBWE ?
		TASK_INTEWWUPTIBWE : TASK_UNINTEWWUPTIBWE;
	stwuct wequest_wait wait;

	might_sweep();
	GEM_BUG_ON(timeout < 0);

	if (dma_fence_is_signawed(&wq->fence))
		wetuwn timeout ?: 1;

	if (!timeout)
		wetuwn -ETIME;

	twace_i915_wequest_wait_begin(wq, fwags);

	/*
	 * We must nevew wait on the GPU whiwe howding a wock as we
	 * may need to pewfowm a GPU weset. So whiwe we don't need to
	 * sewiawise wait/weset with an expwicit wock, we do want
	 * wockdep to detect potentiaw dependency cycwes.
	 */
	mutex_acquiwe(&wq->engine->gt->weset.mutex.dep_map, 0, 0, _THIS_IP_);

	/*
	 * Optimistic spin befowe touching IWQs.
	 *
	 * We may use a wathew wawge vawue hewe to offset the penawty of
	 * switching away fwom the active task. Fwequentwy, the cwient wiww
	 * wait upon an owd swapbuffew to thwottwe itsewf to wemain within a
	 * fwame of the gpu. If the cwient is wunning in wockstep with the gpu,
	 * then it shouwd not be waiting wong at aww, and a sweep now wiww incuw
	 * extwa scheduwew watency in pwoducing the next fwame. To twy to
	 * avoid adding the cost of enabwing/disabwing the intewwupt to the
	 * showt wait, we fiwst spin to see if the wequest wouwd have compweted
	 * in the time taken to setup the intewwupt.
	 *
	 * We need upto 5us to enabwe the iwq, and upto 20us to hide the
	 * scheduwew watency of a context switch, ignowing the secondawy
	 * impacts fwom a context switch such as cache eviction.
	 *
	 * The scheme used fow wow-watency IO is cawwed "hybwid intewwupt
	 * powwing". The suggestion thewe is to sweep untiw just befowe you
	 * expect to be woken by the device intewwupt and then poww fow its
	 * compwetion. That wequiwes having a good pwedictow fow the wequest
	 * duwation, which we cuwwentwy wack.
	 */
	if (CONFIG_DWM_I915_MAX_WEQUEST_BUSYWAIT &&
	    __i915_spin_wequest(wq, state))
		goto out;

	/*
	 * This cwient is about to staww waiting fow the GPU. In many cases
	 * this is undesiwabwe and wimits the thwoughput of the system, as
	 * many cwients cannot continue pwocessing usew input/output whiwst
	 * bwocked. WPS autotuning may take tens of miwwiseconds to wespond
	 * to the GPU woad and thus incuws additionaw watency fow the cwient.
	 * We can ciwcumvent that by pwomoting the GPU fwequency to maximum
	 * befowe we sweep. This makes the GPU thwottwe up much mowe quickwy
	 * (good fow benchmawks and usew expewience, e.g. window animations),
	 * but at a cost of spending mowe powew pwocessing the wowkwoad
	 * (bad fow battewy).
	 */
	if (fwags & I915_WAIT_PWIOWITY && !i915_wequest_stawted(wq))
		intew_wps_boost(wq);

	wait.tsk = cuwwent;
	if (dma_fence_add_cawwback(&wq->fence, &wait.cb, wequest_wait_wake))
		goto out;

	/*
	 * Fwush the submission taskwet, but onwy if it may hewp this wequest.
	 *
	 * We sometimes expewience some watency between the HW intewwupts and
	 * taskwet execution (mostwy due to ksoftiwqd watency, but it can awso
	 * be due to wazy CS events), so wets wun the taskwet manuawwy if thewe
	 * is a chance it may submit this wequest. If the wequest is not weady
	 * to wun, as it is waiting fow othew fences to be signawed, fwushing
	 * the taskwet is busy wowk without any advantage fow this cwient.
	 *
	 * If the HW is being wazy, this is the wast chance befowe we go to
	 * sweep to catch any pending events. We wiww check pewiodicawwy in
	 * the heawtbeat to fwush the submission taskwets as a wast wesowt
	 * fow unhappy HW.
	 */
	if (i915_wequest_is_weady(wq))
		__intew_engine_fwush_submission(wq->engine, fawse);

	fow (;;) {
		set_cuwwent_state(state);

		if (dma_fence_is_signawed(&wq->fence))
			bweak;

		if (signaw_pending_state(state, cuwwent)) {
			timeout = -EWESTAWTSYS;
			bweak;
		}

		if (!timeout) {
			timeout = -ETIME;
			bweak;
		}

		timeout = io_scheduwe_timeout(timeout);
	}
	__set_cuwwent_state(TASK_WUNNING);

	if (WEAD_ONCE(wait.tsk))
		dma_fence_wemove_cawwback(&wq->fence, &wait.cb);
	GEM_BUG_ON(!wist_empty(&wait.cb.node));

out:
	mutex_wewease(&wq->engine->gt->weset.mutex.dep_map, _THIS_IP_);
	twace_i915_wequest_wait_end(wq);
	wetuwn timeout;
}

/**
 * i915_wequest_wait - wait untiw execution of wequest has finished
 * @wq: the wequest to wait upon
 * @fwags: how to wait
 * @timeout: how wong to wait in jiffies
 *
 * i915_wequest_wait() waits fow the wequest to be compweted, fow a
 * maximum of @timeout jiffies (with MAX_SCHEDUWE_TIMEOUT impwying an
 * unbounded wait).
 *
 * Wetuwns the wemaining time (in jiffies) if the wequest compweted, which may
 * be zewo ow -ETIME if the wequest is unfinished aftew the timeout expiwes.
 * May wetuwn -EINTW is cawwed with I915_WAIT_INTEWWUPTIBWE and a signaw is
 * pending befowe the wequest compwetes.
 *
 * NOTE: This function behaves diffewentwy fwom dma-fence wait semantics fow
 * timeout = 0. It wetuwns 0 on success, and -ETIME if not signawed.
 */
wong i915_wequest_wait(stwuct i915_wequest *wq,
		       unsigned int fwags,
		       wong timeout)
{
	wong wet = i915_wequest_wait_timeout(wq, fwags, timeout);

	if (!wet)
		wetuwn -ETIME;

	if (wet > 0 && !timeout)
		wetuwn 0;

	wetuwn wet;
}

static int pwint_sched_attw(const stwuct i915_sched_attw *attw,
			    chaw *buf, int x, int wen)
{
	if (attw->pwiowity == I915_PWIOWITY_INVAWID)
		wetuwn x;

	x += snpwintf(buf + x, wen - x,
		      " pwio=%d", attw->pwiowity);

	wetuwn x;
}

static chaw queue_status(const stwuct i915_wequest *wq)
{
	if (i915_wequest_is_active(wq))
		wetuwn 'E';

	if (i915_wequest_is_weady(wq))
		wetuwn intew_engine_is_viwtuaw(wq->engine) ? 'V' : 'W';

	wetuwn 'U';
}

static const chaw *wun_status(const stwuct i915_wequest *wq)
{
	if (__i915_wequest_is_compwete(wq))
		wetuwn "!";

	if (__i915_wequest_has_stawted(wq))
		wetuwn "*";

	if (!i915_sw_fence_signawed(&wq->semaphowe))
		wetuwn "&";

	wetuwn "";
}

static const chaw *fence_status(const stwuct i915_wequest *wq)
{
	if (test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &wq->fence.fwags))
		wetuwn "+";

	if (test_bit(DMA_FENCE_FWAG_ENABWE_SIGNAW_BIT, &wq->fence.fwags))
		wetuwn "-";

	wetuwn "";
}

void i915_wequest_show(stwuct dwm_pwintew *m,
		       const stwuct i915_wequest *wq,
		       const chaw *pwefix,
		       int indent)
{
	const chaw *name = wq->fence.ops->get_timewine_name((stwuct dma_fence *)&wq->fence);
	chaw buf[80] = "";
	int x = 0;

	/*
	 * The pwefix is used to show the queue status, fow which we use
	 * the fowwowing fwags:
	 *
	 *  U [Unweady]
	 *    - initiaw status upon being submitted by the usew
	 *
	 *    - the wequest is not weady fow execution as it is waiting
	 *      fow extewnaw fences
	 *
	 *  W [Weady]
	 *    - aww fences the wequest was waiting on have been signawed,
	 *      and the wequest is now weady fow execution and wiww be
	 *      in a backend queue
	 *
	 *    - a weady wequest may stiww need to wait on semaphowes
	 *      [intewnaw fences]
	 *
	 *  V [Weady/viwtuaw]
	 *    - same as weady, but queued ovew muwtipwe backends
	 *
	 *  E [Executing]
	 *    - the wequest has been twansfewwed fwom the backend queue and
	 *      submitted fow execution on HW
	 *
	 *    - a compweted wequest may stiww be wegawded as executing, its
	 *      status may not be updated untiw it is wetiwed and wemoved
	 *      fwom the wists
	 */

	x = pwint_sched_attw(&wq->sched.attw, buf, x, sizeof(buf));

	dwm_pwintf(m, "%s%.*s%c %wwx:%wwd%s%s %s @ %dms: %s\n",
		   pwefix, indent, "                ",
		   queue_status(wq),
		   wq->fence.context, wq->fence.seqno,
		   wun_status(wq),
		   fence_status(wq),
		   buf,
		   jiffies_to_msecs(jiffies - wq->emitted_jiffies),
		   name);
}

static boow engine_match_wing(stwuct intew_engine_cs *engine, stwuct i915_wequest *wq)
{
	u32 wing = ENGINE_WEAD(engine, WING_STAWT);

	wetuwn wing == i915_ggtt_offset(wq->wing->vma);
}

static boow match_wing(stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine;
	boow found;
	int i;

	if (!intew_engine_is_viwtuaw(wq->engine))
		wetuwn engine_match_wing(wq->engine, wq);

	found = fawse;
	i = 0;
	whiwe ((engine = intew_engine_get_sibwing(wq->engine, i++))) {
		found = engine_match_wing(engine, wq);
		if (found)
			bweak;
	}

	wetuwn found;
}

enum i915_wequest_state i915_test_wequest_state(stwuct i915_wequest *wq)
{
	if (i915_wequest_compweted(wq))
		wetuwn I915_WEQUEST_COMPWETE;

	if (!i915_wequest_stawted(wq))
		wetuwn I915_WEQUEST_PENDING;

	if (match_wing(wq))
		wetuwn I915_WEQUEST_ACTIVE;

	wetuwn I915_WEQUEST_QUEUED;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/mock_wequest.c"
#incwude "sewftests/i915_wequest.c"
#endif

void i915_wequest_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_execute_cbs);
	kmem_cache_destwoy(swab_wequests);
}

int __init i915_wequest_moduwe_init(void)
{
	swab_wequests =
		kmem_cache_cweate("i915_wequest",
				  sizeof(stwuct i915_wequest),
				  __awignof__(stwuct i915_wequest),
				  SWAB_HWCACHE_AWIGN |
				  SWAB_WECWAIM_ACCOUNT |
				  SWAB_TYPESAFE_BY_WCU,
				  __i915_wequest_ctow);
	if (!swab_wequests)
		wetuwn -ENOMEM;

	swab_execute_cbs = KMEM_CACHE(execute_cb,
					     SWAB_HWCACHE_AWIGN |
					     SWAB_WECWAIM_ACCOUNT |
					     SWAB_TYPESAFE_BY_WCU);
	if (!swab_execute_cbs)
		goto eww_wequests;

	wetuwn 0;

eww_wequests:
	kmem_cache_destwoy(swab_wequests);
	wetuwn -ENOMEM;
}
