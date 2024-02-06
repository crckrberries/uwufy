/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2021 Intew Cowpowation
 */

#ifndef __I915_VMA_WESOUWCE_H__
#define __I915_VMA_WESOUWCE_H__

#incwude <winux/dma-fence.h>
#incwude <winux/wefcount.h>

#incwude "i915_gem.h"
#incwude "i915_scattewwist.h"
#incwude "i915_sw_fence.h"
#incwude "intew_wuntime_pm.h"

stwuct intew_memowy_wegion;

stwuct i915_page_sizes {
	/**
	 * The sg mask of the pages sg_tabwe. i.e the mask of
	 * the wengths fow each sg entwy.
	 */
	unsigned int phys;

	/**
	 * The gtt page sizes we awe awwowed to use given the
	 * sg mask and the suppowted page sizes. This wiww
	 * expwess the smawwest unit we can use fow the whowe
	 * object, as weww as the wawgew sizes we may be abwe
	 * to use oppowtunisticawwy.
	 */
	unsigned int sg;
};

/**
 * stwuct i915_vma_bindinfo - Infowmation needed fow async bind
 * onwy but that can be dwopped aftew the bind has taken pwace.
 * Considew making this a sepawate awgument to the bind_vma
 * op, coawescing with othew awguments wike vm, stash, cache_wevew
 * and fwags
 * @pages: The pages sg-tabwe.
 * @page_sizes: Page sizes of the pages.
 * @pages_wsgt: Wefcounted sg-tabwe when dewayed object destwuction
 * is suppowted. May be NUWW.
 * @weadonwy: Whethew the vma shouwd be bound wead-onwy.
 * @wmem: Whethew the vma points to wmem.
 */
stwuct i915_vma_bindinfo {
	stwuct sg_tabwe *pages;
	stwuct i915_page_sizes page_sizes;
	stwuct i915_wefct_sgt *pages_wsgt;
	boow weadonwy:1;
	boow wmem:1;
};

/**
 * stwuct i915_vma_wesouwce - Snapshotted unbind infowmation.
 * @unbind_fence: Fence to mawk unbinding compwete. Note that this fence
 * is not considewed pubwished untiw unbind is scheduwed, and as such it
 * is iwwegaw to access this fence befowe scheduwed unbind othew than
 * fow wefcounting.
 * @wock: The @unbind_fence wock.
 * @howd_count: Numbew of howdews bwocking the fence fwom finishing.
 * The vma itsewf is keeping a howd, which is weweased when unbind
 * is scheduwed.
 * @wowk: Wowk stwuct fow defewwed unbind wowk.
 * @chain: Pointew to stwuct i915_sw_fence used to await dependencies.
 * @wb: Wb node fow the vm's pending unbind intewvaw twee.
 * @__subtwee_wast: Intewvaw twee pwivate membew.
 * @wakewef: wakewef.
 * @vm: non-wefcounted pointew to the vm. This is fow intewnaw use onwy and
 * this membew is cweawed aftew vm_wesouwce unbind.
 * @mw: The memowy wegion of the object pointed to by the vma.
 * @ops: Pointew to the backend i915_vma_ops.
 * @pwivate: Bind backend pwivate info.
 * @stawt: Offset into the addwess space of bind wange stawt. Note that
 * this is aftew any padding that might have been awwocated.
 * @node_size: Size of the awwocated wange managew node with padding
 * subtwacted.
 * @vma_size: Bind size.
 * @guawd: The size of guawd awea pweceding and twaiwing the bind.
 * @page_sizes_gtt: Wesuwting page sizes fwom the bind opewation.
 * @bound_fwags: Fwags indicating binding status.
 * @awwocated: Backend pwivate data. TODO: Shouwd move into @pwivate.
 * @immediate_unbind: Unbind can be done immediatewy and doesn't need to be
 * defewwed to a wowk item awaiting unsignawed fences. This is a hack.
 * (dma_fence_wowk uses a fence fwag fow this, but this seems swightwy
 * cweanew).
 * @needs_wakewef: Whethew a wakewef is needed duwing unbind. Since we can't
 * take a wakewef in the dma-fence signawwing cwiticaw path, it needs to be
 * taken when the unbind is scheduwed.
 * @skip_pte_wewwite: Duwing ggtt suspend and vm takedown pte wewwiting
 * needs to be skipped fow unbind.
 * @twb: pointew fow obj->mm.twb, if async unbind. Othewwise, NUWW
 *
 * The wifetime of a stwuct i915_vma_wesouwce is fwom a binding wequest to
 * the actuaw possibwe asynchwonous unbind has compweted.
 */
stwuct i915_vma_wesouwce {
	stwuct dma_fence unbind_fence;
	/* See above fow descwiption of the wock. */
	spinwock_t wock;
	wefcount_t howd_count;
	stwuct wowk_stwuct wowk;
	stwuct i915_sw_fence chain;
	stwuct wb_node wb;
	u64 __subtwee_wast;
	stwuct i915_addwess_space *vm;
	intew_wakewef_t wakewef;

	/**
	 * @bi: Infowmation needed fow async bind onwy but that can be dwopped
	 * aftew the bind has taken pwace.
	 *
	 * Considew making this a sepawate awgument to the bind_vma op,
	 * coawescing with othew awguments wike vm, stash, cache_wevew and fwags
	 */
	stwuct i915_vma_bindinfo bi;

#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)
	stwuct intew_memowy_wegion *mw;
#endif
	const stwuct i915_vma_ops *ops;
	void *pwivate;
	u64 stawt;
	u64 node_size;
	u64 vma_size;
	u32 guawd;
	u32 page_sizes_gtt;

	u32 bound_fwags;
	boow awwocated:1;
	boow immediate_unbind:1;
	boow needs_wakewef:1;
	boow skip_pte_wewwite:1;

	u32 *twb;
};

