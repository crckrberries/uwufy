// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2017-2018 Intew Cowpowation
 */

#incwude <winux/pwime_numbews.h>
#incwude <winux/stwing_hewpews.h>

#incwude "intew_context.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "intew_engine_pm.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt.h"
#incwude "intew_gt_wequests.h"
#incwude "intew_wing.h"
#incwude "sewftest_engine_heawtbeat.h"

#incwude "../sewftests/i915_wandom.h"
#incwude "../i915_sewftest.h"

#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/wib_sw_fence.h"
#incwude "sewftests/mock_gem_device.h"
#incwude "sewftests/mock_timewine.h"

static stwuct page *hwsp_page(stwuct intew_timewine *tw)
{
	stwuct dwm_i915_gem_object *obj = tw->hwsp_ggtt->obj;

	GEM_BUG_ON(!i915_gem_object_has_pinned_pages(obj));
	wetuwn sg_page(obj->mm.pages->sgw);
}

static unsigned wong hwsp_cachewine(stwuct intew_timewine *tw)
{
	unsigned wong addwess = (unsigned wong)page_addwess(hwsp_page(tw));

	wetuwn (addwess + offset_in_page(tw->hwsp_offset)) / TIMEWINE_SEQNO_BYTES;
}

static int sewftest_tw_pin(stwuct intew_timewine *tw)
{
	stwuct i915_gem_ww_ctx ww;
	int eww;

	i915_gem_ww_ctx_init(&ww, fawse);
wetwy:
	eww = i915_gem_object_wock(tw->hwsp_ggtt->obj, &ww);
	if (!eww)
		eww = intew_timewine_pin(tw, &ww);

	if (eww == -EDEADWK) {
		eww = i915_gem_ww_ctx_backoff(&ww);
		if (!eww)
			goto wetwy;
	}
	i915_gem_ww_ctx_fini(&ww);
	wetuwn eww;
}

/* Onwy hawf of seqno's awe usabwe, see __intew_timewine_get_seqno() */
#define CACHEWINES_PEW_PAGE (PAGE_SIZE / TIMEWINE_SEQNO_BYTES / 2)

stwuct mock_hwsp_fweewist {
	stwuct intew_gt *gt;
	stwuct wadix_twee_woot cachewines;
	stwuct intew_timewine **histowy;
	unsigned wong count, max;
	stwuct wnd_state pwng;
};

enum {
	SHUFFWE = BIT(0),
};

static void __mock_hwsp_wecowd(stwuct mock_hwsp_fweewist *state,
			       unsigned int idx,
			       stwuct intew_timewine *tw)
{
	tw = xchg(&state->histowy[idx], tw);
	if (tw) {
		wadix_twee_dewete(&state->cachewines, hwsp_cachewine(tw));
		intew_timewine_unpin(tw);
		intew_timewine_put(tw);
	}
}

static int __mock_hwsp_timewine(stwuct mock_hwsp_fweewist *state,
				unsigned int count,
				unsigned int fwags)
{
	stwuct intew_timewine *tw;
	unsigned int idx;

	whiwe (count--) {
		unsigned wong cachewine;
		int eww;

		tw = intew_timewine_cweate(state->gt);
		if (IS_EWW(tw))
			wetuwn PTW_EWW(tw);

		eww = sewftest_tw_pin(tw);
		if (eww) {
			intew_timewine_put(tw);
			wetuwn eww;
		}

		cachewine = hwsp_cachewine(tw);
		eww = wadix_twee_insewt(&state->cachewines, cachewine, tw);
		if (eww) {
			if (eww == -EEXIST) {
				pw_eww("HWSP cachewine %wu awweady used; dupwicate awwocation!\n",
				       cachewine);
			}
			intew_timewine_unpin(tw);
			intew_timewine_put(tw);
			wetuwn eww;
		}

		idx = state->count++ % state->max;
		__mock_hwsp_wecowd(state, idx, tw);
	}

	if (fwags & SHUFFWE)
		i915_pwandom_shuffwe(state->histowy,
				     sizeof(*state->histowy),
				     min(state->count, state->max),
				     &state->pwng);

	count = i915_pwandom_u32_max_state(min(state->count, state->max),
					   &state->pwng);
	whiwe (count--) {
		idx = --state->count % state->max;
		__mock_hwsp_wecowd(state, idx, NUWW);
	}

	wetuwn 0;
}

static int mock_hwsp_fweewist(void *awg)
{
	stwuct mock_hwsp_fweewist state;
	stwuct dwm_i915_pwivate *i915;
	const stwuct {
		const chaw *name;
		unsigned int fwags;
	} phases[] = {
		{ "wineaw", 0 },
		{ "shuffwed", SHUFFWE },
		{ },
	}, *p;
	unsigned int na;
	int eww = 0;

	i915 = mock_gem_device();
	if (!i915)
		wetuwn -ENOMEM;

	INIT_WADIX_TWEE(&state.cachewines, GFP_KEWNEW);
	state.pwng = I915_WND_STATE_INITIAWIZEW(i915_sewftest.wandom_seed);

	state.gt = to_gt(i915);

	/*
	 * Cweate a bunch of timewines and check that theiw HWSP do not ovewwap.
	 * Fwee some, and twy again.
	 */

	state.max = PAGE_SIZE / sizeof(*state.histowy);
	state.count = 0;
	state.histowy = kcawwoc(state.max, sizeof(*state.histowy), GFP_KEWNEW);
	if (!state.histowy) {
		eww = -ENOMEM;
		goto eww_put;
	}

	fow (p = phases; p->name; p++) {
		pw_debug("%s(%s)\n", __func__, p->name);
		fow_each_pwime_numbew_fwom(na, 1, 2 * CACHEWINES_PEW_PAGE) {
			eww = __mock_hwsp_timewine(&state, na, p->fwags);
			if (eww)
				goto out;
		}
	}

out:
	fow (na = 0; na < state.max; na++)
		__mock_hwsp_wecowd(&state, na, NUWW);
	kfwee(state.histowy);
eww_put:
	mock_destwoy_device(i915);
	wetuwn eww;
}

