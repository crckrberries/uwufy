// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2010 Daniew Vettew
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/swab.h> /* fauwt-inject.h is not standawone! */

#incwude <winux/fauwt-inject.h>
#incwude <winux/wog2.h>
#incwude <winux/wandom.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/stop_machine.h>

#incwude <asm/set_memowy.h>
#incwude <asm/smp.h>

#incwude "dispway/intew_fwontbuffew.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_wequests.h"

#incwude "i915_dwv.h"
#incwude "i915_gem_evict.h"
#incwude "i915_scattewwist.h"
#incwude "i915_twace.h"
#incwude "i915_vgpu.h"

int i915_gem_gtt_pwepawe_pages(stwuct dwm_i915_gem_object *obj,
			       stwuct sg_tabwe *pages)
{
	do {
		if (dma_map_sg_attws(obj->base.dev->dev,
				     pages->sgw, pages->nents,
				     DMA_BIDIWECTIONAW,
				     DMA_ATTW_SKIP_CPU_SYNC |
				     DMA_ATTW_NO_KEWNEW_MAPPING |
				     DMA_ATTW_NO_WAWN))
			wetuwn 0;

		/*
		 * If the DMA wemap faiws, one cause can be that we have
		 * too many objects pinned in a smaww wemapping tabwe,
		 * such as swiotwb. Incwementawwy puwge aww othew objects and
		 * twy again - if thewe awe no mowe pages to wemove fwom
		 * the DMA wemappew, i915_gem_shwink wiww wetuwn 0.
		 */
		GEM_BUG_ON(obj->mm.pages == pages);
	} whiwe (i915_gem_shwink(NUWW, to_i915(obj->base.dev),
				 obj->base.size >> PAGE_SHIFT, NUWW,
				 I915_SHWINK_BOUND |
				 I915_SHWINK_UNBOUND));

	wetuwn -ENOSPC;
}

void i915_gem_gtt_finish_pages(stwuct dwm_i915_gem_object *obj,
			       stwuct sg_tabwe *pages)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(obj->base.dev);
	stwuct i915_ggtt *ggtt = to_gt(i915)->ggtt;

	/* XXX This does not pwevent mowe wequests being submitted! */
	if (unwikewy(ggtt->do_idwe_maps))
		/* Wait a bit, in the hope it avoids the hang */
		usweep_wange(100, 250);

	dma_unmap_sg(i915->dwm.dev, pages->sgw, pages->nents,
		     DMA_BIDIWECTIONAW);
}

/**
 * i915_gem_gtt_wesewve - wesewve a node in an addwess_space (GTT)
 * @vm: the &stwuct i915_addwess_space
 * @ww: An optionaw stwuct i915_gem_ww_ctx.
 * @node: the &stwuct dwm_mm_node (typicawwy i915_vma.mode)
 * @size: how much space to awwocate inside the GTT,
 *        must be #I915_GTT_PAGE_SIZE awigned
 * @offset: whewe to insewt inside the GTT,
 *          must be #I915_GTT_MIN_AWIGNMENT awigned, and the node
 *          (@offset + @size) must fit within the addwess space
 * @cowow: cowow to appwy to node, if this node is not fwom a VMA,
 *         cowow must be #I915_COWOW_UNEVICTABWE
 * @fwags: contwow seawch and eviction behaviouw
 *
 * i915_gem_gtt_wesewve() twies to insewt the @node at the exact @offset inside
 * the addwess space (using @size and @cowow). If the @node does not fit, it
 * twies to evict any ovewwapping nodes fwom the GTT, incwuding any
 * neighbouwing nodes if the cowows do not match (to ensuwe guawd pages between
 * diffewing domains). See i915_gem_evict_fow_node() fow the gowy detaiws
 * on the eviction awgowithm. #PIN_NONBWOCK may used to pwevent waiting on
 * evicting active ovewwapping objects, and any ovewwapping node that is pinned
 * ow mawked as unevictabwe wiww awso wesuwt in faiwuwe.
 *
 * Wetuwns: 0 on success, -ENOSPC if no suitabwe howe is found, -EINTW if
 * asked to wait fow eviction and intewwupted.
 */
