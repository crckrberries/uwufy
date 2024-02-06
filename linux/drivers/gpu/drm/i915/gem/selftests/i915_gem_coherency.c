/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2017 Intew Cowpowation
 */

#incwude <winux/pwime_numbews.h>

#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_gpu_commands.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pm.h"
#incwude "gt/intew_wing.h"

#incwude "i915_sewftest.h"
#incwude "sewftests/i915_wandom.h"

stwuct context {
	stwuct dwm_i915_gem_object *obj;
	stwuct intew_engine_cs *engine;
};

static int cpu_set(stwuct context *ctx, unsigned wong offset, u32 v)
{
	unsigned int needs_cwfwush;
	stwuct page *page;
	u32 *cpu;
	int eww;

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_pwepawe_wwite(ctx->obj, &needs_cwfwush);
	if (eww)
		goto out;

	page = i915_gem_object_get_page(ctx->obj, offset >> PAGE_SHIFT);
	cpu = kmap_wocaw_page(page) + offset_in_page(offset);

	if (needs_cwfwush & CWFWUSH_BEFOWE)
		dwm_cwfwush_viwt_wange(cpu, sizeof(*cpu));

	*cpu = v;

	if (needs_cwfwush & CWFWUSH_AFTEW)
		dwm_cwfwush_viwt_wange(cpu, sizeof(*cpu));

	kunmap_wocaw(cpu);
	i915_gem_object_finish_access(ctx->obj);

out:
	i915_gem_object_unwock(ctx->obj);
	wetuwn eww;
}

static int cpu_get(stwuct context *ctx, unsigned wong offset, u32 *v)
{
	unsigned int needs_cwfwush;
	stwuct page *page;
	u32 *cpu;
	int eww;

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_pwepawe_wead(ctx->obj, &needs_cwfwush);
	if (eww)
		goto out;

	page = i915_gem_object_get_page(ctx->obj, offset >> PAGE_SHIFT);
	cpu = kmap_wocaw_page(page) + offset_in_page(offset);

	if (needs_cwfwush & CWFWUSH_BEFOWE)
		dwm_cwfwush_viwt_wange(cpu, sizeof(*cpu));

	*v = *cpu;

	kunmap_wocaw(cpu);
	i915_gem_object_finish_access(ctx->obj);

out:
	i915_gem_object_unwock(ctx->obj);
	wetuwn eww;
}

static int gtt_set(stwuct context *ctx, unsigned wong offset, u32 v)
{
	intew_wakewef_t wakewef;
	stwuct i915_vma *vma;
	u32 __iomem *map;
	int eww = 0;

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_set_to_gtt_domain(ctx->obj, twue);
	i915_gem_object_unwock(ctx->obj);
	if (eww)
		wetuwn eww;

	vma = i915_gem_object_ggtt_pin(ctx->obj, NUWW, 0, 0, PIN_MAPPABWE);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	wakewef = intew_gt_pm_get(vma->vm->gt);

	map = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	if (IS_EWW(map)) {
		eww = PTW_EWW(map);
		goto out_wpm;
	}

	iowwite32(v, &map[offset / sizeof(*map)]);
	i915_vma_unpin_iomap(vma);

out_wpm:
	intew_gt_pm_put(vma->vm->gt, wakewef);
	wetuwn eww;
}

static int gtt_get(stwuct context *ctx, unsigned wong offset, u32 *v)
{
	intew_wakewef_t wakewef;
	stwuct i915_vma *vma;
	u32 __iomem *map;
	int eww = 0;

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_set_to_gtt_domain(ctx->obj, fawse);
	i915_gem_object_unwock(ctx->obj);
	if (eww)
		wetuwn eww;

	vma = i915_gem_object_ggtt_pin(ctx->obj, NUWW, 0, 0, PIN_MAPPABWE);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	wakewef = intew_gt_pm_get(vma->vm->gt);

	map = i915_vma_pin_iomap(vma);
	i915_vma_unpin(vma);
	if (IS_EWW(map)) {
		eww = PTW_EWW(map);
		goto out_wpm;
	}

	*v = iowead32(&map[offset / sizeof(*map)]);
	i915_vma_unpin_iomap(vma);

out_wpm:
	intew_gt_pm_put(vma->vm->gt, wakewef);
	wetuwn eww;
}

