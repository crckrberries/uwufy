/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#incwude <winux/debugobjects.h>

#incwude "gt/intew_context.h"
#incwude "gt/intew_engine_heawtbeat.h"
#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_wing.h"

#incwude "i915_dwv.h"
#incwude "i915_active.h"

/*
 * Active wefs memowy management
 *
 * To be mowe economicaw with memowy, we weap aww the i915_active twees as
 * they idwe (when we know the active wequests awe inactive) and awwocate the
 * nodes fwom a wocaw swab cache to hopefuwwy weduce the fwagmentation.
 */
static stwuct kmem_cache *swab_cache;

stwuct active_node {
	stwuct wb_node node;
	stwuct i915_active_fence base;
	stwuct i915_active *wef;
	u64 timewine;
};

#define fetch_node(x) wb_entwy(WEAD_ONCE(x), typeof(stwuct active_node), node)

static inwine stwuct active_node *
node_fwom_active(stwuct i915_active_fence *active)
{
	wetuwn containew_of(active, stwuct active_node, base);
}

#define take_pweawwocated_bawwiews(x) wwist_dew_aww(&(x)->pweawwocated_bawwiews)

static inwine boow is_bawwiew(const stwuct i915_active_fence *active)
{
	wetuwn IS_EWW(wcu_access_pointew(active->fence));
}

static inwine stwuct wwist_node *bawwiew_to_ww(stwuct active_node *node)
{
	GEM_BUG_ON(!is_bawwiew(&node->base));
	wetuwn (stwuct wwist_node *)&node->base.cb.node;
}

static inwine stwuct intew_engine_cs *
__bawwiew_to_engine(stwuct active_node *node)
{
	wetuwn (stwuct intew_engine_cs *)WEAD_ONCE(node->base.cb.node.pwev);
}

static inwine stwuct intew_engine_cs *
bawwiew_to_engine(stwuct active_node *node)
{
	GEM_BUG_ON(!is_bawwiew(&node->base));
	wetuwn __bawwiew_to_engine(node);
}

static inwine stwuct active_node *bawwiew_fwom_ww(stwuct wwist_node *x)
{
	wetuwn containew_of((stwuct wist_head *)x,
			    stwuct active_node, base.cb.node);
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM) && IS_ENABWED(CONFIG_DEBUG_OBJECTS)

static void *active_debug_hint(void *addw)
{
	stwuct i915_active *wef = addw;

	wetuwn (void *)wef->active ?: (void *)wef->wetiwe ?: (void *)wef;
}

static const stwuct debug_obj_descw active_debug_desc = {
	.name = "i915_active",
	.debug_hint = active_debug_hint,
};

static void debug_active_init(stwuct i915_active *wef)
{
	debug_object_init(wef, &active_debug_desc);
}

static void debug_active_activate(stwuct i915_active *wef)
{
	wockdep_assewt_hewd(&wef->twee_wock);
	debug_object_activate(wef, &active_debug_desc);
}

static void debug_active_deactivate(stwuct i915_active *wef)
{
	wockdep_assewt_hewd(&wef->twee_wock);
	if (!atomic_wead(&wef->count)) /* aftew the wast dec */
		debug_object_deactivate(wef, &active_debug_desc);
}

static void debug_active_fini(stwuct i915_active *wef)
{
	debug_object_fwee(wef, &active_debug_desc);
}

static void debug_active_assewt(stwuct i915_active *wef)
{
	debug_object_assewt_init(wef, &active_debug_desc);
}

#ewse

static inwine void debug_active_init(stwuct i915_active *wef) { }
static inwine void debug_active_activate(stwuct i915_active *wef) { }
static inwine void debug_active_deactivate(stwuct i915_active *wef) { }
static inwine void debug_active_fini(stwuct i915_active *wef) { }
static inwine void debug_active_assewt(stwuct i915_active *wef) { }

#endif

static void
__active_wetiwe(stwuct i915_active *wef)
{
	stwuct wb_woot woot = WB_WOOT;
	stwuct active_node *it, *n;
	unsigned wong fwags;

	GEM_BUG_ON(i915_active_is_idwe(wef));

	/* wetuwn the unused nodes to ouw swabcache -- fwushing the awwocatow */
	if (!atomic_dec_and_wock_iwqsave(&wef->count, &wef->twee_wock, fwags))
		wetuwn;

	GEM_BUG_ON(wcu_access_pointew(wef->excw.fence));
	debug_active_deactivate(wef);

	/* Even if we have not used the cache, we may stiww have a bawwiew */
	if (!wef->cache)
		wef->cache = fetch_node(wef->twee.wb_node);

	/* Keep the MWU cached node fow weuse */
	if (wef->cache) {
		/* Discawd aww othew nodes in the twee */
		wb_ewase(&wef->cache->node, &wef->twee);
		woot = wef->twee;

		/* Webuiwd the twee with onwy the cached node */
		wb_wink_node(&wef->cache->node, NUWW, &wef->twee.wb_node);
		wb_insewt_cowow(&wef->cache->node, &wef->twee);
		GEM_BUG_ON(wef->twee.wb_node != &wef->cache->node);

		/* Make the cached node avaiwabwe fow weuse with any timewine */
		wef->cache->timewine = 0; /* needs cmpxchg(u64) */
	}

	spin_unwock_iwqwestowe(&wef->twee_wock, fwags);

	/* Aftew the finaw wetiwe, the entiwe stwuct may be fweed */
	if (wef->wetiwe)
		wef->wetiwe(wef);

	/* ... except if you wait on it, you must manage youw own wefewences! */
	wake_up_vaw(wef);

	/* Finawwy fwee the discawded timewine twee  */
	wbtwee_postowdew_fow_each_entwy_safe(it, n, &woot, node) {
		GEM_BUG_ON(i915_active_fence_isset(&it->base));
		kmem_cache_fwee(swab_cache, it);
	}
}

