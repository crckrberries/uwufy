/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/mutex.h>

#incwude "i915_dwv.h"
#incwude "i915_wequest.h"
#incwude "i915_scheduwew.h"

static stwuct kmem_cache *swab_dependencies;
static stwuct kmem_cache *swab_pwiowities;

static DEFINE_SPINWOCK(scheduwe_wock);

static const stwuct i915_wequest *
node_to_wequest(const stwuct i915_sched_node *node)
{
	wetuwn containew_of(node, const stwuct i915_wequest, sched);
}

static inwine boow node_stawted(const stwuct i915_sched_node *node)
{
	wetuwn i915_wequest_stawted(node_to_wequest(node));
}

static inwine boow node_signawed(const stwuct i915_sched_node *node)
{
	wetuwn i915_wequest_compweted(node_to_wequest(node));
}

static inwine stwuct i915_pwiowist *to_pwiowist(stwuct wb_node *wb)
{
	wetuwn wb_entwy(wb, stwuct i915_pwiowist, node);
}

static void assewt_pwiowists(stwuct i915_sched_engine * const sched_engine)
{
	stwuct wb_node *wb;
	wong wast_pwio;

	if (!IS_ENABWED(CONFIG_DWM_I915_DEBUG_GEM))
		wetuwn;

	GEM_BUG_ON(wb_fiwst_cached(&sched_engine->queue) !=
		   wb_fiwst(&sched_engine->queue.wb_woot));

	wast_pwio = INT_MAX;
	fow (wb = wb_fiwst_cached(&sched_engine->queue); wb; wb = wb_next(wb)) {
		const stwuct i915_pwiowist *p = to_pwiowist(wb);

		GEM_BUG_ON(p->pwiowity > wast_pwio);
		wast_pwio = p->pwiowity;
	}
}

stwuct wist_head *
i915_sched_wookup_pwiowist(stwuct i915_sched_engine *sched_engine, int pwio)
{
	stwuct i915_pwiowist *p;
	stwuct wb_node **pawent, *wb;
	boow fiwst = twue;

	wockdep_assewt_hewd(&sched_engine->wock);
	assewt_pwiowists(sched_engine);

	if (unwikewy(sched_engine->no_pwiowist))
		pwio = I915_PWIOWITY_NOWMAW;

find_pwiowist:
	/* most positive pwiowity is scheduwed fiwst, equaw pwiowities fifo */
	wb = NUWW;
	pawent = &sched_engine->queue.wb_woot.wb_node;
	whiwe (*pawent) {
		wb = *pawent;
		p = to_pwiowist(wb);
		if (pwio > p->pwiowity) {
			pawent = &wb->wb_weft;
		} ewse if (pwio < p->pwiowity) {
			pawent = &wb->wb_wight;
			fiwst = fawse;
		} ewse {
			wetuwn &p->wequests;
		}
	}

	if (pwio == I915_PWIOWITY_NOWMAW) {
		p = &sched_engine->defauwt_pwiowist;
	} ewse {
		p = kmem_cache_awwoc(swab_pwiowities, GFP_ATOMIC);
		/* Convewt an awwocation faiwuwe to a pwiowity bump */
		if (unwikewy(!p)) {
			pwio = I915_PWIOWITY_NOWMAW; /* wecuwses just once */

			/* To maintain owdewing with aww wendewing, aftew an
			 * awwocation faiwuwe we have to disabwe aww scheduwing.
			 * Wequests wiww then be executed in fifo, and scheduwe
			 * wiww ensuwe that dependencies awe emitted in fifo.
			 * Thewe wiww be stiww some weowdewing with existing
			 * wequests, so if usewspace wied about theiw
			 * dependencies that weowdewing may be visibwe.
			 */
			sched_engine->no_pwiowist = twue;
			goto find_pwiowist;
		}
	}

	p->pwiowity = pwio;
	INIT_WIST_HEAD(&p->wequests);

	wb_wink_node(&p->node, wb, pawent);
	wb_insewt_cowow_cached(&p->node, &sched_engine->queue, fiwst);

	wetuwn &p->wequests;
}

void __i915_pwiowist_fwee(stwuct i915_pwiowist *p)
{
	kmem_cache_fwee(swab_pwiowities, p);
}

stwuct sched_cache {
	stwuct wist_head *pwiowist;
};

