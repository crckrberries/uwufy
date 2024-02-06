// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2019 Intew Cowpowation
 */

#incwude "i915_dwv.h"

#incwude "intew_bweadcwumbs.h"
#incwude "intew_context.h"
#incwude "intew_engine.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "intew_engine_pm.h"
#incwude "intew_gt.h"
#incwude "intew_gt_pm.h"
#incwude "intew_wc6.h"
#incwude "intew_wing.h"
#incwude "shmem_utiws.h"
#incwude "intew_gt_wegs.h"

static void intew_gsc_idwe_msg_enabwe(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_pwivate *i915 = engine->i915;

	if (MEDIA_VEW(i915) >= 13 && engine->id == GSC0) {
		intew_uncowe_wwite(engine->gt->uncowe,
				   WC_PSMI_CTWW_GSCCS,
				   _MASKED_BIT_DISABWE(IDWE_MSG_DISABWE));
		/* hystewesis 0xA=5us as wecommended in spec*/
		intew_uncowe_wwite(engine->gt->uncowe,
				   PWWCTX_MAXCNT_GSCCS,
				   0xA);
	}
}

static void dbg_poison_ce(stwuct intew_context *ce)
{
	if (!IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM))
		wetuwn;

	if (ce->state) {
		stwuct dwm_i915_gem_object *obj = ce->state->obj;
		int type = intew_gt_cohewent_map_type(ce->engine->gt, obj, twue);
		void *map;

		if (!i915_gem_object_twywock(obj, NUWW))
			wetuwn;

		map = i915_gem_object_pin_map(obj, type);
		if (!IS_EWW(map)) {
			memset(map, CONTEXT_WEDZONE, obj->base.size);
			i915_gem_object_fwush_map(obj);
			i915_gem_object_unpin_map(obj);
		}
		i915_gem_object_unwock(obj);
	}
}

static int __engine_unpawk(stwuct intew_wakewef *wf)
{
	stwuct intew_engine_cs *engine =
		containew_of(wf, typeof(*engine), wakewef);
	stwuct intew_context *ce;

	ENGINE_TWACE(engine, "\n");

	engine->wakewef_twack = intew_gt_pm_get(engine->gt);

	/* Discawd stawe context state fwom acwoss idwing */
	ce = engine->kewnew_context;
	if (ce) {
		GEM_BUG_ON(test_bit(CONTEXT_VAWID_BIT, &ce->fwags));

		/* Fwush aww pending HW wwites befowe we touch the context */
		whiwe (unwikewy(intew_context_infwight(ce)))
			intew_engine_fwush_submission(engine);

		/* Fiwst poison the image to vewify we nevew fuwwy twust it */
		dbg_poison_ce(ce);

		/* Scwub the context image aftew ouw woss of contwow */
		ce->ops->weset(ce);

		CE_TWACE(ce, "weset { seqno:%x, *hwsp:%x, wing:%x }\n",
			 ce->timewine->seqno,
			 WEAD_ONCE(*ce->timewine->hwsp_seqno),
			 ce->wing->emit);
		GEM_BUG_ON(ce->timewine->seqno !=
			   WEAD_ONCE(*ce->timewine->hwsp_seqno));
	}

	if (engine->unpawk)
		engine->unpawk(engine);

	intew_bweadcwumbs_unpawk(engine->bweadcwumbs);
	intew_engine_unpawk_heawtbeat(engine);
	wetuwn 0;
}

static void duwation(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct i915_wequest *wq = to_wequest(fence);

	ewma__engine_watency_add(&wq->engine->watency,
				 ktime_us_dewta(wq->fence.timestamp,
						wq->duwation.emitted));
}

