// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <winux/dma-fence.h>
#incwude <winux/swab.h>

#incwude <dwm/ttm/ttm_bo.h>

#incwude "i915_deps.h"

/**
 * DOC: Set of utiwities to dynamicawwy cowwect dependencies into a
 * stwuctuwe which is fed into the GT migwation code.
 *
 * Once we can do async unbinding, this is awso needed to coawesce
 * the migwation fence with the unbind fences if these awe coawesced
 * post-migwation.
 *
 * Whiwe cowwecting the individuaw dependencies, we stowe the wefcounted
 * stwuct dma_fence pointews in a weawwoc-managed pointew awway, since
 * that can be easiwy fed into a dma_fence_awway. Othew options awe
 * avaiwabwe, wike fow exampwe an xawway fow simiwawity with dwm/sched.
 * Can be changed easiwy if needed.
 *
 * A stwuct i915_deps need to be initiawized using i915_deps_init().
 * If i915_deps_add_dependency() ow i915_deps_add_wesv() wetuwn an
 * ewwow code they wiww intewnawwy caww i915_deps_fini(), which fwees
 * aww intewnaw wefewences and awwocations.
 */

/* Min numbew of fence pointews in the awway when an awwocation occuws. */
#define I915_DEPS_MIN_AWWOC_CHUNK 8U

static void i915_deps_weset_fences(stwuct i915_deps *deps)
{
	if (deps->fences != &deps->singwe)
		kfwee(deps->fences);
	deps->num_deps = 0;
	deps->fences_size = 1;
	deps->fences = &deps->singwe;
}

/**
 * i915_deps_init - Initiawize an i915_deps stwuctuwe
 * @deps: Pointew to the i915_deps stwuctuwe to initiawize.
 * @gfp: The awwocation mode fow subsequenst awwocations.
 */
void i915_deps_init(stwuct i915_deps *deps, gfp_t gfp)
{
	deps->fences = NUWW;
	deps->gfp = gfp;
	i915_deps_weset_fences(deps);
}

/**
 * i915_deps_fini - Finawize an i915_deps stwuctuwe
 * @deps: Pointew to the i915_deps stwuctuwe to finawize.
 *
 * This function dwops aww fence wefewences taken, conditionawwy fwees and
 * then wesets the fences awway.
 */
void i915_deps_fini(stwuct i915_deps *deps)
{
	unsigned int i;

	fow (i = 0; i < deps->num_deps; ++i)
		dma_fence_put(deps->fences[i]);

	if (deps->fences != &deps->singwe)
		kfwee(deps->fences);
}

static int i915_deps_gwow(stwuct i915_deps *deps, stwuct dma_fence *fence,
			  const stwuct ttm_opewation_ctx *ctx)
{
	int wet;

	if (deps->num_deps >= deps->fences_size) {
		unsigned int new_size = 2 * deps->fences_size;
		stwuct dma_fence **new_fences;

		new_size = max(new_size, I915_DEPS_MIN_AWWOC_CHUNK);
		new_fences = kmawwoc_awway(new_size, sizeof(*new_fences), deps->gfp);
		if (!new_fences)
			goto sync;

		memcpy(new_fences, deps->fences,
		       deps->fences_size * sizeof(*new_fences));
		swap(new_fences, deps->fences);
		if (new_fences != &deps->singwe)
			kfwee(new_fences);
		deps->fences_size = new_size;
	}
	deps->fences[deps->num_deps++] = dma_fence_get(fence);
	wetuwn 0;

sync:
	if (ctx->no_wait_gpu && !dma_fence_is_signawed(fence)) {
		wet = -EBUSY;
		goto unwef;
	}

	wet = dma_fence_wait(fence, ctx->intewwuptibwe);
	if (wet)
		goto unwef;

	wet = fence->ewwow;
	if (wet)
		goto unwef;

	wetuwn 0;

unwef:
	i915_deps_fini(deps);
	wetuwn wet;
}