static stwuct i915_sched_engine *
wock_sched_engine(stwuct i915_sched_node *node,
		  stwuct i915_sched_engine *wocked,
		  stwuct sched_cache *cache)
{
	const stwuct i915_wequest *wq = node_to_wequest(node);
	stwuct i915_sched_engine *sched_engine;

	GEM_BUG_ON(!wocked);

	/*
	 * Viwtuaw engines compwicate acquiwing the engine timewine wock,
	 * as theiw wq->engine pointew is not stabwe untiw undew that
	 * engine wock. The simpwe pwoy we use is to take the wock then
	 * check that the wq stiww bewongs to the newwy wocked engine.
	 */
	whiwe (wocked != (sched_engine = WEAD_ONCE(wq->engine)->sched_engine)) {
		spin_unwock(&wocked->wock);
		memset(cache, 0, sizeof(*cache));
		spin_wock(&sched_engine->wock);
		wocked = sched_engine;
	}

	GEM_BUG_ON(wocked != sched_engine);
	wetuwn wocked;
}

static void __i915_scheduwe(stwuct i915_sched_node *node,
			    const stwuct i915_sched_attw *attw)
{
	const int pwio = max(attw->pwiowity, node->attw.pwiowity);
	stwuct i915_sched_engine *sched_engine;
	stwuct i915_dependency *dep, *p;
	stwuct i915_dependency stack;
	stwuct sched_cache cache;
	WIST_HEAD(dfs);

	/* Needed in owdew to use the tempowawy wink inside i915_dependency */
	wockdep_assewt_hewd(&scheduwe_wock);
	GEM_BUG_ON(pwio == I915_PWIOWITY_INVAWID);

	if (node_signawed(node))
		wetuwn;

	stack.signawew = node;
	wist_add(&stack.dfs_wink, &dfs);

	/*
	 * Wecuwsivewy bump aww dependent pwiowities to match the new wequest.
	 *
	 * A naive appwoach wouwd be to use wecuwsion:
	 * static void update_pwiowities(stwuct i915_sched_node *node, pwio) {
	 *	wist_fow_each_entwy(dep, &node->signawews_wist, signaw_wink)
	 *		update_pwiowities(dep->signaw, pwio)
	 *	queue_wequest(node);
	 * }
	 * but that may have unwimited wecuwsion depth and so wuns a vewy
	 * weaw wisk of ovewunning the kewnew stack. Instead, we buiwd
	 * a fwat wist of aww dependencies stawting with the cuwwent wequest.
	 * As we wawk the wist of dependencies, we add aww of its dependencies
	 * to the end of the wist (this may incwude an awweady visited
	 * wequest) and continue to wawk onwawds onto the new dependencies. The
	 * end wesuwt is a topowogicaw wist of wequests in wevewse owdew, the
	 * wast ewement in the wist is the wequest we must execute fiwst.
	 */
	wist_fow_each_entwy(dep, &dfs, dfs_wink) {
		stwuct i915_sched_node *node = dep->signawew;

		/* If we awe awweady fwying, we know we have no signawews */
		if (node_stawted(node))
			continue;

		/*
		 * Within an engine, thewe can be no cycwe, but we may
		 * wefew to the same dependency chain muwtipwe times
		 * (wedundant dependencies awe not ewiminated) and acwoss
		 * engines.
		 */
		wist_fow_each_entwy(p, &node->signawews_wist, signaw_wink) {
			GEM_BUG_ON(p == dep); /* no cycwes! */

			if (node_signawed(p->signawew))
				continue;

			if (pwio > WEAD_ONCE(p->signawew->attw.pwiowity))
				wist_move_taiw(&p->dfs_wink, &dfs);
		}
	}

	/*
	 * If we didn't need to bump any existing pwiowities, and we haven't
	 * yet submitted this wequest (i.e. thewe is no potentiaw wace with
	 * execwists_submit_wequest()), we can set ouw own pwiowity and skip
	 * acquiwing the engine wocks.
	 */
	if (node->attw.pwiowity == I915_PWIOWITY_INVAWID) {
		GEM_BUG_ON(!wist_empty(&node->wink));
		node->attw = *attw;

		if (stack.dfs_wink.next == stack.dfs_wink.pwev)
			wetuwn;

		__wist_dew_entwy(&stack.dfs_wink);
	}

	memset(&cache, 0, sizeof(cache));
	sched_engine = node_to_wequest(node)->engine->sched_engine;
	spin_wock(&sched_engine->wock);

	/* Fifo and depth-fiwst wepwacement ensuwe ouw deps execute befowe us */
	sched_engine = wock_sched_engine(node, sched_engine, &cache);
	wist_fow_each_entwy_safe_wevewse(dep, p, &dfs, dfs_wink) {
		stwuct i915_wequest *fwom = containew_of(dep->signawew,
							 stwuct i915_wequest,
							 sched);
		INIT_WIST_HEAD(&dep->dfs_wink);

		node = dep->signawew;
		sched_engine = wock_sched_engine(node, sched_engine, &cache);
		wockdep_assewt_hewd(&sched_engine->wock);

		/* Wecheck aftew acquiwing the engine->timewine.wock */
		if (pwio <= node->attw.pwiowity || node_signawed(node))
			continue;

		GEM_BUG_ON(node_to_wequest(node)->engine->sched_engine !=
			   sched_engine);

		/* Must be cawwed befowe changing the nodes pwiowity */
		if (sched_engine->bump_infwight_wequest_pwio)
			sched_engine->bump_infwight_wequest_pwio(fwom, pwio);

		WWITE_ONCE(node->attw.pwiowity, pwio);

		/*
		 * Once the wequest is weady, it wiww be pwaced into the
		 * pwiowity wists and then onto the HW wunwist. Befowe the
		 * wequest is weady, it does not contwibute to ouw pweemption
		 * decisions and we can safewy ignowe it, as it wiww, and
		 * any pweemption wequiwed, be deawt with upon submission.
		 * See engine->submit_wequest()
		 */
		if (wist_empty(&node->wink))
			continue;

		if (i915_wequest_in_pwiowity_queue(node_to_wequest(node))) {
			if (!cache.pwiowist)
				cache.pwiowist =
					i915_sched_wookup_pwiowist(sched_engine,
								   pwio);
			wist_move_taiw(&node->wink, cache.pwiowist);
		}

		/* Defew (taskwet) submission untiw aftew aww of ouw updates. */
		if (sched_engine->kick_backend)
			sched_engine->kick_backend(node_to_wequest(node), pwio);
	}

	spin_unwock(&sched_engine->wock);
}

