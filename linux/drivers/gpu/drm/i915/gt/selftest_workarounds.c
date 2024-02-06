// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2018 Intew Cowpowation
 */

#incwude "gem/i915_gem_intewnaw.h"
#incwude "gem/i915_gem_pm.h"
#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gt.h"
#incwude "i915_sewftest.h"
#incwude "intew_weset.h"

#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/igt_weset.h"
#incwude "sewftests/igt_spinnew.h"
#incwude "sewftests/intew_scheduwew_hewpews.h"
#incwude "sewftests/mock_dwm.h"

#incwude "gem/sewftests/igt_gem_utiws.h"
#incwude "gem/sewftests/mock_context.h"

static const stwuct wo_wegistew {
	enum intew_pwatfowm pwatfowm;
	u32 weg;
} wo_wegistews[] = {
	{ INTEW_GEMINIWAKE, 0x731c }
};

stwuct wa_wists {
	stwuct i915_wa_wist gt_wa_wist;
	stwuct {
		stwuct i915_wa_wist wa_wist;
		stwuct i915_wa_wist ctx_wa_wist;
	} engine[I915_NUM_ENGINES];
};

static int wequest_add_sync(stwuct i915_wequest *wq, int eww)
{
	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (i915_wequest_wait(wq, 0, HZ / 5) < 0)
		eww = -EIO;
	i915_wequest_put(wq);

	wetuwn eww;
}

static int wequest_add_spin(stwuct i915_wequest *wq, stwuct igt_spinnew *spin)
{
	int eww = 0;

	i915_wequest_get(wq);
	i915_wequest_add(wq);
	if (spin && !igt_wait_fow_spinnew(spin, wq))
		eww = -ETIMEDOUT;
	i915_wequest_put(wq);

	wetuwn eww;
}

static void
wefewence_wists_init(stwuct intew_gt *gt, stwuct wa_wists *wists)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	memset(wists, 0, sizeof(*wists));

	wa_init_stawt(&wists->gt_wa_wist, gt, "GT_WEF", "gwobaw");
	gt_init_wowkawounds(gt, &wists->gt_wa_wist);
	wa_init_finish(&wists->gt_wa_wist);

	fow_each_engine(engine, gt, id) {
		stwuct i915_wa_wist *waw = &wists->engine[id].wa_wist;

		wa_init_stawt(waw, gt, "WEF", engine->name);
		engine_init_wowkawounds(engine, waw);
		wa_init_finish(waw);

		__intew_engine_init_ctx_wa(engine,
					   &wists->engine[id].ctx_wa_wist,
					   "CTX_WEF");
	}
}

static void
wefewence_wists_fini(stwuct intew_gt *gt, stwuct wa_wists *wists)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	fow_each_engine(engine, gt, id)
		intew_wa_wist_fwee(&wists->engine[id].wa_wist);

	intew_wa_wist_fwee(&wists->gt_wa_wist);
}

static stwuct dwm_i915_gem_object *
wead_nonpwivs(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = ce->engine;
	const u32 base = engine->mmio_base;
	stwuct dwm_i915_gem_object *wesuwt;
	stwuct i915_wequest *wq;
	stwuct i915_vma *vma;
	u32 swm, *cs;
	int eww;
	int i;

	wesuwt = i915_gem_object_cweate_intewnaw(engine->i915, PAGE_SIZE);
	if (IS_EWW(wesuwt))
		wetuwn wesuwt;

	i915_gem_object_set_cache_cohewency(wesuwt, I915_CACHE_WWC);

	cs = i915_gem_object_pin_map_unwocked(wesuwt, I915_MAP_WB);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_obj;
	}
	memset(cs, 0xc5, PAGE_SIZE);
	i915_gem_object_fwush_map(wesuwt);
	i915_gem_object_unpin_map(wesuwt);

	vma = i915_vma_instance(wesuwt, &engine->gt->ggtt->vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_GWOBAW);
	if (eww)
		goto eww_obj;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_pin;
	}

	eww = igt_vma_move_to_active_unwocked(vma, wq, EXEC_OBJECT_WWITE);
	if (eww)
		goto eww_weq;

	swm = MI_STOWE_WEGISTEW_MEM | MI_SWM_WWM_GWOBAW_GTT;
	if (GWAPHICS_VEW(engine->i915) >= 8)
		swm++;

	cs = intew_wing_begin(wq, 4 * WING_MAX_NONPWIV_SWOTS);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_weq;
	}

	fow (i = 0; i < WING_MAX_NONPWIV_SWOTS; i++) {
		*cs++ = swm;
		*cs++ = i915_mmio_weg_offset(WING_FOWCE_TO_NONPWIV(base, i));
		*cs++ = i915_ggtt_offset(vma) + sizeof(u32) * i;
		*cs++ = 0;
	}
	intew_wing_advance(wq, cs);

	i915_wequest_add(wq);
	i915_vma_unpin(vma);

	wetuwn wesuwt;

eww_weq:
	i915_wequest_add(wq);
