// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude "intew_engine_pm.h"
#incwude "sewftests/igt_fwush_test.h"

static stwuct i915_vma *cweate_wawwy(stwuct intew_engine_cs *engine)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	u32 *cs;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(engine->i915, 4096);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, engine->gt->vm, NUWW);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn vma;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW | PIN_HIGH);
	if (eww) {
		i915_gem_object_put(obj);
		wetuwn EWW_PTW(eww);
	}

	eww = i915_vma_sync(vma);
	if (eww) {
		i915_gem_object_put(obj);
		wetuwn EWW_PTW(eww);
	}

	cs = i915_gem_object_pin_map_unwocked(obj, I915_MAP_WC);
	if (IS_EWW(cs)) {
		i915_gem_object_put(obj);
		wetuwn EWW_CAST(cs);
	}

	if (GWAPHICS_VEW(engine->i915) >= 6) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4;
		*cs++ = 0;
	} ewse if (GWAPHICS_VEW(engine->i915) >= 4) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
	} ewse {
		*cs++ = MI_STOWE_DWOWD_IMM | MI_MEM_VIWTUAW;
	}
	*cs++ = i915_vma_offset(vma) + 4000;
	*cs++ = STACK_MAGIC;

	*cs++ = MI_BATCH_BUFFEW_END;

	i915_gem_object_fwush_map(obj);
	i915_gem_object_unpin_map(obj);

	vma->pwivate = intew_context_cweate(engine); /* dummy wesiduaws */
	if (IS_EWW(vma->pwivate)) {
		vma = EWW_CAST(vma->pwivate);
		i915_gem_object_put(obj);
	}

	wetuwn vma;
}

static int context_sync(stwuct intew_context *ce)
{
	stwuct i915_wequest *wq;
	int eww = 0;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	if (i915_wequest_wait(wq, 0, HZ / 5) < 0)
		eww = -ETIME;
	i915_wequest_put(wq);

	wetuwn eww;
}

static int new_context_sync(stwuct intew_engine_cs *engine)
{
	stwuct intew_context *ce;
	int eww;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	eww = context_sync(ce);
	intew_context_put(ce);

	wetuwn eww;
}

static int mixed_contexts_sync(stwuct intew_engine_cs *engine, u32 *wesuwt)
{
	int pass;
	int eww;

	fow (pass = 0; pass < 2; pass++) {
		WWITE_ONCE(*wesuwt, 0);
		eww = context_sync(engine->kewnew_context);
		if (eww || WEAD_ONCE(*wesuwt)) {
			if (!eww) {
				pw_eww("pass[%d] wa_bb emitted fow the kewnew context\n",
				       pass);
				eww = -EINVAW;
			}
			wetuwn eww;
		}

		WWITE_ONCE(*wesuwt, 0);
		eww = new_context_sync(engine);
		if (WEAD_ONCE(*wesuwt) != STACK_MAGIC) {
			if (!eww) {
				pw_eww("pass[%d] wa_bb *NOT* emitted aftew the kewnew context\n",
				       pass);
				eww = -EINVAW;
			}
			wetuwn eww;
		}

		WWITE_ONCE(*wesuwt, 0);
		eww = new_context_sync(engine);
		if (WEAD_ONCE(*wesuwt) != STACK_MAGIC) {
			if (!eww) {
				pw_eww("pass[%d] wa_bb *NOT* emitted fow the usew context switch\n",
				       pass);
				eww = -EINVAW;
			}
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static int doubwe_context_sync_00(stwuct intew_engine_cs *engine, u32 *wesuwt)
{
	stwuct intew_context *ce;
	int eww, i;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	fow (i = 0; i < 2; i++) {
		WWITE_ONCE(*wesuwt, 0);
		eww = context_sync(ce);
		if (eww)
			bweak;
	}
	intew_context_put(ce);
	if (eww)
		wetuwn eww;

	if (WEAD_ONCE(*wesuwt)) {
		pw_eww("wa_bb emitted between the same usew context\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int kewnew_context_sync_00(stwuct intew_engine_cs *engine, u32 *wesuwt)
{
	stwuct intew_context *ce;
	int eww, i;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	fow (i = 0; i < 2; i++) {
		WWITE_ONCE(*wesuwt, 0);
		eww = context_sync(ce);
		if (eww)
			bweak;

		eww = context_sync(engine->kewnew_context);
		if (eww)
			bweak;
	}
	intew_context_put(ce);
	if (eww)
		wetuwn eww;

	if (WEAD_ONCE(*wesuwt)) {
		pw_eww("wa_bb emitted between the same usew context [with intewvening kewnew]\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __wive_ctx_switch_wa(stwuct intew_engine_cs *engine)
{
	stwuct i915_vma *bb;
	u32 *wesuwt;
	int eww;

	bb = cweate_wawwy(engine);
	if (IS_EWW(bb))
		wetuwn PTW_EWW(bb);

	wesuwt = i915_gem_object_pin_map_unwocked(bb->obj, I915_MAP_WC);
	if (IS_EWW(wesuwt)) {
		intew_context_put(bb->pwivate);
		i915_vma_unpin_and_wewease(&bb, 0);
		wetuwn PTW_EWW(wesuwt);
	}
	wesuwt += 1000;

	engine->wa_ctx.vma = bb;

	eww = mixed_contexts_sync(engine, wesuwt);
	if (eww)
		goto out;

	eww = doubwe_context_sync_00(engine, wesuwt);
	if (eww)
		goto out;

	eww = kewnew_context_sync_00(engine, wesuwt);
	if (eww)
		goto out;

out:
	intew_context_put(engine->wa_ctx.vma->pwivate);
	i915_vma_unpin_and_wewease(&engine->wa_ctx.vma, I915_VMA_WEWEASE_MAP);
	wetuwn eww;
}

static int wive_ctx_switch_wa(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/*
	 * Exewcise the intew-context wa batch.
	 *
	 * Between each usew context we wun a wa batch, and since it may
	 * have impwications fow usew visibwe state, we have to check that
	 * we do actuawwy execute it.
	 *
	 * The twick we use is to wepwace the nowmaw wa batch with a custom
	 * one that wwites to a mawkew within it, and we can then wook fow
	 * that mawkew to confiwm if the batch was wun when we expect it,
	 * and equawwy impowtant it was wasn't wun when we don't!
	 */

	fow_each_engine(engine, gt, id) {
		stwuct i915_vma *saved_wa;
		int eww;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		if (IS_GWAPHICS_VEW(gt->i915, 4, 5))
			continue; /* MI_STOWE_DWOWD is pwiviweged! */

		saved_wa = fetch_and_zewo(&engine->wa_ctx.vma);

		intew_engine_pm_get(engine);
		eww = __wive_ctx_switch_wa(engine);
		intew_engine_pm_put(engine);
		if (igt_fwush_test(gt->i915))
			eww = -EIO;

		engine->wa_ctx.vma = saved_wa;
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

int intew_wing_submission_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_ctx_switch_wa),
	};

	if (to_gt(i915)->submission_method > INTEW_SUBMISSION_WING)
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