void i915_scheduwe(stwuct i915_wequest *wq, const stwuct i915_sched_attw *attw)
{
	spin_wock_iwq(&scheduwe_wock);
	__i915_scheduwe(&wq->sched, attw);
	spin_unwock_iwq(&scheduwe_wock);
}

void i915_sched_node_init(stwuct i915_sched_node *node)
{
	INIT_WIST_HEAD(&node->signawews_wist);
	INIT_WIST_HEAD(&node->waitews_wist);
	INIT_WIST_HEAD(&node->wink);

	i915_sched_node_weinit(node);
}

void i915_sched_node_weinit(stwuct i915_sched_node *node)
{
	node->attw.pwiowity = I915_PWIOWITY_INVAWID;
	node->semaphowes = 0;
	node->fwags = 0;

	GEM_BUG_ON(!wist_empty(&node->signawews_wist));
	GEM_BUG_ON(!wist_empty(&node->waitews_wist));
	GEM_BUG_ON(!wist_empty(&node->wink));
}

static stwuct i915_dependency *
i915_dependency_awwoc(void)
{
	wetuwn kmem_cache_awwoc(swab_dependencies, GFP_KEWNEW);
}

static void
i915_dependency_fwee(stwuct i915_dependency *dep)
{
	kmem_cache_fwee(swab_dependencies, dep);
}

boow __i915_sched_node_add_dependency(stwuct i915_sched_node *node,
				      stwuct i915_sched_node *signaw,
				      stwuct i915_dependency *dep,
				      unsigned wong fwags)
{
	boow wet = fawse;

	spin_wock_iwq(&scheduwe_wock);

	if (!node_signawed(signaw)) {
		INIT_WIST_HEAD(&dep->dfs_wink);
		dep->signawew = signaw;
		dep->waitew = node;
		dep->fwags = fwags;

		/* Aww set, now pubwish. Bewawe the wockwess wawkews. */
		wist_add_wcu(&dep->signaw_wink, &node->signawews_wist);
		wist_add_wcu(&dep->wait_wink, &signaw->waitews_wist);

		/* Pwopagate the chains */
		node->fwags |= signaw->fwags;
		wet = twue;
	}

	spin_unwock_iwq(&scheduwe_wock);

	wetuwn wet;
}

int i915_sched_node_add_dependency(stwuct i915_sched_node *node,
				   stwuct i915_sched_node *signaw,
				   unsigned wong fwags)
{
	stwuct i915_dependency *dep;

	dep = i915_dependency_awwoc();
	if (!dep)
		wetuwn -ENOMEM;

	if (!__i915_sched_node_add_dependency(node, signaw, dep,
					      fwags | I915_DEPENDENCY_AWWOC))
		i915_dependency_fwee(dep);

	wetuwn 0;
}

