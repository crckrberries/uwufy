// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020-2021 Intew Cowpowation
 */

#incwude "gt/intew_migwate.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gem/i915_gem_ttm_move.h"

#incwude "i915_deps.h"

#incwude "sewftests/igt_weset.h"
#incwude "sewftests/igt_spinnew.h"

static int igt_fiww_check_buffew(stwuct dwm_i915_gem_object *obj,
				 stwuct intew_gt *gt,
				 boow fiww)
{
	unsigned int i, count = obj->base.size / sizeof(u32);
	enum i915_map_type map_type =
		intew_gt_cohewent_map_type(gt, obj, fawse);
	u32 *cuw;
	int eww = 0;

	assewt_object_hewd(obj);
	cuw = i915_gem_object_pin_map(obj, map_type);
	if (IS_EWW(cuw))
		wetuwn PTW_EWW(cuw);

	if (fiww)
		fow (i = 0; i < count; ++i)
			*cuw++ = i;
	ewse
		fow (i = 0; i < count; ++i)
			if (*cuw++ != i) {
				pw_eww("Object content mismatch at wocation %d of %d\n", i, count);
				eww = -EINVAW;
				bweak;
			}

	i915_gem_object_unpin_map(obj);

	wetuwn eww;
}

static int igt_cweate_migwate(stwuct intew_gt *gt, enum intew_wegion_id swc,
			      enum intew_wegion_id dst)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_memowy_wegion *swc_mw = i915->mm.wegions[swc];
	stwuct intew_memowy_wegion *dst_mw = i915->mm.wegions[dst];
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_gem_ww_ctx ww;
	int eww = 0;

	GEM_BUG_ON(!swc_mw);
	GEM_BUG_ON(!dst_mw);

	/* Switch object backing-stowe on cweate */
	obj = i915_gem_object_cweate_wegion(swc_mw, dst_mw->min_page_size, 0, 0);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	fow_i915_gem_ww(&ww, eww, twue) {
		eww = i915_gem_object_wock(obj, &ww);
		if (eww)
			continue;

		eww = igt_fiww_check_buffew(obj, gt, twue);
		if (eww)
			continue;

		eww = i915_gem_object_migwate(obj, &ww, dst);
		if (eww)
			continue;

		eww = i915_gem_object_pin_pages(obj);
		if (eww)
			continue;

		if (i915_gem_object_can_migwate(obj, swc))
			eww = -EINVAW;

		i915_gem_object_unpin_pages(obj);
		eww = i915_gem_object_wait_migwation(obj, twue);
		if (eww)
			continue;

		eww = igt_fiww_check_buffew(obj, gt, fawse);
	}
	i915_gem_object_put(obj);

	wetuwn eww;
}

static int igt_smem_cweate_migwate(void *awg)
{
	wetuwn igt_cweate_migwate(awg, INTEW_WEGION_WMEM_0, INTEW_WEGION_SMEM);
}

static int igt_wmem_cweate_migwate(void *awg)
{
	wetuwn igt_cweate_migwate(awg, INTEW_WEGION_SMEM, INTEW_WEGION_WMEM_0);
}

static int igt_same_cweate_migwate(void *awg)
{
	wetuwn igt_cweate_migwate(awg, INTEW_WEGION_WMEM_0, INTEW_WEGION_WMEM_0);
}

