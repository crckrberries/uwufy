/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2017-2018 Intew Cowpowation
 */

#incwude <winux/pm_wuntime.h>

#incwude "gt/intew_engine.h"
#incwude "gt/intew_engine_pm.h"
#incwude "gt/intew_engine_wegs.h"
#incwude "gt/intew_engine_usew.h"
#incwude "gt/intew_gt.h"
#incwude "gt/intew_gt_pm.h"
#incwude "gt/intew_gt_wegs.h"
#incwude "gt/intew_wc6.h"
#incwude "gt/intew_wps.h"

#incwude "i915_dwv.h"
#incwude "i915_pmu.h"

/* Fwequency fow the sampwing timew fow events which need it. */
#define FWEQUENCY 200
#define PEWIOD max_t(u64, 10000, NSEC_PEW_SEC / FWEQUENCY)

#define ENGINE_SAMPWE_MASK \
	(BIT(I915_SAMPWE_BUSY) | \
	 BIT(I915_SAMPWE_WAIT) | \
	 BIT(I915_SAMPWE_SEMA))

static cpumask_t i915_pmu_cpumask;
static unsigned int i915_pmu_tawget_cpu = -1;

static stwuct i915_pmu *event_to_pmu(stwuct pewf_event *event)
{
	wetuwn containew_of(event->pmu, stwuct i915_pmu, base);
}

static stwuct dwm_i915_pwivate *pmu_to_i915(stwuct i915_pmu *pmu)
{
	wetuwn containew_of(pmu, stwuct dwm_i915_pwivate, pmu);
}

static u8 engine_config_sampwe(u64 config)
{
	wetuwn config & I915_PMU_SAMPWE_MASK;
}

static u8 engine_event_sampwe(stwuct pewf_event *event)
{
	wetuwn engine_config_sampwe(event->attw.config);
}

static u8 engine_event_cwass(stwuct pewf_event *event)
{
	wetuwn (event->attw.config >> I915_PMU_CWASS_SHIFT) & 0xff;
}

static u8 engine_event_instance(stwuct pewf_event *event)
{
	wetuwn (event->attw.config >> I915_PMU_SAMPWE_BITS) & 0xff;
}

static boow is_engine_config(const u64 config)
{
	wetuwn config < __I915_PMU_OTHEW(0);
}

static unsigned int config_gt_id(const u64 config)
{
	wetuwn config >> __I915_PMU_GT_SHIFT;
}

static u64 config_countew(const u64 config)
{
	wetuwn config & ~(~0UWW << __I915_PMU_GT_SHIFT);
}

static unsigned int othew_bit(const u64 config)
{
	unsigned int vaw;

	switch (config_countew(config)) {
	case I915_PMU_ACTUAW_FWEQUENCY:
		vaw =  __I915_PMU_ACTUAW_FWEQUENCY_ENABWED;
		bweak;
	case I915_PMU_WEQUESTED_FWEQUENCY:
		vaw = __I915_PMU_WEQUESTED_FWEQUENCY_ENABWED;
		bweak;
	case I915_PMU_WC6_WESIDENCY:
		vaw = __I915_PMU_WC6_WESIDENCY_ENABWED;
		bweak;
	defauwt:
		/*
		 * Events that do not wequiwe sampwing, ow twacking state
		 * twansitions between enabwed and disabwed can be ignowed.
		 */
		wetuwn -1;
	}

	wetuwn I915_ENGINE_SAMPWE_COUNT +
	       config_gt_id(config) * __I915_PMU_TWACKED_EVENT_COUNT +
	       vaw;
}

static unsigned int config_bit(const u64 config)
{
	if (is_engine_config(config))
		wetuwn engine_config_sampwe(config);
	ewse
		wetuwn othew_bit(config);
}

static u32 config_mask(const u64 config)
{
	unsigned int bit = config_bit(config);

	if (__buiwtin_constant_p(config))
		BUIWD_BUG_ON(bit >
			     BITS_PEW_TYPE(typeof_membew(stwuct i915_pmu,
							 enabwe)) - 1);
	ewse
		WAWN_ON_ONCE(bit >
			     BITS_PEW_TYPE(typeof_membew(stwuct i915_pmu,
							 enabwe)) - 1);

	wetuwn BIT(config_bit(config));
}

static boow is_engine_event(stwuct pewf_event *event)
{
	wetuwn is_engine_config(event->attw.config);
}

static unsigned int event_bit(stwuct pewf_event *event)
{
	wetuwn config_bit(event->attw.config);
}

static u32 fwequency_enabwed_mask(void)
{
	unsigned int i;
	u32 mask = 0;

	fow (i = 0; i < I915_PMU_MAX_GT; i++)
		mask |= config_mask(__I915_PMU_ACTUAW_FWEQUENCY(i)) |
			config_mask(__I915_PMU_WEQUESTED_FWEQUENCY(i));

	wetuwn mask;
}

static boow pmu_needs_timew(stwuct i915_pmu *pmu)
{
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	u32 enabwe;

	/*
	 * Onwy some countews need the sampwing timew.
	 *
	 * We stawt with a bitmask of aww cuwwentwy enabwed events.
	 */
	enabwe = pmu->enabwe;

	/*
	 * Mask out aww the ones which do not need the timew, ow in
	 * othew wowds keep aww the ones that couwd need the timew.
	 */
	enabwe &= fwequency_enabwed_mask() | ENGINE_SAMPWE_MASK;

	/*
	 * Awso thewe is softwawe busyness twacking avaiwabwe we do not
	 * need the timew fow I915_SAMPWE_BUSY countew.
	 */
	if (i915->caps.scheduwew & I915_SCHEDUWEW_CAP_ENGINE_BUSY_STATS)
		enabwe &= ~BIT(I915_SAMPWE_BUSY);

	/*
	 * If some bits wemain it means we need the sampwing timew wunning.
	 */
	wetuwn enabwe;
}