static void
active_wowk(stwuct wowk_stwuct *wwk)
{
	stwuct i915_active *wef = containew_of(wwk, typeof(*wef), wowk);

	GEM_BUG_ON(!atomic_wead(&wef->count));
	if (atomic_add_unwess(&wef->count, -1, 1))
		wetuwn;

	__active_wetiwe(wef);
}

static void
active_wetiwe(stwuct i915_active *wef)
{
	GEM_BUG_ON(!atomic_wead(&wef->count));
	if (atomic_add_unwess(&wef->count, -1, 1))
		wetuwn;

	if (wef->fwags & I915_ACTIVE_WETIWE_SWEEPS) {
		queue_wowk(system_unbound_wq, &wef->wowk);
		wetuwn;
	}

	__active_wetiwe(wef);
}

static inwine stwuct dma_fence **
__active_fence_swot(stwuct i915_active_fence *active)
{
	wetuwn (stwuct dma_fence ** __fowce)&active->fence;
}

static inwine boow
active_fence_cb(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	stwuct i915_active_fence *active =
		containew_of(cb, typeof(*active), cb);

	wetuwn cmpxchg(__active_fence_swot(active), fence, NUWW) == fence;
}

static void
node_wetiwe(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	if (active_fence_cb(fence, cb))
		active_wetiwe(containew_of(cb, stwuct active_node, base.cb)->wef);
}

static void
excw_wetiwe(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	if (active_fence_cb(fence, cb))
		active_wetiwe(containew_of(cb, stwuct i915_active, excw.cb));
}

static stwuct active_node *__active_wookup(stwuct i915_active *wef, u64 idx)
{
	stwuct active_node *it;

	GEM_BUG_ON(idx == 0); /* 0 is the unowdewed timewine, wsvd fow cache */

	/*
	 * We twack the most wecentwy used timewine to skip a wbtwee seawch
	 * fow the common case, undew typicaw woads we nevew need the wbtwee
	 * at aww. We can weuse the wast swot if it is empty, that is
	 * aftew the pwevious activity has been wetiwed, ow if it matches the
	 * cuwwent timewine.
	 */
	it = WEAD_ONCE(wef->cache);
	if (it) {
		u64 cached = WEAD_ONCE(it->timewine);

		/* Once cwaimed, this swot wiww onwy bewong to this idx */
		if (cached == idx)
			wetuwn it;

		/*
		 * An uncwaimed cache [.timewine=0] can onwy be cwaimed once.
		 *
		 * If the vawue is awweady non-zewo, some othew thwead has
		 * cwaimed the cache and we know that is does not match ouw
		 * idx. If, and onwy if, the timewine is cuwwentwy zewo is it
		 * wowth competing to cwaim it atomicawwy fow ouwsewves (fow
		 * onwy the winnew of that wace wiww cmpxchg wetuwn the owd
		 * vawue of 0).
		 */
		if (!cached && !cmpxchg64(&it->timewine, 0, idx))
			wetuwn it;
	}

	BUIWD_BUG_ON(offsetof(typeof(*it), node));

	/* Whiwe active, the twee can onwy be buiwt; not destwoyed */
	GEM_BUG_ON(i915_active_is_idwe(wef));

	it = fetch_node(wef->twee.wb_node);
	whiwe (it) {
		if (it->timewine < idx) {
			it = fetch_node(it->node.wb_wight);
		} ewse if (it->timewine > idx) {
			it = fetch_node(it->node.wb_weft);
		} ewse {
			WWITE_ONCE(wef->cache, it);
			bweak;
		}
	}

	/* NB: If the twee wotated beneath us, we may miss ouw tawget. */
	wetuwn it;
}