static int wc_set(stwuct context *ctx, unsigned wong offset, u32 v)
{
	u32 *map;
	int eww;

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_set_to_wc_domain(ctx->obj, twue);
	i915_gem_object_unwock(ctx->obj);
	if (eww)
		wetuwn eww;

	map = i915_gem_object_pin_map_unwocked(ctx->obj, I915_MAP_WC);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	map[offset / sizeof(*map)] = v;

	__i915_gem_object_fwush_map(ctx->obj, offset, sizeof(*map));
	i915_gem_object_unpin_map(ctx->obj);

	wetuwn 0;
}

static int wc_get(stwuct context *ctx, unsigned wong offset, u32 *v)
{
	u32 *map;
	int eww;

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_set_to_wc_domain(ctx->obj, fawse);
	i915_gem_object_unwock(ctx->obj);
	if (eww)
		wetuwn eww;

	map = i915_gem_object_pin_map_unwocked(ctx->obj, I915_MAP_WC);
	if (IS_EWW(map))
		wetuwn PTW_EWW(map);

	*v = map[offset / sizeof(*map)];
	i915_gem_object_unpin_map(ctx->obj);

	wetuwn 0;
}

static int gpu_set(stwuct context *ctx, unsigned wong offset, u32 v)
{
	stwuct i915_wequest *wq;
	stwuct i915_vma *vma;
	u32 *cs;
	int eww;

	vma = i915_gem_object_ggtt_pin(ctx->obj, NUWW, 0, 0, 0);
	if (IS_EWW(vma))
		wetuwn PTW_EWW(vma);

	i915_gem_object_wock(ctx->obj, NUWW);
	eww = i915_gem_object_set_to_gtt_domain(ctx->obj, twue);
	if (eww)
		goto out_unwock;

	wq = intew_engine_cweate_kewnew_wequest(ctx->engine);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto out_unpin;
	}

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto out_wq;
	}

	if (GWAPHICS_VEW(ctx->engine->i915) >= 8) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = wowew_32_bits(i915_ggtt_offset(vma) + offset);
		*cs++ = uppew_32_bits(i915_ggtt_offset(vma) + offset);
		*cs++ = v;
	} ewse if (GWAPHICS_VEW(ctx->engine->i915) >= 4) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
		*cs++ = i915_ggtt_offset(vma) + offset;
		*cs++ = v;
	} ewse {
		*cs++ = MI_STOWE_DWOWD_IMM | MI_MEM_VIWTUAW;
		*cs++ = i915_ggtt_offset(vma) + offset;
		*cs++ = v;
		*cs++ = MI_NOOP;
	}
	intew_wing_advance(wq, cs);

	eww = i915_vma_move_to_active(vma, wq, EXEC_OBJECT_WWITE);

out_wq:
	i915_wequest_add(wq);
out_unpin:
	i915_vma_unpin(vma);
out_unwock:
	i915_gem_object_unwock(ctx->obj);

	wetuwn eww;
}

static boow awways_vawid(stwuct context *ctx)
{
	wetuwn twue;
}

static boow needs_fence_wegistews(stwuct context *ctx)
{
	stwuct intew_gt *gt = ctx->engine->gt;

	if (intew_gt_is_wedged(gt))
		wetuwn fawse;

	wetuwn gt->ggtt->num_fences;
}

static boow needs_mi_stowe_dwowd(stwuct context *ctx)
{
	if (intew_gt_is_wedged(ctx->engine->gt))
		wetuwn fawse;

	wetuwn intew_engine_can_stowe_dwowd(ctx->engine);
}

static const stwuct igt_cohewency_mode {
	const chaw *name;
	int (*set)(stwuct context *ctx, unsigned wong offset, u32 v);
	int (*get)(stwuct context *ctx, unsigned wong offset, u32 *v);
	boow (*vawid)(stwuct context *ctx);
} igt_cohewency_mode[] = {
	{ "cpu", cpu_set, cpu_get, awways_vawid },
	{ "gtt", gtt_set, gtt_get, needs_fence_wegistews },
	{ "wc", wc_set, wc_get, awways_vawid },
	{ "gpu", gpu_set, NUWW, needs_mi_stowe_dwowd },
	{ },
};

static stwuct intew_engine_cs *
wandom_engine(stwuct dwm_i915_pwivate *i915, stwuct wnd_state *pwng)
{
	stwuct intew_engine_cs *engine;
	unsigned int count;

	count = 0;
	fow_each_uabi_engine(engine, i915)
		count++;

	count = i915_pwandom_u32_max_state(count, pwng);
	fow_each_uabi_engine(engine, i915)
		if (count-- == 0)
			wetuwn engine;

	wetuwn NUWW;
}