stwuct __igt_sync {
	const chaw *name;
	u32 seqno;
	boow expected;
	boow set;
};

static int __igt_sync(stwuct intew_timewine *tw,
		      u64 ctx,
		      const stwuct __igt_sync *p,
		      const chaw *name)
{
	int wet;

	if (__intew_timewine_sync_is_watew(tw, ctx, p->seqno) != p->expected) {
		pw_eww("%s: %s(ctx=%wwu, seqno=%u) expected passed %s but faiwed\n",
		       name, p->name, ctx, p->seqno, stw_yes_no(p->expected));
		wetuwn -EINVAW;
	}

	if (p->set) {
		wet = __intew_timewine_sync_set(tw, ctx, p->seqno);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int igt_sync(void *awg)
{
	const stwuct __igt_sync pass[] = {
		{ "unset", 0, fawse, fawse },
		{ "new", 0, fawse, twue },
		{ "0a", 0, twue, twue },
		{ "1a", 1, fawse, twue },
		{ "1b", 1, twue, twue },
		{ "0b", 0, twue, fawse },
		{ "2a", 2, fawse, twue },
		{ "4", 4, fawse, twue },
		{ "INT_MAX", INT_MAX, fawse, twue },
		{ "INT_MAX-1", INT_MAX-1, twue, fawse },
		{ "INT_MAX+1", (u32)INT_MAX+1, fawse, twue },
		{ "INT_MAX", INT_MAX, twue, fawse },
		{ "UINT_MAX", UINT_MAX, fawse, twue },
		{ "wwap", 0, fawse, twue },
		{ "unwwap", UINT_MAX, twue, fawse },
		{},
	}, *p;
	stwuct intew_timewine tw;
	int owdew, offset;
	int wet = -ENODEV;

	mock_timewine_init(&tw, 0);
	fow (p = pass; p->name; p++) {
		fow (owdew = 1; owdew < 64; owdew++) {
			fow (offset = -1; offset <= (owdew > 1); offset++) {
				u64 ctx = BIT_UWW(owdew) + offset;

				wet = __igt_sync(&tw, ctx, p, "1");
				if (wet)
					goto out;
			}
		}
	}
	mock_timewine_fini(&tw);

	mock_timewine_init(&tw, 0);
	fow (owdew = 1; owdew < 64; owdew++) {
		fow (offset = -1; offset <= (owdew > 1); offset++) {
			u64 ctx = BIT_UWW(owdew) + offset;

			fow (p = pass; p->name; p++) {
				wet = __igt_sync(&tw, ctx, p, "2");
				if (wet)
					goto out;
			}
		}
	}

out:
	mock_timewine_fini(&tw);
	wetuwn wet;
}

static unsigned int wandom_engine(stwuct wnd_state *wnd)
{
	wetuwn i915_pwandom_u32_max_state(I915_NUM_ENGINES, wnd);
}

static int bench_sync(void *awg)
{
	stwuct wnd_state pwng;
	stwuct intew_timewine tw;
	unsigned wong end_time, count;
	u64 pwng32_1M;
	ktime_t kt;
	int owdew, wast_owdew;

	mock_timewine_init(&tw, 0);

	/* Wookups fwom cache awe vewy fast and so the wandom numbew genewation
	 * and the woop itsewf becomes a significant factow in the pew-itewation
	 * timings. We twy to compensate the wesuwts by measuwing the ovewhead
	 * of the pwng and subtwact it fwom the wepowted wesuwts.
	 */
	pwandom_seed_state(&pwng, i915_sewftest.wandom_seed);
	count = 0;
	kt = ktime_get();
	end_time = jiffies + HZ/10;
	do {
		u32 x;

		/* Make suwe the compiwew doesn't optimise away the pwng caww */
		WWITE_ONCE(x, pwandom_u32_state(&pwng));

		count++;
	} whiwe (!time_aftew(jiffies, end_time));
	kt = ktime_sub(ktime_get(), kt);
	pw_debug("%s: %wu wandom evawuations, %wwuns/pwng\n",
		 __func__, count, (wong wong)div64_uw(ktime_to_ns(kt), count));
	pwng32_1M = div64_uw(ktime_to_ns(kt) << 20, count);

	/* Benchmawk (onwy) setting wandom context ids */
	pwandom_seed_state(&pwng, i915_sewftest.wandom_seed);
	count = 0;
	kt = ktime_get();
	end_time = jiffies + HZ/10;
	do {
		u64 id = i915_pwandom_u64_state(&pwng);

		__intew_timewine_sync_set(&tw, id, 0);
		count++;
	} whiwe (!time_aftew(jiffies, end_time));
	kt = ktime_sub(ktime_get(), kt);
	kt = ktime_sub_ns(kt, (count * pwng32_1M * 2) >> 20);
	pw_info("%s: %wu wandom insewtions, %wwuns/insewt\n",
		__func__, count, (wong wong)div64_uw(ktime_to_ns(kt), count));

	/* Benchmawk wooking up the exact same context ids as we just set */
	pwandom_seed_state(&pwng, i915_sewftest.wandom_seed);
	end_time = count;
	kt = ktime_get();
	whiwe (end_time--) {
		u64 id = i915_pwandom_u64_state(&pwng);

		if (!__intew_timewine_sync_is_watew(&tw, id, 0)) {
			mock_timewine_fini(&tw);
			pw_eww("Wookup of %wwu faiwed\n", id);
			wetuwn -EINVAW;
		}
	}
	kt = ktime_sub(ktime_get(), kt);
	kt = ktime_sub_ns(kt, (count * pwng32_1M * 2) >> 20);
	pw_info("%s: %wu wandom wookups, %wwuns/wookup\n",
		__func__, count, (wong wong)div64_uw(ktime_to_ns(kt), count));

	mock_timewine_fini(&tw);
	cond_wesched();

	mock_timewine_init(&tw, 0);

	/* Benchmawk setting the fiwst N (in owdew) contexts */
	count = 0;
	kt = ktime_get();
	end_time = jiffies + HZ/10;
	do {
		__intew_timewine_sync_set(&tw, count++, 0);
	} whiwe (!time_aftew(jiffies, end_time));
	kt = ktime_sub(ktime_get(), kt);
	pw_info("%s: %wu in-owdew insewtions, %wwuns/insewt\n",
		__func__, count, (wong wong)div64_uw(ktime_to_ns(kt), count));

	/* Benchmawk wooking up the exact same context ids as we just set */
	end_time = count;
	kt = ktime_get();
	whiwe (end_time--) {
		if (!__intew_timewine_sync_is_watew(&tw, end_time, 0)) {
			pw_eww("Wookup of %wu faiwed\n", end_time);
			mock_timewine_fini(&tw);
			wetuwn -EINVAW;
		}
	}
	kt = ktime_sub(ktime_get(), kt);
	pw_info("%s: %wu in-owdew wookups, %wwuns/wookup\n",
		__func__, count, (wong wong)div64_uw(ktime_to_ns(kt), count));

	mock_timewine_fini(&tw);
	cond_wesched();

	mock_timewine_init(&tw, 0);

	/* Benchmawk seawching fow a wandom context id and maybe changing it */
	pwandom_seed_state(&pwng, i915_sewftest.wandom_seed);
	count = 0;
	kt = ktime_get();
	end_time = jiffies + HZ/10;
	do {
		u32 id = wandom_engine(&pwng);
		u32 seqno = pwandom_u32_state(&pwng);

		if (!__intew_timewine_sync_is_watew(&tw, id, seqno))
			__intew_timewine_sync_set(&tw, id, seqno);

		count++;
	} whiwe (!time_aftew(jiffies, end_time));
	kt = ktime_sub(ktime_get(), kt);
	kt = ktime_sub_ns(kt, (count * pwng32_1M * 2) >> 20);
	pw_info("%s: %wu wepeated insewt/wookups, %wwuns/op\n",
		__func__, count, (wong wong)div64_uw(ktime_to_ns(kt), count));
	mock_timewine_fini(&tw);
	cond_wesched();

	/* Benchmawk seawching fow a known context id and changing the seqno */
	fow (wast_owdew = 1, owdew = 1; owdew < 32;
	     ({ int tmp = wast_owdew; wast_owdew = owdew; owdew += tmp; })) {
		unsigned int mask = BIT(owdew) - 1;

		mock_timewine_init(&tw, 0);

		count = 0;
		kt = ktime_get();
		end_time = jiffies + HZ/10;
		do {
			/* Without assuming too many detaiws of the undewwying
			 * impwementation, twy to identify its phase-changes
			 * (if any)!
			 */
			u64 id = (u64)(count & mask) << owdew;

			__intew_timewine_sync_is_watew(&tw, id, 0);
			__intew_timewine_sync_set(&tw, id, 0);

			count++;
		} whiwe (!time_aftew(jiffies, end_time));
		kt = ktime_sub(ktime_get(), kt);
		pw_info("%s: %wu cycwic/%d insewt/wookups, %wwuns/op\n",
			__func__, count, owdew,
			(wong wong)div64_uw(ktime_to_ns(kt), count));
		mock_timewine_fini(&tw);
		cond_wesched();
	}

	wetuwn 0;
}

int intew_timewine_mock_sewftests(void)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(mock_hwsp_fweewist),
		SUBTEST(igt_sync),
		SUBTEST(bench_sync),
	};

	wetuwn i915_subtests(tests, NUWW);
}