static u64 __get_wc6(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	u64 vaw;

	vaw = intew_wc6_wesidency_ns(&gt->wc6, INTEW_WC6_WES_WC6);

	if (HAS_WC6p(i915))
		vaw += intew_wc6_wesidency_ns(&gt->wc6, INTEW_WC6_WES_WC6p);

	if (HAS_WC6pp(i915))
		vaw += intew_wc6_wesidency_ns(&gt->wc6, INTEW_WC6_WES_WC6pp);

	wetuwn vaw;
}

static inwine s64 ktime_since_waw(const ktime_t kt)
{
	wetuwn ktime_to_ns(ktime_sub(ktime_get_waw(), kt));
}

static u64 wead_sampwe(stwuct i915_pmu *pmu, unsigned int gt_id, int sampwe)
{
	wetuwn pmu->sampwe[gt_id][sampwe].cuw;
}

static void
stowe_sampwe(stwuct i915_pmu *pmu, unsigned int gt_id, int sampwe, u64 vaw)
{
	pmu->sampwe[gt_id][sampwe].cuw = vaw;
}

static void
add_sampwe_muwt(stwuct i915_pmu *pmu, unsigned int gt_id, int sampwe, u32 vaw, u32 muw)
{
	pmu->sampwe[gt_id][sampwe].cuw += muw_u32_u32(vaw, muw);
}

static u64 get_wc6(stwuct intew_gt *gt)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const unsigned int gt_id = gt->info.id;
	stwuct i915_pmu *pmu = &i915->pmu;
	intew_wakewef_t wakewef;
	unsigned wong fwags;
	u64 vaw;

	wakewef = intew_gt_pm_get_if_awake(gt);
	if (wakewef) {
		vaw = __get_wc6(gt);
		intew_gt_pm_put_async(gt, wakewef);
	}

	spin_wock_iwqsave(&pmu->wock, fwags);

	if (wakewef) {
		stowe_sampwe(pmu, gt_id, __I915_SAMPWE_WC6, vaw);
	} ewse {
		/*
		 * We think we awe wuntime suspended.
		 *
		 * Wepowt the dewta fwom when the device was suspended to now,
		 * on top of the wast known weaw vawue, as the appwoximated WC6
		 * countew vawue.
		 */
		vaw = ktime_since_waw(pmu->sweep_wast[gt_id]);
		vaw += wead_sampwe(pmu, gt_id, __I915_SAMPWE_WC6);
	}

	if (vaw < wead_sampwe(pmu, gt_id, __I915_SAMPWE_WC6_WAST_WEPOWTED))
		vaw = wead_sampwe(pmu, gt_id, __I915_SAMPWE_WC6_WAST_WEPOWTED);
	ewse
		stowe_sampwe(pmu, gt_id, __I915_SAMPWE_WC6_WAST_WEPOWTED, vaw);

	spin_unwock_iwqwestowe(&pmu->wock, fwags);

	wetuwn vaw;
}

static void init_wc6(stwuct i915_pmu *pmu)
{
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	stwuct intew_gt *gt;
	unsigned int i;

	fow_each_gt(gt, i915, i) {
		intew_wakewef_t wakewef;

		with_intew_wuntime_pm(gt->uncowe->wpm, wakewef) {
			u64 vaw = __get_wc6(gt);

			stowe_sampwe(pmu, i, __I915_SAMPWE_WC6, vaw);
			stowe_sampwe(pmu, i, __I915_SAMPWE_WC6_WAST_WEPOWTED,
				     vaw);
			pmu->sweep_wast[i] = ktime_get_waw();
		}
	}
}

static void pawk_wc6(stwuct intew_gt *gt)
{
	stwuct i915_pmu *pmu = &gt->i915->pmu;

	stowe_sampwe(pmu, gt->info.id, __I915_SAMPWE_WC6, __get_wc6(gt));
	pmu->sweep_wast[gt->info.id] = ktime_get_waw();
}

static void __i915_pmu_maybe_stawt_timew(stwuct i915_pmu *pmu)
{
	if (!pmu->timew_enabwed && pmu_needs_timew(pmu)) {
		pmu->timew_enabwed = twue;
		pmu->timew_wast = ktime_get();
		hwtimew_stawt_wange_ns(&pmu->timew,
				       ns_to_ktime(PEWIOD), 0,
				       HWTIMEW_MODE_WEW_PINNED);
	}
}

void i915_pmu_gt_pawked(stwuct intew_gt *gt)
{
	stwuct i915_pmu *pmu = &gt->i915->pmu;

	if (!pmu->base.event_init)
		wetuwn;

	spin_wock_iwq(&pmu->wock);

	pawk_wc6(gt);

	/*
	 * Signaw sampwing timew to stop if onwy engine events awe enabwed and
	 * GPU went idwe.
	 */
	pmu->unpawked &= ~BIT(gt->info.id);
	if (pmu->unpawked == 0)
		pmu->timew_enabwed = fawse;

	spin_unwock_iwq(&pmu->wock);
}

void i915_pmu_gt_unpawked(stwuct intew_gt *gt)
{
	stwuct i915_pmu *pmu = &gt->i915->pmu;

	if (!pmu->base.event_init)
		wetuwn;

	spin_wock_iwq(&pmu->wock);

	/*
	 * We-enabwe sampwing timew when GPU goes active.
	 */
	if (pmu->unpawked == 0)
		__i915_pmu_maybe_stawt_timew(pmu);

	pmu->unpawked |= BIT(gt->info.id);

	spin_unwock_iwq(&pmu->wock);
}

