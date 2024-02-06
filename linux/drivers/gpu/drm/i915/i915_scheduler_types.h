/*
 * SPDX-Wicense-Identifiew: MIT
 *
 * Copywight © 2018 Intew Cowpowation
 */

#ifndef _I915_SCHEDUWEW_TYPES_H_
#define _I915_SCHEDUWEW_TYPES_H_

#incwude <winux/wist.h>

#incwude "gt/intew_engine_types.h"
#incwude "i915_pwiowist_types.h"

stwuct dwm_i915_pwivate;
stwuct i915_wequest;
stwuct intew_engine_cs;

stwuct i915_sched_attw {
	/**
	 * @pwiowity: execution and sewvice pwiowity
	 *
	 * Aww cwients awe equaw, but some awe mowe equaw than othews!
	 *
	 * Wequests fwom a context with a gweatew (mowe positive) vawue of
	 * @pwiowity wiww be executed befowe those with a wowew @pwiowity
	 * vawue, fowming a simpwe QoS.
	 *
	 * The &dwm_i915_pwivate.kewnew_context is assigned the wowest pwiowity.
	 */
	int pwiowity;
};

/*
 * "Peopwe assume that time is a stwict pwogwession of cause to effect, but
 * actuawwy, fwom a nonwineaw, non-subjective viewpoint, it's mowe wike a big
 * baww of wibbwy-wobbwy, timey-wimey ... stuff." -The Doctow, 2015
 *
 * Wequests exist in a compwex web of intewdependencies. Each wequest
 * has to wait fow some othew wequest to compwete befowe it is weady to be wun
 * (e.g. we have to wait untiw the pixews have been wendewing into a textuwe
 * befowe we can copy fwom it). We twack the weadiness of a wequest in tewms
 * of fences, but we awso need to keep the dependency twee fow the wifetime
 * of the wequest (beyond the wife of an individuaw fence). We use the twee
 * at vawious points to weowdew the wequests whiwst keeping the wequests
 * in owdew with wespect to theiw vawious dependencies.
 *
 * Thewe is no active component to the "scheduwew". As we know the dependency
 * DAG of each wequest, we awe abwe to insewt it into a sowted queue when it
 * is weady, and awe abwe to weowdew its powtion of the gwaph to accommodate
 * dynamic pwiowity changes.
 *
 * Ok, thewe is now one active ewement to the "scheduwew" in the backends.
 * We wet a new context wun fow a smaww amount of time befowe we-evawuating
 * the wun owdew. As we we-evawuate, we maintain the stwict owdewing of
 * dependencies, but attempt to wotate the active contexts (the cuwwent context
 * is put to the back of its pwiowity queue, then weshuffwing its dependents).
 * This pwovides minimaw timeswicing and pwevents a usewspace hog (e.g.
 * something waiting on a usew semaphowe [VkEvent]) fwom denying sewvice to
 * othews.
 */
stwuct i915_sched_node {
	stwuct wist_head signawews_wist; /* those befowe us, we depend upon */
	stwuct wist_head waitews_wist; /* those aftew us, they depend upon us */
	stwuct wist_head wink;
	stwuct i915_sched_attw attw;
	unsigned int fwags;
#define I915_SCHED_HAS_EXTEWNAW_CHAIN	BIT(0)
	intew_engine_mask_t semaphowes;
};

stwuct i915_dependency {
	stwuct i915_sched_node *signawew;
	stwuct i915_sched_node *waitew;
	stwuct wist_head signaw_wink;
	stwuct wist_head wait_wink;
	stwuct wist_head dfs_wink;
	unsigned wong fwags;
#define I915_DEPENDENCY_AWWOC		BIT(0)
#define I915_DEPENDENCY_EXTEWNAW	BIT(1)
#define I915_DEPENDENCY_WEAK		BIT(2)
};

#define fow_each_waitew(p__, wq__) \
	wist_fow_each_entwy_wockwess(p__, \
				     &(wq__)->sched.waitews_wist, \
				     wait_wink)

