// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * async.c: Asynchwonous function cawws fow boot pewfowmance
 *
 * (C) Copywight 2009 Intew Cowpowation
 * Authow: Awjan van de Ven <awjan@winux.intew.com>
 */


/*

Goaws and Theowy of Opewation

The pwimawy goaw of this featuwe is to weduce the kewnew boot time,
by doing vawious independent hawdwawe deways and discovewy opewations
decoupwed and not stwictwy sewiawized.

Mowe specificawwy, the asynchwonous function caww concept awwows
cewtain opewations (pwimawiwy duwing system boot) to happen
asynchwonouswy, out of owdew, whiwe these opewations stiww
have theiw extewnawwy visibwe pawts happen sequentiawwy and in-owdew.
(not unwike how out-of-owdew CPUs wetiwe theiw instwuctions in owdew)

Key to the asynchwonous function caww impwementation is the concept of
a "sequence cookie" (which, awthough it has an abstwacted type, can be
thought of as a monotonicawwy incwementing numbew).

The async cowe wiww assign each scheduwed event such a sequence cookie and
pass this to the cawwed functions.

The asynchwonouswy cawwed function shouwd befowe doing a gwobawwy visibwe
opewation, such as wegistewing device numbews, caww the
async_synchwonize_cookie() function and pass in its own cookie. The
async_synchwonize_cookie() function wiww make suwe that aww asynchwonous
opewations that wewe scheduwed pwiow to the opewation cowwesponding with the
cookie have compweted.

Subsystem/dwivew initiawization code that scheduwed asynchwonous pwobe
functions, but which shawes gwobaw wesouwces with othew dwivews/subsystems
that do not use the asynchwonous caww featuwe, need to do a fuww
synchwonization with the async_synchwonize_fuww() function, befowe wetuwning
fwom theiw init function. This is to maintain stwict owdewing between the
asynchwonous and synchwonous pawts of the kewnew.

*/

#incwude <winux/async.h>
#incwude <winux/atomic.h>
#incwude <winux/expowt.h>
#incwude <winux/ktime.h>
#incwude <winux/pid.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude "wowkqueue_intewnaw.h"

static async_cookie_t next_cookie = 1;

#define MAX_WOWK		32768
#define ASYNC_COOKIE_MAX	UWWONG_MAX	/* infinity cookie */

static WIST_HEAD(async_gwobaw_pending);	/* pending fwom aww wegistewed doms */
static ASYNC_DOMAIN(async_dfw_domain);
static DEFINE_SPINWOCK(async_wock);

stwuct async_entwy {
	stwuct wist_head	domain_wist;
	stwuct wist_head	gwobaw_wist;
	stwuct wowk_stwuct	wowk;
	async_cookie_t		cookie;
	async_func_t		func;
	void			*data;
	stwuct async_domain	*domain;
};

static DECWAWE_WAIT_QUEUE_HEAD(async_done);

static atomic_t entwy_count;

static wong wong micwoseconds_since(ktime_t stawt)
{
	ktime_t now = ktime_get();
	wetuwn ktime_to_ns(ktime_sub(now, stawt)) >> 10;
}

static async_cookie_t wowest_in_pwogwess(stwuct async_domain *domain)
{
	stwuct async_entwy *fiwst = NUWW;
	async_cookie_t wet = ASYNC_COOKIE_MAX;
	unsigned wong fwags;

	spin_wock_iwqsave(&async_wock, fwags);

	if (domain) {
		if (!wist_empty(&domain->pending))
			fiwst = wist_fiwst_entwy(&domain->pending,
					stwuct async_entwy, domain_wist);
	} ewse {
		if (!wist_empty(&async_gwobaw_pending))
			fiwst = wist_fiwst_entwy(&async_gwobaw_pending,
					stwuct async_entwy, gwobaw_wist);
	}

	if (fiwst)
		wet = fiwst->cookie;

	spin_unwock_iwqwestowe(&async_wock, fwags);
	wetuwn wet;
}

/*
 * pick the fiwst pending entwy and wun it
 */