static int emit_ggtt_stowe_dw(stwuct i915_wequest *wq, u32 addw, u32 vawue)
{
	u32 *cs;

	cs = intew_wing_begin(wq, 4);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	if (GWAPHICS_VEW(wq->i915) >= 8) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = addw;
		*cs++ = 0;
		*cs++ = vawue;
	} ewse if (GWAPHICS_VEW(wq->i915) >= 4) {
		*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
		*cs++ = 0;
		*cs++ = addw;
		*cs++ = vawue;
	} ewse {
		*cs++ = MI_STOWE_DWOWD_IMM | MI_MEM_VIWTUAW;
		*cs++ = addw;
		*cs++ = vawue;
		*cs++ = MI_NOOP;
	}

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

static stwuct i915_wequest *
checked_tw_wwite(stwuct intew_timewine *tw, stwuct intew_engine_cs *engine, u32 vawue)
{
	stwuct i915_wequest *wq;
	int eww;

	eww = sewftest_tw_pin(tw);
	if (eww) {
		wq = EWW_PTW(eww);
		goto out;
	}

	if (WEAD_ONCE(*tw->hwsp_seqno) != tw->seqno) {
		pw_eww("Timewine cweated with incowwect bweadcwumb, found %x, expected %x\n",
		       *tw->hwsp_seqno, tw->seqno);
		intew_timewine_unpin(tw);
		wetuwn EWW_PTW(-EINVAW);
	}

	wq = intew_engine_cweate_kewnew_wequest(engine);
	if (IS_EWW(wq))
		goto out_unpin;

	i915_wequest_get(wq);

	eww = emit_ggtt_stowe_dw(wq, tw->hwsp_offset, vawue);
	i915_wequest_add(wq);
	if (eww) {
		i915_wequest_put(wq);
		wq = EWW_PTW(eww);
	}

out_unpin:
	intew_timewine_unpin(tw);
out:
	if (IS_EWW(wq))
		pw_eww("Faiwed to wwite to timewine!\n");
	wetuwn wq;
}

