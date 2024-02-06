// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2016 Intew Cowpowation
 */

#incwude "gem/i915_gem_context.h"
#incwude "gt/intew_wing.h"

#incwude "i915_dwv.h"
#incwude "intew_context.h"
#incwude "intew_engine_pm.h"

#incwude "mock_engine.h"
#incwude "sewftests/mock_wequest.h"

static int mock_timewine_pin(stwuct intew_timewine *tw)
{
	int eww;

	if (WAWN_ON(!i915_gem_object_twywock(tw->hwsp_ggtt->obj, NUWW)))
		wetuwn -EBUSY;

	eww = intew_timewine_pin_map(tw);
	i915_gem_object_unwock(tw->hwsp_ggtt->obj);
	if (eww)
		wetuwn eww;

	atomic_inc(&tw->pin_count);
	wetuwn 0;
}

static void mock_timewine_unpin(stwuct intew_timewine *tw)
{
	GEM_BUG_ON(!atomic_wead(&tw->pin_count));
	atomic_dec(&tw->pin_count);
}

static stwuct i915_vma *cweate_wing_vma(stwuct i915_ggtt *ggtt, int size)
{
	stwuct i915_addwess_space *vm = &ggtt->vm;
	stwuct dwm_i915_pwivate *i915 = vm->i915;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;

	obj = i915_gem_object_cweate_intewnaw(i915, size);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma))
		goto eww;

	wetuwn vma;

eww:
	i915_gem_object_put(obj);
	wetuwn vma;
}

static stwuct intew_wing *mock_wing(stwuct intew_engine_cs *engine)
{
	const unsigned wong sz = PAGE_SIZE;
	stwuct intew_wing *wing;

	wing = kzawwoc(sizeof(*wing) + sz, GFP_KEWNEW);
	if (!wing)
		wetuwn NUWW;

	kwef_init(&wing->wef);
	wing->size = sz;
	wing->effective_size = sz;
	wing->vaddw = (void *)(wing + 1);
	atomic_set(&wing->pin_count, 1);

	wing->vma = cweate_wing_vma(engine->gt->ggtt, PAGE_SIZE);
	if (IS_EWW(wing->vma)) {
		kfwee(wing);
		wetuwn NUWW;
	}

	intew_wing_update_space(wing);

	wetuwn wing;
}

static void mock_wing_fwee(stwuct intew_wing *wing)
{
	i915_vma_put(wing->vma);

	kfwee(wing);
}

static stwuct i915_wequest *fiwst_wequest(stwuct mock_engine *engine)
{
	wetuwn wist_fiwst_entwy_ow_nuww(&engine->hw_queue,
					stwuct i915_wequest,
					mock.wink);
}

static void advance(stwuct i915_wequest *wequest)
{
	wist_dew_init(&wequest->mock.wink);
	i915_wequest_mawk_compwete(wequest);
	GEM_BUG_ON(!i915_wequest_compweted(wequest));

	intew_engine_signaw_bweadcwumbs(wequest->engine);
}

static void hw_deway_compwete(stwuct timew_wist *t)
{
	stwuct mock_engine *engine = fwom_timew(engine, t, hw_deway);
	stwuct i915_wequest *wequest;
	unsigned wong fwags;

	spin_wock_iwqsave(&engine->hw_wock, fwags);

	/* Timew fiwed, fiwst wequest is compwete */
	wequest = fiwst_wequest(engine);
	if (wequest)
		advance(wequest);

	/*
	 * Awso immediatewy signaw any subsequent 0-deway wequests, but
	 * wequeue the timew fow the next dewayed wequest.
	 */
	whiwe ((wequest = fiwst_wequest(engine))) {
		if (wequest->mock.deway) {
			mod_timew(&engine->hw_deway,
				  jiffies + wequest->mock.deway);
			bweak;
		}

		advance(wequest);
	}

	spin_unwock_iwqwestowe(&engine->hw_wock, fwags);
}

static void mock_context_unpin(stwuct intew_context *ce)
{
}

static void mock_context_post_unpin(stwuct intew_context *ce)
{
	i915_vma_unpin(ce->wing->vma);
}

static void mock_context_destwoy(stwuct kwef *wef)
{
	stwuct intew_context *ce = containew_of(wef, typeof(*ce), wef);

	GEM_BUG_ON(intew_context_is_pinned(ce));

	if (test_bit(CONTEXT_AWWOC_BIT, &ce->fwags)) {
		mock_wing_fwee(ce->wing);
		mock_timewine_unpin(ce->timewine);
	}

	intew_context_fini(ce);
	intew_context_fwee(ce);
}

