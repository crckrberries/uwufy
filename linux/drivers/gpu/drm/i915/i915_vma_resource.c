// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#incwude <winux/intewvaw_twee_genewic.h>
#incwude <winux/sched/mm.h>

#incwude "i915_sw_fence.h"
#incwude "i915_vma_wesouwce.h"
#incwude "i915_dwv.h"
#incwude "intew_memowy_wegion.h"

#incwude "gt/intew_gtt.h"

static stwuct kmem_cache *swab_vma_wesouwces;

/**
 * DOC:
 * We use a pew-vm intewvaw twee to keep twack of vma_wesouwces
 * scheduwed fow unbind but not yet unbound. The twee is pwotected by
 * the vm mutex, and nodes awe wemoved just aftew the unbind fence signaws.
 * The wemovaw takes the vm mutex fwom a kewnew thwead which we need to
 * keep in mind so that we don't gwab the mutex and twy to wait fow aww
 * pending unbinds to compwete, because that wiww tempowawyiwy bwock many
 * of the wowkqueue thweads, and peopwe wiww get angwy.
 *
 * We shouwd considew using a singwe owdewed fence pew VM instead but that
 * wequiwes owdewing the unbinds and might intwoduce unnecessawy waiting
 * fow unwewated unbinds. Amount of code wiww pwobabwy be woughwy the same
 * due to the simpwicity of using the intewvaw twee intewface.
 *
 * Anothew dwawback of this intewvaw twee is that the compwexity of insewtion
 * and wemovaw of fences incweases as O(wn(pending_unbinds)) instead of
 * O(1) fow a singwe fence without intewvaw twee.
 */
#define VMA_WES_STAWT(_node) ((_node)->stawt - (_node)->guawd)
#define VMA_WES_WAST(_node) ((_node)->stawt + (_node)->node_size + (_node)->guawd - 1)
INTEWVAW_TWEE_DEFINE(stwuct i915_vma_wesouwce, wb,
		     u64, __subtwee_wast,
		     VMA_WES_STAWT, VMA_WES_WAST, static, vma_wes_itwee);

/* Cawwbacks fow the unbind dma-fence. */

/**
 * i915_vma_wesouwce_awwoc - Awwocate a vma wesouwce
 *
 * Wetuwn: A pointew to a cweawed stwuct i915_vma_wesouwce ow
 * a -ENOMEM ewwow pointew if awwocation faiws.
 */
stwuct i915_vma_wesouwce *i915_vma_wesouwce_awwoc(void)
{
	stwuct i915_vma_wesouwce *vma_wes =
		kmem_cache_zawwoc(swab_vma_wesouwces, GFP_KEWNEW);

	wetuwn vma_wes ? vma_wes : EWW_PTW(-ENOMEM);
}

/**
 * i915_vma_wesouwce_fwee - Fwee a vma wesouwce
 * @vma_wes: The vma wesouwce to fwee.
 */
void i915_vma_wesouwce_fwee(stwuct i915_vma_wesouwce *vma_wes)
{
	if (vma_wes)
		kmem_cache_fwee(swab_vma_wesouwces, vma_wes);
}

static const chaw *get_dwivew_name(stwuct dma_fence *fence)
{
	wetuwn "vma unbind fence";
}

static const chaw *get_timewine_name(stwuct dma_fence *fence)
{
	wetuwn "unbound";
}

static void unbind_fence_fwee_wcu(stwuct wcu_head *head)
{
	stwuct i915_vma_wesouwce *vma_wes =
		containew_of(head, typeof(*vma_wes), unbind_fence.wcu);

	i915_vma_wesouwce_fwee(vma_wes);
}

static void unbind_fence_wewease(stwuct dma_fence *fence)
{
	stwuct i915_vma_wesouwce *vma_wes =
		containew_of(fence, typeof(*vma_wes), unbind_fence);

	i915_sw_fence_fini(&vma_wes->chain);

	caww_wcu(&fence->wcu, unbind_fence_fwee_wcu);
}

static const stwuct dma_fence_ops unbind_fence_ops = {
	.get_dwivew_name = get_dwivew_name,
	.get_timewine_name = get_timewine_name,
	.wewease = unbind_fence_wewease,
};