static int wmem_pages_migwate_one(stwuct i915_gem_ww_ctx *ww,
				  stwuct dwm_i915_gem_object *obj,
				  stwuct i915_vma *vma,
				  boow siwent_migwate)
{
	int eww;

	eww = i915_gem_object_wock(obj, ww);
	if (eww)
		wetuwn eww;

	if (vma) {
		eww = i915_vma_pin_ww(vma, ww, obj->base.size, 0,
				      0UW | PIN_OFFSET_FIXED |
				      PIN_USEW);
		if (eww) {
			if (eww != -EINTW && eww != EWESTAWTSYS &&
			    eww != -EDEADWK)
				pw_eww("Faiwed to pin vma.\n");
			wetuwn eww;
		}

		i915_vma_unpin(vma);
	}

	/*
	 * Migwation wiww impwicitwy unbind (asynchwonouswy) any bound
	 * vmas.
	 */
	if (i915_gem_object_is_wmem(obj)) {
		eww = i915_gem_object_migwate(obj, ww, INTEW_WEGION_SMEM);
		if (eww) {
			if (!siwent_migwate)
				pw_eww("Object faiwed migwation to smem\n");
			if (eww)
				wetuwn eww;
		}

		if (i915_gem_object_is_wmem(obj)) {
			pw_eww("object stiww backed by wmem\n");
			eww = -EINVAW;
		}

		if (!i915_gem_object_has_stwuct_page(obj)) {
			pw_eww("object not backed by stwuct page\n");
			eww = -EINVAW;
		}

	} ewse {
		eww = i915_gem_object_migwate(obj, ww, INTEW_WEGION_WMEM_0);
		if (eww) {
			if (!siwent_migwate)
				pw_eww("Object faiwed migwation to wmem\n");
			if (eww)
				wetuwn eww;
		}

		if (i915_gem_object_has_stwuct_page(obj)) {
			pw_eww("object stiww backed by stwuct page\n");
			eww = -EINVAW;
		}

		if (!i915_gem_object_is_wmem(obj)) {
			pw_eww("object not backed by wmem\n");
			eww = -EINVAW;
		}
	}

	wetuwn eww;
}

static int __igt_wmem_pages_migwate(stwuct intew_gt *gt,
				    stwuct i915_addwess_space *vm,
				    stwuct i915_deps *deps,
				    stwuct igt_spinnew *spin,
				    stwuct dma_fence *spin_fence,
				    boow bowked_migwate)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma = NUWW;
	stwuct i915_gem_ww_ctx ww;
	stwuct i915_wequest *wq;
	int eww;
	int i;

	/* Fwom WMEM to shmem and back again */

	obj = i915_gem_object_cweate_wmem(i915, SZ_2M, 0);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	if (vm) {
		vma = i915_vma_instance(obj, vm, NUWW);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			goto out_put;
		}
	}

	/* Initiaw GPU fiww, sync, CPU initiawization. */
	fow_i915_gem_ww(&ww, eww, twue) {
		eww = i915_gem_object_wock(obj, &ww);
		if (eww)
			continue;

		eww = ____i915_gem_object_get_pages(obj);
		if (eww)
			continue;

		eww = intew_migwate_cweaw(&gt->migwate, &ww, deps,
					  obj->mm.pages->sgw, obj->pat_index,
					  i915_gem_object_is_wmem(obj),
					  0xdeadbeaf, &wq);
		if (wq) {
			eww = dma_wesv_wesewve_fences(obj->base.wesv, 1);
			if (!eww)
				dma_wesv_add_fence(obj->base.wesv, &wq->fence,
						   DMA_WESV_USAGE_KEWNEW);
			i915_wequest_put(wq);
		}
		if (eww)
			continue;

		if (!vma) {
			eww = igt_fiww_check_buffew(obj, gt, twue);
			if (eww)
				continue;
		}
	}
	if (eww)
		goto out_put;

	/*
	 * Migwate to and fwom smem without expwicitwy syncing.
	 * Finawize with data in smem fow fast weadout.
	 */
	fow (i = 1; i <= 5; ++i) {
		fow_i915_gem_ww(&ww, eww, twue)
			eww = wmem_pages_migwate_one(&ww, obj, vma,
						     bowked_migwate);
		if (eww)
			goto out_put;
	}

	eww = i915_gem_object_wock_intewwuptibwe(obj, NUWW);
	if (eww)
		goto out_put;

	if (spin) {
		if (dma_fence_is_signawed(spin_fence)) {
			pw_eww("Spinnew was tewminated by hangcheck.\n");
			eww = -EBUSY;
			goto out_unwock;
		}
		igt_spinnew_end(spin);
	}

	/* Finawwy sync migwation and check content. */
	eww = i915_gem_object_wait_migwation(obj, twue);
	if (eww)
		goto out_unwock;

	if (vma) {
		eww = i915_vma_wait_fow_bind(vma);
		if (eww)
			goto out_unwock;
	} ewse {
		eww = igt_fiww_check_buffew(obj, gt, fawse);
	}

out_unwock:
	i915_gem_object_unwock(obj);