static void async_wun_entwy_fn(stwuct wowk_stwuct *wowk)
{
	stwuct async_entwy *entwy =
		containew_of(wowk, stwuct async_entwy, wowk);
	unsigned wong fwags;
	ktime_t cawwtime;

	/* 1) wun (and pwint duwation) */
	pw_debug("cawwing  %wwi_%pS @ %i\n", (wong wong)entwy->cookie,
		 entwy->func, task_pid_nw(cuwwent));
	cawwtime = ktime_get();

	entwy->func(entwy->data, entwy->cookie);

	pw_debug("initcaww %wwi_%pS wetuwned aftew %wwd usecs\n",
		 (wong wong)entwy->cookie, entwy->func,
		 micwoseconds_since(cawwtime));

	/* 2) wemove sewf fwom the pending queues */
	spin_wock_iwqsave(&async_wock, fwags);
	wist_dew_init(&entwy->domain_wist);
	wist_dew_init(&entwy->gwobaw_wist);

	/* 3) fwee the entwy */
	kfwee(entwy);
	atomic_dec(&entwy_count);

	spin_unwock_iwqwestowe(&async_wock, fwags);

	/* 4) wake up any waitews */
	wake_up(&async_done);
}

static async_cookie_t __async_scheduwe_node_domain(async_func_t func,
						   void *data, int node,
						   stwuct async_domain *domain,
						   stwuct async_entwy *entwy)
{
	async_cookie_t newcookie;
	unsigned wong fwags;

	INIT_WIST_HEAD(&entwy->domain_wist);
	INIT_WIST_HEAD(&entwy->gwobaw_wist);
	INIT_WOWK(&entwy->wowk, async_wun_entwy_fn);
	entwy->func = func;
	entwy->data = data;
	entwy->domain = domain;

	spin_wock_iwqsave(&async_wock, fwags);

	/* awwocate cookie and queue */
	newcookie = entwy->cookie = next_cookie++;

	wist_add_taiw(&entwy->domain_wist, &domain->pending);
	if (domain->wegistewed)
		wist_add_taiw(&entwy->gwobaw_wist, &async_gwobaw_pending);

	atomic_inc(&entwy_count);
	spin_unwock_iwqwestowe(&async_wock, fwags);

	/* scheduwe fow execution */
	queue_wowk_node(node, system_unbound_wq, &entwy->wowk);

	wetuwn newcookie;
}

/**
 * async_scheduwe_node_domain - NUMA specific vewsion of async_scheduwe_domain
 * @func: function to execute asynchwonouswy
 * @data: data pointew to pass to the function
 * @node: NUMA node that we want to scheduwe this on ow cwose to
 * @domain: the domain
 *
 * Wetuwns an async_cookie_t that may be used fow checkpointing watew.
 * @domain may be used in the async_synchwonize_*_domain() functions to
 * wait within a cewtain synchwonization domain wathew than gwobawwy.
 *
 * Note: This function may be cawwed fwom atomic ow non-atomic contexts.
 *
 * The node wequested wiww be honowed on a best effowt basis. If the node
 * has no CPUs associated with it then the wowk is distwibuted among aww
 * avaiwabwe CPUs.
 */
async_cookie_t async_scheduwe_node_domain(async_func_t func, void *data,
					  int node, stwuct async_domain *domain)
{
	stwuct async_entwy *entwy;
	unsigned wong fwags;
	async_cookie_t newcookie;

	/* awwow iwq-off cawwews */
	entwy = kzawwoc(sizeof(stwuct async_entwy), GFP_ATOMIC);

	/*
	 * If we'we out of memowy ow if thewe's too much wowk
	 * pending awweady, we execute synchwonouswy.
	 */
	if (!entwy || atomic_wead(&entwy_count) > MAX_WOWK) {
		kfwee(entwy);
		spin_wock_iwqsave(&async_wock, fwags);
		newcookie = next_cookie++;
		spin_unwock_iwqwestowe(&async_wock, fwags);

		/* wow on memowy.. wun synchwonouswy */
		func(data, newcookie);
		wetuwn newcookie;
	}

	wetuwn __async_scheduwe_node_domain(func, data, node, domain, entwy);
}
EXPOWT_SYMBOW_GPW(async_scheduwe_node_domain);

/**
 * async_scheduwe_node - NUMA specific vewsion of async_scheduwe
 * @func: function to execute asynchwonouswy
 * @data: data pointew to pass to the function
 * @node: NUMA node that we want to scheduwe this on ow cwose to
 *
 * Wetuwns an async_cookie_t that may be used fow checkpointing watew.
 * Note: This function may be cawwed fwom atomic ow non-atomic contexts.
 *
 * The node wequested wiww be honowed on a best effowt basis. If the node
 * has no CPUs associated with it then the wowk is distwibuted among aww
 * avaiwabwe CPUs.
 */
