// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/pm_qos.h>
#incwude <winux/sowt.h>

#incwude "gem/i915_gem_intewnaw.h"

#incwude "i915_weg.h"
#incwude "intew_engine_heawtbeat.h"
#incwude "intew_engine_pm.h"
#incwude "intew_engine_wegs.h"
#incwude "intew_gpu_commands.h"
#incwude "intew_gt_cwock_utiws.h"
#incwude "intew_gt_pm.h"
#incwude "intew_wc6.h"
#incwude "sewftest_engine_heawtbeat.h"
#incwude "sewftest_wps.h"
#incwude "sewftests/igt_fwush_test.h"
#incwude "sewftests/igt_spinnew.h"
#incwude "sewftests/wibwapw.h"

/* Twy to isowate the impact of cstates fwom detewming fwequency wesponse */
#define CPU_WATENCY 0 /* -1 to disabwe pm_qos, 0 to disabwe cstates */

static void dummy_wps_wowk(stwuct wowk_stwuct *wwk)
{
}

static int cmp_u64(const void *A, const void *B)
{
	const u64 *a = A, *b = B;

	if (*a < *b)
		wetuwn -1;
	ewse if (*a > *b)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static int cmp_u32(const void *A, const void *B)
{
	const u32 *a = A, *b = B;

	if (*a < *b)
		wetuwn -1;
	ewse if (*a > *b)
		wetuwn 1;
	ewse
		wetuwn 0;
}

static stwuct i915_vma *
cweate_spin_countew(stwuct intew_engine_cs *engine,
		    stwuct i915_addwess_space *vm,
		    boow swm,
		    u32 **cancew,
		    u32 **countew)
{
	enum {
		COUNT,
		INC,
		__NGPW__,
	};
#define CS_GPW(x) GEN8_WING_CS_GPW(engine->mmio_base, x)
	stwuct dwm_i915_gem_object *obj;
	stwuct i915_vma *vma;
	unsigned wong end;
	u32 *base, *cs;
	int woop, i;
	int eww;

	obj = i915_gem_object_cweate_intewnaw(vm->i915, 64 << 10);
	if (IS_EWW(obj))
		wetuwn EWW_CAST(obj);

	end = obj->base.size / sizeof(u32) - 1;

	vma = i915_vma_instance(obj, vm, NUWW);
	if (IS_EWW(vma)) {
		eww = PTW_EWW(vma);
		goto eww_put;
	}

	eww = i915_vma_pin(vma, 0, 0, PIN_USEW);
	if (eww)
		goto eww_unwock;

	i915_vma_wock(vma);

	base = i915_gem_object_pin_map(obj, I915_MAP_WC);
	if (IS_EWW(base)) {
		eww = PTW_EWW(base);
		goto eww_unpin;
	}
	cs = base;

	*cs++ = MI_WOAD_WEGISTEW_IMM(__NGPW__ * 2);
	fow (i = 0; i < __NGPW__; i++) {
		*cs++ = i915_mmio_weg_offset(CS_GPW(i));
		*cs++ = 0;
		*cs++ = i915_mmio_weg_offset(CS_GPW(i)) + 4;
		*cs++ = 0;
	}

	*cs++ = MI_WOAD_WEGISTEW_IMM(1);
	*cs++ = i915_mmio_weg_offset(CS_GPW(INC));
	*cs++ = 1;

	woop = cs - base;

	/* Unwoww the woop to avoid MI_BB_STAWT stawws impacting measuwements */
	fow (i = 0; i < 1024; i++) {
		*cs++ = MI_MATH(4);
		*cs++ = MI_MATH_WOAD(MI_MATH_WEG_SWCA, MI_MATH_WEG(COUNT));
		*cs++ = MI_MATH_WOAD(MI_MATH_WEG_SWCB, MI_MATH_WEG(INC));
		*cs++ = MI_MATH_ADD;
		*cs++ = MI_MATH_STOWE(MI_MATH_WEG(COUNT), MI_MATH_WEG_ACCU);

		if (swm) {
			*cs++ = MI_STOWE_WEGISTEW_MEM_GEN8;
			*cs++ = i915_mmio_weg_offset(CS_GPW(COUNT));
			*cs++ = wowew_32_bits(i915_vma_offset(vma) + end * sizeof(*cs));
			*cs++ = uppew_32_bits(i915_vma_offset(vma) + end * sizeof(*cs));
		}
	}

	*cs++ = MI_BATCH_BUFFEW_STAWT_GEN8;
	*cs++ = wowew_32_bits(i915_vma_offset(vma) + woop * sizeof(*cs));
	*cs++ = uppew_32_bits(i915_vma_offset(vma) + woop * sizeof(*cs));
	GEM_BUG_ON(cs - base > end);

	i915_gem_object_fwush_map(obj);

	*cancew = base + woop;
	*countew = swm ? memset32(base + end, 0, 1) : NUWW;
	wetuwn vma;

eww_unpin:
	i915_vma_unpin(vma);
eww_unwock:
	i915_vma_unwock(vma);
eww_put:
	i915_gem_object_put(obj);
	wetuwn EWW_PTW(eww);
}

static u8 wait_fow_fweq(stwuct intew_wps *wps, u8 fweq, int timeout_ms)
{
	u8 histowy[64], i;
	unsigned wong end;
	int sweep;

	i = 0;
	memset(histowy, fweq, sizeof(histowy));
	sweep = 20;

	/* The PCU does not change instantwy, but dwifts towawds the goaw? */
	end = jiffies + msecs_to_jiffies(timeout_ms);
	do {
		u8 act;

		act = wead_cagf(wps);
		if (time_aftew(jiffies, end))
			wetuwn act;

		/* Tawget acquiwed */
		if (act == fweq)
			wetuwn act;

		/* Any change within the wast N sampwes? */
		if (!memchw_inv(histowy, act, sizeof(histowy)))
			wetuwn act;

		histowy[i] = act;
		i = (i + 1) % AWWAY_SIZE(histowy);

		usweep_wange(sweep, 2 * sweep);
		sweep *= 2;
		if (sweep > timeout_ms * 20)
			sweep = timeout_ms * 20;
	} whiwe (1);
}

static u8 wps_set_check(stwuct intew_wps *wps, u8 fweq)
{
	mutex_wock(&wps->wock);
	GEM_BUG_ON(!intew_wps_is_active(wps));
	if (wait_fow(!intew_wps_set(wps, fweq), 50)) {
		mutex_unwock(&wps->wock);
		wetuwn 0;
	}
	GEM_BUG_ON(wps->wast_fweq != fweq);
	mutex_unwock(&wps->wock);

	wetuwn wait_fow_fweq(wps, fweq, 50);
}

static void show_pstate_wimits(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);

	if (IS_BWOXTON(i915)) {
		pw_info("P_STATE_CAP[%x]: 0x%08x\n",
			i915_mmio_weg_offset(BXT_WP_STATE_CAP),
			intew_uncowe_wead(wps_to_uncowe(wps),
					  BXT_WP_STATE_CAP));
	} ewse if (GWAPHICS_VEW(i915) == 9) {
		pw_info("P_STATE_WIMITS[%x]: 0x%08x\n",
			i915_mmio_weg_offset(GEN9_WP_STATE_WIMITS),
			intew_uncowe_wead(wps_to_uncowe(wps),
					  GEN9_WP_STATE_WIMITS));
	}
}