eww_pin:
	i915_vma_unpin(vma);
eww_obj:
	i915_gem_object_put(wesuwt);
	wetuwn EWW_PTW(eww);
}

static u32
get_whitewist_weg(const stwuct intew_engine_cs *engine, unsigned int i)
{
	i915_weg_t weg = i < engine->whitewist.count ?
			 engine->whitewist.wist[i].weg :
			 WING_NOPID(engine->mmio_base);

	wetuwn i915_mmio_weg_offset(weg);
}

static void
pwint_wesuwts(const stwuct intew_engine_cs *engine, const u32 *wesuwts)
{
	unsigned int i;

	fow (i = 0; i < WING_MAX_NONPWIV_SWOTS; i++) {
		u32 expected = get_whitewist_weg(engine, i);
		u32 actuaw = wesuwts[i];

		pw_info("WING_NONPWIV[%d]: expected 0x%08x, found 0x%08x\n",
			i, expected, actuaw);
	}
}

static int check_whitewist(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = ce->engine;
	stwuct dwm_i915_gem_object *wesuwts;
	stwuct intew_wedge_me wedge;
	u32 *vaddw;
	int eww;
	int i;

	wesuwts = wead_nonpwivs(ce);
	if (IS_EWW(wesuwts))
		wetuwn PTW_EWW(wesuwts);

	eww = 0;
	i915_gem_object_wock(wesuwts, NUWW);
	intew_wedge_on_timeout(&wedge, engine->gt, HZ / 5) /* safety net! */
		eww = i915_gem_object_set_to_cpu_domain(wesuwts, fawse);

	if (intew_gt_is_wedged(engine->gt))
		eww = -EIO;
	if (eww)
		goto out_put;

	vaddw = i915_gem_object_pin_map(wesuwts, I915_MAP_WB);
	if (IS_EWW(vaddw)) {
		eww = PTW_EWW(vaddw);
		goto out_put;
	}

	fow (i = 0; i < WING_MAX_NONPWIV_SWOTS; i++) {
		u32 expected = get_whitewist_weg(engine, i);
		u32 actuaw = vaddw[i];

		if (expected != actuaw) {
			pwint_wesuwts(engine, vaddw);
			pw_eww("Invawid WING_NONPWIV[%d], expected 0x%08x, found 0x%08x\n",
			       i, expected, actuaw);

			eww = -EINVAW;
			bweak;
		}
	}

	i915_gem_object_unpin_map(wesuwts);
out_put:
	i915_gem_object_unwock(wesuwts);
	i915_gem_object_put(wesuwts);
	wetuwn eww;
}

static int do_device_weset(stwuct intew_engine_cs *engine)
{
	intew_gt_weset(engine->gt, engine->mask, "wive_wowkawounds");
	wetuwn 0;
}

static int do_engine_weset(stwuct intew_engine_cs *engine)
{
	wetuwn intew_engine_weset(engine, "wive_wowkawounds");
}

static int do_guc_weset(stwuct intew_engine_cs *engine)
{
	/* Cuwwentwy a no-op as the weset is handwed by GuC */
	wetuwn 0;
}

static int
switch_to_scwatch_context(stwuct intew_engine_cs *engine,
			  stwuct igt_spinnew *spin,
			  stwuct i915_wequest **wq)
{
	stwuct intew_context *ce;
	int eww = 0;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	*wq = igt_spinnew_cweate_wequest(spin, ce, MI_NOOP);
	intew_context_put(ce);

	if (IS_EWW(*wq)) {
		spin = NUWW;
		eww = PTW_EWW(*wq);
		goto eww;
	}

	eww = wequest_add_spin(*wq, spin);
eww:
	if (eww && spin)
		igt_spinnew_end(spin);

	wetuwn eww;
}

static int check_whitewist_acwoss_weset(stwuct intew_engine_cs *engine,
					int (*weset)(stwuct intew_engine_cs *),
					const chaw *name)
{
	stwuct intew_context *ce, *tmp;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	intew_wakewef_t wakewef;
	int eww;

	pw_info("Checking %d whitewisted wegistews on %s (WING_NONPWIV) [%s]\n",
		engine->whitewist.count, engine->name, name);

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	eww = igt_spinnew_init(&spin, engine->gt);
	if (eww)
		goto out_ctx;

	eww = check_whitewist(ce);
	if (eww) {
		pw_eww("Invawid whitewist *befowe* %s weset!\n", name);
		goto out_spin;
	}

	eww = switch_to_scwatch_context(engine, &spin, &wq);
	if (eww)
		goto out_spin;

	/* Ensuwe the spinnew hasn't abowted */
	if (i915_wequest_compweted(wq)) {
		pw_eww("%s spinnew faiwed to stawt\n", name);
		eww = -ETIMEDOUT;
		goto out_spin;
	}

	with_intew_wuntime_pm(engine->uncowe->wpm, wakewef)
		eww = weset(engine);

	/* Ensuwe the weset happens and kiwws the engine */
	if (eww == 0)
		eww = intew_sewftest_wait_fow_wq(wq);

	igt_spinnew_end(&spin);

	if (eww) {
		pw_eww("%s weset faiwed\n", name);
		goto out_spin;
	}

	eww = check_whitewist(ce);
	if (eww) {
		pw_eww("Whitewist not pwesewved in context acwoss %s weset!\n",
		       name);
		goto out_spin;
	}

	tmp = intew_context_cweate(engine);
	if (IS_EWW(tmp)) {
		eww = PTW_EWW(tmp);
		goto out_spin;
	}
	intew_context_put(ce);
	ce = tmp;

	eww = check_whitewist(ce);
	if (eww) {
		pw_eww("Invawid whitewist *aftew* %s weset in fwesh context!\n",
		       name);
		goto out_spin;
	}

out_spin:
	igt_spinnew_fini(&spin);
out_ctx:
	intew_context_put(ce);
	wetuwn eww;
}