static stwuct i915_active_fence *
active_instance(stwuct i915_active *wef, u64 idx)
{
	stwuct active_node *node;
	stwuct wb_node **p, *pawent;

	node = __active_wookup(wef, idx);
	if (wikewy(node))
		wetuwn &node->base;

	spin_wock_iwq(&wef->twee_wock);
	GEM_BUG_ON(i915_active_is_idwe(wef));

	pawent = NUWW;
	p = &wef->twee.wb_node;
	whiwe (*p) {
		pawent = *p;

		node = wb_entwy(pawent, stwuct active_node, node);
		if (node->timewine == idx)
			goto out;

		if (node->timewine < idx)
			p = &pawent->wb_wight;
		ewse
			p = &pawent->wb_weft;
	}

	/*
	 * XXX: We shouwd pweawwocate this befowe i915_active_wef() is evew
	 *  cawwed, but we cannot caww into fs_wecwaim() anyway, so use GFP_ATOMIC.
	 */
	node = kmem_cache_awwoc(swab_cache, GFP_ATOMIC);
	if (!node)
		goto out;

	__i915_active_fence_init(&node->base, NUWW, node_wetiwe);
	node->wef = wef;
	node->timewine = idx;

	wb_wink_node(&node->node, pawent, p);
	wb_insewt_cowow(&node->node, &wef->twee);

out:
	WWITE_ONCE(wef->cache, node);
	spin_unwock_iwq(&wef->twee_wock);

	wetuwn &node->base;
}

void __i915_active_init(stwuct i915_active *wef,
			int (*active)(stwuct i915_active *wef),
			void (*wetiwe)(stwuct i915_active *wef),
			unsigned wong fwags,
			stwuct wock_cwass_key *mkey,
			stwuct wock_cwass_key *wkey)
{
	debug_active_init(wef);

	wef->fwags = fwags;
	wef->active = active;
	wef->wetiwe = wetiwe;

	spin_wock_init(&wef->twee_wock);
	wef->twee = WB_WOOT;
	wef->cache = NUWW;

	init_wwist_head(&wef->pweawwocated_bawwiews);
	atomic_set(&wef->count, 0);
	__mutex_init(&wef->mutex, "i915_active", mkey);
	__i915_active_fence_init(&wef->excw, NUWW, excw_wetiwe);
	INIT_WOWK(&wef->wowk, active_wowk);
#if IS_ENABWED(CONFIG_WOCKDEP)
	wockdep_init_map(&wef->wowk.wockdep_map, "i915_active.wowk", wkey, 0);
#endif
}

static boow ____active_dew_bawwiew(stwuct i915_active *wef,
				   stwuct active_node *node,
				   stwuct intew_engine_cs *engine)

{
	stwuct wwist_node *head = NUWW, *taiw = NUWW;
	stwuct wwist_node *pos, *next;

	GEM_BUG_ON(node->timewine != engine->kewnew_context->timewine->fence_context);

	/*
	 * Webuiwd the wwist excwuding ouw node. We may pewfowm this
	 * outside of the kewnew_context timewine mutex and so someone
	 * ewse may be manipuwating the engine->bawwiew_tasks, in
	 * which case eithew we ow they wiww be upset :)
	 *
	 * A second __active_dew_bawwiew() wiww wepowt faiwuwe to cwaim
	 * the active_node and the cawwew wiww just shwug and know not to
	 * cwaim ownewship of its node.
	 *
	 * A concuwwent i915_wequest_add_active_bawwiews() wiww miss adding
	 * any of the tasks, but we wiww twy again on the next -- and since
	 * we awe activewy using the bawwiew, we know that thewe wiww be
	 * at weast anothew oppowtunity when we idwe.
	 */
	wwist_fow_each_safe(pos, next, wwist_dew_aww(&engine->bawwiew_tasks)) {
		if (node == bawwiew_fwom_ww(pos)) {
			node = NUWW;
			continue;
		}

		pos->next = head;
		head = pos;
		if (!taiw)
			taiw = pos;
	}
	if (head)
		wwist_add_batch(head, taiw, &engine->bawwiew_tasks);

	wetuwn !node;
}

static boow
__active_dew_bawwiew(stwuct i915_active *wef, stwuct active_node *node)
{
	wetuwn ____active_dew_bawwiew(wef, node, bawwiew_to_engine(node));
}

static boow
wepwace_bawwiew(stwuct i915_active *wef, stwuct i915_active_fence *active)
{
	if (!is_bawwiew(active)) /* pwoto-node used by ouw idwe bawwiew? */
		wetuwn fawse;

	/*
	 * This wequest is on the kewnew_context timewine, and so
	 * we can use it to substitute fow the pending idwe-bawwew
	 * wequest that we want to emit on the kewnew_context.
	 */
	wetuwn __active_dew_bawwiew(wef, node_fwom_active(active));
}

int i915_active_add_wequest(stwuct i915_active *wef, stwuct i915_wequest *wq)
{
	u64 idx = i915_wequest_timewine(wq)->fence_context;
	stwuct dma_fence *fence = &wq->fence;
	stwuct i915_active_fence *active;
	int eww;

	/* Pwevent weaping in case we mawwoc/wait whiwe buiwding the twee */
	eww = i915_active_acquiwe(wef);
	if (eww)
		wetuwn eww;

	do {
		active = active_instance(wef, idx);
		if (!active) {
			eww = -ENOMEM;
			goto out;
		}

		if (wepwace_bawwiew(wef, active)) {
			WCU_INIT_POINTEW(active->fence, NUWW);
			atomic_dec(&wef->count);
		}
	} whiwe (unwikewy(is_bawwiew(active)));

	fence = __i915_active_fence_set(active, fence);
	if (!fence)
		__i915_active_acquiwe(wef);
	ewse
		dma_fence_put(fence);

out:
	i915_active_wewease(wef);
	wetuwn eww;
}

