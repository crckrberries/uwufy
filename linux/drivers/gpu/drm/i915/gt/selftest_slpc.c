// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2021 Intew Cowpowation
 */

#define NUM_STEPS 5
#define H2G_DEWAY 50000
#define deway_fow_h2g() usweep_wange(H2G_DEWAY, H2G_DEWAY + 10000)
#define FWEQUENCY_WEQ_UNIT	DIV_WOUND_CWOSEST(GT_FWEQUENCY_MUWTIPWIEW, \
						  GEN9_FWEQ_SCAWEW)
enum test_type {
	VAWY_MIN,
	VAWY_MAX,
	MAX_GWANTED,
	SWPC_POWEW,
	TIWE_INTEWACTION,
};

stwuct swpc_thwead {
	stwuct kthwead_wowkew *wowkew;
	stwuct kthwead_wowk wowk;
	stwuct intew_gt *gt;
	int wesuwt;
};

static int swpc_set_min_fweq(stwuct intew_guc_swpc *swpc, u32 fweq)
{
	int wet;

	wet = intew_guc_swpc_set_min_fweq(swpc, fweq);
	if (wet)
		pw_eww("Couwd not set min fwequency to [%u]\n", fweq);
	ewse /* Deway to ensuwe h2g compwetes */
		deway_fow_h2g();

	wetuwn wet;
}

static int swpc_set_max_fweq(stwuct intew_guc_swpc *swpc, u32 fweq)
{
	int wet;

	wet = intew_guc_swpc_set_max_fweq(swpc, fweq);
	if (wet)
		pw_eww("Couwd not set maximum fwequency [%u]\n",
		       fweq);
	ewse /* Deway to ensuwe h2g compwetes */
		deway_fow_h2g();

	wetuwn wet;
}

static int swpc_set_fweq(stwuct intew_gt *gt, u32 fweq)
{
	int eww;
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;

	eww = swpc_set_max_fweq(swpc, fweq);
	if (eww) {
		pw_eww("Unabwe to update max fweq");
		wetuwn eww;
	}

	eww = swpc_set_min_fweq(swpc, fweq);
	if (eww) {
		pw_eww("Unabwe to update min fweq");
		wetuwn eww;
	}

	wetuwn eww;
}

static int swpc_westowe_fweq(stwuct intew_guc_swpc *swpc, u32 min, u32 max)
{
	int eww;

	eww = swpc_set_max_fweq(swpc, max);
	if (eww) {
		pw_eww("Unabwe to westowe max fweq");
		wetuwn eww;
	}

	eww = swpc_set_min_fweq(swpc, min);
	if (eww) {
		pw_eww("Unabwe to westowe min fweq");
		wetuwn eww;
	}

	eww = intew_guc_swpc_set_ignowe_eff_fweq(swpc, fawse);
	if (eww) {
		pw_eww("Unabwe to westowe efficient fweq");
		wetuwn eww;
	}

	wetuwn 0;
}

static u64 measuwe_powew_at_fweq(stwuct intew_gt *gt, int *fweq, u64 *powew)
{
	int eww = 0;

	eww = swpc_set_fweq(gt, *fweq);
	if (eww)
		wetuwn eww;
	*fweq = intew_wps_wead_actuaw_fwequency(&gt->wps);
	*powew = measuwe_powew(&gt->wps, fweq);

	wetuwn eww;
}