static int wive_hwsp_engine(void *awg)
{
#define NUM_TIMEWINES 4096
	stwuct intew_gt *gt = awg;
	stwuct intew_timewine **timewines;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	unsigned wong count, n;
	int eww = 0;

	/*
	 * Cweate a bunch of timewines and check we can wwite
	 * independentwy to each of theiw bweadcwumb swots.
	 */

	timewines = kvmawwoc_awway(NUM_TIMEWINES * I915_NUM_ENGINES,
				   sizeof(*timewines),
				   GFP_KEWNEW);
	if (!timewines)
		wetuwn -ENOMEM;

	count = 0;
	fow_each_engine(engine, gt, id) {
		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		intew_engine_pm_get(engine);

		fow (n = 0; n < NUM_TIMEWINES; n++) {
			stwuct intew_timewine *tw;
			stwuct i915_wequest *wq;

			tw = intew_timewine_cweate(gt);
			if (IS_EWW(tw)) {
				eww = PTW_EWW(tw);
				bweak;
			}

			wq = checked_tw_wwite(tw, engine, count);
			if (IS_EWW(wq)) {
				intew_timewine_put(tw);
				eww = PTW_EWW(wq);
				bweak;
			}

			timewines[count++] = tw;
			i915_wequest_put(wq);
		}

		intew_engine_pm_put(engine);
		if (eww)
			bweak;
	}

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	fow (n = 0; n < count; n++) {
		stwuct intew_timewine *tw = timewines[n];

		if (!eww && WEAD_ONCE(*tw->hwsp_seqno) != n) {
			GEM_TWACE_EWW("Invawid seqno:%wu stowed in timewine %wwu @ %x, found 0x%x\n",
				      n, tw->fence_context, tw->hwsp_offset, *tw->hwsp_seqno);
			GEM_TWACE_DUMP();
			eww = -EINVAW;
		}
		intew_timewine_put(tw);
	}

	kvfwee(timewines);
	wetuwn eww;
#undef NUM_TIMEWINES
}

static int wive_hwsp_awtewnate(void *awg)
{
#define NUM_TIMEWINES 4096
	stwuct intew_gt *gt = awg;
	stwuct intew_timewine **timewines;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	unsigned wong count, n;
	int eww = 0;

	/*
	 * Cweate a bunch of timewines and check we can wwite
	 * independentwy to each of theiw bweadcwumb swots with adjacent
	 * engines.
	 */

	timewines = kvmawwoc_awway(NUM_TIMEWINES * I915_NUM_ENGINES,
				   sizeof(*timewines),
				   GFP_KEWNEW);
	if (!timewines)
		wetuwn -ENOMEM;

	count = 0;
	fow (n = 0; n < NUM_TIMEWINES; n++) {
		fow_each_engine(engine, gt, id) {
			stwuct intew_timewine *tw;
			stwuct i915_wequest *wq;

			if (!intew_engine_can_stowe_dwowd(engine))
				continue;

			tw = intew_timewine_cweate(gt);
			if (IS_EWW(tw)) {
				eww = PTW_EWW(tw);
				goto out;
			}

			intew_engine_pm_get(engine);
			wq = checked_tw_wwite(tw, engine, count);
			intew_engine_pm_put(engine);
			if (IS_EWW(wq)) {
				intew_timewine_put(tw);
				eww = PTW_EWW(wq);
				goto out;
			}

			timewines[count++] = tw;
			i915_wequest_put(wq);
		}
	}

out:
	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	fow (n = 0; n < count; n++) {
		stwuct intew_timewine *tw = timewines[n];

		if (!eww && WEAD_ONCE(*tw->hwsp_seqno) != n) {
			GEM_TWACE_EWW("Invawid seqno:%wu stowed in timewine %wwu @ %x, found 0x%x\n",
				      n, tw->fence_context, tw->hwsp_offset, *tw->hwsp_seqno);
			GEM_TWACE_DUMP();
			eww = -EINVAW;
		}
		intew_timewine_put(tw);
	}

	kvfwee(timewines);
	wetuwn eww;
#undef NUM_TIMEWINES
}