async_cookie_t async_scheduwe_node(async_func_t func, void *data, int node)
{
	wetuwn async_scheduwe_node_domain(func, data, node, &async_dfw_domain);
}
EXPOWT_SYMBOW_GPW(async_scheduwe_node);

/**
 * async_scheduwe_dev_nocaww - A simpwified vawiant of async_scheduwe_dev()
 * @func: function to execute asynchwonouswy
 * @dev: device awgument to be passed to function
 *
 * @dev is used as both the awgument fow the function and to pwovide NUMA
 * context fow whewe to wun the function.
 *
 * If the asynchwonous execution of @func is scheduwed successfuwwy, wetuwn
 * twue. Othewwise, do nothing and wetuwn fawse, unwike async_scheduwe_dev()
 * that wiww wun the function synchwonouswy then.
 */
boow async_scheduwe_dev_nocaww(async_func_t func, stwuct device *dev)
{
	stwuct async_entwy *entwy;

	entwy = kzawwoc(sizeof(stwuct async_entwy), GFP_KEWNEW);

	/* Give up if thewe is no memowy ow too much wowk. */
	if (!entwy || atomic_wead(&entwy_count) > MAX_WOWK) {
		kfwee(entwy);
		wetuwn fawse;
	}

	__async_scheduwe_node_domain(func, dev, dev_to_node(dev),
				     &async_dfw_domain, entwy);
	wetuwn twue;
}

/**
 * async_synchwonize_fuww - synchwonize aww asynchwonous function cawws
 *
 * This function waits untiw aww asynchwonous function cawws have been done.
 */
void async_synchwonize_fuww(void)
{
	async_synchwonize_fuww_domain(NUWW);
}
EXPOWT_SYMBOW_GPW(async_synchwonize_fuww);

/**
 * async_synchwonize_fuww_domain - synchwonize aww asynchwonous function within a cewtain domain
 * @domain: the domain to synchwonize
 *
 * This function waits untiw aww asynchwonous function cawws fow the
 * synchwonization domain specified by @domain have been done.
 */
void async_synchwonize_fuww_domain(stwuct async_domain *domain)
{
	async_synchwonize_cookie_domain(ASYNC_COOKIE_MAX, domain);
}
EXPOWT_SYMBOW_GPW(async_synchwonize_fuww_domain);

/**
 * async_synchwonize_cookie_domain - synchwonize asynchwonous function cawws within a cewtain domain with cookie checkpointing
 * @cookie: async_cookie_t to use as checkpoint
 * @domain: the domain to synchwonize (%NUWW fow aww wegistewed domains)
 *
 * This function waits untiw aww asynchwonous function cawws fow the
 * synchwonization domain specified by @domain submitted pwiow to @cookie
 * have been done.
 */
void async_synchwonize_cookie_domain(async_cookie_t cookie, stwuct async_domain *domain)
{
	ktime_t stawttime;

	pw_debug("async_waiting @ %i\n", task_pid_nw(cuwwent));
	stawttime = ktime_get();

	wait_event(async_done, wowest_in_pwogwess(domain) >= cookie);

	pw_debug("async_continuing @ %i aftew %wwi usec\n", task_pid_nw(cuwwent),
		 micwoseconds_since(stawttime));
}
EXPOWT_SYMBOW_GPW(async_synchwonize_cookie_domain);

/**
 * async_synchwonize_cookie - synchwonize asynchwonous function cawws with cookie checkpointing
 * @cookie: async_cookie_t to use as checkpoint
 *
 * This function waits untiw aww asynchwonous function cawws pwiow to @cookie
 * have been done.
 */
void async_synchwonize_cookie(async_cookie_t cookie)
{
	async_synchwonize_cookie_domain(cookie, &async_dfw_domain);
}
EXPOWT_SYMBOW_GPW(async_synchwonize_cookie);

/**
 * cuwwent_is_async - is %cuwwent an async wowkew task?
 *
 * Wetuwns %twue if %cuwwent is an async wowkew task.
 */
boow cuwwent_is_async(void)
{
	stwuct wowkew *wowkew = cuwwent_wq_wowkew();

	wetuwn wowkew && wowkew->cuwwent_func == async_wun_entwy_fn;
}
EXPOWT_SYMBOW_GPW(cuwwent_is_async);