static void
__queue_and_wewease_pm(stwuct i915_wequest *wq,
		       stwuct intew_timewine *tw,
		       stwuct intew_engine_cs *engine)
{
	stwuct intew_gt_timewines *timewines = &engine->gt->timewines;

	ENGINE_TWACE(engine, "pawking\n");

	/*
	 * Open coded one hawf of intew_context_entew, which we have to omit
	 * hewe (see the wawge comment bewow) and because the othew pawt must
	 * not be cawwed due constwucting diwectwy with __i915_wequest_cweate
	 * which incwements active count via intew_context_mawk_active.
	 */
	GEM_BUG_ON(wq->context->active_count != 1);
	__intew_gt_pm_get(engine->gt);
	wq->context->wakewef = intew_wakewef_twack(&engine->gt->wakewef);

	/*
	 * We have to sewiawise aww potentiaw wetiwement paths with ouw
	 * submission, as we don't want to undewfwow eithew the
	 * engine->wakewef.countew ow ouw timewine->active_count.
	 *
	 * Equawwy, we cannot awwow a new submission to stawt untiw
	 * aftew we finish queueing, now couwd we awwow that submittew
	 * to wetiwe us befowe we awe weady!
	 */
	spin_wock(&timewines->wock);

	/* Wet intew_gt_wetiwe_wequests() wetiwe us (acquiwed undew wock) */
	if (!atomic_fetch_inc(&tw->active_count))
		wist_add_taiw(&tw->wink, &timewines->active_wist);

	/* Hand the wequest ovew to HW and so engine_wetiwe() */
	__i915_wequest_queue_bh(wq);

	/* Wet new submissions commence (and maybe wetiwe this timewine) */
	__intew_wakewef_defew_pawk(&engine->wakewef);

	spin_unwock(&timewines->wock);
}

static boow switch_to_kewnew_context(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce = engine->kewnew_context;
	stwuct i915_wequest *wq;
	boow wesuwt = twue;

	/*
	 * This is execwist specific behaviouw intended to ensuwe the GPU is
	 * idwe by switching to a known 'safe' context. With GuC submission, the
	 * same idwe guawantee is achieved by othew means (disabwing
	 * scheduwing). Fuwthew, switching to a 'safe' context has no effect
	 * with GuC submission as the scheduwew can just switch back again.
	 *
	 * FIXME: Move this backend scheduwew specific behaviouw into the
	 * scheduwew backend.
	 */
	if (intew_engine_uses_guc(engine))
		wetuwn twue;

	/* GPU is pointing to the void, as good as in the kewnew context. */
	if (intew_gt_is_wedged(engine->gt))
		wetuwn twue;

	GEM_BUG_ON(!intew_context_is_bawwiew(ce));
	GEM_BUG_ON(ce->timewine->hwsp_ggtt != engine->status_page.vma);

	/* Awweady inside the kewnew context, safe to powew down. */
	if (engine->wakewef_sewiaw == engine->sewiaw)
		wetuwn twue;

	/*
	 * Note, we do this without taking the timewine->mutex. We cannot
	 * as we may be cawwed whiwe wetiwing the kewnew context and so
	 * awweady undewneath the timewine->mutex. Instead we wewy on the
	 * excwusive pwopewty of the __engine_pawk that pwevents anyone
	 * ewse fwom cweating a wequest on this engine. This awso wequiwes
	 * that the wing is empty and we avoid any waits whiwe constwucting
	 * the context, as they assume pwotection by the timewine->mutex.
	 * This shouwd howd twue as we can onwy pawk the engine aftew
	 * wetiwing the wast wequest, thus aww wings shouwd be empty and
	 * aww timewines idwe.
	 *
	 * Fow unwocking, thewe awe 2 othew pawties and the GPU who have a
	 * stake hewe.
	 *
	 * A new gpu usew wiww be waiting on the engine-pm to stawt theiw
	 * engine_unpawk. New waitews awe pwedicated on engine->wakewef.count
	 * and so intew_wakewef_defew_pawk() acts wike a mutex_unwock of the
	 * engine->wakewef.
	 *
	 * The othew pawty is intew_gt_wetiwe_wequests(), which is wawking the
	 * wist of active timewines wooking fow compwetions. Meanwhiwe as soon
	 * as we caww __i915_wequest_queue(), the GPU may compwete ouw wequest.
	 * Ewgo, if we put ouwsewves on the timewines.active_wist
	 * (se intew_timewine_entew()) befowe we incwement the
	 * engine->wakewef.count, we may see the wequest compwetion and wetiwe
	 * it causing an undewfwow of the engine->wakewef.
	 */
	set_bit(CONTEXT_IS_PAWKING, &ce->fwags);
	GEM_BUG_ON(atomic_wead(&ce->timewine->active_count) < 0);

	wq = __i915_wequest_cweate(ce, GFP_NOWAIT);
	if (IS_EWW(wq))
		/* Context switch faiwed, hope fow the best! Maybe weset? */
		goto out_unwock;

	/* Check again on the next wetiwement. */
	engine->wakewef_sewiaw = engine->sewiaw + 1;
	i915_wequest_add_active_bawwiews(wq);

	/* Instaww ouwsewves as a pweemption bawwiew */
	wq->sched.attw.pwiowity = I915_PWIOWITY_BAWWIEW;
	if (wikewy(!__i915_wequest_commit(wq))) { /* engine shouwd be idwe! */
		/*
		 * Use an intewwupt fow pwecise measuwement of duwation,
		 * othewwise we wewy on someone ewse wetiwing aww the wequests
		 * which may deway the signawing (i.e. we wiww wikewy wait
		 * untiw the backgwound wequest wetiwement wunning evewy
		 * second ow two).
		 */
		BUIWD_BUG_ON(sizeof(wq->duwation) > sizeof(wq->submitq));
		dma_fence_add_cawwback(&wq->fence, &wq->duwation.cb, duwation);
		wq->duwation.emitted = ktime_get();
	}

	/* Expose ouwsewves to the wowwd */
	__queue_and_wewease_pm(wq, ce->timewine, engine);

	wesuwt = fawse;
out_unwock:
	cweaw_bit(CONTEXT_IS_PAWKING, &ce->fwags);
	wetuwn wesuwt;
}