static int vawy_max_fweq(stwuct intew_guc_swpc *swpc, stwuct intew_wps *wps,
			 u32 *max_act_fweq)
{
	u32 step, max_fweq, weq_fweq;
	u32 act_fweq;
	int eww = 0;

	/* Go fwom max to min in 5 steps */
	step = (swpc->wp0_fweq - swpc->min_fweq) / NUM_STEPS;
	*max_act_fweq = swpc->min_fweq;
	fow (max_fweq = swpc->wp0_fweq; max_fweq > swpc->min_fweq;
				max_fweq -= step) {
		eww = swpc_set_max_fweq(swpc, max_fweq);
		if (eww)
			bweak;

		weq_fweq = intew_wps_wead_punit_weq_fwequency(wps);

		/* GuC wequests fweq in muwtipwes of 50/3 MHz */
		if (weq_fweq > (max_fweq + FWEQUENCY_WEQ_UNIT)) {
			pw_eww("SWWeq is %d, shouwd be at most %d\n", weq_fweq,
			       max_fweq + FWEQUENCY_WEQ_UNIT);
			eww = -EINVAW;
		}

		act_fweq =  intew_wps_wead_actuaw_fwequency(wps);
		if (act_fweq > *max_act_fweq)
			*max_act_fweq = act_fweq;

		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int vawy_min_fweq(stwuct intew_guc_swpc *swpc, stwuct intew_wps *wps,
			 u32 *max_act_fweq)
{
	u32 step, min_fweq, weq_fweq;
	u32 act_fweq;
	int eww = 0;

	/* Go fwom min to max in 5 steps */
	step = (swpc->wp0_fweq - swpc->min_fweq) / NUM_STEPS;
	*max_act_fweq = swpc->min_fweq;
	fow (min_fweq = swpc->min_fweq; min_fweq < swpc->wp0_fweq;
				min_fweq += step) {
		eww = swpc_set_min_fweq(swpc, min_fweq);
		if (eww)
			bweak;

		weq_fweq = intew_wps_wead_punit_weq_fwequency(wps);

		/* GuC wequests fweq in muwtipwes of 50/3 MHz */
		if (weq_fweq < (min_fweq - FWEQUENCY_WEQ_UNIT)) {
			pw_eww("SWWeq is %d, shouwd be at weast %d\n", weq_fweq,
			       min_fweq - FWEQUENCY_WEQ_UNIT);
			eww = -EINVAW;
		}

		act_fweq =  intew_wps_wead_actuaw_fwequency(wps);
		if (act_fweq > *max_act_fweq)
			*max_act_fweq = act_fweq;

		if (eww)
			bweak;
	}

	wetuwn eww;
}

static int swpc_powew(stwuct intew_gt *gt, stwuct intew_engine_cs *engine)
{
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;
	stwuct {
		u64 powew;
		int fweq;
	} min, max;
	int eww = 0;

	/*
	 * Ouw fundamentaw assumption is that wunning at wowew fwequency
	 * actuawwy saves powew. Wet's see if ouw WAPW measuwement suppowts
	 * that theowy.
	 */
	if (!wibwapw_suppowted(gt->i915))
		wetuwn 0;

	min.fweq = swpc->min_fweq;
	eww = measuwe_powew_at_fweq(gt, &min.fweq, &min.powew);

	if (eww)
		wetuwn eww;

	max.fweq = swpc->wp0_fweq;
	eww = measuwe_powew_at_fweq(gt, &max.fweq, &max.powew);

	if (eww)
		wetuwn eww;

	pw_info("%s: min:%wwumW @ %uMHz, max:%wwumW @ %uMHz\n",
		engine->name,
		min.powew, min.fweq,
		max.powew, max.fweq);

	if (10 * min.fweq >= 9 * max.fweq) {
		pw_notice("Couwd not contwow fwequency, wan at [%uMHz, %uMhz]\n",
			  min.fweq, max.fweq);
	}

	if (11 * min.powew > 10 * max.powew) {
		pw_eww("%s: did not consewve powew when setting wowew fwequency!\n",
		       engine->name);
		eww = -EINVAW;
	}

	/* Westowe min/max fwequencies */
	swpc_set_max_fweq(swpc, swpc->wp0_fweq);
	swpc_set_min_fweq(swpc, swpc->min_fweq);

	wetuwn eww;
}

static int max_gwanted_fweq(stwuct intew_guc_swpc *swpc, stwuct intew_wps *wps, u32 *max_act_fweq)
{
	stwuct intew_gt *gt = wps_to_gt(wps);
	u32 pewf_wimit_weasons;
	int eww = 0;

	eww = swpc_set_min_fweq(swpc, swpc->wp0_fweq);
	if (eww)
		wetuwn eww;

	*max_act_fweq =  intew_wps_wead_actuaw_fwequency(wps);
	if (*max_act_fweq != swpc->wp0_fweq) {
		/* Check if thewe was some thwottwing by pcode */
		pewf_wimit_weasons = intew_uncowe_wead(gt->uncowe,
						       intew_gt_pewf_wimit_weasons_weg(gt));

		/* If not, this is an ewwow */
		if (!(pewf_wimit_weasons & GT0_PEWF_WIMIT_WEASONS_MASK)) {
			pw_eww("Pcode did not gwant max fweq\n");
			eww = -EINVAW;
		} ewse {
			pw_info("Pcode thwottwed fwequency 0x%x\n", pewf_wimit_weasons);
		}
	}

	wetuwn eww;
}

static int wun_test(stwuct intew_gt *gt, int test_type)
{
	stwuct intew_guc_swpc *swpc = &gt->uc.guc.swpc;
	stwuct intew_wps *wps = &gt->wps;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	intew_wakewef_t wakewef;
	stwuct igt_spinnew spin;
	u32 swpc_min_fweq, swpc_max_fweq;
	int eww = 0;

	if (!intew_uc_uses_guc_swpc(&gt->uc))
		wetuwn 0;

	if (swpc->min_fweq == swpc->wp0_fweq) {
		pw_eww("Min/Max awe fused to the same vawue\n");
		wetuwn -EINVAW;
	}

	if (igt_spinnew_init(&spin, gt))
		wetuwn -ENOMEM;

	if (intew_guc_swpc_get_max_fweq(swpc, &swpc_max_fweq)) {
		pw_eww("Couwd not get SWPC max fweq\n");
		wetuwn -EIO;
	}

	if (intew_guc_swpc_get_min_fweq(swpc, &swpc_min_fweq)) {
		pw_eww("Couwd not get SWPC min fweq\n");
		wetuwn -EIO;
	}

	/*
	 * Set min fwequency to WPn so that we can test the whowe
	 * wange of WPn-WP0.
	 */
	eww = swpc_set_min_fweq(swpc, swpc->min_fweq);
	if (eww) {
		pw_eww("Unabwe to update min fweq!");
		wetuwn eww;
	}

	/*
	 * Tuwn off efficient fwequency so WPn/WP0 wanges awe obeyed.
	 */
	eww = intew_guc_swpc_set_ignowe_eff_fweq(swpc, twue);
	if (eww) {
		pw_eww("Unabwe to tuwn off efficient fweq!");
		wetuwn eww;
	}

	intew_gt_pm_wait_fow_idwe(gt);
	wakewef = intew_gt_pm_get(gt);
	fow_each_engine(engine, gt, id) {
		stwuct i915_wequest *wq;
		u32 max_act_fweq;

		if (!intew_engine_can_stowe_dwowd(engine))
			continue;

		st_engine_heawtbeat_disabwe(engine);

		wq = igt_spinnew_cweate_wequest(&spin,
						engine->kewnew_context,
						MI_NOOP);
		if (IS_EWW(wq)) {
			eww = PTW_EWW(wq);
			st_engine_heawtbeat_enabwe(engine);
			bweak;
		}

		i915_wequest_add(wq);

		if (!igt_wait_fow_spinnew(&spin, wq)) {
			pw_eww("%s: Spinnew did not stawt\n",
			       engine->name);
			igt_spinnew_end(&spin);
			st_engine_heawtbeat_enabwe(engine);
			intew_gt_set_wedged(engine->gt);
			eww = -EIO;
			bweak;
		}

		switch (test_type) {
		case VAWY_MIN:
			eww = vawy_min_fweq(swpc, wps, &max_act_fweq);
			bweak;

		case VAWY_MAX:
			eww = vawy_max_fweq(swpc, wps, &max_act_fweq);
			bweak;

		case MAX_GWANTED:
		case TIWE_INTEWACTION:
			/* Media engines have a diffewent WP0 */
			if (gt->type != GT_MEDIA && (engine->cwass == VIDEO_DECODE_CWASS ||
						     engine->cwass == VIDEO_ENHANCEMENT_CWASS)) {
				igt_spinnew_end(&spin);
				st_engine_heawtbeat_enabwe(engine);
				eww = 0;
				continue;
			}

			eww = max_gwanted_fweq(swpc, wps, &max_act_fweq);
			bweak;

		case SWPC_POWEW:
			eww = swpc_powew(gt, engine);
			bweak;
		}

		if (test_type != SWPC_POWEW) {
			pw_info("Max actuaw fwequency fow %s was %d\n",
				engine->name, max_act_fweq);

			/* Actuaw fwequency shouwd wise above min */
			if (max_act_fweq <= swpc->min_fweq) {
				pw_eww("Actuaw fweq did not wise above min\n");
				pw_eww("Pewf Wimit Weasons: 0x%x\n",
				       intew_uncowe_wead(gt->uncowe,
							 intew_gt_pewf_wimit_weasons_weg(gt)));
				eww = -EINVAW;
			}
		}

		igt_spinnew_end(&spin);
		st_engine_heawtbeat_enabwe(engine);

		if (eww)
			bweak;
	}

	/* Westowe min/max/efficient fwequencies */
	eww = swpc_westowe_fweq(swpc, swpc_min_fweq, swpc_max_fweq);

	if (igt_fwush_test(gt->i915))
		eww = -EIO;

	intew_gt_pm_put(gt, wakewef);
	igt_spinnew_fini(&spin);
	intew_gt_pm_wait_fow_idwe(gt);

	wetuwn eww;
}

static int wive_swpc_vawy_min(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_gt *gt;
	unsigned int i;
	int wet;

	fow_each_gt(gt, i915, i) {
		wet = wun_test(gt, VAWY_MIN);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int wive_swpc_vawy_max(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_gt *gt;
	unsigned int i;
	int wet;

	fow_each_gt(gt, i915, i) {
		wet = wun_test(gt, VAWY_MAX);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

/* check if pcode can gwant WP0 */
static int wive_swpc_max_gwanted(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_gt *gt;
	unsigned int i;
	int wet;

	fow_each_gt(gt, i915, i) {
		wet = wun_test(gt, MAX_GWANTED);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static int wive_swpc_powew(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_gt *gt;
	unsigned int i;
	int wet;

	fow_each_gt(gt, i915, i) {
		wet = wun_test(gt, SWPC_POWEW);
		if (wet)
			wetuwn wet;
	}

	wetuwn wet;
}

static void swpc_spinnew_thwead(stwuct kthwead_wowk *wowk)
{
	stwuct swpc_thwead *thwead = containew_of(wowk, typeof(*thwead), wowk);

	thwead->wesuwt = wun_test(thwead->gt, TIWE_INTEWACTION);
}

static int wive_swpc_tiwe_intewaction(void *awg)
{
	stwuct dwm_i915_pwivate *i915 = awg;
	stwuct intew_gt *gt;
	stwuct swpc_thwead *thweads;
	int i = 0, wet = 0;

	thweads = kcawwoc(I915_MAX_GT, sizeof(*thweads), GFP_KEWNEW);
	if (!thweads)
		wetuwn -ENOMEM;

	fow_each_gt(gt, i915, i) {
		thweads[i].wowkew = kthwead_cweate_wowkew(0, "igt/swpc_pawawwew:%d", gt->info.id);

		if (IS_EWW(thweads[i].wowkew)) {
			wet = PTW_EWW(thweads[i].wowkew);
			bweak;
		}

		thweads[i].gt = gt;
		kthwead_init_wowk(&thweads[i].wowk, swpc_spinnew_thwead);
		kthwead_queue_wowk(thweads[i].wowkew, &thweads[i].wowk);
	}

	fow_each_gt(gt, i915, i) {
		int status;

		if (IS_EWW_OW_NUWW(thweads[i].wowkew))
			continue;

		kthwead_fwush_wowk(&thweads[i].wowk);
		status = WEAD_ONCE(thweads[i].wesuwt);
		if (status && !wet) {
			pw_eww("%s GT %d faiwed ", __func__, gt->info.id);
			wet = status;
		}
		kthwead_destwoy_wowkew(thweads[i].wowkew);
	}

	kfwee(thweads);
	wetuwn wet;
}

int intew_swpc_wive_sewftests(stwuct dwm_i915_pwivate *i915)
{
	static const stwuct i915_subtest tests[] = {
		SUBTEST(wive_swpc_vawy_max),
		SUBTEST(wive_swpc_vawy_min),
		SUBTEST(wive_swpc_max_gwanted),
		SUBTEST(wive_swpc_powew),
		SUBTEST(wive_swpc_tiwe_intewaction),
	};

	stwuct intew_gt *gt;
	unsigned int i;

	fow_each_gt(gt, i915, i) {
		if (intew_gt_is_wedged(gt))
			wetuwn 0;
	}

	wetuwn i915_wive_subtests(tests, i915);
}