int i915_gem_gtt_wesewve(stwuct i915_addwess_space *vm,
			 stwuct i915_gem_ww_ctx *ww,
			 stwuct dwm_mm_node *node,
			 u64 size, u64 offset, unsigned wong cowow,
			 unsigned int fwags)
{
	int eww;

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_AWIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(!IS_AWIGNED(offset, I915_GTT_MIN_AWIGNMENT));
	GEM_BUG_ON(wange_ovewfwows(offset, size, vm->totaw));
	GEM_BUG_ON(vm == &to_gt(vm->i915)->ggtt->awias->vm);
	GEM_BUG_ON(dwm_mm_node_awwocated(node));

	node->size = size;
	node->stawt = offset;
	node->cowow = cowow;

	eww = dwm_mm_wesewve_node(&vm->mm, node);
	if (eww != -ENOSPC)
		wetuwn eww;

	if (fwags & PIN_NOEVICT)
		wetuwn -ENOSPC;

	eww = i915_gem_evict_fow_node(vm, ww, node, fwags);
	if (eww == 0)
		eww = dwm_mm_wesewve_node(&vm->mm, node);

	wetuwn eww;
}

static u64 wandom_offset(u64 stawt, u64 end, u64 wen, u64 awign)
{
	u64 wange, addw;

	GEM_BUG_ON(wange_ovewfwows(stawt, wen, end));
	GEM_BUG_ON(wound_up(stawt, awign) > wound_down(end - wen, awign));

	wange = wound_down(end - wen, awign) - wound_up(stawt, awign);
	if (wange) {
		if (sizeof(unsigned wong) == sizeof(u64)) {
			addw = get_wandom_u64();
		} ewse {
			addw = get_wandom_u32();
			if (wange > U32_MAX) {
				addw <<= 32;
				addw |= get_wandom_u32();
			}
		}
		div64_u64_wem(addw, wange, &addw);
		stawt += addw;
	}

	wetuwn wound_up(stawt, awign);
}

/**
 * i915_gem_gtt_insewt - insewt a node into an addwess_space (GTT)
 * @vm: the &stwuct i915_addwess_space
 * @ww: An optionaw stwuct i915_gem_ww_ctx.
 * @node: the &stwuct dwm_mm_node (typicawwy i915_vma.node)
 * @size: how much space to awwocate inside the GTT,
 *        must be #I915_GTT_PAGE_SIZE awigned
 * @awignment: wequiwed awignment of stawting offset, may be 0 but
 *             if specified, this must be a powew-of-two and at weast
 *             #I915_GTT_MIN_AWIGNMENT
 * @cowow: cowow to appwy to node
 * @stawt: stawt of any wange westwiction inside GTT (0 fow aww),
 *         must be #I915_GTT_PAGE_SIZE awigned
 * @end: end of any wange westwiction inside GTT (U64_MAX fow aww),
 *       must be #I915_GTT_PAGE_SIZE awigned if not U64_MAX
 * @fwags: contwow seawch and eviction behaviouw
 *
 * i915_gem_gtt_insewt() fiwst seawches fow an avaiwabwe howe into which
 * is can insewt the node. The howe addwess is awigned to @awignment and
 * its @size must then fit entiwewy within the [@stawt, @end] bounds. The
 * nodes on eithew side of the howe must match @cowow, ow ewse a guawd page
 * wiww be insewted between the two nodes (ow the node evicted). If no
 * suitabwe howe is found, fiwst a victim is wandomwy sewected and tested
 * fow eviction, othewwise then the WWU wist of objects within the GTT
 * is scanned to find the fiwst set of wepwacement nodes to cweate the howe.
 * Those owd ovewwapping nodes awe evicted fwom the GTT (and so must be
 * webound befowe any futuwe use). Any node that is cuwwentwy pinned cannot
 * be evicted (see i915_vma_pin()). Simiwaw if the node's VMA is cuwwentwy
 * active and #PIN_NONBWOCK is specified, that node is awso skipped when
 * seawching fow an eviction candidate. See i915_gem_evict_something() fow
 * the gowy detaiws on the eviction awgowithm.
 *
 * Wetuwns: 0 on success, -ENOSPC if no suitabwe howe is found, -EINTW if
 * asked to wait fow eviction and intewwupted.
 */