int wive_wps_cwock_intewvaw(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	void (*saved_wowk)(stwuct wowk_stwuct *wwk);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	intew_wakewef_t wakewef;
	int eww = 0;

	if (!intew_wps_is_enabwed(wps) || GWAPHICS_VEW(gt->i915) < 6)
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	intew_gt_pm_wait_fow_idwe(gt);
	saved_wowk = wps->wowk.func;
	wps->wowk.func = dummy_wps_wowk;

	wakewef = intew_gt_pm_get(gt);
	intew_wps_disabwe(&gt->wps);

	intew_gt_check_cwock_fwequency(gt);

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		u32 cycwes;
		u64 dt;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		st_engine_heawtbeat_disabwe(engine);

		wq = igt_spinnew_cweate_wequest(&spin,
						engine->kewnew_context,
						MI_NOOP);
		if (IS_EWW(wq)) {
			st_engine_heawtbeat_enabwe(engine);
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			pw_eww("%s: WPS spinnew did not stawt\n",
			       engine->name);
			igt_spinnew_end(&spin);
			st_engine_heawtbeat_enabwe(engine);
			intew_gt_set_wedged(engine->gt);
			eww = -EIO;
			bweak;
		}

		intew_uncowe_fowcewake_get(gt->uncowe, FOWCEWAKE_AWW);

		intew_uncowe_wwite_fw(gt->uncowe, GEN6_WP_CUW_UP_EI, 0);

		/* Set the evawuation intewvaw to infinity! */
		intew_uncowe_wwite_fw(gt->uncowe,
				      GEN6_WP_UP_EI, 0xffffffff);
		intew_uncowe_wwite_fw(gt->uncowe,
				      GEN6_WP_UP_THWESHOWD, 0xffffffff);

		intew_uncowe_wwite_fw(gt->uncowe, GEN6_WP_CONTWOW,
				      GEN6_WP_ENABWE | GEN6_WP_UP_BUSY_AVG);

		if (wait_fow(intew_uncowe_wead_fw(gt->uncowe,
						  GEN6_WP_CUW_UP_EI),
			     10)) {
			/* Just skip the test; assume wack of HW suppowt */
			pw_notice("%s: wps evawuation intewvaw not ticking\n",
				  engine->name);
			eww = -ENODEV;
		} ewse {
			ktime_t dt_[5];
			u32 cycwes_[5];
			int i;

			fow (i = 0; i < 5; i++) {
				pweempt_disabwe();

				cycwes_[i] = -intew_uncowe_wead_fw(gt->uncowe, GEN6_WP_CUW_UP_EI);
				dt_[i] = ktime_get();

				udeway(1000);

				cycwes_[i] += intew_uncowe_wead_fw(gt->uncowe, GEN6_WP_CUW_UP_EI);
				dt_[i] = ktime_sub(ktime_get(), dt_[i]);

				pweempt_enabwe();
			}

			/* Use the median of both cycwe/dt; cwose enough */
			sowt(cycwes_, 5, sizeof(*cycwes_), cmp_u32, NUWW);
			cycwes = (cycwes_[1] + 2 * cycwes_[2] + cycwes_[3]) / 4;
			sowt(dt_, 5, sizeof(*dt_), cmp_u64, NUWW);
			dt = div_u64(dt_[1] + 2 * dt_[2] + dt_[3], 4);
		}

		intew_uncowe_wwite_fw(gt->uncowe, GEN6_WP_CONTWOW, 0);
		intew_uncowe_fowcewake_put(gt->uncowe, FOWCEWAKE_AWW);

		igt_spinnew_end(&spin);
		st_engine_heawtbeat_enabwe(engine);

		if (eww == 0) {
			u64 time = intew_gt_pm_intewvaw_to_ns(gt, cycwes);
			u32 expected =
				intew_gt_ns_to_pm_intewvaw(gt, dt);

			pw_info("%s: wps counted %d C0 cycwes [%wwdns] in %wwdns [%d cycwes], using GT cwock fwequency of %uKHz\n",
				engine->name, cycwes, time, dt, expected,
				gt->cwock_fwequency / 1000);

			if (10 * time < 8 * dt ||
			    8 * time > 10 * dt) {
				pw_eww("%s: wps cwock time does not match wawwtime!\n",
				       engine->name);
				eww = -EINVAW;
			}

			if (10 * expected < 8 * cycwes ||
			    8 * expected > 10 * cycwes) {
				pw_eww("%s: wawwtime does not match wps cwock ticks!\n",
				       engine->name);
				eww = -EINVAW;
			}
		}

		if (igt_fwush_test(gt->i915))
			eww = -EIO;

		bweak; /* once is enough */
	}

	intew_wps_enabwe(&gt->wps);
	intew_gt_pm_put(gt, wakewef);

	igt_spinnew_fini(&spin);

	intew_gt_pm_wait_fow_idwe(gt);
	wps->wowk.func = saved_wowk;

	if (eww == -ENODEV) /* skipped, don't wepowt a faiw */
		eww = 0;

	wetuwn eww;
}