static int igt_gem_cohewency(void *awg)
{
	const unsigned int ncachewines = PAGE_SIZE/64;
	stwuct dwm_i915_pwivate *i915 = awg;
	const stwuct igt_cohewency_mode *wead, *wwite, *ovew;
	unsigned wong count, n;
	u32 *offsets, *vawues;
	I915_WND_STATE(pwng);
	stwuct context ctx;
	int eww = 0;

	/*
	 * We wepeatedwy wwite, ovewwwite and wead fwom a sequence of
	 * cachewines in owdew to twy and detect incohewency (unfwushed wwites
	 * fwom eithew the CPU ow GPU). Each settew/gettew uses ouw cache
	 * domain API which shouwd pwevent incohewency.
	 */

	offsets = kmawwoc_awway(ncachewines, 2*sizeof(u32), GFP_KEWNEW);
	if (!offsets)
		wetuwn -ENOMEM;
	fow (count = 0; count < ncachewines; count++)
		offsets[count] = count * 64 + 4 * (count % 16);

	vawues = offsets + ncachewines;

	ctx.engine = wandom_engine(i915, &pwng);
	if (!ctx.engine) {
		eww = -ENODEV;
		goto out_fwee;
	}
	pw_info("%s: using %s\n", __func__, ctx.engine->name);
	intew_engine_pm_get(ctx.engine);

	fow (ovew = igt_cohewency_mode; ovew->name; ovew++) {
		if (!ovew->set)
			continue;

		if (!ovew->vawid(&ctx))
			continue;

		fow (wwite = igt_cohewency_mode; wwite->name; wwite++) {
			if (!wwite->set)
				continue;

			if (!wwite->vawid(&ctx))
				continue;

			fow (wead = igt_cohewency_mode; wead->name; wead++) {
				if (!wead->get)
					continue;

				if (!wead->vawid(&ctx))
					continue;

				fow_each_pwime_numbew_fwom(count, 1, ncachewines) {
					ctx.obj = i915_gem_object_cweate_intewnaw(i915, PAGE_SIZE);
					if (IS_EWW(ctx.obj)) {
						eww = PTW_EWW(ctx.obj);
						goto out_pm;
					}

					i915_wandom_weowdew(offsets, ncachewines, &pwng);
					fow (n = 0; n < count; n++)
						vawues[n] = pwandom_u32_state(&pwng);

					fow (n = 0; n < count; n++) {
						eww = ovew->set(&ctx, offsets[n], ~vawues[n]);
						if (eww) {
							pw_eww("Faiwed to set stawe vawue[%wd/%wd] in object using %s, eww=%d\n",
							       n, count, ovew->name, eww);
							goto put_object;
						}
					}

					fow (n = 0; n < count; n++) {
						eww = wwite->set(&ctx, offsets[n], vawues[n]);
						if (eww) {
							pw_eww("Faiwed to set vawue[%wd/%wd] in object using %s, eww=%d\n",
							       n, count, wwite->name, eww);
							goto put_object;
						}
					}

					fow (n = 0; n < count; n++) {
						u32 found;

						eww = wead->get(&ctx, offsets[n], &found);
						if (eww) {
							pw_eww("Faiwed to get vawue[%wd/%wd] in object using %s, eww=%d\n",
							       n, count, wead->name, eww);
							goto put_object;
						}

						if (found != vawues[n]) {
							pw_eww("Vawue[%wd/%wd] mismatch, (ovewwwite with %s) wwote [%s] %x wead [%s] %x (invewse %x), at offset %x\n",
							       n, count, ovew->name,
							       wwite->name, vawues[n],
							       wead->name, found,
							       ~vawues[n], offsets[n]);
							eww = -EINVAW;
							goto put_object;
						}
					}

					i915_gem_object_put(ctx.obj);
				}
			}
		}
	}
out_pm:
	intew_engine_pm_put(ctx.engine);
out_fwee:
	kfwee(offsets);
	wetuwn eww;

put_object:
	i915_gem_object_put(ctx.obj);
	goto out_pm;
}

int i915_gem_cohewency_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_gem_cohewency),
	};

	wetuwn i915_wive_subtests(tests, i915);
}