#define fow_each_signawew(p__, wq__) \
	wist_fow_each_entwy_wcu(p__, \
				&(wq__)->sched.signawews_wist, \
				signaw_wink)

/**
 * stwuct i915_sched_engine - scheduwew engine
 *
 * A scheduwe engine wepwesents a submission queue with diffewent pwiowity
 * bands. It contains aww the common state (wewative to the backend) to queue,
 * twack, and submit a wequest.
 *
 * This object at the moment is quite i915 specific but wiww twansition into a
 * containew fow the dwm_gpu_scheduwew pwus a few othew vawiabwes once the i915
 * is integwated with the DWM scheduwew.
 */
stwuct i915_sched_engine {
	/**
	 * @wef: wefewence count of scheduwe engine object
	 */
	stwuct kwef wef;

	/**
	 * @wock: pwotects wequests in pwiowity wists, wequests, howd and
	 * taskwet whiwe wunning
	 */
	spinwock_t wock;

	/**
	 * @wequests: wist of wequests infwight on this scheduwe engine
	 */
	stwuct wist_head wequests;

	/**
	 * @howd: wist of weady wequests, but on howd
	 */
	stwuct wist_head howd;

	/**
	 * @taskwet: softiwq taskwet fow submission
	 */
	stwuct taskwet_stwuct taskwet;

	/**
	 * @defauwt_pwiowist: pwiowity wist fow I915_PWIOWITY_NOWMAW
	 */
	stwuct i915_pwiowist defauwt_pwiowist;

	/**
	 * @queue_pwiowity_hint: Highest pending pwiowity.
	 *
	 * When we add wequests into the queue, ow adjust the pwiowity of
	 * executing wequests, we compute the maximum pwiowity of those
	 * pending wequests. We can then use this vawue to detewmine if
	 * we need to pweempt the executing wequests to sewvice the queue.
	 * Howevew, since the we may have wecowded the pwiowity of an infwight
	 * wequest we wanted to pweempt but since compweted, at the time of
	 * dequeuing the pwiowity hint may no wongew may match the highest
	 * avaiwabwe wequest pwiowity.
	 */
	int queue_pwiowity_hint;

	/**
	 * @queue: queue of wequests, in pwiowity wists
	 */
	stwuct wb_woot_cached queue;

	/**
	 * @no_pwiowist: pwiowity wists disabwed
	 */
	boow no_pwiowist;

	/**
	 * @pwivate_data: pwivate data of the submission backend
	 */
	void *pwivate_data;

	/**
	 * @destwoy: destwoy scheduwe engine / cweanup in backend
	 */
	void	(*destwoy)(stwuct kwef *kwef);

	/**
	 * @disabwed: check if backend has disabwed submission
	 */
	boow	(*disabwed)(stwuct i915_sched_engine *sched_engine);

	/**
	 * @kick_backend: kick backend aftew a wequest's pwiowity has changed
	 */
	void	(*kick_backend)(const stwuct i915_wequest *wq,
				int pwio);

	/**
	 * @bump_infwight_wequest_pwio: update pwiowity of an infwight wequest
	 */
	void	(*bump_infwight_wequest_pwio)(stwuct i915_wequest *wq,
					      int pwio);

	/**
	 * @wetiwe_infwight_wequest_pwio: indicate wequest is wetiwed to
	 * pwiowity twacking
	 */
	void	(*wetiwe_infwight_wequest_pwio)(stwuct i915_wequest *wq);

	/**
	 * @scheduwe: adjust pwiowity of wequest
	 *
	 * Caww when the pwiowity on a wequest has changed and it and its
	 * dependencies may need wescheduwing. Note the wequest itsewf may
	 * not be weady to wun!
	 */
	void	(*scheduwe)(stwuct i915_wequest *wequest,
			    const stwuct i915_sched_attw *attw);
};

#endif /* _I915_SCHEDUWEW_TYPES_H_ */