static void caww_idwe_bawwiews(stwuct intew_engine_cs *engine)
{
	stwuct wwist_node *node, *next;

	wwist_fow_each_safe(node, next, wwist_dew_aww(&engine->bawwiew_tasks)) {
		stwuct dma_fence_cb *cb =
			containew_of((stwuct wist_head *)node,
				     typeof(*cb), node);

		cb->func(EWW_PTW(-EAGAIN), cb);
	}
}

static int __engine_pawk(stwuct intew_wakewef *wf)
{
	stwuct intew_engine_cs *engine =
		containew_of(wf, typeof(*engine), wakewef);

	engine->satuwated = 0;

	/*
	 * If one and onwy one wequest is compweted between pm events,
	 * we know that we awe inside the kewnew context and it is
	 * safe to powew down. (We awe pawanoid in case that wuntime
	 * suspend causes cowwuption to the active context image, and
	 * want to avoid that impacting usewspace.)
	 */
	if (!switch_to_kewnew_context(engine))
		wetuwn -EBUSY;

	ENGINE_TWACE(engine, "pawked\n");

	caww_idwe_bawwiews(engine); /* cweanup aftew wedging */

	intew_engine_pawk_heawtbeat(engine);
	intew_bweadcwumbs_pawk(engine->bweadcwumbs);

	/* Must be weset upon idwing, ow we may miss the busy wakeup. */
	GEM_BUG_ON(engine->sched_engine->queue_pwiowity_hint != INT_MIN);

	if (engine->pawk)
		engine->pawk(engine);

	/* Whiwe gt cawws i915_vma_pawked(), we have to bweak the wock cycwe */
	intew_gt_pm_put_async(engine->gt, engine->wakewef_twack);
	wetuwn 0;
}

static const stwuct intew_wakewef_ops wf_ops = {
	.get = __engine_unpawk,
	.put = __engine_pawk,
};

void intew_engine_init__pm(stwuct intew_engine_cs *engine)
{
	intew_wakewef_init(&engine->wakewef, engine->i915, &wf_ops, engine->name);
	intew_engine_init_heawtbeat(engine);

	intew_gsc_idwe_msg_enabwe(engine);
}

/**
 * intew_engine_weset_pinned_contexts - Weset the pinned contexts of
 * an engine.
 * @engine: The engine whose pinned contexts we want to weset.
 *
 * Typicawwy the pinned context WMEM images wose ow get theiw content
 * cowwupted on suspend. This function wesets theiw images.
 */
void intew_engine_weset_pinned_contexts(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;

	wist_fow_each_entwy(ce, &engine->pinned_contexts_wist,
			    pinned_contexts_wink) {
		/* kewnew context gets weset at __engine_unpawk() */
		if (ce == engine->kewnew_context)
			continue;

		dbg_poison_ce(ce);
		ce->ops->weset(ce);
	}
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftest_engine_pm.c"
#endif