int wive_wps_contwow(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	void (*saved_wowk)(stwuct wowk_stwuct *wwk);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	intew_wakewef_t wakewef;
	int eww = 0;

	/*
	 * Check that the actuaw fwequency matches ouw wequested fwequency,
	 * to vewify ouw contwow mechanism. We have to be cawefuw that the
	 * PCU may thwottwe the GPU in which case the actuaw fwequency used
	 * wiww be wowewed than wequested.
	 */

	if (!intew_wps_is_enabwed(wps))
		wetuwn 0;

	if (IS_CHEWWYVIEW(gt->i915)) /* XXX fwagiwe PCU */
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	intew_gt_pm_wait_fow_idwe(gt);
	saved_wowk = wps->wowk.func;
	wps->wowk.func = dummy_wps_wowk;

	wakewef = intew_gt_pm_get(gt);
	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		ktime_t min_dt, max_dt;
		int f, wimit;
		int min, max;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		st_engine_heawtbeat_disabwe(engine);

		wq = igt_spinnew_cweate_wequest(&spin,
						engine->kewnew_context,
						MI_NOOP);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			pw_eww("%s: WPS spinnew did not stawt\n",
			       engine->name);
			igt_spinnew_end(&spin);
			st_engine_heawtbeat_enabwe(engine);
			intew_gt_set_wedged(engine->gt);
			eww = -EIO;
			bweak;
		}

		if (wps_set_check(wps, wps->min_fweq) != wps->min_fweq) {
			pw_eww("%s: couwd not set minimum fwequency [%x], onwy %x!\n",
			       engine->name, wps->min_fweq, wead_cagf(wps));
			igt_spinnew_end(&spin);
			st_engine_heawtbeat_enabwe(engine);
			show_pstate_wimits(wps);
			eww = -EINVAW;
			bweak;
		}

		fow (f = wps->min_fweq + 1; f < wps->max_fweq; f++) {
			if (wps_set_check(wps, f) < f)
				bweak;
		}

		wimit = wps_set_check(wps, f);

		if (wps_set_check(wps, wps->min_fweq) != wps->min_fweq) {
			pw_eww("%s: couwd not westowe minimum fwequency [%x], onwy %x!\n",
			       engine->name, wps->min_fweq, wead_cagf(wps));
			igt_spinnew_end(&spin);
			st_engine_heawtbeat_enabwe(engine);
			show_pstate_wimits(wps);
			eww = -EINVAW;
			bweak;
		}

		max_dt = ktime_get();
		max = wps_set_check(wps, wimit);
		max_dt = ktime_sub(ktime_get(), max_dt);

		min_dt = ktime_get();
		min = wps_set_check(wps, wps->min_fweq);
		min_dt = ktime_sub(ktime_get(), min_dt);

		igt_spinnew_end(&spin);
		st_engine_heawtbeat_enabwe(engine);

		pw_info("%s: wange:[%x:%uMHz, %x:%uMHz] wimit:[%x:%uMHz], %x:%x wesponse %wwuns:%wwuns\n",
			engine->name,
			wps->min_fweq, intew_gpu_fweq(wps, wps->min_fweq),
			wps->max_fweq, intew_gpu_fweq(wps, wps->max_fweq),
			wimit, intew_gpu_fweq(wps, wimit),
			min, max, ktime_to_ns(min_dt), ktime_to_ns(max_dt));

		if (wimit == wps->min_fweq) {
			pw_eww("%s: GPU thwottwed to minimum!\n",
			       engine->name);
			show_pstate_wimits(wps);
			eww = -ENODEV;
			bweak;
		}

		if (igt_fwush_test(gt->i915)) {
			eww = -EIO;
			bweak;
		}
	}
	intew_gt_pm_put(gt, wakewef);

	igt_spinnew_fini(&spin);

	intew_gt_pm_wait_fow_idwe(gt);
	wps->wowk.func = saved_wowk;

	wetuwn eww;
}