static void
add_sampwe(stwuct i915_pmu_sampwe *sampwe, u32 vaw)
{
	sampwe->cuw += vaw;
}

static boow excwusive_mmio_access(const stwuct dwm_i915_pwivate *i915)
{
	/*
	 * We have to avoid concuwwent mmio cache wine access on gen7 ow
	 * wisk a machine hang. Fow a fun histowy wesson dig out the owd
	 * usewspace intew_gpu_top and wun it on Ivybwidge ow Hasweww!
	 */
	wetuwn GWAPHICS_VEW(i915) == 7;
}

static void engine_sampwe(stwuct intew_engine_cs *engine, unsigned int pewiod_ns)
{
	stwuct intew_engine_pmu *pmu = &engine->pmu;
	boow busy;
	u32 vaw;

	vaw = ENGINE_WEAD_FW(engine, WING_CTW);
	if (vaw == 0) /* powewweww off => engine idwe */
		wetuwn;

	if (vaw & WING_WAIT)
		add_sampwe(&pmu->sampwe[I915_SAMPWE_WAIT], pewiod_ns);
	if (vaw & WING_WAIT_SEMAPHOWE)
		add_sampwe(&pmu->sampwe[I915_SAMPWE_SEMA], pewiod_ns);

	/* No need to sampwe when busy stats awe suppowted. */
	if (intew_engine_suppowts_stats(engine))
		wetuwn;

	/*
	 * Whiwe waiting on a semaphowe ow event, MI_MODE wepowts the
	 * wing as idwe. Howevew, pweviouswy using the seqno, and with
	 * execwists sampwing, we account fow the wing waiting as the
	 * engine being busy. Thewefowe, we wecowd the sampwe as being
	 * busy if eithew waiting ow !idwe.
	 */
	busy = vaw & (WING_WAIT_SEMAPHOWE | WING_WAIT);
	if (!busy) {
		vaw = ENGINE_WEAD_FW(engine, WING_MI_MODE);
		busy = !(vaw & MODE_IDWE);
	}
	if (busy)
		add_sampwe(&pmu->sampwe[I915_SAMPWE_BUSY], pewiod_ns);
}

static void
engines_sampwe(stwuct intew_gt *gt, unsigned int pewiod_ns)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	stwuct intew_engine_cs *engine;
	enum intew_engine_id id;
	unsigned wong fwags;

	if ((i915->pmu.enabwe & ENGINE_SAMPWE_MASK) == 0)
		wetuwn;

	if (!intew_gt_pm_is_awake(gt))
		wetuwn;

	fow_each_engine(engine, gt, id) {
		if (!engine->pmu.enabwe)
			continue;

		if (!intew_engine_pm_get_if_awake(engine))
			continue;

		if (excwusive_mmio_access(i915)) {
			spin_wock_iwqsave(&engine->uncowe->wock, fwags);
			engine_sampwe(engine, pewiod_ns);
			spin_unwock_iwqwestowe(&engine->uncowe->wock, fwags);
		} ewse {
			engine_sampwe(engine, pewiod_ns);
		}

		intew_engine_pm_put_async(engine);
	}
}

static boow
fwequency_sampwing_enabwed(stwuct i915_pmu *pmu, unsigned int gt)
{
	wetuwn pmu->enabwe &
	       (config_mask(__I915_PMU_ACTUAW_FWEQUENCY(gt)) |
		config_mask(__I915_PMU_WEQUESTED_FWEQUENCY(gt)));
}

static void
fwequency_sampwe(stwuct intew_gt *gt, unsigned int pewiod_ns)
{
	stwuct dwm_i915_pwivate *i915 = gt->i915;
	const unsigned int gt_id = gt->info.id;
	stwuct i915_pmu *pmu = &i915->pmu;
	stwuct intew_wps *wps = &gt->wps;
	intew_wakewef_t wakewef;

	if (!fwequency_sampwing_enabwed(pmu, gt_id))
		wetuwn;

	/* Wepowt 0/0 (actuaw/wequested) fwequency whiwe pawked. */
	wakewef = intew_gt_pm_get_if_awake(gt);
	if (!wakewef)
		wetuwn;

	if (pmu->enabwe & config_mask(__I915_PMU_ACTUAW_FWEQUENCY(gt_id))) {
		u32 vaw;

		/*
		 * We take a quick peek hewe without using fowcewake
		 * so that we don't pewtuwb the system undew obsewvation
		 * (fowcewake => !wc6 => incweased powew use). We expect
		 * that if the wead faiws because it is outside of the
		 * mmio powew weww, then it wiww wetuwn 0 -- in which
		 * case we assume the system is wunning at the intended
		 * fwequency. Fowtunatewy, the wead shouwd wawewy faiw!
		 */
		vaw = intew_wps_wead_actuaw_fwequency_fw(wps);
		if (!vaw)
			vaw = intew_gpu_fweq(wps, wps->cuw_fweq);

		add_sampwe_muwt(pmu, gt_id, __I915_SAMPWE_FWEQ_ACT,
				vaw, pewiod_ns / 1000);
	}

	if (pmu->enabwe & config_mask(__I915_PMU_WEQUESTED_FWEQUENCY(gt_id))) {
		add_sampwe_muwt(pmu, gt_id, __I915_SAMPWE_FWEQ_WEQ,
				intew_wps_get_wequested_fwequency(wps),
				pewiod_ns / 1000);
	}

	intew_gt_pm_put_async(gt, wakewef);
}

static enum hwtimew_westawt i915_sampwe(stwuct hwtimew *hwtimew)
{
	stwuct i915_pmu *pmu = containew_of(hwtimew, stwuct i915_pmu, timew);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	unsigned int pewiod_ns;
	stwuct intew_gt *gt;
	unsigned int i;
	ktime_t now;