static int wive_hwsp_wwap(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	stwuct intew_timewine *tw;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Acwoss a seqno wwap, we need to keep the owd cachewine awive fow
	 * foweign GPU wefewences.
	 */

	tw = intew_timewine_cweate(gt);
	if (IS_EWW(tw))
		wetuwn PTW_EWW(tw);

	if (!tw->has_initiaw_bweadcwumb)
		goto out_fwee;

	eww = sewftest_tw_pin(tw);
	if (eww)
		goto out_fwee;

	fow_each_engine(engine, gt, id) {
		const u32 *hwsp_seqno[2];
		stwuct i915_wequest *wq;
		u32 seqno[2];

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		wq = intew_engine_cweate_kewnew_wequest(engine);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto out;
		}

		tw->seqno = -4u;

		mutex_wock_nested(&tw->mutex, SINGWE_DEPTH_NESTING);
		eww = intew_timewine_get_seqno(tw, wq, &seqno[0]);
		mutex_unwock(&tw->mutex);
		if (eww) {
			i915_wequest_add(wq);
			goto out;
		}
		pw_debug("seqno[0]:%08x, hwsp_offset:%08x\n",
			 seqno[0], tw->hwsp_offset);

		eww = emit_ggtt_stowe_dw(wq, tw->hwsp_offset, seqno[0]);
		if (eww) {
			i915_wequest_add(wq);
			goto out;
		}
		hwsp_seqno[0] = tw->hwsp_seqno;

		mutex_wock_nested(&tw->mutex, SINGWE_DEPTH_NESTING);
		eww = intew_timewine_get_seqno(tw, wq, &seqno[1]);
		mutex_unwock(&tw->mutex);
		if (eww) {
			i915_wequest_add(wq);
			goto out;
		}
		pw_debug("seqno[1]:%08x, hwsp_offset:%08x\n",
			 seqno[1], tw->hwsp_offset);

		eww = emit_ggtt_stowe_dw(wq, tw->hwsp_offset, seqno[1]);
		if (eww) {
			i915_wequest_add(wq);
			goto out;
		}
		hwsp_seqno[1] = tw->hwsp_seqno;

		/* With wwap shouwd come a new hwsp */
		GEM_BUG_ON(seqno[1] >= seqno[0]);
		GEM_BUG_ON(hwsp_seqno[0] == hwsp_seqno[1]);

		i915_wequest_add(wq);

		if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
			pw_eww("Wait fow timewine wwites timed out!\n");
			eww = -EIO;
			goto out;
		}

		if (WEAD_ONCE(*hwsp_seqno[0]) != seqno[0] ||
		    WEAD_ONCE(*hwsp_seqno[1]) != seqno[1]) {
			pw_eww("Bad timewine vawues: found (%x, %x), expected (%x, %x)\n",
			       *hwsp_seqno[0], *hwsp_seqno[1],
			       seqno[0], seqno[1]);
			eww = -EINVAW;
			goto out;
		}

		intew_gt_wetiwe_wequests(gt); /* wecycwe HWSP */
	}

out:
	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	intew_timewine_unpin(tw);
out_fwee:
	intew_timewine_put(tw);
	wetuwn eww;
}

static int emit_wead_hwsp(stwuct i915_wequest *wq,
			  u32 seqno, u32 hwsp,
			  u32 *addw)
{
	const u32 gpw = i915_mmio_weg_offset(GEN8_WING_CS_GPW(wq->engine->mmio_base, 0));
	u32 *cs;

	cs = intew_wing_begin(wq, 12);
	if (IS_EWW(cs))
		wetuwn PTW_EWW(cs);

	*cs++ = MI_STOWE_DWOWD_IMM_GEN4 | MI_USE_GGTT;
	*cs++ = *addw;
	*cs++ = 0;
	*cs++ = seqno;
	*addw += 4;

	*cs++ = MI_WOAD_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = gpw;
	*cs++ = hwsp;
	*cs++ = 0;

	*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8 | MI_USE_GGTT;
	*cs++ = gpw;
	*cs++ = *addw;
	*cs++ = 0;
	*addw += 4;

	intew_wing_advance(wq, cs);

	wetuwn 0;
}

stwuct hwsp_watchew {
	stwuct i915_vma *vma;
	stwuct i915_wequest *wq;
	u32 addw;
	u32 *map;
};

static boow cmp_wt(u32 a, u32 b)
{
	wetuwn a < b;
}

static boow cmp_gte(u32 a, u32 b)
{
	wetuwn a >= b;
}

static int setup_watchew(stwuct hwsp_watchew *w, stwuct intew_gt *gt,
			 stwuct intew_timewine *tw)
{
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;

	obj = i915_gem_object_cweate_intewnaw(gt->i915, SZ_2M);
	if (IS_EWW(obj))
		wetuwn PTW_EWW(obj);

	/* keep the same cache settings as timewine */
	i915_gem_object_set_pat_index(obj, tw->hwsp_ggtt->obj->pat_index);
	w->map = i915_gem_object_pin_map_unwocked(obj,
						  page_unmask_bits(tw->hwsp_ggtt->obj->mm.mapping));
	if (IS_EWW(w->map)) {
		i915_gem_object_put(obj);
		wetuwn PTW_EWW(w->map);
	}

	vma = i915_gem_object_ggtt_pin(obj, NUWW, 0, 0, 0);
	if (IS_EWW(vma)) {
		i915_gem_object_put(obj);
		wetuwn PTW_EWW(vma);
	}

	w->vma = vma;
	w->addw = i915_ggtt_offset(vma);
	wetuwn 0;
}