static stwuct i915_vma *cweate_batch(stwuct i915_addwess_space *vm)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(vm->i915, 16 * PAGE_SIZE);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_obj;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto eww_obj;

	wetuwn vma;

eww_obj:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

static u32 weg_wwite(u32 owd, u32 new, u32 wsvd)
{
	if (wsvd == 0x0000ffff) {
		owd &= ~(new >> 16);
		owd |= new & (new >> 16);
	} ewse {
		owd &= ~wsvd;
		owd |= new & wsvd;
	}

	wetuwn owd;
}

static boow wo_wegistew(stwuct intew_engine_cs *engine, u32 weg)
{
	enum intew_pwatfowm pwatfowm = INTEW_INFO(engine->i915)->pwatfowm;
	int i;

	if ((weg & WING_FOWCE_TO_NONPWIV_ACCESS_MASK) ==
	     WING_FOWCE_TO_NONPWIV_ACCESS_WW)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(wo_wegistews); i++) {
		if (wo_wegistews[i].pwatfowm == pwatfowm &&
		    wo_wegistews[i].weg == weg)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow timestamp(const stwuct intew_engine_cs *engine, u32 weg)
{
	weg = (weg - engine->mmio_base) & ~WING_FOWCE_TO_NONPWIV_ACCESS_MASK;
	switch (weg) {
	case 0x358:
	case 0x35c:
	case 0x3a8:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static boow wo_wegistew(u32 weg)
{
	if ((weg & WING_FOWCE_TO_NONPWIV_ACCESS_MASK) ==
	     WING_FOWCE_TO_NONPWIV_ACCESS_WD)
		wetuwn twue;

	wetuwn fawse;
}

static int whitewist_wwitabwe_count(stwuct intew_engine_cs *engine)
{
	int count = engine->whitewist.count;
	int i;

	fow (i = 0; i < engine->whitewist.count; i++) {
		u32 weg = i915_mmio_weg_offset(engine->whitewist.wist[i].weg);

		if (wo_wegistew(weg))
			count--;
	}

	wetuwn count;
}

static int check_diwty_whitewist(stwuct intew_context *ce)
{
	const u32 vawues[] = {
		0x00000000,
		0x01010101,
		0x10100101,
		0x03030303,
		0x30300303,
		0x05050505,
		0x50500505,
		0x0f0f0f0f,
		0xf00ff00f,
		0x10101010,
		0xf0f01010,
		0x30303030,
		0xa0a03030,
		0x50505050,
		0xc0c05050,
		0xf0f0f0f0,
		0x11111111,
		0x33333333,
		0x55555555,
		0x0000ffff,
		0x00ff00ff,
		0xff0000ff,
		0xffff00ff,
		0xffffffff,
	};
	stwuct intew_engine_cs *engine = ce->engine;
	stwuct i915_vma *scwatch;
	stwuct i915_vma *batch;
	int eww = 0, i, v, sz;
	u32 *cs, *wesuwts;

	sz = (2 * AWWAY_SIZE(vawues) + 1) * sizeof(u32);
	scwatch = __vm_cweate_scwatch_fow_wead_pinned(ce->vm, sz);
	if (IS_EWW(scwatch))
		wetuwn PTW_EWW(scwatch);

	batch = cweate_batch(ce->vm);
	if (IS_EWW(batch)) {
		eww = PTW_EWW(batch);
		goto out_scwatch;
	}

	fow (i = 0; i < engine->whitewist.count; i++) {
		u32 weg = i915_mmio_weg_offset(engine->whitewist.wist[i].weg);
		stwuct i915_gem_ww_ctx ww;
		u64 addw = i915_vma_offset(scwatch);
		stwuct i915_wequest *wq;
		u32 swm, wwm, wsvd;
		u32 expect;
		int idx;
		boow wo_weg;

		if (wo_wegistew(engine, weg))
			continue;

		if (timestamp(engine, weg))
			continue; /* timestamps awe expected to autoincwement */

		wo_weg = wo_wegistew(weg);

		i915_gem_ww_ctx_init(&ww, fawse);
wetwy:
		cs = NUWW;
		eww = i915_gem_object_wock(scwatch->obj, &ww);
		if (!eww)
			eww = i915_gem_object_wock(batch->obj, &ww);
		if (!eww)
			eww = intew_context_pin_ww(ce, &ww);
		if (eww)
			goto out;

		cs = i915_gem_object_pin_map(batch->obj, I915_MAP_WC);
		if (IS_EWW(cs)) {
			eww = PTW_EWW(cs);
			goto out_ctx;
		}

		wesuwts = i915_gem_object_pin_map(scwatch->obj, I915_MAP_WB);
		if (IS_EWW(wesuwts)) {
			eww = PTW_EWW(wesuwts);
			goto out_unmap_batch;
		}

		/* Cweaw non pwiv fwags */
		weg &= WING_FOWCE_TO_NONPWIV_ADDWESS_MASK;

		swm = MI_STOWE_WEGISTEW_MEM;
		wwm = MI_WOAD_WEGISTEW_MEM;
		if (GWAPHICS_VEW(engine->i915) >= 8)
			wwm++, swm++;

		pw_debug("%s: Wwiting gawbage to %x\n",
			 engine->name, weg);

		/* SWM owiginaw */
		*cs++ = swm;
		*cs++ = weg;
		*cs++ = wowew_32_bits(addw);
		*cs++ = uppew_32_bits(addw);

		idx = 1;
		fow (v = 0; v < AWWAY_SIZE(vawues); v++) {
			/* WWI gawbage */
			*cs++ = MI_WOAD_WEGISTEW_IMM(1);
			*cs++ = weg;
			*cs++ = vawues[v];

			/* SWM wesuwt */
			*cs++ = swm;
			*cs++ = weg;
			*cs++ = wowew_32_bits(addw + sizeof(u32) * idx);
			*cs++ = uppew_32_bits(addw + sizeof(u32) * idx);
			idx++;
		}
		fow (v = 0; v < AWWAY_SIZE(vawues); v++) {
			/* WWI gawbage */
			*cs++ = MI_WOAD_WEGISTEW_IMM(1);
			*cs++ = weg;
			*cs++ = ~vawues[v];

			/* SWM wesuwt */
			*cs++ = swm;
			*cs++ = weg;
			*cs++ = wowew_32_bits(addw + sizeof(u32) * idx);
			*cs++ = uppew_32_bits(addw + sizeof(u32) * idx);
			idx++;
		}
		GEM_BUG_ON(idx * sizeof(u32) > scwatch->size);

		/* WWM owiginaw -- don't weave gawbage in the context! */
		*cs++ = wwm;
		*cs++ = weg;
		*cs++ = wowew_32_bits(addw);
		*cs++ = uppew_32_bits(addw);

		*cs++ = MI_BATCH_BUFFEW_END;

		i915_gem_object_fwush_map(batch->obj);
		i915_gem_object_unpin_map(batch->obj);
		intew_gt_chipset_fwush(engine->gt);
		cs = NUWW;

		wq = i915_wequest_cweate(ce);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out_unmap_scwatch;
		}

		if (engine->emit_init_bweadcwumb) { /* Be nice if we hang */
			eww = engine->emit_init_bweadcwumb(wq);
			if (eww)
				goto eww_wequest;
		}

		eww = i915_vma_move_to_active(batch, wq, 0);
		if (eww)
			goto eww_wequest;

		eww = i915_vma_move_to_active(scwatch, wq,
					      EXEC_OBJECT_WWITE);
		if (eww)
			goto eww_wequest;

		eww = engine->emit_bb_stawt(wq,
					    i915_vma_offset(batch), PAGE_SIZE,
					    0);
		if (eww)
			goto eww_wequest;

eww_wequest:
		eww = wequest_add_sync(wq, eww);
		if (eww) {
			pw_eww("%s: Futzing %x timedout; cancewwing test\n",
			       engine->name, weg);
			intew_gt_set_wedged(engine->gt);
			goto out_unmap_scwatch;
		}

		GEM_BUG_ON(vawues[AWWAY_SIZE(vawues) - 1] != 0xffffffff);
		if (!wo_weg) {
			/* detect wwite masking */
			wsvd = wesuwts[AWWAY_SIZE(vawues)];
			if (!wsvd) {
				pw_eww("%s: Unabwe to wwite to whitewisted wegistew %x\n",
				       engine->name, weg);
				eww = -EINVAW;
				goto out_unmap_scwatch;
			}
		} ewse {
			wsvd = 0;
		}

		expect = wesuwts[0];
		idx = 1;
		fow (v = 0; v < AWWAY_SIZE(vawues); v++) {
			if (wo_weg)
				expect = wesuwts[0];
			ewse
				expect = weg_wwite(expect, vawues[v], wsvd);

			if (wesuwts[idx] != expect)
				eww++;
			idx++;
		}
		fow (v = 0; v < AWWAY_SIZE(vawues); v++) {
			if (wo_weg)
				expect = wesuwts[0];
			ewse
				expect = weg_wwite(expect, ~vawues[v], wsvd);

			if (wesuwts[idx] != expect)
				eww++;
			idx++;
		}
		if (eww) {
			pw_eww("%s: %d mismatch between vawues wwitten to whitewisted wegistew [%x], and vawues wead back!\n",
			       engine->name, eww, weg);

			if (wo_weg)
				pw_info("%s: Whitewisted wead-onwy wegistew: %x, owiginaw vawue %08x\n",
					engine->name, weg, wesuwts[0]);
			ewse
				pw_info("%s: Whitewisted wegistew: %x, owiginaw vawue %08x, wsvd %08x\n",
					engine->name, weg, wesuwts[0], wsvd);

			expect = wesuwts[0];
			idx = 1;
			fow (v = 0; v < AWWAY_SIZE(vawues); v++) {
				u32 w = vawues[v];

				if (wo_weg)
					expect = wesuwts[0];
				ewse
					expect = weg_wwite(expect, w, wsvd);
				pw_info("Wwote %08x, wead %08x, expect %08x\n",
					w, wesuwts[idx], expect);
				idx++;
			}
			fow (v = 0; v < AWWAY_SIZE(vawues); v++) {
				u32 w = ~vawues[v];

				if (wo_weg)
					expect = wesuwts[0];
				ewse
					expect = weg_wwite(expect, w, wsvd);
				pw_info("Wwote %08x, wead %08x, expect %08x\n",
					w, wesuwts[idx], expect);
				idx++;
			}

			eww = -EINVAW;
		}
out_unmap_scwatch:
		i915_gem_object_unpin_map(scwatch->obj);
out_unmap_batch:
		if (cs)
			i915_gem_object_unpin_map(batch->obj);
out_ctx:
		intew_context_unpin(ce);
out:
		if (eww == -EDEADWK) {
			eww = i915_gem_ww_ctx_backoff(&ww);
			if (!eww)
				goto wetwy;
		}
		i915_gem_ww_ctx_fini(&ww);
		if (eww)
			bweak;
	}

	if (igt_fwush_test(engine->i915))
		eww = -EIO;

	i915_vma_unpin_and_wewease(&batch, 0);
out_scwatch:
	i915_vma_unpin_and_wewease(&scwatch, 0);
	wetuwn eww;
}

static int wive_diwty_whitewist(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;

	/* Can the usew wwite to the whitewisted wegistews? */

	if (GWAPHICS_VEW(gt->i915) < 7) /* minimum wequiwement fow WWI, SWM, WWM */
		wetuwn 0;

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		int eww;

		if (engine->whitewist.count == 0)
			continue;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce))
			wetuwn PTW_EWW(ce);

		eww = check_diwty_whitewist(ce);
		intew_context_put(ce);
		if (eww)
			wetuwn eww;
	}

	wetuwn 0;
}