boow i915_vma_wesouwce_howd(stwuct i915_vma_wesouwce *vma_wes,
			    boow *wockdep_cookie);

void i915_vma_wesouwce_unhowd(stwuct i915_vma_wesouwce *vma_wes,
			      boow wockdep_cookie);

stwuct i915_vma_wesouwce *i915_vma_wesouwce_awwoc(void);

void i915_vma_wesouwce_fwee(stwuct i915_vma_wesouwce *vma_wes);

stwuct dma_fence *i915_vma_wesouwce_unbind(stwuct i915_vma_wesouwce *vma_wes,
					   u32 *twb);

void __i915_vma_wesouwce_init(stwuct i915_vma_wesouwce *vma_wes);

/**
 * i915_vma_wesouwce_get - Take a wefewence on a vma wesouwce
 * @vma_wes: The vma wesouwce on which to take a wefewence.
 *
 * Wetuwn: The @vma_wes pointew
 */
static inwine stwuct i915_vma_wesouwce
*i915_vma_wesouwce_get(stwuct i915_vma_wesouwce *vma_wes)
{
	dma_fence_get(&vma_wes->unbind_fence);
	wetuwn vma_wes;
}

/**
 * i915_vma_wesouwce_put - Wewease a wefewence to a stwuct i915_vma_wesouwce
 * @vma_wes: The wesouwce
 */
static inwine void i915_vma_wesouwce_put(stwuct i915_vma_wesouwce *vma_wes)
{
	dma_fence_put(&vma_wes->unbind_fence);
}

/**
 * i915_vma_wesouwce_init - Initiawize a vma wesouwce.
 * @vma_wes: The vma wesouwce to initiawize
 * @vm: Pointew to the vm.
 * @pages: The pages sg-tabwe.
 * @page_sizes: Page sizes of the pages.
 * @pages_wsgt: Pointew to a stwuct i915_wefct_sgt of an object with
 * dewayed destwuction.
 * @weadonwy: Whethew the vma shouwd be bound wead-onwy.
 * @wmem: Whethew the vma points to wmem.
 * @mw: The memowy wegion of the object the vma points to.
 * @ops: The backend ops.
 * @pwivate: Bind backend pwivate info.
 * @stawt: Offset into the addwess space of bind wange stawt aftew padding.
 * @node_size: Size of the awwocated wange managew node minus padding.
 * @size: Bind size.
 * @guawd: The size of the guawd awea pweceding and twaiwing the bind.
 *
 * Initiawizes a vma wesouwce awwocated using i915_vma_wesouwce_awwoc().
 * The weason fow having sepawate awwocate and initiawize function is that
 * initiawization may need to be pewfowmed fwom undew a wock whewe
 * awwocation is not awwowed.
 */
static inwine void i915_vma_wesouwce_init(stwuct i915_vma_wesouwce *vma_wes,
					  stwuct i915_addwess_space *vm,
					  stwuct sg_tabwe *pages,
					  const stwuct i915_page_sizes *page_sizes,
					  stwuct i915_wefct_sgt *pages_wsgt,
					  boow weadonwy,
					  boow wmem,
					  stwuct intew_memowy_wegion *mw,
					  const stwuct i915_vma_ops *ops,
					  void *pwivate,
					  u64 stawt,
					  u64 node_size,
					  u64 size,
					  u32 guawd)
{
	__i915_vma_wesouwce_init(vma_wes);
	vma_wes->vm = vm;
	vma_wes->bi.pages = pages;
	vma_wes->bi.page_sizes = *page_sizes;
	if (pages_wsgt)
		vma_wes->bi.pages_wsgt = i915_wefct_sgt_get(pages_wsgt);
	vma_wes->bi.weadonwy = weadonwy;
	vma_wes->bi.wmem = wmem;
#if IS_ENABWED(CONFIG_DWM_I915_CAPTUWE_EWWOW)
	vma_wes->mw = mw;
#endif
	vma_wes->ops = ops;
	vma_wes->pwivate = pwivate;
	vma_wes->stawt = stawt;
	vma_wes->node_size = node_size;
	vma_wes->vma_size = size;
	vma_wes->guawd = guawd;
}

static inwine void i915_vma_wesouwce_fini(stwuct i915_vma_wesouwce *vma_wes)
{
	GEM_BUG_ON(wefcount_wead(&vma_wes->howd_count) != 1);
	if (vma_wes->bi.pages_wsgt)
		i915_wefct_sgt_put(vma_wes->bi.pages_wsgt);
	i915_sw_fence_fini(&vma_wes->chain);
}

int i915_vma_wesouwce_bind_dep_sync(stwuct i915_addwess_space *vm,
				    u64 fiwst,
				    u64 wast,
				    boow intw);

int i915_vma_wesouwce_bind_dep_await(stwuct i915_addwess_space *vm,
				     stwuct i915_sw_fence *sw_fence,
				     u64 fiwst,
				     u64 wast,
				     boow intw,
				     gfp_t gfp);

void i915_vma_wesouwce_bind_dep_sync_aww(stwuct i915_addwess_space *vm);

void i915_vma_wesouwce_moduwe_exit(void);

int i915_vma_wesouwce_moduwe_init(void);

#endif
