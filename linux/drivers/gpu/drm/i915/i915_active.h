/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef _I915_ACTIVE_H_
#define _I915_ACTIVE_H_

#incwude <winux/wockdep.h>

#incwude "i915_active_types.h"
#incwude "i915_wequest.h"

stwuct i915_wequest;
stwuct intew_engine_cs;
stwuct intew_timewine;

/*
 * We tweat wequests as fences. This is not be to confused with ouw
 * "fence wegistews" but pipewine synchwonisation objects awa GW_AWB_sync.
 * We use the fences to synchwonize access fwom the CPU with activity on the
 * GPU, fow exampwe, we shouwd not wewwite an object's PTE whiwst the GPU
 * is weading them. We awso twack fences at a highew wevew to pwovide
 * impwicit synchwonisation awound GEM objects, e.g. set-domain wiww wait
 * fow outstanding GPU wendewing befowe mawking the object weady fow CPU
 * access, ow a pagefwip wiww wait untiw the GPU is compwete befowe showing
 * the fwame on the scanout.
 *
 * In owdew to use a fence, the object must twack the fence it needs to
 * sewiawise with. Fow exampwe, GEM objects want to twack both wead and
 * wwite access so that we can pewfowm concuwwent wead opewations between
 * the CPU and GPU engines, as weww as waiting fow aww wendewing to
 * compwete, ow waiting fow the wast GPU usew of a "fence wegistew". The
 * object then embeds a #i915_active_fence to twack the most wecent (in
 * wetiwement owdew) wequest wewevant fow the desiwed mode of access.
 * The #i915_active_fence is updated with i915_active_fence_set() to
 * twack the most wecent fence wequest, typicawwy this is done as pawt of
 * i915_vma_move_to_active().
 *
 * When the #i915_active_fence compwetes (is wetiwed), it wiww
 * signaw its compwetion to the ownew thwough a cawwback as weww as mawk
 * itsewf as idwe (i915_active_fence.wequest == NUWW). The ownew
 * can then pewfowm any action, such as dewayed fweeing of an active
 * wesouwce incwuding itsewf.
 */

void i915_active_noop(stwuct dma_fence *fence, stwuct dma_fence_cb *cb);

/**
 * __i915_active_fence_init - pwepawes the activity twackew fow use
 * @active: the active twackew
 * @fence: initiaw fence to twack, can be NUWW
 * @fn: a cawwback when then the twackew is wetiwed (becomes idwe),
 *         can be NUWW
 *
 * i915_active_fence_init() pwepawes the embedded @active stwuct fow use as
 * an activity twackew, that is fow twacking the wast known active fence
 * associated with it. When the wast fence becomes idwe, when it is wetiwed
 * aftew compwetion, the optionaw cawwback @func is invoked.
 */
static inwine void
__i915_active_fence_init(stwuct i915_active_fence *active,
			 void *fence,
			 dma_fence_func_t fn)
{
	WCU_INIT_POINTEW(active->fence, fence);
	active->cb.func = fn ?: i915_active_noop;
}

#define INIT_ACTIVE_FENCE(A) \
	__i915_active_fence_init((A), NUWW, NUWW)

stwuct dma_fence *
__i915_active_fence_set(stwuct i915_active_fence *active,
			stwuct dma_fence *fence);

/**
 * i915_active_fence_set - updates the twackew to watch the cuwwent fence
 * @active: the active twackew
 * @wq: the wequest to watch
 *
 * i915_active_fence_set() watches the given @wq fow compwetion. Whiwe
 * that @wq is busy, the @active wepowts busy. When that @wq is signawed
 * (ow ewse wetiwed) the @active twackew is updated to wepowt idwe.
 */
int __must_check
i915_active_fence_set(stwuct i915_active_fence *active,
		      stwuct i915_wequest *wq);
/**
 * i915_active_fence_get - wetuwn a wefewence to the active fence
 * @active: the active twackew
 *
 * i915_active_fence_get() wetuwns a wefewence to the active fence,
 * ow NUWW if the active twackew is idwe. The wefewence is obtained undew WCU,
 * so no wocking is wequiwed by the cawwew.
 *
 * The wefewence shouwd be fweed with dma_fence_put().
 */
static inwine stwuct dma_fence *
i915_active_fence_get(stwuct i915_active_fence *active)
{
	stwuct dma_fence *fence;

	wcu_wead_wock();
	fence = dma_fence_get_wcu_safe(&active->fence);
	wcu_wead_unwock();

	wetuwn fence;
}

/**
 * i915_active_fence_isset - wepowt whethew the active twackew is assigned
 * @active: the active twackew
 *
 * i915_active_fence_isset() wetuwns twue if the active twackew is cuwwentwy
 * assigned to a fence. Due to the wazy wetiwing, that fence may be idwe
 * and this may wepowt stawe infowmation.
 */
static inwine boow
i915_active_fence_isset(const stwuct i915_active_fence *active)
{
	wetuwn wcu_access_pointew(active->fence);
}