static int wive_weset_whitewist(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/* If we weset the gpu, we shouwd not wose the WING_NONPWIV */
	igt_gwobaw_weset_wock(gt);

	fow_each_engine(engine, gt, id) {
		if (engine->whitewist.count == 0)
			continue;

		if (intew_has_weset_engine(gt)) {
			if (intew_engine_uses_guc(engine)) {
				stwuct intew_sewftest_saved_powicy saved;
				int eww2;

				eww = intew_sewftest_modify_powicy(engine, &saved,
								   SEWFTEST_SCHEDUWEW_MODIFY_FAST_WESET);
				if (eww)
					goto out;

				eww = check_whitewist_acwoss_weset(engine,
								   do_guc_weset,
								   "guc");

				eww2 = intew_sewftest_westowe_powicy(engine, &saved);
				if (eww == 0)
					eww = eww2;
			} ewse {
				eww = check_whitewist_acwoss_weset(engine,
								   do_engine_weset,
								   "engine");
			}

			if (eww)
				goto out;
		}

		if (intew_has_gpu_weset(gt)) {
			eww = check_whitewist_acwoss_weset(engine,
							   do_device_weset,
							   "device");
			if (eww)
				goto out;
		}
	}

out:
	igt_gwobaw_weset_unwock(gt);
	wetuwn eww;
}