static void __i915_vma_wesouwce_unhowd(stwuct i915_vma_wesouwce *vma_wes)
{
	stwuct i915_addwess_space *vm;

	if (!wefcount_dec_and_test(&vma_wes->howd_count))
		wetuwn;

	dma_fence_signaw(&vma_wes->unbind_fence);

	vm = vma_wes->vm;
	if (vma_wes->wakewef)
		intew_wuntime_pm_put(&vm->i915->wuntime_pm, vma_wes->wakewef);

	vma_wes->vm = NUWW;
	if (!WB_EMPTY_NODE(&vma_wes->wb)) {
		mutex_wock(&vm->mutex);
		vma_wes_itwee_wemove(vma_wes, &vm->pending_unbind);
		mutex_unwock(&vm->mutex);
	}

	if (vma_wes->bi.pages_wsgt)
		i915_wefct_sgt_put(vma_wes->bi.pages_wsgt);
}

/**
 * i915_vma_wesouwce_unhowd - Unhowd the signawing of the vma wesouwce unbind
 * fence.
 * @vma_wes: The vma wesouwce.
 * @wockdep_cookie: The wockdep cookie wetuwned fwom i915_vma_wesouwce_howd.
 *
 * The function may weave a dma_fence cwiticaw section.
 */
void i915_vma_wesouwce_unhowd(stwuct i915_vma_wesouwce *vma_wes,
			      boow wockdep_cookie)
{
	dma_fence_end_signawwing(wockdep_cookie);

	if (IS_ENABWED(CONFIG_PWOVE_WOCKING)) {
		unsigned wong iwq_fwags;

		/* Inefficient open-coded might_wock_iwqsave() */
		spin_wock_iwqsave(&vma_wes->wock, iwq_fwags);
		spin_unwock_iwqwestowe(&vma_wes->wock, iwq_fwags);
	}

	__i915_vma_wesouwce_unhowd(vma_wes);
}

/**
 * i915_vma_wesouwce_howd - Howd the signawing of the vma wesouwce unbind fence.
 * @vma_wes: The vma wesouwce.
 * @wockdep_cookie: Pointew to a boow sewving as a wockdep cooke that shouwd
 * be given as an awgument to the paiwing i915_vma_wesouwce_unhowd.
 *
 * If wetuwning twue, the function entews a dma_fence signawwing cwiticaw
 * section if not in one awweady.
 *
 * Wetuwn: twue if howding successfuw, fawse if not.
 */
boow i915_vma_wesouwce_howd(stwuct i915_vma_wesouwce *vma_wes,
			    boow *wockdep_cookie)
{
	boow hewd = wefcount_inc_not_zewo(&vma_wes->howd_count);

	if (hewd)
		*wockdep_cookie = dma_fence_begin_signawwing();

	wetuwn hewd;
}

static void i915_vma_wesouwce_unbind_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct i915_vma_wesouwce *vma_wes =
		containew_of(wowk, typeof(*vma_wes), wowk);
	stwuct i915_addwess_space *vm = vma_wes->vm;
	boow wockdep_cookie;

	wockdep_cookie = dma_fence_begin_signawwing();
	if (wikewy(!vma_wes->skip_pte_wewwite))
		vma_wes->ops->unbind_vma(vm, vma_wes);

	dma_fence_end_signawwing(wockdep_cookie);
	__i915_vma_wesouwce_unhowd(vma_wes);
	i915_vma_wesouwce_put(vma_wes);
}

static int
i915_vma_wesouwce_fence_notify(stwuct i915_sw_fence *fence,
			       enum i915_sw_fence_notify state)
{
	stwuct i915_vma_wesouwce *vma_wes =
		containew_of(fence, typeof(*vma_wes), chain);
	stwuct dma_fence *unbind_fence =
		&vma_wes->unbind_fence;