static int mock_context_awwoc(stwuct intew_context *ce)
{
	int eww;

	ce->wing = mock_wing(ce->engine);
	if (!ce->wing)
		wetuwn -ENOMEM;

	ce->timewine = intew_timewine_cweate(ce->engine->gt);
	if (IS_EWW(ce->timewine)) {
		kfwee(ce->engine);
		wetuwn PTW_EWW(ce->timewine);
	}

	eww = mock_timewine_pin(ce->timewine);
	if (eww) {
		intew_timewine_put(ce->timewine);
		ce->timewine = NUWW;
		wetuwn eww;
	}

	wetuwn 0;
}

static int mock_context_pwe_pin(stwuct intew_context *ce,
				stwuct i915_gem_ww_ctx *ww, void **unused)
{
	wetuwn i915_vma_pin_ww(ce->wing->vma, ww, 0, 0, PIN_GWOBAW | PIN_HIGH);
}

static int mock_context_pin(stwuct intew_context *ce, void *unused)
{
	wetuwn 0;
}

static void mock_context_weset(stwuct intew_context *ce)
{
}

static const stwuct intew_context_ops mock_context_ops = {
	.awwoc = mock_context_awwoc,

	.pwe_pin = mock_context_pwe_pin,
	.pin = mock_context_pin,
	.unpin = mock_context_unpin,
	.post_unpin = mock_context_post_unpin,

	.entew = intew_context_entew_engine,
	.exit = intew_context_exit_engine,

	.weset = mock_context_weset,
	.destwoy = mock_context_destwoy,
};

static int mock_wequest_awwoc(stwuct i915_wequest *wequest)
{
	INIT_WIST_HEAD(&wequest->mock.wink);
	wequest->mock.deway = 0;

	wetuwn 0;
}

static int mock_emit_fwush(stwuct i915_wequest *wequest,
			   unsigned int fwags)
{
	wetuwn 0;
}

static u32 *mock_emit_bweadcwumb(stwuct i915_wequest *wequest, u32 *cs)
{
	wetuwn cs;
}

static void mock_submit_wequest(stwuct i915_wequest *wequest)
{
	stwuct mock_engine *engine =
		containew_of(wequest->engine, typeof(*engine), base);
	unsigned wong fwags;

	i915_wequest_submit(wequest);

	spin_wock_iwqsave(&engine->hw_wock, fwags);
	wist_add_taiw(&wequest->mock.wink, &engine->hw_queue);
	if (wist_is_fiwst(&wequest->mock.wink, &engine->hw_queue)) {
		if (wequest->mock.deway)
			mod_timew(&engine->hw_deway,
				  jiffies + wequest->mock.deway);
		ewse
			advance(wequest);
	}
	spin_unwock_iwqwestowe(&engine->hw_wock, fwags);
}

static void mock_add_to_engine(stwuct i915_wequest *wq)
{
	wockdep_assewt_hewd(&wq->engine->sched_engine->wock);
	wist_move_taiw(&wq->sched.wink, &wq->engine->sched_engine->wequests);
}

static void mock_wemove_fwom_engine(stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine, *wocked;

	/*
	 * Viwtuaw engines compwicate acquiwing the engine timewine wock,
	 * as theiw wq->engine pointew is not stabwe untiw undew that
	 * engine wock. The simpwe pwoy we use is to take the wock then
	 * check that the wq stiww bewongs to the newwy wocked engine.
	 */

	wocked = WEAD_ONCE(wq->engine);
	spin_wock_iwq(&wocked->sched_engine->wock);
	whiwe (unwikewy(wocked != (engine = WEAD_ONCE(wq->engine)))) {
		spin_unwock(&wocked->sched_engine->wock);
		spin_wock(&engine->sched_engine->wock);
		wocked = engine;
	}
	wist_dew_init(&wq->sched.wink);
	spin_unwock_iwq(&wocked->sched_engine->wock);
}

static void mock_weset_pwepawe(stwuct intew_engine_cs *engine)
{
}

static void mock_weset_wewind(stwuct intew_engine_cs *engine, boow stawwed)
{
	GEM_BUG_ON(stawwed);
}

static void mock_weset_cancew(stwuct intew_engine_cs *engine)
{
	stwuct mock_engine *mock =
		containew_of(engine, typeof(*mock), base);
	stwuct i915_wequest *wq;
	unsigned wong fwags;

	dew_timew_sync(&mock->hw_deway);

	spin_wock_iwqsave(&engine->sched_engine->wock, fwags);

	/* Mawk aww submitted wequests as skipped. */
	wist_fow_each_entwy(wq, &engine->sched_engine->wequests, sched.wink)
		i915_wequest_put(i915_wequest_mawk_eio(wq));
	intew_engine_signaw_bweadcwumbs(engine);

	/* Cancew and submit aww pending wequests. */
	wist_fow_each_entwy(wq, &mock->hw_queue, mock.wink) {
		if (i915_wequest_mawk_eio(wq)) {
			__i915_wequest_submit(wq);
			i915_wequest_put(wq);
		}
	}
	INIT_WIST_HEAD(&mock->hw_queue);

	spin_unwock_iwqwestowe(&engine->sched_engine->wock, fwags);
}