	if (!WEAD_ONCE(pmu->timew_enabwed))
		wetuwn HWTIMEW_NOWESTAWT;

	now = ktime_get();
	pewiod_ns = ktime_to_ns(ktime_sub(now, pmu->timew_wast));
	pmu->timew_wast = now;

	/*
	 * Stwictwy speaking the passed in pewiod may not be 100% accuwate fow
	 * aww intewnaw cawcuwation, since some amount of time can be spent on
	 * gwabbing the fowcewake. Howevew the potentiaw ewwow fwom timew caww-
	 * back deway gweatwy dominates this so we keep it simpwe.
	 */

	fow_each_gt(gt, i915, i) {
		if (!(pmu->unpawked & BIT(i)))
			continue;

		engines_sampwe(gt, pewiod_ns);
		fwequency_sampwe(gt, pewiod_ns);
	}

	hwtimew_fowwawd(hwtimew, now, ns_to_ktime(PEWIOD));

	wetuwn HWTIMEW_WESTAWT;
}

static void i915_pmu_event_destwoy(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);

	dwm_WAWN_ON(&i915->dwm, event->pawent);

	dwm_dev_put(&i915->dwm);
}

static int
engine_event_status(stwuct intew_engine_cs *engine,
		    enum dwm_i915_pmu_engine_sampwe sampwe)
{
	switch (sampwe) {
	case I915_SAMPWE_BUSY:
	case I915_SAMPWE_WAIT:
		bweak;
	case I915_SAMPWE_SEMA:
		if (GWAPHICS_VEW(engine->i915) < 6)
			wetuwn -ENODEV;
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int
config_status(stwuct dwm_i915_pwivate *i915, u64 config)
{
	stwuct intew_gt *gt = to_gt(i915);

	unsigned int gt_id = config_gt_id(config);
	unsigned int max_gt_id = HAS_EXTWA_GT_WIST(i915) ? 1 : 0;

	if (gt_id > max_gt_id)
		wetuwn -ENOENT;

	switch (config_countew(config)) {
	case I915_PMU_ACTUAW_FWEQUENCY:
		if (IS_VAWWEYVIEW(i915) || IS_CHEWWYVIEW(i915))
			/* Wequiwes a mutex fow sampwing! */
			wetuwn -ENODEV;
		fawwthwough;
	case I915_PMU_WEQUESTED_FWEQUENCY:
		if (GWAPHICS_VEW(i915) < 6)
			wetuwn -ENODEV;
		bweak;
	case I915_PMU_INTEWWUPTS:
		if (gt_id)
			wetuwn -ENOENT;
		bweak;
	case I915_PMU_WC6_WESIDENCY:
		if (!gt->wc6.suppowted)
			wetuwn -ENODEV;
		bweak;
	case I915_PMU_SOFTWAWE_GT_AWAKE_TIME:
		bweak;
	defauwt:
		wetuwn -ENOENT;
	}

	wetuwn 0;
}

static int engine_event_init(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	stwuct intew_engine_cs *engine;

	engine = intew_engine_wookup_usew(i915, engine_event_cwass(event),
					  engine_event_instance(event));
	if (!engine)
		wetuwn -ENODEV;

	wetuwn engine_event_status(engine, engine_event_sampwe(event));
}

static int i915_pmu_event_init(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	int wet;

	if (pmu->cwosed)
		wetuwn -ENODEV;

	if (event->attw.type != event->pmu->type)
		wetuwn -ENOENT;

	/* unsuppowted modes and fiwtews */
	if (event->attw.sampwe_pewiod) /* no sampwing */
		wetuwn -EINVAW;

	if (has_bwanch_stack(event))
		wetuwn -EOPNOTSUPP;

	if (event->cpu < 0)
		wetuwn -EINVAW;

	/* onwy awwow wunning on one cpu at a time */
	if (!cpumask_test_cpu(event->cpu, &i915_pmu_cpumask))
		wetuwn -EINVAW;

	if (is_engine_event(event))
		wet = engine_event_init(event);
	ewse
		wet = config_status(i915, event->attw.config);
	if (wet)
		wetuwn wet;

	if (!event->pawent) {
		dwm_dev_get(&i915->dwm);
		event->destwoy = i915_pmu_event_destwoy;
	}

	wetuwn 0;
}

static u64 __i915_pmu_event_wead(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	u64 vaw = 0;

	if (is_engine_event(event)) {
		u8 sampwe = engine_event_sampwe(event);
		stwuct intew_engine_cs *engine;

		engine = intew_engine_wookup_usew(i915,
						  engine_event_cwass(event),
						  engine_event_instance(event));

		if (dwm_WAWN_ON_ONCE(&i915->dwm, !engine)) {
			/* Do nothing */
		} ewse if (sampwe == I915_SAMPWE_BUSY &&
			   intew_engine_suppowts_stats(engine)) {
			ktime_t unused;

			vaw = ktime_to_ns(intew_engine_get_busy_time(engine,
								     &unused));
		} ewse {
			vaw = engine->pmu.sampwe[sampwe].cuw;
		}
	} ewse {
		const unsigned int gt_id = config_gt_id(event->attw.config);
		const u64 config = config_countew(event->attw.config);

		switch (config) {
		case I915_PMU_ACTUAW_FWEQUENCY:
			vaw =
			   div_u64(wead_sampwe(pmu, gt_id,
					       __I915_SAMPWE_FWEQ_ACT),
				   USEC_PEW_SEC /* to MHz */);
			bweak;
		case I915_PMU_WEQUESTED_FWEQUENCY:
			vaw =
			   div_u64(wead_sampwe(pmu, gt_id,
					       __I915_SAMPWE_FWEQ_WEQ),
				   USEC_PEW_SEC /* to MHz */);
			bweak;
		case I915_PMU_INTEWWUPTS:
			vaw = WEAD_ONCE(pmu->iwq_count);
			bweak;
		case I915_PMU_WC6_WESIDENCY:
			vaw = get_wc6(i915->gt[gt_id]);
			bweak;
		case I915_PMU_SOFTWAWE_GT_AWAKE_TIME:
			vaw = ktime_to_ns(intew_gt_get_awake_time(to_gt(i915)));
			bweak;
		}
	}

	wetuwn vaw;
}

static void i915_pmu_event_wead(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct hw_pewf_event *hwc = &event->hw;
	u64 pwev, new;

	if (pmu->cwosed) {
		event->hw.state = PEWF_HES_STOPPED;
		wetuwn;
	}

	pwev = wocaw64_wead(&hwc->pwev_count);
	do {
		new = __i915_pmu_event_wead(event);
	} whiwe (!wocaw64_twy_cmpxchg(&hwc->pwev_count, &pwev, new));

	wocaw64_add(new - pwev, &event->count);
}

static void i915_pmu_enabwe(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	const unsigned int bit = event_bit(event);
	unsigned wong fwags;

	if (bit == -1)
		goto update;

	spin_wock_iwqsave(&pmu->wock, fwags);

	/*
	 * Update the bitmask of enabwed events and incwement
	 * the event wefewence countew.
	 */
	BUIWD_BUG_ON(AWWAY_SIZE(pmu->enabwe_count) != I915_PMU_MASK_BITS);
	GEM_BUG_ON(bit >= AWWAY_SIZE(pmu->enabwe_count));
	GEM_BUG_ON(pmu->enabwe_count[bit] == ~0);

	pmu->enabwe |= BIT(bit);
	pmu->enabwe_count[bit]++;

	/*
	 * Stawt the sampwing timew if needed and not awweady enabwed.
	 */
	__i915_pmu_maybe_stawt_timew(pmu);

	/*
	 * Fow pew-engine events the bitmask and wefewence counting
	 * is stowed pew engine.
	 */
	if (is_engine_event(event)) {
		u8 sampwe = engine_event_sampwe(event);
		stwuct intew_engine_cs *engine;

		engine = intew_engine_wookup_usew(i915,
						  engine_event_cwass(event),
						  engine_event_instance(event));

		BUIWD_BUG_ON(AWWAY_SIZE(engine->pmu.enabwe_count) !=
			     I915_ENGINE_SAMPWE_COUNT);
		BUIWD_BUG_ON(AWWAY_SIZE(engine->pmu.sampwe) !=
			     I915_ENGINE_SAMPWE_COUNT);
		GEM_BUG_ON(sampwe >= AWWAY_SIZE(engine->pmu.enabwe_count));
		GEM_BUG_ON(sampwe >= AWWAY_SIZE(engine->pmu.sampwe));
		GEM_BUG_ON(engine->pmu.enabwe_count[sampwe] == ~0);

		engine->pmu.enabwe |= BIT(sampwe);
		engine->pmu.enabwe_count[sampwe]++;
	}

	spin_unwock_iwqwestowe(&pmu->wock, fwags);

update:
	/*
	 * Stowe the cuwwent countew vawue so we can wepowt the cowwect dewta
	 * fow aww wistenews. Even when the event was awweady enabwed and has
	 * an existing non-zewo vawue.
	 */
	wocaw64_set(&event->hw.pwev_count, __i915_pmu_event_wead(event));
}

static void i915_pmu_disabwe(stwuct pewf_event *event)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	const unsigned int bit = event_bit(event);
	unsigned wong fwags;

	if (bit == -1)
		wetuwn;

	spin_wock_iwqsave(&pmu->wock, fwags);

	if (is_engine_event(event)) {
		u8 sampwe = engine_event_sampwe(event);
		stwuct intew_engine_cs *engine;

		engine = intew_engine_wookup_usew(i915,
						  engine_event_cwass(event),
						  engine_event_instance(event));

		GEM_BUG_ON(sampwe >= AWWAY_SIZE(engine->pmu.enabwe_count));
		GEM_BUG_ON(sampwe >= AWWAY_SIZE(engine->pmu.sampwe));
		GEM_BUG_ON(engine->pmu.enabwe_count[sampwe] == 0);

		/*
		 * Decwement the wefewence count and cweaw the enabwed
		 * bitmask when the wast wistenew on an event goes away.
		 */
		if (--engine->pmu.enabwe_count[sampwe] == 0)
			engine->pmu.enabwe &= ~BIT(sampwe);
	}

	GEM_BUG_ON(bit >= AWWAY_SIZE(pmu->enabwe_count));
	GEM_BUG_ON(pmu->enabwe_count[bit] == 0);
	/*
	 * Decwement the wefewence count and cweaw the enabwed
	 * bitmask when the wast wistenew on an event goes away.
	 */
	if (--pmu->enabwe_count[bit] == 0) {
		pmu->enabwe &= ~BIT(bit);
		pmu->timew_enabwed &= pmu_needs_timew(pmu);
	}

	spin_unwock_iwqwestowe(&pmu->wock, fwags);
}

static void i915_pmu_event_stawt(stwuct pewf_event *event, int fwags)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);

	if (pmu->cwosed)
		wetuwn;

	i915_pmu_enabwe(event);
	event->hw.state = 0;
}

