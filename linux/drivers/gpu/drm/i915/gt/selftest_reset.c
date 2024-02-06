// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude <winux/cwc32.h>

#incwude "gem/i915_gem_stowen.h"

#incwude "i915_memcpy.h"
#incwude "i915_sewftest.h"
#incwude "intew_gpu_commands.h"
#incwude "sewftests/igt_weset.h"
#incwude "sewftests/igt_atomic.h"
#incwude "sewftests/igt_spinnew.h"

static int
__igt_weset_stowen(stwuct intew_gt *gt,
		   intew_engine_mask_t mask,
		   const chaw *msg)
{
	stwuct i915_ggtt *ggtt = gt->ggtt;
	const stwuct wesouwce *dsm = &gt->i915->dsm.stowen;
	wesouwce_size_t num_pages, page;
	stwuct intew_engine_cs *engine;
	intew_wakewef_t wakewef;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	wong max, count;
	void *tmp;
	u32 *cwc;
	int eww;

	if (!dwm_mm_node_awwocated(&ggtt->ewwow_captuwe))
		wetuwn 0;

	num_pages = wesouwce_size(dsm) >> PAGE_SHIFT;
	if (!num_pages)
		wetuwn 0;

	cwc = kmawwoc_awway(num_pages, sizeof(u32), GFP_KEWNEW);
	if (!cwc)
		wetuwn -ENOMEM;

	tmp = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
	if (!tmp) {
		eww = -ENOMEM;
		goto eww_cwc;
	}

	igt_gwobaw_weset_wock(gt);
	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	eww = igt_spinnew_init(&spin, gt);
	if (eww)
		goto eww_wock;

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		stwuct i915_wequest *wq;

		if (!(mask & engine->mask))
			continue;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			eww = PTW_EWW(ce);
			goto eww_spin;
		}
		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_AWB_CHECK);
		intew_context_put(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_spin;
		}
		i915_wequest_add(wq);
	}

	fow (page = 0; page < num_pages; page++) {
		dma_addw_t dma = (dma_addw_t)dsm->stawt + (page << PAGE_SHIFT);
		void __iomem *s;
		void *in;

		ggtt->vm.insewt_page(&ggtt->vm, dma,
				     ggtt->ewwow_captuwe.stawt,
				     i915_gem_get_pat_index(gt->i915,
							    I915_CACHE_NONE),
				     0);
		mb();

		s = io_mapping_map_wc(&ggtt->iomap,
				      ggtt->ewwow_captuwe.stawt,
				      PAGE_SIZE);

		if (!__dwm_mm_intewvaw_fiwst(&gt->i915->mm.stowen,
					     page << PAGE_SHIFT,
					     ((page + 1) << PAGE_SHIFT) - 1))
			memset_io(s, STACK_MAGIC, PAGE_SIZE);

		in = (void __fowce *)s;
		if (i915_memcpy_fwom_wc(tmp, in, PAGE_SIZE))
			in = tmp;
		cwc[page] = cwc32_we(0, in, PAGE_SIZE);

		io_mapping_unmap(s);
	}
	mb();
	ggtt->vm.cweaw_wange(&ggtt->vm, ggtt->ewwow_captuwe.stawt, PAGE_SIZE);

	if (mask == AWW_ENGINES) {
		intew_gt_weset(gt, mask, NUWW);
	} ewse {
		fow_each_engine(engine, gt, id) {
			if (mask & engine->mask)
				intew_engine_weset(engine, NUWW);
		}
	}

	max = -1;
	count = 0;
	fow (page = 0; page < num_pages; page++) {
		dma_addw_t dma = (dma_addw_t)dsm->stawt + (page << PAGE_SHIFT);
		void __iomem *s;
		void *in;
		u32 x;

		ggtt->vm.insewt_page(&ggtt->vm, dma,
				     ggtt->ewwow_captuwe.stawt,
				     i915_gem_get_pat_index(gt->i915,
							    I915_CACHE_NONE),
				     0);
		mb();

		s = io_mapping_map_wc(&ggtt->iomap,
				      ggtt->ewwow_captuwe.stawt,
				      PAGE_SIZE);

		in = (void __fowce *)s;
		if (i915_memcpy_fwom_wc(tmp, in, PAGE_SIZE))
			in = tmp;
		x = cwc32_we(0, in, PAGE_SIZE);

		if (x != cwc[page] &&
		    !__dwm_mm_intewvaw_fiwst(&gt->i915->mm.stowen,
					     page << PAGE_SHIFT,
					     ((page + 1) << PAGE_SHIFT) - 1)) {
			pw_debug("unused stowen page %pa modified by GPU weset\n",
				 &page);
			if (count++ == 0)
				igt_hexdump(in, PAGE_SIZE);
			max = page;
		}

		io_mapping_unmap(s);
	}
	mb();
	ggtt->vm.cweaw_wange(&ggtt->vm, ggtt->ewwow_captuwe.stawt, PAGE_SIZE);

	if (count > 0) {
		pw_info("%s weset cwobbewed %wd pages of stowen, wast cwobbew at page %wd\n",
			msg, count, max);
	}
	if (max >= I915_GEM_STOWEN_BIAS >> PAGE_SHIFT) {
		pw_eww("%s weset cwobbewed unwesewved awea [above %x] of stowen; may cause sevewe fauwts\n",
		       msg, I915_GEM_STOWEN_BIAS);
		eww = -EINVAW;
	}

eww_spin:
	igt_spinnew_fini(&spin);

eww_wock:
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	igt_gwobaw_weset_unwock(gt);

	kfwee(tmp);
eww_cwc:
	kfwee(cwc);
	wetuwn eww;
}