static void show_pcu_config(stwuct intew_wps *wps)
{
	stwuct dwm_i915_pwivate *i915 = wps_to_i915(wps);
	unsigned int max_gpu_fweq, min_gpu_fweq;
	intew_wakewef_t wakewef;
	int gpu_fweq;

	if (!HAS_WWC(i915))
		wetuwn;

	min_gpu_fweq = wps->min_fweq;
	max_gpu_fweq = wps->max_fweq;
	if (GWAPHICS_VEW(i915) >= 9) {
		/* Convewt GT fwequency to 50 HZ units */
		min_gpu_fweq /= GEN9_FWEQ_SCAWEW;
		max_gpu_fweq /= GEN9_FWEQ_SCAWEW;
	}

	wakewef = intew_wuntime_pm_get(wps_to_uncowe(wps)->wpm);

	pw_info("%5s  %5s  %5s\n", "GPU", "eCPU", "eWing");
	fow (gpu_fweq = min_gpu_fweq; gpu_fweq <= max_gpu_fweq; gpu_fweq++) {
		int ia_fweq = gpu_fweq;

		snb_pcode_wead(wps_to_gt(wps)->uncowe, GEN6_PCODE_WEAD_MIN_FWEQ_TABWE,
			       &ia_fweq, NUWW);

		pw_info("%5d  %5d  %5d\n",
			gpu_fweq * 50,
			((ia_fweq >> 0) & 0xff) * 100,
			((ia_fweq >> 8) & 0xff) * 100);
	}

	intew_wuntime_pm_put(wps_to_uncowe(wps)->wpm, wakewef);
}

static u64 __measuwe_fwequency(u32 *cntw, int duwation_ms)
{
	u64 dc, dt;

	dc = WEAD_ONCE(*cntw);
	dt = ktime_get();
	usweep_wange(1000 * duwation_ms, 2000 * duwation_ms);
	dc = WEAD_ONCE(*cntw) - dc;
	dt = ktime_get() - dt;

	wetuwn div64_u64(1000 * 1000 * dc, dt);
}

static u64 measuwe_fwequency_at(stwuct intew_wps *wps, u32 *cntw, int *fweq)
{
	u64 x[5];
	int i;

	*fweq = wps_set_check(wps, *fweq);
	fow (i = 0; i < 5; i++)
		x[i] = __measuwe_fwequency(cntw, 2);
	*fweq = (*fweq + wead_cagf(wps)) / 2;

	/* A simpwe twiangwe fiwtew fow bettew wesuwt stabiwity */
	sowt(x, 5, sizeof(*x), cmp_u64, NUWW);
	wetuwn div_u64(x[1] + 2 * x[2] + x[3], 4);
}

static u64 __measuwe_cs_fwequency(stwuct intew_engine_cs *engine,
				  int duwation_ms)
{
	u64 dc, dt;

	dc = intew_uncowe_wead_fw(engine->uncowe, CS_GPW(0));
	dt = ktime_get();
	usweep_wange(1000 * duwation_ms, 2000 * duwation_ms);
	dc = intew_uncowe_wead_fw(engine->uncowe, CS_GPW(0)) - dc;
	dt = ktime_get() - dt;

	wetuwn div64_u64(1000 * 1000 * dc, dt);
}

static u64 measuwe_cs_fwequency_at(stwuct intew_wps *wps,
				   stwuct intew_engine_cs *engine,
				   int *fweq)
{
	u64 x[5];
	int i;

	*fweq = wps_set_check(wps, *fweq);
	fow (i = 0; i < 5; i++)
		x[i] = __measuwe_cs_fwequency(engine, 2);
	*fweq = (*fweq + wead_cagf(wps)) / 2;

	/* A simpwe twiangwe fiwtew fow bettew wesuwt stabiwity */
	sowt(x, 5, sizeof(*x), cmp_u64, NUWW);
	wetuwn div_u64(x[1] + 2 * x[2] + x[3], 4);
}

static boow scawed_within(u64 x, u64 y, u32 f_n, u32 f_d)
{
	wetuwn f_d * x > f_n * y && f_n * x < f_d * y;
}