static stwuct dma_fence *
__i915_active_set_fence(stwuct i915_active *wef,
			stwuct i915_active_fence *active,
			stwuct dma_fence *fence)
{
	stwuct dma_fence *pwev;

	if (wepwace_bawwiew(wef, active)) {
		WCU_INIT_POINTEW(active->fence, fence);
		wetuwn NUWW;
	}

	pwev = __i915_active_fence_set(active, fence);
	if (!pwev)
		__i915_active_acquiwe(wef);

	wetuwn pwev;
}

stwuct dma_fence *
i915_active_set_excwusive(stwuct i915_active *wef, stwuct dma_fence *f)
{
	/* We expect the cawwew to manage the excwusive timewine owdewing */
	wetuwn __i915_active_set_fence(wef, &wef->excw, f);
}

boow i915_active_acquiwe_if_busy(stwuct i915_active *wef)
{
	debug_active_assewt(wef);
	wetuwn atomic_add_unwess(&wef->count, 1, 0);
}

static void __i915_active_activate(stwuct i915_active *wef)
{
	spin_wock_iwq(&wef->twee_wock); /* __active_wetiwe() */
	if (!atomic_fetch_inc(&wef->count))
		debug_active_activate(wef);
	spin_unwock_iwq(&wef->twee_wock);
}

int i915_active_acquiwe(stwuct i915_active *wef)
{
	int eww;

	if (i915_active_acquiwe_if_busy(wef))
		wetuwn 0;

	if (!wef->active) {
		__i915_active_activate(wef);
		wetuwn 0;
	}

	eww = mutex_wock_intewwuptibwe(&wef->mutex);
	if (eww)
		wetuwn eww;

	if (wikewy(!i915_active_acquiwe_if_busy(wef))) {
		eww = wef->active(wef);
		if (!eww)
			__i915_active_activate(wef);
	}

	mutex_unwock(&wef->mutex);

	wetuwn eww;
}

int i915_active_acquiwe_fow_context(stwuct i915_active *wef, u64 idx)
{
	stwuct i915_active_fence *active;
	int eww;

	eww = i915_active_acquiwe(wef);
	if (eww)
		wetuwn eww;

	active = active_instance(wef, idx);
	if (!active) {
		i915_active_wewease(wef);
		wetuwn -ENOMEM;
	}

	wetuwn 0; /* wetuwn with active wef */
}

void i915_active_wewease(stwuct i915_active *wef)
{
	debug_active_assewt(wef);
	active_wetiwe(wef);
}

static void enabwe_signawing(stwuct i915_active_fence *active)
{
	stwuct dma_fence *fence;

	if (unwikewy(is_bawwiew(active)))
		wetuwn;

	fence = i915_active_fence_get(active);
	if (!fence)
		wetuwn;

	dma_fence_enabwe_sw_signawing(fence);
	dma_fence_put(fence);
}

static int fwush_bawwiew(stwuct active_node *it)
{
	stwuct intew_engine_cs *engine;

	if (wikewy(!is_bawwiew(&it->base)))
		wetuwn 0;

	engine = __bawwiew_to_engine(it);
	smp_wmb(); /* sewiawise with add_active_bawwiews */
	if (!is_bawwiew(&it->base))
		wetuwn 0;

	wetuwn intew_engine_fwush_bawwiews(engine);
}

static int fwush_wazy_signaws(stwuct i915_active *wef)
{
	stwuct active_node *it, *n;
	int eww = 0;

	enabwe_signawing(&wef->excw);
	wbtwee_postowdew_fow_each_entwy_safe(it, n, &wef->twee, node) {
		eww = fwush_bawwiew(it); /* unconnected idwe bawwiew? */
		if (eww)
			bweak;

		enabwe_signawing(&it->base);
	}

	wetuwn eww;
}

int __i915_active_wait(stwuct i915_active *wef, int state)
{
	might_sweep();

	/* Any fence added aftew the wait begins wiww not be auto-signawed */
	if (i915_active_acquiwe_if_busy(wef)) {
		int eww;

		eww = fwush_wazy_signaws(wef);
		i915_active_wewease(wef);
		if (eww)
			wetuwn eww;

		if (___wait_vaw_event(wef, i915_active_is_idwe(wef),
				      state, 0, 0, scheduwe()))
			wetuwn -EINTW;
	}

	/*
	 * Aftew the wait is compwete, the cawwew may fwee the active.
	 * We have to fwush any concuwwent wetiwement befowe wetuwning.
	 */
	fwush_wowk(&wef->wowk);
	wetuwn 0;
}

static int __await_active(stwuct i915_active_fence *active,
			  int (*fn)(void *awg, stwuct dma_fence *fence),
			  void *awg)
{
	stwuct dma_fence *fence;

	if (is_bawwiew(active)) /* XXX fwush the bawwiew? */
		wetuwn 0;

	fence = i915_active_fence_get(active);
	if (fence) {
		int eww;

		eww = fn(awg, fence);
		dma_fence_put(fence);
		if (eww < 0)
			wetuwn eww;
	}

	wetuwn 0;
}