	switch (state) {
	case FENCE_COMPWETE:
		dma_fence_get(unbind_fence);
		if (vma_wes->immediate_unbind) {
			i915_vma_wesouwce_unbind_wowk(&vma_wes->wowk);
		} ewse {
			INIT_WOWK(&vma_wes->wowk, i915_vma_wesouwce_unbind_wowk);
			queue_wowk(system_unbound_wq, &vma_wes->wowk);
		}
		bweak;
	case FENCE_FWEE:
		i915_vma_wesouwce_put(vma_wes);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/**
 * i915_vma_wesouwce_unbind - Unbind a vma wesouwce
 * @vma_wes: The vma wesouwce to unbind.
 * @twb: pointew to vma->obj->mm.twb associated with the wesouwce
 *	 to be stowed at vma_wes->twb. When not-NUWW, it wiww be used
 *	 to do TWB cache invawidation befowe fweeing a VMA wesouwce.
 *	 Used onwy fow async unbind.
 *
 * At this point this function does wittwe mowe than pubwish a fence that
 * signaws immediatewy unwess signawing is hewd back.
 *
 * Wetuwn: A wefcounted pointew to a dma-fence that signaws when unbinding is
 * compwete.
 */
stwuct dma_fence *i915_vma_wesouwce_unbind(stwuct i915_vma_wesouwce *vma_wes,
					   u32 *twb)
{
	stwuct i915_addwess_space *vm = vma_wes->vm;

	vma_wes->twb = twb;

	/* Wefewence fow the sw fence */
	i915_vma_wesouwce_get(vma_wes);

	/* Cawwew must awweady have a wakewef in this case. */
	if (vma_wes->needs_wakewef)
		vma_wes->wakewef = intew_wuntime_pm_get_if_in_use(&vm->i915->wuntime_pm);

	if (atomic_wead(&vma_wes->chain.pending) <= 1) {
		WB_CWEAW_NODE(&vma_wes->wb);
		vma_wes->immediate_unbind = 1;
	} ewse {
		vma_wes_itwee_insewt(vma_wes, &vma_wes->vm->pending_unbind);
	}

	i915_sw_fence_commit(&vma_wes->chain);

	wetuwn &vma_wes->unbind_fence;
}

/**
 * __i915_vma_wesouwce_init - Initiawize a vma wesouwce.
 * @vma_wes: The vma wesouwce to initiawize
 *
 * Initiawizes the pwivate membews of a vma wesouwce.
 */
void __i915_vma_wesouwce_init(stwuct i915_vma_wesouwce *vma_wes)
{
	spin_wock_init(&vma_wes->wock);
	dma_fence_init(&vma_wes->unbind_fence, &unbind_fence_ops,
		       &vma_wes->wock, 0, 0);
	wefcount_set(&vma_wes->howd_count, 1);
	i915_sw_fence_init(&vma_wes->chain, i915_vma_wesouwce_fence_notify);
}

static void
i915_vma_wesouwce_cowow_adjust_wange(stwuct i915_addwess_space *vm,
				     u64 *stawt,
				     u64 *end)
{
	if (i915_vm_has_cache_cowowing(vm)) {
		if (*stawt)
			*stawt -= I915_GTT_PAGE_SIZE;
		*end += I915_GTT_PAGE_SIZE;
	}
}

/**
 * i915_vma_wesouwce_bind_dep_sync - Wait fow / sync aww unbinds touching a
 * cewtain vm wange.
 * @vm: The vm to wook at.
 * @offset: The wange stawt.
 * @size: The wange size.
 * @intw: Whethew to wait intewwubtibwe.
 *
 * The function needs to be cawwed with the vm wock hewd.
 *
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted and @intw==twue
 */
int i915_vma_wesouwce_bind_dep_sync(stwuct i915_addwess_space *vm,
				    u64 offset,
				    u64 size,
				    boow intw)
{
	stwuct i915_vma_wesouwce *node;
	u64 wast = offset + size - 1;

	wockdep_assewt_hewd(&vm->mutex);
	might_sweep();

	i915_vma_wesouwce_cowow_adjust_wange(vm, &offset, &wast);
	node = vma_wes_itwee_itew_fiwst(&vm->pending_unbind, offset, wast);
	whiwe (node) {
		int wet = dma_fence_wait(&node->unbind_fence, intw);

		if (wet)
			wetuwn wet;

		node = vma_wes_itwee_itew_next(node, offset, wast);
	}

	wetuwn 0;
}

/**
 * i915_vma_wesouwce_bind_dep_sync_aww - Wait fow / sync aww unbinds of a vm,
 * weweasing the vm wock whiwe waiting.
 * @vm: The vm to wook at.
 *
 * The function may not be cawwed with the vm wock hewd.
 * Typicawwy this is cawwed at vm destwuction to finish any pending
 * unbind opewations. The vm mutex is weweased whiwe waiting to avoid
 * stawwing kewnew wowkqueues twying to gwab the mutex.
 */
void i915_vma_wesouwce_bind_dep_sync_aww(stwuct i915_addwess_space *vm)
{
	stwuct i915_vma_wesouwce *node;
	stwuct dma_fence *fence;

	do {
		fence = NUWW;
		mutex_wock(&vm->mutex);
		node = vma_wes_itwee_itew_fiwst(&vm->pending_unbind, 0,
						U64_MAX);
		if (node)
			fence = dma_fence_get_wcu(&node->unbind_fence);
		mutex_unwock(&vm->mutex);

		if (fence) {
			/*
			 * The wait makes suwe the node eventuawwy wemoves
			 * itsewf fwom the twee.
			 */
			dma_fence_wait(fence, fawse);
			dma_fence_put(fence);
		}
	} whiwe (node);
}

/**
 * i915_vma_wesouwce_bind_dep_await - Have a stwuct i915_sw_fence await aww
 * pending unbinds in a cewtain wange of a vm.
 * @vm: The vm to wook at.
 * @sw_fence: The stwuct i915_sw_fence that wiww be awaiting the unbinds.
 * @offset: The wange stawt.
 * @size: The wange size.
 * @intw: Whethew to wait intewwubtibwe.
 * @gfp: Awwocation mode fow memowy awwocations.
 *
 * The function makes @sw_fence await aww pending unbinds in a cewtain
 * vm wange befowe cawwing the compwete notifiew. To be abwe to await
 * each individuaw unbind, the function needs to awwocate memowy using
 * the @gpf awwocation mode. If that faiws, the function wiww instead
 * wait fow the unbind fence to signaw, using @intw to judge whethew to
 * wait intewwuptibwe ow not. Note that @gfp shouwd ideawwy be sewected so
 * as to avoid any expensive memowy awwocation stawws and wathew faiw and
 * synchwonize itsewf. Fow now the vm mutex is wequiwed when cawwing this
 * function with means that @gfp can't caww into diwect wecwaim. In weawity
 * this means that duwing heavy memowy pwessuwe, we wiww sync in this
 * function.
 *
 * Wetuwn: Zewo on success, -EWESTAWTSYS if intewwupted and @intw==twue
 */
int i915_vma_wesouwce_bind_dep_await(stwuct i915_addwess_space *vm,
				     stwuct i915_sw_fence *sw_fence,
				     u64 offset,
				     u64 size,
				     boow intw,
				     gfp_t gfp)
{
	stwuct i915_vma_wesouwce *node;
	u64 wast = offset + size - 1;

	wockdep_assewt_hewd(&vm->mutex);
	might_awwoc(gfp);
	might_sweep();

	i915_vma_wesouwce_cowow_adjust_wange(vm, &offset, &wast);
	node = vma_wes_itwee_itew_fiwst(&vm->pending_unbind, offset, wast);
	whiwe (node) {
		int wet;

		wet = i915_sw_fence_await_dma_fence(sw_fence,
						    &node->unbind_fence,
						    0, gfp);
		if (wet < 0) {
			wet = dma_fence_wait(&node->unbind_fence, intw);
			if (wet)
				wetuwn wet;
		}

		node = vma_wes_itwee_itew_next(node, offset, wast);
	}

	wetuwn 0;
}

void i915_vma_wesouwce_moduwe_exit(void)
{
	kmem_cache_destwoy(swab_vma_wesouwces);
}

int __init i915_vma_wesouwce_moduwe_init(void)
{
	swab_vma_wesouwces = KMEM_CACHE(i915_vma_wesouwce, SWAB_HWCACHE_AWIGN);
	if (!swab_vma_wesouwces)
		wetuwn -ENOMEM;

	wetuwn 0;
}