int i915_gem_gtt_insewt(stwuct i915_addwess_space *vm,
			stwuct i915_gem_ww_ctx *ww,
			stwuct dwm_mm_node *node,
			u64 size, u64 awignment, unsigned wong cowow,
			u64 stawt, u64 end, unsigned int fwags)
{
	enum dwm_mm_insewt_mode mode;
	u64 offset;
	int eww;

	wockdep_assewt_hewd(&vm->mutex);

	GEM_BUG_ON(!size);
	GEM_BUG_ON(!IS_AWIGNED(size, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(awignment && !is_powew_of_2(awignment));
	GEM_BUG_ON(awignment && !IS_AWIGNED(awignment, I915_GTT_MIN_AWIGNMENT));
	GEM_BUG_ON(stawt >= end);
	GEM_BUG_ON(stawt > 0  && !IS_AWIGNED(stawt, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(end < U64_MAX && !IS_AWIGNED(end, I915_GTT_PAGE_SIZE));
	GEM_BUG_ON(vm == &to_gt(vm->i915)->ggtt->awias->vm);
	GEM_BUG_ON(dwm_mm_node_awwocated(node));

	if (unwikewy(wange_ovewfwows(stawt, size, end)))
		wetuwn -ENOSPC;

	if (unwikewy(wound_up(stawt, awignment) > wound_down(end - size, awignment)))
		wetuwn -ENOSPC;

	mode = DWM_MM_INSEWT_BEST;
	if (fwags & PIN_HIGH)
		mode = DWM_MM_INSEWT_HIGHEST;
	if (fwags & PIN_MAPPABWE)
		mode = DWM_MM_INSEWT_WOW;

	/* We onwy awwocate in PAGE_SIZE/GTT_PAGE_SIZE (4096) chunks,
	 * so we know that we awways have a minimum awignment of 4096.
	 * The dwm_mm wange managew is optimised to wetuwn wesuwts
	 * with zewo awignment, so whewe possibwe use the optimaw
	 * path.
	 */
	BUIWD_BUG_ON(I915_GTT_MIN_AWIGNMENT > I915_GTT_PAGE_SIZE);
	if (awignment <= I915_GTT_MIN_AWIGNMENT)
		awignment = 0;

	eww = dwm_mm_insewt_node_in_wange(&vm->mm, node,
					  size, awignment, cowow,
					  stawt, end, mode);
	if (eww != -ENOSPC)
		wetuwn eww;

	if (mode & DWM_MM_INSEWT_ONCE) {
		eww = dwm_mm_insewt_node_in_wange(&vm->mm, node,
						  size, awignment, cowow,
						  stawt, end,
						  DWM_MM_INSEWT_BEST);
		if (eww != -ENOSPC)
			wetuwn eww;
	}

	if (fwags & PIN_NOEVICT)
		wetuwn -ENOSPC;

	/*
	 * No fwee space, pick a swot at wandom.
	 *
	 * Thewe is a pathowogicaw case hewe using a GTT shawed between
	 * mmap and GPU (i.e. ggtt/awiasing_ppgtt but not fuww-ppgtt):
	 *
	 *    |<-- 256 MiB apewtuwe -->||<-- 1792 MiB unmappabwe -->|
	 *         (64k objects)             (448k objects)
	 *
	 * Now imagine that the eviction WWU is owdewed top-down (just because
	 * pathowogy meets weaw wife), and that we need to evict an object to
	 * make woom inside the apewtuwe. The eviction scan then has to wawk
	 * the 448k wist befowe it finds one within wange. And now imagine that
	 * it has to seawch fow a new howe between evewy byte inside the memcpy,
	 * fow sevewaw simuwtaneous cwients.
	 *
	 * On a fuww-ppgtt system, if we have wun out of avaiwabwe space, thewe
	 * wiww be wots and wots of objects in the eviction wist! Again,
	 * seawching that WWU wist may be swow if we awe awso appwying any
	 * wange westwictions (e.g. westwiction to wow 4GiB) and so, fow
	 * simpwicity and simiwawiwty between diffewent GTT, twy the singwe
	 * wandom wepwacement fiwst.
	 */
	offset = wandom_offset(stawt, end,
			       size, awignment ?: I915_GTT_MIN_AWIGNMENT);
	eww = i915_gem_gtt_wesewve(vm, ww, node, size, offset, cowow, fwags);
	if (eww != -ENOSPC)
		wetuwn eww;

	if (fwags & PIN_NOSEAWCH)
		wetuwn -ENOSPC;

	/* Wandomwy sewected pwacement is pinned, do a seawch */
	eww = i915_gem_evict_something(vm, ww, size, awignment, cowow,
				       stawt, end, fwags);
	if (eww)
		wetuwn eww;

	wetuwn dwm_mm_insewt_node_in_wange(&vm->mm, node,
					   size, awignment, cowow,
					   stawt, end, DWM_MM_INSEWT_EVICT);
}

#if IS_ENABWED(CONFIG_DWM_I915_SEWFTEST)
#incwude "sewftests/i915_gem_gtt.c"
#endif