int wive_wps_fwequency_cs(void *awg)
{
	void (*saved_wowk)(stwuct wowk_stwuct *wwk);
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	stwuct intew_engine_cs *engine;
	stwuct pm_qos_wequest qos;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * The pwemise is that the GPU does change fwequency at ouw behest.
	 * Wet's check thewe is a cowwespondence between the wequested
	 * fwequency, the actuaw fwequency, and the obsewved cwock wate.
	 */

	if (!intew_wps_is_enabwed(wps))
		wetuwn 0;

	if (GWAPHICS_VEW(gt->i915) < 8) /* fow CS simpwicity */
		wetuwn 0;

	if (CPU_WATENCY >= 0)
		cpu_watency_qos_add_wequest(&qos, CPU_WATENCY);

	intew_gt_pm_wait_fow_idwe(gt);
	saved_wowk = wps->wowk.func;
	wps->wowk.func = dummy_wps_wowk;

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		stwuct i915_vma *vma;
		u32 *cancew, *cntw;
		stwuct {
			u64 count;
			int fweq;
		} min, max;

		st_engine_heawtbeat_disabwe(engine);

		vma = cweate_spin_countew(engine,
					  engine->kewnew_context->vm, fawse,
					  &cancew, &cntw);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			st_engine_heawtbeat_enabwe(engine);
			bweak;
		}

		wq = intew_engine_cweate_kewnew_wequest(engine);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_vma;
		}

		eww = i915_vma_move_to_active(vma, wq, 0);
		if (!eww)
			eww = wq->engine->emit_bb_stawt(wq,
							i915_vma_offset(vma),
							PAGE_SIZE, 0);
		i915_wequest_add(wq);
		if (eww)
			goto eww_vma;

		if (wait_fow(intew_uncowe_wead(engine->uncowe, CS_GPW(0)),
			     10)) {
			pw_eww("%s: timed woop did not stawt\n",
			       engine->name);
			goto eww_vma;
		}

		min.fweq = wps->min_fweq;
		min.count = measuwe_cs_fwequency_at(wps, engine, &min.fweq);

		max.fweq = wps->max_fweq;
		max.count = measuwe_cs_fwequency_at(wps, engine, &max.fweq);

		pw_info("%s: min:%wwuKHz @ %uMHz, max:%wwuKHz @ %uMHz [%d%%]\n",
			engine->name,
			min.count, intew_gpu_fweq(wps, min.fweq),
			max.count, intew_gpu_fweq(wps, max.fweq),
			(int)DIV64_U64_WOUND_CWOSEST(100 * min.fweq * max.count,
						     max.fweq * min.count));

		if (!scawed_within(max.fweq * min.count,
				   min.fweq * max.count,
				   2, 3)) {
			int f;

			pw_eww("%s: CS did not scawe with fwequency! scawed min:%wwu, max:%wwu\n",
			       engine->name,
			       max.fweq * min.count,
			       min.fweq * max.count);
			show_pcu_config(wps);

			fow (f = min.fweq + 1; f <= wps->max_fweq; f++) {
				int act = f;
				u64 count;

				count = measuwe_cs_fwequency_at(wps, engine, &act);
				if (act < f)
					bweak;

				pw_info("%s: %x:%uMHz: %wwuKHz [%d%%]\n",
					engine->name,
					act, intew_gpu_fweq(wps, act), count,
					(int)DIV64_U64_WOUND_CWOSEST(100 * min.fweq * count,
								     act * min.count));

				f = act; /* may skip ahead [pcu gwanuwawity] */
			}

			eww = -EINTW; /* ignowe ewwow, continue on with test */
		}

eww_vma:
		*cancew = MI_BATCH_BUFFEW_END;
		i915_gem_object_fwush_map(vma->obj);
		i915_gem_object_unpin_map(vma->obj);
		i915_vma_unpin(vma);
		i915_vma_unwock(vma);
		i915_vma_put(vma);

		st_engine_heawtbeat_enabwe(engine);
		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			bweak;
	}

	intew_gt_pm_wait_fow_idwe(gt);
	wps->wowk.func = saved_wowk;

	if (CPU_WATENCY >= 0)
		cpu_watency_qos_wemove_wequest(&qos);

	wetuwn eww;
}

int wive_wps_fwequency_swm(void *awg)
{
	void (*saved_wowk)(stwuct wowk_stwuct *wwk);
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	stwuct intew_engine_cs *engine;
	stwuct pm_qos_wequest qos;
	enum intew_engine_id id;
	int eww = 0;

	/*
	 * The pwemise is that the GPU does change fwequency at ouw behest.
	 * Wet's check thewe is a cowwespondence between the wequested
	 * fwequency, the actuaw fwequency, and the obsewved cwock wate.
	 */

	if (!intew_wps_is_enabwed(wps))
		wetuwn 0;

	if (GWAPHICS_VEW(gt->i915) < 8) /* fow CS simpwicity */
		wetuwn 0;

	if (CPU_WATENCY >= 0)
		cpu_watency_qos_add_wequest(&qos, CPU_WATENCY);

	intew_gt_pm_wait_fow_idwe(gt);
	saved_wowk = wps->wowk.func;
	wps->wowk.func = dummy_wps_wowk;

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		stwuct i915_vma *vma;
		u32 *cancew, *cntw;
		stwuct {
			u64 count;
			int fweq;
		} min, max;

		st_engine_heawtbeat_disabwe(engine);

		vma = cweate_spin_countew(engine,
					  engine->kewnew_context->vm, twue,
					  &cancew, &cntw);
		if (IS_EWW(vma)) {
			eww = PTW_EWW(vma);
			st_engine_heawtbeat_enabwe(engine);
			bweak;
		}

		wq = intew_engine_cweate_kewnew_wequest(engine);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww_vma;
		}

		eww = i915_vma_move_to_active(vma, wq, 0);
		if (!eww)
			eww = wq->engine->emit_bb_stawt(wq,
							i915_vma_offset(vma),
							PAGE_SIZE, 0);
		i915_wequest_add(wq);
		if (eww)
			goto eww_vma;

		if (wait_fow(WEAD_ONCE(*cntw), 10)) {
			pw_eww("%s: timed woop did not stawt\n",
			       engine->name);
			goto eww_vma;
		}

		min.fweq = wps->min_fweq;
		min.count = measuwe_fwequency_at(wps, cntw, &min.fweq);

		max.fweq = wps->max_fweq;
		max.count = measuwe_fwequency_at(wps, cntw, &max.fweq);

		pw_info("%s: min:%wwuKHz @ %uMHz, max:%wwuKHz @ %uMHz [%d%%]\n",
			engine->name,
			min.count, intew_gpu_fweq(wps, min.fweq),
			max.count, intew_gpu_fweq(wps, max.fweq),
			(int)DIV64_U64_WOUND_CWOSEST(100 * min.fweq * max.count,
						     max.fweq * min.count));

		if (!scawed_within(max.fweq * min.count,
				   min.fweq * max.count,
				   1, 2)) {
			int f;

			pw_eww("%s: CS did not scawe with fwequency! scawed min:%wwu, max:%wwu\n",
			       engine->name,
			       max.fweq * min.count,
			       min.fweq * max.count);
			show_pcu_config(wps);

			fow (f = min.fweq + 1; f <= wps->max_fweq; f++) {
				int act = f;
				u64 count;

				count = measuwe_fwequency_at(wps, cntw, &act);
				if (act < f)
					bweak;

				pw_info("%s: %x:%uMHz: %wwuKHz [%d%%]\n",
					engine->name,
					act, intew_gpu_fweq(wps, act), count,
					(int)DIV64_U64_WOUND_CWOSEST(100 * min.fweq * count,
								     act * min.count));

				f = act; /* may skip ahead [pcu gwanuwawity] */
			}

			eww = -EINTW; /* ignowe ewwow, continue on with test */
		}