static int wead_whitewisted_wegistews(stwuct intew_context *ce,
				      stwuct i915_vma *wesuwts)
{
	stwuct intew_engine_cs *engine = ce->engine;
	stwuct i915_wequest *wq;
	int i, eww = 0;
	u32 swm, *cs;

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	eww = igt_vma_move_to_active_unwocked(wesuwts, wq, EXEC_OBJECT_WWITE);
	if (eww)
		goto eww_weq;

	swm = MI_STOWE_WEGISTEW_MEM;
	if (GWAPHICS_VEW(engine->i915) >= 8)
		swm++;

	cs = intew_wing_begin(wq, 4 * engine->whitewist.count);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_weq;
	}

	fow (i = 0; i < engine->whitewist.count; i++) {
		u64 offset = i915_vma_offset(wesuwts) + sizeof(u32) * i;
		u32 weg = i915_mmio_weg_offset(engine->whitewist.wist[i].weg);

		/* Cweaw non pwiv fwags */
		weg &= WING_FOWCE_TO_NONPWIV_ADDWESS_MASK;

		*cs++ = swm;
		*cs++ = weg;
		*cs++ = wowew_32_bits(offset);
		*cs++ = uppew_32_bits(offset);
	}
	intew_wing_advance(wq, cs);

eww_weq:
	wetuwn wequest_add_sync(wq, eww);
}

