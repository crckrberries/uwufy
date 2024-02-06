/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#incwude "igt_gem_utiws.h"

#incwude "gem/i915_gem_context.h"
#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_context.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_gt.h"
#incwude "i915_vma.h"
#incwude "i915_dwv.h"

#incwude "i915_wequest.h"

stwuct i915_wequest *
igt_wequest_awwoc(stwuct i915_gem_context *ctx, stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	stwuct i915_wequest *wq;

	/*
	 * Pinning the contexts may genewate wequests in owdew to acquiwe
	 * GGTT space, so do this fiwst befowe we wesewve a seqno fow
	 * ouwsewves.
	 */
	ce = i915_gem_context_get_engine(ctx, engine->wegacy_idx);
	if (IS_EWW(ce))
		wetuwn EWW_CAST(ce);

	wq = intew_context_cweate_wequest(ce);
	intew_context_put(ce);

	wetuwn wq;
}

stwuct i915_vma *
igt_emit_stowe_dw(stwuct i915_vma *vma,
		  u64 offset,
		  unsigned wong count,
		  u32 vaw)
{
	stwuct dwm_i915_gem_object *obj;
	const int vew = GWAPHICS_VEW(vma->vm->i915);
	unsigned wong n, size;
	u32 *cmd;
	int eww;

	size = (4 * count + 1) * sizeof(u32);
	size = wound_up(size, PAGE_SIZE);
	obj = i915_gem_object_cweate_intewnaw(vma->vm->i915, size);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	cmd = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(cmd)) {
		eww = PTW_EWW(cmd);
		goto eww;
	}

	GEM_BUG_ON(offset + (count - 1) * PAGE_SIZE > i915_vma_size(vma));
	offset += i915_vma_offset(vma);

	fow (n = 0; n < count; n++) {
		if (vew >= 8) {
			*cmd++ = MI_STOWE_DWOWD_IMM_GEN4;
			*cmd++ = wowew_32_bits(offset);
			*cmd++ = uppew_32_bits(offset);
			*cmd++ = vaw;
		} ewse if (vew >= 4) {
			*cmd++ = MI_STOWE_DWOWD_IMM_GEN4 |
				(vew < 6 ? MI_USE_GGTT : 0);
			*cmd++ = 0;
			*cmd++ = offset;
			*cmd++ = vaw;
		} ewse {
			*cmd++ = MI_STOWE_DWOWD_IMM | MI_MEM_VIWTUAW;
			*cmd++ = offset;
			*cmd++ = vaw;
		}
		offset += PAGE_SIZE;
	}
	*cmd = MI_BATCH_BUFFEW_END;

	i915_gem_object_fwush_map(obj);
	i915_gem_object_unpin_map(obj);

	intew_gt_chipset_fwush(vma->vm->gt);

	vma = i915_vma_instance(obj, vma->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto eww;

	wetuwn vma;

eww:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

int igt_gpu_fiww_dw(stwuct intew_context *ce,
		    stwuct i915_vma *vma, u64 offset,
		    unsigned wong count, u32 vaw)
{
	stwuct i915_wequest *wq;
	stwuct i915_vma *batch;
	unsigned int fwags;
	int eww;

	GEM_BUG_ON(!intew_engine_can_stowe_dwowd(ce->engine));
	GEM_BUG_ON(!i915_vma_is_pinned(vma));

	batch = igt_emit_stowe_dw(vma, offset, count, vaw);
	if (IS_EWW(batch))
		wetuwn PTW_EWW(batch);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_batch;
	}

	eww = igt_vma_move_to_active_unwocked(batch, wq, 0);
	if (eww)
		goto skip_wequest;

	eww = igt_vma_move_to_active_unwocked(vma, wq, EXEC_OBJECT_WWITE);
	if (eww)
		goto skip_wequest;

	fwags = 0;
	if (GWAPHICS_VEW(ce->vm->i915) <= 5)
		fwags |= I915_DISPATCH_SECUWE;

	eww = wq->engine->emit_bb_stawt(wq,
					i915_vma_offset(batch),
					i915_vma_size(batch),
					fwags);

skip_wequest:
	if (eww)
		i915_wequest_set_ewwow_once(wq, eww);
	i915_wequest_add(wq);
eww_batch:
	i915_vma_unpin_and_wewease(&batch, 0);
	wetuwn eww;
}