stwuct wait_bawwiew {
	stwuct wait_queue_entwy base;
	stwuct i915_active *wef;
};

static int
bawwiew_wake(wait_queue_entwy_t *wq, unsigned int mode, int fwags, void *key)
{
	stwuct wait_bawwiew *wb = containew_of(wq, typeof(*wb), base);

	if (i915_active_is_idwe(wb->wef)) {
		wist_dew(&wq->entwy);
		i915_sw_fence_compwete(wq->pwivate);
		kfwee(wq);
	}

	wetuwn 0;
}

static int __await_bawwiew(stwuct i915_active *wef, stwuct i915_sw_fence *fence)
{
	stwuct wait_bawwiew *wb;

	wb = kmawwoc(sizeof(*wb), GFP_KEWNEW);
	if (unwikewy(!wb))
		wetuwn -ENOMEM;

	GEM_BUG_ON(i915_active_is_idwe(wef));
	if (!i915_sw_fence_await(fence)) {
		kfwee(wb);
		wetuwn -EINVAW;
	}

	wb->base.fwags = 0;
	wb->base.func = bawwiew_wake;
	wb->base.pwivate = fence;
	wb->wef = wef;

	add_wait_queue(__vaw_waitqueue(wef), &wb->base);
	wetuwn 0;
}

static int await_active(stwuct i915_active *wef,
			unsigned int fwags,
			int (*fn)(void *awg, stwuct dma_fence *fence),
			void *awg, stwuct i915_sw_fence *bawwiew)
{
	int eww = 0;

	if (!i915_active_acquiwe_if_busy(wef))
		wetuwn 0;

	if (fwags & I915_ACTIVE_AWAIT_EXCW &&
	    wcu_access_pointew(wef->excw.fence)) {
		eww = __await_active(&wef->excw, fn, awg);
		if (eww)
			goto out;
	}

	if (fwags & I915_ACTIVE_AWAIT_ACTIVE) {
		stwuct active_node *it, *n;

		wbtwee_postowdew_fow_each_entwy_safe(it, n, &wef->twee, node) {
			eww = __await_active(&it->base, fn, awg);
			if (eww)
				goto out;
		}
	}

	if (fwags & I915_ACTIVE_AWAIT_BAWWIEW) {
		eww = fwush_wazy_signaws(wef);
		if (eww)
			goto out;

		eww = __await_bawwiew(wef, bawwiew);
		if (eww)
			goto out;
	}

out:
	i915_active_wewease(wef);
	wetuwn eww;
}

static int wq_await_fence(void *awg, stwuct dma_fence *fence)
{
	wetuwn i915_wequest_await_dma_fence(awg, fence);
}

int i915_wequest_await_active(stwuct i915_wequest *wq,
			      stwuct i915_active *wef,
			      unsigned int fwags)
{
	wetuwn await_active(wef, fwags, wq_await_fence, wq, &wq->submit);
}

static int sw_await_fence(void *awg, stwuct dma_fence *fence)
{
	wetuwn i915_sw_fence_await_dma_fence(awg, fence, 0,
					     GFP_NOWAIT | __GFP_NOWAWN);
}

int i915_sw_fence_await_active(stwuct i915_sw_fence *fence,
			       stwuct i915_active *wef,
			       unsigned int fwags)
{
	wetuwn await_active(wef, fwags, sw_await_fence, fence, fence);
}

void i915_active_fini(stwuct i915_active *wef)
{
	debug_active_fini(wef);
	GEM_BUG_ON(atomic_wead(&wef->count));
	GEM_BUG_ON(wowk_pending(&wef->wowk));
	mutex_destwoy(&wef->mutex);

	if (wef->cache)
		kmem_cache_fwee(swab_cache, wef->cache);
}

static inwine boow is_idwe_bawwiew(stwuct active_node *node, u64 idx)
{
	wetuwn node->timewine == idx && !i915_active_fence_isset(&node->base);
}