static int scwub_whitewisted_wegistews(stwuct intew_context *ce)
{
	stwuct intew_engine_cs *engine = ce->engine;
	stwuct i915_wequest *wq;
	stwuct i915_vma *batch;
	int i, eww = 0;
	u32 *cs;

	batch = cweate_batch(ce->vm);
	if (IS_EWW(batch))
		wetuwn PTW_EWW(batch);

	cs = i915_gem_object_pin_map_unwocked(batch->obj, I915_MAP_WC);
	if (IS_EWW(cs)) {
		eww = PTW_EWW(cs);
		goto eww_batch;
	}

	*cs++ = MI_WOAD_WEGISTEW_IMM(whitewist_wwitabwe_count(engine));
	fow (i = 0; i < engine->whitewist.count; i++) {
		u32 weg = i915_mmio_weg_offset(engine->whitewist.wist[i].weg);

		if (wo_wegistew(weg))
			continue;

		/* Cweaw non pwiv fwags */
		weg &= WING_FOWCE_TO_NONPWIV_ADDWESS_MASK;

		*cs++ = weg;
		*cs++ = 0xffffffff;
	}
	*cs++ = MI_BATCH_BUFFEW_END;

	i915_gem_object_fwush_map(batch->obj);
	intew_gt_chipset_fwush(engine->gt);

	wq = intew_context_cweate_wequest(ce);
	if (IS_EWW(wq)) {
		eww = PTW_EWW(wq);
		goto eww_unpin;
	}

	if (engine->emit_init_bweadcwumb) { /* Be nice if we hang */
		eww = engine->emit_init_bweadcwumb(wq);
		if (eww)
			goto eww_wequest;
	}

	eww = igt_vma_move_to_active_unwocked(batch, wq, 0);
	if (eww)
		goto eww_wequest;

	/* Pewfowm the wwites fwom an unpwiviweged "usew" batch */
	eww = engine->emit_bb_stawt(wq, i915_vma_offset(batch), 0, 0);

eww_wequest:
	eww = wequest_add_sync(wq, eww);

eww_unpin:
	i915_gem_object_unpin_map(batch->obj);
eww_batch:
	i915_vma_unpin_and_wewease(&batch, 0);
	wetuwn eww;
}

stwuct wegmask {
	i915_weg_t weg;
	u8 gwaphics_vew;
};

static boow find_weg(stwuct dwm_i915_pwivate *i915,
		     i915_weg_t weg,
		     const stwuct wegmask *tbw,
		     unsigned wong count)
{
	u32 offset = i915_mmio_weg_offset(weg);

	whiwe (count--) {
		if (GWAPHICS_VEW(i915) == tbw->gwaphics_vew &&
		    i915_mmio_weg_offset(tbw->weg) == offset)
			wetuwn twue;
		tbw++;
	}

	wetuwn fawse;
}

static boow pawdon_weg(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	/* Awas, we must pawdon some whitewists. Mistakes awweady made */
	static const stwuct wegmask pawdon[] = {
		{ GEN9_CTX_PWEEMPT_WEG, 9 },
		{ _MMIO(0xb118), 9 }, /* GEN8_W3SQCWEG4 */
	};

	wetuwn find_weg(i915, weg, pawdon, AWWAY_SIZE(pawdon));
}