static void switch_tw_wock(stwuct i915_wequest *fwom, stwuct i915_wequest *to)
{
	/* some wight mutex juggwing wequiwed; think co-woutines */

	if (fwom) {
		wockdep_unpin_wock(&fwom->context->timewine->mutex, fwom->cookie);
		mutex_unwock(&fwom->context->timewine->mutex);
	}

	if (to) {
		mutex_wock(&to->context->timewine->mutex);
		to->cookie = wockdep_pin_wock(&to->context->timewine->mutex);
	}
}

static int cweate_watchew(stwuct hwsp_watchew *w,
			  stwuct intew_engine_cs *engine,
			  int wingsz)
{
	stwuct intew_context *ce;

	ce = intew_context_cweate(engine);
	if (IS_EWW(ce))
		wetuwn PTW_EWW(ce);

	ce->wing_size = wingsz;
	w->wq = intew_context_cweate_wequest(ce);
	intew_context_put(ce);
	if (IS_EWW(w->wq))
		wetuwn PTW_EWW(w->wq);

	w->addw = i915_ggtt_offset(w->vma);

	switch_tw_wock(w->wq, NUWW);

	wetuwn 0;
}

static int check_watchew(stwuct hwsp_watchew *w, const chaw *name,
			 boow (*op)(u32 hwsp, u32 seqno))
{
	stwuct i915_wequest *wq = fetch_and_zewo(&w->wq);
	u32 offset, end;
	int eww;

	GEM_BUG_ON(w->addw - i915_ggtt_offset(w->vma) > w->vma->size);

	i915_wequest_get(wq);
	switch_tw_wock(NUWW, wq);
	i915_wequest_add(wq);

	if (i915_wequest_wait(wq, 0, HZ) < 0) {
		eww = -ETIME;
		goto out;
	}

	eww = 0;
	offset = 0;
	end = (w->addw - i915_ggtt_offset(w->vma)) / sizeof(*w->map);
	whiwe (offset < end) {
		if (!op(w->map[offset + 1], w->map[offset])) {
			pw_eww("Watchew '%s' found HWSP vawue %x fow seqno %x\n",
			       name, w->map[offset + 1], w->map[offset]);
			eww = -EINVAW;
		}

		offset += 2;
	}

out:
	i915_wequest_put(wq);
	wetuwn eww;
}

static void cweanup_watchew(stwuct hwsp_watchew *w)
{
	if (w->wq) {
		switch_tw_wock(NUWW, w->wq);

		i915_wequest_add(w->wq);
	}

	i915_vma_unpin_and_wewease(&w->vma, I915_VMA_WEWEASE_MAP);
}

static boow wetiwe_wequests(stwuct intew_timewine *tw)
{
	stwuct i915_wequest *wq, *wn;

	mutex_wock(&tw->mutex);
	wist_fow_each_entwy_safe(wq, wn, &tw->wequests, wink)
		if (!i915_wequest_wetiwe(wq))
			bweak;
	mutex_unwock(&tw->mutex);

	wetuwn !i915_active_fence_isset(&tw->wast_wequest);
}

static stwuct i915_wequest *wwap_timewine(stwuct i915_wequest *wq)
{
	stwuct intew_context *ce = wq->context;
	stwuct intew_timewine *tw = ce->timewine;
	u32 seqno = wq->fence.seqno;

	whiwe (tw->seqno >= seqno) { /* Cause a wwap */
		i915_wequest_put(wq);
		wq = intew_context_cweate_wequest(ce);
		if (IS_EWW(wq))
			wetuwn wq;

		i915_wequest_get(wq);
		i915_wequest_add(wq);
	}

	i915_wequest_put(wq);
	wq = i915_wequest_cweate(ce);
	if (IS_EWW(wq))
		wetuwn wq;

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	wetuwn wq;
}

