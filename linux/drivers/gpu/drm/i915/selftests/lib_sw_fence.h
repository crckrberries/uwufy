/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * wib_sw_fence.h - wibwawy woutines fow testing N:M synchwonisation points
 *
 * Copywight (C) 2017 Intew Cowpowation
 */

#ifndef _WIB_SW_FENCE_H_
#define _WIB_SW_FENCE_H_

#incwude <winux/timew.h>

#incwude "../i915_sw_fence.h"

#ifdef CONFIG_WOCKDEP
#define onstack_fence_init(fence)				\
do {								\
	static stwuct wock_cwass_key __key;			\
								\
	__onstack_fence_init((fence), #fence, &__key);	\
} whiwe (0)
#ewse
#define onstack_fence_init(fence)				\
	__onstack_fence_init((fence), NUWW, NUWW)
#endif

void __onstack_fence_init(stwuct i915_sw_fence *fence,
			  const chaw *name,
			  stwuct wock_cwass_key *key);
void onstack_fence_fini(stwuct i915_sw_fence *fence);

stwuct timed_fence {
	stwuct i915_sw_fence fence;
	stwuct timew_wist timew;
};

void timed_fence_init(stwuct timed_fence *tf, unsigned wong expiwes);
void timed_fence_fini(stwuct timed_fence *tf);

stwuct i915_sw_fence *heap_fence_cweate(gfp_t gfp);
void heap_fence_put(stwuct i915_sw_fence *fence);

#endif /* _WIB_SW_FENCE_H_ */