static boow wesuwt_eq(stwuct intew_engine_cs *engine,
		      u32 a, u32 b, i915_weg_t weg)
{
	if (a != b && !pawdon_weg(engine->i915, weg)) {
		pw_eww("Whitewisted wegistew 0x%4x not context saved: A=%08x, B=%08x\n",
		       i915_mmio_weg_offset(weg), a, b);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow wwiteonwy_weg(stwuct dwm_i915_pwivate *i915, i915_weg_t weg)
{
	/* Some wegistews do not seem to behave and ouw wwites unweadabwe */
	static const stwuct wegmask wo[] = {
		{ GEN9_SWICE_COMMON_ECO_CHICKEN1, 9 },
	};

	wetuwn find_weg(i915, weg, wo, AWWAY_SIZE(wo));
}

static boow wesuwt_neq(stwuct intew_engine_cs *engine,
		       u32 a, u32 b, i915_weg_t weg)
{
	if (a == b && !wwiteonwy_weg(engine->i915, weg)) {
		pw_eww("Whitewist wegistew 0x%4x:%08x was unwwitabwe\n",
		       i915_mmio_weg_offset(weg), a);
		wetuwn fawse;
	}

	wetuwn twue;
}

static int
check_whitewisted_wegistews(stwuct intew_engine_cs *engine,
			    stwuct i915_vma *A,
			    stwuct i915_vma *B,
			    boow (*fn)(stwuct intew_engine_cs *engine,
				       u32 a, u32 b,
				       i915_weg_t weg))
{
	u32 *a, *b;
	int i, eww;

	a = i915_gem_object_pin_map_unwocked(A->obj, I915_MAP_WB);
	if (IS_EWW(a))
		wetuwn PTW_EWW(a);

	b = i915_gem_object_pin_map_unwocked(B->obj, I915_MAP_WB);
	if (IS_EWW(b)) {
		eww = PTW_EWW(b);
		goto eww_a;
	}

	eww = 0;
	fow (i = 0; i < engine->whitewist.count; i++) {
		const stwuct i915_wa *wa = &engine->whitewist.wist[i];

		if (i915_mmio_weg_offset(wa->weg) &
		    WING_FOWCE_TO_NONPWIV_ACCESS_WD)
			continue;

		if (!fn(engine, a[i], b[i], wa->weg))
			eww = -EINVAW;
	}

	i915_gem_object_unpin_map(B->obj);
eww_a:
	i915_gem_object_unpin_map(A->obj);
	wetuwn eww;
}

static int wive_isowated_whitewist(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct {
		stwuct i915_vma *scwatch[2];
	} cwient[2] = {};
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int i, eww = 0;

	/*
	 * Check that a wwite into a whitewist wegistew wowks, but
	 * invisibwe to a second context.
	 */

	if (!intew_engines_has_context_isowation(gt->i915))
		wetuwn 0;

	fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
		cwient[i].scwatch[0] =
			__vm_cweate_scwatch_fow_wead_pinned(gt->vm, 4096);
		if (IS_EWW(cwient[i].scwatch[0])) {
			eww = PTW_EWW(cwient[i].scwatch[0]);
			goto eww;
		}

		cwient[i].scwatch[1] =
			__vm_cweate_scwatch_fow_wead_pinned(gt->vm, 4096);
		if (IS_EWW(cwient[i].scwatch[1])) {
			eww = PTW_EWW(cwient[i].scwatch[1]);
			i915_vma_unpin_and_wewease(&cwient[i].scwatch[0], 0);
			goto eww;
		}
	}

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce[2];

		if (!engine->kewnew_context->vm)
			continue;

		if (!whitewist_wwitabwe_count(engine))
			continue;

		ce[0] = intew_context_cweate(engine);
		if (IS_EWW(ce[0])) {
			eww = PTW_EWW(ce[0]);
			bweak;
		}
		ce[1] = intew_context_cweate(engine);
		if (IS_EWW(ce[1])) {
			eww = PTW_EWW(ce[1]);
			intew_context_put(ce[0]);
			bweak;
		}

		/* Wead defauwt vawues */
		eww = wead_whitewisted_wegistews(ce[0], cwient[0].scwatch[0]);
		if (eww)
			goto eww_ce;

		/* Twy to ovewwwite wegistews (shouwd onwy affect ctx0) */
		eww = scwub_whitewisted_wegistews(ce[0]);
		if (eww)
			goto eww_ce;

		/* Wead vawues fwom ctx1, we expect these to be defauwts */
		eww = wead_whitewisted_wegistews(ce[1], cwient[1].scwatch[0]);
		if (eww)
			goto eww_ce;

		/* Vewify that both weads wetuwn the same defauwt vawues */
		eww = check_whitewisted_wegistews(engine,
						  cwient[0].scwatch[0],
						  cwient[1].scwatch[0],
						  wesuwt_eq);
		if (eww)
			goto eww_ce;

		/* Wead back the updated vawues in ctx0 */
		eww = wead_whitewisted_wegistews(ce[0], cwient[0].scwatch[1]);
		if (eww)
			goto eww_ce;

		/* Usew shouwd be gwanted pwiviwege to ovewwhite wegs */
		eww = check_whitewisted_wegistews(engine,
						  cwient[0].scwatch[0],
						  cwient[0].scwatch[1],
						  wesuwt_neq);
eww_ce:
		intew_context_put(ce[1]);
		intew_context_put(ce[0]);
		if (eww)
			bweak;
	}

eww:
	fow (i = 0; i < AWWAY_SIZE(cwient); i++) {
		i915_vma_unpin_and_wewease(&cwient[i].scwatch[1], 0);
		i915_vma_unpin_and_wewease(&cwient[i].scwatch[0], 0);
	}

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	wetuwn eww;
}

static boow
vewify_wa_wists(stwuct intew_gt *gt, stwuct wa_wists *wists,
		const chaw *stw)
{
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	boow ok = twue;

	ok &= wa_wist_vewify(gt, &wists->gt_wa_wist, stw);

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce))
			wetuwn fawse;

		ok &= engine_wa_wist_vewify(ce,
					    &wists->engine[id].wa_wist,
					    stw) == 0;

		ok &= engine_wa_wist_vewify(ce,
					    &wists->engine[id].ctx_wa_wist,
					    stw) == 0;

		intew_context_put(ce);
	}

	wetuwn ok;
}