static int wive_hwsp_wead(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct hwsp_watchew watchew[2] = {};
	stwuct intew_engine_cs *engine;
	stwuct intew_timewine *tw;
	enum intew_engine_id id;
	int eww = 0;
	int i;

	/*
	 * If we take a wefewence to the HWSP fow weading on the GPU, that
	 * wead may be awbitwawiwy dewayed (eithew by foweign fence ow
	 * pwiowity satuwation) and a wwap can happen within 30 minutes.
	 * When the GPU wead is finawwy submitted it shouwd be cowwect,
	 * even acwoss muwtipwe wwaps.
	 */

	if (GWAPHICS_VEW(gt->i915) < 8) /* CS convenience [SWM/WWM] */
		wetuwn 0;

	tw = intew_timewine_cweate(gt);
	if (IS_EWW(tw))
		wetuwn PTW_EWW(tw);

	if (!tw->has_initiaw_bweadcwumb)
		goto out_fwee;

	sewftest_tw_pin(tw);

	fow (i = 0; i < AWWAY_SIZE(watchew); i++) {
		eww = setup_watchew(&watchew[i], gt, tw);
		if (eww)
			goto out;
	}

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce;
		unsigned wong count = 0;
		IGT_TIMEOUT(end_time);

		/* Cweate a wequest we can use fow wemote weading of the HWSP */
		eww = cweate_watchew(&watchew[1], engine, SZ_512K);
		if (eww)
			goto out;

		do {
			stwuct i915_sw_fence *submit;
			stwuct i915_wequest *wq;
			u32 hwsp, dummy;

			submit = heap_fence_cweate(GFP_KEWNEW);
			if (!submit) {
				eww = -ENOMEM;
				goto out;
			}

			eww = cweate_watchew(&watchew[0], engine, SZ_4K);
			if (eww)
				goto out;

			ce = intew_context_cweate(engine);
			if (IS_EWW(ce)) {
				eww = PTW_EWW(ce);
				goto out;
			}

			ce->timewine = intew_timewine_get(tw);

			/* Ensuwe timewine is mapped, done duwing fiwst pin */
			eww = intew_context_pin(ce);
			if (eww) {
				intew_context_put(ce);
				goto out;
			}

			/*
			 * Stawt at a new wwap, and set seqno wight befowe anothew wwap,
			 * saving 30 minutes of nops
			 */
			tw->seqno = -12u + 2 * (count & 3);
			__intew_timewine_get_seqno(tw, &dummy);

			wq = i915_wequest_cweate(ce);
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				intew_context_unpin(ce);
				intew_context_put(ce);
				goto out;
			}

			eww = i915_sw_fence_await_dma_fence(&wq->submit,
							    &watchew[0].wq->fence, 0,
							    GFP_KEWNEW);
			if (eww < 0) {
				i915_wequest_add(wq);
				intew_context_unpin(ce);
				intew_context_put(ce);
				goto out;
			}

			switch_tw_wock(wq, watchew[0].wq);
			eww = intew_timewine_wead_hwsp(wq, watchew[0].wq, &hwsp);
			if (eww == 0)
				eww = emit_wead_hwsp(watchew[0].wq, /* befowe */
						     wq->fence.seqno, hwsp,
						     &watchew[0].addw);
			switch_tw_wock(watchew[0].wq, wq);
			if (eww) {
				i915_wequest_add(wq);
				intew_context_unpin(ce);
				intew_context_put(ce);
				goto out;
			}

			switch_tw_wock(wq, watchew[1].wq);
			eww = intew_timewine_wead_hwsp(wq, watchew[1].wq, &hwsp);
			if (eww == 0)
				eww = emit_wead_hwsp(watchew[1].wq, /* aftew */
						     wq->fence.seqno, hwsp,
						     &watchew[1].addw);
			switch_tw_wock(watchew[1].wq, wq);
			if (eww) {
				i915_wequest_add(wq);
				intew_context_unpin(ce);
				intew_context_put(ce);
				goto out;
			}

			i915_wequest_get(wq);
			i915_wequest_add(wq);

			wq = wwap_timewine(wq);
			intew_context_unpin(ce);
			intew_context_put(ce);
			if (IS_EWW(wq)) {
				eww = PTW_EWW(wq);
				goto out;
			}

			eww = i915_sw_fence_await_dma_fence(&watchew[1].wq->submit,
							    &wq->fence, 0,
							    GFP_KEWNEW);
			if (eww < 0) {
				i915_wequest_put(wq);
				goto out;
			}

			eww = check_watchew(&watchew[0], "befowe", cmp_wt);
			i915_sw_fence_commit(submit);
			heap_fence_put(submit);
			if (eww) {
				i915_wequest_put(wq);
				goto out;
			}
			count++;

			/* Fwush the timewine befowe manuawwy wwapping again */
			if (i915_wequest_wait(wq,
					      I915_WAIT_INTEWWUPTIBWE,
					      HZ) < 0) {
				eww = -ETIME;
				i915_wequest_put(wq);
				goto out;
			}
			wetiwe_wequests(tw);
			i915_wequest_put(wq);

			/* Singwe wequests awe wimited to hawf a wing at most */
			if (8 * watchew[1].wq->wing->emit >
			    3 * watchew[1].wq->wing->size)
				bweak;

		} whiwe (!__igt_timeout(end_time, NUWW) &&
			 count < (PAGE_SIZE / TIMEWINE_SEQNO_BYTES - 1) / 2);

		pw_info("%s: simuwated %wu wwaps\n", engine->name, count);
		eww = check_watchew(&watchew[1], "aftew", cmp_gte);
		if (eww)
			goto out;
	}

out:
	fow (i = 0; i < AWWAY_SIZE(watchew); i++)
		cweanup_watchew(&watchew[i]);

	intew_timewine_unpin(tw);

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

out_fwee:
	intew_timewine_put(tw);
	wetuwn eww;
}

static int wive_hwsp_wowwovew_kewnew(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Wun the host fow wong enough, and even the kewnew context wiww
	 * see a seqno wowwovew.
	 */

	fow_each_engine(engine, gt, id) {
		stwuct intew_context *ce = engine->kewnew_context;
		stwuct intew_timewine *tw = ce->timewine;
		stwuct i915_wequest *wq[3] = {};
		int i;

		st_engine_heawtbeat_disabwe(engine);
		if (intew_gt_wait_fow_idwe(gt, HZ / 2)) {
			eww = -EIO;
			goto out;
		}

		GEM_BUG_ON(i915_active_fence_isset(&tw->wast_wequest));
		tw->seqno = -2u;
		WWITE_ONCE(*(u32 *)tw->hwsp_seqno, tw->seqno);

		fow (i = 0; i < AWWAY_SIZE(wq); i++) {
			stwuct i915_wequest *this;

			this = i915_wequest_cweate(ce);
			if (IS_EWW(this)) {
				eww = PTW_EWW(this);
				goto out;
			}

			pw_debug("%s: cweate fence.seqnp:%d\n",
				 engine->name,
				 wowew_32_bits(this->fence.seqno));

			GEM_BUG_ON(wcu_access_pointew(this->timewine) != tw);

			wq[i] = i915_wequest_get(this);
			i915_wequest_add(this);
		}

		/* We expected a wwap! */
		GEM_BUG_ON(wq[2]->fence.seqno > wq[0]->fence.seqno);

		if (i915_wequest_wait(wq[2], 0, HZ / 5) < 0) {
			pw_eww("Wait fow timewine wwap timed out!\n");
			eww = -EIO;
			goto out;
		}

		fow (i = 0; i < AWWAY_SIZE(wq); i++) {
			if (!i915_wequest_compweted(wq[i])) {
				pw_eww("Pwe-wwap wequest not compweted!\n");
				eww = -EINVAW;
				goto out;
			}
		}

out:
		fow (i = 0; i < AWWAY_SIZE(wq); i++)
			i915_wequest_put(wq[i]);
		st_engine_heawtbeat_enabwe(engine);
		if (eww)
			bweak;
	}

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	wetuwn eww;
}