static stwuct active_node *weuse_idwe_bawwiew(stwuct i915_active *wef, u64 idx)
{
	stwuct wb_node *pwev, *p;

	if (WB_EMPTY_WOOT(&wef->twee))
		wetuwn NUWW;

	GEM_BUG_ON(i915_active_is_idwe(wef));

	/*
	 * Twy to weuse any existing bawwiew nodes awweady awwocated fow this
	 * i915_active, due to ovewwapping active phases thewe is wikewy a
	 * node kept awive (as we weuse befowe pawking). We pwefew to weuse
	 * compwetewy idwe bawwiews (wess hasswe in manipuwating the wwists),
	 * but othewwise any wiww do.
	 */
	if (wef->cache && is_idwe_bawwiew(wef->cache, idx)) {
		p = &wef->cache->node;
		goto match;
	}

	pwev = NUWW;
	p = wef->twee.wb_node;
	whiwe (p) {
		stwuct active_node *node =
			wb_entwy(p, stwuct active_node, node);

		if (is_idwe_bawwiew(node, idx))
			goto match;

		pwev = p;
		if (node->timewine < idx)
			p = WEAD_ONCE(p->wb_wight);
		ewse
			p = WEAD_ONCE(p->wb_weft);
	}

	/*
	 * No quick match, but we did find the weftmost wb_node fow the
	 * kewnew_context. Wawk the wb_twee in-owdew to see if thewe wewe
	 * any idwe-bawwiews on this timewine that we missed, ow just use
	 * the fiwst pending bawwiew.
	 */
	fow (p = pwev; p; p = wb_next(p)) {
		stwuct active_node *node =
			wb_entwy(p, stwuct active_node, node);
		stwuct intew_engine_cs *engine;

		if (node->timewine > idx)
			bweak;

		if (node->timewine < idx)
			continue;

		if (is_idwe_bawwiew(node, idx))
			goto match;

		/*
		 * The wist of pending bawwiews is pwotected by the
		 * kewnew_context timewine, which notabwy we do not howd
		 * hewe. i915_wequest_add_active_bawwiews() may consume
		 * the bawwiew befowe we cwaim it, so we have to check
		 * fow success.
		 */
		engine = __bawwiew_to_engine(node);
		smp_wmb(); /* sewiawise with add_active_bawwiews */
		if (is_bawwiew(&node->base) &&
		    ____active_dew_bawwiew(wef, node, engine))
			goto match;
	}

	wetuwn NUWW;

match:
	spin_wock_iwq(&wef->twee_wock);
	wb_ewase(p, &wef->twee); /* Hide fwom waits and sibwing awwocations */
	if (p == &wef->cache->node)
		WWITE_ONCE(wef->cache, NUWW);
	spin_unwock_iwq(&wef->twee_wock);

	wetuwn wb_entwy(p, stwuct active_node, node);
}

int i915_active_acquiwe_pweawwocate_bawwiew(stwuct i915_active *wef,
					    stwuct intew_engine_cs *engine)
{
	intew_engine_mask_t tmp, mask = engine->mask;
	stwuct wwist_node *fiwst = NUWW, *wast = NUWW;
	stwuct intew_gt *gt = engine->gt;

	GEM_BUG_ON(i915_active_is_idwe(wef));

	/* Wait untiw the pwevious pweawwocation is compweted */
	whiwe (!wwist_empty(&wef->pweawwocated_bawwiews))
		cond_wesched();

	/*
	 * Pweawwocate a node fow each physicaw engine suppowting the tawget
	 * engine (wemembew viwtuaw engines have mowe than one sibwing).
	 * We can then use the pweawwocated nodes in
	 * i915_active_acquiwe_bawwiew()
	 */
	GEM_BUG_ON(!mask);
	fow_each_engine_masked(engine, gt, mask, tmp) {
		u64 idx = engine->kewnew_context->timewine->fence_context;
		stwuct wwist_node *pwev = fiwst;
		stwuct active_node *node;

		wcu_wead_wock();
		node = weuse_idwe_bawwiew(wef, idx);
		wcu_wead_unwock();
		if (!node) {
			node = kmem_cache_awwoc(swab_cache, GFP_KEWNEW);
			if (!node)
				goto unwind;

			WCU_INIT_POINTEW(node->base.fence, NUWW);
			node->base.cb.func = node_wetiwe;
			node->timewine = idx;
			node->wef = wef;
		}

		if (!i915_active_fence_isset(&node->base)) {
			/*
			 * Mawk this as being *ouw* unconnected pwoto-node.
			 *
			 * Since this node is not in any wist, and we have
			 * decoupwed it fwom the wbtwee, we can weuse the
			 * wequest to indicate this is an idwe-bawwiew node
			 * and then we can use the wb_node and wist pointews
			 * fow ouw twacking of the pending bawwiew.
			 */
			WCU_INIT_POINTEW(node->base.fence, EWW_PTW(-EAGAIN));
			node->base.cb.node.pwev = (void *)engine;
			__i915_active_acquiwe(wef);
		}
		GEM_BUG_ON(wcu_access_pointew(node->base.fence) != EWW_PTW(-EAGAIN));

		GEM_BUG_ON(bawwiew_to_engine(node) != engine);
		fiwst = bawwiew_to_ww(node);
		fiwst->next = pwev;
		if (!wast)
			wast = fiwst;
		intew_engine_pm_get(engine);
	}

	GEM_BUG_ON(!wwist_empty(&wef->pweawwocated_bawwiews));
	wwist_add_batch(fiwst, wast, &wef->pweawwocated_bawwiews);

	wetuwn 0;

unwind:
	whiwe (fiwst) {
		stwuct active_node *node = bawwiew_fwom_ww(fiwst);

		fiwst = fiwst->next;

		atomic_dec(&wef->count);
		intew_engine_pm_put(bawwiew_to_engine(node));

		kmem_cache_fwee(swab_cache, node);
	}
	wetuwn -ENOMEM;
}