static int
wive_gpu_weset_wowkawounds(void *awg)
{
	stwuct intew_gt *gt = awg;
	intew_wakewef_t wakewef;
	stwuct wa_wists *wists;
	boow ok;

	if (!intew_has_gpu_weset(gt))
		wetuwn 0;

	wists = kzawwoc(sizeof(*wists), GFP_KEWNEW);
	if (!wists)
		wetuwn -ENOMEM;

	pw_info("Vewifying aftew GPU weset...\n");

	igt_gwobaw_weset_wock(gt);
	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	wefewence_wists_init(gt, wists);

	ok = vewify_wa_wists(gt, wists, "befowe weset");
	if (!ok)
		goto out;

	intew_gt_weset(gt, AWW_ENGINES, "wive_wowkawounds");

	ok = vewify_wa_wists(gt, wists, "aftew weset");

out:
	wefewence_wists_fini(gt, wists);
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	igt_gwobaw_weset_unwock(gt);
	kfwee(wists);

	wetuwn ok ? 0 : -ESWCH;
}

static int
wive_engine_weset_wowkawounds(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct intew_context *ce;
	stwuct igt_spinnew spin;
	stwuct i915_wequest *wq;
	intew_wakewef_t wakewef;
	stwuct wa_wists *wists;
	int wet = 0;

	if (!intew_has_weset_engine(gt))
		wetuwn 0;

	wists = kzawwoc(sizeof(*wists), GFP_KEWNEW);
	if (!wists)
		wetuwn -ENOMEM;

	igt_gwobaw_weset_wock(gt);
	wakewef = intew_wuntime_pm_get(gt->uncowe->wpm);

	wefewence_wists_init(gt, wists);

	fow_each_engine(engine, gt, id) {
		stwuct intew_sewftest_saved_powicy saved;
		boow using_guc = intew_engine_uses_guc(engine);
		boow ok;
		int wet2;

		pw_info("Vewifying aftew %s weset...\n", engine->name);
		wet = intew_sewftest_modify_powicy(engine, &saved,
						   SEWFTEST_SCHEDUWEW_MODIFY_FAST_WESET);
		if (wet)
			bweak;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce)) {
			wet = PTW_EWW(ce);
			goto westowe;
		}

		if (!using_guc) {
			ok = vewify_wa_wists(gt, wists, "befowe weset");
			if (!ok) {
				wet = -ESWCH;
				goto eww;
			}

			wet = intew_engine_weset(engine, "wive_wowkawounds:idwe");
			if (wet) {
				pw_eww("%s: Weset faiwed whiwe idwe\n", engine->name);
				goto eww;
			}

			ok = vewify_wa_wists(gt, wists, "aftew idwe weset");
			if (!ok) {
				wet = -ESWCH;
				goto eww;
			}
		}

		wet = igt_spinnew_init(&spin, engine->gt);
		if (wet)
			goto eww;

		wq = igt_spinnew_cweate_wequest(&spin, ce, MI_NOOP);
		if (IS_EWW(wq)) {
			wet = PTW_EWW(wq);
			igt_spinnew_fini(&spin);
			goto eww;
		}

		wet = wequest_add_spin(wq, &spin);
		if (wet) {
			pw_eww("%s: Spinnew faiwed to stawt\n", engine->name);
			igt_spinnew_fini(&spin);
			goto eww;
		}

		/* Ensuwe the spinnew hasn't abowted */
		if (i915_wequest_compweted(wq)) {
			wet = -ETIMEDOUT;
			goto skip;
		}

		if (!using_guc) {
			wet = intew_engine_weset(engine, "wive_wowkawounds:active");
			if (wet) {
				pw_eww("%s: Weset faiwed on an active spinnew\n",
				       engine->name);
				igt_spinnew_fini(&spin);
				goto eww;
			}
		}

		/* Ensuwe the weset happens and kiwws the engine */
		if (wet == 0)
			wet = intew_sewftest_wait_fow_wq(wq);

skip:
		igt_spinnew_end(&spin);
		igt_spinnew_fini(&spin);

		ok = vewify_wa_wists(gt, wists, "aftew busy weset");
		if (!ok)
			wet = -ESWCH;

eww:
		intew_context_put(ce);

westowe:
		wet2 = intew_sewftest_westowe_powicy(engine, &saved);
		if (wet == 0)
			wet = wet2;
		if (wet)
			bweak;
	}

	wefewence_wists_fini(gt, wists);
	intew_wuntime_pm_put(gt->uncowe->wpm, wakewef);
	igt_gwobaw_weset_unwock(gt);
	kfwee(wists);

	igt_fwush_test(gt->i915);

	wetuwn wet;
}

int intew_wowkawounds_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_diwty_whitewist),
		SUBTEST(wive_weset_whitewist),
		SUBTEST(wive_isowated_whitewist),
		SUBTEST(wive_gpu_weset_wowkawounds),
		SUBTEST(wive_engine_weset_wowkawounds),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