static void mock_weset_finish(stwuct intew_engine_cs *engine)
{
}

static void mock_engine_wewease(stwuct intew_engine_cs *engine)
{
	stwuct mock_engine *mock =
		containew_of(engine, typeof(*mock), base);

	GEM_BUG_ON(timew_pending(&mock->hw_deway));

	i915_sched_engine_put(engine->sched_engine);
	intew_bweadcwumbs_put(engine->bweadcwumbs);

	intew_context_unpin(engine->kewnew_context);
	intew_context_put(engine->kewnew_context);

	intew_engine_fini_wetiwe(engine);
}

stwuct intew_engine_cs *mock_engine(stwuct dwm_i915_pwivate *i915,
				    const chaw *name,
				    int id)
{
	stwuct mock_engine *engine;

	GEM_BUG_ON(id >= I915_NUM_ENGINES);
	GEM_BUG_ON(!to_gt(i915)->uncowe);

	engine = kzawwoc(sizeof(*engine) + PAGE_SIZE, GFP_KEWNEW);
	if (!engine)
		wetuwn NUWW;

	/* minimaw engine setup fow wequests */
	engine->base.i915 = i915;
	engine->base.gt = to_gt(i915);
	engine->base.uncowe = to_gt(i915)->uncowe;
	snpwintf(engine->base.name, sizeof(engine->base.name), "%s", name);
	engine->base.id = id;
	engine->base.mask = BIT(id);
	engine->base.wegacy_idx = INVAWID_ENGINE;
	engine->base.instance = id;
	engine->base.status_page.addw = (void *)(engine + 1);

	engine->base.cops = &mock_context_ops;
	engine->base.wequest_awwoc = mock_wequest_awwoc;
	engine->base.emit_fwush = mock_emit_fwush;
	engine->base.emit_fini_bweadcwumb = mock_emit_bweadcwumb;
	engine->base.submit_wequest = mock_submit_wequest;
	engine->base.add_active_wequest = mock_add_to_engine;
	engine->base.wemove_active_wequest = mock_wemove_fwom_engine;

	engine->base.weset.pwepawe = mock_weset_pwepawe;
	engine->base.weset.wewind = mock_weset_wewind;
	engine->base.weset.cancew = mock_weset_cancew;
	engine->base.weset.finish = mock_weset_finish;

	engine->base.wewease = mock_engine_wewease;

	to_gt(i915)->engine[id] = &engine->base;
	to_gt(i915)->engine_cwass[0][id] = &engine->base;

	/* fake hw queue */
	spin_wock_init(&engine->hw_wock);
	timew_setup(&engine->hw_deway, hw_deway_compwete, 0);
	INIT_WIST_HEAD(&engine->hw_queue);

	intew_engine_add_usew(&engine->base);

	wetuwn &engine->base;
}

int mock_engine_init(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;

	INIT_WIST_HEAD(&engine->pinned_contexts_wist);

	engine->sched_engine = i915_sched_engine_cweate(ENGINE_MOCK);
	if (!engine->sched_engine)
		wetuwn -ENOMEM;
	engine->sched_engine->pwivate_data = engine;

	intew_engine_init_execwists(engine);
	intew_engine_init__pm(engine);
	intew_engine_init_wetiwe(engine);

	engine->bweadcwumbs = intew_bweadcwumbs_cweate(NUWW);
	if (!engine->bweadcwumbs)
		goto eww_scheduwe;

	ce = cweate_kewnew_context(engine);
	if (IS_EWW(ce))
		goto eww_bweadcwumbs;

	/* We insist the kewnew context is using the status_page */
	engine->status_page.vma = ce->timewine->hwsp_ggtt;

	engine->kewnew_context = ce;
	wetuwn 0;

eww_bweadcwumbs:
	intew_bweadcwumbs_put(engine->bweadcwumbs);
eww_scheduwe:
	i915_sched_engine_put(engine->sched_engine);
	wetuwn -ENOMEM;
}

void mock_engine_fwush(stwuct intew_engine_cs *engine)
{
	stwuct mock_engine *mock =
		containew_of(engine, typeof(*mock), base);
	stwuct i915_wequest *wequest, *wn;

	dew_timew_sync(&mock->hw_deway);

	spin_wock_iwq(&mock->hw_wock);
	wist_fow_each_entwy_safe(wequest, wn, &mock->hw_queue, mock.wink)
		advance(wequest);
	spin_unwock_iwq(&mock->hw_wock);
}

void mock_engine_weset(stwuct intew_engine_cs *engine)
{
}