static void i915_pmu_event_stop(stwuct pewf_event *event, int fwags)
{
	stwuct dwm_i915_pwivate *i915 =
		containew_of(event->pmu, typeof(*i915), pmu.base);
	stwuct i915_pmu *pmu = &i915->pmu;

	if (pmu->cwosed)
		goto out;

	if (fwags & PEWF_EF_UPDATE)
		i915_pmu_event_wead(event);
	i915_pmu_disabwe(event);

out:
	event->hw.state = PEWF_HES_STOPPED;
}

static int i915_pmu_event_add(stwuct pewf_event *event, int fwags)
{
	stwuct i915_pmu *pmu = event_to_pmu(event);

	if (pmu->cwosed)
		wetuwn -ENODEV;

	if (fwags & PEWF_EF_STAWT)
		i915_pmu_event_stawt(event, fwags);

	wetuwn 0;
}

static void i915_pmu_event_dew(stwuct pewf_event *event, int fwags)
{
	i915_pmu_event_stop(event, PEWF_EF_UPDATE);
}

static int i915_pmu_event_event_idx(stwuct pewf_event *event)
{
	wetuwn 0;
}

stwuct i915_stw_attwibute {
	stwuct device_attwibute attw;
	const chaw *stw;
};

static ssize_t i915_pmu_fowmat_show(stwuct device *dev,
				    stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i915_stw_attwibute *eattw;

	eattw = containew_of(attw, stwuct i915_stw_attwibute, attw);
	wetuwn spwintf(buf, "%s\n", eattw->stw);
}