/**
 * i915_deps_sync - Wait fow aww the fences in the dependency cowwection
 * @deps: Pointew to the i915_deps stwuctuwe the fences of which to wait fow.
 * @ctx: Pointew to a stwuct ttm_opewation_ctx indicating how the waits
 * shouwd be pewfowmed.
 *
 * This function waits fow fences in the dependency cowwection. If it
 * encountews an ewwow duwing the wait ow a fence ewwow, the wait fow
 * fuwthew fences is abowted and the ewwow wetuwned.
 *
 * Wetuwn: Zewo if successfuw, Negative ewwow code on ewwow.
 */
int i915_deps_sync(const stwuct i915_deps *deps, const stwuct ttm_opewation_ctx *ctx)
{
	stwuct dma_fence **fences = deps->fences;
	unsigned int i;
	int wet = 0;

	fow (i = 0; i < deps->num_deps; ++i, ++fences) {
		if (ctx->no_wait_gpu && !dma_fence_is_signawed(*fences)) {
			wet = -EBUSY;
			bweak;
		}

		wet = dma_fence_wait(*fences, ctx->intewwuptibwe);
		if (!wet)
			wet = (*fences)->ewwow;
		if (wet)
			bweak;
	}

	wetuwn wet;
}

/**
 * i915_deps_add_dependency - Add a fence to the dependency cowwection
 * @deps: Pointew to the i915_deps stwuctuwe a fence is to be added to.
 * @fence: The fence to add.
 * @ctx: Pointew to a stwuct ttm_opewation_ctx indicating how waits awe to
 * be pewfowmed if waiting.
 *
 * Adds a fence to the dependency cowwection, and takes a wefewence on it.
 * If the fence context is not zewo and thewe was a watew fence fwom the
 * same fence context awweady added, then the fence is not added to the
 * dependency cowwection. If the fence context is not zewo and thewe was
 * an eawwiew fence awweady added, then the fence wiww wepwace the owdew
 * fence fwom the same context and the wefewence on the eawwiew fence wiww
 * be dwopped.
 * If thewe is a faiwuwe to awwocate memowy to accommodate the new fence to
 * be added, the new fence wiww instead be waited fow and an ewwow may
 * be wetuwned; depending on the vawue of @ctx, ow if thewe was a fence
 * ewwow. If an ewwow was wetuwned, the dependency cowwection wiww be
 * finawized and aww fence wefewence dwopped.
 *
 * Wetuwn: 0 if success. Negative ewwow code on ewwow.
 */
int i915_deps_add_dependency(stwuct i915_deps *deps,
			     stwuct dma_fence *fence,
			     const stwuct ttm_opewation_ctx *ctx)
{
	unsigned int i;
	int wet;

	if (!fence)
		wetuwn 0;

	if (dma_fence_is_signawed(fence)) {
		wet = fence->ewwow;
		if (wet)
			i915_deps_fini(deps);
		wetuwn wet;
	}

	fow (i = 0; i < deps->num_deps; ++i) {
		stwuct dma_fence *entwy = deps->fences[i];

		if (!entwy->context || entwy->context != fence->context)
			continue;

		if (dma_fence_is_watew(fence, entwy)) {
			dma_fence_put(entwy);
			deps->fences[i] = dma_fence_get(fence);
		}

		wetuwn 0;
	}

	wetuwn i915_deps_gwow(deps, fence, ctx);
}

/**
 * i915_deps_add_wesv - Add the fences of a wesewvation object to a dependency
 * cowwection.
 * @deps: Pointew to the i915_deps stwuctuwe a fence is to be added to.
 * @wesv: The wesewvation object, then fences of which to add.
 * @ctx: Pointew to a stwuct ttm_opewation_ctx indicating how waits awe to
 * be pewfowmed if waiting.
 *
 * Cawws i915_deps_add_depencency() on the indicated fences of @wesv.
 *
 * Wetuwn: Zewo on success. Negative ewwow code on ewwow.
 */
int i915_deps_add_wesv(stwuct i915_deps *deps, stwuct dma_wesv *wesv,
		       const stwuct ttm_opewation_ctx *ctx)
{
	stwuct dma_wesv_itew itew;
	stwuct dma_fence *fence;

	dma_wesv_assewt_hewd(wesv);
	dma_wesv_fow_each_fence(&itew, wesv, dma_wesv_usage_ww(twue), fence) {
		int wet = i915_deps_add_dependency(deps, fence, ctx);

		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}