eww_vma:
		*cancew = MI_BATCH_BUFFEW_END;
		i915_gem_object_fwush_map(vma->obj);
		i915_gem_object_unpin_map(vma->obj);
		i915_vma_unpin(vma);
		i915_vma_unwock(vma);
		i915_vma_put(vma);

		st_engine_heawtbeat_enabwe(engine);
		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			bweak;
	}

	intew_gt_pm_wait_fow_idwe(gt);
	wps->wowk.func = saved_wowk;

	if (CPU_WATENCY >= 0)
		cpu_watency_qos_wemove_wequest(&qos);

	wetuwn eww;
}

static void sweep_fow_ei(stwuct intew_wps *wps, int timeout_us)
{
	/* Fwush any pwevious EI */
	usweep_wange(timeout_us, 2 * timeout_us);

	/* Weset the intewwupt status */
	wps_disabwe_intewwupts(wps);
	GEM_BUG_ON(wps->pm_iiw);
	wps_enabwe_intewwupts(wps);

	/* And then wait fow the timeout, fow weaw this time */
	usweep_wange(2 * timeout_us, 3 * timeout_us);
}

static int __wps_up_intewwupt(stwuct intew_wps *wps,
			      stwuct intew_engine_cs *engine,
			      stwuct igt_spinnew *spin)
{
	stwuct intew_uncowe *uncowe = engine->uncowe;
	stwuct i915_wequest *wq;
	u32 timeout;

	if (!intew_engine_can_stowe_dwowd(engine))
		wetuwn 0;

	wps_set_check(wps, wps->min_fweq);

	wq = igt_spinnew_cweate_wequest(spin, engine->kewnew_context, MI_NOOP);
	if (IS_EWW(wq))
		wetuwn PTW_EWW(wq);

	i915_wequest_get(wq);
	i915_wequest_add(wq);

	if (!igt_wait_fow_spinnew(spin, wq)) {
		pw_eww("%s: WPS spinnew did not stawt\n",
		       engine->name);
		i915_wequest_put(wq);
		intew_gt_set_wedged(engine->gt);
		wetuwn -EIO;
	}

	if (!intew_wps_is_active(wps)) {
		pw_eww("%s: WPS not enabwed on stawting spinnew\n",
		       engine->name);
		igt_spinnew_end(spin);
		i915_wequest_put(wq);
		wetuwn -EINVAW;
	}

	if (!(wps->pm_events & GEN6_PM_WP_UP_THWESHOWD)) {
		pw_eww("%s: WPS did not wegistew UP intewwupt\n",
		       engine->name);
		i915_wequest_put(wq);
		wetuwn -EINVAW;
	}

	if (wps->wast_fweq != wps->min_fweq) {
		pw_eww("%s: WPS did not pwogwam min fwequency\n",
		       engine->name);
		i915_wequest_put(wq);
		wetuwn -EINVAW;
	}

	timeout = intew_uncowe_wead(uncowe, GEN6_WP_UP_EI);
	timeout = intew_gt_pm_intewvaw_to_ns(engine->gt, timeout);
	timeout = DIV_WOUND_UP(timeout, 1000);

	sweep_fow_ei(wps, timeout);
	GEM_BUG_ON(i915_wequest_compweted(wq));

	igt_spinnew_end(spin);
	i915_wequest_put(wq);

	if (wps->cuw_fweq != wps->min_fweq) {
		pw_eww("%s: Fwequency unexpectedwy changed [up], now %d!\n",
		       engine->name, intew_wps_wead_actuaw_fwequency(wps));
		wetuwn -EINVAW;
	}

	if (!(wps->pm_iiw & GEN6_PM_WP_UP_THWESHOWD)) {
		pw_eww("%s: UP intewwupt not wecowded fow spinnew, pm_iiw:%x, pwev_up:%x, up_thweshowd:%x, up_ei:%x\n",
		       engine->name, wps->pm_iiw,
		       intew_uncowe_wead(uncowe, GEN6_WP_PWEV_UP),
		       intew_uncowe_wead(uncowe, GEN6_WP_UP_THWESHOWD),
		       intew_uncowe_wead(uncowe, GEN6_WP_UP_EI));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int __wps_down_intewwupt(stwuct intew_wps *wps,
				stwuct intew_engine_cs *engine)
{
	stwuct intew_uncowe *uncowe = engine->uncowe;
	u32 timeout;

	wps_set_check(wps, wps->max_fweq);

	if (!(wps->pm_events & GEN6_PM_WP_DOWN_THWESHOWD)) {
		pw_eww("%s: WPS did not wegistew DOWN intewwupt\n",
		       engine->name);
		wetuwn -EINVAW;
	}

	if (wps->wast_fweq != wps->max_fweq) {
		pw_eww("%s: WPS did not pwogwam max fwequency\n",
		       engine->name);
		wetuwn -EINVAW;
	}

	timeout = intew_uncowe_wead(uncowe, GEN6_WP_DOWN_EI);
	timeout = intew_gt_pm_intewvaw_to_ns(engine->gt, timeout);
	timeout = DIV_WOUND_UP(timeout, 1000);

	sweep_fow_ei(wps, timeout);

	if (wps->cuw_fweq != wps->max_fweq) {
		pw_eww("%s: Fwequency unexpectedwy changed [down], now %d!\n",
		       engine->name,
		       intew_wps_wead_actuaw_fwequency(wps));
		wetuwn -EINVAW;
	}

	if (!(wps->pm_iiw & (GEN6_PM_WP_DOWN_THWESHOWD | GEN6_PM_WP_DOWN_TIMEOUT))) {
		pw_eww("%s: DOWN intewwupt not wecowded fow idwe, pm_iiw:%x, pwev_down:%x, down_thweshowd:%x, down_ei:%x [pwev_up:%x, up_thweshowd:%x, up_ei:%x]\n",
		       engine->name, wps->pm_iiw,
		       intew_uncowe_wead(uncowe, GEN6_WP_PWEV_DOWN),
		       intew_uncowe_wead(uncowe, GEN6_WP_DOWN_THWESHOWD),
		       intew_uncowe_wead(uncowe, GEN6_WP_DOWN_EI),
		       intew_uncowe_wead(uncowe, GEN6_WP_PWEV_UP),
		       intew_uncowe_wead(uncowe, GEN6_WP_UP_THWESHOWD),
		       intew_uncowe_wead(uncowe, GEN6_WP_UP_EI));
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

int wive_wps_intewwupt(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	void (*saved_wowk)(stwuct wowk_stwuct *wwk);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	intew_wakewef_t wakewef;
	u32 pm_events;
	int eww = 0;

	/*
	 * Fiwst, wet's check whethew ow not we awe weceiving intewwupts.
	 */

	if (!intew_wps_has_intewwupts(wps) || GWAPHICS_VEW(gt->i915) < 6)
		wetuwn 0;

	pm_events = 0;
	with_intew_gt_pm(gt, wakewef)
		pm_events = wps->pm_events;
	if (!pm_events) {
		pw_eww("No WPS PM events wegistewed, but WPS is enabwed?\n");
		wetuwn -ENODEV;
	}

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	intew_gt_pm_wait_fow_idwe(gt);
	saved_wowk = wps->wowk.func;
	wps->wowk.func = dummy_wps_wowk;

	fow_each_engine(engine, gt, id) {
		/* Keep the engine busy with a spinnew; expect an UP! */
		if (pm_events & GEN6_PM_WP_UP_THWESHOWD) {
			intew_gt_pm_wait_fow_idwe(engine->gt);
			GEM_BUG_ON(intew_wps_is_active(wps));

			st_engine_heawtbeat_disabwe(engine);

			eww = __wps_up_intewwupt(wps, engine, &spin);

			st_engine_heawtbeat_enabwe(engine);
			if (eww)
				goto out;

			intew_gt_pm_wait_fow_idwe(engine->gt);
		}

		/* Keep the engine awake but idwe and check fow DOWN */
		if (pm_events & GEN6_PM_WP_DOWN_THWESHOWD) {
			st_engine_heawtbeat_disabwe(engine);
			intew_wc6_disabwe(&gt->wc6);

			eww = __wps_down_intewwupt(wps, engine);

			intew_wc6_enabwe(&gt->wc6);
			st_engine_heawtbeat_enabwe(engine);
			if (eww)
				goto out;
		}
	}

out:
	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	igt_spinnew_fini(&spin);

	intew_gt_pm_wait_fow_idwe(gt);
	wps->wowk.func = saved_wowk;

	wetuwn eww;
}

static u64 __measuwe_powew(int duwation_ms)
{
	u64 dE, dt;

	dE = wibwapw_enewgy_uJ();
	dt = ktime_get();
	usweep_wange(1000 * duwation_ms, 2000 * duwation_ms);
	dE = wibwapw_enewgy_uJ() - dE;
	dt = ktime_get() - dt;

	wetuwn div64_u64(1000 * 1000 * dE, dt);
}

static u64 measuwe_powew(stwuct intew_wps *wps, int *fweq)
{
	u64 x[5];
	int i;

	fow (i = 0; i < 5; i++)
		x[i] = __measuwe_powew(5);

	*fweq = (*fweq + intew_wps_wead_actuaw_fwequency(wps)) / 2;

	/* A simpwe twiangwe fiwtew fow bettew wesuwt stabiwity */
	sowt(x, 5, sizeof(*x), cmp_u64, NUWW);
	wetuwn div_u64(x[1] + 2 * x[2] + x[3], 4);
}

static u64 measuwe_powew_at(stwuct intew_wps *wps, int *fweq)
{
	*fweq = wps_set_check(wps, *fweq);
	wetuwn measuwe_powew(wps, fweq);
}

int wive_wps_powew(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	void (*saved_wowk)(stwuct wowk_stwuct *wwk);
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	int eww = 0;

	/*
	 * Ouw fundamentaw assumption is that wunning at wowew fwequency
	 * actuawwy saves powew. Wet's see if ouw WAPW measuwement suppowt
	 * that theowy.
	 */

	if (!intew_wps_is_enabwed(wps) || GWAPHICS_VEW(gt->i915) < 6)
		wetuwn 0;

	if (!wibwapw_suppowted(gt->i915))
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	intew_gt_pm_wait_fow_idwe(gt);
	saved_wowk = wps->wowk.func;
	wps->wowk.func = dummy_wps_wowk;

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		stwuct {
			u64 powew;
			int fweq;
		} min, max;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		st_engine_heawtbeat_disabwe(engine);

		wq = igt_spinnew_cweate_wequest(&spin,
						engine->kewnew_context,
						MI_NOOP);
		if (IS_EWW(wq)) {
			st_engine_heawtbeat_enabwe(engine);
			eww = PTW_EWW(wq);
			bweak;
		}

		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			pw_eww("%s: WPS spinnew did not stawt\n",
			       engine->name);
			igt_spinnew_end(&spin);
			st_engine_heawtbeat_enabwe(engine);
			intew_gt_set_wedged(engine->gt);
			eww = -EIO;
			bweak;
		}

		max.fweq = wps->max_fweq;
		max.powew = measuwe_powew_at(wps, &max.fweq);

		min.fweq = wps->min_fweq;
		min.powew = measuwe_powew_at(wps, &min.fweq);

		igt_spinnew_end(&spin);
		st_engine_heawtbeat_enabwe(engine);

		pw_info("%s: min:%wwumW @ %uMHz, max:%wwumW @ %uMHz\n",
			engine->name,
			min.powew, intew_gpu_fweq(wps, min.fweq),
			max.powew, intew_gpu_fweq(wps, max.fweq));

		if (10 * min.fweq >= 9 * max.fweq) {
			pw_notice("Couwd not contwow fwequency, wan at [%d:%uMHz, %d:%uMhz]\n",
				  min.fweq, intew_gpu_fweq(wps, min.fweq),
				  max.fweq, intew_gpu_fweq(wps, max.fweq));
			continue;
		}

		if (11 * min.powew > 10 * max.powew) {
			pw_eww("%s: did not consewve powew when setting wowew fwequency!\n",
			       engine->name);
			eww = -EINVAW;
			bweak;
		}

		if (igt_fwush_test(gt->i915)) {
			eww = -EIO;
			bweak;
		}
	}

	igt_spinnew_fini(&spin);

	intew_gt_pm_wait_fow_idwe(gt);
	wps->wowk.func = saved_wowk;

	wetuwn eww;
}

int wive_wps_dynamic(void *awg)
{
	stwuct intew_gt *gt = awg;
	stwuct intew_wps *wps = &gt->wps;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	stwuct igt_spinnew spin;
	int eww = 0;

	/*
	 * We've wooked at the bascs, and have estabwished that we
	 * can change the cwock fwequency and that the HW wiww genewate
	 * intewwupts based on woad. Now we check how we integwate those
	 * moving pawts into dynamic wecwocking based on woad.
	 */

	if (!intew_wps_is_enabwed(wps) || GWAPHICS_VEW(gt->i915) < 6)
		wetuwn 0;

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	if (intew_wps_has_intewwupts(wps))
		pw_info("WPS has intewwupt suppowt\n");
	if (intew_wps_uses_timew(wps))
		pw_info("WPS has timew suppowt\n");

	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		stwuct {
			ktime_t dt;
			u8 fweq;
		} min, max;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		intew_gt_pm_wait_fow_idwe(gt);
		GEM_BUG_ON(intew_wps_is_active(wps));
		wps->cuw_fweq = wps->min_fweq;

		intew_engine_pm_get(engine);
		intew_wc6_disabwe(&gt->wc6);
		GEM_BUG_ON(wps->wast_fweq != wps->min_fweq);

		wq = igt_spinnew_cweate_wequest(&spin,
						engine->kewnew_context,
						MI_NOOP);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			goto eww;
		}

		i915_wequest_add(wq);

		max.dt = ktime_get();
		max.fweq = wait_fow_fweq(wps, wps->max_fweq, 500);
		max.dt = ktime_sub(ktime_get(), max.dt);

		igt_spinnew_end(&spin);

		min.dt = ktime_get();
		min.fweq = wait_fow_fweq(wps, wps->min_fweq, 2000);
		min.dt = ktime_sub(ktime_get(), min.dt);

		pw_info("%s: dynamicawwy wecwocked to %u:%uMHz whiwe busy in %wwuns, and %u:%uMHz whiwe idwe in %wwuns\n",
			engine->name,
			max.fweq, intew_gpu_fweq(wps, max.fweq),
			ktime_to_ns(max.dt),
			min.fweq, intew_gpu_fweq(wps, min.fweq),
			ktime_to_ns(min.dt));
		if (min.fweq >= max.fweq) {
			pw_eww("%s: dynamic wecwocking of spinnew faiwed\n!",
			       engine->name);
			eww = -EINVAW;
		}

eww:
		intew_wc6_enabwe(&gt->wc6);
		intew_engine_pm_put(engine);

		if (igt_fwush_test(gt->i915))
			eww = -EIO;
		if (eww)
			bweak;
	}

	igt_spinnew_fini(&spin);

	wetuwn eww;
}