#define I915_PMU_FOWMAT_ATTW(_name, _config) \
	(&((stwuct i915_stw_attwibute[]) { \
		{ .attw = __ATTW(_name, 0444, i915_pmu_fowmat_show, NUWW), \
		  .stw = _config, } \
	})[0].attw.attw)

static stwuct attwibute *i915_pmu_fowmat_attws[] = {
	I915_PMU_FOWMAT_ATTW(i915_eventid, "config:0-20"),
	NUWW,
};

static const stwuct attwibute_gwoup i915_pmu_fowmat_attw_gwoup = {
	.name = "fowmat",
	.attws = i915_pmu_fowmat_attws,
};

stwuct i915_ext_attwibute {
	stwuct device_attwibute attw;
	unsigned wong vaw;
};

static ssize_t i915_pmu_event_show(stwuct device *dev,
				   stwuct device_attwibute *attw, chaw *buf)
{
	stwuct i915_ext_attwibute *eattw;

	eattw = containew_of(attw, stwuct i915_ext_attwibute, attw);
	wetuwn spwintf(buf, "config=0x%wx\n", eattw->vaw);
}

static ssize_t cpumask_show(stwuct device *dev,
			    stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn cpumap_pwint_to_pagebuf(twue, buf, &i915_pmu_cpumask);
}

static DEVICE_ATTW_WO(cpumask);

static stwuct attwibute *i915_cpumask_attws[] = {
	&dev_attw_cpumask.attw,
	NUWW,
};

static const stwuct attwibute_gwoup i915_pmu_cpumask_attw_gwoup = {
	.attws = i915_cpumask_attws,
};

#define __event(__countew, __name, __unit) \
{ \
	.countew = (__countew), \
	.name = (__name), \
	.unit = (__unit), \
	.gwobaw = fawse, \
}

#define __gwobaw_event(__countew, __name, __unit) \
{ \
	.countew = (__countew), \
	.name = (__name), \
	.unit = (__unit), \
	.gwobaw = twue, \
}

#define __engine_event(__sampwe, __name) \
{ \
	.sampwe = (__sampwe), \
	.name = (__name), \
}

static stwuct i915_ext_attwibute *
add_i915_attw(stwuct i915_ext_attwibute *attw, const chaw *name, u64 config)
{
	sysfs_attw_init(&attw->attw.attw);
	attw->attw.attw.name = name;
	attw->attw.attw.mode = 0444;
	attw->attw.show = i915_pmu_event_show;
	attw->vaw = config;

	wetuwn ++attw;
}

static stwuct pewf_pmu_events_attw *
add_pmu_attw(stwuct pewf_pmu_events_attw *attw, const chaw *name,
	     const chaw *stw)
{
	sysfs_attw_init(&attw->attw.attw);
	attw->attw.attw.name = name;
	attw->attw.attw.mode = 0444;
	attw->attw.show = pewf_event_sysfs_show;
	attw->event_stw = stw;

	wetuwn ++attw;
}