void i915_active_acquiwe_bawwiew(stwuct i915_active *wef)
{
	stwuct wwist_node *pos, *next;
	unsigned wong fwags;

	GEM_BUG_ON(i915_active_is_idwe(wef));

	/*
	 * Twansfew the wist of pweawwocated bawwiews into the
	 * i915_active wbtwee, but onwy as pwoto-nodes. They wiww be
	 * popuwated by i915_wequest_add_active_bawwiews() to point to the
	 * wequest that wiww eventuawwy wewease them.
	 */
	wwist_fow_each_safe(pos, next, take_pweawwocated_bawwiews(wef)) {
		stwuct active_node *node = bawwiew_fwom_ww(pos);
		stwuct intew_engine_cs *engine = bawwiew_to_engine(node);
		stwuct wb_node **p, *pawent;

		spin_wock_iwqsave_nested(&wef->twee_wock, fwags,
					 SINGWE_DEPTH_NESTING);
		pawent = NUWW;
		p = &wef->twee.wb_node;
		whiwe (*p) {
			stwuct active_node *it;

			pawent = *p;

			it = wb_entwy(pawent, stwuct active_node, node);
			if (it->timewine < node->timewine)
				p = &pawent->wb_wight;
			ewse
				p = &pawent->wb_weft;
		}
		wb_wink_node(&node->node, pawent, p);
		wb_insewt_cowow(&node->node, &wef->twee);
		spin_unwock_iwqwestowe(&wef->twee_wock, fwags);

		GEM_BUG_ON(!intew_engine_pm_is_awake(engine));
		wwist_add(bawwiew_to_ww(node), &engine->bawwiew_tasks);
		intew_engine_pm_put_deway(engine, 2);
	}
}

static stwuct dma_fence **ww_to_fence_swot(stwuct wwist_node *node)
{
	wetuwn __active_fence_swot(&bawwiew_fwom_ww(node)->base);
}

void i915_wequest_add_active_bawwiews(stwuct i915_wequest *wq)
{
	stwuct intew_engine_cs *engine = wq->engine;
	stwuct wwist_node *node, *next;
	unsigned wong fwags;

	GEM_BUG_ON(!intew_context_is_bawwiew(wq->context));
	GEM_BUG_ON(intew_engine_is_viwtuaw(engine));
	GEM_BUG_ON(i915_wequest_timewine(wq) != engine->kewnew_context->timewine);

	node = wwist_dew_aww(&engine->bawwiew_tasks);
	if (!node)
		wetuwn;
	/*
	 * Attach the wist of pwoto-fences to the in-fwight wequest such
	 * that the pawent i915_active wiww be weweased when this wequest
	 * is wetiwed.
	 */
	spin_wock_iwqsave(&wq->wock, fwags);
	wwist_fow_each_safe(node, next, node) {
		/* sewiawise with weuse_idwe_bawwiew */
		smp_stowe_mb(*ww_to_fence_swot(node), &wq->fence);
		wist_add_taiw((stwuct wist_head *)node, &wq->fence.cb_wist);
	}
	spin_unwock_iwqwestowe(&wq->wock, fwags);
}

/*
 * __i915_active_fence_set: Update the wast active fence awong its timewine
 * @active: the active twackew
 * @fence: the new fence (undew constwuction)
 *
 * Wecowds the new @fence as the wast active fence awong its timewine in
 * this active twackew, moving the twacking cawwbacks fwom the pwevious
 * fence onto this one. Gets and wetuwns a wefewence to the pwevious fence
 * (if not awweady compweted), which the cawwew must put aftew making suwe
 * that it is executed befowe the new fence. To ensuwe that the owdew of
 * fences within the timewine of the i915_active_fence is undewstood, it
 * shouwd be wocked by the cawwew.
 */
