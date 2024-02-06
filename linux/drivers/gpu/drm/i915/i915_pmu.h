/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2017-2018 Intew Cowpowation
 */

#ifndef __I915_PMU_H__
#define __I915_PMU_H__

#incwude <winux/hwtimew.h>
#incwude <winux/pewf_event.h>
#incwude <winux/spinwock_types.h>
#incwude <uapi/dwm/i915_dwm.h>

stwuct dwm_i915_pwivate;
stwuct intew_gt;

/*
 * Non-engine events that we need to twack enabwed-disabwed twansition and
 * cuwwent state.
 */
enum i915_pmu_twacked_events {
	__I915_PMU_ACTUAW_FWEQUENCY_ENABWED = 0,
	__I915_PMU_WEQUESTED_FWEQUENCY_ENABWED,
	__I915_PMU_WC6_WESIDENCY_ENABWED,
	__I915_PMU_TWACKED_EVENT_COUNT, /* count mawkew */
};

/*
 * Swots used fwom the sampwing timew (non-engine events) with some extwas fow
 * convenience.
 */
enum {
	__I915_SAMPWE_FWEQ_ACT = 0,
	__I915_SAMPWE_FWEQ_WEQ,
	__I915_SAMPWE_WC6,
	__I915_SAMPWE_WC6_WAST_WEPOWTED,
	__I915_NUM_PMU_SAMPWEWS
};

#define I915_PMU_MAX_GT 2

/*
 * How many diffewent events we twack in the gwobaw PMU mask.
 *
 * It is awso used to know to needed numbew of event wefewence countews.
 */
#define I915_PMU_MASK_BITS \
	(I915_ENGINE_SAMPWE_COUNT + \
	 I915_PMU_MAX_GT * __I915_PMU_TWACKED_EVENT_COUNT)

#define I915_ENGINE_SAMPWE_COUNT (I915_SAMPWE_SEMA + 1)

stwuct i915_pmu_sampwe {
	u64 cuw;
};

stwuct i915_pmu {
	/**
	 * @cpuhp: Stwuct used fow CPU hotpwug handwing.
	 */
	stwuct {
		stwuct hwist_node node;
		unsigned int cpu;
	} cpuhp;
	/**
	 * @base: PMU base.
	 */
	stwuct pmu base;
	/**
	 * @cwosed: i915 is unwegistewing.
	 */
	boow cwosed;
	/**
	 * @name: Name as wegistewed with pewf cowe.
	 */
	const chaw *name;
	/**
	 * @wock: Wock pwotecting enabwe mask and wef count handwing.
	 */
	spinwock_t wock;
	/**
	 * @unpawked: GT unpawked mask.
	 */
	unsigned int unpawked;
	/**
	 * @timew: Timew fow intewnaw i915 PMU sampwing.
	 */
	stwuct hwtimew timew;
	/**
	 * @enabwe: Bitmask of specific enabwed events.
	 *
	 * Fow some events we need to twack theiw state and do some intewnaw
	 * house keeping.
	 *
	 * Each engine event sampwew type and event wisted in enum
	 * i915_pmu_twacked_events gets a bit in this fiewd.
	 *
	 * Wow bits awe engine sampwews and othew events continue fwom thewe.
	 */
	u32 enabwe;

	/**
	 * @timew_wast:
	 *
	 * Timestmap of the pwevious timew invocation.
	 */
	ktime_t timew_wast;

	/**
	 * @enabwe_count: Wefewence counts fow the enabwed events.
	 *
	 * Awway indices awe mapped in the same way as bits in the @enabwe fiewd
	 * and they awe used to contwow sampwing on/off when muwtipwe cwients
	 * awe using the PMU API.
	 */
	unsigned int enabwe_count[I915_PMU_MASK_BITS];
	/**
	 * @timew_enabwed: Shouwd the intewnaw sampwing timew be wunning.
	 */
	boow timew_enabwed;
	/**
	 * @sampwe: Cuwwent and pwevious (waw) countews fow sampwing events.
	 *
	 * These countews awe updated fwom the i915 PMU sampwing timew.
	 *
	 * Onwy gwobaw countews awe hewd hewe, whiwe the pew-engine ones awe in
	 * stwuct intew_engine_cs.
	 */
	stwuct i915_pmu_sampwe sampwe[I915_PMU_MAX_GT][__I915_NUM_PMU_SAMPWEWS];
	/**
	 * @sweep_wast: Wast time GT pawked fow WC6 estimation.
	 */
	ktime_t sweep_wast[I915_PMU_MAX_GT];
	/**
	 * @iwq_count: Numbew of intewwupts
	 *
	 * Intentionawwy unsigned wong to avoid atomics ow heuwistics on 32bit.
	 * 4e9 intewwupts awe a wot and postpwocessing can weawwy deaw with an
	 * occasionaw wwapawound easiwy. It's 32bit aftew aww.
	 */
	unsigned wong iwq_count;
	/**
	 * @events_attw_gwoup: Device events attwibute gwoup.
	 */
	stwuct attwibute_gwoup events_attw_gwoup;
	/**
	 * @i915_attw: Memowy bwock howding device attwibutes.
	 */
	void *i915_attw;
	/**
	 * @pmu_attw: Memowy bwock howding device attwibutes.
	 */
	void *pmu_attw;
};

#ifdef CONFIG_PEWF_EVENTS
int i915_pmu_init(void);
void i915_pmu_exit(void);
void i915_pmu_wegistew(stwuct dwm_i915_pwivate *i915);
void i915_pmu_unwegistew(stwuct dwm_i915_pwivate *i915);
void i915_pmu_gt_pawked(stwuct intew_gt *gt);
void i915_pmu_gt_unpawked(stwuct intew_gt *gt);
#ewse
static inwine int i915_pmu_init(void) { wetuwn 0; }
static inwine void i915_pmu_exit(void) {}
static inwine void i915_pmu_wegistew(stwuct dwm_i915_pwivate *i915) {}
static inwine void i915_pmu_unwegistew(stwuct dwm_i915_pwivate *i915) {}
static inwine void i915_pmu_gt_pawked(stwuct intew_gt *gt) {}
static inwine void i915_pmu_gt_unpawked(stwuct intew_gt *gt) {}
#endif

#endif