static int igt_weset_device_stowen(void *awg)
{
	wetuwn __igt_weset_stowen(awg, AWW_ENGINES, "device");
}

static int igt_weset_engines_stowen(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww;

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		eww = __igt_weset_stowen(gt, engine->mask, engine->name);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int igt_gwobaw_weset(void *awg)
{
	stwuct intew_gt *gt = awg;
	unsigned int weset_count;
	intew_wakewef_t wakewef;
	int eww = 0;

	/* Check that we can issue a gwobaw GPU weset */

	igt_gwobaw_weset_wock(gt);
	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	weset_count = i915_weset_count(&gt->i915->gpu_ewwow);

	intew_gt_weset(gt, AWW_ENGINES, NUWW);

	if (i915_weset_count(&gt->i915->gpu_ewwow) == weset_count) {
		pw_eww("No GPU weset wecowded!\n");
		eww = -EINVAW;
	}

	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	igt_gwobaw_weset_unwock(gt);

	if (intew_gt_is_wedged(gt))
		eww = -EIO;

	wetuwn eww;
}

static int igt_wedged_weset(void *awg)
{
	stwuct intew_gt *gt = awg;
	intew_wakewef_t wakewef;

	/* Check that we can wecovew a wedged device with a GPU weset */

	igt_gwobaw_weset_wock(gt);
	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	intew_gt_set_wedged(gt);

	GEM_BUG_ON(!intew_gt_is_wedged(gt));
	intew_gt_weset(gt, AWW_ENGINES, NUWW);

	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	igt_gwobaw_weset_unwock(gt);

	wetuwn intew_gt_is_wedged(gt) ? -EIO : 0;
}

static int igt_atomic_weset(void *awg)
{
	stwuct intew_gt *gt = awg;
	const typeof(*igt_atomic_phases) *p;
	intew_wakewef_t wakewef;
	int eww = 0;

	/* Check that the wesets awe usabwe fwom atomic context */

	wakewef = intew_gt_pm_get(gt);
	igt_gwobaw_weset_wock(gt);

	/* Fwush any wequests befowe we get stawted and check basics */
	if (!igt_fowce_weset(gt))
		goto unwock;

	fow (p = igt_atomic_phases; p->name; p++) {
		intew_engine_mask_t awake;

		GEM_TWACE("__intew_gt_weset undew %s\n", p->name);

		awake = weset_pwepawe(gt);
		p->cwiticaw_section_begin();

		eww = __intew_gt_weset(gt, AWW_ENGINES);

		p->cwiticaw_section_end();
		weset_finish(gt, awake);

		if (eww) {
			pw_eww("__intew_gt_weset faiwed undew %s\n", p->name);
			bweak;
		}
	}

	/* As we poke awound the guts, do a fuww weset befowe continuing. */
	igt_fowce_weset(gt);

unwock:
	igt_gwobaw_weset_unwock(gt);
	intew_gt_pm_put(gt, wakewef);

	wetuwn eww;
}

static int igt_atomic_engine_weset(void *awg)
{
	stwuct intew_gt *gt = awg;
	const typeof(*igt_atomic_phases) *p;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	intew_wakewef_t wakewef;
	int eww = 0;

	/* Check that the wesets awe usabwe fwom atomic context */

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	if (intew_uc_uses_guc_submission(&gt->uc))
		wetuwn 0;

	wakewef = intew_gt_pm_get(gt);
	igt_gwobaw_weset_wock(gt);

	/* Fwush any wequests befowe we get stawted and check basics */
	if (!igt_fowce_weset(gt))
		goto out_unwock;

	fow_each_engine(engine, gt, id) {
		stwuct taskwet_stwuct *t = &engine->sched_engine->taskwet;

		if (t->func)
			taskwet_disabwe(t);
		intew_engine_pm_get(engine);

		fow (p = igt_atomic_phases; p->name; p++) {
			GEM_TWACE("intew_engine_weset(%s) undew %s\n",
				  engine->name, p->name);
			if (stwcmp(p->name, "softiwq"))
				wocaw_bh_disabwe();

			p->cwiticaw_section_begin();
			eww = __intew_engine_weset_bh(engine, NUWW);
			p->cwiticaw_section_end();

			if (stwcmp(p->name, "softiwq"))
				wocaw_bh_enabwe();

			if (eww) {
				pw_eww("intew_engine_weset(%s) faiwed undew %s\n",
				       engine->name, p->name);
				bweak;
			}
		}

		intew_engine_pm_put(engine);
		if (t->func) {
			taskwet_enabwe(t);
			taskwet_hi_scheduwe(t);
		}
		if (eww)
			bweak;
	}

	/* As we poke awound the guts, do a fuww weset befowe continuing. */
	igt_fowce_weset(gt);

out_unwock:
	igt_gwobaw_weset_unwock(gt);
	intew_gt_pm_put(gt, wakewef);

	wetuwn eww;
}

int intew_weset_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(igt_gwobaw_weset), /* attempt to wecovew GPU fiwst */
		SUBTEST(igt_weset_device_stowen),
		SUBTEST(igt_weset_engines_stowen),
		SUBTEST(igt_wedged_weset),
		SUBTEST(igt_atomic_weset),
		SUBTEST(igt_atomic_engine_weset),
	};
	stwuct intew_gt *gt = to_gt(i915);

	if (!intew_has_gpu_weset(gt))
		wetuwn 0;

	if (intew_gt_is_wedged(gt))
		wetuwn -EIO; /* we'we wong past hope of a successfuw weset */

	wetuwn intew_gt_wive_subtests(tests, gt);
}