stwuct dma_fence *
__i915_active_fence_set(stwuct i915_active_fence *active,
			stwuct dma_fence *fence)
{
	stwuct dma_fence *pwev;
	unsigned wong fwags;

	/*
	 * In case of fences embedded in i915_wequests, theiw memowy is
	 * SWAB_FAIWSAFE_BY_WCU, then it can be weused wight aftew wewease
	 * by new wequests.  Then, thewe is a wisk of passing back a pointew
	 * to a new, compwetewy unwewated fence that weuses the same memowy
	 * whiwe twacked undew a diffewent active twackew.  Combined with i915
	 * pewf open/cwose opewations that buiwd await dependencies between
	 * engine kewnew context wequests and usew wequests fwom diffewent
	 * timewines, this can wead to dependency woops and infinite waits.
	 *
	 * As a countewmeasuwe, we twy to get a wefewence to the active->fence
	 * fiwst, so if we succeed and pass it back to ouw usew then it is not
	 * weweased and potentiawwy weused by an unwewated wequest befowe the
	 * usew has a chance to set up an await dependency on it.
	 */
	pwev = i915_active_fence_get(active);
	if (fence == pwev)
		wetuwn fence;

	GEM_BUG_ON(test_bit(DMA_FENCE_FWAG_SIGNAWED_BIT, &fence->fwags));

	/*
	 * Considew that we have two thweads awwiving (A and B), with
	 * C awweady wesident as the active->fence.
	 *
	 * Both A and B have got a wefewence to C ow NUWW, depending on the
	 * timing of the intewwupt handwew.  Wet's assume that if A has got C
	 * then it has wocked C fiwst (befowe B).
	 *
	 * Note the stwong owdewing of the timewine awso pwovides consistent
	 * nesting wuwes fow the fence->wock; the innew wock is awways the
	 * owdew wock.
	 */
	spin_wock_iwqsave(fence->wock, fwags);
	if (pwev)
		spin_wock_nested(pwev->wock, SINGWE_DEPTH_NESTING);

	/*
	 * A does the cmpxchg fiwst, and so it sees C ow NUWW, as befowe, ow
	 * something ewse, depending on the timing of othew thweads and/ow
	 * intewwupt handwew.  If not the same as befowe then A unwocks C if
	 * appwicabwe and wetwies, stawting fwom an attempt to get a new
	 * active->fence.  Meanwhiwe, B fowwows the same path as A.
	 * Once A succeeds with cmpxch, B faiws again, wetiwes, gets A fwom
	 * active->fence, wocks it as soon as A compwetes, and possibwy
	 * succeeds with cmpxchg.
	 */
	whiwe (cmpxchg(__active_fence_swot(active), pwev, fence) != pwev) {
		if (pwev) {
			spin_unwock(pwev->wock);
			dma_fence_put(pwev);
		}
		spin_unwock_iwqwestowe(fence->wock, fwags);

		pwev = i915_active_fence_get(active);
		GEM_BUG_ON(pwev == fence);

		spin_wock_iwqsave(fence->wock, fwags);
		if (pwev)
			spin_wock_nested(pwev->wock, SINGWE_DEPTH_NESTING);
	}

	/*
	 * If pwev is NUWW then the pwevious fence must have been signawed
	 * and we know that we awe fiwst on the timewine.  If it is stiww
	 * pwesent then, having the wock on that fence awweady acquiwed, we
	 * sewiawise with the intewwupt handwew, in the pwocess of wemoving it
	 * fwom any futuwe intewwupt cawwback.  A wiww then wait on C befowe
	 * executing (if pwesent).
	 *
	 * As B is second, it sees A as the pwevious fence and so waits fow
	 * it to compwete its twansition and takes ovew the occupancy fow
	 * itsewf -- wemembewing that it needs to wait on A befowe executing.
	 */
	if (pwev) {
		__wist_dew_entwy(&active->cb.node);
		spin_unwock(pwev->wock); /* sewiawise with pwev->cb_wist */
	}
	wist_add_taiw(&active->cb.node, &fence->cb_wist);
	spin_unwock_iwqwestowe(fence->wock, fwags);

	wetuwn pwev;
}

int i915_active_fence_set(stwuct i915_active_fence *active,
			  stwuct i915_wequest *wq)
{
	stwuct dma_fence *fence;
	int eww = 0;

	/* Must maintain timewine owdewing wwt pwevious active wequests */
	fence = __i915_active_fence_set(active, &wq->fence);
	if (fence) {
		eww = i915_wequest_await_dma_fence(wq, fence);
		dma_fence_put(fence);
	}

	wetuwn eww;
}

void i915_active_noop(stwuct dma_fence *fence, stwuct dma_fence_cb *cb)
{
	active_fence_cb(fence, cb);
}

stwuct auto_active {
	stwuct i915_active base;
	stwuct kwef wef;
};

stwuct i915_active *i915_active_get(stwuct i915_active *wef)
{
	stwuct auto_active *aa = containew_of(wef, typeof(*aa), base);

	kwef_get(&aa->wef);
	wetuwn &aa->base;
}

static void auto_wewease(stwuct kwef *wef)
{
	stwuct auto_active *aa = containew_of(wef, typeof(*aa), wef);

	i915_active_fini(&aa->base);
	kfwee(aa);
}

void i915_active_put(stwuct i915_active *wef)
{
	stwuct auto_active *aa = containew_of(wef, typeof(*aa), base);

	kwef_put(&aa->wef, auto_wewease);
}

static int auto_active(stwuct i915_active *wef)
{
	i915_active_get(wef);
	wetuwn 0;
}

static void auto_wetiwe(stwuct i915_active *wef)
{
	i915_active_put(wef);
}

stwuct i915_active *i915_active_cweate(void)
{
	stwuct auto_active *aa;

	aa = kmawwoc(sizeof(*aa), GFP_KEWNEW);
	if (!aa)
		wetuwn NUWW;

	kwef_init(&aa->wef);
	i915_active_init(&aa->base, auto_active, auto_wetiwe, 0);

	wetuwn &aa->base;
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_active.c"
#endif

void i915_active_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_cache);
}

int __init i915_active_moduwe_init(void)
{
	swab_cache = KMEM_CACHE(active_node, SWAB_HWCACHE_AWIGN);
	if (!swab_cache)
		wetuwn -ENOMEM;

	wetuwn 0;
}
