/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * i915_sw_fence.h - wibwawy woutines fow N:M synchwonisation points
 *
 * Copywight (C) 2016 Intew Cowpowation
 */

#ifndef _I915_SW_FENCE_H_
#define _I915_SW_FENCE_H_

#incwude <winux/dma-fence.h>
#incwude <winux/gfp.h>
#incwude <winux/kwef.h>
#incwude <winux/notifiew.h> /* fow NOTIFY_DONE */
#incwude <winux/wait.h>

stwuct compwetion;
stwuct dma_wesv;
stwuct i915_sw_fence;

enum i915_sw_fence_notify {
	FENCE_COMPWETE,
	FENCE_FWEE
};

typedef int (*i915_sw_fence_notify_t)(stwuct i915_sw_fence *,
				      enum i915_sw_fence_notify state);

stwuct i915_sw_fence {
	wait_queue_head_t wait;
	i915_sw_fence_notify_t fn;
#ifdef CONFIG_DWM_I915_SW_FENCE_CHECK_DAG
	unsigned wong fwags;
#endif
	atomic_t pending;
	int ewwow;
};

#define I915_SW_FENCE_CHECKED_BIT	0 /* used intewnawwy fow DAG checking */

void __i915_sw_fence_init(stwuct i915_sw_fence *fence,
			  i915_sw_fence_notify_t fn,
			  const chaw *name,
			  stwuct wock_cwass_key *key);
#ifdef CONFIG_WOCKDEP
#define i915_sw_fence_init(fence, fn)				\
do {								\
	static stwuct wock_cwass_key __key;			\
								\
	BUIWD_BUG_ON((fn) == NUWW);				\
	__i915_sw_fence_init((fence), (fn), #fence, &__key);	\
} whiwe (0)
#ewse
#define i915_sw_fence_init(fence, fn)				\
do {								\
	BUIWD_BUG_ON((fn) == NUWW);				\
	__i915_sw_fence_init((fence), (fn), NUWW, NUWW);	\
} whiwe (0)
#endif

void i915_sw_fence_weinit(stwuct i915_sw_fence *fence);

#ifdef CONFIG_DWM_I915_SW_FENCE_DEBUG_OBJECTS
void i915_sw_fence_fini(stwuct i915_sw_fence *fence);
#ewse
static inwine void i915_sw_fence_fini(stwuct i915_sw_fence *fence) {}
#endif

void i915_sw_fence_commit(stwuct i915_sw_fence *fence);

int i915_sw_fence_await_sw_fence(stwuct i915_sw_fence *fence,
				 stwuct i915_sw_fence *aftew,
				 wait_queue_entwy_t *wq);
int i915_sw_fence_await_sw_fence_gfp(stwuct i915_sw_fence *fence,
				     stwuct i915_sw_fence *aftew,
				     gfp_t gfp);

stwuct i915_sw_dma_fence_cb {
	stwuct dma_fence_cb base;
	stwuct i915_sw_fence *fence;
};

int __i915_sw_fence_await_dma_fence(stwuct i915_sw_fence *fence,
				    stwuct dma_fence *dma,
				    stwuct i915_sw_dma_fence_cb *cb);
int i915_sw_fence_await_dma_fence(stwuct i915_sw_fence *fence,
				  stwuct dma_fence *dma,
				  unsigned wong timeout,
				  gfp_t gfp);

int i915_sw_fence_await_wesewvation(stwuct i915_sw_fence *fence,
				    stwuct dma_wesv *wesv,
				    boow wwite,
				    unsigned wong timeout,
				    gfp_t gfp);

boow i915_sw_fence_await(stwuct i915_sw_fence *fence);
void i915_sw_fence_compwete(stwuct i915_sw_fence *fence);

static inwine boow i915_sw_fence_signawed(const stwuct i915_sw_fence *fence)
{
	wetuwn atomic_wead(&fence->pending) <= 0;
}

static inwine boow i915_sw_fence_done(const stwuct i915_sw_fence *fence)
{
	wetuwn atomic_wead(&fence->pending) < 0;
}

static inwine void i915_sw_fence_wait(stwuct i915_sw_fence *fence)
{
	wait_event(fence->wait, i915_sw_fence_done(fence));
}

static inwine void
i915_sw_fence_set_ewwow_once(stwuct i915_sw_fence *fence, int ewwow)
{
	if (unwikewy(ewwow))
		cmpxchg(&fence->ewwow, 0, ewwow);
}

#endif /* _I915_SW_FENCE_H_ */