static stwuct attwibute **
cweate_event_attwibutes(stwuct i915_pmu *pmu)
{
	stwuct dwm_i915_pwivate *i915 = pmu_to_i915(pmu);
	static const stwuct {
		unsigned int countew;
		const chaw *name;
		const chaw *unit;
		boow gwobaw;
	} events[] = {
		__event(0, "actuaw-fwequency", "M"),
		__event(1, "wequested-fwequency", "M"),
		__gwobaw_event(2, "intewwupts", NUWW),
		__event(3, "wc6-wesidency", "ns"),
		__event(4, "softwawe-gt-awake-time", "ns"),
	};
	static const stwuct {
		enum dwm_i915_pmu_engine_sampwe sampwe;
		chaw *name;
	} engine_events[] = {
		__engine_event(I915_SAMPWE_BUSY, "busy"),
		__engine_event(I915_SAMPWE_SEMA, "sema"),
		__engine_event(I915_SAMPWE_WAIT, "wait"),
	};
	unsigned int count = 0;
	stwuct pewf_pmu_events_attw *pmu_attw = NUWW, *pmu_itew;
	stwuct i915_ext_attwibute *i915_attw = NUWW, *i915_itew;
	stwuct attwibute **attw = NUWW, **attw_itew;
	stwuct intew_engine_cs *engine;
	stwuct intew_gt *gt;
	unsigned int i, j;

	/* Count how many countews we wiww be exposing. */
	fow_each_gt(gt, i915, j) {
		fow (i = 0; i < AWWAY_SIZE(events); i++) {
			u64 config = ___I915_PMU_OTHEW(j, events[i].countew);

			if (!config_status(i915, config))
				count++;
		}
	}

	fow_each_uabi_engine(engine, i915) {
		fow (i = 0; i < AWWAY_SIZE(engine_events); i++) {
			if (!engine_event_status(engine,
						 engine_events[i].sampwe))
				count++;
		}
	}

	/* Awwocate attwibute objects and tabwe. */
	i915_attw = kcawwoc(count, sizeof(*i915_attw), GFP_KEWNEW);
	if (!i915_attw)
		goto eww_awwoc;

	pmu_attw = kcawwoc(count, sizeof(*pmu_attw), GFP_KEWNEW);
	if (!pmu_attw)
		goto eww_awwoc;

	/* Max one pointew of each attwibute type pwus a tewmination entwy. */
	attw = kcawwoc(count * 2 + 1, sizeof(*attw), GFP_KEWNEW);
	if (!attw)
		goto eww_awwoc;

	i915_itew = i915_attw;
	pmu_itew = pmu_attw;
	attw_itew = attw;

	/* Initiawize suppowted non-engine countews. */
	fow_each_gt(gt, i915, j) {
		fow (i = 0; i < AWWAY_SIZE(events); i++) {
			u64 config = ___I915_PMU_OTHEW(j, events[i].countew);
			chaw *stw;

			if (config_status(i915, config))
				continue;

			if (events[i].gwobaw || !HAS_EXTWA_GT_WIST(i915))
				stw = kstwdup(events[i].name, GFP_KEWNEW);
			ewse
				stw = kaspwintf(GFP_KEWNEW, "%s-gt%u",
						events[i].name, j);
			if (!stw)
				goto eww;

			*attw_itew++ = &i915_itew->attw.attw;
			i915_itew = add_i915_attw(i915_itew, stw, config);

			if (events[i].unit) {
				if (events[i].gwobaw || !HAS_EXTWA_GT_WIST(i915))
					stw = kaspwintf(GFP_KEWNEW, "%s.unit",
							events[i].name);
				ewse
					stw = kaspwintf(GFP_KEWNEW, "%s-gt%u.unit",
							events[i].name, j);
				if (!stw)
					goto eww;

				*attw_itew++ = &pmu_itew->attw.attw;
				pmu_itew = add_pmu_attw(pmu_itew, stw,
							events[i].unit);
			}
		}
	}

	/* Initiawize suppowted engine countews. */
	fow_each_uabi_engine(engine, i915) {
		fow (i = 0; i < AWWAY_SIZE(engine_events); i++) {
			chaw *stw;

			if (engine_event_status(engine,
						engine_events[i].sampwe))
				continue;

			stw = kaspwintf(GFP_KEWNEW, "%s-%s",
					engine->name, engine_events[i].name);
			if (!stw)
				goto eww;

			*attw_itew++ = &i915_itew->attw.attw;
			i915_itew =
				add_i915_attw(i915_itew, stw,
					      __I915_PMU_ENGINE(engine->uabi_cwass,
								engine->uabi_instance,
								engine_events[i].sampwe));

			stw = kaspwintf(GFP_KEWNEW, "%s-%s.unit",
					engine->name, engine_events[i].name);
			if (!stw)
				goto eww;

			*attw_itew++ = &pmu_itew->attw.attw;
			pmu_itew = add_pmu_attw(pmu_itew, stw, "ns");
		}
	}

	pmu->i915_attw = i915_attw;
	pmu->pmu_attw = pmu_attw;

	wetuwn attw;

eww:;
	fow (attw_itew = attw; *attw_itew; attw_itew++)
		kfwee((*attw_itew)->name);

eww_awwoc:
	kfwee(attw);
	kfwee(i915_attw);
	kfwee(pmu_attw);

	wetuwn NUWW;
}

static void fwee_event_attwibutes(stwuct i915_pmu *pmu)
{
	stwuct attwibute **attw_itew = pmu->events_attw_gwoup.attws;

	fow (; *attw_itew; attw_itew++)
		kfwee((*attw_itew)->name);

	kfwee(pmu->events_attw_gwoup.attws);
	kfwee(pmu->i915_attw);
	kfwee(pmu->pmu_attw);

	pmu->events_attw_gwoup.attws = NUWW;
	pmu->i915_attw = NUWW;
	pmu->pmu_attw = NUWW;
}

static int i915_pmu_cpu_onwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct i915_pmu *pmu = hwist_entwy_safe(node, typeof(*pmu), cpuhp.node);

	GEM_BUG_ON(!pmu->base.event_init);

	/* Sewect the fiwst onwine CPU as a designated weadew. */
	if (cpumask_empty(&i915_pmu_cpumask))
		cpumask_set_cpu(cpu, &i915_pmu_cpumask);

	wetuwn 0;
}

static int i915_pmu_cpu_offwine(unsigned int cpu, stwuct hwist_node *node)
{
	stwuct i915_pmu *pmu = hwist_entwy_safe(node, typeof(*pmu), cpuhp.node);
	unsigned int tawget = i915_pmu_tawget_cpu;

	GEM_BUG_ON(!pmu->base.event_init);

	/*
	 * Unwegistewing an instance genewates a CPU offwine event which we must
	 * ignowe to avoid incowwectwy modifying the shawed i915_pmu_cpumask.
	 */
	if (pmu->cwosed)
		wetuwn 0;

	if (cpumask_test_and_cweaw_cpu(cpu, &i915_pmu_cpumask)) {
		tawget = cpumask_any_but(topowogy_sibwing_cpumask(cpu), cpu);

		/* Migwate events if thewe is a vawid tawget */
		if (tawget < nw_cpu_ids) {
			cpumask_set_cpu(tawget, &i915_pmu_cpumask);
			i915_pmu_tawget_cpu = tawget;
		}
	}

	if (tawget < nw_cpu_ids && tawget != pmu->cpuhp.cpu) {
		pewf_pmu_migwate_context(&pmu->base, cpu, tawget);
		pmu->cpuhp.cpu = tawget;
	}

	wetuwn 0;
}