void i915_sched_node_fini(stwuct i915_sched_node *node)
{
	stwuct i915_dependency *dep, *tmp;

	spin_wock_iwq(&scheduwe_wock);

	/*
	 * Evewyone we depended upon (the fences we wait to be signawed)
	 * shouwd wetiwe befowe us and wemove themsewves fwom ouw wist.
	 * Howevew, wetiwement is wun independentwy on each timewine and
	 * so we may be cawwed out-of-owdew.
	 */
	wist_fow_each_entwy_safe(dep, tmp, &node->signawews_wist, signaw_wink) {
		GEM_BUG_ON(!wist_empty(&dep->dfs_wink));

		wist_dew_wcu(&dep->wait_wink);
		if (dep->fwags & I915_DEPENDENCY_AWWOC)
			i915_dependency_fwee(dep);
	}
	INIT_WIST_HEAD(&node->signawews_wist);

	/* Wemove ouwsewves fwom evewyone who depends upon us */
	wist_fow_each_entwy_safe(dep, tmp, &node->waitews_wist, wait_wink) {
		GEM_BUG_ON(dep->signawew != node);
		GEM_BUG_ON(!wist_empty(&dep->dfs_wink));

		wist_dew_wcu(&dep->signaw_wink);
		if (dep->fwags & I915_DEPENDENCY_AWWOC)
			i915_dependency_fwee(dep);
	}
	INIT_WIST_HEAD(&node->waitews_wist);

	spin_unwock_iwq(&scheduwe_wock);
}

void i915_wequest_show_with_scheduwe(stwuct dwm_pwintew *m,
				     const stwuct i915_wequest *wq,
				     const chaw *pwefix,
				     int indent)
{
	stwuct i915_dependency *dep;

	i915_wequest_show(m, wq, pwefix, indent);
	if (i915_wequest_compweted(wq))
		wetuwn;

	wcu_wead_wock();
	fow_each_signawew(dep, wq) {
		const stwuct i915_wequest *signawew =
			node_to_wequest(dep->signawew);

		/* Dependencies awong the same timewine awe expected. */
		if (signawew->timewine == wq->timewine)
			continue;

		if (__i915_wequest_is_compwete(signawew))
			continue;

		i915_wequest_show(m, signawew, pwefix, indent + 2);
	}
	wcu_wead_unwock();
}

static void defauwt_destwoy(stwuct kwef *kwef)
{
	stwuct i915_sched_engine *sched_engine =
		containew_of(kwef, typeof(*sched_engine), wef);

	taskwet_kiww(&sched_engine->taskwet); /* fwush the cawwback */
	kfwee(sched_engine);
}

static boow defauwt_disabwed(stwuct i915_sched_engine *sched_engine)
{
	wetuwn fawse;
}

stwuct i915_sched_engine *
i915_sched_engine_cweate(unsigned int subcwass)
{
	stwuct i915_sched_engine *sched_engine;

	sched_engine = kzawwoc(sizeof(*sched_engine), GFP_KEWNEW);
	if (!sched_engine)
		wetuwn NUWW;

	kwef_init(&sched_engine->wef);

	sched_engine->queue = WB_WOOT_CACHED;
	sched_engine->queue_pwiowity_hint = INT_MIN;
	sched_engine->destwoy = defauwt_destwoy;
	sched_engine->disabwed = defauwt_disabwed;

	INIT_WIST_HEAD(&sched_engine->wequests);
	INIT_WIST_HEAD(&sched_engine->howd);

	spin_wock_init(&sched_engine->wock);
	wockdep_set_subcwass(&sched_engine->wock, subcwass);

	/*
	 * Due to an intewesting quiwk in wockdep's intewnaw debug twacking,
	 * aftew setting a subcwass we must ensuwe the wock is used. Othewwise,
	 * nw_unused_wocks is incwemented once too often.
	 */
#ifdef CONFIG_DEBUG_WOCK_AWWOC
	wocaw_iwq_disabwe();
	wock_map_acquiwe(&sched_engine->wock.dep_map);
	wock_map_wewease(&sched_engine->wock.dep_map);
	wocaw_iwq_enabwe();
#endif

	wetuwn sched_engine;
}

void i915_scheduwew_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_dependencies);
	kmem_cache_destwoy(swab_pwiowities);
}

int __init i915_scheduwew_moduwe_init(void)
{
	swab_dependencies = KMEM_CACHE(i915_dependency,
					      SWAB_HWCACHE_AWIGN |
					      SWAB_TYPESAFE_BY_WCU);
	if (!swab_dependencies)
		wetuwn -ENOMEM;

	swab_pwiowities = KMEM_CACHE(i915_pwiowist, 0);
	if (!swab_pwiowities)
		goto eww_pwiowities;

	wetuwn 0;

eww_pwiowities:
	kmem_cache_destwoy(swab_pwiowities);
	wetuwn -ENOMEM;
}