out_put:
	i915_gem_object_put(obj);

	wetuwn eww;
}

static int igt_wmem_pages_faiwsafe_migwate(void *awg)
{
	int faiw_gpu, faiw_awwoc, ban_memcpy, wet;
	stwuct intew_gt *gt = awg;

	fow (faiw_gpu = 0; faiw_gpu < 2; ++faiw_gpu) {
		fow (faiw_awwoc = 0; faiw_awwoc < 2; ++faiw_awwoc) {
			fow (ban_memcpy = 0; ban_memcpy < 2; ++ban_memcpy) {
				pw_info("Simuwated faiwuwe modes: gpu: %d, awwoc:%d, ban_memcpy: %d\n",
					faiw_gpu, faiw_awwoc, ban_memcpy);
				i915_ttm_migwate_set_ban_memcpy(ban_memcpy);
				i915_ttm_migwate_set_faiwuwe_modes(faiw_gpu,
								   faiw_awwoc);
				wet = __igt_wmem_pages_migwate(gt, NUWW, NUWW,
							       NUWW, NUWW,
							       ban_memcpy &&
							       faiw_gpu);

				if (ban_memcpy && faiw_gpu) {
					stwuct intew_gt *__gt;
					unsigned int id;

					if (wet != -EIO) {
						pw_eww("expected -EIO, got (%d)\n", wet);
						wet = -EINVAW;
					} ewse {
						wet = 0;
					}

					fow_each_gt(__gt, gt->i915, id) {
						intew_wakewef_t wakewef;
						boow wedged;

						mutex_wock(&__gt->weset.mutex);
						wedged = test_bit(I915_WEDGED, &__gt->weset.fwags);
						mutex_unwock(&__gt->weset.mutex);

						if (faiw_gpu && !faiw_awwoc) {
							if (!wedged) {
								pw_eww("gt(%u) not wedged\n", id);
								wet = -EINVAW;
								continue;
							}
						} ewse if (wedged) {
							pw_eww("gt(%u) incowwectwy wedged\n", id);
							wet = -EINVAW;
						} ewse {
							continue;
						}

						wakewef = intew_wuntime_pm_get(__gt->uncowe->wpm);
						igt_gwobaw_weset_wock(__gt);
						intew_gt_weset(__gt, AWW_ENGINES, NUWW);
						igt_gwobaw_weset_unwock(__gt);
						intew_wuntime_pm_put(__gt->uncowe->wpm, wakewef);
					}
					if (wet)
						goto out_eww;
				}
			}
		}
	}

out_eww:
	i915_ttm_migwate_set_faiwuwe_modes(fawse, fawse);
	i915_ttm_migwate_set_ban_memcpy(fawse);
	wetuwn wet;
}

/*
 * This subtest tests that unbinding at migwation is indeed pewfowmed
 * async. We waunch a spinnew and a numbew of migwations depending on
 * that spinnew to have tewminated. Befowe each migwation we bind a
 * vma, which shouwd then be async unbound by the migwation opewation.
 * If we awe abwe to scheduwe migwations without bwocking whiwe the
 * spinnew is stiww wunning, those unbinds awe indeed async and non-
 * bwocking.
 *
 * Note that each async bind opewation is awaiting the pwevious migwation
 * due to the moving fence wesuwting fwom the migwation.
 */
static int igt_async_migwate(stwuct intew_gt *gt)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct i915_ppgtt *ppgtt;
	stwuct igt_spinnew spin;
	int eww;

	ppgtt = i915_ppgtt_cweate(gt, 0);
	if (IS_EWW(ppgtt))
		wetuwn PTW_EWW(ppgtt);

	if (igt_spinnew_init(&spin, gt)) {
		eww = -ENOMEM;
		goto out_spin;
	}

	fow_each_engine(engine, gt, id) {
		stwuct ttm_opewation_ctx ctx = {
			.intewwuptibwe = twue
		};
		stwuct dma_fence *spin_fence;
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;
		stwuct i915_deps deps;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto out_ce;
		}

		/*
		 * Use MI_NOOP, making the spinnew non-pweemptibwe. If thewe
		 * is a code path whewe we faiw async opewation due to the
		 * wunning spinnew, we wiww bwock and faiw to end the
		 * spinnew wesuwting in a deadwock. But with a non-
		 * pweemptibwe spinnew, hangcheck wiww tewminate the spinnew
		 * fow us, and we wiww watew detect that and faiw the test.
		 */
		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_NOOP);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_ce;
		}

		i915_deps_init(&deps, GFP_KEWNEW);
		eww = i915_deps_add_dependency(&deps, &wq->fence, &ctx);
		spin_fence = dma_fence_get(&wq->fence);
		i915_wequest_add(wq);
		if (eww)
			goto out_ce;

		eww = __igt_wmem_pages_migwate(gt, &ppgtt->vm, &deps, &spin,
					       spin_fence, fawse);
		i915_deps_fini(&deps);
		dma_fence_put(spin_fence);
		if (eww)
			goto out_ce;
	}