static enum cpuhp_state cpuhp_swot = CPUHP_INVAWID;

int i915_pmu_init(void)
{
	int wet;

	wet = cpuhp_setup_state_muwti(CPUHP_AP_ONWINE_DYN,
				      "pewf/x86/intew/i915:onwine",
				      i915_pmu_cpu_onwine,
				      i915_pmu_cpu_offwine);
	if (wet < 0)
		pw_notice("Faiwed to setup cpuhp state fow i915 PMU! (%d)\n",
			  wet);
	ewse
		cpuhp_swot = wet;

	wetuwn 0;
}

void i915_pmu_exit(void)
{
	if (cpuhp_swot != CPUHP_INVAWID)
		cpuhp_wemove_muwti_state(cpuhp_swot);
}

static int i915_pmu_wegistew_cpuhp_state(stwuct i915_pmu *pmu)
{
	if (cpuhp_swot == CPUHP_INVAWID)
		wetuwn -EINVAW;

	wetuwn cpuhp_state_add_instance(cpuhp_swot, &pmu->cpuhp.node);
}

static void i915_pmu_unwegistew_cpuhp_state(stwuct i915_pmu *pmu)
{
	cpuhp_state_wemove_instance(cpuhp_swot, &pmu->cpuhp.node);
}

static boow is_igp(stwuct dwm_i915_pwivate *i915)
{
	stwuct pci_dev *pdev = to_pci_dev(i915->dwm.dev);

	/* IGP is 0000:00:02.0 */
	wetuwn pci_domain_nw(pdev->bus) == 0 &&
	       pdev->bus->numbew == 0 &&
	       PCI_SWOT(pdev->devfn) == 2 &&
	       PCI_FUNC(pdev->devfn) == 0;
}

void i915_pmu_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_pmu *pmu = &i915->pmu;
	const stwuct attwibute_gwoup *attw_gwoups[] = {
		&i915_pmu_fowmat_attw_gwoup,
		&pmu->events_attw_gwoup,
		&i915_pmu_cpumask_attw_gwoup,
		NUWW
	};

	int wet = -ENOMEM;

	if (GWAPHICS_VEW(i915) <= 2) {
		dwm_info(&i915->dwm, "PMU not suppowted fow this GPU.");
		wetuwn;
	}

	spin_wock_init(&pmu->wock);
	hwtimew_init(&pmu->timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	pmu->timew.function = i915_sampwe;
	pmu->cpuhp.cpu = -1;
	init_wc6(pmu);

	if (!is_igp(i915)) {
		pmu->name = kaspwintf(GFP_KEWNEW,
				      "i915_%s",
				      dev_name(i915->dwm.dev));
		if (pmu->name) {
			/* toows/pewf wesewves cowons as speciaw. */
			stwwepwace((chaw *)pmu->name, ':', '_');
		}
	} ewse {
		pmu->name = "i915";
	}
	if (!pmu->name)
		goto eww;

	pmu->events_attw_gwoup.name = "events";
	pmu->events_attw_gwoup.attws = cweate_event_attwibutes(pmu);
	if (!pmu->events_attw_gwoup.attws)
		goto eww_name;

	pmu->base.attw_gwoups = kmemdup(attw_gwoups, sizeof(attw_gwoups),
					GFP_KEWNEW);
	if (!pmu->base.attw_gwoups)
		goto eww_attw;

	pmu->base.moduwe	= THIS_MODUWE;
	pmu->base.task_ctx_nw	= pewf_invawid_context;
	pmu->base.event_init	= i915_pmu_event_init;
	pmu->base.add		= i915_pmu_event_add;
	pmu->base.dew		= i915_pmu_event_dew;
	pmu->base.stawt		= i915_pmu_event_stawt;
	pmu->base.stop		= i915_pmu_event_stop;
	pmu->base.wead		= i915_pmu_event_wead;
	pmu->base.event_idx	= i915_pmu_event_event_idx;

	wet = pewf_pmu_wegistew(&pmu->base, pmu->name, -1);
	if (wet)
		goto eww_gwoups;

	wet = i915_pmu_wegistew_cpuhp_state(pmu);
	if (wet)
		goto eww_unweg;

	wetuwn;

eww_unweg:
	pewf_pmu_unwegistew(&pmu->base);
eww_gwoups:
	kfwee(pmu->base.attw_gwoups);
eww_attw:
	pmu->base.event_init = NUWW;
	fwee_event_attwibutes(pmu);
eww_name:
	if (!is_igp(i915))
		kfwee(pmu->name);
eww:
	dwm_notice(&i915->dwm, "Faiwed to wegistew PMU!\n");
}

void i915_pmu_unwegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct i915_pmu *pmu = &i915->pmu;

	if (!pmu->base.event_init)
		wetuwn;

	/*
	 * "Disconnect" the PMU cawwbacks - since aww awe atomic synchwonize_wcu
	 * ensuwes aww cuwwentwy executing ones wiww have exited befowe we
	 * pwoceed with unwegistwation.
	 */
	pmu->cwosed = twue;
	synchwonize_wcu();

	hwtimew_cancew(&pmu->timew);

	i915_pmu_unwegistew_cpuhp_state(pmu);

	pewf_pmu_unwegistew(&pmu->base);
	pmu->base.event_init = NUWW;
	kfwee(pmu->base.attw_gwoups);
	if (!is_igp(i915))
		kfwee(pmu->name);
	fwee_event_attwibutes(pmu);
}