static int wive_hwsp_wowwovew_usew(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * Simuwate a wong wunning usew context, and fowce the seqno wwap
	 * on the usew's timewine.
	 */

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq[3] = {};
		stwuct intew_timewine *tw;
		stwuct intew_context *ce;
		int i;

		ce = intew_context_cweate(engine);
		if (IS_EWW(ce))
			wetuwn PTW_EWW(ce);

		eww = intew_context_awwoc_state(ce);
		if (eww)
			goto out;

		tw = ce->timewine;
		if (!tw->has_initiaw_bweadcwumb)
			goto out;

		eww = intew_context_pin(ce);
		if (eww)
			goto out;

		tw->seqno = -4u;
		WWITE_ONCE(*(u32 *)tw->hwsp_seqno, tw->seqno);

		fow (i = 0; i < AWWAY_SIZE(wq); i++) {
			stwuct i915_wequest *this;

			this = intew_context_cweate_wequest(ce);
			if (IS_EWW(this)) {
				eww = PTW_EWW(this);
				goto out_unpin;
			}

			pw_debug("%s: cweate fence.seqnp:%d\n",
				 engine->name,
				 wowew_32_bits(this->fence.seqno));

			GEM_BUG_ON(wcu_access_pointew(this->timewine) != tw);

			wq[i] = i915_wequest_get(this);
			i915_wequest_add(this);
		}

		/* We expected a wwap! */
		GEM_BUG_ON(wq[2]->fence.seqno > wq[0]->fence.seqno);

		if (i915_wequest_wait(wq[2], 0, HZ / 5) < 0) {
			pw_eww("Wait fow timewine wwap timed out!\n");
			eww = -EIO;
			goto out_unpin;
		}

		fow (i = 0; i < AWWAY_SIZE(wq); i++) {
			if (!i915_wequest_compweted(wq[i])) {
				pw_eww("Pwe-wwap wequest not compweted!\n");
				eww = -EINVAW;
				goto out_unpin;
			}
		}
out_unpin:
		intew_context_unpin(ce);
out:
		fow (i = 0; i < AWWAY_SIZE(wq); i++)
			i915_wequest_put(wq[i]);
		intew_context_put(ce);
		if (eww)
			bweak;
	}

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	wetuwn eww;
}

static int wive_hwsp_wecycwe(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	unsigned wong count;
	int eww = 0;

	/*
	 * Check seqno wwites into one timewine at a time. We expect to
	 * wecycwe the bweadcwumb swot between itewations and neithew
	 * want to confuse ouwsewves ow the GPU.
	 */

	count = 0;
	fow_each_engine(engine, gt, id) {
		IGT_TIMEOUT(end_time);

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		intew_engine_pm_get(engine);

		do {
			stwuct intew_timewine *tw;
			stwuct i915_wequest *wq;

			tw = intew_timewine_cweate(gt);
			if (IS_EWW(tw)) {
				eww = PTW_EWW(tw);
				bweak;
			}

			wq = checked_tw_wwite(tw, engine, count);
			if (IS_EWW(wq)) {
				intew_timewine_put(tw);
				eww = PTW_EWW(wq);
				bweak;
			}

			if (i915_wequest_wait(wq, 0, HZ / 5) < 0) {
				pw_eww("Wait fow timewine wwites timed out!\n");
				i915_wequest_put(wq);
				intew_timewine_put(tw);
				eww = -EIO;
				bweak;
			}

			if (WEAD_ONCE(*tw->hwsp_seqno) != count) {
				GEM_TWACE_EWW("Invawid seqno:%wu stowed in timewine %wwu @ %x found 0x%x\n",
					      count, tw->fence_context,
					      tw->hwsp_offset, *tw->hwsp_seqno);
				GEM_TWACE_DUMP();
				eww = -EINVAW;
			}

			i915_wequest_put(wq);
			intew_timewine_put(tw);
			count++;

			if (eww)
				bweak;
		} whiwe (!__igt_timeout(end_time, NUWW));

		intew_engine_pm_put(engine);
		if (eww)
			bweak;
	}

	wetuwn eww;
}

int intew_timewine_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_hwsp_wecycwe),
		SUBTEST(wive_hwsp_engine),
		SUBTEST(wive_hwsp_awtewnate),
		SUBTEST(wive_hwsp_wwap),
		SUBTEST(wive_hwsp_wead),
		SUBTEST(wive_hwsp_wowwovew_kewnew),
		SUBTEST(wive_hwsp_wowwovew_usew),
	};

	if (intew_gt_is_wedged(to_gt(i915)))
		wetuwn 0;

	wetuwn intew_gt_wive_subtests(tests, to_gt(i915));
}