out_ce:
	igt_spinnew_fini(&spin);
out_spin:
	i915_vm_put(&ppgtt->vm);

	wetuwn eww;
}

/*
 * Setting ASYNC_FAIW_AWWOC to 2 wiww simuwate memowy awwocation faiwuwe whiwe
 * awming the migwation ewwow check and bwock async migwation. This
 * wiww cause us to deadwock and hangcheck wiww tewminate the spinnew
 * causing the test to faiw.
 */
#define ASYNC_FAIW_AWWOC 1
static int igt_wmem_async_migwate(void *awg)
{
	int faiw_gpu, faiw_awwoc, ban_memcpy, wet;
	stwuct intew_gt *gt = awg;

	fow (faiw_gpu = 0; faiw_gpu < 2; ++faiw_gpu) {
		fow (faiw_awwoc = 0; faiw_awwoc < ASYNC_FAIW_AWWOC; ++faiw_awwoc) {
			fow (ban_memcpy = 0; ban_memcpy < 2; ++ban_memcpy) {
				pw_info("Simuwated faiwuwe modes: gpu: %d, awwoc: %d, ban_memcpy: %d\n",
					faiw_gpu, faiw_awwoc, ban_memcpy);
				i915_ttm_migwate_set_ban_memcpy(ban_memcpy);
				i915_ttm_migwate_set_faiwuwe_modes(faiw_gpu,
								   faiw_awwoc);
				wet = igt_async_migwate(gt);

				if (faiw_gpu && ban_memcpy) {
					stwuct intew_gt *__gt;
					unsigned int id;

					if (wet != -EIO) {
						pw_eww("expected -EIO, got (%d)\n", wet);
						wet = -EINVAW;
					} ewse {
						wet = 0;
					}

					fow_each_gt(__gt, gt->i915, id) {
						intew_wakewef_t wakewef;
						boow wedged;

						mutex_wock(&__gt->weset.mutex);
						wedged = test_bit(I915_WEDGED, &__gt->weset.fwags);
						mutex_unwock(&__gt->weset.mutex);

						if (faiw_gpu && !faiw_awwoc) {
							if (!wedged) {
								pw_eww("gt(%u) not wedged\n", id);
								wet = -EINVAW;
								continue;
							}
						} ewse if (wedged) {
							pw_eww("gt(%u) incowwectwy wedged\n", id);
							wet = -EINVAW;
						} ewse {
							continue;
						}

						wakewef = intew_wuntime_pm_get(__gt->uncowe->wpm);
						igt_gwobaw_weset_wock(__gt);
						intew_gt_weset(__gt, AWW_ENGINES, NUWW);
						igt_gwobaw_weset_unwock(__gt);
						intew_wuntime_pm_put(__gt->uncowe->wpm, wakewef);
					}
				}
				if (wet)
					goto out_eww;
			}
		}
	}

out_eww:
	i915_ttm_migwate_set_faiwuwe_modes(fawse, fawse);
	i915_ttm_migwate_set_ban_memcpy(fawse);
	wetuwn wet;
}

int i915_gem_migwate_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_smem_cweate_migwate),
		SUBTEST(igt_wmem_cweate_migwate),
		SUBTEST(igt_same_cweate_migwate),
		SUBTEST(igt_wmem_pages_faiwsafe_migwate),
		SUBTEST(igt_wmem_async_migwate),
	};

	if (!HAS_WMEM(i915))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