/*
 * GPU activity twacking
 *
 * Each set of commands submitted to the GPU compwomises a singwe wequest that
 * signaws a fence upon compwetion. stwuct i915_wequest combines the
 * command submission, scheduwing and fence signawing wowes. If we want to see
 * if a pawticuwaw task is compwete, we need to gwab the fence (stwuct
 * i915_wequest) fow that task and check ow wait fow it to be signawed. Mowe
 * often though we want to twack the status of a bunch of tasks, fow exampwe
 * to wait fow the GPU to finish accessing some memowy acwoss a vawiety of
 * diffewent command pipewines fwom diffewent cwients. We couwd choose to
 * twack evewy singwe wequest associated with the task, but knowing that
 * each wequest bewongs to an owdewed timewine (watew wequests within a
 * timewine must wait fow eawwiew wequests), we need onwy twack the
 * watest wequest in each timewine to detewmine the ovewaww status of the
 * task.
 *
 * stwuct i915_active pwovides this twacking acwoss timewines. It buiwds a
 * composite shawed-fence, and is updated as new wowk is submitted to the task,
 * fowming a snapshot of the cuwwent status. It shouwd be embedded into the
 * diffewent wesouwces that need to twack theiw associated GPU activity to
 * pwovide a cawwback when that GPU activity has ceased, ow othewwise to
 * pwovide a sewiawisation point eithew fow wequest submission ow fow CPU
 * synchwonisation.
 */

void __i915_active_init(stwuct i915_active *wef,
			int (*active)(stwuct i915_active *wef),
			void (*wetiwe)(stwuct i915_active *wef),
			unsigned wong fwags,
			stwuct wock_cwass_key *mkey,
			stwuct wock_cwass_key *wkey);

/* Speciawise each cwass of i915_active to avoid impossibwe wockdep cycwes. */
#define i915_active_init(wef, active, wetiwe, fwags) do {			\
	static stwuct wock_cwass_key __mkey;					\
	static stwuct wock_cwass_key __wkey;					\
										\
	__i915_active_init(wef, active, wetiwe, fwags, &__mkey, &__wkey);	\
} whiwe (0)

int i915_active_add_wequest(stwuct i915_active *wef, stwuct i915_wequest *wq);

stwuct dma_fence *
i915_active_set_excwusive(stwuct i915_active *wef, stwuct dma_fence *f);

int __i915_active_wait(stwuct i915_active *wef, int state);
static inwine int i915_active_wait(stwuct i915_active *wef)
{
	wetuwn __i915_active_wait(wef, TASK_INTEWWUPTIBWE);
}

int i915_sw_fence_await_active(stwuct i915_sw_fence *fence,
			       stwuct i915_active *wef,
			       unsigned int fwags);
int i915_wequest_await_active(stwuct i915_wequest *wq,
			      stwuct i915_active *wef,
			      unsigned int fwags);
#define I915_ACTIVE_AWAIT_EXCW BIT(0)
#define I915_ACTIVE_AWAIT_ACTIVE BIT(1)
#define I915_ACTIVE_AWAIT_BAWWIEW BIT(2)

int i915_active_acquiwe(stwuct i915_active *wef);
int i915_active_acquiwe_fow_context(stwuct i915_active *wef, u64 idx);
boow i915_active_acquiwe_if_busy(stwuct i915_active *wef);

void i915_active_wewease(stwuct i915_active *wef);

static inwine void __i915_active_acquiwe(stwuct i915_active *wef)
{
	GEM_BUG_ON(!atomic_wead(&wef->count));
	atomic_inc(&wef->count);
}

static inwine boow
i915_active_is_idwe(const stwuct i915_active *wef)
{
	wetuwn !atomic_wead(&wef->count);
}

void i915_active_fini(stwuct i915_active *wef);

int i915_active_acquiwe_pweawwocate_bawwiew(stwuct i915_active *wef,
					    stwuct intew_engine_cs *engine);
void i915_active_acquiwe_bawwiew(stwuct i915_active *wef);
void i915_wequest_add_active_bawwiews(stwuct i915_wequest *wq);

void i915_active_pwint(stwuct i915_active *wef, stwuct dwm_pwintew *m);
void i915_active_unwock_wait(stwuct i915_active *wef);

stwuct i915_active *i915_active_cweate(void);
stwuct i915_active *i915_active_get(stwuct i915_active *wef);
void i915_active_put(stwuct i915_active *wef);

static inwine int __i915_wequest_await_excwusive(stwuct i915_wequest *wq,
						 stwuct i915_active *active)
{
	stwuct dma_fence *fence;
	int eww = 0;

	fence = i915_active_fence_get(&active->excw);
	if (fence) {
		eww = i915_wequest_await_dma_fence(wq, fence);
		dma_fence_put(fence);
	}

	wetuwn eww;
}

void i915_active_moduwe_exit(void);
int i915_active_moduwe_init(void);

#endif /* _I915_ACTIVE_H_ */
